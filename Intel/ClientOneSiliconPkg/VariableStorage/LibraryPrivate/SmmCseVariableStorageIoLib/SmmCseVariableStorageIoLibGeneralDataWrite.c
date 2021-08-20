/** @file
  SMM CSE Variable Storage General Data Write IO Implementation

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

extern BOOLEAN                                          mRequireWriteCommandQueue;
extern BOOLEAN                                          mTrustedChannelEnabled;
extern BOOLEAN                                          mAtRuntime;
extern CSE_VARIABLE_STORAGE_RUNTIME_DATA_BUFFER_ADDRESS mCseCommandQueueRuntimeDataBufferAddress;
extern CSE_VARIABLE_STORAGE_INDEX_CONTEXT               *mCseIndexQueueWriteBuffer[CSE_VAR_STORAGE_CMD_QUEUE_MAX_TOTAL_REQUESTS];
extern CSE_VARIABLE_STORAGE_REQUEST                     *mCseCommandQueueWriteBuffer[CSE_VAR_STORAGE_CMD_QUEUE_MAX_TOTAL_REQUESTS];
extern CIRCULAR_BUFFER                                  mCseCommandQueue;
extern HECI_PROTOCOL                                    *mHeciProtocol;
extern HECI_TRUSTED_CHANNEL_PROTOCOL                    *mHeciTrustedChannelProtocol;
extern UINTN                                            mTrustedHeciBarAddress;
extern UINTN                                            *mCseCommandQueueRuntimeDataBufferPtr;
extern UINTN                                            mCseCommandQueueWriteRequestConsumerIndex;
extern UINTN                                            mCseCommandQueueWriteRequestProducerIndex;

/**
  Constructs a General Data Storage Write request message.

  @param[in]      CseVariableStorageStore     A pointer to a structure CSE Variable Storage Store structure.
  @param[in]      Data                        A pointer to a buffer of data to write.
  @param[in]      DataSize                    The length in bytes of data to read.
  @param[in]      Offset                      The offset in bytes from the base of the write area to write.
  @param[out]     WriteMsg                    A pointer to the request message

  @retval         EFI_SUCCESS                 The write message was constructed successfully.
  @retval         EFI_INVALID_PARAMETER       A parameter to the function was invalid such as a NULL pointer.
  @retval         EFI_UNSUPPORTED             The requested size exceeds the allowable limit.
  @retval         Others                      An error occurred constructing the read message.

**/
EFI_STATUS
EFIAPI
CseVariableStorageGeneralDataWriteIoGetMessage (
  IN  CONST  CSE_VARIABLE_STORAGE_STORE        *CseVariableStorageStore,
  IN  CONST  VOID                              *Data,
  IN         UINTN                             DataSize,
  IN         UINT32                            Offset,
  OUT        BIOS_STORAGE_REQUEST              *WriteMsg
  )
{
  if (CseVariableStorageStore == NULL || Data == NULL) {
    return EFI_INVALID_PARAMETER;
  } else if (DataSize > CSE_VARIABLE_MAX_DATA_SIZE) {
    return EFI_UNSUPPORTED;
  } else if (Offset > CseVariableStorageStore->Info.MaximumSize) {
    return EFI_INVALID_PARAMETER;
  } else if (!IsDataBufferValid ()) {
    return EFI_SECURITY_VIOLATION;
  }
  ZeroMem ((VOID *) WriteMsg, sizeof (BIOS_STORAGE_REQUEST));

  // Initialize the MKHI message header
  WriteMsg->MkhiHeader.Fields.GroupId    = MKHI_MCA_GROUP_ID;
  WriteMsg->MkhiHeader.Fields.Command    = BIOS_STORAGE_WRITE_CMD;
  WriteMsg->MkhiHeader.Fields.IsResponse = FALSE;
  WriteMsg->MkhiHeader.Fields.Result     = MkhiStatusSuccess;

  // Initialize the message body
  // Note: DMA requires the data buffer provided be 4k-aligned and outside SMRAM
  WriteMsg->Body.Offset                  = CseVariableStorageStore->Info.Offset + Offset;
  WriteMsg->Body.Length                  = (UINT32) DataSize;
  WriteMsg->Body.BufferAddressLow        = mCseCommandQueueRuntimeDataBufferAddress.AddressLow;
  WriteMsg->Body.BufferAddressHigh       = mCseCommandQueueRuntimeDataBufferAddress.AddressHigh;
  WriteMsg->Body.Flags.WritePatternByte  = FALSE;

  DEBUG ((DEBUG_INFO, "Write Message:\n"));
  DEBUG ((DEBUG_INFO, "  Offset              = 0x%08x\n", WriteMsg->Body.Offset));
  DEBUG ((DEBUG_INFO, "  Length              = 0x%08x\n", WriteMsg->Body.Length));
  DEBUG ((DEBUG_INFO, "  Buffer Address Low  = 0x%08x\n", WriteMsg->Body.BufferAddressLow));
  DEBUG ((DEBUG_INFO, "  Buffer Address High = 0x%08x\n", WriteMsg->Body.BufferAddressHigh));

  return EFI_SUCCESS;
}

