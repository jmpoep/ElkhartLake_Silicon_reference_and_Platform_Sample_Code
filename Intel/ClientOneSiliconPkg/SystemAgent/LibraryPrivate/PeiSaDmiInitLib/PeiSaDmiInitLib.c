/** @file
  SA Dmi PEI Initialization library

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

@par Specification Reference:
**/
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PeiServicesLib.h>
#include <CpuRegs.h>
#include <Library/SaPlatformLib.h>
#include <Library/CpuPlatformLib.h>
#include <Library/PchPcrLib.h>
#include <Library/SaDmiInitLib.h>
#include <Library/SaPcieInitLib.h>
#include <Library/PeiPchDmiLib.h>
#include <ConfigBlock/SiConfig.h>
#include <Register/PchDmiRegs.h>
#include <Register/PchDmi15Regs.h>
#include <Register/PchPcrRegs.h>
#include <CpuPcieInfo.h>
#include <Register/SaRegsHostBridge.h>
typedef union {
  struct {
    UINT32  Low;
    UINT32  High;
  } Data32;
  UINT64 Data;
} UINT64_STRUCT;
///
/// Functions
///


/**
  Initialize DMI Tc/Vc mapping through SA-PCH.

  @param[in] PCIE_PEI_PREMEM_CONFIG          PCIe config block from SA Policy PPI

  @retval EFI_SUCCESS
**/
EFI_STATUS
SaDmiTcVcInit (
#if FixedPcdGetBool(PcdCpuPcieEnable) == 1
  IN       PCIE_PEI_PREMEM_CONFIG                  *PciePeiPreMemConfig
#endif
  )
{
  EFI_STATUS                  Status;
  UINT64                      McD0BaseAddress;
  UINT64_STRUCT               DmiBar;
  PCH_DMI_TC_VC_MAP           PchDmiTcVcMap;
  CPU_FAMILY                  CpuFamilyId;

#if FixedPcdGetBool(PcdCpuPcieEnable) == 1
#endif

  McD0BaseAddress    = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, 0);
  DmiBar.Data32.High = PciSegmentRead32 (McD0BaseAddress + R_SA_DMIBAR + 4);
  DmiBar.Data32.Low  =  PciSegmentRead32 (McD0BaseAddress + R_SA_DMIBAR);
  DmiBar.Data       &= (UINT64) ~BIT0;
  CpuFamilyId        = GetCpuFamily ();

  ///
  /// SA OPI Initialization
  ///
  if (!IsPchLinkDmi (CpuFamilyId)) {
    MmioOr8 ((UINTN) (DmiBar.Data + 0xA78), BIT1);
  }

  ///
  /// Get default PchDmiTcVcMap
  ///
  ZeroMem (&PchDmiTcVcMap, sizeof (PCH_DMI_TC_VC_MAP));
  PchDmiTcVcMapInit (&PchDmiTcVcMap);

  ///
  /// Program NB TC/VC mapping
  ///
  SaSetDmiTcVcMapping (&PchDmiTcVcMap, DmiBar.Data);
  ///
  /// Call PchDmiTcVcProgPoll
  ///
  Status = PchDmiTcVcProgPoll (&PchDmiTcVcMap);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Poll NB negotiation completion
  ///
  Status = SaPollDmiVcStatus (&PchDmiTcVcMap, DmiBar.Data);
  ASSERT_EFI_ERROR (Status);
  return EFI_SUCCESS;

}

