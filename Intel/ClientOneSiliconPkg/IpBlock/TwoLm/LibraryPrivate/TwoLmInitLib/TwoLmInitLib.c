/** @file
  Source file for 2LM feature initialization.

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
#include <Library/TwoLmInitLib.h>
#include <Register/TwoLmRegs.h>
#include <Library/CpuPcieLib.h>
#include <Library/PmcPrivateLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <TwoLmConfig.h>
#include <IndustryStandard/Pci22.h>
#include <SaRegs.h>
#include <Ppi/SiPolicy.h>
#include <Include/PcieRegs.h>
#include <Register/SaRegsHostBridge.h>
#include <Library/TimerLib.h>
#include <Library/DebugLib.h>
#include <Library/PciExpressHelpersLib.h>
#include <Library/ItbtPcieRpInitLib.h>
#include <Library/PcieHelperLib.h>
#include <CpuRegs.h>
#include <CpuSbInfo.h>
#include <Library/IoLib.h>
#include <Library/CpuPlatformLib.h>

#define VC_128PHASE_ARBITRATION     0x4   //100b for 128 phases
#define RETRY_COUNT                 3
/**
This function initializes Far Memory Host Controller.

@param[in]      TwoLmInfo            2LM HOB which will have necessary values to initialize FMHC.
@param[in]      TwoLmConfig              2LM Config block.

@retval EFI_SUCCESS            Successfully initialized Far Memory Host Controller.
**/
STATIC
EFI_STATUS
EFIAPI
FmhcInit(
   IN TWOLM_INFO               *TwoLmInfo
  ,IN TWOLM_PREMEM_CONFIG      *TwoLmConfig
)
{
//  CPU_FAMILY        CpuFamilyId;
  UINT8             PmControlStatusOffset;
  UINT8             PcieCapabilityOffset;
  UINT16            MfvcCapabilityOffset;
  UINT16            L1PmCapabilityOffset;
  UINT16            SecondaryPcieCapabilityOffset;
  UINT16            DataLinkFeatureCapabilityOffset;
  UINT16            PhyLayerCapabilityOffset;
  UINT16            PhyLayerMarginingCapabilityOffset;
  UINT32            Data32;
  UINT32            Data32Or;
  UINT32            Data32And;

  DEBUG ((DEBUG_INFO, "FMHC Initialization Start\n"));

  //
  // FMHC Remap registers need to be programmed only for ICL-R and not needed for TGL.
  // In ICL, remap is done in Memory Controller where as in TGL it is handled in CMF.
  //
//  CpuFamilyId = GetCpuFamily ();
//  if (CpuFamilyId == EnumCpuIclDtHaloR) {
    CpuRegbarWrite64 (CPU_SB_PID_FMHC, R_FMHC_HMRMPNEW, LShiftU64 (TwoLmInfo->ToludBase, N_SA_TOLUD_TOLUD_OFFSET));
    CpuRegbarWrite64 (CPU_SB_PID_FMHC, R_FMHC_HMRMPB, LShiftU64 ((UINT64)TwoLmInfo->RemapBase, N_SA_MCHBAR_REMAPBASE_REMAPBASE_OFFSET));
    CpuRegbarWrite64 (CPU_SB_PID_FMHC, R_FMHC_HMRMPL, LShiftU64 ((UINT64)TwoLmInfo->RemapLimit, N_SA_MCHBAR_REMAPLIMIT_REMAPLMT_OFFSET));

    DEBUG ((DEBUG_INFO, "2LM: Tolud = %x  ", LShiftU64 (TwoLmInfo->ToludBase, N_SA_TOLUD_TOLUD_OFFSET)));
    DEBUG ((DEBUG_INFO, "RemapBase = %lx  ", LShiftU64((UINT64)TwoLmInfo->RemapBase, N_SA_MCHBAR_REMAPBASE_REMAPBASE_OFFSET)));
    DEBUG ((DEBUG_INFO, "RemapLimit = %lx\n", LShiftU64((UINT64)TwoLmInfo->RemapLimit, N_SA_MCHBAR_REMAPLIMIT_REMAPLMT_OFFSET)));
//  }

  //
  // Program Persistent Memory register if it is enabled.
  //
  if (TwoLmInfo->PMemSize != 0) {
    CpuRegbarWrite64 (CPU_SB_PID_FMHC, R_FMHC_PMRBL, LShiftU64(TwoLmInfo->FarMemSize, 20));
    CpuRegbarWrite64 (CPU_SB_PID_FMHC, R_FMHC_PMRLL, (LShiftU64(TwoLmInfo->FarMemSize, 20) + LShiftU64(TwoLmInfo->PMemSize, 20) - 1));
    DEBUG ((DEBUG_INFO, "2LM PMem Base=  %lx, PMem Limit = %lx\n", LShiftU64(TwoLmInfo->FarMemSize, 20), (LShiftU64(TwoLmInfo->FarMemSize, 20) + LShiftU64(TwoLmInfo->PMemSize, 20) - 1)));
  }

  //
  // Enable PMC reqeust
  //
  Data32 = CpuRegbarRead32 (CPU_SB_PID_FMHC, R_FMHC_PCE);
  CpuRegbarWrite32 (CPU_SB_PID_FMHC, R_FMHC_PCE, (Data32 | B_FMHC_PCE_PMCRE));

  //
  // Initialize FM Max Supported Outstanding Request register
  //
  Data32And = ~(UINT32)(B_FMHC_FMAXOUTR_MRTS_MASK | B_FMHC_FMAXOUTR_MWSS_MASK | B_FMHC_FMAXOUTR_MCSRTS_MASK);
  Data32Or = B_FMHC_FMAXOUTR_LOADCV | (TwoLmInfo->Mrts << B_FMHC_FMAXOUTR_MRTS_OFFSET) | (TwoLmInfo->Mwss << B_FMHC_FMAXOUTR_MWSS_OFFSET) | (TwoLmInfo->Mcsrts << B_FMHC_FMAXOUTR_MCSRTS_OFFSET);
  CpuRegbarAndThenOr32 (CPU_SB_PID_FMHC, R_FMHC_FMAXOUTR, Data32And, Data32Or);

  //
  // Initize 2LM, PMem and IRR region IDs
  //
  Data32And = ~(UINT32)(B_FMHC_FMAP_PMRID_MASK | B_FMHC_FMAP_IRRID_MASK | B_FMHC_FMAP_MRID_MASK);
  Data32Or = (TwoLmInfo->RegionIdPMem << B_FMHC_FMAP_PMRID_OFFSET) | (TwoLmInfo->RegionIdIrr << B_FMHC_FMAP_IRRID_OFFSET) | (TwoLmInfo->RegionId2lm << B_FMHC_FMAP_MRID_OFFSET);
  CpuRegbarAndThenOr32 (CPU_SB_PID_FMHC, R_FMHC_FMAP, Data32And, Data32Or);


  //
  // Find Power Management Status/Control register capability offset, PCIe capability offset, Multi Function virtual channel extended capability offset,
  // L1 PM substates extended capability offset and update these values in RCIEPPCIE and RCIEPL1PMMFVC registers.
  //
  PmControlStatusOffset  = PcieFindCapId (SA_SEG_NUM, SA_PEG_BUS_NUM, SA_2LM_DEV_NUM, SA_2LM_FUN0_NUM, PM_CAPID);
  PcieCapabilityOffset  = PcieFindCapId (SA_SEG_NUM, SA_PEG_BUS_NUM, SA_2LM_DEV_NUM, SA_2LM_FUN0_NUM, PCIE_CAPID);
  MfvcCapabilityOffset  = PcieFindExtendedCapId (SA_SEG_NUM, SA_PEG_BUS_NUM, SA_2LM_DEV_NUM, SA_2LM_FUN0_NUM, MFVC_CAPID);
  L1PmCapabilityOffset = PcieFindExtendedCapId (SA_SEG_NUM, SA_PEG_BUS_NUM, SA_2LM_DEV_NUM, SA_2LM_FUN0_NUM, L1PM_CAPID);
  DEBUG ((DEBUG_INFO, "Capabilities offset: PMCSR = %x, Pcie = %x, Mfvc = %x, L1Pm = %x\n", PmControlStatusOffset, PcieCapabilityOffset, MfvcCapabilityOffset, L1PmCapabilityOffset));

  if ( PmControlStatusOffset && PcieCapabilityOffset ) {
    Data32And = ~(UINT32) (B_FMHC_RCIEPPCIE_PMCSR_CAPOFF_MASK | B_FMHC_RCIEPPCIE_DEVTYP_MASK | B_FMHC_RCIEPPCIE_PCIE_CAPOFF_MASK);
    Data32Or = (PmControlStatusOffset << B_FMHC_RCIEPPCIE_PMCSR_CAPOFF_OFFSET) | (V_FMHC_RCIEPPCIE_DEVTYP << B_FMHC_RCIEPPCIE_DEVTYP_OFFSET) | (PcieCapabilityOffset << B_FMHC_RCIEPPCIE_PCIE_CAPOFF_OFFSET) | B_FMHC_RCIEPPCIE_PCIE_CAPOFFEN;
    CpuRegbarAndThenOr32 (CPU_SB_PID_FMHC, R_FMHC_RCIEPPCIE, Data32And, Data32Or);

    Data32And = ~(UINT32) (B_FMHC_RCIEPPCIE2_PCIE_CAPOFFLIM_MASK);
    Data32Or = ((PcieCapabilityOffset + PCIE_CAP_SIZE -1)  << B_FMHC_RCIEPPCIE2_PCIE_CAPOFFLIM_OFFSET);
    CpuRegbarAndThenOr32 (CPU_SB_PID_FMHC, R_FMHC_RCIEPPCIE2, Data32And, Data32Or);
  }

  if ( MfvcCapabilityOffset && L1PmCapabilityOffset ) {
    Data32And = ~(UINT32) (B_FMHC_RCIEPL1PMMFVC_MFVC_CAPOFF_MASK | B_FMHC_RCIEPL1PMMFVC_L1PM_CAPOFF_MASK);
    Data32Or = B_FMHC_RCIEPL1PMMFVC_MFVC_CAPOFFEN | (MfvcCapabilityOffset << B_FMHC_RCIEPL1PMMFVC_MFVC_CAPOFF_OFFSET) | B_FMHC_RCIEPL1PMMFVC_L1PM_CAPOFFEN | (L1PmCapabilityOffset << B_FMHC_RCIEPL1PMMFVC_L1PM_CAPOFF_OFFSET);
    CpuRegbarAndThenOr32 (CPU_SB_PID_FMHC, R_FMHC_RCIEPL1PMMFVC, Data32And, Data32Or);

    Data32And = ~(UINT32) (B_FMHC_RCIEPL1PMMFVC2_MFVC_CAPOFFLIM_MASK | B_FMHC_RCIEPL1PMMFVC2_L1PM_CAPOFFLIM_MASK);
    Data32Or = ((MfvcCapabilityOffset + MFVC_CAP_SIZE -1)  << B_FMHC_RCIEPL1PMMFVC2_MFVC_CAPOFFLIM_OFFSET) | ((L1PmCapabilityOffset + L1PM_CAP_SIZE - 1) << B_FMHC_RCIEPL1PMMFVC2_L1PM_CAPOFFLIM_OFFSET);
    CpuRegbarAndThenOr32 (CPU_SB_PID_FMHC, R_FMHC_RCIEPL1PMMFVC2, Data32And, Data32Or);
  }

  SecondaryPcieCapabilityOffset  = PcieFindExtendedCapId (SA_SEG_NUM, SA_PEG_BUS_NUM, SA_2LM_DEV_NUM, SA_2LM_FUN0_NUM, SEC_PCIE_CAPID);
  DataLinkFeatureCapabilityOffset  = PcieFindExtendedCapId (SA_SEG_NUM, SA_PEG_BUS_NUM, SA_2LM_DEV_NUM, SA_2LM_FUN0_NUM, DATA_LINK_FEATURE_CAPID);
  DEBUG ((DEBUG_INFO, "Capabilities offset: Secondary Pcie = %x, Data Link feature = %x\n", SecondaryPcieCapabilityOffset, DataLinkFeatureCapabilityOffset));

  if ( SecondaryPcieCapabilityOffset && DataLinkFeatureCapabilityOffset ) {
    Data32And = ~(UINT32) (B_FMHC_RCIEPLCAPAB_CAPSTRUCT_B_CAPOFF_MASK | B_FMHC_RCIEPLCAPAB_CAPSTRUCT_A_CAPOFF_MASK);
    Data32Or = B_FMHC_RCIEPLCAPAB_CAPSTRUCT_B_CAPOFFEN | (SecondaryPcieCapabilityOffset << B_FMHC_RCIEPLCAPAB_CAPSTRUCT_B_CAPOFF_OFFSET) | B_FMHC_RCIEPLCAPAB_CAPSTRUCT_A_CAPOFFEN | (DataLinkFeatureCapabilityOffset << B_FMHC_RCIEPLCAPAB_CAPSTRUCT_A_CAPOFF_OFFSET);
    CpuRegbarAndThenOr32 (CPU_SB_PID_FMHC, R_FMHC_RCIEPLCAPAB, Data32And, Data32Or);

    Data32And = ~(UINT32) (B_FMHC_RCIEPLCAPAB_CAPSTRUCT_B_CAPOFFLIM_MASK | B_FMHC_RCIEPLCAPAB_CAPSTRUCT_A_CAPOFFLIM_MASK);
    Data32Or = ((SecondaryPcieCapabilityOffset + SEC_PCIE_CAP_SIZE -1)  << B_FMHC_RCIEPLCAPAB_CAPSTRUCT_B_CAPOFFLIM_OFFSET) | ((DataLinkFeatureCapabilityOffset + DATA_LINK_FEATURE_CAP_SIZE - 1) << B_FMHC_RCIEPLCAPAB_CAPSTRUCT_A_CAPOFFLIM_OFFSET);
    CpuRegbarAndThenOr32 (CPU_SB_PID_FMHC, R_FMHC_RCIEPLCAPAB2, Data32And, Data32Or);
  }

  PhyLayerCapabilityOffset  = PcieFindExtendedCapId (SA_SEG_NUM, SA_PEG_BUS_NUM, SA_2LM_DEV_NUM, SA_2LM_FUN0_NUM, PHY_LAYER_16_CAPID);
  PhyLayerMarginingCapabilityOffset  = PcieFindExtendedCapId (SA_SEG_NUM, SA_PEG_BUS_NUM, SA_2LM_DEV_NUM, SA_2LM_FUN0_NUM, PHY_LAYER_16_MARGINING_CAPID);
  DEBUG ((DEBUG_INFO, "Capabilities offset: Physical Layer = %x, Physical Layer Margining = %x\n", PhyLayerCapabilityOffset, PhyLayerMarginingCapabilityOffset));

  if ( PhyLayerCapabilityOffset && PhyLayerMarginingCapabilityOffset ) {
    Data32And = ~(UINT32) (B_FMHC_RCIEPLCAPCD_CAPSTRUCT_D_CAPOFF_MASK | B_FMHC_RCIEPLCAPCD_CAPSTRUCT_C_CAPOFF_MASK);
    Data32Or = B_FMHC_RCIEPLCAPCD_CAPSTRUCT_D_CAPOFFEN | (PhyLayerCapabilityOffset << B_FMHC_RCIEPLCAPCD_CAPSTRUCT_D_CAPOFF_OFFSET) | B_FMHC_RCIEPLCAPCD_CAPSTRUCT_C_CAPOFFEN | (PhyLayerMarginingCapabilityOffset << B_FMHC_RCIEPLCAPCD_CAPSTRUCT_C_CAPOFF_OFFSET);
    CpuRegbarAndThenOr32 (CPU_SB_PID_FMHC, R_FMHC_RCIEPLCAPAB, Data32And, Data32Or);

    Data32And = ~(UINT32) (B_FMHC_RCIEPLCAPCD_CAPSTRUCT_D_CAPOFFLIM_MASK | B_FMHC_RCIEPLCAPCD_CAPSTRUCT_C_CAPOFFLIM_MASK);
    Data32Or = ((PhyLayerCapabilityOffset + PHY_LAYER_16_CAP_SIZE - 1) << B_FMHC_RCIEPLCAPCD_CAPSTRUCT_D_CAPOFFLIM_OFFSET) | ((PhyLayerMarginingCapabilityOffset + PHY_LAYER_16_MARGINING_CAP_SIZE - 1) << B_FMHC_RCIEPLCAPCD_CAPSTRUCT_C_CAPOFFLIM_OFFSET);
    CpuRegbarAndThenOr32 (CPU_SB_PID_FMHC, R_FMHC_RCIEPLCAPAB2, Data32And, Data32Or);
  }

  //
  // Program TPower on Pmstates register based on the value from Willard device.
  //
  CpuRegbarWrite32 (CPU_SB_PID_FMHC, R_TPOWER_ON_PMSTATES, (TwoLmInfo->TpowerOnSupport & (~(BIT2 | BIT10))));
  DEBUG ((DEBUG_INFO, "TPower On Pmstatues value = %x\n", TwoLmInfo->TpowerOnSupport));

  //
  // Program FMHC internal clock gating
  //
  Data32And = ~(UINT32) (B_FMHC_GC03_DCG_AES_DIS | B_FMHC_GC03_DCG_MTU_DIS | B_FMHC_GC03_DCG_STU_DIS | B_FMHC_GC03_DCG_CMIEP_DIS | B_FMHC_GC03_DCG_HBIF_DIS | B_FMHC_GC03_DCG_SBREG_DIS | B_FMHC_GC03_DCG_PMU_DIS | B_FMHC_GC03_DCG_IPDYN_DIS);
  CpuRegbarAndThenOr32 (CPU_SB_PID_FMHC, R_FMHC_GC03, Data32And, 0);

  Data32And = ~(UINT32) (B_FMHC_PRI_CDCB_CCD | B_FMHC_PRI_CDCB_DDCGD);
  CpuRegbarAndThenOr32 (CPU_SB_PID_FMHC, R_FMHC_PRI_CDCB, Data32And, 0);

  Data32And = ~(UINT32) (B_FMHC_SB_CDCB_CCD | B_FMHC_SB_CDCB_DDCGD);
  CpuRegbarAndThenOr32 (CPU_SB_PID_FMHC, R_FMHC_SB_CDCB, Data32And, 0);

  //
  // Lock FMHC registers and REGACC register itself
  //
  CpuRegbarOr32 (CPU_SB_PID_FMHC, R_FMHC_REGACC, B_FMHC_REGACC_MAPLCK | B_FMHC_REGACC_RMPBARLCK | B_FMHC_REGACC_PMBARLCK | B_FMHC_REGACC_LCK);

  return EFI_SUCCESS;
}