/**
  Writes data to a General Data CSE Variable Storage area.

  @param[in]  CseVariableStorageStore     A pointer to a structure CSE Variable Storage Store structure.
  @param[in]  Data                        A pointer to a buffer of data to write.
  @param[in]  DataSize                    The length in bytes of data to write.
  @param[in]  Offset                      The offset in bytes from the base of the write area to write.
  @param[in]  IndexContext                A structure with the index context for the variable being written.

  @retval     EFI_SUCCESS                 The data was written successfully.
  @retval     EFI_INVALID_PARAMETER       A parameter to the function was invalid such as a NULL pointer.
  @retval     EFI_BUFFER_TOO_SMALL        The data size requested exceeds available buffer space.
  @retval     EFI_NOT_READY               The required interfaces are not available for communication at this time.
  @retval     EFI_SECURITY_VIOLATION      A security violation occurred processing the request.
  @retval     EFI_DEVICE_ERROR            An error occurred communicating with the HECI device.
  @retval     Others                      An error occurred causing the communication operation to be aborted.

**/
EFI_STATUS
EFIAPI
CseVariableStorageGeneralDataWriteIo (
  IN  CONST  CSE_VARIABLE_STORAGE_STORE           *CseVariableStorageStore,
  IN  CONST  VOID                                 *Data,
  IN         UINTN                                DataSize,
  IN         UINT32                               Offset,
  IN  CONST  CSE_VARIABLE_STORAGE_INDEX_CONTEXT   *IndexContext OPTIONAL
  )
{
  EFI_STATUS            Status;
  BIOS_STORAGE_BUFFER   *WriteMsg;
  UINT32                MessageReceiveLength;
  UINT32                MessageSendLength;

  if (!IsReadyForTransaction ()) {
    return EFI_NOT_READY;
  }

  WriteMsg = (BIOS_STORAGE_BUFFER *) mCseCommandQueueWriteBuffer[mCseCommandQueueWriteRequestProducerIndex];

  Status =  CseVariableStorageGeneralDataWriteIoGetMessage (
              CseVariableStorageStore,
              Data,
              DataSize,
              Offset,
              &(WriteMsg->Request)
              );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "An error occurred creating the request message. Status = %r.\n", Status));
    goto Exit;
  }

  // Copy the data to the runtime buffer
  ZeroMem (mCseCommandQueueRuntimeDataBufferPtr, mCseCommandQueueRuntimeDataBufferAddress.BufferLength);
  CopyMem ((VOID *) ((UINT8 *) mCseCommandQueueRuntimeDataBufferPtr + EFI_PAGE_SIZE), Data, DataSize);

  // Update the local buffer with the IndexContext if provided
  if (IndexContext != NULL) {
    Status = CseVariableStorageIoUpdateDataWithContext (
               CseVariableStorageStore,
               mCseIndexQueueWriteBuffer,
               mCseCommandQueueWriteRequestProducerIndex,
               (VOID *) ((UINT8 *) mCseCommandQueueRuntimeDataBufferPtr + EFI_PAGE_SIZE),
               DataSize,
               IndexContext
               );
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  MessageSendLength     = sizeof (BIOS_STORAGE_REQUEST);
  MessageReceiveLength  = sizeof (BIOS_STORAGE_RESPONSE);

  Status = mHeciProtocol->SendMsg (
                            CSE_VARIABLE_STORAGE_CMD_QUEUE_UNTRUSTED_HECI_DEVICE,
                            (UINT32 *) WriteMsg,
                            MessageSendLength,
                            BIOS_FIXED_HOST_ADDR,
                            HECI_MCHI_MESSAGE_ADDR
                            );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "An error was returned from the HECI protocol sending the write message.\n"));
    goto Exit;
  }

  DEBUG ((DEBUG_INFO, "Waiting for the write message response to be ready...\n"));

  // Clear the request message before reading the response
  ZeroMem (WriteMsg, (UINTN) MessageSendLength);
  Status = mHeciProtocol->ReadMsg (
                            CSE_VARIABLE_STORAGE_CMD_QUEUE_UNTRUSTED_HECI_DEVICE,
                            BLOCKING,
                            (UINT32 *) WriteMsg,
                            &MessageReceiveLength
                            );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "An error was returned from the HECI protocol getting the write message response.\n"));
    goto Exit;
  } else if (WriteMsg->Response.MkhiHeader.Fields.Result != MkhiStatusSuccess) {
    DEBUG ((
      DEBUG_ERROR,
      "Error in response status. The response status value is 0x%x. Failure specific data = 0x%x\n",
      WriteMsg->Response.MkhiHeader.Fields.Result,
      WriteMsg->Response.Body.FailureSpecificData
      ));
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  } else if (!WriteMsg->Response.MkhiHeader.Fields.IsResponse) {
    DEBUG ((DEBUG_ERROR, "Response bit not set in read message response.\n"));
    goto Exit;
  }
  DEBUG ((DEBUG_INFO, "Total message receive length = 0x%x.\n", MessageReceiveLength));

  if (MessageReceiveLength != sizeof (BIOS_STORAGE_RESPONSE)) {
    ASSERT (MessageReceiveLength == sizeof (BIOS_STORAGE_RESPONSE));
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  DEBUG ((DEBUG_INFO, "Write message successfully completed.\n"));

Exit:
  ZeroMem (mCseCommandQueueRuntimeDataBufferPtr, mCseCommandQueueRuntimeDataBufferAddress.BufferLength);
  ZeroMem (mCseCommandQueueWriteBuffer[mCseCommandQueueWriteRequestProducerIndex], sizeof (BIOS_STORAGE_BUFFER));

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "An error occurred in the write command. Status = %r\n", Status));
  }

  return Status;
}

