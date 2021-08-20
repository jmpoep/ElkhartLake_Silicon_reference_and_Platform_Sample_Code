/**@file
  Touch Panel Driver. Works with all HID I2C - compatible touchpanels

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2018 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:

**/

#include "I2cTouchPanel.h"

#define OPCODE_SET_POWER 0x8
#define POWER_STATE_ON 0x0
#define POWER_STATE_SLEEP 0x1
#define OPCODE_RESET 0x1
#define RESET_REPORT_ID 0x0

EFI_GUID gSupportedTouchPanelGuid = { 0x1bf4b7ae, 0xc199, 0x4f10, { 0xa8, 0xc6, 0xd0, 0xc1, 0xd0, 0x10, 0x98, 0x06 } };

//
// TODO:
// decide how to consume platform-specific support functions (init, interrupt, getHID) :
// - put them in a lib and statically link the lib to driver [current solution], or
// - install them as protocol on touch device's handle, and load them dynamically in driver
//

//
// TODO:
// decide how to show a device with multiple ReportFormats, such as Ntrig device which can work as touchpanel or digitizer:
// - install single AbsPtr protocol on single device, then parse incoming data from all formats. If they have different resolutions,
// internally recalculate coordinates to fit the resolution reported in AbsPtr protocol [current solution]
// - for each ReportFormat create child device and install AbsPtr protocol for each of those children; do not install on parent device;
// this is how it works on Windows
//

///
/// Driver Support EFI Version Protocol instance
///
GLOBAL_REMOVE_IF_UNREFERENCED
EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL gTouchPanelDriverDriverSupportedEfiVersion = {
  sizeof (EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL),
  0x0002001E
};

///
/// Driver Binding Protocol instance
///
GLOBAL_REMOVE_IF_UNREFERENCED EFI_DRIVER_BINDING_PROTOCOL gTouchPanelDriverDriverBinding = {
  TouchPanelDriverDriverBindingSupported,
  TouchPanelDriverDriverBindingStart,
  TouchPanelDriverDriverBindingStop,
  TOUCH_DRIVER_VERSION,
  NULL,
  NULL
};


EFI_I2C_REQUEST_PACKET*
NewRequestPacket (
  UINTN Operations
  )
{
  EFI_I2C_REQUEST_PACKET *NewPacket;
  if (Operations == 0) {
    return NULL;
  }
  NewPacket = AllocateZeroPool (sizeof(EFI_I2C_REQUEST_PACKET) + (Operations -1) * sizeof(EFI_I2C_OPERATION));

  if (NewPacket != NULL) {
    NewPacket->OperationCount = Operations;
  }

  return NewPacket;
}

VOID
DeleteRequestPacket (
  EFI_I2C_REQUEST_PACKET *Packet
  )
{
  FreePool(Packet);
}


/**
  This function resets the pointer device hardware. As part of
  initialization process, the firmware/device will make a quick
  but reasonable attempt to verify that the device is
  functioning. If the ExtendedVerification flag is TRUE the
  firmware may take an extended amount of time to verify the
  device is operating on reset. Otherwise the reset operation is
  to occur as quickly as possible. The hardware verification
  process is not defined by this specification and is left up to
  the platform firmware or driver to implement.

  @param This                 A pointer to the EFI_ABSOLUTE_POINTER_PROTOCOL
                              instance.

  @param ExtendedVerification Indicates that the driver may
                              perform a more exhaustive
                              verification operation of the
                              device during reset.

  @retval EFI_SUCCESS       The device was reset.

  @retval EFI_DEVICE_ERROR  The device is not functioning
                            correctly and could not be reset.

**/
EFI_STATUS
EFIAPI
TouchPanelDriverAbsolutePointerReset (
  IN EFI_ABSOLUTE_POINTER_PROTOCOL *This,
  IN BOOLEAN                       ExtendedVerification
  )
{
  return EFI_UNSUPPORTED;
}

