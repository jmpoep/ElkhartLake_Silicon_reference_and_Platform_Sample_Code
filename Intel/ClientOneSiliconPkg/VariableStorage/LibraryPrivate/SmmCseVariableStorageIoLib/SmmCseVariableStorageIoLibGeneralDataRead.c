/** @file
  SMM CSE Variable Storage General Data Read IO Implementation

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

extern BOOLEAN                                          mRequireReadCommandQueue;
extern BOOLEAN                                          mTrustedChannelEnabled;
extern BOOLEAN                                          mAtRuntime;
extern CSE_VARIABLE_STORAGE_RUNTIME_DATA_BUFFER_ADDRESS mCseCommandQueueRuntimeDataBufferAddress;
extern CIRCULAR_BUFFER                                  mCseCommandQueue;
extern UINTN                                            mCseCommandQueueReadBufferSize;
extern UINTN                                            mTrustedHeciBarAddress;
extern HECI_PROTOCOL                                    *mHeciProtocol;
extern HECI_TRUSTED_CHANNEL_PROTOCOL                    *mHeciTrustedChannelProtocol;
extern UINTN                                            *mCseCommandQueueRuntimeDataBufferPtr;
extern VOID                                             *mCseCommandQueueReadBuffer;

/**
  Constructs a General Data Storage Read request message.

  @param[in]      CseVariableStorageStore     A pointer to a structure CSE Variable Storage Store structure.
  @param[in]      DataSize                    The length in bytes of data to read.
  @param[in]      Offset                      The offset in bytes from the base of the read area to begin reading.
  @param[out]     ReadMsg                     A pointer to the request message

  @retval         EFI_SUCCESS                 The read message was constructed successfully.
  @retval         EFI_INVALID_PARAMETER       A parameter to the function was invalid such as a NULL pointer.
  @retval         EFI_UNSUPPORTED             The requested size exceeds the allowable limit.
  @retval         EFI_NOT_READY               The required interfaces are not available for communication at this time.
  @retval         EFI_SECURITY_VIOLATION      A security violation occurred processing the request.
  @retval         Others                      An error occurred constructing the read message.

**/
EFI_STATUS
EFIAPI
CseVariableStorageGeneralDataReadIoGetMessage (
  IN  CONST  CSE_VARIABLE_STORAGE_STORE           *CseVariableStorageStore,
  IN         UINTN                                DataSize,
  IN         UINT32                               Offset,
  OUT        BIOS_STORAGE_REQUEST                 *ReadMsg
  )
{
  if (CseVariableStorageStore == NULL) {
    return EFI_INVALID_PARAMETER;
  } else if (DataSize > CSE_VARIABLE_MAX_DATA_SIZE) {
    return EFI_UNSUPPORTED;
  } else if (Offset > CseVariableStorageStore->Info.MaximumSize) {
    return EFI_INVALID_PARAMETER;
  } else if (!IsDataBufferValid ()) {
    return EFI_SECURITY_VIOLATION;
  }

  // Initialize the MKHI message header
  ReadMsg->MkhiHeader.Fields.GroupId    = MKHI_MCA_GROUP_ID;
  ReadMsg->MkhiHeader.Fields.Command    = BIOS_STORAGE_READ_CMD;
  ReadMsg->MkhiHeader.Fields.IsResponse = FALSE;
  ReadMsg->MkhiHeader.Fields.Result     = MkhiStatusSuccess;

  // Initialize the message body
  // Note: DMA requires the data buffer provided be 4k-aligned and outside SMRAM
  ReadMsg->Body.Offset                  = CseVariableStorageStore->Info.Offset + Offset;
  ReadMsg->Body.Length                  = (UINT32) DataSize;
  ReadMsg->Body.BufferAddressLow        = mCseCommandQueueRuntimeDataBufferAddress.AddressLow;
  ReadMsg->Body.BufferAddressHigh       = mCseCommandQueueRuntimeDataBufferAddress.AddressHigh;
  ReadMsg->Body.Flags.WritePatternByte  = FALSE;

  DEBUG ((DEBUG_INFO, "Read Message:\n"));
  DEBUG ((DEBUG_INFO, "  Offset              = 0x%08x\n", ReadMsg->Body.Offset));
  DEBUG ((DEBUG_INFO, "  Length              = 0x%08x\n", ReadMsg->Body.Length));
  DEBUG ((DEBUG_INFO, "  Buffer Address Low  = 0x%08x\n", ReadMsg->Body.BufferAddressLow));
  DEBUG ((DEBUG_INFO, "  Buffer Address High = 0x%08x\n", ReadMsg->Body.BufferAddressHigh));

  return EFI_SUCCESS;
}

