/** @file
  Power Management EarlyPost initializations.

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

@par Specification
**/

#include <Ppi/SiPolicy.h>
#include <Library/CpuPlatformLib.h>
#include <Library/CpuMailboxLib.h>
#include <Library/CpuCommonLib.h>
#include <Library/PeiOcLib.h>
#include <Library/BiosGuardInit.h>
#include <Library/ConfigBlockLib.h>
#include "Features.h"
#include <Library/PostCodeLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PeiPmcPrivateLib.h>
#include <SaCommonDefinitions.h>

///
/// Table to convert MilliSeconds into equivalent MSR values
/// This table is used for VR TDC Time Window programming
/// 9ms does not have a unique encoding, so use 10ms encoding.
///
GLOBAL_REMOVE_IF_UNREFERENCED UINT8 mMilliSecondsToMsrValueTable[][2] = {
  ///
  ///  MilliSeconds   MSR Value
  ///
  {        0,         0x00     },
  {        1,         0x00     },
  {        2,         0x01     },
  {        3,         0x41     },
  {        4,         0x02     },
  {        5,         0x22     },
  {        6,         0x42     },
  {        7,         0x62     },
  {        8,         0x03     },
  {        9,         0x23     },
  {       10,         0x23     }
};

GLOBAL_REMOVE_IF_UNREFERENCED CPU_VR_OVERRIDE_TABLE mCpuVrOverrideTable[]={
///
/// Cpu Identifier                   IaIccMax GtIccMax SaIccMax VccIcc IaTdc GtTdc SaTdc VccTdc IaAcLL IaDcLL GtAcLL GtDcLL SaAcLL SaDcLL     VccAc      VccDc   VccIn
///                                   1/4A     1/4A     1/4A     1/4A   1/8A  1/8A  1/8A  1/8A   1/100 mOhm                                 1/100mOhm  1/100mOhm Limit
  { EnumWhlU15Watt42fCpuId,           4*70,    4*31,     4*6,       0,   8*42, 8*18,  8*4,    0,    240,   240,   310,   310,  1030,  1030,       0,        0,     0},
  { EnumWhlU15Watt22fCpuId,           4*35,    4*31,     4*6,       0,   8*24, 8*18,    0,    0,    240,   240,   310,   310,  1030,  1030,       0,        0,     0},
  { EnumWhlU15Watt2f1fCpuId,          4*35,    4*31,     4*6,       0,   8*24, 8*18,    0,    0,    240,   240,   310,   310,  1030,  1030,       0,        0,     0},
  { EnumTglY9WattES1NoExsCpuId,          0,       0,       0,    42*4,      0,    0,    0,  27*8,      0,     0,     0,     0,    0,      0,     540,      200,    0},
  { EnumTglY9WattES1ExsCpuId,            0,       0,       0,    53*4,      0,    0,    0,  27*8,      0,     0,     0,     0,    0,      0,     330,      200,    0},
  { EnumTglY9Watt42fNoExsCpuId,          0,       0,       0,    42*4,      0,    0,    0,  27*8,      0,     0,     0,     0,    0,      0,     540,      200,    0},
  { EnumTglY9Watt42fExsCpuId,            0,       0,       0,    53*4,      0,    0,    0,  27*8,      0,     0,     0,     0,    0,      0,     330,      200,    0},
  { EnumTglU28WattES1CTdpNoExsCpuId,     0,       0,       0,    55*4,      0,    0,    0,  36*8,      0,     0,     0,     0,    0,      0,     440,      200,    0},
  { EnumTglU28WattES1CTdpExsCpuId,       0,       0,       0,    68*4,      0,    0,    0,  36*8,      0,     0,     0,     0,    0,      0,     270,      200,    0},
  { EnumTglU28Watt42fCTdpNoExsCpuId,     0,       0,       0,    55*4,      0,    0,    0,  36*8,      0,     0,     0,     0,    0,      0,     440,      200,    0},
  { EnumTglU28Watt42fCTdpExsCpuId,       0,       0,       0,    68*4,      0,    0,    0,  36*8,      0,     0,     0,     0,    0,      0,     270,      200,    0},
  { EnumTglU28Watt42fNoExsCpuId,         0,       0,       0,    71*4,      0,    0,    0,  48*8,      0,     0,     0,     0,    0,      0,     440,      200,    0},
  { EnumTglU28Watt42fExsCpuId,           0,       0,       0,    76*4,      0,    0,    0,  48*8,      0,     0,     0,     0,    0,      0,     246,      200,    0},
  { EnumTglU28WattES1NoExsCpuId,         0,       0,       0,    71*4,      0,    0,    0,  48*8,      0,     0,     0,     0,    0,      0,     440,      200,    0},
  { EnumTglU28WattES1ExsCpuId,           0,       0,       0,    76*4,      0,    0,    0,  48*8,      0,     0,     0,     0,    0,      0,     246,      200,    0},
  { EnumTglH45Watt81NoExsCpuId,          0,       0,       0,   169*4,      0,    0,    0, 110*8,      0,     0,     0,     0,    0,      0,     200,      200,    0}, //LL data WIP
  { EnumTglH65Watt81NoExsCpuId,          0,       0,       0,   191*4,      0,    0,    0, 128*8,      0,     0,     0,     0,    0,      0,     200,      200,    0}, //LL data WIP
  { EnumTglH95Watt81NoExsCpuId,          0,       0,       0,   191*4,      0,    0,    0, 128*8,      0,     0,     0,     0,    0,      0,     200,      200,    0}, //LL data WIP
  { EnumTglH45Watt81ExsCpuId,            0,       0,       0,   206*4,      0,    0,    0, 110*8,      0,     0,     0,     0,    0,      0,     200,      200,    0}, //LL data WIP
  { EnumTglH65Watt81ExsCpuId,            0,       0,       0,   228*4,      0,    0,    0, 128*8,      0,     0,     0,     0,    0,      0,     200,      200,    0}, //LL data WIP
  { EnumTglH95Watt81ExsCpuId,            0,       0,       0,   228*4,      0,    0,    0, 128*8,      0,     0,     0,     0,    0,      0,     200,      200,    0}, //LL data WIP
};

/**
  Based on ResetType, perform warm or cold reset using PCH reset PPI.

  @param[in] ResetType    - CPU_RESET_TYPE to indicate which reset should be performed.

  @retval EFI_SUCCESS     - Function successful (system should already reset).
  @retval EFI_UNSUPPORTED - Reset type unsupported.
**/
EFI_STATUS
PerformWarmOrColdReset (
  IN CPU_RESET_TYPE ResetType
  )
{
  EFI_STATUS                 Status;

  Status = EFI_SUCCESS;

  ///
  /// Perform the requested reset using EFI RESET2 PeiService.
  ///
  switch (ResetType) {
    case COLD_RESET:
     (*GetPeiServicesTablePointer ())->ResetSystem2 (EfiResetCold, EFI_SUCCESS, 0, NULL);
      break;

    case WARM_RESET:
     (*GetPeiServicesTablePointer ())->ResetSystem2 (EfiResetWarm, EFI_SUCCESS, 0, NULL);
      break;

    default:
      DEBUG ((DEBUG_ERROR, "CpuInitPreResetCpl: PerformWarmOrColdReset - ResetType %d not supported: \n", ResetType));
      Status = EFI_UNSUPPORTED;
      ASSERT_EFI_ERROR (Status);
  }

  return Status;
}

/**
  Program Tcc Activation Offset and  Running Average Temperature Limit (RATL).

  @param[in] SiPolicyPpi    - The SI Policy PPI instance
**/
VOID
InitRatl (
  IN SI_POLICY_PPI *SiPolicyPpi
  )
{
  MSR_REGISTER                TempMsr;
  BOOLEAN                     IsTccActivationOffsetProgrammable;
  CPU_POWER_MGMT_BASIC_CONFIG *CpuPowerMgmtBasicConfig;
  BOOLEAN                     IsTimeWindowInSeconds;
  UINT8                       ConvertedTccOffsetTime;
  EFI_STATUS                  Status;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuPowerMgmtBasicConfigGuid, (VOID *) &CpuPowerMgmtBasicConfig);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Read Temperature Target MSR
  ///
  TempMsr.Qword = AsmReadMsr64 (MSR_TEMPERATURE_TARGET);

  ///
  /// Check Tcc Activation Offset Programmable Setting from Platform Info MSR Bits[30]
  ///
  IsTccActivationOffsetProgrammable = (AsmReadMsr64 (MSR_PLATFORM_INFO) & B_MSR_PLATFORM_INFO_PRG_TJ_OFFSET_EN_MASK) != 0;
  DEBUG ((DEBUG_INFO,"TCC activation programmable = %x\n", IsTccActivationOffsetProgrammable));

  ///
  /// If TccActivationOffset is greater than max supported value, set it to max value.
  ///
  if (CpuPowerMgmtBasicConfig->TccActivationOffset > V_MSR_TEMPERATURE_TARGET_TCC_ACTIVATION_OFFSET_MASK) {
      CpuPowerMgmtBasicConfig->TccActivationOffset = V_MSR_TEMPERATURE_TARGET_TCC_ACTIVATION_OFFSET_MASK;
  }

  ///
  /// First check if TCC Activation Offset is programmable based on PLATFORM INFO MSR [30]
  /// If TCC activation offset is not programmable, skip programming TEMPERATURE_TARGET MSR.
  /// If TCC Activation Offset is programable, program the TCC Activation offset value
  /// from Policy, and the Tcc activation offset programming should be dependent on RESET_CPL done.
  ///
  if (IsTccActivationOffsetProgrammable) {
    TempMsr.Dwords.Low &= ~(UINT32) LShiftU64 (V_MSR_TEMPERATURE_TARGET_TCC_ACTIVATION_OFFSET_MASK, N_MSR_TEMPERATURE_TARGET_TJ_MAX_TCC_OFFSET_OFFSET);
    CpuPowerMgmtBasicConfig->TccActivationOffset &= V_MSR_TEMPERATURE_TARGET_TCC_ACTIVATION_OFFSET_MASK;
    TempMsr.Dwords.Low |= (UINT32) LShiftU64 (CpuPowerMgmtBasicConfig->TccActivationOffset, N_MSR_TEMPERATURE_TARGET_TJ_MAX_TCC_OFFSET_OFFSET);

    ///
    /// Running Average Temperature Limit (RATL) permits advanced thermal management with bursts of excursion above Tjmax
    /// while maintaining the overall average temperature.
    ///
    IsTimeWindowInSeconds = (CpuPowerMgmtBasicConfig->TccOffsetTimeWindowForRatl / 1000) >= 1;
    if (IsTimeWindowInSeconds) {
      ConvertedTccOffsetTime = GetConvertedTime ((CpuPowerMgmtBasicConfig->TccOffsetTimeWindowForRatl / 1000), SecondsTimeWindowConvert);
    } else {
      ConvertedTccOffsetTime = GetConvertedTime (CpuPowerMgmtBasicConfig->TccOffsetTimeWindowForRatl, MilliSecondsTimeWindowConvert);
    }
    TempMsr.Bytes.FirstByte = 0;
    TempMsr.Dwords.Low &= ~B_MSR_TEMPERATURE_TARGET_LOCKED_MASK;
    if (CpuPowerMgmtBasicConfig->TccOffsetTimeWindowForRatl != 0) {
      ///
      /// Get converted time window based on setting of policy
      ///
      TempMsr.Bytes.FirstByte |= (ConvertedTccOffsetTime & B_MSR_TEMPERATURE_TARGET_TCC_OFFSET_TIME_WINDOW_MASK);
    }

    ///
    /// When Clamp enable bit set, allow throttling below P1.
    ///
    TempMsr.Bytes.FirstByte &= ~B_MSR_TEMPERATURE_TARGET_TCC_OFFSET_CLAMPING_BIT_MASK;
    if (CpuPowerMgmtBasicConfig->TccOffsetClamp) {
      TempMsr.Bytes.FirstByte |= B_MSR_TEMPERATURE_TARGET_TCC_OFFSET_CLAMPING_BIT_MASK;
    }

    ///
    /// Lock the MSR by setting BIT31 of MSR 1A2h.
    ///
    TempMsr.Dwords.Low &= ~B_MSR_TEMPERATURE_TARGET_LOCKED_MASK;
    if (CpuPowerMgmtBasicConfig->TccOffsetLock) {
      TempMsr.Dwords.Low |= B_MSR_TEMPERATURE_TARGET_LOCKED_MASK;
    }

    ///
    /// Write Temperature Target MSR
    ///
    AsmWriteMsr64 (MSR_TEMPERATURE_TARGET, TempMsr.Qword);
  }

  return;
}