/**
  The GetState() function retrieves the current state of a pointer
  device. This includes information on the active state associated
  with the pointer device and the current position of the axes
  associated with the pointer device. If the state of the pointer
  device has not changed since the last call to GetState(), then
  EFI_NOT_READY is returned. If the state of the pointer device
  has changed since the last call to GetState(), then the state
  information is placed in State, and EFI_SUCCESS is returned. If
  a device error occurs while attempting to retrieve the state
  information, then EFI_DEVICE_ERROR is returned.


  @param This   A pointer to the EFI_ABSOLUTE_POINTER_PROTOCOL
                instance.

  @param State  A pointer to the state information on the
                pointer device.

  @retval EFI_SUCCESS       The state of the pointer device was
                            returned in State.

  @retval EFI_NOT_READY     The state of the pointer device has not
                            changed since the last call to GetState().

  @retval EFI_DEVICE_ERROR  A device error occurred while
                            attempting to retrieve the pointer
                            device's current state.

**/
EFI_STATUS
EFIAPI
TouchPanelDriverAbsolutePointerGetState (
  IN      EFI_ABSOLUTE_POINTER_PROTOCOL  *This,
  IN OUT  EFI_ABSOLUTE_POINTER_STATE     *State
  )
{
  ABSOLUTE_POINTER_DEV     *TouchDev;

  if (State == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  TouchDev  = TOUCH_CONTEXT_FROM_PROTOCOL (This);

  if (!TouchDev->NewStateAvailable) {
    return EFI_NOT_READY;
  }

  //
  // Retrieve touch state from _ABSOLUTE_POINTER_DEV,
  // which was filled by CheckForPress()
  //
  State->CurrentX      = TouchDev->State.CurrentX;
  State->CurrentY      = TouchDev->State.CurrentY;
  State->CurrentZ      = TouchDev->State.CurrentZ;
  State->ActiveButtons = TouchDev->State.ActiveButtons;

  //
  // State data was consumed - clear availability field
  //
  TouchDev->NewStateAvailable   = FALSE;

  return EFI_SUCCESS;
}

/**
  Unloads an image.

  @param  ImageHandle           Handle that identifies the image to be unloaded.

  @retval EFI_SUCCESS           The image has been unloaded.
  @retval EFI_INVALID_PARAMETER ImageHandle is not a valid image handle.

**/
EFI_STATUS
EFIAPI
TouchPanelDriverUnload (
  IN EFI_HANDLE  ImageHandle
  )
{
  EFI_STATUS  Status;
  EFI_HANDLE  *HandleBuffer;
  UINTN       HandleCount;
  UINTN       Index;

  Status = EFI_SUCCESS;

  Status = gBS->LocateHandleBuffer ( AllHandles, NULL, NULL, &HandleCount, &HandleBuffer);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  for (Index = 0; Index < HandleCount; Index++) {
    Status = gBS->DisconnectController (HandleBuffer[Index], ImageHandle, NULL);
  }

  FreePool (HandleBuffer);

  Status = gBS->UninstallMultipleProtocolInterfaces (
                  ImageHandle,
                  &gEfiDriverSupportedEfiVersionProtocolGuid, &gTouchPanelDriverDriverSupportedEfiVersion,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = gBS->UninstallMultipleProtocolInterfaces (
                  ImageHandle,
                  &gEfiDriverBindingProtocolGuid,  &gTouchPanelDriverDriverBinding,
                  &gEfiComponentNameProtocolGuid,  &gTouchPanelDriverComponentName,
                  &gEfiComponentName2ProtocolGuid, &gTouchPanelDriverComponentName2,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return EFI_SUCCESS;
}

/**
  This is the declaration of an EFI image entry point. This entry point is
  the same for UEFI Applications, UEFI OS Loaders, and UEFI Drivers including
  both device drivers and bus drivers.

  @param  ImageHandle           The firmware allocated handle for the UEFI image.
  @param  SystemTable           A pointer to the EFI System Table.

  @retval EFI_SUCCESS           The operation completed successfully.
  @retval Others                An unexpected error occurred.
**/
EFI_STATUS
EFIAPI
TouchPanelDriverEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS    Status;

  //
  // Install UEFI Driver Model protocol(s).
  //
  Status = EfiLibInstallDriverBindingComponentName2 (
             ImageHandle,
             SystemTable,
             &gTouchPanelDriverDriverBinding,
             ImageHandle,
             &gTouchPanelDriverComponentName,
             &gTouchPanelDriverComponentName2
             );
  ASSERT_EFI_ERROR (Status);

  //
  // Install Driver Supported EFI Version Protocol onto ImageHandle
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiDriverSupportedEfiVersionProtocolGuid, &gTouchPanelDriverDriverSupportedEfiVersion,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  Looks for controllers which declare the EFI_I2C_IO_PROTOCOL and match the device path
  supplied by the silicon vendor or third party I2C driver writer to the platform integrator.

  @param[in]  This                 A pointer to the EFI_DRIVER_BINDING_PROTOCOL instance.
  @param[in]  ControllerHandle     The handle of the controller to test. This handle
                                   must support a protocol interface that supplies
                                   an I/O abstraction to the driver.
  @param[in]  RemainingDevicePath  A pointer to the remaining portion of a device path.  This
                                   parameter is ignored by device drivers, and is optional for bus
                                   drivers. For bus drivers, if this parameter is not NULL, then
                                   the bus driver must determine if the bus controller specified
                                   by ControllerHandle and the child controller specified
                                   by RemainingDevicePath are both supported by this
                                   bus driver.

  @retval EFI_SUCCESS              The device specified by ControllerHandle and
                                   RemainingDevicePath is supported by the driver specified by This.
  @retval EFI_ALREADY_STARTED      The device specified by ControllerHandle and
                                   RemainingDevicePath is already being managed by the driver
                                   specified by This.
  @retval EFI_ACCESS_DENIED        The device specified by ControllerHandle and
                                   RemainingDevicePath is already being managed by a different
                                   driver or an application that requires exclusive access.
                                   Currently not implemented.
  @retval EFI_UNSUPPORTED          The device specified by ControllerHandle and
                                   RemainingDevicePath is not supported by the driver specified by This.
**/
EFI_STATUS
EFIAPI
TouchPanelDriverDriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath OPTIONAL
  )
{
  EFI_STATUS                    Status;
  EFI_I2C_IO_PROTOCOL           *I2cIoProtocol;

  //
  // Open protocol by driver to obtain device guid
  //
  Status = gBS->OpenProtocol(
    ControllerHandle,
    &gEfiI2cIoProtocolGuid,
    (VOID **)&I2cIoProtocol,
    This->DriverBindingHandle,
    ControllerHandle,
    EFI_OPEN_PROTOCOL_BY_DRIVER
    );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Compare the known GUID with the GUID pointed to by the DeviceGuid field
  //
  if (CompareGuid (&gSupportedTouchPanelGuid, I2cIoProtocol->DeviceGuid)) {
    DEBUG((DEBUG_INFO, "TouchPanel Supported: DeviceGuid = %g\n", I2cIoProtocol->DeviceGuid));
    Status = gBS->CloseProtocol (ControllerHandle, &gEfiI2cIoProtocolGuid, This->DriverBindingHandle, ControllerHandle);
    if (EFI_ERROR (Status)) {
      return Status;
    }
    return EFI_SUCCESS;
  }

  gBS->CloseProtocol (ControllerHandle, &gEfiI2cIoProtocolGuid, This->DriverBindingHandle, ControllerHandle);
  return EFI_UNSUPPORTED;
}


/**
  Starts touchpanel device controller.
  If initialization completes successfully, this driver will install AbsolutePointer protocol
  on this device. This protocol can be further used for features such as virtual keyboard.

  Initialization steps:
  - Call init function supplied from platform-specific lib to initialize hardware
  - Read device's HID descriptor, according to Microsoft's HID over I2C specification
  - Using data from HID descriptor, build a table of input descriptors. A single HID device may
    produce data in more than 1 format and each needs to be parsed differently.

  Device context caches one touch event. Cache gets invalidated when its data is consumed by calling
  GetState() from AbsolutePointer protocol.
  Driver checks device's interrupt and potentially retrieves new touch data only if
  cache is empty and either GetState() was called or a periodic timer event was triggered.
  When new data is retrieved from device, absolute pointer's WaitForInput event gets signalled
  to inform users of this protocol that new data is available.
  Such construction allows the following uses of Absolute Pointer protocol:
  - consumer calls gBS->WaitForEvent on AbsPtr's WaitForEvent event, then calls GetState which is
    guaranteed to contain valid data (the suggested way of using AbsolutePointer protocol)
  - consumer calls gBS->checkEvent on AbsPtr's WaitForevent event, and if it returned success then
    consumer may call Getstate() which is guaranteed to contain valid data
  - consumer calls GetState() without bothering with events; GetState() either returns valid data
    or an error

  @param[in]  This                 A pointer to the EFI_DRIVER_BINDING_PROTOCOL instance.
  @param[in]  ControllerHandle     The handle of the controller to start. This handle
                                   must support I2C protocol interface.
  @param[in]  RemainingDevicePath  ignored

  @retval EFI_SUCCESS              The device was started.
  @retval EFI_DEVICE_ERROR         The device could not be started due to a device error.Currently not implemented.
  @retval EFI_OUT_OF_RESOURCES     The request could not be completed due to a lack of resources.
  @retval Others                   The driver failded to start the device.

**/
EFI_STATUS
EFIAPI
TouchPanelDriverDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath OPTIONAL
  )
{
  ABSOLUTE_POINTER_DEV            *TouchDev;
  EFI_I2C_IO_PROTOCOL             *I2cIoProtocol;
  EFI_STATUS                      Status;

  DEBUG ((DEBUG_INFO, "TOUCH start\n"));

  Status = gBS->OpenProtocol (
                  ControllerHandle,
                  &gEfiI2cIoProtocolGuid,
                  (VOID **)&I2cIoProtocol,
                  This->DriverBindingHandle,
                  ControllerHandle,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Allocate the driver context
  //
  TouchDev = AllocateZeroPool (sizeof (ABSOLUTE_POINTER_DEV));
  if (TouchDev == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto ErrorExit;
  }

  TouchDev->ControllerHandle = ControllerHandle;
  TouchDev->Signature = TOUCH_SIGNATURE;

  TouchDev->I2cIoProtocol = I2cIoProtocol;

  TouchDev->AbsolutePointerProtocol.GetState = TouchPanelDriverAbsolutePointerGetState;
  TouchDev->AbsolutePointerProtocol.Reset    = TouchPanelDriverAbsolutePointerReset;
  TouchDev->AbsolutePointerProtocol.Mode     = &(TouchDev->Mode);

  //
  // platform-specific functions, supplied either as statically linked lib
  // or a protocol installed on device handle. Current implementation: lib
  //
  TouchDev->HidI2cPlatformSupport.GetHidRegisterAddress = HidI2cGetHidRegisterAddress;
  TouchDev->HidI2cPlatformSupport.CheckInterrupt = HidI2cCheckInterrupt;
  TouchDev->HidI2cPlatformSupport.Initialize = HidI2cInitialize;

  //
  // Initialize hardware in platform-specific way
  //
  TouchDev->HidI2cPlatformSupport.Initialize(TouchDev->ControllerHandle);

  AddUnicodeString2 (
    "eng",
    gTouchPanelDriverComponentName.SupportedLanguages,
    &TouchDev->ControllerNameTable,
    L"HID-compatible Touchpanel Driver",
    TRUE
    );
  AddUnicodeString2 (
    "en",
    gTouchPanelDriverComponentName2.SupportedLanguages,
    &TouchDev->ControllerNameTable,
    L"HID-compatible Touchpanel Driver",
    FALSE
    );

  Status = gBS->CreateEvent (
                  EVT_NOTIFY_WAIT,
                  TPL_CALLBACK,
                  CheckDataAvailableCallback,
                  (VOID*)TouchDev,
                  &TouchDev->AbsolutePointerProtocol.WaitForInput
                  );
  if (EFI_ERROR (Status)) {
    Status = EFI_OUT_OF_RESOURCES;
    goto ErrorExit;
  }

  //
  // Initialize device by reading its HID descriptor
  //
  Status = TouchDevInit (TouchDev);
  if (EFI_ERROR (Status)) {
    goto ErrorExit;
  }

  Status = gBS->CreateEvent (EVT_TIMER | EVT_NOTIFY_SIGNAL, TPL_CALLBACK, CheckDataAvailableCallback, (VOID*)TouchDev, &TouchDev->PollingEvent);
  if (EFI_ERROR(Status)) {
    goto ErrorExit;
  }

  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ControllerHandle,
                  &gEfiAbsolutePointerProtocolGuid,
                  &TouchDev->AbsolutePointerProtocol,
                  &gEfiTouchPanelGuid,
                  NULL,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto ErrorExit;
  }

  return Status;

ErrorExit:
    DEBUG ((DEBUG_ERROR, "TOUCH start exiting, %r\n", Status));

  if ((TouchDev != NULL) && (TouchDev->AbsolutePointerProtocol.WaitForInput != NULL)) {
    gBS->CloseEvent (TouchDev->AbsolutePointerProtocol.WaitForInput);
  }

  if ((TouchDev != NULL) && (TouchDev->ControllerNameTable != NULL)) {
    FreeUnicodeStringTable (TouchDev->ControllerNameTable);
  }

  if (TouchDev != NULL) {
    FreePool (TouchDev);
  }

  gBS->CloseProtocol (
         ControllerHandle,
         &gEfiI2cIoProtocolGuid,
         This->DriverBindingHandle,
         ControllerHandle
         );

  return Status;

}


/**
  Stops a device controller or a bus controller.

  The Stop() function is designed to be invoked from the EFI boot service DisconnectController().
  As a result, much of the error checking on the parameters to Stop() has been moved
  into this common boot service. It is legal to call Stop() from other locations,
  but the following calling restrictions must be followed, or the system behavior will not be deterministic.
  1. ControllerHandle must be a valid EFI_HANDLE that was used on a previous call to this
     same driver's Start() function.
  2. The first NumberOfChildren handles of ChildHandleBuffer must all be a valid
     EFI_HANDLE. In addition, all of these handles must have been created in this driver's
     Start() function, and the Start() function must have called OpenProtocol() on
     ControllerHandle with an Attribute of EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER.

  @param[in]  This              A pointer to the EFI_DRIVER_BINDING_PROTOCOL instance.
  @param[in]  ControllerHandle  A handle to the device being stopped. The handle must
                                support a bus specific I/O protocol for the driver
                                to use to stop the device.
  @param[in]  NumberOfChildren  The number of child device handles in ChildHandleBuffer.
  @param[in]  ChildHandleBuffer An array of child handles to be freed. May be NULL
                                if NumberOfChildren is 0.

  @retval EFI_SUCCESS           The device was stopped.
  @retval EFI_DEVICE_ERROR      The device could not be stopped due to a device error.

**/
EFI_STATUS
EFIAPI
TouchPanelDriverDriverBindingStop (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   ControllerHandle,
  IN UINTN                        NumberOfChildren,
  IN EFI_HANDLE                   *ChildHandleBuffer OPTIONAL
  )
{
  ABSOLUTE_POINTER_DEV            *TouchDev;
  EFI_STATUS                      Status;

  //
  // Unload any higher level drivers
  //
  Status = gBS->OpenProtocol (
                  ControllerHandle,
                  &gEfiAbsolutePointerProtocolGuid,
                  (VOID **)&TouchDev,
                  This->DriverBindingHandle,
                  ControllerHandle,
                  EFI_OPEN_PROTOCOL_BY_DRIVER | EFI_OPEN_PROTOCOL_EXCLUSIVE
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "INFO - TOUCH driver still in use, Status: %r\n", Status));
    return EFI_SUCCESS;
  }

  //
  // Done with the upper level protocol
  //
  gBS->CloseProtocol (
         ControllerHandle,
         &gEfiAbsolutePointerProtocolGuid,
         This->DriverBindingHandle,
         ControllerHandle
         );

  //
  // Disable touch support
  //
  Status = gBS->UninstallMultipleProtocolInterfaces (
                  ControllerHandle,
                  &gEfiAbsolutePointerProtocolGuid,
                  &TouchDev->AbsolutePointerProtocol,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ERROR - TOUCH driver failed to unload upper protocol, Status: %r\n", Status));
    return Status;
  }

  gBS->CloseEvent (TouchDev->AbsolutePointerProtocol.WaitForInput);

  gBS->CloseProtocol (
         ControllerHandle,
         &gEfiI2cIoProtocolGuid,
         This->DriverBindingHandle,
         ControllerHandle
         );

  FreeUnicodeStringTable (TouchDev->ControllerNameTable);

  FreePool (TouchDev);

  return Status;
}

