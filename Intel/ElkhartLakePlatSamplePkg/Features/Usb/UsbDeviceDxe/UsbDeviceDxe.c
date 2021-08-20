/** @file
 Implementation of USBFN protocol driver.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2017 Intel Corporation.

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


#include "UsbDeviceDxe.h"

typedef struct _USB_MEM_BLOCK USB_MEM_BLOCK;
struct _USB_MEM_BLOCK {
  UINT8                   *BufHost;
  UINTN                   BufLen; // Memory size in bytes
  EFI_PHYSICAL_ADDRESS    MappedAddr;
  VOID                    *Mapping;
  EFI_PCI_IO_PROTOCOL     *PciIo;
};

EFI_DRIVER_BINDING_PROTOCOL mUsbDeviceDxeDriverBinding = {
  UsbDeviceDxeDriverSupported,
  UsbDeviceDxeDriverStart,
  UsbDeviceDxeDriverStop,
  0x1,
  NULL,
  NULL
};


/**
  This function can be called to poll for certain value within a time given.

  @param[in] MmioAddress          The Mmio Address.
  @param[in] BitMask              Bits to be masked.
  @param[in] BitValue             Value to be polled.
  #param[in] DelayTime            Delay time in terms of 100 micro seconds.

  @retval EFI_SUCCESS             Successfully polled the value.
  @retval EFI_TIMEOUT             Timeout while polling the value.
**/
EFI_STATUS
EFIAPI
PchMmioPoll32 (
  IN  UINTN         MmioAddress,
  IN  UINT32        BitMask,
  IN  UINT32        BitValue,
  IN  UINT16        DelayTime
  )
{
  UINT32  LoopTime;
  UINT8   PollSuccess;

  LoopTime    = 0;
  PollSuccess = 0;

  DEBUG ((DEBUG_INFO, "PchMmioPoll32, BitMask: %x, BitValue: %x\n",  BitMask, BitValue));
  for (LoopTime = 0; LoopTime < DelayTime; LoopTime++) {
    if ((MmioRead32 (MmioAddress) & BitMask) == (BitValue & BitMask)) {
      PollSuccess = 1;
      break;
    } else {
      gBS->Stall (100);
    }
  }

  if (PollSuccess) {
    return EFI_SUCCESS;
  } else {
    return EFI_TIMEOUT;
  }
}

