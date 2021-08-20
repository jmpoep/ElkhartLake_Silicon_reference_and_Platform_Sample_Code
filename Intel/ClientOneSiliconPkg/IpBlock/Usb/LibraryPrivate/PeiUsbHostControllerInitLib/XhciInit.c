/** @file
  Library for USB controller initialization for both CPU and PCH.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2020 Intel Corporation.

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
#include <Library/UsbHostControllerInitLib.h>

// General includes
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/TimerLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/GpioPrivateLib.h>
#include <Library/PmcPrivateLib.h>
#include <IndustryStandard/Pci30.h>
#include <Register/UsbRegs.h>
#include <Register/DciRegs.h>
#include <Library/PcdLib.h>
#include <Library/UsbLib.h>
#include <Library/PreSiliconEnvDetectLib.h>

// PCH specific includes
#include <Library/PchPcrLib.h>
#include <Library/PsfLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PchSbiAccessLib.h>
#include <Library/DciPrivateLib.h>

// SA specific includes
#include <Library/CpuPlatformLib.h>

#include <Library/SiScheduleResetLib.h>
#include <Library/HobLib.h>
#include <Library/PeiHsioLib.h>

#include <Library/MeFwStsLib.h>
#include <Library/PreSiliconEnvDetectLib.h>


// xHCI controller DID for USB IP Version detection
#define V_XHCI_DID_CPU_LP_V17_0     0x8A13
#define V_XHCI_DID_PCH_LP_V17_0     0x34ED
#define V_XHCI_DID_CPU_SH_V17_1     0x8AA1
#define V_XHCI_DID_CPU_R_V17_1      0x8AB1
#define V_XHCI_DID_PCH_N_V17_1      0x38ED
#define V_XHCI_DID_V1_1_PCH_N_V17_1 0x4DED
#define V_XHCI_DID_PCH_H_V17_1      0x3DED
#define V_XHCI_DID_PCH_B_V18_0      0x98ED
#define V_XHCI_DID_CPU_UY_V18_0     0x9A13
#define V_XHCI_DID_PCH_LP_V18_0     0xA0ED
#define V_XHCI_DID_PCH_LP_V18_0_1   0x4B7D
#define V_XHCI_DID_PCH_H_V18_1      0x43ED
#define V_XHCI_DID_CPU_H_V18_1      0x9A17
#define V_XHCI_DID_PCH_LP_V18_1     0x7A6D
#define V_XHCI_DID_PCH_S_V18_1      0x7AE0


#define V_XHCI_DID_PCH_SERVER_V18_0 0x1BCD


// xHC Latency Tolerance Parameters used during initialization process
#define V_XHCI_LTR_HIT_1    0x033200A3
#define V_XHCI_LTR_HIT_2    0x00050002
#define V_XHCI_LTR_HIT_3    0x01990208
#define V_XHCI_LTR_MIT_1    0x00CB0028
#define V_XHCI_LTR_MIT_2    0x00050002
#define V_XHCI_LTR_MIT_3    0x011E011E
#define V_XHCI_LTR_LIT_1    0x0099001E
#define V_XHCI_LTR_LIT_2    0x00050002
#define V_XHCI_LTR_LIT_3    0x00300030

// USB IP Version enumeration
typedef enum {
  V17_0 = 0,
  V17_1,
  V18_0,
  V18_1
} USB_IP_VERSION;

// xHCI controller information structure
typedef struct {
  BOOLEAN          OnSouth;
  USB_IP_VERSION   IpVersion;       // Version of USB IP (value according to USB_IP_VERSION enumeration
  BOOLEAN          IsCpuStepA0;     // Flag for applying programming in specific steps for CPU
  UINT16           DeviceId;        // Host Controller device ID
  UINT32           UsbLtrHigh;      // High Idle Time Control LTR parameters
  UINT32           UsbLtrMid;       // Medium Idle Time Control LTR parameters
  UINT32           UsbLtrLow;       // Low Idle Time Control LTR parameters
} USB_CONTROLLER_INFO;

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
  Helper function for checking if USB2 Port Reset Messaging to CPU is supported

  @param[out] HcInfo              xHCI controller information structure

  @retval TRUE      USB2 Port Reset Messaging is supported
  @retval FALSE     USB2 Port Reset Messaging is not supported
**/
STATIC
BOOLEAN
IsPortResetMessagingSupported (
  IN USB_CONTROLLER_INFO   *HcInfo
  )
{
  CPU_GENERATION  CpuGeneration;
  CPU_STEPPING    CpuStepping;

  //
  // If enabled PCH xHCI will signal USB2 Port Reset to CPU xHCI
  // Invalid setting for unsupported combinations will lead to USB2 enumeration hangs
  //
  // Only supported on TGL B0 and newer
  //
  CpuGeneration = GetCpuGeneration ();
  CpuStepping   = GetCpuStepping ();
  return ((CpuGeneration == EnumTglCpu) && (CpuStepping >= EnumTglB0));
}

/**
  Helper function for gathering of xHCI controller features and infromation

  @param[in]  XhciPciBase         xHCI PCI config space address
  @param[out] HcInfo              xHCI controller information structure
**/
STATIC
VOID
GetXhciControllerInfo (
  IN  UINT64                XhciPciBase,
  OUT USB_CONTROLLER_INFO   *HcInfo
  )
{
  UINT16                ControllerDid;

  ZeroMem (HcInfo, sizeof (USB_CONTROLLER_INFO));

  // Check device DID from given PCI config space
  ControllerDid     = PciSegmentRead16 (XhciPciBase + PCI_DEVICE_ID_OFFSET);
  HcInfo->DeviceId  = ControllerDid;

  switch (HcInfo->DeviceId) {
    // USB IP V17.X
    case V_XHCI_DID_CPU_LP_V17_0:
      HcInfo->OnSouth   = FALSE;
      HcInfo->IpVersion = V17_0;
      HcInfo->IsCpuStepA0 = (GetCpuStepping() == EnumIclA0);
      break;

    case V_XHCI_DID_PCH_LP_V17_0:
      HcInfo->OnSouth   = TRUE;
      HcInfo->IpVersion = V17_0;
      break;

    case V_XHCI_DID_CPU_SH_V17_1:
    case V_XHCI_DID_CPU_R_V17_1:
      HcInfo->OnSouth   = FALSE;
      HcInfo->IpVersion = V17_1;
      break;

    case V_XHCI_DID_PCH_N_V17_1:
    case V_XHCI_DID_V1_1_PCH_N_V17_1:
    case V_XHCI_DID_PCH_H_V17_1:
      HcInfo->OnSouth   = TRUE;
      HcInfo->IpVersion = V17_1;
      break;

    // USB IP V18.X
    case V_XHCI_DID_PCH_B_V18_0:
    case V_XHCI_DID_PCH_LP_V18_0:
    case V_XHCI_DID_PCH_SERVER_V18_0:
    case V_XHCI_DID_PCH_LP_V18_0_1:
      HcInfo->OnSouth   = TRUE;
      HcInfo->IpVersion = V18_0;
      break;

    case V_XHCI_DID_CPU_UY_V18_0:
      HcInfo->OnSouth   = FALSE;
      HcInfo->IpVersion = V18_0;
      break;

    case V_XHCI_DID_CPU_H_V18_1:
      HcInfo->OnSouth   = FALSE;
      HcInfo->IpVersion = V18_1;
      break;

    case V_XHCI_DID_PCH_LP_V18_1:
    case V_XHCI_DID_PCH_S_V18_1:
    case V_XHCI_DID_PCH_H_V18_1:
      HcInfo->OnSouth   = TRUE;
      HcInfo->IpVersion = V18_1;
      break;

    default:
      DEBUG ((DEBUG_ERROR, "Trying to configure unknown xHCI controller with DID 0x%4X\n", HcInfo->DeviceId));
      if (!IsSimicsEnvironment () && !IsHfpgaEnvironment ()) {
        ASSERT (FALSE);
      }
      break;
  }

  if (HcInfo->DeviceId == V_XHCI_DID_PCH_B_V18_0) {
    HcInfo->UsbLtrHigh = V_XHCI_LTR_HIT_1;
    HcInfo->UsbLtrMid  = V_XHCI_LTR_MIT_1;
    HcInfo->UsbLtrLow  = V_XHCI_LTR_LIT_1;
  } else if ((HcInfo->IpVersion == V17_0) || (HcInfo->IpVersion == V17_1)) {
    if (HcInfo->OnSouth) {
      HcInfo->UsbLtrHigh = V_XHCI_LTR_HIT_3;
      HcInfo->UsbLtrMid  = V_XHCI_LTR_MIT_3;
      HcInfo->UsbLtrLow  = V_XHCI_LTR_LIT_3;
    } else {
      HcInfo->UsbLtrHigh = V_XHCI_LTR_HIT_2;
      HcInfo->UsbLtrMid  = V_XHCI_LTR_MIT_2;
      HcInfo->UsbLtrLow  = V_XHCI_LTR_LIT_2;
    }
  } else {
    HcInfo->UsbLtrHigh = V_XHCI_LTR_HIT_2;
    HcInfo->UsbLtrMid  = V_XHCI_LTR_MIT_2;
    HcInfo->UsbLtrLow  = V_XHCI_LTR_LIT_2;
  }

  DEBUG ((DEBUG_INFO, "xHCI Controller DID: 0x%4X\n", ControllerDid));
  DEBUG ((DEBUG_INFO, "Params:\n UsbIpVersion: 0x%2X, Device: 0x%4X\n", HcInfo->IpVersion, HcInfo->DeviceId));
}