/**
This function initializes Astro Near Memory Controller.

@param[in]    TwoLmInfo    2LM HOB which will have necessary values to initialize Astro.

@retval       EFI_SUCCESS      Successfully initialized Astro Near Memory Controller.
**/
STATIC
EFI_STATUS
EFIAPI
AstroInit (
  IN TWOLM_INFO    *TwoLmInfo
)
{
  UINTN             Edrambar;
  UINT32            MchBar;
  UINT32            Data32Or;
  UINT32            Data32And;
  UINT64            Data64Or;
  UINT64            Data64And;
  UINT64            Remainder;
  UINT64            RemapLimit;

  DEBUG ((DEBUG_INFO, "2LM: Astro Initialization Start\n"));
  MchBar = PegPciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_PEG_BUS_NUM, 0, 0, 0) + R_SA_MCHBAR) & ~BIT0;
  Edrambar = MmioRead64 (MchBar +R_SA_MCHBAR_EDRAMBAR_OFFSET) & ~BIT0;
  DEBUG ((DEBUG_INFO, "2LM: EDRAM Base is 0X %x\n",Edrambar ));
  if(!Edrambar) {
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }

  if (TwoLmInfo->CurrentMemBootMode == MEM_BOOT_MODE_2LM ) {
    Data64And = ~(UINT64) (B_SXP_SIZE_MASK | B_PMEM_EN | B_PMEM_SIZE_MASK);
    //
    // SXP_SIZE field is in GigaByte alignment. If upper usable memory address ie RemapLimit is not GigaByte aligned, then align it to nearest Gigabyte.
    //
    RemapLimit = LShiftU64((UINT64)TwoLmInfo->RemapLimit, N_SA_MCHBAR_REMAPLIMIT_REMAPLMT_OFFSET);
    RemapLimit = DivU64x64Remainder(RemapLimit, MEM_EQU_1GB, &Remainder);
    if (Remainder != 0) {
      RemapLimit = RemapLimit + 1;
    }
    Data64Or = (RemapLimit << B_SXP_SIZE_OFFSET);
    if (TwoLmInfo->PMemSize != 0) {
      Data64Or = Data64Or | B_PMEM_EN;
      Data64Or = Data64Or | LShiftU64(((TwoLmInfo->PMemSize)/1024), B_PMEM_SIZE_OFFSET); // size in GB
    }
    MmioAndThenOr64 (Edrambar + ASTRO_OFFSET + R_ASTRO_SXP_CONFIG_1, Data64And, Data64Or);
    MmioAndThenOr64 (Edrambar + ASTRO_OFFSET + R_ASTRO_SXP_CONFIG_2, Data64And, Data64Or);

    Data32And = (UINT32) (~B_DDR_SIZE_MASK);
    Data32Or = (((TwoLmInfo->NearMemSize)/1024) << B_DDR_SIZE_OFFSET); // size in GB
    MmioAndThenOr32 (Edrambar + ASTRO_OFFSET + R_ASTRO_DDR_CONFIG, Data32And, Data32Or);
  } else { //Reset default reg values to 0 (curremtly default is non zero )
    MmioWrite64 (Edrambar + ASTRO_OFFSET + R_ASTRO_SXP_CONFIG_1, 0x0);
    MmioWrite64 (Edrambar + ASTRO_OFFSET + R_ASTRO_SXP_CONFIG_2, 0x0);
    MmioWrite32 (Edrambar + ASTRO_OFFSET + R_ASTRO_DDR_CONFIG, 0x0);
    DEBUG ((DEBUG_INFO, "2LM: Resetting Astro SXP rgisters\n"));
  }

  DEBUG ((DEBUG_INFO, "2LM: Astro Initialization End\n"));
  return EFI_SUCCESS;
}