/**
  Platform specific initialization.

**/
VOID
EFIAPI
UsbPlatformSpecificInit (
  VOID
  )
{
  UINT64      OtgPciMmBase;
  UINT64      XhciPciMmBase;
  UINT64      XhciMmioBase;
  UINT64      OtgMmioBase0;
  UINT32      OtgMmioBaseHigh;
  UINTN       *OtgDbgBase;
  UINT32      BitValue;
  UINT32      BitMask;
  EFI_STATUS  Status;

  Status     = EFI_SUCCESS;
  OtgDbgBase = NULL;

  XhciPciMmBase = PCI_SEGMENT_LIB_ADDRESS (
                    DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                    DEFAULT_PCI_BUS_NUMBER_PCH,
                    PCI_DEVICE_NUMBER_PCH_XHCI,
                    PCI_FUNCTION_NUMBER_PCH_XHCI,
                    0
                    );
  XhciMmioBase = PciSegmentRead32 (XhciPciMmBase + R_XHCI_CFG_BAR0) & B_PCH_XHCI_MEM_BASE_BA;
  XhciMmioBase |= LShiftU64 (PciSegmentRead32 (XhciPciMmBase + R_XHCI_CFG_BAR0 + 4), 32);
  OtgPciMmBase = PCI_SEGMENT_LIB_ADDRESS (
                    DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                    DEFAULT_PCI_BUS_NUMBER_PCH,
                    PCI_DEVICE_NUMBER_PCH_OTG,
                    PCI_FUNCTION_NUMBER_PCH_OTG,
                    0
                    );
  DEBUG ((DEBUG_INFO, "XhciPciMmBase: %x, OtgPciMmBase: %x\n", XhciPciMmBase, OtgPciMmBase));

  PciSegmentWrite8 ((OtgPciMmBase + 0x04), 0x06);  // enable MSE and MMIO

  DEBUG_CODE (
    OtgDbgBase = AllocatePool (256);
    ASSERT (OtgDbgBase != NULL);

    PciSegmentReadBuffer (OtgPciMmBase, 256, OtgDbgBase);
    DEBUG ((DEBUG_INFO, "Configuration space of OTG\n"));
    DbgRawdataDump ((VOID *)OtgDbgBase, 256);
  );

  OtgMmioBase0 = PciSegmentRead32((UINTN)(OtgPciMmBase + R_PCH_OTG_BAR0));
  OtgMmioBaseHigh = PciSegmentRead32((UINTN)(OtgPciMmBase + R_PCH_OTG_BAR_HIGH));
  if ((OtgMmioBase0 & B_PCH_OTG_BAR0_TYPE) != B_PCH_OTG_BAR0_64_BIT) {
    OtgMmioBaseHigh = 0;
  }
  OtgMmioBase0 = ((UINT64) OtgMmioBaseHigh << 32) | (OtgMmioBase0 & B_PCH_OTG_BAR0_BA);
  DEBUG ((DEBUG_INFO, "XhciMmioBase: 0x%016lx, OtgMmioBase0: 0x%016lx\n", XhciMmioBase, OtgMmioBase0));
  DEBUG ((DEBUG_INFO, "USBDEVDXE: WA: GEN_REGRW1 =%x before\n", MmioRead32((UINTN)(OtgPciMmBase + R_PCH_OTG_GEN_REGRW1))));
  PciSegmentWrite32(OtgPciMmBase + R_PCH_OTG_GEN_REGRW1,0);
  DEBUG ((DEBUG_INFO, "USBDEVDXE: WA: GEN_REGRW1 =%x after\n", MmioRead32((UINTN)(OtgPciMmBase + R_PCH_OTG_GEN_REGRW1))));

  //
  // Disable OTG mode for device mode
  //

  //
  // Step 1: Enable OTG device Mode
  //
  DEBUG ((DEBUG_INFO, "Before 0x80D8 Value = %x\n", MmioRead32(XhciMmioBase + 0x80D8)));
  MmioOr32 (XhciMmioBase + 0x80D8, (UINT32) (BIT24|BIT21|BIT20)); // It's necessary to set BIT24
  DEBUG ((DEBUG_INFO, "USBDEVDXE: Set ID MUX of the OTG port to device mode. 0x80D8 Value = %x\n", MmioRead32(XhciMmioBase + 0x80D8)));

  //
  // Step 2: 0x80DC register, has a status bit to acknowledge the role change in Bit 29
  //
  BitMask  = (UINT32) (0x20000000);
  BitValue = (UINT32) (1 << 29);
  Status = PchMmioPoll32 (
            (UINTN) (XhciMmioBase + 0x80DC),
            BitMask,
            ~BitValue,
            1000
            );
  if (Status == EFI_TIMEOUT) {
    DEBUG ((DEBUG_ERROR, "Timeout while polling on xHCI BAR + 0x80DC [29] for 0b, %x\n", MmioRead32(XhciMmioBase + 0x80DC)));
  }

  DEBUG_CODE (
    ASSERT (OtgDbgBase != NULL);
    PciSegmentReadBuffer (OtgPciMmBase, 256, OtgDbgBase);
    DEBUG ((DEBUG_INFO, "Configuration space of OTG final\n"));
    DbgRawdataDump ((VOID *)OtgDbgBase, 256);

    FreePool (OtgDbgBase);
  );

  return;
}

/**
  The USB bus driver entry pointer.

  @param ImageHandle       The driver image handle.
  @param SystemTable       The system table.

  @return EFI_SUCCESS      The component name protocol is installed.
  @return Others           Failed to init the usb driver.

**/
EFI_STATUS
EFIAPI
UsbDeviceDxeEntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS              Status;
  BOOLEAN                 UsbFnEnable;
  SETUP_DATA              SystemConfiguration;
  UINTN                   VarSize;

  DEBUG ((DEBUG_INFO, "UsbDeviceDxeEntryPoint entry\n"));
  UsbFnEnable = FALSE;

  VarSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                   L"Setup",
                   &gSetupVariableGuid,
                   NULL,
                   &VarSize,
                   &SystemConfiguration
                   );
  if (!EFI_ERROR(Status)) {
    UsbFnEnable = SystemConfiguration.UsbFnEnable;
  }
  DEBUG ((DEBUG_INFO, "UsbFnEnable: %x\n", UsbFnEnable));

  if (UsbFnEnable == TRUE) {
    Status = EfiLibInstallDriverBindingComponentName2 (
               ImageHandle,
               SystemTable,
               &mUsbDeviceDxeDriverBinding,
               ImageHandle,
               &mUsbDeviceDxeComponentName,
               &mUsbDeviceDxeComponentName2
             );
  }

  DEBUG ((DEBUG_INFO, "UsbDeviceDxeEntryPoint exit, Status: %r\n", Status));
  return Status;
}