/**
  Reads data from a General Data CSE Variable Storage area.

  @param[in]      CseVariableStorageStore A pointer to a structure CSE Variable Storage Store structure.
  @param[out]     Data                    A pointer to a buffer that the data should be read into.
  @param[in,out]  DataSize                The length in bytes of data to read on input.
                                          The length in bytes of dapta read on output.
  @param[in]      Offset                  The offset in bytes from the base of the read area to begin reading.

  @retval     EFI_SUCCESS                 The data was read successfully.
  @retval     EFI_INVALID_PARAMETER       A parameter to the function was invalid such as a NULL pointer.
  @retval     EFI_BUFFER_TOO_SMALL        The data size requested exceeds available buffer space.
  @retval     EFI_NOT_READY               The required interfaces are not available for communication at this time.
  @retval     EFI_SECURITY_VIOLATION      A security violation occurred processing the request.
  @retval     EFI_DEVICE_ERROR            An error occurred communicating with the HECI device.
  @retval     Others                      An error occurred causing the communication operation to be aborted.

**/
EFI_STATUS
EFIAPI
CseVariableStorageGeneralDataReadIo (
  IN  CONST  CSE_VARIABLE_STORAGE_STORE   *CseVariableStorageStore,
  OUT        VOID                         *Data,
  IN  OUT    UINTN                        *DataSize,
  IN         UINT32                       Offset
  )
{
  EFI_STATUS                 Status;
  BIOS_STORAGE_BUFFER        *ReadMsg;
  VOID                       *ReadMsgDataBuffer;
  UINTN                      MessageReceiveLength;
  UINT32                     MessageSendLength;
  UINTN                      TotalResponseLength;

  if (Data == NULL || DataSize == NULL) {
    return EFI_INVALID_PARAMETER;
  } else if (!IsReadyForTransaction ()) {
    return EFI_NOT_READY;
  }

  ZeroMem (mCseCommandQueueRuntimeDataBufferPtr, mCseCommandQueueRuntimeDataBufferAddress.BufferLength);

  ReadMsgDataBuffer = (VOID *) ((UINT8 *) mCseCommandQueueRuntimeDataBufferPtr + EFI_PAGE_SIZE);
  ReadMsg = (BIOS_STORAGE_BUFFER *) ((UINT8 *) ReadMsgDataBuffer - sizeof (BIOS_STORAGE_REQUEST));

  Status =  CseVariableStorageGeneralDataReadIoGetMessage (
              CseVariableStorageStore,
              *DataSize,
              Offset,
              &(ReadMsg->Request)
              );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "An error occurred creating the request message. Status = %r.\n", Status));
    goto ExitWithError;
  }

  MessageSendLength    = sizeof (BIOS_STORAGE_REQUEST);
  MessageReceiveLength = mCseCommandQueueRuntimeDataBufferAddress.BufferLength -
                           (EFI_PAGE_SIZE - sizeof (BIOS_STORAGE_RESPONSE));
  TotalResponseLength  = sizeof (BIOS_STORAGE_RESPONSE) + *DataSize;

  Status = mHeciProtocol->SendMsg (
                            CSE_VARIABLE_STORAGE_CMD_QUEUE_UNTRUSTED_HECI_DEVICE,
                            (UINT32 *) ReadMsg,
                            MessageSendLength,
                            BIOS_FIXED_HOST_ADDR,
                            HECI_MCHI_MESSAGE_ADDR
                            );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "An error was returned from the HECI protocol sending the read message.\n"));
    goto ExitWithError;
  }

  DEBUG ((DEBUG_INFO, "Waiting for the read message response to be ready...\n"));

  // Clear the request header in the upper page and pull the ReadMsg pointer back for the response
  ZeroMem (mCseCommandQueueRuntimeDataBufferPtr, EFI_PAGE_SIZE);
  ReadMsg = (BIOS_STORAGE_BUFFER *) ((UINT8 *) ReadMsgDataBuffer - sizeof (BIOS_STORAGE_RESPONSE));

  Status = mHeciProtocol->ReadMsg (
                            CSE_VARIABLE_STORAGE_CMD_QUEUE_UNTRUSTED_HECI_DEVICE,
                            BLOCKING,
                            (UINT32 *) ReadMsg,
                            (UINT32 *) &MessageReceiveLength
                            );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "An error was returned from the HECI protocol getting the read message response.\n"));
    goto ExitWithError;
  } else if (ReadMsg->Response.MkhiHeader.Fields.Result != MkhiStatusSuccess) {
    DEBUG ((
      DEBUG_ERROR,
      "Error in response status. The response status value is 0x%x.\n",
      ReadMsg->Response.MkhiHeader.Fields.Result
      ));
    Status = EFI_DEVICE_ERROR;
    goto ExitWithError;
  } else if (!ReadMsg->Response.MkhiHeader.Fields.IsResponse) {
    DEBUG ((DEBUG_ERROR, "Response bit not set in read message response.\n"));
    goto ExitWithError;
  }
  DEBUG ((DEBUG_INFO, "Total message receive length = 0x%x.\n", MessageReceiveLength));

  // Check that the message response size is valid
  if (MessageReceiveLength != sizeof (BIOS_STORAGE_RESPONSE)) {
    ASSERT (MessageReceiveLength == sizeof (BIOS_STORAGE_RESPONSE));
    Status = EFI_DEVICE_ERROR;
    goto ExitWithError;
  }

  //
  // Copy the data to the user's provided buffer
  //
  DEBUG ((DEBUG_INFO, "Total read message response size: 0x%x bytes.\n", TotalResponseLength));
  DEBUG ((DEBUG_INFO, "Total size of data read: 0x%x bytes.\n", *DataSize));
  CopyMem (
    Data,
    (VOID *) ReadMsgDataBuffer,
    *DataSize
    );
  DEBUG ((DEBUG_INFO, "BIOS storage read message successfully completed.\n"));

  return EFI_SUCCESS;

