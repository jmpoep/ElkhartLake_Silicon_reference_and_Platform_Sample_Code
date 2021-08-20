#ifndef __MrcMcRegisterIcl6xxx_h__
#define __MrcMcRegisterIcl6xxx_h__
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


#define CCF_IDP_CHANNEL_HASH_REG                                       (0x00006040)

  #define CCF_IDP_CHANNEL_HASH_HASH_MASK_OFF                           ( 6)
  #define CCF_IDP_CHANNEL_HASH_HASH_MASK_WID                           (14)
  #define CCF_IDP_CHANNEL_HASH_HASH_MASK_MSK                           (0x000FFFC0)
  #define CCF_IDP_CHANNEL_HASH_HASH_MASK_MIN                           (0)
  #define CCF_IDP_CHANNEL_HASH_HASH_MASK_MAX                           (16383) // 0x00003FFF
  #define CCF_IDP_CHANNEL_HASH_HASH_MASK_DEF                           (0x00000000)
  #define CCF_IDP_CHANNEL_HASH_HASH_MASK_HSH                           (0x0E066040)

  #define CCF_IDP_CHANNEL_HASH_HASH_LSB_MASK_BIT_OFF                   (24)
  #define CCF_IDP_CHANNEL_HASH_HASH_LSB_MASK_BIT_WID                   ( 3)
  #define CCF_IDP_CHANNEL_HASH_HASH_LSB_MASK_BIT_MSK                   (0x07000000)
  #define CCF_IDP_CHANNEL_HASH_HASH_LSB_MASK_BIT_MIN                   (0)
  #define CCF_IDP_CHANNEL_HASH_HASH_LSB_MASK_BIT_MAX                   (7) // 0x00000007
  #define CCF_IDP_CHANNEL_HASH_HASH_LSB_MASK_BIT_DEF                   (0x00000000)
  #define CCF_IDP_CHANNEL_HASH_HASH_LSB_MASK_BIT_HSH                   (0x03186040)

  #define CCF_IDP_CHANNEL_HASH_HASH_MODE_OFF                           (28)
  #define CCF_IDP_CHANNEL_HASH_HASH_MODE_WID                           ( 1)
  #define CCF_IDP_CHANNEL_HASH_HASH_MODE_MSK                           (0x10000000)
  #define CCF_IDP_CHANNEL_HASH_HASH_MODE_MIN                           (0)
  #define CCF_IDP_CHANNEL_HASH_HASH_MODE_MAX                           (1) // 0x00000001
  #define CCF_IDP_CHANNEL_HASH_HASH_MODE_DEF                           (0x00000000)
  #define CCF_IDP_CHANNEL_HASH_HASH_MODE_HSH                           (0x011C6040)

#define CCF_IDP_CHANNEL_EHASH_REG                                      (0x00006044)

  #define CCF_IDP_CHANNEL_EHASH_EHASH_MASK_OFF                         ( 6)
  #define CCF_IDP_CHANNEL_EHASH_EHASH_MASK_WID                         (14)
  #define CCF_IDP_CHANNEL_EHASH_EHASH_MASK_MSK                         (0x000FFFC0)
  #define CCF_IDP_CHANNEL_EHASH_EHASH_MASK_MIN                         (0)
  #define CCF_IDP_CHANNEL_EHASH_EHASH_MASK_MAX                         (16383) // 0x00003FFF
  #define CCF_IDP_CHANNEL_EHASH_EHASH_MASK_DEF                         (0x00000000)
  #define CCF_IDP_CHANNEL_EHASH_EHASH_MASK_HSH                         (0x0E066044)

  #define CCF_IDP_CHANNEL_EHASH_EHASH_LSB_MASK_BIT_OFF                 (24)
  #define CCF_IDP_CHANNEL_EHASH_EHASH_LSB_MASK_BIT_WID                 ( 3)
  #define CCF_IDP_CHANNEL_EHASH_EHASH_LSB_MASK_BIT_MSK                 (0x07000000)
  #define CCF_IDP_CHANNEL_EHASH_EHASH_LSB_MASK_BIT_MIN                 (0)
  #define CCF_IDP_CHANNEL_EHASH_EHASH_LSB_MASK_BIT_MAX                 (7) // 0x00000007
  #define CCF_IDP_CHANNEL_EHASH_EHASH_LSB_MASK_BIT_DEF                 (0x00000000)
  #define CCF_IDP_CHANNEL_EHASH_EHASH_LSB_MASK_BIT_HSH                 (0x03186044)

  #define CCF_IDP_CHANNEL_EHASH_EHASH_MODE_OFF                         (28)
  #define CCF_IDP_CHANNEL_EHASH_EHASH_MODE_WID                         ( 1)
  #define CCF_IDP_CHANNEL_EHASH_EHASH_MODE_MSK                         (0x10000000)
  #define CCF_IDP_CHANNEL_EHASH_EHASH_MODE_MIN                         (0)
  #define CCF_IDP_CHANNEL_EHASH_EHASH_MODE_MAX                         (1) // 0x00000001
  #define CCF_IDP_CHANNEL_EHASH_EHASH_MODE_DEF                         (0x00000000)
  #define CCF_IDP_CHANNEL_EHASH_EHASH_MODE_HSH                         (0x011C6044)

  #define CCF_IDP_CHANNEL_EHASH_MLMC_IS_BA0_OFF                        (29)
  #define CCF_IDP_CHANNEL_EHASH_MLMC_IS_BA0_WID                        ( 1)
  #define CCF_IDP_CHANNEL_EHASH_MLMC_IS_BA0_MSK                        (0x20000000)
  #define CCF_IDP_CHANNEL_EHASH_MLMC_IS_BA0_MIN                        (0)
  #define CCF_IDP_CHANNEL_EHASH_MLMC_IS_BA0_MAX                        (1) // 0x00000001
  #define CCF_IDP_CHANNEL_EHASH_MLMC_IS_BA0_DEF                        (0x00000000)
  #define CCF_IDP_CHANNEL_EHASH_MLMC_IS_BA0_HSH                        (0x011D6044)

#define CCF_IDP_MAD_INTER_CHANNEL_REG                                  (0x00006048)

  #define CCF_IDP_MAD_INTER_CHANNEL_DDR_TYPE_OFF                       ( 0)
  #define CCF_IDP_MAD_INTER_CHANNEL_DDR_TYPE_WID                       ( 3)
  #define CCF_IDP_MAD_INTER_CHANNEL_DDR_TYPE_MSK                       (0x00000007)
  #define CCF_IDP_MAD_INTER_CHANNEL_DDR_TYPE_MIN                       (0)
  #define CCF_IDP_MAD_INTER_CHANNEL_DDR_TYPE_MAX                       (7) // 0x00000007
  #define CCF_IDP_MAD_INTER_CHANNEL_DDR_TYPE_DEF                       (0x00000000)
  #define CCF_IDP_MAD_INTER_CHANNEL_DDR_TYPE_HSH                       (0x03006048)

  #define CCF_IDP_MAD_INTER_CHANNEL_ECHM_OFF                           ( 3)
  #define CCF_IDP_MAD_INTER_CHANNEL_ECHM_WID                           ( 1)
  #define CCF_IDP_MAD_INTER_CHANNEL_ECHM_MSK                           (0x00000008)
  #define CCF_IDP_MAD_INTER_CHANNEL_ECHM_MIN                           (0)
  #define CCF_IDP_MAD_INTER_CHANNEL_ECHM_MAX                           (1) // 0x00000001
  #define CCF_IDP_MAD_INTER_CHANNEL_ECHM_DEF                           (0x00000000)
  #define CCF_IDP_MAD_INTER_CHANNEL_ECHM_HSH                           (0x01036048)

  #define CCF_IDP_MAD_INTER_CHANNEL_CH_L_MAP_OFF                       ( 4)
  #define CCF_IDP_MAD_INTER_CHANNEL_CH_L_MAP_WID                       ( 1)
  #define CCF_IDP_MAD_INTER_CHANNEL_CH_L_MAP_MSK                       (0x00000010)
  #define CCF_IDP_MAD_INTER_CHANNEL_CH_L_MAP_MIN                       (0)
  #define CCF_IDP_MAD_INTER_CHANNEL_CH_L_MAP_MAX                       (1) // 0x00000001
  #define CCF_IDP_MAD_INTER_CHANNEL_CH_L_MAP_DEF                       (0x00000000)
  #define CCF_IDP_MAD_INTER_CHANNEL_CH_L_MAP_HSH                       (0x01046048)

  #define CCF_IDP_MAD_INTER_CHANNEL_STKD_MODE_OFF                      ( 8)
  #define CCF_IDP_MAD_INTER_CHANNEL_STKD_MODE_WID                      ( 1)
  #define CCF_IDP_MAD_INTER_CHANNEL_STKD_MODE_MSK                      (0x00000100)
  #define CCF_IDP_MAD_INTER_CHANNEL_STKD_MODE_MIN                      (0)
  #define CCF_IDP_MAD_INTER_CHANNEL_STKD_MODE_MAX                      (1) // 0x00000001
  #define CCF_IDP_MAD_INTER_CHANNEL_STKD_MODE_DEF                      (0x00000000)
  #define CCF_IDP_MAD_INTER_CHANNEL_STKD_MODE_HSH                      (0x01086048)

  #define CCF_IDP_MAD_INTER_CHANNEL_STKD_MODE_CH1_OFF                  ( 9)
  #define CCF_IDP_MAD_INTER_CHANNEL_STKD_MODE_CH1_WID                  ( 1)
  #define CCF_IDP_MAD_INTER_CHANNEL_STKD_MODE_CH1_MSK                  (0x00000200)
  #define CCF_IDP_MAD_INTER_CHANNEL_STKD_MODE_CH1_MIN                  (0)
  #define CCF_IDP_MAD_INTER_CHANNEL_STKD_MODE_CH1_MAX                  (1) // 0x00000001
  #define CCF_IDP_MAD_INTER_CHANNEL_STKD_MODE_CH1_DEF                  (0x00000000)
  #define CCF_IDP_MAD_INTER_CHANNEL_STKD_MODE_CH1_HSH                  (0x01096048)

  #define CCF_IDP_MAD_INTER_CHANNEL_CH_S_SIZE_OFF                      (12)
  #define CCF_IDP_MAD_INTER_CHANNEL_CH_S_SIZE_WID                      ( 8)
  #define CCF_IDP_MAD_INTER_CHANNEL_CH_S_SIZE_MSK                      (0x000FF000)
  #define CCF_IDP_MAD_INTER_CHANNEL_CH_S_SIZE_MIN                      (0)
  #define CCF_IDP_MAD_INTER_CHANNEL_CH_S_SIZE_MAX                      (255) // 0x000000FF
  #define CCF_IDP_MAD_INTER_CHANNEL_CH_S_SIZE_DEF                      (0x00000000)
  #define CCF_IDP_MAD_INTER_CHANNEL_CH_S_SIZE_HSH                      (0x080C6048)

  #define CCF_IDP_MAD_INTER_CHANNEL_STKD_MODE_CH_BITS_OFF              (24)
  #define CCF_IDP_MAD_INTER_CHANNEL_STKD_MODE_CH_BITS_WID              ( 3)
  #define CCF_IDP_MAD_INTER_CHANNEL_STKD_MODE_CH_BITS_MSK              (0x07000000)
  #define CCF_IDP_MAD_INTER_CHANNEL_STKD_MODE_CH_BITS_MIN              (0)
  #define CCF_IDP_MAD_INTER_CHANNEL_STKD_MODE_CH_BITS_MAX              (7) // 0x00000007
  #define CCF_IDP_MAD_INTER_CHANNEL_STKD_MODE_CH_BITS_DEF              (0x00000000)
  #define CCF_IDP_MAD_INTER_CHANNEL_STKD_MODE_CH_BITS_HSH              (0x03186048)

#define CCF_IDP_MAD_INTRA_CH0_REG                                      (0x0000604C)

  #define CCF_IDP_MAD_INTRA_CH0_DIMM_L_MAP_OFF                         ( 0)
  #define CCF_IDP_MAD_INTRA_CH0_DIMM_L_MAP_WID                         ( 1)
  #define CCF_IDP_MAD_INTRA_CH0_DIMM_L_MAP_MSK                         (0x00000001)
  #define CCF_IDP_MAD_INTRA_CH0_DIMM_L_MAP_MIN                         (0)
  #define CCF_IDP_MAD_INTRA_CH0_DIMM_L_MAP_MAX                         (1) // 0x00000001
  #define CCF_IDP_MAD_INTRA_CH0_DIMM_L_MAP_DEF                         (0x00000000)
  #define CCF_IDP_MAD_INTRA_CH0_DIMM_L_MAP_HSH                         (0x0100604C)

  #define CCF_IDP_MAD_INTRA_CH0_RI_OFF                                 ( 4)
  #define CCF_IDP_MAD_INTRA_CH0_RI_WID                                 ( 1)
  #define CCF_IDP_MAD_INTRA_CH0_RI_MSK                                 (0x00000010)
  #define CCF_IDP_MAD_INTRA_CH0_RI_MIN                                 (0)
  #define CCF_IDP_MAD_INTRA_CH0_RI_MAX                                 (1) // 0x00000001
  #define CCF_IDP_MAD_INTRA_CH0_RI_DEF                                 (0x00000000)
  #define CCF_IDP_MAD_INTRA_CH0_RI_HSH                                 (0x0104604C)

  #define CCF_IDP_MAD_INTRA_CH0_EIM_OFF                                ( 8)
  #define CCF_IDP_MAD_INTRA_CH0_EIM_WID                                ( 1)
  #define CCF_IDP_MAD_INTRA_CH0_EIM_MSK                                (0x00000100)
  #define CCF_IDP_MAD_INTRA_CH0_EIM_MIN                                (0)
  #define CCF_IDP_MAD_INTRA_CH0_EIM_MAX                                (1) // 0x00000001
  #define CCF_IDP_MAD_INTRA_CH0_EIM_DEF                                (0x00000000)
  #define CCF_IDP_MAD_INTRA_CH0_EIM_HSH                                (0x0108604C)

  #define CCF_IDP_MAD_INTRA_CH0_ECC_OFF                                (12)
  #define CCF_IDP_MAD_INTRA_CH0_ECC_WID                                ( 2)
  #define CCF_IDP_MAD_INTRA_CH0_ECC_MSK                                (0x00003000)
  #define CCF_IDP_MAD_INTRA_CH0_ECC_MIN                                (0)
  #define CCF_IDP_MAD_INTRA_CH0_ECC_MAX                                (3) // 0x00000003
  #define CCF_IDP_MAD_INTRA_CH0_ECC_DEF                                (0x00000000)
  #define CCF_IDP_MAD_INTRA_CH0_ECC_HSH                                (0x020C604C)

#define CCF_IDP_MAD_INTRA_CH1_REG                                      (0x00006050)

  #define CCF_IDP_MAD_INTRA_CH1_DIMM_L_MAP_OFF                         ( 0)
  #define CCF_IDP_MAD_INTRA_CH1_DIMM_L_MAP_WID                         ( 1)
  #define CCF_IDP_MAD_INTRA_CH1_DIMM_L_MAP_MSK                         (0x00000001)
  #define CCF_IDP_MAD_INTRA_CH1_DIMM_L_MAP_MIN                         (0)
  #define CCF_IDP_MAD_INTRA_CH1_DIMM_L_MAP_MAX                         (1) // 0x00000001
  #define CCF_IDP_MAD_INTRA_CH1_DIMM_L_MAP_DEF                         (0x00000000)
  #define CCF_IDP_MAD_INTRA_CH1_DIMM_L_MAP_HSH                         (0x01006050)

  #define CCF_IDP_MAD_INTRA_CH1_RI_OFF                                 ( 4)
  #define CCF_IDP_MAD_INTRA_CH1_RI_WID                                 ( 1)
  #define CCF_IDP_MAD_INTRA_CH1_RI_MSK                                 (0x00000010)
  #define CCF_IDP_MAD_INTRA_CH1_RI_MIN                                 (0)
  #define CCF_IDP_MAD_INTRA_CH1_RI_MAX                                 (1) // 0x00000001
  #define CCF_IDP_MAD_INTRA_CH1_RI_DEF                                 (0x00000000)
  #define CCF_IDP_MAD_INTRA_CH1_RI_HSH                                 (0x01046050)

  #define CCF_IDP_MAD_INTRA_CH1_EIM_OFF                                ( 8)
  #define CCF_IDP_MAD_INTRA_CH1_EIM_WID                                ( 1)
  #define CCF_IDP_MAD_INTRA_CH1_EIM_MSK                                (0x00000100)
  #define CCF_IDP_MAD_INTRA_CH1_EIM_MIN                                (0)
  #define CCF_IDP_MAD_INTRA_CH1_EIM_MAX                                (1) // 0x00000001
  #define CCF_IDP_MAD_INTRA_CH1_EIM_DEF                                (0x00000000)
  #define CCF_IDP_MAD_INTRA_CH1_EIM_HSH                                (0x01086050)

  #define CCF_IDP_MAD_INTRA_CH1_ECC_OFF                                (12)
  #define CCF_IDP_MAD_INTRA_CH1_ECC_WID                                ( 2)
  #define CCF_IDP_MAD_INTRA_CH1_ECC_MSK                                (0x00003000)
  #define CCF_IDP_MAD_INTRA_CH1_ECC_MIN                                (0)
  #define CCF_IDP_MAD_INTRA_CH1_ECC_MAX                                (3) // 0x00000003
  #define CCF_IDP_MAD_INTRA_CH1_ECC_DEF                                (0x00000000)
  #define CCF_IDP_MAD_INTRA_CH1_ECC_HSH                                (0x020C6050)

#define CCF_IDP_MAD_DIMM_CH0_REG                                       (0x00006054)

  #define CCF_IDP_MAD_DIMM_CH0_DIMM_L_SIZE_OFF                         ( 0)
  #define CCF_IDP_MAD_DIMM_CH0_DIMM_L_SIZE_WID                         ( 7)
  #define CCF_IDP_MAD_DIMM_CH0_DIMM_L_SIZE_MSK                         (0x0000007F)
  #define CCF_IDP_MAD_DIMM_CH0_DIMM_L_SIZE_MIN                         (0)
  #define CCF_IDP_MAD_DIMM_CH0_DIMM_L_SIZE_MAX                         (127) // 0x0000007F
  #define CCF_IDP_MAD_DIMM_CH0_DIMM_L_SIZE_DEF                         (0x00000000)
  #define CCF_IDP_MAD_DIMM_CH0_DIMM_L_SIZE_HSH                         (0x07006054)

  #define CCF_IDP_MAD_DIMM_CH0_DLW_OFF                                 ( 7)
  #define CCF_IDP_MAD_DIMM_CH0_DLW_WID                                 ( 2)
  #define CCF_IDP_MAD_DIMM_CH0_DLW_MSK                                 (0x00000180)
  #define CCF_IDP_MAD_DIMM_CH0_DLW_MIN                                 (0)
  #define CCF_IDP_MAD_DIMM_CH0_DLW_MAX                                 (3) // 0x00000003
  #define CCF_IDP_MAD_DIMM_CH0_DLW_DEF                                 (0x00000000)
  #define CCF_IDP_MAD_DIMM_CH0_DLW_HSH                                 (0x02076054)

  #define CCF_IDP_MAD_DIMM_CH0_DLNOR_OFF                               ( 9)
  #define CCF_IDP_MAD_DIMM_CH0_DLNOR_WID                               ( 2)
  #define CCF_IDP_MAD_DIMM_CH0_DLNOR_MSK                               (0x00000600)
  #define CCF_IDP_MAD_DIMM_CH0_DLNOR_MIN                               (0)
  #define CCF_IDP_MAD_DIMM_CH0_DLNOR_MAX                               (3) // 0x00000003
  #define CCF_IDP_MAD_DIMM_CH0_DLNOR_DEF                               (0x00000000)
  #define CCF_IDP_MAD_DIMM_CH0_DLNOR_HSH                               (0x02096054)

  #define CCF_IDP_MAD_DIMM_CH0_DL8Gb_OFF                               (11)
  #define CCF_IDP_MAD_DIMM_CH0_DL8Gb_WID                               ( 1)
  #define CCF_IDP_MAD_DIMM_CH0_DL8Gb_MSK                               (0x00000800)
  #define CCF_IDP_MAD_DIMM_CH0_DL8Gb_MIN                               (0)
  #define CCF_IDP_MAD_DIMM_CH0_DL8Gb_MAX                               (1) // 0x00000001
  #define CCF_IDP_MAD_DIMM_CH0_DL8Gb_DEF                               (0x00000000)
  #define CCF_IDP_MAD_DIMM_CH0_DL8Gb_HSH                               (0x010B6054)

  #define CCF_IDP_MAD_DIMM_CH0_DIMM_S_SIZE_OFF                         (16)
  #define CCF_IDP_MAD_DIMM_CH0_DIMM_S_SIZE_WID                         ( 7)
  #define CCF_IDP_MAD_DIMM_CH0_DIMM_S_SIZE_MSK                         (0x007F0000)
  #define CCF_IDP_MAD_DIMM_CH0_DIMM_S_SIZE_MIN                         (0)
  #define CCF_IDP_MAD_DIMM_CH0_DIMM_S_SIZE_MAX                         (127) // 0x0000007F
  #define CCF_IDP_MAD_DIMM_CH0_DIMM_S_SIZE_DEF                         (0x00000000)
  #define CCF_IDP_MAD_DIMM_CH0_DIMM_S_SIZE_HSH                         (0x07106054)

  #define CCF_IDP_MAD_DIMM_CH0_DSW_OFF                                 (24)
  #define CCF_IDP_MAD_DIMM_CH0_DSW_WID                                 ( 2)
  #define CCF_IDP_MAD_DIMM_CH0_DSW_MSK                                 (0x03000000)
  #define CCF_IDP_MAD_DIMM_CH0_DSW_MIN                                 (0)
  #define CCF_IDP_MAD_DIMM_CH0_DSW_MAX                                 (3) // 0x00000003
  #define CCF_IDP_MAD_DIMM_CH0_DSW_DEF                                 (0x00000000)
  #define CCF_IDP_MAD_DIMM_CH0_DSW_HSH                                 (0x02186054)

  #define CCF_IDP_MAD_DIMM_CH0_DSNOR_OFF                               (26)
  #define CCF_IDP_MAD_DIMM_CH0_DSNOR_WID                               ( 2)
  #define CCF_IDP_MAD_DIMM_CH0_DSNOR_MSK                               (0x0C000000)
  #define CCF_IDP_MAD_DIMM_CH0_DSNOR_MIN                               (0)
  #define CCF_IDP_MAD_DIMM_CH0_DSNOR_MAX                               (3) // 0x00000003
  #define CCF_IDP_MAD_DIMM_CH0_DSNOR_DEF                               (0x00000000)
  #define CCF_IDP_MAD_DIMM_CH0_DSNOR_HSH                               (0x021A6054)

  #define CCF_IDP_MAD_DIMM_CH0_DS8Gb_OFF                               (28)
  #define CCF_IDP_MAD_DIMM_CH0_DS8Gb_WID                               ( 1)
  #define CCF_IDP_MAD_DIMM_CH0_DS8Gb_MSK                               (0x10000000)
  #define CCF_IDP_MAD_DIMM_CH0_DS8Gb_MIN                               (0)
  #define CCF_IDP_MAD_DIMM_CH0_DS8Gb_MAX                               (1) // 0x00000001
  #define CCF_IDP_MAD_DIMM_CH0_DS8Gb_DEF                               (0x00000000)
  #define CCF_IDP_MAD_DIMM_CH0_DS8Gb_HSH                               (0x011C6054)

  #define CCF_IDP_MAD_DIMM_CH0_DLS_BG0_on_bit_11_OFF                   (29)
  #define CCF_IDP_MAD_DIMM_CH0_DLS_BG0_on_bit_11_WID                   ( 1)
  #define CCF_IDP_MAD_DIMM_CH0_DLS_BG0_on_bit_11_MSK                   (0x20000000)
  #define CCF_IDP_MAD_DIMM_CH0_DLS_BG0_on_bit_11_MIN                   (0)
  #define CCF_IDP_MAD_DIMM_CH0_DLS_BG0_on_bit_11_MAX                   (1) // 0x00000001
  #define CCF_IDP_MAD_DIMM_CH0_DLS_BG0_on_bit_11_DEF                   (0x00000000)
  #define CCF_IDP_MAD_DIMM_CH0_DLS_BG0_on_bit_11_HSH                   (0x011D6054)

