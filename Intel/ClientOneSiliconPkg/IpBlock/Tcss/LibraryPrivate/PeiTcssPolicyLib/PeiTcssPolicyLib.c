/** @file
  This file provides services for TCSS policy function

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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
#include <Library/DebugLib.h>
#include <Library/SiConfigBlockLib.h>
#include <Library/ConfigBlockLib.h>
#include <Ppi/SiPolicy.h>
#include <TcssPeiPreMemConfig.h>
#include <TcssPeiConfig.h>
#include <Register/CpuUsbRegs.h>

/**
  Print TCSS_PEI_CONFIG and serial out.

  @param[in] SiPolicyPpi            Pointer to a SI_POLICY_PPI
**/
VOID
TcssPrintConfig (
  IN SI_POLICY_PPI     *SiPolicyPpi
  )
{
  EFI_STATUS             Status;
  TCSS_PEI_CONFIG        *TcssPeiConfig;
  TCSS_PCIE_PORT_POLICY  *SaPeiPciCommonPortConfig;
  UINTN                  Index;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gTcssPeiConfigGuid, (VOID *) &TcssPeiConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------------ TCSS_PEI_CONFIG -----------------\n"));
  DEBUG ((DEBUG_INFO, " Revision : %d\n", TcssPeiConfig->Header.Revision));
  ASSERT (TcssPeiConfig->Header.Revision == TCSS_PEI_CONFIG_REVISION);
  for (Index = 0; Index < MAX_IOM_AUX_BIAS_COUNT; Index++) {
    DEBUG ((DEBUG_INFO, "TcssPeiConfig->IomAuxPortPad[%x].GpioPullN 0x%08x\n", Index, TcssPeiConfig->IomConfig.IomAuxPortPad[Index].GpioPullN));
    DEBUG ((DEBUG_INFO, "TcssPeiConfig->IomAuxPortPad[%x].GpioPullP 0x%08x\n", Index, TcssPeiConfig->IomConfig.IomAuxPortPad[Index].GpioPullP));
  }

  for (Index = 0; Index < TCSS_MAX_USB3_PORTS; Index++) {
    DEBUG ((DEBUG_INFO, "TcssPeiConfig->UsbConfig.PortUsb30[%x].Enable 0x%08x\n", Index, TcssPeiConfig->UsbConfig.PortUsb30[Index].Enable));
  }

  DEBUG ((DEBUG_INFO, "TcssPeiConfig->IomConfig.IomOverrides.AuxOri 0x%04X\n", TcssPeiConfig->IomConfig.IomOverrides.AuxOri));
  DEBUG ((DEBUG_INFO, "TcssPeiConfig->IomConfig.IomOverrides.HslOri 0x%04X\n", TcssPeiConfig->IomConfig.IomOverrides.HslOri));
  DEBUG ((DEBUG_INFO, "TcssPeiConfig->IomConfig.IomInterface.VccSt %d\n", TcssPeiConfig->IomConfig.IomInterface.VccSt));
  DEBUG ((DEBUG_INFO, "TcssPeiConfig->IomConfig.IomInterface.UsbOverride %d\n", TcssPeiConfig->IomConfig.IomInterface.UsbOverride));
  DEBUG ((DEBUG_INFO, "TcssPeiConfig->IomConfig.IomInterface.D3HotEnable %d\n", TcssPeiConfig->IomConfig.IomInterface.D3HotEnable));
  DEBUG ((DEBUG_INFO, "TcssPeiConfig->IomConfig.IomInterface.D3ColdEnable %d\n", TcssPeiConfig->IomConfig.IomInterface.D3ColdEnable));

  DEBUG ((DEBUG_INFO, "TcssPeiConfig->IomConfig.PmcInterface.PmcPdEnable %d\n", TcssPeiConfig->IomConfig.PmcInterface.PmcPdEnable));

  DEBUG((DEBUG_INFO, "------------------------ SA_PEI_PCIE_COMMON_CONFIG -----------------\n"));

  for (Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
    SaPeiPciCommonPortConfig = &(TcssPeiConfig->PciePolicy.PciePortPolicy[Index]);
    DEBUG((DEBUG_INFO, " Itbt Root Port %x Config :\n", Index));
    DEBUG((DEBUG_INFO, " AcsEnabled : %d\n", SaPeiPciCommonPortConfig->AcsEnabled));
    DEBUG((DEBUG_INFO, " DpcEnabled : %d\n", SaPeiPciCommonPortConfig->DpcEnabled));
    DEBUG((DEBUG_INFO, " LtrEnable : %d\n", SaPeiPciCommonPortConfig->LtrEnable));
    DEBUG((DEBUG_INFO, " ItbtPcieRootPortPTM : %d\n", SaPeiPciCommonPortConfig->PtmEnabled));
    DEBUG((DEBUG_INFO, " Aspm : %d\n", SaPeiPciCommonPortConfig->Aspm));
    DEBUG((DEBUG_INFO, " SlotNumber : %d\n", SaPeiPciCommonPortConfig->SlotNumber));
    DEBUG((DEBUG_INFO, " SlotPowerLimitScale : %d\n", SaPeiPciCommonPortConfig->SlotPowerLimitScale));
    DEBUG((DEBUG_INFO, " SlotPowerLimitValue : %d\n", SaPeiPciCommonPortConfig->SlotPowerLimitValue));
    DEBUG((DEBUG_INFO, " AdvancedErrorReporting : %d\n", SaPeiPciCommonPortConfig->AdvancedErrorReporting));
    DEBUG((DEBUG_INFO, " UnsupportedRequestReport : %d\n", SaPeiPciCommonPortConfig->UnsupportedRequestReport));
    DEBUG((DEBUG_INFO, " FatalErrorReport : %d\n", SaPeiPciCommonPortConfig->FatalErrorReport));
    DEBUG((DEBUG_INFO, " NoFatalErrorReport : %d\n", SaPeiPciCommonPortConfig->NoFatalErrorReport));
    DEBUG((DEBUG_INFO, " SystemErrorOnFatalError : %d\n", SaPeiPciCommonPortConfig->SystemErrorOnFatalError));
    DEBUG((DEBUG_INFO, " SystemErrorOnNonFatalError : %d\n", SaPeiPciCommonPortConfig->SystemErrorOnNonFatalError));
    DEBUG((DEBUG_INFO, " SystemErrorOnCorrectableError : %d\n", SaPeiPciCommonPortConfig->SystemErrorOnCorrectableError));

    DEBUG((DEBUG_INFO, " LtrMaxSnoopLatency   : %d\n", SaPeiPciCommonPortConfig->LtrMaxSnoopLatency));
    DEBUG((DEBUG_INFO, " LtrMaxNoSnoopLatency : %d\n", SaPeiPciCommonPortConfig->LtrMaxNoSnoopLatency));
    DEBUG((DEBUG_INFO, " SnoopLatencyOverrideMode          : %d\n", SaPeiPciCommonPortConfig->SnoopLatencyOverrideMode));
    DEBUG((DEBUG_INFO, " SnoopLatencyOverrideMultiplier    : %d\n", SaPeiPciCommonPortConfig->SnoopLatencyOverrideMultiplier));
    DEBUG((DEBUG_INFO, " SnoopLatencyOverrideValue         : %d\n", SaPeiPciCommonPortConfig->SnoopLatencyOverrideValue));
    DEBUG((DEBUG_INFO, " NonSnoopLatencyOverrideMode       : %d\n", SaPeiPciCommonPortConfig->NonSnoopLatencyOverrideMode));
    DEBUG((DEBUG_INFO, " NonSnoopLatencyOverrideMultiplier : %d\n", SaPeiPciCommonPortConfig->NonSnoopLatencyOverrideMultiplier));
    DEBUG((DEBUG_INFO, " NonSnoopLatencyOverrideValue      : %d\n", SaPeiPciCommonPortConfig->NonSnoopLatencyOverrideValue));
    DEBUG((DEBUG_INFO, " ForceLtrOverride : %d\n", SaPeiPciCommonPortConfig->ForceLtrOverride));
    DEBUG((DEBUG_INFO, " LtrConfigLock    : %d\n", SaPeiPciCommonPortConfig->LtrConfigLock));
  }

}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadTcssIomConfigDefault (
IN TCSS_IOM_PEI_CONFIG     *IomConfig
  )
{
  IomConfig->IomInterface.D3ColdEnable = 1;
  IomConfig->IomInterface.D3HotEnable = 1;
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadTcssPmcpdDefault (
  IN TCSS_IOM_PEI_CONFIG     *IomConfig
  )
{
  IomConfig->PmcInterface.PmcPdEnable = 1;
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadPeiPcieCommonConfigDefault(
  IN TCSS_PCIE_PORT_POLICY *SaPeiPciCommonConfig
  )
{
  SaPeiPciCommonConfig->AcsEnabled = 1;
  SaPeiPciCommonConfig->DpcEnabled = 1;
  SaPeiPciCommonConfig->RpDpcExtensionsEnabled = 1;
  SaPeiPciCommonConfig->LtrEnable = 0;
  SaPeiPciCommonConfig->PtmEnabled = 0;
  SaPeiPciCommonConfig->Aspm = 1;
  SaPeiPciCommonConfig->SlotNumber = 0x0;
  SaPeiPciCommonConfig->SlotPowerLimitScale = 0;
  SaPeiPciCommonConfig->SlotPowerLimitValue = 0;
  SaPeiPciCommonConfig->AdvancedErrorReporting = 0;
  SaPeiPciCommonConfig->UnsupportedRequestReport = 0;
  SaPeiPciCommonConfig->FatalErrorReport = 0;
  SaPeiPciCommonConfig->NoFatalErrorReport = 0;
  SaPeiPciCommonConfig->CorrectableErrorReport = 0;

  SaPeiPciCommonConfig->SystemErrorOnFatalError = 0;
  SaPeiPciCommonConfig->SystemErrorOnNonFatalError = 0;
  SaPeiPciCommonConfig->SystemErrorOnCorrectableError = 0;

  ///
  /// LTR Settings Defaults
  ///
  SaPeiPciCommonConfig->LtrMaxSnoopLatency = 0;
  SaPeiPciCommonConfig->LtrMaxNoSnoopLatency = 0;
  SaPeiPciCommonConfig->SnoopLatencyOverrideMode = 1;
  SaPeiPciCommonConfig->SnoopLatencyOverrideMultiplier = 2;
  SaPeiPciCommonConfig->SnoopLatencyOverrideValue = 200;        /// Default is 200us
  SaPeiPciCommonConfig->NonSnoopLatencyOverrideMode = 1;
  SaPeiPciCommonConfig->NonSnoopLatencyOverrideMultiplier = 2;
  SaPeiPciCommonConfig->NonSnoopLatencyOverrideValue = 200;     /// Default is 200us
  SaPeiPciCommonConfig->ForceLtrOverride = 0;
  SaPeiPciCommonConfig->LtrConfigLock = 0;
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadSaUsbConfigDefault (
  IN USB_CONFIG       *UsbConfig
  )
{
  UINTN           PortIndex;

  /********************************
    USB related configuration
  ********************************/
  for (PortIndex = 0; PortIndex < MAX_TCSS_USB3_PORTS; PortIndex++) {
    UsbConfig->PortUsb30[PortIndex].Enable = FALSE;
  }

  //
  // BIOS should program PDO in PEI phase by default
  //
  UsbConfig->PdoProgramming = TRUE;

  UsbConfig->XhciOcLock = TRUE;

  //
  // xDCI configuration
  //
  UsbConfig->XdciConfig.Enable = FALSE;
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadTcssMiscConfigDefault (
  IN TCSS_MISC_PEI_CONFIG     *MiscConfig
  )
{
  //
  //   Refer to InterruptConfig.h and PeiPchPolicyLibIcl.c
  //   In APIC relationship between PIRQs and IRQs is:
  //   INTA:1, INTB:2, INTC:3, INTD:4, NO INT: 0xFF
  //   PIRQA -> IRQ16
  //   PIRQB -> IRQ17
  //   PIRQC -> IRQ18
  //   PIRQD -> IRQ19
  //   PIRQE -> IRQ20
  //   PIRQF -> IRQ21
  //   PIRQG -> IRQ22
  //   PIRQH -> IRQ23
  //
  MiscConfig->SaXdci.IntPing = 1;
  MiscConfig->SaXdci.Irq = 16;
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
TcssLoadConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  TCSS_PEI_CONFIG   *TcssConfig;
  UINTN Index;

  TcssConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "TcssConfig->Header.GuidHob.Name = %g\n", &TcssConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "TcssConfig->Header.GuidHob.Header.HobLength = 0x%x\n", TcssConfig->Header.GuidHob.Header.HobLength));

  LoadTcssPmcpdDefault(&(TcssConfig->IomConfig));

  for (Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
    LoadPeiPcieCommonConfigDefault(&(TcssConfig->PciePolicy.PciePortPolicy[Index]));
  }

  LoadSaUsbConfigDefault(&(TcssConfig->UsbConfig));
  LoadTcssMiscConfigDefault(&(TcssConfig->MiscConfig));
}

STATIC COMPONENT_BLOCK_ENTRY  mTcssBlocks = {
  &gTcssPeiConfigGuid,
  sizeof (TCSS_PEI_CONFIG),
  TCSS_PEI_CONFIG_REVISION,
  TcssLoadConfigDefault
};

/**
  Get TCSS config block table size.

  @retval      Size of config block
**/
UINT16
TcssGetConfigBlockTotalSize (
  VOID
  )
{
  return mTcssBlocks.Size;
}

/**
  Add TCSS ConfigBlock.

  @param[in] ConfigBlockTableAddress    The pointer to config block table

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
TcssAddConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  )
{
  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mTcssBlocks, 1);
}