/**
  Constructs a General Data Storage Trusted Channel Write request message.

  @param[in]      CseVariableStorageStore     A pointer to a structure CSE Variable Storage Store structure.
  @param[in]      Data                        A pointer to a buffer of data to write.
  @param[in]      DataSize                    The length in bytes of data to read.
  @param[in]      Offset                      The offset in bytes from the base of the write area to write.
  @param[out]     TrustedChannelWriteRequest  A pointer to the request message
  @param[in]      IndexContext                A structure with the index context for the variable being written.

  @retval         EFI_SUCCESS                 The write message was constructed successfully.
  @retval         EFI_INVALID_PARAMETER       A parameter to the function was invalid such as a NULL pointer.
  @retval         EFI_UNSUPPORTED             The requested size exceeds the allowable limit.
  @retval         Others                      An error occurred constructing the read message.

**/
EFI_STATUS
EFIAPI
CseVariableStorageGeneralDataWriteTrustedChannelIoGetMessage (
  IN  CONST  CSE_VARIABLE_STORAGE_STORE                   *CseVariableStorageStore,
  IN  CONST  VOID                                         *Data,
  IN         UINTN                                        DataSize,
  IN         UINT32                                       Offset,
  OUT        CSE_VARIABLE_STORAGE_REQUEST                 *TrustedChannelWriteRequest,
  IN  CONST  CSE_VARIABLE_STORAGE_INDEX_CONTEXT           *IndexContext OPTIONAL
  )
{
  EFI_STATUS    Status;

  if (CseVariableStorageStore == NULL || Data == NULL || TrustedChannelWriteRequest == NULL) {
    return EFI_INVALID_PARAMETER;
  } else if (DataSize > CSE_VARIABLE_MAX_DATA_SIZE) {
    return EFI_UNSUPPORTED;
  } else if (Offset > CseVariableStorageStore->Info.MaximumSize) {
    return EFI_INVALID_PARAMETER;
  } else if (!IsDataBufferValid ()) {
    return EFI_SECURITY_VIOLATION;
  }

  ZeroMem ((VOID *) TrustedChannelWriteRequest, sizeof (CSE_VARIABLE_STORAGE_REQUEST));

  // Initialize the message body
  // Note: DMA requires the data buffer provided be 4k-aligned and outside SMRAM
  TrustedChannelWriteRequest->Header.TrustedChannelMessage.Body.Offset = CseVariableStorageStore->Info.Offset + Offset;
  TrustedChannelWriteRequest->Header.TrustedChannelMessage.Body.Length = (UINT32) DataSize;
  TrustedChannelWriteRequest->Header.TrustedChannelMessage.Body.BufferAddressLow = mCseCommandQueueRuntimeDataBufferAddress.AddressLow;
  TrustedChannelWriteRequest->Header.TrustedChannelMessage.Body.BufferAddressHigh  = mCseCommandQueueRuntimeDataBufferAddress.AddressHigh;
  TrustedChannelWriteRequest->Header.TrustedChannelMessage.Body.Flags.WritePatternByte = FALSE;
  TrustedChannelWriteRequest->Header.TrustedChannelMessage.Header.TrustedHeader.Command.IsResponse = FALSE;
  TrustedChannelWriteRequest->Header.TrustedChannelMessage.Header.TrustedHeader.Command.Id = BIOS_STORAGE_WRITE_CMD_TRUSTED_CHANNEL;

  DEBUG ((DEBUG_INFO, "Trusted Channel Write Message:\n"));
  DEBUG ((DEBUG_INFO, "  Offset              = 0x%08x\n", TrustedChannelWriteRequest->Header.TrustedChannelMessage.Body.Offset));
  DEBUG ((DEBUG_INFO, "  Length              = 0x%08x\n", TrustedChannelWriteRequest->Header.TrustedChannelMessage.Body.Length));
  DEBUG ((DEBUG_INFO, "  Buffer Address Low  = 0x%08x\n", TrustedChannelWriteRequest->Header.TrustedChannelMessage.Body.BufferAddressLow));
  DEBUG ((DEBUG_INFO, "  Buffer Address High = 0x%08x\n", TrustedChannelWriteRequest->Header.TrustedChannelMessage.Body.BufferAddressHigh));

  // Copy the user's data to the SMM buffer to calculate the signature
  CopyMem ((VOID *) &(TrustedChannelWriteRequest->Data[0]), Data, DataSize);

  // Update the local buffer with the IndexContext if provided
  if (IndexContext != NULL) {
    Status = CseVariableStorageIoUpdateDataWithContext (
               CseVariableStorageStore,
               mCseIndexQueueWriteBuffer,
               mCseCommandQueueWriteRequestProducerIndex,
               (VOID *) &(TrustedChannelWriteRequest->Data[0]),
               DataSize,
               IndexContext
               );
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  Status = mHeciTrustedChannelProtocol->UpdateTrustedHeader (
                                          (VOID *) &(TrustedChannelWriteRequest->Header.TrustedChannelMessage),
                                          sizeof (BIOS_STORAGE_TRUSTED_CHANNEL_REQUEST),
                                          (UINT32) DataSize
                                          );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "An error occurred updating the trusted header.\n"));
    return Status;
  }
  DEBUG ((
    DEBUG_INFO,
    "  Signature           = 0x%08x\n",
    TrustedChannelWriteRequest->Header.TrustedChannelMessage.Header.TrustedHeader.Signature
    ));
  DEBUG ((
    DEBUG_INFO,
    "  Monotonic Counter   = 0x%08x\n",
    TrustedChannelWriteRequest->Header.TrustedChannelMessage.Header.TrustedHeader.MonotonicCounter
    ));

  return EFI_SUCCESS;
}

