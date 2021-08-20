/** @file
  The PEIM implements the SA PEI Initialization.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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

@par Specification
**/
#include <Library/PeiServicesLib.h>
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Ppi/MemoryDiscovered.h>
#include <Ppi/EndOfPeiPhase.h>
#include <Library/PciSegmentLib.h>
#include <CpuRegs.h>
#include <SaRegs.h>
#include <Register/IgdRegs.h>
#include <Register/GnaRegs.h>
#include <PcieRegs.h>
#include <CpuAccess.h>
#include <SaConfigHob.h>
#include <VtdDataHob.h>
#include <Ppi/SiPolicy.h>
#include <Library/CpuMailboxLib.h>
#include <Library/SaInitLib.h>
#include <Library/PeiOcLib.h>
#include <Library/GnaInitLib.h>
#include <Library/PeiGraphicsInitLib.h>
#include <Library/PeiVtdInitLib.h>
#include <Library/SaPcieInitLib.h>
#include <Library/PeiCpuPcieRpInitLib.h>
#include <Library/PeiCpuTraceHubLib.h>
#include <TraceHubDataHob.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PeiDisplayInitLib.h>
#include <Library/GpioPrivateLib.h>
#include <Library/GpioNativePads.h>
#include <Library/PostCodeLib.h>
#include <Library/SaPlatformLib.h>
#if FixedPcdGetBool(PcdITbtEnable) == 1
#include <Library/TcssInitLib.h>
#endif // PcdITbtEnable
#if FixedPcdGetBool(PcdFspBinaryEnable) == 0
#include <Library/SmmAccessLib.h>
#endif
#include <CpuPcieInfo.h>
#include <Library/PeiFusaLib.h>

typedef struct {
  UINT8 DeviceNumber;
  UINT8 FunctionNumber;
  UINT8 SvidRegOffset;
} SA_SVID_SID_INIT_ENTRY;



/**
  Update SA Hobs in PostMem

  @param[in]  Vtd                      - Instance of VTD_CONFIG
  @param[in]  GtConfig                 - Instance of GRAPHICS_PEI_PREMEM_CONFIG
  @param[in]  PciePeiPreMemConfig      - Instance of PCIE_CONFIG
  @param[in]  CpuPcieRpConfig          - Instance of CPU_PCIE_CONFIG
  @param[in]  MiscPeiConfig            - Instance of SA_MISC_PEI_CONFIG
  @param[in]  CpuTraceHubPreMemConfig  - Instance of CPU_TRACE_HUB_PREMEM_CONFIG
  @retval EFI_SUCCESS
**/
EFI_STATUS
UpdateSaHobPostMem (
  IN       VTD_CONFIG                  *Vtd,
  IN       GRAPHICS_PEI_PREMEM_CONFIG  *GtPreMemConfig,
#if FixedPcdGetBool(PcdCpuPcieEnable) == 1
  IN       PCIE_PEI_PREMEM_CONFIG      *PciePeiPreMemConfig,
  IN       CPU_PCIE_CONFIG             *CpuPcieRpConfig,
#endif
  IN       SA_MISC_PEI_CONFIG          *MiscPeiConfig,
  IN       CPU_TRACE_HUB_PREMEM_CONFIG *CpuTraceHubPreMemConfig
  )
{
  SA_CONFIG_HOB               *SaConfigHob;
  VTD_DATA_HOB                *VtdDataHob;
#if FixedPcdGetBool(PcdCpuPcieEnable) == 1
  SA_PEG_HOB                  *SaPegHob;
#endif
  TRACEHUB_DATA_HOB           *TraceHubDataHob;
  UINT8                       Index;

  ///
  /// Locate and update VTD Hob Data
  ///
  VtdDataHob = (VTD_DATA_HOB *) GetFirstGuidHob (&gVtdDataHobGuid);
  if (VtdDataHob != NULL) {
    VtdDataHob->VtdDisable = (BOOLEAN)Vtd->VtdDisable;
    for (Index = 0; Index < VTD_ENGINE_NUMBER; Index++) {
      VtdDataHob->BaseAddress[Index] = Vtd->BaseAddress[Index];
    }
    VtdDataHob->X2ApicOptOut = (BOOLEAN)Vtd->X2ApicOptOut;
    VtdDataHob->DmaControlGuarantee = (BOOLEAN)Vtd->DmaControlGuarantee;
  }

  ///
  /// Locate HOB for SA Config Data
  ///
  SaConfigHob = (SA_CONFIG_HOB *) GetFirstGuidHob (&gSaConfigHobGuid);
  if (SaConfigHob != NULL) {
    SaConfigHob->ApertureSize = (UINT8) (GtPreMemConfig->ApertureSize);

    ///
    /// Init Other Hob fields
    ///
    SaConfigHob->SkipPamLock = (BOOLEAN) (UINTN) MiscPeiConfig->SkipPamLock;
    ///
    /// Init TraceHubDataHob->CpuTraceHubMode
    ///
    TraceHubDataHob = (TRACEHUB_DATA_HOB *) GetFirstGuidHob (&gTraceHubDataHobGuid);
    if (TraceHubDataHob != NULL) {
      TraceHubDataHob->CpuTraceHubMode = CpuTraceHubPreMemConfig->TraceHub.EnableMode;
    }
    DEBUG ((DEBUG_INFO, "PostMem SA Data HOB updated\n"));
  }
#if FixedPcdGetBool(PcdCpuPcieEnable) == 1
  ///
  /// Locate HOB for SA PEG
  ///
  SaPegHob = GetFirstGuidHob(&gSaPegHobGuid);
  if (SaPegHob != NULL) {
    SaPegHob->InitPcieAspmAfterOprom = (BOOLEAN) (PciePeiPreMemConfig->InitPcieAspmAfterOprom);
    ///
    /// Init SaPcie field in SaPegHob
    ///
    CopyMem (
      SaPegHob->CpuPcieRp.RootPort,
      CpuPcieRpConfig->RootPort,
      sizeof (SaPegHob->CpuPcieRp.RootPort)
      );
    DEBUG ((DEBUG_INFO, "PostMem SA PEG HOB updated\n"));
  }
#endif
  return EFI_SUCCESS;
}


