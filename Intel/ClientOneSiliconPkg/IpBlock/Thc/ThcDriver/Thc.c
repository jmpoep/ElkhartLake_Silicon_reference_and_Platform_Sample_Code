/** @file
  Touch Host Controller Driver

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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

#include "ThcPrivate.h"
#include "ThcAbsPtr.h"
#include "ThcHid.h"
#include "ThcDriver.h"
#include <Uefi/UefiSpec.h>


///
/// Driver Support EFI Version Protocol instance
///
GLOBAL_REMOVE_IF_UNREFERENCED
EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL gThcDriverSupportedEfiVersion = {
  sizeof (EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL),
  EFI_2_40_SYSTEM_TABLE_REVISION
};

/**
  Function to unload Thc Driver when
  gBS->ExitBootServices() called or LegacyBoot event.

  @param[in]  Event             Pointer to this event
  @param[in]  Context           Event handler private data

**/
VOID
EFIAPI
ThcExitEvent (
  IN EFI_EVENT     Event,
  IN VOID          *Context
  )
{
  THC_DEV     *ThcDev;

  ThcDev = Context;

  DEBUG ((DEBUG_INFO, "ThcExitEvent Start \n"));

  //
  // Check if CleanUp is required
  //
  if (ThcDev->Signature != THC_SIGNATURE) {
    DEBUG ((DEBUG_INFO, "ThcExitEvent Thc Structure already freed. End \n"));
    return;
  }

  ThcStop (ThcDev);

  if (Event != NULL) {
    gBS->CloseEvent (Event);
  }

  DEBUG ((DEBUG_INFO, "ThcExitEvent End \n"));
}


/**
  Creates ExitEvent responsible for ExitBootServices clean up

  @param[in]  ThcDev            Context of Thc device

  @retval EFI_SUCCESS           The operation completed successfully.
  @retval Others                An unexpected error occurred.
**/
EFI_STATUS
ThcCreateExitEvents (
  IN THC_DEV                *ThcDev
  )
{
  EFI_STATUS  Status;

  ///
  /// Create ExitBootServices/LegacyBootEvent for calling the ThcDriverBindingStop procedure
  ///
  DEBUG ((DEBUG_INFO, "ThcCreateExitEvents Create ExitBootServices/LegacyBoot Event\n"));
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  ThcExitEvent,
                  ThcDev,
                  &gEfiEventExitBootServicesGuid,
                  &ThcDev->ExitEvent
                  );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  ThcExitEvent,
                  ThcDev,
                  &gEfiEventLegacyBootGuid,
                  &ThcDev->ExitEvent
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  Unloads an image.

  @param[in]  ImageHandle       Handle that identifies the image to be unloaded.

  @retval EFI_SUCCESS           The image has been unloaded.
  @retval EFI_INVALID_PARAMETER ImageHandle is not a valid image handle.

