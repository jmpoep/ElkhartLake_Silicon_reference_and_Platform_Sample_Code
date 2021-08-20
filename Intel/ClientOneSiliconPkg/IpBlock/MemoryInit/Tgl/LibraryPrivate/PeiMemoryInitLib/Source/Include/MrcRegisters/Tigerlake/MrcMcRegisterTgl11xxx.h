#ifndef __MrcMcRegisterTgl11xxx_h__
#define __MrcMcRegisterTgl11xxx_h__
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


#define CMF_LT_SA_W_PG_ACCESS_POLICY_CP_REG                            (0x00011000)

  #define CMF_LT_SA_W_PG_ACCESS_POLICY_CP_SAI_MASK_OFF                 ( 0)
  #define CMF_LT_SA_W_PG_ACCESS_POLICY_CP_SAI_MASK_WID                 (64)
  #define CMF_LT_SA_W_PG_ACCESS_POLICY_CP_SAI_MASK_MSK                 (0xFFFFFFFFFFFFFFFFULL)
  #define CMF_LT_SA_W_PG_ACCESS_POLICY_CP_SAI_MASK_MIN                 (0)
  #define CMF_LT_SA_W_PG_ACCESS_POLICY_CP_SAI_MASK_MAX                 (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define CMF_LT_SA_W_PG_ACCESS_POLICY_CP_SAI_MASK_DEF                 (0x40001000208)
  #define CMF_LT_SA_W_PG_ACCESS_POLICY_CP_SAI_MASK_HSH                 (0x40011000)

#define CMF_LT_SA_W_PG_ACCESS_POLICY_WAC_REG                           (0x00011008)

  #define CMF_LT_SA_W_PG_ACCESS_POLICY_WAC_SAI_MASK_OFF                ( 0)
  #define CMF_LT_SA_W_PG_ACCESS_POLICY_WAC_SAI_MASK_WID                (64)
  #define CMF_LT_SA_W_PG_ACCESS_POLICY_WAC_SAI_MASK_MSK                (0xFFFFFFFFFFFFFFFFULL)
  #define CMF_LT_SA_W_PG_ACCESS_POLICY_WAC_SAI_MASK_MIN                (0)
  #define CMF_LT_SA_W_PG_ACCESS_POLICY_WAC_SAI_MASK_MAX                (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define CMF_LT_SA_W_PG_ACCESS_POLICY_WAC_SAI_MASK_DEF                (0x4000100021A)
  #define CMF_LT_SA_W_PG_ACCESS_POLICY_WAC_SAI_MASK_HSH                (0x40011008)

#define CMF_LT_SA_W_PG_ACCESS_POLICY_RAC_REG                           (0x00011010)

  #define CMF_LT_SA_W_PG_ACCESS_POLICY_RAC_SAI_MASK_OFF                ( 0)
  #define CMF_LT_SA_W_PG_ACCESS_POLICY_RAC_SAI_MASK_WID                (64)
  #define CMF_LT_SA_W_PG_ACCESS_POLICY_RAC_SAI_MASK_MSK                (0xFFFFFFFFFFFFFFFFULL)
  #define CMF_LT_SA_W_PG_ACCESS_POLICY_RAC_SAI_MASK_MIN                (0)
  #define CMF_LT_SA_W_PG_ACCESS_POLICY_RAC_SAI_MASK_MAX                (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define CMF_LT_SA_W_PG_ACCESS_POLICY_RAC_SAI_MASK_DEF                (0xFFFFFFFFFFFFFFFF)
  #define CMF_LT_SA_W_PG_ACCESS_POLICY_RAC_SAI_MASK_HSH                (0x40011010)

#define CMI_PRIO_THRESHOLD_REG                                         (0x00011018)

  #define CMI_PRIO_THRESHOLD_NON_VC1_PRIO_THRESHOLD_OFF                ( 0)
  #define CMI_PRIO_THRESHOLD_NON_VC1_PRIO_THRESHOLD_WID                (16)
  #define CMI_PRIO_THRESHOLD_NON_VC1_PRIO_THRESHOLD_MSK                (0x0000FFFF)
  #define CMI_PRIO_THRESHOLD_NON_VC1_PRIO_THRESHOLD_MIN                (0)
  #define CMI_PRIO_THRESHOLD_NON_VC1_PRIO_THRESHOLD_MAX                (65535) // 0x0000FFFF
  #define CMI_PRIO_THRESHOLD_NON_VC1_PRIO_THRESHOLD_DEF                (0x00000008)
  #define CMI_PRIO_THRESHOLD_NON_VC1_PRIO_THRESHOLD_HSH                (0x10011018)

  #define CMI_PRIO_THRESHOLD_VC1_RD_PRIO_THRESHOLD_OFF                 (16)
  #define CMI_PRIO_THRESHOLD_VC1_RD_PRIO_THRESHOLD_WID                 (16)
  #define CMI_PRIO_THRESHOLD_VC1_RD_PRIO_THRESHOLD_MSK                 (0xFFFF0000)
  #define CMI_PRIO_THRESHOLD_VC1_RD_PRIO_THRESHOLD_MIN                 (0)
  #define CMI_PRIO_THRESHOLD_VC1_RD_PRIO_THRESHOLD_MAX                 (65535) // 0x0000FFFF
  #define CMI_PRIO_THRESHOLD_VC1_RD_PRIO_THRESHOLD_DEF                 (0x00000008)
  #define CMI_PRIO_THRESHOLD_VC1_RD_PRIO_THRESHOLD_HSH                 (0x10211018)

#define CMI_PRIO_LIM_REG                                               (0x0001101C)

  #define CMI_PRIO_LIM_LOW_PRIORITY_LIM_OFF                            ( 0)
  #define CMI_PRIO_LIM_LOW_PRIORITY_LIM_WID                            (16)
  #define CMI_PRIO_LIM_LOW_PRIORITY_LIM_MSK                            (0x0000FFFF)
  #define CMI_PRIO_LIM_LOW_PRIORITY_LIM_MIN                            (0)
  #define CMI_PRIO_LIM_LOW_PRIORITY_LIM_MAX                            (65535) // 0x0000FFFF
  #define CMI_PRIO_LIM_LOW_PRIORITY_LIM_DEF                            (0x00000001)
  #define CMI_PRIO_LIM_LOW_PRIORITY_LIM_HSH                            (0x1001101C)

  #define CMI_PRIO_LIM_HIGH_PRIORITY_LIM_OFF                           (16)
  #define CMI_PRIO_LIM_HIGH_PRIORITY_LIM_WID                           (16)
  #define CMI_PRIO_LIM_HIGH_PRIORITY_LIM_MSK                           (0xFFFF0000)
  #define CMI_PRIO_LIM_HIGH_PRIORITY_LIM_MIN                           (0)
  #define CMI_PRIO_LIM_HIGH_PRIORITY_LIM_MAX                           (65535) // 0x0000FFFF
  #define CMI_PRIO_LIM_HIGH_PRIORITY_LIM_DEF                           (0x00000004)
  #define CMI_PRIO_LIM_HIGH_PRIORITY_LIM_HSH                           (0x1021101C)

#define CMF_GLOBAL_CFG_REG                                             (0x00011020)

  #define CMF_GLOBAL_CFG_CREDITS_CONFIG_DONE_OFF                       ( 0)
  #define CMF_GLOBAL_CFG_CREDITS_CONFIG_DONE_WID                       ( 1)
  #define CMF_GLOBAL_CFG_CREDITS_CONFIG_DONE_MSK                       (0x00000001)
  #define CMF_GLOBAL_CFG_CREDITS_CONFIG_DONE_MIN                       (0)
  #define CMF_GLOBAL_CFG_CREDITS_CONFIG_DONE_MAX                       (1) // 0x00000001
  #define CMF_GLOBAL_CFG_CREDITS_CONFIG_DONE_DEF                       (0x00000000)
  #define CMF_GLOBAL_CFG_CREDITS_CONFIG_DONE_HSH                       (0x01011020)

  #define CMF_GLOBAL_CFG_RESERVED_0_OFF                                ( 1)
  #define CMF_GLOBAL_CFG_RESERVED_0_WID                                (31)
  #define CMF_GLOBAL_CFG_RESERVED_0_MSK                                (0xFFFFFFFE)
  #define CMF_GLOBAL_CFG_RESERVED_0_MIN                                (0)
  #define CMF_GLOBAL_CFG_RESERVED_0_MAX                                (2147483647) // 0x7FFFFFFF
  #define CMF_GLOBAL_CFG_RESERVED_0_DEF                                (0x00000000)
  #define CMF_GLOBAL_CFG_RESERVED_0_HSH                                (0x1F031020)

#define CMF_GLOBAL_CFG_1_REG                                           (0x00011028)

  #define CMF_GLOBAL_CFG_1_ISM_IDLE_TIME_OFF                           ( 0)
  #define CMF_GLOBAL_CFG_1_ISM_IDLE_TIME_WID                           ( 8)
  #define CMF_GLOBAL_CFG_1_ISM_IDLE_TIME_MSK                           (0x000000FF)
  #define CMF_GLOBAL_CFG_1_ISM_IDLE_TIME_MIN                           (0)
  #define CMF_GLOBAL_CFG_1_ISM_IDLE_TIME_MAX                           (255) // 0x000000FF
  #define CMF_GLOBAL_CFG_1_ISM_IDLE_TIME_DEF                           (0x00000010)
  #define CMF_GLOBAL_CFG_1_ISM_IDLE_TIME_HSH                           (0x08011028)

  #define CMF_GLOBAL_CFG_1_FIXED_WINDOW_OFF                            ( 8)
  #define CMF_GLOBAL_CFG_1_FIXED_WINDOW_WID                            ( 1)
  #define CMF_GLOBAL_CFG_1_FIXED_WINDOW_MSK                            (0x00000100)
  #define CMF_GLOBAL_CFG_1_FIXED_WINDOW_MIN                            (0)
  #define CMF_GLOBAL_CFG_1_FIXED_WINDOW_MAX                            (1) // 0x00000001
  #define CMF_GLOBAL_CFG_1_FIXED_WINDOW_DEF                            (0x00000000)
  #define CMF_GLOBAL_CFG_1_FIXED_WINDOW_HSH                            (0x01111028)

  #define CMF_GLOBAL_CFG_1_CLK_GATE_EN_OFF                             ( 9)
  #define CMF_GLOBAL_CFG_1_CLK_GATE_EN_WID                             ( 1)
  #define CMF_GLOBAL_CFG_1_CLK_GATE_EN_MSK                             (0x00000200)
  #define CMF_GLOBAL_CFG_1_CLK_GATE_EN_MIN                             (0)
  #define CMF_GLOBAL_CFG_1_CLK_GATE_EN_MAX                             (1) // 0x00000001
  #define CMF_GLOBAL_CFG_1_CLK_GATE_EN_DEF                             (0x00000001)
  #define CMF_GLOBAL_CFG_1_CLK_GATE_EN_HSH                             (0x01131028)

  #define CMF_GLOBAL_CFG_1_FORCE_ISM_ACTIVE_OFF                        (10)
  #define CMF_GLOBAL_CFG_1_FORCE_ISM_ACTIVE_WID                        ( 1)
  #define CMF_GLOBAL_CFG_1_FORCE_ISM_ACTIVE_MSK                        (0x00000400)
  #define CMF_GLOBAL_CFG_1_FORCE_ISM_ACTIVE_MIN                        (0)
  #define CMF_GLOBAL_CFG_1_FORCE_ISM_ACTIVE_MAX                        (1) // 0x00000001
  #define CMF_GLOBAL_CFG_1_FORCE_ISM_ACTIVE_DEF                        (0x00000000)
  #define CMF_GLOBAL_CFG_1_FORCE_ISM_ACTIVE_HSH                        (0x01151028)

  #define CMF_GLOBAL_CFG_1_BYPASS_EN_OFF                               (11)
  #define CMF_GLOBAL_CFG_1_BYPASS_EN_WID                               ( 1)
  #define CMF_GLOBAL_CFG_1_BYPASS_EN_MSK                               (0x00000800)
  #define CMF_GLOBAL_CFG_1_BYPASS_EN_MIN                               (0)
  #define CMF_GLOBAL_CFG_1_BYPASS_EN_MAX                               (1) // 0x00000001
  #define CMF_GLOBAL_CFG_1_BYPASS_EN_DEF                               (0x00000001)
  #define CMF_GLOBAL_CFG_1_BYPASS_EN_HSH                               (0x01171028)

  #define CMF_GLOBAL_CFG_1_DIS_PERF_COUNTERS_OFF                       (12)
  #define CMF_GLOBAL_CFG_1_DIS_PERF_COUNTERS_WID                       ( 1)
  #define CMF_GLOBAL_CFG_1_DIS_PERF_COUNTERS_MSK                       (0x00001000)
  #define CMF_GLOBAL_CFG_1_DIS_PERF_COUNTERS_MIN                       (0)
  #define CMF_GLOBAL_CFG_1_DIS_PERF_COUNTERS_MAX                       (1) // 0x00000001
  #define CMF_GLOBAL_CFG_1_DIS_PERF_COUNTERS_DEF                       (0x00000000)
  #define CMF_GLOBAL_CFG_1_DIS_PERF_COUNTERS_HSH                       (0x01191028)

  #define CMF_GLOBAL_CFG_1_DIS_GLBDRV_GATING_OFF                       (13)
  #define CMF_GLOBAL_CFG_1_DIS_GLBDRV_GATING_WID                       ( 1)
  #define CMF_GLOBAL_CFG_1_DIS_GLBDRV_GATING_MSK                       (0x00002000)
  #define CMF_GLOBAL_CFG_1_DIS_GLBDRV_GATING_MIN                       (0)
  #define CMF_GLOBAL_CFG_1_DIS_GLBDRV_GATING_MAX                       (1) // 0x00000001
  #define CMF_GLOBAL_CFG_1_DIS_GLBDRV_GATING_DEF                       (0x00000000)
  #define CMF_GLOBAL_CFG_1_DIS_GLBDRV_GATING_HSH                       (0x011B1028)

  #define CMF_GLOBAL_CFG_1_DIS_RSP_PORT_PRE_VALID_OFF                  (14)
  #define CMF_GLOBAL_CFG_1_DIS_RSP_PORT_PRE_VALID_WID                  ( 1)
  #define CMF_GLOBAL_CFG_1_DIS_RSP_PORT_PRE_VALID_MSK                  (0x00004000)
  #define CMF_GLOBAL_CFG_1_DIS_RSP_PORT_PRE_VALID_MIN                  (0)
  #define CMF_GLOBAL_CFG_1_DIS_RSP_PORT_PRE_VALID_MAX                  (1) // 0x00000001
  #define CMF_GLOBAL_CFG_1_DIS_RSP_PORT_PRE_VALID_DEF                  (0x00000000)
  #define CMF_GLOBAL_CFG_1_DIS_RSP_PORT_PRE_VALID_HSH                  (0x011D1028)

  #define CMF_GLOBAL_CFG_1_DIS_RSP_PORT_BYPASS_PRE_VALID_OFF           (15)
  #define CMF_GLOBAL_CFG_1_DIS_RSP_PORT_BYPASS_PRE_VALID_WID           ( 1)
  #define CMF_GLOBAL_CFG_1_DIS_RSP_PORT_BYPASS_PRE_VALID_MSK           (0x00008000)
  #define CMF_GLOBAL_CFG_1_DIS_RSP_PORT_BYPASS_PRE_VALID_MIN           (0)
  #define CMF_GLOBAL_CFG_1_DIS_RSP_PORT_BYPASS_PRE_VALID_MAX           (1) // 0x00000001
  #define CMF_GLOBAL_CFG_1_DIS_RSP_PORT_BYPASS_PRE_VALID_DEF           (0x00000000)
  #define CMF_GLOBAL_CFG_1_DIS_RSP_PORT_BYPASS_PRE_VALID_HSH           (0x011F1028)

  #define CMF_GLOBAL_CFG_1_RESERVED_OFF                                (16)
  #define CMF_GLOBAL_CFG_1_RESERVED_WID                                (16)
  #define CMF_GLOBAL_CFG_1_RESERVED_MSK                                (0xFFFF0000)
  #define CMF_GLOBAL_CFG_1_RESERVED_MIN                                (0)
  #define CMF_GLOBAL_CFG_1_RESERVED_MAX                                (65535) // 0x0000FFFF
  #define CMF_GLOBAL_CFG_1_RESERVED_DEF                                (0x00000000)
  #define CMF_GLOBAL_CFG_1_RESERVED_HSH                                (0x10211028)

#define CMF_ACCUM_CTRL_REG                                             (0x00011040)

  #define CMF_ACCUM_CTRL_CMD_CLEAR_OFF                                 ( 0)
  #define CMF_ACCUM_CTRL_CMD_CLEAR_WID                                 ( 1)
  #define CMF_ACCUM_CTRL_CMD_CLEAR_MSK                                 (0x00000001)
  #define CMF_ACCUM_CTRL_CMD_CLEAR_MIN                                 (0)
  #define CMF_ACCUM_CTRL_CMD_CLEAR_MAX                                 (1) // 0x00000001
  #define CMF_ACCUM_CTRL_CMD_CLEAR_DEF                                 (0x00000000)
  #define CMF_ACCUM_CTRL_CMD_CLEAR_HSH                                 (0x01011040)

  #define CMF_ACCUM_CTRL_CMD_ENABLE_OFF                                ( 1)
  #define CMF_ACCUM_CTRL_CMD_ENABLE_WID                                ( 1)
  #define CMF_ACCUM_CTRL_CMD_ENABLE_MSK                                (0x00000002)
  #define CMF_ACCUM_CTRL_CMD_ENABLE_MIN                                (0)
  #define CMF_ACCUM_CTRL_CMD_ENABLE_MAX                                (1) // 0x00000001
  #define CMF_ACCUM_CTRL_CMD_ENABLE_DEF                                (0x00000000)
  #define CMF_ACCUM_CTRL_CMD_ENABLE_HSH                                (0x01031040)

  #define CMF_ACCUM_CTRL_CMD_FUNC_OV_OFF                               ( 2)
  #define CMF_ACCUM_CTRL_CMD_FUNC_OV_WID                               ( 1)
  #define CMF_ACCUM_CTRL_CMD_FUNC_OV_MSK                               (0x00000004)
  #define CMF_ACCUM_CTRL_CMD_FUNC_OV_MIN                               (0)
  #define CMF_ACCUM_CTRL_CMD_FUNC_OV_MAX                               (1) // 0x00000001
  #define CMF_ACCUM_CTRL_CMD_FUNC_OV_DEF                               (0x00000000)
  #define CMF_ACCUM_CTRL_CMD_FUNC_OV_HSH                               (0x01051040)

  #define CMF_ACCUM_CTRL_RESERVED_OFF                                  ( 3)
  #define CMF_ACCUM_CTRL_RESERVED_WID                                  (29)
  #define CMF_ACCUM_CTRL_RESERVED_MSK                                  (0xFFFFFFF8)
  #define CMF_ACCUM_CTRL_RESERVED_MIN                                  (0)
  #define CMF_ACCUM_CTRL_RESERVED_MAX                                  (536870911) // 0x1FFFFFFF
  #define CMF_ACCUM_CTRL_RESERVED_DEF                                  (0x00000000)
  #define CMF_ACCUM_CTRL_RESERVED_HSH                                  (0x1D071040)

