/** @file
  PEIM to initialize IGFX PM

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
#include <Library/PeiServicesLib.h>
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PciExpressLib.h>
#include <IndustryStandard/Pci22.h>
#include <Library/PeiGraphicsInitLib.h>
#include <Library/SaInitLib.h>
#include <Library/TimerLib.h>
#include <CpuRegs.h>
#include <Library/CpuPlatformLib.h>
#include <Library/SaPlatformLib.h>
#include <Register/IgdRegs.h>

///
/// Driver Consumed PPI Prototypes
///
#include <GraphicsConfig.h>
#include <Ppi/SiPolicy.h>

GLOBAL_REMOVE_IF_UNREFERENCED BOOT_SCRIPT_REGISTER_SETTING  gSaGtRC6Registers[] = {
  //
  // Render/Video/Blitter Idle Max Count
  //
  {0x0,  0x2054,    0x0,  0xA},
  {0x0,  0x12054,   0x0,  0xA},
  {0x0,  0x18054,   0x0,  0xA},
  {0x0,  0x1A054,   0x0,  0xA},
  {0x0,  0x1C054,   0x0,  0xA},
  {0x0,  0x22054,   0x0,  0xA},
  {0x0,  0x182054,  0x0,  0xA},
  {0x0,  0x1C0054,  0x0,  0xA},
  {0x0,  0x1C4054,  0x0,  0xA},
  {0x0,  0x1C8054,  0x0,  0xA},
  {0x0,  0x1D0054,  0x0,  0xA},
  {0x0,  0x1D4054,  0x0,  0xA},
  {0x0,  0x1D8054,  0x0,  0xA},
  {0x0,  0x1E0054,  0x0,  0xA},
  {0x0,  0x1E4054,  0x0,  0xA},
  {0x0,  0x1E8054,  0x0,  0xA},
  {0x0,  0x1F0054,  0x0,  0xA},
  {0x0,  0x1F4054,  0x0,  0xA},
  {0x0,  0x1F8054,  0x0,  0xA},
  {0x0,  0xC3E4,    0x0,  0xA},

  //
  // Enable Idle Messages
  //
  {0x0,  0x2050,    0x0,  0x00010000},
  {0x0,  0x12050,   0x0,  0x00010000},
  {0x0,  0x18050,   0x0,  0x00010000},
  {0x0,  0x1A050,   0x0,  0x00010000},
  {0x0,  0x1C050,   0x0,  0x00010000},
  {0x0,  0x22050,   0x0,  0x00010000},
  {0x0,  0x182050,  0x0,  0x00010000},
  {0x0,  0x1C0050,  0x0,  0x00010000},
  {0x0,  0x1C4050,  0x0,  0x00010000},
  {0x0,  0x1C8050,  0x0,  0x00010000},
  {0x0,  0x1D0050,  0x0,  0x00010000},
  {0x0,  0x1D4050,  0x0,  0x00010000},
  {0x0,  0x1D8050,  0x0,  0x00010000},
  {0x0,  0x1E0050,  0x0,  0x00010000},
  {0x0,  0x1E4050,  0x0,  0x00010000},
  {0x0,  0x1E8050,  0x0,  0x00010000},
  {0x0,  0x1F0050,  0x0,  0x00010000},
  {0x0,  0x1F4050,  0x0,  0x00010000},
  {0x0,  0x1F8050,  0x0,  0x00010000},
  //
  // RP Settings
  //
  {0x0,  0xA024,  0x0,  0x00000592}
};

GLOBAL_REMOVE_IF_UNREFERENCED BOOT_SCRIPT_REGISTER_SETTING  gSaGtSecurityRegisters[] = {
  {0x0,  0x4150,  0x0,         0x80040003},
  {0x0,  0x4154,  0x0,         0x800507FC},
  {0x0,  0x4158,  0x0,         0x800508D3},
  {0x0,  0x415C,  0x0,         0x800BFFFC},
  {0x0,  0x4160,  0x0,         0x80138001},
  {0x0,  0x4164,  0x0,         0x8014FFFC},
  {0x0,  0x4168,  0x0,         0x80190003},
  {0x0,  0x416C,  0x0,         0x80197FFC},
  {0x0,  0x4170,  0x7FFFFFFF,  0x80000000},
  {0x0,  0x4174,  0x7FFFFFFF,  0x80000000},
  {0x0,  0x4178,  0x7FFFFFFF,  0x80000000},
  {0x0,  0x417C,  0x7FFFFFFF,  0x80000000},
  {0x0,  0x4180,  0x7FFFFFFF,  0x80000000},
  {0x0,  0x4184,  0x7FFFFFFF,  0x80000000},
  {0x0,  0x4188,  0x7FFFFFFF,  0x80000000},
  {0x0,  0x418C,  0x7FFFFFFF,  0x80000000}
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT32 gSpcLock[] = {
  0x24688,
  0x2468C,
  0x24690,
  0x24708,
  0x2470C,
  0x24710,
  0x24788,
  0x2478C,
  0x24790,
  0x24308,
  0x2430C,
  0x24310,
  0x25208,
  0x2520C,
  0x25288,
  0x2528C,
  0x25290,
  0x24A08,
  0x24A0C,
  0x24A10,
  0x25210,
  0x24188,
  0x2418C,
  0x24190,
  0x24408,
  0x2440C,
  0x24410,
  0x24488,
  0x2448C,
  0x24490,
  0x24508,
  0x2450C,
  0x24510,
  0x24588,
  0x2458C,
  0x24590,
  0x24E08,
  0x24E0C,
  0x24E10,
  0x24E88,
  0x24E8C,
  0x24E90,
  0x24F08,
  0x24F0C,
  0x24F10,
  0x24F88,
  0x24F8C,
  0x24F90
};

GLOBAL_REMOVE_IF_UNREFERENCED BOOT_SCRIPT_REGISTER_SETTING  gSaGtClockGatingRegisters[] = {
  //
  //Unslice
  //
  {0x0,  0x9430,  0x0,  0x0},
  {0x0,  0x9434,  0x0,  0x40000000},
  {0x0,  0x9438,  0x0,  0x0},
  {0x0,  0x943c,  0x0,  0x0},
  {0x0,  0x9440,  0x0,  0x0},
  {0x0,  0x9444,  0x0,  0x0},
  {0x0,  0x9448,  0x0,  0x0},
  {0x0,  0x9450,  0x0,  0x0},
  {0x0,  0x9454,  0x0,  0x0},
  //
  //Slice
  //
  {0x0,  0x94D0,  0x0,  0x0},
  {0x0,  0x94D4,  0x0,  0x0},
  {0x0,  0x94D8,  0x0,  0x0},
  {0x0,  0x94E0,  0x0,  0x0},
  //
  //Subslice
  //
  {0x0,  0x9520,  0x0,  0x0},
  {0x0,  0x9524,  0x0,  0x0},
  {0x0,  0x9528,  0x0,  0x0},
  {0x0,  0x9530,  0x0,  0x0},
  //
  //INF
  //
  {0x0,  0x9560,  0x0,  0x0},
  //
  //VE/VD Boxes
  //
  {0x0,  0x1C3F04,  0x0,  0x0},
  {0x0,  0x1C3F08,  0x0,  0x0},
  {0x0,  0x1C3F0C,  0x0,  0x0},
  {0x0,  0x1C3F10,  0x0,  0x0},
  {0x0,  0x1C7F04,  0x0,  0x0},
  {0x0,  0x1C7F08,  0x0,  0x0},
  {0x0,  0x1C7F0C,  0x0,  0x0},
  {0x0,  0x1C7F10,  0x0,  0x0},
  {0x0,  0x1CBF04,  0x0,  0x0},
  {0x0,  0x1CBF08,  0x0,  0x0},
  {0x0,  0x1D3F04,  0x0,  0x0},
  {0x0,  0x1D3F08,  0x0,  0x0},
  {0x0,  0x1D3F0C,  0x0,  0x0},
  {0x0,  0x1D3F10,  0x0,  0x0},
  {0x0,  0x1D7F04,  0x0,  0x0},
  {0x0,  0x1D7F08,  0x0,  0x0},
  {0x0,  0x1D7F0C,  0x0,  0x0},
  {0x0,  0x1D7F10,  0x0,  0x0},
  {0x0,  0x1DBF04,  0x0,  0x0},
  {0x0,  0x1DBF08,  0x0,  0x0},
  {0x0,  0x1E3F04,  0x0,  0x0},
  {0x0,  0x1E3F08,  0x0,  0x0},
  {0x0,  0x1E3F0C,  0x0,  0x0},
  {0x0,  0x1E3F10,  0x0,  0x0},
  {0x0,  0x1E7F04,  0x0,  0x0},
  {0x0,  0x1E7F08,  0x0,  0x0},
  {0x0,  0x1E7F0C,  0x0,  0x0},
  {0x0,  0x1E7F10,  0x0,  0x0},
  {0x0,  0x1EBF04,  0x0,  0x0},
  {0x0,  0x1EBF08,  0x0,  0x0},
  {0x0,  0x1F3F04,  0x0,  0x0},
  {0x0,  0x1F3F08,  0x0,  0x0},
  {0x0,  0x1F3F0C,  0x0,  0x0},
  {0x0,  0x1F3F10,  0x0,  0x0},
  {0x0,  0x1F7F04,  0x0,  0x0},
  {0x0,  0x1F7F08,  0x0,  0x0},
  {0x0,  0x1F7F0C,  0x0,  0x0},
  {0x0,  0x1F7F10,  0x0,  0x0},
  {0x0,  0x1FBF04,  0x0,  0x0},
  {0x0,  0x1FBF08,  0x0,  0x0}
};


/**
  Initialize GT PowerManagement of SystemAgent.

  @param[in] GtConfig            - Instance of GRAPHICS_PEI_CONFIG
  @param[in] GttMmAdr            - Base Address of IGFX MMIO BAR
  @param[in] MchBarBase          - Base Address of MCH_BAR

  @retval EFI_SUCCESS           - GT Power Management initialization complete
  @retval EFI_INVALID_PARAMETER - The input parameter is invalid
**/
EFI_STATUS
PmInit (
  IN       GRAPHICS_PEI_CONFIG          *GtConfig,
  IN       UINT32                       GttMmAdr,
  IN       UINT32                       MchBarBase
  )
{
  UINT32            RegOffset;
  UINT32            Data32;
  UINT32            Data32Mask;
  UINT32            Result;
  UINT8             LoopCounter;
  UINT32            Data32And;
  UINT32            Data32Or;
  CPU_STEPPING      CpuSteppingId;
  UINT32            Ssid;

  CpuSteppingId   = GetCpuStepping ();

  if ((GttMmAdr == 0) || (MchBarBase == 0) || (GtConfig == NULL)) {
    DEBUG ((DEBUG_WARN, "Invalid parameters for PmInit\n"));
    return EFI_INVALID_PARAMETER;
  }

  ///
  /// 1aa. Enable all GTI-Uncore clock gating
  ///
  RegOffset = 0x9560;
  Data32    = 0x0;
  MmioWrite32 (GttMmAdr + RegOffset, Data32);

  if (GtConfig->PmSupport && (!IsDisplayOnlySku())) {
    DEBUG ((DEBUG_INFO, "Starting Register programming for GT PM.\n"));
    ///
    /// 1d. Enable Clock squashing (Prochot Feature)
    ///
    RegOffset    = R_SA_GTTMMADR_PROCHOT_0_OFFSET;
    Data32Or     = B_SA_GTTMMADR_PROCHOT_0_TEETH_BREAKING_EN | B_SA_GTTMMADR_PROCHOT_0_DIDT_LOCK_CONTROL;


    MmioOr32 (GttMmAdr + RegOffset, Data32Or);

    ///
    /// Programming Crystal Clock and lock register by setting Bit31.
    ///
    RegOffset = 0xD00;
    Data32    = MmioRead32 (GttMmAdr + RegOffset);
    ///
    /// Programm [2:1] = 11 if [5:3] is 001 (indicate ref clock is 19.2Mhz)
    /// Programm [2:1] = 10 if [5:3] is 000/010/011 (indicate ref clock is 24Mhz/38.4MHz/25MHz)
    ///
    Data32 &= (BIT3 | BIT4 | BIT5);
    Data32 = (Data32 >>3);
    if (Data32 == 1) {
      Data32Or = 0x6;
    } else if ((Data32 == 0) || (Data32 == 2) || (Data32 == 3)) {
      Data32Or = 0x4;
    }

    Data32Or |= BIT31;
    Data32And = (UINT32) ~(BIT2 | BIT1);
    MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);

    ///
    /// Enable Force Wake
    ///
    RegOffset                     = 0xA188;
    Data32                        = 0x00010001;
    MmioWrite32 (GttMmAdr + RegOffset, Data32);

    ///
    /// Poll to verify Force Wake Acknowledge Bit
    ///
    RegOffset                     = 0x130044;
    Data32Mask                    = BIT0;
    Result                        = 1;
    PollGtReady (GttMmAdr, RegOffset, Data32Mask, Result);
    DEBUG ((DEBUG_INFO, "Poll to verify Force Wake Acknowledge Bit, Result = 1\n"));

    ///
    /// GT Security Resgister programming.
    ///
    for (LoopCounter = 0; LoopCounter < sizeof (gSaGtSecurityRegisters) / sizeof (BOOT_SCRIPT_REGISTER_SETTING); ++LoopCounter) {
      RegOffset    = gSaGtSecurityRegisters[LoopCounter].Offset;
      Data32And    = gSaGtSecurityRegisters[LoopCounter].AndMask;
      Data32Or     = gSaGtSecurityRegisters[LoopCounter].OrMask;

      MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);
    }

    ///
    /// Enabling Push Bus Metric Counter
    ///
    RegOffset                     = 0xA250;
    Data32                        = 0x000001FF;
    MmioWrite32 (GttMmAdr + RegOffset, Data32);

    ///
    /// Pushbus Metric Control
    ///
    RegOffset                     = 0xA248;
    Data32                        = 0x80000004;
    MmioWrite32 (GttMmAdr + RegOffset, Data32);


    ///
    /// Program GfxPause Register
    ///
    RegOffset                     = 0xA000;
    Data32                        = 0x00070020;
    MmioWrite32 (GttMmAdr + RegOffset, Data32);


    ///
    /// GPM Control
    ///
    RegOffset                     = 0xA180;
    Data32                        = 0x89200000;
    MmioWrite32 (GttMmAdr + RegOffset, Data32);

    ///
    /// Disable Fence writes
    ///
    RegOffset                     = 0xA194;
    if ( CpuSteppingId == EnumIclA0) {
      Data32Or                      = BIT8;
    }
    Data32Or                      = BIT5 | BIT7 | BIT31;
    MmioOr32 (GttMmAdr + RegOffset, Data32Or);

    ///
    /// Enable DOP clock gating.
    ///
    Data32 = 0xFFFFFFFF;

    RegOffset                     = 0x9424;
    MmioWrite32 (GttMmAdr + RegOffset, Data32);
    DEBUG ((DEBUG_INFO, "Enabled DOP clock gating \n"));

    ///
    /// Enable Unit Level Clock Gating
    ///
    for (LoopCounter = 0; LoopCounter < sizeof (gSaGtClockGatingRegisters) / sizeof (BOOT_SCRIPT_REGISTER_SETTING); ++LoopCounter) {
      RegOffset = gSaGtClockGatingRegisters[LoopCounter].Offset;
      Data32And = gSaGtClockGatingRegisters[LoopCounter].AndMask;
      Data32Or = gSaGtClockGatingRegisters[LoopCounter].OrMask;

      MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);
    }
    RegOffset                     = 0x9044;
    Data32                        = 0xC0000000;
    MmioWrite32 (GttMmAdr + RegOffset, Data32);
    ///
    /// RC6 Settings
    ///
    for (LoopCounter = 0; LoopCounter < sizeof (gSaGtRC6Registers) / sizeof (BOOT_SCRIPT_REGISTER_SETTING); ++LoopCounter) {
      RegOffset = gSaGtRC6Registers[LoopCounter].Offset;
      Data32And = gSaGtRC6Registers[LoopCounter].AndMask;
      Data32Or = gSaGtRC6Registers[LoopCounter].OrMask;

      MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);
    }
    ///
    /// Program GT Normal Frequency Request
    ///
    //
  // Program to 100 MHZ
  //
    Data32 = 0x03000000;

    MmioWrite32 (GttMmAdr + 0xA008, Data32);


    ///
    /// CdynMax Clamping Feature for higher frequency
    ///
    if (GtConfig->CdynmaxClampEnable) {
      ///
      /// a. Program the event weights into GT MMIO registers 0x8C04, 0x8C08 and 0x8C0C (Iccp_CDYNMAX_EVTWTx)
      /// b. Program the EI window in GT MMIO register 0x8C00 (CDYNMAX_CFG0)
      /// c. Program the clamping thresholds and the associated delta values in MMIO registers 0x8C10, 0x8C14, 0x8C18 and 0x8C1C (Iccp_CDYNA_CLAMP_THRx)
      /// d. Program the Panic threshold values in MMIO register 0x8C00.
      /// e. Program the threshold Compare Shift Value in MMIO register 0x8C1C
      /// f. Set the Lock Bit for SPMunit Registers
      /// g. Set the required clamping level (clamped/Unclamped) in register in GT MMIO register 0xA218 (Iccp_Request_level)
      /// h. Enable GT ICCP feature via GT MMIO register 0xA214 (Iccp_Feature_Enable). The below settings are of 86% Clamping Threshold
      ///
      DEBUG ((DEBUG_INFO, "Cdynmax Clamp Feature Enabled\n"));

      RegOffset                     = 0x8C04;
      Data32                        = 0x0960A0FF;
      MmioWrite32 (GttMmAdr + RegOffset, Data32);
      DEBUG ((DEBUG_INFO, "0x8C04: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));

      RegOffset                     = 0x8C08;
      Data32                        = 0x0602070A;
      MmioWrite32 (GttMmAdr + RegOffset, Data32);
      DEBUG ((DEBUG_INFO, "0x8C08: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));

      RegOffset                     = 0x8C0C;
      Data32And                     = 0x0;
      Data32Or                      = 0x04050F0E;
      MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);
      DEBUG ((DEBUG_INFO, "0x8C0C: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));

      ///
      /// b. EI - Evaluation Interval 8C00[15:0]]= 13 (256ns/20 = 12.8)
      /// d.Panic Threshold value 8C00[31:24]= 133, Progam ClampDis Threshold 8C00[23:16]= 64
      ///
      RegOffset                     = 0x8C00;
      Data32                        = 0x8540000D;
      MmioWrite32 (GttMmAdr + RegOffset, Data32);
      DEBUG ((DEBUG_INFO, "0x8C00: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));

      ///
      /// c. Clamping Threshold and Deltas
      ///
      RegOffset                     = 0x8C10;
      Data32                        = 0xF064E043;
      MmioWrite32 (GttMmAdr + RegOffset, Data32);
      DEBUG ((DEBUG_INFO, "0x8C10: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));

      RegOffset                     = 0x8C14;
      Data32                        = 0xFC80F875;
      MmioWrite32 (GttMmAdr + RegOffset, Data32);
      DEBUG ((DEBUG_INFO, "0x8C14: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));

      RegOffset                     = 0x8C18;
      Data32                        = 0x08880085;
      MmioWrite32 (GttMmAdr + RegOffset, Data32);
      DEBUG ((DEBUG_INFO, "0x8C18: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));

      ///
      /// e.Threshold Compare Shift Value in MMIO register 0x8C1C
      ///
      RegOffset                     = 0x8C1C;
      Data32And                     = 0xC0000000;
      Data32Or                      = 0x1220108D;
      MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);
      DEBUG ((DEBUG_INFO, "0x8C1C: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));

      ///
      /// g. License Request Level - GT MMIO Regsiter address: 0xA218 [0:0] 1 - Clamped Mode; 0 - Non-Clamped Mode
      ///
      RegOffset                     = 0xA218;
      Data32And                     = 0xFFFFFFFE;
      Data32Or                      = BIT0;
      MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);
      DEBUG ((DEBUG_INFO, "0xA218: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));

      ///
      /// h. Enabling the feature GT MMIO Regsiter address: 0xA214 [0:0] IccP Feature Enable 0b = Feature is disabled (default) 1b = Feature is enabled
      /// i. Iccp Feature Lock 0xA214 [31:31] =1 , 1b = Feature is locked for SPM and GPM unit  0b = Feature Unlocked.
      ///
      RegOffset                     = 0xA214;
      Data32And                     = 0x7FFFFFFE;
      Data32Or                      = (BIT31 | BIT0);
      MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);
      DEBUG ((DEBUG_INFO, "0xA214: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));

      ///
      /// Programming for 50% CheckPoint
      /// a. Enable 50% CheckPoint 0x8C20[1] = 0
      /// b. 0x8C20[3:2] = 50% checkpoint programmable bubble count. 0x8C20[3:2] = 11b for 86% CT
      /// c. Enable Max Ratio to be 11/16 0x8C20[4] = 0
      /// d. Progam ClampDis Threshold 8C00[23:16] (done above)
      ///
      RegOffset                     = 0x8C20;
      Data32And                     = 0xFFFFFFE1;
      Data32Or                      = 0x0C;
      MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);
      ///
      /// Lock Bit for SPMunit Registers 0x8C20 [9:9]
      ///
      MmioOr32 (GttMmAdr + RegOffset, BIT9);
      DEBUG ((DEBUG_INFO, "0x8C20: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));

    } else {
      ///
      /// Set the Lock Bit for SPMunit Registers
      /// Set the required clamping level as Unclamped in register 0xA218[0]
      /// Disable the feature 0xA214 [0:0]  0b = Feature is disabled 1b = Feature is enabled
      /// Keep it locked 0xA214 [31:31]  IccP Lock bit : 1= Keep it locked for all part.
      ///
      DEBUG ((DEBUG_INFO, "Cdynmax Clamp Feature Disabled\n"));

      ///
      /// Lock Bit for SPMunit Registers
      ///
      RegOffset                     = 0x8C20;
      Data32And                     = (UINT32) ~(BIT9);
      Data32Or                      = BIT9;
      MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);
      DEBUG ((DEBUG_INFO, "0x8C20: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));

      ///
      /// License Request Level - Non-Clamp Mode: 0xA218 [0:0] 1 - Clamped Mode; 0 - Non-Clamped Mode
      ///
      RegOffset                     = 0xA218;
      Data32And                     = (UINT32) ~(BIT0);
      Data32Or                      = 0;
      MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);
      DEBUG ((DEBUG_INFO, "0xA218: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));

      RegOffset                     = 0xA214;
      Data32And                     = 0x7FFFFFFE;
      Data32Or                      = BIT31;
      MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);
      DEBUG ((DEBUG_INFO, "0xA214: 0x%x\n", MmioRead32 (GttMmAdr + RegOffset)));
    }

    ///
    /// SPC Register Lock.
    ///
    //
    // Set slice and subslice steering to valid slices before reading SPC registers
    //
    RegOffset = 0x9138;
    if ((MmioRead32 (GttMmAdr + RegOffset) & BIT0) == 0) {
      ///
      /// Slice 0 disabled, set 0xFDC to Slice 1
      ///
      RegOffset = 0x0FDC;
      Data32And = (UINT32) ~(BIT30 | BIT29 | BIT28 | BIT27);
      Data32Or  = BIT27;
      MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);
    }
    //
    // Reading the first enabled Subslice
    //
    RegOffset = 0x913C;
    Data32 = MmioRead32 (GttMmAdr + RegOffset) & 0xFF;
    for (Ssid = 0; Ssid < 8; Ssid++) {
      if ((Data32 & ((UINT32) 0x1 << Ssid)) == 0)
        break;
    }
    ///
    /// Set 0xFDC to enabled SubSlice ID
    ///
    RegOffset = 0x0FDC;
    Data32And = (UINT32) ~(BIT26 | BIT25 | BIT24);
    Data32Or  = (UINT32) (Ssid << 24);
    MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);

    Data32Or = 0x80000000;
    for (LoopCounter = 0; LoopCounter < sizeof(gSpcLock) / sizeof(UINT32); ++LoopCounter) {
      RegOffset = gSpcLock[LoopCounter];
      MmioOr32(GttMmAdr + RegOffset, Data32Or);
    }

    ///
    /// Enabling to enter RC6 state in idle mode.
    ///
    Data32 = 0;
    if (GtConfig->RenderStandby) {
      RegOffset                     = 0xA094;
      Data32                        = 0x00040000;
      MmioWrite32 (GttMmAdr + RegOffset, Data32);
      DEBUG ((DEBUG_INFO, "Entered RC6 state in idle mode\n"));
    }


    ///
    /// Clear offset 0xA188 [31:0] to clear the force wake enable
    ///
    RegOffset                     = 0xA188;
    Data32                        = 0x00010000;
    MmioWrite32 (GttMmAdr + RegOffset, Data32);

    ///
    /// Poll until clearing is cleared to verify the force wake acknowledge.
    ///
    RegOffset                     = 0x130044;
    Data32Mask                    = BIT0;
    Result                        = 0;
    PollGtReady (GttMmAdr, RegOffset, Data32Mask, Result);


  }

  DEBUG ((DEBUG_INFO, "GT PM Init Done. Exiting.\n"));
  return EFI_SUCCESS;
}

/**
  Program PSMI registers.

  @param[in] GRAPHICS_PEI_CONFIG             *GtConfig
  @param[in] GRAPHICS_PEI_PREMEM_CONFIG      *GtPreMemConfig

  @retval EFI_SUCCESS     - PSMI registers programmed.
**/
EFI_STATUS
ProgramPsmiRegs (
  IN       GRAPHICS_PEI_CONFIG             *GtConfig,
  IN       GRAPHICS_PEI_PREMEM_CONFIG      *GtPreMemConfig
  )
{
  UINT64       McD0BaseAddress;
  UINT64       McD2BaseAddress;
  UINT64       PsmiBase;
  UINT32       *PsmiBaseAddr;
  UINT32       *PsmiLimitAddr;
  UINT64       PsmiLimit;
  UINT32       PavpMemSizeInMeg;
  UINT32       PsmiRegionSize;
  UINT32       GraphicsStolenSize;
  UINT32       PavpMemSize;
  UINT32       GttMmAdr;
  UINT32       GSMBase;

  McD0BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, 0);
  McD2BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, 0);

  GttMmAdr = (PciSegmentRead32 (McD2BaseAddress + R_SA_IGD_GTTMMADR)) & 0xFFFFFFF0;

  if (GttMmAdr == 0) {
    GttMmAdr = GtPreMemConfig->GttMmAdr;
    PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR, (UINT32) (GttMmAdr & 0xFFFFFFFF));
    PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR + 4, 0);
  }

  if (!IgfxCmdRegEnabled()) {
    ///
    /// Enable Bus Master and Memory access on 0:2:0
    ///
    PciSegmentOr16 (McD2BaseAddress + R_SA_IGD_CMD, (BIT2 | BIT1));
  }

  ///
  /// If device 0:2:0 (Internal Graphics Device, or GT) is not enabled, skip programming PSMI registers
  ///
  if ((PciSegmentRead16 (McD2BaseAddress + R_SA_IGD_VID) != 0xFFFF) && (GtPreMemConfig->GtPsmiSupport == 1)) {
    DEBUG ((DEBUG_INFO, "Programming PSMI Registers\n"));
    ///
    /// PsmiBase is GSM Base plus GSM Size.
    ///
    GSMBase = PciSegmentRead32 (McD0BaseAddress + R_SA_BDSM) & B_SA_BDSM_BDSM_MASK;

    if (GtPreMemConfig->IgdDvmt50PreAlloc < 240) {
      GraphicsStolenSize = (32 * GtPreMemConfig->IgdDvmt50PreAlloc) << 20;
    } else {
      GraphicsStolenSize = (4 * (GtPreMemConfig->IgdDvmt50PreAlloc - 239)) << 20;
    }
    PsmiBase = (UINT64) GSMBase + (UINT64) GraphicsStolenSize;
    PsmiBaseAddr = (UINT32 *) &PsmiBase;

    ///
    /// Psmi Limit is Psmibase plus Psmi size and subtract PAVP size.
    ///
    PavpMemSizeInMeg = 1 << ((MmioRead32 (GttMmAdr + R_SA_GTTMMADR_PAVPC_OFFSET) & B_SA_PAVPC_WOPCMSZ_MASK) >> 7);
    PavpMemSize = PavpMemSizeInMeg << 20;
    PsmiRegionSize = (32 + 256 * GtPreMemConfig->PsmiRegionSize) << 20;
    PsmiLimit = (UINT64) PsmiBase + (UINT64) PsmiRegionSize - PavpMemSize;
    PsmiLimitAddr = (UINT32 *) &PsmiLimit;
    ///
    /// Program PSMI Base and PSMI Limit and Lock.
    ///
    MmioWrite32 (GttMmAdr + R_SA_GTTMMADR_PSMIBASE_OFFSET + 4, *(PsmiBaseAddr + 1));
    MmioWrite32 (GttMmAdr + R_SA_GTTMMADR_PSMILIMIT_OFFSET + 4, *(PsmiLimitAddr + 1));
  }
  return EFI_SUCCESS;
}

/**
  Initialize PAVP feature of SystemAgent.

  @param[in] GRAPHICS_PEI_CONFIG             *GtConfig
  @param[in] SA_MISC_PEI_CONFIG              *MiscPeiConfig

  @retval EFI_SUCCESS     - PAVP initialization complete
  @retval EFI_UNSUPPORTED - iGFX is not present so PAVP not supported
**/
EFI_STATUS
PavpInit (
  IN       GRAPHICS_PEI_CONFIG             *GtConfig,
  IN       SA_MISC_PEI_CONFIG              *MiscPeiConfig,
  IN       GRAPHICS_PEI_PREMEM_CONFIG      *GtPreMemConfig
  )
{

  UINT32       PcmBase;
  UINT64       McD0BaseAddress;
  UINT64       McD2BaseAddress;
  UINT32       Pavpc;
  UINT32       GttMmAdr;
  UINT32       GMSSizeSelector;
  UINT32       GMSSize;

  PcmBase = 0;
  McD0BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, 0);
  McD2BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, 0);
  Pavpc = PciSegmentRead32 (McD0BaseAddress + R_SA_PAVPC);

  GttMmAdr = (PciSegmentRead32 (McD2BaseAddress + R_SA_IGD_GTTMMADR)) & 0xFFFFFFF0;
  if (GttMmAdr == 0) {
    GttMmAdr = GtPreMemConfig->GttMmAdr;
    PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR, (UINT32) (GttMmAdr & 0xFFFFFFFF));
    PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR + 4, 0);
  }

  if (!IgfxCmdRegEnabled()) {
    ///
    /// Enable Bus Master and Memory access on 0:2:0
    ///
    PciSegmentOr16(McD2BaseAddress + R_SA_IGD_CMD, (BIT2 | BIT1));
  }

  ///
  /// If device 0:2:0 (Internal Graphics Device, or GT) is not enabled, skip PAVP
  ///
  if (PciSegmentRead16 (McD2BaseAddress + R_SA_IGD_VID) != 0xFFFF) {
    GMSSizeSelector = PciSegmentRead32 (McD0BaseAddress + R_SA_GGC);
    GMSSizeSelector = (GMSSizeSelector & B_SA_GGC_GMS_MASK) >> N_SA_GGC_GMS_OFFSET;
    //
    // Graphics Stolen Size
    // Graphics Stolen size above 64MB has a granularity of 32MB increments
    // GMS values below 240 correspond to Sizes 32 * GSMValue
    // Graphics Stolen size below 64MB has a higher granularity and can be set in 4MB increments
    // GMS values ranging from 240-254 correspond to sizes 4MB to 60MB (excluding 32MB) which is 4*(GSMValue-239)
    //
    if (GMSSizeSelector < 240 ) {
      GMSSize = (UINT32) GMSSizeSelector * 32;
    } else {
      GMSSize = 4 * (GMSSizeSelector - 239);
    }
    DEBUG ((DEBUG_INFO, "Initializing PAVP\n"));
    Pavpc &= (UINT32) ~(B_SA_PAVPC_HVYMODSEL_MASK | B_SA_PAVPC_PCMBASE_MASK | B_SA_PAVPC_PAVPE_MASK | B_SA_PAVPC_PCME_MASK);
    Pavpc &= (UINT32) ~(BIT8 | BIT7);
    //
    // Program PCM Base and size = 2MB
    // PCMBase = DSM top - PCM size
    //
    PcmBase = ((UINT32) RShiftU64 ((PciSegmentRead32 (McD0BaseAddress + R_SA_BDSM)), 20)) + GMSSize - PAVP_PCM_SIZE_2_MB;
    Pavpc  |= (UINT32)(BIT7);

    Pavpc |= (UINT32) LShiftU64 (PcmBase, 20);
    if (GtConfig->PavpEnable == 1) {
      Pavpc |= B_SA_PAVPC_PAVPE_MASK;
    }
    Pavpc |= B_SA_PAVPC_PCME_MASK;

    Pavpc |= BIT6;
  }
  ///
  /// Lock PAVPC Register
  ///
  Pavpc |= B_SA_PAVPC_PAVPLCK_MASK;
  PciSegmentWrite32 (McD0BaseAddress + R_SA_PAVPC, Pavpc);

  //
  // Program GT MMIO PAVPC Mirror register
  //
  MmioWrite32 (GttMmAdr + R_SA_GTTMMADR_PAVPC_OFFSET, Pavpc);
  PciSegmentWrite32 (McD2BaseAddress + R_SA_DEV2_PAVPC, Pavpc);
  return EFI_SUCCESS;
}

/**
  Poll Run busy clear

  @param[in] Base    - Base address of MMIO
  @param[in] Timeout - Timeout value in microsecond

  @retval TRUE       - Run Busy bit is clear
  @retval FALSE      - Run Busy bit is still set
**/
BOOLEAN
PollRunBusyClear (
  IN    UINT64           Base,
  IN    UINT32           Timeout
  )
{
  UINT32  Value;
  BOOLEAN Status = FALSE;

  //
  // Make timeout an exact multiple of 10 to avoid infinite loop
  //
  if ((Timeout) % 10 != 0) {
    Timeout = (Timeout) + 10 - ((Timeout) % 10);
  }

  while (Timeout != 0) {
    Value = MmioRead32 ((UINTN) Base + 0x138124);
    if (Value & BIT31) {
      //
      // Wait for 10us and try again.
      //
      DEBUG ((DEBUG_INFO, "Interface register run busy bit is still set. Trying again \n"));
      MicroSecondDelay (MAILBOX_WAITTIME);
      Timeout = Timeout - MAILBOX_WAITTIME;
    } else {
      Status = TRUE;
      break;
    }
  }
  ASSERT ((Timeout != 0));

  return Status;
}

/**
  Program the max Cd Clock supported by the platform

  @param[in] GtConfig            - Instance of GRAPHICS_PEI_CONFIG
  @param[in] GttMmAdr            - Base Address of IGFX MMIO BAR

  @retval EFI_SUCCESS            - CD Clock value programmed.
  @retval EFI_INVALID_PARAMETER  - The input parameter is invalid

**/
EFI_STATUS
ProgramCdClkReg (
  IN       GRAPHICS_PEI_CONFIG          *GtConfig,
  IN       UINT32                       GttMmAdr
  )
{
  UINT32         Data32Or;
  UINT32         ReferenceFreq;

  ///
  /// For Gen11, CDCLK_CTL - GttMmAdr + 0x46000
  /// CdClock 0: 307.2Mhz - [10:0] = 010 0110 0100 = 0x264
  /// CdClock 1: 312Mhz   - [10:0] = 010 0110 1110 = 0x26E
  /// CdClock 2: 552Mhz   - [10:0] = 100 0100 1110 = 0x44E
  /// CdClock 3: 556.8Mhz - [10:0] = 100 0101 1000 = 0x458
  /// CdClock 4: 648Mhz   - [10:0] = 101 0000 1110 = 0x50E
  /// CdClock 5: 652.8Mhz - [10:0] = 101 0001 1000 = 0x518
  /// CdClock:0xFF Program Max based on reference clock:- For 19.2MHz, 38.4MHz = 652.8 MHz. For 24MHz = 648MHz.
  switch (GtConfig->CdClock) {
    case 0 :
      Data32Or = V_SA_CDCLK_CTL_CD_FREQ_DECIMAL_307_2;
      break;
    case 1 :
      Data32Or = V_SA_CDCLK_CTL_CD_FREQ_DECIMAL_312;
      break;
    case 2 :
      Data32Or = V_SA_CDCLK_CTL_CD_FREQ_DECIMAL_552;
      break;
    case 3 :
      Data32Or = V_SA_CDCLK_CTL_CD_FREQ_DECIMAL_556_8;
      break;
    case 4 :
      Data32Or = V_SA_CDCLK_CTL_CD_FREQ_DECIMAL_648;
      break;
    case 5 :
      Data32Or = V_SA_CDCLK_CTL_CD_FREQ_DECIMAL_652_8;
      break;
    case 0xFF:
      ReferenceFreq = GetDssmReferenceFrequency (GttMmAdr);
      if ((ReferenceFreq == V_SA_CDCLK_PLL_REF_FREQUENCY_19_2MHZ) || (ReferenceFreq == V_SA_CDCLK_PLL_REF_FREQUENCY_38_4MHZ)) {
        Data32Or = V_SA_CDCLK_CTL_CD2X_ALL_CDCLK | V_SA_CDCLK_CTL_CD2X_PIPE_SELECT_NONE | V_SA_CDCLK_CTL_CD_FREQ_DECIMAL_652_8;
      } else {
        Data32Or = V_SA_CDCLK_CTL_CD2X_ALL_CDCLK | V_SA_CDCLK_CTL_CD2X_PIPE_SELECT_NONE | V_SA_CDCLK_CTL_CD_FREQ_DECIMAL_648;
      }
      break;
    default:
      return EFI_INVALID_PARAMETER;
  }
  //
  // Program CDCLK register with user selected value so that GOP can read and initialize CD Clock.
  //
  MmioAndThenOr32 (GttMmAdr + R_SA_GTTMMADR_CDCLK_CTL_OFFSET, 0xFFFFF800, Data32Or);

  return EFI_SUCCESS;
}

/**
  This function will get value of reference clock from DSSM strap register.

  @param[in] GttMmAdr            - Base Address of IGFX MMIO BAR

  @retval ReferenceFreq          - Returns value of reference frequency found in DSSM strap register.
                                   Unit of freuquency is in KHz.
**/
UINT32
GetDssmReferenceFrequency (
  IN  UINT32                GttMmAdr
)
{
  UINT32 DssmVal;
  UINT32 ReferenceFreq;
  UINT8  ReferenceFreqBits;

  DssmVal           = 0;
  ReferenceFreq     = 0;
  ReferenceFreqBits = 0;

  //
  // Read Reference frequency from DSSM register.
  // BIT31:29 of DSSM register indicates reference frequency
  // For BIT31:29 = 0, reference frequency = 24 MHz.
  // For BIT31:29 = 1, reference frequency = 19.2 MHz.
  // For BIT31:29 = 2, reference frequency = 38.4 MHz.
  //
  DssmVal           = MmioRead32 (GttMmAdr + R_SA_GTTMMADR_DSSM_OFFSET);
  ReferenceFreqBits = (UINT8)((DssmVal & B_SA_GTTMMADR_DSSM_REFERENCE_FREQ_MASK) >> B_SA_GTTMMADR_DSSM_REFERENCE_FREQ_OFFSET);

  switch (ReferenceFreqBits) {
    case 0x0:
      ReferenceFreq = V_SA_CDCLK_PLL_REF_FREQUENCY_24MHZ;
      break;
    case 0x1:
      ReferenceFreq = V_SA_CDCLK_PLL_REF_FREQUENCY_19_2MHZ;
      break;
    case 0x2:
      ReferenceFreq = V_SA_CDCLK_PLL_REF_FREQUENCY_38_4MHZ;
      break;
    default:
     DEBUG ((EFI_D_ERROR,"Invalid PLL Reference clock value during CdClockInit()\n"));
      ASSERT (FALSE);
  }
  return ReferenceFreq;
}

/**
  Initialize the full CD clock as per Bspec sequence.

  @param[in] GtConfig            - Instance of GRAPHICS_PEI_CONFIG
  @param[in] GtPreMemConfig      - Instance of GRAPHICS_PEI_PREMEM_CONFIG

  @retval EFI_SUCCESS            - CD Clock Init successful.
  @retval EFI_INVALID_PARAMETER  - The input parameter is invalid
  @retval EFI_UNSUPPORTED        - iGfx is not present.
**/
EFI_STATUS
CdClkInit (
  IN  GRAPHICS_PEI_CONFIG             *GtConfig,
  IN  GRAPHICS_PEI_PREMEM_CONFIG      *GtPreMemConfig
  )
{
  UINT32         Data32Or;
  UINT16         WaitTime;
  UINT64         McD2BaseAddress;
  UINT32         GttMmAdr;
  UINT32         VoltageLevel;
  UINT32         ReferenceFreq;
  UINT8          CdClkPllRatio;

  WaitTime = DISPLAY_CDCLK_TIMEOUT;
  CdClkPllRatio = V_SA_CDCLK_PLL_RATIO_652_8MHZ_REF_38_4MHZ; // Initializing to max value

  McD2BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, 0);
  if (PciSegmentRead16 (McD2BaseAddress + R_SA_IGD_VID) == 0xFFFF) {
    DEBUG ((DEBUG_INFO, "iGFX not enabled - Exit!\n"));
    return EFI_UNSUPPORTED;
  }

  if (GtConfig->SkipCdClockInit) {
    return EFI_SUCCESS;
  }

  GttMmAdr = (PciSegmentRead32 (McD2BaseAddress + R_SA_IGD_GTTMMADR)) & 0xFFFFFFF0;
  if (GttMmAdr == 0) {
    GttMmAdr = GtPreMemConfig->GttMmAdr;
    PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR, (UINT32) (GttMmAdr & 0xFFFFFFFF));
    PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR + 4, 0);
  }

  if (!IgfxCmdRegEnabled()) {
    ///
    /// Enable Bus Master and Memory access on 0:2:0
    ///
    PciSegmentOr16 (McD2BaseAddress + R_SA_IGD_CMD, (BIT2 | BIT1));
  }

  if (!(MmioRead32 (GttMmAdr + R_SA_GTTMMADR_CDCLK_PLL_ENABLE_OFFSET) & B_SA_CDCLK_PLL_ENABLE_BIT)) {
    //
    // Read Reference frequency from DSSM register.
    //
    ReferenceFreq = GetDssmReferenceFrequency (GttMmAdr);

    ///
    /// For Gen11, CDCLK_CTL - GttMmAdr + 0x46000
    /// CdClock 0: [23:22] = 0; [21:19] = 111b; 307.2    Mhz - [10:0] = 010 0110 0100 = 0x264
    /// CdClock 1: [23:22] = 0; [21:19] = 111b; 312      Mhz - [10:0] = 010 0110 1110 = 0x26E
    /// CdClock 2: [23:22] = 0; [21:19] = 111b; 552      Mhz - [10:0] = 100 0100 1110 = 0x44E
    /// CdClock 3: [23:22] = 0; [21:19] = 111b; 556.8    Mhz - [10:0] = 100 0101 1000 = 0x458
    /// CdClock 4: [23:22] = 0; [21:19] = 111b; 648      Mhz - [10:0] = 101 0000 1110 = 0x50E
    /// CdClock 5: [23:22] = 0; [21:19] = 111b; 652.8    Mhz - [10:0] = 101 0001 1000 = 0x518
    /// CdClock:0xFF Program Max based on reference clock:- For 19.2MHz, 38.4MHz = 652.8 MHz. For 24MHz = 648MHz.
    switch (GtConfig->CdClock) {
      case 0 :
        Data32Or = V_SA_CDCLK_CTL_CD2X_ALL_CDCLK | V_SA_CDCLK_CTL_CD2X_PIPE_SELECT_NONE | V_SA_CDCLK_CTL_CD_FREQ_DECIMAL_307_2;
        VoltageLevel = V_SA_GTTMMADR_MAILBOX_DATA_LOW_VOLTAGE_LEVEL_0;
        //
        // 307.2 Mhz cdclk is only supported for reference clock 19.2 and 38.4 Mhz.
        //
        if (ReferenceFreq == V_SA_CDCLK_PLL_REF_FREQUENCY_19_2MHZ) {
          CdClkPllRatio = V_SA_CDCLK_PLL_RATIO_307_2MHZ_REF_19_2MHZ;
        } else {
          CdClkPllRatio = V_SA_CDCLK_PLL_RATIO_307_2MHZ_REF_38_4MHZ;
        }
        break;

      case 1 :
        Data32Or = V_SA_CDCLK_CTL_CD2X_ALL_CDCLK | V_SA_CDCLK_CTL_CD2X_PIPE_SELECT_NONE | V_SA_CDCLK_CTL_CD_FREQ_DECIMAL_312;
        VoltageLevel = V_SA_GTTMMADR_MAILBOX_DATA_LOW_VOLTAGE_LEVEL_0;
        //
        // 312 Mhz cdclk is only supported for reference clock 24 Mhz
        //
        CdClkPllRatio = V_SA_CDCLK_PLL_RATIO_312MHZ_REF_24MHZ;
        break;

      case 2 :
        Data32Or = V_SA_CDCLK_CTL_CD2X_ALL_CDCLK | V_SA_CDCLK_CTL_CD2X_PIPE_SELECT_NONE | V_SA_CDCLK_CTL_CD_FREQ_DECIMAL_552;
        VoltageLevel = V_SA_GTTMMADR_MAILBOX_DATA_LOW_VOLTAGE_LEVEL_1;
        //
        // 552 Mhz cdclk is only supported for reference clock 24 Mhz
        //
        CdClkPllRatio = V_SA_CDCLK_PLL_RATIO_552MHZ_REF_24MHZ;
        break;

      case 3 :
        Data32Or = V_SA_CDCLK_CTL_CD2X_ALL_CDCLK | V_SA_CDCLK_CTL_CD2X_PIPE_SELECT_NONE | V_SA_CDCLK_CTL_CD_FREQ_DECIMAL_556_8;
        VoltageLevel = V_SA_GTTMMADR_MAILBOX_DATA_LOW_VOLTAGE_LEVEL_1;
        //
        // 556.8 Mhz cdclk is only supported for reference clock 19.2 and 38.4 Mhz.
        //
        if (ReferenceFreq == V_SA_CDCLK_PLL_REF_FREQUENCY_19_2MHZ) {
          CdClkPllRatio = V_SA_CDCLK_PLL_RATIO_556_8MHZ_REF_19_2MHZ;
        } else {
          CdClkPllRatio = V_SA_CDCLK_PLL_RATIO_556_8MHZ_REF_38_4MHZ;
        }
        break;

      case 4 :
        Data32Or = V_SA_CDCLK_CTL_CD2X_ALL_CDCLK | V_SA_CDCLK_CTL_CD2X_PIPE_SELECT_NONE | V_SA_CDCLK_CTL_CD_FREQ_DECIMAL_648;
        VoltageLevel = V_SA_GTTMMADR_MAILBOX_DATA_LOW_VOLTAGE_LEVEL_2;
        //
        // 648 Mhz cdclk is only supported for reference clock 24 Mhz
        //
        CdClkPllRatio = V_SA_CDCLK_PLL_RATIO_648MHZ_REF_24MHZ;
        break;

      case 5 :
        Data32Or = V_SA_CDCLK_CTL_CD2X_ALL_CDCLK | V_SA_CDCLK_CTL_CD2X_PIPE_SELECT_NONE | V_SA_CDCLK_CTL_CD_FREQ_DECIMAL_652_8;
        VoltageLevel = V_SA_GTTMMADR_MAILBOX_DATA_LOW_VOLTAGE_LEVEL_2;
        //
        // 652.8 Mhz cdclk is only supported for reference clock 19.2 and 38.4 Mhz.
        //
        if (ReferenceFreq == V_SA_CDCLK_PLL_REF_FREQUENCY_19_2MHZ) {
          CdClkPllRatio = V_SA_CDCLK_PLL_RATIO_652_8MHZ_REF_19_2MHZ;
        } else {
          CdClkPllRatio = V_SA_CDCLK_PLL_RATIO_652_8MHZ_REF_38_4MHZ;
        }
        break;

      case 0xFF :
        VoltageLevel = V_SA_GTTMMADR_MAILBOX_DATA_LOW_VOLTAGE_LEVEL_2;
        Data32Or = V_SA_CDCLK_CTL_CD2X_ALL_CDCLK | V_SA_CDCLK_CTL_CD2X_PIPE_SELECT_NONE;
        //
        // 648 Mhz cdclk is supported for reference clock 24 Mhz , 652.8 Mhz cdclk is supported for reference clock 19.2 and 38.4 Mhz.
        //
        if (ReferenceFreq == V_SA_CDCLK_PLL_REF_FREQUENCY_24MHZ) {
          Data32Or |= V_SA_CDCLK_CTL_CD_FREQ_DECIMAL_648;
          CdClkPllRatio = V_SA_CDCLK_PLL_RATIO_648MHZ_REF_24MHZ;
        } else if (ReferenceFreq == V_SA_CDCLK_PLL_REF_FREQUENCY_19_2MHZ) {
          Data32Or |= V_SA_CDCLK_CTL_CD_FREQ_DECIMAL_652_8;
          CdClkPllRatio = V_SA_CDCLK_PLL_RATIO_652_8MHZ_REF_19_2MHZ;
        } else {
          Data32Or |= V_SA_CDCLK_CTL_CD_FREQ_DECIMAL_652_8;
          CdClkPllRatio = V_SA_CDCLK_PLL_RATIO_652_8MHZ_REF_38_4MHZ;
        }
        break;

      default:
        return EFI_INVALID_PARAMETER;
    }
    //
    // Enable Display Power Well
    //
    EnablePowerWell (GttMmAdr);
    //
    // Inform Power control of upcoming frequency change
    //
    PollRunBusyClear (GttMmAdr, MAILBOX_TIMEOUT); // Poll run-busy before start

    while (WaitTime != 0) { //3ms loop
      MmioWrite32 (GttMmAdr + R_SA_GTTMMADR_MAILBOX_DATA_LOW_OFFSET, 0x00000003);  // mailbox_low       = 0x00000003
      MmioWrite32 (GttMmAdr + R_SA_GTTMMADR_MAILBOX_DATA_HIGH_OFFSET, 0x00000000); // mailbox_high      = 0x00000000
      MmioWrite32 (GttMmAdr + R_SA_GTTMMADR_MAILBOX_INTERFACE_OFFSET, 0x80000007); // mailbox Interface = 0x80000007
      PollRunBusyClear (GttMmAdr, MAILBOX_TIMEOUT);   // Poll Run Busy cleared
      //
      // Check for MailBox Data read status successful
      //
      if ((MmioRead32 (GttMmAdr + R_SA_GTTMMADR_MAILBOX_DATA_LOW_OFFSET) & BIT0) == 1) {
        DEBUG ((DEBUG_INFO, "Mailbox Data low read Successfull \n"));
        break;
      }
      MicroSecondDelay (MAILBOX_WAITTIME);
      WaitTime = WaitTime - MAILBOX_WAITTIME;
    }
    //
    // 3ms Timeout
    //
    if (WaitTime == 0) {
      DEBUG ((DEBUG_INFO, "CDCLK initialization failed , not changing CDCLK \n"));
    } else {
      DEBUG ((DEBUG_INFO, "Enabling CDCLK  \n"));
      //
      // Enable CDCLK PLL and change the CDCLK_CTL register
      //
      MmioAndThenOr32 (GttMmAdr + R_SA_GTTMMADR_CDCLK_PLL_ENABLE_OFFSET, B_SA_GTTMMADR_CDCLK_PLL_RATIO_MASK, CdClkPllRatio);
      MmioOr32 (GttMmAdr + R_SA_GTTMMADR_CDCLK_PLL_ENABLE_OFFSET, B_SA_CDCLK_PLL_ENABLE_BIT);
      PollGtReady (GttMmAdr, R_SA_GTTMMADR_CDCLK_PLL_ENABLE_OFFSET, B_SA_CDCLK_PLL_LOCK_BIT, B_SA_CDCLK_PLL_LOCK_BIT);
      MmioAndThenOr32 (GttMmAdr + R_SA_GTTMMADR_CDCLK_CTL_OFFSET, B_SA_GT_CD_CLK_FREQ_MASK, Data32Or);
      //
      //Inform Power controller of the selected freq
      //
      MmioWrite32 (GttMmAdr + R_SA_GTTMMADR_MAILBOX_DATA_LOW_OFFSET, VoltageLevel);
      MmioWrite32 (GttMmAdr + R_SA_GTTMMADR_MAILBOX_DATA_HIGH_OFFSET, 0x00000000);
      MmioWrite32 (GttMmAdr + R_SA_GTTMMADR_MAILBOX_INTERFACE_OFFSET, 0x80000007);
    }
  }
  return EFI_SUCCESS;
}

/**
Initialize GT Power management

  @param[in] GRAPHICS_PEI_PREMEM_CONFIG      GtPreMemConfig
  @param[in] GRAPHICS_PEI_CONFIG             GtConfig

  @retval EFI_SUCCESS          - GT Power management initialization complete
**/
EFI_STATUS
GraphicsPmInit (
  IN       GRAPHICS_PEI_PREMEM_CONFIG      *GtPreMemConfig,
  IN       GRAPHICS_PEI_CONFIG             *GtConfig
  )
{
  UINT32                LoGTBaseAddress;
  UINT32                HiGTBaseAddress;
  UINT64                McD2BaseAddress;
  UINT32                GttMmAdr;
  UINT32                GmAdr;
  UINT32                MchBarBase;
  UINT32                Msac;

  DEBUG ((DEBUG_INFO, " iGfx Initialization start.\n"));

  GttMmAdr   = 0;
  MchBarBase = 0;
  MchBarBase = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, R_SA_MCHBAR));
  MchBarBase = MchBarBase & (UINT32) ~BIT0;

  ///
  /// If device 0:2:0 (Internal Graphics Device, or GT) is enabled, then Program GTTMMADR,
  ///
  McD2BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, 0);
  if (PciSegmentRead16 (McD2BaseAddress + R_SA_IGD_VID) != 0xFFFF) {
    ///
    /// Program GT PM Settings if GttMmAdr allocation is Successful
    ///
    GttMmAdr                          = GtPreMemConfig->GttMmAdr;
    LoGTBaseAddress                   = (UINT32) (GttMmAdr & 0xFFFFFFFF);
    HiGTBaseAddress                   = 0;
    PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR, LoGTBaseAddress);
    PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR + 4, HiGTBaseAddress);

    Msac = PciSegmentRead32 (McD2BaseAddress + R_SA_IGD_MSAC_OFFSET);
    PciSegmentAndThenOr32 (McD2BaseAddress + R_SA_IGD_MSAC_OFFSET, (UINT32)~(BIT20 + BIT19 + BIT18 + BIT17 + BIT16), SA_GT_APERTURE_SIZE_256MB << 16);

    GmAdr = GtPreMemConfig->GmAdr;
    PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GMADR, GmAdr);

    if (!IgfxCmdRegEnabled()) {
      ///
      /// Enable Bus Master and Memory access on 0:2:0
      ///
      PciSegmentOr16 (McD2BaseAddress + R_SA_IGD_CMD, (BIT2 | BIT1));
    }

    ///
    /// Program GT frequency for GT SKU's only (not applicable on GT0)
    /// Note: User requested frequency takes precedence than DisableTurboGt
    ///
    if (!IsDisplayOnlySku()) {
      if ((GtConfig->DisableTurboGt == 1) && (GtConfig->GtFreqMax == 0xFF)) {
        ///
        /// Read bits[15:8] and limit the GtFrequency to Rp1
        ///
        MmioWrite8 ((MchBarBase + 0x5994), (UINT8)(((MmioRead32 (MchBarBase + 0x5998)) >> 0x8) & 0xFF));
        DEBUG ((DEBUG_INFO, "Disabling Turbo Gt - Programmed to frequency (in units of 50MHz): 0x%x \n", MmioRead8 (MchBarBase + 0x5994)));
      } else if (GtConfig->GtFreqMax != 0xFF) {
        ///
        /// Program user requested GT frequency
        ///
        MmioWrite8 ((MchBarBase + 0x5994), (UINT8) GtConfig->GtFreqMax);
        DEBUG ((DEBUG_INFO, "Max frequency programmed by user in MchBar 0x5994 is (to be multiplied by 50 for MHz): 0x%x  \n", MmioRead8 (MchBarBase + 0x5994)));
      }
    }

    ///
    /// PmInit Initialization
    ///
    DEBUG ((DEBUG_INFO, "Initializing GT PowerManagement\n"));
    PmInit (GtConfig, GttMmAdr, MchBarBase);

    ///
    /// Program CD clock value based on Policy
    ///
    ProgramCdClkReg (GtConfig, GttMmAdr);


    ///
    /// Clear GttMmAdr, GmAdr
    ///
    PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_MSAC_OFFSET, Msac);
  }
  DEBUG ((DEBUG_INFO, "iGfx Initialization end.\n"));
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
  Mirror System Agent registers.

  @param[in] GtPreMemConfig  Instance of GRAPHICS_PEI_PREMEM_CONFIG

  @retval EFI_SUCCESS     - SA Register Mirroring complete
