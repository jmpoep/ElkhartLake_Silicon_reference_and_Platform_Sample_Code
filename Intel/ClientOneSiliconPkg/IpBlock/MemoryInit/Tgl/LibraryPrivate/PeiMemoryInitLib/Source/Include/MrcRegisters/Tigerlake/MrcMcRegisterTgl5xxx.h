#ifndef __MrcMcRegisterTgl5xxx_h__
#define __MrcMcRegisterTgl5xxx_h__
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


#define MC0_MAD_INTER_CHANNEL_REG                                      (0x00005000)

  #define MC0_MAD_INTER_CHANNEL_DDR_TYPE_OFF                           ( 0)
  #define MC0_MAD_INTER_CHANNEL_DDR_TYPE_WID                           ( 3)
  #define MC0_MAD_INTER_CHANNEL_DDR_TYPE_MSK                           (0x00000007)
  #define MC0_MAD_INTER_CHANNEL_DDR_TYPE_MIN                           (0)
  #define MC0_MAD_INTER_CHANNEL_DDR_TYPE_MAX                           (7) // 0x00000007
  #define MC0_MAD_INTER_CHANNEL_DDR_TYPE_DEF                           (0x00000000)
  #define MC0_MAD_INTER_CHANNEL_DDR_TYPE_HSH                           (0x03005000)

  #define MC0_MAD_INTER_CHANNEL_CH_L_MAP_OFF                           ( 4)
  #define MC0_MAD_INTER_CHANNEL_CH_L_MAP_WID                           ( 1)
  #define MC0_MAD_INTER_CHANNEL_CH_L_MAP_MSK                           (0x00000010)
  #define MC0_MAD_INTER_CHANNEL_CH_L_MAP_MIN                           (0)
  #define MC0_MAD_INTER_CHANNEL_CH_L_MAP_MAX                           (1) // 0x00000001
  #define MC0_MAD_INTER_CHANNEL_CH_L_MAP_DEF                           (0x00000000)
  #define MC0_MAD_INTER_CHANNEL_CH_L_MAP_HSH                           (0x01085000)

  #define MC0_MAD_INTER_CHANNEL_CH_S_SIZE_OFF                          (12)
  #define MC0_MAD_INTER_CHANNEL_CH_S_SIZE_WID                          ( 8)
  #define MC0_MAD_INTER_CHANNEL_CH_S_SIZE_MSK                          (0x000FF000)
  #define MC0_MAD_INTER_CHANNEL_CH_S_SIZE_MIN                          (0)
  #define MC0_MAD_INTER_CHANNEL_CH_S_SIZE_MAX                          (255) // 0x000000FF
  #define MC0_MAD_INTER_CHANNEL_CH_S_SIZE_DEF                          (0x00000000)
  #define MC0_MAD_INTER_CHANNEL_CH_S_SIZE_HSH                          (0x08185000)

  #define MC0_MAD_INTER_CHANNEL_CH_WIDTH_OFF                           (27)
  #define MC0_MAD_INTER_CHANNEL_CH_WIDTH_WID                           ( 2)
  #define MC0_MAD_INTER_CHANNEL_CH_WIDTH_MSK                           (0x18000000)
  #define MC0_MAD_INTER_CHANNEL_CH_WIDTH_MIN                           (0)
  #define MC0_MAD_INTER_CHANNEL_CH_WIDTH_MAX                           (3) // 0x00000003
  #define MC0_MAD_INTER_CHANNEL_CH_WIDTH_DEF                           (0x00000000)
  #define MC0_MAD_INTER_CHANNEL_CH_WIDTH_HSH                           (0x02365000)

  #define MC0_MAD_INTER_CHANNEL_HalfCacheLineMode_OFF                  (31)
  #define MC0_MAD_INTER_CHANNEL_HalfCacheLineMode_WID                  ( 1)
  #define MC0_MAD_INTER_CHANNEL_HalfCacheLineMode_MSK                  (0x80000000)
  #define MC0_MAD_INTER_CHANNEL_HalfCacheLineMode_MIN                  (0)
  #define MC0_MAD_INTER_CHANNEL_HalfCacheLineMode_MAX                  (1) // 0x00000001
  #define MC0_MAD_INTER_CHANNEL_HalfCacheLineMode_DEF                  (0x00000000)
  #define MC0_MAD_INTER_CHANNEL_HalfCacheLineMode_HSH                  (0x013E5000)

#define MC0_MAD_INTER_CHANNEL_A0_REG                                   (0x00005000)

  #define MC0_MAD_INTER_CHANNEL_DDR_TYPE_A0_OFF                        ( 0)
  #define MC0_MAD_INTER_CHANNEL_DDR_TYPE_A0_WID                        ( 3)
  #define MC0_MAD_INTER_CHANNEL_DDR_TYPE_A0_MSK                        (0x00000007)
  #define MC0_MAD_INTER_CHANNEL_DDR_TYPE_A0_MIN                        (0)
  #define MC0_MAD_INTER_CHANNEL_DDR_TYPE_A0_MAX                        (7) // 0x00000007
  #define MC0_MAD_INTER_CHANNEL_DDR_TYPE_A0_DEF                        (0x00000000)
  #define MC0_MAD_INTER_CHANNEL_DDR_TYPE_A0_HSH                        (0x03005000)

  #define MC0_MAD_INTER_CHANNEL_CH_L_MAP_A0_OFF                        ( 4)
  #define MC0_MAD_INTER_CHANNEL_CH_L_MAP_A0_WID                        ( 1)
  #define MC0_MAD_INTER_CHANNEL_CH_L_MAP_A0_MSK                        (0x00000010)
  #define MC0_MAD_INTER_CHANNEL_CH_L_MAP_A0_MIN                        (0)
  #define MC0_MAD_INTER_CHANNEL_CH_L_MAP_A0_MAX                        (1) // 0x00000001
  #define MC0_MAD_INTER_CHANNEL_CH_L_MAP_A0_DEF                        (0x00000000)
  #define MC0_MAD_INTER_CHANNEL_CH_L_MAP_A0_HSH                        (0x01085000)

  #define MC0_MAD_INTER_CHANNEL_STKD_MODE_A0_OFF                       ( 8)
  #define MC0_MAD_INTER_CHANNEL_STKD_MODE_A0_WID                       ( 1)
  #define MC0_MAD_INTER_CHANNEL_STKD_MODE_A0_MSK                       (0x00000100)
  #define MC0_MAD_INTER_CHANNEL_STKD_MODE_A0_MIN                       (0)
  #define MC0_MAD_INTER_CHANNEL_STKD_MODE_A0_MAX                       (1) // 0x00000001
  #define MC0_MAD_INTER_CHANNEL_STKD_MODE_A0_DEF                       (0x00000000)
  #define MC0_MAD_INTER_CHANNEL_STKD_MODE_A0_HSH                       (0x01105000)

  #define MC0_MAD_INTER_CHANNEL_STKD_MODE_CH1_A0_OFF                   ( 9)
  #define MC0_MAD_INTER_CHANNEL_STKD_MODE_CH1_A0_WID                   ( 1)
  #define MC0_MAD_INTER_CHANNEL_STKD_MODE_CH1_A0_MSK                   (0x00000200)
  #define MC0_MAD_INTER_CHANNEL_STKD_MODE_CH1_A0_MIN                   (0)
  #define MC0_MAD_INTER_CHANNEL_STKD_MODE_CH1_A0_MAX                   (1) // 0x00000001
  #define MC0_MAD_INTER_CHANNEL_STKD_MODE_CH1_A0_DEF                   (0x00000000)
  #define MC0_MAD_INTER_CHANNEL_STKD_MODE_CH1_A0_HSH                   (0x01125000)

  #define MC0_MAD_INTER_CHANNEL_CH_S_SIZE_A0_OFF                       (12)
  #define MC0_MAD_INTER_CHANNEL_CH_S_SIZE_A0_WID                       ( 8)
  #define MC0_MAD_INTER_CHANNEL_CH_S_SIZE_A0_MSK                       (0x000FF000)
  #define MC0_MAD_INTER_CHANNEL_CH_S_SIZE_A0_MIN                       (0)
  #define MC0_MAD_INTER_CHANNEL_CH_S_SIZE_A0_MAX                       (255) // 0x000000FF
  #define MC0_MAD_INTER_CHANNEL_CH_S_SIZE_A0_DEF                       (0x00000000)
  #define MC0_MAD_INTER_CHANNEL_CH_S_SIZE_A0_HSH                       (0x08185000)

  #define MC0_MAD_INTER_CHANNEL_STKD_MODE_CH_BITS_A0_OFF               (24)
  #define MC0_MAD_INTER_CHANNEL_STKD_MODE_CH_BITS_A0_WID               ( 3)
  #define MC0_MAD_INTER_CHANNEL_STKD_MODE_CH_BITS_A0_MSK               (0x07000000)
  #define MC0_MAD_INTER_CHANNEL_STKD_MODE_CH_BITS_A0_MIN               (0)
  #define MC0_MAD_INTER_CHANNEL_STKD_MODE_CH_BITS_A0_MAX               (7) // 0x00000007
  #define MC0_MAD_INTER_CHANNEL_STKD_MODE_CH_BITS_A0_DEF               (0x00000000)
  #define MC0_MAD_INTER_CHANNEL_STKD_MODE_CH_BITS_A0_HSH               (0x03305000)

  #define MC0_MAD_INTER_CHANNEL_CH_WIDTH_A0_OFF                        (27)
  #define MC0_MAD_INTER_CHANNEL_CH_WIDTH_A0_WID                        ( 2)
  #define MC0_MAD_INTER_CHANNEL_CH_WIDTH_A0_MSK                        (0x18000000)
  #define MC0_MAD_INTER_CHANNEL_CH_WIDTH_A0_MIN                        (0)
  #define MC0_MAD_INTER_CHANNEL_CH_WIDTH_A0_MAX                        (3) // 0x00000003
  #define MC0_MAD_INTER_CHANNEL_CH_WIDTH_A0_DEF                        (0x00000000)
  #define MC0_MAD_INTER_CHANNEL_CH_WIDTH_A0_HSH                        (0x02365000)

  #define MC0_MAD_INTER_CHANNEL_HalfCacheLineMode_A0_OFF               (31)
  #define MC0_MAD_INTER_CHANNEL_HalfCacheLineMode_A0_WID               ( 1)
  #define MC0_MAD_INTER_CHANNEL_HalfCacheLineMode_A0_MSK               (0x80000000)
  #define MC0_MAD_INTER_CHANNEL_HalfCacheLineMode_A0_MIN               (0)
  #define MC0_MAD_INTER_CHANNEL_HalfCacheLineMode_A0_MAX               (1) // 0x00000001
  #define MC0_MAD_INTER_CHANNEL_HalfCacheLineMode_A0_DEF               (0x00000000)
  #define MC0_MAD_INTER_CHANNEL_HalfCacheLineMode_A0_HSH               (0x013E5000)

#define MC0_MAD_INTRA_CH0_REG                                          (0x00005004)

  #define MC0_MAD_INTRA_CH0_DIMM_L_MAP_OFF                             ( 0)
  #define MC0_MAD_INTRA_CH0_DIMM_L_MAP_WID                             ( 1)
  #define MC0_MAD_INTRA_CH0_DIMM_L_MAP_MSK                             (0x00000001)
  #define MC0_MAD_INTRA_CH0_DIMM_L_MAP_MIN                             (0)
  #define MC0_MAD_INTRA_CH0_DIMM_L_MAP_MAX                             (1) // 0x00000001
  #define MC0_MAD_INTRA_CH0_DIMM_L_MAP_DEF                             (0x00000000)
  #define MC0_MAD_INTRA_CH0_DIMM_L_MAP_HSH                             (0x01005004)

  #define MC0_MAD_INTRA_CH0_EIM_OFF                                    ( 8)
  #define MC0_MAD_INTRA_CH0_EIM_WID                                    ( 1)
  #define MC0_MAD_INTRA_CH0_EIM_MSK                                    (0x00000100)
  #define MC0_MAD_INTRA_CH0_EIM_MIN                                    (0)
  #define MC0_MAD_INTRA_CH0_EIM_MAX                                    (1) // 0x00000001
  #define MC0_MAD_INTRA_CH0_EIM_DEF                                    (0x00000000)
  #define MC0_MAD_INTRA_CH0_EIM_HSH                                    (0x01105004)

  #define MC0_MAD_INTRA_CH0_ECC_OFF                                    (12)
  #define MC0_MAD_INTRA_CH0_ECC_WID                                    ( 2)
  #define MC0_MAD_INTRA_CH0_ECC_MSK                                    (0x00003000)
  #define MC0_MAD_INTRA_CH0_ECC_MIN                                    (0)
  #define MC0_MAD_INTRA_CH0_ECC_MAX                                    (3) // 0x00000003
  #define MC0_MAD_INTRA_CH0_ECC_DEF                                    (0x00000000)
  #define MC0_MAD_INTRA_CH0_ECC_HSH                                    (0x02185004)

#define MC0_MAD_INTRA_CH0_A0_REG                                       (0x00005004)

  #define MC0_MAD_INTRA_CH0_DIMM_L_MAP_A0_OFF                          ( 0)
  #define MC0_MAD_INTRA_CH0_DIMM_L_MAP_A0_WID                          ( 1)
  #define MC0_MAD_INTRA_CH0_DIMM_L_MAP_A0_MSK                          (0x00000001)
  #define MC0_MAD_INTRA_CH0_DIMM_L_MAP_A0_MIN                          (0)
  #define MC0_MAD_INTRA_CH0_DIMM_L_MAP_A0_MAX                          (1) // 0x00000001
  #define MC0_MAD_INTRA_CH0_DIMM_L_MAP_A0_DEF                          (0x00000000)
  #define MC0_MAD_INTRA_CH0_DIMM_L_MAP_A0_HSH                          (0x01005004)

  #define MC0_MAD_INTRA_CH0_RI_A0_OFF                                  ( 4)
  #define MC0_MAD_INTRA_CH0_RI_A0_WID                                  ( 1)
  #define MC0_MAD_INTRA_CH0_RI_A0_MSK                                  (0x00000010)
  #define MC0_MAD_INTRA_CH0_RI_A0_MIN                                  (0)
  #define MC0_MAD_INTRA_CH0_RI_A0_MAX                                  (1) // 0x00000001
  #define MC0_MAD_INTRA_CH0_RI_A0_DEF                                  (0x00000000)
  #define MC0_MAD_INTRA_CH0_RI_A0_HSH                                  (0x01085004)

  #define MC0_MAD_INTRA_CH0_EIM_A0_OFF                                 ( 8)
  #define MC0_MAD_INTRA_CH0_EIM_A0_WID                                 ( 1)
  #define MC0_MAD_INTRA_CH0_EIM_A0_MSK                                 (0x00000100)
  #define MC0_MAD_INTRA_CH0_EIM_A0_MIN                                 (0)
  #define MC0_MAD_INTRA_CH0_EIM_A0_MAX                                 (1) // 0x00000001
  #define MC0_MAD_INTRA_CH0_EIM_A0_DEF                                 (0x00000000)
  #define MC0_MAD_INTRA_CH0_EIM_A0_HSH                                 (0x01105004)

  #define MC0_MAD_INTRA_CH0_ECC_A0_OFF                                 (12)
  #define MC0_MAD_INTRA_CH0_ECC_A0_WID                                 ( 2)
  #define MC0_MAD_INTRA_CH0_ECC_A0_MSK                                 (0x00003000)
  #define MC0_MAD_INTRA_CH0_ECC_A0_MIN                                 (0)
  #define MC0_MAD_INTRA_CH0_ECC_A0_MAX                                 (3) // 0x00000003
  #define MC0_MAD_INTRA_CH0_ECC_A0_DEF                                 (0x00000000)
  #define MC0_MAD_INTRA_CH0_ECC_A0_HSH                                 (0x02185004)

#define MC0_MAD_INTRA_CH1_REG                                          (0x00005008)
//Duplicate of MC0_MAD_INTRA_CH0_REG

#define MC0_MAD_DIMM_CH0_REG                                           (0x0000500C)

  #define MC0_MAD_DIMM_CH0_DIMM_L_SIZE_OFF                             ( 0)
  #define MC0_MAD_DIMM_CH0_DIMM_L_SIZE_WID                             ( 7)
  #define MC0_MAD_DIMM_CH0_DIMM_L_SIZE_MSK                             (0x0000007F)
  #define MC0_MAD_DIMM_CH0_DIMM_L_SIZE_MIN                             (0)
  #define MC0_MAD_DIMM_CH0_DIMM_L_SIZE_MAX                             (127) // 0x0000007F
  #define MC0_MAD_DIMM_CH0_DIMM_L_SIZE_DEF                             (0x00000000)
  #define MC0_MAD_DIMM_CH0_DIMM_L_SIZE_HSH                             (0x0700500C)

  #define MC0_MAD_DIMM_CH0_DLW_OFF                                     ( 7)
  #define MC0_MAD_DIMM_CH0_DLW_WID                                     ( 2)
  #define MC0_MAD_DIMM_CH0_DLW_MSK                                     (0x00000180)
  #define MC0_MAD_DIMM_CH0_DLW_MIN                                     (0)
  #define MC0_MAD_DIMM_CH0_DLW_MAX                                     (3) // 0x00000003
  #define MC0_MAD_DIMM_CH0_DLW_DEF                                     (0x00000000)
  #define MC0_MAD_DIMM_CH0_DLW_HSH                                     (0x020E500C)

  #define MC0_MAD_DIMM_CH0_DLNOR_OFF                                   ( 9)
  #define MC0_MAD_DIMM_CH0_DLNOR_WID                                   ( 2)
  #define MC0_MAD_DIMM_CH0_DLNOR_MSK                                   (0x00000600)
  #define MC0_MAD_DIMM_CH0_DLNOR_MIN                                   (0)
  #define MC0_MAD_DIMM_CH0_DLNOR_MAX                                   (3) // 0x00000003
  #define MC0_MAD_DIMM_CH0_DLNOR_DEF                                   (0x00000000)
  #define MC0_MAD_DIMM_CH0_DLNOR_HSH                                   (0x0212500C)

  #define MC0_MAD_DIMM_CH0_DIMM_S_SIZE_OFF                             (16)
  #define MC0_MAD_DIMM_CH0_DIMM_S_SIZE_WID                             ( 7)
  #define MC0_MAD_DIMM_CH0_DIMM_S_SIZE_MSK                             (0x007F0000)
  #define MC0_MAD_DIMM_CH0_DIMM_S_SIZE_MIN                             (0)
  #define MC0_MAD_DIMM_CH0_DIMM_S_SIZE_MAX                             (127) // 0x0000007F
  #define MC0_MAD_DIMM_CH0_DIMM_S_SIZE_DEF                             (0x00000000)
  #define MC0_MAD_DIMM_CH0_DIMM_S_SIZE_HSH                             (0x0720500C)

  #define MC0_MAD_DIMM_CH0_DSW_OFF                                     (24)
  #define MC0_MAD_DIMM_CH0_DSW_WID                                     ( 2)
  #define MC0_MAD_DIMM_CH0_DSW_MSK                                     (0x03000000)
  #define MC0_MAD_DIMM_CH0_DSW_MIN                                     (0)
  #define MC0_MAD_DIMM_CH0_DSW_MAX                                     (3) // 0x00000003
  #define MC0_MAD_DIMM_CH0_DSW_DEF                                     (0x00000000)
  #define MC0_MAD_DIMM_CH0_DSW_HSH                                     (0x0230500C)

  #define MC0_MAD_DIMM_CH0_DSNOR_OFF                                   (26)
  #define MC0_MAD_DIMM_CH0_DSNOR_WID                                   ( 2)
  #define MC0_MAD_DIMM_CH0_DSNOR_MSK                                   (0x0C000000)
  #define MC0_MAD_DIMM_CH0_DSNOR_MIN                                   (0)
  #define MC0_MAD_DIMM_CH0_DSNOR_MAX                                   (3) // 0x00000003
  #define MC0_MAD_DIMM_CH0_DSNOR_DEF                                   (0x00000000)
  #define MC0_MAD_DIMM_CH0_DSNOR_HSH                                   (0x0234500C)

  #define MC0_MAD_DIMM_CH0_DLS_BG0_on_bit_11_OFF                       (29)
  #define MC0_MAD_DIMM_CH0_DLS_BG0_on_bit_11_WID                       ( 1)
  #define MC0_MAD_DIMM_CH0_DLS_BG0_on_bit_11_MSK                       (0x20000000)
  #define MC0_MAD_DIMM_CH0_DLS_BG0_on_bit_11_MIN                       (0)
  #define MC0_MAD_DIMM_CH0_DLS_BG0_on_bit_11_MAX                       (1) // 0x00000001
  #define MC0_MAD_DIMM_CH0_DLS_BG0_on_bit_11_DEF                       (0x00000000)
  #define MC0_MAD_DIMM_CH0_DLS_BG0_on_bit_11_HSH                       (0x013A500C)

#define MC0_MAD_DIMM_CH1_REG                                           (0x00005010)
//Duplicate of MC0_MAD_DIMM_CH0_REG

#define MC0_MCDECS_MISC_REG                                            (0x00005018)

  #define MC0_MCDECS_MISC_Spare_RW_OFF                                 ( 0)
  #define MC0_MCDECS_MISC_Spare_RW_WID                                 (12)
  #define MC0_MCDECS_MISC_Spare_RW_MSK                                 (0x00000FFF)
  #define MC0_MCDECS_MISC_Spare_RW_MIN                                 (0)
  #define MC0_MCDECS_MISC_Spare_RW_MAX                                 (4095) // 0x00000FFF
  #define MC0_MCDECS_MISC_Spare_RW_DEF                                 (0x00000000)
  #define MC0_MCDECS_MISC_Spare_RW_HSH                                 (0x0C005018)

  #define MC0_MCDECS_MISC_VISAByteSel_OFF                              (12)
  #define MC0_MCDECS_MISC_VISAByteSel_WID                              ( 4)
  #define MC0_MCDECS_MISC_VISAByteSel_MSK                              (0x0000F000)
  #define MC0_MCDECS_MISC_VISAByteSel_MIN                              (0)
  #define MC0_MCDECS_MISC_VISAByteSel_MAX                              (15) // 0x0000000F
  #define MC0_MCDECS_MISC_VISAByteSel_DEF                              (0x00000000)
  #define MC0_MCDECS_MISC_VISAByteSel_HSH                              (0x04185018)

  #define MC0_MCDECS_MISC_spare_RW_V_OFF                               (16)
  #define MC0_MCDECS_MISC_spare_RW_V_WID                               (16)
  #define MC0_MCDECS_MISC_spare_RW_V_MSK                               (0xFFFF0000)
  #define MC0_MCDECS_MISC_spare_RW_V_MIN                               (0)
  #define MC0_MCDECS_MISC_spare_RW_V_MAX                               (65535) // 0x0000FFFF
  #define MC0_MCDECS_MISC_spare_RW_V_DEF                               (0x00000000)
  #define MC0_MCDECS_MISC_spare_RW_V_HSH                               (0x10205018)