/**
  Check whether USB bus driver support this device.

  @param  This                   The USB bus driver binding protocol.
  @param  Controller             The controller handle to check.
  @param  RemainingDevicePath    The remaining device path.

  @retval EFI_SUCCESS            The bus supports this controller.
  @retval EFI_UNSUPPORTED        This device isn't supported.

**/
EFI_STATUS
EFIAPI
UsbDeviceDxeDriverSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   Controller,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath
  )
{
  EFI_STATUS                Status;
  EFI_PCI_IO_PROTOCOL       *PciIo;
  USB_CLASSC                UsbClassCReg;


  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiPciIoProtocolGuid,
                  (VOID **) &PciIo,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );

  if (EFI_ERROR (Status)) {
    Status = EFI_UNSUPPORTED;
    goto ON_EXIT;
  }

  Status = PciIo->Pci.Read (
                        PciIo,
                        EfiPciIoWidthUint8,
                        PCI_CLASSCODE_OFFSET,
                        sizeof (USB_CLASSC) / sizeof (UINT8),
                        &UsbClassCReg
                        );

  if (EFI_ERROR (Status)) {
    Status = EFI_UNSUPPORTED;
    goto ON_EXIT;
  }

  //
  // Test whether the controller belongs to USB device type
  //
  // 0x0C03FE / 0x0C0380
  if ((UsbClassCReg.BaseCode != PCI_CLASS_SERIAL) ||
      (UsbClassCReg.SubClassCode != PCI_CLASS_SERIAL_USB) ||
      ((UsbClassCReg.ProgInterface != PCI_IF_USBDEV) && (UsbClassCReg.ProgInterface != 0x80))) {
    Status = EFI_UNSUPPORTED;
  }

ON_EXIT:
  gBS->CloseProtocol (
         Controller,
         &gEfiPciIoProtocolGuid,
         This->DriverBindingHandle,
         Controller
         );

  //DEBUG ((DEBUG_INFO, "UsbDeviceDxeDriverSupported, Status: %r\n", Status));
  return Status;
}


/**
  Start to process the controller.

  @param  This                   The USB bus driver binding instance.
  @param  Controller             The controller to check.
  @param  RemainingDevicePath    The remaining device patch.

  @retval EFI_SUCCESS            The controller is controlled by the usb bus.
  @retval EFI_ALREADY_STARTED    The controller is already controlled by the usb
                                 bus.
  @retval EFI_OUT_OF_RESOURCES   Failed to allocate resources.

**/
EFI_STATUS
EFIAPI
UsbDeviceDxeDriverStart (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   Controller,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath
  )
{
  EFI_STATUS            Status;
  USB_XDCI_DEV_CONTEXT  *UsbXdciDevContext;
  EFI_PCI_IO_PROTOCOL   *PciIo;
  UINT32                XdciMmioBarHigh;

  DEBUG ((USB_FUIO_DEBUG_LOAD, "UsbFunIoEntryPoint - Entry\n"));

  UsbXdciDevContext = NULL;
  XdciMmioBarHigh   = 0;

  //
  // Provide protocol interface
  //
  //
  // Get the PCI I/O Protocol on PciHandle
  //
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiPciIoProtocolGuid,
                  (VOID **) &PciIo,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );

  if (EFI_ERROR (Status)) {
    goto ErrorExit;
  }

  UsbXdciDevContext = AllocateZeroPool (sizeof (USB_XDCI_DEV_CONTEXT));
  if (UsbXdciDevContext == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto ErrorExit;
  }

  //
  // Initialize the driver context
  //
  UsbXdciDevContext->StartUpController = FALSE;
  UsbXdciDevContext->XdciHandle = Controller;
  UsbXdciDevContext->FirstNodePtr = NULL;
  UsbXdciDevContext->Signature = EFI_USB_DEV_SIGNATURE;

  PciIo->Pci.Read (
               PciIo,
               EfiPciIoWidthUint32,
               R_PCH_OTG_BAR0,
               1,
               &UsbXdciDevContext->XdciMmioBarAddr
               );

  if ((UsbXdciDevContext->XdciMmioBarAddr & B_PCH_OTG_BAR0_TYPE) == B_PCH_OTG_BAR0_64_BIT) {
    PciIo->Pci.Read (
                 PciIo,
                 EfiPciIoWidthUint32,
                 R_PCH_OTG_BAR_HIGH,
                 1,
                 &XdciMmioBarHigh
                 );
  }

  UsbXdciDevContext->XdciMmioBarAddr = ((UINT64) XdciMmioBarHigh << 32) | (UsbXdciDevContext->XdciMmioBarAddr & B_PCH_OTG_BAR0_BA);
  DEBUG ((USB_FUIO_DEBUG_INFO, "USB DEV mode IO addr 0x%016lx\n", UsbXdciDevContext->XdciMmioBarAddr));

  CopyMem (
    &(UsbXdciDevContext->UsbFunIoProtocol),
    &mUsbFunIoProtocol,
    sizeof (EFI_USBFN_IO_PROTOCOL)
    );

  CopyMem (
    &(UsbXdciDevContext->UsbDevModeProtocol),
    &mUsbDeviceModeProtocol,
    sizeof (EFI_USB_DEVICE_MODE_PROTOCOL)
    );

  Status = gBS->InstallMultipleProtocolInterfaces (
                  &UsbXdciDevContext->XdciHandle,
                  &gEfiUsbFnIoProtocolGuid,
                  &UsbXdciDevContext->UsbFunIoProtocol,
                  &gEfiUsbDeviceModeProtocolGuid,
                  &UsbXdciDevContext->UsbDevModeProtocol,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((USB_FUIO_DEBUG_LOAD, "ERROR - Failed to install upper protocol, Status: %r\n", Status));
    goto ErrorExit;
  }

  DEBUG ((USB_FUIO_DEBUG_LOAD, "Done - install upper protocol complete\n"));
  DEBUG ((USB_FUIO_DEBUG_LOAD, "UsbFunIoEntryPoint - Exit\n"));
  return Status;

