/** @file
  This file defines the Variable Storage Command Queue module.

  This module installs the EDKII_VARIABLE_STORAGE_IO_COMPLETION_PROTOCOL.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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
#include <Library/BootMediaLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiLib.h>
#include <Library/UefiRuntimeLib.h>

extern VOID                                   *mCseVariableStorageRequestMessageBuffer;
extern VOID                                   *mCseVariableStorageDataBuffer;
extern VOID                                   *mCseVariableStorageDataBufferDataPtr;
extern VOID                                   *mCseVariableStorageDataBufferSmmCommPtr;
extern BIOS_STORAGE_RESPONSE_BUFFER           *mCseVariableStorageResponseBufferPtr;
extern VOID                                   *mCseVariableStorageNoPayloadCommBuffer;
extern VOID                                   *mCseVariableStorageDebugBuffer;
extern HECI_PROTOCOL                          *mHeciProtocol;
extern EFI_SMM_COMMUNICATION_PROTOCOL         *mSmmCommunicationProtocol;
extern BOOLEAN                                mCseVariableStorageSentDataBufferAddress;
extern UINTN                                  mGetOsProxyHeciBaseAddress;
extern UINTN                                  mGetOsProxyHeciBarAddress;
extern UINTN                                  mTrustedHeciBaseAddress;
extern UINTN                                  mTrustedHeciBarAddress;

STATIC EFI_EVENT  mBiosProxyTerminatedEvent;
STATIC EFI_EVENT  mVariableWriteArchitectureEvent;
STATIC EFI_EVENT  mSwitchToTrustedChannelEvent;
STATIC EFI_EVENT  mVirtualAddressChangeEvent;

EDKII_VARIABLE_STORAGE_IO_COMPLETION_PROTOCOL mVariableStorageIoCompletionProtocol = {
  CseVariableStorageIoCompletionComplete,
  CseVariableStorageIoCompletionGetId
};

/**
  Notification function of EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE.

  This is a notification function registered on EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE event.
  It converts pointer to new virtual address.

  @param[in]  Event        Event whose notification function is being invoked.
  @param[in]  Context      Pointer to the notification function's context.

**/
VOID
EFIAPI
CseVariableStorageIoCompletionAddressChangeEvent (
  IN EFI_EVENT             Event,
  IN VOID                  *Context
  )
{
  EfiConvertPointer (0x0, (VOID **) &mCseVariableStorageRequestMessageBuffer);
  EfiConvertPointer (0x0, (VOID **) &mCseVariableStorageDataBuffer);
  EfiConvertPointer (0x0, (VOID **) &mCseVariableStorageDataBufferDataPtr);
  EfiConvertPointer (0x0, (VOID **) &mCseVariableStorageDataBufferSmmCommPtr);
  EfiConvertPointer (0x0, (VOID **) &mCseVariableStorageResponseBufferPtr);
  EfiConvertPointer (0x0, (VOID **) &mCseVariableStorageNoPayloadCommBuffer);
  EfiConvertPointer (0x0, (VOID **) &mCseVariableStorageDebugBuffer);
  EfiConvertPointer (0x0, (VOID **) &mGetOsProxyHeciBaseAddress);
  EfiConvertPointer (0x0, (VOID **) &mGetOsProxyHeciBarAddress);
  EfiConvertPointer (0x0, (VOID **) &mTrustedHeciBaseAddress);
  EfiConvertPointer (0x0, (VOID **) &mTrustedHeciBarAddress);

  EfiConvertPointer (0x0, (VOID **) &mHeciProtocol);
  EfiConvertPointer (0x0, (VOID **) &mSmmCommunicationProtocol);
}