/**
This function initializes Willard device for Powermanagent and 2LM enable.

@param[in]      TwoLmConfig            2LM Config block.
@param[in]      TWOLM_INFO_HOB         *TwoLmInfoHob

@retval         EFI_SUCCESS            Successfully initialized Willard device.
**/
STATIC
EFI_STATUS
EFIAPI
WillardInit (
  IN TWOLM_PREMEM_CONFIG      *TwoLmPreMemConfig,
  IN TWOLM_INFO_HOB           *TwoLmInfoHob
  )
{
  UINT32            Data;
  UINT32            SocData;
  UINT16            SocL1PmCapabilityOffset;
  UINT32            SocValue;
  UINT32            SocScale;
  UINT32            DevValuePm4;
  UINT32            DevScalePm4;
  UINT32            DevValuePm5;
  UINT32            DevScalePm5;
  UINT32            SocBaseAddress;
  EFI_BOOT_MODE     BootMode;

  EFI_STATUS  Status;

  //
  // 1. Read VDM Device HW Status register (150ms for now from platform Power up)
  //
  Status = RegReadVdm (R_SA_FMSS_VDM_MAIL_BOX_DEVHWS, &Data);
  ASSERT_EFI_ERROR (Status);

  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);

  if (!(Data & B_SA_FMSS_VDM_MAIL_BOX_DEVHWS_FWLOADED)) {
    DEBUG ((DEBUG_INFO, "2LM: Device FW error, booting in 1LM mode\n"));
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }

  // 7.  VDM write to PSC register (0x0014h) for every boot :
  //  a.  Write 10 to bit[31:30] if booting from S3 resume.
  //  b.  Write 01 to bit[31:30] for all other boots.
  // Note : BIOS must write to bit[31:30] of the PSC register for every boot.
  Status = RegReadVdm (R_SA_FMSS_VDM_MAIL_BOX_POWER_STATE_CONTROL, &Data);
  ASSERT_EFI_ERROR (Status);
  Data &= ~(BIT31 | BIT30);
  if(BootMode != BOOT_ON_S3_RESUME) {
    Status = RegWriteVdm (R_SA_FMSS_VDM_MAIL_BOX_POWER_STATE_CONTROL, (Data | BIT30));
    ASSERT_EFI_ERROR (Status);
  }
  else {
    Status = RegWriteVdm (R_SA_FMSS_VDM_MAIL_BOX_POWER_STATE_CONTROL, (Data | BIT31));
    ASSERT_EFI_ERROR (Status);
  }

  DEBUG ((DEBUG_INFO, "2LM: VDM write to PSC register 0x0014h is done! \n"));
  //
  // [Arch OPEN] 2. BIOS check RID for VDM & mailbox , fail then boot as 1LM (check value 0 for now, need to define how to implement)
  //

  //
  // 3.  Send VDM admin command write (identify) to check device status
  //
  //
  // Issue Identify device command and Query region command to find 2LM region
  //
  GetTwoLmModuleInfo (TwoLmInfoHob);
  DEBUG ((DEBUG_INFO, "2LM: DeviceProvisioningStatus %d\n", TwoLmInfoHob->TwoLmInfo.DeviceProvisioningStatus));
  DEBUG ((DEBUG_INFO, "2LM: TotalNumberofRegions %d\n", TwoLmInfoHob->TwoLmInfo.TotalNumberofRegions));

  if (!TwoLmInfoHob->TwoLmInfo.DeviceProvisioningStatus) {
    DEBUG ((DEBUG_INFO, "2LM: Updating 2LM policy to Provisioning \n"));
    TwoLmPreMemConfig->MemBootMode = MEM_BOOT_MODE_PROVISIONING;
    TwoLmInfoHob->TwoLmInfo.CurrentMemBootMode = MEM_BOOT_MODE_PROVISIONING;
    //Reseting Astro Reg to 0
    AstroInit (&TwoLmInfoHob->TwoLmInfo);
    return EFI_UNSUPPORTED;
  }

  GetQueryRegionInfo (TwoLmInfoHob);

  DEBUG ((DEBUG_INFO, "2LM: FarMemSize %d MB\n", TwoLmInfoHob->TwoLmInfo.FarMemSize));
  TwoLmPreMemConfig->FarMemorySize =  TwoLmInfoHob->TwoLmInfo.FarMemSize;
  if (!TwoLmInfoHob->TwoLmInfo.FarMemSize) {
    DEBUG ((DEBUG_INFO, "2LM: Far mem size is 0, boot mode will fall back to 1LM \n"));
    return EFI_UNSUPPORTED;
  }

  DEBUG ((DEBUG_INFO, "2LM: PMemSize %d MB\n", TwoLmInfoHob->TwoLmInfo.PMemSize));
  TwoLmPreMemConfig->PMemSize =  TwoLmInfoHob->TwoLmInfo.PMemSize;

  TwoLmInfoHob->TwoLmInfo.PMemBase = LShiftU64(TwoLmInfoHob->TwoLmInfo.FarMemSize, 20); // In bytes
  DEBUG ((DEBUG_INFO, "2LM: PMemBase %lx\n", TwoLmInfoHob->TwoLmInfo.PMemBase));

  //
  // 4. VDM admin command write set log page -> HW Parameters
  //
  if(BootMode != BOOT_ON_S3_RESUME) {
    Status = SetHardwareParameters (
             TwoLmPreMemConfig
             );
    ASSERT_EFI_ERROR (Status);
  }

  //
  // 5.  VDM read device Tpoweron supported and compare with SOC program with max value to VDM Tpoweron value register
  //  a.  Read VDM 2LM L1.2 Tpoweron Support register (offset 30h)
  //  b.  Compare with SOC Tpoweron values
  //  c.  Write VDM 2LM L1,2 Tpoweron Control register (offset 34h)
  //  d.  write the max value to host as well
  Status = RegReadVdm (R_SA_FMSS_VDM_MAIL_BOX_TPOWER_ON_SUPPORT, &Data);
  ASSERT_EFI_ERROR (Status);

  DevScalePm4 =  Data & (B_T_POWER_ON_SCALE_PM4_MASK << B_T_POWER_ON_SCALE_PM4_OFFSET);
  DevScalePm5 =  Data & (B_T_POWER_ON_SCALE_PM5_MASK << B_T_POWER_ON_SCALE_PM5_OFFSET);

  DevValuePm4 =  Data & (B_T_POWER_ON_VALUE_PM4_MASK << B_T_POWER_ON_VALUE_PM4_OFFSET);
  DevValuePm5 =  Data & (B_T_POWER_ON_VALUE_PM5_MASK << B_T_POWER_ON_VALUE_PM5_OFFSET);

  SocBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_PEG3_DEV_NUM, 0, 0);
  SocL1PmCapabilityOffset = PcieFindExtendedCapId (SA_SEG_NUM, SA_MC_BUS, SA_2LM_DEV_NUM, SA_2LM_FUN0_NUM, L1PM_CAPID);
  SocData = PegPciSegmentRead32 (SocBaseAddress + SocL1PmCapabilityOffset + R_L1PM_SUBSTATES_CAPABILITIES_REGISTER);
  SocScale = SocData & (B_PORT_T_POWER_ON_SCALE_MASK << B_PORT_T_POWER_ON_SCALE_OFFSET);
  SocValue = SocData & (B_PORT_T_POWER_ON_VALUE_MASK << B_PORT_T_POWER_ON_VALUE_OFFSET);

  // PM4
  if (((SocScale + 1) * SocValue) > ((DevScalePm4 + 1) * DevValuePm4)) { // program with the soc settings
    Data |= (SocScale << B_T_POWER_ON_SCALE_PM4_OFFSET) | (SocValue << B_T_POWER_ON_VALUE_PM4_OFFSET);
  } else { // program dev with the dev settings
    Data |= (DevScalePm4 << B_T_POWER_ON_SCALE_PM4_OFFSET) | (DevValuePm4 << B_T_POWER_ON_VALUE_PM4_OFFSET);
  }
  // PM5
  if (((SocScale + 1) * SocValue) > ((DevScalePm5 + 1) * DevValuePm5)) { // program with the soc settings
    Data |= (SocScale << B_T_POWER_ON_SCALE_PM5_OFFSET) | (SocValue << B_T_POWER_ON_VALUE_PM5_OFFSET);
  } else { // program dev with the dev settings
    Data |= (DevScalePm5 << B_T_POWER_ON_SCALE_PM5_OFFSET) | (DevValuePm5 << B_T_POWER_ON_VALUE_PM5_OFFSET);
  }

  Status = RegWriteVdm (R_SA_FMSS_VDM_MAIL_BOX_TPOWER_ON_CONTROL, Data);
  ASSERT_EFI_ERROR (Status);

  // write the max value to host as well
  if (((DevScalePm5 + 1) * DevValuePm5) > ((DevScalePm4 + 1) * DevValuePm4)) { // program with the soc settings
    SocData |= (DevScalePm5 << B_PORT_T_POWER_ON_SCALE_OFFSET) | (DevValuePm5 << B_PORT_T_POWER_ON_VALUE_OFFSET);
  } else { // program dev with the dev settings
    SocData |= (DevScalePm4 << B_PORT_T_POWER_ON_SCALE_OFFSET) | (DevValuePm4 << B_PORT_T_POWER_ON_VALUE_OFFSET);
  }
  PegPciSegmentWrite32 (SocBaseAddress + SocL1PmCapabilityOffset + R_L1PM_SUBSTATES_CAPABILITIES_REGISTER, SocData);

  // 6.  BIOS issues Clear region FIS command if needed- will be implemented as part of FZM
  //  a.  Required if Identify FIS command shows there is a provisioned Volatile Memory region
  //  b.  Required for S4/S5 cases.
  //



  // 8.  VDM write to FMSS Power Management Mode register (offset 10h)
  //  a.  Set FMPMMEN bit to 1 (enable 2LM Power Management Mode)
  //  b.  Allow customer optional to set NVMe_hold_disable bit (default to 0)
  //
  Status = RegReadVdm (R_SA_FMSS_VDM_MAIL_BOX_FMPMM, &Data);
  ASSERT_EFI_ERROR (Status);
  Data |= B_SA_FMSS_VDM_MAIL_BOX_FMPMM_FMPMMEN;
  Data |= TwoLmPreMemConfig->NVMeHoldDisableBit &  B_SA_FMSS_VDM_MAIL_BOX_NVME_HOLD_DISABLE;
  Status = RegWriteVdm (R_SA_FMSS_VDM_MAIL_BOX_FMPMM, Data);
  ASSERT_EFI_ERROR (Status);

  return Status;
}