**/
EFI_STATUS
SaRegisterMirror (
  IN       GRAPHICS_PEI_PREMEM_CONFIG             *GtPreMemConfig
  )
{
  UINT32        GttMmAdr;
  UINT16        Data16;
  UINT32        Data32;
  UINT64_STRUCT Data64;
  UINT64        McD0BaseAddress;
  UINT64        McD2BaseAddress;

  McD0BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, 0);
  McD2BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, 0);

  if (PciSegmentRead16 (McD2BaseAddress + R_SA_IGD_VID) == 0xFFFF) {
    DEBUG ((DEBUG_INFO, "\nSkip SA Register Mirror when iGFX is disabled \n"));
    return EFI_SUCCESS;
  }

  GttMmAdr = (PciSegmentRead32 (McD2BaseAddress + R_SA_IGD_GTTMMADR)) & 0xFFFFFFF0;

  if (GttMmAdr == 0) {
    GttMmAdr = GtPreMemConfig->GttMmAdr;
    PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR, (UINT32) (GttMmAdr & 0xFFFFFFFF));
    PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR + 4, 0);
  }

  if (!IgfxCmdRegEnabled()) {
    ///
    /// Enable Bus Master and Memory access on 0:2:0
    ///
    PciSegmentOr16 (McD2BaseAddress + R_SA_IGD_CMD, (BIT2 | BIT1));
  }

  // GGC
  DEBUG ((DEBUG_INFO, "Programming GGC\n"));
  Data16 = PciSegmentRead16 (McD0BaseAddress + R_SA_GGC);
  MmioWrite16 (GttMmAdr + R_SA_GTTMMADR_GGC_OFFSET, Data16);
  // TOUUD
  DEBUG ((DEBUG_INFO, "Programming TOUUD\n"));
  Data64.Data32.High = PciSegmentRead32 (McD0BaseAddress + R_SA_TOUUD + 4);
  Data64.Data32.Low  = PciSegmentRead32 (McD0BaseAddress + R_SA_TOUUD);
  MmioWrite64 (GttMmAdr + R_SA_GTTMMADR_TOUUD_OFFSET, Data64.Data);

  // TOLUD
  DEBUG ((DEBUG_INFO, "Programming TOLUD\n"));
  Data32 = PciSegmentRead32 (McD0BaseAddress + R_SA_TOLUD);
  MmioWrite32 (GttMmAdr + R_SA_GTTMMADR_TOLUD_OFFSET, Data32);

  // BDSM
  DEBUG ((DEBUG_INFO, "Programming BDSM\n"));
  Data64.Data = (UINT64) PciSegmentRead32 (McD0BaseAddress + R_SA_BDSM);
  DEBUG ((DEBUG_INFO, "Programming BDSM 0x%lx \n",Data64.Data ));
  MmioWrite64 (GttMmAdr + R_SA_GTTMMADR_BDSM_OFFSET, Data64.Data);

  // BGSM
  DEBUG ((DEBUG_INFO, "Programming BGSM\n"));
  Data64.Data = (UINT64) PciSegmentRead32 (McD0BaseAddress + R_SA_BGSM);
  DEBUG ((DEBUG_INFO, "Programming BGSM 0x%lx \n", Data64.Data));
  MmioWrite64 (GttMmAdr + R_SA_GTTMMADR_BGSM_OFFSET, Data64.Data);

  // TSEG
  DEBUG ((DEBUG_INFO, "Programming TSEG\n"));
  Data64.Data = (UINT64) PciSegmentRead32 (McD0BaseAddress + R_SA_TSEGMB);
  MmioWrite64 (GttMmAdr + R_SA_GTTMMADR_TSEGMB_OFFSET, Data64.Data);

  return EFI_SUCCESS;
}