#define CCF_IDP_MAD_DIMM_CH1_REG                                       (0x00006058)

  #define CCF_IDP_MAD_DIMM_CH1_DIMM_L_SIZE_OFF                         ( 0)
  #define CCF_IDP_MAD_DIMM_CH1_DIMM_L_SIZE_WID                         ( 7)
  #define CCF_IDP_MAD_DIMM_CH1_DIMM_L_SIZE_MSK                         (0x0000007F)
  #define CCF_IDP_MAD_DIMM_CH1_DIMM_L_SIZE_MIN                         (0)
  #define CCF_IDP_MAD_DIMM_CH1_DIMM_L_SIZE_MAX                         (127) // 0x0000007F
  #define CCF_IDP_MAD_DIMM_CH1_DIMM_L_SIZE_DEF                         (0x00000000)
  #define CCF_IDP_MAD_DIMM_CH1_DIMM_L_SIZE_HSH                         (0x07006058)

  #define CCF_IDP_MAD_DIMM_CH1_DLW_OFF                                 ( 7)
  #define CCF_IDP_MAD_DIMM_CH1_DLW_WID                                 ( 2)
  #define CCF_IDP_MAD_DIMM_CH1_DLW_MSK                                 (0x00000180)
  #define CCF_IDP_MAD_DIMM_CH1_DLW_MIN                                 (0)
  #define CCF_IDP_MAD_DIMM_CH1_DLW_MAX                                 (3) // 0x00000003
  #define CCF_IDP_MAD_DIMM_CH1_DLW_DEF                                 (0x00000000)
  #define CCF_IDP_MAD_DIMM_CH1_DLW_HSH                                 (0x02076058)

  #define CCF_IDP_MAD_DIMM_CH1_DLNOR_OFF                               ( 9)
  #define CCF_IDP_MAD_DIMM_CH1_DLNOR_WID                               ( 2)
  #define CCF_IDP_MAD_DIMM_CH1_DLNOR_MSK                               (0x00000600)
  #define CCF_IDP_MAD_DIMM_CH1_DLNOR_MIN                               (0)
  #define CCF_IDP_MAD_DIMM_CH1_DLNOR_MAX                               (3) // 0x00000003
  #define CCF_IDP_MAD_DIMM_CH1_DLNOR_DEF                               (0x00000000)
  #define CCF_IDP_MAD_DIMM_CH1_DLNOR_HSH                               (0x02096058)

  #define CCF_IDP_MAD_DIMM_CH1_DL8Gb_OFF                               (11)
  #define CCF_IDP_MAD_DIMM_CH1_DL8Gb_WID                               ( 1)
  #define CCF_IDP_MAD_DIMM_CH1_DL8Gb_MSK                               (0x00000800)
  #define CCF_IDP_MAD_DIMM_CH1_DL8Gb_MIN                               (0)
  #define CCF_IDP_MAD_DIMM_CH1_DL8Gb_MAX                               (1) // 0x00000001
  #define CCF_IDP_MAD_DIMM_CH1_DL8Gb_DEF                               (0x00000000)
  #define CCF_IDP_MAD_DIMM_CH1_DL8Gb_HSH                               (0x010B6058)

  #define CCF_IDP_MAD_DIMM_CH1_DIMM_S_SIZE_OFF                         (16)
  #define CCF_IDP_MAD_DIMM_CH1_DIMM_S_SIZE_WID                         ( 7)
  #define CCF_IDP_MAD_DIMM_CH1_DIMM_S_SIZE_MSK                         (0x007F0000)
  #define CCF_IDP_MAD_DIMM_CH1_DIMM_S_SIZE_MIN                         (0)
  #define CCF_IDP_MAD_DIMM_CH1_DIMM_S_SIZE_MAX                         (127) // 0x0000007F
  #define CCF_IDP_MAD_DIMM_CH1_DIMM_S_SIZE_DEF                         (0x00000000)
  #define CCF_IDP_MAD_DIMM_CH1_DIMM_S_SIZE_HSH                         (0x07106058)

  #define CCF_IDP_MAD_DIMM_CH1_DSW_OFF                                 (24)
  #define CCF_IDP_MAD_DIMM_CH1_DSW_WID                                 ( 2)
  #define CCF_IDP_MAD_DIMM_CH1_DSW_MSK                                 (0x03000000)
  #define CCF_IDP_MAD_DIMM_CH1_DSW_MIN                                 (0)
  #define CCF_IDP_MAD_DIMM_CH1_DSW_MAX                                 (3) // 0x00000003
  #define CCF_IDP_MAD_DIMM_CH1_DSW_DEF                                 (0x00000000)
  #define CCF_IDP_MAD_DIMM_CH1_DSW_HSH                                 (0x02186058)

  #define CCF_IDP_MAD_DIMM_CH1_DSNOR_OFF                               (26)
  #define CCF_IDP_MAD_DIMM_CH1_DSNOR_WID                               ( 2)
  #define CCF_IDP_MAD_DIMM_CH1_DSNOR_MSK                               (0x0C000000)
  #define CCF_IDP_MAD_DIMM_CH1_DSNOR_MIN                               (0)
  #define CCF_IDP_MAD_DIMM_CH1_DSNOR_MAX                               (3) // 0x00000003
  #define CCF_IDP_MAD_DIMM_CH1_DSNOR_DEF                               (0x00000000)
  #define CCF_IDP_MAD_DIMM_CH1_DSNOR_HSH                               (0x021A6058)

  #define CCF_IDP_MAD_DIMM_CH1_DS8Gb_OFF                               (28)
  #define CCF_IDP_MAD_DIMM_CH1_DS8Gb_WID                               ( 1)
  #define CCF_IDP_MAD_DIMM_CH1_DS8Gb_MSK                               (0x10000000)
  #define CCF_IDP_MAD_DIMM_CH1_DS8Gb_MIN                               (0)
  #define CCF_IDP_MAD_DIMM_CH1_DS8Gb_MAX                               (1) // 0x00000001
  #define CCF_IDP_MAD_DIMM_CH1_DS8Gb_DEF                               (0x00000000)
  #define CCF_IDP_MAD_DIMM_CH1_DS8Gb_HSH                               (0x011C6058)

  #define CCF_IDP_MAD_DIMM_CH1_DLS_BG0_on_bit_11_OFF                   (29)
  #define CCF_IDP_MAD_DIMM_CH1_DLS_BG0_on_bit_11_WID                   ( 1)
  #define CCF_IDP_MAD_DIMM_CH1_DLS_BG0_on_bit_11_MSK                   (0x20000000)
  #define CCF_IDP_MAD_DIMM_CH1_DLS_BG0_on_bit_11_MIN                   (0)
  #define CCF_IDP_MAD_DIMM_CH1_DLS_BG0_on_bit_11_MAX                   (1) // 0x00000001
  #define CCF_IDP_MAD_DIMM_CH1_DLS_BG0_on_bit_11_DEF                   (0x00000000)
  #define CCF_IDP_MAD_DIMM_CH1_DLS_BG0_on_bit_11_HSH                   (0x011D6058)

#define CCF_IDP_MARS_ENABLE_REG                                        (0x0000605C)

  #define CCF_IDP_MARS_ENABLE_MARS_Enable_OFF                          ( 0)
  #define CCF_IDP_MARS_ENABLE_MARS_Enable_WID                          ( 1)
  #define CCF_IDP_MARS_ENABLE_MARS_Enable_MSK                          (0x00000001)
  #define CCF_IDP_MARS_ENABLE_MARS_Enable_MIN                          (0)
  #define CCF_IDP_MARS_ENABLE_MARS_Enable_MAX                          (1) // 0x00000001
  #define CCF_IDP_MARS_ENABLE_MARS_Enable_DEF                          (0x00000000)
  #define CCF_IDP_MARS_ENABLE_MARS_Enable_HSH                          (0x0100605C)

// IDP1
#define CCF_IDP1_CHANNEL_HASH_REG                                      (0x00006240)
#define CCF_IDP1_CHANNEL_EHASH_REG                                     (0x00006244)
#define CCF_IDP1_MAD_INTER_CHANNEL_REG                                 (0x00006248)
#define CCF_IDP1_MAD_INTRA_CH0_REG                                     (0x0000624C)
#define CCF_IDP1_MAD_INTRA_CH1_REG                                     (0x00006250)
#define CCF_IDP1_MAD_DIMM_CH0_REG                                      (0x00006254)
#define CCF_IDP1_MAD_DIMM_CH1_REG                                      (0x00006258)
#define CCF_IDP1_MARS_ENABLE_REG                                       (0x0000625C)

#define TRUSTED_ACCESS_POLICY_CP_REG                                   (0x00006400)

  #define TRUSTED_ACCESS_POLICY_CP_SAI_MASK_OFF                        ( 0)
  #define TRUSTED_ACCESS_POLICY_CP_SAI_MASK_WID                        (64)
  #define TRUSTED_ACCESS_POLICY_CP_SAI_MASK_MSK                        (0xFFFFFFFFFFFFFFFFULL)
  #define TRUSTED_ACCESS_POLICY_CP_SAI_MASK_MIN                        (0)
  #define TRUSTED_ACCESS_POLICY_CP_SAI_MASK_MAX                        (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define TRUSTED_ACCESS_POLICY_CP_SAI_MASK_DEF                        (0x40001000208)
  #define TRUSTED_ACCESS_POLICY_CP_SAI_MASK_HSH                        (0x40006400)

#define TRUSTED_ACCESS_POLICY_WAC_REG                                  (0x00006408)

  #define TRUSTED_ACCESS_POLICY_WAC_SAI_MASK_OFF                       ( 0)
  #define TRUSTED_ACCESS_POLICY_WAC_SAI_MASK_WID                       (64)
  #define TRUSTED_ACCESS_POLICY_WAC_SAI_MASK_MSK                       (0xFFFFFFFFFFFFFFFFULL)
  #define TRUSTED_ACCESS_POLICY_WAC_SAI_MASK_MIN                       (0)
  #define TRUSTED_ACCESS_POLICY_WAC_SAI_MASK_MAX                       (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define TRUSTED_ACCESS_POLICY_WAC_SAI_MASK_DEF                       (0x4000100021A)
  #define TRUSTED_ACCESS_POLICY_WAC_SAI_MASK_HSH                       (0x40006408)

#define TRUSTED_ACCESS_POLICY_RAC_REG                                  (0x00006410)

  #define TRUSTED_ACCESS_POLICY_RAC_SAI_MASK_OFF                       ( 0)
  #define TRUSTED_ACCESS_POLICY_RAC_SAI_MASK_WID                       (64)
  #define TRUSTED_ACCESS_POLICY_RAC_SAI_MASK_MSK                       (0xFFFFFFFFFFFFFFFFULL)
  #define TRUSTED_ACCESS_POLICY_RAC_SAI_MASK_MIN                       (0)
  #define TRUSTED_ACCESS_POLICY_RAC_SAI_MASK_MAX                       (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define TRUSTED_ACCESS_POLICY_RAC_SAI_MASK_DEF                       (0xFFFFFFFFFFFFFFFF)
  #define TRUSTED_ACCESS_POLICY_RAC_SAI_MASK_HSH                       (0x40006410)

#define PRIO_THRESHOLD_REG                                             (0x00006418)

  #define PRIO_THRESHOLD_NON_VC1_PRIO_THRESHOLD_OFF                    ( 0)
  #define PRIO_THRESHOLD_NON_VC1_PRIO_THRESHOLD_WID                    (16)
  #define PRIO_THRESHOLD_NON_VC1_PRIO_THRESHOLD_MSK                    (0x0000FFFF)
  #define PRIO_THRESHOLD_NON_VC1_PRIO_THRESHOLD_MIN                    (0)
  #define PRIO_THRESHOLD_NON_VC1_PRIO_THRESHOLD_MAX                    (65535) // 0x0000FFFF
  #define PRIO_THRESHOLD_NON_VC1_PRIO_THRESHOLD_DEF                    (0x00000008)
  #define PRIO_THRESHOLD_NON_VC1_PRIO_THRESHOLD_HSH                    (0x10006418)

  #define PRIO_THRESHOLD_VC1_RD_PRIO_THRESHOLD_OFF                     (16)
  #define PRIO_THRESHOLD_VC1_RD_PRIO_THRESHOLD_WID                     (16)
  #define PRIO_THRESHOLD_VC1_RD_PRIO_THRESHOLD_MSK                     (0xFFFF0000)
  #define PRIO_THRESHOLD_VC1_RD_PRIO_THRESHOLD_MIN                     (0)
  #define PRIO_THRESHOLD_VC1_RD_PRIO_THRESHOLD_MAX                     (65535) // 0x0000FFFF
  #define PRIO_THRESHOLD_VC1_RD_PRIO_THRESHOLD_DEF                     (0x00000008)
  #define PRIO_THRESHOLD_VC1_RD_PRIO_THRESHOLD_HSH                     (0x10106418)

#define PRIO_LIM_REG                                                   (0x0000641C)

  #define PRIO_LIM_LOW_PRIORITY_LIM_OFF                                ( 0)
  #define PRIO_LIM_LOW_PRIORITY_LIM_WID                                (16)
  #define PRIO_LIM_LOW_PRIORITY_LIM_MSK                                (0x0000FFFF)
  #define PRIO_LIM_LOW_PRIORITY_LIM_MIN                                (0)
  #define PRIO_LIM_LOW_PRIORITY_LIM_MAX                                (65535) // 0x0000FFFF
  #define PRIO_LIM_LOW_PRIORITY_LIM_DEF                                (0x00000001)
  #define PRIO_LIM_LOW_PRIORITY_LIM_HSH                                (0x1000641C)

  #define PRIO_LIM_HIGH_PRIORITY_LIM_OFF                               (16)
  #define PRIO_LIM_HIGH_PRIORITY_LIM_WID                               (16)
  #define PRIO_LIM_HIGH_PRIORITY_LIM_MSK                               (0xFFFF0000)
  #define PRIO_LIM_HIGH_PRIORITY_LIM_MIN                               (0)
  #define PRIO_LIM_HIGH_PRIORITY_LIM_MAX                               (65535) // 0x0000FFFF
  #define PRIO_LIM_HIGH_PRIORITY_LIM_DEF                               (0x00000004)
  #define PRIO_LIM_HIGH_PRIORITY_LIM_HSH                               (0x1010641C)

#define CMF_GLOBAL_CFG_REG                                             (0x00006420)

  #define CMF_GLOBAL_CFG_CREDITS_CONFIG_DONE_OFF                       ( 0)
  #define CMF_GLOBAL_CFG_CREDITS_CONFIG_DONE_WID                       ( 1)
  #define CMF_GLOBAL_CFG_CREDITS_CONFIG_DONE_MSK                       (0x00000001)
  #define CMF_GLOBAL_CFG_CREDITS_CONFIG_DONE_MIN                       (0)
  #define CMF_GLOBAL_CFG_CREDITS_CONFIG_DONE_MAX                       (1) // 0x00000001
  #define CMF_GLOBAL_CFG_CREDITS_CONFIG_DONE_DEF                       (0x00000000)
  #define CMF_GLOBAL_CFG_CREDITS_CONFIG_DONE_HSH                       (0x01006420)

  #define CMF_GLOBAL_CFG_RESERVED_0_OFF                                ( 1)
  #define CMF_GLOBAL_CFG_RESERVED_0_WID                                (31)
  #define CMF_GLOBAL_CFG_RESERVED_0_MSK                                (0xFFFFFFFE)
  #define CMF_GLOBAL_CFG_RESERVED_0_MIN                                (0)
  #define CMF_GLOBAL_CFG_RESERVED_0_MAX                                (2147483647) // 0x7FFFFFFF
  #define CMF_GLOBAL_CFG_RESERVED_0_DEF                                (0x00000000)
  #define CMF_GLOBAL_CFG_RESERVED_0_HSH                                (0x1F016420)

#define CMF_ACCUM_CTRL_REG                                             (0x00006424)

  #define CMF_ACCUM_CTRL_CMD_CLEAR_OFF                                 ( 0)
  #define CMF_ACCUM_CTRL_CMD_CLEAR_WID                                 ( 1)
  #define CMF_ACCUM_CTRL_CMD_CLEAR_MSK                                 (0x00000001)
  #define CMF_ACCUM_CTRL_CMD_CLEAR_MIN                                 (0)
  #define CMF_ACCUM_CTRL_CMD_CLEAR_MAX                                 (1) // 0x00000001
  #define CMF_ACCUM_CTRL_CMD_CLEAR_DEF                                 (0x00000000)
  #define CMF_ACCUM_CTRL_CMD_CLEAR_HSH                                 (0x01006424)

  #define CMF_ACCUM_CTRL_CMD_ENABLE_OFF                                ( 1)
  #define CMF_ACCUM_CTRL_CMD_ENABLE_WID                                ( 1)
  #define CMF_ACCUM_CTRL_CMD_ENABLE_MSK                                (0x00000002)
  #define CMF_ACCUM_CTRL_CMD_ENABLE_MIN                                (0)
  #define CMF_ACCUM_CTRL_CMD_ENABLE_MAX                                (1) // 0x00000001
  #define CMF_ACCUM_CTRL_CMD_ENABLE_DEF                                (0x00000000)
  #define CMF_ACCUM_CTRL_CMD_ENABLE_HSH                                (0x01016424)

  #define CMF_ACCUM_CTRL_CMD_FUNC_OV_OFF                               ( 2)
  #define CMF_ACCUM_CTRL_CMD_FUNC_OV_WID                               ( 1)
  #define CMF_ACCUM_CTRL_CMD_FUNC_OV_MSK                               (0x00000004)
  #define CMF_ACCUM_CTRL_CMD_FUNC_OV_MIN                               (0)
  #define CMF_ACCUM_CTRL_CMD_FUNC_OV_MAX                               (1) // 0x00000001
  #define CMF_ACCUM_CTRL_CMD_FUNC_OV_DEF                               (0x00000000)
  #define CMF_ACCUM_CTRL_CMD_FUNC_OV_HSH                               (0x01026424)

  #define CMF_ACCUM_CTRL_RESERVED_OFF                                  ( 3)
  #define CMF_ACCUM_CTRL_RESERVED_WID                                  (29)
  #define CMF_ACCUM_CTRL_RESERVED_MSK                                  (0xFFFFFFF8)
  #define CMF_ACCUM_CTRL_RESERVED_MIN                                  (0)
  #define CMF_ACCUM_CTRL_RESERVED_MAX                                  (536870911) // 0x1FFFFFFF
  #define CMF_ACCUM_CTRL_RESERVED_DEF                                  (0x00000000)
  #define CMF_ACCUM_CTRL_RESERVED_HSH                                  (0x1D036424)

#define CMF_RSVD0_REG                                                  (0x00006428)

  #define CMF_RSVD0_RESERVED_OFF                                       ( 0)
  #define CMF_RSVD0_RESERVED_WID                                       (32)
  #define CMF_RSVD0_RESERVED_MSK                                       (0xFFFFFFFF)
  #define CMF_RSVD0_RESERVED_MIN                                       (0)
  #define CMF_RSVD0_RESERVED_MAX                                       (4294967295) // 0xFFFFFFFF
  #define CMF_RSVD0_RESERVED_DEF                                       (0x00000000)
  #define CMF_RSVD0_RESERVED_HSH                                       (0x20006428)

#define CMF_RSVD1_REG                                                  (0x0000642C)

  #define CMF_RSVD1_RESERVED_OFF                                       ( 0)
  #define CMF_RSVD1_RESERVED_WID                                       (32)
  #define CMF_RSVD1_RESERVED_MSK                                       (0xFFFFFFFF)
  #define CMF_RSVD1_RESERVED_MIN                                       (0)
  #define CMF_RSVD1_RESERVED_MAX                                       (4294967295) // 0xFFFFFFFF
  #define CMF_RSVD1_RESERVED_DEF                                       (0xFFFFFFFF)
  #define CMF_RSVD1_RESERVED_HSH                                       (0x2000642C)

#define CMI_IOSF_SB_EP_CTRL_REG                                        (0x00006430)

  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEDEF_OFF                    ( 0)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEDEF_WID                    ( 1)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEDEF_MSK                    (0x00000001)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEDEF_MIN                    (0)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEDEF_MAX                    (1) // 0x00000001
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEDEF_DEF                    (0x00000000)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEDEF_HSH                    (0x01006430)

  #define CMI_IOSF_SB_EP_CTRL_RSVD0_OFF                                ( 1)
  #define CMI_IOSF_SB_EP_CTRL_RSVD0_WID                                ( 7)
  #define CMI_IOSF_SB_EP_CTRL_RSVD0_MSK                                (0x000000FE)
  #define CMI_IOSF_SB_EP_CTRL_RSVD0_MIN                                (0)
  #define CMI_IOSF_SB_EP_CTRL_RSVD0_MAX                                (127) // 0x0000007F
  #define CMI_IOSF_SB_EP_CTRL_RSVD0_DEF                                (0x00000000)
  #define CMI_IOSF_SB_EP_CTRL_RSVD0_HSH                                (0x07016430)

  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEN_OFF                      ( 8)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEN_WID                      ( 1)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEN_MSK                      (0x00000100)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEN_MIN                      (0)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEN_MAX                      (1) // 0x00000001
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEN_DEF                      (0x00000001)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEN_HSH                      (0x01086430)

  #define CMI_IOSF_SB_EP_CTRL_RSVD1_OFF                                ( 9)
  #define CMI_IOSF_SB_EP_CTRL_RSVD1_WID                                ( 7)
  #define CMI_IOSF_SB_EP_CTRL_RSVD1_MSK                                (0x0000FE00)
  #define CMI_IOSF_SB_EP_CTRL_RSVD1_MIN                                (0)
  #define CMI_IOSF_SB_EP_CTRL_RSVD1_MAX                                (127) // 0x0000007F
  #define CMI_IOSF_SB_EP_CTRL_RSVD1_DEF                                (0x00000000)
  #define CMI_IOSF_SB_EP_CTRL_RSVD1_HSH                                (0x07096430)

  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_IDLECNT_OFF                       (16)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_IDLECNT_WID                       ( 8)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_IDLECNT_MSK                       (0x00FF0000)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_IDLECNT_MIN                       (0)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_IDLECNT_MAX                       (255) // 0x000000FF
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_IDLECNT_DEF                       (0x00000010)
  #define CMI_IOSF_SB_EP_CTRL_CGCTRL_IDLECNT_HSH                       (0x08106430)

  #define CMI_IOSF_SB_EP_CTRL_RSVD2_OFF                                (24)
  #define CMI_IOSF_SB_EP_CTRL_RSVD2_WID                                ( 8)
  #define CMI_IOSF_SB_EP_CTRL_RSVD2_MSK                                (0xFF000000)
  #define CMI_IOSF_SB_EP_CTRL_RSVD2_MIN                                (0)
  #define CMI_IOSF_SB_EP_CTRL_RSVD2_MAX                                (255) // 0x000000FF
  #define CMI_IOSF_SB_EP_CTRL_RSVD2_DEF                                (0x00000000)
  #define CMI_IOSF_SB_EP_CTRL_RSVD2_HSH                                (0x08186430)

#define CLK_GATE_EN_0_REG                                              (0x00006434)

  #define CLK_GATE_EN_0_CLK_GATE_EN_OFF                                ( 0)
  #define CLK_GATE_EN_0_CLK_GATE_EN_WID                                (32)
  #define CLK_GATE_EN_0_CLK_GATE_EN_MSK                                (0xFFFFFFFF)
  #define CLK_GATE_EN_0_CLK_GATE_EN_MIN                                (0)
  #define CLK_GATE_EN_0_CLK_GATE_EN_MAX                                (4294967295) // 0xFFFFFFFF
  #define CLK_GATE_EN_0_CLK_GATE_EN_DEF                                (0xFFFFFFFF)
  #define CLK_GATE_EN_0_CLK_GATE_EN_HSH                                (0x20006434)

#define CLK_GATE_EN_1_REG                                              (0x00006438)

  #define CLK_GATE_EN_1_CLK_GATE_EN_OFF                                ( 0)
  #define CLK_GATE_EN_1_CLK_GATE_EN_WID                                (32)
  #define CLK_GATE_EN_1_CLK_GATE_EN_MSK                                (0xFFFFFFFF)
  #define CLK_GATE_EN_1_CLK_GATE_EN_MIN                                (0)
  #define CLK_GATE_EN_1_CLK_GATE_EN_MAX                                (4294967295) // 0xFFFFFFFF
  #define CLK_GATE_EN_1_CLK_GATE_EN_DEF                                (0xFFFFFFFF)
  #define CLK_GATE_EN_1_CLK_GATE_EN_HSH                                (0x20006438)

#define CMF_GLOBAL_STATUS_REG                                          (0x0000643C)

  #define CMF_GLOBAL_STATUS_MUX_DEMUX_STS_OFF                          ( 0)
  #define CMF_GLOBAL_STATUS_MUX_DEMUX_STS_WID                          ( 1)
  #define CMF_GLOBAL_STATUS_MUX_DEMUX_STS_MSK                          (0x00000001)
  #define CMF_GLOBAL_STATUS_MUX_DEMUX_STS_MIN                          (0)
  #define CMF_GLOBAL_STATUS_MUX_DEMUX_STS_MAX                          (1) // 0x00000001
  #define CMF_GLOBAL_STATUS_MUX_DEMUX_STS_DEF                          (0x00000001)
  #define CMF_GLOBAL_STATUS_MUX_DEMUX_STS_HSH                          (0x0100643C)

  #define CMF_GLOBAL_STATUS_RESERVED_OFF                               ( 1)
  #define CMF_GLOBAL_STATUS_RESERVED_WID                               (31)
  #define CMF_GLOBAL_STATUS_RESERVED_MSK                               (0xFFFFFFFE)
  #define CMF_GLOBAL_STATUS_RESERVED_MIN                               (0)
  #define CMF_GLOBAL_STATUS_RESERVED_MAX                               (2147483647) // 0x7FFFFFFF
  #define CMF_GLOBAL_STATUS_RESERVED_DEF                               (0x00000000)
  #define CMF_GLOBAL_STATUS_RESERVED_HSH                               (0x1F01643C)

