/** @file
  SMM CSE Variable Storage IO Command Queue Implementation

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
#include <CseVariableStorageCommandQueue.h>

extern VOID                                             *mCseCommandQueueReadBuffer;
extern CSE_VARIABLE_STORAGE_SUPPORT_PROTOCOL            *mCseVariableStorageSupportProtocol;
extern HECI_TRUSTED_CHANNEL_PROTOCOL                    *mHeciTrustedChannelProtocol;
extern CSE_VARIABLE_STORAGE_INDEX_CONTEXT               *mCseIndexQueueWriteBuffer[CSE_VAR_STORAGE_CMD_QUEUE_MAX_TOTAL_REQUESTS];
extern CSE_VARIABLE_STORAGE_REQUEST                     *mCseCommandQueueWriteBuffer[CSE_VAR_STORAGE_CMD_QUEUE_MAX_TOTAL_REQUESTS];
extern VOID                                             *mCseCommandQueueRequestBuffer;
extern UINTN                                            *mCseCommandQueueRuntimeDataBufferPtr;
extern UINTN                                            mCseCommandQueueReadBufferSize;
extern UINTN                                            mCseCommandQueueWriteBufferSize;
extern UINTN                                            mCseCommandQueueWriteRequestConsumerIndex;
extern UINTN                                            mCseCommandQueueWriteRequestProducerIndex;
extern UINTN                                            mTrustedHeciBarAddress;
extern UINTN                                            mGetOsProxyHeciBaseAddress;
extern UINTN                                            mGetOsProxyHeciBarAddress;
extern CIRCULAR_BUFFER                                  mCseCommandQueue;
extern CSE_VARIABLE_STORAGE_RUNTIME_DATA_BUFFER_ADDRESS mCseCommandQueueRuntimeDataBufferAddress;
extern BOOLEAN                                          mRequireReadCommandQueue;
extern BOOLEAN                                          mRequireWriteCommandQueue;
extern BOOLEAN                                          mSmramLocked;
extern BOOLEAN                                          mTrustedChannelEnabled;

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
  Informs the CSE variable driver that a GetVariable() sequence completed.

  @param[in]  Data                   A pointer to the data buffer that will be copied to the cache.
  @param[in]  VariableSize           The total size of variable data in bytes.

  @retval     EFI_SUCCESS            The variable cache was updated successfully.
  @retval     EFI_ABORTED            Insufficient information exists to update the variable cache.
  @retval     Others                 An error occurred updating the variable cache.

**/
EFI_STATUS
EFIAPI
SendReadCompleteNotify (
  IN  VOID   *Data,
  IN  UINTN  VariableSize
  )
{
  if (mCseVariableStorageSupportProtocol == NULL) {
    return EFI_NOT_READY;
  }

  mCseVariableStorageSupportProtocol->NotifyReadIoComplete (
                                        EFI_SUCCESS,
                                        Data,
                                        VariableSize
                                        );
  return EFI_SUCCESS;
}