/**
  Enables Power Well 1 for platform

  @param[in] GttMmAdr            - Base Address of IGFX MMIO BAR

  @retval EFI_SUCCESS            - Power well 1 Enabled
  @retval EFI_UNSUPPORTED        - Power well 1 programming Failed
  @retval EFI_TIMEOUT            - Timed out
**/
EFI_STATUS
EnablePowerWell1 (
  IN  UINT32     GttMmAdr
  )
{
  EFI_STATUS  Status;
  //
  // Poll for PG0 Fuse distribution status
  //
  Status = PollGtReady (GttMmAdr, R_SA_GTTMMADR_FUSE_STATUS_OFFSET, B_SA_GTTMMADR_FUSE_STATUS_PG0_DIST_STATUS, B_SA_GTTMMADR_FUSE_STATUS_PG0_DIST_STATUS);
  if (Status != EFI_SUCCESS) {
    return EFI_UNSUPPORTED;
  }
  //
  // Enable PG1
  //
  MmioOr32 (GttMmAdr + R_SA_GTTMMADR_PWR_WELL_CTL_OFFSET, B_SA_GTTMMADR_PWR_WELL_CTL_PG_1_ENABLE);
  //
  // Poll for PG1 state
  //
  Status = PollGtReady (GttMmAdr, R_SA_GTTMMADR_PWR_WELL_CTL_OFFSET, B_SA_GTTMMADR_PWR_WELL_CTL_PG_1_STATE, B_SA_GTTMMADR_PWR_WELL_CTL_PG_1_STATE);
  return Status;
}

