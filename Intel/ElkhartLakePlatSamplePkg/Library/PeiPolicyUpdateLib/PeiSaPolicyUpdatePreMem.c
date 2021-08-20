/** @file
Do Platform Stage System Agent initialization.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2020 Intel Corporation.

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

#include <Library/PeiSaPolicyUpdate.h>
#include "MemoryConfig.h"
#include <CpuRegs.h>
#include <Library/CpuPlatformLib.h>
#include <Guid/AcpiVariable.h>
#include <Guid/MemoryTypeInformation.h>
#include <Guid/MemoryOverwriteControl.h>
#include <Library/HobLib.h>
#include <Platform.h>
#include <PlatformBoardConfig.h>
#include <Library/SiPolicyLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PeiSaPolicyLib.h>
#include <Library/GpioLib.h>
#include <Library/MeFwStsLib.h>
#include <Guid/S3MemoryVariable.h>
#include <TcssPeiPreMemConfig.h>
#include <Library/CpuPcieInfoLib.h>
#include <TwoLmConfig.h>
#if FixedPcdGet8(PcdFspModeSelection) == 1
#include <FspmUpd.h>
#else
#include <Ppi/FspmArchConfigPpi.h>
#endif
#include <Library/VtdInfoLib.h>
#include <TelemetryPeiConfig.h>
#include <Register/Cpuid.h>

///
/// Memory Reserved should be between 125% to 150% of the Current required memory
/// otherwise BdsMisc.c would do a reset to make it 125% to avoid s4 resume issues.
///
GLOBAL_REMOVE_IF_UNREFERENCED EFI_MEMORY_TYPE_INFORMATION mDefaultMemoryTypeInformation[] = {
  { EfiACPIReclaimMemory,   FixedPcdGet32 (PcdPlatformEfiAcpiReclaimMemorySize) },  // ASL
  { EfiACPIMemoryNVS,       FixedPcdGet32 (PcdPlatformEfiAcpiNvsMemorySize) },      // ACPI NVS (including S3 related)
  { EfiReservedMemoryType,  FixedPcdGet32 (PcdPlatformEfiReservedMemorySize) },     // BIOS Reserved (including S3 related)
  { EfiRuntimeServicesData, FixedPcdGet32 (PcdPlatformEfiRtDataMemorySize) },       // Runtime Service Data
  { EfiRuntimeServicesCode, FixedPcdGet32 (PcdPlatformEfiRtCodeMemorySize) },       // Runtime Service Code
  { EfiMaxMemoryType, 0 }
};


/**
  UpdatePeiSaPolicyPreMem performs SA PEI Policy initialization

  @retval EFI_SUCCESS              The policy is installed and initialized.
**/
EFI_STATUS
EFIAPI
UpdatePeiSaPolicyPreMem (
  VOID
  )
{
  EFI_STATUS                      Status;
  EFI_STATUS                      Status2;
  EFI_STATUS                      Status3;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices;
  SI_SETUP                        SiSetup;
  SETUP_DATA                      SetupData;
  SA_SETUP                        SaSetup;
  CPU_SETUP                       CpuSetup;
  UINTN                           VariableSize;
  SA_MEMORY_RCOMP                 *RcompData;
  WDT_PPI                         *gWdtPei;
  UINT8                           WdtTimeout;
  UINT32                          RoundedBclkFreq;
  UINT8                           Index;
  S3_MEMORY_VARIABLE              S3MemVariable;
  UINTN                           DataSize;
  EFI_MEMORY_TYPE_INFORMATION     MemoryData[EfiMaxMemoryType + 1];
  EFI_BOOT_MODE                   BootMode;
  UINT8                           MorControl;
  PCH_SETUP                       PchSetup;
  UINT16                          MmioSize;
  UINT32                          TraceHubTotalMemSize;
  UINT8                           IgdDvmt50PreAlloc;
  UINT64                          PlatformMemorySize;
  VOID                            *MemorySavedData;
  PRAM_PREMEM_CONFIG              *PramPreMemConfig;
#if FixedPcdGetBool(PcdHgEnable) == 1
  HYBRID_GRAPHICS_CONFIG          *HgGpioData;
#endif
#if FixedPcdGetBool(PcdFspWrapperEnable) == 1
#endif
#if FixedPcdGet8(PcdFspModeSelection) == 1
  VOID                            *FspmUpd;
  VOID                            *MemorySpdPtr00;
  VOID                            *MemorySpdPtr10;
#else
  SI_PREMEM_POLICY_PPI            *SiPreMemPolicyPpi;
  GRAPHICS_PEI_PREMEM_CONFIG      *GtPreMemConfig;
  MEMORY_CONFIGURATION            *MemConfig;
#if FixedPcdGetBool(PcdIpuEnable) == 1
  IPU_PREMEM_CONFIG               *IpuPreMemPolicy;
#endif
  SA_MISC_PEI_PREMEM_CONFIG       *MiscPeiPreMemConfig;
  MEMORY_CONFIG_NO_CRC            *MemConfigNoCrc;
  CPU_TRACE_HUB_PREMEM_CONFIG     *CpuTraceHubPreMemConfig;
  VTD_CONFIG                      *Vtd;
  EFI_PEI_PPI_DESCRIPTOR          *FspmArchConfigPpiDesc;
  FSPM_ARCH_CONFIG_PPI            *FspmArchConfigPpi;
#endif
  UINT16                          AdjustedMmioSize;
  CPUID_VERSION_INFO_ECX          Ecx;

  DEBUG ((DEBUG_INFO, "Update PeiSaPolicyUpdate Pre-Mem Start\n"));

  RcompData            = NULL;
  PlatformMemorySize   = 0;
  TraceHubTotalMemSize = 0;
#if FixedPcdGetBool(PcdHgEnable) == 1
  HgGpioData           = NULL;
#endif
  PramPreMemConfig     = NULL;
#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspmUpd              = NULL;
  MemorySpdPtr10       = NULL;
  MemorySpdPtr00       = NULL;
#else
  SiPreMemPolicyPpi    = NULL;
  GtPreMemConfig       = NULL;
  MemConfig            = NULL;
#if FixedPcdGetBool(PcdIpuEnable) == 1
  IpuPreMemPolicy      = NULL;
#endif
  MemConfigNoCrc       = NULL;
  MiscPeiPreMemConfig  = NULL;
  CpuTraceHubPreMemConfig = NULL;
#endif

  AdjustedMmioSize = PcdGet16 (PcdSaMiscMmioSizeAdjustment);

#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspmUpd = (FSPM_UPD *) PcdGet32 (PcdFspmUpdDataAddress);
  ASSERT (FspmUpd != NULL);
#else
  Status = PeiServicesLocatePpi (&gSiPreMemPolicyPpiGuid, 0, NULL, (VOID **) &SiPreMemPolicyPpi);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock((VOID *) SiPreMemPolicyPpi, &gSaMiscPeiPreMemConfigGuid, (VOID *) &MiscPeiPreMemConfig);
  ASSERT_EFI_ERROR(Status);

  Status = GetConfigBlock((VOID *) SiPreMemPolicyPpi, &gGraphicsPeiPreMemConfigGuid, (VOID *) &GtPreMemConfig);
  ASSERT_EFI_ERROR(Status);

  Status = GetConfigBlock((VOID *) SiPreMemPolicyPpi, &gMemoryConfigGuid, (VOID *) &MemConfig);
  ASSERT_EFI_ERROR(Status);
#if FixedPcdGetBool(PcdHgEnable) == 1
  Status = GetConfigBlock((VOID *) SiPreMemPolicyPpi, &gHybridGraphicsConfigGuid, (VOID *) &HgGpioData);
  ASSERT_EFI_ERROR(Status);
#endif
#if FixedPcdGetBool(PcdIpuEnable) == 1
  Status = GetConfigBlock((VOID *) SiPreMemPolicyPpi, &gIpuPreMemConfigGuid, (VOID *) &IpuPreMemPolicy);
  ASSERT_EFI_ERROR (Status);
#endif
  Status = GetConfigBlock((VOID *) SiPreMemPolicyPpi, &gMemoryConfigNoCrcGuid, (VOID *) &MemConfigNoCrc);
  ASSERT_EFI_ERROR(Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuTraceHubPreMemConfigGuid, (VOID *) &CpuTraceHubPreMemConfig);
  ASSERT_EFI_ERROR(Status);

  Status = GetConfigBlock((VOID *) SiPreMemPolicyPpi, &gVtdConfigGuid, (VOID *)&Vtd);
  ASSERT_EFI_ERROR(Status);
  Status = GetConfigBlock((VOID *) SiPreMemPolicyPpi, &gPramPreMemConfigGuid, (VOID *) &PramPreMemConfig);
  ASSERT_EFI_ERROR(Status);
#endif

#if FixedPcdGet8(PcdFspModeSelection) == 0
  RcompData = MemConfigNoCrc->RcompData;
#endif

  //
  // Locate system configuration variable
  //
  Status = PeiServicesLocatePpi(
             &gEfiPeiReadOnlyVariable2PpiGuid, // GUID
             0,                                // INSTANCE
             NULL,                             // EFI_PEI_PPI_DESCRIPTOR
             (VOID **) &VariableServices       // PPI
             );
  ASSERT_EFI_ERROR(Status);

  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);

  //
  // Initialize S3 Data variable (S3DataPtr)
  //
  VariableSize = 0;
  MemorySavedData = NULL;
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"MemoryConfig",
                               &gMemoryConfigVariableGuid,
                               NULL,
                               &VariableSize,
                               MemorySavedData
                               );
  if (Status == EFI_BUFFER_TOO_SMALL) {
    MemorySavedData = AllocateZeroPool (VariableSize);
    ASSERT (MemorySavedData != NULL);

    Status = VariableServices->GetVariable (
                                 VariableServices,
                                 L"MemoryConfig",
                                 &gMemoryConfigVariableGuid,
                                 NULL,
                                 &VariableSize,
                                 MemorySavedData
                                 );
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Fail to retrieve Variable: MemoryConfig, Status = %r\n", Status));
      ASSERT_EFI_ERROR (Status);
    }
  }
