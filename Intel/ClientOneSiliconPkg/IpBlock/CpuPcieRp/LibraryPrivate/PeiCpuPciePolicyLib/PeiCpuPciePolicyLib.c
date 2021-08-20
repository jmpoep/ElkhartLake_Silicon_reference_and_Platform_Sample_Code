/** @file
This file provides services for PEI CPU PCIe policy default initialization

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
#include <Library/PeiCpuPciePolicyLib.h>
#include <Library/SiConfigBlockLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PeiServicesLib.h>
#include <Ppi/SiPolicy.h>
#include <SiPolicyStruct.h>
#include <Register/IgdRegs.h>
#include <Library/PchInfoLib.h>

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadPciePeiPreMemDefault (
  IN   VOID          *ConfigBlockPointer
  )
{
  UINT8                  Index;
  PCIE_PEI_PREMEM_CONFIG *PciePeiPreMemConfig;

  PciePeiPreMemConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "PciePeiPreMemConfig->Header.GuidHob.Name = %g\n", &PciePeiPreMemConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "PciePeiPreMemConfig->Header.GuidHob.Header.HobLength = 0x%x\n", PciePeiPreMemConfig->Header.GuidHob.Header.HobLength));
  //
  // Initialize the PciExpress Configuration
  //
  PciePeiPreMemConfig->DmiGen3EqPh2Enable             = 2;
  PciePeiPreMemConfig->DmiGen3ProgramStaticEq         = 1;


  if (IsCnlPch() && IsPchH() && (PchStepping() == PCH_A0)) {
    PciePeiPreMemConfig->DmiMaxLinkSpeed = 1;
  }

  for (Index = 0; Index < SA_DMI_MAX_LANE; Index++) {
    PciePeiPreMemConfig->DmiGen3RootPortPreset[Index] = 4;
    PciePeiPreMemConfig->DmiGen3EndPointPreset[Index] = 7;
    PciePeiPreMemConfig->DmiGen3EndPointHint[Index]   = 2;
  }
  for (Index = 0; Index < SA_DMI_MAX_BUNDLE; Index++) {
    ///
    /// Gen3 RxCTLE peaking default is 0 for DMI
    ///
    PciePeiPreMemConfig->DmiGen3RxCtlePeaking[Index]  = 0;
  }
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadCpuPcieRpPrememDefault (
  IN VOID   *ConfigBlockPointer
  )
{
  CPU_PCIE_RP_PREMEM_CONFIG      *CpuPcieRpPreMemConfig;
  UINT32                         Index;

  CpuPcieRpPreMemConfig = ConfigBlockPointer;
  DEBUG((DEBUG_INFO, "CpuPcieRpPreMemConfig->Header.GuidHob.Name = %g\n", &CpuPcieRpPreMemConfig->Header.GuidHob.Name));
  DEBUG((DEBUG_INFO, "CpuPcieRpPreMemConfig->Header.GuidHob.Header.HobLength = 0x%x\n", CpuPcieRpPreMemConfig->Header.GuidHob.Header.HobLength));

  CpuPcieRpPreMemConfig->RpEnabledMask = 0xF;
  CpuPcieRpPreMemConfig->LinkDownGpios = 0;
  CpuPcieRpPreMemConfig->ClkReqMsgEnable = 1;
  for (Index = 0; Index < GetMaxCpuPciePortNum(); Index++) {
    CpuPcieRpPreMemConfig->PcieSpeed[Index] = 0;
  }
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadCpuPcieRpConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  UINTN                      Index;
  CPU_PCIE_CONFIG            *CpuPcieRpConfig;

  CpuPcieRpConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "CpuPcieRpConfig->Header.GuidHob.Name = %g\n", &CpuPcieRpConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "CpuPcieRpConfig->Header.GuidHob.Header.HobLength = 0x%x\n", CpuPcieRpConfig->Header.GuidHob.Header.HobLength));

  /********************************
    PCI Express related settings
  ********************************/
  CpuPcieRpConfig->PcieCommonConfig.ComplianceTestMode = 0;
  CpuPcieRpConfig->PcieCommonConfig.RpFunctionSwap = FALSE;
  CpuPcieRpConfig->PcieCommonConfig.EnablePeerMemoryWrite = 0;


  CpuPcieRpConfig->PcieCommonConfig.HwEqGen3CoeffList[0].Cm = 0;
  CpuPcieRpConfig->PcieCommonConfig.HwEqGen3CoeffList[0].Cp = 1;
  CpuPcieRpConfig->PcieCommonConfig.HwEqGen3CoeffList[1].Cm = 2;
  CpuPcieRpConfig->PcieCommonConfig.HwEqGen3CoeffList[1].Cp = 3;
  CpuPcieRpConfig->PcieCommonConfig.HwEqGen3CoeffList[2].Cm = 4;
  CpuPcieRpConfig->PcieCommonConfig.HwEqGen3CoeffList[2].Cp = 0;
  CpuPcieRpConfig->PcieCommonConfig.HwEqGen3CoeffList[3].Cm = 0;
  CpuPcieRpConfig->PcieCommonConfig.HwEqGen3CoeffList[3].Cp = 0;
  CpuPcieRpConfig->PcieCommonConfig.HwEqGen3CoeffList[4].Cm = 0;
  CpuPcieRpConfig->PcieCommonConfig.HwEqGen3CoeffList[4].Cp = 0;

  CpuPcieRpConfig->HwEqGen4CoeffList[0].Cm = 0;
  CpuPcieRpConfig->HwEqGen4CoeffList[0].Cp = 7;
  CpuPcieRpConfig->HwEqGen4CoeffList[1].Cm = 8;
  CpuPcieRpConfig->HwEqGen4CoeffList[1].Cp = 9;
  CpuPcieRpConfig->HwEqGen4CoeffList[2].Cm = 0;
  CpuPcieRpConfig->HwEqGen4CoeffList[2].Cp = 0;
  CpuPcieRpConfig->HwEqGen4CoeffList[3].Cm = 0;
  CpuPcieRpConfig->HwEqGen4CoeffList[3].Cp = 0;
  CpuPcieRpConfig->HwEqGen4CoeffList[4].Cm = 0;
  CpuPcieRpConfig->HwEqGen4CoeffList[4].Cp = 0;


  for (Index = 0; Index < GetMaxCpuPciePortNum (); Index++) {
    CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.Aspm                   = CpuPcieAspmAutoConfig;
    CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.PmSci                  = TRUE;
    CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.AcsEnabled             = TRUE;
    CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.PtmEnabled             = TRUE;
    CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.DpcEnabled             = TRUE;
    CpuPcieRpConfig->RootPort[Index].VcEnabled                                 = TRUE;
    CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.RpDpcExtensionsEnabled = TRUE;
    CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.MaxPayload             = CpuPcieMaxPayload256;
    CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.SlotImplemented        = TRUE;
    CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.PhysicalSlotNumber     = (UINT8) Index;
    CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.L1Substates            = CpuPcieL1SubstatesL1_1_2;
    CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.Gen3EqPh3Method        = CpuPcieEqHardware;

    //
    // PCIe LTR Configuration.
    //
    CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.LtrEnable                                              = TRUE;
    CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.PcieRpLtrConfig.LtrMaxSnoopLatency                      = 0x1003;
    CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.PcieRpLtrConfig.LtrMaxNoSnoopLatency                    = 0x1003;
    CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.PcieRpLtrConfig.SnoopLatencyOverrideMode                = 2;
    CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.PcieRpLtrConfig.SnoopLatencyOverrideMultiplier          = 2;
    CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.PcieRpLtrConfig.SnoopLatencyOverrideValue               = 60;
    CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.PcieRpLtrConfig.NonSnoopLatencyOverrideMode             = 2;
    CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.PcieRpLtrConfig.NonSnoopLatencyOverrideMultiplier       = 2;
    CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.PcieRpLtrConfig.NonSnoopLatencyOverrideValue            = 60;
    CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.EnableCpm                                               = TRUE;

    CpuPcieRpConfig->RootPort[Index].VcEnabled                          = 1;
    CpuPcieRpConfig->RootPort[Index].Gen3EqPh3Enable                    = 2;
    CpuPcieRpConfig->RootPort[Index].Gen4EqPh3Enable                    = 2;
    CpuPcieRpConfig->RootPort[Index].Gen3EqPh23Enable                   = 2;
    CpuPcieRpConfig->RootPort[Index].Gen4EqPh23Enable                   = 2;
    CpuPcieRpConfig->RootPort[Index].Gen3Uptp                           = 7;
    CpuPcieRpConfig->RootPort[Index].Gen3Dptp                           = 7;
    CpuPcieRpConfig->RootPort[Index].Gen4Uptp                           = 7;
    CpuPcieRpConfig->RootPort[Index].Gen4Dptp                           = 7;

    CpuPcieRpConfig->EqPh3LaneParam[Index].Cm                           = 6;
    CpuPcieRpConfig->EqPh3LaneParam[Index].Cp                           = 2;
  }

}