/**
  Enables Power Well 2 for platform

  @param[in] GttMmAdr            - Base Address of IGFX MMIO BAR

  @retval EFI_SUCCESS            - Power well 2 Enabled
  @retval EFI_UNSUPPORTED        - Power well 2 programming Failed
  @retval EFI_TIMEOUT            - Timed out
**/
EFI_STATUS
EnablePowerWell2 (
  IN  UINT32     GttMmAdr
  )
{
  EFI_STATUS  Status;
  //
  // Poll Fuse PG1 distribution status
  //
  Status = PollGtReady (GttMmAdr, R_SA_GTTMMADR_FUSE_STATUS_OFFSET, B_SA_GTTMMADR_FUSE_STATUS_PG1_DIST_STATUS, B_SA_GTTMMADR_FUSE_STATUS_PG1_DIST_STATUS);
  if (Status != EFI_SUCCESS) {
    return EFI_UNSUPPORTED;
  }
  //
  // Enable PG2
  //
  MmioOr32 (GttMmAdr + R_SA_GTTMMADR_PWR_WELL_CTL_OFFSET, B_SA_GTTMMADR_PWR_WELL_CTL_PG_2_ENABLE);
  //
  // Poll for PG2 state
  //
  Status = PollGtReady (GttMmAdr, R_SA_GTTMMADR_PWR_WELL_CTL_OFFSET, B_SA_GTTMMADR_PWR_WELL_CTL_PG_2_STATE, B_SA_GTTMMADR_PWR_WELL_CTL_PG_2_STATE);
  return Status;
}

