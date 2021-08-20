/** @file
  The DXE TCSS Init Library Implements After Memory PEIM

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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

#include <Base.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <TcssDataHob.h>
#include <SaPolicyCommon.h>
#include <Library/HobLib.h>
#include <Library/PciSegmentLib.h>
#include <IndustryStandard/Pci22.h>
#include <Protocol/SaNvsArea.h>
#include <Library/PcdLib.h>
#include <Library/UsbLib.h>
#include <Library/PciExpressHelpersLib.h>
#include <Library/BaseMemoryLib.h>
#include <PcieRegs.h>
#include <Register/HostDmaRegs.h>
#include <Register/CpuUsbRegs.h>
#include <Register/ItbtPcieRegs.h>
#include <Register/UsbRegs.h>
#include <Register/SaRegsHostBridge.h>


/**
This function performs Itbt PCI initialization before EndOfDxe.

**/
VOID
TcssIbtPcieConfigPciEnumComplete(
  VOID
  )
{
  UINT8          Index;
  UINT32         TcssDeven;
  UINT32         SaMchBar;
  UINT32         PcieSegMap;
  UINT32         PcieFuncMap;
  UINT8          RootPortFn;
  UINT8          RootPortSeg;
  TCSS_DATA_HOB  *TcssHob;
  LTR_LIMIT      PolicyLtr;

  ///
  /// Update TCSS Device Enable status to TCSS HOB
  ///
  TcssHob = (TCSS_DATA_HOB *)GetFirstGuidHob(&gTcssHobGuid);
  ZeroMem (&PolicyLtr, sizeof (LTR_LIMIT));

  SaMchBar = PciSegmentRead32(PCI_SEGMENT_LIB_ADDRESS(0, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MCHBAR)) & ~B_SA_MCHBAR_MCHBAREN_MASK;
  TcssDeven = MmioRead32(SaMchBar + R_SA_MCHBAR_TCSS_DEVEN_OFFSET);

  DEBUG((DEBUG_ERROR, "TcssIbtPcieConfigPciEnumComplete ()\n"));

  ///
  /// Initiazlize TBT PCI Root Ports
  ///
  PcieFuncMap = PciSegmentRead32(PCI_SEGMENT_LIB_ADDRESS(0, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_PCIEFUNCMAP));
  PcieSegMap = PciSegmentRead32(PCI_SEGMENT_LIB_ADDRESS(0, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_PCIESEGMAP));


  for (Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
    if (TcssDeven & (B_SA_MCHBAR_TCSS_DEVEN_PCIE0_MASK << Index)) {
      RootPortFn = (PcieFuncMap >> (Index * S_SA_PCIEFUNCMAP_PCIE0FUNC_WIDTH)) & B_SA_PCIEFUNCMAP_PCIE0FUNC_MASK;
      RootPortSeg = (PcieSegMap >> (Index * S_SA_PCIESEGMAP_PCIE0SEG_WIDTH)) & B_SA_PCIESEGMAP_PCIE0SEG_MASK;

      DEBUG((DEBUG_ERROR, "TcssRootportDownstreamPmConfiguration %x\n", RootPortFn));

      if (TcssHob != NULL) {
        PolicyLtr.MaxSnoopLatencyScale = TcssHob->PcieItbtLtrData[Index].SnoopLatencyOverrideMultiplier;
        PolicyLtr.MaxSnoopLatencyValue = TcssHob->PcieItbtLtrData[Index].SnoopLatencyOverrideValue;
        PolicyLtr.MaxNoSnoopLatencyScale = TcssHob->PcieItbtLtrData[Index].NonSnoopLatencyOverrideMultiplier;
        PolicyLtr.MaxNoSnoopLatencyValue = TcssHob->PcieItbtLtrData[Index].NonSnoopLatencyOverrideValue;
      }

      TcssRootportDownstreamPmConfiguration(
        RootPortSeg,
        SA_MC_BUS,
        (UINT8)SA_ITBT_PCIE_DEV_NUM,
        (UINT8)RootPortFn,
        PolicyLtr
      );
    }
  }
}