/**
  Map SA DMI TCs to VC

  @param[in] PchDmiTcVcMap        - Instance of PCH_DMI_TC_VC_MAP
  @param[in] DmiBar               - DMIBAR address

  @retval EFI_SUCCESS             -  Succeed.
  @retval EFI_INVALID_PARAMETER   -  Wrong phase parameter passed in.
**/
EFI_STATUS
SaSetDmiTcVcMapping (
  IN    PCH_DMI_TC_VC_MAP   *PchDmiTcVcMap,
  IN    UINT64              DmiBar
  )
{
  UINT32  Data32And;
  UINT32  Data32Or;
  UINT8   Index;
  UINT16  Register;
  UINT8   VcId;
  UINT8   VcMap[PchDmiVcTypeMax];

  ZeroMem (VcMap, PchDmiVcTypeMax);
  ///
  /// Set the TC/VC mappings
  ///
  for (Index = 0; Index < PchDmiTcTypeMax; Index++) {
    VcMap[PchDmiTcVcMap->DmiTc[Index].Vc] |= (BIT0 << Index);
  }
  ///
  /// System BIOS must perform the following steps for VC0 configuration.
  ///   Program the TCs/VC0 map by setting DMIBAR offset 014h [7:1] = '0111 101b'.
  ///
  /// Virtual Channel for ME (VCm) Configuration
  /// This is configured by ConfigMemMe
  ///
  /// Step1. Assign Virtual Channel ID 7 to VCm:
  ///    Programming the DMIVCMRCTL DMI Port Register DMIBAR Offset 038h[26:24] = '111b'.
  ///
  /// Step2. Enable VCm:
  ///    Programming the DMIVMPRCTL DMI Port Register DMIBAR Offset 038h[31] = '1b'.
  ///
  /// Step3. Enable VCm by programming the DMIVCMRCTL DMI Port Register DMIBAR Offset 038h[31] = '1b'.
  ///
  for (Index = 0; Index < PchDmiVcTypeMax; Index++) {
    if (PchDmiTcVcMap->DmiVc[Index].Enable == TRUE) {
      ///
      /// Map TCs to VC, Set the VC ID, Enable VC
      ///
      VcId = PchDmiTcVcMap->DmiVc[Index].VcId;

      Data32And = (UINT32) (~(V_SA_DMIBAR_DMIVCCTL_ID | B_SA_DMIBAR_DMIVCCTL_TVM_MASK));
      Data32Or = VcId << N_SA_DMIBAR_DMIVCCTL_ID;
      Data32Or |= (UINT32) VcMap[Index];
      Data32Or |= N_SA_DMIBAR_DMIVCCTL_EN;

      switch (Index) {
        case PchDmiVcTypeVc0:
          Register = R_SA_DMIBAR_DMIVC0RCTL_OFFSET;
          break;

        case PchDmiVcTypeVc1:
          Register = R_SA_DMIBAR_DMIVC1RCTL_OFFSET;
          break;

        case PchDmiVcTypeVcm:
          Register = R_SA_DMIBAR_DMIVCMRCTL_OFFSET;
          break;

        default:
          return EFI_INVALID_PARAMETER;
      }

      MmioAndThenOr32 ((UINTN) (DmiBar + Register), Data32And, Data32Or);
    }
  }
  return EFI_SUCCESS;
}

/**
  Poll SA DMI negotiation completion

  @param[in] PchDmiTcVcMap        - Instance of PCH_DMI_TC_VC_MAP
  @param[in] DmiBar               - DMIBAR address

  @retval EFI_SUCCESS             -  Succeed.
  @retval EFI_INVALID_PARAMETER   -  Wrong phase parameter passed in.
**/
EFI_STATUS
SaPollDmiVcStatus (
  IN    PCH_DMI_TC_VC_MAP   *PchDmiTcVcMap,
  IN    UINT64              DmiBar
  )
{
  UINT8   Index;
  UINT16  Register;

  ///
  /// 6.2.3.2 - Step 4, Poll until VC1 has been negotiated
  ///    Read the DMIVC1RSTS DMI Port Register Offset 026h until [1]==0
  ///
  /// 6.2.3.4 - Step4. Poll the VCm Negotiation Pending bit until it reads 0:
  ///    Read the DMIVCMRSTS DMI Port Register Offset 03Eh until [1]==0
  ///
  for (Index = 0; Index < PchDmiVcTypeMax; Index++) {
    if (PchDmiTcVcMap->DmiVc[Index].Enable == TRUE) {
      switch (Index) {
        case PchDmiVcTypeVc0:
          Register = R_SA_DMIBAR_DMIVC0RSTS_OFFSET;
          break;

        case PchDmiVcTypeVc1:
          Register = R_SA_DMIBAR_DMIVC1RSTS_OFFSET;
          break;

        case PchDmiVcTypeVcm:
          Register = R_SA_DMIBAR_DMIVCMRSTS_OFFSET;
          break;

        default:
          return EFI_INVALID_PARAMETER;
      }

      ///
      /// Wait for negotiation to complete
      ///
      while ((MmioRead16 ((UINTN) (DmiBar + Register)) & B_SA_DMIBAR_DMISTS_NP) != 0);
    }
  }

  return EFI_SUCCESS;
}