ErrorExit:
  gBS->CloseProtocol (
         Controller,
         &gEfiPciIoProtocolGuid,
         This->DriverBindingHandle,
         Controller
         );
  if (UsbXdciDevContext != NULL) {
    FreePool (UsbXdciDevContext);
  }
  DEBUG ((USB_FUIO_DEBUG_ERROR, "ERROR - UsbFunIoEntryPoint - Exit\n"));

  DEBUG ((DEBUG_INFO, "UsbDeviceDxeDriverStart, Status: %r\n", Status));
  return Status;
}

/**
  Stop handle the controller by this USB bus driver.

  @param  This                   The USB bus driver binding protocol.
  @param  Controller             The controller to release.
  @param  NumberOfChildren       The child of USB bus that opened controller
                                 BY_CHILD.
  @param  ChildHandleBuffer      The array of child handle.

  @retval EFI_SUCCESS            The controller or children are stopped.
  @retval EFI_DEVICE_ERROR       Failed to stop the driver.

**/
EFI_STATUS
EFIAPI
UsbDeviceDxeDriverStop (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   Controller,
  IN UINTN                        NumberOfChildren,
  IN EFI_HANDLE                   *ChildHandleBuffer
  )
{
  EFI_USBFN_IO_PROTOCOL           *UsbFunIoProtocol;

  EFI_STATUS                      Status;
  USB_XDCI_DEV_CONTEXT            *UsbXdciDevContext;


  //
  // Locate USB_BUS for the current host controller
  //
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiUsbFnIoProtocolGuid,
                  (VOID **) &UsbFunIoProtocol,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );


  if (EFI_ERROR (Status)) {
    return Status;
  }

  UsbXdciDevContext = USBFUIO_CONTEXT_FROM_PROTOCOL (UsbFunIoProtocol);

  //
  // free pool
  //
  while (UsbXdciDevContext->FirstNodePtr != NULL) {
    RemoveNode (UsbFunIoProtocol, UsbXdciDevContext->FirstNodePtr);
  }

  Status = gBS->UninstallMultipleProtocolInterfaces (
                  UsbXdciDevContext->XdciHandle,
                  &gEfiUsbFnIoProtocolGuid,
                  &UsbXdciDevContext->UsbFunIoProtocol,
                  &gEfiUsbDeviceModeProtocolGuid,
                  &UsbXdciDevContext->UsbDevModeProtocol,
                  NULL
                  );


  //
  // Deinit??
  //
  if (UsbXdciDevContext->StartUpController == TRUE) {
    Status = StopController (UsbFunIoProtocol);
    DEBUG ((USB_FUIO_DEBUG_INFO, "USB DEV mode STOP UsbFnDeInitDevice %r\n", Status));
  }

  gBS->CloseProtocol (
         Controller,
         &gEfiPciIoProtocolGuid,
         This->DriverBindingHandle,
         Controller
         );

  FreePool (UsbXdciDevContext);

  DEBUG ((DEBUG_INFO, "UsbDeviceDxeDriverStop, Status: %r\n", Status));
  return EFI_SUCCESS;
}
