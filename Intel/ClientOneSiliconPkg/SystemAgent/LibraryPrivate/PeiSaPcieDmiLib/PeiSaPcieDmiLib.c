/** @file
  SA PCIe/DMI PEI Initialization library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2018 Intel Corporation.

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
#include <SystemAgent/LibraryPrivate/PeiSaPcieInitLib/LowLevel/SaPegLowLevel.h>
#include <Library/SaPlatformLib.h>
#include <Library/PcieInitLib.h>
///
/// Functions
///

/**
  Programs the PCIe/DMI recipe.

  @param[in]  DmiBar                      - DMIBAR
  @param[in]  MchBar                      - MCHBAR
  @param[in]  Gen3CtlePeaking             - Array of CTLE Peaking values to program per bundle
  @param[in]  Gen3CtlePeakingLength       - Length of the Gen3CtlePeaking array
  @param[in]  Gen3RxCtleOverride          - RxCTLE override configuration
  @param[in]  ProgramDmiRecipe            - Set to TRUE to program DMI, FALSE to program PCIe
**/
VOID
EFIAPI
CnlPegDmiRecipe (
  IN  UINT64                            DmiBar,
  IN  UINT64                            MchBar,
  IN  UINT8                             *Gen3CtlePeaking,
  IN  UINT8                             Gen3CtlePeakingLength,
  IN  UINT8                             Gen3RxCtleOverride,
  IN  BOOLEAN                           ProgramDmiRecipe
  )
{
  UINT64            BaseAddress;
  UINT64            Peg0BaseAddress;
  UINT64            Peg3BaseAddress;
  UINTN             Index;
  UINTN             Count;
  UINTN             BundlesCount;
  UINTN             LanesCount;
  UINT32            Mask32And;
  UINT32            Data32Or;
  CPU_SKU           CpuSku;
  UINT32            CrOffset;
  CpuSku            = GetCpuSku ();

  BaseAddress     = 0;
  Peg0BaseAddress = 0;
  Peg3BaseAddress = 0;

  if (ProgramDmiRecipe) {
    ///
    /// DMI
    ///
    LanesCount  = GetMaxDmiLanes();

    //
    // BaseAddress will not be used in DMI recipe.
    //
    BaseAddress = (UINT64) 0xFFFFFFFF;
  } else {
    ///
    /// PEG
    ///
    LanesCount  = SA_PEG_MAX_LANE;
    Peg0BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_PEG_BUS_NUM, SA_PEG_DEV_NUM, SA_PEG0_FUN_NUM, 0);
    Peg3BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_PEG_BUS_NUM, SA_PEG3_DEV_NUM, SA_PEG3_FUN_NUM, 0);
  }

  BundlesCount = LanesCount >> 1;

  ///
  ///
  if (!ProgramDmiRecipe) {
    ///
    /// AFEBND0CFG1[21:16] PGACQ = 0xA (PEG)
    ///
    Mask32And = (UINT32) ~(BIT21 | BIT20 | BIT19 | BIT18 | BIT17 | BIT16 );
    Data32Or  = 0xA << 16;
    for (Index = 0; Index < SA_PEG0_CNT_MAX_BUNDLE; Index++) {  // PEG0
      PciSegmentAndThenOr32 (Peg0BaseAddress + R_SA_PEG_AFEBND0CFG1_OFFSET + (Index * BUNDLE_STEP), Mask32And, Data32Or);
    }
    for (Index = 0; Index < SA_PEG3_CNT_MAX_BUNDLE; Index++) {  // PEG3
      PciSegmentAndThenOr32 (Peg3BaseAddress + R_SA_PEG_AFEBND0CFG1_OFFSET + (Index * BUNDLE_STEP), Mask32And, Data32Or);
    }
  }
  ///
  ///
  if (ProgramDmiRecipe) {
    ///
    /// AFEBND0CFG2[23:23] G3BYPCOEFF = 0x0 (DMI)
    ///
    Mask32And = (UINT32) ~(BIT23);
    Data32Or  = 0x0 << 23;
  ///
    /// AFEBND0CFG2[21:15] TXEQPOSTCUR = 0xC (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT21 | BIT20 | BIT19 | BIT18 | BIT17 | BIT16 | BIT15);
    Data32Or  |= 0xC << 15;
  ///
    /// AFEBND0CFG2[14:8] TXEQPRECUR = 0x8 (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT14 | BIT13 | BIT12 | BIT11 | BIT10 | BIT9 | BIT8);
    Data32Or  |= 0x8 << 8;
    ///
    /// AFEBND0CFG2[7:1] TXEQCUR = 0x2A (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT7 | BIT6 | BIT5 | BIT4 | BIT3 | BIT2 | BIT1);
    Data32Or  |= 0x2A << 1;


    for (Index = 0; Index < BundlesCount; Index++) {
      MmioAndThenOr32 ((UINTN) (DmiBar + R_SA_PEG_AFEBND0CFG2_OFFSET + (Index * BUNDLE_STEP)), Mask32And, Data32Or);
    }
  } else {
    ///
    /// AFEBND0CFG2[7:1] TXEQCUR = 0x2A (PEG)
    ///
    Mask32And = (UINT32) ~(BIT7 | BIT6 | BIT5 | BIT4 | BIT3 | BIT2 | BIT1);
    Data32Or  = 0x2A << 1;
    ///
    /// AFEBND0CFG2[21:15] TXEQPOSTCUR = 0xC (PEG)
    ///
    Mask32And &= (UINT32) ~(BIT21 | BIT20 | BIT19 | BIT18 | BIT17 | BIT16 | BIT15);
    Data32Or  |= 0xC << 15;
    ///
    /// AFEBND0CFG2[14:8] TXEQPRECUR = 0x8 (PEG)
    ///
    Mask32And &= (UINT32) ~(BIT14 | BIT13 | BIT12 | BIT11 | BIT10 | BIT9 | BIT8);
    Data32Or  |= 0x8 << 8;
    for (Index = 0; Index < SA_PEG0_CNT_MAX_BUNDLE; Index++) {  // PEG0
      PciSegmentAndThenOr32 (Peg0BaseAddress + R_SA_PEG_AFEBND0CFG2_OFFSET + (Index * BUNDLE_STEP), Mask32And, Data32Or);
    }
    for (Index = 0; Index < SA_PEG3_CNT_MAX_BUNDLE; Index++) {  // PEG3
      PciSegmentAndThenOr32 (Peg3BaseAddress + R_SA_PEG_AFEBND0CFG2_OFFSET + (Index * BUNDLE_STEP), Mask32And, Data32Or);
    }
  }

  ///
  ///
  /// AFEBND0CFG3[24:21] RXRTBIN = 0x3 (PEG & DMI)
  ///
  Mask32And = (UINT32) ~(BIT24 | BIT23 | BIT22 | BIT21);
  Data32Or  = 0x3 << 21;
  ///
  /// AFEBND0CFG3[29:26] TXRTBIN = 0x4 (PEG & DMI)
  ///
  Mask32And &= (UINT32) ~(BIT29 | BIT28 | BIT27 | BIT26);
  Data32Or  |= 0x4 << 26;
  if (ProgramDmiRecipe) {
    for (Index = 0; Index < BundlesCount; Index++) {
      MmioAndThenOr32 ((UINTN) (DmiBar + R_SA_PEG_AFEBND0CFG3_OFFSET + (Index * BUNDLE_STEP)), Mask32And, Data32Or);
    }
  } else {
    ///
    /// AFEBND0CFG3[10:5] PGTRK = 0xA (PEG)
    ///
    Mask32And &= (UINT32) ~(BIT10 | BIT9 | BIT8 | BIT7 | BIT6 | BIT5);
    Data32Or  |= (0xA << 5);
    for (Index = 0; Index < SA_PEG0_CNT_MAX_BUNDLE; Index++) {  // PEG0
      PciSegmentAndThenOr32 (Peg0BaseAddress + R_SA_PEG_AFEBND0CFG3_OFFSET + (Index * BUNDLE_STEP), Mask32And, Data32Or);
    }
    for (Index = 0; Index < SA_PEG3_CNT_MAX_BUNDLE; Index++) {  // PEG3
      PciSegmentAndThenOr32 (Peg3BaseAddress + R_SA_PEG_AFEBND0CFG3_OFFSET + (Index * BUNDLE_STEP), Mask32And, Data32Or);
    }
  }

  ///
  ///
  /// AFEBND0CFG4[13:10] G2RXCTLEPEAK = 0x2 (PEG & DMI)
  ///
  Mask32And = (UINT32) ~(BIT13 | BIT12 | BIT11 | BIT10);
  Data32Or  = (0x2 << 10);
  if (ProgramDmiRecipe) {
    ///
    /// AFEBND0CFG4[9:6] G3RXCTLEPEAK = 0x0(DMI)
    ///
    Mask32And &= (UINT32) ~(BIT9 | BIT8 | BIT7 | BIT6);
    Data32Or  |= (0x0 << 6);
    ///
    /// AFEBND0CFG4[31:25] AFEBNDSPARE = 0x30(DMI)
    ///
    Mask32And &= (UINT32) ~(BIT31 | BIT30 | BIT29 | BIT28 | BIT27 | BIT26 | BIT25);
    Data32Or  |= (0x30 << 25);
    for (Index = 0; Index < BundlesCount; Index++) {
      MmioAndThenOr32 ((UINTN) (DmiBar + R_SA_PEG_AFEBND0CFG4_OFFSET + (Index * BUNDLE_STEP)), Mask32And, Data32Or);
    }
  } else {
    ///
    /// AFEBND0CFG4[31:25] AFEBNDSPARE = 48 or 0x30  (PEG)
    ///
    Mask32And &= (UINT32) ~(BIT31 | BIT30 | BIT29 | BIT28 | BIT27 | BIT26 |BIT25);
    Data32Or  |= (0x30 << 25);
    ///
    /// AFEBND0CFG4[9:6] G3RXCTLEPEAK = 0x0 [48dec] (PEG)
    ///
    Mask32And &= (UINT32) ~(BIT9 | BIT8 | BIT7 | BIT6);
    Data32Or  |= (0x0 << 6);
    for (Index = 0; Index < SA_PEG0_CNT_MAX_BUNDLE; Index++) {  // PEG0
      PciSegmentAndThenOr32 (Peg0BaseAddress + R_SA_PEG_AFEBND0CFG4_OFFSET + (Index * BUNDLE_STEP), Mask32And, Data32Or);
    }
    for (Index = 0; Index < SA_PEG3_CNT_MAX_BUNDLE; Index++) {  // PEG3
      PciSegmentAndThenOr32 (Peg3BaseAddress + R_SA_PEG_AFEBND0CFG4_OFFSET + (Index * BUNDLE_STEP), Mask32And, Data32Or);
    }
  }

  ///
  ///
  /// AFELN0CFG0[4:0] G23RXVREF = 0xA (Peg & DMI)
  ///
  Mask32And = (UINT32) ~(BIT4 | BIT3 | BIT2 | BIT1 | BIT0);
  Data32Or  = 0xA;
  if (ProgramDmiRecipe) {
    for (Index = 0; Index < LanesCount; Index++) {
      MmioAndThenOr32 ((UINTN) (DmiBar + R_SA_PEG_AFELN0CFG0_OFFSET + (Index * LANE_STEP)), Mask32And, Data32Or);
    }
  } else {
    for (Index = 0; Index < SA_PEG0_CNT_MAX_LANE; Index++) {  // PEG0
      PciSegmentAndThenOr32 (Peg0BaseAddress + R_SA_PEG_AFELN0CFG0_OFFSET + (Index * LANE_STEP), Mask32And, Data32Or);
    }
    for (Index = 0; Index < SA_PEG3_CNT_MAX_LANE; Index++) {  // PEG3
      PciSegmentAndThenOr32 (Peg3BaseAddress + R_SA_PEG_AFELN0CFG0_OFFSET + (Index * LANE_STEP), Mask32And, Data32Or);
    }
  }

  ///
  ///
  if (ProgramDmiRecipe) {
    ///
    /// AFELN0CFG1[8:4] G1RXVREFSEL = 0xC (DMI)
    ///
    Mask32And = (UINT32) ~(BIT8 | BIT7 | BIT6 | BIT5 | BIT4);
    Data32Or  = 0xC << 4;
    for (Index = 0; Index < LanesCount; Index++) {
      MmioAndThenOr32 ((UINTN) (DmiBar + R_SA_PEG_AFELN0CFG1_OFFSET + (Index * LANE_STEP)), Mask32And, Data32Or);
    }
  }

  ///
  ///
  /// CRI0_CR_DWORD22[22]    RESSEL_OVRD_EN = 0x1 (DMI, PEG)
  ///
  Mask32And = (UINT32) ~(BIT22);
  Data32Or  = 0x1 << 22;
  ///
  /// CRI0_CR_DWORD22[21:16] PI_RESSEL_OVRD = 0x10 (DMI, PEG)
  ///
  Mask32And &= (UINT32) ~(BIT21 | BIT20 | BIT19 | BIT18 | BIT17 | BIT16);
  Data32Or  |= 0x10 << 16;
  if (ProgramDmiRecipe) {
    for (Index = 0; Index < BundlesCount; Index++) {
      CrOffset  = ((R_SA_PEG_BND10_CRI0_CR_DWORD22_OFFSET << 8)|((Index*2) << 16));
      PcodeMailboxReadThenWrite(CrOffset, Mask32And, Data32Or, DMI_PORT);
    }
  } else {
    for (Index = 0; Index < BundlesCount; Index++) {
      CrOffset  = ((R_SA_PEG_BND0_CRI0_CR_DWORD22_OFFSET << 8)|((Index*2) << 16));
      PcodeMailboxReadThenWrite(CrOffset, Mask32And, Data32Or, PEG_PORT);
    }
  }

  ///
  ///
  if (ProgramDmiRecipe) {
    ///
    /// CRI2_FUSE_DWORD15 [12:8] RXD_SUM_GAIN_GEN1_L1 = 0x4 (DMI)
    ///
    Mask32And  = (UINT32) ~(BIT12 | BIT11 | BIT10 | BIT9 | BIT8);
    Data32Or   = 0x4 << 8;
    ///
    /// CRI2_FUSE_DWORD15[20:16] RXD_SUM_GAIN_GEN2_L1 = 0x3 (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT20 | BIT19 | BIT18 | BIT17 | BIT16);
    Data32Or  |= 0x3 << 16;
  ///
    /// CRI2_FUSE_DWORD15[28:24] RXD_SUM_GAIN_GEN3_L0 = 0x3 (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT28 | BIT27 | BIT26 | BIT25 | BIT24);
    Data32Or  |= 0x3 << 16;
  ///
  /// CRI2_FUSE_DWORD15[4:0] RXD_SUM_GAIN_GEN3_L1 = 0x3 (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT4 | BIT3 | BIT2 | BIT1 | BIT0);
    Data32Or  |= 0x3 << 16;

    for (Index = 0; Index < BundlesCount; Index++) {
      CrOffset  = ((R_SA_PEG_BND10_CRI2_FUSE_DWORD15_OFFSET << 8)|((Index*2) << 16));
      PcodeMailboxReadThenWrite(CrOffset, Mask32And, Data32Or, DMI_PORT);
    }
  } else {
    ///
    /// CRI2_FUSE_DWORD15 [28:24] RXD_SUM_GAIN_GEN3_L1 = 0x3 (PEG)
    ///
    Mask32And  = (UINT32) ~(BIT28 | BIT27 | BIT26 | BIT25 | BIT24);
    Data32Or   = 0x3 << 24;
    ///
    /// CRI2_FUSE_DWORD15[4:0] RXD_SUM_GAIN_GEN3_L0 = 0x3 (PEG)
    ///
    Mask32And &= (UINT32) ~(BIT4 | BIT3 | BIT2 | BIT1 | BIT0);
    Data32Or  |= 0x3 << 0;
    for (Index = 0; Index < BundlesCount; Index++) {
      CrOffset  = ((R_SA_PEG_BND0_CRI2_FUSE_DWORD15_OFFSET << 8)|((Index*2) << 16));
      PcodeMailboxReadThenWrite(CrOffset, Mask32And, Data32Or, PEG_PORT);
    }
  }

  ///
  ///
  if (ProgramDmiRecipe) {
    ///
    /// CRI2_FUSE_DWORD14 [28:24] RXD_SUM_GAIN_GEN2_L0 = 0x3 (DMI)
    ///
    Mask32And  = (UINT32) ~(BIT28 | BIT27 | BIT26 | BIT25 | BIT24);
    Data32Or   = 0x3 << 24;
    ///
    /// CRI2_FUSE_DWORD14 [20:16] RXD_SUM_GAIN_GEN1_L0 = 0x4 (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT20 | BIT19 | BIT18 | BIT17 | BIT16);
    Data32Or  |= 0x4 << 16;
    for (Index = 0; Index < BundlesCount; Index++) {
      CrOffset  = ((R_SA_PEG_BND10_CRI2_FUSE_DWORD14_OFFSET << 8)|((Index*2) << 16));
      PcodeMailboxReadThenWrite(CrOffset, Mask32And, Data32Or, DMI_PORT);
    }
  }

  ///
  ///
  if (ProgramDmiRecipe) {
    ///
    /// CRI2_FUSE_DWORD16 [7:0] SWING_CONTROL = 136 or 0x88 (DMI)
    ///
    Mask32And  = (UINT32) ~(BIT7 | BIT6 | BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0);
    Data32Or   = 0x88 << 0;
    for (Index = 0; Index < BundlesCount; Index++) {
      CrOffset  = ((R_SA_PEG_BND10_CRI2_FUSE_DWORD16_OFFSET << 8)|((Index*2) << 16));
      PcodeMailboxReadThenWrite(CrOffset, Mask32And, Data32Or, DMI_PORT);
    }
  }
  ///
  ///
  /// BND0SPARE[30:30] GEN3SUMBIASSEL = 0x0 (DMI & PEG)
  ///
  Mask32And = (UINT32) ~(BIT30);
  Data32Or  = 0x0 << 30;
  ///
  /// BND0SPARE[29:27] GEN3DFEIDACPD = 0x3 (PEG & DMI)
  ///
  Mask32And &= (UINT32) ~(BIT29 | BIT28 | BIT27);
  Data32Or  |= 0x3 << 27;
  ///
  /// BND0SPARE[18:17] GEN3DFELSBSEL = 0x0 (PEG & DMI)
  ///
  Mask32And &= (UINT32) ~(BIT18 | BIT17);
  Data32Or  |= 0x0 << 17;
  ///
  /// BND0SPARE[14:13] GEN3DFESUM_MFC_10GEN = 0x0 (PEG & DMI)
  ///
  Mask32And &= (UINT32) ~(BIT14 | BIT13);
  Data32Or  |= 0x0 << 13;
  ///
  /// BND0SPARE[10:9] GEN3DFESUMADDMFC = 0x0 (PEG & DMI)
  ///
  Mask32And &= (UINT32) ~(BIT10 | BIT9);
  Data32Or  |= 0x0 << 9;
  ///
  /// BND0SPARE[7:6] GEN2DFESUMADDMFC = 0x0 (DMI & DMI)
  ///
  Mask32And &= (UINT32) ~(BIT7 | BIT6);
  Data32Or  |= 0x0 << 6;
  if (ProgramDmiRecipe) {
    ///
    /// BND0SPARE[25:23] GEN2DFEIDACPD = 0x2 (DMI)
    ///
    Mask32And &= (UINT32) ~(BIT25 | BIT24 | BIT23);
    Data32Or  |= 0x2 << 23;
    for (Index = 0; Index < BundlesCount; Index++) {
      MmioAndThenOr32 ((UINTN) (DmiBar + R_SA_PEG_BND0SPARE_OFFSET + (Index * BUNDLE_STEP)), Mask32And, Data32Or);
    }
  } else {
    ///
    /// BND0SPARE[25:23] GEN2DFEIDACPD = 0x2 (PEG)
    ///
    Mask32And &= (UINT32) ~(BIT25 | BIT24 | BIT23);
    Data32Or  |= 0x2 << 23;
    for (Index = 0; Index < SA_PEG0_CNT_MAX_BUNDLE; Index++) {  // PEG0
      PciSegmentAndThenOr32 (Peg0BaseAddress + R_SA_PEG_BND0SPARE_OFFSET + (Index * BUNDLE_STEP), Mask32And, Data32Or);
    }
    for (Index = 0; Index < SA_PEG3_CNT_MAX_BUNDLE; Index++) {  // PEG3
      PciSegmentAndThenOr32 (Peg3BaseAddress + R_SA_PEG_BND0SPARE_OFFSET + (Index * BUNDLE_STEP), Mask32And, Data32Or);
    }
  }

  ///
  ///
  //
  // @todo: Is it required , not finding in KBL/CNL
  //
  if (ProgramDmiRecipe) {
    ///
    /// Set CFG5[14:11] UPCFGSLVTMR = 4
    ///
    Mask32And = (UINT32) ~(BIT14 | BIT13 | BIT12 | BIT11);
    Data32Or  = (UINT32)  (4 << 11);
    MmioAndThenOr32 ((UINTN) (DmiBar + R_SA_DMIBAR_CFG5_OFFSET), Mask32And, Data32Or);
  }

  ///
  ///
  /// EQCFG[0] EXTEIEOS = 0x1 (Peg & DMI)
  ///
  Mask32And = (UINT32) ~(BIT0);
  Data32Or  = 0x1 << 0;
  if (ProgramDmiRecipe) {
    MmioAndThenOr32 ((UINTN) (DmiBar + R_SA_PEG_EQCFG_OFFSET), Mask32And, Data32Or);
  } else {
    ///
    /// EQCFG[25:20] LF = 0x14
    ///
    //
    // @todo: Is it required for CNL , not finding in KBL/CNL.
    //
    Mask32And &= (UINT32) ~(BIT25 | BIT24 | BIT23 | BIT22 | BIT21 | BIT20);
    Data32Or  |= 0x14 << 20;
    ///
    /// EQCFG[31:26] FS = 0x3E
    ///
    //
    // @todo: Is it required , not finding in KBL/CNL
    //
    Mask32And &= (UINT32) ~(BIT31 | BIT30 | BIT29 | BIT28 | BIT27 | BIT26);
    Data32Or  |= 0x3E << 26;
    PciSegmentAndThenOr32 (Peg0BaseAddress + R_SA_PEG_EQCFG_OFFSET, Mask32And, Data32Or);
  }
  if (!ProgramDmiRecipe) {
    PciSegmentAndThenOr32 (
      PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_PEG_BUS_NUM, SA_PEG_DEV_NUM, SA_PEG1_FUN_NUM, R_SA_PEG_EQCFG_OFFSET),
      Mask32And,
      Data32Or
      );
    PciSegmentAndThenOr32 (
      PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_PEG_BUS_NUM, SA_PEG_DEV_NUM, SA_PEG2_FUN_NUM, R_SA_PEG_EQCFG_OFFSET),
      Mask32And,
      Data32Or
      );
    PciSegmentAndThenOr32 (
      PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_PEG_BUS_NUM, SA_PEG3_DEV_NUM, SA_PEG3_FUN_NUM, R_SA_PEG_EQCFG_OFFSET),
      Mask32And,
      Data32Or
      );
  }
  ///
  /// EQCFG[1] BYPADFSM = 0x1 (DMI)
  ///
  if (ProgramDmiRecipe) {
    Mask32And = (UINT32) ~(BIT1);
    Data32Or  = 0x1 << 1;
    MmioAndThenOr32 ((UINTN) (DmiBar + R_SA_PEG_EQCFG_OFFSET), Mask32And, Data32Or);
  }
  ///
  /// EQPH3[17:0] PH3_COEFF = 0x160C7 (DMI) This requires to set and clear PH3_COEFF_CTRL for each lane
  ///
  // @todo: Is it required for CNL ? not part of recipe , currently keeping same as KBL
  //
  if (ProgramDmiRecipe) {
    Data32Or  = 0x160C7;
    for (Index = 0; Index < LanesCount; Index++) {
      MmioWrite32 ((UINTN) (DmiBar + R_SA_PEG_EQPH3_OFFSET), Data32Or | (Index << 19) | BIT18);
      MmioAnd32 ((UINTN) (DmiBar + R_SA_PEG_EQPH3_OFFSET), (UINT32) ~(BIT21 | BIT20 | BIT19 | BIT18)); // bits[21:19] for lane 0-7
    }
  }

  ///
  ///
  /// Preset Definitions
  ///
  //
  // @todo: check if required for CNL also , get Peg0/Peg3 presets. Currently using same as KBL for both PEG0, PEG3
  //
  if (!ProgramDmiRecipe) {
    for (Index = 0; Index < 2; Index++) { // Loop over PEG0 & PEG3 Controller
      if (Index == 0) { // PEG0
        BaseAddress = Peg0BaseAddress;
      } else if (Index == 1) { // PEG3
        BaseAddress = Peg3BaseAddress;
      }
      PciSegmentWrite32 (BaseAddress + R_SA_PEG_EQPRESET1_2_OFFSET,   0x32012B00);
      PciSegmentWrite32 (BaseAddress + R_SA_PEG_EQPRESET2_3_4_OFFSET, 0x003B000C);
      PciSegmentWrite32 (BaseAddress + R_SA_PEG_EQPRESET4_5_OFFSET,   0x00F802B4);
      PciSegmentWrite32 (BaseAddress + R_SA_PEG_EQPRESET6_7_OFFSET,   0x34280D88);
      PciSegmentWrite32 (BaseAddress + R_SA_PEG_EQPRESET7_8_9_OFFSET, 0x09369200);
      PciSegmentWrite32 (BaseAddress + R_SA_PEG_EQPRESET9_10_OFFSET,  0x00C8C26C);
      PciSegmentWrite32 (BaseAddress + R_SA_PEG_EQPRESET11_OFFSET,    0x00015A40);
    }
  }

  if ((CpuSku  == EnumCpuHalo) || (CpuSku  == EnumCpuTrad)) {
    ///
    ///
    if (ProgramDmiRecipe) {
      ///
      /// CRI0_CR_DWORD24[31:30] FFEWIN_CTRL = 0x0 (DMI)
      ///
      Mask32And = (UINT32) ~(BIT31 | BIT30);
      Data32Or = 0x0 << 30;
      ///
      /// CRI0_CR_DWORD24[29:28] CYCLES_CTRL = 0x0 (DMI)
      ///
      Mask32And &= (UINT32) ~(BIT29 | BIT28);
      Data32Or |= 0x0 << 28;
      ///
      /// CRI0_CR_DWORD24[27:25] PH3CDR_CTL = 0x1 (DMI)
      ///
      Mask32And &= (UINT32) ~(BIT27 | BIT26 | BIT25);
      Data32Or |= 0x1 << 25;
      ///
      /// CRI0_CR_DWORD24[24:21] PTRNSEL = 0x0 (DMI)
      ///
      Mask32And &= (UINT32) ~(BIT24 | BIT23 | BIT22 | BIT21);
      Data32Or |= 0x0 << 21;
      ///
      /// CRI0_CR_DWORD24[20:18] INITPS = 0x1 (DMI)
      ///
      Mask32And &= (UINT32) ~(BIT20 | BIT19 | BIT18);
      Data32Or |= 0x1 << 18;
      ///
      /// CRI0_CR_DWORD24[17:14] INITCTLEP = 0x2 (DMI)
      ///
      Mask32And &= (UINT32) ~(BIT17 | BIT16 | BIT15 | BIT14);
      Data32Or |= 0x2 << 14;
      ///
      /// CRI0_CR_DWORD24[13:12] DFX_CTRL = 0x0 (DMI)
      ///
      Mask32And &= (UINT32) ~(BIT13 | BIT12);
      Data32Or |= 0x0 << 12;
    } else {
      ///
      /// CRI0_CR_DWORD24[31:30] FFEWIN_CTRL = 0x0 (PEG)
      ///
      Mask32And = (UINT32) ~(BIT31 | BIT30);
      Data32Or  = 0x0 << 30;
      ///
      /// CRI0_CR_DWORD24[29:28] CYCLES_CTRL = 0x0 (PEG)
      ///
      Mask32And &= (UINT32) ~(BIT29 | BIT28);
      Data32Or |= 0x0 << 28;
      ///
      /// CRI0_CR_DWORD24[27:25] PH3CDR_CTL = 0x1 (PEG)
      ///
      ///
      Mask32And &= (UINT32) ~(BIT27 | BIT26 | BIT25);
      Data32Or |= 0x1 << 25;
      ///
      /// CRI0_CR_DWORD24[24:21] PTRNSEL = 0x0 (PEG)
      ///
      Mask32And &= (UINT32) ~(BIT24 | BIT23 | BIT22 | BIT21);
      Data32Or |= 0x0 << 21;
      ///
      /// CRI0_CR_DWORD24[20:18] INITPS = 0x1 (PEG)
      ///
      Mask32And &= (UINT32) ~(BIT20 | BIT19 | BIT18);
      Data32Or |= 0x1 << 18;
      ///
      /// CRI0_CR_DWORD24[17:14] INITCTLEP = 0x2 (PEG)
      ///
      Mask32And &= (UINT32) ~(BIT17 | BIT16 | BIT15 | BIT14);
      Data32Or |= 0x2 << 14;
      ///
      /// CRI0_CR_DWORD24[13:12] DFX_CTRL = 0x0 (PEG)
      ///
      Mask32And &= (UINT32) ~(BIT13 | BIT12);
      Data32Or |= 0x0 << 12;
    }
    for (Index = 0; Index < BundlesCount; Index++) {
      if (!ProgramDmiRecipe) {
        CrOffset  = ((R_SA_PEG_BND0_CRI0_CR_DWORD24_OFFSET << 8)|((Index*2) << 16));
        PcodeMailboxReadThenWrite(CrOffset, Mask32And, Data32Or, PEG_PORT);
      } else {
        CrOffset  = ((R_SA_PEG_BND10_CRI0_CR_DWORD24_OFFSET << 8)|((Index*2) << 16));
        PcodeMailboxReadThenWrite(CrOffset, Mask32And, Data32Or, DMI_PORT);
      }
    }
    ///
    ///
    Mask32And = 0x0;
    if (ProgramDmiRecipe) {
      ///
      /// CRI0_CR_DWORD26[31:16] PH3SUP_CTRL = 384 or 0x180 (DMI)
      ///
      Data32Or = 0x180 << 16;
      ///
      /// CRI0_CR_DWORD26[15:0] CTLEADJUST_CTRL = 21878 or 0x5576 (DMI)
      ///
      Data32Or |= 0x5576 << 0;
    } else {
      ///
      /// CRI0_CR_DWORD26[31:16] PH3SUP_CTRL = 384 or 0x180 (PEG)
      ///
      Data32Or = 0x180 << 16;
      ///
      /// CRI0_CR_DWORD26[15:0] CTLEADJUST_CTRL = 21878 or 0x5576 (PEG)
      ///
      Data32Or |= 0x5576 << 0;
    }
    for (Index = 0; Index < BundlesCount; Index++) {
      if (!ProgramDmiRecipe) {
        CrOffset  = ((R_SA_PEG_BND0_CRI0_CR_DWORD26_OFFSET << 8)|((Index*2) << 16));
        PcodeMailboxReadThenWrite(CrOffset, Mask32And, Data32Or, PEG_PORT);
      } else {
        CrOffset  = ((R_SA_PEG_BND10_CRI0_CR_DWORD26_OFFSET << 8)|((Index*2) << 16));
        PcodeMailboxReadThenWrite(CrOffset, Mask32And, Data32Or, DMI_PORT);
      }
    }

    ///
    ///
    if (ProgramDmiRecipe) {
      ///
      /// CRI0_CR_DWORD28[2:0] AVG_CTRL = 0x2 (DMI)
      ///
      Mask32And = (UINT32) ~(BIT2 | BIT1 | BIT0);
      Data32Or = 0x2 << 0;
      ///
      /// CRI0_CR_DWORD28[3:3] CR_EN_PH3_NEW_CTLE_PK = 0x1 (DMI)
      ///
      Mask32And &= (UINT32) ~(BIT3);
      Data32Or |= 0x1 << 3;
      ///
      /// Only applicable to DT/Halo
      ///
      if ((CpuSku  == EnumCpuHalo) || (CpuSku  == EnumCpuTrad)) {
        ///
        /// CRI0_CR_DWORD28[4:4] CR_ENABLE_ROUND_FIX_PH3 = 0x1 (DMI)
        ///
        Mask32And &= (UINT32) ~(BIT4);
        Data32Or |= 0x1 << 4;
      }
    } else {
      ///
      /// CRI0_CR_DWORD28[2:0] AVG_CTRL = 0x2 (PEG)
      ///
      Mask32And = (UINT32) ~(BIT2 | BIT1 | BIT0);
      Data32Or = 0x2 << 0;
      ///
      /// CRI0_CR_DWORD28[3:3] CR_EN_PH3_NEW_CTLE_PK = 0x1 only if RxCTLE Override is disabled (PEG)
      ///
      if (Gen3RxCtleOverride == 0) {
        Mask32And &= (UINT32) ~(BIT3);
        Data32Or |= 0x1 << 3;
      }
      ///
      /// Only applicable to DT/Halo
      ///
      if ((CpuSku  == EnumCpuHalo) || (CpuSku  == EnumCpuTrad)) {
        ///
        /// CRI0_CR_DWORD28[4:4] CR_ENABLE_ROUND_FIX_PH3 = 0x1 (PEG)
        ///
        Mask32And &= (UINT32) ~(BIT4);
        Data32Or |= 0x1 << 4;
      }
    }
    for (Index = 0; Index < BundlesCount; Index++) {
      if (!ProgramDmiRecipe) {
        CrOffset  = ((R_SA_PEG_BND0_CRI0_CR_DWORD28_OFFSET << 8)|((Index*2) << 16));
        PcodeMailboxReadThenWrite(CrOffset, Mask32And, Data32Or, PEG_PORT);
      } else {
        CrOffset  = ((R_SA_PEG_BND10_CRI0_CR_DWORD28_OFFSET << 8)|((Index*2) << 16));
        PcodeMailboxReadThenWrite(CrOffset, Mask32And, Data32Or, DMI_PORT);
      }
    }
  }

  ///
  /// AFEBND0CFG4[9:6] G3RXCTLEPEAK = Read from configuration. Default = 0x0 PEG, 0x0 DMI. (PEG & DMI)
  ///
  Mask32And = (UINT32) ~(BIT9 | BIT8 | BIT7 | BIT6);
  for (Index = 0; Index < BundlesCount; Index++) {
    if ((Index < Gen3CtlePeakingLength) && (Gen3CtlePeaking[Index] < 16)) {
      Data32Or = Gen3CtlePeaking[Index] << 6;
    } else {
      if (ProgramDmiRecipe) {
        Data32Or = 0 << 6;
      } else {
        Data32Or = 0 << 6;
      }
      DEBUG ((DEBUG_ERROR, "CTLE Peaking array incorrect length or invalid value!\n"));
      return;
    }
    if (ProgramDmiRecipe) {
      MmioAndThenOr32 ((UINTN) (DmiBar + R_SA_PEG_AFEBND0CFG4_OFFSET + (Index * BUNDLE_STEP)), Mask32And, Data32Or);
    } else {
      if (Index < SA_PEG3_CNT_MAX_BUNDLE) { // Bundle 0-1 belongs to PEG3
        BaseAddress = Peg3BaseAddress;
        Count = Index;
      } else { // Bundle 2-9 belongs to PEG0, but for BIOS Bundle Index start from 0
        BaseAddress = Peg0BaseAddress;
        Count = Index-SA_PEG3_CNT_MAX_BUNDLE;
      }
      PciSegmentAndThenOr32 (BaseAddress + R_SA_PEG_AFEBND0CFG4_OFFSET + (Count * BUNDLE_STEP), Mask32And, Data32Or);
    }
  }
  return;
}

