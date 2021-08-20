/** @file
  SMM CSE Variable Storage IO Library Internal Header

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

#ifndef _CSE_VARIABLE_STORAGE_SMM_IO_H_
#define _CSE_VARIABLE_STORAGE_SMM_IO_H_

#include <CseVariableStorage.h>
#include <CseVariableStorageCommandQueue.h>

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BootMediaLib.h>
#include <Library/CircularBufferLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/SmmMemLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/HeciPowerManagementLib.h>
#include <Library/CseVariableStorageIndexLib.h>
#include <Library/CseVariableStorageIoLib.h>

#include <Protocol/CseVariableStorageSupportProtocol.h>
#include <Protocol/HeciProtocol.h>
#include <Protocol/PchSmmPeriodicTimerControl.h>
#include <Protocol/SmmPeriodicTimerDispatch2.h>
#include <Protocol/SmmReadyToLock.h>
#include <Protocol/TrustedChannel.h>
#include <Protocol/VariableStorageSupportProtocol.h>

#pragma pack(push, 1)

typedef struct {
  BIOS_STORAGE_REQUEST_BUFFER             Header;
  UINT8                                   Data[CSE_VARIABLE_MAX_DATA_SIZE];
} CSE_VARIABLE_STORAGE_REQUEST;

typedef struct {
  CSE_VAR_BIOS_STORAGE_REQUEST            Header;
  UINT8                                   Data[CSE_VARIABLE_MAX_DATA_SIZE];
} CSE_VARIABLE_STORAGE_TRUSTED_CHANNEL_RESPONSE;

typedef struct {
  UINT32    AddressLow;
  UINT32    AddressHigh;
  UINTN     BufferLength;
} CSE_VARIABLE_STORAGE_RUNTIME_DATA_BUFFER_ADDRESS;

typedef struct {
  UINT32    ProducerCounter;
  UINT32    ConsumerCounter;
} CSE_VARIABLE_STORAGE_MONOTONIC_COUNTERS;

#pragma pack(pop)

typedef struct {
  BOOLEAN                                  WaitingForReceive;
  EFI_SMM_PERIODIC_TIMER_REGISTER_CONTEXT  RegisterContext;
  EFI_HANDLE                               DispatchHandle;
} CSE_VARIABLE_STORAGE_PERIODIC_SMI_CONTEXT;

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
  );

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
  );

/**
  CSE Variable Storage SMI handler entry.

  This SMI handler provides services for the Runtime DXE CSE Variable Storage Command Queue module

  Caution: This function may receive untrusted input.

  The communicate buffer is external input, so this function will do basic validation.
  Each sub function GetNextWriteBuffer, SetDataBuffer, GetCommandQueue, VerifyResponse, ResetCommandQueue,
  DebugMessage should also do validation based on its own knowledge.

  @param[in]     DispatchHandle               The unique handle assigned to this handler by SmiHandlerRegister().
  @param[in]     RegisterContext              Points to an optional handler context which was specified when the
                                              handler was registered.
  @param[in, out] CommBuffer                  A pointer to a collection of data in memory that will
                                              be conveyed from a non-SMM environment into an SMM environment.
  @param[in, out] CommBufferSize              The size of the CommBuffer.

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
  );

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
  );

/**
  Resets the write request data buffer.

**/
VOID
EFIAPI
ResetWriteRequestDataBuffer (
  VOID
  );

/**
  Determines if fundamental requirements are met to interact using storage proxy messages with CSME.

  @retval     TRUE            Basic requirements are met for a storage proxy transaction.
  @retval     FALSE           The HECI protocol could not be found or the HECI device is not in a normal state.
**/
BOOLEAN
EFIAPI
IsReadyForTransaction (
  VOID
  );

/**
  Validates the data buffer is initialized properly.

  @retval     TRUE            The data buffer is initialized to a valid address.
  @retval     FALSE           The data buffer is not initialized to a valid address.
**/
BOOLEAN
EFIAPI
IsDataBufferValid (
  VOID
  );

/**
  Initializes command queue buffers used in this module.

  @retval        EFI_SUCCESS  The buffers were initialized successfully.
  @retval        Others       The buffers could not be initialized.

**/
EFI_STATUS
EFIAPI
InitializeCommandQueueBuffers (
  VOID
  );

#endif
