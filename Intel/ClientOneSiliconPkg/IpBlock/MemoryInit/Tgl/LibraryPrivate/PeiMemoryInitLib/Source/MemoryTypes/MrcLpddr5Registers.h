/** @file
  Definition of LPDDR5 Registers.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

#ifndef _MRC_LPDDR5_REGISTERS_H_
#define _MRC_LPDDR5_REGISTERS_H_

/// Enumerations and Defines
#define LPDDR5_VREF_FIELD_MAX (127)

typedef enum {
  Lp5LmX16,
  Lp5LmByteMode,
  Lp5LmMax
} LPDDR5_LATENCY_MODE;

typedef enum {
  Lp5CkmDifferential,
  Lp5CkmSingleEnd,
  Lp5CkmMax
} LPDDR5_CK_MODE;

/**
  This list is for DVFSC disabled, x16/x8 DRAM Set B Latency
**/
typedef enum {
  Lp5Wl4t1B2,
  Lp5Wl4t1B3,
  Lp5Wl4t1B4,
  Lp5Wl4t1B5,
  Lp5Wl4t1B7,
  Lp5Wl4t1B8,
  Lp5Wl4t1B9,
  Lp5Wl4t1B11,
  Lp5Wl4t1B12,
  Lp5Wl4t1B14,
  Lp5Wl4t1B15,
  Lp5Wl4t1B16,
  Lp5Wl4t1BMax
} LPDDR5_WR_LATENCY_4t1_B;

/**
  This list is for DVFSC disabled, x16, DBI Disabled
**/
typedef enum {
  Lp5RlRbtp4t1X16_3,
  Lp5RlRbtp4t1X16_4,
  Lp5RlRbtp4t1X16_5,
  Lp5RlRbtp4t1X16_6,
  Lp5RlRbtp4t1X16_8,
  Lp5RlRbtp4t1X16_9,
  Lp5RlRbtp4t1X16_10,
  Lp5RlRbtp4t1X16_12,
  Lp5RlRbtp4t1X16_13,
  Lp5RlRbtp4t1X16_15,
  Lp5RlRbtp4t1X16_16,
  Lp5RlRbtp4t1X16_17,
  Lp5RlRbtp4t1X16Max
} LPDDR5_RL_RBTP_4t1_x16;

/**
  This list is for DVFSC disabled, x8, DBI Disabled
**/
typedef enum {
  Lp5RlRbtp4t1X8_3,
  Lp5RlRbtp4t1X8_4,
  Lp5RlRbtp4t1X8_5,
  Lp5RlRbtp4t1X8_7,
  Lp5RlRbtp4t1X8_8,
  Lp5RlRbtp4t1X8_10,
  Lp5RlRbtp4t1X8_11,
  Lp5RlRbtp4t1X8_13,
  Lp5RlRbtp4t1X8_14,
  Lp5RlRbtp4t1X8_16,
  Lp5RlRbtp4t1X8_17,
  Lp5RlRbtp4t1X8_18,
  Lp5RlRbtp4t1X8Max
} LPDDR5_RL_RBTP_4t1_x8;

/**
  This list is for DVFSC disabled, x16
**/
typedef enum {
  Lp5Wr4t1X16_3,
  Lp5Wr4t1X16_5,
  Lp5Wr4t1X16_7,
  Lp5Wr4t1X16_10,
  Lp5Wr4t1X16_12,
  Lp5Wr4t1X16_14,
  Lp5Wr4t1X16_16,
  Lp5Wr4t1X16_19,
  Lp5Wr4t1X16_21,
  Lp5Wr4t1X16_24,
  Lp5Wr4t1X16_26,
  Lp5Wr4t1X16_28,
  Lp5Wr4t1X16Max
} LPDDR5_WR_4t1_x16;

/**
  This list is for DVFSC disabled, x8
**/
typedef enum {
  Lp5Wr4t1X8_3,
  Lp5Wr4t1X8_5,
  Lp5Wr4t1X8_8,
  Lp5Wr4t1X8_10,
  Lp5Wr4t1X8_13,
  Lp5Wr4t1X8_15,
  Lp5Wr4t1X8_17,
  Lp5Wr4t1X8_20,
  Lp5Wr4t1X8_22,
  Lp5Wr4t1X8_25,
  Lp5Wr4t1X8_28,
  Lp5Wr4t1X8_29,
  Lp5Wr4t1X8Max
} LPDDR5_WR_4t1_x8;

/// Structure Definitions
#pragma pack(push, 1)
/// Mode Register 0 is Read Only.
typedef union {
  struct {
    UINT8               : 1;  ///< Bits 0:0
    UINT8 LatencyMode   : 1;  ///< Bits 1:1
    UINT8               : 6;  ///< Bits 2:7
  } Bits;
  UINT8 Data8;
} LPDDR5_MODE_REGISTER_0_TYPE;

typedef union {
  struct {
    UINT8                   : 3;  ///< Bits 0:2
    UINT8 CkMode            : 1;  ///< Bits 3:3
    UINT8 WriteLatency      : 4;  ///< Bits 4:7
  } Bits;
  UINT8 Data8;
} LPDDR5_MODE_REGISTER_1_TYPE;