/**
  Program and enable XHCI Memory Space

  @param[in] XhciPciBase          XHCI PCI Base Address
  @param[in] XhciMmioBase         Memory base address of XHCI Controller
**/
STATIC
VOID
XhciMemorySpaceOpen (
  IN  UINT64                      XhciPciBase,
  IN  UINT32                      XhciMmioBase
  )
{
  //
  // Assign memory resources
  //
  PciSegmentWrite32 (XhciPciBase + R_XHCI_CFG_BAR0, XhciMmioBase);
  PciSegmentWrite32 (XhciPciBase + R_XHCI_CFG_BAR0 + 4, 0);

  PciSegmentOr16 (
    XhciPciBase + PCI_COMMAND_OFFSET,
    (UINT16) (EFI_PCI_COMMAND_MEMORY_SPACE)
    );
}

/**
  Clear and disable XHCI Memory Space

  @param[in] XhciPciBase          XHCI PCI Base Address
**/
STATIC
VOID
XhciMemorySpaceClose (
  IN  UINT64                      XhciPciBase
  )
{
  //
  // Clear memory resources
  //
  PciSegmentAnd16 (
    XhciPciBase + PCI_COMMAND_OFFSET,
    (UINT16) ~(EFI_PCI_COMMAND_MEMORY_SPACE)
    );

  PciSegmentWrite32 ((XhciPciBase + R_XHCI_CFG_BAR0), 0);
  PciSegmentWrite32 ((XhciPciBase + R_XHCI_CFG_BAR0 + 4), 0);
}

/**
  Verifies if OverCurrent pins in USB config Block are from valid range

  @param[in]  UsbConfig          The policy for USB configuration

  @retval     BOOLEAN            Over Current pin assignment validity
**/
STATIC
BOOLEAN
XhciIsOverCurrentMappingValid (
  IN  CONST USB_CONFIG            *UsbConfig
  )
{
  UINT32  PortIndex;
  UINT32  OcPin;

  if (UsbConfig == NULL) {
    DEBUG ((DEBUG_ERROR, "[%a] Invalid USB Config Block\n", __FUNCTION__));
    return FALSE;
  }

  for (PortIndex = 0; PortIndex < GetPchUsb2MaxPhysicalPortNum (); PortIndex++) {
    OcPin = UsbConfig->PortUsb20[PortIndex].OverCurrentPin;
    if (OcPin >= UsbOverCurrentPinMax && OcPin < UsbOverCurrentPinSkip) {
      DEBUG ((DEBUG_ERROR, "[%a] Invalid OC pin for USB2 port %d\n", __FUNCTION__, PortIndex));
      return FALSE;
    }
  }

  for (PortIndex = 0; PortIndex < GetPchXhciMaxUsb3PortNum (); PortIndex++) {
    OcPin = UsbConfig->PortUsb30[PortIndex].OverCurrentPin;
    if (OcPin >= UsbOverCurrentPinMax && OcPin < UsbOverCurrentPinSkip) {
      DEBUG ((DEBUG_ERROR, "[%a] Invalid OC pin for USB3 port %d\n", __FUNCTION__, PortIndex));
      return FALSE;
    }
  }

  return TRUE;
}

/**
  Setup XHCI Over-Current Mapping

  @param[in] HcInfo               xHCI controller information structure
  @param[in] UsbConfig            The policy for USB configuration
  @param[in] XhciPciBase          XHCI PCI Base Address
  @param[in] XhciMmioBase         XHCI Memory Bar base address
**/
STATIC
VOID
XhciOverCurrentMapping (
  IN  CONST USB_CONTROLLER_INFO   *HcInfo,
  IN  CONST USB_CONFIG            *UsbConfig,
  IN  UINT64                      XhciPciBase,
  IN  UINT32                      XhciMmioBase
  )
{
  UINT32                   Index;
  UINT32                   U2OcMBuf[PCH_USB_OC_PINS_MAX];
  UINT32                   U3OcMBuf[PCH_USB_OC_PINS_MAX];
  UINT32                   OcPin;
  UINT32                   OcPinsUsedMask;

  if (!UsbConfig->OverCurrentEnable) {
    //
    // Clear Over-Current registers to switch off Over-Current detection.
    //
    DEBUG ((DEBUG_WARN, "Clear Over-Current registers to enable OBS pins usage\n"));

    for (Index = 0; Index < PCH_USB_OC_PINS_MAX; Index++) {
      if (HcInfo->IpVersion >= V17_1) {
        MmioWrite32 (XhciMmioBase + R_XHCI_MEM_U2OCM + (Index * 4), 0);
        MmioWrite32 (XhciMmioBase + R_XHCI_MEM_U3OCM + (Index * 4), 0);
      } else {
        PciSegmentWrite32 (XhciPciBase + R_XHCI_CFG_U2OCM + (Index * 4), 0);
        PciSegmentWrite32 (XhciPciBase + R_XHCI_CFG_U3OCM + (Index * 4), 0);
      }
    }

    //
    // Exit function after clearing Overcurrent mapping
    //
    return;
  }

  //
  // Verify proper Over Current pins are used in policy
  //
  if (!XhciIsOverCurrentMappingValid (UsbConfig)) {
    DEBUG ((DEBUG_ERROR, "Over Current pin mapping uses invalid values. Skipping USB Over Current programming.\n"));
    return;
  }

  ZeroMem (U2OcMBuf, sizeof (U2OcMBuf));
  ZeroMem (U3OcMBuf, sizeof (U3OcMBuf));
  OcPinsUsedMask = 0;

  for (Index = 0; Index < GetPchUsb2MaxPhysicalPortNum (); Index++) {
    if (UsbConfig->PortUsb20[Index].OverCurrentPin != UsbOverCurrentPinSkip) {
      OcPin = UsbConfig->PortUsb20[Index].OverCurrentPin;
      U2OcMBuf[OcPin] |= (UINT32) (BIT0 << Index);
      OcPinsUsedMask |= (UINT32) (BIT0 << OcPin);
    }
  }

  for (Index = 0; Index < GetPchXhciMaxUsb3PortNum (); Index++) {
    if (UsbConfig->PortUsb30[Index].OverCurrentPin != UsbOverCurrentPinSkip) {
      OcPin = UsbConfig->PortUsb30[Index].OverCurrentPin;
      U3OcMBuf[OcPin] |= (UINT32) (BIT0 << Index);
      OcPinsUsedMask |= (UINT32) (BIT0 << OcPin);
    }
  }

  for (Index = 0; Index < PCH_USB_OC_PINS_MAX; Index++) {
    if (HcInfo->IpVersion >= V17_1) {
      MmioWrite32 (XhciMmioBase + R_XHCI_MEM_U2OCM + (Index * 4), U2OcMBuf[Index]);
      MmioWrite32 (XhciMmioBase + R_XHCI_MEM_U3OCM + (Index * 4), U3OcMBuf[Index]);
    } else {
      PciSegmentWrite32 (XhciPciBase + R_XHCI_CFG_U2OCM + (Index * 4), U2OcMBuf[Index]);
      PciSegmentWrite32 (XhciPciBase + R_XHCI_CFG_U3OCM + (Index * 4), U3OcMBuf[Index]);
    }
  }

  for (Index = 0; Index < PCH_USB_OC_PINS_MAX; Index++) {
    if ((OcPinsUsedMask >> Index) & BIT0) {
      GpioEnableUsbOverCurrent (Index);
    }
  }
}

