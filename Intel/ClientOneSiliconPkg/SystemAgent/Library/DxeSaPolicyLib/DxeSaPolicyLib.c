/** @file
  This file provide services for DXE phase policy default initialization

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

#include "DxeSaPolicyLibrary.h"
#include <Library/DxeGraphicsPolicyLib.h>
#include <Library/CpuPcieLib.h>


GLOBAL_REMOVE_IF_UNREFERENCED PCIE_ASPM_OVERRIDE_LIST mPcieAspmDevsOverride[] = {
  {0x8086, 0x108b, 0xff, 2, 2},           ///< Tekoa w/o iAMT
  {0x8086, 0x108c, 0x00, 0, 0},           ///< Tekoa A2
  {0x8086, 0x108c, 0xff, 2, 2},           ///< Tekoa others
  {0x8086, 0x109a, 0xff, 2, 2},           ///< Vidalia
  {0x8086, 0x4222, 0xff, 2, 3},           ///< 3945ABG
  {0x8086, 0x4227, 0xff, 2, 3},           ///< 3945ABG
  {0x8086, 0x4228, 0xff, 2, 3},           ///< 3945ABG
  ///
  /// Place structures for known bad OEM/IHV devices here
  ///
  {CPU_PCIE_DEV_END_OF_TABLE, 0, 0, 0, 0}  ///< End of table
};

GLOBAL_REMOVE_IF_UNREFERENCED PCIE_LTR_DEV_INFO mPcieLtrDevsOverride[] = {
  ///
  /// Place holder for PCIe devices with correct LTR requirements
  ///
  {CPU_PCIE_DEV_END_OF_TABLE, 0, 0, 0, 0}  ///< End of table
};
extern EFI_GUID gMemoryDxeConfigGuid;
extern EFI_GUID gMiscDxeConfigGuid;
extern EFI_GUID gPcieDxeConfigGuid;
extern EFI_GUID gVbiosDxeConfigGuid;

/**
  This function prints the SA DXE phase policy.

  @param[in] SaPolicy - SA DXE Policy protocol
**/
VOID
SaPrintPolicyProtocol (
  IN  SA_POLICY_PROTOCOL      *SaPolicy
  )
{
  EFI_STATUS                  Status;
  PCIE_DXE_CONFIG             *PcieDxeConfig;
  MISC_DXE_CONFIG             *MiscDxeConfig;
  MEMORY_DXE_CONFIG           *MemoryDxeConfig;
  VBIOS_DXE_CONFIG            *VbiosDxeConfig;

  //
  // Get requisite IP Config Blocks which needs to be used here
  //

  Status = GetConfigBlock ((VOID *) SaPolicy, &gMiscDxeConfigGuid, (VOID *)&MiscDxeConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SaPolicy, &gPcieDxeConfigGuid, (VOID *)&PcieDxeConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SaPolicy, &gMemoryDxeConfigGuid, (VOID *)&MemoryDxeConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SaPolicy, &gVbiosDxeConfigGuid, (VOID *)&VbiosDxeConfig);
  ASSERT_EFI_ERROR (Status);


  DEBUG_CODE_BEGIN ();
  INTN  i;

  DEBUG ((DEBUG_INFO, "\n------------------------ SA Policy (DXE) print BEGIN -----------------\n"));
  DEBUG ((DEBUG_INFO, "Revision : %x\n", SaPolicy->TableHeader.Header.Revision));
  ASSERT (SaPolicy->TableHeader.Header.Revision == SA_POLICY_PROTOCOL_REVISION);

  DEBUG ((DEBUG_INFO, "------------------------ SA_MEMORY_CONFIGURATION -----------------\n"));
  //@todo: Matching the hardcode at lines 384.  Need to be addressed.
  DEBUG ((DEBUG_INFO, " SpdAddressTable[%d] :", 4));
  for (i = 0; i < 4; i++) {
    DEBUG ((DEBUG_INFO, " %x", MemoryDxeConfig->SpdAddressTable[i]));
  }
  DEBUG ((DEBUG_INFO, "\n"));

  DEBUG ((DEBUG_INFO, " ChannelASlotMap : %x\n", MemoryDxeConfig->ChannelASlotMap));
  DEBUG ((DEBUG_INFO, " ChannelBSlotMap : %x\n", MemoryDxeConfig->ChannelBSlotMap));
  DEBUG ((DEBUG_INFO, " MrcTimeMeasure  : %x\n", MemoryDxeConfig->MrcTimeMeasure));
  DEBUG ((DEBUG_INFO, " MrcFastBoot     : %x\n", MemoryDxeConfig->MrcFastBoot));

  DEBUG ((DEBUG_INFO, "------------------------ CPU_PCIE_CONFIGURATION -----------------\n"));
  DEBUG ((DEBUG_INFO, " PegAspm[%d] :", SA_PEG_MAX_FUN));
  for (i = 0; i < SA_PEG_MAX_FUN; i++) {
    DEBUG ((DEBUG_INFO, " %x", PcieDxeConfig->PegAspm[i]));
  }
  DEBUG ((DEBUG_INFO, "\n"));

  DEBUG ((DEBUG_INFO, " PegAspmL0s[%d] :", SA_PEG_MAX_FUN));
  for (i = 0; i < SA_PEG_MAX_FUN; i++) {
    DEBUG ((DEBUG_INFO, " %x", PcieDxeConfig->PegAspmL0s[i]));
  }
  DEBUG ((DEBUG_INFO, "\n"));

  DEBUG ((DEBUG_INFO, " PegRootPortHPE[%d] :", SA_PEG_MAX_FUN));
  for (i = 0; i < SA_PEG_MAX_FUN; i++) {
    DEBUG ((DEBUG_INFO, " %x", PcieDxeConfig->PegRootPortHPE[i]));
  }
  DEBUG ((DEBUG_INFO, "\n"));

  if (PcieDxeConfig->PcieAspmDevsOverride != NULL) {
    DEBUG ((DEBUG_INFO, "------------------------ PCIE_ASPM_OVERRIDE_LIST -----------------\n"));
    DEBUG ((DEBUG_INFO, " VendorId DeviceId RevId RootApmcMask EndpointApmcMask\n"));
    i = 0;
    while ((PcieDxeConfig->PcieAspmDevsOverride[i].VendorId != CPU_PCIE_DEV_END_OF_TABLE) &&
           (i < MAX_PCIE_ASPM_OVERRIDE)) {
      DEBUG ((DEBUG_INFO, " %04x     %04x     %02x    %01x            %01x\n",
              PcieDxeConfig->PcieAspmDevsOverride[i].VendorId,
              PcieDxeConfig->PcieAspmDevsOverride[i].DeviceId,
              PcieDxeConfig->PcieAspmDevsOverride[i].RevId,
              PcieDxeConfig->PcieAspmDevsOverride[i].RootApmcMask,
              PcieDxeConfig->PcieAspmDevsOverride[i].EndpointApmcMask));
      i++;
    }
    DEBUG ((DEBUG_INFO, "------------------------ END_OF_TABLE -----------------------\n"));
  }
  if (PcieDxeConfig->PcieLtrDevsOverride != NULL) {
    DEBUG ((DEBUG_INFO, "------------------------ PCIE_LTR_DEV_INFO -----------------\n"));
    DEBUG ((DEBUG_INFO, " VendorId DeviceId RevId SnoopLatency NonSnoopLatency\n"));
    i = 0;
    while ((PcieDxeConfig->PcieLtrDevsOverride[i].VendorId != CPU_PCIE_DEV_END_OF_TABLE) &&
           (i < MAX_PCIE_LTR_OVERRIDE)) {
      DEBUG ((DEBUG_INFO, " %04x     %04x     %02x    %01x            %01x\n",
              PcieDxeConfig->PcieLtrDevsOverride[i].VendorId,
              PcieDxeConfig->PcieLtrDevsOverride[i].DeviceId,
              PcieDxeConfig->PcieLtrDevsOverride[i].RevId,
              PcieDxeConfig->PcieLtrDevsOverride[i].SnoopLatency,
              PcieDxeConfig->PcieLtrDevsOverride[i].NonSnoopLatency));
      i++;
    }
    DEBUG ((DEBUG_INFO, "------------------------ END_OF_TABLE ----------------------\n"));
  }

  for (i = 0; i < SA_PEG_MAX_FUN; i++) {
    DEBUG ((DEBUG_INFO, " PegPwrOpt[%d].LtrEnable            : %x\n", i, PcieDxeConfig->PegPwrOpt[i].LtrEnable));
    DEBUG ((DEBUG_INFO, " PegPwrOpt[%d].LtrMaxSnoopLatency   : %x\n", i, PcieDxeConfig->PegPwrOpt[i].LtrMaxSnoopLatency));
    DEBUG ((DEBUG_INFO, " PegPwrOpt[%d].ObffEnable           : %x\n", i, PcieDxeConfig->PegPwrOpt[i].ObffEnable));
    DEBUG ((DEBUG_INFO, " PegPwrOpt[%d].LtrMaxNoSnoopLatency : %x\n", i, PcieDxeConfig->PegPwrOpt[i].LtrMaxNoSnoopLatency));
  }


  if (VbiosDxeConfig != NULL) {
    DEBUG ((DEBUG_INFO, "------------------------ SA_SG_VBIOS_CONFIGURATION -----------------\n"));
    DEBUG ((DEBUG_INFO, " LoadVbios    : %x\n", VbiosDxeConfig->LoadVbios));
    DEBUG ((DEBUG_INFO, " ExecuteVbios : %x\n", VbiosDxeConfig->ExecuteVbios));
    DEBUG ((DEBUG_INFO, " VbiosSource  : %x\n", VbiosDxeConfig->VbiosSource));
  }


  DEBUG ((DEBUG_INFO, "------------------------ SA_MISC_CONFIGURATION -----------------\n"));
  DEBUG ((DEBUG_INFO, "\n------------------------ SA Policy (DXE) print END -----------------\n"));
  DEBUG_CODE_END ();

  return;
}