static COMPONENT_BLOCK_ENTRY  mCpuPciePeiIpBlocksPreMem = {
  &gCpuPciePeiPreMemConfigGuid, sizeof (PCIE_PEI_PREMEM_CONFIG), CPU_PCIE_PEI_PREMEM_CONFIG_REVISION, LoadPciePeiPreMemDefault
};


static COMPONENT_BLOCK_ENTRY  mCpuPcieIpBlocksPreMem = {
  &gCpuPcieRpPrememConfigGuid,       sizeof (CPU_PCIE_RP_PREMEM_CONFIG),  CPU_PCIE_RP_PREMEM_CONFIG_REVISION,   LoadCpuPcieRpPrememDefault
};

static COMPONENT_BLOCK_ENTRY  mCpuPcieIpBlocks = {
  &gCpuPcieRpConfigGuid,       sizeof (CPU_PCIE_CONFIG),     CPU_PCIE_RP_CONFIG_REVISION,       LoadCpuPcieRpConfigDefault
};

/**
  Get Cpu Pcie PEI config block table total size.

  @retval     Size of Graphics PEI config block table
**/
UINT16
EFIAPI
CpuPcieGetConfigBlockTotalSize (
  VOID
  )
{
  return mCpuPcieIpBlocks.Size;
}

/**
  Get Cpu Pcie Pre-Mem config block table total size.

  @retval      Size of Graphics PEI Pre-Mem config block table
**/
UINT16
EFIAPI
CpuPcieGetConfigBlockTotalSizePreMem (
  VOID
  )
{
  return mCpuPcieIpBlocksPreMem.Size;
}