ExitWithError:
  ZeroMem (mCseCommandQueueRuntimeDataBufferPtr, mCseCommandQueueRuntimeDataBufferAddress.BufferLength);
  *DataSize = 0;

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "An error occurred in the BIOS storage read command. Status = %r\n", Status));
  }

  return Status;
}

/**
  Constructs a General Data Storage Trusted Channel Read request message.

  @param[in]      CseVariableStorageStore     A pointer to a structure CSE Variable Storage Store structure.
  @param[in]      DataSize                    The length in bytes of data to read.
  @param[in]      Offset                      The offset in bytes from the base of the read area to begin reading.
  @param[out]     TrustedChannelReadRequest   A pointer to the request message

  @retval         EFI_SUCCESS                 The read message was constructed successfully.
  @retval         EFI_INVALID_PARAMETER       A parameter to the function was invalid such as a NULL pointer.
  @retval         EFI_UNSUPPORTED             The requested size exceeds the allowable limit.
  @retval         EFI_NOT_READY               The required interfaces are not available for communication at this time.
  @retval         EFI_SECURITY_VIOLATION      A security violation occurred processing the request.
  @retval         Others                      An error occurred constructing the read message.

**/
EFI_STATUS
EFIAPI
CseVariableStorageGeneralDataReadTrustedChannelIoGetMessage (
  IN  CONST  CSE_VARIABLE_STORAGE_STORE           *CseVariableStorageStore,
  IN         UINTN                                DataSize,
  IN         UINT32                               Offset,
  OUT        BIOS_STORAGE_TRUSTED_CHANNEL_REQUEST *TrustedChannelReadRequest
  )
{
  EFI_STATUS    Status;

  if (CseVariableStorageStore == NULL || TrustedChannelReadRequest == NULL) {
    return EFI_INVALID_PARAMETER;
  } else if (DataSize > CSE_VARIABLE_MAX_DATA_SIZE) {
    return EFI_UNSUPPORTED;
  } else if (Offset > CseVariableStorageStore->Info.MaximumSize) {
    return EFI_INVALID_PARAMETER;
  } else if (!IsReadyForTransaction ()) {
    return EFI_NOT_READY;
  } else if (!IsDataBufferValid ()) {
    return EFI_SECURITY_VIOLATION;
  }

  ZeroMem ((VOID *) TrustedChannelReadRequest, sizeof (BIOS_STORAGE_TRUSTED_CHANNEL_REQUEST));

  // Initialize the message body
  // Note: DMA requires the data buffer provided be 4k-aligned and outside SMRAM
  TrustedChannelReadRequest->Body.Offset                             = CseVariableStorageStore->Info.Offset + Offset;
  TrustedChannelReadRequest->Body.Length                             = (UINT32) DataSize;
  TrustedChannelReadRequest->Body.BufferAddressLow                   = mCseCommandQueueRuntimeDataBufferAddress.AddressLow;
  TrustedChannelReadRequest->Body.BufferAddressHigh                  = mCseCommandQueueRuntimeDataBufferAddress.AddressHigh;
  TrustedChannelReadRequest->Body.Flags.WritePatternByte             = FALSE;
  TrustedChannelReadRequest->Header.TrustedHeader.Command.IsResponse = FALSE;
  TrustedChannelReadRequest->Header.TrustedHeader.Command.Id         = BIOS_STORAGE_READ_CMD_TRUSTED_CHANNEL;

  DEBUG ((DEBUG_INFO, "Trusted Channel Read Message:\n"));
  DEBUG ((DEBUG_INFO, "  Offset              = 0x%08x\n", TrustedChannelReadRequest->Body.Offset));
  DEBUG ((DEBUG_INFO, "  Length              = 0x%08x\n", TrustedChannelReadRequest->Body.Length));
  DEBUG ((DEBUG_INFO, "  Buffer Address Low  = 0x%08x\n", TrustedChannelReadRequest->Body.BufferAddressLow));
  DEBUG ((DEBUG_INFO, "  Buffer Address High = 0x%08x\n", TrustedChannelReadRequest->Body.BufferAddressHigh));

  Status = mHeciTrustedChannelProtocol->UpdateTrustedHeader (
                                          (VOID *) TrustedChannelReadRequest,
                                          sizeof (BIOS_STORAGE_TRUSTED_CHANNEL_REQUEST),
                                          0
                                          );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "An error occurred updating the trusted header.\n"));
    return Status;
  }
  DEBUG ((DEBUG_INFO, "  Signature           = 0x%08x\n", TrustedChannelReadRequest->Header.TrustedHeader.Signature));
  DEBUG ((DEBUG_INFO, "  Monotonic Counter   = 0x%08x\n", TrustedChannelReadRequest->Header.TrustedHeader.MonotonicCounter));

  return EFI_SUCCESS;
}

