/** @file
  This file contains define definitions specific to processor

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
#ifndef _POWER_MGMT_DEFINITIONS_H_
#define _POWER_MGMT_DEFINITIONS_H_

#define CSTATE_SUPPORTED          0x1
#define ENHANCED_CSTATE_SUPPORTED 0x2
#define C6_C7_SHORT_LATENCY_SUPPORTED 0x01
#define C6_C7_LONG_LATENCY_SUPPORTED  0x02
#define C7s_SHORT_LATENCY_SUPPORTED   0x03
#define C7s_LONG_LATENCY_SUPPORTED    0x04
//
// Voltage offset definitions
//
#define OC_LIB_OFFSET_ADAPTIVE  0
#define OC_LIB_OFFSET_OVERRIDE  1
//
// Platform Power Management Flags Bit Definitions:
//   These defines are also used in CPU0CST.ASL to check platform configuration
//   and build C-state table accordingly.
//
#ifdef __GNUC__
//
// @todo Add workaround for GCC build, In GCC build the BIT can not be changed to value by GCC (ex: BIT0 can not be changed to 0x1)
//
#define PPM_EIST                0x1        ///< BIT 0 : Enhanced Intel Speed Step Technology.
#define PPM_C1                  0x2        ///< BIT 1 : C1 enabled, supported.
#define PPM_C1E                 0x4        ///< BIT 2 : C1E enabled.
#define PPM_C6                  0x10       ///< BIT 4 : C6 enabled, supported.
#define PPM_C7                  0x20       ///< BIT 5 : C7 enabled, supported.
#define PPM_C7S                 0x40       ///< BIT 6 : C7S enabled, supported
#define PPM_TM                  0x80       ///< BIT 7 : Adaptive Thermal Monitor.
#define PPM_TURBO               0x100      ///< BIT 8 : Long duration turbo mode
#define PPM_CMP                 0x200      ///< BIT 9 : CMP.
#define PPM_TSTATES             0x400      ///< BIT 10: CPU throttling states
#define PPM_MWAIT_EXT           0x800      ///< BIT 11: MONITIOR/MWAIT Extensions supported.
#define PPM_EEPST               0x1000     ///< BIT 12: Energy efficient P-State Feature enabled
#define PPM_TSTATE_FINE_GRAINED 0x2000     ///< BIT 13: Fine grained CPU Throttling states
#define PPM_CD                  0x4000     ///< BIT 14: Deep Cstate - C8/C9/C10
#define PPM_TIMED_MWAIT         0x8000     ///< BIT 15: Timed Mwait support
#define C6_LONG_LATENCY_ENABLE  0x10000    ///< BIT 16: 1=C6 Long and Short,0=C6 Short only
#define C7_LONG_LATENCY_ENABLE  0x20000    ///< BIT 17: 1=C7 Long and Short,0=C7 Short only
#define C7s_LONG_LATENCY_ENABLE 0x40000    ///< BIT 18: 1=C7s Long and Short,0=C7s Short only
#define PPM_C8                  0x80000    ///< Bit 19: 1= C8 enabled/supported
#define PPM_C9                  0x100000   ///< Bit 20: 1= C9 enabled/supported
#define PPM_C10                 0x200000   ///< Bit 21: 1= C10 enabled/supported
#define PPM_HWP                 0x400000   ///< Bit 22: 1= HWP enabled/supported
#define PPM_OC_UNLOCKED         0x1000000  ///< Bit 24: 1= Overclocking fully uncloked
#define PPM_TURBO_BOOST_MAX     0x2000000  ///< Bit 25: 1= Intel Turbo Boost Max Technology 3.0.
#else
#define PPM_EIST                BIT0   ///< Enhanced Intel Speed Step Technology.
#define PPM_C1                  BIT1   ///< C1 enabled, supported.
#define PPM_C1E                 BIT2   ///< C1E enabled.
#define PPM_C6                  BIT4   ///< C6 enabled, supported.
#define PPM_C7                  BIT5   ///< C7 enabled, supported.
#define PPM_C7S                 BIT6   ///< C7S enabled, supported
#define PPM_TM                  BIT7   ///< Adaptive Thermal Monitor.
#define PPM_TURBO               BIT8   ///< Long duration turbo mode
#define PPM_CMP                 BIT9   ///< CMP.
#define PPM_TSTATES             BIT10  ///< CPU throttling states
#define PPM_MWAIT_EXT           BIT11  ///< MONITIOR/MWAIT Extensions supported.
#define PPM_EEPST               BIT12  ///< Energy efficient P-State Feature enabled
#define PPM_TSTATE_FINE_GRAINED BIT13  ///< Fine grained CPU Throttling states
#define PPM_CD                  BIT14  ///< Deep Cstate - C8/C9/C10
#define PPM_TIMED_MWAIT         BIT15  ///< Timed Mwait support
#define C6_LONG_LATENCY_ENABLE  BIT16  ///< 1=C6 Long and Short,0=C6 Short only
#define C7_LONG_LATENCY_ENABLE  BIT17  ///< 1=C7 Long and Short,0=C7 Short only
#define C7s_LONG_LATENCY_ENABLE BIT18  ///< 1=C7s Long and Short,0=C7s Short only
#define PPM_C8                  BIT19  ///< 1= C8 enabled/supported
#define PPM_C9                  BIT20  ///< 1= C9 enabled/supported
#define PPM_C10                 BIT21  ///< 1= C10 enabled/supported
#define PPM_HWP                 BIT22  ///< 1= HWP enabled/supported
#define PPM_OC_UNLOCKED         BIT24  ///< 1= Overclocking fully unlocked
#define PPM_TURBO_BOOST_MAX     BIT25  ///< 1= Intel Turbo Boost Max Technology 3.0
#endif

#define PPM_C_STATES            0x72    ///< PPM_C1 + PPM_C6 + PPM_C7 + PPM_C7S
#define C6_C7_SHORT_LATENCY     0x76
#define C6_C7_LONG_LATENCY      0x94
#define C8_LATENCY              0xFA
#define C9_LATENCY              0x14C
#define C10_LATENCY             0x3F2

//
// The following definitions are based on assumed location for the  ACPI
// Base Address.  Modify as necessary base on platform-specific requirements.
//
#define PCH_ACPI_PBLK 0x1810
#define PCH_ACPI_LV2  0x1814
#define PCH_ACPI_LV3  0x1815
#define PCH_ACPI_LV4  0x1816
#define PCH_ACPI_LV6  0x1818
#define PCH_ACPI_LV5  0x1817
#define PCH_ACPI_LV7  0x1819

//
// C-State Latency (us) and Power (mW) for C1
//
#define C1_LATENCY                        1
#define C1_POWER                          0x3E8
#define C3_POWER                          0x1F4
#define C6_POWER                          0x15E
#define C7_POWER                          0xC8
#define C8_POWER                          0xC8
#define C9_POWER                          0xC8
#define C10_POWER                         0xC8

#define MAX_POWER_LIMIT_1_TIME_IN_SECONDS 32767
#ifndef AUTO
#define AUTO                              0
#endif
#define END_OF_TABLE                      0xFF

#define CONFIG_TDP_DOWN                   1
#define CONFIG_TDP_UP                     2
#define CONFIG_TDP_DEACTIVATE             0xFF
//
// MMIO definitions
//
#define MMIO_DDR_RAPL_LIMIT     0x58e0
#define MMIO_TURBO_POWER_LIMIT  0x59A0

#define MAX_OVERCLOCKING_BINS   0x7

///
/// For Mobile and Halo, default PL1 time window value is 28 seconds
///
#define MB_POWER_LIMIT1_TIME_DEFAULT  28
///
/// For Desktop, default PL1 time window value is 8 second
///
#define DT_POWER_LIMIT1_TIME_DEFAULT  8

#define PROCESSOR_FLAVOR_MOBILE       0x04
#define PROCESSOR_FLAVOR_DESKTOP      0x00
#define PROCESSOR_FLAVOR_MASK         (BIT3 | BIT2)

//
// Power definitions (Based on EMTS V1.0 for standard voltage 2.4-2.6 GHz dual-core parts.)
//
#define FVID_MAX_POWER      35000
#define FVID_TURBO_POWER    35000
#define FVID_SUPERLFM_POWER 12000
//
// Power definitions for LFM and Turbo mode TBD.
//
#define FVID_MIN_POWER  15000

///
/// Limit the number of P-states for different generation OS.
///
#define TPSS_FVID_MAX_STATES                   40
#define LPSS_FVID_MAX_STATES                   16

#define READ_PL1_DUTY_CYCLE_CLAMP_ENABLE  0x00000015
#define WRITE_PL1_DUTY_CYCLE_CLAMP_ENABLE 0x00000016

//
//  VR mailbox commands
//
#define READ_VR_STRAP_CONFIG_CMD          0x80000018
#define READ_ACDC_LOADLINE_CMD            0x80000118
#define WRITE_ACDC_LOADLINE_CMD           0x80000218
#define READ_PSI_CUTOFF_CMD               0x80001318
#define WRITE_PSI_CUTOFF_CMD              0x80000318
#define READ_IMON_CONFIG_CMD              0x80001418
#define WRITE_IMON_CONFIG_CMD             0x80000418
#define READ_VR_ICC_MAX_CMD               0x80000518
#define WRITE_VR_ICC_MAX_CMD              0x80000618
#define READ_VR_VOLTAGE_LIMIT_CMD         0x80000718
#define WRITE_VR_VOLTAGE_LIMIT_CMD        0x80000818
#define READ_PSYS_PMAX_CMD                0x80000B17
#define WRITE_PSYS_CONFIG_CMD             0x80000918
#define WRITE_PSYS_PMAX_CMD               0x80000B18
#define READ_VR_TDC_CONFIG_CMD            0x80000019
#define WRITE_VR_TDC_CONFIG_CMD           0x8000001A
#define WRITE_VOLTAGE_OPTIMIZATION_CMD    0x8000001F
#define READ_PLL_VOLTAGE_OFFSET_CMD       0x8000002C
#define WRITE_PLL_VOLTAGE_OFFSET_CMD      0x8000002D
#define WRITE_MPS_VR_IMPV8_CMD            0x80000E18
#define WRITE_PS4_EXIT_VR_CMD             0x80000034
#define MPS_VR_CMD_REQUESTED              0x01
#define PS4_EXIT_VR_CMD_REQUESTED         0x02
#define WRITE_VCCIN_MIN_VOLTAGE           0x80000059

//
//  VR mailbox commands for Acoustic Noise Mitigation
//
#define WRITE_SVID_SET_VR_SLEW_RATE_CMD           0x80000C18
#define WRITE_SVID_SET_DISABLE_FAST_PKGC_RAMP_CMD 0x80000D18
#define READ_ACOUSTIC_MIGITATION_RANGE            0x80000007
#define WRITE_ACOUSTIC_MIGITATION_RANGE           0x80000008
#define NOISE_MIGITATION_RANGE_MASK               0xFF
#define RAMP_UP_OFFSET                            8
#define RAMP_DOWN_OFFSET                          16

#define VR_ADDRESS_MASK                   0xF
#define VR_ADDRESS_OFFSET                 16
#define AC_LOADLINE_MASK                  0xFFFF
#define DC_LOADLINE_MASK                  0xFFFF0000
#define VR_TDC_ADDRESS_OFFSET             8
#define DC_LOADLINE_OFFSET                16
#define AC_DC_LOADLINE_MAX                6249 ///< 62.49 mOhm max
#define PSI_THRESHOLD_MASK                0x3FF
#define PSI2_THRESHOLD_OFFSET_MASK        0xFFC00
#define PSI3_THRESHOLD_OFFSET_MASK        0x3FF00000
#define PSI2_THRESHOLD_OFFSET             10
#define PSI3_THRESHOLD_OFFSET             20
#define PSI3_ENABLE_OFFSET                30
#define PSI4_ENABLE_OFFSET                31
#define VR_IMON_SLOPE_OFFSET              16
#define VR_IMON_SLOPE_MASK                0xFFFF0000
#define VR_IMON_OFFSET_MASK               0xFFFF
#define VR_VOLTAGE_LIMIT_MASK             0xFFFF
#define PSYS_SLOPE_OFFSET                 8
#define VR_TDC_CURRENT_LIMIT_MASK         0x7FFF
#define VR_TDC_TIME_WINDOW_MASK           0x7F
#define VR_TDC_TIME_WINDOW_LOCATION_MASK  0xFE0000
#define VR_TDC_ENABLE_OFFSET              15
#define VR_TDC_TIME_WINDOW_OFFSET         17
#define VR_TDC_LOCK_OFFSET                31
#define VR_TDC_TIME_WINDOW_MAX            10

//
//  PID Tuning mailbox commands
//
#define WRITE_PID_RATL                    0x80000021
#define WRITE_PID_VR0_TDC                 0x81000021
#define WRITE_PID_VR1_TDC                 0x81010021
#define WRITE_PID_VR2_TDC                 0x81020021
#define WRITE_PID_VR3_TDC                 0x81030021
#define WRITE_PID_PSYS_PL1_MSR            0x82000021
#define WRITE_PID_PSYS_PL1_MMIO           0x82010021
#define WRITE_PID_PSYS_PL2_MSR            0x82020021
#define WRITE_PID_PSYS_PL2_MMIO           0x82030021
#define WRITE_PID_PKG_PL1_MSR             0x82040021
#define WRITE_PID_PKG_PL1_MMIO            0x82050021
#define WRITE_PID_PKG_PL2_MSR             0x82060021
#define WRITE_PID_PKG_PL2_MMIO            0x82070021
#define WRITE_PID_DDR_PL1_MSR             0x82080021
#define WRITE_PID_DDR_PL1_MMIO            0x82090021
#define WRITE_PID_DDR_PL2_MSR             0x820A0021
#define WRITE_PID_DDR_PL2_MMIO            0x820B0021
#define PID_DOMAIN_KP                     0
#define PID_DOMAIN_KI                     1
#define PID_DOMAIN_KD                     2
#define MAILBOX_PARAM_1_OFFSET            8

///
/// Elixir Springs Mailbox commands
///

#define SVID_GET_REGISTER         0x80001018
#define SVID_SET_REGISTER         0x80001118
#define SVID_SET_EXCLUSIVE        0x80001218
#define SVID_READ_REG_WHITELIST   0x80001518
#define SVID_WRITE_REG_WHITELIST  0x80001618


#define SVID_REGISTER_VR_ID_OFFSET    16
#define SVID_REGISTER_VR_ID_VIRTUAL_0  4
#define SVID_REGISTER_VR_ID_VIRTUAL_1  5
#define SVID_REGISTER_ADDR_OFFSET     20
#define SVID_WHITELIST_DWORD_OFFSET   20

#define SVID_EXCLUSIVE_DISABLE  0
#define SVID_EXCLUSIVE_ENABLE   1

#define ELIXIR_VENDOR_ID_MAILBOX_ADDRESS    0
#define ELIXIR_PRODUCT_ID_MAILBOX_ADDRESS   1
#define ELIXIR_PRODUCT_REV_MAILBOX_ADDRESS  2
#define ELIXIR_LOT_CODE_MAILBOX_ADDRESS     4

#define ELIXIR_VENDOR_ID_INTEL  0x14


///
///  VR Domain Definitions
///
#define CPU_VR_DOMAIN_SA           0x0
#define CPU_VR_DOMAIN_IA           0x1
#define CPU_VR_DOMAIN_RING         0x2
#define CPU_VR_DOMAIN_GT           0x3
#define CPU_VR_DOMAIN_FIVR         0x4

///
///  RFI Definitions
///
#define CLOCK_FREQUENCY_19MHz                    19200000
#define CLOCK_FREQUENCY_24MHz                    24000000
#define CLOCK_FREQUENCY_38MHz                    38400000

#define R_EMI_CONTROL_0_0_0_MCHBAR_PCU           0x5A08
#define B_SPREAD_SPECTRUM_ENABLE                 BIT8
#define B_SPREAD_SPECTRUM_MASK                   0xFF
#define V_SPREAD_SPECTRUM_POINT_ONE_ENCODING_MAX 0x1C
#define V_FIVR_SPREAD_SPECTRUM_MAX               0x3F

//24MHz XTAL Clock Frequency
#define R_RFI_CONTROL_0_0_0_MCHBAR_PCU           0x5A0C
#define N_RFI_FREQ_LO_PF2_OFFSET                 2
#define N_RFI_FREQ_HI_PF2_OFFSET                 16
#define B_RFI_FREQ_PF2_MASK                      (BIT23 | BIT22 | BIT21 | BIT20 | BIT19 | BIT18 | BIT17 | BIT16 | BIT3 | BIT2)

//38.4MHx XTAL Clock Frequency
#define R_RFI_CONTROL2_0_0_0_MCHBAR_PCU          0x5A18
#define N_RFI_FREQ_LO_PF3_OFFSET                 10
#define N_RFI_FREQ_HI_PF3_OFFSET                 16
#define B_RFI_FREQ_PF3_MASK                      (BIT23 | BIT22 | BIT21 | BIT20 | BIT19 | BIT18 | BIT17 | BIT16 | BIT11 | BIT10)

#define B_RFI_FREQ_ADJ_MASK                      0xFF
#define V_RFI_FREQ_ADJ_MAX                       0x7F
#define B_RFI_FREQ_SPREAD_MASK                   0xFF00
#define B_RFI_FREQ_UPDATE_MASK                   0xFFFF
#define N_RFI_FREQ_LO_PF1_OFFSET                 0
#define N_RFI_FREQ_HI_PF1_OFFSET                 8
#define B_RFI_FREQ_PF1_MASK                      (BIT15 | BIT14 | BIT13 | BIT12 | BIT11 | BIT10 | BIT9 | BIT8 | BIT1 | BIT0)
#define N_RFI_FREQ_LO_PF2_OFFSET                 2
#define N_RFI_FREQ_HI_PF2_OFFSET                 16
#define B_RFI_FREQ_PF2_MASK                      (BIT23 | BIT22 | BIT21 | BIT20 | BIT19 | BIT18 | BIT17 | BIT16 | BIT3 | BIT2)
#define N_RFI_FREQ_LO_PF3_OFFSET                 10
#define N_RFI_FREQ_HI_PF3_OFFSET                 16
#define B_RFI_FREQ_PF3_MASK                      (BIT23 | BIT22 | BIT21 | BIT20 | BIT19 | BIT18 | BIT17 | BIT16 | BIT11 | BIT10)
#define R_RFI_STATUS_0_0_0_MCHBAR_PCU            0x5A10
#define B_RFI_CURRENT_FREQ_MASK                  0xFFF
#define V_MAX_RFI_VALUE                          0x3FF

///
///  VR default override values
///


#define CPU_TDP_15_WATTS       1500
#define CPU_TDP_28_WATTS       2800
#define CPU_TDP_35_WATTS       3500
#define CPU_TDP_45_WATTS       4500
#define CPU_TDP_54_WATTS       5400
#define CPU_TDP_58_WATTS       5800
#define CPU_TDP_62_WATTS       6200
#define CPU_TDP_65_WATTS       6500
#define CPU_TDP_91_WATTS       9100
#define CPU_TDP_95_WATTS       9500
#define CPU_TDP_120_WATTS      12000

//
//  CFL-X 62
//
#define IA_AC_DC_LL_DEFAULT_CFL_X_6_2    105

///
/// HDC Definitions
///
#define N_HDC_SUPPORT                 0
#define B_HDC_SUPPORT                 BIT0

///
/// Used to identify the CPU used for programming with the VR override table
///
typedef enum {
  EnumUnknownCpuId             = 0,
  EnumMinCpuId                 = 1,
  ///
  /// EHL
  ///
  EnumEhl10Watt18fMblSku1CpuId   = 0x1,
  EnumEhl10Watt20fMblSku2CpuId   = 0x2,
  EnumEhl6Watt12fmblSku3CpuId    = 0x3,
  EnumEhl6Watt12fmblSku4CpuId    = 0x4,
  EnumEhl12Watt18fDtSku7CpuId    = 0x7,
  EnumEhl6Watt15fDtSku5CpuId     = 0x5,
  EnumEhl9Watt17fDtSku6CpuId     = 0x6,
  EnumEhl6Watt15fInduSku8CpuId   = 0x8,
  EnumEhl9Watt17fInduSku9CpuId   = 0x9,
  EnumEhl12Watt19fInduSku10CpuId = 0xA,
  EnumEhl4Watt10fInduSku12CpuId  = 0xC,
  EnumEhl12Watt19fInduSku11CpuId = 0xB,
  EnumEhlMaxCpuId                = EnumEhl12Watt19fInduSku11CpuId,

  ///
  /// TGL-Y
  ///
  EnumTglY9WattES1NoExsCpuId   = 0x16,
  EnumTglY9Watt42fNoExsCpuId   = 0x17,
  EnumTglY9WattES1ExsCpuId     = 0x18,
  EnumTglY9Watt42fExsCpuId     = 0x19,
  EnumTglYMaxCpuId             = EnumTglY9Watt42fExsCpuId,
  ///
  /// TGL-U
  ///
  EnumTglU28WattES1CTdpNoExsCpuId  = 0x1A,
  EnumTglU28Watt42fCTdpNoExsCpuId  = 0x1B,
  EnumTglU28WattES1NoExsCpuId      = 0x1C,
  EnumTglU28Watt42fNoExsCpuId      = 0x1D,
  EnumTglU28Watt42fExsCpuId        = 0x1E,
  EnumTglU28WattES1ExsCpuId        = 0x1F,
  EnumTglU28WattES1CTdpExsCpuId    = 0x22,
  EnumTglU28Watt42fCTdpExsCpuId    = 0x23,
  EnumTglUMaxCpuId                 = EnumTglU28Watt42fCTdpExsCpuId,
  ///
  /// TGL-H
  ///
  EnumTglH45Watt81ExsCpuId     = 0xD,
  EnumTglH45Watt81NoExsCpuId   = 0xE,
  EnumTglH65Watt81ExsCpuId     = 0xF,
  EnumTglH65Watt81NoExsCpuId   = 0x10,
  EnumTglH95Watt81ExsCpuId     = 0x11,
  EnumTglH95Watt81NoExsCpuId   = 0x12,
  EnumTglHMaxCpuId             = EnumTglH95Watt81NoExsCpuId,
  ///
  /// WHL
  ///
  EnumWhlU15Watt42fCpuId       = 0x20,
  EnumWhlU15Watt22fCpuId       = 0x24,
  EnumWhlU15Watt2f1fCpuId      = 0x21,
  EnumWhlUMaxCpuId             = EnumWhlU15Watt2f1fCpuId,

  EnumMaxCpuId                 = EnumWhlUMaxCpuId,
} CPU_OVERRIDE_IDENTIFIER;

///
/// VR Override table structure
///
typedef struct {
  CPU_OVERRIDE_IDENTIFIER  CpuIdentifier;
  UINT16 IaIccMax;
  UINT16 GtIccMax;
  UINT16 SaIccMax;
  UINT16 VccInIccMax;
  UINT16 IaTdclimit;
  UINT16 GtTdclimit;
  UINT16 SaTdclimit;
  UINT16 VccInTdclimit;
  UINT16 IaAcLoadLine;
  UINT16 IaDcLoadLine;
  UINT16 GtAcLoadLine;
  UINT16 GtDcLoadLine;
  UINT16 SaAcLoadLine;
  UINT16 SaDcLoadLine;
  UINT16 VccInAcLoadLine;
  UINT16 VccInDcLoadLine;
  UINT16 VrVoltageLimit;
} CPU_VR_OVERRIDE_TABLE;
#endif