#define CMI_IOSF_SB_EP_CTRL_REG                                        (0x00011044)

  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEDEF_OFF                    ( 0)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEDEF_WID                    ( 1)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEDEF_MSK                    (0x00000001)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEDEF_MIN                    (0)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEDEF_MAX                    (1) // 0x00000001
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEDEF_DEF                    (0x00000000)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEDEF_HSH                    (0x01011044)

  #define CMI_IOSF_SB_EP_CTRL_RSVD0_OFF                                ( 1)
  #define CMI_IOSF_SB_EP_CTRL_RSVD0_WID                                ( 7)
  #define CMI_IOSF_SB_EP_CTRL_RSVD0_MSK                                (0x000000FE)
  #define CMI_IOSF_SB_EP_CTRL_RSVD0_MIN                                (0)
  #define CMI_IOSF_SB_EP_CTRL_RSVD0_MAX                                (127) // 0x0000007F
  #define CMI_IOSF_SB_EP_CTRL_RSVD0_DEF                                (0x00000000)
  #define CMI_IOSF_SB_EP_CTRL_RSVD0_HSH                                (0x07031044)

  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEN_OFF                      ( 8)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEN_WID                      ( 1)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEN_MSK                      (0x00000100)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEN_MIN                      (0)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEN_MAX                      (1) // 0x00000001
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEN_DEF                      (0x00000001)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEN_HSH                      (0x01111044)

  #define CMI_IOSF_SB_EP_CTRL_RSVD1_OFF                                ( 9)
  #define CMI_IOSF_SB_EP_CTRL_RSVD1_WID                                ( 7)
  #define CMI_IOSF_SB_EP_CTRL_RSVD1_MSK                                (0x0000FE00)
  #define CMI_IOSF_SB_EP_CTRL_RSVD1_MIN                                (0)
  #define CMI_IOSF_SB_EP_CTRL_RSVD1_MAX                                (127) // 0x0000007F
  #define CMI_IOSF_SB_EP_CTRL_RSVD1_DEF                                (0x00000000)
  #define CMI_IOSF_SB_EP_CTRL_RSVD1_HSH                                (0x07131044)

  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_IDLECNT_OFF                       (16)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_IDLECNT_WID                       ( 8)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_IDLECNT_MSK                       (0x00FF0000)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_IDLECNT_MIN                       (0)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_IDLECNT_MAX                       (255) // 0x000000FF
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_IDLECNT_DEF                       (0x00000010)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_IDLECNT_HSH                       (0x08211044)

  #define CMI_IOSF_SB_EP_CTRL_RSVD2_OFF                                (24)
  #define CMI_IOSF_SB_EP_CTRL_RSVD2_WID                                ( 8)
  #define CMI_IOSF_SB_EP_CTRL_RSVD2_MSK                                (0xFF000000)
  #define CMI_IOSF_SB_EP_CTRL_RSVD2_MIN                                (0)
  #define CMI_IOSF_SB_EP_CTRL_RSVD2_MAX                                (255) // 0x000000FF
  #define CMI_IOSF_SB_EP_CTRL_RSVD2_DEF                                (0x00000000)
  #define CMI_IOSF_SB_EP_CTRL_RSVD2_HSH                                (0x08311044)

#define CMI_CLK_GATE_EN_0_REG                                          (0x00011048)

  #define CMI_CLK_GATE_EN_0_CLK_GATE_EN_OFF                            ( 0)
  #define CMI_CLK_GATE_EN_0_CLK_GATE_EN_WID                            (32)
  #define CMI_CLK_GATE_EN_0_CLK_GATE_EN_MSK                            (0xFFFFFFFF)
  #define CMI_CLK_GATE_EN_0_CLK_GATE_EN_MIN                            (0)
  #define CMI_CLK_GATE_EN_0_CLK_GATE_EN_MAX                            (4294967295) // 0xFFFFFFFF
  #define CMI_CLK_GATE_EN_0_CLK_GATE_EN_DEF                            (0xFFFFFFFF)
  #define CMI_CLK_GATE_EN_0_CLK_GATE_EN_HSH                            (0x20011048)

#define CMI_CLK_GATE_EN_1_REG                                          (0x0001104C)
//Duplicate of CMI_CLK_GATE_EN_0_REG

#define CMF_RSVD0_REG                                                  (0x00011060)

  #define CMF_RSVD0_RESERVED_OFF                                       ( 0)
  #define CMF_RSVD0_RESERVED_WID                                       (32)
  #define CMF_RSVD0_RESERVED_MSK                                       (0xFFFFFFFF)
  #define CMF_RSVD0_RESERVED_MIN                                       (0)
  #define CMF_RSVD0_RESERVED_MAX                                       (4294967295) // 0xFFFFFFFF
  #define CMF_RSVD0_RESERVED_DEF                                       (0x00000000)
  #define CMF_RSVD0_RESERVED_HSH                                       (0x20011060)

#define CMF_RSVD1_REG                                                  (0x00011064)

  #define CMF_RSVD1_RESERVED_OFF                                       ( 0)
  #define CMF_RSVD1_RESERVED_WID                                       (32)
  #define CMF_RSVD1_RESERVED_MSK                                       (0xFFFFFFFF)
  #define CMF_RSVD1_RESERVED_MIN                                       (0)
  #define CMF_RSVD1_RESERVED_MAX                                       (4294967295) // 0xFFFFFFFF
  #define CMF_RSVD1_RESERVED_DEF                                       (0xFFFFFFFF)
  #define CMF_RSVD1_RESERVED_HSH                                       (0x20011064)

#define CMF_P_U_CODE_PG_ACCESS_POLICY_CP_REG                           (0x00011070)
//Duplicate of CMF_LT_SA_W_PG_ACCESS_POLICY_CP_REG

#define CMF_P_U_CODE_PG_ACCESS_POLICY_WAC_REG                          (0x00011078)

  #define CMF_P_U_CODE_PG_ACCESS_POLICY_WAC_SAI_MASK_OFF               ( 0)
  #define CMF_P_U_CODE_PG_ACCESS_POLICY_WAC_SAI_MASK_WID               (64)
  #define CMF_P_U_CODE_PG_ACCESS_POLICY_WAC_SAI_MASK_MSK               (0xFFFFFFFFFFFFFFFFULL)
  #define CMF_P_U_CODE_PG_ACCESS_POLICY_WAC_SAI_MASK_MIN               (0)
  #define CMF_P_U_CODE_PG_ACCESS_POLICY_WAC_SAI_MASK_MAX               (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define CMF_P_U_CODE_PG_ACCESS_POLICY_WAC_SAI_MASK_DEF               (0x4000100020A)
  #define CMF_P_U_CODE_PG_ACCESS_POLICY_WAC_SAI_MASK_HSH               (0x40011078)

#define CMF_P_U_CODE_PG_ACCESS_POLICY_RAC_REG                          (0x00011080)
//Duplicate of CMF_P_U_CODE_PG_ACCESS_POLICY_WAC_REG