/**
  Sends a write message request for a General Data CSE Variable Storage area with the Trusted Channel.

  @param[in]  CseVariableStorageStore     A pointer to a structure CSE Variable Storage Store structure.
  @param[in]  Data                        A pointer to a buffer of data to write.
  @param[in]  DataSize                    The length in bytes of data to write.
  @param[in]  Offset                      The offset in bytes from the base of the write area to write.
  @param[in]  IndexContext                A structure with the index context for the variable being written.

  @retval     EFI_SUCCESS                 The data was sent successfully.
  @retval     EFI_INVALID_PARAMETER       A parameter to the function was invalid such as a NULL pointer.
  @retval     EFI_BUFFER_TOO_SMALL        The data size requested exceeds available buffer space.
  @retval     EFI_NOT_READY               The required interfaces are not available for communication at this time.
  @retval     EFI_SECURITY_VIOLATION      A security violation occurred processing the request.
  @retval     EFI_DEVICE_ERROR            An error occurred communicating with the HECI device.
  @retval     Others                      An error occurred causing the communication operation to be aborted.

**/
EFI_STATUS
EFIAPI
CseVariableStorageGeneralDataWriteTrustedChannelIoSend (
  IN  CONST  CSE_VARIABLE_STORAGE_STORE         *CseVariableStorageStore,
  IN  CONST  VOID                               *Data,
  IN         UINTN                              DataSize,
  IN         UINT32                             Offset,
  IN  CONST  CSE_VARIABLE_STORAGE_INDEX_CONTEXT *IndexContext OPTIONAL
  )
{
  EFI_STATUS                    Status;
  CSE_VARIABLE_STORAGE_REQUEST  *RequestMsg;
  UINT32                        MessageSendLength;

  if (CseVariableStorageStore == NULL || Data == NULL) {
    return EFI_INVALID_PARAMETER;
  } else if (!IsReadyForTransaction ()) {
    return EFI_NOT_READY;
  }

  RequestMsg = mCseCommandQueueWriteBuffer[mCseCommandQueueWriteRequestProducerIndex];

  Status =  CseVariableStorageGeneralDataWriteTrustedChannelIoGetMessage (
              CseVariableStorageStore,
              Data,
              DataSize,
              Offset,
              RequestMsg,
              IndexContext
              );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "An error occurred creating the request message. Status = %r.\n", Status));
    goto ExitWithError;
  }
  ZeroMem (mCseCommandQueueRuntimeDataBufferPtr, mCseCommandQueueRuntimeDataBufferAddress.BufferLength);
  CopyMem (
    (VOID *) ((UINT8 *) mCseCommandQueueRuntimeDataBufferPtr + EFI_PAGE_SIZE),
    (VOID *) &(RequestMsg->Data[0]),
    DataSize
    );

  // The write request buffer will be reused to hold the response
  MessageSendLength = sizeof (BIOS_STORAGE_TRUSTED_CHANNEL_REQUEST);

  Status = mHeciProtocol->SendMsg (
                            CSE_VARIABLE_STORAGE_CMD_QUEUE_TRUSTED_HECI_DEVICE,
                            (UINT32 *) &(RequestMsg->Header.TrustedChannelMessage),
                            MessageSendLength,
                            BIOS_FIXED_HOST_ADDR,
                            HECI_BIOS_STORAGE_MESSAGE_ADDR
                            );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "An error was returned from the HECI protocol sending the write message.\n"));
    goto ExitWithError;
  }

  // Clear the request message before reading the response
  ZeroMem (&(RequestMsg->Header.TrustedChannelMessage), (UINTN) MessageSendLength);

  return Status;