/**
  Programs static equalization phase 1 settings for DMI

  @param[in]  DmiBar                      - Current value for DMIBAR
  @param[in]  DmiGen3RootPortPreset       - RP Presets array, length must be == SA_DMI_MAX_LANE == 8
  @param[in]  DmiGen3EndPointPreset       - EP Presets array, length must be == SA_DMI_MAX_LANE == 8
  @param[in]  DmiGen3EndPointHint         - EP Hints array, length must be == SA_DMI_MAX_LANE == 8
**/
VOID
EFIAPI
DmiProgramGen3EqPhase1 (
  IN  UINT64                            DmiBar,
  IN  UINT8                             *DmiGen3RootPortPresets,
  IN  UINT8                             *DmiGen3EndPointPresets,
  IN  UINT8                             *DmiGen3EndPointHints
  )
{
  UINT32        OrData;
  UINT8         BundleIndex;
  UINT8         LaneIndex;

  DEBUG ((DEBUG_INFO, "Programming DMI Gen3 Eq Phase1\n"));

  ///
  /// Do bounds checking on input
  ///
  for (LaneIndex = 0; LaneIndex < SA_DMI_MAX_LANE; LaneIndex++) {
    if (DmiGen3RootPortPresets[LaneIndex] > 9) {
      DmiGen3RootPortPresets[LaneIndex] = 4;
    }
    if (DmiGen3EndPointPresets[LaneIndex] > 9) {
      DmiGen3EndPointPresets[LaneIndex] = 7;
    }
    if (DmiGen3EndPointHints[LaneIndex] > 6) {
      DmiGen3EndPointHints[LaneIndex] = 2;
    }
  }


  for (BundleIndex = 0; BundleIndex < GetMaxDmiBundles(); BundleIndex++) {
    ///
    /// Compute data to program
    ///
    OrData  = (UINT32) (DmiGen3EndPointPresets[BundleIndex << 1] << 8);
    OrData |= (UINT32) (DmiGen3EndPointHints[BundleIndex << 1] << 12);
    OrData |= (UINT32) (DmiGen3EndPointPresets[ (BundleIndex << 1) + 1] << 24);
    OrData |= (UINT32) (DmiGen3EndPointHints[ (BundleIndex << 1) + 1] << 28);
    OrData |= (UINT32) (DmiGen3RootPortPresets[BundleIndex << 1]);
    OrData |= (UINT32) (DmiGen3RootPortPresets[ (BundleIndex << 1) + 1] << 16);

    ///
    /// Program Eq Settings
    ///
    MmioAndThenOr32 ((UINTN) (DmiBar + R_SA_PEG_EQCTL0_1_OFFSET + (BundleIndex << 2)), 0x80F080F0, OrData);
  }
}

/**
  Invert the lane if LaneReversal bit is set based on DMI X4 width

  @param[in]  Lane                - Lane to potentially invert
  @param[in]  LaneReversal        - LaneReversal bit

  @retval     Lane number compensated for LaneReversal
**/
UINT8
DmiReverseLane (
  IN  UINT8 Lane,
  IN  UINT8 LaneReversal
  )
{
  if (LaneReversal != 0) {
    return (GetMaxDmiLanes() - Lane - 1);
  } else {
    return Lane;
  }
}

/**
  Get Full Swing value for EndPoint Transmitter

  @param[in]  DmiBar                      - Current value for DMIBAR
  @param[in]  Lane                        - Physical Lane Number
  @param[out] FullSwing                   - Full Swing value
**/
VOID
EFIAPI
DmiGetLinkPartnerFullSwing (
  IN  UINTN                             DmiBar,
  IN  UINT8                             Lane,
  OUT UINT8                             *FullSwing
  )
{
  UINT32  Data32;

  if (Lane > (GetMaxDmiLanes() - 1)) {
    ASSERT (Lane <= (GetMaxDmiLanes() - 1));
    Lane = 0;
  }

  Data32 = BIT25 | BIT23 | (Lane << 19) | BIT18;
  MmioWrite32 (DmiBar + R_SA_PEG_EQPH3_OFFSET, Data32);
  Data32 = MmioRead32 (DmiBar + R_SA_PEG_EQPH3_OFFSET);
  MmioWrite32 (DmiBar + R_SA_PEG_EQPH3_OFFSET, 0);

  *FullSwing = (Data32 >> 6) & 0x3F;

  return;
}

