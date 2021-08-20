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
  // BaseAddr  Offset  AndMask  OrMask
  //
  //
  // Render/Video/Blitter Idle Max Count
  //
  {0x0,  0x2054,    0x0,  0xA},
  {0x0,  0x22054,   0x0,  0xA},
  {0x0,  0x1C2054,  0x0,  0xA},
  {0x0,  0x1C6054,  0x0,  0xA},
  {0x0,  0x1C8054,  0x0,  0xA},
  {0x0,  0x1D2054,  0x0,  0xA},
  {0x0,  0x1D6054,  0x0,  0xA},
  {0x0,  0xC3E4,    0x0,  0xA},
  {0x0,  0x1A054,   0x0,  0xA},

  //
  // Enable Idle Messages
  //
  {0x0,  0x2050,    0x0,  0x00010000},
  {0x0,  0x22050,   0x0,  0x00010000},
  {0x0,  0x1C2050,  0x0,  0x00010000},
  {0x0,  0x1C6050,  0x0,  0x00010000},
  {0x0,  0x1D2050,  0x0,  0x00010000},
  {0x0,  0x1D6050,  0x0,  0x00010000},
  {0x0,  0x18050,   0x0,  0x00010000},
  {0x0,  0x1A050,   0x0,  0x00010000},
  {0x0,  0x1C0050,  0x0,  0x00010000},
  {0x0,  0x1C8050,  0x0,  0x00010000},
  {0x0,  0x1D0050,  0x0,  0x00010000},
};

GLOBAL_REMOVE_IF_UNREFERENCED BOOT_SCRIPT_REGISTER_SETTING  gSaGtSecurityRegisters[] = {
  {0x0,  0x41A0,  0x0,         0x80040003},
  {0x0,  0x41A4,  0x0,         0x800507FC},
  {0x0,  0x41A8,  0x0,         0x800508D3},
  {0x0,  0x41AC,  0x0,         0x800BFFFC},
  {0x0,  0x41B0,  0x0,         0x80138001},
  {0x0,  0x41B4,  0x0,         0x8015FFFC},
  {0x0,  0x41B8,  0x0,         0x80190003},
  {0x0,  0x41BC,  0x0,         0x80197FFC},
  {0x0,  0x41C0,  0x7FFFFFFF,  0x80000000},
  {0x0,  0x41C4,  0x7FFFFFFF,  0x80000000},
  {0x0,  0x41C8,  0x7FFFFFFF,  0x80000000},
  {0x0,  0x41CC,  0x7FFFFFFF,  0x80000000},
  {0x0,  0x41D0,  0x7FFFFFFF,  0x80000000},
  {0x0,  0x41D4,  0x7FFFFFFF,  0x80000000},
  {0x0,  0x41D8,  0x7FFFFFFF,  0x80000000},
  {0x0,  0x41DC,  0x7FFFFFFF,  0x80000000}
};
GLOBAL_REMOVE_IF_UNREFERENCED UINT32 gSpcLock[] = {
  //
  // GTI
  //
  0x24008,
  //
  // Slice
  //
  0x24188,
  0x24190,
  0x2418C,
  //
  // Media Sampler
  //
  0x24A08,
  0x24A0C,
  0x24A10,
  //
  // Media -L
  //
  0x25208,
  0x2520C,
  0x25210,
  //
  // Media - R
  //
  0x25288,
  0x2528C,
  0x25290,
  //
  // HCP (Media - L)
  //
  0x25608,
  0x25610,
  0x2560C,
  //
  // HCP (Media - R)
  //
  0x25688,
  0x25690,
  0x2568C,
  //
  // MFXVDNC (Media - L)
  //
  0x25A08,
  0x25A10,
  0x25A0C,
  //
  // MFXVDNC (Media - R)
  //
  0x25A88,
  0x25A90,
  0x25A8C,
};

GLOBAL_REMOVE_IF_UNREFERENCED BOOT_SCRIPT_REGISTER_SETTING  gSaGtClockGatingRegisters[] = {
  //
  // BaseAddr  Offset  AndMask  OrMask
  //
  //
  //Unslice
  //
  {0x0,  0x9430,  0x0,  0x0},
  {0x0,  0x9434,  0x0,  0x0},
  {0x0,  0x9438,  0x0,  0x0},
  {0x0,  0x9440,  0x0,  0x0},
  {0x0,  0x9444,  0x0,  0x0},
  //
  //Slice
  //
  {0x0,  0x94D0,  0x0,  0x0},
  {0x0,  0x94D4,  0x0,  0x0},
  //
  //Subslice
  //
  {0x0,  0x9520,  0x0,  0x0},
  //
  //VE/VD Boxes
  //
  {0x0,  0x1C3F0C,  0x0,  0x0},
  {0x0,  0x1C7F0C,  0x0,  0x0},
  {0x0,  0x1D3F0C,  0x0,  0x0},
  {0x0,  0x1D7F0C,  0x0,  0x0},
};


