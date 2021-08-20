#ifndef __MrcMcRegisterStructIcl6xxx_h__
#define __MrcMcRegisterStructIcl6xxx_h__
/** @file
  This file was automatically generated. Modify at your own risk.
  Note that no error checking is done in these functions so ensure that the correct values are passed.

@copyright
  Copyright (c) 2010 - 2018 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by the
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.
  This file contains an 'Intel Peripheral Driver' and is uniquely
  identified as "Intel Reference Module" and is licensed for Intel
  CPUs and chipsets under the terms of your license agreement with
  Intel or your vendor. This file may be modified by the user, subject
  to additional terms of the license agreement.

@par Specification Reference:
**/

#pragma pack(push, 1)

typedef union {
  struct {
    UINT32                                         :  6;  // Bits 5:0
    UINT32 HASH_MASK                               :  14;  // Bits 19:6
    UINT32                                         :  4;  // Bits 23:20
    UINT32 HASH_LSB_MASK_BIT                       :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 HASH_MODE                               :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CCF_IDP_CHANNEL_HASH_STRUCT;

typedef union {
  struct {
    UINT32                                         :  6;  // Bits 5:0
    UINT32 EHASH_MASK                              :  14;  // Bits 19:6
    UINT32                                         :  4;  // Bits 23:20
    UINT32 EHASH_LSB_MASK_BIT                      :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 EHASH_MODE                              :  1;  // Bits 28:28
    UINT32 MLMC_IS_BA0                             :  1;  // Bits 29:29
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CCF_IDP_CHANNEL_EHASH_STRUCT;

typedef union {
  struct {
    UINT32 DDR_TYPE                                :  3;  // Bits 2:0
    UINT32 ECHM                                    :  1;  // Bits 3:3
    UINT32 CH_L_MAP                                :  1;  // Bits 4:4
    UINT32                                         :  3;  // Bits 7:5
    UINT32 STKD_MODE                               :  1;  // Bits 8:8
    UINT32 STKD_MODE_CH1                           :  1;  // Bits 9:9
    UINT32                                         :  2;  // Bits 11:10
    UINT32 CH_S_SIZE                               :  8;  // Bits 19:12
    UINT32                                         :  4;  // Bits 23:20
    UINT32 STKD_MODE_CH_BITS                       :  3;  // Bits 26:24
    UINT32                                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CCF_IDP_MAD_INTER_CHANNEL_STRUCT;

typedef union {
  struct {
    UINT32 DIMM_L_MAP                              :  1;  // Bits 0:0
    UINT32                                         :  3;  // Bits 3:1
    UINT32 RI                                      :  1;  // Bits 4:4
    UINT32                                         :  3;  // Bits 7:5
    UINT32 EIM                                     :  1;  // Bits 8:8
    UINT32                                         :  3;  // Bits 11:9
    UINT32 ECC                                     :  2;  // Bits 13:12
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CCF_IDP_MAD_INTRA_CH0_STRUCT;

typedef union {
  struct {
    UINT32 DIMM_L_MAP                              :  1;  // Bits 0:0
    UINT32                                         :  3;  // Bits 3:1
    UINT32 RI                                      :  1;  // Bits 4:4
    UINT32                                         :  3;  // Bits 7:5
    UINT32 EIM                                     :  1;  // Bits 8:8
    UINT32                                         :  3;  // Bits 11:9
    UINT32 ECC                                     :  2;  // Bits 13:12
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CCF_IDP_MAD_INTRA_CH1_STRUCT;

typedef union {
  struct {
    UINT32 DIMM_L_SIZE                             :  7;  // Bits 6:0
    UINT32 DLW                                     :  2;  // Bits 8:7
    UINT32 DLNOR                                   :  2;  // Bits 10:9
    UINT32 DL8Gb                                   :  1;  // Bits 11:11
    UINT32                                         :  4;  // Bits 15:12
    UINT32 DIMM_S_SIZE                             :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 DSW                                     :  2;  // Bits 25:24
    UINT32 DSNOR                                   :  2;  // Bits 27:26
    UINT32 DS8Gb                                   :  1;  // Bits 28:28
    UINT32 DLS_BG0_on_bit_11                       :  1;  // Bits 29:29
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CCF_IDP_MAD_DIMM_CH0_STRUCT;

typedef union {
  struct {
    UINT32 DIMM_L_SIZE                             :  7;  // Bits 6:0
    UINT32 DLW                                     :  2;  // Bits 8:7
    UINT32 DLNOR                                   :  2;  // Bits 10:9
    UINT32 DL8Gb                                   :  1;  // Bits 11:11
    UINT32                                         :  4;  // Bits 15:12
    UINT32 DIMM_S_SIZE                             :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 DSW                                     :  2;  // Bits 25:24
    UINT32 DSNOR                                   :  2;  // Bits 27:26
    UINT32 DS8Gb                                   :  1;  // Bits 28:28
    UINT32 DLS_BG0_on_bit_11                       :  1;  // Bits 29:29
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CCF_IDP_MAD_DIMM_CH1_STRUCT;

typedef union {
  struct {
    UINT32 MARS_Enable                             :  1;  // Bits 0:0
    UINT32                                         :  31;  // Bits 31:1
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CCF_IDP_MARS_ENABLE_STRUCT;

typedef union {
  struct {
    UINT32 SAI_MASKLow                             :  32;  // Bits 31:0
    UINT32 SAI_MASKHigh                            :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} TRUSTED_ACCESS_POLICY_CP_STRUCT;

typedef union {
  struct {
    UINT32 SAI_MASKLow                             :  32;  // Bits 31:0
    UINT32 SAI_MASKHigh                            :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} TRUSTED_ACCESS_POLICY_WAC_STRUCT;

typedef union {
  struct {
    UINT32 SAI_MASKLow                             :  32;  // Bits 31:0
    UINT32 SAI_MASKHigh                            :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} TRUSTED_ACCESS_POLICY_RAC_STRUCT;

typedef union {
  struct {
    UINT32 NON_VC1_PRIO_THRESHOLD                  :  16;  // Bits 15:0
    UINT32 VC1_RD_PRIO_THRESHOLD                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PRIO_THRESHOLD_STRUCT;

typedef union {
  struct {
    UINT32 LOW_PRIORITY_LIM                        :  16;  // Bits 15:0
    UINT32 HIGH_PRIORITY_LIM                       :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PRIO_LIM_STRUCT;

typedef union {
  struct {
    UINT32 CREDITS_CONFIG_DONE                     :  1;  // Bits 0:0
    UINT32 RESERVED_0                              :  31;  // Bits 31:1
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMF_GLOBAL_CFG_STRUCT;

typedef union {
  struct {
    UINT32 CMD_CLEAR                               :  1;  // Bits 0:0
    UINT32 CMD_ENABLE                              :  1;  // Bits 1:1
    UINT32 CMD_FUNC_OV                             :  1;  // Bits 2:2
    UINT32 RESERVED                                :  29;  // Bits 31:3
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMF_ACCUM_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMF_RSVD0_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMF_RSVD1_STRUCT;

typedef union {
  struct {
    UINT32 CGCTRL_CLKGATEDEF                       :  1;  // Bits 0:0
    UINT32 RSVD0                                   :  7;  // Bits 7:1
    UINT32 CGCTRL_CLKGATEN                         :  1;  // Bits 8:8
    UINT32 RSVD1                                   :  7;  // Bits 15:9
    UINT32 CGCTRL_IDLECNT                          :  8;  // Bits 23:16
    UINT32 RSVD2                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_IOSF_SB_EP_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 CLK_GATE_EN                             :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CLK_GATE_EN_0_STRUCT;

typedef union {
  struct {
    UINT32 CLK_GATE_EN                             :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CLK_GATE_EN_1_STRUCT;

typedef union {
  struct {
    UINT32 MUX_DEMUX_STS                           :  1;  // Bits 0:0
    UINT32 RESERVED                                :  31;  // Bits 31:1
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMF_GLOBAL_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 ISM_IDLE_TIME                           :  8;  // Bits 7:0
    UINT32 FIXED_WINDOW                            :  1;  // Bits 8:8
    UINT32 CLK_GATE_EN                             :  1;  // Bits 9:9
    UINT32 FORCE_ISM_ACTIVE                        :  1;  // Bits 10:10
    UINT32 BYPASS_EN                               :  1;  // Bits 11:11
    UINT32 AGENT_WR_RSP                            :  5;  // Bits 16:12
    UINT32 REQ_FAST_WAKE                           :  5;  // Bits 21:17
    UINT32 FAST_WAKE_EN                            :  1;  // Bits 22:22
    UINT32 RESERVED                                :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMF_GLOBAL_CFG_1_STRUCT;

typedef union {
  struct {
    UINT32 REQ_WR_PARK_SIZE                        :  4;  // Bits 3:0
    UINT32 VC1WR_WINDOW                            :  3;  // Bits 6:4
    UINT32 VC1WR_WINDOW_FIX_DISABLE                :  1;  // Bits 7:7
    UINT32 REQ_RD_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 REQ_WR_MAX_CREDIT                       :  8;  // Bits 23:16
    UINT32 REQ_RD_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_STRUCT;

typedef union {
  struct {
    UINT32 REQ_WR_PARK_SIZE                        :  4;  // Bits 3:0
    UINT32 VC1WR_WINDOW                            :  3;  // Bits 6:4
    UINT32 VC1WR_WINDOW_FIX_DISABLE                :  1;  // Bits 7:7
    UINT32 REQ_RD_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 REQ_WR_MAX_CREDIT                       :  8;  // Bits 23:16
    UINT32 REQ_RD_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_STRUCT;

typedef union {
  struct {
    UINT32 REQ_WR_PARK_SIZE                        :  4;  // Bits 3:0
    UINT32 VC1WR_WINDOW                            :  3;  // Bits 6:4
    UINT32 VC1WR_WINDOW_FIX_DISABLE                :  1;  // Bits 7:7
    UINT32 REQ_RD_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 REQ_WR_MAX_CREDIT                       :  8;  // Bits 23:16
    UINT32 REQ_RD_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_STRUCT;

typedef union {
  struct {
    UINT32 REQ_WR_PARK_SIZE                        :  4;  // Bits 3:0
    UINT32 VC1WR_WINDOW                            :  3;  // Bits 6:4
    UINT32 VC1WR_WINDOW_FIX_DISABLE                :  1;  // Bits 7:7
    UINT32 REQ_RD_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 REQ_WR_MAX_CREDIT                       :  8;  // Bits 23:16
    UINT32 REQ_RD_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_STRUCT;

typedef union {
  struct {
    UINT32 REQ_WR_QUEUEDEPTH                       :  8;  // Bits 7:0
    UINT32 REQ_RD_QUEUEDEPTH                       :  8;  // Bits 15:8
    UINT32 RESERVED1                               :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_0_REQ_CONFIG_1_STRUCT;

typedef union {
  struct {
    UINT32 REQ_STALL                               :  1;  // Bits 0:0
    UINT32 RSVD0                                   :  4;  // Bits 4:1
    UINT32 RSVD1                                   :  3;  // Bits 7:5
    UINT32 UNSTALL_COUNTER_VALUE                   :  16;  // Bits 23:8
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_0_STALL_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_0_RESERVED_0_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_0_RESERVED_1_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_0_RESERVED_2_STRUCT;

typedef union {
  struct {
    UINT32 REQ_CMD_SUM                             :  16;  // Bits 15:0
    UINT32 REQ_DATA_SUM                            :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_0_ACCUM_REQ_IN_STRUCT;

typedef union {
  struct {
    UINT32 RD_CPL_CMD_SUM                          :  16;  // Bits 15:0
    UINT32 RD_CPL_DATA_SUM                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_0_ACCUM_RD_CPL_OUT_STRUCT;

typedef union {
  struct {
    UINT32 RSP_CMD_SUM                             :  16;  // Bits 15:0
    UINT32 RSVD                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_0_ACCUM_RSP_OUT_STRUCT;

typedef union {
  struct {
    UINT32 REQ_WR_PARK_SIZE                        :  4;  // Bits 3:0
    UINT32 VC1WR_WINDOW                            :  3;  // Bits 6:4
    UINT32 VC1WR_WINDOW_FIX_DISABLE                :  1;  // Bits 7:7
    UINT32 REQ_RD_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 REQ_WR_MAX_CREDIT                       :  8;  // Bits 23:16
    UINT32 REQ_RD_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_STRUCT;

typedef union {
  struct {
    UINT32 REQ_WR_PARK_SIZE                        :  4;  // Bits 3:0
    UINT32 VC1WR_WINDOW                            :  3;  // Bits 6:4
    UINT32 VC1WR_WINDOW_FIX_DISABLE                :  1;  // Bits 7:7
    UINT32 REQ_RD_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 REQ_WR_MAX_CREDIT                       :  8;  // Bits 23:16
    UINT32 REQ_RD_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_STRUCT;

typedef union {
  struct {
    UINT32 REQ_WR_PARK_SIZE                        :  4;  // Bits 3:0
    UINT32 VC1WR_WINDOW                            :  3;  // Bits 6:4
    UINT32 VC1WR_WINDOW_FIX_DISABLE                :  1;  // Bits 7:7
    UINT32 REQ_RD_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 REQ_WR_MAX_CREDIT                       :  8;  // Bits 23:16
    UINT32 REQ_RD_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_STRUCT;

typedef union {
  struct {
    UINT32 REQ_WR_PARK_SIZE                        :  4;  // Bits 3:0
    UINT32 VC1WR_WINDOW                            :  3;  // Bits 6:4
    UINT32 VC1WR_WINDOW_FIX_DISABLE                :  1;  // Bits 7:7
    UINT32 REQ_RD_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 REQ_WR_MAX_CREDIT                       :  8;  // Bits 23:16
    UINT32 REQ_RD_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_STRUCT;

typedef union {
  struct {
    UINT32 REQ_WR_QUEUEDEPTH                       :  8;  // Bits 7:0
    UINT32 REQ_RD_QUEUEDEPTH                       :  8;  // Bits 15:8
    UINT32 RESERVED1                               :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_1_REQ_CONFIG_1_STRUCT;

typedef union {
  struct {
    UINT32 REQ_STALL                               :  1;  // Bits 0:0
    UINT32 RSVD0                                   :  4;  // Bits 4:1
    UINT32 RSVD1                                   :  3;  // Bits 7:5
    UINT32 UNSTALL_COUNTER_VALUE                   :  16;  // Bits 23:8
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_1_STALL_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_1_RESERVED_0_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_1_RESERVED_1_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_1_RESERVED_2_STRUCT;

typedef union {
  struct {
    UINT32 REQ_CMD_SUM                             :  16;  // Bits 15:0
    UINT32 REQ_DATA_SUM                            :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_1_ACCUM_REQ_IN_STRUCT;

typedef union {
  struct {
    UINT32 RD_CPL_CMD_SUM                          :  16;  // Bits 15:0
    UINT32 RD_CPL_DATA_SUM                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_1_ACCUM_RD_CPL_OUT_STRUCT;

typedef union {
  struct {
    UINT32 RSP_CMD_SUM                             :  16;  // Bits 15:0
    UINT32 RSVD                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_1_ACCUM_RSP_OUT_STRUCT;

typedef union {
  struct {
    UINT32 REQ_WR_PARK_SIZE                        :  4;  // Bits 3:0
    UINT32 VC1WR_WINDOW                            :  3;  // Bits 6:4
    UINT32 VC1WR_WINDOW_FIX_DISABLE                :  1;  // Bits 7:7
    UINT32 REQ_RD_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 REQ_WR_MAX_CREDIT                       :  8;  // Bits 23:16
    UINT32 REQ_RD_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_STRUCT;

typedef union {
  struct {
    UINT32 REQ_WR_PARK_SIZE                        :  4;  // Bits 3:0
    UINT32 VC1WR_WINDOW                            :  3;  // Bits 6:4
    UINT32 VC1WR_WINDOW_FIX_DISABLE                :  1;  // Bits 7:7
    UINT32 REQ_RD_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 REQ_WR_MAX_CREDIT                       :  8;  // Bits 23:16
    UINT32 REQ_RD_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_STRUCT;

typedef union {
  struct {
    UINT32 REQ_WR_PARK_SIZE                        :  4;  // Bits 3:0
    UINT32 VC1WR_WINDOW                            :  3;  // Bits 6:4
    UINT32 VC1WR_WINDOW_FIX_DISABLE                :  1;  // Bits 7:7
    UINT32 REQ_RD_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 REQ_WR_MAX_CREDIT                       :  8;  // Bits 23:16
    UINT32 REQ_RD_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_STRUCT;

typedef union {
  struct {
    UINT32 REQ_WR_PARK_SIZE                        :  4;  // Bits 3:0
    UINT32 VC1WR_WINDOW                            :  3;  // Bits 6:4
    UINT32 VC1WR_WINDOW_FIX_DISABLE                :  1;  // Bits 7:7
    UINT32 REQ_RD_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 REQ_WR_MAX_CREDIT                       :  8;  // Bits 23:16
    UINT32 REQ_RD_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_STRUCT;

typedef union {
  struct {
    UINT32 REQ_WR_QUEUEDEPTH                       :  8;  // Bits 7:0
    UINT32 REQ_RD_QUEUEDEPTH                       :  8;  // Bits 15:8
    UINT32 RESERVED1                               :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_2_REQ_CONFIG_1_STRUCT;

typedef union {
  struct {
    UINT32 REQ_STALL                               :  1;  // Bits 0:0
    UINT32 RSVD0                                   :  4;  // Bits 4:1
    UINT32 RSVD1                                   :  3;  // Bits 7:5
    UINT32 UNSTALL_COUNTER_VALUE                   :  16;  // Bits 23:8
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_2_STALL_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_2_RESERVED_0_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_2_RESERVED_1_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_2_RESERVED_2_STRUCT;

typedef union {
  struct {
    UINT32 REQ_CMD_SUM                             :  16;  // Bits 15:0
    UINT32 REQ_DATA_SUM                            :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_2_ACCUM_REQ_IN_STRUCT;

typedef union {
  struct {
    UINT32 RD_CPL_CMD_SUM                          :  16;  // Bits 15:0
    UINT32 RD_CPL_DATA_SUM                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_2_ACCUM_RD_CPL_OUT_STRUCT;

typedef union {
  struct {
    UINT32 RSP_CMD_SUM                             :  16;  // Bits 15:0
    UINT32 RSVD                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_2_ACCUM_RSP_OUT_STRUCT;

typedef union {
  struct {
    UINT32 REQ_WR_PARK_SIZE                        :  4;  // Bits 3:0
    UINT32 VC1WR_WINDOW                            :  3;  // Bits 6:4
    UINT32 VC1WR_WINDOW_FIX_DISABLE                :  1;  // Bits 7:7
    UINT32 REQ_RD_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 REQ_WR_MAX_CREDIT                       :  8;  // Bits 23:16
    UINT32 REQ_RD_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_STRUCT;

typedef union {
  struct {
    UINT32 REQ_WR_PARK_SIZE                        :  4;  // Bits 3:0
    UINT32 VC1WR_WINDOW                            :  3;  // Bits 6:4
    UINT32 VC1WR_WINDOW_FIX_DISABLE                :  1;  // Bits 7:7
    UINT32 REQ_RD_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 REQ_WR_MAX_CREDIT                       :  8;  // Bits 23:16
    UINT32 REQ_RD_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_STRUCT;

typedef union {
  struct {
    UINT32 REQ_WR_PARK_SIZE                        :  4;  // Bits 3:0
    UINT32 VC1WR_WINDOW                            :  3;  // Bits 6:4
    UINT32 VC1WR_WINDOW_FIX_DISABLE                :  1;  // Bits 7:7
    UINT32 REQ_RD_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 REQ_WR_MAX_CREDIT                       :  8;  // Bits 23:16
    UINT32 REQ_RD_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_STRUCT;

typedef union {
  struct {
    UINT32 REQ_WR_PARK_SIZE                        :  4;  // Bits 3:0
    UINT32 VC1WR_WINDOW                            :  3;  // Bits 6:4
    UINT32 VC1WR_WINDOW_FIX_DISABLE                :  1;  // Bits 7:7
    UINT32 REQ_RD_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 REQ_WR_MAX_CREDIT                       :  8;  // Bits 23:16
    UINT32 REQ_RD_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_STRUCT;

typedef union {
  struct {
    UINT32 REQ_WR_QUEUEDEPTH                       :  8;  // Bits 7:0
    UINT32 REQ_RD_QUEUEDEPTH                       :  8;  // Bits 15:8
    UINT32 RESERVED1                               :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_3_REQ_CONFIG_1_STRUCT;

typedef union {
  struct {
    UINT32 REQ_STALL                               :  1;  // Bits 0:0
    UINT32 RSVD0                                   :  4;  // Bits 4:1
    UINT32 RSVD1                                   :  3;  // Bits 7:5
    UINT32 UNSTALL_COUNTER_VALUE                   :  16;  // Bits 23:8
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_3_STALL_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_3_RESERVED_0_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_3_RESERVED_1_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_3_RESERVED_2_STRUCT;

typedef union {
  struct {
    UINT32 REQ_CMD_SUM                             :  16;  // Bits 15:0
    UINT32 REQ_DATA_SUM                            :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_3_ACCUM_REQ_IN_STRUCT;

typedef union {
  struct {
    UINT32 RD_CPL_CMD_SUM                          :  16;  // Bits 15:0
    UINT32 RD_CPL_DATA_SUM                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_3_ACCUM_RD_CPL_OUT_STRUCT;

typedef union {
  struct {
    UINT32 RSP_CMD_SUM                             :  16;  // Bits 15:0
    UINT32 RSVD                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} REQUEST_PORT_3_ACCUM_RSP_OUT_STRUCT;

typedef union {
  struct {
    UINT32 RSP_PARK_SIZE                           :  4;  // Bits 3:0
    UINT32 RESERVED0                               :  4;  // Bits 7:4
    UINT32 RD_CPL_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 RSP_MAX_CREDIT                          :  8;  // Bits 23:16
    UINT32 RD_CPL_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT;

typedef union {
  struct {
    UINT32 RSP_PARK_SIZE                           :  4;  // Bits 3:0
    UINT32 RESERVED0                               :  4;  // Bits 7:4
    UINT32 RD_CPL_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 RSP_MAX_CREDIT                          :  8;  // Bits 23:16
    UINT32 RD_CPL_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_STRUCT;

typedef union {
  struct {
    UINT32 RSP_PARK_SIZE                           :  4;  // Bits 3:0
    UINT32 RESERVED0                               :  4;  // Bits 7:4
    UINT32 RD_CPL_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 RSP_MAX_CREDIT                          :  8;  // Bits 23:16
    UINT32 RD_CPL_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_STRUCT;

typedef union {
  struct {
    UINT32 RSP_PARK_SIZE                           :  4;  // Bits 3:0
    UINT32 RESERVED0                               :  4;  // Bits 7:4
    UINT32 RD_CPL_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 RSP_MAX_CREDIT                          :  8;  // Bits 23:16
    UINT32 RD_CPL_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_STRUCT;

typedef union {
  struct {
    UINT32 RD_CPL_QUEUEDEPTH                       :  8;  // Bits 7:0
    UINT32 RSP_QUEUEDEPTH                          :  8;  // Bits 15:8
    UINT32 RESERVED1                               :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_0_CPL_CONFIG_1_STRUCT;

typedef union {
  struct {
    UINT32 RSVD0                                   :  4;  // Bits 3:0
    UINT32 RSP_RD_CPL_STALL                        :  1;  // Bits 4:4
    UINT32 RSVD1                                   :  3;  // Bits 7:5
    UINT32 UNSTALL_COUNTER_VALUE                   :  16;  // Bits 23:8
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_0_STALL_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_0_RESERVED_0_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_0_RESERVED_1_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_0_RESERVED_2_STRUCT;

typedef union {
  struct {
    UINT32 REQ_CMD_SUM                             :  16;  // Bits 15:0
    UINT32 REQ_DATA_SUM                            :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_0_ACCUM_REQ_OUT_STRUCT;

typedef union {
  struct {
    UINT32 RD_CPL_CMD_SUM                          :  16;  // Bits 15:0
    UINT32 RD_CPL_DATA_SUM                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_0_ACCUM_RD_CPL_IN_STRUCT;

typedef union {
  struct {
    UINT32 RSP_CMD_SUM                             :  16;  // Bits 15:0
    UINT32 RSVD                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_0_ACCUM_RSP_IN_STRUCT;

typedef union {
  struct {
    UINT32 RSP_PARK_SIZE                           :  4;  // Bits 3:0
    UINT32 RESERVED0                               :  4;  // Bits 7:4
    UINT32 RD_CPL_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 RSP_MAX_CREDIT                          :  8;  // Bits 23:16
    UINT32 RD_CPL_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_STRUCT;

typedef union {
  struct {
    UINT32 RSP_PARK_SIZE                           :  4;  // Bits 3:0
    UINT32 RESERVED0                               :  4;  // Bits 7:4
    UINT32 RD_CPL_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 RSP_MAX_CREDIT                          :  8;  // Bits 23:16
    UINT32 RD_CPL_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_STRUCT;

typedef union {
  struct {
    UINT32 RSP_PARK_SIZE                           :  4;  // Bits 3:0
    UINT32 RESERVED0                               :  4;  // Bits 7:4
    UINT32 RD_CPL_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 RSP_MAX_CREDIT                          :  8;  // Bits 23:16
    UINT32 RD_CPL_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_STRUCT;

typedef union {
  struct {
    UINT32 RSP_PARK_SIZE                           :  4;  // Bits 3:0
    UINT32 RESERVED0                               :  4;  // Bits 7:4
    UINT32 RD_CPL_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 RSP_MAX_CREDIT                          :  8;  // Bits 23:16
    UINT32 RD_CPL_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_STRUCT;

typedef union {
  struct {
    UINT32 RD_CPL_QUEUEDEPTH                       :  8;  // Bits 7:0
    UINT32 RSP_QUEUEDEPTH                          :  8;  // Bits 15:8
    UINT32 RESERVED1                               :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_1_CPL_CONFIG_1_STRUCT;

typedef union {
  struct {
    UINT32 RSVD0                                   :  4;  // Bits 3:0
    UINT32 RSP_RD_CPL_STALL                        :  1;  // Bits 4:4
    UINT32 RSVD1                                   :  3;  // Bits 7:5
    UINT32 UNSTALL_COUNTER_VALUE                   :  16;  // Bits 23:8
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_1_STALL_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_1_RESERVED_0_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_1_RESERVED_1_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_1_RESERVED_2_STRUCT;

typedef union {
  struct {
    UINT32 REQ_CMD_SUM                             :  16;  // Bits 15:0
    UINT32 REQ_DATA_SUM                            :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_1_ACCUM_REQ_OUT_STRUCT;

typedef union {
  struct {
    UINT32 RD_CPL_CMD_SUM                          :  16;  // Bits 15:0
    UINT32 RD_CPL_DATA_SUM                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_1_ACCUM_RD_CPL_IN_STRUCT;

typedef union {
  struct {
    UINT32 RSP_CMD_SUM                             :  16;  // Bits 15:0
    UINT32 RSVD                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_1_ACCUM_RSP_IN_STRUCT;

typedef union {
  struct {
    UINT32 RSP_PARK_SIZE                           :  4;  // Bits 3:0
    UINT32 RESERVED0                               :  4;  // Bits 7:4
    UINT32 RD_CPL_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 RSP_MAX_CREDIT                          :  8;  // Bits 23:16
    UINT32 RD_CPL_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_STRUCT;

typedef union {
  struct {
    UINT32 RSP_PARK_SIZE                           :  4;  // Bits 3:0
    UINT32 RESERVED0                               :  4;  // Bits 7:4
    UINT32 RD_CPL_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 RSP_MAX_CREDIT                          :  8;  // Bits 23:16
    UINT32 RD_CPL_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_STRUCT;

typedef union {
  struct {
    UINT32 RSP_PARK_SIZE                           :  4;  // Bits 3:0
    UINT32 RESERVED0                               :  4;  // Bits 7:4
    UINT32 RD_CPL_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 RSP_MAX_CREDIT                          :  8;  // Bits 23:16
    UINT32 RD_CPL_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_STRUCT;

typedef union {
  struct {
    UINT32 RSP_PARK_SIZE                           :  4;  // Bits 3:0
    UINT32 RESERVED0                               :  4;  // Bits 7:4
    UINT32 RD_CPL_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 RSP_MAX_CREDIT                          :  8;  // Bits 23:16
    UINT32 RD_CPL_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_STRUCT;

typedef union {
  struct {
    UINT32 RD_CPL_QUEUEDEPTH                       :  8;  // Bits 7:0
    UINT32 RSP_QUEUEDEPTH                          :  8;  // Bits 15:8
    UINT32 RESERVED1                               :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_2_CPL_CONFIG_1_STRUCT;

typedef union {
  struct {
    UINT32 RSVD0                                   :  4;  // Bits 3:0
    UINT32 RSP_RD_CPL_STALL                        :  1;  // Bits 4:4
    UINT32 RSVD1                                   :  3;  // Bits 7:5
    UINT32 UNSTALL_COUNTER_VALUE                   :  16;  // Bits 23:8
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_2_STALL_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_2_RESERVED_0_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_2_RESERVED_1_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_2_RESERVED_2_STRUCT;

typedef union {
  struct {
    UINT32 REQ_CMD_SUM                             :  16;  // Bits 15:0
    UINT32 REQ_DATA_SUM                            :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_2_ACCUM_REQ_OUT_STRUCT;

typedef union {
  struct {
    UINT32 RD_CPL_CMD_SUM                          :  16;  // Bits 15:0
    UINT32 RD_CPL_DATA_SUM                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_2_ACCUM_RD_CPL_IN_STRUCT;

typedef union {
  struct {
    UINT32 RSP_CMD_SUM                             :  16;  // Bits 15:0
    UINT32 RSVD                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_2_ACCUM_RSP_IN_STRUCT;

typedef union {
  struct {
    UINT32 RSP_PARK_SIZE                           :  4;  // Bits 3:0
    UINT32 RESERVED0                               :  4;  // Bits 7:4
    UINT32 RD_CPL_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 RSP_MAX_CREDIT                          :  8;  // Bits 23:16
    UINT32 RD_CPL_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_STRUCT;

typedef union {
  struct {
    UINT32 RSP_PARK_SIZE                           :  4;  // Bits 3:0
    UINT32 RESERVED0                               :  4;  // Bits 7:4
    UINT32 RD_CPL_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 RSP_MAX_CREDIT                          :  8;  // Bits 23:16
    UINT32 RD_CPL_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_STRUCT;

typedef union {
  struct {
    UINT32 RSP_PARK_SIZE                           :  4;  // Bits 3:0
    UINT32 RESERVED0                               :  4;  // Bits 7:4
    UINT32 RD_CPL_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 RSP_MAX_CREDIT                          :  8;  // Bits 23:16
    UINT32 RD_CPL_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_STRUCT;

typedef union {
  struct {
    UINT32 RSP_PARK_SIZE                           :  4;  // Bits 3:0
    UINT32 RESERVED0                               :  4;  // Bits 7:4
    UINT32 RD_CPL_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 RSP_MAX_CREDIT                          :  8;  // Bits 23:16
    UINT32 RD_CPL_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_STRUCT;

typedef union {
  struct {
    UINT32 RD_CPL_QUEUEDEPTH                       :  8;  // Bits 7:0
    UINT32 RSP_QUEUEDEPTH                          :  8;  // Bits 15:8
    UINT32 RESERVED1                               :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_3_CPL_CONFIG_1_STRUCT;

typedef union {
  struct {
    UINT32 RSVD0                                   :  4;  // Bits 3:0
    UINT32 RSP_RD_CPL_STALL                        :  1;  // Bits 4:4
    UINT32 RSVD1                                   :  3;  // Bits 7:5
    UINT32 UNSTALL_COUNTER_VALUE                   :  16;  // Bits 23:8
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_3_STALL_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_3_RESERVED_0_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_3_RESERVED_1_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_3_RESERVED_2_STRUCT;

typedef union {
  struct {
    UINT32 REQ_CMD_SUM                             :  16;  // Bits 15:0
    UINT32 REQ_DATA_SUM                            :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_3_ACCUM_REQ_OUT_STRUCT;

typedef union {
  struct {
    UINT32 RD_CPL_CMD_SUM                          :  16;  // Bits 15:0
    UINT32 RD_CPL_DATA_SUM                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_3_ACCUM_RD_CPL_IN_STRUCT;

typedef union {
  struct {
    UINT32 RSP_CMD_SUM                             :  16;  // Bits 15:0
    UINT32 RSVD                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RESPOND_PORT_3_ACCUM_RSP_IN_STRUCT;

typedef union {
  struct {
    UINT32 lock                                    :  1;  // Bits 0:0
    UINT32                                         :  9;  // Bits 9:1
    UINT32 imriaexcbaseLow                         :  22;  // Bits 31:10
    UINT32 imriaexcbaseHigh                        :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IMRIAEXCBASE_MCHBAR_CBO_INGRESS_STRUCT;

typedef union {
  struct {
    UINT32 lock                                    :  1;  // Bits 0:0
    UINT32                                         :  9;  // Bits 9:1
    UINT32 imriaexclimitLow                        :  22;  // Bits 31:10
    UINT32 imriaexclimitHigh                       :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IMRIAEXCLIMIT_MCHBAR_CBO_INGRESS_STRUCT;

typedef union {
  struct {
    UINT32 lock                                    :  1;  // Bits 0:0
    UINT32                                         :  9;  // Bits 9:1
    UINT32 imrgtexcbaseLow                         :  22;  // Bits 31:10
    UINT32 imrgtexcbaseHigh                        :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IMRGTEXCBASE_MCHBAR_CBO_INGRESS_STRUCT;

typedef union {
  struct {
    UINT32 lock                                    :  1;  // Bits 0:0
    UINT32                                         :  9;  // Bits 9:1
    UINT32 imrgtexclimitLow                        :  22;  // Bits 31:10
    UINT32 imrgtexclimitHigh                       :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IMRGTEXCLIMIT_MCHBAR_CBO_INGRESS_STRUCT;

#pragma pack(pop)
#endif