/**
  Performs basic configuration of USB3 (xHCI) controller.

  @param[in]  HcInfo              xHCI controller information structure
  @param[in]  XhciPciBase         xHCI PCI config space address
  @param[in]  XhciMmioBase        Memory base address of xHCI Controller
**/
STATIC
VOID
XhciHcInit (
  IN  USB_CONTROLLER_INFO   *HcInfo,
  IN  UINT64                XhciPciBase,
  IN  UINT32                XhciMmioBase,
  IN  USB_CONFIG            *UsbConfig
  )
{
  UINT32          Data32;
  UINT32          Data32Or;
  UINT32          Data32And;
  UINT16          Data16Or;
  UINT32          SsPortCount;
  UINT32          XhciUsb3Pdo;
  UINT32          XhciUsb3PortsMask;

  DEBUG ((DEBUG_INFO, "XhciHcInit XhciMmio Base = 0x%x\n", XhciMmioBase));

  SsPortCount = GetUsb3PortCount (XhciMmioBase);

  DEBUG ((DEBUG_INFO, "Number of supported Super Speed Ports  = %d\n", SsPortCount));
  DEBUG ((DEBUG_INFO, "Number of supported High Speed Ports   = %d\n", GetUsb2PortCount (XhciMmioBase)));

  //
  //  XHCC1 - XHCI System Bus Configuration 1
  //  Address Offset: 0x40
  //  Writes to this registers needs to be performed per bytes to avoid touching bit 31
  //  Bit 31 is used to lock RW/L bits and can be writen once.
  //
  if (HcInfo->IpVersion < V18_0) {
    PciSegmentOr8 (
      XhciPciBase + R_XHCI_CFG_XHCC1 + 1,
      (UINT8) (BIT0)
      );
    PciSegmentOr8 (
      XhciPciBase + R_XHCI_CFG_XHCC1 + 2,
      (UINT8) (BIT5 | BIT4 | BIT2)
      );
  } else {
    PciSegmentOr8 (
      XhciPciBase + R_XHCI_CFG_XHCC1 + 3,
      (UINT8) (BIT5)
      );
  }

  //
  //  DBGDEV_CTRL_REG1 - Debug Device Control Register 1
  //  Address Offset: 0x8754
  //
  if (UsbConfig->UsbClockGatingEnable != 0) {
    MmioOr32 (
      (XhciMmioBase + R_XHCI_MEM_DBGDEV_CTRL_REG1),
      (UINT32) (BIT9)
      );
  } else {
    MmioAnd32 (
      (XhciMmioBase + R_XHCI_MEM_DBGDEV_CTRL_REG1),
      (UINT32)~(BIT9)
      );
  }

  //
  //  XHCC2 - XHCI System Bus Configuration 2
  //  Address Offset: 0x44
  //
  Data32Or     = (BIT22 | BIT0);
  Data32And    = (UINT32)~(BIT11);
  if (!HcInfo->OnSouth || (HcInfo->IpVersion < V18_0)) {
    Data32Or  |= (BIT25 | BIT24 | BIT23 | BIT2 | BIT1);
  }
  if (HcInfo->IpVersion < V18_0) {
    Data32Or  |= (BIT21 | 0x7F << N_XHCI_CFG_XHCC2_UNPPA | BIT10 | BIT9 | BIT7 | BIT3);
    Data32And &= (UINT32)~((B_XHCI_CFG_XHCC2_UNPPA << N_XHCI_CFG_XHCC2_UNPPA) |
                  BIT8 | BIT6 | BIT5 | BIT4);
  } else {
    Data32And &= (UINT32)~(BIT10);
  }
  PciSegmentAndThenOr32 (
    XhciPciBase + R_XHCI_CFG_XHCC2,
    Data32And,
    Data32Or
    );

  //
  //  PMCTRL2 - Power Management Control 2
  //  Address Offset: 0x8468
  //  This bits must be set before setting USB_SRAM_PG_EN (bit27) in XHCLKGTEN
  //
  if (UsbConfig->UsbPowerGatingEnable != 0) {
    MmioOr32 (
      (XhciMmioBase + R_XHCI_MEM_PMCTRL2),
      (UINT32) (BIT5 | BIT0)
      );
  } else {
    MmioAndThenOr32 (
      (XhciMmioBase + R_XHCI_MEM_PMCTRL2),
      (UINT32)~(BIT5),
      (UINT32) (BIT0)
      );
  }

  if (HcInfo->IpVersion < V18_0) {
    //
    //  XHCLKGTEN - Clock Gating
    //  Address Offset: 0x50
    //
    if (HcInfo->OnSouth || (!HcInfo->OnSouth && GetCpuStepping() < EnumIclD0)) {
      Data32 = 0x0FDC6D7F;
      if ((HcInfo->IpVersion == V17_1) ||
        ((HcInfo->DeviceId == V_XHCI_DID_CPU_LP_V17_0) && !HcInfo->IsCpuStepA0)) {
        Data32 |= (BIT17 | BIT16);
        Data32 &= (UINT32)~(BIT6);
      }
      PciSegmentWrite32 (
        (XhciPciBase + R_XHCI_CFG_XHCLKGTEN),
        Data32
        );
    }

    //
    //  MSI_NEXT - Next Item Pointer
    //  Address Offset: 0x81
    //
    PciSegmentWrite8 (
      (XhciPciBase + R_XHCI_CFG_MSI_NEXT),
      0x90
      );
  }
  if (UsbConfig->UsbClockGatingEnable == 0) {
    PciSegmentAndThenOr32 (
      (XhciPciBase + R_XHCI_CFG_XHCLKGTEN),
      (UINT32)~(BIT31 | BIT26 | BIT25 | BIT24 | BIT15 | BIT14 | BIT13 | BIT12 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0),
      (UINT32) (BIT29)
      );
  }
  if (UsbConfig->UsbPowerGatingEnable == 0) {
    PciSegmentAnd32 (
      (XhciPciBase + R_XHCI_CFG_XHCLKGTEN),
      (UINT32)~(BIT27)
      );
  }

  //
  //  PCE - Power Control Enables
  //  Address Offset: 0xA2
  //
  if (UsbConfig->UsbPowerGatingEnable != 0) {
    if (HcInfo->OnSouth || (!HcInfo->OnSouth && GetCpuStepping() < EnumIclD0)) {
      Data16Or  = (UINT16) BIT3;
      if (HcInfo->OnSouth) {
        Data16Or |= (BIT2 | BIT1);
      }
      PciSegmentOr16 (
        (XhciPciBase + R_XHCI_CFG_PCE),
        Data16Or
        );
    }
  } else {
    PciSegmentAnd16 (
      (XhciPciBase + R_XHCI_CFG_PCE),
      (UINT16)~(BIT5 | BIT3 | BIT2 | BIT1)
      );
  }

  //
  //  HSCFG2 - High Speed Configuration 2
  //  Address Offset: 0xA4
  //
  Data32Or = 0;
  if (HcInfo->IpVersion < V18_0) {
    Data32Or |= (BIT12 | BIT11);
  }
  PciSegmentAndThenOr32 (
    (XhciPciBase + R_XHCI_CFG_HSCFG2),
    (UINT32)~(BIT15 | BIT14 | BIT13),
    Data32Or
    );

  //
  //  SSCFG1 - SuperSpeed Configuration 1
  //  Address Offset: 0xA8
  //
  Data32Or = (BIT14);
  if (HcInfo->IpVersion < V18_0) {
    Data32Or |= (BIT17);
  } else {
    if (HcInfo->OnSouth) {
      Data32Or |= BIT12;
    }
  }
  PciSegmentOr32 (
    (XhciPciBase + R_XHCI_CFG_SSCFG1),
    Data32Or
    );

  //
  //  HSCFG1 - High Speed Configuration 1
  //  Address offset: 0xAC
  //
  Data32Or = 0;
  if ((HcInfo->IpVersion >= V18_0) && HcInfo->OnSouth) {
    Data32Or |= BIT9;
  }
  PciSegmentAndThenOr32 (
    (XhciPciBase + R_XHCI_CFG_HSCFG1),
    (UINT32)~(BIT19 | BIT18),
    Data32Or
    );

  //
  //  XHCC3 - XHCI System Bus Configuration 3
  //  Address Offset: 0xFC
  //
  if (HcInfo->DeviceId == V_XHCI_DID_PCH_SERVER_V18_0) {
    PciSegmentAnd32 (
      (XhciPciBase + R_XHCI_CFG_XHCC3),
      (UINT32)~(BIT4)
      );
  } else {
    PciSegmentOr32 (
      (XhciPciBase + R_XHCI_CFG_XHCC3),
      (UINT32) (BIT4)
      );
  }

  if (HcInfo->IpVersion < V18_0) {
    //
    //  HCIVERSION - Host Controller Interface Version Number
    //  Address Offset: 0x02
    //  Only for IP V17.1 and earlier
    //
    MmioAndThenOr32 (
      (XhciMmioBase + R_XHCI_MEM_CAPLENGTH),
      (UINT32) B_XHCI_MEM_HCIVERSION,
      (UINT32) (V_XHCI_MEM_HCIVERSION << N_XHCI_MEM_HCIVERSION)
      );

    //
    //  HCSPARAMS3 - Structural Parameters 3
    //  Address Offset: 0x0C
    //
    Data32Or = (UINT32) (0xA0 << N_XHCI_MEM_HCSPARAMS3_U2DEL | 0x0A);
    if (((HcInfo->DeviceId == V_XHCI_DID_CPU_LP_V17_0) && HcInfo->IsCpuStepA0) ||
        ((HcInfo->DeviceId == V_XHCI_DID_PCH_LP_V17_0) && (PchStepping () == PCH_A0))) {
      Data32Or = (0x0396 << N_XHCI_MEM_HCSPARAMS3_U2DEL) | (Data32Or & B_XHCI_MEM_HCSPARAMS3_U1DEL);
    }
    if ((HcInfo->IpVersion >= V18_0) && !HcInfo->OnSouth) {
      Data32Or = (UINT32) ((0x190 << N_XHCI_MEM_HCSPARAMS3_U2DEL) | (Data32Or & 0xFF));
    }
    MmioAndThenOr32 (
      (XhciMmioBase + R_XHCI_MEM_HCSPARAMS3),
      B_XHCI_MEM_HCSPARAMS3,
      Data32Or
      );

    //
    //  HCCPARAMS1 - Capability Parameters 1
    //  Address Offset: 0x10
    //
    MmioOr32 (
      (XhciMmioBase + R_XHCI_MEM_HCCPARAMS1),
      (UINT32) (BIT11)
      );


    //
    //  XECP_CMDM_CTRL_REG1 - Command Manager Control 1
    //  Address Offset: 0x818C
    //
    MmioAndThenOr32 (
      (XhciMmioBase + R_XHCI_MEM_XECP_CMDM_CTRL_REG1),
      (UINT32)~(BIT20 | BIT8),
      (UINT32) (BIT16)
      );

    //
    //  XECP_CMDM_CTRL_REG2 - Command Manager Control 2
    //  Address offset: 0x8190
    //
    MmioAnd32 (
      (XhciMmioBase + R_XHCI_MEM_XECP_CMDM_CTRL_REG2),
      (UINT32)~(BIT14)
      );

    //
    //  XECP_CMDM_CTRL_REG3 - Command Manager Control 3
    //  Address offset: 0x8194
    //
    MmioOr32 (
      (XhciMmioBase + R_XHCI_MEM_XECP_CMDM_CTRL_REG3),
      (UINT32) (BIT25)
      );

    //
    //  HOST_CTRL_ODMA_REG - Host Control ODMA Register
    //  Address Offset: 0x8098
    //
    MmioAnd32 (
      (XhciMmioBase + R_XHCI_MEM_HOST_CTRL_ODMA_REG),
      (UINT32)~(BIT2 | BIT1)
      );
  }

  //
  //  HCCPARAMS2 - Capability Parameters 2
  //  Address Offset: 0x1C
  //
  Data32Or    = 0;
  if (HcInfo->IpVersion < V18_0) {
    Data32Or |= (BIT6 | BIT4);
  } else {
    Data32Or |= BIT8;
  }
  MmioOr32 (
    (XhciMmioBase + R_XHCI_MEM_HCCPARAMS2),
    Data32Or
    );

  //
  //  PMCTRL - Power Management Control
  //  Address Offset: 0x80A4
  //
  Data32Or    = (UINT32) (BIT7 | BIT4 | BIT3);
  Data32And   = (UINT32)~(BIT25 | BIT23 | BIT22);
  if (HcInfo->IpVersion < V18_0) {
    Data32Or  |= (BIT30 | BIT27 | BIT24 | BIT16 | (0x50 << N_XHCI_MEM_PMCTRL_SSU3LPFS_DET) | BIT2);
    Data32And &= (UINT32)~(BIT31 | BIT29 | B_XHCI_MEM_PMCTRL_SSU3LFPS_DET);
  }
  if (HcInfo->DeviceId == V_XHCI_DID_PCH_B_V18_0) {
    Data32Or  |= (UINT32) (BIT23 | BIT22);
  }
  if (HcInfo->IsCpuStepA0 ||
    ((HcInfo->DeviceId == V_XHCI_DID_PCH_LP_V17_0) && (PchStepping () < PCH_B0))) {
    Data32Or |= BIT17;
  }
  if (UsbConfig->UsbPowerGatingEnable == 0) {
    Data32Or |= (UINT32) (BIT29 | BIT27 | BIT24 | BIT23 | BIT22);
  }
  MmioAndThenOr32 (
    (XhciMmioBase + R_XHCI_MEM_PMCTRL),
    Data32And,
    Data32Or
    );

  //
  //  Host Controller Misc Reg 2
  //  Address Offset: 0x80B4
  //
  Data32And = ~0u;
  Data32Or  = (UINT32) (BIT23);
  if (HcInfo->IpVersion < V18_0) {
    Data32And &= (UINT32)~(BIT5 | BIT2);
    Data32Or  |= (UINT32) (BIT28 | BIT7);
  }
  MmioAndThenOr32 (
    (XhciMmioBase + R_XHCI_MEM_HOST_CTRL_MISC_REG_2),
    Data32And,
    Data32Or
    );

  //
  //  HOST_CTRL_PORT_LINK_REG - SuperSpeed Port Link Control
  //  Address Offset: 0x80EC
  //
  Data32Or    = 0u;
  Data32And   = (UINT32)~(BIT17 | BIT14 | BIT13 | BIT12);
  if (HcInfo->IpVersion < V18_0) {
    Data32And &= (UINT32)~(BIT19);
    if (((HcInfo->DeviceId == V_XHCI_DID_CPU_LP_V17_0) && (HcInfo->IsCpuStepA0)) ||
        ((HcInfo->DeviceId == V_XHCI_DID_PCH_LP_V17_0) && (PchStepping () == PCH_A0))) {
      Data32Or |= (BIT14 | BIT13);
    }
  } else {
    Data32And &= (UINT32)~(BIT11 | BIT10 | BIT9);
  }
  MmioAndThenOr32 (
    (XhciMmioBase + R_XHCI_MEM_HOST_CTRL_PORT_LINK_REG),
    Data32And,
    Data32Or
    );

  if (HcInfo->IpVersion < V18_0) {
    //
    //  Host Controller Misc Reg
    //  Address Offset: 0x80B0
    //
    MmioAndThenOr32 (
      (XhciMmioBase + R_XHCI_MEM_HOST_CTRL_MISC_REG),
      (UINT32)~(BIT24 | BIT18 | BIT17 | BIT16),
      (UINT32) (BIT23)
      );

    //
    //  SSPE - Super Speed Port Enables
    //  Address Offset: 0x80B8
    //
    MmioOr32 (
      (XhciMmioBase + R_XHCI_MEM_SSPE),
      (UINT32) (BIT30)
      );

    //
    //  HOST_BW_OV_HS_REG - High Speed TT Bandwidth Overhead
    //  Address Offset: 0x80C8
    //
    Data32And    = (UINT32)~(B_XHCI_MEM_HOST_BW_OV_HS_REG_OVHD_HSTTBW);
    Data32Or     = 0;
    if (HcInfo->OnSouth) {
      Data32And &= (UINT32)~(B_XHCI_MEM_HOST_BW_OV_HS_REG_OVHD_HSBW);
      Data32Or  |= (0xA << N_XHCI_MEM_HOST_BW_OV_HS_REG_OVHD_HSBW);
    }
    MmioAndThenOr32 (
      (XhciMmioBase + R_XHCI_MEM_HOST_BW_OV_HS_REG),
      Data32And,
      Data32Or
      );

    //
    //  HOST_CTRL_SCH_REG - Host Control Scheduler
    //  Address Offset: 0x8094
    //
    MmioAndThenOr32 (
      (XhciMmioBase + R_XHCI_MEM_HOST_CTRL_SCH_REG),
      (UINT32)~(BIT21 | BIT14),
      (UINT32) (BIT23 | BIT22 | BIT6)
      );

    //
    //  AUX_CTRL_REG1 - AUX Power Management Control
    //  Address Offset: 0x80E0
    //
    MmioAndThenOr32 (
      (XhciMmioBase + R_XHCI_MEM_AUX_CTRL_REG1),
      (UINT32)~(BIT16 | BIT9),
      (UINT32) (BIT6)
      );

    //
    //  USB2_LINK_MGR_CTRL_REG1 - USB2 Port Link Control 1, 2, 3, 4
    //  Address Offset: 0x80F0
    //
    MmioOr32 (
      (XhciMmioBase + R_XHCI_MEM_USB2_LINK_MGR_CTRL_REG1_DW4),
      (UINT32) (BIT25)
      );
    Data32And = (UINT32)~(BIT20);
    Data32Or  = 0u;
    if (HcInfo->OnSouth) {
      Data32Or |= BIT22;
    }
    MmioAndThenOr32 (
      (XhciMmioBase + R_XHCI_MEM_USB2_LINK_MGR_CTRL_REG1_DW1),
      Data32And,
      Data32Or
      );

    //
    //  HOST_CTRL_BW_CTRL_REG - Host Controller Bandwith Control Register
    //  Address Offset: 0x8100
    //
    if ((HcInfo->IpVersion == V17_0) ||
        (HcInfo->DeviceId == V_XHCI_DID_V1_1_PCH_N_V17_1) ||
        (HcInfo->DeviceId == V_XHCI_DID_PCH_N_V17_1)) {
      MmioOr32 (
        (XhciMmioBase + R_XHCI_MEM_HOST_CTRL_BW_CTRL_REG),
        (UINT32) (BIT20 | BIT21)
        );
    }

    //
    //  HOST_CTRL_TRM_REG2 - Host Controller Transfer Manager Control 2
    //  Address Offset: 0x8110
    //
    MmioAndThenOr32 (
      (XhciMmioBase + R_XHCI_MEM_HOST_CTRL_TRM_REG2),
      (UINT32)~(BIT2),
      (UINT32) (BIT20 | BIT11)
      );

    //
    //  HOST_CTRL_BW_MAX_REG - MAX BW Control Reg 4
    //  Address Offset: 0x8128
    //
    if (HcInfo->OnSouth) {
      MmioAndThenOr32 (
        (XhciMmioBase + R_XHCI_MEM_HOST_CTRL_BW_MAX_REG),
        (UINT32)~(B_XHCI_MEM_HOST_CTRL_BW_MAX_REG_MAX_HS_BW),
        (UINT32) (0x753 << N_XHCI_MEM_HOST_CTRL_BW_MAX_REG_MAX_HS_BW)
        );
    }

    //
    //  AUX_CTRL_REG2 - Aux PM Control Register 2
    //  Address Offset: 0x8154
    //
    Data32Or  = (UINT32) (BIT31);
    Data32And = (UINT32)~(BIT21);
    if ((HcInfo->DeviceId == V_XHCI_DID_CPU_LP_V17_0) && (HcInfo->IsCpuStepA0)) {
      Data32And &= (UINT32)~(BIT13);
    } else {
      Data32Or |= BIT13;
    }
    MmioAndThenOr32 (
      (XhciMmioBase + R_XHCI_MEM_AUX_CTRL_REG2),
      Data32And,
      Data32Or
      );

    if (HcInfo->OnSouth) {
      //
      //  HOST_CTRL_SCH_REG2
      //  Address Offset: 0x8160
      //
      MmioOr32 (
        (XhciMmioBase + R_XHCI_MEM_HOST_CTRL_SCH_REG2),
        (UINT32) (BIT10)
        );
    }

    //
    //  AUXCLKCTL - xHCI Aux Clock Control Register
    //  Address Offset: 0x816C
    //
    Data32Or = (UINT32) (BIT18 | BIT17 | BIT16 | BIT14 | BIT5 | BIT4 | BIT3 | BIT2);
    if (HcInfo->OnSouth) {
      Data32Or |= BIT19;
    }
    MmioAndThenOr32 (
      (XhciMmioBase + R_XHCI_MEM_AUXCLKCTL),
      (UINT32)~(BIT19 | BIT13 | BIT12 | BIT11 | BIT10 | BIT9 | BIT8),
      Data32Or
      );
  }
  if (UsbConfig->UsbClockGatingEnable == 0) {
    MmioAndThenOr32 (
      (XhciMmioBase + R_XHCI_MEM_AUX_CTRL_REG1),
      (UINT32)~(BIT6),
      (UINT32) (BIT16 | BIT9)
      );
    MmioAnd32 (
      (XhciMmioBase + R_XHCI_MEM_AUX_CTRL_REG2),
      (UINT32)~(BIT10)
      );
    MmioAnd32 (
      (XhciMmioBase + R_XHCI_MEM_AUXCLKCTL),
      (UINT32)~(BIT19 | BIT18 | BIT17 | BIT16 | BIT14 | BIT7 | BIT6 | BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0)
      );
  }
  //
  //  HOST_IF_CTRL_REG - Host Controller Interface Control Register
  //  Address Offset: 0x8108
  //
  if (HcInfo->DeviceId == V_XHCI_DID_PCH_SERVER_V18_0) {
    MmioAnd32 (
      (XhciMmioBase + R_XHCI_MEM_HOST_IF_CTRL_REG),
      (UINT32)~(BIT30)
      );
  } else {
    MmioOr32 (
      (XhciMmioBase + R_XHCI_MEM_HOST_IF_CTRL_REG),
      (UINT32) (BIT30)
      );
  }

  //
  //  HOST_IF_PWR_CTRL_REG0 - Power Scheduler Control 0
  //  Address Offset: 0x8140
  //
  Data32 = 0xFF00F03C;

  if ((HcInfo->DeviceId == V_XHCI_DID_PCH_LP_V18_0) ||
      (HcInfo->DeviceId == V_XHCI_DID_PCH_H_V18_1)) {
    if ((PchStepping () == PCH_Z0) || (PchStepping () == PCH_Z1)) {
      Data32 = 0xFF01803C;
    } else if (PchStepping () < PCH_B0) {
      Data32 = 0xFF01803C;
    }
  }

  MmioWrite32 (
    (XhciMmioBase + R_XHCI_MEM_HOST_IF_PWR_CTRL_REG0),
    Data32
    );

  if (HcInfo->DeviceId != V_XHCI_DID_PCH_SERVER_V18_0) {
    //
    //  HOST_IF_PWR_CTRL_REG1 - Power Scheduler Control 1
    //  Address Offset: 0x8144
    //
    Data32Or = BIT8;
    if (HcInfo->OnSouth &&
      (HcInfo->IpVersion >= V17_1) &&
      (HcInfo->IpVersion != V_XHCI_DID_PCH_B_V18_0)) {
      Data32Or |= BIT24;
    }
    MmioOr32 (
      (XhciMmioBase + R_XHCI_MEM_HOST_IF_PWR_CTRL_REG1),
      Data32Or
      );

    //
    //  USBLPM - USB LPM Parameters
    //  Address Offset: 0x8170
    //
    Data32And = (UINT32)~(0x3FF);
    if (HcInfo->IpVersion < V18_0) {
      Data32And &= (UINT32)~(0x70000);
    }
    MmioAnd32 (
      (XhciMmioBase + R_XHCI_MEM_USBLPM),
      Data32And
      );

    //
    //  xHC Latency Tolerance Parameters - LTV Control
    //  Address Offset: 0x8174
    //
    if (HcInfo->IpVersion < V18_0) {
      Data32And = ~0u;
      Data32Or  = (BIT30 | BIT24);
      if (HcInfo->OnSouth) {
        Data32And = (UINT32)~(0xFFF);
        Data32Or |= 0xC0A;
      }
      MmioAndThenOr32 (
        (XhciMmioBase + R_XHCI_MEM_XHCLTVCTL),
        Data32And,
        Data32Or
        );
    } else {
      if (HcInfo->OnSouth) {
        MmioOr32 (
          (XhciMmioBase + R_XHCI_MEM_XHCLTVCTL),
          (UINT32) (BIT25)
          );
      }
    }

    //
    //  xHC Latency Tolerance Control 2 - LTV Control 2
    //  Address Offset: 0x8178
    //
    if ((HcInfo->IpVersion >= V18_0) && HcInfo->OnSouth) {
      MmioOr32 (
        (XhciMmioBase + R_XHCI_MEM_XHCLTVCTL2),
        BIT15
        );
    }

    //
    //  xHC Latency Tolerance Parameters - High Idle Time Control
    //  Address Offset: 0x817C
    //
    MmioWrite32 (
      (XhciMmioBase + R_XHCI_MEM_LTVHIT),
      HcInfo->UsbLtrHigh
      );

    //
    //  xHC Latency Tolerance Parameters - Medium Idle Time Control
    //  Address Offset: 0x8180
    //
    MmioWrite32 (
      (XhciMmioBase + R_XHCI_MEM_LTVMIT),
      HcInfo->UsbLtrMid
      );

    //
    //  xHC Latency Tolerance Parameters - Low Idle Time Control
    //  Address Offset: 0x8184
    //
    MmioWrite32 (
      (XhciMmioBase + R_XHCI_MEM_LTVLIT),
      HcInfo->UsbLtrLow
      );

    //
    //  USB2 U2 LTR Policy
    //  Address Offset: 0x8188
    //
    if ((HcInfo->IpVersion >= V18_0) && (HcInfo->OnSouth)) {
      Data32 = (1 << GetPchUsb2MaxPhysicalPortNum ()) - 1;
      MmioWrite32 (
        (XhciMmioBase + R_XHCI_MEM_CFG_USB2_LTV_U2_NOREQ_REG),
        Data32
        );
    }
  }

  if (HcInfo->IpVersion < V18_0) {
    //
    //  THROTT - XHCI Throttle Control
    //  Address Offset: 0x819C
    //
    MmioAndThenOr32 (
      (XhciMmioBase + R_XHCI_MEM_THROTT),
      (UINT32)~(BIT16 | BIT11 | BIT10 | BIT7 | BIT1),
      (UINT32) (BIT20 | BIT14 | BIT13 | BIT12 | BIT9 | BIT8 | BIT6 | BIT5 | BIT4 | BIT3 | BIT2 | BIT0)
      );

    //
    //  THROTT2 - XHCI Throttle Control2
    //  Address Offset: 0x81B4
    //
    MmioWrite32 (
      (XhciMmioBase + R_XHCI_MEM_THROTT2),
      0x0
      );
  }

  //
  //  D0I2CTRL - D0I2 Control Register
  //  Address Offset: 0x81BC
  //
  Data32Or  = (0x1F << N_XHCI_MEM_D0I2CTRL_MSID0I2PWT);
  Data32And = ~0u;
  if (HcInfo->IpVersion < V18_0) {
    Data32Or |= (UINT32) (BIT31 |
                         (0x4 << N_XHCI_MEM_D0I2CTRL_D0I2_ENTRY_HYSTERESIS_TIMER) |
                         (0x20 << N_XHCI_MEM_D0I2CTRL_MSI_IDLE_THRESHOLD));
    Data32And &= (UINT32)~(B_XHCI_MEM_D0I2CTRL_D0I2_MIN_RESIDENCY |
                           B_XHCI_MEM_D0I2CTRL_MSI_IDLE_THRESHOLD);
  } else {
    Data32And &= (UINT32)~(BIT31);
  }
  if ((HcInfo->DeviceId == V_XHCI_DID_PCH_LP_V17_0) ||
     ((HcInfo->DeviceId == V_XHCI_DID_CPU_LP_V17_0) && HcInfo->IsCpuStepA0)) {
    Data32Or |= BIT3;
  }
  MmioAndThenOr32 (
    (XhciMmioBase + R_XHCI_MEM_D0I2CTRL),
    Data32And,
    Data32Or
    );

  //
  //  D0i2SchAlarmCtrl - D0i2 Scheduler Alarm Control Register
  //  Address Offset: 0x81C0
  //
  MmioAndThenOr32 (
    (XhciMmioBase + R_XHCI_MEM_D0I2SCH_ALARM_CTRL),
    (UINT32)~(B_XHCI_MEM_D0I2SCH_ALARM_CTRL),
    (UINT32) ((0x2D << N_XHCI_MEM_D0I2SCH_ALARM_CTRL_D0I2IT) | 0xF)
    );

  //
  //  USB2PMCTRL - USB2 Power Management Control
  //  Address Offset: 0x81C4
  //
  Data32Or  = (UINT32) (BIT11 | BIT8);
  Data32And = (UINT32)~(BIT10 | BIT9);
  if (HcInfo->DeviceId != V_XHCI_DID_PCH_B_V18_0) {
    Data32Or  |= (BIT3 | BIT1);
    Data32And &= (UINT32)~(BIT2 | BIT0);
  } else {
    Data32And &= (UINT32)~(0xF);
  }
  if ((HcInfo->DeviceId == V_XHCI_DID_PCH_LP_V18_0) ||
      (HcInfo->DeviceId == V_XHCI_DID_PCH_H_V18_1) ||
      (HcInfo->DeviceId == V_XHCI_DID_PCH_SERVER_V18_0)) {
    Data32Or |= BIT13;
  }
  if (UsbConfig->UsbClockGatingEnable == 0) {
    Data32Or |= (UINT32) (BIT12);
  }
  MmioAndThenOr32 (
    (XhciMmioBase + R_XHCI_MEM_USB2PMCTRL),
    Data32And,
    Data32Or
    );

  //
  //  AUX_CTRL_REG3 - Aux PM Control 3 Register
  //  Address Offset: 0x81C8
  //
  Data32Or  = (UINT32) (BIT6);
  Data32And = ~0u;
  if ((HcInfo->DeviceId == V_XHCI_DID_PCH_LP_V18_0) ||
      (HcInfo->DeviceId == V_XHCI_DID_PCH_H_V18_1) ||
      (HcInfo->DeviceId == V_XHCI_DID_PCH_SERVER_V18_0)) {
    Data32And &= (UINT32)~(BIT14);
  }
  MmioAndThenOr32 (
    (XhciMmioBase + R_XHCI_MEM_AUX_CTRL_REG3),
    Data32And,
    Data32Or
    );

  if (HcInfo->IpVersion < V18_0) {
    //
    //  TRBPRFCTRLREG1 - TRB Prefetch Control Register 1
    //  Address Offset: 0x81D0
    //
    MmioAndThenOr32 (
      (XhciMmioBase + R_XHCI_MEM_TRBPRFCTRLREG1),
      (UINT32)~(BIT25),
      (UINT32) (BIT23 | BIT2 | BIT0)
      );
  }

  //
  //  TRBPRFCACHEINVREG - TRB Prefetch Cache Invalidation Register 1
  //  Address Offset: 0x81D8
  //
  Data32Or    = 0;
  if (HcInfo->IpVersion < V18_0) {
    Data32Or |= (0x7F << N_XHCI_MEM_TRBPRFCACHEINVREG_EN_TRB_FLUSH);
  }
  if (HcInfo->OnSouth) {
    Data32Or |= BIT15;
  }
  MmioOr32 (
    (XhciMmioBase + R_XHCI_MEM_TRBPRFCACHEINVREG),
    Data32Or
    );

  //
  //  HOST_CTRL_SUS_LINK_PORT_REG
  //  Address Offset: 0x81F8
  //
  if (HcInfo->IpVersion < V18_0) {
    MmioAndThenOr32 (
      (XhciMmioBase + R_XHCI_MEM_HOST_CTRL_SUS_LINK_PORT_REG),
      (UINT32)~(BIT8 | BIT7),
      (UINT32) (BIT7)
      );
  }
  if ((HcInfo->DeviceId == V_XHCI_DID_PCH_LP_V18_0) ||
      (HcInfo->DeviceId == V_XHCI_DID_PCH_H_V18_1) ||
      (HcInfo->DeviceId == V_XHCI_DID_PCH_SERVER_V18_0)) {
    MmioOr32 (
      (XhciMmioBase + R_XHCI_MEM_HOST_CTRL_SUS_LINK_PORT_REG),
      (UINT32) (BIT17)
      );
  }

  if (HcInfo->OnSouth) {
    //
    // HOST CTRL EARLY DBG REG
    // Address Offset: 0x81FC
    //
    MmioAndThenOr32 (
      (XhciMmioBase + R_XHCI_MEM_HOST_CTRL_EARLY_DBG_REG),
      (UINT32)~(BIT0),
      (UINT32) (BIT1)
      );
  }

  if ((HcInfo->DeviceId == V_XHCI_DID_CPU_SH_V17_1) ||
      (HcInfo->DeviceId == V_XHCI_DID_PCH_H_V17_1)) {
    //
    //  MULT_IN_SCH_POLICY - Multiple IN Scheduler Policy Register
    //  Address Offset: 0x82A0
    //
    MmioOr32 (
      (XhciMmioBase + R_XHCI_MEM_MULT_IN_SCH_POLICY),
      (UINT32) (BIT5 | BIT4)
      );
  }

  if ((HcInfo->DeviceId != V_XHCI_DID_CPU_LP_V17_0) &&
      (HcInfo->DeviceId != V_XHCI_DID_PCH_LP_V17_0) &&
      (HcInfo->DeviceId != V_XHCI_DID_PCH_N_V17_1) &&
      (HcInfo->DeviceId != V_XHCI_DID_V1_1_PCH_N_V17_1)) {
    //
    //  MULT_IN_FAIRNESS_POLICY_1 - Fairness Policy Register 1
    //  Address Offset: 0x82A4
    //
    MmioOr32 (
      (XhciMmioBase + R_XHCI_MEM_MULT_IN_FAIRNESS_POLICY_1),
      (UINT32) (BIT6 | BIT5 | BIT4)
      );
  }

  if (HcInfo->IpVersion >= V18_0) {
    //
    // XHCI_ECN_REG - Misc Reg 3
    // Address Offset: 0x82FC
    //
    MmioOr32 (
      (XhciMmioBase + R_XHCI_MEM_XHCI_ECN_REG),
      (UINT32) (BIT2 | BIT1 | BIT0)
      );
  }

  if (HcInfo->DeviceId != V_XHCI_DID_PCH_SERVER_V18_0) {
    //
    //  PMREQ Control Register
    //  Address Offset: 0x83D0
    //
    Data32Or  = (UINT32) (BIT15);
    Data32And = ~0u;
    if (HcInfo->DeviceId == V_XHCI_DID_PCH_LP_V17_0) {
      Data32Or |= BIT12;
    } else {
      Data32And &= (UINT32)~(BIT12);
    }
    if (HcInfo->IpVersion >= V18_0) {
      Data32Or |= BIT24;
    }
    MmioAndThenOr32 (
      (XhciMmioBase + R_XHCI_MEM_PMREQ_CTRL_REG),
      Data32And,
      Data32Or
      );
  }

  if ((HcInfo->DeviceId == V_XHCI_DID_PCH_LP_V17_0) ||
      (HcInfo->DeviceId == V_XHCI_DID_PCH_N_V17_1) ||
      (HcInfo->DeviceId == V_XHCI_DID_V1_1_PCH_N_V17_1) ||
     ((HcInfo->DeviceId == V_XHCI_DID_CPU_LP_V17_0) && (HcInfo->IsCpuStepA0))) {
    //
    //  Enhanced Clock Gate Control Policy Reguster
    //  Address Offset: 0x83D8
    //
    MmioOr32 (
      (XhciMmioBase + R_XHCI_MEM_ENH_CLK_GATE_CTRL),
      (UINT32) (BIT3 | BIT2)
      );
  }
  if (UsbConfig->UsbClockGatingEnable == 0) {
    MmioOr32 (
      (XhciMmioBase + R_XHCI_MEM_ENH_CLK_GATE_CTRL),
      (UINT32) (BIT6 | BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0)
      );
  }

  //
  //  DBCCTL - DBC Control
  //  Address Offset: 0x8760
  //
  MmioOr32 (
    (XhciMmioBase + R_XHCI_MEM_DBC_DBCCTL),
    (UINT32) ((0x1F << N_XHCI_MEM_DBC_DBCCTL_DISC_RXD_CNT) | BIT0)
    );

  //
  //  HOST_CTRL_SSP_LINK_PORT_REG1
  //  Address Offset: 0x8E5C
  //
  if (UsbConfig->USB3LinkSpeed == 1) {
    MmioOr32 (
      (XhciMmioBase + R_XHCI_MEM_HOST_CTRL_SSP_LINK_PORT_REG1),
      BIT0
      );
  }

  if (HcInfo->IpVersion < V18_0) {
    //
    //  HOST_CTRL_SSP_LINK_REG2
    //  Address Offset: 0x8E68
    //
    Data32Or = (UINT32) (BIT22 | BIT20);
    if (!HcInfo->OnSouth) {
      Data32Or |= BIT21;
    }
    MmioOr32 (
      (XhciMmioBase + R_XHCI_MEM_HOST_CTRL_SSP_LINK_REG2),
      Data32Or
      );

    //
    //  HOST_CTRL_SSP_LFPS_REG2
    //  Address Offset: 0x8E74
    //
    MmioAndThenOr32 (
      XhciMmioBase + R_XHCI_MEM_HOST_CTRL_SSP_LFPS_REG2,
      (UINT32)~(0x7C0000),
      (UINT32) (BIT19 | BIT18)
      );

    //
    //  HOST_CTRL_SSP_LFPS_REG3
    //  Address Offset: 0x8E78
    //
    MmioAndThenOr32 (
      XhciMmioBase + R_XHCI_MEM_HOST_CTRL_SSP_LFPS_REG3,
      (UINT32)~(0x1F),
      (UINT32) (BIT1 | BIT0)
      );
  }

  //
  //  HOST_CTRL_SSP_LFPS_REG4
  //  Address Offset: 0x8E7C
  //
  Data32And = (UINT32)~(B_XHCI_MEM_HOST_CTRL_SSP_LFPS_REG4_SCD_LFPS_TIMEOUT |
                        B_XHCI_MEM_HOST_CTRL_SSP_LFPS_REG4_SCD_TX_COUNT);
  if (((HcInfo->DeviceId == V_XHCI_DID_PCH_B_V18_0) && (PchStepping() < PCH_B0)) ||
       (HcInfo->IpVersion < V18_0)) {
    Data32Or = ((0x4 << N_XHCI_MEM_HOST_CTRL_SSP_LFPS_REG4_SCD_LFPS_TIMEOUT) |
                (0x6 << N_XHCI_MEM_HOST_CTRL_SSP_LFPS_REG4_SCD_TX_COUNT));
  } else {
    Data32Or = ((0x3C << N_XHCI_MEM_HOST_CTRL_SSP_LFPS_REG4_SCD_LFPS_TIMEOUT) |
                (0x2  << N_XHCI_MEM_HOST_CTRL_SSP_LFPS_REG4_SCD_TX_COUNT));
  }
  MmioAndThenOr32 (
    XhciMmioBase + R_XHCI_MEM_HOST_CTRL_SSP_LFPS_REG4,
    Data32And,
    Data32Or
    );

  if (!HcInfo->OnSouth) {
    //
    //  HOST_CTRL_USB3_RECAL
    //  Address Offset: 0x8E84
    //
    MmioAnd32 (
      XhciMmioBase + R_XHCI_MEM_HOST_CTRL_USB3_RECAL,
      (UINT32)~(BIT31)
      );
  }

  //
  //  HOST_CTRL_SSP_CONFIG_REG2
  //  Address Offset: 0x8E9C
  //
  MmioOr32 (
    (XhciMmioBase + R_XHCI_MEM_HOST_CTRL_SSP_CONFIG_REG2),
    (UINT32) (BIT27)
    );

  if (!HcInfo->OnSouth) {
    //
    //  HOST_CTRL_SSP_TUNNELING_REG
    //  Address Offset: 0x8EA0
    //
    MmioOr32 (
      (XhciMmioBase + R_XHCI_MEM_HOST_CTRL_SSP_TUNNELING_REG),
      (UINT32) (BIT5 | BIT3 | BIT0)
      );
  }

  if ((HcInfo->IpVersion >= V18_0) && HcInfo->OnSouth) {
    //
    //  AUDIO_OFFLOAD_CTR
    //  Address Offset: 0x91F4
    //
    if (UsbConfig->UsbClockGatingEnable != 0) {
      MmioOr32 (
        (XhciMmioBase + R_XHCI_MEM_AUDIO_OFFLOAD_CTR),
        (UINT32) (BIT31 | BIT3)
        );
    } else {
      MmioAndThenOr32 (
        (XhciMmioBase + R_XHCI_MEM_AUDIO_OFFLOAD_CTR),
        (UINT32)~(BIT31),
        (UINT32) (BIT3)
        );
    }

    //
    //  U2PRM_U2PRDE
    //  Address Offset: 0x92F4
    //
    if (!IsPortResetMessagingSupported (HcInfo)) {
      MmioWrite32 (
        (XhciMmioBase + R_XHCI_MEM_U2PRM_U2PRDE),
        0x0
        );
    }
  }

  if ((HcInfo->DeviceId == V_XHCI_DID_CPU_UY_V18_0) ||
      (HcInfo->DeviceId == V_XHCI_DID_PCH_B_V18_0)) {
    Data32And = (UINT32)~(
                  B_XHCI_MEM_HOST_CTRL_USB3_CPXX_DEEPMH_CP1_PRECURSOR |
                  B_XHCI_MEM_HOST_CTRL_USB3_CPXX_DEEPMH_C0_VALUE |
                  B_XHCI_MEM_HOST_CTRL_USB3_CPXX_DEEPMH_CM1_PRECURSOR);

    //
    //  HOST_CTRL_USB3_CP13_DEEMPH
    //  Address Offset: 0x8E8C
    //
    Data32Or = (UINT32) (
                  (0x39 << N_XHCI_MEM_HOST_CTRL_USB3_CPXX_DEEPMH_C0_VALUE) |
                  (0x06 << N_XHCI_MEM_HOST_CTRL_USB3_CPXX_DEEPMH_CM1_PRECURSOR));
    MmioAndThenOr32 (
      (XhciMmioBase + R_XHCI_MEM_HOST_CTRL_USB3_CP13_DEEMPH),
      Data32And,
      Data32Or
      );

    //
    //  HOST_CTRL_USB3_CP14_DEEMPH
    //  Address Offset: 0x8E90
    //
    Data32Or = (UINT32) (
                  (0x08 << N_XHCI_MEM_HOST_CTRL_USB3_CPXX_DEEPMH_CP1_PRECURSOR) |
                  (0x37 << N_XHCI_MEM_HOST_CTRL_USB3_CPXX_DEEPMH_C0_VALUE));
    MmioAndThenOr32 (
      (XhciMmioBase + R_XHCI_MEM_HOST_CTRL_USB3_CP14_DEEMPH),
      Data32And,
      Data32Or
      );

    //
    //  HOST_CTRL_USB3_CP15_DEEMPH
    //  Address Offset: 0x8E94
    //
    Data32Or = (UINT32) (
                  (0x08 << N_XHCI_MEM_HOST_CTRL_USB3_CPXX_DEEPMH_CP1_PRECURSOR) |
                  (0x31 << N_XHCI_MEM_HOST_CTRL_USB3_CPXX_DEEPMH_C0_VALUE) |
                  (0x06 << N_XHCI_MEM_HOST_CTRL_USB3_CPXX_DEEPMH_CM1_PRECURSOR));
    MmioAndThenOr32 (
      (XhciMmioBase + R_XHCI_MEM_HOST_CTRL_USB3_CP15_DEEMPH),
      Data32And,
      Data32Or
      );

    //
    //  HOST_CTRL_USB3_CP16_DEEMPH
    //  Address Offset: 0x8E98
    //
    Data32Or = (UINT32) (0x3F << N_XHCI_MEM_HOST_CTRL_USB3_CPXX_DEEPMH_C0_VALUE);
    MmioAndThenOr32 (
      (XhciMmioBase + R_XHCI_MEM_HOST_CTRL_USB3_CP16_DEEMPH),
      Data32And,
      Data32Or
      );
  }

  //
  //  Set 1 to enable Super Speed Ports terminations on enabled ports only (PDO = 0)
  //  Required for Deep S3
  //
  XhciUsb3PortsMask = (UINT32)((1 << SsPortCount) - 1);
  XhciUsb3Pdo = MmioRead32 (XhciMmioBase + R_PCH_XHCI_MEM_USB3PDO) & XhciUsb3PortsMask;
  Data32 = (~XhciUsb3Pdo) & XhciUsb3PortsMask;

  MmioAndThenOr32 (
    XhciMmioBase + R_XHCI_MEM_SSPE,
    (UINT32)~(XhciUsb3PortsMask),
    Data32
    );

  //
  //  SSIC related programming
  //
  MmioOr32 (
    XhciMmioBase + R_XHCI_MEM_SSIC_CONF_REG2_PORT_1,
    (UINT32) (B_XHCI_MEM_SSIC_CONF_REG2_PORT_UNUSED | B_XHCI_MEM_SSIC_CONF_REG2_PROG_DONE)
    );

  MmioOr32 (
    XhciMmioBase + R_XHCI_MEM_SSIC_CONF_REG2_PORT_2,
    (UINT32) (B_XHCI_MEM_SSIC_CONF_REG2_PORT_UNUSED | B_XHCI_MEM_SSIC_CONF_REG2_PROG_DONE)
    );


  if (!HcInfo->OnSouth) {
    //
    // Support use cases where customers will be able to use DBC in Green(Without unlock) state.
    //
    if ((IsHdciDebugEnabled () == TRUE) || (IsCpuDebugDisabled () == FALSE)) {
      MmioOr32 (XhciMmioBase + R_XHCI_MEM_GRP0_SAI_WAC_POLICY_LO, BIT25);
      MmioOr32 (XhciMmioBase + R_XHCI_MEM_GRP0_SAI_RAC_POLICY_LO, BIT25);
    }
  }
}