**/
EFI_STATUS
EFIAPI
ThcUnload (
  IN EFI_HANDLE  ImageHandle
  )
{
  EFI_STATUS  Status;
  EFI_HANDLE  *HandleBuffer;
  UINTN       HandleCount;
  UINTN       Index;

  Status = EFI_SUCCESS;

  //
  // Retrieve array of all handles in the handle database
  //
  Status = gBS->LocateHandleBuffer (
                  AllHandles,
                  NULL,
                  NULL,
                  &HandleCount,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Disconnect the current driver from handles in the handle database
  //
  for (Index = 0; Index < HandleCount; Index++) {
    Status = gBS->DisconnectController (HandleBuffer[Index], ImageHandle, NULL);
  }

  //
  // Free the array of handles
  //
  FreePool (HandleBuffer);

  //
  // Uninstall the driver version protocol
  //
  Status = gBS->UninstallMultipleProtocolInterfaces (
                  ImageHandle,
                  &gEfiDriverSupportedEfiVersionProtocolGuid,
                  &gThcDriverSupportedEfiVersion,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Uninstall protocols installed in the driver entry point
  //
  Status = gBS->UninstallMultipleProtocolInterfaces (
                  ImageHandle,
                  &gEfiDriverBindingProtocolGuid,  &gThcDriverBinding,
                  &gEfiComponentNameProtocolGuid,  &gThcDriverComponentName,
                  &gEfiComponentName2ProtocolGuid, &gThcDriverComponentName2,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  return EFI_SUCCESS;
}

/**
  Starts Circular Buffer state Pointer polling on Thc

  @param[in]  ThcDev      Context of Thc device

  @retval EFI_SUCCESS     Polling started
  @retval other           Error during initialization
**/
EFI_STATUS
ThcStartPolling (
  IN THC_DEV        *ThcDev
  )
{
  EFI_STATUS    Status;

  //
  // Periodic events run with NOTIFY priority to guarantee driver works fine when called from code that runs with CALLBACK priority
  //
  Status = gBS->CreateEvent (
                  EVT_TIMER | EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  ThcPolling,
                  (VOID*) ThcDev,
                  &ThcDev->PollingEvent
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ThcStartPolling error, cannot create PollingEvent Status %r\n", Status));
    return Status;
  }

  Status = gBS->SetTimer (
                  ThcDev->PollingEvent,
                  TimerPeriodic,
                  EFI_TIMER_PERIOD_MILLISECONDS (THC_POLLING_PERIOD)
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ThcStartPolling error, cannot enable PollingEvent timer, %r\n", Status));
    return Status;
  }

  return Status;
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
ThcEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS    Status;

  Status = EFI_SUCCESS;
  //
  // Install UEFI Driver Model protocol(s).
  //
  Status = EfiLibInstallDriverBindingComponentName2 (
             ImageHandle,
             SystemTable,
             &gThcDriverBinding,
             ImageHandle,
             &gThcDriverComponentName,
             &gThcDriverComponentName2
             );
  ASSERT_EFI_ERROR (Status);

  //
  // Install Driver Supported EFI Version Protocol onto ImageHandle
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiDriverSupportedEfiVersionProtocolGuid, &gThcDriverSupportedEfiVersion,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  Tests to see if this driver supports a given controller. If a child device is provided,
  it further tests to see if this driver supports creating a handle for the specified child device.

  This function checks to see if the driver specified by This supports the device specified by
  ControllerHandle. Drivers will typically use the device path attached to
  ControllerHandle and/or the services from the bus I/O abstraction attached to
  ControllerHandle to determine if the driver supports ControllerHandle. This function
  may be called many times during platform initialization. In order to reduce boot times, the tests
  performed by this function must be very small, and take as little time as possible to execute. This
  function must not change the state of any hardware devices, and this function must be aware that the
  device specified by ControllerHandle may already be managed by the same driver or a
  different driver. This function must match its calls to AllocatePages() with FreePages(),
  AllocatePool() with FreePool(), and OpenProtocol() with CloseProtocol().
  Because ControllerHandle may have been previously started by the same driver, if a protocol is
  already in the opened state, then it must not be closed with CloseProtocol(). This is required
  to guarantee the state of ControllerHandle is not modified by this function.

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
ThcDriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath OPTIONAL
  )
{
  THC_PROTOCOL                    *ThcProtocol;
  EFI_STATUS                      Status;
  EFI_PCI_IO_PROTOCOL             *PciIo;
  UINT16                          DeviceId;

  //
  // Verify that this driver is not already running on this device
  //
  Status = gBS->OpenProtocol (
                  ControllerHandle,
                  &gThcProtocolGuid,
                  (VOID **) &ThcProtocol,
                  NULL,
                  NULL,
                  EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                  );
  if (!EFI_ERROR (Status)) {
    return EFI_ALREADY_STARTED;
  }

  Status = gBS->OpenProtocol (
                  ControllerHandle,
                  &gEfiPciIoProtocolGuid,
                  (VOID **) &PciIo,
                  This->DriverBindingHandle,
                  ControllerHandle,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status)) {
    return EFI_UNSUPPORTED;
  }

  PciIo->Pci.Read (
               PciIo,
               EfiPciIoWidthUint16,
               PCI_DEVICE_ID_OFFSET,
               1,
               &DeviceId
               );

  //
  // Close the PCI I/O Protocol that was opened with PROTOCOL_BY_DRIVER
  //
  gBS->CloseProtocol (ControllerHandle, &gEfiPciIoProtocolGuid, This->DriverBindingHandle, ControllerHandle);
  if (EFI_ERROR (Status)) {
    return EFI_UNSUPPORTED;
  }

  if (DeviceId == PCI_DEVICE_ID_PCH_THC0) {
    THC_LOCAL_DEBUG(L"ThcDriverBindingSupported DeviceId: 0x%X \n", DeviceId)
    DEBUG ((DEBUG_INFO, "ThcDriverBindingSupported DeviceId: 0x%X \n", DeviceId));
    return EFI_SUCCESS;
  }

  return EFI_UNSUPPORTED;
}


/**
  Starts a device controller or a bus controller.

  The Start() function is designed to be invoked from the EFI boot service ConnectController().
  As a result, much of the error checking on the parameters to Start() has been moved into this
  common boot service. It is legal to call Start() from other locations,
  but the following calling restrictions must be followed, or the system behavior will not be deterministic.
  1. ControllerHandle must be a valid EFI_HANDLE.
  2. If RemainingDevicePath is not NULL, then it must be a pointer to a naturally aligned
     EFI_DEVICE_PATH_PROTOCOL.
  3. Prior to calling Start(), the Supported() function for the driver specified by This must
     have been called with the same calling parameters, and Supported() must have returned EFI_SUCCESS.

  @param[in]  This                 A pointer to the EFI_DRIVER_BINDING_PROTOCOL instance.
  @param[in]  ControllerHandle     The handle of the controller to start. This handle
                                   must support a protocol interface that supplies
                                   an I/O abstraction to the driver.
  @param[in]  RemainingDevicePath  A pointer to the remaining portion of a device path.  This
                                   parameter is ignored by device drivers, and is optional for bus
                                   drivers. For a bus driver, if this parameter is NULL, then handles
                                   for all the children of Controller are created by this driver.
                                   If this parameter is not NULL and the first Device Path Node is
                                   not the End of Device Path Node, then only the handle for the
                                   child device specified by the first Device Path Node of
                                   RemainingDevicePath is created by this driver.
                                   If the first Device Path Node of RemainingDevicePath is
                                   the End of Device Path Node, no child handle is created by this
                                   driver.

  @retval EFI_SUCCESS              The device was started.
  @retval EFI_DEVICE_ERROR         The device could not be started due to a device error.Currently not implemented.
  @retval EFI_OUT_OF_RESOURCES     The request could not be completed due to a lack of resources.
  @retval Others                   The driver failed to start the device.

**/
EFI_STATUS
EFIAPI
ThcDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath OPTIONAL
  )
{
  THC_DEV      *ThcDev;
  EFI_STATUS   Status;
  UINT64       Supports;
  UINT64       OriginalPciAttributes;

  OriginalPciAttributes  = 0;

  DEBUG ((DEBUG_INFO, "ThcDriverBindingStart Start()\n"));
  THC_LOCAL_DEBUG(L"ThcDriverBindingStart Start ()\n")
  //
  // Allocate the driver context
  //
  ThcDev = AllocateZeroPool (sizeof (THC_DEV));
  if (ThcDev == NULL) {
    THC_LOCAL_DEBUG(L"ThcDriverBindingStart Failed to allocate driver context EFI_OUT_OF_RESOURCES \n")
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Save PciIo Protocol instance for DMA usage
  //
  Status = gBS->OpenProtocol (
                  ControllerHandle,
                  &gEfiPciIoProtocolGuid,
                  (VOID **) &ThcDev->PciIo,
                  This->DriverBindingHandle,
                  ControllerHandle,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status)) {
    THC_LOCAL_DEBUG(L"ThcDriverBindingStart Failed to OpenProtocol PciIoProtocol\n")
    return Status;
  }

  //
  // Get BAR0
  //
  Status = ThcDev->PciIo->Pci.Read (ThcDev->PciIo, EfiPciIoWidthUint64, PCI_BASE_ADDRESSREG_OFFSET, 1, &ThcDev->PciBar0);
  if (EFI_ERROR (Status)) {
    THC_LOCAL_DEBUG(L"ThcDriverBindingStart ERROR - Thc failed to read BAR0 Status: %r\n", Status);
    DEBUG ((DEBUG_ERROR, "ERROR - Thc failed to BAR0 Status: %r\n", Status));
    FreePool (ThcDev);
    return Status;
  }
  ThcDev->PciBar0 = ThcDev->PciBar0 & 0xFFFFFFFFFFFFFFF0;
  THC_LOCAL_DEBUG(L"ThcDriverBindingStart BAR0 value: 0x%X\n", ThcDev->PciBar0)

  //
  // Set D0
  //
  ThcDev->PciPwrst = (UINT8)~(V_THC_CFG_PMD_PMCSRBSE_PMCSR_PWRST_D3);
  Status = ThcDev->PciIo->Pci.Write (ThcDev->PciIo, EfiPciIoWidthUint8, R_THC_CFG_PMD_PMCSRBSE_PMCSR, 1, &ThcDev->PciPwrst);
  if (EFI_ERROR (Status)) {
    THC_LOCAL_DEBUG(L"ThcDriverBindingStart ERROR - Thc failed to set D0 state Status: %r\n", Status)
    DEBUG ((DEBUG_ERROR, "ERROR - Thc failed to set D0 Status: %r\n", Status));
    FreePool (ThcDev);
    return Status;
  }
  THC_LOCAL_DEBUG(L"ThcDriverBindingStart Thc D0 set\n");

  //
  // Save Controllers Pci Configuration state
  //
  Status = ThcDev->PciIo->Attributes (ThcDev->PciIo, EfiPciIoAttributeOperationGet, 0, &OriginalPciAttributes);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  ThcDev->PciAttributes = OriginalPciAttributes;

  //
  // Enable Controller
  //
  Status = ThcDev->PciIo->Attributes (ThcDev->PciIo, EfiPciIoAttributeOperationSupported, 0, &Supports);
  if (!EFI_ERROR (Status)) {
    Supports &= (UINT64) EFI_PCI_DEVICE_ENABLE;
    Status = ThcDev->PciIo->Attributes (ThcDev->PciIo, EfiPciIoAttributeOperationEnable, Supports, NULL);
  }
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Initialize the driver context
  //
  ThcDev->Signature                = THC_SIGNATURE;
  ThcDev->ControllerHandle         = ControllerHandle;
  ThcDev->Initialized              = FALSE;

  ThcDev->ThcProtocol.Revision      = THC_PROTOCOL_REVISION;
  ThcDev->ThcProtocol.DeviceStatus  = EFI_NOT_READY;

  //
  // HID
  //
  ThcDev->ThcProtocol.HidGetFeature = HidGetFeature;
  ThcDev->ThcProtocol.HidSetFeature = HidSetFeature;
  ThcDev->HidDataAvailable          = FALSE;
  ThcDev->HidActive                 = FALSE;
  ThcDev->HidBuffer                 = NULL;

  ThcDev->AbsPtrDataAvailable       = FALSE;
  ThcDev->ReadDone                  = FALSE;

  AddUnicodeString2 ("eng", gThcDriverComponentName.SupportedLanguages,  &ThcDev->ControllerNameTable, L"Intel Touch Host Controller Driver", TRUE);
  AddUnicodeString2 ("en",  gThcDriverComponentName2.SupportedLanguages, &ThcDev->ControllerNameTable, L"Intel Touch Host Controller Driver", FALSE);

  //
  // Install only Thc Protocol to avoid Binding Start getting invoked for second time.
  // Other protocols will be installed after Thc successful Initialization
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ControllerHandle,
                  &gThcProtocolGuid,
                  &ThcDev->ThcProtocol,
                  NULL,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ERROR - Thc failed to install ThcProtocol Status: %r\n", Status));
    FreePool (ThcDev);
    return Status;
  }

  Status = ThcCreateExitEvents (ThcDev);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ERROR - Thc failed to create Exit Events Status: %r\n", Status));
    FreePool (ThcDev);
    return Status;
  }

  Status = ThcInitialize (ThcDev);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ERROR - Thc failed to Initialize Device Status: %r\n", Status));
    goto THC_ERROR_EXIT;
  }

  Status = ThcReadConfig (ThcDev);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ERROR - Thc failed to Read Device Configuration Status: %r\n", Status));
    goto THC_ERROR_EXIT;
  }

  ThcPrintConfig (ThcDev);

  Status = ThcSetFrequency (ThcDev);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ERROR - Thc failed to Set New Thc Frequency Device Status: %r\n", Status));
    goto THC_ERROR_EXIT;
  }

  Status = ThcEnableEndDevice (ThcDev);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ERROR - Thc failed to Configure Device Status: %r\n", Status));
    goto THC_ERROR_EXIT;
  }

  Status = ThcDmaInitialize (ThcDev);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ERROR - Thc failed to Initialize DMA Status: %r\n", Status));
    goto THC_ERROR_EXIT;
  }

  ThcPrintConfig (ThcDev);

  ThcDev->ReadDone = TRUE;

  Status = ThcStartPolling (ThcDev);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ERROR - Thc failed to StartPolling Status: %r\n", Status));
    goto THC_ERROR_EXIT;
  }

  Status = ThcInstallAbsPtr (ThcDev);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ERROR - Thc failed to Install AbsPtr Protocol Status: %r\n", Status));
    goto THC_ERROR_EXIT;
  }

  Status = gBS->ConnectController (ThcDev->ControllerHandle, NULL, NULL, TRUE);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ERROR - Thc failed to ConnectController Status: %r\n", Status));
    goto THC_ERROR_EXIT;
  }

  ThcDev->Initialized = TRUE;
  ThcDev->ThcProtocol.DeviceStatus = EFI_SUCCESS;

  THC_LOCAL_DEBUG(L"ThcDriverBindingStart End()\n")
  DEBUG ((DEBUG_INFO, "ThcDriverBindingStart End()\n"));
  if (!EFI_ERROR (Status)) {
    return Status;
  }