/**
  Initialize the CSE Command Queue module and install a CSE Variable Storage instance of
  the Variable IO Completion Protocol.

  @param[in]  ImageHandle  The image handle.
  @param[in]  SystemTable  The system table.

  @retval     EFI_SUCCESS  The protocol was installed successfully.
  @retval     Others       Protocol could not be installed.
**/
EFI_STATUS
EFIAPI
CseVariableStorageCommandQueueRuntimeDxeInitialize (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS  Status;
  VOID        *EventRegistrationLocal = NULL;

  if (!BootMediaIsUfs ()) {
    return EFI_SUCCESS;
  }

  DEBUG ((EFI_D_INFO, "Initializing the CSE Variable Storage command queue.\n"));

  Status = gBS->LocateProtocol (&gEfiSmmCommunicationProtocolGuid, NULL, (VOID **) &mSmmCommunicationProtocol);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = gBS->LocateProtocol (&gHeciProtocolGuid, NULL, (VOID **) &mHeciProtocol);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  if (!PcdGetBool (PcdEnableVariableConfigInCseRecoveryMode)) {

    //
    // Register for Virtual Address Change notification
    //
    Status = gBS->CreateEventEx (
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    CseVariableStorageIoCompletionAddressChangeEvent,
                    NULL,
                    &gEfiEventVirtualAddressChangeGuid,
                    &mVirtualAddressChangeEvent
                    );
    ASSERT_EFI_ERROR(Status);

    //
    // Register for PCI Enumeration Complete notification
    //
    EfiCreateProtocolNotifyEvent (
      &gEfiPciEnumerationCompleteProtocolGuid,
      TPL_CALLBACK,
      CseVariableStorageCommandQueuePciEnumerationComplete,
      NULL,
      &EventRegistrationLocal
      );

    gBS->CreateEvent (
           EVT_NOTIFY_SIGNAL,
           TPL_NOTIFY,
           SwitchToTrustedChannelEvent,
           NULL,
           &mSwitchToTrustedChannelEvent
           );
  }
  gBS->CreateEvent (
         EVT_NOTIFY_SIGNAL,
         TPL_CALLBACK,
         BiosProxyTerminatedEvent,
         NULL,
         &mBiosProxyTerminatedEvent
         );

  gBS->CreateEvent (
         EVT_NOTIFY_SIGNAL,
         TPL_NOTIFY,
         VariableWriteArchitectureEvent,
         NULL,
         &mVariableWriteArchitectureEvent
         );

  //
  // After Core BIOS Done the untrusted channel is disallowed
  //
  Status = gBS->RegisterProtocolNotify (
                  &gMeCoreBiosDoneProtocolGuid,
                  mSwitchToTrustedChannelEvent,
                  (VOID **) &EventRegistrationLocal
                  );

  //
  // In case Core BIOS Done was not sent disallow the untrusted channel after End of POST
  //
  Status = gBS->RegisterProtocolNotify (
                  &gMeEopDoneProtocolGuid,
                  mSwitchToTrustedChannelEvent,
                  (VOID **) &EventRegistrationLocal
                  );

  //
  // The OS proxy is required after the BIOS proxy is terminated
  //
  Status = gBS->RegisterProtocolNotify (
                  &gBiosStorageProxyTerminatedProtocolGuid,
                  mBiosProxyTerminatedEvent,
                  (VOID **) &EventRegistrationLocal
                  );

  //
  // The read command queue is enabled after the write architectural protocol is installed
  //
  Status = gBS->RegisterProtocolNotify (
                  &gEfiVariableWriteArchProtocolGuid,
                  mVariableWriteArchitectureEvent,
                  (VOID **) &EventRegistrationLocal
                  );

  //
  // Initialize module buffers used for SMM communication
  //
  Status = InitializeModuleBuffers ();
  if (EFI_ERROR (Status)) {
    ASSERT_EFI_ERROR (Status);
    return Status;
  }

  //
  // The CSE variable storage SMM module needs a Runtime DXE buffer for CSE DMA
  //
  Status = CseVariableStorageSendDataBufferAddress ();
  if (!EFI_ERROR (Status)) {
      mCseVariableStorageSentDataBufferAddress = TRUE;
      DEBUG ((DEBUG_INFO, "Runtime DXE data buffer address successfully shared with SMM...\n"));
  }

  //
  // Enable the write command queue immediately since this implementation uses a Runtime DXE BIOS Proxy
  // to handle storage messages for the data.
  //
  Status = SendNoPayloadCommunicateBuffer (SMM_CSE_VARIABLE_STORAGE_FUNCTION_REQUIRE_WRITE_COMMAND_QUEUE);
  ASSERT_EFI_ERROR (Status);

  //
  // Install the Variable IO Completion Protocol instance for CSE Variable Storage
  //
  Status = gBS->InstallProtocolInterface (
                  &ImageHandle,
                  &gEdkiiVariableStorageIoCompletionProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mVariableStorageIoCompletionProtocol
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}