/**
  Helper function that concatenates two 8-bit variables into 16bit value
**/
UINT16
GetLength (
  IN UINT8 Lsb,
  IN UINT8 Msb
  )
{
  return ((Msb<<8) + Lsb);
}

/**
  Event used for first read HID Descriptor transaction from Touch Device

  @param[in]  Event    Event called by I2C HOST on the I2C request completion
  @param[in]  Context  Context passed by the event creator
**/
VOID
EFIAPI
HidDescriptorReceivedEvent (
  IN EFI_EVENT   Event,
  IN VOID        *Context
  )
{
  if ((Event == NULL) || (Context == NULL)) {
    return;
  }
  *((BOOLEAN *) Context) = FALSE;
}

/**
  Get HID descriptor via I2C protocol.

  @param  DriverContext         The code context.

  @retval EFI_SUCCESS           The operation completed successfully.
  @retval EFI_DEVICE_ERROR      Failed to obtain HID Descriptor.
  @retval Others                An unexpected error occurred.
**/
EFI_STATUS
EFIAPI
GetHidDescriptor (
  IN OUT ABSOLUTE_POINTER_DEV  *TouchDev
  )
{
  UINT16                 HidDataLength;
  EFI_STATUS             Status;
  UINT8                  WriteBuffer[2];
  EFI_I2C_REQUEST_PACKET *RequestPacket;
  BOOLEAN                WaitForResponse;
  UINT8                  ExitLoopCounter;
  EFI_EVENT              CallbackEvent;

  WaitForResponse = TRUE;
  ExitLoopCounter = 10;

  WriteBuffer[0] = (UINT8)(TouchDev->HidI2cPlatformSupport.GetHidRegisterAddress(TouchDev->ControllerHandle) & 0xff);
  WriteBuffer[1] = (UINT8)(TouchDev->HidI2cPlatformSupport.GetHidRegisterAddress(TouchDev->ControllerHandle) >> 8) & 0xff;

   Status = gBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_NOTIFY,
                   HidDescriptorReceivedEvent,
                   &WaitForResponse,
                   &CallbackEvent
                   );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "GetHidDescriptor Failed to Create CallbackEvent with Status: %r\n", Status));
    return Status;
  }

  RequestPacket = NewRequestPacket(2);
  if (RequestPacket == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  RequestPacket->Operation[0].Flags = 0;
  RequestPacket->Operation[0].LengthInBytes = 2;
  RequestPacket->Operation[0].Buffer = WriteBuffer;
  RequestPacket->Operation[1].Flags = I2C_FLAG_READ;
  RequestPacket->Operation[1].LengthInBytes = DEFAULT_HID_DESCRIPTOR_LENGTH-2;
  RequestPacket->Operation[1].Buffer = (UINT8*)(&(TouchDev->HidDescriptor));
  TouchDev->I2cIoProtocol->QueueRequest (TouchDev->I2cIoProtocol,0,CallbackEvent,RequestPacket,&Status);
  while (WaitForResponse && (ExitLoopCounter > 0)) {
    gBS->Stall (EFI_TIMER_PERIOD_MILLISECONDS(10));
    ExitLoopCounter--;
  }

  gBS->CloseEvent (CallbackEvent);
  DeleteRequestPacket (RequestPacket);

  if (ExitLoopCounter == 0) {
    DEBUG ((DEBUG_ERROR, "GetHidDescriptor Failed to read hid descriptor in 100ms\n"));
    return EFI_DEVICE_ERROR;
  }

  HidDataLength = GetLength(TouchDev->HidDescriptor.HIDDescLengthLsb, TouchDev->HidDescriptor.HIDDescLengthLsb);
  DeleteRequestPacket (RequestPacket);
  if (HidDataLength == 0 || HidDataLength == 0xFFFF) {
    return EFI_DEVICE_ERROR;
  }

  return Status;
}