/**
  Initialize GT PowerManagement of SystemAgent.

  @param[in] GtConfig            - Instance of GRAPHICS_PEI_CONFIG
  @param[in] GttMmAdr            - Base Address of IGFX MMIO BAR
  @param[in] MchBarBase          - Base Address of MCH_BAR

  @retval EFI_SUCCESS            - GT Power Management initialization complete
  @retval EFI_INVALID_PARAMETER  - The input parameter is invalid
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
  UINT32            Ssid;

  DEBUG ((DEBUG_INFO, "----- GT PMInit() Begin------\n"));

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
    //
    // Lock squash steps
    //
    RegOffset = 0x9584;
    Data32Or  = BIT31;
    Data32And = (UINT32) ~(BIT31);
    MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);
    //
    // Set squash step 1 to 16.667MHz and lock
    //
    RegOffset = 0x9588;
    Data32Or  = 0x80000001;
    Data32And = 0x7FFFFE00;
    MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);

    ///
    /// 1d. Enable Clock squashing based di/dt mitigation
    ///
    Data32Or = B_SA_GTTMMADR_PROCHOT_0_TEETH_BREAKING_EN | B_SA_GTTMMADR_PROCHOT_0_DIDT_LOCK_CONTROL;
    MmioOr32 (GttMmAdr + R_SA_GTTMMADR_PROCHOT_0_OFFSET, Data32Or);
    //
    // Set and lock RC1p frequency to 16.667Mhz.
    //
    RegOffset = 0xC14;
    Data32Or  = 0x80000001;
    MmioOr32 (GttMmAdr + RegOffset, Data32Or);
    //
    // Set RC1p hysteresis to 4096 SBclocks, 10us.
    //
    RegOffset = 0xC1C;
    Data32Or  = 0x00001000;
    MmioOr32 (GttMmAdr + RegOffset, Data32Or);
    //
    // Enable or disable RC1p.
    //
    RegOffset = 0xC18;
    Data32Or  = 0;
    if (GtConfig -> RC1pFreqEnable == 1) {
      Data32Or = 0x1;
    }
    MmioOr32 (GttMmAdr + RegOffset, Data32Or);

    ///
    /// 1e. Programming Crystal Clock.
    ///
    RegOffset = 0xD00;
    Data32    = MmioRead32 (GttMmAdr + RegOffset);
    ///
    /// Programm [2:1] = 11b if [5:3] is 001 (indicate ref clock is 19.2Mhz)
    /// Programm [2:1] = 10b if [5:3] is 000/010/011 (indicate ref clock is 24Mhz/38.4MHz/25MHz)
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
    /// 2a. Enable Force Wake
    ///
    RegOffset = 0xA188;
    Data32 = 0x00010001;
    MmioWrite32 (GttMmAdr + RegOffset, Data32);

    ///
    /// 2b. Poll to verify Force Wake Acknowledge Bit
    ///
    RegOffset = 0x130044;
    Data32Mask = BIT0;
    Result = 1;
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
    /// 5a. GPM Control
    ///
    RegOffset = 0xA180;
    Data32 = 0x81200000;
    MmioWrite32 (GttMmAdr + RegOffset, Data32);

    ///
    /// 5b. ECOBUS Disable Fence writes
    ///
    RegOffset = 0xA194;
    Data32Or = BIT5 | BIT7 | BIT8 | BIT31;
    MmioOr32 (GttMmAdr + RegOffset, Data32Or);

    ///
    /// 5b. Enable DOP clock gating.
    ///
    Data32 = 0xFFFFFFFF;

    RegOffset = 0x9424;
    MmioWrite32 (GttMmAdr + RegOffset, Data32);
    DEBUG ((DEBUG_INFO, "Enabled DOP clock gating \n"));

    ///
    /// 5c. Enable Unit Level Clock Gating
    ///
    for (LoopCounter = 0; LoopCounter < sizeof (gSaGtClockGatingRegisters) / sizeof (BOOT_SCRIPT_REGISTER_SETTING); ++LoopCounter) {
      RegOffset = gSaGtClockGatingRegisters[LoopCounter].Offset;
      Data32And = gSaGtClockGatingRegisters[LoopCounter].AndMask;
      Data32Or = gSaGtClockGatingRegisters[LoopCounter].OrMask;

      MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);
    }

    ///
    /// 5h. Disable LLC open poll.
    ///
    RegOffset = 0x9044;
    Data32 = 0xC0000000;
    MmioWrite32 (GttMmAdr + RegOffset, Data32);
    ///
    /// 6. RC6 Settings and 7. Enable Idle Messages from all *CS
    ///
    for (LoopCounter = 0; LoopCounter < sizeof (gSaGtRC6Registers) / sizeof (BOOT_SCRIPT_REGISTER_SETTING); ++LoopCounter) {
      RegOffset = gSaGtRC6Registers[LoopCounter].Offset;
      Data32And = gSaGtRC6Registers[LoopCounter].AndMask;
      Data32Or = gSaGtRC6Registers[LoopCounter].OrMask;

      MmioAndThenOr32 (GttMmAdr + RegOffset, Data32And, Data32Or);
    }
    ///
    /// 8a. Program GT Normal Frequency Request
    ///
    Data32 = 0x06000000;
    MmioWrite32 (GttMmAdr + 0xA008, Data32);

    ///
    /// 8b. RP Control.
    ///
    Data32 = 0x00000400;
    MmioWrite32 (GttMmAdr + 0xA024, Data32);

    ///
    /// 8c. Lock all SPC registers.
    ///
    ///
    /// Set slice and subslice steering to valid slices before reading SPC registers
    ///
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
    /// Sublice Slice 0 disabled, set 0xFDC[subslice select] = 1
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
    /// 9. Enabling to enter RC6 state in idle mode.
    ///
    Data32 = 0;
    if (GtConfig->RenderStandby) {
      RegOffset = 0xA094;
      Data32 = 0x00040000;
      MmioWrite32 (GttMmAdr + RegOffset, Data32);
      DEBUG ((DEBUG_INFO, "Entered RC6 state in idle mode\n"));
    }

    ///
    /// 10a. Clear offset 0xA188 [31:0] to clear the force wake enable
    ///
    RegOffset = 0xA188;
    Data32 = 0x00010000;
    MmioWrite32 (GttMmAdr + RegOffset, Data32);

    ///
    /// 10b. Poll until clearing is cleared to verify the force wake acknowledge.
    ///
    RegOffset = 0x130044;
    Data32Mask = BIT0;
    Result = 0;
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
    //MmioWrite32 (GttMmAdr + R_SA_GTTMMADR_PSMIBASE_OFFSET, (*PsmiBaseAddr & B_SA_PSMIBASE_LSB_MASK) | B_SA_PSMI_LOCK_MASK);

    MmioWrite32 (GttMmAdr + R_SA_GTTMMADR_PSMILIMIT_OFFSET + 4, *(PsmiLimitAddr + 1));
    //MmioWrite32 (GttMmAdr + R_SA_GTTMMADR_PSMILIMIT_OFFSET, (*PsmiLimitAddr & B_SA_PSMILIMIT_LSB_MASK) | B_SA_PSMI_LOCK_MASK);
  } /*else if (GtPreMemConfig->GtPsmiSupport == 0) {
    ///
    /// Program Non-Existent memony location for security when PSMI not in use.
    ///
    PsmiBase = 0xFFFFFFFFFFFFFFFF;
    PsmiBaseAddr = (UINT32 *) &PsmiBase;
    PsmiLimit = 0;
    PsmiLimitAddr = (UINT32 *) &PsmiLimit;
    ///
    /// Program PSMI Base and PSMI Limit and Lock.
    ///
    MmioWrite32 (GttMmAdr + R_SA_GTTMMADR_PSMIBASE_OFFSET + 4, *(PsmiBaseAddr + 1));
    MmioWrite32 (GttMmAdr + R_SA_GTTMMADR_PSMIBASE_OFFSET, (*PsmiBaseAddr & B_SA_PSMIBASE_LSB_MASK) | B_SA_PSMI_LOCK_MASK);

    MmioWrite32 (GttMmAdr + R_SA_GTTMMADR_PSMILIMIT_OFFSET + 4, *(PsmiLimitAddr + 1));
    MmioWrite32 (GttMmAdr + R_SA_GTTMMADR_PSMILIMIT_OFFSET, (*PsmiLimitAddr & B_SA_PSMILIMIT_LSB_MASK) | B_SA_PSMI_LOCK_MASK);
  }*/
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
    DEBUG ((DEBUG_INFO, "Initializing PAVP\n"));
    Pavpc &= (UINT32) ~(B_SA_PAVPC_HVYMODSEL_MASK | B_SA_PAVPC_PCMBASE_MASK | B_SA_PAVPC_PAVPE_MASK | B_SA_PAVPC_PCME_MASK);
    Pavpc &= (UINT32) ~(BIT8 | BIT7);
    //
    // Program PCM Base and size = 2MB
    //
    PcmBase = ((UINT32) RShiftU64 ((PciSegmentRead32 (McD0BaseAddress +R_SA_TOLUD)), 20)) - PAVP_PCM_SIZE_2_MB;
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
  /// For Gen12, CDCLK_CTL - GttMmAdr + 0x46000
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
    /// For Gen12, CDCLK_CTL - GttMmAdr + 0x46000
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
  DiSM support for 2LM Sku

  @param[in]  DismBase - Base address of DiSM range
  @param[in]  DismSize - Limit of DiSM range

  @retval EFI_SUCCESS           - DiSM initialization complete
  @retval EFI_INVALID_PARAMETER - The input parameter is invalid
  @retval EFI_NOT_FOUND         - SaPolicy or temporary GTT base address not found
