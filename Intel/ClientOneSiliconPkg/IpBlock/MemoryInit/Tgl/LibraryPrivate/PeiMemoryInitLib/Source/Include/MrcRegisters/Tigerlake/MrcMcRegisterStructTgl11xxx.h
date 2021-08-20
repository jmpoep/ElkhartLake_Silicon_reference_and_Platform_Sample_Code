#ifndef __MrcMcRegisterStructTgl11xxx_h__
#define __MrcMcRegisterStructTgl11xxx_h__
/** @file
  This file was automatically generated. Modify at your own risk.
  Note that no error checking is done in these functions so ensure that the correct values are passed.

@copyright
  Copyright (c) 2010 - 2019 Intel Corporation. All rights reserved
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
    UINT32 SAI_MASKLow                             :  32;  // Bits 31:0
    UINT32 SAI_MASKHigh                            :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CMF_LT_SA_W_PG_ACCESS_POLICY_CP_STRUCT;
typedef union {
  struct {
    UINT32 SAI_MASKLow                             :  32;  // Bits 31:0
    UINT32 SAI_MASKHigh                            :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CMF_LT_SA_W_PG_ACCESS_POLICY_WAC_STRUCT;
typedef union {
  struct {
    UINT32 SAI_MASKLow                             :  32;  // Bits 31:0
    UINT32 SAI_MASKHigh                            :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CMF_LT_SA_W_PG_ACCESS_POLICY_RAC_STRUCT;
typedef union {
  struct {
    UINT32 NON_VC1_PRIO_THRESHOLD                  :  16;  // Bits 15:0
    UINT32 VC1_RD_PRIO_THRESHOLD                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_PRIO_THRESHOLD_STRUCT;
typedef union {
  struct {
    UINT32 LOW_PRIORITY_LIM                        :  16;  // Bits 15:0
    UINT32 HIGH_PRIORITY_LIM                       :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_PRIO_LIM_STRUCT;
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
    UINT32 ISM_IDLE_TIME                           :  8;  // Bits 7:0
    UINT32 FIXED_WINDOW                            :  1;  // Bits 8:8
    UINT32 CLK_GATE_EN                             :  1;  // Bits 9:9
    UINT32 FORCE_ISM_ACTIVE                        :  1;  // Bits 10:10
    UINT32 BYPASS_EN                               :  1;  // Bits 11:11
    UINT32 DIS_PERF_COUNTERS                       :  1;  // Bits 12:12
    UINT32 DIS_GLBDRV_GATING                       :  1;  // Bits 13:13
    UINT32 DIS_RSP_PORT_PRE_VALID                  :  1;  // Bits 14:14
    UINT32 DIS_RSP_PORT_BYPASS_PRE_VALID           :  1;  // Bits 15:15
    UINT32 RESERVED                                :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMF_GLOBAL_CFG_1_STRUCT;
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
} CMI_CLK_GATE_EN_0_STRUCT;

typedef CMI_CLK_GATE_EN_0_STRUCT CMI_CLK_GATE_EN_1_STRUCT;
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

typedef CMF_LT_SA_W_PG_ACCESS_POLICY_CP_STRUCT CMF_P_U_CODE_PG_ACCESS_POLICY_CP_STRUCT;
typedef union {
  struct {
    UINT32 SAI_MASKLow                             :  32;  // Bits 31:0
    UINT32 SAI_MASKHigh                            :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CMF_P_U_CODE_PG_ACCESS_POLICY_WAC_STRUCT;

typedef CMF_P_U_CODE_PG_ACCESS_POLICY_WAC_STRUCT CMF_P_U_CODE_PG_ACCESS_POLICY_RAC_STRUCT;
typedef union {
  struct {
    UINT32 SEL_2LM_1LM                             :  1;  // Bits 0:0
    UINT32 SEL_TME_ON                              :  1;  // Bits 1:1
    UINT32 SEL_IBECC_ON                            :  1;  // Bits 2:2
    UINT32 Reserved_0                              :  5;  // Bits 7:3
    UINT32 SLICE_0_DISABLE                         :  1;  // Bits 8:8
    UINT32 SLICE_1_DISABLE                         :  1;  // Bits 9:9
    UINT32 Reserved_1                              :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMF_TOPOLOGY_GLOBAL_CFG_0_STRUCT;
typedef union {
  struct {
    UINT32 Reserved_0                              :  10;  // Bits 9:0
    UINT32 AGENT_WR_RSP                            :  5;  // Bits 14:10
    UINT32 Reserved_1                              :  3;  // Bits 17:15
    UINT32 CPL_MUX_DEMUX_3_CFG                     :  1;  // Bits 18:18
    UINT32 CPL_MUX_DEMUX_2_CFG                     :  2;  // Bits 20:19
    UINT32 REQ_MUX_DEMUX_1_CFG                     :  2;  // Bits 22:21
    UINT32 REQ_MUX_DEMUX_0_CFG                     :  1;  // Bits 23:23
    UINT32 Reserved_2                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMF_TOPOLOGY_GLOBAL_CFG_1_STRUCT;
typedef union {
  struct {
    UINT32 Reserved_0                              :  10;  // Bits 9:0
    UINT32 AGENT_WR_RSP                            :  5;  // Bits 14:10
    UINT32 Reserved_1                              :  3;  // Bits 17:15
    UINT32 CPL_MUX_DEMUX_3_CFG                     :  1;  // Bits 18:18
    UINT32 CPL_MUX_DEMUX_2_CFG                     :  2;  // Bits 20:19
    UINT32 REQ_MUX_DEMUX_1_CFG                     :  2;  // Bits 22:21
    UINT32 REQ_MUX_DEMUX_0_CFG                     :  1;  // Bits 23:23
    UINT32 Reserved_2                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMF_TOPOLOGY_GLOBAL_CFG_2_STRUCT;
typedef union {
  struct {
    UINT32 Reserved_0                              :  10;  // Bits 9:0
    UINT32 AGENT_WR_RSP                            :  5;  // Bits 14:10
    UINT32 Reserved_1                              :  3;  // Bits 17:15
    UINT32 CPL_MUX_DEMUX_3_CFG                     :  1;  // Bits 18:18
    UINT32 CPL_MUX_DEMUX_2_CFG                     :  2;  // Bits 20:19
    UINT32 REQ_MUX_DEMUX_1_CFG                     :  2;  // Bits 22:21
    UINT32 REQ_MUX_DEMUX_0_CFG                     :  1;  // Bits 23:23
    UINT32 Reserved_2                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMF_TOPOLOGY_GLOBAL_CFG_3_STRUCT;
typedef union {
  struct {
    UINT32 Reserved_0                              :  10;  // Bits 9:0
    UINT32 AGENT_WR_RSP                            :  5;  // Bits 14:10
    UINT32 Reserved_1                              :  3;  // Bits 17:15
    UINT32 CPL_MUX_DEMUX_3_CFG                     :  1;  // Bits 18:18
    UINT32 CPL_MUX_DEMUX_2_CFG                     :  2;  // Bits 20:19
    UINT32 REQ_MUX_DEMUX_1_CFG                     :  2;  // Bits 22:21
    UINT32 REQ_MUX_DEMUX_0_CFG                     :  1;  // Bits 23:23
    UINT32 Reserved_2                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMF_TOPOLOGY_GLOBAL_CFG_4_STRUCT;
typedef union {
  struct {
    UINT32 Reserved_0                              :  10;  // Bits 9:0
    UINT32 AGENT_WR_RSP                            :  5;  // Bits 14:10
    UINT32 Reserved_1                              :  3;  // Bits 17:15
    UINT32 CPL_MUX_DEMUX_3_CFG                     :  1;  // Bits 18:18
    UINT32 CPL_MUX_DEMUX_2_CFG                     :  2;  // Bits 20:19
    UINT32 REQ_MUX_DEMUX_1_CFG                     :  2;  // Bits 22:21
    UINT32 REQ_MUX_DEMUX_0_CFG                     :  1;  // Bits 23:23
    UINT32 Reserved_2                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMF_TOPOLOGY_GLOBAL_CFG_5_STRUCT;
typedef union {
  struct {
    UINT32 Reserved_0                              :  4;  // Bits 3:0
    UINT32 MS_L_MAP                                :  1;  // Bits 4:4
    UINT32 Reserved_1                              :  3;  // Bits 7:5
    UINT32 STKD_MODE                               :  1;  // Bits 8:8
    UINT32 STKD_MODE_MS1                           :  1;  // Bits 9:9
    UINT32 Reserved_2                              :  2;  // Bits 11:10
    UINT32 MS_S_SIZE                               :  8;  // Bits 19:12
    UINT32 Reserved_3                              :  4;  // Bits 23:20
    UINT32 STKD_MODE_MS_BITS                       :  3;  // Bits 26:24
    UINT32 Reserved_4                              :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_MAD_SLICE_STRUCT;
typedef union {
  struct {
    UINT32 Reserved_0                              :  6;  // Bits 5:0
    UINT32 HASH_MASK                               :  14;  // Bits 19:6
    UINT32 Reserved_1                              :  4;  // Bits 23:20
    UINT32 HASH_LSB_MASK_BIT                       :  3;  // Bits 26:24
    UINT32 Reserved_2                              :  1;  // Bits 27:27
    UINT32 HASH_MODE                               :  1;  // Bits 28:28
    UINT32 Reserved_3                              :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_MEMORY_SLICE_HASH_STRUCT;
typedef union {
  struct {
    UINT32 Reserved_0                              :  20;  // Bits 19:0
    UINT32 REMAPBASELow                            :  12;  // Bits 31:20
    UINT32 REMAPBASEHigh                           :  7;  // Bits 38:32
    UINT32 Reserved_1                              :  25;  // Bits 63:39
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CMI_REMAP_BASE_STRUCT;
typedef union {
  struct {
    UINT32 Reserved_0                              :  20;  // Bits 19:0
    UINT32 REMAPLMTLow                             :  12;  // Bits 31:20
    UINT32 REMAPLMTHigh                            :  7;  // Bits 38:32
    UINT32 Reserved_1                              :  25;  // Bits 63:39
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CMI_REMAP_LIMIT_STRUCT;
typedef union {
  struct {
    UINT32 Reserved                                :  20;  // Bits 19:0
    UINT32 TOLUD                                   :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_TOLUD_STRUCT;

typedef CMI_MAD_SLICE_STRUCT CMI_MAD_SLICE_NM_P0_STRUCT;
typedef CMI_MEMORY_SLICE_HASH_STRUCT CMI_MEMORY_SLICE_HASH_NM_P0_STRUCT;
typedef union {
  struct {
    UINT32 REQ_WR_PARK_SIZE                        :  4;  // Bits 3:0
    UINT32 RESERVED0                               :  4;  // Bits 7:4
    UINT32 REQ_RD_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 REQ_WR_MAX_CREDIT                       :  8;  // Bits 23:16
    UINT32 REQ_RD_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_STRUCT;
typedef union {
  struct {
    UINT32 REQ_WR_PARK_SIZE                        :  4;  // Bits 3:0
    UINT32 RESERVED0                               :  4;  // Bits 7:4
    UINT32 REQ_RD_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 REQ_WR_MAX_CREDIT                       :  8;  // Bits 23:16
    UINT32 REQ_RD_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_STRUCT;

typedef CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_STRUCT CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_STRUCT;

typedef CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_STRUCT CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_STRUCT;
typedef union {
  struct {
    UINT32 REQ_WR_QUEUEDEPTH                       :  8;  // Bits 7:0
    UINT32 REQ_RD_QUEUEDEPTH                       :  8;  // Bits 15:8
    UINT32 RESERVED1                               :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_REQUEST_PORT_0_REQ_CONFIG_1_STRUCT;
typedef union {
  struct {
    UINT32 REQ_STALL                               :  1;  // Bits 0:0
    UINT32 RSVD0                                   :  4;  // Bits 4:1
    UINT32 RSVD1                                   :  3;  // Bits 7:5
    UINT32 UNSTALL_COUNTER_VALUE                   :  16;  // Bits 23:8
    UINT32 RSVD2                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_REQUEST_PORT_0_STALL_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_REQUEST_PORT_0_RESERVED_0_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_REQUEST_PORT_0_RESERVED_1_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_REQUEST_PORT_0_RESERVED_2_STRUCT;
typedef union {
  struct {
    UINT32 REQ_CMD_SUM                             :  16;  // Bits 15:0
    UINT32 REQ_DATA_SUM                            :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_REQUEST_PORT_0_ACCUM_REQ_IN_STRUCT;
typedef union {
  struct {
    UINT32 RD_CPL_CMD_SUM                          :  16;  // Bits 15:0
    UINT32 RD_CPL_DATA_SUM                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_STRUCT;
typedef union {
  struct {
    UINT32 RSP_CMD_SUM                             :  16;  // Bits 15:0
    UINT32 RSVD                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_STRUCT;

typedef CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_STRUCT CMI_REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_STRUCT;

typedef CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_STRUCT CMI_REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_STRUCT;

typedef CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_STRUCT CMI_REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_STRUCT;

typedef CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_STRUCT CMI_REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_STRUCT;

typedef CMI_REQUEST_PORT_0_REQ_CONFIG_1_STRUCT CMI_REQUEST_PORT_1_REQ_CONFIG_1_STRUCT;

typedef CMI_REQUEST_PORT_0_STALL_STRUCT CMI_REQUEST_PORT_1_STALL_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_REQUEST_PORT_1_RESERVED_0_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_REQUEST_PORT_1_RESERVED_1_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_REQUEST_PORT_1_RESERVED_2_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_REQ_IN_STRUCT CMI_REQUEST_PORT_1_ACCUM_REQ_IN_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_STRUCT CMI_REQUEST_PORT_1_ACCUM_RD_CPL_OUT_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_STRUCT CMI_REQUEST_PORT_1_ACCUM_RSP_OUT_STRUCT;
typedef union {
  struct {
    UINT32 REQ_WR_PARK_SIZE                        :  4;  // Bits 3:0
    UINT32 RESERVED0                               :  4;  // Bits 7:4
    UINT32 REQ_RD_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 REQ_WR_MAX_CREDIT                       :  8;  // Bits 23:16
    UINT32 REQ_RD_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_STRUCT;

typedef CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_STRUCT CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_STRUCT;

typedef CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_STRUCT CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_STRUCT;

typedef CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_STRUCT CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_STRUCT;
typedef union {
  struct {
    UINT32 REQ_WR_QUEUEDEPTH                       :  8;  // Bits 7:0
    UINT32 REQ_RD_QUEUEDEPTH                       :  8;  // Bits 15:8
    UINT32 RESERVED1                               :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_REQUEST_PORT_2_REQ_CONFIG_1_STRUCT;

typedef CMI_REQUEST_PORT_0_STALL_STRUCT CMI_REQUEST_PORT_2_STALL_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_REQUEST_PORT_2_RESERVED_0_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_REQUEST_PORT_2_RESERVED_1_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_REQUEST_PORT_2_RESERVED_2_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_REQ_IN_STRUCT CMI_REQUEST_PORT_2_ACCUM_REQ_IN_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_STRUCT CMI_REQUEST_PORT_2_ACCUM_RD_CPL_OUT_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_STRUCT CMI_REQUEST_PORT_2_ACCUM_RSP_OUT_STRUCT;
typedef union {
  struct {
    UINT32 REQ_WR_PARK_SIZE                        :  4;  // Bits 3:0
    UINT32 RESERVED0                               :  4;  // Bits 7:4
    UINT32 REQ_RD_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 REQ_WR_MAX_CREDIT                       :  8;  // Bits 23:16
    UINT32 REQ_RD_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_STRUCT;

typedef CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_STRUCT CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_STRUCT;

typedef CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_STRUCT CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_STRUCT;

typedef CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_STRUCT CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_STRUCT;
typedef union {
  struct {
    UINT32 REQ_WR_QUEUEDEPTH                       :  8;  // Bits 7:0
    UINT32 REQ_RD_QUEUEDEPTH                       :  8;  // Bits 15:8
    UINT32 RESERVED1                               :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_REQUEST_PORT_3_REQ_CONFIG_1_STRUCT;

typedef CMI_REQUEST_PORT_0_STALL_STRUCT CMI_REQUEST_PORT_3_STALL_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_REQUEST_PORT_3_RESERVED_0_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_REQUEST_PORT_3_RESERVED_1_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_REQUEST_PORT_3_RESERVED_2_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_REQ_IN_STRUCT CMI_REQUEST_PORT_3_ACCUM_REQ_IN_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_STRUCT CMI_REQUEST_PORT_3_ACCUM_RD_CPL_OUT_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_STRUCT CMI_REQUEST_PORT_3_ACCUM_RSP_OUT_STRUCT;

typedef CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_STRUCT CMI_REQUEST_PORT_4_REQ_CONFIG_0_CHANNEL_0_STRUCT;

typedef CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_STRUCT CMI_REQUEST_PORT_4_REQ_CONFIG_0_CHANNEL_1_STRUCT;

typedef CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_STRUCT CMI_REQUEST_PORT_4_REQ_CONFIG_0_CHANNEL_2_STRUCT;

typedef CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_STRUCT CMI_REQUEST_PORT_4_REQ_CONFIG_0_CHANNEL_3_STRUCT;

typedef CMI_REQUEST_PORT_3_REQ_CONFIG_1_STRUCT CMI_REQUEST_PORT_4_REQ_CONFIG_1_STRUCT;

typedef CMI_REQUEST_PORT_0_STALL_STRUCT CMI_REQUEST_PORT_4_STALL_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_REQUEST_PORT_4_RESERVED_0_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_REQUEST_PORT_4_RESERVED_1_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_REQUEST_PORT_4_RESERVED_2_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_REQ_IN_STRUCT CMI_REQUEST_PORT_4_ACCUM_REQ_IN_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_STRUCT CMI_REQUEST_PORT_4_ACCUM_RD_CPL_OUT_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_STRUCT CMI_REQUEST_PORT_4_ACCUM_RSP_OUT_STRUCT;
typedef union {
  struct {
    UINT32 WR_RSP_PARK_SIZE                        :  4;  // Bits 3:0
    UINT32 RESERVED0                               :  4;  // Bits 7:4
    UINT32 RD_CPL_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 RSP_MAX_CREDIT                          :  8;  // Bits 23:16
    UINT32 RD_CPL_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT;

typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_STRUCT;

typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_STRUCT;
typedef union {
  struct {
    UINT32 WR_RSP_PARK_SIZE                        :  4;  // Bits 3:0
    UINT32 RESERVED0                               :  4;  // Bits 7:4
    UINT32 RD_CPL_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 RSP_MAX_CREDIT                          :  8;  // Bits 23:16
    UINT32 RD_CPL_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_STRUCT;
typedef union {
  struct {
    UINT32 RD_CPL_QUEUEDEPTH                       :  8;  // Bits 7:0
    UINT32 RSP_QUEUEDEPTH                          :  8;  // Bits 15:8
    UINT32 REQ_FAST_WAKE                           :  1;  // Bits 16:16
    UINT32 RESERVED1                               :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_RESPOND_PORT_0_CPL_CONFIG_1_STRUCT;
typedef union {
  struct {
    UINT32 RSVD0                                   :  4;  // Bits 3:0
    UINT32 RSP_RD_CPL_STALL                        :  1;  // Bits 4:4
    UINT32 RSVD1                                   :  3;  // Bits 7:5
    UINT32 UNSTALL_COUNTER_VALUE                   :  16;  // Bits 23:8
    UINT32 RSVD2                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_RESPOND_PORT_0_STALL_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_RESPOND_PORT_0_RESERVED_0_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_RESPOND_PORT_0_RESERVED_1_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_RESPOND_PORT_0_RESERVED_2_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_REQ_IN_STRUCT CMI_RESPOND_PORT_0_ACCUM_REQ_OUT_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_STRUCT CMI_RESPOND_PORT_0_ACCUM_RD_CPL_IN_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_STRUCT CMI_RESPOND_PORT_0_ACCUM_RSP_IN_STRUCT;

typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_STRUCT;

typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_STRUCT;

typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_STRUCT;

typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_STRUCT CMI_RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_STRUCT;

typedef CMI_RESPOND_PORT_0_CPL_CONFIG_1_STRUCT CMI_RESPOND_PORT_1_CPL_CONFIG_1_STRUCT;

typedef CMI_RESPOND_PORT_0_STALL_STRUCT CMI_RESPOND_PORT_1_STALL_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_RESPOND_PORT_1_RESERVED_0_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_RESPOND_PORT_1_RESERVED_1_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_RESPOND_PORT_1_RESERVED_2_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_REQ_IN_STRUCT CMI_RESPOND_PORT_1_ACCUM_REQ_OUT_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_STRUCT CMI_RESPOND_PORT_1_ACCUM_RD_CPL_IN_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_STRUCT CMI_RESPOND_PORT_1_ACCUM_RSP_IN_STRUCT;
typedef union {
  struct {
    UINT32 WR_RSP_PARK_SIZE                        :  4;  // Bits 3:0
    UINT32 RESERVED0                               :  4;  // Bits 7:4
    UINT32 RD_CPL_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 RSP_MAX_CREDIT                          :  8;  // Bits 23:16
    UINT32 RD_CPL_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_STRUCT;

typedef CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_STRUCT;

typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_STRUCT;

typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_STRUCT;
typedef union {
  struct {
    UINT32 RD_CPL_QUEUEDEPTH                       :  8;  // Bits 7:0
    UINT32 RSP_QUEUEDEPTH                          :  8;  // Bits 15:8
    UINT32 REQ_FAST_WAKE                           :  1;  // Bits 16:16
    UINT32 RESERVED1                               :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_RESPOND_PORT_2_CPL_CONFIG_1_STRUCT;

typedef CMI_RESPOND_PORT_0_STALL_STRUCT CMI_RESPOND_PORT_2_STALL_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_RESPOND_PORT_2_RESERVED_0_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_RESPOND_PORT_2_RESERVED_1_STRUCT;
typedef union {
  struct {
    UINT32 FIRST_LEVEL_BID_RD_PARK_SIZE_CH_0       :  4;  // Bits 3:0
    UINT32 FIRST_LEVEL_BID_WR_PARK_SIZE_CH_0       :  4;  // Bits 7:4
    UINT32 RESERVED                                :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_REQ_IN_STRUCT CMI_RESPOND_PORT_2_ACCUM_REQ_OUT_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_STRUCT CMI_RESPOND_PORT_2_ACCUM_RD_CPL_IN_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_STRUCT CMI_RESPOND_PORT_2_ACCUM_RSP_IN_STRUCT;
typedef union {
  struct {
    UINT32 WR_RSP_PARK_SIZE                        :  4;  // Bits 3:0
    UINT32 RESERVED0                               :  4;  // Bits 7:4
    UINT32 RD_CPL_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 RESERVED1                               :  4;  // Bits 15:12
    UINT32 RSP_MAX_CREDIT                          :  8;  // Bits 23:16
    UINT32 RD_CPL_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_STRUCT;

typedef CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_STRUCT;

typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_STRUCT;

typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_STRUCT;
typedef union {
  struct {
    UINT32 RD_CPL_QUEUEDEPTH                       :  8;  // Bits 7:0
    UINT32 RSP_QUEUEDEPTH                          :  8;  // Bits 15:8
    UINT32 REQ_FAST_WAKE                           :  1;  // Bits 16:16
    UINT32 RESERVED1                               :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_RESPOND_PORT_3_CPL_CONFIG_1_STRUCT;

typedef CMI_RESPOND_PORT_0_STALL_STRUCT CMI_RESPOND_PORT_3_STALL_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_RESPOND_PORT_3_RESERVED_0_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_RESPOND_PORT_3_RESERVED_1_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_RESPOND_PORT_3_RESERVED_2_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_REQ_IN_STRUCT CMI_RESPOND_PORT_3_ACCUM_REQ_OUT_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_STRUCT CMI_RESPOND_PORT_3_ACCUM_RD_CPL_IN_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_STRUCT CMI_RESPOND_PORT_3_ACCUM_RSP_IN_STRUCT;

typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_RESPOND_PORT_4_CPL_CONFIG_0_CHANNEL_0_STRUCT;

typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_RESPOND_PORT_4_CPL_CONFIG_0_CHANNEL_1_STRUCT;

typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_RESPOND_PORT_4_CPL_CONFIG_0_CHANNEL_2_STRUCT;

typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_RESPOND_PORT_4_CPL_CONFIG_0_CHANNEL_3_STRUCT;
typedef union {
  struct {
    UINT32 RD_CPL_QUEUEDEPTH                       :  8;  // Bits 7:0
    UINT32 RSP_QUEUEDEPTH                          :  8;  // Bits 15:8
    UINT32 REQ_FAST_WAKE                           :  1;  // Bits 16:16
    UINT32 RESERVED1                               :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_RESPOND_PORT_4_CPL_CONFIG_1_STRUCT;

typedef CMI_RESPOND_PORT_0_STALL_STRUCT CMI_RESPOND_PORT_4_STALL_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_RESPOND_PORT_4_RESERVED_0_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_RESPOND_PORT_4_RESERVED_1_STRUCT;

typedef CMF_RSVD0_STRUCT CMI_RESPOND_PORT_4_RESERVED_2_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_REQ_IN_STRUCT CMI_RESPOND_PORT_4_ACCUM_REQ_OUT_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_STRUCT CMI_RESPOND_PORT_4_ACCUM_RD_CPL_IN_STRUCT;

typedef CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_STRUCT CMI_RESPOND_PORT_4_ACCUM_RSP_IN_STRUCT;

typedef CMF_LT_SA_W_PG_ACCESS_POLICY_CP_STRUCT CMF_LT_MEM_SA_PG_ACCESS_POLICY_CP_STRUCT;

typedef CMF_LT_SA_W_PG_ACCESS_POLICY_WAC_STRUCT CMF_LT_MEM_SA_PG_ACCESS_POLICY_WAC_STRUCT;

typedef CMF_LT_SA_W_PG_ACCESS_POLICY_RAC_STRUCT CMF_LT_MEM_SA_PG_ACCESS_POLICY_RAC_STRUCT;

typedef CMF_LT_SA_W_PG_ACCESS_POLICY_CP_STRUCT CMF_OS_PG_ACCESS_POLICY_CP_STRUCT;
typedef union {
  struct {
    UINT32 SAI_MASKLow                             :  32;  // Bits 31:0
    UINT32 SAI_MASKHigh                            :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CMF_OS_PG_ACCESS_POLICY_WAC_STRUCT;

typedef CMF_LT_SA_W_PG_ACCESS_POLICY_RAC_STRUCT CMF_OS_PG_ACCESS_POLICY_RAC_STRUCT;
typedef union {
  struct {
    UINT32 Reserved_0                              :  5;  // Bits 4:0
    UINT32 ERR_ADDRESSLow                          :  27;  // Bits 31:5
    UINT32 ERR_ADDRESSHigh                         :  7;  // Bits 38:32
    UINT32 Reserved_1                              :  9;  // Bits 47:39
    UINT32 ERR_SRC                                 :  3;  // Bits 50:48
    UINT32 Reserved_2                              :  12;  // Bits 62:51
    UINT32 ERR_STS                                 :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CMI_PARITY_ERR_LOG_STRUCT;
typedef union {
  struct {
    UINT32 Reserved_0                              :  8;  // Bits 7:0
    UINT32 ADDR_ERR_EN                             :  1;  // Bits 8:8
    UINT32 Reserved_1                              :  1;  // Bits 9:9
    UINT32 Reserved_2                              :  6;  // Bits 15:10
    UINT32 ERR_SRC_MASK                            :  8;  // Bits 23:16
    UINT32 Reserved_3                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_PARITY_ERR_INJ_STRUCT;
typedef union {
  struct {
    UINT32 ADDR_PARITY_CHK_MASK                    :  8;  // Bits 7:0
    UINT32 ADDR_PARITY_GEN_MASK                    :  8;  // Bits 15:8
    UINT32 DIS_PARITY_PCH_EVENT                    :  1;  // Bits 16:16
    UINT32 DIS_PARITY_LOG                          :  1;  // Bits 17:17
    UINT32 DIS_MULTIPLE_PCH_MSG                    :  1;  // Bits 18:18
    UINT32 Reserved                                :  12;  // Bits 30:19
    UINT32 PARITY_EN                               :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_PARITY_CONTROL_STRUCT;
typedef union {
  struct {
    UINT32 NonVC1Wr_HiPri_Park_Size                :  4;  // Bits 3:0
    UINT32 NonVC1Wr_LoPri_Park_Size                :  4;  // Bits 7:4
    UINT32 VC1Wr_HiPri_Park_Size                   :  4;  // Bits 11:8
    UINT32 VC1Wr_LoPri_Park_Size                   :  4;  // Bits 15:12
    UINT32 Reserved                                :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CMI_REQ_L3_ARB_CONFIG_STRUCT;
typedef union {
  struct {
    UINT32 DIP_VC1_RD_PARK_SIZE1                   :  4;  // Bits 3:0
    UINT32 DIP_VC1_RD_PARK_SIZE2                   :  4;  // Bits 7:4
    UINT32 DIP_VC1_RD_PARK_SIZE3                   :  4;  // Bits 11:8
    UINT32 DIP_VC1_RD_PARK_SIZE4                   :  4;  // Bits 15:12
    UINT32 IOP_VC1_RD_PARK_SIZE1                   :  4;  // Bits 19:16
    UINT32 IOP_VC1_RD_PARK_SIZE2                   :  4;  // Bits 23:20
    UINT32 IOP_VC1_RD_PARK_SIZE3                   :  4;  // Bits 27:24
    UINT32 IOP_VC1_RD_PARK_SIZE4                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IOP_CMI_EP_ARB_CTL_STRUCT;
typedef union {
  struct {
    UINT32 READ_COUNTERLow                         :  32;  // Bits 31:0
    UINT32 READ_COUNTERHigh                        :  32;  // Bits 63:32
  } P0Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_STRUCT;

typedef CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_STRUCT CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_1_P0_STRUCT;
typedef union {
  struct {
    UINT32 READ_COUNTERLow                         :  32;  // Bits 31:0
    UINT32 READ_COUNTERHigh                        :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_3_STRUCT;
typedef union {
  struct {
    UINT32 WRITE_COUNTERLow                        :  32;  // Bits 31:0
    UINT32 WRITE_COUNTERHigh                       :  32;  // Bits 63:32
  } P0Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_STRUCT;

typedef CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_STRUCT CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_1_P0_STRUCT;
typedef union {
  struct {
    UINT32 WRITE_COUNTERLow                        :  32;  // Bits 31:0
    UINT32 WRITE_COUNTERHigh                       :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_3_STRUCT;

typedef CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_STRUCT CMI_RESPOND_PORT_1_RD_COUNTER_CHANNEL_0_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_STRUCT CMI_RESPOND_PORT_1_RD_COUNTER_CHANNEL_1_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_3_STRUCT CMI_RESPOND_PORT_1_RD_COUNTER_CHANNEL_3_STRUCT;

typedef CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_STRUCT CMI_RESPOND_PORT_1_WR_COUNTER_CHANNEL_0_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_STRUCT CMI_RESPOND_PORT_1_WR_COUNTER_CHANNEL_1_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_3_STRUCT CMI_RESPOND_PORT_1_WR_COUNTER_CHANNEL_3_STRUCT;

typedef CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_3_STRUCT CMI_RESPOND_PORT_2_RD_COUNTER_CHANNEL_0_STRUCT;

typedef CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_3_STRUCT CMI_RESPOND_PORT_2_WR_COUNTER_CHANNEL_0_STRUCT;

typedef CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_3_STRUCT CMI_RESPOND_PORT_2_RD_COUNTER_CHANNEL_1_STRUCT;

typedef CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_3_STRUCT CMI_RESPOND_PORT_2_WR_COUNTER_CHANNEL_1_STRUCT;

typedef CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_3_STRUCT CMI_RESPOND_PORT_3_RD_COUNTER_CHANNEL_0_STRUCT;

typedef CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_3_STRUCT CMI_RESPOND_PORT_3_WR_COUNTER_CHANNEL_0_STRUCT;

typedef CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_3_STRUCT CMI_RESPOND_PORT_3_RD_COUNTER_CHANNEL_1_STRUCT;

typedef CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_3_STRUCT CMI_RESPOND_PORT_3_WR_COUNTER_CHANNEL_1_STRUCT;

typedef CMF_LT_SA_W_PG_ACCESS_POLICY_CP_STRUCT CMF_1_LT_SA_W_PG_ACCESS_POLICY_CP_P0_STRUCT;
typedef CMF_LT_SA_W_PG_ACCESS_POLICY_WAC_STRUCT CMF_1_LT_SA_W_PG_ACCESS_POLICY_WAC_P0_STRUCT;
typedef CMF_LT_SA_W_PG_ACCESS_POLICY_RAC_STRUCT CMF_1_LT_SA_W_PG_ACCESS_POLICY_RAC_P0_STRUCT;
typedef CMI_PRIO_THRESHOLD_STRUCT CMI_1_PRIO_THRESHOLD_P0_STRUCT;
typedef CMI_PRIO_LIM_STRUCT CMI_1_PRIO_LIM_P0_STRUCT;
typedef CMF_GLOBAL_CFG_STRUCT CMF_1_GLOBAL_CFG_P0_STRUCT;
typedef CMF_GLOBAL_CFG_1_STRUCT CMF_1_GLOBAL_CFG_1_P0_STRUCT;
typedef CMF_ACCUM_CTRL_STRUCT CMF_1_ACCUM_CTRL_P0_STRUCT;
typedef CMI_IOSF_SB_EP_CTRL_STRUCT CMI_1_IOSF_SB_EP_CTRL_P0_STRUCT;
typedef CMI_CLK_GATE_EN_0_STRUCT CMI_1_CLK_GATE_EN_0_P0_STRUCT;
typedef CMI_CLK_GATE_EN_0_STRUCT CMI_1_CLK_GATE_EN_1_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMF_1_RSVD0_P0_STRUCT;
typedef CMF_RSVD1_STRUCT CMF_1_RSVD1_P0_STRUCT;
typedef CMF_LT_SA_W_PG_ACCESS_POLICY_CP_STRUCT CMF_1_P_U_CODE_PG_ACCESS_POLICY_CP_P0_STRUCT;
typedef CMF_P_U_CODE_PG_ACCESS_POLICY_WAC_STRUCT CMF_1_P_U_CODE_PG_ACCESS_POLICY_WAC_P0_STRUCT;
typedef CMF_P_U_CODE_PG_ACCESS_POLICY_WAC_STRUCT CMF_1_P_U_CODE_PG_ACCESS_POLICY_RAC_P0_STRUCT;
typedef CMF_TOPOLOGY_GLOBAL_CFG_0_STRUCT CMF_1_TOPOLOGY_GLOBAL_CFG_0_P0_STRUCT;
typedef CMF_TOPOLOGY_GLOBAL_CFG_1_STRUCT CMF_1_TOPOLOGY_GLOBAL_CFG_1_P0_STRUCT;
typedef CMF_TOPOLOGY_GLOBAL_CFG_2_STRUCT CMF_1_TOPOLOGY_GLOBAL_CFG_2_P0_STRUCT;
typedef CMF_TOPOLOGY_GLOBAL_CFG_3_STRUCT CMF_1_TOPOLOGY_GLOBAL_CFG_3_P0_STRUCT;
typedef CMF_TOPOLOGY_GLOBAL_CFG_4_STRUCT CMF_1_TOPOLOGY_GLOBAL_CFG_4_P0_STRUCT;
typedef CMF_TOPOLOGY_GLOBAL_CFG_5_STRUCT CMF_1_TOPOLOGY_GLOBAL_CFG_5_P0_STRUCT;
typedef CMI_MAD_SLICE_STRUCT CMI_1_MAD_SLICE_P0_STRUCT;
typedef CMI_MEMORY_SLICE_HASH_STRUCT CMI_1_MEMORY_SLICE_HASH_P0_STRUCT;
typedef CMI_REMAP_BASE_STRUCT CMI_1_REMAP_BASE_P0_STRUCT;
typedef CMI_REMAP_LIMIT_STRUCT CMI_1_REMAP_LIMIT_P0_STRUCT;
typedef CMI_TOLUD_STRUCT CMI_1_TOLUD_P0_STRUCT;
typedef CMI_MAD_SLICE_STRUCT CMI_1_MAD_SLICE_NM_P0_STRUCT;
typedef CMI_MEMORY_SLICE_HASH_STRUCT CMI_1_MEMORY_SLICE_HASH_NM_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_STRUCT CMI_1_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_STRUCT CMI_1_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_STRUCT CMI_1_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_STRUCT CMI_1_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_REQ_CONFIG_1_STRUCT CMI_1_REQUEST_PORT_0_REQ_CONFIG_1_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_STALL_STRUCT CMI_1_REQUEST_PORT_0_STALL_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_REQUEST_PORT_0_RESERVED_0_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_REQUEST_PORT_0_RESERVED_1_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_REQUEST_PORT_0_RESERVED_2_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_REQ_IN_STRUCT CMI_1_REQUEST_PORT_0_ACCUM_REQ_IN_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_STRUCT CMI_1_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_STRUCT CMI_1_REQUEST_PORT_0_ACCUM_RSP_OUT_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_STRUCT CMI_1_REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_STRUCT CMI_1_REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_STRUCT CMI_1_REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_STRUCT CMI_1_REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_REQ_CONFIG_1_STRUCT CMI_1_REQUEST_PORT_1_REQ_CONFIG_1_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_STALL_STRUCT CMI_1_REQUEST_PORT_1_STALL_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_REQUEST_PORT_1_RESERVED_0_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_REQUEST_PORT_1_RESERVED_1_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_REQUEST_PORT_1_RESERVED_2_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_REQ_IN_STRUCT CMI_1_REQUEST_PORT_1_ACCUM_REQ_IN_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_STRUCT CMI_1_REQUEST_PORT_1_ACCUM_RD_CPL_OUT_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_STRUCT CMI_1_REQUEST_PORT_1_ACCUM_RSP_OUT_P0_STRUCT;
typedef CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_STRUCT CMI_1_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_P0_STRUCT;
typedef CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_STRUCT CMI_1_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_STRUCT CMI_1_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_STRUCT CMI_1_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_P0_STRUCT;
typedef CMI_REQUEST_PORT_2_REQ_CONFIG_1_STRUCT CMI_1_REQUEST_PORT_2_REQ_CONFIG_1_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_STALL_STRUCT CMI_1_REQUEST_PORT_2_STALL_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_REQUEST_PORT_2_RESERVED_0_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_REQUEST_PORT_2_RESERVED_1_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_REQUEST_PORT_2_RESERVED_2_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_REQ_IN_STRUCT CMI_1_REQUEST_PORT_2_ACCUM_REQ_IN_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_STRUCT CMI_1_REQUEST_PORT_2_ACCUM_RD_CPL_OUT_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_STRUCT CMI_1_REQUEST_PORT_2_ACCUM_RSP_OUT_P0_STRUCT;
typedef CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_STRUCT CMI_1_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_STRUCT CMI_1_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_STRUCT CMI_1_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_P0_STRUCT;
typedef CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_STRUCT CMI_1_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_P0_STRUCT;
typedef CMI_REQUEST_PORT_3_REQ_CONFIG_1_STRUCT CMI_1_REQUEST_PORT_3_REQ_CONFIG_1_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_STALL_STRUCT CMI_1_REQUEST_PORT_3_STALL_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_REQUEST_PORT_3_RESERVED_0_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_REQUEST_PORT_3_RESERVED_1_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_REQUEST_PORT_3_RESERVED_2_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_REQ_IN_STRUCT CMI_1_REQUEST_PORT_3_ACCUM_REQ_IN_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_STRUCT CMI_1_REQUEST_PORT_3_ACCUM_RD_CPL_OUT_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_STRUCT CMI_1_REQUEST_PORT_3_ACCUM_RSP_OUT_P0_STRUCT;
typedef CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_STRUCT CMI_1_REQUEST_PORT_4_REQ_CONFIG_0_CHANNEL_0_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_STRUCT CMI_1_REQUEST_PORT_4_REQ_CONFIG_0_CHANNEL_1_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_STRUCT CMI_1_REQUEST_PORT_4_REQ_CONFIG_0_CHANNEL_2_P0_STRUCT;
typedef CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_STRUCT CMI_1_REQUEST_PORT_4_REQ_CONFIG_0_CHANNEL_3_P0_STRUCT;
typedef CMI_REQUEST_PORT_3_REQ_CONFIG_1_STRUCT CMI_1_REQUEST_PORT_4_REQ_CONFIG_1_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_STALL_STRUCT CMI_1_REQUEST_PORT_4_STALL_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_REQUEST_PORT_4_RESERVED_0_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_REQUEST_PORT_4_RESERVED_1_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_REQUEST_PORT_4_RESERVED_2_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_REQ_IN_STRUCT CMI_1_REQUEST_PORT_4_ACCUM_REQ_IN_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_STRUCT CMI_1_REQUEST_PORT_4_ACCUM_RD_CPL_OUT_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_STRUCT CMI_1_REQUEST_PORT_4_ACCUM_RSP_OUT_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_1_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_1_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_1_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_STRUCT CMI_1_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_CPL_CONFIG_1_STRUCT CMI_1_RESPOND_PORT_0_CPL_CONFIG_1_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_STALL_STRUCT CMI_1_RESPOND_PORT_0_STALL_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_RESPOND_PORT_0_RESERVED_0_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_RESPOND_PORT_0_RESERVED_1_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_RESPOND_PORT_0_RESERVED_2_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_REQ_IN_STRUCT CMI_1_RESPOND_PORT_0_ACCUM_REQ_OUT_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_STRUCT CMI_1_RESPOND_PORT_0_ACCUM_RD_CPL_IN_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_STRUCT CMI_1_RESPOND_PORT_0_ACCUM_RSP_IN_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_1_RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_1_RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_1_RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_STRUCT CMI_1_RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_CPL_CONFIG_1_STRUCT CMI_1_RESPOND_PORT_1_CPL_CONFIG_1_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_STALL_STRUCT CMI_1_RESPOND_PORT_1_STALL_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_RESPOND_PORT_1_RESERVED_0_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_RESPOND_PORT_1_RESERVED_1_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_RESPOND_PORT_1_RESERVED_2_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_REQ_IN_STRUCT CMI_1_RESPOND_PORT_1_ACCUM_REQ_OUT_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_STRUCT CMI_1_RESPOND_PORT_1_ACCUM_RD_CPL_IN_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_STRUCT CMI_1_RESPOND_PORT_1_ACCUM_RSP_IN_P0_STRUCT;
typedef CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_1_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_P0_STRUCT;
typedef CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_1_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_1_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_1_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_P0_STRUCT;
typedef CMI_RESPOND_PORT_2_CPL_CONFIG_1_STRUCT CMI_1_RESPOND_PORT_2_CPL_CONFIG_1_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_STALL_STRUCT CMI_1_RESPOND_PORT_2_STALL_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_RESPOND_PORT_2_RESERVED_0_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_RESPOND_PORT_2_RESERVED_1_P0_STRUCT;
typedef CMI_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_STRUCT CMI_1_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_REQ_IN_STRUCT CMI_1_RESPOND_PORT_2_ACCUM_REQ_OUT_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_STRUCT CMI_1_RESPOND_PORT_2_ACCUM_RD_CPL_IN_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_STRUCT CMI_1_RESPOND_PORT_2_ACCUM_RSP_IN_P0_STRUCT;
typedef CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_1_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_P0_STRUCT;
typedef CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_1_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_1_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_1_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_P0_STRUCT;
typedef CMI_RESPOND_PORT_3_CPL_CONFIG_1_STRUCT CMI_1_RESPOND_PORT_3_CPL_CONFIG_1_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_STALL_STRUCT CMI_1_RESPOND_PORT_3_STALL_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_RESPOND_PORT_3_RESERVED_0_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_RESPOND_PORT_3_RESERVED_1_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_RESPOND_PORT_3_RESERVED_2_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_REQ_IN_STRUCT CMI_1_RESPOND_PORT_3_ACCUM_REQ_OUT_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_STRUCT CMI_1_RESPOND_PORT_3_ACCUM_RD_CPL_IN_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_STRUCT CMI_1_RESPOND_PORT_3_ACCUM_RSP_IN_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_1_RESPOND_PORT_4_CPL_CONFIG_0_CHANNEL_0_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_1_RESPOND_PORT_4_CPL_CONFIG_0_CHANNEL_1_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_1_RESPOND_PORT_4_CPL_CONFIG_0_CHANNEL_2_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_STRUCT CMI_1_RESPOND_PORT_4_CPL_CONFIG_0_CHANNEL_3_P0_STRUCT;
typedef CMI_RESPOND_PORT_4_CPL_CONFIG_1_STRUCT CMI_1_RESPOND_PORT_4_CPL_CONFIG_1_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_STALL_STRUCT CMI_1_RESPOND_PORT_4_STALL_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_RESPOND_PORT_4_RESERVED_0_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_RESPOND_PORT_4_RESERVED_1_P0_STRUCT;
typedef CMF_RSVD0_STRUCT CMI_1_RESPOND_PORT_4_RESERVED_2_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_REQ_IN_STRUCT CMI_1_RESPOND_PORT_4_ACCUM_REQ_OUT_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_STRUCT CMI_1_RESPOND_PORT_4_ACCUM_RD_CPL_IN_P0_STRUCT;
typedef CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_STRUCT CMI_1_RESPOND_PORT_4_ACCUM_RSP_IN_P0_STRUCT;
typedef CMF_LT_SA_W_PG_ACCESS_POLICY_CP_STRUCT CMF_1_LT_MEM_SA_PG_ACCESS_POLICY_CP_P0_STRUCT;
typedef CMF_LT_SA_W_PG_ACCESS_POLICY_WAC_STRUCT CMF_1_LT_MEM_SA_PG_ACCESS_POLICY_WAC_P0_STRUCT;
typedef CMF_LT_SA_W_PG_ACCESS_POLICY_RAC_STRUCT CMF_1_LT_MEM_SA_PG_ACCESS_POLICY_RAC_P0_STRUCT;
typedef CMF_LT_SA_W_PG_ACCESS_POLICY_CP_STRUCT CMF_1_OS_PG_ACCESS_POLICY_CP_P0_STRUCT;
typedef CMF_OS_PG_ACCESS_POLICY_WAC_STRUCT CMF_1_OS_PG_ACCESS_POLICY_WAC_P0_STRUCT;
typedef CMF_LT_SA_W_PG_ACCESS_POLICY_RAC_STRUCT CMF_1_OS_PG_ACCESS_POLICY_RAC_P0_STRUCT;
typedef CMI_PARITY_ERR_LOG_STRUCT CMI_1_PARITY_ERR_LOG_P0_STRUCT;
typedef CMI_PARITY_ERR_INJ_STRUCT CMI_1_PARITY_ERR_INJ_P0_STRUCT;
typedef CMI_PARITY_CONTROL_STRUCT CMI_1_PARITY_CONTROL_P0_STRUCT;
typedef CMI_REQ_L3_ARB_CONFIG_STRUCT CMI_1_REQ_L3_ARB_CONFIG_P0_STRUCT;
typedef IOP_CMI_EP_ARB_CTL_STRUCT IOP_CMI_1_EP_ARB_CTL_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_STRUCT CMI_1_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_STRUCT CMI_1_RESPOND_PORT_0_RD_COUNTER_CHANNEL_1_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_STRUCT CMI_1_RESPOND_PORT_0_RD_COUNTER_CHANNEL_3_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_STRUCT CMI_1_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_STRUCT CMI_1_RESPOND_PORT_0_WR_COUNTER_CHANNEL_1_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_STRUCT CMI_1_RESPOND_PORT_0_WR_COUNTER_CHANNEL_3_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_STRUCT CMI_1_RESPOND_PORT_1_RD_COUNTER_CHANNEL_0_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_STRUCT CMI_1_RESPOND_PORT_1_RD_COUNTER_CHANNEL_1_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_STRUCT CMI_1_RESPOND_PORT_1_RD_COUNTER_CHANNEL_3_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_STRUCT CMI_1_RESPOND_PORT_1_WR_COUNTER_CHANNEL_0_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_STRUCT CMI_1_RESPOND_PORT_1_WR_COUNTER_CHANNEL_1_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_STRUCT CMI_1_RESPOND_PORT_1_WR_COUNTER_CHANNEL_3_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_STRUCT CMI_1_RESPOND_PORT_2_RD_COUNTER_CHANNEL_0_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_STRUCT CMI_1_RESPOND_PORT_2_WR_COUNTER_CHANNEL_0_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_STRUCT CMI_1_RESPOND_PORT_2_RD_COUNTER_CHANNEL_1_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_STRUCT CMI_1_RESPOND_PORT_2_WR_COUNTER_CHANNEL_1_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_STRUCT CMI_1_RESPOND_PORT_3_RD_COUNTER_CHANNEL_0_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_STRUCT CMI_1_RESPOND_PORT_3_WR_COUNTER_CHANNEL_0_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_STRUCT CMI_1_RESPOND_PORT_3_RD_COUNTER_CHANNEL_1_P0_STRUCT;
typedef CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_STRUCT CMI_1_RESPOND_PORT_3_WR_COUNTER_CHANNEL_1_P0_STRUCT;
#pragma pack(pop)
#endif