/**
  Set HID Power via I2C protocol.

  @param  DriverContext         The code context.

  @retval EFI_SUCCESS           The operation completed successfully.
  @retval Others                An unexpected error occurred.
**/
EFI_STATUS
SetHidPower (
  IN ABSOLUTE_POINTER_DEV *TouchDev
  )
{
  EFI_STATUS             Status;
  UINT8                  WriteBuffer[4];
  EFI_I2C_REQUEST_PACKET *RequestPacket;

  WriteBuffer[0] = TouchDev->HidDescriptor.CommandRegisterLsb;
  WriteBuffer[1] = TouchDev->HidDescriptor.CommandRegisterMsb;
  WriteBuffer[2] = POWER_STATE_ON;
  WriteBuffer[3] = OPCODE_SET_POWER;

  RequestPacket = NewRequestPacket(1);
  if (RequestPacket == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  RequestPacket->Operation[0].Flags = 0;
  RequestPacket->Operation[0].LengthInBytes = 4;
  RequestPacket->Operation[0].Buffer = WriteBuffer;
  Status = TouchDev->I2cIoProtocol->QueueRequest (TouchDev->I2cIoProtocol,0,NULL,RequestPacket,NULL);
  DeleteRequestPacket(RequestPacket);

  return Status;
}

/**
  Set HID Reset via I2C protocol.

  @param  DriverContext         The code context.

  @retval EFI_SUCCESS           The operation completed successfully.
  @retval Others                An unexpected error occurred.
**/
EFI_STATUS
SetHidReset (
  IN ABSOLUTE_POINTER_DEV *TouchDev
  )
{
  EFI_STATUS             Status;
  UINT8                  WriteBuffer[4];
  UINT8                  ReadData[20];
  EFI_I2C_REQUEST_PACKET *RequestPacket;

  Status = EFI_SUCCESS;
  WriteBuffer[0] = TouchDev->HidDescriptor.CommandRegisterLsb;
  WriteBuffer[1] = TouchDev->HidDescriptor.CommandRegisterMsb;
  WriteBuffer[2] = RESET_REPORT_ID;
  WriteBuffer[3] = OPCODE_RESET;

  RequestPacket = NewRequestPacket(2);
  if (RequestPacket == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  RequestPacket->Operation[0].Flags = 0;
  RequestPacket->Operation[0].LengthInBytes = 4;
  RequestPacket->Operation[0].Buffer = WriteBuffer;
  RequestPacket->Operation[1].Flags = I2C_FLAG_READ;
  RequestPacket->Operation[1].LengthInBytes = 20;
  RequestPacket->Operation[1].Buffer = ReadData;
  Status = TouchDev->I2cIoProtocol->QueueRequest (TouchDev->I2cIoProtocol,0,NULL,RequestPacket,NULL);
  DeleteRequestPacket(RequestPacket);

  return Status;
}

/**
  Get new touch data via I2C.

  @param  DriverContext         The Code context.
  @param  *X                    The touch controller report x location.
  @param  *Y                    The touch controller report y location.
  @param  *Z                    The touch controller report z location.
  @param  ActiveButtons         The touch controller report touch/release event.

  @retval EFI_SUCCESS           The operation completed successfully.
  @retval Others                An unexpected error occurred.
**/
EFI_STATUS
GetTouchCoordinates (
  IN     ABSOLUTE_POINTER_DEV  *TouchDev,
  IN OUT UINT16                *X,
  IN OUT UINT16                *Y,
  IN OUT UINT16                *Z,
  IN OUT UINT16                *ActiveButtons
  )
{
  UINT8*                   ReadBuffer;
  UINT32                   InputLength;
  EFI_STATUS               Status = EFI_SUCCESS;
  TOUCH_OUTPUT             Output;
  EFI_I2C_REQUEST_PACKET   *RequestPacket;

  InputLength = GetLength(TouchDev->HidDescriptor.MaxInputLengthLsb, TouchDev->HidDescriptor.MaxInputLengthMsb);
  ReadBuffer = AllocatePool(InputLength);
  if (ReadBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  RequestPacket = NewRequestPacket(1);
  if (RequestPacket == NULL) {
    FreePool(ReadBuffer);
    return EFI_OUT_OF_RESOURCES;
  }

  RequestPacket->Operation[0].Flags = I2C_FLAG_READ;
  RequestPacket->Operation[0].LengthInBytes = InputLength;
  RequestPacket->Operation[0].Buffer = ReadBuffer;
  Status = TouchDev->I2cIoProtocol->QueueRequest (TouchDev->I2cIoProtocol,0,NULL,RequestPacket,NULL);
  DeleteRequestPacket(RequestPacket);
  if (EFI_ERROR (Status)) {
    FreePool(ReadBuffer);
    return Status;
  }

  Output = ParseInput(TouchDev->InputReportTable, ReadBuffer);
  *X = (UINT16)Output.X;
  *Y = (UINT16)Output.Y;
  *Z = 0;
  *ActiveButtons = (UINT16)Output.B;

  FreePool(ReadBuffer);
  return Status;
}

/**
  Check the touch device do send interrupt event.

  @param[in] Event    Event whose notification function is being invoked.
  @param[in] Context  Pointer to the notification function's context,
                      which is implementation-dependent.  Context corresponds
                      to NotifyContext in CreateEventEx().
**/
VOID
EFIAPI
CheckDataAvailableCallback (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  ABSOLUTE_POINTER_DEV *TouchDev;
  UINT16               X;
  UINT16               Y;
  UINT16               Z;
  UINT16               ActiveButtons;

  TouchDev = (ABSOLUTE_POINTER_DEV *)Context;
  if (TouchDev->HidI2cPlatformSupport.CheckInterrupt(TouchDev->ControllerHandle)) {
    if (GetTouchCoordinates(TouchDev, &X, &Y, &Z, &ActiveButtons) == EFI_SUCCESS) {
      TouchDev->NewStateAvailable = TRUE;
      TouchDev->State.CurrentX    = X;
      TouchDev->State.CurrentY    = Y;
      TouchDev->State.CurrentZ    = Z;
      TouchDev->State.ActiveButtons = ActiveButtons? 1:0;
      gBS->SignalEvent(TouchDev->AbsolutePointerProtocol.WaitForInput);
    }
  }
}


/**
  Gets HID descriptor and initializes dictionary for parsing touch input data

  @param  DriverContext         The Code context.

  @retval EFI_SUCCESS           The operation completed successfully.
  @retval Others                An unexpected error occurred.
**/
EFI_STATUS
EFIAPI
TouchDevInit(
  IN ABSOLUTE_POINTER_DEV  *TouchDev
  )
{
  EFI_STATUS Status;

  Status = GetHidDescriptor (TouchDev);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "GetHidDescriptor: %r\n", Status));
    return Status;
  }
  DEBUG ((DEBUG_INFO, "TouchDevInit VendorId 0x%02x.\n",  TouchDev->HidDescriptor.VendorId));
  DEBUG ((DEBUG_INFO, "TouchDevInit ProductId 0x%02x.\n", TouchDev->HidDescriptor.ProductId));

  Status = SetHidPower (TouchDev);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "SetHidPower: %r\n", Status));
    return Status;
  }

  Status = SetHidReset (TouchDev);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "SetHidReset: %r\n", Status));
    return Status;
  }

  Status = ReadInputReportDescriptor (TouchDev);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "ReadInputReportDescriptor: %r\n", Status));
    return Status;
  }

  Status = SetInterruptFrequency (TouchDev);
  return EFI_SUCCESS;

}

