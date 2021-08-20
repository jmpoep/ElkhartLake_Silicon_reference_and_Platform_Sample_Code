/** @file
  This file is SampleCode of the library for Intel Silicon PEI
  Platform Policy initialization.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#include <Library/PeiSiPolicyUpdate.h>
#include <Setup.h>
#include <SetupVariable.h>
#include <Library/HobLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/SiPolicyLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/SerialPortParameterLib.h>
#include <Library/CpuTraceHubInfoLib.h>
#include <Library/PchTraceHubInfoLib.h>
#include <Ppi/ReadOnlyVariable2.h>
#if FixedPcdGet8(PcdFspModeSelection) == 1
#include <FspmUpd.h>
#include <FspsUpd.h>
#endif
#include <PciePreMemConfig.h>
#include <TccConfig.h>
#include <TccConfigSubRegion.h>
#include <Library/PeiTccConfigFvLib.h>
#include <Library/BfxTempRamLib.h>
/**
  This function allocates Trace Hub Memory, and set allocated memory base into policy

  @param[in, out] TraceHubMemBase       Allocated Trace Hub memory base address

  @retval EFI_SUCCESS              The function completed successfully
  @retval EFI_OUT_OF_RESOURCES     Allocated memory failure
**/
EFI_STATUS
TraceHubMemAllocation (
  IN OUT UINT32                   *TraceHubMemBase
  )
{
  UINT32                          TraceHubMemSize;
  EFI_BOOT_MODE                   BootMode;
  EFI_STATUS                      Status;
  SI_SETUP                        SiSetup;
  SA_SETUP                        SaSetup;
  PCH_SETUP                       PchSetup;
  UINTN                           VariableSize;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices;

  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);

  if (BootMode == BOOT_ON_S3_RESUME) {
    return EFI_SUCCESS;
  }

  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &VariableServices
             );
  ASSERT_EFI_ERROR (Status);

  //
  // Get Setup Variable
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
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (SA_SETUP);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"SaSetup",
                               &gSaSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &SaSetup
                               );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (PCH_SETUP);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"PchSetup",
                               &gPchSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &PchSetup
                               );
  ASSERT_EFI_ERROR (Status);

  TraceHubMemSize = TraceHubCalculateTotalBufferSize (
                      SiSetup.PlatformDebugConsent,
                      SaSetup.CpuTraceHubMode,
                      SaSetup.CpuTraceHubMemReg0Size,
                      SaSetup.CpuTraceHubMemReg1Size,
                      PchSetup.PchTraceHubMode,
                      PchSetup.PchTraceHubMemReg0Size,
                      PchSetup.PchTraceHubMemReg1Size
                      );
  DEBUG ((DEBUG_INFO, "Allocate Trace Hub Mem Size = 0x%08x\n", TraceHubMemSize));
  *TraceHubMemBase = (UINT32) (UINTN) AllocateAlignedReservedPages (EFI_SIZE_TO_PAGES (TraceHubMemSize), TraceHubMemSize);
  if (*TraceHubMemBase == 0) {
    DEBUG ((DEBUG_ERROR, "AllocateAlignedReservedPages for Trace Hub failed\n"));
    return EFI_OUT_OF_RESOURCES;
  }
  DEBUG ((DEBUG_INFO, "Allocate Trace Hub Mem Base = 0x%08x\n", *TraceHubMemBase));

  return EFI_SUCCESS;
}

VOID
GetTccConfig (
  OUT TCC_CONFIG_SUB_REGION     **TccConfigSubRegion,
  OUT UINT32                    *TccConfigSize
  )
{
  InstallTccConfigFv ();
  GetTccConfigSubRegion (TccConfigSubRegion, TccConfigSize);
}