/**
  Load DXE Config block default for PCIe

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadPcieDxeDefault (
  IN VOID    *ConfigBlockPointer
  )
{
  UINT8                  pegFn;
  UINT8                  Index;
  PCIE_DXE_CONFIG        *PcieDxeConfig;

  PcieDxeConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "PcieDxeConfig->Header.GuidHob.Name = %g\n", &PcieDxeConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "PcieDxeConfig->Header.GuidHob.Header.HobLength = 0x%x\n", PcieDxeConfig->Header.GuidHob.Header.HobLength));
  ///
  /// Initialize the PCIE Configuration
  /// PEG ASPM per port configuration. 4 PEG controllers i.e. 0,1,2,3
  ///
  for (pegFn = 0; pegFn < SA_PEG_MAX_FUN; pegFn++) {
    PcieDxeConfig->PegAspm[pegFn]       = PcieAspmAutoConfig;
    PcieDxeConfig->PegAspmL0s[pegFn]    = 0;
  }

  for (Index = 0; Index < SA_PEG_MAX_FUN; Index++) {
    PcieDxeConfig->PegPwrOpt[Index].LtrEnable            = 1;
    PcieDxeConfig->PegPwrOpt[Index].LtrMaxSnoopLatency   = V_SA_LTR_MAX_SNOOP_LATENCY_VALUE;
    PcieDxeConfig->PegPwrOpt[Index].LtrMaxNoSnoopLatency = V_SA_LTR_MAX_NON_SNOOP_LATENCY_VALUE;
    PcieDxeConfig->PegPwrOpt[Index].ObffEnable           = 1;
  }

  PcieDxeConfig->PcieAspmDevsOverride = mPcieAspmDevsOverride;
  PcieDxeConfig->PcieLtrDevsOverride = mPcieLtrDevsOverride;
}

/**
  Load DXE Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadMiscDxeDefault (
  IN VOID    *ConfigBlockPointer
  )
{
  MISC_DXE_CONFIG        *MiscDxeConfig;

  MiscDxeConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "MiscDxeConfig->Header.GuidHob.Name = %g\n", &MiscDxeConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "MiscDxeConfig->Header.GuidHob.Header.HobLength = 0x%x\n", MiscDxeConfig->Header.GuidHob.Header.HobLength));
  ///
  /// RMRR Base and Limit Address for USB
  ///
  MiscDxeConfig->RmrrUsbBaseAddress = AllocateZeroPool (sizeof (EFI_PHYSICAL_ADDRESS) * 2);
  ASSERT (MiscDxeConfig->RmrrUsbBaseAddress != NULL);
  if (MiscDxeConfig->RmrrUsbBaseAddress != NULL) {
    ///
    /// BIOS must update USB RMRR base address
    ///
    MiscDxeConfig->RmrrUsbBaseAddress[0] = 0x3E2E0000;
    MiscDxeConfig->RmrrUsbBaseAddress[1] = 0x3E2FFFFF;
  }
}

/**
  Load DXE Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadMemoryDxeDefault (
  IN VOID    *ConfigBlockPointer
  )
{
  MEMORY_DXE_CONFIG        *MemoryDxeConfig;

  MemoryDxeConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "MemoryDxeConfig->Header.GuidHob.Name = %g\n", &MemoryDxeConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "MemoryDxeConfig->Header.GuidHob.Header.HobLength = 0x%x\n", MemoryDxeConfig->Header.GuidHob.Header.HobLength));
  ///
  /// Initialize the Memory Configuration
  ///
  ///
  /// DIMM SMBus addresses info
  /// Refer to the SpdAddressTable[] mapping rule in DxeSaPolicyLibrary.h
  ///
  MemoryDxeConfig->SpdAddressTable = AllocateZeroPool (sizeof (UINT8) * 4);
  ASSERT (MemoryDxeConfig->SpdAddressTable != NULL);
  if (MemoryDxeConfig->SpdAddressTable != NULL) {
    MemoryDxeConfig->SpdAddressTable[0] = DIMM_SMB_SPD_P0C0D0;
    MemoryDxeConfig->SpdAddressTable[1] = DIMM_SMB_SPD_P0C0D1;
    MemoryDxeConfig->SpdAddressTable[2] = DIMM_SMB_SPD_P0C1D0;
    MemoryDxeConfig->SpdAddressTable[3] = DIMM_SMB_SPD_P0C1D1;
  }
  MemoryDxeConfig->ChannelASlotMap = 0x01;
  MemoryDxeConfig->ChannelBSlotMap = 0x01;
}

/**
  Load DXE Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadVbiosDxeDefault (
  IN VOID    *ConfigBlockPointer
  )
{
  VBIOS_DXE_CONFIG        *VbiosDxeConfig;

  VbiosDxeConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "VbiosDxeConfig->Header.GuidHob.Name = %g\n", &VbiosDxeConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "VbiosDxeConfig->Header.GuidHob.Header.HobLength = 0x%x\n", VbiosDxeConfig->Header.GuidHob.Header.HobLength));
  ///
  /// Initialize the SG VBIOS DXE Policies
  ///
  ///
  /// 1 = secondary display device VBIOS Source is PCI Card
  /// 0 = secondary display device VBIOS Source is FW Volume
  ///
  VbiosDxeConfig->VbiosSource = 1;
}

/**
  LoadSaDxeConfigBlockDefault - Initialize default settings for each SA Config block

  @param[in] ConfigBlockPointer         The buffer pointer that will be initialized as specific config block
  @param[in] BlockId                    Request to initialize defaults of specified config block by given Block ID

  @retval EFI_SUCCESS                   The given buffer has contained the defaults of requested config block
  @retval EFI_NOT_FOUND                 Block ID is not defined so no default Config block will be initialized
**/