ExitWithError:
  ZeroMem (mCseCommandQueueRuntimeDataBufferPtr, mCseCommandQueueRuntimeDataBufferAddress.BufferLength);
  ZeroMem (
    mCseCommandQueueWriteBuffer[mCseCommandQueueWriteRequestProducerIndex],
    sizeof (BIOS_STORAGE_TRUSTED_CHANNEL_BUFFER)
    );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "An error occurred in the trusted channel write command. Status = %r\n", Status));
  }

  return Status;
}

/**
  Receives a write message response for a General Data CSE Variable Storage area with the Trusted Channel.

  @param[in]  Blocking                    Determines whether execution blocks for the response message.

  @retval     EFI_SUCCESS                 The data was received successfully.
  @retval     EFI_INVALID_PARAMETER       A parameter to the function was invalid such as a NULL pointer.
  @retval     EFI_SECURITY_VIOLATION      A security violation occurred processing the request.
  @retval     EFI_DEVICE_ERROR            An error occurred communicating with the HECI device.
  @retval     EFI_TIMEOUT                 A timeout occurred waiting for a HECI message response.
  @retval     Others                      An error occurred causing the communication operation to be aborted.

**/
EFI_STATUS
EFIAPI
CseVariableStorageGeneralDataWriteTrustedChannelIoReceive (
  IN         BOOLEAN                      Blocking
  )
{
  EFI_STATUS                              Status;
  EFI_STATUS                              Status2;
  BIOS_STORAGE_TRUSTED_CHANNEL_RESPONSE   *ResponseMsg;
  UINT32                                  MessageReceiveLength;
  BOOLEAN                                 IsVerificationSuccessful = FALSE;

  MessageReceiveLength  = sizeof (BIOS_STORAGE_TRUSTED_CHANNEL_RESPONSE);
  ResponseMsg = (BIOS_STORAGE_TRUSTED_CHANNEL_RESPONSE *)
                  mCseCommandQueueWriteBuffer[mCseCommandQueueWriteRequestProducerIndex];

  DEBUG ((DEBUG_INFO, "Waiting for the write message response to be ready...\n"));

  Status = mHeciProtocol->ReadMsg (
                            CSE_VARIABLE_STORAGE_CMD_QUEUE_TRUSTED_HECI_DEVICE,
                            ((Blocking) ? BLOCKING : NON_BLOCKING),
                            (UINT32 *) ResponseMsg,
                            &MessageReceiveLength
                            );
  if (Status == EFI_TIMEOUT && !Blocking) {
    return Status;
  } else if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "An error was returned from the HECI protocol getting the write message response.\n"));
    goto Exit;
  } else if (ResponseMsg->Header.Status != BIOS_STORAGE_STATUS_SUCCESS) {
    DEBUG ((
      DEBUG_ERROR,
      "Error in response status. The response status value is 0x%x.\n",
      ResponseMsg->Header.Status
      ));
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }
  DEBUG ((DEBUG_INFO, "Total message receive length = 0x%x.\n", MessageReceiveLength));

  if (MessageReceiveLength != sizeof (BIOS_STORAGE_TRUSTED_CHANNEL_RESPONSE)) {
    ASSERT (MessageReceiveLength == sizeof (BIOS_STORAGE_TRUSTED_CHANNEL_RESPONSE));
    Status = EFI_DEVICE_ERROR;
    goto Exit;
  }

  DEBUG ((DEBUG_INFO, "Verifying the trusted channel write response header.\n"));
  Status = mHeciTrustedChannelProtocol->VerifyTrustedHeader (
             (VOID *) ResponseMsg,
             MessageReceiveLength,
             &IsVerificationSuccessful
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "An error occurred verifying the trusted header.\n"));
    goto Exit;
  } else if (!IsVerificationSuccessful) {
    DEBUG ((EFI_D_ERROR, "HMAC verification failed for the write response header!\n"));
    Status = EFI_SECURITY_VIOLATION;
    goto Exit;
  }
  DEBUG ((DEBUG_INFO, "HMAC verification succeeded.\n"));
  DEBUG ((DEBUG_INFO, "Trusted channel write message successfully completed.\n"));