#if FixedPcdGet8(PcdFspModeSelection) == 0
  FspmArchConfigPpi = (FSPM_ARCH_CONFIG_PPI *) AllocateZeroPool (sizeof (FSPM_ARCH_CONFIG_PPI));
  if (FspmArchConfigPpi == NULL) {
    ASSERT (FALSE);
    return EFI_OUT_OF_RESOURCES;
  }
  FspmArchConfigPpi->Revision     = 1;
  FspmArchConfigPpi->NvsBufferPtr = MemorySavedData;
  MiscPeiPreMemConfig->S3DataPtr  = MemorySavedData;

  FspmArchConfigPpiDesc = (EFI_PEI_PPI_DESCRIPTOR *) AllocateZeroPool (sizeof (EFI_PEI_PPI_DESCRIPTOR));
  if (FspmArchConfigPpiDesc == NULL) {
    ASSERT (FALSE);
    return EFI_OUT_OF_RESOURCES;
  }
  FspmArchConfigPpiDesc->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
  FspmArchConfigPpiDesc->Guid  = &gFspmArchConfigPpiGuid;
  FspmArchConfigPpiDesc->Ppi   = FspmArchConfigPpi;

  //
  // Install FSP-M Arch Config PPI
  //
  Status = PeiServicesInstallPpi (FspmArchConfigPpiDesc);
  ASSERT_EFI_ERROR (Status);

#else
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmArchUpd.NvsBufferPtr, MiscPeiPreMemConfig->S3DataPtr, MemorySavedData);
#endif




  //
  // Get S3 Memory Variable
  //
  VariableSize = sizeof (S3_MEMORY_VARIABLE);
  Status = VariableServices->GetVariable(
                               VariableServices,
                               S3_MEMORY_VARIABLE_NAME,
                               &gS3MemoryVariableGuid,
                               NULL,
                               &VariableSize,
                               &S3MemVariable
                               );
  if (Status == EFI_SUCCESS) {
#if FixedPcdGet8(PcdFspModeSelection) == 0
    MiscPeiPreMemConfig->AcpiReservedMemoryBase = S3MemVariable.AcpiReservedMemoryBase;
    MiscPeiPreMemConfig->AcpiReservedMemorySize = S3MemVariable.AcpiReservedMemorySize;
    MiscPeiPreMemConfig->SystemMemoryLength     = S3MemVariable.SystemMemoryLength;
#endif
  }

  VariableSize = sizeof (MorControl);
  Status = VariableServices->GetVariable(
                               VariableServices,
                               MEMORY_OVERWRITE_REQUEST_VARIABLE_NAME,
                               &gEfiMemoryOverwriteControlDataGuid,
                               NULL,
                               &VariableSize,
                               &MorControl
                               );
  if (EFI_ERROR (Status)) {
    MorControl = 0;
  }

  //
  // Get System configuration variables
  //
  VariableSize = sizeof (SI_SETUP);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"SiSetup",
                               &gSiSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &SiSetup
                               );

  VariableSize = sizeof (SETUP_DATA);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               PLATFORM_SETUP_VARIABLE_NAME,
                               &gSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &SetupData
                               );
  ASSERT_EFI_ERROR(Status);

  VariableSize = sizeof (SA_SETUP);
  Status2 = VariableServices->GetVariable (
                                VariableServices,
                                L"SaSetup",
                                &gSaSetupVariableGuid,
                                NULL,
                                &VariableSize,
                                &SaSetup
                                );
  ASSERT_EFI_ERROR(Status2);

  VariableSize = sizeof (CPU_SETUP);
  Status3 = VariableServices->GetVariable (
                                VariableServices,
                                L"CpuSetup",
                                &gCpuSetupVariableGuid,
                                NULL,
                                &VariableSize,
                                &CpuSetup
                                );
  ASSERT_EFI_ERROR(Status3);

  VariableSize = sizeof (PCH_SETUP);
  VariableServices->GetVariable (
                      VariableServices,
                      L"PchSetup",
                      &gPchSetupVariableGuid,
                      NULL,
                      &VariableSize,
                      &PchSetup
                      );
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.UserBd,     MiscPeiPreMemConfig->UserBd,      0); // It's a CRB mobile board by default (btCRBMB)
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.CridEnable, MiscPeiPreMemConfig->CridEnable,  SaSetup.CridEnable);

#if (FixedPcdGetBool(PcdFspWrapperEnable) == 1) && (FixedPcdGet8(PcdFspModeSelection) == 0)
  MiscPeiPreMemConfig->TxtImplemented = 0;