/**
  Resets the write request data buffer.

**/
VOID
EFIAPI
ResetWriteRequestDataBuffer (
  VOID
  )
{
  UINTN Index;

  mCseCommandQueueWriteRequestConsumerIndex = 0;
  mCseCommandQueueWriteRequestProducerIndex = 0;

  for (Index = 0; Index < CSE_VAR_STORAGE_CMD_QUEUE_MAX_TOTAL_REQUESTS; Index++) {
    if (mCseCommandQueueWriteBuffer[Index] != NULL) {
      ZeroMem (mCseCommandQueueWriteBuffer[Index], sizeof (CSE_VARIABLE_STORAGE_REQUEST));
    }
    if (mCseIndexQueueWriteBuffer[Index] != NULL) {
      ZeroMem (mCseIndexQueueWriteBuffer[Index], sizeof (CSE_VARIABLE_STORAGE_INDEX_CONTEXT));
    }
  }
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
  CSE Variable Storage Response Command SMM verification.

  Caution: This function may receive untrusted input.

  This function validates the CSE HMAC response data, updates the NV variable cache on reads, and writes back
  index area information to memory from a temporary area on writes if the NVM write was successful.

  @param[in]     VerifyResponse  A pointer to a Verify Response structure passed from a Runtime DXE wrapper.

  @retval EFI_SUCCESS                         The response data was verified and handled successfully.
  @retval EFI_INVALID_PARAMETER               The VerifyResponse actual parameter was NULL or the command is invalid.
  @retval EFI_PROTOCOL_ERROR                  The HECI_TRUSTED_CHANNEL_PROTOCOL SMM protocol could not be located.
  @retval EFI_NOT_READY                       The EDKII_VARIABLE_STORAGE_SUPPORT_PROTOCOL could not be located.
  @retval EFI_SECURITY_VIOLATION              The response message signature was computed and is invalid.
  @retval Others                              An error occurred attempting to verify the message.
**/
EFI_STATUS
EFIAPI
VerifyCommandResponseData (
  IN   CONST SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_VERIFY_RESPONSE   *VerifyResponse
  )
{
  EFI_STATUS                                    Status;
  BIOS_STORAGE_TRUSTED_CHANNEL_RESPONSE         *ReadResponse;
  BIOS_STORAGE_TRUSTED_CHANNEL_RESPONSE         WriteResponseHeader;
  BOOLEAN                                       IsVerificationSuccessful  = FALSE;
  CONST UINTN                                   HeaderSize  = sizeof (BIOS_STORAGE_TRUSTED_CHANNEL_RESPONSE);
  CONST TRUSTED_CHANNEL_BIOS_RESPONSE_HEADER    *TrustedChannelResponseHeader;

  TrustedChannelResponseHeader = (CONST TRUSTED_CHANNEL_BIOS_RESPONSE_HEADER *) &VerifyResponse->ResponseMessage;

  if (VerifyResponse == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  if (mHeciTrustedChannelProtocol == NULL) {
    return EFI_PROTOCOL_ERROR;
  }

  if (TrustedChannelResponseHeader->TrustedHeader.Command.Id == BIOS_STORAGE_READ_CMD_TRUSTED_CHANNEL) {
    // Read commands must be able to update the variable NV cache
    if (mCseVariableStorageSupportProtocol == NULL) {
      return EFI_NOT_READY;
    } else if (VerifyResponse->DataSize > (mCseCommandQueueReadBufferSize - EFI_PAGE_SIZE)) {
      DEBUG ((DEBUG_ERROR, "An invalid data buffer size was given when verifying the read message response.\n"));
      return EFI_INVALID_PARAMETER;
    }
    ZeroMem (mCseCommandQueueReadBuffer, mCseCommandQueueReadBufferSize);
    ReadResponse = (BIOS_STORAGE_TRUSTED_CHANNEL_RESPONSE *) mCseCommandQueueReadBuffer;
    // Copy the header to the SMM buffer
    CopyMem ((VOID *) &ReadResponse->Header, (VOID *) &VerifyResponse->ResponseMessage, HeaderSize);
    // Copy the data to the SMM buffer
    CopyMem ((VOID *) (ReadResponse + 1), (VOID *) &VerifyResponse->Data, VerifyResponse->DataSize);
    Status = mHeciTrustedChannelProtocol->VerifyTrustedHeader (
                                            (CONST VOID *) &ReadResponse[0],
                                            (UINT32) (HeaderSize + VerifyResponse->DataSize),
                                            &IsVerificationSuccessful
                                            );
  } else if (TrustedChannelResponseHeader->TrustedHeader.Command.Id == BIOS_STORAGE_WRITE_CMD_TRUSTED_CHANNEL) {
    // Copy the header to the local SMM buffer
    CopyMem ((VOID *) &WriteResponseHeader, (VOID *) &VerifyResponse->ResponseMessage, HeaderSize);
    Status = mHeciTrustedChannelProtocol->VerifyTrustedHeader (
                                            (CONST VOID *) &WriteResponseHeader,
                                            (UINT32) HeaderSize,
                                            &IsVerificationSuccessful
                                            );
  } else {
    DEBUG ((DEBUG_ERROR, "Invalid message type received in SMM command queue verification.\n"));
    ASSERT (FALSE);
    return EFI_INVALID_PARAMETER;
  }
  DEBUG ((DEBUG_INFO, "CSE Variable Storage Command Queue Verification Parameters:\n"));
  DEBUG ((DEBUG_INFO, "  HeaderSize: %d\n", HeaderSize));
  DEBUG ((DEBUG_INFO, "  DataSize: %d\n", VerifyResponse->DataSize));

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "An error occurred in signature verification. Status = %r.\n", Status));
    return Status;
  } else if (!IsVerificationSuccessful) {
    DEBUG ((DEBUG_ERROR, "Signature verification failed for a command queue response!\n"));
    return EFI_SECURITY_VIOLATION;
  }

  if (TrustedChannelResponseHeader->TrustedHeader.Command.Id == BIOS_STORAGE_READ_CMD_TRUSTED_CHANNEL) {
    DEBUG ((DEBUG_INFO, "Updating the variable driver non-volatile cache after read completion.\n"));
    Status = SendReadCompleteNotify ((VOID *) (ReadResponse + 1), VerifyResponse->DataSize);
    ZeroMem (mCseCommandQueueReadBuffer, mCseCommandQueueReadBufferSize);
    if (Status == EFI_ABORTED) {
      DEBUG ((DEBUG_ERROR, "Current variable header is NULL. Cannot update the variable cache.\n"));
      return Status;
    }
  }

  return EFI_SUCCESS;
}

