/** @file
  This file defines the Variable Storage Command Queue module.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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

#include "CseCommandQueueRuntimeDxe.h"

#include <CoreBiosMsg.h>
#include <Register/HeciRegs.h>
#include <Register/MeRegs.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/IoLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/TimerLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiRuntimeLib.h>
#include <Library/CseVariableStorageOsProxyLib.h>
#include <Library/HeciPowerManagementLib.h>
#include <Library/DxeMeLib.h>
#include <HeciContextLib.h>

HECI_PROTOCOL                   *mHeciProtocol;
EFI_SMM_COMMUNICATION_PROTOCOL  *mSmmCommunicationProtocol;

//
// Holds all pending request messages from the SMM command queue.
//
VOID          *mCseVariableStorageRequestMessageBuffer;
STATIC VOID   *mCseVariableStorageRequestMessageBufferPhysical;

//
// A buffer outside SMRAM used for communication with CSE.
//  Reads: CSE will DMA into this buffer. SMM will verify data.
//  Writes: CSE will DMA from this buffer. CSE will verify data.
//
VOID          *mCseVariableStorageDataBuffer;
STATIC VOID   *mCseVariableStorageDataBufferPhysical;

//
// Points to the data portion of the data buffer (below SMM communicate headers)
//
VOID          *mCseVariableStorageDataBufferDataPtr;

//
// Points to the SMM communicate header portion of the data buffer (bottom of the first page, top of content)
//
VOID          *mCseVariableStorageDataBufferSmmCommPtr;
STATIC VOID   *mCseVariableStorageDataBufferSmmCommPtrPhysical;

//
// Points to the response header portion of the data buffer (above the data)
//
BIOS_STORAGE_RESPONSE_BUFFER *mCseVariableStorageResponseBufferPtr;

//
// A buffer used to send SMM communicate messages with no payload.
//
VOID          *mCseVariableStorageNoPayloadCommBuffer;
STATIC VOID   *mCseVariableStorageNoPayloadCommBufferPhysical;

//
// A buffer reserved for debug communication with SMM.
//
VOID          *mCseVariableStorageDebugBuffer;
STATIC VOID   *mCseVariableStorageDebugBufferPhysical;

STATIC UINTN  mCseVariableStorageRequestMessageBufferSize;
STATIC UINTN  mCseVariableStorageActualDataBufferSmmCommunicateBufferSize;
STATIC UINTN  mCseVariableStorageDataBufferSize;
STATIC UINTN  mCseVariableStorageNoPayloadCommBufferSize;
STATIC UINTN  mCseVariableStorageDebugBufferSize;

UINTN mGetOsProxyHeciBaseAddress;
UINTN mGetOsProxyHeciBarAddress;
UINTN mTrustedHeciBaseAddress;
UINTN mTrustedHeciBarAddress;

STATIC BOOLEAN mCseVariableStorageBiosProxyTerminated     = FALSE;
STATIC BOOLEAN mCseVariableStorageTrustedChannelEnabled   = FALSE;
BOOLEAN mCseVariableStorageSentDataBufferAddress          = FALSE;

EFI_LOCK  mCseVariableStorageLock;

/**
  Initialize the communicate buffer using DataSize and Function.

  The communicate size is: SMM_COMMUNICATE_HEADER_SIZE + SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_HEADER_SIZE + DataSize.

  @param[out]    DataPtr                     Points to the data in the communicate buffer.
  @param[in,out] CommBuffer                  A pointer to the communicate buffer.
  @param[in]     CommBufferSize              The size of the communicate buffer.
  @param[in]     DataSize                    The data size to send to SMM.
  @param[in]     Function                    The function number used to initialize the communicate header.

  @retval        EFI_SUCCESS                 The communicate buffer was initialized successfully.
  @retval        EFI_BUFFER_TOO_SMALL        The communicate buffer is too small for the given data size.
  @retval        EFI_INVALID_PARAMETER       The DataSize given is too large or CommBuffer is NULL.

**/
EFI_STATUS
EFIAPI
InitCommunicateBuffer (
  OUT            VOID                        **DataPtr OPTIONAL,
  IN  OUT        UINT8                       *CommBuffer,
  IN             UINTN                       CommBufferSize,
  IN             UINTN                       DataSize,
  IN             UINTN                       Function
  )
{
  EFI_SMM_COMMUNICATE_HEADER                  *SmmCommunicateHeader;
  SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_HEADER *SmmCseVariableStorageFunctionHeader;

  if (CommBuffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  if (SMM_CSE_VAR_STORAGE_GET_TOTAL_COMM_BUFFER_SIZE (DataSize) > CommBufferSize) {
    return EFI_BUFFER_TOO_SMALL;
  }

  SmmCommunicateHeader = (EFI_SMM_COMMUNICATE_HEADER *) CommBuffer;
  CopyGuid (&SmmCommunicateHeader->HeaderGuid, &gCseVariableStorageProtocolInstanceGuid);
  SmmCommunicateHeader->MessageLength =  SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_HEADER_SIZE + DataSize;

  SmmCseVariableStorageFunctionHeader = (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_HEADER *) SmmCommunicateHeader->Data;
  SmmCseVariableStorageFunctionHeader->Function     = Function;
  SmmCseVariableStorageFunctionHeader->ReturnStatus = EFI_SUCCESS;
  if (DataPtr != NULL) {
    *DataPtr = SmmCseVariableStorageFunctionHeader->Data;
  }

  return EFI_SUCCESS;
}

/**
  Send the data in the communicate buffer to SMM.

  @param[in,out] CommBuffer                  A pointer to the SMM communicate buffer.
  @param[in,out] CommBufferPhysical          A pointer to the physical SMM communicate buffer.
  @param[in]     DataSize                    This size of the function header and data.

  @retval        EFI_SUCCESS                 The SMI handler returned EFI_SUCCESS.
  @retval        Others                      A failure was returned from the SMI handler.

**/
EFI_STATUS
EFIAPI
SendCommunicateBuffer (
  IN OUT         VOID                        *CommBuffer,
  IN OUT         VOID                        *CommBufferPhysical,
  IN             UINTN                       DataSize
  )
{
  EFI_STATUS                                   Status;
  UINTN                                        CommSize;
  EFI_SMM_COMMUNICATE_HEADER                   *SmmCommunicateHeader;
  SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_HEADER  *SmmCseVariableStorageFunctionHeader;

  CommSize = SMM_CSE_VAR_STORAGE_GET_TOTAL_COMM_BUFFER_SIZE (DataSize);
  Status = mSmmCommunicationProtocol->Communicate (mSmmCommunicationProtocol, CommBufferPhysical, &CommSize);

  SmmCommunicateHeader                = (EFI_SMM_COMMUNICATE_HEADER *) CommBuffer;
  SmmCseVariableStorageFunctionHeader = (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_HEADER *) SmmCommunicateHeader->Data;

  return SmmCseVariableStorageFunctionHeader->ReturnStatus;
}

/**
  Sends a debug message to SMM.

  @param[in] DebugMessageString          A pointer to a debug message string.
  @param[in] DebugMessageData            A pointer to a data buffer that should be printed.
  @param[in] DebugMessageDataLength      The length in bytes of the data buffer.

  @retval    EFI_SUCCESS                 The debug message was communicated successfully.
  @retval    Others                      A failure occurred sending the debug message.

**/
STATIC
EFI_STATUS
EFIAPI
RuntimeDebugMessage (
  IN    CHAR8     *DebugMessageString,
  IN    UINT8     *DebugMessageData,      OPTIONAL
  IN    UINTN     DebugMessageDataLength  OPTIONAL
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;

  DEBUG_CODE_BEGIN();

  SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_DEBUG_MSG  *SmmDebugMsg = NULL;
  UINTN PayloadSize;

  if (DebugMessageString == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  PayloadSize = sizeof (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_DEBUG_MSG);

  Status = InitCommunicateBuffer (
             (VOID **) &SmmDebugMsg,
             mCseVariableStorageDebugBuffer,
             mCseVariableStorageDebugBufferSize,
             PayloadSize,
             SMM_CSE_VARIABLE_STORAGE_FUNCTION_DEBUG_MESSAGE
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (SmmDebugMsg == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  CopyMem ((VOID *) &SmmDebugMsg->DebugMsg[0], (VOID *) DebugMessageString, AsciiStrSize (DebugMessageString));
  SmmDebugMsg->Length = (UINT8) AsciiStrSize (DebugMessageString);

  if (DebugMessageData != NULL) {
    CopyMem (
      (VOID *) &SmmDebugMsg->Data[0],
      (VOID *) DebugMessageData,
      MIN (sizeof (SmmDebugMsg->Data), DebugMessageDataLength)
      );
    SmmDebugMsg->Datalength = (UINT8) MIN (sizeof (SmmDebugMsg->Data), DebugMessageDataLength);
  } else {
    SmmDebugMsg->Datalength = 0;
  }
  Status = SendCommunicateBuffer (
             mCseVariableStorageDebugBuffer,
             mCseVariableStorageDebugBufferPhysical,
             PayloadSize
             );

  DEBUG_CODE_END();

  return Status;
}

/**
  This function sends a communicate buffer with no payload.

  @retval   EFI_SUCCESS       The function was communicated to SMM successfully.
  @retval   Others            An error occurred during communication with SMM.

**/
EFI_STATUS
EFIAPI
SendNoPayloadCommunicateBuffer (
  IN  UINTN                   Function
  )
{
  EFI_STATUS  Status;

  ZeroMem (mCseVariableStorageNoPayloadCommBuffer, mCseVariableStorageNoPayloadCommBufferSize);
  Status = InitCommunicateBuffer (
             NULL,
             mCseVariableStorageNoPayloadCommBuffer,
             mCseVariableStorageNoPayloadCommBufferSize,
             0,
             Function
             );
  if (EFI_ERROR (Status)) {
    RuntimeDebugMessage ("Failed to initialize the no payload function.\n", (UINT8 *) &Function, sizeof (UINTN));
    return Status;
  }

  Status = SendCommunicateBuffer (
             mCseVariableStorageNoPayloadCommBuffer,
             mCseVariableStorageNoPayloadCommBufferPhysical,
             0
             );
  if (EFI_ERROR (Status)) {
    RuntimeDebugMessage ("Failed to send the no payload function.\n", (UINT8 *) &Function, sizeof (UINTN));
  }

  return Status;
}

/**
  Sends the Runtime DXE data buffer address to SMM.

  SMM will use this address to build storage request messages.

  @retval        EFI_SUCCESS                 The data buffer was communicated to SMM successfully.
  @retval        Others                      An error occurred communicating the buffer to SMM.
**/
EFI_STATUS
EFIAPI
CseVariableStorageSendDataBufferAddress (
  VOID
  )
{
  EFI_STATUS                                            Status;
  UINTN                                                 CommunicateSize;
  VOID                                                  *CommunicateBuffer                    = NULL;
  EFI_SMM_COMMUNICATE_HEADER                            *SmmCommunicateHeader                 = NULL;
  SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_SET_DATA_BUFFER  *SetDataBuffer                        = NULL;
  SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_HEADER           *SmmCseVariableStorageFunctionHeader  = NULL;

  CommunicateSize = SMM_CSE_VAR_STORAGE_GET_TOTAL_COMM_BUFFER_SIZE (
                      sizeof (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_SET_DATA_BUFFER)
                      );
  //
  // Reuse the request message buffer
  //
  if (mCseVariableStorageRequestMessageBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  } else if (mCseVariableStorageDataBufferSize < SMM_CSE_VAR_STORAGE_GET_TOTAL_COMM_BUFFER_SIZE (0)) {
    return EFI_INVALID_PARAMETER;
  }
  ZeroMem (mCseVariableStorageRequestMessageBuffer, mCseVariableStorageRequestMessageBufferSize);
  CommunicateBuffer = mCseVariableStorageRequestMessageBuffer;
  SmmCommunicateHeader = (EFI_SMM_COMMUNICATE_HEADER *) CommunicateBuffer;

  Status = InitCommunicateBuffer (
             (VOID **) &SetDataBuffer,
             CommunicateBuffer,
             CommunicateSize,
             sizeof (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_SET_DATA_BUFFER),
             SMM_CSE_VARIABLE_STORAGE_FUNCTION_SET_DATA_BUFFER
             );
  if (EFI_ERROR (Status)) {
    return Status;
  } else if (SetDataBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  SetDataBuffer->DataBufferAddressHigh = (UINT32) RShiftU64 ((UINTN) mCseVariableStorageDataBuffer, 32);
  SetDataBuffer->DataBufferAddressLow = (UINT32) (UINTN) mCseVariableStorageDataBuffer;
  SetDataBuffer->BufferLength = mCseVariableStorageDataBufferSize -
                                  SMM_CSE_VAR_STORAGE_GET_TOTAL_COMM_BUFFER_SIZE (0);
  //
  // Send the communicate data to SMM
  //
  Status = mSmmCommunicationProtocol->Communicate (
                                        mSmmCommunicationProtocol,
                                        mCseVariableStorageRequestMessageBufferPhysical,
                                        &CommunicateSize
                                        );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  SmmCseVariableStorageFunctionHeader = (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_HEADER *) SmmCommunicateHeader->Data;
  Status = SmmCseVariableStorageFunctionHeader->ReturnStatus;

  return Status;
}

/**
  Notifies SMM that a Trusted Channel transaction failed.

  The remaining messages in the queue (if any) cannot be sent since the monotonic counter used to
  compute the HMAC is invalid.

  @param[in]     MessageCount                The number of remaining messages in the queue when the failure occurred.

  @retval        EFI_SUCCESS                 The notification was successfully sent.
  @retval        EFI_OUT_OF_RESOURCES        The SMM communicate buffer is too small or the buffer is NULL.
  @retval        Others                      An error occurred attempting to send the notification.

**/
EFI_STATUS
EFIAPI
SendTrustedChannelCommunicationFailure (
  IN    UINTN    MessageCount
  )
{
  EFI_STATUS                  Status;
  UINTN                       CommunicateSize;
  VOID                        *CommunicateBuffer      = NULL;
  EFI_SMM_COMMUNICATE_HEADER  *SmmCommunicateHeader   = NULL;
  SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_TRUSTED_CHANNEL_COMM_FAILURE *TrustedChannelCommFailure = NULL;

  CommunicateSize = SMM_CSE_VAR_STORAGE_GET_TOTAL_COMM_BUFFER_SIZE (
                      sizeof (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_TRUSTED_CHANNEL_COMM_FAILURE)
                      );

  //
  // Reuse the request message buffer
  //
  if (mCseVariableStorageRequestMessageBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  } else if (mCseVariableStorageDataBufferSize < SMM_CSE_VAR_STORAGE_GET_TOTAL_COMM_BUFFER_SIZE (0)) {
    return EFI_INVALID_PARAMETER;
  }
  RuntimeDebugMessage (
    "Sending Trusted Channel failure notification. Messages remaining:\n",
    (UINT8 *) &MessageCount,
    sizeof (UINTN)
    );

  ZeroMem (mCseVariableStorageRequestMessageBuffer, mCseVariableStorageRequestMessageBufferSize);
  CommunicateBuffer = mCseVariableStorageRequestMessageBuffer;
  SmmCommunicateHeader = (EFI_SMM_COMMUNICATE_HEADER *) CommunicateBuffer;

  Status = InitCommunicateBuffer (
             (VOID **) &TrustedChannelCommFailure,
             CommunicateBuffer,
             CommunicateSize,
             sizeof (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_TRUSTED_CHANNEL_COMM_FAILURE),
             SMM_CSE_VARIABLE_STORAGE_FUNCTION_TRUSTED_CHANNEL_COMM_FAILURE
             );
  if (EFI_ERROR (Status)) {
    return Status;
  } else if (TrustedChannelCommFailure == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  TrustedChannelCommFailure->MessagesRemaining = MessageCount;

  //
  // Send the communicate data to SMM
  //
  Status = mSmmCommunicationProtocol->Communicate (
                                        mSmmCommunicationProtocol,
                                        mCseVariableStorageRequestMessageBufferPhysical,
                                        &CommunicateSize
                                        );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return ((SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_HEADER *) SmmCommunicateHeader->Data)->ReturnStatus;
}

/**
  Gets the number of Trusted Channel messages remaining in the command queue.

  @param[in]     CommandQueueBuffer          A pointer to a buffer of request messages.
  @param[in]     RemainingMessages           The number of messages remaining in the buffer given.

  @retval        The number of Trusted Channel messages remaining in the request buffer given.

**/
UINTN
EFIAPI
GetRemainingTrustedChannelMessages (
  IN  CSE_VAR_BIOS_STORAGE_REQUEST  *CommandQueueBuffer,
  IN  UINTN                         RemainingMessages
  )
{
  BIOS_STORAGE_TYPE             CurrentMessageBiosStorageType;
  UINTN                         CurrentCommandAdvancementOffset = 0;
  UINTN                         CurrentCommandCount             = 0;
  UINTN                         TrustedChannelMessageCount      = 0;
  CSE_VAR_BIOS_STORAGE_REQUEST  *CurrentRequest                 = CommandQueueBuffer;

  if (RemainingMessages == 0) {
    return 0;
  }

  for (CurrentCommandCount = 0; CurrentCommandCount < RemainingMessages; CurrentCommandCount++) {
    if (CurrentRequest == NULL) {
      return TrustedChannelMessageCount;
    }

    CurrentMessageBiosStorageType = CurrentRequest->Type;
    if (CurrentMessageBiosStorageType == BiosStorageTrusted) {
      TrustedChannelMessageCount++;
    }

    CurrentCommandAdvancementOffset = (UINTN) (VOID *) CurrentRequest;
    CurrentCommandAdvancementOffset +=  sizeof (CSE_VAR_BIOS_STORAGE_REQUEST);
    CurrentCommandAdvancementOffset +=  (UINTN) CSE_VAR_STORAGE_CMD_QUEUE_GET_PAD_SIZE (
                                                  sizeof (CSE_VAR_BIOS_STORAGE_REQUEST)
                                                  );
    CurrentRequest = (CSE_VAR_BIOS_STORAGE_REQUEST *) CurrentCommandAdvancementOffset;
  }

  return TrustedChannelMessageCount;
}

/**
  Notifies SMM that it must switch to the trusted channel for BIOS storage messages.

  The command queue is only needed and compatible with trusted channel messages. Therefore, the command
  queue should be used after this notification.

  @param[in]  Event        Event whose notification function is being invoked.
  @param[in]  Context      Pointer to the notification function's context.

**/
VOID
EFIAPI
SwitchToTrustedChannelEvent (
  IN EFI_EVENT             Event,
  IN VOID                  *Context
  )
{
  EFI_STATUS  Status;

  if (mCseVariableStorageTrustedChannelEnabled) {
    return;
  }

  if (CSE_VARIABLE_STORAGE_CMD_QUEUE_UNTRUSTED_HECI_DEVICE != CSE_VARIABLE_STORAGE_CMD_QUEUE_TRUSTED_HECI_DEVICE) {
    DEBUG ((DEBUG_INFO, "Initializing the trusted channel HECI device since it varies from the untrusted device.\n"));

    DEBUG ((DEBUG_INFO, "Resetting the trusted channel HECI device...\n"));
    Status = mHeciProtocol->ResetHeci (CSE_VARIABLE_STORAGE_CMD_QUEUE_TRUSTED_HECI_DEVICE);
    DEBUG ((DEBUG_INFO, "HECI reset status = %r.\n", Status));
    Status = mHeciProtocol->InitHeci (CSE_VARIABLE_STORAGE_CMD_QUEUE_TRUSTED_HECI_DEVICE);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Error initializing trusted channel HECI device. Status = %r.\n", Status));
      DEBUG ((DEBUG_ERROR, "Could not switch to the trusted channel.\n"));
      ASSERT_EFI_ERROR (Status);
      return;
    }
  }

  mCseVariableStorageTrustedChannelEnabled = TRUE;
  RuntimeDebugMessage ("BIOS storage trusted channel enabled.\n", NULL, 0);

  Status = SendNoPayloadCommunicateBuffer (SMM_CSE_VARIABLE_STORAGE_FUNCTION_TRUSTED_CHANNEL_ENABLE);
  ASSERT_EFI_ERROR (Status);

  return;
}

/**
  Notification function for the BIOS Proxy Terminated event.

  @param[in]  Event        Event whose notification function is being invoked.
  @param[in]  Context      Pointer to the notification function's context.

**/
VOID
EFIAPI
BiosProxyTerminatedEvent (
  IN EFI_EVENT             Event,
  IN VOID                  *Context
  )
{
  EFI_STATUS Status;

  DEBUG ((DEBUG_INFO, "BIOS storage proxy terminated.\n"));
  mCseVariableStorageBiosProxyTerminated = TRUE;
  DEBUG ((DEBUG_INFO, "CSE variable storage is switching to HECI Runtime DXE protocol.\n"));
  Status = gBS->LocateProtocol (&gHeciRuntimeProtocolGuid, NULL, (VOID **) &mHeciProtocol);
  if (EFI_ERROR (Status)) {
    ASSERT_EFI_ERROR (Status);
  }
}

/**
  Notification function for the Variable Write Architecture protocol installed event.

  @param[in]  Event        Event whose notification function is being invoked.
  @param[in]  Context      Pointer to the notification function's context.

**/
VOID
EFIAPI
VariableWriteArchitectureEvent (
  IN EFI_EVENT             Event,
  IN VOID                  *Context
  )
{
  EFI_STATUS   Status;

  Status = SendNoPayloadCommunicateBuffer (SMM_CSE_VARIABLE_STORAGE_FUNCTION_REQUIRE_READ_COMMAND_QUEUE);
  ASSERT_EFI_ERROR (Status);
}

/**
  Sends the Trusted Channel device information to SMM.

  @param[in]     TrustedHeciBarAddress       The BAR address of the HECI Trusted Channel device.

  @retval        EFI_SUCCESS                 The data was successfully sent.
  @retval        EFI_OUT_OF_RESOURCES        The SMM communicate buffer is too small or the buffer is NULL.
  @retval        Others                      An error occurred attempting to send the data.

**/
EFI_STATUS
EFIAPI
SendTrustedChannelDeviceInfo (
  IN    UINTN    TrustedHeciBarAddress
  )
{
  EFI_STATUS                  Status;
  UINTN                       CommunicateSize;
  VOID                        *CommunicateBuffer      = NULL;
  EFI_SMM_COMMUNICATE_HEADER  *SmmCommunicateHeader   = NULL;
  SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_TRUSTED_CHANNEL_DEVICE_INFO *TrustedChannelDeviceInfo = NULL;

  CommunicateSize = SMM_CSE_VAR_STORAGE_GET_TOTAL_COMM_BUFFER_SIZE (
                      sizeof (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_TRUSTED_CHANNEL_DEVICE_INFO)
                      );

  //
  // Reuse the request message buffer
  //
  if (mCseVariableStorageRequestMessageBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  } else if (mCseVariableStorageDataBufferSize < SMM_CSE_VAR_STORAGE_GET_TOTAL_COMM_BUFFER_SIZE (0)) {
    return EFI_INVALID_PARAMETER;
  }
  RuntimeDebugMessage ("Sending the Trusted Channel BAR.\n", (UINT8 *) &TrustedHeciBarAddress, sizeof (UINTN));

  ZeroMem (mCseVariableStorageRequestMessageBuffer, mCseVariableStorageRequestMessageBufferSize);
  CommunicateBuffer = mCseVariableStorageRequestMessageBuffer;
  SmmCommunicateHeader = (EFI_SMM_COMMUNICATE_HEADER *) CommunicateBuffer;

  Status = InitCommunicateBuffer (
             (VOID **) &TrustedChannelDeviceInfo,
             CommunicateBuffer,
             CommunicateSize,
             sizeof (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_TRUSTED_CHANNEL_DEVICE_INFO),
             SMM_CSE_VARIABLE_STORAGE_FUNCTION_TRUSTED_CHANNEL_DEVICE_INFO
             );
  if (EFI_ERROR (Status)) {
    return Status;
  } else if (TrustedChannelDeviceInfo == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  TrustedChannelDeviceInfo->HeciTrustedDeviceBar = TrustedHeciBarAddress;

  //
  // Send the communicate data to SMM
  //
  Status = mSmmCommunicationProtocol->Communicate (
                                        mSmmCommunicationProtocol,
                                        mCseVariableStorageRequestMessageBufferPhysical,
                                        &CommunicateSize
                                        );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return ((SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_HEADER *) SmmCommunicateHeader->Data)->ReturnStatus;
}

/**
  Sends the OS Proxy HECI device information to SMM.

  @param[in]     OsProxyHeciBaseAddress      The base address of the OS Proxy HECI device.
  @param[in]     OsProxyHeciBar              The BAR address of the OS Proxy HECI device.

  @retval        EFI_SUCCESS                 The data was successfully sent.
  @retval        EFI_OUT_OF_RESOURCES        The SMM communicate buffer is too small or the buffer is NULL.
  @retval        Others                      An error occurred attempting to send the data.

**/
EFI_STATUS
EFIAPI
SendOsProxyInfo (
  IN    UINTN    OsProxyHeciBaseAddress,
  IN    UINTN    OsProxyHeciBar
  )
{
  EFI_STATUS                                                Status;
  UINTN                                                     CommunicateSize;
  VOID                                                      *CommunicateBuffer    = NULL;
  EFI_SMM_COMMUNICATE_HEADER                                *SmmCommunicateHeader = NULL;
  SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_OS_PROXY_DEVICE_INFO *OsProxyDeviceInfo    = NULL;

  CommunicateSize = SMM_CSE_VAR_STORAGE_GET_TOTAL_COMM_BUFFER_SIZE (
                      sizeof (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_OS_PROXY_DEVICE_INFO)
                      );

  //
  // Reuse the request message buffer
  //
  if (mCseVariableStorageRequestMessageBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  } else if (mCseVariableStorageDataBufferSize < SMM_CSE_VAR_STORAGE_GET_TOTAL_COMM_BUFFER_SIZE (0)) {
    return EFI_INVALID_PARAMETER;
  }
  RuntimeDebugMessage ("Sending the OS Proxy base address to SMM.\n", (UINT8 *) &OsProxyHeciBaseAddress, sizeof (UINTN));
  RuntimeDebugMessage ("Sending the OS Proxy BAR address to SMM.\n", (UINT8 *) &OsProxyHeciBar, sizeof (UINTN));

  ZeroMem (mCseVariableStorageRequestMessageBuffer, mCseVariableStorageRequestMessageBufferSize);
  CommunicateBuffer = mCseVariableStorageRequestMessageBuffer;
  SmmCommunicateHeader = (EFI_SMM_COMMUNICATE_HEADER *) CommunicateBuffer;

  Status = InitCommunicateBuffer (
             (VOID **) &OsProxyDeviceInfo,
             CommunicateBuffer,
             CommunicateSize,
             sizeof (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_OS_PROXY_DEVICE_INFO),
             SMM_CSE_VARIABLE_STORAGE_FUNCTION_OS_PROXY_DEVICE_INFO
             );
  if (EFI_ERROR (Status)) {
    return Status;
  } else if (OsProxyDeviceInfo == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  OsProxyDeviceInfo->OsProxyHeciBaseAddress = OsProxyHeciBaseAddress;
  OsProxyDeviceInfo->OsProxyHeciBar         = OsProxyHeciBar;

  //
  // Send the communicate data to SMM
  //
  Status = mSmmCommunicationProtocol->Communicate (
                                        mSmmCommunicationProtocol,
                                        mCseVariableStorageRequestMessageBufferPhysical,
                                        &CommunicateSize
                                        );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return ((SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_HEADER *) SmmCommunicateHeader->Data)->ReturnStatus;
}

/**
  Initializes Get Proxy HECI device memory attributes for usage at runtime.

  @param[out]     HeciBaseAddress     HECI device PCI configuration space base address.
  @param[out]     HeciBarAddress      HECI device PCI BAR address.
  @param[in]      HeciDevice          The HECI device.

  @retval         EFI_SUCCESS         The device is available and the memory attributes were updated.
  @retval         EFI_DEVICE_ERROR    The PCI device is currently not available.
  @retval         Others              An error occurred updating the memory attributes.

**/
EFI_STATUS
EFIAPI
InitializeHeciRuntimeMemoryAttributes (
  OUT  UINTN         *HeciBaseAddress,
  OUT  UINTN         *HeciBarAddress,
  IN   HECI_DEVICE   HeciDevice
  )
{
  EFI_STATUS                          Status;
  UINT64                              HeciSegmentBaseAddress;
  UINTN                               HeciBarAddressLocal;
  UINT64                              HeciBarLength;
  UINT64                              HeciBaseLength;
  EFI_GCD_MEMORY_SPACE_DESCRIPTOR     GcdDescriptor;
  UINT32                              Buffer[2];

  HeciSegmentBaseAddress = 0;
  HeciBarAddressLocal    = 0;
  HeciBarLength          = SIZE_4KB;
  HeciBaseLength         = SIZE_4KB;

  DEBUG ((DEBUG_INFO, "Setting OS Storage Proxy HECI device memory attributes.\n"));
  HeciSegmentBaseAddress =  PCI_SEGMENT_LIB_ADDRESS (
                              ME_SEGMENT,
                              ME_BUS,
                              ME_DEVICE_NUMBER,
                              HECI_FUNCTION_NUMBER + HeciDevice,
                              0
                              );
  *HeciBaseAddress = HeciSegmentBaseAddress + (UINTN) PcdGet64 (PcdPciExpressBaseAddress);

  if (PciSegmentRead16 (HeciSegmentBaseAddress + PCI_DEVICE_ID_OFFSET) != 0xFFFF) {
    Buffer[0] = PciSegmentRead32 (HeciSegmentBaseAddress + PCI_BASE_ADDRESSREG_OFFSET) & 0xFFFFFFF0;
    Buffer[1] = 0x0;
    if ((PciSegmentRead32 (HeciSegmentBaseAddress + PCI_BASE_ADDRESSREG_OFFSET) & 0x6) == 0x4) {
      Buffer[1] = PciSegmentRead32 (HeciSegmentBaseAddress + (PCI_BASE_ADDRESSREG_OFFSET + 4));
    }

    if (!((Buffer[0] == 0x0 && Buffer[1] == 0x0) || Buffer[0] == 0xFFFFFFFF)) {
      ///
      /// Enable HECI BME and MSE
      ///
      PciSegmentOr8 (HeciSegmentBaseAddress + PCI_COMMAND_OFFSET, (EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER));
      HeciBarAddressLocal = *((UINTN *) (&Buffer[0]));
    }
  } else {
    HeciBarAddressLocal = GetHeciContextBar0 (HeciDevice);
  }
  if (HeciBarAddressLocal == 0) {
    return EFI_DEVICE_ERROR;
  }
  *HeciBarAddress = HeciBarAddressLocal;

  //
  // Set the EFI_MEMORY_RUNTIME attribute for the HECI BAR MMIO range
  //
  Status = gDS->GetMemorySpaceDescriptor (*HeciBarAddress, &GcdDescriptor);
  if (Status == EFI_NOT_FOUND) {
    DEBUG ((DEBUG_INFO, "Adding HECI BAR descriptor in command queue.\n"));
    Status = gDS->AddMemorySpace (
                    EfiGcdMemoryTypeMemoryMappedIo,
                    *HeciBarAddress,
                    HeciBarLength,
                    0
                    );
    if (!EFI_ERROR (Status)) {
      Status = gDS->GetMemorySpaceDescriptor (*HeciBarAddress, &GcdDescriptor);
    }
  }
  if (EFI_ERROR (Status)) {
    return Status;
  }
  Status = gDS->SetMemorySpaceAttributes (
                  *HeciBarAddress,
                  HeciBarLength,
                  GcdDescriptor.Attributes | EFI_MEMORY_RUNTIME
                  );

  //
  // Set the EFI_MEMORY_RUNTIME attribute for the HECI PCI CFG MMIO range
  //
  Status = gDS->GetMemorySpaceDescriptor (*HeciBaseAddress, &GcdDescriptor);
  if (Status == EFI_NOT_FOUND) {
    DEBUG ((DEBUG_INFO, "Adding HECI PCI CFG descriptor in command queue.\n"));
    Status = gDS->AddMemorySpace (
                    EfiGcdMemoryTypeMemoryMappedIo,
                    *HeciBaseAddress,
                    HeciBaseLength,
                    0
                    );
    if (!EFI_ERROR (Status)) {
      Status = gDS->GetMemorySpaceDescriptor (*HeciBaseAddress, &GcdDescriptor);
    }
  }
  if (EFI_ERROR (Status)) {
    return Status;
  }
  Status = gDS->SetMemorySpaceAttributes (
                  *HeciBaseAddress,
                  HeciBaseLength,
                  GcdDescriptor.Attributes | EFI_MEMORY_RUNTIME
                  );

  return EFI_SUCCESS;
}

/**
  PCI enumeration complete event handler to configure memory resources in GCD needed at runtime.

  @param[in] Event    Event whose notification function is being invoked.
  @param[in] Context  Pointer to the notification function's context.
**/
VOID
EFIAPI
CseVariableStorageCommandQueuePciEnumerationComplete (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  EFI_STATUS          Status;
  VOID                *Interface;

  Status = gBS->LocateProtocol (
                  &gEfiPciEnumerationCompleteProtocolGuid,
                  NULL,
                  &Interface
                  );
  if (EFI_ERROR (Status)) {
    return;
  }

  Status =  InitializeHeciRuntimeMemoryAttributes (
              &mGetOsProxyHeciBaseAddress,
              &mGetOsProxyHeciBarAddress,
              CSE_VARIABLE_STORAGE_GET_PROXY_HECI_DEVICE
              );
  ASSERT_EFI_ERROR (Status);
  Status =  InitializeHeciRuntimeMemoryAttributes (
              &mTrustedHeciBaseAddress,
              &mTrustedHeciBarAddress,
              CSE_VARIABLE_STORAGE_CMD_QUEUE_TRUSTED_HECI_DEVICE
              );
  ASSERT_EFI_ERROR (Status);

  Status = SendTrustedChannelDeviceInfo (mTrustedHeciBarAddress);
  ASSERT_EFI_ERROR (Status);
  Status = SendOsProxyInfo (mGetOsProxyHeciBaseAddress, mGetOsProxyHeciBarAddress);
  ASSERT_EFI_ERROR (Status);
}

/**
  Requests the next write data buffer from SMM.

  The data is placed into the data buffer.

  @param[in]     CommandResponseDataSize     The size in bytes of the data to request.

  @retval        EFI_SUCCESS                 The write data was retrieved successfully.
  @retval        EFI_OUT_OF_RESOURCES        The communicate buffer is not large enough to hold the communicate data.
  @retval        Others                      An error occurred retrieving the write data.

**/
EFI_STATUS
EFIAPI
CseVariableStorageRequestNextWriteDataBuffer (
  IN    UINTN     DataSize
  )
{
  EFI_STATUS  Status;
  UINTN       CommunicateDataSize;
  SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_GET_NEXT_WRITE_BUFFER *GetNextWriteBuffer = NULL;

  CONST UINTN CommFunctionStructureSize = OFFSET_OF (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_GET_NEXT_WRITE_BUFFER, Data);

  CommunicateDataSize = CommFunctionStructureSize + DataSize;

  RuntimeDebugMessage ("Preparing to request write data from SMM.\n", NULL, 0);
  RuntimeDebugMessage ("  Communicate Data Size:\n", (UINT8 *) &CommunicateDataSize, sizeof (UINTN));
  RuntimeDebugMessage ("  Data Content Size:\n", (UINT8 *) &DataSize, sizeof (UINTN));

  if (
    mCseVariableStorageDataBufferSize <
    SMM_CSE_VAR_STORAGE_GET_TOTAL_COMM_BUFFER_SIZE (CommunicateDataSize)
    ) {
    // The total communicate size exceeds the pre-allocated buffer size
    return EFI_OUT_OF_RESOURCES;
  }

  Status = InitCommunicateBuffer (
             (VOID **) &GetNextWriteBuffer,
             ((UINT8 *) mCseVariableStorageDataBufferSmmCommPtr) - CommFunctionStructureSize,
             mCseVariableStorageActualDataBufferSmmCommunicateBufferSize,
             CommunicateDataSize,
             SMM_CSE_VARIABLE_STORAGE_FUNCTION_GET_NEXT_WRITE_BUFFER
             );
  if (EFI_ERROR (Status)) {
    return Status;
  } else if (GetNextWriteBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  GetNextWriteBuffer->DataSize = DataSize;

  Status = SendCommunicateBuffer (
             mCseVariableStorageDataBufferSmmCommPtr,
             (VOID *) ((UINT8 *) mCseVariableStorageDataBufferSmmCommPtrPhysical - CommFunctionStructureSize),
             CommunicateDataSize
             );

  return Status;
}

/**
  Verifies an HMAC command response from CSE in SMM.

  @param[in]     IsLastCommand               Indicates if the is the final command in the current dispatch sequence.
  @param[in]     CommandResponseDataSize     The size in bytes of the data content being verified.

  @retval        EFI_SUCCESS                 The message was successfully verified.
  @retval        EFI_SECURITY_VIOLATION      The message failed verification.
  @retval        Others                      An error occurred verifying the message.

**/
EFI_STATUS
EFIAPI
VerifyHmacCommandResponse (
  IN    BOOLEAN   IsLastCommand,
  IN    UINTN     CommandResponseDataSize
  )
{
  EFI_STATUS  Status;
  UINTN       CommunicateDataSize;
  SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_VERIFY_RESPONSE *SmmVerifyResponseHeader = NULL;

  CONST UINTN CommFunctionStructureSize = OFFSET_OF (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_VERIFY_RESPONSE, Data);
  CommunicateDataSize = CommFunctionStructureSize + CommandResponseDataSize;

  RuntimeDebugMessage ("Preparing to send Verify HMAC SMI.\n", NULL, 0);
  RuntimeDebugMessage ("  Communicate Data Size:\n", (UINT8 *) &CommunicateDataSize, sizeof (UINTN));
  RuntimeDebugMessage ("  Data Content Size:\n", (UINT8 *) &CommandResponseDataSize, sizeof (UINTN));

  if (
    mCseVariableStorageDataBufferSize <
    SMM_CSE_VAR_STORAGE_GET_TOTAL_COMM_BUFFER_SIZE (CommunicateDataSize)
    ) {
    // The total communicate size exceeds the pre-allocated buffer size
    return EFI_OUT_OF_RESOURCES;
  }

  Status = InitCommunicateBuffer (
             (VOID **) &SmmVerifyResponseHeader,
             ((UINT8 *) mCseVariableStorageDataBufferSmmCommPtr) - CommFunctionStructureSize,
             mCseVariableStorageActualDataBufferSmmCommunicateBufferSize,
             CommunicateDataSize,
             SMM_CSE_VARIABLE_STORAGE_FUNCTION_VERIFY_RESPONSE
             );
  if (EFI_ERROR (Status)) {
    return Status;
  } else if (SmmVerifyResponseHeader == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  SmmVerifyResponseHeader->IsLastCommand = IsLastCommand;
  SmmVerifyResponseHeader->DataSize = CommandResponseDataSize;

  RuntimeDebugMessage (
    "Response header sent for verification:\n",
    (UINT8 *) mCseVariableStorageResponseBufferPtr,
    sizeof (BIOS_STORAGE_RESPONSE_BUFFER)
    );

  Status = SendCommunicateBuffer (
             mCseVariableStorageDataBufferSmmCommPtr,
             (VOID *) ((UINT8 *) mCseVariableStorageDataBufferSmmCommPtrPhysical - CommFunctionStructureSize),
             CommunicateDataSize
             );

  return Status;
}

/**
  Send the data in the data buffer to the EDKII variable cache.

  Note: This must only be called for untrusted messages.

  @param[in]     DataSize                    Size of the data.

  @retval        EFI_SUCCESS                 The data was successfully sent to the variable cache.
  @retval        EFI_OUT_OF_RESOURCES        The SMM communicate buffer is too small or the buffer is NULL.
  @retval        Others                      An error occurred attempting to send the data to the variable cache.

**/
EFI_STATUS
EFIAPI
SendDataToVariableCache (
  IN    UINTN     DataSize
  )
{
  EFI_STATUS  Status;
  UINTN       CommunicateDataSize;
  SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_CACHE_DATA_BUFFER *CacheDataBufferHeader = NULL;

  CONST UINTN CommFunctionStructureSize = OFFSET_OF (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_CACHE_DATA_BUFFER, Data);
  CommunicateDataSize = CommFunctionStructureSize + DataSize;

  RuntimeDebugMessage ("Preparing to send data to the variable cache.\n", NULL, 0);
  RuntimeDebugMessage ("  Data Size:\n", (UINT8 *) &DataSize, sizeof (UINTN));

  if (
    mCseVariableStorageDataBufferSize <
    SMM_CSE_VAR_STORAGE_GET_TOTAL_COMM_BUFFER_SIZE (CommunicateDataSize)
    ) {
    //
    // The total communicate size exceeds the pre-allocated buffer size
    //
    return EFI_OUT_OF_RESOURCES;
  }

  Status = InitCommunicateBuffer (
             (VOID **) &CacheDataBufferHeader,
             ((UINT8 *) mCseVariableStorageDataBufferSmmCommPtr) - CommFunctionStructureSize,
             mCseVariableStorageActualDataBufferSmmCommunicateBufferSize,
             CommunicateDataSize,
             SMM_CSE_VARIABLE_STORAGE_FUNCTION_READ_COMPLETION_IO_DONE
             );
  if (EFI_ERROR (Status)) {
    return Status;
  } else if (CacheDataBufferHeader == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  CacheDataBufferHeader->DataSize = DataSize;

  Status = SendCommunicateBuffer (
             mCseVariableStorageDataBufferSmmCommPtr,
             (VOID *) ((UINT8 *) mCseVariableStorageDataBufferSmmCommPtrPhysical - CommFunctionStructureSize),
             CommunicateDataSize
             );

  return Status;
}

/**
  Dispatches all the commands in the CSE variable storage command queue.

  This function will not return until all commands are dispatched.

  @param[in,out] CommandQueueBuffer          A pointer to a buffer of trusted channel request commands (the command queue).
  @param[in]     CommandQueueCount           The total number of commands in the command queue.

  @retval        EFI_SUCCESS                 The command queue was dispatched successfully.
  @retval        EFI_INVALID_PARAMETER       The command queue buffer pointer is null or the internal buffer is null.
  @retval        EFI_NOT_READY               A required dependency such as the HECI protocol was not available.
  @retval        EFI_DEVICE_ERROR            The HECI command was not recognized.
  @retval        EFI_ABORTED                 An internal error occurred in the command queue and dispatch was aborted.
  @retval        EFI_SECURITY_VIOLATION      The command response data failed HMAC verification.
  @retval        Others                      The command queue could not be dispatched successfully.

**/
EFI_STATUS
EFIAPI
DispatchCommandQueue (
  IN OUT      CSE_VAR_BIOS_STORAGE_REQUEST  *CommandQueueRequest,
  IN          UINTN                         CommandQueueCount
  )
{
  EFI_STATUS  Status;
  EFI_STATUS  Status2;

  UINT32    CommandRequestHeaderSize;
  UINT32    CommandResponseHeaderSize;
  BOOLEAN   IsCurrentCommandWrite;
  UINTN     CurrentCommandAdvancementOffset     = 0;
  UINTN     CurrentCommandDataSize              = 0;
  UINTN     CurrentCommandIndex                 = 0;
  UINT8     CurrentHeciMessageAddress           = 0;
  UINT32    CurrentResponseReceiveLength        = 0;

  BIOS_STORAGE_TYPE             CurrentMessageBiosStorageType;
  EFI_TPL                       OriginalTpl;
  HECI_DEVICE                   CurrentMessageHeciDevice;
  CSE_VAR_BIOS_STORAGE_REQUEST  *CurrentRequest = NULL;

  CONST EFI_TPL                 WaitTpl = TPL_CALLBACK;

  OriginalTpl = 0;
  if (CommandQueueRequest == NULL || CommandQueueCount > CSE_VAR_STORAGE_CMD_QUEUE_MAX_TOTAL_REQUESTS) {
    return EFI_INVALID_PARAMETER;
  }
  if (mHeciProtocol == NULL) {
    return EFI_NOT_READY;
  }
  if (CommandQueueCount == 0) {
    return EFI_SUCCESS;
  }
  RuntimeDebugMessage (
    "Performing command queue dispatch. Total command count:\n",
    (UINT8 *) &CommandQueueCount,
    sizeof (UINTN)
    );

  if (!EfiAtRuntime ()) {
    OriginalTpl = EfiGetCurrentTpl ();
  }

  SetHeciActive (mTrustedHeciBarAddress, EfiAtRuntime ());
  CurrentRequest = CommandQueueRequest;
  for (CurrentCommandIndex = 0; CurrentCommandIndex < CommandQueueCount; CurrentCommandIndex++) {
    RuntimeDebugMessage ("Dispatching command number:\n", (UINT8 *) &CurrentCommandIndex, sizeof (UINTN));

    if (!EfiAtRuntime ()) {
      OriginalTpl = EfiGetCurrentTpl ();
    }

    if (CurrentRequest == NULL) {
      RuntimeDebugMessage ("A request header is NULL. Command queue dispatch cannot continue.\n", NULL, 0);
      Status = EFI_ABORTED;
      goto Exit;
    }
    ZeroMem (mCseVariableStorageDataBuffer, mCseVariableStorageDataBufferSize);

    IsCurrentCommandWrite = FALSE;
    CurrentMessageBiosStorageType = CurrentRequest->Type;
    if (CurrentMessageBiosStorageType == BiosStorageUntrusted) {
      CommandRequestHeaderSize = sizeof (BIOS_STORAGE_REQUEST);
      CommandResponseHeaderSize = sizeof (BIOS_STORAGE_RESPONSE);
      CurrentMessageHeciDevice = CSE_VARIABLE_STORAGE_CMD_QUEUE_UNTRUSTED_HECI_DEVICE;
      CurrentHeciMessageAddress = HECI_MCHI_MESSAGE_ADDR;

      switch (CurrentRequest->Buffer.Message.MkhiHeader.Fields.Command) {
        case BIOS_STORAGE_READ_CMD:
            RuntimeDebugMessage ("Current command is: Read\n", NULL, 0);
            CurrentCommandDataSize = (UINTN) CurrentRequest->Buffer.Message.Body.Length;
          break;
        case BIOS_STORAGE_WRITE_CMD:
            RuntimeDebugMessage ("Current command is: Write\n", NULL, 0);
            Status = CseVariableStorageRequestNextWriteDataBuffer ((UINTN) CurrentRequest->Buffer.Message.Body.Length);
            if (EFI_ERROR (Status)) {
              RuntimeDebugMessage ("An error occurred retrieving write buffer data.\n", NULL, 0);
              goto Exit;
            }
            CurrentCommandDataSize = 0;
            IsCurrentCommandWrite = TRUE;
          break;
        default:
          RuntimeDebugMessage ("Invalid command in the command queue.\n", NULL, 0);
          Status = EFI_DEVICE_ERROR;
          goto Exit;
      }

      RuntimeDebugMessage (
        "Current Command Data Size:\n",
        (UINT8 *) &(CurrentRequest->Buffer.Message.Body.Length),
        sizeof (UINT32)
        );
    } else if (CurrentMessageBiosStorageType == BiosStorageTrusted) {
      CommandRequestHeaderSize = sizeof (BIOS_STORAGE_TRUSTED_CHANNEL_REQUEST);
      CommandResponseHeaderSize = sizeof (BIOS_STORAGE_TRUSTED_CHANNEL_RESPONSE);
      CurrentMessageHeciDevice = CSE_VARIABLE_STORAGE_CMD_QUEUE_TRUSTED_HECI_DEVICE;
      CurrentHeciMessageAddress = HECI_BIOS_STORAGE_MESSAGE_ADDR;

      switch (CurrentRequest->Buffer.TrustedChannelMessage.Header.TrustedHeader.Command.Id) {
        case BIOS_STORAGE_READ_CMD_TRUSTED_CHANNEL:
          RuntimeDebugMessage ("Current command is: Trusted Channel Read\n", NULL, 0);
          CurrentCommandDataSize = CurrentRequest->Buffer.TrustedChannelMessage.Body.Length;
          break;
        case BIOS_STORAGE_WRITE_CMD_TRUSTED_CHANNEL:
          RuntimeDebugMessage ("Current command is: Trusted Channel Write\n", NULL, 0);
          CurrentCommandDataSize = 0;
          Status = CseVariableStorageRequestNextWriteDataBuffer ((UINTN) CurrentRequest->Buffer.TrustedChannelMessage.Body.Length);
          if (EFI_ERROR (Status)) {
            RuntimeDebugMessage ("An error occurred retrieving write buffer data.\n", NULL, 0);
            goto Exit;
          }
          IsCurrentCommandWrite = TRUE;
          break;
        default:
          RuntimeDebugMessage ("Invalid command in the command queue.\n", NULL, 0);
          Status = EFI_DEVICE_ERROR;
          goto Exit;
      }

      RuntimeDebugMessage (
        "Current Command Data Size:\n",
        (UINT8 *) &(CurrentRequest->Buffer.TrustedChannelMessage.Body.Length),
        sizeof (UINT32)
        );
      RuntimeDebugMessage (
        "Current Command Monotonic Count:\n",
        (UINT8 *) &(CurrentRequest->Buffer.TrustedChannelMessage.Header.TrustedHeader.MonotonicCounter),
        sizeof (UINT32)
        );
    } else {
      RuntimeDebugMessage ("The message processed is of an unknown type.\n", NULL, 0);
      Status = EFI_DEVICE_ERROR;
      goto Exit;
    }

    RuntimeDebugMessage ("Command Request Header Size:\n", (UINT8 *) &CommandRequestHeaderSize, sizeof (UINT32));
    RuntimeDebugMessage ("Command Response Header Size:\n", (UINT8 *) &CommandResponseHeaderSize, sizeof (UINT32));

    RuntimeDebugMessage (
      "Current Request Header for Dispatch:\n",
      (UINT8 *) CurrentRequest,
      CommandRequestHeaderSize
      );

    //
    // Adjust TPL to accommodate BIOS storage proxy priority
    //
    if (!EfiAtRuntime () && OriginalTpl > WaitTpl) {
      gBS->RestoreTPL (WaitTpl);
    } else if (!EfiAtRuntime () && OriginalTpl < WaitTpl) {
      gBS->RaiseTPL (WaitTpl);
    }

    Status = mHeciProtocol->SendMsg (
                              CurrentMessageHeciDevice,
                              (UINT32 *) CurrentRequest,
                              CommandRequestHeaderSize,
                              BIOS_FIXED_HOST_ADDR,
                              CurrentHeciMessageAddress
                              );
    //
    // The SMM command queue must be flushed after the first HECI message to ensure the message is not sent again
    // with an invalid monotonic counter value.
    //
    if (EFI_ERROR (SendNoPayloadCommunicateBuffer (SMM_CSE_VARIABLE_STORAGE_FUNCTION_RESET_COMMAND_QUEUE))) {
      RuntimeDebugMessage ("An error occurred resetting the SMM command queue.\n", NULL, 0);
      Status = EFI_OUT_OF_RESOURCES;
      goto Exit;
    }
    if (EFI_ERROR (Status)) {
      RuntimeDebugMessage ("An error occurred. Resetting the SMM command queue.\n", NULL, 0);
      goto Exit;
    }
    RuntimeDebugMessage ("Waiting for the storage command response...\n", NULL, 0);

    ZeroMem ((VOID *) mCseVariableStorageResponseBufferPtr, sizeof (BIOS_STORAGE_RESPONSE_BUFFER));

    CurrentResponseReceiveLength = CommandResponseHeaderSize;
    Status = mHeciProtocol->ReadMsg (
                              CurrentMessageHeciDevice,
                              BLOCKING,
                              (UINT32 *) mCseVariableStorageResponseBufferPtr,
                              &CurrentResponseReceiveLength
                              );

    if (!EfiAtRuntime () && OriginalTpl > WaitTpl) {
      gBS->RaiseTPL (OriginalTpl);
    } else if (!EfiAtRuntime () && OriginalTpl < WaitTpl) {
      gBS->RestoreTPL (OriginalTpl);
    }
    if (EFI_ERROR (Status)) {
      RuntimeDebugMessage ("An error was returned from the HECI protocol getting the read message response.\n", NULL, 0);
      goto Exit;
    }

    if (CurrentMessageBiosStorageType == BiosStorageUntrusted) {
      if (mCseVariableStorageResponseBufferPtr->Message.MkhiHeader.Fields.Result != MkhiStatusSuccess) {
        RuntimeDebugMessage ("The message response indicates an error.\n", NULL, 0);
        Status = EFI_DEVICE_ERROR;
        goto Exit;
      }
      if (CurrentRequest->Buffer.Message.MkhiHeader.Fields.Command == BIOS_STORAGE_READ_CMD) {
        Status = SendDataToVariableCache (CurrentCommandDataSize);
        if (EFI_ERROR (Status)) {
          RuntimeDebugMessage ("An error occurred updating the variable cache.\n", NULL, 0);
          goto Exit;
        }
      }
    } else if (CurrentMessageBiosStorageType == BiosStorageTrusted) {
      if (mCseVariableStorageResponseBufferPtr->TrustedChannelMessage.Header.Status != BIOS_STORAGE_STATUS_SUCCESS) {
        RuntimeDebugMessage ("The message response indicates an error.\n", NULL, 0);
        RuntimeDebugMessage (
          "Status:\n",
          (UINT8 *) &(mCseVariableStorageResponseBufferPtr->TrustedChannelMessage.Header.Status),
          sizeof (UINT8)
          );
        Status = EFI_DEVICE_ERROR;
        goto Exit;
      }

      RuntimeDebugMessage ("Sending response for verification...\n", NULL, 0);
      Status = VerifyHmacCommandResponse (
                 (BOOLEAN) (CurrentCommandIndex == (CommandQueueCount - 1)),
                 CurrentCommandDataSize
                 );
      if (EFI_ERROR (Status)) {
        RuntimeDebugMessage ("Message verification failed.\n", NULL, 0);
        goto Exit;
      }
    }

    if (IsCurrentCommandWrite) {
      Status = SendNoPayloadCommunicateBuffer (SMM_CSE_VARIABLE_STORAGE_FUNCTION_WRITE_COMPLETION_IO_DONE);

      if (EFI_ERROR (Status)) {
        RuntimeDebugMessage ("The write completion IO done message failed.\n", NULL, 0);
      }
    }

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
  }

Exit:
  SetHeciIdle (mTrustedHeciBarAddress, EfiAtRuntime());

  if (EFI_ERROR (Status)) {
    Status2 = SendTrustedChannelCommunicationFailure (
                GetRemainingTrustedChannelMessages (CurrentRequest, (CommandQueueCount - CurrentCommandIndex))
                );
    if (EFI_ERROR (Status2)) {
      RuntimeDebugMessage ("A failure occurred notifying SMM about a Trusted Channel comm failure.\n", NULL, 0);
    }
  }
  Status2 = SendNoPayloadCommunicateBuffer (SMM_CSE_VARIABLE_STORAGE_FUNCTION_RESET_WRITE_COMMAND_QUEUE);
  if (EFI_ERROR (Status2)) {
    RuntimeDebugMessage ("Reseting the write command queue failed.\n", NULL, 0);
  }

  if (!EfiAtRuntime () && (EfiGetCurrentTpl () != OriginalTpl)) {
    if (OriginalTpl > WaitTpl) {
      gBS->RaiseTPL (OriginalTpl);
    } else {
      gBS->RestoreTPL (OriginalTpl);
    }
  }

  return Status;
}

/**
  Gets the command queue from CSE Variable Storage SMM.

  @param[out]    CommandQueueBuffer  A pointer to a buffer of trusted channel storage request commands (the command queue).
  @param[in]     CommandQueueCount   The total number of commands in the command queue.

  @retval        EFI_SUCCESS         The command queue was retrieved successfully.
  @retval        Others              The command queue could not be retrieved successfully.

**/
EFI_STATUS
EFIAPI
GetCommandQueue (
  OUT        CSE_VAR_BIOS_STORAGE_REQUEST **CommandQueueBuffer,
  OUT        UINTN                        *CommandQueueCount
  )
{
  EFI_STATUS  Status;
  SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_GET_COMMAND_QUEUE *SmmGetCommandQueueHeader = NULL;

  RuntimeDebugMessage ("Retrieving the command queue in Runtime DXE...\n", NULL, 0);

  ZeroMem (mCseVariableStorageRequestMessageBuffer, mCseVariableStorageRequestMessageBufferSize);

  Status = InitCommunicateBuffer (
             (VOID **) &SmmGetCommandQueueHeader,
             mCseVariableStorageRequestMessageBuffer,
             mCseVariableStorageRequestMessageBufferSize,
             CSE_VAR_STORAGE_CMD_QUEUE_TOTAL_BUFFER_SIZE,
             SMM_CSE_VARIABLE_STORAGE_FUNCTION_GET_COMMAND_QUEUE
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  if (SmmGetCommandQueueHeader == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  RuntimeDebugMessage ("Triggering SMI to get the command queue.\n", NULL, 0);

  Status = SendCommunicateBuffer (
             mCseVariableStorageRequestMessageBuffer,
             mCseVariableStorageRequestMessageBufferPhysical,
             CSE_VAR_STORAGE_CMD_QUEUE_TOTAL_BUFFER_SIZE
             );
  if (!EFI_ERROR (Status)) {
    *CommandQueueCount  = SmmGetCommandQueueHeader->CommandQueueCount;
    *CommandQueueBuffer = (CSE_VAR_BIOS_STORAGE_REQUEST  *) &SmmGetCommandQueueHeader->CommandQueueDataBuffer[0];
  }

  RuntimeDebugMessage ("Finished retrieving the command queue in Runtime DXE.\n", NULL, 0);

  return Status;
}

/**
  Retrieves a protocol instance-specific GUID.

  Returns a unique GUID per VARIABLE_STORAGE_IO_COMPLETION_PROTOCOL instance.

  @param[in]     This                        A pointer to this protocol instance.
  @param[out]    InstanceGuid                A pointer to an EFI_GUID that is this protocol instance's GUID.

  @retval        EFI_SUCCESS                 The protocol instance GUID was returned successfully.
  @retval        EFI_INVALID_PARAMETER       The InstanceGuid parameter provided was NULL.

**/
EFI_STATUS
EFIAPI
CseVariableStorageIoCompletionGetId (
  IN             EDKII_VARIABLE_STORAGE_IO_COMPLETION_PROTOCOL  *This,
  OUT            EFI_GUID                                       *InstanceGuid
  )
{
  if (InstanceGuid == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  CopyMem ((VOID *) InstanceGuid, (VOID *) &gCseVariableStorageProtocolInstanceGuid, sizeof (EFI_GUID));

  return EFI_SUCCESS;
}

/**
  Returns when the variable storage IO request is finished (the transaction is complete).

  @param[in]     This                        A pointer to this protocol instance.
  @param[in]     SetVariableIoCompletion     TRUE if Complete() is being called to perform I/O for SetVariable
                                             FALSE if Complete() is being called to perform I/O for GetVariable


  @retval        EFI_SUCCESS                 The command status was retrieved successfully.
  @retval        EFI_NOT_FOUND               The CSE OS proxy driver is not available.
  @retval        Others                      An error occurred retrieving the command status.

**/
EFI_STATUS
EFIAPI
CseVariableStorageIoCompletionComplete (
  IN        EDKII_VARIABLE_STORAGE_IO_COMPLETION_PROTOCOL   *This,
  IN        BOOLEAN                                         SetVariableIoCompletion
  )
{
  EFI_STATUS Status;

  HECI_PROXY_STATE              OsProxyState         = HeciProxyStateUnknown;
  CSE_VAR_BIOS_STORAGE_REQUEST  *CommandQueueBuffer  = NULL;
  UINTN                         CommandQueueCount    = 0;
  EFI_TPL                       OriginalTpl = 0;

  if (!EfiAtRuntime ()) {
    OriginalTpl = EfiGetCurrentTpl ();
    if (OriginalTpl > TPL_CALLBACK) {
      gBS->RestoreTPL (TPL_CALLBACK);
    } else {
      gBS->RaiseTPL (TPL_CALLBACK);
    }
    EfiAcquireLock (&mCseVariableStorageLock);
  }

  RuntimeDebugMessage ("CSE command queue is beginning to complete IO.\n", NULL, 0);

  RuntimeDebugMessage ("Getting command queue from SMM...\n", NULL, 0);
  //
  // Get the command queue
  //
  Status = GetCommandQueue (&CommandQueueBuffer, &CommandQueueCount);
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  // The command queue must use the OS proxy when the BIOS proxy terminates for storage interaction.
  if (mCseVariableStorageBiosProxyTerminated) {
    RuntimeDebugMessage ("Waiting for OS proxy availability...\n", NULL, 0);
    Status = CseVariableStorageWaitForOsProxyState (mGetOsProxyHeciBaseAddress, &OsProxyState);
    if (EFI_ERROR (Status) || OsProxyState != HeciProxyStatePresent) {
      RuntimeDebugMessage ("The OS proxy is not ready, exiting CSE variable storage command queue.\n", NULL, 0);
      Status = SendTrustedChannelCommunicationFailure (
                 GetRemainingTrustedChannelMessages (CommandQueueBuffer, CommandQueueCount)
                 );
      if (EFI_ERROR (Status)) {
        RuntimeDebugMessage ("A failure occurred notifying SMM about a Trusted Channel comm failure.\n", NULL, 0);
      }
      if (SetVariableIoCompletion) {
        // A warning is returned because the OS proxy driver was not available when SetVariable ()
        // was called. This is a workaround to allow operations such as Windows installation to succeed
        // as a WinPE compatible OS proxy driver stack currently does not exist.
        RuntimeDebugMessage ("Returning a warning that the OS proxy is not available.\n", NULL, 0);
        Status = EFI_WARN_OS_DRIVER_NOT_PRESENT;
        goto Done;
      } else {
        Status = EFI_NOT_FOUND;
        goto Done;
      }
    }
    RuntimeDebugMessage ("The OS proxy driver is present.\n", NULL, 0);
  }

  // The buffer address may have been sent earlier to share data before the command queue was used.
  if (!mCseVariableStorageSentDataBufferAddress) {
    Status = CseVariableStorageSendDataBufferAddress ();
    if (!EFI_ERROR (Status)) {
      mCseVariableStorageSentDataBufferAddress = TRUE;
    } else {
      goto Done;
    }
    RuntimeDebugMessage ("Data buffer address successfully shared with SMM...\n", NULL, 0);
  }

  //
  // Dispatch the command queue
  //
  Status = DispatchCommandQueue (CommandQueueBuffer, CommandQueueCount);

  RuntimeDebugMessage ("CSE command queue is done completing IO.\n", NULL, 0);

Done :
  if (!EfiAtRuntime ()) {
    EfiReleaseLock (&mCseVariableStorageLock);
    if (OriginalTpl > TPL_CALLBACK) {
      gBS->RaiseTPL (OriginalTpl);
    } else {
      gBS->RestoreTPL (OriginalTpl);
    }
  }
  return Status;
}

/**
  Initializes module buffers used in this module.

  @retval        EFI_SUCCESS                 The buffers were initialized successfully.
  @retval        Others                      The buffers could not be initialized.

**/
EFI_STATUS
EFIAPI
InitializeModuleBuffers (
  VOID
  )
{
  EfiInitializeLock(&mCseVariableStorageLock, TPL_CALLBACK);

  mCseVariableStorageRequestMessageBufferSize = SMM_CSE_VAR_STORAGE_GET_TOTAL_COMM_BUFFER_SIZE (
                                                  CSE_VAR_STORAGE_CMD_QUEUE_TOTAL_BUFFER_SIZE
                                                  );
  mCseVariableStorageRequestMessageBuffer = AllocateRuntimeZeroPool (mCseVariableStorageRequestMessageBufferSize);
  if (mCseVariableStorageRequestMessageBuffer == NULL) {
    goto InitializeModuleBuffersError;
  }
  mCseVariableStorageRequestMessageBufferPhysical = mCseVariableStorageRequestMessageBuffer;

  mCseVariableStorageDataBufferSize = SMM_CSE_VAR_STORAGE_GET_TOTAL_COMM_BUFFER_SIZE (
                                             CSE_VARIABLE_MAX_DATA_SIZE_WITH_HEADER
                                             );
  mCseVariableStorageDataBuffer = AllocateRuntimePages (EFI_SIZE_TO_PAGES (mCseVariableStorageDataBufferSize));
  if (mCseVariableStorageDataBuffer == NULL) {
    goto InitializeModuleBuffersError;
  }
  mCseVariableStorageDataBufferPhysical = mCseVariableStorageDataBuffer;

  mCseVariableStorageNoPayloadCommBufferSize = SMM_CSE_VAR_STORAGE_GET_TOTAL_COMM_BUFFER_SIZE (0);
  mCseVariableStorageNoPayloadCommBuffer = AllocateRuntimeZeroPool (
                                                    mCseVariableStorageNoPayloadCommBufferSize
                                                    );
  if (mCseVariableStorageNoPayloadCommBuffer == NULL) {
    goto InitializeModuleBuffersError;
  }
  mCseVariableStorageNoPayloadCommBufferPhysical = mCseVariableStorageNoPayloadCommBuffer;

  mCseVariableStorageDebugBufferSize = SMM_CSE_VAR_STORAGE_GET_TOTAL_COMM_BUFFER_SIZE (
                                         sizeof (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_DEBUG_MSG)
                                         );
  mCseVariableStorageDebugBuffer = AllocateRuntimeZeroPool (mCseVariableStorageDebugBufferSize);
  if (mCseVariableStorageDebugBuffer == NULL) {
    goto InitializeModuleBuffersError;
  }
  mCseVariableStorageDebugBufferPhysical = mCseVariableStorageDebugBuffer;

  mCseVariableStorageDataBufferDataPtr = (VOID *) ((UINT8 *) mCseVariableStorageDataBuffer + SIZE_4KB);
  mCseVariableStorageDataBufferSmmCommPtr = (VOID *) (
                                              (UINT8 *) mCseVariableStorageDataBufferDataPtr -
                                              SMM_CSE_VAR_STORAGE_GET_TOTAL_COMM_BUFFER_SIZE (0)
                                              );
  mCseVariableStorageDataBufferSmmCommPtrPhysical = mCseVariableStorageDataBufferSmmCommPtr;
  mCseVariableStorageResponseBufferPtr =  (BIOS_STORAGE_RESPONSE_BUFFER *) (
                                            (UINT8 *) mCseVariableStorageDataBufferDataPtr -
                                            sizeof (BIOS_STORAGE_RESPONSE_BUFFER)
                                            );

  mCseVariableStorageActualDataBufferSmmCommunicateBufferSize = mCseVariableStorageDataBufferSize -
                                                                  (
                                                                    (UINTN) mCseVariableStorageDataBufferSmmCommPtr -
                                                                    (UINTN) mCseVariableStorageDataBuffer
                                                                    );

  DEBUG ((EFI_D_INFO, "CSE Variable Storage Command Queue Buffer Sizes:\n"));
  DEBUG ((EFI_D_INFO, "  Request Message Buffer Size: %d bytes.\n", mCseVariableStorageRequestMessageBufferSize));
  DEBUG ((EFI_D_INFO, "  Data Buffer Size: %d bytes.\n", mCseVariableStorageDataBufferSize));
  DEBUG ((
    EFI_D_INFO,
    "  Actual SMM Communicate Data Buffer Size: %d bytes.\n",
    mCseVariableStorageActualDataBufferSmmCommunicateBufferSize
    ));
  DEBUG ((EFI_D_INFO, "  No Payload Communicate Buffer Size: %d bytes.\n", mCseVariableStorageNoPayloadCommBufferSize));
  DEBUG ((EFI_D_INFO, "  Debug Buffer Size: %d bytes.\n", mCseVariableStorageDebugBufferSize));

  return EFI_SUCCESS;

InitializeModuleBuffersError:
  if (mCseVariableStorageRequestMessageBuffer != NULL) {
    FreePool (mCseVariableStorageRequestMessageBuffer);
    mCseVariableStorageRequestMessageBuffer = NULL;
  }
  if (mCseVariableStorageDataBuffer != NULL) {
    FreePool (mCseVariableStorageDataBuffer);
    mCseVariableStorageDataBuffer = NULL;
  }
  if (mCseVariableStorageNoPayloadCommBuffer != NULL) {
    FreePool (mCseVariableStorageNoPayloadCommBuffer);
    mCseVariableStorageNoPayloadCommBuffer = NULL;
  }
  if (mCseVariableStorageDebugBuffer != NULL) {
    FreePool (mCseVariableStorageDebugBuffer);
    mCseVariableStorageDebugBuffer = NULL;
  }
  mCseVariableStorageDataBufferDataPtr = NULL;
  mCseVariableStorageDataBufferSmmCommPtr = NULL;
  mCseVariableStorageResponseBufferPtr = NULL;

  return EFI_OUT_OF_RESOURCES;
}