THC_ERROR_EXIT:
  //
  // Thc Driver always returns EFI_SUCCESS from this point even if initialization fails
  // Driver Context, Events, Memory are cleared in Exit Boot Services Event
  // True device status is available on THC Protocol
  //
  ThcDev->ThcProtocol.DeviceStatus = EFI_DEVICE_ERROR;
  DEBUG ((DEBUG_ERROR, "ThcDriverBindingStart End() - Failed\n"));
  return EFI_SUCCESS;
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
ThcDriverBindingStop (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   ControllerHandle,
  IN UINTN                        NumberOfChildren,
  IN EFI_HANDLE                   *ChildHandleBuffer OPTIONAL
  )
{
  THC_PROTOCOL       *ThcProtocol;
  THC_DEV            *ThcDev;
  EFI_STATUS         Status;

  DEBUG ((DEBUG_INFO, "ThcDriverBindingStop Start\n"));

  //
  // Check if ThcProtocol is installed
  //
  Status = gBS->OpenProtocol (
                  ControllerHandle,
                  &gThcProtocolGuid,
                  (VOID **) &ThcProtocol,
                  This->DriverBindingHandle,
                  ControllerHandle,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ThcDriverBindingStop Failed to get ThcProtocol, Status: %r\n", Status));
    return EFI_UNSUPPORTED;
  }

  //
  // Get ThcDevice context from Protocol
  //
  ThcDev = THC_CONTEXT_FROM_THC_PROTOCOL (ThcProtocol);
  if (ThcDev == NULL) {
    return EFI_DEVICE_ERROR;
  }

  gBS->CloseEvent (ThcDev->ExitEvent);

  ThcStop (ThcDev);

  Status = gBS->UninstallMultipleProtocolInterfaces (
                  ControllerHandle,
                  &gThcProtocolGuid,
                  &ThcDev->ThcProtocol,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_WARN, "ThcDriverBindingStop Failed to Uninstall ThcProtocol, Status: %r\n", Status));
  }

  DEBUG ((DEBUG_INFO, "ThcDriverBindingStop End\n"));

  return Status;
}

///
/// Driver Binding Protocol instance
///
GLOBAL_REMOVE_IF_UNREFERENCED EFI_DRIVER_BINDING_PROTOCOL gThcDriverBinding = {
  ThcDriverBindingSupported,
  ThcDriverBindingStart,
  ThcDriverBindingStop,
  TOUCH_DRIVER_VERSION,
  NULL,
  NULL
};