/**
  Reads data from a General Data CSE Variable Storage area with the Trusted Channel.

  @param[in]      CseVariableStorageStore A pointer to a structure CSE Variable Storage Store structure.
  @param[out]     Data                    A pointer to a buffer that the data should be read into.
  @param[in,out]  DataSize                The length in bytes of data to read on input.
                                          The length in bytes of dapta read on output.
  @param[in]      Offset                  The offset in bytes from the base of the read area to begin reading.

  @retval     EFI_SUCCESS                 The data was read successfully.
  @retval     EFI_INVALID_PARAMETER       A parameter to the function was invalid such as a NULL pointer.
  @retval     EFI_BUFFER_TOO_SMALL        The data size requested exceeds available buffer space.
  @retval     EFI_NOT_READY               The required interfaces are not available for communication at this time.
  @retval     EFI_SECURITY_VIOLATION      A security violation occurred processing the request.
  @retval     EFI_DEVICE_ERROR            An error occurred communicating with the HECI device.
  @retval     Others                      An error occurred causing the communication operation to be aborted.

**/
EFI_STATUS
EFIAPI
CseVariableStorageGeneralDataReadTrustedChannelIo (
  IN  CONST  CSE_VARIABLE_STORAGE_STORE   *CseVariableStorageStore,
  OUT        VOID                         *Data,
  IN  OUT    UINTN                        *DataSize,
  IN         UINT32                       Offset
  )
{
  EFI_STATUS                            Status;
  EFI_STATUS                            Status2;
  BIOS_STORAGE_TRUSTED_CHANNEL_BUFFER   *ReadMsgRtDxePtr;
  BIOS_STORAGE_TRUSTED_CHANNEL_BUFFER   *ReadMsgSmmPtr;
  VOID                                  *ReadMsgRtDxeDataBuffer;
  VOID                                  *ReadMsgSmmDataBuffer;
  UINTN                                 MessageReceiveLength;
  UINT32                                MessageSendLength;
  UINTN                                 TotalResponseLength;
  BOOLEAN                               IsVerificationSuccessful = FALSE;

  if (CseVariableStorageStore == NULL || Data == NULL || DataSize == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  ZeroMem (mCseCommandQueueRuntimeDataBufferPtr, mCseCommandQueueRuntimeDataBufferAddress.BufferLength);
  ZeroMem (mCseCommandQueueReadBuffer, mCseCommandQueueReadBufferSize);

  ReadMsgSmmPtr = (BIOS_STORAGE_TRUSTED_CHANNEL_BUFFER *) mCseCommandQueueReadBuffer;

  Status =  CseVariableStorageGeneralDataReadTrustedChannelIoGetMessage (
              CseVariableStorageStore,
              *DataSize,
              Offset,
              &ReadMsgSmmPtr->Request
              );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "An error occurred creating the request message. Status = %r.\n", Status));
    goto ExitWithError;
  }
  MessageSendLength    = sizeof (BIOS_STORAGE_TRUSTED_CHANNEL_REQUEST);
  MessageReceiveLength = mCseCommandQueueRuntimeDataBufferAddress.BufferLength -
                           (EFI_PAGE_SIZE - sizeof (BIOS_STORAGE_TRUSTED_CHANNEL_RESPONSE));
  TotalResponseLength  = sizeof (BIOS_STORAGE_TRUSTED_CHANNEL_RESPONSE) + *DataSize;

  Status = mHeciProtocol->SendMsg (
                            CSE_VARIABLE_STORAGE_CMD_QUEUE_TRUSTED_HECI_DEVICE,
                            (UINT32 *) ReadMsgSmmPtr,
                            MessageSendLength,
                            BIOS_FIXED_HOST_ADDR,
                            HECI_BIOS_STORAGE_MESSAGE_ADDR
                            );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "An error was returned from the HECI protocol sending the read message.\n"));
    goto ExitWithError;
  }

  DEBUG ((DEBUG_INFO, "Waiting for the read message response to be ready...\n"));

  // Pull the pointers back for the response
  ReadMsgSmmDataBuffer = (VOID *) ((UINT8 *) mCseCommandQueueReadBuffer + EFI_PAGE_SIZE);
  ReadMsgSmmPtr = (BIOS_STORAGE_TRUSTED_CHANNEL_BUFFER *) (
                    ((UINT8 *) ReadMsgSmmDataBuffer) - sizeof (BIOS_STORAGE_TRUSTED_CHANNEL_RESPONSE)
                    );
  ReadMsgRtDxeDataBuffer = (VOID *) ((UINT8 *) mCseCommandQueueRuntimeDataBufferPtr + EFI_PAGE_SIZE);
  ReadMsgRtDxePtr = (BIOS_STORAGE_TRUSTED_CHANNEL_BUFFER *) (
                      ((UINT8 *) ReadMsgRtDxeDataBuffer) - sizeof (BIOS_STORAGE_TRUSTED_CHANNEL_RESPONSE)
                      );

  Status = mHeciProtocol->ReadMsg (
                            CSE_VARIABLE_STORAGE_CMD_QUEUE_TRUSTED_HECI_DEVICE,
                            BLOCKING,
                            (UINT32 *) ReadMsgRtDxePtr,
                            (UINT32 *) &MessageReceiveLength
                            );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "An error was returned from the HECI protocol getting the read message response.\n"));
    goto ExitWithError;
  } else if (ReadMsgRtDxePtr->Response.Header.Status != BIOS_STORAGE_STATUS_SUCCESS) {
    DEBUG ((
      DEBUG_ERROR,
      "Error in response status. The response status value is 0x%x.\n",
      ReadMsgRtDxePtr->Response.Header.Status
      ));
    Status = EFI_DEVICE_ERROR;
    goto ExitWithError;
  }
  DEBUG ((DEBUG_INFO, "Total message receive length = 0x%x.\n", MessageReceiveLength));

  // Check that the message response size is valid
  if (MessageReceiveLength != sizeof (BIOS_STORAGE_TRUSTED_CHANNEL_RESPONSE)) {
    ASSERT (MessageReceiveLength == sizeof (BIOS_STORAGE_TRUSTED_CHANNEL_RESPONSE));
    Status = EFI_DEVICE_ERROR;
    goto ExitWithError;
  }

  // Copy the response contents to SMRAM to verify in isolation
  CopyMem ((VOID *) ReadMsgSmmPtr, (VOID *) ReadMsgRtDxePtr, TotalResponseLength);
  ZeroMem (mCseCommandQueueRuntimeDataBufferPtr, mCseCommandQueueRuntimeDataBufferAddress.BufferLength);

  DEBUG ((DEBUG_INFO, "Verifying the trusted channel read response header.\n"));
  Status = mHeciTrustedChannelProtocol->VerifyTrustedHeader (
             (VOID *) ReadMsgSmmPtr,
             (UINT32) TotalResponseLength,
             &IsVerificationSuccessful
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "An error occurred verifying the trusted header.\n"));
    goto ExitWithError;
  } else if (!IsVerificationSuccessful) {
    DEBUG ((EFI_D_ERROR, "HMAC verification failed for the read response header!\n"));
    Status = EFI_SECURITY_VIOLATION;
    goto ExitWithError;
  }
  DEBUG ((DEBUG_INFO, "HMAC verification succeeded.\n"));

  //
  // Copy the data to the user's provided buffer
  //
  DEBUG ((DEBUG_INFO, "Total read message response size: 0x%x bytes.\n", TotalResponseLength));
  DEBUG ((DEBUG_INFO, "Total size of data read: 0x%x bytes.\n", *DataSize));
  CopyMem (
    Data,
    (VOID *) ReadMsgSmmDataBuffer,
    *DataSize
    );
  DEBUG ((DEBUG_INFO, "Trusted channel read message successfully completed.\n"));

  return EFI_SUCCESS;