/**
  Locks xHCI configuration by setting the proper lock bits in controller

  @param[in]  UsbConfig           The USB_CONFIG policy instance
  @param[in]  XhciPciBase         xHCI PCI config space address
**/
VOID
XhciLockConfiguration (
  IN  USB_CONFIG            *UsbConfig,
  IN  UINT64                XhciPciBase
  )
{
  //
  // After xHCI is initialized, BIOS should lock the xHCI configuration registers to RO.
  // This prevent any unintended changes. There is also a lockdown feature for OverCurrent
  // registers. BIOS should set these bits to lock down the settings prior to end of POST.
  // 1. Set Access Control bit at XHCI PCI offset 40h[31] to 1b to lock xHCI register settings.
  // 2. Set OC Configuration Done bit at XHCI PCI offset 44h[31] to lock overcurrent mappings from
  //    further changes.
  //
  if (UsbConfig->XhciOcLock) {
    PciSegmentOr32 (XhciPciBase + R_XHCI_CFG_XHCC2, (UINT32) (B_XHCI_CFG_XHCC2_OCCFDONE));
  }

  //
  // XHCI PCI offset 40h is write once register.
  // Unsupported Request Detected bit is write clear
  //
  PciSegmentAndThenOr32 (
    XhciPciBase + R_XHCI_CFG_XHCC1,
    (UINT32)~(B_XHCI_CFG_XHCC1_URD),
    (UINT32) (B_XHCI_CFG_XHCC1_ACCTRL)
    );
}