/**
  Function to handle SA at end of PEI

  @retval None

**/
EFI_STATUS
EFIAPI
SaOnEndOfPei (
  VOID
  )
{
  UINTN           McD2BaseAddress;

  EndOfPeiCheckAndForceVddOn ();
  SaS3ResumeAtEndOfPei ();

  ///
  /// Clear IGD GttMmAdr, GmAdr and disable Bus Master and Memory Access for 0/2/0
  ///
  McD2BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, 0);
  PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_CMD, 0x0);
  PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR, 0x0);
  PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR + 0x4, 0x0);
  PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GMADR, 0x0);

  return EFI_SUCCESS;
}

///
/// Functions
///
/**
  This function handles SA S3 resume task

  @retval EFI_STATUS       - Always return EFI_SUCCESS
**/
EFI_STATUS
SaS3ResumeAtEndOfPei (
  VOID
  )
{
  EFI_BOOT_MODE               BootMode;
  EFI_STATUS                  Status;
#if FixedPcdGetBool(PcdFspBinaryEnable) == 0
  SI_POLICY_PPI               *SiPolicyPpi;
  SA_MISC_PEI_CONFIG          *MiscPeiConfig;
  BOOLEAN                     SkipPamLock;
#endif

  Status = PeiServicesGetBootMode (&BootMode);
  DEBUG ((DEBUG_INFO, "[SA] BootMode = %X\n", BootMode));
  if ((Status != EFI_SUCCESS) || (BootMode != BOOT_ON_S3_RESUME)) {
    return EFI_SUCCESS;
  }
  DEBUG ((DEBUG_INFO, "SaS3ResumeAtEndOfPei Callback Entry\n"));
  PostCode (0xA70);
  //
  // SA S3 tasks that must be done after S3 Boot Script Restore finished.
  //
#if FixedPcdGetBool(PcdFspBinaryEnable) == 0
  //
  // In FSP S3 resume path, PAM lock is took care by Notify Phase API, so skipped it here.
  //
  SiPolicyPpi = NULL;
  MiscPeiConfig = NULL;
  SkipPamLock = FALSE;

  Status = PeiServicesLocatePpi (
             &gSiPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPolicyPpi
             );
  if ((Status == EFI_SUCCESS) && (SiPolicyPpi != NULL)) {
    Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gSaMiscPeiConfigGuid, (VOID *) &MiscPeiConfig);
    if (Status == EFI_SUCCESS) {
      SkipPamLock  = (BOOLEAN) (UINTN) MiscPeiConfig->SkipPamLock;
    }
  }

  if (SkipPamLock == FALSE) {
    DEBUG ((DEBUG_INFO, "S3 PAM_LOCK!!\n"));
    PciSegmentOr32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, 0, 0, 0, R_SA_PAM0), BIT0);
  }