/*
  HID's InputReportDescriptor consists of variable length tokens.
  On entry, Descriptor points to InputReportDescriptor's start or a boundary
    between two tokens somewhere inside descriptor. Size means number of bytes
    before end of Descriptor.
  Function returns a single Token.
  On exit, Descriptor points next boundary between tokens, just after the token
    that was returned. Size is decreased by as many bytes as Descriptor pointer
    was moved forward.
  Tokens in Long Item format are only partially supported; they will return
    invalid value but Descriptor pointer and Size will be updated correctly to
    allow further parsing
*/
TOKEN
GetToken (
  IN OUT UINT8** Descriptor,
  IN OUT UINT16* Size
  )
{
  TOKEN  Token;
  UINT16 Length;
  UINT8  DataSize;
  Token.ID = ((**Descriptor)>>2);
  Token.Value = 0;
  DataSize = (**Descriptor)&0x3;

  if (**Descriptor==0xFE) {
    // Long Item format
    Token.ID = *(*Descriptor+2);
    //don't care about value - Long Items are not supported
    Length = *(*Descriptor+1);
    (*Descriptor)+=Length;
    (*Size)-=Length;
    return Token;
  }
  switch(DataSize) {
    case 0:
      Token.Value = 0;
      break;
    case 1:
      Token.Value = *(*Descriptor+1);
      break;
    case 2:
      Token.Value = *(*Descriptor+1) + (*(*Descriptor+2)<<8);
      break;
    case 3:
      Token.Value = *(*Descriptor+1) + ((*(*Descriptor+2))<<8) + ((*(*Descriptor+3))<<16) + ((*(*Descriptor+4))<<24);
      break;
    default: ;
  }
  // move descriptor pointer and decrease size by datasize + 1 byte for ID
  (*Descriptor) += (1+DataSize);
  (*Size) -= (1+DataSize);

  return Token;
}