#endif

  if (SaSetup.IedMemEnable == 1) {
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.IedSize, MiscPeiPreMemConfig->IedSize, 0x400000);
  }

  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.EnableAbove4GBMmio, MiscPeiPreMemConfig->EnableAbove4GBMmio, SaSetup.EnableAbove4GBMmio);
  if (PcdGet32 (PcdMrcRcompTarget)) {
    COPY_POLICY ((VOID *)((FSPM_UPD *) FspmUpd)->FspmConfig.RcompTarget, (VOID *)RcompData->RcompTarget, (VOID *)(UINTN)PcdGet32 (PcdMrcRcompTarget), sizeof (UINT16) * MRC_MAX_RCOMP_TARGETS);
  }

  if (PcdGetBool (PcdMrcDqPinsInterleavedControl)) {
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.DqPinsInterleaved, MemConfig->DqPinsInterleaved, PcdGetBool (PcdMrcDqPinsInterleaved));
  }

  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.SpdAddressTable[0], MiscPeiPreMemConfig->SpdAddressTable[0], PcdGet8 (PcdMrcSpdAddressTable0));
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.SpdAddressTable[1], MiscPeiPreMemConfig->SpdAddressTable[1], PcdGet8 (PcdMrcSpdAddressTable1));
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.SpdAddressTable[2], MiscPeiPreMemConfig->SpdAddressTable[2], PcdGet8 (PcdMrcSpdAddressTable2));
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.SpdAddressTable[3], MiscPeiPreMemConfig->SpdAddressTable[3], PcdGet8 (PcdMrcSpdAddressTable3));

  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.CaVrefConfig, MemConfig->CaVrefConfig, PcdGet8 (PcdMrcCaVrefConfig));

#if FixedPcdGet8(PcdFspModeSelection) == 1
  MemorySpdPtr00 = AllocateZeroPool (SPD_DATA_SIZE);
  ASSERT (MemorySpdPtr00 != NULL);
  MemorySpdPtr10 = AllocateZeroPool (SPD_DATA_SIZE);
  ASSERT (MemorySpdPtr10 != NULL);
  ((FSPM_UPD *) FspmUpd)->FspmConfig.MemorySpdPtr00 = (UINT32) MemorySpdPtr00;
  ((FSPM_UPD *) FspmUpd)->FspmConfig.MemorySpdPtr10 = (UINT32) MemorySpdPtr10;
#endif

  if (PcdGet32 (PcdMrcRcompResistor)) {
    COPY_POLICY ((VOID *)((FSPM_UPD *) FspmUpd)->FspmConfig.RcompResistor, (VOID *)RcompData->RcompResistor, (VOID *)(UINTN)PcdGet32 (PcdMrcRcompResistor), sizeof (UINT16) * MRC_MAX_RCOMP_RESISTOR);
  }

  if (PcdGet32 (PcdMrcDqByteMap)) {
    COPY_POLICY ((VOID *)((FSPM_UPD *) FspmUpd)->FspmConfig.DqByteMapCh0, (VOID *)MemConfigNoCrc->DqByteMap, (VOID *)(UINTN)PcdGet32 (PcdMrcDqByteMap), sizeof (UINT8) * MEM_CFG_MAX_CHANNELS * MRC_DQ_SWIZZLE_ITERATION_MAX * 2);
  }
  if (PcdGet32 (PcdMrcDqsMapCpu2Dram)) {
    COPY_POLICY ((VOID *)((FSPM_UPD *) FspmUpd)->FspmConfig.DqsMapCpu2DramCh0, (VOID *)MemConfigNoCrc->DqsMap, (VOID *)(UINTN)PcdGet32 (PcdMrcDqsMapCpu2Dram), sizeof (UINT8) * MEM_CFG_MAX_CHANNELS * MEM_CFG_NUM_BYTES_MAPPED);
  }
  if (PcdGet32 (PcdMrcSpdData)) {
    COPY_POLICY ((VOID *)((FSPM_UPD *) FspmUpd)->FspmConfig.MemorySpdPtr00, (VOID *)MemConfigNoCrc->SpdData->SpdData[0][0], (VOID *)(UINTN)PcdGet32 (PcdMrcSpdData), SPD_DATA_SIZE);
    COPY_POLICY ((VOID *)((FSPM_UPD *) FspmUpd)->FspmConfig.MemorySpdPtr10, (VOID *)MemConfigNoCrc->SpdData->SpdData[1][0], (VOID *)(UINTN)PcdGet32 (PcdMrcSpdData), SPD_DATA_SIZE);
  }



  if (!EFI_ERROR(Status2)) {
    //
    // Get the Platform Configuration from SetupData
    //
#if FixedPcdGet8(PcdFspModeSelection) == 0
    MiscPeiPreMemConfig->MchBar   = (UINTN) PcdGet64 (PcdMchBaseAddress);
    MiscPeiPreMemConfig->DmiBar   = (UINTN) PcdGet64 (PcdDmiBaseAddress);
    MiscPeiPreMemConfig->EpBar    = (UINTN) PcdGet64 (PcdEpBaseAddress);
    MiscPeiPreMemConfig->EdramBar = (UINTN) PcdGet64 (PcdEdramBaseAddress);
    MiscPeiPreMemConfig->SmbusBar = (UINTN) PcdGet16 (PcdSmbusBaseAddress);
#endif
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.TsegSize,           MiscPeiPreMemConfig->TsegSize,           PcdGet32 (PcdTsegSize));
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.UserBd,             MiscPeiPreMemConfig->UserBd,             PcdGet8 (PcdSaMiscUserBd));
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.MmioSizeAdjustment, MiscPeiPreMemConfig->MmioSizeAdjustment, PcdGet16 (PcdSaMiscMmioSizeAdjustment));



    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.CkeRankMapping, MemConfig->CkeRankMapping, 0xAA);

    //
    // For 2LM Sku, DSM is still required but only needs to be 4MB
    //
    if (SaSetup.DismSize != 0) {
      IgdDvmt50PreAlloc = 0xF0; // 4 MB
    } else {
      IgdDvmt50PreAlloc = SaSetup.IgdDvmt50PreAlloc;
    }

    //
    // Initialize the Graphics configuration
    //
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.IgdDvmt50PreAlloc,          GtPreMemConfig->IgdDvmt50PreAlloc,             IgdDvmt50PreAlloc);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.InternalGfx,                GtPreMemConfig->InternalGraphics,              SaSetup.InternalGraphics);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PrimaryDisplay,             GtPreMemConfig->PrimaryDisplay,                SaSetup.PrimaryDisplay);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.ApertureSize,               GtPreMemConfig->ApertureSize,                  SaSetup.ApertureSize);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.GttSize,                    GtPreMemConfig->GttSize,                       SaSetup.GTTSize);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.GmAdr,                      GtPreMemConfig->GmAdr,                         (UINTN)PcdGet64(PcdGmAdrAddress));
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.GttMmAdr,                   GtPreMemConfig->GttMmAdr,                      (UINTN)PcdGet64(PcdGttMmAddress));
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PsmiRegionSize,             GtPreMemConfig->PsmiRegionSize,                SaSetup.GtPsmiRegionSize);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.DismSize,                   GtPreMemConfig->DismSize,                      SaSetup.DismSize);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.GtPsmiSupport,              GtPreMemConfig->GtPsmiSupport,                 SaSetup.GtPsmiSupport);
    //
    // External Graphics card scan option.
    //
    if (SetupData.CsmControl == EFI_CSM_CONTROL_DETECT_LEGACY_VGA) {
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.ScanExtGfxForLegacyOpRom, MiscPeiPreMemConfig->ScanExtGfxForLegacyOpRom, 1);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.SkipExtGfxScan,           MiscPeiPreMemConfig->SkipExtGfxScan,           0);
    } else {
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.ScanExtGfxForLegacyOpRom, MiscPeiPreMemConfig->ScanExtGfxForLegacyOpRom, 0);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.SkipExtGfxScan,           MiscPeiPreMemConfig->SkipExtGfxScan,           SaSetup.SkipExtGfxScan);
    }