#define MC0_MCDECS_CBIT_REG                                            (0x0000501C)

  #define MC0_MCDECS_CBIT_increase_rcomp_OFF                           ( 0)
  #define MC0_MCDECS_CBIT_increase_rcomp_WID                           ( 1)
  #define MC0_MCDECS_CBIT_increase_rcomp_MSK                           (0x00000001)
  #define MC0_MCDECS_CBIT_increase_rcomp_MIN                           (0)
  #define MC0_MCDECS_CBIT_increase_rcomp_MAX                           (1) // 0x00000001
  #define MC0_MCDECS_CBIT_increase_rcomp_DEF                           (0x00000000)
  #define MC0_MCDECS_CBIT_increase_rcomp_HSH                           (0x0100501C)

  #define MC0_MCDECS_CBIT_rank2_to_rank1_OFF                           ( 1)
  #define MC0_MCDECS_CBIT_rank2_to_rank1_WID                           ( 1)
  #define MC0_MCDECS_CBIT_rank2_to_rank1_MSK                           (0x00000002)
  #define MC0_MCDECS_CBIT_rank2_to_rank1_MIN                           (0)
  #define MC0_MCDECS_CBIT_rank2_to_rank1_MAX                           (1) // 0x00000001
  #define MC0_MCDECS_CBIT_rank2_to_rank1_DEF                           (0x00000000)
  #define MC0_MCDECS_CBIT_rank2_to_rank1_HSH                           (0x0102501C)

  #define MC0_MCDECS_CBIT_ovrd_pcu_sr_exit_OFF                         ( 2)
  #define MC0_MCDECS_CBIT_ovrd_pcu_sr_exit_WID                         ( 1)
  #define MC0_MCDECS_CBIT_ovrd_pcu_sr_exit_MSK                         (0x00000004)
  #define MC0_MCDECS_CBIT_ovrd_pcu_sr_exit_MIN                         (0)
  #define MC0_MCDECS_CBIT_ovrd_pcu_sr_exit_MAX                         (1) // 0x00000001
  #define MC0_MCDECS_CBIT_ovrd_pcu_sr_exit_DEF                         (0x00000000)
  #define MC0_MCDECS_CBIT_ovrd_pcu_sr_exit_HSH                         (0x0104501C)

  #define MC0_MCDECS_CBIT_psmi_freeze_pwm_counters_OFF                 ( 3)
  #define MC0_MCDECS_CBIT_psmi_freeze_pwm_counters_WID                 ( 1)
  #define MC0_MCDECS_CBIT_psmi_freeze_pwm_counters_MSK                 (0x00000008)
  #define MC0_MCDECS_CBIT_psmi_freeze_pwm_counters_MIN                 (0)
  #define MC0_MCDECS_CBIT_psmi_freeze_pwm_counters_MAX                 (1) // 0x00000001
  #define MC0_MCDECS_CBIT_psmi_freeze_pwm_counters_DEF                 (0x00000000)
  #define MC0_MCDECS_CBIT_psmi_freeze_pwm_counters_HSH                 (0x0106501C)

  #define MC0_MCDECS_CBIT_dis_single_ch_sr_OFF                         ( 4)
  #define MC0_MCDECS_CBIT_dis_single_ch_sr_WID                         ( 1)
  #define MC0_MCDECS_CBIT_dis_single_ch_sr_MSK                         (0x00000010)
  #define MC0_MCDECS_CBIT_dis_single_ch_sr_MIN                         (0)
  #define MC0_MCDECS_CBIT_dis_single_ch_sr_MAX                         (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_single_ch_sr_DEF                         (0x00000001)
  #define MC0_MCDECS_CBIT_dis_single_ch_sr_HSH                         (0x0108501C)

  #define MC0_MCDECS_CBIT_dis_other_ch_stolen_ref_OFF                  ( 5)
  #define MC0_MCDECS_CBIT_dis_other_ch_stolen_ref_WID                  ( 1)
  #define MC0_MCDECS_CBIT_dis_other_ch_stolen_ref_MSK                  (0x00000020)
  #define MC0_MCDECS_CBIT_dis_other_ch_stolen_ref_MIN                  (0)
  #define MC0_MCDECS_CBIT_dis_other_ch_stolen_ref_MAX                  (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_other_ch_stolen_ref_DEF                  (0x00000001)
  #define MC0_MCDECS_CBIT_dis_other_ch_stolen_ref_HSH                  (0x010A501C)

  #define MC0_MCDECS_CBIT_ForceSREntry_dft_OFF                         ( 6)
  #define MC0_MCDECS_CBIT_ForceSREntry_dft_WID                         ( 1)
  #define MC0_MCDECS_CBIT_ForceSREntry_dft_MSK                         (0x00000040)
  #define MC0_MCDECS_CBIT_ForceSREntry_dft_MIN                         (0)
  #define MC0_MCDECS_CBIT_ForceSREntry_dft_MAX                         (1) // 0x00000001
  #define MC0_MCDECS_CBIT_ForceSREntry_dft_DEF                         (0x00000000)
  #define MC0_MCDECS_CBIT_ForceSREntry_dft_HSH                         (0x010C501C)

  #define MC0_MCDECS_CBIT_reserved_OFF                                 ( 7)
  #define MC0_MCDECS_CBIT_reserved_WID                                 ( 2)
  #define MC0_MCDECS_CBIT_reserved_MSK                                 (0x00000180)
  #define MC0_MCDECS_CBIT_reserved_MIN                                 (0)
  #define MC0_MCDECS_CBIT_reserved_MAX                                 (3) // 0x00000003
  #define MC0_MCDECS_CBIT_reserved_DEF                                 (0x00000000)
  #define MC0_MCDECS_CBIT_reserved_HSH                                 (0x020E501C)

  #define MC0_MCDECS_CBIT_ForceSREntry_dft_is_sticky_OFF               ( 9)
  #define MC0_MCDECS_CBIT_ForceSREntry_dft_is_sticky_WID               ( 1)
  #define MC0_MCDECS_CBIT_ForceSREntry_dft_is_sticky_MSK               (0x00000200)
  #define MC0_MCDECS_CBIT_ForceSREntry_dft_is_sticky_MIN               (0)
  #define MC0_MCDECS_CBIT_ForceSREntry_dft_is_sticky_MAX               (1) // 0x00000001
  #define MC0_MCDECS_CBIT_ForceSREntry_dft_is_sticky_DEF               (0x00000001)
  #define MC0_MCDECS_CBIT_ForceSREntry_dft_is_sticky_HSH               (0x0112501C)

  #define MC0_MCDECS_CBIT_iosfsb_keep_ISM_active_OFF                   (11)
  #define MC0_MCDECS_CBIT_iosfsb_keep_ISM_active_WID                   ( 1)
  #define MC0_MCDECS_CBIT_iosfsb_keep_ISM_active_MSK                   (0x00000800)
  #define MC0_MCDECS_CBIT_iosfsb_keep_ISM_active_MIN                   (0)
  #define MC0_MCDECS_CBIT_iosfsb_keep_ISM_active_MAX                   (1) // 0x00000001
  #define MC0_MCDECS_CBIT_iosfsb_keep_ISM_active_DEF                   (0x00000000)
  #define MC0_MCDECS_CBIT_iosfsb_keep_ISM_active_HSH                   (0x0116501C)

  #define MC0_MCDECS_CBIT_ignoreRefBetweenSRX2SRE_OFF                  (12)
  #define MC0_MCDECS_CBIT_ignoreRefBetweenSRX2SRE_WID                  ( 1)
  #define MC0_MCDECS_CBIT_ignoreRefBetweenSRX2SRE_MSK                  (0x00001000)
  #define MC0_MCDECS_CBIT_ignoreRefBetweenSRX2SRE_MIN                  (0)
  #define MC0_MCDECS_CBIT_ignoreRefBetweenSRX2SRE_MAX                  (1) // 0x00000001
  #define MC0_MCDECS_CBIT_ignoreRefBetweenSRX2SRE_DEF                  (0x00000000)
  #define MC0_MCDECS_CBIT_ignoreRefBetweenSRX2SRE_HSH                  (0x0118501C)

  #define MC0_MCDECS_CBIT_dis_cmi_spec_req_early_valid_OFF             (14)
  #define MC0_MCDECS_CBIT_dis_cmi_spec_req_early_valid_WID             ( 1)
  #define MC0_MCDECS_CBIT_dis_cmi_spec_req_early_valid_MSK             (0x00004000)
  #define MC0_MCDECS_CBIT_dis_cmi_spec_req_early_valid_MIN             (0)
  #define MC0_MCDECS_CBIT_dis_cmi_spec_req_early_valid_MAX             (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_cmi_spec_req_early_valid_DEF             (0x00000000)
  #define MC0_MCDECS_CBIT_dis_cmi_spec_req_early_valid_HSH             (0x011C501C)

  #define MC0_MCDECS_CBIT_Dis_EFLOW_fwd_data_hack_OFF                  (15)
  #define MC0_MCDECS_CBIT_Dis_EFLOW_fwd_data_hack_WID                  ( 1)
  #define MC0_MCDECS_CBIT_Dis_EFLOW_fwd_data_hack_MSK                  (0x00008000)
  #define MC0_MCDECS_CBIT_Dis_EFLOW_fwd_data_hack_MIN                  (0)
  #define MC0_MCDECS_CBIT_Dis_EFLOW_fwd_data_hack_MAX                  (1) // 0x00000001
  #define MC0_MCDECS_CBIT_Dis_EFLOW_fwd_data_hack_DEF                  (0x00000000)
  #define MC0_MCDECS_CBIT_Dis_EFLOW_fwd_data_hack_HSH                  (0x011E501C)

  #define MC0_MCDECS_CBIT_freeze_visa_values_OFF                       (16)
  #define MC0_MCDECS_CBIT_freeze_visa_values_WID                       ( 1)
  #define MC0_MCDECS_CBIT_freeze_visa_values_MSK                       (0x00010000)
  #define MC0_MCDECS_CBIT_freeze_visa_values_MIN                       (0)
  #define MC0_MCDECS_CBIT_freeze_visa_values_MAX                       (1) // 0x00000001
  #define MC0_MCDECS_CBIT_freeze_visa_values_DEF                       (0x00000000)
  #define MC0_MCDECS_CBIT_freeze_visa_values_HSH                       (0x0120501C)

  #define MC0_MCDECS_CBIT_freeze_visa_values_on_RTB_OFF                (17)
  #define MC0_MCDECS_CBIT_freeze_visa_values_on_RTB_WID                ( 1)
  #define MC0_MCDECS_CBIT_freeze_visa_values_on_RTB_MSK                (0x00020000)
  #define MC0_MCDECS_CBIT_freeze_visa_values_on_RTB_MIN                (0)
  #define MC0_MCDECS_CBIT_freeze_visa_values_on_RTB_MAX                (1) // 0x00000001
  #define MC0_MCDECS_CBIT_freeze_visa_values_on_RTB_DEF                (0x00000000)
  #define MC0_MCDECS_CBIT_freeze_visa_values_on_RTB_HSH                (0x0122501C)

  #define MC0_MCDECS_CBIT_dis_cmi_ep_power_flows_OFF                   (18)
  #define MC0_MCDECS_CBIT_dis_cmi_ep_power_flows_WID                   ( 1)
  #define MC0_MCDECS_CBIT_dis_cmi_ep_power_flows_MSK                   (0x00040000)
  #define MC0_MCDECS_CBIT_dis_cmi_ep_power_flows_MIN                   (0)
  #define MC0_MCDECS_CBIT_dis_cmi_ep_power_flows_MAX                   (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_cmi_ep_power_flows_DEF                   (0x00000000)
  #define MC0_MCDECS_CBIT_dis_cmi_ep_power_flows_HSH                   (0x0124501C)

  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_opcodes_OFF                (19)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_opcodes_WID                ( 1)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_opcodes_MSK                (0x00080000)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_opcodes_MIN                (0)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_opcodes_MAX                (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_opcodes_DEF                (0x00000000)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_opcodes_HSH                (0x0126501C)

  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_bar_OFF                    (20)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_bar_WID                    ( 1)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_bar_MSK                    (0x00100000)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_bar_MIN                    (0)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_bar_MAX                    (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_bar_DEF                    (0x00000000)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_bar_HSH                    (0x0128501C)

  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_range_OFF                  (21)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_range_WID                  ( 1)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_range_MSK                  (0x00200000)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_range_MIN                  (0)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_range_MAX                  (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_range_DEF                  (0x00000000)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_range_HSH                  (0x012A501C)

  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_sai_OFF                    (22)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_sai_WID                    ( 1)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_sai_MSK                    (0x00400000)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_sai_MIN                    (0)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_sai_MAX                    (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_sai_DEF                    (0x00000000)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_sai_HSH                    (0x012C501C)

  #define MC0_MCDECS_CBIT_delay_normal_mode_when_temp_read_OFF         (23)
  #define MC0_MCDECS_CBIT_delay_normal_mode_when_temp_read_WID         ( 1)
  #define MC0_MCDECS_CBIT_delay_normal_mode_when_temp_read_MSK         (0x00800000)
  #define MC0_MCDECS_CBIT_delay_normal_mode_when_temp_read_MIN         (0)
  #define MC0_MCDECS_CBIT_delay_normal_mode_when_temp_read_MAX         (1) // 0x00000001
  #define MC0_MCDECS_CBIT_delay_normal_mode_when_temp_read_DEF         (0x00000000)
  #define MC0_MCDECS_CBIT_delay_normal_mode_when_temp_read_HSH         (0x012E501C)

  #define MC0_MCDECS_CBIT_dis_cmi_spec_rsp_cpl_early_valid_OFF         (24)
  #define MC0_MCDECS_CBIT_dis_cmi_spec_rsp_cpl_early_valid_WID         ( 1)
  #define MC0_MCDECS_CBIT_dis_cmi_spec_rsp_cpl_early_valid_MSK         (0x01000000)
  #define MC0_MCDECS_CBIT_dis_cmi_spec_rsp_cpl_early_valid_MIN         (0)
  #define MC0_MCDECS_CBIT_dis_cmi_spec_rsp_cpl_early_valid_MAX         (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_cmi_spec_rsp_cpl_early_valid_DEF         (0x00000000)
  #define MC0_MCDECS_CBIT_dis_cmi_spec_rsp_cpl_early_valid_HSH         (0x0130501C)

  #define MC0_MCDECS_CBIT_force_sb_ep_clk_req_OFF                      (25)
  #define MC0_MCDECS_CBIT_force_sb_ep_clk_req_WID                      ( 1)
  #define MC0_MCDECS_CBIT_force_sb_ep_clk_req_MSK                      (0x02000000)
  #define MC0_MCDECS_CBIT_force_sb_ep_clk_req_MIN                      (0)
  #define MC0_MCDECS_CBIT_force_sb_ep_clk_req_MAX                      (1) // 0x00000001
  #define MC0_MCDECS_CBIT_force_sb_ep_clk_req_DEF                      (0x00000000)
  #define MC0_MCDECS_CBIT_force_sb_ep_clk_req_HSH                      (0x0132501C)

  #define MC0_MCDECS_CBIT_dis_cmi_wr_rsp_OFF                           (26)
  #define MC0_MCDECS_CBIT_dis_cmi_wr_rsp_WID                           ( 1)
  #define MC0_MCDECS_CBIT_dis_cmi_wr_rsp_MSK                           (0x04000000)
  #define MC0_MCDECS_CBIT_dis_cmi_wr_rsp_MIN                           (0)
  #define MC0_MCDECS_CBIT_dis_cmi_wr_rsp_MAX                           (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_cmi_wr_rsp_DEF                           (0x00000000)
  #define MC0_MCDECS_CBIT_dis_cmi_wr_rsp_HSH                           (0x0134501C)

  #define MC0_MCDECS_CBIT_dis_iosf_sb_clk_gate_OFF                     (27)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_clk_gate_WID                     ( 1)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_clk_gate_MSK                     (0x08000000)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_clk_gate_MIN                     (0)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_clk_gate_MAX                     (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_iosf_sb_clk_gate_DEF                     (0x00000000)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_clk_gate_HSH                     (0x0136501C)

  #define MC0_MCDECS_CBIT_dis_glbdrv_clk_gate_OFF                      (28)
  #define MC0_MCDECS_CBIT_dis_glbdrv_clk_gate_WID                      ( 1)
  #define MC0_MCDECS_CBIT_dis_glbdrv_clk_gate_MSK                      (0x10000000)
  #define MC0_MCDECS_CBIT_dis_glbdrv_clk_gate_MIN                      (0)
  #define MC0_MCDECS_CBIT_dis_glbdrv_clk_gate_MAX                      (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_glbdrv_clk_gate_DEF                      (0x00000000)
  #define MC0_MCDECS_CBIT_dis_glbdrv_clk_gate_HSH                      (0x0138501C)

  #define MC0_MCDECS_CBIT_dis_reg_clk_gate_OFF                         (29)
  #define MC0_MCDECS_CBIT_dis_reg_clk_gate_WID                         ( 1)
  #define MC0_MCDECS_CBIT_dis_reg_clk_gate_MSK                         (0x20000000)
  #define MC0_MCDECS_CBIT_dis_reg_clk_gate_MIN                         (0)
  #define MC0_MCDECS_CBIT_dis_reg_clk_gate_MAX                         (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_reg_clk_gate_DEF                         (0x00000000)
  #define MC0_MCDECS_CBIT_dis_reg_clk_gate_HSH                         (0x013A501C)

  #define MC0_MCDECS_CBIT_dis_clk_gate_OFF                             (31)
  #define MC0_MCDECS_CBIT_dis_clk_gate_WID                             ( 1)
  #define MC0_MCDECS_CBIT_dis_clk_gate_MSK                             (0x80000000)
  #define MC0_MCDECS_CBIT_dis_clk_gate_MIN                             (0)
  #define MC0_MCDECS_CBIT_dis_clk_gate_MAX                             (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_clk_gate_DEF                             (0x00000000)
  #define MC0_MCDECS_CBIT_dis_clk_gate_HSH                             (0x013E501C)

#define MC0_CHANNEL_HASH_REG                                           (0x00005024)

  #define MC0_CHANNEL_HASH_HASH_MASK_OFF                               ( 6)
  #define MC0_CHANNEL_HASH_HASH_MASK_WID                               (14)
  #define MC0_CHANNEL_HASH_HASH_MASK_MSK                               (0x000FFFC0)
  #define MC0_CHANNEL_HASH_HASH_MASK_MIN                               (0)
  #define MC0_CHANNEL_HASH_HASH_MASK_MAX                               (16383) // 0x00003FFF
  #define MC0_CHANNEL_HASH_HASH_MASK_DEF                               (0x00000000)
  #define MC0_CHANNEL_HASH_HASH_MASK_HSH                               (0x0E0C5024)

  #define MC0_CHANNEL_HASH_HASH_LSB_MASK_BIT_OFF                       (24)
  #define MC0_CHANNEL_HASH_HASH_LSB_MASK_BIT_WID                       ( 3)
  #define MC0_CHANNEL_HASH_HASH_LSB_MASK_BIT_MSK                       (0x07000000)
  #define MC0_CHANNEL_HASH_HASH_LSB_MASK_BIT_MIN                       (0)
  #define MC0_CHANNEL_HASH_HASH_LSB_MASK_BIT_MAX                       (7) // 0x00000007
  #define MC0_CHANNEL_HASH_HASH_LSB_MASK_BIT_DEF                       (0x00000000)
  #define MC0_CHANNEL_HASH_HASH_LSB_MASK_BIT_HSH                       (0x03305024)

  #define MC0_CHANNEL_HASH_HASH_MODE_OFF                               (28)
  #define MC0_CHANNEL_HASH_HASH_MODE_WID                               ( 1)
  #define MC0_CHANNEL_HASH_HASH_MODE_MSK                               (0x10000000)
  #define MC0_CHANNEL_HASH_HASH_MODE_MIN                               (0)
  #define MC0_CHANNEL_HASH_HASH_MODE_MAX                               (1) // 0x00000001
  #define MC0_CHANNEL_HASH_HASH_MODE_DEF                               (0x00000000)
  #define MC0_CHANNEL_HASH_HASH_MODE_HSH                               (0x01385024)

#define MC0_CHANNEL_EHASH_REG                                          (0x00005028)

  #define MC0_CHANNEL_EHASH_EHASH_MASK_OFF                             ( 6)
  #define MC0_CHANNEL_EHASH_EHASH_MASK_WID                             (14)
  #define MC0_CHANNEL_EHASH_EHASH_MASK_MSK                             (0x000FFFC0)
  #define MC0_CHANNEL_EHASH_EHASH_MASK_MIN                             (0)
  #define MC0_CHANNEL_EHASH_EHASH_MASK_MAX                             (16383) // 0x00003FFF
  #define MC0_CHANNEL_EHASH_EHASH_MASK_DEF                             (0x00000000)
  #define MC0_CHANNEL_EHASH_EHASH_MASK_HSH                             (0x0E0C5028)

  #define MC0_CHANNEL_EHASH_EHASH_LSB_MASK_BIT_OFF                     (24)
  #define MC0_CHANNEL_EHASH_EHASH_LSB_MASK_BIT_WID                     ( 3)
  #define MC0_CHANNEL_EHASH_EHASH_LSB_MASK_BIT_MSK                     (0x07000000)
  #define MC0_CHANNEL_EHASH_EHASH_LSB_MASK_BIT_MIN                     (0)
  #define MC0_CHANNEL_EHASH_EHASH_LSB_MASK_BIT_MAX                     (7) // 0x00000007
  #define MC0_CHANNEL_EHASH_EHASH_LSB_MASK_BIT_DEF                     (0x00000000)
  #define MC0_CHANNEL_EHASH_EHASH_LSB_MASK_BIT_HSH                     (0x03305028)

  #define MC0_CHANNEL_EHASH_EHASH_MODE_OFF                             (28)
  #define MC0_CHANNEL_EHASH_EHASH_MODE_WID                             ( 1)
  #define MC0_CHANNEL_EHASH_EHASH_MODE_MSK                             (0x10000000)
  #define MC0_CHANNEL_EHASH_EHASH_MODE_MIN                             (0)
  #define MC0_CHANNEL_EHASH_EHASH_MODE_MAX                             (1) // 0x00000001
  #define MC0_CHANNEL_EHASH_EHASH_MODE_DEF                             (0x00000000)
  #define MC0_CHANNEL_EHASH_EHASH_MODE_HSH                             (0x01385028)

#define MC0_MC_INIT_STATE_G_REG                                        (0x00005030)

  #define MC0_MC_INIT_STATE_G_ddr_reset_OFF                            ( 1)
  #define MC0_MC_INIT_STATE_G_ddr_reset_WID                            ( 1)
  #define MC0_MC_INIT_STATE_G_ddr_reset_MSK                            (0x00000002)
  #define MC0_MC_INIT_STATE_G_ddr_reset_MIN                            (0)
  #define MC0_MC_INIT_STATE_G_ddr_reset_MAX                            (1) // 0x00000001
  #define MC0_MC_INIT_STATE_G_ddr_reset_DEF                            (0x00000001)
  #define MC0_MC_INIT_STATE_G_ddr_reset_HSH                            (0x01025030)

  #define MC0_MC_INIT_STATE_G_refresh_enable_OFF                       ( 3)
  #define MC0_MC_INIT_STATE_G_refresh_enable_WID                       ( 1)
  #define MC0_MC_INIT_STATE_G_refresh_enable_MSK                       (0x00000008)
  #define MC0_MC_INIT_STATE_G_refresh_enable_MIN                       (0)
  #define MC0_MC_INIT_STATE_G_refresh_enable_MAX                       (1) // 0x00000001
  #define MC0_MC_INIT_STATE_G_refresh_enable_DEF                       (0x00000000)
  #define MC0_MC_INIT_STATE_G_refresh_enable_HSH                       (0x01065030)

  #define MC0_MC_INIT_STATE_G_mc_init_done_ack_OFF                     ( 5)
  #define MC0_MC_INIT_STATE_G_mc_init_done_ack_WID                     ( 1)
  #define MC0_MC_INIT_STATE_G_mc_init_done_ack_MSK                     (0x00000020)
  #define MC0_MC_INIT_STATE_G_mc_init_done_ack_MIN                     (0)
  #define MC0_MC_INIT_STATE_G_mc_init_done_ack_MAX                     (1) // 0x00000001
  #define MC0_MC_INIT_STATE_G_mc_init_done_ack_DEF                     (0x00000000)
  #define MC0_MC_INIT_STATE_G_mc_init_done_ack_HSH                     (0x010A5030)

  #define MC0_MC_INIT_STATE_G_mrc_done_OFF                             ( 7)
  #define MC0_MC_INIT_STATE_G_mrc_done_WID                             ( 1)
  #define MC0_MC_INIT_STATE_G_mrc_done_MSK                             (0x00000080)
  #define MC0_MC_INIT_STATE_G_mrc_done_MIN                             (0)
  #define MC0_MC_INIT_STATE_G_mrc_done_MAX                             (1) // 0x00000001
  #define MC0_MC_INIT_STATE_G_mrc_done_DEF                             (0x00000000)
  #define MC0_MC_INIT_STATE_G_mrc_done_HSH                             (0x010E5030)

  #define MC0_MC_INIT_STATE_G_pure_srx_OFF                             ( 9)
  #define MC0_MC_INIT_STATE_G_pure_srx_WID                             ( 1)
  #define MC0_MC_INIT_STATE_G_pure_srx_MSK                             (0x00000200)
  #define MC0_MC_INIT_STATE_G_pure_srx_MIN                             (0)
  #define MC0_MC_INIT_STATE_G_pure_srx_MAX                             (1) // 0x00000001
  #define MC0_MC_INIT_STATE_G_pure_srx_DEF                             (0x00000000)
  #define MC0_MC_INIT_STATE_G_pure_srx_HSH                             (0x01125030)

  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_0_OFF                  (11)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_0_WID                  ( 1)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_0_MSK                  (0x00000800)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_0_MIN                  (0)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_0_MAX                  (1) // 0x00000001
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_0_DEF                  (0x00000000)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_0_HSH                  (0x01165030)

  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_1_OFF                  (12)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_1_WID                  ( 1)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_1_MSK                  (0x00001000)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_1_MIN                  (0)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_1_MAX                  (1) // 0x00000001
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_1_DEF                  (0x00000000)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_1_HSH                  (0x01185030)

  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_2_OFF                  (13)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_2_WID                  ( 1)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_2_MSK                  (0x00002000)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_2_MIN                  (0)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_2_MAX                  (1) // 0x00000001
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_2_DEF                  (0x00000000)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_2_HSH                  (0x011A5030)

  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_3_OFF                  (14)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_3_WID                  ( 1)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_3_MSK                  (0x00004000)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_3_MIN                  (0)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_3_MAX                  (1) // 0x00000001
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_3_DEF                  (0x00000000)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_3_HSH                  (0x011C5030)

  #define MC0_MC_INIT_STATE_G_dclk_enable_OFF                          (22)
  #define MC0_MC_INIT_STATE_G_dclk_enable_WID                          ( 1)
  #define MC0_MC_INIT_STATE_G_dclk_enable_MSK                          (0x00400000)
  #define MC0_MC_INIT_STATE_G_dclk_enable_MIN                          (0)
  #define MC0_MC_INIT_STATE_G_dclk_enable_MAX                          (1) // 0x00000001
  #define MC0_MC_INIT_STATE_G_dclk_enable_DEF                          (0x00000000)
  #define MC0_MC_INIT_STATE_G_dclk_enable_HSH                          (0x012C5030)

  #define MC0_MC_INIT_STATE_G_override_sr_enable_OFF                   (24)
  #define MC0_MC_INIT_STATE_G_override_sr_enable_WID                   ( 1)
  #define MC0_MC_INIT_STATE_G_override_sr_enable_MSK                   (0x01000000)
  #define MC0_MC_INIT_STATE_G_override_sr_enable_MIN                   (0)
  #define MC0_MC_INIT_STATE_G_override_sr_enable_MAX                   (1) // 0x00000001
  #define MC0_MC_INIT_STATE_G_override_sr_enable_DEF                   (0x00000000)
  #define MC0_MC_INIT_STATE_G_override_sr_enable_HSH                   (0x01305030)

  #define MC0_MC_INIT_STATE_G_override_sr_enable_value_OFF             (25)
  #define MC0_MC_INIT_STATE_G_override_sr_enable_value_WID             ( 1)
  #define MC0_MC_INIT_STATE_G_override_sr_enable_value_MSK             (0x02000000)
  #define MC0_MC_INIT_STATE_G_override_sr_enable_value_MIN             (0)
  #define MC0_MC_INIT_STATE_G_override_sr_enable_value_MAX             (1) // 0x00000001
  #define MC0_MC_INIT_STATE_G_override_sr_enable_value_DEF             (0x00000000)
  #define MC0_MC_INIT_STATE_G_override_sr_enable_value_HSH             (0x01325030)

#define MC0_MRC_REVISION_REG                                           (0x00005034)

  #define MC0_MRC_REVISION_REVISION_OFF                                ( 0)
  #define MC0_MRC_REVISION_REVISION_WID                                (32)
  #define MC0_MRC_REVISION_REVISION_MSK                                (0xFFFFFFFF)
  #define MC0_MRC_REVISION_REVISION_MIN                                (0)
  #define MC0_MRC_REVISION_REVISION_MAX                                (4294967295) // 0xFFFFFFFF
  #define MC0_MRC_REVISION_REVISION_DEF                                (0x00000000)
  #define MC0_MRC_REVISION_REVISION_HSH                                (0x20005034)

#define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_REG                       (0x0000503C)

  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID0_OFF      ( 0)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID0_WID      ( 5)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID0_MSK      (0x0000001F)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID0_MIN      (0)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID0_MAX      (31) // 0x0000001F
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID0_DEF      (0x00000000)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID0_HSH      (0x0500503C)

  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID1_OFF      ( 5)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID1_WID      ( 5)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID1_MSK      (0x000003E0)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID1_MIN      (0)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID1_MAX      (31) // 0x0000001F
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID1_DEF      (0x00000001)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID1_HSH      (0x050A503C)

  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID2_OFF      (10)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID2_WID      ( 5)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID2_MSK      (0x00007C00)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID2_MIN      (0)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID2_MAX      (31) // 0x0000001F
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID2_DEF      (0x00000002)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID2_HSH      (0x0514503C)

  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID3_OFF      (15)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID3_WID      ( 5)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID3_MSK      (0x000F8000)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID3_MIN      (0)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID3_MAX      (31) // 0x0000001F
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID3_DEF      (0x00000002)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID3_HSH      (0x051E503C)

#define MC0_PWM_TOTAL_REQCOUNT_REG                                     (0x00005040)

  #define MC0_PWM_TOTAL_REQCOUNT_count_OFF                             ( 0)
  #define MC0_PWM_TOTAL_REQCOUNT_count_WID                             (64)
  #define MC0_PWM_TOTAL_REQCOUNT_count_MSK                             (0xFFFFFFFFFFFFFFFFULL)
  #define MC0_PWM_TOTAL_REQCOUNT_count_MIN                             (0)
  #define MC0_PWM_TOTAL_REQCOUNT_count_MAX                             (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define MC0_PWM_TOTAL_REQCOUNT_count_DEF                             (0x00000000)
  #define MC0_PWM_TOTAL_REQCOUNT_count_HSH                             (0x40005040)

#define MC0_PWM_TOTAL_REQCOUNT_A0_REG                                  (0x00005040)

  #define MC0_PWM_TOTAL_REQCOUNT_count_A0_OFF                          ( 0)
  #define MC0_PWM_TOTAL_REQCOUNT_count_A0_WID                          (32)
  #define MC0_PWM_TOTAL_REQCOUNT_count_A0_MSK                          (0xFFFFFFFF)
  #define MC0_PWM_TOTAL_REQCOUNT_count_A0_MIN                          (0)
  #define MC0_PWM_TOTAL_REQCOUNT_count_A0_MAX                          (4294967295) // 0xFFFFFFFF
  #define MC0_PWM_TOTAL_REQCOUNT_count_A0_DEF                          (0x00000000)
  #define MC0_PWM_TOTAL_REQCOUNT_count_A0_HSH                          (0x20005040)

#define MC0_PWM_PROGRAMMABLE_REQCOUNT_0_REG                            (0x00005048)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_REG

#define MC0_PWM_PROGRAMMABLE_REQCOUNT_0_A0_REG                         (0x00005048)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_A0_REG

#define MC0_PWM_PROGRAMMABLE_REQCOUNT_1_A0_REG                         (0x0000504C)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_A0_REG

#define MC0_PWM_PROGRAMMABLE_REQCOUNT_1_REG                            (0x00005050)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_REG

#define MC0_PWM_RDCAS_COUNT_REG                                        (0x00005058)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_REG

#define MC0_PWM_RDCAS_COUNT_A0_REG                                     (0x00005058)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_A0_REG

#define MC0_PM_SREF_CONFIG_REG                                         (0x00005060)

  #define MC0_PM_SREF_CONFIG_Idle_timer_OFF                            ( 0)
  #define MC0_PM_SREF_CONFIG_Idle_timer_WID                            (16)
  #define MC0_PM_SREF_CONFIG_Idle_timer_MSK                            (0x0000FFFF)
  #define MC0_PM_SREF_CONFIG_Idle_timer_MIN                            (0)
  #define MC0_PM_SREF_CONFIG_Idle_timer_MAX                            (65535) // 0x0000FFFF
  #define MC0_PM_SREF_CONFIG_Idle_timer_DEF                            (0x00000200)
  #define MC0_PM_SREF_CONFIG_Idle_timer_HSH                            (0x10005060)

  #define MC0_PM_SREF_CONFIG_SR_Enable_OFF                             (16)
  #define MC0_PM_SREF_CONFIG_SR_Enable_WID                             ( 1)
  #define MC0_PM_SREF_CONFIG_SR_Enable_MSK                             (0x00010000)
  #define MC0_PM_SREF_CONFIG_SR_Enable_MIN                             (0)
  #define MC0_PM_SREF_CONFIG_SR_Enable_MAX                             (1) // 0x00000001
  #define MC0_PM_SREF_CONFIG_SR_Enable_DEF                             (0x00000001)
  #define MC0_PM_SREF_CONFIG_SR_Enable_HSH                             (0x01205060)

  #define MC0_PM_SREF_CONFIG_delay_qsync_OFF                           (17)
  #define MC0_PM_SREF_CONFIG_delay_qsync_WID                           ( 2)
  #define MC0_PM_SREF_CONFIG_delay_qsync_MSK                           (0x00060000)
  #define MC0_PM_SREF_CONFIG_delay_qsync_MIN                           (0)
  #define MC0_PM_SREF_CONFIG_delay_qsync_MAX                           (3) // 0x00000003
  #define MC0_PM_SREF_CONFIG_delay_qsync_DEF                           (0x00000000)
  #define MC0_PM_SREF_CONFIG_delay_qsync_HSH                           (0x02225060)

#define MC0_ATMC_STS_REG                                               (0x00005064)

  #define MC0_ATMC_STS_VC1_WR_CNFLT_OFF                                ( 0)
  #define MC0_ATMC_STS_VC1_WR_CNFLT_WID                                ( 1)
  #define MC0_ATMC_STS_VC1_WR_CNFLT_MSK                                (0x00000001)
  #define MC0_ATMC_STS_VC1_WR_CNFLT_MIN                                (0)
  #define MC0_ATMC_STS_VC1_WR_CNFLT_MAX                                (1) // 0x00000001
  #define MC0_ATMC_STS_VC1_WR_CNFLT_DEF                                (0x00000000)
  #define MC0_ATMC_STS_VC1_WR_CNFLT_HSH                                (0x01005064)

  #define MC0_ATMC_STS_VC1_RD_CNFLT_OFF                                ( 1)
  #define MC0_ATMC_STS_VC1_RD_CNFLT_WID                                ( 1)
  #define MC0_ATMC_STS_VC1_RD_CNFLT_MSK                                (0x00000002)
  #define MC0_ATMC_STS_VC1_RD_CNFLT_MIN                                (0)
  #define MC0_ATMC_STS_VC1_RD_CNFLT_MAX                                (1) // 0x00000001
  #define MC0_ATMC_STS_VC1_RD_CNFLT_DEF                                (0x00000000)
  #define MC0_ATMC_STS_VC1_RD_CNFLT_HSH                                (0x01025064)

#define MC0_READ_OCCUPANCY_COUNT_REG                                   (0x00005068)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_REG

#define MC0_READ_OCCUPANCY_COUNT_A0_REG                                (0x00005068)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_A0_REG

#define MC0_STALL_DRAIN_REG                                            (0x00005074)

  #define MC0_STALL_DRAIN_stall_until_drain_OFF                        ( 0)
  #define MC0_STALL_DRAIN_stall_until_drain_WID                        ( 1)
  #define MC0_STALL_DRAIN_stall_until_drain_MSK                        (0x00000001)
  #define MC0_STALL_DRAIN_stall_until_drain_MIN                        (0)
  #define MC0_STALL_DRAIN_stall_until_drain_MAX                        (1) // 0x00000001
  #define MC0_STALL_DRAIN_stall_until_drain_DEF                        (0x00000000)
  #define MC0_STALL_DRAIN_stall_until_drain_HSH                        (0x01005074)

  #define MC0_STALL_DRAIN_stall_input_OFF                              ( 1)
  #define MC0_STALL_DRAIN_stall_input_WID                              ( 1)
  #define MC0_STALL_DRAIN_stall_input_MSK                              (0x00000002)
  #define MC0_STALL_DRAIN_stall_input_MIN                              (0)
  #define MC0_STALL_DRAIN_stall_input_MAX                              (1) // 0x00000001
  #define MC0_STALL_DRAIN_stall_input_DEF                              (0x00000000)
  #define MC0_STALL_DRAIN_stall_input_HSH                              (0x01025074)

  #define MC0_STALL_DRAIN_mc_drained_OFF                               ( 4)
  #define MC0_STALL_DRAIN_mc_drained_WID                               ( 1)
  #define MC0_STALL_DRAIN_mc_drained_MSK                               (0x00000010)
  #define MC0_STALL_DRAIN_mc_drained_MIN                               (0)
  #define MC0_STALL_DRAIN_mc_drained_MAX                               (1) // 0x00000001
  #define MC0_STALL_DRAIN_mc_drained_DEF                               (0x00000000)
  #define MC0_STALL_DRAIN_mc_drained_HSH                               (0x01085074)

  #define MC0_STALL_DRAIN_sr_state_OFF                                 ( 8)
  #define MC0_STALL_DRAIN_sr_state_WID                                 ( 1)
  #define MC0_STALL_DRAIN_sr_state_MSK                                 (0x00000100)
  #define MC0_STALL_DRAIN_sr_state_MIN                                 (0)
  #define MC0_STALL_DRAIN_sr_state_MAX                                 (1) // 0x00000001
  #define MC0_STALL_DRAIN_sr_state_DEF                                 (0x00000000)
  #define MC0_STALL_DRAIN_sr_state_HSH                                 (0x01105074)

  #define MC0_STALL_DRAIN_stall_state_OFF                              (12)
  #define MC0_STALL_DRAIN_stall_state_WID                              ( 1)
  #define MC0_STALL_DRAIN_stall_state_MSK                              (0x00001000)
  #define MC0_STALL_DRAIN_stall_state_MIN                              (0)
  #define MC0_STALL_DRAIN_stall_state_MAX                              (1) // 0x00000001
  #define MC0_STALL_DRAIN_stall_state_DEF                              (0x00000000)
  #define MC0_STALL_DRAIN_stall_state_HSH                              (0x01185074)

#define MC0_IPC_MC_ARB_REG                                             (0x00005078)

  #define MC0_IPC_MC_ARB_NonVC1Threshold_OFF                           ( 0)
  #define MC0_IPC_MC_ARB_NonVC1Threshold_WID                           ( 4)
  #define MC0_IPC_MC_ARB_NonVC1Threshold_MSK                           (0x0000000F)
  #define MC0_IPC_MC_ARB_NonVC1Threshold_MIN                           (0)
  #define MC0_IPC_MC_ARB_NonVC1Threshold_MAX                           (15) // 0x0000000F
  #define MC0_IPC_MC_ARB_NonVC1Threshold_DEF                           (0x00000004)
  #define MC0_IPC_MC_ARB_NonVC1Threshold_HSH                           (0x04005078)

  #define MC0_IPC_MC_ARB_VC1RdThreshold_OFF                            ( 4)
  #define MC0_IPC_MC_ARB_VC1RdThreshold_WID                            ( 4)
  #define MC0_IPC_MC_ARB_VC1RdThreshold_MSK                            (0x000000F0)
  #define MC0_IPC_MC_ARB_VC1RdThreshold_MIN                            (0)
  #define MC0_IPC_MC_ARB_VC1RdThreshold_MAX                            (15) // 0x0000000F
  #define MC0_IPC_MC_ARB_VC1RdThreshold_DEF                            (0x00000004)
  #define MC0_IPC_MC_ARB_VC1RdThreshold_HSH                            (0x04085078)

  #define MC0_IPC_MC_ARB_FixedRateEn_OFF                               ( 8)
  #define MC0_IPC_MC_ARB_FixedRateEn_WID                               ( 1)
  #define MC0_IPC_MC_ARB_FixedRateEn_MSK                               (0x00000100)
  #define MC0_IPC_MC_ARB_FixedRateEn_MIN                               (0)
  #define MC0_IPC_MC_ARB_FixedRateEn_MAX                               (1) // 0x00000001
  #define MC0_IPC_MC_ARB_FixedRateEn_DEF                               (0x00000000)
  #define MC0_IPC_MC_ARB_FixedRateEn_HSH                               (0x01105078)

  #define MC0_IPC_MC_ARB_HIGH_PRIO_LIM_OFF                             ( 9)
  #define MC0_IPC_MC_ARB_HIGH_PRIO_LIM_WID                             ( 3)
  #define MC0_IPC_MC_ARB_HIGH_PRIO_LIM_MSK                             (0x00000E00)
  #define MC0_IPC_MC_ARB_HIGH_PRIO_LIM_MIN                             (0)
  #define MC0_IPC_MC_ARB_HIGH_PRIO_LIM_MAX                             (7) // 0x00000007
  #define MC0_IPC_MC_ARB_HIGH_PRIO_LIM_DEF                             (0x00000004)
  #define MC0_IPC_MC_ARB_HIGH_PRIO_LIM_HSH                             (0x03125078)

  #define MC0_IPC_MC_ARB_LOW_PRIO_LIM_OFF                              (12)
  #define MC0_IPC_MC_ARB_LOW_PRIO_LIM_WID                              ( 3)
  #define MC0_IPC_MC_ARB_LOW_PRIO_LIM_MSK                              (0x00007000)
  #define MC0_IPC_MC_ARB_LOW_PRIO_LIM_MIN                              (0)
  #define MC0_IPC_MC_ARB_LOW_PRIO_LIM_MAX                              (7) // 0x00000007
  #define MC0_IPC_MC_ARB_LOW_PRIO_LIM_DEF                              (0x00000001)
  #define MC0_IPC_MC_ARB_LOW_PRIO_LIM_HSH                              (0x03185078)

  #define MC0_IPC_MC_ARB_spare_OFF                                     (15)
  #define MC0_IPC_MC_ARB_spare_WID                                     ( 8)
  #define MC0_IPC_MC_ARB_spare_MSK                                     (0x007F8000)
  #define MC0_IPC_MC_ARB_spare_MIN                                     (0)
  #define MC0_IPC_MC_ARB_spare_MAX                                     (255) // 0x000000FF
  #define MC0_IPC_MC_ARB_spare_DEF                                     (0x00000000)
  #define MC0_IPC_MC_ARB_spare_HSH                                     (0x081E5078)

#define MC0_IPC_MC_DEC_ARB_REG                                         (0x0000507C)
//Duplicate of MC0_IPC_MC_ARB_REG

#define MC0_QUEUE_CREDIT_C_REG                                         (0x00005080)

  #define MC0_QUEUE_CREDIT_C_RPQ_count_OFF                             ( 0)
  #define MC0_QUEUE_CREDIT_C_RPQ_count_WID                             ( 6)
  #define MC0_QUEUE_CREDIT_C_RPQ_count_MSK                             (0x0000003F)
  #define MC0_QUEUE_CREDIT_C_RPQ_count_MIN                             (0)
  #define MC0_QUEUE_CREDIT_C_RPQ_count_MAX                             (63) // 0x0000003F
  #define MC0_QUEUE_CREDIT_C_RPQ_count_DEF                             (0x00000020)
  #define MC0_QUEUE_CREDIT_C_RPQ_count_HSH                             (0x06005080)

  #define MC0_QUEUE_CREDIT_C_WPQ_count_OFF                             ( 8)
  #define MC0_QUEUE_CREDIT_C_WPQ_count_WID                             ( 7)
  #define MC0_QUEUE_CREDIT_C_WPQ_count_MSK                             (0x00007F00)
  #define MC0_QUEUE_CREDIT_C_WPQ_count_MIN                             (0)
  #define MC0_QUEUE_CREDIT_C_WPQ_count_MAX                             (127) // 0x0000007F
  #define MC0_QUEUE_CREDIT_C_WPQ_count_DEF                             (0x00000040)
  #define MC0_QUEUE_CREDIT_C_WPQ_count_HSH                             (0x07105080)

  #define MC0_QUEUE_CREDIT_C_IPQ_count_OFF                             (16)
  #define MC0_QUEUE_CREDIT_C_IPQ_count_WID                             ( 5)
  #define MC0_QUEUE_CREDIT_C_IPQ_count_MSK                             (0x001F0000)
  #define MC0_QUEUE_CREDIT_C_IPQ_count_MIN                             (0)
  #define MC0_QUEUE_CREDIT_C_IPQ_count_MAX                             (31) // 0x0000001F
  #define MC0_QUEUE_CREDIT_C_IPQ_count_DEF                             (0x00000010)
  #define MC0_QUEUE_CREDIT_C_IPQ_count_HSH                             (0x05205080)

  #define MC0_QUEUE_CREDIT_C_WPQ_MinSlotsToReq_OFF                     (21)
  #define MC0_QUEUE_CREDIT_C_WPQ_MinSlotsToReq_WID                     ( 4)
  #define MC0_QUEUE_CREDIT_C_WPQ_MinSlotsToReq_MSK                     (0x01E00000)
  #define MC0_QUEUE_CREDIT_C_WPQ_MinSlotsToReq_MIN                     (0)
  #define MC0_QUEUE_CREDIT_C_WPQ_MinSlotsToReq_MAX                     (15) // 0x0000000F
  #define MC0_QUEUE_CREDIT_C_WPQ_MinSlotsToReq_DEF                     (0x00000002)
  #define MC0_QUEUE_CREDIT_C_WPQ_MinSlotsToReq_HSH                     (0x042A5080)

  #define MC0_QUEUE_CREDIT_C_IPQ_MinSlotsToReq_OFF                     (25)
  #define MC0_QUEUE_CREDIT_C_IPQ_MinSlotsToReq_WID                     ( 3)
  #define MC0_QUEUE_CREDIT_C_IPQ_MinSlotsToReq_MSK                     (0x0E000000)
  #define MC0_QUEUE_CREDIT_C_IPQ_MinSlotsToReq_MIN                     (0)
  #define MC0_QUEUE_CREDIT_C_IPQ_MinSlotsToReq_MAX                     (7) // 0x00000007
  #define MC0_QUEUE_CREDIT_C_IPQ_MinSlotsToReq_DEF                     (0x00000002)
  #define MC0_QUEUE_CREDIT_C_IPQ_MinSlotsToReq_HSH                     (0x03325080)

  #define MC0_QUEUE_CREDIT_C_RPQ_MinSlotsToReq_OFF                     (28)
  #define MC0_QUEUE_CREDIT_C_RPQ_MinSlotsToReq_WID                     ( 4)
  #define MC0_QUEUE_CREDIT_C_RPQ_MinSlotsToReq_MSK                     (0xF0000000)
  #define MC0_QUEUE_CREDIT_C_RPQ_MinSlotsToReq_MIN                     (0)
  #define MC0_QUEUE_CREDIT_C_RPQ_MinSlotsToReq_MAX                     (15) // 0x0000000F
  #define MC0_QUEUE_CREDIT_C_RPQ_MinSlotsToReq_DEF                     (0x00000002)
  #define MC0_QUEUE_CREDIT_C_RPQ_MinSlotsToReq_HSH                     (0x04385080)

#define MC0_ECC_INJ_ADDR_COMPARE_REG                                   (0x00005088)

  #define MC0_ECC_INJ_ADDR_COMPARE_Address_OFF                         ( 0)
  #define MC0_ECC_INJ_ADDR_COMPARE_Address_WID                         (33)
  #define MC0_ECC_INJ_ADDR_COMPARE_Address_MSK                         (0x00000001FFFFFFFFULL)
  #define MC0_ECC_INJ_ADDR_COMPARE_Address_MIN                         (0)
  #define MC0_ECC_INJ_ADDR_COMPARE_Address_MAX                         (8589934591ULL) // 0x1FFFFFFFF
  #define MC0_ECC_INJ_ADDR_COMPARE_Address_DEF                         (0x00000000)
  #define MC0_ECC_INJ_ADDR_COMPARE_Address_HSH                         (0x61005088)

#define MC0_REMAPBASE_REG                                              (0x00005090)

  #define MC0_REMAPBASE_REMAPBASE_OFF                                  (20)
  #define MC0_REMAPBASE_REMAPBASE_WID                                  (19)
  #define MC0_REMAPBASE_REMAPBASE_MSK                                  (0x0000007FFFF00000ULL)
  #define MC0_REMAPBASE_REMAPBASE_MIN                                  (0)
  #define MC0_REMAPBASE_REMAPBASE_MAX                                  (524287) // 0x0007FFFF
  #define MC0_REMAPBASE_REMAPBASE_DEF                                  (0x0007FFFF)
  #define MC0_REMAPBASE_REMAPBASE_HSH                                  (0x53285090)

#define MC0_REMAPLIMIT_REG                                             (0x00005098)

  #define MC0_REMAPLIMIT_REMAPLMT_OFF                                  (20)
  #define MC0_REMAPLIMIT_REMAPLMT_WID                                  (19)
  #define MC0_REMAPLIMIT_REMAPLMT_MSK                                  (0x0000007FFFF00000ULL)
  #define MC0_REMAPLIMIT_REMAPLMT_MIN                                  (0)
  #define MC0_REMAPLIMIT_REMAPLMT_MAX                                  (524287) // 0x0007FFFF
  #define MC0_REMAPLIMIT_REMAPLMT_DEF                                  (0x00000000)
  #define MC0_REMAPLIMIT_REMAPLMT_HSH                                  (0x53285098)

#define MC0_PWM_WRCAS_COUNT_REG                                        (0x000050A0)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_REG

#define MC0_PWM_WRCAS_COUNT_A0_REG                                     (0x000050A0)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_A0_REG

#define MC0_PWM_COMMAND_COUNT_REG                                      (0x000050A8)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_REG

#define MC0_PWM_COMMAND_COUNT_A0_REG                                   (0x000050A8)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_A0_REG

#define MC0_PWM_NON_SR_COUNT_REG                                       (0x000050B0)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_REG

#define MC0_PWM_NON_SR_COUNT_A0_REG                                    (0x000050B0)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_A0_REG

#define MC0_TOLUD_REG                                                  (0x000050BC)

  #define MC0_TOLUD_TOLUD_OFF                                          (20)
  #define MC0_TOLUD_TOLUD_WID                                          (12)
  #define MC0_TOLUD_TOLUD_MSK                                          (0xFFF00000)
  #define MC0_TOLUD_TOLUD_MIN                                          (0)
  #define MC0_TOLUD_TOLUD_MAX                                          (4095) // 0x00000FFF
  #define MC0_TOLUD_TOLUD_DEF                                          (0x00000001)
  #define MC0_TOLUD_TOLUD_HSH                                          (0x0C2850BC)

#define MC0_PWM_GLB_DRV_OFF_COUNT_REG                                  (0x000050C0)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_REG

#define MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_REG                         (0x00005100)

  #define MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_sys_addr_OFF              ( 0)
  #define MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_sys_addr_WID              (33)
  #define MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_sys_addr_MSK              (0x00000001FFFFFFFFULL)
  #define MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_sys_addr_MIN              (0)
  #define MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_sys_addr_MAX              (8589934591ULL) // 0x1FFFFFFFF
  #define MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_sys_addr_DEF              (0x00000000)
  #define MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_sys_addr_HSH              (0x61005100)

#define MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_1_REG                         (0x00005108)
//Duplicate of MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_REG

#define MC0_GDXC_DDR_SYS_ADD_FILTER_MATCH_0_REG                        (0x00005110)
//Duplicate of MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_REG

#define MC0_GDXC_DDR_SYS_ADD_FILTER_MATCH_1_REG                        (0x00005118)
//Duplicate of MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_REG

#define MC0_GDXC_DDR_SYS_ADD_TRIGGER_MASK_REG                          (0x00005120)
//Duplicate of MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_REG

#define MC0_GDXC_DDR_SYS_ADD_TRIGGER_MATCH_REG                         (0x00005128)
//Duplicate of MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_REG

#define MC0_SC_QOS_REG                                                 (0x00005130)

  #define MC0_SC_QOS_Isoch_time_window_OFF                             ( 0)
  #define MC0_SC_QOS_Isoch_time_window_WID                             (17)
  #define MC0_SC_QOS_Isoch_time_window_MSK                             (0x0001FFFF)
  #define MC0_SC_QOS_Isoch_time_window_MIN                             (0)
  #define MC0_SC_QOS_Isoch_time_window_MAX                             (131071) // 0x0001FFFF
  #define MC0_SC_QOS_Isoch_time_window_DEF                             (0x000001C2)
  #define MC0_SC_QOS_Isoch_time_window_HSH                             (0x51005130)

  #define MC0_SC_QOS_Write_starvation_window_OFF                       (17)
  #define MC0_SC_QOS_Write_starvation_window_WID                       (11)
  #define MC0_SC_QOS_Write_starvation_window_MSK                       (0x0FFE0000)
  #define MC0_SC_QOS_Write_starvation_window_MIN                       (0)
  #define MC0_SC_QOS_Write_starvation_window_MAX                       (2047) // 0x000007FF
  #define MC0_SC_QOS_Write_starvation_window_DEF                       (0x0000005A)
  #define MC0_SC_QOS_Write_starvation_window_HSH                       (0x4B225130)

  #define MC0_SC_QOS_VC1_Read_starvation_en_OFF                        (28)
  #define MC0_SC_QOS_VC1_Read_starvation_en_WID                        ( 1)
  #define MC0_SC_QOS_VC1_Read_starvation_en_MSK                        (0x10000000)
  #define MC0_SC_QOS_VC1_Read_starvation_en_MIN                        (0)
  #define MC0_SC_QOS_VC1_Read_starvation_en_MAX                        (1) // 0x00000001
  #define MC0_SC_QOS_VC1_Read_starvation_en_DEF                        (0x00000001)
  #define MC0_SC_QOS_VC1_Read_starvation_en_HSH                        (0x41385130)

  #define MC0_SC_QOS_Write_starvation_in_Isoc_en_OFF                   (29)
  #define MC0_SC_QOS_Write_starvation_in_Isoc_en_WID                   ( 1)
  #define MC0_SC_QOS_Write_starvation_in_Isoc_en_MSK                   (0x20000000)
  #define MC0_SC_QOS_Write_starvation_in_Isoc_en_MIN                   (0)
  #define MC0_SC_QOS_Write_starvation_in_Isoc_en_MAX                   (1) // 0x00000001
  #define MC0_SC_QOS_Write_starvation_in_Isoc_en_DEF                   (0x00000001)
  #define MC0_SC_QOS_Write_starvation_in_Isoc_en_HSH                   (0x413A5130)

  #define MC0_SC_QOS_Read_starvation_in_Isoch_en_OFF                   (30)
  #define MC0_SC_QOS_Read_starvation_in_Isoch_en_WID                   ( 1)
  #define MC0_SC_QOS_Read_starvation_in_Isoch_en_MSK                   (0x40000000)
  #define MC0_SC_QOS_Read_starvation_in_Isoch_en_MIN                   (0)
  #define MC0_SC_QOS_Read_starvation_in_Isoch_en_MAX                   (1) // 0x00000001
  #define MC0_SC_QOS_Read_starvation_in_Isoch_en_DEF                   (0x00000001)
  #define MC0_SC_QOS_Read_starvation_in_Isoch_en_HSH                   (0x413C5130)

  #define MC0_SC_QOS_VC0_counter_disable_OFF                           (31)
  #define MC0_SC_QOS_VC0_counter_disable_WID                           ( 1)
  #define MC0_SC_QOS_VC0_counter_disable_MSK                           (0x80000000)
  #define MC0_SC_QOS_VC0_counter_disable_MIN                           (0)
  #define MC0_SC_QOS_VC0_counter_disable_MAX                           (1) // 0x00000001
  #define MC0_SC_QOS_VC0_counter_disable_DEF                           (0x00000000)
  #define MC0_SC_QOS_VC0_counter_disable_HSH                           (0x413E5130)

  #define MC0_SC_QOS_Read_starvation_window_OFF                        (32)
  #define MC0_SC_QOS_Read_starvation_window_WID                        (11)
  #define MC0_SC_QOS_Read_starvation_window_MSK                        (0x000007FF00000000ULL)
  #define MC0_SC_QOS_Read_starvation_window_MIN                        (0)
  #define MC0_SC_QOS_Read_starvation_window_MAX                        (2047) // 0x000007FF
  #define MC0_SC_QOS_Read_starvation_window_DEF                        (0x0000005A)
  #define MC0_SC_QOS_Read_starvation_window_HSH                        (0x4B405130)

  #define MC0_SC_QOS_VC0_read_count_OFF                                (43)
  #define MC0_SC_QOS_VC0_read_count_WID                                ( 9)
  #define MC0_SC_QOS_VC0_read_count_MSK                                (0x000FF80000000000ULL)
  #define MC0_SC_QOS_VC0_read_count_MIN                                (0)
  #define MC0_SC_QOS_VC0_read_count_MAX                                (511) // 0x000001FF
  #define MC0_SC_QOS_VC0_read_count_DEF                                (0x00000016)
  #define MC0_SC_QOS_VC0_read_count_HSH                                (0x49565130)

  #define MC0_SC_QOS_Force_MCVC1Demote_OFF                             (52)
  #define MC0_SC_QOS_Force_MCVC1Demote_WID                             ( 1)
  #define MC0_SC_QOS_Force_MCVC1Demote_MSK                             (0x0010000000000000ULL)
  #define MC0_SC_QOS_Force_MCVC1Demote_MIN                             (0)
  #define MC0_SC_QOS_Force_MCVC1Demote_MAX                             (1) // 0x00000001
  #define MC0_SC_QOS_Force_MCVC1Demote_DEF                             (0x00000000)
  #define MC0_SC_QOS_Force_MCVC1Demote_HSH                             (0x41685130)

  #define MC0_SC_QOS_Disable_MCVC1Demote_OFF                           (53)
  #define MC0_SC_QOS_Disable_MCVC1Demote_WID                           ( 1)
  #define MC0_SC_QOS_Disable_MCVC1Demote_MSK                           (0x0020000000000000ULL)
  #define MC0_SC_QOS_Disable_MCVC1Demote_MIN                           (0)
  #define MC0_SC_QOS_Disable_MCVC1Demote_MAX                           (1) // 0x00000001
  #define MC0_SC_QOS_Disable_MCVC1Demote_DEF                           (0x00000000)
  #define MC0_SC_QOS_Disable_MCVC1Demote_HSH                           (0x416A5130)

  #define MC0_SC_QOS_MC_Ignore_VC1Demote_OFF                           (54)
  #define MC0_SC_QOS_MC_Ignore_VC1Demote_WID                           ( 1)
  #define MC0_SC_QOS_MC_Ignore_VC1Demote_MSK                           (0x0040000000000000ULL)
  #define MC0_SC_QOS_MC_Ignore_VC1Demote_MIN                           (0)
  #define MC0_SC_QOS_MC_Ignore_VC1Demote_MAX                           (1) // 0x00000001
  #define MC0_SC_QOS_MC_Ignore_VC1Demote_DEF                           (0x00000000)
  #define MC0_SC_QOS_MC_Ignore_VC1Demote_HSH                           (0x416C5130)

  #define MC0_SC_QOS_Ignore_RGBSync_OFF                                (55)
  #define MC0_SC_QOS_Ignore_RGBSync_WID                                ( 1)
  #define MC0_SC_QOS_Ignore_RGBSync_MSK                                (0x0080000000000000ULL)
  #define MC0_SC_QOS_Ignore_RGBSync_MIN                                (0)
  #define MC0_SC_QOS_Ignore_RGBSync_MAX                                (1) // 0x00000001
  #define MC0_SC_QOS_Ignore_RGBSync_DEF                                (0x00000000)
  #define MC0_SC_QOS_Ignore_RGBSync_HSH                                (0x416E5130)

  #define MC0_SC_QOS_Force_MC_WPriority_OFF                            (56)
  #define MC0_SC_QOS_Force_MC_WPriority_WID                            ( 1)
  #define MC0_SC_QOS_Force_MC_WPriority_MSK                            (0x0100000000000000ULL)
  #define MC0_SC_QOS_Force_MC_WPriority_MIN                            (0)
  #define MC0_SC_QOS_Force_MC_WPriority_MAX                            (1) // 0x00000001
  #define MC0_SC_QOS_Force_MC_WPriority_DEF                            (0x00000000)
  #define MC0_SC_QOS_Force_MC_WPriority_HSH                            (0x41705130)

  #define MC0_SC_QOS_Disable_MC_WPriority_OFF                          (57)
  #define MC0_SC_QOS_Disable_MC_WPriority_WID                          ( 1)
  #define MC0_SC_QOS_Disable_MC_WPriority_MSK                          (0x0200000000000000ULL)
  #define MC0_SC_QOS_Disable_MC_WPriority_MIN                          (0)
  #define MC0_SC_QOS_Disable_MC_WPriority_MAX                          (1) // 0x00000001
  #define MC0_SC_QOS_Disable_MC_WPriority_DEF                          (0x00000000)
  #define MC0_SC_QOS_Disable_MC_WPriority_HSH                          (0x41725130)

  #define MC0_SC_QOS_allow_cross_vc_blocking_OFF                       (58)
  #define MC0_SC_QOS_allow_cross_vc_blocking_WID                       ( 1)
  #define MC0_SC_QOS_allow_cross_vc_blocking_MSK                       (0x0400000000000000ULL)
  #define MC0_SC_QOS_allow_cross_vc_blocking_MIN                       (0)
  #define MC0_SC_QOS_allow_cross_vc_blocking_MAX                       (1) // 0x00000001
  #define MC0_SC_QOS_allow_cross_vc_blocking_DEF                       (0x00000001)
  #define MC0_SC_QOS_allow_cross_vc_blocking_HSH                       (0x41745130)

  #define MC0_SC_QOS_VC1_block_VC0_OFF                                 (59)
  #define MC0_SC_QOS_VC1_block_VC0_WID                                 ( 1)
  #define MC0_SC_QOS_VC1_block_VC0_MSK                                 (0x0800000000000000ULL)
  #define MC0_SC_QOS_VC1_block_VC0_MIN                                 (0)
  #define MC0_SC_QOS_VC1_block_VC0_MAX                                 (1) // 0x00000001
  #define MC0_SC_QOS_VC1_block_VC0_DEF                                 (0x00000000)
  #define MC0_SC_QOS_VC1_block_VC0_HSH                                 (0x41765130)

  #define MC0_SC_QOS_VC0_block_VC1_OFF                                 (60)
  #define MC0_SC_QOS_VC0_block_VC1_WID                                 ( 1)
  #define MC0_SC_QOS_VC0_block_VC1_MSK                                 (0x1000000000000000ULL)
  #define MC0_SC_QOS_VC0_block_VC1_MIN                                 (0)
  #define MC0_SC_QOS_VC0_block_VC1_MAX                                 (1) // 0x00000001
  #define MC0_SC_QOS_VC0_block_VC1_DEF                                 (0x00000000)
  #define MC0_SC_QOS_VC0_block_VC1_HSH                                 (0x41785130)

  #define MC0_SC_QOS_Delay_VC1_on_read_starvation_OFF                  (61)
  #define MC0_SC_QOS_Delay_VC1_on_read_starvation_WID                  ( 1)
  #define MC0_SC_QOS_Delay_VC1_on_read_starvation_MSK                  (0x2000000000000000ULL)
  #define MC0_SC_QOS_Delay_VC1_on_read_starvation_MIN                  (0)
  #define MC0_SC_QOS_Delay_VC1_on_read_starvation_MAX                  (1) // 0x00000001
  #define MC0_SC_QOS_Delay_VC1_on_read_starvation_DEF                  (0x00000000)
  #define MC0_SC_QOS_Delay_VC1_on_read_starvation_HSH                  (0x417A5130)

#define MC0_MCMAINS_GLOBAL_DRIVER_GATE_CFG_REG                         (0x00005138)
//Duplicate of MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_REG

#define MC0_PWM_COUNTERS_DURATION_REG                                  (0x00005148)
//Duplicate of MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_REG

#define MC0_PWM_COUNTERS_DURATION_A0_REG                               (0x0000514C)
//Duplicate of MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_A0_REG

#define MC0_MCDECS_SECOND_CBIT_REG                                     (0x00005154)

  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_enable_OFF              ( 0)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_enable_WID              ( 1)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_enable_MSK              (0x00000001)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_enable_MIN              (0)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_enable_MAX              (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_enable_DEF              (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_enable_HSH              (0x01005154)

  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_phase_OFF               ( 1)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_phase_WID               ( 1)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_phase_MSK               (0x00000002)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_phase_MIN               (0)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_phase_MAX               (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_phase_DEF               (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_phase_HSH               (0x01025154)

  #define MC0_MCDECS_SECOND_CBIT_block_scheduler_OFF                   ( 2)
  #define MC0_MCDECS_SECOND_CBIT_block_scheduler_WID                   ( 4)
  #define MC0_MCDECS_SECOND_CBIT_block_scheduler_MSK                   (0x0000003C)
  #define MC0_MCDECS_SECOND_CBIT_block_scheduler_MIN                   (0)
  #define MC0_MCDECS_SECOND_CBIT_block_scheduler_MAX                   (15) // 0x0000000F
  #define MC0_MCDECS_SECOND_CBIT_block_scheduler_DEF                   (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_block_scheduler_HSH                   (0x04045154)

  #define MC0_MCDECS_SECOND_CBIT_pwm_clock_enable_OFF                  ( 6)
  #define MC0_MCDECS_SECOND_CBIT_pwm_clock_enable_WID                  ( 1)
  #define MC0_MCDECS_SECOND_CBIT_pwm_clock_enable_MSK                  (0x00000040)
  #define MC0_MCDECS_SECOND_CBIT_pwm_clock_enable_MIN                  (0)
  #define MC0_MCDECS_SECOND_CBIT_pwm_clock_enable_MAX                  (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_pwm_clock_enable_DEF                  (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_pwm_clock_enable_HSH                  (0x010C5154)

  #define MC0_MCDECS_SECOND_CBIT_Mock_InSR_OFF                         ( 7)
  #define MC0_MCDECS_SECOND_CBIT_Mock_InSR_WID                         ( 1)
  #define MC0_MCDECS_SECOND_CBIT_Mock_InSR_MSK                         (0x00000080)
  #define MC0_MCDECS_SECOND_CBIT_Mock_InSR_MIN                         (0)
  #define MC0_MCDECS_SECOND_CBIT_Mock_InSR_MAX                         (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_Mock_InSR_DEF                         (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_Mock_InSR_HSH                         (0x010E5154)

  #define MC0_MCDECS_SECOND_CBIT_dis_other_mc_stolen_ref_OFF           ( 8)
  #define MC0_MCDECS_SECOND_CBIT_dis_other_mc_stolen_ref_WID           ( 1)
  #define MC0_MCDECS_SECOND_CBIT_dis_other_mc_stolen_ref_MSK           (0x00000100)
  #define MC0_MCDECS_SECOND_CBIT_dis_other_mc_stolen_ref_MIN           (0)
  #define MC0_MCDECS_SECOND_CBIT_dis_other_mc_stolen_ref_MAX           (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_dis_other_mc_stolen_ref_DEF           (0x00000001)
  #define MC0_MCDECS_SECOND_CBIT_dis_other_mc_stolen_ref_HSH           (0x01105154)

  #define MC0_MCDECS_SECOND_CBIT_allow_blockack_on_pending_srx_OFF     ( 9)
  #define MC0_MCDECS_SECOND_CBIT_allow_blockack_on_pending_srx_WID     ( 1)
  #define MC0_MCDECS_SECOND_CBIT_allow_blockack_on_pending_srx_MSK     (0x00000200)
  #define MC0_MCDECS_SECOND_CBIT_allow_blockack_on_pending_srx_MIN     (0)
  #define MC0_MCDECS_SECOND_CBIT_allow_blockack_on_pending_srx_MAX     (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_allow_blockack_on_pending_srx_DEF     (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_allow_blockack_on_pending_srx_HSH     (0x01125154)

  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ca_valid_dis_OFF        (10)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ca_valid_dis_WID        ( 1)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ca_valid_dis_MSK        (0x00000400)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ca_valid_dis_MIN        (0)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ca_valid_dis_MAX        (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ca_valid_dis_DEF        (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ca_valid_dis_HSH        (0x01145154)

  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ckstop_dis_OFF          (11)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ckstop_dis_WID          ( 1)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ckstop_dis_MSK          (0x00000800)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ckstop_dis_MIN          (0)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ckstop_dis_MAX          (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ckstop_dis_DEF          (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ckstop_dis_HSH          (0x01165154)

  #define MC0_MCDECS_SECOND_CBIT_dis_spid_cmd_clk_gate_OFF             (12)
  #define MC0_MCDECS_SECOND_CBIT_dis_spid_cmd_clk_gate_WID             ( 1)
  #define MC0_MCDECS_SECOND_CBIT_dis_spid_cmd_clk_gate_MSK             (0x00001000)
  #define MC0_MCDECS_SECOND_CBIT_dis_spid_cmd_clk_gate_MIN             (0)
  #define MC0_MCDECS_SECOND_CBIT_dis_spid_cmd_clk_gate_MAX             (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_dis_spid_cmd_clk_gate_DEF             (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_dis_spid_cmd_clk_gate_HSH             (0x01185154)

  #define MC0_MCDECS_SECOND_CBIT_init_complete_override_OFF            (16)
  #define MC0_MCDECS_SECOND_CBIT_init_complete_override_WID            ( 4)
  #define MC0_MCDECS_SECOND_CBIT_init_complete_override_MSK            (0x000F0000)
  #define MC0_MCDECS_SECOND_CBIT_init_complete_override_MIN            (0)
  #define MC0_MCDECS_SECOND_CBIT_init_complete_override_MAX            (15) // 0x0000000F
  #define MC0_MCDECS_SECOND_CBIT_init_complete_override_DEF            (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_init_complete_override_HSH            (0x04205154)

#define MC0_MCDECS_SECOND_CBIT_A0_REG                                  (0x00005154)

  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_enable_A0_OFF           ( 0)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_enable_A0_WID           ( 1)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_enable_A0_MSK           (0x00000001)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_enable_A0_MIN           (0)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_enable_A0_MAX           (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_enable_A0_DEF           (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_enable_A0_HSH           (0x01005154)

  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_phase_A0_OFF            ( 1)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_phase_A0_WID            ( 1)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_phase_A0_MSK            (0x00000002)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_phase_A0_MIN            (0)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_phase_A0_MAX            (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_phase_A0_DEF            (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_phase_A0_HSH            (0x01025154)

  #define MC0_MCDECS_SECOND_CBIT_block_scheduler_A0_OFF                ( 2)
  #define MC0_MCDECS_SECOND_CBIT_block_scheduler_A0_WID                ( 4)
  #define MC0_MCDECS_SECOND_CBIT_block_scheduler_A0_MSK                (0x0000003C)
  #define MC0_MCDECS_SECOND_CBIT_block_scheduler_A0_MIN                (0)
  #define MC0_MCDECS_SECOND_CBIT_block_scheduler_A0_MAX                (15) // 0x0000000F
  #define MC0_MCDECS_SECOND_CBIT_block_scheduler_A0_DEF                (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_block_scheduler_A0_HSH                (0x04045154)

  #define MC0_MCDECS_SECOND_CBIT_pwm_clock_enable_A0_OFF               ( 6)
  #define MC0_MCDECS_SECOND_CBIT_pwm_clock_enable_A0_WID               ( 1)
  #define MC0_MCDECS_SECOND_CBIT_pwm_clock_enable_A0_MSK               (0x00000040)
  #define MC0_MCDECS_SECOND_CBIT_pwm_clock_enable_A0_MIN               (0)
  #define MC0_MCDECS_SECOND_CBIT_pwm_clock_enable_A0_MAX               (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_pwm_clock_enable_A0_DEF               (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_pwm_clock_enable_A0_HSH               (0x010C5154)

  #define MC0_MCDECS_SECOND_CBIT_Mock_InSR_A0_OFF                      ( 7)
  #define MC0_MCDECS_SECOND_CBIT_Mock_InSR_A0_WID                      ( 1)
  #define MC0_MCDECS_SECOND_CBIT_Mock_InSR_A0_MSK                      (0x00000080)
  #define MC0_MCDECS_SECOND_CBIT_Mock_InSR_A0_MIN                      (0)
  #define MC0_MCDECS_SECOND_CBIT_Mock_InSR_A0_MAX                      (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_Mock_InSR_A0_DEF                      (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_Mock_InSR_A0_HSH                      (0x010E5154)

  #define MC0_MCDECS_SECOND_CBIT_dis_other_mc_stolen_ref_A0_OFF        ( 8)
  #define MC0_MCDECS_SECOND_CBIT_dis_other_mc_stolen_ref_A0_WID        ( 1)
  #define MC0_MCDECS_SECOND_CBIT_dis_other_mc_stolen_ref_A0_MSK        (0x00000100)
  #define MC0_MCDECS_SECOND_CBIT_dis_other_mc_stolen_ref_A0_MIN        (0)
  #define MC0_MCDECS_SECOND_CBIT_dis_other_mc_stolen_ref_A0_MAX        (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_dis_other_mc_stolen_ref_A0_DEF        (0x00000001)
  #define MC0_MCDECS_SECOND_CBIT_dis_other_mc_stolen_ref_A0_HSH        (0x01105154)

  #define MC0_MCDECS_SECOND_CBIT_allow_blockack_on_pending_srx_A0_OFF  ( 9)
  #define MC0_MCDECS_SECOND_CBIT_allow_blockack_on_pending_srx_A0_WID  ( 1)
  #define MC0_MCDECS_SECOND_CBIT_allow_blockack_on_pending_srx_A0_MSK  (0x00000200)
  #define MC0_MCDECS_SECOND_CBIT_allow_blockack_on_pending_srx_A0_MIN  (0)
  #define MC0_MCDECS_SECOND_CBIT_allow_blockack_on_pending_srx_A0_MAX  (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_allow_blockack_on_pending_srx_A0_DEF  (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_allow_blockack_on_pending_srx_A0_HSH  (0x01125154)

  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ca_valid_dis_A0_OFF     (10)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ca_valid_dis_A0_WID     ( 1)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ca_valid_dis_A0_MSK     (0x00000400)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ca_valid_dis_A0_MIN     (0)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ca_valid_dis_A0_MAX     (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ca_valid_dis_A0_DEF     (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ca_valid_dis_A0_HSH     (0x01145154)

  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ckstop_dis_A0_OFF       (11)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ckstop_dis_A0_WID       ( 1)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ckstop_dis_A0_MSK       (0x00000800)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ckstop_dis_A0_MIN       (0)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ckstop_dis_A0_MAX       (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ckstop_dis_A0_DEF       (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ckstop_dis_A0_HSH       (0x01165154)

  #define MC0_MCDECS_SECOND_CBIT_dis_spid_cmd_clk_gate_A0_OFF          (12)
  #define MC0_MCDECS_SECOND_CBIT_dis_spid_cmd_clk_gate_A0_WID          ( 1)
  #define MC0_MCDECS_SECOND_CBIT_dis_spid_cmd_clk_gate_A0_MSK          (0x00001000)
  #define MC0_MCDECS_SECOND_CBIT_dis_spid_cmd_clk_gate_A0_MIN          (0)
  #define MC0_MCDECS_SECOND_CBIT_dis_spid_cmd_clk_gate_A0_MAX          (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_dis_spid_cmd_clk_gate_A0_DEF          (0x00000001)
  #define MC0_MCDECS_SECOND_CBIT_dis_spid_cmd_clk_gate_A0_HSH          (0x01185154)

  #define MC0_MCDECS_SECOND_CBIT_init_complete_override_A0_OFF         (16)
  #define MC0_MCDECS_SECOND_CBIT_init_complete_override_A0_WID         ( 4)
  #define MC0_MCDECS_SECOND_CBIT_init_complete_override_A0_MSK         (0x000F0000)
  #define MC0_MCDECS_SECOND_CBIT_init_complete_override_A0_MIN         (0)
  #define MC0_MCDECS_SECOND_CBIT_init_complete_override_A0_MAX         (15) // 0x0000000F
  #define MC0_MCDECS_SECOND_CBIT_init_complete_override_A0_DEF         (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_init_complete_override_A0_HSH         (0x04205154)

#define MC0_ECC_INJ_ADDR_MASK_REG                                      (0x00005158)

  #define MC0_ECC_INJ_ADDR_MASK_Address_OFF                            ( 0)
  #define MC0_ECC_INJ_ADDR_MASK_Address_WID                            (33)
  #define MC0_ECC_INJ_ADDR_MASK_Address_MSK                            (0x00000001FFFFFFFFULL)
  #define MC0_ECC_INJ_ADDR_MASK_Address_MIN                            (0)
  #define MC0_ECC_INJ_ADDR_MASK_Address_MAX                            (8589934591ULL) // 0x1FFFFFFFF
  #define MC0_ECC_INJ_ADDR_MASK_Address_DEF                            (0x1FFFFFFFF)
  #define MC0_ECC_INJ_ADDR_MASK_Address_HSH                            (0x61005158)

#define MC0_SC_QOS2_REG                                                (0x00005160)

  #define MC0_SC_QOS2_RW_Isoch_time_window_OFF                         ( 0)
  #define MC0_SC_QOS2_RW_Isoch_time_window_WID                         (17)
  #define MC0_SC_QOS2_RW_Isoch_time_window_MSK                         (0x0001FFFF)
  #define MC0_SC_QOS2_RW_Isoch_time_window_MIN                         (0)
  #define MC0_SC_QOS2_RW_Isoch_time_window_MAX                         (131071) // 0x0001FFFF
  #define MC0_SC_QOS2_RW_Isoch_time_window_DEF                         (0x000000E1)
  #define MC0_SC_QOS2_RW_Isoch_time_window_HSH                         (0x51005160)

  #define MC0_SC_QOS2_RW_Write_starvation_window_OFF                   (17)
  #define MC0_SC_QOS2_RW_Write_starvation_window_WID                   (11)
  #define MC0_SC_QOS2_RW_Write_starvation_window_MSK                   (0x0FFE0000)
  #define MC0_SC_QOS2_RW_Write_starvation_window_MIN                   (0)
  #define MC0_SC_QOS2_RW_Write_starvation_window_MAX                   (2047) // 0x000007FF
  #define MC0_SC_QOS2_RW_Write_starvation_window_DEF                   (0x000001C2)
  #define MC0_SC_QOS2_RW_Write_starvation_window_HSH                   (0x4B225160)

  #define MC0_SC_QOS2_RW_Read_starvation_window_OFF                    (32)
  #define MC0_SC_QOS2_RW_Read_starvation_window_WID                    (11)
  #define MC0_SC_QOS2_RW_Read_starvation_window_MSK                    (0x000007FF00000000ULL)
  #define MC0_SC_QOS2_RW_Read_starvation_window_MIN                    (0)
  #define MC0_SC_QOS2_RW_Read_starvation_window_MAX                    (2047) // 0x000007FF
  #define MC0_SC_QOS2_RW_Read_starvation_window_DEF                    (0x0000005A)
  #define MC0_SC_QOS2_RW_Read_starvation_window_HSH                    (0x4B405160)

  #define MC0_SC_QOS2_Isoc_during_demote_period_x8_OFF                 (43)
  #define MC0_SC_QOS2_Isoc_during_demote_period_x8_WID                 ( 8)
  #define MC0_SC_QOS2_Isoc_during_demote_period_x8_MSK                 (0x0007F80000000000ULL)
  #define MC0_SC_QOS2_Isoc_during_demote_period_x8_MIN                 (0)
  #define MC0_SC_QOS2_Isoc_during_demote_period_x8_MAX                 (255) // 0x000000FF
  #define MC0_SC_QOS2_Isoc_during_demote_period_x8_DEF                 (0x00000080)
  #define MC0_SC_QOS2_Isoc_during_demote_period_x8_HSH                 (0x48565160)

  #define MC0_SC_QOS2_Isoc_during_demote_window_OFF                    (51)
  #define MC0_SC_QOS2_Isoc_during_demote_window_WID                    ( 8)
  #define MC0_SC_QOS2_Isoc_during_demote_window_MSK                    (0x07F8000000000000ULL)
  #define MC0_SC_QOS2_Isoc_during_demote_window_MIN                    (0)
  #define MC0_SC_QOS2_Isoc_during_demote_window_MAX                    (255) // 0x000000FF
  #define MC0_SC_QOS2_Isoc_during_demote_window_DEF                    (0x00000040)
  #define MC0_SC_QOS2_Isoc_during_demote_window_HSH                    (0x48665160)

#define MC0_SC_QOS3_REG                                                (0x00005168)

  #define MC0_SC_QOS3_Yellow_Decay_x128_OFF                            ( 0)
  #define MC0_SC_QOS3_Yellow_Decay_x128_WID                            ( 9)
  #define MC0_SC_QOS3_Yellow_Decay_x128_MSK                            (0x000001FF)
  #define MC0_SC_QOS3_Yellow_Decay_x128_MIN                            (0)
  #define MC0_SC_QOS3_Yellow_Decay_x128_MAX                            (511) // 0x000001FF
  #define MC0_SC_QOS3_Yellow_Decay_x128_DEF                            (0x0000007D)
  #define MC0_SC_QOS3_Yellow_Decay_x128_HSH                            (0x09005168)

  #define MC0_SC_QOS3_Yellow_Threshold_OFF                             ( 9)
  #define MC0_SC_QOS3_Yellow_Threshold_WID                             (10)
  #define MC0_SC_QOS3_Yellow_Threshold_MSK                             (0x0007FE00)
  #define MC0_SC_QOS3_Yellow_Threshold_MIN                             (0)
  #define MC0_SC_QOS3_Yellow_Threshold_MAX                             (1023) // 0x000003FF
  #define MC0_SC_QOS3_Yellow_Threshold_DEF                             (0x000000A0)
  #define MC0_SC_QOS3_Yellow_Threshold_HSH                             (0x0A125168)

#define MC0_NORMALMODE_CFG_REG                                         (0x0000516C)

  #define MC0_NORMALMODE_CFG_normalmode_OFF                            ( 0)
  #define MC0_NORMALMODE_CFG_normalmode_WID                            ( 1)
  #define MC0_NORMALMODE_CFG_normalmode_MSK                            (0x00000001)
  #define MC0_NORMALMODE_CFG_normalmode_MIN                            (0)
  #define MC0_NORMALMODE_CFG_normalmode_MAX                            (1) // 0x00000001
  #define MC0_NORMALMODE_CFG_normalmode_DEF                            (0x00000000)
  #define MC0_NORMALMODE_CFG_normalmode_HSH                            (0x0100516C)

#define MC0_MC_CPGC_CMI_REG                                            (0x00005170)

  #define MC0_MC_CPGC_CMI_CPGC_ACTIVE_OFF                              (24)
  #define MC0_MC_CPGC_CMI_CPGC_ACTIVE_WID                              ( 1)
  #define MC0_MC_CPGC_CMI_CPGC_ACTIVE_MSK                              (0x01000000)
  #define MC0_MC_CPGC_CMI_CPGC_ACTIVE_MIN                              (0)
  #define MC0_MC_CPGC_CMI_CPGC_ACTIVE_MAX                              (1) // 0x00000001
  #define MC0_MC_CPGC_CMI_CPGC_ACTIVE_DEF                              (0x00000000)
  #define MC0_MC_CPGC_CMI_CPGC_ACTIVE_HSH                              (0x01305170)

  #define MC0_MC_CPGC_CMI_CPGC_ECC_BYTE_OFF                            (28)
  #define MC0_MC_CPGC_CMI_CPGC_ECC_BYTE_WID                            ( 3)
  #define MC0_MC_CPGC_CMI_CPGC_ECC_BYTE_MSK                            (0x70000000)
  #define MC0_MC_CPGC_CMI_CPGC_ECC_BYTE_MIN                            (0)
  #define MC0_MC_CPGC_CMI_CPGC_ECC_BYTE_MAX                            (7) // 0x00000007
  #define MC0_MC_CPGC_CMI_CPGC_ECC_BYTE_DEF                            (0x00000000)
  #define MC0_MC_CPGC_CMI_CPGC_ECC_BYTE_HSH                            (0x03385170)

  #define MC0_MC_CPGC_CMI_Stall_CPGC_CMI_Req_OFF                       (31)
  #define MC0_MC_CPGC_CMI_Stall_CPGC_CMI_Req_WID                       ( 1)
  #define MC0_MC_CPGC_CMI_Stall_CPGC_CMI_Req_MSK                       (0x80000000)
  #define MC0_MC_CPGC_CMI_Stall_CPGC_CMI_Req_MIN                       (0)
  #define MC0_MC_CPGC_CMI_Stall_CPGC_CMI_Req_MAX                       (1) // 0x00000001
  #define MC0_MC_CPGC_CMI_Stall_CPGC_CMI_Req_DEF                       (0x00000000)
  #define MC0_MC_CPGC_CMI_Stall_CPGC_CMI_Req_HSH                       (0x013E5170)

#define MC0_MC_CPGC_MISC_DFT_REG                                       (0x00005174)

  #define MC0_MC_CPGC_MISC_DFT_Concat_Row2Col_OFF                      ( 0)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Row2Col_WID                      ( 1)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Row2Col_MSK                      (0x00000001)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Row2Col_MIN                      (0)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Row2Col_MAX                      (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_Concat_Row2Col_DEF                      (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Row2Col_HSH                      (0x01005174)

  #define MC0_MC_CPGC_MISC_DFT_Col_align_OFF                           ( 1)
  #define MC0_MC_CPGC_MISC_DFT_Col_align_WID                           ( 3)
  #define MC0_MC_CPGC_MISC_DFT_Col_align_MSK                           (0x0000000E)
  #define MC0_MC_CPGC_MISC_DFT_Col_align_MIN                           (0)
  #define MC0_MC_CPGC_MISC_DFT_Col_align_MAX                           (7) // 0x00000007
  #define MC0_MC_CPGC_MISC_DFT_Col_align_DEF                           (0x00000003)
  #define MC0_MC_CPGC_MISC_DFT_Col_align_HSH                           (0x03025174)

  #define MC0_MC_CPGC_MISC_DFT_Concat_Bank2Row_OFF                     ( 4)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Bank2Row_WID                     ( 1)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Bank2Row_MSK                     (0x00000010)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Bank2Row_MIN                     (0)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Bank2Row_MAX                     (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_Concat_Bank2Row_DEF                     (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Bank2Row_HSH                     (0x01085174)

  #define MC0_MC_CPGC_MISC_DFT_Concat_Col2Row_OFF                      ( 5)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Col2Row_WID                      ( 1)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Col2Row_MSK                      (0x00000020)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Col2Row_MIN                      (0)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Col2Row_MAX                      (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_Concat_Col2Row_DEF                      (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Col2Row_HSH                      (0x010A5174)

  #define MC0_MC_CPGC_MISC_DFT_Row_align_OFF                           ( 6)
  #define MC0_MC_CPGC_MISC_DFT_Row_align_WID                           ( 3)
  #define MC0_MC_CPGC_MISC_DFT_Row_align_MSK                           (0x000001C0)
  #define MC0_MC_CPGC_MISC_DFT_Row_align_MIN                           (0)
  #define MC0_MC_CPGC_MISC_DFT_Row_align_MAX                           (7) // 0x00000007
  #define MC0_MC_CPGC_MISC_DFT_Row_align_DEF                           (0x00000003)
  #define MC0_MC_CPGC_MISC_DFT_Row_align_HSH                           (0x030C5174)

  #define MC0_MC_CPGC_MISC_DFT_Concat_BG2Bank_OFF                      ( 9)
  #define MC0_MC_CPGC_MISC_DFT_Concat_BG2Bank_WID                      ( 1)
  #define MC0_MC_CPGC_MISC_DFT_Concat_BG2Bank_MSK                      (0x00000200)
  #define MC0_MC_CPGC_MISC_DFT_Concat_BG2Bank_MIN                      (0)
  #define MC0_MC_CPGC_MISC_DFT_Concat_BG2Bank_MAX                      (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_Concat_BG2Bank_DEF                      (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_Concat_BG2Bank_HSH                      (0x01125174)

  #define MC0_MC_CPGC_MISC_DFT_dis_BankGroup_OFF                       (10)
  #define MC0_MC_CPGC_MISC_DFT_dis_BankGroup_WID                       ( 1)
  #define MC0_MC_CPGC_MISC_DFT_dis_BankGroup_MSK                       (0x00000400)
  #define MC0_MC_CPGC_MISC_DFT_dis_BankGroup_MIN                       (0)
  #define MC0_MC_CPGC_MISC_DFT_dis_BankGroup_MAX                       (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_dis_BankGroup_DEF                       (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_dis_BankGroup_HSH                       (0x01145174)

  #define MC0_MC_CPGC_MISC_DFT_Rank_as_it_OFF                          (11)
  #define MC0_MC_CPGC_MISC_DFT_Rank_as_it_WID                          ( 1)
  #define MC0_MC_CPGC_MISC_DFT_Rank_as_it_MSK                          (0x00000800)
  #define MC0_MC_CPGC_MISC_DFT_Rank_as_it_MIN                          (0)
  #define MC0_MC_CPGC_MISC_DFT_Rank_as_it_MAX                          (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_Rank_as_it_DEF                          (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_Rank_as_it_HSH                          (0x01165174)

  #define MC0_MC_CPGC_MISC_DFT_channel_is_CID_Zero_OFF                 (12)
  #define MC0_MC_CPGC_MISC_DFT_channel_is_CID_Zero_WID                 ( 1)
  #define MC0_MC_CPGC_MISC_DFT_channel_is_CID_Zero_MSK                 (0x00001000)
  #define MC0_MC_CPGC_MISC_DFT_channel_is_CID_Zero_MIN                 (0)
  #define MC0_MC_CPGC_MISC_DFT_channel_is_CID_Zero_MAX                 (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_channel_is_CID_Zero_DEF                 (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_channel_is_CID_Zero_HSH                 (0x01185174)

  #define MC0_MC_CPGC_MISC_DFT_Inverse_channel_OFF                     (13)
  #define MC0_MC_CPGC_MISC_DFT_Inverse_channel_WID                     ( 1)
  #define MC0_MC_CPGC_MISC_DFT_Inverse_channel_MSK                     (0x00002000)
  #define MC0_MC_CPGC_MISC_DFT_Inverse_channel_MIN                     (0)
  #define MC0_MC_CPGC_MISC_DFT_Inverse_channel_MAX                     (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_Inverse_channel_DEF                     (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_Inverse_channel_HSH                     (0x011A5174)

  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_info_OFF                      (14)
  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_info_WID                      ( 1)
  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_info_MSK                      (0x00004000)
  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_info_MIN                      (0)
  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_info_MAX                      (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_info_DEF                      (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_info_HSH                      (0x011C5174)

  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_data_OFF                      (15)
  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_data_WID                      ( 1)
  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_data_MSK                      (0x00008000)
  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_data_MIN                      (0)
  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_data_MAX                      (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_data_DEF                      (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_data_HSH                      (0x011E5174)

  #define MC0_MC_CPGC_MISC_DFT_Reset_CPGC_OFF                          (16)
  #define MC0_MC_CPGC_MISC_DFT_Reset_CPGC_WID                          ( 1)
  #define MC0_MC_CPGC_MISC_DFT_Reset_CPGC_MSK                          (0x00010000)
  #define MC0_MC_CPGC_MISC_DFT_Reset_CPGC_MIN                          (0)
  #define MC0_MC_CPGC_MISC_DFT_Reset_CPGC_MAX                          (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_Reset_CPGC_DEF                          (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_Reset_CPGC_HSH                          (0x01205174)

  #define MC0_MC_CPGC_MISC_DFT_Lock_On_Active_CPGC_CMI_ISM_OFF         (17)
  #define MC0_MC_CPGC_MISC_DFT_Lock_On_Active_CPGC_CMI_ISM_WID         ( 1)
  #define MC0_MC_CPGC_MISC_DFT_Lock_On_Active_CPGC_CMI_ISM_MSK         (0x00020000)
  #define MC0_MC_CPGC_MISC_DFT_Lock_On_Active_CPGC_CMI_ISM_MIN         (0)
  #define MC0_MC_CPGC_MISC_DFT_Lock_On_Active_CPGC_CMI_ISM_MAX         (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_Lock_On_Active_CPGC_CMI_ISM_DEF         (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_Lock_On_Active_CPGC_CMI_ISM_HSH         (0x01225174)

  #define MC0_MC_CPGC_MISC_DFT_BG1_mask_OFF                            (18)
  #define MC0_MC_CPGC_MISC_DFT_BG1_mask_WID                            ( 1)
  #define MC0_MC_CPGC_MISC_DFT_BG1_mask_MSK                            (0x00040000)
  #define MC0_MC_CPGC_MISC_DFT_BG1_mask_MIN                            (0)
  #define MC0_MC_CPGC_MISC_DFT_BG1_mask_MAX                            (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_BG1_mask_DEF                            (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_BG1_mask_HSH                            (0x01245174)

  #define MC0_MC_CPGC_MISC_DFT_Rank1_as_ERM_BG1_OFF                    (19)
  #define MC0_MC_CPGC_MISC_DFT_Rank1_as_ERM_BG1_WID                    ( 1)
  #define MC0_MC_CPGC_MISC_DFT_Rank1_as_ERM_BG1_MSK                    (0x00080000)
  #define MC0_MC_CPGC_MISC_DFT_Rank1_as_ERM_BG1_MIN                    (0)
  #define MC0_MC_CPGC_MISC_DFT_Rank1_as_ERM_BG1_MAX                    (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_Rank1_as_ERM_BG1_DEF                    (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_Rank1_as_ERM_BG1_HSH                    (0x01265174)

#define MC0_PARITYERRLOG_REG                                           (0x000051A0)

  #define MC0_PARITYERRLOG_ERR_ADDRESS_OFF                             ( 0)
  #define MC0_PARITYERRLOG_ERR_ADDRESS_WID                             (39)
  #define MC0_PARITYERRLOG_ERR_ADDRESS_MSK                             (0x0000007FFFFFFFFFULL)
  #define MC0_PARITYERRLOG_ERR_ADDRESS_MIN                             (0)
  #define MC0_PARITYERRLOG_ERR_ADDRESS_MAX                             (549755813887ULL) // 0x7FFFFFFFFF
  #define MC0_PARITYERRLOG_ERR_ADDRESS_DEF                             (0x00000000)
  #define MC0_PARITYERRLOG_ERR_ADDRESS_HSH                             (0x670051A0)

  #define MC0_PARITYERRLOG_RESERVED_OFF                                (39)
  #define MC0_PARITYERRLOG_RESERVED_WID                                (21)
  #define MC0_PARITYERRLOG_RESERVED_MSK                                (0x0FFFFF8000000000ULL)
  #define MC0_PARITYERRLOG_RESERVED_MIN                                (0)
  #define MC0_PARITYERRLOG_RESERVED_MAX                                (2097151) // 0x001FFFFF
  #define MC0_PARITYERRLOG_RESERVED_DEF                                (0x00000000)
  #define MC0_PARITYERRLOG_RESERVED_HSH                                (0x554E51A0)

  #define MC0_PARITYERRLOG_ERR_SRC_OFF                                 (60)
  #define MC0_PARITYERRLOG_ERR_SRC_WID                                 ( 1)
  #define MC0_PARITYERRLOG_ERR_SRC_MSK                                 (0x1000000000000000ULL)
  #define MC0_PARITYERRLOG_ERR_SRC_MIN                                 (0)
  #define MC0_PARITYERRLOG_ERR_SRC_MAX                                 (1) // 0x00000001
  #define MC0_PARITYERRLOG_ERR_SRC_DEF                                 (0x00000000)
  #define MC0_PARITYERRLOG_ERR_SRC_HSH                                 (0x417851A0)

  #define MC0_PARITYERRLOG_ERR_TYPE_OFF                                (61)
  #define MC0_PARITYERRLOG_ERR_TYPE_WID                                ( 2)
  #define MC0_PARITYERRLOG_ERR_TYPE_MSK                                (0x6000000000000000ULL)
  #define MC0_PARITYERRLOG_ERR_TYPE_MIN                                (0)
  #define MC0_PARITYERRLOG_ERR_TYPE_MAX                                (3) // 0x00000003
  #define MC0_PARITYERRLOG_ERR_TYPE_DEF                                (0x00000000)
  #define MC0_PARITYERRLOG_ERR_TYPE_HSH                                (0x427A51A0)

  #define MC0_PARITYERRLOG_ERR_STS_OFF                                 (63)
  #define MC0_PARITYERRLOG_ERR_STS_WID                                 ( 1)
  #define MC0_PARITYERRLOG_ERR_STS_MSK                                 (0x8000000000000000ULL)
  #define MC0_PARITYERRLOG_ERR_STS_MIN                                 (0)
  #define MC0_PARITYERRLOG_ERR_STS_MAX                                 (1) // 0x00000001
  #define MC0_PARITYERRLOG_ERR_STS_DEF                                 (0x00000000)
  #define MC0_PARITYERRLOG_ERR_STS_HSH                                 (0x417E51A0)

#define MC0_PARITY_ERR_INJ_REG                                         (0x000051A8)

  #define MC0_PARITY_ERR_INJ_DATA_ERR_EN_OFF                           ( 0)
  #define MC0_PARITY_ERR_INJ_DATA_ERR_EN_WID                           ( 8)
  #define MC0_PARITY_ERR_INJ_DATA_ERR_EN_MSK                           (0x000000FF)
  #define MC0_PARITY_ERR_INJ_DATA_ERR_EN_MIN                           (0)
  #define MC0_PARITY_ERR_INJ_DATA_ERR_EN_MAX                           (255) // 0x000000FF
  #define MC0_PARITY_ERR_INJ_DATA_ERR_EN_DEF                           (0x00000000)
  #define MC0_PARITY_ERR_INJ_DATA_ERR_EN_HSH                           (0x080051A8)

  #define MC0_PARITY_ERR_INJ_ADDR_ERR_EN_OFF                           ( 8)
  #define MC0_PARITY_ERR_INJ_ADDR_ERR_EN_WID                           ( 1)
  #define MC0_PARITY_ERR_INJ_ADDR_ERR_EN_MSK                           (0x00000100)
  #define MC0_PARITY_ERR_INJ_ADDR_ERR_EN_MIN                           (0)
  #define MC0_PARITY_ERR_INJ_ADDR_ERR_EN_MAX                           (1) // 0x00000001
  #define MC0_PARITY_ERR_INJ_ADDR_ERR_EN_DEF                           (0x00000000)
  #define MC0_PARITY_ERR_INJ_ADDR_ERR_EN_HSH                           (0x011051A8)

  #define MC0_PARITY_ERR_INJ_BE_ERR_EN_OFF                             ( 9)
  #define MC0_PARITY_ERR_INJ_BE_ERR_EN_WID                             ( 2)
  #define MC0_PARITY_ERR_INJ_BE_ERR_EN_MSK                             (0x00000600)
  #define MC0_PARITY_ERR_INJ_BE_ERR_EN_MIN                             (0)
  #define MC0_PARITY_ERR_INJ_BE_ERR_EN_MAX                             (3) // 0x00000003
  #define MC0_PARITY_ERR_INJ_BE_ERR_EN_DEF                             (0x00000000)
  #define MC0_PARITY_ERR_INJ_BE_ERR_EN_HSH                             (0x021251A8)

  #define MC0_PARITY_ERR_INJ_RSVD_OFF                                  (11)
  #define MC0_PARITY_ERR_INJ_RSVD_WID                                  ( 5)
  #define MC0_PARITY_ERR_INJ_RSVD_MSK                                  (0x0000F800)
  #define MC0_PARITY_ERR_INJ_RSVD_MIN                                  (0)
  #define MC0_PARITY_ERR_INJ_RSVD_MAX                                  (31) // 0x0000001F
  #define MC0_PARITY_ERR_INJ_RSVD_DEF                                  (0x00000000)
  #define MC0_PARITY_ERR_INJ_RSVD_HSH                                  (0x051651A8)

  #define MC0_PARITY_ERR_INJ_ERR_INJ_MASK_OFF                          (16)
  #define MC0_PARITY_ERR_INJ_ERR_INJ_MASK_WID                          ( 5)
  #define MC0_PARITY_ERR_INJ_ERR_INJ_MASK_MSK                          (0x001F0000)
  #define MC0_PARITY_ERR_INJ_ERR_INJ_MASK_MIN                          (0)
  #define MC0_PARITY_ERR_INJ_ERR_INJ_MASK_MAX                          (31) // 0x0000001F
  #define MC0_PARITY_ERR_INJ_ERR_INJ_MASK_DEF                          (0x00000000)
  #define MC0_PARITY_ERR_INJ_ERR_INJ_MASK_HSH                          (0x052051A8)

  #define MC0_PARITY_ERR_INJ_RSVD2_OFF                                 (21)
  #define MC0_PARITY_ERR_INJ_RSVD2_WID                                 (10)
  #define MC0_PARITY_ERR_INJ_RSVD2_MSK                                 (0x7FE00000)
  #define MC0_PARITY_ERR_INJ_RSVD2_MIN                                 (0)
  #define MC0_PARITY_ERR_INJ_RSVD2_MAX                                 (1023) // 0x000003FF
  #define MC0_PARITY_ERR_INJ_RSVD2_DEF                                 (0x00000000)
  #define MC0_PARITY_ERR_INJ_RSVD2_HSH                                 (0x0A2A51A8)

  #define MC0_PARITY_ERR_INJ_DATA_ERR_INJ_SRC_OFF                      (31)
  #define MC0_PARITY_ERR_INJ_DATA_ERR_INJ_SRC_WID                      ( 1)
  #define MC0_PARITY_ERR_INJ_DATA_ERR_INJ_SRC_MSK                      (0x80000000)
  #define MC0_PARITY_ERR_INJ_DATA_ERR_INJ_SRC_MIN                      (0)
  #define MC0_PARITY_ERR_INJ_DATA_ERR_INJ_SRC_MAX                      (1) // 0x00000001
  #define MC0_PARITY_ERR_INJ_DATA_ERR_INJ_SRC_DEF                      (0x00000000)
  #define MC0_PARITY_ERR_INJ_DATA_ERR_INJ_SRC_HSH                      (0x013E51A8)

#define MC0_PARITY_CONTROL_REG                                         (0x000051B4)

  #define MC0_PARITY_CONTROL_ADDR_PARITY_EN_OFF                        ( 0)
  #define MC0_PARITY_CONTROL_ADDR_PARITY_EN_WID                        ( 1)
  #define MC0_PARITY_CONTROL_ADDR_PARITY_EN_MSK                        (0x00000001)
  #define MC0_PARITY_CONTROL_ADDR_PARITY_EN_MIN                        (0)
  #define MC0_PARITY_CONTROL_ADDR_PARITY_EN_MAX                        (1) // 0x00000001
  #define MC0_PARITY_CONTROL_ADDR_PARITY_EN_DEF                        (0x00000001)
  #define MC0_PARITY_CONTROL_ADDR_PARITY_EN_HSH                        (0x010051B4)

  #define MC0_PARITY_CONTROL_WBE_PARITY_EN_OFF                         ( 1)
  #define MC0_PARITY_CONTROL_WBE_PARITY_EN_WID                         ( 1)
  #define MC0_PARITY_CONTROL_WBE_PARITY_EN_MSK                         (0x00000002)
  #define MC0_PARITY_CONTROL_WBE_PARITY_EN_MIN                         (0)
  #define MC0_PARITY_CONTROL_WBE_PARITY_EN_MAX                         (1) // 0x00000001
  #define MC0_PARITY_CONTROL_WBE_PARITY_EN_DEF                         (0x00000001)
  #define MC0_PARITY_CONTROL_WBE_PARITY_EN_HSH                         (0x010251B4)

  #define MC0_PARITY_CONTROL_WDATA_PARITY_EN_OFF                       ( 2)
  #define MC0_PARITY_CONTROL_WDATA_PARITY_EN_WID                       ( 2)
  #define MC0_PARITY_CONTROL_WDATA_PARITY_EN_MSK                       (0x0000000C)
  #define MC0_PARITY_CONTROL_WDATA_PARITY_EN_MIN                       (0)
  #define MC0_PARITY_CONTROL_WDATA_PARITY_EN_MAX                       (3) // 0x00000003
  #define MC0_PARITY_CONTROL_WDATA_PARITY_EN_DEF                       (0x00000003)
  #define MC0_PARITY_CONTROL_WDATA_PARITY_EN_HSH                       (0x020451B4)

  #define MC0_PARITY_CONTROL_RDATA_PARITY_EN_OFF                       ( 4)
  #define MC0_PARITY_CONTROL_RDATA_PARITY_EN_WID                       ( 1)
  #define MC0_PARITY_CONTROL_RDATA_PARITY_EN_MSK                       (0x00000010)
  #define MC0_PARITY_CONTROL_RDATA_PARITY_EN_MIN                       (0)
  #define MC0_PARITY_CONTROL_RDATA_PARITY_EN_MAX                       (1) // 0x00000001
  #define MC0_PARITY_CONTROL_RDATA_PARITY_EN_DEF                       (0x00000001)
  #define MC0_PARITY_CONTROL_RDATA_PARITY_EN_HSH                       (0x010851B4)

  #define MC0_PARITY_CONTROL_RSVD_0_OFF                                ( 5)
  #define MC0_PARITY_CONTROL_RSVD_0_WID                                ( 3)
  #define MC0_PARITY_CONTROL_RSVD_0_MSK                                (0x000000E0)
  #define MC0_PARITY_CONTROL_RSVD_0_MIN                                (0)
  #define MC0_PARITY_CONTROL_RSVD_0_MAX                                (7) // 0x00000007
  #define MC0_PARITY_CONTROL_RSVD_0_DEF                                (0x00000000)
  #define MC0_PARITY_CONTROL_RSVD_0_HSH                                (0x030A51B4)

  #define MC0_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_OFF                  ( 8)
  #define MC0_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_WID                  ( 1)
  #define MC0_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_MSK                  (0x00000100)
  #define MC0_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_MIN                  (0)
  #define MC0_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_MAX                  (1) // 0x00000001
  #define MC0_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_DEF                  (0x00000000)
  #define MC0_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_HSH                  (0x011051B4)

  #define MC0_PARITY_CONTROL_DIS_PARITY_LOG_OFF                        ( 9)
  #define MC0_PARITY_CONTROL_DIS_PARITY_LOG_WID                        ( 1)
  #define MC0_PARITY_CONTROL_DIS_PARITY_LOG_MSK                        (0x00000200)
  #define MC0_PARITY_CONTROL_DIS_PARITY_LOG_MIN                        (0)
  #define MC0_PARITY_CONTROL_DIS_PARITY_LOG_MAX                        (1) // 0x00000001
  #define MC0_PARITY_CONTROL_DIS_PARITY_LOG_DEF                        (0x00000000)
  #define MC0_PARITY_CONTROL_DIS_PARITY_LOG_HSH                        (0x011251B4)

  #define MC0_PARITY_CONTROL_RSVD_1_OFF                                (10)
  #define MC0_PARITY_CONTROL_RSVD_1_WID                                (21)
  #define MC0_PARITY_CONTROL_RSVD_1_MSK                                (0x7FFFFC00)
  #define MC0_PARITY_CONTROL_RSVD_1_MIN                                (0)
  #define MC0_PARITY_CONTROL_RSVD_1_MAX                                (2097151) // 0x001FFFFF
  #define MC0_PARITY_CONTROL_RSVD_1_DEF                                (0x00000000)
  #define MC0_PARITY_CONTROL_RSVD_1_HSH                                (0x151451B4)

  #define MC0_PARITY_CONTROL_PARITY_EN_OFF                             (31)
  #define MC0_PARITY_CONTROL_PARITY_EN_WID                             ( 1)
  #define MC0_PARITY_CONTROL_PARITY_EN_MSK                             (0x80000000)
  #define MC0_PARITY_CONTROL_PARITY_EN_MIN                             (0)
  #define MC0_PARITY_CONTROL_PARITY_EN_MAX                             (1) // 0x00000001
  #define MC0_PARITY_CONTROL_PARITY_EN_DEF                             (0x00000000)
  #define MC0_PARITY_CONTROL_PARITY_EN_HSH                             (0x013E51B4)

#define MC0_DDRPL_CFG_DTF_REG                                          (0x00005200)

  #define MC0_DDRPL_CFG_DTF_MCHTrace_OFF                               ( 4)
  #define MC0_DDRPL_CFG_DTF_MCHTrace_WID                               ( 1)
  #define MC0_DDRPL_CFG_DTF_MCHTrace_MSK                               (0x00000010)
  #define MC0_DDRPL_CFG_DTF_MCHTrace_MIN                               (0)
  #define MC0_DDRPL_CFG_DTF_MCHTrace_MAX                               (1) // 0x00000001
  #define MC0_DDRPL_CFG_DTF_MCHTrace_DEF                               (0x00000000)
  #define MC0_DDRPL_CFG_DTF_MCHTrace_HSH                               (0x01085200)

  #define MC0_DDRPL_CFG_DTF_SCHTrace_OFF                               ( 5)
  #define MC0_DDRPL_CFG_DTF_SCHTrace_WID                               ( 1)
  #define MC0_DDRPL_CFG_DTF_SCHTrace_MSK                               (0x00000020)
  #define MC0_DDRPL_CFG_DTF_SCHTrace_MIN                               (0)
  #define MC0_DDRPL_CFG_DTF_SCHTrace_MAX                               (1) // 0x00000001
  #define MC0_DDRPL_CFG_DTF_SCHTrace_DEF                               (0x00000000)
  #define MC0_DDRPL_CFG_DTF_SCHTrace_HSH                               (0x010A5200)

  #define MC0_DDRPL_CFG_DTF_ECC_EN_OFF                                 ( 6)
  #define MC0_DDRPL_CFG_DTF_ECC_EN_WID                                 ( 1)
  #define MC0_DDRPL_CFG_DTF_ECC_EN_MSK                                 (0x00000040)
  #define MC0_DDRPL_CFG_DTF_ECC_EN_MIN                                 (0)
  #define MC0_DDRPL_CFG_DTF_ECC_EN_MAX                                 (1) // 0x00000001
  #define MC0_DDRPL_CFG_DTF_ECC_EN_DEF                                 (0x00000000)
  #define MC0_DDRPL_CFG_DTF_ECC_EN_HSH                                 (0x010C5200)

  #define MC0_DDRPL_CFG_DTF_ECC_BYTE_replace_OFF                       ( 7)
  #define MC0_DDRPL_CFG_DTF_ECC_BYTE_replace_WID                       ( 3)
  #define MC0_DDRPL_CFG_DTF_ECC_BYTE_replace_MSK                       (0x00000380)
  #define MC0_DDRPL_CFG_DTF_ECC_BYTE_replace_MIN                       (0)
  #define MC0_DDRPL_CFG_DTF_ECC_BYTE_replace_MAX                       (7) // 0x00000007
  #define MC0_DDRPL_CFG_DTF_ECC_BYTE_replace_DEF                       (0x00000000)
  #define MC0_DDRPL_CFG_DTF_ECC_BYTE_replace_HSH                       (0x030E5200)

  #define MC0_DDRPL_CFG_DTF_RSVD_16_10_OFF                             (10)
  #define MC0_DDRPL_CFG_DTF_RSVD_16_10_WID                             ( 7)
  #define MC0_DDRPL_CFG_DTF_RSVD_16_10_MSK                             (0x0001FC00)
  #define MC0_DDRPL_CFG_DTF_RSVD_16_10_MIN                             (0)
  #define MC0_DDRPL_CFG_DTF_RSVD_16_10_MAX                             (127) // 0x0000007F
  #define MC0_DDRPL_CFG_DTF_RSVD_16_10_DEF                             (0x00000000)
  #define MC0_DDRPL_CFG_DTF_RSVD_16_10_HSH                             (0x07145200)

  #define MC0_DDRPL_CFG_DTF_Enable_ACC_Trace_OFF                       (17)
  #define MC0_DDRPL_CFG_DTF_Enable_ACC_Trace_WID                       ( 1)
  #define MC0_DDRPL_CFG_DTF_Enable_ACC_Trace_MSK                       (0x00020000)
  #define MC0_DDRPL_CFG_DTF_Enable_ACC_Trace_MIN                       (0)
  #define MC0_DDRPL_CFG_DTF_Enable_ACC_Trace_MAX                       (1) // 0x00000001
  #define MC0_DDRPL_CFG_DTF_Enable_ACC_Trace_DEF                       (0x00000001)
  #define MC0_DDRPL_CFG_DTF_Enable_ACC_Trace_HSH                       (0x01225200)

  #define MC0_DDRPL_CFG_DTF_Enable_ReadData_Trace_OFF                  (18)
  #define MC0_DDRPL_CFG_DTF_Enable_ReadData_Trace_WID                  ( 1)
  #define MC0_DDRPL_CFG_DTF_Enable_ReadData_Trace_MSK                  (0x00040000)
  #define MC0_DDRPL_CFG_DTF_Enable_ReadData_Trace_MIN                  (0)
  #define MC0_DDRPL_CFG_DTF_Enable_ReadData_Trace_MAX                  (1) // 0x00000001
  #define MC0_DDRPL_CFG_DTF_Enable_ReadData_Trace_DEF                  (0x00000001)
  #define MC0_DDRPL_CFG_DTF_Enable_ReadData_Trace_HSH                  (0x01245200)

  #define MC0_DDRPL_CFG_DTF_Enable_WriteData_Trace_OFF                 (19)
  #define MC0_DDRPL_CFG_DTF_Enable_WriteData_Trace_WID                 ( 1)
  #define MC0_DDRPL_CFG_DTF_Enable_WriteData_Trace_MSK                 (0x00080000)
  #define MC0_DDRPL_CFG_DTF_Enable_WriteData_Trace_MIN                 (0)
  #define MC0_DDRPL_CFG_DTF_Enable_WriteData_Trace_MAX                 (1) // 0x00000001
  #define MC0_DDRPL_CFG_DTF_Enable_WriteData_Trace_DEF                 (0x00000001)
  #define MC0_DDRPL_CFG_DTF_Enable_WriteData_Trace_HSH                 (0x01265200)

  #define MC0_DDRPL_CFG_DTF_DDRPL_Activate_OFF                         (20)
  #define MC0_DDRPL_CFG_DTF_DDRPL_Activate_WID                         ( 1)
  #define MC0_DDRPL_CFG_DTF_DDRPL_Activate_MSK                         (0x00100000)
  #define MC0_DDRPL_CFG_DTF_DDRPL_Activate_MIN                         (0)
  #define MC0_DDRPL_CFG_DTF_DDRPL_Activate_MAX                         (1) // 0x00000001
  #define MC0_DDRPL_CFG_DTF_DDRPL_Activate_DEF                         (0x00000000)
  #define MC0_DDRPL_CFG_DTF_DDRPL_Activate_HSH                         (0x01285200)

  #define MC0_DDRPL_CFG_DTF_DDRPL_GLB_DRV_GATE_DIS_OFF                 (21)
  #define MC0_DDRPL_CFG_DTF_DDRPL_GLB_DRV_GATE_DIS_WID                 ( 1)
  #define MC0_DDRPL_CFG_DTF_DDRPL_GLB_DRV_GATE_DIS_MSK                 (0x00200000)
  #define MC0_DDRPL_CFG_DTF_DDRPL_GLB_DRV_GATE_DIS_MIN                 (0)
  #define MC0_DDRPL_CFG_DTF_DDRPL_GLB_DRV_GATE_DIS_MAX                 (1) // 0x00000001
  #define MC0_DDRPL_CFG_DTF_DDRPL_GLB_DRV_GATE_DIS_DEF                 (0x00000000)
  #define MC0_DDRPL_CFG_DTF_DDRPL_GLB_DRV_GATE_DIS_HSH                 (0x012A5200)

  #define MC0_DDRPL_CFG_DTF_RSVD_23_22_OFF                             (22)
  #define MC0_DDRPL_CFG_DTF_RSVD_23_22_WID                             ( 2)
  #define MC0_DDRPL_CFG_DTF_RSVD_23_22_MSK                             (0x00C00000)
  #define MC0_DDRPL_CFG_DTF_RSVD_23_22_MIN                             (0)
  #define MC0_DDRPL_CFG_DTF_RSVD_23_22_MAX                             (3) // 0x00000003
  #define MC0_DDRPL_CFG_DTF_RSVD_23_22_DEF                             (0x00000002)
  #define MC0_DDRPL_CFG_DTF_RSVD_23_22_HSH                             (0x022C5200)

  #define MC0_DDRPL_CFG_DTF_DTF_ENC_CB_OFF                             (24)
  #define MC0_DDRPL_CFG_DTF_DTF_ENC_CB_WID                             ( 1)
  #define MC0_DDRPL_CFG_DTF_DTF_ENC_CB_MSK                             (0x01000000)
  #define MC0_DDRPL_CFG_DTF_DTF_ENC_CB_MIN                             (0)
  #define MC0_DDRPL_CFG_DTF_DTF_ENC_CB_MAX                             (1) // 0x00000001
  #define MC0_DDRPL_CFG_DTF_DTF_ENC_CB_DEF                             (0x00000000)
  #define MC0_DDRPL_CFG_DTF_DTF_ENC_CB_HSH                             (0x01305200)

  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_read_OFF                 (26)
  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_read_WID                 ( 1)
  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_read_MSK                 (0x04000000)
  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_read_MIN                 (0)
  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_read_MAX                 (1) // 0x00000001
  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_read_DEF                 (0x00000000)
  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_read_HSH                 (0x01345200)

  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_write_OFF                (27)
  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_write_WID                ( 1)
  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_write_MSK                (0x08000000)
  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_write_MIN                (0)
  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_write_MAX                (1) // 0x00000001
  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_write_DEF                (0x00000000)
  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_write_HSH                (0x01365200)

  #define MC0_DDRPL_CFG_DTF_Trace_2LM_Tag_OFF                          (28)
  #define MC0_DDRPL_CFG_DTF_Trace_2LM_Tag_WID                          ( 1)
  #define MC0_DDRPL_CFG_DTF_Trace_2LM_Tag_MSK                          (0x10000000)
  #define MC0_DDRPL_CFG_DTF_Trace_2LM_Tag_MIN                          (0)
  #define MC0_DDRPL_CFG_DTF_Trace_2LM_Tag_MAX                          (1) // 0x00000001
  #define MC0_DDRPL_CFG_DTF_Trace_2LM_Tag_DEF                          (0x00000000)
  #define MC0_DDRPL_CFG_DTF_Trace_2LM_Tag_HSH                          (0x01385200)

#define MC0_DDRPL_FILTER_DTF_REG                                       (0x00005204)

  #define MC0_DDRPL_FILTER_DTF_Enable_ACC_Window_Filtering_OFF         ( 0)
  #define MC0_DDRPL_FILTER_DTF_Enable_ACC_Window_Filtering_WID         ( 1)
  #define MC0_DDRPL_FILTER_DTF_Enable_ACC_Window_Filtering_MSK         (0x00000001)
  #define MC0_DDRPL_FILTER_DTF_Enable_ACC_Window_Filtering_MIN         (0)
  #define MC0_DDRPL_FILTER_DTF_Enable_ACC_Window_Filtering_MAX         (1) // 0x00000001
  #define MC0_DDRPL_FILTER_DTF_Enable_ACC_Window_Filtering_DEF         (0x00000001)
  #define MC0_DDRPL_FILTER_DTF_Enable_ACC_Window_Filtering_HSH         (0x01005204)

  #define MC0_DDRPL_FILTER_DTF_Filter_Window_Depth_OFF                 ( 1)
  #define MC0_DDRPL_FILTER_DTF_Filter_Window_Depth_WID                 ( 8)
  #define MC0_DDRPL_FILTER_DTF_Filter_Window_Depth_MSK                 (0x000001FE)
  #define MC0_DDRPL_FILTER_DTF_Filter_Window_Depth_MIN                 (0)
  #define MC0_DDRPL_FILTER_DTF_Filter_Window_Depth_MAX                 (255) // 0x000000FF
  #define MC0_DDRPL_FILTER_DTF_Filter_Window_Depth_DEF                 (0x000000FF)
  #define MC0_DDRPL_FILTER_DTF_Filter_Window_Depth_HSH                 (0x08025204)

#define MC0_DDRPL_DEBUG_DTF_REG                                        (0x00005208)

  #define MC0_DDRPL_DEBUG_DTF_Read_Data_UserDefined_Bits_OFF           (16)
  #define MC0_DDRPL_DEBUG_DTF_Read_Data_UserDefined_Bits_WID           ( 8)
  #define MC0_DDRPL_DEBUG_DTF_Read_Data_UserDefined_Bits_MSK           (0x00FF0000)
  #define MC0_DDRPL_DEBUG_DTF_Read_Data_UserDefined_Bits_MIN           (0)
  #define MC0_DDRPL_DEBUG_DTF_Read_Data_UserDefined_Bits_MAX           (255) // 0x000000FF
  #define MC0_DDRPL_DEBUG_DTF_Read_Data_UserDefined_Bits_DEF           (0x00000000)
  #define MC0_DDRPL_DEBUG_DTF_Read_Data_UserDefined_Bits_HSH           (0x08205208)

  #define MC0_DDRPL_DEBUG_DTF_Write_Data_UserDefined_Bits_OFF          (24)
  #define MC0_DDRPL_DEBUG_DTF_Write_Data_UserDefined_Bits_WID          ( 8)
  #define MC0_DDRPL_DEBUG_DTF_Write_Data_UserDefined_Bits_MSK          (0xFF000000)
  #define MC0_DDRPL_DEBUG_DTF_Write_Data_UserDefined_Bits_MIN          (0)
  #define MC0_DDRPL_DEBUG_DTF_Write_Data_UserDefined_Bits_MAX          (255) // 0x000000FF
  #define MC0_DDRPL_DEBUG_DTF_Write_Data_UserDefined_Bits_DEF          (0x00000000)
  #define MC0_DDRPL_DEBUG_DTF_Write_Data_UserDefined_Bits_HSH          (0x08305208)

#define MC0_DDRPL_VISA_LANES_REG                                       (0x0000520C)

  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_1_out_OFF                ( 0)
  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_1_out_WID                ( 8)
  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_1_out_MSK                (0x000000FF)
  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_1_out_MIN                (0)
  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_1_out_MAX                (255) // 0x000000FF
  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_1_out_DEF                (0x00000000)
  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_1_out_HSH                (0x0800520C)

  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_0_out_OFF                ( 8)
  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_0_out_WID                ( 8)
  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_0_out_MSK                (0x0000FF00)
  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_0_out_MIN                (0)
  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_0_out_MAX                (255) // 0x000000FF
  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_0_out_DEF                (0x00000000)
  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_0_out_HSH                (0x0810520C)

  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_1_out_OFF                (16)
  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_1_out_WID                ( 8)
  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_1_out_MSK                (0x00FF0000)
  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_1_out_MIN                (0)
  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_1_out_MAX                (255) // 0x000000FF
  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_1_out_DEF                (0x00000000)
  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_1_out_HSH                (0x0820520C)

  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_0_out_OFF                (24)
  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_0_out_WID                ( 8)
  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_0_out_MSK                (0xFF000000)
  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_0_out_MIN                (0)
  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_0_out_MAX                (255) // 0x000000FF
  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_0_out_DEF                (0x00000000)
  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_0_out_HSH                (0x0830520C)

#define MC0_DDRPL_VISA_CFG_DTF_REG                                     (0x00005210)

  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Dclk_tree_OFF    ( 0)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Dclk_tree_WID    ( 2)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Dclk_tree_MSK    (0x00000003)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Dclk_tree_MIN    (0)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Dclk_tree_MAX    (3) // 0x00000003
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Dclk_tree_DEF    (0x00000000)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Dclk_tree_HSH    (0x02005210)

  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Dclk_tree_OFF    ( 2)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Dclk_tree_WID    ( 2)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Dclk_tree_MSK    (0x0000000C)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Dclk_tree_MIN    (0)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Dclk_tree_MAX    (3) // 0x00000003
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Dclk_tree_DEF    (0x00000000)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Dclk_tree_HSH    (0x02045210)

  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Qclk_tree_OFF    ( 4)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Qclk_tree_WID    ( 2)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Qclk_tree_MSK    (0x00000030)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Qclk_tree_MIN    (0)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Qclk_tree_MAX    (3) // 0x00000003
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Qclk_tree_DEF    (0x00000000)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Qclk_tree_HSH    (0x02085210)

  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Qclk_tree_OFF    ( 6)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Qclk_tree_WID    ( 2)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Qclk_tree_MSK    (0x000000C0)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Qclk_tree_MIN    (0)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Qclk_tree_MAX    (3) // 0x00000003
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Qclk_tree_DEF    (0x00000000)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Qclk_tree_HSH    (0x020C5210)

#define CAMARILLO_MAILBOX_DATA0_PCU_REG                                (0x00005810)

  #define CAMARILLO_MAILBOX_DATA0_PCU_DATA_OFF                         ( 0)
  #define CAMARILLO_MAILBOX_DATA0_PCU_DATA_WID                         (32)
  #define CAMARILLO_MAILBOX_DATA0_PCU_DATA_MSK                         (0xFFFFFFFF)
  #define CAMARILLO_MAILBOX_DATA0_PCU_DATA_MIN                         (0)
  #define CAMARILLO_MAILBOX_DATA0_PCU_DATA_MAX                         (4294967295) // 0xFFFFFFFF
  #define CAMARILLO_MAILBOX_DATA0_PCU_DATA_DEF                         (0x00000000)
  #define CAMARILLO_MAILBOX_DATA0_PCU_DATA_HSH                         (0x20005810)

#define CAMARILLO_MAILBOX_DATA1_PCU_REG                                (0x00005814)
//Duplicate of CAMARILLO_MAILBOX_DATA0_PCU_REG

#define CAMARILLO_MAILBOX_INTERFACE_PCU_REG                            (0x00005818)

  #define CAMARILLO_MAILBOX_INTERFACE_PCU_COMMAND_OFF                  ( 0)
  #define CAMARILLO_MAILBOX_INTERFACE_PCU_COMMAND_WID                  ( 8)
  #define CAMARILLO_MAILBOX_INTERFACE_PCU_COMMAND_MSK                  (0x000000FF)
  #define CAMARILLO_MAILBOX_INTERFACE_PCU_COMMAND_MIN                  (0)
  #define CAMARILLO_MAILBOX_INTERFACE_PCU_COMMAND_MAX                  (255) // 0x000000FF
  #define CAMARILLO_MAILBOX_INTERFACE_PCU_COMMAND_DEF                  (0x00000000)
  #define CAMARILLO_MAILBOX_INTERFACE_PCU_COMMAND_HSH                  (0x08005818)

  #define CAMARILLO_MAILBOX_INTERFACE_PCU_PARAM1_OFF                   ( 8)
  #define CAMARILLO_MAILBOX_INTERFACE_PCU_PARAM1_WID                   ( 8)
  #define CAMARILLO_MAILBOX_INTERFACE_PCU_PARAM1_MSK                   (0x0000FF00)
  #define CAMARILLO_MAILBOX_INTERFACE_PCU_PARAM1_MIN                   (0)
  #define CAMARILLO_MAILBOX_INTERFACE_PCU_PARAM1_MAX                   (255) // 0x000000FF
  #define CAMARILLO_MAILBOX_INTERFACE_PCU_PARAM1_DEF                   (0x00000000)
  #define CAMARILLO_MAILBOX_INTERFACE_PCU_PARAM1_HSH                   (0x08105818)

  #define CAMARILLO_MAILBOX_INTERFACE_PCU_PARAM2_OFF                   (16)
  #define CAMARILLO_MAILBOX_INTERFACE_PCU_PARAM2_WID                   (14)
  #define CAMARILLO_MAILBOX_INTERFACE_PCU_PARAM2_MSK                   (0x3FFF0000)
  #define CAMARILLO_MAILBOX_INTERFACE_PCU_PARAM2_MIN                   (0)
  #define CAMARILLO_MAILBOX_INTERFACE_PCU_PARAM2_MAX                   (16383) // 0x00003FFF
  #define CAMARILLO_MAILBOX_INTERFACE_PCU_PARAM2_DEF                   (0x00000000)
  #define CAMARILLO_MAILBOX_INTERFACE_PCU_PARAM2_HSH                   (0x0E205818)

  #define CAMARILLO_MAILBOX_INTERFACE_PCU_RUN_BUSY_OFF                 (31)
  #define CAMARILLO_MAILBOX_INTERFACE_PCU_RUN_BUSY_WID                 ( 1)
  #define CAMARILLO_MAILBOX_INTERFACE_PCU_RUN_BUSY_MSK                 (0x80000000)
  #define CAMARILLO_MAILBOX_INTERFACE_PCU_RUN_BUSY_MIN                 (0)
  #define CAMARILLO_MAILBOX_INTERFACE_PCU_RUN_BUSY_MAX                 (1) // 0x00000001
  #define CAMARILLO_MAILBOX_INTERFACE_PCU_RUN_BUSY_DEF                 (0x00000000)
  #define CAMARILLO_MAILBOX_INTERFACE_PCU_RUN_BUSY_HSH                 (0x013E5818)

#define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_REG                      (0x00005820)

  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_HIGH_TEMP_INT_ENABLE_OFF ( 0)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_HIGH_TEMP_INT_ENABLE_WID ( 1)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_HIGH_TEMP_INT_ENABLE_MSK (0x00000001)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_HIGH_TEMP_INT_ENABLE_MIN (0)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_HIGH_TEMP_INT_ENABLE_MAX (1) // 0x00000001
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_HIGH_TEMP_INT_ENABLE_DEF (0x00000000)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_HIGH_TEMP_INT_ENABLE_HSH (0x01005820)

  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_LOW_TEMP_INT_ENABLE_OFF ( 1)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_LOW_TEMP_INT_ENABLE_WID ( 1)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_LOW_TEMP_INT_ENABLE_MSK (0x00000002)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_LOW_TEMP_INT_ENABLE_MIN (0)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_LOW_TEMP_INT_ENABLE_MAX (1) // 0x00000001
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_LOW_TEMP_INT_ENABLE_DEF (0x00000000)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_LOW_TEMP_INT_ENABLE_HSH (0x01025820)

  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_PROCHOT_INT_ENABLE_OFF ( 2)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_PROCHOT_INT_ENABLE_WID ( 1)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_PROCHOT_INT_ENABLE_MSK (0x00000004)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_PROCHOT_INT_ENABLE_MIN (0)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_PROCHOT_INT_ENABLE_MAX (1) // 0x00000001
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_PROCHOT_INT_ENABLE_DEF (0x00000000)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_PROCHOT_INT_ENABLE_HSH (0x01045820)

  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_OUT_OF_SPEC_INT_ENABLE_OFF ( 4)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_OUT_OF_SPEC_INT_ENABLE_WID ( 1)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_OUT_OF_SPEC_INT_ENABLE_MSK (0x00000010)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_OUT_OF_SPEC_INT_ENABLE_MIN (0)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_OUT_OF_SPEC_INT_ENABLE_MAX (1) // 0x00000001
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_OUT_OF_SPEC_INT_ENABLE_DEF (0x00000000)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_OUT_OF_SPEC_INT_ENABLE_HSH (0x01085820)

  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_REL_TEMP_OFF ( 8)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_REL_TEMP_WID ( 7)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_REL_TEMP_MSK (0x00007F00)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_REL_TEMP_MIN (0)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_REL_TEMP_MAX (127) // 0x0000007F
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_REL_TEMP_DEF (0x00000000)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_REL_TEMP_HSH (0x07105820)

  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_INT_ENABLE_OFF (15)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_INT_ENABLE_WID ( 1)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_INT_ENABLE_MSK (0x00008000)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_INT_ENABLE_MIN (0)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_INT_ENABLE_MAX (1) // 0x00000001
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_INT_ENABLE_DEF (0x00000000)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_1_INT_ENABLE_HSH (0x011E5820)

  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_REL_TEMP_OFF (16)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_REL_TEMP_WID ( 7)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_REL_TEMP_MSK (0x007F0000)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_REL_TEMP_MIN (0)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_REL_TEMP_MAX (127) // 0x0000007F
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_REL_TEMP_DEF (0x00000000)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_REL_TEMP_HSH (0x07205820)

  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_INT_ENABLE_OFF (23)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_INT_ENABLE_WID ( 1)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_INT_ENABLE_MSK (0x00800000)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_INT_ENABLE_MIN (0)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_INT_ENABLE_MAX (1) // 0x00000001
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_INT_ENABLE_DEF (0x00000000)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD_2_INT_ENABLE_HSH (0x012E5820)

  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_POWER_INT_ENABLE_OFF   (24)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_POWER_INT_ENABLE_WID   ( 1)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_POWER_INT_ENABLE_MSK   (0x01000000)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_POWER_INT_ENABLE_MIN   (0)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_POWER_INT_ENABLE_MAX   (1) // 0x00000001
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_POWER_INT_ENABLE_DEF   (0x00000000)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_POWER_INT_ENABLE_HSH   (0x01305820)

  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_TEMPERATURE_AVERAGING_TIME_WINDOW_OFF (25)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_TEMPERATURE_AVERAGING_TIME_WINDOW_WID ( 7)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_TEMPERATURE_AVERAGING_TIME_WINDOW_MSK (0xFE000000)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_TEMPERATURE_AVERAGING_TIME_WINDOW_MIN (0)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_TEMPERATURE_AVERAGING_TIME_WINDOW_MAX (127) // 0x0000007F
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_TEMPERATURE_AVERAGING_TIME_WINDOW_DEF (0x00000000)
  #define PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_TEMPERATURE_AVERAGING_TIME_WINDOW_HSH (0x07325820)

#define BIOS_POST_CODE_PCU_REG                                         (0x00005824)

  #define BIOS_POST_CODE_PCU_PostCode_OFF                              ( 0)
  #define BIOS_POST_CODE_PCU_PostCode_WID                              (32)
  #define BIOS_POST_CODE_PCU_PostCode_MSK                              (0xFFFFFFFF)
  #define BIOS_POST_CODE_PCU_PostCode_MIN                              (0)
  #define BIOS_POST_CODE_PCU_PostCode_MAX                              (4294967295) // 0xFFFFFFFF
  #define BIOS_POST_CODE_PCU_PostCode_DEF                              (0x00000000)
  #define BIOS_POST_CODE_PCU_PostCode_HSH                              (0x20005824)

#define EDRAM_PM_CONTROL_PCU_REG                                       (0x00005878)

  #define EDRAM_PM_CONTROL_PCU_EDRAM_EN_OFF                            ( 0)
  #define EDRAM_PM_CONTROL_PCU_EDRAM_EN_WID                            ( 1)
  #define EDRAM_PM_CONTROL_PCU_EDRAM_EN_MSK                            (0x00000001)
  #define EDRAM_PM_CONTROL_PCU_EDRAM_EN_MIN                            (0)
  #define EDRAM_PM_CONTROL_PCU_EDRAM_EN_MAX                            (1) // 0x00000001
  #define EDRAM_PM_CONTROL_PCU_EDRAM_EN_DEF                            (0x00000000)
  #define EDRAM_PM_CONTROL_PCU_EDRAM_EN_HSH                            (0x01005878)

  #define EDRAM_PM_CONTROL_PCU_EOPIO_LINK_SPEED_PREFERENCE_OFF         (27)
  #define EDRAM_PM_CONTROL_PCU_EOPIO_LINK_SPEED_PREFERENCE_WID         ( 1)
  #define EDRAM_PM_CONTROL_PCU_EOPIO_LINK_SPEED_PREFERENCE_MSK         (0x08000000)
  #define EDRAM_PM_CONTROL_PCU_EOPIO_LINK_SPEED_PREFERENCE_MIN         (0)
  #define EDRAM_PM_CONTROL_PCU_EOPIO_LINK_SPEED_PREFERENCE_MAX         (1) // 0x00000001
  #define EDRAM_PM_CONTROL_PCU_EOPIO_LINK_SPEED_PREFERENCE_DEF         (0x00000000)
  #define EDRAM_PM_CONTROL_PCU_EOPIO_LINK_SPEED_PREFERENCE_HSH         (0x01365878)

  #define EDRAM_PM_CONTROL_PCU_PKGC_FLUSH_LEVEL_OFF                    (28)
  #define EDRAM_PM_CONTROL_PCU_PKGC_FLUSH_LEVEL_WID                    ( 2)
  #define EDRAM_PM_CONTROL_PCU_PKGC_FLUSH_LEVEL_MSK                    (0x30000000)
  #define EDRAM_PM_CONTROL_PCU_PKGC_FLUSH_LEVEL_MIN                    (0)
  #define EDRAM_PM_CONTROL_PCU_PKGC_FLUSH_LEVEL_MAX                    (3) // 0x00000003
  #define EDRAM_PM_CONTROL_PCU_PKGC_FLUSH_LEVEL_DEF                    (0x00000000)
  #define EDRAM_PM_CONTROL_PCU_PKGC_FLUSH_LEVEL_HSH                    (0x02385878)

  #define EDRAM_PM_CONTROL_PCU_POLICY_OFF                              (30)
  #define EDRAM_PM_CONTROL_PCU_POLICY_WID                              ( 1)
  #define EDRAM_PM_CONTROL_PCU_POLICY_MSK                              (0x40000000)
  #define EDRAM_PM_CONTROL_PCU_POLICY_MIN                              (0)
  #define EDRAM_PM_CONTROL_PCU_POLICY_MAX                              (1) // 0x00000001
  #define EDRAM_PM_CONTROL_PCU_POLICY_DEF                              (0x00000000)
  #define EDRAM_PM_CONTROL_PCU_POLICY_HSH                              (0x013C5878)

  #define EDRAM_PM_CONTROL_PCU_MODE_OFF                                (31)
  #define EDRAM_PM_CONTROL_PCU_MODE_WID                                ( 1)
  #define EDRAM_PM_CONTROL_PCU_MODE_MSK                                (0x80000000)
  #define EDRAM_PM_CONTROL_PCU_MODE_MIN                                (0)
  #define EDRAM_PM_CONTROL_PCU_MODE_MAX                                (1) // 0x00000001
  #define EDRAM_PM_CONTROL_PCU_MODE_DEF                                (0x00000000)
  #define EDRAM_PM_CONTROL_PCU_MODE_HSH                                (0x013E5878)

#define DDR_PTM_CTL_PCU_REG                                            (0x00005880)

  #define DDR_PTM_CTL_PCU_OLTM_ENABLE_OFF                              ( 0)
  #define DDR_PTM_CTL_PCU_OLTM_ENABLE_WID                              ( 1)
  #define DDR_PTM_CTL_PCU_OLTM_ENABLE_MSK                              (0x00000001)
  #define DDR_PTM_CTL_PCU_OLTM_ENABLE_MIN                              (0)
  #define DDR_PTM_CTL_PCU_OLTM_ENABLE_MAX                              (1) // 0x00000001
  #define DDR_PTM_CTL_PCU_OLTM_ENABLE_DEF                              (0x00000000)
  #define DDR_PTM_CTL_PCU_OLTM_ENABLE_HSH                              (0x01005880)

  #define DDR_PTM_CTL_PCU_CLTM_ENABLE_OFF                              ( 1)
  #define DDR_PTM_CTL_PCU_CLTM_ENABLE_WID                              ( 1)
  #define DDR_PTM_CTL_PCU_CLTM_ENABLE_MSK                              (0x00000002)
  #define DDR_PTM_CTL_PCU_CLTM_ENABLE_MIN                              (0)
  #define DDR_PTM_CTL_PCU_CLTM_ENABLE_MAX                              (1) // 0x00000001
  #define DDR_PTM_CTL_PCU_CLTM_ENABLE_DEF                              (0x00000000)
  #define DDR_PTM_CTL_PCU_CLTM_ENABLE_HSH                              (0x01025880)

  #define DDR_PTM_CTL_PCU_REFRESH_2X_MODE_OFF                          ( 2)
  #define DDR_PTM_CTL_PCU_REFRESH_2X_MODE_WID                          ( 2)
  #define DDR_PTM_CTL_PCU_REFRESH_2X_MODE_MSK                          (0x0000000C)
  #define DDR_PTM_CTL_PCU_REFRESH_2X_MODE_MIN                          (0)
  #define DDR_PTM_CTL_PCU_REFRESH_2X_MODE_MAX                          (3) // 0x00000003
  #define DDR_PTM_CTL_PCU_REFRESH_2X_MODE_DEF                          (0x00000000)
  #define DDR_PTM_CTL_PCU_REFRESH_2X_MODE_HSH                          (0x02045880)

  #define DDR_PTM_CTL_PCU_EXTTS_ENABLE_OFF                             ( 4)
  #define DDR_PTM_CTL_PCU_EXTTS_ENABLE_WID                             ( 1)
  #define DDR_PTM_CTL_PCU_EXTTS_ENABLE_MSK                             (0x00000010)
  #define DDR_PTM_CTL_PCU_EXTTS_ENABLE_MIN                             (0)
  #define DDR_PTM_CTL_PCU_EXTTS_ENABLE_MAX                             (1) // 0x00000001
  #define DDR_PTM_CTL_PCU_EXTTS_ENABLE_DEF                             (0x00000000)
  #define DDR_PTM_CTL_PCU_EXTTS_ENABLE_HSH                             (0x01085880)

  #define DDR_PTM_CTL_PCU_LOCK_PTM_REGS_PCU_OFF                        ( 5)
  #define DDR_PTM_CTL_PCU_LOCK_PTM_REGS_PCU_WID                        ( 1)
  #define DDR_PTM_CTL_PCU_LOCK_PTM_REGS_PCU_MSK                        (0x00000020)
  #define DDR_PTM_CTL_PCU_LOCK_PTM_REGS_PCU_MIN                        (0)
  #define DDR_PTM_CTL_PCU_LOCK_PTM_REGS_PCU_MAX                        (1) // 0x00000001
  #define DDR_PTM_CTL_PCU_LOCK_PTM_REGS_PCU_DEF                        (0x00000000)
  #define DDR_PTM_CTL_PCU_LOCK_PTM_REGS_PCU_HSH                        (0x010A5880)

  #define DDR_PTM_CTL_PCU_PDWN_CONFIG_CTL_OFF                          ( 6)
  #define DDR_PTM_CTL_PCU_PDWN_CONFIG_CTL_WID                          ( 1)
  #define DDR_PTM_CTL_PCU_PDWN_CONFIG_CTL_MSK                          (0x00000040)
  #define DDR_PTM_CTL_PCU_PDWN_CONFIG_CTL_MIN                          (0)
  #define DDR_PTM_CTL_PCU_PDWN_CONFIG_CTL_MAX                          (1) // 0x00000001
  #define DDR_PTM_CTL_PCU_PDWN_CONFIG_CTL_DEF                          (0x00000000)
  #define DDR_PTM_CTL_PCU_PDWN_CONFIG_CTL_HSH                          (0x010C5880)

  #define DDR_PTM_CTL_PCU_DISABLE_DRAM_TS_OFF                          ( 7)
  #define DDR_PTM_CTL_PCU_DISABLE_DRAM_TS_WID                          ( 1)
  #define DDR_PTM_CTL_PCU_DISABLE_DRAM_TS_MSK                          (0x00000080)
  #define DDR_PTM_CTL_PCU_DISABLE_DRAM_TS_MIN                          (0)
  #define DDR_PTM_CTL_PCU_DISABLE_DRAM_TS_MAX                          (1) // 0x00000001
  #define DDR_PTM_CTL_PCU_DISABLE_DRAM_TS_DEF                          (0x00000000)
  #define DDR_PTM_CTL_PCU_DISABLE_DRAM_TS_HSH                          (0x010E5880)

  #define DDR_PTM_CTL_PCU_DDR4_SKIP_REFRESH_EN_OFF                     ( 8)
  #define DDR_PTM_CTL_PCU_DDR4_SKIP_REFRESH_EN_WID                     ( 1)
  #define DDR_PTM_CTL_PCU_DDR4_SKIP_REFRESH_EN_MSK                     (0x00000100)
  #define DDR_PTM_CTL_PCU_DDR4_SKIP_REFRESH_EN_MIN                     (0)
  #define DDR_PTM_CTL_PCU_DDR4_SKIP_REFRESH_EN_MAX                     (1) // 0x00000001
  #define DDR_PTM_CTL_PCU_DDR4_SKIP_REFRESH_EN_DEF                     (0x00000000)
  #define DDR_PTM_CTL_PCU_DDR4_SKIP_REFRESH_EN_HSH                     (0x01105880)

#define DDR_BANDWIDTH_CONTROL_PCU_REG                                  (0x00005884)

  #define DDR_BANDWIDTH_CONTROL_PCU_BANDWIDTH_THROTTLE_OFF             ( 0)
  #define DDR_BANDWIDTH_CONTROL_PCU_BANDWIDTH_THROTTLE_WID             ( 4)
  #define DDR_BANDWIDTH_CONTROL_PCU_BANDWIDTH_THROTTLE_MSK             (0x0000000F)
  #define DDR_BANDWIDTH_CONTROL_PCU_BANDWIDTH_THROTTLE_MIN             (0)
  #define DDR_BANDWIDTH_CONTROL_PCU_BANDWIDTH_THROTTLE_MAX             (15) // 0x0000000F
  #define DDR_BANDWIDTH_CONTROL_PCU_BANDWIDTH_THROTTLE_DEF             (0x00000000)
  #define DDR_BANDWIDTH_CONTROL_PCU_BANDWIDTH_THROTTLE_HSH             (0x04005884)

#define DDR_THERM_CAMARILLO_INTERRUPT_PCU_REG                          (0x000058A0)

  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD1_INT_ENABLE_OFF  ( 0)
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD1_INT_ENABLE_WID  ( 1)
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD1_INT_ENABLE_MSK  (0x00000001)
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD1_INT_ENABLE_MIN  (0)
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD1_INT_ENABLE_MAX  (1) // 0x00000001
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD1_INT_ENABLE_DEF  (0x00000000)
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD1_INT_ENABLE_HSH  (0x010058A0)

  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD2_INT_ENABLE_OFF  ( 1)
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD2_INT_ENABLE_WID  ( 1)
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD2_INT_ENABLE_MSK  (0x00000002)
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD2_INT_ENABLE_MIN  (0)
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD2_INT_ENABLE_MAX  (1) // 0x00000001
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD2_INT_ENABLE_DEF  (0x00000000)
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD2_INT_ENABLE_HSH  (0x010258A0)

  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD1_OFF             ( 8)
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD1_WID             ( 8)
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD1_MSK             (0x0000FF00)
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD1_MIN             (0)
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD1_MAX             (255) // 0x000000FF
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD1_DEF             (0x00000000)
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD1_HSH             (0x081058A0)

  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD2_OFF             (16)
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD2_WID             ( 8)
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD2_MSK             (0x00FF0000)
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD2_MIN             (0)
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD2_MAX             (255) // 0x000000FF
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD2_DEF             (0x00000000)
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_THRESHOLD2_HSH             (0x082058A0)

  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_TIME_WINDOW_OFF            (24)
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_TIME_WINDOW_WID            ( 7)
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_TIME_WINDOW_MSK            (0x7F000000)
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_TIME_WINDOW_MIN            (0)
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_TIME_WINDOW_MAX            (127) // 0x0000007F
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_TIME_WINDOW_DEF            (0x00000000)
  #define DDR_THERM_CAMARILLO_INTERRUPT_PCU_TIME_WINDOW_HSH            (0x073058A0)

#define DDR_VOLTAGE_PCU_REG                                            (0x000058A4)

  #define DDR_VOLTAGE_PCU_DDR_VOLTAGE_OFF                              ( 0)
  #define DDR_VOLTAGE_PCU_DDR_VOLTAGE_WID                              ( 3)
  #define DDR_VOLTAGE_PCU_DDR_VOLTAGE_MSK                              (0x00000007)
  #define DDR_VOLTAGE_PCU_DDR_VOLTAGE_MIN                              (0)
  #define DDR_VOLTAGE_PCU_DDR_VOLTAGE_MAX                              (7) // 0x00000007
  #define DDR_VOLTAGE_PCU_DDR_VOLTAGE_DEF                              (0x00000000)
  #define DDR_VOLTAGE_PCU_DDR_VOLTAGE_HSH                              (0x030058A4)

#define DDR_RAPL_LIMIT_PCU_REG                                         (0x000058E0)

  #define DDR_RAPL_LIMIT_PCU_LIMIT1_POWER_OFF                          ( 0)
  #define DDR_RAPL_LIMIT_PCU_LIMIT1_POWER_WID                          (15)
  #define DDR_RAPL_LIMIT_PCU_LIMIT1_POWER_MSK                          (0x00007FFF)
  #define DDR_RAPL_LIMIT_PCU_LIMIT1_POWER_MIN                          (0)
  #define DDR_RAPL_LIMIT_PCU_LIMIT1_POWER_MAX                          (32767) // 0x00007FFF
  #define DDR_RAPL_LIMIT_PCU_LIMIT1_POWER_DEF                          (0x00000000)
  #define DDR_RAPL_LIMIT_PCU_LIMIT1_POWER_HSH                          (0x4F0058E0)

  #define DDR_RAPL_LIMIT_PCU_LIMIT1_ENABLE_OFF                         (15)
  #define DDR_RAPL_LIMIT_PCU_LIMIT1_ENABLE_WID                         ( 1)
  #define DDR_RAPL_LIMIT_PCU_LIMIT1_ENABLE_MSK                         (0x00008000)
  #define DDR_RAPL_LIMIT_PCU_LIMIT1_ENABLE_MIN                         (0)
  #define DDR_RAPL_LIMIT_PCU_LIMIT1_ENABLE_MAX                         (1) // 0x00000001
  #define DDR_RAPL_LIMIT_PCU_LIMIT1_ENABLE_DEF                         (0x00000000)
  #define DDR_RAPL_LIMIT_PCU_LIMIT1_ENABLE_HSH                         (0x411E58E0)

  #define DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_Y_OFF                  (17)
  #define DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_Y_WID                  ( 5)
  #define DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_Y_MSK                  (0x003E0000)
  #define DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_Y_MIN                  (0)
  #define DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_Y_MAX                  (31) // 0x0000001F
  #define DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_Y_DEF                  (0x00000000)
  #define DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_Y_HSH                  (0x452258E0)

  #define DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_X_OFF                  (22)
  #define DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_X_WID                  ( 2)
  #define DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_X_MSK                  (0x00C00000)
  #define DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_X_MIN                  (0)
  #define DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_X_MAX                  (3) // 0x00000003
  #define DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_X_DEF                  (0x00000000)
  #define DDR_RAPL_LIMIT_PCU_LIMIT1_TIME_WINDOW_X_HSH                  (0x422C58E0)

  #define DDR_RAPL_LIMIT_PCU_LIMIT2_POWER_OFF                          (32)
  #define DDR_RAPL_LIMIT_PCU_LIMIT2_POWER_WID                          (15)
  #define DDR_RAPL_LIMIT_PCU_LIMIT2_POWER_MSK                          (0x00007FFF00000000ULL)
  #define DDR_RAPL_LIMIT_PCU_LIMIT2_POWER_MIN                          (0)
  #define DDR_RAPL_LIMIT_PCU_LIMIT2_POWER_MAX                          (32767) // 0x00007FFF
  #define DDR_RAPL_LIMIT_PCU_LIMIT2_POWER_DEF                          (0x00000000)
  #define DDR_RAPL_LIMIT_PCU_LIMIT2_POWER_HSH                          (0x4F4058E0)

  #define DDR_RAPL_LIMIT_PCU_LIMIT2_ENABLE_OFF                         (47)
  #define DDR_RAPL_LIMIT_PCU_LIMIT2_ENABLE_WID                         ( 1)
  #define DDR_RAPL_LIMIT_PCU_LIMIT2_ENABLE_MSK                         (0x0000800000000000ULL)
  #define DDR_RAPL_LIMIT_PCU_LIMIT2_ENABLE_MIN                         (0)
  #define DDR_RAPL_LIMIT_PCU_LIMIT2_ENABLE_MAX                         (1) // 0x00000001
  #define DDR_RAPL_LIMIT_PCU_LIMIT2_ENABLE_DEF                         (0x00000000)
  #define DDR_RAPL_LIMIT_PCU_LIMIT2_ENABLE_HSH                         (0x415E58E0)

  #define DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_Y_OFF                  (49)
  #define DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_Y_WID                  ( 5)
  #define DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_Y_MSK                  (0x003E000000000000ULL)
  #define DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_Y_MIN                  (0)
  #define DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_Y_MAX                  (31) // 0x0000001F
  #define DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_Y_DEF                  (0x00000000)
  #define DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_Y_HSH                  (0x456258E0)

  #define DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_X_OFF                  (54)
  #define DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_X_WID                  ( 2)
  #define DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_X_MSK                  (0x00C0000000000000ULL)
  #define DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_X_MIN                  (0)
  #define DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_X_MAX                  (3) // 0x00000003
  #define DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_X_DEF                  (0x00000000)
  #define DDR_RAPL_LIMIT_PCU_LIMIT2_TIME_WINDOW_X_HSH                  (0x426C58E0)

  #define DDR_RAPL_LIMIT_PCU_LOCKED_OFF                                (63)
  #define DDR_RAPL_LIMIT_PCU_LOCKED_WID                                ( 1)
  #define DDR_RAPL_LIMIT_PCU_LOCKED_MSK                                (0x8000000000000000ULL)
  #define DDR_RAPL_LIMIT_PCU_LOCKED_MIN                                (0)
  #define DDR_RAPL_LIMIT_PCU_LOCKED_MAX                                (1) // 0x00000001
  #define DDR_RAPL_LIMIT_PCU_LOCKED_DEF                                (0x00000000)
  #define DDR_RAPL_LIMIT_PCU_LOCKED_HSH                                (0x417E58E0)

#define DDR_ENERGY_STATUS_PCU_REG                                      (0x000058E8)

  #define DDR_ENERGY_STATUS_PCU_JOULES_CONSUMED_OFF                    ( 0)
  #define DDR_ENERGY_STATUS_PCU_JOULES_CONSUMED_WID                    (32)
  #define DDR_ENERGY_STATUS_PCU_JOULES_CONSUMED_MSK                    (0xFFFFFFFF)
  #define DDR_ENERGY_STATUS_PCU_JOULES_CONSUMED_MIN                    (0)
  #define DDR_ENERGY_STATUS_PCU_JOULES_CONSUMED_MAX                    (4294967295) // 0xFFFFFFFF
  #define DDR_ENERGY_STATUS_PCU_JOULES_CONSUMED_DEF                    (0x00000000)
  #define DDR_ENERGY_STATUS_PCU_JOULES_CONSUMED_HSH                    (0x200058E8)

#define DDR_RAPL_PERF_STATUS_PCU_REG                                   (0x000058EC)

  #define DDR_RAPL_PERF_STATUS_PCU_DURATION_OFF                        ( 0)
  #define DDR_RAPL_PERF_STATUS_PCU_DURATION_WID                        (32)
  #define DDR_RAPL_PERF_STATUS_PCU_DURATION_MSK                        (0xFFFFFFFF)
  #define DDR_RAPL_PERF_STATUS_PCU_DURATION_MIN                        (0)
  #define DDR_RAPL_PERF_STATUS_PCU_DURATION_MAX                        (4294967295) // 0xFFFFFFFF
  #define DDR_RAPL_PERF_STATUS_PCU_DURATION_DEF                        (0x00000000)
  #define DDR_RAPL_PERF_STATUS_PCU_DURATION_HSH                        (0x200058EC)

#define PACKAGE_RAPL_PERF_STATUS_PCU_REG                               (0x000058F0)

  #define PACKAGE_RAPL_PERF_STATUS_PCU_COUNTS_OFF                      ( 0)
  #define PACKAGE_RAPL_PERF_STATUS_PCU_COUNTS_WID                      (32)
  #define PACKAGE_RAPL_PERF_STATUS_PCU_COUNTS_MSK                      (0xFFFFFFFF)
  #define PACKAGE_RAPL_PERF_STATUS_PCU_COUNTS_MIN                      (0)
  #define PACKAGE_RAPL_PERF_STATUS_PCU_COUNTS_MAX                      (4294967295) // 0xFFFFFFFF
  #define PACKAGE_RAPL_PERF_STATUS_PCU_COUNTS_DEF                      (0x00000000)
  #define PACKAGE_RAPL_PERF_STATUS_PCU_COUNTS_HSH                      (0x200058F0)

#define EDRAM_COST_ESTIMATE_PCU_REG                                    (0x00005908)

  #define EDRAM_COST_ESTIMATE_PCU_COST_ESTIMATE_OFF                    ( 0)
  #define EDRAM_COST_ESTIMATE_PCU_COST_ESTIMATE_WID                    (32)
  #define EDRAM_COST_ESTIMATE_PCU_COST_ESTIMATE_MSK                    (0xFFFFFFFF)
  #define EDRAM_COST_ESTIMATE_PCU_COST_ESTIMATE_MIN                    (0)
  #define EDRAM_COST_ESTIMATE_PCU_COST_ESTIMATE_MAX                    (4294967295) // 0xFFFFFFFF
  #define EDRAM_COST_ESTIMATE_PCU_COST_ESTIMATE_DEF                    (0x00000000)
  #define EDRAM_COST_ESTIMATE_PCU_COST_ESTIMATE_HSH                    (0x20005908)

#define EDRAM_STATUS_PCU_REG                                           (0x0000590C)

  #define EDRAM_STATUS_PCU_STATE_OFF                                   ( 0)
  #define EDRAM_STATUS_PCU_STATE_WID                                   ( 1)
  #define EDRAM_STATUS_PCU_STATE_MSK                                   (0x00000001)
  #define EDRAM_STATUS_PCU_STATE_MIN                                   (0)
  #define EDRAM_STATUS_PCU_STATE_MAX                                   (1) // 0x00000001
  #define EDRAM_STATUS_PCU_STATE_DEF                                   (0x00000000)
  #define EDRAM_STATUS_PCU_STATE_HSH                                   (0x0100590C)

  #define EDRAM_STATUS_PCU_POLICY_OFF                                  ( 1)
  #define EDRAM_STATUS_PCU_POLICY_WID                                  ( 1)
  #define EDRAM_STATUS_PCU_POLICY_MSK                                  (0x00000002)
  #define EDRAM_STATUS_PCU_POLICY_MIN                                  (0)
  #define EDRAM_STATUS_PCU_POLICY_MAX                                  (1) // 0x00000001
  #define EDRAM_STATUS_PCU_POLICY_DEF                                  (0x00000001)
  #define EDRAM_STATUS_PCU_POLICY_HSH                                  (0x0102590C)

  #define EDRAM_STATUS_PCU_EOPIO_LINK_SPEED_OFF                        ( 2)
  #define EDRAM_STATUS_PCU_EOPIO_LINK_SPEED_WID                        ( 1)
  #define EDRAM_STATUS_PCU_EOPIO_LINK_SPEED_MSK                        (0x00000004)
  #define EDRAM_STATUS_PCU_EOPIO_LINK_SPEED_MIN                        (0)
  #define EDRAM_STATUS_PCU_EOPIO_LINK_SPEED_MAX                        (1) // 0x00000001
  #define EDRAM_STATUS_PCU_EOPIO_LINK_SPEED_DEF                        (0x00000000)
  #define EDRAM_STATUS_PCU_EOPIO_LINK_SPEED_HSH                        (0x0104590C)

  #define EDRAM_STATUS_PCU_EOPIO_LINK_SPEED_CHANGE_AVAILABLE_OFF       ( 3)
  #define EDRAM_STATUS_PCU_EOPIO_LINK_SPEED_CHANGE_AVAILABLE_WID       ( 1)
  #define EDRAM_STATUS_PCU_EOPIO_LINK_SPEED_CHANGE_AVAILABLE_MSK       (0x00000008)
  #define EDRAM_STATUS_PCU_EOPIO_LINK_SPEED_CHANGE_AVAILABLE_MIN       (0)
  #define EDRAM_STATUS_PCU_EOPIO_LINK_SPEED_CHANGE_AVAILABLE_MAX       (1) // 0x00000001
  #define EDRAM_STATUS_PCU_EOPIO_LINK_SPEED_CHANGE_AVAILABLE_DEF       (0x00000000)
  #define EDRAM_STATUS_PCU_EOPIO_LINK_SPEED_CHANGE_AVAILABLE_HSH       (0x0106590C)

#define EDRAM_PERF_ESTIMATE_PCU_REG                                    (0x00005914)

  #define EDRAM_PERF_ESTIMATE_PCU_PERF_ESTIMATE_OFF                    ( 0)
  #define EDRAM_PERF_ESTIMATE_PCU_PERF_ESTIMATE_WID                    (32)
  #define EDRAM_PERF_ESTIMATE_PCU_PERF_ESTIMATE_MSK                    (0xFFFFFFFF)
  #define EDRAM_PERF_ESTIMATE_PCU_PERF_ESTIMATE_MIN                    (0)
  #define EDRAM_PERF_ESTIMATE_PCU_PERF_ESTIMATE_MAX                    (4294967295) // 0xFFFFFFFF
  #define EDRAM_PERF_ESTIMATE_PCU_PERF_ESTIMATE_DEF                    (0x00000000)
  #define EDRAM_PERF_ESTIMATE_PCU_PERF_ESTIMATE_HSH                    (0x20005914)

#define PRIP_TURBO_PLCY_PCU_REG                                        (0x00005920)

  #define PRIP_TURBO_PLCY_PCU_PRIPTP_OFF                               ( 0)
  #define PRIP_TURBO_PLCY_PCU_PRIPTP_WID                               ( 5)
  #define PRIP_TURBO_PLCY_PCU_PRIPTP_MSK                               (0x0000001F)
  #define PRIP_TURBO_PLCY_PCU_PRIPTP_MIN                               (0)
  #define PRIP_TURBO_PLCY_PCU_PRIPTP_MAX                               (31) // 0x0000001F
  #define PRIP_TURBO_PLCY_PCU_PRIPTP_DEF                               (0x00000000)
  #define PRIP_TURBO_PLCY_PCU_PRIPTP_HSH                               (0x05005920)

#define SECP_TURBO_PLCY_PCU_REG                                        (0x00005924)

  #define SECP_TURBO_PLCY_PCU_SECPTP_OFF                               ( 0)
  #define SECP_TURBO_PLCY_PCU_SECPTP_WID                               ( 5)
  #define SECP_TURBO_PLCY_PCU_SECPTP_MSK                               (0x0000001F)
  #define SECP_TURBO_PLCY_PCU_SECPTP_MIN                               (0)
  #define SECP_TURBO_PLCY_PCU_SECPTP_MAX                               (31) // 0x0000001F
  #define SECP_TURBO_PLCY_PCU_SECPTP_DEF                               (0x00000010)
  #define SECP_TURBO_PLCY_PCU_SECPTP_HSH                               (0x05005924)

#define PRIP_NRG_STTS_PCU_REG                                          (0x00005928)
//Duplicate of CAMARILLO_MAILBOX_DATA0_PCU_REG

#define SECP_NRG_STTS_PCU_REG                                          (0x0000592C)
//Duplicate of CAMARILLO_MAILBOX_DATA0_PCU_REG

#define PACKAGE_POWER_SKU_PCU_REG                                      (0x00005930)

  #define PACKAGE_POWER_SKU_PCU_PKG_TDP_OFF                            ( 0)
  #define PACKAGE_POWER_SKU_PCU_PKG_TDP_WID                            (15)
  #define PACKAGE_POWER_SKU_PCU_PKG_TDP_MSK                            (0x00007FFF)
  #define PACKAGE_POWER_SKU_PCU_PKG_TDP_MIN                            (0)
  #define PACKAGE_POWER_SKU_PCU_PKG_TDP_MAX                            (32767) // 0x00007FFF
  #define PACKAGE_POWER_SKU_PCU_PKG_TDP_DEF                            (0x00000118)
  #define PACKAGE_POWER_SKU_PCU_PKG_TDP_HSH                            (0x4F005930)

  #define PACKAGE_POWER_SKU_PCU_PKG_MIN_PWR_OFF                        (16)
  #define PACKAGE_POWER_SKU_PCU_PKG_MIN_PWR_WID                        (15)
  #define PACKAGE_POWER_SKU_PCU_PKG_MIN_PWR_MSK                        (0x7FFF0000)
  #define PACKAGE_POWER_SKU_PCU_PKG_MIN_PWR_MIN                        (0)
  #define PACKAGE_POWER_SKU_PCU_PKG_MIN_PWR_MAX                        (32767) // 0x00007FFF
  #define PACKAGE_POWER_SKU_PCU_PKG_MIN_PWR_DEF                        (0x00000060)
  #define PACKAGE_POWER_SKU_PCU_PKG_MIN_PWR_HSH                        (0x4F205930)

  #define PACKAGE_POWER_SKU_PCU_PKG_MAX_PWR_OFF                        (32)
  #define PACKAGE_POWER_SKU_PCU_PKG_MAX_PWR_WID                        (15)
  #define PACKAGE_POWER_SKU_PCU_PKG_MAX_PWR_MSK                        (0x00007FFF00000000ULL)
  #define PACKAGE_POWER_SKU_PCU_PKG_MAX_PWR_MIN                        (0)
  #define PACKAGE_POWER_SKU_PCU_PKG_MAX_PWR_MAX                        (32767) // 0x00007FFF
  #define PACKAGE_POWER_SKU_PCU_PKG_MAX_PWR_DEF                        (0x00000240)
  #define PACKAGE_POWER_SKU_PCU_PKG_MAX_PWR_HSH                        (0x4F405930)

  #define PACKAGE_POWER_SKU_PCU_PKG_MAX_WIN_OFF                        (48)
  #define PACKAGE_POWER_SKU_PCU_PKG_MAX_WIN_WID                        ( 7)
  #define PACKAGE_POWER_SKU_PCU_PKG_MAX_WIN_MSK                        (0x007F000000000000ULL)
  #define PACKAGE_POWER_SKU_PCU_PKG_MAX_WIN_MIN                        (0)
  #define PACKAGE_POWER_SKU_PCU_PKG_MAX_WIN_MAX                        (127) // 0x0000007F
  #define PACKAGE_POWER_SKU_PCU_PKG_MAX_WIN_DEF                        (0x00000012)
  #define PACKAGE_POWER_SKU_PCU_PKG_MAX_WIN_HSH                        (0x47605930)

#define PACKAGE_POWER_SKU_UNIT_PCU_REG                                 (0x00005938)

  #define PACKAGE_POWER_SKU_UNIT_PCU_PWR_UNIT_OFF                      ( 0)
  #define PACKAGE_POWER_SKU_UNIT_PCU_PWR_UNIT_WID                      ( 4)
  #define PACKAGE_POWER_SKU_UNIT_PCU_PWR_UNIT_MSK                      (0x0000000F)
  #define PACKAGE_POWER_SKU_UNIT_PCU_PWR_UNIT_MIN                      (0)
  #define PACKAGE_POWER_SKU_UNIT_PCU_PWR_UNIT_MAX                      (15) // 0x0000000F
  #define PACKAGE_POWER_SKU_UNIT_PCU_PWR_UNIT_DEF                      (0x00000003)
  #define PACKAGE_POWER_SKU_UNIT_PCU_PWR_UNIT_HSH                      (0x04005938)

  #define PACKAGE_POWER_SKU_UNIT_PCU_ENERGY_UNIT_OFF                   ( 8)
  #define PACKAGE_POWER_SKU_UNIT_PCU_ENERGY_UNIT_WID                   ( 5)
  #define PACKAGE_POWER_SKU_UNIT_PCU_ENERGY_UNIT_MSK                   (0x00001F00)
  #define PACKAGE_POWER_SKU_UNIT_PCU_ENERGY_UNIT_MIN                   (0)
  #define PACKAGE_POWER_SKU_UNIT_PCU_ENERGY_UNIT_MAX                   (31) // 0x0000001F
  #define PACKAGE_POWER_SKU_UNIT_PCU_ENERGY_UNIT_DEF                   (0x0000000E)
  #define PACKAGE_POWER_SKU_UNIT_PCU_ENERGY_UNIT_HSH                   (0x05105938)

  #define PACKAGE_POWER_SKU_UNIT_PCU_TIME_UNIT_OFF                     (16)
  #define PACKAGE_POWER_SKU_UNIT_PCU_TIME_UNIT_WID                     ( 4)
  #define PACKAGE_POWER_SKU_UNIT_PCU_TIME_UNIT_MSK                     (0x000F0000)
  #define PACKAGE_POWER_SKU_UNIT_PCU_TIME_UNIT_MIN                     (0)
  #define PACKAGE_POWER_SKU_UNIT_PCU_TIME_UNIT_MAX                     (15) // 0x0000000F
  #define PACKAGE_POWER_SKU_UNIT_PCU_TIME_UNIT_DEF                     (0x0000000A)
  #define PACKAGE_POWER_SKU_UNIT_PCU_TIME_UNIT_HSH                     (0x04205938)

#define PACKAGE_ENERGY_STATUS_PCU_REG                                  (0x0000593C)
//Duplicate of CAMARILLO_MAILBOX_DATA0_PCU_REG

#define EDRAM_TEMPERATURE_PCU_REG                                      (0x0000594C)

  #define EDRAM_TEMPERATURE_PCU_DATA_OFF                               ( 0)
  #define EDRAM_TEMPERATURE_PCU_DATA_WID                               ( 8)
  #define EDRAM_TEMPERATURE_PCU_DATA_MSK                               (0x000000FF)
  #define EDRAM_TEMPERATURE_PCU_DATA_MIN                               (0)
  #define EDRAM_TEMPERATURE_PCU_DATA_MAX                               (255) // 0x000000FF
  #define EDRAM_TEMPERATURE_PCU_DATA_DEF                               (0x00000000)
  #define EDRAM_TEMPERATURE_PCU_DATA_HSH                               (0x0800594C)

#define PLATFORM_ID_PCU_REG                                            (0x00005950)

  #define PLATFORM_ID_PCU_PLATFORMID_OFF                               (50)
  #define PLATFORM_ID_PCU_PLATFORMID_WID                               ( 3)
  #define PLATFORM_ID_PCU_PLATFORMID_MSK                               (0x001C000000000000ULL)
  #define PLATFORM_ID_PCU_PLATFORMID_MIN                               (0)
  #define PLATFORM_ID_PCU_PLATFORMID_MAX                               (7) // 0x00000007
  #define PLATFORM_ID_PCU_PLATFORMID_DEF                               (0x00000000)
  #define PLATFORM_ID_PCU_PLATFORMID_HSH                               (0x43645950)

#define PLATFORM_INFO_PCU_REG                                          (0x00005958)

  #define PLATFORM_INFO_PCU_MAX_NON_TURBO_LIM_RATIO_OFF                ( 8)
  #define PLATFORM_INFO_PCU_MAX_NON_TURBO_LIM_RATIO_WID                ( 8)
  #define PLATFORM_INFO_PCU_MAX_NON_TURBO_LIM_RATIO_MSK                (0x0000FF00)
  #define PLATFORM_INFO_PCU_MAX_NON_TURBO_LIM_RATIO_MIN                (0)
  #define PLATFORM_INFO_PCU_MAX_NON_TURBO_LIM_RATIO_MAX                (255) // 0x000000FF
  #define PLATFORM_INFO_PCU_MAX_NON_TURBO_LIM_RATIO_DEF                (0x00000000)
  #define PLATFORM_INFO_PCU_MAX_NON_TURBO_LIM_RATIO_HSH                (0x48105958)

  #define PLATFORM_INFO_PCU_SMM_SAVE_CAP_OFF                           (16)
  #define PLATFORM_INFO_PCU_SMM_SAVE_CAP_WID                           ( 1)
  #define PLATFORM_INFO_PCU_SMM_SAVE_CAP_MSK                           (0x00010000)
  #define PLATFORM_INFO_PCU_SMM_SAVE_CAP_MIN                           (0)
  #define PLATFORM_INFO_PCU_SMM_SAVE_CAP_MAX                           (1) // 0x00000001
  #define PLATFORM_INFO_PCU_SMM_SAVE_CAP_DEF                           (0x00000001)
  #define PLATFORM_INFO_PCU_SMM_SAVE_CAP_HSH                           (0x41205958)

  #define PLATFORM_INFO_PCU_PPIN_CAP_OFF                               (23)
  #define PLATFORM_INFO_PCU_PPIN_CAP_WID                               ( 1)
  #define PLATFORM_INFO_PCU_PPIN_CAP_MSK                               (0x00800000)
  #define PLATFORM_INFO_PCU_PPIN_CAP_MIN                               (0)
  #define PLATFORM_INFO_PCU_PPIN_CAP_MAX                               (1) // 0x00000001
  #define PLATFORM_INFO_PCU_PPIN_CAP_DEF                               (0x00000000)
  #define PLATFORM_INFO_PCU_PPIN_CAP_HSH                               (0x412E5958)

  #define PLATFORM_INFO_PCU_OCVOLT_OVRD_AVAIL_OFF                      (24)
  #define PLATFORM_INFO_PCU_OCVOLT_OVRD_AVAIL_WID                      ( 1)
  #define PLATFORM_INFO_PCU_OCVOLT_OVRD_AVAIL_MSK                      (0x01000000)
  #define PLATFORM_INFO_PCU_OCVOLT_OVRD_AVAIL_MIN                      (0)
  #define PLATFORM_INFO_PCU_OCVOLT_OVRD_AVAIL_MAX                      (1) // 0x00000001
  #define PLATFORM_INFO_PCU_OCVOLT_OVRD_AVAIL_DEF                      (0x00000000)
  #define PLATFORM_INFO_PCU_OCVOLT_OVRD_AVAIL_HSH                      (0x41305958)

  #define PLATFORM_INFO_PCU_DCU_16K_MODE_AVAIL_OFF                     (26)
  #define PLATFORM_INFO_PCU_DCU_16K_MODE_AVAIL_WID                     ( 1)
  #define PLATFORM_INFO_PCU_DCU_16K_MODE_AVAIL_MSK                     (0x04000000)
  #define PLATFORM_INFO_PCU_DCU_16K_MODE_AVAIL_MIN                     (0)
  #define PLATFORM_INFO_PCU_DCU_16K_MODE_AVAIL_MAX                     (1) // 0x00000001
  #define PLATFORM_INFO_PCU_DCU_16K_MODE_AVAIL_DEF                     (0x00000000)
  #define PLATFORM_INFO_PCU_DCU_16K_MODE_AVAIL_HSH                     (0x41345958)

  #define PLATFORM_INFO_PCU_SAMPLE_PART_OFF                            (27)
  #define PLATFORM_INFO_PCU_SAMPLE_PART_WID                            ( 1)
  #define PLATFORM_INFO_PCU_SAMPLE_PART_MSK                            (0x08000000)
  #define PLATFORM_INFO_PCU_SAMPLE_PART_MIN                            (0)
  #define PLATFORM_INFO_PCU_SAMPLE_PART_MAX                            (1) // 0x00000001
  #define PLATFORM_INFO_PCU_SAMPLE_PART_DEF                            (0x00000000)
  #define PLATFORM_INFO_PCU_SAMPLE_PART_HSH                            (0x41365958)

  #define PLATFORM_INFO_PCU_PRG_TURBO_RATIO_EN_OFF                     (28)
  #define PLATFORM_INFO_PCU_PRG_TURBO_RATIO_EN_WID                     ( 1)
  #define PLATFORM_INFO_PCU_PRG_TURBO_RATIO_EN_MSK                     (0x10000000)
  #define PLATFORM_INFO_PCU_PRG_TURBO_RATIO_EN_MIN                     (0)
  #define PLATFORM_INFO_PCU_PRG_TURBO_RATIO_EN_MAX                     (1) // 0x00000001
  #define PLATFORM_INFO_PCU_PRG_TURBO_RATIO_EN_DEF                     (0x00000001)
  #define PLATFORM_INFO_PCU_PRG_TURBO_RATIO_EN_HSH                     (0x41385958)

  #define PLATFORM_INFO_PCU_PRG_TDP_LIM_EN_OFF                         (29)
  #define PLATFORM_INFO_PCU_PRG_TDP_LIM_EN_WID                         ( 1)
  #define PLATFORM_INFO_PCU_PRG_TDP_LIM_EN_MSK                         (0x20000000)
  #define PLATFORM_INFO_PCU_PRG_TDP_LIM_EN_MIN                         (0)
  #define PLATFORM_INFO_PCU_PRG_TDP_LIM_EN_MAX                         (1) // 0x00000001
  #define PLATFORM_INFO_PCU_PRG_TDP_LIM_EN_DEF                         (0x00000001)
  #define PLATFORM_INFO_PCU_PRG_TDP_LIM_EN_HSH                         (0x413A5958)

  #define PLATFORM_INFO_PCU_PRG_TJ_OFFSET_EN_OFF                       (30)
  #define PLATFORM_INFO_PCU_PRG_TJ_OFFSET_EN_WID                       ( 1)
  #define PLATFORM_INFO_PCU_PRG_TJ_OFFSET_EN_MSK                       (0x40000000)
  #define PLATFORM_INFO_PCU_PRG_TJ_OFFSET_EN_MIN                       (0)
  #define PLATFORM_INFO_PCU_PRG_TJ_OFFSET_EN_MAX                       (1) // 0x00000001
  #define PLATFORM_INFO_PCU_PRG_TJ_OFFSET_EN_DEF                       (0x00000001)
  #define PLATFORM_INFO_PCU_PRG_TJ_OFFSET_EN_HSH                       (0x413C5958)

  #define PLATFORM_INFO_PCU_CPUID_FAULTING_EN_OFF                      (31)
  #define PLATFORM_INFO_PCU_CPUID_FAULTING_EN_WID                      ( 1)
  #define PLATFORM_INFO_PCU_CPUID_FAULTING_EN_MSK                      (0x80000000)
  #define PLATFORM_INFO_PCU_CPUID_FAULTING_EN_MIN                      (0)
  #define PLATFORM_INFO_PCU_CPUID_FAULTING_EN_MAX                      (1) // 0x00000001
  #define PLATFORM_INFO_PCU_CPUID_FAULTING_EN_DEF                      (0x00000001)
  #define PLATFORM_INFO_PCU_CPUID_FAULTING_EN_HSH                      (0x413E5958)

  #define PLATFORM_INFO_PCU_LPM_SUPPORT_OFF                            (32)
  #define PLATFORM_INFO_PCU_LPM_SUPPORT_WID                            ( 1)
  #define PLATFORM_INFO_PCU_LPM_SUPPORT_MSK                            (0x0000000100000000ULL)
  #define PLATFORM_INFO_PCU_LPM_SUPPORT_MIN                            (0)
  #define PLATFORM_INFO_PCU_LPM_SUPPORT_MAX                            (1) // 0x00000001
  #define PLATFORM_INFO_PCU_LPM_SUPPORT_DEF                            (0x00000000)
  #define PLATFORM_INFO_PCU_LPM_SUPPORT_HSH                            (0x41405958)

  #define PLATFORM_INFO_PCU_CONFIG_TDP_LEVELS_OFF                      (33)
  #define PLATFORM_INFO_PCU_CONFIG_TDP_LEVELS_WID                      ( 2)
  #define PLATFORM_INFO_PCU_CONFIG_TDP_LEVELS_MSK                      (0x0000000600000000ULL)
  #define PLATFORM_INFO_PCU_CONFIG_TDP_LEVELS_MIN                      (0)
  #define PLATFORM_INFO_PCU_CONFIG_TDP_LEVELS_MAX                      (3) // 0x00000003
  #define PLATFORM_INFO_PCU_CONFIG_TDP_LEVELS_DEF                      (0x00000000)
  #define PLATFORM_INFO_PCU_CONFIG_TDP_LEVELS_HSH                      (0x42425958)

  #define PLATFORM_INFO_PCU_PFAT_ENABLE_OFF                            (35)
  #define PLATFORM_INFO_PCU_PFAT_ENABLE_WID                            ( 1)
  #define PLATFORM_INFO_PCU_PFAT_ENABLE_MSK                            (0x0000000800000000ULL)
  #define PLATFORM_INFO_PCU_PFAT_ENABLE_MIN                            (0)
  #define PLATFORM_INFO_PCU_PFAT_ENABLE_MAX                            (1) // 0x00000001
  #define PLATFORM_INFO_PCU_PFAT_ENABLE_DEF                            (0x00000000)
  #define PLATFORM_INFO_PCU_PFAT_ENABLE_HSH                            (0x41465958)

  #define PLATFORM_INFO_PCU_PEG2DMIDIS_EN_OFF                          (36)
  #define PLATFORM_INFO_PCU_PEG2DMIDIS_EN_WID                          ( 1)
  #define PLATFORM_INFO_PCU_PEG2DMIDIS_EN_MSK                          (0x0000001000000000ULL)
  #define PLATFORM_INFO_PCU_PEG2DMIDIS_EN_MIN                          (0)
  #define PLATFORM_INFO_PCU_PEG2DMIDIS_EN_MAX                          (1) // 0x00000001
  #define PLATFORM_INFO_PCU_PEG2DMIDIS_EN_DEF                          (0x00000001)
  #define PLATFORM_INFO_PCU_PEG2DMIDIS_EN_HSH                          (0x41485958)

  #define PLATFORM_INFO_PCU_TIMED_MWAIT_ENABLE_OFF                     (37)
  #define PLATFORM_INFO_PCU_TIMED_MWAIT_ENABLE_WID                     ( 1)
  #define PLATFORM_INFO_PCU_TIMED_MWAIT_ENABLE_MSK                     (0x0000002000000000ULL)
  #define PLATFORM_INFO_PCU_TIMED_MWAIT_ENABLE_MIN                     (0)
  #define PLATFORM_INFO_PCU_TIMED_MWAIT_ENABLE_MAX                     (1) // 0x00000001
  #define PLATFORM_INFO_PCU_TIMED_MWAIT_ENABLE_DEF                     (0x00000000)
  #define PLATFORM_INFO_PCU_TIMED_MWAIT_ENABLE_HSH                     (0x414A5958)

  #define PLATFORM_INFO_PCU_MAX_EFFICIENCY_RATIO_OFF                   (40)
  #define PLATFORM_INFO_PCU_MAX_EFFICIENCY_RATIO_WID                   ( 8)
  #define PLATFORM_INFO_PCU_MAX_EFFICIENCY_RATIO_MSK                   (0x0000FF0000000000ULL)
  #define PLATFORM_INFO_PCU_MAX_EFFICIENCY_RATIO_MIN                   (0)
  #define PLATFORM_INFO_PCU_MAX_EFFICIENCY_RATIO_MAX                   (255) // 0x000000FF
  #define PLATFORM_INFO_PCU_MAX_EFFICIENCY_RATIO_DEF                   (0x00000000)
  #define PLATFORM_INFO_PCU_MAX_EFFICIENCY_RATIO_HSH                   (0x48505958)

  #define PLATFORM_INFO_PCU_MIN_OPERATING_RATIO_OFF                    (48)
  #define PLATFORM_INFO_PCU_MIN_OPERATING_RATIO_WID                    ( 8)
  #define PLATFORM_INFO_PCU_MIN_OPERATING_RATIO_MSK                    (0x00FF000000000000ULL)
  #define PLATFORM_INFO_PCU_MIN_OPERATING_RATIO_MIN                    (0)
  #define PLATFORM_INFO_PCU_MIN_OPERATING_RATIO_MAX                    (255) // 0x000000FF
  #define PLATFORM_INFO_PCU_MIN_OPERATING_RATIO_DEF                    (0x00000008)
  #define PLATFORM_INFO_PCU_MIN_OPERATING_RATIO_HSH                    (0x48605958)

  #define PLATFORM_INFO_PCU_PushPatch_EN_OFF                           (56)
  #define PLATFORM_INFO_PCU_PushPatch_EN_WID                           ( 1)
  #define PLATFORM_INFO_PCU_PushPatch_EN_MSK                           (0x0100000000000000ULL)
  #define PLATFORM_INFO_PCU_PushPatch_EN_MIN                           (0)
  #define PLATFORM_INFO_PCU_PushPatch_EN_MAX                           (1) // 0x00000001
  #define PLATFORM_INFO_PCU_PushPatch_EN_DEF                           (0x00000000)
  #define PLATFORM_INFO_PCU_PushPatch_EN_HSH                           (0x41705958)

  #define PLATFORM_INFO_PCU_EDRAM_ENABLE_OFF                           (57)
  #define PLATFORM_INFO_PCU_EDRAM_ENABLE_WID                           ( 1)
  #define PLATFORM_INFO_PCU_EDRAM_ENABLE_MSK                           (0x0200000000000000ULL)
  #define PLATFORM_INFO_PCU_EDRAM_ENABLE_MIN                           (0)
  #define PLATFORM_INFO_PCU_EDRAM_ENABLE_MAX                           (1) // 0x00000001
  #define PLATFORM_INFO_PCU_EDRAM_ENABLE_DEF                           (0x00000000)
  #define PLATFORM_INFO_PCU_EDRAM_ENABLE_HSH                           (0x41725958)

  #define PLATFORM_INFO_PCU_SXP_2LM_EN_OFF                             (58)
  #define PLATFORM_INFO_PCU_SXP_2LM_EN_WID                             ( 1)
  #define PLATFORM_INFO_PCU_SXP_2LM_EN_MSK                             (0x0400000000000000ULL)
  #define PLATFORM_INFO_PCU_SXP_2LM_EN_MIN                             (0)
  #define PLATFORM_INFO_PCU_SXP_2LM_EN_MAX                             (1) // 0x00000001
  #define PLATFORM_INFO_PCU_SXP_2LM_EN_DEF                             (0x00000000)
  #define PLATFORM_INFO_PCU_SXP_2LM_EN_HSH                             (0x41745958)

  #define PLATFORM_INFO_PCU_SMM_SUPOVR_STATE_LOCK_ENABLE_OFF           (59)
  #define PLATFORM_INFO_PCU_SMM_SUPOVR_STATE_LOCK_ENABLE_WID           ( 1)
  #define PLATFORM_INFO_PCU_SMM_SUPOVR_STATE_LOCK_ENABLE_MSK           (0x0800000000000000ULL)
  #define PLATFORM_INFO_PCU_SMM_SUPOVR_STATE_LOCK_ENABLE_MIN           (0)
  #define PLATFORM_INFO_PCU_SMM_SUPOVR_STATE_LOCK_ENABLE_MAX           (1) // 0x00000001
  #define PLATFORM_INFO_PCU_SMM_SUPOVR_STATE_LOCK_ENABLE_DEF           (0x00000000)
  #define PLATFORM_INFO_PCU_SMM_SUPOVR_STATE_LOCK_ENABLE_HSH           (0x41765958)

  #define PLATFORM_INFO_PCU_TIO_ENABLE_OFF                             (60)
  #define PLATFORM_INFO_PCU_TIO_ENABLE_WID                             ( 1)
  #define PLATFORM_INFO_PCU_TIO_ENABLE_MSK                             (0x1000000000000000ULL)
  #define PLATFORM_INFO_PCU_TIO_ENABLE_MIN                             (0)
  #define PLATFORM_INFO_PCU_TIO_ENABLE_MAX                             (1) // 0x00000001
  #define PLATFORM_INFO_PCU_TIO_ENABLE_DEF                             (0x00000000)
  #define PLATFORM_INFO_PCU_TIO_ENABLE_HSH                             (0x41785958)

#define PACKAGE_TEMPERATURE_PCU_REG                                    (0x00005978)
//Duplicate of EDRAM_TEMPERATURE_PCU_REG

#define PP0_TEMPERATURE_PCU_REG                                        (0x0000597C)
//Duplicate of EDRAM_TEMPERATURE_PCU_REG

#define PP1_TEMPERATURE_PCU_REG                                        (0x00005980)
//Duplicate of EDRAM_TEMPERATURE_PCU_REG

#define DEVICE_SHARED_IDLE_DURATION_PCU_REG                            (0x00005988)

  #define DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_OFF                 ( 0)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_WID                 ( 1)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_MSK                 (0x00000001)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_MIN                 (0)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_MAX                 (1) // 0x00000001
  #define DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_DEF                 (0x00000000)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_HSH                 (0x01005988)

  #define DEVICE_SHARED_IDLE_DURATION_PCU_VALID_OFF                    ( 1)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_VALID_WID                    ( 1)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_VALID_MSK                    (0x00000002)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_VALID_MIN                    (0)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_VALID_MAX                    (1) // 0x00000001
  #define DEVICE_SHARED_IDLE_DURATION_PCU_VALID_DEF                    (0x00000000)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_VALID_HSH                    (0x01025988)

  #define DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_BITS_OFF            ( 2)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_BITS_WID            ( 4)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_BITS_MSK            (0x0000003C)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_BITS_MIN            (0)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_BITS_MAX            (15) // 0x0000000F
  #define DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_BITS_DEF            (0x00000000)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_RESERVED_BITS_HSH            (0x04045988)

  #define DEVICE_SHARED_IDLE_DURATION_PCU_OD_OFF                       ( 6)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_OD_WID                       ( 1)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_OD_MSK                       (0x00000040)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_OD_MIN                       (0)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_OD_MAX                       (1) // 0x00000001
  #define DEVICE_SHARED_IDLE_DURATION_PCU_OD_DEF                       (0x00000000)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_OD_HSH                       (0x010C5988)

  #define DEVICE_SHARED_IDLE_DURATION_PCU_IM_OFF                       ( 7)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_IM_WID                       ( 1)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_IM_MSK                       (0x00000080)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_IM_MIN                       (0)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_IM_MAX                       (1) // 0x00000001
  #define DEVICE_SHARED_IDLE_DURATION_PCU_IM_DEF                       (0x00000000)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_IM_HSH                       (0x010E5988)

  #define DEVICE_SHARED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_OFF     ( 8)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_WID     (21)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_MSK     (0x1FFFFF00)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_MIN     (0)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_MAX     (2097151) // 0x001FFFFF
  #define DEVICE_SHARED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_DEF     (0x00000000)
  #define DEVICE_SHARED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_HSH     (0x15105988)

#define DEVICE_DEDICATED_IDLE_DURATION_PCU_REG                         (0x0000598C)

  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_USED_OFF                  ( 0)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_USED_WID                  ( 1)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_USED_MSK                  (0x00000001)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_USED_MIN                  (0)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_USED_MAX                  (1) // 0x00000001
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_USED_DEF                  (0x00000000)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_USED_HSH                  (0x0100598C)

  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_VALID_OFF                 ( 1)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_VALID_WID                 ( 1)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_VALID_MSK                 (0x00000002)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_VALID_MIN                 (0)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_VALID_MAX                 (1) // 0x00000001
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_VALID_DEF                 (0x00000000)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_VALID_HSH                 (0x0102598C)

  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_RESERVED_BITS_OFF         ( 2)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_RESERVED_BITS_WID         ( 4)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_RESERVED_BITS_MSK         (0x0000003C)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_RESERVED_BITS_MIN         (0)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_RESERVED_BITS_MAX         (15) // 0x0000000F
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_RESERVED_BITS_DEF         (0x00000000)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_RESERVED_BITS_HSH         (0x0404598C)

  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_OD_OFF                    ( 6)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_OD_WID                    ( 1)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_OD_MSK                    (0x00000040)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_OD_MIN                    (0)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_OD_MAX                    (1) // 0x00000001
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_OD_DEF                    (0x00000000)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_OD_HSH                    (0x010C598C)

  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_IM_OFF                    ( 7)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_IM_WID                    ( 1)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_IM_MSK                    (0x00000080)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_IM_MIN                    (0)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_IM_MAX                    (1) // 0x00000001
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_IM_DEF                    (0x00000000)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_IM_HSH                    (0x010E598C)

  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_OFF  ( 8)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_WID  (21)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_MSK  (0x1FFFFF00)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_MIN  (0)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_MAX  (2097151) // 0x001FFFFF
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_DEF  (0x00000000)
  #define DEVICE_DEDICATED_IDLE_DURATION_PCU_NEXT_DEVICE_ACTIVITY_HSH  (0x1510598C)

#define RP_STATE_LIMITS_PCU_REG                                        (0x00005994)

  #define RP_STATE_LIMITS_PCU_RPSTT_LIM_OFF                            ( 0)
  #define RP_STATE_LIMITS_PCU_RPSTT_LIM_WID                            ( 8)
  #define RP_STATE_LIMITS_PCU_RPSTT_LIM_MSK                            (0x000000FF)
  #define RP_STATE_LIMITS_PCU_RPSTT_LIM_MIN                            (0)
  #define RP_STATE_LIMITS_PCU_RPSTT_LIM_MAX                            (255) // 0x000000FF
  #define RP_STATE_LIMITS_PCU_RPSTT_LIM_DEF                            (0x000000FF)
  #define RP_STATE_LIMITS_PCU_RPSTT_LIM_HSH                            (0x08005994)

#define PACKAGE_RAPL_LIMIT_PCU_REG                                     (0x000059A0)

  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_OFF                     ( 0)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_WID                     (15)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_MSK                     (0x00007FFF)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_MIN                     (0)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_MAX                     (32767) // 0x00007FFF
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_DEF                     (0x00000000)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_HSH                     (0x4F0059A0)

  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_EN_OFF                  (15)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_EN_WID                  ( 1)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_EN_MSK                  (0x00008000)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_EN_MIN                  (0)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_EN_MAX                  (1) // 0x00000001
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_EN_DEF                  (0x00000000)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_EN_HSH                  (0x411E59A0)

  #define PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_1_OFF                    (16)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_1_WID                    ( 1)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_1_MSK                    (0x00010000)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_1_MIN                    (0)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_1_MAX                    (1) // 0x00000001
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_1_DEF                    (0x00000000)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_1_HSH                    (0x412059A0)

  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_TIME_OFF                (17)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_TIME_WID                ( 7)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_TIME_MSK                (0x00FE0000)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_TIME_MIN                (0)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_TIME_MAX                (127) // 0x0000007F
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_TIME_DEF                (0x00000000)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_1_TIME_HSH                (0x472259A0)

  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_OFF                     (32)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_WID                     (15)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_MSK                     (0x00007FFF00000000ULL)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_MIN                     (0)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_MAX                     (32767) // 0x00007FFF
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_DEF                     (0x00000000)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_HSH                     (0x4F4059A0)

  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_EN_OFF                  (47)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_EN_WID                  ( 1)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_EN_MSK                  (0x0000800000000000ULL)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_EN_MIN                  (0)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_EN_MAX                  (1) // 0x00000001
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_EN_DEF                  (0x00000000)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_EN_HSH                  (0x415E59A0)

  #define PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_2_OFF                    (48)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_2_WID                    ( 1)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_2_MSK                    (0x0001000000000000ULL)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_2_MIN                    (0)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_2_MAX                    (1) // 0x00000001
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_2_DEF                    (0x00000000)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_CLMP_LIM_2_HSH                    (0x416059A0)

  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_TIME_OFF                (49)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_TIME_WID                ( 7)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_TIME_MSK                (0x00FE000000000000ULL)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_TIME_MIN                (0)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_TIME_MAX                (127) // 0x0000007F
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_TIME_DEF                (0x00000000)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_2_TIME_HSH                (0x476259A0)

  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_LOCK_OFF                  (63)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_LOCK_WID                  ( 1)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_LOCK_MSK                  (0x8000000000000000ULL)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_LOCK_MIN                  (0)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_LOCK_MAX                  (1) // 0x00000001
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_LOCK_DEF                  (0x00000000)
  #define PACKAGE_RAPL_LIMIT_PCU_PKG_PWR_LIM_LOCK_HSH                  (0x417E59A0)

#define PRIP_TURBO_PWR_LIM_PCU_REG                                     (0x000059A8)

  #define PRIP_TURBO_PWR_LIM_PCU_IA_PP_PWR_LIM_OFF                     ( 0)
  #define PRIP_TURBO_PWR_LIM_PCU_IA_PP_PWR_LIM_WID                     (15)
  #define PRIP_TURBO_PWR_LIM_PCU_IA_PP_PWR_LIM_MSK                     (0x00007FFF)
  #define PRIP_TURBO_PWR_LIM_PCU_IA_PP_PWR_LIM_MIN                     (0)
  #define PRIP_TURBO_PWR_LIM_PCU_IA_PP_PWR_LIM_MAX                     (32767) // 0x00007FFF
  #define PRIP_TURBO_PWR_LIM_PCU_IA_PP_PWR_LIM_DEF                     (0x00000000)
  #define PRIP_TURBO_PWR_LIM_PCU_IA_PP_PWR_LIM_HSH                     (0x0F0059A8)

  #define PRIP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_OFF                   (15)
  #define PRIP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_WID                   ( 1)
  #define PRIP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_MSK                   (0x00008000)
  #define PRIP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_MIN                   (0)
  #define PRIP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_MAX                   (1) // 0x00000001
  #define PRIP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_DEF                   (0x00000000)
  #define PRIP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_HSH                   (0x011E59A8)

  #define PRIP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_OFF                      (16)
  #define PRIP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_WID                      ( 1)
  #define PRIP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_MSK                      (0x00010000)
  #define PRIP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_MIN                      (0)
  #define PRIP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_MAX                      (1) // 0x00000001
  #define PRIP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_DEF                      (0x00000000)
  #define PRIP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_HSH                      (0x012059A8)

  #define PRIP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_OFF                     (17)
  #define PRIP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_WID                     ( 7)
  #define PRIP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_MSK                     (0x00FE0000)
  #define PRIP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_MIN                     (0)
  #define PRIP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_MAX                     (127) // 0x0000007F
  #define PRIP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_DEF                     (0x00000000)
  #define PRIP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_HSH                     (0x072259A8)

  #define PRIP_TURBO_PWR_LIM_PCU_PP_PWR_LIM_LOCK_OFF                   (31)
  #define PRIP_TURBO_PWR_LIM_PCU_PP_PWR_LIM_LOCK_WID                   ( 1)
  #define PRIP_TURBO_PWR_LIM_PCU_PP_PWR_LIM_LOCK_MSK                   (0x80000000)
  #define PRIP_TURBO_PWR_LIM_PCU_PP_PWR_LIM_LOCK_MIN                   (0)
  #define PRIP_TURBO_PWR_LIM_PCU_PP_PWR_LIM_LOCK_MAX                   (1) // 0x00000001
  #define PRIP_TURBO_PWR_LIM_PCU_PP_PWR_LIM_LOCK_DEF                   (0x00000000)
  #define PRIP_TURBO_PWR_LIM_PCU_PP_PWR_LIM_LOCK_HSH                   (0x013E59A8)

#define SECP_TURBO_PWR_LIM_PCU_REG                                     (0x000059AC)

  #define SECP_TURBO_PWR_LIM_PCU_NON_IA_PP_PWR_LIM_OFF                 ( 0)
  #define SECP_TURBO_PWR_LIM_PCU_NON_IA_PP_PWR_LIM_WID                 (15)
  #define SECP_TURBO_PWR_LIM_PCU_NON_IA_PP_PWR_LIM_MSK                 (0x00007FFF)
  #define SECP_TURBO_PWR_LIM_PCU_NON_IA_PP_PWR_LIM_MIN                 (0)
  #define SECP_TURBO_PWR_LIM_PCU_NON_IA_PP_PWR_LIM_MAX                 (32767) // 0x00007FFF
  #define SECP_TURBO_PWR_LIM_PCU_NON_IA_PP_PWR_LIM_DEF                 (0x00000000)
  #define SECP_TURBO_PWR_LIM_PCU_NON_IA_PP_PWR_LIM_HSH                 (0x0F0059AC)

  #define SECP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_OFF                   (15)
  #define SECP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_WID                   ( 1)
  #define SECP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_MSK                   (0x00008000)
  #define SECP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_MIN                   (0)
  #define SECP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_MAX                   (1) // 0x00000001
  #define SECP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_DEF                   (0x00000000)
  #define SECP_TURBO_PWR_LIM_PCU_PWR_LIM_CTRL_EN_HSH                   (0x011E59AC)

  #define SECP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_OFF                      (16)
  #define SECP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_WID                      ( 1)
  #define SECP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_MSK                      (0x00010000)
  #define SECP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_MIN                      (0)
  #define SECP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_MAX                      (1) // 0x00000001
  #define SECP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_DEF                      (0x00000000)
  #define SECP_TURBO_PWR_LIM_PCU_PP_CLAMP_LIM_HSH                      (0x012059AC)

  #define SECP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_OFF                     (17)
  #define SECP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_WID                     ( 7)
  #define SECP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_MSK                     (0x00FE0000)
  #define SECP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_MIN                     (0)
  #define SECP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_MAX                     (127) // 0x0000007F
  #define SECP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_DEF                     (0x00000000)
  #define SECP_TURBO_PWR_LIM_PCU_CTRL_TIME_WIN_HSH                     (0x072259AC)

  #define SECP_TURBO_PWR_LIM_PCU_SP_PWR_LIM_LOCK_OFF                   (31)
  #define SECP_TURBO_PWR_LIM_PCU_SP_PWR_LIM_LOCK_WID                   ( 1)
  #define SECP_TURBO_PWR_LIM_PCU_SP_PWR_LIM_LOCK_MSK                   (0x80000000)
  #define SECP_TURBO_PWR_LIM_PCU_SP_PWR_LIM_LOCK_MIN                   (0)
  #define SECP_TURBO_PWR_LIM_PCU_SP_PWR_LIM_LOCK_MAX                   (1) // 0x00000001
  #define SECP_TURBO_PWR_LIM_PCU_SP_PWR_LIM_LOCK_DEF                   (0x00000000)
  #define SECP_TURBO_PWR_LIM_PCU_SP_PWR_LIM_LOCK_HSH                   (0x013E59AC)

#define MRC_ODT_POWER_SAVING_PCU_REG                                   (0x000059B8)

  #define MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Rd_OFF                   ( 0)
  #define MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Rd_WID                   ( 8)
  #define MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Rd_MSK                   (0x000000FF)
  #define MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Rd_MIN                   (0)
  #define MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Rd_MAX                   (255) // 0x000000FF
  #define MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Rd_DEF                   (0x00000000)
  #define MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Rd_HSH                   (0x080059B8)

  #define MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Wt_OFF                   ( 8)
  #define MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Wt_WID                   ( 8)
  #define MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Wt_MSK                   (0x0000FF00)
  #define MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Wt_MIN                   (0)
  #define MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Wt_MAX                   (255) // 0x000000FF
  #define MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Wt_DEF                   (0x00000000)
  #define MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Wt_HSH                   (0x081059B8)

  #define MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Cmd_OFF                  (16)
  #define MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Cmd_WID                  ( 8)
  #define MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Cmd_MSK                  (0x00FF0000)
  #define MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Cmd_MIN                  (0)
  #define MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Cmd_MAX                  (255) // 0x000000FF
  #define MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Cmd_DEF                  (0x00000000)
  #define MRC_ODT_POWER_SAVING_PCU_MRC_Saving_Cmd_HSH                  (0x082059B8)

  #define MRC_ODT_POWER_SAVING_PCU_RESERVED_OFF                        (24)
  #define MRC_ODT_POWER_SAVING_PCU_RESERVED_WID                        ( 8)
  #define MRC_ODT_POWER_SAVING_PCU_RESERVED_MSK                        (0xFF000000)
  #define MRC_ODT_POWER_SAVING_PCU_RESERVED_MIN                        (0)
  #define MRC_ODT_POWER_SAVING_PCU_RESERVED_MAX                        (255) // 0x000000FF
  #define MRC_ODT_POWER_SAVING_PCU_RESERVED_DEF                        (0x00000000)
  #define MRC_ODT_POWER_SAVING_PCU_RESERVED_HSH                        (0x083059B8)

#define DEVICE_IDLE_DURATION_OVERRIDE_PCU_REG                          (0x000059C8)

  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_OFF               ( 0)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_WID               ( 1)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_MSK               (0x00000001)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_MIN               (0)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_MAX               (1) // 0x00000001
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_DEF               (0x00000000)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_HSH               (0x010059C8)

  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_VALID_OFF                  ( 1)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_VALID_WID                  ( 1)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_VALID_MSK                  (0x00000002)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_VALID_MIN                  (0)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_VALID_MAX                  (1) // 0x00000001
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_VALID_DEF                  (0x00000000)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_VALID_HSH                  (0x010259C8)

  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_BITS_OFF          ( 2)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_BITS_WID          ( 4)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_BITS_MSK          (0x0000003C)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_BITS_MIN          (0)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_BITS_MAX          (15) // 0x0000000F
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_BITS_DEF          (0x00000000)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_RESERVED_BITS_HSH          (0x040459C8)

  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_OD_OFF                     ( 6)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_OD_WID                     ( 1)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_OD_MSK                     (0x00000040)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_OD_MIN                     (0)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_OD_MAX                     (1) // 0x00000001
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_OD_DEF                     (0x00000000)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_OD_HSH                     (0x010C59C8)

  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_IM_OFF                     ( 7)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_IM_WID                     ( 1)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_IM_MSK                     (0x00000080)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_IM_MIN                     (0)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_IM_MAX                     (1) // 0x00000001
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_IM_DEF                     (0x00000000)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_IM_HSH                     (0x010E59C8)

  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_NEXT_DEVICE_ACTIVITY_OFF   ( 8)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_NEXT_DEVICE_ACTIVITY_WID   (21)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_NEXT_DEVICE_ACTIVITY_MSK   (0x1FFFFF00)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_NEXT_DEVICE_ACTIVITY_MIN   (0)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_NEXT_DEVICE_ACTIVITY_MAX   (2097151) // 0x001FFFFF
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_NEXT_DEVICE_ACTIVITY_DEF   (0x00000000)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_NEXT_DEVICE_ACTIVITY_HSH   (0x151059C8)

  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_DISABLE_MDID_EVALUATION_OFF (29)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_DISABLE_MDID_EVALUATION_WID ( 1)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_DISABLE_MDID_EVALUATION_MSK (0x20000000)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_DISABLE_MDID_EVALUATION_MIN (0)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_DISABLE_MDID_EVALUATION_MAX (1) // 0x00000001
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_DISABLE_MDID_EVALUATION_DEF (0x00000000)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_DISABLE_MDID_EVALUATION_HSH (0x013A59C8)

  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_FORCE_MDID_OVERRIDE_OFF    (30)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_FORCE_MDID_OVERRIDE_WID    ( 1)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_FORCE_MDID_OVERRIDE_MSK    (0x40000000)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_FORCE_MDID_OVERRIDE_MIN    (0)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_FORCE_MDID_OVERRIDE_MAX    (1) // 0x00000001
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_FORCE_MDID_OVERRIDE_DEF    (0x00000000)
  #define DEVICE_IDLE_DURATION_OVERRIDE_PCU_FORCE_MDID_OVERRIDE_HSH    (0x013C59C8)

#define CHAP_CONFIG_PCU_REG                                            (0x00005A00)

  #define CHAP_CONFIG_PCU_PECI_CMD_OFF                                 ( 4)
  #define CHAP_CONFIG_PCU_PECI_CMD_WID                                 ( 8)
  #define CHAP_CONFIG_PCU_PECI_CMD_MSK                                 (0x00000FF0)
  #define CHAP_CONFIG_PCU_PECI_CMD_MIN                                 (0)
  #define CHAP_CONFIG_PCU_PECI_CMD_MAX                                 (255) // 0x000000FF
  #define CHAP_CONFIG_PCU_PECI_CMD_DEF                                 (0x00000000)
  #define CHAP_CONFIG_PCU_PECI_CMD_HSH                                 (0x08085A00)

#define FFFC_EMI_CONTROL_PCU_REG                                       (0x00005A08)
//Duplicate of CAMARILLO_MAILBOX_DATA0_PCU_REG

#define FFFC_RFI_CONTROL_PCU_REG                                       (0x00005A0C)
//Duplicate of CAMARILLO_MAILBOX_DATA0_PCU_REG

#define FFFC_RFI_STATUS_PCU_REG                                        (0x00005A10)
//Duplicate of CAMARILLO_MAILBOX_DATA0_PCU_REG

#define FFFC_FAULT_STATUS_PCU_REG                                      (0x00005A14)
//Duplicate of CAMARILLO_MAILBOX_DATA0_PCU_REG

#define FFFC_RFI_CONTROL2_PCU_REG                                      (0x00005A18)
//Duplicate of CAMARILLO_MAILBOX_DATA0_PCU_REG

#define ENERGY_DEBUG_PCU_REG                                           (0x00005B04)

  #define ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP0_VALUE_OFF                  ( 0)
  #define ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP0_VALUE_WID                  (10)
  #define ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP0_VALUE_MSK                  (0x000003FF)
  #define ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP0_VALUE_MIN                  (0)
  #define ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP0_VALUE_MAX                  (1023) // 0x000003FF
  #define ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP0_VALUE_DEF                  (0x00000000)
  #define ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP0_VALUE_HSH                  (0x0A005B04)

  #define ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP1_VALUE_OFF                  (10)
  #define ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP1_VALUE_WID                  (10)
  #define ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP1_VALUE_MSK                  (0x000FFC00)
  #define ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP1_VALUE_MIN                  (0)
  #define ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP1_VALUE_MAX                  (1023) // 0x000003FF
  #define ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP1_VALUE_DEF                  (0x00000000)
  #define ENERGY_DEBUG_PCU_DEBUG_ENERGY_PP1_VALUE_HSH                  (0x0A145B04)

  #define ENERGY_DEBUG_PCU_DEBUG_ENERGY_SA_VALUE_OFF                   (20)
  #define ENERGY_DEBUG_PCU_DEBUG_ENERGY_SA_VALUE_WID                   (10)
  #define ENERGY_DEBUG_PCU_DEBUG_ENERGY_SA_VALUE_MSK                   (0x3FF00000)
  #define ENERGY_DEBUG_PCU_DEBUG_ENERGY_SA_VALUE_MIN                   (0)
  #define ENERGY_DEBUG_PCU_DEBUG_ENERGY_SA_VALUE_MAX                   (1023) // 0x000003FF
  #define ENERGY_DEBUG_PCU_DEBUG_ENERGY_SA_VALUE_DEF                   (0x00000000)
  #define ENERGY_DEBUG_PCU_DEBUG_ENERGY_SA_VALUE_HSH                   (0x0A285B04)

#define SSKPD_PCU_REG                                                  (0x00005D10)

  #define SSKPD_PCU_SKPD_OFF                                           ( 0)
  #define SSKPD_PCU_SKPD_WID                                           (64)
  #define SSKPD_PCU_SKPD_MSK                                           (0xFFFFFFFFFFFFFFFFULL)
  #define SSKPD_PCU_SKPD_MIN                                           (0)
  #define SSKPD_PCU_SKPD_MAX                                           (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define SSKPD_PCU_SKPD_DEF                                           (0x00000000)
  #define SSKPD_PCU_SKPD_HSH                                           (0x40005D10)

#define C2C3TT_PCU_REG                                                 (0x00005D20)

  #define C2C3TT_PCU_PPDN_INIT_OFF                                     ( 0)
  #define C2C3TT_PCU_PPDN_INIT_WID                                     (12)
  #define C2C3TT_PCU_PPDN_INIT_MSK                                     (0x00000FFF)
  #define C2C3TT_PCU_PPDN_INIT_MIN                                     (0)
  #define C2C3TT_PCU_PPDN_INIT_MAX                                     (4095) // 0x00000FFF
  #define C2C3TT_PCU_PPDN_INIT_DEF                                     (0x00000005)
  #define C2C3TT_PCU_PPDN_INIT_HSH                                     (0x0C005D20)

#define C2_DDR_TT_PCU_REG                                              (0x00005D24)

  #define C2_DDR_TT_PCU_DDR_TIMER_VALUE_OFF                            ( 0)
  #define C2_DDR_TT_PCU_DDR_TIMER_VALUE_WID                            (13)
  #define C2_DDR_TT_PCU_DDR_TIMER_VALUE_MSK                            (0x00001FFF)
  #define C2_DDR_TT_PCU_DDR_TIMER_VALUE_MIN                            (0)
  #define C2_DDR_TT_PCU_DDR_TIMER_VALUE_MAX                            (8191) // 0x00001FFF
  #define C2_DDR_TT_PCU_DDR_TIMER_VALUE_DEF                            (0x000001F4)
  #define C2_DDR_TT_PCU_DDR_TIMER_VALUE_HSH                            (0x0D005D24)

#define PCIE_ILTR_OVRD_PCU_REG                                         (0x00005D30)

  #define PCIE_ILTR_OVRD_PCU_NSTL_OFF                                  ( 0)
  #define PCIE_ILTR_OVRD_PCU_NSTL_WID                                  (10)
  #define PCIE_ILTR_OVRD_PCU_NSTL_MSK                                  (0x000003FF)
  #define PCIE_ILTR_OVRD_PCU_NSTL_MIN                                  (0)
  #define PCIE_ILTR_OVRD_PCU_NSTL_MAX                                  (1023) // 0x000003FF
  #define PCIE_ILTR_OVRD_PCU_NSTL_DEF                                  (0x00000000)
  #define PCIE_ILTR_OVRD_PCU_NSTL_HSH                                  (0x0A005D30)

  #define PCIE_ILTR_OVRD_PCU_MULTIPLIER_OFF                            (10)
  #define PCIE_ILTR_OVRD_PCU_MULTIPLIER_WID                            ( 3)
  #define PCIE_ILTR_OVRD_PCU_MULTIPLIER_MSK                            (0x00001C00)
  #define PCIE_ILTR_OVRD_PCU_MULTIPLIER_MIN                            (0)
  #define PCIE_ILTR_OVRD_PCU_MULTIPLIER_MAX                            (7) // 0x00000007
  #define PCIE_ILTR_OVRD_PCU_MULTIPLIER_DEF                            (0x00000000)
  #define PCIE_ILTR_OVRD_PCU_MULTIPLIER_HSH                            (0x03145D30)

  #define PCIE_ILTR_OVRD_PCU_FORCE_NL_OFF                              (14)
  #define PCIE_ILTR_OVRD_PCU_FORCE_NL_WID                              ( 1)
  #define PCIE_ILTR_OVRD_PCU_FORCE_NL_MSK                              (0x00004000)
  #define PCIE_ILTR_OVRD_PCU_FORCE_NL_MIN                              (0)
  #define PCIE_ILTR_OVRD_PCU_FORCE_NL_MAX                              (1) // 0x00000001
  #define PCIE_ILTR_OVRD_PCU_FORCE_NL_DEF                              (0x00000000)
  #define PCIE_ILTR_OVRD_PCU_FORCE_NL_HSH                              (0x011C5D30)

  #define PCIE_ILTR_OVRD_PCU_NL_V_OFF                                  (15)
  #define PCIE_ILTR_OVRD_PCU_NL_V_WID                                  ( 1)
  #define PCIE_ILTR_OVRD_PCU_NL_V_MSK                                  (0x00008000)
  #define PCIE_ILTR_OVRD_PCU_NL_V_MIN                                  (0)
  #define PCIE_ILTR_OVRD_PCU_NL_V_MAX                                  (1) // 0x00000001
  #define PCIE_ILTR_OVRD_PCU_NL_V_DEF                                  (0x00000000)
  #define PCIE_ILTR_OVRD_PCU_NL_V_HSH                                  (0x011E5D30)

  #define PCIE_ILTR_OVRD_PCU_SXL_OFF                                   (16)
  #define PCIE_ILTR_OVRD_PCU_SXL_WID                                   (10)
  #define PCIE_ILTR_OVRD_PCU_SXL_MSK                                   (0x03FF0000)
  #define PCIE_ILTR_OVRD_PCU_SXL_MIN                                   (0)
  #define PCIE_ILTR_OVRD_PCU_SXL_MAX                                   (1023) // 0x000003FF
  #define PCIE_ILTR_OVRD_PCU_SXL_DEF                                   (0x00000000)
  #define PCIE_ILTR_OVRD_PCU_SXL_HSH                                   (0x0A205D30)

  #define PCIE_ILTR_OVRD_PCU_SXLM_OFF                                  (26)
  #define PCIE_ILTR_OVRD_PCU_SXLM_WID                                  ( 3)
  #define PCIE_ILTR_OVRD_PCU_SXLM_MSK                                  (0x1C000000)
  #define PCIE_ILTR_OVRD_PCU_SXLM_MIN                                  (0)
  #define PCIE_ILTR_OVRD_PCU_SXLM_MAX                                  (7) // 0x00000007
  #define PCIE_ILTR_OVRD_PCU_SXLM_DEF                                  (0x00000000)
  #define PCIE_ILTR_OVRD_PCU_SXLM_HSH                                  (0x03345D30)

  #define PCIE_ILTR_OVRD_PCU_FORCE_SXL_OFF                             (30)
  #define PCIE_ILTR_OVRD_PCU_FORCE_SXL_WID                             ( 1)
  #define PCIE_ILTR_OVRD_PCU_FORCE_SXL_MSK                             (0x40000000)
  #define PCIE_ILTR_OVRD_PCU_FORCE_SXL_MIN                             (0)
  #define PCIE_ILTR_OVRD_PCU_FORCE_SXL_MAX                             (1) // 0x00000001
  #define PCIE_ILTR_OVRD_PCU_FORCE_SXL_DEF                             (0x00000000)
  #define PCIE_ILTR_OVRD_PCU_FORCE_SXL_HSH                             (0x013C5D30)

  #define PCIE_ILTR_OVRD_PCU_SXL_V_OFF                                 (31)
  #define PCIE_ILTR_OVRD_PCU_SXL_V_WID                                 ( 1)
  #define PCIE_ILTR_OVRD_PCU_SXL_V_MSK                                 (0x80000000)
  #define PCIE_ILTR_OVRD_PCU_SXL_V_MIN                                 (0)
  #define PCIE_ILTR_OVRD_PCU_SXL_V_MAX                                 (1) // 0x00000001
  #define PCIE_ILTR_OVRD_PCU_SXL_V_DEF                                 (0x00000000)
  #define PCIE_ILTR_OVRD_PCU_SXL_V_HSH                                 (0x013E5D30)

#define PCIE_ILTR_VAL_PCU_0_REG                                        (0x00005D34)

  #define PCIE_ILTR_VAL_PCU_0_NL_VALUE_OFF                             ( 0)
  #define PCIE_ILTR_VAL_PCU_0_NL_VALUE_WID                             (10)
  #define PCIE_ILTR_VAL_PCU_0_NL_VALUE_MSK                             (0x000003FF)
  #define PCIE_ILTR_VAL_PCU_0_NL_VALUE_MIN                             (0)
  #define PCIE_ILTR_VAL_PCU_0_NL_VALUE_MAX                             (1023) // 0x000003FF
  #define PCIE_ILTR_VAL_PCU_0_NL_VALUE_DEF                             (0x00000000)
  #define PCIE_ILTR_VAL_PCU_0_NL_VALUE_HSH                             (0x0A005D34)

  #define PCIE_ILTR_VAL_PCU_0_NL_SCALE_OFF                             (10)
  #define PCIE_ILTR_VAL_PCU_0_NL_SCALE_WID                             ( 3)
  #define PCIE_ILTR_VAL_PCU_0_NL_SCALE_MSK                             (0x00001C00)
  #define PCIE_ILTR_VAL_PCU_0_NL_SCALE_MIN                             (0)
  #define PCIE_ILTR_VAL_PCU_0_NL_SCALE_MAX                             (7) // 0x00000007
  #define PCIE_ILTR_VAL_PCU_0_NL_SCALE_DEF                             (0x00000000)
  #define PCIE_ILTR_VAL_PCU_0_NL_SCALE_HSH                             (0x03145D34)

  #define PCIE_ILTR_VAL_PCU_0_NL_RESERVED_OFF                          (13)
  #define PCIE_ILTR_VAL_PCU_0_NL_RESERVED_WID                          ( 2)
  #define PCIE_ILTR_VAL_PCU_0_NL_RESERVED_MSK                          (0x00006000)
  #define PCIE_ILTR_VAL_PCU_0_NL_RESERVED_MIN                          (0)
  #define PCIE_ILTR_VAL_PCU_0_NL_RESERVED_MAX                          (3) // 0x00000003
  #define PCIE_ILTR_VAL_PCU_0_NL_RESERVED_DEF                          (0x00000000)
  #define PCIE_ILTR_VAL_PCU_0_NL_RESERVED_HSH                          (0x021A5D34)

  #define PCIE_ILTR_VAL_PCU_0_NL_VALID_OFF                             (15)
  #define PCIE_ILTR_VAL_PCU_0_NL_VALID_WID                             ( 1)
  #define PCIE_ILTR_VAL_PCU_0_NL_VALID_MSK                             (0x00008000)
  #define PCIE_ILTR_VAL_PCU_0_NL_VALID_MIN                             (0)
  #define PCIE_ILTR_VAL_PCU_0_NL_VALID_MAX                             (1) // 0x00000001
  #define PCIE_ILTR_VAL_PCU_0_NL_VALID_DEF                             (0x00000000)
  #define PCIE_ILTR_VAL_PCU_0_NL_VALID_HSH                             (0x011E5D34)

  #define PCIE_ILTR_VAL_PCU_0_SXL_VALUE_OFF                            (16)
  #define PCIE_ILTR_VAL_PCU_0_SXL_VALUE_WID                            (10)
  #define PCIE_ILTR_VAL_PCU_0_SXL_VALUE_MSK                            (0x03FF0000)
  #define PCIE_ILTR_VAL_PCU_0_SXL_VALUE_MIN                            (0)
  #define PCIE_ILTR_VAL_PCU_0_SXL_VALUE_MAX                            (1023) // 0x000003FF
  #define PCIE_ILTR_VAL_PCU_0_SXL_VALUE_DEF                            (0x00000000)
  #define PCIE_ILTR_VAL_PCU_0_SXL_VALUE_HSH                            (0x0A205D34)

  #define PCIE_ILTR_VAL_PCU_0_SXL_SCALE_OFF                            (26)
  #define PCIE_ILTR_VAL_PCU_0_SXL_SCALE_WID                            ( 3)
  #define PCIE_ILTR_VAL_PCU_0_SXL_SCALE_MSK                            (0x1C000000)
  #define PCIE_ILTR_VAL_PCU_0_SXL_SCALE_MIN                            (0)
  #define PCIE_ILTR_VAL_PCU_0_SXL_SCALE_MAX                            (7) // 0x00000007
  #define PCIE_ILTR_VAL_PCU_0_SXL_SCALE_DEF                            (0x00000000)
  #define PCIE_ILTR_VAL_PCU_0_SXL_SCALE_HSH                            (0x03345D34)

  #define PCIE_ILTR_VAL_PCU_0_SXL_RESERVED_OFF                         (29)
  #define PCIE_ILTR_VAL_PCU_0_SXL_RESERVED_WID                         ( 2)
  #define PCIE_ILTR_VAL_PCU_0_SXL_RESERVED_MSK                         (0x60000000)
  #define PCIE_ILTR_VAL_PCU_0_SXL_RESERVED_MIN                         (0)
  #define PCIE_ILTR_VAL_PCU_0_SXL_RESERVED_MAX                         (3) // 0x00000003
  #define PCIE_ILTR_VAL_PCU_0_SXL_RESERVED_DEF                         (0x00000000)
  #define PCIE_ILTR_VAL_PCU_0_SXL_RESERVED_HSH                         (0x023A5D34)

  #define PCIE_ILTR_VAL_PCU_0_SXL_VALID_OFF                            (31)
  #define PCIE_ILTR_VAL_PCU_0_SXL_VALID_WID                            ( 1)
  #define PCIE_ILTR_VAL_PCU_0_SXL_VALID_MSK                            (0x80000000)
  #define PCIE_ILTR_VAL_PCU_0_SXL_VALID_MIN                            (0)
  #define PCIE_ILTR_VAL_PCU_0_SXL_VALID_MAX                            (1) // 0x00000001
  #define PCIE_ILTR_VAL_PCU_0_SXL_VALID_DEF                            (0x00000000)
  #define PCIE_ILTR_VAL_PCU_0_SXL_VALID_HSH                            (0x013E5D34)

#define PCIE_ILTR_VAL_PCU_1_REG                                        (0x00005D38)
//Duplicate of PCIE_ILTR_VAL_PCU_0_REG

#define PCIE_ILTR_VAL_PCU_2_REG                                        (0x00005D3C)
//Duplicate of PCIE_ILTR_VAL_PCU_0_REG

#define PCIE_ILTR_VAL_PCU_3_REG                                        (0x00005D40)
//Duplicate of PCIE_ILTR_VAL_PCU_0_REG

#define BIOS_MAILBOX_DATA_PCU_REG                                      (0x00005DA0)
//Duplicate of CAMARILLO_MAILBOX_DATA0_PCU_REG

#define BIOS_MAILBOX_INTERFACE_PCU_REG                                 (0x00005DA4)

  #define BIOS_MAILBOX_INTERFACE_PCU_COMMAND_OFF                       ( 0)
  #define BIOS_MAILBOX_INTERFACE_PCU_COMMAND_WID                       ( 8)
  #define BIOS_MAILBOX_INTERFACE_PCU_COMMAND_MSK                       (0x000000FF)
  #define BIOS_MAILBOX_INTERFACE_PCU_COMMAND_MIN                       (0)
  #define BIOS_MAILBOX_INTERFACE_PCU_COMMAND_MAX                       (255) // 0x000000FF
  #define BIOS_MAILBOX_INTERFACE_PCU_COMMAND_DEF                       (0x00000000)
  #define BIOS_MAILBOX_INTERFACE_PCU_COMMAND_HSH                       (0x08005DA4)

  #define BIOS_MAILBOX_INTERFACE_PCU_PARAM1_OFF                        ( 8)
  #define BIOS_MAILBOX_INTERFACE_PCU_PARAM1_WID                        ( 8)
  #define BIOS_MAILBOX_INTERFACE_PCU_PARAM1_MSK                        (0x0000FF00)
  #define BIOS_MAILBOX_INTERFACE_PCU_PARAM1_MIN                        (0)
  #define BIOS_MAILBOX_INTERFACE_PCU_PARAM1_MAX                        (255) // 0x000000FF
  #define BIOS_MAILBOX_INTERFACE_PCU_PARAM1_DEF                        (0x00000000)
  #define BIOS_MAILBOX_INTERFACE_PCU_PARAM1_HSH                        (0x08105DA4)

  #define BIOS_MAILBOX_INTERFACE_PCU_PARAM2_OFF                        (16)
  #define BIOS_MAILBOX_INTERFACE_PCU_PARAM2_WID                        (13)
  #define BIOS_MAILBOX_INTERFACE_PCU_PARAM2_MSK                        (0x1FFF0000)
  #define BIOS_MAILBOX_INTERFACE_PCU_PARAM2_MIN                        (0)
  #define BIOS_MAILBOX_INTERFACE_PCU_PARAM2_MAX                        (8191) // 0x00001FFF
  #define BIOS_MAILBOX_INTERFACE_PCU_PARAM2_DEF                        (0x00000000)
  #define BIOS_MAILBOX_INTERFACE_PCU_PARAM2_HSH                        (0x0D205DA4)

  #define BIOS_MAILBOX_INTERFACE_PCU_RUN_BUSY_OFF                      (31)
  #define BIOS_MAILBOX_INTERFACE_PCU_RUN_BUSY_WID                      ( 1)
  #define BIOS_MAILBOX_INTERFACE_PCU_RUN_BUSY_MSK                      (0x80000000)
  #define BIOS_MAILBOX_INTERFACE_PCU_RUN_BUSY_MIN                      (0)
  #define BIOS_MAILBOX_INTERFACE_PCU_RUN_BUSY_MAX                      (1) // 0x00000001
  #define BIOS_MAILBOX_INTERFACE_PCU_RUN_BUSY_DEF                      (0x00000000)
  #define BIOS_MAILBOX_INTERFACE_PCU_RUN_BUSY_HSH                      (0x013E5DA4)

#define BIOS_RESET_CPL_PCU_REG                                         (0x00005DA8)

  #define BIOS_RESET_CPL_PCU_RST_CPL_OFF                               ( 0)
  #define BIOS_RESET_CPL_PCU_RST_CPL_WID                               ( 1)
  #define BIOS_RESET_CPL_PCU_RST_CPL_MSK                               (0x00000001)
  #define BIOS_RESET_CPL_PCU_RST_CPL_MIN                               (0)
  #define BIOS_RESET_CPL_PCU_RST_CPL_MAX                               (1) // 0x00000001
  #define BIOS_RESET_CPL_PCU_RST_CPL_DEF                               (0x00000000)
  #define BIOS_RESET_CPL_PCU_RST_CPL_HSH                               (0x01005DA8)

  #define BIOS_RESET_CPL_PCU_PCIE_ENUMERATION_DONE_OFF                 ( 1)
  #define BIOS_RESET_CPL_PCU_PCIE_ENUMERATION_DONE_WID                 ( 1)
  #define BIOS_RESET_CPL_PCU_PCIE_ENUMERATION_DONE_MSK                 (0x00000002)
  #define BIOS_RESET_CPL_PCU_PCIE_ENUMERATION_DONE_MIN                 (0)
  #define BIOS_RESET_CPL_PCU_PCIE_ENUMERATION_DONE_MAX                 (1) // 0x00000001
  #define BIOS_RESET_CPL_PCU_PCIE_ENUMERATION_DONE_DEF                 (0x00000000)
  #define BIOS_RESET_CPL_PCU_PCIE_ENUMERATION_DONE_HSH                 (0x01025DA8)

  #define BIOS_RESET_CPL_PCU_C7_ALLOWED_OFF                            ( 2)
  #define BIOS_RESET_CPL_PCU_C7_ALLOWED_WID                            ( 1)
  #define BIOS_RESET_CPL_PCU_C7_ALLOWED_MSK                            (0x00000004)
  #define BIOS_RESET_CPL_PCU_C7_ALLOWED_MIN                            (0)
  #define BIOS_RESET_CPL_PCU_C7_ALLOWED_MAX                            (1) // 0x00000001
  #define BIOS_RESET_CPL_PCU_C7_ALLOWED_DEF                            (0x00000000)
  #define BIOS_RESET_CPL_PCU_C7_ALLOWED_HSH                            (0x01045DA8)

  #define BIOS_RESET_CPL_PCU_ENABLE_PCIE_NDA_PG_OFF                    ( 3)
  #define BIOS_RESET_CPL_PCU_ENABLE_PCIE_NDA_PG_WID                    ( 1)
  #define BIOS_RESET_CPL_PCU_ENABLE_PCIE_NDA_PG_MSK                    (0x00000008)
  #define BIOS_RESET_CPL_PCU_ENABLE_PCIE_NDA_PG_MIN                    (0)
  #define BIOS_RESET_CPL_PCU_ENABLE_PCIE_NDA_PG_MAX                    (1) // 0x00000001
  #define BIOS_RESET_CPL_PCU_ENABLE_PCIE_NDA_PG_DEF                    (0x00000000)
  #define BIOS_RESET_CPL_PCU_ENABLE_PCIE_NDA_PG_HSH                    (0x01065DA8)

#define MC_BIOS_REQ_PCU_REG                                            (0x00005E00)

  #define MC_BIOS_REQ_PCU_REQ_DATA_OFF                                 ( 0)
  #define MC_BIOS_REQ_PCU_REQ_DATA_WID                                 ( 8)
  #define MC_BIOS_REQ_PCU_REQ_DATA_MSK                                 (0x000000FF)
  #define MC_BIOS_REQ_PCU_REQ_DATA_MIN                                 (0)
  #define MC_BIOS_REQ_PCU_REQ_DATA_MAX                                 (255) // 0x000000FF
  #define MC_BIOS_REQ_PCU_REQ_DATA_DEF                                 (0x00000000)
  #define MC_BIOS_REQ_PCU_REQ_DATA_HSH                                 (0x08005E00)

  #define MC_BIOS_REQ_PCU_REQ_TYPE_OFF                                 ( 8)
  #define MC_BIOS_REQ_PCU_REQ_TYPE_WID                                 ( 4)
  #define MC_BIOS_REQ_PCU_REQ_TYPE_MSK                                 (0x00000F00)
  #define MC_BIOS_REQ_PCU_REQ_TYPE_MIN                                 (0)
  #define MC_BIOS_REQ_PCU_REQ_TYPE_MAX                                 (15) // 0x0000000F
  #define MC_BIOS_REQ_PCU_REQ_TYPE_DEF                                 (0x00000000)
  #define MC_BIOS_REQ_PCU_REQ_TYPE_HSH                                 (0x04105E00)

  #define MC_BIOS_REQ_PCU_GEAR_TYPE_OFF                                (16)
  #define MC_BIOS_REQ_PCU_GEAR_TYPE_WID                                ( 1)
  #define MC_BIOS_REQ_PCU_GEAR_TYPE_MSK                                (0x00010000)
  #define MC_BIOS_REQ_PCU_GEAR_TYPE_MIN                                (0)
  #define MC_BIOS_REQ_PCU_GEAR_TYPE_MAX                                (1) // 0x00000001
  #define MC_BIOS_REQ_PCU_GEAR_TYPE_DEF                                (0x00000000)
  #define MC_BIOS_REQ_PCU_GEAR_TYPE_HSH                                (0x01205E00)

  #define MC_BIOS_REQ_PCU_REQ_VDDQ_TX_VOLTAGE_OFF                      (17)
  #define MC_BIOS_REQ_PCU_REQ_VDDQ_TX_VOLTAGE_WID                      (10)
  #define MC_BIOS_REQ_PCU_REQ_VDDQ_TX_VOLTAGE_MSK                      (0x07FE0000)
  #define MC_BIOS_REQ_PCU_REQ_VDDQ_TX_VOLTAGE_MIN                      (0)
  #define MC_BIOS_REQ_PCU_REQ_VDDQ_TX_VOLTAGE_MAX                      (1023) // 0x000003FF
  #define MC_BIOS_REQ_PCU_REQ_VDDQ_TX_VOLTAGE_DEF                      (0x00000000)
  #define MC_BIOS_REQ_PCU_REQ_VDDQ_TX_VOLTAGE_HSH                      (0x0A225E00)

  #define MC_BIOS_REQ_PCU_REQ_VDDQ_TX_ICCMAX_OFF                       (27)
  #define MC_BIOS_REQ_PCU_REQ_VDDQ_TX_ICCMAX_WID                       ( 4)
  #define MC_BIOS_REQ_PCU_REQ_VDDQ_TX_ICCMAX_MSK                       (0x78000000)
  #define MC_BIOS_REQ_PCU_REQ_VDDQ_TX_ICCMAX_MIN                       (0)
  #define MC_BIOS_REQ_PCU_REQ_VDDQ_TX_ICCMAX_MAX                       (15) // 0x0000000F
  #define MC_BIOS_REQ_PCU_REQ_VDDQ_TX_ICCMAX_DEF                       (0x00000000)
  #define MC_BIOS_REQ_PCU_REQ_VDDQ_TX_ICCMAX_HSH                       (0x04365E00)

  #define MC_BIOS_REQ_PCU_RUN_BUSY_OFF                                 (31)
  #define MC_BIOS_REQ_PCU_RUN_BUSY_WID                                 ( 1)
  #define MC_BIOS_REQ_PCU_RUN_BUSY_MSK                                 (0x80000000)
  #define MC_BIOS_REQ_PCU_RUN_BUSY_MIN                                 (0)
  #define MC_BIOS_REQ_PCU_RUN_BUSY_MAX                                 (1) // 0x00000001
  #define MC_BIOS_REQ_PCU_RUN_BUSY_DEF                                 (0x00000000)
  #define MC_BIOS_REQ_PCU_RUN_BUSY_HSH                                 (0x013E5E00)

#define MC_BIOS_DATA_PCU_REG                                           (0x00005E04)

  #define MC_BIOS_DATA_PCU_MC_FREQ_OFF                                 ( 0)
  #define MC_BIOS_DATA_PCU_MC_FREQ_WID                                 ( 8)
  #define MC_BIOS_DATA_PCU_MC_FREQ_MSK                                 (0x000000FF)
  #define MC_BIOS_DATA_PCU_MC_FREQ_MIN                                 (0)
  #define MC_BIOS_DATA_PCU_MC_FREQ_MAX                                 (255) // 0x000000FF
  #define MC_BIOS_DATA_PCU_MC_FREQ_DEF                                 (0x00000000)
  #define MC_BIOS_DATA_PCU_MC_FREQ_HSH                                 (0x08005E04)

  #define MC_BIOS_DATA_PCU_MC_FREQ_TYPE_OFF                            ( 8)
  #define MC_BIOS_DATA_PCU_MC_FREQ_TYPE_WID                            ( 4)
  #define MC_BIOS_DATA_PCU_MC_FREQ_TYPE_MSK                            (0x00000F00)
  #define MC_BIOS_DATA_PCU_MC_FREQ_TYPE_MIN                            (0)
  #define MC_BIOS_DATA_PCU_MC_FREQ_TYPE_MAX                            (15) // 0x0000000F
  #define MC_BIOS_DATA_PCU_MC_FREQ_TYPE_DEF                            (0x00000000)
  #define MC_BIOS_DATA_PCU_MC_FREQ_TYPE_HSH                            (0x04105E04)

  #define MC_BIOS_DATA_PCU_GEAR_TYPE_OFF                               (16)
  #define MC_BIOS_DATA_PCU_GEAR_TYPE_WID                               ( 1)
  #define MC_BIOS_DATA_PCU_GEAR_TYPE_MSK                               (0x00010000)
  #define MC_BIOS_DATA_PCU_GEAR_TYPE_MIN                               (0)
  #define MC_BIOS_DATA_PCU_GEAR_TYPE_MAX                               (1) // 0x00000001
  #define MC_BIOS_DATA_PCU_GEAR_TYPE_DEF                               (0x00000000)
  #define MC_BIOS_DATA_PCU_GEAR_TYPE_HSH                               (0x01205E04)

  #define MC_BIOS_DATA_PCU_VDDQ_TX_VOLTAGE_OFF                         (17)
  #define MC_BIOS_DATA_PCU_VDDQ_TX_VOLTAGE_WID                         (10)
  #define MC_BIOS_DATA_PCU_VDDQ_TX_VOLTAGE_MSK                         (0x07FE0000)
  #define MC_BIOS_DATA_PCU_VDDQ_TX_VOLTAGE_MIN                         (0)
  #define MC_BIOS_DATA_PCU_VDDQ_TX_VOLTAGE_MAX                         (1023) // 0x000003FF
  #define MC_BIOS_DATA_PCU_VDDQ_TX_VOLTAGE_DEF                         (0x00000000)
  #define MC_BIOS_DATA_PCU_VDDQ_TX_VOLTAGE_HSH                         (0x0A225E04)

  #define MC_BIOS_DATA_PCU_VDDQ_TX_ICCMAX_OFF                          (27)
  #define MC_BIOS_DATA_PCU_VDDQ_TX_ICCMAX_WID                          ( 4)
  #define MC_BIOS_DATA_PCU_VDDQ_TX_ICCMAX_MSK                          (0x78000000)
  #define MC_BIOS_DATA_PCU_VDDQ_TX_ICCMAX_MIN                          (0)
  #define MC_BIOS_DATA_PCU_VDDQ_TX_ICCMAX_MAX                          (15) // 0x0000000F
  #define MC_BIOS_DATA_PCU_VDDQ_TX_ICCMAX_DEF                          (0x00000000)
  #define MC_BIOS_DATA_PCU_VDDQ_TX_ICCMAX_HSH                          (0x04365E04)

#define SAPMCTL_PCU_REG                                                (0x00005F00)

  #define SAPMCTL_PCU_SACG_ENA_OFF                                     ( 0)
  #define SAPMCTL_PCU_SACG_ENA_WID                                     ( 1)
  #define SAPMCTL_PCU_SACG_ENA_MSK                                     (0x00000001)
  #define SAPMCTL_PCU_SACG_ENA_MIN                                     (0)
  #define SAPMCTL_PCU_SACG_ENA_MAX                                     (1) // 0x00000001
  #define SAPMCTL_PCU_SACG_ENA_DEF                                     (0x00000000)
  #define SAPMCTL_PCU_SACG_ENA_HSH                                     (0x01005F00)

  #define SAPMCTL_PCU_MPLL_OFF_ENA_OFF                                 ( 1)
  #define SAPMCTL_PCU_MPLL_OFF_ENA_WID                                 ( 1)
  #define SAPMCTL_PCU_MPLL_OFF_ENA_MSK                                 (0x00000002)
  #define SAPMCTL_PCU_MPLL_OFF_ENA_MIN                                 (0)
  #define SAPMCTL_PCU_MPLL_OFF_ENA_MAX                                 (1) // 0x00000001
  #define SAPMCTL_PCU_MPLL_OFF_ENA_DEF                                 (0x00000001)
  #define SAPMCTL_PCU_MPLL_OFF_ENA_HSH                                 (0x01025F00)

  #define SAPMCTL_PCU_PPLL_OFF_ENA_OFF                                 ( 2)
  #define SAPMCTL_PCU_PPLL_OFF_ENA_WID                                 ( 1)
  #define SAPMCTL_PCU_PPLL_OFF_ENA_MSK                                 (0x00000004)
  #define SAPMCTL_PCU_PPLL_OFF_ENA_MIN                                 (0)
  #define SAPMCTL_PCU_PPLL_OFF_ENA_MAX                                 (1) // 0x00000001
  #define SAPMCTL_PCU_PPLL_OFF_ENA_DEF                                 (0x00000001)
  #define SAPMCTL_PCU_PPLL_OFF_ENA_HSH                                 (0x01045F00)

  #define SAPMCTL_PCU_SACG_SEN_OFF                                     ( 8)
  #define SAPMCTL_PCU_SACG_SEN_WID                                     ( 1)
  #define SAPMCTL_PCU_SACG_SEN_MSK                                     (0x00000100)
  #define SAPMCTL_PCU_SACG_SEN_MIN                                     (0)
  #define SAPMCTL_PCU_SACG_SEN_MAX                                     (1) // 0x00000001
  #define SAPMCTL_PCU_SACG_SEN_DEF                                     (0x00000001)
  #define SAPMCTL_PCU_SACG_SEN_HSH                                     (0x01105F00)

  #define SAPMCTL_PCU_MPLL_OFF_SEN_OFF                                 ( 9)
  #define SAPMCTL_PCU_MPLL_OFF_SEN_WID                                 ( 1)
  #define SAPMCTL_PCU_MPLL_OFF_SEN_MSK                                 (0x00000200)
  #define SAPMCTL_PCU_MPLL_OFF_SEN_MIN                                 (0)
  #define SAPMCTL_PCU_MPLL_OFF_SEN_MAX                                 (1) // 0x00000001
  #define SAPMCTL_PCU_MPLL_OFF_SEN_DEF                                 (0x00000000)
  #define SAPMCTL_PCU_MPLL_OFF_SEN_HSH                                 (0x01125F00)

  #define SAPMCTL_PCU_MDLL_OFF_SEN_OFF                                 (10)
  #define SAPMCTL_PCU_MDLL_OFF_SEN_WID                                 ( 1)
  #define SAPMCTL_PCU_MDLL_OFF_SEN_MSK                                 (0x00000400)
  #define SAPMCTL_PCU_MDLL_OFF_SEN_MIN                                 (0)
  #define SAPMCTL_PCU_MDLL_OFF_SEN_MAX                                 (1) // 0x00000001
  #define SAPMCTL_PCU_MDLL_OFF_SEN_DEF                                 (0x00000000)
  #define SAPMCTL_PCU_MDLL_OFF_SEN_HSH                                 (0x01145F00)

  #define SAPMCTL_PCU_SACG_SREXIT_OFF                                  (11)
  #define SAPMCTL_PCU_SACG_SREXIT_WID                                  ( 1)
  #define SAPMCTL_PCU_SACG_SREXIT_MSK                                  (0x00000800)
  #define SAPMCTL_PCU_SACG_SREXIT_MIN                                  (0)
  #define SAPMCTL_PCU_SACG_SREXIT_MAX                                  (1) // 0x00000001
  #define SAPMCTL_PCU_SACG_SREXIT_DEF                                  (0x00000000)
  #define SAPMCTL_PCU_SACG_SREXIT_HSH                                  (0x01165F00)

  #define SAPMCTL_PCU_NSWAKE_SREXIT_OFF                                (12)
  #define SAPMCTL_PCU_NSWAKE_SREXIT_WID                                ( 1)
  #define SAPMCTL_PCU_NSWAKE_SREXIT_MSK                                (0x00001000)
  #define SAPMCTL_PCU_NSWAKE_SREXIT_MIN                                (0)
  #define SAPMCTL_PCU_NSWAKE_SREXIT_MAX                                (1) // 0x00000001
  #define SAPMCTL_PCU_NSWAKE_SREXIT_DEF                                (0x00000000)
  #define SAPMCTL_PCU_NSWAKE_SREXIT_HSH                                (0x01185F00)

  #define SAPMCTL_PCU_SACG_MPLL_OFF                                    (13)
  #define SAPMCTL_PCU_SACG_MPLL_WID                                    ( 1)
  #define SAPMCTL_PCU_SACG_MPLL_MSK                                    (0x00002000)
  #define SAPMCTL_PCU_SACG_MPLL_MIN                                    (0)
  #define SAPMCTL_PCU_SACG_MPLL_MAX                                    (1) // 0x00000001
  #define SAPMCTL_PCU_SACG_MPLL_DEF                                    (0x00000001)
  #define SAPMCTL_PCU_SACG_MPLL_HSH                                    (0x011A5F00)

  #define SAPMCTL_PCU_MPLL_ON_DE_OFF                                   (14)
  #define SAPMCTL_PCU_MPLL_ON_DE_WID                                   ( 1)
  #define SAPMCTL_PCU_MPLL_ON_DE_MSK                                   (0x00004000)
  #define SAPMCTL_PCU_MPLL_ON_DE_MIN                                   (0)
  #define SAPMCTL_PCU_MPLL_ON_DE_MAX                                   (1) // 0x00000001
  #define SAPMCTL_PCU_MPLL_ON_DE_DEF                                   (0x00000000)
  #define SAPMCTL_PCU_MPLL_ON_DE_HSH                                   (0x011C5F00)

  #define SAPMCTL_PCU_MDLL_ON_DE_OFF                                   (15)
  #define SAPMCTL_PCU_MDLL_ON_DE_WID                                   ( 1)
  #define SAPMCTL_PCU_MDLL_ON_DE_MSK                                   (0x00008000)
  #define SAPMCTL_PCU_MDLL_ON_DE_MIN                                   (0)
  #define SAPMCTL_PCU_MDLL_ON_DE_MAX                                   (1) // 0x00000001
  #define SAPMCTL_PCU_MDLL_ON_DE_DEF                                   (0x00000000)
  #define SAPMCTL_PCU_MDLL_ON_DE_HSH                                   (0x011E5F00)

#define P_COMP_PCU_REG                                                 (0x00005F04)

  #define P_COMP_PCU_COMP_DISABLE_OFF                                  ( 0)
  #define P_COMP_PCU_COMP_DISABLE_WID                                  ( 1)
  #define P_COMP_PCU_COMP_DISABLE_MSK                                  (0x00000001)
  #define P_COMP_PCU_COMP_DISABLE_MIN                                  (0)
  #define P_COMP_PCU_COMP_DISABLE_MAX                                  (1) // 0x00000001
  #define P_COMP_PCU_COMP_DISABLE_DEF                                  (0x00000001)
  #define P_COMP_PCU_COMP_DISABLE_HSH                                  (0x01005F04)

  #define P_COMP_PCU_COMP_INTERVAL_OFF                                 ( 1)
  #define P_COMP_PCU_COMP_INTERVAL_WID                                 ( 4)
  #define P_COMP_PCU_COMP_INTERVAL_MSK                                 (0x0000001E)
  #define P_COMP_PCU_COMP_INTERVAL_MIN                                 (0)
  #define P_COMP_PCU_COMP_INTERVAL_MAX                                 (15) // 0x0000000F
  #define P_COMP_PCU_COMP_INTERVAL_DEF                                 (0x00000008)
  #define P_COMP_PCU_COMP_INTERVAL_HSH                                 (0x04025F04)

  #define P_COMP_PCU_COMP_FORCE_OFF                                    ( 8)
  #define P_COMP_PCU_COMP_FORCE_WID                                    ( 1)
  #define P_COMP_PCU_COMP_FORCE_MSK                                    (0x00000100)
  #define P_COMP_PCU_COMP_FORCE_MIN                                    (0)
  #define P_COMP_PCU_COMP_FORCE_MAX                                    (1) // 0x00000001
  #define P_COMP_PCU_COMP_FORCE_DEF                                    (0x00000000)
  #define P_COMP_PCU_COMP_FORCE_HSH                                    (0x01105F04)

#define M_COMP_PCU_REG                                                 (0x00005F08)

  #define M_COMP_PCU_COMP_DISABLE_OFF                                  ( 0)
  #define M_COMP_PCU_COMP_DISABLE_WID                                  ( 1)
  #define M_COMP_PCU_COMP_DISABLE_MSK                                  (0x00000001)
  #define M_COMP_PCU_COMP_DISABLE_MIN                                  (0)
  #define M_COMP_PCU_COMP_DISABLE_MAX                                  (1) // 0x00000001
  #define M_COMP_PCU_COMP_DISABLE_DEF                                  (0x00000000)
  #define M_COMP_PCU_COMP_DISABLE_HSH                                  (0x01005F08)

  #define M_COMP_PCU_COMP_INTERVAL_OFF                                 ( 1)
  #define M_COMP_PCU_COMP_INTERVAL_WID                                 ( 4)
  #define M_COMP_PCU_COMP_INTERVAL_MSK                                 (0x0000001E)
  #define M_COMP_PCU_COMP_INTERVAL_MIN                                 (0)
  #define M_COMP_PCU_COMP_INTERVAL_MAX                                 (15) // 0x0000000F
  #define M_COMP_PCU_COMP_INTERVAL_DEF                                 (0x0000000D)
  #define M_COMP_PCU_COMP_INTERVAL_HSH                                 (0x04025F08)

  #define M_COMP_PCU_COMP_FORCE_OFF                                    ( 8)
  #define M_COMP_PCU_COMP_FORCE_WID                                    ( 1)
  #define M_COMP_PCU_COMP_FORCE_MSK                                    (0x00000100)
  #define M_COMP_PCU_COMP_FORCE_MIN                                    (0)
  #define M_COMP_PCU_COMP_FORCE_MAX                                    (1) // 0x00000001
  #define M_COMP_PCU_COMP_FORCE_DEF                                    (0x00000000)
  #define M_COMP_PCU_COMP_FORCE_HSH                                    (0x01105F08)

#define FUSA_CONFIG_PCU_REG                                            (0x00005F0C)

  #define FUSA_CONFIG_PCU_UMCNF_CATERR_DIS_OFF                         ( 0)
  #define FUSA_CONFIG_PCU_UMCNF_CATERR_DIS_WID                         ( 1)
  #define FUSA_CONFIG_PCU_UMCNF_CATERR_DIS_MSK                         (0x00000001)
  #define FUSA_CONFIG_PCU_UMCNF_CATERR_DIS_MIN                         (0)
  #define FUSA_CONFIG_PCU_UMCNF_CATERR_DIS_MAX                         (1) // 0x00000001
  #define FUSA_CONFIG_PCU_UMCNF_CATERR_DIS_DEF                         (0x00000000)
  #define FUSA_CONFIG_PCU_UMCNF_CATERR_DIS_HSH                         (0x01005F0C)

#define FUSA_TASK_COMPLETION_COUNTER_PCU_REG                           (0x00005F10)

  #define FUSA_TASK_COMPLETION_COUNTER_PCU_COMPLETION_COUNTER_OFF      ( 0)
  #define FUSA_TASK_COMPLETION_COUNTER_PCU_COMPLETION_COUNTER_WID      (24)
  #define FUSA_TASK_COMPLETION_COUNTER_PCU_COMPLETION_COUNTER_MSK      (0x00FFFFFF)
  #define FUSA_TASK_COMPLETION_COUNTER_PCU_COMPLETION_COUNTER_MIN      (0)
  #define FUSA_TASK_COMPLETION_COUNTER_PCU_COMPLETION_COUNTER_MAX      (16777215) // 0x00FFFFFF
  #define FUSA_TASK_COMPLETION_COUNTER_PCU_COMPLETION_COUNTER_DEF      (0x00000000)
  #define FUSA_TASK_COMPLETION_COUNTER_PCU_COMPLETION_COUNTER_HSH      (0x18005F10)

  #define FUSA_TASK_COMPLETION_COUNTER_PCU_CRC8_OFF                    (24)
  #define FUSA_TASK_COMPLETION_COUNTER_PCU_CRC8_WID                    ( 8)
  #define FUSA_TASK_COMPLETION_COUNTER_PCU_CRC8_MSK                    (0xFF000000)
  #define FUSA_TASK_COMPLETION_COUNTER_PCU_CRC8_MIN                    (0)
  #define FUSA_TASK_COMPLETION_COUNTER_PCU_CRC8_MAX                    (255) // 0x000000FF
  #define FUSA_TASK_COMPLETION_COUNTER_PCU_CRC8_DEF                    (0x00000000)
  #define FUSA_TASK_COMPLETION_COUNTER_PCU_CRC8_HSH                    (0x08305F10)

#define SAPM_PG_STATUS_PCU_REG                                         (0x00005F18)

  #define SAPM_PG_STATUS_PCU_PCIE_PWR_STATUS_OFF                       ( 0)
  #define SAPM_PG_STATUS_PCU_PCIE_PWR_STATUS_WID                       ( 1)
  #define SAPM_PG_STATUS_PCU_PCIE_PWR_STATUS_MSK                       (0x00000001)
  #define SAPM_PG_STATUS_PCU_PCIE_PWR_STATUS_MIN                       (0)
  #define SAPM_PG_STATUS_PCU_PCIE_PWR_STATUS_MAX                       (1) // 0x00000001
  #define SAPM_PG_STATUS_PCU_PCIE_PWR_STATUS_DEF                       (0x00000001)
  #define SAPM_PG_STATUS_PCU_PCIE_PWR_STATUS_HSH                       (0x01005F18)

#define CONFIG_TDP_NOMINAL_PCU_REG                                     (0x00005F3C)

  #define CONFIG_TDP_NOMINAL_PCU_TDP_RATIO_OFF                         ( 0)
  #define CONFIG_TDP_NOMINAL_PCU_TDP_RATIO_WID                         ( 8)
  #define CONFIG_TDP_NOMINAL_PCU_TDP_RATIO_MSK                         (0x000000FF)
  #define CONFIG_TDP_NOMINAL_PCU_TDP_RATIO_MIN                         (0)
  #define CONFIG_TDP_NOMINAL_PCU_TDP_RATIO_MAX                         (255) // 0x000000FF
  #define CONFIG_TDP_NOMINAL_PCU_TDP_RATIO_DEF                         (0x00000000)
  #define CONFIG_TDP_NOMINAL_PCU_TDP_RATIO_HSH                         (0x08005F3C)

#define CONFIG_TDP_LEVEL1_PCU_REG                                      (0x00005F40)

  #define CONFIG_TDP_LEVEL1_PCU_PKG_TDP_OFF                            ( 0)
  #define CONFIG_TDP_LEVEL1_PCU_PKG_TDP_WID                            (15)
  #define CONFIG_TDP_LEVEL1_PCU_PKG_TDP_MSK                            (0x00007FFF)
  #define CONFIG_TDP_LEVEL1_PCU_PKG_TDP_MIN                            (0)
  #define CONFIG_TDP_LEVEL1_PCU_PKG_TDP_MAX                            (32767) // 0x00007FFF
  #define CONFIG_TDP_LEVEL1_PCU_PKG_TDP_DEF                            (0x00000000)
  #define CONFIG_TDP_LEVEL1_PCU_PKG_TDP_HSH                            (0x4F005F40)

  #define CONFIG_TDP_LEVEL1_PCU_TDP_RATIO_OFF                          (16)
  #define CONFIG_TDP_LEVEL1_PCU_TDP_RATIO_WID                          ( 8)
  #define CONFIG_TDP_LEVEL1_PCU_TDP_RATIO_MSK                          (0x00FF0000)
  #define CONFIG_TDP_LEVEL1_PCU_TDP_RATIO_MIN                          (0)
  #define CONFIG_TDP_LEVEL1_PCU_TDP_RATIO_MAX                          (255) // 0x000000FF
  #define CONFIG_TDP_LEVEL1_PCU_TDP_RATIO_DEF                          (0x00000000)
  #define CONFIG_TDP_LEVEL1_PCU_TDP_RATIO_HSH                          (0x48205F40)

  #define CONFIG_TDP_LEVEL1_PCU_PKG_MAX_PWR_OFF                        (32)
  #define CONFIG_TDP_LEVEL1_PCU_PKG_MAX_PWR_WID                        (15)
  #define CONFIG_TDP_LEVEL1_PCU_PKG_MAX_PWR_MSK                        (0x00007FFF00000000ULL)
  #define CONFIG_TDP_LEVEL1_PCU_PKG_MAX_PWR_MIN                        (0)
  #define CONFIG_TDP_LEVEL1_PCU_PKG_MAX_PWR_MAX                        (32767) // 0x00007FFF
  #define CONFIG_TDP_LEVEL1_PCU_PKG_MAX_PWR_DEF                        (0x00000000)
  #define CONFIG_TDP_LEVEL1_PCU_PKG_MAX_PWR_HSH                        (0x4F405F40)

  #define CONFIG_TDP_LEVEL1_PCU_PKG_MIN_PWR_OFF                        (48)
  #define CONFIG_TDP_LEVEL1_PCU_PKG_MIN_PWR_WID                        (15)
  #define CONFIG_TDP_LEVEL1_PCU_PKG_MIN_PWR_MSK                        (0x7FFF000000000000ULL)
  #define CONFIG_TDP_LEVEL1_PCU_PKG_MIN_PWR_MIN                        (0)
  #define CONFIG_TDP_LEVEL1_PCU_PKG_MIN_PWR_MAX                        (32767) // 0x00007FFF
  #define CONFIG_TDP_LEVEL1_PCU_PKG_MIN_PWR_DEF                        (0x00000000)
  #define CONFIG_TDP_LEVEL1_PCU_PKG_MIN_PWR_HSH                        (0x4F605F40)

#define CONFIG_TDP_LEVEL2_PCU_REG                                      (0x00005F48)
//Duplicate of CONFIG_TDP_LEVEL1_PCU_REG

#define CONFIG_TDP_CONTROL_PCU_REG                                     (0x00005F50)

  #define CONFIG_TDP_CONTROL_PCU_TDP_LEVEL_OFF                         ( 0)
  #define CONFIG_TDP_CONTROL_PCU_TDP_LEVEL_WID                         ( 2)
  #define CONFIG_TDP_CONTROL_PCU_TDP_LEVEL_MSK                         (0x00000003)
  #define CONFIG_TDP_CONTROL_PCU_TDP_LEVEL_MIN                         (0)
  #define CONFIG_TDP_CONTROL_PCU_TDP_LEVEL_MAX                         (3) // 0x00000003
  #define CONFIG_TDP_CONTROL_PCU_TDP_LEVEL_DEF                         (0x00000000)
  #define CONFIG_TDP_CONTROL_PCU_TDP_LEVEL_HSH                         (0x02005F50)

  #define CONFIG_TDP_CONTROL_PCU_CONFIG_TDP_LOCK_OFF                   (31)
  #define CONFIG_TDP_CONTROL_PCU_CONFIG_TDP_LOCK_WID                   ( 1)
  #define CONFIG_TDP_CONTROL_PCU_CONFIG_TDP_LOCK_MSK                   (0x80000000)
  #define CONFIG_TDP_CONTROL_PCU_CONFIG_TDP_LOCK_MIN                   (0)
  #define CONFIG_TDP_CONTROL_PCU_CONFIG_TDP_LOCK_MAX                   (1) // 0x00000001
  #define CONFIG_TDP_CONTROL_PCU_CONFIG_TDP_LOCK_DEF                   (0x00000000)
  #define CONFIG_TDP_CONTROL_PCU_CONFIG_TDP_LOCK_HSH                   (0x013E5F50)

#define TURBO_ACTIVATION_RATIO_PCU_REG                                 (0x00005F54)

  #define TURBO_ACTIVATION_RATIO_PCU_MAX_NON_TURBO_RATIO_OFF           ( 0)
  #define TURBO_ACTIVATION_RATIO_PCU_MAX_NON_TURBO_RATIO_WID           ( 8)
  #define TURBO_ACTIVATION_RATIO_PCU_MAX_NON_TURBO_RATIO_MSK           (0x000000FF)
  #define TURBO_ACTIVATION_RATIO_PCU_MAX_NON_TURBO_RATIO_MIN           (0)
  #define TURBO_ACTIVATION_RATIO_PCU_MAX_NON_TURBO_RATIO_MAX           (255) // 0x000000FF
  #define TURBO_ACTIVATION_RATIO_PCU_MAX_NON_TURBO_RATIO_DEF           (0x00000000)
  #define TURBO_ACTIVATION_RATIO_PCU_MAX_NON_TURBO_RATIO_HSH           (0x08005F54)

  #define TURBO_ACTIVATION_RATIO_PCU_TURBO_ACTIVATION_RATIO_LOCK_OFF   (31)
  #define TURBO_ACTIVATION_RATIO_PCU_TURBO_ACTIVATION_RATIO_LOCK_WID   ( 1)
  #define TURBO_ACTIVATION_RATIO_PCU_TURBO_ACTIVATION_RATIO_LOCK_MSK   (0x80000000)
  #define TURBO_ACTIVATION_RATIO_PCU_TURBO_ACTIVATION_RATIO_LOCK_MIN   (0)
  #define TURBO_ACTIVATION_RATIO_PCU_TURBO_ACTIVATION_RATIO_LOCK_MAX   (1) // 0x00000001
  #define TURBO_ACTIVATION_RATIO_PCU_TURBO_ACTIVATION_RATIO_LOCK_DEF   (0x00000000)
  #define TURBO_ACTIVATION_RATIO_PCU_TURBO_ACTIVATION_RATIO_LOCK_HSH   (0x013E5F54)

#define OC_STATUS_PCU_REG                                              (0x00005F58)

  #define OC_STATUS_PCU_MC_TIMING_RUNTIME_OC_ENABLED_OFF               ( 0)
  #define OC_STATUS_PCU_MC_TIMING_RUNTIME_OC_ENABLED_WID               ( 1)
  #define OC_STATUS_PCU_MC_TIMING_RUNTIME_OC_ENABLED_MSK               (0x00000001)
  #define OC_STATUS_PCU_MC_TIMING_RUNTIME_OC_ENABLED_MIN               (0)
  #define OC_STATUS_PCU_MC_TIMING_RUNTIME_OC_ENABLED_MAX               (1) // 0x00000001
  #define OC_STATUS_PCU_MC_TIMING_RUNTIME_OC_ENABLED_DEF               (0x00000000)
  #define OC_STATUS_PCU_MC_TIMING_RUNTIME_OC_ENABLED_HSH               (0x01005F58)

  #define OC_STATUS_PCU_RSVD_0_OFF                                     ( 1)
  #define OC_STATUS_PCU_RSVD_0_WID                                     ( 1)
  #define OC_STATUS_PCU_RSVD_0_MSK                                     (0x00000002)
  #define OC_STATUS_PCU_RSVD_0_MIN                                     (0)
  #define OC_STATUS_PCU_RSVD_0_MAX                                     (1) // 0x00000001
  #define OC_STATUS_PCU_RSVD_0_DEF                                     (0x00000000)
  #define OC_STATUS_PCU_RSVD_0_HSH                                     (0x01025F58)

  #define OC_STATUS_PCU_RSVD_1_OFF                                     ( 2)
  #define OC_STATUS_PCU_RSVD_1_WID                                     ( 1)
  #define OC_STATUS_PCU_RSVD_1_MSK                                     (0x00000004)
  #define OC_STATUS_PCU_RSVD_1_MIN                                     (0)
  #define OC_STATUS_PCU_RSVD_1_MAX                                     (1) // 0x00000001
  #define OC_STATUS_PCU_RSVD_1_DEF                                     (0x00000000)
  #define OC_STATUS_PCU_RSVD_1_HSH                                     (0x01045F58)

  #define OC_STATUS_PCU_RSVD_2_OFF                                     ( 3)
  #define OC_STATUS_PCU_RSVD_2_WID                                     ( 1)
  #define OC_STATUS_PCU_RSVD_2_MSK                                     (0x00000008)
  #define OC_STATUS_PCU_RSVD_2_MIN                                     (0)
  #define OC_STATUS_PCU_RSVD_2_MAX                                     (1) // 0x00000001
  #define OC_STATUS_PCU_RSVD_2_DEF                                     (0x00000000)
  #define OC_STATUS_PCU_RSVD_2_HSH                                     (0x01065F58)
#pragma pack(pop)
#endif