/**
This function initializes 2LM specific config registers of 2LM Device PCIe Function 0 and Function 7.

@param[in]      TwoLmConfig            2LM Config block.

@retval         EFI_SUCCESS            Successfully initialized 3DXP Device's PCIe Controller.
@retval         EFI_NOT_FOUND          Error condition when the RP is not enabled or the capability is not found.
**/
STATIC
EFI_STATUS
EFIAPI
WillardPcieDeviceInit (
  IN TWOLM_PREMEM_CONFIG  *TwoLmPreMemConfig
)
{
  UINT32            DeviceBaseAddress;
  UINT32            SocBaseAddress;
  UINT32            Data32Or;
  UINT16            Data16Or;
  UINT16            Data16And;
  UINT16            MfvcCapabilityOffset;
  UINT16            EndPortAspm;
  UINT8             DevPcieCapabilityOffset;
  UINT8             SocPcieCapabilityOffset;
  UINT16            SocL1PmCapabilityOffset;
  UINT16            DevL1PmCapabilityOffset;
  UINT8             Mps;
  UINT32            SocValue;
  UINT32            SocScale;
  UINT32            DevValue;
  UINT32            DevScale;
  UINT8             i;
  UINT8             j;

  DEBUG ((DEBUG_INFO, "2LM: WillardPcieDeviceInit Initialization Start\n"));

  // Get the Soc base address for Pcie North Port (Peg60)
  SocBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_PEG3_DEV_NUM, 0, 0);
  if (PegPciSegmentRead16 (SocBaseAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    DEBUG ((DEBUG_INFO, "2LM: Rp 0/6/0 is not enabled\n"));
    return EFI_NOT_FOUND;
  }

  //
  // Following configurations are required for Fun7
  //
  DEBUG ((DEBUG_INFO, "2LM: Programming Fun7 Configurations\n"));
  DeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_PEG_BUS_NUM, SA_2LM_DEV_NUM, SA_2LM_FUN7_NUM, 0);
  if (PegPciSegmentRead16 (DeviceBaseAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    DEBUG ((DEBUG_INFO, "2LM: No 2LM device found on 0/3/7 \n"));
    return EFI_NOT_FOUND;
  }

  //
  // Fun7: Program Base Address Register (10h to 14h):BAR[63:56]=80h BAR[55:0] = 00000000000000h
  // note: just configuring the 64bit Bar register here, there won't be any 64bit mmio access in PEI phase.
  //

  PegPciSegmentAnd32 (DeviceBaseAddress + PCI_BASE_ADDRESSREG_OFFSET, 0);
  PegPciSegmentOr32 (DeviceBaseAddress + PCI_BASE_ADDRESSREG_OFFSET + 0x4, BIT31);


  //
  // Fun7: Program MSE and SERRE to 1 in command register
  //
  Data32Or = (UINT32)(EFI_PCI_COMMAND_SERR + EFI_PCI_COMMAND_MEMORY_SPACE);
  PegPciSegmentOr32 (DeviceBaseAddress + PCI_COMMAND_OFFSET, Data32Or);

  DevPcieCapabilityOffset  = PegPcieFindCapId (SA_SEG_NUM, SA_PEG_BUS_NUM, SA_2LM_DEV_NUM, SA_2LM_FUN7_NUM, PCIE_CAPID);
  DEBUG ((DEBUG_INFO, "2LM: Fun7: Device Capabilities offset: Pcie = %x \n", DevPcieCapabilityOffset));

  SocPcieCapabilityOffset  = PegPcieFindCapId (SA_SEG_NUM, SA_MC_BUS, SA_PEG3_DEV_NUM, 0, PCIE_CAPID);
  DEBUG ((DEBUG_INFO, "2LM: Fun7: Soc Capabilities offset: Pcie = %x \n", SocPcieCapabilityOffset));

  if ( DevPcieCapabilityOffset && SocPcieCapabilityOffset ) {
    //
    // Fun7: Device Control Register (08h):

    // Max_payload_size: Read MPS support from both SOC and Device and program the common min to PF7 (expected must be 512B = 010b)

    SocValue = PegPciSegmentRead32 (SocBaseAddress + SocPcieCapabilityOffset + R_DEVICE_CAPABILITIES_REGISTER) & 0x7;
    DevValue = PegPciSegmentRead32 (DeviceBaseAddress + DevPcieCapabilityOffset + R_DEVICE_CAPABILITIES_REGISTER)& 0x7;
    Mps = (UINT8)(SocValue < DevValue ? SocValue : DevValue); // x < y ? x:y;
     if ( Mps < 0x2) {
       DEBUG ((DEBUG_INFO, "2LM: Max Payload size is less than 512B\n"));
       ASSERT (FALSE);
       return EFI_NOT_FOUND;
     }
    // Correctable error reporting enable = 1b, Non fatal error reporting enable = 1b, Fatal error reporting enable = 1b
    // Unsupported request reporting enable = 1b, Relaxed Ordering Enable = 1
    //
    Data16Or = (UINT16)(Mps << B_MAX_PAYLOAD_SIZE_OFFSET) |
    (B_ENABLE_RELAXED_ORDERING + B_UNSUPPORTED_REQUEST_EN + B_FATAL_ERROR_EN + B_NON_FATAL_ERROR_EN + B_CORRECTABLE_ERROR_EN);
    PegPciSegmentOr16 (DeviceBaseAddress + DevPcieCapabilityOffset + R_DEVICE_CONTROL_REGISTER, Data16Or);

    //
    // Fun7: Link Control Register (10h): Enable ASPM (L0s & L1)
    // R_LINK_CAPABILITIES_REGISTER : Bit[11:10] Active State Power Management (ASPM) Support :
    // 00b No ASPM Support, 01b L0s Supported, 10b L1 Supported, 11b L0s and L1 Supported
    //
    EndPortAspm = 0;
    //
    // Select L1/L0 programming based on setup questions
    //
    switch (TwoLmPreMemConfig->Peg3Aspm) {
      case PcieAspmL1:
        EndPortAspm = L1_SET;
        break;
      case PcieAspmL0sL1:
      case PcieAspmAutoConfig:
        EndPortAspm = L1_SET | L0_SET;
        break;
      case PcieAspmL0s:
        EndPortAspm = L0_SET;
        break;
      case PcieAspmDisabled:
        default:
        break;
    }
    PegPciSegmentOr16 (DeviceBaseAddress + DevPcieCapabilityOffset + R_LINK_CONTROL_REGISTER, EndPortAspm);

    //
    // Fun7: Device Control 2 Register (28h): IDO Completion Enable = 1
    //
    Data16Or = (UINT16) (B_IDO_COMPLETION_EN);
    PegPciSegmentOr16 (DeviceBaseAddress + DevPcieCapabilityOffset + R_DEVICE_CONTROL2_REGISTER, Data16Or);
  }

  //
  // Following configurations are required for Fun0
  //
  DEBUG ((DEBUG_INFO, "2LM: Programming Fun0 Configurations\n"));

  DeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_PEG_BUS_NUM, SA_2LM_DEV_NUM, SA_2LM_FUN0_NUM, 0);
  DevPcieCapabilityOffset  = PcieFindCapId (SA_SEG_NUM, SA_PEG_BUS_NUM, SA_2LM_DEV_NUM, SA_2LM_FUN0_NUM, PCIE_CAPID);
  DEBUG ((DEBUG_INFO, "2LM: Fun0: Capabilities offset: Pcie = %x \n", DevPcieCapabilityOffset));

  if ( DevPcieCapabilityOffset ) {
    //
    // Fun0: Link Control Register (10h): Disable ASPM (L0s & L1)
    //
    Data16And = (UINT16) ( ~ (B_L1_ENTRY_ENABLED + B_L0_ENTRY_ENABLED));
    PegPciSegmentAnd16 (DeviceBaseAddress + DevPcieCapabilityOffset + R_LINK_CONTROL_REGISTER, Data16And);

    //
    // Fun0: Device Control 2 Register (28h): LTR Mechanism Enable = 1b
    //
    Data16Or = (UINT16) (B_LTR_MECHANISM_EN);
    PegPciSegmentOr16 (DeviceBaseAddress + DevPcieCapabilityOffset + R_DEVICE_CONTROL2_REGISTER, Data16Or);
  }

  // 5. Check the RC and PF0 PM substate capability, and program ASPM/PM L1.1 and L1.2 enabled
  // (based on support bit)(expected ASPM L1.2 enabled only)
  SocL1PmCapabilityOffset = PegPcieFindExtendedCapId (SA_SEG_NUM, SA_MC_BUS, SA_2LM_DEV_NUM, SA_2LM_FUN0_NUM, L1PM_CAPID);
  DevL1PmCapabilityOffset = PegPcieFindExtendedCapId (SA_SEG_NUM, SA_MC_BUS, SA_PEG3_DEV_NUM, SA_2LM_FUN0_NUM, L1PM_CAPID);

  if (SocL1PmCapabilityOffset && DevL1PmCapabilityOffset) {
    SocValue = PegPciSegmentRead32 (SocBaseAddress + SocL1PmCapabilityOffset + R_L1PM_SUBSTATES_CAPABILITIES_REGISTER)
                & (0x3 << B_ASPM_L1_2_SUPPORTED_OFFSET);
    DevValue = PegPciSegmentRead32 (DeviceBaseAddress + DevL1PmCapabilityOffset + R_L1PM_SUBSTATES_CAPABILITIES_REGISTER)
                & (0x3 << B_ASPM_L1_2_SUPPORTED_OFFSET);
    // write the common value
    Data16Or = (UINT16) ((SocValue & DevValue) << B_ASPM_L1_2_SUPPORTED_OFFSET);
    // Check if ASPM L1.2 is enabled as expected
    if (!(Data16Or & (0x1 << B_ASPM_L1_2_SUPPORTED_OFFSET))) {
      DEBUG ((DEBUG_INFO, "2LM: ASPM L1.2 is not enabled\n"));
      ASSERT (FALSE);
      return EFI_NOT_FOUND;
    }
    PegPciSegmentOr16 (DeviceBaseAddress + DevL1PmCapabilityOffset + R_L1PM_SUBSTATES_CONTROL_1_REGISTER, Data16Or);

    // 6. Read PF0 Tpoweron supported for both SOC and device, program with max value to PF0
    // TPOS is (scale + 1) * value, calculate it for both SOC and Dev and then compare and program based on the max value

    SocScale = PegPciSegmentRead32 (SocBaseAddress + SocL1PmCapabilityOffset + R_L1PM_SUBSTATES_CAPABILITIES_REGISTER)
                & (B_PORT_T_POWER_ON_SCALE_MASK << B_PORT_T_POWER_ON_SCALE_OFFSET);
    DevScale = PegPciSegmentRead32 (DeviceBaseAddress + DevL1PmCapabilityOffset + R_L1PM_SUBSTATES_CAPABILITIES_REGISTER)
                & (B_PORT_T_POWER_ON_SCALE_MASK << B_PORT_T_POWER_ON_SCALE_OFFSET);

    SocValue = PegPciSegmentRead32 (SocBaseAddress + SocL1PmCapabilityOffset + R_L1PM_SUBSTATES_CAPABILITIES_REGISTER)
                  & (B_PORT_T_POWER_ON_VALUE_MASK << B_PORT_T_POWER_ON_VALUE_OFFSET);
    DevValue = PegPciSegmentRead32 (DeviceBaseAddress + DevL1PmCapabilityOffset + R_L1PM_SUBSTATES_CAPABILITIES_REGISTER)
                  & (B_PORT_T_POWER_ON_VALUE_MASK << B_PORT_T_POWER_ON_VALUE_OFFSET);

    if (((SocScale+1) * SocValue) > ((DevScale+1) * DevValue)) {
      // program dev with the Soc settings
      Data32Or = (SocScale << B_PORT_T_POWER_ON_SCALE_CONTROL_OFFSET) | (SocValue << B_PORT_T_POWER_ON_VALUE_CONTROL_OFFSET);
    } else { // program dev with the dev settings
      Data32Or = (DevScale << B_PORT_T_POWER_ON_SCALE_CONTROL_OFFSET) | (DevValue << B_PORT_T_POWER_ON_VALUE_CONTROL_OFFSET);
    }
    // program Dev PF0
    PegPciSegmentOr32 (DeviceBaseAddress + DevL1PmCapabilityOffset + R_L1PM_SUBSTATES_CONTROL_2_REGISTER, Data32Or);
  }
  //
  // Following programming is required for the MFVC capability (Fun0)
  // The Extended Capability ID for the MFVC Capability is 0008h (as per PCIe spec v4)
  //
  MfvcCapabilityOffset  = PegPcieFindExtendedCapId (SA_SEG_NUM, SA_PEG_BUS_NUM, SA_2LM_DEV_NUM, SA_2LM_FUN0_NUM, MFVC_CAPID);

  DEBUG ((DEBUG_INFO, "2LM: Fun0: Capabilities offset: Mfvc = %x \n", MfvcCapabilityOffset));
  if ( MfvcCapabilityOffset ) {
    //7.  Provide capability to configure MFVC WRR arbitration table
    // i.  Write VC1 or VC0 to all 128 phases of these registers
    for (i = 0; i < MFVC_VC_ARB_TABLE_INDEX; ++i) {
      if (!TwoLmPreMemConfig->MfvcWrrArb) {
        Data32Or = 0x11111111;  // Default setting to VC1
      } else { // Get the user selection
        Data32Or = 0x0;
        DEBUG ((DEBUG_INFO, "2LM: TwoLmPreMemConfig->VcId_7_0[%d]=0x%x\n", i, TwoLmPreMemConfig->VcId_7_0[i]));
        for (j = 0; j < 8; ++j) {
          if (TwoLmPreMemConfig->VcId_7_0[i] & (0x1 << j)) {
            switch(j) {
              case 0:
                Data32Or |= (0x1 << B_VC_ID0_OFFSET);
                break;
              case 1:
                Data32Or |= (0x1 << B_VC_ID1_OFFSET);
                break;
              case 2:
                Data32Or |= (0x1 << B_VC_ID2_OFFSET);
                break;
              case 3:
                Data32Or |= (0x1 << B_VC_ID3_OFFSET);
                break;
              case 4:
                Data32Or |= (0x1 << B_VC_ID4_OFFSET);
                break;
              case 5:
                Data32Or |= (0x1 << B_VC_ID5_OFFSET);
                break;
              case 6:
                Data32Or |= (0x1 << B_VC_ID6_OFFSET);
                break;
              case 7:
                Data32Or |= (0x1 << B_VC_ID7_OFFSET);
                break;
            }
          }
        }
      }
      DEBUG ((DEBUG_INFO, "2LM: 128ph  Initialization Regoffset 0x%x Data = 0x%x \n", R_MFVC_VC_ARB_TABLE_0_REGISTER + i*4, Data32Or));
      PegPciSegmentOr32 (DeviceBaseAddress + MfvcCapabilityOffset + R_MFVC_VC_ARB_TABLE_0_REGISTER + i*4, Data32Or);
    }
    // ii. Write to MFVC Port VC Control and Status register (offset 0Ch) :
    //    1.  Set load_vc_arbitration_table (bit[0]) to 1
    //    2.  Set vc_arbitration_select (bit[3:1]) to 100b (128 phases)
    Data16Or = (VC_128PHASE_ARBITRATION << B_VC_ARBITRATION_SELECT_OFFSET) | B_LOAD_VC_ARBITRATION_TABLE;
    PegPciSegmentOr16 (DeviceBaseAddress + MfvcCapabilityOffset + R_PORT_VC_CONTROL_REGISTER, Data16Or);
    // iii.  Read the MFVC Port VC Control and Status register (offset 0Ch) to make sure bit[0] is clear
    // (This bit always returns 0b when read.)
    // This should be very fast compare to config write then read.
    // set max 3 times read if not 0 and declare failure and proceed
    for (i = 0; i < RETRY_COUNT; ++i) {
      if (PegPciSegmentRead16 (DeviceBaseAddress + MfvcCapabilityOffset + R_PORT_VC_STATUS_REGISTER) & 0x1) {
        if (i == 2) {
          DEBUG ((DEBUG_INFO, "2LM: Error in applying the arbitration table by HW \n"));
          ASSERT(FALSE);
        }
      }
      else {
        i = 3;
        DEBUG ((DEBUG_INFO, "2LM: Success in applying the arbitration table by HW \n"));
      }
    }

    //a.  Write to MFVC VC1 Resource Control Register (offset 20h-23h)
    // Enable VC1 in MFVC VC1_resource_ctrl[31:0] = 8000_0080h, (bit[31] is VC1 enable, bit[7] is TC7, the rest must be 0)
    PegPciSegmentWrite32 (DeviceBaseAddress + MfvcCapabilityOffset + R_VC1_RESOURCE_CONTROL_REGISTER, 0x81000080);

    //b.  Read  MFVC VC1 Resource Status Register (offset 24h-27) to confirm vc_negotiate_pending (bit[17]) is clear to 0 (wait for 1ms)
    MicroSecondDelay(1000);
    if ((PegPciSegmentRead32 (DeviceBaseAddress + MfvcCapabilityOffset + R_VC1_RESOURCE_STATUS_REGISTER) >> B_VC1_NEGOTIATION_PENDING_OFFSET) & 0x1) {
      DEBUG ((DEBUG_INFO, "2LM: Error in VC1 negotiation\n"));
      ASSERT(FALSE);
      return EFI_NOT_FOUND;
    }
  }

  DEBUG ((DEBUG_INFO, "2LM: WillardPcieDeviceInit Initialization End\n"));
  return EFI_SUCCESS;
}