/**
  Enables Power Well 3 for platform

  @param[in] GttMmAdr            - Base Address of IGFX MMIO BAR

  @retval EFI_SUCCESS            - Power well 3 Enabled
  @retval EFI_UNSUPPORTED        - Power well 3 programming Failed
  @retval EFI_TIMEOUT            - Timed out
**/
EFI_STATUS
EnablePowerWell3 (
  IN  UINT32     GttMmAdr
  )
{
  EFI_STATUS  Status;
  //
  // Poll Fuse PG2 distribution status
  //
  Status = PollGtReady (GttMmAdr, R_SA_GTTMMADR_FUSE_STATUS_OFFSET, B_SA_GTTMMADR_FUSE_STATUS_PG2_DIST_STATUS, B_SA_GTTMMADR_FUSE_STATUS_PG2_DIST_STATUS);
  if (Status != EFI_SUCCESS) {
    return EFI_UNSUPPORTED;
  }
  //
  // Enable PG3
  //
  MmioOr32 (GttMmAdr + R_SA_GTTMMADR_PWR_WELL_CTL_OFFSET, B_SA_GTTMMADR_PWR_WELL_CTL_PG_3_ENABLE);
  //
  // Poll for PG3 state
  //
  Status = PollGtReady (GttMmAdr, R_SA_GTTMMADR_PWR_WELL_CTL_OFFSET, B_SA_GTTMMADR_PWR_WELL_CTL_PG_3_STATE, B_SA_GTTMMADR_PWR_WELL_CTL_PG_3_STATE);
  return Status;
}

/**
  Program the Display Power Wells supported by platform

  @param[in] GttMmAdr            - Base Address of IGFX MMIO BAR

  @retval EFI_SUCCESS            - Power well programming finished successfully
  @retval EFI_UNSUPPORTED        - Power well programming failed
  @retval EFI_TIMEOUT            - Timed out
**/
EFI_STATUS
EnablePowerWell (
  IN  UINT32     GttMmAdr
)
{
  EFI_STATUS        Status;

  DEBUG ((DEBUG_INFO, "EnablePowerWell Started !\n"));
  //
  // Enable the power well 1
  //
  Status = EnablePowerWell1 (GttMmAdr);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_WARN, "EnablePowerWell1 () has failed!\n"));
    return Status;
  }
  //
  // Enable power well 2
  //
  Status = EnablePowerWell2 (GttMmAdr);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_WARN, "EnablePowerWell2 () has failed!\n"));
    return Status;
  }

  //
  // Enable power well 3
  //
  Status = EnablePowerWell3 (GttMmAdr);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_WARN, "EnablePowerWell3 () has failed!\n"));
    return Status;
  }

  DEBUG ((DEBUG_INFO, "EnablePowerWell Successfull \n"));
  return EFI_SUCCESS;
}