/**
  Common entry point for PCH and CPU xHCI controller

  @param[in]  UsbConfig           The USB_CONFIG policy instance
  @param[in]  XhciPciBase         xHCI PCI config space address
**/
VOID
XhciConfigure (
  IN  USB_CONFIG  *UsbConfig,
  IN  UINT64      XhciPciBase
  )
{
  UINT32                Usb2DisabledPorts;
  UINT32                Usb2PortCount;
  UINT32                Usb3DisabledPorts;
  UINT32                Usb3PortCount;
  UINT32                Index;
  USB_CONTROLLER_INFO   HcInfo;
  UINT32                XhciMmioBase;
  EFI_STATUS            Status;

  if (PciSegmentRead16 (XhciPciBase + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    DEBUG ((DEBUG_INFO, "xHCI: PCI device NOT found. XhciPciBase 0x%8X\n", XhciPciBase));
    return;
  }

  DEBUG ((DEBUG_INFO, "XhciConfigure() - Start\n"));

  GetXhciControllerInfo (XhciPciBase, &HcInfo);

  XhciMmioBase = PcdGet32 (PcdSiliconInitTempMemBaseAddr);

  //
  // Assign memory resources
  //
  XhciMemorySpaceOpen (
    XhciPciBase,
    XhciMmioBase
    );

  //
  // Program Xhci Port Disable Override.
  //
  if (HcInfo.OnSouth && UsbConfig->PdoProgramming) {
    DEBUG ((DEBUG_INFO, "xHCI: PEI phase PDO programming\n"));

    Usb2DisabledPorts = 0;
    Usb2PortCount = GetUsb2PortCount (XhciMmioBase);
    for (Index = 0; Index < Usb2PortCount; Index++) {
      if (UsbConfig->PortUsb20[Index].Enable == FALSE) {
        Usb2DisabledPorts |= (BIT0 << Index);
      }
    }
    Usb3DisabledPorts = 0;
    Usb3PortCount = GetUsb3PortCount (XhciMmioBase);
    for (Index = 0; Index < Usb3PortCount; Index++) {
      if (UsbConfig->PortUsb30[Index].Enable == FALSE) {
        Usb3DisabledPorts |= (BIT0 << Index);
      }
    }

    Status = UsbDisablePorts (
               XhciMmioBase,
               Usb2DisabledPorts,
               Usb3DisabledPorts
               );

    //
    // If PDO register is locked, reset platform to unlock it
    //
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "%a - scheduling WarmReset to unlock PDO registers\n", __FUNCTION__));
      SiScheduleResetSetType (EfiResetWarm, NULL);
    }
  }

  //
  // Override LTR values if option is set in Config block
  //
  if (UsbConfig->LtrOverrideEnable) {
    HcInfo.UsbLtrHigh = UsbConfig->LtrHighIdleTimeOverride;
    HcInfo.UsbLtrMid  = UsbConfig->LtrMediumIdleTimeOverride;
    HcInfo.UsbLtrLow  = UsbConfig->LtrLowIdleTimeOverride;
  }

  XhciHcInit (
    &HcInfo,
    XhciPciBase,
    XhciMmioBase,
    UsbConfig
    );

  //
  // Setup USB Over-Current Mapping.
  //
  XhciOverCurrentMapping (
    &HcInfo,
    UsbConfig,
    XhciPciBase,
    XhciMmioBase
    );

  //
  // Clear memory resources
  //
  XhciMemorySpaceClose (XhciPciBase);


  DEBUG ((DEBUG_INFO, "XhciConfigure() - End\n"));
}