/**
  Get Cpu Pcie PEI Pre-Mem config block table total size.

  @retval      Size of Graphics PEI Pre-Mem config block table
**/
UINT16
EFIAPI
CpuPciePeiGetConfigBlockTotalSizePreMem (
  VOID
  )
{
  return mCpuPciePeiIpBlocksPreMem.Size;
}

/**
  CpuPcieAddConfigBlocksPreMem add all Cpu Pcie PEI PreMem config block.

  @param[in] ConfigBlockTableAddress    The pointer to add SA config blocks

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
CpuPciePeiAddConfigBlocksPreMem (
  IN VOID           *ConfigBlockTableAddress
  )
{
  EFI_STATUS  Status;
  Status = AddComponentConfigBlocks (ConfigBlockTableAddress, &mCpuPciePeiIpBlocksPreMem, 1);
  return Status;
}

/**
  CpuPcieAddConfigBlocksPreMem add all Cpu Pcie PreMem config block.

  @param[in] ConfigBlockTableAddress    The pointer to add SA config blocks

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
CpuPcieAddConfigBlocksPreMem (
  IN VOID           *ConfigBlockTableAddress
  )
{
  EFI_STATUS  Status;
  Status = AddComponentConfigBlocks (ConfigBlockTableAddress, &mCpuPcieIpBlocksPreMem, 1);
  return Status;
}

/**
  CpuPcieAddConfigBlocks add all Graphics PEI config block.

  @param[in] ConfigBlockTableAddress    The pointer to add SA config blocks

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
CpuPcieAddConfigBlocks (
  IN VOID           *ConfigBlockTableAddress
  )
{
  EFI_STATUS  Status;
  Status = AddComponentConfigBlocks (ConfigBlockTableAddress, &mCpuPcieIpBlocks, 1);
  return Status;
}

/**
  This function prints the PEI phase Cpu Pcie PreMem policy.

  @param[in] SiPolicyPreMemPpi - Instance of SI_PREMEM_POLICY_PPI
**/
VOID
EFIAPI
CpuPciePeiPrintPolicyPpiPreMem (
  IN  SI_PREMEM_POLICY_PPI *SiPolicyPreMemPpi
  )
{
  DEBUG_CODE_BEGIN ();
  EFI_STATUS                            Status;
  PCIE_PEI_PREMEM_CONFIG                *PciePeiPreMemConfig;
  UINT32                                Index;

  //
  // Get requisite IP Config Blocks which needs to be used here
  //
  Status = GetConfigBlock ((VOID *)SiPolicyPreMemPpi, &gCpuPciePeiPreMemConfigGuid, (VOID *)&PciePeiPreMemConfig);
  ASSERT_EFI_ERROR(Status);

  DEBUG ((DEBUG_INFO, "------------------------ PCIE_PEI_PREMEM_CONFIG -----------------\n"));
  DEBUG ((DEBUG_INFO, " Revision : %d\n", PciePeiPreMemConfig->Header.Revision));
  ASSERT (PciePeiPreMemConfig->Header.Revision == CPU_PCIE_PEI_PREMEM_CONFIG_REVISION);
  DEBUG ((DEBUG_INFO, " DmiMaxLinkSpeed : 0x%x\n", PciePeiPreMemConfig->DmiMaxLinkSpeed));
  DEBUG ((DEBUG_INFO, " DmiGen3EqPh2Enable : 0x%x\n", PciePeiPreMemConfig->DmiGen3EqPh2Enable));
  DEBUG ((DEBUG_INFO, " DmiGen3EqPh3Method : 0x%x\n", PciePeiPreMemConfig->DmiGen3EqPh3Method));
  DEBUG ((DEBUG_INFO, " DmiGen3ProgramStaticEq : 0x%x\n", PciePeiPreMemConfig->DmiGen3ProgramStaticEq));
  DEBUG ((DEBUG_INFO, " InitPcieAspmAfterOprom : 0x%x\n", PciePeiPreMemConfig->InitPcieAspmAfterOprom));
  DEBUG ((DEBUG_INFO, " DmiGen3RootPortPreset[%d] :", SA_DMI_MAX_LANE));
  for (Index = 0; Index < SA_DMI_MAX_LANE; Index++) {
    DEBUG ((DEBUG_INFO, " 0x%x", PciePeiPreMemConfig->DmiGen3RootPortPreset[Index]));
  }
  DEBUG ((DEBUG_INFO, "\n DmiGen3EndPointPreset[%d] :", SA_DMI_MAX_LANE));
  for (Index = 0; Index < SA_DMI_MAX_LANE; Index++) {
    DEBUG ((DEBUG_INFO, " 0x%x", PciePeiPreMemConfig->DmiGen3EndPointPreset[Index]));
  }
  DEBUG ((DEBUG_INFO, "\n DmiGen3EndPointHint[%d] :", SA_DMI_MAX_LANE));
  for (Index = 0; Index < SA_DMI_MAX_LANE; Index++) {
    DEBUG ((DEBUG_INFO, " 0x%x", PciePeiPreMemConfig->DmiGen3EndPointHint[Index]));
  }
  DEBUG ((DEBUG_INFO, "\n DmiGen3RxCtlePeaking[%d] :", SA_DMI_MAX_BUNDLE));
  for (Index = 0; Index < SA_DMI_MAX_BUNDLE; Index++) {
    DEBUG ((DEBUG_INFO, " 0x%x", PciePeiPreMemConfig->DmiGen3RxCtlePeaking[Index]));
  }

  DEBUG ((DEBUG_INFO, " DmiDeEmphasis : 0x%x\n", PciePeiPreMemConfig->DmiDeEmphasis));
  DEBUG ((DEBUG_INFO, "\n------------------------ PCIE_PEI_PREMEM_CONFIG Print END -----------------\n"));
  DEBUG_CODE_END ();
  return;
}

