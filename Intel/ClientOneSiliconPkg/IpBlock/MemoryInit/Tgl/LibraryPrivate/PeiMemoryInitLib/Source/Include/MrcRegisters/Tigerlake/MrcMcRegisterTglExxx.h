#ifndef __MrcMcRegisterTglExxx_h__
#define __MrcMcRegisterTglExxx_h__
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


#define MC0_CH0_CR_TC_PRE_P0_REG                                       (0x0000E000)

  #define MC0_CH0_CR_TC_PRE_tRP_P0_OFF                                 ( 0)
  #define MC0_CH0_CR_TC_PRE_tRP_P0_WID                                 ( 7)
  #define MC0_CH0_CR_TC_PRE_tRP_P0_MSK                                 (0x0000007F)
  #define MC0_CH0_CR_TC_PRE_tRP_P0_MIN                                 (0)
  #define MC0_CH0_CR_TC_PRE_tRP_P0_MAX                                 (127) // 0x0000007F
  #define MC0_CH0_CR_TC_PRE_tRP_P0_DEF                                 (0x00000008)
  #define MC0_CH0_CR_TC_PRE_tRP_P0_HSH                                 (0x4700E000)

  #define MC0_CH0_CR_TC_PRE_tRPab_ext_P0_OFF                           ( 7)
  #define MC0_CH0_CR_TC_PRE_tRPab_ext_P0_WID                           ( 4)
  #define MC0_CH0_CR_TC_PRE_tRPab_ext_P0_MSK                           (0x00000780)
  #define MC0_CH0_CR_TC_PRE_tRPab_ext_P0_MIN                           (0)
  #define MC0_CH0_CR_TC_PRE_tRPab_ext_P0_MAX                           (15) // 0x0000000F
  #define MC0_CH0_CR_TC_PRE_tRPab_ext_P0_DEF                           (0x00000000)
  #define MC0_CH0_CR_TC_PRE_tRPab_ext_P0_HSH                           (0x440EE000)

  #define MC0_CH0_CR_TC_PRE_tRDPRE_P0_OFF                              (11)
  #define MC0_CH0_CR_TC_PRE_tRDPRE_P0_WID                              ( 6)
  #define MC0_CH0_CR_TC_PRE_tRDPRE_P0_MSK                              (0x0001F800)
  #define MC0_CH0_CR_TC_PRE_tRDPRE_P0_MIN                              (0)
  #define MC0_CH0_CR_TC_PRE_tRDPRE_P0_MAX                              (63) // 0x0000003F
  #define MC0_CH0_CR_TC_PRE_tRDPRE_P0_DEF                              (0x00000006)
  #define MC0_CH0_CR_TC_PRE_tRDPRE_P0_HSH                              (0x4616E000)

  #define MC0_CH0_CR_TC_PRE_tPPD_P0_OFF                                (17)
  #define MC0_CH0_CR_TC_PRE_tPPD_P0_WID                                ( 4)
  #define MC0_CH0_CR_TC_PRE_tPPD_P0_MSK                                (0x001E0000)
  #define MC0_CH0_CR_TC_PRE_tPPD_P0_MIN                                (0)
  #define MC0_CH0_CR_TC_PRE_tPPD_P0_MAX                                (15) // 0x0000000F
  #define MC0_CH0_CR_TC_PRE_tPPD_P0_DEF                                (0x00000004)
  #define MC0_CH0_CR_TC_PRE_tPPD_P0_HSH                                (0x4422E000)

  #define MC0_CH0_CR_TC_PRE_tWRPRE_P0_OFF                              (21)
  #define MC0_CH0_CR_TC_PRE_tWRPRE_P0_WID                              ( 9)
  #define MC0_CH0_CR_TC_PRE_tWRPRE_P0_MSK                              (0x3FE00000)
  #define MC0_CH0_CR_TC_PRE_tWRPRE_P0_MIN                              (0)
  #define MC0_CH0_CR_TC_PRE_tWRPRE_P0_MAX                              (511) // 0x000001FF
  #define MC0_CH0_CR_TC_PRE_tWRPRE_P0_DEF                              (0x00000018)
  #define MC0_CH0_CR_TC_PRE_tWRPRE_P0_HSH                              (0x492AE000)

  #define MC0_CH0_CR_TC_PRE_tRAS_P0_OFF                                (33)
  #define MC0_CH0_CR_TC_PRE_tRAS_P0_WID                                ( 8)
  #define MC0_CH0_CR_TC_PRE_tRAS_P0_MSK                                (0x000001FE00000000ULL)
  #define MC0_CH0_CR_TC_PRE_tRAS_P0_MIN                                (0)
  #define MC0_CH0_CR_TC_PRE_tRAS_P0_MAX                                (255) // 0x000000FF
  #define MC0_CH0_CR_TC_PRE_tRAS_P0_DEF                                (0x0000001C)
  #define MC0_CH0_CR_TC_PRE_tRAS_P0_HSH                                (0x4842E000)

  #define MC0_CH0_CR_TC_PRE_tRCD_P0_OFF                                (41)
  #define MC0_CH0_CR_TC_PRE_tRCD_P0_WID                                ( 7)
  #define MC0_CH0_CR_TC_PRE_tRCD_P0_MSK                                (0x0000FE0000000000ULL)
  #define MC0_CH0_CR_TC_PRE_tRCD_P0_MIN                                (0)
  #define MC0_CH0_CR_TC_PRE_tRCD_P0_MAX                                (127) // 0x0000007F
  #define MC0_CH0_CR_TC_PRE_tRCD_P0_DEF                                (0x00000008)
  #define MC0_CH0_CR_TC_PRE_tRCD_P0_HSH                                (0x4752E000)

#define MC0_CH0_CR_TC_ACT_P0_REG                                       (0x0000E008)

  #define MC0_CH0_CR_TC_ACT_tFAW_P0_OFF                                ( 0)
  #define MC0_CH0_CR_TC_ACT_tFAW_P0_WID                                ( 8)
  #define MC0_CH0_CR_TC_ACT_tFAW_P0_MSK                                (0x000000FF)
  #define MC0_CH0_CR_TC_ACT_tFAW_P0_MIN                                (0)
  #define MC0_CH0_CR_TC_ACT_tFAW_P0_MAX                                (255) // 0x000000FF
  #define MC0_CH0_CR_TC_ACT_tFAW_P0_DEF                                (0x00000010)
  #define MC0_CH0_CR_TC_ACT_tFAW_P0_HSH                                (0x0800E008)

  #define MC0_CH0_CR_TC_ACT_tRRD_sg_P0_OFF                             ( 8)
  #define MC0_CH0_CR_TC_ACT_tRRD_sg_P0_WID                             ( 6)
  #define MC0_CH0_CR_TC_ACT_tRRD_sg_P0_MSK                             (0x00003F00)
  #define MC0_CH0_CR_TC_ACT_tRRD_sg_P0_MIN                             (0)
  #define MC0_CH0_CR_TC_ACT_tRRD_sg_P0_MAX                             (63) // 0x0000003F
  #define MC0_CH0_CR_TC_ACT_tRRD_sg_P0_DEF                             (0x00000004)
  #define MC0_CH0_CR_TC_ACT_tRRD_sg_P0_HSH                             (0x0610E008)

  #define MC0_CH0_CR_TC_ACT_tRRD_dg_P0_OFF                             (14)
  #define MC0_CH0_CR_TC_ACT_tRRD_dg_P0_WID                             ( 6)
  #define MC0_CH0_CR_TC_ACT_tRRD_dg_P0_MSK                             (0x000FC000)
  #define MC0_CH0_CR_TC_ACT_tRRD_dg_P0_MIN                             (0)
  #define MC0_CH0_CR_TC_ACT_tRRD_dg_P0_MAX                             (63) // 0x0000003F
  #define MC0_CH0_CR_TC_ACT_tRRD_dg_P0_DEF                             (0x00000004)
  #define MC0_CH0_CR_TC_ACT_tRRD_dg_P0_HSH                             (0x061CE008)

  #define MC0_CH0_CR_TC_ACT_derating_ext_P0_OFF                        (20)
  #define MC0_CH0_CR_TC_ACT_derating_ext_P0_WID                        ( 4)
  #define MC0_CH0_CR_TC_ACT_derating_ext_P0_MSK                        (0x00F00000)
  #define MC0_CH0_CR_TC_ACT_derating_ext_P0_MIN                        (0)
  #define MC0_CH0_CR_TC_ACT_derating_ext_P0_MAX                        (15) // 0x0000000F
  #define MC0_CH0_CR_TC_ACT_derating_ext_P0_DEF                        (0x00000002)
  #define MC0_CH0_CR_TC_ACT_derating_ext_P0_HSH                        (0x0428E008)

  #define MC0_CH0_CR_TC_ACT_trefsbrd_P0_OFF                            (24)
  #define MC0_CH0_CR_TC_ACT_trefsbrd_P0_WID                            ( 8)
  #define MC0_CH0_CR_TC_ACT_trefsbrd_P0_MSK                            (0xFF000000)
  #define MC0_CH0_CR_TC_ACT_trefsbrd_P0_MIN                            (0)
  #define MC0_CH0_CR_TC_ACT_trefsbrd_P0_MAX                            (255) // 0x000000FF
  #define MC0_CH0_CR_TC_ACT_trefsbrd_P0_DEF                            (0x00000018)
  #define MC0_CH0_CR_TC_ACT_trefsbrd_P0_HSH                            (0x0830E008)

#define MC0_CH0_CR_TC_RDRD_P0_REG                                      (0x0000E00C)

  #define MC0_CH0_CR_TC_RDRD_tRDRD_sg_P0_OFF                           ( 0)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_sg_P0_WID                           ( 6)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_sg_P0_MSK                           (0x0000003F)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_sg_P0_MIN                           (0)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_sg_P0_MAX                           (63) // 0x0000003F
  #define MC0_CH0_CR_TC_RDRD_tRDRD_sg_P0_DEF                           (0x00000004)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_sg_P0_HSH                           (0x0600E00C)

  #define MC0_CH0_CR_TC_RDRD_tRDRD_dg_P0_OFF                           ( 8)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dg_P0_WID                           ( 6)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dg_P0_MSK                           (0x00003F00)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dg_P0_MIN                           (0)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dg_P0_MAX                           (63) // 0x0000003F
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dg_P0_DEF                           (0x00000004)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dg_P0_HSH                           (0x0610E00C)

  #define MC0_CH0_CR_TC_RDRD_tRDRD_dr_P0_OFF                           (16)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dr_P0_WID                           ( 7)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dr_P0_MSK                           (0x007F0000)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dr_P0_MIN                           (0)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dr_P0_MAX                           (127) // 0x0000007F
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dr_P0_DEF                           (0x00000004)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dr_P0_HSH                           (0x0720E00C)

  #define MC0_CH0_CR_TC_RDRD_tRDRD_dd_P0_OFF                           (24)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dd_P0_WID                           ( 7)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dd_P0_MSK                           (0x7F000000)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dd_P0_MIN                           (0)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dd_P0_MAX                           (127) // 0x0000007F
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dd_P0_DEF                           (0x00000004)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dd_P0_HSH                           (0x0730E00C)

#define MC0_CH0_CR_TC_RDWR_P0_REG                                      (0x0000E010)

  #define MC0_CH0_CR_TC_RDWR_tRDWR_sg_P0_OFF                           ( 0)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_sg_P0_WID                           ( 7)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_sg_P0_MSK                           (0x0000007F)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_sg_P0_MIN                           (0)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_sg_P0_MAX                           (127) // 0x0000007F
  #define MC0_CH0_CR_TC_RDWR_tRDWR_sg_P0_DEF                           (0x00000004)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_sg_P0_HSH                           (0x0700E010)

  #define MC0_CH0_CR_TC_RDWR_tRDWR_dg_P0_OFF                           ( 8)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dg_P0_WID                           ( 7)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dg_P0_MSK                           (0x00007F00)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dg_P0_MIN                           (0)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dg_P0_MAX                           (127) // 0x0000007F
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dg_P0_DEF                           (0x00000004)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dg_P0_HSH                           (0x0710E010)

  #define MC0_CH0_CR_TC_RDWR_tRDWR_dr_P0_OFF                           (16)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dr_P0_WID                           ( 7)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dr_P0_MSK                           (0x007F0000)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dr_P0_MIN                           (0)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dr_P0_MAX                           (127) // 0x0000007F
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dr_P0_DEF                           (0x00000004)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dr_P0_HSH                           (0x0720E010)

  #define MC0_CH0_CR_TC_RDWR_tRDWR_dd_P0_OFF                           (24)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dd_P0_WID                           ( 7)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dd_P0_MSK                           (0x7F000000)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dd_P0_MIN                           (0)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dd_P0_MAX                           (127) // 0x0000007F
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dd_P0_DEF                           (0x00000004)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dd_P0_HSH                           (0x0730E010)

#define MC0_CH0_CR_TC_WRRD_P0_REG                                      (0x0000E014)

  #define MC0_CH0_CR_TC_WRRD_tWRRD_sg_P0_OFF                           ( 0)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_sg_P0_WID                           ( 8)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_sg_P0_MSK                           (0x000000FF)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_sg_P0_MIN                           (0)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_sg_P0_MAX                           (255) // 0x000000FF
  #define MC0_CH0_CR_TC_WRRD_tWRRD_sg_P0_DEF                           (0x00000004)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_sg_P0_HSH                           (0x0800E014)

  #define MC0_CH0_CR_TC_WRRD_tWRRD_dg_P0_OFF                           ( 8)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dg_P0_WID                           ( 8)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dg_P0_MSK                           (0x0000FF00)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dg_P0_MIN                           (0)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dg_P0_MAX                           (255) // 0x000000FF
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dg_P0_DEF                           (0x00000004)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dg_P0_HSH                           (0x0810E014)

  #define MC0_CH0_CR_TC_WRRD_tWRRD_dr_P0_OFF                           (16)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dr_P0_WID                           ( 6)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dr_P0_MSK                           (0x003F0000)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dr_P0_MIN                           (0)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dr_P0_MAX                           (63) // 0x0000003F
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dr_P0_DEF                           (0x00000004)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dr_P0_HSH                           (0x0620E014)

  #define MC0_CH0_CR_TC_WRRD_tWRRD_dd_P0_OFF                           (24)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dd_P0_WID                           ( 6)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dd_P0_MSK                           (0x3F000000)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dd_P0_MIN                           (0)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dd_P0_MAX                           (63) // 0x0000003F
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dd_P0_DEF                           (0x00000004)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dd_P0_HSH                           (0x0630E014)

#define MC0_CH0_CR_TC_WRWR_P0_REG                                      (0x0000E018)

  #define MC0_CH0_CR_TC_WRWR_tWRWR_sg_P0_OFF                           ( 0)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_sg_P0_WID                           ( 7)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_sg_P0_MSK                           (0x0000007F)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_sg_P0_MIN                           (0)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_sg_P0_MAX                           (127) // 0x0000007F
  #define MC0_CH0_CR_TC_WRWR_tWRWR_sg_P0_DEF                           (0x00000004)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_sg_P0_HSH                           (0x0700E018)

  #define MC0_CH0_CR_TC_WRWR_tWRWR_dg_P0_OFF                           ( 8)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dg_P0_WID                           ( 6)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dg_P0_MSK                           (0x00003F00)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dg_P0_MIN                           (0)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dg_P0_MAX                           (63) // 0x0000003F
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dg_P0_DEF                           (0x00000004)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dg_P0_HSH                           (0x0610E018)

  #define MC0_CH0_CR_TC_WRWR_tWRWR_dr_P0_OFF                           (16)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dr_P0_WID                           ( 6)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dr_P0_MSK                           (0x003F0000)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dr_P0_MIN                           (0)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dr_P0_MAX                           (63) // 0x0000003F
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dr_P0_DEF                           (0x00000004)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dr_P0_HSH                           (0x0620E018)

  #define MC0_CH0_CR_TC_WRWR_tWRWR_dd_P0_OFF                           (24)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dd_P0_WID                           ( 7)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dd_P0_MSK                           (0x7F000000)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dd_P0_MIN                           (0)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dd_P0_MAX                           (127) // 0x0000007F
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dd_P0_DEF                           (0x00000004)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dd_P0_HSH                           (0x0730E018)

#define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_P0_REG                         (0x0000E020)

  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_0_latency_P0_OFF        ( 0)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_0_latency_P0_WID        ( 8)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_0_latency_P0_MSK        (0x000000FF)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_0_latency_P0_MIN        (0)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_0_latency_P0_MAX        (255) // 0x000000FF
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_0_latency_P0_DEF        (0x00000019)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_0_latency_P0_HSH        (0x4800E020)

  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_1_latency_P0_OFF        ( 8)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_1_latency_P0_WID        ( 8)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_1_latency_P0_MSK        (0x0000FF00)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_1_latency_P0_MIN        (0)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_1_latency_P0_MAX        (255) // 0x000000FF
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_1_latency_P0_DEF        (0x00000019)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_1_latency_P0_HSH        (0x4810E020)

  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_2_latency_P0_OFF        (16)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_2_latency_P0_WID        ( 8)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_2_latency_P0_MSK        (0x00FF0000)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_2_latency_P0_MIN        (0)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_2_latency_P0_MAX        (255) // 0x000000FF
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_2_latency_P0_DEF        (0x00000019)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_2_latency_P0_HSH        (0x4820E020)

  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_3_latency_P0_OFF        (24)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_3_latency_P0_WID        ( 8)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_3_latency_P0_MSK        (0xFF000000)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_3_latency_P0_MIN        (0)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_3_latency_P0_MAX        (255) // 0x000000FF
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_3_latency_P0_DEF        (0x00000019)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_3_latency_P0_HSH        (0x4830E020)

  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_4_latency_P0_OFF        (32)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_4_latency_P0_WID        ( 8)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_4_latency_P0_MSK        (0x000000FF00000000ULL)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_4_latency_P0_MIN        (0)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_4_latency_P0_MAX        (255) // 0x000000FF
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_4_latency_P0_DEF        (0x00000019)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_4_latency_P0_HSH        (0x4840E020)

  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_5_latency_P0_OFF        (40)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_5_latency_P0_WID        ( 8)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_5_latency_P0_MSK        (0x0000FF0000000000ULL)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_5_latency_P0_MIN        (0)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_5_latency_P0_MAX        (255) // 0x000000FF
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_5_latency_P0_DEF        (0x00000019)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_5_latency_P0_HSH        (0x4850E020)

  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_6_latency_P0_OFF        (48)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_6_latency_P0_WID        ( 8)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_6_latency_P0_MSK        (0x00FF000000000000ULL)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_6_latency_P0_MIN        (0)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_6_latency_P0_MAX        (255) // 0x000000FF
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_6_latency_P0_DEF        (0x00000019)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_6_latency_P0_HSH        (0x4860E020)

  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_7_latency_P0_OFF        (56)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_7_latency_P0_WID        ( 8)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_7_latency_P0_MSK        (0xFF00000000000000ULL)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_7_latency_P0_MIN        (0)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_7_latency_P0_MAX        (255) // 0x000000FF
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_7_latency_P0_DEF        (0x00000019)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_7_latency_P0_HSH        (0x4870E020)

#define MC0_CH0_CR_SCHED_CBIT_P0_REG                                   (0x0000E028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_cas_P0_OFF                     ( 0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_cas_P0_WID                     ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_cas_P0_MSK                     (0x00000001)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_cas_P0_MIN                     (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_cas_P0_MAX                     (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_cas_P0_DEF                     (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_cas_P0_HSH                     (0x0100E028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_cas_P0_OFF                  ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_cas_P0_WID                  ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_cas_P0_MSK                  (0x00000002)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_cas_P0_MIN                  (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_cas_P0_MAX                  (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_cas_P0_DEF                  (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_cas_P0_HSH                  (0x0102E028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ras_P0_OFF                     ( 2)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ras_P0_WID                     ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ras_P0_MSK                     (0x00000004)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ras_P0_MIN                     (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ras_P0_MAX                     (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ras_P0_DEF                     (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ras_P0_HSH                     (0x0104E028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_ras_P0_OFF                  ( 3)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_ras_P0_WID                  ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_ras_P0_MSK                  (0x00000008)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_ras_P0_MIN                  (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_ras_P0_MAX                  (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_ras_P0_DEF                  (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_ras_P0_HSH                  (0x0106E028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_2c_byp_P0_OFF                      ( 4)
  #define MC0_CH0_CR_SCHED_CBIT_dis_2c_byp_P0_WID                      ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_2c_byp_P0_MSK                      (0x00000010)
  #define MC0_CH0_CR_SCHED_CBIT_dis_2c_byp_P0_MIN                      (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_2c_byp_P0_MAX                      (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_2c_byp_P0_DEF                      (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_2c_byp_P0_HSH                      (0x0108E028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_deprd_opt_P0_OFF                   ( 5)
  #define MC0_CH0_CR_SCHED_CBIT_dis_deprd_opt_P0_WID                   ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_deprd_opt_P0_MSK                   (0x00000020)
  #define MC0_CH0_CR_SCHED_CBIT_dis_deprd_opt_P0_MIN                   (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_deprd_opt_P0_MAX                   (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_deprd_opt_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_deprd_opt_P0_HSH                   (0x010AE028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_pt_it_P0_OFF                       ( 6)
  #define MC0_CH0_CR_SCHED_CBIT_dis_pt_it_P0_WID                       ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_pt_it_P0_MSK                       (0x00000040)
  #define MC0_CH0_CR_SCHED_CBIT_dis_pt_it_P0_MIN                       (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_pt_it_P0_MAX                       (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_pt_it_P0_DEF                       (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_pt_it_P0_HSH                       (0x010CE028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_ring_P0_OFF                  ( 7)
  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_ring_P0_WID                  ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_ring_P0_MSK                  (0x00000080)
  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_ring_P0_MIN                  (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_ring_P0_MAX                  (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_ring_P0_DEF                  (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_ring_P0_HSH                  (0x010EE028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_sa_P0_OFF                    ( 8)
  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_sa_P0_WID                    ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_sa_P0_MSK                    (0x00000100)
  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_sa_P0_MIN                    (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_sa_P0_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_sa_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_sa_P0_HSH                    (0x0110E028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_ph_P0_OFF                     ( 9)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_ph_P0_WID                     ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_ph_P0_MSK                     (0x00000200)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_ph_P0_MIN                     (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_ph_P0_MAX                     (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_ph_P0_DEF                     (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_ph_P0_HSH                     (0x0112E028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pe_P0_OFF                     (10)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pe_P0_WID                     ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pe_P0_MSK                     (0x00000400)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pe_P0_MIN                     (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pe_P0_MAX                     (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pe_P0_DEF                     (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pe_P0_HSH                     (0x0114E028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pm_P0_OFF                     (11)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pm_P0_WID                     ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pm_P0_MSK                     (0x00000800)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pm_P0_MIN                     (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pm_P0_MAX                     (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pm_P0_DEF                     (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pm_P0_HSH                     (0x0116E028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_odt_P0_OFF                         (12)
  #define MC0_CH0_CR_SCHED_CBIT_dis_odt_P0_WID                         ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_odt_P0_MSK                         (0x00001000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_odt_P0_MIN                         (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_odt_P0_MAX                         (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_odt_P0_DEF                         (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_odt_P0_HSH                         (0x0118E028)

  #define MC0_CH0_CR_SCHED_CBIT_OE_alw_off_P0_OFF                      (13)
  #define MC0_CH0_CR_SCHED_CBIT_OE_alw_off_P0_WID                      ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_OE_alw_off_P0_MSK                      (0x00002000)
  #define MC0_CH0_CR_SCHED_CBIT_OE_alw_off_P0_MIN                      (0)
  #define MC0_CH0_CR_SCHED_CBIT_OE_alw_off_P0_MAX                      (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_OE_alw_off_P0_DEF                      (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_OE_alw_off_P0_HSH                      (0x011AE028)

  #define MC0_CH0_CR_SCHED_CBIT_block_rpq_P0_OFF                       (14)
  #define MC0_CH0_CR_SCHED_CBIT_block_rpq_P0_WID                       ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_block_rpq_P0_MSK                       (0x00004000)
  #define MC0_CH0_CR_SCHED_CBIT_block_rpq_P0_MIN                       (0)
  #define MC0_CH0_CR_SCHED_CBIT_block_rpq_P0_MAX                       (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_block_rpq_P0_DEF                       (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_block_rpq_P0_HSH                       (0x011CE028)

  #define MC0_CH0_CR_SCHED_CBIT_block_ipq_P0_OFF                       (15)
  #define MC0_CH0_CR_SCHED_CBIT_block_ipq_P0_WID                       ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_block_ipq_P0_MSK                       (0x00008000)
  #define MC0_CH0_CR_SCHED_CBIT_block_ipq_P0_MIN                       (0)
  #define MC0_CH0_CR_SCHED_CBIT_block_ipq_P0_MAX                       (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_block_ipq_P0_DEF                       (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_block_ipq_P0_HSH                       (0x011EE028)

  #define MC0_CH0_CR_SCHED_CBIT_block_wpq_P0_OFF                       (16)
  #define MC0_CH0_CR_SCHED_CBIT_block_wpq_P0_WID                       ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_block_wpq_P0_MSK                       (0x00010000)
  #define MC0_CH0_CR_SCHED_CBIT_block_wpq_P0_MIN                       (0)
  #define MC0_CH0_CR_SCHED_CBIT_block_wpq_P0_MAX                       (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_block_wpq_P0_DEF                       (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_block_wpq_P0_HSH                       (0x0120E028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_zq_P0_OFF                          (17)
  #define MC0_CH0_CR_SCHED_CBIT_dis_zq_P0_WID                          ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_zq_P0_MSK                          (0x00020000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_zq_P0_MIN                          (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_zq_P0_MAX                          (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_zq_P0_DEF                          (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_zq_P0_HSH                          (0x0122E028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_tt_P0_OFF                          (18)
  #define MC0_CH0_CR_SCHED_CBIT_dis_tt_P0_WID                          ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_tt_P0_MSK                          (0x00040000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_tt_P0_MIN                          (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_tt_P0_MAX                          (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_tt_P0_DEF                          (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_tt_P0_HSH                          (0x0124E028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ref_P0_OFF                     (19)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ref_P0_WID                     ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ref_P0_MSK                     (0x00080000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ref_P0_MIN                     (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ref_P0_MAX                     (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ref_P0_DEF                     (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ref_P0_HSH                     (0x0126E028)

  #define MC0_CH0_CR_SCHED_CBIT_long_zq_P0_OFF                         (20)
  #define MC0_CH0_CR_SCHED_CBIT_long_zq_P0_WID                         ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_long_zq_P0_MSK                         (0x00100000)
  #define MC0_CH0_CR_SCHED_CBIT_long_zq_P0_MIN                         (0)
  #define MC0_CH0_CR_SCHED_CBIT_long_zq_P0_MAX                         (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_long_zq_P0_DEF                         (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_long_zq_P0_HSH                         (0x0128E028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_srx_zq_P0_OFF                      (21)
  #define MC0_CH0_CR_SCHED_CBIT_dis_srx_zq_P0_WID                      ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_srx_zq_P0_MSK                      (0x00200000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_srx_zq_P0_MIN                      (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_srx_zq_P0_MAX                      (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_srx_zq_P0_DEF                      (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_srx_zq_P0_HSH                      (0x012AE028)

  #define MC0_CH0_CR_SCHED_CBIT_serialize_zq_P0_OFF                    (22)
  #define MC0_CH0_CR_SCHED_CBIT_serialize_zq_P0_WID                    ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_serialize_zq_P0_MSK                    (0x00400000)
  #define MC0_CH0_CR_SCHED_CBIT_serialize_zq_P0_MIN                    (0)
  #define MC0_CH0_CR_SCHED_CBIT_serialize_zq_P0_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_serialize_zq_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_serialize_zq_P0_HSH                    (0x012CE028)

  #define MC0_CH0_CR_SCHED_CBIT_zq_fast_exec_P0_OFF                    (23)
  #define MC0_CH0_CR_SCHED_CBIT_zq_fast_exec_P0_WID                    ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_zq_fast_exec_P0_MSK                    (0x00800000)
  #define MC0_CH0_CR_SCHED_CBIT_zq_fast_exec_P0_MIN                    (0)
  #define MC0_CH0_CR_SCHED_CBIT_zq_fast_exec_P0_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_zq_fast_exec_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_zq_fast_exec_P0_HSH                    (0x012EE028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_starved_read_rank_block_P0_OFF     (24)
  #define MC0_CH0_CR_SCHED_CBIT_dis_starved_read_rank_block_P0_WID     ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_starved_read_rank_block_P0_MSK     (0x01000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_starved_read_rank_block_P0_MIN     (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_starved_read_rank_block_P0_MAX     (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_starved_read_rank_block_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_starved_read_rank_block_P0_HSH     (0x0130E028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_idle_preempt_P0_OFF                (25)
  #define MC0_CH0_CR_SCHED_CBIT_dis_idle_preempt_P0_WID                ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_idle_preempt_P0_MSK                (0x02000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_idle_preempt_P0_MIN                (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_idle_preempt_P0_MAX                (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_idle_preempt_P0_DEF                (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_idle_preempt_P0_HSH                (0x0132E028)

  #define MC0_CH0_CR_SCHED_CBIT_find_first_allocation_P0_OFF           (26)
  #define MC0_CH0_CR_SCHED_CBIT_find_first_allocation_P0_WID           ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_find_first_allocation_P0_MSK           (0x04000000)
  #define MC0_CH0_CR_SCHED_CBIT_find_first_allocation_P0_MIN           (0)
  #define MC0_CH0_CR_SCHED_CBIT_find_first_allocation_P0_MAX           (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_find_first_allocation_P0_DEF           (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_find_first_allocation_P0_HSH           (0x0134E028)

  #define MC0_CH0_CR_SCHED_CBIT_duplicate_spid_rank_P0_OFF             (27)
  #define MC0_CH0_CR_SCHED_CBIT_duplicate_spid_rank_P0_WID             ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_duplicate_spid_rank_P0_MSK             (0x08000000)
  #define MC0_CH0_CR_SCHED_CBIT_duplicate_spid_rank_P0_MIN             (0)
  #define MC0_CH0_CR_SCHED_CBIT_duplicate_spid_rank_P0_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_duplicate_spid_rank_P0_DEF             (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_duplicate_spid_rank_P0_HSH             (0x0136E028)

  #define MC0_CH0_CR_SCHED_CBIT_wio_merge_lpmode_2_3_P0_OFF            (28)
  #define MC0_CH0_CR_SCHED_CBIT_wio_merge_lpmode_2_3_P0_WID            ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_wio_merge_lpmode_2_3_P0_MSK            (0x10000000)
  #define MC0_CH0_CR_SCHED_CBIT_wio_merge_lpmode_2_3_P0_MIN            (0)
  #define MC0_CH0_CR_SCHED_CBIT_wio_merge_lpmode_2_3_P0_MAX            (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_wio_merge_lpmode_2_3_P0_DEF            (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_wio_merge_lpmode_2_3_P0_HSH            (0x0138E028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_write_gap_P0_OFF              (29)
  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_write_gap_P0_WID              ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_write_gap_P0_MSK              (0x20000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_write_gap_P0_MIN              (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_write_gap_P0_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_write_gap_P0_DEF              (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_write_gap_P0_HSH              (0x013AE028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_read_gap_P0_OFF               (30)
  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_read_gap_P0_WID               ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_read_gap_P0_MSK               (0x40000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_read_gap_P0_MIN               (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_read_gap_P0_MAX               (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_read_gap_P0_DEF               (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_read_gap_P0_HSH               (0x013CE028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_clk_gate_P0_OFF                    (31)
  #define MC0_CH0_CR_SCHED_CBIT_dis_clk_gate_P0_WID                    ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_clk_gate_P0_MSK                    (0x80000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_clk_gate_P0_MIN                    (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_clk_gate_P0_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_clk_gate_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_clk_gate_P0_HSH                    (0x013EE028)

#define MC0_CH0_CR_SCHED_SECOND_CBIT_P0_REG                            (0x0000E02C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_srx_mr4_P0_OFF              ( 0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_srx_mr4_P0_WID              ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_srx_mr4_P0_MSK              (0x00000001)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_srx_mr4_P0_MIN              (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_srx_mr4_P0_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_srx_mr4_P0_DEF              (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_srx_mr4_P0_HSH              (0x0100E02C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ck_tristate_P0_OFF          ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ck_tristate_P0_WID          ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ck_tristate_P0_MSK          (0x00000002)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ck_tristate_P0_MIN          (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ck_tristate_P0_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ck_tristate_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ck_tristate_P0_HSH          (0x0102E02C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_bus_retain_P0_OFF           ( 3)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_bus_retain_P0_WID           ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_bus_retain_P0_MSK           (0x00000008)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_bus_retain_P0_MIN           (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_bus_retain_P0_MAX           (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_bus_retain_P0_DEF           (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_bus_retain_P0_HSH           (0x0106E02C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_async_odt_P0_OFF            ( 4)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_async_odt_P0_WID            ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_async_odt_P0_MSK            (0x00000010)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_async_odt_P0_MIN            (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_async_odt_P0_MAX            (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_async_odt_P0_DEF            (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_async_odt_P0_HSH            (0x0108E02C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_reset_P0_OFF            ( 5)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_reset_P0_WID            ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_reset_P0_MSK            (0x00000020)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_reset_P0_MIN            (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_reset_P0_MAX            (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_reset_P0_DEF            (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_reset_P0_HSH            (0x010AE02C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_SPARE_CBIT_P0_OFF               ( 6)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_SPARE_CBIT_P0_WID               ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_SPARE_CBIT_P0_MSK               (0x00000040)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_SPARE_CBIT_P0_MIN               (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_SPARE_CBIT_P0_MAX               (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_SPARE_CBIT_P0_DEF               (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_SPARE_CBIT_P0_HSH               (0x010CE02C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_MRS_MR4_P0_OFF          ( 7)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_MRS_MR4_P0_WID          ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_MRS_MR4_P0_MSK          (0x00000080)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_MRS_MR4_P0_MIN          (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_MRS_MR4_P0_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_MRS_MR4_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_MRS_MR4_P0_HSH          (0x010EE02C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_opp_ref_idle_delay_P0_OFF   ( 8)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_opp_ref_idle_delay_P0_WID   ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_opp_ref_idle_delay_P0_MSK   (0x00000100)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_opp_ref_idle_delay_P0_MIN   (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_opp_ref_idle_delay_P0_MAX   (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_opp_ref_idle_delay_P0_DEF   (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_opp_ref_idle_delay_P0_HSH   (0x0110E02C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ignore_1st_trefi_P0_OFF     ( 9)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ignore_1st_trefi_P0_WID     ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ignore_1st_trefi_P0_MSK     (0x00000200)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ignore_1st_trefi_P0_MIN     (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ignore_1st_trefi_P0_MAX     (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ignore_1st_trefi_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ignore_1st_trefi_P0_HSH     (0x0112E02C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_echo_mask_P0_OFF                (10)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_echo_mask_P0_WID                ( 9)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_echo_mask_P0_MSK                (0x0007FC00)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_echo_mask_P0_MIN                (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_echo_mask_P0_MAX                (511) // 0x000001FF
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_echo_mask_P0_DEF                (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_echo_mask_P0_HSH                (0x0914E02C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_early_go_P0_OFF             (19)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_early_go_P0_WID             ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_early_go_P0_MSK             (0x00080000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_early_go_P0_MIN             (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_early_go_P0_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_early_go_P0_DEF             (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_early_go_P0_HSH             (0x0126E02C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_new_wr_to_full_P0_OFF       (20)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_new_wr_to_full_P0_WID       ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_new_wr_to_full_P0_MSK       (0x00100000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_new_wr_to_full_P0_MIN       (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_new_wr_to_full_P0_MAX       (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_new_wr_to_full_P0_DEF       (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_new_wr_to_full_P0_HSH       (0x0128E02C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_drainless_SAGV_do_zq_P0_OFF     (22)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_drainless_SAGV_do_zq_P0_WID     ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_drainless_SAGV_do_zq_P0_MSK     (0x00400000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_drainless_SAGV_do_zq_P0_MIN     (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_drainless_SAGV_do_zq_P0_MAX     (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_drainless_SAGV_do_zq_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_drainless_SAGV_do_zq_P0_HSH     (0x012CE02C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_do_temp_reading_after_drainless_SAGV_P0_OFF (23)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_do_temp_reading_after_drainless_SAGV_P0_WID ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_do_temp_reading_after_drainless_SAGV_P0_MSK (0x00800000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_do_temp_reading_after_drainless_SAGV_P0_MIN (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_do_temp_reading_after_drainless_SAGV_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_do_temp_reading_after_drainless_SAGV_P0_DEF (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_do_temp_reading_after_drainless_SAGV_P0_HSH (0x012EE02C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_ignore_refresh_between_SR_P0_OFF (24)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_ignore_refresh_between_SR_P0_WID ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_ignore_refresh_between_SR_P0_MSK (0x01000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_ignore_refresh_between_SR_P0_MIN (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_ignore_refresh_between_SR_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_ignore_refresh_between_SR_P0_DEF (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_ignore_refresh_between_SR_P0_HSH (0x0130E02C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_DisWrActThrottleOnAnyRead_P0_OFF (25)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_DisWrActThrottleOnAnyRead_P0_WID ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_DisWrActThrottleOnAnyRead_P0_MSK (0x02000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_DisWrActThrottleOnAnyRead_P0_MIN (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_DisWrActThrottleOnAnyRead_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_DisWrActThrottleOnAnyRead_P0_DEF (0x00000001)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_DisWrActThrottleOnAnyRead_P0_HSH (0x0132E02C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_enable_fdata_nak_P0_OFF         (26)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_enable_fdata_nak_P0_WID         ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_enable_fdata_nak_P0_MSK         (0x04000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_enable_fdata_nak_P0_MIN         (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_enable_fdata_nak_P0_MAX         (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_enable_fdata_nak_P0_DEF         (0x00000001)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_enable_fdata_nak_P0_HSH         (0x0134E02C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_disable_wr_on_SAGV_exit_for_DCC_P0_OFF (27)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_disable_wr_on_SAGV_exit_for_DCC_P0_WID ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_disable_wr_on_SAGV_exit_for_DCC_P0_MSK (0x08000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_disable_wr_on_SAGV_exit_for_DCC_P0_MIN (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_disable_wr_on_SAGV_exit_for_DCC_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_disable_wr_on_SAGV_exit_for_DCC_P0_DEF (0x00000001)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_disable_wr_on_SAGV_exit_for_DCC_P0_HSH (0x0136E02C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_spare_Copy_P0_OFF               (29)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_spare_Copy_P0_WID               ( 3)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_spare_Copy_P0_MSK               (0xE0000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_spare_Copy_P0_MIN               (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_spare_Copy_P0_MAX               (7) // 0x00000007
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_spare_Copy_P0_DEF               (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_spare_Copy_P0_HSH               (0x033AE02C)

#define MC0_CH0_CR_DFT_MISC_P0_REG                                     (0x0000E030)

  #define MC0_CH0_CR_DFT_MISC_WDAR_P0_OFF                              ( 0)
  #define MC0_CH0_CR_DFT_MISC_WDAR_P0_WID                              ( 1)
  #define MC0_CH0_CR_DFT_MISC_WDAR_P0_MSK                              (0x00000001)
  #define MC0_CH0_CR_DFT_MISC_WDAR_P0_MIN                              (0)
  #define MC0_CH0_CR_DFT_MISC_WDAR_P0_MAX                              (1) // 0x00000001
  #define MC0_CH0_CR_DFT_MISC_WDAR_P0_DEF                              (0x00000000)
  #define MC0_CH0_CR_DFT_MISC_WDAR_P0_HSH                              (0x0100E030)

  #define MC0_CH0_CR_DFT_MISC_WDB_Block_En_P0_OFF                      ( 1)
  #define MC0_CH0_CR_DFT_MISC_WDB_Block_En_P0_WID                      ( 1)
  #define MC0_CH0_CR_DFT_MISC_WDB_Block_En_P0_MSK                      (0x00000002)
  #define MC0_CH0_CR_DFT_MISC_WDB_Block_En_P0_MIN                      (0)
  #define MC0_CH0_CR_DFT_MISC_WDB_Block_En_P0_MAX                      (1) // 0x00000001
  #define MC0_CH0_CR_DFT_MISC_WDB_Block_En_P0_DEF                      (0x00000000)
  #define MC0_CH0_CR_DFT_MISC_WDB_Block_En_P0_HSH                      (0x0102E030)

  #define MC0_CH0_CR_DFT_MISC_isolate_data_return_P0_OFF               ( 4)
  #define MC0_CH0_CR_DFT_MISC_isolate_data_return_P0_WID               ( 1)
  #define MC0_CH0_CR_DFT_MISC_isolate_data_return_P0_MSK               (0x00000010)
  #define MC0_CH0_CR_DFT_MISC_isolate_data_return_P0_MIN               (0)
  #define MC0_CH0_CR_DFT_MISC_isolate_data_return_P0_MAX               (1) // 0x00000001
  #define MC0_CH0_CR_DFT_MISC_isolate_data_return_P0_DEF               (0x00000000)
  #define MC0_CH0_CR_DFT_MISC_isolate_data_return_P0_HSH               (0x0108E030)

  #define MC0_CH0_CR_DFT_MISC_dft_block_enable_P0_OFF                  (17)
  #define MC0_CH0_CR_DFT_MISC_dft_block_enable_P0_WID                  ( 1)
  #define MC0_CH0_CR_DFT_MISC_dft_block_enable_P0_MSK                  (0x00020000)
  #define MC0_CH0_CR_DFT_MISC_dft_block_enable_P0_MIN                  (0)
  #define MC0_CH0_CR_DFT_MISC_dft_block_enable_P0_MAX                  (1) // 0x00000001
  #define MC0_CH0_CR_DFT_MISC_dft_block_enable_P0_DEF                  (0x00000000)
  #define MC0_CH0_CR_DFT_MISC_dft_block_enable_P0_HSH                  (0x0122E030)

  #define MC0_CH0_CR_DFT_MISC_SAM_overloading_P0_OFF                   (18)
  #define MC0_CH0_CR_DFT_MISC_SAM_overloading_P0_WID                   ( 3)
  #define MC0_CH0_CR_DFT_MISC_SAM_overloading_P0_MSK                   (0x001C0000)
  #define MC0_CH0_CR_DFT_MISC_SAM_overloading_P0_MIN                   (0)
  #define MC0_CH0_CR_DFT_MISC_SAM_overloading_P0_MAX                   (7) // 0x00000007
  #define MC0_CH0_CR_DFT_MISC_SAM_overloading_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_DFT_MISC_SAM_overloading_P0_HSH                   (0x0324E030)

  #define MC0_CH0_CR_DFT_MISC_Stretch_mode_en_P0_OFF                   (24)
  #define MC0_CH0_CR_DFT_MISC_Stretch_mode_en_P0_WID                   ( 1)
  #define MC0_CH0_CR_DFT_MISC_Stretch_mode_en_P0_MSK                   (0x01000000)
  #define MC0_CH0_CR_DFT_MISC_Stretch_mode_en_P0_MIN                   (0)
  #define MC0_CH0_CR_DFT_MISC_Stretch_mode_en_P0_MAX                   (1) // 0x00000001
  #define MC0_CH0_CR_DFT_MISC_Stretch_mode_en_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_DFT_MISC_Stretch_mode_en_P0_HSH                   (0x0130E030)

  #define MC0_CH0_CR_DFT_MISC_STF_P0_OFF                               (25)
  #define MC0_CH0_CR_DFT_MISC_STF_P0_WID                               ( 5)
  #define MC0_CH0_CR_DFT_MISC_STF_P0_MSK                               (0x3E000000)
  #define MC0_CH0_CR_DFT_MISC_STF_P0_MIN                               (0)
  #define MC0_CH0_CR_DFT_MISC_STF_P0_MAX                               (31) // 0x0000001F
  #define MC0_CH0_CR_DFT_MISC_STF_P0_DEF                               (0x00000000)
  #define MC0_CH0_CR_DFT_MISC_STF_P0_HSH                               (0x0532E030)

  #define MC0_CH0_CR_DFT_MISC_Stretch_delay_from_write_P0_OFF          (30)
  #define MC0_CH0_CR_DFT_MISC_Stretch_delay_from_write_P0_WID          ( 1)
  #define MC0_CH0_CR_DFT_MISC_Stretch_delay_from_write_P0_MSK          (0x40000000)
  #define MC0_CH0_CR_DFT_MISC_Stretch_delay_from_write_P0_MIN          (0)
  #define MC0_CH0_CR_DFT_MISC_Stretch_delay_from_write_P0_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_DFT_MISC_Stretch_delay_from_write_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_DFT_MISC_Stretch_delay_from_write_P0_HSH          (0x013CE030)

#define MC0_CH0_CR_SC_PCIT_P0_REG                                      (0x0000E034)

  #define MC0_CH0_CR_SC_PCIT_PCIT_P0_OFF                               ( 0)
  #define MC0_CH0_CR_SC_PCIT_PCIT_P0_WID                               ( 8)
  #define MC0_CH0_CR_SC_PCIT_PCIT_P0_MSK                               (0x000000FF)
  #define MC0_CH0_CR_SC_PCIT_PCIT_P0_MIN                               (0)
  #define MC0_CH0_CR_SC_PCIT_PCIT_P0_MAX                               (255) // 0x000000FF
  #define MC0_CH0_CR_SC_PCIT_PCIT_P0_DEF                               (0x00000040)
  #define MC0_CH0_CR_SC_PCIT_PCIT_P0_HSH                               (0x0800E034)

  #define MC0_CH0_CR_SC_PCIT_PCIT_GT_P0_OFF                            (16)
  #define MC0_CH0_CR_SC_PCIT_PCIT_GT_P0_WID                            ( 8)
  #define MC0_CH0_CR_SC_PCIT_PCIT_GT_P0_MSK                            (0x00FF0000)
  #define MC0_CH0_CR_SC_PCIT_PCIT_GT_P0_MIN                            (0)
  #define MC0_CH0_CR_SC_PCIT_PCIT_GT_P0_MAX                            (255) // 0x000000FF
  #define MC0_CH0_CR_SC_PCIT_PCIT_GT_P0_DEF                            (0x00000000)
  #define MC0_CH0_CR_SC_PCIT_PCIT_GT_P0_HSH                            (0x0820E034)

#define MC0_CH0_CR_ECC_DFT_P0_REG                                      (0x0000E038)

  #define MC0_CH0_CR_ECC_DFT_ECC_Inject_P0_OFF                         ( 0)
  #define MC0_CH0_CR_ECC_DFT_ECC_Inject_P0_WID                         ( 3)
  #define MC0_CH0_CR_ECC_DFT_ECC_Inject_P0_MSK                         (0x00000007)
  #define MC0_CH0_CR_ECC_DFT_ECC_Inject_P0_MIN                         (0)
  #define MC0_CH0_CR_ECC_DFT_ECC_Inject_P0_MAX                         (7) // 0x00000007
  #define MC0_CH0_CR_ECC_DFT_ECC_Inject_P0_DEF                         (0x00000000)
  #define MC0_CH0_CR_ECC_DFT_ECC_Inject_P0_HSH                         (0x0300E038)

  #define MC0_CH0_CR_ECC_DFT_ECC_correction_disable_P0_OFF             ( 4)
  #define MC0_CH0_CR_ECC_DFT_ECC_correction_disable_P0_WID             ( 1)
  #define MC0_CH0_CR_ECC_DFT_ECC_correction_disable_P0_MSK             (0x00000010)
  #define MC0_CH0_CR_ECC_DFT_ECC_correction_disable_P0_MIN             (0)
  #define MC0_CH0_CR_ECC_DFT_ECC_correction_disable_P0_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_ECC_DFT_ECC_correction_disable_P0_DEF             (0x00000000)
  #define MC0_CH0_CR_ECC_DFT_ECC_correction_disable_P0_HSH             (0x0108E038)

  #define MC0_CH0_CR_ECC_DFT_DIS_MCA_LOG_P0_OFF                        ( 8)
  #define MC0_CH0_CR_ECC_DFT_DIS_MCA_LOG_P0_WID                        ( 1)
  #define MC0_CH0_CR_ECC_DFT_DIS_MCA_LOG_P0_MSK                        (0x00000100)
  #define MC0_CH0_CR_ECC_DFT_DIS_MCA_LOG_P0_MIN                        (0)
  #define MC0_CH0_CR_ECC_DFT_DIS_MCA_LOG_P0_MAX                        (1) // 0x00000001
  #define MC0_CH0_CR_ECC_DFT_DIS_MCA_LOG_P0_DEF                        (0x00000000)
  #define MC0_CH0_CR_ECC_DFT_DIS_MCA_LOG_P0_HSH                        (0x0110E038)

  #define MC0_CH0_CR_ECC_DFT_DIS_PCH_EVENT_P0_OFF                      ( 9)
  #define MC0_CH0_CR_ECC_DFT_DIS_PCH_EVENT_P0_WID                      ( 1)
  #define MC0_CH0_CR_ECC_DFT_DIS_PCH_EVENT_P0_MSK                      (0x00000200)
  #define MC0_CH0_CR_ECC_DFT_DIS_PCH_EVENT_P0_MIN                      (0)
  #define MC0_CH0_CR_ECC_DFT_DIS_PCH_EVENT_P0_MAX                      (1) // 0x00000001
  #define MC0_CH0_CR_ECC_DFT_DIS_PCH_EVENT_P0_DEF                      (0x00000000)
  #define MC0_CH0_CR_ECC_DFT_DIS_PCH_EVENT_P0_HSH                      (0x0112E038)

  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_POISON_P0_OFF                     (10)
  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_POISON_P0_WID                     ( 1)
  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_POISON_P0_MSK                     (0x00000400)
  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_POISON_P0_MIN                     (0)
  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_POISON_P0_MAX                     (1) // 0x00000001
  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_POISON_P0_DEF                     (0x00000001)
  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_POISON_P0_HSH                     (0x0114E038)

  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_ERROR_P0_OFF                      (11)
  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_ERROR_P0_WID                      ( 1)
  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_ERROR_P0_MSK                      (0x00000800)
  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_ERROR_P0_MIN                      (0)
  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_ERROR_P0_MAX                      (1) // 0x00000001
  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_ERROR_P0_DEF                      (0x00000001)
  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_ERROR_P0_HSH                      (0x0116E038)

  #define MC0_CH0_CR_ECC_DFT_ECC_trigger_P0_OFF                        (16)
  #define MC0_CH0_CR_ECC_DFT_ECC_trigger_P0_WID                        ( 2)
  #define MC0_CH0_CR_ECC_DFT_ECC_trigger_P0_MSK                        (0x00030000)
  #define MC0_CH0_CR_ECC_DFT_ECC_trigger_P0_MIN                        (0)
  #define MC0_CH0_CR_ECC_DFT_ECC_trigger_P0_MAX                        (3) // 0x00000003
  #define MC0_CH0_CR_ECC_DFT_ECC_trigger_P0_DEF                        (0x00000000)
  #define MC0_CH0_CR_ECC_DFT_ECC_trigger_P0_HSH                        (0x0220E038)

#define MC0_CH0_CR_PM_PDWN_CONFIG_P0_REG                               (0x0000E040)

  #define MC0_CH0_CR_PM_PDWN_CONFIG_PDWN_idle_counter_P0_OFF           ( 0)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_PDWN_idle_counter_P0_WID           (12)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_PDWN_idle_counter_P0_MSK           (0x00000FFF)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_PDWN_idle_counter_P0_MIN           (0)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_PDWN_idle_counter_P0_MAX           (4095) // 0x00000FFF
  #define MC0_CH0_CR_PM_PDWN_CONFIG_PDWN_idle_counter_P0_DEF           (0x00000000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_PDWN_idle_counter_P0_HSH           (0x0C00E040)

  #define MC0_CH0_CR_PM_PDWN_CONFIG_APD_P0_OFF                         (12)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_APD_P0_WID                         ( 1)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_APD_P0_MSK                         (0x00001000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_APD_P0_MIN                         (0)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_APD_P0_MAX                         (1) // 0x00000001
  #define MC0_CH0_CR_PM_PDWN_CONFIG_APD_P0_DEF                         (0x00000000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_APD_P0_HSH                         (0x0118E040)

  #define MC0_CH0_CR_PM_PDWN_CONFIG_PPD_P0_OFF                         (13)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_PPD_P0_WID                         ( 1)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_PPD_P0_MSK                         (0x00002000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_PPD_P0_MIN                         (0)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_PPD_P0_MAX                         (1) // 0x00000001
  #define MC0_CH0_CR_PM_PDWN_CONFIG_PPD_P0_DEF                         (0x00000000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_PPD_P0_HSH                         (0x011AE040)

  #define MC0_CH0_CR_PM_PDWN_CONFIG_Global_PD_P0_OFF                   (15)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_Global_PD_P0_WID                   ( 1)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_Global_PD_P0_MSK                   (0x00008000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_Global_PD_P0_MIN                   (0)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_Global_PD_P0_MAX                   (1) // 0x00000001
  #define MC0_CH0_CR_PM_PDWN_CONFIG_Global_PD_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_Global_PD_P0_HSH                   (0x011EE040)

  #define MC0_CH0_CR_PM_PDWN_CONFIG_TT_idle_counter_P0_OFF             (16)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_TT_idle_counter_P0_WID             ( 8)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_TT_idle_counter_P0_MSK             (0x00FF0000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_TT_idle_counter_P0_MIN             (0)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_TT_idle_counter_P0_MAX             (255) // 0x000000FF
  #define MC0_CH0_CR_PM_PDWN_CONFIG_TT_idle_counter_P0_DEF             (0x00000000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_TT_idle_counter_P0_HSH             (0x0820E040)

  #define MC0_CH0_CR_PM_PDWN_CONFIG_dis_cke_tt_P0_OFF                  (24)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_dis_cke_tt_P0_WID                  ( 1)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_dis_cke_tt_P0_MSK                  (0x01000000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_dis_cke_tt_P0_MIN                  (0)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_dis_cke_tt_P0_MAX                  (1) // 0x00000001
  #define MC0_CH0_CR_PM_PDWN_CONFIG_dis_cke_tt_P0_DEF                  (0x00000000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_dis_cke_tt_P0_HSH                  (0x0130E040)

  #define MC0_CH0_CR_PM_PDWN_CONFIG_write_threshold_P0_OFF             (25)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_write_threshold_P0_WID             ( 6)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_write_threshold_P0_MSK             (0x7E000000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_write_threshold_P0_MIN             (0)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_write_threshold_P0_MAX             (63) // 0x0000003F
  #define MC0_CH0_CR_PM_PDWN_CONFIG_write_threshold_P0_DEF             (0x00000000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_write_threshold_P0_HSH             (0x0632E040)

  #define MC0_CH0_CR_PM_PDWN_CONFIG_allow_opp_ref_below_write_threhold_P0_OFF (31)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_allow_opp_ref_below_write_threhold_P0_WID ( 1)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_allow_opp_ref_below_write_threhold_P0_MSK (0x80000000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_allow_opp_ref_below_write_threhold_P0_MIN (0)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_allow_opp_ref_below_write_threhold_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_PM_PDWN_CONFIG_allow_opp_ref_below_write_threhold_P0_DEF (0x00000000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_allow_opp_ref_below_write_threhold_P0_HSH (0x013EE040)

#define MC0_CH0_CR_WMM_READ_CONFIG_P0_REG                              (0x0000E044)

  #define MC0_CH0_CR_WMM_READ_CONFIG_Dis_Opp_rd_P0_OFF                 ( 0)
  #define MC0_CH0_CR_WMM_READ_CONFIG_Dis_Opp_rd_P0_WID                 ( 1)
  #define MC0_CH0_CR_WMM_READ_CONFIG_Dis_Opp_rd_P0_MSK                 (0x00000001)
  #define MC0_CH0_CR_WMM_READ_CONFIG_Dis_Opp_rd_P0_MIN                 (0)
  #define MC0_CH0_CR_WMM_READ_CONFIG_Dis_Opp_rd_P0_MAX                 (1) // 0x00000001
  #define MC0_CH0_CR_WMM_READ_CONFIG_Dis_Opp_rd_P0_DEF                 (0x00000000)
  #define MC0_CH0_CR_WMM_READ_CONFIG_Dis_Opp_rd_P0_HSH                 (0x0100E044)

  #define MC0_CH0_CR_WMM_READ_CONFIG_ACT_Enable_P0_OFF                 ( 1)
  #define MC0_CH0_CR_WMM_READ_CONFIG_ACT_Enable_P0_WID                 ( 1)
  #define MC0_CH0_CR_WMM_READ_CONFIG_ACT_Enable_P0_MSK                 (0x00000002)
  #define MC0_CH0_CR_WMM_READ_CONFIG_ACT_Enable_P0_MIN                 (0)
  #define MC0_CH0_CR_WMM_READ_CONFIG_ACT_Enable_P0_MAX                 (1) // 0x00000001
  #define MC0_CH0_CR_WMM_READ_CONFIG_ACT_Enable_P0_DEF                 (0x00000001)
  #define MC0_CH0_CR_WMM_READ_CONFIG_ACT_Enable_P0_HSH                 (0x0102E044)

  #define MC0_CH0_CR_WMM_READ_CONFIG_PRE_Enable_P0_OFF                 ( 2)
  #define MC0_CH0_CR_WMM_READ_CONFIG_PRE_Enable_P0_WID                 ( 1)
  #define MC0_CH0_CR_WMM_READ_CONFIG_PRE_Enable_P0_MSK                 (0x00000004)
  #define MC0_CH0_CR_WMM_READ_CONFIG_PRE_Enable_P0_MIN                 (0)
  #define MC0_CH0_CR_WMM_READ_CONFIG_PRE_Enable_P0_MAX                 (1) // 0x00000001
  #define MC0_CH0_CR_WMM_READ_CONFIG_PRE_Enable_P0_DEF                 (0x00000001)
  #define MC0_CH0_CR_WMM_READ_CONFIG_PRE_Enable_P0_HSH                 (0x0104E044)

  #define MC0_CH0_CR_WMM_READ_CONFIG_MAX_RPQ_CAS_P0_OFF                ( 3)
  #define MC0_CH0_CR_WMM_READ_CONFIG_MAX_RPQ_CAS_P0_WID                ( 4)
  #define MC0_CH0_CR_WMM_READ_CONFIG_MAX_RPQ_CAS_P0_MSK                (0x00000078)
  #define MC0_CH0_CR_WMM_READ_CONFIG_MAX_RPQ_CAS_P0_MIN                (0)
  #define MC0_CH0_CR_WMM_READ_CONFIG_MAX_RPQ_CAS_P0_MAX                (15) // 0x0000000F
  #define MC0_CH0_CR_WMM_READ_CONFIG_MAX_RPQ_CAS_P0_DEF                (0x00000008)
  #define MC0_CH0_CR_WMM_READ_CONFIG_MAX_RPQ_CAS_P0_HSH                (0x0406E044)

#define MC0_CH0_CR_ECCERRLOG0_P0_REG                                   (0x0000E048)

  #define MC0_CH0_CR_ECCERRLOG0_CERRSTS_P0_OFF                         ( 0)
  #define MC0_CH0_CR_ECCERRLOG0_CERRSTS_P0_WID                         ( 1)
  #define MC0_CH0_CR_ECCERRLOG0_CERRSTS_P0_MSK                         (0x00000001)
  #define MC0_CH0_CR_ECCERRLOG0_CERRSTS_P0_MIN                         (0)
  #define MC0_CH0_CR_ECCERRLOG0_CERRSTS_P0_MAX                         (1) // 0x00000001
  #define MC0_CH0_CR_ECCERRLOG0_CERRSTS_P0_DEF                         (0x00000000)
  #define MC0_CH0_CR_ECCERRLOG0_CERRSTS_P0_HSH                         (0x0100E048)

  #define MC0_CH0_CR_ECCERRLOG0_MERRSTS_P0_OFF                         ( 1)
  #define MC0_CH0_CR_ECCERRLOG0_MERRSTS_P0_WID                         ( 1)
  #define MC0_CH0_CR_ECCERRLOG0_MERRSTS_P0_MSK                         (0x00000002)
  #define MC0_CH0_CR_ECCERRLOG0_MERRSTS_P0_MIN                         (0)
  #define MC0_CH0_CR_ECCERRLOG0_MERRSTS_P0_MAX                         (1) // 0x00000001
  #define MC0_CH0_CR_ECCERRLOG0_MERRSTS_P0_DEF                         (0x00000000)
  #define MC0_CH0_CR_ECCERRLOG0_MERRSTS_P0_HSH                         (0x0102E048)

  #define MC0_CH0_CR_ECCERRLOG0_ERRSYND_P0_OFF                         (16)
  #define MC0_CH0_CR_ECCERRLOG0_ERRSYND_P0_WID                         ( 8)
  #define MC0_CH0_CR_ECCERRLOG0_ERRSYND_P0_MSK                         (0x00FF0000)
  #define MC0_CH0_CR_ECCERRLOG0_ERRSYND_P0_MIN                         (0)
  #define MC0_CH0_CR_ECCERRLOG0_ERRSYND_P0_MAX                         (255) // 0x000000FF
  #define MC0_CH0_CR_ECCERRLOG0_ERRSYND_P0_DEF                         (0x00000000)
  #define MC0_CH0_CR_ECCERRLOG0_ERRSYND_P0_HSH                         (0x0820E048)

  #define MC0_CH0_CR_ECCERRLOG0_ERRCHUNK_P0_OFF                        (24)
  #define MC0_CH0_CR_ECCERRLOG0_ERRCHUNK_P0_WID                        ( 3)
  #define MC0_CH0_CR_ECCERRLOG0_ERRCHUNK_P0_MSK                        (0x07000000)
  #define MC0_CH0_CR_ECCERRLOG0_ERRCHUNK_P0_MIN                        (0)
  #define MC0_CH0_CR_ECCERRLOG0_ERRCHUNK_P0_MAX                        (7) // 0x00000007
  #define MC0_CH0_CR_ECCERRLOG0_ERRCHUNK_P0_DEF                        (0x00000000)
  #define MC0_CH0_CR_ECCERRLOG0_ERRCHUNK_P0_HSH                        (0x0330E048)

  #define MC0_CH0_CR_ECCERRLOG0_ERRRANK_P0_OFF                         (27)
  #define MC0_CH0_CR_ECCERRLOG0_ERRRANK_P0_WID                         ( 2)
  #define MC0_CH0_CR_ECCERRLOG0_ERRRANK_P0_MSK                         (0x18000000)
  #define MC0_CH0_CR_ECCERRLOG0_ERRRANK_P0_MIN                         (0)
  #define MC0_CH0_CR_ECCERRLOG0_ERRRANK_P0_MAX                         (3) // 0x00000003
  #define MC0_CH0_CR_ECCERRLOG0_ERRRANK_P0_DEF                         (0x00000000)
  #define MC0_CH0_CR_ECCERRLOG0_ERRRANK_P0_HSH                         (0x0236E048)

  #define MC0_CH0_CR_ECCERRLOG0_ERRBANK_P0_OFF                         (29)
  #define MC0_CH0_CR_ECCERRLOG0_ERRBANK_P0_WID                         ( 3)
  #define MC0_CH0_CR_ECCERRLOG0_ERRBANK_P0_MSK                         (0xE0000000)
  #define MC0_CH0_CR_ECCERRLOG0_ERRBANK_P0_MIN                         (0)
  #define MC0_CH0_CR_ECCERRLOG0_ERRBANK_P0_MAX                         (7) // 0x00000007
  #define MC0_CH0_CR_ECCERRLOG0_ERRBANK_P0_DEF                         (0x00000000)
  #define MC0_CH0_CR_ECCERRLOG0_ERRBANK_P0_HSH                         (0x033AE048)

#define MC0_CH0_CR_ECCERRLOG1_P0_REG                                   (0x0000E04C)

  #define MC0_CH0_CR_ECCERRLOG1_ERRROW_P0_OFF                          ( 0)
  #define MC0_CH0_CR_ECCERRLOG1_ERRROW_P0_WID                          (18)
  #define MC0_CH0_CR_ECCERRLOG1_ERRROW_P0_MSK                          (0x0003FFFF)
  #define MC0_CH0_CR_ECCERRLOG1_ERRROW_P0_MIN                          (0)
  #define MC0_CH0_CR_ECCERRLOG1_ERRROW_P0_MAX                          (262143) // 0x0003FFFF
  #define MC0_CH0_CR_ECCERRLOG1_ERRROW_P0_DEF                          (0x00000000)
  #define MC0_CH0_CR_ECCERRLOG1_ERRROW_P0_HSH                          (0x1200E04C)

  #define MC0_CH0_CR_ECCERRLOG1_ERRCOL_P0_OFF                          (18)
  #define MC0_CH0_CR_ECCERRLOG1_ERRCOL_P0_WID                          (11)
  #define MC0_CH0_CR_ECCERRLOG1_ERRCOL_P0_MSK                          (0x1FFC0000)
  #define MC0_CH0_CR_ECCERRLOG1_ERRCOL_P0_MIN                          (0)
  #define MC0_CH0_CR_ECCERRLOG1_ERRCOL_P0_MAX                          (2047) // 0x000007FF
  #define MC0_CH0_CR_ECCERRLOG1_ERRCOL_P0_DEF                          (0x00000000)
  #define MC0_CH0_CR_ECCERRLOG1_ERRCOL_P0_HSH                          (0x0B24E04C)

  #define MC0_CH0_CR_ECCERRLOG1_ERRBANKGROUP_P0_OFF                    (29)
  #define MC0_CH0_CR_ECCERRLOG1_ERRBANKGROUP_P0_WID                    ( 3)
  #define MC0_CH0_CR_ECCERRLOG1_ERRBANKGROUP_P0_MSK                    (0xE0000000)
  #define MC0_CH0_CR_ECCERRLOG1_ERRBANKGROUP_P0_MIN                    (0)
  #define MC0_CH0_CR_ECCERRLOG1_ERRBANKGROUP_P0_MAX                    (7) // 0x00000007
  #define MC0_CH0_CR_ECCERRLOG1_ERRBANKGROUP_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_ECCERRLOG1_ERRBANKGROUP_P0_HSH                    (0x033AE04C)

#define MC0_CH0_CR_TC_PWRDN_P0_REG                                     (0x0000E050)

  #define MC0_CH0_CR_TC_PWRDN_tCKE_P0_OFF                              ( 0)
  #define MC0_CH0_CR_TC_PWRDN_tCKE_P0_WID                              ( 6)
  #define MC0_CH0_CR_TC_PWRDN_tCKE_P0_MSK                              (0x0000003F)
  #define MC0_CH0_CR_TC_PWRDN_tCKE_P0_MIN                              (0)
  #define MC0_CH0_CR_TC_PWRDN_tCKE_P0_MAX                              (63) // 0x0000003F
  #define MC0_CH0_CR_TC_PWRDN_tCKE_P0_DEF                              (0x00000004)
  #define MC0_CH0_CR_TC_PWRDN_tCKE_P0_HSH                              (0x4600E050)

  #define MC0_CH0_CR_TC_PWRDN_tXP_P0_OFF                               ( 8)
  #define MC0_CH0_CR_TC_PWRDN_tXP_P0_WID                               ( 6)
  #define MC0_CH0_CR_TC_PWRDN_tXP_P0_MSK                               (0x00003F00)
  #define MC0_CH0_CR_TC_PWRDN_tXP_P0_MIN                               (0)
  #define MC0_CH0_CR_TC_PWRDN_tXP_P0_MAX                               (63) // 0x0000003F
  #define MC0_CH0_CR_TC_PWRDN_tXP_P0_DEF                               (0x00000004)
  #define MC0_CH0_CR_TC_PWRDN_tXP_P0_HSH                               (0x4610E050)

  #define MC0_CH0_CR_TC_PWRDN_tXPDLL_P0_OFF                            (16)
  #define MC0_CH0_CR_TC_PWRDN_tXPDLL_P0_WID                            ( 6)
  #define MC0_CH0_CR_TC_PWRDN_tXPDLL_P0_MSK                            (0x003F0000)
  #define MC0_CH0_CR_TC_PWRDN_tXPDLL_P0_MIN                            (0)
  #define MC0_CH0_CR_TC_PWRDN_tXPDLL_P0_MAX                            (63) // 0x0000003F
  #define MC0_CH0_CR_TC_PWRDN_tXPDLL_P0_DEF                            (0x00000004)
  #define MC0_CH0_CR_TC_PWRDN_tXPDLL_P0_HSH                            (0x4620E050)

  #define MC0_CH0_CR_TC_PWRDN_tRDPDEN_P0_OFF                           (24)
  #define MC0_CH0_CR_TC_PWRDN_tRDPDEN_P0_WID                           ( 7)
  #define MC0_CH0_CR_TC_PWRDN_tRDPDEN_P0_MSK                           (0x7F000000)
  #define MC0_CH0_CR_TC_PWRDN_tRDPDEN_P0_MIN                           (0)
  #define MC0_CH0_CR_TC_PWRDN_tRDPDEN_P0_MAX                           (127) // 0x0000007F
  #define MC0_CH0_CR_TC_PWRDN_tRDPDEN_P0_DEF                           (0x00000004)
  #define MC0_CH0_CR_TC_PWRDN_tRDPDEN_P0_HSH                           (0x4730E050)

  #define MC0_CH0_CR_TC_PWRDN_tWRPDEN_P0_OFF                           (32)
  #define MC0_CH0_CR_TC_PWRDN_tWRPDEN_P0_WID                           ( 9)
  #define MC0_CH0_CR_TC_PWRDN_tWRPDEN_P0_MSK                           (0x000001FF00000000ULL)
  #define MC0_CH0_CR_TC_PWRDN_tWRPDEN_P0_MIN                           (0)
  #define MC0_CH0_CR_TC_PWRDN_tWRPDEN_P0_MAX                           (511) // 0x000001FF
  #define MC0_CH0_CR_TC_PWRDN_tWRPDEN_P0_DEF                           (0x00000004)
  #define MC0_CH0_CR_TC_PWRDN_tWRPDEN_P0_HSH                           (0x4940E050)

  #define MC0_CH0_CR_TC_PWRDN_tCSH_P0_OFF                              (41)
  #define MC0_CH0_CR_TC_PWRDN_tCSH_P0_WID                              ( 6)
  #define MC0_CH0_CR_TC_PWRDN_tCSH_P0_MSK                              (0x00007E0000000000ULL)
  #define MC0_CH0_CR_TC_PWRDN_tCSH_P0_MIN                              (0)
  #define MC0_CH0_CR_TC_PWRDN_tCSH_P0_MAX                              (63) // 0x0000003F
  #define MC0_CH0_CR_TC_PWRDN_tCSH_P0_DEF                              (0x00000004)
  #define MC0_CH0_CR_TC_PWRDN_tCSH_P0_HSH                              (0x4652E050)

  #define MC0_CH0_CR_TC_PWRDN_tCSL_P0_OFF                              (47)
  #define MC0_CH0_CR_TC_PWRDN_tCSL_P0_WID                              ( 6)
  #define MC0_CH0_CR_TC_PWRDN_tCSL_P0_MSK                              (0x001F800000000000ULL)
  #define MC0_CH0_CR_TC_PWRDN_tCSL_P0_MIN                              (0)
  #define MC0_CH0_CR_TC_PWRDN_tCSL_P0_MAX                              (63) // 0x0000003F
  #define MC0_CH0_CR_TC_PWRDN_tCSL_P0_DEF                              (0x00000004)
  #define MC0_CH0_CR_TC_PWRDN_tCSL_P0_HSH                              (0x465EE050)

  #define MC0_CH0_CR_TC_PWRDN_tCA2CS_P0_OFF                            (53)
  #define MC0_CH0_CR_TC_PWRDN_tCA2CS_P0_WID                            ( 5)
  #define MC0_CH0_CR_TC_PWRDN_tCA2CS_P0_MSK                            (0x03E0000000000000ULL)
  #define MC0_CH0_CR_TC_PWRDN_tCA2CS_P0_MIN                            (0)
  #define MC0_CH0_CR_TC_PWRDN_tCA2CS_P0_MAX                            (31) // 0x0000001F
  #define MC0_CH0_CR_TC_PWRDN_tCA2CS_P0_DEF                            (0x00000004)
  #define MC0_CH0_CR_TC_PWRDN_tCA2CS_P0_HSH                            (0x456AE050)

  #define MC0_CH0_CR_TC_PWRDN_tPRPDEN_P0_OFF                           (58)
  #define MC0_CH0_CR_TC_PWRDN_tPRPDEN_P0_WID                           ( 5)
  #define MC0_CH0_CR_TC_PWRDN_tPRPDEN_P0_MSK                           (0x7C00000000000000ULL)
  #define MC0_CH0_CR_TC_PWRDN_tPRPDEN_P0_MIN                           (0)
  #define MC0_CH0_CR_TC_PWRDN_tPRPDEN_P0_MAX                           (31) // 0x0000001F
  #define MC0_CH0_CR_TC_PWRDN_tPRPDEN_P0_DEF                           (0x00000001)
  #define MC0_CH0_CR_TC_PWRDN_tPRPDEN_P0_HSH                           (0x4574E050)

#define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_RPQ_P0_REG                      (0x0000E058)

  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_RPQ_RPQ_disable_P0_OFF        ( 0)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_RPQ_RPQ_disable_P0_WID        (32)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_RPQ_RPQ_disable_P0_MSK        (0xFFFFFFFF)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_RPQ_RPQ_disable_P0_MIN        (0)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_RPQ_RPQ_disable_P0_MAX        (4294967295) // 0xFFFFFFFF
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_RPQ_RPQ_disable_P0_DEF        (0x00000000)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_RPQ_RPQ_disable_P0_HSH        (0x2000E058)

#define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_IPQ_P0_REG                      (0x0000E05C)

  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_IPQ_IPQ_disable_P0_OFF        ( 0)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_IPQ_IPQ_disable_P0_WID        (16)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_IPQ_IPQ_disable_P0_MSK        (0x0000FFFF)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_IPQ_IPQ_disable_P0_MIN        (0)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_IPQ_IPQ_disable_P0_MAX        (65535) // 0x0000FFFF
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_IPQ_IPQ_disable_P0_DEF        (0x00000000)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_IPQ_IPQ_disable_P0_HSH        (0x1000E05C)

#define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_WPQ_P0_REG                      (0x0000E060)

  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_WPQ_WPQ_disable_P0_OFF        ( 0)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_WPQ_WPQ_disable_P0_WID        (64)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_WPQ_WPQ_disable_P0_MSK        (0xFFFFFFFFFFFFFFFFULL)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_WPQ_WPQ_disable_P0_MIN        (0)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_WPQ_WPQ_disable_P0_MAX        (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_WPQ_WPQ_disable_P0_DEF        (0x00000000)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_WPQ_WPQ_disable_P0_HSH        (0x4000E060)

#define MC0_CH0_CR_SC_WDBWM_P0_REG                                     (0x0000E068)

  #define MC0_CH0_CR_SC_WDBWM_WMM_entry_wm_P0_OFF                      ( 0)
  #define MC0_CH0_CR_SC_WDBWM_WMM_entry_wm_P0_WID                      ( 7)
  #define MC0_CH0_CR_SC_WDBWM_WMM_entry_wm_P0_MSK                      (0x0000007F)
  #define MC0_CH0_CR_SC_WDBWM_WMM_entry_wm_P0_MIN                      (0)
  #define MC0_CH0_CR_SC_WDBWM_WMM_entry_wm_P0_MAX                      (127) // 0x0000007F
  #define MC0_CH0_CR_SC_WDBWM_WMM_entry_wm_P0_DEF                      (0x00000038)
  #define MC0_CH0_CR_SC_WDBWM_WMM_entry_wm_P0_HSH                      (0x4700E068)

  #define MC0_CH0_CR_SC_WDBWM_WMM_exit_wm_P0_OFF                       ( 8)
  #define MC0_CH0_CR_SC_WDBWM_WMM_exit_wm_P0_WID                       ( 7)
  #define MC0_CH0_CR_SC_WDBWM_WMM_exit_wm_P0_MSK                       (0x00007F00)
  #define MC0_CH0_CR_SC_WDBWM_WMM_exit_wm_P0_MIN                       (0)
  #define MC0_CH0_CR_SC_WDBWM_WMM_exit_wm_P0_MAX                       (127) // 0x0000007F
  #define MC0_CH0_CR_SC_WDBWM_WMM_exit_wm_P0_DEF                       (0x00000030)
  #define MC0_CH0_CR_SC_WDBWM_WMM_exit_wm_P0_HSH                       (0x4710E068)

  #define MC0_CH0_CR_SC_WDBWM_WIM_wm_P0_OFF                            (16)
  #define MC0_CH0_CR_SC_WDBWM_WIM_wm_P0_WID                            ( 7)
  #define MC0_CH0_CR_SC_WDBWM_WIM_wm_P0_MSK                            (0x007F0000)
  #define MC0_CH0_CR_SC_WDBWM_WIM_wm_P0_MIN                            (0)
  #define MC0_CH0_CR_SC_WDBWM_WIM_wm_P0_MAX                            (127) // 0x0000007F
  #define MC0_CH0_CR_SC_WDBWM_WIM_wm_P0_DEF                            (0x0000003C)
  #define MC0_CH0_CR_SC_WDBWM_WIM_wm_P0_HSH                            (0x4720E068)

  #define MC0_CH0_CR_SC_WDBWM_Write_Isoc_CAS_count_P0_OFF              (24)
  #define MC0_CH0_CR_SC_WDBWM_Write_Isoc_CAS_count_P0_WID              ( 8)
  #define MC0_CH0_CR_SC_WDBWM_Write_Isoc_CAS_count_P0_MSK              (0xFF000000)
  #define MC0_CH0_CR_SC_WDBWM_Write_Isoc_CAS_count_P0_MIN              (0)
  #define MC0_CH0_CR_SC_WDBWM_Write_Isoc_CAS_count_P0_MAX              (255) // 0x000000FF
  #define MC0_CH0_CR_SC_WDBWM_Write_Isoc_CAS_count_P0_DEF              (0x00000040)
  #define MC0_CH0_CR_SC_WDBWM_Write_Isoc_CAS_count_P0_HSH              (0x4830E068)

  #define MC0_CH0_CR_SC_WDBWM_Read_CAS_count_P0_OFF                    (32)
  #define MC0_CH0_CR_SC_WDBWM_Read_CAS_count_P0_WID                    ( 8)
  #define MC0_CH0_CR_SC_WDBWM_Read_CAS_count_P0_MSK                    (0x000000FF00000000ULL)
  #define MC0_CH0_CR_SC_WDBWM_Read_CAS_count_P0_MIN                    (0)
  #define MC0_CH0_CR_SC_WDBWM_Read_CAS_count_P0_MAX                    (255) // 0x000000FF
  #define MC0_CH0_CR_SC_WDBWM_Read_CAS_count_P0_DEF                    (0x00000040)
  #define MC0_CH0_CR_SC_WDBWM_Read_CAS_count_P0_HSH                    (0x4840E068)

  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_P0_OFF                   (40)
  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_P0_WID                   ( 8)
  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_P0_MSK                   (0x0000FF0000000000ULL)
  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_P0_MIN                   (0)
  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_P0_MAX                   (255) // 0x000000FF
  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_P0_DEF                   (0x00000040)
  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_P0_HSH                   (0x4850E068)

  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_for_VC1_P0_OFF           (48)
  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_for_VC1_P0_WID           ( 8)
  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_for_VC1_P0_MSK           (0x00FF000000000000ULL)
  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_for_VC1_P0_MIN           (0)
  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_for_VC1_P0_MAX           (255) // 0x000000FF
  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_for_VC1_P0_DEF           (0x00000040)
  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_for_VC1_P0_HSH           (0x4860E068)

  #define MC0_CH0_CR_SC_WDBWM_Write_threshold_for_lp_read_bklr_P0_OFF  (56)
  #define MC0_CH0_CR_SC_WDBWM_Write_threshold_for_lp_read_bklr_P0_WID  ( 7)
  #define MC0_CH0_CR_SC_WDBWM_Write_threshold_for_lp_read_bklr_P0_MSK  (0x7F00000000000000ULL)
  #define MC0_CH0_CR_SC_WDBWM_Write_threshold_for_lp_read_bklr_P0_MIN  (0)
  #define MC0_CH0_CR_SC_WDBWM_Write_threshold_for_lp_read_bklr_P0_MAX  (127) // 0x0000007F
  #define MC0_CH0_CR_SC_WDBWM_Write_threshold_for_lp_read_bklr_P0_DEF  (0x00000016)
  #define MC0_CH0_CR_SC_WDBWM_Write_threshold_for_lp_read_bklr_P0_HSH  (0x4770E068)

  #define MC0_CH0_CR_SC_WDBWM_En_Wr_in_WIM_during_TT_P0_OFF            (63)
  #define MC0_CH0_CR_SC_WDBWM_En_Wr_in_WIM_during_TT_P0_WID            ( 1)
  #define MC0_CH0_CR_SC_WDBWM_En_Wr_in_WIM_during_TT_P0_MSK            (0x8000000000000000ULL)
  #define MC0_CH0_CR_SC_WDBWM_En_Wr_in_WIM_during_TT_P0_MIN            (0)
  #define MC0_CH0_CR_SC_WDBWM_En_Wr_in_WIM_during_TT_P0_MAX            (1) // 0x00000001
  #define MC0_CH0_CR_SC_WDBWM_En_Wr_in_WIM_during_TT_P0_DEF            (0x00000000)
  #define MC0_CH0_CR_SC_WDBWM_En_Wr_in_WIM_during_TT_P0_HSH            (0x417EE068)

#define MC0_CH0_CR_TC_ODT_P0_REG                                       (0x0000E070)

  #define MC0_CH0_CR_TC_ODT_ODT_read_duration_P0_OFF                   ( 0)
  #define MC0_CH0_CR_TC_ODT_ODT_read_duration_P0_WID                   ( 4)
  #define MC0_CH0_CR_TC_ODT_ODT_read_duration_P0_MSK                   (0x0000000F)
  #define MC0_CH0_CR_TC_ODT_ODT_read_duration_P0_MIN                   (0)
  #define MC0_CH0_CR_TC_ODT_ODT_read_duration_P0_MAX                   (15) // 0x0000000F
  #define MC0_CH0_CR_TC_ODT_ODT_read_duration_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_TC_ODT_ODT_read_duration_P0_HSH                   (0x4400E070)

  #define MC0_CH0_CR_TC_ODT_ODT_Read_Delay_P0_OFF                      ( 4)
  #define MC0_CH0_CR_TC_ODT_ODT_Read_Delay_P0_WID                      ( 4)
  #define MC0_CH0_CR_TC_ODT_ODT_Read_Delay_P0_MSK                      (0x000000F0)
  #define MC0_CH0_CR_TC_ODT_ODT_Read_Delay_P0_MIN                      (0)
  #define MC0_CH0_CR_TC_ODT_ODT_Read_Delay_P0_MAX                      (15) // 0x0000000F
  #define MC0_CH0_CR_TC_ODT_ODT_Read_Delay_P0_DEF                      (0x00000000)
  #define MC0_CH0_CR_TC_ODT_ODT_Read_Delay_P0_HSH                      (0x4408E070)

  #define MC0_CH0_CR_TC_ODT_ODT_write_duration_P0_OFF                  ( 8)
  #define MC0_CH0_CR_TC_ODT_ODT_write_duration_P0_WID                  ( 4)
  #define MC0_CH0_CR_TC_ODT_ODT_write_duration_P0_MSK                  (0x00000F00)
  #define MC0_CH0_CR_TC_ODT_ODT_write_duration_P0_MIN                  (0)
  #define MC0_CH0_CR_TC_ODT_ODT_write_duration_P0_MAX                  (15) // 0x0000000F
  #define MC0_CH0_CR_TC_ODT_ODT_write_duration_P0_DEF                  (0x00000000)
  #define MC0_CH0_CR_TC_ODT_ODT_write_duration_P0_HSH                  (0x4410E070)

  #define MC0_CH0_CR_TC_ODT_ODT_Write_Delay_P0_OFF                     (12)
  #define MC0_CH0_CR_TC_ODT_ODT_Write_Delay_P0_WID                     ( 4)
  #define MC0_CH0_CR_TC_ODT_ODT_Write_Delay_P0_MSK                     (0x0000F000)
  #define MC0_CH0_CR_TC_ODT_ODT_Write_Delay_P0_MIN                     (0)
  #define MC0_CH0_CR_TC_ODT_ODT_Write_Delay_P0_MAX                     (15) // 0x0000000F
  #define MC0_CH0_CR_TC_ODT_ODT_Write_Delay_P0_DEF                     (0x00000000)
  #define MC0_CH0_CR_TC_ODT_ODT_Write_Delay_P0_HSH                     (0x4418E070)

  #define MC0_CH0_CR_TC_ODT_tCL_P0_OFF                                 (16)
  #define MC0_CH0_CR_TC_ODT_tCL_P0_WID                                 ( 7)
  #define MC0_CH0_CR_TC_ODT_tCL_P0_MSK                                 (0x007F0000)
  #define MC0_CH0_CR_TC_ODT_tCL_P0_MIN                                 (0)
  #define MC0_CH0_CR_TC_ODT_tCL_P0_MAX                                 (127) // 0x0000007F
  #define MC0_CH0_CR_TC_ODT_tCL_P0_DEF                                 (0x00000005)
  #define MC0_CH0_CR_TC_ODT_tCL_P0_HSH                                 (0x4720E070)

  #define MC0_CH0_CR_TC_ODT_tCWL_P0_OFF                                (23)
  #define MC0_CH0_CR_TC_ODT_tCWL_P0_WID                                ( 7)
  #define MC0_CH0_CR_TC_ODT_tCWL_P0_MSK                                (0x3F800000)
  #define MC0_CH0_CR_TC_ODT_tCWL_P0_MIN                                (0)
  #define MC0_CH0_CR_TC_ODT_tCWL_P0_MAX                                (127) // 0x0000007F
  #define MC0_CH0_CR_TC_ODT_tCWL_P0_DEF                                (0x00000006)
  #define MC0_CH0_CR_TC_ODT_tCWL_P0_HSH                                (0x472EE070)

  #define MC0_CH0_CR_TC_ODT_Write_Early_ODT_P0_OFF                     (30)
  #define MC0_CH0_CR_TC_ODT_Write_Early_ODT_P0_WID                     ( 1)
  #define MC0_CH0_CR_TC_ODT_Write_Early_ODT_P0_MSK                     (0x40000000)
  #define MC0_CH0_CR_TC_ODT_Write_Early_ODT_P0_MIN                     (0)
  #define MC0_CH0_CR_TC_ODT_Write_Early_ODT_P0_MAX                     (1) // 0x00000001
  #define MC0_CH0_CR_TC_ODT_Write_Early_ODT_P0_DEF                     (0x00000000)
  #define MC0_CH0_CR_TC_ODT_Write_Early_ODT_P0_HSH                     (0x413CE070)

  #define MC0_CH0_CR_TC_ODT_tAONPD_P0_OFF                              (32)
  #define MC0_CH0_CR_TC_ODT_tAONPD_P0_WID                              ( 6)
  #define MC0_CH0_CR_TC_ODT_tAONPD_P0_MSK                              (0x0000003F00000000ULL)
  #define MC0_CH0_CR_TC_ODT_tAONPD_P0_MIN                              (0)
  #define MC0_CH0_CR_TC_ODT_tAONPD_P0_MAX                              (63) // 0x0000003F
  #define MC0_CH0_CR_TC_ODT_tAONPD_P0_DEF                              (0x00000004)
  #define MC0_CH0_CR_TC_ODT_tAONPD_P0_HSH                              (0x4640E070)

#define MC0_CH0_CR_MCSCHEDS_SPARE_P0_REG                               (0x0000E078)

  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_P0_OFF                    ( 0)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_P0_WID                    (15)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_P0_MSK                    (0x00007FFF)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_P0_MIN                    (0)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_P0_MAX                    (32767) // 0x00007FFF
  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_P0_HSH                    (0x0F00E078)

  #define MC0_CH0_CR_MCSCHEDS_SPARE_EnableB2BPreemption_P0_OFF         (15)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_EnableB2BPreemption_P0_WID         ( 1)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_EnableB2BPreemption_P0_MSK         (0x00008000)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_EnableB2BPreemption_P0_MIN         (0)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_EnableB2BPreemption_P0_MAX         (1) // 0x00000001
  #define MC0_CH0_CR_MCSCHEDS_SPARE_EnableB2BPreemption_P0_DEF         (0x00000000)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_EnableB2BPreemption_P0_HSH         (0x011EE078)

  #define MC0_CH0_CR_MCSCHEDS_SPARE_WMM_exit_wm_for_FBRMM_P0_OFF       (16)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_WMM_exit_wm_for_FBRMM_P0_WID       ( 7)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_WMM_exit_wm_for_FBRMM_P0_MSK       (0x007F0000)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_WMM_exit_wm_for_FBRMM_P0_MIN       (0)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_WMM_exit_wm_for_FBRMM_P0_MAX       (127) // 0x0000007F
  #define MC0_CH0_CR_MCSCHEDS_SPARE_WMM_exit_wm_for_FBRMM_P0_DEF       (0x00000030)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_WMM_exit_wm_for_FBRMM_P0_HSH       (0x0720E078)

  #define MC0_CH0_CR_MCSCHEDS_SPARE_ForcePBRWM_P0_OFF                  (23)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_ForcePBRWM_P0_WID                  ( 4)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_ForcePBRWM_P0_MSK                  (0x07800000)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_ForcePBRWM_P0_MIN                  (0)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_ForcePBRWM_P0_MAX                  (15) // 0x0000000F
  #define MC0_CH0_CR_MCSCHEDS_SPARE_ForcePBRWM_P0_DEF                  (0x00000005)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_ForcePBRWM_P0_HSH                  (0x042EE078)

  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_V_P0_OFF                  (27)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_V_P0_WID                  ( 5)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_V_P0_MSK                  (0xF8000000)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_V_P0_MIN                  (0)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_V_P0_MAX                  (31) // 0x0000001F
  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_V_P0_DEF                  (0x00000000)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_V_P0_HSH                  (0x0536E078)

#define MC0_CH0_CR_TC_MPC_P0_REG                                       (0x0000E07C)

  #define MC0_CH0_CR_TC_MPC_MPC_Setup_P0_OFF                           ( 0)
  #define MC0_CH0_CR_TC_MPC_MPC_Setup_P0_WID                           ( 5)
  #define MC0_CH0_CR_TC_MPC_MPC_Setup_P0_MSK                           (0x0000001F)
  #define MC0_CH0_CR_TC_MPC_MPC_Setup_P0_MIN                           (0)
  #define MC0_CH0_CR_TC_MPC_MPC_Setup_P0_MAX                           (31) // 0x0000001F
  #define MC0_CH0_CR_TC_MPC_MPC_Setup_P0_DEF                           (0x00000000)
  #define MC0_CH0_CR_TC_MPC_MPC_Setup_P0_HSH                           (0x0500E07C)

  #define MC0_CH0_CR_TC_MPC_MPC_Hold_P0_OFF                            ( 5)
  #define MC0_CH0_CR_TC_MPC_MPC_Hold_P0_WID                            ( 5)
  #define MC0_CH0_CR_TC_MPC_MPC_Hold_P0_MSK                            (0x000003E0)
  #define MC0_CH0_CR_TC_MPC_MPC_Hold_P0_MIN                            (0)
  #define MC0_CH0_CR_TC_MPC_MPC_Hold_P0_MAX                            (31) // 0x0000001F
  #define MC0_CH0_CR_TC_MPC_MPC_Hold_P0_DEF                            (0x00000000)
  #define MC0_CH0_CR_TC_MPC_MPC_Hold_P0_HSH                            (0x050AE07C)

  #define MC0_CH0_CR_TC_MPC_MultiCycCS_P0_OFF                          (10)
  #define MC0_CH0_CR_TC_MPC_MultiCycCS_P0_WID                          ( 5)
  #define MC0_CH0_CR_TC_MPC_MultiCycCS_P0_MSK                          (0x00007C00)
  #define MC0_CH0_CR_TC_MPC_MultiCycCS_P0_MIN                          (0)
  #define MC0_CH0_CR_TC_MPC_MultiCycCS_P0_MAX                          (31) // 0x0000001F
  #define MC0_CH0_CR_TC_MPC_MultiCycCS_P0_DEF                          (0x00000000)
  #define MC0_CH0_CR_TC_MPC_MultiCycCS_P0_HSH                          (0x0514E07C)

#define MC0_CH0_CR_SC_ODT_MATRIX_P0_REG                                (0x0000E080)

  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_0_P0_OFF                  ( 0)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_0_P0_WID                  ( 4)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_0_P0_MSK                  (0x0000000F)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_0_P0_MIN                  (0)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_0_P0_MAX                  (15) // 0x0000000F
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_0_P0_DEF                  (0x00000000)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_0_P0_HSH                  (0x0400E080)

  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_1_P0_OFF                  ( 4)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_1_P0_WID                  ( 4)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_1_P0_MSK                  (0x000000F0)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_1_P0_MIN                  (0)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_1_P0_MAX                  (15) // 0x0000000F
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_1_P0_DEF                  (0x00000000)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_1_P0_HSH                  (0x0408E080)

  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_2_P0_OFF                  ( 8)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_2_P0_WID                  ( 4)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_2_P0_MSK                  (0x00000F00)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_2_P0_MIN                  (0)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_2_P0_MAX                  (15) // 0x0000000F
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_2_P0_DEF                  (0x00000000)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_2_P0_HSH                  (0x0410E080)

  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_3_P0_OFF                  (12)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_3_P0_WID                  ( 4)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_3_P0_MSK                  (0x0000F000)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_3_P0_MIN                  (0)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_3_P0_MAX                  (15) // 0x0000000F
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_3_P0_DEF                  (0x00000000)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_3_P0_HSH                  (0x0418E080)

  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_0_P0_OFF                 (16)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_0_P0_WID                 ( 4)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_0_P0_MSK                 (0x000F0000)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_0_P0_MIN                 (0)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_0_P0_MAX                 (15) // 0x0000000F
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_0_P0_DEF                 (0x00000000)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_0_P0_HSH                 (0x0420E080)

  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_1_P0_OFF                 (20)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_1_P0_WID                 ( 4)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_1_P0_MSK                 (0x00F00000)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_1_P0_MIN                 (0)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_1_P0_MAX                 (15) // 0x0000000F
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_1_P0_DEF                 (0x00000000)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_1_P0_HSH                 (0x0428E080)

  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_2_P0_OFF                 (24)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_2_P0_WID                 ( 4)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_2_P0_MSK                 (0x0F000000)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_2_P0_MIN                 (0)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_2_P0_MAX                 (15) // 0x0000000F
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_2_P0_DEF                 (0x00000000)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_2_P0_HSH                 (0x0430E080)

  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_3_P0_OFF                 (28)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_3_P0_WID                 ( 4)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_3_P0_MSK                 (0xF0000000)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_3_P0_MIN                 (0)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_3_P0_MAX                 (15) // 0x0000000F
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_3_P0_DEF                 (0x00000000)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_3_P0_HSH                 (0x0438E080)

#define MC0_CH0_CR_DFT_BLOCK_P0_REG                                    (0x0000E084)

  #define MC0_CH0_CR_DFT_BLOCK_dft_block_cycles_P0_OFF                 ( 0)
  #define MC0_CH0_CR_DFT_BLOCK_dft_block_cycles_P0_WID                 (16)
  #define MC0_CH0_CR_DFT_BLOCK_dft_block_cycles_P0_MSK                 (0x0000FFFF)
  #define MC0_CH0_CR_DFT_BLOCK_dft_block_cycles_P0_MIN                 (0)
  #define MC0_CH0_CR_DFT_BLOCK_dft_block_cycles_P0_MAX                 (65535) // 0x0000FFFF
  #define MC0_CH0_CR_DFT_BLOCK_dft_block_cycles_P0_DEF                 (0x00000000)
  #define MC0_CH0_CR_DFT_BLOCK_dft_block_cycles_P0_HSH                 (0x1000E084)

  #define MC0_CH0_CR_DFT_BLOCK_dft_nonblock_cycles_P0_OFF              (16)
  #define MC0_CH0_CR_DFT_BLOCK_dft_nonblock_cycles_P0_WID              (16)
  #define MC0_CH0_CR_DFT_BLOCK_dft_nonblock_cycles_P0_MSK              (0xFFFF0000)
  #define MC0_CH0_CR_DFT_BLOCK_dft_nonblock_cycles_P0_MIN              (0)
  #define MC0_CH0_CR_DFT_BLOCK_dft_nonblock_cycles_P0_MAX              (65535) // 0x0000FFFF
  #define MC0_CH0_CR_DFT_BLOCK_dft_nonblock_cycles_P0_DEF              (0x00000000)
  #define MC0_CH0_CR_DFT_BLOCK_dft_nonblock_cycles_P0_HSH              (0x1020E084)

#define MC0_CH0_CR_SC_GS_CFG_P0_REG                                    (0x0000E088)

  #define MC0_CH0_CR_SC_GS_CFG_DRAM_technology_P0_OFF                  ( 0)
  #define MC0_CH0_CR_SC_GS_CFG_DRAM_technology_P0_WID                  ( 3)
  #define MC0_CH0_CR_SC_GS_CFG_DRAM_technology_P0_MSK                  (0x00000007)
  #define MC0_CH0_CR_SC_GS_CFG_DRAM_technology_P0_MIN                  (0)
  #define MC0_CH0_CR_SC_GS_CFG_DRAM_technology_P0_MAX                  (7) // 0x00000007
  #define MC0_CH0_CR_SC_GS_CFG_DRAM_technology_P0_DEF                  (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_DRAM_technology_P0_HSH                  (0x4300E088)

  #define MC0_CH0_CR_SC_GS_CFG_CMD_stretch_P0_OFF                      ( 3)
  #define MC0_CH0_CR_SC_GS_CFG_CMD_stretch_P0_WID                      ( 2)
  #define MC0_CH0_CR_SC_GS_CFG_CMD_stretch_P0_MSK                      (0x00000018)
  #define MC0_CH0_CR_SC_GS_CFG_CMD_stretch_P0_MIN                      (0)
  #define MC0_CH0_CR_SC_GS_CFG_CMD_stretch_P0_MAX                      (3) // 0x00000003
  #define MC0_CH0_CR_SC_GS_CFG_CMD_stretch_P0_DEF                      (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_CMD_stretch_P0_HSH                      (0x4206E088)

  #define MC0_CH0_CR_SC_GS_CFG_N_to_1_ratio_P0_OFF                     ( 5)
  #define MC0_CH0_CR_SC_GS_CFG_N_to_1_ratio_P0_WID                     ( 3)
  #define MC0_CH0_CR_SC_GS_CFG_N_to_1_ratio_P0_MSK                     (0x000000E0)
  #define MC0_CH0_CR_SC_GS_CFG_N_to_1_ratio_P0_MIN                     (0)
  #define MC0_CH0_CR_SC_GS_CFG_N_to_1_ratio_P0_MAX                     (7) // 0x00000007
  #define MC0_CH0_CR_SC_GS_CFG_N_to_1_ratio_P0_DEF                     (0x00000001)
  #define MC0_CH0_CR_SC_GS_CFG_N_to_1_ratio_P0_HSH                     (0x430AE088)

  #define MC0_CH0_CR_SC_GS_CFG_Address_mirror_P0_OFF                   ( 8)
  #define MC0_CH0_CR_SC_GS_CFG_Address_mirror_P0_WID                   ( 4)
  #define MC0_CH0_CR_SC_GS_CFG_Address_mirror_P0_MSK                   (0x00000F00)
  #define MC0_CH0_CR_SC_GS_CFG_Address_mirror_P0_MIN                   (0)
  #define MC0_CH0_CR_SC_GS_CFG_Address_mirror_P0_MAX                   (15) // 0x0000000F
  #define MC0_CH0_CR_SC_GS_CFG_Address_mirror_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_Address_mirror_P0_HSH                   (0x4410E088)

  #define MC0_CH0_CR_SC_GS_CFG_disable_odt_tristate_P0_OFF             (13)
  #define MC0_CH0_CR_SC_GS_CFG_disable_odt_tristate_P0_WID             ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_disable_odt_tristate_P0_MSK             (0x00002000)
  #define MC0_CH0_CR_SC_GS_CFG_disable_odt_tristate_P0_MIN             (0)
  #define MC0_CH0_CR_SC_GS_CFG_disable_odt_tristate_P0_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_disable_odt_tristate_P0_DEF             (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_disable_odt_tristate_P0_HSH             (0x411AE088)

  #define MC0_CH0_CR_SC_GS_CFG_disable_cs_tristate_P0_OFF              (14)
  #define MC0_CH0_CR_SC_GS_CFG_disable_cs_tristate_P0_WID              ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_disable_cs_tristate_P0_MSK              (0x00004000)
  #define MC0_CH0_CR_SC_GS_CFG_disable_cs_tristate_P0_MIN              (0)
  #define MC0_CH0_CR_SC_GS_CFG_disable_cs_tristate_P0_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_disable_cs_tristate_P0_DEF              (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_disable_cs_tristate_P0_HSH              (0x411CE088)

  #define MC0_CH0_CR_SC_GS_CFG_disable_tristate_P0_OFF                 (15)
  #define MC0_CH0_CR_SC_GS_CFG_disable_tristate_P0_WID                 ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_disable_tristate_P0_MSK                 (0x00008000)
  #define MC0_CH0_CR_SC_GS_CFG_disable_tristate_P0_MIN                 (0)
  #define MC0_CH0_CR_SC_GS_CFG_disable_tristate_P0_MAX                 (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_disable_tristate_P0_DEF                 (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_disable_tristate_P0_HSH                 (0x411EE088)

  #define MC0_CH0_CR_SC_GS_CFG_tCAL_P0_OFF                             (19)
  #define MC0_CH0_CR_SC_GS_CFG_tCAL_P0_WID                             ( 3)
  #define MC0_CH0_CR_SC_GS_CFG_tCAL_P0_MSK                             (0x00380000)
  #define MC0_CH0_CR_SC_GS_CFG_tCAL_P0_MIN                             (0)
  #define MC0_CH0_CR_SC_GS_CFG_tCAL_P0_MAX                             (7) // 0x00000007
  #define MC0_CH0_CR_SC_GS_CFG_tCAL_P0_DEF                             (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_tCAL_P0_HSH                             (0x4326E088)

  #define MC0_CH0_CR_SC_GS_CFG_frequency_point_P0_OFF                  (22)
  #define MC0_CH0_CR_SC_GS_CFG_frequency_point_P0_WID                  ( 2)
  #define MC0_CH0_CR_SC_GS_CFG_frequency_point_P0_MSK                  (0x00C00000)
  #define MC0_CH0_CR_SC_GS_CFG_frequency_point_P0_MIN                  (0)
  #define MC0_CH0_CR_SC_GS_CFG_frequency_point_P0_MAX                  (3) // 0x00000003
  #define MC0_CH0_CR_SC_GS_CFG_frequency_point_P0_DEF                  (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_frequency_point_P0_HSH                  (0x422CE088)

  #define MC0_CH0_CR_SC_GS_CFG_enable_odt_matrix_P0_OFF                (24)
  #define MC0_CH0_CR_SC_GS_CFG_enable_odt_matrix_P0_WID                ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_enable_odt_matrix_P0_MSK                (0x01000000)
  #define MC0_CH0_CR_SC_GS_CFG_enable_odt_matrix_P0_MIN                (0)
  #define MC0_CH0_CR_SC_GS_CFG_enable_odt_matrix_P0_MAX                (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_enable_odt_matrix_P0_DEF                (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_enable_odt_matrix_P0_HSH                (0x4130E088)

  #define MC0_CH0_CR_SC_GS_CFG_cs_to_cke_P0_OFF                        (25)
  #define MC0_CH0_CR_SC_GS_CFG_cs_to_cke_P0_WID                        ( 3)
  #define MC0_CH0_CR_SC_GS_CFG_cs_to_cke_P0_MSK                        (0x0E000000)
  #define MC0_CH0_CR_SC_GS_CFG_cs_to_cke_P0_MIN                        (0)
  #define MC0_CH0_CR_SC_GS_CFG_cs_to_cke_P0_MAX                        (7) // 0x00000007
  #define MC0_CH0_CR_SC_GS_CFG_cs_to_cke_P0_DEF                        (0x00000002)
  #define MC0_CH0_CR_SC_GS_CFG_cs_to_cke_P0_HSH                        (0x4332E088)

  #define MC0_CH0_CR_SC_GS_CFG_x8_device_P0_OFF                        (28)
  #define MC0_CH0_CR_SC_GS_CFG_x8_device_P0_WID                        ( 2)
  #define MC0_CH0_CR_SC_GS_CFG_x8_device_P0_MSK                        (0x30000000)
  #define MC0_CH0_CR_SC_GS_CFG_x8_device_P0_MIN                        (0)
  #define MC0_CH0_CR_SC_GS_CFG_x8_device_P0_MAX                        (3) // 0x00000003
  #define MC0_CH0_CR_SC_GS_CFG_x8_device_P0_DEF                        (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_x8_device_P0_HSH                        (0x4238E088)

  #define MC0_CH0_CR_SC_GS_CFG_no_gear2_param_divide_P0_OFF            (30)
  #define MC0_CH0_CR_SC_GS_CFG_no_gear2_param_divide_P0_WID            ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_no_gear2_param_divide_P0_MSK            (0x40000000)
  #define MC0_CH0_CR_SC_GS_CFG_no_gear2_param_divide_P0_MIN            (0)
  #define MC0_CH0_CR_SC_GS_CFG_no_gear2_param_divide_P0_MAX            (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_no_gear2_param_divide_P0_DEF            (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_no_gear2_param_divide_P0_HSH            (0x413CE088)

  #define MC0_CH0_CR_SC_GS_CFG_gear2_P0_OFF                            (31)
  #define MC0_CH0_CR_SC_GS_CFG_gear2_P0_WID                            ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_gear2_P0_MSK                            (0x80000000)
  #define MC0_CH0_CR_SC_GS_CFG_gear2_P0_MIN                            (0)
  #define MC0_CH0_CR_SC_GS_CFG_gear2_P0_MAX                            (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_gear2_P0_DEF                            (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_gear2_P0_HSH                            (0x413EE088)

  #define MC0_CH0_CR_SC_GS_CFG_ddr_1dpc_split_ranks_on_subch_P0_OFF    (32)
  #define MC0_CH0_CR_SC_GS_CFG_ddr_1dpc_split_ranks_on_subch_P0_WID    ( 2)
  #define MC0_CH0_CR_SC_GS_CFG_ddr_1dpc_split_ranks_on_subch_P0_MSK    (0x0000000300000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_ddr_1dpc_split_ranks_on_subch_P0_MIN    (0)
  #define MC0_CH0_CR_SC_GS_CFG_ddr_1dpc_split_ranks_on_subch_P0_MAX    (3) // 0x00000003
  #define MC0_CH0_CR_SC_GS_CFG_ddr_1dpc_split_ranks_on_subch_P0_DEF    (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_ddr_1dpc_split_ranks_on_subch_P0_HSH    (0x4240E088)

  #define MC0_CH0_CR_SC_GS_CFG_Limit_MM_Transitions_P0_OFF             (34)
  #define MC0_CH0_CR_SC_GS_CFG_Limit_MM_Transitions_P0_WID             ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_Limit_MM_Transitions_P0_MSK             (0x0000000400000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_Limit_MM_Transitions_P0_MIN             (0)
  #define MC0_CH0_CR_SC_GS_CFG_Limit_MM_Transitions_P0_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_Limit_MM_Transitions_P0_DEF             (0x00000001)
  #define MC0_CH0_CR_SC_GS_CFG_Limit_MM_Transitions_P0_HSH             (0x4144E088)

  #define MC0_CH0_CR_SC_GS_CFG_pl_trace_only_cs_cmd_P0_OFF             (35)
  #define MC0_CH0_CR_SC_GS_CFG_pl_trace_only_cs_cmd_P0_WID             ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_pl_trace_only_cs_cmd_P0_MSK             (0x0000000800000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_pl_trace_only_cs_cmd_P0_MIN             (0)
  #define MC0_CH0_CR_SC_GS_CFG_pl_trace_only_cs_cmd_P0_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_pl_trace_only_cs_cmd_P0_DEF             (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_pl_trace_only_cs_cmd_P0_HSH             (0x4146E088)

  #define MC0_CH0_CR_SC_GS_CFG_two_cycle_cke_idle_P0_OFF               (36)
  #define MC0_CH0_CR_SC_GS_CFG_two_cycle_cke_idle_P0_WID               ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_two_cycle_cke_idle_P0_MSK               (0x0000001000000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_two_cycle_cke_idle_P0_MIN               (0)
  #define MC0_CH0_CR_SC_GS_CFG_two_cycle_cke_idle_P0_MAX               (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_two_cycle_cke_idle_P0_DEF               (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_two_cycle_cke_idle_P0_HSH               (0x4148E088)

  #define MC0_CH0_CR_SC_GS_CFG_disable_ca_tristate_P0_OFF              (37)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ca_tristate_P0_WID              ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ca_tristate_P0_MSK              (0x0000002000000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ca_tristate_P0_MIN              (0)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ca_tristate_P0_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_disable_ca_tristate_P0_DEF              (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ca_tristate_P0_HSH              (0x414AE088)

  #define MC0_CH0_CR_SC_GS_CFG_disable_ck_tristate_P0_OFF              (38)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ck_tristate_P0_WID              ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ck_tristate_P0_MSK              (0x0000004000000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ck_tristate_P0_MIN              (0)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ck_tristate_P0_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_disable_ck_tristate_P0_DEF              (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ck_tristate_P0_HSH              (0x414CE088)

  #define MC0_CH0_CR_SC_GS_CFG_ck_to_cke_P0_OFF                        (39)
  #define MC0_CH0_CR_SC_GS_CFG_ck_to_cke_P0_WID                        ( 6)
  #define MC0_CH0_CR_SC_GS_CFG_ck_to_cke_P0_MSK                        (0x00001F8000000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_ck_to_cke_P0_MIN                        (0)
  #define MC0_CH0_CR_SC_GS_CFG_ck_to_cke_P0_MAX                        (63) // 0x0000003F
  #define MC0_CH0_CR_SC_GS_CFG_ck_to_cke_P0_DEF                        (0x00000002)
  #define MC0_CH0_CR_SC_GS_CFG_ck_to_cke_P0_HSH                        (0x464EE088)

  #define MC0_CH0_CR_SC_GS_CFG_PDE_CA11_P0_OFF                         (45)
  #define MC0_CH0_CR_SC_GS_CFG_PDE_CA11_P0_WID                         ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_PDE_CA11_P0_MSK                         (0x0000200000000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_PDE_CA11_P0_MIN                         (0)
  #define MC0_CH0_CR_SC_GS_CFG_PDE_CA11_P0_MAX                         (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_PDE_CA11_P0_DEF                         (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_PDE_CA11_P0_HSH                         (0x415AE088)

  #define MC0_CH0_CR_SC_GS_CFG_lp5_wck_tck_ratio_P0_OFF                (46)
  #define MC0_CH0_CR_SC_GS_CFG_lp5_wck_tck_ratio_P0_WID                ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_lp5_wck_tck_ratio_P0_MSK                (0x0000400000000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_lp5_wck_tck_ratio_P0_MIN                (0)
  #define MC0_CH0_CR_SC_GS_CFG_lp5_wck_tck_ratio_P0_MAX                (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_lp5_wck_tck_ratio_P0_DEF                (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_lp5_wck_tck_ratio_P0_HSH                (0x415CE088)

  #define MC0_CH0_CR_SC_GS_CFG_write0_enable_P0_OFF                    (47)
  #define MC0_CH0_CR_SC_GS_CFG_write0_enable_P0_WID                    ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_write0_enable_P0_MSK                    (0x0000800000000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_write0_enable_P0_MIN                    (0)
  #define MC0_CH0_CR_SC_GS_CFG_write0_enable_P0_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_write0_enable_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_write0_enable_P0_HSH                    (0x415EE088)

  #define MC0_CH0_CR_SC_GS_CFG_MultiCycCmd_P0_OFF                      (48)
  #define MC0_CH0_CR_SC_GS_CFG_MultiCycCmd_P0_WID                      ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_MultiCycCmd_P0_MSK                      (0x0001000000000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_MultiCycCmd_P0_MIN                      (0)
  #define MC0_CH0_CR_SC_GS_CFG_MultiCycCmd_P0_MAX                      (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_MultiCycCmd_P0_DEF                      (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_MultiCycCmd_P0_HSH                      (0x4160E088)

  #define MC0_CH0_CR_SC_GS_CFG_tCPDED_P0_OFF                           (56)
  #define MC0_CH0_CR_SC_GS_CFG_tCPDED_P0_WID                           ( 5)
  #define MC0_CH0_CR_SC_GS_CFG_tCPDED_P0_MSK                           (0x1F00000000000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_tCPDED_P0_MIN                           (0)
  #define MC0_CH0_CR_SC_GS_CFG_tCPDED_P0_MAX                           (31) // 0x0000001F
  #define MC0_CH0_CR_SC_GS_CFG_tCPDED_P0_DEF                           (0x00000001)
  #define MC0_CH0_CR_SC_GS_CFG_tCPDED_P0_HSH                           (0x4570E088)

#define MC0_CH0_CR_SC_PH_THROTTLING_0_P0_REG                           (0x0000E090)

  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_same_rank_P0_OFF        ( 0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_same_rank_P0_WID        ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_same_rank_P0_MSK        (0x0000003F)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_same_rank_P0_MIN        (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_same_rank_P0_MAX        (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_same_rank_P0_DEF        (0x00000008)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_same_rank_P0_HSH        (0x0600E090)

  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_same_rank_P0_OFF      ( 8)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_same_rank_P0_WID      ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_same_rank_P0_MSK      (0x00003F00)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_same_rank_P0_MIN      (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_same_rank_P0_MAX      (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_same_rank_P0_DEF      (0x00000001)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_same_rank_P0_HSH      (0x0610E090)

  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_different_rank_P0_OFF   (16)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_different_rank_P0_WID   ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_different_rank_P0_MSK   (0x003F0000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_different_rank_P0_MIN   (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_different_rank_P0_MAX   (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_different_rank_P0_DEF   (0x0000000C)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_different_rank_P0_HSH   (0x0620E090)

  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_different_rank_P0_OFF (24)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_different_rank_P0_WID ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_different_rank_P0_MSK (0x3F000000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_different_rank_P0_MIN (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_different_rank_P0_MAX (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_different_rank_P0_DEF (0x00000003)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_different_rank_P0_HSH (0x0630E090)

#define MC0_CH0_CR_SC_PH_THROTTLING_1_P0_REG                           (0x0000E094)

  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_same_rank_P0_OFF        ( 0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_same_rank_P0_WID        ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_same_rank_P0_MSK        (0x0000003F)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_same_rank_P0_MIN        (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_same_rank_P0_MAX        (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_same_rank_P0_DEF        (0x00000004)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_same_rank_P0_HSH        (0x0600E094)

  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_same_rank_P0_OFF      ( 8)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_same_rank_P0_WID      ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_same_rank_P0_MSK      (0x00003F00)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_same_rank_P0_MIN      (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_same_rank_P0_MAX      (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_same_rank_P0_DEF      (0x00000000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_same_rank_P0_HSH      (0x0610E094)

  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_different_rank_P0_OFF   (16)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_different_rank_P0_WID   ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_different_rank_P0_MSK   (0x003F0000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_different_rank_P0_MIN   (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_different_rank_P0_MAX   (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_different_rank_P0_DEF   (0x00000008)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_different_rank_P0_HSH   (0x0620E094)

  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_different_rank_P0_OFF (24)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_different_rank_P0_WID ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_different_rank_P0_MSK (0x3F000000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_different_rank_P0_MIN (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_different_rank_P0_MAX (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_different_rank_P0_DEF (0x00000002)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_different_rank_P0_HSH (0x0630E094)

#define MC0_CH0_CR_SC_PH_THROTTLING_2_P0_REG                           (0x0000E098)

  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_same_rank_P0_OFF        ( 0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_same_rank_P0_WID        ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_same_rank_P0_MSK        (0x0000003F)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_same_rank_P0_MIN        (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_same_rank_P0_MAX        (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_same_rank_P0_DEF        (0x00000002)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_same_rank_P0_HSH        (0x0600E098)

  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_same_rank_P0_OFF      ( 8)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_same_rank_P0_WID      ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_same_rank_P0_MSK      (0x00003F00)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_same_rank_P0_MIN      (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_same_rank_P0_MAX      (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_same_rank_P0_DEF      (0x00000000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_same_rank_P0_HSH      (0x0610E098)

  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_different_rank_P0_OFF   (16)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_different_rank_P0_WID   ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_different_rank_P0_MSK   (0x003F0000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_different_rank_P0_MIN   (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_different_rank_P0_MAX   (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_different_rank_P0_DEF   (0x00000006)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_different_rank_P0_HSH   (0x0620E098)

  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_different_rank_P0_OFF (24)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_different_rank_P0_WID ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_different_rank_P0_MSK (0x3F000000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_different_rank_P0_MIN (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_different_rank_P0_MAX (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_different_rank_P0_DEF (0x00000000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_different_rank_P0_HSH (0x0630E098)

#define MC0_CH0_CR_SC_PH_THROTTLING_3_P0_REG                           (0x0000E09C)

  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_same_rank_P0_OFF        ( 0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_same_rank_P0_WID        ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_same_rank_P0_MSK        (0x0000003F)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_same_rank_P0_MIN        (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_same_rank_P0_MAX        (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_same_rank_P0_DEF        (0x00000000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_same_rank_P0_HSH        (0x0600E09C)

  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_same_rank_P0_OFF      ( 8)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_same_rank_P0_WID      ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_same_rank_P0_MSK      (0x00003F00)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_same_rank_P0_MIN      (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_same_rank_P0_MAX      (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_same_rank_P0_DEF      (0x00000000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_same_rank_P0_HSH      (0x0610E09C)

  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_different_rank_P0_OFF   (16)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_different_rank_P0_WID   ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_different_rank_P0_MSK   (0x003F0000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_different_rank_P0_MIN   (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_different_rank_P0_MAX   (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_different_rank_P0_DEF   (0x00000000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_different_rank_P0_HSH   (0x0620E09C)

  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_different_rank_P0_OFF (24)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_different_rank_P0_WID ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_different_rank_P0_MSK (0x3F000000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_different_rank_P0_MIN (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_different_rank_P0_MAX (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_different_rank_P0_DEF (0x00000000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_different_rank_P0_HSH (0x0630E09C)

#define MC0_CH0_CR_SC_WPQ_THRESHOLD_P0_REG                             (0x0000E0A0)

  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Low_WM_P0_OFF                    ( 0)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Low_WM_P0_WID                    ( 6)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Low_WM_P0_MSK                    (0x0000003F)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Low_WM_P0_MIN                    (0)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Low_WM_P0_MAX                    (63) // 0x0000003F
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Low_WM_P0_DEF                    (0x0000000A)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Low_WM_P0_HSH                    (0x0600E0A0)

  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Med_WM_P0_OFF                    ( 6)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Med_WM_P0_WID                    ( 6)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Med_WM_P0_MSK                    (0x00000FC0)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Med_WM_P0_MIN                    (0)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Med_WM_P0_MAX                    (63) // 0x0000003F
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Med_WM_P0_DEF                    (0x00000014)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Med_WM_P0_HSH                    (0x060CE0A0)

  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_High_WM_P0_OFF                   (12)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_High_WM_P0_WID                   ( 6)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_High_WM_P0_MSK                   (0x0003F000)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_High_WM_P0_MIN                   (0)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_High_WM_P0_MAX                   (63) // 0x0000003F
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_High_WM_P0_DEF                   (0x00000024)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_High_WM_P0_HSH                   (0x0618E0A0)

  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_low_wm_P0_OFF  (18)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_low_wm_P0_WID  ( 4)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_low_wm_P0_MSK  (0x003C0000)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_low_wm_P0_MIN  (0)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_low_wm_P0_MAX  (15) // 0x0000000F
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_low_wm_P0_DEF  (0x00000001)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_low_wm_P0_HSH  (0x0424E0A0)

  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_med_wm_P0_OFF  (22)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_med_wm_P0_WID  ( 4)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_med_wm_P0_MSK  (0x03C00000)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_med_wm_P0_MIN  (0)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_med_wm_P0_MAX  (15) // 0x0000000F
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_med_wm_P0_DEF  (0x00000002)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_med_wm_P0_HSH  (0x042CE0A0)

  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_high_wm_P0_OFF (26)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_high_wm_P0_WID ( 4)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_high_wm_P0_MSK (0x3C000000)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_high_wm_P0_MIN (0)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_high_wm_P0_MAX (15) // 0x0000000F
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_high_wm_P0_DEF (0x00000004)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_high_wm_P0_HSH (0x0434E0A0)

  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_RPQ_PHs_weight_P0_OFF            (30)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_RPQ_PHs_weight_P0_WID            ( 2)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_RPQ_PHs_weight_P0_MSK            (0xC0000000)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_RPQ_PHs_weight_P0_MIN            (0)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_RPQ_PHs_weight_P0_MAX            (3) // 0x00000003
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_RPQ_PHs_weight_P0_DEF            (0x00000001)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_RPQ_PHs_weight_P0_HSH            (0x023CE0A0)

#define MC0_CH0_CR_SC_PR_CNT_CONFIG_P0_REG                             (0x0000E0A8)

  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_Ring_P0_OFF                      ( 0)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_Ring_P0_WID                      (10)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_Ring_P0_MSK                      (0x000003FF)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_Ring_P0_MIN                      (0)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_Ring_P0_MAX                      (1023) // 0x000003FF
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_Ring_P0_DEF                      (0x00000040)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_Ring_P0_HSH                      (0x4A00E0A8)

  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_SA_P0_OFF                        (10)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_SA_P0_WID                        (10)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_SA_P0_MSK                        (0x000FFC00)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_SA_P0_MIN                        (0)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_SA_P0_MAX                        (1023) // 0x000003FF
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_SA_P0_DEF                        (0x00000100)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_SA_P0_HSH                        (0x4A14E0A8)

  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC0_latency_guard_timer_x16_P0_OFF (20)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC0_latency_guard_timer_x16_P0_WID ( 9)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC0_latency_guard_timer_x16_P0_MSK (0x1FF00000)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC0_latency_guard_timer_x16_P0_MIN (0)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC0_latency_guard_timer_x16_P0_MAX (511) // 0x000001FF
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC0_latency_guard_timer_x16_P0_DEF (0x00000000)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC0_latency_guard_timer_x16_P0_HSH (0x4928E0A8)

  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_latency_guard_timer_x8_P0_OFF (32)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_latency_guard_timer_x8_P0_WID (11)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_latency_guard_timer_x8_P0_MSK (0x000007FF00000000ULL)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_latency_guard_timer_x8_P0_MIN (0)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_latency_guard_timer_x8_P0_MAX (2047) // 0x000007FF
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_latency_guard_timer_x8_P0_DEF (0x00000010)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_latency_guard_timer_x8_P0_HSH (0x4B40E0A8)

  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_Isoc_latency_guard_timer_x8_P0_OFF (43)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_Isoc_latency_guard_timer_x8_P0_WID (11)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_Isoc_latency_guard_timer_x8_P0_MSK (0x003FF80000000000ULL)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_Isoc_latency_guard_timer_x8_P0_MIN (0)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_Isoc_latency_guard_timer_x8_P0_MAX (2047) // 0x000007FF
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_Isoc_latency_guard_timer_x8_P0_DEF (0x00000008)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_Isoc_latency_guard_timer_x8_P0_HSH (0x4B56E0A8)

#define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_P0_REG                     (0x0000E0B0)

  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CKE_Override_P0_OFF      ( 0)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CKE_Override_P0_WID      ( 4)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CKE_Override_P0_MSK      (0x0000000F)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CKE_Override_P0_MIN      (0)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CKE_Override_P0_MAX      (15) // 0x0000000F
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CKE_Override_P0_DEF      (0x0000000F)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CKE_Override_P0_HSH      (0x0400E0B0)

  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_0_P0_OFF     ( 4)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_0_P0_WID     ( 4)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_0_P0_MSK     (0x000000F0)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_0_P0_MIN     (0)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_0_P0_MAX     (15) // 0x0000000F
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_0_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_0_P0_HSH     (0x0408E0B0)

  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_1_P0_OFF     ( 8)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_1_P0_WID     ( 4)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_1_P0_MSK     (0x00000F00)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_1_P0_MIN     (0)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_1_P0_MAX     (15) // 0x0000000F
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_1_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_1_P0_HSH     (0x0410E0B0)

  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CKE_On_P0_OFF            (16)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CKE_On_P0_WID            ( 4)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CKE_On_P0_MSK            (0x000F0000)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CKE_On_P0_MIN            (0)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CKE_On_P0_MAX            (15) // 0x0000000F
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CKE_On_P0_DEF            (0x00000000)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CKE_On_P0_HSH            (0x0420E0B0)

  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_Val_0_P0_OFF (20)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_Val_0_P0_WID ( 4)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_Val_0_P0_MSK (0x00F00000)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_Val_0_P0_MIN (0)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_Val_0_P0_MAX (15) // 0x0000000F
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_Val_0_P0_DEF (0x00000000)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_Val_0_P0_HSH (0x0428E0B0)

  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_Val_1_P0_OFF (24)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_Val_1_P0_WID ( 4)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_Val_1_P0_MSK (0x0F000000)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_Val_1_P0_MIN (0)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_Val_1_P0_MAX (15) // 0x0000000F
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_Val_1_P0_DEF (0x00000000)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_CS_Override_Val_1_P0_HSH (0x0430E0B0)

#define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_P0_REG                        (0x0000E0B4)

  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_Override_P0_OFF         ( 0)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_Override_P0_WID         ( 4)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_Override_P0_MSK         (0x0000000F)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_Override_P0_MIN         (0)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_Override_P0_MAX         (15) // 0x0000000F
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_Override_P0_DEF         (0x00000000)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_Override_P0_HSH         (0x0400E0B4)

  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_On_P0_OFF               (16)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_On_P0_WID               ( 4)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_On_P0_MSK               (0x000F0000)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_On_P0_MIN               (0)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_On_P0_MAX               (15) // 0x0000000F
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_On_P0_DEF               (0x00000000)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_On_P0_HSH               (0x0420E0B4)

  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_MPR_Train_DDR_On_P0_OFF     (31)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_MPR_Train_DDR_On_P0_WID     ( 1)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_MPR_Train_DDR_On_P0_MSK     (0x80000000)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_MPR_Train_DDR_On_P0_MIN     (0)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_MPR_Train_DDR_On_P0_MAX     (1) // 0x00000001
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_MPR_Train_DDR_On_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_MPR_Train_DDR_On_P0_HSH     (0x013EE0B4)

#define MC0_CH0_CR_SPID_LOW_POWER_CTL_P0_REG                           (0x0000E0B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_raise_cke_after_exit_latency_P0_OFF ( 0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_raise_cke_after_exit_latency_P0_WID ( 1)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_raise_cke_after_exit_latency_P0_MSK (0x00000001)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_raise_cke_after_exit_latency_P0_MIN (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_raise_cke_after_exit_latency_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_raise_cke_after_exit_latency_P0_DEF (0x00000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_raise_cke_after_exit_latency_P0_HSH (0x0100E0B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_latency_P0_OFF            ( 1)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_latency_P0_WID            ( 3)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_latency_P0_MSK            (0x0000000E)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_latency_P0_MIN            (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_latency_P0_MAX            (7) // 0x00000007
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_latency_P0_DEF            (0x00000001)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_latency_P0_HSH            (0x0302E0B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_length_P0_OFF             ( 4)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_length_P0_WID             ( 4)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_length_P0_MSK             (0x000000F0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_length_P0_MIN             (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_length_P0_MAX             (15) // 0x0000000F
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_length_P0_DEF             (0x00000003)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_length_P0_HSH             (0x0408E0B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_latency_P0_OFF       ( 8)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_latency_P0_WID       ( 4)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_latency_P0_MSK       (0x00000F00)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_latency_P0_MIN       (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_latency_P0_MAX       (15) // 0x0000000F
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_latency_P0_DEF       (0x00000004)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_latency_P0_HSH       (0x0410E0B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_length_P0_OFF        (12)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_length_P0_WID        ( 4)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_length_P0_MSK        (0x0000F000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_length_P0_MIN        (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_length_P0_MAX        (15) // 0x0000000F
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_length_P0_DEF        (0x00000001)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_length_P0_HSH        (0x0418E0B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_latency_P0_OFF     (16)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_latency_P0_WID     ( 4)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_latency_P0_MSK     (0x000F0000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_latency_P0_MIN     (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_latency_P0_MAX     (15) // 0x0000000F
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_latency_P0_DEF     (0x00000004)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_latency_P0_HSH     (0x0420E0B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_length_P0_OFF      (20)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_length_P0_WID      ( 4)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_length_P0_MSK      (0x00F00000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_length_P0_MIN      (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_length_P0_MAX      (15) // 0x0000000F
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_length_P0_DEF      (0x00000001)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_length_P0_HSH      (0x0428E0B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_length_P0_OFF         (24)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_length_P0_WID         ( 4)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_length_P0_MSK         (0x0F000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_length_P0_MIN         (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_length_P0_MAX         (15) // 0x0000000F
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_length_P0_DEF         (0x00000008)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_length_P0_HSH         (0x0430E0B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_enable_P0_OFF         (28)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_enable_P0_WID         ( 1)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_enable_P0_MSK         (0x10000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_enable_P0_MIN         (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_enable_P0_MAX         (1) // 0x00000001
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_enable_P0_DEF         (0x00000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_enable_P0_HSH         (0x0138E0B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_enable_P0_OFF             (29)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_enable_P0_WID             ( 1)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_enable_P0_MSK             (0x20000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_enable_P0_MIN             (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_enable_P0_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_enable_P0_DEF             (0x00000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_enable_P0_HSH             (0x013AE0B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_enable_P0_OFF        (30)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_enable_P0_WID        ( 1)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_enable_P0_MSK        (0x40000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_enable_P0_MIN        (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_enable_P0_MAX        (1) // 0x00000001
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_enable_P0_DEF        (0x00000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_enable_P0_HSH        (0x013CE0B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_enable_P0_OFF      (31)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_enable_P0_WID      ( 1)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_enable_P0_MSK      (0x80000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_enable_P0_MIN      (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_enable_P0_MAX      (1) // 0x00000001
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_enable_P0_DEF      (0x00000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_enable_P0_HSH      (0x013EE0B8)

#define MC0_CH0_CR_SC_GS_CFG_TRAINING_P0_REG                           (0x0000E0BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_P0_OFF        ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_P0_WID        ( 4)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_P0_MSK        (0x0000001E)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_P0_MIN        (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_P0_MAX        (15) // 0x0000000F
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_P0_DEF        (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_P0_HSH        (0x0402E0BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_delay_P0_OFF             ( 5)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_delay_P0_WID             ( 3)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_delay_P0_MSK             (0x000000E0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_delay_P0_MIN             (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_delay_P0_MAX             (7) // 0x00000007
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_delay_P0_DEF             (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_delay_P0_HSH             (0x030AE0BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_ignore_cke_P0_OFF              ( 8)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_ignore_cke_P0_WID              ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_ignore_cke_P0_MSK              (0x00000100)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_ignore_cke_P0_MIN              (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_ignore_cke_P0_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_ignore_cke_P0_DEF              (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_ignore_cke_P0_HSH              (0x0110E0BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_mask_cs_P0_OFF                 ( 9)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_mask_cs_P0_WID                 ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_mask_cs_P0_MSK                 (0x00000200)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_mask_cs_P0_MIN                 (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_mask_cs_P0_MAX                 (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_mask_cs_P0_DEF                 (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_mask_cs_P0_HSH                 (0x0112E0BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_lp4_fifo_rd_wr_P0_OFF          (10)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_lp4_fifo_rd_wr_P0_WID          ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_lp4_fifo_rd_wr_P0_MSK          (0x00000400)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_lp4_fifo_rd_wr_P0_MIN          (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_lp4_fifo_rd_wr_P0_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_lp4_fifo_rd_wr_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_lp4_fifo_rd_wr_P0_HSH          (0x0114E0BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_disable_tristate_P0_OFF        (11)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_disable_tristate_P0_WID        ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_disable_tristate_P0_MSK        (0x00000800)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_disable_tristate_P0_MIN        (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_disable_tristate_P0_MAX        (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_disable_tristate_P0_DEF        (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_disable_tristate_P0_HSH        (0x0116E0BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cpgc_in_order_P0_OFF           (12)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cpgc_in_order_P0_WID           ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cpgc_in_order_P0_MSK           (0x00001000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cpgc_in_order_P0_MIN           (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cpgc_in_order_P0_MAX           (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cpgc_in_order_P0_DEF           (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cpgc_in_order_P0_HSH           (0x0118E0BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cadb_enable_P0_OFF             (13)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cadb_enable_P0_WID             ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cadb_enable_P0_MSK             (0x00002000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cadb_enable_P0_MIN             (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cadb_enable_P0_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cadb_enable_P0_DEF             (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cadb_enable_P0_HSH             (0x011AE0BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_deselect_enable_P0_OFF         (14)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_deselect_enable_P0_WID         ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_deselect_enable_P0_MSK         (0x00004000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_deselect_enable_P0_MIN         (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_deselect_enable_P0_MAX         (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_deselect_enable_P0_DEF         (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_deselect_enable_P0_HSH         (0x011CE0BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Reset_CADB_P0_OFF              (15)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Reset_CADB_P0_WID              ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Reset_CADB_P0_MSK              (0x00008000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Reset_CADB_P0_MIN              (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Reset_CADB_P0_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Reset_CADB_P0_DEF              (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Reset_CADB_P0_HSH              (0x011EE0BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_bus_retain_on_n_to_1_bubble_P0_OFF (16)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_bus_retain_on_n_to_1_bubble_P0_WID ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_bus_retain_on_n_to_1_bubble_P0_MSK (0x00010000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_bus_retain_on_n_to_1_bubble_P0_MIN (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_bus_retain_on_n_to_1_bubble_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_bus_retain_on_n_to_1_bubble_P0_DEF (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_bus_retain_on_n_to_1_bubble_P0_HSH (0x0120E0BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_xarb_P0_OFF              (17)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_xarb_P0_WID              ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_xarb_P0_MSK              (0x00020000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_xarb_P0_MIN              (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_xarb_P0_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_xarb_P0_DEF              (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_xarb_P0_HSH              (0x0122E0BC)

#define MC0_CH0_CR_SCHED_THIRD_CBIT_P0_REG                             (0x0000E0C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_isoc_block_relaxation_P0_OFF ( 0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_isoc_block_relaxation_P0_WID ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_isoc_block_relaxation_P0_MSK (0x00000001)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_isoc_block_relaxation_P0_MIN (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_isoc_block_relaxation_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_isoc_block_relaxation_P0_DEF (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_isoc_block_relaxation_P0_HSH (0x0100E0C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_lp_read_blkr_P0_OFF              ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_lp_read_blkr_P0_WID              ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_lp_read_blkr_P0_MSK              (0x00000002)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_lp_read_blkr_P0_MIN              (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_lp_read_blkr_P0_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_lp_read_blkr_P0_DEF              (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_lp_read_blkr_P0_HSH              (0x0102E0C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_pe_read_for_pe_blkr_P0_OFF       ( 2)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_pe_read_for_pe_blkr_P0_WID       ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_pe_read_for_pe_blkr_P0_MSK       (0x00000004)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_pe_read_for_pe_blkr_P0_MIN       (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_pe_read_for_pe_blkr_P0_MAX       (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_pe_read_for_pe_blkr_P0_DEF       (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_pe_read_for_pe_blkr_P0_HSH       (0x0104E0C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_write_ph_blocks_read_pre_P0_OFF  ( 3)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_write_ph_blocks_read_pre_P0_WID  ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_write_ph_blocks_read_pre_P0_MSK  (0x00000008)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_write_ph_blocks_read_pre_P0_MIN  (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_write_ph_blocks_read_pre_P0_MAX  (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_write_ph_blocks_read_pre_P0_DEF  (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_write_ph_blocks_read_pre_P0_HSH  (0x0106E0C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_Read_threshold_for_lp_read_bklr_P0_OFF ( 4)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_Read_threshold_for_lp_read_bklr_P0_WID ( 6)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_Read_threshold_for_lp_read_bklr_P0_MSK (0x000003F0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_Read_threshold_for_lp_read_bklr_P0_MIN (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_Read_threshold_for_lp_read_bklr_P0_MAX (63) // 0x0000003F
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_Read_threshold_for_lp_read_bklr_P0_DEF (0x00000008)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_Read_threshold_for_lp_read_bklr_P0_HSH (0x0608E0C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_ignore_1st_zqcs_P0_OFF       (10)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_ignore_1st_zqcs_P0_WID       ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_ignore_1st_zqcs_P0_MSK       (0x00000400)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_ignore_1st_zqcs_P0_MIN       (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_ignore_1st_zqcs_P0_MAX       (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_ignore_1st_zqcs_P0_DEF       (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_ignore_1st_zqcs_P0_HSH       (0x0114E0C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_preempt_vc1_during_demote_P0_OFF (11)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_preempt_vc1_during_demote_P0_WID ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_preempt_vc1_during_demote_P0_MSK (0x00000800)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_preempt_vc1_during_demote_P0_MIN (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_preempt_vc1_during_demote_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_preempt_vc1_during_demote_P0_DEF (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_preempt_vc1_during_demote_P0_HSH (0x0116E0C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_idle_ref_start_P0_OFF        (12)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_idle_ref_start_P0_WID        ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_idle_ref_start_P0_MSK        (0x00001000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_idle_ref_start_P0_MIN        (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_idle_ref_start_P0_MAX        (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_idle_ref_start_P0_DEF        (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_idle_ref_start_P0_HSH        (0x0118E0C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_invert_ALERT_n_P0_OFF            (13)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_invert_ALERT_n_P0_WID            ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_invert_ALERT_n_P0_MSK            (0x00002000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_invert_ALERT_n_P0_MIN            (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_invert_ALERT_n_P0_MAX            (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_invert_ALERT_n_P0_DEF            (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_invert_ALERT_n_P0_HSH            (0x011AE0C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_oldest_isoch_pre_over_ph_P0_OFF (14)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_oldest_isoch_pre_over_ph_P0_WID ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_oldest_isoch_pre_over_ph_P0_MSK (0x00004000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_oldest_isoch_pre_over_ph_P0_MIN (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_oldest_isoch_pre_over_ph_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_oldest_isoch_pre_over_ph_P0_DEF (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_oldest_isoch_pre_over_ph_P0_HSH (0x011CE0C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_seperate_zq_block_P0_OFF     (15)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_seperate_zq_block_P0_WID     ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_seperate_zq_block_P0_MSK     (0x00008000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_seperate_zq_block_P0_MIN     (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_seperate_zq_block_P0_MAX     (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_seperate_zq_block_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_seperate_zq_block_P0_HSH     (0x011EE0C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_cke_off_in_refresh_P0_OFF    (16)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_cke_off_in_refresh_P0_WID    ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_cke_off_in_refresh_P0_MSK    (0x00010000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_cke_off_in_refresh_P0_MIN    (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_cke_off_in_refresh_P0_MAX    (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_cke_off_in_refresh_P0_DEF    (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_cke_off_in_refresh_P0_HSH    (0x0120E0C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_allow_ecc_dft_overrides_P0_OFF   (17)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_allow_ecc_dft_overrides_P0_WID   ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_allow_ecc_dft_overrides_P0_MSK   (0x00020000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_allow_ecc_dft_overrides_P0_MIN   (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_allow_ecc_dft_overrides_P0_MAX   (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_allow_ecc_dft_overrides_P0_DEF   (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_allow_ecc_dft_overrides_P0_HSH   (0x0122E0C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_wdb_clk_gate_P0_OFF          (18)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_wdb_clk_gate_P0_WID          ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_wdb_clk_gate_P0_MSK          (0x00040000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_wdb_clk_gate_P0_MIN          (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_wdb_clk_gate_P0_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_wdb_clk_gate_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_wdb_clk_gate_P0_HSH          (0x0124E0C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_mnt_clk_gate_P0_OFF          (19)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_mnt_clk_gate_P0_WID          ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_mnt_clk_gate_P0_MSK          (0x00080000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_mnt_clk_gate_P0_MIN          (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_mnt_clk_gate_P0_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_mnt_clk_gate_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_mnt_clk_gate_P0_HSH          (0x0126E0C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_scheds_clk_gate_P0_OFF       (20)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_scheds_clk_gate_P0_WID       ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_scheds_clk_gate_P0_MSK       (0x00100000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_scheds_clk_gate_P0_MIN       (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_scheds_clk_gate_P0_MAX       (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_scheds_clk_gate_P0_DEF       (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_scheds_clk_gate_P0_HSH       (0x0128E0C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_lpmode_on_sagv_P0_OFF        (21)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_lpmode_on_sagv_P0_WID        ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_lpmode_on_sagv_P0_MSK        (0x00200000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_lpmode_on_sagv_P0_MIN        (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_lpmode_on_sagv_P0_MAX        (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_lpmode_on_sagv_P0_DEF        (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_lpmode_on_sagv_P0_HSH        (0x012AE0C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ignore_fragment_safe_in_ref_P0_OFF (22)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ignore_fragment_safe_in_ref_P0_WID ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ignore_fragment_safe_in_ref_P0_MSK (0x00400000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ignore_fragment_safe_in_ref_P0_MIN (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ignore_fragment_safe_in_ref_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ignore_fragment_safe_in_ref_P0_DEF (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ignore_fragment_safe_in_ref_P0_HSH (0x012CE0C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cmi_short_rmw_stall_P0_OFF       (23)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cmi_short_rmw_stall_P0_WID       ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cmi_short_rmw_stall_P0_MSK       (0x00800000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cmi_short_rmw_stall_P0_MIN       (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cmi_short_rmw_stall_P0_MAX       (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cmi_short_rmw_stall_P0_DEF       (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cmi_short_rmw_stall_P0_HSH       (0x012EE0C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ipq_ignore_write_ph_P0_OFF       (24)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ipq_ignore_write_ph_P0_WID       ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ipq_ignore_write_ph_P0_MSK       (0x01000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ipq_ignore_write_ph_P0_MIN       (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ipq_ignore_write_ph_P0_MAX       (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ipq_ignore_write_ph_P0_DEF       (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ipq_ignore_write_ph_P0_HSH       (0x0130E0C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverride_P0_OFF     (25)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverride_P0_WID     ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverride_P0_MSK     (0x02000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverride_P0_MIN     (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverride_P0_MAX     (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverride_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverride_P0_HSH     (0x0132E0C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverridevalue_P0_OFF (26)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverridevalue_P0_WID ( 2)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverridevalue_P0_MSK (0x0C000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverridevalue_P0_MIN (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverridevalue_P0_MAX (3) // 0x00000003
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverridevalue_P0_DEF (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverridevalue_P0_HSH (0x0234E0C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_asdynamicmodeinsertbubble_P0_OFF (28)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_asdynamicmodeinsertbubble_P0_WID ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_asdynamicmodeinsertbubble_P0_MSK (0x10000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_asdynamicmodeinsertbubble_P0_MIN (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_asdynamicmodeinsertbubble_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_asdynamicmodeinsertbubble_P0_DEF (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_asdynamicmodeinsertbubble_P0_HSH (0x0138E0C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_read_pre_in_vc0_read_starvation_P0_OFF (29)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_read_pre_in_vc0_read_starvation_P0_WID ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_read_pre_in_vc0_read_starvation_P0_MSK (0x20000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_read_pre_in_vc0_read_starvation_P0_MIN (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_read_pre_in_vc0_read_starvation_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_read_pre_in_vc0_read_starvation_P0_DEF (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_read_pre_in_vc0_read_starvation_P0_HSH (0x013AE0C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_spare_P0_OFF                     (30)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_spare_P0_WID                     ( 2)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_spare_P0_MSK                     (0xC0000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_spare_P0_MIN                     (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_spare_P0_MAX                     (3) // 0x00000003
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_spare_P0_DEF                     (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_spare_P0_HSH                     (0x023CE0C0)

#define MC0_CH0_CR_DEADLOCK_BREAKER_P0_REG                             (0x0000E0C4)

  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_P0_OFF          ( 0)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_P0_WID          (16)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_P0_MSK          (0x0000FFFF)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_P0_MIN          (0)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_P0_MAX          (65535) // 0x0000FFFF
  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_P0_HSH          (0x1000E0C4)

  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_en_P0_OFF       (16)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_en_P0_WID       ( 1)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_en_P0_MSK       (0x00010000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_en_P0_MIN       (0)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_en_P0_MAX       (1) // 0x00000001
  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_en_P0_DEF       (0x00000000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_en_P0_HSH       (0x0120E0C4)

  #define MC0_CH0_CR_DEADLOCK_BREAKER_Preemption_threshold_en_P0_OFF   (17)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Preemption_threshold_en_P0_WID   ( 1)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Preemption_threshold_en_P0_MSK   (0x00020000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Preemption_threshold_en_P0_MIN   (0)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Preemption_threshold_en_P0_MAX   (1) // 0x00000001
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Preemption_threshold_en_P0_DEF   (0x00000000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Preemption_threshold_en_P0_HSH   (0x0122E0C4)

  #define MC0_CH0_CR_DEADLOCK_BREAKER_Stop_count_during_tt_P0_OFF      (18)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Stop_count_during_tt_P0_WID      ( 1)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Stop_count_during_tt_P0_MSK      (0x00040000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Stop_count_during_tt_P0_MIN      (0)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Stop_count_during_tt_P0_MAX      (1) // 0x00000001
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Stop_count_during_tt_P0_DEF      (0x00000000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Stop_count_during_tt_P0_HSH      (0x0124E0C4)

  #define MC0_CH0_CR_DEADLOCK_BREAKER_Attempt_refresh_on_deadlock_P0_OFF (19)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Attempt_refresh_on_deadlock_P0_WID ( 1)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Attempt_refresh_on_deadlock_P0_MSK (0x00080000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Attempt_refresh_on_deadlock_P0_MIN (0)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Attempt_refresh_on_deadlock_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Attempt_refresh_on_deadlock_P0_DEF (0x00000000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Attempt_refresh_on_deadlock_P0_HSH (0x0126E0C4)

  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_duration_P0_OFF  (20)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_duration_P0_WID  ( 8)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_duration_P0_MSK  (0x0FF00000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_duration_P0_MIN  (0)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_duration_P0_MAX  (255) // 0x000000FF
  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_duration_P0_DEF  (0x00000000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_duration_P0_HSH  (0x0828E0C4)

  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_en_P0_OFF        (28)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_en_P0_WID        ( 1)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_en_P0_MSK        (0x10000000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_en_P0_MIN        (0)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_en_P0_MAX        (1) // 0x00000001
  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_en_P0_DEF        (0x00000000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_en_P0_HSH        (0x0138E0C4)

  #define MC0_CH0_CR_DEADLOCK_BREAKER_Disable_blocking_rules_P0_OFF    (29)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Disable_blocking_rules_P0_WID    ( 1)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Disable_blocking_rules_P0_MSK    (0x20000000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Disable_blocking_rules_P0_MIN    (0)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Disable_blocking_rules_P0_MAX    (1) // 0x00000001
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Disable_blocking_rules_P0_DEF    (0x00000000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Disable_blocking_rules_P0_HSH    (0x013AE0C4)

  #define MC0_CH0_CR_DEADLOCK_BREAKER_Rank_join_P0_OFF                 (30)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Rank_join_P0_WID                 ( 2)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Rank_join_P0_MSK                 (0xC0000000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Rank_join_P0_MIN                 (0)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Rank_join_P0_MAX                 (3) // 0x00000003
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Rank_join_P0_DEF                 (0x00000000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Rank_join_P0_HSH                 (0x023CE0C4)

#define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_P0_REG                           (0x0000E0C8)

  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDWR_P0_OFF               ( 0)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDWR_P0_WID               ( 6)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDWR_P0_MSK               (0x0000003F)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDWR_P0_MIN               (0)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDWR_P0_MAX               (63) // 0x0000003F
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDWR_P0_DEF               (0x00000004)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDWR_P0_HSH               (0x0600E0C8)

  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bits01_P0_OFF ( 6)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bits01_P0_WID ( 2)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bits01_P0_MSK (0x000000C0)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bits01_P0_MIN (0)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bits01_P0_MAX (3) // 0x00000003
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bits01_P0_DEF (0x00000000)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bits01_P0_HSH (0x020CE0C8)

  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRWR_P0_OFF               ( 8)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRWR_P0_WID               ( 7)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRWR_P0_MSK               (0x00007F00)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRWR_P0_MIN               (0)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRWR_P0_MAX               (127) // 0x0000007F
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRWR_P0_DEF               (0x00000004)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRWR_P0_HSH               (0x0710E0C8)

  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bit2_P0_OFF (15)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bit2_P0_WID ( 1)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bit2_P0_MSK (0x00008000)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bit2_P0_MIN (0)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bit2_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bit2_P0_DEF (0x00000000)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bit2_P0_HSH (0x011EE0C8)

  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRRD_P0_OFF               (16)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRRD_P0_WID               ( 8)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRRD_P0_MSK               (0x00FF0000)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRRD_P0_MIN               (0)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRRD_P0_MAX               (255) // 0x000000FF
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRRD_P0_DEF               (0x00000004)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRRD_P0_HSH               (0x0820E0C8)

  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDRD_P0_OFF               (24)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDRD_P0_WID               ( 6)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDRD_P0_MSK               (0x3F000000)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDRD_P0_MIN               (0)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDRD_P0_MAX               (63) // 0x0000003F
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDRD_P0_DEF               (0x00000004)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDRD_P0_HSH               (0x0630E0C8)

#define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_P0_REG                          (0x0000E0CC)

  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_read_switch_P0_OFF ( 0)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_read_switch_P0_WID ( 1)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_read_switch_P0_MSK (0x00000001)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_read_switch_P0_MIN (0)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_read_switch_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_read_switch_P0_DEF (0x00000001)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_read_switch_P0_HSH (0x0100E0CC)

  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_write_switch_P0_OFF ( 1)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_write_switch_P0_WID ( 1)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_write_switch_P0_MSK (0x00000002)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_write_switch_P0_MIN (0)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_write_switch_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_write_switch_P0_DEF (0x00000001)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_write_switch_P0_HSH (0x0102E0CC)

  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_any_cas_switch_P0_OFF ( 2)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_any_cas_switch_P0_WID ( 1)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_any_cas_switch_P0_MSK (0x00000004)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_any_cas_switch_P0_MIN (0)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_any_cas_switch_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_any_cas_switch_P0_DEF (0x00000001)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_any_cas_switch_P0_HSH (0x0104E0CC)

  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Rank_mode_P0_OFF              ( 3)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Rank_mode_P0_WID              ( 1)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Rank_mode_P0_MSK              (0x00000008)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Rank_mode_P0_MIN              (0)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Rank_mode_P0_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Rank_mode_P0_DEF              (0x00000001)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Rank_mode_P0_HSH              (0x0106E0CC)

  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_P0_OFF              ( 4)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_P0_WID              ( 1)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_P0_MSK              (0x00000010)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_P0_MIN              (0)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_P0_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_P0_DEF              (0x00000000)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_P0_HSH              (0x0108E0CC)

  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_multiplier_P0_OFF   ( 5)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_multiplier_P0_WID   ( 2)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_multiplier_P0_MSK   (0x00000060)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_multiplier_P0_MIN   (0)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_multiplier_P0_MAX   (3) // 0x00000003
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_multiplier_P0_DEF   (0x00000001)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_multiplier_P0_HSH   (0x020AE0CC)

  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Dis_MRR_Bubble_P0_OFF         ( 7)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Dis_MRR_Bubble_P0_WID         ( 1)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Dis_MRR_Bubble_P0_MSK         (0x00000080)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Dis_MRR_Bubble_P0_MIN         (0)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Dis_MRR_Bubble_P0_MAX         (1) // 0x00000001
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Dis_MRR_Bubble_P0_DEF         (0x00000000)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Dis_MRR_Bubble_P0_HSH         (0x010EE0CC)

  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_read_switch_num_cas_P0_OFF ( 8)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_read_switch_num_cas_P0_WID ( 8)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_read_switch_num_cas_P0_MSK (0x0000FF00)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_read_switch_num_cas_P0_MIN (0)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_read_switch_num_cas_P0_MAX (255) // 0x000000FF
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_read_switch_num_cas_P0_DEF (0x00000020)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_read_switch_num_cas_P0_HSH (0x0810E0CC)

  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_write_switch_num_cas_P0_OFF (16)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_write_switch_num_cas_P0_WID ( 8)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_write_switch_num_cas_P0_MSK (0x00FF0000)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_write_switch_num_cas_P0_MIN (0)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_write_switch_num_cas_P0_MAX (255) // 0x000000FF
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_write_switch_num_cas_P0_DEF (0x00000020)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_write_switch_num_cas_P0_HSH (0x0820E0CC)

  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_any_cas_switch_num_cas_P0_OFF (24)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_any_cas_switch_num_cas_P0_WID ( 8)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_any_cas_switch_num_cas_P0_MSK (0xFF000000)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_any_cas_switch_num_cas_P0_MIN (0)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_any_cas_switch_num_cas_P0_MAX (255) // 0x000000FF
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_any_cas_switch_num_cas_P0_DEF (0x00000080)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_any_cas_switch_num_cas_P0_HSH (0x0830E0CC)

#define MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_P0_REG              (0x0000E0D0)
//Duplicate of MC0_MCMAINS_GLOBAL_DRIVER_GATE_CFG_P0_REG

#define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_P0_REG                        (0x0000E0D4)

  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_ph_blkr_P0_OFF   ( 0)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_ph_blkr_P0_WID   ( 1)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_ph_blkr_P0_MSK   (0x00000001)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_ph_blkr_P0_MIN   (0)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_ph_blkr_P0_MAX   (1) // 0x00000001
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_ph_blkr_P0_DEF   (0x00000000)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_ph_blkr_P0_HSH   (0x0100E0D4)

  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_pe_blkr_P0_OFF   ( 1)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_pe_blkr_P0_WID   ( 1)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_pe_blkr_P0_MSK   (0x00000002)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_pe_blkr_P0_MIN   (0)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_pe_blkr_P0_MAX   (1) // 0x00000001
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_pe_blkr_P0_DEF   (0x00000000)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_pe_blkr_P0_HSH   (0x0102E0D4)

  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_low_wm_allowed_preempt_priorities_P0_OFF ( 2)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_low_wm_allowed_preempt_priorities_P0_WID ( 3)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_low_wm_allowed_preempt_priorities_P0_MSK (0x0000001C)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_low_wm_allowed_preempt_priorities_P0_MIN (0)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_low_wm_allowed_preempt_priorities_P0_MAX (7) // 0x00000007
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_low_wm_allowed_preempt_priorities_P0_DEF (0x00000007)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_low_wm_allowed_preempt_priorities_P0_HSH (0x0304E0D4)

  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_med_wm_allowed_preempt_priorities_P0_OFF ( 5)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_med_wm_allowed_preempt_priorities_P0_WID ( 3)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_med_wm_allowed_preempt_priorities_P0_MSK (0x000000E0)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_med_wm_allowed_preempt_priorities_P0_MIN (0)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_med_wm_allowed_preempt_priorities_P0_MAX (7) // 0x00000007
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_med_wm_allowed_preempt_priorities_P0_DEF (0x00000006)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_med_wm_allowed_preempt_priorities_P0_HSH (0x030AE0D4)

  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_high_wm_allowed_preempt_priorities_P0_OFF ( 8)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_high_wm_allowed_preempt_priorities_P0_WID ( 3)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_high_wm_allowed_preempt_priorities_P0_MSK (0x00000700)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_high_wm_allowed_preempt_priorities_P0_MIN (0)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_high_wm_allowed_preempt_priorities_P0_MAX (7) // 0x00000007
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_high_wm_allowed_preempt_priorities_P0_DEF (0x00000004)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_high_wm_allowed_preempt_priorities_P0_HSH (0x0310E0D4)

  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_ph_block_pe_P0_OFF          (11)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_ph_block_pe_P0_WID          ( 1)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_ph_block_pe_P0_MSK          (0x00000800)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_ph_block_pe_P0_MIN          (0)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_ph_block_pe_P0_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_ph_block_pe_P0_DEF          (0x00000001)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_ph_block_pe_P0_HSH          (0x0116E0D4)

  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_blkr_effect_major_mode_P0_OFF (12)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_blkr_effect_major_mode_P0_WID ( 1)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_blkr_effect_major_mode_P0_MSK (0x00001000)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_blkr_effect_major_mode_P0_MIN (0)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_blkr_effect_major_mode_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_blkr_effect_major_mode_P0_DEF (0x00000000)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_blkr_effect_major_mode_P0_HSH (0x0118E0D4)

  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_optimization_P0_OFF  (13)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_optimization_P0_WID  ( 1)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_optimization_P0_MSK  (0x00002000)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_optimization_P0_MIN  (0)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_optimization_P0_MAX  (1) // 0x00000001
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_optimization_P0_DEF  (0x00000001)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_optimization_P0_HSH  (0x011AE0D4)

  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_prefer_VC1_P0_OFF    (14)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_prefer_VC1_P0_WID    ( 1)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_prefer_VC1_P0_MSK    (0x00004000)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_prefer_VC1_P0_MIN    (0)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_prefer_VC1_P0_MAX    (1) // 0x00000001
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_prefer_VC1_P0_DEF    (0x00000001)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_prefer_VC1_P0_HSH    (0x011CE0D4)

#define MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_P0_REG                   (0x0000E0D8)

  #define MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_ACT_COUNTER_P0_OFF     ( 0)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_ACT_COUNTER_P0_WID     (64)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_ACT_COUNTER_P0_MSK     (0xFFFFFFFFFFFFFFFFULL)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_ACT_COUNTER_P0_MIN     (0)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_ACT_COUNTER_P0_MAX     (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_ACT_COUNTER_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_ACT_COUNTER_P0_HSH     (0x4000E0D8)

#define MC0_CH0_CR_PWM_DDR_SUBCH1_ACT_COUNTER_P0_REG                   (0x0000E0E0)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_P0_REG

#define MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_P0_REG         (0x0000E0E8)

  #define MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REQ_OCCUPANCY_COUNTER_P0_OFF ( 0)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REQ_OCCUPANCY_COUNTER_P0_WID (64)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REQ_OCCUPANCY_COUNTER_P0_MSK (0xFFFFFFFFFFFFFFFFULL)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REQ_OCCUPANCY_COUNTER_P0_MIN (0)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REQ_OCCUPANCY_COUNTER_P0_MAX (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REQ_OCCUPANCY_COUNTER_P0_DEF (0x00000000)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REQ_OCCUPANCY_COUNTER_P0_HSH (0x4000E0E8)

#define MC0_CH0_CR_PWM_DDR_SUBCH1_REQ_OCCUPANCY_COUNTER_P0_REG         (0x0000E0F0)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_P0_REG

#define MC0_CH0_CR_WCK_CONFIG_P0_REG                                   (0x0000E0F8)

  #define MC0_CH0_CR_WCK_CONFIG_LP5_WCK_MODE_P0_OFF                    ( 0)
  #define MC0_CH0_CR_WCK_CONFIG_LP5_WCK_MODE_P0_WID                    ( 2)
  #define MC0_CH0_CR_WCK_CONFIG_LP5_WCK_MODE_P0_MSK                    (0x00000003)
  #define MC0_CH0_CR_WCK_CONFIG_LP5_WCK_MODE_P0_MIN                    (0)
  #define MC0_CH0_CR_WCK_CONFIG_LP5_WCK_MODE_P0_MAX                    (3) // 0x00000003
  #define MC0_CH0_CR_WCK_CONFIG_LP5_WCK_MODE_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_LP5_WCK_MODE_P0_HSH                    (0x4200E0F8)

  #define MC0_CH0_CR_WCK_CONFIG_RD_WCK_ASYNC_GAP_P0_OFF                ( 2)
  #define MC0_CH0_CR_WCK_CONFIG_RD_WCK_ASYNC_GAP_P0_WID                ( 9)
  #define MC0_CH0_CR_WCK_CONFIG_RD_WCK_ASYNC_GAP_P0_MSK                (0x000007FC)
  #define MC0_CH0_CR_WCK_CONFIG_RD_WCK_ASYNC_GAP_P0_MIN                (0)
  #define MC0_CH0_CR_WCK_CONFIG_RD_WCK_ASYNC_GAP_P0_MAX                (511) // 0x000001FF
  #define MC0_CH0_CR_WCK_CONFIG_RD_WCK_ASYNC_GAP_P0_DEF                (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_RD_WCK_ASYNC_GAP_P0_HSH                (0x4904E0F8)

  #define MC0_CH0_CR_WCK_CONFIG_WR_WCK_ASYNC_GAP_P0_OFF                (11)
  #define MC0_CH0_CR_WCK_CONFIG_WR_WCK_ASYNC_GAP_P0_WID                ( 9)
  #define MC0_CH0_CR_WCK_CONFIG_WR_WCK_ASYNC_GAP_P0_MSK                (0x000FF800)
  #define MC0_CH0_CR_WCK_CONFIG_WR_WCK_ASYNC_GAP_P0_MIN                (0)
  #define MC0_CH0_CR_WCK_CONFIG_WR_WCK_ASYNC_GAP_P0_MAX                (511) // 0x000001FF
  #define MC0_CH0_CR_WCK_CONFIG_WR_WCK_ASYNC_GAP_P0_DEF                (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_WR_WCK_ASYNC_GAP_P0_HSH                (0x4916E0F8)

  #define MC0_CH0_CR_WCK_CONFIG_WCK_OFF_IDLE_TIMER_P0_OFF              (20)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_OFF_IDLE_TIMER_P0_WID              (12)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_OFF_IDLE_TIMER_P0_MSK              (0xFFF00000)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_OFF_IDLE_TIMER_P0_MIN              (0)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_OFF_IDLE_TIMER_P0_MAX              (4095) // 0x00000FFF
  #define MC0_CH0_CR_WCK_CONFIG_WCK_OFF_IDLE_TIMER_P0_DEF              (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_OFF_IDLE_TIMER_P0_HSH              (0x4C28E0F8)

  #define MC0_CH0_CR_WCK_CONFIG_tWCKPST_P0_OFF                         (32)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKPST_P0_WID                         ( 4)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKPST_P0_MSK                         (0x0000000F00000000ULL)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKPST_P0_MIN                         (0)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKPST_P0_MAX                         (15) // 0x0000000F
  #define MC0_CH0_CR_WCK_CONFIG_tWCKPST_P0_DEF                         (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKPST_P0_HSH                         (0x4440E0F8)

  #define MC0_CH0_CR_WCK_CONFIG_tWCKOFF_P0_OFF                         (36)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKOFF_P0_WID                         ( 8)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKOFF_P0_MSK                         (0x00000FF000000000ULL)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKOFF_P0_MIN                         (0)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKOFF_P0_MAX                         (255) // 0x000000FF
  #define MC0_CH0_CR_WCK_CONFIG_tWCKOFF_P0_DEF                         (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKOFF_P0_HSH                         (0x4848E0F8)

  #define MC0_CH0_CR_WCK_CONFIG_tCASSTOP_ADDITIONAL_GAP_P0_OFF         (44)
  #define MC0_CH0_CR_WCK_CONFIG_tCASSTOP_ADDITIONAL_GAP_P0_WID         ( 5)
  #define MC0_CH0_CR_WCK_CONFIG_tCASSTOP_ADDITIONAL_GAP_P0_MSK         (0x0001F00000000000ULL)
  #define MC0_CH0_CR_WCK_CONFIG_tCASSTOP_ADDITIONAL_GAP_P0_MIN         (0)
  #define MC0_CH0_CR_WCK_CONFIG_tCASSTOP_ADDITIONAL_GAP_P0_MAX         (31) // 0x0000001F
  #define MC0_CH0_CR_WCK_CONFIG_tCASSTOP_ADDITIONAL_GAP_P0_DEF         (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_tCASSTOP_ADDITIONAL_GAP_P0_HSH         (0x4558E0F8)

  #define MC0_CH0_CR_WCK_CONFIG_WCK_MRR_SHORTER_BL_DIS_P0_OFF          (49)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_MRR_SHORTER_BL_DIS_P0_WID          ( 1)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_MRR_SHORTER_BL_DIS_P0_MSK          (0x0002000000000000ULL)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_MRR_SHORTER_BL_DIS_P0_MIN          (0)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_MRR_SHORTER_BL_DIS_P0_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_WCK_CONFIG_WCK_MRR_SHORTER_BL_DIS_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_MRR_SHORTER_BL_DIS_P0_HSH          (0x4162E0F8)

  #define MC0_CH0_CR_WCK_CONFIG_WCK_FAST_MODE_P0_OFF                   (50)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_FAST_MODE_P0_WID                   ( 1)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_FAST_MODE_P0_MSK                   (0x0004000000000000ULL)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_FAST_MODE_P0_MIN                   (0)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_FAST_MODE_P0_MAX                   (1) // 0x00000001
  #define MC0_CH0_CR_WCK_CONFIG_WCK_FAST_MODE_P0_DEF                   (0x00000001)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_FAST_MODE_P0_HSH                   (0x4164E0F8)

  #define MC0_CH0_CR_WCK_CONFIG_WXSA_P0_OFF                            (51)
  #define MC0_CH0_CR_WCK_CONFIG_WXSA_P0_WID                            ( 1)
  #define MC0_CH0_CR_WCK_CONFIG_WXSA_P0_MSK                            (0x0008000000000000ULL)
  #define MC0_CH0_CR_WCK_CONFIG_WXSA_P0_MIN                            (0)
  #define MC0_CH0_CR_WCK_CONFIG_WXSA_P0_MAX                            (1) // 0x00000001
  #define MC0_CH0_CR_WCK_CONFIG_WXSA_P0_DEF                            (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_WXSA_P0_HSH                            (0x4166E0F8)

  #define MC0_CH0_CR_WCK_CONFIG_WXSB_P0_OFF                            (52)
  #define MC0_CH0_CR_WCK_CONFIG_WXSB_P0_WID                            ( 1)
  #define MC0_CH0_CR_WCK_CONFIG_WXSB_P0_MSK                            (0x0010000000000000ULL)
  #define MC0_CH0_CR_WCK_CONFIG_WXSB_P0_MIN                            (0)
  #define MC0_CH0_CR_WCK_CONFIG_WXSB_P0_MAX                            (1) // 0x00000001
  #define MC0_CH0_CR_WCK_CONFIG_WXSB_P0_DEF                            (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_WXSB_P0_HSH                            (0x4168E0F8)

#define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_P0_REG                    (0x0000E404)

  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Refresh_Rank_Mask_P0_OFF ( 0)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Refresh_Rank_Mask_P0_WID ( 4)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Refresh_Rank_Mask_P0_MSK (0x0000000F)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Refresh_Rank_Mask_P0_MIN (0)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Refresh_Rank_Mask_P0_MAX (15) // 0x0000000F
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Refresh_Rank_Mask_P0_DEF (0x0000000F)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Refresh_Rank_Mask_P0_HSH (0x0400E404)

  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_RefZQ_En_Start_Test_Sync_P0_OFF ( 8)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_RefZQ_En_Start_Test_Sync_P0_WID ( 1)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_RefZQ_En_Start_Test_Sync_P0_MSK (0x00000100)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_RefZQ_En_Start_Test_Sync_P0_MIN (0)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_RefZQ_En_Start_Test_Sync_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_RefZQ_En_Start_Test_Sync_P0_DEF (0x00000000)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_RefZQ_En_Start_Test_Sync_P0_HSH (0x0110E404)

  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Panic_Refresh_Only_P0_OFF (31)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Panic_Refresh_Only_P0_WID ( 1)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Panic_Refresh_Only_P0_MSK (0x80000000)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Panic_Refresh_Only_P0_MIN (0)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Panic_Refresh_Only_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Panic_Refresh_Only_P0_DEF (0x00000000)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Panic_Refresh_Only_P0_HSH (0x013EE404)

#define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_P0_REG                         (0x0000E408)

  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_ZQ_Rank_Mask_P0_OFF          ( 0)
  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_ZQ_Rank_Mask_P0_WID          ( 4)
  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_ZQ_Rank_Mask_P0_MSK          (0x0000000F)
  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_ZQ_Rank_Mask_P0_MIN          (0)
  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_ZQ_Rank_Mask_P0_MAX          (15) // 0x0000000F
  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_ZQ_Rank_Mask_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_ZQ_Rank_Mask_P0_HSH          (0x0400E408)

  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_Always_Do_ZQ_P0_OFF          (31)
  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_Always_Do_ZQ_P0_WID          ( 1)
  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_Always_Do_ZQ_P0_MSK          (0x80000000)
  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_Always_Do_ZQ_P0_MIN          (0)
  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_Always_Do_ZQ_P0_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_Always_Do_ZQ_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_Always_Do_ZQ_P0_HSH          (0x013EE408)

#define MC0_CH0_CR_DDR_MR_PARAMS_P0_REG                                (0x0000E410)

  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_0_width_P0_OFF                 ( 0)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_0_width_P0_WID                 ( 2)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_0_width_P0_MSK                 (0x00000003)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_0_width_P0_MIN                 (0)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_0_width_P0_MAX                 (3) // 0x00000003
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_0_width_P0_DEF                 (0x00000000)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_0_width_P0_HSH                 (0x0200E410)

  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_1_width_P0_OFF                 ( 2)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_1_width_P0_WID                 ( 2)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_1_width_P0_MSK                 (0x0000000C)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_1_width_P0_MIN                 (0)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_1_width_P0_MAX                 (3) // 0x00000003
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_1_width_P0_DEF                 (0x00000000)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_1_width_P0_HSH                 (0x0204E410)

  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_2_width_P0_OFF                 ( 4)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_2_width_P0_WID                 ( 2)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_2_width_P0_MSK                 (0x00000030)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_2_width_P0_MIN                 (0)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_2_width_P0_MAX                 (3) // 0x00000003
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_2_width_P0_DEF                 (0x00000000)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_2_width_P0_HSH                 (0x0208E410)

  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_3_width_P0_OFF                 ( 6)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_3_width_P0_WID                 ( 2)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_3_width_P0_MSK                 (0x000000C0)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_3_width_P0_MIN                 (0)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_3_width_P0_MAX                 (3) // 0x00000003
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_3_width_P0_DEF                 (0x00000000)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_3_width_P0_HSH                 (0x020CE410)

  #define MC0_CH0_CR_DDR_MR_PARAMS_MR4_PERIOD_P0_OFF                   ( 8)
  #define MC0_CH0_CR_DDR_MR_PARAMS_MR4_PERIOD_P0_WID                   (16)
  #define MC0_CH0_CR_DDR_MR_PARAMS_MR4_PERIOD_P0_MSK                   (0x00FFFF00)
  #define MC0_CH0_CR_DDR_MR_PARAMS_MR4_PERIOD_P0_MIN                   (0)
  #define MC0_CH0_CR_DDR_MR_PARAMS_MR4_PERIOD_P0_MAX                   (65535) // 0x0000FFFF
  #define MC0_CH0_CR_DDR_MR_PARAMS_MR4_PERIOD_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_DDR_MR_PARAMS_MR4_PERIOD_P0_HSH                   (0x1010E410)

  #define MC0_CH0_CR_DDR_MR_PARAMS_DDR4_TS_readout_en_P0_OFF           (24)
  #define MC0_CH0_CR_DDR_MR_PARAMS_DDR4_TS_readout_en_P0_WID           ( 1)
  #define MC0_CH0_CR_DDR_MR_PARAMS_DDR4_TS_readout_en_P0_MSK           (0x01000000)
  #define MC0_CH0_CR_DDR_MR_PARAMS_DDR4_TS_readout_en_P0_MIN           (0)
  #define MC0_CH0_CR_DDR_MR_PARAMS_DDR4_TS_readout_en_P0_MAX           (1) // 0x00000001
  #define MC0_CH0_CR_DDR_MR_PARAMS_DDR4_TS_readout_en_P0_DEF           (0x00000001)
  #define MC0_CH0_CR_DDR_MR_PARAMS_DDR4_TS_readout_en_P0_HSH           (0x0130E410)

#define MC0_CH0_CR_DDR_MR_COMMAND_P0_REG                               (0x0000E414)

  #define MC0_CH0_CR_DDR_MR_COMMAND_Address_P0_OFF                     ( 0)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Address_P0_WID                     ( 9)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Address_P0_MSK                     (0x000001FF)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Address_P0_MIN                     (0)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Address_P0_MAX                     (511) // 0x000001FF
  #define MC0_CH0_CR_DDR_MR_COMMAND_Address_P0_DEF                     (0x00000000)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Address_P0_HSH                     (0x0900E414)

  #define MC0_CH0_CR_DDR_MR_COMMAND_Data_P0_OFF                        ( 9)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Data_P0_WID                        ( 8)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Data_P0_MSK                        (0x0001FE00)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Data_P0_MIN                        (0)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Data_P0_MAX                        (255) // 0x000000FF
  #define MC0_CH0_CR_DDR_MR_COMMAND_Data_P0_DEF                        (0x00000000)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Data_P0_HSH                        (0x0812E414)

  #define MC0_CH0_CR_DDR_MR_COMMAND_Rank_P0_OFF                        (17)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Rank_P0_WID                        ( 2)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Rank_P0_MSK                        (0x00060000)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Rank_P0_MIN                        (0)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Rank_P0_MAX                        (3) // 0x00000003
  #define MC0_CH0_CR_DDR_MR_COMMAND_Rank_P0_DEF                        (0x00000000)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Rank_P0_HSH                        (0x0222E414)

  #define MC0_CH0_CR_DDR_MR_COMMAND_Command_P0_OFF                     (19)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Command_P0_WID                     ( 2)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Command_P0_MSK                     (0x00180000)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Command_P0_MIN                     (0)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Command_P0_MAX                     (3) // 0x00000003
  #define MC0_CH0_CR_DDR_MR_COMMAND_Command_P0_DEF                     (0x00000000)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Command_P0_HSH                     (0x0226E414)

  #define MC0_CH0_CR_DDR_MR_COMMAND_DRAM_mask_P0_OFF                   (21)
  #define MC0_CH0_CR_DDR_MR_COMMAND_DRAM_mask_P0_WID                   ( 9)
  #define MC0_CH0_CR_DDR_MR_COMMAND_DRAM_mask_P0_MSK                   (0x3FE00000)
  #define MC0_CH0_CR_DDR_MR_COMMAND_DRAM_mask_P0_MIN                   (0)
  #define MC0_CH0_CR_DDR_MR_COMMAND_DRAM_mask_P0_MAX                   (511) // 0x000001FF
  #define MC0_CH0_CR_DDR_MR_COMMAND_DRAM_mask_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_DDR_MR_COMMAND_DRAM_mask_P0_HSH                   (0x092AE414)

  #define MC0_CH0_CR_DDR_MR_COMMAND_Assume_idle_P0_OFF                 (30)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Assume_idle_P0_WID                 ( 1)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Assume_idle_P0_MSK                 (0x40000000)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Assume_idle_P0_MIN                 (0)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Assume_idle_P0_MAX                 (1) // 0x00000001
  #define MC0_CH0_CR_DDR_MR_COMMAND_Assume_idle_P0_DEF                 (0x00000000)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Assume_idle_P0_HSH                 (0x013CE414)

  #define MC0_CH0_CR_DDR_MR_COMMAND_Busy_P0_OFF                        (31)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Busy_P0_WID                        ( 1)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Busy_P0_MSK                        (0x80000000)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Busy_P0_MIN                        (0)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Busy_P0_MAX                        (1) // 0x00000001
  #define MC0_CH0_CR_DDR_MR_COMMAND_Busy_P0_DEF                        (0x00000000)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Busy_P0_HSH                        (0x013EE414)

#define MC0_CH0_CR_DDR_MR_RESULT_0_P0_REG                              (0x0000E418)

  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_0_P0_OFF                   ( 0)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_0_P0_WID                   ( 8)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_0_P0_MSK                   (0x000000FF)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_0_P0_MIN                   (0)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_0_P0_MAX                   (255) // 0x000000FF
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_0_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_0_P0_HSH                   (0x0800E418)

  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_1_P0_OFF                   ( 8)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_1_P0_WID                   ( 8)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_1_P0_MSK                   (0x0000FF00)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_1_P0_MIN                   (0)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_1_P0_MAX                   (255) // 0x000000FF
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_1_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_1_P0_HSH                   (0x0810E418)

  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_2_P0_OFF                   (16)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_2_P0_WID                   ( 8)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_2_P0_MSK                   (0x00FF0000)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_2_P0_MIN                   (0)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_2_P0_MAX                   (255) // 0x000000FF
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_2_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_2_P0_HSH                   (0x0820E418)

  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_3_P0_OFF                   (24)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_3_P0_WID                   ( 8)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_3_P0_MSK                   (0xFF000000)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_3_P0_MIN                   (0)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_3_P0_MAX                   (255) // 0x000000FF
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_3_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_3_P0_HSH                   (0x0830E418)

#define MC0_CH0_CR_DDR_MR_RESULT_1_P0_REG                              (0x0000E41C)

  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_4_P0_OFF                   ( 0)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_4_P0_WID                   ( 8)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_4_P0_MSK                   (0x000000FF)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_4_P0_MIN                   (0)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_4_P0_MAX                   (255) // 0x000000FF
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_4_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_4_P0_HSH                   (0x0800E41C)

  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_5_P0_OFF                   ( 8)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_5_P0_WID                   ( 8)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_5_P0_MSK                   (0x0000FF00)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_5_P0_MIN                   (0)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_5_P0_MAX                   (255) // 0x000000FF
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_5_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_5_P0_HSH                   (0x0810E41C)

  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_6_P0_OFF                   (16)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_6_P0_WID                   ( 8)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_6_P0_MSK                   (0x00FF0000)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_6_P0_MIN                   (0)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_6_P0_MAX                   (255) // 0x000000FF
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_6_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_6_P0_HSH                   (0x0820E41C)

  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_7_P0_OFF                   (24)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_7_P0_WID                   ( 8)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_7_P0_MSK                   (0xFF000000)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_7_P0_MIN                   (0)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_7_P0_MAX                   (255) // 0x000000FF
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_7_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_7_P0_HSH                   (0x0830E41C)

#define MC0_CH0_CR_DDR_MR_RESULT_2_P0_REG                              (0x0000E420)

  #define MC0_CH0_CR_DDR_MR_RESULT_2_Device_8_P0_OFF                   ( 0)
  #define MC0_CH0_CR_DDR_MR_RESULT_2_Device_8_P0_WID                   ( 8)
  #define MC0_CH0_CR_DDR_MR_RESULT_2_Device_8_P0_MSK                   (0x000000FF)
  #define MC0_CH0_CR_DDR_MR_RESULT_2_Device_8_P0_MIN                   (0)
  #define MC0_CH0_CR_DDR_MR_RESULT_2_Device_8_P0_MAX                   (255) // 0x000000FF
  #define MC0_CH0_CR_DDR_MR_RESULT_2_Device_8_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_DDR_MR_RESULT_2_Device_8_P0_HSH                   (0x0800E420)

#define MC0_CH0_CR_MR4_RANK_TEMPERATURE_P0_REG                         (0x0000E424)

  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_0_P0_OFF                ( 0)
  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_0_P0_WID                ( 5)
  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_0_P0_MSK                (0x0000001F)
  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_0_P0_MIN                (0)
  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_0_P0_MAX                (31) // 0x0000001F
  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_0_P0_DEF                (0x00000003)
  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_0_P0_HSH                (0x0500E424)

  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_1_P0_OFF                ( 8)
  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_1_P0_WID                ( 5)
  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_1_P0_MSK                (0x00001F00)
  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_1_P0_MIN                (0)
  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_1_P0_MAX                (31) // 0x0000001F
  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_1_P0_DEF                (0x00000003)
  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_1_P0_HSH                (0x0510E424)

  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_2_P0_OFF                (16)
  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_2_P0_WID                ( 5)
  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_2_P0_MSK                (0x001F0000)
  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_2_P0_MIN                (0)
  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_2_P0_MAX                (31) // 0x0000001F
  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_2_P0_DEF                (0x00000003)
  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_2_P0_HSH                (0x0520E424)

  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_3_P0_OFF                (24)
  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_3_P0_WID                ( 5)
  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_3_P0_MSK                (0x1F000000)
  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_3_P0_MIN                (0)
  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_3_P0_MAX                (31) // 0x0000001F
  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_3_P0_DEF                (0x00000003)
  #define MC0_CH0_CR_MR4_RANK_TEMPERATURE_Rank_3_P0_HSH                (0x0530E424)

#define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_P0_REG                    (0x0000E428)

  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_0_P0_OFF           ( 0)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_0_P0_WID           ( 2)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_0_P0_MSK           (0x00000003)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_0_P0_MIN           (0)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_0_P0_MAX           (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_0_P0_DEF           (0x00000001)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_0_P0_HSH           (0x0200E428)

  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_1_P0_OFF           ( 8)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_1_P0_WID           ( 2)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_1_P0_MSK           (0x00000300)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_1_P0_MIN           (0)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_1_P0_MAX           (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_1_P0_DEF           (0x00000001)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_1_P0_HSH           (0x0210E428)

  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_2_P0_OFF           (16)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_2_P0_WID           ( 2)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_2_P0_MSK           (0x00030000)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_2_P0_MIN           (0)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_2_P0_MAX           (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_2_P0_DEF           (0x00000001)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_2_P0_HSH           (0x0220E428)

  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_3_P0_OFF           (24)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_3_P0_WID           ( 2)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_3_P0_MSK           (0x03000000)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_3_P0_MIN           (0)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_3_P0_MAX           (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_3_P0_DEF           (0x00000001)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_3_P0_HSH           (0x0230E428)

#define MC0_CH0_CR_DESWIZZLE_LOW_ERM_P0_REG                            (0x0000E430)

  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_0_P0_OFF                    ( 0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_0_P0_WID                    ( 3)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_0_P0_MSK                    (0x00000007)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_0_P0_MIN                    (0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_0_P0_MAX                    (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_0_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_0_P0_HSH                    (0x4300E430)

  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_1_P0_OFF                    ( 3)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_1_P0_WID                    ( 3)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_1_P0_MSK                    (0x00000038)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_1_P0_MIN                    (0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_1_P0_MAX                    (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_1_P0_DEF                    (0x00000001)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_1_P0_HSH                    (0x4306E430)

  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_2_P0_OFF                    ( 6)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_2_P0_WID                    ( 3)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_2_P0_MSK                    (0x000001C0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_2_P0_MIN                    (0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_2_P0_MAX                    (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_2_P0_DEF                    (0x00000002)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_2_P0_HSH                    (0x430CE430)

  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_3_P0_OFF                    ( 9)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_3_P0_WID                    ( 3)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_3_P0_MSK                    (0x00000E00)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_3_P0_MIN                    (0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_3_P0_MAX                    (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_3_P0_DEF                    (0x00000003)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_3_P0_HSH                    (0x4312E430)

  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_4_P0_OFF                    (12)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_4_P0_WID                    ( 3)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_4_P0_MSK                    (0x00007000)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_4_P0_MIN                    (0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_4_P0_MAX                    (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_4_P0_DEF                    (0x00000004)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_4_P0_HSH                    (0x4318E430)

  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_8_P0_OFF                    (15)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_8_P0_WID                    ( 3)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_8_P0_MSK                    (0x00038000)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_8_P0_MIN                    (0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_8_P0_MAX                    (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_8_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_8_P0_HSH                    (0x431EE430)

  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_9_P0_OFF                    (18)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_9_P0_WID                    ( 3)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_9_P0_MSK                    (0x001C0000)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_9_P0_MIN                    (0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_9_P0_MAX                    (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_9_P0_DEF                    (0x00000001)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_9_P0_HSH                    (0x4324E430)

  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_10_P0_OFF                   (21)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_10_P0_WID                   ( 3)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_10_P0_MSK                   (0x00E00000)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_10_P0_MIN                   (0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_10_P0_MAX                   (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_10_P0_DEF                   (0x00000002)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_10_P0_HSH                   (0x432AE430)

  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_11_P0_OFF                   (24)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_11_P0_WID                   ( 3)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_11_P0_MSK                   (0x07000000)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_11_P0_MIN                   (0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_11_P0_MAX                   (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_11_P0_DEF                   (0x00000003)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_11_P0_HSH                   (0x4330E430)

  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_12_P0_OFF                   (27)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_12_P0_WID                   ( 3)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_12_P0_MSK                   (0x38000000)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_12_P0_MIN                   (0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_12_P0_MAX                   (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_12_P0_DEF                   (0x00000004)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_12_P0_HSH                   (0x4336E430)

  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_0_P0_OFF                   (32)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_0_P0_WID                   ( 3)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_0_P0_MSK                   (0x0000000700000000ULL)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_0_P0_MIN                   (0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_0_P0_MAX                   (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_0_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_0_P0_HSH                   (0x4340E430)

  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_1_P0_OFF                   (35)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_1_P0_WID                   ( 3)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_1_P0_MSK                   (0x0000003800000000ULL)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_1_P0_MIN                   (0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_1_P0_MAX                   (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_1_P0_DEF                   (0x00000001)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_1_P0_HSH                   (0x4346E430)

#define MC0_CH0_CR_TC_RFP_P0_REG                                       (0x0000E438)

  #define MC0_CH0_CR_TC_RFP_OREF_RI_P0_OFF                             ( 0)
  #define MC0_CH0_CR_TC_RFP_OREF_RI_P0_WID                             ( 8)
  #define MC0_CH0_CR_TC_RFP_OREF_RI_P0_MSK                             (0x000000FF)
  #define MC0_CH0_CR_TC_RFP_OREF_RI_P0_MIN                             (0)
  #define MC0_CH0_CR_TC_RFP_OREF_RI_P0_MAX                             (255) // 0x000000FF
  #define MC0_CH0_CR_TC_RFP_OREF_RI_P0_DEF                             (0x0000000F)
  #define MC0_CH0_CR_TC_RFP_OREF_RI_P0_HSH                             (0x0800E438)

  #define MC0_CH0_CR_TC_RFP_Refresh_HP_WM_P0_OFF                       ( 8)
  #define MC0_CH0_CR_TC_RFP_Refresh_HP_WM_P0_WID                       ( 4)
  #define MC0_CH0_CR_TC_RFP_Refresh_HP_WM_P0_MSK                       (0x00000F00)
  #define MC0_CH0_CR_TC_RFP_Refresh_HP_WM_P0_MIN                       (0)
  #define MC0_CH0_CR_TC_RFP_Refresh_HP_WM_P0_MAX                       (15) // 0x0000000F
  #define MC0_CH0_CR_TC_RFP_Refresh_HP_WM_P0_DEF                       (0x00000008)
  #define MC0_CH0_CR_TC_RFP_Refresh_HP_WM_P0_HSH                       (0x0410E438)

  #define MC0_CH0_CR_TC_RFP_Refresh_panic_wm_P0_OFF                    (12)
  #define MC0_CH0_CR_TC_RFP_Refresh_panic_wm_P0_WID                    ( 4)
  #define MC0_CH0_CR_TC_RFP_Refresh_panic_wm_P0_MSK                    (0x0000F000)
  #define MC0_CH0_CR_TC_RFP_Refresh_panic_wm_P0_MIN                    (0)
  #define MC0_CH0_CR_TC_RFP_Refresh_panic_wm_P0_MAX                    (15) // 0x0000000F
  #define MC0_CH0_CR_TC_RFP_Refresh_panic_wm_P0_DEF                    (0x00000009)
  #define MC0_CH0_CR_TC_RFP_Refresh_panic_wm_P0_HSH                    (0x0418E438)

  #define MC0_CH0_CR_TC_RFP_HPRefOnMRS_P0_OFF                          (16)
  #define MC0_CH0_CR_TC_RFP_HPRefOnMRS_P0_WID                          ( 1)
  #define MC0_CH0_CR_TC_RFP_HPRefOnMRS_P0_MSK                          (0x00010000)
  #define MC0_CH0_CR_TC_RFP_HPRefOnMRS_P0_MIN                          (0)
  #define MC0_CH0_CR_TC_RFP_HPRefOnMRS_P0_MAX                          (1) // 0x00000001
  #define MC0_CH0_CR_TC_RFP_HPRefOnMRS_P0_DEF                          (0x00000001)
  #define MC0_CH0_CR_TC_RFP_HPRefOnMRS_P0_HSH                          (0x0120E438)

  #define MC0_CH0_CR_TC_RFP_SRX_Ref_Debits_P0_OFF                      (17)
  #define MC0_CH0_CR_TC_RFP_SRX_Ref_Debits_P0_WID                      ( 2)
  #define MC0_CH0_CR_TC_RFP_SRX_Ref_Debits_P0_MSK                      (0x00060000)
  #define MC0_CH0_CR_TC_RFP_SRX_Ref_Debits_P0_MIN                      (0)
  #define MC0_CH0_CR_TC_RFP_SRX_Ref_Debits_P0_MAX                      (3) // 0x00000003
  #define MC0_CH0_CR_TC_RFP_SRX_Ref_Debits_P0_DEF                      (0x00000001)
  #define MC0_CH0_CR_TC_RFP_SRX_Ref_Debits_P0_HSH                      (0x0222E438)

  #define MC0_CH0_CR_TC_RFP_RAISE_BLK_WAIT_P0_OFF                      (19)
  #define MC0_CH0_CR_TC_RFP_RAISE_BLK_WAIT_P0_WID                      ( 4)
  #define MC0_CH0_CR_TC_RFP_RAISE_BLK_WAIT_P0_MSK                      (0x00780000)
  #define MC0_CH0_CR_TC_RFP_RAISE_BLK_WAIT_P0_MIN                      (0)
  #define MC0_CH0_CR_TC_RFP_RAISE_BLK_WAIT_P0_MAX                      (15) // 0x0000000F
  #define MC0_CH0_CR_TC_RFP_RAISE_BLK_WAIT_P0_DEF                      (0x00000005)
  #define MC0_CH0_CR_TC_RFP_RAISE_BLK_WAIT_P0_HSH                      (0x0426E438)

  #define MC0_CH0_CR_TC_RFP_tREFIx9_P0_OFF                             (23)
  #define MC0_CH0_CR_TC_RFP_tREFIx9_P0_WID                             ( 9)
  #define MC0_CH0_CR_TC_RFP_tREFIx9_P0_MSK                             (0xFF800000)
  #define MC0_CH0_CR_TC_RFP_tREFIx9_P0_MIN                             (0)
  #define MC0_CH0_CR_TC_RFP_tREFIx9_P0_MAX                             (511) // 0x000001FF
  #define MC0_CH0_CR_TC_RFP_tREFIx9_P0_DEF                             (0x00000023)
  #define MC0_CH0_CR_TC_RFP_tREFIx9_P0_HSH                             (0x092EE438)

#define MC0_CH0_CR_TC_RFTP_P0_REG                                      (0x0000E43C)

  #define MC0_CH0_CR_TC_RFTP_tREFI_P0_OFF                              ( 0)
  #define MC0_CH0_CR_TC_RFTP_tREFI_P0_WID                              (17)
  #define MC0_CH0_CR_TC_RFTP_tREFI_P0_MSK                              (0x0001FFFF)
  #define MC0_CH0_CR_TC_RFTP_tREFI_P0_MIN                              (0)
  #define MC0_CH0_CR_TC_RFTP_tREFI_P0_MAX                              (131071) // 0x0001FFFF
  #define MC0_CH0_CR_TC_RFTP_tREFI_P0_DEF                              (0x00001004)
  #define MC0_CH0_CR_TC_RFTP_tREFI_P0_HSH                              (0x1100E43C)

  #define MC0_CH0_CR_TC_RFTP_tRFC_P0_OFF                               (17)
  #define MC0_CH0_CR_TC_RFTP_tRFC_P0_WID                               (12)
  #define MC0_CH0_CR_TC_RFTP_tRFC_P0_MSK                               (0x1FFE0000)
  #define MC0_CH0_CR_TC_RFTP_tRFC_P0_MIN                               (0)
  #define MC0_CH0_CR_TC_RFTP_tRFC_P0_MAX                               (4095) // 0x00000FFF
  #define MC0_CH0_CR_TC_RFTP_tRFC_P0_DEF                               (0x000000B4)
  #define MC0_CH0_CR_TC_RFTP_tRFC_P0_HSH                               (0x0C22E43C)

  #define MC0_CH0_CR_TC_RFTP_CounttREFIWhileRefEnOff_P0_OFF            (29)
  #define MC0_CH0_CR_TC_RFTP_CounttREFIWhileRefEnOff_P0_WID            ( 1)
  #define MC0_CH0_CR_TC_RFTP_CounttREFIWhileRefEnOff_P0_MSK            (0x20000000)
  #define MC0_CH0_CR_TC_RFTP_CounttREFIWhileRefEnOff_P0_MIN            (0)
  #define MC0_CH0_CR_TC_RFTP_CounttREFIWhileRefEnOff_P0_MAX            (1) // 0x00000001
  #define MC0_CH0_CR_TC_RFTP_CounttREFIWhileRefEnOff_P0_DEF            (0x00000000)
  #define MC0_CH0_CR_TC_RFTP_CounttREFIWhileRefEnOff_P0_HSH            (0x013AE43C)

  #define MC0_CH0_CR_TC_RFTP_AlwaysRefOnMRS_P0_OFF                     (30)
  #define MC0_CH0_CR_TC_RFTP_AlwaysRefOnMRS_P0_WID                     ( 1)
  #define MC0_CH0_CR_TC_RFTP_AlwaysRefOnMRS_P0_MSK                     (0x40000000)
  #define MC0_CH0_CR_TC_RFTP_AlwaysRefOnMRS_P0_MIN                     (0)
  #define MC0_CH0_CR_TC_RFTP_AlwaysRefOnMRS_P0_MAX                     (1) // 0x00000001
  #define MC0_CH0_CR_TC_RFTP_AlwaysRefOnMRS_P0_DEF                     (0x00000000)
  #define MC0_CH0_CR_TC_RFTP_AlwaysRefOnMRS_P0_HSH                     (0x013CE43C)

#define MC0_CH0_CR_TC_SRFTP_P0_REG                                     (0x0000E440)

  #define MC0_CH0_CR_TC_SRFTP_tXSDLL_P0_OFF                            ( 0)
  #define MC0_CH0_CR_TC_SRFTP_tXSDLL_P0_WID                            (12)
  #define MC0_CH0_CR_TC_SRFTP_tXSDLL_P0_MSK                            (0x00000FFF)
  #define MC0_CH0_CR_TC_SRFTP_tXSDLL_P0_MIN                            (0)
  #define MC0_CH0_CR_TC_SRFTP_tXSDLL_P0_MAX                            (4095) // 0x00000FFF
  #define MC0_CH0_CR_TC_SRFTP_tXSDLL_P0_DEF                            (0x00000200)
  #define MC0_CH0_CR_TC_SRFTP_tXSDLL_P0_HSH                            (0x0C00E440)

  #define MC0_CH0_CR_TC_SRFTP_tZQOPER_P0_OFF                           (15)
  #define MC0_CH0_CR_TC_SRFTP_tZQOPER_P0_WID                           (10)
  #define MC0_CH0_CR_TC_SRFTP_tZQOPER_P0_MSK                           (0x01FF8000)
  #define MC0_CH0_CR_TC_SRFTP_tZQOPER_P0_MIN                           (0)
  #define MC0_CH0_CR_TC_SRFTP_tZQOPER_P0_MAX                           (1023) // 0x000003FF
  #define MC0_CH0_CR_TC_SRFTP_tZQOPER_P0_DEF                           (0x00000100)
  #define MC0_CH0_CR_TC_SRFTP_tZQOPER_P0_HSH                           (0x0A1EE440)

  #define MC0_CH0_CR_TC_SRFTP_tMOD_P0_OFF                              (25)
  #define MC0_CH0_CR_TC_SRFTP_tMOD_P0_WID                              ( 7)
  #define MC0_CH0_CR_TC_SRFTP_tMOD_P0_MSK                              (0xFE000000)
  #define MC0_CH0_CR_TC_SRFTP_tMOD_P0_MIN                              (0)
  #define MC0_CH0_CR_TC_SRFTP_tMOD_P0_MAX                              (127) // 0x0000007F
  #define MC0_CH0_CR_TC_SRFTP_tMOD_P0_DEF                              (0x00000000)
  #define MC0_CH0_CR_TC_SRFTP_tMOD_P0_HSH                              (0x0732E440)

#define MC0_CH0_CR_MC_REFRESH_STAGGER_P0_REG                           (0x0000E444)

  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Interval_P0_OFF            ( 0)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Interval_P0_WID            (12)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Interval_P0_MSK            (0x00000FFF)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Interval_P0_MIN            (0)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Interval_P0_MAX            (4095) // 0x00000FFF
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Interval_P0_DEF            (0x00000000)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Interval_P0_HSH            (0x0C00E444)

  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_Mode_P0_OFF        (12)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_Mode_P0_WID        ( 1)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_Mode_P0_MSK        (0x00001000)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_Mode_P0_MIN        (0)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_Mode_P0_MAX        (1) // 0x00000001
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_Mode_P0_DEF        (0x00000000)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_Mode_P0_HSH        (0x0118E444)

  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Disable_Stolen_Refresh_P0_OFF  (13)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Disable_Stolen_Refresh_P0_WID  ( 1)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Disable_Stolen_Refresh_P0_MSK  (0x00002000)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Disable_Stolen_Refresh_P0_MIN  (0)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Disable_Stolen_Refresh_P0_MAX  (1) // 0x00000001
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Disable_Stolen_Refresh_P0_DEF  (0x00000000)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Disable_Stolen_Refresh_P0_HSH  (0x011AE444)

  #define MC0_CH0_CR_MC_REFRESH_STAGGER_En_Ref_Type_Display_P0_OFF     (14)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_En_Ref_Type_Display_P0_WID     ( 1)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_En_Ref_Type_Display_P0_MSK     (0x00004000)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_En_Ref_Type_Display_P0_MIN     (0)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_En_Ref_Type_Display_P0_MAX     (1) // 0x00000001
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_En_Ref_Type_Display_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_En_Ref_Type_Display_P0_HSH     (0x011CE444)

  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_En_P0_OFF          (15)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_En_P0_WID          ( 1)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_En_P0_MSK          (0x00008000)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_En_P0_MIN          (0)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_En_P0_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_En_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_En_P0_HSH          (0x011EE444)

  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Trefipulse_Stagger_Disable_P0_OFF (16)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Trefipulse_Stagger_Disable_P0_WID ( 1)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Trefipulse_Stagger_Disable_P0_MSK (0x00010000)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Trefipulse_Stagger_Disable_P0_MIN (0)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Trefipulse_Stagger_Disable_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Trefipulse_Stagger_Disable_P0_DEF (0x00000000)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Trefipulse_Stagger_Disable_P0_HSH (0x0120E444)

  #define MC0_CH0_CR_MC_REFRESH_STAGGER_WakeUpOnHPM_P0_OFF             (17)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_WakeUpOnHPM_P0_WID             ( 1)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_WakeUpOnHPM_P0_MSK             (0x00020000)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_WakeUpOnHPM_P0_MIN             (0)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_WakeUpOnHPM_P0_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_WakeUpOnHPM_P0_DEF             (0x00000000)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_WakeUpOnHPM_P0_HSH             (0x0122E444)

#define MC0_CH0_CR_TC_ZQCAL_P0_REG                                     (0x0000E448)

  #define MC0_CH0_CR_TC_ZQCAL_ZQCS_period_P0_OFF                       ( 0)
  #define MC0_CH0_CR_TC_ZQCAL_ZQCS_period_P0_WID                       (10)
  #define MC0_CH0_CR_TC_ZQCAL_ZQCS_period_P0_MSK                       (0x000003FF)
  #define MC0_CH0_CR_TC_ZQCAL_ZQCS_period_P0_MIN                       (0)
  #define MC0_CH0_CR_TC_ZQCAL_ZQCS_period_P0_MAX                       (1023) // 0x000003FF
  #define MC0_CH0_CR_TC_ZQCAL_ZQCS_period_P0_DEF                       (0x00000080)
  #define MC0_CH0_CR_TC_ZQCAL_ZQCS_period_P0_HSH                       (0x0A00E448)

  #define MC0_CH0_CR_TC_ZQCAL_tZQCS_P0_OFF                             (10)
  #define MC0_CH0_CR_TC_ZQCAL_tZQCS_P0_WID                             (10)
  #define MC0_CH0_CR_TC_ZQCAL_tZQCS_P0_MSK                             (0x000FFC00)
  #define MC0_CH0_CR_TC_ZQCAL_tZQCS_P0_MIN                             (0)
  #define MC0_CH0_CR_TC_ZQCAL_tZQCS_P0_MAX                             (1023) // 0x000003FF
  #define MC0_CH0_CR_TC_ZQCAL_tZQCS_P0_DEF                             (0x00000040)
  #define MC0_CH0_CR_TC_ZQCAL_tZQCS_P0_HSH                             (0x0A14E448)

  #define MC0_CH0_CR_TC_ZQCAL_tZQCAL_P0_OFF                            (20)
  #define MC0_CH0_CR_TC_ZQCAL_tZQCAL_P0_WID                            (12)
  #define MC0_CH0_CR_TC_ZQCAL_tZQCAL_P0_MSK                            (0xFFF00000)
  #define MC0_CH0_CR_TC_ZQCAL_tZQCAL_P0_MIN                            (0)
  #define MC0_CH0_CR_TC_ZQCAL_tZQCAL_P0_MAX                            (4095) // 0x00000FFF
  #define MC0_CH0_CR_TC_ZQCAL_tZQCAL_P0_DEF                            (0x00000320)
  #define MC0_CH0_CR_TC_ZQCAL_tZQCAL_P0_HSH                            (0x0C28E448)

#define MC0_CH0_CR_MRH_CONFIG_P0_REG                                   (0x0000E44C)

  #define MC0_CH0_CR_MRH_CONFIG_mrh_quiet_time_before_command_P0_OFF   ( 0)
  #define MC0_CH0_CR_MRH_CONFIG_mrh_quiet_time_before_command_P0_WID   (10)
  #define MC0_CH0_CR_MRH_CONFIG_mrh_quiet_time_before_command_P0_MSK   (0x000003FF)
  #define MC0_CH0_CR_MRH_CONFIG_mrh_quiet_time_before_command_P0_MIN   (0)
  #define MC0_CH0_CR_MRH_CONFIG_mrh_quiet_time_before_command_P0_MAX   (1023) // 0x000003FF
  #define MC0_CH0_CR_MRH_CONFIG_mrh_quiet_time_before_command_P0_DEF   (0x00000000)
  #define MC0_CH0_CR_MRH_CONFIG_mrh_quiet_time_before_command_P0_HSH   (0x0A00E44C)

  #define MC0_CH0_CR_MRH_CONFIG_mrh_quiet_time_after_command_P0_OFF    (10)
  #define MC0_CH0_CR_MRH_CONFIG_mrh_quiet_time_after_command_P0_WID    (10)
  #define MC0_CH0_CR_MRH_CONFIG_mrh_quiet_time_after_command_P0_MSK    (0x000FFC00)
  #define MC0_CH0_CR_MRH_CONFIG_mrh_quiet_time_after_command_P0_MIN    (0)
  #define MC0_CH0_CR_MRH_CONFIG_mrh_quiet_time_after_command_P0_MAX    (1023) // 0x000003FF
  #define MC0_CH0_CR_MRH_CONFIG_mrh_quiet_time_after_command_P0_DEF    (0x00000000)
  #define MC0_CH0_CR_MRH_CONFIG_mrh_quiet_time_after_command_P0_HSH    (0x0A14E44C)

#define MC0_CH0_CR_TC_MR4_SHADDOW_P0_REG                               (0x0000E450)

  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_low_P0_OFF                  ( 0)
  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_low_P0_WID                  ( 2)
  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_low_P0_MSK                  (0x00000003)
  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_low_P0_MIN                  (0)
  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_low_P0_MAX                  (3) // 0x00000003
  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_low_P0_DEF                  (0x00000000)
  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_low_P0_HSH                  (0x0200E450)

  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_high_P0_OFF                 ( 4)
  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_high_P0_WID                 (10)
  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_high_P0_MSK                 (0x00003FF0)
  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_high_P0_MIN                 (0)
  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_high_P0_MAX                 (1023) // 0x000003FF
  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_high_P0_DEF                 (0x00000000)
  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_high_P0_HSH                 (0x0A08E450)

#define MC0_CH0_CR_MC_INIT_STATE_P0_REG                                (0x0000E454)

  #define MC0_CH0_CR_MC_INIT_STATE_Rank_occupancy_P0_OFF               ( 0)
  #define MC0_CH0_CR_MC_INIT_STATE_Rank_occupancy_P0_WID               ( 8)
  #define MC0_CH0_CR_MC_INIT_STATE_Rank_occupancy_P0_MSK               (0x000000FF)
  #define MC0_CH0_CR_MC_INIT_STATE_Rank_occupancy_P0_MIN               (0)
  #define MC0_CH0_CR_MC_INIT_STATE_Rank_occupancy_P0_MAX               (255) // 0x000000FF
  #define MC0_CH0_CR_MC_INIT_STATE_Rank_occupancy_P0_DEF               (0x0000000F)
  #define MC0_CH0_CR_MC_INIT_STATE_Rank_occupancy_P0_HSH               (0x0800E454)

  #define MC0_CH0_CR_MC_INIT_STATE_SRX_reset_P0_OFF                    ( 8)
  #define MC0_CH0_CR_MC_INIT_STATE_SRX_reset_P0_WID                    ( 1)
  #define MC0_CH0_CR_MC_INIT_STATE_SRX_reset_P0_MSK                    (0x00000100)
  #define MC0_CH0_CR_MC_INIT_STATE_SRX_reset_P0_MIN                    (0)
  #define MC0_CH0_CR_MC_INIT_STATE_SRX_reset_P0_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_MC_INIT_STATE_SRX_reset_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_MC_INIT_STATE_SRX_reset_P0_HSH                    (0x0110E454)

  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_P0_OFF           ( 9)
  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_P0_WID           ( 1)
  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_P0_MSK           (0x00000200)
  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_P0_MIN           (0)
  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_P0_MAX           (1) // 0x00000001
  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_P0_DEF           (0x00000000)
  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_P0_HSH           (0x0112E454)

  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_tracking_P0_OFF  (10)
  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_tracking_P0_WID  ( 1)
  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_tracking_P0_MSK  (0x00000400)
  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_tracking_P0_MIN  (0)
  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_tracking_P0_MAX  (1) // 0x00000001
  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_tracking_P0_DEF  (0x00000000)
  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_tracking_P0_HSH  (0x0114E454)

  #define MC0_CH0_CR_MC_INIT_STATE_Reset_refresh_debt_P0_OFF           (11)
  #define MC0_CH0_CR_MC_INIT_STATE_Reset_refresh_debt_P0_WID           ( 1)
  #define MC0_CH0_CR_MC_INIT_STATE_Reset_refresh_debt_P0_MSK           (0x00000800)
  #define MC0_CH0_CR_MC_INIT_STATE_Reset_refresh_debt_P0_MIN           (0)
  #define MC0_CH0_CR_MC_INIT_STATE_Reset_refresh_debt_P0_MAX           (1) // 0x00000001
  #define MC0_CH0_CR_MC_INIT_STATE_Reset_refresh_debt_P0_DEF           (0x00000000)
  #define MC0_CH0_CR_MC_INIT_STATE_Reset_refresh_debt_P0_HSH           (0x0116E454)

  #define MC0_CH0_CR_MC_INIT_STATE_Deep_SRX_reset_P0_OFF               (12)
  #define MC0_CH0_CR_MC_INIT_STATE_Deep_SRX_reset_P0_WID               ( 1)
  #define MC0_CH0_CR_MC_INIT_STATE_Deep_SRX_reset_P0_MSK               (0x00001000)
  #define MC0_CH0_CR_MC_INIT_STATE_Deep_SRX_reset_P0_MIN               (0)
  #define MC0_CH0_CR_MC_INIT_STATE_Deep_SRX_reset_P0_MAX               (1) // 0x00000001
  #define MC0_CH0_CR_MC_INIT_STATE_Deep_SRX_reset_P0_DEF               (0x00000000)
  #define MC0_CH0_CR_MC_INIT_STATE_Deep_SRX_reset_P0_HSH               (0x0118E454)

#define MC0_CH0_CR_WDB_VISA_SEL_P0_REG                                 (0x0000E458)

  #define MC0_CH0_CR_WDB_VISA_SEL_VISAByteSel_P0_OFF                   ( 0)
  #define MC0_CH0_CR_WDB_VISA_SEL_VISAByteSel_P0_WID                   ( 3)
  #define MC0_CH0_CR_WDB_VISA_SEL_VISAByteSel_P0_MSK                   (0x00000007)
  #define MC0_CH0_CR_WDB_VISA_SEL_VISAByteSel_P0_MIN                   (0)
  #define MC0_CH0_CR_WDB_VISA_SEL_VISAByteSel_P0_MAX                   (7) // 0x00000007
  #define MC0_CH0_CR_WDB_VISA_SEL_VISAByteSel_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_WDB_VISA_SEL_VISAByteSel_P0_HSH                   (0x0300E458)

  #define MC0_CH0_CR_WDB_VISA_SEL_RefFSMRankSel_P0_OFF                 ( 8)
  #define MC0_CH0_CR_WDB_VISA_SEL_RefFSMRankSel_P0_WID                 ( 2)
  #define MC0_CH0_CR_WDB_VISA_SEL_RefFSMRankSel_P0_MSK                 (0x00000300)
  #define MC0_CH0_CR_WDB_VISA_SEL_RefFSMRankSel_P0_MIN                 (0)
  #define MC0_CH0_CR_WDB_VISA_SEL_RefFSMRankSel_P0_MAX                 (3) // 0x00000003
  #define MC0_CH0_CR_WDB_VISA_SEL_RefFSMRankSel_P0_DEF                 (0x00000000)
  #define MC0_CH0_CR_WDB_VISA_SEL_RefFSMRankSel_P0_HSH                 (0x0210E458)

  #define MC0_CH0_CR_WDB_VISA_SEL_Ref_counterSel_P0_OFF                (10)
  #define MC0_CH0_CR_WDB_VISA_SEL_Ref_counterSel_P0_WID                ( 3)
  #define MC0_CH0_CR_WDB_VISA_SEL_Ref_counterSel_P0_MSK                (0x00001C00)
  #define MC0_CH0_CR_WDB_VISA_SEL_Ref_counterSel_P0_MIN                (0)
  #define MC0_CH0_CR_WDB_VISA_SEL_Ref_counterSel_P0_MAX                (7) // 0x00000007
  #define MC0_CH0_CR_WDB_VISA_SEL_Ref_counterSel_P0_DEF                (0x00000007)
  #define MC0_CH0_CR_WDB_VISA_SEL_Ref_counterSel_P0_HSH                (0x0314E458)

  #define MC0_CH0_CR_WDB_VISA_SEL_Enable_Ref_Status_Sample_P0_OFF      (13)
  #define MC0_CH0_CR_WDB_VISA_SEL_Enable_Ref_Status_Sample_P0_WID      ( 1)
  #define MC0_CH0_CR_WDB_VISA_SEL_Enable_Ref_Status_Sample_P0_MSK      (0x00002000)
  #define MC0_CH0_CR_WDB_VISA_SEL_Enable_Ref_Status_Sample_P0_MIN      (0)
  #define MC0_CH0_CR_WDB_VISA_SEL_Enable_Ref_Status_Sample_P0_MAX      (1) // 0x00000001
  #define MC0_CH0_CR_WDB_VISA_SEL_Enable_Ref_Status_Sample_P0_DEF      (0x00000000)
  #define MC0_CH0_CR_WDB_VISA_SEL_Enable_Ref_Status_Sample_P0_HSH      (0x011AE458)

#define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_P0_REG                          (0x0000E460)

  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM0_IDLE_ENERGY_P0_OFF      ( 0)
  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM0_IDLE_ENERGY_P0_WID      ( 6)
  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM0_IDLE_ENERGY_P0_MSK      (0x0000003F)
  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM0_IDLE_ENERGY_P0_MIN      (0)
  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM0_IDLE_ENERGY_P0_MAX      (63) // 0x0000003F
  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM0_IDLE_ENERGY_P0_DEF      (0x00000000)
  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM0_IDLE_ENERGY_P0_HSH      (0x0600E460)

  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM1_IDLE_ENERGY_P0_OFF      ( 8)
  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM1_IDLE_ENERGY_P0_WID      ( 6)
  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM1_IDLE_ENERGY_P0_MSK      (0x00003F00)
  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM1_IDLE_ENERGY_P0_MIN      (0)
  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM1_IDLE_ENERGY_P0_MAX      (63) // 0x0000003F
  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM1_IDLE_ENERGY_P0_DEF      (0x00000000)
  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM1_IDLE_ENERGY_P0_HSH      (0x0610E460)

#define MC0_CH0_CR_PM_DIMM_PD_ENERGY_P0_REG                            (0x0000E464)

  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM0_PD_ENERGY_P0_OFF          ( 0)
  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM0_PD_ENERGY_P0_WID          ( 6)
  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM0_PD_ENERGY_P0_MSK          (0x0000003F)
  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM0_PD_ENERGY_P0_MIN          (0)
  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM0_PD_ENERGY_P0_MAX          (63) // 0x0000003F
  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM0_PD_ENERGY_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM0_PD_ENERGY_P0_HSH          (0x0600E464)

  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM1_PD_ENERGY_P0_OFF          ( 8)
  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM1_PD_ENERGY_P0_WID          ( 6)
  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM1_PD_ENERGY_P0_MSK          (0x00003F00)
  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM1_PD_ENERGY_P0_MIN          (0)
  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM1_PD_ENERGY_P0_MAX          (63) // 0x0000003F
  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM1_PD_ENERGY_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM1_PD_ENERGY_P0_HSH          (0x0610E464)

#define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_P0_REG                           (0x0000E468)

  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM0_ACT_ENERGY_P0_OFF        ( 0)
  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM0_ACT_ENERGY_P0_WID        ( 8)
  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM0_ACT_ENERGY_P0_MSK        (0x000000FF)
  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM0_ACT_ENERGY_P0_MIN        (0)
  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM0_ACT_ENERGY_P0_MAX        (255) // 0x000000FF
  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM0_ACT_ENERGY_P0_DEF        (0x00000000)
  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM0_ACT_ENERGY_P0_HSH        (0x0800E468)

  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM1_ACT_ENERGY_P0_OFF        ( 8)
  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM1_ACT_ENERGY_P0_WID        ( 8)
  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM1_ACT_ENERGY_P0_MSK        (0x0000FF00)
  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM1_ACT_ENERGY_P0_MIN        (0)
  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM1_ACT_ENERGY_P0_MAX        (255) // 0x000000FF
  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM1_ACT_ENERGY_P0_DEF        (0x00000000)
  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM1_ACT_ENERGY_P0_HSH        (0x0810E468)

#define MC0_CH0_CR_PM_DIMM_RD_ENERGY_P0_REG                            (0x0000E46C)

  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM0_RD_ENERGY_P0_OFF          ( 0)
  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM0_RD_ENERGY_P0_WID          ( 8)
  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM0_RD_ENERGY_P0_MSK          (0x000000FF)
  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM0_RD_ENERGY_P0_MIN          (0)
  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM0_RD_ENERGY_P0_MAX          (255) // 0x000000FF
  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM0_RD_ENERGY_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM0_RD_ENERGY_P0_HSH          (0x0800E46C)

  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM1_RD_ENERGY_P0_OFF          ( 8)
  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM1_RD_ENERGY_P0_WID          ( 8)
  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM1_RD_ENERGY_P0_MSK          (0x0000FF00)
  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM1_RD_ENERGY_P0_MIN          (0)
  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM1_RD_ENERGY_P0_MAX          (255) // 0x000000FF
  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM1_RD_ENERGY_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM1_RD_ENERGY_P0_HSH          (0x0810E46C)

#define MC0_CH0_CR_PM_DIMM_WR_ENERGY_P0_REG                            (0x0000E470)

  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM0_WR_ENERGY_P0_OFF          ( 0)
  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM0_WR_ENERGY_P0_WID          ( 8)
  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM0_WR_ENERGY_P0_MSK          (0x000000FF)
  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM0_WR_ENERGY_P0_MIN          (0)
  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM0_WR_ENERGY_P0_MAX          (255) // 0x000000FF
  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM0_WR_ENERGY_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM0_WR_ENERGY_P0_HSH          (0x0800E470)

  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM1_WR_ENERGY_P0_OFF          ( 8)
  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM1_WR_ENERGY_P0_WID          ( 8)
  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM1_WR_ENERGY_P0_MSK          (0x0000FF00)
  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM1_WR_ENERGY_P0_MIN          (0)
  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM1_WR_ENERGY_P0_MAX          (255) // 0x000000FF
  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM1_WR_ENERGY_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM1_WR_ENERGY_P0_HSH          (0x0810E470)

#define MC0_CH0_CR_SC_WR_DELAY_P0_REG                                  (0x0000E478)

  #define MC0_CH0_CR_SC_WR_DELAY_Dec_tCWL_P0_OFF                       ( 0)
  #define MC0_CH0_CR_SC_WR_DELAY_Dec_tCWL_P0_WID                       ( 6)
  #define MC0_CH0_CR_SC_WR_DELAY_Dec_tCWL_P0_MSK                       (0x0000003F)
  #define MC0_CH0_CR_SC_WR_DELAY_Dec_tCWL_P0_MIN                       (0)
  #define MC0_CH0_CR_SC_WR_DELAY_Dec_tCWL_P0_MAX                       (63) // 0x0000003F
  #define MC0_CH0_CR_SC_WR_DELAY_Dec_tCWL_P0_DEF                       (0x00000003)
  #define MC0_CH0_CR_SC_WR_DELAY_Dec_tCWL_P0_HSH                       (0x0600E478)

  #define MC0_CH0_CR_SC_WR_DELAY_Add_tCWL_P0_OFF                       ( 6)
  #define MC0_CH0_CR_SC_WR_DELAY_Add_tCWL_P0_WID                       ( 6)
  #define MC0_CH0_CR_SC_WR_DELAY_Add_tCWL_P0_MSK                       (0x00000FC0)
  #define MC0_CH0_CR_SC_WR_DELAY_Add_tCWL_P0_MIN                       (0)
  #define MC0_CH0_CR_SC_WR_DELAY_Add_tCWL_P0_MAX                       (63) // 0x0000003F
  #define MC0_CH0_CR_SC_WR_DELAY_Add_tCWL_P0_DEF                       (0x00000000)
  #define MC0_CH0_CR_SC_WR_DELAY_Add_tCWL_P0_HSH                       (0x060CE478)

  #define MC0_CH0_CR_SC_WR_DELAY_Add_1Qclk_delay_P0_OFF                (12)
  #define MC0_CH0_CR_SC_WR_DELAY_Add_1Qclk_delay_P0_WID                ( 1)
  #define MC0_CH0_CR_SC_WR_DELAY_Add_1Qclk_delay_P0_MSK                (0x00001000)
  #define MC0_CH0_CR_SC_WR_DELAY_Add_1Qclk_delay_P0_MIN                (0)
  #define MC0_CH0_CR_SC_WR_DELAY_Add_1Qclk_delay_P0_MAX                (1) // 0x00000001
  #define MC0_CH0_CR_SC_WR_DELAY_Add_1Qclk_delay_P0_DEF                (0x00000000)
  #define MC0_CH0_CR_SC_WR_DELAY_Add_1Qclk_delay_P0_HSH                (0x0118E478)

#define MC0_CH0_CR_READ_RETURN_DFT_P0_REG                              (0x0000E47C)

  #define MC0_CH0_CR_READ_RETURN_DFT_ECC_P0_OFF                        ( 0)
  #define MC0_CH0_CR_READ_RETURN_DFT_ECC_P0_WID                        ( 8)
  #define MC0_CH0_CR_READ_RETURN_DFT_ECC_P0_MSK                        (0x000000FF)
  #define MC0_CH0_CR_READ_RETURN_DFT_ECC_P0_MIN                        (0)
  #define MC0_CH0_CR_READ_RETURN_DFT_ECC_P0_MAX                        (255) // 0x000000FF
  #define MC0_CH0_CR_READ_RETURN_DFT_ECC_P0_DEF                        (0x00000000)
  #define MC0_CH0_CR_READ_RETURN_DFT_ECC_P0_HSH                        (0x0800E47C)

  #define MC0_CH0_CR_READ_RETURN_DFT_RRD_DFT_Mode_P0_OFF               ( 8)
  #define MC0_CH0_CR_READ_RETURN_DFT_RRD_DFT_Mode_P0_WID               ( 2)
  #define MC0_CH0_CR_READ_RETURN_DFT_RRD_DFT_Mode_P0_MSK               (0x00000300)
  #define MC0_CH0_CR_READ_RETURN_DFT_RRD_DFT_Mode_P0_MIN               (0)
  #define MC0_CH0_CR_READ_RETURN_DFT_RRD_DFT_Mode_P0_MAX               (3) // 0x00000003
  #define MC0_CH0_CR_READ_RETURN_DFT_RRD_DFT_Mode_P0_DEF               (0x00000000)
  #define MC0_CH0_CR_READ_RETURN_DFT_RRD_DFT_Mode_P0_HSH               (0x0210E47C)

  #define MC0_CH0_CR_READ_RETURN_DFT_LFSR_Seed_Index_P0_OFF            (10)
  #define MC0_CH0_CR_READ_RETURN_DFT_LFSR_Seed_Index_P0_WID            ( 5)
  #define MC0_CH0_CR_READ_RETURN_DFT_LFSR_Seed_Index_P0_MSK            (0x00007C00)
  #define MC0_CH0_CR_READ_RETURN_DFT_LFSR_Seed_Index_P0_MIN            (0)
  #define MC0_CH0_CR_READ_RETURN_DFT_LFSR_Seed_Index_P0_MAX            (31) // 0x0000001F
  #define MC0_CH0_CR_READ_RETURN_DFT_LFSR_Seed_Index_P0_DEF            (0x00000000)
  #define MC0_CH0_CR_READ_RETURN_DFT_LFSR_Seed_Index_P0_HSH            (0x0514E47C)

  #define MC0_CH0_CR_READ_RETURN_DFT_Inversion_Mode_P0_OFF             (15)
  #define MC0_CH0_CR_READ_RETURN_DFT_Inversion_Mode_P0_WID             ( 1)
  #define MC0_CH0_CR_READ_RETURN_DFT_Inversion_Mode_P0_MSK             (0x00008000)
  #define MC0_CH0_CR_READ_RETURN_DFT_Inversion_Mode_P0_MIN             (0)
  #define MC0_CH0_CR_READ_RETURN_DFT_Inversion_Mode_P0_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_READ_RETURN_DFT_Inversion_Mode_P0_DEF             (0x00000000)
  #define MC0_CH0_CR_READ_RETURN_DFT_Inversion_Mode_P0_HSH             (0x011EE47C)

  #define MC0_CH0_CR_READ_RETURN_DFT_AddressBased_P0_OFF               (16)
  #define MC0_CH0_CR_READ_RETURN_DFT_AddressBased_P0_WID               ( 1)
  #define MC0_CH0_CR_READ_RETURN_DFT_AddressBased_P0_MSK               (0x00010000)
  #define MC0_CH0_CR_READ_RETURN_DFT_AddressBased_P0_MIN               (0)
  #define MC0_CH0_CR_READ_RETURN_DFT_AddressBased_P0_MAX               (1) // 0x00000001
  #define MC0_CH0_CR_READ_RETURN_DFT_AddressBased_P0_DEF               (0x00000000)
  #define MC0_CH0_CR_READ_RETURN_DFT_AddressBased_P0_HSH               (0x0120E47C)

#define MC0_CH0_CR_DESWIZZLE_LOW_P0_REG                                (0x0000E480)
//Duplicate of MC0_CH0_CR_DESWIZZLE_LOW_ERM_P0_REG

#define MC0_CH0_CR_SC_PBR_P0_REG                                       (0x0000E488)

  #define MC0_CH0_CR_SC_PBR_PBR_Disable_P0_OFF                         ( 0)
  #define MC0_CH0_CR_SC_PBR_PBR_Disable_P0_WID                         ( 1)
  #define MC0_CH0_CR_SC_PBR_PBR_Disable_P0_MSK                         (0x00000001)
  #define MC0_CH0_CR_SC_PBR_PBR_Disable_P0_MIN                         (0)
  #define MC0_CH0_CR_SC_PBR_PBR_Disable_P0_MAX                         (1) // 0x00000001
  #define MC0_CH0_CR_SC_PBR_PBR_Disable_P0_DEF                         (0x00000001)
  #define MC0_CH0_CR_SC_PBR_PBR_Disable_P0_HSH                         (0x0100E488)

  #define MC0_CH0_CR_SC_PBR_PBR_OOO_Dis_P0_OFF                         ( 1)
  #define MC0_CH0_CR_SC_PBR_PBR_OOO_Dis_P0_WID                         ( 1)
  #define MC0_CH0_CR_SC_PBR_PBR_OOO_Dis_P0_MSK                         (0x00000002)
  #define MC0_CH0_CR_SC_PBR_PBR_OOO_Dis_P0_MIN                         (0)
  #define MC0_CH0_CR_SC_PBR_PBR_OOO_Dis_P0_MAX                         (1) // 0x00000001
  #define MC0_CH0_CR_SC_PBR_PBR_OOO_Dis_P0_DEF                         (0x00000000)
  #define MC0_CH0_CR_SC_PBR_PBR_OOO_Dis_P0_HSH                         (0x0102E488)

  #define MC0_CH0_CR_SC_PBR_PBR_Issue_NOP_P0_OFF                       ( 2)
  #define MC0_CH0_CR_SC_PBR_PBR_Issue_NOP_P0_WID                       ( 1)
  #define MC0_CH0_CR_SC_PBR_PBR_Issue_NOP_P0_MSK                       (0x00000004)
  #define MC0_CH0_CR_SC_PBR_PBR_Issue_NOP_P0_MIN                       (0)
  #define MC0_CH0_CR_SC_PBR_PBR_Issue_NOP_P0_MAX                       (1) // 0x00000001
  #define MC0_CH0_CR_SC_PBR_PBR_Issue_NOP_P0_DEF                       (0x00000000)
  #define MC0_CH0_CR_SC_PBR_PBR_Issue_NOP_P0_HSH                       (0x0104E488)

  #define MC0_CH0_CR_SC_PBR_PBR_Disable_on_hot_P0_OFF                  ( 3)
  #define MC0_CH0_CR_SC_PBR_PBR_Disable_on_hot_P0_WID                  ( 1)
  #define MC0_CH0_CR_SC_PBR_PBR_Disable_on_hot_P0_MSK                  (0x00000008)
  #define MC0_CH0_CR_SC_PBR_PBR_Disable_on_hot_P0_MIN                  (0)
  #define MC0_CH0_CR_SC_PBR_PBR_Disable_on_hot_P0_MAX                  (1) // 0x00000001
  #define MC0_CH0_CR_SC_PBR_PBR_Disable_on_hot_P0_DEF                  (0x00000000)
  #define MC0_CH0_CR_SC_PBR_PBR_Disable_on_hot_P0_HSH                  (0x0106E488)

  #define MC0_CH0_CR_SC_PBR_PBR_Exit_on_Idle_Cnt_P0_OFF                ( 4)
  #define MC0_CH0_CR_SC_PBR_PBR_Exit_on_Idle_Cnt_P0_WID                ( 6)
  #define MC0_CH0_CR_SC_PBR_PBR_Exit_on_Idle_Cnt_P0_MSK                (0x000003F0)
  #define MC0_CH0_CR_SC_PBR_PBR_Exit_on_Idle_Cnt_P0_MIN                (0)
  #define MC0_CH0_CR_SC_PBR_PBR_Exit_on_Idle_Cnt_P0_MAX                (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PBR_PBR_Exit_on_Idle_Cnt_P0_DEF                (0x00000001)
  #define MC0_CH0_CR_SC_PBR_PBR_Exit_on_Idle_Cnt_P0_HSH                (0x0608E488)

  #define MC0_CH0_CR_SC_PBR_tRFCpb_P0_OFF                              (10)
  #define MC0_CH0_CR_SC_PBR_tRFCpb_P0_WID                              (10)
  #define MC0_CH0_CR_SC_PBR_tRFCpb_P0_MSK                              (0x000FFC00)
  #define MC0_CH0_CR_SC_PBR_tRFCpb_P0_MIN                              (0)
  #define MC0_CH0_CR_SC_PBR_tRFCpb_P0_MAX                              (1023) // 0x000003FF
  #define MC0_CH0_CR_SC_PBR_tRFCpb_P0_DEF                              (0x0000003C)
  #define MC0_CH0_CR_SC_PBR_tRFCpb_P0_HSH                              (0x0A14E488)

  #define MC0_CH0_CR_SC_PBR_Refresh_ABR_release_P0_OFF                 (20)
  #define MC0_CH0_CR_SC_PBR_Refresh_ABR_release_P0_WID                 ( 4)
  #define MC0_CH0_CR_SC_PBR_Refresh_ABR_release_P0_MSK                 (0x00F00000)
  #define MC0_CH0_CR_SC_PBR_Refresh_ABR_release_P0_MIN                 (0)
  #define MC0_CH0_CR_SC_PBR_Refresh_ABR_release_P0_MAX                 (15) // 0x0000000F
  #define MC0_CH0_CR_SC_PBR_Refresh_ABR_release_P0_DEF                 (0x00000007)
  #define MC0_CH0_CR_SC_PBR_Refresh_ABR_release_P0_HSH                 (0x0428E488)

  #define MC0_CH0_CR_SC_PBR_PBR_extended_disable_while_DQS_OSC_P0_OFF  (24)
  #define MC0_CH0_CR_SC_PBR_PBR_extended_disable_while_DQS_OSC_P0_WID  ( 1)
  #define MC0_CH0_CR_SC_PBR_PBR_extended_disable_while_DQS_OSC_P0_MSK  (0x01000000)
  #define MC0_CH0_CR_SC_PBR_PBR_extended_disable_while_DQS_OSC_P0_MIN  (0)
  #define MC0_CH0_CR_SC_PBR_PBR_extended_disable_while_DQS_OSC_P0_MAX  (1) // 0x00000001
  #define MC0_CH0_CR_SC_PBR_PBR_extended_disable_while_DQS_OSC_P0_DEF  (0x00000001)
  #define MC0_CH0_CR_SC_PBR_PBR_extended_disable_while_DQS_OSC_P0_HSH  (0x0130E488)

  #define MC0_CH0_CR_SC_PBR_SPARE_P0_OFF                               (25)
  #define MC0_CH0_CR_SC_PBR_SPARE_P0_WID                               ( 7)
  #define MC0_CH0_CR_SC_PBR_SPARE_P0_MSK                               (0xFE000000)
  #define MC0_CH0_CR_SC_PBR_SPARE_P0_MIN                               (0)
  #define MC0_CH0_CR_SC_PBR_SPARE_P0_MAX                               (127) // 0x0000007F
  #define MC0_CH0_CR_SC_PBR_SPARE_P0_DEF                               (0x00000000)
  #define MC0_CH0_CR_SC_PBR_SPARE_P0_HSH                               (0x0732E488)

#define MC0_CH0_CR_TC_LPDDR4_MISC_P0_REG                               (0x0000E494)

  #define MC0_CH0_CR_TC_LPDDR4_MISC_tOSCO_P0_OFF                       ( 0)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tOSCO_P0_WID                       ( 7)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tOSCO_P0_MSK                       (0x0000007F)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tOSCO_P0_MIN                       (0)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tOSCO_P0_MAX                       (127) // 0x0000007F
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tOSCO_P0_DEF                       (0x00000056)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tOSCO_P0_HSH                       (0x0700E494)

  #define MC0_CH0_CR_TC_LPDDR4_MISC_tPREMRR_P0_OFF                     ( 7)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tPREMRR_P0_WID                     ( 7)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tPREMRR_P0_MSK                     (0x00003F80)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tPREMRR_P0_MIN                     (0)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tPREMRR_P0_MAX                     (127) // 0x0000007F
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tPREMRR_P0_DEF                     (0x00000010)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tPREMRR_P0_HSH                     (0x070EE494)

  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRRMRW_P0_OFF                     (14)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRRMRW_P0_WID                     ( 7)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRRMRW_P0_MSK                     (0x001FC000)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRRMRW_P0_MIN                     (0)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRRMRW_P0_MAX                     (127) // 0x0000007F
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRRMRW_P0_DEF                     (0x00000010)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRRMRW_P0_HSH                     (0x071CE494)

  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRR_P0_OFF                        (21)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRR_P0_WID                        ( 7)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRR_P0_MSK                        (0x0FE00000)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRR_P0_MIN                        (0)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRR_P0_MAX                        (127) // 0x0000007F
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRR_P0_DEF                        (0x00000010)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRR_P0_HSH                        (0x072AE494)

  #define MC0_CH0_CR_TC_LPDDR4_MISC_Manual_DQS_MR_READ_P0_OFF          (28)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_Manual_DQS_MR_READ_P0_WID          ( 1)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_Manual_DQS_MR_READ_P0_MSK          (0x10000000)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_Manual_DQS_MR_READ_P0_MIN          (0)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_Manual_DQS_MR_READ_P0_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_TC_LPDDR4_MISC_Manual_DQS_MR_READ_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_Manual_DQS_MR_READ_P0_HSH          (0x0138E494)

#define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_P0_REG                           (0x0000E498)

  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_16_P0_OFF                  ( 0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_16_P0_WID                  ( 3)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_16_P0_MSK                  (0x00000007)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_16_P0_MIN                  (0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_16_P0_MAX                  (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_16_P0_DEF                  (0x00000000)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_16_P0_HSH                  (0x4300E498)

  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_17_P0_OFF                  ( 3)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_17_P0_WID                  ( 3)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_17_P0_MSK                  (0x00000038)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_17_P0_MIN                  (0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_17_P0_MAX                  (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_17_P0_DEF                  (0x00000001)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_17_P0_HSH                  (0x4306E498)

  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_18_P0_OFF                  ( 6)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_18_P0_WID                  ( 3)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_18_P0_MSK                  (0x000001C0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_18_P0_MIN                  (0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_18_P0_MAX                  (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_18_P0_DEF                  (0x00000002)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_18_P0_HSH                  (0x430CE498)

  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_19_P0_OFF                  ( 9)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_19_P0_WID                  ( 3)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_19_P0_MSK                  (0x00000E00)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_19_P0_MIN                  (0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_19_P0_MAX                  (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_19_P0_DEF                  (0x00000003)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_19_P0_HSH                  (0x4312E498)

  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_20_P0_OFF                  (12)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_20_P0_WID                  ( 3)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_20_P0_MSK                  (0x00007000)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_20_P0_MIN                  (0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_20_P0_MAX                  (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_20_P0_DEF                  (0x00000004)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_20_P0_HSH                  (0x4318E498)

  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_24_P0_OFF                  (15)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_24_P0_WID                  ( 3)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_24_P0_MSK                  (0x00038000)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_24_P0_MIN                  (0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_24_P0_MAX                  (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_24_P0_DEF                  (0x00000000)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_24_P0_HSH                  (0x431EE498)

  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_25_P0_OFF                  (18)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_25_P0_WID                  ( 3)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_25_P0_MSK                  (0x001C0000)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_25_P0_MIN                  (0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_25_P0_MAX                  (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_25_P0_DEF                  (0x00000001)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_25_P0_HSH                  (0x4324E498)

  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_26_P0_OFF                  (21)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_26_P0_WID                  ( 3)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_26_P0_MSK                  (0x00E00000)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_26_P0_MIN                  (0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_26_P0_MAX                  (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_26_P0_DEF                  (0x00000002)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_26_P0_HSH                  (0x432AE498)

  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_27_P0_OFF                  (24)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_27_P0_WID                  ( 3)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_27_P0_MSK                  (0x07000000)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_27_P0_MIN                  (0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_27_P0_MAX                  (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_27_P0_DEF                  (0x00000003)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_27_P0_HSH                  (0x4330E498)

  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_28_P0_OFF                  (27)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_28_P0_WID                  ( 3)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_28_P0_MSK                  (0x38000000)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_28_P0_MIN                  (0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_28_P0_MAX                  (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_28_P0_DEF                  (0x00000004)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_28_P0_HSH                  (0x4336E498)

  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_0_P0_OFF                  (32)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_0_P0_WID                  ( 3)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_0_P0_MSK                  (0x0000000700000000ULL)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_0_P0_MIN                  (0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_0_P0_MAX                  (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_0_P0_DEF                  (0x00000000)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_0_P0_HSH                  (0x4340E498)

  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_1_P0_OFF                  (35)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_1_P0_WID                  ( 3)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_1_P0_MSK                  (0x0000003800000000ULL)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_1_P0_MIN                  (0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_1_P0_MAX                  (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_1_P0_DEF                  (0x00000001)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_1_P0_HSH                  (0x4346E498)

#define MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_P0_REG                   (0x0000E4B0)
//Duplicate of MC0_PWM_COUNTERS_DURATION_P0_REG

#define MC0_CH0_CR_DESWIZZLE_HIGH_P0_REG                               (0x0000E4B8)
//Duplicate of MC0_CH0_CR_DESWIZZLE_HIGH_ERM_P0_REG

#define MC0_CH0_CR_TC_SREXITTP_P0_REG                                  (0x0000E4C0)

  #define MC0_CH0_CR_TC_SREXITTP_tXSR_P0_OFF                           ( 0)
  #define MC0_CH0_CR_TC_SREXITTP_tXSR_P0_WID                           (12)
  #define MC0_CH0_CR_TC_SREXITTP_tXSR_P0_MSK                           (0x00000FFF)
  #define MC0_CH0_CR_TC_SREXITTP_tXSR_P0_MIN                           (0)
  #define MC0_CH0_CR_TC_SREXITTP_tXSR_P0_MAX                           (4095) // 0x00000FFF
  #define MC0_CH0_CR_TC_SREXITTP_tXSR_P0_DEF                           (0x00000000)
  #define MC0_CH0_CR_TC_SREXITTP_tXSR_P0_HSH                           (0x4C00E4C0)

  #define MC0_CH0_CR_TC_SREXITTP_tXSR_DS_P0_OFF                        (20)
  #define MC0_CH0_CR_TC_SREXITTP_tXSR_DS_P0_WID                        (14)
  #define MC0_CH0_CR_TC_SREXITTP_tXSR_DS_P0_MSK                        (0x00000003FFF00000ULL)
  #define MC0_CH0_CR_TC_SREXITTP_tXSR_DS_P0_MIN                        (0)
  #define MC0_CH0_CR_TC_SREXITTP_tXSR_DS_P0_MAX                        (16383) // 0x00003FFF
  #define MC0_CH0_CR_TC_SREXITTP_tXSR_DS_P0_DEF                        (0x00000000)
  #define MC0_CH0_CR_TC_SREXITTP_tXSR_DS_P0_HSH                        (0x4E28E4C0)

  #define MC0_CH0_CR_TC_SREXITTP_serial_zq_between_sub_ch_P0_OFF       (34)
  #define MC0_CH0_CR_TC_SREXITTP_serial_zq_between_sub_ch_P0_WID       ( 1)
  #define MC0_CH0_CR_TC_SREXITTP_serial_zq_between_sub_ch_P0_MSK       (0x0000000400000000ULL)
  #define MC0_CH0_CR_TC_SREXITTP_serial_zq_between_sub_ch_P0_MIN       (0)
  #define MC0_CH0_CR_TC_SREXITTP_serial_zq_between_sub_ch_P0_MAX       (1) // 0x00000001
  #define MC0_CH0_CR_TC_SREXITTP_serial_zq_between_sub_ch_P0_DEF       (0x00000000)
  #define MC0_CH0_CR_TC_SREXITTP_serial_zq_between_sub_ch_P0_HSH       (0x4144E4C0)

  #define MC0_CH0_CR_TC_SREXITTP_count_block_wr_on_srx_P0_OFF          (35)
  #define MC0_CH0_CR_TC_SREXITTP_count_block_wr_on_srx_P0_WID          (16)
  #define MC0_CH0_CR_TC_SREXITTP_count_block_wr_on_srx_P0_MSK          (0x0007FFF800000000ULL)
  #define MC0_CH0_CR_TC_SREXITTP_count_block_wr_on_srx_P0_MIN          (0)
  #define MC0_CH0_CR_TC_SREXITTP_count_block_wr_on_srx_P0_MAX          (65535) // 0x0000FFFF
  #define MC0_CH0_CR_TC_SREXITTP_count_block_wr_on_srx_P0_DEF          (0x00000014)
  #define MC0_CH0_CR_TC_SREXITTP_count_block_wr_on_srx_P0_HSH          (0x5046E4C0)

  #define MC0_CH0_CR_TC_SREXITTP_tSR_P0_OFF                            (51)
  #define MC0_CH0_CR_TC_SREXITTP_tSR_P0_WID                            ( 6)
  #define MC0_CH0_CR_TC_SREXITTP_tSR_P0_MSK                            (0x01F8000000000000ULL)
  #define MC0_CH0_CR_TC_SREXITTP_tSR_P0_MIN                            (0)
  #define MC0_CH0_CR_TC_SREXITTP_tSR_P0_MAX                            (63) // 0x0000003F
  #define MC0_CH0_CR_TC_SREXITTP_tSR_P0_DEF                            (0x00000020)
  #define MC0_CH0_CR_TC_SREXITTP_tSR_P0_HSH                            (0x4666E4C0)

#define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_P0_REG                        (0x0000E4C8)

  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_DQSOSCL_PERIOD_P0_OFF       ( 0)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_DQSOSCL_PERIOD_P0_WID       (16)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_DQSOSCL_PERIOD_P0_MSK       (0x0000FFFF)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_DQSOSCL_PERIOD_P0_MIN       (0)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_DQSOSCL_PERIOD_P0_MAX       (65535) // 0x0000FFFF
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_DQSOSCL_PERIOD_P0_DEF       (0x00000100)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_DQSOSCL_PERIOD_P0_HSH       (0x1000E4C8)

  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_MR19toBlockAckPeriod_P0_OFF (16)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_MR19toBlockAckPeriod_P0_WID ( 8)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_MR19toBlockAckPeriod_P0_MSK (0x00FF0000)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_MR19toBlockAckPeriod_P0_MIN (0)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_MR19toBlockAckPeriod_P0_MAX (255) // 0x000000FF
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_MR19toBlockAckPeriod_P0_DEF (0x00000007)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_MR19toBlockAckPeriod_P0_HSH (0x0820E4C8)

  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_DIS_SRX_DQSOSCL_P0_OFF      (24)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_DIS_SRX_DQSOSCL_P0_WID      ( 1)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_DIS_SRX_DQSOSCL_P0_MSK      (0x01000000)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_DIS_SRX_DQSOSCL_P0_MIN      (0)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_DIS_SRX_DQSOSCL_P0_MAX      (1) // 0x00000001
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_DIS_SRX_DQSOSCL_P0_DEF      (0x00000000)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_DIS_SRX_DQSOSCL_P0_HSH      (0x0130E4C8)

  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_disable_wr_on_pkgc_exit_P0_OFF (26)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_disable_wr_on_pkgc_exit_P0_WID ( 1)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_disable_wr_on_pkgc_exit_P0_MSK (0x04000000)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_disable_wr_on_pkgc_exit_P0_MIN (0)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_disable_wr_on_pkgc_exit_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_disable_wr_on_pkgc_exit_P0_DEF (0x00000000)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_disable_wr_on_pkgc_exit_P0_HSH (0x0134E4C8)

  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_disable_wr_on_SR_exit_P0_OFF (27)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_disable_wr_on_SR_exit_P0_WID ( 1)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_disable_wr_on_SR_exit_P0_MSK (0x08000000)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_disable_wr_on_SR_exit_P0_MIN (0)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_disable_wr_on_SR_exit_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_disable_wr_on_SR_exit_P0_DEF (0x00000000)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_disable_wr_on_SR_exit_P0_HSH (0x0136E4C8)

  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_disable_PMreqWaitForMR19_P0_OFF (28)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_disable_PMreqWaitForMR19_P0_WID ( 1)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_disable_PMreqWaitForMR19_P0_MSK (0x10000000)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_disable_PMreqWaitForMR19_P0_MIN (0)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_disable_PMreqWaitForMR19_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_disable_PMreqWaitForMR19_P0_DEF (0x00000000)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_disable_PMreqWaitForMR19_P0_HSH (0x0138E4C8)

  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_dqs_oscillator_resolution_is_64_P0_OFF (29)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_dqs_oscillator_resolution_is_64_P0_WID ( 1)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_dqs_oscillator_resolution_is_64_P0_MSK (0x20000000)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_dqs_oscillator_resolution_is_64_P0_MIN (0)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_dqs_oscillator_resolution_is_64_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_dqs_oscillator_resolution_is_64_P0_DEF (0x00000000)
  #define MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_dqs_oscillator_resolution_is_64_P0_HSH (0x013AE4C8)

#define MC0_CH0_CR_LPDDR_PASR_P0_REG                                   (0x0000E4CC)

  #define MC0_CH0_CR_LPDDR_PASR_row_msb_P0_OFF                         ( 0)
  #define MC0_CH0_CR_LPDDR_PASR_row_msb_P0_WID                         ( 2)
  #define MC0_CH0_CR_LPDDR_PASR_row_msb_P0_MSK                         (0x00000003)
  #define MC0_CH0_CR_LPDDR_PASR_row_msb_P0_MIN                         (0)
  #define MC0_CH0_CR_LPDDR_PASR_row_msb_P0_MAX                         (3) // 0x00000003
  #define MC0_CH0_CR_LPDDR_PASR_row_msb_P0_DEF                         (0x00000000)
  #define MC0_CH0_CR_LPDDR_PASR_row_msb_P0_HSH                         (0x0200E4CC)

  #define MC0_CH0_CR_LPDDR_PASR_disabled_segment_P0_OFF                ( 2)
  #define MC0_CH0_CR_LPDDR_PASR_disabled_segment_P0_WID                ( 8)
  #define MC0_CH0_CR_LPDDR_PASR_disabled_segment_P0_MSK                (0x000003FC)
  #define MC0_CH0_CR_LPDDR_PASR_disabled_segment_P0_MIN                (0)
  #define MC0_CH0_CR_LPDDR_PASR_disabled_segment_P0_MAX                (255) // 0x000000FF
  #define MC0_CH0_CR_LPDDR_PASR_disabled_segment_P0_DEF                (0x00000000)
  #define MC0_CH0_CR_LPDDR_PASR_disabled_segment_P0_HSH                (0x0804E4CC)

  #define MC0_CH0_CR_LPDDR_PASR_new_wr_req_hit_pasr_dis_seg_P0_OFF     (31)
  #define MC0_CH0_CR_LPDDR_PASR_new_wr_req_hit_pasr_dis_seg_P0_WID     ( 1)
  #define MC0_CH0_CR_LPDDR_PASR_new_wr_req_hit_pasr_dis_seg_P0_MSK     (0x80000000)
  #define MC0_CH0_CR_LPDDR_PASR_new_wr_req_hit_pasr_dis_seg_P0_MIN     (0)
  #define MC0_CH0_CR_LPDDR_PASR_new_wr_req_hit_pasr_dis_seg_P0_MAX     (1) // 0x00000001
  #define MC0_CH0_CR_LPDDR_PASR_new_wr_req_hit_pasr_dis_seg_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_LPDDR_PASR_new_wr_req_hit_pasr_dis_seg_P0_HSH     (0x013EE4CC)

#define MC0_CH0_CR_WDB_RD_WR_DFX_DATA_P0_REG                           (0x0000E4D8)

  #define MC0_CH0_CR_WDB_RD_WR_DFX_DATA_DATA_P0_OFF                    ( 0)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_DATA_DATA_P0_WID                    (64)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_DATA_DATA_P0_MSK                    (0xFFFFFFFFFFFFFFFFULL)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_DATA_DATA_P0_MIN                    (0)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_DATA_DATA_P0_MAX                    (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define MC0_CH0_CR_WDB_RD_WR_DFX_DATA_DATA_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_DATA_DATA_P0_HSH                    (0x4000E4D8)

#define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_P0_REG                            (0x0000E4E0)

  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_GO_P0_OFF                       ( 0)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_GO_P0_WID                       ( 1)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_GO_P0_MSK                       (0x00000001)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_GO_P0_MIN                       (0)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_GO_P0_MAX                       (1) // 0x00000001
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_GO_P0_DEF                       (0x00000000)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_GO_P0_HSH                       (0x0100E4E0)

  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Chunk_Sel_P0_OFF                ( 1)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Chunk_Sel_P0_WID                ( 8)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Chunk_Sel_P0_MSK                (0x000001FE)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Chunk_Sel_P0_MIN                (0)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Chunk_Sel_P0_MAX                (255) // 0x000000FF
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Chunk_Sel_P0_DEF                (0x00000000)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Chunk_Sel_P0_HSH                (0x0802E4E0)

  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Op_P0_OFF                       ( 9)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Op_P0_WID                       ( 1)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Op_P0_MSK                       (0x00000200)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Op_P0_MIN                       (0)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Op_P0_MAX                       (1) // 0x00000001
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Op_P0_DEF                       (0x00000000)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Op_P0_HSH                       (0x0112E4E0)

  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_SubCh_P0_OFF                    (10)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_SubCh_P0_WID                    ( 1)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_SubCh_P0_MSK                    (0x00000400)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_SubCh_P0_MIN                    (0)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_SubCh_P0_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_SubCh_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_SubCh_P0_HSH                    (0x0114E4E0)

  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_WID_P0_OFF                      (11)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_WID_P0_WID                      ( 6)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_WID_P0_MSK                      (0x0001F800)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_WID_P0_MIN                      (0)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_WID_P0_MAX                      (63) // 0x0000003F
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_WID_P0_DEF                      (0x00000000)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_WID_P0_HSH                      (0x0616E4E0)

#define MC0_CH0_CR_REF_FSM_STATUS_P0_REG                               (0x0000E4E4)

  #define MC0_CH0_CR_REF_FSM_STATUS_DQS_INTERVAL_FSM_status_P0_OFF     ( 0)
  #define MC0_CH0_CR_REF_FSM_STATUS_DQS_INTERVAL_FSM_status_P0_WID     ( 4)
  #define MC0_CH0_CR_REF_FSM_STATUS_DQS_INTERVAL_FSM_status_P0_MSK     (0x0000000F)
  #define MC0_CH0_CR_REF_FSM_STATUS_DQS_INTERVAL_FSM_status_P0_MIN     (0)
  #define MC0_CH0_CR_REF_FSM_STATUS_DQS_INTERVAL_FSM_status_P0_MAX     (15) // 0x0000000F
  #define MC0_CH0_CR_REF_FSM_STATUS_DQS_INTERVAL_FSM_status_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_REF_FSM_STATUS_DQS_INTERVAL_FSM_status_P0_HSH     (0x0400E4E4)

  #define MC0_CH0_CR_REF_FSM_STATUS_TEMP_RD_FSM_status_P0_OFF          ( 4)
  #define MC0_CH0_CR_REF_FSM_STATUS_TEMP_RD_FSM_status_P0_WID          ( 5)
  #define MC0_CH0_CR_REF_FSM_STATUS_TEMP_RD_FSM_status_P0_MSK          (0x000001F0)
  #define MC0_CH0_CR_REF_FSM_STATUS_TEMP_RD_FSM_status_P0_MIN          (0)
  #define MC0_CH0_CR_REF_FSM_STATUS_TEMP_RD_FSM_status_P0_MAX          (31) // 0x0000001F
  #define MC0_CH0_CR_REF_FSM_STATUS_TEMP_RD_FSM_status_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_REF_FSM_STATUS_TEMP_RD_FSM_status_P0_HSH          (0x0508E4E4)

  #define MC0_CH0_CR_REF_FSM_STATUS_REFRATE_CHNG_FSM_status_P0_OFF     ( 9)
  #define MC0_CH0_CR_REF_FSM_STATUS_REFRATE_CHNG_FSM_status_P0_WID     ( 2)
  #define MC0_CH0_CR_REF_FSM_STATUS_REFRATE_CHNG_FSM_status_P0_MSK     (0x00000600)
  #define MC0_CH0_CR_REF_FSM_STATUS_REFRATE_CHNG_FSM_status_P0_MIN     (0)
  #define MC0_CH0_CR_REF_FSM_STATUS_REFRATE_CHNG_FSM_status_P0_MAX     (3) // 0x00000003
  #define MC0_CH0_CR_REF_FSM_STATUS_REFRATE_CHNG_FSM_status_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_REF_FSM_STATUS_REFRATE_CHNG_FSM_status_P0_HSH     (0x0212E4E4)

  #define MC0_CH0_CR_REF_FSM_STATUS_ZQCS_FSM_status_P0_OFF             (11)
  #define MC0_CH0_CR_REF_FSM_STATUS_ZQCS_FSM_status_P0_WID             ( 3)
  #define MC0_CH0_CR_REF_FSM_STATUS_ZQCS_FSM_status_P0_MSK             (0x00003800)
  #define MC0_CH0_CR_REF_FSM_STATUS_ZQCS_FSM_status_P0_MIN             (0)
  #define MC0_CH0_CR_REF_FSM_STATUS_ZQCS_FSM_status_P0_MAX             (7) // 0x00000007
  #define MC0_CH0_CR_REF_FSM_STATUS_ZQCS_FSM_status_P0_DEF             (0x00000000)
  #define MC0_CH0_CR_REF_FSM_STATUS_ZQCS_FSM_status_P0_HSH             (0x0316E4E4)

  #define MC0_CH0_CR_REF_FSM_STATUS_EXE_REF_FSM_status_P0_OFF          (14)
  #define MC0_CH0_CR_REF_FSM_STATUS_EXE_REF_FSM_status_P0_WID          ( 3)
  #define MC0_CH0_CR_REF_FSM_STATUS_EXE_REF_FSM_status_P0_MSK          (0x0001C000)
  #define MC0_CH0_CR_REF_FSM_STATUS_EXE_REF_FSM_status_P0_MIN          (0)
  #define MC0_CH0_CR_REF_FSM_STATUS_EXE_REF_FSM_status_P0_MAX          (7) // 0x00000007
  #define MC0_CH0_CR_REF_FSM_STATUS_EXE_REF_FSM_status_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_REF_FSM_STATUS_EXE_REF_FSM_status_P0_HSH          (0x031CE4E4)

  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_REF_FSM_status_P0_OFF         (17)
  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_REF_FSM_status_P0_WID         ( 3)
  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_REF_FSM_status_P0_MSK         (0x000E0000)
  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_REF_FSM_status_P0_MIN         (0)
  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_REF_FSM_status_P0_MAX         (7) // 0x00000007
  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_REF_FSM_status_P0_DEF         (0x00000000)
  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_REF_FSM_status_P0_HSH         (0x0322E4E4)

  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_SR_FSM_status_P0_OFF          (20)
  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_SR_FSM_status_P0_WID          ( 4)
  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_SR_FSM_status_P0_MSK          (0x00F00000)
  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_SR_FSM_status_P0_MIN          (0)
  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_SR_FSM_status_P0_MAX          (15) // 0x0000000F
  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_SR_FSM_status_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_SR_FSM_status_P0_HSH          (0x0428E4E4)

  #define MC0_CH0_CR_REF_FSM_STATUS_counter_status_P0_OFF              (24)
  #define MC0_CH0_CR_REF_FSM_STATUS_counter_status_P0_WID              ( 8)
  #define MC0_CH0_CR_REF_FSM_STATUS_counter_status_P0_MSK              (0xFF000000)
  #define MC0_CH0_CR_REF_FSM_STATUS_counter_status_P0_MIN              (0)
  #define MC0_CH0_CR_REF_FSM_STATUS_counter_status_P0_MAX              (255) // 0x000000FF
  #define MC0_CH0_CR_REF_FSM_STATUS_counter_status_P0_DEF              (0x00000000)
  #define MC0_CH0_CR_REF_FSM_STATUS_counter_status_P0_HSH              (0x0830E4E4)

#define MC0_CH0_CR_WDB_MBIST_0_P0_REG                                  (0x0000E4E8)

  #define MC0_CH0_CR_WDB_MBIST_0_PASS_P0_OFF                           ( 0)
  #define MC0_CH0_CR_WDB_MBIST_0_PASS_P0_WID                           ( 1)
  #define MC0_CH0_CR_WDB_MBIST_0_PASS_P0_MSK                           (0x00000001)
  #define MC0_CH0_CR_WDB_MBIST_0_PASS_P0_MIN                           (0)
  #define MC0_CH0_CR_WDB_MBIST_0_PASS_P0_MAX                           (1) // 0x00000001
  #define MC0_CH0_CR_WDB_MBIST_0_PASS_P0_DEF                           (0x00000000)
  #define MC0_CH0_CR_WDB_MBIST_0_PASS_P0_HSH                           (0x0100E4E8)

  #define MC0_CH0_CR_WDB_MBIST_0_Complete_P0_OFF                       ( 1)
  #define MC0_CH0_CR_WDB_MBIST_0_Complete_P0_WID                       ( 1)
  #define MC0_CH0_CR_WDB_MBIST_0_Complete_P0_MSK                       (0x00000002)
  #define MC0_CH0_CR_WDB_MBIST_0_Complete_P0_MIN                       (0)
  #define MC0_CH0_CR_WDB_MBIST_0_Complete_P0_MAX                       (1) // 0x00000001
  #define MC0_CH0_CR_WDB_MBIST_0_Complete_P0_DEF                       (0x00000000)
  #define MC0_CH0_CR_WDB_MBIST_0_Complete_P0_HSH                       (0x0102E4E8)

  #define MC0_CH0_CR_WDB_MBIST_0_Inject_Failure_P0_OFF                 ( 8)
  #define MC0_CH0_CR_WDB_MBIST_0_Inject_Failure_P0_WID                 ( 1)
  #define MC0_CH0_CR_WDB_MBIST_0_Inject_Failure_P0_MSK                 (0x00000100)
  #define MC0_CH0_CR_WDB_MBIST_0_Inject_Failure_P0_MIN                 (0)
  #define MC0_CH0_CR_WDB_MBIST_0_Inject_Failure_P0_MAX                 (1) // 0x00000001
  #define MC0_CH0_CR_WDB_MBIST_0_Inject_Failure_P0_DEF                 (0x00000000)
  #define MC0_CH0_CR_WDB_MBIST_0_Inject_Failure_P0_HSH                 (0x0110E4E8)

  #define MC0_CH0_CR_WDB_MBIST_0_RUN_BUSY_P0_OFF                       (31)
  #define MC0_CH0_CR_WDB_MBIST_0_RUN_BUSY_P0_WID                       ( 1)
  #define MC0_CH0_CR_WDB_MBIST_0_RUN_BUSY_P0_MSK                       (0x80000000)
  #define MC0_CH0_CR_WDB_MBIST_0_RUN_BUSY_P0_MIN                       (0)
  #define MC0_CH0_CR_WDB_MBIST_0_RUN_BUSY_P0_MAX                       (1) // 0x00000001
  #define MC0_CH0_CR_WDB_MBIST_0_RUN_BUSY_P0_DEF                       (0x00000000)
  #define MC0_CH0_CR_WDB_MBIST_0_RUN_BUSY_P0_HSH                       (0x013EE4E8)

#define MC0_CH0_CR_WDB_MBIST_1_P0_REG                                  (0x0000E4EC)
//Duplicate of MC0_CH0_CR_WDB_MBIST_0_P0_REG

#define MC0_CH0_CR_RDB_MBIST_P0_REG                                    (0x0000E4F8)
//Duplicate of MC0_CH0_CR_WDB_MBIST_0_P0_REG

#define MC0_CH0_CR_ECC_INJECT_COUNT_P0_REG                             (0x0000E4FC)

  #define MC0_CH0_CR_ECC_INJECT_COUNT_Count_P0_OFF                     ( 0)
  #define MC0_CH0_CR_ECC_INJECT_COUNT_Count_P0_WID                     (32)
  #define MC0_CH0_CR_ECC_INJECT_COUNT_Count_P0_MSK                     (0xFFFFFFFF)
  #define MC0_CH0_CR_ECC_INJECT_COUNT_Count_P0_MIN                     (0)
  #define MC0_CH0_CR_ECC_INJECT_COUNT_Count_P0_MAX                     (4294967295) // 0xFFFFFFFF
  #define MC0_CH0_CR_ECC_INJECT_COUNT_Count_P0_DEF                     (0xFFFFFFFF)
  #define MC0_CH0_CR_ECC_INJECT_COUNT_Count_P0_HSH                     (0x2000E4FC)

#define MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_P0_REG                (0x0000E500)

  #define MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_RDDATA_COUNTER_P0_OFF ( 0)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_RDDATA_COUNTER_P0_WID (64)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_RDDATA_COUNTER_P0_MSK (0xFFFFFFFFFFFFFFFFULL)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_RDDATA_COUNTER_P0_MIN (0)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_RDDATA_COUNTER_P0_MAX (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_RDDATA_COUNTER_P0_DEF (0x00000000)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_RDDATA_COUNTER_P0_HSH (0x4000E500)

#define MC0_CH0_CR_PWM_DDR_SUBCH1_RDDATA_COUNTER_P0_REG                (0x0000E508)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_P0_REG

#define MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_P0_REG                (0x0000E510)

  #define MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_WRDATA_COUNTER_P0_OFF ( 0)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_WRDATA_COUNTER_P0_WID (64)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_WRDATA_COUNTER_P0_MSK (0xFFFFFFFFFFFFFFFFULL)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_WRDATA_COUNTER_P0_MIN (0)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_WRDATA_COUNTER_P0_MAX (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_WRDATA_COUNTER_P0_DEF (0x00000000)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_WRDATA_COUNTER_P0_HSH (0x4000E510)

#define MC0_CH0_CR_PWM_DDR_SUBCH1_WRDATA_COUNTER_P0_REG                (0x0000E518)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_P0_REG

#define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_P0_REG                (0x0000E520)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte0_P0_OFF  ( 0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte0_P0_WID  ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte0_P0_MSK  (0x00000007)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte0_P0_MIN  (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte0_P0_MAX  (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte0_P0_DEF  (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte0_P0_HSH  (0x4300E520)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte1_P0_OFF  ( 4)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte1_P0_WID  ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte1_P0_MSK  (0x00000070)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte1_P0_MIN  (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte1_P0_MAX  (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte1_P0_DEF  (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte1_P0_HSH  (0x4308E520)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte2_P0_OFF  ( 8)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte2_P0_WID  ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte2_P0_MSK  (0x00000700)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte2_P0_MIN  (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte2_P0_MAX  (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte2_P0_DEF  (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte2_P0_HSH  (0x4310E520)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte3_P0_OFF  (12)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte3_P0_WID  ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte3_P0_MSK  (0x00007000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte3_P0_MIN  (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte3_P0_MAX  (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte3_P0_DEF  (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte3_P0_HSH  (0x4318E520)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte4_P0_OFF  (16)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte4_P0_WID  ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte4_P0_MSK  (0x00070000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte4_P0_MIN  (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte4_P0_MAX  (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte4_P0_DEF  (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte4_P0_HSH  (0x4320E520)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte5_P0_OFF  (20)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte5_P0_WID  ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte5_P0_MSK  (0x00700000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte5_P0_MIN  (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte5_P0_MAX  (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte5_P0_DEF  (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte5_P0_HSH  (0x4328E520)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte6_P0_OFF  (24)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte6_P0_WID  ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte6_P0_MSK  (0x07000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte6_P0_MIN  (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte6_P0_MAX  (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte6_P0_DEF  (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte6_P0_HSH  (0x4330E520)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte7_P0_OFF  (28)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte7_P0_WID  ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte7_P0_MSK  (0x70000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte7_P0_MIN  (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte7_P0_MAX  (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte7_P0_DEF  (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte7_P0_HSH  (0x4338E520)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte0_P0_OFF  (32)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte0_P0_WID  ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte0_P0_MSK  (0x0000000700000000ULL)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte0_P0_MIN  (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte0_P0_MAX  (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte0_P0_DEF  (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte0_P0_HSH  (0x4340E520)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte1_P0_OFF  (36)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte1_P0_WID  ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte1_P0_MSK  (0x0000007000000000ULL)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte1_P0_MIN  (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte1_P0_MAX  (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte1_P0_DEF  (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte1_P0_HSH  (0x4348E520)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte2_P0_OFF  (40)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte2_P0_WID  ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte2_P0_MSK  (0x0000070000000000ULL)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte2_P0_MIN  (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte2_P0_MAX  (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte2_P0_DEF  (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte2_P0_HSH  (0x4350E520)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte3_P0_OFF  (44)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte3_P0_WID  ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte3_P0_MSK  (0x0000700000000000ULL)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte3_P0_MIN  (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte3_P0_MAX  (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte3_P0_DEF  (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte3_P0_HSH  (0x4358E520)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte4_P0_OFF  (48)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte4_P0_WID  ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte4_P0_MSK  (0x0007000000000000ULL)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte4_P0_MIN  (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte4_P0_MAX  (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte4_P0_DEF  (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte4_P0_HSH  (0x4360E520)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte5_P0_OFF  (52)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte5_P0_WID  ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte5_P0_MSK  (0x0070000000000000ULL)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte5_P0_MIN  (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte5_P0_MAX  (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte5_P0_DEF  (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte5_P0_HSH  (0x4368E520)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte6_P0_OFF  (56)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte6_P0_WID  ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte6_P0_MSK  (0x0700000000000000ULL)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte6_P0_MIN  (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte6_P0_MAX  (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte6_P0_DEF  (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte6_P0_HSH  (0x4370E520)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte7_P0_OFF  (60)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte7_P0_WID  ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte7_P0_MSK  (0x7000000000000000ULL)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte7_P0_MIN  (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte7_P0_MAX  (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte7_P0_DEF  (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte7_P0_HSH  (0x4378E520)

#define MC0_CH0_CR_DDR4_MR2_RTT_WR_DIMM1_VALUES_P0_REG                 (0x0000E528)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_P0_REG

#define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_P0_REG                 (0x0000E530)

  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte0_P0_OFF         ( 0)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte0_P0_WID         ( 7)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte0_P0_MSK         (0x0000007F)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte0_P0_MIN         (0)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte0_P0_MAX         (127) // 0x0000007F
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte0_P0_DEF         (0x00000000)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte0_P0_HSH         (0x4700E530)

  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte1_P0_OFF         ( 8)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte1_P0_WID         ( 7)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte1_P0_MSK         (0x00007F00)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte1_P0_MIN         (0)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte1_P0_MAX         (127) // 0x0000007F
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte1_P0_DEF         (0x00000000)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte1_P0_HSH         (0x4710E530)

  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte2_P0_OFF         (16)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte2_P0_WID         ( 7)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte2_P0_MSK         (0x007F0000)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte2_P0_MIN         (0)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte2_P0_MAX         (127) // 0x0000007F
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte2_P0_DEF         (0x00000000)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte2_P0_HSH         (0x4720E530)

  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte3_P0_OFF         (24)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte3_P0_WID         ( 7)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte3_P0_MSK         (0x7F000000)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte3_P0_MIN         (0)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte3_P0_MAX         (127) // 0x0000007F
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte3_P0_DEF         (0x00000000)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte3_P0_HSH         (0x4730E530)

  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte4_P0_OFF         (32)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte4_P0_WID         ( 7)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte4_P0_MSK         (0x0000007F00000000ULL)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte4_P0_MIN         (0)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte4_P0_MAX         (127) // 0x0000007F
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte4_P0_DEF         (0x00000000)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte4_P0_HSH         (0x4740E530)

  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte5_P0_OFF         (40)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte5_P0_WID         ( 7)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte5_P0_MSK         (0x00007F0000000000ULL)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte5_P0_MIN         (0)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte5_P0_MAX         (127) // 0x0000007F
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte5_P0_DEF         (0x00000000)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte5_P0_HSH         (0x4750E530)

  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte6_P0_OFF         (48)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte6_P0_WID         ( 7)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte6_P0_MSK         (0x007F000000000000ULL)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte6_P0_MIN         (0)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte6_P0_MAX         (127) // 0x0000007F
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte6_P0_DEF         (0x00000000)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte6_P0_HSH         (0x4760E530)

  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte7_P0_OFF         (56)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte7_P0_WID         ( 7)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte7_P0_MSK         (0x7F00000000000000ULL)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte7_P0_MIN         (0)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte7_P0_MAX         (127) // 0x0000007F
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte7_P0_DEF         (0x00000000)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte7_P0_HSH         (0x4770E530)

#define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_1_P0_REG                 (0x0000E538)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_P0_REG

#define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_P0_REG                   (0x0000E544)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte0_P0_OFF     ( 0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte0_P0_WID     ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte0_P0_MSK     (0x00000003)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte0_P0_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte0_P0_MAX     (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte0_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte0_P0_HSH     (0x0200E544)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte1_P0_OFF     ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte1_P0_WID     ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte1_P0_MSK     (0x0000000C)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte1_P0_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte1_P0_MAX     (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte1_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte1_P0_HSH     (0x0204E544)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte2_P0_OFF     ( 4)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte2_P0_WID     ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte2_P0_MSK     (0x00000030)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte2_P0_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte2_P0_MAX     (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte2_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte2_P0_HSH     (0x0208E544)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte3_P0_OFF     ( 6)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte3_P0_WID     ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte3_P0_MSK     (0x000000C0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte3_P0_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte3_P0_MAX     (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte3_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte3_P0_HSH     (0x020CE544)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte4_P0_OFF     ( 8)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte4_P0_WID     ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte4_P0_MSK     (0x00000300)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte4_P0_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte4_P0_MAX     (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte4_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte4_P0_HSH     (0x0210E544)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte5_P0_OFF     (10)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte5_P0_WID     ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte5_P0_MSK     (0x00000C00)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte5_P0_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte5_P0_MAX     (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte5_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte5_P0_HSH     (0x0214E544)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte6_P0_OFF     (12)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte6_P0_WID     ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte6_P0_MSK     (0x00003000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte6_P0_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte6_P0_MAX     (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte6_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte6_P0_HSH     (0x0218E544)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte7_P0_OFF     (14)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte7_P0_WID     ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte7_P0_MSK     (0x0000C000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte7_P0_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte7_P0_MAX     (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte7_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte7_P0_HSH     (0x021CE544)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte0_P0_OFF     (16)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte0_P0_WID     ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte0_P0_MSK     (0x00030000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte0_P0_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte0_P0_MAX     (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte0_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte0_P0_HSH     (0x0220E544)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte1_P0_OFF     (18)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte1_P0_WID     ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte1_P0_MSK     (0x000C0000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte1_P0_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte1_P0_MAX     (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte1_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte1_P0_HSH     (0x0224E544)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte2_P0_OFF     (20)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte2_P0_WID     ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte2_P0_MSK     (0x00300000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte2_P0_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte2_P0_MAX     (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte2_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte2_P0_HSH     (0x0228E544)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte3_P0_OFF     (22)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte3_P0_WID     ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte3_P0_MSK     (0x00C00000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte3_P0_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte3_P0_MAX     (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte3_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte3_P0_HSH     (0x022CE544)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte4_P0_OFF     (24)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte4_P0_WID     ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte4_P0_MSK     (0x03000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte4_P0_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte4_P0_MAX     (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte4_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte4_P0_HSH     (0x0230E544)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte5_P0_OFF     (26)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte5_P0_WID     ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte5_P0_MSK     (0x0C000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte5_P0_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte5_P0_MAX     (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte5_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte5_P0_HSH     (0x0234E544)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte6_P0_OFF     (28)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte6_P0_WID     ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte6_P0_MSK     (0x30000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte6_P0_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte6_P0_MAX     (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte6_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte6_P0_HSH     (0x0238E544)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte7_P0_OFF     (30)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte7_P0_WID     ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte7_P0_MSK     (0xC0000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte7_P0_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte7_P0_MAX     (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte7_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte7_P0_HSH     (0x023CE544)

#define MC0_CH0_CR_DDR4_MR5_RTT_PARK_VALUES_P0_REG                     (0x0000E548)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_P0_REG

#define MC0_CH0_CR_DDR4_MR5_RTT_PARK_DIMM1_VALUES_P0_REG               (0x0000E550)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_P0_REG

#define MC0_CH0_CR_DDR4_MR1_RTT_NOM_VALUES_P0_REG                      (0x0000E558)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_P0_REG

#define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_P0_REG                  (0x0000E560)

  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_PDDS_P0_OFF           ( 0)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_PDDS_P0_WID           ( 3)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_PDDS_P0_MSK           (0x00000007)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_PDDS_P0_MIN           (0)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_PDDS_P0_MAX           (7) // 0x00000007
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_PDDS_P0_DEF           (0x00000000)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_PDDS_P0_HSH           (0x4300E560)

  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_ODT_P0_OFF         ( 3)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_ODT_P0_WID         ( 3)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_ODT_P0_MSK         (0x00000038)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_ODT_P0_MIN         (0)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_ODT_P0_MAX         (7) // 0x00000007
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_ODT_P0_DEF         (0x00000000)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_ODT_P0_HSH         (0x4306E560)

  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_ODT_P0_OFF         ( 6)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_ODT_P0_WID         ( 3)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_ODT_P0_MSK         (0x000001C0)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_ODT_P0_MIN         (0)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_ODT_P0_MAX         (7) // 0x00000007
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_ODT_P0_DEF         (0x00000000)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_ODT_P0_HSH         (0x430CE560)

  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_P0_OFF        ( 9)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_P0_WID        ( 7)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_P0_MSK        (0x0000FE00)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_P0_MIN        (0)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_P0_MAX        (127) // 0x0000007F
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_P0_DEF        (0x00000000)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_P0_HSH        (0x4712E560)

  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_P0_OFF        (16)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_P0_WID        ( 7)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_P0_MSK        (0x007F0000)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_P0_MIN        (0)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_P0_MAX        (127) // 0x0000007F
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_P0_DEF        (0x00000000)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_P0_HSH        (0x4720E560)

  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CODT_P0_OFF           (23)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CODT_P0_WID           ( 6)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CODT_P0_MSK           (0x1F800000)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CODT_P0_MIN           (0)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CODT_P0_MAX           (63) // 0x0000003F
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CODT_P0_DEF           (0x00000000)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CODT_P0_HSH           (0x462EE560)

  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_High_P0_OFF   (29)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_High_P0_WID   ( 7)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_High_P0_MSK   (0x0000000FE0000000ULL)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_High_P0_MIN   (0)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_High_P0_MAX   (127) // 0x0000007F
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_High_P0_DEF   (0x00000000)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_High_P0_HSH   (0x473AE560)

  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_High_P0_OFF   (36)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_High_P0_WID   ( 7)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_High_P0_MSK   (0x000007F000000000ULL)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_High_P0_MIN   (0)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_High_P0_MAX   (127) // 0x0000007F
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_High_P0_DEF   (0x00000000)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_High_P0_HSH   (0x4748E560)

#define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_1_P0_REG                  (0x0000E568)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_P0_REG

#define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_2_P0_REG                  (0x0000E570)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_P0_REG

#define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_3_P0_REG                  (0x0000E578)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_P0_REG

#define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_4_P0_REG                  (0x0000E580)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_P0_REG

#define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_5_P0_REG                  (0x0000E588)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_P0_REG

#define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_6_P0_REG                  (0x0000E590)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_P0_REG

#define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_7_P0_REG                  (0x0000E598)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_P0_REG

#define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_P0_REG                         (0x0000E5A0)

  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR0_P0_OFF                   ( 0)
  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR0_P0_WID                   (14)
  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR0_P0_MSK                   (0x00003FFF)
  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR0_P0_MIN                   (0)
  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR0_P0_MAX                   (16383) // 0x00003FFF
  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR0_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR0_P0_HSH                   (0x0E00E5A0)

  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR1_P0_OFF                   (16)
  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR1_P0_WID                   (14)
  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR1_P0_MSK                   (0x3FFF0000)
  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR1_P0_MIN                   (0)
  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR1_P0_MAX                   (16383) // 0x00003FFF
  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR1_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR1_P0_HSH                   (0x0E20E5A0)

#define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_P0_REG                         (0x0000E5A4)

  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR2_P0_OFF                   ( 0)
  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR2_P0_WID                   (14)
  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR2_P0_MSK                   (0x00003FFF)
  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR2_P0_MIN                   (0)
  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR2_P0_MAX                   (16383) // 0x00003FFF
  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR2_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR2_P0_HSH                   (0x0E00E5A4)

  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR3_P0_OFF                   (16)
  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR3_P0_WID                   (14)
  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR3_P0_MSK                   (0x3FFF0000)
  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR3_P0_MIN                   (0)
  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR3_P0_MAX                   (16383) // 0x00003FFF
  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR3_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR3_P0_HSH                   (0x0E20E5A4)

#define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_P0_REG                         (0x0000E5A8)

  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR4_P0_OFF                   ( 0)
  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR4_P0_WID                   (14)
  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR4_P0_MSK                   (0x00003FFF)
  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR4_P0_MIN                   (0)
  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR4_P0_MAX                   (16383) // 0x00003FFF
  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR4_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR4_P0_HSH                   (0x0E00E5A8)

  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR5_P0_OFF                   (16)
  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR5_P0_WID                   (14)
  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR5_P0_MSK                   (0x3FFF0000)
  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR5_P0_MIN                   (0)
  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR5_P0_MAX                   (16383) // 0x00003FFF
  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR5_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR5_P0_HSH                   (0x0E20E5A8)

#define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_P0_REG                         (0x0000E5AC)

  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR6_P0_OFF                   ( 0)
  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR6_P0_WID                   (14)
  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR6_P0_MSK                   (0x00003FFF)
  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR6_P0_MIN                   (0)
  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR6_P0_MAX                   (16383) // 0x00003FFF
  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR6_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR6_P0_HSH                   (0x0E00E5AC)

  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR7_P0_OFF                   (16)
  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR7_P0_WID                   (14)
  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR7_P0_MSK                   (0x3FFF0000)
  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR7_P0_MIN                   (0)
  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR7_P0_MAX                   (16383) // 0x00003FFF
  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR7_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR7_P0_HSH                   (0x0E20E5AC)

#define MC0_CH0_CR_DDR4_MR2_RTT_WR_VALUES_P0_REG                       (0x0000E5B0)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_P0_REG

#define MC0_CH0_CR_DDR4_MR6_VREF_VALUES_0_P0_REG                       (0x0000E5B8)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_P0_REG

#define MC0_CH0_CR_DDR4_MR6_VREF_VALUES_1_P0_REG                       (0x0000E5C0)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_P0_REG

#define MC0_CH0_CR_LPDDR_MR_CONTENT_P0_REG                             (0x0000E5C8)

  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR1_P0_OFF                       ( 0)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR1_P0_WID                       ( 8)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR1_P0_MSK                       (0x000000FF)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR1_P0_MIN                       (0)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR1_P0_MAX                       (255) // 0x000000FF
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR1_P0_DEF                       (0x00000000)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR1_P0_HSH                       (0x4800E5C8)

  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR2_P0_OFF                       ( 8)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR2_P0_WID                       ( 8)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR2_P0_MSK                       (0x0000FF00)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR2_P0_MIN                       (0)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR2_P0_MAX                       (255) // 0x000000FF
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR2_P0_DEF                       (0x00000000)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR2_P0_HSH                       (0x4810E5C8)

  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR3_P0_OFF                       (16)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR3_P0_WID                       ( 8)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR3_P0_MSK                       (0x00FF0000)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR3_P0_MIN                       (0)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR3_P0_MAX                       (255) // 0x000000FF
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR3_P0_DEF                       (0x00000000)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR3_P0_HSH                       (0x4820E5C8)

  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR11_P0_OFF                      (24)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR11_P0_WID                      ( 8)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR11_P0_MSK                      (0xFF000000)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR11_P0_MIN                      (0)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR11_P0_MAX                      (255) // 0x000000FF
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR11_P0_DEF                      (0x00000000)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR11_P0_HSH                      (0x4830E5C8)

  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR12_P0_OFF                      (32)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR12_P0_WID                      ( 8)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR12_P0_MSK                      (0x000000FF00000000ULL)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR12_P0_MIN                      (0)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR12_P0_MAX                      (255) // 0x000000FF
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR12_P0_DEF                      (0x00000000)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR12_P0_HSH                      (0x4840E5C8)

  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR13_P0_OFF                      (40)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR13_P0_WID                      ( 8)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR13_P0_MSK                      (0x0000FF0000000000ULL)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR13_P0_MIN                      (0)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR13_P0_MAX                      (255) // 0x000000FF
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR13_P0_DEF                      (0x00000000)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR13_P0_HSH                      (0x4850E5C8)

  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR22_P0_OFF                      (48)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR22_P0_WID                      ( 8)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR22_P0_MSK                      (0x00FF000000000000ULL)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR22_P0_MIN                      (0)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR22_P0_MAX                      (255) // 0x000000FF
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR22_P0_DEF                      (0x00000000)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR22_P0_HSH                      (0x4860E5C8)

  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR23_P0_OFF                      (56)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR23_P0_WID                      ( 8)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR23_P0_MSK                      (0xFF00000000000000ULL)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR23_P0_MIN                      (0)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR23_P0_MAX                      (255) // 0x000000FF
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR23_P0_DEF                      (0x0000003F)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR23_P0_HSH                      (0x4870E5C8)

#define MC0_CH0_CR_MRS_FSM_CONTROL_P0_REG                              (0x0000E5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR_P0_OFF            ( 0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR_P0_WID            ( 8)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR_P0_MSK            (0x000000FF)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR_P0_MIN            (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR_P0_MAX            (255) // 0x000000FF
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR_P0_DEF            (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR_P0_HSH            (0x4800E5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_ODIC_Per_Device_P0_OFF ( 8)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_ODIC_Per_Device_P0_WID ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_ODIC_Per_Device_P0_MSK (0x00000100)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_ODIC_Per_Device_P0_MIN (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_ODIC_Per_Device_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_ODIC_Per_Device_P0_DEF (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_ODIC_Per_Device_P0_HSH (0x4110E5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR2_Per_Device_P0_OFF ( 9)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR2_Per_Device_P0_WID ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR2_Per_Device_P0_MSK (0x00000200)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR2_Per_Device_P0_MIN (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR2_Per_Device_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR2_Per_Device_P0_DEF (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR2_Per_Device_P0_HSH (0x4112E5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR6_Per_Device_P0_OFF (10)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR6_Per_Device_P0_WID ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR6_Per_Device_P0_MSK (0x00000400)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR6_Per_Device_P0_MIN (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR6_Per_Device_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR6_Per_Device_P0_DEF (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR6_Per_Device_P0_HSH (0x4114E5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_PDA_VREF_Initial_P0_OFF      (11)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_PDA_VREF_Initial_P0_WID      ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_PDA_VREF_Initial_P0_MSK      (0x00000800)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_PDA_VREF_Initial_P0_MIN      (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_PDA_VREF_Initial_P0_MAX      (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_PDA_VREF_Initial_P0_DEF      (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_PDA_VREF_Initial_P0_HSH      (0x4116E5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Short_VREF_Exit_P0_OFF       (12)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Short_VREF_Exit_P0_WID       ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Short_VREF_Exit_P0_MSK       (0x00001000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Short_VREF_Exit_P0_MIN       (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Short_VREF_Exit_P0_MAX       (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Short_VREF_Exit_P0_DEF       (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Short_VREF_Exit_P0_HSH       (0x4118E5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR_Restore_MR_P0_OFF           (13)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR_Restore_MR_P0_WID           ( 9)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR_Restore_MR_P0_MSK           (0x003FE000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR_Restore_MR_P0_MIN           (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR_Restore_MR_P0_MAX           (511) // 0x000001FF
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR_Restore_MR_P0_DEF           (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR_Restore_MR_P0_HSH           (0x491AE5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_ZQCL_P0_OFF                    (22)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_ZQCL_P0_WID                    ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_ZQCL_P0_MSK                    (0x00400000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_ZQCL_P0_MIN                    (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_ZQCL_P0_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_ZQCL_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_ZQCL_P0_HSH                    (0x412CE5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_zero_rank1_MR11_P0_OFF            (23)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_zero_rank1_MR11_P0_WID            ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_zero_rank1_MR11_P0_MSK            (0x00800000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_zero_rank1_MR11_P0_MIN            (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_zero_rank1_MR11_P0_MAX            (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_zero_rank1_MR11_P0_DEF            (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_zero_rank1_MR11_P0_HSH            (0x412EE5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_reset_flow_P0_OFF                 (24)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_reset_flow_P0_WID                 ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_reset_flow_P0_MSK                 (0x01000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_reset_flow_P0_MIN                 (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_reset_flow_P0_MAX                 (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_reset_flow_P0_DEF                 (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_reset_flow_P0_HSH                 (0x4130E5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_vref_time_per_byte_P0_OFF         (25)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_vref_time_per_byte_P0_WID         ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_vref_time_per_byte_P0_MSK         (0x02000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_vref_time_per_byte_P0_MIN         (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_vref_time_per_byte_P0_MAX         (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_vref_time_per_byte_P0_DEF         (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_vref_time_per_byte_P0_HSH         (0x4132E5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_pda_for_1R1R_P0_OFF            (26)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_pda_for_1R1R_P0_WID            ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_pda_for_1R1R_P0_MSK            (0x04000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_pda_for_1R1R_P0_MIN            (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_pda_for_1R1R_P0_MAX            (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_pda_for_1R1R_P0_DEF            (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_pda_for_1R1R_P0_HSH            (0x4134E5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_add_initial_vref_P0_OFF           (27)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_add_initial_vref_P0_WID           ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_add_initial_vref_P0_MSK           (0x08000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_add_initial_vref_P0_MIN           (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_add_initial_vref_P0_MAX           (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_add_initial_vref_P0_DEF           (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_add_initial_vref_P0_HSH           (0x4136E5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_switch_FSP_P0_OFF          (28)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_switch_FSP_P0_WID          ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_switch_FSP_P0_MSK          (0x10000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_switch_FSP_P0_MIN          (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_switch_FSP_P0_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_switch_FSP_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_switch_FSP_P0_HSH          (0x4138E5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_dq_osc_start_P0_OFF            (29)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_dq_osc_start_P0_WID            ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_dq_osc_start_P0_MSK            (0x20000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_dq_osc_start_P0_MIN            (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_dq_osc_start_P0_MAX            (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_dq_osc_start_P0_DEF            (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_dq_osc_start_P0_HSH            (0x413AE5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_GV_auto_enable_P0_OFF             (30)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GV_auto_enable_P0_WID             ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GV_auto_enable_P0_MSK             (0x40000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GV_auto_enable_P0_MIN             (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GV_auto_enable_P0_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GV_auto_enable_P0_DEF             (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GV_auto_enable_P0_HSH             (0x413CE5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_split_transition_P0_OFF    (31)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_split_transition_P0_WID    ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_split_transition_P0_MSK    (0x80000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_split_transition_P0_MIN    (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_split_transition_P0_MAX    (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_split_transition_P0_DEF    (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_split_transition_P0_HSH    (0x413EE5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_tVREFDQ_P0_OFF                    (32)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_tVREFDQ_P0_WID                    (10)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_tVREFDQ_P0_MSK                    (0x000003FF00000000ULL)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_tVREFDQ_P0_MIN                    (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_tVREFDQ_P0_MAX                    (1023) // 0x000003FF
  #define MC0_CH0_CR_MRS_FSM_CONTROL_tVREFDQ_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_tVREFDQ_P0_HSH                    (0x4A40E5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_cbit_count_each_rank_P0_OFF       (42)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_cbit_count_each_rank_P0_WID       ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_cbit_count_each_rank_P0_MSK       (0x0000040000000000ULL)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_cbit_count_each_rank_P0_MIN       (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_cbit_count_each_rank_P0_MAX       (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_cbit_count_each_rank_P0_DEF       (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_cbit_count_each_rank_P0_HSH       (0x4154E5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_PDA_for_ECC_P0_OFF             (43)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_PDA_for_ECC_P0_WID             ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_PDA_for_ECC_P0_MSK             (0x0000080000000000ULL)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_PDA_for_ECC_P0_MIN             (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_PDA_for_ECC_P0_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_PDA_for_ECC_P0_DEF             (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_PDA_for_ECC_P0_HSH             (0x4156E5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR5_Per_Device_P0_OFF (44)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR5_Per_Device_P0_WID ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR5_Per_Device_P0_MSK (0x0000100000000000ULL)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR5_Per_Device_P0_MIN (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR5_Per_Device_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR5_Per_Device_P0_DEF (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR5_Per_Device_P0_HSH (0x4158E5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_TwoDPC_support_P0_OFF             (45)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_TwoDPC_support_P0_WID             ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_TwoDPC_support_P0_MSK             (0x0000200000000000ULL)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_TwoDPC_support_P0_MIN             (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_TwoDPC_support_P0_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_TwoDPC_support_P0_DEF             (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_TwoDPC_support_P0_HSH             (0x415AE5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_RTTNOM_Per_Device_P0_OFF (46)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_RTTNOM_Per_Device_P0_WID ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_RTTNOM_Per_Device_P0_MSK (0x0000400000000000ULL)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_RTTNOM_Per_Device_P0_MIN (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_RTTNOM_Per_Device_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_RTTNOM_Per_Device_P0_DEF (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_RTTNOM_Per_Device_P0_HSH (0x415CE5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_Fast_PDA_P0_OFF                   (47)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_Fast_PDA_P0_WID                   ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_Fast_PDA_P0_MSK                   (0x0000800000000000ULL)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_Fast_PDA_P0_MIN                   (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_Fast_PDA_P0_MAX                   (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_Fast_PDA_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_Fast_PDA_P0_HSH                   (0x415EE5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_always_count_tFC_P0_OFF           (48)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_always_count_tFC_P0_WID           ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_always_count_tFC_P0_MSK           (0x0001000000000000ULL)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_always_count_tFC_P0_MIN           (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_always_count_tFC_P0_MAX           (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_always_count_tFC_P0_DEF           (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_always_count_tFC_P0_HSH           (0x4160E5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_PDA_wr_delay_P0_OFF               (49)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_PDA_wr_delay_P0_WID               ( 6)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_PDA_wr_delay_P0_MSK               (0x007E000000000000ULL)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_PDA_wr_delay_P0_MIN               (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_PDA_wr_delay_P0_MAX               (63) // 0x0000003F
  #define MC0_CH0_CR_MRS_FSM_CONTROL_PDA_wr_delay_P0_DEF               (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_PDA_wr_delay_P0_HSH               (0x4662E5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_per_byte_vref_P0_OFF       (55)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_per_byte_vref_P0_WID       ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_per_byte_vref_P0_MSK       (0x0080000000000000ULL)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_per_byte_vref_P0_MIN       (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_per_byte_vref_P0_MAX       (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_per_byte_vref_P0_DEF       (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_per_byte_vref_P0_HSH       (0x416EE5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_Clear_VRCG_P0_OFF                 (56)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_Clear_VRCG_P0_WID                 ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_Clear_VRCG_P0_MSK                 (0x0100000000000000ULL)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_Clear_VRCG_P0_MIN                 (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_Clear_VRCG_P0_MAX                 (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_Clear_VRCG_P0_DEF                 (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_Clear_VRCG_P0_HSH                 (0x4170E5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Enable_P0_OFF     (57)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Enable_P0_WID     ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Enable_P0_MSK     (0x0200000000000000ULL)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Enable_P0_MIN     (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Enable_P0_MAX     (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Enable_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Enable_P0_HSH     (0x4172E5D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Breakpoint_Address_P0_OFF (58)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Breakpoint_Address_P0_WID ( 6)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Breakpoint_Address_P0_MSK (0xFC00000000000000ULL)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Breakpoint_Address_P0_MIN (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Breakpoint_Address_P0_MAX (63) // 0x0000003F
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Breakpoint_Address_P0_DEF (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Breakpoint_Address_P0_HSH (0x4674E5D0)

#define MC0_CH0_CR_MRS_FSM_RUN_P0_REG                                  (0x0000E5D8)

  #define MC0_CH0_CR_MRS_FSM_RUN_Run_P0_OFF                            ( 0)
  #define MC0_CH0_CR_MRS_FSM_RUN_Run_P0_WID                            ( 1)
  #define MC0_CH0_CR_MRS_FSM_RUN_Run_P0_MSK                            (0x00000001)
  #define MC0_CH0_CR_MRS_FSM_RUN_Run_P0_MIN                            (0)
  #define MC0_CH0_CR_MRS_FSM_RUN_Run_P0_MAX                            (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_RUN_Run_P0_DEF                            (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_RUN_Run_P0_HSH                            (0x0100E5D8)

#define MC0_CH0_CR_DDR4_MR1_ODIC_VALUES_P0_REG                         (0x0000E5DC)
//Duplicate of MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_P0_REG

#define MC0_CH0_CR_PL_AGENT_CFG_DTF_P0_REG                             (0x0000E5E0)

  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_data_trace_mode_P0_OFF           ( 0)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_data_trace_mode_P0_WID           ( 2)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_data_trace_mode_P0_MSK           (0x00000003)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_data_trace_mode_P0_MIN           (0)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_data_trace_mode_P0_MAX           (3) // 0x00000003
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_data_trace_mode_P0_DEF           (0x00000000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_data_trace_mode_P0_HSH           (0x0200E5E0)

  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_UI_to_trace_P0_OFF               ( 2)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_UI_to_trace_P0_WID               ( 3)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_UI_to_trace_P0_MSK               (0x0000001C)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_UI_to_trace_P0_MIN               (0)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_UI_to_trace_P0_MAX               (7) // 0x00000007
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_UI_to_trace_P0_DEF               (0x00000000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_UI_to_trace_P0_HSH               (0x0304E5E0)

  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_byte_to_trace_P0_OFF             ( 5)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_byte_to_trace_P0_WID             ( 3)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_byte_to_trace_P0_MSK             (0x000000E0)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_byte_to_trace_P0_MIN             (0)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_byte_to_trace_P0_MAX             (7) // 0x00000007
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_byte_to_trace_P0_DEF             (0x00000000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_byte_to_trace_P0_HSH             (0x030AE5E0)

  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_EN_P0_OFF                    ( 8)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_EN_P0_WID                    ( 1)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_EN_P0_MSK                    (0x00000100)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_EN_P0_MIN                    (0)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_EN_P0_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_EN_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_EN_P0_HSH                    (0x0110E5E0)

  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_BYTE_replace_P0_OFF          ( 9)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_BYTE_replace_P0_WID          ( 3)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_BYTE_replace_P0_MSK          (0x00000E00)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_BYTE_replace_P0_MIN          (0)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_BYTE_replace_P0_MAX          (7) // 0x00000007
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_BYTE_replace_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_BYTE_replace_P0_HSH          (0x0312E5E0)

  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_read_data_P0_OFF           (12)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_read_data_P0_WID           ( 1)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_read_data_P0_MSK           (0x00001000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_read_data_P0_MIN           (0)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_read_data_P0_MAX           (1) // 0x00000001
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_read_data_P0_DEF           (0x00000000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_read_data_P0_HSH           (0x0118E5E0)

  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_write_data_P0_OFF          (13)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_write_data_P0_WID          ( 1)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_write_data_P0_MSK          (0x00002000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_write_data_P0_MIN          (0)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_write_data_P0_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_write_data_P0_DEF          (0x00000001)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_write_data_P0_HSH          (0x011AE5E0)

  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_DDRPL_Activate_P0_OFF            (14)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_DDRPL_Activate_P0_WID            ( 1)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_DDRPL_Activate_P0_MSK            (0x00004000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_DDRPL_Activate_P0_MIN            (0)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_DDRPL_Activate_P0_MAX            (1) // 0x00000001
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_DDRPL_Activate_P0_DEF            (0x00000000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_DDRPL_Activate_P0_HSH            (0x011CE5E0)

  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_SCHTrace_P0_OFF                  (15)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_SCHTrace_P0_WID                  ( 1)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_SCHTrace_P0_MSK                  (0x00008000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_SCHTrace_P0_MIN                  (0)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_SCHTrace_P0_MAX                  (1) // 0x00000001
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_SCHTrace_P0_DEF                  (0x00000000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_SCHTrace_P0_HSH                  (0x011EE5E0)

  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_dis_early_ind_override_P0_OFF    (16)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_dis_early_ind_override_P0_WID    ( 1)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_dis_early_ind_override_P0_MSK    (0x00010000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_dis_early_ind_override_P0_MIN    (0)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_dis_early_ind_override_P0_MAX    (1) // 0x00000001
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_dis_early_ind_override_P0_DEF    (0x00000000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_dis_early_ind_override_P0_HSH    (0x0120E5E0)

#define MC0_CH0_CR_MCMNTS_GLOBAL_DRIVER_GATE_CFG_P0_REG                (0x0000E5E4)
//Duplicate of MC0_MCMAINS_GLOBAL_DRIVER_GATE_CFG_P0_REG

#define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_P0_REG                       (0x0000E5E8)

  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank0_P0_OFF          ( 0)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank0_P0_WID          ( 2)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank0_P0_MSK          (0x00000003)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank0_P0_MIN          (0)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank0_P0_MAX          (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank0_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank0_P0_HSH          (0x4200E5E8)

  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank1_P0_OFF          ( 2)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank1_P0_WID          ( 2)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank1_P0_MSK          (0x0000000C)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank1_P0_MIN          (0)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank1_P0_MAX          (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank1_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank1_P0_HSH          (0x4204E5E8)

  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank0_P0_OFF        ( 4)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank0_P0_WID        ( 3)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank0_P0_MSK        (0x00000070)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank0_P0_MIN        (0)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank0_P0_MAX        (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank0_P0_DEF        (0x00000000)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank0_P0_HSH        (0x4308E5E8)

  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank1_P0_OFF        ( 7)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank1_P0_WID        ( 3)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank1_P0_MSK        (0x00000380)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank1_P0_MIN        (0)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank1_P0_MAX        (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank1_P0_DEF        (0x00000000)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank1_P0_HSH        (0x430EE5E8)

  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank0_P0_OFF          (10)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank0_P0_WID          ( 7)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank0_P0_MSK          (0x0001FC00)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank0_P0_MIN          (0)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank0_P0_MAX          (127) // 0x0000007F
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank0_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank0_P0_HSH          (0x4714E5E8)

  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank1_P0_OFF          (17)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank1_P0_WID          ( 7)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank1_P0_MSK          (0x00FE0000)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank1_P0_MIN          (0)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank1_P0_MAX          (127) // 0x0000007F
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank1_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank1_P0_HSH          (0x4722E5E8)

  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank0_P0_OFF       (24)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank0_P0_WID       ( 3)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank0_P0_MSK       (0x07000000)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank0_P0_MIN       (0)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank0_P0_MAX       (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank0_P0_DEF       (0x00000000)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank0_P0_HSH       (0x4330E5E8)

  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank1_P0_OFF       (27)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank1_P0_WID       ( 3)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank1_P0_MSK       (0x38000000)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank1_P0_MIN       (0)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank1_P0_MAX       (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank1_P0_DEF       (0x00000000)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank1_P0_HSH       (0x4336E5E8)

  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank0_P0_OFF      (32)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank0_P0_WID      ( 3)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank0_P0_MSK      (0x0000000700000000ULL)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank0_P0_MIN      (0)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank0_P0_MAX      (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank0_P0_DEF      (0x00000000)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank0_P0_HSH      (0x4340E5E8)

  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank1_P0_OFF      (35)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank1_P0_WID      ( 3)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank1_P0_MSK      (0x0000003800000000ULL)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank1_P0_MIN      (0)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank1_P0_MAX      (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank1_P0_DEF      (0x00000000)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank1_P0_HSH      (0x4346E5E8)

#define MC0_CH0_CR_DDR4_ECC_DEVICE_DIMM1_VALUES_P0_REG                 (0x0000E5F0)
//Duplicate of MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_P0_REG

#define MC0_CH0_CR_MCMNTS_SPARE2_P0_REG                                (0x0000E5F8)

  #define MC0_CH0_CR_MCMNTS_SPARE2_Spare_RW_P0_OFF                     ( 0)
  #define MC0_CH0_CR_MCMNTS_SPARE2_Spare_RW_P0_WID                     (16)
  #define MC0_CH0_CR_MCMNTS_SPARE2_Spare_RW_P0_MSK                     (0x0000FFFF)
  #define MC0_CH0_CR_MCMNTS_SPARE2_Spare_RW_P0_MIN                     (0)
  #define MC0_CH0_CR_MCMNTS_SPARE2_Spare_RW_P0_MAX                     (65535) // 0x0000FFFF
  #define MC0_CH0_CR_MCMNTS_SPARE2_Spare_RW_P0_DEF                     (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE2_Spare_RW_P0_HSH                     (0x1000E5F8)

  #define MC0_CH0_CR_MCMNTS_SPARE2_Spare_RW_V_P0_OFF                   (16)
  #define MC0_CH0_CR_MCMNTS_SPARE2_Spare_RW_V_P0_WID                   (16)
  #define MC0_CH0_CR_MCMNTS_SPARE2_Spare_RW_V_P0_MSK                   (0xFFFF0000)
  #define MC0_CH0_CR_MCMNTS_SPARE2_Spare_RW_V_P0_MIN                   (0)
  #define MC0_CH0_CR_MCMNTS_SPARE2_Spare_RW_V_P0_MAX                   (65535) // 0x0000FFFF
  #define MC0_CH0_CR_MCMNTS_SPARE2_Spare_RW_V_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE2_Spare_RW_V_P0_HSH                   (0x1020E5F8)

#define MC0_CH0_CR_MCMNTS_SPARE_P0_REG                                 (0x0000E5FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_P0_OFF                      ( 0)
  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_P0_WID                      ( 8)
  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_P0_MSK                      (0x000000FF)
  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_P0_MIN                      (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_P0_MAX                      (255) // 0x000000FF
  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_P0_DEF                      (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_P0_HSH                      (0x0800E5FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX2Ref_P0_OFF                    ( 8)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX2Ref_P0_WID                    ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX2Ref_P0_MSK                    (0x00000100)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX2Ref_P0_MIN                    (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX2Ref_P0_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX2Ref_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX2Ref_P0_HSH                    (0x0110E5FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX4Ref_P0_OFF                    ( 9)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX4Ref_P0_WID                    ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX4Ref_P0_MSK                    (0x00000200)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX4Ref_P0_MIN                    (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX4Ref_P0_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX4Ref_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX4Ref_P0_HSH                    (0x0112E5FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_DisLowRefRate_P0_OFF                 (10)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisLowRefRate_P0_WID                 ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisLowRefRate_P0_MSK                 (0x00000400)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisLowRefRate_P0_MIN                 (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisLowRefRate_P0_MAX                 (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_DisLowRefRate_P0_DEF                 (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisLowRefRate_P0_HSH                 (0x0114E5FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_disRegardZQonSRtime_P0_OFF           (11)
  #define MC0_CH0_CR_MCMNTS_SPARE_disRegardZQonSRtime_P0_WID           ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_disRegardZQonSRtime_P0_MSK           (0x00000800)
  #define MC0_CH0_CR_MCMNTS_SPARE_disRegardZQonSRtime_P0_MIN           (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_disRegardZQonSRtime_P0_MAX           (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_disRegardZQonSRtime_P0_DEF           (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_disRegardZQonSRtime_P0_HSH           (0x0116E5FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_Decoder_EBH_P0_OFF                   (12)
  #define MC0_CH0_CR_MCMNTS_SPARE_Decoder_EBH_P0_WID                   ( 2)
  #define MC0_CH0_CR_MCMNTS_SPARE_Decoder_EBH_P0_MSK                   (0x00003000)
  #define MC0_CH0_CR_MCMNTS_SPARE_Decoder_EBH_P0_MIN                   (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_Decoder_EBH_P0_MAX                   (3) // 0x00000003
  #define MC0_CH0_CR_MCMNTS_SPARE_Decoder_EBH_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_Decoder_EBH_P0_HSH                   (0x0218E5FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_DDR_alert_P0_OFF                     (14)
  #define MC0_CH0_CR_MCMNTS_SPARE_DDR_alert_P0_WID                     ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_DDR_alert_P0_MSK                     (0x00004000)
  #define MC0_CH0_CR_MCMNTS_SPARE_DDR_alert_P0_MIN                     (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_DDR_alert_P0_MAX                     (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_DDR_alert_P0_DEF                     (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_DDR_alert_P0_HSH                     (0x011CE5FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_DisSREXcnt_P0_OFF                    (15)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisSREXcnt_P0_WID                    ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisSREXcnt_P0_MSK                    (0x00008000)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisSREXcnt_P0_MIN                    (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisSREXcnt_P0_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_DisSREXcnt_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisSREXcnt_P0_HSH                    (0x011EE5FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX8Ref_P0_OFF                    (16)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX8Ref_P0_WID                    ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX8Ref_P0_MSK                    (0x00010000)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX8Ref_P0_MIN                    (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX8Ref_P0_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX8Ref_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX8Ref_P0_HSH                    (0x0120E5FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_Background_ZQ_Mode_P0_OFF            (17)
  #define MC0_CH0_CR_MCMNTS_SPARE_Background_ZQ_Mode_P0_WID            ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_Background_ZQ_Mode_P0_MSK            (0x00020000)
  #define MC0_CH0_CR_MCMNTS_SPARE_Background_ZQ_Mode_P0_MIN            (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_Background_ZQ_Mode_P0_MAX            (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_Background_ZQ_Mode_P0_DEF            (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_Background_ZQ_Mode_P0_HSH            (0x0122E5FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_global_driver_wake_without_ref_P0_OFF (18)
  #define MC0_CH0_CR_MCMNTS_SPARE_global_driver_wake_without_ref_P0_WID ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_global_driver_wake_without_ref_P0_MSK (0x00040000)
  #define MC0_CH0_CR_MCMNTS_SPARE_global_driver_wake_without_ref_P0_MIN (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_global_driver_wake_without_ref_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_global_driver_wake_without_ref_P0_DEF (0x00000001)
  #define MC0_CH0_CR_MCMNTS_SPARE_global_driver_wake_without_ref_P0_HSH (0x0124E5FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_DisMaintenanceRoundRobinArb_P0_OFF   (19)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisMaintenanceRoundRobinArb_P0_WID   ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisMaintenanceRoundRobinArb_P0_MSK   (0x00080000)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisMaintenanceRoundRobinArb_P0_MIN   (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisMaintenanceRoundRobinArb_P0_MAX   (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_DisMaintenanceRoundRobinArb_P0_DEF   (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisMaintenanceRoundRobinArb_P0_HSH   (0x0126E5FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass2_P0_OFF                    (20)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass2_P0_WID                    ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass2_P0_MSK                    (0x00100000)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass2_P0_MIN                    (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass2_P0_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass2_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass2_P0_HSH                    (0x0128E5FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass1_P0_OFF                    (21)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass1_P0_WID                    ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass1_P0_MSK                    (0x00200000)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass1_P0_MIN                    (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass1_P0_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass1_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass1_P0_HSH                    (0x012AE5FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass0_P0_OFF                    (22)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass0_P0_WID                    ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass0_P0_MSK                    (0x00400000)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass0_P0_MIN                    (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass0_P0_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass0_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass0_P0_HSH                    (0x012CE5FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_Run_Delay_P0_OFF                     (23)
  #define MC0_CH0_CR_MCMNTS_SPARE_Run_Delay_P0_WID                     ( 5)
  #define MC0_CH0_CR_MCMNTS_SPARE_Run_Delay_P0_MSK                     (0x0F800000)
  #define MC0_CH0_CR_MCMNTS_SPARE_Run_Delay_P0_MIN                     (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_Run_Delay_P0_MAX                     (31) // 0x0000001F
  #define MC0_CH0_CR_MCMNTS_SPARE_Run_Delay_P0_DEF                     (0x00000010)
  #define MC0_CH0_CR_MCMNTS_SPARE_Run_Delay_P0_HSH                     (0x052EE5FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_Generic_mrs_device_loop_enable_P0_OFF (28)
  #define MC0_CH0_CR_MCMNTS_SPARE_Generic_mrs_device_loop_enable_P0_WID ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_Generic_mrs_device_loop_enable_P0_MSK (0x10000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_Generic_mrs_device_loop_enable_P0_MIN (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_Generic_mrs_device_loop_enable_P0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_Generic_mrs_device_loop_enable_P0_DEF (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_Generic_mrs_device_loop_enable_P0_HSH (0x0138E5FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_V_P0_OFF                    (29)
  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_V_P0_WID                    ( 3)
  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_V_P0_MSK                    (0xE0000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_V_P0_MIN                    (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_V_P0_MAX                    (7) // 0x00000007
  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_V_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_V_P0_HSH                    (0x033AE5FC)

#define MC0_CH0_CR_MCMNTS_RDDATA_CTL_P0_REG                            (0x0000E600)

  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc0_credits_P0_OFF        ( 0)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc0_credits_P0_WID        ( 5)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc0_credits_P0_MSK        (0x0000001F)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc0_credits_P0_MIN        (0)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc0_credits_P0_MAX        (31) // 0x0000001F
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc0_credits_P0_DEF        (0x0000000F)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc0_credits_P0_HSH        (0x0500E600)

  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc1_credits_P0_OFF        ( 5)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc1_credits_P0_WID        ( 5)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc1_credits_P0_MSK        (0x000003E0)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc1_credits_P0_MIN        (0)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc1_credits_P0_MAX        (31) // 0x0000001F
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc1_credits_P0_DEF        (0x0000000F)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc1_credits_P0_HSH        (0x050AE600)

  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_total_credits_P0_OFF      (10)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_total_credits_P0_WID      ( 5)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_total_credits_P0_MSK      (0x00007C00)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_total_credits_P0_MIN      (0)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_total_credits_P0_MAX      (31) // 0x0000001F
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_total_credits_P0_DEF      (0x00000010)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_total_credits_P0_HSH      (0x0514E600)

#define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_P0_REG             (0x0000E608)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_0_P0_OFF ( 0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_0_P0_WID ( 8)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_0_P0_MSK (0x000000FF)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_0_P0_MIN (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_0_P0_MAX (255) // 0x000000FF
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_0_P0_DEF (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_0_P0_HSH (0x0800E608)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_1_P0_OFF ( 8)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_1_P0_WID ( 8)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_1_P0_MSK (0x0000FF00)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_1_P0_MIN (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_1_P0_MAX (255) // 0x000000FF
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_1_P0_DEF (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_1_P0_HSH (0x0810E608)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_2_P0_OFF (16)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_2_P0_WID ( 8)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_2_P0_MSK (0x00FF0000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_2_P0_MIN (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_2_P0_MAX (255) // 0x000000FF
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_2_P0_DEF (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_2_P0_HSH (0x0820E608)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_3_P0_OFF (24)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_3_P0_WID ( 8)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_3_P0_MSK (0xFF000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_3_P0_MIN (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_3_P0_MAX (255) // 0x000000FF
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_3_P0_DEF (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_TIMING_FIELD_3_P0_HSH (0x0830E608)

#define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_1_P0_REG             (0x0000E60C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG                    (0x0000E610)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ADDRESS_P0_OFF          ( 0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ADDRESS_P0_WID          ( 8)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ADDRESS_P0_MSK          (0x000000FF)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ADDRESS_P0_MIN          (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ADDRESS_P0_MAX          (255) // 0x000000FF
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ADDRESS_P0_DEF          (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ADDRESS_P0_HSH          (0x0800E610)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_GENERIC_MRS_STORAGE_POINTER_P0_OFF ( 8)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_GENERIC_MRS_STORAGE_POINTER_P0_WID ( 9)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_GENERIC_MRS_STORAGE_POINTER_P0_MSK (0x0001FF00)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_GENERIC_MRS_STORAGE_POINTER_P0_MIN (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_GENERIC_MRS_STORAGE_POINTER_P0_MAX (511) // 0x000001FF
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_GENERIC_MRS_STORAGE_POINTER_P0_DEF (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_GENERIC_MRS_STORAGE_POINTER_P0_HSH (0x0910E610)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_COMMAND_TYPE_P0_OFF     (22)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_COMMAND_TYPE_P0_WID     ( 2)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_COMMAND_TYPE_P0_MSK     (0x00C00000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_COMMAND_TYPE_P0_MIN     (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_COMMAND_TYPE_P0_MAX     (3) // 0x00000003
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_COMMAND_TYPE_P0_DEF     (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_COMMAND_TYPE_P0_HSH     (0x022CE610)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_TIMING_VALUE_POINTER_P0_OFF (24)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_TIMING_VALUE_POINTER_P0_WID ( 3)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_TIMING_VALUE_POINTER_P0_MSK (0x07000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_TIMING_VALUE_POINTER_P0_MIN (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_TIMING_VALUE_POINTER_P0_MAX (7) // 0x00000007
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_TIMING_VALUE_POINTER_P0_DEF (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_TIMING_VALUE_POINTER_P0_HSH (0x0330E610)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_DEVICE_P0_OFF       (27)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_DEVICE_P0_WID       ( 1)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_DEVICE_P0_MSK       (0x08000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_DEVICE_P0_MIN       (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_DEVICE_P0_MAX       (1) // 0x00000001
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_DEVICE_P0_DEF       (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_DEVICE_P0_HSH       (0x0136E610)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_FSP_CONTROL_P0_OFF      (28)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_FSP_CONTROL_P0_WID      ( 2)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_FSP_CONTROL_P0_MSK      (0x30000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_FSP_CONTROL_P0_MIN      (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_FSP_CONTROL_P0_MAX      (3) // 0x00000003
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_FSP_CONTROL_P0_DEF      (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_FSP_CONTROL_P0_HSH      (0x0238E610)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_RANK_P0_OFF         (30)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_RANK_P0_WID         ( 1)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_RANK_P0_MSK         (0x40000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_RANK_P0_MIN         (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_RANK_P0_MAX         (1) // 0x00000001
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_RANK_P0_DEF         (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_RANK_P0_HSH         (0x013CE610)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ACTIVE_P0_OFF           (31)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ACTIVE_P0_WID           ( 1)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ACTIVE_P0_MSK           (0x80000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ACTIVE_P0_MIN           (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ACTIVE_P0_MAX           (1) // 0x00000001
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ACTIVE_P0_DEF           (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ACTIVE_P0_HSH           (0x013EE610)

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_1_P0_REG                    (0x0000E614)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_2_P0_REG                    (0x0000E618)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_3_P0_REG                    (0x0000E61C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_4_P0_REG                    (0x0000E620)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_5_P0_REG                    (0x0000E624)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_6_P0_REG                    (0x0000E628)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_7_P0_REG                    (0x0000E62C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_8_P0_REG                    (0x0000E630)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_9_P0_REG                    (0x0000E634)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_10_P0_REG                   (0x0000E638)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_11_P0_REG                   (0x0000E63C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_12_P0_REG                   (0x0000E640)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_13_P0_REG                   (0x0000E644)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_14_P0_REG                   (0x0000E648)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_15_P0_REG                   (0x0000E64C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_16_P0_REG                   (0x0000E650)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_17_P0_REG                   (0x0000E654)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_18_P0_REG                   (0x0000E658)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_19_P0_REG                   (0x0000E65C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_20_P0_REG                   (0x0000E660)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_21_P0_REG                   (0x0000E664)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_22_P0_REG                   (0x0000E668)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_23_P0_REG                   (0x0000E66C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_24_P0_REG                   (0x0000E670)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_25_P0_REG                   (0x0000E674)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_26_P0_REG                   (0x0000E678)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_27_P0_REG                   (0x0000E67C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_28_P0_REG                   (0x0000E680)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_29_P0_REG                   (0x0000E684)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_30_P0_REG                   (0x0000E688)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_31_P0_REG                   (0x0000E68C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_32_P0_REG                   (0x0000E690)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_33_P0_REG                   (0x0000E694)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_34_P0_REG                   (0x0000E698)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_35_P0_REG                   (0x0000E69C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_36_P0_REG                   (0x0000E6A0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_37_P0_REG                   (0x0000E6A4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_38_P0_REG                   (0x0000E6A8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_39_P0_REG                   (0x0000E6AC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_40_P0_REG                   (0x0000E6B0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_41_P0_REG                   (0x0000E6B4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_42_P0_REG                   (0x0000E6B8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_43_P0_REG                   (0x0000E6BC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_44_P0_REG                   (0x0000E6C0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_45_P0_REG                   (0x0000E6C4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_46_P0_REG                   (0x0000E6C8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_47_P0_REG                   (0x0000E6CC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_48_P0_REG                   (0x0000E6D0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_49_P0_REG                   (0x0000E6D4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_50_P0_REG                   (0x0000E6D8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_51_P0_REG                   (0x0000E6DC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_52_P0_REG                   (0x0000E6E0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_53_P0_REG                   (0x0000E6E4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_54_P0_REG                   (0x0000E6E8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_55_P0_REG                   (0x0000E6EC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_56_P0_REG                   (0x0000E6F0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_57_P0_REG                   (0x0000E6F4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_58_P0_REG                   (0x0000E6F8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_59_P0_REG                   (0x0000E6FC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_60_P0_REG                   (0x0000E700)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_61_P0_REG                   (0x0000E704)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_62_P0_REG                   (0x0000E708)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_63_P0_REG                   (0x0000E70C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_64_P0_REG                   (0x0000E710)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_65_P0_REG                   (0x0000E714)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_66_P0_REG                   (0x0000E718)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_67_P0_REG                   (0x0000E71C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_68_P0_REG                   (0x0000E720)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_69_P0_REG                   (0x0000E724)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_70_P0_REG                   (0x0000E728)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_71_P0_REG                   (0x0000E72C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_72_P0_REG                   (0x0000E730)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_73_P0_REG                   (0x0000E734)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_74_P0_REG                   (0x0000E738)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_75_P0_REG                   (0x0000E73C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG             (0x0000E740)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_0_P0_OFF    ( 0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_0_P0_WID    ( 8)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_0_P0_MSK    (0x000000FF)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_0_P0_MIN    (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_0_P0_MAX    (255) // 0x000000FF
  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_0_P0_DEF    (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_0_P0_HSH    (0x0800E740)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_1_P0_OFF    ( 8)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_1_P0_WID    ( 8)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_1_P0_MSK    (0x0000FF00)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_1_P0_MIN    (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_1_P0_MAX    (255) // 0x000000FF
  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_1_P0_DEF    (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_1_P0_HSH    (0x0810E740)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_2_P0_OFF    (16)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_2_P0_WID    ( 8)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_2_P0_MSK    (0x00FF0000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_2_P0_MIN    (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_2_P0_MAX    (255) // 0x000000FF
  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_2_P0_DEF    (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_2_P0_HSH    (0x0820E740)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_3_P0_OFF    (24)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_3_P0_WID    ( 8)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_3_P0_MSK    (0xFF000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_3_P0_MIN    (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_3_P0_MAX    (255) // 0x000000FF
  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_3_P0_DEF    (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_BYTE_3_P0_HSH    (0x0830E740)

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_1_P0_REG             (0x0000E744)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_2_P0_REG             (0x0000E748)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_3_P0_REG             (0x0000E74C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_4_P0_REG             (0x0000E750)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_5_P0_REG             (0x0000E754)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_6_P0_REG             (0x0000E758)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_7_P0_REG             (0x0000E75C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_8_P0_REG             (0x0000E760)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_9_P0_REG             (0x0000E764)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_10_P0_REG            (0x0000E768)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_11_P0_REG            (0x0000E76C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_12_P0_REG            (0x0000E770)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_13_P0_REG            (0x0000E774)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_14_P0_REG            (0x0000E778)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_15_P0_REG            (0x0000E77C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_16_P0_REG            (0x0000E780)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_17_P0_REG            (0x0000E784)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_18_P0_REG            (0x0000E788)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_19_P0_REG            (0x0000E78C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_20_P0_REG            (0x0000E790)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_21_P0_REG            (0x0000E794)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_22_P0_REG            (0x0000E798)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_23_P0_REG            (0x0000E79C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_24_P0_REG            (0x0000E7A0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_25_P0_REG            (0x0000E7A4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_26_P0_REG            (0x0000E7A8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_27_P0_REG            (0x0000E7AC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_28_P0_REG            (0x0000E7B0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_29_P0_REG            (0x0000E7B4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_30_P0_REG            (0x0000E7B8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_31_P0_REG            (0x0000E7BC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_32_P0_REG            (0x0000E7C0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_33_P0_REG            (0x0000E7C4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_34_P0_REG            (0x0000E7C8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_35_P0_REG            (0x0000E7CC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_36_P0_REG            (0x0000E7D0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_37_P0_REG            (0x0000E7D4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_38_P0_REG            (0x0000E7D8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_39_P0_REG            (0x0000E7DC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_40_P0_REG            (0x0000E7E0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_41_P0_REG            (0x0000E7E4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_42_P0_REG            (0x0000E7E8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_43_P0_REG            (0x0000E7EC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_44_P0_REG            (0x0000E7F0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_45_P0_REG            (0x0000E7F4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_46_P0_REG            (0x0000E7F8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_47_P0_REG            (0x0000E7FC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_TC_PRE_P0_REG                                       (0x0000E800)
//Duplicate of MC0_CH0_CR_TC_PRE_P0_REG

#define MC0_CH1_CR_TC_ACT_P0_REG                                       (0x0000E808)
//Duplicate of MC0_CH0_CR_TC_ACT_P0_REG

#define MC0_CH1_CR_TC_RDRD_P0_REG                                      (0x0000E80C)
//Duplicate of MC0_CH0_CR_TC_RDRD_P0_REG

#define MC0_CH1_CR_TC_RDWR_P0_REG                                      (0x0000E810)
//Duplicate of MC0_CH0_CR_TC_RDWR_P0_REG

#define MC0_CH1_CR_TC_WRRD_P0_REG                                      (0x0000E814)
//Duplicate of MC0_CH0_CR_TC_WRRD_P0_REG

#define MC0_CH1_CR_TC_WRWR_P0_REG                                      (0x0000E818)
//Duplicate of MC0_CH0_CR_TC_WRWR_P0_REG

#define MC0_CH1_CR_SC_ROUNDTRIP_LATENCY_P0_REG                         (0x0000E820)
//Duplicate of MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_P0_REG

#define MC0_CH1_CR_SCHED_CBIT_P0_REG                                   (0x0000E828)
//Duplicate of MC0_CH0_CR_SCHED_CBIT_P0_REG

#define MC0_CH1_CR_SCHED_SECOND_CBIT_P0_REG                            (0x0000E82C)
//Duplicate of MC0_CH0_CR_SCHED_SECOND_CBIT_P0_REG

#define MC0_CH1_CR_DFT_MISC_P0_REG                                     (0x0000E830)
//Duplicate of MC0_CH0_CR_DFT_MISC_P0_REG

#define MC0_CH1_CR_SC_PCIT_P0_REG                                      (0x0000E834)
//Duplicate of MC0_CH0_CR_SC_PCIT_P0_REG

#define MC0_CH1_CR_ECC_DFT_P0_REG                                      (0x0000E838)
//Duplicate of MC0_CH0_CR_ECC_DFT_P0_REG

#define MC0_CH1_CR_PM_PDWN_CONFIG_P0_REG                               (0x0000E840)
//Duplicate of MC0_CH0_CR_PM_PDWN_CONFIG_P0_REG

#define MC0_CH1_CR_WMM_READ_CONFIG_P0_REG                              (0x0000E844)
//Duplicate of MC0_CH0_CR_WMM_READ_CONFIG_P0_REG

#define MC0_CH1_CR_ECCERRLOG0_P0_REG                                   (0x0000E848)
//Duplicate of MC0_CH0_CR_ECCERRLOG0_P0_REG

#define MC0_CH1_CR_ECCERRLOG1_P0_REG                                   (0x0000E84C)
//Duplicate of MC0_CH0_CR_ECCERRLOG1_P0_REG

#define MC0_CH1_CR_TC_PWRDN_P0_REG                                     (0x0000E850)
//Duplicate of MC0_CH0_CR_TC_PWRDN_P0_REG

#define MC0_CH1_CR_QUEUE_ENTRY_DISABLE_RPQ_P0_REG                      (0x0000E858)
//Duplicate of MC0_CH0_CR_QUEUE_ENTRY_DISABLE_RPQ_P0_REG

#define MC0_CH1_CR_QUEUE_ENTRY_DISABLE_IPQ_P0_REG                      (0x0000E85C)
//Duplicate of MC0_CH0_CR_QUEUE_ENTRY_DISABLE_IPQ_P0_REG

#define MC0_CH1_CR_QUEUE_ENTRY_DISABLE_WPQ_P0_REG                      (0x0000E860)
//Duplicate of MC0_CH0_CR_QUEUE_ENTRY_DISABLE_WPQ_P0_REG

#define MC0_CH1_CR_SC_WDBWM_P0_REG                                     (0x0000E868)
//Duplicate of MC0_CH0_CR_SC_WDBWM_P0_REG

#define MC0_CH1_CR_TC_ODT_P0_REG                                       (0x0000E870)
//Duplicate of MC0_CH0_CR_TC_ODT_P0_REG

#define MC0_CH1_CR_MCSCHEDS_SPARE_P0_REG                               (0x0000E878)
//Duplicate of MC0_CH0_CR_MCSCHEDS_SPARE_P0_REG

#define MC0_CH1_CR_TC_MPC_P0_REG                                       (0x0000E87C)
//Duplicate of MC0_CH0_CR_TC_MPC_P0_REG

#define MC0_CH1_CR_SC_ODT_MATRIX_P0_REG                                (0x0000E880)
//Duplicate of MC0_CH0_CR_SC_ODT_MATRIX_P0_REG

#define MC0_CH1_CR_DFT_BLOCK_P0_REG                                    (0x0000E884)
//Duplicate of MC0_CH0_CR_DFT_BLOCK_P0_REG

#define MC0_CH1_CR_SC_GS_CFG_P0_REG                                    (0x0000E888)
//Duplicate of MC0_CH0_CR_SC_GS_CFG_P0_REG

#define MC0_CH1_CR_SC_PH_THROTTLING_0_P0_REG                           (0x0000E890)
//Duplicate of MC0_CH0_CR_SC_PH_THROTTLING_0_P0_REG

#define MC0_CH1_CR_SC_PH_THROTTLING_1_P0_REG                           (0x0000E894)
//Duplicate of MC0_CH0_CR_SC_PH_THROTTLING_1_P0_REG

#define MC0_CH1_CR_SC_PH_THROTTLING_2_P0_REG                           (0x0000E898)
//Duplicate of MC0_CH0_CR_SC_PH_THROTTLING_2_P0_REG

#define MC0_CH1_CR_SC_PH_THROTTLING_3_P0_REG                           (0x0000E89C)
//Duplicate of MC0_CH0_CR_SC_PH_THROTTLING_3_P0_REG

#define MC0_CH1_CR_SC_WPQ_THRESHOLD_P0_REG                             (0x0000E8A0)
//Duplicate of MC0_CH0_CR_SC_WPQ_THRESHOLD_P0_REG

#define MC0_CH1_CR_SC_PR_CNT_CONFIG_P0_REG                             (0x0000E8A8)
//Duplicate of MC0_CH0_CR_SC_PR_CNT_CONFIG_P0_REG

#define MC0_CH1_CR_REUT_CH_MISC_CKE_CS_CTRL_P0_REG                     (0x0000E8B0)
//Duplicate of MC0_CH0_CR_REUT_CH_MISC_CKE_CS_CTRL_P0_REG

#define MC0_CH1_CR_REUT_CH_MISC_ODT_CTRL_P0_REG                        (0x0000E8B4)
//Duplicate of MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_P0_REG

#define MC0_CH1_CR_SPID_LOW_POWER_CTL_P0_REG                           (0x0000E8B8)
//Duplicate of MC0_CH0_CR_SPID_LOW_POWER_CTL_P0_REG

#define MC0_CH1_CR_SC_GS_CFG_TRAINING_P0_REG                           (0x0000E8BC)
//Duplicate of MC0_CH0_CR_SC_GS_CFG_TRAINING_P0_REG

#define MC0_CH1_CR_SCHED_THIRD_CBIT_P0_REG                             (0x0000E8C0)
//Duplicate of MC0_CH0_CR_SCHED_THIRD_CBIT_P0_REG

#define MC0_CH1_CR_DEADLOCK_BREAKER_P0_REG                             (0x0000E8C4)
//Duplicate of MC0_CH0_CR_DEADLOCK_BREAKER_P0_REG

#define MC0_CH1_CR_XARB_TC_BUBBLE_INJ_P0_REG                           (0x0000E8C8)
//Duplicate of MC0_CH0_CR_XARB_TC_BUBBLE_INJ_P0_REG

#define MC0_CH1_CR_XARB_CFG_BUBBLE_INJ_P0_REG                          (0x0000E8CC)
//Duplicate of MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_P0_REG

#define MC0_CH1_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_P0_REG              (0x0000E8D0)
//Duplicate of MC0_MCMAINS_GLOBAL_DRIVER_GATE_CFG_P0_REG

#define MC0_CH1_CR_SC_BLOCKING_RULES_CFG_P0_REG                        (0x0000E8D4)
//Duplicate of MC0_CH0_CR_SC_BLOCKING_RULES_CFG_P0_REG

#define MC0_CH1_CR_PWM_DDR_SUBCH0_ACT_COUNTER_P0_REG                   (0x0000E8D8)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_P0_REG

#define MC0_CH1_CR_PWM_DDR_SUBCH1_ACT_COUNTER_P0_REG                   (0x0000E8E0)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_P0_REG

#define MC0_CH1_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_P0_REG         (0x0000E8E8)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_P0_REG

#define MC0_CH1_CR_PWM_DDR_SUBCH1_REQ_OCCUPANCY_COUNTER_P0_REG         (0x0000E8F0)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_P0_REG

#define MC0_CH1_CR_WCK_CONFIG_P0_REG                                   (0x0000E8F8)
//Duplicate of MC0_CH0_CR_WCK_CONFIG_P0_REG

#define MC0_CH1_CR_REUT_CH_MISC_REFRESH_CTRL_P0_REG                    (0x0000EC04)
//Duplicate of MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_P0_REG

#define MC0_CH1_CR_REUT_CH_MISC_ZQ_CTRL_P0_REG                         (0x0000EC08)
//Duplicate of MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_P0_REG

#define MC0_CH1_CR_DDR_MR_PARAMS_P0_REG                                (0x0000EC10)
//Duplicate of MC0_CH0_CR_DDR_MR_PARAMS_P0_REG

#define MC0_CH1_CR_DDR_MR_COMMAND_P0_REG                               (0x0000EC14)
//Duplicate of MC0_CH0_CR_DDR_MR_COMMAND_P0_REG

#define MC0_CH1_CR_DDR_MR_RESULT_0_P0_REG                              (0x0000EC18)
//Duplicate of MC0_CH0_CR_DDR_MR_RESULT_0_P0_REG

#define MC0_CH1_CR_DDR_MR_RESULT_1_P0_REG                              (0x0000EC1C)
//Duplicate of MC0_CH0_CR_DDR_MR_RESULT_1_P0_REG

#define MC0_CH1_CR_DDR_MR_RESULT_2_P0_REG                              (0x0000EC20)
//Duplicate of MC0_CH0_CR_DDR_MR_RESULT_2_P0_REG

#define MC0_CH1_CR_MR4_RANK_TEMPERATURE_P0_REG                         (0x0000EC24)
//Duplicate of MC0_CH0_CR_MR4_RANK_TEMPERATURE_P0_REG

#define MC0_CH1_CR_DDR4_MPR_RANK_TEMPERATURE_P0_REG                    (0x0000EC28)
//Duplicate of MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_P0_REG

#define MC0_CH1_CR_DESWIZZLE_LOW_ERM_P0_REG                            (0x0000EC30)
//Duplicate of MC0_CH0_CR_DESWIZZLE_LOW_ERM_P0_REG

#define MC0_CH1_CR_TC_RFP_P0_REG                                       (0x0000EC38)
//Duplicate of MC0_CH0_CR_TC_RFP_P0_REG

#define MC0_CH1_CR_TC_RFTP_P0_REG                                      (0x0000EC3C)
//Duplicate of MC0_CH0_CR_TC_RFTP_P0_REG

#define MC0_CH1_CR_TC_SRFTP_P0_REG                                     (0x0000EC40)
//Duplicate of MC0_CH0_CR_TC_SRFTP_P0_REG

#define MC0_CH1_CR_MC_REFRESH_STAGGER_P0_REG                           (0x0000EC44)
//Duplicate of MC0_CH0_CR_MC_REFRESH_STAGGER_P0_REG

#define MC0_CH1_CR_TC_ZQCAL_P0_REG                                     (0x0000EC48)
//Duplicate of MC0_CH0_CR_TC_ZQCAL_P0_REG

#define MC0_CH1_CR_MRH_CONFIG_P0_REG                                   (0x0000EC4C)
//Duplicate of MC0_CH0_CR_MRH_CONFIG_P0_REG

#define MC0_CH1_CR_TC_MR4_SHADDOW_P0_REG                               (0x0000EC50)
//Duplicate of MC0_CH0_CR_TC_MR4_SHADDOW_P0_REG

#define MC0_CH1_CR_MC_INIT_STATE_P0_REG                                (0x0000EC54)
//Duplicate of MC0_CH0_CR_MC_INIT_STATE_P0_REG

#define MC0_CH1_CR_WDB_VISA_SEL_P0_REG                                 (0x0000EC58)
//Duplicate of MC0_CH0_CR_WDB_VISA_SEL_P0_REG

#define MC0_CH1_CR_PM_DIMM_IDLE_ENERGY_P0_REG                          (0x0000EC60)
//Duplicate of MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_P0_REG

#define MC0_CH1_CR_PM_DIMM_PD_ENERGY_P0_REG                            (0x0000EC64)
//Duplicate of MC0_CH0_CR_PM_DIMM_PD_ENERGY_P0_REG

#define MC0_CH1_CR_PM_DIMM_ACT_ENERGY_P0_REG                           (0x0000EC68)
//Duplicate of MC0_CH0_CR_PM_DIMM_ACT_ENERGY_P0_REG

#define MC0_CH1_CR_PM_DIMM_RD_ENERGY_P0_REG                            (0x0000EC6C)
//Duplicate of MC0_CH0_CR_PM_DIMM_RD_ENERGY_P0_REG

#define MC0_CH1_CR_PM_DIMM_WR_ENERGY_P0_REG                            (0x0000EC70)
//Duplicate of MC0_CH0_CR_PM_DIMM_WR_ENERGY_P0_REG

#define MC0_CH1_CR_SC_WR_DELAY_P0_REG                                  (0x0000EC78)
//Duplicate of MC0_CH0_CR_SC_WR_DELAY_P0_REG

#define MC0_CH1_CR_READ_RETURN_DFT_P0_REG                              (0x0000EC7C)
//Duplicate of MC0_CH0_CR_READ_RETURN_DFT_P0_REG

#define MC0_CH1_CR_DESWIZZLE_LOW_P0_REG                                (0x0000EC80)
//Duplicate of MC0_CH0_CR_DESWIZZLE_LOW_ERM_P0_REG

#define MC0_CH1_CR_SC_PBR_P0_REG                                       (0x0000EC88)
//Duplicate of MC0_CH0_CR_SC_PBR_P0_REG

#define MC0_CH1_CR_TC_LPDDR4_MISC_P0_REG                               (0x0000EC94)
//Duplicate of MC0_CH0_CR_TC_LPDDR4_MISC_P0_REG

#define MC0_CH1_CR_DESWIZZLE_HIGH_ERM_P0_REG                           (0x0000EC98)
//Duplicate of MC0_CH0_CR_DESWIZZLE_HIGH_ERM_P0_REG

#define MC0_CH1_CR_PM_ALL_RANKS_CKE_LOW_COUNT_P0_REG                   (0x0000ECB0)
//Duplicate of MC0_PWM_COUNTERS_DURATION_P0_REG

#define MC0_CH1_CR_DESWIZZLE_HIGH_P0_REG                               (0x0000ECB8)
//Duplicate of MC0_CH0_CR_DESWIZZLE_HIGH_ERM_P0_REG

#define MC0_CH1_CR_TC_SREXITTP_P0_REG                                  (0x0000ECC0)
//Duplicate of MC0_CH0_CR_TC_SREXITTP_P0_REG

#define MC0_CH1_CR_DQS_OSCILLATOR_PARAMS_P0_REG                        (0x0000ECC8)
//Duplicate of MC0_CH0_CR_DQS_OSCILLATOR_PARAMS_P0_REG

#define MC0_CH1_CR_LPDDR_PASR_P0_REG                                   (0x0000ECCC)
//Duplicate of MC0_CH0_CR_LPDDR_PASR_P0_REG

#define MC0_CH1_CR_WDB_RD_WR_DFX_DATA_P0_REG                           (0x0000ECD8)
//Duplicate of MC0_CH0_CR_WDB_RD_WR_DFX_DATA_P0_REG

#define MC0_CH1_CR_WDB_RD_WR_DFX_CTL_P0_REG                            (0x0000ECE0)
//Duplicate of MC0_CH0_CR_WDB_RD_WR_DFX_CTL_P0_REG

#define MC0_CH1_CR_REF_FSM_STATUS_P0_REG                               (0x0000ECE4)
//Duplicate of MC0_CH0_CR_REF_FSM_STATUS_P0_REG

#define MC0_CH1_CR_WDB_MBIST_0_P0_REG                                  (0x0000ECE8)
//Duplicate of MC0_CH0_CR_WDB_MBIST_0_P0_REG

#define MC0_CH1_CR_WDB_MBIST_1_P0_REG                                  (0x0000ECEC)
//Duplicate of MC0_CH0_CR_WDB_MBIST_0_P0_REG

#define MC0_CH1_CR_RDB_MBIST_P0_REG                                    (0x0000ECF8)
//Duplicate of MC0_CH0_CR_WDB_MBIST_0_P0_REG

#define MC0_CH1_CR_ECC_INJECT_COUNT_P0_REG                             (0x0000ECFC)
//Duplicate of MC0_CH0_CR_ECC_INJECT_COUNT_P0_REG

#define MC0_CH1_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_P0_REG                (0x0000ED00)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_P0_REG

#define MC0_CH1_CR_PWM_DDR_SUBCH1_RDDATA_COUNTER_P0_REG                (0x0000ED08)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_P0_REG

#define MC0_CH1_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_P0_REG                (0x0000ED10)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_P0_REG

#define MC0_CH1_CR_PWM_DDR_SUBCH1_WRDATA_COUNTER_P0_REG                (0x0000ED18)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_P0_REG

#define MC0_CH1_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_P0_REG                (0x0000ED20)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_P0_REG

#define MC0_CH1_CR_DDR4_MR2_RTT_WR_DIMM1_VALUES_P0_REG                 (0x0000ED28)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_P0_REG

#define MC0_CH1_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_P0_REG                 (0x0000ED30)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_P0_REG

#define MC0_CH1_CR_DDR4_MR6_VREF_DIMM1_VALUES_1_P0_REG                 (0x0000ED38)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_P0_REG

#define MC0_CH1_CR_DDR4_MR1_ODIC_DIMM1_VALUES_P0_REG                   (0x0000ED44)
//Duplicate of MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_P0_REG

#define MC0_CH1_CR_DDR4_MR5_RTT_PARK_VALUES_P0_REG                     (0x0000ED48)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_P0_REG

#define MC0_CH1_CR_DDR4_MR5_RTT_PARK_DIMM1_VALUES_P0_REG               (0x0000ED50)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_P0_REG

#define MC0_CH1_CR_DDR4_MR1_RTT_NOM_VALUES_P0_REG                      (0x0000ED58)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_P0_REG

#define MC0_CH1_CR_LPDDR4_DISCRETE_MR_VALUES_0_P0_REG                  (0x0000ED60)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_P0_REG

#define MC0_CH1_CR_LPDDR4_DISCRETE_MR_VALUES_1_P0_REG                  (0x0000ED68)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_P0_REG

#define MC0_CH1_CR_LPDDR4_DISCRETE_MR_VALUES_2_P0_REG                  (0x0000ED70)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_P0_REG

#define MC0_CH1_CR_LPDDR4_DISCRETE_MR_VALUES_3_P0_REG                  (0x0000ED78)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_P0_REG

#define MC0_CH1_CR_LPDDR4_DISCRETE_MR_VALUES_4_P0_REG                  (0x0000ED80)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_P0_REG

#define MC0_CH1_CR_LPDDR4_DISCRETE_MR_VALUES_5_P0_REG                  (0x0000ED88)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_P0_REG

#define MC0_CH1_CR_LPDDR4_DISCRETE_MR_VALUES_6_P0_REG                  (0x0000ED90)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_P0_REG

#define MC0_CH1_CR_LPDDR4_DISCRETE_MR_VALUES_7_P0_REG                  (0x0000ED98)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_P0_REG

#define MC0_CH1_CR_DDR4_MR0_MR1_CONTENT_P0_REG                         (0x0000EDA0)
//Duplicate of MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_P0_REG

#define MC0_CH1_CR_DDR4_MR2_MR3_CONTENT_P0_REG                         (0x0000EDA4)
//Duplicate of MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_P0_REG

#define MC0_CH1_CR_DDR4_MR4_MR5_CONTENT_P0_REG                         (0x0000EDA8)
//Duplicate of MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_P0_REG

#define MC0_CH1_CR_DDR4_MR6_MR7_CONTENT_P0_REG                         (0x0000EDAC)
//Duplicate of MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_P0_REG

#define MC0_CH1_CR_DDR4_MR2_RTT_WR_VALUES_P0_REG                       (0x0000EDB0)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_P0_REG

#define MC0_CH1_CR_DDR4_MR6_VREF_VALUES_0_P0_REG                       (0x0000EDB8)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_P0_REG

#define MC0_CH1_CR_DDR4_MR6_VREF_VALUES_1_P0_REG                       (0x0000EDC0)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_P0_REG

#define MC0_CH1_CR_LPDDR_MR_CONTENT_P0_REG                             (0x0000EDC8)
//Duplicate of MC0_CH0_CR_LPDDR_MR_CONTENT_P0_REG

#define MC0_CH1_CR_MRS_FSM_CONTROL_P0_REG                              (0x0000EDD0)
//Duplicate of MC0_CH0_CR_MRS_FSM_CONTROL_P0_REG

#define MC0_CH1_CR_MRS_FSM_RUN_P0_REG                                  (0x0000EDD8)
//Duplicate of MC0_CH0_CR_MRS_FSM_RUN_P0_REG

#define MC0_CH1_CR_DDR4_MR1_ODIC_VALUES_P0_REG                         (0x0000EDDC)
//Duplicate of MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_P0_REG

#define MC0_CH1_CR_PL_AGENT_CFG_DTF_P0_REG                             (0x0000EDE0)
//Duplicate of MC0_CH0_CR_PL_AGENT_CFG_DTF_P0_REG

#define MC0_CH1_CR_MCMNTS_GLOBAL_DRIVER_GATE_CFG_P0_REG                (0x0000EDE4)
//Duplicate of MC0_MCMAINS_GLOBAL_DRIVER_GATE_CFG_P0_REG

#define MC0_CH1_CR_DDR4_ECC_DEVICE_VALUES_P0_REG                       (0x0000EDE8)
//Duplicate of MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_P0_REG

#define MC0_CH1_CR_DDR4_ECC_DEVICE_DIMM1_VALUES_P0_REG                 (0x0000EDF0)
//Duplicate of MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_P0_REG

#define MC0_CH1_CR_MCMNTS_SPARE2_P0_REG                                (0x0000EDF8)
//Duplicate of MC0_CH0_CR_MCMNTS_SPARE2_P0_REG

#define MC0_CH1_CR_MCMNTS_SPARE_P0_REG                                 (0x0000EDFC)
//Duplicate of MC0_CH0_CR_MCMNTS_SPARE_P0_REG

#define MC0_CH1_CR_MCMNTS_RDDATA_CTL_P0_REG                            (0x0000EE00)
//Duplicate of MC0_CH0_CR_MCMNTS_RDDATA_CTL_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_P0_REG             (0x0000EE08)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_TIMING_STORAGE_1_P0_REG             (0x0000EE0C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG                    (0x0000EE10)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_1_P0_REG                    (0x0000EE14)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_2_P0_REG                    (0x0000EE18)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_3_P0_REG                    (0x0000EE1C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_4_P0_REG                    (0x0000EE20)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_5_P0_REG                    (0x0000EE24)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_6_P0_REG                    (0x0000EE28)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_7_P0_REG                    (0x0000EE2C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_8_P0_REG                    (0x0000EE30)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_9_P0_REG                    (0x0000EE34)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_10_P0_REG                   (0x0000EE38)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_11_P0_REG                   (0x0000EE3C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_12_P0_REG                   (0x0000EE40)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_13_P0_REG                   (0x0000EE44)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_14_P0_REG                   (0x0000EE48)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_15_P0_REG                   (0x0000EE4C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_16_P0_REG                   (0x0000EE50)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_17_P0_REG                   (0x0000EE54)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_18_P0_REG                   (0x0000EE58)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_19_P0_REG                   (0x0000EE5C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_20_P0_REG                   (0x0000EE60)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_21_P0_REG                   (0x0000EE64)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_22_P0_REG                   (0x0000EE68)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_23_P0_REG                   (0x0000EE6C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_24_P0_REG                   (0x0000EE70)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_25_P0_REG                   (0x0000EE74)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_26_P0_REG                   (0x0000EE78)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_27_P0_REG                   (0x0000EE7C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_28_P0_REG                   (0x0000EE80)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_29_P0_REG                   (0x0000EE84)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_30_P0_REG                   (0x0000EE88)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_31_P0_REG                   (0x0000EE8C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_32_P0_REG                   (0x0000EE90)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_33_P0_REG                   (0x0000EE94)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_34_P0_REG                   (0x0000EE98)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_35_P0_REG                   (0x0000EE9C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_36_P0_REG                   (0x0000EEA0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_37_P0_REG                   (0x0000EEA4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_38_P0_REG                   (0x0000EEA8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_39_P0_REG                   (0x0000EEAC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_40_P0_REG                   (0x0000EEB0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_41_P0_REG                   (0x0000EEB4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_42_P0_REG                   (0x0000EEB8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_43_P0_REG                   (0x0000EEBC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_44_P0_REG                   (0x0000EEC0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_45_P0_REG                   (0x0000EEC4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_46_P0_REG                   (0x0000EEC8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_47_P0_REG                   (0x0000EECC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_48_P0_REG                   (0x0000EED0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_49_P0_REG                   (0x0000EED4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_50_P0_REG                   (0x0000EED8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_51_P0_REG                   (0x0000EEDC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_52_P0_REG                   (0x0000EEE0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_53_P0_REG                   (0x0000EEE4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_54_P0_REG                   (0x0000EEE8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_55_P0_REG                   (0x0000EEEC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_56_P0_REG                   (0x0000EEF0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_57_P0_REG                   (0x0000EEF4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_58_P0_REG                   (0x0000EEF8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_59_P0_REG                   (0x0000EEFC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_60_P0_REG                   (0x0000EF00)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_61_P0_REG                   (0x0000EF04)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_62_P0_REG                   (0x0000EF08)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_63_P0_REG                   (0x0000EF0C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_64_P0_REG                   (0x0000EF10)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_65_P0_REG                   (0x0000EF14)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_66_P0_REG                   (0x0000EF18)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_67_P0_REG                   (0x0000EF1C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_68_P0_REG                   (0x0000EF20)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_69_P0_REG                   (0x0000EF24)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_70_P0_REG                   (0x0000EF28)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_71_P0_REG                   (0x0000EF2C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_72_P0_REG                   (0x0000EF30)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_73_P0_REG                   (0x0000EF34)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_74_P0_REG                   (0x0000EF38)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_75_P0_REG                   (0x0000EF3C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG             (0x0000EF40)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_1_P0_REG             (0x0000EF44)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_2_P0_REG             (0x0000EF48)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_3_P0_REG             (0x0000EF4C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_4_P0_REG             (0x0000EF50)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_5_P0_REG             (0x0000EF54)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_6_P0_REG             (0x0000EF58)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_7_P0_REG             (0x0000EF5C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_8_P0_REG             (0x0000EF60)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_9_P0_REG             (0x0000EF64)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_10_P0_REG            (0x0000EF68)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_11_P0_REG            (0x0000EF6C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_12_P0_REG            (0x0000EF70)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_13_P0_REG            (0x0000EF74)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_14_P0_REG            (0x0000EF78)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_15_P0_REG            (0x0000EF7C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_16_P0_REG            (0x0000EF80)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_17_P0_REG            (0x0000EF84)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_18_P0_REG            (0x0000EF88)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_19_P0_REG            (0x0000EF8C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_20_P0_REG            (0x0000EF90)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_21_P0_REG            (0x0000EF94)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_22_P0_REG            (0x0000EF98)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_23_P0_REG            (0x0000EF9C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_24_P0_REG            (0x0000EFA0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_25_P0_REG            (0x0000EFA4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_26_P0_REG            (0x0000EFA8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_27_P0_REG            (0x0000EFAC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_28_P0_REG            (0x0000EFB0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_29_P0_REG            (0x0000EFB4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_30_P0_REG            (0x0000EFB8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_31_P0_REG            (0x0000EFBC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_32_P0_REG            (0x0000EFC0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_33_P0_REG            (0x0000EFC4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_34_P0_REG            (0x0000EFC8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_35_P0_REG            (0x0000EFCC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_36_P0_REG            (0x0000EFD0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_37_P0_REG            (0x0000EFD4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_38_P0_REG            (0x0000EFD8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_39_P0_REG            (0x0000EFDC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_40_P0_REG            (0x0000EFE0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_41_P0_REG            (0x0000EFE4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_42_P0_REG            (0x0000EFE8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_43_P0_REG            (0x0000EFEC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_44_P0_REG            (0x0000EFF0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_45_P0_REG            (0x0000EFF4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_46_P0_REG            (0x0000EFF8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_STORAGE_VALUES_47_P0_REG            (0x0000EFFC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_STORAGE_VALUES_0_P0_REG
#pragma pack(pop)
#endif