**/
EFI_STATUS
DismInit (
  IN    UINT64    DismBase,
  IN    UINT64    DismLimit
  )
{
  UINT64                      McD2BaseAddress;
  SI_PREMEM_POLICY_PPI        *SiPreMemPolicyPpi;
  GRAPHICS_PEI_PREMEM_CONFIG  *GtPreMemConfig;
  UINTN                       GttMmAdr;
  EFI_STATUS                  Status;

  DEBUG ((DEBUG_INFO, "DiSM initialization DismLimit: 0x%lX  \n", DismLimit));
  DEBUG ((DEBUG_INFO, "DiSM initialization DismBase: 0x%lX  \n", DismBase));

  McD2BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, 0);

  if (PciSegmentRead16 (McD2BaseAddress + R_SA_IGD_VID) == 0xFFFF) {
    DEBUG ((DEBUG_INFO, "\nSkip DiSM initialization when iGFX is disabled \n"));
    return EFI_SUCCESS;
  }

  GttMmAdr = (PciSegmentRead32 (McD2BaseAddress + R_SA_IGD_GTTMMADR)) & 0xFFFFFFF0;

  if (GttMmAdr == 0) {
    ///
    /// Get SA Policy settings through the SaInitConfigBlock PPI
    ///
    Status = PeiServicesLocatePpi (
               &gSiPreMemPolicyPpiGuid,
               0,
               NULL,
               (VOID **) &SiPreMemPolicyPpi
               );
    if (EFI_ERROR (Status) || (SiPreMemPolicyPpi == NULL)) {
      DEBUG ((DEBUG_WARN, "SaPolicy PPI not found - Exit!\n"));
      return EFI_NOT_FOUND;
    }

    Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gGraphicsPeiPreMemConfigGuid, (VOID *) &GtPreMemConfig);
    ASSERT_EFI_ERROR (Status);

    GttMmAdr = GtPreMemConfig->GttMmAdr;

    if (GttMmAdr == 0) {
      DEBUG ((DEBUG_WARN, "Temporary GttMmAdr Bar is not initialized - Exit!\n"));
      return EFI_NOT_FOUND;
    }

    ///
    /// Program and read back GTT Memory Mapped BAR
    ///
    PciSegmentWrite32 (McD2BaseAddress + R_SA_IGD_GTTMMADR, (UINT32) (GttMmAdr & 0xFF000000));
    GttMmAdr = (PciSegmentRead32 (McD2BaseAddress + R_SA_IGD_GTTMMADR)) & 0xFFFFFFF0;
  }

  if (!IgfxCmdRegEnabled()) {
    ///
    /// Enable Bus Master and Memory access on 0:2:0
    ///
    PciSegmentOr16 (McD2BaseAddress + R_SA_IGD_CMD, (BIT2 | BIT1));
  }

  ///
  /// Programming DiSM Limit
  ///
  DEBUG ((DEBUG_INFO, "Programming DiSM Limit\n"));
  MmioWrite32 (GttMmAdr + R_SA_GTTMMADR_DISM_LIMIT_LSB_OFFSET, (UINT32) (DismLimit & 0xFFFFFFFF));
  MmioWrite32 (GttMmAdr + R_SA_GTTMMADR_DISM_LIMIT_MSB_OFFSET, (UINT32) (RShiftU64 (DismLimit, 32)));

  ///
  /// Programming DiSM Base
  ///
  DEBUG ((DEBUG_INFO, "Programming DiSM Base\n"));
  MmioWrite32 (GttMmAdr + R_SA_GTTMMADR_DISM_BASE_LSB_OFFSET, (UINT32) (DismBase & 0xFFFFFFFF));
  MmioWrite32 (GttMmAdr + R_SA_GTTMMADR_DISM_BASE_MSB_OFFSET, (UINT32) (RShiftU64 (DismBase, 32)));

  DEBUG((DEBUG_INFO, "All DiSM register programming done. Exiting.\n"));
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
