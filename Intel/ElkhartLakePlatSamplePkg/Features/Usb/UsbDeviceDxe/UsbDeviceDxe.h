/** @file
  Header file for USBFN protocol driver.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

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


#ifndef __USB_DEVICE_DXE_H__
#define __USB_DEVICE_DXE_H__

#include <Uefi.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DevicePathLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PciSegmentLib.h>
#include <IndustryStandard/Pci22.h>
#include <Register/PchRegs.h>
#include <Register/UsbRegs.h>
#include <Protocol/PciIo.h>
#include <Protocol/EfiUsbFnIo.h>
#include <Protocol/UsbDeviceModeProtocol.h>
#include <SetupVariable.h>
#include "UsbFuncIo.h"
#include "UsbDeviceMode.h"
#include "MsgPrintf.h"


#define WA_FOR_INVALID_SETUP              1 // Fixme: WA enable for 1st EP0 XfrComplete event


#define PCI_DEVICE_NUMBER_PCH_OTG          PCI_DEVICE_NUMBER_PCH_XDCI
#define PCI_FUNCTION_NUMBER_PCH_OTG        PCI_FUNCTION_NUMBER_PCH_XDCI

#define R_PCH_OTG_BAR0                     0x10                         // BAR 0
#define B_PCH_OTG_BAR0_BA                  0xFFFFF000                   // Base Address
#define B_PCH_OTG_BAR0_TYPE                0x00000006                   // Type
#define B_PCH_OTG_BAR0_64_BIT              0x00000004                   // 64 bit
#define R_PCH_OTG_BAR_HIGH                 0x14                         // BAR High
#define R_PCH_OTG_BAR1                     0x18                         // BAR 1

#define B_PCH_XHCI_MEM_BASE_BA             0xFFFFFFFFFFFF0000           // Base Address
#define R_PCH_OTG_GEN_REGRW1               0xB0

#define PCI_IF_USBDEV                      0xFE

#define EFI_USB_DEV_SIGNATURE              0x55534244                   // "USBD"
#define USBFUIO_CONTEXT_FROM_PROTOCOL(a)   CR (a, USB_XDCI_DEV_CONTEXT, UsbFunIoProtocol, EFI_USB_DEV_SIGNATURE)
#define USBUSBD_CONTEXT_FROM_PROTOCOL(a)   CR (a, USB_XDCI_DEV_CONTEXT, UsbDevModeProtocol, EFI_USB_DEV_SIGNATURE)


typedef struct _USB_FUIO_EVENT_NODE        USB_FUIO_EVENT_NODE;

struct _USB_FUIO_EVENT_NODE{
  EFI_USBFN_MESSAGE              Message;
  UINTN                          PayloadSize;
  EFI_USBFN_MESSAGE_PAYLOAD      Payload;
  USB_FUIO_EVENT_NODE            *Nextptr;
};

typedef struct {
  UINTN                          Signature;
  UINTN                          XdciMmioBarAddr;
  EFI_HANDLE                     XdciHandle;
  EFI_USB_DEVICE_MODE_PROTOCOL   UsbDevModeProtocol;
  EFI_USBFN_IO_PROTOCOL          UsbFunIoProtocol;

  //
  // Structure members used by UsbFunIoProtocol.
  //
  USB_MEM_NODE                   *FirstNodePtr;
  EFI_USB_DEVICE_INFO            *DevInfoPtr;
  EFI_USB_CONFIG_INFO            IndexPtrConfig;
  EFI_USB_INTERFACE_INFO         IndexPtrInteface;
  USB_DEVICE_ENDPOINT_INFO       IndexPtrInEp;
  USB_DEVICE_ENDPOINT_INFO       IndexPtrOutEp;
  XDCI_CORE_HANDLE               *XdciDrvIfHandle;
  USB_DEV_CORE                   *DrvCore;
  UINT16                         VendorId;
  UINT16                         DeviceId;
  USBD_EP_XFER_REC               EndPointXferRec[DWC_XDCI_MAX_ENDPOINTS * 2];
  BOOLEAN                        StartUpController;
  BOOLEAN                        DevReConnect;
  BOOLEAN                        DevResetFlag;
  EFI_EVENT                      TimerEvent;
  USB_FUIO_EVENT_NODE            *EventNodePtr;
  //
  // Following structure members are used by UsbDevModeProtocol.
  //

} USB_XDCI_DEV_CONTEXT;


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
  );

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
  );

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
  );

/**
  Platform specific initialization.

**/
VOID
EFIAPI
UsbPlatformSpecificInit (
  VOID
  );

extern EFI_COMPONENT_NAME_PROTOCOL    mUsbDeviceDxeComponentName;
extern EFI_COMPONENT_NAME2_PROTOCOL   mUsbDeviceDxeComponentName2;

#endif