#endif

  DEBUG ((DEBUG_INFO, "SaS3ResumeAtEndOfPei Callback Exit\n"));
  PostCode (0xA7F);
  return EFI_SUCCESS;
}
typedef union {
  struct {
    UINT32  Low;
    UINT32  High;
  } Data32;
  UINT64 Data;
} UINT64_STRUCT;
/**
  This function does SA security lock
**/
VOID
SaSecurityLock (
  VOID
  )
{
  CPU_FAMILY                  CpuFamilyId;
  EFI_STATUS                 Status;
  SA_MISC_PEI_CONFIG         *MiscPeiConfig;
  SI_POLICY_PPI              *SiPolicyPpi;
  UINT64_STRUCT              DmiBar;

  DEBUG ((DEBUG_INFO, "SaSecurityLock Start\n"));
  PostCode (0xA50);

  DmiBar.Data32.High = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, R_SA_DMIBAR + 4));
  DmiBar.Data32.Low  = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, R_SA_DMIBAR));
  DmiBar.Data       &= (UINT64) ~BIT0;
  CpuFamilyId        = GetCpuFamily ();

  ///
  /// System Agent Security Lock configuration
  ///
  Status = PeiServicesLocatePpi (
             &gSiPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPolicyPpi
             );
  if ((Status == EFI_SUCCESS) && (SiPolicyPpi != NULL)) {
    Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gSaMiscPeiConfigGuid, (VOID *)&MiscPeiConfig);
    if (Status == EFI_SUCCESS) {
    }
  }

  if (!IsPchLinkDmi (CpuFamilyId)) {
    ///
    /// Enable pOPIO Clockgating during POSTBOOT_SAI Transition before setting pOPIO Security Lock Bit
    ///
    MmioOr32 ((UINTN) (DmiBar.Data + R_SA_DMIBAR_OPIO_PHY_CONTROL), N_SA_DMIBAR_OPIO_CLOCK_GATE);
    if (MmioRead32 (TXT_PUBLIC_BASE + 0x200) & BIT31) {
      ///
      /// For ULT/ULX set DMIBAR offset 0xB34 [26] to lockdown OPI debug on production systems
      ///
      MmioOr32 ((UINTN) (DmiBar.Data + R_SA_DMIBAR_OPIO_PHY_CONTROL), N_SA_DMIBAR_OPIO_SECURITY_LOCK_BIT);
    }
  }

  DEBUG ((DEBUG_INFO, "SaSecurityLock End\n"));
  PostCode (0xA5F);
}

/**
This function performs SA internal devices enabling/disabling

@param[in] MiscPeiConfig - Instance of SA_MISC_PEI_CONFIG
@param[in] GnaConfig - Instance of GNA_CONFIG

**/
VOID
DeviceConfigure (
  IN    SA_MISC_PEI_CONFIG      *MiscPeiConfig,
  IN    GNA_CONFIG              *GnaConfig
  )
{
  UINT64     McD0BaseAddress;
  UINT32     DevEn;

  McD0BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, 0);
  DevEn = PciSegmentRead32 (McD0BaseAddress + R_SA_DEVEN);
  ///
  /// Enable/Disable Thermal device (B0,D4,F0).
  ///
  if (MiscPeiConfig->Device4Enable) {
    DevEn |= B_SA_DEVEN_D4EN_MASK;
  } else {
    DevEn &= ~B_SA_DEVEN_D4EN_MASK;
  }
  ///
  /// Enable/Disable GNA device (B0,D8,F0).
  ///
  if (GnaConfig->GnaEnable) {
    DevEn |= B_SA_DEVEN_D8EN_MASK;
  } else {
    DevEn &= ~B_SA_DEVEN_D8EN_MASK;
  }

  PciSegmentWrite32 (McD0BaseAddress + R_SA_DEVEN, DevEn);
  return;
}