/**
This function initializes 2LM specific configurations for the SOC Host PCIe RP controller.

@param[in]      TwoLmConfig            2LM Config block.

@retval         EFI_SUCCESS            Successfully initialized SOC Device's PCIe Controller.
**/
STATIC
EFI_STATUS
EFIAPI
HostPcieDeviceInit (
  IN TWOLM_PREMEM_CONFIG  *TwoLmPreMemConfig
)
{
  UINT32            DeviceBaseAddress;
  UINT32            Data32Or;
  UINT32            Data32And;
  UINT32            RootPortAspm;

  DEBUG ((DEBUG_INFO, "2LM: HostPcieDeviceInit Start\n"));

  DeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_PEG_BUS_NUM, SA_PEG3_DEV_NUM, SA_PEG3_FUN_NUM, 0);
  if (PegPciSegmentRead16 (DeviceBaseAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    DEBUG ((DEBUG_INFO, "2LM: RP controller is not enabled \n"));
    return EFI_NOT_FOUND;
  }

  //
  // Program BME and MSE in command register
  //
  Data32Or = (UINT32)(EFI_PCI_COMMAND_BUS_MASTER + EFI_PCI_COMMAND_MEMORY_SPACE);
  PegPciSegmentOr32 (DeviceBaseAddress + PCI_COMMAND_OFFSET, Data32Or);

  //
  // Program 0 to Primary, Secondary and Subordinate bus registers.
  //
  PegPciSegmentWrite16 (DeviceBaseAddress + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, 0);
  PegPciSegmentWrite8 (DeviceBaseAddress + PCI_BRIDGE_SUBORDINATE_BUS_REGISTER_OFFSET, 0);

  //
  // Program Memory Base and Limit register with value 0xFFF to Bits15:4 and 0 to Bits 31:20
  //
  Data32And = 0xF000F;
  Data32Or = 0xFFF0;
  PegPciSegmentAndThenOr32 (DeviceBaseAddress + R_PCI_BRIDGE_MBL, Data32And, Data32Or);

  //
  // Program Prefetchable Memory Base and Limit register with value 0xFFF to Bits15:4 and 0 to Bits 31:20
  //
  Data32And = 0xF000F;
  Data32Or = 0xFFF0;
  PegPciSegmentAndThenOr32 (DeviceBaseAddress + R_PCI_BRIDGE_PMBL, Data32And, Data32Or);

  //
  // Program all 1s Prefetchable Memory Base Upper and Limit Upper.
  //
  PegPciSegmentWrite32 (DeviceBaseAddress + R_PCI_BRIDGE_PMBU32, 0xFFFFFFFF);
  PegPciSegmentWrite32 (DeviceBaseAddress + R_PCI_BRIDGE_PMLU32, 0);

  //
  // Enable ASPM Optionality Compliance, ASPM L0 and L1 Capabilities
  //
  Data32Or = B_PCIE_LCAP_ASPMOC + B_PCIE_LCAP_APMS_L1 + B_PCIE_LCAP_APMS_L0S;
  PegPciSegmentOr32 (DeviceBaseAddress + R_PCIE_LCAP, Data32Or);

  RootPortAspm = 0;
  ///
  /// Select L1/L0 programming based on setup questions
  ///
  switch (TwoLmPreMemConfig->Peg3Aspm) {
    case PcieAspmL1:
      RootPortAspm = L1_SET;
      break;
    case PcieAspmL0sL1:
    case PcieAspmAutoConfig:
      RootPortAspm = L1_SET | L0_SET;
      break;
    case PcieAspmL0s:
      RootPortAspm = L0_SET;
      break;
    case PcieAspmDisabled:
    default:
      break;
  }
  PegPciSegmentOr32 (DeviceBaseAddress + R_PCIE_LCTL, RootPortAspm);

  //
  // Enable 10-Bit Tag Completer Support capabilities
  //
  Data32Or = B_PCIE_DCAP2_PX10BTCS;
  PegPciSegmentOr32 (DeviceBaseAddress + R_PCIE_DCAP2, Data32Or);

  //
  // Initialize L0s Periodic Flow Control Update Frequency
  //
  Data32Or = 3 << B_PCIE_CONTROL1_L0SPFCUF_OFFSET;
  PegPciSegmentOr32 (DeviceBaseAddress + R_PCIE_CONTROL1, Data32Or);

  //
  // Initialize Transaction Layer Advance Control and Status register.
  //
  Data32And = (UINT32)~(B_PCIE_TLADVCTLST_VC0TXARBGC_MASK + B_PCIE_TLADVCTLST_VC0REQPUTARBGC_MASK);
  Data32Or = (7 << B_PCIE_TLADVCTLST_VC1TXARBGC_OFFSET) + (7 << B_PCIE_TLADVCTLST_VC1REQPUTARBGC_OFFSET);
  PegPciSegmentAndThenOr32 (DeviceBaseAddress + R_PCIE_TLADVCTLST, Data32And, Data32Or);

  //
  // Initialize Far Memory Mode Control and Status register
  //
  Data32And = (UINT32)(~B_PCIE_FMMCTLST_FMMPS_MASK);
  Data32Or = 2 << B_PCIE_FMMCTLST_FMMPS_OFFSET;
  PegPciSegmentAndThenOr32 (DeviceBaseAddress + R_PCIE_FMMCTLST, Data32And, Data32Or);

  //
  // Initialize VC1 link
  //
  // Todo. Below code has to be revisited once it is added as part of PEG code.
  PegPciSegmentWrite32 (DeviceBaseAddress + 0x280, 0x10009);
  PegPciSegmentWrite32 (DeviceBaseAddress + 0x294, 0x8000007f);
  PegPciSegmentWrite32 (DeviceBaseAddress + 0x2a0, 0x81000080);
  PegPciSegmentOr32    (DeviceBaseAddress + 0x284, 0x1);    //Bits[2:0] BIOS to prog 0x1 for VC support config

  DEBUG ((DEBUG_INFO, "Reading VC1 register 0x2a0 from host 0x%x\n", PegPciSegmentRead32 (DeviceBaseAddress + 0x2a0)));
  DEBUG ((DEBUG_INFO, "Reading VC1 Capability Register 1 0x284 from host 0x%x\n", PegPciSegmentRead32 (DeviceBaseAddress + 0x284)));

  return EFI_SUCCESS;
}

