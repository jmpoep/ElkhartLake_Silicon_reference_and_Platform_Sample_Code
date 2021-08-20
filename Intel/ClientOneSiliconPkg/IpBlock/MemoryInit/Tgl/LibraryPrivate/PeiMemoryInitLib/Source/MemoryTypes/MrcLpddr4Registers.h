/** @file
  Definition of LPDDR4 Registers.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2018 Intel Corporation.

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

#ifndef _MRC_LPDDR4_REGISTERS_H_
#define _MRC_LPDDR4_REGISTERS_H_

/// Enumerations and Defines
#define LPDDR4_VREF_FIELD_MAX (51)

typedef enum {
  Lp4Bl16,
  Lp4Bl32,
  Lp4BlOnTheFly,
  Lp4BlMax
} LPDDR4_BL;

typedef enum {
  Lp4WrPreReserved,
  Lp4WrPre2Tck,
  Lp4WrPreMax
} LPDDR4_WR_PREAMBLE_LEN;

typedef enum {
  Lp4RdPreStatic,
  Lp4RdPreToggle,
  Lp4RdPreMax
} LPDDR4_RD_PREAMBLE_TYPE;

typedef enum {
  Lp4x16Wr6,
  Lp4x16Wr10,
  Lp4x16Wr16,
  Lp4x16Wr20,
  Lp4x16Wr24,
  Lp4x16Wr30,
  Lp4x16Wr34,
  Lp4x16Wr40,
  Lp4x16WrMax
} LPDDR4_X16_WRITE_RECOVERY;

typedef enum {
  Lp4x8Wr6,
  Lp4x8Wr12,
  Lp4x8Wr16,
  Lp4x8Wr22,
  Lp4x8Wr28,
  Lp4x8Wr32,
  Lp4x8Wr38,
  Lp4x8Wr44,
  Lp4x8WrMax
} LPDDR4_X8_WRITE_RECOVERY;

typedef enum {
  Lp4RdPst0_5Tck,
  Lp4RdPst1_5Tck,
  Lp4RstPstMax
} LPDDR4_RD_POSTAMBLE_LEN;

typedef enum {
  Lp4x16Rl6,
  Lp4x16Rl10,
  Lp4x16Rl14,
  Lp4x16Rl20,
  Lp4x16Rl24,
  Lp4x16Rl28,
  Lp4x16Rl32,
  Lp4x16Rl36,
  Lp4x16RlMax
} LPDDR4_X16_RD_LATENCY;

typedef enum {
  Lp4x8Rl6,
  Lp4x8Rl10,
  Lp4x8Rl16,
  Lp4x8Rl22,
  Lp4x8Rl26,
  Lp4x8Rl32,
  Lp4x8Rl36,
  Lp4x8Rl40,
  Lp4x8RlMax
} LPDDR4_X8_RD_LATENCY;

typedef enum {
  Lp4DbiRl6,
  Lp4DbiRl12,
  Lp4DbiRl16,
  Lp4DbiRl22,
  Lp4DbiRl28,
  Lp4DbiRl32,
  Lp4DbiRl36,
  Lp4DbiRl40,
  Lp4DbiRlMax
} LPDDR4_DBI_RD_LATENCY;

typedef enum {
  Lp4WlA4,
  Lp4WlA6,
  Lp4WlA8,
  Lp4WlA10,
  Lp4WlA12,
  Lp4WlA14,
  Lp4WlA16,
  Lp4WlA18,
  Lp4WlAMax
} LPDDR4_WR_LATENCY_A;

typedef enum {
  Lp4WlB4,
  Lp4WlB8,
  Lp4WlB12,
  Lp4WlB18,
  Lp4WlB22,
  Lp4WlB26,
  Lp4WlB30,
  Lp4WlB34,
  Lp4WlBMax
} LPDDR4_WR_LATENCY_B;

typedef enum {
  Lp4WlSetA,
  Lp4WlSetB,
  Lp4WlSetMax
} LPDDR4_WR_LATENCY_SET;

typedef enum {
  Lp4WlModeDis,
  Lp4WlModeEn,
  Lp4WlModeMax
} LPDDR4_WR_LEVELING_MODE;

/// CA, DQ, and SOC ODT fields share the same encoding.
typedef enum {
  Lp4OdtOff,  ///< Disabled, Reset default
  Lp4Odt240,  ///< RZQ/1
  Lp4Odt120,  ///< RZQ/2
  Lp4Odt80,   ///< RZQ/3
  Lp4Odt60,   ///< RZQ/4
  Lp4Odt48,   ///< RZQ/5
  Lp4Odt40,   ///< RZQ/6
  Lp4OdtMax
} LPDDR4_ODT_ENCODING;

typedef enum {
  Lp4PuCal2_5,  ///< VDDQ / 2.5
  Lp4PuCal3,    ///< VDDQ / 3 (Reset default)
  Lp4PuCalMax
} LPDDR4_PU_CAL;

typedef enum {
  Lp4xPuCal0_6, ///< VDDQ * 0.6
  Lp4xPuCal0_5, ///< VDDQ * 0.5
  Lp4xPuCalMax
} LPDDR4X_PU_CAL;

typedef enum {
  Lp4WrPst0_5,  ///< 0.5tCK (Reset default)
  Lp4WrPst1_5,  ///< 1.5tCK
  Lp4WrPstMax
} LPDDR4_WR_POSTAMBLE;

typedef enum {
  Lp4PprProtectDis,
  Lp4PprProtectEn,
  Lp4PprProtectMax
} LPDDR4_POST_PACKAGE_REPAIR_PROTECTION;

typedef enum {
  Lp4RdDbiDis,  ///< (Reset default)
  Lp4RdDbiEn,
  Lp4RdDbiMax
} LPDDR4_DBI_RD;

typedef enum {
  Lp4WrDbiDis,  ///< (Reset default)
  Lp4WrDbiEn,
  Lp4WrDbiMax
} LPDDR4_DBI_WR;

/// CA Vref and DQ Vref Range fields are the same.  So we have only 1 enum.
typedef enum {
  Lp4VrefRange0,
  Lp4VrevRange1,   ///< Reset default
  Lp4VrefRangeMax
} LPDDR4_VREF_RANGE;

typedef enum {
  Lp4CbtDis,
  Lp4CbtEn,
  Lp4CbtMax
} LPDDR4_CMD_BUS_TRAINING_MODE;

typedef enum {
  Lp4RptDis,
  Lp4RptEn,
  Lp4RptMax
} LPDDR4_RD_PREAMBLE_TRAINING_MODE;

typedef enum {
  Lp4VroDis,
  Lp4VroEn,
  Lp4VroMax
} LPDDR4_VREF_OUTPUT;

typedef enum {
  Lp4VrcgNormal,
  Lp4VrcgHighCurrent,
  Lp4VrcgMax
} LPDDR4_VREF_CURRENT_GEN;

typedef enum {
  Lp4RroDisCodes1_2,  ///< Disables code 001 and 010 in MR4 OP[2:0]
  Lp4RroAllCodes,
  Lp4RroMax
} LPDDR4_REFRESH_RATE_OPTION;

typedef enum {
  Lp4DmEn,
  Lp4DmDis,
  Lp4DmMax
} LPDDR4_DATA_MASK_MODE;

typedef enum {
  Lp4FspWePoint0,
  Lp4FspWePoint1,
  Lp4FspWeMax
} LPDDR4_FSP_WRITE_EN;

typedef enum {
  Lp4FspOpPoint0,
  Lp4FspOpPoint1,
  Lp4FspOpMax
} LPDDR4_FSP_OP_MODE;

typedef enum {
  Lp4CkOdtDis,  ///< Override Disabled.
  Lp4CkOdtEn,   ///< Override Enabled.
  Lp4CkOdtMax
} LPDDR4_CK_ODT_EN;

typedef enum {
  Lp4xCkOdtEn,
  Lp4xCkOdtDis,
  Lp4xCkOdtMax
} LPDDR4X_CK_ODT_EN;

typedef enum {
  Lp4CsOdtDis,  ///< Override Disabled.
  Lp4CsOdtEn,   ///< Override Enabled.
  Lp4CsOdtMax
} LPDDR4_CS_ODT_EN;

typedef enum {
  Lp4xCsOdtEn,
  Lp4xCsOdtDis,
  Lp4xCsOdtMax
} LPDDR4X_CS_ODT_EN;

typedef enum {
  Lp4CaOdtEn,   ///< Obeys ODT_CA bond pad in Lp4.  Lp4x ignores bond pad.
  Lp4CaOdtDis,
  Lp4CaOdtMax
} LPDDR4_CA_ODT_EN;

/// Structure Definitions
#pragma pack(push, 1)
/// Mode Register 0 is Read Only.
typedef union {
  struct {
    UINT8 RefreshMode   : 1;  ///< Bits 0:0
    UINT8               : 2;  ///< Bits 1:2
    UINT8 ZqSelfTest    : 2;  ///< Bits 3:4
    UINT8               : 2;  ///< Bits 5:6
    UINT8 CaTermRank    : 1;  ///< Bits 7:7
  } Bits;
  UINT8 Data8;
} LPDDR4_MODE_REGISTER_0_TYPE;

typedef union {
  struct {
    UINT8 BurstLength       : 2;  ///< Bits 0:1
    UINT8 WritePreambleLen  : 1;  ///< Bits 2:2
    UINT8 RdPreambleType    : 1;  ///< Bits 3:3
    UINT8 WrRecovery        : 3;  ///< Bits 4:6
    UINT8 RdPostAmbleLen    : 1;  ///< Bits 7:7
  } Bits;
  UINT8 Data8;
} LPDDR4_MODE_REGISTER_1_TYPE;

typedef union {
  struct {
    UINT8 RdLatency       : 3;  ///< Bits 0:2
    UINT8 WrLatency       : 3;  ///< Bits 3:5
    UINT8 WrLatencySet    : 1;  ///< Bits 6:6
    UINT8 WrLevelingMode  : 1;  ///< Bits 7:7
  } Bits;
  UINT8 Data8;
} LPDDR4_MODE_REGISTER_2_TYPE;

typedef union {
  struct {
    UINT8 PullUpCal       : 1;  ///< Bits 0:0
    UINT8 WrPostAmbleLen  : 1;  ///< Bits 1:1
    UINT8 PprProtection   : 1;  ///< Bits 2:2 - Post Package Repair Protection 0: Disabled, 1 Enabled.
    UINT8 PdDriveStrength : 3;  ///< Bits 3:5
    UINT8 DbiRdEn         : 1;  ///< Bits 6:6
    UINT8 DbiWrEn         : 1;  ///< Bits 7:7
  } Bits;
  UINT8 Data8;
} LPDDR4_MODE_REGISTER_3_TYPE;

typedef union {
  struct {
    UINT8 RefreshRate   : 3;  ///< Bits 0:2 - Read Only
    UINT8 SelfRefAbort  : 1;  ///< Bits 3:3
    UINT8 PprMode       : 1;  ///< Bits 4:4 - 0: Exit PPR Mode, 1: Enter PPR Mode.
    UINT8 ThermalOffset : 2;  ///< Bits 5:6
    UINT8 TempUpdteFlag : 1;  ///< Bits 7:7 - Read Only
  } Bits;
  UINT8 Data8;
} LPDDR4_MODE_REGISTER_4_TYPE;

/// Mode Register 8 is Read Only
typedef union {
  struct {
    UINT8 Type    : 2;  ///< Bits 0:1
    UINT8 Density : 4;  ///< Bits 2:5
    UINT8 IoWidth : 2;  ///< Bits 6:7
  } Bits;
  UINT8 Data8;
} LPDDR4_MODE_REGISTER_8_TYPE;

typedef union {
  struct {
    UINT8 DqOdt : 3;  ///< Bits 0:2
    UINT8       : 1;  ///< Bits 3:3
    UINT8 CaOdt : 3;  ///< Bits 4:6
    UINT8       : 1;  ///< Bits 7:7
  } Bits;
  UINT8 Data8;
} LPDDR4_MODE_REGISTER_11_TYPE;

/// Mode Register 12 is Read/Write
typedef union {
  struct {
    UINT8 CaVref      : 6;  ///< Bits 0:5
    UINT8 CaVrefRange : 1;  ///< Bits 6:6
    UINT8 CaCbtMode   : 1;  ///< Bits 7:7
  } Bits;
  UINT8 Data8;
} LPDDR4_MODE_REGISTER_12_TYPE;

typedef union {
  struct {
    UINT8 CbtMode   : 1;  ///< Bits 0:0 - Command Buffer Training Mode
    UINT8 RptMode   : 1;  ///< Bits 1:1 - Read Preamble Training Mode
    UINT8 VroMode   : 1;  ///< Bits 2:2 - Vref Output Mode
    UINT8 VrcgMode  : 1;  ///< Bits 3:3 - Vref Current Generator Mode
    UINT8 RroMode   : 1;  ///< Bits 4:4 - Refresh Rate Option
    UINT8 DmDisable : 1;  ///< Bits 5:5 - Data Mask Disable
    UINT8 FspWe     : 1;  ///< Bits 6:6 - Frequency Set Point Write Enable
    UINT8 FspOpMode : 1;  ///< Bits 7:7 - Frequency Set Point Operation Mode
  } Bits;
  UINT8 Data8;
} LPDDR4_MODE_REGISTER_13_TYPE;

/// Mode Register 14 is Read/Write
typedef union {
  struct {
    UINT8 DqVref      : 6;  ///< Bits 0:5
    UINT8 DqVrefRange : 1;  ///< Bits 6:6
    UINT8             : 1;  ///< Bits 7:7
  } Bits;
  UINT8 Data8;
} LPDDR4_MODE_REGISTER_14_TYPE;

typedef union {
  struct {
    UINT8 SocOdt        : 3;  ///< Bits 0:2
    UINT8 CkOdtEn       : 1;  ///< Bits 3:3
    UINT8 CsOdtEn       : 1;  ///< Bits 4:4
    UINT8 CaOdtEn       : 1;  ///< Bits 5:5
    UINT8 x8OdtDis7to0  : 1;  ///< Bit  6 - x8_2ch Byte mode
    UINT8 x8OdtDis15to8 : 1;  ///< Bit  7 - x8_2ch Byte mode
  } Bits;
  UINT8 Data8;
} LPDDR4_MODE_REGISTER_22_TYPE;

typedef union {
  struct {
    UINT8 DqsIntervalRunTime : 8;  ///< Bits 0:7
  } Bits;
  UINT8 Data8;
} LPDDR4_MODE_REGISTER_23_TYPE;

#pragma pack(pop)
#endif // _MRC_LPDDR4_REGISTERS_H_