/**
This function does addition DMI VC/TC configuration
Disable VCp
Programme TLDMI VC1RCTL
**/
VOID
DmiTcVcConfigure ()
{
  UINT32           Data32And;
  UINT32           Data32Or;
  UINT32           Register;
  UINT64           McD0BaseAddress;
  UINT64_STRUCT    EpBar;
  UINT64_STRUCT    DmiBar;


  McD0BaseAddress    = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, 0);
  DmiBar.Data32.High = PciSegmentRead32 (McD0BaseAddress + R_SA_DMIBAR + 4);
  DmiBar.Data32.Low  = PciSegmentRead32 (McD0BaseAddress + R_SA_DMIBAR);
  DmiBar.Data       &= (UINT64) ~BIT0;

  EpBar.Data32.High = PciSegmentRead32 (McD0BaseAddress + R_SA_PXPEPBAR + 4);
  EpBar.Data32.Low  = PciSegmentRead32 (McD0BaseAddress + R_SA_PXPEPBAR);
  EpBar.Data       &= (UINT64) ~BIT0;

  DEBUG ((DEBUG_INFO, "Disable VCp\n"));
  ///
  /// Disable VCp: Programming the DMIVCPRCTL DMI Port Register DMIBAR Offset 02Ch = 0x0.
  ///
  Register = R_SA_DMIBAR_DMIVCPRCTL_OFFSET;
  Data32And = 0x0;
  Data32Or = 0x0;
  MmioAndThenOr32 ((UINTN) (DmiBar.Data + Register), Data32And, Data32Or);

  ///
  /// Programming EPVC1RCTL in PXPEPBAR
  ///
  DEBUG ((DEBUG_INFO, "Programming EPVC1RCTL\n"));
  Register = R_SA_DMIBAR_DMIVC1RCTL_OFFSET;
  Data32And = ~(B_SA_PXPEPBAR_EPVC1RCTL_VC1E | B_SA_PXPEPBAR_EPVC1RCTL_VC1ID | B_SA_PXPEPBAR_EPVC1RCTL_TC1VC1M);
  Data32Or = 0x0;
  MmioAndThenOr32 ((UINTN) (EpBar.Data + Register), Data32And, Data32Or);
  return;
}
/**
  SA late PEI Initialization.

  @retval EFI_SUCCESS           Function executed successfully
  @retval EFI_NOT_FOUND         The required PPI could not be located.
**/
EFI_STATUS
EFIAPI
SaInit (
  VOID
  )
{
  EFI_STATUS                   Status;
  SI_PREMEM_POLICY_PPI        *SiPreMemPolicyPpi;
  SI_POLICY_PPI               *SiPolicyPpi;
  SA_MISC_PEI_CONFIG          *MiscPeiConfig;
#if FixedPcdGetBool(PcdCpuPcieEnable) == 1
  PCIE_PEI_PREMEM_CONFIG      *PciePeiPreMemConfig;
  CPU_PCIE_CONFIG             *CpuPcieRpConfig;
#endif
  GRAPHICS_PEI_PREMEM_CONFIG  *GtPreMemConfig;
  GRAPHICS_PEI_CONFIG         *GtConfig;
  CPU_TRACE_HUB_PREMEM_CONFIG *CpuTraceHubPreMemConfig;
  VTD_CONFIG                  *Vtd;
  GNA_CONFIG                  *GnaConfig;
  MEMORY_CONFIGURATION        *MemConfig;
  UINT64_STRUCT               MchBar;
  CPU_FAMILY                  CpuFamilyId;
  CpuFamilyId = GetCpuFamily ();

  MchBar.Data32.High = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, R_SA_MCHBAR + 4));
  MchBar.Data32.Low  = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, R_SA_MCHBAR));
  MchBar.Data       &= (UINT64) ~BIT0;

  DEBUG ((DEBUG_INFO, "PostMem SaInit Entry\n"));
  PostCode (0xA00);
  ///
  /// Get policy settings through the SiSaPolicyPpi
  ///
  Status = PeiServicesLocatePpi (
             &gSiPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);
  if ((Status != EFI_SUCCESS) || (SiPolicyPpi == NULL)) {
    return EFI_NOT_FOUND;
  }
  ///
  /// Get policy settings through the SiPreMemPolicyPpi
  ///
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);
  if ((Status != EFI_SUCCESS) || (SiPreMemPolicyPpi == NULL)) {
    return EFI_NOT_FOUND;
  }
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gSaMiscPeiConfigGuid, (VOID *) &MiscPeiConfig);
  ASSERT_EFI_ERROR (Status);