/**
  Function to modify EPOC bit to support 1LM/2LM mode switching
  Changing EPOC bit will trigger System-Reboot
**/
VOID
ModifyEpoc2lmBit (
  VOID
  )
{
  TWOLM_EPOC_SET TwoLmEpocValue;

  DEBUG ((DEBUG_INFO, "Inside ModifyEpoc2lmBit\n"));

  TwoLmEpocValue.Uint32 = PmcGetCpuEpoc ();
  if (TwoLmEpocValue.Bits.TwoLm) {
    TwoLmEpocValue.Bits.TwoLm = 0; // Set the EPOC bit to 1LM
  } else {
    TwoLmEpocValue.Bits.TwoLm = 1; // Set the EPOC bit to 2LM
  }
  PmcSetCpuEpoc (TwoLmEpocValue.Uint32);
  //
  //RESET is Required since the EPOC value has changed
  //
  DEBUG ((DEBUG_INFO, "EPOC is set to : 0x%x Triggering EarlyPowerOnConfig Reset\n", TwoLmEpocValue.Uint32));
  (*GetPeiServicesTablePointer ())->ResetSystem2 (EfiResetCold, EFI_SUCCESS, 0, NULL);
}

/**
  Function to check the possibility of booting in 2LM mode based on multiple parameters

  @param[in] MemBootMode           - Boot Mode Setup option for 2LM

  @retval UINT8                    - return Boot policy based on the boot mode decision
**/
UINT8
Detect2Lm (
  IN UINT8        MemBootMode
  )
{
  UINT16          DevId;
  UINT8           Dev;
  UINT8           Func;
  UINT8           HeaderType;
  UINT8           MaxFunction;
  UINT32          DeviceBaseAddress;
  TWOLM_EPOC_SET  TwoLmEpocValue;
  UINT32          PcieBusNum  = 0x00010100;

  DEBUG ((DEBUG_INFO, "2LM: Inside Detect2Lm\n"));
  TwoLmEpocValue.Uint32 = PmcGetCpuEpoc ();

  // Enable the config space for Dev3, Func0 and Func7 (enabling it irrespective of the status to avoid the if condition check)
  PegPciSegmentOr32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM,SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_DEVEN), (UINT32) B_SA_DEVEN_D3F0EN_MASK);
  PegPciSegmentOr32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM,SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_DEVEN), (UINT32) B_SA_DEVEN_D3F7EN_MASK);

  //
  // Step1: check CAPID and Setup option for 2LM, reset EPOC bit if required
  // @todo: Add check for 2LM CAPID
  //
  if (MemBootMode == MEM_BOOT_MODE_1LM){

    if (TwoLmEpocValue.Bits.TwoLm) {
      ModifyEpoc2lmBit ();
    }
    return MEM_BOOT_MODE_1LM;
  }
  //
  // Step2: At this stage, check the possibility to boot in 2LM mode based on the 2LM device discovery
  // @todo take care of provisioning mode
  //

  //
  // Step3: BootMode:2LM, EPOC = ? check if the EPOC bit is supporting 2LM mode
  //
  if (!TwoLmEpocValue.Bits.TwoLm) {
    DeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_PEG3_DEV_NUM, 0, 0);
    if (PegPciSegmentRead16 (DeviceBaseAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
      DEBUG ((DEBUG_INFO, "2LM: RP 0/6/0 is not enabled\n"));
      return MEM_BOOT_MODE_1LM;
    }
    //
    // Enumerate and check if any of the devices connected to 0/6/0 is 2LM device
    // VID= 0x8086 and DID = 0x41C0 to 0x41CF
    //
    PegPciSegmentWrite32 (DeviceBaseAddress + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, PcieBusNum); // Assigning temp Bus
    for (Dev = 0; Dev <= 31; ++Dev) {
      //
      // Read Vendor ID to check if device exists
      // if no device exists, then check next device
      //
      DeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, 1, Dev, 0, 0);
      if (PegPciSegmentRead16 (DeviceBaseAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
        continue;
      }
      //
      // Check for a multifunction device
      //
      HeaderType = PegPciSegmentRead8 (DeviceBaseAddress + PCI_HEADER_TYPE_OFFSET);
      if ((HeaderType & HEADER_TYPE_MULTI_FUNCTION) != 0) {
        MaxFunction = 7;
      } else {
        MaxFunction = 0;
      }
      for (Func = 0; Func <= MaxFunction; ++Func) {
        DeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, 1, Dev, Func, 0);
        if (PegPciSegmentRead16 (DeviceBaseAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
          continue;
        } else if (PegPciSegmentRead16 (DeviceBaseAddress + PCI_VENDOR_ID_OFFSET) == 0x8086) {
          DevId = (PegPciSegmentRead16 (DeviceBaseAddress + PCI_DEVICE_ID_OFFSET));
          if ( DevId >> 4 == 0x41C ) {
            DEBUG ((DEBUG_INFO, "2LM: Device detected on Peg port is 2LM device\n"));
            ModifyEpoc2lmBit ();
          }
        }
      }
    }// End of this phase, BootMode:2LM, EPOC = 1LM, Device = 1LM/No device
    DEBUG ((DEBUG_INFO, "2LM: No 2LM Device detected on PEG port\n"));
    //
    // Need to clear the assigned temporary bus no
    //
    DeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_PEG3_DEV_NUM, 0, 0);
    PegPciSegmentWrite32 (DeviceBaseAddress + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, 0);
    return MEM_BOOT_MODE_1LM;
  }

  //
  // M_CREDITS_CONFIG_DONE bits in FMHC has to be set before first cfg access to 2LM device and VDM register access.
  //
  CpuRegbarOr32 (CPU_SB_PID_FMHC, R_FMHC_CCRDC, B_FMHC_CCRDC_M_CREDITS_CONFIG_DONE);
  CpuRegbarOr32 (CPU_SB_PID_FMHC, R_FMHC_HBIFCREDIT_VC1, B_FMHC_HBIFCREDIT_VC1_M_CREDITS_CONFIG_DONE);

  //
  // Step4: BootMode:2LM, EPOC = 2LM, Device = ?
  // Check if FMHC is enabled
  //
  DEBUG ((DEBUG_INFO, "2LM: Detect 2LM device in Bus 0 Dev3 Fun 0 "));
  DeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_DEV, TWOLM_DEVICE_NUM, 0, 0);
  if (PegPciSegmentRead16 (DeviceBaseAddress + PCI_VENDOR_ID_OFFSET) != 0xFFFF) {
    DEBUG ((DEBUG_INFO, "Vendor ID =  %x\n", PegPciSegmentRead16 (DeviceBaseAddress + PCI_VENDOR_ID_OFFSET)));
    //
    // FMHC is enabled, do the device discovery for 0/3/Y and check for 2LM device
    // Check for a multifunction device
    //
    HeaderType = PegPciSegmentRead8 (DeviceBaseAddress + PCI_HEADER_TYPE_OFFSET);
    if ((HeaderType & HEADER_TYPE_MULTI_FUNCTION) != 0) {
      MaxFunction = 7;
    } else {
      MaxFunction = 0;
    }
    for (Func = 0; Func <= MaxFunction; ++Func) {
      DeviceBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_DEV, TWOLM_DEVICE_NUM, Func, 0);
      if (PegPciSegmentRead16 (DeviceBaseAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
        continue;
      } else if (PegPciSegmentRead16 (DeviceBaseAddress + PCI_VENDOR_ID_OFFSET) == 0x8086) {
        DevId = (PegPciSegmentRead16 (DeviceBaseAddress + PCI_DEVICE_ID_OFFSET));
        if ( DevId >> 4 == 0x41C ) {
          // At this stage => Setup:2LM, EPOC = 2LM, Device = 2LM, Update boot policy to 2LM
          DEBUG ((DEBUG_INFO, "2LM: Device detected on 0/3/%d is 2LM device, Boot the system in 2LM mode\n", Func));
          return MEM_BOOT_MODE_2LM;
        }
      }
    }
  }
  DEBUG ((DEBUG_INFO, "2LM: No 2LM device found\n"));
  ModifyEpoc2lmBit ();
  return MEM_BOOT_MODE_2LM;
}

