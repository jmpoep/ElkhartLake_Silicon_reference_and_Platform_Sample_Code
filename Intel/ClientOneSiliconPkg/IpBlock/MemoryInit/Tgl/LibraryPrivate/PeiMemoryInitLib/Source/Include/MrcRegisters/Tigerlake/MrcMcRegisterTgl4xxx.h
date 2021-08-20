#ifndef __MrcMcRegisterTgl4xxx_h__
#define __MrcMcRegisterTgl4xxx_h__
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


#define MC0_CH0_CR_TC_PRE_REG                                          (0x00004000)

  #define MC0_CH0_CR_TC_PRE_tRP_OFF                                    ( 0)
  #define MC0_CH0_CR_TC_PRE_tRP_WID                                    ( 7)
  #define MC0_CH0_CR_TC_PRE_tRP_MSK                                    (0x0000007F)
  #define MC0_CH0_CR_TC_PRE_tRP_MIN                                    (0)
  #define MC0_CH0_CR_TC_PRE_tRP_MAX                                    (127) // 0x0000007F
  #define MC0_CH0_CR_TC_PRE_tRP_DEF                                    (0x00000008)
  #define MC0_CH0_CR_TC_PRE_tRP_HSH                                    (0x47004000)

  #define MC0_CH0_CR_TC_PRE_tRPab_ext_OFF                              ( 7)
  #define MC0_CH0_CR_TC_PRE_tRPab_ext_WID                              ( 4)
  #define MC0_CH0_CR_TC_PRE_tRPab_ext_MSK                              (0x00000780)
  #define MC0_CH0_CR_TC_PRE_tRPab_ext_MIN                              (0)
  #define MC0_CH0_CR_TC_PRE_tRPab_ext_MAX                              (15) // 0x0000000F
  #define MC0_CH0_CR_TC_PRE_tRPab_ext_DEF                              (0x00000000)
  #define MC0_CH0_CR_TC_PRE_tRPab_ext_HSH                              (0x440E4000)

  #define MC0_CH0_CR_TC_PRE_tRDPRE_OFF                                 (11)
  #define MC0_CH0_CR_TC_PRE_tRDPRE_WID                                 ( 6)
  #define MC0_CH0_CR_TC_PRE_tRDPRE_MSK                                 (0x0001F800)
  #define MC0_CH0_CR_TC_PRE_tRDPRE_MIN                                 (0)
  #define MC0_CH0_CR_TC_PRE_tRDPRE_MAX                                 (63) // 0x0000003F
  #define MC0_CH0_CR_TC_PRE_tRDPRE_DEF                                 (0x00000006)
  #define MC0_CH0_CR_TC_PRE_tRDPRE_HSH                                 (0x46164000)

  #define MC0_CH0_CR_TC_PRE_tPPD_OFF                                   (17)
  #define MC0_CH0_CR_TC_PRE_tPPD_WID                                   ( 4)
  #define MC0_CH0_CR_TC_PRE_tPPD_MSK                                   (0x001E0000)
  #define MC0_CH0_CR_TC_PRE_tPPD_MIN                                   (0)
  #define MC0_CH0_CR_TC_PRE_tPPD_MAX                                   (15) // 0x0000000F
  #define MC0_CH0_CR_TC_PRE_tPPD_DEF                                   (0x00000004)
  #define MC0_CH0_CR_TC_PRE_tPPD_HSH                                   (0x44224000)

  #define MC0_CH0_CR_TC_PRE_tWRPRE_OFF                                 (21)
  #define MC0_CH0_CR_TC_PRE_tWRPRE_WID                                 ( 9)
  #define MC0_CH0_CR_TC_PRE_tWRPRE_MSK                                 (0x3FE00000)
  #define MC0_CH0_CR_TC_PRE_tWRPRE_MIN                                 (0)
  #define MC0_CH0_CR_TC_PRE_tWRPRE_MAX                                 (511) // 0x000001FF
  #define MC0_CH0_CR_TC_PRE_tWRPRE_DEF                                 (0x00000018)
  #define MC0_CH0_CR_TC_PRE_tWRPRE_HSH                                 (0x492A4000)

  #define MC0_CH0_CR_TC_PRE_tRAS_OFF                                   (33)
  #define MC0_CH0_CR_TC_PRE_tRAS_WID                                   ( 8)
  #define MC0_CH0_CR_TC_PRE_tRAS_MSK                                   (0x000001FE00000000ULL)
  #define MC0_CH0_CR_TC_PRE_tRAS_MIN                                   (0)
  #define MC0_CH0_CR_TC_PRE_tRAS_MAX                                   (255) // 0x000000FF
  #define MC0_CH0_CR_TC_PRE_tRAS_DEF                                   (0x0000001C)
  #define MC0_CH0_CR_TC_PRE_tRAS_HSH                                   (0x48424000)

  #define MC0_CH0_CR_TC_PRE_tRCD_OFF                                   (41)
  #define MC0_CH0_CR_TC_PRE_tRCD_WID                                   ( 7)
  #define MC0_CH0_CR_TC_PRE_tRCD_MSK                                   (0x0000FE0000000000ULL)
  #define MC0_CH0_CR_TC_PRE_tRCD_MIN                                   (0)
  #define MC0_CH0_CR_TC_PRE_tRCD_MAX                                   (127) // 0x0000007F
  #define MC0_CH0_CR_TC_PRE_tRCD_DEF                                   (0x00000008)
  #define MC0_CH0_CR_TC_PRE_tRCD_HSH                                   (0x47524000)

#define MC0_CH0_CR_TC_ACT_REG                                          (0x00004008)

  #define MC0_CH0_CR_TC_ACT_tFAW_OFF                                   ( 0)
  #define MC0_CH0_CR_TC_ACT_tFAW_WID                                   ( 8)
  #define MC0_CH0_CR_TC_ACT_tFAW_MSK                                   (0x000000FF)
  #define MC0_CH0_CR_TC_ACT_tFAW_MIN                                   (0)
  #define MC0_CH0_CR_TC_ACT_tFAW_MAX                                   (255) // 0x000000FF
  #define MC0_CH0_CR_TC_ACT_tFAW_DEF                                   (0x00000010)
  #define MC0_CH0_CR_TC_ACT_tFAW_HSH                                   (0x08004008)

  #define MC0_CH0_CR_TC_ACT_tRRD_sg_OFF                                ( 8)
  #define MC0_CH0_CR_TC_ACT_tRRD_sg_WID                                ( 6)
  #define MC0_CH0_CR_TC_ACT_tRRD_sg_MSK                                (0x00003F00)
  #define MC0_CH0_CR_TC_ACT_tRRD_sg_MIN                                (0)
  #define MC0_CH0_CR_TC_ACT_tRRD_sg_MAX                                (63) // 0x0000003F
  #define MC0_CH0_CR_TC_ACT_tRRD_sg_DEF                                (0x00000004)
  #define MC0_CH0_CR_TC_ACT_tRRD_sg_HSH                                (0x06104008)

  #define MC0_CH0_CR_TC_ACT_tRRD_dg_OFF                                (14)
  #define MC0_CH0_CR_TC_ACT_tRRD_dg_WID                                ( 6)
  #define MC0_CH0_CR_TC_ACT_tRRD_dg_MSK                                (0x000FC000)
  #define MC0_CH0_CR_TC_ACT_tRRD_dg_MIN                                (0)
  #define MC0_CH0_CR_TC_ACT_tRRD_dg_MAX                                (63) // 0x0000003F
  #define MC0_CH0_CR_TC_ACT_tRRD_dg_DEF                                (0x00000004)
  #define MC0_CH0_CR_TC_ACT_tRRD_dg_HSH                                (0x061C4008)

  #define MC0_CH0_CR_TC_ACT_derating_ext_OFF                           (20)
  #define MC0_CH0_CR_TC_ACT_derating_ext_WID                           ( 3)
  #define MC0_CH0_CR_TC_ACT_derating_ext_MSK                           (0x00700000)
  #define MC0_CH0_CR_TC_ACT_derating_ext_MIN                           (0)
  #define MC0_CH0_CR_TC_ACT_derating_ext_MAX                           (7) // 0x00000007
  #define MC0_CH0_CR_TC_ACT_derating_ext_DEF                           (0x00000002)
  #define MC0_CH0_CR_TC_ACT_derating_ext_HSH                           (0x03284008)

#define MC0_CH0_CR_TC_RDRD_REG                                         (0x0000400C)

  #define MC0_CH0_CR_TC_RDRD_tRDRD_sg_OFF                              ( 0)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_sg_WID                              ( 6)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_sg_MSK                              (0x0000003F)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_sg_MIN                              (0)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_sg_MAX                              (63) // 0x0000003F
  #define MC0_CH0_CR_TC_RDRD_tRDRD_sg_DEF                              (0x00000004)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_sg_HSH                              (0x0600400C)

  #define MC0_CH0_CR_TC_RDRD_tRDRD_dg_OFF                              ( 8)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dg_WID                              ( 6)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dg_MSK                              (0x00003F00)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dg_MIN                              (0)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dg_MAX                              (63) // 0x0000003F
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dg_DEF                              (0x00000004)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dg_HSH                              (0x0610400C)

  #define MC0_CH0_CR_TC_RDRD_tRDRD_dr_OFF                              (16)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dr_WID                              ( 7)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dr_MSK                              (0x007F0000)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dr_MIN                              (0)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dr_MAX                              (127) // 0x0000007F
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dr_DEF                              (0x00000004)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dr_HSH                              (0x0720400C)

  #define MC0_CH0_CR_TC_RDRD_tRDRD_dd_OFF                              (24)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dd_WID                              ( 7)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dd_MSK                              (0x7F000000)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dd_MIN                              (0)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dd_MAX                              (127) // 0x0000007F
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dd_DEF                              (0x00000004)
  #define MC0_CH0_CR_TC_RDRD_tRDRD_dd_HSH                              (0x0730400C)

#define MC0_CH0_CR_TC_RDWR_REG                                         (0x00004010)

  #define MC0_CH0_CR_TC_RDWR_tRDWR_sg_OFF                              ( 0)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_sg_WID                              ( 7)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_sg_MSK                              (0x0000007F)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_sg_MIN                              (0)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_sg_MAX                              (127) // 0x0000007F
  #define MC0_CH0_CR_TC_RDWR_tRDWR_sg_DEF                              (0x00000004)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_sg_HSH                              (0x07004010)

  #define MC0_CH0_CR_TC_RDWR_tRDWR_dg_OFF                              ( 8)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dg_WID                              ( 7)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dg_MSK                              (0x00007F00)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dg_MIN                              (0)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dg_MAX                              (127) // 0x0000007F
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dg_DEF                              (0x00000004)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dg_HSH                              (0x07104010)

  #define MC0_CH0_CR_TC_RDWR_tRDWR_dr_OFF                              (16)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dr_WID                              ( 7)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dr_MSK                              (0x007F0000)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dr_MIN                              (0)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dr_MAX                              (127) // 0x0000007F
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dr_DEF                              (0x00000004)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dr_HSH                              (0x07204010)

  #define MC0_CH0_CR_TC_RDWR_tRDWR_dd_OFF                              (24)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dd_WID                              ( 7)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dd_MSK                              (0x7F000000)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dd_MIN                              (0)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dd_MAX                              (127) // 0x0000007F
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dd_DEF                              (0x00000004)
  #define MC0_CH0_CR_TC_RDWR_tRDWR_dd_HSH                              (0x07304010)

#define MC0_CH0_CR_TC_WRRD_REG                                         (0x00004014)

  #define MC0_CH0_CR_TC_WRRD_tWRRD_sg_OFF                              ( 0)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_sg_WID                              ( 8)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_sg_MSK                              (0x000000FF)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_sg_MIN                              (0)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_sg_MAX                              (255) // 0x000000FF
  #define MC0_CH0_CR_TC_WRRD_tWRRD_sg_DEF                              (0x00000004)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_sg_HSH                              (0x08004014)

  #define MC0_CH0_CR_TC_WRRD_tWRRD_dg_OFF                              ( 8)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dg_WID                              ( 8)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dg_MSK                              (0x0000FF00)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dg_MIN                              (0)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dg_MAX                              (255) // 0x000000FF
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dg_DEF                              (0x00000004)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dg_HSH                              (0x08104014)

  #define MC0_CH0_CR_TC_WRRD_tWRRD_dr_OFF                              (16)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dr_WID                              ( 6)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dr_MSK                              (0x003F0000)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dr_MIN                              (0)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dr_MAX                              (63) // 0x0000003F
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dr_DEF                              (0x00000004)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dr_HSH                              (0x06204014)

  #define MC0_CH0_CR_TC_WRRD_tWRRD_dd_OFF                              (24)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dd_WID                              ( 6)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dd_MSK                              (0x3F000000)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dd_MIN                              (0)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dd_MAX                              (63) // 0x0000003F
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dd_DEF                              (0x00000004)
  #define MC0_CH0_CR_TC_WRRD_tWRRD_dd_HSH                              (0x06304014)

#define MC0_CH0_CR_TC_WRWR_REG                                         (0x00004018)

  #define MC0_CH0_CR_TC_WRWR_tWRWR_sg_OFF                              ( 0)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_sg_WID                              ( 6)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_sg_MSK                              (0x0000003F)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_sg_MIN                              (0)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_sg_MAX                              (63) // 0x0000003F
  #define MC0_CH0_CR_TC_WRWR_tWRWR_sg_DEF                              (0x00000004)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_sg_HSH                              (0x06004018)

  #define MC0_CH0_CR_TC_WRWR_tWRWR_dg_OFF                              ( 8)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dg_WID                              ( 6)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dg_MSK                              (0x00003F00)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dg_MIN                              (0)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dg_MAX                              (63) // 0x0000003F
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dg_DEF                              (0x00000004)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dg_HSH                              (0x06104018)

  #define MC0_CH0_CR_TC_WRWR_tWRWR_dr_OFF                              (16)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dr_WID                              ( 6)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dr_MSK                              (0x003F0000)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dr_MIN                              (0)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dr_MAX                              (63) // 0x0000003F
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dr_DEF                              (0x00000004)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dr_HSH                              (0x06204018)

  #define MC0_CH0_CR_TC_WRWR_tWRWR_dd_OFF                              (24)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dd_WID                              ( 7)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dd_MSK                              (0x7F000000)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dd_MIN                              (0)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dd_MAX                              (127) // 0x0000007F
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dd_DEF                              (0x00000004)
  #define MC0_CH0_CR_TC_WRWR_tWRWR_dd_HSH                              (0x07304018)

#define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_REG                            (0x00004020)

  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_0_latency_OFF           ( 0)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_0_latency_WID           ( 8)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_0_latency_MSK           (0x000000FF)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_0_latency_MIN           (0)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_0_latency_MAX           (255) // 0x000000FF
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_0_latency_DEF           (0x00000019)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_0_latency_HSH           (0x48004020)

  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_1_latency_OFF           ( 8)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_1_latency_WID           ( 8)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_1_latency_MSK           (0x0000FF00)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_1_latency_MIN           (0)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_1_latency_MAX           (255) // 0x000000FF
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_1_latency_DEF           (0x00000019)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_1_latency_HSH           (0x48104020)

  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_2_latency_OFF           (16)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_2_latency_WID           ( 8)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_2_latency_MSK           (0x00FF0000)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_2_latency_MIN           (0)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_2_latency_MAX           (255) // 0x000000FF
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_2_latency_DEF           (0x00000019)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_2_latency_HSH           (0x48204020)

  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_3_latency_OFF           (24)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_3_latency_WID           ( 8)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_3_latency_MSK           (0xFF000000)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_3_latency_MIN           (0)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_3_latency_MAX           (255) // 0x000000FF
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_3_latency_DEF           (0x00000019)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_3_latency_HSH           (0x48304020)

  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_4_latency_OFF           (32)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_4_latency_WID           ( 8)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_4_latency_MSK           (0x000000FF00000000ULL)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_4_latency_MIN           (0)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_4_latency_MAX           (255) // 0x000000FF
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_4_latency_DEF           (0x00000019)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_4_latency_HSH           (0x48404020)

  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_5_latency_OFF           (40)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_5_latency_WID           ( 8)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_5_latency_MSK           (0x0000FF0000000000ULL)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_5_latency_MIN           (0)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_5_latency_MAX           (255) // 0x000000FF
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_5_latency_DEF           (0x00000019)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_5_latency_HSH           (0x48504020)

  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_6_latency_OFF           (48)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_6_latency_WID           ( 8)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_6_latency_MSK           (0x00FF000000000000ULL)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_6_latency_MIN           (0)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_6_latency_MAX           (255) // 0x000000FF
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_6_latency_DEF           (0x00000019)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_6_latency_HSH           (0x48604020)

  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_7_latency_OFF           (56)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_7_latency_WID           ( 8)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_7_latency_MSK           (0xFF00000000000000ULL)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_7_latency_MIN           (0)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_7_latency_MAX           (255) // 0x000000FF
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_7_latency_DEF           (0x00000019)
  #define MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_7_latency_HSH           (0x48704020)

#define MC0_CH0_CR_SCHED_CBIT_REG                                      (0x00004028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_cas_OFF                        ( 0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_cas_WID                        ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_cas_MSK                        (0x00000001)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_cas_MIN                        (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_cas_MAX                        (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_cas_DEF                        (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_cas_HSH                        (0x01004028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_cas_OFF                     ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_cas_WID                     ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_cas_MSK                     (0x00000002)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_cas_MIN                     (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_cas_MAX                     (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_cas_DEF                     (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_cas_HSH                     (0x01024028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ras_OFF                        ( 2)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ras_WID                        ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ras_MSK                        (0x00000004)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ras_MIN                        (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ras_MAX                        (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ras_DEF                        (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ras_HSH                        (0x01044028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_ras_OFF                     ( 3)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_ras_WID                     ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_ras_MSK                     (0x00000008)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_ras_MIN                     (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_ras_MAX                     (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_ras_DEF                     (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_is_ras_HSH                     (0x01064028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_2c_byp_OFF                         ( 4)
  #define MC0_CH0_CR_SCHED_CBIT_dis_2c_byp_WID                         ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_2c_byp_MSK                         (0x00000010)
  #define MC0_CH0_CR_SCHED_CBIT_dis_2c_byp_MIN                         (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_2c_byp_MAX                         (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_2c_byp_DEF                         (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_2c_byp_HSH                         (0x01084028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_deprd_opt_OFF                      ( 5)
  #define MC0_CH0_CR_SCHED_CBIT_dis_deprd_opt_WID                      ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_deprd_opt_MSK                      (0x00000020)
  #define MC0_CH0_CR_SCHED_CBIT_dis_deprd_opt_MIN                      (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_deprd_opt_MAX                      (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_deprd_opt_DEF                      (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_deprd_opt_HSH                      (0x010A4028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_pt_it_OFF                          ( 6)
  #define MC0_CH0_CR_SCHED_CBIT_dis_pt_it_WID                          ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_pt_it_MSK                          (0x00000040)
  #define MC0_CH0_CR_SCHED_CBIT_dis_pt_it_MIN                          (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_pt_it_MAX                          (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_pt_it_DEF                          (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_pt_it_HSH                          (0x010C4028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_ring_OFF                     ( 7)
  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_ring_WID                     ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_ring_MSK                     (0x00000080)
  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_ring_MIN                     (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_ring_MAX                     (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_ring_DEF                     (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_ring_HSH                     (0x010E4028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_sa_OFF                       ( 8)
  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_sa_WID                       ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_sa_MSK                       (0x00000100)
  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_sa_MIN                       (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_sa_MAX                       (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_sa_DEF                       (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_prcnt_sa_HSH                       (0x01104028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_ph_OFF                        ( 9)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_ph_WID                        ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_ph_MSK                        (0x00000200)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_ph_MIN                        (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_ph_MAX                        (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_ph_DEF                        (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_ph_HSH                        (0x01124028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pe_OFF                        (10)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pe_WID                        ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pe_MSK                        (0x00000400)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pe_MIN                        (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pe_MAX                        (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pe_DEF                        (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pe_HSH                        (0x01144028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pm_OFF                        (11)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pm_WID                        ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pm_MSK                        (0x00000800)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pm_MIN                        (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pm_MAX                        (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pm_DEF                        (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_blkr_pm_HSH                        (0x01164028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_odt_OFF                            (12)
  #define MC0_CH0_CR_SCHED_CBIT_dis_odt_WID                            ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_odt_MSK                            (0x00001000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_odt_MIN                            (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_odt_MAX                            (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_odt_DEF                            (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_odt_HSH                            (0x01184028)

  #define MC0_CH0_CR_SCHED_CBIT_OE_alw_off_OFF                         (13)
  #define MC0_CH0_CR_SCHED_CBIT_OE_alw_off_WID                         ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_OE_alw_off_MSK                         (0x00002000)
  #define MC0_CH0_CR_SCHED_CBIT_OE_alw_off_MIN                         (0)
  #define MC0_CH0_CR_SCHED_CBIT_OE_alw_off_MAX                         (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_OE_alw_off_DEF                         (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_OE_alw_off_HSH                         (0x011A4028)

  #define MC0_CH0_CR_SCHED_CBIT_block_rpq_OFF                          (14)
  #define MC0_CH0_CR_SCHED_CBIT_block_rpq_WID                          ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_block_rpq_MSK                          (0x00004000)
  #define MC0_CH0_CR_SCHED_CBIT_block_rpq_MIN                          (0)
  #define MC0_CH0_CR_SCHED_CBIT_block_rpq_MAX                          (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_block_rpq_DEF                          (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_block_rpq_HSH                          (0x011C4028)

  #define MC0_CH0_CR_SCHED_CBIT_block_ipq_OFF                          (15)
  #define MC0_CH0_CR_SCHED_CBIT_block_ipq_WID                          ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_block_ipq_MSK                          (0x00008000)
  #define MC0_CH0_CR_SCHED_CBIT_block_ipq_MIN                          (0)
  #define MC0_CH0_CR_SCHED_CBIT_block_ipq_MAX                          (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_block_ipq_DEF                          (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_block_ipq_HSH                          (0x011E4028)

  #define MC0_CH0_CR_SCHED_CBIT_block_wpq_OFF                          (16)
  #define MC0_CH0_CR_SCHED_CBIT_block_wpq_WID                          ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_block_wpq_MSK                          (0x00010000)
  #define MC0_CH0_CR_SCHED_CBIT_block_wpq_MIN                          (0)
  #define MC0_CH0_CR_SCHED_CBIT_block_wpq_MAX                          (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_block_wpq_DEF                          (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_block_wpq_HSH                          (0x01204028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_zq_OFF                             (17)
  #define MC0_CH0_CR_SCHED_CBIT_dis_zq_WID                             ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_zq_MSK                             (0x00020000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_zq_MIN                             (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_zq_MAX                             (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_zq_DEF                             (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_zq_HSH                             (0x01224028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_tt_OFF                             (18)
  #define MC0_CH0_CR_SCHED_CBIT_dis_tt_WID                             ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_tt_MSK                             (0x00040000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_tt_MIN                             (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_tt_MAX                             (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_tt_DEF                             (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_tt_HSH                             (0x01244028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ref_OFF                        (19)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ref_WID                        ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ref_MSK                        (0x00080000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ref_MIN                        (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ref_MAX                        (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ref_DEF                        (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_opp_ref_HSH                        (0x01264028)

  #define MC0_CH0_CR_SCHED_CBIT_long_zq_OFF                            (20)
  #define MC0_CH0_CR_SCHED_CBIT_long_zq_WID                            ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_long_zq_MSK                            (0x00100000)
  #define MC0_CH0_CR_SCHED_CBIT_long_zq_MIN                            (0)
  #define MC0_CH0_CR_SCHED_CBIT_long_zq_MAX                            (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_long_zq_DEF                            (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_long_zq_HSH                            (0x01284028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_srx_zq_OFF                         (21)
  #define MC0_CH0_CR_SCHED_CBIT_dis_srx_zq_WID                         ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_srx_zq_MSK                         (0x00200000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_srx_zq_MIN                         (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_srx_zq_MAX                         (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_srx_zq_DEF                         (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_srx_zq_HSH                         (0x012A4028)

  #define MC0_CH0_CR_SCHED_CBIT_serialize_zq_OFF                       (22)
  #define MC0_CH0_CR_SCHED_CBIT_serialize_zq_WID                       ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_serialize_zq_MSK                       (0x00400000)
  #define MC0_CH0_CR_SCHED_CBIT_serialize_zq_MIN                       (0)
  #define MC0_CH0_CR_SCHED_CBIT_serialize_zq_MAX                       (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_serialize_zq_DEF                       (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_serialize_zq_HSH                       (0x012C4028)

  #define MC0_CH0_CR_SCHED_CBIT_zq_fast_exec_OFF                       (23)
  #define MC0_CH0_CR_SCHED_CBIT_zq_fast_exec_WID                       ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_zq_fast_exec_MSK                       (0x00800000)
  #define MC0_CH0_CR_SCHED_CBIT_zq_fast_exec_MIN                       (0)
  #define MC0_CH0_CR_SCHED_CBIT_zq_fast_exec_MAX                       (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_zq_fast_exec_DEF                       (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_zq_fast_exec_HSH                       (0x012E4028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_starved_read_rank_block_OFF        (24)
  #define MC0_CH0_CR_SCHED_CBIT_dis_starved_read_rank_block_WID        ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_starved_read_rank_block_MSK        (0x01000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_starved_read_rank_block_MIN        (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_starved_read_rank_block_MAX        (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_starved_read_rank_block_DEF        (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_starved_read_rank_block_HSH        (0x01304028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_idle_preempt_OFF                   (25)
  #define MC0_CH0_CR_SCHED_CBIT_dis_idle_preempt_WID                   ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_idle_preempt_MSK                   (0x02000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_idle_preempt_MIN                   (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_idle_preempt_MAX                   (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_idle_preempt_DEF                   (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_idle_preempt_HSH                   (0x01324028)

  #define MC0_CH0_CR_SCHED_CBIT_find_first_allocation_OFF              (26)
  #define MC0_CH0_CR_SCHED_CBIT_find_first_allocation_WID              ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_find_first_allocation_MSK              (0x04000000)
  #define MC0_CH0_CR_SCHED_CBIT_find_first_allocation_MIN              (0)
  #define MC0_CH0_CR_SCHED_CBIT_find_first_allocation_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_find_first_allocation_DEF              (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_find_first_allocation_HSH              (0x01344028)

  #define MC0_CH0_CR_SCHED_CBIT_duplicate_spid_rank_OFF                (27)
  #define MC0_CH0_CR_SCHED_CBIT_duplicate_spid_rank_WID                ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_duplicate_spid_rank_MSK                (0x08000000)
  #define MC0_CH0_CR_SCHED_CBIT_duplicate_spid_rank_MIN                (0)
  #define MC0_CH0_CR_SCHED_CBIT_duplicate_spid_rank_MAX                (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_duplicate_spid_rank_DEF                (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_duplicate_spid_rank_HSH                (0x01364028)

  #define MC0_CH0_CR_SCHED_CBIT_wio_merge_lpmode_2_3_OFF               (28)
  #define MC0_CH0_CR_SCHED_CBIT_wio_merge_lpmode_2_3_WID               ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_wio_merge_lpmode_2_3_MSK               (0x10000000)
  #define MC0_CH0_CR_SCHED_CBIT_wio_merge_lpmode_2_3_MIN               (0)
  #define MC0_CH0_CR_SCHED_CBIT_wio_merge_lpmode_2_3_MAX               (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_wio_merge_lpmode_2_3_DEF               (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_wio_merge_lpmode_2_3_HSH               (0x01384028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_write_gap_OFF                 (29)
  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_write_gap_WID                 ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_write_gap_MSK                 (0x20000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_write_gap_MIN                 (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_write_gap_MAX                 (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_write_gap_DEF                 (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_write_gap_HSH                 (0x013A4028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_read_gap_OFF                  (30)
  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_read_gap_WID                  ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_read_gap_MSK                  (0x40000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_read_gap_MIN                  (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_read_gap_MAX                  (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_read_gap_DEF                  (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_5cyc_read_gap_HSH                  (0x013C4028)

  #define MC0_CH0_CR_SCHED_CBIT_dis_clk_gate_OFF                       (31)
  #define MC0_CH0_CR_SCHED_CBIT_dis_clk_gate_WID                       ( 1)
  #define MC0_CH0_CR_SCHED_CBIT_dis_clk_gate_MSK                       (0x80000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_clk_gate_MIN                       (0)
  #define MC0_CH0_CR_SCHED_CBIT_dis_clk_gate_MAX                       (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_CBIT_dis_clk_gate_DEF                       (0x00000000)
  #define MC0_CH0_CR_SCHED_CBIT_dis_clk_gate_HSH                       (0x013E4028)

#define MC0_CH0_CR_SCHED_SECOND_CBIT_REG                               (0x0000402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_srx_mr4_OFF                 ( 0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_srx_mr4_WID                 ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_srx_mr4_MSK                 (0x00000001)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_srx_mr4_MIN                 (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_srx_mr4_MAX                 (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_srx_mr4_DEF                 (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_srx_mr4_HSH                 (0x0100402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ck_tristate_OFF             ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ck_tristate_WID             ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ck_tristate_MSK             (0x00000002)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ck_tristate_MIN             (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ck_tristate_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ck_tristate_DEF             (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ck_tristate_HSH             (0x0102402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_bus_retain_OFF              ( 3)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_bus_retain_WID              ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_bus_retain_MSK              (0x00000008)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_bus_retain_MIN              (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_bus_retain_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_bus_retain_DEF              (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_bus_retain_HSH              (0x0106402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_async_odt_OFF               ( 4)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_async_odt_WID               ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_async_odt_MSK               (0x00000010)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_async_odt_MIN               (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_async_odt_MAX               (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_async_odt_DEF               (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_async_odt_HSH               (0x0108402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_reset_OFF               ( 5)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_reset_WID               ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_reset_MSK               (0x00000020)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_reset_MIN               (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_reset_MAX               (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_reset_DEF               (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_reset_HSH               (0x010A402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_SPARE_CBIT_OFF                  ( 6)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_SPARE_CBIT_WID                  ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_SPARE_CBIT_MSK                  (0x00000040)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_SPARE_CBIT_MIN                  (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_SPARE_CBIT_MAX                  (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_SPARE_CBIT_DEF                  (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_SPARE_CBIT_HSH                  (0x010C402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_MRS_MR4_OFF             ( 7)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_MRS_MR4_WID             ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_MRS_MR4_MSK             (0x00000080)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_MRS_MR4_MIN             (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_MRS_MR4_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_MRS_MR4_DEF             (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_MRS_MR4_HSH             (0x010E402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_opp_ref_idle_delay_OFF      ( 8)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_opp_ref_idle_delay_WID      ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_opp_ref_idle_delay_MSK      (0x00000100)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_opp_ref_idle_delay_MIN      (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_opp_ref_idle_delay_MAX      (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_opp_ref_idle_delay_DEF      (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_opp_ref_idle_delay_HSH      (0x0110402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ignore_1st_trefi_OFF        ( 9)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ignore_1st_trefi_WID        ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ignore_1st_trefi_MSK        (0x00000200)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ignore_1st_trefi_MIN        (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ignore_1st_trefi_MAX        (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ignore_1st_trefi_DEF        (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ignore_1st_trefi_HSH        (0x0112402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_echo_mask_OFF                   (10)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_echo_mask_WID                   ( 9)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_echo_mask_MSK                   (0x0007FC00)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_echo_mask_MIN                   (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_echo_mask_MAX                   (511) // 0x000001FF
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_echo_mask_DEF                   (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_echo_mask_HSH                   (0x0914402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_early_go_OFF                (19)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_early_go_WID                ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_early_go_MSK                (0x00080000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_early_go_MIN                (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_early_go_MAX                (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_early_go_DEF                (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_early_go_HSH                (0x0126402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_new_wr_to_full_OFF          (20)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_new_wr_to_full_WID          ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_new_wr_to_full_MSK          (0x00100000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_new_wr_to_full_MIN          (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_new_wr_to_full_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_new_wr_to_full_DEF          (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_new_wr_to_full_HSH          (0x0128402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_drainless_SAGV_do_zq_OFF        (22)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_drainless_SAGV_do_zq_WID        ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_drainless_SAGV_do_zq_MSK        (0x00400000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_drainless_SAGV_do_zq_MIN        (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_drainless_SAGV_do_zq_MAX        (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_drainless_SAGV_do_zq_DEF        (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_drainless_SAGV_do_zq_HSH        (0x012C402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_do_temp_reading_after_drainless_SAGV_OFF (23)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_do_temp_reading_after_drainless_SAGV_WID ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_do_temp_reading_after_drainless_SAGV_MSK (0x00800000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_do_temp_reading_after_drainless_SAGV_MIN (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_do_temp_reading_after_drainless_SAGV_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_do_temp_reading_after_drainless_SAGV_DEF (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_do_temp_reading_after_drainless_SAGV_HSH (0x012E402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_ignore_refresh_between_SR_OFF   (24)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_ignore_refresh_between_SR_WID   ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_ignore_refresh_between_SR_MSK   (0x01000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_ignore_refresh_between_SR_MIN   (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_ignore_refresh_between_SR_MAX   (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_ignore_refresh_between_SR_DEF   (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_ignore_refresh_between_SR_HSH   (0x0130402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_DisWrActThrottleOnAnyRead_OFF   (25)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_DisWrActThrottleOnAnyRead_WID   ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_DisWrActThrottleOnAnyRead_MSK   (0x02000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_DisWrActThrottleOnAnyRead_MIN   (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_DisWrActThrottleOnAnyRead_MAX   (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_DisWrActThrottleOnAnyRead_DEF   (0x00000001)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_DisWrActThrottleOnAnyRead_HSH   (0x0132402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_enable_fdata_nak_OFF            (26)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_enable_fdata_nak_WID            ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_enable_fdata_nak_MSK            (0x04000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_enable_fdata_nak_MIN            (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_enable_fdata_nak_MAX            (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_enable_fdata_nak_DEF            (0x00000001)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_enable_fdata_nak_HSH            (0x0134402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_disable_wr_on_SAGV_exit_for_DCC_OFF (27)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_disable_wr_on_SAGV_exit_for_DCC_WID ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_disable_wr_on_SAGV_exit_for_DCC_MSK (0x08000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_disable_wr_on_SAGV_exit_for_DCC_MIN (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_disable_wr_on_SAGV_exit_for_DCC_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_disable_wr_on_SAGV_exit_for_DCC_DEF (0x00000001)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_disable_wr_on_SAGV_exit_for_DCC_HSH (0x0136402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_spare_Copy_OFF                  (29)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_spare_Copy_WID                  ( 3)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_spare_Copy_MSK                  (0xE0000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_spare_Copy_MIN                  (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_spare_Copy_MAX                  (7) // 0x00000007
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_spare_Copy_DEF                  (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_spare_Copy_HSH                  (0x033A402C)

#define MC0_CH0_CR_SCHED_SECOND_CBIT_A0_REG                            (0x0000402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_srx_mr4_A0_OFF              ( 0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_srx_mr4_A0_WID              ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_srx_mr4_A0_MSK              (0x00000001)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_srx_mr4_A0_MIN              (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_srx_mr4_A0_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_srx_mr4_A0_DEF              (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_srx_mr4_A0_HSH              (0x0100402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ck_tristate_A0_OFF          ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ck_tristate_A0_WID          ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ck_tristate_A0_MSK          (0x00000002)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ck_tristate_A0_MIN          (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ck_tristate_A0_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ck_tristate_A0_DEF          (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ck_tristate_A0_HSH          (0x0102402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_bus_retain_A0_OFF           ( 3)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_bus_retain_A0_WID           ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_bus_retain_A0_MSK           (0x00000008)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_bus_retain_A0_MIN           (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_bus_retain_A0_MAX           (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_bus_retain_A0_DEF           (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_bus_retain_A0_HSH           (0x0106402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_async_odt_A0_OFF            ( 4)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_async_odt_A0_WID            ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_async_odt_A0_MSK            (0x00000010)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_async_odt_A0_MIN            (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_async_odt_A0_MAX            (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_async_odt_A0_DEF            (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_async_odt_A0_HSH            (0x0108402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_reset_A0_OFF            ( 5)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_reset_A0_WID            ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_reset_A0_MSK            (0x00000020)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_reset_A0_MIN            (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_reset_A0_MAX            (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_reset_A0_DEF            (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_reset_A0_HSH            (0x010A402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_SPARE_CBIT_A0_OFF               ( 6)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_SPARE_CBIT_A0_WID               ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_SPARE_CBIT_A0_MSK               (0x00000040)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_SPARE_CBIT_A0_MIN               (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_SPARE_CBIT_A0_MAX               (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_SPARE_CBIT_A0_DEF               (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_SPARE_CBIT_A0_HSH               (0x010C402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_MRS_MR4_A0_OFF          ( 7)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_MRS_MR4_A0_WID          ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_MRS_MR4_A0_MSK          (0x00000080)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_MRS_MR4_A0_MIN          (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_MRS_MR4_A0_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_MRS_MR4_A0_DEF          (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_SRX_MRS_MR4_A0_HSH          (0x010E402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_opp_ref_idle_delay_A0_OFF   ( 8)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_opp_ref_idle_delay_A0_WID   ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_opp_ref_idle_delay_A0_MSK   (0x00000100)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_opp_ref_idle_delay_A0_MIN   (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_opp_ref_idle_delay_A0_MAX   (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_opp_ref_idle_delay_A0_DEF   (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_opp_ref_idle_delay_A0_HSH   (0x0110402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ignore_1st_trefi_A0_OFF     ( 9)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ignore_1st_trefi_A0_WID     ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ignore_1st_trefi_A0_MSK     (0x00000200)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ignore_1st_trefi_A0_MIN     (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ignore_1st_trefi_A0_MAX     (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ignore_1st_trefi_A0_DEF     (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_ignore_1st_trefi_A0_HSH     (0x0112402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_echo_mask_A0_OFF                (10)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_echo_mask_A0_WID                ( 9)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_echo_mask_A0_MSK                (0x0007FC00)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_echo_mask_A0_MIN                (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_echo_mask_A0_MAX                (511) // 0x000001FF
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_echo_mask_A0_DEF                (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_echo_mask_A0_HSH                (0x0914402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_early_go_A0_OFF             (19)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_early_go_A0_WID             ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_early_go_A0_MSK             (0x00080000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_early_go_A0_MIN             (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_early_go_A0_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_early_go_A0_DEF             (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_early_go_A0_HSH             (0x0126402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_new_wr_to_full_A0_OFF       (20)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_new_wr_to_full_A0_WID       ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_new_wr_to_full_A0_MSK       (0x00100000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_new_wr_to_full_A0_MIN       (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_new_wr_to_full_A0_MAX       (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_new_wr_to_full_A0_DEF       (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_dis_new_wr_to_full_A0_HSH       (0x0128402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_drainless_SAGV_do_zq_A0_OFF     (22)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_drainless_SAGV_do_zq_A0_WID     ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_drainless_SAGV_do_zq_A0_MSK     (0x00400000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_drainless_SAGV_do_zq_A0_MIN     (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_drainless_SAGV_do_zq_A0_MAX     (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_drainless_SAGV_do_zq_A0_DEF     (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_drainless_SAGV_do_zq_A0_HSH     (0x012C402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_do_temp_reading_after_drainless_SAGV_A0_OFF (23)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_do_temp_reading_after_drainless_SAGV_A0_WID ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_do_temp_reading_after_drainless_SAGV_A0_MSK (0x00800000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_do_temp_reading_after_drainless_SAGV_A0_MIN (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_do_temp_reading_after_drainless_SAGV_A0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_do_temp_reading_after_drainless_SAGV_A0_DEF (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_do_temp_reading_after_drainless_SAGV_A0_HSH (0x012E402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_ignore_refresh_between_SR_A0_OFF (24)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_ignore_refresh_between_SR_A0_WID ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_ignore_refresh_between_SR_A0_MSK (0x01000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_ignore_refresh_between_SR_A0_MIN (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_ignore_refresh_between_SR_A0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_ignore_refresh_between_SR_A0_DEF (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_ignore_refresh_between_SR_A0_HSH (0x0130402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_DisWrActThrottleOnAnyRead_A0_OFF (25)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_DisWrActThrottleOnAnyRead_A0_WID ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_DisWrActThrottleOnAnyRead_A0_MSK (0x02000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_DisWrActThrottleOnAnyRead_A0_MIN (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_DisWrActThrottleOnAnyRead_A0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_DisWrActThrottleOnAnyRead_A0_DEF (0x00000001)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_DisWrActThrottleOnAnyRead_A0_HSH (0x0132402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_enable_fdata_nak_A0_OFF         (26)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_enable_fdata_nak_A0_WID         ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_enable_fdata_nak_A0_MSK         (0x04000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_enable_fdata_nak_A0_MIN         (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_enable_fdata_nak_A0_MAX         (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_enable_fdata_nak_A0_DEF         (0x00000001)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_enable_fdata_nak_A0_HSH         (0x0134402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_disable_wr_on_SAGV_exit_for_DCC_A0_OFF (27)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_disable_wr_on_SAGV_exit_for_DCC_A0_WID ( 1)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_disable_wr_on_SAGV_exit_for_DCC_A0_MSK (0x08000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_disable_wr_on_SAGV_exit_for_DCC_A0_MIN (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_disable_wr_on_SAGV_exit_for_DCC_A0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_disable_wr_on_SAGV_exit_for_DCC_A0_DEF (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_disable_wr_on_SAGV_exit_for_DCC_A0_HSH (0x0136402C)

  #define MC0_CH0_CR_SCHED_SECOND_CBIT_spare_Copy_A0_OFF               (29)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_spare_Copy_A0_WID               ( 3)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_spare_Copy_A0_MSK               (0xE0000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_spare_Copy_A0_MIN               (0)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_spare_Copy_A0_MAX               (7) // 0x00000007
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_spare_Copy_A0_DEF               (0x00000000)
  #define MC0_CH0_CR_SCHED_SECOND_CBIT_spare_Copy_A0_HSH               (0x033A402C)

#define MC0_CH0_CR_DFT_MISC_REG                                        (0x00004030)

  #define MC0_CH0_CR_DFT_MISC_WDAR_OFF                                 ( 0)
  #define MC0_CH0_CR_DFT_MISC_WDAR_WID                                 ( 1)
  #define MC0_CH0_CR_DFT_MISC_WDAR_MSK                                 (0x00000001)
  #define MC0_CH0_CR_DFT_MISC_WDAR_MIN                                 (0)
  #define MC0_CH0_CR_DFT_MISC_WDAR_MAX                                 (1) // 0x00000001
  #define MC0_CH0_CR_DFT_MISC_WDAR_DEF                                 (0x00000000)
  #define MC0_CH0_CR_DFT_MISC_WDAR_HSH                                 (0x01004030)

  #define MC0_CH0_CR_DFT_MISC_WDB_Block_En_OFF                         ( 1)
  #define MC0_CH0_CR_DFT_MISC_WDB_Block_En_WID                         ( 1)
  #define MC0_CH0_CR_DFT_MISC_WDB_Block_En_MSK                         (0x00000002)
  #define MC0_CH0_CR_DFT_MISC_WDB_Block_En_MIN                         (0)
  #define MC0_CH0_CR_DFT_MISC_WDB_Block_En_MAX                         (1) // 0x00000001
  #define MC0_CH0_CR_DFT_MISC_WDB_Block_En_DEF                         (0x00000000)
  #define MC0_CH0_CR_DFT_MISC_WDB_Block_En_HSH                         (0x01024030)

  #define MC0_CH0_CR_DFT_MISC_isolate_data_return_OFF                  ( 4)
  #define MC0_CH0_CR_DFT_MISC_isolate_data_return_WID                  ( 1)
  #define MC0_CH0_CR_DFT_MISC_isolate_data_return_MSK                  (0x00000010)
  #define MC0_CH0_CR_DFT_MISC_isolate_data_return_MIN                  (0)
  #define MC0_CH0_CR_DFT_MISC_isolate_data_return_MAX                  (1) // 0x00000001
  #define MC0_CH0_CR_DFT_MISC_isolate_data_return_DEF                  (0x00000000)
  #define MC0_CH0_CR_DFT_MISC_isolate_data_return_HSH                  (0x01084030)

  #define MC0_CH0_CR_DFT_MISC_dft_block_enable_OFF                     (17)
  #define MC0_CH0_CR_DFT_MISC_dft_block_enable_WID                     ( 1)
  #define MC0_CH0_CR_DFT_MISC_dft_block_enable_MSK                     (0x00020000)
  #define MC0_CH0_CR_DFT_MISC_dft_block_enable_MIN                     (0)
  #define MC0_CH0_CR_DFT_MISC_dft_block_enable_MAX                     (1) // 0x00000001
  #define MC0_CH0_CR_DFT_MISC_dft_block_enable_DEF                     (0x00000000)
  #define MC0_CH0_CR_DFT_MISC_dft_block_enable_HSH                     (0x01224030)

  #define MC0_CH0_CR_DFT_MISC_SAM_overloading_OFF                      (18)
  #define MC0_CH0_CR_DFT_MISC_SAM_overloading_WID                      ( 3)
  #define MC0_CH0_CR_DFT_MISC_SAM_overloading_MSK                      (0x001C0000)
  #define MC0_CH0_CR_DFT_MISC_SAM_overloading_MIN                      (0)
  #define MC0_CH0_CR_DFT_MISC_SAM_overloading_MAX                      (7) // 0x00000007
  #define MC0_CH0_CR_DFT_MISC_SAM_overloading_DEF                      (0x00000000)
  #define MC0_CH0_CR_DFT_MISC_SAM_overloading_HSH                      (0x03244030)

  #define MC0_CH0_CR_DFT_MISC_Stretch_mode_en_OFF                      (24)
  #define MC0_CH0_CR_DFT_MISC_Stretch_mode_en_WID                      ( 1)
  #define MC0_CH0_CR_DFT_MISC_Stretch_mode_en_MSK                      (0x01000000)
  #define MC0_CH0_CR_DFT_MISC_Stretch_mode_en_MIN                      (0)
  #define MC0_CH0_CR_DFT_MISC_Stretch_mode_en_MAX                      (1) // 0x00000001
  #define MC0_CH0_CR_DFT_MISC_Stretch_mode_en_DEF                      (0x00000000)
  #define MC0_CH0_CR_DFT_MISC_Stretch_mode_en_HSH                      (0x01304030)

  #define MC0_CH0_CR_DFT_MISC_STF_OFF                                  (25)
  #define MC0_CH0_CR_DFT_MISC_STF_WID                                  ( 5)
  #define MC0_CH0_CR_DFT_MISC_STF_MSK                                  (0x3E000000)
  #define MC0_CH0_CR_DFT_MISC_STF_MIN                                  (0)
  #define MC0_CH0_CR_DFT_MISC_STF_MAX                                  (31) // 0x0000001F
  #define MC0_CH0_CR_DFT_MISC_STF_DEF                                  (0x00000000)
  #define MC0_CH0_CR_DFT_MISC_STF_HSH                                  (0x05324030)

  #define MC0_CH0_CR_DFT_MISC_Stretch_delay_from_write_OFF             (30)
  #define MC0_CH0_CR_DFT_MISC_Stretch_delay_from_write_WID             ( 1)
  #define MC0_CH0_CR_DFT_MISC_Stretch_delay_from_write_MSK             (0x40000000)
  #define MC0_CH0_CR_DFT_MISC_Stretch_delay_from_write_MIN             (0)
  #define MC0_CH0_CR_DFT_MISC_Stretch_delay_from_write_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_DFT_MISC_Stretch_delay_from_write_DEF             (0x00000000)
  #define MC0_CH0_CR_DFT_MISC_Stretch_delay_from_write_HSH             (0x013C4030)

#define MC0_CH0_CR_SC_PCIT_REG                                         (0x00004034)

  #define MC0_CH0_CR_SC_PCIT_PCIT_OFF                                  ( 0)
  #define MC0_CH0_CR_SC_PCIT_PCIT_WID                                  ( 8)
  #define MC0_CH0_CR_SC_PCIT_PCIT_MSK                                  (0x000000FF)
  #define MC0_CH0_CR_SC_PCIT_PCIT_MIN                                  (0)
  #define MC0_CH0_CR_SC_PCIT_PCIT_MAX                                  (255) // 0x000000FF
  #define MC0_CH0_CR_SC_PCIT_PCIT_DEF                                  (0x00000040)
  #define MC0_CH0_CR_SC_PCIT_PCIT_HSH                                  (0x08004034)

  #define MC0_CH0_CR_SC_PCIT_PCIT_GT_OFF                               (16)
  #define MC0_CH0_CR_SC_PCIT_PCIT_GT_WID                               ( 8)
  #define MC0_CH0_CR_SC_PCIT_PCIT_GT_MSK                               (0x00FF0000)
  #define MC0_CH0_CR_SC_PCIT_PCIT_GT_MIN                               (0)
  #define MC0_CH0_CR_SC_PCIT_PCIT_GT_MAX                               (255) // 0x000000FF
  #define MC0_CH0_CR_SC_PCIT_PCIT_GT_DEF                               (0x00000000)
  #define MC0_CH0_CR_SC_PCIT_PCIT_GT_HSH                               (0x08204034)

#define MC0_CH0_CR_ECC_DFT_REG                                         (0x00004038)

  #define MC0_CH0_CR_ECC_DFT_ECC_Inject_OFF                            ( 0)
  #define MC0_CH0_CR_ECC_DFT_ECC_Inject_WID                            ( 3)
  #define MC0_CH0_CR_ECC_DFT_ECC_Inject_MSK                            (0x00000007)
  #define MC0_CH0_CR_ECC_DFT_ECC_Inject_MIN                            (0)
  #define MC0_CH0_CR_ECC_DFT_ECC_Inject_MAX                            (7) // 0x00000007
  #define MC0_CH0_CR_ECC_DFT_ECC_Inject_DEF                            (0x00000000)
  #define MC0_CH0_CR_ECC_DFT_ECC_Inject_HSH                            (0x03004038)

  #define MC0_CH0_CR_ECC_DFT_ECC_correction_disable_OFF                ( 4)
  #define MC0_CH0_CR_ECC_DFT_ECC_correction_disable_WID                ( 1)
  #define MC0_CH0_CR_ECC_DFT_ECC_correction_disable_MSK                (0x00000010)
  #define MC0_CH0_CR_ECC_DFT_ECC_correction_disable_MIN                (0)
  #define MC0_CH0_CR_ECC_DFT_ECC_correction_disable_MAX                (1) // 0x00000001
  #define MC0_CH0_CR_ECC_DFT_ECC_correction_disable_DEF                (0x00000000)
  #define MC0_CH0_CR_ECC_DFT_ECC_correction_disable_HSH                (0x01084038)

  #define MC0_CH0_CR_ECC_DFT_DIS_MCA_LOG_OFF                           ( 8)
  #define MC0_CH0_CR_ECC_DFT_DIS_MCA_LOG_WID                           ( 1)
  #define MC0_CH0_CR_ECC_DFT_DIS_MCA_LOG_MSK                           (0x00000100)
  #define MC0_CH0_CR_ECC_DFT_DIS_MCA_LOG_MIN                           (0)
  #define MC0_CH0_CR_ECC_DFT_DIS_MCA_LOG_MAX                           (1) // 0x00000001
  #define MC0_CH0_CR_ECC_DFT_DIS_MCA_LOG_DEF                           (0x00000000)
  #define MC0_CH0_CR_ECC_DFT_DIS_MCA_LOG_HSH                           (0x01104038)

  #define MC0_CH0_CR_ECC_DFT_DIS_PCH_EVENT_OFF                         ( 9)
  #define MC0_CH0_CR_ECC_DFT_DIS_PCH_EVENT_WID                         ( 1)
  #define MC0_CH0_CR_ECC_DFT_DIS_PCH_EVENT_MSK                         (0x00000200)
  #define MC0_CH0_CR_ECC_DFT_DIS_PCH_EVENT_MIN                         (0)
  #define MC0_CH0_CR_ECC_DFT_DIS_PCH_EVENT_MAX                         (1) // 0x00000001
  #define MC0_CH0_CR_ECC_DFT_DIS_PCH_EVENT_DEF                         (0x00000000)
  #define MC0_CH0_CR_ECC_DFT_DIS_PCH_EVENT_HSH                         (0x01124038)

  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_POISON_OFF                        (10)
  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_POISON_WID                        ( 1)
  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_POISON_MSK                        (0x00000400)
  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_POISON_MIN                        (0)
  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_POISON_MAX                        (1) // 0x00000001
  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_POISON_DEF                        (0x00000001)
  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_POISON_HSH                        (0x01144038)

  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_ERROR_OFF                         (11)
  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_ERROR_WID                         ( 1)
  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_ERROR_MSK                         (0x00000800)
  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_ERROR_MIN                         (0)
  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_ERROR_MAX                         (1) // 0x00000001
  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_ERROR_DEF                         (0x00000001)
  #define MC0_CH0_CR_ECC_DFT_DIS_RCH_ERROR_HSH                         (0x01164038)

  #define MC0_CH0_CR_ECC_DFT_ECC_trigger_OFF                           (16)
  #define MC0_CH0_CR_ECC_DFT_ECC_trigger_WID                           ( 2)
  #define MC0_CH0_CR_ECC_DFT_ECC_trigger_MSK                           (0x00030000)
  #define MC0_CH0_CR_ECC_DFT_ECC_trigger_MIN                           (0)
  #define MC0_CH0_CR_ECC_DFT_ECC_trigger_MAX                           (3) // 0x00000003
  #define MC0_CH0_CR_ECC_DFT_ECC_trigger_DEF                           (0x00000000)
  #define MC0_CH0_CR_ECC_DFT_ECC_trigger_HSH                           (0x02204038)

#define MC0_CH0_CR_PM_PDWN_CONFIG_REG                                  (0x00004040)

  #define MC0_CH0_CR_PM_PDWN_CONFIG_PDWN_idle_counter_OFF              ( 0)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_PDWN_idle_counter_WID              (12)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_PDWN_idle_counter_MSK              (0x00000FFF)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_PDWN_idle_counter_MIN              (0)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_PDWN_idle_counter_MAX              (4095) // 0x00000FFF
  #define MC0_CH0_CR_PM_PDWN_CONFIG_PDWN_idle_counter_DEF              (0x00000000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_PDWN_idle_counter_HSH              (0x0C004040)

  #define MC0_CH0_CR_PM_PDWN_CONFIG_APD_OFF                            (12)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_APD_WID                            ( 1)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_APD_MSK                            (0x00001000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_APD_MIN                            (0)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_APD_MAX                            (1) // 0x00000001
  #define MC0_CH0_CR_PM_PDWN_CONFIG_APD_DEF                            (0x00000000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_APD_HSH                            (0x01184040)

  #define MC0_CH0_CR_PM_PDWN_CONFIG_PPD_OFF                            (13)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_PPD_WID                            ( 1)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_PPD_MSK                            (0x00002000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_PPD_MIN                            (0)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_PPD_MAX                            (1) // 0x00000001
  #define MC0_CH0_CR_PM_PDWN_CONFIG_PPD_DEF                            (0x00000000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_PPD_HSH                            (0x011A4040)

  #define MC0_CH0_CR_PM_PDWN_CONFIG_Global_PD_OFF                      (15)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_Global_PD_WID                      ( 1)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_Global_PD_MSK                      (0x00008000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_Global_PD_MIN                      (0)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_Global_PD_MAX                      (1) // 0x00000001
  #define MC0_CH0_CR_PM_PDWN_CONFIG_Global_PD_DEF                      (0x00000000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_Global_PD_HSH                      (0x011E4040)

  #define MC0_CH0_CR_PM_PDWN_CONFIG_TT_idle_counter_OFF                (16)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_TT_idle_counter_WID                ( 8)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_TT_idle_counter_MSK                (0x00FF0000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_TT_idle_counter_MIN                (0)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_TT_idle_counter_MAX                (255) // 0x000000FF
  #define MC0_CH0_CR_PM_PDWN_CONFIG_TT_idle_counter_DEF                (0x00000000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_TT_idle_counter_HSH                (0x08204040)

  #define MC0_CH0_CR_PM_PDWN_CONFIG_dis_cke_tt_OFF                     (24)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_dis_cke_tt_WID                     ( 1)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_dis_cke_tt_MSK                     (0x01000000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_dis_cke_tt_MIN                     (0)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_dis_cke_tt_MAX                     (1) // 0x00000001
  #define MC0_CH0_CR_PM_PDWN_CONFIG_dis_cke_tt_DEF                     (0x00000000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_dis_cke_tt_HSH                     (0x01304040)

  #define MC0_CH0_CR_PM_PDWN_CONFIG_write_threshold_OFF                (25)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_write_threshold_WID                ( 6)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_write_threshold_MSK                (0x7E000000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_write_threshold_MIN                (0)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_write_threshold_MAX                (63) // 0x0000003F
  #define MC0_CH0_CR_PM_PDWN_CONFIG_write_threshold_DEF                (0x00000000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_write_threshold_HSH                (0x06324040)

  #define MC0_CH0_CR_PM_PDWN_CONFIG_allow_opp_ref_below_write_threhold_OFF (31)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_allow_opp_ref_below_write_threhold_WID ( 1)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_allow_opp_ref_below_write_threhold_MSK (0x80000000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_allow_opp_ref_below_write_threhold_MIN (0)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_allow_opp_ref_below_write_threhold_MAX (1) // 0x00000001
  #define MC0_CH0_CR_PM_PDWN_CONFIG_allow_opp_ref_below_write_threhold_DEF (0x00000000)
  #define MC0_CH0_CR_PM_PDWN_CONFIG_allow_opp_ref_below_write_threhold_HSH (0x013E4040)

#define MC0_CH0_CR_WMM_READ_CONFIG_REG                                 (0x00004044)

  #define MC0_CH0_CR_WMM_READ_CONFIG_Dis_Opp_rd_OFF                    ( 0)
  #define MC0_CH0_CR_WMM_READ_CONFIG_Dis_Opp_rd_WID                    ( 1)
  #define MC0_CH0_CR_WMM_READ_CONFIG_Dis_Opp_rd_MSK                    (0x00000001)
  #define MC0_CH0_CR_WMM_READ_CONFIG_Dis_Opp_rd_MIN                    (0)
  #define MC0_CH0_CR_WMM_READ_CONFIG_Dis_Opp_rd_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_WMM_READ_CONFIG_Dis_Opp_rd_DEF                    (0x00000000)
  #define MC0_CH0_CR_WMM_READ_CONFIG_Dis_Opp_rd_HSH                    (0x01004044)

  #define MC0_CH0_CR_WMM_READ_CONFIG_ACT_Enable_OFF                    ( 1)
  #define MC0_CH0_CR_WMM_READ_CONFIG_ACT_Enable_WID                    ( 1)
  #define MC0_CH0_CR_WMM_READ_CONFIG_ACT_Enable_MSK                    (0x00000002)
  #define MC0_CH0_CR_WMM_READ_CONFIG_ACT_Enable_MIN                    (0)
  #define MC0_CH0_CR_WMM_READ_CONFIG_ACT_Enable_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_WMM_READ_CONFIG_ACT_Enable_DEF                    (0x00000001)
  #define MC0_CH0_CR_WMM_READ_CONFIG_ACT_Enable_HSH                    (0x01024044)

  #define MC0_CH0_CR_WMM_READ_CONFIG_PRE_Enable_OFF                    ( 2)
  #define MC0_CH0_CR_WMM_READ_CONFIG_PRE_Enable_WID                    ( 1)
  #define MC0_CH0_CR_WMM_READ_CONFIG_PRE_Enable_MSK                    (0x00000004)
  #define MC0_CH0_CR_WMM_READ_CONFIG_PRE_Enable_MIN                    (0)
  #define MC0_CH0_CR_WMM_READ_CONFIG_PRE_Enable_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_WMM_READ_CONFIG_PRE_Enable_DEF                    (0x00000001)
  #define MC0_CH0_CR_WMM_READ_CONFIG_PRE_Enable_HSH                    (0x01044044)

  #define MC0_CH0_CR_WMM_READ_CONFIG_MAX_RPQ_CAS_OFF                   ( 3)
  #define MC0_CH0_CR_WMM_READ_CONFIG_MAX_RPQ_CAS_WID                   ( 4)
  #define MC0_CH0_CR_WMM_READ_CONFIG_MAX_RPQ_CAS_MSK                   (0x00000078)
  #define MC0_CH0_CR_WMM_READ_CONFIG_MAX_RPQ_CAS_MIN                   (0)
  #define MC0_CH0_CR_WMM_READ_CONFIG_MAX_RPQ_CAS_MAX                   (15) // 0x0000000F
  #define MC0_CH0_CR_WMM_READ_CONFIG_MAX_RPQ_CAS_DEF                   (0x00000008)
  #define MC0_CH0_CR_WMM_READ_CONFIG_MAX_RPQ_CAS_HSH                   (0x04064044)

#define MC0_CH0_CR_ECCERRLOG0_REG                                      (0x00004048)

  #define MC0_CH0_CR_ECCERRLOG0_CERRSTS_OFF                            ( 0)
  #define MC0_CH0_CR_ECCERRLOG0_CERRSTS_WID                            ( 1)
  #define MC0_CH0_CR_ECCERRLOG0_CERRSTS_MSK                            (0x00000001)
  #define MC0_CH0_CR_ECCERRLOG0_CERRSTS_MIN                            (0)
  #define MC0_CH0_CR_ECCERRLOG0_CERRSTS_MAX                            (1) // 0x00000001
  #define MC0_CH0_CR_ECCERRLOG0_CERRSTS_DEF                            (0x00000000)
  #define MC0_CH0_CR_ECCERRLOG0_CERRSTS_HSH                            (0x01004048)

  #define MC0_CH0_CR_ECCERRLOG0_MERRSTS_OFF                            ( 1)
  #define MC0_CH0_CR_ECCERRLOG0_MERRSTS_WID                            ( 1)
  #define MC0_CH0_CR_ECCERRLOG0_MERRSTS_MSK                            (0x00000002)
  #define MC0_CH0_CR_ECCERRLOG0_MERRSTS_MIN                            (0)
  #define MC0_CH0_CR_ECCERRLOG0_MERRSTS_MAX                            (1) // 0x00000001
  #define MC0_CH0_CR_ECCERRLOG0_MERRSTS_DEF                            (0x00000000)
  #define MC0_CH0_CR_ECCERRLOG0_MERRSTS_HSH                            (0x01024048)

  #define MC0_CH0_CR_ECCERRLOG0_ERRSYND_OFF                            (16)
  #define MC0_CH0_CR_ECCERRLOG0_ERRSYND_WID                            ( 8)
  #define MC0_CH0_CR_ECCERRLOG0_ERRSYND_MSK                            (0x00FF0000)
  #define MC0_CH0_CR_ECCERRLOG0_ERRSYND_MIN                            (0)
  #define MC0_CH0_CR_ECCERRLOG0_ERRSYND_MAX                            (255) // 0x000000FF
  #define MC0_CH0_CR_ECCERRLOG0_ERRSYND_DEF                            (0x00000000)
  #define MC0_CH0_CR_ECCERRLOG0_ERRSYND_HSH                            (0x08204048)

  #define MC0_CH0_CR_ECCERRLOG0_ERRCHUNK_OFF                           (24)
  #define MC0_CH0_CR_ECCERRLOG0_ERRCHUNK_WID                           ( 3)
  #define MC0_CH0_CR_ECCERRLOG0_ERRCHUNK_MSK                           (0x07000000)
  #define MC0_CH0_CR_ECCERRLOG0_ERRCHUNK_MIN                           (0)
  #define MC0_CH0_CR_ECCERRLOG0_ERRCHUNK_MAX                           (7) // 0x00000007
  #define MC0_CH0_CR_ECCERRLOG0_ERRCHUNK_DEF                           (0x00000000)
  #define MC0_CH0_CR_ECCERRLOG0_ERRCHUNK_HSH                           (0x03304048)

  #define MC0_CH0_CR_ECCERRLOG0_ERRRANK_OFF                            (27)
  #define MC0_CH0_CR_ECCERRLOG0_ERRRANK_WID                            ( 2)
  #define MC0_CH0_CR_ECCERRLOG0_ERRRANK_MSK                            (0x18000000)
  #define MC0_CH0_CR_ECCERRLOG0_ERRRANK_MIN                            (0)
  #define MC0_CH0_CR_ECCERRLOG0_ERRRANK_MAX                            (3) // 0x00000003
  #define MC0_CH0_CR_ECCERRLOG0_ERRRANK_DEF                            (0x00000000)
  #define MC0_CH0_CR_ECCERRLOG0_ERRRANK_HSH                            (0x02364048)

  #define MC0_CH0_CR_ECCERRLOG0_ERRBANK_OFF                            (29)
  #define MC0_CH0_CR_ECCERRLOG0_ERRBANK_WID                            ( 3)
  #define MC0_CH0_CR_ECCERRLOG0_ERRBANK_MSK                            (0xE0000000)
  #define MC0_CH0_CR_ECCERRLOG0_ERRBANK_MIN                            (0)
  #define MC0_CH0_CR_ECCERRLOG0_ERRBANK_MAX                            (7) // 0x00000007
  #define MC0_CH0_CR_ECCERRLOG0_ERRBANK_DEF                            (0x00000000)
  #define MC0_CH0_CR_ECCERRLOG0_ERRBANK_HSH                            (0x033A4048)

#define MC0_CH0_CR_ECCERRLOG1_REG                                      (0x0000404C)

  #define MC0_CH0_CR_ECCERRLOG1_ERRROW_OFF                             ( 0)
  #define MC0_CH0_CR_ECCERRLOG1_ERRROW_WID                             (18)
  #define MC0_CH0_CR_ECCERRLOG1_ERRROW_MSK                             (0x0003FFFF)
  #define MC0_CH0_CR_ECCERRLOG1_ERRROW_MIN                             (0)
  #define MC0_CH0_CR_ECCERRLOG1_ERRROW_MAX                             (262143) // 0x0003FFFF
  #define MC0_CH0_CR_ECCERRLOG1_ERRROW_DEF                             (0x00000000)
  #define MC0_CH0_CR_ECCERRLOG1_ERRROW_HSH                             (0x1200404C)

  #define MC0_CH0_CR_ECCERRLOG1_ERRCOL_OFF                             (18)
  #define MC0_CH0_CR_ECCERRLOG1_ERRCOL_WID                             (11)
  #define MC0_CH0_CR_ECCERRLOG1_ERRCOL_MSK                             (0x1FFC0000)
  #define MC0_CH0_CR_ECCERRLOG1_ERRCOL_MIN                             (0)
  #define MC0_CH0_CR_ECCERRLOG1_ERRCOL_MAX                             (2047) // 0x000007FF
  #define MC0_CH0_CR_ECCERRLOG1_ERRCOL_DEF                             (0x00000000)
  #define MC0_CH0_CR_ECCERRLOG1_ERRCOL_HSH                             (0x0B24404C)

  #define MC0_CH0_CR_ECCERRLOG1_ERRBANKGROUP_OFF                       (29)
  #define MC0_CH0_CR_ECCERRLOG1_ERRBANKGROUP_WID                       ( 2)
  #define MC0_CH0_CR_ECCERRLOG1_ERRBANKGROUP_MSK                       (0x60000000)
  #define MC0_CH0_CR_ECCERRLOG1_ERRBANKGROUP_MIN                       (0)
  #define MC0_CH0_CR_ECCERRLOG1_ERRBANKGROUP_MAX                       (3) // 0x00000003
  #define MC0_CH0_CR_ECCERRLOG1_ERRBANKGROUP_DEF                       (0x00000000)
  #define MC0_CH0_CR_ECCERRLOG1_ERRBANKGROUP_HSH                       (0x023A404C)

#define MC0_CH0_CR_ECCERRLOG1_A0_REG                                   (0x0000404C)

  #define MC0_CH0_CR_ECCERRLOG1_ERRROW_A0_OFF                          ( 0)
  #define MC0_CH0_CR_ECCERRLOG1_ERRROW_A0_WID                          (17)
  #define MC0_CH0_CR_ECCERRLOG1_ERRROW_A0_MSK                          (0x0001FFFF)
  #define MC0_CH0_CR_ECCERRLOG1_ERRROW_A0_MIN                          (0)
  #define MC0_CH0_CR_ECCERRLOG1_ERRROW_A0_MAX                          (131071) // 0x0001FFFF
  #define MC0_CH0_CR_ECCERRLOG1_ERRROW_A0_DEF                          (0x00000000)
  #define MC0_CH0_CR_ECCERRLOG1_ERRROW_A0_HSH                          (0x1100404C)

  #define MC0_CH0_CR_ECCERRLOG1_ERRCOL_A0_OFF                          (17)
  #define MC0_CH0_CR_ECCERRLOG1_ERRCOL_A0_WID                          (12)
  #define MC0_CH0_CR_ECCERRLOG1_ERRCOL_A0_MSK                          (0x1FFE0000)
  #define MC0_CH0_CR_ECCERRLOG1_ERRCOL_A0_MIN                          (0)
  #define MC0_CH0_CR_ECCERRLOG1_ERRCOL_A0_MAX                          (4095) // 0x00000FFF
  #define MC0_CH0_CR_ECCERRLOG1_ERRCOL_A0_DEF                          (0x00000000)
  #define MC0_CH0_CR_ECCERRLOG1_ERRCOL_A0_HSH                          (0x0C22404C)

  #define MC0_CH0_CR_ECCERRLOG1_ERRBANKGROUP_A0_OFF                    (29)
  #define MC0_CH0_CR_ECCERRLOG1_ERRBANKGROUP_A0_WID                    ( 2)
  #define MC0_CH0_CR_ECCERRLOG1_ERRBANKGROUP_A0_MSK                    (0x60000000)
  #define MC0_CH0_CR_ECCERRLOG1_ERRBANKGROUP_A0_MIN                    (0)
  #define MC0_CH0_CR_ECCERRLOG1_ERRBANKGROUP_A0_MAX                    (3) // 0x00000003
  #define MC0_CH0_CR_ECCERRLOG1_ERRBANKGROUP_A0_DEF                    (0x00000000)
  #define MC0_CH0_CR_ECCERRLOG1_ERRBANKGROUP_A0_HSH                    (0x023A404C)

#define MC0_CH0_CR_TC_PWRDN_REG                                        (0x00004050)

  #define MC0_CH0_CR_TC_PWRDN_tCKE_OFF                                 ( 0)
  #define MC0_CH0_CR_TC_PWRDN_tCKE_WID                                 ( 6)
  #define MC0_CH0_CR_TC_PWRDN_tCKE_MSK                                 (0x0000003F)
  #define MC0_CH0_CR_TC_PWRDN_tCKE_MIN                                 (0)
  #define MC0_CH0_CR_TC_PWRDN_tCKE_MAX                                 (63) // 0x0000003F
  #define MC0_CH0_CR_TC_PWRDN_tCKE_DEF                                 (0x00000004)
  #define MC0_CH0_CR_TC_PWRDN_tCKE_HSH                                 (0x46004050)

  #define MC0_CH0_CR_TC_PWRDN_tXP_OFF                                  ( 8)
  #define MC0_CH0_CR_TC_PWRDN_tXP_WID                                  ( 6)
  #define MC0_CH0_CR_TC_PWRDN_tXP_MSK                                  (0x00003F00)
  #define MC0_CH0_CR_TC_PWRDN_tXP_MIN                                  (0)
  #define MC0_CH0_CR_TC_PWRDN_tXP_MAX                                  (63) // 0x0000003F
  #define MC0_CH0_CR_TC_PWRDN_tXP_DEF                                  (0x00000004)
  #define MC0_CH0_CR_TC_PWRDN_tXP_HSH                                  (0x46104050)

  #define MC0_CH0_CR_TC_PWRDN_tXPDLL_OFF                               (16)
  #define MC0_CH0_CR_TC_PWRDN_tXPDLL_WID                               ( 6)
  #define MC0_CH0_CR_TC_PWRDN_tXPDLL_MSK                               (0x003F0000)
  #define MC0_CH0_CR_TC_PWRDN_tXPDLL_MIN                               (0)
  #define MC0_CH0_CR_TC_PWRDN_tXPDLL_MAX                               (63) // 0x0000003F
  #define MC0_CH0_CR_TC_PWRDN_tXPDLL_DEF                               (0x00000004)
  #define MC0_CH0_CR_TC_PWRDN_tXPDLL_HSH                               (0x46204050)

  #define MC0_CH0_CR_TC_PWRDN_tRDPDEN_OFF                              (24)
  #define MC0_CH0_CR_TC_PWRDN_tRDPDEN_WID                              ( 7)
  #define MC0_CH0_CR_TC_PWRDN_tRDPDEN_MSK                              (0x7F000000)
  #define MC0_CH0_CR_TC_PWRDN_tRDPDEN_MIN                              (0)
  #define MC0_CH0_CR_TC_PWRDN_tRDPDEN_MAX                              (127) // 0x0000007F
  #define MC0_CH0_CR_TC_PWRDN_tRDPDEN_DEF                              (0x00000004)
  #define MC0_CH0_CR_TC_PWRDN_tRDPDEN_HSH                              (0x47304050)

  #define MC0_CH0_CR_TC_PWRDN_tWRPDEN_OFF                              (32)
  #define MC0_CH0_CR_TC_PWRDN_tWRPDEN_WID                              ( 9)
  #define MC0_CH0_CR_TC_PWRDN_tWRPDEN_MSK                              (0x000001FF00000000ULL)
  #define MC0_CH0_CR_TC_PWRDN_tWRPDEN_MIN                              (0)
  #define MC0_CH0_CR_TC_PWRDN_tWRPDEN_MAX                              (511) // 0x000001FF
  #define MC0_CH0_CR_TC_PWRDN_tWRPDEN_DEF                              (0x00000004)
  #define MC0_CH0_CR_TC_PWRDN_tWRPDEN_HSH                              (0x49404050)

  #define MC0_CH0_CR_TC_PWRDN_tCSH_OFF                                 (41)
  #define MC0_CH0_CR_TC_PWRDN_tCSH_WID                                 ( 5)
  #define MC0_CH0_CR_TC_PWRDN_tCSH_MSK                                 (0x00003E0000000000ULL)
  #define MC0_CH0_CR_TC_PWRDN_tCSH_MIN                                 (0)
  #define MC0_CH0_CR_TC_PWRDN_tCSH_MAX                                 (31) // 0x0000001F
  #define MC0_CH0_CR_TC_PWRDN_tCSH_DEF                                 (0x00000004)
  #define MC0_CH0_CR_TC_PWRDN_tCSH_HSH                                 (0x45524050)

  #define MC0_CH0_CR_TC_PWRDN_tCSL_OFF                                 (46)
  #define MC0_CH0_CR_TC_PWRDN_tCSL_WID                                 ( 5)
  #define MC0_CH0_CR_TC_PWRDN_tCSL_MSK                                 (0x0007C00000000000ULL)
  #define MC0_CH0_CR_TC_PWRDN_tCSL_MIN                                 (0)
  #define MC0_CH0_CR_TC_PWRDN_tCSL_MAX                                 (31) // 0x0000001F
  #define MC0_CH0_CR_TC_PWRDN_tCSL_DEF                                 (0x00000004)
  #define MC0_CH0_CR_TC_PWRDN_tCSL_HSH                                 (0x455C4050)

  #define MC0_CH0_CR_TC_PWRDN_tCA2CS_OFF                               (51)
  #define MC0_CH0_CR_TC_PWRDN_tCA2CS_WID                               ( 5)
  #define MC0_CH0_CR_TC_PWRDN_tCA2CS_MSK                               (0x00F8000000000000ULL)
  #define MC0_CH0_CR_TC_PWRDN_tCA2CS_MIN                               (0)
  #define MC0_CH0_CR_TC_PWRDN_tCA2CS_MAX                               (31) // 0x0000001F
  #define MC0_CH0_CR_TC_PWRDN_tCA2CS_DEF                               (0x00000004)
  #define MC0_CH0_CR_TC_PWRDN_tCA2CS_HSH                               (0x45664050)

  #define MC0_CH0_CR_TC_PWRDN_tPRPDEN_OFF                              (56)
  #define MC0_CH0_CR_TC_PWRDN_tPRPDEN_WID                              ( 5)
  #define MC0_CH0_CR_TC_PWRDN_tPRPDEN_MSK                              (0x1F00000000000000ULL)
  #define MC0_CH0_CR_TC_PWRDN_tPRPDEN_MIN                              (0)
  #define MC0_CH0_CR_TC_PWRDN_tPRPDEN_MAX                              (31) // 0x0000001F
  #define MC0_CH0_CR_TC_PWRDN_tPRPDEN_DEF                              (0x00000001)
  #define MC0_CH0_CR_TC_PWRDN_tPRPDEN_HSH                              (0x45704050)

#define MC0_CH0_CR_TC_PWRDN_A0_REG                                     (0x00004050)

  #define MC0_CH0_CR_TC_PWRDN_tCKE_A0_OFF                              ( 0)
  #define MC0_CH0_CR_TC_PWRDN_tCKE_A0_WID                              ( 6)
  #define MC0_CH0_CR_TC_PWRDN_tCKE_A0_MSK                              (0x0000003F)
  #define MC0_CH0_CR_TC_PWRDN_tCKE_A0_MIN                              (0)
  #define MC0_CH0_CR_TC_PWRDN_tCKE_A0_MAX                              (63) // 0x0000003F
  #define MC0_CH0_CR_TC_PWRDN_tCKE_A0_DEF                              (0x00000004)
  #define MC0_CH0_CR_TC_PWRDN_tCKE_A0_HSH                              (0x46004050)

  #define MC0_CH0_CR_TC_PWRDN_tXP_A0_OFF                               ( 8)
  #define MC0_CH0_CR_TC_PWRDN_tXP_A0_WID                               ( 6)
  #define MC0_CH0_CR_TC_PWRDN_tXP_A0_MSK                               (0x00003F00)
  #define MC0_CH0_CR_TC_PWRDN_tXP_A0_MIN                               (0)
  #define MC0_CH0_CR_TC_PWRDN_tXP_A0_MAX                               (63) // 0x0000003F
  #define MC0_CH0_CR_TC_PWRDN_tXP_A0_DEF                               (0x00000004)
  #define MC0_CH0_CR_TC_PWRDN_tXP_A0_HSH                               (0x46104050)

  #define MC0_CH0_CR_TC_PWRDN_tXPDLL_A0_OFF                            (16)
  #define MC0_CH0_CR_TC_PWRDN_tXPDLL_A0_WID                            ( 6)
  #define MC0_CH0_CR_TC_PWRDN_tXPDLL_A0_MSK                            (0x003F0000)
  #define MC0_CH0_CR_TC_PWRDN_tXPDLL_A0_MIN                            (0)
  #define MC0_CH0_CR_TC_PWRDN_tXPDLL_A0_MAX                            (63) // 0x0000003F
  #define MC0_CH0_CR_TC_PWRDN_tXPDLL_A0_DEF                            (0x00000004)
  #define MC0_CH0_CR_TC_PWRDN_tXPDLL_A0_HSH                            (0x46204050)

  #define MC0_CH0_CR_TC_PWRDN_tPRPDEN_A0_OFF                           (22)
  #define MC0_CH0_CR_TC_PWRDN_tPRPDEN_A0_WID                           ( 2)
  #define MC0_CH0_CR_TC_PWRDN_tPRPDEN_A0_MSK                           (0x00C00000)
  #define MC0_CH0_CR_TC_PWRDN_tPRPDEN_A0_MIN                           (0)
  #define MC0_CH0_CR_TC_PWRDN_tPRPDEN_A0_MAX                           (3) // 0x00000003
  #define MC0_CH0_CR_TC_PWRDN_tPRPDEN_A0_DEF                           (0x00000001)
  #define MC0_CH0_CR_TC_PWRDN_tPRPDEN_A0_HSH                           (0x422C4050)

  #define MC0_CH0_CR_TC_PWRDN_tRDPDEN_A0_OFF                           (24)
  #define MC0_CH0_CR_TC_PWRDN_tRDPDEN_A0_WID                           ( 7)
  #define MC0_CH0_CR_TC_PWRDN_tRDPDEN_A0_MSK                           (0x7F000000)
  #define MC0_CH0_CR_TC_PWRDN_tRDPDEN_A0_MIN                           (0)
  #define MC0_CH0_CR_TC_PWRDN_tRDPDEN_A0_MAX                           (127) // 0x0000007F
  #define MC0_CH0_CR_TC_PWRDN_tRDPDEN_A0_DEF                           (0x00000004)
  #define MC0_CH0_CR_TC_PWRDN_tRDPDEN_A0_HSH                           (0x47304050)

  #define MC0_CH0_CR_TC_PWRDN_tWRPDEN_A0_OFF                           (32)
  #define MC0_CH0_CR_TC_PWRDN_tWRPDEN_A0_WID                           ( 9)
  #define MC0_CH0_CR_TC_PWRDN_tWRPDEN_A0_MSK                           (0x000001FF00000000ULL)
  #define MC0_CH0_CR_TC_PWRDN_tWRPDEN_A0_MIN                           (0)
  #define MC0_CH0_CR_TC_PWRDN_tWRPDEN_A0_MAX                           (511) // 0x000001FF
  #define MC0_CH0_CR_TC_PWRDN_tWRPDEN_A0_DEF                           (0x00000004)
  #define MC0_CH0_CR_TC_PWRDN_tWRPDEN_A0_HSH                           (0x49404050)

  #define MC0_CH0_CR_TC_PWRDN_tCSH_A0_OFF                              (41)
  #define MC0_CH0_CR_TC_PWRDN_tCSH_A0_WID                              ( 5)
  #define MC0_CH0_CR_TC_PWRDN_tCSH_A0_MSK                              (0x00003E0000000000ULL)
  #define MC0_CH0_CR_TC_PWRDN_tCSH_A0_MIN                              (0)
  #define MC0_CH0_CR_TC_PWRDN_tCSH_A0_MAX                              (31) // 0x0000001F
  #define MC0_CH0_CR_TC_PWRDN_tCSH_A0_DEF                              (0x00000004)
  #define MC0_CH0_CR_TC_PWRDN_tCSH_A0_HSH                              (0x45524050)

  #define MC0_CH0_CR_TC_PWRDN_tCSL_A0_OFF                              (46)
  #define MC0_CH0_CR_TC_PWRDN_tCSL_A0_WID                              ( 5)
  #define MC0_CH0_CR_TC_PWRDN_tCSL_A0_MSK                              (0x0007C00000000000ULL)
  #define MC0_CH0_CR_TC_PWRDN_tCSL_A0_MIN                              (0)
  #define MC0_CH0_CR_TC_PWRDN_tCSL_A0_MAX                              (31) // 0x0000001F
  #define MC0_CH0_CR_TC_PWRDN_tCSL_A0_DEF                              (0x00000004)
  #define MC0_CH0_CR_TC_PWRDN_tCSL_A0_HSH                              (0x455C4050)

  #define MC0_CH0_CR_TC_PWRDN_tCA2CS_A0_OFF                            (51)
  #define MC0_CH0_CR_TC_PWRDN_tCA2CS_A0_WID                            ( 5)
  #define MC0_CH0_CR_TC_PWRDN_tCA2CS_A0_MSK                            (0x00F8000000000000ULL)
  #define MC0_CH0_CR_TC_PWRDN_tCA2CS_A0_MIN                            (0)
  #define MC0_CH0_CR_TC_PWRDN_tCA2CS_A0_MAX                            (31) // 0x0000001F
  #define MC0_CH0_CR_TC_PWRDN_tCA2CS_A0_DEF                            (0x00000004)
  #define MC0_CH0_CR_TC_PWRDN_tCA2CS_A0_HSH                            (0x45664050)

#define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_RPQ_REG                         (0x00004058)

  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_RPQ_RPQ_disable_OFF           ( 0)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_RPQ_RPQ_disable_WID           (32)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_RPQ_RPQ_disable_MSK           (0xFFFFFFFF)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_RPQ_RPQ_disable_MIN           (0)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_RPQ_RPQ_disable_MAX           (4294967295) // 0xFFFFFFFF
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_RPQ_RPQ_disable_DEF           (0x00000000)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_RPQ_RPQ_disable_HSH           (0x20004058)

#define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_IPQ_REG                         (0x0000405C)

  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_IPQ_IPQ_disable_OFF           ( 0)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_IPQ_IPQ_disable_WID           (16)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_IPQ_IPQ_disable_MSK           (0x0000FFFF)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_IPQ_IPQ_disable_MIN           (0)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_IPQ_IPQ_disable_MAX           (65535) // 0x0000FFFF
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_IPQ_IPQ_disable_DEF           (0x00000000)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_IPQ_IPQ_disable_HSH           (0x1000405C)

#define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_WPQ_REG                         (0x00004060)

  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_WPQ_WPQ_disable_OFF           ( 0)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_WPQ_WPQ_disable_WID           (64)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_WPQ_WPQ_disable_MSK           (0xFFFFFFFFFFFFFFFFULL)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_WPQ_WPQ_disable_MIN           (0)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_WPQ_WPQ_disable_MAX           (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_WPQ_WPQ_disable_DEF           (0x00000000)
  #define MC0_CH0_CR_QUEUE_ENTRY_DISABLE_WPQ_WPQ_disable_HSH           (0x40004060)

#define MC0_CH0_CR_SC_WDBWM_REG                                        (0x00004068)

  #define MC0_CH0_CR_SC_WDBWM_WMM_entry_wm_OFF                         ( 0)
  #define MC0_CH0_CR_SC_WDBWM_WMM_entry_wm_WID                         ( 7)
  #define MC0_CH0_CR_SC_WDBWM_WMM_entry_wm_MSK                         (0x0000007F)
  #define MC0_CH0_CR_SC_WDBWM_WMM_entry_wm_MIN                         (0)
  #define MC0_CH0_CR_SC_WDBWM_WMM_entry_wm_MAX                         (127) // 0x0000007F
  #define MC0_CH0_CR_SC_WDBWM_WMM_entry_wm_DEF                         (0x00000038)
  #define MC0_CH0_CR_SC_WDBWM_WMM_entry_wm_HSH                         (0x47004068)

  #define MC0_CH0_CR_SC_WDBWM_WMM_exit_wm_OFF                          ( 8)
  #define MC0_CH0_CR_SC_WDBWM_WMM_exit_wm_WID                          ( 7)
  #define MC0_CH0_CR_SC_WDBWM_WMM_exit_wm_MSK                          (0x00007F00)
  #define MC0_CH0_CR_SC_WDBWM_WMM_exit_wm_MIN                          (0)
  #define MC0_CH0_CR_SC_WDBWM_WMM_exit_wm_MAX                          (127) // 0x0000007F
  #define MC0_CH0_CR_SC_WDBWM_WMM_exit_wm_DEF                          (0x00000030)
  #define MC0_CH0_CR_SC_WDBWM_WMM_exit_wm_HSH                          (0x47104068)

  #define MC0_CH0_CR_SC_WDBWM_WIM_wm_OFF                               (16)
  #define MC0_CH0_CR_SC_WDBWM_WIM_wm_WID                               ( 7)
  #define MC0_CH0_CR_SC_WDBWM_WIM_wm_MSK                               (0x007F0000)
  #define MC0_CH0_CR_SC_WDBWM_WIM_wm_MIN                               (0)
  #define MC0_CH0_CR_SC_WDBWM_WIM_wm_MAX                               (127) // 0x0000007F
  #define MC0_CH0_CR_SC_WDBWM_WIM_wm_DEF                               (0x0000003C)
  #define MC0_CH0_CR_SC_WDBWM_WIM_wm_HSH                               (0x47204068)

  #define MC0_CH0_CR_SC_WDBWM_Write_Isoc_CAS_count_OFF                 (24)
  #define MC0_CH0_CR_SC_WDBWM_Write_Isoc_CAS_count_WID                 ( 8)
  #define MC0_CH0_CR_SC_WDBWM_Write_Isoc_CAS_count_MSK                 (0xFF000000)
  #define MC0_CH0_CR_SC_WDBWM_Write_Isoc_CAS_count_MIN                 (0)
  #define MC0_CH0_CR_SC_WDBWM_Write_Isoc_CAS_count_MAX                 (255) // 0x000000FF
  #define MC0_CH0_CR_SC_WDBWM_Write_Isoc_CAS_count_DEF                 (0x00000040)
  #define MC0_CH0_CR_SC_WDBWM_Write_Isoc_CAS_count_HSH                 (0x48304068)

  #define MC0_CH0_CR_SC_WDBWM_Read_CAS_count_OFF                       (32)
  #define MC0_CH0_CR_SC_WDBWM_Read_CAS_count_WID                       ( 8)
  #define MC0_CH0_CR_SC_WDBWM_Read_CAS_count_MSK                       (0x000000FF00000000ULL)
  #define MC0_CH0_CR_SC_WDBWM_Read_CAS_count_MIN                       (0)
  #define MC0_CH0_CR_SC_WDBWM_Read_CAS_count_MAX                       (255) // 0x000000FF
  #define MC0_CH0_CR_SC_WDBWM_Read_CAS_count_DEF                       (0x00000040)
  #define MC0_CH0_CR_SC_WDBWM_Read_CAS_count_HSH                       (0x48404068)

  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_OFF                      (40)
  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_WID                      ( 8)
  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_MSK                      (0x0000FF0000000000ULL)
  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_MIN                      (0)
  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_MAX                      (255) // 0x000000FF
  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_DEF                      (0x00000040)
  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_HSH                      (0x48504068)

  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_for_VC1_OFF              (48)
  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_for_VC1_WID              ( 8)
  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_for_VC1_MSK              (0x00FF000000000000ULL)
  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_for_VC1_MIN              (0)
  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_for_VC1_MAX              (255) // 0x000000FF
  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_for_VC1_DEF              (0x00000040)
  #define MC0_CH0_CR_SC_WDBWM_Write_CAS_count_for_VC1_HSH              (0x48604068)

  #define MC0_CH0_CR_SC_WDBWM_Write_threshold_for_lp_read_bklr_OFF     (56)
  #define MC0_CH0_CR_SC_WDBWM_Write_threshold_for_lp_read_bklr_WID     ( 7)
  #define MC0_CH0_CR_SC_WDBWM_Write_threshold_for_lp_read_bklr_MSK     (0x7F00000000000000ULL)
  #define MC0_CH0_CR_SC_WDBWM_Write_threshold_for_lp_read_bklr_MIN     (0)
  #define MC0_CH0_CR_SC_WDBWM_Write_threshold_for_lp_read_bklr_MAX     (127) // 0x0000007F
  #define MC0_CH0_CR_SC_WDBWM_Write_threshold_for_lp_read_bklr_DEF     (0x00000016)
  #define MC0_CH0_CR_SC_WDBWM_Write_threshold_for_lp_read_bklr_HSH     (0x47704068)

  #define MC0_CH0_CR_SC_WDBWM_En_Wr_in_WIM_during_TT_OFF               (63)
  #define MC0_CH0_CR_SC_WDBWM_En_Wr_in_WIM_during_TT_WID               ( 1)
  #define MC0_CH0_CR_SC_WDBWM_En_Wr_in_WIM_during_TT_MSK               (0x8000000000000000ULL)
  #define MC0_CH0_CR_SC_WDBWM_En_Wr_in_WIM_during_TT_MIN               (0)
  #define MC0_CH0_CR_SC_WDBWM_En_Wr_in_WIM_during_TT_MAX               (1) // 0x00000001
  #define MC0_CH0_CR_SC_WDBWM_En_Wr_in_WIM_during_TT_DEF               (0x00000000)
  #define MC0_CH0_CR_SC_WDBWM_En_Wr_in_WIM_during_TT_HSH               (0x417E4068)

#define MC0_CH0_CR_TC_ODT_REG                                          (0x00004070)

  #define MC0_CH0_CR_TC_ODT_ODT_read_duration_OFF                      ( 0)
  #define MC0_CH0_CR_TC_ODT_ODT_read_duration_WID                      ( 4)
  #define MC0_CH0_CR_TC_ODT_ODT_read_duration_MSK                      (0x0000000F)
  #define MC0_CH0_CR_TC_ODT_ODT_read_duration_MIN                      (0)
  #define MC0_CH0_CR_TC_ODT_ODT_read_duration_MAX                      (15) // 0x0000000F
  #define MC0_CH0_CR_TC_ODT_ODT_read_duration_DEF                      (0x00000000)
  #define MC0_CH0_CR_TC_ODT_ODT_read_duration_HSH                      (0x44004070)

  #define MC0_CH0_CR_TC_ODT_ODT_Read_Delay_OFF                         ( 4)
  #define MC0_CH0_CR_TC_ODT_ODT_Read_Delay_WID                         ( 4)
  #define MC0_CH0_CR_TC_ODT_ODT_Read_Delay_MSK                         (0x000000F0)
  #define MC0_CH0_CR_TC_ODT_ODT_Read_Delay_MIN                         (0)
  #define MC0_CH0_CR_TC_ODT_ODT_Read_Delay_MAX                         (15) // 0x0000000F
  #define MC0_CH0_CR_TC_ODT_ODT_Read_Delay_DEF                         (0x00000000)
  #define MC0_CH0_CR_TC_ODT_ODT_Read_Delay_HSH                         (0x44084070)

  #define MC0_CH0_CR_TC_ODT_ODT_write_duration_OFF                     ( 8)
  #define MC0_CH0_CR_TC_ODT_ODT_write_duration_WID                     ( 4)
  #define MC0_CH0_CR_TC_ODT_ODT_write_duration_MSK                     (0x00000F00)
  #define MC0_CH0_CR_TC_ODT_ODT_write_duration_MIN                     (0)
  #define MC0_CH0_CR_TC_ODT_ODT_write_duration_MAX                     (15) // 0x0000000F
  #define MC0_CH0_CR_TC_ODT_ODT_write_duration_DEF                     (0x00000000)
  #define MC0_CH0_CR_TC_ODT_ODT_write_duration_HSH                     (0x44104070)

  #define MC0_CH0_CR_TC_ODT_ODT_Write_Delay_OFF                        (12)
  #define MC0_CH0_CR_TC_ODT_ODT_Write_Delay_WID                        ( 4)
  #define MC0_CH0_CR_TC_ODT_ODT_Write_Delay_MSK                        (0x0000F000)
  #define MC0_CH0_CR_TC_ODT_ODT_Write_Delay_MIN                        (0)
  #define MC0_CH0_CR_TC_ODT_ODT_Write_Delay_MAX                        (15) // 0x0000000F
  #define MC0_CH0_CR_TC_ODT_ODT_Write_Delay_DEF                        (0x00000000)
  #define MC0_CH0_CR_TC_ODT_ODT_Write_Delay_HSH                        (0x44184070)

  #define MC0_CH0_CR_TC_ODT_tCL_OFF                                    (16)
  #define MC0_CH0_CR_TC_ODT_tCL_WID                                    ( 7)
  #define MC0_CH0_CR_TC_ODT_tCL_MSK                                    (0x007F0000)
  #define MC0_CH0_CR_TC_ODT_tCL_MIN                                    (0)
  #define MC0_CH0_CR_TC_ODT_tCL_MAX                                    (127) // 0x0000007F
  #define MC0_CH0_CR_TC_ODT_tCL_DEF                                    (0x00000005)
  #define MC0_CH0_CR_TC_ODT_tCL_HSH                                    (0x47204070)

  #define MC0_CH0_CR_TC_ODT_tCWL_OFF                                   (23)
  #define MC0_CH0_CR_TC_ODT_tCWL_WID                                   ( 7)
  #define MC0_CH0_CR_TC_ODT_tCWL_MSK                                   (0x3F800000)
  #define MC0_CH0_CR_TC_ODT_tCWL_MIN                                   (0)
  #define MC0_CH0_CR_TC_ODT_tCWL_MAX                                   (127) // 0x0000007F
  #define MC0_CH0_CR_TC_ODT_tCWL_DEF                                   (0x00000006)
  #define MC0_CH0_CR_TC_ODT_tCWL_HSH                                   (0x472E4070)

  #define MC0_CH0_CR_TC_ODT_Write_Early_ODT_OFF                        (30)
  #define MC0_CH0_CR_TC_ODT_Write_Early_ODT_WID                        ( 1)
  #define MC0_CH0_CR_TC_ODT_Write_Early_ODT_MSK                        (0x40000000)
  #define MC0_CH0_CR_TC_ODT_Write_Early_ODT_MIN                        (0)
  #define MC0_CH0_CR_TC_ODT_Write_Early_ODT_MAX                        (1) // 0x00000001
  #define MC0_CH0_CR_TC_ODT_Write_Early_ODT_DEF                        (0x00000000)
  #define MC0_CH0_CR_TC_ODT_Write_Early_ODT_HSH                        (0x413C4070)

  #define MC0_CH0_CR_TC_ODT_tAONPD_OFF                                 (32)
  #define MC0_CH0_CR_TC_ODT_tAONPD_WID                                 ( 6)
  #define MC0_CH0_CR_TC_ODT_tAONPD_MSK                                 (0x0000003F00000000ULL)
  #define MC0_CH0_CR_TC_ODT_tAONPD_MIN                                 (0)
  #define MC0_CH0_CR_TC_ODT_tAONPD_MAX                                 (63) // 0x0000003F
  #define MC0_CH0_CR_TC_ODT_tAONPD_DEF                                 (0x00000004)
  #define MC0_CH0_CR_TC_ODT_tAONPD_HSH                                 (0x46404070)

#define MC0_CH0_CR_MCSCHEDS_SPARE_REG                                  (0x00004078)

  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_OFF                       ( 0)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_WID                       (15)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_MSK                       (0x00007FFF)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_MIN                       (0)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_MAX                       (32767) // 0x00007FFF
  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_DEF                       (0x00000000)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_HSH                       (0x0F004078)

  #define MC0_CH0_CR_MCSCHEDS_SPARE_EnableB2BPreemption_OFF            (15)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_EnableB2BPreemption_WID            ( 1)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_EnableB2BPreemption_MSK            (0x00008000)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_EnableB2BPreemption_MIN            (0)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_EnableB2BPreemption_MAX            (1) // 0x00000001
  #define MC0_CH0_CR_MCSCHEDS_SPARE_EnableB2BPreemption_DEF            (0x00000000)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_EnableB2BPreemption_HSH            (0x011E4078)

  #define MC0_CH0_CR_MCSCHEDS_SPARE_WMM_exit_wm_for_FBRMM_OFF          (16)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_WMM_exit_wm_for_FBRMM_WID          ( 7)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_WMM_exit_wm_for_FBRMM_MSK          (0x007F0000)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_WMM_exit_wm_for_FBRMM_MIN          (0)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_WMM_exit_wm_for_FBRMM_MAX          (127) // 0x0000007F
  #define MC0_CH0_CR_MCSCHEDS_SPARE_WMM_exit_wm_for_FBRMM_DEF          (0x00000030)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_WMM_exit_wm_for_FBRMM_HSH          (0x07204078)

  #define MC0_CH0_CR_MCSCHEDS_SPARE_ForcePBRWM_OFF                     (23)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_ForcePBRWM_WID                     ( 4)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_ForcePBRWM_MSK                     (0x07800000)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_ForcePBRWM_MIN                     (0)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_ForcePBRWM_MAX                     (15) // 0x0000000F
  #define MC0_CH0_CR_MCSCHEDS_SPARE_ForcePBRWM_DEF                     (0x00000005)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_ForcePBRWM_HSH                     (0x042E4078)

  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_V_OFF                     (27)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_V_WID                     ( 5)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_V_MSK                     (0xF8000000)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_V_MIN                     (0)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_V_MAX                     (31) // 0x0000001F
  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_V_DEF                     (0x00000000)
  #define MC0_CH0_CR_MCSCHEDS_SPARE_Spare_RW_V_HSH                     (0x05364078)

#define MC0_CH0_CR_SC_ODT_MATRIX_REG                                   (0x00004080)

  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_0_OFF                     ( 0)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_0_WID                     ( 4)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_0_MSK                     (0x0000000F)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_0_MIN                     (0)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_0_MAX                     (15) // 0x0000000F
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_0_DEF                     (0x00000000)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_0_HSH                     (0x04004080)

  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_1_OFF                     ( 4)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_1_WID                     ( 4)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_1_MSK                     (0x000000F0)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_1_MIN                     (0)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_1_MAX                     (15) // 0x0000000F
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_1_DEF                     (0x00000000)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_1_HSH                     (0x04084080)

  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_2_OFF                     ( 8)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_2_WID                     ( 4)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_2_MSK                     (0x00000F00)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_2_MIN                     (0)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_2_MAX                     (15) // 0x0000000F
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_2_DEF                     (0x00000000)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_2_HSH                     (0x04104080)

  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_3_OFF                     (12)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_3_WID                     ( 4)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_3_MSK                     (0x0000F000)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_3_MIN                     (0)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_3_MAX                     (15) // 0x0000000F
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_3_DEF                     (0x00000000)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Read_Rank_3_HSH                     (0x04184080)

  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_0_OFF                    (16)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_0_WID                    ( 4)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_0_MSK                    (0x000F0000)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_0_MIN                    (0)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_0_MAX                    (15) // 0x0000000F
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_0_DEF                    (0x00000000)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_0_HSH                    (0x04204080)

  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_1_OFF                    (20)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_1_WID                    ( 4)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_1_MSK                    (0x00F00000)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_1_MIN                    (0)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_1_MAX                    (15) // 0x0000000F
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_1_DEF                    (0x00000000)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_1_HSH                    (0x04284080)

  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_2_OFF                    (24)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_2_WID                    ( 4)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_2_MSK                    (0x0F000000)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_2_MIN                    (0)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_2_MAX                    (15) // 0x0000000F
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_2_DEF                    (0x00000000)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_2_HSH                    (0x04304080)

  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_3_OFF                    (28)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_3_WID                    ( 4)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_3_MSK                    (0xF0000000)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_3_MIN                    (0)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_3_MAX                    (15) // 0x0000000F
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_3_DEF                    (0x00000000)
  #define MC0_CH0_CR_SC_ODT_MATRIX_Write_Rank_3_HSH                    (0x04384080)

#define MC0_CH0_CR_DFT_BLOCK_REG                                       (0x00004084)

  #define MC0_CH0_CR_DFT_BLOCK_dft_block_cycles_OFF                    ( 0)
  #define MC0_CH0_CR_DFT_BLOCK_dft_block_cycles_WID                    (16)
  #define MC0_CH0_CR_DFT_BLOCK_dft_block_cycles_MSK                    (0x0000FFFF)
  #define MC0_CH0_CR_DFT_BLOCK_dft_block_cycles_MIN                    (0)
  #define MC0_CH0_CR_DFT_BLOCK_dft_block_cycles_MAX                    (65535) // 0x0000FFFF
  #define MC0_CH0_CR_DFT_BLOCK_dft_block_cycles_DEF                    (0x00000000)
  #define MC0_CH0_CR_DFT_BLOCK_dft_block_cycles_HSH                    (0x10004084)

  #define MC0_CH0_CR_DFT_BLOCK_dft_nonblock_cycles_OFF                 (16)
  #define MC0_CH0_CR_DFT_BLOCK_dft_nonblock_cycles_WID                 (16)
  #define MC0_CH0_CR_DFT_BLOCK_dft_nonblock_cycles_MSK                 (0xFFFF0000)
  #define MC0_CH0_CR_DFT_BLOCK_dft_nonblock_cycles_MIN                 (0)
  #define MC0_CH0_CR_DFT_BLOCK_dft_nonblock_cycles_MAX                 (65535) // 0x0000FFFF
  #define MC0_CH0_CR_DFT_BLOCK_dft_nonblock_cycles_DEF                 (0x00000000)
  #define MC0_CH0_CR_DFT_BLOCK_dft_nonblock_cycles_HSH                 (0x10204084)

#define MC0_CH0_CR_SC_GS_CFG_REG                                       (0x00004088)

  #define MC0_CH0_CR_SC_GS_CFG_DRAM_technology_OFF                     ( 0)
  #define MC0_CH0_CR_SC_GS_CFG_DRAM_technology_WID                     ( 3)
  #define MC0_CH0_CR_SC_GS_CFG_DRAM_technology_MSK                     (0x00000007)
  #define MC0_CH0_CR_SC_GS_CFG_DRAM_technology_MIN                     (0)
  #define MC0_CH0_CR_SC_GS_CFG_DRAM_technology_MAX                     (7) // 0x00000007
  #define MC0_CH0_CR_SC_GS_CFG_DRAM_technology_DEF                     (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_DRAM_technology_HSH                     (0x43004088)

  #define MC0_CH0_CR_SC_GS_CFG_CMD_stretch_OFF                         ( 3)
  #define MC0_CH0_CR_SC_GS_CFG_CMD_stretch_WID                         ( 2)
  #define MC0_CH0_CR_SC_GS_CFG_CMD_stretch_MSK                         (0x00000018)
  #define MC0_CH0_CR_SC_GS_CFG_CMD_stretch_MIN                         (0)
  #define MC0_CH0_CR_SC_GS_CFG_CMD_stretch_MAX                         (3) // 0x00000003
  #define MC0_CH0_CR_SC_GS_CFG_CMD_stretch_DEF                         (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_CMD_stretch_HSH                         (0x42064088)

  #define MC0_CH0_CR_SC_GS_CFG_N_to_1_ratio_OFF                        ( 5)
  #define MC0_CH0_CR_SC_GS_CFG_N_to_1_ratio_WID                        ( 3)
  #define MC0_CH0_CR_SC_GS_CFG_N_to_1_ratio_MSK                        (0x000000E0)
  #define MC0_CH0_CR_SC_GS_CFG_N_to_1_ratio_MIN                        (0)
  #define MC0_CH0_CR_SC_GS_CFG_N_to_1_ratio_MAX                        (7) // 0x00000007
  #define MC0_CH0_CR_SC_GS_CFG_N_to_1_ratio_DEF                        (0x00000001)
  #define MC0_CH0_CR_SC_GS_CFG_N_to_1_ratio_HSH                        (0x430A4088)

  #define MC0_CH0_CR_SC_GS_CFG_Address_mirror_OFF                      ( 8)
  #define MC0_CH0_CR_SC_GS_CFG_Address_mirror_WID                      ( 4)
  #define MC0_CH0_CR_SC_GS_CFG_Address_mirror_MSK                      (0x00000F00)
  #define MC0_CH0_CR_SC_GS_CFG_Address_mirror_MIN                      (0)
  #define MC0_CH0_CR_SC_GS_CFG_Address_mirror_MAX                      (15) // 0x0000000F
  #define MC0_CH0_CR_SC_GS_CFG_Address_mirror_DEF                      (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_Address_mirror_HSH                      (0x44104088)

  #define MC0_CH0_CR_SC_GS_CFG_tCPDED_OFF                              (12)
  #define MC0_CH0_CR_SC_GS_CFG_tCPDED_WID                              ( 3)
  #define MC0_CH0_CR_SC_GS_CFG_tCPDED_MSK                              (0x00007000)
  #define MC0_CH0_CR_SC_GS_CFG_tCPDED_MIN                              (0)
  #define MC0_CH0_CR_SC_GS_CFG_tCPDED_MAX                              (7) // 0x00000007
  #define MC0_CH0_CR_SC_GS_CFG_tCPDED_DEF                              (0x00000001)
  #define MC0_CH0_CR_SC_GS_CFG_tCPDED_HSH                              (0x43184088)

  #define MC0_CH0_CR_SC_GS_CFG_disable_tristate_OFF                    (15)
  #define MC0_CH0_CR_SC_GS_CFG_disable_tristate_WID                    ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_disable_tristate_MSK                    (0x00008000)
  #define MC0_CH0_CR_SC_GS_CFG_disable_tristate_MIN                    (0)
  #define MC0_CH0_CR_SC_GS_CFG_disable_tristate_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_disable_tristate_DEF                    (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_disable_tristate_HSH                    (0x411E4088)

  #define MC0_CH0_CR_SC_GS_CFG_tCAL_OFF                                (19)
  #define MC0_CH0_CR_SC_GS_CFG_tCAL_WID                                ( 3)
  #define MC0_CH0_CR_SC_GS_CFG_tCAL_MSK                                (0x00380000)
  #define MC0_CH0_CR_SC_GS_CFG_tCAL_MIN                                (0)
  #define MC0_CH0_CR_SC_GS_CFG_tCAL_MAX                                (7) // 0x00000007
  #define MC0_CH0_CR_SC_GS_CFG_tCAL_DEF                                (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_tCAL_HSH                                (0x43264088)

  #define MC0_CH0_CR_SC_GS_CFG_frequency_point_OFF                     (22)
  #define MC0_CH0_CR_SC_GS_CFG_frequency_point_WID                     ( 2)
  #define MC0_CH0_CR_SC_GS_CFG_frequency_point_MSK                     (0x00C00000)
  #define MC0_CH0_CR_SC_GS_CFG_frequency_point_MIN                     (0)
  #define MC0_CH0_CR_SC_GS_CFG_frequency_point_MAX                     (3) // 0x00000003
  #define MC0_CH0_CR_SC_GS_CFG_frequency_point_DEF                     (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_frequency_point_HSH                     (0x422C4088)

  #define MC0_CH0_CR_SC_GS_CFG_enable_odt_matrix_OFF                   (24)
  #define MC0_CH0_CR_SC_GS_CFG_enable_odt_matrix_WID                   ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_enable_odt_matrix_MSK                   (0x01000000)
  #define MC0_CH0_CR_SC_GS_CFG_enable_odt_matrix_MIN                   (0)
  #define MC0_CH0_CR_SC_GS_CFG_enable_odt_matrix_MAX                   (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_enable_odt_matrix_DEF                   (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_enable_odt_matrix_HSH                   (0x41304088)

  #define MC0_CH0_CR_SC_GS_CFG_cs_to_cke_OFF                           (25)
  #define MC0_CH0_CR_SC_GS_CFG_cs_to_cke_WID                           ( 3)
  #define MC0_CH0_CR_SC_GS_CFG_cs_to_cke_MSK                           (0x0E000000)
  #define MC0_CH0_CR_SC_GS_CFG_cs_to_cke_MIN                           (0)
  #define MC0_CH0_CR_SC_GS_CFG_cs_to_cke_MAX                           (7) // 0x00000007
  #define MC0_CH0_CR_SC_GS_CFG_cs_to_cke_DEF                           (0x00000002)
  #define MC0_CH0_CR_SC_GS_CFG_cs_to_cke_HSH                           (0x43324088)

  #define MC0_CH0_CR_SC_GS_CFG_x8_device_OFF                           (28)
  #define MC0_CH0_CR_SC_GS_CFG_x8_device_WID                           ( 2)
  #define MC0_CH0_CR_SC_GS_CFG_x8_device_MSK                           (0x30000000)
  #define MC0_CH0_CR_SC_GS_CFG_x8_device_MIN                           (0)
  #define MC0_CH0_CR_SC_GS_CFG_x8_device_MAX                           (3) // 0x00000003
  #define MC0_CH0_CR_SC_GS_CFG_x8_device_DEF                           (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_x8_device_HSH                           (0x42384088)

  #define MC0_CH0_CR_SC_GS_CFG_no_gear2_param_divide_OFF               (30)
  #define MC0_CH0_CR_SC_GS_CFG_no_gear2_param_divide_WID               ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_no_gear2_param_divide_MSK               (0x40000000)
  #define MC0_CH0_CR_SC_GS_CFG_no_gear2_param_divide_MIN               (0)
  #define MC0_CH0_CR_SC_GS_CFG_no_gear2_param_divide_MAX               (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_no_gear2_param_divide_DEF               (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_no_gear2_param_divide_HSH               (0x413C4088)

  #define MC0_CH0_CR_SC_GS_CFG_gear2_OFF                               (31)
  #define MC0_CH0_CR_SC_GS_CFG_gear2_WID                               ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_gear2_MSK                               (0x80000000)
  #define MC0_CH0_CR_SC_GS_CFG_gear2_MIN                               (0)
  #define MC0_CH0_CR_SC_GS_CFG_gear2_MAX                               (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_gear2_DEF                               (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_gear2_HSH                               (0x413E4088)

  #define MC0_CH0_CR_SC_GS_CFG_ddr4_1dpc_OFF                           (32)
  #define MC0_CH0_CR_SC_GS_CFG_ddr4_1dpc_WID                           ( 2)
  #define MC0_CH0_CR_SC_GS_CFG_ddr4_1dpc_MSK                           (0x0000000300000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_ddr4_1dpc_MIN                           (0)
  #define MC0_CH0_CR_SC_GS_CFG_ddr4_1dpc_MAX                           (3) // 0x00000003
  #define MC0_CH0_CR_SC_GS_CFG_ddr4_1dpc_DEF                           (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_ddr4_1dpc_HSH                           (0x42404088)

  #define MC0_CH0_CR_SC_GS_CFG_Limit_MM_Transitions_OFF                (34)
  #define MC0_CH0_CR_SC_GS_CFG_Limit_MM_Transitions_WID                ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_Limit_MM_Transitions_MSK                (0x0000000400000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_Limit_MM_Transitions_MIN                (0)
  #define MC0_CH0_CR_SC_GS_CFG_Limit_MM_Transitions_MAX                (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_Limit_MM_Transitions_DEF                (0x00000001)
  #define MC0_CH0_CR_SC_GS_CFG_Limit_MM_Transitions_HSH                (0x41444088)

  #define MC0_CH0_CR_SC_GS_CFG_pl_trace_only_cs_cmd_OFF                (35)
  #define MC0_CH0_CR_SC_GS_CFG_pl_trace_only_cs_cmd_WID                ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_pl_trace_only_cs_cmd_MSK                (0x0000000800000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_pl_trace_only_cs_cmd_MIN                (0)
  #define MC0_CH0_CR_SC_GS_CFG_pl_trace_only_cs_cmd_MAX                (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_pl_trace_only_cs_cmd_DEF                (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_pl_trace_only_cs_cmd_HSH                (0x41464088)

  #define MC0_CH0_CR_SC_GS_CFG_two_cycle_cke_idle_OFF                  (36)
  #define MC0_CH0_CR_SC_GS_CFG_two_cycle_cke_idle_WID                  ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_two_cycle_cke_idle_MSK                  (0x0000001000000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_two_cycle_cke_idle_MIN                  (0)
  #define MC0_CH0_CR_SC_GS_CFG_two_cycle_cke_idle_MAX                  (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_two_cycle_cke_idle_DEF                  (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_two_cycle_cke_idle_HSH                  (0x41484088)

  #define MC0_CH0_CR_SC_GS_CFG_disable_ca_tristate_OFF                 (37)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ca_tristate_WID                 ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ca_tristate_MSK                 (0x0000002000000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ca_tristate_MIN                 (0)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ca_tristate_MAX                 (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_disable_ca_tristate_DEF                 (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ca_tristate_HSH                 (0x414A4088)

  #define MC0_CH0_CR_SC_GS_CFG_disable_ck_tristate_OFF                 (38)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ck_tristate_WID                 ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ck_tristate_MSK                 (0x0000004000000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ck_tristate_MIN                 (0)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ck_tristate_MAX                 (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_disable_ck_tristate_DEF                 (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ck_tristate_HSH                 (0x414C4088)

  #define MC0_CH0_CR_SC_GS_CFG_ck_to_cke_OFF                           (39)
  #define MC0_CH0_CR_SC_GS_CFG_ck_to_cke_WID                           ( 7)
  #define MC0_CH0_CR_SC_GS_CFG_ck_to_cke_MSK                           (0x00003F8000000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_ck_to_cke_MIN                           (0)
  #define MC0_CH0_CR_SC_GS_CFG_ck_to_cke_MAX                           (127) // 0x0000007F
  #define MC0_CH0_CR_SC_GS_CFG_ck_to_cke_DEF                           (0x00000002)
  #define MC0_CH0_CR_SC_GS_CFG_ck_to_cke_HSH                           (0x474E4088)

  #define MC0_CH0_CR_SC_GS_CFG_lp5_wck_tck_ratio_OFF                   (46)
  #define MC0_CH0_CR_SC_GS_CFG_lp5_wck_tck_ratio_WID                   ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_lp5_wck_tck_ratio_MSK                   (0x0000400000000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_lp5_wck_tck_ratio_MIN                   (0)
  #define MC0_CH0_CR_SC_GS_CFG_lp5_wck_tck_ratio_MAX                   (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_lp5_wck_tck_ratio_DEF                   (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_lp5_wck_tck_ratio_HSH                   (0x415C4088)

  #define MC0_CH0_CR_SC_GS_CFG_write0_enable_OFF                       (47)
  #define MC0_CH0_CR_SC_GS_CFG_write0_enable_WID                       ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_write0_enable_MSK                       (0x0000800000000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_write0_enable_MIN                       (0)
  #define MC0_CH0_CR_SC_GS_CFG_write0_enable_MAX                       (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_write0_enable_DEF                       (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_write0_enable_HSH                       (0x415E4088)

  #define MC0_CH0_CR_SC_GS_CFG_row_msb_OFF                             (49)
  #define MC0_CH0_CR_SC_GS_CFG_row_msb_WID                             ( 2)
  #define MC0_CH0_CR_SC_GS_CFG_row_msb_MSK                             (0x0006000000000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_row_msb_MIN                             (0)
  #define MC0_CH0_CR_SC_GS_CFG_row_msb_MAX                             (3) // 0x00000003
  #define MC0_CH0_CR_SC_GS_CFG_row_msb_DEF                             (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_row_msb_HSH                             (0x42624088)

  #define MC0_CH0_CR_SC_GS_CFG_WCKDiffLowInIdle_OFF                    (51)
  #define MC0_CH0_CR_SC_GS_CFG_WCKDiffLowInIdle_WID                    ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_WCKDiffLowInIdle_MSK                    (0x0008000000000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_WCKDiffLowInIdle_MIN                    (0)
  #define MC0_CH0_CR_SC_GS_CFG_WCKDiffLowInIdle_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_WCKDiffLowInIdle_DEF                    (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_WCKDiffLowInIdle_HSH                    (0x41664088)

#define MC0_CH0_CR_SC_GS_CFG_A0_REG                                    (0x00004088)

  #define MC0_CH0_CR_SC_GS_CFG_DRAM_technology_A0_OFF                  ( 0)
  #define MC0_CH0_CR_SC_GS_CFG_DRAM_technology_A0_WID                  ( 3)
  #define MC0_CH0_CR_SC_GS_CFG_DRAM_technology_A0_MSK                  (0x00000007)
  #define MC0_CH0_CR_SC_GS_CFG_DRAM_technology_A0_MIN                  (0)
  #define MC0_CH0_CR_SC_GS_CFG_DRAM_technology_A0_MAX                  (7) // 0x00000007
  #define MC0_CH0_CR_SC_GS_CFG_DRAM_technology_A0_DEF                  (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_DRAM_technology_A0_HSH                  (0x43004088)

  #define MC0_CH0_CR_SC_GS_CFG_CMD_stretch_A0_OFF                      ( 3)
  #define MC0_CH0_CR_SC_GS_CFG_CMD_stretch_A0_WID                      ( 2)
  #define MC0_CH0_CR_SC_GS_CFG_CMD_stretch_A0_MSK                      (0x00000018)
  #define MC0_CH0_CR_SC_GS_CFG_CMD_stretch_A0_MIN                      (0)
  #define MC0_CH0_CR_SC_GS_CFG_CMD_stretch_A0_MAX                      (3) // 0x00000003
  #define MC0_CH0_CR_SC_GS_CFG_CMD_stretch_A0_DEF                      (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_CMD_stretch_A0_HSH                      (0x42064088)

  #define MC0_CH0_CR_SC_GS_CFG_N_to_1_ratio_A0_OFF                     ( 5)
  #define MC0_CH0_CR_SC_GS_CFG_N_to_1_ratio_A0_WID                     ( 3)
  #define MC0_CH0_CR_SC_GS_CFG_N_to_1_ratio_A0_MSK                     (0x000000E0)
  #define MC0_CH0_CR_SC_GS_CFG_N_to_1_ratio_A0_MIN                     (0)
  #define MC0_CH0_CR_SC_GS_CFG_N_to_1_ratio_A0_MAX                     (7) // 0x00000007
  #define MC0_CH0_CR_SC_GS_CFG_N_to_1_ratio_A0_DEF                     (0x00000001)
  #define MC0_CH0_CR_SC_GS_CFG_N_to_1_ratio_A0_HSH                     (0x430A4088)

  #define MC0_CH0_CR_SC_GS_CFG_Address_mirror_A0_OFF                   ( 8)
  #define MC0_CH0_CR_SC_GS_CFG_Address_mirror_A0_WID                   ( 4)
  #define MC0_CH0_CR_SC_GS_CFG_Address_mirror_A0_MSK                   (0x00000F00)
  #define MC0_CH0_CR_SC_GS_CFG_Address_mirror_A0_MIN                   (0)
  #define MC0_CH0_CR_SC_GS_CFG_Address_mirror_A0_MAX                   (15) // 0x0000000F
  #define MC0_CH0_CR_SC_GS_CFG_Address_mirror_A0_DEF                   (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_Address_mirror_A0_HSH                   (0x44104088)

  #define MC0_CH0_CR_SC_GS_CFG_tCPDED_A0_OFF                           (12)
  #define MC0_CH0_CR_SC_GS_CFG_tCPDED_A0_WID                           ( 3)
  #define MC0_CH0_CR_SC_GS_CFG_tCPDED_A0_MSK                           (0x00007000)
  #define MC0_CH0_CR_SC_GS_CFG_tCPDED_A0_MIN                           (0)
  #define MC0_CH0_CR_SC_GS_CFG_tCPDED_A0_MAX                           (7) // 0x00000007
  #define MC0_CH0_CR_SC_GS_CFG_tCPDED_A0_DEF                           (0x00000001)
  #define MC0_CH0_CR_SC_GS_CFG_tCPDED_A0_HSH                           (0x43184088)

  #define MC0_CH0_CR_SC_GS_CFG_disable_tristate_A0_OFF                 (15)
  #define MC0_CH0_CR_SC_GS_CFG_disable_tristate_A0_WID                 ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_disable_tristate_A0_MSK                 (0x00008000)
  #define MC0_CH0_CR_SC_GS_CFG_disable_tristate_A0_MIN                 (0)
  #define MC0_CH0_CR_SC_GS_CFG_disable_tristate_A0_MAX                 (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_disable_tristate_A0_DEF                 (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_disable_tristate_A0_HSH                 (0x411E4088)

  #define MC0_CH0_CR_SC_GS_CFG_tCAL_A0_OFF                             (19)
  #define MC0_CH0_CR_SC_GS_CFG_tCAL_A0_WID                             ( 3)
  #define MC0_CH0_CR_SC_GS_CFG_tCAL_A0_MSK                             (0x00380000)
  #define MC0_CH0_CR_SC_GS_CFG_tCAL_A0_MIN                             (0)
  #define MC0_CH0_CR_SC_GS_CFG_tCAL_A0_MAX                             (7) // 0x00000007
  #define MC0_CH0_CR_SC_GS_CFG_tCAL_A0_DEF                             (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_tCAL_A0_HSH                             (0x43264088)

  #define MC0_CH0_CR_SC_GS_CFG_frequency_point_A0_OFF                  (22)
  #define MC0_CH0_CR_SC_GS_CFG_frequency_point_A0_WID                  ( 2)
  #define MC0_CH0_CR_SC_GS_CFG_frequency_point_A0_MSK                  (0x00C00000)
  #define MC0_CH0_CR_SC_GS_CFG_frequency_point_A0_MIN                  (0)
  #define MC0_CH0_CR_SC_GS_CFG_frequency_point_A0_MAX                  (3) // 0x00000003
  #define MC0_CH0_CR_SC_GS_CFG_frequency_point_A0_DEF                  (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_frequency_point_A0_HSH                  (0x422C4088)

  #define MC0_CH0_CR_SC_GS_CFG_enable_odt_matrix_A0_OFF                (24)
  #define MC0_CH0_CR_SC_GS_CFG_enable_odt_matrix_A0_WID                ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_enable_odt_matrix_A0_MSK                (0x01000000)
  #define MC0_CH0_CR_SC_GS_CFG_enable_odt_matrix_A0_MIN                (0)
  #define MC0_CH0_CR_SC_GS_CFG_enable_odt_matrix_A0_MAX                (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_enable_odt_matrix_A0_DEF                (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_enable_odt_matrix_A0_HSH                (0x41304088)

  #define MC0_CH0_CR_SC_GS_CFG_cs_to_cke_A0_OFF                        (25)
  #define MC0_CH0_CR_SC_GS_CFG_cs_to_cke_A0_WID                        ( 3)
  #define MC0_CH0_CR_SC_GS_CFG_cs_to_cke_A0_MSK                        (0x0E000000)
  #define MC0_CH0_CR_SC_GS_CFG_cs_to_cke_A0_MIN                        (0)
  #define MC0_CH0_CR_SC_GS_CFG_cs_to_cke_A0_MAX                        (7) // 0x00000007
  #define MC0_CH0_CR_SC_GS_CFG_cs_to_cke_A0_DEF                        (0x00000002)
  #define MC0_CH0_CR_SC_GS_CFG_cs_to_cke_A0_HSH                        (0x43324088)

  #define MC0_CH0_CR_SC_GS_CFG_x8_device_A0_OFF                        (28)
  #define MC0_CH0_CR_SC_GS_CFG_x8_device_A0_WID                        ( 2)
  #define MC0_CH0_CR_SC_GS_CFG_x8_device_A0_MSK                        (0x30000000)
  #define MC0_CH0_CR_SC_GS_CFG_x8_device_A0_MIN                        (0)
  #define MC0_CH0_CR_SC_GS_CFG_x8_device_A0_MAX                        (3) // 0x00000003
  #define MC0_CH0_CR_SC_GS_CFG_x8_device_A0_DEF                        (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_x8_device_A0_HSH                        (0x42384088)

  #define MC0_CH0_CR_SC_GS_CFG_no_gear2_param_divide_A0_OFF            (30)
  #define MC0_CH0_CR_SC_GS_CFG_no_gear2_param_divide_A0_WID            ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_no_gear2_param_divide_A0_MSK            (0x40000000)
  #define MC0_CH0_CR_SC_GS_CFG_no_gear2_param_divide_A0_MIN            (0)
  #define MC0_CH0_CR_SC_GS_CFG_no_gear2_param_divide_A0_MAX            (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_no_gear2_param_divide_A0_DEF            (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_no_gear2_param_divide_A0_HSH            (0x413C4088)

  #define MC0_CH0_CR_SC_GS_CFG_gear2_A0_OFF                            (31)
  #define MC0_CH0_CR_SC_GS_CFG_gear2_A0_WID                            ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_gear2_A0_MSK                            (0x80000000)
  #define MC0_CH0_CR_SC_GS_CFG_gear2_A0_MIN                            (0)
  #define MC0_CH0_CR_SC_GS_CFG_gear2_A0_MAX                            (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_gear2_A0_DEF                            (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_gear2_A0_HSH                            (0x413E4088)

  #define MC0_CH0_CR_SC_GS_CFG_ddr4_1dpc_A0_OFF                        (32)
  #define MC0_CH0_CR_SC_GS_CFG_ddr4_1dpc_A0_WID                        ( 2)
  #define MC0_CH0_CR_SC_GS_CFG_ddr4_1dpc_A0_MSK                        (0x0000000300000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_ddr4_1dpc_A0_MIN                        (0)
  #define MC0_CH0_CR_SC_GS_CFG_ddr4_1dpc_A0_MAX                        (3) // 0x00000003
  #define MC0_CH0_CR_SC_GS_CFG_ddr4_1dpc_A0_DEF                        (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_ddr4_1dpc_A0_HSH                        (0x42404088)

  #define MC0_CH0_CR_SC_GS_CFG_Limit_MM_Transitions_A0_OFF             (34)
  #define MC0_CH0_CR_SC_GS_CFG_Limit_MM_Transitions_A0_WID             ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_Limit_MM_Transitions_A0_MSK             (0x0000000400000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_Limit_MM_Transitions_A0_MIN             (0)
  #define MC0_CH0_CR_SC_GS_CFG_Limit_MM_Transitions_A0_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_Limit_MM_Transitions_A0_DEF             (0x00000001)
  #define MC0_CH0_CR_SC_GS_CFG_Limit_MM_Transitions_A0_HSH             (0x41444088)

  #define MC0_CH0_CR_SC_GS_CFG_pl_trace_only_cs_cmd_A0_OFF             (35)
  #define MC0_CH0_CR_SC_GS_CFG_pl_trace_only_cs_cmd_A0_WID             ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_pl_trace_only_cs_cmd_A0_MSK             (0x0000000800000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_pl_trace_only_cs_cmd_A0_MIN             (0)
  #define MC0_CH0_CR_SC_GS_CFG_pl_trace_only_cs_cmd_A0_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_pl_trace_only_cs_cmd_A0_DEF             (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_pl_trace_only_cs_cmd_A0_HSH             (0x41464088)

  #define MC0_CH0_CR_SC_GS_CFG_two_cycle_cke_idle_A0_OFF               (36)
  #define MC0_CH0_CR_SC_GS_CFG_two_cycle_cke_idle_A0_WID               ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_two_cycle_cke_idle_A0_MSK               (0x0000001000000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_two_cycle_cke_idle_A0_MIN               (0)
  #define MC0_CH0_CR_SC_GS_CFG_two_cycle_cke_idle_A0_MAX               (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_two_cycle_cke_idle_A0_DEF               (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_two_cycle_cke_idle_A0_HSH               (0x41484088)

  #define MC0_CH0_CR_SC_GS_CFG_disable_ca_tristate_A0_OFF              (37)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ca_tristate_A0_WID              ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ca_tristate_A0_MSK              (0x0000002000000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ca_tristate_A0_MIN              (0)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ca_tristate_A0_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_disable_ca_tristate_A0_DEF              (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ca_tristate_A0_HSH              (0x414A4088)

  #define MC0_CH0_CR_SC_GS_CFG_disable_ck_tristate_A0_OFF              (38)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ck_tristate_A0_WID              ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ck_tristate_A0_MSK              (0x0000004000000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ck_tristate_A0_MIN              (0)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ck_tristate_A0_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_disable_ck_tristate_A0_DEF              (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_disable_ck_tristate_A0_HSH              (0x414C4088)

  #define MC0_CH0_CR_SC_GS_CFG_ck_to_cke_A0_OFF                        (39)
  #define MC0_CH0_CR_SC_GS_CFG_ck_to_cke_A0_WID                        ( 7)
  #define MC0_CH0_CR_SC_GS_CFG_ck_to_cke_A0_MSK                        (0x00003F8000000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_ck_to_cke_A0_MIN                        (0)
  #define MC0_CH0_CR_SC_GS_CFG_ck_to_cke_A0_MAX                        (127) // 0x0000007F
  #define MC0_CH0_CR_SC_GS_CFG_ck_to_cke_A0_DEF                        (0x00000002)
  #define MC0_CH0_CR_SC_GS_CFG_ck_to_cke_A0_HSH                        (0x474E4088)

  #define MC0_CH0_CR_SC_GS_CFG_lp5_wck_tck_ratio_A0_OFF                (46)
  #define MC0_CH0_CR_SC_GS_CFG_lp5_wck_tck_ratio_A0_WID                ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_lp5_wck_tck_ratio_A0_MSK                (0x0000400000000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_lp5_wck_tck_ratio_A0_MIN                (0)
  #define MC0_CH0_CR_SC_GS_CFG_lp5_wck_tck_ratio_A0_MAX                (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_lp5_wck_tck_ratio_A0_DEF                (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_lp5_wck_tck_ratio_A0_HSH                (0x415C4088)

  #define MC0_CH0_CR_SC_GS_CFG_write0_enable_A0_OFF                    (47)
  #define MC0_CH0_CR_SC_GS_CFG_write0_enable_A0_WID                    ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_write0_enable_A0_MSK                    (0x0000800000000000ULL)
  #define MC0_CH0_CR_SC_GS_CFG_write0_enable_A0_MIN                    (0)
  #define MC0_CH0_CR_SC_GS_CFG_write0_enable_A0_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_write0_enable_A0_DEF                    (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_write0_enable_A0_HSH                    (0x415E4088)

#define MC0_CH0_CR_SC_PH_THROTTLING_0_REG                              (0x00004090)

  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_same_rank_OFF           ( 0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_same_rank_WID           ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_same_rank_MSK           (0x0000003F)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_same_rank_MIN           (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_same_rank_MAX           (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_same_rank_DEF           (0x00000008)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_same_rank_HSH           (0x06004090)

  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_same_rank_OFF         ( 8)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_same_rank_WID         ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_same_rank_MSK         (0x00003F00)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_same_rank_MIN         (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_same_rank_MAX         (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_same_rank_DEF         (0x00000001)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_same_rank_HSH         (0x06104090)

  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_different_rank_OFF      (16)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_different_rank_WID      ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_different_rank_MSK      (0x003F0000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_different_rank_MIN      (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_different_rank_MAX      (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_different_rank_DEF      (0x0000000C)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_loaded_different_rank_HSH      (0x06204090)

  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_different_rank_OFF    (24)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_different_rank_WID    ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_different_rank_MSK    (0x3F000000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_different_rank_MIN    (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_different_rank_MAX    (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_different_rank_DEF    (0x00000003)
  #define MC0_CH0_CR_SC_PH_THROTTLING_0_unloaded_different_rank_HSH    (0x06304090)

#define MC0_CH0_CR_SC_PH_THROTTLING_1_REG                              (0x00004094)

  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_same_rank_OFF           ( 0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_same_rank_WID           ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_same_rank_MSK           (0x0000003F)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_same_rank_MIN           (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_same_rank_MAX           (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_same_rank_DEF           (0x00000004)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_same_rank_HSH           (0x06004094)

  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_same_rank_OFF         ( 8)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_same_rank_WID         ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_same_rank_MSK         (0x00003F00)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_same_rank_MIN         (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_same_rank_MAX         (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_same_rank_DEF         (0x00000000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_same_rank_HSH         (0x06104094)

  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_different_rank_OFF      (16)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_different_rank_WID      ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_different_rank_MSK      (0x003F0000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_different_rank_MIN      (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_different_rank_MAX      (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_different_rank_DEF      (0x00000008)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_loaded_different_rank_HSH      (0x06204094)

  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_different_rank_OFF    (24)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_different_rank_WID    ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_different_rank_MSK    (0x3F000000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_different_rank_MIN    (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_different_rank_MAX    (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_different_rank_DEF    (0x00000002)
  #define MC0_CH0_CR_SC_PH_THROTTLING_1_unloaded_different_rank_HSH    (0x06304094)

#define MC0_CH0_CR_SC_PH_THROTTLING_2_REG                              (0x00004098)

  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_same_rank_OFF           ( 0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_same_rank_WID           ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_same_rank_MSK           (0x0000003F)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_same_rank_MIN           (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_same_rank_MAX           (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_same_rank_DEF           (0x00000002)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_same_rank_HSH           (0x06004098)

  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_same_rank_OFF         ( 8)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_same_rank_WID         ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_same_rank_MSK         (0x00003F00)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_same_rank_MIN         (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_same_rank_MAX         (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_same_rank_DEF         (0x00000000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_same_rank_HSH         (0x06104098)

  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_different_rank_OFF      (16)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_different_rank_WID      ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_different_rank_MSK      (0x003F0000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_different_rank_MIN      (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_different_rank_MAX      (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_different_rank_DEF      (0x00000006)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_loaded_different_rank_HSH      (0x06204098)

  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_different_rank_OFF    (24)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_different_rank_WID    ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_different_rank_MSK    (0x3F000000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_different_rank_MIN    (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_different_rank_MAX    (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_different_rank_DEF    (0x00000000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_2_unloaded_different_rank_HSH    (0x06304098)

#define MC0_CH0_CR_SC_PH_THROTTLING_3_REG                              (0x0000409C)

  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_same_rank_OFF           ( 0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_same_rank_WID           ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_same_rank_MSK           (0x0000003F)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_same_rank_MIN           (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_same_rank_MAX           (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_same_rank_DEF           (0x00000000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_same_rank_HSH           (0x0600409C)

  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_same_rank_OFF         ( 8)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_same_rank_WID         ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_same_rank_MSK         (0x00003F00)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_same_rank_MIN         (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_same_rank_MAX         (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_same_rank_DEF         (0x00000000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_same_rank_HSH         (0x0610409C)

  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_different_rank_OFF      (16)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_different_rank_WID      ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_different_rank_MSK      (0x003F0000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_different_rank_MIN      (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_different_rank_MAX      (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_different_rank_DEF      (0x00000000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_loaded_different_rank_HSH      (0x0620409C)

  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_different_rank_OFF    (24)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_different_rank_WID    ( 6)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_different_rank_MSK    (0x3F000000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_different_rank_MIN    (0)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_different_rank_MAX    (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_different_rank_DEF    (0x00000000)
  #define MC0_CH0_CR_SC_PH_THROTTLING_3_unloaded_different_rank_HSH    (0x0630409C)

#define MC0_CH0_CR_SC_WPQ_THRESHOLD_REG                                (0x000040A0)

  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Low_WM_OFF                       ( 0)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Low_WM_WID                       ( 6)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Low_WM_MSK                       (0x0000003F)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Low_WM_MIN                       (0)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Low_WM_MAX                       (63) // 0x0000003F
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Low_WM_DEF                       (0x0000000A)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Low_WM_HSH                       (0x060040A0)

  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Med_WM_OFF                       ( 6)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Med_WM_WID                       ( 6)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Med_WM_MSK                       (0x00000FC0)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Med_WM_MIN                       (0)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Med_WM_MAX                       (63) // 0x0000003F
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Med_WM_DEF                       (0x00000014)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_Med_WM_HSH                       (0x060C40A0)

  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_High_WM_OFF                      (12)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_High_WM_WID                      ( 6)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_High_WM_MSK                      (0x0003F000)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_High_WM_MIN                      (0)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_High_WM_MAX                      (63) // 0x0000003F
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_High_WM_DEF                      (0x00000024)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_High_WM_HSH                      (0x061840A0)

  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_low_wm_OFF     (18)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_low_wm_WID     ( 4)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_low_wm_MSK     (0x003C0000)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_low_wm_MIN     (0)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_low_wm_MAX     (15) // 0x0000000F
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_low_wm_DEF     (0x00000001)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_low_wm_HSH     (0x042440A0)

  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_med_wm_OFF     (22)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_med_wm_WID     ( 4)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_med_wm_MSK     (0x03C00000)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_med_wm_MIN     (0)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_med_wm_MAX     (15) // 0x0000000F
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_med_wm_DEF     (0x00000002)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_med_wm_HSH     (0x042C40A0)

  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_high_wm_OFF    (26)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_high_wm_WID    ( 4)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_high_wm_MSK    (0x3C000000)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_high_wm_MIN    (0)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_high_wm_MAX    (15) // 0x0000000F
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_high_wm_DEF    (0x00000004)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_PHs_allowed_under_high_wm_HSH    (0x043440A0)

  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_RPQ_PHs_weight_OFF               (30)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_RPQ_PHs_weight_WID               ( 2)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_RPQ_PHs_weight_MSK               (0xC0000000)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_RPQ_PHs_weight_MIN               (0)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_RPQ_PHs_weight_MAX               (3) // 0x00000003
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_RPQ_PHs_weight_DEF               (0x00000001)
  #define MC0_CH0_CR_SC_WPQ_THRESHOLD_RPQ_PHs_weight_HSH               (0x023C40A0)

#define MC0_CH0_CR_SC_PR_CNT_CONFIG_REG                                (0x000040A8)

  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_Ring_OFF                         ( 0)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_Ring_WID                         (10)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_Ring_MSK                         (0x000003FF)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_Ring_MIN                         (0)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_Ring_MAX                         (1023) // 0x000003FF
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_Ring_DEF                         (0x00000040)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_Ring_HSH                         (0x4A0040A8)

  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_SA_OFF                           (10)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_SA_WID                           (10)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_SA_MSK                           (0x000FFC00)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_SA_MIN                           (0)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_SA_MAX                           (1023) // 0x000003FF
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_SA_DEF                           (0x00000100)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_SA_HSH                           (0x4A1440A8)

  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC0_latency_guard_timer_x16_OFF  (20)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC0_latency_guard_timer_x16_WID  ( 9)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC0_latency_guard_timer_x16_MSK  (0x1FF00000)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC0_latency_guard_timer_x16_MIN  (0)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC0_latency_guard_timer_x16_MAX  (511) // 0x000001FF
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC0_latency_guard_timer_x16_DEF  (0x00000000)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC0_latency_guard_timer_x16_HSH  (0x492840A8)

  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_latency_guard_timer_x8_OFF   (32)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_latency_guard_timer_x8_WID   (11)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_latency_guard_timer_x8_MSK   (0x000007FF00000000ULL)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_latency_guard_timer_x8_MIN   (0)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_latency_guard_timer_x8_MAX   (2047) // 0x000007FF
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_latency_guard_timer_x8_DEF   (0x00000010)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_latency_guard_timer_x8_HSH   (0x4B4040A8)

  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_Isoc_latency_guard_timer_x8_OFF (43)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_Isoc_latency_guard_timer_x8_WID (11)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_Isoc_latency_guard_timer_x8_MSK (0x003FF80000000000ULL)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_Isoc_latency_guard_timer_x8_MIN (0)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_Isoc_latency_guard_timer_x8_MAX (2047) // 0x000007FF
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_Isoc_latency_guard_timer_x8_DEF (0x00000008)
  #define MC0_CH0_CR_SC_PR_CNT_CONFIG_VC1_Isoc_latency_guard_timer_x8_HSH (0x4B5640A8)

#define MC0_CH0_CR_REUT_CH_MISC_CKE_CTRL_REG                           (0x000040B0)

  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CTRL_CKE_Override_OFF            ( 0)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CTRL_CKE_Override_WID            ( 4)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CTRL_CKE_Override_MSK            (0x0000000F)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CTRL_CKE_Override_MIN            (0)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CTRL_CKE_Override_MAX            (15) // 0x0000000F
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CTRL_CKE_Override_DEF            (0x0000000F)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CTRL_CKE_Override_HSH            (0x040040B0)

  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CTRL_CKE_On_OFF                  (16)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CTRL_CKE_On_WID                  ( 4)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CTRL_CKE_On_MSK                  (0x000F0000)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CTRL_CKE_On_MIN                  (0)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CTRL_CKE_On_MAX                  (15) // 0x0000000F
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CTRL_CKE_On_DEF                  (0x00000000)
  #define MC0_CH0_CR_REUT_CH_MISC_CKE_CTRL_CKE_On_HSH                  (0x042040B0)

#define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_REG                           (0x000040B4)

  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_Override_OFF            ( 0)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_Override_WID            ( 4)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_Override_MSK            (0x0000000F)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_Override_MIN            (0)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_Override_MAX            (15) // 0x0000000F
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_Override_DEF            (0x00000000)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_Override_HSH            (0x040040B4)

  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_On_OFF                  (16)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_On_WID                  ( 4)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_On_MSK                  (0x000F0000)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_On_MIN                  (0)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_On_MAX                  (15) // 0x0000000F
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_On_DEF                  (0x00000000)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_On_HSH                  (0x042040B4)

  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_MPR_Train_DDR_On_OFF        (31)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_MPR_Train_DDR_On_WID        ( 1)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_MPR_Train_DDR_On_MSK        (0x80000000)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_MPR_Train_DDR_On_MIN        (0)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_MPR_Train_DDR_On_MAX        (1) // 0x00000001
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_MPR_Train_DDR_On_DEF        (0x00000000)
  #define MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_MPR_Train_DDR_On_HSH        (0x013E40B4)

#define MC0_CH0_CR_SPID_LOW_POWER_CTL_REG                              (0x000040B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_raise_cke_after_exit_latency_OFF ( 0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_raise_cke_after_exit_latency_WID ( 1)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_raise_cke_after_exit_latency_MSK (0x00000001)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_raise_cke_after_exit_latency_MIN (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_raise_cke_after_exit_latency_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_raise_cke_after_exit_latency_DEF (0x00000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_raise_cke_after_exit_latency_HSH (0x010040B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_length_OFF                ( 1)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_length_WID                ( 4)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_length_MSK                (0x0000001E)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_length_MIN                (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_length_MAX                (15) // 0x0000000F
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_length_DEF                (0x00000003)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_length_HSH                (0x040240B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_latency_OFF          ( 5)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_latency_WID          ( 5)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_latency_MSK          (0x000003E0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_latency_MIN          (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_latency_MAX          (31) // 0x0000001F
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_latency_DEF          (0x00000001)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_latency_HSH          (0x050A40B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_length_OFF           (10)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_length_WID           ( 4)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_length_MSK           (0x00003C00)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_length_MIN           (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_length_MAX           (15) // 0x0000000F
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_length_DEF           (0x00000001)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_length_HSH           (0x041440B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_latency_OFF        (14)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_latency_WID        ( 6)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_latency_MSK        (0x000FC000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_latency_MIN        (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_latency_MAX        (63) // 0x0000003F
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_latency_DEF        (0x00000001)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_latency_HSH        (0x061C40B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_length_OFF         (20)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_length_WID         ( 4)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_length_MSK         (0x00F00000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_length_MIN         (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_length_MAX         (15) // 0x0000000F
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_length_DEF         (0x00000001)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_length_HSH         (0x042840B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_length_OFF            (24)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_length_WID            ( 4)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_length_MSK            (0x0F000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_length_MIN            (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_length_MAX            (15) // 0x0000000F
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_length_DEF            (0x00000008)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_length_HSH            (0x043040B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_enable_OFF            (28)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_enable_WID            ( 1)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_enable_MSK            (0x10000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_enable_MIN            (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_enable_MAX            (1) // 0x00000001
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_enable_DEF            (0x00000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_enable_HSH            (0x013840B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_enable_OFF                (29)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_enable_WID                ( 1)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_enable_MSK                (0x20000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_enable_MIN                (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_enable_MAX                (1) // 0x00000001
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_enable_DEF                (0x00000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_enable_HSH                (0x013A40B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_enable_OFF           (30)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_enable_WID           ( 1)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_enable_MSK           (0x40000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_enable_MIN           (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_enable_MAX           (1) // 0x00000001
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_enable_DEF           (0x00000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_enable_HSH           (0x013C40B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_enable_OFF         (31)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_enable_WID         ( 1)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_enable_MSK         (0x80000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_enable_MIN         (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_enable_MAX         (1) // 0x00000001
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_enable_DEF         (0x00000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_enable_HSH         (0x013E40B8)

#define MC0_CH0_CR_SPID_LOW_POWER_CTL_A0_REG                           (0x000040B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_raise_cke_after_exit_latency_A0_OFF ( 0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_raise_cke_after_exit_latency_A0_WID ( 1)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_raise_cke_after_exit_latency_A0_MSK (0x00000001)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_raise_cke_after_exit_latency_A0_MIN (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_raise_cke_after_exit_latency_A0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_raise_cke_after_exit_latency_A0_DEF (0x00000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_raise_cke_after_exit_latency_A0_HSH (0x010040B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_latency_A0_OFF            ( 1)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_latency_A0_WID            ( 3)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_latency_A0_MSK            (0x0000000E)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_latency_A0_MIN            (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_latency_A0_MAX            (7) // 0x00000007
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_latency_A0_DEF            (0x00000001)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_latency_A0_HSH            (0x030240B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_length_A0_OFF             ( 4)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_length_A0_WID             ( 4)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_length_A0_MSK             (0x000000F0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_length_A0_MIN             (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_length_A0_MAX             (15) // 0x0000000F
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_length_A0_DEF             (0x00000004)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_length_A0_HSH             (0x040840B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_latency_A0_OFF       ( 8)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_latency_A0_WID       ( 4)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_latency_A0_MSK       (0x00000F00)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_latency_A0_MIN       (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_latency_A0_MAX       (15) // 0x0000000F
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_latency_A0_DEF       (0x00000004)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_latency_A0_HSH       (0x041040B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_length_A0_OFF        (12)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_length_A0_WID        ( 4)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_length_A0_MSK        (0x0000F000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_length_A0_MIN        (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_length_A0_MAX        (15) // 0x0000000F
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_length_A0_DEF        (0x00000001)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_length_A0_HSH        (0x041840B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_latency_A0_OFF     (16)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_latency_A0_WID     ( 4)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_latency_A0_MSK     (0x000F0000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_latency_A0_MIN     (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_latency_A0_MAX     (15) // 0x0000000F
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_latency_A0_DEF     (0x00000004)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_latency_A0_HSH     (0x042040B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_length_A0_OFF      (20)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_length_A0_WID      ( 4)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_length_A0_MSK      (0x00F00000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_length_A0_MIN      (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_length_A0_MAX      (15) // 0x0000000F
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_length_A0_DEF      (0x00000001)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_length_A0_HSH      (0x042840B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_length_A0_OFF         (24)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_length_A0_WID         ( 4)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_length_A0_MSK         (0x0F000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_length_A0_MIN         (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_length_A0_MAX         (15) // 0x0000000F
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_length_A0_DEF         (0x00000008)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_length_A0_HSH         (0x043040B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_enable_A0_OFF         (28)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_enable_A0_WID         ( 1)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_enable_A0_MSK         (0x10000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_enable_A0_MIN         (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_enable_A0_MAX         (1) // 0x00000001
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_enable_A0_DEF         (0x00000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_ckevalid_enable_A0_HSH         (0x013840B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_enable_A0_OFF             (29)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_enable_A0_WID             ( 1)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_enable_A0_MSK             (0x20000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_enable_A0_MIN             (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_enable_A0_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_enable_A0_DEF             (0x00000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_idle_enable_A0_HSH             (0x013A40B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_enable_A0_OFF        (30)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_enable_A0_WID        ( 1)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_enable_A0_MSK        (0x40000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_enable_A0_MIN        (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_enable_A0_MAX        (1) // 0x00000001
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_enable_A0_DEF        (0x00000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_powerdown_enable_A0_HSH        (0x013C40B8)

  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_enable_A0_OFF      (31)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_enable_A0_WID      ( 1)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_enable_A0_MSK      (0x80000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_enable_A0_MIN      (0)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_enable_A0_MAX      (1) // 0x00000001
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_enable_A0_DEF      (0x00000000)
  #define MC0_CH0_CR_SPID_LOW_POWER_CTL_selfrefresh_enable_A0_HSH      (0x013E40B8)

#define MC0_CH0_CR_SC_GS_CFG_TRAINING_REG                              (0x000040BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_OFF           ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_WID           ( 4)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_MSK           (0x0000001E)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_MIN           (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_MAX           (15) // 0x0000000F
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_DEF           (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_HSH           (0x040240BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_delay_OFF                ( 5)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_delay_WID                ( 3)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_delay_MSK                (0x000000E0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_delay_MIN                (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_delay_MAX                (7) // 0x00000007
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_delay_DEF                (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_delay_HSH                (0x030A40BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_ignore_cke_OFF                 ( 8)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_ignore_cke_WID                 ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_ignore_cke_MSK                 (0x00000100)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_ignore_cke_MIN                 (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_ignore_cke_MAX                 (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_ignore_cke_DEF                 (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_ignore_cke_HSH                 (0x011040BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_mask_cs_OFF                    ( 9)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_mask_cs_WID                    ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_mask_cs_MSK                    (0x00000200)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_mask_cs_MIN                    (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_mask_cs_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_mask_cs_DEF                    (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_mask_cs_HSH                    (0x011240BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_lp4_fifo_rd_wr_OFF             (10)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_lp4_fifo_rd_wr_WID             ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_lp4_fifo_rd_wr_MSK             (0x00000400)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_lp4_fifo_rd_wr_MIN             (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_lp4_fifo_rd_wr_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_lp4_fifo_rd_wr_DEF             (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_lp4_fifo_rd_wr_HSH             (0x011440BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_disable_tristate_OFF           (11)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_disable_tristate_WID           ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_disable_tristate_MSK           (0x00000800)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_disable_tristate_MIN           (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_disable_tristate_MAX           (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_disable_tristate_DEF           (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_disable_tristate_HSH           (0x011640BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cpgc_in_order_OFF              (12)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cpgc_in_order_WID              ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cpgc_in_order_MSK              (0x00001000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cpgc_in_order_MIN              (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cpgc_in_order_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cpgc_in_order_DEF              (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cpgc_in_order_HSH              (0x011840BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cadb_enable_OFF                (13)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cadb_enable_WID                ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cadb_enable_MSK                (0x00002000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cadb_enable_MIN                (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cadb_enable_MAX                (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cadb_enable_DEF                (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cadb_enable_HSH                (0x011A40BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_deselect_enable_OFF            (14)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_deselect_enable_WID            ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_deselect_enable_MSK            (0x00004000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_deselect_enable_MIN            (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_deselect_enable_MAX            (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_deselect_enable_DEF            (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_deselect_enable_HSH            (0x011C40BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Reset_CADB_OFF                 (15)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Reset_CADB_WID                 ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Reset_CADB_MSK                 (0x00008000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Reset_CADB_MIN                 (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Reset_CADB_MAX                 (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Reset_CADB_DEF                 (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Reset_CADB_HSH                 (0x011E40BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_bus_retain_on_n_to_1_bubble_OFF (16)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_bus_retain_on_n_to_1_bubble_WID ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_bus_retain_on_n_to_1_bubble_MSK (0x00010000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_bus_retain_on_n_to_1_bubble_MIN (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_bus_retain_on_n_to_1_bubble_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_bus_retain_on_n_to_1_bubble_DEF (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_bus_retain_on_n_to_1_bubble_HSH (0x012040BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_xarb_OFF                 (17)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_xarb_WID                 ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_xarb_MSK                 (0x00020000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_xarb_MIN                 (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_xarb_MAX                 (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_xarb_DEF                 (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_xarb_HSH                 (0x012240BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_cke_OFF                  (18)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_cke_WID                  ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_cke_MSK                  (0x00040000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_cke_MIN                  (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_cke_MAX                  (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_cke_DEF                  (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_cke_HSH                  (0x012440BC)

#define MC0_CH0_CR_SC_GS_CFG_TRAINING_A0_REG                           (0x000040BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_A0_OFF        ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_A0_WID        ( 4)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_A0_MSK        (0x0000001E)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_A0_MIN        (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_A0_MAX        (15) // 0x0000000F
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_A0_DEF        (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_A0_HSH        (0x040240BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_delay_A0_OFF             ( 5)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_delay_A0_WID             ( 3)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_delay_A0_MSK             (0x000000E0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_delay_A0_MIN             (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_delay_A0_MAX             (7) // 0x00000007
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_delay_A0_DEF             (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_reset_delay_A0_HSH             (0x030A40BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_ignore_cke_A0_OFF              ( 8)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_ignore_cke_A0_WID              ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_ignore_cke_A0_MSK              (0x00000100)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_ignore_cke_A0_MIN              (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_ignore_cke_A0_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_ignore_cke_A0_DEF              (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_ignore_cke_A0_HSH              (0x011040BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_mask_cs_A0_OFF                 ( 9)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_mask_cs_A0_WID                 ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_mask_cs_A0_MSK                 (0x00000200)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_mask_cs_A0_MIN                 (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_mask_cs_A0_MAX                 (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_mask_cs_A0_DEF                 (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_mask_cs_A0_HSH                 (0x011240BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_lp4_fifo_rd_wr_A0_OFF          (10)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_lp4_fifo_rd_wr_A0_WID          ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_lp4_fifo_rd_wr_A0_MSK          (0x00000400)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_lp4_fifo_rd_wr_A0_MIN          (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_lp4_fifo_rd_wr_A0_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_lp4_fifo_rd_wr_A0_DEF          (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_lp4_fifo_rd_wr_A0_HSH          (0x011440BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_disable_tristate_A0_OFF        (11)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_disable_tristate_A0_WID        ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_disable_tristate_A0_MSK        (0x00000800)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_disable_tristate_A0_MIN        (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_disable_tristate_A0_MAX        (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_disable_tristate_A0_DEF        (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_disable_tristate_A0_HSH        (0x011640BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cpgc_in_order_A0_OFF           (12)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cpgc_in_order_A0_WID           ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cpgc_in_order_A0_MSK           (0x00001000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cpgc_in_order_A0_MIN           (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cpgc_in_order_A0_MAX           (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cpgc_in_order_A0_DEF           (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cpgc_in_order_A0_HSH           (0x011840BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cadb_enable_A0_OFF             (13)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cadb_enable_A0_WID             ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cadb_enable_A0_MSK             (0x00002000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cadb_enable_A0_MIN             (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cadb_enable_A0_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cadb_enable_A0_DEF             (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_cadb_enable_A0_HSH             (0x011A40BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_deselect_enable_A0_OFF         (14)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_deselect_enable_A0_WID         ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_deselect_enable_A0_MSK         (0x00004000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_deselect_enable_A0_MIN         (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_deselect_enable_A0_MAX         (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_deselect_enable_A0_DEF         (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_deselect_enable_A0_HSH         (0x011C40BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Reset_CADB_A0_OFF              (15)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Reset_CADB_A0_WID              ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Reset_CADB_A0_MSK              (0x00008000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Reset_CADB_A0_MIN              (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Reset_CADB_A0_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Reset_CADB_A0_DEF              (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Reset_CADB_A0_HSH              (0x011E40BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_bus_retain_on_n_to_1_bubble_A0_OFF (16)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_bus_retain_on_n_to_1_bubble_A0_WID ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_bus_retain_on_n_to_1_bubble_A0_MSK (0x00010000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_bus_retain_on_n_to_1_bubble_A0_MIN (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_bus_retain_on_n_to_1_bubble_A0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_bus_retain_on_n_to_1_bubble_A0_DEF (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_bus_retain_on_n_to_1_bubble_A0_HSH (0x012040BC)

  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_xarb_A0_OFF              (17)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_xarb_A0_WID              ( 1)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_xarb_A0_MSK              (0x00020000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_xarb_A0_MIN              (0)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_xarb_A0_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_xarb_A0_DEF              (0x00000000)
  #define MC0_CH0_CR_SC_GS_CFG_TRAINING_Block_xarb_A0_HSH              (0x012240BC)

#define MC0_CH0_CR_SCHED_THIRD_CBIT_REG                                (0x000040C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_isoc_block_relaxation_OFF    ( 0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_isoc_block_relaxation_WID    ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_isoc_block_relaxation_MSK    (0x00000001)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_isoc_block_relaxation_MIN    (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_isoc_block_relaxation_MAX    (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_isoc_block_relaxation_DEF    (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_isoc_block_relaxation_HSH    (0x010040C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_lp_read_blkr_OFF                 ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_lp_read_blkr_WID                 ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_lp_read_blkr_MSK                 (0x00000002)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_lp_read_blkr_MIN                 (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_lp_read_blkr_MAX                 (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_lp_read_blkr_DEF                 (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_lp_read_blkr_HSH                 (0x010240C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_pe_read_for_pe_blkr_OFF          ( 2)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_pe_read_for_pe_blkr_WID          ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_pe_read_for_pe_blkr_MSK          (0x00000004)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_pe_read_for_pe_blkr_MIN          (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_pe_read_for_pe_blkr_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_pe_read_for_pe_blkr_DEF          (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_pe_read_for_pe_blkr_HSH          (0x010440C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_write_ph_blocks_read_pre_OFF     ( 3)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_write_ph_blocks_read_pre_WID     ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_write_ph_blocks_read_pre_MSK     (0x00000008)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_write_ph_blocks_read_pre_MIN     (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_write_ph_blocks_read_pre_MAX     (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_write_ph_blocks_read_pre_DEF     (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_write_ph_blocks_read_pre_HSH     (0x010640C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_Read_threshold_for_lp_read_bklr_OFF ( 4)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_Read_threshold_for_lp_read_bklr_WID ( 6)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_Read_threshold_for_lp_read_bklr_MSK (0x000003F0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_Read_threshold_for_lp_read_bklr_MIN (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_Read_threshold_for_lp_read_bklr_MAX (63) // 0x0000003F
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_Read_threshold_for_lp_read_bklr_DEF (0x00000008)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_Read_threshold_for_lp_read_bklr_HSH (0x060840C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_ignore_1st_zqcs_OFF          (10)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_ignore_1st_zqcs_WID          ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_ignore_1st_zqcs_MSK          (0x00000400)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_ignore_1st_zqcs_MIN          (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_ignore_1st_zqcs_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_ignore_1st_zqcs_DEF          (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_ignore_1st_zqcs_HSH          (0x011440C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_preempt_vc1_during_demote_OFF    (11)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_preempt_vc1_during_demote_WID    ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_preempt_vc1_during_demote_MSK    (0x00000800)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_preempt_vc1_during_demote_MIN    (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_preempt_vc1_during_demote_MAX    (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_preempt_vc1_during_demote_DEF    (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_preempt_vc1_during_demote_HSH    (0x011640C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_idle_ref_start_OFF           (12)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_idle_ref_start_WID           ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_idle_ref_start_MSK           (0x00001000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_idle_ref_start_MIN           (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_idle_ref_start_MAX           (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_idle_ref_start_DEF           (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_idle_ref_start_HSH           (0x011840C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_invert_ALERT_n_OFF               (13)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_invert_ALERT_n_WID               ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_invert_ALERT_n_MSK               (0x00002000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_invert_ALERT_n_MIN               (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_invert_ALERT_n_MAX               (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_invert_ALERT_n_DEF               (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_invert_ALERT_n_HSH               (0x011A40C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_oldest_isoch_pre_over_ph_OFF (14)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_oldest_isoch_pre_over_ph_WID ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_oldest_isoch_pre_over_ph_MSK (0x00004000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_oldest_isoch_pre_over_ph_MIN (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_oldest_isoch_pre_over_ph_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_oldest_isoch_pre_over_ph_DEF (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_oldest_isoch_pre_over_ph_HSH (0x011C40C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_seperate_zq_block_OFF        (15)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_seperate_zq_block_WID        ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_seperate_zq_block_MSK        (0x00008000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_seperate_zq_block_MIN        (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_seperate_zq_block_MAX        (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_seperate_zq_block_DEF        (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_seperate_zq_block_HSH        (0x011E40C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_cke_off_in_refresh_OFF       (16)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_cke_off_in_refresh_WID       ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_cke_off_in_refresh_MSK       (0x00010000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_cke_off_in_refresh_MIN       (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_cke_off_in_refresh_MAX       (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_cke_off_in_refresh_DEF       (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_cke_off_in_refresh_HSH       (0x012040C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_allow_ecc_dft_overrides_OFF      (17)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_allow_ecc_dft_overrides_WID      ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_allow_ecc_dft_overrides_MSK      (0x00020000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_allow_ecc_dft_overrides_MIN      (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_allow_ecc_dft_overrides_MAX      (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_allow_ecc_dft_overrides_DEF      (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_allow_ecc_dft_overrides_HSH      (0x012240C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_wdb_clk_gate_OFF             (18)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_wdb_clk_gate_WID             ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_wdb_clk_gate_MSK             (0x00040000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_wdb_clk_gate_MIN             (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_wdb_clk_gate_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_wdb_clk_gate_DEF             (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_wdb_clk_gate_HSH             (0x012440C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_mnt_clk_gate_OFF             (19)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_mnt_clk_gate_WID             ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_mnt_clk_gate_MSK             (0x00080000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_mnt_clk_gate_MIN             (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_mnt_clk_gate_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_mnt_clk_gate_DEF             (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_mnt_clk_gate_HSH             (0x012640C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_scheds_clk_gate_OFF          (20)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_scheds_clk_gate_WID          ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_scheds_clk_gate_MSK          (0x00100000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_scheds_clk_gate_MIN          (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_scheds_clk_gate_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_scheds_clk_gate_DEF          (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_scheds_clk_gate_HSH          (0x012840C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_lpmode_on_sagv_OFF           (21)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_lpmode_on_sagv_WID           ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_lpmode_on_sagv_MSK           (0x00200000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_lpmode_on_sagv_MIN           (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_lpmode_on_sagv_MAX           (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_lpmode_on_sagv_DEF           (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_lpmode_on_sagv_HSH           (0x012A40C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ignore_fragment_safe_in_ref_OFF  (22)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ignore_fragment_safe_in_ref_WID  ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ignore_fragment_safe_in_ref_MSK  (0x00400000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ignore_fragment_safe_in_ref_MIN  (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ignore_fragment_safe_in_ref_MAX  (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ignore_fragment_safe_in_ref_DEF  (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ignore_fragment_safe_in_ref_HSH  (0x012C40C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cmi_short_rmw_stall_OFF          (23)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cmi_short_rmw_stall_WID          ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cmi_short_rmw_stall_MSK          (0x00800000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cmi_short_rmw_stall_MIN          (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cmi_short_rmw_stall_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cmi_short_rmw_stall_DEF          (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cmi_short_rmw_stall_HSH          (0x012E40C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ipq_ignore_write_ph_OFF          (24)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ipq_ignore_write_ph_WID          ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ipq_ignore_write_ph_MSK          (0x01000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ipq_ignore_write_ph_MIN          (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ipq_ignore_write_ph_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ipq_ignore_write_ph_DEF          (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ipq_ignore_write_ph_HSH          (0x013040C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverride_OFF        (25)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverride_WID        ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverride_MSK        (0x02000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverride_MIN        (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverride_MAX        (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverride_DEF        (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverride_HSH        (0x013240C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverridevalue_OFF   (26)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverridevalue_WID   ( 2)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverridevalue_MSK   (0x0C000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverridevalue_MIN   (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverridevalue_MAX   (3) // 0x00000003
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverridevalue_DEF   (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverridevalue_HSH   (0x023440C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_asdynamicmodeinsertbubble_OFF    (28)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_asdynamicmodeinsertbubble_WID    ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_asdynamicmodeinsertbubble_MSK    (0x10000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_asdynamicmodeinsertbubble_MIN    (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_asdynamicmodeinsertbubble_MAX    (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_asdynamicmodeinsertbubble_DEF    (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_asdynamicmodeinsertbubble_HSH    (0x013840C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_read_pre_in_vc0_read_starvation_OFF (29)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_read_pre_in_vc0_read_starvation_WID ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_read_pre_in_vc0_read_starvation_MSK (0x20000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_read_pre_in_vc0_read_starvation_MIN (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_read_pre_in_vc0_read_starvation_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_read_pre_in_vc0_read_starvation_DEF (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_read_pre_in_vc0_read_starvation_HSH (0x013A40C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_spare_OFF                        (30)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_spare_WID                        ( 2)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_spare_MSK                        (0xC0000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_spare_MIN                        (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_spare_MAX                        (3) // 0x00000003
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_spare_DEF                        (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_spare_HSH                        (0x023C40C0)

#define MC0_CH0_CR_SCHED_THIRD_CBIT_A0_REG                             (0x000040C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_isoc_block_relaxation_A0_OFF ( 0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_isoc_block_relaxation_A0_WID ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_isoc_block_relaxation_A0_MSK (0x00000001)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_isoc_block_relaxation_A0_MIN (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_isoc_block_relaxation_A0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_isoc_block_relaxation_A0_DEF (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_isoc_block_relaxation_A0_HSH (0x010040C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_lp_read_blkr_A0_OFF              ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_lp_read_blkr_A0_WID              ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_lp_read_blkr_A0_MSK              (0x00000002)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_lp_read_blkr_A0_MIN              (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_lp_read_blkr_A0_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_lp_read_blkr_A0_DEF              (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_lp_read_blkr_A0_HSH              (0x010240C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_pe_read_for_pe_blkr_A0_OFF       ( 2)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_pe_read_for_pe_blkr_A0_WID       ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_pe_read_for_pe_blkr_A0_MSK       (0x00000004)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_pe_read_for_pe_blkr_A0_MIN       (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_pe_read_for_pe_blkr_A0_MAX       (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_pe_read_for_pe_blkr_A0_DEF       (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_pe_read_for_pe_blkr_A0_HSH       (0x010440C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_write_ph_blocks_read_pre_A0_OFF  ( 3)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_write_ph_blocks_read_pre_A0_WID  ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_write_ph_blocks_read_pre_A0_MSK  (0x00000008)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_write_ph_blocks_read_pre_A0_MIN  (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_write_ph_blocks_read_pre_A0_MAX  (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_write_ph_blocks_read_pre_A0_DEF  (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_write_ph_blocks_read_pre_A0_HSH  (0x010640C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_Read_threshold_for_lp_read_bklr_A0_OFF ( 4)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_Read_threshold_for_lp_read_bklr_A0_WID ( 6)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_Read_threshold_for_lp_read_bklr_A0_MSK (0x000003F0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_Read_threshold_for_lp_read_bklr_A0_MIN (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_Read_threshold_for_lp_read_bklr_A0_MAX (63) // 0x0000003F
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_Read_threshold_for_lp_read_bklr_A0_DEF (0x00000008)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_Read_threshold_for_lp_read_bklr_A0_HSH (0x060840C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_ignore_1st_zqcs_A0_OFF       (10)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_ignore_1st_zqcs_A0_WID       ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_ignore_1st_zqcs_A0_MSK       (0x00000400)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_ignore_1st_zqcs_A0_MIN       (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_ignore_1st_zqcs_A0_MAX       (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_ignore_1st_zqcs_A0_DEF       (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_ignore_1st_zqcs_A0_HSH       (0x011440C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_preempt_vc1_during_demote_A0_OFF (11)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_preempt_vc1_during_demote_A0_WID ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_preempt_vc1_during_demote_A0_MSK (0x00000800)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_preempt_vc1_during_demote_A0_MIN (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_preempt_vc1_during_demote_A0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_preempt_vc1_during_demote_A0_DEF (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_preempt_vc1_during_demote_A0_HSH (0x011640C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_idle_ref_start_A0_OFF        (12)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_idle_ref_start_A0_WID        ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_idle_ref_start_A0_MSK        (0x00001000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_idle_ref_start_A0_MIN        (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_idle_ref_start_A0_MAX        (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_idle_ref_start_A0_DEF        (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_idle_ref_start_A0_HSH        (0x011840C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_invert_ALERT_n_A0_OFF            (13)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_invert_ALERT_n_A0_WID            ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_invert_ALERT_n_A0_MSK            (0x00002000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_invert_ALERT_n_A0_MIN            (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_invert_ALERT_n_A0_MAX            (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_invert_ALERT_n_A0_DEF            (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_invert_ALERT_n_A0_HSH            (0x011A40C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_oldest_isoch_pre_over_ph_A0_OFF (14)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_oldest_isoch_pre_over_ph_A0_WID ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_oldest_isoch_pre_over_ph_A0_MSK (0x00004000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_oldest_isoch_pre_over_ph_A0_MIN (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_oldest_isoch_pre_over_ph_A0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_oldest_isoch_pre_over_ph_A0_DEF (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_oldest_isoch_pre_over_ph_A0_HSH (0x011C40C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_seperate_zq_block_A0_OFF     (15)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_seperate_zq_block_A0_WID     ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_seperate_zq_block_A0_MSK     (0x00008000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_seperate_zq_block_A0_MIN     (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_seperate_zq_block_A0_MAX     (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_seperate_zq_block_A0_DEF     (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_seperate_zq_block_A0_HSH     (0x011E40C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_cke_off_in_refresh_A0_OFF    (16)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_cke_off_in_refresh_A0_WID    ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_cke_off_in_refresh_A0_MSK    (0x00010000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_cke_off_in_refresh_A0_MIN    (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_cke_off_in_refresh_A0_MAX    (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_cke_off_in_refresh_A0_DEF    (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_cke_off_in_refresh_A0_HSH    (0x012040C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_allow_ecc_dft_overrides_A0_OFF   (17)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_allow_ecc_dft_overrides_A0_WID   ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_allow_ecc_dft_overrides_A0_MSK   (0x00020000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_allow_ecc_dft_overrides_A0_MIN   (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_allow_ecc_dft_overrides_A0_MAX   (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_allow_ecc_dft_overrides_A0_DEF   (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_allow_ecc_dft_overrides_A0_HSH   (0x012240C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_wdb_clk_gate_A0_OFF          (18)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_wdb_clk_gate_A0_WID          ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_wdb_clk_gate_A0_MSK          (0x00040000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_wdb_clk_gate_A0_MIN          (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_wdb_clk_gate_A0_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_wdb_clk_gate_A0_DEF          (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_wdb_clk_gate_A0_HSH          (0x012440C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_mnt_clk_gate_A0_OFF          (19)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_mnt_clk_gate_A0_WID          ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_mnt_clk_gate_A0_MSK          (0x00080000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_mnt_clk_gate_A0_MIN          (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_mnt_clk_gate_A0_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_mnt_clk_gate_A0_DEF          (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_mnt_clk_gate_A0_HSH          (0x012640C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_scheds_clk_gate_A0_OFF       (20)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_scheds_clk_gate_A0_WID       ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_scheds_clk_gate_A0_MSK       (0x00100000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_scheds_clk_gate_A0_MIN       (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_scheds_clk_gate_A0_MAX       (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_scheds_clk_gate_A0_DEF       (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_scheds_clk_gate_A0_HSH       (0x012840C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_lpmode_on_sagv_A0_OFF        (21)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_lpmode_on_sagv_A0_WID        ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_lpmode_on_sagv_A0_MSK        (0x00200000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_lpmode_on_sagv_A0_MIN        (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_lpmode_on_sagv_A0_MAX        (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_lpmode_on_sagv_A0_DEF        (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_dis_lpmode_on_sagv_A0_HSH        (0x012A40C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ignore_fragment_safe_in_ref_A0_OFF (22)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ignore_fragment_safe_in_ref_A0_WID ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ignore_fragment_safe_in_ref_A0_MSK (0x00400000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ignore_fragment_safe_in_ref_A0_MIN (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ignore_fragment_safe_in_ref_A0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ignore_fragment_safe_in_ref_A0_DEF (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ignore_fragment_safe_in_ref_A0_HSH (0x012C40C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cmi_short_rmw_stall_A0_OFF       (23)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cmi_short_rmw_stall_A0_WID       ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cmi_short_rmw_stall_A0_MSK       (0x00800000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cmi_short_rmw_stall_A0_MIN       (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cmi_short_rmw_stall_A0_MAX       (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cmi_short_rmw_stall_A0_DEF       (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cmi_short_rmw_stall_A0_HSH       (0x012E40C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ipq_ignore_write_ph_A0_OFF       (24)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ipq_ignore_write_ph_A0_WID       ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ipq_ignore_write_ph_A0_MSK       (0x01000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ipq_ignore_write_ph_A0_MIN       (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ipq_ignore_write_ph_A0_MAX       (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ipq_ignore_write_ph_A0_DEF       (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_ipq_ignore_write_ph_A0_HSH       (0x013040C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverride_A0_OFF     (25)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverride_A0_WID     ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverride_A0_MSK     (0x02000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverride_A0_MIN     (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverride_A0_MAX     (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverride_A0_DEF     (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverride_A0_HSH     (0x013240C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverridevalue_A0_OFF (26)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverridevalue_A0_WID ( 2)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverridevalue_A0_MSK (0x0C000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverridevalue_A0_MIN (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverridevalue_A0_MAX (3) // 0x00000003
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverridevalue_A0_DEF (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_cksynccounteroverridevalue_A0_HSH (0x023440C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_asdynamicmodeinsertbubble_A0_OFF (28)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_asdynamicmodeinsertbubble_A0_WID ( 1)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_asdynamicmodeinsertbubble_A0_MSK (0x10000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_asdynamicmodeinsertbubble_A0_MIN (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_asdynamicmodeinsertbubble_A0_MAX (1) // 0x00000001
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_asdynamicmodeinsertbubble_A0_DEF (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_asdynamicmodeinsertbubble_A0_HSH (0x013840C0)

  #define MC0_CH0_CR_SCHED_THIRD_CBIT_spare_A0_OFF                     (30)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_spare_A0_WID                     ( 2)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_spare_A0_MSK                     (0xC0000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_spare_A0_MIN                     (0)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_spare_A0_MAX                     (3) // 0x00000003
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_spare_A0_DEF                     (0x00000000)
  #define MC0_CH0_CR_SCHED_THIRD_CBIT_spare_A0_HSH                     (0x023C40C0)

#define MC0_CH0_CR_DEADLOCK_BREAKER_REG                                (0x000040C4)

  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_OFF             ( 0)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_WID             (16)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_MSK             (0x0000FFFF)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_MIN             (0)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_MAX             (65535) // 0x0000FFFF
  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_DEF             (0x00000000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_HSH             (0x100040C4)

  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_en_OFF          (16)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_en_WID          ( 1)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_en_MSK          (0x00010000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_en_MIN          (0)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_en_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_en_DEF          (0x00000000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_No_CAS_threshold_en_HSH          (0x012040C4)

  #define MC0_CH0_CR_DEADLOCK_BREAKER_Preemption_threshold_en_OFF      (17)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Preemption_threshold_en_WID      ( 1)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Preemption_threshold_en_MSK      (0x00020000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Preemption_threshold_en_MIN      (0)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Preemption_threshold_en_MAX      (1) // 0x00000001
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Preemption_threshold_en_DEF      (0x00000000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Preemption_threshold_en_HSH      (0x012240C4)

  #define MC0_CH0_CR_DEADLOCK_BREAKER_Stop_count_during_tt_OFF         (18)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Stop_count_during_tt_WID         ( 1)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Stop_count_during_tt_MSK         (0x00040000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Stop_count_during_tt_MIN         (0)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Stop_count_during_tt_MAX         (1) // 0x00000001
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Stop_count_during_tt_DEF         (0x00000000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Stop_count_during_tt_HSH         (0x012440C4)

  #define MC0_CH0_CR_DEADLOCK_BREAKER_Attempt_refresh_on_deadlock_OFF  (19)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Attempt_refresh_on_deadlock_WID  ( 1)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Attempt_refresh_on_deadlock_MSK  (0x00080000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Attempt_refresh_on_deadlock_MIN  (0)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Attempt_refresh_on_deadlock_MAX  (1) // 0x00000001
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Attempt_refresh_on_deadlock_DEF  (0x00000000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Attempt_refresh_on_deadlock_HSH  (0x012640C4)

  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_duration_OFF     (20)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_duration_WID     ( 8)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_duration_MSK     (0x0FF00000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_duration_MIN     (0)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_duration_MAX     (255) // 0x000000FF
  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_duration_DEF     (0x00000000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_duration_HSH     (0x082840C4)

  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_en_OFF           (28)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_en_WID           ( 1)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_en_MSK           (0x10000000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_en_MIN           (0)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_en_MAX           (1) // 0x00000001
  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_en_DEF           (0x00000000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_MajorMode_force_en_HSH           (0x013840C4)

  #define MC0_CH0_CR_DEADLOCK_BREAKER_Disable_blocking_rules_OFF       (29)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Disable_blocking_rules_WID       ( 1)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Disable_blocking_rules_MSK       (0x20000000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Disable_blocking_rules_MIN       (0)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Disable_blocking_rules_MAX       (1) // 0x00000001
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Disable_blocking_rules_DEF       (0x00000000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Disable_blocking_rules_HSH       (0x013A40C4)

  #define MC0_CH0_CR_DEADLOCK_BREAKER_Rank_join_OFF                    (30)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Rank_join_WID                    ( 2)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Rank_join_MSK                    (0xC0000000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Rank_join_MIN                    (0)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Rank_join_MAX                    (3) // 0x00000003
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Rank_join_DEF                    (0x00000000)
  #define MC0_CH0_CR_DEADLOCK_BREAKER_Rank_join_HSH                    (0x023C40C4)

#define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_REG                              (0x000040C8)

  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDWR_OFF                  ( 0)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDWR_WID                  ( 6)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDWR_MSK                  (0x0000003F)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDWR_MIN                  (0)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDWR_MAX                  (63) // 0x0000003F
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDWR_DEF                  (0x00000004)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDWR_HSH                  (0x060040C8)

  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bits01_OFF ( 6)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bits01_WID ( 2)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bits01_MSK (0x000000C0)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bits01_MIN (0)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bits01_MAX (3) // 0x00000003
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bits01_DEF (0x00000000)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bits01_HSH (0x020C40C8)

  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRWR_OFF                  ( 8)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRWR_WID                  ( 6)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRWR_MSK                  (0x00003F00)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRWR_MIN                  (0)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRWR_MAX                  (63) // 0x0000003F
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRWR_DEF                  (0x00000004)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRWR_HSH                  (0x061040C8)

  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bit2_OFF   (14)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bit2_WID   ( 1)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bit2_MSK   (0x00004000)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bit2_MIN   (0)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bit2_MAX   (1) // 0x00000001
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bit2_DEF   (0x00000000)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_bubble_cnt_visa_out_bit2_HSH   (0x011C40C8)

  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRRD_OFF                  (16)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRRD_WID                  ( 8)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRRD_MSK                  (0x00FF0000)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRRD_MIN                  (0)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRRD_MAX                  (255) // 0x000000FF
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRRD_DEF                  (0x00000004)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tWRRD_HSH                  (0x082040C8)

  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDRD_OFF                  (24)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDRD_WID                  ( 6)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDRD_MSK                  (0x3F000000)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDRD_MIN                  (0)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDRD_MAX                  (63) // 0x0000003F
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDRD_DEF                  (0x00000004)
  #define MC0_CH0_CR_XARB_TC_BUBBLE_INJ_max_tRDRD_HSH                  (0x063040C8)

#define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_REG                             (0x000040CC)

  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_read_switch_OFF ( 0)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_read_switch_WID ( 1)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_read_switch_MSK (0x00000001)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_read_switch_MIN (0)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_read_switch_MAX (1) // 0x00000001
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_read_switch_DEF (0x00000001)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_read_switch_HSH (0x010040CC)

  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_write_switch_OFF ( 1)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_write_switch_WID ( 1)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_write_switch_MSK (0x00000002)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_write_switch_MIN (0)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_write_switch_MAX (1) // 0x00000001
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_write_switch_DEF (0x00000001)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_write_switch_HSH (0x010240CC)

  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_any_cas_switch_OFF ( 2)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_any_cas_switch_WID ( 1)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_any_cas_switch_MSK (0x00000004)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_any_cas_switch_MIN (0)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_any_cas_switch_MAX (1) // 0x00000001
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_any_cas_switch_DEF (0x00000001)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_enable_any_cas_switch_HSH (0x010440CC)

  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Rank_mode_OFF                 ( 3)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Rank_mode_WID                 ( 1)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Rank_mode_MSK                 (0x00000008)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Rank_mode_MIN                 (0)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Rank_mode_MAX                 (1) // 0x00000001
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Rank_mode_DEF                 (0x00000001)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Rank_mode_HSH                 (0x010640CC)

  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_OFF                 ( 4)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_WID                 ( 1)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_MSK                 (0x00000010)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_MIN                 (0)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_MAX                 (1) // 0x00000001
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_DEF                 (0x00000000)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_HSH                 (0x010840CC)

  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_multiplier_OFF      ( 5)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_multiplier_WID      ( 2)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_multiplier_MSK      (0x00000060)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_multiplier_MIN      (0)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_multiplier_MAX      (3) // 0x00000003
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_multiplier_DEF      (0x00000001)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_DIMM_mode_multiplier_HSH      (0x020A40CC)

  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Dis_MRR_Bubble_OFF            ( 7)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Dis_MRR_Bubble_WID            ( 1)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Dis_MRR_Bubble_MSK            (0x00000080)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Dis_MRR_Bubble_MIN            (0)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Dis_MRR_Bubble_MAX            (1) // 0x00000001
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Dis_MRR_Bubble_DEF            (0x00000000)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_Dis_MRR_Bubble_HSH            (0x010E40CC)

  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_read_switch_num_cas_OFF ( 8)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_read_switch_num_cas_WID ( 8)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_read_switch_num_cas_MSK (0x0000FF00)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_read_switch_num_cas_MIN (0)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_read_switch_num_cas_MAX (255) // 0x000000FF
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_read_switch_num_cas_DEF (0x00000020)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_read_switch_num_cas_HSH (0x081040CC)

  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_write_switch_num_cas_OFF (16)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_write_switch_num_cas_WID ( 8)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_write_switch_num_cas_MSK (0x00FF0000)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_write_switch_num_cas_MIN (0)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_write_switch_num_cas_MAX (255) // 0x000000FF
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_write_switch_num_cas_DEF (0x00000020)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_write_switch_num_cas_HSH (0x082040CC)

  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_any_cas_switch_num_cas_OFF (24)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_any_cas_switch_num_cas_WID ( 8)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_any_cas_switch_num_cas_MSK (0xFF000000)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_any_cas_switch_num_cas_MIN (0)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_any_cas_switch_num_cas_MAX (255) // 0x000000FF
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_any_cas_switch_num_cas_DEF (0x00000080)
  #define MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_bubble_inj_any_cas_switch_num_cas_HSH (0x083040CC)

#define MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_REG                 (0x000040D0)

  #define MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_GLB_GRACE_CNT_OFF ( 0)
  #define MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_GLB_GRACE_CNT_WID ( 8)
  #define MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_GLB_GRACE_CNT_MSK (0x000000FF)
  #define MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_GLB_GRACE_CNT_MIN (0)
  #define MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_GLB_GRACE_CNT_MAX (255) // 0x000000FF
  #define MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_GLB_GRACE_CNT_DEF (0x0000000F)
  #define MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_GLB_GRACE_CNT_HSH (0x080040D0)

  #define MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_GLB_DRV_GATE_DIS_OFF ( 8)
  #define MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_GLB_DRV_GATE_DIS_WID ( 1)
  #define MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_GLB_DRV_GATE_DIS_MSK (0x00000100)
  #define MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_GLB_DRV_GATE_DIS_MIN (0)
  #define MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_GLB_DRV_GATE_DIS_MAX (1) // 0x00000001
  #define MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_GLB_DRV_GATE_DIS_DEF (0x00000000)
  #define MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_GLB_DRV_GATE_DIS_HSH (0x011040D0)

#define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_REG                           (0x000040D4)

  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_ph_blkr_OFF      ( 0)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_ph_blkr_WID      ( 1)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_ph_blkr_MSK      (0x00000001)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_ph_blkr_MIN      (0)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_ph_blkr_MAX      (1) // 0x00000001
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_ph_blkr_DEF      (0x00000000)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_ph_blkr_HSH      (0x010040D4)

  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_pe_blkr_OFF      ( 1)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_pe_blkr_WID      ( 1)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_pe_blkr_MSK      (0x00000002)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_pe_blkr_MIN      (0)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_pe_blkr_MAX      (1) // 0x00000001
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_pe_blkr_DEF      (0x00000000)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_dis_legacy_pe_blkr_HSH      (0x010240D4)

  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_low_wm_allowed_preempt_priorities_OFF ( 2)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_low_wm_allowed_preempt_priorities_WID ( 3)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_low_wm_allowed_preempt_priorities_MSK (0x0000001C)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_low_wm_allowed_preempt_priorities_MIN (0)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_low_wm_allowed_preempt_priorities_MAX (7) // 0x00000007
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_low_wm_allowed_preempt_priorities_DEF (0x00000007)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_low_wm_allowed_preempt_priorities_HSH (0x030440D4)

  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_med_wm_allowed_preempt_priorities_OFF ( 5)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_med_wm_allowed_preempt_priorities_WID ( 3)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_med_wm_allowed_preempt_priorities_MSK (0x000000E0)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_med_wm_allowed_preempt_priorities_MIN (0)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_med_wm_allowed_preempt_priorities_MAX (7) // 0x00000007
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_med_wm_allowed_preempt_priorities_DEF (0x00000006)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_med_wm_allowed_preempt_priorities_HSH (0x030A40D4)

  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_high_wm_allowed_preempt_priorities_OFF ( 8)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_high_wm_allowed_preempt_priorities_WID ( 3)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_high_wm_allowed_preempt_priorities_MSK (0x00000700)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_high_wm_allowed_preempt_priorities_MIN (0)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_high_wm_allowed_preempt_priorities_MAX (7) // 0x00000007
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_high_wm_allowed_preempt_priorities_DEF (0x00000004)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_high_wm_allowed_preempt_priorities_HSH (0x031040D4)

  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_ph_block_pe_OFF             (11)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_ph_block_pe_WID             ( 1)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_ph_block_pe_MSK             (0x00000800)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_ph_block_pe_MIN             (0)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_ph_block_pe_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_ph_block_pe_DEF             (0x00000001)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_ph_block_pe_HSH             (0x011640D4)

  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_blkr_effect_major_mode_OFF  (12)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_blkr_effect_major_mode_WID  ( 1)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_blkr_effect_major_mode_MSK  (0x00001000)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_blkr_effect_major_mode_MIN  (0)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_blkr_effect_major_mode_MAX  (1) // 0x00000001
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_blkr_effect_major_mode_DEF  (0x00000000)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_blkr_effect_major_mode_HSH  (0x011840D4)

  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_optimization_OFF     (13)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_optimization_WID     ( 1)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_optimization_MSK     (0x00002000)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_optimization_MIN     (0)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_optimization_MAX     (1) // 0x00000001
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_optimization_DEF     (0x00000001)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_optimization_HSH     (0x011A40D4)

  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_prefer_VC1_OFF       (14)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_prefer_VC1_WID       ( 1)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_prefer_VC1_MSK       (0x00004000)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_prefer_VC1_MIN       (0)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_prefer_VC1_MAX       (1) // 0x00000001
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_prefer_VC1_DEF       (0x00000001)
  #define MC0_CH0_CR_SC_BLOCKING_RULES_CFG_RIM_BW_prefer_VC1_HSH       (0x011C40D4)

#define MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_REG                      (0x000040D8)

  #define MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_ACT_COUNTER_OFF        ( 0)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_ACT_COUNTER_WID        (64)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_ACT_COUNTER_MSK        (0xFFFFFFFFFFFFFFFFULL)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_ACT_COUNTER_MIN        (0)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_ACT_COUNTER_MAX        (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_ACT_COUNTER_DEF        (0x00000000)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_ACT_COUNTER_HSH        (0x400040D8)

#define MC0_CH0_CR_PWM_DDR_SUBCH1_ACT_COUNTER_REG                      (0x000040E0)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_REG

#define MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REG            (0x000040E8)

  #define MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REQ_OCCUPANCY_COUNTER_OFF ( 0)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REQ_OCCUPANCY_COUNTER_WID (64)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REQ_OCCUPANCY_COUNTER_MSK (0xFFFFFFFFFFFFFFFFULL)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REQ_OCCUPANCY_COUNTER_MIN (0)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REQ_OCCUPANCY_COUNTER_MAX (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REQ_OCCUPANCY_COUNTER_DEF (0x00000000)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REQ_OCCUPANCY_COUNTER_HSH (0x400040E8)

#define MC0_CH0_CR_PWM_DDR_SUBCH0_DCLK_ACTIVE_COUNTER_A0_REG           (0x000040E8)

  #define MC0_CH0_CR_PWM_DDR_SUBCH0_DCLK_ACTIVE_COUNTER_DCLK_ACTIVE_COUNTER_A0_OFF ( 0)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_DCLK_ACTIVE_COUNTER_DCLK_ACTIVE_COUNTER_A0_WID (64)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_DCLK_ACTIVE_COUNTER_DCLK_ACTIVE_COUNTER_A0_MSK (0xFFFFFFFFFFFFFFFFULL)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_DCLK_ACTIVE_COUNTER_DCLK_ACTIVE_COUNTER_A0_MIN (0)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_DCLK_ACTIVE_COUNTER_DCLK_ACTIVE_COUNTER_A0_MAX (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_DCLK_ACTIVE_COUNTER_DCLK_ACTIVE_COUNTER_A0_DEF (0x00000000)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_DCLK_ACTIVE_COUNTER_DCLK_ACTIVE_COUNTER_A0_HSH (0x400040E8)

#define MC0_CH0_CR_PWM_DDR_SUBCH1_REQ_OCCUPANCY_COUNTER_REG            (0x000040F0)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REG

#define MC0_CH0_CR_PWM_DDR_SUBCH1_DCLK_ACTIVE_COUNTER_A0_REG           (0x000040F0)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_DCLK_ACTIVE_COUNTER_A0_REG

#define MC0_CH0_CR_WCK_CONFIG_REG                                      (0x000040F8)

  #define MC0_CH0_CR_WCK_CONFIG_LP5_WCK_MODE_OFF                       ( 0)
  #define MC0_CH0_CR_WCK_CONFIG_LP5_WCK_MODE_WID                       ( 2)
  #define MC0_CH0_CR_WCK_CONFIG_LP5_WCK_MODE_MSK                       (0x00000003)
  #define MC0_CH0_CR_WCK_CONFIG_LP5_WCK_MODE_MIN                       (0)
  #define MC0_CH0_CR_WCK_CONFIG_LP5_WCK_MODE_MAX                       (3) // 0x00000003
  #define MC0_CH0_CR_WCK_CONFIG_LP5_WCK_MODE_DEF                       (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_LP5_WCK_MODE_HSH                       (0x420040F8)

  #define MC0_CH0_CR_WCK_CONFIG_RD_WCK_ASYNC_GAP_OFF                   ( 2)
  #define MC0_CH0_CR_WCK_CONFIG_RD_WCK_ASYNC_GAP_WID                   ( 9)
  #define MC0_CH0_CR_WCK_CONFIG_RD_WCK_ASYNC_GAP_MSK                   (0x000007FC)
  #define MC0_CH0_CR_WCK_CONFIG_RD_WCK_ASYNC_GAP_MIN                   (0)
  #define MC0_CH0_CR_WCK_CONFIG_RD_WCK_ASYNC_GAP_MAX                   (511) // 0x000001FF
  #define MC0_CH0_CR_WCK_CONFIG_RD_WCK_ASYNC_GAP_DEF                   (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_RD_WCK_ASYNC_GAP_HSH                   (0x490440F8)

  #define MC0_CH0_CR_WCK_CONFIG_WR_WCK_ASYNC_GAP_OFF                   (11)
  #define MC0_CH0_CR_WCK_CONFIG_WR_WCK_ASYNC_GAP_WID                   ( 9)
  #define MC0_CH0_CR_WCK_CONFIG_WR_WCK_ASYNC_GAP_MSK                   (0x000FF800)
  #define MC0_CH0_CR_WCK_CONFIG_WR_WCK_ASYNC_GAP_MIN                   (0)
  #define MC0_CH0_CR_WCK_CONFIG_WR_WCK_ASYNC_GAP_MAX                   (511) // 0x000001FF
  #define MC0_CH0_CR_WCK_CONFIG_WR_WCK_ASYNC_GAP_DEF                   (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_WR_WCK_ASYNC_GAP_HSH                   (0x491640F8)

  #define MC0_CH0_CR_WCK_CONFIG_WCK_OFF_IDLE_TIMER_OFF                 (20)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_OFF_IDLE_TIMER_WID                 (12)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_OFF_IDLE_TIMER_MSK                 (0xFFF00000)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_OFF_IDLE_TIMER_MIN                 (0)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_OFF_IDLE_TIMER_MAX                 (4095) // 0x00000FFF
  #define MC0_CH0_CR_WCK_CONFIG_WCK_OFF_IDLE_TIMER_DEF                 (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_OFF_IDLE_TIMER_HSH                 (0x4C2840F8)

  #define MC0_CH0_CR_WCK_CONFIG_tWCKPST_OFF                            (32)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKPST_WID                            ( 4)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKPST_MSK                            (0x0000000F00000000ULL)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKPST_MIN                            (0)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKPST_MAX                            (15) // 0x0000000F
  #define MC0_CH0_CR_WCK_CONFIG_tWCKPST_DEF                            (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKPST_HSH                            (0x444040F8)

  #define MC0_CH0_CR_WCK_CONFIG_tWCKOFF_OFF                            (36)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKOFF_WID                            ( 8)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKOFF_MSK                            (0x00000FF000000000ULL)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKOFF_MIN                            (0)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKOFF_MAX                            (255) // 0x000000FF
  #define MC0_CH0_CR_WCK_CONFIG_tWCKOFF_DEF                            (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKOFF_HSH                            (0x484840F8)

  #define MC0_CH0_CR_WCK_CONFIG_tCASSTOP_ADDITIONAL_GAP_OFF            (44)
  #define MC0_CH0_CR_WCK_CONFIG_tCASSTOP_ADDITIONAL_GAP_WID            ( 5)
  #define MC0_CH0_CR_WCK_CONFIG_tCASSTOP_ADDITIONAL_GAP_MSK            (0x0001F00000000000ULL)
  #define MC0_CH0_CR_WCK_CONFIG_tCASSTOP_ADDITIONAL_GAP_MIN            (0)
  #define MC0_CH0_CR_WCK_CONFIG_tCASSTOP_ADDITIONAL_GAP_MAX            (31) // 0x0000001F
  #define MC0_CH0_CR_WCK_CONFIG_tCASSTOP_ADDITIONAL_GAP_DEF            (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_tCASSTOP_ADDITIONAL_GAP_HSH            (0x455840F8)

  #define MC0_CH0_CR_WCK_CONFIG_WCK_MRR_SHORTER_BL_DIS_OFF             (49)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_MRR_SHORTER_BL_DIS_WID             ( 1)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_MRR_SHORTER_BL_DIS_MSK             (0x0002000000000000ULL)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_MRR_SHORTER_BL_DIS_MIN             (0)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_MRR_SHORTER_BL_DIS_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_WCK_CONFIG_WCK_MRR_SHORTER_BL_DIS_DEF             (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_MRR_SHORTER_BL_DIS_HSH             (0x416240F8)

  #define MC0_CH0_CR_WCK_CONFIG_WCK_FAST_MODE_OFF                      (50)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_FAST_MODE_WID                      ( 1)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_FAST_MODE_MSK                      (0x0004000000000000ULL)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_FAST_MODE_MIN                      (0)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_FAST_MODE_MAX                      (1) // 0x00000001
  #define MC0_CH0_CR_WCK_CONFIG_WCK_FAST_MODE_DEF                      (0x00000001)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_FAST_MODE_HSH                      (0x416440F8)

  #define MC0_CH0_CR_WCK_CONFIG_WXSA_OFF                               (51)
  #define MC0_CH0_CR_WCK_CONFIG_WXSA_WID                               ( 1)
  #define MC0_CH0_CR_WCK_CONFIG_WXSA_MSK                               (0x0008000000000000ULL)
  #define MC0_CH0_CR_WCK_CONFIG_WXSA_MIN                               (0)
  #define MC0_CH0_CR_WCK_CONFIG_WXSA_MAX                               (1) // 0x00000001
  #define MC0_CH0_CR_WCK_CONFIG_WXSA_DEF                               (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_WXSA_HSH                               (0x416640F8)

  #define MC0_CH0_CR_WCK_CONFIG_WXSB_OFF                               (52)
  #define MC0_CH0_CR_WCK_CONFIG_WXSB_WID                               ( 1)
  #define MC0_CH0_CR_WCK_CONFIG_WXSB_MSK                               (0x0010000000000000ULL)
  #define MC0_CH0_CR_WCK_CONFIG_WXSB_MIN                               (0)
  #define MC0_CH0_CR_WCK_CONFIG_WXSB_MAX                               (1) // 0x00000001
  #define MC0_CH0_CR_WCK_CONFIG_WXSB_DEF                               (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_WXSB_HSH                               (0x416840F8)

#define MC0_CH0_CR_WCK_CONFIG_A0_REG                                   (0x000040F8)

  #define MC0_CH0_CR_WCK_CONFIG_LP5_WCK_MODE_A0_OFF                    ( 0)
  #define MC0_CH0_CR_WCK_CONFIG_LP5_WCK_MODE_A0_WID                    ( 2)
  #define MC0_CH0_CR_WCK_CONFIG_LP5_WCK_MODE_A0_MSK                    (0x00000003)
  #define MC0_CH0_CR_WCK_CONFIG_LP5_WCK_MODE_A0_MIN                    (0)
  #define MC0_CH0_CR_WCK_CONFIG_LP5_WCK_MODE_A0_MAX                    (3) // 0x00000003
  #define MC0_CH0_CR_WCK_CONFIG_LP5_WCK_MODE_A0_DEF                    (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_LP5_WCK_MODE_A0_HSH                    (0x420040F8)

  #define MC0_CH0_CR_WCK_CONFIG_RD_WCK_ASYNC_GAP_A0_OFF                ( 2)
  #define MC0_CH0_CR_WCK_CONFIG_RD_WCK_ASYNC_GAP_A0_WID                ( 9)
  #define MC0_CH0_CR_WCK_CONFIG_RD_WCK_ASYNC_GAP_A0_MSK                (0x000007FC)
  #define MC0_CH0_CR_WCK_CONFIG_RD_WCK_ASYNC_GAP_A0_MIN                (0)
  #define MC0_CH0_CR_WCK_CONFIG_RD_WCK_ASYNC_GAP_A0_MAX                (511) // 0x000001FF
  #define MC0_CH0_CR_WCK_CONFIG_RD_WCK_ASYNC_GAP_A0_DEF                (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_RD_WCK_ASYNC_GAP_A0_HSH                (0x490440F8)

  #define MC0_CH0_CR_WCK_CONFIG_WR_WCK_ASYNC_GAP_A0_OFF                (11)
  #define MC0_CH0_CR_WCK_CONFIG_WR_WCK_ASYNC_GAP_A0_WID                ( 9)
  #define MC0_CH0_CR_WCK_CONFIG_WR_WCK_ASYNC_GAP_A0_MSK                (0x000FF800)
  #define MC0_CH0_CR_WCK_CONFIG_WR_WCK_ASYNC_GAP_A0_MIN                (0)
  #define MC0_CH0_CR_WCK_CONFIG_WR_WCK_ASYNC_GAP_A0_MAX                (511) // 0x000001FF
  #define MC0_CH0_CR_WCK_CONFIG_WR_WCK_ASYNC_GAP_A0_DEF                (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_WR_WCK_ASYNC_GAP_A0_HSH                (0x491640F8)

  #define MC0_CH0_CR_WCK_CONFIG_WCK_OFF_IDLE_TIMER_A0_OFF              (20)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_OFF_IDLE_TIMER_A0_WID              (12)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_OFF_IDLE_TIMER_A0_MSK              (0xFFF00000)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_OFF_IDLE_TIMER_A0_MIN              (0)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_OFF_IDLE_TIMER_A0_MAX              (4095) // 0x00000FFF
  #define MC0_CH0_CR_WCK_CONFIG_WCK_OFF_IDLE_TIMER_A0_DEF              (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_OFF_IDLE_TIMER_A0_HSH              (0x4C2840F8)

  #define MC0_CH0_CR_WCK_CONFIG_tWCKPST_A0_OFF                         (32)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKPST_A0_WID                         ( 4)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKPST_A0_MSK                         (0x0000000F00000000ULL)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKPST_A0_MIN                         (0)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKPST_A0_MAX                         (15) // 0x0000000F
  #define MC0_CH0_CR_WCK_CONFIG_tWCKPST_A0_DEF                         (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKPST_A0_HSH                         (0x444040F8)

  #define MC0_CH0_CR_WCK_CONFIG_tWCKOFF_A0_OFF                         (36)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKOFF_A0_WID                         ( 8)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKOFF_A0_MSK                         (0x00000FF000000000ULL)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKOFF_A0_MIN                         (0)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKOFF_A0_MAX                         (255) // 0x000000FF
  #define MC0_CH0_CR_WCK_CONFIG_tWCKOFF_A0_DEF                         (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_tWCKOFF_A0_HSH                         (0x484840F8)

  #define MC0_CH0_CR_WCK_CONFIG_tCASSTOP_ADDITIONAL_GAP_A0_OFF         (44)
  #define MC0_CH0_CR_WCK_CONFIG_tCASSTOP_ADDITIONAL_GAP_A0_WID         ( 5)
  #define MC0_CH0_CR_WCK_CONFIG_tCASSTOP_ADDITIONAL_GAP_A0_MSK         (0x0001F00000000000ULL)
  #define MC0_CH0_CR_WCK_CONFIG_tCASSTOP_ADDITIONAL_GAP_A0_MIN         (0)
  #define MC0_CH0_CR_WCK_CONFIG_tCASSTOP_ADDITIONAL_GAP_A0_MAX         (31) // 0x0000001F
  #define MC0_CH0_CR_WCK_CONFIG_tCASSTOP_ADDITIONAL_GAP_A0_DEF         (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_tCASSTOP_ADDITIONAL_GAP_A0_HSH         (0x455840F8)

  #define MC0_CH0_CR_WCK_CONFIG_WCK_MRR_SHORTER_BL_DIS_A0_OFF          (49)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_MRR_SHORTER_BL_DIS_A0_WID          ( 1)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_MRR_SHORTER_BL_DIS_A0_MSK          (0x0002000000000000ULL)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_MRR_SHORTER_BL_DIS_A0_MIN          (0)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_MRR_SHORTER_BL_DIS_A0_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_WCK_CONFIG_WCK_MRR_SHORTER_BL_DIS_A0_DEF          (0x00000000)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_MRR_SHORTER_BL_DIS_A0_HSH          (0x416240F8)

  #define MC0_CH0_CR_WCK_CONFIG_WCK_FAST_MODE_A0_OFF                   (50)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_FAST_MODE_A0_WID                   ( 1)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_FAST_MODE_A0_MSK                   (0x0004000000000000ULL)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_FAST_MODE_A0_MIN                   (0)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_FAST_MODE_A0_MAX                   (1) // 0x00000001
  #define MC0_CH0_CR_WCK_CONFIG_WCK_FAST_MODE_A0_DEF                   (0x00000001)
  #define MC0_CH0_CR_WCK_CONFIG_WCK_FAST_MODE_A0_HSH                   (0x416440F8)

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG                       (0x00004120)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ADDRESS_OFF             ( 0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ADDRESS_WID             ( 6)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ADDRESS_MSK             (0x0000003F)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ADDRESS_MIN             (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ADDRESS_MAX             (63) // 0x0000003F
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ADDRESS_DEF             (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ADDRESS_HSH             (0x06004120)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_RANK_STORAGE_POINTER_OFF (16)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_RANK_STORAGE_POINTER_WID ( 4)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_RANK_STORAGE_POINTER_MSK (0x000F0000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_RANK_STORAGE_POINTER_MIN (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_RANK_STORAGE_POINTER_MAX (15) // 0x0000000F
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_RANK_STORAGE_POINTER_DEF (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_RANK_STORAGE_POINTER_HSH (0x04204120)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_TIMING_VALUE_POINTER_OFF (24)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_TIMING_VALUE_POINTER_WID ( 2)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_TIMING_VALUE_POINTER_MSK (0x03000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_TIMING_VALUE_POINTER_MIN (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_TIMING_VALUE_POINTER_MAX (3) // 0x00000003
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_TIMING_VALUE_POINTER_DEF (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_TIMING_VALUE_POINTER_HSH (0x02304120)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_FSP_CONTROL_OFF         (28)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_FSP_CONTROL_WID         ( 2)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_FSP_CONTROL_MSK         (0x30000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_FSP_CONTROL_MIN         (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_FSP_CONTROL_MAX         (3) // 0x00000003
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_FSP_CONTROL_DEF         (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_FSP_CONTROL_HSH         (0x02384120)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_RANK_OFF            (30)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_RANK_WID            ( 1)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_RANK_MSK            (0x40000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_RANK_MIN            (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_RANK_MAX            (1) // 0x00000001
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_RANK_DEF            (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_PER_RANK_HSH            (0x013C4120)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ACTIVE_OFF              (31)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ACTIVE_WID              ( 1)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ACTIVE_MSK              (0x80000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ACTIVE_MIN              (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ACTIVE_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ACTIVE_DEF              (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_ACTIVE_HSH              (0x013E4120)

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_1_REG                       (0x00004124)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_2_REG                       (0x00004128)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_3_REG                       (0x0000412C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_4_REG                       (0x00004130)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_5_REG                       (0x00004134)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_6_REG                       (0x00004138)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_7_REG                       (0x0000413C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_8_REG                       (0x00004140)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_9_REG                       (0x00004144)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_10_REG                      (0x00004148)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_11_REG                      (0x0000414C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_12_REG                      (0x00004150)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_13_REG                      (0x00004154)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_14_REG                      (0x00004158)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_15_REG                      (0x0000415C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_16_REG                      (0x00004160)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_17_REG                      (0x00004164)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_18_REG                      (0x00004168)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_19_REG                      (0x0000416C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_20_REG                      (0x00004170)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_21_REG                      (0x00004174)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_22_REG                      (0x00004178)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_23_REG                      (0x0000417C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_24_REG                      (0x00004180)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_25_REG                      (0x00004184)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_26_REG                      (0x00004188)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_27_REG                      (0x0000418C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG               (0x00004190)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_0_OFF    ( 0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_0_WID    ( 8)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_0_MSK    (0x000000FF)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_0_MIN    (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_0_MAX    (255) // 0x000000FF
  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_0_DEF    (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_0_HSH    (0x08004190)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_1_OFF    ( 8)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_1_WID    ( 8)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_1_MSK    (0x0000FF00)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_1_MIN    (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_1_MAX    (255) // 0x000000FF
  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_1_DEF    (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_1_HSH    (0x08104190)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_2_OFF    (16)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_2_WID    ( 8)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_2_MSK    (0x00FF0000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_2_MIN    (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_2_MAX    (255) // 0x000000FF
  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_2_DEF    (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_2_HSH    (0x08204190)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_3_OFF    (24)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_3_WID    ( 8)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_3_MSK    (0xFF000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_3_MIN    (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_3_MAX    (255) // 0x000000FF
  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_3_DEF    (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_SHADOW_3_HSH    (0x08304190)

#define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_1_REG               (0x00004194)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_2_REG               (0x00004198)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_3_REG               (0x0000419C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_4_REG               (0x000041A0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_5_REG               (0x000041A4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_6_REG               (0x000041A8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_7_REG               (0x000041AC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_8_REG               (0x000041B0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_9_REG               (0x000041B4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_10_REG              (0x000041B8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_11_REG              (0x000041BC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_SHADOW_VALUES_0_REG                 (0x000041C0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_SHADOW_VALUES_1_REG                 (0x000041C4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_SHADOW_VALUES_2_REG                 (0x000041C8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_SHADOW_VALUES_3_REG                 (0x000041CC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_SHADOW_VALUES_4_REG                 (0x000041D0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_SHADOW_VALUES_5_REG                 (0x000041D4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_SHADOW_VALUES_6_REG                 (0x000041D8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_REG                  (0x000041E0)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_0_OFF ( 0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_0_WID ( 8)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_0_MSK (0x000000FF)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_0_MIN (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_0_MAX (255) // 0x000000FF
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_0_DEF (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_0_HSH (0x080041E0)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_1_OFF ( 8)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_1_WID ( 8)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_1_MSK (0x0000FF00)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_1_MIN (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_1_MAX (255) // 0x000000FF
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_1_DEF (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_1_HSH (0x081041E0)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_2_OFF (16)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_2_WID ( 8)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_2_MSK (0x00FF0000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_2_MIN (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_2_MAX (255) // 0x000000FF
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_2_DEF (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_2_HSH (0x082041E0)

  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_3_OFF (24)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_3_WID ( 8)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_3_MSK (0xFF000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_3_MIN (0)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_3_MAX (255) // 0x000000FF
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_3_DEF (0x00000000)
  #define MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_TIMING_FIELD_3_HSH (0x083041E0)

#define MC0_CH0_CR_MCMNTS_RDDATA_CTL_REG                               (0x000041E8)

  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc0_credits_OFF           ( 0)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc0_credits_WID           ( 5)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc0_credits_MSK           (0x0000001F)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc0_credits_MIN           (0)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc0_credits_MAX           (31) // 0x0000001F
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc0_credits_DEF           (0x0000000F)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc0_credits_HSH           (0x050041E8)

  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc1_credits_OFF           ( 5)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc1_credits_WID           ( 5)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc1_credits_MSK           (0x000003E0)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc1_credits_MIN           (0)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc1_credits_MAX           (31) // 0x0000001F
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc1_credits_DEF           (0x0000000F)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_vc1_credits_HSH           (0x050A41E8)

  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_total_credits_OFF         (10)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_total_credits_WID         ( 5)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_total_credits_MSK         (0x00007C00)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_total_credits_MIN         (0)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_total_credits_MAX         (31) // 0x0000001F
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_total_credits_DEF         (0x00000010)
  #define MC0_CH0_CR_MCMNTS_RDDATA_CTL_rdbuf_total_credits_HSH         (0x051441E8)

#define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_REG                       (0x00004204)

  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Refresh_Rank_Mask_OFF   ( 0)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Refresh_Rank_Mask_WID   ( 4)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Refresh_Rank_Mask_MSK   (0x0000000F)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Refresh_Rank_Mask_MIN   (0)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Refresh_Rank_Mask_MAX   (15) // 0x0000000F
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Refresh_Rank_Mask_DEF   (0x0000000F)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Refresh_Rank_Mask_HSH   (0x04004204)

  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_RefZQ_En_Start_Test_Sync_OFF ( 8)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_RefZQ_En_Start_Test_Sync_WID ( 1)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_RefZQ_En_Start_Test_Sync_MSK (0x00000100)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_RefZQ_En_Start_Test_Sync_MIN (0)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_RefZQ_En_Start_Test_Sync_MAX (1) // 0x00000001
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_RefZQ_En_Start_Test_Sync_DEF (0x00000000)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_RefZQ_En_Start_Test_Sync_HSH (0x01104204)

  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Panic_Refresh_Only_OFF  (31)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Panic_Refresh_Only_WID  ( 1)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Panic_Refresh_Only_MSK  (0x80000000)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Panic_Refresh_Only_MIN  (0)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Panic_Refresh_Only_MAX  (1) // 0x00000001
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Panic_Refresh_Only_DEF  (0x00000000)
  #define MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Panic_Refresh_Only_HSH  (0x013E4204)

#define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_REG                            (0x00004208)

  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_ZQ_Rank_Mask_OFF             ( 0)
  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_ZQ_Rank_Mask_WID             ( 4)
  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_ZQ_Rank_Mask_MSK             (0x0000000F)
  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_ZQ_Rank_Mask_MIN             (0)
  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_ZQ_Rank_Mask_MAX             (15) // 0x0000000F
  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_ZQ_Rank_Mask_DEF             (0x00000000)
  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_ZQ_Rank_Mask_HSH             (0x04004208)

  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_Always_Do_ZQ_OFF             (31)
  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_Always_Do_ZQ_WID             ( 1)
  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_Always_Do_ZQ_MSK             (0x80000000)
  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_Always_Do_ZQ_MIN             (0)
  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_Always_Do_ZQ_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_Always_Do_ZQ_DEF             (0x00000000)
  #define MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_Always_Do_ZQ_HSH             (0x013E4208)

#define MC0_CH0_CR_DDR_MR_PARAMS_REG                                   (0x00004210)

  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_0_width_OFF                    ( 0)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_0_width_WID                    ( 2)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_0_width_MSK                    (0x00000003)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_0_width_MIN                    (0)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_0_width_MAX                    (3) // 0x00000003
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_0_width_DEF                    (0x00000000)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_0_width_HSH                    (0x02004210)

  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_1_width_OFF                    ( 2)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_1_width_WID                    ( 2)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_1_width_MSK                    (0x0000000C)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_1_width_MIN                    (0)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_1_width_MAX                    (3) // 0x00000003
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_1_width_DEF                    (0x00000000)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_1_width_HSH                    (0x02044210)

  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_2_width_OFF                    ( 4)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_2_width_WID                    ( 2)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_2_width_MSK                    (0x00000030)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_2_width_MIN                    (0)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_2_width_MAX                    (3) // 0x00000003
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_2_width_DEF                    (0x00000000)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_2_width_HSH                    (0x02084210)

  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_3_width_OFF                    ( 6)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_3_width_WID                    ( 2)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_3_width_MSK                    (0x000000C0)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_3_width_MIN                    (0)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_3_width_MAX                    (3) // 0x00000003
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_3_width_DEF                    (0x00000000)
  #define MC0_CH0_CR_DDR_MR_PARAMS_Rank_3_width_HSH                    (0x020C4210)

  #define MC0_CH0_CR_DDR_MR_PARAMS_MR4_PERIOD_OFF                      ( 8)
  #define MC0_CH0_CR_DDR_MR_PARAMS_MR4_PERIOD_WID                      (16)
  #define MC0_CH0_CR_DDR_MR_PARAMS_MR4_PERIOD_MSK                      (0x00FFFF00)
  #define MC0_CH0_CR_DDR_MR_PARAMS_MR4_PERIOD_MIN                      (0)
  #define MC0_CH0_CR_DDR_MR_PARAMS_MR4_PERIOD_MAX                      (65535) // 0x0000FFFF
  #define MC0_CH0_CR_DDR_MR_PARAMS_MR4_PERIOD_DEF                      (0x00000000)
  #define MC0_CH0_CR_DDR_MR_PARAMS_MR4_PERIOD_HSH                      (0x10104210)

  #define MC0_CH0_CR_DDR_MR_PARAMS_DDR4_TS_readout_en_OFF              (24)
  #define MC0_CH0_CR_DDR_MR_PARAMS_DDR4_TS_readout_en_WID              ( 1)
  #define MC0_CH0_CR_DDR_MR_PARAMS_DDR4_TS_readout_en_MSK              (0x01000000)
  #define MC0_CH0_CR_DDR_MR_PARAMS_DDR4_TS_readout_en_MIN              (0)
  #define MC0_CH0_CR_DDR_MR_PARAMS_DDR4_TS_readout_en_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_DDR_MR_PARAMS_DDR4_TS_readout_en_DEF              (0x00000001)
  #define MC0_CH0_CR_DDR_MR_PARAMS_DDR4_TS_readout_en_HSH              (0x01304210)

#define MC0_CH0_CR_DDR_MR_COMMAND_REG                                  (0x00004214)

  #define MC0_CH0_CR_DDR_MR_COMMAND_Address_OFF                        ( 0)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Address_WID                        ( 9)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Address_MSK                        (0x000001FF)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Address_MIN                        (0)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Address_MAX                        (511) // 0x000001FF
  #define MC0_CH0_CR_DDR_MR_COMMAND_Address_DEF                        (0x00000000)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Address_HSH                        (0x09004214)

  #define MC0_CH0_CR_DDR_MR_COMMAND_Data_OFF                           ( 9)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Data_WID                           ( 8)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Data_MSK                           (0x0001FE00)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Data_MIN                           (0)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Data_MAX                           (255) // 0x000000FF
  #define MC0_CH0_CR_DDR_MR_COMMAND_Data_DEF                           (0x00000000)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Data_HSH                           (0x08124214)

  #define MC0_CH0_CR_DDR_MR_COMMAND_Rank_OFF                           (17)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Rank_WID                           ( 2)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Rank_MSK                           (0x00060000)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Rank_MIN                           (0)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Rank_MAX                           (3) // 0x00000003
  #define MC0_CH0_CR_DDR_MR_COMMAND_Rank_DEF                           (0x00000000)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Rank_HSH                           (0x02224214)

  #define MC0_CH0_CR_DDR_MR_COMMAND_Command_OFF                        (19)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Command_WID                        ( 2)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Command_MSK                        (0x00180000)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Command_MIN                        (0)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Command_MAX                        (3) // 0x00000003
  #define MC0_CH0_CR_DDR_MR_COMMAND_Command_DEF                        (0x00000000)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Command_HSH                        (0x02264214)

  #define MC0_CH0_CR_DDR_MR_COMMAND_DRAM_mask_OFF                      (21)
  #define MC0_CH0_CR_DDR_MR_COMMAND_DRAM_mask_WID                      ( 9)
  #define MC0_CH0_CR_DDR_MR_COMMAND_DRAM_mask_MSK                      (0x3FE00000)
  #define MC0_CH0_CR_DDR_MR_COMMAND_DRAM_mask_MIN                      (0)
  #define MC0_CH0_CR_DDR_MR_COMMAND_DRAM_mask_MAX                      (511) // 0x000001FF
  #define MC0_CH0_CR_DDR_MR_COMMAND_DRAM_mask_DEF                      (0x00000000)
  #define MC0_CH0_CR_DDR_MR_COMMAND_DRAM_mask_HSH                      (0x092A4214)

  #define MC0_CH0_CR_DDR_MR_COMMAND_Assume_idle_OFF                    (30)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Assume_idle_WID                    ( 1)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Assume_idle_MSK                    (0x40000000)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Assume_idle_MIN                    (0)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Assume_idle_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_DDR_MR_COMMAND_Assume_idle_DEF                    (0x00000000)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Assume_idle_HSH                    (0x013C4214)

  #define MC0_CH0_CR_DDR_MR_COMMAND_Busy_OFF                           (31)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Busy_WID                           ( 1)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Busy_MSK                           (0x80000000)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Busy_MIN                           (0)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Busy_MAX                           (1) // 0x00000001
  #define MC0_CH0_CR_DDR_MR_COMMAND_Busy_DEF                           (0x00000000)
  #define MC0_CH0_CR_DDR_MR_COMMAND_Busy_HSH                           (0x013E4214)

#define MC0_CH0_CR_DDR_MR_RESULT_0_REG                                 (0x00004218)

  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_0_OFF                      ( 0)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_0_WID                      ( 8)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_0_MSK                      (0x000000FF)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_0_MIN                      (0)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_0_MAX                      (255) // 0x000000FF
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_0_DEF                      (0x00000000)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_0_HSH                      (0x08004218)

  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_1_OFF                      ( 8)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_1_WID                      ( 8)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_1_MSK                      (0x0000FF00)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_1_MIN                      (0)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_1_MAX                      (255) // 0x000000FF
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_1_DEF                      (0x00000000)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_1_HSH                      (0x08104218)

  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_2_OFF                      (16)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_2_WID                      ( 8)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_2_MSK                      (0x00FF0000)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_2_MIN                      (0)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_2_MAX                      (255) // 0x000000FF
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_2_DEF                      (0x00000000)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_2_HSH                      (0x08204218)

  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_3_OFF                      (24)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_3_WID                      ( 8)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_3_MSK                      (0xFF000000)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_3_MIN                      (0)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_3_MAX                      (255) // 0x000000FF
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_3_DEF                      (0x00000000)
  #define MC0_CH0_CR_DDR_MR_RESULT_0_Device_3_HSH                      (0x08304218)

#define MC0_CH0_CR_DDR_MR_RESULT_1_REG                                 (0x0000421C)

  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_4_OFF                      ( 0)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_4_WID                      ( 8)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_4_MSK                      (0x000000FF)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_4_MIN                      (0)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_4_MAX                      (255) // 0x000000FF
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_4_DEF                      (0x00000000)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_4_HSH                      (0x0800421C)

  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_5_OFF                      ( 8)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_5_WID                      ( 8)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_5_MSK                      (0x0000FF00)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_5_MIN                      (0)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_5_MAX                      (255) // 0x000000FF
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_5_DEF                      (0x00000000)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_5_HSH                      (0x0810421C)

  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_6_OFF                      (16)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_6_WID                      ( 8)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_6_MSK                      (0x00FF0000)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_6_MIN                      (0)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_6_MAX                      (255) // 0x000000FF
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_6_DEF                      (0x00000000)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_6_HSH                      (0x0820421C)

  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_7_OFF                      (24)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_7_WID                      ( 8)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_7_MSK                      (0xFF000000)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_7_MIN                      (0)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_7_MAX                      (255) // 0x000000FF
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_7_DEF                      (0x00000000)
  #define MC0_CH0_CR_DDR_MR_RESULT_1_Device_7_HSH                      (0x0830421C)

#define MC0_CH0_CR_DDR_MR_RESULT_2_REG                                 (0x00004220)

  #define MC0_CH0_CR_DDR_MR_RESULT_2_Device_8_OFF                      ( 0)
  #define MC0_CH0_CR_DDR_MR_RESULT_2_Device_8_WID                      ( 8)
  #define MC0_CH0_CR_DDR_MR_RESULT_2_Device_8_MSK                      (0x000000FF)
  #define MC0_CH0_CR_DDR_MR_RESULT_2_Device_8_MIN                      (0)
  #define MC0_CH0_CR_DDR_MR_RESULT_2_Device_8_MAX                      (255) // 0x000000FF
  #define MC0_CH0_CR_DDR_MR_RESULT_2_Device_8_DEF                      (0x00000000)
  #define MC0_CH0_CR_DDR_MR_RESULT_2_Device_8_HSH                      (0x08004220)

#define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_REG                      (0x00004224)

  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_0_OFF             ( 0)
  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_0_WID             ( 5)
  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_0_MSK             (0x0000001F)
  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_0_MIN             (0)
  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_0_MAX             (31) // 0x0000001F
  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_0_DEF             (0x00000003)
  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_0_HSH             (0x05004224)

  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_1_OFF             ( 8)
  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_1_WID             ( 5)
  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_1_MSK             (0x00001F00)
  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_1_MIN             (0)
  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_1_MAX             (31) // 0x0000001F
  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_1_DEF             (0x00000003)
  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_1_HSH             (0x05104224)

  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_2_OFF             (16)
  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_2_WID             ( 5)
  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_2_MSK             (0x001F0000)
  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_2_MIN             (0)
  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_2_MAX             (31) // 0x0000001F
  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_2_DEF             (0x00000003)
  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_2_HSH             (0x05204224)

  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_3_OFF             (24)
  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_3_WID             ( 5)
  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_3_MSK             (0x1F000000)
  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_3_MIN             (0)
  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_3_MAX             (31) // 0x0000001F
  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_3_DEF             (0x00000003)
  #define MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_3_HSH             (0x05304224)

#define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_REG                       (0x00004228)

  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_0_OFF              ( 0)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_0_WID              ( 2)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_0_MSK              (0x00000003)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_0_MIN              (0)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_0_MAX              (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_0_DEF              (0x00000001)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_0_HSH              (0x02004228)

  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_1_OFF              ( 8)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_1_WID              ( 2)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_1_MSK              (0x00000300)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_1_MIN              (0)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_1_MAX              (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_1_DEF              (0x00000001)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_1_HSH              (0x02104228)

  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_2_OFF              (16)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_2_WID              ( 2)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_2_MSK              (0x00030000)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_2_MIN              (0)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_2_MAX              (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_2_DEF              (0x00000001)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_2_HSH              (0x02204228)

  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_3_OFF              (24)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_3_WID              ( 2)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_3_MSK              (0x03000000)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_3_MIN              (0)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_3_MAX              (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_3_DEF              (0x00000001)
  #define MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_3_HSH              (0x02304228)

#define MC0_CH0_CR_DESWIZZLE_LOW_ERM_REG                               (0x00004230)

  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_0_OFF                       ( 0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_0_WID                       ( 3)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_0_MSK                       (0x00000007)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_0_MIN                       (0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_0_MAX                       (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_0_DEF                       (0x00000000)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_0_HSH                       (0x43004230)

  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_1_OFF                       ( 3)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_1_WID                       ( 3)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_1_MSK                       (0x00000038)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_1_MIN                       (0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_1_MAX                       (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_1_DEF                       (0x00000001)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_1_HSH                       (0x43064230)

  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_2_OFF                       ( 6)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_2_WID                       ( 3)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_2_MSK                       (0x000001C0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_2_MIN                       (0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_2_MAX                       (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_2_DEF                       (0x00000002)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_2_HSH                       (0x430C4230)

  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_3_OFF                       ( 9)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_3_WID                       ( 3)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_3_MSK                       (0x00000E00)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_3_MIN                       (0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_3_MAX                       (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_3_DEF                       (0x00000003)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_3_HSH                       (0x43124230)

  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_4_OFF                       (12)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_4_WID                       ( 3)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_4_MSK                       (0x00007000)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_4_MIN                       (0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_4_MAX                       (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_4_DEF                       (0x00000004)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_4_HSH                       (0x43184230)

  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_8_OFF                       (15)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_8_WID                       ( 3)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_8_MSK                       (0x00038000)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_8_MIN                       (0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_8_MAX                       (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_8_DEF                       (0x00000000)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_8_HSH                       (0x431E4230)

  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_9_OFF                       (18)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_9_WID                       ( 3)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_9_MSK                       (0x001C0000)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_9_MIN                       (0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_9_MAX                       (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_9_DEF                       (0x00000001)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_9_HSH                       (0x43244230)

  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_10_OFF                      (21)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_10_WID                      ( 3)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_10_MSK                      (0x00E00000)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_10_MIN                      (0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_10_MAX                      (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_10_DEF                      (0x00000002)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_10_HSH                      (0x432A4230)

  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_11_OFF                      (24)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_11_WID                      ( 3)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_11_MSK                      (0x07000000)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_11_MIN                      (0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_11_MAX                      (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_11_DEF                      (0x00000003)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_11_HSH                      (0x43304230)

  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_12_OFF                      (27)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_12_WID                      ( 3)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_12_MSK                      (0x38000000)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_12_MIN                      (0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_12_MAX                      (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_12_DEF                      (0x00000004)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Bit_12_HSH                      (0x43364230)

  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_0_OFF                      (32)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_0_WID                      ( 3)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_0_MSK                      (0x0000000700000000ULL)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_0_MIN                      (0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_0_MAX                      (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_0_DEF                      (0x00000000)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_0_HSH                      (0x43404230)

  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_1_OFF                      (35)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_1_WID                      ( 3)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_1_MSK                      (0x0000003800000000ULL)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_1_MIN                      (0)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_1_MAX                      (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_1_DEF                      (0x00000001)
  #define MC0_CH0_CR_DESWIZZLE_LOW_ERM_Byte_1_HSH                      (0x43464230)

#define MC0_CH0_CR_TC_RFP_REG                                          (0x00004238)

  #define MC0_CH0_CR_TC_RFP_OREF_RI_OFF                                ( 0)
  #define MC0_CH0_CR_TC_RFP_OREF_RI_WID                                ( 8)
  #define MC0_CH0_CR_TC_RFP_OREF_RI_MSK                                (0x000000FF)
  #define MC0_CH0_CR_TC_RFP_OREF_RI_MIN                                (0)
  #define MC0_CH0_CR_TC_RFP_OREF_RI_MAX                                (255) // 0x000000FF
  #define MC0_CH0_CR_TC_RFP_OREF_RI_DEF                                (0x0000000F)
  #define MC0_CH0_CR_TC_RFP_OREF_RI_HSH                                (0x08004238)

  #define MC0_CH0_CR_TC_RFP_Refresh_HP_WM_OFF                          ( 8)
  #define MC0_CH0_CR_TC_RFP_Refresh_HP_WM_WID                          ( 4)
  #define MC0_CH0_CR_TC_RFP_Refresh_HP_WM_MSK                          (0x00000F00)
  #define MC0_CH0_CR_TC_RFP_Refresh_HP_WM_MIN                          (0)
  #define MC0_CH0_CR_TC_RFP_Refresh_HP_WM_MAX                          (15) // 0x0000000F
  #define MC0_CH0_CR_TC_RFP_Refresh_HP_WM_DEF                          (0x00000008)
  #define MC0_CH0_CR_TC_RFP_Refresh_HP_WM_HSH                          (0x04104238)

  #define MC0_CH0_CR_TC_RFP_Refresh_panic_wm_OFF                       (12)
  #define MC0_CH0_CR_TC_RFP_Refresh_panic_wm_WID                       ( 4)
  #define MC0_CH0_CR_TC_RFP_Refresh_panic_wm_MSK                       (0x0000F000)
  #define MC0_CH0_CR_TC_RFP_Refresh_panic_wm_MIN                       (0)
  #define MC0_CH0_CR_TC_RFP_Refresh_panic_wm_MAX                       (15) // 0x0000000F
  #define MC0_CH0_CR_TC_RFP_Refresh_panic_wm_DEF                       (0x00000009)
  #define MC0_CH0_CR_TC_RFP_Refresh_panic_wm_HSH                       (0x04184238)

  #define MC0_CH0_CR_TC_RFP_CounttREFIWhileRefEnOff_OFF                (16)
  #define MC0_CH0_CR_TC_RFP_CounttREFIWhileRefEnOff_WID                ( 1)
  #define MC0_CH0_CR_TC_RFP_CounttREFIWhileRefEnOff_MSK                (0x00010000)
  #define MC0_CH0_CR_TC_RFP_CounttREFIWhileRefEnOff_MIN                (0)
  #define MC0_CH0_CR_TC_RFP_CounttREFIWhileRefEnOff_MAX                (1) // 0x00000001
  #define MC0_CH0_CR_TC_RFP_CounttREFIWhileRefEnOff_DEF                (0x00000000)
  #define MC0_CH0_CR_TC_RFP_CounttREFIWhileRefEnOff_HSH                (0x01204238)

  #define MC0_CH0_CR_TC_RFP_HPRefOnMRS_OFF                             (17)
  #define MC0_CH0_CR_TC_RFP_HPRefOnMRS_WID                             ( 1)
  #define MC0_CH0_CR_TC_RFP_HPRefOnMRS_MSK                             (0x00020000)
  #define MC0_CH0_CR_TC_RFP_HPRefOnMRS_MIN                             (0)
  #define MC0_CH0_CR_TC_RFP_HPRefOnMRS_MAX                             (1) // 0x00000001
  #define MC0_CH0_CR_TC_RFP_HPRefOnMRS_DEF                             (0x00000001)
  #define MC0_CH0_CR_TC_RFP_HPRefOnMRS_HSH                             (0x01224238)

  #define MC0_CH0_CR_TC_RFP_AlwaysRefOnMRS_OFF                         (18)
  #define MC0_CH0_CR_TC_RFP_AlwaysRefOnMRS_WID                         ( 1)
  #define MC0_CH0_CR_TC_RFP_AlwaysRefOnMRS_MSK                         (0x00040000)
  #define MC0_CH0_CR_TC_RFP_AlwaysRefOnMRS_MIN                         (0)
  #define MC0_CH0_CR_TC_RFP_AlwaysRefOnMRS_MAX                         (1) // 0x00000001
  #define MC0_CH0_CR_TC_RFP_AlwaysRefOnMRS_DEF                         (0x00000000)
  #define MC0_CH0_CR_TC_RFP_AlwaysRefOnMRS_HSH                         (0x01244238)

  #define MC0_CH0_CR_TC_RFP_RAISE_BLK_WAIT_OFF                         (21)
  #define MC0_CH0_CR_TC_RFP_RAISE_BLK_WAIT_WID                         ( 4)
  #define MC0_CH0_CR_TC_RFP_RAISE_BLK_WAIT_MSK                         (0x01E00000)
  #define MC0_CH0_CR_TC_RFP_RAISE_BLK_WAIT_MIN                         (0)
  #define MC0_CH0_CR_TC_RFP_RAISE_BLK_WAIT_MAX                         (15) // 0x0000000F
  #define MC0_CH0_CR_TC_RFP_RAISE_BLK_WAIT_DEF                         (0x00000005)
  #define MC0_CH0_CR_TC_RFP_RAISE_BLK_WAIT_HSH                         (0x042A4238)

  #define MC0_CH0_CR_TC_RFP_tREFIx9_OFF                                (25)
  #define MC0_CH0_CR_TC_RFP_tREFIx9_WID                                ( 7)
  #define MC0_CH0_CR_TC_RFP_tREFIx9_MSK                                (0xFE000000)
  #define MC0_CH0_CR_TC_RFP_tREFIx9_MIN                                (0)
  #define MC0_CH0_CR_TC_RFP_tREFIx9_MAX                                (127) // 0x0000007F
  #define MC0_CH0_CR_TC_RFP_tREFIx9_DEF                                (0x00000023)
  #define MC0_CH0_CR_TC_RFP_tREFIx9_HSH                                (0x07324238)

#define MC0_CH0_CR_TC_RFP_A0_REG                                       (0x00004238)

  #define MC0_CH0_CR_TC_RFP_OREF_RI_A0_OFF                             ( 0)
  #define MC0_CH0_CR_TC_RFP_OREF_RI_A0_WID                             ( 8)
  #define MC0_CH0_CR_TC_RFP_OREF_RI_A0_MSK                             (0x000000FF)
  #define MC0_CH0_CR_TC_RFP_OREF_RI_A0_MIN                             (0)
  #define MC0_CH0_CR_TC_RFP_OREF_RI_A0_MAX                             (255) // 0x000000FF
  #define MC0_CH0_CR_TC_RFP_OREF_RI_A0_DEF                             (0x0000000F)
  #define MC0_CH0_CR_TC_RFP_OREF_RI_A0_HSH                             (0x08004238)

  #define MC0_CH0_CR_TC_RFP_Refresh_HP_WM_A0_OFF                       ( 8)
  #define MC0_CH0_CR_TC_RFP_Refresh_HP_WM_A0_WID                       ( 4)
  #define MC0_CH0_CR_TC_RFP_Refresh_HP_WM_A0_MSK                       (0x00000F00)
  #define MC0_CH0_CR_TC_RFP_Refresh_HP_WM_A0_MIN                       (0)
  #define MC0_CH0_CR_TC_RFP_Refresh_HP_WM_A0_MAX                       (15) // 0x0000000F
  #define MC0_CH0_CR_TC_RFP_Refresh_HP_WM_A0_DEF                       (0x00000008)
  #define MC0_CH0_CR_TC_RFP_Refresh_HP_WM_A0_HSH                       (0x04104238)

  #define MC0_CH0_CR_TC_RFP_Refresh_panic_wm_A0_OFF                    (12)
  #define MC0_CH0_CR_TC_RFP_Refresh_panic_wm_A0_WID                    ( 4)
  #define MC0_CH0_CR_TC_RFP_Refresh_panic_wm_A0_MSK                    (0x0000F000)
  #define MC0_CH0_CR_TC_RFP_Refresh_panic_wm_A0_MIN                    (0)
  #define MC0_CH0_CR_TC_RFP_Refresh_panic_wm_A0_MAX                    (15) // 0x0000000F
  #define MC0_CH0_CR_TC_RFP_Refresh_panic_wm_A0_DEF                    (0x00000009)
  #define MC0_CH0_CR_TC_RFP_Refresh_panic_wm_A0_HSH                    (0x04184238)

  #define MC0_CH0_CR_TC_RFP_CounttREFIWhileRefEnOff_A0_OFF             (16)
  #define MC0_CH0_CR_TC_RFP_CounttREFIWhileRefEnOff_A0_WID             ( 1)
  #define MC0_CH0_CR_TC_RFP_CounttREFIWhileRefEnOff_A0_MSK             (0x00010000)
  #define MC0_CH0_CR_TC_RFP_CounttREFIWhileRefEnOff_A0_MIN             (0)
  #define MC0_CH0_CR_TC_RFP_CounttREFIWhileRefEnOff_A0_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_TC_RFP_CounttREFIWhileRefEnOff_A0_DEF             (0x00000000)
  #define MC0_CH0_CR_TC_RFP_CounttREFIWhileRefEnOff_A0_HSH             (0x01204238)

  #define MC0_CH0_CR_TC_RFP_HPRefOnMRS_A0_OFF                          (17)
  #define MC0_CH0_CR_TC_RFP_HPRefOnMRS_A0_WID                          ( 1)
  #define MC0_CH0_CR_TC_RFP_HPRefOnMRS_A0_MSK                          (0x00020000)
  #define MC0_CH0_CR_TC_RFP_HPRefOnMRS_A0_MIN                          (0)
  #define MC0_CH0_CR_TC_RFP_HPRefOnMRS_A0_MAX                          (1) // 0x00000001
  #define MC0_CH0_CR_TC_RFP_HPRefOnMRS_A0_DEF                          (0x00000001)
  #define MC0_CH0_CR_TC_RFP_HPRefOnMRS_A0_HSH                          (0x01224238)

  #define MC0_CH0_CR_TC_RFP_AlwaysRefOnMRS_A0_OFF                      (18)
  #define MC0_CH0_CR_TC_RFP_AlwaysRefOnMRS_A0_WID                      ( 1)
  #define MC0_CH0_CR_TC_RFP_AlwaysRefOnMRS_A0_MSK                      (0x00040000)
  #define MC0_CH0_CR_TC_RFP_AlwaysRefOnMRS_A0_MIN                      (0)
  #define MC0_CH0_CR_TC_RFP_AlwaysRefOnMRS_A0_MAX                      (1) // 0x00000001
  #define MC0_CH0_CR_TC_RFP_AlwaysRefOnMRS_A0_DEF                      (0x00000000)
  #define MC0_CH0_CR_TC_RFP_AlwaysRefOnMRS_A0_HSH                      (0x01244238)

  #define MC0_CH0_CR_TC_RFP_tREFIx9_A0_OFF                             (25)
  #define MC0_CH0_CR_TC_RFP_tREFIx9_A0_WID                             ( 7)
  #define MC0_CH0_CR_TC_RFP_tREFIx9_A0_MSK                             (0xFE000000)
  #define MC0_CH0_CR_TC_RFP_tREFIx9_A0_MIN                             (0)
  #define MC0_CH0_CR_TC_RFP_tREFIx9_A0_MAX                             (127) // 0x0000007F
  #define MC0_CH0_CR_TC_RFP_tREFIx9_A0_DEF                             (0x00000023)
  #define MC0_CH0_CR_TC_RFP_tREFIx9_A0_HSH                             (0x07324238)

#define MC0_CH0_CR_TC_RFTP_REG                                         (0x0000423C)

  #define MC0_CH0_CR_TC_RFTP_tREFI_OFF                                 ( 0)
  #define MC0_CH0_CR_TC_RFTP_tREFI_WID                                 (17)
  #define MC0_CH0_CR_TC_RFTP_tREFI_MSK                                 (0x0001FFFF)
  #define MC0_CH0_CR_TC_RFTP_tREFI_MIN                                 (0)
  #define MC0_CH0_CR_TC_RFTP_tREFI_MAX                                 (131071) // 0x0001FFFF
  #define MC0_CH0_CR_TC_RFTP_tREFI_DEF                                 (0x00001004)
  #define MC0_CH0_CR_TC_RFTP_tREFI_HSH                                 (0x1100423C)

  #define MC0_CH0_CR_TC_RFTP_tRFC_OFF                                  (17)
  #define MC0_CH0_CR_TC_RFTP_tRFC_WID                                  (12)
  #define MC0_CH0_CR_TC_RFTP_tRFC_MSK                                  (0x1FFE0000)
  #define MC0_CH0_CR_TC_RFTP_tRFC_MIN                                  (0)
  #define MC0_CH0_CR_TC_RFTP_tRFC_MAX                                  (4095) // 0x00000FFF
  #define MC0_CH0_CR_TC_RFTP_tRFC_DEF                                  (0x000000B4)
  #define MC0_CH0_CR_TC_RFTP_tRFC_HSH                                  (0x0C22423C)

#define MC0_CH0_CR_TC_SRFTP_REG                                        (0x00004240)

  #define MC0_CH0_CR_TC_SRFTP_tXSDLL_OFF                               ( 0)
  #define MC0_CH0_CR_TC_SRFTP_tXSDLL_WID                               (12)
  #define MC0_CH0_CR_TC_SRFTP_tXSDLL_MSK                               (0x00000FFF)
  #define MC0_CH0_CR_TC_SRFTP_tXSDLL_MIN                               (0)
  #define MC0_CH0_CR_TC_SRFTP_tXSDLL_MAX                               (4095) // 0x00000FFF
  #define MC0_CH0_CR_TC_SRFTP_tXSDLL_DEF                               (0x00000200)
  #define MC0_CH0_CR_TC_SRFTP_tXSDLL_HSH                               (0x0C004240)

  #define MC0_CH0_CR_TC_SRFTP_tZQOPER_OFF                              (16)
  #define MC0_CH0_CR_TC_SRFTP_tZQOPER_WID                              (10)
  #define MC0_CH0_CR_TC_SRFTP_tZQOPER_MSK                              (0x03FF0000)
  #define MC0_CH0_CR_TC_SRFTP_tZQOPER_MIN                              (0)
  #define MC0_CH0_CR_TC_SRFTP_tZQOPER_MAX                              (1023) // 0x000003FF
  #define MC0_CH0_CR_TC_SRFTP_tZQOPER_DEF                              (0x00000100)
  #define MC0_CH0_CR_TC_SRFTP_tZQOPER_HSH                              (0x0A204240)

  #define MC0_CH0_CR_TC_SRFTP_tMOD_OFF                                 (26)
  #define MC0_CH0_CR_TC_SRFTP_tMOD_WID                                 ( 6)
  #define MC0_CH0_CR_TC_SRFTP_tMOD_MSK                                 (0xFC000000)
  #define MC0_CH0_CR_TC_SRFTP_tMOD_MIN                                 (0)
  #define MC0_CH0_CR_TC_SRFTP_tMOD_MAX                                 (63) // 0x0000003F
  #define MC0_CH0_CR_TC_SRFTP_tMOD_DEF                                 (0x00000000)
  #define MC0_CH0_CR_TC_SRFTP_tMOD_HSH                                 (0x06344240)

#define MC0_CH0_CR_MC_REFRESH_STAGGER_REG                              (0x00004244)

  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Interval_OFF               ( 0)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Interval_WID               (12)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Interval_MSK               (0x00000FFF)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Interval_MIN               (0)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Interval_MAX               (4095) // 0x00000FFF
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Interval_DEF               (0x00000000)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Interval_HSH               (0x0C004244)

  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_Mode_OFF           (12)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_Mode_WID           ( 1)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_Mode_MSK           (0x00001000)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_Mode_MIN           (0)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_Mode_MAX           (1) // 0x00000001
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_Mode_DEF           (0x00000000)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_Mode_HSH           (0x01184244)

  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Disable_Stolen_Refresh_OFF     (13)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Disable_Stolen_Refresh_WID     ( 1)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Disable_Stolen_Refresh_MSK     (0x00002000)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Disable_Stolen_Refresh_MIN     (0)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Disable_Stolen_Refresh_MAX     (1) // 0x00000001
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Disable_Stolen_Refresh_DEF     (0x00000000)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Disable_Stolen_Refresh_HSH     (0x011A4244)

  #define MC0_CH0_CR_MC_REFRESH_STAGGER_En_Ref_Type_Display_OFF        (14)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_En_Ref_Type_Display_WID        ( 1)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_En_Ref_Type_Display_MSK        (0x00004000)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_En_Ref_Type_Display_MIN        (0)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_En_Ref_Type_Display_MAX        (1) // 0x00000001
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_En_Ref_Type_Display_DEF        (0x00000000)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_En_Ref_Type_Display_HSH        (0x011C4244)

  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_En_OFF             (15)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_En_WID             ( 1)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_En_MSK             (0x00008000)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_En_MIN             (0)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_En_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_En_DEF             (0x00000000)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_En_HSH             (0x011E4244)

  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Trefipulse_Stagger_Disable_OFF (16)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Trefipulse_Stagger_Disable_WID ( 1)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Trefipulse_Stagger_Disable_MSK (0x00010000)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Trefipulse_Stagger_Disable_MIN (0)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Trefipulse_Stagger_Disable_MAX (1) // 0x00000001
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Trefipulse_Stagger_Disable_DEF (0x00000000)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_Trefipulse_Stagger_Disable_HSH (0x01204244)

  #define MC0_CH0_CR_MC_REFRESH_STAGGER_WakeUpOnHPM_OFF                (17)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_WakeUpOnHPM_WID                ( 1)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_WakeUpOnHPM_MSK                (0x00020000)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_WakeUpOnHPM_MIN                (0)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_WakeUpOnHPM_MAX                (1) // 0x00000001
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_WakeUpOnHPM_DEF                (0x00000000)
  #define MC0_CH0_CR_MC_REFRESH_STAGGER_WakeUpOnHPM_HSH                (0x01224244)

#define MC0_CH0_CR_TC_ZQCAL_REG                                        (0x00004248)

  #define MC0_CH0_CR_TC_ZQCAL_ZQCS_period_OFF                          ( 0)
  #define MC0_CH0_CR_TC_ZQCAL_ZQCS_period_WID                          (10)
  #define MC0_CH0_CR_TC_ZQCAL_ZQCS_period_MSK                          (0x000003FF)
  #define MC0_CH0_CR_TC_ZQCAL_ZQCS_period_MIN                          (0)
  #define MC0_CH0_CR_TC_ZQCAL_ZQCS_period_MAX                          (1023) // 0x000003FF
  #define MC0_CH0_CR_TC_ZQCAL_ZQCS_period_DEF                          (0x00000080)
  #define MC0_CH0_CR_TC_ZQCAL_ZQCS_period_HSH                          (0x0A004248)

  #define MC0_CH0_CR_TC_ZQCAL_tZQCS_OFF                                (10)
  #define MC0_CH0_CR_TC_ZQCAL_tZQCS_WID                                (10)
  #define MC0_CH0_CR_TC_ZQCAL_tZQCS_MSK                                (0x000FFC00)
  #define MC0_CH0_CR_TC_ZQCAL_tZQCS_MIN                                (0)
  #define MC0_CH0_CR_TC_ZQCAL_tZQCS_MAX                                (1023) // 0x000003FF
  #define MC0_CH0_CR_TC_ZQCAL_tZQCS_DEF                                (0x00000040)
  #define MC0_CH0_CR_TC_ZQCAL_tZQCS_HSH                                (0x0A144248)

  #define MC0_CH0_CR_TC_ZQCAL_tZQCAL_OFF                               (20)
  #define MC0_CH0_CR_TC_ZQCAL_tZQCAL_WID                               (12)
  #define MC0_CH0_CR_TC_ZQCAL_tZQCAL_MSK                               (0xFFF00000)
  #define MC0_CH0_CR_TC_ZQCAL_tZQCAL_MIN                               (0)
  #define MC0_CH0_CR_TC_ZQCAL_tZQCAL_MAX                               (4095) // 0x00000FFF
  #define MC0_CH0_CR_TC_ZQCAL_tZQCAL_DEF                               (0x00000320)
  #define MC0_CH0_CR_TC_ZQCAL_tZQCAL_HSH                               (0x0C284248)

#define MC0_CH0_CR_TC_MR2_SHADDOW_REG                                  (0x0000424C)

  #define MC0_CH0_CR_TC_MR2_SHADDOW_MR2_shaddow_OFF                    ( 0)
  #define MC0_CH0_CR_TC_MR2_SHADDOW_MR2_shaddow_WID                    (14)
  #define MC0_CH0_CR_TC_MR2_SHADDOW_MR2_shaddow_MSK                    (0x00003FFF)
  #define MC0_CH0_CR_TC_MR2_SHADDOW_MR2_shaddow_MIN                    (0)
  #define MC0_CH0_CR_TC_MR2_SHADDOW_MR2_shaddow_MAX                    (16383) // 0x00003FFF
  #define MC0_CH0_CR_TC_MR2_SHADDOW_MR2_shaddow_DEF                    (0x00000000)
  #define MC0_CH0_CR_TC_MR2_SHADDOW_MR2_shaddow_HSH                    (0x0E00424C)

  #define MC0_CH0_CR_TC_MR2_SHADDOW_SRT_avail_OFF                      (14)
  #define MC0_CH0_CR_TC_MR2_SHADDOW_SRT_avail_WID                      ( 2)
  #define MC0_CH0_CR_TC_MR2_SHADDOW_SRT_avail_MSK                      (0x0000C000)
  #define MC0_CH0_CR_TC_MR2_SHADDOW_SRT_avail_MIN                      (0)
  #define MC0_CH0_CR_TC_MR2_SHADDOW_SRT_avail_MAX                      (3) // 0x00000003
  #define MC0_CH0_CR_TC_MR2_SHADDOW_SRT_avail_DEF                      (0x00000000)
  #define MC0_CH0_CR_TC_MR2_SHADDOW_SRT_avail_HSH                      (0x021C424C)

#define MC0_CH0_CR_TC_MR4_SHADDOW_REG                                  (0x00004250)

  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_low_OFF                     ( 0)
  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_low_WID                     ( 2)
  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_low_MSK                     (0x00000003)
  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_low_MIN                     (0)
  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_low_MAX                     (3) // 0x00000003
  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_low_DEF                     (0x00000000)
  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_low_HSH                     (0x02004250)

  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_high_OFF                    ( 4)
  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_high_WID                    (10)
  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_high_MSK                    (0x00003FF0)
  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_high_MIN                    (0)
  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_high_MAX                    (1023) // 0x000003FF
  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_high_DEF                    (0x00000000)
  #define MC0_CH0_CR_TC_MR4_SHADDOW_MR4_sh_high_HSH                    (0x0A084250)

#define MC0_CH0_CR_MC_INIT_STATE_REG                                   (0x00004254)

  #define MC0_CH0_CR_MC_INIT_STATE_Rank_occupancy_OFF                  ( 0)
  #define MC0_CH0_CR_MC_INIT_STATE_Rank_occupancy_WID                  ( 8)
  #define MC0_CH0_CR_MC_INIT_STATE_Rank_occupancy_MSK                  (0x000000FF)
  #define MC0_CH0_CR_MC_INIT_STATE_Rank_occupancy_MIN                  (0)
  #define MC0_CH0_CR_MC_INIT_STATE_Rank_occupancy_MAX                  (255) // 0x000000FF
  #define MC0_CH0_CR_MC_INIT_STATE_Rank_occupancy_DEF                  (0x0000000F)
  #define MC0_CH0_CR_MC_INIT_STATE_Rank_occupancy_HSH                  (0x08004254)

  #define MC0_CH0_CR_MC_INIT_STATE_SRX_reset_OFF                       ( 8)
  #define MC0_CH0_CR_MC_INIT_STATE_SRX_reset_WID                       ( 1)
  #define MC0_CH0_CR_MC_INIT_STATE_SRX_reset_MSK                       (0x00000100)
  #define MC0_CH0_CR_MC_INIT_STATE_SRX_reset_MIN                       (0)
  #define MC0_CH0_CR_MC_INIT_STATE_SRX_reset_MAX                       (1) // 0x00000001
  #define MC0_CH0_CR_MC_INIT_STATE_SRX_reset_DEF                       (0x00000000)
  #define MC0_CH0_CR_MC_INIT_STATE_SRX_reset_HSH                       (0x01104254)

  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_OFF              ( 9)
  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_WID              ( 1)
  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_MSK              (0x00000200)
  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_MIN              (0)
  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_DEF              (0x00000000)
  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_HSH              (0x01124254)

  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_tracking_OFF     (10)
  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_tracking_WID     ( 1)
  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_tracking_MSK     (0x00000400)
  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_tracking_MIN     (0)
  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_tracking_MAX     (1) // 0x00000001
  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_tracking_DEF     (0x00000000)
  #define MC0_CH0_CR_MC_INIT_STATE_LPDDR4_current_FSP_tracking_HSH     (0x01144254)

  #define MC0_CH0_CR_MC_INIT_STATE_Reset_refresh_debt_OFF              (11)
  #define MC0_CH0_CR_MC_INIT_STATE_Reset_refresh_debt_WID              ( 1)
  #define MC0_CH0_CR_MC_INIT_STATE_Reset_refresh_debt_MSK              (0x00000800)
  #define MC0_CH0_CR_MC_INIT_STATE_Reset_refresh_debt_MIN              (0)
  #define MC0_CH0_CR_MC_INIT_STATE_Reset_refresh_debt_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_MC_INIT_STATE_Reset_refresh_debt_DEF              (0x00000000)
  #define MC0_CH0_CR_MC_INIT_STATE_Reset_refresh_debt_HSH              (0x01164254)

  #define MC0_CH0_CR_MC_INIT_STATE_Deep_SRX_reset_OFF                  (12)
  #define MC0_CH0_CR_MC_INIT_STATE_Deep_SRX_reset_WID                  ( 1)
  #define MC0_CH0_CR_MC_INIT_STATE_Deep_SRX_reset_MSK                  (0x00001000)
  #define MC0_CH0_CR_MC_INIT_STATE_Deep_SRX_reset_MIN                  (0)
  #define MC0_CH0_CR_MC_INIT_STATE_Deep_SRX_reset_MAX                  (1) // 0x00000001
  #define MC0_CH0_CR_MC_INIT_STATE_Deep_SRX_reset_DEF                  (0x00000000)
  #define MC0_CH0_CR_MC_INIT_STATE_Deep_SRX_reset_HSH                  (0x01184254)

#define MC0_CH0_CR_WDB_VISA_SEL_REG                                    (0x00004258)

  #define MC0_CH0_CR_WDB_VISA_SEL_VISAByteSel_OFF                      ( 0)
  #define MC0_CH0_CR_WDB_VISA_SEL_VISAByteSel_WID                      ( 3)
  #define MC0_CH0_CR_WDB_VISA_SEL_VISAByteSel_MSK                      (0x00000007)
  #define MC0_CH0_CR_WDB_VISA_SEL_VISAByteSel_MIN                      (0)
  #define MC0_CH0_CR_WDB_VISA_SEL_VISAByteSel_MAX                      (7) // 0x00000007
  #define MC0_CH0_CR_WDB_VISA_SEL_VISAByteSel_DEF                      (0x00000000)
  #define MC0_CH0_CR_WDB_VISA_SEL_VISAByteSel_HSH                      (0x03004258)

  #define MC0_CH0_CR_WDB_VISA_SEL_RefFSMRankSel_OFF                    ( 8)
  #define MC0_CH0_CR_WDB_VISA_SEL_RefFSMRankSel_WID                    ( 2)
  #define MC0_CH0_CR_WDB_VISA_SEL_RefFSMRankSel_MSK                    (0x00000300)
  #define MC0_CH0_CR_WDB_VISA_SEL_RefFSMRankSel_MIN                    (0)
  #define MC0_CH0_CR_WDB_VISA_SEL_RefFSMRankSel_MAX                    (3) // 0x00000003
  #define MC0_CH0_CR_WDB_VISA_SEL_RefFSMRankSel_DEF                    (0x00000000)
  #define MC0_CH0_CR_WDB_VISA_SEL_RefFSMRankSel_HSH                    (0x02104258)

  #define MC0_CH0_CR_WDB_VISA_SEL_Ref_counterSel_OFF                   (10)
  #define MC0_CH0_CR_WDB_VISA_SEL_Ref_counterSel_WID                   ( 3)
  #define MC0_CH0_CR_WDB_VISA_SEL_Ref_counterSel_MSK                   (0x00001C00)
  #define MC0_CH0_CR_WDB_VISA_SEL_Ref_counterSel_MIN                   (0)
  #define MC0_CH0_CR_WDB_VISA_SEL_Ref_counterSel_MAX                   (7) // 0x00000007
  #define MC0_CH0_CR_WDB_VISA_SEL_Ref_counterSel_DEF                   (0x00000007)
  #define MC0_CH0_CR_WDB_VISA_SEL_Ref_counterSel_HSH                   (0x03144258)

  #define MC0_CH0_CR_WDB_VISA_SEL_Enable_Ref_Status_Sample_OFF         (13)
  #define MC0_CH0_CR_WDB_VISA_SEL_Enable_Ref_Status_Sample_WID         ( 1)
  #define MC0_CH0_CR_WDB_VISA_SEL_Enable_Ref_Status_Sample_MSK         (0x00002000)
  #define MC0_CH0_CR_WDB_VISA_SEL_Enable_Ref_Status_Sample_MIN         (0)
  #define MC0_CH0_CR_WDB_VISA_SEL_Enable_Ref_Status_Sample_MAX         (1) // 0x00000001
  #define MC0_CH0_CR_WDB_VISA_SEL_Enable_Ref_Status_Sample_DEF         (0x00000000)
  #define MC0_CH0_CR_WDB_VISA_SEL_Enable_Ref_Status_Sample_HSH         (0x011A4258)

#define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_REG                             (0x00004260)

  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM0_IDLE_ENERGY_OFF         ( 0)
  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM0_IDLE_ENERGY_WID         ( 6)
  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM0_IDLE_ENERGY_MSK         (0x0000003F)
  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM0_IDLE_ENERGY_MIN         (0)
  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM0_IDLE_ENERGY_MAX         (63) // 0x0000003F
  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM0_IDLE_ENERGY_DEF         (0x00000000)
  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM0_IDLE_ENERGY_HSH         (0x06004260)

  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM1_IDLE_ENERGY_OFF         ( 8)
  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM1_IDLE_ENERGY_WID         ( 6)
  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM1_IDLE_ENERGY_MSK         (0x00003F00)
  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM1_IDLE_ENERGY_MIN         (0)
  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM1_IDLE_ENERGY_MAX         (63) // 0x0000003F
  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM1_IDLE_ENERGY_DEF         (0x00000000)
  #define MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_DIMM1_IDLE_ENERGY_HSH         (0x06104260)

#define MC0_CH0_CR_PM_DIMM_PD_ENERGY_REG                               (0x00004264)

  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM0_PD_ENERGY_OFF             ( 0)
  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM0_PD_ENERGY_WID             ( 6)
  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM0_PD_ENERGY_MSK             (0x0000003F)
  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM0_PD_ENERGY_MIN             (0)
  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM0_PD_ENERGY_MAX             (63) // 0x0000003F
  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM0_PD_ENERGY_DEF             (0x00000000)
  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM0_PD_ENERGY_HSH             (0x06004264)

  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM1_PD_ENERGY_OFF             ( 8)
  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM1_PD_ENERGY_WID             ( 6)
  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM1_PD_ENERGY_MSK             (0x00003F00)
  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM1_PD_ENERGY_MIN             (0)
  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM1_PD_ENERGY_MAX             (63) // 0x0000003F
  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM1_PD_ENERGY_DEF             (0x00000000)
  #define MC0_CH0_CR_PM_DIMM_PD_ENERGY_DIMM1_PD_ENERGY_HSH             (0x06104264)

#define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_REG                              (0x00004268)

  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM0_ACT_ENERGY_OFF           ( 0)
  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM0_ACT_ENERGY_WID           ( 8)
  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM0_ACT_ENERGY_MSK           (0x000000FF)
  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM0_ACT_ENERGY_MIN           (0)
  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM0_ACT_ENERGY_MAX           (255) // 0x000000FF
  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM0_ACT_ENERGY_DEF           (0x00000000)
  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM0_ACT_ENERGY_HSH           (0x08004268)

  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM1_ACT_ENERGY_OFF           ( 8)
  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM1_ACT_ENERGY_WID           ( 8)
  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM1_ACT_ENERGY_MSK           (0x0000FF00)
  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM1_ACT_ENERGY_MIN           (0)
  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM1_ACT_ENERGY_MAX           (255) // 0x000000FF
  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM1_ACT_ENERGY_DEF           (0x00000000)
  #define MC0_CH0_CR_PM_DIMM_ACT_ENERGY_DIMM1_ACT_ENERGY_HSH           (0x08104268)

#define MC0_CH0_CR_PM_DIMM_RD_ENERGY_REG                               (0x0000426C)

  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM0_RD_ENERGY_OFF             ( 0)
  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM0_RD_ENERGY_WID             ( 8)
  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM0_RD_ENERGY_MSK             (0x000000FF)
  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM0_RD_ENERGY_MIN             (0)
  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM0_RD_ENERGY_MAX             (255) // 0x000000FF
  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM0_RD_ENERGY_DEF             (0x00000000)
  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM0_RD_ENERGY_HSH             (0x0800426C)

  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM1_RD_ENERGY_OFF             ( 8)
  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM1_RD_ENERGY_WID             ( 8)
  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM1_RD_ENERGY_MSK             (0x0000FF00)
  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM1_RD_ENERGY_MIN             (0)
  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM1_RD_ENERGY_MAX             (255) // 0x000000FF
  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM1_RD_ENERGY_DEF             (0x00000000)
  #define MC0_CH0_CR_PM_DIMM_RD_ENERGY_DIMM1_RD_ENERGY_HSH             (0x0810426C)

#define MC0_CH0_CR_PM_DIMM_WR_ENERGY_REG                               (0x00004270)

  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM0_WR_ENERGY_OFF             ( 0)
  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM0_WR_ENERGY_WID             ( 8)
  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM0_WR_ENERGY_MSK             (0x000000FF)
  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM0_WR_ENERGY_MIN             (0)
  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM0_WR_ENERGY_MAX             (255) // 0x000000FF
  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM0_WR_ENERGY_DEF             (0x00000000)
  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM0_WR_ENERGY_HSH             (0x08004270)

  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM1_WR_ENERGY_OFF             ( 8)
  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM1_WR_ENERGY_WID             ( 8)
  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM1_WR_ENERGY_MSK             (0x0000FF00)
  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM1_WR_ENERGY_MIN             (0)
  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM1_WR_ENERGY_MAX             (255) // 0x000000FF
  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM1_WR_ENERGY_DEF             (0x00000000)
  #define MC0_CH0_CR_PM_DIMM_WR_ENERGY_DIMM1_WR_ENERGY_HSH             (0x08104270)

#define MC0_CH0_CR_SC_WR_DELAY_REG                                     (0x00004278)

  #define MC0_CH0_CR_SC_WR_DELAY_Dec_tCWL_OFF                          ( 0)
  #define MC0_CH0_CR_SC_WR_DELAY_Dec_tCWL_WID                          ( 6)
  #define MC0_CH0_CR_SC_WR_DELAY_Dec_tCWL_MSK                          (0x0000003F)
  #define MC0_CH0_CR_SC_WR_DELAY_Dec_tCWL_MIN                          (0)
  #define MC0_CH0_CR_SC_WR_DELAY_Dec_tCWL_MAX                          (63) // 0x0000003F
  #define MC0_CH0_CR_SC_WR_DELAY_Dec_tCWL_DEF                          (0x00000003)
  #define MC0_CH0_CR_SC_WR_DELAY_Dec_tCWL_HSH                          (0x06004278)

  #define MC0_CH0_CR_SC_WR_DELAY_Add_tCWL_OFF                          ( 6)
  #define MC0_CH0_CR_SC_WR_DELAY_Add_tCWL_WID                          ( 6)
  #define MC0_CH0_CR_SC_WR_DELAY_Add_tCWL_MSK                          (0x00000FC0)
  #define MC0_CH0_CR_SC_WR_DELAY_Add_tCWL_MIN                          (0)
  #define MC0_CH0_CR_SC_WR_DELAY_Add_tCWL_MAX                          (63) // 0x0000003F
  #define MC0_CH0_CR_SC_WR_DELAY_Add_tCWL_DEF                          (0x00000000)
  #define MC0_CH0_CR_SC_WR_DELAY_Add_tCWL_HSH                          (0x060C4278)

  #define MC0_CH0_CR_SC_WR_DELAY_Add_1Qclk_delay_OFF                   (12)
  #define MC0_CH0_CR_SC_WR_DELAY_Add_1Qclk_delay_WID                   ( 1)
  #define MC0_CH0_CR_SC_WR_DELAY_Add_1Qclk_delay_MSK                   (0x00001000)
  #define MC0_CH0_CR_SC_WR_DELAY_Add_1Qclk_delay_MIN                   (0)
  #define MC0_CH0_CR_SC_WR_DELAY_Add_1Qclk_delay_MAX                   (1) // 0x00000001
  #define MC0_CH0_CR_SC_WR_DELAY_Add_1Qclk_delay_DEF                   (0x00000000)
  #define MC0_CH0_CR_SC_WR_DELAY_Add_1Qclk_delay_HSH                   (0x01184278)

#define MC0_CH0_CR_READ_RETURN_DFT_REG                                 (0x0000427C)

  #define MC0_CH0_CR_READ_RETURN_DFT_ECC_OFF                           ( 0)
  #define MC0_CH0_CR_READ_RETURN_DFT_ECC_WID                           ( 8)
  #define MC0_CH0_CR_READ_RETURN_DFT_ECC_MSK                           (0x000000FF)
  #define MC0_CH0_CR_READ_RETURN_DFT_ECC_MIN                           (0)
  #define MC0_CH0_CR_READ_RETURN_DFT_ECC_MAX                           (255) // 0x000000FF
  #define MC0_CH0_CR_READ_RETURN_DFT_ECC_DEF                           (0x00000000)
  #define MC0_CH0_CR_READ_RETURN_DFT_ECC_HSH                           (0x0800427C)

  #define MC0_CH0_CR_READ_RETURN_DFT_RRD_DFT_Mode_OFF                  ( 8)
  #define MC0_CH0_CR_READ_RETURN_DFT_RRD_DFT_Mode_WID                  ( 2)
  #define MC0_CH0_CR_READ_RETURN_DFT_RRD_DFT_Mode_MSK                  (0x00000300)
  #define MC0_CH0_CR_READ_RETURN_DFT_RRD_DFT_Mode_MIN                  (0)
  #define MC0_CH0_CR_READ_RETURN_DFT_RRD_DFT_Mode_MAX                  (3) // 0x00000003
  #define MC0_CH0_CR_READ_RETURN_DFT_RRD_DFT_Mode_DEF                  (0x00000000)
  #define MC0_CH0_CR_READ_RETURN_DFT_RRD_DFT_Mode_HSH                  (0x0210427C)

  #define MC0_CH0_CR_READ_RETURN_DFT_LFSR_Seed_Index_OFF               (10)
  #define MC0_CH0_CR_READ_RETURN_DFT_LFSR_Seed_Index_WID               ( 5)
  #define MC0_CH0_CR_READ_RETURN_DFT_LFSR_Seed_Index_MSK               (0x00007C00)
  #define MC0_CH0_CR_READ_RETURN_DFT_LFSR_Seed_Index_MIN               (0)
  #define MC0_CH0_CR_READ_RETURN_DFT_LFSR_Seed_Index_MAX               (31) // 0x0000001F
  #define MC0_CH0_CR_READ_RETURN_DFT_LFSR_Seed_Index_DEF               (0x00000000)
  #define MC0_CH0_CR_READ_RETURN_DFT_LFSR_Seed_Index_HSH               (0x0514427C)

  #define MC0_CH0_CR_READ_RETURN_DFT_Inversion_Mode_OFF                (15)
  #define MC0_CH0_CR_READ_RETURN_DFT_Inversion_Mode_WID                ( 1)
  #define MC0_CH0_CR_READ_RETURN_DFT_Inversion_Mode_MSK                (0x00008000)
  #define MC0_CH0_CR_READ_RETURN_DFT_Inversion_Mode_MIN                (0)
  #define MC0_CH0_CR_READ_RETURN_DFT_Inversion_Mode_MAX                (1) // 0x00000001
  #define MC0_CH0_CR_READ_RETURN_DFT_Inversion_Mode_DEF                (0x00000000)
  #define MC0_CH0_CR_READ_RETURN_DFT_Inversion_Mode_HSH                (0x011E427C)

  #define MC0_CH0_CR_READ_RETURN_DFT_AddressBased_OFF                  (16)
  #define MC0_CH0_CR_READ_RETURN_DFT_AddressBased_WID                  ( 1)
  #define MC0_CH0_CR_READ_RETURN_DFT_AddressBased_MSK                  (0x00010000)
  #define MC0_CH0_CR_READ_RETURN_DFT_AddressBased_MIN                  (0)
  #define MC0_CH0_CR_READ_RETURN_DFT_AddressBased_MAX                  (1) // 0x00000001
  #define MC0_CH0_CR_READ_RETURN_DFT_AddressBased_DEF                  (0x00000000)
  #define MC0_CH0_CR_READ_RETURN_DFT_AddressBased_HSH                  (0x0120427C)

#define MC0_CH0_CR_DESWIZZLE_LOW_REG                                   (0x00004280)
//Duplicate of MC0_CH0_CR_DESWIZZLE_LOW_ERM_REG

#define MC0_CH0_CR_SC_PBR_REG                                          (0x00004288)

  #define MC0_CH0_CR_SC_PBR_PBR_Disable_OFF                            ( 0)
  #define MC0_CH0_CR_SC_PBR_PBR_Disable_WID                            ( 1)
  #define MC0_CH0_CR_SC_PBR_PBR_Disable_MSK                            (0x00000001)
  #define MC0_CH0_CR_SC_PBR_PBR_Disable_MIN                            (0)
  #define MC0_CH0_CR_SC_PBR_PBR_Disable_MAX                            (1) // 0x00000001
  #define MC0_CH0_CR_SC_PBR_PBR_Disable_DEF                            (0x00000001)
  #define MC0_CH0_CR_SC_PBR_PBR_Disable_HSH                            (0x01004288)

  #define MC0_CH0_CR_SC_PBR_PBR_OOO_Dis_OFF                            ( 1)
  #define MC0_CH0_CR_SC_PBR_PBR_OOO_Dis_WID                            ( 1)
  #define MC0_CH0_CR_SC_PBR_PBR_OOO_Dis_MSK                            (0x00000002)
  #define MC0_CH0_CR_SC_PBR_PBR_OOO_Dis_MIN                            (0)
  #define MC0_CH0_CR_SC_PBR_PBR_OOO_Dis_MAX                            (1) // 0x00000001
  #define MC0_CH0_CR_SC_PBR_PBR_OOO_Dis_DEF                            (0x00000000)
  #define MC0_CH0_CR_SC_PBR_PBR_OOO_Dis_HSH                            (0x01024288)

  #define MC0_CH0_CR_SC_PBR_PBR_Issue_NOP_OFF                          ( 2)
  #define MC0_CH0_CR_SC_PBR_PBR_Issue_NOP_WID                          ( 1)
  #define MC0_CH0_CR_SC_PBR_PBR_Issue_NOP_MSK                          (0x00000004)
  #define MC0_CH0_CR_SC_PBR_PBR_Issue_NOP_MIN                          (0)
  #define MC0_CH0_CR_SC_PBR_PBR_Issue_NOP_MAX                          (1) // 0x00000001
  #define MC0_CH0_CR_SC_PBR_PBR_Issue_NOP_DEF                          (0x00000000)
  #define MC0_CH0_CR_SC_PBR_PBR_Issue_NOP_HSH                          (0x01044288)

  #define MC0_CH0_CR_SC_PBR_PBR_Disable_on_hot_OFF                     ( 3)
  #define MC0_CH0_CR_SC_PBR_PBR_Disable_on_hot_WID                     ( 1)
  #define MC0_CH0_CR_SC_PBR_PBR_Disable_on_hot_MSK                     (0x00000008)
  #define MC0_CH0_CR_SC_PBR_PBR_Disable_on_hot_MIN                     (0)
  #define MC0_CH0_CR_SC_PBR_PBR_Disable_on_hot_MAX                     (1) // 0x00000001
  #define MC0_CH0_CR_SC_PBR_PBR_Disable_on_hot_DEF                     (0x00000000)
  #define MC0_CH0_CR_SC_PBR_PBR_Disable_on_hot_HSH                     (0x01064288)

  #define MC0_CH0_CR_SC_PBR_PBR_Exit_on_Idle_Cnt_OFF                   ( 4)
  #define MC0_CH0_CR_SC_PBR_PBR_Exit_on_Idle_Cnt_WID                   ( 6)
  #define MC0_CH0_CR_SC_PBR_PBR_Exit_on_Idle_Cnt_MSK                   (0x000003F0)
  #define MC0_CH0_CR_SC_PBR_PBR_Exit_on_Idle_Cnt_MIN                   (0)
  #define MC0_CH0_CR_SC_PBR_PBR_Exit_on_Idle_Cnt_MAX                   (63) // 0x0000003F
  #define MC0_CH0_CR_SC_PBR_PBR_Exit_on_Idle_Cnt_DEF                   (0x00000001)
  #define MC0_CH0_CR_SC_PBR_PBR_Exit_on_Idle_Cnt_HSH                   (0x06084288)

  #define MC0_CH0_CR_SC_PBR_tRFCpb_OFF                                 (10)
  #define MC0_CH0_CR_SC_PBR_tRFCpb_WID                                 (10)
  #define MC0_CH0_CR_SC_PBR_tRFCpb_MSK                                 (0x000FFC00)
  #define MC0_CH0_CR_SC_PBR_tRFCpb_MIN                                 (0)
  #define MC0_CH0_CR_SC_PBR_tRFCpb_MAX                                 (1023) // 0x000003FF
  #define MC0_CH0_CR_SC_PBR_tRFCpb_DEF                                 (0x0000003C)
  #define MC0_CH0_CR_SC_PBR_tRFCpb_HSH                                 (0x0A144288)

  #define MC0_CH0_CR_SC_PBR_Refresh_ABR_release_OFF                    (20)
  #define MC0_CH0_CR_SC_PBR_Refresh_ABR_release_WID                    ( 4)
  #define MC0_CH0_CR_SC_PBR_Refresh_ABR_release_MSK                    (0x00F00000)
  #define MC0_CH0_CR_SC_PBR_Refresh_ABR_release_MIN                    (0)
  #define MC0_CH0_CR_SC_PBR_Refresh_ABR_release_MAX                    (15) // 0x0000000F
  #define MC0_CH0_CR_SC_PBR_Refresh_ABR_release_DEF                    (0x00000007)
  #define MC0_CH0_CR_SC_PBR_Refresh_ABR_release_HSH                    (0x04284288)

  #define MC0_CH0_CR_SC_PBR_PBR_extended_disable_while_DQS_OSC_OFF     (24)
  #define MC0_CH0_CR_SC_PBR_PBR_extended_disable_while_DQS_OSC_WID     ( 1)
  #define MC0_CH0_CR_SC_PBR_PBR_extended_disable_while_DQS_OSC_MSK     (0x01000000)
  #define MC0_CH0_CR_SC_PBR_PBR_extended_disable_while_DQS_OSC_MIN     (0)
  #define MC0_CH0_CR_SC_PBR_PBR_extended_disable_while_DQS_OSC_MAX     (1) // 0x00000001
  #define MC0_CH0_CR_SC_PBR_PBR_extended_disable_while_DQS_OSC_DEF     (0x00000001)
  #define MC0_CH0_CR_SC_PBR_PBR_extended_disable_while_DQS_OSC_HSH     (0x01304288)

  #define MC0_CH0_CR_SC_PBR_SPARE_OFF                                  (25)
  #define MC0_CH0_CR_SC_PBR_SPARE_WID                                  ( 7)
  #define MC0_CH0_CR_SC_PBR_SPARE_MSK                                  (0xFE000000)
  #define MC0_CH0_CR_SC_PBR_SPARE_MIN                                  (0)
  #define MC0_CH0_CR_SC_PBR_SPARE_MAX                                  (127) // 0x0000007F
  #define MC0_CH0_CR_SC_PBR_SPARE_DEF                                  (0x00000000)
  #define MC0_CH0_CR_SC_PBR_SPARE_HSH                                  (0x07324288)

#define MC0_CH0_CR_LPDDR_PASR_REG                                      (0x00004290)

  #define MC0_CH0_CR_LPDDR_PASR_row_msb_OFF                            ( 0)
  #define MC0_CH0_CR_LPDDR_PASR_row_msb_WID                            ( 2)
  #define MC0_CH0_CR_LPDDR_PASR_row_msb_MSK                            (0x00000003)
  #define MC0_CH0_CR_LPDDR_PASR_row_msb_MIN                            (0)
  #define MC0_CH0_CR_LPDDR_PASR_row_msb_MAX                            (3) // 0x00000003
  #define MC0_CH0_CR_LPDDR_PASR_row_msb_DEF                            (0x00000000)
  #define MC0_CH0_CR_LPDDR_PASR_row_msb_HSH                            (0x02004290)

  #define MC0_CH0_CR_LPDDR_PASR_disabled_segment_OFF                   ( 2)
  #define MC0_CH0_CR_LPDDR_PASR_disabled_segment_WID                   ( 8)
  #define MC0_CH0_CR_LPDDR_PASR_disabled_segment_MSK                   (0x000003FC)
  #define MC0_CH0_CR_LPDDR_PASR_disabled_segment_MIN                   (0)
  #define MC0_CH0_CR_LPDDR_PASR_disabled_segment_MAX                   (255) // 0x000000FF
  #define MC0_CH0_CR_LPDDR_PASR_disabled_segment_DEF                   (0x00000000)
  #define MC0_CH0_CR_LPDDR_PASR_disabled_segment_HSH                   (0x08044290)

  #define MC0_CH0_CR_LPDDR_PASR_new_wr_req_hit_pasr_dis_seg_OFF        (31)
  #define MC0_CH0_CR_LPDDR_PASR_new_wr_req_hit_pasr_dis_seg_WID        ( 1)
  #define MC0_CH0_CR_LPDDR_PASR_new_wr_req_hit_pasr_dis_seg_MSK        (0x80000000)
  #define MC0_CH0_CR_LPDDR_PASR_new_wr_req_hit_pasr_dis_seg_MIN        (0)
  #define MC0_CH0_CR_LPDDR_PASR_new_wr_req_hit_pasr_dis_seg_MAX        (1) // 0x00000001
  #define MC0_CH0_CR_LPDDR_PASR_new_wr_req_hit_pasr_dis_seg_DEF        (0x00000000)
  #define MC0_CH0_CR_LPDDR_PASR_new_wr_req_hit_pasr_dis_seg_HSH        (0x013E4290)

#define MC0_CH0_CR_TC_LPDDR4_MISC_REG                                  (0x00004294)

  #define MC0_CH0_CR_TC_LPDDR4_MISC_tOSCO_OFF                          ( 0)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tOSCO_WID                          ( 7)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tOSCO_MSK                          (0x0000007F)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tOSCO_MIN                          (0)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tOSCO_MAX                          (127) // 0x0000007F
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tOSCO_DEF                          (0x00000056)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tOSCO_HSH                          (0x07004294)

  #define MC0_CH0_CR_TC_LPDDR4_MISC_tPREMRR_OFF                        ( 7)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tPREMRR_WID                        ( 7)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tPREMRR_MSK                        (0x00003F80)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tPREMRR_MIN                        (0)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tPREMRR_MAX                        (127) // 0x0000007F
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tPREMRR_DEF                        (0x00000010)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tPREMRR_HSH                        (0x070E4294)

  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRRMRW_OFF                        (14)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRRMRW_WID                        ( 7)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRRMRW_MSK                        (0x001FC000)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRRMRW_MIN                        (0)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRRMRW_MAX                        (127) // 0x0000007F
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRRMRW_DEF                        (0x00000010)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRRMRW_HSH                        (0x071C4294)

  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRR_OFF                           (21)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRR_WID                           ( 7)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRR_MSK                           (0x0FE00000)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRR_MIN                           (0)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRR_MAX                           (127) // 0x0000007F
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRR_DEF                           (0x00000010)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRR_HSH                           (0x072A4294)

  #define MC0_CH0_CR_TC_LPDDR4_MISC_Manual_DQS_MR_READ_OFF             (28)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_Manual_DQS_MR_READ_WID             ( 1)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_Manual_DQS_MR_READ_MSK             (0x10000000)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_Manual_DQS_MR_READ_MIN             (0)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_Manual_DQS_MR_READ_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_TC_LPDDR4_MISC_Manual_DQS_MR_READ_DEF             (0x00000000)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_Manual_DQS_MR_READ_HSH             (0x01384294)

#define MC0_CH0_CR_TC_LPDDR4_MISC_A0_REG                               (0x00004294)

  #define MC0_CH0_CR_TC_LPDDR4_MISC_tOSCO_A0_OFF                       ( 0)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tOSCO_A0_WID                       ( 7)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tOSCO_A0_MSK                       (0x0000007F)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tOSCO_A0_MIN                       (0)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tOSCO_A0_MAX                       (127) // 0x0000007F
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tOSCO_A0_DEF                       (0x00000056)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tOSCO_A0_HSH                       (0x07004294)

  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRR_A0_OFF                        ( 7)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRR_A0_WID                        ( 5)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRR_A0_MSK                        (0x00000F80)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRR_A0_MIN                        (0)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRR_A0_MAX                        (31) // 0x0000001F
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRR_A0_DEF                        (0x00000010)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRR_A0_HSH                        (0x050E4294)

  #define MC0_CH0_CR_TC_LPDDR4_MISC_Manual_DQS_MR_READ_A0_OFF          (12)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_Manual_DQS_MR_READ_A0_WID          ( 1)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_Manual_DQS_MR_READ_A0_MSK          (0x00001000)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_Manual_DQS_MR_READ_A0_MIN          (0)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_Manual_DQS_MR_READ_A0_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_TC_LPDDR4_MISC_Manual_DQS_MR_READ_A0_DEF          (0x00000000)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_Manual_DQS_MR_READ_A0_HSH          (0x01184294)

  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRRMRW_A0_OFF                     (13)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRRMRW_A0_WID                     ( 7)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRRMRW_A0_MSK                     (0x000FE000)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRRMRW_A0_MIN                     (0)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRRMRW_A0_MAX                     (127) // 0x0000007F
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRRMRW_A0_DEF                     (0x00000010)
  #define MC0_CH0_CR_TC_LPDDR4_MISC_tMRRMRW_A0_HSH                     (0x071A4294)

#define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_REG                              (0x00004298)

  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_16_OFF                     ( 0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_16_WID                     ( 3)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_16_MSK                     (0x00000007)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_16_MIN                     (0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_16_MAX                     (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_16_DEF                     (0x00000000)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_16_HSH                     (0x43004298)

  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_17_OFF                     ( 3)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_17_WID                     ( 3)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_17_MSK                     (0x00000038)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_17_MIN                     (0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_17_MAX                     (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_17_DEF                     (0x00000001)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_17_HSH                     (0x43064298)

  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_18_OFF                     ( 6)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_18_WID                     ( 3)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_18_MSK                     (0x000001C0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_18_MIN                     (0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_18_MAX                     (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_18_DEF                     (0x00000002)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_18_HSH                     (0x430C4298)

  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_19_OFF                     ( 9)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_19_WID                     ( 3)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_19_MSK                     (0x00000E00)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_19_MIN                     (0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_19_MAX                     (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_19_DEF                     (0x00000003)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_19_HSH                     (0x43124298)

  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_20_OFF                     (12)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_20_WID                     ( 3)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_20_MSK                     (0x00007000)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_20_MIN                     (0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_20_MAX                     (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_20_DEF                     (0x00000004)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_20_HSH                     (0x43184298)

  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_24_OFF                     (15)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_24_WID                     ( 3)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_24_MSK                     (0x00038000)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_24_MIN                     (0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_24_MAX                     (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_24_DEF                     (0x00000000)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_24_HSH                     (0x431E4298)

  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_25_OFF                     (18)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_25_WID                     ( 3)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_25_MSK                     (0x001C0000)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_25_MIN                     (0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_25_MAX                     (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_25_DEF                     (0x00000001)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_25_HSH                     (0x43244298)

  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_26_OFF                     (21)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_26_WID                     ( 3)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_26_MSK                     (0x00E00000)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_26_MIN                     (0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_26_MAX                     (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_26_DEF                     (0x00000002)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_26_HSH                     (0x432A4298)

  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_27_OFF                     (24)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_27_WID                     ( 3)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_27_MSK                     (0x07000000)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_27_MIN                     (0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_27_MAX                     (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_27_DEF                     (0x00000003)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_27_HSH                     (0x43304298)

  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_28_OFF                     (27)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_28_WID                     ( 3)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_28_MSK                     (0x38000000)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_28_MIN                     (0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_28_MAX                     (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_28_DEF                     (0x00000004)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Bit_28_HSH                     (0x43364298)

  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_0_OFF                     (32)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_0_WID                     ( 3)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_0_MSK                     (0x0000000700000000ULL)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_0_MIN                     (0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_0_MAX                     (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_0_DEF                     (0x00000000)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_0_HSH                     (0x43404298)

  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_1_OFF                     (35)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_1_WID                     ( 3)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_1_MSK                     (0x0000003800000000ULL)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_1_MIN                     (0)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_1_MAX                     (7) // 0x00000007
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_1_DEF                     (0x00000001)
  #define MC0_CH0_CR_DESWIZZLE_HIGH_ERM_Byte_1_HSH                     (0x43464298)

#define MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_REG                      (0x000042B0)

  #define MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_Count_OFF              ( 0)
  #define MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_Count_WID              (64)
  #define MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_Count_MSK              (0xFFFFFFFFFFFFFFFFULL)
  #define MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_Count_MIN              (0)
  #define MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_Count_MAX              (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_Count_DEF              (0x00000000)
  #define MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_Count_HSH              (0x400042B0)

#define MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_A0_REG                   (0x000042B0)

  #define MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_Count_A0_OFF           ( 0)
  #define MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_Count_A0_WID           (32)
  #define MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_Count_A0_MSK           (0xFFFFFFFF)
  #define MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_Count_A0_MIN           (0)
  #define MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_Count_A0_MAX           (4294967295) // 0xFFFFFFFF
  #define MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_Count_A0_DEF           (0x00000000)
  #define MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_Count_A0_HSH           (0x200042B0)

#define MC0_CH0_CR_DESWIZZLE_HIGH_REG                                  (0x000042B8)
//Duplicate of MC0_CH0_CR_DESWIZZLE_HIGH_ERM_REG

#define MC0_CH0_CR_TC_SREXITTP_REG                                     (0x000042C0)

  #define MC0_CH0_CR_TC_SREXITTP_tXSR_OFF                              ( 0)
  #define MC0_CH0_CR_TC_SREXITTP_tXSR_WID                              (12)
  #define MC0_CH0_CR_TC_SREXITTP_tXSR_MSK                              (0x00000FFF)
  #define MC0_CH0_CR_TC_SREXITTP_tXSR_MIN                              (0)
  #define MC0_CH0_CR_TC_SREXITTP_tXSR_MAX                              (4095) // 0x00000FFF
  #define MC0_CH0_CR_TC_SREXITTP_tXSR_DEF                              (0x00000000)
  #define MC0_CH0_CR_TC_SREXITTP_tXSR_HSH                              (0x4C0042C0)

  #define MC0_CH0_CR_TC_SREXITTP_tXSR_DS_OFF                           (20)
  #define MC0_CH0_CR_TC_SREXITTP_tXSR_DS_WID                           (14)
  #define MC0_CH0_CR_TC_SREXITTP_tXSR_DS_MSK                           (0x00000003FFF00000ULL)
  #define MC0_CH0_CR_TC_SREXITTP_tXSR_DS_MIN                           (0)
  #define MC0_CH0_CR_TC_SREXITTP_tXSR_DS_MAX                           (16383) // 0x00003FFF
  #define MC0_CH0_CR_TC_SREXITTP_tXSR_DS_DEF                           (0x00000000)
  #define MC0_CH0_CR_TC_SREXITTP_tXSR_DS_HSH                           (0x4E2842C0)

  #define MC0_CH0_CR_TC_SREXITTP_serial_zq_between_sub_ch_OFF          (34)
  #define MC0_CH0_CR_TC_SREXITTP_serial_zq_between_sub_ch_WID          ( 1)
  #define MC0_CH0_CR_TC_SREXITTP_serial_zq_between_sub_ch_MSK          (0x0000000400000000ULL)
  #define MC0_CH0_CR_TC_SREXITTP_serial_zq_between_sub_ch_MIN          (0)
  #define MC0_CH0_CR_TC_SREXITTP_serial_zq_between_sub_ch_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_TC_SREXITTP_serial_zq_between_sub_ch_DEF          (0x00000000)
  #define MC0_CH0_CR_TC_SREXITTP_serial_zq_between_sub_ch_HSH          (0x414442C0)

  #define MC0_CH0_CR_TC_SREXITTP_count_block_wr_on_srx_OFF             (35)
  #define MC0_CH0_CR_TC_SREXITTP_count_block_wr_on_srx_WID             (16)
  #define MC0_CH0_CR_TC_SREXITTP_count_block_wr_on_srx_MSK             (0x0007FFF800000000ULL)
  #define MC0_CH0_CR_TC_SREXITTP_count_block_wr_on_srx_MIN             (0)
  #define MC0_CH0_CR_TC_SREXITTP_count_block_wr_on_srx_MAX             (65535) // 0x0000FFFF
  #define MC0_CH0_CR_TC_SREXITTP_count_block_wr_on_srx_DEF             (0x00000014)
  #define MC0_CH0_CR_TC_SREXITTP_count_block_wr_on_srx_HSH             (0x504642C0)

#define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_REG                       (0x000042C8)

  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_DQSOSCL_PERIOD_OFF      ( 0)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_DQSOSCL_PERIOD_WID      (16)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_DQSOSCL_PERIOD_MSK      (0x0000FFFF)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_DQSOSCL_PERIOD_MIN      (0)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_DQSOSCL_PERIOD_MAX      (65535) // 0x0000FFFF
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_DQSOSCL_PERIOD_DEF      (0x00000100)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_DQSOSCL_PERIOD_HSH      (0x100042C8)

  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_MR19toBlockAckPeriod_OFF (16)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_MR19toBlockAckPeriod_WID ( 8)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_MR19toBlockAckPeriod_MSK (0x00FF0000)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_MR19toBlockAckPeriod_MIN (0)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_MR19toBlockAckPeriod_MAX (255) // 0x000000FF
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_MR19toBlockAckPeriod_DEF (0x00000007)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_MR19toBlockAckPeriod_HSH (0x082042C8)

  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_DIS_SRX_DQSOSCL_OFF     (24)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_DIS_SRX_DQSOSCL_WID     ( 1)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_DIS_SRX_DQSOSCL_MSK     (0x01000000)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_DIS_SRX_DQSOSCL_MIN     (0)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_DIS_SRX_DQSOSCL_MAX     (1) // 0x00000001
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_DIS_SRX_DQSOSCL_DEF     (0x00000000)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_DIS_SRX_DQSOSCL_HSH     (0x013042C8)

  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_disable_wr_on_pkgc_exit_OFF (26)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_disable_wr_on_pkgc_exit_WID ( 1)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_disable_wr_on_pkgc_exit_MSK (0x04000000)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_disable_wr_on_pkgc_exit_MIN (0)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_disable_wr_on_pkgc_exit_MAX (1) // 0x00000001
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_disable_wr_on_pkgc_exit_DEF (0x00000000)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_disable_wr_on_pkgc_exit_HSH (0x013442C8)

  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_disable_wr_on_SR_exit_OFF (27)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_disable_wr_on_SR_exit_WID ( 1)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_disable_wr_on_SR_exit_MSK (0x08000000)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_disable_wr_on_SR_exit_MIN (0)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_disable_wr_on_SR_exit_MAX (1) // 0x00000001
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_disable_wr_on_SR_exit_DEF (0x00000000)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_disable_wr_on_SR_exit_HSH (0x013642C8)

  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_disable_PMreqWaitForMR19_OFF (28)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_disable_PMreqWaitForMR19_WID ( 1)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_disable_PMreqWaitForMR19_MSK (0x10000000)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_disable_PMreqWaitForMR19_MIN (0)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_disable_PMreqWaitForMR19_MAX (1) // 0x00000001
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_disable_PMreqWaitForMR19_DEF (0x00000000)
  #define MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_disable_PMreqWaitForMR19_HSH (0x013842C8)

#define MC0_CH0_CR_WDB_RD_WR_DFX_DATA_REG                              (0x000042D8)

  #define MC0_CH0_CR_WDB_RD_WR_DFX_DATA_DATA_OFF                       ( 0)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_DATA_DATA_WID                       (64)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_DATA_DATA_MSK                       (0xFFFFFFFFFFFFFFFFULL)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_DATA_DATA_MIN                       (0)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_DATA_DATA_MAX                       (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define MC0_CH0_CR_WDB_RD_WR_DFX_DATA_DATA_DEF                       (0x00000000)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_DATA_DATA_HSH                       (0x400042D8)

#define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_REG                               (0x000042E0)

  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_GO_OFF                          ( 0)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_GO_WID                          ( 1)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_GO_MSK                          (0x00000001)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_GO_MIN                          (0)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_GO_MAX                          (1) // 0x00000001
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_GO_DEF                          (0x00000000)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_GO_HSH                          (0x010042E0)

  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Chunk_Sel_OFF                   ( 1)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Chunk_Sel_WID                   ( 8)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Chunk_Sel_MSK                   (0x000001FE)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Chunk_Sel_MIN                   (0)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Chunk_Sel_MAX                   (255) // 0x000000FF
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Chunk_Sel_DEF                   (0x00000000)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Chunk_Sel_HSH                   (0x080242E0)

  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Op_OFF                          ( 9)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Op_WID                          ( 1)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Op_MSK                          (0x00000200)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Op_MIN                          (0)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Op_MAX                          (1) // 0x00000001
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Op_DEF                          (0x00000000)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_Op_HSH                          (0x011242E0)

  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_SubCh_OFF                       (10)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_SubCh_WID                       ( 1)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_SubCh_MSK                       (0x00000400)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_SubCh_MIN                       (0)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_SubCh_MAX                       (1) // 0x00000001
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_SubCh_DEF                       (0x00000000)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_SubCh_HSH                       (0x011442E0)

  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_WID_OFF                         (11)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_WID_WID                         ( 6)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_WID_MSK                         (0x0001F800)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_WID_MIN                         (0)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_WID_MAX                         (63) // 0x0000003F
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_WID_DEF                         (0x00000000)
  #define MC0_CH0_CR_WDB_RD_WR_DFX_CTL_WID_HSH                         (0x061642E0)

#define MC0_CH0_CR_REF_FSM_STATUS_REG                                  (0x000042E4)

  #define MC0_CH0_CR_REF_FSM_STATUS_DQS_INTERVAL_FSM_status_OFF        ( 0)
  #define MC0_CH0_CR_REF_FSM_STATUS_DQS_INTERVAL_FSM_status_WID        ( 4)
  #define MC0_CH0_CR_REF_FSM_STATUS_DQS_INTERVAL_FSM_status_MSK        (0x0000000F)
  #define MC0_CH0_CR_REF_FSM_STATUS_DQS_INTERVAL_FSM_status_MIN        (0)
  #define MC0_CH0_CR_REF_FSM_STATUS_DQS_INTERVAL_FSM_status_MAX        (15) // 0x0000000F
  #define MC0_CH0_CR_REF_FSM_STATUS_DQS_INTERVAL_FSM_status_DEF        (0x00000000)
  #define MC0_CH0_CR_REF_FSM_STATUS_DQS_INTERVAL_FSM_status_HSH        (0x040042E4)

  #define MC0_CH0_CR_REF_FSM_STATUS_TEMP_RD_FSM_status_OFF             ( 4)
  #define MC0_CH0_CR_REF_FSM_STATUS_TEMP_RD_FSM_status_WID             ( 5)
  #define MC0_CH0_CR_REF_FSM_STATUS_TEMP_RD_FSM_status_MSK             (0x000001F0)
  #define MC0_CH0_CR_REF_FSM_STATUS_TEMP_RD_FSM_status_MIN             (0)
  #define MC0_CH0_CR_REF_FSM_STATUS_TEMP_RD_FSM_status_MAX             (31) // 0x0000001F
  #define MC0_CH0_CR_REF_FSM_STATUS_TEMP_RD_FSM_status_DEF             (0x00000000)
  #define MC0_CH0_CR_REF_FSM_STATUS_TEMP_RD_FSM_status_HSH             (0x050842E4)

  #define MC0_CH0_CR_REF_FSM_STATUS_REFRATE_CHNG_FSM_status_OFF        ( 9)
  #define MC0_CH0_CR_REF_FSM_STATUS_REFRATE_CHNG_FSM_status_WID        ( 2)
  #define MC0_CH0_CR_REF_FSM_STATUS_REFRATE_CHNG_FSM_status_MSK        (0x00000600)
  #define MC0_CH0_CR_REF_FSM_STATUS_REFRATE_CHNG_FSM_status_MIN        (0)
  #define MC0_CH0_CR_REF_FSM_STATUS_REFRATE_CHNG_FSM_status_MAX        (3) // 0x00000003
  #define MC0_CH0_CR_REF_FSM_STATUS_REFRATE_CHNG_FSM_status_DEF        (0x00000000)
  #define MC0_CH0_CR_REF_FSM_STATUS_REFRATE_CHNG_FSM_status_HSH        (0x021242E4)

  #define MC0_CH0_CR_REF_FSM_STATUS_ZQCS_FSM_status_OFF                (11)
  #define MC0_CH0_CR_REF_FSM_STATUS_ZQCS_FSM_status_WID                ( 3)
  #define MC0_CH0_CR_REF_FSM_STATUS_ZQCS_FSM_status_MSK                (0x00003800)
  #define MC0_CH0_CR_REF_FSM_STATUS_ZQCS_FSM_status_MIN                (0)
  #define MC0_CH0_CR_REF_FSM_STATUS_ZQCS_FSM_status_MAX                (7) // 0x00000007
  #define MC0_CH0_CR_REF_FSM_STATUS_ZQCS_FSM_status_DEF                (0x00000000)
  #define MC0_CH0_CR_REF_FSM_STATUS_ZQCS_FSM_status_HSH                (0x031642E4)

  #define MC0_CH0_CR_REF_FSM_STATUS_EXE_REF_FSM_status_OFF             (14)
  #define MC0_CH0_CR_REF_FSM_STATUS_EXE_REF_FSM_status_WID             ( 3)
  #define MC0_CH0_CR_REF_FSM_STATUS_EXE_REF_FSM_status_MSK             (0x0001C000)
  #define MC0_CH0_CR_REF_FSM_STATUS_EXE_REF_FSM_status_MIN             (0)
  #define MC0_CH0_CR_REF_FSM_STATUS_EXE_REF_FSM_status_MAX             (7) // 0x00000007
  #define MC0_CH0_CR_REF_FSM_STATUS_EXE_REF_FSM_status_DEF             (0x00000000)
  #define MC0_CH0_CR_REF_FSM_STATUS_EXE_REF_FSM_status_HSH             (0x031C42E4)

  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_REF_FSM_status_OFF            (17)
  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_REF_FSM_status_WID            ( 3)
  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_REF_FSM_status_MSK            (0x000E0000)
  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_REF_FSM_status_MIN            (0)
  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_REF_FSM_status_MAX            (7) // 0x00000007
  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_REF_FSM_status_DEF            (0x00000000)
  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_REF_FSM_status_HSH            (0x032242E4)

  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_SR_FSM_status_OFF             (20)
  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_SR_FSM_status_WID             ( 4)
  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_SR_FSM_status_MSK             (0x00F00000)
  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_SR_FSM_status_MIN             (0)
  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_SR_FSM_status_MAX             (15) // 0x0000000F
  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_SR_FSM_status_DEF             (0x00000000)
  #define MC0_CH0_CR_REF_FSM_STATUS_MAIN_SR_FSM_status_HSH             (0x042842E4)

  #define MC0_CH0_CR_REF_FSM_STATUS_counter_status_OFF                 (24)
  #define MC0_CH0_CR_REF_FSM_STATUS_counter_status_WID                 ( 8)
  #define MC0_CH0_CR_REF_FSM_STATUS_counter_status_MSK                 (0xFF000000)
  #define MC0_CH0_CR_REF_FSM_STATUS_counter_status_MIN                 (0)
  #define MC0_CH0_CR_REF_FSM_STATUS_counter_status_MAX                 (255) // 0x000000FF
  #define MC0_CH0_CR_REF_FSM_STATUS_counter_status_DEF                 (0x00000000)
  #define MC0_CH0_CR_REF_FSM_STATUS_counter_status_HSH                 (0x083042E4)

#define MC0_CH0_CR_WDB_MBIST_0_REG                                     (0x000042E8)

  #define MC0_CH0_CR_WDB_MBIST_0_PASS_OFF                              ( 0)
  #define MC0_CH0_CR_WDB_MBIST_0_PASS_WID                              ( 1)
  #define MC0_CH0_CR_WDB_MBIST_0_PASS_MSK                              (0x00000001)
  #define MC0_CH0_CR_WDB_MBIST_0_PASS_MIN                              (0)
  #define MC0_CH0_CR_WDB_MBIST_0_PASS_MAX                              (1) // 0x00000001
  #define MC0_CH0_CR_WDB_MBIST_0_PASS_DEF                              (0x00000000)
  #define MC0_CH0_CR_WDB_MBIST_0_PASS_HSH                              (0x010042E8)

  #define MC0_CH0_CR_WDB_MBIST_0_Complete_OFF                          ( 1)
  #define MC0_CH0_CR_WDB_MBIST_0_Complete_WID                          ( 1)
  #define MC0_CH0_CR_WDB_MBIST_0_Complete_MSK                          (0x00000002)
  #define MC0_CH0_CR_WDB_MBIST_0_Complete_MIN                          (0)
  #define MC0_CH0_CR_WDB_MBIST_0_Complete_MAX                          (1) // 0x00000001
  #define MC0_CH0_CR_WDB_MBIST_0_Complete_DEF                          (0x00000000)
  #define MC0_CH0_CR_WDB_MBIST_0_Complete_HSH                          (0x010242E8)

  #define MC0_CH0_CR_WDB_MBIST_0_Inject_Failure_OFF                    ( 8)
  #define MC0_CH0_CR_WDB_MBIST_0_Inject_Failure_WID                    ( 1)
  #define MC0_CH0_CR_WDB_MBIST_0_Inject_Failure_MSK                    (0x00000100)
  #define MC0_CH0_CR_WDB_MBIST_0_Inject_Failure_MIN                    (0)
  #define MC0_CH0_CR_WDB_MBIST_0_Inject_Failure_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_WDB_MBIST_0_Inject_Failure_DEF                    (0x00000000)
  #define MC0_CH0_CR_WDB_MBIST_0_Inject_Failure_HSH                    (0x011042E8)

  #define MC0_CH0_CR_WDB_MBIST_0_RUN_BUSY_OFF                          (31)
  #define MC0_CH0_CR_WDB_MBIST_0_RUN_BUSY_WID                          ( 1)
  #define MC0_CH0_CR_WDB_MBIST_0_RUN_BUSY_MSK                          (0x80000000)
  #define MC0_CH0_CR_WDB_MBIST_0_RUN_BUSY_MIN                          (0)
  #define MC0_CH0_CR_WDB_MBIST_0_RUN_BUSY_MAX                          (1) // 0x00000001
  #define MC0_CH0_CR_WDB_MBIST_0_RUN_BUSY_DEF                          (0x00000000)
  #define MC0_CH0_CR_WDB_MBIST_0_RUN_BUSY_HSH                          (0x013E42E8)

#define MC0_CH0_CR_WDB_MBIST_1_REG                                     (0x000042EC)
//Duplicate of MC0_CH0_CR_WDB_MBIST_0_REG

#define MC0_CH0_CR_RDB_MBIST_REG                                       (0x000042F8)
//Duplicate of MC0_CH0_CR_WDB_MBIST_0_REG

#define MC0_CH0_CR_ECC_INJECT_COUNT_REG                                (0x000042FC)

  #define MC0_CH0_CR_ECC_INJECT_COUNT_Count_OFF                        ( 0)
  #define MC0_CH0_CR_ECC_INJECT_COUNT_Count_WID                        (32)
  #define MC0_CH0_CR_ECC_INJECT_COUNT_Count_MSK                        (0xFFFFFFFF)
  #define MC0_CH0_CR_ECC_INJECT_COUNT_Count_MIN                        (0)
  #define MC0_CH0_CR_ECC_INJECT_COUNT_Count_MAX                        (4294967295) // 0xFFFFFFFF
  #define MC0_CH0_CR_ECC_INJECT_COUNT_Count_DEF                        (0xFFFFFFFF)
  #define MC0_CH0_CR_ECC_INJECT_COUNT_Count_HSH                        (0x200042FC)

#define MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_REG                   (0x00004300)

  #define MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_RDDATA_COUNTER_OFF  ( 0)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_RDDATA_COUNTER_WID  (64)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_RDDATA_COUNTER_MSK  (0xFFFFFFFFFFFFFFFFULL)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_RDDATA_COUNTER_MIN  (0)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_RDDATA_COUNTER_MAX  (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_RDDATA_COUNTER_DEF  (0x00000000)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_RDDATA_COUNTER_HSH  (0x40004300)

#define MC0_CH0_CR_PWM_DDR_SUBCH1_RDDATA_COUNTER_REG                   (0x00004308)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_REG

#define MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_REG                   (0x00004310)

  #define MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_WRDATA_COUNTER_OFF  ( 0)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_WRDATA_COUNTER_WID  (64)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_WRDATA_COUNTER_MSK  (0xFFFFFFFFFFFFFFFFULL)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_WRDATA_COUNTER_MIN  (0)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_WRDATA_COUNTER_MAX  (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_WRDATA_COUNTER_DEF  (0x00000000)
  #define MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_WRDATA_COUNTER_HSH  (0x40004310)

#define MC0_CH0_CR_PWM_DDR_SUBCH1_WRDATA_COUNTER_REG                   (0x00004318)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_REG

#define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG                   (0x00004320)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte0_OFF     ( 0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte0_WID     ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte0_MSK     (0x00000007)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte0_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte0_MAX     (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte0_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte0_HSH     (0x43004320)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte1_OFF     ( 4)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte1_WID     ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte1_MSK     (0x00000070)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte1_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte1_MAX     (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte1_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte1_HSH     (0x43084320)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte2_OFF     ( 8)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte2_WID     ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte2_MSK     (0x00000700)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte2_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte2_MAX     (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte2_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte2_HSH     (0x43104320)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte3_OFF     (12)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte3_WID     ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte3_MSK     (0x00007000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte3_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte3_MAX     (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte3_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte3_HSH     (0x43184320)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte4_OFF     (16)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte4_WID     ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte4_MSK     (0x00070000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte4_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte4_MAX     (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte4_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte4_HSH     (0x43204320)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte5_OFF     (20)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte5_WID     ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte5_MSK     (0x00700000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte5_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte5_MAX     (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte5_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte5_HSH     (0x43284320)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte6_OFF     (24)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte6_WID     ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte6_MSK     (0x07000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte6_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte6_MAX     (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte6_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte6_HSH     (0x43304320)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte7_OFF     (28)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte7_WID     ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte7_MSK     (0x70000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte7_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte7_MAX     (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte7_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank0_Byte7_HSH     (0x43384320)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte0_OFF     (32)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte0_WID     ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte0_MSK     (0x0000000700000000ULL)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte0_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte0_MAX     (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte0_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte0_HSH     (0x43404320)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte1_OFF     (36)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte1_WID     ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte1_MSK     (0x0000007000000000ULL)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte1_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte1_MAX     (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte1_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte1_HSH     (0x43484320)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte2_OFF     (40)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte2_WID     ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte2_MSK     (0x0000070000000000ULL)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte2_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte2_MAX     (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte2_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte2_HSH     (0x43504320)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte3_OFF     (44)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte3_WID     ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte3_MSK     (0x0000700000000000ULL)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte3_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte3_MAX     (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte3_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte3_HSH     (0x43584320)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte4_OFF     (48)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte4_WID     ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte4_MSK     (0x0007000000000000ULL)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte4_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte4_MAX     (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte4_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte4_HSH     (0x43604320)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte5_OFF     (52)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte5_WID     ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte5_MSK     (0x0070000000000000ULL)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte5_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte5_MAX     (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte5_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte5_HSH     (0x43684320)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte6_OFF     (56)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte6_WID     ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte6_MSK     (0x0700000000000000ULL)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte6_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte6_MAX     (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte6_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte6_HSH     (0x43704320)

  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte7_OFF     (60)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte7_WID     ( 3)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte7_MSK     (0x7000000000000000ULL)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte7_MIN     (0)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte7_MAX     (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte7_DEF     (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_Rank1_Byte7_HSH     (0x43784320)

#define MC0_CH0_CR_DDR4_MR2_RTT_WR_DIMM1_VALUES_REG                    (0x00004328)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG                    (0x00004330)

  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte0_OFF            ( 0)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte0_WID            ( 7)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte0_MSK            (0x0000007F)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte0_MIN            (0)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte0_MAX            (127) // 0x0000007F
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte0_DEF            (0x00000000)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte0_HSH            (0x47004330)

  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte1_OFF            ( 8)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte1_WID            ( 7)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte1_MSK            (0x00007F00)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte1_MIN            (0)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte1_MAX            (127) // 0x0000007F
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte1_DEF            (0x00000000)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte1_HSH            (0x47104330)

  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte2_OFF            (16)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte2_WID            ( 7)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte2_MSK            (0x007F0000)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte2_MIN            (0)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte2_MAX            (127) // 0x0000007F
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte2_DEF            (0x00000000)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte2_HSH            (0x47204330)

  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte3_OFF            (24)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte3_WID            ( 7)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte3_MSK            (0x7F000000)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte3_MIN            (0)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte3_MAX            (127) // 0x0000007F
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte3_DEF            (0x00000000)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte3_HSH            (0x47304330)

  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte4_OFF            (32)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte4_WID            ( 7)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte4_MSK            (0x0000007F00000000ULL)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte4_MIN            (0)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte4_MAX            (127) // 0x0000007F
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte4_DEF            (0x00000000)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte4_HSH            (0x47404330)

  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte5_OFF            (40)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte5_WID            ( 7)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte5_MSK            (0x00007F0000000000ULL)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte5_MIN            (0)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte5_MAX            (127) // 0x0000007F
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte5_DEF            (0x00000000)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte5_HSH            (0x47504330)

  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte6_OFF            (48)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte6_WID            ( 7)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte6_MSK            (0x007F000000000000ULL)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte6_MIN            (0)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte6_MAX            (127) // 0x0000007F
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte6_DEF            (0x00000000)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte6_HSH            (0x47604330)

  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte7_OFF            (56)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte7_WID            ( 7)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte7_MSK            (0x7F00000000000000ULL)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte7_MIN            (0)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte7_MAX            (127) // 0x0000007F
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte7_DEF            (0x00000000)
  #define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_Byte7_HSH            (0x47704330)

#define MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_1_REG                    (0x00004338)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG

#define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_REG                      (0x00004344)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte0_OFF        ( 0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte0_WID        ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte0_MSK        (0x00000003)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte0_MIN        (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte0_MAX        (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte0_DEF        (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte0_HSH        (0x02004344)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte1_OFF        ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte1_WID        ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte1_MSK        (0x0000000C)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte1_MIN        (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte1_MAX        (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte1_DEF        (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte1_HSH        (0x02044344)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte2_OFF        ( 4)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte2_WID        ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte2_MSK        (0x00000030)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte2_MIN        (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte2_MAX        (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte2_DEF        (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte2_HSH        (0x02084344)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte3_OFF        ( 6)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte3_WID        ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte3_MSK        (0x000000C0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte3_MIN        (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte3_MAX        (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte3_DEF        (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte3_HSH        (0x020C4344)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte4_OFF        ( 8)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte4_WID        ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte4_MSK        (0x00000300)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte4_MIN        (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte4_MAX        (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte4_DEF        (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte4_HSH        (0x02104344)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte5_OFF        (10)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte5_WID        ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte5_MSK        (0x00000C00)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte5_MIN        (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte5_MAX        (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte5_DEF        (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte5_HSH        (0x02144344)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte6_OFF        (12)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte6_WID        ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte6_MSK        (0x00003000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte6_MIN        (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte6_MAX        (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte6_DEF        (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte6_HSH        (0x02184344)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte7_OFF        (14)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte7_WID        ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte7_MSK        (0x0000C000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte7_MIN        (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte7_MAX        (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte7_DEF        (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank0_Byte7_HSH        (0x021C4344)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte0_OFF        (16)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte0_WID        ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte0_MSK        (0x00030000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte0_MIN        (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte0_MAX        (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte0_DEF        (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte0_HSH        (0x02204344)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte1_OFF        (18)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte1_WID        ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte1_MSK        (0x000C0000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte1_MIN        (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte1_MAX        (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte1_DEF        (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte1_HSH        (0x02244344)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte2_OFF        (20)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte2_WID        ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte2_MSK        (0x00300000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte2_MIN        (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte2_MAX        (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte2_DEF        (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte2_HSH        (0x02284344)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte3_OFF        (22)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte3_WID        ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte3_MSK        (0x00C00000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte3_MIN        (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte3_MAX        (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte3_DEF        (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte3_HSH        (0x022C4344)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte4_OFF        (24)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte4_WID        ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte4_MSK        (0x03000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte4_MIN        (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte4_MAX        (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte4_DEF        (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte4_HSH        (0x02304344)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte5_OFF        (26)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte5_WID        ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte5_MSK        (0x0C000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte5_MIN        (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte5_MAX        (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte5_DEF        (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte5_HSH        (0x02344344)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte6_OFF        (28)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte6_WID        ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte6_MSK        (0x30000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte6_MIN        (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte6_MAX        (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte6_DEF        (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte6_HSH        (0x02384344)

  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte7_OFF        (30)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte7_WID        ( 2)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte7_MSK        (0xC0000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte7_MIN        (0)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte7_MAX        (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte7_DEF        (0x00000000)
  #define MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_Rank1_Byte7_HSH        (0x023C4344)

#define MC0_CH0_CR_DDR4_MR5_RTT_PARK_VALUES_REG                        (0x00004348)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC0_CH0_CR_DDR4_MR5_RTT_PARK_DIMM1_VALUES_REG                  (0x00004350)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC0_CH0_CR_DDR4_MR1_RTT_NOM_VALUES_REG                         (0x00004358)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG                     (0x00004360)

  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_PDDS_OFF              ( 0)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_PDDS_WID              ( 3)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_PDDS_MSK              (0x00000007)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_PDDS_MIN              (0)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_PDDS_MAX              (7) // 0x00000007
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_PDDS_DEF              (0x00000000)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_PDDS_HSH              (0x43004360)

  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_ODT_OFF            ( 3)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_ODT_WID            ( 3)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_ODT_MSK            (0x00000038)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_ODT_MIN            (0)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_ODT_MAX            (7) // 0x00000007
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_ODT_DEF            (0x00000000)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_ODT_HSH            (0x43064360)

  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_ODT_OFF            ( 6)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_ODT_WID            ( 3)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_ODT_MSK            (0x000001C0)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_ODT_MIN            (0)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_ODT_MAX            (7) // 0x00000007
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_ODT_DEF            (0x00000000)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_ODT_HSH            (0x430C4360)

  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_OFF           ( 9)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_WID           ( 7)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_MSK           (0x0000FE00)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_MIN           (0)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_MAX           (127) // 0x0000007F
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_DEF           (0x00000000)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_HSH           (0x47124360)

  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_OFF           (16)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_WID           ( 7)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_MSK           (0x007F0000)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_MIN           (0)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_MAX           (127) // 0x0000007F
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_DEF           (0x00000000)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_HSH           (0x47204360)

  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CODT_OFF              (23)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CODT_WID              ( 6)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CODT_MSK              (0x1F800000)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CODT_MIN              (0)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CODT_MAX              (63) // 0x0000003F
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CODT_DEF              (0x00000000)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CODT_HSH              (0x462E4360)

  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_High_OFF      (29)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_High_WID      ( 7)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_High_MSK      (0x0000000FE0000000ULL)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_High_MIN      (0)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_High_MAX      (127) // 0x0000007F
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_High_DEF      (0x00000000)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_CA_VREF_High_HSH      (0x473A4360)

  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_High_OFF      (36)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_High_WID      ( 7)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_High_MSK      (0x000007F000000000ULL)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_High_MIN      (0)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_High_MAX      (127) // 0x0000007F
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_High_DEF      (0x00000000)
  #define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_DQ_VREF_High_HSH      (0x47484360)

#define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_1_REG                     (0x00004368)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_2_REG                     (0x00004370)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_3_REG                     (0x00004378)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_4_REG                     (0x00004380)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_5_REG                     (0x00004388)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_6_REG                     (0x00004390)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_7_REG                     (0x00004398)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_REG                            (0x000043A0)

  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR0_OFF                      ( 0)
  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR0_WID                      (14)
  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR0_MSK                      (0x00003FFF)
  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR0_MIN                      (0)
  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR0_MAX                      (16383) // 0x00003FFF
  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR0_DEF                      (0x00000000)
  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR0_HSH                      (0x0E0043A0)

  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR1_OFF                      (16)
  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR1_WID                      (14)
  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR1_MSK                      (0x3FFF0000)
  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR1_MIN                      (0)
  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR1_MAX                      (16383) // 0x00003FFF
  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR1_DEF                      (0x00000000)
  #define MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_MR1_HSH                      (0x0E2043A0)

#define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_REG                            (0x000043A4)

  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR2_OFF                      ( 0)
  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR2_WID                      (14)
  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR2_MSK                      (0x00003FFF)
  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR2_MIN                      (0)
  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR2_MAX                      (16383) // 0x00003FFF
  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR2_DEF                      (0x00000000)
  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR2_HSH                      (0x0E0043A4)

  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR3_OFF                      (16)
  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR3_WID                      (14)
  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR3_MSK                      (0x3FFF0000)
  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR3_MIN                      (0)
  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR3_MAX                      (16383) // 0x00003FFF
  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR3_DEF                      (0x00000000)
  #define MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_MR3_HSH                      (0x0E2043A4)

#define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_REG                            (0x000043A8)

  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR4_OFF                      ( 0)
  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR4_WID                      (14)
  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR4_MSK                      (0x00003FFF)
  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR4_MIN                      (0)
  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR4_MAX                      (16383) // 0x00003FFF
  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR4_DEF                      (0x00000000)
  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR4_HSH                      (0x0E0043A8)

  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR5_OFF                      (16)
  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR5_WID                      (14)
  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR5_MSK                      (0x3FFF0000)
  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR5_MIN                      (0)
  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR5_MAX                      (16383) // 0x00003FFF
  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR5_DEF                      (0x00000000)
  #define MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_MR5_HSH                      (0x0E2043A8)

#define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_REG                            (0x000043AC)

  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR6_OFF                      ( 0)
  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR6_WID                      (14)
  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR6_MSK                      (0x00003FFF)
  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR6_MIN                      (0)
  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR6_MAX                      (16383) // 0x00003FFF
  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR6_DEF                      (0x00000000)
  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR6_HSH                      (0x0E0043AC)

  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR7_OFF                      (16)
  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR7_WID                      (14)
  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR7_MSK                      (0x3FFF0000)
  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR7_MIN                      (0)
  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR7_MAX                      (16383) // 0x00003FFF
  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR7_DEF                      (0x00000000)
  #define MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_MR7_HSH                      (0x0E2043AC)

#define MC0_CH0_CR_DDR4_MR2_RTT_WR_VALUES_REG                          (0x000043B0)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC0_CH0_CR_DDR4_MR6_VREF_VALUES_0_REG                          (0x000043B8)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG

#define MC0_CH0_CR_DDR4_MR6_VREF_VALUES_1_REG                          (0x000043C0)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG

#define MC0_CH0_CR_LPDDR_MR_CONTENT_REG                                (0x000043C8)

  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR1_OFF                          ( 0)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR1_WID                          ( 8)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR1_MSK                          (0x000000FF)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR1_MIN                          (0)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR1_MAX                          (255) // 0x000000FF
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR1_DEF                          (0x00000000)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR1_HSH                          (0x480043C8)

  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR2_OFF                          ( 8)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR2_WID                          ( 8)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR2_MSK                          (0x0000FF00)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR2_MIN                          (0)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR2_MAX                          (255) // 0x000000FF
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR2_DEF                          (0x00000000)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR2_HSH                          (0x481043C8)

  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR3_OFF                          (16)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR3_WID                          ( 8)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR3_MSK                          (0x00FF0000)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR3_MIN                          (0)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR3_MAX                          (255) // 0x000000FF
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR3_DEF                          (0x00000000)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR3_HSH                          (0x482043C8)

  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR11_OFF                         (24)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR11_WID                         ( 8)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR11_MSK                         (0xFF000000)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR11_MIN                         (0)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR11_MAX                         (255) // 0x000000FF
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR11_DEF                         (0x00000000)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR11_HSH                         (0x483043C8)

  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR12_OFF                         (32)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR12_WID                         ( 8)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR12_MSK                         (0x000000FF00000000ULL)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR12_MIN                         (0)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR12_MAX                         (255) // 0x000000FF
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR12_DEF                         (0x00000000)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR12_HSH                         (0x484043C8)

  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR13_OFF                         (40)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR13_WID                         ( 8)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR13_MSK                         (0x0000FF0000000000ULL)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR13_MIN                         (0)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR13_MAX                         (255) // 0x000000FF
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR13_DEF                         (0x00000000)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR13_HSH                         (0x485043C8)

  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR22_OFF                         (48)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR22_WID                         ( 8)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR22_MSK                         (0x00FF000000000000ULL)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR22_MIN                         (0)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR22_MAX                         (255) // 0x000000FF
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR22_DEF                         (0x00000000)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR22_HSH                         (0x486043C8)

  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR23_OFF                         (56)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR23_WID                         ( 8)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR23_MSK                         (0xFF00000000000000ULL)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR23_MIN                         (0)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR23_MAX                         (255) // 0x000000FF
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR23_DEF                         (0x0000003F)
  #define MC0_CH0_CR_LPDDR_MR_CONTENT_MR23_HSH                         (0x487043C8)

#define MC0_CH0_CR_MRS_FSM_CONTROL_REG                                 (0x000043D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR_OFF               ( 0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR_WID               ( 8)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR_MSK               (0x000000FF)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR_MIN               (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR_MAX               (255) // 0x000000FF
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR_DEF               (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR_HSH               (0x480043D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_ODIC_Per_Device_OFF ( 8)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_ODIC_Per_Device_WID ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_ODIC_Per_Device_MSK (0x00000100)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_ODIC_Per_Device_MIN (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_ODIC_Per_Device_MAX (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_ODIC_Per_Device_DEF (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_ODIC_Per_Device_HSH (0x411043D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR2_Per_Device_OFF   ( 9)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR2_Per_Device_WID   ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR2_Per_Device_MSK   (0x00000200)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR2_Per_Device_MIN   (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR2_Per_Device_MAX   (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR2_Per_Device_DEF   (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR2_Per_Device_HSH   (0x411243D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR6_Per_Device_OFF   (10)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR6_Per_Device_WID   ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR6_Per_Device_MSK   (0x00000400)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR6_Per_Device_MIN   (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR6_Per_Device_MAX   (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR6_Per_Device_DEF   (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR6_Per_Device_HSH   (0x411443D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_PDA_VREF_Initial_OFF         (11)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_PDA_VREF_Initial_WID         ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_PDA_VREF_Initial_MSK         (0x00000800)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_PDA_VREF_Initial_MIN         (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_PDA_VREF_Initial_MAX         (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_PDA_VREF_Initial_DEF         (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_PDA_VREF_Initial_HSH         (0x411643D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Short_VREF_Exit_OFF          (12)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Short_VREF_Exit_WID          ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Short_VREF_Exit_MSK          (0x00001000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Short_VREF_Exit_MIN          (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Short_VREF_Exit_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Short_VREF_Exit_DEF          (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Short_VREF_Exit_HSH          (0x411843D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR_Restore_MR_OFF              (13)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR_Restore_MR_WID              ( 9)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR_Restore_MR_MSK              (0x003FE000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR_Restore_MR_MIN              (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR_Restore_MR_MAX              (511) // 0x000001FF
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR_Restore_MR_DEF              (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR_Restore_MR_HSH              (0x491A43D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_ZQCL_OFF                       (22)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_ZQCL_WID                       ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_ZQCL_MSK                       (0x00400000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_ZQCL_MIN                       (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_ZQCL_MAX                       (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_ZQCL_DEF                       (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_ZQCL_HSH                       (0x412C43D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_zero_rank1_MR11_OFF               (23)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_zero_rank1_MR11_WID               ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_zero_rank1_MR11_MSK               (0x00800000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_zero_rank1_MR11_MIN               (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_zero_rank1_MR11_MAX               (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_zero_rank1_MR11_DEF               (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_zero_rank1_MR11_HSH               (0x412E43D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_reset_flow_OFF                    (24)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_reset_flow_WID                    ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_reset_flow_MSK                    (0x01000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_reset_flow_MIN                    (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_reset_flow_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_reset_flow_DEF                    (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_reset_flow_HSH                    (0x413043D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_vref_time_per_byte_OFF            (25)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_vref_time_per_byte_WID            ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_vref_time_per_byte_MSK            (0x02000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_vref_time_per_byte_MIN            (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_vref_time_per_byte_MAX            (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_vref_time_per_byte_DEF            (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_vref_time_per_byte_HSH            (0x413243D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_pda_for_1R1R_OFF               (26)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_pda_for_1R1R_WID               ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_pda_for_1R1R_MSK               (0x04000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_pda_for_1R1R_MIN               (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_pda_for_1R1R_MAX               (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_pda_for_1R1R_DEF               (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_pda_for_1R1R_HSH               (0x413443D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_add_initial_vref_OFF              (27)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_add_initial_vref_WID              ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_add_initial_vref_MSK              (0x08000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_add_initial_vref_MIN              (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_add_initial_vref_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_add_initial_vref_DEF              (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_add_initial_vref_HSH              (0x413643D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_switch_FSP_OFF             (28)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_switch_FSP_WID             ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_switch_FSP_MSK             (0x10000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_switch_FSP_MIN             (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_switch_FSP_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_switch_FSP_DEF             (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_switch_FSP_HSH             (0x413843D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_dq_osc_start_OFF               (29)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_dq_osc_start_WID               ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_dq_osc_start_MSK               (0x20000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_dq_osc_start_MIN               (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_dq_osc_start_MAX               (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_dq_osc_start_DEF               (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_dq_osc_start_HSH               (0x413A43D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_GV_auto_enable_OFF                (30)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GV_auto_enable_WID                ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GV_auto_enable_MSK                (0x40000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GV_auto_enable_MIN                (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GV_auto_enable_MAX                (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GV_auto_enable_DEF                (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GV_auto_enable_HSH                (0x413C43D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_split_transition_OFF       (31)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_split_transition_WID       ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_split_transition_MSK       (0x80000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_split_transition_MIN       (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_split_transition_MAX       (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_split_transition_DEF       (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_split_transition_HSH       (0x413E43D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_tVREFDQ_OFF                       (32)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_tVREFDQ_WID                       (10)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_tVREFDQ_MSK                       (0x000003FF00000000ULL)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_tVREFDQ_MIN                       (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_tVREFDQ_MAX                       (1023) // 0x000003FF
  #define MC0_CH0_CR_MRS_FSM_CONTROL_tVREFDQ_DEF                       (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_tVREFDQ_HSH                       (0x4A4043D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_cbit_count_each_rank_OFF          (42)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_cbit_count_each_rank_WID          ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_cbit_count_each_rank_MSK          (0x0000040000000000ULL)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_cbit_count_each_rank_MIN          (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_cbit_count_each_rank_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_cbit_count_each_rank_DEF          (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_cbit_count_each_rank_HSH          (0x415443D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_PDA_for_ECC_OFF                (43)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_PDA_for_ECC_WID                ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_PDA_for_ECC_MSK                (0x0000080000000000ULL)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_PDA_for_ECC_MIN                (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_PDA_for_ECC_MAX                (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_PDA_for_ECC_DEF                (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_do_PDA_for_ECC_HSH                (0x415643D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR5_Per_Device_OFF   (44)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR5_Per_Device_WID   ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR5_Per_Device_MSK   (0x0000100000000000ULL)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR5_Per_Device_MIN   (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR5_Per_Device_MAX   (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR5_Per_Device_DEF   (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR5_Per_Device_HSH   (0x415843D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_TwoDPC_support_OFF                (45)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_TwoDPC_support_WID                ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_TwoDPC_support_MSK                (0x0000200000000000ULL)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_TwoDPC_support_MIN                (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_TwoDPC_support_MAX                (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_TwoDPC_support_DEF                (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_TwoDPC_support_HSH                (0x415A43D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_RTTNOM_Per_Device_OFF (46)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_RTTNOM_Per_Device_WID ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_RTTNOM_Per_Device_MSK (0x0000400000000000ULL)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_RTTNOM_Per_Device_MIN (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_RTTNOM_Per_Device_MAX (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_RTTNOM_Per_Device_DEF (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_DDR4_Restore_MR1_RTTNOM_Per_Device_HSH (0x415C43D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_Fast_PDA_OFF                      (47)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_Fast_PDA_WID                      ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_Fast_PDA_MSK                      (0x0000800000000000ULL)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_Fast_PDA_MIN                      (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_Fast_PDA_MAX                      (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_Fast_PDA_DEF                      (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_Fast_PDA_HSH                      (0x415E43D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_always_count_tFC_OFF              (48)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_always_count_tFC_WID              ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_always_count_tFC_MSK              (0x0001000000000000ULL)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_always_count_tFC_MIN              (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_always_count_tFC_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_always_count_tFC_DEF              (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_always_count_tFC_HSH              (0x416043D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_PDA_wr_delay_OFF                  (49)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_PDA_wr_delay_WID                  ( 6)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_PDA_wr_delay_MSK                  (0x007E000000000000ULL)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_PDA_wr_delay_MIN                  (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_PDA_wr_delay_MAX                  (63) // 0x0000003F
  #define MC0_CH0_CR_MRS_FSM_CONTROL_PDA_wr_delay_DEF                  (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_PDA_wr_delay_HSH                  (0x466243D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_per_byte_vref_OFF          (55)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_per_byte_vref_WID          ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_per_byte_vref_MSK          (0x0080000000000000ULL)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_per_byte_vref_MIN          (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_per_byte_vref_MAX          (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_per_byte_vref_DEF          (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_LPDDR4_per_byte_vref_HSH          (0x416E43D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_Clear_VRCG_OFF                    (56)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_Clear_VRCG_WID                    ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_Clear_VRCG_MSK                    (0x0100000000000000ULL)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_Clear_VRCG_MIN                    (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_Clear_VRCG_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_Clear_VRCG_DEF                    (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_Clear_VRCG_HSH                    (0x417043D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Enable_OFF        (57)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Enable_WID        ( 1)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Enable_MSK        (0x0200000000000000ULL)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Enable_MIN        (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Enable_MAX        (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Enable_DEF        (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Enable_HSH        (0x417243D0)

  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Breakpoint_Address_OFF (58)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Breakpoint_Address_WID ( 5)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Breakpoint_Address_MSK (0x7C00000000000000ULL)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Breakpoint_Address_MIN (0)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Breakpoint_Address_MAX (31) // 0x0000001F
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Breakpoint_Address_DEF (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_CONTROL_GENERIC_MRS_FSM_Breakpoint_Address_HSH (0x457443D0)

#define MC0_CH0_CR_MRS_FSM_RUN_REG                                     (0x000043D8)

  #define MC0_CH0_CR_MRS_FSM_RUN_Run_OFF                               ( 0)
  #define MC0_CH0_CR_MRS_FSM_RUN_Run_WID                               ( 1)
  #define MC0_CH0_CR_MRS_FSM_RUN_Run_MSK                               (0x00000001)
  #define MC0_CH0_CR_MRS_FSM_RUN_Run_MIN                               (0)
  #define MC0_CH0_CR_MRS_FSM_RUN_Run_MAX                               (1) // 0x00000001
  #define MC0_CH0_CR_MRS_FSM_RUN_Run_DEF                               (0x00000000)
  #define MC0_CH0_CR_MRS_FSM_RUN_Run_HSH                               (0x010043D8)

#define MC0_CH0_CR_DDR4_MR1_ODIC_VALUES_REG                            (0x000043DC)
//Duplicate of MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_REG

#define MC0_CH0_CR_PL_AGENT_CFG_DTF_REG                                (0x000043E0)

  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_data_trace_mode_OFF              ( 0)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_data_trace_mode_WID              ( 2)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_data_trace_mode_MSK              (0x00000003)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_data_trace_mode_MIN              (0)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_data_trace_mode_MAX              (3) // 0x00000003
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_data_trace_mode_DEF              (0x00000000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_data_trace_mode_HSH              (0x020043E0)

  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_UI_to_trace_OFF                  ( 2)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_UI_to_trace_WID                  ( 3)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_UI_to_trace_MSK                  (0x0000001C)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_UI_to_trace_MIN                  (0)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_UI_to_trace_MAX                  (7) // 0x00000007
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_UI_to_trace_DEF                  (0x00000000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_UI_to_trace_HSH                  (0x030443E0)

  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_byte_to_trace_OFF                ( 5)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_byte_to_trace_WID                ( 3)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_byte_to_trace_MSK                (0x000000E0)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_byte_to_trace_MIN                (0)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_byte_to_trace_MAX                (7) // 0x00000007
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_byte_to_trace_DEF                (0x00000000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_byte_to_trace_HSH                (0x030A43E0)

  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_EN_OFF                       ( 8)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_EN_WID                       ( 1)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_EN_MSK                       (0x00000100)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_EN_MIN                       (0)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_EN_MAX                       (1) // 0x00000001
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_EN_DEF                       (0x00000000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_EN_HSH                       (0x011043E0)

  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_BYTE_replace_OFF             ( 9)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_BYTE_replace_WID             ( 3)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_BYTE_replace_MSK             (0x00000E00)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_BYTE_replace_MIN             (0)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_BYTE_replace_MAX             (7) // 0x00000007
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_BYTE_replace_DEF             (0x00000000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_ECC_BYTE_replace_HSH             (0x031243E0)

  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_read_data_OFF              (12)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_read_data_WID              ( 1)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_read_data_MSK              (0x00001000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_read_data_MIN              (0)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_read_data_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_read_data_DEF              (0x00000000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_read_data_HSH              (0x011843E0)

  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_write_data_OFF             (13)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_write_data_WID             ( 1)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_write_data_MSK             (0x00002000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_write_data_MIN             (0)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_write_data_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_write_data_DEF             (0x00000001)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_trace_write_data_HSH             (0x011A43E0)

  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_DDRPL_Activate_OFF               (14)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_DDRPL_Activate_WID               ( 1)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_DDRPL_Activate_MSK               (0x00004000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_DDRPL_Activate_MIN               (0)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_DDRPL_Activate_MAX               (1) // 0x00000001
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_DDRPL_Activate_DEF               (0x00000000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_DDRPL_Activate_HSH               (0x011C43E0)

  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_SCHTrace_OFF                     (15)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_SCHTrace_WID                     ( 1)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_SCHTrace_MSK                     (0x00008000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_SCHTrace_MIN                     (0)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_SCHTrace_MAX                     (1) // 0x00000001
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_SCHTrace_DEF                     (0x00000000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_SCHTrace_HSH                     (0x011E43E0)

  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_dis_early_ind_override_OFF       (16)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_dis_early_ind_override_WID       ( 1)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_dis_early_ind_override_MSK       (0x00010000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_dis_early_ind_override_MIN       (0)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_dis_early_ind_override_MAX       (1) // 0x00000001
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_dis_early_ind_override_DEF       (0x00000000)
  #define MC0_CH0_CR_PL_AGENT_CFG_DTF_dis_early_ind_override_HSH       (0x012043E0)

#define MC0_CH0_CR_MCMNTS_GLOBAL_DRIVER_GATE_CFG_REG                   (0x000043E4)
//Duplicate of MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_REG

#define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_REG                          (0x000043E8)

  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank0_OFF             ( 0)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank0_WID             ( 2)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank0_MSK             (0x00000003)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank0_MIN             (0)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank0_MAX             (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank0_DEF             (0x00000000)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank0_HSH             (0x420043E8)

  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank1_OFF             ( 2)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank1_WID             ( 2)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank1_MSK             (0x0000000C)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank1_MIN             (0)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank1_MAX             (3) // 0x00000003
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank1_DEF             (0x00000000)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_ODIC_Rank1_HSH             (0x420443E8)

  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank0_OFF           ( 4)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank0_WID           ( 3)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank0_MSK           (0x00000070)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank0_MIN           (0)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank0_MAX           (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank0_DEF           (0x00000000)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank0_HSH           (0x430843E8)

  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank1_OFF           ( 7)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank1_WID           ( 3)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank1_MSK           (0x00000380)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank1_MIN           (0)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank1_MAX           (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank1_DEF           (0x00000000)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_WR_Rank1_HSH           (0x430E43E8)

  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank0_OFF             (10)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank0_WID             ( 7)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank0_MSK             (0x0001FC00)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank0_MIN             (0)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank0_MAX             (127) // 0x0000007F
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank0_DEF             (0x00000000)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank0_HSH             (0x471443E8)

  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank1_OFF             (17)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank1_WID             ( 7)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank1_MSK             (0x00FE0000)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank1_MIN             (0)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank1_MAX             (127) // 0x0000007F
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank1_DEF             (0x00000000)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_VREF_Rank1_HSH             (0x472243E8)

  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank0_OFF          (24)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank0_WID          ( 3)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank0_MSK          (0x07000000)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank0_MIN          (0)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank0_MAX          (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank0_DEF          (0x00000000)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank0_HSH          (0x433043E8)

  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank1_OFF          (27)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank1_WID          ( 3)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank1_MSK          (0x38000000)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank1_MIN          (0)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank1_MAX          (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank1_DEF          (0x00000000)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_NOM_Rank1_HSH          (0x433643E8)

  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank0_OFF         (32)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank0_WID         ( 3)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank0_MSK         (0x0000000700000000ULL)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank0_MIN         (0)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank0_MAX         (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank0_DEF         (0x00000000)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank0_HSH         (0x434043E8)

  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank1_OFF         (35)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank1_WID         ( 3)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank1_MSK         (0x0000003800000000ULL)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank1_MIN         (0)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank1_MAX         (7) // 0x00000007
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank1_DEF         (0x00000000)
  #define MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_RTT_PARK_Rank1_HSH         (0x434643E8)

#define MC0_CH0_CR_DDR4_ECC_DEVICE_DIMM1_VALUES_REG                    (0x000043F0)
//Duplicate of MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_REG

#define MC0_CH0_CR_MCMNTS_SPARE_REG                                    (0x000043FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_OFF                         ( 0)
  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_WID                         ( 8)
  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_MSK                         (0x000000FF)
  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_MIN                         (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_MAX                         (255) // 0x000000FF
  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_DEF                         (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_HSH                         (0x080043FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX2Ref_OFF                       ( 8)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX2Ref_WID                       ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX2Ref_MSK                       (0x00000100)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX2Ref_MIN                       (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX2Ref_MAX                       (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX2Ref_DEF                       (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX2Ref_HSH                       (0x011043FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX4Ref_OFF                       ( 9)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX4Ref_WID                       ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX4Ref_MSK                       (0x00000200)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX4Ref_MIN                       (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX4Ref_MAX                       (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX4Ref_DEF                       (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX4Ref_HSH                       (0x011243FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_DisLowRefRate_OFF                    (10)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisLowRefRate_WID                    ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisLowRefRate_MSK                    (0x00000400)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisLowRefRate_MIN                    (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisLowRefRate_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_DisLowRefRate_DEF                    (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisLowRefRate_HSH                    (0x011443FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_disRegardZQonSRtime_OFF              (11)
  #define MC0_CH0_CR_MCMNTS_SPARE_disRegardZQonSRtime_WID              ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_disRegardZQonSRtime_MSK              (0x00000800)
  #define MC0_CH0_CR_MCMNTS_SPARE_disRegardZQonSRtime_MIN              (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_disRegardZQonSRtime_MAX              (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_disRegardZQonSRtime_DEF              (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_disRegardZQonSRtime_HSH              (0x011643FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_Decoder_EBH_OFF                      (12)
  #define MC0_CH0_CR_MCMNTS_SPARE_Decoder_EBH_WID                      ( 2)
  #define MC0_CH0_CR_MCMNTS_SPARE_Decoder_EBH_MSK                      (0x00003000)
  #define MC0_CH0_CR_MCMNTS_SPARE_Decoder_EBH_MIN                      (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_Decoder_EBH_MAX                      (3) // 0x00000003
  #define MC0_CH0_CR_MCMNTS_SPARE_Decoder_EBH_DEF                      (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_Decoder_EBH_HSH                      (0x021843FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_DDR4_alert_OFF                       (14)
  #define MC0_CH0_CR_MCMNTS_SPARE_DDR4_alert_WID                       ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_DDR4_alert_MSK                       (0x00004000)
  #define MC0_CH0_CR_MCMNTS_SPARE_DDR4_alert_MIN                       (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_DDR4_alert_MAX                       (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_DDR4_alert_DEF                       (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_DDR4_alert_HSH                       (0x011C43FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_DisSREXcnt_OFF                       (15)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisSREXcnt_WID                       ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisSREXcnt_MSK                       (0x00008000)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisSREXcnt_MIN                       (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisSREXcnt_MAX                       (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_DisSREXcnt_DEF                       (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisSREXcnt_HSH                       (0x011E43FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX8Ref_OFF                       (16)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX8Ref_WID                       ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX8Ref_MSK                       (0x00010000)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX8Ref_MIN                       (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX8Ref_MAX                       (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX8Ref_DEF                       (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_ForceX8Ref_HSH                       (0x012043FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_Background_ZQ_Mode_OFF               (17)
  #define MC0_CH0_CR_MCMNTS_SPARE_Background_ZQ_Mode_WID               ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_Background_ZQ_Mode_MSK               (0x00020000)
  #define MC0_CH0_CR_MCMNTS_SPARE_Background_ZQ_Mode_MIN               (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_Background_ZQ_Mode_MAX               (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_Background_ZQ_Mode_DEF               (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_Background_ZQ_Mode_HSH               (0x012243FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_global_driver_wake_without_ref_OFF   (18)
  #define MC0_CH0_CR_MCMNTS_SPARE_global_driver_wake_without_ref_WID   ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_global_driver_wake_without_ref_MSK   (0x00040000)
  #define MC0_CH0_CR_MCMNTS_SPARE_global_driver_wake_without_ref_MIN   (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_global_driver_wake_without_ref_MAX   (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_global_driver_wake_without_ref_DEF   (0x00000001)
  #define MC0_CH0_CR_MCMNTS_SPARE_global_driver_wake_without_ref_HSH   (0x012443FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_DisMaintenanceRoundRobinArb_OFF      (19)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisMaintenanceRoundRobinArb_WID      ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisMaintenanceRoundRobinArb_MSK      (0x00080000)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisMaintenanceRoundRobinArb_MIN      (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisMaintenanceRoundRobinArb_MAX      (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_DisMaintenanceRoundRobinArb_DEF      (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisMaintenanceRoundRobinArb_HSH      (0x012643FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass2_OFF                       (20)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass2_WID                       ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass2_MSK                       (0x00100000)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass2_MIN                       (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass2_MAX                       (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass2_DEF                       (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass2_HSH                       (0x012843FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass1_OFF                       (21)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass1_WID                       ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass1_MSK                       (0x00200000)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass1_MIN                       (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass1_MAX                       (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass1_DEF                       (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass1_HSH                       (0x012A43FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass0_OFF                       (22)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass0_WID                       ( 1)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass0_MSK                       (0x00400000)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass0_MIN                       (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass0_MAX                       (1) // 0x00000001
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass0_DEF                       (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_DisBypass0_HSH                       (0x012C43FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_Run_Delay_OFF                        (23)
  #define MC0_CH0_CR_MCMNTS_SPARE_Run_Delay_WID                        ( 5)
  #define MC0_CH0_CR_MCMNTS_SPARE_Run_Delay_MSK                        (0x0F800000)
  #define MC0_CH0_CR_MCMNTS_SPARE_Run_Delay_MIN                        (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_Run_Delay_MAX                        (31) // 0x0000001F
  #define MC0_CH0_CR_MCMNTS_SPARE_Run_Delay_DEF                        (0x00000010)
  #define MC0_CH0_CR_MCMNTS_SPARE_Run_Delay_HSH                        (0x052E43FC)

  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_V_OFF                       (28)
  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_V_WID                       ( 4)
  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_V_MSK                       (0xF0000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_V_MIN                       (0)
  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_V_MAX                       (15) // 0x0000000F
  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_V_DEF                       (0x00000000)
  #define MC0_CH0_CR_MCMNTS_SPARE_Spare_RW_V_HSH                       (0x043843FC)

#define MC0_CH1_CR_TC_PRE_REG                                          (0x00004400)
//Duplicate of MC0_CH0_CR_TC_PRE_REG

#define MC0_CH1_CR_TC_ACT_REG                                          (0x00004408)
//Duplicate of MC0_CH0_CR_TC_ACT_REG

#define MC0_CH1_CR_TC_RDRD_REG                                         (0x0000440C)
//Duplicate of MC0_CH0_CR_TC_RDRD_REG

#define MC0_CH1_CR_TC_RDWR_REG                                         (0x00004410)
//Duplicate of MC0_CH0_CR_TC_RDWR_REG

#define MC0_CH1_CR_TC_WRRD_REG                                         (0x00004414)
//Duplicate of MC0_CH0_CR_TC_WRRD_REG

#define MC0_CH1_CR_TC_WRWR_REG                                         (0x00004418)
//Duplicate of MC0_CH0_CR_TC_WRWR_REG

#define MC0_CH1_CR_SC_ROUNDTRIP_LATENCY_REG                            (0x00004420)
//Duplicate of MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_REG

#define MC0_CH1_CR_SCHED_CBIT_REG                                      (0x00004428)
//Duplicate of MC0_CH0_CR_SCHED_CBIT_REG

#define MC0_CH1_CR_SCHED_SECOND_CBIT_REG                               (0x0000442C)
//Duplicate of MC0_CH0_CR_SCHED_SECOND_CBIT_REG

#define MC0_CH1_CR_DFT_MISC_REG                                        (0x00004430)
//Duplicate of MC0_CH0_CR_DFT_MISC_REG

#define MC0_CH1_CR_SC_PCIT_REG                                         (0x00004434)
//Duplicate of MC0_CH0_CR_SC_PCIT_REG

#define MC0_CH1_CR_ECC_DFT_REG                                         (0x00004438)
//Duplicate of MC0_CH0_CR_ECC_DFT_REG

#define MC0_CH1_CR_PM_PDWN_CONFIG_REG                                  (0x00004440)
//Duplicate of MC0_CH0_CR_PM_PDWN_CONFIG_REG

#define MC0_CH1_CR_WMM_READ_CONFIG_REG                                 (0x00004444)
//Duplicate of MC0_CH0_CR_WMM_READ_CONFIG_REG

#define MC0_CH1_CR_ECCERRLOG0_REG                                      (0x00004448)
//Duplicate of MC0_CH0_CR_ECCERRLOG0_REG

#define MC0_CH1_CR_ECCERRLOG1_REG                                      (0x0000444C)
//Duplicate of MC0_CH0_CR_ECCERRLOG1_REG

#define MC0_CH1_CR_TC_PWRDN_REG                                        (0x00004450)
//Duplicate of MC0_CH0_CR_TC_PWRDN_REG

#define MC0_CH1_CR_QUEUE_ENTRY_DISABLE_RPQ_REG                         (0x00004458)
//Duplicate of MC0_CH0_CR_QUEUE_ENTRY_DISABLE_RPQ_REG

#define MC0_CH1_CR_QUEUE_ENTRY_DISABLE_IPQ_REG                         (0x0000445C)
//Duplicate of MC0_CH0_CR_QUEUE_ENTRY_DISABLE_IPQ_REG

#define MC0_CH1_CR_QUEUE_ENTRY_DISABLE_WPQ_REG                         (0x00004460)
//Duplicate of MC0_CH0_CR_QUEUE_ENTRY_DISABLE_WPQ_REG

#define MC0_CH1_CR_SC_WDBWM_REG                                        (0x00004468)
//Duplicate of MC0_CH0_CR_SC_WDBWM_REG

#define MC0_CH1_CR_TC_ODT_REG                                          (0x00004470)
//Duplicate of MC0_CH0_CR_TC_ODT_REG

#define MC0_CH1_CR_MCSCHEDS_SPARE_REG                                  (0x00004478)
//Duplicate of MC0_CH0_CR_MCSCHEDS_SPARE_REG

#define MC0_CH1_CR_SC_ODT_MATRIX_REG                                   (0x00004480)
//Duplicate of MC0_CH0_CR_SC_ODT_MATRIX_REG

#define MC0_CH1_CR_DFT_BLOCK_REG                                       (0x00004484)
//Duplicate of MC0_CH0_CR_DFT_BLOCK_REG

#define MC0_CH1_CR_SC_GS_CFG_REG                                       (0x00004488)
//Duplicate of MC0_CH0_CR_SC_GS_CFG_REG

#define MC0_CH1_CR_SC_PH_THROTTLING_0_REG                              (0x00004490)
//Duplicate of MC0_CH0_CR_SC_PH_THROTTLING_0_REG

#define MC0_CH1_CR_SC_PH_THROTTLING_1_REG                              (0x00004494)
//Duplicate of MC0_CH0_CR_SC_PH_THROTTLING_1_REG

#define MC0_CH1_CR_SC_PH_THROTTLING_2_REG                              (0x00004498)
//Duplicate of MC0_CH0_CR_SC_PH_THROTTLING_2_REG

#define MC0_CH1_CR_SC_PH_THROTTLING_3_REG                              (0x0000449C)
//Duplicate of MC0_CH0_CR_SC_PH_THROTTLING_3_REG

#define MC0_CH1_CR_SC_WPQ_THRESHOLD_REG                                (0x000044A0)
//Duplicate of MC0_CH0_CR_SC_WPQ_THRESHOLD_REG

#define MC0_CH1_CR_SC_PR_CNT_CONFIG_REG                                (0x000044A8)
//Duplicate of MC0_CH0_CR_SC_PR_CNT_CONFIG_REG

#define MC0_CH1_CR_REUT_CH_MISC_CKE_CTRL_REG                           (0x000044B0)
//Duplicate of MC0_CH0_CR_REUT_CH_MISC_CKE_CTRL_REG

#define MC0_CH1_CR_REUT_CH_MISC_ODT_CTRL_REG                           (0x000044B4)
//Duplicate of MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_REG

#define MC0_CH1_CR_SPID_LOW_POWER_CTL_REG                              (0x000044B8)
//Duplicate of MC0_CH0_CR_SPID_LOW_POWER_CTL_REG

#define MC0_CH1_CR_SC_GS_CFG_TRAINING_REG                              (0x000044BC)
//Duplicate of MC0_CH0_CR_SC_GS_CFG_TRAINING_REG

#define MC0_CH1_CR_SCHED_THIRD_CBIT_REG                                (0x000044C0)
//Duplicate of MC0_CH0_CR_SCHED_THIRD_CBIT_REG

#define MC0_CH1_CR_DEADLOCK_BREAKER_REG                                (0x000044C4)
//Duplicate of MC0_CH0_CR_DEADLOCK_BREAKER_REG

#define MC0_CH1_CR_XARB_TC_BUBBLE_INJ_REG                              (0x000044C8)
//Duplicate of MC0_CH0_CR_XARB_TC_BUBBLE_INJ_REG

#define MC0_CH1_CR_XARB_CFG_BUBBLE_INJ_REG                             (0x000044CC)
//Duplicate of MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_REG

#define MC0_CH1_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_REG                 (0x000044D0)
//Duplicate of MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_REG

#define MC0_CH1_CR_SC_BLOCKING_RULES_CFG_REG                           (0x000044D4)
//Duplicate of MC0_CH0_CR_SC_BLOCKING_RULES_CFG_REG

#define MC0_CH1_CR_PWM_DDR_SUBCH0_ACT_COUNTER_REG                      (0x000044D8)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_REG

#define MC0_CH1_CR_PWM_DDR_SUBCH1_ACT_COUNTER_REG                      (0x000044E0)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_REG

#define MC0_CH1_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REG            (0x000044E8)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REG

#define MC0_CH1_CR_PWM_DDR_SUBCH0_DCLK_ACTIVE_COUNTER_A0_REG           (0x000044E8)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_DCLK_ACTIVE_COUNTER_A0_REG

#define MC0_CH1_CR_PWM_DDR_SUBCH1_REQ_OCCUPANCY_COUNTER_REG            (0x000044F0)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REG

#define MC0_CH1_CR_PWM_DDR_SUBCH1_DCLK_ACTIVE_COUNTER_A0_REG           (0x000044F0)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_DCLK_ACTIVE_COUNTER_A0_REG

#define MC0_CH1_CR_WCK_CONFIG_REG                                      (0x000044F8)
//Duplicate of MC0_CH0_CR_WCK_CONFIG_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_0_REG                       (0x00004520)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_1_REG                       (0x00004524)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_2_REG                       (0x00004528)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_3_REG                       (0x0000452C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_4_REG                       (0x00004530)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_5_REG                       (0x00004534)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_6_REG                       (0x00004538)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_7_REG                       (0x0000453C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_8_REG                       (0x00004540)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_9_REG                       (0x00004544)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_10_REG                      (0x00004548)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_11_REG                      (0x0000454C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_12_REG                      (0x00004550)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_13_REG                      (0x00004554)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_14_REG                      (0x00004558)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_15_REG                      (0x0000455C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_16_REG                      (0x00004560)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_17_REG                      (0x00004564)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_18_REG                      (0x00004568)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_19_REG                      (0x0000456C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_20_REG                      (0x00004570)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_21_REG                      (0x00004574)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_22_REG                      (0x00004578)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_23_REG                      (0x0000457C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_24_REG                      (0x00004580)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_25_REG                      (0x00004584)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_26_REG                      (0x00004588)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_27_REG                      (0x0000458C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG               (0x00004590)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_1_REG               (0x00004594)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_2_REG               (0x00004598)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_3_REG               (0x0000459C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_4_REG               (0x000045A0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_5_REG               (0x000045A4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_6_REG               (0x000045A8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_7_REG               (0x000045AC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_8_REG               (0x000045B0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_9_REG               (0x000045B4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_10_REG              (0x000045B8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_11_REG              (0x000045BC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_SHADOW_VALUES_0_REG                 (0x000045C0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_SHADOW_VALUES_1_REG                 (0x000045C4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_SHADOW_VALUES_2_REG                 (0x000045C8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_SHADOW_VALUES_3_REG                 (0x000045CC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_SHADOW_VALUES_4_REG                 (0x000045D0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_SHADOW_VALUES_5_REG                 (0x000045D4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_SHADOW_VALUES_6_REG                 (0x000045D8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_CH1_CR_GENERIC_MRS_FSM_TIMING_STORAGE_REG                  (0x000045E0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_REG

#define MC0_CH1_CR_MCMNTS_RDDATA_CTL_REG                               (0x000045E8)
//Duplicate of MC0_CH0_CR_MCMNTS_RDDATA_CTL_REG

#define MC0_CH1_CR_REUT_CH_MISC_REFRESH_CTRL_REG                       (0x00004604)
//Duplicate of MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_REG

#define MC0_CH1_CR_REUT_CH_MISC_ZQ_CTRL_REG                            (0x00004608)
//Duplicate of MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_REG

#define MC0_CH1_CR_DDR_MR_PARAMS_REG                                   (0x00004610)
//Duplicate of MC0_CH0_CR_DDR_MR_PARAMS_REG

#define MC0_CH1_CR_DDR_MR_COMMAND_REG                                  (0x00004614)
//Duplicate of MC0_CH0_CR_DDR_MR_COMMAND_REG

#define MC0_CH1_CR_DDR_MR_RESULT_0_REG                                 (0x00004618)
//Duplicate of MC0_CH0_CR_DDR_MR_RESULT_0_REG

#define MC0_CH1_CR_DDR_MR_RESULT_1_REG                                 (0x0000461C)
//Duplicate of MC0_CH0_CR_DDR_MR_RESULT_1_REG

#define MC0_CH1_CR_DDR_MR_RESULT_2_REG                                 (0x00004620)
//Duplicate of MC0_CH0_CR_DDR_MR_RESULT_2_REG

#define MC0_CH1_CR_LPDDR_MR4_RANK_TEMPERATURE_REG                      (0x00004624)
//Duplicate of MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_REG

#define MC0_CH1_CR_DDR4_MPR_RANK_TEMPERATURE_REG                       (0x00004628)
//Duplicate of MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_REG

#define MC0_CH1_CR_DESWIZZLE_LOW_ERM_REG                               (0x00004630)
//Duplicate of MC0_CH0_CR_DESWIZZLE_LOW_ERM_REG

#define MC0_CH1_CR_TC_RFP_REG                                          (0x00004638)
//Duplicate of MC0_CH0_CR_TC_RFP_REG

#define MC0_CH1_CR_TC_RFTP_REG                                         (0x0000463C)
//Duplicate of MC0_CH0_CR_TC_RFTP_REG

#define MC0_CH1_CR_TC_SRFTP_REG                                        (0x00004640)
//Duplicate of MC0_CH0_CR_TC_SRFTP_REG

#define MC0_CH1_CR_MC_REFRESH_STAGGER_REG                              (0x00004644)
//Duplicate of MC0_CH0_CR_MC_REFRESH_STAGGER_REG

#define MC0_CH1_CR_TC_ZQCAL_REG                                        (0x00004648)
//Duplicate of MC0_CH0_CR_TC_ZQCAL_REG

#define MC0_CH1_CR_TC_MR2_SHADDOW_REG                                  (0x0000464C)
//Duplicate of MC0_CH0_CR_TC_MR2_SHADDOW_REG

#define MC0_CH1_CR_TC_MR4_SHADDOW_REG                                  (0x00004650)
//Duplicate of MC0_CH0_CR_TC_MR4_SHADDOW_REG

#define MC0_CH1_CR_MC_INIT_STATE_REG                                   (0x00004654)
//Duplicate of MC0_CH0_CR_MC_INIT_STATE_REG

#define MC0_CH1_CR_WDB_VISA_SEL_REG                                    (0x00004658)
//Duplicate of MC0_CH0_CR_WDB_VISA_SEL_REG

#define MC0_CH1_CR_PM_DIMM_IDLE_ENERGY_REG                             (0x00004660)
//Duplicate of MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_REG

#define MC0_CH1_CR_PM_DIMM_PD_ENERGY_REG                               (0x00004664)
//Duplicate of MC0_CH0_CR_PM_DIMM_PD_ENERGY_REG

#define MC0_CH1_CR_PM_DIMM_ACT_ENERGY_REG                              (0x00004668)
//Duplicate of MC0_CH0_CR_PM_DIMM_ACT_ENERGY_REG

#define MC0_CH1_CR_PM_DIMM_RD_ENERGY_REG                               (0x0000466C)
//Duplicate of MC0_CH0_CR_PM_DIMM_RD_ENERGY_REG

#define MC0_CH1_CR_PM_DIMM_WR_ENERGY_REG                               (0x00004670)
//Duplicate of MC0_CH0_CR_PM_DIMM_WR_ENERGY_REG

#define MC0_CH1_CR_SC_WR_DELAY_REG                                     (0x00004678)
//Duplicate of MC0_CH0_CR_SC_WR_DELAY_REG

#define MC0_CH1_CR_READ_RETURN_DFT_REG                                 (0x0000467C)
//Duplicate of MC0_CH0_CR_READ_RETURN_DFT_REG

#define MC0_CH1_CR_DESWIZZLE_LOW_REG                                   (0x00004680)
//Duplicate of MC0_CH0_CR_DESWIZZLE_LOW_ERM_REG

#define MC0_CH1_CR_SC_PBR_REG                                          (0x00004688)
//Duplicate of MC0_CH0_CR_SC_PBR_REG

#define MC0_CH1_CR_LPDDR_PASR_REG                                      (0x00004690)
//Duplicate of MC0_CH0_CR_LPDDR_PASR_REG

#define MC0_CH1_CR_TC_LPDDR4_MISC_REG                                  (0x00004694)
//Duplicate of MC0_CH0_CR_TC_LPDDR4_MISC_REG

#define MC0_CH1_CR_DESWIZZLE_HIGH_ERM_REG                              (0x00004698)
//Duplicate of MC0_CH0_CR_DESWIZZLE_HIGH_ERM_REG

#define MC0_CH1_CR_PM_ALL_RANKS_CKE_LOW_COUNT_REG                      (0x000046B0)
//Duplicate of MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_REG

#define MC0_CH1_CR_PM_ALL_RANKS_CKE_LOW_COUNT_A0_REG                   (0x000046B0)
//Duplicate of MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_A0_REG

#define MC0_CH1_CR_DESWIZZLE_HIGH_REG                                  (0x000046B8)
//Duplicate of MC0_CH0_CR_DESWIZZLE_HIGH_ERM_REG

#define MC0_CH1_CR_TC_SREXITTP_REG                                     (0x000046C0)
//Duplicate of MC0_CH0_CR_TC_SREXITTP_REG

#define MC0_CH1_CR_LP4_DQS_OSCILLATOR_PARAMS_REG                       (0x000046C8)
//Duplicate of MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_REG

#define MC0_CH1_CR_WDB_RD_WR_DFX_DATA_REG                              (0x000046D8)
//Duplicate of MC0_CH0_CR_WDB_RD_WR_DFX_DATA_REG

#define MC0_CH1_CR_WDB_RD_WR_DFX_CTL_REG                               (0x000046E0)
//Duplicate of MC0_CH0_CR_WDB_RD_WR_DFX_CTL_REG

#define MC0_CH1_CR_REF_FSM_STATUS_REG                                  (0x000046E4)
//Duplicate of MC0_CH0_CR_REF_FSM_STATUS_REG

#define MC0_CH1_CR_WDB_MBIST_0_REG                                     (0x000046E8)
//Duplicate of MC0_CH0_CR_WDB_MBIST_0_REG

#define MC0_CH1_CR_WDB_MBIST_1_REG                                     (0x000046EC)
//Duplicate of MC0_CH0_CR_WDB_MBIST_0_REG

#define MC0_CH1_CR_RDB_MBIST_REG                                       (0x000046F8)
//Duplicate of MC0_CH0_CR_WDB_MBIST_0_REG

#define MC0_CH1_CR_ECC_INJECT_COUNT_REG                                (0x000046FC)
//Duplicate of MC0_CH0_CR_ECC_INJECT_COUNT_REG

#define MC0_CH1_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_REG                   (0x00004700)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_REG

#define MC0_CH1_CR_PWM_DDR_SUBCH1_RDDATA_COUNTER_REG                   (0x00004708)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_REG

#define MC0_CH1_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_REG                   (0x00004710)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_REG

#define MC0_CH1_CR_PWM_DDR_SUBCH1_WRDATA_COUNTER_REG                   (0x00004718)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_REG

#define MC0_CH1_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG                   (0x00004720)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC0_CH1_CR_DDR4_MR2_RTT_WR_DIMM1_VALUES_REG                    (0x00004728)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC0_CH1_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG                    (0x00004730)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG

#define MC0_CH1_CR_DDR4_MR6_VREF_DIMM1_VALUES_1_REG                    (0x00004738)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG

#define MC0_CH1_CR_DDR4_MR1_ODIC_DIMM1_VALUES_REG                      (0x00004744)
//Duplicate of MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_REG

#define MC0_CH1_CR_DDR4_MR5_RTT_PARK_VALUES_REG                        (0x00004748)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC0_CH1_CR_DDR4_MR5_RTT_PARK_DIMM1_VALUES_REG                  (0x00004750)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC0_CH1_CR_DDR4_MR1_RTT_NOM_VALUES_REG                         (0x00004758)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC0_CH1_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG                     (0x00004760)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC0_CH1_CR_LPDDR4_DISCRETE_MR_VALUES_1_REG                     (0x00004768)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC0_CH1_CR_LPDDR4_DISCRETE_MR_VALUES_2_REG                     (0x00004770)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC0_CH1_CR_LPDDR4_DISCRETE_MR_VALUES_3_REG                     (0x00004778)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC0_CH1_CR_LPDDR4_DISCRETE_MR_VALUES_4_REG                     (0x00004780)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC0_CH1_CR_LPDDR4_DISCRETE_MR_VALUES_5_REG                     (0x00004788)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC0_CH1_CR_LPDDR4_DISCRETE_MR_VALUES_6_REG                     (0x00004790)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC0_CH1_CR_LPDDR4_DISCRETE_MR_VALUES_7_REG                     (0x00004798)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC0_CH1_CR_DDR4_MR0_MR1_CONTENT_REG                            (0x000047A0)
//Duplicate of MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_REG

#define MC0_CH1_CR_DDR4_MR2_MR3_CONTENT_REG                            (0x000047A4)
//Duplicate of MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_REG

#define MC0_CH1_CR_DDR4_MR4_MR5_CONTENT_REG                            (0x000047A8)
//Duplicate of MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_REG

#define MC0_CH1_CR_DDR4_MR6_MR7_CONTENT_REG                            (0x000047AC)
//Duplicate of MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_REG

#define MC0_CH1_CR_DDR4_MR2_RTT_WR_VALUES_REG                          (0x000047B0)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC0_CH1_CR_DDR4_MR6_VREF_VALUES_0_REG                          (0x000047B8)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG

#define MC0_CH1_CR_DDR4_MR6_VREF_VALUES_1_REG                          (0x000047C0)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG

#define MC0_CH1_CR_LPDDR_MR_CONTENT_REG                                (0x000047C8)
//Duplicate of MC0_CH0_CR_LPDDR_MR_CONTENT_REG

#define MC0_CH1_CR_MRS_FSM_CONTROL_REG                                 (0x000047D0)
//Duplicate of MC0_CH0_CR_MRS_FSM_CONTROL_REG

#define MC0_CH1_CR_MRS_FSM_RUN_REG                                     (0x000047D8)
//Duplicate of MC0_CH0_CR_MRS_FSM_RUN_REG

#define MC0_CH1_CR_DDR4_MR1_ODIC_VALUES_REG                            (0x000047DC)
//Duplicate of MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_REG

#define MC0_CH1_CR_PL_AGENT_CFG_DTF_REG                                (0x000047E0)
//Duplicate of MC0_CH0_CR_PL_AGENT_CFG_DTF_REG

#define MC0_CH1_CR_MCMNTS_GLOBAL_DRIVER_GATE_CFG_REG                   (0x000047E4)
//Duplicate of MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_REG

#define MC0_CH1_CR_DDR4_ECC_DEVICE_VALUES_REG                          (0x000047E8)
//Duplicate of MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_REG

#define MC0_CH1_CR_DDR4_ECC_DEVICE_DIMM1_VALUES_REG                    (0x000047F0)
//Duplicate of MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_REG

#define MC0_CH1_CR_MCMNTS_SPARE_REG                                    (0x000047FC)
//Duplicate of MC0_CH0_CR_MCMNTS_SPARE_REG

#define MC0_BC_CR_TC_PRE_REG                                           (0x00004C00)
//Duplicate of MC0_CH0_CR_TC_PRE_REG

#define MC0_BC_CR_TC_ACT_REG                                           (0x00004C08)
//Duplicate of MC0_CH0_CR_TC_ACT_REG

#define MC0_BC_CR_TC_RDRD_REG                                          (0x00004C0C)
//Duplicate of MC0_CH0_CR_TC_RDRD_REG

#define MC0_BC_CR_TC_RDWR_REG                                          (0x00004C10)
//Duplicate of MC0_CH0_CR_TC_RDWR_REG

#define MC0_BC_CR_TC_WRRD_REG                                          (0x00004C14)
//Duplicate of MC0_CH0_CR_TC_WRRD_REG

#define MC0_BC_CR_TC_WRWR_REG                                          (0x00004C18)
//Duplicate of MC0_CH0_CR_TC_WRWR_REG

#define MC0_BC_CR_SC_ROUNDTRIP_LATENCY_REG                             (0x00004C20)
//Duplicate of MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_REG

#define MC0_BC_CR_SCHED_CBIT_REG                                       (0x00004C28)
//Duplicate of MC0_CH0_CR_SCHED_CBIT_REG

#define MC0_BC_CR_SCHED_SECOND_CBIT_REG                                (0x00004C2C)
//Duplicate of MC0_CH0_CR_SCHED_SECOND_CBIT_REG

#define MC0_BC_CR_DFT_MISC_REG                                         (0x00004C30)
//Duplicate of MC0_CH0_CR_DFT_MISC_REG

#define MC0_BC_CR_SC_PCIT_REG                                          (0x00004C34)
//Duplicate of MC0_CH0_CR_SC_PCIT_REG

#define MC0_BC_CR_ECC_DFT_REG                                          (0x00004C38)
//Duplicate of MC0_CH0_CR_ECC_DFT_REG

#define MC0_BC_CR_PM_PDWN_CONFIG_REG                                   (0x00004C40)
//Duplicate of MC0_CH0_CR_PM_PDWN_CONFIG_REG

#define MC0_BC_CR_WMM_READ_CONFIG_REG                                  (0x00004C44)
//Duplicate of MC0_CH0_CR_WMM_READ_CONFIG_REG

#define MC0_BC_CR_ECCERRLOG0_REG                                       (0x00004C48)
//Duplicate of MC0_CH0_CR_ECCERRLOG0_REG

#define MC0_BC_CR_ECCERRLOG1_REG                                       (0x00004C4C)
//Duplicate of MC0_CH0_CR_ECCERRLOG1_REG

#define MC0_BC_CR_TC_PWRDN_REG                                         (0x00004C50)
//Duplicate of MC0_CH0_CR_TC_PWRDN_REG

#define MC0_BC_CR_QUEUE_ENTRY_DISABLE_RPQ_REG                          (0x00004C58)
//Duplicate of MC0_CH0_CR_QUEUE_ENTRY_DISABLE_RPQ_REG

#define MC0_BC_CR_QUEUE_ENTRY_DISABLE_IPQ_REG                          (0x00004C5C)
//Duplicate of MC0_CH0_CR_QUEUE_ENTRY_DISABLE_IPQ_REG

#define MC0_BC_CR_QUEUE_ENTRY_DISABLE_WPQ_REG                          (0x00004C60)
//Duplicate of MC0_CH0_CR_QUEUE_ENTRY_DISABLE_WPQ_REG

#define MC0_BC_CR_SC_WDBWM_REG                                         (0x00004C68)
//Duplicate of MC0_CH0_CR_SC_WDBWM_REG

#define MC0_BC_CR_TC_ODT_REG                                           (0x00004C70)
//Duplicate of MC0_CH0_CR_TC_ODT_REG

#define MC0_BC_CR_MCSCHEDS_SPARE_REG                                   (0x00004C78)
//Duplicate of MC0_CH0_CR_MCSCHEDS_SPARE_REG

#define MC0_BC_CR_SC_ODT_MATRIX_REG                                    (0x00004C80)
//Duplicate of MC0_CH0_CR_SC_ODT_MATRIX_REG

#define MC0_BC_CR_DFT_BLOCK_REG                                        (0x00004C84)
//Duplicate of MC0_CH0_CR_DFT_BLOCK_REG

#define MC0_BC_CR_SC_GS_CFG_REG                                        (0x00004C88)
//Duplicate of MC0_CH0_CR_SC_GS_CFG_REG

#define MC0_BC_CR_SC_PH_THROTTLING_0_REG                               (0x00004C90)
//Duplicate of MC0_CH0_CR_SC_PH_THROTTLING_0_REG

#define MC0_BC_CR_SC_PH_THROTTLING_1_REG                               (0x00004C94)
//Duplicate of MC0_CH0_CR_SC_PH_THROTTLING_1_REG

#define MC0_BC_CR_SC_PH_THROTTLING_2_REG                               (0x00004C98)
//Duplicate of MC0_CH0_CR_SC_PH_THROTTLING_2_REG

#define MC0_BC_CR_SC_PH_THROTTLING_3_REG                               (0x00004C9C)
//Duplicate of MC0_CH0_CR_SC_PH_THROTTLING_3_REG

#define MC0_BC_CR_SC_WPQ_THRESHOLD_REG                                 (0x00004CA0)
//Duplicate of MC0_CH0_CR_SC_WPQ_THRESHOLD_REG

#define MC0_BC_CR_SC_PR_CNT_CONFIG_REG                                 (0x00004CA8)
//Duplicate of MC0_CH0_CR_SC_PR_CNT_CONFIG_REG

#define MC0_BC_CR_REUT_CH_MISC_CKE_CTRL_REG                            (0x00004CB0)
//Duplicate of MC0_CH0_CR_REUT_CH_MISC_CKE_CTRL_REG

#define MC0_BC_CR_REUT_CH_MISC_ODT_CTRL_REG                            (0x00004CB4)
//Duplicate of MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_REG

#define MC0_BC_CR_SPID_LOW_POWER_CTL_REG                               (0x00004CB8)
//Duplicate of MC0_CH0_CR_SPID_LOW_POWER_CTL_REG

#define MC0_BC_CR_SC_GS_CFG_TRAINING_REG                               (0x00004CBC)
//Duplicate of MC0_CH0_CR_SC_GS_CFG_TRAINING_REG

#define MC0_BC_CR_SCHED_THIRD_CBIT_REG                                 (0x00004CC0)
//Duplicate of MC0_CH0_CR_SCHED_THIRD_CBIT_REG

#define MC0_BC_CR_DEADLOCK_BREAKER_REG                                 (0x00004CC4)
//Duplicate of MC0_CH0_CR_DEADLOCK_BREAKER_REG

#define MC0_BC_CR_XARB_TC_BUBBLE_INJ_REG                               (0x00004CC8)
//Duplicate of MC0_CH0_CR_XARB_TC_BUBBLE_INJ_REG

#define MC0_BC_CR_XARB_CFG_BUBBLE_INJ_REG                              (0x00004CCC)
//Duplicate of MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_REG

#define MC0_BC_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_REG                  (0x00004CD0)
//Duplicate of MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_REG

#define MC0_BC_CR_SC_BLOCKING_RULES_CFG_REG                            (0x00004CD4)
//Duplicate of MC0_CH0_CR_SC_BLOCKING_RULES_CFG_REG

#define MC0_BC_CR_PWM_DDR_SUBCH0_ACT_COUNTER_REG                       (0x00004CD8)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_REG

#define MC0_BC_CR_PWM_DDR_SUBCH1_ACT_COUNTER_REG                       (0x00004CE0)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_REG

#define MC0_BC_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REG             (0x00004CE8)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REG

#define MC0_BC_CR_PWM_DDR_SUBCH0_DCLK_ACTIVE_COUNTER_A0_REG            (0x00004CE8)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_DCLK_ACTIVE_COUNTER_A0_REG

#define MC0_BC_CR_PWM_DDR_SUBCH1_REQ_OCCUPANCY_COUNTER_REG             (0x00004CF0)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REG

#define MC0_BC_CR_PWM_DDR_SUBCH1_DCLK_ACTIVE_COUNTER_A0_REG            (0x00004CF0)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_DCLK_ACTIVE_COUNTER_A0_REG

#define MC0_BC_CR_WCK_CONFIG_REG                                       (0x00004CF8)
//Duplicate of MC0_CH0_CR_WCK_CONFIG_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_0_REG                        (0x00004D20)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_1_REG                        (0x00004D24)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_2_REG                        (0x00004D28)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_3_REG                        (0x00004D2C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_4_REG                        (0x00004D30)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_5_REG                        (0x00004D34)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_6_REG                        (0x00004D38)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_7_REG                        (0x00004D3C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_8_REG                        (0x00004D40)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_9_REG                        (0x00004D44)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_10_REG                       (0x00004D48)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_11_REG                       (0x00004D4C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_12_REG                       (0x00004D50)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_13_REG                       (0x00004D54)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_14_REG                       (0x00004D58)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_15_REG                       (0x00004D5C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_16_REG                       (0x00004D60)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_17_REG                       (0x00004D64)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_18_REG                       (0x00004D68)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_19_REG                       (0x00004D6C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_20_REG                       (0x00004D70)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_21_REG                       (0x00004D74)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_22_REG                       (0x00004D78)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_23_REG                       (0x00004D7C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_24_REG                       (0x00004D80)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_25_REG                       (0x00004D84)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_26_REG                       (0x00004D88)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_27_REG                       (0x00004D8C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG                (0x00004D90)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_1_REG                (0x00004D94)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_2_REG                (0x00004D98)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_3_REG                (0x00004D9C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_4_REG                (0x00004DA0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_5_REG                (0x00004DA4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_6_REG                (0x00004DA8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_7_REG                (0x00004DAC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_8_REG                (0x00004DB0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_9_REG                (0x00004DB4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_10_REG               (0x00004DB8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_11_REG               (0x00004DBC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_SHADOW_VALUES_0_REG                  (0x00004DC0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_SHADOW_VALUES_1_REG                  (0x00004DC4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_SHADOW_VALUES_2_REG                  (0x00004DC8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_SHADOW_VALUES_3_REG                  (0x00004DCC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_SHADOW_VALUES_4_REG                  (0x00004DD0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_SHADOW_VALUES_5_REG                  (0x00004DD4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_SHADOW_VALUES_6_REG                  (0x00004DD8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC0_BC_CR_GENERIC_MRS_FSM_TIMING_STORAGE_REG                   (0x00004DE0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_REG

#define MC0_BC_CR_MCMNTS_RDDATA_CTL_REG                                (0x00004DE8)
//Duplicate of MC0_CH0_CR_MCMNTS_RDDATA_CTL_REG

#define MC0_BC_CR_REUT_CH_MISC_REFRESH_CTRL_REG                        (0x00004E04)
//Duplicate of MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_REG

#define MC0_BC_CR_REUT_CH_MISC_ZQ_CTRL_REG                             (0x00004E08)
//Duplicate of MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_REG

#define MC0_BC_CR_DDR_MR_PARAMS_REG                                    (0x00004E10)
//Duplicate of MC0_CH0_CR_DDR_MR_PARAMS_REG

#define MC0_BC_CR_DDR_MR_COMMAND_REG                                   (0x00004E14)
//Duplicate of MC0_CH0_CR_DDR_MR_COMMAND_REG

#define MC0_BC_CR_DDR_MR_RESULT_0_REG                                  (0x00004E18)
//Duplicate of MC0_CH0_CR_DDR_MR_RESULT_0_REG

#define MC0_BC_CR_DDR_MR_RESULT_1_REG                                  (0x00004E1C)
//Duplicate of MC0_CH0_CR_DDR_MR_RESULT_1_REG

#define MC0_BC_CR_DDR_MR_RESULT_2_REG                                  (0x00004E20)
//Duplicate of MC0_CH0_CR_DDR_MR_RESULT_2_REG

#define MC0_BC_CR_LPDDR_MR4_RANK_TEMPERATURE_REG                       (0x00004E24)
//Duplicate of MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_REG

#define MC0_BC_CR_DDR4_MPR_RANK_TEMPERATURE_REG                        (0x00004E28)
//Duplicate of MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_REG

#define MC0_BC_CR_DESWIZZLE_LOW_ERM_REG                                (0x00004E30)
//Duplicate of MC0_CH0_CR_DESWIZZLE_LOW_ERM_REG

#define MC0_BC_CR_TC_RFP_REG                                           (0x00004E38)
//Duplicate of MC0_CH0_CR_TC_RFP_REG

#define MC0_BC_CR_TC_RFTP_REG                                          (0x00004E3C)
//Duplicate of MC0_CH0_CR_TC_RFTP_REG

#define MC0_BC_CR_TC_SRFTP_REG                                         (0x00004E40)
//Duplicate of MC0_CH0_CR_TC_SRFTP_REG

#define MC0_BC_CR_MC_REFRESH_STAGGER_REG                               (0x00004E44)
//Duplicate of MC0_CH0_CR_MC_REFRESH_STAGGER_REG

#define MC0_BC_CR_TC_ZQCAL_REG                                         (0x00004E48)
//Duplicate of MC0_CH0_CR_TC_ZQCAL_REG

#define MC0_BC_CR_TC_MR2_SHADDOW_REG                                   (0x00004E4C)
//Duplicate of MC0_CH0_CR_TC_MR2_SHADDOW_REG

#define MC0_BC_CR_TC_MR4_SHADDOW_REG                                   (0x00004E50)
//Duplicate of MC0_CH0_CR_TC_MR4_SHADDOW_REG

#define MC0_BC_CR_MC_INIT_STATE_REG                                    (0x00004E54)
//Duplicate of MC0_CH0_CR_MC_INIT_STATE_REG

#define MC0_BC_CR_WDB_VISA_SEL_REG                                     (0x00004E58)
//Duplicate of MC0_CH0_CR_WDB_VISA_SEL_REG

#define MC0_BC_CR_PM_DIMM_IDLE_ENERGY_REG                              (0x00004E60)
//Duplicate of MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_REG

#define MC0_BC_CR_PM_DIMM_PD_ENERGY_REG                                (0x00004E64)
//Duplicate of MC0_CH0_CR_PM_DIMM_PD_ENERGY_REG

#define MC0_BC_CR_PM_DIMM_ACT_ENERGY_REG                               (0x00004E68)
//Duplicate of MC0_CH0_CR_PM_DIMM_ACT_ENERGY_REG

#define MC0_BC_CR_PM_DIMM_RD_ENERGY_REG                                (0x00004E6C)
//Duplicate of MC0_CH0_CR_PM_DIMM_RD_ENERGY_REG

#define MC0_BC_CR_PM_DIMM_WR_ENERGY_REG                                (0x00004E70)
//Duplicate of MC0_CH0_CR_PM_DIMM_WR_ENERGY_REG

#define MC0_BC_CR_SC_WR_DELAY_REG                                      (0x00004E78)
//Duplicate of MC0_CH0_CR_SC_WR_DELAY_REG

#define MC0_BC_CR_READ_RETURN_DFT_REG                                  (0x00004E7C)
//Duplicate of MC0_CH0_CR_READ_RETURN_DFT_REG

#define MC0_BC_CR_DESWIZZLE_LOW_REG                                    (0x00004E80)
//Duplicate of MC0_CH0_CR_DESWIZZLE_LOW_ERM_REG

#define MC0_BC_CR_SC_PBR_REG                                           (0x00004E88)
//Duplicate of MC0_CH0_CR_SC_PBR_REG

#define MC0_BC_CR_LPDDR_PASR_REG                                       (0x00004E90)
//Duplicate of MC0_CH0_CR_LPDDR_PASR_REG

#define MC0_BC_CR_TC_LPDDR4_MISC_REG                                   (0x00004E94)
//Duplicate of MC0_CH0_CR_TC_LPDDR4_MISC_REG

#define MC0_BC_CR_DESWIZZLE_HIGH_ERM_REG                               (0x00004E98)
//Duplicate of MC0_CH0_CR_DESWIZZLE_HIGH_ERM_REG

#define MC0_BC_CR_PM_ALL_RANKS_CKE_LOW_COUNT_REG                       (0x00004EB0)
//Duplicate of MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_REG

#define MC0_BC_CR_PM_ALL_RANKS_CKE_LOW_COUNT_A0_REG                    (0x00004EB0)
//Duplicate of MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_A0_REG

#define MC0_BC_CR_DESWIZZLE_HIGH_REG                                   (0x00004EB8)
//Duplicate of MC0_CH0_CR_DESWIZZLE_HIGH_ERM_REG

#define MC0_BC_CR_TC_SREXITTP_REG                                      (0x00004EC0)
//Duplicate of MC0_CH0_CR_TC_SREXITTP_REG

#define MC0_BC_CR_LP4_DQS_OSCILLATOR_PARAMS_REG                        (0x00004EC8)
//Duplicate of MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_REG

#define MC0_BC_CR_WDB_RD_WR_DFX_DATA_REG                               (0x00004ED8)
//Duplicate of MC0_CH0_CR_WDB_RD_WR_DFX_DATA_REG

#define MC0_BC_CR_WDB_RD_WR_DFX_CTL_REG                                (0x00004EE0)
//Duplicate of MC0_CH0_CR_WDB_RD_WR_DFX_CTL_REG

#define MC0_BC_CR_REF_FSM_STATUS_REG                                   (0x00004EE4)
//Duplicate of MC0_CH0_CR_REF_FSM_STATUS_REG

#define MC0_BC_CR_WDB_MBIST_0_REG                                      (0x00004EE8)
//Duplicate of MC0_CH0_CR_WDB_MBIST_0_REG

#define MC0_BC_CR_WDB_MBIST_1_REG                                      (0x00004EEC)
//Duplicate of MC0_CH0_CR_WDB_MBIST_0_REG

#define MC0_BC_CR_RDB_MBIST_REG                                        (0x00004EF8)
//Duplicate of MC0_CH0_CR_WDB_MBIST_0_REG

#define MC0_BC_CR_ECC_INJECT_COUNT_REG                                 (0x00004EFC)
//Duplicate of MC0_CH0_CR_ECC_INJECT_COUNT_REG

#define MC0_BC_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_REG                    (0x00004F00)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_REG

#define MC0_BC_CR_PWM_DDR_SUBCH1_RDDATA_COUNTER_REG                    (0x00004F08)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_REG

#define MC0_BC_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_REG                    (0x00004F10)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_REG

#define MC0_BC_CR_PWM_DDR_SUBCH1_WRDATA_COUNTER_REG                    (0x00004F18)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_REG

#define MC0_BC_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG                    (0x00004F20)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC0_BC_CR_DDR4_MR2_RTT_WR_DIMM1_VALUES_REG                     (0x00004F28)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC0_BC_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG                     (0x00004F30)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG

#define MC0_BC_CR_DDR4_MR6_VREF_DIMM1_VALUES_1_REG                     (0x00004F38)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG

#define MC0_BC_CR_DDR4_MR1_ODIC_DIMM1_VALUES_REG                       (0x00004F44)
//Duplicate of MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_REG

#define MC0_BC_CR_DDR4_MR5_RTT_PARK_VALUES_REG                         (0x00004F48)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC0_BC_CR_DDR4_MR5_RTT_PARK_DIMM1_VALUES_REG                   (0x00004F50)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC0_BC_CR_DDR4_MR1_RTT_NOM_VALUES_REG                          (0x00004F58)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC0_BC_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG                      (0x00004F60)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC0_BC_CR_LPDDR4_DISCRETE_MR_VALUES_1_REG                      (0x00004F68)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC0_BC_CR_LPDDR4_DISCRETE_MR_VALUES_2_REG                      (0x00004F70)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC0_BC_CR_LPDDR4_DISCRETE_MR_VALUES_3_REG                      (0x00004F78)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC0_BC_CR_LPDDR4_DISCRETE_MR_VALUES_4_REG                      (0x00004F80)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC0_BC_CR_LPDDR4_DISCRETE_MR_VALUES_5_REG                      (0x00004F88)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC0_BC_CR_LPDDR4_DISCRETE_MR_VALUES_6_REG                      (0x00004F90)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC0_BC_CR_LPDDR4_DISCRETE_MR_VALUES_7_REG                      (0x00004F98)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC0_BC_CR_DDR4_MR0_MR1_CONTENT_REG                             (0x00004FA0)
//Duplicate of MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_REG

#define MC0_BC_CR_DDR4_MR2_MR3_CONTENT_REG                             (0x00004FA4)
//Duplicate of MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_REG

#define MC0_BC_CR_DDR4_MR4_MR5_CONTENT_REG                             (0x00004FA8)
//Duplicate of MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_REG

#define MC0_BC_CR_DDR4_MR6_MR7_CONTENT_REG                             (0x00004FAC)
//Duplicate of MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_REG

#define MC0_BC_CR_DDR4_MR2_RTT_WR_VALUES_REG                           (0x00004FB0)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC0_BC_CR_DDR4_MR6_VREF_VALUES_0_REG                           (0x00004FB8)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG

#define MC0_BC_CR_DDR4_MR6_VREF_VALUES_1_REG                           (0x00004FC0)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG

#define MC0_BC_CR_LPDDR_MR_CONTENT_REG                                 (0x00004FC8)
//Duplicate of MC0_CH0_CR_LPDDR_MR_CONTENT_REG

#define MC0_BC_CR_MRS_FSM_CONTROL_REG                                  (0x00004FD0)
//Duplicate of MC0_CH0_CR_MRS_FSM_CONTROL_REG

#define MC0_BC_CR_MRS_FSM_RUN_REG                                      (0x00004FD8)
//Duplicate of MC0_CH0_CR_MRS_FSM_RUN_REG

#define MC0_BC_CR_DDR4_MR1_ODIC_VALUES_REG                             (0x00004FDC)
//Duplicate of MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_REG

#define MC0_BC_CR_PL_AGENT_CFG_DTF_REG                                 (0x00004FE0)
//Duplicate of MC0_CH0_CR_PL_AGENT_CFG_DTF_REG

#define MC0_BC_CR_MCMNTS_GLOBAL_DRIVER_GATE_CFG_REG                    (0x00004FE4)
//Duplicate of MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_REG

#define MC0_BC_CR_DDR4_ECC_DEVICE_VALUES_REG                           (0x00004FE8)
//Duplicate of MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_REG

#define MC0_BC_CR_DDR4_ECC_DEVICE_DIMM1_VALUES_REG                     (0x00004FF0)
//Duplicate of MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_REG

#define MC0_BC_CR_MCMNTS_SPARE_REG                                     (0x00004FFC)
//Duplicate of MC0_CH0_CR_MCMNTS_SPARE_REG
#pragma pack(pop)
#endif