/**
  This function prints the Cpu Pcie PreMem policy.

  @param[in] SiPolicyPreMemPpi - Instance of SI_PREMEM_POLICY_PPI
**/
VOID
EFIAPI
CpuPciePrintPolicyPpiPreMem (
  IN  SI_PREMEM_POLICY_PPI *SiPolicyPreMemPpi
  )
{
  DEBUG_CODE_BEGIN ();
  EFI_STATUS                            Status;
  CPU_PCIE_RP_PREMEM_CONFIG             *CpuPcieRpPreMemConfig;
  UINT32                                Index;

  //
  // Get requisite IP Config Blocks which needs to be used here
  //
  Status = GetConfigBlock((VOID *)SiPolicyPreMemPpi, &gCpuPcieRpPrememConfigGuid, (VOID *)&CpuPcieRpPreMemConfig);
  ASSERT_EFI_ERROR (Status);


  DEBUG ((DEBUG_INFO, "\n------------------------ CPU_PCIE_RP_PREMEM_CONFIG -----------------\n"));
  DEBUG ((DEBUG_INFO, " Revision : %d\n", CpuPcieRpPreMemConfig->Header.Revision));
  ASSERT (CpuPcieRpPreMemConfig->Header.Revision == CPU_PCIE_RP_PREMEM_CONFIG_REVISION);
  DEBUG ((DEBUG_INFO, " RpEnabledMask : 0x%x\n", CpuPcieRpPreMemConfig->RpEnabledMask));
  DEBUG ((DEBUG_INFO, " Link Down GPIOs : 0x%x\n", CpuPcieRpPreMemConfig->LinkDownGpios));
  DEBUG ((DEBUG_INFO, " ClockReq Messaging Enable : 0x%x\n", CpuPcieRpPreMemConfig->ClkReqMsgEnable));
  for (Index = 0; Index < GetMaxCpuPciePortNum (); Index++) {
    DEBUG ((DEBUG_INFO, " PcieSpeed : %x\n", CpuPcieRpPreMemConfig->PcieSpeed[Index]));
  }
  DEBUG ((DEBUG_INFO, "\n------------------------ CPU_PCIE_RP_PREMEM_CONFIG Print END -----------------\n"));
  DEBUG_CODE_END ();
  return;
}

