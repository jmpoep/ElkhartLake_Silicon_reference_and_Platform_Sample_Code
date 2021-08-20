/** @file
  Internal header file for the CSE Variable Storage Command Queue module.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2006 - 2018 Intel Corporation.

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

@par Specification
**/

#ifndef _CSE_VARIABLE_STORAGE_COMMAND_QUEUE_RUNTIME_DXE_H_
#define _CSE_VARIABLE_STORAGE_COMMAND_QUEUE_RUNTIME_DXE_H_

#include <CseVariableStorageCommandQueue.h>
#include <TrustedChannel.h>

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include <Protocol/HeciProtocol.h>
#include <Protocol/SmmCommunication.h>
#include <Protocol/VariableStorageIoCompletionProtocol.h>

/**
  This function sends a communicate buffer with no payload.

  @retval   EFI_SUCCESS       The function was communicated to SMM successfully.
  @retval   Others            An error occurred during communication with SMM.

**/
EFI_STATUS
EFIAPI
SendNoPayloadCommunicateBuffer (
  IN  UINTN                   Function
  );

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
  );

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
  );

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
  );

/**
  PCI enumeration complete event handler to configure memory ranges in GCD needed at runtime.

  @param[in] Event    Event whose notification function is being invoked.
  @param[in] Context  Pointer to the notification function's context.
**/
VOID
EFIAPI
CseVariableStorageCommandQueuePciEnumerationComplete (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  );

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
  );

/**
  Initializes module buffers used in this module.

  @retval        EFI_SUCCESS                 The buffers were initialized successfully.
  @retval        Others                      The buffers could not be initialized.

**/
EFI_STATUS
EFIAPI
InitializeModuleBuffers (
  VOID
  );

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
  );

/**
  Retrieves a protocol instance-specific GUID.

  Returns a unique GUID per EDKII_VARIABLE_STORAGE_IO_COMPLETION_PROTOCOL instance.

  @param[in]     This                     A pointer to this protocol instance.
  @param[out]    InstanceGuid             A pointer to an EFI_GUID that is this protocol instance's GUID.

  @retval        EFI_SUCCESS              The protocol instance GUID was returned successfully.
  @retval        EFI_INVALID_PARAMETER    The InstanceGuid parameter provided was NULL.

**/
EFI_STATUS
EFIAPI
CseVariableStorageIoCompletionGetId (
  IN  EDKII_VARIABLE_STORAGE_IO_COMPLETION_PROTOCOL   *This,
  OUT EFI_GUID                                        *InstanceGuid
  );

/**
  Returns when the variable storage IO request is finished (the transaction is complete).

  @param[in]     This                     A pointer to this protocol instance.
  @param[in]     SetVariableIoCompletion  TRUE if Complete() is being called to perform I/O for SetVariable
                                          FALSE if Complete() is being called to perform I/O for GetVariable

  @retval        EFI_SUCCESS              The commands executed successfully.
  @retval        EFI_NOT_READY            The CSE OS proxy driver is not available.
  @retval        Others                   An error occurred executing commands in the command queue.

**/
EFI_STATUS
EFIAPI
CseVariableStorageIoCompletionComplete (
  IN  EDKII_VARIABLE_STORAGE_IO_COMPLETION_PROTOCOL   *This,
  IN  BOOLEAN                                         SetVariableIoCompletion
  );

#endif