/**
  CSE Variable Storage SMI handler entry.

  This SMI handler provides services for the Runtime DXE CSE Variable Storage Command Queue module

  Caution: This function may receive untrusted input.

  The communicate buffer is external input, so this function will do basic validation.
  Each sub function GetNextWriteBuffer, SetDataBuffer, GetCommandQueue, VerifyResponse, ResetCommandQueue,
  DebugMessage should also do validation based on its own knowledge.

  @param[in]     DispatchHandle  The unique handle assigned to this handler by SmiHandlerRegister().
  @param[in]     RegisterContext Points to an optional handler context which was specified when the
                                 handler was registered.
  @param[in, out] CommBuffer     A pointer to a collection of data in memory that will
                                 be conveyed from a non-SMM environment into an SMM environment.
  @param[in, out] CommBufferSize The size of the CommBuffer.

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
SmmCseVariableStorageHandler (
  IN       EFI_HANDLE    DispatchHandle,
  IN       CONST VOID    *RegisterContext,
  IN OUT   VOID          *CommBuffer,
  IN OUT   UINTN         *CommBufferSize
  )
{
  EFI_STATUS             Status;
  UINTN                  CommBufferPayloadSize;
  UINTN                  TempCommBufferSize;
  UINTN                  *RuntimeDataBufferDataPtr = NULL;

  SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_HEADER                      *SmmVariableStorageFunctionHeader;
  SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_GET_NEXT_WRITE_BUFFER       *GetNextWriteBuffer;
  SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_SET_DATA_BUFFER              *SetDataBuffer;
  SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_GET_COMMAND_QUEUE            *GetCommandQueue;
  SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_DEBUG_MSG                    *DebugMessage;
  SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_CACHE_DATA_BUFFER            *CacheDataBuffer;
  SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_TRUSTED_CHANNEL_DEVICE_INFO  *TrustedChannelDeviceInfo;
  SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_OS_PROXY_DEVICE_INFO         *OsProxyDeviceInfo;
  SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_TRUSTED_CHANNEL_COMM_FAILURE *TrustedChannelCommunicationFailure;

  Status = EFI_SUCCESS;

  //
  // If input is invalid, stop processing this SMI
  //
  if (CommBuffer == NULL || CommBufferSize == NULL) {
    return EFI_SUCCESS;
  }

  TempCommBufferSize = *CommBufferSize;

  if (TempCommBufferSize < SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_HEADER_SIZE) {
    DEBUG ((DEBUG_ERROR, "CSE Variable Storage SMM Handler: Communication buffer size is invalid!\n"));
    return EFI_SUCCESS;
  }
  CommBufferPayloadSize = TempCommBufferSize - SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_HEADER_SIZE;
  if (
    CommBufferPayloadSize >
    SMM_CSE_VAR_STORAGE_GET_TOTAL_COMM_BUFFER_SIZE (CSE_VARIABLE_MAX_DATA_SIZE_WITH_HEADER)
    ) {
    DEBUG ((DEBUG_ERROR, "CSE Variable Storage SMM Handler: SMM communication buffer payload size invalid!\n"));
    return EFI_SUCCESS;
  }

  if (!SmmIsBufferOutsideSmmValid ((UINTN) CommBuffer, TempCommBufferSize)) {
    DEBUG ((DEBUG_ERROR, "CSE Variable Storage SMM Handler: SMM communication buffer in SMRAM or overflow!\n"));
    return EFI_SUCCESS;
  }

  SmmVariableStorageFunctionHeader = (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_HEADER *) CommBuffer;

  switch (SmmVariableStorageFunctionHeader->Function) {
    case SMM_CSE_VARIABLE_STORAGE_FUNCTION_GET_NEXT_WRITE_BUFFER:
      if (CommBufferPayloadSize < sizeof (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_GET_NEXT_WRITE_BUFFER)) {
        DEBUG ((DEBUG_ERROR, "SMM communication buffer size for Get Next Write Buffer is invalid!\n"));
        Status = EFI_INVALID_PARAMETER;
      } else if (mCseCommandQueueWriteRequestConsumerIndex >= mCseCommandQueueWriteRequestProducerIndex) {
        // An invalid write buffer was requested (exceeded the number of enqueued entries)
        Status = EFI_OUT_OF_RESOURCES;
      } else {
        GetNextWriteBuffer = (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_GET_NEXT_WRITE_BUFFER *) SmmVariableStorageFunctionHeader->Data;
        CopyMem (
          &(GetNextWriteBuffer->Data[0]),
          &(mCseCommandQueueWriteBuffer[mCseCommandQueueWriteRequestConsumerIndex]->Data[0]),
          GetNextWriteBuffer->DataSize
          );
        mCseCommandQueueWriteRequestConsumerIndex++;
        Status = EFI_SUCCESS;
      }
      break;

    case SMM_CSE_VARIABLE_STORAGE_FUNCTION_SET_DATA_BUFFER:
      if (CommBufferPayloadSize < sizeof (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_SET_DATA_BUFFER)) {
        DEBUG ((DEBUG_ERROR, "SMM communication buffer for Set Data Buffer is invalid!\n"));
        Status = EFI_INVALID_PARAMETER;
      } else if (mSmramLocked) {
        DEBUG ((DEBUG_ERROR, "CSE variable storage command queue data buffer set after SMM is locked!\n"));
        Status = EFI_SECURITY_VIOLATION;
      } else {
        SetDataBuffer = (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_SET_DATA_BUFFER *) SmmVariableStorageFunctionHeader->Data;

        // The pointer points to the beginning of the full data buffer (including first page used for headers)
        mCseCommandQueueRuntimeDataBufferPtr =  (UINTN *) (
                                                  (UINTN) SetDataBuffer->DataBufferAddressLow |
                                                  LShiftU64 ((UINTN) SetDataBuffer->DataBufferAddressHigh, 32)
                                                  );
        RuntimeDataBufferDataPtr =  (UINTN *) ((UINT8 *) mCseCommandQueueRuntimeDataBufferPtr + EFI_PAGE_SIZE);

        // The addresses in the structure are the addresses of the actual data area used for DMA (1 page from start)
        mCseCommandQueueRuntimeDataBufferAddress.AddressLow = (UINT32) (UINTN) RuntimeDataBufferDataPtr;
        mCseCommandQueueRuntimeDataBufferAddress.AddressHigh = (UINT32) RShiftU64 ((UINTN) RuntimeDataBufferDataPtr, 32);
        mCseCommandQueueRuntimeDataBufferAddress.BufferLength = SetDataBuffer->BufferLength;

        ASSERT (mCseCommandQueueRuntimeDataBufferAddress.BufferLength > 0);
        DEBUG ((DEBUG_INFO, "Runtime DXE Data Buffers:\n"));
        DEBUG ((DEBUG_INFO, "  Address Low: 0x%08x\n", mCseCommandQueueRuntimeDataBufferAddress.AddressLow));
        DEBUG ((DEBUG_INFO, "  Address High: 0x%08x\n", mCseCommandQueueRuntimeDataBufferAddress.AddressHigh));
        DEBUG ((DEBUG_INFO, "  Address Pointer: %p\n", mCseCommandQueueRuntimeDataBufferPtr));

        mCseVariableStorageSupportProtocol->NofityRuntimeInitialized ();
        Status = EFI_SUCCESS;
      }
      break;

    case SMM_CSE_VARIABLE_STORAGE_FUNCTION_GET_COMMAND_QUEUE:
      if (CommBufferPayloadSize < sizeof (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_GET_COMMAND_QUEUE)) {
        DEBUG ((DEBUG_ERROR, "SMM communication buffer for Get Command Queue is invalid!\n"));
        Status = EFI_INVALID_PARAMETER;
      } else if (CommBufferPayloadSize < mCseCommandQueue.Capacity) {
        // The communicate buffer should have been allocated large enough to hold the entire SMM command queue
        DEBUG ((DEBUG_ERROR, "SMM communication buffer size for Get Command Queue is too small!\n"));
        Status = EFI_BUFFER_TOO_SMALL;
      } else {
        DEBUG ((DEBUG_INFO, "Getting command queue in SMM...\n"));
        GetCommandQueue = (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_GET_COMMAND_QUEUE *) SmmVariableStorageFunctionHeader->Data;
        CopyMem (
          (VOID *) &GetCommandQueue->CommandQueueDataBuffer[0],
          mCseCommandQueueRequestBuffer,
          mCseCommandQueue.Capacity
          );
        GetCommandQueue->CommandQueueCount = mCseCommandQueue.Count;
        Status = EFI_SUCCESS;
      }
      break;

    case SMM_CSE_VARIABLE_STORAGE_FUNCTION_VERIFY_RESPONSE:
      if (CommBufferPayloadSize < OFFSET_OF (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_VERIFY_RESPONSE, Data)) {
        DEBUG ((DEBUG_ERROR, "SMM communication buffer size for VerifyResponse is invalid!\n"));
        Status = EFI_INVALID_PARAMETER;
      } else {
        Status = VerifyCommandResponseData (
                   (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_VERIFY_RESPONSE *) SmmVariableStorageFunctionHeader->Data
                   );
      }
      break;

    case SMM_CSE_VARIABLE_STORAGE_FUNCTION_RESET_COMMAND_QUEUE:
      // Only the request queue should be cleared.
      Status = CircularBufferReset (&mCseCommandQueue);
      break;

    case SMM_CSE_VARIABLE_STORAGE_FUNCTION_TRUSTED_CHANNEL_ENABLE:
      mTrustedChannelEnabled = TRUE;
      break;

    case SMM_CSE_VARIABLE_STORAGE_FUNCTION_DEBUG_MESSAGE:
      DebugMessage = (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_DEBUG_MSG *) SmmVariableStorageFunctionHeader->Data;

      DEBUG_CODE_BEGIN ();
      DEBUG ((DEBUG_INFO, "RT DXE Message:\n"));
      DEBUG ((DEBUG_INFO, "  %a", DebugMessage->DebugMsg));

      if (DebugMessage->Datalength != 0) {
        DEBUG ((DEBUG_INFO, "\nRT DXE Message Data:\n"));
        PrintBinaryBuffer (&DebugMessage->Data[0], DebugMessage->Datalength);
      }
      DEBUG ((DEBUG_INFO, "\n"));
      DEBUG_CODE_END ();

      Status = EFI_SUCCESS;
      break;

    case SMM_CSE_VARIABLE_STORAGE_FUNCTION_RESET_WRITE_COMMAND_QUEUE:
      ResetWriteRequestDataBuffer ();
      break;

    case SMM_CSE_VARIABLE_STORAGE_FUNCTION_REQUIRE_READ_COMMAND_QUEUE:
      if (!BootMediaIsSpi ()) {
        mRequireReadCommandQueue = TRUE;
      }
      break;

    case SMM_CSE_VARIABLE_STORAGE_FUNCTION_REQUIRE_WRITE_COMMAND_QUEUE:
      if (!BootMediaIsSpi ()) {
        mRequireWriteCommandQueue = TRUE;
      }
      break;

    case SMM_CSE_VARIABLE_STORAGE_FUNCTION_READ_COMPLETION_IO_DONE:
      if (CommBufferPayloadSize < OFFSET_OF (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_CACHE_DATA_BUFFER, Data)) {
        DEBUG ((DEBUG_ERROR, "SMM communication buffer size for ReadCompletionIoDone is invalid!\n"));
        Status = EFI_INVALID_PARAMETER;
      } else {
        CacheDataBuffer = (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_CACHE_DATA_BUFFER *) SmmVariableStorageFunctionHeader->Data;
        Status = SendReadCompleteNotify ((VOID *) &CacheDataBuffer->Data, CacheDataBuffer->DataSize);
      }
      ZeroMem (mCseCommandQueueReadBuffer, mCseCommandQueueReadBufferSize);
      break;

    case SMM_CSE_VARIABLE_STORAGE_FUNCTION_WRITE_COMPLETION_IO_DONE:
      if (
        mCseCommandQueueWriteRequestConsumerIndex == 0 ||
        mCseCommandQueueWriteRequestConsumerIndex > mCseCommandQueueWriteRequestProducerIndex
        ) {
        DEBUG ((DEBUG_ERROR, "Write index update is invalid. The request is out of range.\n"));
        Status = EFI_UNSUPPORTED;
      } else if (mCseIndexQueueWriteBuffer[mCseCommandQueueWriteRequestConsumerIndex - 1] != NULL) {
        Status =  CseVariableStorageIoUpdateIndexArea (
                    mCseIndexQueueWriteBuffer[mCseCommandQueueWriteRequestConsumerIndex - 1]
                    );
      }
      break;

    case SMM_CSE_VARIABLE_STORAGE_FUNCTION_TRUSTED_CHANNEL_DEVICE_INFO:
      if (CommBufferPayloadSize != sizeof (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_TRUSTED_CHANNEL_DEVICE_INFO)) {
        DEBUG ((DEBUG_ERROR, "SMM communication buffer size for TrustedChannelDeviceInfo is invalid!\n"));
        Status = EFI_INVALID_PARAMETER;
      } else if (mSmramLocked) {
        DEBUG ((DEBUG_ERROR, "Trusted Channel device info sent after SMM is locked!\n"));
        Status = EFI_SECURITY_VIOLATION;
      } else {
        TrustedChannelDeviceInfo = (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_TRUSTED_CHANNEL_DEVICE_INFO *) SmmVariableStorageFunctionHeader->Data;
        ASSERT (TrustedChannelDeviceInfo->HeciTrustedDeviceBar != 0);
        mTrustedHeciBarAddress = TrustedChannelDeviceInfo->HeciTrustedDeviceBar;
      }
      break;

    case SMM_CSE_VARIABLE_STORAGE_FUNCTION_OS_PROXY_DEVICE_INFO:
      if (CommBufferPayloadSize != sizeof (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_OS_PROXY_DEVICE_INFO)) {
        DEBUG ((DEBUG_ERROR, "SMM communication buffer size for OsProxyDeviceInfo is invalid!\n"));
        Status = EFI_INVALID_PARAMETER;
      } else if (mSmramLocked) {
        DEBUG ((DEBUG_ERROR, "OS Proxy device info sent after SMM is locked!\n"));
        Status = EFI_SECURITY_VIOLATION;
      } else {
        OsProxyDeviceInfo = (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_OS_PROXY_DEVICE_INFO *) SmmVariableStorageFunctionHeader->Data;
        ASSERT (OsProxyDeviceInfo->OsProxyHeciBaseAddress != 0);
        ASSERT (OsProxyDeviceInfo->OsProxyHeciBar != 0);
        mGetOsProxyHeciBaseAddress = OsProxyDeviceInfo->OsProxyHeciBaseAddress;
        mGetOsProxyHeciBarAddress = OsProxyDeviceInfo->OsProxyHeciBar;
      }
      break;

    case SMM_CSE_VARIABLE_STORAGE_FUNCTION_TRUSTED_CHANNEL_COMM_FAILURE:
      if (CommBufferPayloadSize < sizeof (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_TRUSTED_CHANNEL_COMM_FAILURE)) {
        DEBUG ((DEBUG_ERROR, "SMM communication buffer size for Trusted Channel communication failure is invalid!\n"));
        Status = EFI_INVALID_PARAMETER;
      } else {
        TrustedChannelCommunicationFailure = (SMM_CSE_VARIABLE_STORAGE_COMMUNICATE_TRUSTED_CHANNEL_COMM_FAILURE *)
                                               SmmVariableStorageFunctionHeader->Data;

        Status = CircularBufferReset (&mCseCommandQueue);
        ASSERT_EFI_ERROR (Status);
        ResetWriteRequestDataBuffer ();
        ZeroMem (mCseCommandQueueReadBuffer, mCseCommandQueueReadBufferSize);

        Status = mHeciTrustedChannelProtocol->DecrementMonotonicCount (
                                                (UINT32) TrustedChannelCommunicationFailure->MessagesRemaining
                                                );
      }
      break;

    default:
      Status = EFI_UNSUPPORTED;
  }

  SmmVariableStorageFunctionHeader->ReturnStatus = Status;

  return EFI_SUCCESS;
}

/**
  Initializes command queue buffers used in this module.

  @retval        EFI_SUCCESS                 The buffers were initialized successfully.
  @retval        Others                      The buffers could not be initialized.

**/
EFI_STATUS
EFIAPI
InitializeCommandQueueBuffers (
  VOID
  )
{
  UINTN     Index;

  // Use the maximum total size of all possible request headers - Multiple requests may exist in the command queue
  mCseCommandQueueRequestBuffer = AllocateZeroPool (CSE_VAR_STORAGE_CMD_QUEUE_TOTAL_BUFFER_SIZE);
  if (mCseCommandQueueRequestBuffer == NULL) {
    ASSERT (mCseCommandQueueRequestBuffer != NULL);
    goto InitializeCommandQueueBuffersError;
  }

  // Use the single maximum message size - only a single read message will be verified at a time
  // The message contents are copied to SMRAM from the DMA buffer to verify the digest in isolation
  mCseCommandQueueReadBufferSize = CSE_VARIABLE_MAX_DATA_SIZE_WITH_HEADER;
  mCseCommandQueueReadBuffer = AllocateZeroPool (mCseCommandQueueReadBufferSize);
  if (mCseCommandQueueReadBuffer == NULL) {
    ASSERT (mCseCommandQueueReadBuffer != NULL);
    goto InitializeCommandQueueBuffersError;
  }

  // Assume the worst case for writes - the max number of request messages are write requests
  mCseCommandQueueWriteBufferSize = (sizeof (CSE_VARIABLE_STORAGE_REQUEST) * \
                                      CSE_VAR_STORAGE_CMD_QUEUE_MAX_TOTAL_REQUESTS);
  for (Index = 0; Index < CSE_VAR_STORAGE_CMD_QUEUE_MAX_TOTAL_REQUESTS; Index++) {
    mCseCommandQueueWriteBuffer[Index] = AllocateZeroPool (sizeof (CSE_VARIABLE_STORAGE_REQUEST));
    if (mCseCommandQueueWriteBuffer[Index] == NULL) {
      ASSERT (mCseCommandQueueWriteBuffer[Index] != NULL);
      goto InitializeCommandQueueBuffersError;
    }
    mCseIndexQueueWriteBuffer[Index] = AllocateZeroPool (sizeof (CSE_VARIABLE_STORAGE_INDEX_CONTEXT));
    if (mCseIndexQueueWriteBuffer[Index] == NULL) {
      ASSERT (mCseIndexQueueWriteBuffer[Index] != NULL);
      goto InitializeCommandQueueBuffersError;
    }
  }

  DEBUG ((DEBUG_INFO, "CSE Variable Storage SMM Command Queue Allocation Sizes:\n"));
  DEBUG ((
    DEBUG_INFO,
    "  Index Queue Buffer Size: 0x%x bytes\n",
    (sizeof (CSE_VARIABLE_STORAGE_INDEX_CONTEXT) * CSE_VAR_STORAGE_CMD_QUEUE_MAX_TOTAL_REQUESTS)
    ));
  DEBUG ((DEBUG_INFO, "  Command Queue Request Buffer Size: 0x%x bytes\n", CSE_VAR_STORAGE_CMD_QUEUE_TOTAL_BUFFER_SIZE));
  DEBUG ((DEBUG_INFO, "  Command Queue Read Buffer Size: 0x%x bytes\n", mCseCommandQueueReadBufferSize));
  DEBUG ((DEBUG_INFO, "  Command Queue Write Buffer Size: 0x%x bytes\n", mCseCommandQueueWriteBufferSize));

  mCseCommandQueue.Buffer = mCseCommandQueueRequestBuffer;

  return EFI_SUCCESS;

InitializeCommandQueueBuffersError:
  if (mCseCommandQueueRequestBuffer != NULL) {
    FreePool (mCseCommandQueueRequestBuffer);
    mCseCommandQueueRequestBuffer = NULL;
  }
  if (mCseCommandQueueReadBuffer != NULL) {
    FreePool (mCseCommandQueueReadBuffer);
    mCseCommandQueueReadBuffer = NULL;
  }
  for (Index = 0; Index < CSE_VAR_STORAGE_CMD_QUEUE_MAX_TOTAL_REQUESTS; Index++) {
    if (mCseCommandQueueWriteBuffer[Index] != NULL) {
      FreePool (mCseCommandQueueWriteBuffer[Index]);
    }
    if (mCseIndexQueueWriteBuffer[Index] != NULL) {
      FreePool (mCseIndexQueueWriteBuffer[Index]);
    }
  }
  mCseCommandQueueReadBufferSize = 0;
  mCseCommandQueueWriteBufferSize = 0;

  return EFI_OUT_OF_RESOURCES;
}