/**
  This function prints the Cpu Pcie PEI phase policy.

  @param[in] SiPolicyPpi - Instance of SI_POLICY_PPI
**/
VOID
EFIAPI
CpuPciePrintPolicyPpi (
  IN  SI_POLICY_PPI     *SiPolicyPpi
  )
{
  DEBUG_CODE_BEGIN ();
  EFI_STATUS                            Status;
  CPU_PCIE_CONFIG                       *CpuPcieRpConfig;
  UINT32                                Index;

  //
  // Get requisite IP Config Blocks which needs to be used here
  //
  Status = GetConfigBlock((VOID *)SiPolicyPpi, &gCpuPcieRpConfigGuid, (VOID *)&CpuPcieRpConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG((DEBUG_INFO, "------------------------ CPU_PCIE_Config -----------------\n"));
  ASSERT (CpuPcieRpConfig->Header.Revision == CPU_PCIE_RP_CONFIG_REVISION);
  DEBUG ((DEBUG_INFO, " SetSecuredRegisterLock = %x\n", CpuPcieRpConfig->SetSecuredRegisterLock));
  DEBUG ((DEBUG_INFO, " SkipCpuFiaProgramming = %x\n", CpuPcieRpConfig->SkipCpuFiaProgramming));
  DEBUG ((DEBUG_INFO, " DisableRootPortClockGating= %x\n", CpuPcieRpConfig->DisableRootPortClockGating));
  DEBUG ((DEBUG_INFO, " DisableRootPortPowerGating= %x\n", CpuPcieRpConfig->DisableRootPortPowerGating));
  DEBUG ((DEBUG_INFO, " ComplianceTestMode= %x\n", CpuPcieRpConfig->PcieCommonConfig.ComplianceTestMode));
  DEBUG ((DEBUG_INFO, " RpFunctionSwap= %x\n", CpuPcieRpConfig->PcieCommonConfig.RpFunctionSwap));
  DEBUG ((DEBUG_INFO, " EnablePeerMemoryWrite= %x\n", CpuPcieRpConfig->PcieCommonConfig.EnablePeerMemoryWrite));
  DEBUG ((DEBUG_INFO, " PcieDeviceOverrideTablePtr= %x\n", CpuPcieRpConfig->PcieDeviceOverrideTablePtr));
  for (Index = 0; Index < GetMaxCpuPciePortNum(); Index++) {
    DEBUG ((DEBUG_INFO, " Gen3EqPh3Enable= %x\n", CpuPcieRpConfig->RootPort[Index].Gen3EqPh3Enable));
    DEBUG ((DEBUG_INFO, " Gen4EqPh3Enable= %x\n", CpuPcieRpConfig->RootPort[Index].Gen4EqPh3Enable));
    DEBUG ((DEBUG_INFO, " Gen3EqPh23Enable= %x\n", CpuPcieRpConfig->RootPort[Index].Gen3EqPh23Enable));
    DEBUG ((DEBUG_INFO, " Gen4EqPh23Enable= %x\n", CpuPcieRpConfig->RootPort[Index].Gen4EqPh23Enable));
    DEBUG ((DEBUG_INFO, " RootPort[%d] HotPlug= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.HotPlug));
    DEBUG ((DEBUG_INFO, " RootPort[%d] PmSci= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.PmSci));
    DEBUG ((DEBUG_INFO, " RootPort[%d] ExtSync= %x\n", Index, CpuPcieRpConfig->RootPort[Index].ExtSync));
    DEBUG ((DEBUG_INFO, " RootPort[%d] UnsupportedRequestReport= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.UnsupportedRequestReport));
    DEBUG ((DEBUG_INFO, " RootPort[%d] FatalErrorReport= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.FatalErrorReport));
    DEBUG ((DEBUG_INFO, " RootPort[%d] NoFatalErrorReport= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.NoFatalErrorReport));
    DEBUG ((DEBUG_INFO, " RootPort[%d] CorrectableErrorReport= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.CorrectableErrorReport));
    DEBUG ((DEBUG_INFO, " RootPort[%d] SystemErrorOnFatalError= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.SystemErrorOnFatalError));
    DEBUG ((DEBUG_INFO, " RootPort[%d] SystemErrorOnNonFatalError= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.SystemErrorOnNonFatalError));
    DEBUG ((DEBUG_INFO, " RootPort[%d] SystemErrorOnCorrectableError= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.SystemErrorOnCorrectableError));
    DEBUG ((DEBUG_INFO, " RootPort[%d] MaxPayload= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.MaxPayload));
    DEBUG ((DEBUG_INFO, " RootPort[%d] DpcEnabled= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.DpcEnabled));
    DEBUG ((DEBUG_INFO, " RootPort[%d] RpDpcExtensionsEnabled= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.RpDpcExtensionsEnabled));
    DEBUG ((DEBUG_INFO, " RootPort[%d] SlotImplemented= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.SlotImplemented));
    DEBUG ((DEBUG_INFO, " RootPort[%d] AcsEnabled= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.AcsEnabled));
    DEBUG ((DEBUG_INFO, " RootPort[%d] PtmEnabled= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.PtmEnabled));
    DEBUG ((DEBUG_INFO, " RootPort[%d] VcEnabled= %x\n", Index, CpuPcieRpConfig->RootPort[Index].VcEnabled));
    DEBUG ((DEBUG_INFO, " RootPort[%d] AdvancedErrorReporting= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.AdvancedErrorReporting));
    DEBUG ((DEBUG_INFO, " RootPort[%d] TransmitterHalfSwing= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.TransmitterHalfSwing));
    DEBUG ((DEBUG_INFO, " RootPort[%d] Gen3EqPh3Method= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.Gen3EqPh3Method));
    DEBUG ((DEBUG_INFO, " RootPort[%d] PhysicalSlotNumber= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.PhysicalSlotNumber));
    DEBUG ((DEBUG_INFO, " RootPort[%d] CompletionTimeout= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.CompletionTimeout));
    DEBUG ((DEBUG_INFO, " RootPort[%d] Aspm= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.Aspm));
    DEBUG ((DEBUG_INFO, " RootPort[%d] L1Substates= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.L1Substates));
    DEBUG ((DEBUG_INFO, " RootPort[%d] LtrEnable= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.LtrEnable));
    DEBUG ((DEBUG_INFO, " RootPort[%d] LtrConfigLock= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.PcieRpLtrConfig.LtrConfigLock));
    DEBUG ((DEBUG_INFO, " RootPort[%d] LtrMaxSnoopLatency= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.PcieRpLtrConfig.LtrMaxSnoopLatency));
    DEBUG ((DEBUG_INFO, " RootPort[%d] LtrMaxNoSnoopLatency= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.PcieRpLtrConfig.LtrMaxNoSnoopLatency));
    DEBUG ((DEBUG_INFO, " RootPort[%d] SnoopLatencyOverrideMode= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.PcieRpLtrConfig.SnoopLatencyOverrideMode));
    DEBUG ((DEBUG_INFO, " RootPort[%d] SnoopLatencyOverrideMultiplier= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.PcieRpLtrConfig.SnoopLatencyOverrideMultiplier));
    DEBUG ((DEBUG_INFO, " RootPort[%d] SnoopLatencyOverrideValue= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.PcieRpLtrConfig.SnoopLatencyOverrideValue));
    DEBUG ((DEBUG_INFO, " RootPort[%d] NonSnoopLatencyOverrideMode= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.PcieRpLtrConfig.NonSnoopLatencyOverrideMode));
    DEBUG ((DEBUG_INFO, " RootPort[%d] NonSnoopLatencyOverrideMultiplier= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.PcieRpLtrConfig.NonSnoopLatencyOverrideMultiplier));
    DEBUG ((DEBUG_INFO, " RootPort[%d] NonSnoopLatencyOverrideValue= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.PcieRpLtrConfig.NonSnoopLatencyOverrideValue));
    DEBUG ((DEBUG_INFO, " RootPort[%d] ForceLtrOverride= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.PcieRpLtrConfig.ForceLtrOverride));
    DEBUG ((DEBUG_INFO, " RootPort[%d] DetectTimeoutMs= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.DetectTimeoutMs));
    DEBUG ((DEBUG_INFO, " RootPort[%d] Gen3Uptp= %x\n", Index, CpuPcieRpConfig->RootPort[Index].Gen3Uptp));
    DEBUG ((DEBUG_INFO, " RootPort[%d] Gen3Dptp= %x\n", Index, CpuPcieRpConfig->RootPort[Index].Gen3Dptp));
    DEBUG ((DEBUG_INFO, " RootPort[%d] Gen4Uptp= %x\n", Index, CpuPcieRpConfig->RootPort[Index].Gen4Uptp));
    DEBUG ((DEBUG_INFO, " RootPort[%d] gen4Dptp= %x\n", Index, CpuPcieRpConfig->RootPort[Index].Gen4Dptp));
    DEBUG ((DEBUG_INFO, " RootPort[%d] EnableCpm= %x\n", Index, CpuPcieRpConfig->RootPort[Index].PcieRpCommonConfig.EnableCpm));
  }
  for (Index = 0; Index < PCIE_HWEQ_COEFFS_MAX; Index++) {
    DEBUG ((DEBUG_INFO, " HwEqGen3CoeffListCm= %x\n", CpuPcieRpConfig->PcieCommonConfig.HwEqGen3CoeffList[Index].Cm));
    DEBUG ((DEBUG_INFO, " HwEqGen3CoeffListCp= %x\n", CpuPcieRpConfig->PcieCommonConfig.HwEqGen3CoeffList[Index].Cp));
    DEBUG ((DEBUG_INFO, " HwEqGen4CoeffListCm= %x\n", CpuPcieRpConfig->HwEqGen4CoeffList[0].Cm));
    DEBUG ((DEBUG_INFO, " HwEqGen4CoeffListCp= %x\n", CpuPcieRpConfig->HwEqGen4CoeffList[0].Cp));
  }
  DEBUG ((DEBUG_INFO, "\n------------------------ CPU_PCIE_Config Print END -----------------\n"));

  DEBUG_CODE_END ();
  return;
}