/**
  Programs the FIVR RFI settings based on XTAL clock frequency.

  @param[IN] CpuPowerMgmtVrConfig  - CPU Power Management VR Config Block
**/
VOID
UpdateFivrRfiSettings (
  IN CPU_POWER_MGMT_VR_CONFIG *CpuPowerMgmtVrConfig
  )
{
  UINTN                       MchBar;
  UINT32                      RfiData;
  UINT32                      RegEcx;
  UINT16                      RfiValue;
  UINT16                      DoubledValue;
  UINT8                       RfiLowBits;
  UINT8                       RfiHighByte;
  UINT8                       LowOffset;
  UINT8                       HighOffset;
  UINT32                      RfiMask;
  UINT32                      SpreadSpectrumData;
  UINT8                       EncodedSpectrum;

  MchBar = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MCHBAR)) & ~BIT0;

  if (CpuPowerMgmtVrConfig->FivrSpreadSpectrum != 0) {
    //
    // Sets clock spectrum spread percentage:
    // 0x00=0.2% , 0x3F=10%
    // 1 LSB = 0.1% increase in spread (for settings 0x01 thru 0x1C)
    // 1 LSB = 0.2% increase in spread (for settings 0x1E thru 0x3F)
    // The bit[7:6] are not used.
    //
    EncodedSpectrum = 0;
    if (CpuPowerMgmtVrConfig->FivrSpreadSpectrum > 2) {
      EncodedSpectrum = CpuPowerMgmtVrConfig->FivrSpreadSpectrum - 2;
      if (EncodedSpectrum > V_SPREAD_SPECTRUM_POINT_ONE_ENCODING_MAX) {
        EncodedSpectrum = EncodedSpectrum - V_SPREAD_SPECTRUM_POINT_ONE_ENCODING_MAX;
        EncodedSpectrum = EncodedSpectrum / 2;
        EncodedSpectrum = EncodedSpectrum + V_SPREAD_SPECTRUM_POINT_ONE_ENCODING_MAX;
        if (EncodedSpectrum > V_FIVR_SPREAD_SPECTRUM_MAX) {
          EncodedSpectrum = V_FIVR_SPREAD_SPECTRUM_MAX;
        }
      }
    }

    //
    // Write the Spread Spectrum value.
    //
    SpreadSpectrumData = MmioRead32 (MchBar + R_EMI_CONTROL_0_0_0_MCHBAR_PCU);
    SpreadSpectrumData = (SpreadSpectrumData & ~B_SPREAD_SPECTRUM_MASK);
    SpreadSpectrumData = SpreadSpectrumData | EncodedSpectrum;
    SpreadSpectrumData = SpreadSpectrumData | B_SPREAD_SPECTRUM_ENABLE;
    MmioWrite32 ((MchBar + R_EMI_CONTROL_0_0_0_MCHBAR_PCU), SpreadSpectrumData);

    //
    // Update PCH FIVR RFI setting based on RFIControl0/EMIControl0
    // settings on CPU side
    // @todo Clear reserved bits
    //
    PmcConfigureFivrEmiControl0 (SpreadSpectrumData);
  }

  if (CpuPowerMgmtVrConfig->FivrRfiFrequency != 0) {
    ///
    /// Determine XTAL clock frequency
    ///
    AsmCpuid(CPUID_TIME_STAMP_COUNTER, NULL, NULL, &RegEcx, NULL);

    ///
    /// RfiValue = Policy->RfiFreq * 100KHz * (128/ClockInKhz).
    ///
    if (RegEcx == CLOCK_FREQUENCY_19MHz) {
	  RfiData = MmioRead32 (MchBar + R_RFI_CONTROL2_0_0_0_MCHBAR_PCU);
      //
      // RfiValue = Config->RfiFreq * 12800 / 19200.
      // RfiValue = Config->RfiFreq * 2 / 3.
      // Round to nearest by doubling before dividing by 3, then add 1 to the result and divide by 2.
      //
      DoubledValue = (CpuPowerMgmtVrConfig->FivrRfiFrequency * 4) / 3;
      RfiValue = (DoubledValue + 1) / 2;
      //
      // Set offsets and mask based on clock.
      //
      LowOffset = N_RFI_FREQ_LO_PF1_OFFSET;
      HighOffset = N_RFI_FREQ_HI_PF1_OFFSET;
      RfiMask = B_RFI_FREQ_PF1_MASK;
    } else if (RegEcx == CLOCK_FREQUENCY_38MHz) {
      RfiData = MmioRead32 (MchBar + R_RFI_CONTROL2_0_0_0_MCHBAR_PCU);
      //
      // RfiValue = Config->RfiFreq * 12800 / 38400.
      // RfiValue = Config->RfiFreq * 1 / 3.
      // Round to nearest by doubling before dividing by 3, then add 1 to the result and divide by 2.
      //
      DoubledValue = (CpuPowerMgmtVrConfig->FivrRfiFrequency * 2) / 3;
      RfiValue = (DoubledValue + 1) / 2;


      //
      // Set offsets and mask based on clock.
      //
      LowOffset = N_RFI_FREQ_LO_PF3_OFFSET;
      HighOffset = N_RFI_FREQ_HI_PF3_OFFSET;
      RfiMask = B_RFI_FREQ_PF3_MASK;
    } else if (RegEcx == CLOCK_FREQUENCY_24MHz) {
      RfiData = MmioRead32 (MchBar + R_RFI_CONTROL_0_0_0_MCHBAR_PCU);
      //
      // RfiValue = Config->RfiFreq * 12800 / 24000.
      // RfiValue = Config->RfiFreq * 8 / 15.
      // Round to nearest by doubling before dividing by 15, then add 1 to the result and divide by 2.
      //
      DoubledValue = (CpuPowerMgmtVrConfig->FivrRfiFrequency * 16) / 15;
      RfiValue = (DoubledValue + 1) / 2;

      //
      // Set offsets and mask based on clock.
      //
      LowOffset = N_RFI_FREQ_LO_PF2_OFFSET;
      HighOffset = N_RFI_FREQ_HI_PF2_OFFSET;
      RfiMask = B_RFI_FREQ_PF2_MASK;
    } else {
      DEBUG ((DEBUG_ERROR, "Unexpected Clock Frequency! RegEcx: %d\n", RegEcx));
      return;
    }

    if (RfiValue > V_MAX_RFI_VALUE) {
      RfiValue = V_MAX_RFI_VALUE;
    }

    RfiData = (RfiData & ~RfiMask);
    RfiLowBits = (RfiValue & (BIT1 | BIT0));
    RfiHighByte = (UINT8) (RfiValue >> 2);
    RfiData = RfiData | (UINT32) (RfiLowBits << LowOffset);
    RfiData = RfiData | (UINT32) (RfiHighByte << HighOffset);
    MmioWrite32 ((MchBar + R_RFI_CONTROL_0_0_0_MCHBAR_PCU), RfiData);

    //
    // Update PCH FIVR RFI setting based on RFIControl0/EMIControl0
    // settings on CPU side
    // @todo Clear reserved bits
    //
    PmcConfigureFivrRfiControl4 (RfiData);
  }
}