/**
  Sets the Phase 3 Hijack Equalization Coefficients

  @param[in]  DmiBar                      - Current value for DMIBAR
  @param[in]  Lane                        - Physical Lane Number
  @param[in]  PreCursor                   - Computed Pre-Cursor
  @param[in]  Cursor                      - Computed Cursor
  @param[in]  PostCursor                  - Computed Post-Cursor
**/
VOID
EFIAPI
DmiSetPartnerTxCoefficients (
  IN  UINTN                             DmiBar,
  IN  UINT8                             Lane,
  IN  UINT8                             *PreCursor,
  IN  UINT8                             *Cursor,
  IN  UINT8                             *PostCursor
  )
{
  UINT32  Data32;

  if (Lane > GetMaxDmiLanes()) {
    ASSERT (Lane <= GetMaxDmiLanes());
    return;
  }
  if ((*Cursor) > 63) {
    ASSERT ((*Cursor) <= 63);
    return;
  }
  if ((*PreCursor) > 63) {
    ASSERT ((*PreCursor) <= 63);
    return;
  }
  if ((*PostCursor) > 63) {
    ASSERT ((*PostCursor) <= 63);
    return;
  }

  Data32 = (Lane << 19) | BIT18 | (*Cursor << 12) | (*PreCursor << 6) | (*PostCursor);
  MmioWrite32 (DmiBar + R_SA_PEG_EQPH3_OFFSET, Data32);
  MmioWrite32 (DmiBar + R_SA_PEG_EQPH3_OFFSET, 0);

  return;
}

/**
  Wait until link is up.

  @param[in]  DmiBar                      - Current value for DMIBAR
  @param[in]  MaxDmiSpeed                 - Max DMI Link Speed

  @retval EFI_SUCCESS     - Completed successfully before timeout
  @retval EFI_TIMEOUT     - Timed out
**/
EFI_STATUS
EFIAPI
DmiWaitForL0 (
  IN  UINTN                             DmiBar,
  IN  UINT8                             MaxDmiSpeed
  )
{
  UINT32        Index;
  EFI_STATUS    Status;
  BOOLEAN       CheckEq;
  BOOLEAN       CompletedEq;
  UINT32        EqStatus;
  UINT32        LinkStatus;

  Status         = EFI_TIMEOUT;
  CheckEq        = (MaxDmiSpeed >= 0x3) ? TRUE : FALSE;
  CompletedEq    = FALSE;
  Index          = 0;

  ///
  /// If endpoint's LCAP.MLS (Spec section 7.8.6) indicated Gen3 capability, first wait for equalization to complete.
  /// Check equalization status LSTS2.EC (Spec section 7.8.20) until Gen3 equalization successfully completed.
  ///
  if (CheckEq) {
    for (; Index < 100; Index++) {
      EqStatus = MmioRead16 (DmiBar + R_SA_DMIBAR_LSTS2_OFFSET);
      EqStatus = (EqStatus >> 1) & 0x1;
      if (EqStatus == 0x1) {
        CompletedEq = TRUE;
        break;
      }
      MicroSecondDelay (STALL_ONE_MILLI_SECOND);
    }
  }

  ///
  /// Check for L0 status.
  /// Continue up to 100 msec of combined delay.
  /// Skip if equalization was needed but didn't successfully complete.
  ///
  if ((CheckEq && CompletedEq) || !CheckEq) {
    for (; Index < 100; Index++) {
      LinkStatus = MmioRead32 (DmiBar + R_SA_DMIBAR_DMISTS_OFFSET);
      LinkStatus = (LinkStatus >> 16) & 0xF;
      if (LinkStatus == 0x7) {
        Status = EFI_SUCCESS;
        break;
      }
      MicroSecondDelay (STALL_ONE_MILLI_SECOND);
    }
  }

  return Status;
}