GLOBAL_REMOVE_IF_UNREFERENCED COMPONENT_BLOCK_ENTRY  mSaDxeIpBlocks [] = {
  {&gMiscDxeConfigGuid,     sizeof (MISC_DXE_CONFIG),     MISC_DXE_CONFIG_REVISION,      LoadMiscDxeDefault},
  {&gPcieDxeConfigGuid,     sizeof (PCIE_DXE_CONFIG),     PCIE_DXE_CONFIG_REVISION,      LoadPcieDxeDefault},
  {&gMemoryDxeConfigGuid,   sizeof (MEMORY_DXE_CONFIG),   MEMORY_DXE_CONFIG_REVISION,    LoadMemoryDxeDefault},
  {&gVbiosDxeConfigGuid,    sizeof (VBIOS_DXE_CONFIG),    VBIOS_DXE_CONFIG_REVISION,     LoadVbiosDxeDefault}
};


/**
  CreateSaDxeConfigBlocks generates the config blocksg of SA DXE Policy.
  It allocates and zero out buffer, and fills in the Intel default settings.

  @param[out] SaPolicy               The pointer to get SA  DXE Protocol instance

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
CreateSaDxeConfigBlocks (
  IN OUT  SA_POLICY_PROTOCOL      **SaPolicy
  )
{
  UINT16              TotalBlockSize;
  EFI_STATUS          Status;
  SA_POLICY_PROTOCOL  *SaInitPolicy;
  UINT16              RequiredSize;

  DEBUG ((DEBUG_INFO, "SA Create Dxe Config Blocks\n"));

  SaInitPolicy = NULL;

  TotalBlockSize = GetComponentConfigBlockTotalSize (&mSaDxeIpBlocks[0], sizeof (mSaDxeIpBlocks) / sizeof (COMPONENT_BLOCK_ENTRY));
  TotalBlockSize += GraphicsGetConfigBlockTotalSizeDxe ();
  DEBUG ((DEBUG_INFO, "TotalBlockSize = 0x%x\n", TotalBlockSize));

  RequiredSize = sizeof (CONFIG_BLOCK_TABLE_HEADER) + TotalBlockSize;

  Status = CreateConfigBlockTable (RequiredSize, (VOID *) &SaInitPolicy);
  ASSERT_EFI_ERROR (Status);

  //
  // Initialize Policy Revision
  //
  SaInitPolicy->TableHeader.Header.Revision = SA_POLICY_PROTOCOL_REVISION;
  //
  // Add config blocks.
  //
  Status =  AddComponentConfigBlocks ((VOID *) SaInitPolicy, &mSaDxeIpBlocks[0], sizeof (mSaDxeIpBlocks) / sizeof (COMPONENT_BLOCK_ENTRY));
  ASSERT_EFI_ERROR (Status);
  // Gfx
  Status = GraphicsAddConfigBlocksDxe ((VOID *) SaInitPolicy);
  ASSERT_EFI_ERROR (Status);

  //
  // Assignment for returning SaInitPolicy config block base address
  //
  *SaPolicy = SaInitPolicy;
  return Status;
}


/**
  SaInstallPolicyProtocol installs SA Policy.
  While installed, RC assumes the Policy is ready and finalized. So please update and override
  any setting before calling this function.

  @param[in] ImageHandle                Image handle of this driver.
  @param[in] SaPolicy                   The pointer to SA Policy Protocol instance

  @retval EFI_SUCCESS                   The policy is installed.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer

**/
EFI_STATUS
EFIAPI
SaInstallPolicyProtocol (
  IN  EFI_HANDLE                  ImageHandle,
  IN  SA_POLICY_PROTOCOL         *SaPolicy
  )
{
  EFI_STATUS            Status;

  ///
  /// Print SA DXE Policy
  ///
  SaPrintPolicyProtocol (SaPolicy);
  GraphicsDxePolicyPrint (SaPolicy);

  ///
  /// Install protocol to to allow access to this Policy.
  ///
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gSaPolicyProtocolGuid,
                  SaPolicy,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}