/**
This function performs any early configuration of 2LM if needed.

**/
VOID
EFIAPI
TwoLmEarlyConfig (
  )
{
  UINT32            Data32;
//  CPU_FAMILY        CpuFamilyId;

  Data32 = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MC_CAPID0_B));
  if (Data32 & BIT14) {
    Data32 = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_DEVEN));

    //
    // Hide RP controller Bus 0 Dev 6 Fun 0 if it is a 2LM enabled boot.
    //
    Data32 &= ~B_SA_DEVEN_D6EN_MASK;
    PciSegmentWrite32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_DEVEN), Data32);
    DEBUG ((DEBUG_INFO, "Host PCIe Dev6 hidden\n"));
  } else {
    Data32 = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_DEVEN));
    //
    // Hide Bus 0 Dev 3 Fun 0/7 in case if it is enabled
    //
    Data32 &= ~B_SA_DEVEN_D3F0EN_MASK & ~B_SA_DEVEN_D3F7EN_MASK;
    PciSegmentWrite32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_DEVEN), Data32);
    DEBUG ((DEBUG_INFO, "Host PCIe Dev3 func 0 and func7 hidden\n"));
  }
  Data32 = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_DEVEN));
  DEBUG ((DEBUG_INFO, "DevEn 0x%x\n", Data32));

  //Todo: below code has been added temporarily to enable 2LM and 1LM NVME boot in official BIOS.
  // Once it has been implemented in SA driver, below four lines of code can be removed.
//  CpuFamilyId = GetCpuFamily ();
//  if (CpuFamilyId == CPUID_FULL_FAMILY_MODEL_ICELAKE_DT_HALO_R) {
    PegPciSegmentWrite32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_PEG_BUS_NUM, SA_PEG3_DEV_NUM, SA_PEG3_FUN_NUM, 0xD0), 0x00000077);
    PegPciSegmentWrite32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_PEG_BUS_NUM, SA_PEG3_DEV_NUM, SA_PEG3_FUN_NUM, 0xF0), 0x00000770);
    PegPciSegmentWrite32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_PEG_BUS_NUM, SA_PEG3_DEV_NUM, SA_PEG3_FUN_NUM, 0x6CC), 0);
    PegPciSegmentWrite32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_PEG_BUS_NUM, SA_PEG3_DEV_NUM, SA_PEG3_FUN_NUM, 0x594), 0x1E40F);
  }
//}

/**
This function does the basic configurations of IPs and issues the Mailbox commands
to find out the Far Memory region and its size which would be used by the MRC phase
in creating the memory map.

@param[in]      TwoLmConfig              2LM Config block.

@retval EFI_SUCCESS            Successfully initialized Pre-Mem configurations.
@retval EFI_UNSUPPORTED        in case if all the requirements to support 2LM boot mode are not met.
**/

EFI_STATUS
EFIAPI
TwoLmPreMemInit (
   IN TWOLM_PREMEM_CONFIG      *TwoLmPreMemConfig
)
{
  EFI_STATUS                   Status;
  TWOLM_INFO_HOB               *TwoLmInfoHob;

  DEBUG ((DEBUG_INFO, "2LM: TwoLmPreMemInit Start\n"));

  //
  // Create HOB for 2LM INFO
  //
  Status = PeiServicesCreateHob (
             EFI_HOB_TYPE_GUID_EXTENSION,
             sizeof (TWOLM_INFO_HOB),
             (VOID **) &TwoLmInfoHob
             );
  ASSERT_EFI_ERROR (Status);

  //
  // Initialize default HOB data
  //
  TwoLmInfoHob->EfiHobGuidType.Name = gTwoLmInfoHobGuid;
  DEBUG ((DEBUG_INFO, "TwoLmInfoHob->EfiHobGuidType.Name: %g\n", &TwoLmInfoHob->EfiHobGuidType.Name));
  ZeroMem (&(TwoLmInfoHob->TwoLmInfo), sizeof (TWOLM_INFO));

  if (Detect2Lm (TwoLmPreMemConfig->MemBootMode) == MEM_BOOT_MODE_1LM) {
    TwoLmPreMemConfig->MemBootMode = MEM_BOOT_MODE_1LM;
    TwoLmInfoHob->TwoLmInfo.CurrentMemBootMode = MEM_BOOT_MODE_1LM;
    return EFI_UNSUPPORTED;
  }


  // Initialize Hob with the current policy and EPOC value
  TwoLmInfoHob->TwoLmInfo.CurrentMemBootMode = TwoLmPreMemConfig->MemBootMode;
  TwoLmInfoHob->TwoLmInfo.EpocBitValue = 1;

  //
  // Initialize Host PCIe controller
  //
  Status = HostPcieDeviceInit (TwoLmPreMemConfig);
  if (Status != EFI_SUCCESS) {
      TwoLmInfoHob->TwoLmInfo.CurrentMemBootMode = MEM_BOOT_MODE_1LM;
      return EFI_UNSUPPORTED;
  }

  //
  // Initialize 2LM device PCIe controller
  //
  Status = WillardPcieDeviceInit (TwoLmPreMemConfig);
  if (Status != EFI_SUCCESS) {
      TwoLmInfoHob->TwoLmInfo.CurrentMemBootMode = MEM_BOOT_MODE_1LM;
      return EFI_UNSUPPORTED;
  }
  //
  // Initialize Willard device for Power management and 2LM enable.
  //
  Status = WillardInit (
            TwoLmPreMemConfig
           ,TwoLmInfoHob
          );
  if (Status != EFI_SUCCESS) {
      TwoLmInfoHob->TwoLmInfo.CurrentMemBootMode = MEM_BOOT_MODE_1LM;
      return EFI_UNSUPPORTED;
  }

  DEBUG ((DEBUG_INFO, "2LM: TwoLmPreMemInit End\n"));
  return EFI_SUCCESS;
}