typedef union {
  struct {
    UINT8 RlAndRbtp       : 4;  ///< Bits 0:3
    UINT8 WriteRecovery   : 4;  ///< Bits 4:7
  } Bits;
  UINT8 Data8;
} LPDDR5_MODE_REGISTER_2_TYPE;

typedef union {
  struct {
    UINT8 PullDnDrvStr    : 3;  ///< Bits 0:2
    UINT8 BankBgOrg       : 2;  ///< Bits 3:4
    UINT8 WriteLatencySet : 1;  ///< Bits 5:5
    UINT8 DbiRdEn         : 1;  ///< Bits 6:6
    UINT8 DbiWrEn         : 1;  ///< Bits 7:7
  } Bits;
  UINT8 Data8;
} LPDDR5_MODE_REGISTER_3_TYPE;

/// Mode Register 4 is Read Only
typedef union {
  struct {
    UINT8 RefreshRate     : 5;  ///< Bits 0:4
    UINT8 ZqUpdateFlag    : 1;  ///< Bits 5:5
    UINT8 ZqMaster        : 1;  ///< Bits 6:6
    UINT8 TempUpdateFlag  : 1;  ///< Bits 7:7
  } Bits;
  UINT8 Data8;
} LPDDR5_MODE_REGISTER_4_TYPE;

/// Mode Register 8 is Read Only
typedef union {
  struct {
    UINT8 Type    : 2;  ///< Bits 0:1
    UINT8 Density : 4;  ///< Bits 2:5
    UINT8 IoWidth : 2;  ///< Bits 6:7
  } Bits;
  UINT8 Data8;
} LPDDR5_MODE_REGISTER_8_TYPE;

typedef union {
  struct {
    UINT8 RdqsPstMode : 1;  ///< Bits 0:0
    UINT8             : 1;  ///< Bits 1:1
    UINT8 WckPstLen   : 2;  ///< Bits 2:3
    UINT8 RdqsPreLen  : 2;  ///< Bits 4:5
    UINT8 RdqsPstLen  : 2;  ///< Bits 6:7
  } Bits;
  UINT8 Data8;
} LPDDR5_MODE_REGISTER_10_TYPE;

typedef union {
  struct {
    UINT8 DqOdt   : 3;  ///< Bits 0:2
    UINT8 NtOdtEn : 1;  ///< Bits 3:3
    UINT8 CaOdt   : 3;  ///< Bits 4:6
    UINT8         : 1;  ///< Bits 7:7
  } Bits;
  UINT8 Data8;
} LPDDR5_MODE_REGISTER_11_TYPE;

/// Mode Register 12 is Read/Write
typedef union {
  struct {
    UINT8 CaVref      : 7;  ///< Bits 0:6
    UINT8 VrefByteSel : 1;  ///< Bits 7:7
  } Bits;
  UINT8 Data8;
} LPDDR5_MODE_REGISTER_12_TYPE;

typedef union {
  struct {
    UINT8 ThermalOffset : 2;  ///< Bits 0:1
    UINT8 VroMode       : 1;  ///< Bits 2:2 - Vref Output Mode
    UINT8               : 2;  ///< Bits 3:4
    UINT8 DmDisable     : 1;  ///< Bits 5:5 - Data Mask Disable
    UINT8 CbtMode       : 1;  ///< Bits 6:6
    UINT8 DualVdd2      : 1;  ///< Bits 7:7
  } Bits;
  UINT8 Data8;
} LPDDR5_MODE_REGISTER_13_TYPE;

/// Mode Register is Read/Write
typedef union {
  struct {
    UINT8 DqVref  : 7;  ///< Bits 0:6
    UINT8 Vdlc    : 1;  ///< Bits 7:7 - Vref DQ Lower Byte Control
  } Bits;
  UINT8 Data8;
} LPDDR5_MODE_REGISTER_14_TYPE;

/// Mode Register is Read/Write
typedef union {
  struct {
    UINT8 DqVref  : 7;  ///< Bits 0:6
    UINT8         : 1;  ///< Bits 7:7
  } Bits;
  UINT8 Data8;
} LPDDR5_MODE_REGISTER_15_TYPE;

/// Mode Register is Read/Write
typedef union {
  struct {
    UINT8 FspWr     : 2;  ///< Bits 0:1
    UINT8 FspOp     : 2;  ///< Bits 2:3
    UINT8 CbtEn     : 2;  ///< Bits 4:5
    UINT8 Vrcg      : 1;  ///< Bits 6:6
    UINT8 CbtPhase  : 1;  ///< Bits 7:7
  } Bits;
  UINT8 Data8;
} LPDDR5_MODE_REGISTER_16_TYPE;