/*
  Stack contains a set of data retrieved from parsing InputReportDescriptor.
  This function checks if that set of data constitutes a valid InputData
  dictionary, and if so then puts it into ReportTable, table of dictionaries.
  Unless this is the 1st dictionary for a particular device, this means
  allocating new bigger table and deallocating old table
*/
VOID
ExportReport (
  PARSER_STACK* Stack,
  INPUT_REPORT_TABLE* ReportTable
  )
{
  INPUT_REPORT_FORMAT* ArrayOfReports;

  if( Stack->TouchPanelUsage ) {
    ReportTable->TouchPanel = 1;
  }

  if( Stack->TempReport.BitStopX == 0 ||
      Stack->TempReport.BitStopY == 0 ||
      Stack->TempReport.BitStopB == 0 ) {
    DEBUG ((DEBUG_INFO, "ExportReport - report incomplete, aborting\n"));
    return;
  }

  ArrayOfReports = AllocatePool( sizeof(INPUT_REPORT_FORMAT) * (ReportTable->Quantity + 1) );
  ASSERT (ArrayOfReports != NULL);
  if (ArrayOfReports != NULL){
    if (ReportTable->Quantity != 0) {
      CopyMem(ArrayOfReports, ReportTable->Report, sizeof(INPUT_REPORT_FORMAT) * ReportTable->Quantity);
      FreePool (ReportTable->Report);
    }
    ReportTable->Report = ArrayOfReports;
    CopyMem(&(ReportTable->Report[ReportTable->Quantity]), &(Stack->TempReport), sizeof(INPUT_REPORT_FORMAT));
    ReportTable->Quantity++;
  }
}

/*
  Stack is pointer to a not-yet-complete InputReport dictionary.
  This function consumes Token retrieved from InputReportDescriptor stream
  and uses it to update the dictionary.
  Once a dictionary is completed, it calls ExportReport() which puts the
  dictionary in a table of dictionaries. Then it clears internal data
  and prepares to build a new one.
  This implementation of Descriptor parser ignores all types of data except for
  information on how to decode Button presses and X/Y touch coordinates, as this
  is the only info relevant for touchpanels.
*/
VOID
UpdateStack (
  PARSER_STACK* Stack,
  TOKEN Token,
  INPUT_REPORT_TABLE* ReportTable
  )
{
  switch(Token.ID) {
    case USE_PAGE:  Stack->GlobalUsage = Token.Value; break;
    case USAGE:
      if(Token.Value>0xFFFF) { //special case for 32 bit usages - they indicate Usage + Use Page together
        Stack->GlobalUsage = Token.Value >> 16;
        Token.Value = Token.Value & 0xFFFF;
      }
      Stack->Usages++;
      if(Stack->GlobalUsage==DIGITIZER && Token.Value == TIP_SWITCH) { Stack->UsageB = Stack->Usages; }
      if(Stack->GlobalUsage==DESKTOP && Token.Value == X_AXIS) { Stack->UsageX = Stack->Usages; }
      if(Stack->GlobalUsage==DESKTOP && Token.Value == Y_AXIS) { Stack->UsageY = Stack->Usages; }
      if(Stack->GlobalUsage==DIGITIZER && Token.Value == TOUCHPANEL) { Stack->TouchPanelUsage = 1; }
      break;
    case LOG_MIN:  Stack->LogMin = Token.Value; break;
    case LOG_MAX:  Stack->LogMax = Token.Value; break;
    case REP_SIZE:  Stack->ReportSize = Token.Value; break;
    case REP_COUNT:  Stack->ReportCount = Token.Value; break;
    case REPORT_ID:
      ExportReport(Stack, ReportTable);
      Stack->Usages = 0;
      Stack->UsageX = 0;
      Stack->UsageY = 0;
      Stack->UsageB = 0;
      Stack->TempReport.Id = Token.Value;
      Stack->TempReport.LogMaxX = 0;
      Stack->TempReport.LogMinX = 0;
      Stack->TempReport.LogMaxY = 0;
      Stack->TempReport.LogMinY = 0;
      Stack->TempReport.BitStartX = 0;
      Stack->TempReport.BitStopX = 0;
      Stack->TempReport.BitStartY = 0;
      Stack->TempReport.BitStopY = 0;
      Stack->TempReport.BitStartB = 0;
      Stack->TempReport.BitStopB = 0;
      Stack->TempReport.BitsTotal = 0;
      Stack->TouchPanelUsage = 0;
      break;
    case INPUT:
      if (Stack->UsageB != 0 && Stack->ReportCount >= Stack->UsageB) {
        Stack->TempReport.BitStartB = Stack->TempReport.BitsTotal + Stack->ReportSize * (Stack->UsageB - 1);
        Stack->TempReport.BitStopB  = Stack->TempReport.BitsTotal + Stack->ReportSize * (Stack->UsageB);
      }
      if (Stack->UsageX != 0 && Stack->ReportCount >= Stack->UsageX) {
        Stack->TempReport.BitStartX = Stack->TempReport.BitsTotal + Stack->ReportSize * (Stack->UsageX - 1);
        Stack->TempReport.BitStopX  = Stack->TempReport.BitsTotal + Stack->ReportSize * (Stack->UsageX);
        Stack->TempReport.LogMaxX = Stack->LogMax;
        Stack->TempReport.LogMinX = Stack->LogMin;
      }
      if (Stack->UsageY != 0 && Stack->ReportCount >= Stack->UsageY) {
        Stack->TempReport.BitStartY = Stack->TempReport.BitsTotal + Stack->ReportSize * (Stack->UsageY - 1);
        Stack->TempReport.BitStopY  = Stack->TempReport.BitsTotal + Stack->ReportSize * (Stack->UsageY);
        Stack->TempReport.LogMaxY = Stack->LogMax;
        Stack->TempReport.LogMinY = Stack->LogMin;
      }
      Stack->TempReport.BitsTotal += (Stack->ReportSize * Stack->ReportCount);
      // no break here - let code fall down to post-MAIN-tag cleanup
    //these are Main tags. Main tags always cancel all Local tags, which includes Usages
    case OUTPUT:
    case FEATURE:
    case COLLECTION:
    case END_COLLECTION:
      Stack->Usages = 0;
      Stack->UsageB = 0;
      Stack->UsageX = 0;
      Stack->UsageY = 0;
      break;
    case PUSH:
      Stack->GlobalUsageOnStack = Stack->GlobalUsage;
      Stack->ReportSizeOnStack  = Stack->ReportSize;
      Stack->ReportCountOnStack = Stack->ReportCount;
      break;
    case POP:
      Stack->GlobalUsage = Stack->GlobalUsageOnStack;
      Stack->ReportSize  = Stack->ReportSizeOnStack;
      Stack->ReportCount = Stack->ReportCountOnStack;
      break;
    default: ;
  }
}

