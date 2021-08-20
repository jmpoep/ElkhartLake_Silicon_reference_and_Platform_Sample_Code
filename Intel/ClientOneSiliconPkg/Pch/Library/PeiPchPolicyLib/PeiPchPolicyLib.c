/** @file
  This file is PeiPchPolicy library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2020 Intel Corporation.

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
#include "PeiPchPolicyLibrary.h"
#include <Library/PchPcieRpLib.h>
#include <Library/CpuPlatformLib.h>
#include <Register/PchRegsLpcCnl.h>

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadPchGeneralConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  PCH_GENERAL_CONFIG  *PchGeneralConfig;
  PchGeneralConfig = ConfigBlockPointer;

  PchGeneralConfig->PchMasterClockGating = 0;
  PchGeneralConfig->PchMasterPowerGating = 0;
  PchGeneralConfig->SciPinMuxEnable      = 0;

  DEBUG ((DEBUG_INFO, "PchGeneralConfig->Header.GuidHob.Name = %g\n", &PchGeneralConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "PchGeneralConfig->Header.GuidHob.Header.HobLength = 0x%x\n", PchGeneralConfig->Header.GuidHob.Header.HobLength));

  /********************************
    PCH general configuration
  ********************************/
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadPcieRpConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  UINTN            Index;
  PCH_PCIE_CONFIG  *PcieRpConfig;

  PcieRpConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "PcieRpConfig->Header.GuidHob.Name = %g\n", &PcieRpConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "PcieRpConfig->Header.GuidHob.Header.HobLength = 0x%x\n", PcieRpConfig->Header.GuidHob.Header.HobLength));

  /********************************
    PCI Express related settings
  ********************************/
  PcieRpConfig->RpFunctionSwap = TRUE;

  for (Index = 0; Index < GetPchMaxPciePortNum (); Index++) {
    PcieRpConfig->RootPort[Index].Aspm                         = PchPcieAspmAutoConfig;
    PcieRpConfig->RootPort[Index].PmSci                        = TRUE;
    PcieRpConfig->RootPort[Index].AcsEnabled                   = TRUE;
    PcieRpConfig->RootPort[Index].PtmEnabled                   = TRUE;
    PcieRpConfig->RootPort[Index].DpcEnabled                   = TRUE;
    PcieRpConfig->RootPort[Index].RpDpcExtensionsEnabled       = TRUE;
    PcieRpConfig->RootPort[Index].MaxPayload                   = PchPcieMaxPayload256;
    PcieRpConfig->RootPort[Index].SlotImplemented              = TRUE;
    PcieRpConfig->RootPort[Index].PhysicalSlotNumber           = (UINT8) Index;
    PcieRpConfig->RootPort[Index].L1Substates                  = PchPcieL1SubstatesL1_1_2;
    PcieRpConfig->RootPort[Index].PcieRpCommonConfig.EnableCpm = TRUE;
    PcieRpConfig->RootPort[Index].MultiVcEnabled               = TRUE;
    if (IsTglPch () && IsPchLp () && (PchStepping () == PCH_Z0)) {
      PcieRpConfig->RootPort[Index].Aspm                         = PchPcieAspmL1;
      PcieRpConfig->RootPort[Index].L1Substates                  = PchPcieL1SubstatesDisabled;
    }
    //
    // PCIe LTR Configuration.
    //
    PcieRpConfig->RootPort[Index].LtrEnable             = TRUE;
    if (IsPchLp ()) {
      PcieRpConfig->RootPort[Index].PcieRpLtrConfig.LtrMaxSnoopLatency               = 0x1003;
      PcieRpConfig->RootPort[Index].PcieRpLtrConfig.LtrMaxNoSnoopLatency             = 0x1003;
    }
    if (IsPchH ()) {
      PcieRpConfig->RootPort[Index].PcieRpLtrConfig.LtrMaxSnoopLatency               = 0x0846;
      PcieRpConfig->RootPort[Index].PcieRpLtrConfig.LtrMaxNoSnoopLatency             = 0x0846;
    }
    PcieRpConfig->RootPort[Index].PcieRpLtrConfig.SnoopLatencyOverrideMode           = 2;
    PcieRpConfig->RootPort[Index].PcieRpLtrConfig.SnoopLatencyOverrideMultiplier     = 2;
    PcieRpConfig->RootPort[Index].PcieRpLtrConfig.SnoopLatencyOverrideValue          = 60;
    PcieRpConfig->RootPort[Index].PcieRpLtrConfig.NonSnoopLatencyOverrideMode        = 2;
    PcieRpConfig->RootPort[Index].PcieRpLtrConfig.NonSnoopLatencyOverrideMultiplier  = 2;
    PcieRpConfig->RootPort[Index].PcieRpLtrConfig.NonSnoopLatencyOverrideValue       = 60;
  }
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadRstConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  UINTN            Index;
  RST_CONFIG       *RstConfig;

  RstConfig = (RST_CONFIG *)ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "RstConfig->Header.GuidHob.Name = %g\n", &RstConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "RstConfig->Header.GuidHob.Header.HobLength = 0x%x\n", RstConfig->Header.GuidHob.Header.HobLength));

  RstConfig->Raid0              = TRUE;
  RstConfig->Raid1              = TRUE;
  RstConfig->Raid10             = TRUE;
  RstConfig->Raid5              = TRUE;
  RstConfig->Irrt               = TRUE;
  RstConfig->OromUiBanner       = TRUE;
  RstConfig->OromUiDelay        = SataOromDelay2sec;
  RstConfig->HddUnlock          = TRUE;
  RstConfig->LedLocate          = TRUE;
  RstConfig->IrrtOnly           = TRUE;
  RstConfig->SmartStorage       = TRUE;
  RstConfig->OptaneMemory       = TRUE;
  RstConfig->CpuAttachedStorage = TRUE;

  for (Index = 0; Index < PCH_MAX_RST_PCIE_STORAGE_CR; Index++) {
    RstConfig->HardwareRemappedStorageConfig[Index].DeviceResetDelay = 100;
  }
}