#if FixedPcdGetBool(PcdHgEnable) == 1
    //
    // SaRtd3Pcie GPIO configuration
    //
    if (SaSetup.PcieCardSelect != 2) {
      UPDATE_POLICY (*(UINT8  *)&((FSPM_UPD *) FspmUpd)->FspmConfig.RootPortIndex,       HgGpioData->RootPortIndex,                        PcdGet8 (PcdRootPortIndex));
      UPDATE_POLICY (*(UINT8  *)&((FSPM_UPD *) FspmUpd)->FspmConfig.CpuPcie0Rtd3Gpio[0],  HgGpioData->CpuPcie0Rtd3Gpio.HoldRst.ExpanderNo,   PcdGet8 (PcdPcieSlot1HoldRstExpanderNo));
      UPDATE_POLICY (*(UINT8  *)&((FSPM_UPD *) FspmUpd)->FspmConfig.CpuPcie0Rtd3Gpio[1],  HgGpioData->CpuPcie0Rtd3Gpio.HoldRst.Active,       PcdGetBool (PcdPcieSlot1HoldRstGpioPolarity));
      UPDATE_POLICY (*(UINT32 *)&((FSPM_UPD *) FspmUpd)->FspmConfig.CpuPcie0Rtd3Gpio[4],  HgGpioData->CpuPcie0Rtd3Gpio.HoldRst.GpioNo,       PcdGet32 (PcdPcieSlot1HoldRstGpioNo));
      UPDATE_POLICY (*(UINT8  *)&((FSPM_UPD *) FspmUpd)->FspmConfig.CpuPcie0Rtd3Gpio[8],  HgGpioData->CpuPcie0Rtd3Gpio.PwrEnable.ExpanderNo, PcdGet8 (PcdPcieSlot1PwrEnableExpanderNo));
      UPDATE_POLICY (*(UINT8  *)&((FSPM_UPD *) FspmUpd)->FspmConfig.CpuPcie0Rtd3Gpio[9],  HgGpioData->CpuPcie0Rtd3Gpio.PwrEnable.Active,     PcdGetBool (PcdPcieSlot1PwrEnableGpioPolarity));
      UPDATE_POLICY (*(UINT32 *)&((FSPM_UPD *) FspmUpd)->FspmConfig.CpuPcie0Rtd3Gpio[12], HgGpioData->CpuPcie0Rtd3Gpio.PwrEnable.GpioNo,     PcdGet32 (PcdPcieSlot1PwrEnableGpioNo));
      UPDATE_POLICY (*(UINT8  *)&((FSPM_UPD *) FspmUpd)->FspmConfig.CpuPcie0Rtd3Gpio[20], HgGpioData->CpuPcie0Rtd3Gpio.GpioSupport,          PcdGet8 (PcdPcieSlot1GpioSupport));
    }

    ///
    /// For Elk-Creek card, invert the Power enable signal
    ///
    if (SaSetup.PcieCardSelect == 0) {
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.CpuPcie0Rtd3Gpio[9],  HgGpioData->CpuPcie0Rtd3Gpio.PwrEnable.Active, !(HgGpioData->CpuPcie0Rtd3Gpio.PwrEnable.Active));
    }
    //
    // Initialize the Hybrid Graphics Configuration
    //
    if (SaSetup.PrimaryDisplay == 4) {
      ///
      /// In Hybrid Gfx mode PCIe needs to be always enabled and IGFX must be set as Primary Display.
      ///
#if FixedPcdGet8(PcdFspModeSelection) == 0
      HgGpioData->HgMode = 2;  //HgModeMuxless
      HgGpioData->HgSubSystemId = 0x2112;
#endif
      UPDATE_POLICY ( ((FSPM_UPD *) FspmUpd)->FspmConfig.PrimaryDisplay, GtPreMemConfig->PrimaryDisplay, 0);
    } else if ((SaSetup.PrimaryDisplay == 1) || (SaSetup.PrimaryDisplay == 2) || (SaSetup.PrimaryDisplay == 3)) {
      ///
      /// In PEG or PCI or Auto mode set Hybrid Gfx mode as dGPU
      ///
#if FixedPcdGetBool(PcdFspWrapperEnable) == 0
      HgGpioData->HgMode = 3;  //HgModeDgpu
      HgGpioData->HgSubSystemId = 0x2212;
#endif
    } else if (SaSetup.PrimaryDisplay == 0) {
      ///
      /// In IGFX only mode mode set Hybrid Gfx mode as Disabled
      ///
#if FixedPcdGetBool(PcdFspWrapperEnable) == 0
      HgGpioData->HgMode = 0;  //HgModeDisabled
      HgGpioData->HgSubSystemId = 0x2212;
#endif
    }

    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.HgDelayAfterPwrEn,     HgGpioData->HgDelayAfterPwrEn,     SaSetup.DelayAfterPwrEn);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.HgDelayAfterHoldReset, HgGpioData->HgDelayAfterHoldReset, SaSetup.DelayAfterHoldReset);
#endif

    ///
    /// Initialize the VTD Configuration
    ///
    if (SaSetup.EnableVtd == 0) {
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.VtdDisable,   Vtd->VtdDisable,   1);
      for (Index = 0; Index < VTD_ENGINE_NUMBER; Index++) {
        UPDATE_POLICY(((FSPM_UPD *)FspmUpd)->FspmConfig.VtdBaseAddress[Index], Vtd->BaseAddress[Index], 0);
      }
    } else {
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.VtdDisable,   Vtd->VtdDisable,   0);
      for (Index = 0; Index < VTD_ENGINE_NUMBER; Index++) {
        UPDATE_POLICY(((FSPM_UPD *)FspmUpd)->FspmConfig.VtdBaseAddress[Index], Vtd->BaseAddress[Index], GetVtdBaseAddress (Index));
      }
    }
    AsmCpuid (CPUID_VERSION_INFO, NULL, NULL, &Ecx.Uint32, NULL);
    if (Ecx.Bits.x2APIC == 1) {
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.X2ApicOptOut, Vtd->X2ApicOptOut, SaSetup.X2ApicOptOut);
    } else {
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.X2ApicOptOut, Vtd->X2ApicOptOut, 1);
    }
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.DmaControlGuarantee, Vtd->DmaControlGuarantee, SaSetup.DmaControlGuarantee);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.VtdIgdEnable, Vtd->VtdIgdEnable, SaSetup.VtdIgdEnable);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.VtdIpuEnable, Vtd->VtdIpuEnable, SaSetup.VtdIpuEnable);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.VtdIopEnable, Vtd->VtdIopEnable, SaSetup.VtdIopEnable);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.VtdItbtEnable, Vtd->VtdItbtEnable, SaSetup.VtdItbtEnable);