/**
  This function performs Silicon PEI Policy initialization.

  @retval EFI_SUCCESS             The PPI is installed and initialized.
  @retval EFI_NOT_FOUND           The FspmUpd is not found.
  @retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver
**/
EFI_STATUS
EFIAPI
UpdatePeiSiPolicyPreMem (
  VOID
  )
{
  EFI_STATUS                        Status;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI   *VariableServices;
  UINTN                             VariableSize;
  SI_SETUP                          SiSetup;
#if FixedPcdGetBool(PcdBfxEnable) == 0
  SETUP_DATA                        SetupVariables;
  TCC_CONFIG_SUB_REGION             *TccConfigSubRegion;
  UINT32                            TccConfigSize;
#endif
#if FixedPcdGet8(PcdFspModeSelection) == 1
  VOID                              *FspmUpd;
  EFI_PEI_HOB_POINTERS              Hob;
  DEBUG_CONFIG_DATA_HOB             *DebugConfigData;
  UINT8                             DebugInterfaces;
#else
  SI_PREMEM_POLICY_PPI              *SiPreMemPolicy;
  SI_PREMEM_CONFIG                  *SiPreMemConfig;
  PCIE_PREMEM_CONFIG                *PciePreMemConfig;
#if FixedPcdGetBool(PcdBfxEnable) == 0
  TCC_CONFIG                        *TccPreMemConfig;

  TccPreMemConfig = NULL;
#endif
  SiPreMemPolicy = NULL;
  SiPreMemConfig = NULL;
  PciePreMemConfig = NULL;
#endif

  DEBUG ((DEBUG_INFO, "Update PeiSiPolicyUpdate Pre-Mem Start\n"));

#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspmUpd = NULL;
  FspmUpd = (FSPM_UPD *) PcdGet32 (PcdFspmUpdDataAddress);
  ASSERT (FspmUpd != NULL);
  if (FspmUpd == NULL) {
    return EFI_NOT_FOUND;
  }
#if FixedPcdGetBool(PcdBfxEnable) == 1
  ((FSPM_UPD *)FspmUpd)->FspmArchUpd.StackBase = (VOID *) (UINTN) (BfxGetTempRamBase () + BfxGetTempRamSize () - (PcdGet32 (PcdFspTemporaryRamSize) + PcdGet32 (PcdFspReservedBufferSize)));
#else
  ((FSPM_UPD *)FspmUpd)->FspmArchUpd.StackBase = (VOID *) (UINTN) (PcdGet32 (PcdTemporaryRamBase) + PcdGet32 (PcdTemporaryRamSize) - (PcdGet32 (PcdFspTemporaryRamSize) + PcdGet32 (PcdFspReservedBufferSize)));
#endif
  ((FSPM_UPD *)FspmUpd)->FspmArchUpd.StackSize = PcdGet32 (PcdFspTemporaryRamSize);

  Status = PeiServicesGetBootMode (&(((FSPM_UPD *)FspmUpd)->FspmArchUpd.BootMode));
  if (EFI_ERROR (Status)) {
    ((FSPM_UPD *)FspmUpd)->FspmArchUpd.BootMode = BOOT_WITH_FULL_CONFIGURATION;
  }
  ((FSPM_UPD *)FspmUpd)->FspmArchUpd.BootLoaderTolumSize = 0x0;

  //
  // Initialize DebugConfigData
  //
  DebugInterfaces = 0;
  Hob.Guid = GetFirstGuidHob (&gDebugConfigHobGuid);
  if (Hob.Guid != NULL) {
    DebugConfigData = (DEBUG_CONFIG_DATA_HOB *) GET_GUID_HOB_DATA (Hob.Guid);
    if (DebugConfigData != NULL) {
      // Debug Interfaces
      if (DebugConfigData->RamDebugInterface)      { DebugInterfaces |= STATUS_CODE_USE_RAM; }
      if (DebugConfigData->UartDebugInterface)     { DebugInterfaces |= STATUS_CODE_USE_ISA_SERIAL; }
      if (DebugConfigData->Usb3DebugInterface)     { DebugInterfaces |= STATUS_CODE_USE_USB3; }
      if (DebugConfigData->SerialIoDebugInterface) { DebugInterfaces |= STATUS_CODE_USE_SERIALIO; }
      if (DebugConfigData->TraceHubDebugInterface) { DebugInterfaces |= STATUS_CODE_USE_TRACEHUB; }
      ((FSPM_UPD *)FspmUpd)->FspmConfig.PcdDebugInterfaceFlags  = DebugInterfaces;
      // Serial debug message baud rate
      ((FSPM_UPD *)FspmUpd)->FspmConfig.PcdSerialDebugBaudRate  = DebugConfigData->SerialDebugBaudRate;
      //Serial debug message level
      ((FSPM_UPD *)FspmUpd)->FspmConfig.PcdSerialDebugLevel     = DebugConfigData->SerialDebug;
    }
  }
  DEBUG ((DEBUG_INFO, "FspmUpd->FspmConfig.PcdDebugInterfaceFlags is 0x%X\n", ((FSPM_UPD *)FspmUpd)->FspmConfig.PcdDebugInterfaceFlags));
  DEBUG ((DEBUG_INFO, "FspmUpd->FspmConfig.PcdSerialDebugBaudRate is 0x%X\n", ((FSPM_UPD *)FspmUpd)->FspmConfig.PcdSerialDebugBaudRate));
  DEBUG ((DEBUG_INFO, "FspmUpd->FspmConfig.PcdSerialDebugLevel is 0x%X\n",    ((FSPM_UPD *)FspmUpd)->FspmConfig.PcdSerialDebugLevel));
#else
  Status = PeiServicesLocatePpi (&gSiPreMemPolicyPpiGuid, 0, NULL, (VOID **) &SiPreMemPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gSiPreMemConfigGuid, (VOID *) &SiPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock((VOID *)SiPreMemPolicy, &gPciePreMemConfigGuid, (VOID *)&PciePreMemConfig);
  ASSERT_EFI_ERROR(Status);
#if FixedPcdGetBool(PcdBfxEnable) == 0
  Status = GetConfigBlock((VOID *) SiPreMemPolicy, &gTccPreMemConfigGuid, (VOID *)&TccPreMemConfig);
  ASSERT_EFI_ERROR(Status);
#endif
#endif

  //
  // Retrieve Setup variable
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid, // GUID
             0,                                // INSTANCE
             NULL,                             // EFI_PEI_PPI_DESCRIPTOR
             (VOID **) &VariableServices       // PPI
             );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (SI_SETUP);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"SiSetup",
                               &gSiSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &SiSetup
                               );
  ASSERT_EFI_ERROR (Status);

  if (Status == EFI_SUCCESS) {
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PlatformDebugConsent,  SiPreMemConfig->PlatformDebugConsent,       SiSetup.PlatformDebugConsent);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PcieImrEnabled,        PciePreMemConfig->PcieImr.ImrEnabled,       SiSetup.PcieImrEnable);
    if (SiSetup.PcieImrEnable) {
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PcieImrRpLocation,     PciePreMemConfig->PcieImr.ImrRpLocation,    SiSetup.PcieImrRpLocation);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PcieImrRpSelection,    PciePreMemConfig->PcieImr.ImrRpSelection,   SiSetup.PcieImrRpSelection);
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PcieImrSize,           PciePreMemConfig->PcieImr.ImrSize,          SiSetup.PcieImrSize);
    }
  }
