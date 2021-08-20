/** @file
  SMM CSE Variable Storage IO Library

  CSE Variable Storage I/O in SMM can operate in three states:
    1. Before Core BIOS Done: HECI1
    2. After Core BIOS Done: HECI2 with Trusted Channel
    3. At OS Runtime: HECI2 with Trusted Channel and Command Queue

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

  The source code contained or described herein and all documents related to the
  source code ("Material") are owned by Intel Corporation or its suppliers or
  licensors. Title to the Material remains with Intel Corporation or its suppliers
  and licensors. The Material may contain trade secrets and proprietary and
  confidential information of Intel Corporation and its suppliers and licensors,
  and is protected by worldwide copyright and trade secret laws and treaty
  provisions. No part of the Material may be used, copied, reproduced, modified,
  published, uploaded, posted, transmitted, distributed, or disclosed in any way
  without Intel's prior express written permission.

  No license under any patent, copyright, trade secret or other intellectual
  property right is granted to or conferred upon you by disclosure or delivery
  of the Materials, either expressly, by implication, inducement, estoppel or
  otherwise. Any license under such intellectual property rights must be
  express and approved by Intel in writing.

  Unless otherwise agreed by Intel in writing, you may not remove or alter
  this notice or any other notice embedded in Materials by Intel or
  Intel's suppliers or licensors in any way.

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#include "CseVariableStorageIoSmm.h"

#include <Library/SmmMemLib.h>
#include <Library/PsfLib.h>
#include <MkhiMsgs.h>
#include <CoreBiosMsg.h>

extern CSE_VARIABLE_HECI_DEVICE      CurrentCseVariableHeciDevice;

VOID                                              *mCseCommandQueueRequestBuffer;
VOID                                              *mCseCommandQueueReadBuffer;
CSE_VARIABLE_STORAGE_INDEX_CONTEXT                *mCseIndexQueueWriteBuffer[CSE_VAR_STORAGE_CMD_QUEUE_MAX_TOTAL_REQUESTS];
CSE_VARIABLE_STORAGE_REQUEST                      *mCseCommandQueueWriteBuffer[CSE_VAR_STORAGE_CMD_QUEUE_MAX_TOTAL_REQUESTS];
CSE_VARIABLE_STORAGE_RUNTIME_DATA_BUFFER_ADDRESS  mCseCommandQueueRuntimeDataBufferAddress;
CSE_VARIABLE_STORAGE_SUPPORT_PROTOCOL             *mCseVariableStorageSupportProtocol;
CSE_VARIABLE_STORAGE_PERIODIC_SMI_CONTEXT         mCseVariableStoragePeriodicSmiContext;
EDKII_VARIABLE_STORAGE_SUPPORT_PROTOCOL           *mVariableStorageSupportProtocol;
CIRCULAR_BUFFER                                   mCseCommandQueue = { 0, 0, CSE_VAR_STORAGE_CMD_QUEUE_TOTAL_BUFFER_SIZE, 0, NULL};
EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL         *mSmmPeriodicTimerDispatch2Protocol;
PCH_SMM_PERIODIC_TIMER_CONTROL_PROTOCOL           *mSmmPeriodicTimerControlProtocol;

UINTN   mCseCommandQueueWriteRequestConsumerIndex;
UINTN   mCseCommandQueueWriteRequestProducerIndex;
UINTN   mCseCommandQueueReadBufferSize;
UINTN   mCseCommandQueueWriteBufferSize;
UINTN   *mCseCommandQueueRuntimeDataBufferPtr;
UINTN   mTrustedHeciBarAddress;
UINTN   mGetOsProxyHeciBaseAddress;
UINTN   mGetOsProxyHeciBarAddress;
UINT64  mSmiTickPeriod;

BOOLEAN                        mRequireReadCommandQueue   = FALSE;
BOOLEAN                        mRequireWriteCommandQueue  = FALSE;
BOOLEAN                        mSmramLocked               = FALSE;
BOOLEAN                        mTrustedChannelEnabled     = FALSE;
BOOLEAN                        mAtRuntime                 = FALSE;
HECI_PROTOCOL                  *mHeciProtocol;
HECI_TRUSTED_CHANNEL_PROTOCOL  *mHeciTrustedChannelProtocol = NULL;
BOOLEAN                        mEnableVariableConfigInCseRecoveryMode = FALSE;
/**
  Returns whether asynchronous I/O is required with CSE.

  @retval       TRUE        Asynchronous I/O is required.
  @retval       FALSE       Asynchronous I/O is not required.

**/
BOOLEAN
EFIAPI
CseVariableStorageIsAsyncIoRequired (
  VOID
  )
{
  return (mRequireReadCommandQueue || mRequireWriteCommandQueue);
}

