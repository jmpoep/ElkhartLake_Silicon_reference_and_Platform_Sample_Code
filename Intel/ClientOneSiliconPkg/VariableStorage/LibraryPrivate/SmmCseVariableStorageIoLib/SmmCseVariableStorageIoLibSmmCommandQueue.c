/** @file
  SMM CSE Variable Storage IO SMM Command Queue Implementation

  This command queue is only used for variable requests that originate from SMM. In this case, a periodic SMI
  implementation is used that allows the OS proxy stack to be scheduled between variable requests.

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
#include <CoreBiosMsg.h>
#include <CseVariableStorageCommandQueue.h>
#include <Library/CseVariableStorageOsProxyLib.h>

extern CSE_VARIABLE_STORAGE_INDEX_CONTEXT               *mCseIndexQueueWriteBuffer[CSE_VAR_STORAGE_CMD_QUEUE_MAX_TOTAL_REQUESTS];
extern CSE_VARIABLE_STORAGE_REQUEST                     *mCseCommandQueueWriteBuffer[CSE_VAR_STORAGE_CMD_QUEUE_MAX_TOTAL_REQUESTS];
extern CSE_VARIABLE_STORAGE_PERIODIC_SMI_CONTEXT        mCseVariableStoragePeriodicSmiContext;
extern EDKII_VARIABLE_STORAGE_SUPPORT_PROTOCOL          *mVariableStorageSupportProtocol;
extern EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL        *mSmmPeriodicTimerDispatch2Protocol;
extern PCH_SMM_PERIODIC_TIMER_CONTROL_PROTOCOL          *mSmmPeriodicTimerControlProtocol;
extern HECI_PROTOCOL                                    *mHeciProtocol;
extern HECI_TRUSTED_CHANNEL_PROTOCOL                    *mHeciTrustedChannelProtocol;
extern VOID                                             *mCseCommandQueueRequestBuffer;
extern UINTN                                            *mCseCommandQueueRuntimeDataBufferPtr;
extern UINTN                                            mTrustedHeciBarAddress;
extern UINTN                                            mGetOsProxyHeciBaseAddress;
extern CIRCULAR_BUFFER                                  mCseCommandQueue;
extern CSE_VARIABLE_STORAGE_RUNTIME_DATA_BUFFER_ADDRESS mCseCommandQueueRuntimeDataBufferAddress;
extern UINTN                                            mCseCommandQueueWriteRequestConsumerIndex;
extern UINTN                                            mCseCommandQueueWriteRequestProducerIndex;
extern BOOLEAN                                          mAtRuntime;
extern UINT64                                           mSmiTickPeriod;

STATIC
VOID
EFIAPI
PrintBinaryBuffer (
  IN CONST  UINT8*      Buffer,
  IN        UINTN       BufferSize
  )
{
  UINTN    CurrentByte = 0;

  if (BufferSize == 0) {
    return;
  }

  DEBUG ((DEBUG_INFO, "  Base  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n"));
  DEBUG ((DEBUG_INFO, "  %4d %2x ", CurrentByte / 16, Buffer[0]));

  for (CurrentByte = 1; CurrentByte < BufferSize; CurrentByte++) {
    if ((CurrentByte % 16) == 0) {
      DEBUG ((DEBUG_INFO, "\n  %4d %2x ", CurrentByte / 16, Buffer[CurrentByte]));
    } else {
      DEBUG ((DEBUG_INFO, "%2x ", Buffer[CurrentByte]));
    }
  }
  DEBUG ((DEBUG_INFO, "\n"));
  return;
}

/**
  An SMI handler for CSE variable storage periodic SMI command queue operations.

  @param[in]      DispatchHandle  The unique handle assigned to this handler by SmiHandlerRegister().
  @param[in]      Context         Points to an optional handler context which was specified when the
                                  handler was registered.
  @param[in,out]  CommBuffer      A pointer to a collection of data in memory that will
                                  be conveyed from a non-SMM environment into an SMM environment.
  @param[in,out]  CommBufferSize  The size of the CommBuffer.

  @retval EFI_SUCCESS                         The interrupt was handled and quiesced. No other handlers
                                              should still be called.
  @retval EFI_WARN_INTERRUPT_SOURCE_QUIESCED  The interrupt has been quiesced but other handlers should
                                              still be called.
  @retval EFI_WARN_INTERRUPT_SOURCE_PENDING   The interrupt is still pending and other handlers should still
                                              be called.
  @retval EFI_INTERRUPT_PENDING               The interrupt could not be quiesced.
**/
EFI_STATUS
EFIAPI
CseVariableStorageCommandQueuePeriodicSmiHandler (
  IN       EFI_HANDLE  DispatchHandle,
  IN CONST VOID        *Context         OPTIONAL,
  IN OUT   VOID        *CommBuffer      OPTIONAL,
  IN OUT   UINTN       *CommBufferSize  OPTIONAL
  )
{
  EFI_STATUS  Status;

  UINTN            CurrentCommandAdvancementOffset;
  UINT32           CurrentResponseReceiveLength;
  VOID             *RtDxeDataBuffer;
  HECI_PROXY_STATE CurrentHeciOsProxyState;
  SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_VERIFY_RESPONSE *RtDxeVerifyResponse;

  STATIC UINT32 CommandRequestHeaderSize;
  STATIC UINT32 CommandResponseHeaderSize;

  STATIC BIOS_STORAGE_TYPE  CurrentMessageBiosStorageType;
  STATIC HECI_DEVICE        CurrentMessageHeciDevice;

  STATIC UINTN              CurrentCommandIndex;
  STATIC UINTN              CurrentCommandVerificationDataSize;
  STATIC UINT8              CurrentHeciMessageAddress;
  STATIC UINT32             CurrentPeriodicSmiEntryCount;
  STATIC BOOLEAN            IsCurrentCommandWrite;

  STATIC CSE_VAR_BIOS_STORAGE_REQUEST  *CurrentRequest;

  Status = EFI_SUCCESS;
  DEBUG ((DEBUG_INFO, "CSE variable storage periodic SMI entry count = %d.\n", CurrentPeriodicSmiEntryCount));
  if (CurrentPeriodicSmiEntryCount == 0) {
    DEBUG ((DEBUG_INFO, "Beginning SMM command queue dispatch for %d commands.\n", mCseCommandQueue.Count));
    CurrentRequest = mCseCommandQueueRequestBuffer;
    ZeroMem (mCseCommandQueueRuntimeDataBufferPtr, mCseCommandQueueRuntimeDataBufferAddress.BufferLength);
    SetHeciActive (mTrustedHeciBarAddress, mAtRuntime);
  }
  CurrentPeriodicSmiEntryCount++;

  if (mAtRuntime) {
    Status = CseVariableStorageReadOsProxyState (mGetOsProxyHeciBaseAddress, &CurrentHeciOsProxyState);
    if (EFI_ERROR (Status) || CurrentHeciOsProxyState != HeciProxyStatePresent) {
      if (
        ((CSE_VARIABLE_MAX_PROXY_WAIT_SECS * 1000) / ((mSmiTickPeriod / PERIODIC_TIMER_TICKS_PER_MS) * PERIODIC_TIMER_CALL_PERIOD)) <
        CurrentPeriodicSmiEntryCount
        ) {
          // A warning is returned because the OS proxy driver was not available when SetVariable ()
          // was called. This is a workaround to allow operations such as Windows installation to succeed
          // as a WinPE compatible OS proxy driver stack currently does not exist.
          DEBUG ((DEBUG_INFO, "Returning a warning that the OS proxy is not available.\n"));
          Status = EFI_WARN_OS_DRIVER_NOT_PRESENT;
          goto Exit;
      } else {
        DEBUG ((
          DEBUG_INFO,
          "The OS proxy is not ready, waiting %dms to try again.",
          (mSmiTickPeriod / PERIODIC_TIMER_TICKS_PER_MS)
          ));
        return EFI_SUCCESS;
      }
    }
  }
  if (CurrentCommandIndex < mCseCommandQueue.Count) {
    if (!mCseVariableStoragePeriodicSmiContext.WaitingForReceive) {
      DEBUG ((DEBUG_INFO, "Dispatching command number %d\n", CurrentCommandIndex));

      if (CurrentRequest == NULL) {
        DEBUG ((DEBUG_ERROR, "A request header is NULL. Command queue dispatch cannot continue.\n"));
        Status = EFI_ABORTED;
        goto Exit;
      }
      CurrentMessageBiosStorageType = CurrentRequest->Type;

      if (CurrentMessageBiosStorageType == BiosStorageUntrusted) {
        CommandRequestHeaderSize = sizeof (BIOS_STORAGE_REQUEST);
        CommandResponseHeaderSize = sizeof (BIOS_STORAGE_RESPONSE);
        CurrentMessageHeciDevice = CSE_VARIABLE_STORAGE_CMD_QUEUE_UNTRUSTED_HECI_DEVICE;
        CurrentHeciMessageAddress = HECI_MCHI_MESSAGE_ADDR;

        switch (CurrentRequest->Buffer.Message.MkhiHeader.Fields.Command) {
          case BIOS_STORAGE_READ_CMD:
            DEBUG ((DEBUG_INFO, "Current command is: Read\n"));
            IsCurrentCommandWrite = FALSE;
            break;
          case BIOS_STORAGE_WRITE_CMD:
            DEBUG ((DEBUG_INFO, "Current command is: Write\n"));
            if (mCseCommandQueueWriteRequestConsumerIndex >= mCseCommandQueueWriteRequestProducerIndex) {
              DEBUG ((DEBUG_ERROR, "The consumer index exceeds producer index in write queue.\n"));
              Status = EFI_OUT_OF_RESOURCES;
              goto Exit;
            }
            // Copy the data from the SMM write buffer to the runtime data buffer
            CopyMem (
              (VOID *) ((UINT8 *) mCseCommandQueueRuntimeDataBufferPtr + EFI_PAGE_SIZE),
              (VOID *) &(mCseCommandQueueWriteBuffer[mCseCommandQueueWriteRequestConsumerIndex]->Data[0]),
              (UINTN) CurrentRequest->Buffer.Message.Body.Length
              );
            IsCurrentCommandWrite = TRUE;
            mCseCommandQueueWriteRequestConsumerIndex++;
            break;
          default:
            DEBUG ((DEBUG_ERROR, "Invalid command in the command queue.\n"));
            Status = EFI_ABORTED;
            goto Exit;
        }
        DEBUG ((DEBUG_INFO, "Current Command Data Size: %d bytes.\n", CurrentRequest->Buffer.Message.Body.Length));
      } else if (CurrentMessageBiosStorageType == BiosStorageTrusted) {
        CommandRequestHeaderSize = sizeof (BIOS_STORAGE_TRUSTED_CHANNEL_REQUEST);
        CommandResponseHeaderSize = sizeof (BIOS_STORAGE_TRUSTED_CHANNEL_RESPONSE);
        CurrentMessageHeciDevice = CSE_VARIABLE_STORAGE_CMD_QUEUE_TRUSTED_HECI_DEVICE;
        CurrentHeciMessageAddress = HECI_BIOS_STORAGE_MESSAGE_ADDR;

        switch (CurrentRequest->Buffer.TrustedChannelMessage.Header.TrustedHeader.Command.Id) {
          case BIOS_STORAGE_READ_CMD_TRUSTED_CHANNEL:
            DEBUG ((DEBUG_INFO, "Current command is: Trusted Channel Read\n"));
            CurrentCommandVerificationDataSize = CurrentRequest->Buffer.TrustedChannelMessage.Body.Length;
            IsCurrentCommandWrite = FALSE;
            break;
          case BIOS_STORAGE_WRITE_CMD_TRUSTED_CHANNEL:
            DEBUG ((DEBUG_INFO, "Current command is: Trusted Channel Write\n"));
            CurrentCommandVerificationDataSize = 0;

            if (mCseCommandQueueWriteRequestConsumerIndex >= mCseCommandQueueWriteRequestProducerIndex) {
              DEBUG ((DEBUG_ERROR, "The consumer index exceeds producer index in write queue.\n"));
              Status = EFI_OUT_OF_RESOURCES;
              goto Exit;
            }

            // Copy the data from the SMM write buffer to the runtime data buffer
            CopyMem (
              (VOID *) ((UINT8 *) mCseCommandQueueRuntimeDataBufferPtr + EFI_PAGE_SIZE),
              (VOID *) &(mCseCommandQueueWriteBuffer[mCseCommandQueueWriteRequestConsumerIndex]->Data[0]),
              (UINTN) CurrentRequest->Buffer.TrustedChannelMessage.Body.Length
              );
            IsCurrentCommandWrite = TRUE;
            mCseCommandQueueWriteRequestConsumerIndex++;
            break;
          default:
            DEBUG ((DEBUG_ERROR, "Invalid command in the command queue.\n"));
            Status = EFI_ABORTED;
            goto Exit;
        }
        DEBUG ((
          DEBUG_INFO,
          "Current Command Data Size: %d bytes.\n",
          CurrentRequest->Buffer.TrustedChannelMessage.Body.Length
          ));
        DEBUG ((
          DEBUG_INFO,
          "Current Command Monotonic Count: %d\n",
          CurrentRequest->Buffer.TrustedChannelMessage.Header.TrustedHeader.MonotonicCounter
          ));
      } else {
        DEBUG ((DEBUG_ERROR, "Invalid command in the command queue.\n"));
      }

      Status = mHeciProtocol->SendMsg (
                                CurrentMessageHeciDevice,
                                (UINT32 *) CurrentRequest,
                                CommandRequestHeaderSize,
                                BIOS_FIXED_HOST_ADDR,
                                CurrentHeciMessageAddress
                                );
      if (EFI_ERROR (Status)) {
        DEBUG ((
          DEBUG_ERROR,
          "An error occurred sending the HECI command queue message, aborting. Status = %r.\n",
          Status
          ));
        goto Exit;
      }
      mCseVariableStoragePeriodicSmiContext.WaitingForReceive = TRUE;
      return EFI_SUCCESS;
    } else {
      CurrentResponseReceiveLength = (UINT32) CommandResponseHeaderSize;
      RtDxeDataBuffer = (VOID *) ((UINT8 *) mCseCommandQueueRuntimeDataBufferPtr + EFI_PAGE_SIZE);

      RtDxeVerifyResponse = (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_VERIFY_RESPONSE *) (
                              ((UINT8 *) RtDxeDataBuffer) - sizeof (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_VERIFY_RESPONSE)
                              );

      Status = mHeciProtocol->ReadMsg (
                                CurrentMessageHeciDevice,
                                NON_BLOCKING,
                                (
                                  (CurrentMessageBiosStorageType == BiosStorageUntrusted) ?
                                  (UINT32 *) RtDxeDataBuffer :
                                  (UINT32 *) &(RtDxeVerifyResponse->ResponseMessage)
                                  ),
                                &CurrentResponseReceiveLength
                                );
      if (Status == EFI_TIMEOUT || Status == EFI_NO_RESPONSE) {
        if (
          ((CSE_VARIABLE_CMD_QUEUE_WAIT_SECS * 1000) / ((mSmiTickPeriod / PERIODIC_TIMER_TICKS_PER_MS) * PERIODIC_TIMER_CALL_PERIOD)) <
          CurrentPeriodicSmiEntryCount
          ) {
          Status = EFI_NO_RESPONSE;
          goto Exit;
        }
        // Exit the handler to try to receive again in the next periodic entry
        return EFI_SUCCESS;
      } else if (EFI_ERROR (Status)) {
        DEBUG ((
          DEBUG_ERROR,
          "An error occurred in HECI response, aborting current HECI command queue sequence. Status = %r.\n",
          Status
          ));
        goto Exit;
      }
      if (CurrentMessageBiosStorageType == BiosStorageUntrusted) {
        if (((BIOS_STORAGE_RESPONSE *) RtDxeDataBuffer)->MkhiHeader.Fields.Result != MkhiStatusSuccess) {
          DEBUG ((DEBUG_ERROR, "The message response indicates an error.\n"));
          DEBUG ((DEBUG_ERROR, "Status: 0x%x\n", ((BIOS_STORAGE_RESPONSE *) RtDxeDataBuffer)->MkhiHeader.Fields.Result));
          Status = EFI_DEVICE_ERROR;
          goto Exit;
        }
      } else if (CurrentMessageBiosStorageType == BiosStorageTrusted) {
        if (RtDxeVerifyResponse->ResponseMessage.Header.Status != BIOS_STORAGE_STATUS_SUCCESS) {
          DEBUG ((DEBUG_ERROR, "The message response indicates an error.\n"));
          DEBUG ((DEBUG_ERROR, "Status = 0x%x\n", RtDxeVerifyResponse->ResponseMessage.Header.Status));
          Status = EFI_DEVICE_ERROR;
          goto Exit;
        }

        DEBUG ((DEBUG_INFO, "Sending response for verification...\n"));
        RtDxeVerifyResponse->IsLastCommand = (BOOLEAN) (CurrentCommandIndex == (mCseCommandQueue.Count - 1));
        RtDxeVerifyResponse->DataSize = CurrentCommandVerificationDataSize;
        Status  = VerifyCommandResponseData (RtDxeVerifyResponse);
        ZeroMem (mCseCommandQueueRuntimeDataBufferPtr, mCseCommandQueueRuntimeDataBufferAddress.BufferLength);
        if (EFI_ERROR (Status)) {
          DEBUG ((DEBUG_ERROR, "Message verification failed.\n"));
          goto Exit;
        }
      }
      if (IsCurrentCommandWrite && mCseIndexQueueWriteBuffer[mCseCommandQueueWriteRequestConsumerIndex - 1] != NULL) {
        Status = CseVariableStorageIoUpdateIndexArea (
                  mCseIndexQueueWriteBuffer[mCseCommandQueueWriteRequestConsumerIndex - 1]
                  );
        if (EFI_ERROR (Status)) {
          DEBUG ((DEBUG_ERROR, "Updating the index area from context failed.\n"));
          goto Exit;
        }
      }
      mCseVariableStoragePeriodicSmiContext.WaitingForReceive = FALSE;

      DEBUG ((DEBUG_INFO, "Completed periodic SMI command %d.\n", CurrentCommandIndex));

      //
      // Move to the next command (all commands in the queue are requests)
      // Command headers must be DWORD aligned
      //
      CurrentCommandAdvancementOffset = (UINTN) (VOID *) CurrentRequest;
      CurrentCommandAdvancementOffset +=  sizeof (CSE_VAR_BIOS_STORAGE_REQUEST);
      CurrentCommandAdvancementOffset +=  (UINTN) CSE_VAR_STORAGE_CMD_QUEUE_GET_PAD_SIZE (
                                                    sizeof (CSE_VAR_BIOS_STORAGE_REQUEST)
                                                    );
      CurrentRequest = (CSE_VAR_BIOS_STORAGE_REQUEST *) CurrentCommandAdvancementOffset;
      CurrentCommandIndex++;
    }
    if ((BOOLEAN) (CurrentCommandIndex < mCseCommandQueue.Count)) {
      DEBUG ((
        DEBUG_INFO,
        "%d CSE variable storage commands remaining in periodic SMI queue.\n",
        (mCseCommandQueue.Count - CurrentCommandIndex)
        ));
      return EFI_SUCCESS;
    }
  }

Exit:
  SetHeciIdle (mTrustedHeciBarAddress, mAtRuntime);

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "An error occurred in CSE variable storage periodic SMI. Status = %r.\n", Status));
    ASSERT_EFI_ERROR (Status);
  }
  if (CurrentMessageBiosStorageType == BiosStorageTrusted) {
    Status = mHeciTrustedChannelProtocol->DecrementMonotonicCount (
                                            (UINT32)GetRemainingTrustedChannelMessages (
                                            CurrentRequest,
                                            (mCseCommandQueue.Count - CurrentCommandIndex)
                                            )
                                            );
    ASSERT_EFI_ERROR(Status);
  }

  //
  // Clean up static state for the next periodic SMI sequence
  //
  CircularBufferReset (&mCseCommandQueue);
  ResetWriteRequestDataBuffer ();
  ZeroMem (mCseCommandQueueRuntimeDataBufferPtr, mCseCommandQueueRuntimeDataBufferAddress.BufferLength);

  CurrentCommandIndex                 = 0;
  CurrentCommandVerificationDataSize  = 0;
  CurrentPeriodicSmiEntryCount        = 0;
  CurrentRequest                      = NULL;

  if (mSmmPeriodicTimerControlProtocol != NULL) {
    Status = mSmmPeriodicTimerControlProtocol->Pause (
                                                 mSmmPeriodicTimerControlProtocol,
                                                 mCseVariableStoragePeriodicSmiContext.DispatchHandle
                                                 );
  } else {
    Status = EFI_NOT_FOUND;
  }
  DEBUG ((DEBUG_INFO, "CSE variable storage SMM command queue dispatch complete - Pause Status = %r.\n", Status));
  ASSERT_EFI_ERROR (Status);

  if (mVariableStorageSupportProtocol != NULL) {
    mVariableStorageSupportProtocol->NotifySmmIoComplete (&gCseVariableStorageProtocolInstanceGuid, Status);
  } else {
    DEBUG ((
      DEBUG_ERROR,
      "Failed to locate EDKII variable storage support protocol. Cannot notify the variable driver.\n"
      ));
    ASSERT (FALSE);
  }

  return EFI_SUCCESS;
}