#define CMF_TOPOLOGY_GLOBAL_CFG_0_REG                                  (0x00011088)

  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SEL_2LM_1LM_OFF                    ( 0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SEL_2LM_1LM_WID                    ( 1)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SEL_2LM_1LM_MSK                    (0x00000001)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SEL_2LM_1LM_MIN                    (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SEL_2LM_1LM_MAX                    (1) // 0x00000001
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SEL_2LM_1LM_DEF                    (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SEL_2LM_1LM_HSH                    (0x01011088)

  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SEL_TME_ON_OFF                     ( 1)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SEL_TME_ON_WID                     ( 1)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SEL_TME_ON_MSK                     (0x00000002)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SEL_TME_ON_MIN                     (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SEL_TME_ON_MAX                     (1) // 0x00000001
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SEL_TME_ON_DEF                     (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SEL_TME_ON_HSH                     (0x01031088)

  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SEL_IBECC_ON_OFF                   ( 2)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SEL_IBECC_ON_WID                   ( 1)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SEL_IBECC_ON_MSK                   (0x00000004)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SEL_IBECC_ON_MIN                   (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SEL_IBECC_ON_MAX                   (1) // 0x00000001
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SEL_IBECC_ON_DEF                   (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SEL_IBECC_ON_HSH                   (0x01051088)

  #define CMF_TOPOLOGY_GLOBAL_CFG_0_Reserved_0_OFF                     ( 3)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_Reserved_0_WID                     ( 5)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_Reserved_0_MSK                     (0x000000F8)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_Reserved_0_MIN                     (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_Reserved_0_MAX                     (31) // 0x0000001F
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_Reserved_0_DEF                     (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_Reserved_0_HSH                     (0x05071088)

  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SLICE_0_DISABLE_OFF                ( 8)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SLICE_0_DISABLE_WID                ( 1)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SLICE_0_DISABLE_MSK                (0x00000100)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SLICE_0_DISABLE_MIN                (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SLICE_0_DISABLE_MAX                (1) // 0x00000001
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SLICE_0_DISABLE_DEF                (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SLICE_0_DISABLE_HSH                (0x01111088)

  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SLICE_1_DISABLE_OFF                ( 9)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SLICE_1_DISABLE_WID                ( 1)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SLICE_1_DISABLE_MSK                (0x00000200)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SLICE_1_DISABLE_MIN                (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SLICE_1_DISABLE_MAX                (1) // 0x00000001
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SLICE_1_DISABLE_DEF                (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_SLICE_1_DISABLE_HSH                (0x01131088)

  #define CMF_TOPOLOGY_GLOBAL_CFG_0_Reserved_1_OFF                     (10)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_Reserved_1_WID                     (22)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_Reserved_1_MSK                     (0xFFFFFC00)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_Reserved_1_MIN                     (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_Reserved_1_MAX                     (4194303) // 0x003FFFFF
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_Reserved_1_DEF                     (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_0_Reserved_1_HSH                     (0x16151088)

#define CMF_TOPOLOGY_GLOBAL_CFG_1_REG                                  (0x0001108C)

  #define CMF_TOPOLOGY_GLOBAL_CFG_1_Reserved_0_OFF                     ( 0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_Reserved_0_WID                     (10)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_Reserved_0_MSK                     (0x000003FF)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_Reserved_0_MIN                     (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_Reserved_0_MAX                     (1023) // 0x000003FF
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_Reserved_0_DEF                     (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_Reserved_0_HSH                     (0x0A01108C)

  #define CMF_TOPOLOGY_GLOBAL_CFG_1_AGENT_WR_RSP_OFF                   (10)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_AGENT_WR_RSP_WID                   ( 5)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_AGENT_WR_RSP_MSK                   (0x00007C00)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_AGENT_WR_RSP_MIN                   (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_AGENT_WR_RSP_MAX                   (31) // 0x0000001F
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_AGENT_WR_RSP_DEF                   (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_AGENT_WR_RSP_HSH                   (0x0515108C)

  #define CMF_TOPOLOGY_GLOBAL_CFG_1_Reserved_1_OFF                     (15)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_Reserved_1_WID                     ( 3)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_Reserved_1_MSK                     (0x00038000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_Reserved_1_MIN                     (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_Reserved_1_MAX                     (7) // 0x00000007
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_Reserved_1_DEF                     (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_Reserved_1_HSH                     (0x031F108C)

  #define CMF_TOPOLOGY_GLOBAL_CFG_1_CPL_MUX_DEMUX_3_CFG_OFF            (18)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_CPL_MUX_DEMUX_3_CFG_WID            ( 1)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_CPL_MUX_DEMUX_3_CFG_MSK            (0x00040000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_CPL_MUX_DEMUX_3_CFG_MIN            (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_CPL_MUX_DEMUX_3_CFG_MAX            (1) // 0x00000001
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_CPL_MUX_DEMUX_3_CFG_DEF            (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_CPL_MUX_DEMUX_3_CFG_HSH            (0x0125108C)

  #define CMF_TOPOLOGY_GLOBAL_CFG_1_CPL_MUX_DEMUX_2_CFG_OFF            (19)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_CPL_MUX_DEMUX_2_CFG_WID            ( 2)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_CPL_MUX_DEMUX_2_CFG_MSK            (0x00180000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_CPL_MUX_DEMUX_2_CFG_MIN            (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_CPL_MUX_DEMUX_2_CFG_MAX            (3) // 0x00000003
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_CPL_MUX_DEMUX_2_CFG_DEF            (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_CPL_MUX_DEMUX_2_CFG_HSH            (0x0227108C)

  #define CMF_TOPOLOGY_GLOBAL_CFG_1_REQ_MUX_DEMUX_1_CFG_OFF            (21)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_REQ_MUX_DEMUX_1_CFG_WID            ( 2)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_REQ_MUX_DEMUX_1_CFG_MSK            (0x00600000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_REQ_MUX_DEMUX_1_CFG_MIN            (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_REQ_MUX_DEMUX_1_CFG_MAX            (3) // 0x00000003
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_REQ_MUX_DEMUX_1_CFG_DEF            (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_REQ_MUX_DEMUX_1_CFG_HSH            (0x022B108C)

  #define CMF_TOPOLOGY_GLOBAL_CFG_1_REQ_MUX_DEMUX_0_CFG_OFF            (23)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_REQ_MUX_DEMUX_0_CFG_WID            ( 1)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_REQ_MUX_DEMUX_0_CFG_MSK            (0x00800000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_REQ_MUX_DEMUX_0_CFG_MIN            (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_REQ_MUX_DEMUX_0_CFG_MAX            (1) // 0x00000001
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_REQ_MUX_DEMUX_0_CFG_DEF            (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_REQ_MUX_DEMUX_0_CFG_HSH            (0x012F108C)

  #define CMF_TOPOLOGY_GLOBAL_CFG_1_Reserved_2_OFF                     (24)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_Reserved_2_WID                     ( 8)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_Reserved_2_MSK                     (0xFF000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_Reserved_2_MIN                     (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_Reserved_2_MAX                     (255) // 0x000000FF
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_Reserved_2_DEF                     (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_1_Reserved_2_HSH                     (0x0831108C)

#define CMF_TOPOLOGY_GLOBAL_CFG_2_REG                                  (0x00011090)

  #define CMF_TOPOLOGY_GLOBAL_CFG_2_Reserved_0_OFF                     ( 0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_Reserved_0_WID                     (10)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_Reserved_0_MSK                     (0x000003FF)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_Reserved_0_MIN                     (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_Reserved_0_MAX                     (1023) // 0x000003FF
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_Reserved_0_DEF                     (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_Reserved_0_HSH                     (0x0A011090)

  #define CMF_TOPOLOGY_GLOBAL_CFG_2_AGENT_WR_RSP_OFF                   (10)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_AGENT_WR_RSP_WID                   ( 5)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_AGENT_WR_RSP_MSK                   (0x00007C00)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_AGENT_WR_RSP_MIN                   (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_AGENT_WR_RSP_MAX                   (31) // 0x0000001F
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_AGENT_WR_RSP_DEF                   (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_AGENT_WR_RSP_HSH                   (0x05151090)

  #define CMF_TOPOLOGY_GLOBAL_CFG_2_Reserved_1_OFF                     (15)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_Reserved_1_WID                     ( 3)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_Reserved_1_MSK                     (0x00038000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_Reserved_1_MIN                     (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_Reserved_1_MAX                     (7) // 0x00000007
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_Reserved_1_DEF                     (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_Reserved_1_HSH                     (0x031F1090)

  #define CMF_TOPOLOGY_GLOBAL_CFG_2_CPL_MUX_DEMUX_3_CFG_OFF            (18)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_CPL_MUX_DEMUX_3_CFG_WID            ( 1)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_CPL_MUX_DEMUX_3_CFG_MSK            (0x00040000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_CPL_MUX_DEMUX_3_CFG_MIN            (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_CPL_MUX_DEMUX_3_CFG_MAX            (1) // 0x00000001
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_CPL_MUX_DEMUX_3_CFG_DEF            (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_CPL_MUX_DEMUX_3_CFG_HSH            (0x01251090)

  #define CMF_TOPOLOGY_GLOBAL_CFG_2_CPL_MUX_DEMUX_2_CFG_OFF            (19)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_CPL_MUX_DEMUX_2_CFG_WID            ( 2)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_CPL_MUX_DEMUX_2_CFG_MSK            (0x00180000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_CPL_MUX_DEMUX_2_CFG_MIN            (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_CPL_MUX_DEMUX_2_CFG_MAX            (3) // 0x00000003
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_CPL_MUX_DEMUX_2_CFG_DEF            (0x00000001)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_CPL_MUX_DEMUX_2_CFG_HSH            (0x02271090)

  #define CMF_TOPOLOGY_GLOBAL_CFG_2_REQ_MUX_DEMUX_1_CFG_OFF            (21)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_REQ_MUX_DEMUX_1_CFG_WID            ( 2)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_REQ_MUX_DEMUX_1_CFG_MSK            (0x00600000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_REQ_MUX_DEMUX_1_CFG_MIN            (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_REQ_MUX_DEMUX_1_CFG_MAX            (3) // 0x00000003
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_REQ_MUX_DEMUX_1_CFG_DEF            (0x00000001)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_REQ_MUX_DEMUX_1_CFG_HSH            (0x022B1090)

  #define CMF_TOPOLOGY_GLOBAL_CFG_2_REQ_MUX_DEMUX_0_CFG_OFF            (23)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_REQ_MUX_DEMUX_0_CFG_WID            ( 1)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_REQ_MUX_DEMUX_0_CFG_MSK            (0x00800000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_REQ_MUX_DEMUX_0_CFG_MIN            (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_REQ_MUX_DEMUX_0_CFG_MAX            (1) // 0x00000001
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_REQ_MUX_DEMUX_0_CFG_DEF            (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_REQ_MUX_DEMUX_0_CFG_HSH            (0x012F1090)

  #define CMF_TOPOLOGY_GLOBAL_CFG_2_Reserved_2_OFF                     (24)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_Reserved_2_WID                     ( 8)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_Reserved_2_MSK                     (0xFF000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_Reserved_2_MIN                     (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_Reserved_2_MAX                     (255) // 0x000000FF
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_Reserved_2_DEF                     (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_2_Reserved_2_HSH                     (0x08311090)

#define CMF_TOPOLOGY_GLOBAL_CFG_3_REG                                  (0x00011094)

  #define CMF_TOPOLOGY_GLOBAL_CFG_3_Reserved_0_OFF                     ( 0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_Reserved_0_WID                     (10)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_Reserved_0_MSK                     (0x000003FF)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_Reserved_0_MIN                     (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_Reserved_0_MAX                     (1023) // 0x000003FF
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_Reserved_0_DEF                     (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_Reserved_0_HSH                     (0x0A011094)

  #define CMF_TOPOLOGY_GLOBAL_CFG_3_AGENT_WR_RSP_OFF                   (10)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_AGENT_WR_RSP_WID                   ( 5)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_AGENT_WR_RSP_MSK                   (0x00007C00)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_AGENT_WR_RSP_MIN                   (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_AGENT_WR_RSP_MAX                   (31) // 0x0000001F
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_AGENT_WR_RSP_DEF                   (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_AGENT_WR_RSP_HSH                   (0x05151094)

  #define CMF_TOPOLOGY_GLOBAL_CFG_3_Reserved_1_OFF                     (15)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_Reserved_1_WID                     ( 3)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_Reserved_1_MSK                     (0x00038000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_Reserved_1_MIN                     (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_Reserved_1_MAX                     (7) // 0x00000007
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_Reserved_1_DEF                     (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_Reserved_1_HSH                     (0x031F1094)

  #define CMF_TOPOLOGY_GLOBAL_CFG_3_CPL_MUX_DEMUX_3_CFG_OFF            (18)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_CPL_MUX_DEMUX_3_CFG_WID            ( 1)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_CPL_MUX_DEMUX_3_CFG_MSK            (0x00040000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_CPL_MUX_DEMUX_3_CFG_MIN            (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_CPL_MUX_DEMUX_3_CFG_MAX            (1) // 0x00000001
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_CPL_MUX_DEMUX_3_CFG_DEF            (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_CPL_MUX_DEMUX_3_CFG_HSH            (0x01251094)

  #define CMF_TOPOLOGY_GLOBAL_CFG_3_CPL_MUX_DEMUX_2_CFG_OFF            (19)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_CPL_MUX_DEMUX_2_CFG_WID            ( 2)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_CPL_MUX_DEMUX_2_CFG_MSK            (0x00180000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_CPL_MUX_DEMUX_2_CFG_MIN            (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_CPL_MUX_DEMUX_2_CFG_MAX            (3) // 0x00000003
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_CPL_MUX_DEMUX_2_CFG_DEF            (0x00000002)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_CPL_MUX_DEMUX_2_CFG_HSH            (0x02271094)

  #define CMF_TOPOLOGY_GLOBAL_CFG_3_REQ_MUX_DEMUX_1_CFG_OFF            (21)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_REQ_MUX_DEMUX_1_CFG_WID            ( 2)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_REQ_MUX_DEMUX_1_CFG_MSK            (0x00600000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_REQ_MUX_DEMUX_1_CFG_MIN            (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_REQ_MUX_DEMUX_1_CFG_MAX            (3) // 0x00000003
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_REQ_MUX_DEMUX_1_CFG_DEF            (0x00000002)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_REQ_MUX_DEMUX_1_CFG_HSH            (0x022B1094)

  #define CMF_TOPOLOGY_GLOBAL_CFG_3_REQ_MUX_DEMUX_0_CFG_OFF            (23)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_REQ_MUX_DEMUX_0_CFG_WID            ( 1)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_REQ_MUX_DEMUX_0_CFG_MSK            (0x00800000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_REQ_MUX_DEMUX_0_CFG_MIN            (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_REQ_MUX_DEMUX_0_CFG_MAX            (1) // 0x00000001
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_REQ_MUX_DEMUX_0_CFG_DEF            (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_REQ_MUX_DEMUX_0_CFG_HSH            (0x012F1094)

  #define CMF_TOPOLOGY_GLOBAL_CFG_3_Reserved_2_OFF                     (24)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_Reserved_2_WID                     ( 8)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_Reserved_2_MSK                     (0xFF000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_Reserved_2_MIN                     (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_Reserved_2_MAX                     (255) // 0x000000FF
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_Reserved_2_DEF                     (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_3_Reserved_2_HSH                     (0x08311094)

#define CMF_TOPOLOGY_GLOBAL_CFG_4_REG                                  (0x00011098)

  #define CMF_TOPOLOGY_GLOBAL_CFG_4_Reserved_0_OFF                     ( 0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_Reserved_0_WID                     (10)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_Reserved_0_MSK                     (0x000003FF)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_Reserved_0_MIN                     (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_Reserved_0_MAX                     (1023) // 0x000003FF
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_Reserved_0_DEF                     (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_Reserved_0_HSH                     (0x0A011098)

  #define CMF_TOPOLOGY_GLOBAL_CFG_4_AGENT_WR_RSP_OFF                   (10)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_AGENT_WR_RSP_WID                   ( 5)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_AGENT_WR_RSP_MSK                   (0x00007C00)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_AGENT_WR_RSP_MIN                   (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_AGENT_WR_RSP_MAX                   (31) // 0x0000001F
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_AGENT_WR_RSP_DEF                   (0x0000000C)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_AGENT_WR_RSP_HSH                   (0x05151098)

  #define CMF_TOPOLOGY_GLOBAL_CFG_4_Reserved_1_OFF                     (15)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_Reserved_1_WID                     ( 3)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_Reserved_1_MSK                     (0x00038000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_Reserved_1_MIN                     (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_Reserved_1_MAX                     (7) // 0x00000007
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_Reserved_1_DEF                     (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_Reserved_1_HSH                     (0x031F1098)

  #define CMF_TOPOLOGY_GLOBAL_CFG_4_CPL_MUX_DEMUX_3_CFG_OFF            (18)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_CPL_MUX_DEMUX_3_CFG_WID            ( 1)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_CPL_MUX_DEMUX_3_CFG_MSK            (0x00040000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_CPL_MUX_DEMUX_3_CFG_MIN            (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_CPL_MUX_DEMUX_3_CFG_MAX            (1) // 0x00000001
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_CPL_MUX_DEMUX_3_CFG_DEF            (0x00000001)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_CPL_MUX_DEMUX_3_CFG_HSH            (0x01251098)

  #define CMF_TOPOLOGY_GLOBAL_CFG_4_CPL_MUX_DEMUX_2_CFG_OFF            (19)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_CPL_MUX_DEMUX_2_CFG_WID            ( 2)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_CPL_MUX_DEMUX_2_CFG_MSK            (0x00180000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_CPL_MUX_DEMUX_2_CFG_MIN            (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_CPL_MUX_DEMUX_2_CFG_MAX            (3) // 0x00000003
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_CPL_MUX_DEMUX_2_CFG_DEF            (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_CPL_MUX_DEMUX_2_CFG_HSH            (0x02271098)

  #define CMF_TOPOLOGY_GLOBAL_CFG_4_REQ_MUX_DEMUX_1_CFG_OFF            (21)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_REQ_MUX_DEMUX_1_CFG_WID            ( 2)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_REQ_MUX_DEMUX_1_CFG_MSK            (0x00600000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_REQ_MUX_DEMUX_1_CFG_MIN            (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_REQ_MUX_DEMUX_1_CFG_MAX            (3) // 0x00000003
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_REQ_MUX_DEMUX_1_CFG_DEF            (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_REQ_MUX_DEMUX_1_CFG_HSH            (0x022B1098)

  #define CMF_TOPOLOGY_GLOBAL_CFG_4_REQ_MUX_DEMUX_0_CFG_OFF            (23)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_REQ_MUX_DEMUX_0_CFG_WID            ( 1)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_REQ_MUX_DEMUX_0_CFG_MSK            (0x00800000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_REQ_MUX_DEMUX_0_CFG_MIN            (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_REQ_MUX_DEMUX_0_CFG_MAX            (1) // 0x00000001
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_REQ_MUX_DEMUX_0_CFG_DEF            (0x00000001)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_REQ_MUX_DEMUX_0_CFG_HSH            (0x012F1098)

  #define CMF_TOPOLOGY_GLOBAL_CFG_4_Reserved_2_OFF                     (24)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_Reserved_2_WID                     ( 8)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_Reserved_2_MSK                     (0xFF000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_Reserved_2_MIN                     (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_Reserved_2_MAX                     (255) // 0x000000FF
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_Reserved_2_DEF                     (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_4_Reserved_2_HSH                     (0x08311098)

#define CMF_TOPOLOGY_GLOBAL_CFG_5_REG                                  (0x0001109C)

  #define CMF_TOPOLOGY_GLOBAL_CFG_5_Reserved_0_OFF                     ( 0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_Reserved_0_WID                     (10)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_Reserved_0_MSK                     (0x000003FF)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_Reserved_0_MIN                     (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_Reserved_0_MAX                     (1023) // 0x000003FF
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_Reserved_0_DEF                     (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_Reserved_0_HSH                     (0x0A01109C)

  #define CMF_TOPOLOGY_GLOBAL_CFG_5_AGENT_WR_RSP_OFF                   (10)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_AGENT_WR_RSP_WID                   ( 5)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_AGENT_WR_RSP_MSK                   (0x00007C00)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_AGENT_WR_RSP_MIN                   (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_AGENT_WR_RSP_MAX                   (31) // 0x0000001F
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_AGENT_WR_RSP_DEF                   (0x0000000C)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_AGENT_WR_RSP_HSH                   (0x0515109C)

  #define CMF_TOPOLOGY_GLOBAL_CFG_5_Reserved_1_OFF                     (15)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_Reserved_1_WID                     ( 3)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_Reserved_1_MSK                     (0x00038000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_Reserved_1_MIN                     (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_Reserved_1_MAX                     (7) // 0x00000007
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_Reserved_1_DEF                     (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_Reserved_1_HSH                     (0x031F109C)

  #define CMF_TOPOLOGY_GLOBAL_CFG_5_CPL_MUX_DEMUX_3_CFG_OFF            (18)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_CPL_MUX_DEMUX_3_CFG_WID            ( 1)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_CPL_MUX_DEMUX_3_CFG_MSK            (0x00040000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_CPL_MUX_DEMUX_3_CFG_MIN            (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_CPL_MUX_DEMUX_3_CFG_MAX            (1) // 0x00000001
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_CPL_MUX_DEMUX_3_CFG_DEF            (0x00000001)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_CPL_MUX_DEMUX_3_CFG_HSH            (0x0125109C)

  #define CMF_TOPOLOGY_GLOBAL_CFG_5_CPL_MUX_DEMUX_2_CFG_OFF            (19)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_CPL_MUX_DEMUX_2_CFG_WID            ( 2)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_CPL_MUX_DEMUX_2_CFG_MSK            (0x00180000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_CPL_MUX_DEMUX_2_CFG_MIN            (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_CPL_MUX_DEMUX_2_CFG_MAX            (3) // 0x00000003
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_CPL_MUX_DEMUX_2_CFG_DEF            (0x00000001)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_CPL_MUX_DEMUX_2_CFG_HSH            (0x0227109C)

  #define CMF_TOPOLOGY_GLOBAL_CFG_5_REQ_MUX_DEMUX_1_CFG_OFF            (21)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_REQ_MUX_DEMUX_1_CFG_WID            ( 2)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_REQ_MUX_DEMUX_1_CFG_MSK            (0x00600000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_REQ_MUX_DEMUX_1_CFG_MIN            (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_REQ_MUX_DEMUX_1_CFG_MAX            (3) // 0x00000003
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_REQ_MUX_DEMUX_1_CFG_DEF            (0x00000001)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_REQ_MUX_DEMUX_1_CFG_HSH            (0x022B109C)

  #define CMF_TOPOLOGY_GLOBAL_CFG_5_REQ_MUX_DEMUX_0_CFG_OFF            (23)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_REQ_MUX_DEMUX_0_CFG_WID            ( 1)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_REQ_MUX_DEMUX_0_CFG_MSK            (0x00800000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_REQ_MUX_DEMUX_0_CFG_MIN            (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_REQ_MUX_DEMUX_0_CFG_MAX            (1) // 0x00000001
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_REQ_MUX_DEMUX_0_CFG_DEF            (0x00000001)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_REQ_MUX_DEMUX_0_CFG_HSH            (0x012F109C)

  #define CMF_TOPOLOGY_GLOBAL_CFG_5_Reserved_2_OFF                     (24)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_Reserved_2_WID                     ( 8)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_Reserved_2_MSK                     (0xFF000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_Reserved_2_MIN                     (0)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_Reserved_2_MAX                     (255) // 0x000000FF
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_Reserved_2_DEF                     (0x00000000)
  #define CMF_TOPOLOGY_GLOBAL_CFG_5_Reserved_2_HSH                     (0x0831109C)

#define CMI_MAD_SLICE_REG                                              (0x000110A8)

  #define CMI_MAD_SLICE_Reserved_0_OFF                                 ( 0)
  #define CMI_MAD_SLICE_Reserved_0_WID                                 ( 4)
  #define CMI_MAD_SLICE_Reserved_0_MSK                                 (0x0000000F)
  #define CMI_MAD_SLICE_Reserved_0_MIN                                 (0)
  #define CMI_MAD_SLICE_Reserved_0_MAX                                 (15) // 0x0000000F
  #define CMI_MAD_SLICE_Reserved_0_DEF                                 (0x00000000)
  #define CMI_MAD_SLICE_Reserved_0_HSH                                 (0x040110A8)

  #define CMI_MAD_SLICE_MS_L_MAP_OFF                                   ( 4)
  #define CMI_MAD_SLICE_MS_L_MAP_WID                                   ( 1)
  #define CMI_MAD_SLICE_MS_L_MAP_MSK                                   (0x00000010)
  #define CMI_MAD_SLICE_MS_L_MAP_MIN                                   (0)
  #define CMI_MAD_SLICE_MS_L_MAP_MAX                                   (1) // 0x00000001
  #define CMI_MAD_SLICE_MS_L_MAP_DEF                                   (0x00000000)
  #define CMI_MAD_SLICE_MS_L_MAP_HSH                                   (0x010910A8)

  #define CMI_MAD_SLICE_Reserved_1_OFF                                 ( 5)
  #define CMI_MAD_SLICE_Reserved_1_WID                                 ( 3)
  #define CMI_MAD_SLICE_Reserved_1_MSK                                 (0x000000E0)
  #define CMI_MAD_SLICE_Reserved_1_MIN                                 (0)
  #define CMI_MAD_SLICE_Reserved_1_MAX                                 (7) // 0x00000007
  #define CMI_MAD_SLICE_Reserved_1_DEF                                 (0x00000000)
  #define CMI_MAD_SLICE_Reserved_1_HSH                                 (0x030B10A8)

  #define CMI_MAD_SLICE_STKD_MODE_OFF                                  ( 8)
  #define CMI_MAD_SLICE_STKD_MODE_WID                                  ( 1)
  #define CMI_MAD_SLICE_STKD_MODE_MSK                                  (0x00000100)
  #define CMI_MAD_SLICE_STKD_MODE_MIN                                  (0)
  #define CMI_MAD_SLICE_STKD_MODE_MAX                                  (1) // 0x00000001
  #define CMI_MAD_SLICE_STKD_MODE_DEF                                  (0x00000000)
  #define CMI_MAD_SLICE_STKD_MODE_HSH                                  (0x011110A8)

  #define CMI_MAD_SLICE_STKD_MODE_MS1_OFF                              ( 9)
  #define CMI_MAD_SLICE_STKD_MODE_MS1_WID                              ( 1)
  #define CMI_MAD_SLICE_STKD_MODE_MS1_MSK                              (0x00000200)
  #define CMI_MAD_SLICE_STKD_MODE_MS1_MIN                              (0)
  #define CMI_MAD_SLICE_STKD_MODE_MS1_MAX                              (1) // 0x00000001
  #define CMI_MAD_SLICE_STKD_MODE_MS1_DEF                              (0x00000000)
  #define CMI_MAD_SLICE_STKD_MODE_MS1_HSH                              (0x011310A8)

  #define CMI_MAD_SLICE_Reserved_2_OFF                                 (10)
  #define CMI_MAD_SLICE_Reserved_2_WID                                 ( 2)
  #define CMI_MAD_SLICE_Reserved_2_MSK                                 (0x00000C00)
  #define CMI_MAD_SLICE_Reserved_2_MIN                                 (0)
  #define CMI_MAD_SLICE_Reserved_2_MAX                                 (3) // 0x00000003
  #define CMI_MAD_SLICE_Reserved_2_DEF                                 (0x00000000)
  #define CMI_MAD_SLICE_Reserved_2_HSH                                 (0x021510A8)

  #define CMI_MAD_SLICE_MS_S_SIZE_OFF                                  (12)
  #define CMI_MAD_SLICE_MS_S_SIZE_WID                                  ( 8)
  #define CMI_MAD_SLICE_MS_S_SIZE_MSK                                  (0x000FF000)
  #define CMI_MAD_SLICE_MS_S_SIZE_MIN                                  (0)
  #define CMI_MAD_SLICE_MS_S_SIZE_MAX                                  (255) // 0x000000FF
  #define CMI_MAD_SLICE_MS_S_SIZE_DEF                                  (0x00000000)
  #define CMI_MAD_SLICE_MS_S_SIZE_HSH                                  (0x081910A8)

  #define CMI_MAD_SLICE_Reserved_3_OFF                                 (20)
  #define CMI_MAD_SLICE_Reserved_3_WID                                 ( 4)
  #define CMI_MAD_SLICE_Reserved_3_MSK                                 (0x00F00000)
  #define CMI_MAD_SLICE_Reserved_3_MIN                                 (0)
  #define CMI_MAD_SLICE_Reserved_3_MAX                                 (15) // 0x0000000F
  #define CMI_MAD_SLICE_Reserved_3_DEF                                 (0x00000000)
  #define CMI_MAD_SLICE_Reserved_3_HSH                                 (0x042910A8)

  #define CMI_MAD_SLICE_STKD_MODE_MS_BITS_OFF                          (24)
  #define CMI_MAD_SLICE_STKD_MODE_MS_BITS_WID                          ( 3)
  #define CMI_MAD_SLICE_STKD_MODE_MS_BITS_MSK                          (0x07000000)
  #define CMI_MAD_SLICE_STKD_MODE_MS_BITS_MIN                          (0)
  #define CMI_MAD_SLICE_STKD_MODE_MS_BITS_MAX                          (7) // 0x00000007
  #define CMI_MAD_SLICE_STKD_MODE_MS_BITS_DEF                          (0x00000000)
  #define CMI_MAD_SLICE_STKD_MODE_MS_BITS_HSH                          (0x033110A8)

  #define CMI_MAD_SLICE_Reserved_4_OFF                                 (27)
  #define CMI_MAD_SLICE_Reserved_4_WID                                 ( 5)
  #define CMI_MAD_SLICE_Reserved_4_MSK                                 (0xF8000000)
  #define CMI_MAD_SLICE_Reserved_4_MIN                                 (0)
  #define CMI_MAD_SLICE_Reserved_4_MAX                                 (31) // 0x0000001F
  #define CMI_MAD_SLICE_Reserved_4_DEF                                 (0x00000000)
  #define CMI_MAD_SLICE_Reserved_4_HSH                                 (0x053710A8)

#define CMI_MEMORY_SLICE_HASH_REG                                      (0x000110AC)

  #define CMI_MEMORY_SLICE_HASH_Reserved_0_OFF                         ( 0)
  #define CMI_MEMORY_SLICE_HASH_Reserved_0_WID                         ( 6)
  #define CMI_MEMORY_SLICE_HASH_Reserved_0_MSK                         (0x0000003F)
  #define CMI_MEMORY_SLICE_HASH_Reserved_0_MIN                         (0)
  #define CMI_MEMORY_SLICE_HASH_Reserved_0_MAX                         (63) // 0x0000003F
  #define CMI_MEMORY_SLICE_HASH_Reserved_0_DEF                         (0x00000000)
  #define CMI_MEMORY_SLICE_HASH_Reserved_0_HSH                         (0x060110AC)

  #define CMI_MEMORY_SLICE_HASH_HASH_MASK_OFF                          ( 6)
  #define CMI_MEMORY_SLICE_HASH_HASH_MASK_WID                          (14)
  #define CMI_MEMORY_SLICE_HASH_HASH_MASK_MSK                          (0x000FFFC0)
  #define CMI_MEMORY_SLICE_HASH_HASH_MASK_MIN                          (0)
  #define CMI_MEMORY_SLICE_HASH_HASH_MASK_MAX                          (16383) // 0x00003FFF
  #define CMI_MEMORY_SLICE_HASH_HASH_MASK_DEF                          (0x00000000)
  #define CMI_MEMORY_SLICE_HASH_HASH_MASK_HSH                          (0x0E0D10AC)

  #define CMI_MEMORY_SLICE_HASH_Reserved_1_OFF                         (20)
  #define CMI_MEMORY_SLICE_HASH_Reserved_1_WID                         ( 4)
  #define CMI_MEMORY_SLICE_HASH_Reserved_1_MSK                         (0x00F00000)
  #define CMI_MEMORY_SLICE_HASH_Reserved_1_MIN                         (0)
  #define CMI_MEMORY_SLICE_HASH_Reserved_1_MAX                         (15) // 0x0000000F
  #define CMI_MEMORY_SLICE_HASH_Reserved_1_DEF                         (0x00000000)
  #define CMI_MEMORY_SLICE_HASH_Reserved_1_HSH                         (0x042910AC)

  #define CMI_MEMORY_SLICE_HASH_HASH_LSB_MASK_BIT_OFF                  (24)
  #define CMI_MEMORY_SLICE_HASH_HASH_LSB_MASK_BIT_WID                  ( 3)
  #define CMI_MEMORY_SLICE_HASH_HASH_LSB_MASK_BIT_MSK                  (0x07000000)
  #define CMI_MEMORY_SLICE_HASH_HASH_LSB_MASK_BIT_MIN                  (0)
  #define CMI_MEMORY_SLICE_HASH_HASH_LSB_MASK_BIT_MAX                  (7) // 0x00000007
  #define CMI_MEMORY_SLICE_HASH_HASH_LSB_MASK_BIT_DEF                  (0x00000000)
  #define CMI_MEMORY_SLICE_HASH_HASH_LSB_MASK_BIT_HSH                  (0x033110AC)

  #define CMI_MEMORY_SLICE_HASH_Reserved_2_OFF                         (27)
  #define CMI_MEMORY_SLICE_HASH_Reserved_2_WID                         ( 1)
  #define CMI_MEMORY_SLICE_HASH_Reserved_2_MSK                         (0x08000000)
  #define CMI_MEMORY_SLICE_HASH_Reserved_2_MIN                         (0)
  #define CMI_MEMORY_SLICE_HASH_Reserved_2_MAX                         (1) // 0x00000001
  #define CMI_MEMORY_SLICE_HASH_Reserved_2_DEF                         (0x00000000)
  #define CMI_MEMORY_SLICE_HASH_Reserved_2_HSH                         (0x013710AC)

  #define CMI_MEMORY_SLICE_HASH_HASH_MODE_OFF                          (28)
  #define CMI_MEMORY_SLICE_HASH_HASH_MODE_WID                          ( 1)
  #define CMI_MEMORY_SLICE_HASH_HASH_MODE_MSK                          (0x10000000)
  #define CMI_MEMORY_SLICE_HASH_HASH_MODE_MIN                          (0)
  #define CMI_MEMORY_SLICE_HASH_HASH_MODE_MAX                          (1) // 0x00000001
  #define CMI_MEMORY_SLICE_HASH_HASH_MODE_DEF                          (0x00000000)
  #define CMI_MEMORY_SLICE_HASH_HASH_MODE_HSH                          (0x013910AC)

  #define CMI_MEMORY_SLICE_HASH_Reserved_3_OFF                         (29)
  #define CMI_MEMORY_SLICE_HASH_Reserved_3_WID                         ( 3)
  #define CMI_MEMORY_SLICE_HASH_Reserved_3_MSK                         (0xE0000000)
  #define CMI_MEMORY_SLICE_HASH_Reserved_3_MIN                         (0)
  #define CMI_MEMORY_SLICE_HASH_Reserved_3_MAX                         (7) // 0x00000007
  #define CMI_MEMORY_SLICE_HASH_Reserved_3_DEF                         (0x00000000)
  #define CMI_MEMORY_SLICE_HASH_Reserved_3_HSH                         (0x033B10AC)

#define CMI_REMAP_BASE_REG                                             (0x000110B0)

  #define CMI_REMAP_BASE_Reserved_0_OFF                                ( 0)
  #define CMI_REMAP_BASE_Reserved_0_WID                                (20)
  #define CMI_REMAP_BASE_Reserved_0_MSK                                (0x000FFFFF)
  #define CMI_REMAP_BASE_Reserved_0_MIN                                (0)
  #define CMI_REMAP_BASE_Reserved_0_MAX                                (1048575) // 0x000FFFFF
  #define CMI_REMAP_BASE_Reserved_0_DEF                                (0x00000000)
  #define CMI_REMAP_BASE_Reserved_0_HSH                                (0x540110B0)

  #define CMI_REMAP_BASE_REMAPBASE_OFF                                 (20)
  #define CMI_REMAP_BASE_REMAPBASE_WID                                 (19)
  #define CMI_REMAP_BASE_REMAPBASE_MSK                                 (0x0000007FFFF00000ULL)
  #define CMI_REMAP_BASE_REMAPBASE_MIN                                 (0)
  #define CMI_REMAP_BASE_REMAPBASE_MAX                                 (524287) // 0x0007FFFF
  #define CMI_REMAP_BASE_REMAPBASE_DEF                                 (0x0007FFFF)
  #define CMI_REMAP_BASE_REMAPBASE_HSH                                 (0x532910B0)

  #define CMI_REMAP_BASE_Reserved_1_OFF                                (39)
  #define CMI_REMAP_BASE_Reserved_1_WID                                (25)
  #define CMI_REMAP_BASE_Reserved_1_MSK                                (0xFFFFFF8000000000ULL)
  #define CMI_REMAP_BASE_Reserved_1_MIN                                (0)
  #define CMI_REMAP_BASE_Reserved_1_MAX                                (33554431) // 0x01FFFFFF
  #define CMI_REMAP_BASE_Reserved_1_DEF                                (0x00000000)
  #define CMI_REMAP_BASE_Reserved_1_HSH                                (0x594F10B0)

#define CMI_REMAP_LIMIT_REG                                            (0x000110B8)

  #define CMI_REMAP_LIMIT_Reserved_0_OFF                               ( 0)
  #define CMI_REMAP_LIMIT_Reserved_0_WID                               (20)
  #define CMI_REMAP_LIMIT_Reserved_0_MSK                               (0x000FFFFF)
  #define CMI_REMAP_LIMIT_Reserved_0_MIN                               (0)
  #define CMI_REMAP_LIMIT_Reserved_0_MAX                               (1048575) // 0x000FFFFF
  #define CMI_REMAP_LIMIT_Reserved_0_DEF                               (0x00000000)
  #define CMI_REMAP_LIMIT_Reserved_0_HSH                               (0x540110B8)

  #define CMI_REMAP_LIMIT_REMAPLMT_OFF                                 (20)
  #define CMI_REMAP_LIMIT_REMAPLMT_WID                                 (19)
  #define CMI_REMAP_LIMIT_REMAPLMT_MSK                                 (0x0000007FFFF00000ULL)
  #define CMI_REMAP_LIMIT_REMAPLMT_MIN                                 (0)
  #define CMI_REMAP_LIMIT_REMAPLMT_MAX                                 (524287) // 0x0007FFFF
  #define CMI_REMAP_LIMIT_REMAPLMT_DEF                                 (0x00000000)
  #define CMI_REMAP_LIMIT_REMAPLMT_HSH                                 (0x532910B8)

  #define CMI_REMAP_LIMIT_Reserved_1_OFF                               (39)
  #define CMI_REMAP_LIMIT_Reserved_1_WID                               (25)
  #define CMI_REMAP_LIMIT_Reserved_1_MSK                               (0xFFFFFF8000000000ULL)
  #define CMI_REMAP_LIMIT_Reserved_1_MIN                               (0)
  #define CMI_REMAP_LIMIT_Reserved_1_MAX                               (33554431) // 0x01FFFFFF
  #define CMI_REMAP_LIMIT_Reserved_1_DEF                               (0x00000000)
  #define CMI_REMAP_LIMIT_Reserved_1_HSH                               (0x594F10B8)

#define CMI_TOLUD_REG                                                  (0x000110C0)

  #define CMI_TOLUD_Reserved_OFF                                       ( 0)
  #define CMI_TOLUD_Reserved_WID                                       (20)
  #define CMI_TOLUD_Reserved_MSK                                       (0x000FFFFF)
  #define CMI_TOLUD_Reserved_MIN                                       (0)
  #define CMI_TOLUD_Reserved_MAX                                       (1048575) // 0x000FFFFF
  #define CMI_TOLUD_Reserved_DEF                                       (0x00000000)
  #define CMI_TOLUD_Reserved_HSH                                       (0x140110C0)

  #define CMI_TOLUD_TOLUD_OFF                                          (20)
  #define CMI_TOLUD_TOLUD_WID                                          (12)
  #define CMI_TOLUD_TOLUD_MSK                                          (0xFFF00000)
  #define CMI_TOLUD_TOLUD_MIN                                          (0)
  #define CMI_TOLUD_TOLUD_MAX                                          (4095) // 0x00000FFF
  #define CMI_TOLUD_TOLUD_DEF                                          (0x00000001)
  #define CMI_TOLUD_TOLUD_HSH                                          (0x0C2910C0)

#define CMI_MAD_SLICE_NM_P0_REG                                        (0x000110C4)
//Duplicate of CMI_MAD_SLICE_P0_REG

#define CMI_MEMORY_SLICE_HASH_NM_P0_REG                                (0x000110C8)
//Duplicate of CMI_MEMORY_SLICE_HASH_P0_REG

#define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REG                  (0x000110D0)

  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_OFF ( 0)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_WID ( 4)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_MSK (0x0000000F)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_MIN (0)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_MAX (15) // 0x0000000F
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_DEF (0x00000003)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_HSH (0x040110D0)

  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_RESERVED0_OFF      ( 4)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_RESERVED0_WID      ( 4)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_RESERVED0_MSK      (0x000000F0)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_RESERVED0_MIN      (0)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_RESERVED0_MAX      (15) // 0x0000000F
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_RESERVED0_DEF      (0x00000000)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_RESERVED0_HSH      (0x040910D0)

  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_OFF ( 8)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_WID ( 4)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_MSK (0x00000F00)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_MIN (0)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_MAX (15) // 0x0000000F
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_DEF (0x00000003)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_HSH (0x041110D0)

  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_RESERVED1_OFF      (12)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_RESERVED1_WID      ( 4)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_RESERVED1_MSK      (0x0000F000)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_RESERVED1_MIN      (0)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_RESERVED1_MAX      (15) // 0x0000000F
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_RESERVED1_DEF      (0x00000000)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_RESERVED1_HSH      (0x041910D0)

  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_OFF (16)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_WID ( 8)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_MSK (0x00FF0000)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_MIN (0)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_MAX (255) // 0x000000FF
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_DEF (0x00000005)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_HSH (0x082110D0)

  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_OFF (24)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_WID ( 8)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_MSK (0xFF000000)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_MIN (0)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_MAX (255) // 0x000000FF
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_DEF (0x00000008)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_HSH (0x083110D0)

#define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REG                  (0x000110D4)

  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_OFF ( 0)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_WID ( 4)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_MSK (0x0000000F)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_MIN (0)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_MAX (15) // 0x0000000F
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_DEF (0x00000003)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_HSH (0x040110D4)

  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_RESERVED0_OFF      ( 4)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_RESERVED0_WID      ( 4)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_RESERVED0_MSK      (0x000000F0)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_RESERVED0_MIN      (0)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_RESERVED0_MAX      (15) // 0x0000000F
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_RESERVED0_DEF      (0x00000000)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_RESERVED0_HSH      (0x040910D4)

  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_OFF ( 8)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_WID ( 4)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_MSK (0x00000F00)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_MIN (0)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_MAX (15) // 0x0000000F
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_DEF (0x00000003)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_HSH (0x041110D4)

  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_RESERVED1_OFF      (12)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_RESERVED1_WID      ( 4)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_RESERVED1_MSK      (0x0000F000)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_RESERVED1_MIN      (0)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_RESERVED1_MAX      (15) // 0x0000000F
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_RESERVED1_DEF      (0x00000000)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_RESERVED1_HSH      (0x041910D4)

  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_OFF (16)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_WID ( 8)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_MSK (0x00FF0000)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_MIN (0)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_MAX (255) // 0x000000FF
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_DEF (0x00000000)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_HSH (0x082110D4)

  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_OFF (24)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_WID ( 8)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_MSK (0xFF000000)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_MIN (0)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_MAX (255) // 0x000000FF
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_DEF (0x00000000)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_HSH (0x083110D4)

#define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REG                  (0x000110D8)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REG

#define CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REG                  (0x000110DC)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REG

#define CMI_REQUEST_PORT_0_REQ_CONFIG_1_REG                            (0x000110E0)

  #define CMI_REQUEST_PORT_0_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_OFF        ( 0)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_WID        ( 8)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_MSK        (0x000000FF)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_MIN        (0)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_MAX        (255) // 0x000000FF
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_DEF        (0x00000005)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_HSH        (0x080110E0)

  #define CMI_REQUEST_PORT_0_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_OFF        ( 8)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_WID        ( 8)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_MSK        (0x0000FF00)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_MIN        (0)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_MAX        (255) // 0x000000FF
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_DEF        (0x00000008)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_HSH        (0x081110E0)

  #define CMI_REQUEST_PORT_0_REQ_CONFIG_1_RESERVED1_OFF                (16)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_1_RESERVED1_WID                (16)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_1_RESERVED1_MSK                (0xFFFF0000)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_1_RESERVED1_MIN                (0)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_1_RESERVED1_MAX                (65535) // 0x0000FFFF
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_1_RESERVED1_DEF                (0x00000000)
  #define CMI_REQUEST_PORT_0_REQ_CONFIG_1_RESERVED1_HSH                (0x102110E0)

#define CMI_REQUEST_PORT_0_STALL_REG                                   (0x000110E4)

  #define CMI_REQUEST_PORT_0_STALL_REQ_STALL_OFF                       ( 0)
  #define CMI_REQUEST_PORT_0_STALL_REQ_STALL_WID                       ( 1)
  #define CMI_REQUEST_PORT_0_STALL_REQ_STALL_MSK                       (0x00000001)
  #define CMI_REQUEST_PORT_0_STALL_REQ_STALL_MIN                       (0)
  #define CMI_REQUEST_PORT_0_STALL_REQ_STALL_MAX                       (1) // 0x00000001
  #define CMI_REQUEST_PORT_0_STALL_REQ_STALL_DEF                       (0x00000000)
  #define CMI_REQUEST_PORT_0_STALL_REQ_STALL_HSH                       (0x010110E4)

  #define CMI_REQUEST_PORT_0_STALL_RSVD0_OFF                           ( 1)
  #define CMI_REQUEST_PORT_0_STALL_RSVD0_WID                           ( 4)
  #define CMI_REQUEST_PORT_0_STALL_RSVD0_MSK                           (0x0000001E)
  #define CMI_REQUEST_PORT_0_STALL_RSVD0_MIN                           (0)
  #define CMI_REQUEST_PORT_0_STALL_RSVD0_MAX                           (15) // 0x0000000F
  #define CMI_REQUEST_PORT_0_STALL_RSVD0_DEF                           (0x00000000)
  #define CMI_REQUEST_PORT_0_STALL_RSVD0_HSH                           (0x040310E4)

  #define CMI_REQUEST_PORT_0_STALL_RSVD1_OFF                           ( 5)
  #define CMI_REQUEST_PORT_0_STALL_RSVD1_WID                           ( 3)
  #define CMI_REQUEST_PORT_0_STALL_RSVD1_MSK                           (0x000000E0)
  #define CMI_REQUEST_PORT_0_STALL_RSVD1_MIN                           (0)
  #define CMI_REQUEST_PORT_0_STALL_RSVD1_MAX                           (7) // 0x00000007
  #define CMI_REQUEST_PORT_0_STALL_RSVD1_DEF                           (0x00000000)
  #define CMI_REQUEST_PORT_0_STALL_RSVD1_HSH                           (0x030B10E4)

  #define CMI_REQUEST_PORT_0_STALL_UNSTALL_COUNTER_VALUE_OFF           ( 8)
  #define CMI_REQUEST_PORT_0_STALL_UNSTALL_COUNTER_VALUE_WID           (16)
  #define CMI_REQUEST_PORT_0_STALL_UNSTALL_COUNTER_VALUE_MSK           (0x00FFFF00)
  #define CMI_REQUEST_PORT_0_STALL_UNSTALL_COUNTER_VALUE_MIN           (0)
  #define CMI_REQUEST_PORT_0_STALL_UNSTALL_COUNTER_VALUE_MAX           (65535) // 0x0000FFFF
  #define CMI_REQUEST_PORT_0_STALL_UNSTALL_COUNTER_VALUE_DEF           (0x00000000)
  #define CMI_REQUEST_PORT_0_STALL_UNSTALL_COUNTER_VALUE_HSH           (0x101110E4)

  #define CMI_REQUEST_PORT_0_STALL_RSVD2_OFF                           (24)
  #define CMI_REQUEST_PORT_0_STALL_RSVD2_WID                           ( 8)
  #define CMI_REQUEST_PORT_0_STALL_RSVD2_MSK                           (0xFF000000)
  #define CMI_REQUEST_PORT_0_STALL_RSVD2_MIN                           (0)
  #define CMI_REQUEST_PORT_0_STALL_RSVD2_MAX                           (255) // 0x000000FF
  #define CMI_REQUEST_PORT_0_STALL_RSVD2_DEF                           (0x00000000)
  #define CMI_REQUEST_PORT_0_STALL_RSVD2_HSH                           (0x083110E4)

#define CMI_REQUEST_PORT_0_RESERVED_0_REG                              (0x000110E8)
//Duplicate of CMF_RSVD0_REG

#define CMI_REQUEST_PORT_0_RESERVED_1_REG                              (0x000110EC)
//Duplicate of CMF_RSVD0_REG

#define CMI_REQUEST_PORT_0_RESERVED_2_REG                              (0x000110F0)
//Duplicate of CMF_RSVD0_REG

#define CMI_REQUEST_PORT_0_ACCUM_REQ_IN_REG                            (0x000110F4)

  #define CMI_REQUEST_PORT_0_ACCUM_REQ_IN_REQ_CMD_SUM_OFF              ( 0)
  #define CMI_REQUEST_PORT_0_ACCUM_REQ_IN_REQ_CMD_SUM_WID              (16)
  #define CMI_REQUEST_PORT_0_ACCUM_REQ_IN_REQ_CMD_SUM_MSK              (0x0000FFFF)
  #define CMI_REQUEST_PORT_0_ACCUM_REQ_IN_REQ_CMD_SUM_MIN              (0)
  #define CMI_REQUEST_PORT_0_ACCUM_REQ_IN_REQ_CMD_SUM_MAX              (65535) // 0x0000FFFF
  #define CMI_REQUEST_PORT_0_ACCUM_REQ_IN_REQ_CMD_SUM_DEF              (0x00000000)
  #define CMI_REQUEST_PORT_0_ACCUM_REQ_IN_REQ_CMD_SUM_HSH              (0x100110F4)

  #define CMI_REQUEST_PORT_0_ACCUM_REQ_IN_REQ_DATA_SUM_OFF             (16)
  #define CMI_REQUEST_PORT_0_ACCUM_REQ_IN_REQ_DATA_SUM_WID             (16)
  #define CMI_REQUEST_PORT_0_ACCUM_REQ_IN_REQ_DATA_SUM_MSK             (0xFFFF0000)
  #define CMI_REQUEST_PORT_0_ACCUM_REQ_IN_REQ_DATA_SUM_MIN             (0)
  #define CMI_REQUEST_PORT_0_ACCUM_REQ_IN_REQ_DATA_SUM_MAX             (65535) // 0x0000FFFF
  #define CMI_REQUEST_PORT_0_ACCUM_REQ_IN_REQ_DATA_SUM_DEF             (0x00000000)
  #define CMI_REQUEST_PORT_0_ACCUM_REQ_IN_REQ_DATA_SUM_HSH             (0x102110F4)

#define CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_REG                        (0x000110F8)

  #define CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_OFF       ( 0)
  #define CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_WID       (16)
  #define CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_MSK       (0x0000FFFF)
  #define CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_MIN       (0)
  #define CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_MAX       (65535) // 0x0000FFFF
  #define CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_DEF       (0x00000000)
  #define CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_HSH       (0x100110F8)

  #define CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_OFF      (16)
  #define CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_WID      (16)
  #define CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_MSK      (0xFFFF0000)
  #define CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_MIN      (0)
  #define CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_MAX      (65535) // 0x0000FFFF
  #define CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_DEF      (0x00000000)
  #define CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_HSH      (0x102110F8)

#define CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_REG                           (0x000110FC)

  #define CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_RSP_CMD_SUM_OFF             ( 0)
  #define CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_RSP_CMD_SUM_WID             (16)
  #define CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_RSP_CMD_SUM_MSK             (0x0000FFFF)
  #define CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_RSP_CMD_SUM_MIN             (0)
  #define CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_RSP_CMD_SUM_MAX             (65535) // 0x0000FFFF
  #define CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_RSP_CMD_SUM_DEF             (0x00000000)
  #define CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_RSP_CMD_SUM_HSH             (0x100110FC)

  #define CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_RSVD_OFF                    (16)
  #define CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_RSVD_WID                    (16)
  #define CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_RSVD_MSK                    (0xFFFF0000)
  #define CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_RSVD_MIN                    (0)
  #define CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_RSVD_MAX                    (65535) // 0x0000FFFF
  #define CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_RSVD_DEF                    (0x00000000)
  #define CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_RSVD_HSH                    (0x102110FC)

#define CMI_REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REG                  (0x00011100)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REG

#define CMI_REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REG                  (0x00011104)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REG

#define CMI_REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REG                  (0x00011108)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REG

#define CMI_REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REG                  (0x0001110C)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REG

#define CMI_REQUEST_PORT_1_REQ_CONFIG_1_REG                            (0x00011110)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_1_REG

#define CMI_REQUEST_PORT_1_STALL_REG                                   (0x00011114)
//Duplicate of CMI_REQUEST_PORT_0_STALL_REG

#define CMI_REQUEST_PORT_1_RESERVED_0_REG                              (0x00011118)
//Duplicate of CMF_RSVD0_REG

#define CMI_REQUEST_PORT_1_RESERVED_1_REG                              (0x0001111C)
//Duplicate of CMF_RSVD0_REG

#define CMI_REQUEST_PORT_1_RESERVED_2_REG                              (0x00011120)
//Duplicate of CMF_RSVD0_REG

#define CMI_REQUEST_PORT_1_ACCUM_REQ_IN_REG                            (0x00011124)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_REQ_IN_REG

#define CMI_REQUEST_PORT_1_ACCUM_RD_CPL_OUT_REG                        (0x00011128)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_REG

#define CMI_REQUEST_PORT_1_ACCUM_RSP_OUT_REG                           (0x0001112C)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_REG

#define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REG                  (0x00011130)

  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_OFF ( 0)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_WID ( 4)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_MSK (0x0000000F)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_MIN (0)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_MAX (15) // 0x0000000F
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_DEF (0x00000003)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_HSH (0x04011130)

  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_RESERVED0_OFF      ( 4)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_RESERVED0_WID      ( 4)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_RESERVED0_MSK      (0x000000F0)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_RESERVED0_MIN      (0)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_RESERVED0_MAX      (15) // 0x0000000F
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_RESERVED0_DEF      (0x00000000)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_RESERVED0_HSH      (0x04091130)

  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_OFF ( 8)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_WID ( 4)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_MSK (0x00000F00)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_MIN (0)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_MAX (15) // 0x0000000F
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_DEF (0x00000003)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_HSH (0x04111130)

  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_RESERVED1_OFF      (12)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_RESERVED1_WID      ( 4)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_RESERVED1_MSK      (0x0000F000)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_RESERVED1_MIN      (0)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_RESERVED1_MAX      (15) // 0x0000000F
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_RESERVED1_DEF      (0x00000000)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_RESERVED1_HSH      (0x04191130)

  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_OFF (16)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_WID ( 8)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_MSK (0x00FF0000)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_MIN (0)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_MAX (255) // 0x000000FF
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_DEF (0x00000009)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_HSH (0x08211130)

  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_OFF (24)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_WID ( 8)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_MSK (0xFF000000)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_MIN (0)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_MAX (255) // 0x000000FF
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_DEF (0x0000000A)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_HSH (0x08311130)

#define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REG                  (0x00011134)
//Duplicate of CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REG

#define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REG                  (0x00011138)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REG

#define CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REG                  (0x0001113C)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REG

#define CMI_REQUEST_PORT_2_REQ_CONFIG_1_REG                            (0x00011140)

  #define CMI_REQUEST_PORT_2_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_OFF        ( 0)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_WID        ( 8)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_MSK        (0x000000FF)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_MIN        (0)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_MAX        (255) // 0x000000FF
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_DEF        (0x00000012)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_HSH        (0x08011140)

  #define CMI_REQUEST_PORT_2_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_OFF        ( 8)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_WID        ( 8)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_MSK        (0x0000FF00)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_MIN        (0)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_MAX        (255) // 0x000000FF
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_DEF        (0x00000014)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_HSH        (0x08111140)

  #define CMI_REQUEST_PORT_2_REQ_CONFIG_1_RESERVED1_OFF                (16)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_1_RESERVED1_WID                (16)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_1_RESERVED1_MSK                (0xFFFF0000)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_1_RESERVED1_MIN                (0)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_1_RESERVED1_MAX                (65535) // 0x0000FFFF
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_1_RESERVED1_DEF                (0x00000000)
  #define CMI_REQUEST_PORT_2_REQ_CONFIG_1_RESERVED1_HSH                (0x10211140)

#define CMI_REQUEST_PORT_2_STALL_REG                                   (0x00011144)
//Duplicate of CMI_REQUEST_PORT_0_STALL_REG

#define CMI_REQUEST_PORT_2_RESERVED_0_REG                              (0x00011148)
//Duplicate of CMF_RSVD0_REG

#define CMI_REQUEST_PORT_2_RESERVED_1_REG                              (0x0001114C)
//Duplicate of CMF_RSVD0_REG

#define CMI_REQUEST_PORT_2_RESERVED_2_REG                              (0x00011150)
//Duplicate of CMF_RSVD0_REG

#define CMI_REQUEST_PORT_2_ACCUM_REQ_IN_REG                            (0x00011154)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_REQ_IN_REG

#define CMI_REQUEST_PORT_2_ACCUM_RD_CPL_OUT_REG                        (0x00011158)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_REG

#define CMI_REQUEST_PORT_2_ACCUM_RSP_OUT_REG                           (0x0001115C)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_REG

#define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REG                  (0x00011160)

  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_OFF ( 0)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_WID ( 4)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_MSK (0x0000000F)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_MIN (0)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_MAX (15) // 0x0000000F
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_DEF (0x00000003)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_HSH (0x04011160)

  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_RESERVED0_OFF      ( 4)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_RESERVED0_WID      ( 4)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_RESERVED0_MSK      (0x000000F0)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_RESERVED0_MIN      (0)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_RESERVED0_MAX      (15) // 0x0000000F
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_RESERVED0_DEF      (0x00000000)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_RESERVED0_HSH      (0x04091160)

  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_OFF ( 8)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_WID ( 4)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_MSK (0x00000F00)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_MIN (0)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_MAX (15) // 0x0000000F
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_DEF (0x00000003)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_HSH (0x04111160)

  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_RESERVED1_OFF      (12)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_RESERVED1_WID      ( 4)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_RESERVED1_MSK      (0x0000F000)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_RESERVED1_MIN      (0)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_RESERVED1_MAX      (15) // 0x0000000F
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_RESERVED1_DEF      (0x00000000)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_RESERVED1_HSH      (0x04191160)

  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_OFF (16)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_WID ( 8)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_MSK (0x00FF0000)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_MIN (0)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_MAX (255) // 0x000000FF
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_DEF (0x00000009)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_HSH (0x08211160)

  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_OFF (24)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_WID ( 8)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_MSK (0xFF000000)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_MIN (0)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_MAX (255) // 0x000000FF
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_DEF (0x00000009)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_HSH (0x08311160)

#define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REG                  (0x00011164)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REG

#define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REG                  (0x00011168)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REG

#define CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REG                  (0x0001116C)
//Duplicate of CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REG

#define CMI_REQUEST_PORT_3_REQ_CONFIG_1_REG                            (0x00011170)

  #define CMI_REQUEST_PORT_3_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_OFF        ( 0)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_WID        ( 8)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_MSK        (0x000000FF)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_MIN        (0)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_MAX        (255) // 0x000000FF
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_DEF        (0x00000012)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_HSH        (0x08011170)

  #define CMI_REQUEST_PORT_3_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_OFF        ( 8)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_WID        ( 8)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_MSK        (0x0000FF00)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_MIN        (0)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_MAX        (255) // 0x000000FF
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_DEF        (0x00000012)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_HSH        (0x08111170)

  #define CMI_REQUEST_PORT_3_REQ_CONFIG_1_RESERVED1_OFF                (16)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_1_RESERVED1_WID                (16)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_1_RESERVED1_MSK                (0xFFFF0000)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_1_RESERVED1_MIN                (0)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_1_RESERVED1_MAX                (65535) // 0x0000FFFF
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_1_RESERVED1_DEF                (0x00000000)
  #define CMI_REQUEST_PORT_3_REQ_CONFIG_1_RESERVED1_HSH                (0x10211170)

#define CMI_REQUEST_PORT_3_STALL_REG                                   (0x00011174)
//Duplicate of CMI_REQUEST_PORT_0_STALL_REG

#define CMI_REQUEST_PORT_3_RESERVED_0_REG                              (0x00011178)
//Duplicate of CMF_RSVD0_REG

#define CMI_REQUEST_PORT_3_RESERVED_1_REG                              (0x0001117C)
//Duplicate of CMF_RSVD0_REG

#define CMI_REQUEST_PORT_3_RESERVED_2_REG                              (0x00011180)
//Duplicate of CMF_RSVD0_REG

#define CMI_REQUEST_PORT_3_ACCUM_REQ_IN_REG                            (0x00011184)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_REQ_IN_REG

#define CMI_REQUEST_PORT_3_ACCUM_RD_CPL_OUT_REG                        (0x00011188)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_REG

#define CMI_REQUEST_PORT_3_ACCUM_RSP_OUT_REG                           (0x0001118C)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_REG

#define CMI_REQUEST_PORT_4_REQ_CONFIG_0_CHANNEL_0_REG                  (0x00011190)
//Duplicate of CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REG

#define CMI_REQUEST_PORT_4_REQ_CONFIG_0_CHANNEL_1_REG                  (0x00011194)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REG

#define CMI_REQUEST_PORT_4_REQ_CONFIG_0_CHANNEL_2_REG                  (0x00011198)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REG

#define CMI_REQUEST_PORT_4_REQ_CONFIG_0_CHANNEL_3_REG                  (0x0001119C)
//Duplicate of CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REG

#define CMI_REQUEST_PORT_4_REQ_CONFIG_1_REG                            (0x000111A0)
//Duplicate of CMI_REQUEST_PORT_3_REQ_CONFIG_1_REG

#define CMI_REQUEST_PORT_4_STALL_REG                                   (0x000111A4)
//Duplicate of CMI_REQUEST_PORT_0_STALL_REG

#define CMI_REQUEST_PORT_4_RESERVED_0_REG                              (0x000111A8)
//Duplicate of CMF_RSVD0_REG

#define CMI_REQUEST_PORT_4_RESERVED_1_REG                              (0x000111AC)
//Duplicate of CMF_RSVD0_REG

#define CMI_REQUEST_PORT_4_RESERVED_2_REG                              (0x000111B0)
//Duplicate of CMF_RSVD0_REG

#define CMI_REQUEST_PORT_4_ACCUM_REQ_IN_REG                            (0x000111B4)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_REQ_IN_REG

#define CMI_REQUEST_PORT_4_ACCUM_RD_CPL_OUT_REG                        (0x000111B8)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_REG

#define CMI_REQUEST_PORT_4_ACCUM_RSP_OUT_REG                           (0x000111BC)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_REG

#define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_REG                  (0x00011280)

  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_WR_RSP_PARK_SIZE_OFF ( 0)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_WR_RSP_PARK_SIZE_WID ( 4)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_WR_RSP_PARK_SIZE_MSK (0x0000000F)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_WR_RSP_PARK_SIZE_MIN (0)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_WR_RSP_PARK_SIZE_MAX (15) // 0x0000000F
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_WR_RSP_PARK_SIZE_DEF (0x00000003)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_WR_RSP_PARK_SIZE_HSH (0x04011280)

  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED0_OFF      ( 4)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED0_WID      ( 4)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED0_MSK      (0x000000F0)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED0_MIN      (0)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED0_MAX      (15) // 0x0000000F
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED0_DEF      (0x00000000)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED0_HSH      (0x04091280)

  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_OFF ( 8)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_WID ( 4)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_MSK (0x00000F00)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_MIN (0)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_MAX (15) // 0x0000000F
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_DEF (0x00000003)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_HSH (0x04111280)

  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED1_OFF      (12)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED1_WID      ( 4)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED1_MSK      (0x0000F000)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED1_MIN      (0)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED1_MAX      (15) // 0x0000000F
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED1_DEF      (0x00000000)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED1_HSH      (0x04191280)

  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_OFF (16)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_WID ( 8)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_MSK (0x00FF0000)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_MIN (0)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_MAX (255) // 0x000000FF
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_DEF (0x00000000)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_HSH (0x08211280)

  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_OFF (24)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_WID ( 8)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_MSK (0xFF000000)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_MIN (0)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_MAX (255) // 0x000000FF
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_DEF (0x00000000)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_HSH (0x08311280)

#define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_REG                  (0x00011284)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_REG

#define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_REG                  (0x00011288)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_REG

#define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_REG                  (0x0001128C)

  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_WR_RSP_PARK_SIZE_OFF ( 0)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_WR_RSP_PARK_SIZE_WID ( 4)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_WR_RSP_PARK_SIZE_MSK (0x0000000F)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_WR_RSP_PARK_SIZE_MIN (0)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_WR_RSP_PARK_SIZE_MAX (15) // 0x0000000F
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_WR_RSP_PARK_SIZE_DEF (0x00000003)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_WR_RSP_PARK_SIZE_HSH (0x0401128C)

  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED0_OFF      ( 4)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED0_WID      ( 4)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED0_MSK      (0x000000F0)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED0_MIN      (0)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED0_MAX      (15) // 0x0000000F
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED0_DEF      (0x00000000)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED0_HSH      (0x0409128C)

  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_OFF ( 8)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_WID ( 4)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_MSK (0x00000F00)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_MIN (0)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_MAX (15) // 0x0000000F
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_DEF (0x00000003)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_HSH (0x0411128C)

  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED1_OFF      (12)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED1_WID      ( 4)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED1_MSK      (0x0000F000)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED1_MIN      (0)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED1_MAX      (15) // 0x0000000F
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED1_DEF      (0x00000000)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED1_HSH      (0x0419128C)

  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_OFF (16)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_WID ( 8)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_MSK (0x00FF0000)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_MIN (0)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_MAX (255) // 0x000000FF
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_DEF (0x00000005)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_HSH (0x0821128C)

  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_OFF (24)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_WID ( 8)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_MSK (0xFF000000)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_MIN (0)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_MAX (255) // 0x000000FF
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_DEF (0x00000006)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_HSH (0x0831128C)

#define CMI_RESPOND_PORT_0_CPL_CONFIG_1_REG                            (0x00011290)

  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_OFF        ( 0)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_WID        ( 8)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_MSK        (0x000000FF)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_MIN        (0)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_MAX        (255) // 0x000000FF
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_DEF        (0x00000006)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_HSH        (0x08011290)

  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_RSP_QUEUEDEPTH_OFF           ( 8)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_RSP_QUEUEDEPTH_WID           ( 8)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_RSP_QUEUEDEPTH_MSK           (0x0000FF00)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_RSP_QUEUEDEPTH_MIN           (0)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_RSP_QUEUEDEPTH_MAX           (255) // 0x000000FF
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_RSP_QUEUEDEPTH_DEF           (0x00000005)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_RSP_QUEUEDEPTH_HSH           (0x08111290)

  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_REQ_FAST_WAKE_OFF            (16)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_REQ_FAST_WAKE_WID            ( 1)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_REQ_FAST_WAKE_MSK            (0x00010000)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_REQ_FAST_WAKE_MIN            (0)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_REQ_FAST_WAKE_MAX            (1) // 0x00000001
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_REQ_FAST_WAKE_DEF            (0x00000000)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_REQ_FAST_WAKE_HSH            (0x01211290)

  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_RESERVED1_OFF                (17)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_RESERVED1_WID                (15)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_RESERVED1_MSK                (0xFFFE0000)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_RESERVED1_MIN                (0)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_RESERVED1_MAX                (32767) // 0x00007FFF
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_RESERVED1_DEF                (0x00000000)
  #define CMI_RESPOND_PORT_0_CPL_CONFIG_1_RESERVED1_HSH                (0x0F231290)

#define CMI_RESPOND_PORT_0_STALL_REG                                   (0x00011294)

  #define CMI_RESPOND_PORT_0_STALL_RSVD0_OFF                           ( 0)
  #define CMI_RESPOND_PORT_0_STALL_RSVD0_WID                           ( 4)
  #define CMI_RESPOND_PORT_0_STALL_RSVD0_MSK                           (0x0000000F)
  #define CMI_RESPOND_PORT_0_STALL_RSVD0_MIN                           (0)
  #define CMI_RESPOND_PORT_0_STALL_RSVD0_MAX                           (15) // 0x0000000F
  #define CMI_RESPOND_PORT_0_STALL_RSVD0_DEF                           (0x00000000)
  #define CMI_RESPOND_PORT_0_STALL_RSVD0_HSH                           (0x04011294)

  #define CMI_RESPOND_PORT_0_STALL_RSP_RD_CPL_STALL_OFF                ( 4)
  #define CMI_RESPOND_PORT_0_STALL_RSP_RD_CPL_STALL_WID                ( 1)
  #define CMI_RESPOND_PORT_0_STALL_RSP_RD_CPL_STALL_MSK                (0x00000010)
  #define CMI_RESPOND_PORT_0_STALL_RSP_RD_CPL_STALL_MIN                (0)
  #define CMI_RESPOND_PORT_0_STALL_RSP_RD_CPL_STALL_MAX                (1) // 0x00000001
  #define CMI_RESPOND_PORT_0_STALL_RSP_RD_CPL_STALL_DEF                (0x00000000)
  #define CMI_RESPOND_PORT_0_STALL_RSP_RD_CPL_STALL_HSH                (0x01091294)

  #define CMI_RESPOND_PORT_0_STALL_RSVD1_OFF                           ( 5)
  #define CMI_RESPOND_PORT_0_STALL_RSVD1_WID                           ( 3)
  #define CMI_RESPOND_PORT_0_STALL_RSVD1_MSK                           (0x000000E0)
  #define CMI_RESPOND_PORT_0_STALL_RSVD1_MIN                           (0)
  #define CMI_RESPOND_PORT_0_STALL_RSVD1_MAX                           (7) // 0x00000007
  #define CMI_RESPOND_PORT_0_STALL_RSVD1_DEF                           (0x00000000)
  #define CMI_RESPOND_PORT_0_STALL_RSVD1_HSH                           (0x030B1294)

  #define CMI_RESPOND_PORT_0_STALL_UNSTALL_COUNTER_VALUE_OFF           ( 8)
  #define CMI_RESPOND_PORT_0_STALL_UNSTALL_COUNTER_VALUE_WID           (16)
  #define CMI_RESPOND_PORT_0_STALL_UNSTALL_COUNTER_VALUE_MSK           (0x00FFFF00)
  #define CMI_RESPOND_PORT_0_STALL_UNSTALL_COUNTER_VALUE_MIN           (0)
  #define CMI_RESPOND_PORT_0_STALL_UNSTALL_COUNTER_VALUE_MAX           (65535) // 0x0000FFFF
  #define CMI_RESPOND_PORT_0_STALL_UNSTALL_COUNTER_VALUE_DEF           (0x00000000)
  #define CMI_RESPOND_PORT_0_STALL_UNSTALL_COUNTER_VALUE_HSH           (0x10111294)

  #define CMI_RESPOND_PORT_0_STALL_RSVD2_OFF                           (24)
  #define CMI_RESPOND_PORT_0_STALL_RSVD2_WID                           ( 8)
  #define CMI_RESPOND_PORT_0_STALL_RSVD2_MSK                           (0xFF000000)
  #define CMI_RESPOND_PORT_0_STALL_RSVD2_MIN                           (0)
  #define CMI_RESPOND_PORT_0_STALL_RSVD2_MAX                           (255) // 0x000000FF
  #define CMI_RESPOND_PORT_0_STALL_RSVD2_DEF                           (0x00000000)
  #define CMI_RESPOND_PORT_0_STALL_RSVD2_HSH                           (0x08311294)

#define CMI_RESPOND_PORT_0_RESERVED_0_REG                              (0x00011298)
//Duplicate of CMF_RSVD0_REG

#define CMI_RESPOND_PORT_0_RESERVED_1_REG                              (0x0001129C)
//Duplicate of CMF_RSVD0_REG

#define CMI_RESPOND_PORT_0_RESERVED_2_REG                              (0x000112A0)
//Duplicate of CMF_RSVD0_REG

#define CMI_RESPOND_PORT_0_ACCUM_REQ_OUT_REG                           (0x000112A4)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_REQ_IN_REG

#define CMI_RESPOND_PORT_0_ACCUM_RD_CPL_IN_REG                         (0x000112A8)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_REG

#define CMI_RESPOND_PORT_0_ACCUM_RSP_IN_REG                            (0x000112AC)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_REG

#define CMI_RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_REG                  (0x000112B0)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_REG

#define CMI_RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_REG                  (0x000112B4)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_REG

#define CMI_RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_REG                  (0x000112B8)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_REG

#define CMI_RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_REG                  (0x000112BC)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_REG

#define CMI_RESPOND_PORT_1_CPL_CONFIG_1_REG                            (0x000112C0)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_1_REG

#define CMI_RESPOND_PORT_1_STALL_REG                                   (0x000112C4)
//Duplicate of CMI_RESPOND_PORT_0_STALL_REG

#define CMI_RESPOND_PORT_1_RESERVED_0_REG                              (0x000112C8)
//Duplicate of CMF_RSVD0_REG

#define CMI_RESPOND_PORT_1_RESERVED_1_REG                              (0x000112CC)
//Duplicate of CMF_RSVD0_REG

#define CMI_RESPOND_PORT_1_RESERVED_2_REG                              (0x000112D0)
//Duplicate of CMF_RSVD0_REG

#define CMI_RESPOND_PORT_1_ACCUM_REQ_OUT_REG                           (0x000112D4)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_REQ_IN_REG

#define CMI_RESPOND_PORT_1_ACCUM_RD_CPL_IN_REG                         (0x000112D8)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_REG

#define CMI_RESPOND_PORT_1_ACCUM_RSP_IN_REG                            (0x000112DC)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_REG

#define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_REG                  (0x000112E0)

  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_WR_RSP_PARK_SIZE_OFF ( 0)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_WR_RSP_PARK_SIZE_WID ( 4)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_WR_RSP_PARK_SIZE_MSK (0x0000000F)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_WR_RSP_PARK_SIZE_MIN (0)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_WR_RSP_PARK_SIZE_MAX (15) // 0x0000000F
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_WR_RSP_PARK_SIZE_DEF (0x00000003)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_WR_RSP_PARK_SIZE_HSH (0x040112E0)

  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED0_OFF      ( 4)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED0_WID      ( 4)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED0_MSK      (0x000000F0)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED0_MIN      (0)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED0_MAX      (15) // 0x0000000F
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED0_DEF      (0x00000000)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED0_HSH      (0x040912E0)

  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_OFF ( 8)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_WID ( 4)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_MSK (0x00000F00)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_MIN (0)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_MAX (15) // 0x0000000F
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_DEF (0x00000003)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_HSH (0x041112E0)

  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED1_OFF      (12)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED1_WID      ( 4)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED1_MSK      (0x0000F000)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED1_MIN      (0)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED1_MAX      (15) // 0x0000000F
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED1_DEF      (0x00000000)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED1_HSH      (0x041912E0)

  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_OFF (16)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_WID ( 8)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_MSK (0x00FF0000)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_MIN (0)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_MAX (255) // 0x000000FF
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_DEF (0x0000000E)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_HSH (0x082112E0)

  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_OFF (24)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_WID ( 8)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_MSK (0xFF000000)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_MIN (0)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_MAX (255) // 0x000000FF
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_DEF (0x0000000A)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_HSH (0x083112E0)

#define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_REG                  (0x000112E4)
//Duplicate of CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_REG

#define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_REG                  (0x000112E8)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_REG

#define CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_REG                  (0x000112EC)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_REG

#define CMI_RESPOND_PORT_2_CPL_CONFIG_1_REG                            (0x000112F0)

  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_OFF        ( 0)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_WID        ( 8)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_MSK        (0x000000FF)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_MIN        (0)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_MAX        (255) // 0x000000FF
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_DEF        (0x00000014)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_HSH        (0x080112F0)

  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_RSP_QUEUEDEPTH_OFF           ( 8)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_RSP_QUEUEDEPTH_WID           ( 8)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_RSP_QUEUEDEPTH_MSK           (0x0000FF00)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_RSP_QUEUEDEPTH_MIN           (0)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_RSP_QUEUEDEPTH_MAX           (255) // 0x000000FF
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_RSP_QUEUEDEPTH_DEF           (0x0000001C)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_RSP_QUEUEDEPTH_HSH           (0x081112F0)

  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_REQ_FAST_WAKE_OFF            (16)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_REQ_FAST_WAKE_WID            ( 1)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_REQ_FAST_WAKE_MSK            (0x00010000)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_REQ_FAST_WAKE_MIN            (0)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_REQ_FAST_WAKE_MAX            (1) // 0x00000001
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_REQ_FAST_WAKE_DEF            (0x00000001)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_REQ_FAST_WAKE_HSH            (0x012112F0)

  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_RESERVED1_OFF                (17)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_RESERVED1_WID                (15)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_RESERVED1_MSK                (0xFFFE0000)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_RESERVED1_MIN                (0)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_RESERVED1_MAX                (32767) // 0x00007FFF
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_RESERVED1_DEF                (0x00000000)
  #define CMI_RESPOND_PORT_2_CPL_CONFIG_1_RESERVED1_HSH                (0x0F2312F0)

#define CMI_RESPOND_PORT_2_STALL_REG                                   (0x000112F4)
//Duplicate of CMI_RESPOND_PORT_0_STALL_REG

#define CMI_RESPOND_PORT_2_RESERVED_0_REG                              (0x000112F8)
//Duplicate of CMF_RSVD0_REG

#define CMI_RESPOND_PORT_2_RESERVED_1_REG                              (0x000112FC)
//Duplicate of CMF_RSVD0_REG

#define CMI_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_REG               (0x00011300)

  #define CMI_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_FIRST_LEVEL_BID_RD_PARK_SIZE_CH_0_OFF ( 0)
  #define CMI_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_FIRST_LEVEL_BID_RD_PARK_SIZE_CH_0_WID ( 4)
  #define CMI_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_FIRST_LEVEL_BID_RD_PARK_SIZE_CH_0_MSK (0x0000000F)
  #define CMI_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_FIRST_LEVEL_BID_RD_PARK_SIZE_CH_0_MIN (0)
  #define CMI_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_FIRST_LEVEL_BID_RD_PARK_SIZE_CH_0_MAX (15) // 0x0000000F
  #define CMI_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_FIRST_LEVEL_BID_RD_PARK_SIZE_CH_0_DEF (0x00000003)
  #define CMI_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_FIRST_LEVEL_BID_RD_PARK_SIZE_CH_0_HSH (0x04011300)

  #define CMI_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_FIRST_LEVEL_BID_WR_PARK_SIZE_CH_0_OFF ( 4)
  #define CMI_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_FIRST_LEVEL_BID_WR_PARK_SIZE_CH_0_WID ( 4)
  #define CMI_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_FIRST_LEVEL_BID_WR_PARK_SIZE_CH_0_MSK (0x000000F0)
  #define CMI_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_FIRST_LEVEL_BID_WR_PARK_SIZE_CH_0_MIN (0)
  #define CMI_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_FIRST_LEVEL_BID_WR_PARK_SIZE_CH_0_MAX (15) // 0x0000000F
  #define CMI_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_FIRST_LEVEL_BID_WR_PARK_SIZE_CH_0_DEF (0x00000003)
  #define CMI_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_FIRST_LEVEL_BID_WR_PARK_SIZE_CH_0_HSH (0x04091300)

  #define CMI_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_RESERVED_OFF    ( 8)
  #define CMI_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_RESERVED_WID    (24)
  #define CMI_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_RESERVED_MSK    (0xFFFFFF00)
  #define CMI_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_RESERVED_MIN    (0)
  #define CMI_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_RESERVED_MAX    (16777215) // 0x00FFFFFF
  #define CMI_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_RESERVED_DEF    (0x00000000)
  #define CMI_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_RESERVED_HSH    (0x18111300)

#define CMI_RESPOND_PORT_2_ACCUM_REQ_OUT_REG                           (0x00011304)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_REQ_IN_REG

#define CMI_RESPOND_PORT_2_ACCUM_RD_CPL_IN_REG                         (0x00011308)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_REG

#define CMI_RESPOND_PORT_2_ACCUM_RSP_IN_REG                            (0x0001130C)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_REG

#define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_REG                  (0x00011310)

  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_WR_RSP_PARK_SIZE_OFF ( 0)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_WR_RSP_PARK_SIZE_WID ( 4)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_WR_RSP_PARK_SIZE_MSK (0x0000000F)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_WR_RSP_PARK_SIZE_MIN (0)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_WR_RSP_PARK_SIZE_MAX (15) // 0x0000000F
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_WR_RSP_PARK_SIZE_DEF (0x00000003)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_WR_RSP_PARK_SIZE_HSH (0x04011310)

  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED0_OFF      ( 4)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED0_WID      ( 4)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED0_MSK      (0x000000F0)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED0_MIN      (0)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED0_MAX      (15) // 0x0000000F
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED0_DEF      (0x00000000)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED0_HSH      (0x04091310)

  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_OFF ( 8)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_WID ( 4)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_MSK (0x00000F00)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_MIN (0)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_MAX (15) // 0x0000000F
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_DEF (0x00000003)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_HSH (0x04111310)

  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED1_OFF      (12)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED1_WID      ( 4)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED1_MSK      (0x0000F000)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED1_MIN      (0)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED1_MAX      (15) // 0x0000000F
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED1_DEF      (0x00000000)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED1_HSH      (0x04191310)

  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_OFF (16)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_WID ( 8)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_MSK (0x00FF0000)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_MIN (0)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_MAX (255) // 0x000000FF
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_DEF (0x0000000C)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_HSH (0x08211310)

  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_OFF (24)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_WID ( 8)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_MSK (0xFF000000)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_MIN (0)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_MAX (255) // 0x000000FF
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_DEF (0x0000000A)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_HSH (0x08311310)

#define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_REG                  (0x00011314)
//Duplicate of CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_REG

#define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_REG                  (0x00011318)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_REG

#define CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_REG                  (0x0001131C)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_REG

#define CMI_RESPOND_PORT_3_CPL_CONFIG_1_REG                            (0x00011320)

  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_OFF        ( 0)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_WID        ( 8)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_MSK        (0x000000FF)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_MIN        (0)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_MAX        (255) // 0x000000FF
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_DEF        (0x00000014)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_HSH        (0x08011320)

  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_RSP_QUEUEDEPTH_OFF           ( 8)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_RSP_QUEUEDEPTH_WID           ( 8)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_RSP_QUEUEDEPTH_MSK           (0x0000FF00)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_RSP_QUEUEDEPTH_MIN           (0)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_RSP_QUEUEDEPTH_MAX           (255) // 0x000000FF
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_RSP_QUEUEDEPTH_DEF           (0x00000018)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_RSP_QUEUEDEPTH_HSH           (0x08111320)

  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_REQ_FAST_WAKE_OFF            (16)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_REQ_FAST_WAKE_WID            ( 1)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_REQ_FAST_WAKE_MSK            (0x00010000)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_REQ_FAST_WAKE_MIN            (0)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_REQ_FAST_WAKE_MAX            (1) // 0x00000001
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_REQ_FAST_WAKE_DEF            (0x00000001)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_REQ_FAST_WAKE_HSH            (0x01211320)

  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_RESERVED1_OFF                (17)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_RESERVED1_WID                (15)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_RESERVED1_MSK                (0xFFFE0000)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_RESERVED1_MIN                (0)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_RESERVED1_MAX                (32767) // 0x00007FFF
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_RESERVED1_DEF                (0x00000000)
  #define CMI_RESPOND_PORT_3_CPL_CONFIG_1_RESERVED1_HSH                (0x0F231320)

#define CMI_RESPOND_PORT_3_STALL_REG                                   (0x00011324)
//Duplicate of CMI_RESPOND_PORT_0_STALL_REG

#define CMI_RESPOND_PORT_3_RESERVED_0_REG                              (0x00011328)
//Duplicate of CMF_RSVD0_REG

#define CMI_RESPOND_PORT_3_RESERVED_1_REG                              (0x0001132C)
//Duplicate of CMF_RSVD0_REG

#define CMI_RESPOND_PORT_3_RESERVED_2_REG                              (0x00011330)
//Duplicate of CMF_RSVD0_REG

#define CMI_RESPOND_PORT_3_ACCUM_REQ_OUT_REG                           (0x00011334)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_REQ_IN_REG

#define CMI_RESPOND_PORT_3_ACCUM_RD_CPL_IN_REG                         (0x00011338)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_REG

#define CMI_RESPOND_PORT_3_ACCUM_RSP_IN_REG                            (0x0001133C)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_REG

#define CMI_RESPOND_PORT_4_CPL_CONFIG_0_CHANNEL_0_REG                  (0x00011340)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_REG

#define CMI_RESPOND_PORT_4_CPL_CONFIG_0_CHANNEL_1_REG                  (0x00011344)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_REG

#define CMI_RESPOND_PORT_4_CPL_CONFIG_0_CHANNEL_2_REG                  (0x00011348)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_REG

#define CMI_RESPOND_PORT_4_CPL_CONFIG_0_CHANNEL_3_REG                  (0x0001134C)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_REG

#define CMI_RESPOND_PORT_4_CPL_CONFIG_1_REG                            (0x00011350)

  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_OFF        ( 0)
  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_WID        ( 8)
  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_MSK        (0x000000FF)
  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_MIN        (0)
  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_MAX        (255) // 0x000000FF
  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_DEF        (0x00000000)
  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_HSH        (0x08011350)

  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_RSP_QUEUEDEPTH_OFF           ( 8)
  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_RSP_QUEUEDEPTH_WID           ( 8)
  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_RSP_QUEUEDEPTH_MSK           (0x0000FF00)
  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_RSP_QUEUEDEPTH_MIN           (0)
  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_RSP_QUEUEDEPTH_MAX           (255) // 0x000000FF
  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_RSP_QUEUEDEPTH_DEF           (0x00000000)
  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_RSP_QUEUEDEPTH_HSH           (0x08111350)

  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_REQ_FAST_WAKE_OFF            (16)
  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_REQ_FAST_WAKE_WID            ( 1)
  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_REQ_FAST_WAKE_MSK            (0x00010000)
  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_REQ_FAST_WAKE_MIN            (0)
  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_REQ_FAST_WAKE_MAX            (1) // 0x00000001
  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_REQ_FAST_WAKE_DEF            (0x00000001)
  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_REQ_FAST_WAKE_HSH            (0x01211350)

  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_RESERVED1_OFF                (17)
  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_RESERVED1_WID                (15)
  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_RESERVED1_MSK                (0xFFFE0000)
  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_RESERVED1_MIN                (0)
  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_RESERVED1_MAX                (32767) // 0x00007FFF
  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_RESERVED1_DEF                (0x00000000)
  #define CMI_RESPOND_PORT_4_CPL_CONFIG_1_RESERVED1_HSH                (0x0F231350)

#define CMI_RESPOND_PORT_4_STALL_REG                                   (0x00011354)
//Duplicate of CMI_RESPOND_PORT_0_STALL_REG

#define CMI_RESPOND_PORT_4_RESERVED_0_REG                              (0x00011358)
//Duplicate of CMF_RSVD0_REG

#define CMI_RESPOND_PORT_4_RESERVED_1_REG                              (0x0001135C)
//Duplicate of CMF_RSVD0_REG

#define CMI_RESPOND_PORT_4_RESERVED_2_REG                              (0x00011360)
//Duplicate of CMF_RSVD0_REG

#define CMI_RESPOND_PORT_4_ACCUM_REQ_OUT_REG                           (0x00011364)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_REQ_IN_REG

#define CMI_RESPOND_PORT_4_ACCUM_RD_CPL_IN_REG                         (0x00011368)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_REG

#define CMI_RESPOND_PORT_4_ACCUM_RSP_IN_REG                            (0x0001136C)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_REG

#define CMF_LT_MEM_SA_PG_ACCESS_POLICY_CP_REG                          (0x00011400)
//Duplicate of CMF_LT_SA_W_PG_ACCESS_POLICY_CP_REG

#define CMF_LT_MEM_SA_PG_ACCESS_POLICY_WAC_REG                         (0x00011408)
//Duplicate of CMF_LT_SA_W_PG_ACCESS_POLICY_WAC_REG

#define CMF_LT_MEM_SA_PG_ACCESS_POLICY_RAC_REG                         (0x00011410)
//Duplicate of CMF_LT_SA_W_PG_ACCESS_POLICY_RAC_REG

#define CMF_OS_PG_ACCESS_POLICY_CP_REG                                 (0x00011418)
//Duplicate of CMF_LT_SA_W_PG_ACCESS_POLICY_CP_REG

#define CMF_OS_PG_ACCESS_POLICY_WAC_REG                                (0x00011420)

  #define CMF_OS_PG_ACCESS_POLICY_WAC_SAI_MASK_OFF                     ( 0)
  #define CMF_OS_PG_ACCESS_POLICY_WAC_SAI_MASK_WID                     (64)
  #define CMF_OS_PG_ACCESS_POLICY_WAC_SAI_MASK_MSK                     (0xFFFFFFFFFFFFFFFFULL)
  #define CMF_OS_PG_ACCESS_POLICY_WAC_SAI_MASK_MIN                     (0)
  #define CMF_OS_PG_ACCESS_POLICY_WAC_SAI_MASK_MAX                     (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define CMF_OS_PG_ACCESS_POLICY_WAC_SAI_MASK_DEF                     (0x4000100021B)
  #define CMF_OS_PG_ACCESS_POLICY_WAC_SAI_MASK_HSH                     (0x40011420)

#define CMF_OS_PG_ACCESS_POLICY_RAC_REG                                (0x00011428)
//Duplicate of CMF_LT_SA_W_PG_ACCESS_POLICY_RAC_REG

#define CMI_PARITY_ERR_LOG_REG                                         (0x00011448)

  #define CMI_PARITY_ERR_LOG_Reserved_0_OFF                            ( 0)
  #define CMI_PARITY_ERR_LOG_Reserved_0_WID                            ( 5)
  #define CMI_PARITY_ERR_LOG_Reserved_0_MSK                            (0x0000001F)
  #define CMI_PARITY_ERR_LOG_Reserved_0_MIN                            (0)
  #define CMI_PARITY_ERR_LOG_Reserved_0_MAX                            (31) // 0x0000001F
  #define CMI_PARITY_ERR_LOG_Reserved_0_DEF                            (0x00000000)
  #define CMI_PARITY_ERR_LOG_Reserved_0_HSH                            (0x45011448)

  #define CMI_PARITY_ERR_LOG_ERR_ADDRESS_OFF                           ( 5)
  #define CMI_PARITY_ERR_LOG_ERR_ADDRESS_WID                           (34)
  #define CMI_PARITY_ERR_LOG_ERR_ADDRESS_MSK                           (0x0000007FFFFFFFE0ULL)
  #define CMI_PARITY_ERR_LOG_ERR_ADDRESS_MIN                           (0)
  #define CMI_PARITY_ERR_LOG_ERR_ADDRESS_MAX                           (17179869183ULL) // 0x3FFFFFFFF
  #define CMI_PARITY_ERR_LOG_ERR_ADDRESS_DEF                           (0x00000000)
  #define CMI_PARITY_ERR_LOG_ERR_ADDRESS_HSH                           (0x620B1448)

  #define CMI_PARITY_ERR_LOG_Reserved_1_OFF                            (39)
  #define CMI_PARITY_ERR_LOG_Reserved_1_WID                            ( 9)
  #define CMI_PARITY_ERR_LOG_Reserved_1_MSK                            (0x0000FF8000000000ULL)
  #define CMI_PARITY_ERR_LOG_Reserved_1_MIN                            (0)
  #define CMI_PARITY_ERR_LOG_Reserved_1_MAX                            (511) // 0x000001FF
  #define CMI_PARITY_ERR_LOG_Reserved_1_DEF                            (0x00000000)
  #define CMI_PARITY_ERR_LOG_Reserved_1_HSH                            (0x494F1448)

  #define CMI_PARITY_ERR_LOG_ERR_SRC_OFF                               (48)
  #define CMI_PARITY_ERR_LOG_ERR_SRC_WID                               ( 3)
  #define CMI_PARITY_ERR_LOG_ERR_SRC_MSK                               (0x0007000000000000ULL)
  #define CMI_PARITY_ERR_LOG_ERR_SRC_MIN                               (0)
  #define CMI_PARITY_ERR_LOG_ERR_SRC_MAX                               (7) // 0x00000007
  #define CMI_PARITY_ERR_LOG_ERR_SRC_DEF                               (0x00000000)
  #define CMI_PARITY_ERR_LOG_ERR_SRC_HSH                               (0x43611448)

  #define CMI_PARITY_ERR_LOG_Reserved_2_OFF                            (51)
  #define CMI_PARITY_ERR_LOG_Reserved_2_WID                            (12)
  #define CMI_PARITY_ERR_LOG_Reserved_2_MSK                            (0x7FF8000000000000ULL)
  #define CMI_PARITY_ERR_LOG_Reserved_2_MIN                            (0)
  #define CMI_PARITY_ERR_LOG_Reserved_2_MAX                            (4095) // 0x00000FFF
  #define CMI_PARITY_ERR_LOG_Reserved_2_DEF                            (0x00000000)
  #define CMI_PARITY_ERR_LOG_Reserved_2_HSH                            (0x4C671448)

  #define CMI_PARITY_ERR_LOG_ERR_STS_OFF                               (63)
  #define CMI_PARITY_ERR_LOG_ERR_STS_WID                               ( 1)
  #define CMI_PARITY_ERR_LOG_ERR_STS_MSK                               (0x8000000000000000ULL)
  #define CMI_PARITY_ERR_LOG_ERR_STS_MIN                               (0)
  #define CMI_PARITY_ERR_LOG_ERR_STS_MAX                               (1) // 0x00000001
  #define CMI_PARITY_ERR_LOG_ERR_STS_DEF                               (0x00000000)
  #define CMI_PARITY_ERR_LOG_ERR_STS_HSH                               (0x417F1448)

#define CMI_PARITY_ERR_INJ_REG                                         (0x00011450)

  #define CMI_PARITY_ERR_INJ_Reserved_0_OFF                            ( 0)
  #define CMI_PARITY_ERR_INJ_Reserved_0_WID                            ( 8)
  #define CMI_PARITY_ERR_INJ_Reserved_0_MSK                            (0x000000FF)
  #define CMI_PARITY_ERR_INJ_Reserved_0_MIN                            (0)
  #define CMI_PARITY_ERR_INJ_Reserved_0_MAX                            (255) // 0x000000FF
  #define CMI_PARITY_ERR_INJ_Reserved_0_DEF                            (0x00000000)
  #define CMI_PARITY_ERR_INJ_Reserved_0_HSH                            (0x08011450)

  #define CMI_PARITY_ERR_INJ_ADDR_ERR_EN_OFF                           ( 8)
  #define CMI_PARITY_ERR_INJ_ADDR_ERR_EN_WID                           ( 1)
  #define CMI_PARITY_ERR_INJ_ADDR_ERR_EN_MSK                           (0x00000100)
  #define CMI_PARITY_ERR_INJ_ADDR_ERR_EN_MIN                           (0)
  #define CMI_PARITY_ERR_INJ_ADDR_ERR_EN_MAX                           (1) // 0x00000001
  #define CMI_PARITY_ERR_INJ_ADDR_ERR_EN_DEF                           (0x00000000)
  #define CMI_PARITY_ERR_INJ_ADDR_ERR_EN_HSH                           (0x01111450)

  #define CMI_PARITY_ERR_INJ_Reserved_1_OFF                            ( 9)
  #define CMI_PARITY_ERR_INJ_Reserved_1_WID                            ( 1)
  #define CMI_PARITY_ERR_INJ_Reserved_1_MSK                            (0x00000200)
  #define CMI_PARITY_ERR_INJ_Reserved_1_MIN                            (0)
  #define CMI_PARITY_ERR_INJ_Reserved_1_MAX                            (1) // 0x00000001
  #define CMI_PARITY_ERR_INJ_Reserved_1_DEF                            (0x00000000)
  #define CMI_PARITY_ERR_INJ_Reserved_1_HSH                            (0x01131450)

  #define CMI_PARITY_ERR_INJ_Reserved_2_OFF                            (10)
  #define CMI_PARITY_ERR_INJ_Reserved_2_WID                            ( 6)
  #define CMI_PARITY_ERR_INJ_Reserved_2_MSK                            (0x0000FC00)
  #define CMI_PARITY_ERR_INJ_Reserved_2_MIN                            (0)
  #define CMI_PARITY_ERR_INJ_Reserved_2_MAX                            (63) // 0x0000003F
  #define CMI_PARITY_ERR_INJ_Reserved_2_DEF                            (0x00000000)
  #define CMI_PARITY_ERR_INJ_Reserved_2_HSH                            (0x06151450)

  #define CMI_PARITY_ERR_INJ_ERR_SRC_MASK_OFF                          (16)
  #define CMI_PARITY_ERR_INJ_ERR_SRC_MASK_WID                          ( 8)
  #define CMI_PARITY_ERR_INJ_ERR_SRC_MASK_MSK                          (0x00FF0000)
  #define CMI_PARITY_ERR_INJ_ERR_SRC_MASK_MIN                          (0)
  #define CMI_PARITY_ERR_INJ_ERR_SRC_MASK_MAX                          (255) // 0x000000FF
  #define CMI_PARITY_ERR_INJ_ERR_SRC_MASK_DEF                          (0x00000000)
  #define CMI_PARITY_ERR_INJ_ERR_SRC_MASK_HSH                          (0x08211450)

  #define CMI_PARITY_ERR_INJ_Reserved_3_OFF                            (24)
  #define CMI_PARITY_ERR_INJ_Reserved_3_WID                            ( 8)
  #define CMI_PARITY_ERR_INJ_Reserved_3_MSK                            (0xFF000000)
  #define CMI_PARITY_ERR_INJ_Reserved_3_MIN                            (0)
  #define CMI_PARITY_ERR_INJ_Reserved_3_MAX                            (255) // 0x000000FF
  #define CMI_PARITY_ERR_INJ_Reserved_3_DEF                            (0x00000000)
  #define CMI_PARITY_ERR_INJ_Reserved_3_HSH                            (0x08311450)

#define CMI_PARITY_CONTROL_REG                                         (0x00011454)

  #define CMI_PARITY_CONTROL_ADDR_PARITY_CHK_MASK_OFF                  ( 0)
  #define CMI_PARITY_CONTROL_ADDR_PARITY_CHK_MASK_WID                  ( 8)
  #define CMI_PARITY_CONTROL_ADDR_PARITY_CHK_MASK_MSK                  (0x000000FF)
  #define CMI_PARITY_CONTROL_ADDR_PARITY_CHK_MASK_MIN                  (0)
  #define CMI_PARITY_CONTROL_ADDR_PARITY_CHK_MASK_MAX                  (255) // 0x000000FF
  #define CMI_PARITY_CONTROL_ADDR_PARITY_CHK_MASK_DEF                  (0x000000FF)
  #define CMI_PARITY_CONTROL_ADDR_PARITY_CHK_MASK_HSH                  (0x08011454)

  #define CMI_PARITY_CONTROL_ADDR_PARITY_GEN_MASK_OFF                  ( 8)
  #define CMI_PARITY_CONTROL_ADDR_PARITY_GEN_MASK_WID                  ( 8)
  #define CMI_PARITY_CONTROL_ADDR_PARITY_GEN_MASK_MSK                  (0x0000FF00)
  #define CMI_PARITY_CONTROL_ADDR_PARITY_GEN_MASK_MIN                  (0)
  #define CMI_PARITY_CONTROL_ADDR_PARITY_GEN_MASK_MAX                  (255) // 0x000000FF
  #define CMI_PARITY_CONTROL_ADDR_PARITY_GEN_MASK_DEF                  (0x000000FF)
  #define CMI_PARITY_CONTROL_ADDR_PARITY_GEN_MASK_HSH                  (0x08111454)

  #define CMI_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_OFF                  (16)
  #define CMI_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_WID                  ( 1)
  #define CMI_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_MSK                  (0x00010000)
  #define CMI_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_MIN                  (0)
  #define CMI_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_MAX                  (1) // 0x00000001
  #define CMI_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_DEF                  (0x00000000)
  #define CMI_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_HSH                  (0x01211454)

  #define CMI_PARITY_CONTROL_DIS_PARITY_LOG_OFF                        (17)
  #define CMI_PARITY_CONTROL_DIS_PARITY_LOG_WID                        ( 1)
  #define CMI_PARITY_CONTROL_DIS_PARITY_LOG_MSK                        (0x00020000)
  #define CMI_PARITY_CONTROL_DIS_PARITY_LOG_MIN                        (0)
  #define CMI_PARITY_CONTROL_DIS_PARITY_LOG_MAX                        (1) // 0x00000001
  #define CMI_PARITY_CONTROL_DIS_PARITY_LOG_DEF                        (0x00000000)
  #define CMI_PARITY_CONTROL_DIS_PARITY_LOG_HSH                        (0x01231454)

  #define CMI_PARITY_CONTROL_DIS_MULTIPLE_PCH_MSG_OFF                  (18)
  #define CMI_PARITY_CONTROL_DIS_MULTIPLE_PCH_MSG_WID                  ( 1)
  #define CMI_PARITY_CONTROL_DIS_MULTIPLE_PCH_MSG_MSK                  (0x00040000)
  #define CMI_PARITY_CONTROL_DIS_MULTIPLE_PCH_MSG_MIN                  (0)
  #define CMI_PARITY_CONTROL_DIS_MULTIPLE_PCH_MSG_MAX                  (1) // 0x00000001
  #define CMI_PARITY_CONTROL_DIS_MULTIPLE_PCH_MSG_DEF                  (0x00000000)
  #define CMI_PARITY_CONTROL_DIS_MULTIPLE_PCH_MSG_HSH                  (0x01251454)

  #define CMI_PARITY_CONTROL_Reserved_OFF                              (19)
  #define CMI_PARITY_CONTROL_Reserved_WID                              (12)
  #define CMI_PARITY_CONTROL_Reserved_MSK                              (0x7FF80000)
  #define CMI_PARITY_CONTROL_Reserved_MIN                              (0)
  #define CMI_PARITY_CONTROL_Reserved_MAX                              (4095) // 0x00000FFF
  #define CMI_PARITY_CONTROL_Reserved_DEF                              (0x00000000)
  #define CMI_PARITY_CONTROL_Reserved_HSH                              (0x0C271454)

  #define CMI_PARITY_CONTROL_PARITY_EN_OFF                             (31)
  #define CMI_PARITY_CONTROL_PARITY_EN_WID                             ( 1)
  #define CMI_PARITY_CONTROL_PARITY_EN_MSK                             (0x80000000)
  #define CMI_PARITY_CONTROL_PARITY_EN_MIN                             (0)
  #define CMI_PARITY_CONTROL_PARITY_EN_MAX                             (1) // 0x00000001
  #define CMI_PARITY_CONTROL_PARITY_EN_DEF                             (0x00000000)
  #define CMI_PARITY_CONTROL_PARITY_EN_HSH                             (0x013F1454)

#define CMI_REQ_L3_ARB_CONFIG_REG                                      (0x0001145C)

  #define CMI_REQ_L3_ARB_CONFIG_NonVC1Wr_HiPri_Park_Size_OFF           ( 0)
  #define CMI_REQ_L3_ARB_CONFIG_NonVC1Wr_HiPri_Park_Size_WID           ( 4)
  #define CMI_REQ_L3_ARB_CONFIG_NonVC1Wr_HiPri_Park_Size_MSK           (0x0000000F)
  #define CMI_REQ_L3_ARB_CONFIG_NonVC1Wr_HiPri_Park_Size_MIN           (0)
  #define CMI_REQ_L3_ARB_CONFIG_NonVC1Wr_HiPri_Park_Size_MAX           (15) // 0x0000000F
  #define CMI_REQ_L3_ARB_CONFIG_NonVC1Wr_HiPri_Park_Size_DEF           (0x00000008)
  #define CMI_REQ_L3_ARB_CONFIG_NonVC1Wr_HiPri_Park_Size_HSH           (0x0401145C)

  #define CMI_REQ_L3_ARB_CONFIG_NonVC1Wr_LoPri_Park_Size_OFF           ( 4)
  #define CMI_REQ_L3_ARB_CONFIG_NonVC1Wr_LoPri_Park_Size_WID           ( 4)
  #define CMI_REQ_L3_ARB_CONFIG_NonVC1Wr_LoPri_Park_Size_MSK           (0x000000F0)
  #define CMI_REQ_L3_ARB_CONFIG_NonVC1Wr_LoPri_Park_Size_MIN           (0)
  #define CMI_REQ_L3_ARB_CONFIG_NonVC1Wr_LoPri_Park_Size_MAX           (15) // 0x0000000F
  #define CMI_REQ_L3_ARB_CONFIG_NonVC1Wr_LoPri_Park_Size_DEF           (0x00000002)
  #define CMI_REQ_L3_ARB_CONFIG_NonVC1Wr_LoPri_Park_Size_HSH           (0x0409145C)

  #define CMI_REQ_L3_ARB_CONFIG_VC1Wr_HiPri_Park_Size_OFF              ( 8)
  #define CMI_REQ_L3_ARB_CONFIG_VC1Wr_HiPri_Park_Size_WID              ( 4)
  #define CMI_REQ_L3_ARB_CONFIG_VC1Wr_HiPri_Park_Size_MSK              (0x00000F00)
  #define CMI_REQ_L3_ARB_CONFIG_VC1Wr_HiPri_Park_Size_MIN              (0)
  #define CMI_REQ_L3_ARB_CONFIG_VC1Wr_HiPri_Park_Size_MAX              (15) // 0x0000000F
  #define CMI_REQ_L3_ARB_CONFIG_VC1Wr_HiPri_Park_Size_DEF              (0x00000008)
  #define CMI_REQ_L3_ARB_CONFIG_VC1Wr_HiPri_Park_Size_HSH              (0x0411145C)

  #define CMI_REQ_L3_ARB_CONFIG_VC1Wr_LoPri_Park_Size_OFF              (12)
  #define CMI_REQ_L3_ARB_CONFIG_VC1Wr_LoPri_Park_Size_WID              ( 4)
  #define CMI_REQ_L3_ARB_CONFIG_VC1Wr_LoPri_Park_Size_MSK              (0x0000F000)
  #define CMI_REQ_L3_ARB_CONFIG_VC1Wr_LoPri_Park_Size_MIN              (0)
  #define CMI_REQ_L3_ARB_CONFIG_VC1Wr_LoPri_Park_Size_MAX              (15) // 0x0000000F
  #define CMI_REQ_L3_ARB_CONFIG_VC1Wr_LoPri_Park_Size_DEF              (0x00000002)
  #define CMI_REQ_L3_ARB_CONFIG_VC1Wr_LoPri_Park_Size_HSH              (0x0419145C)

  #define CMI_REQ_L3_ARB_CONFIG_Reserved_OFF                           (16)
  #define CMI_REQ_L3_ARB_CONFIG_Reserved_WID                           (16)
  #define CMI_REQ_L3_ARB_CONFIG_Reserved_MSK                           (0xFFFF0000)
  #define CMI_REQ_L3_ARB_CONFIG_Reserved_MIN                           (0)
  #define CMI_REQ_L3_ARB_CONFIG_Reserved_MAX                           (65535) // 0x0000FFFF
  #define CMI_REQ_L3_ARB_CONFIG_Reserved_DEF                           (0x00000000)
  #define CMI_REQ_L3_ARB_CONFIG_Reserved_HSH                           (0x1021145C)

#define IOP_CMI_EP_ARB_CTL_REG                                         (0x00011468)

  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE1_OFF                 ( 0)
  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE1_WID                 ( 4)
  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE1_MSK                 (0x0000000F)
  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE1_MIN                 (0)
  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE1_MAX                 (15) // 0x0000000F
  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE1_DEF                 (0x00000003)
  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE1_HSH                 (0x04011468)

  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE2_OFF                 ( 4)
  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE2_WID                 ( 4)
  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE2_MSK                 (0x000000F0)
  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE2_MIN                 (0)
  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE2_MAX                 (15) // 0x0000000F
  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE2_DEF                 (0x00000007)
  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE2_HSH                 (0x04091468)

  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE3_OFF                 ( 8)
  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE3_WID                 ( 4)
  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE3_MSK                 (0x00000F00)
  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE3_MIN                 (0)
  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE3_MAX                 (15) // 0x0000000F
  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE3_DEF                 (0x00000001)
  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE3_HSH                 (0x04111468)

  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE4_OFF                 (12)
  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE4_WID                 ( 4)
  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE4_MSK                 (0x0000F000)
  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE4_MIN                 (0)
  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE4_MAX                 (15) // 0x0000000F
  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE4_DEF                 (0x00000005)
  #define IOP_CMI_EP_ARB_CTL_DIP_VC1_RD_PARK_SIZE4_HSH                 (0x04191468)

  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE1_OFF                 (16)
  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE1_WID                 ( 4)
  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE1_MSK                 (0x000F0000)
  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE1_MIN                 (0)
  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE1_MAX                 (15) // 0x0000000F
  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE1_DEF                 (0x00000007)
  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE1_HSH                 (0x04211468)

  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE2_OFF                 (20)
  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE2_WID                 ( 4)
  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE2_MSK                 (0x00F00000)
  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE2_MIN                 (0)
  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE2_MAX                 (15) // 0x0000000F
  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE2_DEF                 (0x00000003)
  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE2_HSH                 (0x04291468)

  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE3_OFF                 (24)
  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE3_WID                 ( 4)
  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE3_MSK                 (0x0F000000)
  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE3_MIN                 (0)
  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE3_MAX                 (15) // 0x0000000F
  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE3_DEF                 (0x00000009)
  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE3_HSH                 (0x04311468)

  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE4_OFF                 (28)
  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE4_WID                 ( 4)
  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE4_MSK                 (0xF0000000)
  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE4_MIN                 (0)
  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE4_MAX                 (15) // 0x0000000F
  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE4_DEF                 (0x00000005)
  #define IOP_CMI_EP_ARB_CTL_IOP_VC1_RD_PARK_SIZE4_HSH                 (0x04391468)

#define CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_REG                 (0x00011480)

  #define CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_READ_COUNTER_P0_OFF  ( 0)
  #define CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_READ_COUNTER_P0_WID  (64)
  #define CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_READ_COUNTER_P0_MSK  (0xFFFFFFFFFFFFFFFFULL)
  #define CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_READ_COUNTER_P0_MIN  (0)
  #define CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_READ_COUNTER_P0_MAX  (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_READ_COUNTER_P0_DEF  (0x00000000)
  #define CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_READ_COUNTER_P0_HSH  (0x40011480)

#define CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_1_P0_REG                 (0x00011488)
//Duplicate of CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_REG

#define CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_3_REG                    (0x00011498)

  #define CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_3_READ_COUNTER_OFF     ( 0)
  #define CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_3_READ_COUNTER_WID     (64)
  #define CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_3_READ_COUNTER_MSK     (0xFFFFFFFFFFFFFFFFULL)
  #define CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_3_READ_COUNTER_MIN     (0)
  #define CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_3_READ_COUNTER_MAX     (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_3_READ_COUNTER_DEF     (0x00000000)
  #define CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_3_READ_COUNTER_HSH     (0x40011498)

#define CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_3_P0_REG                 (0x00011498)
//Duplicate of CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_REG

#define CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_REG                 (0x000114A0)

  #define CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_WRITE_COUNTER_P0_OFF ( 0)
  #define CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_WRITE_COUNTER_P0_WID (64)
  #define CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_WRITE_COUNTER_P0_MSK (0xFFFFFFFFFFFFFFFFULL)
  #define CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_WRITE_COUNTER_P0_MIN (0)
  #define CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_WRITE_COUNTER_P0_MAX (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_WRITE_COUNTER_P0_DEF (0x00000000)
  #define CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_WRITE_COUNTER_P0_HSH (0x400114A0)

#define CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_1_P0_REG                 (0x000114A8)
//Duplicate of CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_REG

#define CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_3_REG                    (0x000114B8)

  #define CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_3_WRITE_COUNTER_OFF    ( 0)
  #define CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_3_WRITE_COUNTER_WID    (64)
  #define CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_3_WRITE_COUNTER_MSK    (0xFFFFFFFFFFFFFFFFULL)
  #define CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_3_WRITE_COUNTER_MIN    (0)
  #define CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_3_WRITE_COUNTER_MAX    (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_3_WRITE_COUNTER_DEF    (0x00000000)
  #define CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_3_WRITE_COUNTER_HSH    (0x400114B8)

#define CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_3_P0_REG                 (0x000114B8)
//Duplicate of CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_REG

#define CMI_RESPOND_PORT_1_RD_COUNTER_CHANNEL_0_P0_REG                 (0x000114C0)
//Duplicate of CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_REG

#define CMI_RESPOND_PORT_1_RD_COUNTER_CHANNEL_1_P0_REG                 (0x000114C8)
//Duplicate of CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_REG

#define CMI_RESPOND_PORT_1_RD_COUNTER_CHANNEL_3_REG                    (0x000114D8)
//Duplicate of CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_3_REG

#define CMI_RESPOND_PORT_1_WR_COUNTER_CHANNEL_0_P0_REG                 (0x000114E0)
//Duplicate of CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_REG

#define CMI_RESPOND_PORT_1_WR_COUNTER_CHANNEL_1_P0_REG                 (0x000114E8)
//Duplicate of CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_REG

#define CMI_RESPOND_PORT_1_WR_COUNTER_CHANNEL_3_REG                    (0x000114F8)
//Duplicate of CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_3_REG

#define CMI_RESPOND_PORT_2_RD_COUNTER_CHANNEL_0_REG                    (0x00011500)
//Duplicate of CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_3_REG

#define CMI_RESPOND_PORT_2_WR_COUNTER_CHANNEL_0_REG                    (0x00011508)
//Duplicate of CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_3_REG

#define CMI_RESPOND_PORT_2_RD_COUNTER_CHANNEL_1_REG                    (0x00011520)
//Duplicate of CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_3_REG

#define CMI_RESPOND_PORT_2_WR_COUNTER_CHANNEL_1_REG                    (0x00011528)
//Duplicate of CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_3_REG

#define CMI_RESPOND_PORT_3_RD_COUNTER_CHANNEL_0_REG                    (0x00011540)
//Duplicate of CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_3_REG

#define CMI_RESPOND_PORT_3_WR_COUNTER_CHANNEL_0_REG                    (0x00011548)
//Duplicate of CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_3_REG

#define CMI_RESPOND_PORT_3_RD_COUNTER_CHANNEL_1_REG                    (0x00011560)
//Duplicate of CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_3_REG

#define CMI_RESPOND_PORT_3_WR_COUNTER_CHANNEL_1_REG                    (0x00011568)
//Duplicate of CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_3_REG

#define CMF_1_LT_SA_W_PG_ACCESS_POLICY_CP_P0_REG                       (0x00011800)
//Duplicate of CMF_LT_SA_W_PG_ACCESS_POLICY_CP_P0_REG

#define CMF_1_LT_SA_W_PG_ACCESS_POLICY_WAC_P0_REG                      (0x00011808)
//Duplicate of CMF_LT_SA_W_PG_ACCESS_POLICY_WAC_P0_REG

#define CMF_1_LT_SA_W_PG_ACCESS_POLICY_RAC_P0_REG                      (0x00011810)
//Duplicate of CMF_LT_SA_W_PG_ACCESS_POLICY_RAC_P0_REG

#define CMI_1_PRIO_THRESHOLD_P0_REG                                    (0x00011818)
//Duplicate of CMI_PRIO_THRESHOLD_P0_REG

#define CMI_1_PRIO_LIM_P0_REG                                          (0x0001181C)
//Duplicate of CMI_PRIO_LIM_P0_REG

#define CMF_1_GLOBAL_CFG_P0_REG                                        (0x00011820)
//Duplicate of CMF_GLOBAL_CFG_P0_REG

#define CMF_1_GLOBAL_CFG_1_P0_REG                                      (0x00011828)
//Duplicate of CMF_GLOBAL_CFG_1_P0_REG

#define CMF_1_ACCUM_CTRL_P0_REG                                        (0x00011840)
//Duplicate of CMF_ACCUM_CTRL_P0_REG

#define CMI_1_IOSF_SB_EP_CTRL_P0_REG                                   (0x00011844)
//Duplicate of CMI_IOSF_SB_EP_CTRL_P0_REG

#define CMI_1_CLK_GATE_EN_0_P0_REG                                     (0x00011848)
//Duplicate of CMI_CLK_GATE_EN_0_P0_REG

#define CMI_1_CLK_GATE_EN_1_P0_REG                                     (0x0001184C)
//Duplicate of CMI_CLK_GATE_EN_0_P0_REG

#define CMF_1_RSVD0_P0_REG                                             (0x00011860)
//Duplicate of CMF_RSVD0_P0_REG

#define CMF_1_RSVD1_P0_REG                                             (0x00011864)
//Duplicate of CMF_RSVD1_P0_REG

#define CMF_1_P_U_CODE_PG_ACCESS_POLICY_CP_P0_REG                      (0x00011870)
//Duplicate of CMF_LT_SA_W_PG_ACCESS_POLICY_CP_P0_REG

#define CMF_1_P_U_CODE_PG_ACCESS_POLICY_WAC_P0_REG                     (0x00011878)
//Duplicate of CMF_P_U_CODE_PG_ACCESS_POLICY_WAC_P0_REG

#define CMF_1_P_U_CODE_PG_ACCESS_POLICY_RAC_P0_REG                     (0x00011880)
//Duplicate of CMF_P_U_CODE_PG_ACCESS_POLICY_WAC_P0_REG

#define CMF_1_TOPOLOGY_GLOBAL_CFG_0_P0_REG                             (0x00011888)
//Duplicate of CMF_TOPOLOGY_GLOBAL_CFG_0_P0_REG

#define CMF_1_TOPOLOGY_GLOBAL_CFG_1_P0_REG                             (0x0001188C)
//Duplicate of CMF_TOPOLOGY_GLOBAL_CFG_1_P0_REG

#define CMF_1_TOPOLOGY_GLOBAL_CFG_2_P0_REG                             (0x00011890)
//Duplicate of CMF_TOPOLOGY_GLOBAL_CFG_2_P0_REG

#define CMF_1_TOPOLOGY_GLOBAL_CFG_3_P0_REG                             (0x00011894)
//Duplicate of CMF_TOPOLOGY_GLOBAL_CFG_3_P0_REG

#define CMF_1_TOPOLOGY_GLOBAL_CFG_4_P0_REG                             (0x00011898)
//Duplicate of CMF_TOPOLOGY_GLOBAL_CFG_4_P0_REG

#define CMF_1_TOPOLOGY_GLOBAL_CFG_5_P0_REG                             (0x0001189C)
//Duplicate of CMF_TOPOLOGY_GLOBAL_CFG_5_P0_REG

#define CMI_1_MAD_SLICE_P0_REG                                         (0x000118A8)
//Duplicate of CMI_MAD_SLICE_P0_REG

#define CMI_1_MEMORY_SLICE_HASH_P0_REG                                 (0x000118AC)
//Duplicate of CMI_MEMORY_SLICE_HASH_P0_REG

#define CMI_1_REMAP_BASE_P0_REG                                        (0x000118B0)
//Duplicate of CMI_REMAP_BASE_P0_REG

#define CMI_1_REMAP_LIMIT_P0_REG                                       (0x000118B8)
//Duplicate of CMI_REMAP_LIMIT_P0_REG

#define CMI_1_TOLUD_P0_REG                                             (0x000118C0)
//Duplicate of CMI_TOLUD_P0_REG

#define CMI_1_MAD_SLICE_NM_P0_REG                                      (0x000118C4)
//Duplicate of CMI_MAD_SLICE_P0_REG

#define CMI_1_MEMORY_SLICE_HASH_NM_P0_REG                              (0x000118C8)
//Duplicate of CMI_MEMORY_SLICE_HASH_P0_REG

#define CMI_1_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_P0_REG             (0x000118D0)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_P0_REG

#define CMI_1_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_P0_REG             (0x000118D4)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_P0_REG

#define CMI_1_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_P0_REG             (0x000118D8)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_P0_REG

#define CMI_1_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_P0_REG             (0x000118DC)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_P0_REG

#define CMI_1_REQUEST_PORT_0_REQ_CONFIG_1_P0_REG                       (0x000118E0)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_1_P0_REG

#define CMI_1_REQUEST_PORT_0_STALL_P0_REG                              (0x000118E4)
//Duplicate of CMI_REQUEST_PORT_0_STALL_P0_REG

#define CMI_1_REQUEST_PORT_0_RESERVED_0_P0_REG                         (0x000118E8)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_REQUEST_PORT_0_RESERVED_1_P0_REG                         (0x000118EC)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_REQUEST_PORT_0_RESERVED_2_P0_REG                         (0x000118F0)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_REQUEST_PORT_0_ACCUM_REQ_IN_P0_REG                       (0x000118F4)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_REQ_IN_P0_REG

#define CMI_1_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_P0_REG                   (0x000118F8)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_P0_REG

#define CMI_1_REQUEST_PORT_0_ACCUM_RSP_OUT_P0_REG                      (0x000118FC)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_P0_REG

#define CMI_1_REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_P0_REG             (0x00011900)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_P0_REG

#define CMI_1_REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_P0_REG             (0x00011904)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_P0_REG

#define CMI_1_REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_P0_REG             (0x00011908)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_P0_REG

#define CMI_1_REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_P0_REG             (0x0001190C)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_P0_REG

#define CMI_1_REQUEST_PORT_1_REQ_CONFIG_1_P0_REG                       (0x00011910)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_1_P0_REG

#define CMI_1_REQUEST_PORT_1_STALL_P0_REG                              (0x00011914)
//Duplicate of CMI_REQUEST_PORT_0_STALL_P0_REG

#define CMI_1_REQUEST_PORT_1_RESERVED_0_P0_REG                         (0x00011918)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_REQUEST_PORT_1_RESERVED_1_P0_REG                         (0x0001191C)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_REQUEST_PORT_1_RESERVED_2_P0_REG                         (0x00011920)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_REQUEST_PORT_1_ACCUM_REQ_IN_P0_REG                       (0x00011924)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_REQ_IN_P0_REG

#define CMI_1_REQUEST_PORT_1_ACCUM_RD_CPL_OUT_P0_REG                   (0x00011928)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_P0_REG

#define CMI_1_REQUEST_PORT_1_ACCUM_RSP_OUT_P0_REG                      (0x0001192C)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_P0_REG

#define CMI_1_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_P0_REG             (0x00011930)
//Duplicate of CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_P0_REG

#define CMI_1_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_P0_REG             (0x00011934)
//Duplicate of CMI_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_P0_REG

#define CMI_1_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_P0_REG             (0x00011938)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_P0_REG

#define CMI_1_REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_P0_REG             (0x0001193C)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_P0_REG

#define CMI_1_REQUEST_PORT_2_REQ_CONFIG_1_P0_REG                       (0x00011940)
//Duplicate of CMI_REQUEST_PORT_2_REQ_CONFIG_1_P0_REG

#define CMI_1_REQUEST_PORT_2_STALL_P0_REG                              (0x00011944)
//Duplicate of CMI_REQUEST_PORT_0_STALL_P0_REG

#define CMI_1_REQUEST_PORT_2_RESERVED_0_P0_REG                         (0x00011948)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_REQUEST_PORT_2_RESERVED_1_P0_REG                         (0x0001194C)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_REQUEST_PORT_2_RESERVED_2_P0_REG                         (0x00011950)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_REQUEST_PORT_2_ACCUM_REQ_IN_P0_REG                       (0x00011954)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_REQ_IN_P0_REG

#define CMI_1_REQUEST_PORT_2_ACCUM_RD_CPL_OUT_P0_REG                   (0x00011958)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_P0_REG

#define CMI_1_REQUEST_PORT_2_ACCUM_RSP_OUT_P0_REG                      (0x0001195C)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_P0_REG

#define CMI_1_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_P0_REG             (0x00011960)
//Duplicate of CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_P0_REG

#define CMI_1_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_P0_REG             (0x00011964)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_P0_REG

#define CMI_1_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_P0_REG             (0x00011968)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_P0_REG

#define CMI_1_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_P0_REG             (0x0001196C)
//Duplicate of CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_P0_REG

#define CMI_1_REQUEST_PORT_3_REQ_CONFIG_1_P0_REG                       (0x00011970)
//Duplicate of CMI_REQUEST_PORT_3_REQ_CONFIG_1_P0_REG

#define CMI_1_REQUEST_PORT_3_STALL_P0_REG                              (0x00011974)
//Duplicate of CMI_REQUEST_PORT_0_STALL_P0_REG

#define CMI_1_REQUEST_PORT_3_RESERVED_0_P0_REG                         (0x00011978)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_REQUEST_PORT_3_RESERVED_1_P0_REG                         (0x0001197C)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_REQUEST_PORT_3_RESERVED_2_P0_REG                         (0x00011980)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_REQUEST_PORT_3_ACCUM_REQ_IN_P0_REG                       (0x00011984)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_REQ_IN_P0_REG

#define CMI_1_REQUEST_PORT_3_ACCUM_RD_CPL_OUT_P0_REG                   (0x00011988)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_P0_REG

#define CMI_1_REQUEST_PORT_3_ACCUM_RSP_OUT_P0_REG                      (0x0001198C)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_P0_REG

#define CMI_1_REQUEST_PORT_4_REQ_CONFIG_0_CHANNEL_0_P0_REG             (0x00011990)
//Duplicate of CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_P0_REG

#define CMI_1_REQUEST_PORT_4_REQ_CONFIG_0_CHANNEL_1_P0_REG             (0x00011994)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_P0_REG

#define CMI_1_REQUEST_PORT_4_REQ_CONFIG_0_CHANNEL_2_P0_REG             (0x00011998)
//Duplicate of CMI_REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_P0_REG

#define CMI_1_REQUEST_PORT_4_REQ_CONFIG_0_CHANNEL_3_P0_REG             (0x0001199C)
//Duplicate of CMI_REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_P0_REG

#define CMI_1_REQUEST_PORT_4_REQ_CONFIG_1_P0_REG                       (0x000119A0)
//Duplicate of CMI_REQUEST_PORT_3_REQ_CONFIG_1_P0_REG

#define CMI_1_REQUEST_PORT_4_STALL_P0_REG                              (0x000119A4)
//Duplicate of CMI_REQUEST_PORT_0_STALL_P0_REG

#define CMI_1_REQUEST_PORT_4_RESERVED_0_P0_REG                         (0x000119A8)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_REQUEST_PORT_4_RESERVED_1_P0_REG                         (0x000119AC)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_REQUEST_PORT_4_RESERVED_2_P0_REG                         (0x000119B0)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_REQUEST_PORT_4_ACCUM_REQ_IN_P0_REG                       (0x000119B4)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_REQ_IN_P0_REG

#define CMI_1_REQUEST_PORT_4_ACCUM_RD_CPL_OUT_P0_REG                   (0x000119B8)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_P0_REG

#define CMI_1_REQUEST_PORT_4_ACCUM_RSP_OUT_P0_REG                      (0x000119BC)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_P0_REG

#define CMI_1_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_P0_REG             (0x00011A80)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_P0_REG             (0x00011A84)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_P0_REG             (0x00011A88)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_P0_REG             (0x00011A8C)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_P0_REG

#define CMI_1_RESPOND_PORT_0_CPL_CONFIG_1_P0_REG                       (0x00011A90)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_1_P0_REG

#define CMI_1_RESPOND_PORT_0_STALL_P0_REG                              (0x00011A94)
//Duplicate of CMI_RESPOND_PORT_0_STALL_P0_REG

#define CMI_1_RESPOND_PORT_0_RESERVED_0_P0_REG                         (0x00011A98)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_RESPOND_PORT_0_RESERVED_1_P0_REG                         (0x00011A9C)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_RESPOND_PORT_0_RESERVED_2_P0_REG                         (0x00011AA0)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_RESPOND_PORT_0_ACCUM_REQ_OUT_P0_REG                      (0x00011AA4)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_REQ_IN_P0_REG

#define CMI_1_RESPOND_PORT_0_ACCUM_RD_CPL_IN_P0_REG                    (0x00011AA8)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_P0_REG

#define CMI_1_RESPOND_PORT_0_ACCUM_RSP_IN_P0_REG                       (0x00011AAC)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_P0_REG

#define CMI_1_RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_P0_REG             (0x00011AB0)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_P0_REG             (0x00011AB4)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_P0_REG             (0x00011AB8)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_P0_REG             (0x00011ABC)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_P0_REG

#define CMI_1_RESPOND_PORT_1_CPL_CONFIG_1_P0_REG                       (0x00011AC0)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_1_P0_REG

#define CMI_1_RESPOND_PORT_1_STALL_P0_REG                              (0x00011AC4)
//Duplicate of CMI_RESPOND_PORT_0_STALL_P0_REG

#define CMI_1_RESPOND_PORT_1_RESERVED_0_P0_REG                         (0x00011AC8)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_RESPOND_PORT_1_RESERVED_1_P0_REG                         (0x00011ACC)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_RESPOND_PORT_1_RESERVED_2_P0_REG                         (0x00011AD0)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_RESPOND_PORT_1_ACCUM_REQ_OUT_P0_REG                      (0x00011AD4)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_REQ_IN_P0_REG

#define CMI_1_RESPOND_PORT_1_ACCUM_RD_CPL_IN_P0_REG                    (0x00011AD8)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_P0_REG

#define CMI_1_RESPOND_PORT_1_ACCUM_RSP_IN_P0_REG                       (0x00011ADC)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_P0_REG

#define CMI_1_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_P0_REG             (0x00011AE0)
//Duplicate of CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_P0_REG             (0x00011AE4)
//Duplicate of CMI_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_P0_REG             (0x00011AE8)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_P0_REG             (0x00011AEC)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_2_CPL_CONFIG_1_P0_REG                       (0x00011AF0)
//Duplicate of CMI_RESPOND_PORT_2_CPL_CONFIG_1_P0_REG

#define CMI_1_RESPOND_PORT_2_STALL_P0_REG                              (0x00011AF4)
//Duplicate of CMI_RESPOND_PORT_0_STALL_P0_REG

#define CMI_1_RESPOND_PORT_2_RESERVED_0_P0_REG                         (0x00011AF8)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_RESPOND_PORT_2_RESERVED_1_P0_REG                         (0x00011AFC)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_P0_REG          (0x00011B00)
//Duplicate of CMI_RESPOND_PORT_2_FIRST_LEVEL_BID_PARK_SIZE_P0_REG

#define CMI_1_RESPOND_PORT_2_ACCUM_REQ_OUT_P0_REG                      (0x00011B04)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_REQ_IN_P0_REG

#define CMI_1_RESPOND_PORT_2_ACCUM_RD_CPL_IN_P0_REG                    (0x00011B08)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_P0_REG

#define CMI_1_RESPOND_PORT_2_ACCUM_RSP_IN_P0_REG                       (0x00011B0C)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_P0_REG

#define CMI_1_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_P0_REG             (0x00011B10)
//Duplicate of CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_P0_REG             (0x00011B14)
//Duplicate of CMI_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_P0_REG             (0x00011B18)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_P0_REG             (0x00011B1C)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_3_CPL_CONFIG_1_P0_REG                       (0x00011B20)
//Duplicate of CMI_RESPOND_PORT_3_CPL_CONFIG_1_P0_REG

#define CMI_1_RESPOND_PORT_3_STALL_P0_REG                              (0x00011B24)
//Duplicate of CMI_RESPOND_PORT_0_STALL_P0_REG

#define CMI_1_RESPOND_PORT_3_RESERVED_0_P0_REG                         (0x00011B28)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_RESPOND_PORT_3_RESERVED_1_P0_REG                         (0x00011B2C)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_RESPOND_PORT_3_RESERVED_2_P0_REG                         (0x00011B30)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_RESPOND_PORT_3_ACCUM_REQ_OUT_P0_REG                      (0x00011B34)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_REQ_IN_P0_REG

#define CMI_1_RESPOND_PORT_3_ACCUM_RD_CPL_IN_P0_REG                    (0x00011B38)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_P0_REG

#define CMI_1_RESPOND_PORT_3_ACCUM_RSP_IN_P0_REG                       (0x00011B3C)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_P0_REG

#define CMI_1_RESPOND_PORT_4_CPL_CONFIG_0_CHANNEL_0_P0_REG             (0x00011B40)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_4_CPL_CONFIG_0_CHANNEL_1_P0_REG             (0x00011B44)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_4_CPL_CONFIG_0_CHANNEL_2_P0_REG             (0x00011B48)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_4_CPL_CONFIG_0_CHANNEL_3_P0_REG             (0x00011B4C)
//Duplicate of CMI_RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_4_CPL_CONFIG_1_P0_REG                       (0x00011B50)
//Duplicate of CMI_RESPOND_PORT_4_CPL_CONFIG_1_P0_REG

#define CMI_1_RESPOND_PORT_4_STALL_P0_REG                              (0x00011B54)
//Duplicate of CMI_RESPOND_PORT_0_STALL_P0_REG

#define CMI_1_RESPOND_PORT_4_RESERVED_0_P0_REG                         (0x00011B58)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_RESPOND_PORT_4_RESERVED_1_P0_REG                         (0x00011B5C)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_RESPOND_PORT_4_RESERVED_2_P0_REG                         (0x00011B60)
//Duplicate of CMF_RSVD0_P0_REG

#define CMI_1_RESPOND_PORT_4_ACCUM_REQ_OUT_P0_REG                      (0x00011B64)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_REQ_IN_P0_REG

#define CMI_1_RESPOND_PORT_4_ACCUM_RD_CPL_IN_P0_REG                    (0x00011B68)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RD_CPL_OUT_P0_REG

#define CMI_1_RESPOND_PORT_4_ACCUM_RSP_IN_P0_REG                       (0x00011B6C)
//Duplicate of CMI_REQUEST_PORT_0_ACCUM_RSP_OUT_P0_REG

#define CMF_1_LT_MEM_SA_PG_ACCESS_POLICY_CP_P0_REG                     (0x00011C00)
//Duplicate of CMF_LT_SA_W_PG_ACCESS_POLICY_CP_P0_REG

#define CMF_1_LT_MEM_SA_PG_ACCESS_POLICY_WAC_P0_REG                    (0x00011C08)
//Duplicate of CMF_LT_SA_W_PG_ACCESS_POLICY_WAC_P0_REG

#define CMF_1_LT_MEM_SA_PG_ACCESS_POLICY_RAC_P0_REG                    (0x00011C10)
//Duplicate of CMF_LT_SA_W_PG_ACCESS_POLICY_RAC_P0_REG

#define CMF_1_OS_PG_ACCESS_POLICY_CP_P0_REG                            (0x00011C18)
//Duplicate of CMF_LT_SA_W_PG_ACCESS_POLICY_CP_P0_REG

#define CMF_1_OS_PG_ACCESS_POLICY_WAC_P0_REG                           (0x00011C20)
//Duplicate of CMF_OS_PG_ACCESS_POLICY_WAC_P0_REG

#define CMF_1_OS_PG_ACCESS_POLICY_RAC_P0_REG                           (0x00011C28)
//Duplicate of CMF_LT_SA_W_PG_ACCESS_POLICY_RAC_P0_REG

#define CMI_1_PARITY_ERR_LOG_P0_REG                                    (0x00011C48)
//Duplicate of CMI_PARITY_ERR_LOG_P0_REG

#define CMI_1_PARITY_ERR_INJ_P0_REG                                    (0x00011C50)
//Duplicate of CMI_PARITY_ERR_INJ_P0_REG

#define CMI_1_PARITY_CONTROL_P0_REG                                    (0x00011C54)
//Duplicate of CMI_PARITY_CONTROL_P0_REG

#define CMI_1_REQ_L3_ARB_CONFIG_P0_REG                                 (0x00011C5C)
//Duplicate of CMI_REQ_L3_ARB_CONFIG_P0_REG

#define IOP_CMI_1_EP_ARB_CTL_P0_REG                                    (0x00011C68)
//Duplicate of IOP_CMI_EP_ARB_CTL_P0_REG

#define CMI_1_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_REG               (0x00011C80)
//Duplicate of CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_0_RD_COUNTER_CHANNEL_1_P0_REG               (0x00011C88)
//Duplicate of CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_0_RD_COUNTER_CHANNEL_3_P0_REG               (0x00011C98)
//Duplicate of CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_REG               (0x00011CA0)
//Duplicate of CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_0_WR_COUNTER_CHANNEL_1_P0_REG               (0x00011CA8)
//Duplicate of CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_0_WR_COUNTER_CHANNEL_3_P0_REG               (0x00011CB8)
//Duplicate of CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_1_RD_COUNTER_CHANNEL_0_P0_REG               (0x00011CC0)
//Duplicate of CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_1_RD_COUNTER_CHANNEL_1_P0_REG               (0x00011CC8)
//Duplicate of CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_1_RD_COUNTER_CHANNEL_3_P0_REG               (0x00011CD8)
//Duplicate of CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_1_WR_COUNTER_CHANNEL_0_P0_REG               (0x00011CE0)
//Duplicate of CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_1_WR_COUNTER_CHANNEL_1_P0_REG               (0x00011CE8)
//Duplicate of CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_1_WR_COUNTER_CHANNEL_3_P0_REG               (0x00011CF8)
//Duplicate of CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_2_RD_COUNTER_CHANNEL_0_P0_REG               (0x00011D00)
//Duplicate of CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_2_WR_COUNTER_CHANNEL_0_P0_REG               (0x00011D08)
//Duplicate of CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_2_RD_COUNTER_CHANNEL_1_P0_REG               (0x00011D20)
//Duplicate of CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_2_WR_COUNTER_CHANNEL_1_P0_REG               (0x00011D28)
//Duplicate of CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_3_RD_COUNTER_CHANNEL_0_P0_REG               (0x00011D40)
//Duplicate of CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_3_WR_COUNTER_CHANNEL_0_P0_REG               (0x00011D48)
//Duplicate of CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_3_RD_COUNTER_CHANNEL_1_P0_REG               (0x00011D60)
//Duplicate of CMI_RESPOND_PORT_0_RD_COUNTER_CHANNEL_0_P0_REG

#define CMI_1_RESPOND_PORT_3_WR_COUNTER_CHANNEL_1_P0_REG               (0x00011D68)
//Duplicate of CMI_RESPOND_PORT_0_WR_COUNTER_CHANNEL_0_P0_REG
#pragma pack(pop)
#endif