/**
  Updates the Vr Config block with Intel default override values if needed

  @param[IN] CpuPowerMgmtVrConfig  - CPU Power Management VR Config Block
**/
VOID
UpdateVrOverrides (
  IN CPU_POWER_MGMT_VR_CONFIG *CpuPowerMgmtVrConfig
  )
{
  UINTN                      TableIndex;
  UINTN                      NoOfOverrides;
  CPU_VR_OVERRIDE_TABLE      *VrOverrideTable;
  CPU_OVERRIDE_IDENTIFIER    CpuIdentifier;

  VrOverrideTable = mCpuVrOverrideTable;
  NoOfOverrides = 0;
  ///
  /// Get CpuIdentifier to identify which set of VR values we need to override
  ///
  CpuIdentifier = GetCpuIdentifier ();
  DEBUG ((DEBUG_INFO, "VR: Cpu Identifier = %X\n", CpuIdentifier));
  if (CpuIdentifier == EnumUnknownCpuId) {
    DEBUG ((DEBUG_ERROR, "VR: Unknown Cpu Identifier, bypassing VR overrides.\n"));
    return;
  }

  ///
  /// Update the VR config block with the VR override table data.
  /// Only override if the config block value is AUTO/default and the
  /// override table data is non-zero.
  ///
  if (sizeof (CPU_VR_OVERRIDE_TABLE) != 0){
    NoOfOverrides = (sizeof (mCpuVrOverrideTable)) / (sizeof (CPU_VR_OVERRIDE_TABLE));
  }

  for (TableIndex = 0; TableIndex < NoOfOverrides; TableIndex++, VrOverrideTable++) {
    ///
    /// If Cpu Identifier matches, then update with overrides values
    ///
    if (VrOverrideTable->CpuIdentifier == CpuIdentifier) {
      ///
      /// ICC Max Overrides. Only override default if left at AUTO.
      ///
      if ((CpuPowerMgmtVrConfig->IccMax[CPU_VR_DOMAIN_IA] == AUTO) && (VrOverrideTable->IaIccMax != 0)) {
        CpuPowerMgmtVrConfig->IccMax[CPU_VR_DOMAIN_IA] = VrOverrideTable->IaIccMax;
      }
      if ((CpuPowerMgmtVrConfig->IccMax[CPU_VR_DOMAIN_GT] == AUTO) && (VrOverrideTable->GtIccMax != 0)) {
        CpuPowerMgmtVrConfig->IccMax[CPU_VR_DOMAIN_GT] = VrOverrideTable->GtIccMax;
      }
      if ((CpuPowerMgmtVrConfig->IccMax[CPU_VR_DOMAIN_SA] == AUTO) && (VrOverrideTable->SaIccMax != 0)) {
        CpuPowerMgmtVrConfig->IccMax[CPU_VR_DOMAIN_SA] = VrOverrideTable->SaIccMax;
      }
      if ((CpuPowerMgmtVrConfig->IccMax[CPU_VR_DOMAIN_FIVR] == AUTO) && (VrOverrideTable->VccInIccMax != 0)) {
        CpuPowerMgmtVrConfig->IccMax[CPU_VR_DOMAIN_FIVR] = VrOverrideTable->VccInIccMax;
      }

      ///
      /// VR TDC Overrides. Only override default if left at AUTO.
      ///
      if ((CpuPowerMgmtVrConfig->TdcCurrentLimit[CPU_VR_DOMAIN_IA] == AUTO) && (VrOverrideTable->IaTdclimit != 0)) {
        CpuPowerMgmtVrConfig->TdcCurrentLimit[CPU_VR_DOMAIN_IA] = VrOverrideTable->IaTdclimit;
        CpuPowerMgmtVrConfig->TdcEnable[CPU_VR_DOMAIN_IA] = 1;
      }
      if ((CpuPowerMgmtVrConfig->TdcCurrentLimit[CPU_VR_DOMAIN_GT] == AUTO) && (VrOverrideTable->GtTdclimit != 0)) {
        CpuPowerMgmtVrConfig->TdcCurrentLimit[CPU_VR_DOMAIN_GT] = VrOverrideTable->GtTdclimit;
        CpuPowerMgmtVrConfig->TdcEnable[CPU_VR_DOMAIN_GT] = 1;
      }
      if ((CpuPowerMgmtVrConfig->TdcCurrentLimit[CPU_VR_DOMAIN_SA] == AUTO) && (VrOverrideTable->SaTdclimit != 0)) {
        CpuPowerMgmtVrConfig->TdcCurrentLimit[CPU_VR_DOMAIN_SA] = VrOverrideTable->SaTdclimit;
        CpuPowerMgmtVrConfig->TdcEnable[CPU_VR_DOMAIN_SA] = 1;
      }
      if ((CpuPowerMgmtVrConfig->TdcCurrentLimit[CPU_VR_DOMAIN_FIVR] == AUTO) && (VrOverrideTable->VccInTdclimit != 0)) {
        CpuPowerMgmtVrConfig->TdcCurrentLimit[CPU_VR_DOMAIN_FIVR] = VrOverrideTable->VccInTdclimit;
        CpuPowerMgmtVrConfig->TdcEnable[CPU_VR_DOMAIN_FIVR] = 1;
      }

      ///
      /// AC/DC Loadlines. Only override default if left at AUTO.
      ///
      if ((CpuPowerMgmtVrConfig->AcLoadline[CPU_VR_DOMAIN_IA] == AUTO) && (VrOverrideTable->IaAcLoadLine != 0)) {
        CpuPowerMgmtVrConfig->AcLoadline[CPU_VR_DOMAIN_IA] = VrOverrideTable->IaAcLoadLine;
      }
      if ((CpuPowerMgmtVrConfig->DcLoadline[CPU_VR_DOMAIN_IA] == AUTO) && (VrOverrideTable->IaDcLoadLine != 0)) {
        CpuPowerMgmtVrConfig->DcLoadline[CPU_VR_DOMAIN_IA] = VrOverrideTable->IaDcLoadLine;
      }
      if ((CpuPowerMgmtVrConfig->AcLoadline[CPU_VR_DOMAIN_GT] == AUTO)  && (VrOverrideTable->GtAcLoadLine != 0)) {
        CpuPowerMgmtVrConfig->AcLoadline[CPU_VR_DOMAIN_GT] = VrOverrideTable->GtAcLoadLine;
      }
      if ((CpuPowerMgmtVrConfig->DcLoadline[CPU_VR_DOMAIN_GT] == AUTO) && (VrOverrideTable->GtDcLoadLine != 0)) {
        CpuPowerMgmtVrConfig->DcLoadline[CPU_VR_DOMAIN_GT] = VrOverrideTable->GtDcLoadLine;
      }
      if ((CpuPowerMgmtVrConfig->AcLoadline[CPU_VR_DOMAIN_SA] == AUTO) && (VrOverrideTable->SaAcLoadLine != 0)) {
        CpuPowerMgmtVrConfig->AcLoadline[CPU_VR_DOMAIN_SA] = VrOverrideTable->SaAcLoadLine;
      }
      if ((CpuPowerMgmtVrConfig->DcLoadline[CPU_VR_DOMAIN_SA] == AUTO) && (VrOverrideTable->SaDcLoadLine != 0)) {
        CpuPowerMgmtVrConfig->DcLoadline[CPU_VR_DOMAIN_SA] = VrOverrideTable->SaDcLoadLine;
      }
      if ((CpuPowerMgmtVrConfig->AcLoadline[CPU_VR_DOMAIN_FIVR] == AUTO) && (VrOverrideTable->VccInAcLoadLine != 0)) {
        CpuPowerMgmtVrConfig->AcLoadline[CPU_VR_DOMAIN_FIVR] = VrOverrideTable->VccInAcLoadLine;
      }
      if ((CpuPowerMgmtVrConfig->DcLoadline[CPU_VR_DOMAIN_FIVR] == AUTO) && (VrOverrideTable->VccInDcLoadLine != 0)) {
        CpuPowerMgmtVrConfig->DcLoadline[CPU_VR_DOMAIN_FIVR] = VrOverrideTable->VccInDcLoadLine;
      }

      ///
      ///  VccIn VR Voltage Limit. Only override if default is left at AUTO.
      ///
      if ((CpuPowerMgmtVrConfig->VrVoltageLimit[CPU_VR_DOMAIN_FIVR] == AUTO) && (VrOverrideTable->VrVoltageLimit != 0)) {
        CpuPowerMgmtVrConfig->VrVoltageLimit[CPU_VR_DOMAIN_FIVR] = VrOverrideTable->VrVoltageLimit;
      }

      ///
      /// Exit loop when the correct CPU overrides have been applied.
      ///
      break;
    }
  }
}