Exit:
  ZeroMem (mCseCommandQueueRuntimeDataBufferPtr, mCseCommandQueueRuntimeDataBufferAddress.BufferLength);
  ZeroMem (
    mCseCommandQueueWriteBuffer[mCseCommandQueueWriteRequestProducerIndex],
    sizeof (BIOS_STORAGE_TRUSTED_CHANNEL_BUFFER)
    );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "An error occurred in the trusted channel write command. Status = %r\n", Status));
    Status2 = mHeciTrustedChannelProtocol->DecrementMonotonicCount (1);
    ASSERT_EFI_ERROR (Status2);
  }

  return Status;
}

/**
  Writes data to a General Data CSE Variable Storage area with the Trusted Channel.

  @param[in]  CseVariableStorageStore     A pointer to a structure CSE Variable Storage Store structure.
  @param[in]  Data                        A pointer to a buffer of data to write.
  @param[in]  DataSize                    The length in bytes of data to write.
  @param[in]  Offset                      The offset in bytes from the base of the write area to write.
  @param[in]  IndexContext                A structure with the index context for the variable being written.

  @retval     EFI_SUCCESS                 The data was written successfully.
  @retval     EFI_INVALID_PARAMETER       A parameter to the function was invalid such as a NULL pointer.
  @retval     EFI_BUFFER_TOO_SMALL        The data size requested exceeds available buffer space.
  @retval     EFI_NOT_READY               The required interfaces are not available for communication at this time.
  @retval     EFI_SECURITY_VIOLATION      A security violation occurred processing the request.
  @retval     EFI_DEVICE_ERROR            An error occurred communicating with the HECI device.
  @retval     EFI_TIMEOUT                 A timeout occurred waiting for a HECI message response.
  @retval     Others                      An error occurred causing the communication operation to be aborted.

**/
EFI_STATUS
EFIAPI
CseVariableStorageGeneralDataWriteTrustedChannelIo (
  IN  CONST  CSE_VARIABLE_STORAGE_STORE           *CseVariableStorageStore,
  IN  CONST  VOID                                 *Data,
  IN         UINTN                                DataSize,
  IN         UINT32                               Offset,
  IN  CONST  CSE_VARIABLE_STORAGE_INDEX_CONTEXT   *IndexContext OPTIONAL
  )
{
  EFI_STATUS  Status;

  Status =  CseVariableStorageGeneralDataWriteTrustedChannelIoSend (
              CseVariableStorageStore,
              Data,
              DataSize,
              Offset,
              IndexContext
              );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status =  CseVariableStorageGeneralDataWriteTrustedChannelIoReceive (TRUE);
  return Status;
}