/**
  Get Sata Config Policy

  @param[in]  SiPolicy            The RC Policy PPI instance
  @param[in]  SataCtrlIndex       SATA controller index

  @retval     SataConfig          Pointer to Sata Config Policy
**/
SATA_CONFIG *
GetPchSataConfig (
  IN SI_POLICY_PPI      *SiPolicy,
  IN UINT32             SataCtrlIndex
  )
{
  SATA_CONFIG         *SataConfig;
  EFI_STATUS          Status;

  ASSERT (SataCtrlIndex < MaxSataControllerNum ());

  Status = GetConfigBlock ((VOID *) SiPolicy, &gSataConfigGuid, (VOID *) &SataConfig);
  ASSERT_EFI_ERROR (Status);

  SataConfig += SataCtrlIndex;

  return SataConfig;
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadFlashProtectionConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  PCH_FLASH_PROTECTION_CONFIG  *FlashProtectionConfig;
  FlashProtectionConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "FlashProtectionConfig->Header.GuidHob.Name = %g\n", &FlashProtectionConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "FlashProtectionConfig->Header.GuidHob.Header.HobLength = 0x%x\n", FlashProtectionConfig->Header.GuidHob.Header.HobLength));
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadLockDownConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  PCH_LOCK_DOWN_CONFIG  *LockDownConfig;
  LockDownConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "LockDownConfig->Header.GuidHob.Name = %g\n", &LockDownConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "LockDownConfig->Header.GuidHob.Header.HobLength = 0x%x\n", LockDownConfig->Header.GuidHob.Header.HobLength));

  /********************************
    Lockdown configuration
  ********************************/
  LockDownConfig->GlobalSmi       = TRUE;
  LockDownConfig->BiosInterface   = TRUE;
  LockDownConfig->BiosLock        = TRUE;
}