/**
  Locates the HECI protocol and sets the module HECI protocol pointer.

  @retval     EFI_SUCCESS            The HECI protocol was found.
  @retval     EFI_INVALID_PARAMETER  Invalid parameter.
  @retval     EFI_NOT_FOUND          The protocol interface was not found.

**/
EFI_STATUS
EFIAPI
LocateHeciProtocol (
  VOID
  )
{
  EFI_STATUS  Status;

  Status = EFI_SUCCESS;
  if (mHeciProtocol == NULL) {
    Status = gSmst->SmmLocateProtocol (
                      &gHeciProtocolGuid,
                      NULL,
                     (VOID **) &mHeciProtocol
                     );
  }

  return Status;
}

/**
  Determines if fundamental requirements are met to interact using storage proxy messages with CSME.

  @retval     TRUE            Basic requirements are met for a storage proxy transaction.
  @retval     FALSE           The HECI protocol could not be found or the HECI device is not in a normal state.
**/
BOOLEAN
EFIAPI
IsReadyForTransaction (
  VOID
  )
{
  EFI_STATUS    Status;
  UINT32        MeMode;

  Status = LocateHeciProtocol ();
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Could not locate the SMM HECI protocol.\n"));
    ASSERT_EFI_ERROR (Status);
    return FALSE;
  }

  Status = mHeciProtocol->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    DEBUG ((DEBUG_ERROR, "Error getting ME mode or mode is not normal. Status = %r.\n", Status));
    return FALSE;
  }

  if (
    mCseCommandQueueRequestBuffer == NULL ||
    mCseCommandQueueReadBuffer == NULL ||
    mCseCommandQueueWriteBuffer == NULL ||
    mCseCommandQueueRuntimeDataBufferPtr == NULL
    ) {
      return FALSE;
  }

  return TRUE;
}

/**
  Validates the data buffer is initialized properly.

  @retval     TRUE                    The data buffer is initialized to a valid address.
  @retval     FALSE                   The data buffer is not initialized to a valid address.
**/
BOOLEAN
EFIAPI
IsDataBufferValid (
  VOID
  )
{
  if (
    mCseCommandQueueRuntimeDataBufferAddress.AddressLow == 0x0 ||
    mCseCommandQueueRuntimeDataBufferAddress.BufferLength == 0x0 ||
    mCseCommandQueueRuntimeDataBufferPtr == NULL
    ) {
    return FALSE;
  } else if (!IS_ALIGNED ((UINTN) mCseCommandQueueRuntimeDataBufferPtr, EFI_PAGE_SIZE)) {
    return FALSE;
  } else if (
    !SmmIsBufferOutsideSmmValid (
      (UINTN) mCseCommandQueueRuntimeDataBufferPtr,
      mCseCommandQueueRuntimeDataBufferAddress.BufferLength
      )
    ) {
    DEBUG ((DEBUG_ERROR, "The data buffer provided outside SMM is invalid!\n"));
    return FALSE;
  }

  return TRUE;
}

/**
  SMM Ready To Lock event notification handler.

  It sets a flag indicating that SMRAM has been locked.

  @param[in] Protocol   Points to the protocol's unique identifier.
  @param[in] Interface  Points to the interface instance.
  @param[in] Handle     The handle on which the interface was installed.

  @retval EFI_SUCCESS   Notification handler ran successfully.
 **/
EFI_STATUS
EFIAPI
SmmReadyToLockEventNotify (
  IN CONST EFI_GUID  *Protocol,
  IN VOID            *Interface,
  IN EFI_HANDLE      Handle
  )
{
  mSmramLocked = TRUE;
  return EFI_SUCCESS;
}

/**
  SMM Exit Boot Services event notification handler.

  @param[in] Protocol   Points to the protocol's unique identifier.
  @param[in] Interface  Points to the interface instance.
  @param[in] Handle     The handle on which the interface was installed.

  @retval EFI_SUCCESS   Notification handler ran successfully.
 **/