typedef union {
  struct {
    UINT8 SocOdt        : 3;  ///< Bits 0:2
    UINT8 CkOdtEn       : 1;  ///< Bits 3:3
    UINT8               : 1;  ///< Bits 4:4
    UINT8 CaOdtEn       : 1;  ///< Bits 5:5
    UINT8 x8OdtDis7to0  : 1;  ///< Bits 6:6 - x8_2ch Byte mode
    UINT8 x8OdtDis15to8 : 1;  ///< Bits 7:7 - x8_2ch Byte mode
  } Bits;
  UINT8 Data8;
} LPDDR5_MODE_REGISTER_17_TYPE;

typedef union {
  struct {
    UINT8 WckOdt        : 3;  ///< Bits 0:2
    UINT8               : 1;  ///< Bits 3:3
    UINT8 WckAlwaysOn   : 1;  ///< Bits 4:4
    UINT8 WckSync       : 1;  ///< Bits 5:5
    UINT8 Wck2CkLevel   : 1;  ///< Bits 6:6
    UINT8 WckToCkRatio  : 1;  ///< Bits 7:7
  } Bits;
  UINT8 Data8;
} LPDDR5_MODE_REGISTER_18_TYPE;

typedef union {
  struct {
    UINT8 DVFSC : 2;  ///< Bits 0:1 - VDD2 Dynamic Voltage and Frequency Scaling Core
    UINT8 DVFSQ : 2;  ///< Bits 2:3 - VDDQ Dynamic Voltage and Frequency Scaling VDDQ
    UINT8       : 4;  ///< Bits 4:7
  } Bits;
  UINT8 Data8;
} LPDDR5_MODE_REGISTER_19_TYPE;

typedef union {
  struct {
    UINT8 RdqsMode    : 2;  ///< Bits 0:1
    UINT8 WckMode     : 2;  ///< Bits 2:3
    UINT8             : 2;  ///< Bits 4:5
    UINT8 RdcDmiMode  : 1;  ///< Bits 6:6
    UINT8 RdcDqMode   : 1;  ///< Bits 7:7
  } Bits;
  UINT8 Data8;
} LPDDR5_MODE_REGISTER_20_TYPE;

typedef union {
  struct {
    UINT8 Wdcfs : 1;  ///< Bits 0:0 - Read Only
    UINT8 Rdcfs : 1;  ///< Bits 1:1 - Read Only
    UINT8 Wxfs  : 1;  ///< Bits 2:2 - Read Only
    UINT8       : 1;  ///< Bits 3:3
    UINT8 Wdcfe : 1;  ///< Bits 4:4
    UINT8 Rdcfe : 1;  ///< Bits 5:5
    UINT8 Wxfe  : 1;  ///< Bits 6:6
    UINT8       : 1;  ///< Bits 7:7
  } Bits;
  UINT8 Data8;
} LPDDR5_MODE_REGISTER_21_TYPE;

typedef union {
  struct {
    UINT8             : 4;  ///< Bits 0:3
    UINT8 CkPairOdt   : 1;  ///< Bits 4:4
    UINT8 CaInputOdt  : 1;  ///< Bits 5:5
    UINT8 Parc        : 1;  ///< Bits 6:6
    UINT8             : 1;  ///< Bits 7:7
  } Bits;
  UINT8 Data8;
} LPDDR5_MODE_REGISTER_25_TYPE;

typedef union {
  struct {
    UINT8 ZqReset     : 1;  ///< Bits 0:0
    UINT8 ZqStop      : 1;  ///< Bits 1:1
    UINT8 ZqInterval  : 2;  ///< Bits 2:3
    UINT8             : 1;  ///< Bits 4:4
    UINT8 ZqMode      : 1;  ///< Bits 5:5
    UINT8             : 2;  ///< Bits 6:7
  } Bits;
  UINT8 Data8;
} LPDDR5_MODE_REGISTER_28_TYPE;

typedef union {
  struct {
    UINT8 DcaLowByte    : 4;  ///< Bits 0:3
    UINT8 DcaUpperByte  : 4;  ///< Bits 4:7
  } Bits;
  UINT8 Data8;
} LPDDR5_MODE_REGISTER_30_TYPE;

typedef union {
  struct {
    UINT8 Wck2DqiInterval : 8;  ///< Bits 0:7
  } Bits;
  UINT8 Data8;
} LPDDR5_MODE_REGISTER_37_TYPE;

typedef union {
  struct {
    UINT8 Wck2DqoInterval : 8;  ///< Bits 0:7
  } Bits;
  UINT8 Data8;
} LPDDR5_MODE_REGISTER_40_TYPE;

typedef union {
  struct {
    UINT8 PprResBg0 : 1;  ///< Bits 0:0
    UINT8 PprResBg1 : 1;  ///< Bits 1:1
    UINT8 PprResBg2 : 1;  ///< Bits 2:2
    UINT8 PprResBg3 : 1;  ///< Bits 3:3
    UINT8 Ppre      : 1;  ///< Bits 4:4
    UINT8 NtDqOdt   : 3;  ///< Bits 5:7
  } Bits;
  UINT8 Data8;
} LPDDR5_MODE_REGISTER_41_TYPE;

#pragma pack(pop)
#endif // _MRC_LPDDR4_REGISTERS_H_

