/**@file
  This is the code that initializes xDCI.

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
#include <Library/UsbDeviceControllerInitLib.h>

#include <Library/PciSegmentLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PchPcrLib.h>
#include <Library/DebugLib.h>
#include <Library/PsfLib.h>
#include <Library/PmcPrivateLib.h>
#include <Library/IoLib.h>
#include <Library/TimerLib.h>
#include <Library/PreSiliconEnvDetectLib.h>
#include <IndustryStandard/Pci30.h>
#include <Register/UsbRegs.h>

#define XDCI_WAIT_FOR_D3      10000      ///< Timeout of 10000 * 10us = 100ms


#define V_XDCI_DID_CPU_UY_V17_0     0x8A15
#define V_XDCI_DID_PCH_LP_V17_0     0x34EE
#define V_XDCI_DID_PCH_N_V17_1      0x38EE
#define V_XDCI_DID_V1_1_PCH_N_V17_1 0x4DEE
#define V_XDCI_DID_PCH_H_V17_1      0x3DEE
#define V_XDCI_DID_PCH_B_V18_0      0x98EE
#define V_XDCI_DID_PCH_LP_V18_0     0xA0EE
#define V_XDCI_DID_PCH_LP_V18_0_1   0x4B7E
#define V_XDCI_DID_CPU_UY_V18_0     0x9A15
#define V_XDCI_DID_PCH_H_V18_1      0x43EE
#define V_XDCI_DID_PCH_LP_V18_1     0x7A6E
#define V_XDCI_DID_PCH_S_V18_1      0x7AE1

/**
  Function for detection of who owns the xDCI controller

  @param[in]  XdciPciBase       xDCI PCI config space address

  @retval     BOOLEAN           TRUE for known PCH xDCI device IDs, otherwise FALSE
**/
BOOLEAN
IsPchXdci (
  IN  UINT64          XdciPciBase
  )
{
  UINT16            ControllerDid;

  // Check device DID from given PCI config space
  ControllerDid = PciSegmentRead16 (XdciPciBase + PCI_DEVICE_ID_OFFSET);
  DEBUG ((DEBUG_INFO, "xDCI Controller DID: 0x%4X\n", ControllerDid));

  switch (ControllerDid) {
    case V_XDCI_DID_PCH_LP_V17_0:
    case V_XDCI_DID_PCH_N_V17_1:
    case V_XDCI_DID_V1_1_PCH_N_V17_1:
    case V_XDCI_DID_PCH_H_V17_1:
    case V_XDCI_DID_PCH_B_V18_0:
    case V_XDCI_DID_PCH_LP_V18_0:
    case V_XDCI_DID_PCH_H_V18_1:
    case V_XDCI_DID_PCH_LP_V18_1:
    case V_XDCI_DID_PCH_S_V18_1:
    case V_XDCI_DID_PCH_LP_V18_0_1:
      return TRUE;
    case V_XDCI_DID_CPU_UY_V17_0:
    case V_XDCI_DID_CPU_UY_V18_0:
      return FALSE;
    default:
      DEBUG ((DEBUG_ERROR, "Trying to configure unknown xDCI controller with DID 0x%4X\n", ControllerDid));
      if (!IsSimicsEnvironment () && !IsHfpgaEnvironment ()) {
        ASSERT (FALSE);
      }
      break;
  }

  return FALSE;
}