/**
  Performs any additional equalization programming that needs to be done after
  initial link training and endpoint detection

  @param[in]  DmiBar                      - Current value for DMIBAR
  @param[in]  PciePeiPreMemConfig         - PCIe Configuration Block
  @param[in]  MaxDmiSpeed                 - Max DMI Link Speed
**/
VOID
EFIAPI
DmiPostDetectionEqProgramming (
  IN  UINTN                             DmiBar,
  IN  PCIE_PEI_PREMEM_CONFIG            *PciePeiPreMemConfig,
  IN  UINT8                             MaxDmiSpeed
  )
{
  BOOLEAN   Ph3Hijack;
  UINT8     LaneReversal;
  UINT8     FullSwing;
  UINT8     PreCursor;
  UINT8     Cursor;
  UINT8     PostCursor;
  UINT8     Lane;

  LaneReversal = (MmioRead32 (DmiBar + R_SA_DMIBAR_DMITST_OFFSET) >> 20) & 0x1;
  Ph3Hijack    = FALSE;
  FullSwing    = 0;

  ///
  ///
  if (PciePeiPreMemConfig->DmiGen3EqPh3Method == PH3_METHOD_STATIC ||
      PciePeiPreMemConfig->DmiGen3EqPh3Method == PH3_METHOD_SWEQ) {
    Ph3Hijack = TRUE;
    MmioOr32 (DmiBar + R_SA_PEG_EQCFG_OFFSET, BIT1);
  }

  ///
  /// If any Gen3 device, setup equalization values and retrain link
  ///
  if ((MaxDmiSpeed >= DMI_GEN3) && Ph3Hijack) {
    ///
    /// Program presets based upon endpoint fullswing value
    ///
    for (Lane = 0; Lane < SA_DMI_MAX_LANE; Lane++) {
      if (Lane == 0) {
        DmiGetLinkPartnerFullSwing (DmiBar, Lane, &FullSwing);
      }
      GetCoefficientsFromPreset (
        PciePeiPreMemConfig->DmiGen3EndPointPreset[DmiReverseLane (Lane, LaneReversal) ],
        FullSwing,
        &PreCursor,
        &Cursor,
        &PostCursor
        );
      DmiSetPartnerTxCoefficients (DmiBar, Lane, &PreCursor, &Cursor, &PostCursor);
    }

    ///
    /// Clear phase2 bypass
    ///
    MmioAnd32 (DmiBar + R_SA_PEG_EQCFG_OFFSET, (UINT32) ~(BIT15));

    ///
    /// Redo EQ
    ///
    MmioOr32 (DmiBar + R_SA_PEG_LCTL3_OFFSET, BIT0);    ///< DOEQ
  ///
  /// Retrain Link
  ///
    DmiLinkTrain (DmiBar);
    DmiWaitForL0 (DmiBar, MaxDmiSpeed);
  }
}

/**
 This function programs Equalization Phase 2/3 Bypass

  @param[in]  DmiBar                      - Current value for DMIBAR
  @param[in]  PciePeiPreMemConfig         - PCIe Configuration Block
**/
VOID
EFIAPI
DmiEqPh2Ph3BypassProgramming (
  IN  UINTN                             DmiBar,
  IN  PCIE_PEI_PREMEM_CONFIG            *PciePeiPreMemConfig
  )
{
  ///
  /// After last equalization, set PH3 bypass if needed
  ///
  if (PciePeiPreMemConfig->DmiGen3EqPh3Method == PH3_METHOD_SWEQ ||
      PciePeiPreMemConfig->DmiGen3EqPh3Method == PH3_METHOD_DISABLED) {
    MmioOr32 (DmiBar + R_SA_PEG_EQCFG_OFFSET, BIT14);
  }
  ///
  /// Set Ph2 Bypass if enabled by SA policy
  ///
  if (PciePeiPreMemConfig->DmiGen3EqPh2Enable == 0) {
    MmioOr32 (DmiBar + R_SA_PEG_EQCFG_OFFSET, BIT15);
  } else {
    MmioAnd32 (DmiBar + R_SA_PEG_EQCFG_OFFSET, (UINT32) ~(BIT15));
  }
}