/**
  Writes data to a General Data CSE Variable Storage area.

  The actual write is deferred if CommandInProgress is returned TRUE.

  @param[in]  CseVariableStorageStore A pointer to a structure CSE Variable Storage Store structure.
  @param[in]  Data                    A pointer to a buffer of data to write.
  @param[in]  DataSize                The length in bytes of data to write.
  @param[in]  Offset                  The offset in bytes from the base of the write area to write.
  @param[in]  Truncate                If true and a file system is used, the file will be truncated.
                                      If a file system is not used, this parameter is ignored.
  @param[in]  IndexContext            A structure with the index context for the variable being written.
  @param[out] CommandInProgress       TRUE if the command requires asynchronous I/O and has not completed yet.
                                      If this command is TRUE, then the Data and DataSize are not updated and do
                                      not contain valid data.

  @retval     EFI_SUCCESS             The data was written successfully.
  @retval     EFI_INVALID_PARAMETER   A parameter to the function was invalid such as a NULL pointer.
  @retval     EFI_UNSUPPORTED         The ability to write to CSE is not supported or the requested size is invalid.
  @retval     EFI_ABORTED             The write operation could not be completed successfully.
  @retval     Others                  An error occurred writing the data.

**/
EFI_STATUS
EFIAPI
CseVariableStorageGeneralDataWrite (
  IN  CONST  CSE_VARIABLE_STORAGE_STORE         *CseVariableStorageStore,
  IN  CONST  VOID                               *Data,
  IN         UINTN                              DataSize,
  IN         UINT32                             Offset,
  IN         BOOLEAN                            Truncate,
  IN  CONST  CSE_VARIABLE_STORAGE_INDEX_CONTEXT *IndexContext, OPTIONAL
  OUT        BOOLEAN                            *CommandInProgress OPTIONAL
  )
{
  EFI_STATUS                             Status;
  CSE_VAR_BIOS_STORAGE_REQUEST           CseVariableStorageWriteRequest;
  if (CseVariableStorageStore == NULL || Data == NULL) {
    return EFI_INVALID_PARAMETER;
  } else if (DataSize > CSE_VARIABLE_MAX_DATA_SIZE) {
    DEBUG ((DEBUG_ERROR, "The data size exceeds the maximum data write size.\n"));
    return EFI_UNSUPPORTED;
  }

  if (CommandInProgress != NULL) {
    *CommandInProgress = FALSE;
  }

  if (mTrustedChannelEnabled) {
    if (!mAtRuntime && !mRequireWriteCommandQueue) {
      SetHeciActive (mTrustedHeciBarAddress, mAtRuntime);
      Status =  CseVariableStorageGeneralDataWriteTrustedChannelIo (
                  CseVariableStorageStore,
                  Data,
                  DataSize,
                  Offset,
                  IndexContext
                  );
      SetHeciIdle (mTrustedHeciBarAddress, mAtRuntime);
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "An error occurred during the TC General Data Write IO operation. Status = %r.\n", Status));
        return Status;
      } else if (IndexContext != NULL) {
        Status = CseVariableStorageIoUpdateIndexArea (IndexContext);
      }
    } else {
      if (mCseCommandQueueWriteRequestProducerIndex >= CSE_VAR_STORAGE_CMD_QUEUE_MAX_TOTAL_REQUESTS) {
        DEBUG ((DEBUG_ERROR, "The maximum number of allowed queued write messages has been exceeded.\n"));
        return EFI_OUT_OF_RESOURCES;
      }
      Status =  CseVariableStorageGeneralDataWriteTrustedChannelIoGetMessage (
                  CseVariableStorageStore,
                  Data,
                  DataSize,
                  Offset,
                  mCseCommandQueueWriteBuffer[mCseCommandQueueWriteRequestProducerIndex],
                  IndexContext
                  );
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "An error occurred creating the TC General Data Write IO message. Status = %r.\n", Status));
        return Status;
      }
      CseVariableStorageWriteRequest.Type = BiosStorageTrusted;
      CopyMem (
        (VOID *) &(CseVariableStorageWriteRequest.Buffer.TrustedChannelMessage),
        (VOID *) &(mCseCommandQueueWriteBuffer[mCseCommandQueueWriteRequestProducerIndex]->Header.TrustedChannelMessage),
        sizeof (BIOS_STORAGE_TRUSTED_CHANNEL_REQUEST)
        );

      // Enqueue the request message and wait for the variable driver to invoke Complete()
      Status = CircularBufferEnqueueAligned (
                 &mCseCommandQueue,
                 (CONST UINT8 *) &CseVariableStorageWriteRequest,
                 sizeof (CSE_VAR_BIOS_STORAGE_REQUEST),
                 CSE_VAR_STORAGE_CMD_QUEUE_ALIGNMENT
                 );
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "An error occurred placing a TC General Data Write IO message in the command queue.\n"));
        ZeroMem (
          mCseCommandQueueWriteBuffer[mCseCommandQueueWriteRequestProducerIndex],
          sizeof (CSE_VARIABLE_STORAGE_REQUEST)
          );
      } else {
        if (IndexContext != NULL) {
          CopyMem (
            (VOID *) mCseIndexQueueWriteBuffer[mCseCommandQueueWriteRequestProducerIndex],
            (VOID *) IndexContext,
            sizeof (CSE_VARIABLE_STORAGE_INDEX_CONTEXT)
            );
          mCseIndexQueueWriteBuffer[mCseCommandQueueWriteRequestProducerIndex]->Valid = TRUE;
        }
        mCseCommandQueueWriteRequestProducerIndex++;
        if (CommandInProgress != NULL) {
          *CommandInProgress = TRUE;
        }
        DEBUG ((DEBUG_INFO, "TC General Data Write message queued.\n"));
      }
    }
  } else {
    if (!mAtRuntime && !mRequireWriteCommandQueue) {
      Status =  CseVariableStorageGeneralDataWriteIo (CseVariableStorageStore, Data, DataSize, Offset, IndexContext);
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "An error occurred during the General Data Write IO. Status = %r.\n", Status));
        return Status;
      } else if (IndexContext != NULL) {
        Status = CseVariableStorageIoUpdateIndexArea (IndexContext);
      }
    } else {
      if (mCseCommandQueueWriteRequestProducerIndex >= CSE_VAR_STORAGE_CMD_QUEUE_MAX_TOTAL_REQUESTS) {
        DEBUG ((DEBUG_ERROR, "The maximum number of allowed queued write messages has been exceeded.\n"));
        return EFI_OUT_OF_RESOURCES;
      }
      ZeroMem (
        (VOID *) mCseCommandQueueWriteBuffer[mCseCommandQueueWriteRequestProducerIndex],
        sizeof (CSE_VARIABLE_STORAGE_REQUEST)
        );
      Status =  CseVariableStorageGeneralDataWriteIoGetMessage (
                  CseVariableStorageStore,
                  Data,
                  DataSize,
                  Offset,
                  &(mCseCommandQueueWriteBuffer[mCseCommandQueueWriteRequestProducerIndex]->Header.Message)
                  );
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "An error occurred creating the General Data Write IO message. Status = %r.\n", Status));
        return Status;
      }
      CseVariableStorageWriteRequest.Type = BiosStorageUntrusted;
      CopyMem (
        (VOID *) &(CseVariableStorageWriteRequest.Buffer.Message),
        (VOID *) &(mCseCommandQueueWriteBuffer[mCseCommandQueueWriteRequestProducerIndex]->Header.Message),
        sizeof (BIOS_STORAGE_REQUEST)
        );
      CopyMem (
        (VOID *) &(mCseCommandQueueWriteBuffer[mCseCommandQueueWriteRequestProducerIndex]->Data),
        Data,
        DataSize
        );
      if (IndexContext != NULL) {
        Status = CseVariableStorageIoUpdateDataWithContext (
                   CseVariableStorageStore,
                   mCseIndexQueueWriteBuffer,
                   mCseCommandQueueWriteRequestProducerIndex,
                   (VOID *) &(mCseCommandQueueWriteBuffer[mCseCommandQueueWriteRequestProducerIndex]->Data),
                   DataSize,
                   IndexContext
                   );
        if (EFI_ERROR (Status)) {
          return Status;
        }
      }

      // Enqueue the request message and wait for the variable driver to invoke Complete()
      Status = CircularBufferEnqueueAligned (
                 &mCseCommandQueue,
                 (CONST UINT8 *) &CseVariableStorageWriteRequest,
                 sizeof (CSE_VAR_BIOS_STORAGE_REQUEST),
                 CSE_VAR_STORAGE_CMD_QUEUE_ALIGNMENT
                 );
      if (EFI_ERROR (Status)) {
        DEBUG ((
          DEBUG_ERROR,
          "An error occurred placing a General Data Write IO message in the command queue. Status = %r.\n",
          Status
          ));
        ZeroMem (
          mCseCommandQueueWriteBuffer[mCseCommandQueueWriteRequestProducerIndex],
          sizeof (CSE_VARIABLE_STORAGE_REQUEST)
          );
      } else {
        if (IndexContext != NULL) {
          CopyMem (
            (VOID *) mCseIndexQueueWriteBuffer[mCseCommandQueueWriteRequestProducerIndex],
            (VOID *) IndexContext,
            sizeof (CSE_VARIABLE_STORAGE_INDEX_CONTEXT)
            );
          mCseIndexQueueWriteBuffer[mCseCommandQueueWriteRequestProducerIndex]->Valid = TRUE;
        }

        mCseCommandQueueWriteRequestProducerIndex++;
        if (CommandInProgress != NULL) {
          *CommandInProgress = TRUE;
        }
        DEBUG ((DEBUG_INFO, "General Data Write message queued.\n"));
      }
    }
  }

  return Status;
}