#if FixedPcdGetBool(PcdBfxEnable) == 0
  VariableSize = sizeof (SETUP_DATA);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"Setup",
                               &gSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &SetupVariables
                               );
  ASSERT_EFI_ERROR (Status);

  GetTccConfig (&TccConfigSubRegion, &TccConfigSize);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.TccTuningEnable, TccPreMemConfig->TccTuningEnable,          SetupVariables.TccMode);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.TccConfigBase,   TccPreMemConfig->TccSubRegion.BaseAddress, (UINT64)  TccConfigSubRegion);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.TccConfigSize,   TccPreMemConfig->TccSubRegion.Size,        (UINT32)  TccConfigSize);
#endif
  return EFI_SUCCESS;
}

/*
STATIC SVID_SID_INIT_ENTRY mSsidTablePtr[SI_MAX_DEVICE_COUNT] = {0};
*/

/**
  This provide sample code to update SSID table policy.

  @param[in] FspsUpd/SiConfig  FSPSUPD structure or SICONFIG policy
**/
STATIC
VOID
UpdateSsidPolicy (
#if FixedPcdGet8(PcdFspModeSelection) == 1
  FSPS_UPD   *FspsUpd
#else
  SI_CONFIG  *SiConfig
#endif
  )
{
/*
  Below provides the sample code to update SSID table.
  This is valid when SkipSsidProgramming is FALSE;
  It doesn't need to contain entries for all Intel internal devices.
  It can only contains the SVID_SID_INIT_ENTRY entries for those Dev# Func# which needs
  to be override.
  In the enties, only Dev, Function, SubSystemVendorId, and SubSystemId are required.

  E.g. Platform only needs to override BDF 0:31:5 to AAAA:BBBB and BDF 0:31:3 to CCCC:DDDD,
  it can be done in platform like this:
*/
/*
  UINT32                             EntryCount;

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SiSkipSsidProgramming,  *(UINT32 *)SiConfig->SkipSsidProgramming, FALSE);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SiCustomizedSvid,       *(UINT32 *)SiConfig->CustomizedSvid, 0x1234);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SiCustomizedSsid,       *(UINT32 *)SiConfig->CustomizedSsid, 0x5678);

  EntryCount = 0;
  mSsidTablePtr[EntryCount].Address.Bits.Device   = SpiDeviceNumber ();
  mSsidTablePtr[EntryCount].Address.Bits.Function = SpiFunctionNumber ();
  mSsidTablePtr[EntryCount].SvidSidValue.SubSystemVendorId = 0xAAAA;
  mSsidTablePtr[EntryCount].SvidSidValue.SubSystemId       = 0xBBBB;
  EntryCount ++;
  mSsidTablePtr[EntryCount].Address.Bits.Device   = HdaDevNumber ();
  mSsidTablePtr[EntryCount].Address.Bits.Function = HdaFuncNumber ();
  mSsidTablePtr[EntryCount].SvidSidValue.SubSystemVendorId = 0xCCCC;
  mSsidTablePtr[EntryCount].SvidSidValue.SubSystemId       = 0xDDDD;
  EntryCount ++;
  ASSERT (EntryCount < SI_MAX_DEVICE_COUNT);

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SiSsidTablePtr,           *(UINT32 *)SiConfig->SsidTablePtr, (UINTN) mSsidTablePtr);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SiNumberOfSsidTableEntry, SiConfig->NumberOfSsidTableEntry,  (UINT16) EntryCount);
*/
}