/**
  Configure DMI Max Speed

  @param[in]  PciePeiPreMemConfig         - PCIe Configuration Block
  @param[in]  DmiBar                      - Current value for DMIBAR
**/
VOID
DmiConfigureMaxSpeed (
  IN  PCIE_PEI_PREMEM_CONFIG            *PciePeiPreMemConfig,
  IN  UINT64                            DmiBar
  )
{
  UINT16                       LinkStatus;
  UINT8                        DmiLcap;
  UINT8                        MaxDmiSpeed;
  UINT8                        ActualDmiSpeed;
  UINT32                       Data32And;
  UINT32                       Data32Or;
  ///
  /// Check to make sure Ph2 and Ph3 options are compatible
  ///
  if ((PciePeiPreMemConfig->DmiGen3EqPh2Enable == 0)                &&
      ((PciePeiPreMemConfig->DmiGen3EqPh3Method == PH3_METHOD_AUTO) ||
       (PciePeiPreMemConfig->DmiGen3EqPh3Method == PH3_METHOD_HWEQ))) {
    ///
    /// If Ph2 is disabled we can't enable Ph3
    ///
    PciePeiPreMemConfig->DmiGen3EqPh3Method = PH3_METHOD_DISABLED;
  }
  if (PciePeiPreMemConfig->DmiGen3EqPh3Method == PH3_METHOD_SWEQ) {
    DEBUG ((DEBUG_WARN, "SW EQ not supported on DMI, using Static EQ\n"));
    PciePeiPreMemConfig->DmiGen3EqPh3Method = PH3_METHOD_STATIC;
  }

  DmiLcap = PchPcrRead8 (PID_DMI, R_PCH_DMI_PCR_LCAP);
  if (((DmiLcap & (BIT0 | BIT1 | BIT2 | BIT3)) == 0x1) ||
      (PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MC_CAPID0_A_OFFSET)) & BIT22)) {
    DEBUG ((DEBUG_WARN, "DMI Gen2 is fused off, staying at Gen1!\n"));
    MaxDmiSpeed = DMI_GEN1;
  }
  else if (((DmiLcap & (BIT0 | BIT1 | BIT2 | BIT3)) <= 0x2) ||
           (PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MC_CAPID0_B)) & BIT15)) {
    DEBUG ((DEBUG_WARN, "DMI Gen3 is fused off, staying at Gen2!\n"));
    MaxDmiSpeed = DMI_GEN2;
  }
  else {
    MaxDmiSpeed = DMI_GEN3;
  }

  if ((PciePeiPreMemConfig->DmiMaxLinkSpeed != DMI_AUTO) &&
      (PciePeiPreMemConfig->DmiMaxLinkSpeed < MaxDmiSpeed)) {
    DEBUG ((DEBUG_INFO, "Limiting DMI speed to Gen%d based on SA Policy\n", PciePeiPreMemConfig->DmiMaxLinkSpeed));
    MaxDmiSpeed = (UINT8) PciePeiPreMemConfig->DmiMaxLinkSpeed;
  }

  ///
  /// Read/Write LCAP to make LCAP read only.
  ///
  MmioAndThenOr32 ((UINTN) (DmiBar + R_SA_DMIBAR_LCAP_OFFSET), (UINT32) 0xFFFFFFFF, (UINT32) 0);

  ///
  /// If we are going to Gen3, then perform Gen3 Equalization
  ///
  if (MaxDmiSpeed >= DMI_GEN3) {
    if (PciePeiPreMemConfig->DmiGen3ProgramStaticEq != 0) {
      DEBUG ((DEBUG_INFO, "Program DMI Gen3 Static Equalization...\n"));
      DmiProgramGen3EqPhase1 (
        DmiBar,
        &(PciePeiPreMemConfig->DmiGen3RootPortPreset[0]),
        &(PciePeiPreMemConfig->DmiGen3EndPointPreset[0]),
        &(PciePeiPreMemConfig->DmiGen3EndPointHint[0])
        );
    }
  }

  DEBUG ((DEBUG_INFO, "Programming DMI speed to Gen%d\n", MaxDmiSpeed));

  if (MaxDmiSpeed > DMI_GEN1) {
    ///
    /// Program PCH TLS
    ///
    PchDmiSetTargetLinkSpeed (MaxDmiSpeed);
    ///
    /// Set the requested speed in Target Link Speed in LCTL2[3:0].
    ///
    MmioAndThenOr16 ((UINTN) (DmiBar + R_SA_DMIBAR_LCTL2_OFFSET), (UINT16) ~0xF, MaxDmiSpeed);
  }

  ///
  /// Set Phase2 Bypass for first link train to Gen3
  ///
  if (MaxDmiSpeed >= DMI_GEN3) {
    MmioOr32 ((UINTN) (DmiBar + R_SA_PEG_EQCFG_OFFSET), BIT15);
  }

  ///
  /// Retrain link
  ///
  DmiLinkTrain (DmiBar);

  ///
  /// Retrain link if link speed is less than max speed
  ///
  if ((((MmioRead16 ((UINTN) (DmiBar + R_SA_DMIBAR_LSTS_OFFSET))) & 0x0F) < MaxDmiSpeed) ||
      ((PchPcrRead16 (PID_DMI, R_PCH_DMI15_PCR_LSTS) & 0x0F) < MaxDmiSpeed)) {
    DEBUG ((DEBUG_INFO, "Retraining DMI Link to reach Gen%d\n", MaxDmiSpeed));
    DmiLinkTrain (DmiBar);
  }

  ///
  /// Post initial Gen3 link training steps
  ///
  if (MaxDmiSpeed >= DMI_GEN3) {
    DmiPostDetectionEqProgramming ((UINTN) DmiBar, PciePeiPreMemConfig, MaxDmiSpeed);
    DmiEqPh2Ph3BypassProgramming ((UINTN) DmiBar, PciePeiPreMemConfig);
  }

  ///
  /// Get the current link status
  ///
  LinkStatus = MmioRead16 ((UINTN) (DmiBar + R_SA_DMIBAR_LSTS_OFFSET));
  ActualDmiSpeed = (UINT8) (LinkStatus & 0x0F);
  DEBUG ((DEBUG_INFO, "DMI trained to x%d at Gen%d\n", ((LinkStatus >> 4) & 0x3F), ActualDmiSpeed));

  ///
  /// Set DMI Offset 0xC28 [31:26]
  ///
  Data32And = (UINT32) ~(BIT31 | BIT30 | BIT29 | BIT28 | BIT27 | BIT26);
  if (ActualDmiSpeed >= DMI_GEN3) {
    Data32Or  = 0x10 << 26;
  } else if (ActualDmiSpeed == DMI_GEN2) {
    Data32Or  = 0x8 << 26;
  } else {
    Data32Or  = 0x4 << 26;
  }
  MmioAndThenOr32 ((UINTN) (DmiBar + R_SA_DMIBAR_AFE_PM_TMR_OFFSET), Data32And, Data32Or);
}