/**
  Perform Far Memory Encryption initialization.

  @retval VOID - No value to return
**/
VOID
FmeInit (
  )
{
  UINT64            FmeCapability;
  UINT64            FmeActivate;
  EFI_BOOT_MODE     BootMode;
  EFI_STATUS        Status;

  FmeActivate   = 0;

  DEBUG ((DEBUG_INFO, "2LM: Far Memory Encryption (FME) Initialization\n"));

  //
  // Read MSR_PLATFORM_INFO BIT58 to check if Far Memory Encryption feature is supported.
  //
  FmeCapability = AsmReadMsr64 (MSR_PLATFORM_INFO);

  if (FmeCapability & B_MSR_PLATFORM_INFO_SXP_2LM_ENABLE_MASK) {

    //
    // Set Fme enable - BIT[1]
    //
    FmeActivate |= B_FME_ACTIVATE_FME_ENABLE;

    //
    // Set FME Key Select for various boot modes.
    // Key Select - BIT[2]
    //   - Set for S3 resume and flash update flow to restore FME keys from previous boot.
    //   - Clear for cold/warm boot to create new FME keys
    //
    Status = PeiServicesGetBootMode (&BootMode);
    ASSERT_EFI_ERROR (Status);

    if ((BootMode == BOOT_ON_S3_RESUME) || (BootMode == BOOT_ON_FLASH_UPDATE)) {
      FmeActivate |= B_FME_ACTIVATE_KEY_SELECT;
    } else {
      FmeActivate &= (UINT64)~B_FME_ACTIVATE_KEY_SELECT;
    }

    //
    // Save key for standby - BIT[3]
    //
    FmeActivate |= B_FME_ACTIVATE_SAVE_KEY;

    //
    // Lock FME Activate MSR - BIT[0]
    //
    FmeActivate |= B_FME_ACTIVATE_FME_LOCK;

    //
    // Configure IA32_FME_ACTIVATE MSR (81H) with FME Enable, Key Select, Save Key
    //
    DEBUG ((DEBUG_INFO, "Initialize MSR_IA32_FME_ACTIVATE: %x\n", FmeActivate));
    AsmWriteMsr64 (MSR_IA32_FME_ACTIVATE, FmeActivate);
  } else {
    DEBUG ((DEBUG_INFO, "Far Memory Encryption is not supported\n"));
  }
}

/**
This function does the basic configurations of Astro controller
This function will be called only if the 2LM mode is enabled in the policy.

@param[in]      NearMemorySize           Near memory size detected in MRC.
@param[in]      ToludBase                ToludBase value from MRC.
@param[in]      RemapBase                RemapBase value from MRC.
@param[in]      RemapLimit               RemapLimit value from MRC.
@param[in]      MemBootMode              Mem boot mode value as a result of detected near mem size

@retval EFI_SUCCESS            Successfully initialized Post-Mem configurations.
**/
EFI_STATUS
EFIAPI
TwoLmPostDdrInit (
  IN UINT32 NearMemorySize,
  IN UINT32 ToludBase,
  IN UINT32 RemapBase,
  IN UINT32 RemapLimit,
  IN UINT8 MemBootMode
  )
{
  EFI_STATUS                    Status;
  TWOLM_INFO_HOB                *TwoLmInfoHob;
  TWOLM_PREMEM_CONFIG           *TwoLmPreMemConfig;
  SI_PREMEM_POLICY_PPI          *SiPreMemPolicyPpi;

  ///
  /// Get policy settings through the SaInitConfigBlock PPI
  ///
  Status = PeiServicesLocatePpi(
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **)&SiPreMemPolicyPpi
  );
  ASSERT_EFI_ERROR(Status);
  if ((Status != EFI_SUCCESS) || (SiPreMemPolicyPpi == NULL)) {
    return EFI_NOT_FOUND;
  }

  Status = GetConfigBlock((VOID *)SiPreMemPolicyPpi, &gTwoLmPreMemConfigGuid, (VOID *)&TwoLmPreMemConfig);
  ASSERT_EFI_ERROR(Status);


  DEBUG ((DEBUG_INFO, "2LM: TwoLmPostDdrInit start\n"));

  TwoLmInfoHob = (TWOLM_INFO_HOB *) GetFirstGuidHob (&gTwoLmInfoHobGuid);
  if (TwoLmInfoHob == NULL) {
    return EFI_UNSUPPORTED;
  }

  if (MemBootMode != MEM_BOOT_MODE_2LM) {
    // updating policy and Hob info based on the near mem detection
    TwoLmPreMemConfig->MemBootMode = MemBootMode;
    TwoLmInfoHob->TwoLmInfo.CurrentMemBootMode = MemBootMode;
    DEBUG ((DEBUG_INFO, "2LM: updating policy and Hob info to %d\n", MemBootMode));
    return EFI_UNSUPPORTED;
  }

  // Update Hob with inputs from MRC
  TwoLmInfoHob->TwoLmInfo.NearMemSize = NearMemorySize;
  TwoLmInfoHob->TwoLmInfo.ToludBase = ToludBase;
  TwoLmInfoHob->TwoLmInfo.RemapBase = RemapBase;
  TwoLmInfoHob->TwoLmInfo.RemapLimit = RemapLimit;
  DEBUG ((DEBUG_INFO, "2LM: Inputs from MRC: NearMemSize is %d  ToludBase is %d  RemapBase is %d  RemapLimit is %d\n",
          NearMemorySize, ToludBase, RemapBase, RemapLimit));
  //
  // Initialize the Far Memory Host Controller
  //
  Status = FmhcInit (
            &TwoLmInfoHob->TwoLmInfo
            ,TwoLmPreMemConfig
           );
  if (Status != EFI_SUCCESS) {
    // updating policy and Hob info to 1LM
    TwoLmPreMemConfig->MemBootMode = MEM_BOOT_MODE_1LM;
    TwoLmInfoHob->TwoLmInfo.CurrentMemBootMode = MEM_BOOT_MODE_1LM;
    DEBUG ((DEBUG_INFO, "2LM: Fmhc Initialization failure, updating policy and Hob info to 1LM\n"));
    return EFI_UNSUPPORTED;
  }

  //
  // Initialize the Astro Controller
  //
  Status = AstroInit (&TwoLmInfoHob->TwoLmInfo);
  if (Status != EFI_SUCCESS) {
    // updating policy and Hob info to 1LM
    TwoLmPreMemConfig->MemBootMode = MEM_BOOT_MODE_1LM;
    TwoLmInfoHob->TwoLmInfo.CurrentMemBootMode = MEM_BOOT_MODE_1LM;
    DEBUG ((DEBUG_INFO, "2LM: Astro Initialization failure, updating policy and Hob info to 1LM\n"));
    return EFI_UNSUPPORTED;
  }

  //
  // Initialize Far Memory Encrytion feature
  //
  FmeInit ();

  DEBUG ((DEBUG_INFO, "2LM: DdrSize %d MB\n",TwoLmInfoHob->TwoLmInfo.NearMemSize));
  DEBUG ((DEBUG_INFO, "2LM: TwoLmPostDdrInit End\n"));
  return EFI_SUCCESS;
}


/**
This function hanldes all post mem activities for 2LM feature.

@retval EFI_SUCCESS      Successfully initialized Post-Mem configurations.
**/
EFI_STATUS
EFIAPI
TwoLmPostMemInit (
  )
{
  TWOLM_INFO_HOB         *TwoLmInfoHob;
  UINT64                 McD0BaseAddress;
  UINT32                 DevEn;

  DEBUG ((DEBUG_INFO, "2LM: TwoLmPostMemInit start\n"));
  TwoLmInfoHob = (TWOLM_INFO_HOB *)GetFirstGuidHob (&gTwoLmInfoHobGuid);
  if (TwoLmInfoHob == NULL) {
    return EFI_UNSUPPORTED;
  }

  McD0BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, 0);
  DevEn = PegPciSegmentRead32 (McD0BaseAddress + R_SA_DEVEN);

  //
  // Hide NVME function Bus 0 Dev 3 Fun 0, if there is no storage available
  //
  if (TwoLmInfoHob->TwoLmInfo.StorageSize == 0) {
    DevEn &= ~B_SA_DEVEN_D3F0EN_MASK;
  }

  //
  // Hide 2LM PCIe function Bus 0 Dev 3 Fun 7
  //
  DevEn &= ~B_SA_DEVEN_D3F7EN_MASK;

  //
  // Hide RP controller Bus 0 Dev 6 Fun 0
  //
  DevEn &= ~B_SA_DEVEN_D6EN_MASK;

  PegPciSegmentWrite32 (McD0BaseAddress + R_SA_DEVEN, DevEn);

  return EFI_SUCCESS;
}