/**
  Programs the VR parameters for the external VR's which support SVID communication.

  @param[IN OUT] SiPolicyPpi    - The SI Policy PPI instance
**/
VOID
ConfigureSvidVrs (
  IN OUT SI_POLICY_PPI *SiPolicyPpi
  )
{
  EFI_STATUS                  Status;
  UINT32                      MailboxData;
  UINT32                      MailboxCmd;
  UINT32                      MailboxStatus;
  UINT32                      MailboxType;
  UINT64                      TempAcLoadline;
  UINT64                      TempDcLoadline;
  VR_TOPOLOGY_DATA            VrTopology;
  UINT8                       TempVrAddress;
  UINT8                       SvidEnabled;
  UINT8                       ConvertedTimeWindow;
  UINTN                       VrIndex;
  UINTN                       MaxVrIndex;
  CPU_CONFIG                  *CpuConfig;
  CPU_POWER_MGMT_VR_CONFIG    *CpuPowerMgmtVrConfig;
  CPU_TEST_CONFIG             *CpuTestConfig;
  CPU_POWER_MGMT_PSYS_CONFIG  *CpuPowerMgmtPsysConfig;

  DEBUG ((DEBUG_INFO, "VR: Configure SVID Vr's\n"));
  DEBUG ((DEBUG_INFO, "VR_Handler\n"));

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuConfigGuid, (VOID *) &CpuConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuPowerMgmtVrConfigGuid, (VOID *) &CpuPowerMgmtVrConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuTestConfigGuid, (VOID *) &CpuTestConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuPowerMgmtPsysConfigGuid, (VOID *) &CpuPowerMgmtPsysConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "VR: Update VR overrides\n"));
  UpdateVrOverrides (CpuPowerMgmtVrConfig);

  ///
  /// Send command for MPS IMPV8 VR if requested
  ///
  if (CpuPowerMgmtVrConfig->SendVrMbxCmd == MPS_VR_CMD_REQUESTED) {
    MailboxType = MAILBOX_TYPE_PCODE;
    MailboxCmd  = WRITE_MPS_VR_IMPV8_CMD;
    MailboxData = 0x1;
    DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_MPS_VR_IMPV8_CMD\n"));
    Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
    if (EFI_ERROR(Status) || (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS)) {
      DEBUG ((DEBUG_ERROR, "VR: Error writing MPS VR IMPV8 command. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
    }
  }

  ///
  /// Send command for PS4 exit failures on specific VRs if requested
  ///
  if (CpuPowerMgmtVrConfig->SendVrMbxCmd == PS4_EXIT_VR_CMD_REQUESTED) {
    MailboxType = MAILBOX_TYPE_PCODE;
    MailboxCmd  = WRITE_PS4_EXIT_VR_CMD;
    MailboxData = 0x0;
    DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_PS4_EXIT_VR_CMD\n"));
    Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
    if (EFI_ERROR(Status) || (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS)) {
      DEBUG ((DEBUG_ERROR, "VR: Error writing PS4 Exit VR command. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
    }
  }

  ///
  /// Initialize Reliability features
  ///
  MailboxCmd  = WRITE_VOLTAGE_OPTIMIZATION_CMD;
  MailboxType = MAILBOX_TYPE_PCODE;
  ///
  /// Voltage Optimization mailbox command uses reverse encoding. 0 - Enable, 1 - Disable.
  ///
  MailboxData = ~CpuTestConfig->VoltageOptimization & BIT0;
  DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_VOLTAGE_OPTIMIZATION_CMD\n"));
  Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
  if (EFI_ERROR(Status) || (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS)) {
     DEBUG ((DEBUG_ERROR, "VR: Error writing Voltage Optimization. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
  }

  ///
  /// CPU VR MSR mailbox
  ///
  MailboxType = MAILBOX_TYPE_VR_MSR;

  /**
    Configure Platform Level controls

    PSYS Config
    -PsysSlope is defined as U10.1.9 fixed point
    -Policy Psys slope is defined in 1/100 increments
    -Mailbox PsysSlope = (PlatPolicyPsysSlope * 2^9)/100
  **/
  if (CpuPowerMgmtVrConfig->PsysOffset != 0 || CpuPowerMgmtVrConfig->PsysSlope != 0 ) {
    MailboxData =  (UINT32)(CpuPowerMgmtVrConfig->PsysOffset) |
                   (((CpuPowerMgmtVrConfig->PsysSlope * (1 << 9))/100) << PSYS_SLOPE_OFFSET);
    MailboxCmd = WRITE_PSYS_CONFIG_CMD;
    DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_PSYS_CONFIG_CMD\n"));
    DEBUG ((DEBUG_INFO, "(MAILBOX) PsysOffset            = %d (1/4)\n", CpuPowerMgmtVrConfig->PsysOffset));
    DEBUG ((DEBUG_INFO, "(MAILBOX) PsysSlope             = %d (1/100)\n", CpuPowerMgmtVrConfig->PsysSlope));
    DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Data    = %d\n", MailboxData));
    Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
    if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
      DEBUG ((DEBUG_ERROR, "VR: Error Writing PSYS Config. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
    }
  }

  ///
  /// PSYS Pmax
  /// -PMax is defined as U16.10.6 fixed point
  /// -Policy Pmax is defined in 1/8 W increments
  /// -Mailbox Pmax = (PlatPolicyPmax * 2^6)/8
  ///
  if (CpuPowerMgmtPsysConfig->PsysPmax != 0) {
    MailboxData =  (UINT32)((CpuPowerMgmtPsysConfig->PsysPmax * (1<<6))/8);
    MailboxCmd = WRITE_PSYS_PMAX_CMD;
    DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_PSYS_PMAX_CMD\n"));
    DEBUG ((DEBUG_INFO, "(MAILBOX) PsysPmax              = %d (1/8 Watt)\n", CpuPowerMgmtPsysConfig->PsysPmax));
    DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Data    = %d\n", MailboxData));
    Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
    if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
      DEBUG ((DEBUG_ERROR, "VR: Error Writing Psys PMAX. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
    }
  }

  ///
  /// Support Min Voltage override command. Min Voltage Runtime Data[7:0] and Min Voltage for C8 Data[15:8].
  /// - Mailbox Voltage limit defined in U8.1.7 volts in fixed point. Range 0 to 1.999V
  /// - Policy defined in mV, Range 0 - 1999mV.
  ///
  if (CpuPowerMgmtVrConfig->EnableMinVoltageOverride == 1) {
    MailboxData =  (UINT32) ((CpuPowerMgmtVrConfig->MinVoltageRuntime) * ((1<<7) /1000)        ///< Min Voltage Runtime Data[7:0]
                            | (((CpuPowerMgmtVrConfig->MinVoltageC8) * ((1<<7) /1000)) << 8)); ///< Min Voltage C8 Data[15:8]
    MailboxCmd = WRITE_VCCIN_MIN_VOLTAGE;
    DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_VCCIN_MIN_VOLTAGE\n"));
    DEBUG ((DEBUG_INFO, "(MAILBOX) MinVoltageRuntime     = %d mV\n",CpuPowerMgmtVrConfig->MinVoltageRuntime));
    DEBUG ((DEBUG_INFO, "(MAILBOX) MinVoltageC8          = %d mV\n", CpuPowerMgmtVrConfig->MinVoltageC8));
    DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Data    = %d\n", MailboxData));
    Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
    if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
      DEBUG ((DEBUG_ERROR, "VR: Error Writing Min Voltage Override Command. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
    }
  }

  ///
  /// Get CPU VR topology
  ///
  DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Read Command = READ_VR_STRAP_CONFIG_CMD\n"));
  Status = MailboxRead (MailboxType, READ_VR_STRAP_CONFIG_CMD, (UINT32*)&VrTopology.Fields, &MailboxStatus);
  if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
    DEBUG ((DEBUG_ERROR, "VR: Error Reading VR topology. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
  }

  ///
  /// Print VR Topology data
  ///
  DEBUG ((DEBUG_INFO, "VR: VR Topology data = 0x%x\n", VrTopology.Fields));
  DEBUG ((DEBUG_INFO, "    VR Type 0 = SVID, VR Type 1 = non-SVID\n"));
  DEBUG ((DEBUG_INFO, "    SA VR Address    = 0x%x\n", VrTopology.Fields.VrSaAddress));
  DEBUG ((DEBUG_INFO, "    SA VR Type       = 0x%x\n", VrTopology.Fields.VrSaSvidType));
  DEBUG ((DEBUG_INFO, "    IA VR Address    = 0x%x\n", VrTopology.Fields.VrIaAddress));
  DEBUG ((DEBUG_INFO, "    IA VR Type       = 0x%x\n", VrTopology.Fields.VrIaSvidType));
  DEBUG ((DEBUG_INFO, "    Ring VR Address  = 0x%x\n", VrTopology.Fields.VrRingAddress));
  DEBUG ((DEBUG_INFO, "    Ring VR Type     = 0x%x\n", VrTopology.Fields.VrRingSvidType));
  DEBUG ((DEBUG_INFO, "    GT VR Address    = 0x%x\n", VrTopology.Fields.VrGtAddress));
  DEBUG ((DEBUG_INFO, "    GT VR Type       = 0x%x\n", VrTopology.Fields.VrGtSvidType));
  DEBUG ((DEBUG_INFO, "    FIVR VR Address  = 0x%x\n", VrTopology.Fields.VrFivrAddress));
  DEBUG ((DEBUG_INFO, "    FIVR VR Type     = 0x%x\n", VrTopology.Fields.VrFivrSvidType));

  MaxVrIndex = CPU_VR_DOMAIN_FIVR;

  ///
  /// Set VR configuration parameters for all VR domains
  /// SA = 0, IA = 1, Ring = 2, GT = 3, FIVR = 4
  ///
  for (VrIndex = CPU_VR_DOMAIN_SA; VrIndex <= MaxVrIndex; VrIndex++) {
    switch (VrIndex) {

      case CPU_VR_DOMAIN_SA:
        TempVrAddress = (UINT8) VrTopology.Fields.VrSaAddress;
        SvidEnabled = (UINT8) (~VrTopology.Fields.VrSaSvidType) & BIT0;
        break;

      case CPU_VR_DOMAIN_IA:
        TempVrAddress = (UINT8) VrTopology.Fields.VrIaAddress;
        SvidEnabled = (UINT8) (~VrTopology.Fields.VrIaSvidType) & BIT0;
        break;

      case CPU_VR_DOMAIN_GT:
        TempVrAddress = (UINT8) VrTopology.Fields.VrGtAddress;
        SvidEnabled = (UINT8) (~VrTopology.Fields.VrGtSvidType) & BIT0;
        break;

      case CPU_VR_DOMAIN_FIVR:
        TempVrAddress = (UINT8) VrTopology.Fields.VrFivrAddress;
        SvidEnabled = (UINT8) (~VrTopology.Fields.VrFivrSvidType) & BIT0;
        break;

      default:
        TempVrAddress = 0;
        SvidEnabled = 0;
        break;
    }

    if (CpuPowerMgmtVrConfig->VrConfigEnable[VrIndex] == 1 && SvidEnabled == 1) {
      ///
      /// AC/DC Loadline
      ///
      if (CpuPowerMgmtVrConfig->AcLoadline[VrIndex] != 0 || CpuPowerMgmtVrConfig->DcLoadline[VrIndex] != 0) {
        ///
        ///  Check max AC/DC loadline boundary. Max allowed is 6249 (62.49 mOhm)
        ///
        if (CpuPowerMgmtVrConfig->AcLoadline[VrIndex] > AC_DC_LOADLINE_MAX){
          CpuPowerMgmtVrConfig->AcLoadline[VrIndex] = AC_DC_LOADLINE_MAX;
        } else if (CpuPowerMgmtVrConfig->DcLoadline[VrIndex] > AC_DC_LOADLINE_MAX){
          CpuPowerMgmtVrConfig->DcLoadline[VrIndex] = AC_DC_LOADLINE_MAX;
        }

        ///
        ///  Loadline is 1/100 mOhm units. Mailbox interface requires Loadline in U-4.20 Ohms format.
        ///  After multiplying by 2^20, we must divide the result by 100,000 to convert to Ohms.
        ///  Adding half of divisor to dividend to account for rounding errors in fixed point arithmetic.
        ///
        TempAcLoadline = MultU64x64(CpuPowerMgmtVrConfig->AcLoadline[VrIndex], LShiftU64 (1, 20));
        TempAcLoadline = DivU64x32(TempAcLoadline + 50000, 100000);
        TempDcLoadline = MultU64x64(CpuPowerMgmtVrConfig->DcLoadline[VrIndex], LShiftU64 (1, 20));
        TempDcLoadline = DivU64x32(TempDcLoadline + 50000, 100000);

        MailboxData = (UINT32) (TempAcLoadline | (LShiftU64 (TempDcLoadline, DC_LOADLINE_OFFSET)));
        MailboxCmd = WRITE_ACDC_LOADLINE_CMD | ((TempVrAddress & VR_ADDRESS_MASK) << VR_ADDRESS_OFFSET);
        DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_ACDC_LOADLINE_CMD\n"));
        DEBUG ((DEBUG_INFO, "(MAILBOX) AcLoadline            = %d (1/100 mOhms)\n",CpuPowerMgmtVrConfig->AcLoadline[VrIndex]));
        DEBUG ((DEBUG_INFO, "(MAILBOX) DcLoadline            = %d (1/100 mOhms)\n",CpuPowerMgmtVrConfig->DcLoadline[VrIndex]));
        DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Data    = %d\n", MailboxData));
        Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
        if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
          DEBUG ((DEBUG_ERROR, "VR: Error Writing AC/DC Loadline. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
        }
      }

      ///
      /// PS Cutoff Current
      ///
      MailboxData =  (UINT32)(CpuPowerMgmtVrConfig->Psi1Threshold[VrIndex] & PSI_THRESHOLD_MASK) |
                     ((CpuPowerMgmtVrConfig->Psi2Threshold[VrIndex] & PSI_THRESHOLD_MASK) << PSI2_THRESHOLD_OFFSET) |
                     ((CpuPowerMgmtVrConfig->Psi3Threshold[VrIndex] & PSI_THRESHOLD_MASK) << PSI3_THRESHOLD_OFFSET) |
                     ((~CpuPowerMgmtVrConfig->Psi3Enable[VrIndex] & BIT0) << PSI3_ENABLE_OFFSET) |
                     ((~CpuPowerMgmtVrConfig->Psi4Enable[VrIndex] & BIT0) << PSI4_ENABLE_OFFSET);
      MailboxCmd = WRITE_PSI_CUTOFF_CMD | ((TempVrAddress & VR_ADDRESS_MASK) << VR_ADDRESS_OFFSET);
      DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_PSI_CUTOFF_CMD\n"));
      DEBUG ((DEBUG_INFO, "(MAILBOX) Psi1Threshold         = %d (1/4 Amp)\n",CpuPowerMgmtVrConfig->Psi1Threshold));
      DEBUG ((DEBUG_INFO, "(MAILBOX) Psi2Threshold         = %d (1/4 Amp)\n",CpuPowerMgmtVrConfig->Psi2Threshold));
      DEBUG ((DEBUG_INFO, "(MAILBOX) Psi3Threshold         = %d (1/4 Amp)\n",CpuPowerMgmtVrConfig->Psi3Threshold));
      DEBUG ((DEBUG_INFO, "(MAILBOX) Psi3Enable            = %d, Psi4Enable            = %d\n",CpuPowerMgmtVrConfig->Psi3Enable, CpuPowerMgmtVrConfig->Psi4Enable));
      DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Data    = %d\n", MailboxData));
      Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
      if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
        DEBUG ((DEBUG_ERROR, "VR: Error Writing PS Cutoff Current. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
      }

      /// -ImonOffset is defined as S16.7.8 fixed point
      /// -ImonSlope is defined as U16.1.15 fixed point
      /// -Policy Imon offset is defined in 1/1000 increments
      /// -Policy Imon slope is defined in 1/100 increments
      /// -Mailbox ImonOffset = (PlatPolicyImonOffset * 2^8)/1000
      /// -Mailbox ImonSlope = (PlatPolicyImonSlope * 2^15)/100
      /// -Adding half of divisor to dividend to account for rounding errors in fixed point arithmetic.
      ///
      MailboxData =  (UINT32)(((CpuPowerMgmtVrConfig->ImonOffset[VrIndex] * (1 << 8) + 500) / 1000))
                             | (((CpuPowerMgmtVrConfig->ImonSlope[VrIndex] * (1 << 15) + 50) / 100) << VR_IMON_SLOPE_OFFSET);
      MailboxCmd = WRITE_IMON_CONFIG_CMD | ((TempVrAddress & VR_ADDRESS_MASK) << VR_ADDRESS_OFFSET);
      DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_IMON_CONFIG_CMD\n"));
      DEBUG ((DEBUG_INFO, "(MAILBOX) ImonOffset            = %d (1/1000)\n",CpuPowerMgmtVrConfig->ImonOffset[VrIndex]));
      DEBUG ((DEBUG_INFO, "(MAILBOX) ImonSlope             = %d (1/100)\n",CpuPowerMgmtVrConfig->ImonSlope[VrIndex]));
      DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Data    = %d\n", MailboxData));
      Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
      if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
        DEBUG ((DEBUG_ERROR, "VR: Error Writing IMON Config. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
      }

      ///
      /// Icc Max
      ///
      if (CpuPowerMgmtVrConfig->IccMax[VrIndex] != 0) {
        MailboxData =  (UINT32)CpuPowerMgmtVrConfig->IccMax[VrIndex];
        MailboxCmd = WRITE_VR_ICC_MAX_CMD | ((TempVrAddress & VR_ADDRESS_MASK) << VR_ADDRESS_OFFSET);
        DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_VR_ICC_MAX_CMD\n"));
        DEBUG ((DEBUG_INFO, "(MAILBOX) IccMax                = %d (1/4 A)\n",CpuPowerMgmtVrConfig->IccMax[VrIndex]));
        Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
        if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
          DEBUG ((DEBUG_ERROR, "VR: Error Writing IccMax. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
        }
      }

      ///
      /// VR Voltage Limit
      /// -Mailbox Voltage Limit defined as U16.3.13, Range 0-7.999V
      /// -Policy defined in mV, Range 0-7999mV
      /// -Adding half of divisor to dividend to account for rounding errors in fixed point arithmetic.
      ///
      if (CpuPowerMgmtVrConfig->VrVoltageLimit[VrIndex] != 0) {
        MailboxData =  (UINT32)((CpuPowerMgmtVrConfig->VrVoltageLimit[VrIndex] * (1 << 13) + 500) / 1000) & VR_VOLTAGE_LIMIT_MASK;
        MailboxCmd = WRITE_VR_VOLTAGE_LIMIT_CMD | ((TempVrAddress & VR_ADDRESS_MASK) << VR_ADDRESS_OFFSET);
        DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_VR_VOLTAGE_LIMIT_CMD\n"));
        DEBUG ((DEBUG_INFO, "(MAILBOX) VrVoltageLimit        = %d mV\n",CpuPowerMgmtVrConfig->VrVoltageLimit[VrIndex]));
        DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Data    = %d\n", MailboxData));
        Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
        if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
          DEBUG ((DEBUG_ERROR, "VR: Error Writing VR Voltage Limit. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
        }
      }

      ///
      /// VR TDC Settings
      /// -Mailbox TDC Current Limit defined as U15.12.3, Range 0-4095A
      ///    -Policy defined in 1/8 A increments
      /// -Time window mailbox format, in binary, is xxyyyyy, time window = (1+X/4)*pow(2,Y)
      ///    -Set to 1ms default (mailbox value = 0000000b)
      ///

      ///
      /// Ensure Time Window Value is within the supported range.
      ///
      if (CpuPowerMgmtVrConfig->TdcTimeWindow[VrIndex] <= VR_TDC_TIME_WINDOW_MAX) {
        ConvertedTimeWindow = mMilliSecondsToMsrValueTable[CpuPowerMgmtVrConfig->TdcTimeWindow[VrIndex]][1];
      } else {
        ConvertedTimeWindow = 0;
      }

      MailboxData =  (UINT32)((CpuPowerMgmtVrConfig->TdcCurrentLimit[VrIndex] & VR_TDC_CURRENT_LIMIT_MASK) |
                             ((CpuPowerMgmtVrConfig->TdcEnable[VrIndex] & BIT0) << VR_TDC_ENABLE_OFFSET) |
                             ((ConvertedTimeWindow & VR_TDC_TIME_WINDOW_MASK) << VR_TDC_TIME_WINDOW_OFFSET) |
                             ((CpuPowerMgmtVrConfig->TdcLock[VrIndex] & BIT0) << VR_TDC_LOCK_OFFSET));
      MailboxCmd = WRITE_VR_TDC_CONFIG_CMD | ((TempVrAddress & VR_ADDRESS_MASK) << VR_TDC_ADDRESS_OFFSET);

      DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_VR_TDC_CONFIG_CMD\n"));
      DEBUG ((DEBUG_INFO, "(MAILBOX) TdcPowerLimit         = %d (1/8A)\n",CpuPowerMgmtVrConfig->TdcCurrentLimit[VrIndex]));
      Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
      if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
        DEBUG ((DEBUG_ERROR, "VR: Error Writing VR TDC Config. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
      }
    }

    ///
    /// Acoustic Noise Mitigation
    ///
    if (CpuPowerMgmtVrConfig->AcousticNoiseMitigation) {
      ///
      /// Set Fast and Slow Slew Rate for Deep Package C States
      ///

      ///
      /// IA domain
      ///
      if (VrIndex == CPU_VR_DOMAIN_IA) {
        MailboxCmd  = WRITE_SVID_SET_DISABLE_FAST_PKGC_RAMP_CMD | ((TempVrAddress & VR_ADDRESS_MASK) << VR_ADDRESS_OFFSET);
        MailboxData = CpuPowerMgmtVrConfig->FastPkgCRampDisableIa;
        DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command   = WRITE_SVID_SET_DISABLE_FAST_PKGC_RAMP_CMD\n"));
        Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
        if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
          DEBUG ((DEBUG_ERROR, "VR: Error Writing disable Fast Deep Package C States for IA. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
        }

        MailboxCmd  = WRITE_SVID_SET_VR_SLEW_RATE_CMD | ((TempVrAddress & VR_ADDRESS_MASK) << VR_ADDRESS_OFFSET);
        MailboxData = CpuPowerMgmtVrConfig->SlowSlewRateForIa;
        DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = SSR - WRITE_SVID_SET_VR_SLEW_RATE_CMD\n"));
        DEBUG ((DEBUG_INFO, "(MAILBOX) SlowSlewRateForIa   = %d (0: Fast/2</b>; 1: Fast/4; 2: Fast/8; 3: Fast/16)\n",CpuPowerMgmtVrConfig->SlowSlewRateForIa));
        Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
        if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
          DEBUG ((DEBUG_ERROR, "VR: Error Writing Slow Slew Rate for IA. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
        }
      }

      ///
      /// GT domain
      ///
      if (VrIndex == CPU_VR_DOMAIN_GT) {
        MailboxCmd  = WRITE_SVID_SET_DISABLE_FAST_PKGC_RAMP_CMD | ((TempVrAddress & VR_ADDRESS_MASK) << VR_ADDRESS_OFFSET);
        MailboxData = CpuPowerMgmtVrConfig->FastPkgCRampDisableGt;
        DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_SVID_SET_DISABLE_FAST_PKGC_RAMP_CMD\n"));
        Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
        if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
          DEBUG ((DEBUG_ERROR, "VR: Error Writing disable Fast Deep Package C States for GT. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
        }

        MailboxCmd  = WRITE_SVID_SET_VR_SLEW_RATE_CMD | ((TempVrAddress & VR_ADDRESS_MASK) << VR_ADDRESS_OFFSET);
        MailboxData = CpuPowerMgmtVrConfig->SlowSlewRateForGt;
        DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_SVID_SET_VR_SLEW_RATE_CMD\n"));
        DEBUG ((DEBUG_INFO, "(MAILBOX) SlowSlewRateForGt   = %d (0: Fast/2</b>; 1: Fast/4; 2: Fast/8; 3: Fast/16)\n",CpuPowerMgmtVrConfig->SlowSlewRateForGt));
        Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
        if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
          DEBUG ((DEBUG_ERROR, "VR: Error Writing Slow Slew Rate for GT. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
        }
      }

      ///
      /// FIVR domain
      ///
      if (VrIndex == CPU_VR_DOMAIN_FIVR) {
        MailboxCmd  = WRITE_SVID_SET_DISABLE_FAST_PKGC_RAMP_CMD | ((TempVrAddress & VR_ADDRESS_MASK) << VR_ADDRESS_OFFSET);
        MailboxData = CpuPowerMgmtVrConfig->FastPkgCRampDisableFivr;
        DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_SVID_SET_DISABLE_FAST_PKGC_RAMP_CMD\n"));
        Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
        if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
          DEBUG ((DEBUG_ERROR, "VR: Error Writing disable Fast Deep Package C States for FIVR. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
        }

        MailboxCmd  = WRITE_SVID_SET_VR_SLEW_RATE_CMD | ((TempVrAddress & VR_ADDRESS_MASK) << VR_ADDRESS_OFFSET);
        MailboxData = CpuPowerMgmtVrConfig->SlowSlewRateForFivr;
        DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_SVID_SET_VR_SLEW_RATE_CMD\n"));
        DEBUG ((DEBUG_INFO, "(MAILBOX) SlowSlewRateForFivr   = %d (0: Fast/2</b>; 1: Fast/4; 2: Fast/8; 3: Fast/16)\n",CpuPowerMgmtVrConfig->SlowSlewRateForFivr));
        Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
        if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
          DEBUG ((DEBUG_ERROR, "VR: Error Writing Slow Slew Rate for FIVR. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
        }
      }

      ///
      /// SA domain
      ///
      if (VrIndex == CPU_VR_DOMAIN_SA) {
        MailboxCmd  = WRITE_SVID_SET_DISABLE_FAST_PKGC_RAMP_CMD | ((TempVrAddress & VR_ADDRESS_MASK) << VR_ADDRESS_OFFSET);
        MailboxData = CpuPowerMgmtVrConfig->FastPkgCRampDisableSa;
        DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_SVID_SET_DISABLE_FAST_PKGC_RAMP_CMD\n"));
        Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
        if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
          DEBUG ((DEBUG_ERROR, "VR: Error Writing disable Fast Deep Package C States for SA. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
        }

        MailboxCmd  = WRITE_SVID_SET_VR_SLEW_RATE_CMD | ((TempVrAddress & VR_ADDRESS_MASK) << VR_ADDRESS_OFFSET);
        MailboxData = CpuPowerMgmtVrConfig->SlowSlewRateForSa;
        DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_SVID_SET_VR_SLEW_RATE_CMD\n"));
        DEBUG ((DEBUG_INFO, "(MAILBOX) SlowSlewRateForSa   = %d (0: Fast/2</b>; 1: Fast/4; 2: Fast/8; 3: Fast/16)\n",CpuPowerMgmtVrConfig->SlowSlewRateForSa));
        Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
        if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
          DEBUG ((DEBUG_ERROR, "VR: Error Writing Slow Slew Rate for SA. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
        }
      }
    }
  }

  ///
  /// RFI Mitigation
  ///
  UpdateFivrRfiSettings (CpuPowerMgmtVrConfig);
}

/**
  Programs the PID parameters

  @param[in] SiPolicyPpi - The SI Policy PPI instance
**/
VOID
ConfigurePidSettings (
  IN OUT SI_POLICY_PPI *SiPolicyPpi
  )
{
  EFI_STATUS          Status;
  UINT32              MailboxData;
  UINT32              MailboxCmd;
  UINT32              MailboxStatus;
  UINT32              MailboxType;
  UINTN               Index;
  CPU_PID_TEST_CONFIG *CpuPidTestConfig;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuPidTestConfigGuid, (VOID *) &CpuPidTestConfig);
  ASSERT_EFI_ERROR (Status);

  ///
  /// PID tuning must be enabled to continue
  ///
  if (CpuPidTestConfig->PidTuning == 0) {
    return;
  }

  ///
  /// Send PID mailbox commands. If any setting is non-zero we need to update
  /// that setting for all domains.
  ///
  DEBUG ((DEBUG_INFO, "PID: Configure PID Settings\n"));
  MailboxType = MAILBOX_TYPE_PCODE;

  ///
  /// RATL
  ///
  if ( (CpuPidTestConfig->Ratl[PID_DOMAIN_KP] != 0) ||
       (CpuPidTestConfig->Ratl[PID_DOMAIN_KI] != 0) ||
       (CpuPidTestConfig->Ratl[PID_DOMAIN_KD] != 0) ) {

    for (Index = PID_DOMAIN_KP; Index <= PID_DOMAIN_KD; Index++) {
      MailboxData = CpuPidTestConfig->Ratl[Index];
      MailboxCmd = WRITE_PID_RATL | (Index << MAILBOX_PARAM_1_OFFSET);
      DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_PID_RATL\n"));
      DEBUG ((DEBUG_INFO, "(MAILBOX) Ratl[%d]              = %d (1/256 units)\n",Index,CpuPidTestConfig->Ratl[Index]));
      Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
      if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
        DEBUG ((DEBUG_ERROR, "PID: Error Writing RATL for index %X. EFI_STATUS = %r, Mailbox Status = %X\n", Index, Status, MailboxStatus));
      }
    }
  }

  ///
  /// VR TDC for VR0
  ///
  if ( (CpuPidTestConfig->VrTdcVr0[PID_DOMAIN_KP] != 0) ||
       (CpuPidTestConfig->VrTdcVr0[PID_DOMAIN_KI] != 0) ||
       (CpuPidTestConfig->VrTdcVr0[PID_DOMAIN_KD] != 0) ) {

    for (Index = PID_DOMAIN_KP; Index <= PID_DOMAIN_KD; Index++) {
      MailboxData = CpuPidTestConfig->VrTdcVr0[Index];
      MailboxCmd = WRITE_PID_VR0_TDC | (Index << MAILBOX_PARAM_1_OFFSET);
      DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_PID_VR0_TDC\n"));
      DEBUG ((DEBUG_INFO, "(MAILBOX) VrTdcVr0[%d]          = %d (1/256 units)\n",Index,CpuPidTestConfig->VrTdcVr0[Index]));
      Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
      if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
        DEBUG ((DEBUG_ERROR, "PID: Error Writing VR TDC VR0 for index %X. EFI_STATUS = %r, Mailbox Status = %X\n", Index, Status, MailboxStatus));
      }
    }
  }

  ///
  /// VR TDC for VR1
  ///
  if ( (CpuPidTestConfig->VrTdcVr1[PID_DOMAIN_KP] != 0) ||
       (CpuPidTestConfig->VrTdcVr1[PID_DOMAIN_KI] != 0) ||
       (CpuPidTestConfig->VrTdcVr1[PID_DOMAIN_KD] != 0) ) {

    for (Index = PID_DOMAIN_KP; Index <= PID_DOMAIN_KD; Index++) {
      MailboxData = CpuPidTestConfig->VrTdcVr1[Index];
      MailboxCmd = WRITE_PID_VR1_TDC | (Index << MAILBOX_PARAM_1_OFFSET);
      DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_PID_VR1_TDC\n"));
      DEBUG ((DEBUG_INFO, "(MAILBOX) VrTdcVr1[%d]          = %d (1/256 units)\n",Index,CpuPidTestConfig->VrTdcVr1[Index]));
      Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
      if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
        DEBUG ((DEBUG_ERROR, "PID: Error Writing VR TDC VR1 for index %X. EFI_STATUS = %r, Mailbox Status = %X\n", Index, Status, MailboxStatus));
      }
    }
  }

  ///
  /// VR TDC for VR2
  ///
  if ( (CpuPidTestConfig->VrTdcVr2[PID_DOMAIN_KP] != 0) ||
       (CpuPidTestConfig->VrTdcVr2[PID_DOMAIN_KI] != 0) ||
       (CpuPidTestConfig->VrTdcVr2[PID_DOMAIN_KD] != 0) ) {

    for (Index = PID_DOMAIN_KP; Index <= PID_DOMAIN_KD; Index++) {
      MailboxData = CpuPidTestConfig->VrTdcVr2[Index];
      MailboxCmd = WRITE_PID_VR2_TDC | (Index << MAILBOX_PARAM_1_OFFSET);
      DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_PID_VR2_TDC\n"));
      DEBUG ((DEBUG_INFO, "(MAILBOX) VrTdcVr2[%d]          = %d (1/256 units)\n",Index,CpuPidTestConfig->VrTdcVr2[Index]));
      Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
      if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
        DEBUG ((DEBUG_ERROR, "PID: Error Writing VR TDC VR2 for index %X. EFI_STATUS = %r, Mailbox Status = %X\n", Index, Status, MailboxStatus));
      }
    }
  }

  ///
  /// VR TDC for VR3
  ///
  if ( (CpuPidTestConfig->VrTdcVr3[PID_DOMAIN_KP] != 0) ||
       (CpuPidTestConfig->VrTdcVr3[PID_DOMAIN_KI] != 0) ||
       (CpuPidTestConfig->VrTdcVr3[PID_DOMAIN_KD] != 0) ) {

    for (Index = PID_DOMAIN_KP; Index <= PID_DOMAIN_KD; Index++) {
      MailboxData = CpuPidTestConfig->VrTdcVr3[Index];
      MailboxCmd = WRITE_PID_VR3_TDC | (Index << MAILBOX_PARAM_1_OFFSET);
      DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_PID_VR3_TDC\n"));
      DEBUG ((DEBUG_INFO, "(MAILBOX) VrTdcVr3[%d]          = %d (1/256 units)\n",Index,CpuPidTestConfig->VrTdcVr3[Index]));
      Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
      if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
        DEBUG ((DEBUG_ERROR, "PID: Error Writing VR TDC VR3 for index %X. EFI_STATUS = %r, Mailbox Status = %X\n", Index, Status, MailboxStatus));
      }
    }
  }

  ///
  /// PBM PSYS PL1 MSR
  ///
  if ( (CpuPidTestConfig->PbmPsysPl1Msr[PID_DOMAIN_KP] != 0) ||
       (CpuPidTestConfig->PbmPsysPl1Msr[PID_DOMAIN_KI] != 0) ||
       (CpuPidTestConfig->PbmPsysPl1Msr[PID_DOMAIN_KD] != 0) ) {

    for (Index = PID_DOMAIN_KP; Index <= PID_DOMAIN_KD; Index++) {
      MailboxData = CpuPidTestConfig->PbmPsysPl1Msr[Index];
      MailboxCmd = WRITE_PID_PSYS_PL1_MSR| (Index << MAILBOX_PARAM_1_OFFSET);
      DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_PID_PSYS_PL1_MSR\n"));
      DEBUG ((DEBUG_INFO, "(MAILBOX) PbmPsysPl1Msr[%d]     = %d (1/256 units)\n",Index,CpuPidTestConfig->PbmPsysPl1Msr[Index]));
      Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
      if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
        DEBUG ((DEBUG_ERROR, "PID: Error Writing PbmPsysPl1Msr for index %X. EFI_STATUS = %r, Mailbox Status = %X\n", Index, Status, MailboxStatus));
      }
    }
  }

  ///
  /// PBM PSYS PL1 MMIO PCS
  ///
  if ( (CpuPidTestConfig->PbmPsysPl1MmioPcs[PID_DOMAIN_KP] != 0) ||
       (CpuPidTestConfig->PbmPsysPl1MmioPcs[PID_DOMAIN_KI] != 0) ||
       (CpuPidTestConfig->PbmPsysPl1MmioPcs[PID_DOMAIN_KD] != 0) ) {

    for (Index = PID_DOMAIN_KP; Index <= PID_DOMAIN_KD; Index++) {
      MailboxData = CpuPidTestConfig->PbmPsysPl1MmioPcs[Index];
      MailboxCmd = WRITE_PID_PSYS_PL1_MMIO| (Index << MAILBOX_PARAM_1_OFFSET);
      DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_PID_PSYS_PL1_MMIO\n"));
      DEBUG ((DEBUG_INFO, "(MAILBOX) PbmPsysPl1MmioPcs[%d] = %d (1/256 units)\n",Index,CpuPidTestConfig->PbmPsysPl1MmioPcs[Index]));
      Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
      if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
        DEBUG ((DEBUG_ERROR, "PID: Error Writing PbmPsysPl1MmioPcs for index %X. EFI_STATUS = %r, Mailbox Status = %X\n", Index, Status, MailboxStatus));
      }
    }
  }

  ///
  /// PBM PSYS PL2 MSR
  ///
  if ( (CpuPidTestConfig->PbmPsysPl2Msr[PID_DOMAIN_KP] != 0) ||
       (CpuPidTestConfig->PbmPsysPl2Msr[PID_DOMAIN_KI] != 0) ||
       (CpuPidTestConfig->PbmPsysPl2Msr[PID_DOMAIN_KD] != 0) ) {

    for (Index = PID_DOMAIN_KP; Index <= PID_DOMAIN_KD; Index++) {
      MailboxData = CpuPidTestConfig->PbmPsysPl2Msr[Index];
      MailboxCmd = WRITE_PID_PSYS_PL2_MSR | (Index << MAILBOX_PARAM_1_OFFSET);
      DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_PID_PSYS_PL2_MSR\n"));
      DEBUG ((DEBUG_INFO, "(MAILBOX) PbmPsysPl2Msr[%d]     = %d (1/256 units)\n",Index,CpuPidTestConfig->PbmPsysPl2Msr[Index]));
      Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
      if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
        DEBUG ((DEBUG_ERROR, "PID: Error Writing PbmPsysPl2Msr for index %X. EFI_STATUS = %r, Mailbox Status = %X\n", Index, Status, MailboxStatus));
      }
    }
  }

  ///
  /// PBM PSYS PL2 MMIO PCS
  ///
  if ( (CpuPidTestConfig->PbmPsysPl2MmioPcs[PID_DOMAIN_KP] != 0) ||
       (CpuPidTestConfig->PbmPsysPl2MmioPcs[PID_DOMAIN_KI] != 0) ||
       (CpuPidTestConfig->PbmPsysPl2MmioPcs[PID_DOMAIN_KD] != 0) ) {

    for (Index = PID_DOMAIN_KP; Index <= PID_DOMAIN_KD; Index++) {
      MailboxData = CpuPidTestConfig->PbmPsysPl2MmioPcs[Index];
      MailboxCmd = WRITE_PID_PSYS_PL2_MMIO | (Index << MAILBOX_PARAM_1_OFFSET);
      DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_PID_PSYS_PL2_MMIO\n"));
      DEBUG ((DEBUG_INFO, "(MAILBOX) PbmPsysPl2MmioPcs[%d] = %d (1/256 units)\n",Index,CpuPidTestConfig->PbmPsysPl2MmioPcs[Index]));
      Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
      if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
        DEBUG ((DEBUG_ERROR, "PID: Error Writing PbmPsysPl2MmioPcs for index %X. EFI_STATUS = %r, Mailbox Status = %X\n", Index, Status, MailboxStatus));
      }
    }
  }

  ///
  /// PBM Package PL1 MSR
  ///
  if ( (CpuPidTestConfig->PbmPkgPl1Msr[PID_DOMAIN_KP] != 0) ||
       (CpuPidTestConfig->PbmPkgPl1Msr[PID_DOMAIN_KI] != 0) ||
       (CpuPidTestConfig->PbmPkgPl1Msr[PID_DOMAIN_KD] != 0) ) {

    for (Index = PID_DOMAIN_KP; Index <= PID_DOMAIN_KD; Index++) {
      MailboxData = CpuPidTestConfig->PbmPkgPl1Msr[Index];
      MailboxCmd = WRITE_PID_PKG_PL1_MSR | (Index << MAILBOX_PARAM_1_OFFSET);
      DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_PID_PKG_PL1_MSR\n"));
      DEBUG ((DEBUG_INFO, "(MAILBOX) PbmPkgPl1Msr[%d]      = %d (1/256 units)\n",Index,CpuPidTestConfig->PbmPkgPl1Msr[Index]));
      Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
      if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
        DEBUG ((DEBUG_ERROR, "PID: Error Writing PbmPkgPl1Msr for index %X. EFI_STATUS = %r, Mailbox Status = %X\n", Index, Status, MailboxStatus));
      }
    }
  }

  ///
  /// PBM Package PL1 MMIO PCS
  ///
  if ( (CpuPidTestConfig->PbmPkgPl1MmioPcs[PID_DOMAIN_KP] != 0) ||
       (CpuPidTestConfig->PbmPkgPl1MmioPcs[PID_DOMAIN_KI] != 0) ||
       (CpuPidTestConfig->PbmPkgPl1MmioPcs[PID_DOMAIN_KD] != 0) ) {

    for (Index = PID_DOMAIN_KP; Index <= PID_DOMAIN_KD; Index++) {
      MailboxData = CpuPidTestConfig->PbmPkgPl1MmioPcs[Index];
      MailboxCmd = WRITE_PID_PKG_PL1_MMIO | (Index << MAILBOX_PARAM_1_OFFSET);
      DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_PID_PKG_PL1_MMIO\n"));
      DEBUG ((DEBUG_INFO, "(MAILBOX) PbmPkgPl1MmioPcs[%d]  = %d (1/256 units)\n",Index,CpuPidTestConfig->PbmPkgPl1MmioPcs[Index]));
      Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
      if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
        DEBUG ((DEBUG_ERROR, "PID: Error Writing PbmPkgPl1MmioPcs for index %X. EFI_STATUS = %r, Mailbox Status = %X\n", Index, Status, MailboxStatus));
      }
    }
  }

  ///
  /// PBM Package PL2 MSR
  ///
  if ( (CpuPidTestConfig->PbmPkgPl2Msr[PID_DOMAIN_KP] != 0) ||
       (CpuPidTestConfig->PbmPkgPl2Msr[PID_DOMAIN_KI] != 0) ||
       (CpuPidTestConfig->PbmPkgPl2Msr[PID_DOMAIN_KD] != 0) ) {

    for (Index = PID_DOMAIN_KP; Index <= PID_DOMAIN_KD; Index++) {
      MailboxData = CpuPidTestConfig->PbmPkgPl2Msr[Index];
      MailboxCmd = WRITE_PID_PKG_PL2_MSR | (Index << MAILBOX_PARAM_1_OFFSET);
      DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_PID_PKG_PL2_MSR\n"));
      DEBUG ((DEBUG_INFO, "(MAILBOX) PbmPkgPl2Msr[%d]      = %d (1/256 units)\n",Index,CpuPidTestConfig->PbmPkgPl2Msr[Index]));
      Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
      if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
        DEBUG ((DEBUG_ERROR, "PID: Error Writing PbmPkgPl2Msr for index %X. EFI_STATUS = %r, Mailbox Status = %X\n", Index, Status, MailboxStatus));
      }
    }
  }

  ///
  /// PBM Package PL2 MMIO PCS
  ///
  if ( (CpuPidTestConfig->PbmPkgPl2MmioPcs[PID_DOMAIN_KP] != 0) ||
       (CpuPidTestConfig->PbmPkgPl2MmioPcs[PID_DOMAIN_KI] != 0) ||
       (CpuPidTestConfig->PbmPkgPl2MmioPcs[PID_DOMAIN_KD] != 0) ) {

    for (Index = PID_DOMAIN_KP; Index <= PID_DOMAIN_KD; Index++) {
      MailboxData = CpuPidTestConfig->PbmPkgPl2MmioPcs[Index];
      MailboxCmd = WRITE_PID_PKG_PL2_MMIO | (Index << MAILBOX_PARAM_1_OFFSET);
      DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_PID_PKG_PL2_MMIO\n"));
      DEBUG ((DEBUG_INFO, "(MAILBOX) PbmPkgPl2MmioPcs[%d]  = %d (1/256 units)\n",Index,CpuPidTestConfig->PbmPkgPl2MmioPcs[Index]));
      Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
      if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
        DEBUG ((DEBUG_ERROR, "PID: Error Writing PbmPkgPl2MmioPcs for index %X. EFI_STATUS = %r, Mailbox Status = %X\n", Index, Status, MailboxStatus));
      }
    }
  }

  ///
  /// DDR PL1 MSR
  ///
  if ( (CpuPidTestConfig->DdrPl1Msr[PID_DOMAIN_KP] != 0) ||
       (CpuPidTestConfig->DdrPl1Msr[PID_DOMAIN_KI] != 0) ||
       (CpuPidTestConfig->DdrPl1Msr[PID_DOMAIN_KD] != 0) ) {

    for (Index = PID_DOMAIN_KP; Index <= PID_DOMAIN_KD; Index++) {
      MailboxData = CpuPidTestConfig->DdrPl1Msr[Index];
      MailboxCmd = WRITE_PID_DDR_PL1_MSR | (Index << MAILBOX_PARAM_1_OFFSET);
      DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_PID_DDR_PL1_MSR\n"));
      DEBUG ((DEBUG_INFO, "(MAILBOX) DdrPl1Msr[%d]         = %d (1/256 units)\n",Index,CpuPidTestConfig->DdrPl1Msr[Index]));
      Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
      if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
        DEBUG ((DEBUG_ERROR, "PID: Error Writing DdrPl1Msr for index %X. EFI_STATUS = %r, Mailbox Status = %X\n", Index, Status, MailboxStatus));
      }
    }
  }

  ///
  /// DDR PL1 MMIO PCS
  ///
  if ( (CpuPidTestConfig->DdrPl1MmioPcs[PID_DOMAIN_KP] != 0) ||
       (CpuPidTestConfig->DdrPl1MmioPcs[PID_DOMAIN_KI] != 0) ||
       (CpuPidTestConfig->DdrPl1MmioPcs[PID_DOMAIN_KD] != 0) ) {

    for (Index = PID_DOMAIN_KP; Index <= PID_DOMAIN_KD; Index++) {
      MailboxData = CpuPidTestConfig->DdrPl1MmioPcs[Index];
      MailboxCmd = WRITE_PID_DDR_PL1_MMIO | (Index << MAILBOX_PARAM_1_OFFSET);
      DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_PID_DDR_PL1_MMIO\n"));
      DEBUG ((DEBUG_INFO, "(MAILBOX) DdrPl1MmioPcs[%d]     = %d (1/256 units)\n",Index,CpuPidTestConfig->DdrPl1MmioPcs[Index]));
      Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
      if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
        DEBUG ((DEBUG_ERROR, "PID: Error Writing DdrPl1MmioPcs for index %X. EFI_STATUS = %r, Mailbox Status = %X\n", Index, Status, MailboxStatus));
      }
    }
  }

  ///
  /// DDR PL2 MSR
  ///
  if ( (CpuPidTestConfig->DdrPl2Msr[PID_DOMAIN_KP] != 0) ||
       (CpuPidTestConfig->DdrPl2Msr[PID_DOMAIN_KI] != 0) ||
       (CpuPidTestConfig->DdrPl2Msr[PID_DOMAIN_KD] != 0) ) {

    for (Index = PID_DOMAIN_KP; Index <= PID_DOMAIN_KD; Index++) {
      MailboxData = CpuPidTestConfig->DdrPl2Msr[Index];
      MailboxCmd = WRITE_PID_DDR_PL2_MSR | (Index << MAILBOX_PARAM_1_OFFSET);
      DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_PID_DDR_PL2_MSR\n"));
      DEBUG ((DEBUG_INFO, "(MAILBOX) DdrPl2Msr[%d]         = %d (1/256 units)\n",Index,CpuPidTestConfig->DdrPl2Msr[Index]));
      Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
      if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
        DEBUG ((DEBUG_ERROR, "PID: Error Writing DdrPl2Msr for index %X. EFI_STATUS = %r, Mailbox Status = %X\n", Index, Status, MailboxStatus));
      }
    }
  }

  ///
  /// DDR PL2 MMIO PCS
  ///
  if ( (CpuPidTestConfig->DdrPl2MmioPcs[PID_DOMAIN_KP] != 0) ||
       (CpuPidTestConfig->DdrPl2MmioPcs[PID_DOMAIN_KI] != 0) ||
       (CpuPidTestConfig->DdrPl2MmioPcs[PID_DOMAIN_KD] != 0) ) {

    for (Index = PID_DOMAIN_KP; Index <= PID_DOMAIN_KD; Index++) {
      MailboxData = CpuPidTestConfig->DdrPl2MmioPcs[Index];
      MailboxCmd = WRITE_PID_DDR_PL2_MMIO | (Index << MAILBOX_PARAM_1_OFFSET);
      DEBUG ((DEBUG_INFO, "(MAILBOX) Mailbox Write Command = WRITE_PID_DDR_PL2_MMIO\n"));
      DEBUG ((DEBUG_INFO, "(MAILBOX) DdrPl2MmioPcs[%d]     = %d (1/256 units)\n",Index,CpuPidTestConfig->DdrPl2MmioPcs[Index]));
      Status = MailboxWrite (MailboxType, MailboxCmd, MailboxData, &MailboxStatus);
      if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
        DEBUG ((DEBUG_ERROR, "PID: Error Writing DdrPl2MmioPcs for index %X. EFI_STATUS = %r, Mailbox Status = %X\n", Index, Status, MailboxStatus));
      }
    }
  }

}

/**
  Set processor P state based on input parameter.

  @param[in out] Buffer - Pointer to UINT8 BootRatio parameter.
**/
VOID
EFIAPI
ApSafeSetBootPState (
  IN OUT VOID *Buffer
  )
{
  UINT8        BootRatio;
  MSR_REGISTER Ia32PerfCtl;

  ///
  /// Extract the boot ratio from the buffer.
  ///
  BootRatio = *((UINT8 *) Buffer);

  Ia32PerfCtl.Qword = AsmReadMsr64 (MSR_IA32_PERF_CTL);
  Ia32PerfCtl.Qword &= (UINT64) ~B_IA32_PERF_CTRLP_STATE_TARGET;
  Ia32PerfCtl.Qword |= (LShiftU64 (BootRatio, N_IA32_PERF_CTRLP_STATE_TARGET) & B_IA32_PERF_CTRLP_STATE_TARGET);
  AsmWriteMsr64 (MSR_IA32_PERF_CTL, Ia32PerfCtl.Qword);

  return;
}

/**
  Set the Boot Frequency across all logical processors.

  @param[in] PeiServices   Pointer to PEI Services Table
  @param[in] SiPolicyPpi - The SI Policy PPI instance.
**/
VOID
SetBootFrequency (
  IN CONST EFI_PEI_SERVICES  **PeiServices,
  IN SI_POLICY_PPI           *SiPolicyPpi
  )
{
  UINT8                              BootRatio;
  MSR_REGISTER                       PlatformInfoMsr;
  MSR_REGISTER                       MsrValue;
  MSR_IA32_MISC_ENABLE_REGISTER      MiscEnable;
  UINT8                              MaxBusRatio;
  UINT8                              MinBusRatio;
  UINT8                              BootFrequencyMode;
  CPUID_THERMAL_POWER_MANAGEMENT_EAX Eax;
  UINT8                              NumberOfConfigTdpLevels;
  UINT8                              SupportedCtdpLevels;
  UINT8                              SelectedCtdpLevel;
  UINT8                              CtdpTarRatioPlusOne;
  CPU_POWER_MGMT_BASIC_CONFIG        *CpuPowerMgmtBasicConfig;
  CPU_POWER_MGMT_TEST_CONFIG         *CpuPowerMgmtTestConfig;
  CPU_POWER_MGMT_CUSTOM_CONFIG       *CpuPowerMgmtCustomConfig;
  CPU_CONFIG_LIB_PREMEM_CONFIG       *CpuConfigLibPreMemConfig;
  EFI_STATUS                         Status;
  SI_PREMEM_POLICY_PPI               *SiPreMemPolicyPpi;

  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **)&SiPreMemPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuPowerMgmtBasicConfigGuid, (VOID *) &CpuPowerMgmtBasicConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuPowerMgmtCustomConfigGuid, (VOID *) &CpuPowerMgmtCustomConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuPowerMgmtTestConfigGuid, (VOID *) &CpuPowerMgmtTestConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuConfigLibPreMemConfigGuid, (VOID *) &CpuConfigLibPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Get Maximum Non-Turbo bus ratio (HFM) from Platform Info MSR Bits[15:8]
  /// Get Maximum Efficiency bus ratio (LFM) from Platform Info MSR Bits[47:40]
  ///
  PlatformInfoMsr.Qword = AsmReadMsr64 (MSR_PLATFORM_INFO);
  MaxBusRatio = PlatformInfoMsr.Bytes.SecondByte;
  MinBusRatio = PlatformInfoMsr.Bytes.SixthByte;

  BootRatio = MinBusRatio;
  BootFrequencyMode = (UINT8) CpuConfigLibPreMemConfig->BootFrequency;

  ///
  /// Temporarily enable EIST on BSP.
  ///
  MiscEnable.Uint64 = AsmReadMsr64 (MSR_IA32_MISC_ENABLE);
  MiscEnable.Bits.EIST = 1;
  AsmWriteMsr64 (MSR_IA32_MISC_ENABLE, MiscEnable.Uint64);

  if (CpuConfigLibPreMemConfig->BootFrequency == 2) {
    if (CpuPowerMgmtBasicConfig->TurboMode && (CpuPowerMgmtTestConfig->Eist || CpuPowerMgmtBasicConfig->Hwp)) {
      //
      // Set processor P state as TURBO_RATIO_LIMIT_1C if available
      //
      AsmCpuid (CPUID_THERMAL_POWER_MANAGEMENT, &Eax.Uint32, NULL, NULL, NULL);
      if ((Eax.Bits.TurboBoostTechnology == 1) ||
          ((MiscEnable.Uint64 & B_MSR_MISC_ENABLES_TURBO_MODE_DISABLE_MASK) == B_MSR_MISC_ENABLES_TURBO_MODE_DISABLE_MASK)) {
        //
        // Enable Turbo
        //
        MiscEnable.Uint64 &= ~B_MSR_MISC_ENABLES_TURBO_MODE_DISABLE_MASK;
        AsmWriteMsr64 (MSR_IA32_MISC_ENABLE, MiscEnable.Uint64);
        //
        // Set Boot Ratio to TURBO_RATIO_LIMIT_1C
        //
        BootRatio = (UINT8) (AsmReadMsr64 (MSR_TURBO_RATIO_LIMIT) & B_MSR_TURBO_RATIO_LIMIT_MAX_TURBO_1_CORE_MASK);
      } else {
        //
        // Turbo is not available, down to HFM
        //
        DEBUG ((DEBUG_INFO, "CPU: Turbo mode is not available, down to HFM mode.\n"));
        BootFrequencyMode = 1;
        BootRatio = MaxBusRatio;
      }
    } else {
      //
      // Turbo is disabled, down to HFM
      //
      BootFrequencyMode = 1;
      BootRatio = MaxBusRatio;
    }
  } else if (CpuConfigLibPreMemConfig->BootFrequency == 1) {
    BootRatio = MaxBusRatio;
  } else {
    BootRatio = MinBusRatio;
  }

  ///
  /// If there are any configurable TDP Levels supported, set the boot ratio
  /// based on BootFrequencyMode and cTDP TAR ratio.
  ///
  PlatformInfoMsr.Qword &= B_MSR_PLATFORM_INFO_CONFIG_TDP_LEVELS_MASK;
  NumberOfConfigTdpLevels = (UINT8) RShiftU64 (PlatformInfoMsr.Qword, N_MSR_PLATFORM_INFO_CONFIG_TDP_LEVELS_OFFSET);
  if (NumberOfConfigTdpLevels != 0) {
    //
    // Find the selected level and the TAR ratio.
    //
    SupportedCtdpLevels = NumberOfConfigTdpLevels + 1;
    SelectedCtdpLevel = (UINT8) CpuPowerMgmtTestConfig->ConfigTdpLevel;

    //
    // Select cTDP Nominal if cTDP is disabled or the level is not supported.
    //
    if (SelectedCtdpLevel == CONFIG_TDP_DEACTIVATE || SelectedCtdpLevel >= SupportedCtdpLevels) {
      SelectedCtdpLevel = 0;
    }

    if (SelectedCtdpLevel >= 3) {
      DEBUG ((DEBUG_ERROR, "ERROR: Invalid SelectedCtdpLevel=%x, and SelectedCtdpLevel should be range in 0-2 \n", SelectedCtdpLevel));
      ASSERT (FALSE);
      return;
    }

    if (CpuPowerMgmtCustomConfig->CustomConfigTdpTable[SelectedCtdpLevel].CustomTurboActivationRatio != 0) {
      CtdpTarRatioPlusOne = (UINT8) CpuPowerMgmtCustomConfig->CustomConfigTdpTable[SelectedCtdpLevel].CustomTurboActivationRatio + 1;
    } else {
      MsrValue.Qword = AsmReadMsr64 (MSR_CONFIG_TDP_NOMINAL + SelectedCtdpLevel);
      if (SelectedCtdpLevel == 0) {
        CtdpTarRatioPlusOne = MsrValue.Bytes.FirstByte;
      } else if (SelectedCtdpLevel == 1) {
        if (MsrValue.Bytes.ThirdByte == 0) {
          //
          // If Level1 was not valid, then read Level2 register
          //
          MsrValue.Qword = AsmReadMsr64 (MSR_CONFIG_TDP_LEVEL2);
        }
        CtdpTarRatioPlusOne = MsrValue.Bytes.ThirdByte;
      } else {
        CtdpTarRatioPlusOne = MsrValue.Bytes.ThirdByte;
      }
    }

    //
    // Make sure the TAR+1 ratio is between the fused min and (max+1) ratios.
    //
    if (CtdpTarRatioPlusOne < MinBusRatio) {
      CtdpTarRatioPlusOne = MinBusRatio;
    } else if (CtdpTarRatioPlusOne > MaxBusRatio + 1) {
      CtdpTarRatioPlusOne = MaxBusRatio + 1;
    }

    if (BootFrequencyMode == 2) {
      //
      // Use TAR Ratio + 1 to go to Turbo mode once ConfigTDP is fully configured and the TAR ratio MSR is configured.
      //
      BootRatio = CtdpTarRatioPlusOne;
    } else if (BootFrequencyMode == 1) {
      //
      // Use TAR Ratio as max non-turbo ratio, which is equal to ConfigTDP boot ratio - 1.
      //
      BootRatio = CtdpTarRatioPlusOne - 1;

      //
      // If EIST is disabled use ConfigTDP boot ratio, which is equal to TAR+1.
      //
      if (!CpuPowerMgmtTestConfig->Eist) {
        BootRatio = BootRatio + 1;
      }
    } else {
      //
      // Use MinBusRatio (LFM) unless ConfigTDP boot ratio is equal to LFM.
      // In that case, use 'fake' P-State of ConfigTDP boot ratio - 1, which is equal to TAR ratio.
      //
      BootRatio = MinBusRatio;
      if ((CtdpTarRatioPlusOne == MinBusRatio) && CpuPowerMgmtTestConfig->Eist) {
        BootRatio = CtdpTarRatioPlusOne - 1;
      }
    }
  }

  ///
  /// Set MSR_IA32_PERF_CTL on BSP.
  ///
  ApSafeSetBootPState (&BootRatio);

  ///
  /// Set MSR_IA32_PERF_CTL on all APs unless disabled by policy setting.
  ///
  if (CpuPowerMgmtBasicConfig->SkipSetBootPState != CPU_FEATURE_ENABLE) {
    gMpServicesPpi->StartupAllAPs (
                      PeiServices,
                      gMpServicesPpi,
                      (EFI_AP_PROCEDURE) ApSafeSetBootPState,
                      FALSE,
                      0,
                      &BootRatio
                      );
  }
}

/**
  Initialize performance and power management features before RESET_CPL at Post-memory phase.

  @param[in] PeiServices     Pointer to PEI Services Table
  @param[in] SiPolicyPpi     The SI Policy PPI instance.
**/
VOID
CpuInitPreResetCpl (
  IN CONST EFI_PEI_SERVICES   **PeiServices,
  IN SI_POLICY_PPI             *SiPolicyPpi
  )
{
  EFI_STATUS                  Status;
  CPUID_VERSION_INFO_ECX      Ecx;
  CPU_TEST_CONFIG             *CpuTestConfig;
  CPU_CONFIG                  *CpuConfig;

  DEBUG((DEBUG_INFO, "CpuInitPreResetCpl Start \n"));
  PostCode (0xC20);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuTestConfigGuid, (VOID *) &CpuTestConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCpuConfigGuid, (VOID *) &CpuConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG((DEBUG_INFO, "ProcessorsPrefetcherInitialization Start \n"));
  PostCode (0xC21);

  ///
  /// Initializes Processor Prefetcher
  ///
  ProcessorsPrefetcherInitialization (
          CpuTestConfig->MlcStreamerPrefetcher,
          CpuTestConfig->MlcSpatialPrefetcher
          );

  DEBUG((DEBUG_INFO, "InitRatl Start \n"));
  PostCode (0xC22);

  ///
  /// Program Tcc Activation Offset and  Running Average Temperature Limit (RATL)
  ///
  InitRatl (SiPolicyPpi);

  DEBUG((DEBUG_INFO, "ConfigureSvidVrs Start \n"));
  PostCode (0xC23);

  ///
  /// Program Skylake platform power and SVID VR's
  ///
  ConfigureSvidVrs (SiPolicyPpi);

  DEBUG((DEBUG_INFO, "ConfigurePidSettings Start \n"));
  PostCode (0xC24);

  ///
  /// Program PID Settings
  ///
  ConfigurePidSettings (SiPolicyPpi);

  ///
  /// Check to see if CPU supports EIST capability.
  ///
  if (CpuConfig->SkipMpInit == 0) {
    AsmCpuid (CPUID_VERSION_INFO, NULL, NULL, &Ecx.Uint32, NULL);
    if (Ecx.Bits.EIST == 1) {
      DEBUG((DEBUG_INFO, "SetBootFrequency Start \n"));
      PostCode (0xC25);
      ///
      /// Program Boot Frequency on all threads.
      ///
      SetBootFrequency (PeiServices, SiPolicyPpi);
    }
  }

  ///
  /// BIOS Guard Initialization
  ///
  BiosGuardInit (SiPolicyPpi);

  DEBUG((DEBUG_INFO, "CpuInitPreResetCpl Done \n"));
  PostCode (0xC3F);

  return;
}