/**
  Configure DMI De-Emphasis

  @param[in]  DmiBar                      - Current value for DMIBAR
  @param[in]  DeEmphasisValue             - De-emphasis policy value
**/
VOID
DmiConfigureDeEmphasis (
  IN  UINT64                            DmiBar,
  IN  UINT8                             DeEmphasisValue
  )
{
  UINT32                  Data32And;
  UINT32                  Data32Or;

  ASSERT (DeEmphasisValue <= 0x1);

  ///
  /// Set LCTL2[6] SELECTABLEDEEMPHASIS according to the policy
  ///
  Data32And = (UINT32) ~(BIT6);
  Data32Or  = (UINT32) (DeEmphasisValue) << 6;
  MmioAndThenOr32 ((UINTN) (DmiBar + R_SA_DMIBAR_LCTL2_OFFSET), Data32And, Data32Or);
  DEBUG ((DEBUG_INFO, "DmiDeEmphasis set to x%d\n", DeEmphasisValue));
}

/**
  Initialize DMI.

  @param[in] PCIE_PEI_PREMEM_CONFIG          PCIe config block from SA Policy PPI

  @retval EFI_SUCCESS
**/
EFI_STATUS
DmiInit (
  IN       PCIE_PEI_PREMEM_CONFIG     *PciePeiPreMemConfig
  )
{
  UINT64                       McD0BaseAddress;
  UINT64_STRUCT                MchBar;
  UINT64_STRUCT                DmiBar;
  UINT32                       Data32And;
  UINT32                       Data32Or;
  UINT32                       Bundle;
  McD0BaseAddress    = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, 0);
  MchBar.Data32.High = PciSegmentRead32 (McD0BaseAddress + R_SA_MCHBAR + 4);
  MchBar.Data32.Low  = PciSegmentRead32 (McD0BaseAddress + R_SA_MCHBAR);
  MchBar.Data       &= (UINT64) ~BIT0;
  DmiBar.Data32.High = PciSegmentRead32 (McD0BaseAddress + R_SA_DMIBAR + 4);
  DmiBar.Data32.Low  = PciSegmentRead32 (McD0BaseAddress + R_SA_DMIBAR);
  DmiBar.Data       &= (UINT64) ~BIT0;

  ///
  ///
  ///
  /// DCBLNC = 0
  ///
  Data32And = (UINT32) ~(BIT3 | BIT2);
  Data32Or  = 0;
  for (Bundle = 0; Bundle < GetMaxDmiBundles(); Bundle++) {
    MmioAndThenOr32 ((UINTN)(DmiBar.Data + R_SA_PEG_G3CTL0_OFFSET + (Bundle * BUNDLE_STEP)), Data32And, Data32Or);
  }

  ///
  /// Perform DMI Recipe steps
  ///
  DEBUG ((DEBUG_INFO, "DMI Recipe...\n"));

  ///
  /// Configure DMI nFTS
  ///
  DmiConfigureNFts (
    DmiBar.Data
    );
  ///
  /// Program DMI de-emphasis value
  ///
  DmiConfigureDeEmphasis (
    DmiBar.Data,
    (UINT8) PciePeiPreMemConfig->DmiDeEmphasis
    );
  ///
  /// Program DMI Link Speed
  ///
  DmiConfigureMaxSpeed (
    PciePeiPreMemConfig,
    DmiBar.Data
    );
  return EFI_SUCCESS;
}