#if FixedPcdGetBool(PcdCpuPcieEnable) == 1
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuPciePeiPreMemConfigGuid, (VOID *) &PciePeiPreMemConfig);
  ASSERT_EFI_ERROR (Status);
#endif

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gVtdConfigGuid, (VOID *) &Vtd);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gGraphicsPeiPreMemConfigGuid, (VOID *) &GtPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gGraphicsPeiConfigGuid, (VOID *) &GtConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gGnaConfigGuid, (VOID *) &GnaConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gMemoryConfigGuid, (VOID *) &MemConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuTraceHubPreMemConfigGuid, (VOID *) &CpuTraceHubPreMemConfig);
  ASSERT_EFI_ERROR (Status);

#if (FixedPcdGetBool (PcdITbtEnable) == 1)
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gTcssPeiPreMemConfigGuid, (VOID *) &TcssPeiPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock((VOID *) SiPolicyPpi, &gTcssPeiConfigGuid, (VOID *) &TcssPeiConfig);
  ASSERT_EFI_ERROR(Status);

#endif

#if FixedPcdGetBool(PcdVmdEnable) == 1
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gVmdPeiConfigGuid, (VOID *) &VmdPeiConfig);
  ASSERT_EFI_ERROR (Status);
#endif

#if FixedPcdGetBool(Pcd2lmEnable) == 1
  Status = GetConfigBlock((VOID *)SiPreMemPolicyPpi, &gTwoLmPreMemConfigGuid, (VOID *)&TwoLmPreMemConfig);
  ASSERT_EFI_ERROR(Status);
#endif


#if FixedPcdGetBool(PcdCpuPcieEnable) == 1
  Status = GetConfigBlock((VOID *)SiPolicyPpi, &gCpuPcieRpConfigGuid, (VOID *)&CpuPcieRpConfig);
  ASSERT_EFI_ERROR(Status);
#endif
  ///
  /// Check and Enable Panel Power (Vdd Bit)
  ///
  PostMemCheckAndForceVddOn (GtPreMemConfig, GtConfig);

  ///
  /// SA device configuration
  ///
  DEBUG ((DEBUG_INFO, "DeviceConfigure Start\n"));
  PostCode (0xA01);
  DeviceConfigure (MiscPeiConfig, GnaConfig);

  ///
  /// SA Register Mirror
  ///
  DEBUG ((DEBUG_INFO, "Sa Register Mirror Start\n"));
  SaRegisterMirror (GtPreMemConfig);

  ///
  /// Initialize Display Native GPIO's
  ///
  DEBUG ((DEBUG_INFO, "Initializing Display Native Gpio \n"));
  PostCode (0xA0B);
  DisplayNativeGpioInit (GtConfig);

  /// Initialize SA GNA Device
  ///
  DEBUG ((DEBUG_INFO, "Initializing SA GNA device\n"));
  PostCode (0xA16);
  GnaInit (GnaConfig);


  ///
  /// CPU Trace Hub Initialization
  ///
  DEBUG ((DEBUG_INFO, "Initializing ConfigureCpuTraceHub\n"));
  PostCode (0xA22);
  ConfigureCpuTraceHub (CpuTraceHubPreMemConfig->TraceHub.EnableMode);

#if (FixedPcdGetBool (PcdITbtEnable) == 1)
  ///
  /// Initializing TCSS Devices
  ///
  DEBUG ((DEBUG_INFO, "Initializing TCSS\n"));
  PostCode (0xA31);
  TcssInit (SiPolicyPpi, TcssPeiPreMemConfig, TcssPeiConfig);