#if FixedPcdGetBool(PcdIpuEnable) == 1
    //
    // Initialize IPU PreMem Configuration
    //
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.SaIpuEnable,           IpuPreMemPolicy->IpuEnable,           SaSetup.SaIpuEnable);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.SaIpuImrConfiguration, IpuPreMemPolicy->IpuImrConfiguration, SaSetup.SaIpuImrConfiguration);
#endif
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.HobBufferSize,         MemConfig->HobBufferSize,      SaSetup.HobBufferSize);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.EccSupport,            MemConfig->EccSupport,         SaSetup.EccSupport);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.SaGv,                  MemConfig->SaGv,               SaSetup.SaGv);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.FreqSaGvLow,           MemConfig->FreqSaGvLow,        SaSetup.FreqSaGvLow);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.FreqSaGvMid,           MemConfig->FreqSaGvMid,        SaSetup.FreqSaGvMid);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.DdrSpeedControl,       MemConfig->DdrSpeedControl,    SaSetup.DdrSpeedControl);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.SaGvLowGear2,          MemConfig->SaGvLowGear2,       SaSetup.SaGvLowGear2);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.SaGvMidGear2,          MemConfig->SaGvMidGear2,       SaSetup.SaGvMidGear2);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.SaGvHighGear2,         MemConfig->SaGvHighGear2,      SaSetup.SaGvHighGear2);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.EpgEnable,             MemConfig->EpgEnable,          SaSetup.EpgEnable);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.Idd3n,                 MemConfig->Idd3n,              SaSetup.Idd3n);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.Idd3p,                 MemConfig->Idd3p,              SaSetup.Idd3p);

    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.SpdProfileSelected,    MemConfig->SpdProfileSelected, (CpuSetup.OverclockingSupport == 0) ? 0 : SaSetup.SpdProfileSelected);

    //
    // If user custom profile is selected, we will send the setup values to the MRC.
    // The setup values will be the current memory settings plus user override values.
    // If any other profile is selected or a WDT timeout has occured, we zero out
    // the settings just to be safe.
    //
    gWdtPei = NULL;
    Status = PeiServicesLocatePpi(
               &gWdtPpiGuid,
               0,
               NULL,
               (VOID **) &gWdtPei
               );
    if (gWdtPei != NULL) {
      WdtTimeout = gWdtPei->CheckStatus();
    } else {
      WdtTimeout = FALSE;
    }

    if ((SaSetup.SpdProfileSelected == UserDefined) && (WdtTimeout == FALSE)) {
      //
      // If USER custom profile is selected, we will start the WDT.
      //
      if (gWdtPei != NULL) {
        Status = gWdtPei->ReloadAndStart(WDT_TIMEOUT);
      }

      //
      // Read DDR RefClk setting selected in Bios setup, 0 for 133MHz and 1 for 100MHz.
      //
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.VddVoltage,   MemConfig->VddVoltage,          SaSetup.MemoryVoltage); // Vddq in [mV], 0 = platform default.
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RefClk,       MemConfig->RefClk,              SaSetup.DdrRefClk);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.Ratio,        MemConfig->Ratio,               SaSetup.DdrRatio);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.tCL,          MemConfig->tCL,                 SaSetup.tCL);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.tCWL,         MemConfig->tCWL,                SaSetup.tCWL);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.tFAW,         MemConfig->tFAW,                SaSetup.tFAW);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.tRAS,         MemConfig->tRAS,                SaSetup.tRAS);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.tRCDtRP,      MemConfig->tRCDtRP,             SaSetup.tRCDtRP);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.tREFI,        MemConfig->tREFI,               SaSetup.tREFI);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.tRFC,         MemConfig->tRFC,                SaSetup.tRFC);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.tRRD,         MemConfig->tRRD,                SaSetup.tRRD);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.tRTP,         MemConfig->tRTP,                SaSetup.tRTP);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.tWR,          MemConfig->tWR,                 SaSetup.tWR);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.tWTR,         MemConfig->tWTR,                SaSetup.tWTR);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.NModeSupport, MemConfig->NModeSupport,        SaSetup.NModeSupport);
    } else {
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.VddVoltage,   MemConfig->VddVoltage,          0); // Use platform default as the safe value.
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.Ratio,        MemConfig->Ratio,               0);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.tCL,          MemConfig->tCL,                 0);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.tCWL,         MemConfig->tCWL,                0);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.tFAW,         MemConfig->tFAW,                0);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.tRAS,         MemConfig->tRAS,                0);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.tRCDtRP,      MemConfig->tRCDtRP,             0);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.tREFI,        MemConfig->tREFI,               0);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.tRFC,         MemConfig->tRFC,                0);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.tRRD,         MemConfig->tRRD,                0);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.tRTP,         MemConfig->tRTP,                0);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.tWR,          MemConfig->tWR,                 0);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.tWTR,         MemConfig->tWTR,                0);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.NModeSupport, MemConfig->NModeSupport,        0);
    }
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RemapEnable,      MemConfig->RemapEnable,      SaSetup.RemapEnable);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.MrcFastBoot,      MemConfig->MrcFastBoot,      SaSetup.MrcFastBoot);

    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.ScramblerSupport, MemConfig->ScramblerSupport, SaSetup.ScramblerSupport);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.TrainTrace,       MemConfig->TrainTrace,       SaSetup.TrainTrace);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RmtPerTask,       MemConfig->RmtPerTask,       SaSetup.RmtPerTask);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RMTLoopCount,     MemConfig->RMTLoopCount,     SaSetup.RMTLoopCount);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.MrcTimeMeasure,   MemConfig->MrcTimeMeasure,   SaSetup.MrcTimeMeasure);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.MrcTrainOnWarm,   MemConfig->MrcTrainOnWarm,   SaSetup.MrcTrainOnWarm);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.LowSupplyEnData,  MemConfig->LowSupplyEnData,  SaSetup.LowSupplyEnData);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.LowSupplyEnCcc,   MemConfig->LowSupplyEnCcc,   SaSetup.LowSupplyEnCcc);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.DisPgCloseIdleTimeout,    MemConfig->DisPgCloseIdleTimeout, SaSetup.DisPgCloseIdleTimeout);
    {
      UINT32 CurrentDebugPrintErrorLevel;
      UINT8  ControlLevel;

      CurrentDebugPrintErrorLevel = GetDebugPrintErrorLevel();

      switch (CurrentDebugPrintErrorLevel) {
      case 0:
        ControlLevel = 0;
        break;
      case DEBUG_ERROR:
        ControlLevel = 1;
        break;
      case DEBUG_ERROR | DEBUG_WARN:
        ControlLevel = 2;
        break;
      default:  // DEBUG_ERROR|DEBUG_WARN|DEBUG_INFO|DEBUG_LOAD
        ControlLevel = 3;
      }
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PcdSerialDebugLevel, MemConfigNoCrc->SerialDebugLevel, ControlLevel);
    }
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.ECT,                   MemConfig->ECT,                 SaSetup.ECT);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.SOT,                   MemConfig->SOT,                 SaSetup.SOT);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.ERDMPRTC2D,            MemConfig->ERDMPRTC2D,          SaSetup.ERDMPRTC2D);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RDMPRT,                MemConfig->RDMPRT,              SaSetup.RDMPRT);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RCVET,                 MemConfig->RCVET,               SaSetup.RCVET);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.JWRL,                  MemConfig->JWRL,                SaSetup.JWRL);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.EWRTC2D,               MemConfig->EWRTC2D,             SaSetup.EWRTC2D);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.ERDTC2D,               MemConfig->ERDTC2D,             SaSetup.ERDTC2D);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.WRTC1D,                MemConfig->WRTC1D,              SaSetup.WRTC1D);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.WRVC1D,                MemConfig->WRVC1D,              SaSetup.WRVC1D);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RDTC1D,                MemConfig->RDTC1D,              SaSetup.RDTC1D);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.DIMMODTT,              MemConfig->DIMMODTT,            SaSetup.DIMMODTT);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.DIMMRONT,              MemConfig->DIMMRONT,            SaSetup.DIMMRONT);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.WRSRT,                 MemConfig->WRSRT,               SaSetup.WRSRT);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RDODTT,                MemConfig->RDODTT,              SaSetup.RDODTT);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RDEQT,                 MemConfig->RDEQT,               SaSetup.RDEQT);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RDAPT,                 MemConfig->RDAPT,               SaSetup.RDAPT);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.WRTC2D,                MemConfig->WRTC2D,              SaSetup.WRTC2D);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RDTC2D,                MemConfig->RDTC2D,              SaSetup.RDTC2D);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.WRVC2D,                MemConfig->WRVC2D,              SaSetup.WRVC2D);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RDVC2D,                MemConfig->RDVC2D,              SaSetup.RDVC2D);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.CMDVC,                 MemConfig->CMDVC,               SaSetup.CMDVC);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.LCT,                   MemConfig->LCT,                 SaSetup.LCT);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RTL,                   MemConfig->RTL,                 SaSetup.RTL);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.TAT,                   MemConfig->TAT,                 SaSetup.TAT);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RCVENC1D,              MemConfig->RCVENC1D,            SaSetup.RCVENC1D);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RMT,                   MemConfig->RMT,                 SaSetup.RMT);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RMTBIT,                MemConfig->RMTBIT,              SaSetup.RMTBIT);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.MarginLimitCheck,      MemConfig->MarginLimitCheck,    SaSetup.MarginLimitCheck);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.MarginLimitL2,         MemConfig->MarginLimitL2,       SaSetup.MarginLimitL2);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.MEMTST,                MemConfig->MEMTST,              SaSetup.MEMTST);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.ALIASCHK,              MemConfig->ALIASCHK,            SaSetup.ALIASCHK);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RMC,                   MemConfig->RMC,                 SaSetup.RMC);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.WRDSUDT,               MemConfig->WRDSUDT,             SaSetup.WRDSUDT);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.WRDSEQT,               MemConfig->WRDSEQT,             SaSetup.WRDSEQT);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.CMDSR,                 MemConfig->CMDSR,               SaSetup.CMDSR);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.CMDDSEQ,               MemConfig->CMDDSEQ,             SaSetup.CMDDSEQ);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.CMDNORM,               MemConfig->CMDNORM,             SaSetup.CMDNORM);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.EWRDSEQ,               MemConfig->EWRDSEQ,             SaSetup.EWRDSEQ);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RDVC1D,                MemConfig->RDVC1D,              SaSetup.RDVC1D);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.TXTCO,                 MemConfig->TXTCO,               SaSetup.TXTCO);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.CLKTCO,                MemConfig->CLKTCO,              SaSetup.CLKTCO);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.DIMMODTCA,             MemConfig->DIMMODTCA,           SaSetup.DIMMODTCA);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.TXTCODQS,              MemConfig->TXTCODQS,            SaSetup.TXTCODQS);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.DCC,                   MemConfig->DCC,                 SaSetup.DCC);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.DQDFE,                 MemConfig->DQDFE,               SaSetup.DQDFE);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.SOTC,                  MemConfig->SOTC,                SaSetup.SOTC);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.Lp4DqsOscEn,           MemConfig->Lp4DqsOscEn,         SaSetup.Lp4DqsOscEn);

    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.MrcSafeConfig,         MemConfig->MrcSafeConfig,       SaSetup.MrcSafeConfig);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.SafeMode,              MemConfig->SafeMode,            SaSetup.SafeMode);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.Ddr4OneDpc,            MemConfig->Ddr4OneDpc,          SaSetup.Ddr4OneDpc);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.ExitOnFailure,         MemConfig->ExitOnFailure,       SaSetup.ExitOnFailure);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RhPrevention,          MemConfig->RhPrevention,        SaSetup.RhPrevention);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RhSolution,            MemConfig->RhSolution,          SaSetup.RhSolution);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RhActProbability,      MemConfig->RhActProbability,    SaSetup.RhActProbability);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.ChHashEnable,          MemConfig->ChHashEnable,        SaSetup.ChHashEnable);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.ChHashMask,            MemConfig->ChHashMask,          SaSetup.ChHashMask);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.ChHashInterleaveBit,   MemConfig->ChHashInterleaveBit, SaSetup.ChHashInterleaveBit);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.ExtendedBankHashing,   MemConfig->ExtendedBankHashing, SaSetup.ExtendedBankHashing);