/**
  DMI link training

  @param[in] DmiBar - DMIBAR address
**/
VOID
DmiLinkTrain (
  IN  UINT64 DmiBar
  )
{
  ///
  /// Retrain link
  ///
  MmioOr8 ((UINTN) (DmiBar + R_SA_DMIBAR_LCTL_OFFSET), BIT5);
}

/**
  DMI Max Payload Size Init

  @param[in] PCIE_PEI_PREMEM_CONFIG          PCIe config block from SA Policy PPI
**/
VOID
MaxPayloadSizeInit (
  IN PCIE_PEI_PREMEM_CONFIG          *PciePeiPreMemConfig
  )
{
  UINT64_STRUCT DmiBar;
  UINT32        Data32;
  UINT32        Data32And;
  UINT32        Data32Or;
  UINT32        DmiMaxPayloadSizeCap;
  UINT64        McBaseAddress;
  //
  // Read R_SA_DMIBAR_DCAP_OFFSET register
  //
  McBaseAddress      = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, 0);
  DmiBar.Data32.High = PciSegmentRead32 (McBaseAddress + R_SA_DMIBAR + 4);
  DmiBar.Data32.Low  = PciSegmentRead32 (McBaseAddress + R_SA_DMIBAR);
  DmiBar.Data       &= (UINT64) ~BIT0;
  ASSERT (DmiBar.Data != 0);

  Data32 = MmioRead32 ((UINTN)(DmiBar.Data + R_SA_DMIBAR_DCAP_OFFSET));
  DmiMaxPayloadSizeCap = (UINT32) (Data32 & B_SA_DMIBAR_DCAP_OFFSET_LOCK);  // Apply this to extract Bit [2:0] only

  //
  //
  //
  // Write back after reading contents to ensure bit 0 of DMI DCAP register (RW_O) does not get over ridden
  //
  MmioWrite32 ((UINTN)(DmiBar.Data + R_SA_DMIBAR_DCAP_OFFSET), Data32);

  //
  // Checking if PCIE_TL_CR_DCAP_0_0_0_DMIBAR[2:0] is set to 1.
  // If yes, then DMI can be configured for MPS of 256B or 128B
  //
  if (DmiMaxPayloadSizeCap == 0x1) {
    ///
    /// Verified that DMI MPS is 256/128B configurable.
    /// For SKL setting,
    /// PCIE_TL_CR_DCTL_0_0_0_DMIBAR[7:5] = 1 ; 256B of MPS
    /// PCIE_TL_CR_DCTL_0_0_0_DMIBAR[7:5] = 0 ; 128B of MPS
    ///
    Data32And = (UINT32) B_SA_DMIBAR_DCTL_OFFSET_MASK;
    Data32Or  = (UINT32) (DmiMaxPayloadSizeCap  << 5);
    MmioAndThenOr32 ((UINTN)(DmiBar.Data + R_SA_DMIBAR_DCTL_OFFSET), Data32And, Data32Or);
  }
  return;
}

/**
  Set SB Min Duration
**/
VOID
SetSbMin (
  VOID
  )
{
  UINT64_STRUCT                DmiBar;
  UINT64                       McBaseAddress;

  McBaseAddress      = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, 0);
  DmiBar.Data32.High = PciSegmentRead32 (McBaseAddress + R_SA_DMIBAR + 4);
  DmiBar.Data32.Low  = PciSegmentRead32 (McBaseAddress + R_SA_DMIBAR);
  DmiBar.Data       &= (UINT64) ~BIT0;
  // Set SB Min
  MmioWrite32 ((UINTN)(DmiBar.Data + R_SA_DMIBAR_OPIO_T_SB_MIN), 0x14);
  DEBUG ((DEBUG_INFO, "Set OPIO SB Min 0x14\n"));
}

/**
  Configure DMI nFTS

  @param[in] DmiBar                 - DMIBAR address
**/
VOID DmiConfigureNFts (
  IN UINT64                    DmiBar
  )
{
  UINT32                       Data32And;
  UINT32                       Data32Or;
  ///
  /// Set L0SLAT[15:0] to 0x2020
  ///
  Data32And = (UINT32) ~(0xFFFF);
  Data32Or  = 0x2020;
  MmioAndThenOr32 ((UINTN) (DmiBar + R_SA_PEG_L0SLAT_OFFSET), Data32And, Data32Or);
  DEBUG ((DEBUG_INFO, "DMI nFTS 0x%x\n", Data32Or));
}