/**
  This function gets registered as a callback to perform TCSS PCIe initialization before EndOfDxe

  @param[in] Event     - A pointer to the Event that triggered the callback.
  @param[in] Context   - A pointer to private data registered with the callback function.
**/
VOID
EFIAPI
TcssPciEnumCompleteCallback (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
{
  EFI_STATUS              Status;
  VOID                    *ProtocolPointer;
  ///
  /// Check if this is first time called by EfiCreateProtocolNotifyEvent() or not,
  /// if it is, we will skip it until real event is triggered
  ///
  Status = gBS->LocateProtocol (&gEfiPciEnumerationCompleteProtocolGuid, NULL, (VOID **) &ProtocolPointer);
  if (EFI_SUCCESS != Status) {
    return;
  }

  gBS->CloseEvent (Event);
  TcssIbtPcieConfigPciEnumComplete();

  return;
}

/**
  Update TCSS NVS AREA tables

**/
VOID
UpdateTcssNVS (
  VOID
  )
{
  UINT64                           XdciPciBase;
  EFI_STATUS                       Status;
  SYSTEM_AGENT_NVS_AREA_PROTOCOL   *SaNvsAreaProtocol;
  TCSS_DATA_HOB                    *TcssHob;
  UINT32                           Index = 0;
  UINT64                           XdciBar;
  UINT16                           PciMemConfig;
  UINT8                            ClearXdciBar = FALSE;
  VOID                             *Registration;

  ///
  /// Update TCSS Device Enable status in Nvs from HOB values
  ///

  TcssHob = (TCSS_DATA_HOB *) GetFirstGuidHob (&gTcssHobGuid);
  if (TcssHob == NULL) {
    ASSERT (FALSE);
    return;
  }

  Status = gBS->LocateProtocol (&gSaNvsAreaProtocolGuid, NULL, (VOID **) &SaNvsAreaProtocol);
  if (Status != EFI_SUCCESS) {
    return;
  }

  DEBUG ((DEBUG_INFO, "[TCSS] Update TCSS GNVS Area.\n"));

  //
  // Initialize default values for TCSS NVS
  //

  //
  // xDCI Int and APIC IRQ setting
  //
  SaNvsAreaProtocol->Area->TcssxDCIInt = TcssHob->TcssData.TcssxDCIInt;
  SaNvsAreaProtocol->Area->TcssxDCIIrq = TcssHob->TcssData.TcssxDCIIrq;

  //
  // xHCI and xDCI
  //
  SaNvsAreaProtocol->Area->ItbtXhciEn = TcssHob->TcssData.ItbtXhciEn;
  SaNvsAreaProtocol->Area->ItbtXdciEn = TcssHob->TcssData.ItbtXdciEn;

  //
  // IOM Ready
  //
  SaNvsAreaProtocol->Area->IomReady = (UINT8) TcssHob->TcssData.IOMReady;

  //
  // IOM VccSt
  //
  SaNvsAreaProtocol->Area->TcssIomVccSt = TcssHob->TcssData.TcssIomVccSt;

  //
  // TCSS RTD3
  //
  SaNvsAreaProtocol->Area->TcssRtd3 = TcssHob->TcssData.TcssRtd3;

  //
  // iTBT PCIE rootports
  //
  for (Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
    SaNvsAreaProtocol->Area->ItbtPcieRpEn[Index] = TcssHob->TcssData.ItbtPcieRpEn[Index];
  }
  //
  // Update ASL iTBT PCIE port address according to root port device and function
  //
  for (Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
    SaNvsAreaProtocol->Area->ItbtPcieRpAddress[Index] = ((UINT8) SA_ITBT_PCIE_DEV_NUM << 16) | (UINT8) ((TcssHob->TcssData.ItbtPcieFuncMap >> (3 * Index)) & 0x7);;
    SaNvsAreaProtocol->Area->LtrEnable[Index] = TcssHob->PcieItbtLtrData[Index].LtrEnable;
    SaNvsAreaProtocol->Area->PcieLtrMaxSnoopLatency[Index] = (UINT16) ((TcssHob->PcieItbtLtrData[Index].SnoopLatencyOverrideMultiplier << 10) | TcssHob->PcieItbtLtrData[Index].SnoopLatencyOverrideValue );
    SaNvsAreaProtocol->Area->PcieLtrMaxNoSnoopLatency[Index] = (UINT16) ((TcssHob->PcieItbtLtrData[Index].NonSnoopLatencyOverrideMultiplier << 10) | TcssHob->PcieItbtLtrData[Index].NonSnoopLatencyOverrideValue );
  }

  //
  // TBT DMA
  //
  for (Index = 0; Index < SA_MAX_HOST_ITBT_DMA_NUMBER; Index++) {
    SaNvsAreaProtocol->Area->ItbtDmaEn[Index] = TcssHob->TcssData.ItbtDmaEn[Index];
  }

  //
  // Saving GCTL value into SA NVS area
  //

  XdciPciBase = PCI_SEGMENT_LIB_ADDRESS (
                  SA_SEG_NUM,
                  SA_XDCI_NORTH_BUS_NUM,
                  SA_XDCI_NORTH_DEV_NUM,
                  SA_XDCI_NORTH_FUNC_NUM,
                  0
                  );

  ///
  /// Create PCI Enumeration Completed callback for CPU PCIe
  ///
  EfiCreateProtocolNotifyEvent (
    &gEfiPciEnumerationCompleteProtocolGuid,
    TPL_CALLBACK,
    TcssPciEnumCompleteCallback,
    NULL,
    &Registration
    );

  //
  // Determine Base address for Base address register (Offset 0x10)
  //
  if (PciSegmentRead32 (XdciPciBase) != 0xFFFFFFFF) {

    XdciBar = PciSegmentRead32 (XdciPciBase + PCI_BASE_ADDRESSREG_OFFSET) & 0xFFFFFFF0;

    if ((PciSegmentRead32 (XdciPciBase + PCI_BASE_ADDRESSREG_OFFSET) & B_PCI_BAR_MEMORY_TYPE_MASK) == B_PCI_BAR_MEMORY_TYPE_64) {
      XdciBar += (UINT64)PciSegmentRead32 (XdciPciBase + (PCI_BASE_ADDRESSREG_OFFSET + 4)) << 32;
    }

    if (XdciBar == 0x0) {
      ClearXdciBar = TRUE;
      PciSegmentWrite32 ((XdciPciBase + PCI_BASE_ADDRESSREG_OFFSET), PcdGet32 (PcdSiliconInitTempMemBaseAddr));
      XdciBar = PciSegmentRead32 (XdciPciBase + PCI_BASE_ADDRESSREG_OFFSET) & 0xFFFFFFF0;
      if ((PciSegmentRead32 (XdciPciBase + PCI_BASE_ADDRESSREG_OFFSET) & B_PCI_BAR_MEMORY_TYPE_MASK) == B_PCI_BAR_MEMORY_TYPE_64) {
        XdciBar += (UINT64)PciSegmentRead32 (XdciPciBase + (PCI_BASE_ADDRESSREG_OFFSET + 4)) << 32;
      }
    }

    //
    // Enable Pci Memconfig to read the correct value for GCTL register
    //
    PciMemConfig = PciSegmentRead16 (XdciPciBase + PCI_COMMAND_OFFSET);
    PciSegmentWrite16(XdciPciBase + PCI_COMMAND_OFFSET, PciMemConfig | (EFI_PCI_COMMAND_BUS_MASTER | EFI_PCI_COMMAND_MEMORY_SPACE));

    SaNvsAreaProtocol->Area->TcssxDCIPwrDnScale = MmioRead32 (XdciBar + R_XDCI_MEM_GCTL);
    DEBUG ((DEBUG_INFO, "TcssxDCIPwrDnScale  0x%x\n", (UINT32)SaNvsAreaProtocol->Area->TcssxDCIPwrDnScale));
    //
    // Disable Pci Memconfig & clear Base address
    //
    PciSegmentWrite16 (XdciPciBase + PCI_COMMAND_OFFSET, PciMemConfig);

    if (ClearXdciBar == TRUE) {
      PciSegmentWrite32 ((XdciPciBase + PCI_BASE_ADDRESSREG_OFFSET), 0x0);
      PciSegmentWrite32 ((XdciPciBase + (PCI_BASE_ADDRESSREG_OFFSET + 4)), 0x0);
    }
  }
}

