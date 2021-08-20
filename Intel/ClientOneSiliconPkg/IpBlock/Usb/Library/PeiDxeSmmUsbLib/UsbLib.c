/** @file
  Implementation of functions available in general USB Library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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

#include <Library/UsbLib.h>

#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/IoLib.h>
#include <Register/UsbRegs.h>

/*
  Disables requested ports through Port Disable Override register programming

  @param[in]  XhciMmioBase            xHCI Memory BAR0 address
  @param[in]  Usb2DisabledPorts       Disabled ports bitmask with a bit for each USB2 port
                                      i.e. BIT0 is Port 0, BIT1 is Port 1 etc
  @param[in]  Usb3DisabledPorts       Disabled ports bitmask with a bit for each USB3 port
                                      i.e. BIT0 is Port 0, BIT1 is Port 1 etc

  @retval     EFI_SUCCESS             Programming ended successfully and no errors occured
              EFI_ACCESS_DENIED       Port Disable Override register was locked and write
                                      didn't go through. Platform may require restart to unlock.
*/
EFI_STATUS
UsbDisablePorts (
  IN  UINTN   XhciMmioBase,
  IN  UINT32  Usb2DisabledPorts,
  IN  UINT32  Usb3DisabledPorts
  )
{
  UINT32      XhciUsb2Pdo;
  UINT32      XhciUsb2PdoMask;
  UINT32      XhciUsb3Pdo;
  UINT32      XhciUsb3PdoMask;
  UINT32      XhciUsb2PdoRd;
  UINT32      XhciUsb3PdoRd;
  UINT32      HsPortCount;
  UINT32      SsPortCount;

  DEBUG ((DEBUG_INFO, "xHCI: Usb2DisabledPorts = 0x%x\n", Usb2DisabledPorts));
  DEBUG ((DEBUG_INFO, "xHCI: Usb3DisabledPorts = 0x%x\n", Usb3DisabledPorts));

  //
  // Read supported USB ports count from Host Controller
  //
  HsPortCount = (MmioRead32 (XhciMmioBase + R_XHCI_MEM_XECP_SUPP_USB2_2) & 0x0000FF00) >> 8;
  SsPortCount = (MmioRead32 (XhciMmioBase + R_XHCI_MEM_XECP_SUPP_USB3_2) & 0x0000FF00) >> 8;

  DEBUG ((DEBUG_INFO, "HsPortCount %d, SsPortCount %d\n", HsPortCount, SsPortCount));

  //
  // Masks for PDO registers based on supported number of ports, with a bit set for each supported port
  //
  XhciUsb2PdoMask = (UINT32)((1 << HsPortCount) - 1);
  XhciUsb3PdoMask = (UINT32)((1 << SsPortCount) - 1);

  DEBUG ((DEBUG_INFO, "XhciUsb2PdoMask 0x%8X, XhciUsb3PdoMask 0x%8X\n", XhciUsb2PdoMask, XhciUsb3PdoMask));

  XhciUsb2Pdo = Usb2DisabledPorts & XhciUsb2PdoMask;  // XHCI PDO for HS
  XhciUsb3Pdo = Usb3DisabledPorts & XhciUsb3PdoMask;  // XHCI PDO for SS

  DEBUG ((DEBUG_INFO, "XhciUsb2Pdo 0x%8X, XhciUsb3Pdo 0x%8X\n", XhciUsb2Pdo, XhciUsb3Pdo));

  //
  // USB2PDO and USB3PDO are Write-Once registers and bits in them are in the SUS Well.
  //
  MmioWrite32 (XhciMmioBase + R_PCH_XHCI_MEM_USB2PDO, XhciUsb2Pdo);
  MmioWrite32 (XhciMmioBase + R_PCH_XHCI_MEM_USB3PDO, XhciUsb3Pdo);

  XhciUsb2PdoRd = MmioRead32 (XhciMmioBase + R_PCH_XHCI_MEM_USB2PDO);
  XhciUsb3PdoRd = MmioRead32 (XhciMmioBase + R_PCH_XHCI_MEM_USB3PDO);

  //
  // If USB2PDO and USB3PDO are not updated successfully perform Warm Reset to unlock RWO bits.
  //
  if ((XhciUsb2Pdo != XhciUsb2PdoRd) || (XhciUsb3Pdo != XhciUsb3PdoRd)) {
    DEBUG ((DEBUG_INFO, "USB2PDO - Read: 0x%8X, Expected: 0x%8X\n", XhciUsb2PdoRd, XhciUsb2Pdo));
    DEBUG ((DEBUG_INFO, "USB3PDO - Read: 0x%8X, Expected: 0x%8X\n", XhciUsb3PdoRd, XhciUsb3Pdo));
    DEBUG ((DEBUG_ERROR, "UsbDisablePorts: PDO register value doesn't match expected value. PDO register might be locked.\n"));
    return EFI_ACCESS_DENIED;
  }

  return EFI_SUCCESS;
}