#if FixedPcdGetBool(PcdUpServerEnable) == 1
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.UserThresholdEnable,     MemConfig->UserThresholdEnable,     SaSetup.UserThresholdEnable);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.UserBudgetEnable,        MemConfig->UserBudgetEnable,        SaSetup.UserBudgetEnable);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.TsodTcritMax,            MemConfig->TsodTcritMax,            SaSetup.TsodTcritMax);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.TsodEventMode,           MemConfig->TsodEventMode,           SaSetup.TsodEventMode);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.TsodEventPolarity,       MemConfig->TsodEventPolarity,       SaSetup.TsodEventPolarity);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.TsodCriticalEventOnly,   MemConfig->TsodCriticalEventOnly,   SaSetup.TsodCriticalEventOnly);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.TsodEventOutputControl,  MemConfig->TsodEventOutputControl,  SaSetup.TsodEventOutputControl);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.TsodAlarmwindowLockBit,  MemConfig->TsodAlarmwindowLockBit,  SaSetup.TsodAlarmwindowLockBit);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.TsodCriticaltripLockBit, MemConfig->TsodCriticaltripLockBit, SaSetup.TsodCriticaltripLockBit);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.TsodShutdownMode,        MemConfig->TsodShutdownMode,        SaSetup.TsodShutdownMode);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.TsodThigMax,             MemConfig->TsodThigMax,             SaSetup.TsodThigMax);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.TsodManualEnable,        MemConfig->TsodManualEnable,        SaSetup.TsodManualEnable);
#endif

    //
    // Thermal Options
    //
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.EnableExtts,              MemConfig->EnableExtts,           SaSetup.EnableExtts);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.EnableCltm,               MemConfig->EnableCltm,            SaSetup.EnableCltm);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.EnableOltm,               MemConfig->EnableOltm,            SaSetup.EnableOltm);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.EnablePwrDn,              MemConfig->EnablePwrDn,           SaSetup.EnablePwrDn);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.EnablePwrDnLpddr,         MemConfig->EnablePwrDnLpddr,      SaSetup.EnablePwrDnLpddr);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.Refresh2X,                MemConfig->Refresh2X,             SaSetup.Refresh2X);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.DdrThermalSensor,         MemConfig->DdrThermalSensor,      SaSetup.DdrThermalSensor);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.UserPowerWeightsEn,       MemConfig->UserPowerWeightsEn,    SaSetup.UserPowerWeightsEn);

    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.EnergyScaleFact,          MemConfig->EnergyScaleFact,       SaSetup.EnergyScaleFact);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RaplPwrFlCh1,             MemConfig->RaplPwrFlCh1,          SaSetup.RaplPwrFlCh1);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RaplPwrFlCh0,             MemConfig->RaplPwrFlCh0,          SaSetup.RaplPwrFlCh0);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RaplLim2Lock,             MemConfig->RaplLim2Lock,          SaSetup.RaplLim2Lock);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RaplLim2WindX,            MemConfig->RaplLim2WindX,         SaSetup.RaplLim2WindX);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RaplLim2WindY,            MemConfig->RaplLim2WindY,         SaSetup.RaplLim2WindY);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RaplLim2Ena,              MemConfig->RaplLim2Ena,           SaSetup.RaplLim2Ena);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RaplLim2Pwr,              MemConfig->RaplLim2Pwr,           SaSetup.RaplLim2Pwr);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RaplLim1WindX,            MemConfig->RaplLim1WindX,         SaSetup.RaplLim1WindX);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RaplLim1WindY,            MemConfig->RaplLim1WindY,         SaSetup.RaplLim1WindY);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RaplLim1Ena,              MemConfig->RaplLim1Ena,           SaSetup.RaplLim1Ena);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RaplLim1Pwr,              MemConfig->RaplLim1Pwr,           SaSetup.RaplLim1Pwr);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.WarmThresholdCh0Dimm0,    MemConfig->WarmThresholdCh0Dimm0, SaSetup.WarmThresholdCh0Dimm0);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.WarmThresholdCh0Dimm1,    MemConfig->WarmThresholdCh0Dimm1, SaSetup.WarmThresholdCh0Dimm1);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.WarmThresholdCh1Dimm0,    MemConfig->WarmThresholdCh1Dimm0, SaSetup.WarmThresholdCh1Dimm0);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.WarmThresholdCh1Dimm1,    MemConfig->WarmThresholdCh1Dimm1, SaSetup.WarmThresholdCh1Dimm1);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.HotThresholdCh0Dimm0,     MemConfig->HotThresholdCh0Dimm0,  SaSetup.HotThresholdCh0Dimm0);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.HotThresholdCh0Dimm1,     MemConfig->HotThresholdCh0Dimm1,  SaSetup.HotThresholdCh0Dimm1);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.HotThresholdCh1Dimm0,     MemConfig->HotThresholdCh1Dimm0,  SaSetup.HotThresholdCh1Dimm0);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.HotThresholdCh1Dimm1,     MemConfig->HotThresholdCh1Dimm1,  SaSetup.HotThresholdCh1Dimm1);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.WarmBudgetCh0Dimm0,       MemConfig->WarmBudgetCh0Dimm0,    SaSetup.WarmBudgetCh0Dimm0);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.WarmBudgetCh0Dimm1,       MemConfig->WarmBudgetCh0Dimm1,    SaSetup.WarmBudgetCh0Dimm1);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.WarmBudgetCh1Dimm0,       MemConfig->WarmBudgetCh1Dimm0,    SaSetup.WarmBudgetCh1Dimm0);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.WarmBudgetCh1Dimm1,       MemConfig->WarmBudgetCh1Dimm1,    SaSetup.WarmBudgetCh1Dimm1);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.HotBudgetCh0Dimm0,        MemConfig->HotBudgetCh0Dimm0,     SaSetup.HotBudgetCh0Dimm0);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.HotBudgetCh0Dimm1,        MemConfig->HotBudgetCh0Dimm1,     SaSetup.HotBudgetCh0Dimm1);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.HotBudgetCh1Dimm0,        MemConfig->HotBudgetCh1Dimm0,     SaSetup.HotBudgetCh1Dimm0);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.HotBudgetCh1Dimm1,        MemConfig->HotBudgetCh1Dimm1,     SaSetup.HotBudgetCh1Dimm1);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.IdleEnergyCh0Dimm1,       MemConfig->IdleEnergyCh0Dimm1,    SaSetup.IdleEnergyCh0Dimm1);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.IdleEnergyCh0Dimm0,       MemConfig->IdleEnergyCh0Dimm0,    SaSetup.IdleEnergyCh0Dimm0);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PdEnergyCh0Dimm1,         MemConfig->PdEnergyCh0Dimm1,      SaSetup.PdEnergyCh0Dimm1);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PdEnergyCh0Dimm0,         MemConfig->PdEnergyCh0Dimm0,      SaSetup.PdEnergyCh0Dimm0);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.ActEnergyCh0Dimm1,        MemConfig->ActEnergyCh0Dimm1,     SaSetup.ActEnergyCh0Dimm1);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.ActEnergyCh0Dimm0,        MemConfig->ActEnergyCh0Dimm0,     SaSetup.ActEnergyCh0Dimm0);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RdEnergyCh0Dimm1,         MemConfig->RdEnergyCh0Dimm1,      SaSetup.RdEnergyCh0Dimm1);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RdEnergyCh0Dimm0,         MemConfig->RdEnergyCh0Dimm0,      SaSetup.RdEnergyCh0Dimm0);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.WrEnergyCh0Dimm1,         MemConfig->WrEnergyCh0Dimm1,      SaSetup.WrEnergyCh0Dimm1);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.WrEnergyCh0Dimm0,         MemConfig->WrEnergyCh0Dimm0,      SaSetup.WrEnergyCh0Dimm0);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.IdleEnergyCh1Dimm1,       MemConfig->IdleEnergyCh1Dimm1,    SaSetup.IdleEnergyCh1Dimm1);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.IdleEnergyCh1Dimm0,       MemConfig->IdleEnergyCh1Dimm0,    SaSetup.IdleEnergyCh1Dimm0);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PdEnergyCh1Dimm1,         MemConfig->PdEnergyCh1Dimm1,      SaSetup.PdEnergyCh1Dimm1);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PdEnergyCh1Dimm0,         MemConfig->PdEnergyCh1Dimm0,      SaSetup.PdEnergyCh1Dimm0);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.ActEnergyCh1Dimm1,        MemConfig->ActEnergyCh1Dimm1,     SaSetup.ActEnergyCh1Dimm1);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.ActEnergyCh1Dimm0,        MemConfig->ActEnergyCh1Dimm0,     SaSetup.ActEnergyCh1Dimm0);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RdEnergyCh1Dimm1,         MemConfig->RdEnergyCh1Dimm1,      SaSetup.RdEnergyCh1Dimm1);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.RdEnergyCh1Dimm0,         MemConfig->RdEnergyCh1Dimm0,      SaSetup.RdEnergyCh1Dimm0);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.WrEnergyCh1Dimm1,         MemConfig->WrEnergyCh1Dimm1,      SaSetup.WrEnergyCh1Dimm1);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.WrEnergyCh1Dimm0,         MemConfig->WrEnergyCh1Dimm0,      SaSetup.WrEnergyCh1Dimm0);

    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.SrefCfgEna,               MemConfig->SrefCfgEna,            SaSetup.SrefCfgEna);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.ThrtCkeMinDefeat,         MemConfig->ThrtCkeMinDefeat,      SaSetup.ThrtCkeMinDefeat);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.ThrtCkeMinTmr,            MemConfig->ThrtCkeMinTmr,         SaSetup.ThrtCkeMinTmr);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.ThrtCkeMinDefeatLpddr,    MemConfig->ThrtCkeMinDefeatLpddr, SaSetup.ThrtCkeMinDefeatLpddr);

    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.Ibecc,                    MemConfig->Ibecc,                 SaSetup.Ibecc);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.IbeccParity,        MemConfig->IbeccParity,        SaSetup.IbeccParity);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.IbeccOperationMode, MemConfig->IbeccOperationMode, SaSetup.IbeccOperationMode);
    for (Index = 0; Index < MAX_IBECC_REGIONS; Index ++) {
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.IbeccProtectedRegionEnable[Index], MemConfig->IbeccProtectedRegionEnable[Index], SaSetup.IbeccProtectedRegionEnable[Index]);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.IbeccProtectedRegionBase[Index],   MemConfig->IbeccProtectedRegionBase[Index],   SaSetup.IbeccProtectedRegionBase[Index]);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.IbeccProtectedRegionMask[Index],   MemConfig->IbeccProtectedRegionMask[Index],   SaSetup.IbeccProtectedRegionMask[Index]);
    }