/**
  This function performs Silicon PEI Policy initialization.

  @retval EFI_SUCCESS  The function completed successfully
**/
EFI_STATUS
EFIAPI
UpdatePeiSiPolicy (
  VOID
  )
{
  EFI_STATUS                         Status;
  UINT32                             TraceHubMemBase;
#if FixedPcdGetBool(PcdBfxEnable) == 0
  TCC_CONFIG_SUB_REGION              *TccConfigSubRegion;
  UINT32                             TccConfigSize;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI    *VariableServices;
  UINT32                             VariableSize;
  SETUP_DATA                         SetupVariables;
#endif
#if FixedPcdGet8(PcdFspModeSelection) == 1
  VOID                               *FspsUpd;
#else
  SI_POLICY_PPI                      *SiPolicyPpi;
  SI_CONFIG                          *SiConfig;
  TCC_CONFIG                         *TccConfig;
#endif

  DEBUG ((DEBUG_INFO, "Update PeiSiPolicyUpdate Pos-Mem Start\n"));

  Status = EFI_SUCCESS;
#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspsUpd = NULL;
#else
  SiPolicyPpi     = NULL;
  SiConfig        = NULL;
  TccConfig       = NULL;
  TraceHubMemBase = 0;
#endif

#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspsUpd = (FSPS_UPD *) PcdGet32 (PcdFspsUpdDataAddress);
  ASSERT (FspsUpd != NULL);
#else
  Status = PeiServicesLocatePpi (&gSiPolicyPpiGuid, 0, NULL, (VOID **) &SiPolicyPpi);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gSiConfigGuid, (VOID *) &SiConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gTccConfigGuid, (VOID *) &TccConfig);
  ASSERT_EFI_ERROR (Status);
#endif

  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SiCsmFlag, SiConfig->CsmFlag, 0);
  UpdateSsidPolicy (
#if FixedPcdGet8(PcdFspModeSelection) == 1
    FspsUpd
#else
    SiConfig
#endif
    );

  TraceHubMemAllocation (&TraceHubMemBase);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TraceHubMemBase,          SiConfig->TraceHubMemBase,         TraceHubMemBase);

#if FixedPcdGetBool(PcdBfxEnable) == 0
  //
  // Retrieve Setup variable
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid, // GUID
             0,                                // INSTANCE
             NULL,                             // EFI_PEI_PPI_DESCRIPTOR
             (VOID **) &VariableServices       // PPI
             );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (SETUP_DATA);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"Setup",
                               &gSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &SetupVariables
                               );
  ASSERT_EFI_ERROR (Status);

  GetTccConfig (&TccConfigSubRegion, &TccConfigSize);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TccTuningEnable, TccConfig->TccTuningEnable,          SetupVariables.TccMode);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TccConfigBase,   TccConfig->TccSubRegion.BaseAddress, (UINT64)  TccConfigSubRegion);
  UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.TccConfigSize,   TccConfig->TccSubRegion.Size,        (UINT32)  TccConfigSize);
#endif

  return EFI_SUCCESS;
}