#define CMF_GLOBAL_CFG_1_REG                                           (0x00006440)

  #define CMF_GLOBAL_CFG_1_ISM_IDLE_TIME_OFF                           ( 0)
  #define CMF_GLOBAL_CFG_1_ISM_IDLE_TIME_WID                           ( 8)
  #define CMF_GLOBAL_CFG_1_ISM_IDLE_TIME_MSK                           (0x000000FF)
  #define CMF_GLOBAL_CFG_1_ISM_IDLE_TIME_MIN                           (0)
  #define CMF_GLOBAL_CFG_1_ISM_IDLE_TIME_MAX                           (255) // 0x000000FF
  #define CMF_GLOBAL_CFG_1_ISM_IDLE_TIME_DEF                           (0x00000010)
  #define CMF_GLOBAL_CFG_1_ISM_IDLE_TIME_HSH                           (0x08006440)

  #define CMF_GLOBAL_CFG_1_FIXED_WINDOW_OFF                            ( 8)
  #define CMF_GLOBAL_CFG_1_FIXED_WINDOW_WID                            ( 1)
  #define CMF_GLOBAL_CFG_1_FIXED_WINDOW_MSK                            (0x00000100)
  #define CMF_GLOBAL_CFG_1_FIXED_WINDOW_MIN                            (0)
  #define CMF_GLOBAL_CFG_1_FIXED_WINDOW_MAX                            (1) // 0x00000001
  #define CMF_GLOBAL_CFG_1_FIXED_WINDOW_DEF                            (0x00000000)
  #define CMF_GLOBAL_CFG_1_FIXED_WINDOW_HSH                            (0x01086440)

  #define CMF_GLOBAL_CFG_1_CLK_GATE_EN_OFF                             ( 9)
  #define CMF_GLOBAL_CFG_1_CLK_GATE_EN_WID                             ( 1)
  #define CMF_GLOBAL_CFG_1_CLK_GATE_EN_MSK                             (0x00000200)
  #define CMF_GLOBAL_CFG_1_CLK_GATE_EN_MIN                             (0)
  #define CMF_GLOBAL_CFG_1_CLK_GATE_EN_MAX                             (1) // 0x00000001
  #define CMF_GLOBAL_CFG_1_CLK_GATE_EN_DEF                             (0x00000001)
  #define CMF_GLOBAL_CFG_1_CLK_GATE_EN_HSH                             (0x01096440)

  #define CMF_GLOBAL_CFG_1_FORCE_ISM_ACTIVE_OFF                        (10)
  #define CMF_GLOBAL_CFG_1_FORCE_ISM_ACTIVE_WID                        ( 1)
  #define CMF_GLOBAL_CFG_1_FORCE_ISM_ACTIVE_MSK                        (0x00000400)
  #define CMF_GLOBAL_CFG_1_FORCE_ISM_ACTIVE_MIN                        (0)
  #define CMF_GLOBAL_CFG_1_FORCE_ISM_ACTIVE_MAX                        (1) // 0x00000001
  #define CMF_GLOBAL_CFG_1_FORCE_ISM_ACTIVE_DEF                        (0x00000000)
  #define CMF_GLOBAL_CFG_1_FORCE_ISM_ACTIVE_HSH                        (0x010A6440)

  #define CMF_GLOBAL_CFG_1_BYPASS_EN_OFF                               (11)
  #define CMF_GLOBAL_CFG_1_BYPASS_EN_WID                               ( 1)
  #define CMF_GLOBAL_CFG_1_BYPASS_EN_MSK                               (0x00000800)
  #define CMF_GLOBAL_CFG_1_BYPASS_EN_MIN                               (0)
  #define CMF_GLOBAL_CFG_1_BYPASS_EN_MAX                               (1) // 0x00000001
  #define CMF_GLOBAL_CFG_1_BYPASS_EN_DEF                               (0x00000001)
  #define CMF_GLOBAL_CFG_1_BYPASS_EN_HSH                               (0x010B6440)

  #define CMF_GLOBAL_CFG_1_AGENT_WR_RSP_OFF                            (12)
  #define CMF_GLOBAL_CFG_1_AGENT_WR_RSP_WID                            ( 5)
  #define CMF_GLOBAL_CFG_1_AGENT_WR_RSP_MSK                            (0x0001F000)
  #define CMF_GLOBAL_CFG_1_AGENT_WR_RSP_MIN                            (0)
  #define CMF_GLOBAL_CFG_1_AGENT_WR_RSP_MAX                            (31) // 0x0000001F
  #define CMF_GLOBAL_CFG_1_AGENT_WR_RSP_DEF                            (0x00000000)
  #define CMF_GLOBAL_CFG_1_AGENT_WR_RSP_HSH                            (0x050C6440)

  #define CMF_GLOBAL_CFG_1_REQ_FAST_WAKE_OFF                           (17)
  #define CMF_GLOBAL_CFG_1_REQ_FAST_WAKE_WID                           ( 5)
  #define CMF_GLOBAL_CFG_1_REQ_FAST_WAKE_MSK                           (0x003E0000)
  #define CMF_GLOBAL_CFG_1_REQ_FAST_WAKE_MIN                           (0)
  #define CMF_GLOBAL_CFG_1_REQ_FAST_WAKE_MAX                           (31) // 0x0000001F
  #define CMF_GLOBAL_CFG_1_REQ_FAST_WAKE_DEF                           (0x00000004)
  #define CMF_GLOBAL_CFG_1_REQ_FAST_WAKE_HSH                           (0x05116440)

  #define CMF_GLOBAL_CFG_1_FAST_WAKE_EN_OFF                            (22)
  #define CMF_GLOBAL_CFG_1_FAST_WAKE_EN_WID                            ( 1)
  #define CMF_GLOBAL_CFG_1_FAST_WAKE_EN_MSK                            (0x00400000)
  #define CMF_GLOBAL_CFG_1_FAST_WAKE_EN_MIN                            (0)
  #define CMF_GLOBAL_CFG_1_FAST_WAKE_EN_MAX                            (1) // 0x00000001
  #define CMF_GLOBAL_CFG_1_FAST_WAKE_EN_DEF                            (0x00000001)
  #define CMF_GLOBAL_CFG_1_FAST_WAKE_EN_HSH                            (0x01166440)

  #define CMF_GLOBAL_CFG_1_RESERVED_OFF                                (23)
  #define CMF_GLOBAL_CFG_1_RESERVED_WID                                ( 9)
  #define CMF_GLOBAL_CFG_1_RESERVED_MSK                                (0xFF800000)
  #define CMF_GLOBAL_CFG_1_RESERVED_MIN                                (0)
  #define CMF_GLOBAL_CFG_1_RESERVED_MAX                                (511) // 0x000001FF
  #define CMF_GLOBAL_CFG_1_RESERVED_DEF                                (0x00000000)
  #define CMF_GLOBAL_CFG_1_RESERVED_HSH                                (0x09176440)