#if FixedPcdGet8(PcdFspModeSelection) == 0
    MemConfig->ThrtCkeMinTmrLpddr = SaSetup.ThrtCkeMinTmrLpddr;
#endif

    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.DisableDimmChannel0, MemConfig->DisableDimmChannel[0], SaSetup.DisableDimmMc0Ch0);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.DisableDimmChannel1, MemConfig->DisableDimmChannel[1], SaSetup.DisableDimmMc0Ch1);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.DllBwEn0, MemConfig->DllBwEn0, SaSetup.DllBwEn0);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.DllBwEn1, MemConfig->DllBwEn1, SaSetup.DllBwEn1);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.DllBwEn2, MemConfig->DllBwEn2, SaSetup.DllBwEn2);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.DllBwEn3, MemConfig->DllBwEn3, SaSetup.DllBwEn3);
#if FixedPcdGet8(PcdFspModeSelection) == 0
    MemConfig->RetrainOnFastFail = SaSetup.RetrainOnFastFail;
#endif
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.IsvtIoPort,               MemConfig->IsvtIoPort,            PcdGet8 (PcdIsvtIoPort));

    //
    // Setup BCLK value is in 10kHz units. Convert to Hertz for MRC to use. We need to round
    // the BCLK value to the nearest coarse BCLK freq.
    //
    RoundedBclkFreq = SaSetup.BclkFrequency * 10000;
    if (RoundedBclkFreq > BCLK_MAX) {
      RoundedBclkFreq = BCLK_MAX;
    } else if (RoundedBclkFreq < BCLK_100) {
      RoundedBclkFreq = BCLK_100;
    }

    if ((RoundedBclkFreq % BCLK_GRANULARITY) != 0) {
      RoundedBclkFreq += (BCLK_GRANULARITY - (RoundedBclkFreq % BCLK_GRANULARITY));
    }
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.BClkFrequency, MemConfig->BClkFrequency, RoundedBclkFreq);

    //
    // DDR Frequency Limit (0 = Auto)
    // The values must match the definitions in IcelakeSiliconPkg\SystemAgent\MemoryInit\Include\MrcInterface.h
    //
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.DdrFreqLimit, MemConfig->DdrFreqLimit, SaSetup.DdrFreqLimit);

    //
    // Update MemTestOnWarmBoot variable. Default is run BaseMemoryTest on warm boot.
    //
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.MemTestOnWarmBoot, MemConfigNoCrc->MemTestOnWarmBoot, SaSetup.MemTestOnWarmBoot);

    //
    // Update CleanMemory variable from Memory overwrite request value. Ignore if we are performing capsule update.
    //
    if ((BootMode != BOOT_ON_FLASH_UPDATE) && (BootMode != BOOT_ON_S3_RESUME)) {
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.CleanMemory, MemConfigNoCrc->CleanMemory, (BOOLEAN)(MorControl & MOR_CLEAR_MEMORY_BIT_MASK));
    }

    //
    // Based on BIOS setup to determine maximum top of memory size below 4G, and reserved for MMIO
    //
    switch (SaSetup.MaxTolud) {
      case MAX_TOLUD_DYNAMIC:
        MmioSize = 0x0;
        break;
      case MAX_TOLUD_1G:
        MmioSize = 0xC00;
        break;
      case MAX_TOLUD_1_25G:
        MmioSize = 0xB00;
        break;
      case MAX_TOLUD_1_5G:
        MmioSize = 0xA00;
        break;
      case MAX_TOLUD_1_75G:
        MmioSize = 0x900;
        break;
      case MAX_TOLUD_2G:
        MmioSize = 0x800;
        break;
      case MAX_TOLUD_2_25G:
        MmioSize = 0x700;
        break;
      case MAX_TOLUD_2_5G:
        MmioSize = 0x600;
        break;
      case MAX_TOLUD_2_75G:
        MmioSize = 0x500;
        break;
      default:
      case MAX_TOLUD_3G:
        MmioSize = 0x400;
        break;
      case MAX_TOLUD_3_25G:
        MmioSize = 0x300;
        break;
      case MAX_TOLUD_3_5G:
        MmioSize = 0x200;
        break;
    }
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.MmioSize, MiscPeiPreMemConfig->MmioSize, MmioSize);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.CpuTraceHubMode,        CpuTraceHubPreMemConfig->TraceHub.EnableMode,         SaSetup.CpuTraceHubMode);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.CpuTraceHubMemReg0Size, CpuTraceHubPreMemConfig->TraceHub.MemReg0Size, SaSetup.CpuTraceHubMemReg0Size);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.CpuTraceHubMemReg1Size, CpuTraceHubPreMemConfig->TraceHub.MemReg1Size, SaSetup.CpuTraceHubMemReg1Size);
    //
    // When DCD bit is set, the CPU Trace Hub Mem Buffer Size 1 is hidden,
    // the expectation is MSC1BAR and MSC1SIZE should 0x0.
    //
    if (IsCpuDebugDisabled ()) {
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.CpuTraceHubMemReg1Size, CpuTraceHubPreMemConfig->TraceHub.MemReg1Size, 0);
    }
  }