/**
  Common entry point for PCH and CPU for xDCI controller configuration flow

  @param[in]  UsbConfig         The USB_CONFIG policy instance
  @param[in]  XdciPciBase       xDCI PCI config space address
**/
VOID
XdciConfigure (
  IN  USB_CONFIG      *UsbConfig,
  IN  UINT64          XdciPciBase
  )
{
  UINT32             Timeout;
  BOOLEAN            IsPchXdciController;
  UINT32             XdciMmioBase;
  UINT16             Data16;

  if (PciSegmentRead16 (XdciPciBase + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    DEBUG ((DEBUG_INFO, "xDCI: PCI device NOT found. XdciPciBase 0x%8X\n", XdciPciBase));
    return;
  }

  IsPchXdciController = IsPchXdci (XdciPciBase);

  if (IsPchXdciController) {
    if (UsbConfig->UsbClockGatingEnable != 0) {
    //
    //  Enabling Trunk Clock Gating
    //  Set bit [5:0]=6'b111111
    //
    PchPcrAndThenOr32 (
      PID_OTG, R_OTG_PCR_IOSF_PMCTL,
      (UINT32) ~(0),
      (BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0)
      );
    } else {
      PchPcrAndThenOr32 (
        PID_OTG, R_OTG_PCR_IOSF_PMCTL,
        (UINT32) ~(BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0),
        (0)
        );
    }
  }

  //
  // Assign memory resources for xDCI
  //
  XdciMmioBase = PcdGet32 (PcdSiliconInitTempMemBaseAddr);

  PciSegmentWrite32 (XdciPciBase + PCI_BASE_ADDRESSREG_OFFSET+ 4, 0); // clearing upper part of MBAR address
  PciSegmentWrite32 (XdciPciBase + PCI_BASE_ADDRESSREG_OFFSET, XdciMmioBase);
  PciSegmentOr16 ((UINT64) (XdciPciBase + PCI_COMMAND_OFFSET), (UINT16) EFI_PCI_COMMAND_MEMORY_SPACE);

  if (UsbConfig->UsbPowerGatingEnable != 0) {
    //
    // Set the CPGE D3-Hot to Enable either BIT1 or BIT2 can be set at the same time
    // If BIT2 is set then function will power gate when idle and the PMCSR[1:0] register in the function = 2'b11 (D3)
    // xDCI cfg space 0xA2 bit [2:1] = 2'b10
    //
    PciSegmentAndThenOr16 (
      (XdciPciBase + R_XDCI_CFG_CPGE),
      (UINT16) ~(BIT1),
      (UINT16) (BIT2)
      );
  } else {
    PciSegmentAndThenOr16 (
      (XdciPciBase + R_XDCI_CFG_CPGE),
      (UINT16) ~(BIT2 | BIT1),
      (UINT16) (0)
      );
  }

  if (UsbConfig->UsbPowerGatingEnable != 0) {
  //
  // Set the bits below to 1 to enable the USB2 PHY suspend if no XDCI driver is loaded
  // Set xDCIBAR + C200h [6] to 1b
  //
  MmioOr32 (
    XdciMmioBase + R_XDCI_MEM_GUSB2PHYCFG,
    B_XDCI_MEM_GUSB2PHYCFG_SUSPHY
    );

  //
  // Enabling this bit will allow USB3.0 PHY to enter Suspend mode under valid conditions
  // Set xDCIBAR + C2C0h [17] to 1b
  //
  MmioOr32 (
    XdciMmioBase + R_XDCI_MEM_GUSB3PIPECTL0,
    B_XDCI_MEM_GUSB3PIPECTL0_SUSPEN_EN
    );
  } else {
    MmioAnd32 (
      XdciMmioBase + R_XDCI_MEM_GUSB2PHYCFG,
      (UINT32)~(B_XDCI_MEM_GUSB2PHYCFG_SUSPHY)
      );
    MmioAnd32 (
      XdciMmioBase + R_XDCI_MEM_GUSB3PIPECTL0,
      (UINT32)~(B_XDCI_MEM_GUSB3PIPECTL0_SUSPEN_EN)
      );
  }

  if (IsPchXdciController && UsbConfig->XdciConfig.Enable == 0) {
    DEBUG ((DEBUG_INFO, "xDCI: Device disabled\n"));

    //
    // Since xDCI function is disabled, the U2/U3 PME shall NOT be enabled
    //
    MmioAnd32 (
      XdciMmioBase + R_XDCI_MEM_APBFC_U3PMU_CFG5,
      (UINT32)~(BIT4 | BIT3)
      );

    //
    // 1. Set xDCIBAR + C110h [1] to 1b
    // It will allow hibernation through xDCI's MMIO register space
    //
    MmioOr32 (
      XdciMmioBase + R_XDCI_MEM_GCTL,
      B_XDCI_MEM_GCTL_GHIBEREN
      );

    //
    // 2. Put xDCI into D3 using xDCI MMIO space (APBFC_U3PMU_CFG4[1:0] = 2'b11)
    //
    MmioOr16 (
      XdciMmioBase + R_XDCI_MEM_APBFC_U3PMU_CFG4,
      (UINT16) (BIT1 | BIT0)
      );

    //
    // 3. Wait for D3 using the xDCI MMIO space (APBFC_U3PMU_CFG2[11:8] = 4'b1111)
    //
    Timeout = 0;
    Data16 = MmioRead16 (XdciMmioBase + R_XDCI_MEM_APBFC_U3PMU_CFG2);
    while (((Data16 & (BIT11 | BIT10 | BIT9 | BIT8)) != 0xF00) &&
           (Timeout < XDCI_WAIT_FOR_D3)) {
      MicroSecondDelay (10);
      Timeout++;
      Data16 = MmioRead16 (XdciMmioBase + R_XDCI_MEM_APBFC_U3PMU_CFG2);
    }

    //
    // 4. Set the xDCI PCI Config space PMCSR register to indicate D3 (XDCI cfg space 0x84 bit [1:0] = 2'b11)
    //
    PciSegmentOr8 (
      XdciPciBase + R_XDCI_CFG_PMCSR,
      (UINT8) (BIT1 | BIT0)
      );

    //
    // Clear memory resources for xDCI
    //
    PciSegmentAnd16 ((UINT64) (XdciPciBase + PCI_COMMAND_OFFSET), (UINT16) (~EFI_PCI_COMMAND_MEMORY_SPACE));
    PciSegmentWrite32 (XdciPciBase + PCI_BASE_ADDRESSREG_OFFSET, 0);

    if (IsPchXdciController) {
      //
      // 5. Disable xDCI function.
      //
      PsfDisableXdciDevice ();

      //
      // Disable XDCI Controller in PMC
      //
      PmcDisableXdci ();
    }
  } else {
    DEBUG ((DEBUG_INFO, "xDCI: Device enabled\n"));
    //
    //  Set xDCIBAR + 10F820h [13] to 1'1b
    //  It will Enable RxStandby control by XDCI. RxStandby will be dynamically controlled when entering/exiting P0
    //
    MmioOr16 (
      XdciMmioBase + R_XDCI_MEM_APBFC_U3PMU_CFG6,
      (UINT32) (BIT13)
      );

    //
    // Clear memory resources for xDCI
    //
    PciSegmentAnd16 ((UINTN) (XdciPciBase + PCI_COMMAND_OFFSET), (UINT16) (~EFI_PCI_COMMAND_MEMORY_SPACE));
    PciSegmentWrite32 (XdciPciBase + PCI_BASE_ADDRESSREG_OFFSET, 0);
  }
}