#define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REG                      (0x00006450)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_OFF   ( 0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_MSK   (0x0000000F)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_HSH   (0x04006450)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_OFF       ( 4)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_WID       ( 3)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_MSK       (0x00000070)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_MIN       (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_MAX       (7) // 0x00000007
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_DEF       (0x00000000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_HSH       (0x03046450)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_OFF ( 7)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_WID ( 1)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_MSK (0x00000080)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_MIN (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_MAX (1) // 0x00000001
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_DEF (0x00000000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_HSH (0x01076450)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_OFF   ( 8)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_MSK   (0x00000F00)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_HSH   (0x04086450)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_RESERVED1_OFF          (12)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_RESERVED1_WID          ( 4)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_RESERVED1_MSK          (0x0000F000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_RESERVED1_MIN          (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_RESERVED1_MAX          (15) // 0x0000000F
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_RESERVED1_DEF          (0x00000000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_RESERVED1_HSH          (0x040C6450)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_OFF  (16)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_MSK  (0x00FF0000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_DEF  (0x00000002)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_HSH  (0x08106450)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_OFF  (24)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_MSK  (0xFF000000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_DEF  (0x00000003)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_HSH  (0x08186450)

#define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REG                      (0x00006454)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_OFF   ( 0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_MSK   (0x0000000F)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_HSH   (0x04006454)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_OFF       ( 4)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_WID       ( 3)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_MSK       (0x00000070)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_MIN       (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_MAX       (7) // 0x00000007
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_DEF       (0x00000000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_HSH       (0x03046454)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_OFF ( 7)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_WID ( 1)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_MSK (0x00000080)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_MIN (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_MAX (1) // 0x00000001
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_DEF (0x00000000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_HSH (0x01076454)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_OFF   ( 8)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_MSK   (0x00000F00)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_HSH   (0x04086454)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_RESERVED1_OFF          (12)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_RESERVED1_WID          ( 4)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_RESERVED1_MSK          (0x0000F000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_RESERVED1_MIN          (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_RESERVED1_MAX          (15) // 0x0000000F
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_RESERVED1_DEF          (0x00000000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_RESERVED1_HSH          (0x040C6454)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_OFF  (16)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_MSK  (0x00FF0000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_DEF  (0x00000002)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_HSH  (0x08106454)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_OFF  (24)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_MSK  (0xFF000000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_DEF  (0x00000003)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_HSH  (0x08186454)

#define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REG                      (0x00006458)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_OFF   ( 0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_MSK   (0x0000000F)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_HSH   (0x04006458)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_OFF       ( 4)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_WID       ( 3)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_MSK       (0x00000070)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_MIN       (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_MAX       (7) // 0x00000007
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_DEF       (0x00000000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_HSH       (0x03046458)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_OFF ( 7)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_WID ( 1)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_MSK (0x00000080)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_MIN (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_MAX (1) // 0x00000001
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_DEF (0x00000000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_HSH (0x01076458)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_OFF   ( 8)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_MSK   (0x00000F00)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_HSH   (0x04086458)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_RESERVED1_OFF          (12)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_RESERVED1_WID          ( 4)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_RESERVED1_MSK          (0x0000F000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_RESERVED1_MIN          (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_RESERVED1_MAX          (15) // 0x0000000F
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_RESERVED1_DEF          (0x00000000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_RESERVED1_HSH          (0x040C6458)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_OFF  (16)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_MSK  (0x00FF0000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_DEF  (0x00000000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_HSH  (0x08106458)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_OFF  (24)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_MSK  (0xFF000000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_DEF  (0x00000000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_HSH  (0x08186458)

#define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REG                      (0x0000645C)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_OFF   ( 0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_MSK   (0x0000000F)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_HSH   (0x0400645C)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_OFF       ( 4)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_WID       ( 3)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_MSK       (0x00000070)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_MIN       (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_MAX       (7) // 0x00000007
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_DEF       (0x00000000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_HSH       (0x0304645C)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_OFF ( 7)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_WID ( 1)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_MSK (0x00000080)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_MIN (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_MAX (1) // 0x00000001
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_DEF (0x00000000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_HSH (0x0107645C)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_OFF   ( 8)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_MSK   (0x00000F00)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_HSH   (0x0408645C)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_RESERVED1_OFF          (12)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_RESERVED1_WID          ( 4)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_RESERVED1_MSK          (0x0000F000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_RESERVED1_MIN          (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_RESERVED1_MAX          (15) // 0x0000000F
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_RESERVED1_DEF          (0x00000000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_RESERVED1_HSH          (0x040C645C)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_OFF  (16)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_MSK  (0x00FF0000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_DEF  (0x00000000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_HSH  (0x0810645C)

  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_OFF  (24)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_MSK  (0xFF000000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_DEF  (0x00000000)
  #define REQUEST_PORT_0_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_HSH  (0x0818645C)

#define REQUEST_PORT_0_REQ_CONFIG_1_REG                                (0x00006460)

  #define REQUEST_PORT_0_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_OFF            ( 0)
  #define REQUEST_PORT_0_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_WID            ( 8)
  #define REQUEST_PORT_0_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_MSK            (0x000000FF)
  #define REQUEST_PORT_0_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_MIN            (0)
  #define REQUEST_PORT_0_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_MAX            (255) // 0x000000FF
  #define REQUEST_PORT_0_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_DEF            (0x00000004)
  #define REQUEST_PORT_0_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_HSH            (0x08006460)

  #define REQUEST_PORT_0_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_OFF            ( 8)
  #define REQUEST_PORT_0_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_WID            ( 8)
  #define REQUEST_PORT_0_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_MSK            (0x0000FF00)
  #define REQUEST_PORT_0_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_MIN            (0)
  #define REQUEST_PORT_0_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_MAX            (255) // 0x000000FF
  #define REQUEST_PORT_0_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_DEF            (0x00000006)
  #define REQUEST_PORT_0_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_HSH            (0x08086460)

  #define REQUEST_PORT_0_REQ_CONFIG_1_RESERVED1_OFF                    (16)
  #define REQUEST_PORT_0_REQ_CONFIG_1_RESERVED1_WID                    (16)
  #define REQUEST_PORT_0_REQ_CONFIG_1_RESERVED1_MSK                    (0xFFFF0000)
  #define REQUEST_PORT_0_REQ_CONFIG_1_RESERVED1_MIN                    (0)
  #define REQUEST_PORT_0_REQ_CONFIG_1_RESERVED1_MAX                    (65535) // 0x0000FFFF
  #define REQUEST_PORT_0_REQ_CONFIG_1_RESERVED1_DEF                    (0x00000000)
  #define REQUEST_PORT_0_REQ_CONFIG_1_RESERVED1_HSH                    (0x10106460)

#define REQUEST_PORT_0_STALL_REG                                       (0x00006464)

  #define REQUEST_PORT_0_STALL_REQ_STALL_OFF                           ( 0)
  #define REQUEST_PORT_0_STALL_REQ_STALL_WID                           ( 1)
  #define REQUEST_PORT_0_STALL_REQ_STALL_MSK                           (0x00000001)
  #define REQUEST_PORT_0_STALL_REQ_STALL_MIN                           (0)
  #define REQUEST_PORT_0_STALL_REQ_STALL_MAX                           (1) // 0x00000001
  #define REQUEST_PORT_0_STALL_REQ_STALL_DEF                           (0x00000000)
  #define REQUEST_PORT_0_STALL_REQ_STALL_HSH                           (0x01006464)

  #define REQUEST_PORT_0_STALL_RSVD0_OFF                               ( 1)
  #define REQUEST_PORT_0_STALL_RSVD0_WID                               ( 4)
  #define REQUEST_PORT_0_STALL_RSVD0_MSK                               (0x0000001E)
  #define REQUEST_PORT_0_STALL_RSVD0_MIN                               (0)
  #define REQUEST_PORT_0_STALL_RSVD0_MAX                               (15) // 0x0000000F
  #define REQUEST_PORT_0_STALL_RSVD0_DEF                               (0x00000000)
  #define REQUEST_PORT_0_STALL_RSVD0_HSH                               (0x04016464)

  #define REQUEST_PORT_0_STALL_RSVD1_OFF                               ( 5)
  #define REQUEST_PORT_0_STALL_RSVD1_WID                               ( 3)
  #define REQUEST_PORT_0_STALL_RSVD1_MSK                               (0x000000E0)
  #define REQUEST_PORT_0_STALL_RSVD1_MIN                               (0)
  #define REQUEST_PORT_0_STALL_RSVD1_MAX                               (7) // 0x00000007
  #define REQUEST_PORT_0_STALL_RSVD1_DEF                               (0x00000000)
  #define REQUEST_PORT_0_STALL_RSVD1_HSH                               (0x03056464)

  #define REQUEST_PORT_0_STALL_UNSTALL_COUNTER_VALUE_OFF               ( 8)
  #define REQUEST_PORT_0_STALL_UNSTALL_COUNTER_VALUE_WID               (16)
  #define REQUEST_PORT_0_STALL_UNSTALL_COUNTER_VALUE_MSK               (0x00FFFF00)
  #define REQUEST_PORT_0_STALL_UNSTALL_COUNTER_VALUE_MIN               (0)
  #define REQUEST_PORT_0_STALL_UNSTALL_COUNTER_VALUE_MAX               (65535) // 0x0000FFFF
  #define REQUEST_PORT_0_STALL_UNSTALL_COUNTER_VALUE_DEF               (0x00000000)
  #define REQUEST_PORT_0_STALL_UNSTALL_COUNTER_VALUE_HSH               (0x10086464)

#define REQUEST_PORT_0_RESERVED_0_REG                                  (0x00006468)

  #define REQUEST_PORT_0_RESERVED_0_RESERVED_OFF                       ( 0)
  #define REQUEST_PORT_0_RESERVED_0_RESERVED_WID                       (32)
  #define REQUEST_PORT_0_RESERVED_0_RESERVED_MSK                       (0xFFFFFFFF)
  #define REQUEST_PORT_0_RESERVED_0_RESERVED_MIN                       (0)
  #define REQUEST_PORT_0_RESERVED_0_RESERVED_MAX                       (4294967295) // 0xFFFFFFFF
  #define REQUEST_PORT_0_RESERVED_0_RESERVED_DEF                       (0x00000000)
  #define REQUEST_PORT_0_RESERVED_0_RESERVED_HSH                       (0x20006468)

#define REQUEST_PORT_0_RESERVED_1_REG                                  (0x0000646C)

  #define REQUEST_PORT_0_RESERVED_1_RESERVED_OFF                       ( 0)
  #define REQUEST_PORT_0_RESERVED_1_RESERVED_WID                       (32)
  #define REQUEST_PORT_0_RESERVED_1_RESERVED_MSK                       (0xFFFFFFFF)
  #define REQUEST_PORT_0_RESERVED_1_RESERVED_MIN                       (0)
  #define REQUEST_PORT_0_RESERVED_1_RESERVED_MAX                       (4294967295) // 0xFFFFFFFF
  #define REQUEST_PORT_0_RESERVED_1_RESERVED_DEF                       (0x00000000)
  #define REQUEST_PORT_0_RESERVED_1_RESERVED_HSH                       (0x2000646C)

#define REQUEST_PORT_0_RESERVED_2_REG                                  (0x00006470)

  #define REQUEST_PORT_0_RESERVED_2_RESERVED_OFF                       ( 0)
  #define REQUEST_PORT_0_RESERVED_2_RESERVED_WID                       (32)
  #define REQUEST_PORT_0_RESERVED_2_RESERVED_MSK                       (0xFFFFFFFF)
  #define REQUEST_PORT_0_RESERVED_2_RESERVED_MIN                       (0)
  #define REQUEST_PORT_0_RESERVED_2_RESERVED_MAX                       (4294967295) // 0xFFFFFFFF
  #define REQUEST_PORT_0_RESERVED_2_RESERVED_DEF                       (0x00000000)
  #define REQUEST_PORT_0_RESERVED_2_RESERVED_HSH                       (0x20006470)

#define REQUEST_PORT_0_ACCUM_REQ_IN_REG                                (0x00006474)

  #define REQUEST_PORT_0_ACCUM_REQ_IN_REQ_CMD_SUM_OFF                  ( 0)
  #define REQUEST_PORT_0_ACCUM_REQ_IN_REQ_CMD_SUM_WID                  (16)
  #define REQUEST_PORT_0_ACCUM_REQ_IN_REQ_CMD_SUM_MSK                  (0x0000FFFF)
  #define REQUEST_PORT_0_ACCUM_REQ_IN_REQ_CMD_SUM_MIN                  (0)
  #define REQUEST_PORT_0_ACCUM_REQ_IN_REQ_CMD_SUM_MAX                  (65535) // 0x0000FFFF
  #define REQUEST_PORT_0_ACCUM_REQ_IN_REQ_CMD_SUM_DEF                  (0x00000000)
  #define REQUEST_PORT_0_ACCUM_REQ_IN_REQ_CMD_SUM_HSH                  (0x10006474)

  #define REQUEST_PORT_0_ACCUM_REQ_IN_REQ_DATA_SUM_OFF                 (16)
  #define REQUEST_PORT_0_ACCUM_REQ_IN_REQ_DATA_SUM_WID                 (16)
  #define REQUEST_PORT_0_ACCUM_REQ_IN_REQ_DATA_SUM_MSK                 (0xFFFF0000)
  #define REQUEST_PORT_0_ACCUM_REQ_IN_REQ_DATA_SUM_MIN                 (0)
  #define REQUEST_PORT_0_ACCUM_REQ_IN_REQ_DATA_SUM_MAX                 (65535) // 0x0000FFFF
  #define REQUEST_PORT_0_ACCUM_REQ_IN_REQ_DATA_SUM_DEF                 (0x00000000)
  #define REQUEST_PORT_0_ACCUM_REQ_IN_REQ_DATA_SUM_HSH                 (0x10106474)

#define REQUEST_PORT_0_ACCUM_RD_CPL_OUT_REG                            (0x00006478)

  #define REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_OFF           ( 0)
  #define REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_WID           (16)
  #define REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_MSK           (0x0000FFFF)
  #define REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_MIN           (0)
  #define REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_MAX           (65535) // 0x0000FFFF
  #define REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_DEF           (0x00000000)
  #define REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_HSH           (0x10006478)

  #define REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_OFF          (16)
  #define REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_WID          (16)
  #define REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_MSK          (0xFFFF0000)
  #define REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_MIN          (0)
  #define REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_MAX          (65535) // 0x0000FFFF
  #define REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_DEF          (0x00000000)
  #define REQUEST_PORT_0_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_HSH          (0x10106478)

#define REQUEST_PORT_0_ACCUM_RSP_OUT_REG                               (0x0000647C)

  #define REQUEST_PORT_0_ACCUM_RSP_OUT_RSP_CMD_SUM_OFF                 ( 0)
  #define REQUEST_PORT_0_ACCUM_RSP_OUT_RSP_CMD_SUM_WID                 (16)
  #define REQUEST_PORT_0_ACCUM_RSP_OUT_RSP_CMD_SUM_MSK                 (0x0000FFFF)
  #define REQUEST_PORT_0_ACCUM_RSP_OUT_RSP_CMD_SUM_MIN                 (0)
  #define REQUEST_PORT_0_ACCUM_RSP_OUT_RSP_CMD_SUM_MAX                 (65535) // 0x0000FFFF
  #define REQUEST_PORT_0_ACCUM_RSP_OUT_RSP_CMD_SUM_DEF                 (0x00000000)
  #define REQUEST_PORT_0_ACCUM_RSP_OUT_RSP_CMD_SUM_HSH                 (0x1000647C)

  #define REQUEST_PORT_0_ACCUM_RSP_OUT_RSVD_OFF                        (16)
  #define REQUEST_PORT_0_ACCUM_RSP_OUT_RSVD_WID                        (16)
  #define REQUEST_PORT_0_ACCUM_RSP_OUT_RSVD_MSK                        (0xFFFF0000)
  #define REQUEST_PORT_0_ACCUM_RSP_OUT_RSVD_MIN                        (0)
  #define REQUEST_PORT_0_ACCUM_RSP_OUT_RSVD_MAX                        (65535) // 0x0000FFFF
  #define REQUEST_PORT_0_ACCUM_RSP_OUT_RSVD_DEF                        (0x00000000)
  #define REQUEST_PORT_0_ACCUM_RSP_OUT_RSVD_HSH                        (0x1010647C)

#define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REG                      (0x00006480)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_OFF   ( 0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_MSK   (0x0000000F)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_HSH   (0x04006480)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_OFF       ( 4)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_WID       ( 3)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_MSK       (0x00000070)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_MIN       (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_MAX       (7) // 0x00000007
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_DEF       (0x00000000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_HSH       (0x03046480)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_OFF ( 7)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_WID ( 1)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_MSK (0x00000080)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_MIN (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_MAX (1) // 0x00000001
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_DEF (0x00000000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_HSH (0x01076480)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_OFF   ( 8)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_MSK   (0x00000F00)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_HSH   (0x04086480)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_RESERVED1_OFF          (12)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_RESERVED1_WID          ( 4)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_RESERVED1_MSK          (0x0000F000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_RESERVED1_MIN          (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_RESERVED1_MAX          (15) // 0x0000000F
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_RESERVED1_DEF          (0x00000000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_RESERVED1_HSH          (0x040C6480)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_OFF  (16)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_MSK  (0x00FF0000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_DEF  (0x00000002)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_HSH  (0x08106480)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_OFF  (24)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_MSK  (0xFF000000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_DEF  (0x00000003)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_HSH  (0x08186480)

#define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REG                      (0x00006484)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_OFF   ( 0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_MSK   (0x0000000F)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_HSH   (0x04006484)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_OFF       ( 4)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_WID       ( 3)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_MSK       (0x00000070)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_MIN       (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_MAX       (7) // 0x00000007
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_DEF       (0x00000000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_HSH       (0x03046484)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_OFF ( 7)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_WID ( 1)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_MSK (0x00000080)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_MIN (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_MAX (1) // 0x00000001
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_DEF (0x00000000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_HSH (0x01076484)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_OFF   ( 8)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_MSK   (0x00000F00)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_HSH   (0x04086484)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_RESERVED1_OFF          (12)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_RESERVED1_WID          ( 4)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_RESERVED1_MSK          (0x0000F000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_RESERVED1_MIN          (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_RESERVED1_MAX          (15) // 0x0000000F
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_RESERVED1_DEF          (0x00000000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_RESERVED1_HSH          (0x040C6484)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_OFF  (16)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_MSK  (0x00FF0000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_DEF  (0x00000000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_HSH  (0x08106484)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_OFF  (24)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_MSK  (0xFF000000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_DEF  (0x00000000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_HSH  (0x08186484)

#define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REG                      (0x00006488)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_OFF   ( 0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_MSK   (0x0000000F)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_HSH   (0x04006488)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_OFF       ( 4)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_WID       ( 3)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_MSK       (0x00000070)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_MIN       (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_MAX       (7) // 0x00000007
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_DEF       (0x00000000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_HSH       (0x03046488)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_OFF ( 7)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_WID ( 1)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_MSK (0x00000080)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_MIN (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_MAX (1) // 0x00000001
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_DEF (0x00000000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_HSH (0x01076488)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_OFF   ( 8)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_MSK   (0x00000F00)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_HSH   (0x04086488)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_RESERVED1_OFF          (12)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_RESERVED1_WID          ( 4)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_RESERVED1_MSK          (0x0000F000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_RESERVED1_MIN          (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_RESERVED1_MAX          (15) // 0x0000000F
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_RESERVED1_DEF          (0x00000000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_RESERVED1_HSH          (0x040C6488)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_OFF  (16)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_MSK  (0x00FF0000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_DEF  (0x00000000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_HSH  (0x08106488)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_OFF  (24)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_MSK  (0xFF000000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_DEF  (0x00000000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_HSH  (0x08186488)

#define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REG                      (0x0000648C)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_OFF   ( 0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_MSK   (0x0000000F)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_HSH   (0x0400648C)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_OFF       ( 4)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_WID       ( 3)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_MSK       (0x00000070)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_MIN       (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_MAX       (7) // 0x00000007
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_DEF       (0x00000000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_HSH       (0x0304648C)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_OFF ( 7)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_WID ( 1)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_MSK (0x00000080)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_MIN (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_MAX (1) // 0x00000001
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_DEF (0x00000000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_HSH (0x0107648C)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_OFF   ( 8)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_MSK   (0x00000F00)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_HSH   (0x0408648C)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_RESERVED1_OFF          (12)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_RESERVED1_WID          ( 4)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_RESERVED1_MSK          (0x0000F000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_RESERVED1_MIN          (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_RESERVED1_MAX          (15) // 0x0000000F
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_RESERVED1_DEF          (0x00000000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_RESERVED1_HSH          (0x040C648C)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_OFF  (16)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_MSK  (0x00FF0000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_DEF  (0x00000002)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_HSH  (0x0810648C)

  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_OFF  (24)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_MSK  (0xFF000000)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_DEF  (0x00000003)
  #define REQUEST_PORT_1_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_HSH  (0x0818648C)

#define REQUEST_PORT_1_REQ_CONFIG_1_REG                                (0x00006490)

  #define REQUEST_PORT_1_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_OFF            ( 0)
  #define REQUEST_PORT_1_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_WID            ( 8)
  #define REQUEST_PORT_1_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_MSK            (0x000000FF)
  #define REQUEST_PORT_1_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_MIN            (0)
  #define REQUEST_PORT_1_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_MAX            (255) // 0x000000FF
  #define REQUEST_PORT_1_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_DEF            (0x00000004)
  #define REQUEST_PORT_1_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_HSH            (0x08006490)

  #define REQUEST_PORT_1_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_OFF            ( 8)
  #define REQUEST_PORT_1_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_WID            ( 8)
  #define REQUEST_PORT_1_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_MSK            (0x0000FF00)
  #define REQUEST_PORT_1_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_MIN            (0)
  #define REQUEST_PORT_1_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_MAX            (255) // 0x000000FF
  #define REQUEST_PORT_1_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_DEF            (0x00000006)
  #define REQUEST_PORT_1_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_HSH            (0x08086490)

  #define REQUEST_PORT_1_REQ_CONFIG_1_RESERVED1_OFF                    (16)
  #define REQUEST_PORT_1_REQ_CONFIG_1_RESERVED1_WID                    (16)
  #define REQUEST_PORT_1_REQ_CONFIG_1_RESERVED1_MSK                    (0xFFFF0000)
  #define REQUEST_PORT_1_REQ_CONFIG_1_RESERVED1_MIN                    (0)
  #define REQUEST_PORT_1_REQ_CONFIG_1_RESERVED1_MAX                    (65535) // 0x0000FFFF
  #define REQUEST_PORT_1_REQ_CONFIG_1_RESERVED1_DEF                    (0x00000000)
  #define REQUEST_PORT_1_REQ_CONFIG_1_RESERVED1_HSH                    (0x10106490)

#define REQUEST_PORT_1_STALL_REG                                       (0x00006494)

  #define REQUEST_PORT_1_STALL_REQ_STALL_OFF                           ( 0)
  #define REQUEST_PORT_1_STALL_REQ_STALL_WID                           ( 1)
  #define REQUEST_PORT_1_STALL_REQ_STALL_MSK                           (0x00000001)
  #define REQUEST_PORT_1_STALL_REQ_STALL_MIN                           (0)
  #define REQUEST_PORT_1_STALL_REQ_STALL_MAX                           (1) // 0x00000001
  #define REQUEST_PORT_1_STALL_REQ_STALL_DEF                           (0x00000000)
  #define REQUEST_PORT_1_STALL_REQ_STALL_HSH                           (0x01006494)

  #define REQUEST_PORT_1_STALL_RSVD0_OFF                               ( 1)
  #define REQUEST_PORT_1_STALL_RSVD0_WID                               ( 4)
  #define REQUEST_PORT_1_STALL_RSVD0_MSK                               (0x0000001E)
  #define REQUEST_PORT_1_STALL_RSVD0_MIN                               (0)
  #define REQUEST_PORT_1_STALL_RSVD0_MAX                               (15) // 0x0000000F
  #define REQUEST_PORT_1_STALL_RSVD0_DEF                               (0x00000000)
  #define REQUEST_PORT_1_STALL_RSVD0_HSH                               (0x04016494)

  #define REQUEST_PORT_1_STALL_RSVD1_OFF                               ( 5)
  #define REQUEST_PORT_1_STALL_RSVD1_WID                               ( 3)
  #define REQUEST_PORT_1_STALL_RSVD1_MSK                               (0x000000E0)
  #define REQUEST_PORT_1_STALL_RSVD1_MIN                               (0)
  #define REQUEST_PORT_1_STALL_RSVD1_MAX                               (7) // 0x00000007
  #define REQUEST_PORT_1_STALL_RSVD1_DEF                               (0x00000000)
  #define REQUEST_PORT_1_STALL_RSVD1_HSH                               (0x03056494)

  #define REQUEST_PORT_1_STALL_UNSTALL_COUNTER_VALUE_OFF               ( 8)
  #define REQUEST_PORT_1_STALL_UNSTALL_COUNTER_VALUE_WID               (16)
  #define REQUEST_PORT_1_STALL_UNSTALL_COUNTER_VALUE_MSK               (0x00FFFF00)
  #define REQUEST_PORT_1_STALL_UNSTALL_COUNTER_VALUE_MIN               (0)
  #define REQUEST_PORT_1_STALL_UNSTALL_COUNTER_VALUE_MAX               (65535) // 0x0000FFFF
  #define REQUEST_PORT_1_STALL_UNSTALL_COUNTER_VALUE_DEF               (0x00000000)
  #define REQUEST_PORT_1_STALL_UNSTALL_COUNTER_VALUE_HSH               (0x10086494)

#define REQUEST_PORT_1_RESERVED_0_REG                                  (0x00006498)

  #define REQUEST_PORT_1_RESERVED_0_RESERVED_OFF                       ( 0)
  #define REQUEST_PORT_1_RESERVED_0_RESERVED_WID                       (32)
  #define REQUEST_PORT_1_RESERVED_0_RESERVED_MSK                       (0xFFFFFFFF)
  #define REQUEST_PORT_1_RESERVED_0_RESERVED_MIN                       (0)
  #define REQUEST_PORT_1_RESERVED_0_RESERVED_MAX                       (4294967295) // 0xFFFFFFFF
  #define REQUEST_PORT_1_RESERVED_0_RESERVED_DEF                       (0x00000000)
  #define REQUEST_PORT_1_RESERVED_0_RESERVED_HSH                       (0x20006498)

#define REQUEST_PORT_1_RESERVED_1_REG                                  (0x0000649C)

  #define REQUEST_PORT_1_RESERVED_1_RESERVED_OFF                       ( 0)
  #define REQUEST_PORT_1_RESERVED_1_RESERVED_WID                       (32)
  #define REQUEST_PORT_1_RESERVED_1_RESERVED_MSK                       (0xFFFFFFFF)
  #define REQUEST_PORT_1_RESERVED_1_RESERVED_MIN                       (0)
  #define REQUEST_PORT_1_RESERVED_1_RESERVED_MAX                       (4294967295) // 0xFFFFFFFF
  #define REQUEST_PORT_1_RESERVED_1_RESERVED_DEF                       (0x00000000)
  #define REQUEST_PORT_1_RESERVED_1_RESERVED_HSH                       (0x2000649C)

#define REQUEST_PORT_1_RESERVED_2_REG                                  (0x000064A0)

  #define REQUEST_PORT_1_RESERVED_2_RESERVED_OFF                       ( 0)
  #define REQUEST_PORT_1_RESERVED_2_RESERVED_WID                       (32)
  #define REQUEST_PORT_1_RESERVED_2_RESERVED_MSK                       (0xFFFFFFFF)
  #define REQUEST_PORT_1_RESERVED_2_RESERVED_MIN                       (0)
  #define REQUEST_PORT_1_RESERVED_2_RESERVED_MAX                       (4294967295) // 0xFFFFFFFF
  #define REQUEST_PORT_1_RESERVED_2_RESERVED_DEF                       (0x00000000)
  #define REQUEST_PORT_1_RESERVED_2_RESERVED_HSH                       (0x200064A0)

#define REQUEST_PORT_1_ACCUM_REQ_IN_REG                                (0x000064A4)

  #define REQUEST_PORT_1_ACCUM_REQ_IN_REQ_CMD_SUM_OFF                  ( 0)
  #define REQUEST_PORT_1_ACCUM_REQ_IN_REQ_CMD_SUM_WID                  (16)
  #define REQUEST_PORT_1_ACCUM_REQ_IN_REQ_CMD_SUM_MSK                  (0x0000FFFF)
  #define REQUEST_PORT_1_ACCUM_REQ_IN_REQ_CMD_SUM_MIN                  (0)
  #define REQUEST_PORT_1_ACCUM_REQ_IN_REQ_CMD_SUM_MAX                  (65535) // 0x0000FFFF
  #define REQUEST_PORT_1_ACCUM_REQ_IN_REQ_CMD_SUM_DEF                  (0x00000000)
  #define REQUEST_PORT_1_ACCUM_REQ_IN_REQ_CMD_SUM_HSH                  (0x100064A4)

  #define REQUEST_PORT_1_ACCUM_REQ_IN_REQ_DATA_SUM_OFF                 (16)
  #define REQUEST_PORT_1_ACCUM_REQ_IN_REQ_DATA_SUM_WID                 (16)
  #define REQUEST_PORT_1_ACCUM_REQ_IN_REQ_DATA_SUM_MSK                 (0xFFFF0000)
  #define REQUEST_PORT_1_ACCUM_REQ_IN_REQ_DATA_SUM_MIN                 (0)
  #define REQUEST_PORT_1_ACCUM_REQ_IN_REQ_DATA_SUM_MAX                 (65535) // 0x0000FFFF
  #define REQUEST_PORT_1_ACCUM_REQ_IN_REQ_DATA_SUM_DEF                 (0x00000000)
  #define REQUEST_PORT_1_ACCUM_REQ_IN_REQ_DATA_SUM_HSH                 (0x101064A4)

#define REQUEST_PORT_1_ACCUM_RD_CPL_OUT_REG                            (0x000064A8)

  #define REQUEST_PORT_1_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_OFF           ( 0)
  #define REQUEST_PORT_1_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_WID           (16)
  #define REQUEST_PORT_1_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_MSK           (0x0000FFFF)
  #define REQUEST_PORT_1_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_MIN           (0)
  #define REQUEST_PORT_1_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_MAX           (65535) // 0x0000FFFF
  #define REQUEST_PORT_1_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_DEF           (0x00000000)
  #define REQUEST_PORT_1_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_HSH           (0x100064A8)

  #define REQUEST_PORT_1_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_OFF          (16)
  #define REQUEST_PORT_1_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_WID          (16)
  #define REQUEST_PORT_1_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_MSK          (0xFFFF0000)
  #define REQUEST_PORT_1_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_MIN          (0)
  #define REQUEST_PORT_1_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_MAX          (65535) // 0x0000FFFF
  #define REQUEST_PORT_1_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_DEF          (0x00000000)
  #define REQUEST_PORT_1_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_HSH          (0x101064A8)

#define REQUEST_PORT_1_ACCUM_RSP_OUT_REG                               (0x000064AC)

  #define REQUEST_PORT_1_ACCUM_RSP_OUT_RSP_CMD_SUM_OFF                 ( 0)
  #define REQUEST_PORT_1_ACCUM_RSP_OUT_RSP_CMD_SUM_WID                 (16)
  #define REQUEST_PORT_1_ACCUM_RSP_OUT_RSP_CMD_SUM_MSK                 (0x0000FFFF)
  #define REQUEST_PORT_1_ACCUM_RSP_OUT_RSP_CMD_SUM_MIN                 (0)
  #define REQUEST_PORT_1_ACCUM_RSP_OUT_RSP_CMD_SUM_MAX                 (65535) // 0x0000FFFF
  #define REQUEST_PORT_1_ACCUM_RSP_OUT_RSP_CMD_SUM_DEF                 (0x00000000)
  #define REQUEST_PORT_1_ACCUM_RSP_OUT_RSP_CMD_SUM_HSH                 (0x100064AC)

  #define REQUEST_PORT_1_ACCUM_RSP_OUT_RSVD_OFF                        (16)
  #define REQUEST_PORT_1_ACCUM_RSP_OUT_RSVD_WID                        (16)
  #define REQUEST_PORT_1_ACCUM_RSP_OUT_RSVD_MSK                        (0xFFFF0000)
  #define REQUEST_PORT_1_ACCUM_RSP_OUT_RSVD_MIN                        (0)
  #define REQUEST_PORT_1_ACCUM_RSP_OUT_RSVD_MAX                        (65535) // 0x0000FFFF
  #define REQUEST_PORT_1_ACCUM_RSP_OUT_RSVD_DEF                        (0x00000000)
  #define REQUEST_PORT_1_ACCUM_RSP_OUT_RSVD_HSH                        (0x101064AC)

#define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REG                      (0x000064B0)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_OFF   ( 0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_MSK   (0x0000000F)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_HSH   (0x040064B0)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_OFF       ( 4)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_WID       ( 3)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_MSK       (0x00000070)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_MIN       (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_MAX       (7) // 0x00000007
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_DEF       (0x00000000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_HSH       (0x030464B0)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_OFF ( 7)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_WID ( 1)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_MSK (0x00000080)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_MIN (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_MAX (1) // 0x00000001
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_DEF (0x00000000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_HSH (0x010764B0)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_OFF   ( 8)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_MSK   (0x00000F00)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_HSH   (0x040864B0)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_RESERVED1_OFF          (12)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_RESERVED1_WID          ( 4)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_RESERVED1_MSK          (0x0000F000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_RESERVED1_MIN          (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_RESERVED1_MAX          (15) // 0x0000000F
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_RESERVED1_DEF          (0x00000000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_RESERVED1_HSH          (0x040C64B0)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_OFF  (16)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_MSK  (0x00FF0000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_DEF  (0x00000002)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_HSH  (0x081064B0)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_OFF  (24)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_MSK  (0xFF000000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_DEF  (0x00000003)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_HSH  (0x081864B0)

#define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REG                      (0x000064B4)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_OFF   ( 0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_MSK   (0x0000000F)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_HSH   (0x040064B4)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_OFF       ( 4)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_WID       ( 3)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_MSK       (0x00000070)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_MIN       (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_MAX       (7) // 0x00000007
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_DEF       (0x00000000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_HSH       (0x030464B4)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_OFF ( 7)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_WID ( 1)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_MSK (0x00000080)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_MIN (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_MAX (1) // 0x00000001
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_DEF (0x00000000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_HSH (0x010764B4)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_OFF   ( 8)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_MSK   (0x00000F00)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_HSH   (0x040864B4)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_RESERVED1_OFF          (12)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_RESERVED1_WID          ( 4)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_RESERVED1_MSK          (0x0000F000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_RESERVED1_MIN          (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_RESERVED1_MAX          (15) // 0x0000000F
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_RESERVED1_DEF          (0x00000000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_RESERVED1_HSH          (0x040C64B4)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_OFF  (16)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_MSK  (0x00FF0000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_DEF  (0x00000000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_HSH  (0x081064B4)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_OFF  (24)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_MSK  (0xFF000000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_DEF  (0x00000000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_HSH  (0x081864B4)

#define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REG                      (0x000064B8)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_OFF   ( 0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_MSK   (0x0000000F)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_HSH   (0x040064B8)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_OFF       ( 4)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_WID       ( 3)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_MSK       (0x00000070)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_MIN       (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_MAX       (7) // 0x00000007
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_DEF       (0x00000000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_HSH       (0x030464B8)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_OFF ( 7)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_WID ( 1)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_MSK (0x00000080)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_MIN (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_MAX (1) // 0x00000001
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_DEF (0x00000000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_HSH (0x010764B8)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_OFF   ( 8)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_MSK   (0x00000F00)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_HSH   (0x040864B8)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_RESERVED1_OFF          (12)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_RESERVED1_WID          ( 4)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_RESERVED1_MSK          (0x0000F000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_RESERVED1_MIN          (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_RESERVED1_MAX          (15) // 0x0000000F
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_RESERVED1_DEF          (0x00000000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_RESERVED1_HSH          (0x040C64B8)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_OFF  (16)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_MSK  (0x00FF0000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_DEF  (0x00000000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_HSH  (0x081064B8)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_OFF  (24)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_MSK  (0xFF000000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_DEF  (0x00000000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_HSH  (0x081864B8)

#define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REG                      (0x000064BC)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_OFF   ( 0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_MSK   (0x0000000F)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_HSH   (0x040064BC)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_OFF       ( 4)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_WID       ( 3)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_MSK       (0x00000070)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_MIN       (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_MAX       (7) // 0x00000007
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_DEF       (0x00000000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_HSH       (0x030464BC)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_OFF ( 7)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_WID ( 1)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_MSK (0x00000080)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_MIN (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_MAX (1) // 0x00000001
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_DEF (0x00000000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_HSH (0x010764BC)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_OFF   ( 8)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_MSK   (0x00000F00)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_HSH   (0x040864BC)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_RESERVED1_OFF          (12)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_RESERVED1_WID          ( 4)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_RESERVED1_MSK          (0x0000F000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_RESERVED1_MIN          (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_RESERVED1_MAX          (15) // 0x0000000F
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_RESERVED1_DEF          (0x00000000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_RESERVED1_HSH          (0x040C64BC)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_OFF  (16)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_MSK  (0x00FF0000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_DEF  (0x00000000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_HSH  (0x081064BC)

  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_OFF  (24)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_MSK  (0xFF000000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_DEF  (0x00000000)
  #define REQUEST_PORT_2_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_HSH  (0x081864BC)

#define REQUEST_PORT_2_REQ_CONFIG_1_REG                                (0x000064C0)

  #define REQUEST_PORT_2_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_OFF            ( 0)
  #define REQUEST_PORT_2_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_WID            ( 8)
  #define REQUEST_PORT_2_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_MSK            (0x000000FF)
  #define REQUEST_PORT_2_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_MIN            (0)
  #define REQUEST_PORT_2_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_MAX            (255) // 0x000000FF
  #define REQUEST_PORT_2_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_DEF            (0x00000002)
  #define REQUEST_PORT_2_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_HSH            (0x080064C0)

  #define REQUEST_PORT_2_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_OFF            ( 8)
  #define REQUEST_PORT_2_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_WID            ( 8)
  #define REQUEST_PORT_2_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_MSK            (0x0000FF00)
  #define REQUEST_PORT_2_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_MIN            (0)
  #define REQUEST_PORT_2_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_MAX            (255) // 0x000000FF
  #define REQUEST_PORT_2_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_DEF            (0x00000003)
  #define REQUEST_PORT_2_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_HSH            (0x080864C0)

  #define REQUEST_PORT_2_REQ_CONFIG_1_RESERVED1_OFF                    (16)
  #define REQUEST_PORT_2_REQ_CONFIG_1_RESERVED1_WID                    (16)
  #define REQUEST_PORT_2_REQ_CONFIG_1_RESERVED1_MSK                    (0xFFFF0000)
  #define REQUEST_PORT_2_REQ_CONFIG_1_RESERVED1_MIN                    (0)
  #define REQUEST_PORT_2_REQ_CONFIG_1_RESERVED1_MAX                    (65535) // 0x0000FFFF
  #define REQUEST_PORT_2_REQ_CONFIG_1_RESERVED1_DEF                    (0x00000000)
  #define REQUEST_PORT_2_REQ_CONFIG_1_RESERVED1_HSH                    (0x101064C0)

#define REQUEST_PORT_2_STALL_REG                                       (0x000064C4)

  #define REQUEST_PORT_2_STALL_REQ_STALL_OFF                           ( 0)
  #define REQUEST_PORT_2_STALL_REQ_STALL_WID                           ( 1)
  #define REQUEST_PORT_2_STALL_REQ_STALL_MSK                           (0x00000001)
  #define REQUEST_PORT_2_STALL_REQ_STALL_MIN                           (0)
  #define REQUEST_PORT_2_STALL_REQ_STALL_MAX                           (1) // 0x00000001
  #define REQUEST_PORT_2_STALL_REQ_STALL_DEF                           (0x00000000)
  #define REQUEST_PORT_2_STALL_REQ_STALL_HSH                           (0x010064C4)

  #define REQUEST_PORT_2_STALL_RSVD0_OFF                               ( 1)
  #define REQUEST_PORT_2_STALL_RSVD0_WID                               ( 4)
  #define REQUEST_PORT_2_STALL_RSVD0_MSK                               (0x0000001E)
  #define REQUEST_PORT_2_STALL_RSVD0_MIN                               (0)
  #define REQUEST_PORT_2_STALL_RSVD0_MAX                               (15) // 0x0000000F
  #define REQUEST_PORT_2_STALL_RSVD0_DEF                               (0x00000000)
  #define REQUEST_PORT_2_STALL_RSVD0_HSH                               (0x040164C4)

  #define REQUEST_PORT_2_STALL_RSVD1_OFF                               ( 5)
  #define REQUEST_PORT_2_STALL_RSVD1_WID                               ( 3)
  #define REQUEST_PORT_2_STALL_RSVD1_MSK                               (0x000000E0)
  #define REQUEST_PORT_2_STALL_RSVD1_MIN                               (0)
  #define REQUEST_PORT_2_STALL_RSVD1_MAX                               (7) // 0x00000007
  #define REQUEST_PORT_2_STALL_RSVD1_DEF                               (0x00000000)
  #define REQUEST_PORT_2_STALL_RSVD1_HSH                               (0x030564C4)

  #define REQUEST_PORT_2_STALL_UNSTALL_COUNTER_VALUE_OFF               ( 8)
  #define REQUEST_PORT_2_STALL_UNSTALL_COUNTER_VALUE_WID               (16)
  #define REQUEST_PORT_2_STALL_UNSTALL_COUNTER_VALUE_MSK               (0x00FFFF00)
  #define REQUEST_PORT_2_STALL_UNSTALL_COUNTER_VALUE_MIN               (0)
  #define REQUEST_PORT_2_STALL_UNSTALL_COUNTER_VALUE_MAX               (65535) // 0x0000FFFF
  #define REQUEST_PORT_2_STALL_UNSTALL_COUNTER_VALUE_DEF               (0x00000000)
  #define REQUEST_PORT_2_STALL_UNSTALL_COUNTER_VALUE_HSH               (0x100864C4)

#define REQUEST_PORT_2_RESERVED_0_REG                                  (0x000064C8)

  #define REQUEST_PORT_2_RESERVED_0_RESERVED_OFF                       ( 0)
  #define REQUEST_PORT_2_RESERVED_0_RESERVED_WID                       (32)
  #define REQUEST_PORT_2_RESERVED_0_RESERVED_MSK                       (0xFFFFFFFF)
  #define REQUEST_PORT_2_RESERVED_0_RESERVED_MIN                       (0)
  #define REQUEST_PORT_2_RESERVED_0_RESERVED_MAX                       (4294967295) // 0xFFFFFFFF
  #define REQUEST_PORT_2_RESERVED_0_RESERVED_DEF                       (0x00000000)
  #define REQUEST_PORT_2_RESERVED_0_RESERVED_HSH                       (0x200064C8)

#define REQUEST_PORT_2_RESERVED_1_REG                                  (0x000064CC)

  #define REQUEST_PORT_2_RESERVED_1_RESERVED_OFF                       ( 0)
  #define REQUEST_PORT_2_RESERVED_1_RESERVED_WID                       (32)
  #define REQUEST_PORT_2_RESERVED_1_RESERVED_MSK                       (0xFFFFFFFF)
  #define REQUEST_PORT_2_RESERVED_1_RESERVED_MIN                       (0)
  #define REQUEST_PORT_2_RESERVED_1_RESERVED_MAX                       (4294967295) // 0xFFFFFFFF
  #define REQUEST_PORT_2_RESERVED_1_RESERVED_DEF                       (0x00000000)
  #define REQUEST_PORT_2_RESERVED_1_RESERVED_HSH                       (0x200064CC)

#define REQUEST_PORT_2_RESERVED_2_REG                                  (0x000064D0)

  #define REQUEST_PORT_2_RESERVED_2_RESERVED_OFF                       ( 0)
  #define REQUEST_PORT_2_RESERVED_2_RESERVED_WID                       (32)
  #define REQUEST_PORT_2_RESERVED_2_RESERVED_MSK                       (0xFFFFFFFF)
  #define REQUEST_PORT_2_RESERVED_2_RESERVED_MIN                       (0)
  #define REQUEST_PORT_2_RESERVED_2_RESERVED_MAX                       (4294967295) // 0xFFFFFFFF
  #define REQUEST_PORT_2_RESERVED_2_RESERVED_DEF                       (0x00000000)
  #define REQUEST_PORT_2_RESERVED_2_RESERVED_HSH                       (0x200064D0)

#define REQUEST_PORT_2_ACCUM_REQ_IN_REG                                (0x000064D4)

  #define REQUEST_PORT_2_ACCUM_REQ_IN_REQ_CMD_SUM_OFF                  ( 0)
  #define REQUEST_PORT_2_ACCUM_REQ_IN_REQ_CMD_SUM_WID                  (16)
  #define REQUEST_PORT_2_ACCUM_REQ_IN_REQ_CMD_SUM_MSK                  (0x0000FFFF)
  #define REQUEST_PORT_2_ACCUM_REQ_IN_REQ_CMD_SUM_MIN                  (0)
  #define REQUEST_PORT_2_ACCUM_REQ_IN_REQ_CMD_SUM_MAX                  (65535) // 0x0000FFFF
  #define REQUEST_PORT_2_ACCUM_REQ_IN_REQ_CMD_SUM_DEF                  (0x00000000)
  #define REQUEST_PORT_2_ACCUM_REQ_IN_REQ_CMD_SUM_HSH                  (0x100064D4)

  #define REQUEST_PORT_2_ACCUM_REQ_IN_REQ_DATA_SUM_OFF                 (16)
  #define REQUEST_PORT_2_ACCUM_REQ_IN_REQ_DATA_SUM_WID                 (16)
  #define REQUEST_PORT_2_ACCUM_REQ_IN_REQ_DATA_SUM_MSK                 (0xFFFF0000)
  #define REQUEST_PORT_2_ACCUM_REQ_IN_REQ_DATA_SUM_MIN                 (0)
  #define REQUEST_PORT_2_ACCUM_REQ_IN_REQ_DATA_SUM_MAX                 (65535) // 0x0000FFFF
  #define REQUEST_PORT_2_ACCUM_REQ_IN_REQ_DATA_SUM_DEF                 (0x00000000)
  #define REQUEST_PORT_2_ACCUM_REQ_IN_REQ_DATA_SUM_HSH                 (0x101064D4)

#define REQUEST_PORT_2_ACCUM_RD_CPL_OUT_REG                            (0x000064D8)

  #define REQUEST_PORT_2_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_OFF           ( 0)
  #define REQUEST_PORT_2_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_WID           (16)
  #define REQUEST_PORT_2_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_MSK           (0x0000FFFF)
  #define REQUEST_PORT_2_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_MIN           (0)
  #define REQUEST_PORT_2_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_MAX           (65535) // 0x0000FFFF
  #define REQUEST_PORT_2_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_DEF           (0x00000000)
  #define REQUEST_PORT_2_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_HSH           (0x100064D8)

  #define REQUEST_PORT_2_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_OFF          (16)
  #define REQUEST_PORT_2_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_WID          (16)
  #define REQUEST_PORT_2_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_MSK          (0xFFFF0000)
  #define REQUEST_PORT_2_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_MIN          (0)
  #define REQUEST_PORT_2_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_MAX          (65535) // 0x0000FFFF
  #define REQUEST_PORT_2_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_DEF          (0x00000000)
  #define REQUEST_PORT_2_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_HSH          (0x101064D8)

#define REQUEST_PORT_2_ACCUM_RSP_OUT_REG                               (0x000064DC)

  #define REQUEST_PORT_2_ACCUM_RSP_OUT_RSP_CMD_SUM_OFF                 ( 0)
  #define REQUEST_PORT_2_ACCUM_RSP_OUT_RSP_CMD_SUM_WID                 (16)
  #define REQUEST_PORT_2_ACCUM_RSP_OUT_RSP_CMD_SUM_MSK                 (0x0000FFFF)
  #define REQUEST_PORT_2_ACCUM_RSP_OUT_RSP_CMD_SUM_MIN                 (0)
  #define REQUEST_PORT_2_ACCUM_RSP_OUT_RSP_CMD_SUM_MAX                 (65535) // 0x0000FFFF
  #define REQUEST_PORT_2_ACCUM_RSP_OUT_RSP_CMD_SUM_DEF                 (0x00000000)
  #define REQUEST_PORT_2_ACCUM_RSP_OUT_RSP_CMD_SUM_HSH                 (0x100064DC)

  #define REQUEST_PORT_2_ACCUM_RSP_OUT_RSVD_OFF                        (16)
  #define REQUEST_PORT_2_ACCUM_RSP_OUT_RSVD_WID                        (16)
  #define REQUEST_PORT_2_ACCUM_RSP_OUT_RSVD_MSK                        (0xFFFF0000)
  #define REQUEST_PORT_2_ACCUM_RSP_OUT_RSVD_MIN                        (0)
  #define REQUEST_PORT_2_ACCUM_RSP_OUT_RSVD_MAX                        (65535) // 0x0000FFFF
  #define REQUEST_PORT_2_ACCUM_RSP_OUT_RSVD_DEF                        (0x00000000)
  #define REQUEST_PORT_2_ACCUM_RSP_OUT_RSVD_HSH                        (0x101064DC)

#define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REG                      (0x000064E0)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_OFF   ( 0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_MSK   (0x0000000F)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_PARK_SIZE_HSH   (0x040064E0)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_OFF       ( 4)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_WID       ( 3)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_MSK       (0x00000070)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_MIN       (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_MAX       (7) // 0x00000007
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_DEF       (0x00000000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_HSH       (0x030464E0)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_OFF ( 7)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_WID ( 1)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_MSK (0x00000080)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_MIN (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_MAX (1) // 0x00000001
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_DEF (0x00000000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_VC1WR_WINDOW_FIX_DISABLE_HSH (0x010764E0)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_OFF   ( 8)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_MSK   (0x00000F00)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_PARK_SIZE_HSH   (0x040864E0)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_RESERVED1_OFF          (12)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_RESERVED1_WID          ( 4)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_RESERVED1_MSK          (0x0000F000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_RESERVED1_MIN          (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_RESERVED1_MAX          (15) // 0x0000000F
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_RESERVED1_DEF          (0x00000000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_RESERVED1_HSH          (0x040C64E0)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_OFF  (16)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_MSK  (0x00FF0000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_DEF  (0x00000000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_WR_MAX_CREDIT_HSH  (0x081064E0)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_OFF  (24)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_MSK  (0xFF000000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_DEF  (0x00000000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_0_REQ_RD_MAX_CREDIT_HSH  (0x081864E0)

#define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REG                      (0x000064E4)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_OFF   ( 0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_MSK   (0x0000000F)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_WR_PARK_SIZE_HSH   (0x040064E4)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_OFF       ( 4)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_WID       ( 3)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_MSK       (0x00000070)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_MIN       (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_MAX       (7) // 0x00000007
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_DEF       (0x00000000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_HSH       (0x030464E4)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_OFF ( 7)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_WID ( 1)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_MSK (0x00000080)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_MIN (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_MAX (1) // 0x00000001
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_DEF (0x00000000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_VC1WR_WINDOW_FIX_DISABLE_HSH (0x010764E4)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_OFF   ( 8)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_MSK   (0x00000F00)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_RD_PARK_SIZE_HSH   (0x040864E4)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_RESERVED1_OFF          (12)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_RESERVED1_WID          ( 4)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_RESERVED1_MSK          (0x0000F000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_RESERVED1_MIN          (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_RESERVED1_MAX          (15) // 0x0000000F
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_RESERVED1_DEF          (0x00000000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_RESERVED1_HSH          (0x040C64E4)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_OFF  (16)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_MSK  (0x00FF0000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_DEF  (0x00000000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_WR_MAX_CREDIT_HSH  (0x081064E4)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_OFF  (24)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_MSK  (0xFF000000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_DEF  (0x00000000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_1_REQ_RD_MAX_CREDIT_HSH  (0x081864E4)

#define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REG                      (0x000064E8)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_OFF   ( 0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_MSK   (0x0000000F)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_WR_PARK_SIZE_HSH   (0x040064E8)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_OFF       ( 4)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_WID       ( 3)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_MSK       (0x00000070)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_MIN       (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_MAX       (7) // 0x00000007
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_DEF       (0x00000000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_HSH       (0x030464E8)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_OFF ( 7)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_WID ( 1)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_MSK (0x00000080)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_MIN (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_MAX (1) // 0x00000001
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_DEF (0x00000000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_VC1WR_WINDOW_FIX_DISABLE_HSH (0x010764E8)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_OFF   ( 8)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_MSK   (0x00000F00)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_RD_PARK_SIZE_HSH   (0x040864E8)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_RESERVED1_OFF          (12)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_RESERVED1_WID          ( 4)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_RESERVED1_MSK          (0x0000F000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_RESERVED1_MIN          (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_RESERVED1_MAX          (15) // 0x0000000F
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_RESERVED1_DEF          (0x00000000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_RESERVED1_HSH          (0x040C64E8)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_OFF  (16)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_MSK  (0x00FF0000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_DEF  (0x00000000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_WR_MAX_CREDIT_HSH  (0x081064E8)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_OFF  (24)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_MSK  (0xFF000000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_DEF  (0x00000000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_2_REQ_RD_MAX_CREDIT_HSH  (0x081864E8)

#define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REG                      (0x000064EC)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_OFF   ( 0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_MSK   (0x0000000F)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_WR_PARK_SIZE_HSH   (0x040064EC)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_OFF       ( 4)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_WID       ( 3)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_MSK       (0x00000070)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_MIN       (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_MAX       (7) // 0x00000007
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_DEF       (0x00000000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_HSH       (0x030464EC)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_OFF ( 7)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_WID ( 1)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_MSK (0x00000080)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_MIN (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_MAX (1) // 0x00000001
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_DEF (0x00000000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_VC1WR_WINDOW_FIX_DISABLE_HSH (0x010764EC)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_OFF   ( 8)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_WID   ( 4)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_MSK   (0x00000F00)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_MIN   (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_MAX   (15) // 0x0000000F
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_DEF   (0x00000003)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_RD_PARK_SIZE_HSH   (0x040864EC)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_RESERVED1_OFF          (12)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_RESERVED1_WID          ( 4)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_RESERVED1_MSK          (0x0000F000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_RESERVED1_MIN          (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_RESERVED1_MAX          (15) // 0x0000000F
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_RESERVED1_DEF          (0x00000000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_RESERVED1_HSH          (0x040C64EC)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_OFF  (16)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_MSK  (0x00FF0000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_DEF  (0x00000000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_WR_MAX_CREDIT_HSH  (0x081064EC)

  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_OFF  (24)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_WID  ( 8)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_MSK  (0xFF000000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_MIN  (0)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_DEF  (0x00000000)
  #define REQUEST_PORT_3_REQ_CONFIG_0_CHANNEL_3_REQ_RD_MAX_CREDIT_HSH  (0x081864EC)

#define REQUEST_PORT_3_REQ_CONFIG_1_REG                                (0x000064F0)

  #define REQUEST_PORT_3_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_OFF            ( 0)
  #define REQUEST_PORT_3_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_WID            ( 8)
  #define REQUEST_PORT_3_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_MSK            (0x000000FF)
  #define REQUEST_PORT_3_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_MIN            (0)
  #define REQUEST_PORT_3_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_MAX            (255) // 0x000000FF
  #define REQUEST_PORT_3_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_DEF            (0x00000000)
  #define REQUEST_PORT_3_REQ_CONFIG_1_REQ_WR_QUEUEDEPTH_HSH            (0x080064F0)

  #define REQUEST_PORT_3_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_OFF            ( 8)
  #define REQUEST_PORT_3_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_WID            ( 8)
  #define REQUEST_PORT_3_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_MSK            (0x0000FF00)
  #define REQUEST_PORT_3_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_MIN            (0)
  #define REQUEST_PORT_3_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_MAX            (255) // 0x000000FF
  #define REQUEST_PORT_3_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_DEF            (0x00000000)
  #define REQUEST_PORT_3_REQ_CONFIG_1_REQ_RD_QUEUEDEPTH_HSH            (0x080864F0)

  #define REQUEST_PORT_3_REQ_CONFIG_1_RESERVED1_OFF                    (16)
  #define REQUEST_PORT_3_REQ_CONFIG_1_RESERVED1_WID                    (16)
  #define REQUEST_PORT_3_REQ_CONFIG_1_RESERVED1_MSK                    (0xFFFF0000)
  #define REQUEST_PORT_3_REQ_CONFIG_1_RESERVED1_MIN                    (0)
  #define REQUEST_PORT_3_REQ_CONFIG_1_RESERVED1_MAX                    (65535) // 0x0000FFFF
  #define REQUEST_PORT_3_REQ_CONFIG_1_RESERVED1_DEF                    (0x00000000)
  #define REQUEST_PORT_3_REQ_CONFIG_1_RESERVED1_HSH                    (0x101064F0)

#define REQUEST_PORT_3_STALL_REG                                       (0x000064F4)

  #define REQUEST_PORT_3_STALL_REQ_STALL_OFF                           ( 0)
  #define REQUEST_PORT_3_STALL_REQ_STALL_WID                           ( 1)
  #define REQUEST_PORT_3_STALL_REQ_STALL_MSK                           (0x00000001)
  #define REQUEST_PORT_3_STALL_REQ_STALL_MIN                           (0)
  #define REQUEST_PORT_3_STALL_REQ_STALL_MAX                           (1) // 0x00000001
  #define REQUEST_PORT_3_STALL_REQ_STALL_DEF                           (0x00000000)
  #define REQUEST_PORT_3_STALL_REQ_STALL_HSH                           (0x010064F4)

  #define REQUEST_PORT_3_STALL_RSVD0_OFF                               ( 1)
  #define REQUEST_PORT_3_STALL_RSVD0_WID                               ( 4)
  #define REQUEST_PORT_3_STALL_RSVD0_MSK                               (0x0000001E)
  #define REQUEST_PORT_3_STALL_RSVD0_MIN                               (0)
  #define REQUEST_PORT_3_STALL_RSVD0_MAX                               (15) // 0x0000000F
  #define REQUEST_PORT_3_STALL_RSVD0_DEF                               (0x00000000)
  #define REQUEST_PORT_3_STALL_RSVD0_HSH                               (0x040164F4)

  #define REQUEST_PORT_3_STALL_RSVD1_OFF                               ( 5)
  #define REQUEST_PORT_3_STALL_RSVD1_WID                               ( 3)
  #define REQUEST_PORT_3_STALL_RSVD1_MSK                               (0x000000E0)
  #define REQUEST_PORT_3_STALL_RSVD1_MIN                               (0)
  #define REQUEST_PORT_3_STALL_RSVD1_MAX                               (7) // 0x00000007
  #define REQUEST_PORT_3_STALL_RSVD1_DEF                               (0x00000000)
  #define REQUEST_PORT_3_STALL_RSVD1_HSH                               (0x030564F4)

  #define REQUEST_PORT_3_STALL_UNSTALL_COUNTER_VALUE_OFF               ( 8)
  #define REQUEST_PORT_3_STALL_UNSTALL_COUNTER_VALUE_WID               (16)
  #define REQUEST_PORT_3_STALL_UNSTALL_COUNTER_VALUE_MSK               (0x00FFFF00)
  #define REQUEST_PORT_3_STALL_UNSTALL_COUNTER_VALUE_MIN               (0)
  #define REQUEST_PORT_3_STALL_UNSTALL_COUNTER_VALUE_MAX               (65535) // 0x0000FFFF
  #define REQUEST_PORT_3_STALL_UNSTALL_COUNTER_VALUE_DEF               (0x00000000)
  #define REQUEST_PORT_3_STALL_UNSTALL_COUNTER_VALUE_HSH               (0x100864F4)

#define REQUEST_PORT_3_RESERVED_0_REG                                  (0x000064F8)

  #define REQUEST_PORT_3_RESERVED_0_RESERVED_OFF                       ( 0)
  #define REQUEST_PORT_3_RESERVED_0_RESERVED_WID                       (32)
  #define REQUEST_PORT_3_RESERVED_0_RESERVED_MSK                       (0xFFFFFFFF)
  #define REQUEST_PORT_3_RESERVED_0_RESERVED_MIN                       (0)
  #define REQUEST_PORT_3_RESERVED_0_RESERVED_MAX                       (4294967295) // 0xFFFFFFFF
  #define REQUEST_PORT_3_RESERVED_0_RESERVED_DEF                       (0x00000000)
  #define REQUEST_PORT_3_RESERVED_0_RESERVED_HSH                       (0x200064F8)

#define REQUEST_PORT_3_RESERVED_1_REG                                  (0x000064FC)

  #define REQUEST_PORT_3_RESERVED_1_RESERVED_OFF                       ( 0)
  #define REQUEST_PORT_3_RESERVED_1_RESERVED_WID                       (32)
  #define REQUEST_PORT_3_RESERVED_1_RESERVED_MSK                       (0xFFFFFFFF)
  #define REQUEST_PORT_3_RESERVED_1_RESERVED_MIN                       (0)
  #define REQUEST_PORT_3_RESERVED_1_RESERVED_MAX                       (4294967295) // 0xFFFFFFFF
  #define REQUEST_PORT_3_RESERVED_1_RESERVED_DEF                       (0x00000000)
  #define REQUEST_PORT_3_RESERVED_1_RESERVED_HSH                       (0x200064FC)

#define REQUEST_PORT_3_RESERVED_2_REG                                  (0x00006500)

  #define REQUEST_PORT_3_RESERVED_2_RESERVED_OFF                       ( 0)
  #define REQUEST_PORT_3_RESERVED_2_RESERVED_WID                       (32)
  #define REQUEST_PORT_3_RESERVED_2_RESERVED_MSK                       (0xFFFFFFFF)
  #define REQUEST_PORT_3_RESERVED_2_RESERVED_MIN                       (0)
  #define REQUEST_PORT_3_RESERVED_2_RESERVED_MAX                       (4294967295) // 0xFFFFFFFF
  #define REQUEST_PORT_3_RESERVED_2_RESERVED_DEF                       (0x00000000)
  #define REQUEST_PORT_3_RESERVED_2_RESERVED_HSH                       (0x20006500)

#define REQUEST_PORT_3_ACCUM_REQ_IN_REG                                (0x00006504)

  #define REQUEST_PORT_3_ACCUM_REQ_IN_REQ_CMD_SUM_OFF                  ( 0)
  #define REQUEST_PORT_3_ACCUM_REQ_IN_REQ_CMD_SUM_WID                  (16)
  #define REQUEST_PORT_3_ACCUM_REQ_IN_REQ_CMD_SUM_MSK                  (0x0000FFFF)
  #define REQUEST_PORT_3_ACCUM_REQ_IN_REQ_CMD_SUM_MIN                  (0)
  #define REQUEST_PORT_3_ACCUM_REQ_IN_REQ_CMD_SUM_MAX                  (65535) // 0x0000FFFF
  #define REQUEST_PORT_3_ACCUM_REQ_IN_REQ_CMD_SUM_DEF                  (0x00000000)
  #define REQUEST_PORT_3_ACCUM_REQ_IN_REQ_CMD_SUM_HSH                  (0x10006504)

  #define REQUEST_PORT_3_ACCUM_REQ_IN_REQ_DATA_SUM_OFF                 (16)
  #define REQUEST_PORT_3_ACCUM_REQ_IN_REQ_DATA_SUM_WID                 (16)
  #define REQUEST_PORT_3_ACCUM_REQ_IN_REQ_DATA_SUM_MSK                 (0xFFFF0000)
  #define REQUEST_PORT_3_ACCUM_REQ_IN_REQ_DATA_SUM_MIN                 (0)
  #define REQUEST_PORT_3_ACCUM_REQ_IN_REQ_DATA_SUM_MAX                 (65535) // 0x0000FFFF
  #define REQUEST_PORT_3_ACCUM_REQ_IN_REQ_DATA_SUM_DEF                 (0x00000000)
  #define REQUEST_PORT_3_ACCUM_REQ_IN_REQ_DATA_SUM_HSH                 (0x10106504)

#define REQUEST_PORT_3_ACCUM_RD_CPL_OUT_REG                            (0x00006508)

  #define REQUEST_PORT_3_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_OFF           ( 0)
  #define REQUEST_PORT_3_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_WID           (16)
  #define REQUEST_PORT_3_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_MSK           (0x0000FFFF)
  #define REQUEST_PORT_3_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_MIN           (0)
  #define REQUEST_PORT_3_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_MAX           (65535) // 0x0000FFFF
  #define REQUEST_PORT_3_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_DEF           (0x00000000)
  #define REQUEST_PORT_3_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_HSH           (0x10006508)

  #define REQUEST_PORT_3_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_OFF          (16)
  #define REQUEST_PORT_3_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_WID          (16)
  #define REQUEST_PORT_3_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_MSK          (0xFFFF0000)
  #define REQUEST_PORT_3_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_MIN          (0)
  #define REQUEST_PORT_3_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_MAX          (65535) // 0x0000FFFF
  #define REQUEST_PORT_3_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_DEF          (0x00000000)
  #define REQUEST_PORT_3_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_HSH          (0x10106508)

#define REQUEST_PORT_3_ACCUM_RSP_OUT_REG                               (0x0000650C)

  #define REQUEST_PORT_3_ACCUM_RSP_OUT_RSP_CMD_SUM_OFF                 ( 0)
  #define REQUEST_PORT_3_ACCUM_RSP_OUT_RSP_CMD_SUM_WID                 (16)
  #define REQUEST_PORT_3_ACCUM_RSP_OUT_RSP_CMD_SUM_MSK                 (0x0000FFFF)
  #define REQUEST_PORT_3_ACCUM_RSP_OUT_RSP_CMD_SUM_MIN                 (0)
  #define REQUEST_PORT_3_ACCUM_RSP_OUT_RSP_CMD_SUM_MAX                 (65535) // 0x0000FFFF
  #define REQUEST_PORT_3_ACCUM_RSP_OUT_RSP_CMD_SUM_DEF                 (0x00000000)
  #define REQUEST_PORT_3_ACCUM_RSP_OUT_RSP_CMD_SUM_HSH                 (0x1000650C)

  #define REQUEST_PORT_3_ACCUM_RSP_OUT_RSVD_OFF                        (16)
  #define REQUEST_PORT_3_ACCUM_RSP_OUT_RSVD_WID                        (16)
  #define REQUEST_PORT_3_ACCUM_RSP_OUT_RSVD_MSK                        (0xFFFF0000)
  #define REQUEST_PORT_3_ACCUM_RSP_OUT_RSVD_MIN                        (0)
  #define REQUEST_PORT_3_ACCUM_RSP_OUT_RSVD_MAX                        (65535) // 0x0000FFFF
  #define REQUEST_PORT_3_ACCUM_RSP_OUT_RSVD_DEF                        (0x00000000)
  #define REQUEST_PORT_3_ACCUM_RSP_OUT_RSVD_HSH                        (0x1010650C)

#define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_REG                      (0x00006540)

  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_OFF      ( 0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_WID      ( 4)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_MSK      (0x0000000F)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_MIN      (0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_MAX      (15) // 0x0000000F
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_DEF      (0x00000003)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_HSH      (0x04006540)

  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED0_OFF          ( 4)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED0_WID          ( 4)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED0_MSK          (0x000000F0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED0_MIN          (0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED0_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED0_DEF          (0x00000000)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED0_HSH          (0x04046540)

  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_OFF   ( 8)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_WID   ( 4)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_MSK   (0x00000F00)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_MIN   (0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_MAX   (15) // 0x0000000F
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_DEF   (0x00000003)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_HSH   (0x04086540)

  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED1_OFF          (12)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED1_WID          ( 4)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED1_MSK          (0x0000F000)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED1_MIN          (0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED1_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED1_DEF          (0x00000000)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RESERVED1_HSH          (0x040C6540)

  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_OFF     (16)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_WID     ( 8)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_MSK     (0x00FF0000)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_MIN     (0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_MAX     (255) // 0x000000FF
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_DEF     (0x00000000)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_HSH     (0x08106540)

  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_OFF  (24)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_WID  ( 8)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_MSK  (0xFF000000)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_MIN  (0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_DEF  (0x00000000)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_HSH  (0x08186540)

#define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_REG                      (0x00006544)

  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_OFF      ( 0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_WID      ( 4)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_MSK      (0x0000000F)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_MIN      (0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_MAX      (15) // 0x0000000F
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_DEF      (0x00000003)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_HSH      (0x04006544)

  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RESERVED0_OFF          ( 4)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RESERVED0_WID          ( 4)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RESERVED0_MSK          (0x000000F0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RESERVED0_MIN          (0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RESERVED0_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RESERVED0_DEF          (0x00000000)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RESERVED0_HSH          (0x04046544)

  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_OFF   ( 8)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_WID   ( 4)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_MSK   (0x00000F00)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_MIN   (0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_MAX   (15) // 0x0000000F
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_DEF   (0x00000003)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_HSH   (0x04086544)

  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RESERVED1_OFF          (12)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RESERVED1_WID          ( 4)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RESERVED1_MSK          (0x0000F000)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RESERVED1_MIN          (0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RESERVED1_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RESERVED1_DEF          (0x00000000)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RESERVED1_HSH          (0x040C6544)

  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_OFF     (16)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_WID     ( 8)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_MSK     (0x00FF0000)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_MIN     (0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_MAX     (255) // 0x000000FF
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_DEF     (0x00000000)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_HSH     (0x08106544)

  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_OFF  (24)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_WID  ( 8)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_MSK  (0xFF000000)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_MIN  (0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_DEF  (0x00000000)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_HSH  (0x08186544)

#define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_REG                      (0x00006548)

  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_OFF      ( 0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_WID      ( 4)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_MSK      (0x0000000F)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_MIN      (0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_MAX      (15) // 0x0000000F
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_DEF      (0x00000003)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_HSH      (0x04006548)

  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RESERVED0_OFF          ( 4)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RESERVED0_WID          ( 4)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RESERVED0_MSK          (0x000000F0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RESERVED0_MIN          (0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RESERVED0_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RESERVED0_DEF          (0x00000000)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RESERVED0_HSH          (0x04046548)

  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_OFF   ( 8)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_WID   ( 4)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_MSK   (0x00000F00)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_MIN   (0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_MAX   (15) // 0x0000000F
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_DEF   (0x00000003)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_HSH   (0x04086548)

  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RESERVED1_OFF          (12)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RESERVED1_WID          ( 4)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RESERVED1_MSK          (0x0000F000)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RESERVED1_MIN          (0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RESERVED1_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RESERVED1_DEF          (0x00000000)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RESERVED1_HSH          (0x040C6548)

  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_OFF     (16)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_WID     ( 8)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_MSK     (0x00FF0000)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_MIN     (0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_MAX     (255) // 0x000000FF
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_DEF     (0x00000000)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_HSH     (0x08106548)

  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_OFF  (24)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_WID  ( 8)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_MSK  (0xFF000000)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_MIN  (0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_DEF  (0x00000000)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_HSH  (0x08186548)

#define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_REG                      (0x0000654C)

  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_OFF      ( 0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_WID      ( 4)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_MSK      (0x0000000F)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_MIN      (0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_MAX      (15) // 0x0000000F
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_DEF      (0x00000003)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_HSH      (0x0400654C)

  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED0_OFF          ( 4)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED0_WID          ( 4)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED0_MSK          (0x000000F0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED0_MIN          (0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED0_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED0_DEF          (0x00000000)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED0_HSH          (0x0404654C)

  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_OFF   ( 8)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_WID   ( 4)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_MSK   (0x00000F00)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_MIN   (0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_MAX   (15) // 0x0000000F
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_DEF   (0x00000003)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_HSH   (0x0408654C)

  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED1_OFF          (12)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED1_WID          ( 4)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED1_MSK          (0x0000F000)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED1_MIN          (0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED1_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED1_DEF          (0x00000000)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RESERVED1_HSH          (0x040C654C)

  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_OFF     (16)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_WID     ( 8)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_MSK     (0x00FF0000)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_MIN     (0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_MAX     (255) // 0x000000FF
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_DEF     (0x00000003)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_HSH     (0x0810654C)

  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_OFF  (24)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_WID  ( 8)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_MSK  (0xFF000000)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_MIN  (0)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_DEF  (0x00000002)
  #define RESPOND_PORT_0_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_HSH  (0x0818654C)

#define RESPOND_PORT_0_CPL_CONFIG_1_REG                                (0x00006550)

  #define RESPOND_PORT_0_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_OFF            ( 0)
  #define RESPOND_PORT_0_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_WID            ( 8)
  #define RESPOND_PORT_0_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_MSK            (0x000000FF)
  #define RESPOND_PORT_0_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_MIN            (0)
  #define RESPOND_PORT_0_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_MAX            (255) // 0x000000FF
  #define RESPOND_PORT_0_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_DEF            (0x00000002)
  #define RESPOND_PORT_0_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_HSH            (0x08006550)

  #define RESPOND_PORT_0_CPL_CONFIG_1_RSP_QUEUEDEPTH_OFF               ( 8)
  #define RESPOND_PORT_0_CPL_CONFIG_1_RSP_QUEUEDEPTH_WID               ( 8)
  #define RESPOND_PORT_0_CPL_CONFIG_1_RSP_QUEUEDEPTH_MSK               (0x0000FF00)
  #define RESPOND_PORT_0_CPL_CONFIG_1_RSP_QUEUEDEPTH_MIN               (0)
  #define RESPOND_PORT_0_CPL_CONFIG_1_RSP_QUEUEDEPTH_MAX               (255) // 0x000000FF
  #define RESPOND_PORT_0_CPL_CONFIG_1_RSP_QUEUEDEPTH_DEF               (0x00000003)
  #define RESPOND_PORT_0_CPL_CONFIG_1_RSP_QUEUEDEPTH_HSH               (0x08086550)

  #define RESPOND_PORT_0_CPL_CONFIG_1_RESERVED1_OFF                    (16)
  #define RESPOND_PORT_0_CPL_CONFIG_1_RESERVED1_WID                    (16)
  #define RESPOND_PORT_0_CPL_CONFIG_1_RESERVED1_MSK                    (0xFFFF0000)
  #define RESPOND_PORT_0_CPL_CONFIG_1_RESERVED1_MIN                    (0)
  #define RESPOND_PORT_0_CPL_CONFIG_1_RESERVED1_MAX                    (65535) // 0x0000FFFF
  #define RESPOND_PORT_0_CPL_CONFIG_1_RESERVED1_DEF                    (0x00000000)
  #define RESPOND_PORT_0_CPL_CONFIG_1_RESERVED1_HSH                    (0x10106550)

#define RESPOND_PORT_0_STALL_REG                                       (0x00006554)

  #define RESPOND_PORT_0_STALL_RSVD0_OFF                               ( 0)
  #define RESPOND_PORT_0_STALL_RSVD0_WID                               ( 4)
  #define RESPOND_PORT_0_STALL_RSVD0_MSK                               (0x0000000F)
  #define RESPOND_PORT_0_STALL_RSVD0_MIN                               (0)
  #define RESPOND_PORT_0_STALL_RSVD0_MAX                               (15) // 0x0000000F
  #define RESPOND_PORT_0_STALL_RSVD0_DEF                               (0x00000000)
  #define RESPOND_PORT_0_STALL_RSVD0_HSH                               (0x04006554)

  #define RESPOND_PORT_0_STALL_RSP_RD_CPL_STALL_OFF                    ( 4)
  #define RESPOND_PORT_0_STALL_RSP_RD_CPL_STALL_WID                    ( 1)
  #define RESPOND_PORT_0_STALL_RSP_RD_CPL_STALL_MSK                    (0x00000010)
  #define RESPOND_PORT_0_STALL_RSP_RD_CPL_STALL_MIN                    (0)
  #define RESPOND_PORT_0_STALL_RSP_RD_CPL_STALL_MAX                    (1) // 0x00000001
  #define RESPOND_PORT_0_STALL_RSP_RD_CPL_STALL_DEF                    (0x00000000)
  #define RESPOND_PORT_0_STALL_RSP_RD_CPL_STALL_HSH                    (0x01046554)

  #define RESPOND_PORT_0_STALL_RSVD1_OFF                               ( 5)
  #define RESPOND_PORT_0_STALL_RSVD1_WID                               ( 3)
  #define RESPOND_PORT_0_STALL_RSVD1_MSK                               (0x000000E0)
  #define RESPOND_PORT_0_STALL_RSVD1_MIN                               (0)
  #define RESPOND_PORT_0_STALL_RSVD1_MAX                               (7) // 0x00000007
  #define RESPOND_PORT_0_STALL_RSVD1_DEF                               (0x00000000)
  #define RESPOND_PORT_0_STALL_RSVD1_HSH                               (0x03056554)

  #define RESPOND_PORT_0_STALL_UNSTALL_COUNTER_VALUE_OFF               ( 8)
  #define RESPOND_PORT_0_STALL_UNSTALL_COUNTER_VALUE_WID               (16)
  #define RESPOND_PORT_0_STALL_UNSTALL_COUNTER_VALUE_MSK               (0x00FFFF00)
  #define RESPOND_PORT_0_STALL_UNSTALL_COUNTER_VALUE_MIN               (0)
  #define RESPOND_PORT_0_STALL_UNSTALL_COUNTER_VALUE_MAX               (65535) // 0x0000FFFF
  #define RESPOND_PORT_0_STALL_UNSTALL_COUNTER_VALUE_DEF               (0x00000000)
  #define RESPOND_PORT_0_STALL_UNSTALL_COUNTER_VALUE_HSH               (0x10086554)

#define RESPOND_PORT_0_RESERVED_0_REG                                  (0x00006558)

  #define RESPOND_PORT_0_RESERVED_0_RESERVED_OFF                       ( 0)
  #define RESPOND_PORT_0_RESERVED_0_RESERVED_WID                       (32)
  #define RESPOND_PORT_0_RESERVED_0_RESERVED_MSK                       (0xFFFFFFFF)
  #define RESPOND_PORT_0_RESERVED_0_RESERVED_MIN                       (0)
  #define RESPOND_PORT_0_RESERVED_0_RESERVED_MAX                       (4294967295) // 0xFFFFFFFF
  #define RESPOND_PORT_0_RESERVED_0_RESERVED_DEF                       (0x00000000)
  #define RESPOND_PORT_0_RESERVED_0_RESERVED_HSH                       (0x20006558)

#define RESPOND_PORT_0_RESERVED_1_REG                                  (0x0000655C)

  #define RESPOND_PORT_0_RESERVED_1_RESERVED_OFF                       ( 0)
  #define RESPOND_PORT_0_RESERVED_1_RESERVED_WID                       (32)
  #define RESPOND_PORT_0_RESERVED_1_RESERVED_MSK                       (0xFFFFFFFF)
  #define RESPOND_PORT_0_RESERVED_1_RESERVED_MIN                       (0)
  #define RESPOND_PORT_0_RESERVED_1_RESERVED_MAX                       (4294967295) // 0xFFFFFFFF
  #define RESPOND_PORT_0_RESERVED_1_RESERVED_DEF                       (0x00000000)
  #define RESPOND_PORT_0_RESERVED_1_RESERVED_HSH                       (0x2000655C)

#define RESPOND_PORT_0_RESERVED_2_REG                                  (0x00006560)

  #define RESPOND_PORT_0_RESERVED_2_RESERVED_OFF                       ( 0)
  #define RESPOND_PORT_0_RESERVED_2_RESERVED_WID                       (32)
  #define RESPOND_PORT_0_RESERVED_2_RESERVED_MSK                       (0xFFFFFFFF)
  #define RESPOND_PORT_0_RESERVED_2_RESERVED_MIN                       (0)
  #define RESPOND_PORT_0_RESERVED_2_RESERVED_MAX                       (4294967295) // 0xFFFFFFFF
  #define RESPOND_PORT_0_RESERVED_2_RESERVED_DEF                       (0x00000000)
  #define RESPOND_PORT_0_RESERVED_2_RESERVED_HSH                       (0x20006560)

#define RESPOND_PORT_0_ACCUM_REQ_OUT_REG                               (0x00006564)

  #define RESPOND_PORT_0_ACCUM_REQ_OUT_REQ_CMD_SUM_OFF                 ( 0)
  #define RESPOND_PORT_0_ACCUM_REQ_OUT_REQ_CMD_SUM_WID                 (16)
  #define RESPOND_PORT_0_ACCUM_REQ_OUT_REQ_CMD_SUM_MSK                 (0x0000FFFF)
  #define RESPOND_PORT_0_ACCUM_REQ_OUT_REQ_CMD_SUM_MIN                 (0)
  #define RESPOND_PORT_0_ACCUM_REQ_OUT_REQ_CMD_SUM_MAX                 (65535) // 0x0000FFFF
  #define RESPOND_PORT_0_ACCUM_REQ_OUT_REQ_CMD_SUM_DEF                 (0x00000000)
  #define RESPOND_PORT_0_ACCUM_REQ_OUT_REQ_CMD_SUM_HSH                 (0x10006564)

  #define RESPOND_PORT_0_ACCUM_REQ_OUT_REQ_DATA_SUM_OFF                (16)
  #define RESPOND_PORT_0_ACCUM_REQ_OUT_REQ_DATA_SUM_WID                (16)
  #define RESPOND_PORT_0_ACCUM_REQ_OUT_REQ_DATA_SUM_MSK                (0xFFFF0000)
  #define RESPOND_PORT_0_ACCUM_REQ_OUT_REQ_DATA_SUM_MIN                (0)
  #define RESPOND_PORT_0_ACCUM_REQ_OUT_REQ_DATA_SUM_MAX                (65535) // 0x0000FFFF
  #define RESPOND_PORT_0_ACCUM_REQ_OUT_REQ_DATA_SUM_DEF                (0x00000000)
  #define RESPOND_PORT_0_ACCUM_REQ_OUT_REQ_DATA_SUM_HSH                (0x10106564)

#define RESPOND_PORT_0_ACCUM_RD_CPL_IN_REG                             (0x00006568)

  #define RESPOND_PORT_0_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_OFF            ( 0)
  #define RESPOND_PORT_0_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_WID            (16)
  #define RESPOND_PORT_0_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_MSK            (0x0000FFFF)
  #define RESPOND_PORT_0_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_MIN            (0)
  #define RESPOND_PORT_0_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_MAX            (65535) // 0x0000FFFF
  #define RESPOND_PORT_0_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_DEF            (0x00000000)
  #define RESPOND_PORT_0_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_HSH            (0x10006568)

  #define RESPOND_PORT_0_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_OFF           (16)
  #define RESPOND_PORT_0_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_WID           (16)
  #define RESPOND_PORT_0_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_MSK           (0xFFFF0000)
  #define RESPOND_PORT_0_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_MIN           (0)
  #define RESPOND_PORT_0_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_MAX           (65535) // 0x0000FFFF
  #define RESPOND_PORT_0_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_DEF           (0x00000000)
  #define RESPOND_PORT_0_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_HSH           (0x10106568)

#define RESPOND_PORT_0_ACCUM_RSP_IN_REG                                (0x0000656C)

  #define RESPOND_PORT_0_ACCUM_RSP_IN_RSP_CMD_SUM_OFF                  ( 0)
  #define RESPOND_PORT_0_ACCUM_RSP_IN_RSP_CMD_SUM_WID                  (16)
  #define RESPOND_PORT_0_ACCUM_RSP_IN_RSP_CMD_SUM_MSK                  (0x0000FFFF)
  #define RESPOND_PORT_0_ACCUM_RSP_IN_RSP_CMD_SUM_MIN                  (0)
  #define RESPOND_PORT_0_ACCUM_RSP_IN_RSP_CMD_SUM_MAX                  (65535) // 0x0000FFFF
  #define RESPOND_PORT_0_ACCUM_RSP_IN_RSP_CMD_SUM_DEF                  (0x00000000)
  #define RESPOND_PORT_0_ACCUM_RSP_IN_RSP_CMD_SUM_HSH                  (0x1000656C)

  #define RESPOND_PORT_0_ACCUM_RSP_IN_RSVD_OFF                         (16)
  #define RESPOND_PORT_0_ACCUM_RSP_IN_RSVD_WID                         (16)
  #define RESPOND_PORT_0_ACCUM_RSP_IN_RSVD_MSK                         (0xFFFF0000)
  #define RESPOND_PORT_0_ACCUM_RSP_IN_RSVD_MIN                         (0)
  #define RESPOND_PORT_0_ACCUM_RSP_IN_RSVD_MAX                         (65535) // 0x0000FFFF
  #define RESPOND_PORT_0_ACCUM_RSP_IN_RSVD_DEF                         (0x00000000)
  #define RESPOND_PORT_0_ACCUM_RSP_IN_RSVD_HSH                         (0x1010656C)

#define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_REG                      (0x00006570)

  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_OFF      ( 0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_WID      ( 4)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_MSK      (0x0000000F)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_MIN      (0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_MAX      (15) // 0x0000000F
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_DEF      (0x00000003)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_HSH      (0x04006570)

  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RESERVED0_OFF          ( 4)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RESERVED0_WID          ( 4)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RESERVED0_MSK          (0x000000F0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RESERVED0_MIN          (0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RESERVED0_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RESERVED0_DEF          (0x00000000)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RESERVED0_HSH          (0x04046570)

  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_OFF   ( 8)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_WID   ( 4)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_MSK   (0x00000F00)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_MIN   (0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_MAX   (15) // 0x0000000F
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_DEF   (0x00000003)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_HSH   (0x04086570)

  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RESERVED1_OFF          (12)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RESERVED1_WID          ( 4)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RESERVED1_MSK          (0x0000F000)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RESERVED1_MIN          (0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RESERVED1_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RESERVED1_DEF          (0x00000000)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RESERVED1_HSH          (0x040C6570)

  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_OFF     (16)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_WID     ( 8)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_MSK     (0x00FF0000)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_MIN     (0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_MAX     (255) // 0x000000FF
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_DEF     (0x00000007)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_HSH     (0x08106570)

  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_OFF  (24)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_WID  ( 8)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_MSK  (0xFF000000)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_MIN  (0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_DEF  (0x00000004)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_HSH  (0x08186570)

#define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_REG                      (0x00006574)

  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_OFF      ( 0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_WID      ( 4)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_MSK      (0x0000000F)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_MIN      (0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_MAX      (15) // 0x0000000F
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_DEF      (0x00000003)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_HSH      (0x04006574)

  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RESERVED0_OFF          ( 4)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RESERVED0_WID          ( 4)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RESERVED0_MSK          (0x000000F0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RESERVED0_MIN          (0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RESERVED0_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RESERVED0_DEF          (0x00000000)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RESERVED0_HSH          (0x04046574)

  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_OFF   ( 8)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_WID   ( 4)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_MSK   (0x00000F00)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_MIN   (0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_MAX   (15) // 0x0000000F
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_DEF   (0x00000003)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_HSH   (0x04086574)

  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RESERVED1_OFF          (12)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RESERVED1_WID          ( 4)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RESERVED1_MSK          (0x0000F000)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RESERVED1_MIN          (0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RESERVED1_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RESERVED1_DEF          (0x00000000)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RESERVED1_HSH          (0x040C6574)

  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_OFF     (16)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_WID     ( 8)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_MSK     (0x00FF0000)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_MIN     (0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_MAX     (255) // 0x000000FF
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_DEF     (0x00000007)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_HSH     (0x08106574)

  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_OFF  (24)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_WID  ( 8)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_MSK  (0xFF000000)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_MIN  (0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_DEF  (0x00000004)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_HSH  (0x08186574)

#define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_REG                      (0x00006578)

  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_OFF      ( 0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_WID      ( 4)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_MSK      (0x0000000F)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_MIN      (0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_MAX      (15) // 0x0000000F
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_DEF      (0x00000003)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_HSH      (0x04006578)

  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RESERVED0_OFF          ( 4)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RESERVED0_WID          ( 4)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RESERVED0_MSK          (0x000000F0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RESERVED0_MIN          (0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RESERVED0_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RESERVED0_DEF          (0x00000000)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RESERVED0_HSH          (0x04046578)

  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_OFF   ( 8)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_WID   ( 4)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_MSK   (0x00000F00)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_MIN   (0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_MAX   (15) // 0x0000000F
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_DEF   (0x00000003)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_HSH   (0x04086578)

  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RESERVED1_OFF          (12)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RESERVED1_WID          ( 4)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RESERVED1_MSK          (0x0000F000)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RESERVED1_MIN          (0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RESERVED1_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RESERVED1_DEF          (0x00000000)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RESERVED1_HSH          (0x040C6578)

  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_OFF     (16)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_WID     ( 8)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_MSK     (0x00FF0000)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_MIN     (0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_MAX     (255) // 0x000000FF
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_DEF     (0x00000000)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_HSH     (0x08106578)

  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_OFF  (24)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_WID  ( 8)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_MSK  (0xFF000000)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_MIN  (0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_DEF  (0x00000000)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_HSH  (0x08186578)

#define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_REG                      (0x0000657C)

  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_OFF      ( 0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_WID      ( 4)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_MSK      (0x0000000F)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_MIN      (0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_MAX      (15) // 0x0000000F
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_DEF      (0x00000003)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_HSH      (0x0400657C)

  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RESERVED0_OFF          ( 4)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RESERVED0_WID          ( 4)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RESERVED0_MSK          (0x000000F0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RESERVED0_MIN          (0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RESERVED0_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RESERVED0_DEF          (0x00000000)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RESERVED0_HSH          (0x0404657C)

  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_OFF   ( 8)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_WID   ( 4)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_MSK   (0x00000F00)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_MIN   (0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_MAX   (15) // 0x0000000F
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_DEF   (0x00000003)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_HSH   (0x0408657C)

  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RESERVED1_OFF          (12)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RESERVED1_WID          ( 4)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RESERVED1_MSK          (0x0000F000)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RESERVED1_MIN          (0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RESERVED1_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RESERVED1_DEF          (0x00000000)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RESERVED1_HSH          (0x040C657C)

  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_OFF     (16)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_WID     ( 8)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_MSK     (0x00FF0000)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_MIN     (0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_MAX     (255) // 0x000000FF
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_DEF     (0x00000000)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_HSH     (0x0810657C)

  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_OFF  (24)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_WID  ( 8)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_MSK  (0xFF000000)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_MIN  (0)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_DEF  (0x00000000)
  #define RESPOND_PORT_1_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_HSH  (0x0818657C)

#define RESPOND_PORT_1_CPL_CONFIG_1_REG                                (0x00006580)

  #define RESPOND_PORT_1_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_OFF            ( 0)
  #define RESPOND_PORT_1_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_WID            ( 8)
  #define RESPOND_PORT_1_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_MSK            (0x000000FF)
  #define RESPOND_PORT_1_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_MIN            (0)
  #define RESPOND_PORT_1_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_MAX            (255) // 0x000000FF
  #define RESPOND_PORT_1_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_DEF            (0x00000008)
  #define RESPOND_PORT_1_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_HSH            (0x08006580)

  #define RESPOND_PORT_1_CPL_CONFIG_1_RSP_QUEUEDEPTH_OFF               ( 8)
  #define RESPOND_PORT_1_CPL_CONFIG_1_RSP_QUEUEDEPTH_WID               ( 8)
  #define RESPOND_PORT_1_CPL_CONFIG_1_RSP_QUEUEDEPTH_MSK               (0x0000FF00)
  #define RESPOND_PORT_1_CPL_CONFIG_1_RSP_QUEUEDEPTH_MIN               (0)
  #define RESPOND_PORT_1_CPL_CONFIG_1_RSP_QUEUEDEPTH_MAX               (255) // 0x000000FF
  #define RESPOND_PORT_1_CPL_CONFIG_1_RSP_QUEUEDEPTH_DEF               (0x0000000E)
  #define RESPOND_PORT_1_CPL_CONFIG_1_RSP_QUEUEDEPTH_HSH               (0x08086580)

  #define RESPOND_PORT_1_CPL_CONFIG_1_RESERVED1_OFF                    (16)
  #define RESPOND_PORT_1_CPL_CONFIG_1_RESERVED1_WID                    (16)
  #define RESPOND_PORT_1_CPL_CONFIG_1_RESERVED1_MSK                    (0xFFFF0000)
  #define RESPOND_PORT_1_CPL_CONFIG_1_RESERVED1_MIN                    (0)
  #define RESPOND_PORT_1_CPL_CONFIG_1_RESERVED1_MAX                    (65535) // 0x0000FFFF
  #define RESPOND_PORT_1_CPL_CONFIG_1_RESERVED1_DEF                    (0x00000000)
  #define RESPOND_PORT_1_CPL_CONFIG_1_RESERVED1_HSH                    (0x10106580)

#define RESPOND_PORT_1_STALL_REG                                       (0x00006584)

  #define RESPOND_PORT_1_STALL_RSVD0_OFF                               ( 0)
  #define RESPOND_PORT_1_STALL_RSVD0_WID                               ( 4)
  #define RESPOND_PORT_1_STALL_RSVD0_MSK                               (0x0000000F)
  #define RESPOND_PORT_1_STALL_RSVD0_MIN                               (0)
  #define RESPOND_PORT_1_STALL_RSVD0_MAX                               (15) // 0x0000000F
  #define RESPOND_PORT_1_STALL_RSVD0_DEF                               (0x00000000)
  #define RESPOND_PORT_1_STALL_RSVD0_HSH                               (0x04006584)

  #define RESPOND_PORT_1_STALL_RSP_RD_CPL_STALL_OFF                    ( 4)
  #define RESPOND_PORT_1_STALL_RSP_RD_CPL_STALL_WID                    ( 1)
  #define RESPOND_PORT_1_STALL_RSP_RD_CPL_STALL_MSK                    (0x00000010)
  #define RESPOND_PORT_1_STALL_RSP_RD_CPL_STALL_MIN                    (0)
  #define RESPOND_PORT_1_STALL_RSP_RD_CPL_STALL_MAX                    (1) // 0x00000001
  #define RESPOND_PORT_1_STALL_RSP_RD_CPL_STALL_DEF                    (0x00000000)
  #define RESPOND_PORT_1_STALL_RSP_RD_CPL_STALL_HSH                    (0x01046584)

  #define RESPOND_PORT_1_STALL_RSVD1_OFF                               ( 5)
  #define RESPOND_PORT_1_STALL_RSVD1_WID                               ( 3)
  #define RESPOND_PORT_1_STALL_RSVD1_MSK                               (0x000000E0)
  #define RESPOND_PORT_1_STALL_RSVD1_MIN                               (0)
  #define RESPOND_PORT_1_STALL_RSVD1_MAX                               (7) // 0x00000007
  #define RESPOND_PORT_1_STALL_RSVD1_DEF                               (0x00000000)
  #define RESPOND_PORT_1_STALL_RSVD1_HSH                               (0x03056584)

  #define RESPOND_PORT_1_STALL_UNSTALL_COUNTER_VALUE_OFF               ( 8)
  #define RESPOND_PORT_1_STALL_UNSTALL_COUNTER_VALUE_WID               (16)
  #define RESPOND_PORT_1_STALL_UNSTALL_COUNTER_VALUE_MSK               (0x00FFFF00)
  #define RESPOND_PORT_1_STALL_UNSTALL_COUNTER_VALUE_MIN               (0)
  #define RESPOND_PORT_1_STALL_UNSTALL_COUNTER_VALUE_MAX               (65535) // 0x0000FFFF
  #define RESPOND_PORT_1_STALL_UNSTALL_COUNTER_VALUE_DEF               (0x00000000)
  #define RESPOND_PORT_1_STALL_UNSTALL_COUNTER_VALUE_HSH               (0x10086584)

#define RESPOND_PORT_1_RESERVED_0_REG                                  (0x00006588)

  #define RESPOND_PORT_1_RESERVED_0_RESERVED_OFF                       ( 0)
  #define RESPOND_PORT_1_RESERVED_0_RESERVED_WID                       (32)
  #define RESPOND_PORT_1_RESERVED_0_RESERVED_MSK                       (0xFFFFFFFF)
  #define RESPOND_PORT_1_RESERVED_0_RESERVED_MIN                       (0)
  #define RESPOND_PORT_1_RESERVED_0_RESERVED_MAX                       (4294967295) // 0xFFFFFFFF
  #define RESPOND_PORT_1_RESERVED_0_RESERVED_DEF                       (0x00000000)
  #define RESPOND_PORT_1_RESERVED_0_RESERVED_HSH                       (0x20006588)

#define RESPOND_PORT_1_RESERVED_1_REG                                  (0x0000658C)

  #define RESPOND_PORT_1_RESERVED_1_RESERVED_OFF                       ( 0)
  #define RESPOND_PORT_1_RESERVED_1_RESERVED_WID                       (32)
  #define RESPOND_PORT_1_RESERVED_1_RESERVED_MSK                       (0xFFFFFFFF)
  #define RESPOND_PORT_1_RESERVED_1_RESERVED_MIN                       (0)
  #define RESPOND_PORT_1_RESERVED_1_RESERVED_MAX                       (4294967295) // 0xFFFFFFFF
  #define RESPOND_PORT_1_RESERVED_1_RESERVED_DEF                       (0x00000000)
  #define RESPOND_PORT_1_RESERVED_1_RESERVED_HSH                       (0x2000658C)

#define RESPOND_PORT_1_RESERVED_2_REG                                  (0x00006590)

  #define RESPOND_PORT_1_RESERVED_2_RESERVED_OFF                       ( 0)
  #define RESPOND_PORT_1_RESERVED_2_RESERVED_WID                       (32)
  #define RESPOND_PORT_1_RESERVED_2_RESERVED_MSK                       (0xFFFFFFFF)
  #define RESPOND_PORT_1_RESERVED_2_RESERVED_MIN                       (0)
  #define RESPOND_PORT_1_RESERVED_2_RESERVED_MAX                       (4294967295) // 0xFFFFFFFF
  #define RESPOND_PORT_1_RESERVED_2_RESERVED_DEF                       (0x00000000)
  #define RESPOND_PORT_1_RESERVED_2_RESERVED_HSH                       (0x20006590)

#define RESPOND_PORT_1_ACCUM_REQ_OUT_REG                               (0x00006594)

  #define RESPOND_PORT_1_ACCUM_REQ_OUT_REQ_CMD_SUM_OFF                 ( 0)
  #define RESPOND_PORT_1_ACCUM_REQ_OUT_REQ_CMD_SUM_WID                 (16)
  #define RESPOND_PORT_1_ACCUM_REQ_OUT_REQ_CMD_SUM_MSK                 (0x0000FFFF)
  #define RESPOND_PORT_1_ACCUM_REQ_OUT_REQ_CMD_SUM_MIN                 (0)
  #define RESPOND_PORT_1_ACCUM_REQ_OUT_REQ_CMD_SUM_MAX                 (65535) // 0x0000FFFF
  #define RESPOND_PORT_1_ACCUM_REQ_OUT_REQ_CMD_SUM_DEF                 (0x00000000)
  #define RESPOND_PORT_1_ACCUM_REQ_OUT_REQ_CMD_SUM_HSH                 (0x10006594)

  #define RESPOND_PORT_1_ACCUM_REQ_OUT_REQ_DATA_SUM_OFF                (16)
  #define RESPOND_PORT_1_ACCUM_REQ_OUT_REQ_DATA_SUM_WID                (16)
  #define RESPOND_PORT_1_ACCUM_REQ_OUT_REQ_DATA_SUM_MSK                (0xFFFF0000)
  #define RESPOND_PORT_1_ACCUM_REQ_OUT_REQ_DATA_SUM_MIN                (0)
  #define RESPOND_PORT_1_ACCUM_REQ_OUT_REQ_DATA_SUM_MAX                (65535) // 0x0000FFFF
  #define RESPOND_PORT_1_ACCUM_REQ_OUT_REQ_DATA_SUM_DEF                (0x00000000)
  #define RESPOND_PORT_1_ACCUM_REQ_OUT_REQ_DATA_SUM_HSH                (0x10106594)

#define RESPOND_PORT_1_ACCUM_RD_CPL_IN_REG                             (0x00006598)

  #define RESPOND_PORT_1_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_OFF            ( 0)
  #define RESPOND_PORT_1_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_WID            (16)
  #define RESPOND_PORT_1_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_MSK            (0x0000FFFF)
  #define RESPOND_PORT_1_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_MIN            (0)
  #define RESPOND_PORT_1_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_MAX            (65535) // 0x0000FFFF
  #define RESPOND_PORT_1_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_DEF            (0x00000000)
  #define RESPOND_PORT_1_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_HSH            (0x10006598)

  #define RESPOND_PORT_1_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_OFF           (16)
  #define RESPOND_PORT_1_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_WID           (16)
  #define RESPOND_PORT_1_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_MSK           (0xFFFF0000)
  #define RESPOND_PORT_1_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_MIN           (0)
  #define RESPOND_PORT_1_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_MAX           (65535) // 0x0000FFFF
  #define RESPOND_PORT_1_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_DEF           (0x00000000)
  #define RESPOND_PORT_1_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_HSH           (0x10106598)

#define RESPOND_PORT_1_ACCUM_RSP_IN_REG                                (0x0000659C)

  #define RESPOND_PORT_1_ACCUM_RSP_IN_RSP_CMD_SUM_OFF                  ( 0)
  #define RESPOND_PORT_1_ACCUM_RSP_IN_RSP_CMD_SUM_WID                  (16)
  #define RESPOND_PORT_1_ACCUM_RSP_IN_RSP_CMD_SUM_MSK                  (0x0000FFFF)
  #define RESPOND_PORT_1_ACCUM_RSP_IN_RSP_CMD_SUM_MIN                  (0)
  #define RESPOND_PORT_1_ACCUM_RSP_IN_RSP_CMD_SUM_MAX                  (65535) // 0x0000FFFF
  #define RESPOND_PORT_1_ACCUM_RSP_IN_RSP_CMD_SUM_DEF                  (0x00000000)
  #define RESPOND_PORT_1_ACCUM_RSP_IN_RSP_CMD_SUM_HSH                  (0x1000659C)

  #define RESPOND_PORT_1_ACCUM_RSP_IN_RSVD_OFF                         (16)
  #define RESPOND_PORT_1_ACCUM_RSP_IN_RSVD_WID                         (16)
  #define RESPOND_PORT_1_ACCUM_RSP_IN_RSVD_MSK                         (0xFFFF0000)
  #define RESPOND_PORT_1_ACCUM_RSP_IN_RSVD_MIN                         (0)
  #define RESPOND_PORT_1_ACCUM_RSP_IN_RSVD_MAX                         (65535) // 0x0000FFFF
  #define RESPOND_PORT_1_ACCUM_RSP_IN_RSVD_DEF                         (0x00000000)
  #define RESPOND_PORT_1_ACCUM_RSP_IN_RSVD_HSH                         (0x1010659C)

#define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_REG                      (0x000065A0)

  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_OFF      ( 0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_WID      ( 4)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_MSK      (0x0000000F)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_MIN      (0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_MAX      (15) // 0x0000000F
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_DEF      (0x00000003)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_HSH      (0x040065A0)

  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED0_OFF          ( 4)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED0_WID          ( 4)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED0_MSK          (0x000000F0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED0_MIN          (0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED0_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED0_DEF          (0x00000000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED0_HSH          (0x040465A0)

  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_OFF   ( 8)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_WID   ( 4)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_MSK   (0x00000F00)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_MIN   (0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_MAX   (15) // 0x0000000F
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_DEF   (0x00000003)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_HSH   (0x040865A0)

  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED1_OFF          (12)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED1_WID          ( 4)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED1_MSK          (0x0000F000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED1_MIN          (0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED1_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED1_DEF          (0x00000000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RESERVED1_HSH          (0x040C65A0)

  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_OFF     (16)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_WID     ( 8)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_MSK     (0x00FF0000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_MIN     (0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_MAX     (255) // 0x000000FF
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_DEF     (0x00000000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_HSH     (0x081065A0)

  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_OFF  (24)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_WID  ( 8)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_MSK  (0xFF000000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_MIN  (0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_DEF  (0x00000000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_HSH  (0x081865A0)

#define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_REG                      (0x000065A4)

  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_OFF      ( 0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_WID      ( 4)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_MSK      (0x0000000F)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_MIN      (0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_MAX      (15) // 0x0000000F
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_DEF      (0x00000003)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_HSH      (0x040065A4)

  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RESERVED0_OFF          ( 4)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RESERVED0_WID          ( 4)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RESERVED0_MSK          (0x000000F0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RESERVED0_MIN          (0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RESERVED0_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RESERVED0_DEF          (0x00000000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RESERVED0_HSH          (0x040465A4)

  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_OFF   ( 8)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_WID   ( 4)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_MSK   (0x00000F00)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_MIN   (0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_MAX   (15) // 0x0000000F
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_DEF   (0x00000003)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_HSH   (0x040865A4)

  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RESERVED1_OFF          (12)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RESERVED1_WID          ( 4)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RESERVED1_MSK          (0x0000F000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RESERVED1_MIN          (0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RESERVED1_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RESERVED1_DEF          (0x00000000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RESERVED1_HSH          (0x040C65A4)

  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_OFF     (16)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_WID     ( 8)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_MSK     (0x00FF0000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_MIN     (0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_MAX     (255) // 0x000000FF
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_DEF     (0x00000000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_HSH     (0x081065A4)

  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_OFF  (24)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_WID  ( 8)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_MSK  (0xFF000000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_MIN  (0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_DEF  (0x00000000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_HSH  (0x081865A4)

#define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_REG                      (0x000065A8)

  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_OFF      ( 0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_WID      ( 4)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_MSK      (0x0000000F)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_MIN      (0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_MAX      (15) // 0x0000000F
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_DEF      (0x00000003)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_HSH      (0x040065A8)

  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RESERVED0_OFF          ( 4)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RESERVED0_WID          ( 4)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RESERVED0_MSK          (0x000000F0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RESERVED0_MIN          (0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RESERVED0_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RESERVED0_DEF          (0x00000000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RESERVED0_HSH          (0x040465A8)

  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_OFF   ( 8)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_WID   ( 4)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_MSK   (0x00000F00)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_MIN   (0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_MAX   (15) // 0x0000000F
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_DEF   (0x00000003)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_HSH   (0x040865A8)

  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RESERVED1_OFF          (12)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RESERVED1_WID          ( 4)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RESERVED1_MSK          (0x0000F000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RESERVED1_MIN          (0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RESERVED1_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RESERVED1_DEF          (0x00000000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RESERVED1_HSH          (0x040C65A8)

  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_OFF     (16)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_WID     ( 8)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_MSK     (0x00FF0000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_MIN     (0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_MAX     (255) // 0x000000FF
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_DEF     (0x00000000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_HSH     (0x081065A8)

  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_OFF  (24)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_WID  ( 8)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_MSK  (0xFF000000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_MIN  (0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_DEF  (0x00000000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_HSH  (0x081865A8)

#define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_REG                      (0x000065AC)

  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_OFF      ( 0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_WID      ( 4)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_MSK      (0x0000000F)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_MIN      (0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_MAX      (15) // 0x0000000F
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_DEF      (0x00000003)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_HSH      (0x040065AC)

  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RESERVED0_OFF          ( 4)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RESERVED0_WID          ( 4)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RESERVED0_MSK          (0x000000F0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RESERVED0_MIN          (0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RESERVED0_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RESERVED0_DEF          (0x00000000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RESERVED0_HSH          (0x040465AC)

  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_OFF   ( 8)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_WID   ( 4)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_MSK   (0x00000F00)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_MIN   (0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_MAX   (15) // 0x0000000F
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_DEF   (0x00000003)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_HSH   (0x040865AC)

  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RESERVED1_OFF          (12)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RESERVED1_WID          ( 4)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RESERVED1_MSK          (0x0000F000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RESERVED1_MIN          (0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RESERVED1_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RESERVED1_DEF          (0x00000000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RESERVED1_HSH          (0x040C65AC)

  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_OFF     (16)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_WID     ( 8)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_MSK     (0x00FF0000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_MIN     (0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_MAX     (255) // 0x000000FF
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_DEF     (0x00000000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_HSH     (0x081065AC)

  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_OFF  (24)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_WID  ( 8)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_MSK  (0xFF000000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_MIN  (0)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_DEF  (0x00000000)
  #define RESPOND_PORT_2_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_HSH  (0x081865AC)

#define RESPOND_PORT_2_CPL_CONFIG_1_REG                                (0x000065B0)

  #define RESPOND_PORT_2_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_OFF            ( 0)
  #define RESPOND_PORT_2_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_WID            ( 8)
  #define RESPOND_PORT_2_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_MSK            (0x000000FF)
  #define RESPOND_PORT_2_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_MIN            (0)
  #define RESPOND_PORT_2_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_MAX            (255) // 0x000000FF
  #define RESPOND_PORT_2_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_DEF            (0x00000000)
  #define RESPOND_PORT_2_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_HSH            (0x080065B0)

  #define RESPOND_PORT_2_CPL_CONFIG_1_RSP_QUEUEDEPTH_OFF               ( 8)
  #define RESPOND_PORT_2_CPL_CONFIG_1_RSP_QUEUEDEPTH_WID               ( 8)
  #define RESPOND_PORT_2_CPL_CONFIG_1_RSP_QUEUEDEPTH_MSK               (0x0000FF00)
  #define RESPOND_PORT_2_CPL_CONFIG_1_RSP_QUEUEDEPTH_MIN               (0)
  #define RESPOND_PORT_2_CPL_CONFIG_1_RSP_QUEUEDEPTH_MAX               (255) // 0x000000FF
  #define RESPOND_PORT_2_CPL_CONFIG_1_RSP_QUEUEDEPTH_DEF               (0x00000000)
  #define RESPOND_PORT_2_CPL_CONFIG_1_RSP_QUEUEDEPTH_HSH               (0x080865B0)

  #define RESPOND_PORT_2_CPL_CONFIG_1_RESERVED1_OFF                    (16)
  #define RESPOND_PORT_2_CPL_CONFIG_1_RESERVED1_WID                    (16)
  #define RESPOND_PORT_2_CPL_CONFIG_1_RESERVED1_MSK                    (0xFFFF0000)
  #define RESPOND_PORT_2_CPL_CONFIG_1_RESERVED1_MIN                    (0)
  #define RESPOND_PORT_2_CPL_CONFIG_1_RESERVED1_MAX                    (65535) // 0x0000FFFF
  #define RESPOND_PORT_2_CPL_CONFIG_1_RESERVED1_DEF                    (0x00000000)
  #define RESPOND_PORT_2_CPL_CONFIG_1_RESERVED1_HSH                    (0x101065B0)

#define RESPOND_PORT_2_STALL_REG                                       (0x000065B4)

  #define RESPOND_PORT_2_STALL_RSVD0_OFF                               ( 0)
  #define RESPOND_PORT_2_STALL_RSVD0_WID                               ( 4)
  #define RESPOND_PORT_2_STALL_RSVD0_MSK                               (0x0000000F)
  #define RESPOND_PORT_2_STALL_RSVD0_MIN                               (0)
  #define RESPOND_PORT_2_STALL_RSVD0_MAX                               (15) // 0x0000000F
  #define RESPOND_PORT_2_STALL_RSVD0_DEF                               (0x00000000)
  #define RESPOND_PORT_2_STALL_RSVD0_HSH                               (0x040065B4)

  #define RESPOND_PORT_2_STALL_RSP_RD_CPL_STALL_OFF                    ( 4)
  #define RESPOND_PORT_2_STALL_RSP_RD_CPL_STALL_WID                    ( 1)
  #define RESPOND_PORT_2_STALL_RSP_RD_CPL_STALL_MSK                    (0x00000010)
  #define RESPOND_PORT_2_STALL_RSP_RD_CPL_STALL_MIN                    (0)
  #define RESPOND_PORT_2_STALL_RSP_RD_CPL_STALL_MAX                    (1) // 0x00000001
  #define RESPOND_PORT_2_STALL_RSP_RD_CPL_STALL_DEF                    (0x00000000)
  #define RESPOND_PORT_2_STALL_RSP_RD_CPL_STALL_HSH                    (0x010465B4)

  #define RESPOND_PORT_2_STALL_RSVD1_OFF                               ( 5)
  #define RESPOND_PORT_2_STALL_RSVD1_WID                               ( 3)
  #define RESPOND_PORT_2_STALL_RSVD1_MSK                               (0x000000E0)
  #define RESPOND_PORT_2_STALL_RSVD1_MIN                               (0)
  #define RESPOND_PORT_2_STALL_RSVD1_MAX                               (7) // 0x00000007
  #define RESPOND_PORT_2_STALL_RSVD1_DEF                               (0x00000000)
  #define RESPOND_PORT_2_STALL_RSVD1_HSH                               (0x030565B4)

  #define RESPOND_PORT_2_STALL_UNSTALL_COUNTER_VALUE_OFF               ( 8)
  #define RESPOND_PORT_2_STALL_UNSTALL_COUNTER_VALUE_WID               (16)
  #define RESPOND_PORT_2_STALL_UNSTALL_COUNTER_VALUE_MSK               (0x00FFFF00)
  #define RESPOND_PORT_2_STALL_UNSTALL_COUNTER_VALUE_MIN               (0)
  #define RESPOND_PORT_2_STALL_UNSTALL_COUNTER_VALUE_MAX               (65535) // 0x0000FFFF
  #define RESPOND_PORT_2_STALL_UNSTALL_COUNTER_VALUE_DEF               (0x00000000)
  #define RESPOND_PORT_2_STALL_UNSTALL_COUNTER_VALUE_HSH               (0x100865B4)

#define RESPOND_PORT_2_RESERVED_0_REG                                  (0x000065B8)

  #define RESPOND_PORT_2_RESERVED_0_RESERVED_OFF                       ( 0)
  #define RESPOND_PORT_2_RESERVED_0_RESERVED_WID                       (32)
  #define RESPOND_PORT_2_RESERVED_0_RESERVED_MSK                       (0xFFFFFFFF)
  #define RESPOND_PORT_2_RESERVED_0_RESERVED_MIN                       (0)
  #define RESPOND_PORT_2_RESERVED_0_RESERVED_MAX                       (4294967295) // 0xFFFFFFFF
  #define RESPOND_PORT_2_RESERVED_0_RESERVED_DEF                       (0x00000000)
  #define RESPOND_PORT_2_RESERVED_0_RESERVED_HSH                       (0x200065B8)

#define RESPOND_PORT_2_RESERVED_1_REG                                  (0x000065BC)

  #define RESPOND_PORT_2_RESERVED_1_RESERVED_OFF                       ( 0)
  #define RESPOND_PORT_2_RESERVED_1_RESERVED_WID                       (32)
  #define RESPOND_PORT_2_RESERVED_1_RESERVED_MSK                       (0xFFFFFFFF)
  #define RESPOND_PORT_2_RESERVED_1_RESERVED_MIN                       (0)
  #define RESPOND_PORT_2_RESERVED_1_RESERVED_MAX                       (4294967295) // 0xFFFFFFFF
  #define RESPOND_PORT_2_RESERVED_1_RESERVED_DEF                       (0x00000000)
  #define RESPOND_PORT_2_RESERVED_1_RESERVED_HSH                       (0x200065BC)

#define RESPOND_PORT_2_RESERVED_2_REG                                  (0x000065C0)

  #define RESPOND_PORT_2_RESERVED_2_RESERVED_OFF                       ( 0)
  #define RESPOND_PORT_2_RESERVED_2_RESERVED_WID                       (32)
  #define RESPOND_PORT_2_RESERVED_2_RESERVED_MSK                       (0xFFFFFFFF)
  #define RESPOND_PORT_2_RESERVED_2_RESERVED_MIN                       (0)
  #define RESPOND_PORT_2_RESERVED_2_RESERVED_MAX                       (4294967295) // 0xFFFFFFFF
  #define RESPOND_PORT_2_RESERVED_2_RESERVED_DEF                       (0x00000000)
  #define RESPOND_PORT_2_RESERVED_2_RESERVED_HSH                       (0x200065C0)

#define RESPOND_PORT_2_ACCUM_REQ_OUT_REG                               (0x000065C4)

  #define RESPOND_PORT_2_ACCUM_REQ_OUT_REQ_CMD_SUM_OFF                 ( 0)
  #define RESPOND_PORT_2_ACCUM_REQ_OUT_REQ_CMD_SUM_WID                 (16)
  #define RESPOND_PORT_2_ACCUM_REQ_OUT_REQ_CMD_SUM_MSK                 (0x0000FFFF)
  #define RESPOND_PORT_2_ACCUM_REQ_OUT_REQ_CMD_SUM_MIN                 (0)
  #define RESPOND_PORT_2_ACCUM_REQ_OUT_REQ_CMD_SUM_MAX                 (65535) // 0x0000FFFF
  #define RESPOND_PORT_2_ACCUM_REQ_OUT_REQ_CMD_SUM_DEF                 (0x00000000)
  #define RESPOND_PORT_2_ACCUM_REQ_OUT_REQ_CMD_SUM_HSH                 (0x100065C4)

  #define RESPOND_PORT_2_ACCUM_REQ_OUT_REQ_DATA_SUM_OFF                (16)
  #define RESPOND_PORT_2_ACCUM_REQ_OUT_REQ_DATA_SUM_WID                (16)
  #define RESPOND_PORT_2_ACCUM_REQ_OUT_REQ_DATA_SUM_MSK                (0xFFFF0000)
  #define RESPOND_PORT_2_ACCUM_REQ_OUT_REQ_DATA_SUM_MIN                (0)
  #define RESPOND_PORT_2_ACCUM_REQ_OUT_REQ_DATA_SUM_MAX                (65535) // 0x0000FFFF
  #define RESPOND_PORT_2_ACCUM_REQ_OUT_REQ_DATA_SUM_DEF                (0x00000000)
  #define RESPOND_PORT_2_ACCUM_REQ_OUT_REQ_DATA_SUM_HSH                (0x101065C4)

#define RESPOND_PORT_2_ACCUM_RD_CPL_IN_REG                             (0x000065C8)

  #define RESPOND_PORT_2_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_OFF            ( 0)
  #define RESPOND_PORT_2_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_WID            (16)
  #define RESPOND_PORT_2_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_MSK            (0x0000FFFF)
  #define RESPOND_PORT_2_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_MIN            (0)
  #define RESPOND_PORT_2_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_MAX            (65535) // 0x0000FFFF
  #define RESPOND_PORT_2_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_DEF            (0x00000000)
  #define RESPOND_PORT_2_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_HSH            (0x100065C8)

  #define RESPOND_PORT_2_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_OFF           (16)
  #define RESPOND_PORT_2_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_WID           (16)
  #define RESPOND_PORT_2_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_MSK           (0xFFFF0000)
  #define RESPOND_PORT_2_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_MIN           (0)
  #define RESPOND_PORT_2_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_MAX           (65535) // 0x0000FFFF
  #define RESPOND_PORT_2_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_DEF           (0x00000000)
  #define RESPOND_PORT_2_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_HSH           (0x101065C8)

#define RESPOND_PORT_2_ACCUM_RSP_IN_REG                                (0x000065CC)

  #define RESPOND_PORT_2_ACCUM_RSP_IN_RSP_CMD_SUM_OFF                  ( 0)
  #define RESPOND_PORT_2_ACCUM_RSP_IN_RSP_CMD_SUM_WID                  (16)
  #define RESPOND_PORT_2_ACCUM_RSP_IN_RSP_CMD_SUM_MSK                  (0x0000FFFF)
  #define RESPOND_PORT_2_ACCUM_RSP_IN_RSP_CMD_SUM_MIN                  (0)
  #define RESPOND_PORT_2_ACCUM_RSP_IN_RSP_CMD_SUM_MAX                  (65535) // 0x0000FFFF
  #define RESPOND_PORT_2_ACCUM_RSP_IN_RSP_CMD_SUM_DEF                  (0x00000000)
  #define RESPOND_PORT_2_ACCUM_RSP_IN_RSP_CMD_SUM_HSH                  (0x100065CC)

  #define RESPOND_PORT_2_ACCUM_RSP_IN_RSVD_OFF                         (16)
  #define RESPOND_PORT_2_ACCUM_RSP_IN_RSVD_WID                         (16)
  #define RESPOND_PORT_2_ACCUM_RSP_IN_RSVD_MSK                         (0xFFFF0000)
  #define RESPOND_PORT_2_ACCUM_RSP_IN_RSVD_MIN                         (0)
  #define RESPOND_PORT_2_ACCUM_RSP_IN_RSVD_MAX                         (65535) // 0x0000FFFF
  #define RESPOND_PORT_2_ACCUM_RSP_IN_RSVD_DEF                         (0x00000000)
  #define RESPOND_PORT_2_ACCUM_RSP_IN_RSVD_HSH                         (0x101065CC)

#define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_REG                      (0x000065D0)

  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_OFF      ( 0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_WID      ( 4)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_MSK      (0x0000000F)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_MIN      (0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_MAX      (15) // 0x0000000F
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_DEF      (0x00000003)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RSP_PARK_SIZE_HSH      (0x040065D0)

  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED0_OFF          ( 4)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED0_WID          ( 4)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED0_MSK          (0x000000F0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED0_MIN          (0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED0_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED0_DEF          (0x00000000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED0_HSH          (0x040465D0)

  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_OFF   ( 8)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_WID   ( 4)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_MSK   (0x00000F00)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_MIN   (0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_MAX   (15) // 0x0000000F
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_DEF   (0x00000003)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_PARK_SIZE_HSH   (0x040865D0)

  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED1_OFF          (12)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED1_WID          ( 4)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED1_MSK          (0x0000F000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED1_MIN          (0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED1_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED1_DEF          (0x00000000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RESERVED1_HSH          (0x040C65D0)

  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_OFF     (16)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_WID     ( 8)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_MSK     (0x00FF0000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_MIN     (0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_MAX     (255) // 0x000000FF
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_DEF     (0x00000000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RSP_MAX_CREDIT_HSH     (0x081065D0)

  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_OFF  (24)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_WID  ( 8)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_MSK  (0xFF000000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_MIN  (0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_DEF  (0x00000000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_0_RD_CPL_MAX_CREDIT_HSH  (0x081865D0)

#define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_REG                      (0x000065D4)

  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_OFF      ( 0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_WID      ( 4)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_MSK      (0x0000000F)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_MIN      (0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_MAX      (15) // 0x0000000F
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_DEF      (0x00000003)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RSP_PARK_SIZE_HSH      (0x040065D4)

  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RESERVED0_OFF          ( 4)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RESERVED0_WID          ( 4)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RESERVED0_MSK          (0x000000F0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RESERVED0_MIN          (0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RESERVED0_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RESERVED0_DEF          (0x00000000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RESERVED0_HSH          (0x040465D4)

  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_OFF   ( 8)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_WID   ( 4)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_MSK   (0x00000F00)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_MIN   (0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_MAX   (15) // 0x0000000F
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_DEF   (0x00000003)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RD_CPL_PARK_SIZE_HSH   (0x040865D4)

  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RESERVED1_OFF          (12)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RESERVED1_WID          ( 4)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RESERVED1_MSK          (0x0000F000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RESERVED1_MIN          (0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RESERVED1_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RESERVED1_DEF          (0x00000000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RESERVED1_HSH          (0x040C65D4)

  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_OFF     (16)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_WID     ( 8)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_MSK     (0x00FF0000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_MIN     (0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_MAX     (255) // 0x000000FF
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_DEF     (0x00000000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RSP_MAX_CREDIT_HSH     (0x081065D4)

  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_OFF  (24)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_WID  ( 8)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_MSK  (0xFF000000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_MIN  (0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_DEF  (0x00000000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_1_RD_CPL_MAX_CREDIT_HSH  (0x081865D4)

#define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_REG                      (0x000065D8)

  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_OFF      ( 0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_WID      ( 4)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_MSK      (0x0000000F)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_MIN      (0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_MAX      (15) // 0x0000000F
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_DEF      (0x00000003)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RSP_PARK_SIZE_HSH      (0x040065D8)

  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RESERVED0_OFF          ( 4)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RESERVED0_WID          ( 4)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RESERVED0_MSK          (0x000000F0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RESERVED0_MIN          (0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RESERVED0_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RESERVED0_DEF          (0x00000000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RESERVED0_HSH          (0x040465D8)

  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_OFF   ( 8)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_WID   ( 4)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_MSK   (0x00000F00)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_MIN   (0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_MAX   (15) // 0x0000000F
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_DEF   (0x00000003)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RD_CPL_PARK_SIZE_HSH   (0x040865D8)

  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RESERVED1_OFF          (12)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RESERVED1_WID          ( 4)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RESERVED1_MSK          (0x0000F000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RESERVED1_MIN          (0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RESERVED1_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RESERVED1_DEF          (0x00000000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RESERVED1_HSH          (0x040C65D8)

  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_OFF     (16)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_WID     ( 8)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_MSK     (0x00FF0000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_MIN     (0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_MAX     (255) // 0x000000FF
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_DEF     (0x00000000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RSP_MAX_CREDIT_HSH     (0x081065D8)

  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_OFF  (24)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_WID  ( 8)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_MSK  (0xFF000000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_MIN  (0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_DEF  (0x00000000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_2_RD_CPL_MAX_CREDIT_HSH  (0x081865D8)

#define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_REG                      (0x000065DC)

  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_OFF      ( 0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_WID      ( 4)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_MSK      (0x0000000F)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_MIN      (0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_MAX      (15) // 0x0000000F
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_DEF      (0x00000003)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RSP_PARK_SIZE_HSH      (0x040065DC)

  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RESERVED0_OFF          ( 4)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RESERVED0_WID          ( 4)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RESERVED0_MSK          (0x000000F0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RESERVED0_MIN          (0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RESERVED0_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RESERVED0_DEF          (0x00000000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RESERVED0_HSH          (0x040465DC)

  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_OFF   ( 8)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_WID   ( 4)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_MSK   (0x00000F00)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_MIN   (0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_MAX   (15) // 0x0000000F
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_DEF   (0x00000003)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RD_CPL_PARK_SIZE_HSH   (0x040865DC)

  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RESERVED1_OFF          (12)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RESERVED1_WID          ( 4)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RESERVED1_MSK          (0x0000F000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RESERVED1_MIN          (0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RESERVED1_MAX          (15) // 0x0000000F
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RESERVED1_DEF          (0x00000000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RESERVED1_HSH          (0x040C65DC)

  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_OFF     (16)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_WID     ( 8)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_MSK     (0x00FF0000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_MIN     (0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_MAX     (255) // 0x000000FF
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_DEF     (0x00000000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RSP_MAX_CREDIT_HSH     (0x081065DC)

  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_OFF  (24)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_WID  ( 8)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_MSK  (0xFF000000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_MIN  (0)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_MAX  (255) // 0x000000FF
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_DEF  (0x00000000)
  #define RESPOND_PORT_3_CPL_CONFIG_0_CHANNEL_3_RD_CPL_MAX_CREDIT_HSH  (0x081865DC)

#define RESPOND_PORT_3_CPL_CONFIG_1_REG                                (0x000065E0)

  #define RESPOND_PORT_3_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_OFF            ( 0)
  #define RESPOND_PORT_3_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_WID            ( 8)
  #define RESPOND_PORT_3_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_MSK            (0x000000FF)
  #define RESPOND_PORT_3_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_MIN            (0)
  #define RESPOND_PORT_3_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_MAX            (255) // 0x000000FF
  #define RESPOND_PORT_3_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_DEF            (0x00000000)
  #define RESPOND_PORT_3_CPL_CONFIG_1_RD_CPL_QUEUEDEPTH_HSH            (0x080065E0)

  #define RESPOND_PORT_3_CPL_CONFIG_1_RSP_QUEUEDEPTH_OFF               ( 8)
  #define RESPOND_PORT_3_CPL_CONFIG_1_RSP_QUEUEDEPTH_WID               ( 8)
  #define RESPOND_PORT_3_CPL_CONFIG_1_RSP_QUEUEDEPTH_MSK               (0x0000FF00)
  #define RESPOND_PORT_3_CPL_CONFIG_1_RSP_QUEUEDEPTH_MIN               (0)
  #define RESPOND_PORT_3_CPL_CONFIG_1_RSP_QUEUEDEPTH_MAX               (255) // 0x000000FF
  #define RESPOND_PORT_3_CPL_CONFIG_1_RSP_QUEUEDEPTH_DEF               (0x00000000)
  #define RESPOND_PORT_3_CPL_CONFIG_1_RSP_QUEUEDEPTH_HSH               (0x080865E0)

  #define RESPOND_PORT_3_CPL_CONFIG_1_RESERVED1_OFF                    (16)
  #define RESPOND_PORT_3_CPL_CONFIG_1_RESERVED1_WID                    (16)
  #define RESPOND_PORT_3_CPL_CONFIG_1_RESERVED1_MSK                    (0xFFFF0000)
  #define RESPOND_PORT_3_CPL_CONFIG_1_RESERVED1_MIN                    (0)
  #define RESPOND_PORT_3_CPL_CONFIG_1_RESERVED1_MAX                    (65535) // 0x0000FFFF
  #define RESPOND_PORT_3_CPL_CONFIG_1_RESERVED1_DEF                    (0x00000000)
  #define RESPOND_PORT_3_CPL_CONFIG_1_RESERVED1_HSH                    (0x101065E0)

#define RESPOND_PORT_3_STALL_REG                                       (0x000065E4)

  #define RESPOND_PORT_3_STALL_RSVD0_OFF                               ( 0)
  #define RESPOND_PORT_3_STALL_RSVD0_WID                               ( 4)
  #define RESPOND_PORT_3_STALL_RSVD0_MSK                               (0x0000000F)
  #define RESPOND_PORT_3_STALL_RSVD0_MIN                               (0)
  #define RESPOND_PORT_3_STALL_RSVD0_MAX                               (15) // 0x0000000F
  #define RESPOND_PORT_3_STALL_RSVD0_DEF                               (0x00000000)
  #define RESPOND_PORT_3_STALL_RSVD0_HSH                               (0x040065E4)

  #define RESPOND_PORT_3_STALL_RSP_RD_CPL_STALL_OFF                    ( 4)
  #define RESPOND_PORT_3_STALL_RSP_RD_CPL_STALL_WID                    ( 1)
  #define RESPOND_PORT_3_STALL_RSP_RD_CPL_STALL_MSK                    (0x00000010)
  #define RESPOND_PORT_3_STALL_RSP_RD_CPL_STALL_MIN                    (0)
  #define RESPOND_PORT_3_STALL_RSP_RD_CPL_STALL_MAX                    (1) // 0x00000001
  #define RESPOND_PORT_3_STALL_RSP_RD_CPL_STALL_DEF                    (0x00000000)
  #define RESPOND_PORT_3_STALL_RSP_RD_CPL_STALL_HSH                    (0x010465E4)

  #define RESPOND_PORT_3_STALL_RSVD1_OFF                               ( 5)
  #define RESPOND_PORT_3_STALL_RSVD1_WID                               ( 3)
  #define RESPOND_PORT_3_STALL_RSVD1_MSK                               (0x000000E0)
  #define RESPOND_PORT_3_STALL_RSVD1_MIN                               (0)
  #define RESPOND_PORT_3_STALL_RSVD1_MAX                               (7) // 0x00000007
  #define RESPOND_PORT_3_STALL_RSVD1_DEF                               (0x00000000)
  #define RESPOND_PORT_3_STALL_RSVD1_HSH                               (0x030565E4)

  #define RESPOND_PORT_3_STALL_UNSTALL_COUNTER_VALUE_OFF               ( 8)
  #define RESPOND_PORT_3_STALL_UNSTALL_COUNTER_VALUE_WID               (16)
  #define RESPOND_PORT_3_STALL_UNSTALL_COUNTER_VALUE_MSK               (0x00FFFF00)
  #define RESPOND_PORT_3_STALL_UNSTALL_COUNTER_VALUE_MIN               (0)
  #define RESPOND_PORT_3_STALL_UNSTALL_COUNTER_VALUE_MAX               (65535) // 0x0000FFFF
  #define RESPOND_PORT_3_STALL_UNSTALL_COUNTER_VALUE_DEF               (0x00000000)
  #define RESPOND_PORT_3_STALL_UNSTALL_COUNTER_VALUE_HSH               (0x100865E4)

#define RESPOND_PORT_3_RESERVED_0_REG                                  (0x000065E8)

  #define RESPOND_PORT_3_RESERVED_0_RESERVED_OFF                       ( 0)
  #define RESPOND_PORT_3_RESERVED_0_RESERVED_WID                       (32)
  #define RESPOND_PORT_3_RESERVED_0_RESERVED_MSK                       (0xFFFFFFFF)
  #define RESPOND_PORT_3_RESERVED_0_RESERVED_MIN                       (0)
  #define RESPOND_PORT_3_RESERVED_0_RESERVED_MAX                       (4294967295) // 0xFFFFFFFF
  #define RESPOND_PORT_3_RESERVED_0_RESERVED_DEF                       (0x00000000)
  #define RESPOND_PORT_3_RESERVED_0_RESERVED_HSH                       (0x200065E8)

#define RESPOND_PORT_3_RESERVED_1_REG                                  (0x000065EC)

  #define RESPOND_PORT_3_RESERVED_1_RESERVED_OFF                       ( 0)
  #define RESPOND_PORT_3_RESERVED_1_RESERVED_WID                       (32)
  #define RESPOND_PORT_3_RESERVED_1_RESERVED_MSK                       (0xFFFFFFFF)
  #define RESPOND_PORT_3_RESERVED_1_RESERVED_MIN                       (0)
  #define RESPOND_PORT_3_RESERVED_1_RESERVED_MAX                       (4294967295) // 0xFFFFFFFF
  #define RESPOND_PORT_3_RESERVED_1_RESERVED_DEF                       (0x00000000)
  #define RESPOND_PORT_3_RESERVED_1_RESERVED_HSH                       (0x200065EC)

#define RESPOND_PORT_3_RESERVED_2_REG                                  (0x000065F0)

  #define RESPOND_PORT_3_RESERVED_2_RESERVED_OFF                       ( 0)
  #define RESPOND_PORT_3_RESERVED_2_RESERVED_WID                       (32)
  #define RESPOND_PORT_3_RESERVED_2_RESERVED_MSK                       (0xFFFFFFFF)
  #define RESPOND_PORT_3_RESERVED_2_RESERVED_MIN                       (0)
  #define RESPOND_PORT_3_RESERVED_2_RESERVED_MAX                       (4294967295) // 0xFFFFFFFF
  #define RESPOND_PORT_3_RESERVED_2_RESERVED_DEF                       (0x00000000)
  #define RESPOND_PORT_3_RESERVED_2_RESERVED_HSH                       (0x200065F0)

#define RESPOND_PORT_3_ACCUM_REQ_OUT_REG                               (0x000065F4)

  #define RESPOND_PORT_3_ACCUM_REQ_OUT_REQ_CMD_SUM_OFF                 ( 0)
  #define RESPOND_PORT_3_ACCUM_REQ_OUT_REQ_CMD_SUM_WID                 (16)
  #define RESPOND_PORT_3_ACCUM_REQ_OUT_REQ_CMD_SUM_MSK                 (0x0000FFFF)
  #define RESPOND_PORT_3_ACCUM_REQ_OUT_REQ_CMD_SUM_MIN                 (0)
  #define RESPOND_PORT_3_ACCUM_REQ_OUT_REQ_CMD_SUM_MAX                 (65535) // 0x0000FFFF
  #define RESPOND_PORT_3_ACCUM_REQ_OUT_REQ_CMD_SUM_DEF                 (0x00000000)
  #define RESPOND_PORT_3_ACCUM_REQ_OUT_REQ_CMD_SUM_HSH                 (0x100065F4)

  #define RESPOND_PORT_3_ACCUM_REQ_OUT_REQ_DATA_SUM_OFF                (16)
  #define RESPOND_PORT_3_ACCUM_REQ_OUT_REQ_DATA_SUM_WID                (16)
  #define RESPOND_PORT_3_ACCUM_REQ_OUT_REQ_DATA_SUM_MSK                (0xFFFF0000)
  #define RESPOND_PORT_3_ACCUM_REQ_OUT_REQ_DATA_SUM_MIN                (0)
  #define RESPOND_PORT_3_ACCUM_REQ_OUT_REQ_DATA_SUM_MAX                (65535) // 0x0000FFFF
  #define RESPOND_PORT_3_ACCUM_REQ_OUT_REQ_DATA_SUM_DEF                (0x00000000)
  #define RESPOND_PORT_3_ACCUM_REQ_OUT_REQ_DATA_SUM_HSH                (0x101065F4)

#define RESPOND_PORT_3_ACCUM_RD_CPL_IN_REG                             (0x000065F8)

  #define RESPOND_PORT_3_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_OFF            ( 0)
  #define RESPOND_PORT_3_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_WID            (16)
  #define RESPOND_PORT_3_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_MSK            (0x0000FFFF)
  #define RESPOND_PORT_3_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_MIN            (0)
  #define RESPOND_PORT_3_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_MAX            (65535) // 0x0000FFFF
  #define RESPOND_PORT_3_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_DEF            (0x00000000)
  #define RESPOND_PORT_3_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_HSH            (0x100065F8)

  #define RESPOND_PORT_3_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_OFF           (16)
  #define RESPOND_PORT_3_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_WID           (16)
  #define RESPOND_PORT_3_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_MSK           (0xFFFF0000)
  #define RESPOND_PORT_3_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_MIN           (0)
  #define RESPOND_PORT_3_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_MAX           (65535) // 0x0000FFFF
  #define RESPOND_PORT_3_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_DEF           (0x00000000)
  #define RESPOND_PORT_3_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_HSH           (0x101065F8)

#define RESPOND_PORT_3_ACCUM_RSP_IN_REG                                (0x000065FC)

  #define RESPOND_PORT_3_ACCUM_RSP_IN_RSP_CMD_SUM_OFF                  ( 0)
  #define RESPOND_PORT_3_ACCUM_RSP_IN_RSP_CMD_SUM_WID                  (16)
  #define RESPOND_PORT_3_ACCUM_RSP_IN_RSP_CMD_SUM_MSK                  (0x0000FFFF)
  #define RESPOND_PORT_3_ACCUM_RSP_IN_RSP_CMD_SUM_MIN                  (0)
  #define RESPOND_PORT_3_ACCUM_RSP_IN_RSP_CMD_SUM_MAX                  (65535) // 0x0000FFFF
  #define RESPOND_PORT_3_ACCUM_RSP_IN_RSP_CMD_SUM_DEF                  (0x00000000)
  #define RESPOND_PORT_3_ACCUM_RSP_IN_RSP_CMD_SUM_HSH                  (0x100065FC)

  #define RESPOND_PORT_3_ACCUM_RSP_IN_RSVD_OFF                         (16)
  #define RESPOND_PORT_3_ACCUM_RSP_IN_RSVD_WID                         (16)
  #define RESPOND_PORT_3_ACCUM_RSP_IN_RSVD_MSK                         (0xFFFF0000)
  #define RESPOND_PORT_3_ACCUM_RSP_IN_RSVD_MIN                         (0)
  #define RESPOND_PORT_3_ACCUM_RSP_IN_RSVD_MAX                         (65535) // 0x0000FFFF
  #define RESPOND_PORT_3_ACCUM_RSP_IN_RSVD_DEF                         (0x00000000)
  #define RESPOND_PORT_3_ACCUM_RSP_IN_RSVD_HSH                         (0x101065FC)

#define IMRIAEXCBASE_MCHBAR_CBO_INGRESS_REG                            (0x00006A40)

  #define IMRIAEXCBASE_MCHBAR_CBO_INGRESS_lock_OFF                     ( 0)
  #define IMRIAEXCBASE_MCHBAR_CBO_INGRESS_lock_WID                     ( 1)
  #define IMRIAEXCBASE_MCHBAR_CBO_INGRESS_lock_MSK                     (0x00000001)
  #define IMRIAEXCBASE_MCHBAR_CBO_INGRESS_lock_MIN                     (0)
  #define IMRIAEXCBASE_MCHBAR_CBO_INGRESS_lock_MAX                     (1) // 0x00000001
  #define IMRIAEXCBASE_MCHBAR_CBO_INGRESS_lock_DEF                     (0x00000000)
  #define IMRIAEXCBASE_MCHBAR_CBO_INGRESS_lock_HSH                     (0x41006A40)

  #define IMRIAEXCBASE_MCHBAR_CBO_INGRESS_imriaexcbase_OFF             (10)
  #define IMRIAEXCBASE_MCHBAR_CBO_INGRESS_imriaexcbase_WID             (29)
  #define IMRIAEXCBASE_MCHBAR_CBO_INGRESS_imriaexcbase_MSK             (0x0000007FFFFFFC00ULL)
  #define IMRIAEXCBASE_MCHBAR_CBO_INGRESS_imriaexcbase_MIN             (0)
  #define IMRIAEXCBASE_MCHBAR_CBO_INGRESS_imriaexcbase_MAX             (536870911) // 0x1FFFFFFF
  #define IMRIAEXCBASE_MCHBAR_CBO_INGRESS_imriaexcbase_DEF             (0x00000000)
  #define IMRIAEXCBASE_MCHBAR_CBO_INGRESS_imriaexcbase_HSH             (0x5D0A6A40)

#define IMRIAEXCLIMIT_MCHBAR_CBO_INGRESS_REG                           (0x00006A48)

  #define IMRIAEXCLIMIT_MCHBAR_CBO_INGRESS_lock_OFF                    ( 0)
  #define IMRIAEXCLIMIT_MCHBAR_CBO_INGRESS_lock_WID                    ( 1)
  #define IMRIAEXCLIMIT_MCHBAR_CBO_INGRESS_lock_MSK                    (0x00000001)
  #define IMRIAEXCLIMIT_MCHBAR_CBO_INGRESS_lock_MIN                    (0)
  #define IMRIAEXCLIMIT_MCHBAR_CBO_INGRESS_lock_MAX                    (1) // 0x00000001
  #define IMRIAEXCLIMIT_MCHBAR_CBO_INGRESS_lock_DEF                    (0x00000000)
  #define IMRIAEXCLIMIT_MCHBAR_CBO_INGRESS_lock_HSH                    (0x41006A48)

  #define IMRIAEXCLIMIT_MCHBAR_CBO_INGRESS_imriaexclimit_OFF           (10)
  #define IMRIAEXCLIMIT_MCHBAR_CBO_INGRESS_imriaexclimit_WID           (29)
  #define IMRIAEXCLIMIT_MCHBAR_CBO_INGRESS_imriaexclimit_MSK           (0x0000007FFFFFFC00ULL)
  #define IMRIAEXCLIMIT_MCHBAR_CBO_INGRESS_imriaexclimit_MIN           (0)
  #define IMRIAEXCLIMIT_MCHBAR_CBO_INGRESS_imriaexclimit_MAX           (536870911) // 0x1FFFFFFF
  #define IMRIAEXCLIMIT_MCHBAR_CBO_INGRESS_imriaexclimit_DEF           (0x00000000)
  #define IMRIAEXCLIMIT_MCHBAR_CBO_INGRESS_imriaexclimit_HSH           (0x5D0A6A48)

#define IMRGTEXCBASE_MCHBAR_CBO_INGRESS_REG                            (0x00006A50)

  #define IMRGTEXCBASE_MCHBAR_CBO_INGRESS_lock_OFF                     ( 0)
  #define IMRGTEXCBASE_MCHBAR_CBO_INGRESS_lock_WID                     ( 1)
  #define IMRGTEXCBASE_MCHBAR_CBO_INGRESS_lock_MSK                     (0x00000001)
  #define IMRGTEXCBASE_MCHBAR_CBO_INGRESS_lock_MIN                     (0)
  #define IMRGTEXCBASE_MCHBAR_CBO_INGRESS_lock_MAX                     (1) // 0x00000001
  #define IMRGTEXCBASE_MCHBAR_CBO_INGRESS_lock_DEF                     (0x00000000)
  #define IMRGTEXCBASE_MCHBAR_CBO_INGRESS_lock_HSH                     (0x41006A50)

  #define IMRGTEXCBASE_MCHBAR_CBO_INGRESS_imrgtexcbase_OFF             (10)
  #define IMRGTEXCBASE_MCHBAR_CBO_INGRESS_imrgtexcbase_WID             (29)
  #define IMRGTEXCBASE_MCHBAR_CBO_INGRESS_imrgtexcbase_MSK             (0x0000007FFFFFFC00ULL)
  #define IMRGTEXCBASE_MCHBAR_CBO_INGRESS_imrgtexcbase_MIN             (0)
  #define IMRGTEXCBASE_MCHBAR_CBO_INGRESS_imrgtexcbase_MAX             (536870911) // 0x1FFFFFFF
  #define IMRGTEXCBASE_MCHBAR_CBO_INGRESS_imrgtexcbase_DEF             (0x00000000)
  #define IMRGTEXCBASE_MCHBAR_CBO_INGRESS_imrgtexcbase_HSH             (0x5D0A6A50)

#define IMRGTEXCLIMIT_MCHBAR_CBO_INGRESS_REG                           (0x00006A58)

  #define IMRGTEXCLIMIT_MCHBAR_CBO_INGRESS_lock_OFF                    ( 0)
  #define IMRGTEXCLIMIT_MCHBAR_CBO_INGRESS_lock_WID                    ( 1)
  #define IMRGTEXCLIMIT_MCHBAR_CBO_INGRESS_lock_MSK                    (0x00000001)
  #define IMRGTEXCLIMIT_MCHBAR_CBO_INGRESS_lock_MIN                    (0)
  #define IMRGTEXCLIMIT_MCHBAR_CBO_INGRESS_lock_MAX                    (1) // 0x00000001
  #define IMRGTEXCLIMIT_MCHBAR_CBO_INGRESS_lock_DEF                    (0x00000000)
  #define IMRGTEXCLIMIT_MCHBAR_CBO_INGRESS_lock_HSH                    (0x41006A58)

  #define IMRGTEXCLIMIT_MCHBAR_CBO_INGRESS_imrgtexclimit_OFF           (10)
  #define IMRGTEXCLIMIT_MCHBAR_CBO_INGRESS_imrgtexclimit_WID           (29)
  #define IMRGTEXCLIMIT_MCHBAR_CBO_INGRESS_imrgtexclimit_MSK           (0x0000007FFFFFFC00ULL)
  #define IMRGTEXCLIMIT_MCHBAR_CBO_INGRESS_imrgtexclimit_MIN           (0)
  #define IMRGTEXCLIMIT_MCHBAR_CBO_INGRESS_imrgtexclimit_MAX           (536870911) // 0x1FFFFFFF
  #define IMRGTEXCLIMIT_MCHBAR_CBO_INGRESS_imrgtexclimit_DEF           (0x00000000)
  #define IMRGTEXCLIMIT_MCHBAR_CBO_INGRESS_imrgtexclimit_HSH           (0x5D0A6A58)
#pragma pack(pop)
#endif