/**
  Starts dispatching all queued CSE variable storage messages from SMM.

  @retval     EFI_SUCCESS                 The command queue was enabled successfully.
  @retval     EFI_UNSUPPORTED             The CSE variable storage SMM command queue is not supported at this time.
  @retval     EFI_NOT_READY               The required interfaces are not available for communication at this time.
  @retval     Others                      An error occurred enabling the command queue.

**/
EFI_STATUS
EFIAPI
CseVariableStorageStartSmmCommandQueue (
  VOID
  )
{
  if (mCseCommandQueue.Count == 0) {
    return EFI_SUCCESS;
  } else if (
    mCseCommandQueueRequestBuffer == NULL ||
    mSmmPeriodicTimerDispatch2Protocol == NULL ||
    mSmmPeriodicTimerControlProtocol == NULL ||
    mHeciProtocol == NULL
    ) {
    return EFI_NOT_READY;
  } else if (mSmiTickPeriod == 0) {
    DEBUG ((DEBUG_ERROR, "The periodic SMI tick period is invalid. Cannot register the CSE variable periodic SMI.\n"));
    return EFI_NOT_READY;
  } else if (mCseCommandQueue.Count > CSE_VAR_STORAGE_CMD_QUEUE_MAX_TOTAL_REQUESTS) {
    return EFI_OUT_OF_RESOURCES;
  }

  mCseVariableStoragePeriodicSmiContext.WaitingForReceive = FALSE;

  DEBUG ((DEBUG_INFO, "Resuming the variable storage periodic SMI handler...\n"));
  return mSmmPeriodicTimerControlProtocol->Resume (
                                             mSmmPeriodicTimerControlProtocol,
                                             mCseVariableStoragePeriodicSmiContext.DispatchHandle
                                             );
}