/*
  Retrieves single bit from multi-byte stream
*/
UINT32
AccessBit (
  UINT8* InputStream,
  UINT32 Bit
  )
{
  return ( ( InputStream[Bit/8] & (1<<(Bit%8)) ) ? 1:0 );
}

VOID
ShowReportTable (
  INPUT_REPORT_TABLE ReportTable
  )
{
  UINT32 i;
  for (i = 0; i < ReportTable.Quantity; i++) {
    DEBUG ((DEBUG_INFO, "Id_%x ",ReportTable.Report[i].Id));
    DEBUG ((DEBUG_INFO, "MaxX_%x ",ReportTable.Report[i].LogMaxX));
    DEBUG ((DEBUG_INFO, "MinX_%x ",ReportTable.Report[i].LogMinX));
    DEBUG ((DEBUG_INFO, "MaxY_%x ",ReportTable.Report[i].LogMaxY));
    DEBUG ((DEBUG_INFO, "MinY_%x ",ReportTable.Report[i].LogMinY));
    DEBUG ((DEBUG_INFO, "BitB_%d-%d ",ReportTable.Report[i].BitStartB, ReportTable.Report[i].BitStopB-1));
    DEBUG ((DEBUG_INFO, "BitX_%d-%d ",ReportTable.Report[i].BitStartX, ReportTable.Report[i].BitStopX-1));
    DEBUG ((DEBUG_INFO, "BitY_%d-%d ",ReportTable.Report[i].BitStartY, ReportTable.Report[i].BitStopY-1));
    DEBUG ((DEBUG_INFO, "\n"));
  }
}