/**
  Configure USB OTG

  @param[in]  UsbConfig           The USB_CONFIG policy instance
**/
VOID
UsbConfigureOtg (
  IN  USB_CONFIG      *UsbConfig
  )
{
  UINT32     Data32;
  UINT32     SubscriptionType;
  UINT16     Offset;
  UINT8      PortIndex;
  UINT8      MaxUsbPort2Number;
  UINT8      MaxUsbPort3Number;

  MaxUsbPort2Number = GetPchUsb2MaxPhysicalPortNum ();
  MaxUsbPort3Number = GetPchXhciMaxUsb3PortNum ();

  for (PortIndex = 0; PortIndex < MaxUsbPort2Number; PortIndex++) {
    if (UsbConfig->USB20Otg[PortIndex] == 1) {
      Offset = R_XHCI_PCR_DAP_USB2PORT_CTRL_0 + (PortIndex * S_XHCI_MEM_PORTSC_PORT_SPACING);
      Data32 = PchPcrRead32 (PID_XHCI, Offset);
      SubscriptionType = (Data32 & B_XHCI_PCR_DAP_USB2PORT_CTRL_0_CE) >> N_XHCI_PCR_DAP_USB2PORT_CTRL_0_CE;
      if (SubscriptionType == V_XHCI_PCR_DAP_USB2PORT_CTRL_0_CE_OTG) {
        DEBUG ((DEBUG_INFO, "USB 2.0 Port %d already in OTG mode\n", PortIndex));
      } else {
        DEBUG ((DEBUG_INFO, "USB 2.0 Port %d changes subscription from 0x%x to OTG\n", PortIndex, SubscriptionType));
        Data32 = Data32 & ~B_XHCI_PCR_DAP_USB2PORT_CTRL_0_CE;
        Data32 = Data32 | (V_XHCI_PCR_DAP_USB2PORT_CTRL_0_CE_OTG << N_XHCI_PCR_DAP_USB2PORT_CTRL_0_CE);
        PchPcrWrite32 (PID_XHCI, Offset, Data32);
      }
    }
  }

  for (PortIndex = 0; PortIndex < MaxUsbPort3Number; PortIndex++) {
    if (UsbConfig->USB30Otg[PortIndex] == 1) {
      Offset = R_XHCI_PCR_DAP_USB3PORT_CTRL_0 + (PortIndex * S_XHCI_MEM_PORTSC_PORT_SPACING);
      Data32 = PchPcrRead32 (PID_XHCI, Offset);
      SubscriptionType = (Data32 & B_XHCI_PCR_DAP_USB3PORT_CTRL_0_CE) >> N_XHCI_PCR_DAP_USB3PORT_CTRL_0_CE;
      if (SubscriptionType == V_XHCI_PCR_DAP_USB3PORT_CTRL_0_CE_OTG) {
        DEBUG ((DEBUG_INFO, "USB 3.0 Port %d already in OTG mode\n", PortIndex));
      } else {
        DEBUG ((DEBUG_INFO, "USB 3.0 Port %d changes subscription from 0x%x to OTG\n", PortIndex, SubscriptionType));
        Data32 = Data32 & ~B_XHCI_PCR_DAP_USB3PORT_CTRL_0_CE;
        Data32 = Data32 | (V_XHCI_PCR_DAP_USB3PORT_CTRL_0_CE_OTG << N_XHCI_PCR_DAP_USB3PORT_CTRL_0_CE);
        PchPcrWrite32 (PID_XHCI, Offset, Data32);
      }
    }
  }
}