/**
  Load Config block default for FIVR

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadFivrConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  PCH_FIVR_CONFIG  *FivrConfig;
  FivrConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "FivrConfig->Header.GuidHob.Name = %g\n", &FivrConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "FivrConfig->Header.GuidHob.Header.HobLength = 0x%x\n", FivrConfig->Header.GuidHob.Header.HobLength));

  /********************************
    Fivr configuration.
  ********************************/
  FivrConfig->ExtV1p05Rail.EnabledStates = 0x0;
  FivrConfig->ExtV1p05Rail.SupportedVoltageStates = 0x0;
  FivrConfig->ExtV1p05Rail.Voltage = 0x01A4;
  FivrConfig->ExtV1p05Rail.IccMax = 0x64;
  FivrConfig->ExtVnnRail.EnabledStates = 0x0;
  FivrConfig->ExtVnnRail.SupportedVoltageStates = 0x0;
  FivrConfig->ExtVnnRail.Voltage = 0x01A4;
  FivrConfig->ExtVnnRail.IccMax = 0xC8;
  FivrConfig->ExtVnnRailSx.EnabledStates = 0x0;
  FivrConfig->ExtVnnRailSx.Voltage = 0x01A4;
  FivrConfig->ExtVnnRailSx.IccMax = 0xC8;
  FivrConfig->VccinAux.LowToHighCurModeVolTranTime = 0x0;
  FivrConfig->VccinAux.RetToHighCurModeVolTranTime = 0x0;
  FivrConfig->VccinAux.RetToLowCurModeVolTranTime = 0x0;
  FivrConfig->VccinAux.OffToHighCurModeVolTranTime = 0x5A;
  FivrConfig->FivrDynPm = TRUE;
  FivrConfig->ExtV1p05Rail.CtrlRampTmr  = 0x01; // Default after reset value
  FivrConfig->ExtVnnRail.CtrlRampTmr    = 0x01; // Default after reset value
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadHsioConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  PCH_HSIO_CONFIG  *HsioConfig;
  HsioConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "HsioConfig->Header.GuidHob.Name = %g\n", &HsioConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "HsioConfig->Header.GuidHob.Header.HobLength = 0x%x\n", HsioConfig->Header.GuidHob.Header.HobLength));
}

/**
  Load Config block default
  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadFiaConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  PCH_FIA_CONFIG  *FiaConfig;
  FiaConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "FiaConfig->Header.GuidHob.Name = %g\n", &FiaConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "FiaConfig->Header.GuidHob.Header.HobLength = 0x%x\n", FiaConfig->Header.GuidHob.Header.HobLength));

  FiaConfig->LaneReversalEnable = 0x0;
}

GLOBAL_REMOVE_IF_UNREFERENCED COMPONENT_BLOCK_ENTRY  mPchIpBlocks [] = {
  {&gPchGeneralConfigGuid,       sizeof (PCH_GENERAL_CONFIG),           PCH_GENERAL_CONFIG_REVISION,       LoadPchGeneralConfigDefault},
  {&gPchPcieRpConfigGuid,        sizeof (PCH_PCIE_CONFIG),              PCIE_RP_CONFIG_REVISION,           LoadPcieRpConfigDefault},
  {&gFlashProtectionConfigGuid,  sizeof (PCH_FLASH_PROTECTION_CONFIG),  FLASH_PROTECTION_CONFIG_REVISION,  LoadFlashProtectionConfigDefault},
  {&gLockDownConfigGuid,         sizeof (PCH_LOCK_DOWN_CONFIG),         LOCK_DOWN_CONFIG_REVISION,         LoadLockDownConfigDefault},
  {&gHsioConfigGuid,             sizeof (PCH_HSIO_CONFIG),              HSIO_CONFIG_REVISION,              LoadHsioConfigDefault},
  {&gFiaConfigGuid,              sizeof (PCH_FIA_CONFIG),               FIA_CONFIG_REVISION,               LoadFiaConfigDefault}
  ,{&gFivrConfigGuid,            sizeof (PCH_FIVR_CONFIG),              FIVR_CONFIG_REVISION,              LoadFivrConfigDefault}
};

/**
  Get PCH config block table total size.

  @retval                               Size of PCH config block table
**/
UINT16
EFIAPI
PchGetConfigBlockTotalSize (
  VOID
  )
{
  return GetComponentConfigBlockTotalSize (&mPchIpBlocks[0], sizeof (mPchIpBlocks) / sizeof (COMPONENT_BLOCK_ENTRY));
}

/**
  PchAddConfigBlocks add all PCH config blocks.

  @param[in] ConfigBlockTableAddress    The pointer to add PCH config blocks

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
PchAddConfigBlocks (
  IN     VOID      *ConfigBlockTableAddress
  )
{
  DEBUG ((DEBUG_INFO, "PCH AddConfigBlocks\n"));

  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mPchIpBlocks[0], sizeof (mPchIpBlocks) / sizeof (COMPONENT_BLOCK_ENTRY));
}