#if FixedPcdGet8(PcdFspModeSelection) == 0
  //
  // mutiplied by 2 for adding aligned memory (overhead) for natural alignment.
  // please refer to InternalAllocateAlignedPages (), the overhead will be free when creating memory map, it won't waste
  //
  TraceHubTotalMemSize = 2 * TraceHubCalculateTotalBufferSize (
                               SiSetup.PlatformDebugConsent,
                               SaSetup.CpuTraceHubMode,
                               SaSetup.CpuTraceHubMemReg0Size,
                               SaSetup.CpuTraceHubMemReg1Size,
                               PchSetup.PchTraceHubMode,
                               PchSetup.PchTraceHubMemReg0Size,
                               PchSetup.PchTraceHubMemReg1Size
                               );
#endif

  DataSize = sizeof (MemoryData);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               EFI_MEMORY_TYPE_INFORMATION_VARIABLE_NAME,
                               &gEfiMemoryTypeInformationGuid,
                               NULL,
                               &DataSize,
                               &MemoryData
                               );
  ///
  /// Accumulate maximum amount of memory needed
  ///
#if FixedPcdGet8(PcdFspModeSelection) == 1
  PlatformMemorySize = ((FSPM_UPD *) FspmUpd)->FspmConfig.PlatformMemorySize;
#else
  PlatformMemorySize = MemConfigNoCrc->PlatformMemorySize;
#endif
  if (EFI_ERROR (Status)) {
    if (BootMode == BOOT_IN_RECOVERY_MODE) {
      PlatformMemorySize = PEI_RECOVERY_MIN_MEMORY_SIZE;
    } else {
      ///
      /// Use default value to avoid memory fragment. Plus tracehub memory if required.
      /// OS boot/installation fails if there is not enough continuous memory available
      ///
      PlatformMemorySize = PEI_MIN_MEMORY_SIZE + TraceHubTotalMemSize;
      DataSize = sizeof (mDefaultMemoryTypeInformation);
      CopyMem (MemoryData, mDefaultMemoryTypeInformation, DataSize);

      MemoryData[0].NumberOfPages += (INT32) (PcdGet32 (PcdBoardAdjustEfiAcpiReclaimMemorySize));
      MemoryData[1].NumberOfPages += (INT32) (PcdGet32 (PcdBoardAdjustEfiAcpiNvsMemorySize));
      MemoryData[2].NumberOfPages += (INT32) (PcdGet32 (PcdBoardAdjustEfiReservedMemorySize));
      MemoryData[3].NumberOfPages += (INT32) (PcdGet32 (PcdBoardAdjustEfiRtDataMemorySize));
      MemoryData[4].NumberOfPages += (INT32) (PcdGet32 (PcdBoardAdjustEfiRtCodeMemorySize));
    }
  } else {
    ///
    /// Start with at least PEI_MIN_MEMORY_SIZE of memory for the DXE Core and the DXE Stack
    ///
    PlatformMemorySize = PEI_MIN_MEMORY_SIZE + TraceHubTotalMemSize;
  }
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PlatformMemorySize, MemConfigNoCrc->PlatformMemorySize, PlatformMemorySize);

  if (BootMode != BOOT_IN_RECOVERY_MODE) {
    for (Index = 0; Index < DataSize / sizeof (EFI_MEMORY_TYPE_INFORMATION); Index++) {
      PlatformMemorySize += MemoryData[Index].NumberOfPages * EFI_PAGE_SIZE;
    }
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PlatformMemorySize, MemConfigNoCrc->PlatformMemorySize, PlatformMemorySize);
    ///
    /// Pram
    ///
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PramSize, PramPreMemConfig->PramSize, SaSetup.PramSize);

    ///
    /// Build the GUID'd HOB for DXE
    ///
    BuildGuidDataHob (
      &gEfiMemoryTypeInformationGuid,
      MemoryData,
      DataSize
      );
  }

  return EFI_SUCCESS;
}