#endif
  ///
  /// Initialize Late VT-d
  ///
  DEBUG ((DEBUG_INFO, "Initializing VtdLateInit\n"));
  PostCode (0xA37);
  VtdLateInit (Vtd);

  ///
  /// Update SA HOBs in PostMem
  ///
  DEBUG ((DEBUG_INFO, "UpdateSaHobPostMem Start\n"));
  PostCode (0xA02);
  UpdateSaHobPostMem (
    Vtd,
    GtPreMemConfig,
#if FixedPcdGetBool(PcdCpuPcieEnable) == 1
    PciePeiPreMemConfig,
    CpuPcieRpConfig,
#endif
    MiscPeiConfig,
    CpuTraceHubPreMemConfig
  );
#if FixedPcdGetBool(PcdVmdEnable) == 1
  //
  // VMD Initializations if the VMD IP is Supported
  //
  DEBUG ((DEBUG_INFO, "Initializing VMD\n"));
  PostCode (0xA33);
  VmdInit(VmdPeiConfig);
#endif
  ///
  /// PAVP Initialization
  ///
  DEBUG ((DEBUG_INFO, "Initializing Pavp\n"));
  PostCode (0xA32);
  PavpInit (GtConfig, MiscPeiConfig, GtPreMemConfig);

  ///
  /// Program PSMI Registers
  ///
  if (CpuFamilyId == EnumCpuEhl) {
    ProgramPsmiRegs (GtConfig, GtPreMemConfig);
  }

#if FixedPcdGetBool(PcdFspBinaryEnable) == 0
  ///
  /// Install SMM Access PPI
  ///
  DEBUG ((DEBUG_INFO, "PeiInstallSmmAccessPpi Start\n"));
  PostCode (0xA34);
  PeiInstallSmmAccessPpi ();
#endif

#if FixedPcdGetBool(PcdCpuPcieEnable) == 1
#endif


  ///
  /// Program Edram Mode
  ///
  if ((AsmReadMsr64 (MSR_PLATFORM_INFO) & B_MSR_PLATFORM_INFO_EDRAM_ENABLE_MASK) == B_MSR_PLATFORM_INFO_EDRAM_ENABLE_MASK) {
    DEBUG ((DEBUG_INFO, "ProgramEdramMode Start\n"));
    PostCode (0xA36);
    ProgramEdramMode (MiscPeiConfig);
  }
  ///
  /// Configure DMI VC/TC
  ///
  DmiTcVcConfigure ();

  DEBUG((DEBUG_INFO, "Post-Mem SaInit Exit\n"));
  PostCode (0xA4F);

  return EFI_SUCCESS;
}

