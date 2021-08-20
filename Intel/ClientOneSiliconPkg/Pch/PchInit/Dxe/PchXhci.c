/** @file
  Perform related functions for PCH XHCI in DXE phase

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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

#include "PchInit.h"
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/BaseLib.h>
#include <Register/UsbRegs.h>
#include <Register/PchRegs.h>
#include <Library/UsbLib.h>
#include <Library/UefiLib.h>
#include <Library/S3BootScriptLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <IndustryStandard/Pci30.h>


/*
  Helper function to return supported number of USB3 ports reported by Host Controller

  @param[in]  XhciMmioBase      Memory BAR of the xHCI controller
*/
STATIC
UINT32
GetUsb3PortCount (
  IN UINTN     XhciMmioBase
  )
{
  UINT32  PortCount;

  PortCount = ((MmioRead32 (XhciMmioBase + R_XHCI_MEM_XECP_SUPP_USB3_2) & B_XHCI_MEM_XECP_SUPP_USBX_2_CPC) >> N_XHCI_MEM_XECP_SUPP_USBX_2_CPC);
  ASSERT (PortCount <= MAX_USB3_PORTS);

  return (MIN (PortCount, MAX_USB3_PORTS));
}

/*
  Helper function to return supported number of USB2 ports reported by Host Controller

  @param[in]  XhciMmioBase      Memory BAR of the xHCI controller
*/
STATIC
UINT32
GetUsb2PortCount (
  IN UINTN     XhciMmioBase
  )
{
  UINT32  PortCount;

  PortCount = ((MmioRead32 (XhciMmioBase + R_XHCI_MEM_XECP_SUPP_USB2_2) & B_XHCI_MEM_XECP_SUPP_USBX_2_CPC) >> N_XHCI_MEM_XECP_SUPP_USBX_2_CPC);
  ASSERT (PortCount <= MAX_USB2_PORTS);

  return (MIN (PortCount, MAX_USB2_PORTS));
}