EFI_STATUS
EFIAPI
SmmExitBootServicesEventNotify (
  IN CONST EFI_GUID  *Protocol,
  IN VOID            *Interface,
  IN EFI_HANDLE      Handle
  )
{
  mAtRuntime = TRUE;

  //
  // The Trusted Channel HECI device must be power managed when enabled
  //
  if (!mEnableVariableConfigInCseRecoveryMode) {
    SetHeciIdle(mTrustedHeciBarAddress, mAtRuntime);
  }

  return EFI_SUCCESS;
}

/**
  CSE Variable Storage Support protocol notification handler.

  @param[in] Protocol   Points to the protocol's unique identifier.
  @param[in] Interface  Points to the interface instance.
  @param[in] Handle     The handle on which the interface was installed.

  @retval EFI_SUCCESS   Notification handler ran successfully.
 **/
EFI_STATUS
EFIAPI
CseVariableStorageSupportReadyNotify (
  IN CONST EFI_GUID  *Protocol,
  IN VOID            *Interface,
  IN EFI_HANDLE      Handle
  )
{
  EFI_STATUS  Status;

  Status = gSmst->SmmLocateProtocol (
                    &gCseVariableStorageSupportProtocolGuid,
                    NULL,
                    (VOID **) &mCseVariableStorageSupportProtocol
                    );
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  EDKII Variable Storage Support Protocol notification callback.

  @param   Protocol      Points to the protocol's unique identifier
  @param   Interface     Points to the interface instance
  @param   Handle        The handle on which the interface was installed

  @retval  EFI_SUCCESS   The callback function ran successfully
**/
EFI_STATUS
EFIAPI
VariableStorageSupportProtocolNotify (
  IN CONST EFI_GUID      *Protocol,
  IN VOID                *Interface,
  IN EFI_HANDLE          Handle
  )
{
  EFI_STATUS         Status;

  Status = gSmst->SmmLocateProtocol (
                    &gEdkiiVariableStorageSupportProtocolGuid,
                    NULL,
                    (VOID **) &mVariableStorageSupportProtocol
                    );
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  Returns whether the command queue is enabled for CSE variable read operations.

  @retval     TRUE                        Command queue is enabled for CSE variable read operations.
  @retval     FALSE                       Command queue is disabled for CSE variable read operations.

**/
BOOLEAN
EFIAPI
CseVariableStorageIsReadCommandQueueEnabled (
  VOID
  )
{
  return mRequireReadCommandQueue;
}

/**
  Returns whether the command queue is enabled for CSE variable write operations.

  @retval     TRUE                        Command queue is enabled for CSE variable write operations.
  @retval     FALSE                       Command queue is disabled for CSE variable write operations.

**/
BOOLEAN
EFIAPI
CseVariableStorageIsWriteCommandQueueEnabled (
  VOID
  )
{
  return mRequireWriteCommandQueue;
}

/**
  Disables the command queue for CSE variable read operations.

**/
VOID
EFIAPI
CseVariableStorageDisableReadCommandQueue (
  VOID
  )
{
  mRequireReadCommandQueue = FALSE;
}

/**
  Enables the command queue for CSE variable read operations.

**/
VOID
EFIAPI
CseVariableStorageEnableReadCommandQueue (
  VOID
  )
{
  mRequireReadCommandQueue = TRUE;
}

/**
  Disables the command queue for CSE variable write operations.

**/
VOID
EFIAPI
CseVariableStorageDisableWriteCommandQueue (
  VOID
  )
{
  mRequireWriteCommandQueue = FALSE;
}

/**
  Enables the command queue for CSE variable write operations.

**/
VOID
EFIAPI
CseVariableStorageEnableWriteCommandQueue (
  VOID
  )
{
  mRequireWriteCommandQueue = TRUE;
}

/**
  Initializes a CSE Variable Storage index context structure for a new variable write.

  @param[in]  CseVariableStorageStore          Pointer to a structure that contains CSE variable storage store info.
  @param[in]  VariableStoreInfo                Pointer to a structure that maintains variable store information.
  @param[out] IndexContext                     Pointer to the index context structure to initialize.
  @param[out] IndexVariableStoreHeader         Pointer to an index area variable store header buffer.

  @retval     EFI_SUCCESS                      The variable write operation was successful.
  @retval     EFI_UNSUPPORTED                  CSE variable index context initialization is not supported.
  @retval     EFI_INVALID_PARAMETER            A required pointer is set to NULL.
**/
EFI_STATUS
EFIAPI
CseVariableStorageInitializeNewVariableContext (
  IN  CONST  CSE_VARIABLE_STORAGE_STORE   *CseVariableStorageStore,
  IN  VARIABLE_NVM_STORE_INFO             *VariableStoreInfo,
  OUT CSE_VARIABLE_STORAGE_INDEX_CONTEXT  *IndexContext,
  OUT VARIABLE_NVM_STORE_HEADER           **IndexVariableStoreHeader
  )
{
  CSE_VARIABLE_STORAGE_INDEX_CONTEXT  *LastIndexContext = NULL;

  if (CseVariableStorageStore == NULL || VariableStoreInfo == NULL || IndexContext == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Determine the latest variable store header
  //
  LastIndexContext =  CseVariableStorageGetLastIndexQueueEntry (
                        CseVariableStorageStore->Info.Type,
                        mCseIndexQueueWriteBuffer,
                        mCseCommandQueueWriteRequestProducerIndex,
                        TRUE,
                        TRUE,
                        TRUE
                        );
  if (LastIndexContext != NULL) {
    *IndexVariableStoreHeader = &(LastIndexContext->VariableStoreHeader);
  } else {
    *IndexVariableStoreHeader = VariableStoreInfo->VariableStoreHeader;
  }

  ZeroMem (IndexContext, sizeof (CSE_VARIABLE_STORAGE_INDEX_CONTEXT));
  IndexContext->VariableStoreIndexPtr = VariableStoreInfo->VariableStoreHeader;
  IndexContext->VariableHeaderIndexPtr =  (AUTHENTICATED_VARIABLE_NVM_HEADER *) NVM_HEADER_ALIGN (
                                            (UINTN) IndexContext->VariableStoreIndexPtr +
                                            sizeof (VARIABLE_NVM_STORE_HEADER) +
                                            (*IndexVariableStoreHeader)->VariableHeaderTotalLength
                                            );
  IndexContext->AuthFlag = VariableStoreInfo->AuthFlag;
  IndexContext->CseVariableStore = CseVariableStorageStore;

  return EFI_SUCCESS;
}

/**
  Gets a tick period to use for CSE variable storage periodic SMI handlers.

  @retval    EFI_SUCCESS           The periodic timer interval was found successfully.
  @retval    EFI_NOT_FOUND         A valid periodic timer interval could not be found.
  @retval    EFI_NOT_READY         An instance of the EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL was not found.
  @retval    EFI_OUT_OF_RESOURCES  Insufficient resources to allocate a buffer for a periodic timer interval table.
**/
EFI_STATUS
EFIAPI
FindPeriodicTimerInterval (
  VOID
  )
{
  EFI_STATUS  Status;
  UINTN       Count               = 0;
  UINT64      *SmiTickInterval    = NULL;
  UINT64      *SmiTickPeriodTable = NULL;

  if (mSmmPeriodicTimerDispatch2Protocol == NULL) {
    return EFI_NOT_READY;
  }

  //
  // Count the number of periodic SMI tick intervals that the SMM Periodic Timer
  // Dipatch 2 Protocol supports.
  //
  do {
    Status = mSmmPeriodicTimerDispatch2Protocol->GetNextShorterInterval (
                                                   mSmmPeriodicTimerDispatch2Protocol,
                                                   &SmiTickInterval
                                                   );
    ASSERT_EFI_ERROR (Status);
    Count++;
  } while (SmiTickInterval != NULL);

  //
  // Allocate a buffer for the table of supported periodic SMI tick periods.
  //
  SmiTickPeriodTable = AllocateZeroPool (Count * sizeof (UINT64));
  if (SmiTickPeriodTable == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Fill in the table of supported periodic SMI tick periods.
  //
  SmiTickInterval = NULL;
  Count = 0;
  do {
    SmiTickPeriodTable[Count] = 0;
    Status = mSmmPeriodicTimerDispatch2Protocol->GetNextShorterInterval (
                                                   mSmmPeriodicTimerDispatch2Protocol,
                                                   &SmiTickInterval
                                                   );
    ASSERT_EFI_ERROR (Status);
    if (SmiTickInterval != NULL) {
      SmiTickPeriodTable[Count] = *SmiTickInterval;
    }
    Count++;
  } while (SmiTickInterval != NULL);

  //
  // Finds the next period less than 128ms
  // Note: The table is sorted largest to smallest and terminated by zero
  // Note: The table values are in 100ns units
  //
  for (Count = 0; SmiTickPeriodTable[Count] > 0; Count++) {
    if (SmiTickPeriodTable[Count] < 1280000) {
      mSmiTickPeriod = SmiTickPeriodTable[Count];
      FreePool (SmiTickPeriodTable);
      return EFI_SUCCESS;
    }
  }

  //
  // Should never reach here
  //
  DEBUG ((DEBUG_ERROR, "A valid periodic tick period was not found.\n"));

  FreePool (SmiTickPeriodTable);

  return EFI_NOT_FOUND;
}

/**
  Register the CSE Variable Storage periodic SMI handler.

  @retval EFI_SUCCESS       The periodic SMI handler was registered successfully.
  @retval EFI_NOT_READY     An instance of both EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL and
                            PCH_SMM_PERIODIC_TIMER_CONTROL_PROTOCOL were not installed yet.
  @retval EFI_DEVICE_ERROR  A valid SMI periodic tick period was not found.
  @retval Others            An error occurred registering the SMI handler.
**/
EFI_STATUS
EFIAPI
RegisterVariablePeriodicSmiHandler (
  VOID
  )
{
  EFI_STATUS  Status;

  if (mSmmPeriodicTimerDispatch2Protocol == NULL || mSmmPeriodicTimerControlProtocol == NULL) {
    return EFI_NOT_READY;
  }

  Status = FindPeriodicTimerInterval ();
  if (EFI_ERROR (Status)) {
    return Status;
  } else if (mSmiTickPeriod == 0) {
    return EFI_DEVICE_ERROR;
  }

  DEBUG ((
    DEBUG_INFO,
    "Registering CSE variable storage SMM CMD Queue handler.\nPeriodic tick period = %dms.\n\n",
    (mSmiTickPeriod / PERIODIC_TIMER_TICKS_PER_MS)
    ));

  mCseVariableStoragePeriodicSmiContext.RegisterContext.Period          = mSmiTickPeriod * PERIODIC_TIMER_CALL_PERIOD;
  mCseVariableStoragePeriodicSmiContext.RegisterContext.SmiTickInterval = mSmiTickPeriod;

  Status = mSmmPeriodicTimerDispatch2Protocol->Register (
                                                 mSmmPeriodicTimerDispatch2Protocol,
                                                 CseVariableStorageCommandQueuePeriodicSmiHandler,
                                                 &(mCseVariableStoragePeriodicSmiContext.RegisterContext),
                                                 &(mCseVariableStoragePeriodicSmiContext.DispatchHandle)
                                                 );
  if (!EFI_ERROR (Status)) {
    Status = mSmmPeriodicTimerControlProtocol->Pause (
                                                 mSmmPeriodicTimerControlProtocol,
                                                 mCseVariableStoragePeriodicSmiContext.DispatchHandle
                                                 );
  }
  ASSERT_EFI_ERROR (Status);
  if (!EFI_ERROR (Status)) {
    mVariableStorageSupportProtocol->NotifyWriteServiceReady ();
  }

  return Status;
}

/**
  SMM Periodic Timer Dispatch protocol notification handler.

  @param[in] Protocol   Points to the protocol's unique identifier.
  @param[in] Interface  Points to the interface instance.
  @param[in] Handle     The handle on which the interface was installed.

  @retval EFI_SUCCESS   Notification handler ran successfully.
**/
EFI_STATUS
EFIAPI
SmmPeriodicTimerDispatch2Notify (
  IN CONST EFI_GUID  *Protocol,
  IN VOID            *Interface,
  IN EFI_HANDLE      Handle
  )
{
  EFI_STATUS  Status;

  Status = gSmst->SmmLocateProtocol (
                    &gEfiSmmPeriodicTimerDispatch2ProtocolGuid,
                    NULL,
                    (VOID **) &mSmmPeriodicTimerDispatch2Protocol
                    );
  ASSERT_EFI_ERROR (Status);

  Status = RegisterVariablePeriodicSmiHandler ();
  ASSERT (Status == EFI_SUCCESS || Status == EFI_NOT_READY);

  return EFI_SUCCESS;
}

/**
  PCH SMM Periodic Timer Control protocol notification handler.

  @param[in] Protocol   Points to the protocol's unique identifier.
  @param[in] Interface  Points to the interface instance.
  @param[in] Handle     The handle on which the interface was installed.

  @retval EFI_SUCCESS   Notification handler ran successfully.
**/
EFI_STATUS
EFIAPI
SmmPeriodicTimerControlNotify (
  IN CONST EFI_GUID  *Protocol,
  IN VOID            *Interface,
  IN EFI_HANDLE      Handle
  )
{
  EFI_STATUS  Status;

  Status = gSmst->SmmLocateProtocol (
                    &gPchSmmPeriodicTimerControlGuid,
                    NULL,
                    (VOID **) &mSmmPeriodicTimerControlProtocol
                    );
  ASSERT_EFI_ERROR (Status);

  Status = RegisterVariablePeriodicSmiHandler ();
  ASSERT (Status == EFI_SUCCESS || Status == EFI_NOT_READY);

  return EFI_SUCCESS;
}

/**
  The SMM CSE Variable Storage IO Library constructor.

  @param[in]  ImageHandle       The firmware allocated handle for the UEFI image.
  @param[in]  SystemTable       A pointer to the EFI system table.

  @retval     EFI_SUCCESS       The function always return EFI_SUCCESS for now.
                                It will ASSERT on error for debug version.
**/
EFI_STATUS
EFIAPI
SmmCseVariableStorageIoLibConstructor (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS    Status;
  VOID          *Registration;
  EFI_HANDLE    SmiHandle    = NULL;

  if (!PcdGetBool (PcdEnableCseVariableStorage) || PcdGetBool (PcdNvVariableEmulationMode)) {
    DEBUG ((DEBUG_INFO, "CSE variable storage IO functionality is disabled due to variable configuration.\n"));
    return EFI_SUCCESS;
  }
  mEnableVariableConfigInCseRecoveryMode = PcdGetBool(PcdEnableVariableConfigInCseRecoveryMode);
  Status = InitializeCommandQueueBuffers ();
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Register the SMI Handler Used for Runtime DXE Command Queue Support
  //
  Status = gSmst->SmiHandlerRegister (
                    SmmCseVariableStorageHandler,
                    &gCseVariableStorageProtocolInstanceGuid,
                    &SmiHandle
                    );
  ASSERT_EFI_ERROR (Status);

  //
  // Locate the Trusted Channel Protocol (Signs and Verifies Messages)
  //
  if (!mEnableVariableConfigInCseRecoveryMode) {
    Status = gSmst->SmmLocateProtocol (
                      &gHeciTrustedChannelProtocolGuid,
                      NULL,
                      (VOID **) &mHeciTrustedChannelProtocol
                      );
    ASSERT_EFI_ERROR (Status);
  }
  //
  // Register SMM Ready To Lock Protocol notification
  //
  Status = gSmst->SmmRegisterProtocolNotify (
                    &gEfiSmmReadyToLockProtocolGuid,
                    SmmReadyToLockEventNotify,
                    &Registration
                    );
  ASSERT_EFI_ERROR (Status);

  //
  // Register for Exit Boot Services notification
  //
  Status = gSmst->SmmRegisterProtocolNotify (
                    &gEdkiiSmmExitBootServicesProtocolGuid,
                    SmmExitBootServicesEventNotify,
                    &Registration
                    );
  ASSERT_EFI_ERROR (Status);

  //
  // Register EDKII Variable Storage Support notification
  //
  Status = gSmst->SmmRegisterProtocolNotify (
                    &gEdkiiVariableStorageSupportProtocolGuid,
                    VariableStorageSupportProtocolNotify,
                    &Registration
                    );
  ASSERT_EFI_ERROR (Status);

  //
  // Register SMM Periodic Timer Dispatch Protocol notification
  //
  Status = gSmst->SmmRegisterProtocolNotify (
                    &gEfiSmmPeriodicTimerDispatch2ProtocolGuid,
                    SmmPeriodicTimerDispatch2Notify,
                    &Registration
                    );
  ASSERT_EFI_ERROR (Status);

  //
  // Register SMM Periodic Timer Control Protocol notification
  //
  Status = gSmst->SmmRegisterProtocolNotify (
                    &gPchSmmPeriodicTimerControlGuid,
                    SmmPeriodicTimerControlNotify,
                    &Registration
                    );
  ASSERT_EFI_ERROR (Status);

  //
  // Register CSE Variable Storage Support Protocol notification
  //
  Status = gSmst->SmmRegisterProtocolNotify (
                    &gCseVariableStorageSupportProtocolGuid,
                    CseVariableStorageSupportReadyNotify,
                    &Registration
                    );
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}