/**
  Print SA PCI space in Debug log.

  @retval None
**/
VOID
SaPciPrint (
  VOID
  )
{
  UINT64 PciBase;
  UINT8  Device;
  UINT8  i;
  UINT8  j;

  for (Device = 0; Device <= 8; Device++) {
    if ((PcdGetBool (PcdSaPciPrint)) || (Device == 0) || (Device == 2)) {
      PciBase = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, 0, Device, 0, 0);
      if (PciSegmentRead16 (PciBase) != 0xFFFF) {
        DEBUG ((DEBUG_INFO, "\nPrinting PCI space for device %x\n  ", Device));
        for (i = 0; i <= 0xF ; i++) {
          DEBUG ((DEBUG_INFO,"  %2X",i));
        }
        for (i = 0; i <= 0xF; i++) {
          DEBUG ((DEBUG_INFO, "\n%2X", (i * 0x10)));
          for (j = 0; j <= 0xF; j++) {
            DEBUG ((DEBUG_INFO, "  %2X", PciSegmentRead8 (PciBase + (i * 0x10) + j)));
          }
        }
      }
    }
  }

  DEBUG ((DEBUG_INFO, "\n"));
}
/**
  BIOS_RESET_CPL bit is set for processor to activate the power and thermal management
  features on the platform.

  @retval EFI_SUCCESS
**/
EFI_STATUS
SaResetComplete (
  VOID
  )
{
  EFI_STATUS                  Status;
  UINT64_STRUCT               MchBar;
  UINT32                      Data32And;
  UINT32                      Data32Or;
  SI_PREMEM_POLICY_PPI        *SiPreMemPolicyPpi;
  SI_POLICY_PPI               *SiPolicyPpi;
  SA_MISC_PEI_CONFIG          *MiscPeiConfig;
  GRAPHICS_PEI_PREMEM_CONFIG  *GtPreMemConfig;
  GRAPHICS_PEI_CONFIG         *GtConfig;
  MchBar.Data32.High = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, R_SA_MCHBAR + 4));
  MchBar.Data32.Low  = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, R_SA_MCHBAR));
  MchBar.Data       &= (UINT64) ~BIT0;

  ///
  /// Get policy settings through the SaPolicy PPI
  ///
  Status = PeiServicesLocatePpi (&gSiPolicyPpiGuid, 0, NULL, (VOID **) &SiPolicyPpi);
  ASSERT_EFI_ERROR (Status);

  Status = PeiServicesLocatePpi (&gSiPreMemPolicyPpiGuid, 0, NULL, (VOID **) &SiPreMemPolicyPpi);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gSaMiscPeiConfigGuid, (VOID *) &MiscPeiConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gGraphicsPeiPreMemConfigGuid, (VOID *) &GtPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gGraphicsPeiConfigGuid, (VOID *) &GtConfig);
  ASSERT_EFI_ERROR (Status);


  ///
  /// Set MCHBAR Offset 5F00h [10:9] = 11b
  ///
  Data32And = (UINT32) ~(BIT10 | BIT9);
  Data32Or  = 0x3 << 9;
  MmioAndThenOr32 ((UINTN) MchBar.Data + R_SA_MCHBAR_SAPMCTL_OFFSET, Data32And, Data32Or);

  ///
  /// Set BIOS_RESET_CPL
  ///
  DEBUG ((DEBUG_INFO, "Set BIOS_RESET_CPL to indicate all configurations complete\n"));
  PostCode (0xA61);
  MmioOr8 ((UINTN) MchBar.Data + R_SA_MCHBAR_BIOS_RESET_CPL_OFFSET, BIT0 | BIT1);

  ///
  /// Graphics PM initialization after BIOS_RESET_CPL
  ///
  DEBUG ((DEBUG_INFO, "GraphicsPmInit Start\n"));
  PostCode (0xA63);
  GraphicsPmInit (GtPreMemConfig, GtConfig);

  ///
  /// Initialize PEI Display
  ///
  DEBUG ((DEBUG_INFO, "Initializing Pei Display\n"));
  PostCode (0xA03);
  PeiDisplayInit (GtPreMemConfig, GtConfig);

  ///
  /// Initialize full CD Clock
  ///
  DEBUG ((DEBUG_INFO, "Initializing CD Clock\n"));
  PostCode (0xA65);
  CdClkInit (GtConfig, GtPreMemConfig);

  DEBUG ((DEBUG_INFO, "SaPciPrint Start\n"));
  PostCode (0xA64);
  SaPciPrint ();


  DEBUG((DEBUG_INFO, "SaSResetComplete Exit\n"));
  PostCode (0xA6F);
  return EFI_SUCCESS;
}

/**
  ProgramEdramMode - Disable EDRAM by default and enable it through HW Test Mode policy if needed

  @param[in] MiscPeiConfig - Instance of SA_MISC_PEI_CONFIG
**/
VOID
ProgramEdramMode (
  IN    SA_MISC_PEI_CONFIG          *MiscPeiConfig
  )
{
  UINT32                    Data32;
  UINT64_STRUCT             MchBar;

  MchBar.Data32.High = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, R_SA_MCHBAR + 4));
  MchBar.Data32.Low  = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, R_SA_MCHBAR));
  MchBar.Data       &= (UINT64) ~BIT0;

  Data32 = 0x00000000;  // Edram HW mode by default
  if (MiscPeiConfig->EdramTestMode == 0) {
    Data32 = 0x80000000; //EDRAM SW Disable
    DEBUG ((DEBUG_INFO, "Edram SW Disabled %x\n", Data32));
  } else if (MiscPeiConfig->EdramTestMode == 1) {
    Data32 = 0x80000001; //EDRAM SW Enable
    DEBUG ((DEBUG_INFO, "Edram SW Enabled %x\n", Data32));
  }
  DEBUG ((DEBUG_INFO, " Writing MchBar + 0x5878 :  %X\n", Data32));
  MmioWrite32 ((UINTN) MchBar.Data + 0x5878, Data32);

}