ExitWithError:
  ZeroMem (mCseCommandQueueRuntimeDataBufferPtr, mCseCommandQueueRuntimeDataBufferAddress.BufferLength);
  ZeroMem (mCseCommandQueueReadBuffer, mCseCommandQueueReadBufferSize);

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "An error occurred in the trusted channel read command. Status = %r\n", Status));
    Status2 = mHeciTrustedChannelProtocol->DecrementMonotonicCount (1);
    ASSERT_EFI_ERROR (Status2);
  }

  return Status;
}

/**
  Reads data from a General Data CSE Variable Storage area.

  The actual read is deferred if CommandInProgress is returned TRUE.

  @param[in]      CseVariableStorageStore A pointer to a structure CSE Variable Storage Store structure.
  @param[out]     Data                    A pointer to a buffer that the data should be read into.
  @param[in,out]  DataSize                The length in bytes of data to read on input.
                                          The length in bytes of dapta read on output.
  @param[in]      Offset                  The offset in bytes from the base of the read area to begin reading.
  @param[out]     CommandInProgress       TRUE if the command requires asynchronous I/O and has not completed yet.
                                          If this command is TRUE, then the Data and DataSize are not updated and do
                                          not contain valid data.

  @retval     EFI_SUCCESS                 The data was read successfully.
  @retval     EFI_INVALID_PARAMETER       A parameter to the function was invalid such as a NULL pointer.
  @retval     EFI_ABORTED                 The read operation could not be completed successfully.
  @retval     Others                      An error occurred reading the data.

**/
EFI_STATUS
EFIAPI
CseVariableStorageGeneralDataRead (
  IN  CONST  CSE_VARIABLE_STORAGE_STORE   *CseVariableStorageStore,
  OUT        VOID                         *Data,
  IN  OUT    UINTN                        *DataSize,
  IN         UINT32                       Offset,
  OUT        BOOLEAN                      *CommandInProgress OPTIONAL
  )
{
  EFI_STATUS                      Status;
  CSE_VAR_BIOS_STORAGE_REQUEST    CseVariableStorageReadRequest;

  if (CseVariableStorageStore == NULL || Data == NULL || DataSize == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (CommandInProgress != NULL) {
    *CommandInProgress = FALSE;
  }
  if (mTrustedChannelEnabled) {
    if (mAtRuntime || !mRequireReadCommandQueue) {
      SetHeciActive (mTrustedHeciBarAddress, mAtRuntime);
      Status =  CseVariableStorageGeneralDataReadTrustedChannelIo (
                  CseVariableStorageStore,
                  Data,
                  DataSize,
                  Offset
                  );
      SetHeciIdle (mTrustedHeciBarAddress, mAtRuntime);
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "An error occurred during the TC General Data Read IO operation. Status = %r.\n", Status));
        return Status;
      }
    } else {
      Status =  CseVariableStorageGeneralDataReadTrustedChannelIoGetMessage (
                  CseVariableStorageStore,
                  *DataSize,
                  Offset,
                  &(CseVariableStorageReadRequest.Buffer.TrustedChannelMessage)
                  );
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "An error occurred creating the TC General Data Read IO message. Status = %r.\n", Status));
        return Status;
      }
      CseVariableStorageReadRequest.Type = BiosStorageTrusted;

      // Enqueue the request message and wait for the variable driver to invoke Complete()
      Status = CircularBufferEnqueueAligned (
                 &mCseCommandQueue,
                 (CONST UINT8* ) &CseVariableStorageReadRequest,
                 sizeof (CSE_VAR_BIOS_STORAGE_REQUEST),
                 CSE_VAR_STORAGE_CMD_QUEUE_ALIGNMENT
                 );
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "An error occurred placing a General Data Read IO message in the command queue.\n"));
      } else {
        DEBUG ((DEBUG_INFO, "General Data Read message queued.\n"));
        if (CommandInProgress != NULL) {
          *CommandInProgress = TRUE;
        }
      }
    }
  } else {
    if (mAtRuntime || !mRequireReadCommandQueue) {
      Status =  CseVariableStorageGeneralDataReadIo (
                  CseVariableStorageStore,
                  Data,
                  DataSize,
                  Offset
                  );
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "An error occurred during the General Data Read IO. Status = %r.\n", Status));
        return Status;
      }
    } else {
      Status =  CseVariableStorageGeneralDataReadIoGetMessage (
                  CseVariableStorageStore,
                  *DataSize,
                  Offset,
                  &(CseVariableStorageReadRequest.Buffer.Message)
                  );
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "An error occurred creating the General Data Read IO message. Status = %r.\n", Status));
        return Status;
      }
      CseVariableStorageReadRequest.Type = BiosStorageUntrusted;

      // Enqueue the request message and wait for the variable driver to invoke Complete()
      Status = CircularBufferEnqueueAligned (
                 &mCseCommandQueue,
                 (CONST UINT8* ) &CseVariableStorageReadRequest,
                 sizeof (CSE_VAR_BIOS_STORAGE_REQUEST),
                 CSE_VAR_STORAGE_CMD_QUEUE_ALIGNMENT
                 );
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "An error occurred placing a General Data Read IO message in the command queue.\n"));
      } else {
        DEBUG ((DEBUG_INFO, "General Data Read message queued.\n"));
        if (CommandInProgress != NULL) {
          *CommandInProgress = TRUE;
        }
      }
    }
  }

  return Status;
}