/*
  This function limits touchpanel's interrupt frequency to
  prevent traffic congestion on I2C
*/
EFI_STATUS
SetInterruptFrequency (
  IN ABSOLUTE_POINTER_DEV *TouchDev
  )
{
  UINTN                  i;
  UINT8                  WriteBuffer [6];
  EFI_STATUS             Status;
  EFI_I2C_REQUEST_PACKET *RequestPacket;

  Status = EFI_SUCCESS;
  RequestPacket = NewRequestPacket(1);
  if (RequestPacket == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  RequestPacket->Operation[0].Flags = 0;
  RequestPacket->Operation[0].LengthInBytes = 6;
  RequestPacket->Operation[0].Buffer = WriteBuffer;

  for (i = 0; i < TouchDev->InputReportTable.Quantity; i++) {
    //
    // for each ReportID this driver understands, limit interrupt frequency to 100ms
    // It is necessary due to extremely slow I2C driver operation
    //
    WriteBuffer[0] = TouchDev->HidDescriptor.DataRegisterLsb;
    WriteBuffer[1] = TouchDev->HidDescriptor.DataRegisterMsb;
    WriteBuffer[2] = 4;  //data length LSB
    WriteBuffer[3] = 0;  //data length MSB
    WriteBuffer[4] = 0x64;    //time between interrupts, in ms (LSB)
    WriteBuffer[5] = 0; //time between interrupts, in ms (MSB)
     Status = TouchDev->I2cIoProtocol->QueueRequest (TouchDev->I2cIoProtocol,0,NULL,RequestPacket,NULL);
    if (EFI_ERROR(Status)) {
      break;
    }
    WriteBuffer[0] = TouchDev->HidDescriptor.CommandRegisterLsb;
    WriteBuffer[1] = TouchDev->HidDescriptor.CommandRegisterMsb;
    WriteBuffer[2] = (UINT8)TouchDev->InputReportTable.Report[i].Id;
    WriteBuffer[3] = SET_IDLE;
    WriteBuffer[4] = 0;
    WriteBuffer[5] = 0;
    Status = TouchDev->I2cIoProtocol->QueueRequest (TouchDev->I2cIoProtocol,0,NULL,RequestPacket,NULL);
    if (EFI_ERROR(Status)) {
      break;
    }
  }
  DeleteRequestPacket(RequestPacket);
  return Status;
}

/*
  A HID-compliant device may have more than 1 functionality, for example
  digitizer/touchpanel/pen/button etc. Each functionality reports data in
  a different format. In order to correctly parse that data, a set of dictionaries
  must be built.
  This function reads HID device's InputReportDescriptor and uses its data to
  create dictionaries for all types of InputReports this device supports.
  Such set of dictionaries is held in InputReportTable.
  InputDataDescriptor is parsed sequentially. In a loop, GetToken() extracts single
  data token from the descriptor stream. Those tokens are passed to UpdateStack()
  which updates ParseStack, which is a not-yet-complete dictionary. Once
  a dictionary is complete, it is either added to InputReportTable or discarded.
  */
EFI_STATUS
ReadInputReportDescriptor (
  IN ABSOLUTE_POINTER_DEV *TouchDev
  )
{
  UINT8* InputReportDescriptor;
  UINT8* MovingPointer;
  UINT8  WriteBuffer[2];
  UINT16 InputReportLength;
  PARSER_STACK ParseStack;
  TOKEN Token;
  EFI_STATUS Status;
  EFI_I2C_REQUEST_PACKET *RequestPacket;

  TouchDev->InputReportTable.Quantity = 0;
  TouchDev->InputReportTable.Report = NULL;

  ZeroMem(&ParseStack, sizeof(PARSER_STACK));

  InputReportLength = TouchDev->HidDescriptor.ReportDescRegLengthLsb + (TouchDev->HidDescriptor.ReportDescRegLengthMsb<<8);
  InputReportDescriptor = AllocatePool(InputReportLength);
  if (InputReportDescriptor == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  MovingPointer = InputReportDescriptor;
  WriteBuffer[0] = TouchDev->HidDescriptor.ReportDescRegisterLsb;
  WriteBuffer[1] = TouchDev->HidDescriptor.ReportDescRegisterMsb;

  RequestPacket = NewRequestPacket(2);
  if (RequestPacket == NULL) {
    FreePool (InputReportDescriptor);
    return EFI_OUT_OF_RESOURCES;
  }

  RequestPacket->Operation[0].Flags = 0;
  RequestPacket->Operation[0].LengthInBytes = sizeof (WriteBuffer);
  RequestPacket->Operation[0].Buffer = WriteBuffer;
  RequestPacket->Operation[1].Flags = I2C_FLAG_READ;
  RequestPacket->Operation[1].LengthInBytes = InputReportLength;
  RequestPacket->Operation[1].Buffer = InputReportDescriptor;
  Status = TouchDev->I2cIoProtocol->QueueRequest (TouchDev->I2cIoProtocol,0,NULL,RequestPacket,NULL);
  DeleteRequestPacket(RequestPacket);

  if (EFI_ERROR (Status)) {
    FreePool (InputReportDescriptor);
    return Status;
  }

  while(InputReportLength>0) {
    Token = GetToken(&MovingPointer, &InputReportLength);
    UpdateStack(&ParseStack, Token, &(TouchDev->InputReportTable) );
  }
  ExportReport(&ParseStack, &(TouchDev->InputReportTable) );
  ShowReportTable(TouchDev->InputReportTable);
  // this assumes all Report formats have the same Max/Min X/Y values
  // since ABSOLUTE_POINTER_DEV only holds single set of Max/Min values, supporting
  // multiple resolutions means doing internal stretching of different formats to the biggest one
  //
  // TODO: rewrite this to treat each format report as a separate touch device with its own AbsPtr protocol (like in Windows)?
  //
  TouchDev->Mode.AbsoluteMaxX = TouchDev->InputReportTable.Report[0].LogMaxX;
  TouchDev->Mode.AbsoluteMaxY = TouchDev->InputReportTable.Report[0].LogMaxY;
  FreePool (InputReportDescriptor);
  if(TouchDev->InputReportTable.TouchPanel == 0) {
    // this is to prevent driver from installing on touchpads, gyroscopes etc; the HID layer is compatible and driver would
    // read input data correctly, but would interpret it in unexpected and misleading way
    return EFI_UNSUPPORTED;
  }
  if(TouchDev->InputReportTable.Quantity == 0) {
    return EFI_UNSUPPORTED;
  }
  return EFI_SUCCESS;
}

/*
  This function uses dictionaries to parse incoming InputReport and convert it into X/Y coordinates plus Button info.
*/
TOUCH_OUTPUT
ParseInput (
  INPUT_REPORT_TABLE ReportTable,
  UINT8*             InputStream
  )
{
  UINT32 IdPresent = 0;
  UINT32 i;
  UINT32 j;
  TOUCH_OUTPUT Output;
  UINT8* RawData;


  Output.X=0;
  Output.Y=0;
  Output.B=0;
  //
  // HID I2C devices support either a single or multiple InputReport formats.
  // In case of multiple, every report is prefixed with ReportID.
  // In case of single, ReportID may or may not be present. This information is
  // stored in device's dictionaries
  //
  if(ReportTable.Quantity > 1 || (ReportTable.Quantity != 0 && ReportTable.Report[0].Id != 0)) {
    IdPresent = 1;
  }
  //
  //sets pointer to beginning of useful data. Skips Length bytes and ReportID byte if present.
  //
  RawData = InputStream + I2C_HID_LENGTH_PREFIX;
  if (IdPresent) {
    RawData++;
  }

  //
  // Incoming data is parsed using proper dictionary selected by ReportID. In cases where
  // ReportID is not provided, it is guaranteed that only a single dictionary exists
  //
  // Dictionary describes which bits from input stream hold X / Y / Button data.
  // There's no guarantee coordinates will be byte-aligned, therefore we use bit access
  //
  for (i = 0; i < ReportTable.Quantity; i++) {
    if (!IdPresent || InputStream[2] == ReportTable.Report[i].Id) {
      for(j=ReportTable.Report[i].BitStartX; j<ReportTable.Report[i].BitStopX; j++) {
        Output.X += AccessBit(RawData, j) << (j-ReportTable.Report[i].BitStartX);
      }
      for(j=ReportTable.Report[i].BitStartY; j<ReportTable.Report[i].BitStopY; j++) {
        Output.Y += AccessBit(RawData, j) << (j-ReportTable.Report[i].BitStartY);
      }
      for(j=ReportTable.Report[i].BitStartB; j<ReportTable.Report[i].BitStopB; j++) {
        Output.B += AccessBit(RawData, j) << (j-ReportTable.Report[i].BitStartB);
      }
      return Output;
      }
    }
  return Output;
  }