/**
  Configure USB3 Port to Compliance Mode

  @param  Event         Event whose notification function is being invoked.
  @param  Context       Pointer to the notification function's context, which is
                        always zero in current implementation.

**/
VOID
EFIAPI
Usb3ComplianceModeExitBootService (
  EFI_EVENT  Event,
  VOID       *Context
  )
{
  UINT32      Index;
  UINT32      Usb3PortSc;
  UINT64      XhciPciBase;
  UINT64      XhciMmioBase;
  UINT32      HccParams2;
  UINT32      Usb2PortCount;
  UINT32      Usb3PortCount;
  UINT32      Usb2DisabledPorts;
  UINT32      Usb3DisabledPorts;
  USB_HOB     *UsbConfigHob;

  DEBUG ((DEBUG_INFO, "Usb3ComplianceModeExitBootService () - Start\n"));
  //
  // Get USB Config data HOB
  //
  UsbConfigHob = NULL;
  UsbConfigHob = &(mPchConfigHob->Usb);

  if (UsbConfigHob == NULL) {
    DEBUG ((DEBUG_ERROR, "Usb3ComplianceModeExitBootService () - UsbConfigHob is NULL!\n"));
    return;
  }

  ///
  /// Setup USB Compliance Mode
  ///
  XhciPciBase = PCI_SEGMENT_LIB_ADDRESS (
                  DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                  PCI_BUS_NUMBER_PCH_XHCI,
                  PCI_DEVICE_NUMBER_PCH_XHCI,
                  PCI_FUNCTION_NUMBER_PCH_XHCI,
                  0
                  );
  if (PciSegmentRead32 (XhciPciBase) == 0xFFFFFFFF) {
    DEBUG ((DEBUG_ERROR, "xHCI not present, exiting...\n"));
    return;
  }
  XhciMmioBase  = PciSegmentRead32 (XhciPciBase + R_XHCI_CFG_BAR0);
  XhciMmioBase |= LShiftU64 ((UINT64) (PciSegmentRead32 (XhciPciBase + R_XHCI_CFG_BAR0 + 0x04)), 32);
  XhciMmioBase &= (UINT64)~(B_XHCI_CFG_ALIGN_MASK);

  HccParams2 = MmioRead32 ((UINTN) (XhciMmioBase + R_XHCI_MEM_HCCPARAMS2));
  DEBUG ((DEBUG_INFO, "HccParams2 = 0x%x\n", HccParams2));
  DEBUG ((DEBUG_INFO, "UsbConfigHob->EnableUsbComplianceMode = %d\n", UsbConfigHob->EnableUsbComplianceMode));

  if ((UsbConfigHob->EnableUsbComplianceMode == TRUE) && ((HccParams2 & B_XHCI_MEM_HCCPARAMS2_CTC) == B_XHCI_MEM_HCCPARAMS2_CTC)) {
    DEBUG ((DEBUG_INFO, "xHCI: Start Configuring Compliance Mode for USB3 Port\n"));
    Usb2DisabledPorts = 0;
    Usb2PortCount = GetUsb2PortCount (XhciMmioBase);
    for (Index = 0; Index < Usb2PortCount; Index++) {
      if (UsbConfigHob->PortUsb20[Index].Enable == FALSE) {
        Usb2DisabledPorts |= (BIT0 << Index);
      }
    }
    Usb3DisabledPorts = 0;
    Usb3PortCount = GetUsb3PortCount (XhciMmioBase);
    for (Index = 0; Index < Usb3PortCount; Index++) {
      if (UsbConfigHob->PortUsb30[Index].Enable == FALSE) {
        Usb3DisabledPorts |= (BIT0 << Index);
      }
    }

    for (Index = 0; Index < Usb3PortCount; Index++) {
      Usb3PortSc = MmioRead32 ((UINTN) (XhciMmioBase + R_XHCI_MEM_PORTSC_START_OFFSET + ((Usb2PortCount + Index) * 0x10)));

      if ((Usb3PortSc & V_XHCI_MEM_PORTSCXUSB3_PLS_RXDETECT) == V_XHCI_MEM_PORTSCXUSB3_PLS_RXDETECT) {
        DEBUG ((DEBUG_INFO, "USB3 port %d in RxDetect State, Set to Compliance Mode\n", Index));
        MmioWrite32 (
          (UINTN) ((XhciMmioBase + R_XHCI_MEM_PORTSC_START_OFFSET + ((Usb2PortCount + Index) * 0x10))),
          (V_XHCI_MEM_PORTSCXUSB3_PLS_COMPLIANCE | B_XHCI_MEM_PORTSCXUSB3_PP | B_XHCI_MEM_PORTSCXUSB3_LWS | B_XHCI_MEM_PORTSCXUSB3_WRC)
          );
        S3BootScriptSaveMemWrite (
          S3BootScriptWidthUint32,
          (UINTN) ((XhciMmioBase + R_XHCI_MEM_PORTSC_START_OFFSET + ((Usb2PortCount + Index) * 0x10))),
          1,
          (VOID *) (UINTN) ((XhciMmioBase + R_XHCI_MEM_PORTSC_START_OFFSET + ((Usb2PortCount + Index) * 0x10)))
          );
      } else {
        DEBUG ((DEBUG_INFO, "USB3 port %d NOT in RxDetect State, Skip Setting Compliance Mode\n", Index));
      }

      Usb3PortSc = MmioRead32 ((UINTN) (XhciMmioBase + R_XHCI_MEM_PORTSC_START_OFFSET + ((Usb2PortCount + Index)* 0x10)));
      if ((Usb3PortSc & (V_XHCI_MEM_PORTSCXUSB3_PLS_COMPLIANCE | B_XHCI_MEM_PORTSCXUSB3_PP)) == (V_XHCI_MEM_PORTSCXUSB3_PLS_COMPLIANCE | B_XHCI_MEM_PORTSCXUSB3_PP)) {
        DEBUG ((DEBUG_INFO, "USB3 port %d in Compliance Mode with PORTSC = 0x%X\n", Index, Usb3PortSc));
      } else {
        DEBUG ((DEBUG_INFO, "USB3 port %d NOT in Compliance Mode with PORTSC = 0x%X\n", Index, Usb3PortSc));
      }
    }
  } else {
    DEBUG ((DEBUG_INFO, "xHCI: Skip Configuring Compliance Mode for USB3 Port\n"));
  }

  DEBUG ((DEBUG_INFO, "Usb3ComplianceModeExitBootService () - End\n"));
}

/**
  In DXE phase, register USB3 Compliance Mode configuration function at ExitBootService
**/
VOID
ConfigureUsb3ComplianceDxe (
  VOID
  )
{
  EFI_EVENT  mExitBootServicesEvent;
  EFI_STATUS Status;

  mExitBootServicesEvent = NULL;

  DEBUG ((DEBUG_INFO, "ConfigureUsb3ComplianceDxe () - Start\n"));

  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  Usb3ComplianceModeExitBootService,
                  NULL,
                  &gEfiEventExitBootServicesGuid,
                  &mExitBootServicesEvent
                  );
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "ConfigureUsb3ComplianceDxe () - End\n"));
}
