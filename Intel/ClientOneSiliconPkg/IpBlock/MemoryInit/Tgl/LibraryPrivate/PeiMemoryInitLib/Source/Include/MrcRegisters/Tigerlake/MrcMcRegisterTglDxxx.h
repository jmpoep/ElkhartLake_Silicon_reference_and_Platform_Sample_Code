#ifndef __MrcMcRegisterTglDxxx_h__
#define __MrcMcRegisterTglDxxx_h__
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


#define MC0_CH0_CR_CADB_ACCESS_CONTROL_POLICY_REG                      (0x0000D000)
//Duplicate of MC0_CR_CPGC2_ACCESS_CONTROL_POLICY_REG

#define MC0_CH0_CR_CADB_ACCESS_READ_POLICY_REG                         (0x0000D008)
//Duplicate of MC0_CR_CPGC2_ACCESS_READ_POLICY_REG

#define MC0_CH0_CR_CADB_ACCESS_WRITE_POLICY_REG                        (0x0000D010)
//Duplicate of MC0_CR_CPGC2_ACCESS_WRITE_POLICY_REG

#define MC0_CH0_CR_CADB_CTL_REG                                        (0x0000D020)

  #define MC0_CH0_CR_CADB_CTL_START_TEST_OFF                           ( 0)
  #define MC0_CH0_CR_CADB_CTL_START_TEST_WID                           ( 1)
  #define MC0_CH0_CR_CADB_CTL_START_TEST_MSK                           (0x00000001)
  #define MC0_CH0_CR_CADB_CTL_START_TEST_MIN                           (0)
  #define MC0_CH0_CR_CADB_CTL_START_TEST_MAX                           (1) // 0x00000001
  #define MC0_CH0_CR_CADB_CTL_START_TEST_DEF                           (0x00000000)
  #define MC0_CH0_CR_CADB_CTL_START_TEST_HSH                           (0x0100D020)

  #define MC0_CH0_CR_CADB_CTL_STOP_TEST_OFF                            ( 1)
  #define MC0_CH0_CR_CADB_CTL_STOP_TEST_WID                            ( 1)
  #define MC0_CH0_CR_CADB_CTL_STOP_TEST_MSK                            (0x00000002)
  #define MC0_CH0_CR_CADB_CTL_STOP_TEST_MIN                            (0)
  #define MC0_CH0_CR_CADB_CTL_STOP_TEST_MAX                            (1) // 0x00000001
  #define MC0_CH0_CR_CADB_CTL_STOP_TEST_DEF                            (0x00000000)
  #define MC0_CH0_CR_CADB_CTL_STOP_TEST_HSH                            (0x0102D020)

#define MC0_CH0_CR_CADB_CFG_REG                                        (0x0000D024)

  #define MC0_CH0_CR_CADB_CFG_CMD_DESELECT_START_OFF                   ( 0)
  #define MC0_CH0_CR_CADB_CFG_CMD_DESELECT_START_WID                   ( 4)
  #define MC0_CH0_CR_CADB_CFG_CMD_DESELECT_START_MSK                   (0x0000000F)
  #define MC0_CH0_CR_CADB_CFG_CMD_DESELECT_START_MIN                   (0)
  #define MC0_CH0_CR_CADB_CFG_CMD_DESELECT_START_MAX                   (15) // 0x0000000F
  #define MC0_CH0_CR_CADB_CFG_CMD_DESELECT_START_DEF                   (0x00000000)
  #define MC0_CH0_CR_CADB_CFG_CMD_DESELECT_START_HSH                   (0x0400D024)

  #define MC0_CH0_CR_CADB_CFG_CMD_DESELECT_STOP_OFF                    ( 4)
  #define MC0_CH0_CR_CADB_CFG_CMD_DESELECT_STOP_WID                    ( 4)
  #define MC0_CH0_CR_CADB_CFG_CMD_DESELECT_STOP_MSK                    (0x000000F0)
  #define MC0_CH0_CR_CADB_CFG_CMD_DESELECT_STOP_MIN                    (0)
  #define MC0_CH0_CR_CADB_CFG_CMD_DESELECT_STOP_MAX                    (15) // 0x0000000F
  #define MC0_CH0_CR_CADB_CFG_CMD_DESELECT_STOP_DEF                    (0x00000000)
  #define MC0_CH0_CR_CADB_CFG_CMD_DESELECT_STOP_HSH                    (0x0408D024)

  #define MC0_CH0_CR_CADB_CFG_LANE_DESELECT_EN_OFF                     ( 8)
  #define MC0_CH0_CR_CADB_CFG_LANE_DESELECT_EN_WID                     ( 3)
  #define MC0_CH0_CR_CADB_CFG_LANE_DESELECT_EN_MSK                     (0x00000700)
  #define MC0_CH0_CR_CADB_CFG_LANE_DESELECT_EN_MIN                     (0)
  #define MC0_CH0_CR_CADB_CFG_LANE_DESELECT_EN_MAX                     (7) // 0x00000007
  #define MC0_CH0_CR_CADB_CFG_LANE_DESELECT_EN_DEF                     (0x00000000)
  #define MC0_CH0_CR_CADB_CFG_LANE_DESELECT_EN_HSH                     (0x0310D024)

  #define MC0_CH0_CR_CADB_CFG_INITIAL_DSEL_EN_OFF                      (11)
  #define MC0_CH0_CR_CADB_CFG_INITIAL_DSEL_EN_WID                      ( 1)
  #define MC0_CH0_CR_CADB_CFG_INITIAL_DSEL_EN_MSK                      (0x00000800)
  #define MC0_CH0_CR_CADB_CFG_INITIAL_DSEL_EN_MIN                      (0)
  #define MC0_CH0_CR_CADB_CFG_INITIAL_DSEL_EN_MAX                      (1) // 0x00000001
  #define MC0_CH0_CR_CADB_CFG_INITIAL_DSEL_EN_DEF                      (0x00000001)
  #define MC0_CH0_CR_CADB_CFG_INITIAL_DSEL_EN_HSH                      (0x0116D024)

  #define MC0_CH0_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_OFF                 (12)
  #define MC0_CH0_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_WID                 ( 1)
  #define MC0_CH0_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_MSK                 (0x00001000)
  #define MC0_CH0_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_MIN                 (0)
  #define MC0_CH0_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_MAX                 (1) // 0x00000001
  #define MC0_CH0_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_DEF                 (0x00000001)
  #define MC0_CH0_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_HSH                 (0x0118D024)

  #define MC0_CH0_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_OFF              (13)
  #define MC0_CH0_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_WID              ( 3)
  #define MC0_CH0_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_MSK              (0x0000E000)
  #define MC0_CH0_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_MIN              (0)
  #define MC0_CH0_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_MAX              (7) // 0x00000007
  #define MC0_CH0_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_DEF              (0x00000000)
  #define MC0_CH0_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_HSH              (0x031AD024)

  #define MC0_CH0_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_OFF               (16)
  #define MC0_CH0_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_WID               ( 3)
  #define MC0_CH0_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_MSK               (0x00070000)
  #define MC0_CH0_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_MIN               (0)
  #define MC0_CH0_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_MAX               (7) // 0x00000007
  #define MC0_CH0_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_DEF               (0x00000000)
  #define MC0_CH0_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_HSH               (0x0320D024)

  #define MC0_CH0_CR_CADB_CFG_CADB_TO_CPGC_BIND_OFF                    (24)
  #define MC0_CH0_CR_CADB_CFG_CADB_TO_CPGC_BIND_WID                    ( 1)
  #define MC0_CH0_CR_CADB_CFG_CADB_TO_CPGC_BIND_MSK                    (0x01000000)
  #define MC0_CH0_CR_CADB_CFG_CADB_TO_CPGC_BIND_MIN                    (0)
  #define MC0_CH0_CR_CADB_CFG_CADB_TO_CPGC_BIND_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_CADB_CFG_CADB_TO_CPGC_BIND_DEF                    (0x00000000)
  #define MC0_CH0_CR_CADB_CFG_CADB_TO_CPGC_BIND_HSH                    (0x0130D024)

  #define MC0_CH0_CR_CADB_CFG_GLOBAL_START_BIND_OFF                    (25)
  #define MC0_CH0_CR_CADB_CFG_GLOBAL_START_BIND_WID                    ( 1)
  #define MC0_CH0_CR_CADB_CFG_GLOBAL_START_BIND_MSK                    (0x02000000)
  #define MC0_CH0_CR_CADB_CFG_GLOBAL_START_BIND_MIN                    (0)
  #define MC0_CH0_CR_CADB_CFG_GLOBAL_START_BIND_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_CADB_CFG_GLOBAL_START_BIND_DEF                    (0x00000000)
  #define MC0_CH0_CR_CADB_CFG_GLOBAL_START_BIND_HSH                    (0x0132D024)

  #define MC0_CH0_CR_CADB_CFG_GLOBAL_STOP_BIND_OFF                     (26)
  #define MC0_CH0_CR_CADB_CFG_GLOBAL_STOP_BIND_WID                     ( 1)
  #define MC0_CH0_CR_CADB_CFG_GLOBAL_STOP_BIND_MSK                     (0x04000000)
  #define MC0_CH0_CR_CADB_CFG_GLOBAL_STOP_BIND_MIN                     (0)
  #define MC0_CH0_CR_CADB_CFG_GLOBAL_STOP_BIND_MAX                     (1) // 0x00000001
  #define MC0_CH0_CR_CADB_CFG_GLOBAL_STOP_BIND_DEF                     (0x00000000)
  #define MC0_CH0_CR_CADB_CFG_GLOBAL_STOP_BIND_HSH                     (0x0134D024)

  #define MC0_CH0_CR_CADB_CFG_CADB_MODE_OFF                            (29)
  #define MC0_CH0_CR_CADB_CFG_CADB_MODE_WID                            ( 3)
  #define MC0_CH0_CR_CADB_CFG_CADB_MODE_MSK                            (0xE0000000)
  #define MC0_CH0_CR_CADB_CFG_CADB_MODE_MIN                            (0)
  #define MC0_CH0_CR_CADB_CFG_CADB_MODE_MAX                            (7) // 0x00000007
  #define MC0_CH0_CR_CADB_CFG_CADB_MODE_DEF                            (0x00000000)
  #define MC0_CH0_CR_CADB_CFG_CADB_MODE_HSH                            (0x033AD024)

#define MC0_CH0_CR_CADB_DLY_REG                                        (0x0000D028)

  #define MC0_CH0_CR_CADB_DLY_START_DELAY_OFF                          ( 0)
  #define MC0_CH0_CR_CADB_DLY_START_DELAY_WID                          (10)
  #define MC0_CH0_CR_CADB_DLY_START_DELAY_MSK                          (0x000003FF)
  #define MC0_CH0_CR_CADB_DLY_START_DELAY_MIN                          (0)
  #define MC0_CH0_CR_CADB_DLY_START_DELAY_MAX                          (1023) // 0x000003FF
  #define MC0_CH0_CR_CADB_DLY_START_DELAY_DEF                          (0x00000000)
  #define MC0_CH0_CR_CADB_DLY_START_DELAY_HSH                          (0x0A00D028)

  #define MC0_CH0_CR_CADB_DLY_STOP_DELAY_OFF                           (16)
  #define MC0_CH0_CR_CADB_DLY_STOP_DELAY_WID                           (10)
  #define MC0_CH0_CR_CADB_DLY_STOP_DELAY_MSK                           (0x03FF0000)
  #define MC0_CH0_CR_CADB_DLY_STOP_DELAY_MIN                           (0)
  #define MC0_CH0_CR_CADB_DLY_STOP_DELAY_MAX                           (1023) // 0x000003FF
  #define MC0_CH0_CR_CADB_DLY_STOP_DELAY_DEF                           (0x00000000)
  #define MC0_CH0_CR_CADB_DLY_STOP_DELAY_HSH                           (0x0A20D028)

#define MC0_CH0_CR_CADB_STATUS_REG                                     (0x0000D02C)

  #define MC0_CH0_CR_CADB_STATUS_MRS_CURR_PTR_OFF                      (21)
  #define MC0_CH0_CR_CADB_STATUS_MRS_CURR_PTR_WID                      ( 3)
  #define MC0_CH0_CR_CADB_STATUS_MRS_CURR_PTR_MSK                      (0x00E00000)
  #define MC0_CH0_CR_CADB_STATUS_MRS_CURR_PTR_MIN                      (0)
  #define MC0_CH0_CR_CADB_STATUS_MRS_CURR_PTR_MAX                      (7) // 0x00000007
  #define MC0_CH0_CR_CADB_STATUS_MRS_CURR_PTR_DEF                      (0x00000000)
  #define MC0_CH0_CR_CADB_STATUS_MRS_CURR_PTR_HSH                      (0x032AD02C)

  #define MC0_CH0_CR_CADB_STATUS_TEST_ABORTED_OFF                      (24)
  #define MC0_CH0_CR_CADB_STATUS_TEST_ABORTED_WID                      ( 1)
  #define MC0_CH0_CR_CADB_STATUS_TEST_ABORTED_MSK                      (0x01000000)
  #define MC0_CH0_CR_CADB_STATUS_TEST_ABORTED_MIN                      (0)
  #define MC0_CH0_CR_CADB_STATUS_TEST_ABORTED_MAX                      (1) // 0x00000001
  #define MC0_CH0_CR_CADB_STATUS_TEST_ABORTED_DEF                      (0x00000000)
  #define MC0_CH0_CR_CADB_STATUS_TEST_ABORTED_HSH                      (0x0130D02C)

  #define MC0_CH0_CR_CADB_STATUS_ALGO_DONE_OFF                         (28)
  #define MC0_CH0_CR_CADB_STATUS_ALGO_DONE_WID                         ( 1)
  #define MC0_CH0_CR_CADB_STATUS_ALGO_DONE_MSK                         (0x10000000)
  #define MC0_CH0_CR_CADB_STATUS_ALGO_DONE_MIN                         (0)
  #define MC0_CH0_CR_CADB_STATUS_ALGO_DONE_MAX                         (1) // 0x00000001
  #define MC0_CH0_CR_CADB_STATUS_ALGO_DONE_DEF                         (0x00000000)
  #define MC0_CH0_CR_CADB_STATUS_ALGO_DONE_HSH                         (0x0138D02C)

  #define MC0_CH0_CR_CADB_STATUS_START_TEST_DELAY_BUSY_OFF             (29)
  #define MC0_CH0_CR_CADB_STATUS_START_TEST_DELAY_BUSY_WID             ( 1)
  #define MC0_CH0_CR_CADB_STATUS_START_TEST_DELAY_BUSY_MSK             (0x20000000)
  #define MC0_CH0_CR_CADB_STATUS_START_TEST_DELAY_BUSY_MIN             (0)
  #define MC0_CH0_CR_CADB_STATUS_START_TEST_DELAY_BUSY_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_CADB_STATUS_START_TEST_DELAY_BUSY_DEF             (0x00000000)
  #define MC0_CH0_CR_CADB_STATUS_START_TEST_DELAY_BUSY_HSH             (0x013AD02C)

  #define MC0_CH0_CR_CADB_STATUS_TEST_BUSY_OFF                         (30)
  #define MC0_CH0_CR_CADB_STATUS_TEST_BUSY_WID                         ( 1)
  #define MC0_CH0_CR_CADB_STATUS_TEST_BUSY_MSK                         (0x40000000)
  #define MC0_CH0_CR_CADB_STATUS_TEST_BUSY_MIN                         (0)
  #define MC0_CH0_CR_CADB_STATUS_TEST_BUSY_MAX                         (1) // 0x00000001
  #define MC0_CH0_CR_CADB_STATUS_TEST_BUSY_DEF                         (0x00000000)
  #define MC0_CH0_CR_CADB_STATUS_TEST_BUSY_HSH                         (0x013CD02C)

  #define MC0_CH0_CR_CADB_STATUS_TEST_DONE_OFF                         (31)
  #define MC0_CH0_CR_CADB_STATUS_TEST_DONE_WID                         ( 1)
  #define MC0_CH0_CR_CADB_STATUS_TEST_DONE_MSK                         (0x80000000)
  #define MC0_CH0_CR_CADB_STATUS_TEST_DONE_MIN                         (0)
  #define MC0_CH0_CR_CADB_STATUS_TEST_DONE_MAX                         (1) // 0x00000001
  #define MC0_CH0_CR_CADB_STATUS_TEST_DONE_DEF                         (0x00000000)
  #define MC0_CH0_CR_CADB_STATUS_TEST_DONE_HSH                         (0x013ED02C)

#define MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_REG                          (0x0000D030)

  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_OFF            ( 0)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_WID            ( 2)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_MSK            (0x00000003)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_MIN            (0)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_MAX            (3) // 0x00000003
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_DEF            (0x00000001)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_HSH            (0x0200D030)

  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_OFF ( 3)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_WID ( 3)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_MSK (0x00000038)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_MIN (0)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_MAX (7) // 0x00000007
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_DEF (0x00000000)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_HSH (0x0306D030)

#define MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_1_REG                          (0x0000D031)
//Duplicate of MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_REG

#define MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_2_REG                          (0x0000D032)
//Duplicate of MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_REG

#define MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_REG                         (0x0000D034)

  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_OFF                   ( 0)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_WID                   (32)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_MSK                   (0xFFFFFFFF)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_MIN                   (0)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_MAX                   (4294967295) // 0xFFFFFFFF
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_DEF                   (0x0000AA55)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_HSH                   (0x2000D034)

#define MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_1_REG                         (0x0000D038)
//Duplicate of MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_REG

#define MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_2_REG                         (0x0000D03C)
//Duplicate of MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_REG

#define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_REG                            (0x0000D040)

  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_OFF                    ( 0)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_WID                    ( 1)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_MSK                    (0x00000001)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_MIN                    (0)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_MAX                    (1) // 0x00000001
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_DEF                    (0x00000000)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_HSH                    (0x0100D040)

  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_OFF             ( 4)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_WID             ( 4)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_MSK             (0x000000F0)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_MIN             (0)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_MAX             (15) // 0x0000000F
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_DEF             (0x00000000)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_HSH             (0x0408D040)

  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_OFF                    ( 8)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_WID                    ( 8)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_MSK                    (0x0000FF00)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_MIN                    (0)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_MAX                    (255) // 0x000000FF
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_DEF                    (0x00000000)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_HSH                    (0x0810D040)

  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_OFF                    (16)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_WID                    ( 8)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_MSK                    (0x00FF0000)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_MIN                    (0)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_MAX                    (255) // 0x000000FF
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_DEF                    (0x00000000)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_HSH                    (0x0820D040)

  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_OFF                    (24)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_WID                    ( 8)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_MSK                    (0xFF000000)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_MIN                    (0)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_MAX                    (255) // 0x000000FF
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_DEF                    (0x00000000)
  #define MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_HSH                    (0x0830D040)

#define MC0_CH0_CR_CADB_BUF_0_REG                                      (0x0000D048)

  #define MC0_CH0_CR_CADB_BUF_0_CS_OFF                                 ( 0)
  #define MC0_CH0_CR_CADB_BUF_0_CS_WID                                 ( 4)
  #define MC0_CH0_CR_CADB_BUF_0_CS_MSK                                 (0x0000000F)
  #define MC0_CH0_CR_CADB_BUF_0_CS_MIN                                 (0)
  #define MC0_CH0_CR_CADB_BUF_0_CS_MAX                                 (15) // 0x0000000F
  #define MC0_CH0_CR_CADB_BUF_0_CS_DEF                                 (0x00000000)
  #define MC0_CH0_CR_CADB_BUF_0_CS_HSH                                 (0x4400D048)

  #define MC0_CH0_CR_CADB_BUF_0_CID_OFF                                ( 4)
  #define MC0_CH0_CR_CADB_BUF_0_CID_WID                                ( 3)
  #define MC0_CH0_CR_CADB_BUF_0_CID_MSK                                (0x00000070)
  #define MC0_CH0_CR_CADB_BUF_0_CID_MIN                                (0)
  #define MC0_CH0_CR_CADB_BUF_0_CID_MAX                                (7) // 0x00000007
  #define MC0_CH0_CR_CADB_BUF_0_CID_DEF                                (0x00000000)
  #define MC0_CH0_CR_CADB_BUF_0_CID_HSH                                (0x4308D048)

  #define MC0_CH0_CR_CADB_BUF_0_ODT_OFF                                ( 7)
  #define MC0_CH0_CR_CADB_BUF_0_ODT_WID                                ( 4)
  #define MC0_CH0_CR_CADB_BUF_0_ODT_MSK                                (0x00000780)
  #define MC0_CH0_CR_CADB_BUF_0_ODT_MIN                                (0)
  #define MC0_CH0_CR_CADB_BUF_0_ODT_MAX                                (15) // 0x0000000F
  #define MC0_CH0_CR_CADB_BUF_0_ODT_DEF                                (0x00000000)
  #define MC0_CH0_CR_CADB_BUF_0_ODT_HSH                                (0x440ED048)

  #define MC0_CH0_CR_CADB_BUF_0_CKE_OFF                                (11)
  #define MC0_CH0_CR_CADB_BUF_0_CKE_WID                                ( 4)
  #define MC0_CH0_CR_CADB_BUF_0_CKE_MSK                                (0x00007800)
  #define MC0_CH0_CR_CADB_BUF_0_CKE_MIN                                (0)
  #define MC0_CH0_CR_CADB_BUF_0_CKE_MAX                                (15) // 0x0000000F
  #define MC0_CH0_CR_CADB_BUF_0_CKE_DEF                                (0x00000000)
  #define MC0_CH0_CR_CADB_BUF_0_CKE_HSH                                (0x4416D048)

  #define MC0_CH0_CR_CADB_BUF_0_USE_HALF_CA_OFF                        (15)
  #define MC0_CH0_CR_CADB_BUF_0_USE_HALF_CA_WID                        ( 1)
  #define MC0_CH0_CR_CADB_BUF_0_USE_HALF_CA_MSK                        (0x00008000)
  #define MC0_CH0_CR_CADB_BUF_0_USE_HALF_CA_MIN                        (0)
  #define MC0_CH0_CR_CADB_BUF_0_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define MC0_CH0_CR_CADB_BUF_0_USE_HALF_CA_DEF                        (0x00000000)
  #define MC0_CH0_CR_CADB_BUF_0_USE_HALF_CA_HSH                        (0x411ED048)

  #define MC0_CH0_CR_CADB_BUF_0_VAL_OFF                                (16)
  #define MC0_CH0_CR_CADB_BUF_0_VAL_WID                                ( 1)
  #define MC0_CH0_CR_CADB_BUF_0_VAL_MSK                                (0x00010000)
  #define MC0_CH0_CR_CADB_BUF_0_VAL_MIN                                (0)
  #define MC0_CH0_CR_CADB_BUF_0_VAL_MAX                                (1) // 0x00000001
  #define MC0_CH0_CR_CADB_BUF_0_VAL_DEF                                (0x00000000)
  #define MC0_CH0_CR_CADB_BUF_0_VAL_HSH                                (0x4120D048)

  #define MC0_CH0_CR_CADB_BUF_0_PAR_OFF                                (17)
  #define MC0_CH0_CR_CADB_BUF_0_PAR_WID                                ( 1)
  #define MC0_CH0_CR_CADB_BUF_0_PAR_MSK                                (0x00020000)
  #define MC0_CH0_CR_CADB_BUF_0_PAR_MIN                                (0)
  #define MC0_CH0_CR_CADB_BUF_0_PAR_MAX                                (1) // 0x00000001
  #define MC0_CH0_CR_CADB_BUF_0_PAR_DEF                                (0x00000000)
  #define MC0_CH0_CR_CADB_BUF_0_PAR_HSH                                (0x4122D048)

  #define MC0_CH0_CR_CADB_BUF_0_CA_OFF                                 (18)
  #define MC0_CH0_CR_CADB_BUF_0_CA_WID                                 (24)
  #define MC0_CH0_CR_CADB_BUF_0_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define MC0_CH0_CR_CADB_BUF_0_CA_MIN                                 (0)
  #define MC0_CH0_CR_CADB_BUF_0_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define MC0_CH0_CR_CADB_BUF_0_CA_DEF                                 (0x00000000)
  #define MC0_CH0_CR_CADB_BUF_0_CA_HSH                                 (0x5824D048)

#define MC0_CH0_CR_CADB_BUF_0_P0_REG                                   (0x0000D048)

  #define MC0_CH0_CR_CADB_BUF_0_CS_P0_OFF                              ( 0)
  #define MC0_CH0_CR_CADB_BUF_0_CS_P0_WID                              ( 4)
  #define MC0_CH0_CR_CADB_BUF_0_CS_P0_MSK                              (0x0000000F)
  #define MC0_CH0_CR_CADB_BUF_0_CS_P0_MIN                              (0)
  #define MC0_CH0_CR_CADB_BUF_0_CS_P0_MAX                              (15) // 0x0000000F
  #define MC0_CH0_CR_CADB_BUF_0_CS_P0_DEF                              (0x00000000)
  #define MC0_CH0_CR_CADB_BUF_0_CS_P0_HSH                              (0x4400D048)

  #define MC0_CH0_CR_CADB_BUF_0_CID_P0_OFF                             ( 4)
  #define MC0_CH0_CR_CADB_BUF_0_CID_P0_WID                             ( 3)
  #define MC0_CH0_CR_CADB_BUF_0_CID_P0_MSK                             (0x00000070)
  #define MC0_CH0_CR_CADB_BUF_0_CID_P0_MIN                             (0)
  #define MC0_CH0_CR_CADB_BUF_0_CID_P0_MAX                             (7) // 0x00000007
  #define MC0_CH0_CR_CADB_BUF_0_CID_P0_DEF                             (0x00000000)
  #define MC0_CH0_CR_CADB_BUF_0_CID_P0_HSH                             (0x4308D048)

  #define MC0_CH0_CR_CADB_BUF_0_ODT_P0_OFF                             ( 7)
  #define MC0_CH0_CR_CADB_BUF_0_ODT_P0_WID                             ( 4)
  #define MC0_CH0_CR_CADB_BUF_0_ODT_P0_MSK                             (0x00000780)
  #define MC0_CH0_CR_CADB_BUF_0_ODT_P0_MIN                             (0)
  #define MC0_CH0_CR_CADB_BUF_0_ODT_P0_MAX                             (15) // 0x0000000F
  #define MC0_CH0_CR_CADB_BUF_0_ODT_P0_DEF                             (0x00000000)
  #define MC0_CH0_CR_CADB_BUF_0_ODT_P0_HSH                             (0x440ED048)

  #define MC0_CH0_CR_CADB_BUF_0_CKE_P0_OFF                             (11)
  #define MC0_CH0_CR_CADB_BUF_0_CKE_P0_WID                             ( 4)
  #define MC0_CH0_CR_CADB_BUF_0_CKE_P0_MSK                             (0x00007800)
  #define MC0_CH0_CR_CADB_BUF_0_CKE_P0_MIN                             (0)
  #define MC0_CH0_CR_CADB_BUF_0_CKE_P0_MAX                             (15) // 0x0000000F
  #define MC0_CH0_CR_CADB_BUF_0_CKE_P0_DEF                             (0x00000000)
  #define MC0_CH0_CR_CADB_BUF_0_CKE_P0_HSH                             (0x4416D048)

  #define MC0_CH0_CR_CADB_BUF_0_USE_HALF_CA_P0_OFF                     (15)
  #define MC0_CH0_CR_CADB_BUF_0_USE_HALF_CA_P0_WID                     ( 1)
  #define MC0_CH0_CR_CADB_BUF_0_USE_HALF_CA_P0_MSK                     (0x00008000)
  #define MC0_CH0_CR_CADB_BUF_0_USE_HALF_CA_P0_MIN                     (0)
  #define MC0_CH0_CR_CADB_BUF_0_USE_HALF_CA_P0_MAX                     (1) // 0x00000001
  #define MC0_CH0_CR_CADB_BUF_0_USE_HALF_CA_P0_DEF                     (0x00000000)
  #define MC0_CH0_CR_CADB_BUF_0_USE_HALF_CA_P0_HSH                     (0x411ED048)

  #define MC0_CH0_CR_CADB_BUF_0_VAL_P0_OFF                             (16)
  #define MC0_CH0_CR_CADB_BUF_0_VAL_P0_WID                             ( 1)
  #define MC0_CH0_CR_CADB_BUF_0_VAL_P0_MSK                             (0x00010000)
  #define MC0_CH0_CR_CADB_BUF_0_VAL_P0_MIN                             (0)
  #define MC0_CH0_CR_CADB_BUF_0_VAL_P0_MAX                             (1) // 0x00000001
  #define MC0_CH0_CR_CADB_BUF_0_VAL_P0_DEF                             (0x00000000)
  #define MC0_CH0_CR_CADB_BUF_0_VAL_P0_HSH                             (0x4120D048)

  #define MC0_CH0_CR_CADB_BUF_0_PAR_P0_OFF                             (17)
  #define MC0_CH0_CR_CADB_BUF_0_PAR_P0_WID                             ( 1)
  #define MC0_CH0_CR_CADB_BUF_0_PAR_P0_MSK                             (0x00020000)
  #define MC0_CH0_CR_CADB_BUF_0_PAR_P0_MIN                             (0)
  #define MC0_CH0_CR_CADB_BUF_0_PAR_P0_MAX                             (1) // 0x00000001
  #define MC0_CH0_CR_CADB_BUF_0_PAR_P0_DEF                             (0x00000000)
  #define MC0_CH0_CR_CADB_BUF_0_PAR_P0_HSH                             (0x4122D048)

  #define MC0_CH0_CR_CADB_BUF_0_CA_P0_OFF                              (18)
  #define MC0_CH0_CR_CADB_BUF_0_CA_P0_WID                              (28)
  #define MC0_CH0_CR_CADB_BUF_0_CA_P0_MSK                              (0x00003FFFFFFC0000ULL)
  #define MC0_CH0_CR_CADB_BUF_0_CA_P0_MIN                              (0)
  #define MC0_CH0_CR_CADB_BUF_0_CA_P0_MAX                              (268435455) // 0x0FFFFFFF
  #define MC0_CH0_CR_CADB_BUF_0_CA_P0_DEF                              (0x00000000)
  #define MC0_CH0_CR_CADB_BUF_0_CA_P0_HSH                              (0x5C24D048)

#define MC0_CH0_CR_CADB_BUF_1_REG                                      (0x0000D050)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH0_CR_CADB_BUF_2_REG                                      (0x0000D058)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH0_CR_CADB_BUF_3_REG                                      (0x0000D060)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH0_CR_CADB_BUF_4_REG                                      (0x0000D068)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH0_CR_CADB_BUF_5_REG                                      (0x0000D070)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH0_CR_CADB_BUF_6_REG                                      (0x0000D078)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH0_CR_CADB_BUF_7_REG                                      (0x0000D080)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH0_CR_CADB_AO_MRSCFG_REG                                  (0x0000D088)

  #define MC0_CH0_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_OFF                  ( 0)
  #define MC0_CH0_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_WID                  ( 1)
  #define MC0_CH0_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_MSK                  (0x00000001)
  #define MC0_CH0_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_MIN                  (0)
  #define MC0_CH0_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_MAX                  (1) // 0x00000001
  #define MC0_CH0_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_DEF                  (0x00000000)
  #define MC0_CH0_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_HSH                  (0x0100D088)

  #define MC0_CH0_CR_CADB_AO_MRSCFG_MRS_GAP_OFF                        ( 1)
  #define MC0_CH0_CR_CADB_AO_MRSCFG_MRS_GAP_WID                        ( 4)
  #define MC0_CH0_CR_CADB_AO_MRSCFG_MRS_GAP_MSK                        (0x0000001E)
  #define MC0_CH0_CR_CADB_AO_MRSCFG_MRS_GAP_MIN                        (0)
  #define MC0_CH0_CR_CADB_AO_MRSCFG_MRS_GAP_MAX                        (15) // 0x0000000F
  #define MC0_CH0_CR_CADB_AO_MRSCFG_MRS_GAP_DEF                        (0x00000000)
  #define MC0_CH0_CR_CADB_AO_MRSCFG_MRS_GAP_HSH                        (0x0402D088)

  #define MC0_CH0_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_OFF                 ( 8)
  #define MC0_CH0_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_WID                 (16)
  #define MC0_CH0_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_MSK                 (0x00FFFF00)
  #define MC0_CH0_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_MIN                 (0)
  #define MC0_CH0_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_MAX                 (65535) // 0x0000FFFF
  #define MC0_CH0_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_DEF                 (0x00000000)
  #define MC0_CH0_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_HSH                 (0x1010D088)

#define MC0_CH0_CR_CADB_SELCFG_REG                                     (0x0000D090)

  #define MC0_CH0_CR_CADB_SELCFG_WR_SELECT_ENABLE_OFF                  ( 0)
  #define MC0_CH0_CR_CADB_SELCFG_WR_SELECT_ENABLE_WID                  ( 3)
  #define MC0_CH0_CR_CADB_SELCFG_WR_SELECT_ENABLE_MSK                  (0x00000007)
  #define MC0_CH0_CR_CADB_SELCFG_WR_SELECT_ENABLE_MIN                  (0)
  #define MC0_CH0_CR_CADB_SELCFG_WR_SELECT_ENABLE_MAX                  (7) // 0x00000007
  #define MC0_CH0_CR_CADB_SELCFG_WR_SELECT_ENABLE_DEF                  (0x00000000)
  #define MC0_CH0_CR_CADB_SELCFG_WR_SELECT_ENABLE_HSH                  (0x0300D090)

  #define MC0_CH0_CR_CADB_SELCFG_RD_SELECT_ENABLE_OFF                  ( 8)
  #define MC0_CH0_CR_CADB_SELCFG_RD_SELECT_ENABLE_WID                  ( 3)
  #define MC0_CH0_CR_CADB_SELCFG_RD_SELECT_ENABLE_MSK                  (0x00000700)
  #define MC0_CH0_CR_CADB_SELCFG_RD_SELECT_ENABLE_MIN                  (0)
  #define MC0_CH0_CR_CADB_SELCFG_RD_SELECT_ENABLE_MAX                  (7) // 0x00000007
  #define MC0_CH0_CR_CADB_SELCFG_RD_SELECT_ENABLE_DEF                  (0x00000000)
  #define MC0_CH0_CR_CADB_SELCFG_RD_SELECT_ENABLE_HSH                  (0x0310D090)

  #define MC0_CH0_CR_CADB_SELCFG_ACT_SELECT_ENABLE_OFF                 (16)
  #define MC0_CH0_CR_CADB_SELCFG_ACT_SELECT_ENABLE_WID                 ( 3)
  #define MC0_CH0_CR_CADB_SELCFG_ACT_SELECT_ENABLE_MSK                 (0x00070000)
  #define MC0_CH0_CR_CADB_SELCFG_ACT_SELECT_ENABLE_MIN                 (0)
  #define MC0_CH0_CR_CADB_SELCFG_ACT_SELECT_ENABLE_MAX                 (7) // 0x00000007
  #define MC0_CH0_CR_CADB_SELCFG_ACT_SELECT_ENABLE_DEF                 (0x00000000)
  #define MC0_CH0_CR_CADB_SELCFG_ACT_SELECT_ENABLE_HSH                 (0x0320D090)

  #define MC0_CH0_CR_CADB_SELCFG_PRE_SELECT_ENABLE_OFF                 (24)
  #define MC0_CH0_CR_CADB_SELCFG_PRE_SELECT_ENABLE_WID                 ( 3)
  #define MC0_CH0_CR_CADB_SELCFG_PRE_SELECT_ENABLE_MSK                 (0x07000000)
  #define MC0_CH0_CR_CADB_SELCFG_PRE_SELECT_ENABLE_MIN                 (0)
  #define MC0_CH0_CR_CADB_SELCFG_PRE_SELECT_ENABLE_MAX                 (7) // 0x00000007
  #define MC0_CH0_CR_CADB_SELCFG_PRE_SELECT_ENABLE_DEF                 (0x00000000)
  #define MC0_CH0_CR_CADB_SELCFG_PRE_SELECT_ENABLE_HSH                 (0x0330D090)

  #define MC0_CH0_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_OFF               (28)
  #define MC0_CH0_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_WID               ( 1)
  #define MC0_CH0_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_MSK               (0x10000000)
  #define MC0_CH0_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_MIN               (0)
  #define MC0_CH0_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_MAX               (1) // 0x00000001
  #define MC0_CH0_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_DEF               (0x00000001)
  #define MC0_CH0_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_HSH               (0x0138D090)

#define MC0_CH0_CR_CADB_MRSCFG_REG                                     (0x0000D098)

  #define MC0_CH0_CR_CADB_MRSCFG_CS_CLOCKS_OFF                         ( 0)
  #define MC0_CH0_CR_CADB_MRSCFG_CS_CLOCKS_WID                         ( 3)
  #define MC0_CH0_CR_CADB_MRSCFG_CS_CLOCKS_MSK                         (0x00000007)
  #define MC0_CH0_CR_CADB_MRSCFG_CS_CLOCKS_MIN                         (0)
  #define MC0_CH0_CR_CADB_MRSCFG_CS_CLOCKS_MAX                         (7) // 0x00000007
  #define MC0_CH0_CR_CADB_MRSCFG_CS_CLOCKS_DEF                         (0x00000000)
  #define MC0_CH0_CR_CADB_MRSCFG_CS_CLOCKS_HSH                         (0x4300D098)

  #define MC0_CH0_CR_CADB_MRSCFG_DSEL_CLOCKS_OFF                       ( 3)
  #define MC0_CH0_CR_CADB_MRSCFG_DSEL_CLOCKS_WID                       ( 4)
  #define MC0_CH0_CR_CADB_MRSCFG_DSEL_CLOCKS_MSK                       (0x00000078)
  #define MC0_CH0_CR_CADB_MRSCFG_DSEL_CLOCKS_MIN                       (0)
  #define MC0_CH0_CR_CADB_MRSCFG_DSEL_CLOCKS_MAX                       (15) // 0x0000000F
  #define MC0_CH0_CR_CADB_MRSCFG_DSEL_CLOCKS_DEF                       (0x00000000)
  #define MC0_CH0_CR_CADB_MRSCFG_DSEL_CLOCKS_HSH                       (0x4406D098)

  #define MC0_CH0_CR_CADB_MRSCFG_SETUP_CLOCKS_OFF                      ( 8)
  #define MC0_CH0_CR_CADB_MRSCFG_SETUP_CLOCKS_WID                      ( 3)
  #define MC0_CH0_CR_CADB_MRSCFG_SETUP_CLOCKS_MSK                      (0x00000700)
  #define MC0_CH0_CR_CADB_MRSCFG_SETUP_CLOCKS_MIN                      (0)
  #define MC0_CH0_CR_CADB_MRSCFG_SETUP_CLOCKS_MAX                      (7) // 0x00000007
  #define MC0_CH0_CR_CADB_MRSCFG_SETUP_CLOCKS_DEF                      (0x00000000)
  #define MC0_CH0_CR_CADB_MRSCFG_SETUP_CLOCKS_HSH                      (0x4310D098)

  #define MC0_CH0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_OFF                (11)
  #define MC0_CH0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_WID                ( 1)
  #define MC0_CH0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_MSK                (0x00000800)
  #define MC0_CH0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_MIN                (0)
  #define MC0_CH0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_MAX                (1) // 0x00000001
  #define MC0_CH0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_DEF                (0x00000000)
  #define MC0_CH0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_HSH                (0x4116D098)

  #define MC0_CH0_CR_CADB_MRSCFG_MRS_START_PTR_OFF                     (12)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_START_PTR_WID                     ( 3)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_START_PTR_MSK                     (0x00007000)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_START_PTR_MIN                     (0)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_START_PTR_MAX                     (7) // 0x00000007
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_START_PTR_DEF                     (0x00000000)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_START_PTR_HSH                     (0x4318D098)

  #define MC0_CH0_CR_CADB_MRSCFG_MRS_END_PTR_OFF                       (16)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_END_PTR_WID                       ( 3)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_END_PTR_MSK                       (0x00070000)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_END_PTR_MIN                       (0)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_END_PTR_MAX                       (7) // 0x00000007
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_END_PTR_DEF                       (0x00000000)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_END_PTR_HSH                       (0x4320D098)

  #define MC0_CH0_CR_CADB_MRSCFG_MRS_GOTO_PTR_OFF                      (19)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_GOTO_PTR_WID                      ( 3)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_GOTO_PTR_MSK                      (0x00380000)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_GOTO_PTR_MIN                      (0)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_GOTO_PTR_MAX                      (7) // 0x00000007
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_GOTO_PTR_DEF                      (0x00000000)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_GOTO_PTR_HSH                      (0x4326D098)

  #define MC0_CH0_CR_CADB_MRSCFG_MRS_CS_MODE_OFF                       (22)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_CS_MODE_WID                       ( 2)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_CS_MODE_MSK                       (0x00C00000)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_CS_MODE_MIN                       (0)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_CS_MODE_MAX                       (3) // 0x00000003
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_CS_MODE_DEF                       (0x00000000)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_CS_MODE_HSH                       (0x422CD098)

  #define MC0_CH0_CR_CADB_MRSCFG_MRS_DELAY_CNT_OFF                     (24)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_DELAY_CNT_WID                     (16)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_DELAY_CNT_MSK                     (0x000000FFFF000000ULL)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_DELAY_CNT_MIN                     (0)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_DELAY_CNT_MAX                     (65535) // 0x0000FFFF
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_DELAY_CNT_DEF                     (0x00000000)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_DELAY_CNT_HSH                     (0x5030D098)

#define MC0_CH0_CR_CADB_MRSCFG_P0_REG                                  (0x0000D098)

  #define MC0_CH0_CR_CADB_MRSCFG_CS_CLOCKS_P0_OFF                      ( 0)
  #define MC0_CH0_CR_CADB_MRSCFG_CS_CLOCKS_P0_WID                      ( 3)
  #define MC0_CH0_CR_CADB_MRSCFG_CS_CLOCKS_P0_MSK                      (0x00000007)
  #define MC0_CH0_CR_CADB_MRSCFG_CS_CLOCKS_P0_MIN                      (0)
  #define MC0_CH0_CR_CADB_MRSCFG_CS_CLOCKS_P0_MAX                      (7) // 0x00000007
  #define MC0_CH0_CR_CADB_MRSCFG_CS_CLOCKS_P0_DEF                      (0x00000000)
  #define MC0_CH0_CR_CADB_MRSCFG_CS_CLOCKS_P0_HSH                      (0x4300D098)

  #define MC0_CH0_CR_CADB_MRSCFG_DSEL_CLOCKS_P0_OFF                    ( 3)
  #define MC0_CH0_CR_CADB_MRSCFG_DSEL_CLOCKS_P0_WID                    ( 4)
  #define MC0_CH0_CR_CADB_MRSCFG_DSEL_CLOCKS_P0_MSK                    (0x00000078)
  #define MC0_CH0_CR_CADB_MRSCFG_DSEL_CLOCKS_P0_MIN                    (0)
  #define MC0_CH0_CR_CADB_MRSCFG_DSEL_CLOCKS_P0_MAX                    (15) // 0x0000000F
  #define MC0_CH0_CR_CADB_MRSCFG_DSEL_CLOCKS_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_CADB_MRSCFG_DSEL_CLOCKS_P0_HSH                    (0x4406D098)

  #define MC0_CH0_CR_CADB_MRSCFG_SETUP_CLOCKS_P0_OFF                   ( 7)
  #define MC0_CH0_CR_CADB_MRSCFG_SETUP_CLOCKS_P0_WID                   ( 4)
  #define MC0_CH0_CR_CADB_MRSCFG_SETUP_CLOCKS_P0_MSK                   (0x00000780)
  #define MC0_CH0_CR_CADB_MRSCFG_SETUP_CLOCKS_P0_MIN                   (0)
  #define MC0_CH0_CR_CADB_MRSCFG_SETUP_CLOCKS_P0_MAX                   (15) // 0x0000000F
  #define MC0_CH0_CR_CADB_MRSCFG_SETUP_CLOCKS_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_CADB_MRSCFG_SETUP_CLOCKS_P0_HSH                   (0x440ED098)

  #define MC0_CH0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_P0_OFF             (11)
  #define MC0_CH0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_P0_WID             ( 1)
  #define MC0_CH0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_P0_MSK             (0x00000800)
  #define MC0_CH0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_P0_MIN             (0)
  #define MC0_CH0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_P0_MAX             (1) // 0x00000001
  #define MC0_CH0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_P0_DEF             (0x00000000)
  #define MC0_CH0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_P0_HSH             (0x4116D098)

  #define MC0_CH0_CR_CADB_MRSCFG_MRS_START_PTR_P0_OFF                  (12)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_START_PTR_P0_WID                  ( 3)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_START_PTR_P0_MSK                  (0x00007000)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_START_PTR_P0_MIN                  (0)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_START_PTR_P0_MAX                  (7) // 0x00000007
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_START_PTR_P0_DEF                  (0x00000000)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_START_PTR_P0_HSH                  (0x4318D098)

  #define MC0_CH0_CR_CADB_MRSCFG_MRS_END_PTR_P0_OFF                    (16)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_END_PTR_P0_WID                    ( 3)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_END_PTR_P0_MSK                    (0x00070000)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_END_PTR_P0_MIN                    (0)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_END_PTR_P0_MAX                    (7) // 0x00000007
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_END_PTR_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_END_PTR_P0_HSH                    (0x4320D098)

  #define MC0_CH0_CR_CADB_MRSCFG_MRS_GOTO_PTR_P0_OFF                   (19)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_GOTO_PTR_P0_WID                   ( 3)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_GOTO_PTR_P0_MSK                   (0x00380000)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_GOTO_PTR_P0_MIN                   (0)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_GOTO_PTR_P0_MAX                   (7) // 0x00000007
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_GOTO_PTR_P0_DEF                   (0x00000000)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_GOTO_PTR_P0_HSH                   (0x4326D098)

  #define MC0_CH0_CR_CADB_MRSCFG_MRS_CS_MODE_P0_OFF                    (22)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_CS_MODE_P0_WID                    ( 2)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_CS_MODE_P0_MSK                    (0x00C00000)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_CS_MODE_P0_MIN                    (0)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_CS_MODE_P0_MAX                    (3) // 0x00000003
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_CS_MODE_P0_DEF                    (0x00000000)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_CS_MODE_P0_HSH                    (0x422CD098)

  #define MC0_CH0_CR_CADB_MRSCFG_MRS_DELAY_CNT_P0_OFF                  (24)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_DELAY_CNT_P0_WID                  (16)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_DELAY_CNT_P0_MSK                  (0x000000FFFF000000ULL)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_DELAY_CNT_P0_MIN                  (0)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_DELAY_CNT_P0_MAX                  (65535) // 0x0000FFFF
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_DELAY_CNT_P0_DEF                  (0x00000000)
  #define MC0_CH0_CR_CADB_MRSCFG_MRS_DELAY_CNT_P0_HSH                  (0x5030D098)

#define MC0_CH1_CR_CADB_ACCESS_CONTROL_POLICY_REG                      (0x0000D100)
//Duplicate of MC0_CR_CPGC2_ACCESS_CONTROL_POLICY_REG

#define MC0_CH1_CR_CADB_ACCESS_READ_POLICY_REG                         (0x0000D108)
//Duplicate of MC0_CR_CPGC2_ACCESS_READ_POLICY_REG

#define MC0_CH1_CR_CADB_ACCESS_WRITE_POLICY_REG                        (0x0000D110)
//Duplicate of MC0_CR_CPGC2_ACCESS_WRITE_POLICY_REG

#define MC0_CH1_CR_CADB_CTL_REG                                        (0x0000D120)
//Duplicate of MC0_CH0_CR_CADB_CTL_REG

#define MC0_CH1_CR_CADB_CFG_REG                                        (0x0000D124)
//Duplicate of MC0_CH0_CR_CADB_CFG_REG

#define MC0_CH1_CR_CADB_DLY_REG                                        (0x0000D128)
//Duplicate of MC0_CH0_CR_CADB_DLY_REG

#define MC0_CH1_CR_CADB_STATUS_REG                                     (0x0000D12C)
//Duplicate of MC0_CH0_CR_CADB_STATUS_REG

#define MC0_CH1_CR_CADB_DSEL_UNISEQ_CFG_0_REG                          (0x0000D130)
//Duplicate of MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_REG

#define MC0_CH1_CR_CADB_DSEL_UNISEQ_CFG_1_REG                          (0x0000D131)
//Duplicate of MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_REG

#define MC0_CH1_CR_CADB_DSEL_UNISEQ_CFG_2_REG                          (0x0000D132)
//Duplicate of MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_REG

#define MC0_CH1_CR_CADB_DSEL_UNISEQ_PBUF_0_REG                         (0x0000D134)
//Duplicate of MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_REG

#define MC0_CH1_CR_CADB_DSEL_UNISEQ_PBUF_1_REG                         (0x0000D138)
//Duplicate of MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_REG

#define MC0_CH1_CR_CADB_DSEL_UNISEQ_PBUF_2_REG                         (0x0000D13C)
//Duplicate of MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_REG

#define MC0_CH1_CR_CADB_DSEL_UNISEQ_LMN_REG                            (0x0000D140)
//Duplicate of MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_REG

#define MC0_CH1_CR_CADB_BUF_0_REG                                      (0x0000D148)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH1_CR_CADB_BUF_1_REG                                      (0x0000D150)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH1_CR_CADB_BUF_2_REG                                      (0x0000D158)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH1_CR_CADB_BUF_3_REG                                      (0x0000D160)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH1_CR_CADB_BUF_4_REG                                      (0x0000D168)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH1_CR_CADB_BUF_5_REG                                      (0x0000D170)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH1_CR_CADB_BUF_6_REG                                      (0x0000D178)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH1_CR_CADB_BUF_7_REG                                      (0x0000D180)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH1_CR_CADB_AO_MRSCFG_REG                                  (0x0000D188)
//Duplicate of MC0_CH0_CR_CADB_AO_MRSCFG_REG

#define MC0_CH1_CR_CADB_SELCFG_REG                                     (0x0000D190)
//Duplicate of MC0_CH0_CR_CADB_SELCFG_REG

#define MC0_CH1_CR_CADB_MRSCFG_REG                                     (0x0000D198)
//Duplicate of MC0_CH0_CR_CADB_MRSCFG_REG

#define MC0_CH2_CR_CADB_ACCESS_CONTROL_POLICY_REG                      (0x0000D200)
//Duplicate of MC0_CR_CPGC2_ACCESS_CONTROL_POLICY_REG

#define MC0_CH2_CR_CADB_ACCESS_READ_POLICY_REG                         (0x0000D208)
//Duplicate of MC0_CR_CPGC2_ACCESS_READ_POLICY_REG

#define MC0_CH2_CR_CADB_ACCESS_WRITE_POLICY_REG                        (0x0000D210)
//Duplicate of MC0_CR_CPGC2_ACCESS_WRITE_POLICY_REG

#define MC0_CH2_CR_CADB_CTL_REG                                        (0x0000D220)
//Duplicate of MC0_CH0_CR_CADB_CTL_REG

#define MC0_CH2_CR_CADB_CFG_REG                                        (0x0000D224)
//Duplicate of MC0_CH0_CR_CADB_CFG_REG

#define MC0_CH2_CR_CADB_DLY_REG                                        (0x0000D228)
//Duplicate of MC0_CH0_CR_CADB_DLY_REG

#define MC0_CH2_CR_CADB_STATUS_REG                                     (0x0000D22C)
//Duplicate of MC0_CH0_CR_CADB_STATUS_REG

#define MC0_CH2_CR_CADB_DSEL_UNISEQ_CFG_0_REG                          (0x0000D230)
//Duplicate of MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_REG

#define MC0_CH2_CR_CADB_DSEL_UNISEQ_CFG_1_REG                          (0x0000D231)
//Duplicate of MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_REG

#define MC0_CH2_CR_CADB_DSEL_UNISEQ_CFG_2_REG                          (0x0000D232)
//Duplicate of MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_REG

#define MC0_CH2_CR_CADB_DSEL_UNISEQ_PBUF_0_REG                         (0x0000D234)
//Duplicate of MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_REG

#define MC0_CH2_CR_CADB_DSEL_UNISEQ_PBUF_1_REG                         (0x0000D238)
//Duplicate of MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_REG

#define MC0_CH2_CR_CADB_DSEL_UNISEQ_PBUF_2_REG                         (0x0000D23C)
//Duplicate of MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_REG

#define MC0_CH2_CR_CADB_DSEL_UNISEQ_LMN_REG                            (0x0000D240)
//Duplicate of MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_REG

#define MC0_CH2_CR_CADB_BUF_0_REG                                      (0x0000D248)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH2_CR_CADB_BUF_1_REG                                      (0x0000D250)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH2_CR_CADB_BUF_2_REG                                      (0x0000D258)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH2_CR_CADB_BUF_3_REG                                      (0x0000D260)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH2_CR_CADB_BUF_4_REG                                      (0x0000D268)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH2_CR_CADB_BUF_5_REG                                      (0x0000D270)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH2_CR_CADB_BUF_6_REG                                      (0x0000D278)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH2_CR_CADB_BUF_7_REG                                      (0x0000D280)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH2_CR_CADB_AO_MRSCFG_REG                                  (0x0000D288)
//Duplicate of MC0_CH0_CR_CADB_AO_MRSCFG_REG

#define MC0_CH2_CR_CADB_SELCFG_REG                                     (0x0000D290)
//Duplicate of MC0_CH0_CR_CADB_SELCFG_REG

#define MC0_CH2_CR_CADB_MRSCFG_REG                                     (0x0000D298)
//Duplicate of MC0_CH0_CR_CADB_MRSCFG_REG

#define MC0_CH3_CR_CADB_ACCESS_CONTROL_POLICY_REG                      (0x0000D300)
//Duplicate of MC0_CR_CPGC2_ACCESS_CONTROL_POLICY_REG

#define MC0_CH3_CR_CADB_ACCESS_READ_POLICY_REG                         (0x0000D308)
//Duplicate of MC0_CR_CPGC2_ACCESS_READ_POLICY_REG

#define MC0_CH3_CR_CADB_ACCESS_WRITE_POLICY_REG                        (0x0000D310)
//Duplicate of MC0_CR_CPGC2_ACCESS_WRITE_POLICY_REG

#define MC0_CH3_CR_CADB_CTL_REG                                        (0x0000D320)
//Duplicate of MC0_CH0_CR_CADB_CTL_REG

#define MC0_CH3_CR_CADB_CFG_REG                                        (0x0000D324)
//Duplicate of MC0_CH0_CR_CADB_CFG_REG

#define MC0_CH3_CR_CADB_DLY_REG                                        (0x0000D328)
//Duplicate of MC0_CH0_CR_CADB_DLY_REG

#define MC0_CH3_CR_CADB_STATUS_REG                                     (0x0000D32C)
//Duplicate of MC0_CH0_CR_CADB_STATUS_REG

#define MC0_CH3_CR_CADB_DSEL_UNISEQ_CFG_0_REG                          (0x0000D330)
//Duplicate of MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_REG

#define MC0_CH3_CR_CADB_DSEL_UNISEQ_CFG_1_REG                          (0x0000D331)
//Duplicate of MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_REG

#define MC0_CH3_CR_CADB_DSEL_UNISEQ_CFG_2_REG                          (0x0000D332)
//Duplicate of MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_REG

#define MC0_CH3_CR_CADB_DSEL_UNISEQ_PBUF_0_REG                         (0x0000D334)
//Duplicate of MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_REG

#define MC0_CH3_CR_CADB_DSEL_UNISEQ_PBUF_1_REG                         (0x0000D338)
//Duplicate of MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_REG

#define MC0_CH3_CR_CADB_DSEL_UNISEQ_PBUF_2_REG                         (0x0000D33C)
//Duplicate of MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_REG

#define MC0_CH3_CR_CADB_DSEL_UNISEQ_LMN_REG                            (0x0000D340)
//Duplicate of MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_REG

#define MC0_CH3_CR_CADB_BUF_0_REG                                      (0x0000D348)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH3_CR_CADB_BUF_1_REG                                      (0x0000D350)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH3_CR_CADB_BUF_2_REG                                      (0x0000D358)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH3_CR_CADB_BUF_3_REG                                      (0x0000D360)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH3_CR_CADB_BUF_4_REG                                      (0x0000D368)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH3_CR_CADB_BUF_5_REG                                      (0x0000D370)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH3_CR_CADB_BUF_6_REG                                      (0x0000D378)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH3_CR_CADB_BUF_7_REG                                      (0x0000D380)
//Duplicate of MC0_CH0_CR_CADB_BUF_0_REG

#define MC0_CH3_CR_CADB_AO_MRSCFG_REG                                  (0x0000D388)
//Duplicate of MC0_CH0_CR_CADB_AO_MRSCFG_REG

#define MC0_CH3_CR_CADB_SELCFG_REG                                     (0x0000D390)
//Duplicate of MC0_CH0_CR_CADB_SELCFG_REG

#define MC0_CH3_CR_CADB_MRSCFG_REG                                     (0x0000D398)
//Duplicate of MC0_CH0_CR_CADB_MRSCFG_REG

#define MC0_MAD_INTER_CHANNEL_P0_REG                                   (0x0000D800)

  #define MC0_MAD_INTER_CHANNEL_DDR_TYPE_P0_OFF                        ( 0)
  #define MC0_MAD_INTER_CHANNEL_DDR_TYPE_P0_WID                        ( 3)
  #define MC0_MAD_INTER_CHANNEL_DDR_TYPE_P0_MSK                        (0x00000007)
  #define MC0_MAD_INTER_CHANNEL_DDR_TYPE_P0_MIN                        (0)
  #define MC0_MAD_INTER_CHANNEL_DDR_TYPE_P0_MAX                        (7) // 0x00000007
  #define MC0_MAD_INTER_CHANNEL_DDR_TYPE_P0_DEF                        (0x00000000)
  #define MC0_MAD_INTER_CHANNEL_DDR_TYPE_P0_HSH                        (0x0300D800)

  #define MC0_MAD_INTER_CHANNEL_CH_L_MAP_P0_OFF                        ( 4)
  #define MC0_MAD_INTER_CHANNEL_CH_L_MAP_P0_WID                        ( 1)
  #define MC0_MAD_INTER_CHANNEL_CH_L_MAP_P0_MSK                        (0x00000010)
  #define MC0_MAD_INTER_CHANNEL_CH_L_MAP_P0_MIN                        (0)
  #define MC0_MAD_INTER_CHANNEL_CH_L_MAP_P0_MAX                        (1) // 0x00000001
  #define MC0_MAD_INTER_CHANNEL_CH_L_MAP_P0_DEF                        (0x00000000)
  #define MC0_MAD_INTER_CHANNEL_CH_L_MAP_P0_HSH                        (0x0108D800)

  #define MC0_MAD_INTER_CHANNEL_CH_S_SIZE_P0_OFF                       (12)
  #define MC0_MAD_INTER_CHANNEL_CH_S_SIZE_P0_WID                       ( 8)
  #define MC0_MAD_INTER_CHANNEL_CH_S_SIZE_P0_MSK                       (0x000FF000)
  #define MC0_MAD_INTER_CHANNEL_CH_S_SIZE_P0_MIN                       (0)
  #define MC0_MAD_INTER_CHANNEL_CH_S_SIZE_P0_MAX                       (255) // 0x000000FF
  #define MC0_MAD_INTER_CHANNEL_CH_S_SIZE_P0_DEF                       (0x00000000)
  #define MC0_MAD_INTER_CHANNEL_CH_S_SIZE_P0_HSH                       (0x0818D800)

  #define MC0_MAD_INTER_CHANNEL_CH_WIDTH_P0_OFF                        (27)
  #define MC0_MAD_INTER_CHANNEL_CH_WIDTH_P0_WID                        ( 2)
  #define MC0_MAD_INTER_CHANNEL_CH_WIDTH_P0_MSK                        (0x18000000)
  #define MC0_MAD_INTER_CHANNEL_CH_WIDTH_P0_MIN                        (0)
  #define MC0_MAD_INTER_CHANNEL_CH_WIDTH_P0_MAX                        (3) // 0x00000003
  #define MC0_MAD_INTER_CHANNEL_CH_WIDTH_P0_DEF                        (0x00000000)
  #define MC0_MAD_INTER_CHANNEL_CH_WIDTH_P0_HSH                        (0x0236D800)

  #define MC0_MAD_INTER_CHANNEL_HalfCacheLineMode_P0_OFF               (31)
  #define MC0_MAD_INTER_CHANNEL_HalfCacheLineMode_P0_WID               ( 1)
  #define MC0_MAD_INTER_CHANNEL_HalfCacheLineMode_P0_MSK               (0x80000000)
  #define MC0_MAD_INTER_CHANNEL_HalfCacheLineMode_P0_MIN               (0)
  #define MC0_MAD_INTER_CHANNEL_HalfCacheLineMode_P0_MAX               (1) // 0x00000001
  #define MC0_MAD_INTER_CHANNEL_HalfCacheLineMode_P0_DEF               (0x00000000)
  #define MC0_MAD_INTER_CHANNEL_HalfCacheLineMode_P0_HSH               (0x013ED800)

#define MC0_MAD_INTRA_CH0_P0_REG                                       (0x0000D804)

  #define MC0_MAD_INTRA_CH0_DIMM_L_MAP_P0_OFF                          ( 0)
  #define MC0_MAD_INTRA_CH0_DIMM_L_MAP_P0_WID                          ( 1)
  #define MC0_MAD_INTRA_CH0_DIMM_L_MAP_P0_MSK                          (0x00000001)
  #define MC0_MAD_INTRA_CH0_DIMM_L_MAP_P0_MIN                          (0)
  #define MC0_MAD_INTRA_CH0_DIMM_L_MAP_P0_MAX                          (1) // 0x00000001
  #define MC0_MAD_INTRA_CH0_DIMM_L_MAP_P0_DEF                          (0x00000000)
  #define MC0_MAD_INTRA_CH0_DIMM_L_MAP_P0_HSH                          (0x0100D804)

  #define MC0_MAD_INTRA_CH0_EIM_P0_OFF                                 ( 8)
  #define MC0_MAD_INTRA_CH0_EIM_P0_WID                                 ( 1)
  #define MC0_MAD_INTRA_CH0_EIM_P0_MSK                                 (0x00000100)
  #define MC0_MAD_INTRA_CH0_EIM_P0_MIN                                 (0)
  #define MC0_MAD_INTRA_CH0_EIM_P0_MAX                                 (1) // 0x00000001
  #define MC0_MAD_INTRA_CH0_EIM_P0_DEF                                 (0x00000000)
  #define MC0_MAD_INTRA_CH0_EIM_P0_HSH                                 (0x0110D804)

  #define MC0_MAD_INTRA_CH0_ECC_P0_OFF                                 (12)
  #define MC0_MAD_INTRA_CH0_ECC_P0_WID                                 ( 2)
  #define MC0_MAD_INTRA_CH0_ECC_P0_MSK                                 (0x00003000)
  #define MC0_MAD_INTRA_CH0_ECC_P0_MIN                                 (0)
  #define MC0_MAD_INTRA_CH0_ECC_P0_MAX                                 (3) // 0x00000003
  #define MC0_MAD_INTRA_CH0_ECC_P0_DEF                                 (0x00000000)
  #define MC0_MAD_INTRA_CH0_ECC_P0_HSH                                 (0x0218D804)

  #define MC0_MAD_INTRA_CH0_CRC_P0_OFF                                 (14)
  #define MC0_MAD_INTRA_CH0_CRC_P0_WID                                 ( 1)
  #define MC0_MAD_INTRA_CH0_CRC_P0_MSK                                 (0x00004000)
  #define MC0_MAD_INTRA_CH0_CRC_P0_MIN                                 (0)
  #define MC0_MAD_INTRA_CH0_CRC_P0_MAX                                 (1) // 0x00000001
  #define MC0_MAD_INTRA_CH0_CRC_P0_DEF                                 (0x00000000)
  #define MC0_MAD_INTRA_CH0_CRC_P0_HSH                                 (0x011CD804)

#define MC0_MAD_INTRA_CH1_P0_REG                                       (0x0000D808)
//Duplicate of MC0_MAD_INTRA_CH0_P0_REG

#define MC0_MAD_DIMM_CH0_P0_REG                                        (0x0000D80C)

  #define MC0_MAD_DIMM_CH0_DIMM_L_SIZE_P0_OFF                          ( 0)
  #define MC0_MAD_DIMM_CH0_DIMM_L_SIZE_P0_WID                          ( 7)
  #define MC0_MAD_DIMM_CH0_DIMM_L_SIZE_P0_MSK                          (0x0000007F)
  #define MC0_MAD_DIMM_CH0_DIMM_L_SIZE_P0_MIN                          (0)
  #define MC0_MAD_DIMM_CH0_DIMM_L_SIZE_P0_MAX                          (127) // 0x0000007F
  #define MC0_MAD_DIMM_CH0_DIMM_L_SIZE_P0_DEF                          (0x00000000)
  #define MC0_MAD_DIMM_CH0_DIMM_L_SIZE_P0_HSH                          (0x0700D80C)

  #define MC0_MAD_DIMM_CH0_DLW_P0_OFF                                  ( 7)
  #define MC0_MAD_DIMM_CH0_DLW_P0_WID                                  ( 2)
  #define MC0_MAD_DIMM_CH0_DLW_P0_MSK                                  (0x00000180)
  #define MC0_MAD_DIMM_CH0_DLW_P0_MIN                                  (0)
  #define MC0_MAD_DIMM_CH0_DLW_P0_MAX                                  (3) // 0x00000003
  #define MC0_MAD_DIMM_CH0_DLW_P0_DEF                                  (0x00000000)
  #define MC0_MAD_DIMM_CH0_DLW_P0_HSH                                  (0x020ED80C)

  #define MC0_MAD_DIMM_CH0_DLNOR_P0_OFF                                ( 9)
  #define MC0_MAD_DIMM_CH0_DLNOR_P0_WID                                ( 2)
  #define MC0_MAD_DIMM_CH0_DLNOR_P0_MSK                                (0x00000600)
  #define MC0_MAD_DIMM_CH0_DLNOR_P0_MIN                                (0)
  #define MC0_MAD_DIMM_CH0_DLNOR_P0_MAX                                (3) // 0x00000003
  #define MC0_MAD_DIMM_CH0_DLNOR_P0_DEF                                (0x00000000)
  #define MC0_MAD_DIMM_CH0_DLNOR_P0_HSH                                (0x0212D80C)

  #define MC0_MAD_DIMM_CH0_DIMM_S_SIZE_P0_OFF                          (16)
  #define MC0_MAD_DIMM_CH0_DIMM_S_SIZE_P0_WID                          ( 7)
  #define MC0_MAD_DIMM_CH0_DIMM_S_SIZE_P0_MSK                          (0x007F0000)
  #define MC0_MAD_DIMM_CH0_DIMM_S_SIZE_P0_MIN                          (0)
  #define MC0_MAD_DIMM_CH0_DIMM_S_SIZE_P0_MAX                          (127) // 0x0000007F
  #define MC0_MAD_DIMM_CH0_DIMM_S_SIZE_P0_DEF                          (0x00000000)
  #define MC0_MAD_DIMM_CH0_DIMM_S_SIZE_P0_HSH                          (0x0720D80C)

  #define MC0_MAD_DIMM_CH0_DSW_P0_OFF                                  (24)
  #define MC0_MAD_DIMM_CH0_DSW_P0_WID                                  ( 2)
  #define MC0_MAD_DIMM_CH0_DSW_P0_MSK                                  (0x03000000)
  #define MC0_MAD_DIMM_CH0_DSW_P0_MIN                                  (0)
  #define MC0_MAD_DIMM_CH0_DSW_P0_MAX                                  (3) // 0x00000003
  #define MC0_MAD_DIMM_CH0_DSW_P0_DEF                                  (0x00000000)
  #define MC0_MAD_DIMM_CH0_DSW_P0_HSH                                  (0x0230D80C)

  #define MC0_MAD_DIMM_CH0_DSNOR_P0_OFF                                (26)
  #define MC0_MAD_DIMM_CH0_DSNOR_P0_WID                                ( 2)
  #define MC0_MAD_DIMM_CH0_DSNOR_P0_MSK                                (0x0C000000)
  #define MC0_MAD_DIMM_CH0_DSNOR_P0_MIN                                (0)
  #define MC0_MAD_DIMM_CH0_DSNOR_P0_MAX                                (3) // 0x00000003
  #define MC0_MAD_DIMM_CH0_DSNOR_P0_DEF                                (0x00000000)
  #define MC0_MAD_DIMM_CH0_DSNOR_P0_HSH                                (0x0234D80C)

  #define MC0_MAD_DIMM_CH0_DLS_BG0_on_bit_11_P0_OFF                    (29)
  #define MC0_MAD_DIMM_CH0_DLS_BG0_on_bit_11_P0_WID                    ( 1)
  #define MC0_MAD_DIMM_CH0_DLS_BG0_on_bit_11_P0_MSK                    (0x20000000)
  #define MC0_MAD_DIMM_CH0_DLS_BG0_on_bit_11_P0_MIN                    (0)
  #define MC0_MAD_DIMM_CH0_DLS_BG0_on_bit_11_P0_MAX                    (1) // 0x00000001
  #define MC0_MAD_DIMM_CH0_DLS_BG0_on_bit_11_P0_DEF                    (0x00000000)
  #define MC0_MAD_DIMM_CH0_DLS_BG0_on_bit_11_P0_HSH                    (0x013AD80C)

  #define MC0_MAD_DIMM_CH0_ddr5_device_8Gb_P0_OFF                      (30)
  #define MC0_MAD_DIMM_CH0_ddr5_device_8Gb_P0_WID                      ( 1)
  #define MC0_MAD_DIMM_CH0_ddr5_device_8Gb_P0_MSK                      (0x40000000)
  #define MC0_MAD_DIMM_CH0_ddr5_device_8Gb_P0_MIN                      (0)
  #define MC0_MAD_DIMM_CH0_ddr5_device_8Gb_P0_MAX                      (1) // 0x00000001
  #define MC0_MAD_DIMM_CH0_ddr5_device_8Gb_P0_DEF                      (0x00000001)
  #define MC0_MAD_DIMM_CH0_ddr5_device_8Gb_P0_HSH                      (0x013CD80C)

#define MC0_MAD_DIMM_CH1_P0_REG                                        (0x0000D810)
//Duplicate of MC0_MAD_DIMM_CH0_P0_REG

#define MC0_MCDECS_MISC_P0_REG                                         (0x0000D818)

  #define MC0_MCDECS_MISC_Spare_RW_P0_OFF                              ( 0)
  #define MC0_MCDECS_MISC_Spare_RW_P0_WID                              (12)
  #define MC0_MCDECS_MISC_Spare_RW_P0_MSK                              (0x00000FFF)
  #define MC0_MCDECS_MISC_Spare_RW_P0_MIN                              (0)
  #define MC0_MCDECS_MISC_Spare_RW_P0_MAX                              (4095) // 0x00000FFF
  #define MC0_MCDECS_MISC_Spare_RW_P0_DEF                              (0x00000000)
  #define MC0_MCDECS_MISC_Spare_RW_P0_HSH                              (0x0C00D818)

  #define MC0_MCDECS_MISC_VISAByteSel_P0_OFF                           (12)
  #define MC0_MCDECS_MISC_VISAByteSel_P0_WID                           ( 4)
  #define MC0_MCDECS_MISC_VISAByteSel_P0_MSK                           (0x0000F000)
  #define MC0_MCDECS_MISC_VISAByteSel_P0_MIN                           (0)
  #define MC0_MCDECS_MISC_VISAByteSel_P0_MAX                           (15) // 0x0000000F
  #define MC0_MCDECS_MISC_VISAByteSel_P0_DEF                           (0x00000000)
  #define MC0_MCDECS_MISC_VISAByteSel_P0_HSH                           (0x0418D818)

  #define MC0_MCDECS_MISC_spare_RW_V_P0_OFF                            (16)
  #define MC0_MCDECS_MISC_spare_RW_V_P0_WID                            (16)
  #define MC0_MCDECS_MISC_spare_RW_V_P0_MSK                            (0xFFFF0000)
  #define MC0_MCDECS_MISC_spare_RW_V_P0_MIN                            (0)
  #define MC0_MCDECS_MISC_spare_RW_V_P0_MAX                            (65535) // 0x0000FFFF
  #define MC0_MCDECS_MISC_spare_RW_V_P0_DEF                            (0x00000000)
  #define MC0_MCDECS_MISC_spare_RW_V_P0_HSH                            (0x1020D818)

#define MC0_MCDECS_CBIT_P0_REG                                         (0x0000D81C)

  #define MC0_MCDECS_CBIT_increase_rcomp_P0_OFF                        ( 0)
  #define MC0_MCDECS_CBIT_increase_rcomp_P0_WID                        ( 1)
  #define MC0_MCDECS_CBIT_increase_rcomp_P0_MSK                        (0x00000001)
  #define MC0_MCDECS_CBIT_increase_rcomp_P0_MIN                        (0)
  #define MC0_MCDECS_CBIT_increase_rcomp_P0_MAX                        (1) // 0x00000001
  #define MC0_MCDECS_CBIT_increase_rcomp_P0_DEF                        (0x00000000)
  #define MC0_MCDECS_CBIT_increase_rcomp_P0_HSH                        (0x0100D81C)

  #define MC0_MCDECS_CBIT_rank2_to_rank1_P0_OFF                        ( 1)
  #define MC0_MCDECS_CBIT_rank2_to_rank1_P0_WID                        ( 1)
  #define MC0_MCDECS_CBIT_rank2_to_rank1_P0_MSK                        (0x00000002)
  #define MC0_MCDECS_CBIT_rank2_to_rank1_P0_MIN                        (0)
  #define MC0_MCDECS_CBIT_rank2_to_rank1_P0_MAX                        (1) // 0x00000001
  #define MC0_MCDECS_CBIT_rank2_to_rank1_P0_DEF                        (0x00000000)
  #define MC0_MCDECS_CBIT_rank2_to_rank1_P0_HSH                        (0x0102D81C)

  #define MC0_MCDECS_CBIT_ovrd_pcu_sr_exit_P0_OFF                      ( 2)
  #define MC0_MCDECS_CBIT_ovrd_pcu_sr_exit_P0_WID                      ( 1)
  #define MC0_MCDECS_CBIT_ovrd_pcu_sr_exit_P0_MSK                      (0x00000004)
  #define MC0_MCDECS_CBIT_ovrd_pcu_sr_exit_P0_MIN                      (0)
  #define MC0_MCDECS_CBIT_ovrd_pcu_sr_exit_P0_MAX                      (1) // 0x00000001
  #define MC0_MCDECS_CBIT_ovrd_pcu_sr_exit_P0_DEF                      (0x00000000)
  #define MC0_MCDECS_CBIT_ovrd_pcu_sr_exit_P0_HSH                      (0x0104D81C)

  #define MC0_MCDECS_CBIT_psmi_freeze_pwm_counters_P0_OFF              ( 3)
  #define MC0_MCDECS_CBIT_psmi_freeze_pwm_counters_P0_WID              ( 1)
  #define MC0_MCDECS_CBIT_psmi_freeze_pwm_counters_P0_MSK              (0x00000008)
  #define MC0_MCDECS_CBIT_psmi_freeze_pwm_counters_P0_MIN              (0)
  #define MC0_MCDECS_CBIT_psmi_freeze_pwm_counters_P0_MAX              (1) // 0x00000001
  #define MC0_MCDECS_CBIT_psmi_freeze_pwm_counters_P0_DEF              (0x00000000)
  #define MC0_MCDECS_CBIT_psmi_freeze_pwm_counters_P0_HSH              (0x0106D81C)

  #define MC0_MCDECS_CBIT_dis_single_ch_sr_P0_OFF                      ( 4)
  #define MC0_MCDECS_CBIT_dis_single_ch_sr_P0_WID                      ( 1)
  #define MC0_MCDECS_CBIT_dis_single_ch_sr_P0_MSK                      (0x00000010)
  #define MC0_MCDECS_CBIT_dis_single_ch_sr_P0_MIN                      (0)
  #define MC0_MCDECS_CBIT_dis_single_ch_sr_P0_MAX                      (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_single_ch_sr_P0_DEF                      (0x00000001)
  #define MC0_MCDECS_CBIT_dis_single_ch_sr_P0_HSH                      (0x0108D81C)

  #define MC0_MCDECS_CBIT_dis_other_ch_stolen_ref_P0_OFF               ( 5)
  #define MC0_MCDECS_CBIT_dis_other_ch_stolen_ref_P0_WID               ( 1)
  #define MC0_MCDECS_CBIT_dis_other_ch_stolen_ref_P0_MSK               (0x00000020)
  #define MC0_MCDECS_CBIT_dis_other_ch_stolen_ref_P0_MIN               (0)
  #define MC0_MCDECS_CBIT_dis_other_ch_stolen_ref_P0_MAX               (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_other_ch_stolen_ref_P0_DEF               (0x00000001)
  #define MC0_MCDECS_CBIT_dis_other_ch_stolen_ref_P0_HSH               (0x010AD81C)

  #define MC0_MCDECS_CBIT_ForceSREntry_dft_P0_OFF                      ( 6)
  #define MC0_MCDECS_CBIT_ForceSREntry_dft_P0_WID                      ( 1)
  #define MC0_MCDECS_CBIT_ForceSREntry_dft_P0_MSK                      (0x00000040)
  #define MC0_MCDECS_CBIT_ForceSREntry_dft_P0_MIN                      (0)
  #define MC0_MCDECS_CBIT_ForceSREntry_dft_P0_MAX                      (1) // 0x00000001
  #define MC0_MCDECS_CBIT_ForceSREntry_dft_P0_DEF                      (0x00000000)
  #define MC0_MCDECS_CBIT_ForceSREntry_dft_P0_HSH                      (0x010CD81C)

  #define MC0_MCDECS_CBIT_reserved_P0_OFF                              ( 7)
  #define MC0_MCDECS_CBIT_reserved_P0_WID                              ( 2)
  #define MC0_MCDECS_CBIT_reserved_P0_MSK                              (0x00000180)
  #define MC0_MCDECS_CBIT_reserved_P0_MIN                              (0)
  #define MC0_MCDECS_CBIT_reserved_P0_MAX                              (3) // 0x00000003
  #define MC0_MCDECS_CBIT_reserved_P0_DEF                              (0x00000000)
  #define MC0_MCDECS_CBIT_reserved_P0_HSH                              (0x020ED81C)

  #define MC0_MCDECS_CBIT_ForceSREntry_dft_is_sticky_P0_OFF            ( 9)
  #define MC0_MCDECS_CBIT_ForceSREntry_dft_is_sticky_P0_WID            ( 1)
  #define MC0_MCDECS_CBIT_ForceSREntry_dft_is_sticky_P0_MSK            (0x00000200)
  #define MC0_MCDECS_CBIT_ForceSREntry_dft_is_sticky_P0_MIN            (0)
  #define MC0_MCDECS_CBIT_ForceSREntry_dft_is_sticky_P0_MAX            (1) // 0x00000001
  #define MC0_MCDECS_CBIT_ForceSREntry_dft_is_sticky_P0_DEF            (0x00000001)
  #define MC0_MCDECS_CBIT_ForceSREntry_dft_is_sticky_P0_HSH            (0x0112D81C)

  #define MC0_MCDECS_CBIT_iosfsb_keep_ISM_active_P0_OFF                (11)
  #define MC0_MCDECS_CBIT_iosfsb_keep_ISM_active_P0_WID                ( 1)
  #define MC0_MCDECS_CBIT_iosfsb_keep_ISM_active_P0_MSK                (0x00000800)
  #define MC0_MCDECS_CBIT_iosfsb_keep_ISM_active_P0_MIN                (0)
  #define MC0_MCDECS_CBIT_iosfsb_keep_ISM_active_P0_MAX                (1) // 0x00000001
  #define MC0_MCDECS_CBIT_iosfsb_keep_ISM_active_P0_DEF                (0x00000000)
  #define MC0_MCDECS_CBIT_iosfsb_keep_ISM_active_P0_HSH                (0x0116D81C)

  #define MC0_MCDECS_CBIT_ignoreRefBetweenSRX2SRE_P0_OFF               (12)
  #define MC0_MCDECS_CBIT_ignoreRefBetweenSRX2SRE_P0_WID               ( 1)
  #define MC0_MCDECS_CBIT_ignoreRefBetweenSRX2SRE_P0_MSK               (0x00001000)
  #define MC0_MCDECS_CBIT_ignoreRefBetweenSRX2SRE_P0_MIN               (0)
  #define MC0_MCDECS_CBIT_ignoreRefBetweenSRX2SRE_P0_MAX               (1) // 0x00000001
  #define MC0_MCDECS_CBIT_ignoreRefBetweenSRX2SRE_P0_DEF               (0x00000000)
  #define MC0_MCDECS_CBIT_ignoreRefBetweenSRX2SRE_P0_HSH               (0x0118D81C)

  #define MC0_MCDECS_CBIT_dis_cmi_spec_req_early_valid_P0_OFF          (14)
  #define MC0_MCDECS_CBIT_dis_cmi_spec_req_early_valid_P0_WID          ( 1)
  #define MC0_MCDECS_CBIT_dis_cmi_spec_req_early_valid_P0_MSK          (0x00004000)
  #define MC0_MCDECS_CBIT_dis_cmi_spec_req_early_valid_P0_MIN          (0)
  #define MC0_MCDECS_CBIT_dis_cmi_spec_req_early_valid_P0_MAX          (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_cmi_spec_req_early_valid_P0_DEF          (0x00000000)
  #define MC0_MCDECS_CBIT_dis_cmi_spec_req_early_valid_P0_HSH          (0x011CD81C)

  #define MC0_MCDECS_CBIT_Dis_EFLOW_fwd_data_hack_P0_OFF               (15)
  #define MC0_MCDECS_CBIT_Dis_EFLOW_fwd_data_hack_P0_WID               ( 1)
  #define MC0_MCDECS_CBIT_Dis_EFLOW_fwd_data_hack_P0_MSK               (0x00008000)
  #define MC0_MCDECS_CBIT_Dis_EFLOW_fwd_data_hack_P0_MIN               (0)
  #define MC0_MCDECS_CBIT_Dis_EFLOW_fwd_data_hack_P0_MAX               (1) // 0x00000001
  #define MC0_MCDECS_CBIT_Dis_EFLOW_fwd_data_hack_P0_DEF               (0x00000000)
  #define MC0_MCDECS_CBIT_Dis_EFLOW_fwd_data_hack_P0_HSH               (0x011ED81C)

  #define MC0_MCDECS_CBIT_freeze_visa_values_P0_OFF                    (16)
  #define MC0_MCDECS_CBIT_freeze_visa_values_P0_WID                    ( 1)
  #define MC0_MCDECS_CBIT_freeze_visa_values_P0_MSK                    (0x00010000)
  #define MC0_MCDECS_CBIT_freeze_visa_values_P0_MIN                    (0)
  #define MC0_MCDECS_CBIT_freeze_visa_values_P0_MAX                    (1) // 0x00000001
  #define MC0_MCDECS_CBIT_freeze_visa_values_P0_DEF                    (0x00000000)
  #define MC0_MCDECS_CBIT_freeze_visa_values_P0_HSH                    (0x0120D81C)

  #define MC0_MCDECS_CBIT_freeze_visa_values_on_RTB_P0_OFF             (17)
  #define MC0_MCDECS_CBIT_freeze_visa_values_on_RTB_P0_WID             ( 1)
  #define MC0_MCDECS_CBIT_freeze_visa_values_on_RTB_P0_MSK             (0x00020000)
  #define MC0_MCDECS_CBIT_freeze_visa_values_on_RTB_P0_MIN             (0)
  #define MC0_MCDECS_CBIT_freeze_visa_values_on_RTB_P0_MAX             (1) // 0x00000001
  #define MC0_MCDECS_CBIT_freeze_visa_values_on_RTB_P0_DEF             (0x00000000)
  #define MC0_MCDECS_CBIT_freeze_visa_values_on_RTB_P0_HSH             (0x0122D81C)

  #define MC0_MCDECS_CBIT_dis_cmi_ep_power_flows_P0_OFF                (18)
  #define MC0_MCDECS_CBIT_dis_cmi_ep_power_flows_P0_WID                ( 1)
  #define MC0_MCDECS_CBIT_dis_cmi_ep_power_flows_P0_MSK                (0x00040000)
  #define MC0_MCDECS_CBIT_dis_cmi_ep_power_flows_P0_MIN                (0)
  #define MC0_MCDECS_CBIT_dis_cmi_ep_power_flows_P0_MAX                (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_cmi_ep_power_flows_P0_DEF                (0x00000000)
  #define MC0_MCDECS_CBIT_dis_cmi_ep_power_flows_P0_HSH                (0x0124D81C)

  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_opcodes_P0_OFF             (19)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_opcodes_P0_WID             ( 1)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_opcodes_P0_MSK             (0x00080000)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_opcodes_P0_MIN             (0)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_opcodes_P0_MAX             (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_opcodes_P0_DEF             (0x00000000)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_opcodes_P0_HSH             (0x0126D81C)

  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_bar_P0_OFF                 (20)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_bar_P0_WID                 ( 1)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_bar_P0_MSK                 (0x00100000)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_bar_P0_MIN                 (0)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_bar_P0_MAX                 (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_bar_P0_DEF                 (0x00000000)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_bar_P0_HSH                 (0x0128D81C)

  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_range_P0_OFF               (21)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_range_P0_WID               ( 1)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_range_P0_MSK               (0x00200000)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_range_P0_MIN               (0)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_range_P0_MAX               (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_range_P0_DEF               (0x00000000)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_range_P0_HSH               (0x012AD81C)

  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_sai_P0_OFF                 (22)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_sai_P0_WID                 ( 1)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_sai_P0_MSK                 (0x00400000)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_sai_P0_MIN                 (0)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_sai_P0_MAX                 (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_sai_P0_DEF                 (0x00000000)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_error_sai_P0_HSH                 (0x012CD81C)

  #define MC0_MCDECS_CBIT_delay_normal_mode_when_temp_read_P0_OFF      (23)
  #define MC0_MCDECS_CBIT_delay_normal_mode_when_temp_read_P0_WID      ( 1)
  #define MC0_MCDECS_CBIT_delay_normal_mode_when_temp_read_P0_MSK      (0x00800000)
  #define MC0_MCDECS_CBIT_delay_normal_mode_when_temp_read_P0_MIN      (0)
  #define MC0_MCDECS_CBIT_delay_normal_mode_when_temp_read_P0_MAX      (1) // 0x00000001
  #define MC0_MCDECS_CBIT_delay_normal_mode_when_temp_read_P0_DEF      (0x00000000)
  #define MC0_MCDECS_CBIT_delay_normal_mode_when_temp_read_P0_HSH      (0x012ED81C)

  #define MC0_MCDECS_CBIT_dis_cmi_spec_rsp_cpl_early_valid_P0_OFF      (24)
  #define MC0_MCDECS_CBIT_dis_cmi_spec_rsp_cpl_early_valid_P0_WID      ( 1)
  #define MC0_MCDECS_CBIT_dis_cmi_spec_rsp_cpl_early_valid_P0_MSK      (0x01000000)
  #define MC0_MCDECS_CBIT_dis_cmi_spec_rsp_cpl_early_valid_P0_MIN      (0)
  #define MC0_MCDECS_CBIT_dis_cmi_spec_rsp_cpl_early_valid_P0_MAX      (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_cmi_spec_rsp_cpl_early_valid_P0_DEF      (0x00000000)
  #define MC0_MCDECS_CBIT_dis_cmi_spec_rsp_cpl_early_valid_P0_HSH      (0x0130D81C)

  #define MC0_MCDECS_CBIT_force_sb_ep_clk_req_P0_OFF                   (25)
  #define MC0_MCDECS_CBIT_force_sb_ep_clk_req_P0_WID                   ( 1)
  #define MC0_MCDECS_CBIT_force_sb_ep_clk_req_P0_MSK                   (0x02000000)
  #define MC0_MCDECS_CBIT_force_sb_ep_clk_req_P0_MIN                   (0)
  #define MC0_MCDECS_CBIT_force_sb_ep_clk_req_P0_MAX                   (1) // 0x00000001
  #define MC0_MCDECS_CBIT_force_sb_ep_clk_req_P0_DEF                   (0x00000000)
  #define MC0_MCDECS_CBIT_force_sb_ep_clk_req_P0_HSH                   (0x0132D81C)

  #define MC0_MCDECS_CBIT_dis_cmi_wr_rsp_P0_OFF                        (26)
  #define MC0_MCDECS_CBIT_dis_cmi_wr_rsp_P0_WID                        ( 1)
  #define MC0_MCDECS_CBIT_dis_cmi_wr_rsp_P0_MSK                        (0x04000000)
  #define MC0_MCDECS_CBIT_dis_cmi_wr_rsp_P0_MIN                        (0)
  #define MC0_MCDECS_CBIT_dis_cmi_wr_rsp_P0_MAX                        (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_cmi_wr_rsp_P0_DEF                        (0x00000000)
  #define MC0_MCDECS_CBIT_dis_cmi_wr_rsp_P0_HSH                        (0x0134D81C)

  #define MC0_MCDECS_CBIT_dis_iosf_sb_clk_gate_P0_OFF                  (27)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_clk_gate_P0_WID                  ( 1)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_clk_gate_P0_MSK                  (0x08000000)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_clk_gate_P0_MIN                  (0)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_clk_gate_P0_MAX                  (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_iosf_sb_clk_gate_P0_DEF                  (0x00000000)
  #define MC0_MCDECS_CBIT_dis_iosf_sb_clk_gate_P0_HSH                  (0x0136D81C)

  #define MC0_MCDECS_CBIT_dis_glbdrv_clk_gate_P0_OFF                   (28)
  #define MC0_MCDECS_CBIT_dis_glbdrv_clk_gate_P0_WID                   ( 1)
  #define MC0_MCDECS_CBIT_dis_glbdrv_clk_gate_P0_MSK                   (0x10000000)
  #define MC0_MCDECS_CBIT_dis_glbdrv_clk_gate_P0_MIN                   (0)
  #define MC0_MCDECS_CBIT_dis_glbdrv_clk_gate_P0_MAX                   (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_glbdrv_clk_gate_P0_DEF                   (0x00000000)
  #define MC0_MCDECS_CBIT_dis_glbdrv_clk_gate_P0_HSH                   (0x0138D81C)

  #define MC0_MCDECS_CBIT_dis_reg_clk_gate_P0_OFF                      (29)
  #define MC0_MCDECS_CBIT_dis_reg_clk_gate_P0_WID                      ( 1)
  #define MC0_MCDECS_CBIT_dis_reg_clk_gate_P0_MSK                      (0x20000000)
  #define MC0_MCDECS_CBIT_dis_reg_clk_gate_P0_MIN                      (0)
  #define MC0_MCDECS_CBIT_dis_reg_clk_gate_P0_MAX                      (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_reg_clk_gate_P0_DEF                      (0x00000000)
  #define MC0_MCDECS_CBIT_dis_reg_clk_gate_P0_HSH                      (0x013AD81C)

  #define MC0_MCDECS_CBIT_dis_clk_gate_P0_OFF                          (31)
  #define MC0_MCDECS_CBIT_dis_clk_gate_P0_WID                          ( 1)
  #define MC0_MCDECS_CBIT_dis_clk_gate_P0_MSK                          (0x80000000)
  #define MC0_MCDECS_CBIT_dis_clk_gate_P0_MIN                          (0)
  #define MC0_MCDECS_CBIT_dis_clk_gate_P0_MAX                          (1) // 0x00000001
  #define MC0_MCDECS_CBIT_dis_clk_gate_P0_DEF                          (0x00000000)
  #define MC0_MCDECS_CBIT_dis_clk_gate_P0_HSH                          (0x013ED81C)

#define MC0_CHANNEL_HASH_P0_REG                                        (0x0000D824)

  #define MC0_CHANNEL_HASH_HASH_MASK_P0_OFF                            ( 6)
  #define MC0_CHANNEL_HASH_HASH_MASK_P0_WID                            (14)
  #define MC0_CHANNEL_HASH_HASH_MASK_P0_MSK                            (0x000FFFC0)
  #define MC0_CHANNEL_HASH_HASH_MASK_P0_MIN                            (0)
  #define MC0_CHANNEL_HASH_HASH_MASK_P0_MAX                            (16383) // 0x00003FFF
  #define MC0_CHANNEL_HASH_HASH_MASK_P0_DEF                            (0x00000000)
  #define MC0_CHANNEL_HASH_HASH_MASK_P0_HSH                            (0x0E0CD824)

  #define MC0_CHANNEL_HASH_HASH_LSB_MASK_BIT_P0_OFF                    (24)
  #define MC0_CHANNEL_HASH_HASH_LSB_MASK_BIT_P0_WID                    ( 3)
  #define MC0_CHANNEL_HASH_HASH_LSB_MASK_BIT_P0_MSK                    (0x07000000)
  #define MC0_CHANNEL_HASH_HASH_LSB_MASK_BIT_P0_MIN                    (0)
  #define MC0_CHANNEL_HASH_HASH_LSB_MASK_BIT_P0_MAX                    (7) // 0x00000007
  #define MC0_CHANNEL_HASH_HASH_LSB_MASK_BIT_P0_DEF                    (0x00000000)
  #define MC0_CHANNEL_HASH_HASH_LSB_MASK_BIT_P0_HSH                    (0x0330D824)

  #define MC0_CHANNEL_HASH_HASH_MODE_P0_OFF                            (28)
  #define MC0_CHANNEL_HASH_HASH_MODE_P0_WID                            ( 1)
  #define MC0_CHANNEL_HASH_HASH_MODE_P0_MSK                            (0x10000000)
  #define MC0_CHANNEL_HASH_HASH_MODE_P0_MIN                            (0)
  #define MC0_CHANNEL_HASH_HASH_MODE_P0_MAX                            (1) // 0x00000001
  #define MC0_CHANNEL_HASH_HASH_MODE_P0_DEF                            (0x00000000)
  #define MC0_CHANNEL_HASH_HASH_MODE_P0_HSH                            (0x0138D824)

#define MC0_CHANNEL_EHASH_P0_REG                                       (0x0000D828)

  #define MC0_CHANNEL_EHASH_EHASH_MASK_P0_OFF                          ( 6)
  #define MC0_CHANNEL_EHASH_EHASH_MASK_P0_WID                          (14)
  #define MC0_CHANNEL_EHASH_EHASH_MASK_P0_MSK                          (0x000FFFC0)
  #define MC0_CHANNEL_EHASH_EHASH_MASK_P0_MIN                          (0)
  #define MC0_CHANNEL_EHASH_EHASH_MASK_P0_MAX                          (16383) // 0x00003FFF
  #define MC0_CHANNEL_EHASH_EHASH_MASK_P0_DEF                          (0x00000000)
  #define MC0_CHANNEL_EHASH_EHASH_MASK_P0_HSH                          (0x0E0CD828)

  #define MC0_CHANNEL_EHASH_EHASH_LSB_MASK_BIT_P0_OFF                  (24)
  #define MC0_CHANNEL_EHASH_EHASH_LSB_MASK_BIT_P0_WID                  ( 3)
  #define MC0_CHANNEL_EHASH_EHASH_LSB_MASK_BIT_P0_MSK                  (0x07000000)
  #define MC0_CHANNEL_EHASH_EHASH_LSB_MASK_BIT_P0_MIN                  (0)
  #define MC0_CHANNEL_EHASH_EHASH_LSB_MASK_BIT_P0_MAX                  (7) // 0x00000007
  #define MC0_CHANNEL_EHASH_EHASH_LSB_MASK_BIT_P0_DEF                  (0x00000000)
  #define MC0_CHANNEL_EHASH_EHASH_LSB_MASK_BIT_P0_HSH                  (0x0330D828)

  #define MC0_CHANNEL_EHASH_EHASH_MODE_P0_OFF                          (28)
  #define MC0_CHANNEL_EHASH_EHASH_MODE_P0_WID                          ( 1)
  #define MC0_CHANNEL_EHASH_EHASH_MODE_P0_MSK                          (0x10000000)
  #define MC0_CHANNEL_EHASH_EHASH_MODE_P0_MIN                          (0)
  #define MC0_CHANNEL_EHASH_EHASH_MODE_P0_MAX                          (1) // 0x00000001
  #define MC0_CHANNEL_EHASH_EHASH_MODE_P0_DEF                          (0x00000000)
  #define MC0_CHANNEL_EHASH_EHASH_MODE_P0_HSH                          (0x0138D828)

#define MC0_MC_INIT_STATE_G_P0_REG                                     (0x0000D830)

  #define MC0_MC_INIT_STATE_G_ddr_reset_P0_OFF                         ( 1)
  #define MC0_MC_INIT_STATE_G_ddr_reset_P0_WID                         ( 1)
  #define MC0_MC_INIT_STATE_G_ddr_reset_P0_MSK                         (0x00000002)
  #define MC0_MC_INIT_STATE_G_ddr_reset_P0_MIN                         (0)
  #define MC0_MC_INIT_STATE_G_ddr_reset_P0_MAX                         (1) // 0x00000001
  #define MC0_MC_INIT_STATE_G_ddr_reset_P0_DEF                         (0x00000001)
  #define MC0_MC_INIT_STATE_G_ddr_reset_P0_HSH                         (0x0102D830)

  #define MC0_MC_INIT_STATE_G_refresh_enable_P0_OFF                    ( 3)
  #define MC0_MC_INIT_STATE_G_refresh_enable_P0_WID                    ( 1)
  #define MC0_MC_INIT_STATE_G_refresh_enable_P0_MSK                    (0x00000008)
  #define MC0_MC_INIT_STATE_G_refresh_enable_P0_MIN                    (0)
  #define MC0_MC_INIT_STATE_G_refresh_enable_P0_MAX                    (1) // 0x00000001
  #define MC0_MC_INIT_STATE_G_refresh_enable_P0_DEF                    (0x00000000)
  #define MC0_MC_INIT_STATE_G_refresh_enable_P0_HSH                    (0x0106D830)

  #define MC0_MC_INIT_STATE_G_mc_init_done_ack_P0_OFF                  ( 5)
  #define MC0_MC_INIT_STATE_G_mc_init_done_ack_P0_WID                  ( 1)
  #define MC0_MC_INIT_STATE_G_mc_init_done_ack_P0_MSK                  (0x00000020)
  #define MC0_MC_INIT_STATE_G_mc_init_done_ack_P0_MIN                  (0)
  #define MC0_MC_INIT_STATE_G_mc_init_done_ack_P0_MAX                  (1) // 0x00000001
  #define MC0_MC_INIT_STATE_G_mc_init_done_ack_P0_DEF                  (0x00000000)
  #define MC0_MC_INIT_STATE_G_mc_init_done_ack_P0_HSH                  (0x010AD830)

  #define MC0_MC_INIT_STATE_G_mrc_done_P0_OFF                          ( 7)
  #define MC0_MC_INIT_STATE_G_mrc_done_P0_WID                          ( 1)
  #define MC0_MC_INIT_STATE_G_mrc_done_P0_MSK                          (0x00000080)
  #define MC0_MC_INIT_STATE_G_mrc_done_P0_MIN                          (0)
  #define MC0_MC_INIT_STATE_G_mrc_done_P0_MAX                          (1) // 0x00000001
  #define MC0_MC_INIT_STATE_G_mrc_done_P0_DEF                          (0x00000000)
  #define MC0_MC_INIT_STATE_G_mrc_done_P0_HSH                          (0x010ED830)

  #define MC0_MC_INIT_STATE_G_pure_srx_P0_OFF                          ( 9)
  #define MC0_MC_INIT_STATE_G_pure_srx_P0_WID                          ( 1)
  #define MC0_MC_INIT_STATE_G_pure_srx_P0_MSK                          (0x00000200)
  #define MC0_MC_INIT_STATE_G_pure_srx_P0_MIN                          (0)
  #define MC0_MC_INIT_STATE_G_pure_srx_P0_MAX                          (1) // 0x00000001
  #define MC0_MC_INIT_STATE_G_pure_srx_P0_DEF                          (0x00000000)
  #define MC0_MC_INIT_STATE_G_pure_srx_P0_HSH                          (0x0112D830)

  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_0_P0_OFF               (11)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_0_P0_WID               ( 1)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_0_P0_MSK               (0x00000800)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_0_P0_MIN               (0)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_0_P0_MAX               (1) // 0x00000001
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_0_P0_DEF               (0x00000000)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_0_P0_HSH               (0x0116D830)

  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_1_P0_OFF               (12)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_1_P0_WID               ( 1)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_1_P0_MSK               (0x00001000)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_1_P0_MIN               (0)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_1_P0_MAX               (1) // 0x00000001
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_1_P0_DEF               (0x00000000)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_1_P0_HSH               (0x0118D830)

  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_2_P0_OFF               (13)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_2_P0_WID               ( 1)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_2_P0_MSK               (0x00002000)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_2_P0_MIN               (0)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_2_P0_MAX               (1) // 0x00000001
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_2_P0_DEF               (0x00000000)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_2_P0_HSH               (0x011AD830)

  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_3_P0_OFF               (14)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_3_P0_WID               ( 1)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_3_P0_MSK               (0x00004000)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_3_P0_MIN               (0)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_3_P0_MAX               (1) // 0x00000001
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_3_P0_DEF               (0x00000000)
  #define MC0_MC_INIT_STATE_G_mrc_save_gv_point_3_P0_HSH               (0x011CD830)

  #define MC0_MC_INIT_STATE_G_dclk_enable_P0_OFF                       (22)
  #define MC0_MC_INIT_STATE_G_dclk_enable_P0_WID                       ( 1)
  #define MC0_MC_INIT_STATE_G_dclk_enable_P0_MSK                       (0x00400000)
  #define MC0_MC_INIT_STATE_G_dclk_enable_P0_MIN                       (0)
  #define MC0_MC_INIT_STATE_G_dclk_enable_P0_MAX                       (1) // 0x00000001
  #define MC0_MC_INIT_STATE_G_dclk_enable_P0_DEF                       (0x00000000)
  #define MC0_MC_INIT_STATE_G_dclk_enable_P0_HSH                       (0x012CD830)

  #define MC0_MC_INIT_STATE_G_override_sr_enable_P0_OFF                (24)
  #define MC0_MC_INIT_STATE_G_override_sr_enable_P0_WID                ( 1)
  #define MC0_MC_INIT_STATE_G_override_sr_enable_P0_MSK                (0x01000000)
  #define MC0_MC_INIT_STATE_G_override_sr_enable_P0_MIN                (0)
  #define MC0_MC_INIT_STATE_G_override_sr_enable_P0_MAX                (1) // 0x00000001
  #define MC0_MC_INIT_STATE_G_override_sr_enable_P0_DEF                (0x00000000)
  #define MC0_MC_INIT_STATE_G_override_sr_enable_P0_HSH                (0x0130D830)

  #define MC0_MC_INIT_STATE_G_override_sr_enable_value_P0_OFF          (25)
  #define MC0_MC_INIT_STATE_G_override_sr_enable_value_P0_WID          ( 1)
  #define MC0_MC_INIT_STATE_G_override_sr_enable_value_P0_MSK          (0x02000000)
  #define MC0_MC_INIT_STATE_G_override_sr_enable_value_P0_MIN          (0)
  #define MC0_MC_INIT_STATE_G_override_sr_enable_value_P0_MAX          (1) // 0x00000001
  #define MC0_MC_INIT_STATE_G_override_sr_enable_value_P0_DEF          (0x00000000)
  #define MC0_MC_INIT_STATE_G_override_sr_enable_value_P0_HSH          (0x0132D830)

#define MC0_MRC_REVISION_P0_REG                                        (0x0000D834)

  #define MC0_MRC_REVISION_REVISION_P0_OFF                             ( 0)
  #define MC0_MRC_REVISION_REVISION_P0_WID                             (32)
  #define MC0_MRC_REVISION_REVISION_P0_MSK                             (0xFFFFFFFF)
  #define MC0_MRC_REVISION_REVISION_P0_MIN                             (0)
  #define MC0_MRC_REVISION_REVISION_P0_MAX                             (4294967295) // 0xFFFFFFFF
  #define MC0_MRC_REVISION_REVISION_P0_DEF                             (0x00000000)
  #define MC0_MRC_REVISION_REVISION_P0_HSH                             (0x2000D834)

#define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_P0_REG                    (0x0000D83C)

  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID0_P0_OFF   ( 0)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID0_P0_WID   ( 5)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID0_P0_MSK   (0x0000001F)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID0_P0_MIN   (0)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID0_P0_MAX   (31) // 0x0000001F
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID0_P0_DEF   (0x00000000)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID0_P0_HSH   (0x0500D83C)

  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID1_P0_OFF   ( 5)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID1_P0_WID   ( 5)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID1_P0_MSK   (0x000003E0)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID1_P0_MIN   (0)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID1_P0_MAX   (31) // 0x0000001F
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID1_P0_DEF   (0x00000001)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID1_P0_HSH   (0x050AD83C)

  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID2_P0_OFF   (10)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID2_P0_WID   ( 5)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID2_P0_MSK   (0x00007C00)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID2_P0_MIN   (0)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID2_P0_MAX   (31) // 0x0000001F
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID2_P0_DEF   (0x00000002)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID2_P0_HSH   (0x0514D83C)

  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID3_P0_OFF   (15)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID3_P0_WID   ( 5)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID3_P0_MSK   (0x000F8000)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID3_P0_MIN   (0)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID3_P0_MAX   (31) // 0x0000001F
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID3_P0_DEF   (0x00000002)
  #define MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_CMI_Source_ID3_P0_HSH   (0x051ED83C)

#define MC0_PWM_TOTAL_REQCOUNT_P0_REG                                  (0x0000D840)

  #define MC0_PWM_TOTAL_REQCOUNT_count_P0_OFF                          ( 0)
  #define MC0_PWM_TOTAL_REQCOUNT_count_P0_WID                          (64)
  #define MC0_PWM_TOTAL_REQCOUNT_count_P0_MSK                          (0xFFFFFFFFFFFFFFFFULL)
  #define MC0_PWM_TOTAL_REQCOUNT_count_P0_MIN                          (0)
  #define MC0_PWM_TOTAL_REQCOUNT_count_P0_MAX                          (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define MC0_PWM_TOTAL_REQCOUNT_count_P0_DEF                          (0x00000000)
  #define MC0_PWM_TOTAL_REQCOUNT_count_P0_HSH                          (0x4000D840)

#define MC0_PWM_PROGRAMMABLE_REQCOUNT_0_P0_REG                         (0x0000D848)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_P0_REG

#define MC0_PWM_PROGRAMMABLE_REQCOUNT_1_P0_REG                         (0x0000D850)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_P0_REG

#define MC0_PWM_RDCAS_COUNT_P0_REG                                     (0x0000D858)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_P0_REG

#define MC0_PM_SREF_CONFIG_P0_REG                                      (0x0000D860)

  #define MC0_PM_SREF_CONFIG_Idle_timer_P0_OFF                         ( 0)
  #define MC0_PM_SREF_CONFIG_Idle_timer_P0_WID                         (16)
  #define MC0_PM_SREF_CONFIG_Idle_timer_P0_MSK                         (0x0000FFFF)
  #define MC0_PM_SREF_CONFIG_Idle_timer_P0_MIN                         (0)
  #define MC0_PM_SREF_CONFIG_Idle_timer_P0_MAX                         (65535) // 0x0000FFFF
  #define MC0_PM_SREF_CONFIG_Idle_timer_P0_DEF                         (0x00000200)
  #define MC0_PM_SREF_CONFIG_Idle_timer_P0_HSH                         (0x1000D860)

  #define MC0_PM_SREF_CONFIG_SR_Enable_P0_OFF                          (16)
  #define MC0_PM_SREF_CONFIG_SR_Enable_P0_WID                          ( 1)
  #define MC0_PM_SREF_CONFIG_SR_Enable_P0_MSK                          (0x00010000)
  #define MC0_PM_SREF_CONFIG_SR_Enable_P0_MIN                          (0)
  #define MC0_PM_SREF_CONFIG_SR_Enable_P0_MAX                          (1) // 0x00000001
  #define MC0_PM_SREF_CONFIG_SR_Enable_P0_DEF                          (0x00000001)
  #define MC0_PM_SREF_CONFIG_SR_Enable_P0_HSH                          (0x0120D860)

  #define MC0_PM_SREF_CONFIG_delay_qsync_P0_OFF                        (17)
  #define MC0_PM_SREF_CONFIG_delay_qsync_P0_WID                        ( 2)
  #define MC0_PM_SREF_CONFIG_delay_qsync_P0_MSK                        (0x00060000)
  #define MC0_PM_SREF_CONFIG_delay_qsync_P0_MIN                        (0)
  #define MC0_PM_SREF_CONFIG_delay_qsync_P0_MAX                        (3) // 0x00000003
  #define MC0_PM_SREF_CONFIG_delay_qsync_P0_DEF                        (0x00000000)
  #define MC0_PM_SREF_CONFIG_delay_qsync_P0_HSH                        (0x0222D860)

#define MC0_ATMC_STS_P0_REG                                            (0x0000D864)

  #define MC0_ATMC_STS_VC1_WR_CNFLT_P0_OFF                             ( 0)
  #define MC0_ATMC_STS_VC1_WR_CNFLT_P0_WID                             ( 1)
  #define MC0_ATMC_STS_VC1_WR_CNFLT_P0_MSK                             (0x00000001)
  #define MC0_ATMC_STS_VC1_WR_CNFLT_P0_MIN                             (0)
  #define MC0_ATMC_STS_VC1_WR_CNFLT_P0_MAX                             (1) // 0x00000001
  #define MC0_ATMC_STS_VC1_WR_CNFLT_P0_DEF                             (0x00000000)
  #define MC0_ATMC_STS_VC1_WR_CNFLT_P0_HSH                             (0x0100D864)

  #define MC0_ATMC_STS_VC1_RD_CNFLT_P0_OFF                             ( 1)
  #define MC0_ATMC_STS_VC1_RD_CNFLT_P0_WID                             ( 1)
  #define MC0_ATMC_STS_VC1_RD_CNFLT_P0_MSK                             (0x00000002)
  #define MC0_ATMC_STS_VC1_RD_CNFLT_P0_MIN                             (0)
  #define MC0_ATMC_STS_VC1_RD_CNFLT_P0_MAX                             (1) // 0x00000001
  #define MC0_ATMC_STS_VC1_RD_CNFLT_P0_DEF                             (0x00000000)
  #define MC0_ATMC_STS_VC1_RD_CNFLT_P0_HSH                             (0x0102D864)

#define MC0_READ_OCCUPANCY_COUNT_P0_REG                                (0x0000D868)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_P0_REG

#define MC0_STALL_DRAIN_P0_REG                                         (0x0000D874)

  #define MC0_STALL_DRAIN_stall_until_drain_P0_OFF                     ( 0)
  #define MC0_STALL_DRAIN_stall_until_drain_P0_WID                     ( 1)
  #define MC0_STALL_DRAIN_stall_until_drain_P0_MSK                     (0x00000001)
  #define MC0_STALL_DRAIN_stall_until_drain_P0_MIN                     (0)
  #define MC0_STALL_DRAIN_stall_until_drain_P0_MAX                     (1) // 0x00000001
  #define MC0_STALL_DRAIN_stall_until_drain_P0_DEF                     (0x00000000)
  #define MC0_STALL_DRAIN_stall_until_drain_P0_HSH                     (0x0100D874)

  #define MC0_STALL_DRAIN_stall_input_P0_OFF                           ( 1)
  #define MC0_STALL_DRAIN_stall_input_P0_WID                           ( 1)
  #define MC0_STALL_DRAIN_stall_input_P0_MSK                           (0x00000002)
  #define MC0_STALL_DRAIN_stall_input_P0_MIN                           (0)
  #define MC0_STALL_DRAIN_stall_input_P0_MAX                           (1) // 0x00000001
  #define MC0_STALL_DRAIN_stall_input_P0_DEF                           (0x00000000)
  #define MC0_STALL_DRAIN_stall_input_P0_HSH                           (0x0102D874)

  #define MC0_STALL_DRAIN_mc_drained_P0_OFF                            ( 4)
  #define MC0_STALL_DRAIN_mc_drained_P0_WID                            ( 1)
  #define MC0_STALL_DRAIN_mc_drained_P0_MSK                            (0x00000010)
  #define MC0_STALL_DRAIN_mc_drained_P0_MIN                            (0)
  #define MC0_STALL_DRAIN_mc_drained_P0_MAX                            (1) // 0x00000001
  #define MC0_STALL_DRAIN_mc_drained_P0_DEF                            (0x00000000)
  #define MC0_STALL_DRAIN_mc_drained_P0_HSH                            (0x0108D874)

  #define MC0_STALL_DRAIN_sr_state_P0_OFF                              ( 8)
  #define MC0_STALL_DRAIN_sr_state_P0_WID                              ( 1)
  #define MC0_STALL_DRAIN_sr_state_P0_MSK                              (0x00000100)
  #define MC0_STALL_DRAIN_sr_state_P0_MIN                              (0)
  #define MC0_STALL_DRAIN_sr_state_P0_MAX                              (1) // 0x00000001
  #define MC0_STALL_DRAIN_sr_state_P0_DEF                              (0x00000000)
  #define MC0_STALL_DRAIN_sr_state_P0_HSH                              (0x0110D874)

  #define MC0_STALL_DRAIN_stall_state_P0_OFF                           (12)
  #define MC0_STALL_DRAIN_stall_state_P0_WID                           ( 1)
  #define MC0_STALL_DRAIN_stall_state_P0_MSK                           (0x00001000)
  #define MC0_STALL_DRAIN_stall_state_P0_MIN                           (0)
  #define MC0_STALL_DRAIN_stall_state_P0_MAX                           (1) // 0x00000001
  #define MC0_STALL_DRAIN_stall_state_P0_DEF                           (0x00000000)
  #define MC0_STALL_DRAIN_stall_state_P0_HSH                           (0x0118D874)

#define MC0_IPC_MC_ARB_P0_REG                                          (0x0000D878)

  #define MC0_IPC_MC_ARB_NonVC1Threshold_P0_OFF                        ( 0)
  #define MC0_IPC_MC_ARB_NonVC1Threshold_P0_WID                        ( 4)
  #define MC0_IPC_MC_ARB_NonVC1Threshold_P0_MSK                        (0x0000000F)
  #define MC0_IPC_MC_ARB_NonVC1Threshold_P0_MIN                        (0)
  #define MC0_IPC_MC_ARB_NonVC1Threshold_P0_MAX                        (15) // 0x0000000F
  #define MC0_IPC_MC_ARB_NonVC1Threshold_P0_DEF                        (0x00000004)
  #define MC0_IPC_MC_ARB_NonVC1Threshold_P0_HSH                        (0x0400D878)

  #define MC0_IPC_MC_ARB_VC1RdThreshold_P0_OFF                         ( 4)
  #define MC0_IPC_MC_ARB_VC1RdThreshold_P0_WID                         ( 4)
  #define MC0_IPC_MC_ARB_VC1RdThreshold_P0_MSK                         (0x000000F0)
  #define MC0_IPC_MC_ARB_VC1RdThreshold_P0_MIN                         (0)
  #define MC0_IPC_MC_ARB_VC1RdThreshold_P0_MAX                         (15) // 0x0000000F
  #define MC0_IPC_MC_ARB_VC1RdThreshold_P0_DEF                         (0x00000004)
  #define MC0_IPC_MC_ARB_VC1RdThreshold_P0_HSH                         (0x0408D878)

  #define MC0_IPC_MC_ARB_FixedRateEn_P0_OFF                            ( 8)
  #define MC0_IPC_MC_ARB_FixedRateEn_P0_WID                            ( 1)
  #define MC0_IPC_MC_ARB_FixedRateEn_P0_MSK                            (0x00000100)
  #define MC0_IPC_MC_ARB_FixedRateEn_P0_MIN                            (0)
  #define MC0_IPC_MC_ARB_FixedRateEn_P0_MAX                            (1) // 0x00000001
  #define MC0_IPC_MC_ARB_FixedRateEn_P0_DEF                            (0x00000000)
  #define MC0_IPC_MC_ARB_FixedRateEn_P0_HSH                            (0x0110D878)

  #define MC0_IPC_MC_ARB_HIGH_PRIO_LIM_P0_OFF                          ( 9)
  #define MC0_IPC_MC_ARB_HIGH_PRIO_LIM_P0_WID                          ( 3)
  #define MC0_IPC_MC_ARB_HIGH_PRIO_LIM_P0_MSK                          (0x00000E00)
  #define MC0_IPC_MC_ARB_HIGH_PRIO_LIM_P0_MIN                          (0)
  #define MC0_IPC_MC_ARB_HIGH_PRIO_LIM_P0_MAX                          (7) // 0x00000007
  #define MC0_IPC_MC_ARB_HIGH_PRIO_LIM_P0_DEF                          (0x00000004)
  #define MC0_IPC_MC_ARB_HIGH_PRIO_LIM_P0_HSH                          (0x0312D878)

  #define MC0_IPC_MC_ARB_LOW_PRIO_LIM_P0_OFF                           (12)
  #define MC0_IPC_MC_ARB_LOW_PRIO_LIM_P0_WID                           ( 3)
  #define MC0_IPC_MC_ARB_LOW_PRIO_LIM_P0_MSK                           (0x00007000)
  #define MC0_IPC_MC_ARB_LOW_PRIO_LIM_P0_MIN                           (0)
  #define MC0_IPC_MC_ARB_LOW_PRIO_LIM_P0_MAX                           (7) // 0x00000007
  #define MC0_IPC_MC_ARB_LOW_PRIO_LIM_P0_DEF                           (0x00000001)
  #define MC0_IPC_MC_ARB_LOW_PRIO_LIM_P0_HSH                           (0x0318D878)

  #define MC0_IPC_MC_ARB_spare_P0_OFF                                  (15)
  #define MC0_IPC_MC_ARB_spare_P0_WID                                  ( 8)
  #define MC0_IPC_MC_ARB_spare_P0_MSK                                  (0x007F8000)
  #define MC0_IPC_MC_ARB_spare_P0_MIN                                  (0)
  #define MC0_IPC_MC_ARB_spare_P0_MAX                                  (255) // 0x000000FF
  #define MC0_IPC_MC_ARB_spare_P0_DEF                                  (0x00000000)
  #define MC0_IPC_MC_ARB_spare_P0_HSH                                  (0x081ED878)

#define MC0_IPC_MC_DEC_ARB_P0_REG                                      (0x0000D87C)
//Duplicate of MC0_IPC_MC_ARB_P0_REG

#define MC0_QUEUE_CREDIT_C_P0_REG                                      (0x0000D880)

  #define MC0_QUEUE_CREDIT_C_RPQ_count_P0_OFF                          ( 0)
  #define MC0_QUEUE_CREDIT_C_RPQ_count_P0_WID                          ( 6)
  #define MC0_QUEUE_CREDIT_C_RPQ_count_P0_MSK                          (0x0000003F)
  #define MC0_QUEUE_CREDIT_C_RPQ_count_P0_MIN                          (0)
  #define MC0_QUEUE_CREDIT_C_RPQ_count_P0_MAX                          (63) // 0x0000003F
  #define MC0_QUEUE_CREDIT_C_RPQ_count_P0_DEF                          (0x00000020)
  #define MC0_QUEUE_CREDIT_C_RPQ_count_P0_HSH                          (0x0600D880)

  #define MC0_QUEUE_CREDIT_C_WPQ_count_P0_OFF                          ( 8)
  #define MC0_QUEUE_CREDIT_C_WPQ_count_P0_WID                          ( 7)
  #define MC0_QUEUE_CREDIT_C_WPQ_count_P0_MSK                          (0x00007F00)
  #define MC0_QUEUE_CREDIT_C_WPQ_count_P0_MIN                          (0)
  #define MC0_QUEUE_CREDIT_C_WPQ_count_P0_MAX                          (127) // 0x0000007F
  #define MC0_QUEUE_CREDIT_C_WPQ_count_P0_DEF                          (0x00000040)
  #define MC0_QUEUE_CREDIT_C_WPQ_count_P0_HSH                          (0x0710D880)

  #define MC0_QUEUE_CREDIT_C_IPQ_count_P0_OFF                          (16)
  #define MC0_QUEUE_CREDIT_C_IPQ_count_P0_WID                          ( 5)
  #define MC0_QUEUE_CREDIT_C_IPQ_count_P0_MSK                          (0x001F0000)
  #define MC0_QUEUE_CREDIT_C_IPQ_count_P0_MIN                          (0)
  #define MC0_QUEUE_CREDIT_C_IPQ_count_P0_MAX                          (31) // 0x0000001F
  #define MC0_QUEUE_CREDIT_C_IPQ_count_P0_DEF                          (0x00000010)
  #define MC0_QUEUE_CREDIT_C_IPQ_count_P0_HSH                          (0x0520D880)

  #define MC0_QUEUE_CREDIT_C_WPQ_MinSlotsToReq_P0_OFF                  (21)
  #define MC0_QUEUE_CREDIT_C_WPQ_MinSlotsToReq_P0_WID                  ( 4)
  #define MC0_QUEUE_CREDIT_C_WPQ_MinSlotsToReq_P0_MSK                  (0x01E00000)
  #define MC0_QUEUE_CREDIT_C_WPQ_MinSlotsToReq_P0_MIN                  (0)
  #define MC0_QUEUE_CREDIT_C_WPQ_MinSlotsToReq_P0_MAX                  (15) // 0x0000000F
  #define MC0_QUEUE_CREDIT_C_WPQ_MinSlotsToReq_P0_DEF                  (0x00000002)
  #define MC0_QUEUE_CREDIT_C_WPQ_MinSlotsToReq_P0_HSH                  (0x042AD880)

  #define MC0_QUEUE_CREDIT_C_IPQ_MinSlotsToReq_P0_OFF                  (25)
  #define MC0_QUEUE_CREDIT_C_IPQ_MinSlotsToReq_P0_WID                  ( 3)
  #define MC0_QUEUE_CREDIT_C_IPQ_MinSlotsToReq_P0_MSK                  (0x0E000000)
  #define MC0_QUEUE_CREDIT_C_IPQ_MinSlotsToReq_P0_MIN                  (0)
  #define MC0_QUEUE_CREDIT_C_IPQ_MinSlotsToReq_P0_MAX                  (7) // 0x00000007
  #define MC0_QUEUE_CREDIT_C_IPQ_MinSlotsToReq_P0_DEF                  (0x00000002)
  #define MC0_QUEUE_CREDIT_C_IPQ_MinSlotsToReq_P0_HSH                  (0x0332D880)

  #define MC0_QUEUE_CREDIT_C_RPQ_MinSlotsToReq_P0_OFF                  (28)
  #define MC0_QUEUE_CREDIT_C_RPQ_MinSlotsToReq_P0_WID                  ( 4)
  #define MC0_QUEUE_CREDIT_C_RPQ_MinSlotsToReq_P0_MSK                  (0xF0000000)
  #define MC0_QUEUE_CREDIT_C_RPQ_MinSlotsToReq_P0_MIN                  (0)
  #define MC0_QUEUE_CREDIT_C_RPQ_MinSlotsToReq_P0_MAX                  (15) // 0x0000000F
  #define MC0_QUEUE_CREDIT_C_RPQ_MinSlotsToReq_P0_DEF                  (0x00000002)
  #define MC0_QUEUE_CREDIT_C_RPQ_MinSlotsToReq_P0_HSH                  (0x0438D880)

#define MC0_ECC_INJ_ADDR_COMPARE_P0_REG                                (0x0000D888)

  #define MC0_ECC_INJ_ADDR_COMPARE_Address_P0_OFF                      ( 0)
  #define MC0_ECC_INJ_ADDR_COMPARE_Address_P0_WID                      (33)
  #define MC0_ECC_INJ_ADDR_COMPARE_Address_P0_MSK                      (0x00000001FFFFFFFFULL)
  #define MC0_ECC_INJ_ADDR_COMPARE_Address_P0_MIN                      (0)
  #define MC0_ECC_INJ_ADDR_COMPARE_Address_P0_MAX                      (8589934591ULL) // 0x1FFFFFFFF
  #define MC0_ECC_INJ_ADDR_COMPARE_Address_P0_DEF                      (0x00000000)
  #define MC0_ECC_INJ_ADDR_COMPARE_Address_P0_HSH                      (0x6100D888)

#define MC0_REMAPBASE_P0_REG                                           (0x0000D890)

  #define MC0_REMAPBASE_REMAPBASE_P0_OFF                               (20)
  #define MC0_REMAPBASE_REMAPBASE_P0_WID                               (19)
  #define MC0_REMAPBASE_REMAPBASE_P0_MSK                               (0x0000007FFFF00000ULL)
  #define MC0_REMAPBASE_REMAPBASE_P0_MIN                               (0)
  #define MC0_REMAPBASE_REMAPBASE_P0_MAX                               (524287) // 0x0007FFFF
  #define MC0_REMAPBASE_REMAPBASE_P0_DEF                               (0x0007FFFF)
  #define MC0_REMAPBASE_REMAPBASE_P0_HSH                               (0x5328D890)

#define MC0_REMAPLIMIT_P0_REG                                          (0x0000D898)

  #define MC0_REMAPLIMIT_REMAPLMT_P0_OFF                               (20)
  #define MC0_REMAPLIMIT_REMAPLMT_P0_WID                               (19)
  #define MC0_REMAPLIMIT_REMAPLMT_P0_MSK                               (0x0000007FFFF00000ULL)
  #define MC0_REMAPLIMIT_REMAPLMT_P0_MIN                               (0)
  #define MC0_REMAPLIMIT_REMAPLMT_P0_MAX                               (524287) // 0x0007FFFF
  #define MC0_REMAPLIMIT_REMAPLMT_P0_DEF                               (0x00000000)
  #define MC0_REMAPLIMIT_REMAPLMT_P0_HSH                               (0x5328D898)

#define MC0_PWM_WRCAS_COUNT_P0_REG                                     (0x0000D8A0)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_P0_REG

#define MC0_PWM_COMMAND_COUNT_P0_REG                                   (0x0000D8A8)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_P0_REG

#define MC0_PWM_NON_SR_COUNT_P0_REG                                    (0x0000D8B0)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_P0_REG

#define MC0_TOLUD_P0_REG                                               (0x0000D8BC)

  #define MC0_TOLUD_TOLUD_P0_OFF                                       (20)
  #define MC0_TOLUD_TOLUD_P0_WID                                       (12)
  #define MC0_TOLUD_TOLUD_P0_MSK                                       (0xFFF00000)
  #define MC0_TOLUD_TOLUD_P0_MIN                                       (0)
  #define MC0_TOLUD_TOLUD_P0_MAX                                       (4095) // 0x00000FFF
  #define MC0_TOLUD_TOLUD_P0_DEF                                       (0x00000001)
  #define MC0_TOLUD_TOLUD_P0_HSH                                       (0x0C28D8BC)

#define MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_P0_REG                      (0x0000D900)

  #define MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_sys_addr_P0_OFF           ( 0)
  #define MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_sys_addr_P0_WID           (33)
  #define MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_sys_addr_P0_MSK           (0x00000001FFFFFFFFULL)
  #define MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_sys_addr_P0_MIN           (0)
  #define MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_sys_addr_P0_MAX           (8589934591ULL) // 0x1FFFFFFFF
  #define MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_sys_addr_P0_DEF           (0x00000000)
  #define MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_sys_addr_P0_HSH           (0x6100D900)

#define MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_1_P0_REG                      (0x0000D908)
//Duplicate of MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_P0_REG

#define MC0_GDXC_DDR_SYS_ADD_FILTER_MATCH_0_P0_REG                     (0x0000D910)
//Duplicate of MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_P0_REG

#define MC0_GDXC_DDR_SYS_ADD_FILTER_MATCH_1_P0_REG                     (0x0000D918)
//Duplicate of MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_P0_REG

#define MC0_GDXC_DDR_SYS_ADD_TRIGGER_MASK_P0_REG                       (0x0000D920)
//Duplicate of MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_P0_REG

#define MC0_GDXC_DDR_SYS_ADD_TRIGGER_MATCH_P0_REG                      (0x0000D928)
//Duplicate of MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_P0_REG

#define MC0_SC_QOS_P0_REG                                              (0x0000D930)

  #define MC0_SC_QOS_Isoch_time_window_P0_OFF                          ( 0)
  #define MC0_SC_QOS_Isoch_time_window_P0_WID                          (17)
  #define MC0_SC_QOS_Isoch_time_window_P0_MSK                          (0x0001FFFF)
  #define MC0_SC_QOS_Isoch_time_window_P0_MIN                          (0)
  #define MC0_SC_QOS_Isoch_time_window_P0_MAX                          (131071) // 0x0001FFFF
  #define MC0_SC_QOS_Isoch_time_window_P0_DEF                          (0x000001C2)
  #define MC0_SC_QOS_Isoch_time_window_P0_HSH                          (0x5100D930)

  #define MC0_SC_QOS_Write_starvation_window_P0_OFF                    (17)
  #define MC0_SC_QOS_Write_starvation_window_P0_WID                    (11)
  #define MC0_SC_QOS_Write_starvation_window_P0_MSK                    (0x0FFE0000)
  #define MC0_SC_QOS_Write_starvation_window_P0_MIN                    (0)
  #define MC0_SC_QOS_Write_starvation_window_P0_MAX                    (2047) // 0x000007FF
  #define MC0_SC_QOS_Write_starvation_window_P0_DEF                    (0x0000005A)
  #define MC0_SC_QOS_Write_starvation_window_P0_HSH                    (0x4B22D930)

  #define MC0_SC_QOS_VC1_Read_starvation_en_P0_OFF                     (28)
  #define MC0_SC_QOS_VC1_Read_starvation_en_P0_WID                     ( 1)
  #define MC0_SC_QOS_VC1_Read_starvation_en_P0_MSK                     (0x10000000)
  #define MC0_SC_QOS_VC1_Read_starvation_en_P0_MIN                     (0)
  #define MC0_SC_QOS_VC1_Read_starvation_en_P0_MAX                     (1) // 0x00000001
  #define MC0_SC_QOS_VC1_Read_starvation_en_P0_DEF                     (0x00000001)
  #define MC0_SC_QOS_VC1_Read_starvation_en_P0_HSH                     (0x4138D930)

  #define MC0_SC_QOS_Write_starvation_in_Isoc_en_P0_OFF                (29)
  #define MC0_SC_QOS_Write_starvation_in_Isoc_en_P0_WID                ( 1)
  #define MC0_SC_QOS_Write_starvation_in_Isoc_en_P0_MSK                (0x20000000)
  #define MC0_SC_QOS_Write_starvation_in_Isoc_en_P0_MIN                (0)
  #define MC0_SC_QOS_Write_starvation_in_Isoc_en_P0_MAX                (1) // 0x00000001
  #define MC0_SC_QOS_Write_starvation_in_Isoc_en_P0_DEF                (0x00000001)
  #define MC0_SC_QOS_Write_starvation_in_Isoc_en_P0_HSH                (0x413AD930)

  #define MC0_SC_QOS_Read_starvation_in_Isoch_en_P0_OFF                (30)
  #define MC0_SC_QOS_Read_starvation_in_Isoch_en_P0_WID                ( 1)
  #define MC0_SC_QOS_Read_starvation_in_Isoch_en_P0_MSK                (0x40000000)
  #define MC0_SC_QOS_Read_starvation_in_Isoch_en_P0_MIN                (0)
  #define MC0_SC_QOS_Read_starvation_in_Isoch_en_P0_MAX                (1) // 0x00000001
  #define MC0_SC_QOS_Read_starvation_in_Isoch_en_P0_DEF                (0x00000001)
  #define MC0_SC_QOS_Read_starvation_in_Isoch_en_P0_HSH                (0x413CD930)

  #define MC0_SC_QOS_VC0_counter_disable_P0_OFF                        (31)
  #define MC0_SC_QOS_VC0_counter_disable_P0_WID                        ( 1)
  #define MC0_SC_QOS_VC0_counter_disable_P0_MSK                        (0x80000000)
  #define MC0_SC_QOS_VC0_counter_disable_P0_MIN                        (0)
  #define MC0_SC_QOS_VC0_counter_disable_P0_MAX                        (1) // 0x00000001
  #define MC0_SC_QOS_VC0_counter_disable_P0_DEF                        (0x00000000)
  #define MC0_SC_QOS_VC0_counter_disable_P0_HSH                        (0x413ED930)

  #define MC0_SC_QOS_Read_starvation_window_P0_OFF                     (32)
  #define MC0_SC_QOS_Read_starvation_window_P0_WID                     (11)
  #define MC0_SC_QOS_Read_starvation_window_P0_MSK                     (0x000007FF00000000ULL)
  #define MC0_SC_QOS_Read_starvation_window_P0_MIN                     (0)
  #define MC0_SC_QOS_Read_starvation_window_P0_MAX                     (2047) // 0x000007FF
  #define MC0_SC_QOS_Read_starvation_window_P0_DEF                     (0x0000005A)
  #define MC0_SC_QOS_Read_starvation_window_P0_HSH                     (0x4B40D930)

  #define MC0_SC_QOS_VC0_read_count_P0_OFF                             (43)
  #define MC0_SC_QOS_VC0_read_count_P0_WID                             ( 9)
  #define MC0_SC_QOS_VC0_read_count_P0_MSK                             (0x000FF80000000000ULL)
  #define MC0_SC_QOS_VC0_read_count_P0_MIN                             (0)
  #define MC0_SC_QOS_VC0_read_count_P0_MAX                             (511) // 0x000001FF
  #define MC0_SC_QOS_VC0_read_count_P0_DEF                             (0x00000016)
  #define MC0_SC_QOS_VC0_read_count_P0_HSH                             (0x4956D930)

  #define MC0_SC_QOS_Force_MCVC1Demote_P0_OFF                          (52)
  #define MC0_SC_QOS_Force_MCVC1Demote_P0_WID                          ( 1)
  #define MC0_SC_QOS_Force_MCVC1Demote_P0_MSK                          (0x0010000000000000ULL)
  #define MC0_SC_QOS_Force_MCVC1Demote_P0_MIN                          (0)
  #define MC0_SC_QOS_Force_MCVC1Demote_P0_MAX                          (1) // 0x00000001
  #define MC0_SC_QOS_Force_MCVC1Demote_P0_DEF                          (0x00000000)
  #define MC0_SC_QOS_Force_MCVC1Demote_P0_HSH                          (0x4168D930)

  #define MC0_SC_QOS_Disable_MCVC1Demote_P0_OFF                        (53)
  #define MC0_SC_QOS_Disable_MCVC1Demote_P0_WID                        ( 1)
  #define MC0_SC_QOS_Disable_MCVC1Demote_P0_MSK                        (0x0020000000000000ULL)
  #define MC0_SC_QOS_Disable_MCVC1Demote_P0_MIN                        (0)
  #define MC0_SC_QOS_Disable_MCVC1Demote_P0_MAX                        (1) // 0x00000001
  #define MC0_SC_QOS_Disable_MCVC1Demote_P0_DEF                        (0x00000000)
  #define MC0_SC_QOS_Disable_MCVC1Demote_P0_HSH                        (0x416AD930)

  #define MC0_SC_QOS_MC_Ignore_VC1Demote_P0_OFF                        (54)
  #define MC0_SC_QOS_MC_Ignore_VC1Demote_P0_WID                        ( 1)
  #define MC0_SC_QOS_MC_Ignore_VC1Demote_P0_MSK                        (0x0040000000000000ULL)
  #define MC0_SC_QOS_MC_Ignore_VC1Demote_P0_MIN                        (0)
  #define MC0_SC_QOS_MC_Ignore_VC1Demote_P0_MAX                        (1) // 0x00000001
  #define MC0_SC_QOS_MC_Ignore_VC1Demote_P0_DEF                        (0x00000000)
  #define MC0_SC_QOS_MC_Ignore_VC1Demote_P0_HSH                        (0x416CD930)

  #define MC0_SC_QOS_Ignore_RGBSync_P0_OFF                             (55)
  #define MC0_SC_QOS_Ignore_RGBSync_P0_WID                             ( 1)
  #define MC0_SC_QOS_Ignore_RGBSync_P0_MSK                             (0x0080000000000000ULL)
  #define MC0_SC_QOS_Ignore_RGBSync_P0_MIN                             (0)
  #define MC0_SC_QOS_Ignore_RGBSync_P0_MAX                             (1) // 0x00000001
  #define MC0_SC_QOS_Ignore_RGBSync_P0_DEF                             (0x00000000)
  #define MC0_SC_QOS_Ignore_RGBSync_P0_HSH                             (0x416ED930)

  #define MC0_SC_QOS_Force_MC_WPriority_P0_OFF                         (56)
  #define MC0_SC_QOS_Force_MC_WPriority_P0_WID                         ( 1)
  #define MC0_SC_QOS_Force_MC_WPriority_P0_MSK                         (0x0100000000000000ULL)
  #define MC0_SC_QOS_Force_MC_WPriority_P0_MIN                         (0)
  #define MC0_SC_QOS_Force_MC_WPriority_P0_MAX                         (1) // 0x00000001
  #define MC0_SC_QOS_Force_MC_WPriority_P0_DEF                         (0x00000000)
  #define MC0_SC_QOS_Force_MC_WPriority_P0_HSH                         (0x4170D930)

  #define MC0_SC_QOS_Disable_MC_WPriority_P0_OFF                       (57)
  #define MC0_SC_QOS_Disable_MC_WPriority_P0_WID                       ( 1)
  #define MC0_SC_QOS_Disable_MC_WPriority_P0_MSK                       (0x0200000000000000ULL)
  #define MC0_SC_QOS_Disable_MC_WPriority_P0_MIN                       (0)
  #define MC0_SC_QOS_Disable_MC_WPriority_P0_MAX                       (1) // 0x00000001
  #define MC0_SC_QOS_Disable_MC_WPriority_P0_DEF                       (0x00000000)
  #define MC0_SC_QOS_Disable_MC_WPriority_P0_HSH                       (0x4172D930)

  #define MC0_SC_QOS_allow_cross_vc_blocking_P0_OFF                    (58)
  #define MC0_SC_QOS_allow_cross_vc_blocking_P0_WID                    ( 1)
  #define MC0_SC_QOS_allow_cross_vc_blocking_P0_MSK                    (0x0400000000000000ULL)
  #define MC0_SC_QOS_allow_cross_vc_blocking_P0_MIN                    (0)
  #define MC0_SC_QOS_allow_cross_vc_blocking_P0_MAX                    (1) // 0x00000001
  #define MC0_SC_QOS_allow_cross_vc_blocking_P0_DEF                    (0x00000001)
  #define MC0_SC_QOS_allow_cross_vc_blocking_P0_HSH                    (0x4174D930)

  #define MC0_SC_QOS_VC1_block_VC0_P0_OFF                              (59)
  #define MC0_SC_QOS_VC1_block_VC0_P0_WID                              ( 1)
  #define MC0_SC_QOS_VC1_block_VC0_P0_MSK                              (0x0800000000000000ULL)
  #define MC0_SC_QOS_VC1_block_VC0_P0_MIN                              (0)
  #define MC0_SC_QOS_VC1_block_VC0_P0_MAX                              (1) // 0x00000001
  #define MC0_SC_QOS_VC1_block_VC0_P0_DEF                              (0x00000000)
  #define MC0_SC_QOS_VC1_block_VC0_P0_HSH                              (0x4176D930)

  #define MC0_SC_QOS_VC0_block_VC1_P0_OFF                              (60)
  #define MC0_SC_QOS_VC0_block_VC1_P0_WID                              ( 1)
  #define MC0_SC_QOS_VC0_block_VC1_P0_MSK                              (0x1000000000000000ULL)
  #define MC0_SC_QOS_VC0_block_VC1_P0_MIN                              (0)
  #define MC0_SC_QOS_VC0_block_VC1_P0_MAX                              (1) // 0x00000001
  #define MC0_SC_QOS_VC0_block_VC1_P0_DEF                              (0x00000000)
  #define MC0_SC_QOS_VC0_block_VC1_P0_HSH                              (0x4178D930)

  #define MC0_SC_QOS_Delay_VC1_on_read_starvation_P0_OFF               (61)
  #define MC0_SC_QOS_Delay_VC1_on_read_starvation_P0_WID               ( 1)
  #define MC0_SC_QOS_Delay_VC1_on_read_starvation_P0_MSK               (0x2000000000000000ULL)
  #define MC0_SC_QOS_Delay_VC1_on_read_starvation_P0_MIN               (0)
  #define MC0_SC_QOS_Delay_VC1_on_read_starvation_P0_MAX               (1) // 0x00000001
  #define MC0_SC_QOS_Delay_VC1_on_read_starvation_P0_DEF               (0x00000000)
  #define MC0_SC_QOS_Delay_VC1_on_read_starvation_P0_HSH               (0x417AD930)

#define MC0_MCMAINS_GLOBAL_DRIVER_GATE_CFG_P0_REG                      (0x0000D938)

  #define MC0_MCMAINS_GLOBAL_DRIVER_GATE_CFG_GLB_GRACE_CNT_P0_OFF      ( 0)
  #define MC0_MCMAINS_GLOBAL_DRIVER_GATE_CFG_GLB_GRACE_CNT_P0_WID      ( 8)
  #define MC0_MCMAINS_GLOBAL_DRIVER_GATE_CFG_GLB_GRACE_CNT_P0_MSK      (0x000000FF)
  #define MC0_MCMAINS_GLOBAL_DRIVER_GATE_CFG_GLB_GRACE_CNT_P0_MIN      (0)
  #define MC0_MCMAINS_GLOBAL_DRIVER_GATE_CFG_GLB_GRACE_CNT_P0_MAX      (255) // 0x000000FF
  #define MC0_MCMAINS_GLOBAL_DRIVER_GATE_CFG_GLB_GRACE_CNT_P0_DEF      (0x0000000F)
  #define MC0_MCMAINS_GLOBAL_DRIVER_GATE_CFG_GLB_GRACE_CNT_P0_HSH      (0x0800D938)

  #define MC0_MCMAINS_GLOBAL_DRIVER_GATE_CFG_GLB_DRV_GATE_DIS_P0_OFF   ( 8)
  #define MC0_MCMAINS_GLOBAL_DRIVER_GATE_CFG_GLB_DRV_GATE_DIS_P0_WID   ( 1)
  #define MC0_MCMAINS_GLOBAL_DRIVER_GATE_CFG_GLB_DRV_GATE_DIS_P0_MSK   (0x00000100)
  #define MC0_MCMAINS_GLOBAL_DRIVER_GATE_CFG_GLB_DRV_GATE_DIS_P0_MIN   (0)
  #define MC0_MCMAINS_GLOBAL_DRIVER_GATE_CFG_GLB_DRV_GATE_DIS_P0_MAX   (1) // 0x00000001
  #define MC0_MCMAINS_GLOBAL_DRIVER_GATE_CFG_GLB_DRV_GATE_DIS_P0_DEF   (0x00000000)
  #define MC0_MCMAINS_GLOBAL_DRIVER_GATE_CFG_GLB_DRV_GATE_DIS_P0_HSH   (0x0110D938)

#define MC0_PWM_COUNTERS_DURATION_P0_REG                               (0x0000D948)

  #define MC0_PWM_COUNTERS_DURATION_Count_P0_OFF                       ( 0)
  #define MC0_PWM_COUNTERS_DURATION_Count_P0_WID                       (64)
  #define MC0_PWM_COUNTERS_DURATION_Count_P0_MSK                       (0xFFFFFFFFFFFFFFFFULL)
  #define MC0_PWM_COUNTERS_DURATION_Count_P0_MIN                       (0)
  #define MC0_PWM_COUNTERS_DURATION_Count_P0_MAX                       (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define MC0_PWM_COUNTERS_DURATION_Count_P0_DEF                       (0x00000000)
  #define MC0_PWM_COUNTERS_DURATION_Count_P0_HSH                       (0x4000D948)

#define MC0_MCDECS_SECOND_CBIT_P0_REG                                  (0x0000D954)

  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_enable_P0_OFF           ( 0)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_enable_P0_WID           ( 1)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_enable_P0_MSK           (0x00000001)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_enable_P0_MIN           (0)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_enable_P0_MAX           (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_enable_P0_DEF           (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_enable_P0_HSH           (0x0100D954)

  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_phase_P0_OFF            ( 1)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_phase_P0_WID            ( 1)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_phase_P0_MSK            (0x00000002)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_phase_P0_MIN            (0)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_phase_P0_MAX            (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_phase_P0_DEF            (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_cmi_req_stall_phase_P0_HSH            (0x0102D954)

  #define MC0_MCDECS_SECOND_CBIT_block_scheduler_P0_OFF                ( 2)
  #define MC0_MCDECS_SECOND_CBIT_block_scheduler_P0_WID                ( 4)
  #define MC0_MCDECS_SECOND_CBIT_block_scheduler_P0_MSK                (0x0000003C)
  #define MC0_MCDECS_SECOND_CBIT_block_scheduler_P0_MIN                (0)
  #define MC0_MCDECS_SECOND_CBIT_block_scheduler_P0_MAX                (15) // 0x0000000F
  #define MC0_MCDECS_SECOND_CBIT_block_scheduler_P0_DEF                (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_block_scheduler_P0_HSH                (0x0404D954)

  #define MC0_MCDECS_SECOND_CBIT_pwm_clock_enable_P0_OFF               ( 6)
  #define MC0_MCDECS_SECOND_CBIT_pwm_clock_enable_P0_WID               ( 1)
  #define MC0_MCDECS_SECOND_CBIT_pwm_clock_enable_P0_MSK               (0x00000040)
  #define MC0_MCDECS_SECOND_CBIT_pwm_clock_enable_P0_MIN               (0)
  #define MC0_MCDECS_SECOND_CBIT_pwm_clock_enable_P0_MAX               (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_pwm_clock_enable_P0_DEF               (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_pwm_clock_enable_P0_HSH               (0x010CD954)

  #define MC0_MCDECS_SECOND_CBIT_Mock_InSR_P0_OFF                      ( 7)
  #define MC0_MCDECS_SECOND_CBIT_Mock_InSR_P0_WID                      ( 1)
  #define MC0_MCDECS_SECOND_CBIT_Mock_InSR_P0_MSK                      (0x00000080)
  #define MC0_MCDECS_SECOND_CBIT_Mock_InSR_P0_MIN                      (0)
  #define MC0_MCDECS_SECOND_CBIT_Mock_InSR_P0_MAX                      (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_Mock_InSR_P0_DEF                      (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_Mock_InSR_P0_HSH                      (0x010ED954)

  #define MC0_MCDECS_SECOND_CBIT_dis_other_mc_stolen_ref_P0_OFF        ( 8)
  #define MC0_MCDECS_SECOND_CBIT_dis_other_mc_stolen_ref_P0_WID        ( 1)
  #define MC0_MCDECS_SECOND_CBIT_dis_other_mc_stolen_ref_P0_MSK        (0x00000100)
  #define MC0_MCDECS_SECOND_CBIT_dis_other_mc_stolen_ref_P0_MIN        (0)
  #define MC0_MCDECS_SECOND_CBIT_dis_other_mc_stolen_ref_P0_MAX        (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_dis_other_mc_stolen_ref_P0_DEF        (0x00000001)
  #define MC0_MCDECS_SECOND_CBIT_dis_other_mc_stolen_ref_P0_HSH        (0x0110D954)

  #define MC0_MCDECS_SECOND_CBIT_allow_blockack_on_pending_srx_P0_OFF  ( 9)
  #define MC0_MCDECS_SECOND_CBIT_allow_blockack_on_pending_srx_P0_WID  ( 1)
  #define MC0_MCDECS_SECOND_CBIT_allow_blockack_on_pending_srx_P0_MSK  (0x00000200)
  #define MC0_MCDECS_SECOND_CBIT_allow_blockack_on_pending_srx_P0_MIN  (0)
  #define MC0_MCDECS_SECOND_CBIT_allow_blockack_on_pending_srx_P0_MAX  (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_allow_blockack_on_pending_srx_P0_DEF  (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_allow_blockack_on_pending_srx_P0_HSH  (0x0112D954)

  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ca_valid_dis_P0_OFF     (10)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ca_valid_dis_P0_WID     ( 1)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ca_valid_dis_P0_MSK     (0x00000400)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ca_valid_dis_P0_MIN     (0)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ca_valid_dis_P0_MAX     (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ca_valid_dis_P0_DEF     (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ca_valid_dis_P0_HSH     (0x0114D954)

  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ckstop_dis_P0_OFF       (11)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ckstop_dis_P0_WID       ( 1)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ckstop_dis_P0_MSK       (0x00000800)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ckstop_dis_P0_MIN       (0)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ckstop_dis_P0_MAX       (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ckstop_dis_P0_DEF       (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_two_cyc_early_ckstop_dis_P0_HSH       (0x0116D954)

  #define MC0_MCDECS_SECOND_CBIT_dis_spid_cmd_clk_gate_P0_OFF          (12)
  #define MC0_MCDECS_SECOND_CBIT_dis_spid_cmd_clk_gate_P0_WID          ( 1)
  #define MC0_MCDECS_SECOND_CBIT_dis_spid_cmd_clk_gate_P0_MSK          (0x00001000)
  #define MC0_MCDECS_SECOND_CBIT_dis_spid_cmd_clk_gate_P0_MIN          (0)
  #define MC0_MCDECS_SECOND_CBIT_dis_spid_cmd_clk_gate_P0_MAX          (1) // 0x00000001
  #define MC0_MCDECS_SECOND_CBIT_dis_spid_cmd_clk_gate_P0_DEF          (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_dis_spid_cmd_clk_gate_P0_HSH          (0x0118D954)

  #define MC0_MCDECS_SECOND_CBIT_init_complete_override_P0_OFF         (16)
  #define MC0_MCDECS_SECOND_CBIT_init_complete_override_P0_WID         ( 4)
  #define MC0_MCDECS_SECOND_CBIT_init_complete_override_P0_MSK         (0x000F0000)
  #define MC0_MCDECS_SECOND_CBIT_init_complete_override_P0_MIN         (0)
  #define MC0_MCDECS_SECOND_CBIT_init_complete_override_P0_MAX         (15) // 0x0000000F
  #define MC0_MCDECS_SECOND_CBIT_init_complete_override_P0_DEF         (0x00000000)
  #define MC0_MCDECS_SECOND_CBIT_init_complete_override_P0_HSH         (0x0420D954)

#define MC0_ECC_INJ_ADDR_MASK_P0_REG                                   (0x0000D958)

  #define MC0_ECC_INJ_ADDR_MASK_Address_P0_OFF                         ( 0)
  #define MC0_ECC_INJ_ADDR_MASK_Address_P0_WID                         (33)
  #define MC0_ECC_INJ_ADDR_MASK_Address_P0_MSK                         (0x00000001FFFFFFFFULL)
  #define MC0_ECC_INJ_ADDR_MASK_Address_P0_MIN                         (0)
  #define MC0_ECC_INJ_ADDR_MASK_Address_P0_MAX                         (8589934591ULL) // 0x1FFFFFFFF
  #define MC0_ECC_INJ_ADDR_MASK_Address_P0_DEF                         (0x1FFFFFFFF)
  #define MC0_ECC_INJ_ADDR_MASK_Address_P0_HSH                         (0x6100D958)

#define MC0_SC_QOS2_P0_REG                                             (0x0000D960)

  #define MC0_SC_QOS2_RW_Isoch_time_window_P0_OFF                      ( 0)
  #define MC0_SC_QOS2_RW_Isoch_time_window_P0_WID                      (17)
  #define MC0_SC_QOS2_RW_Isoch_time_window_P0_MSK                      (0x0001FFFF)
  #define MC0_SC_QOS2_RW_Isoch_time_window_P0_MIN                      (0)
  #define MC0_SC_QOS2_RW_Isoch_time_window_P0_MAX                      (131071) // 0x0001FFFF
  #define MC0_SC_QOS2_RW_Isoch_time_window_P0_DEF                      (0x000000E1)
  #define MC0_SC_QOS2_RW_Isoch_time_window_P0_HSH                      (0x5100D960)

  #define MC0_SC_QOS2_RW_Write_starvation_window_P0_OFF                (17)
  #define MC0_SC_QOS2_RW_Write_starvation_window_P0_WID                (11)
  #define MC0_SC_QOS2_RW_Write_starvation_window_P0_MSK                (0x0FFE0000)
  #define MC0_SC_QOS2_RW_Write_starvation_window_P0_MIN                (0)
  #define MC0_SC_QOS2_RW_Write_starvation_window_P0_MAX                (2047) // 0x000007FF
  #define MC0_SC_QOS2_RW_Write_starvation_window_P0_DEF                (0x000001C2)
  #define MC0_SC_QOS2_RW_Write_starvation_window_P0_HSH                (0x4B22D960)

  #define MC0_SC_QOS2_RW_Read_starvation_window_P0_OFF                 (32)
  #define MC0_SC_QOS2_RW_Read_starvation_window_P0_WID                 (11)
  #define MC0_SC_QOS2_RW_Read_starvation_window_P0_MSK                 (0x000007FF00000000ULL)
  #define MC0_SC_QOS2_RW_Read_starvation_window_P0_MIN                 (0)
  #define MC0_SC_QOS2_RW_Read_starvation_window_P0_MAX                 (2047) // 0x000007FF
  #define MC0_SC_QOS2_RW_Read_starvation_window_P0_DEF                 (0x0000005A)
  #define MC0_SC_QOS2_RW_Read_starvation_window_P0_HSH                 (0x4B40D960)

  #define MC0_SC_QOS2_Isoc_during_demote_period_x8_P0_OFF              (43)
  #define MC0_SC_QOS2_Isoc_during_demote_period_x8_P0_WID              ( 8)
  #define MC0_SC_QOS2_Isoc_during_demote_period_x8_P0_MSK              (0x0007F80000000000ULL)
  #define MC0_SC_QOS2_Isoc_during_demote_period_x8_P0_MIN              (0)
  #define MC0_SC_QOS2_Isoc_during_demote_period_x8_P0_MAX              (255) // 0x000000FF
  #define MC0_SC_QOS2_Isoc_during_demote_period_x8_P0_DEF              (0x00000080)
  #define MC0_SC_QOS2_Isoc_during_demote_period_x8_P0_HSH              (0x4856D960)

  #define MC0_SC_QOS2_Isoc_during_demote_window_P0_OFF                 (51)
  #define MC0_SC_QOS2_Isoc_during_demote_window_P0_WID                 ( 8)
  #define MC0_SC_QOS2_Isoc_during_demote_window_P0_MSK                 (0x07F8000000000000ULL)
  #define MC0_SC_QOS2_Isoc_during_demote_window_P0_MIN                 (0)
  #define MC0_SC_QOS2_Isoc_during_demote_window_P0_MAX                 (255) // 0x000000FF
  #define MC0_SC_QOS2_Isoc_during_demote_window_P0_DEF                 (0x00000040)
  #define MC0_SC_QOS2_Isoc_during_demote_window_P0_HSH                 (0x4866D960)

#define MC0_SC_QOS3_P0_REG                                             (0x0000D968)

  #define MC0_SC_QOS3_Yellow_Decay_x128_P0_OFF                         ( 0)
  #define MC0_SC_QOS3_Yellow_Decay_x128_P0_WID                         ( 9)
  #define MC0_SC_QOS3_Yellow_Decay_x128_P0_MSK                         (0x000001FF)
  #define MC0_SC_QOS3_Yellow_Decay_x128_P0_MIN                         (0)
  #define MC0_SC_QOS3_Yellow_Decay_x128_P0_MAX                         (511) // 0x000001FF
  #define MC0_SC_QOS3_Yellow_Decay_x128_P0_DEF                         (0x0000007D)
  #define MC0_SC_QOS3_Yellow_Decay_x128_P0_HSH                         (0x0900D968)

  #define MC0_SC_QOS3_Yellow_Threshold_P0_OFF                          ( 9)
  #define MC0_SC_QOS3_Yellow_Threshold_P0_WID                          (10)
  #define MC0_SC_QOS3_Yellow_Threshold_P0_MSK                          (0x0007FE00)
  #define MC0_SC_QOS3_Yellow_Threshold_P0_MIN                          (0)
  #define MC0_SC_QOS3_Yellow_Threshold_P0_MAX                          (1023) // 0x000003FF
  #define MC0_SC_QOS3_Yellow_Threshold_P0_DEF                          (0x000000A0)
  #define MC0_SC_QOS3_Yellow_Threshold_P0_HSH                          (0x0A12D968)

#define MC0_NORMALMODE_CFG_P0_REG                                      (0x0000D96C)

  #define MC0_NORMALMODE_CFG_normalmode_P0_OFF                         ( 0)
  #define MC0_NORMALMODE_CFG_normalmode_P0_WID                         ( 1)
  #define MC0_NORMALMODE_CFG_normalmode_P0_MSK                         (0x00000001)
  #define MC0_NORMALMODE_CFG_normalmode_P0_MIN                         (0)
  #define MC0_NORMALMODE_CFG_normalmode_P0_MAX                         (1) // 0x00000001
  #define MC0_NORMALMODE_CFG_normalmode_P0_DEF                         (0x00000000)
  #define MC0_NORMALMODE_CFG_normalmode_P0_HSH                         (0x0100D96C)

#define MC0_MC_CPGC_CMI_P0_REG                                         (0x0000D970)

  #define MC0_MC_CPGC_CMI_CPGC_ACTIVE_P0_OFF                           (24)
  #define MC0_MC_CPGC_CMI_CPGC_ACTIVE_P0_WID                           ( 1)
  #define MC0_MC_CPGC_CMI_CPGC_ACTIVE_P0_MSK                           (0x01000000)
  #define MC0_MC_CPGC_CMI_CPGC_ACTIVE_P0_MIN                           (0)
  #define MC0_MC_CPGC_CMI_CPGC_ACTIVE_P0_MAX                           (1) // 0x00000001
  #define MC0_MC_CPGC_CMI_CPGC_ACTIVE_P0_DEF                           (0x00000000)
  #define MC0_MC_CPGC_CMI_CPGC_ACTIVE_P0_HSH                           (0x0130D970)

  #define MC0_MC_CPGC_CMI_CPGC_ECC_BYTE_P0_OFF                         (28)
  #define MC0_MC_CPGC_CMI_CPGC_ECC_BYTE_P0_WID                         ( 3)
  #define MC0_MC_CPGC_CMI_CPGC_ECC_BYTE_P0_MSK                         (0x70000000)
  #define MC0_MC_CPGC_CMI_CPGC_ECC_BYTE_P0_MIN                         (0)
  #define MC0_MC_CPGC_CMI_CPGC_ECC_BYTE_P0_MAX                         (7) // 0x00000007
  #define MC0_MC_CPGC_CMI_CPGC_ECC_BYTE_P0_DEF                         (0x00000000)
  #define MC0_MC_CPGC_CMI_CPGC_ECC_BYTE_P0_HSH                         (0x0338D970)

  #define MC0_MC_CPGC_CMI_Stall_CPGC_CMI_Req_P0_OFF                    (31)
  #define MC0_MC_CPGC_CMI_Stall_CPGC_CMI_Req_P0_WID                    ( 1)
  #define MC0_MC_CPGC_CMI_Stall_CPGC_CMI_Req_P0_MSK                    (0x80000000)
  #define MC0_MC_CPGC_CMI_Stall_CPGC_CMI_Req_P0_MIN                    (0)
  #define MC0_MC_CPGC_CMI_Stall_CPGC_CMI_Req_P0_MAX                    (1) // 0x00000001
  #define MC0_MC_CPGC_CMI_Stall_CPGC_CMI_Req_P0_DEF                    (0x00000000)
  #define MC0_MC_CPGC_CMI_Stall_CPGC_CMI_Req_P0_HSH                    (0x013ED970)

#define MC0_MC_CPGC_MISC_DFT_P0_REG                                    (0x0000D974)

  #define MC0_MC_CPGC_MISC_DFT_Concat_Row2Col_P0_OFF                   ( 0)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Row2Col_P0_WID                   ( 1)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Row2Col_P0_MSK                   (0x00000001)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Row2Col_P0_MIN                   (0)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Row2Col_P0_MAX                   (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_Concat_Row2Col_P0_DEF                   (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Row2Col_P0_HSH                   (0x0100D974)

  #define MC0_MC_CPGC_MISC_DFT_Col_align_P0_OFF                        ( 1)
  #define MC0_MC_CPGC_MISC_DFT_Col_align_P0_WID                        ( 3)
  #define MC0_MC_CPGC_MISC_DFT_Col_align_P0_MSK                        (0x0000000E)
  #define MC0_MC_CPGC_MISC_DFT_Col_align_P0_MIN                        (0)
  #define MC0_MC_CPGC_MISC_DFT_Col_align_P0_MAX                        (7) // 0x00000007
  #define MC0_MC_CPGC_MISC_DFT_Col_align_P0_DEF                        (0x00000003)
  #define MC0_MC_CPGC_MISC_DFT_Col_align_P0_HSH                        (0x0302D974)

  #define MC0_MC_CPGC_MISC_DFT_Concat_Bank2Row_P0_OFF                  ( 4)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Bank2Row_P0_WID                  ( 1)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Bank2Row_P0_MSK                  (0x00000010)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Bank2Row_P0_MIN                  (0)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Bank2Row_P0_MAX                  (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_Concat_Bank2Row_P0_DEF                  (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Bank2Row_P0_HSH                  (0x0108D974)

  #define MC0_MC_CPGC_MISC_DFT_Concat_Col2Row_P0_OFF                   ( 5)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Col2Row_P0_WID                   ( 1)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Col2Row_P0_MSK                   (0x00000020)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Col2Row_P0_MIN                   (0)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Col2Row_P0_MAX                   (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_Concat_Col2Row_P0_DEF                   (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_Concat_Col2Row_P0_HSH                   (0x010AD974)

  #define MC0_MC_CPGC_MISC_DFT_Row_align_P0_OFF                        ( 6)
  #define MC0_MC_CPGC_MISC_DFT_Row_align_P0_WID                        ( 3)
  #define MC0_MC_CPGC_MISC_DFT_Row_align_P0_MSK                        (0x000001C0)
  #define MC0_MC_CPGC_MISC_DFT_Row_align_P0_MIN                        (0)
  #define MC0_MC_CPGC_MISC_DFT_Row_align_P0_MAX                        (7) // 0x00000007
  #define MC0_MC_CPGC_MISC_DFT_Row_align_P0_DEF                        (0x00000003)
  #define MC0_MC_CPGC_MISC_DFT_Row_align_P0_HSH                        (0x030CD974)

  #define MC0_MC_CPGC_MISC_DFT_Concat_BG2Bank_P0_OFF                   ( 9)
  #define MC0_MC_CPGC_MISC_DFT_Concat_BG2Bank_P0_WID                   ( 1)
  #define MC0_MC_CPGC_MISC_DFT_Concat_BG2Bank_P0_MSK                   (0x00000200)
  #define MC0_MC_CPGC_MISC_DFT_Concat_BG2Bank_P0_MIN                   (0)
  #define MC0_MC_CPGC_MISC_DFT_Concat_BG2Bank_P0_MAX                   (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_Concat_BG2Bank_P0_DEF                   (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_Concat_BG2Bank_P0_HSH                   (0x0112D974)

  #define MC0_MC_CPGC_MISC_DFT_dis_BankGroup_P0_OFF                    (10)
  #define MC0_MC_CPGC_MISC_DFT_dis_BankGroup_P0_WID                    ( 1)
  #define MC0_MC_CPGC_MISC_DFT_dis_BankGroup_P0_MSK                    (0x00000400)
  #define MC0_MC_CPGC_MISC_DFT_dis_BankGroup_P0_MIN                    (0)
  #define MC0_MC_CPGC_MISC_DFT_dis_BankGroup_P0_MAX                    (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_dis_BankGroup_P0_DEF                    (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_dis_BankGroup_P0_HSH                    (0x0114D974)

  #define MC0_MC_CPGC_MISC_DFT_Rank_as_it_P0_OFF                       (11)
  #define MC0_MC_CPGC_MISC_DFT_Rank_as_it_P0_WID                       ( 1)
  #define MC0_MC_CPGC_MISC_DFT_Rank_as_it_P0_MSK                       (0x00000800)
  #define MC0_MC_CPGC_MISC_DFT_Rank_as_it_P0_MIN                       (0)
  #define MC0_MC_CPGC_MISC_DFT_Rank_as_it_P0_MAX                       (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_Rank_as_it_P0_DEF                       (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_Rank_as_it_P0_HSH                       (0x0116D974)

  #define MC0_MC_CPGC_MISC_DFT_channel_is_CID_Zero_P0_OFF              (12)
  #define MC0_MC_CPGC_MISC_DFT_channel_is_CID_Zero_P0_WID              ( 1)
  #define MC0_MC_CPGC_MISC_DFT_channel_is_CID_Zero_P0_MSK              (0x00001000)
  #define MC0_MC_CPGC_MISC_DFT_channel_is_CID_Zero_P0_MIN              (0)
  #define MC0_MC_CPGC_MISC_DFT_channel_is_CID_Zero_P0_MAX              (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_channel_is_CID_Zero_P0_DEF              (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_channel_is_CID_Zero_P0_HSH              (0x0118D974)

  #define MC0_MC_CPGC_MISC_DFT_Inverse_channel_P0_OFF                  (13)
  #define MC0_MC_CPGC_MISC_DFT_Inverse_channel_P0_WID                  ( 1)
  #define MC0_MC_CPGC_MISC_DFT_Inverse_channel_P0_MSK                  (0x00002000)
  #define MC0_MC_CPGC_MISC_DFT_Inverse_channel_P0_MIN                  (0)
  #define MC0_MC_CPGC_MISC_DFT_Inverse_channel_P0_MAX                  (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_Inverse_channel_P0_DEF                  (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_Inverse_channel_P0_HSH                  (0x011AD974)

  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_info_P0_OFF                   (14)
  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_info_P0_WID                   ( 1)
  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_info_P0_MSK                   (0x00004000)
  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_info_P0_MIN                   (0)
  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_info_P0_MAX                   (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_info_P0_DEF                   (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_info_P0_HSH                   (0x011CD974)

  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_data_P0_OFF                   (15)
  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_data_P0_WID                   ( 1)
  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_data_P0_MSK                   (0x00008000)
  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_data_P0_MIN                   (0)
  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_data_P0_MAX                   (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_data_P0_DEF                   (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_Delay_cpl_data_P0_HSH                   (0x011ED974)

  #define MC0_MC_CPGC_MISC_DFT_Reset_CPGC_P0_OFF                       (16)
  #define MC0_MC_CPGC_MISC_DFT_Reset_CPGC_P0_WID                       ( 1)
  #define MC0_MC_CPGC_MISC_DFT_Reset_CPGC_P0_MSK                       (0x00010000)
  #define MC0_MC_CPGC_MISC_DFT_Reset_CPGC_P0_MIN                       (0)
  #define MC0_MC_CPGC_MISC_DFT_Reset_CPGC_P0_MAX                       (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_Reset_CPGC_P0_DEF                       (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_Reset_CPGC_P0_HSH                       (0x0120D974)

  #define MC0_MC_CPGC_MISC_DFT_Lock_On_Active_CPGC_CMI_ISM_P0_OFF      (17)
  #define MC0_MC_CPGC_MISC_DFT_Lock_On_Active_CPGC_CMI_ISM_P0_WID      ( 1)
  #define MC0_MC_CPGC_MISC_DFT_Lock_On_Active_CPGC_CMI_ISM_P0_MSK      (0x00020000)
  #define MC0_MC_CPGC_MISC_DFT_Lock_On_Active_CPGC_CMI_ISM_P0_MIN      (0)
  #define MC0_MC_CPGC_MISC_DFT_Lock_On_Active_CPGC_CMI_ISM_P0_MAX      (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_Lock_On_Active_CPGC_CMI_ISM_P0_DEF      (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_Lock_On_Active_CPGC_CMI_ISM_P0_HSH      (0x0122D974)

  #define MC0_MC_CPGC_MISC_DFT_BG1_mask_P0_OFF                         (18)
  #define MC0_MC_CPGC_MISC_DFT_BG1_mask_P0_WID                         ( 1)
  #define MC0_MC_CPGC_MISC_DFT_BG1_mask_P0_MSK                         (0x00040000)
  #define MC0_MC_CPGC_MISC_DFT_BG1_mask_P0_MIN                         (0)
  #define MC0_MC_CPGC_MISC_DFT_BG1_mask_P0_MAX                         (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_BG1_mask_P0_DEF                         (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_BG1_mask_P0_HSH                         (0x0124D974)

  #define MC0_MC_CPGC_MISC_DFT_Rank1_as_ERM_BG1_P0_OFF                 (19)
  #define MC0_MC_CPGC_MISC_DFT_Rank1_as_ERM_BG1_P0_WID                 ( 1)
  #define MC0_MC_CPGC_MISC_DFT_Rank1_as_ERM_BG1_P0_MSK                 (0x00080000)
  #define MC0_MC_CPGC_MISC_DFT_Rank1_as_ERM_BG1_P0_MIN                 (0)
  #define MC0_MC_CPGC_MISC_DFT_Rank1_as_ERM_BG1_P0_MAX                 (1) // 0x00000001
  #define MC0_MC_CPGC_MISC_DFT_Rank1_as_ERM_BG1_P0_DEF                 (0x00000000)
  #define MC0_MC_CPGC_MISC_DFT_Rank1_as_ERM_BG1_P0_HSH                 (0x0126D974)

#define MC0_PWM_GLB_DRV_OFF_COUNT_P0_REG                               (0x0000D978)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_P0_REG

#define MC0_PARITYERRLOG_P0_REG                                        (0x0000D9A0)

  #define MC0_PARITYERRLOG_ERR_ADDRESS_P0_OFF                          ( 0)
  #define MC0_PARITYERRLOG_ERR_ADDRESS_P0_WID                          (39)
  #define MC0_PARITYERRLOG_ERR_ADDRESS_P0_MSK                          (0x0000007FFFFFFFFFULL)
  #define MC0_PARITYERRLOG_ERR_ADDRESS_P0_MIN                          (0)
  #define MC0_PARITYERRLOG_ERR_ADDRESS_P0_MAX                          (549755813887ULL) // 0x7FFFFFFFFF
  #define MC0_PARITYERRLOG_ERR_ADDRESS_P0_DEF                          (0x00000000)
  #define MC0_PARITYERRLOG_ERR_ADDRESS_P0_HSH                          (0x6700D9A0)

  #define MC0_PARITYERRLOG_RESERVED_P0_OFF                             (39)
  #define MC0_PARITYERRLOG_RESERVED_P0_WID                             (21)
  #define MC0_PARITYERRLOG_RESERVED_P0_MSK                             (0x0FFFFF8000000000ULL)
  #define MC0_PARITYERRLOG_RESERVED_P0_MIN                             (0)
  #define MC0_PARITYERRLOG_RESERVED_P0_MAX                             (2097151) // 0x001FFFFF
  #define MC0_PARITYERRLOG_RESERVED_P0_DEF                             (0x00000000)
  #define MC0_PARITYERRLOG_RESERVED_P0_HSH                             (0x554ED9A0)

  #define MC0_PARITYERRLOG_ERR_SRC_P0_OFF                              (60)
  #define MC0_PARITYERRLOG_ERR_SRC_P0_WID                              ( 1)
  #define MC0_PARITYERRLOG_ERR_SRC_P0_MSK                              (0x1000000000000000ULL)
  #define MC0_PARITYERRLOG_ERR_SRC_P0_MIN                              (0)
  #define MC0_PARITYERRLOG_ERR_SRC_P0_MAX                              (1) // 0x00000001
  #define MC0_PARITYERRLOG_ERR_SRC_P0_DEF                              (0x00000000)
  #define MC0_PARITYERRLOG_ERR_SRC_P0_HSH                              (0x4178D9A0)

  #define MC0_PARITYERRLOG_ERR_TYPE_P0_OFF                             (61)
  #define MC0_PARITYERRLOG_ERR_TYPE_P0_WID                             ( 2)
  #define MC0_PARITYERRLOG_ERR_TYPE_P0_MSK                             (0x6000000000000000ULL)
  #define MC0_PARITYERRLOG_ERR_TYPE_P0_MIN                             (0)
  #define MC0_PARITYERRLOG_ERR_TYPE_P0_MAX                             (3) // 0x00000003
  #define MC0_PARITYERRLOG_ERR_TYPE_P0_DEF                             (0x00000000)
  #define MC0_PARITYERRLOG_ERR_TYPE_P0_HSH                             (0x427AD9A0)

  #define MC0_PARITYERRLOG_ERR_STS_P0_OFF                              (63)
  #define MC0_PARITYERRLOG_ERR_STS_P0_WID                              ( 1)
  #define MC0_PARITYERRLOG_ERR_STS_P0_MSK                              (0x8000000000000000ULL)
  #define MC0_PARITYERRLOG_ERR_STS_P0_MIN                              (0)
  #define MC0_PARITYERRLOG_ERR_STS_P0_MAX                              (1) // 0x00000001
  #define MC0_PARITYERRLOG_ERR_STS_P0_DEF                              (0x00000000)
  #define MC0_PARITYERRLOG_ERR_STS_P0_HSH                              (0x417ED9A0)

#define MC0_PARITY_ERR_INJ_P0_REG                                      (0x0000D9A8)

  #define MC0_PARITY_ERR_INJ_DATA_ERR_EN_P0_OFF                        ( 0)
  #define MC0_PARITY_ERR_INJ_DATA_ERR_EN_P0_WID                        ( 8)
  #define MC0_PARITY_ERR_INJ_DATA_ERR_EN_P0_MSK                        (0x000000FF)
  #define MC0_PARITY_ERR_INJ_DATA_ERR_EN_P0_MIN                        (0)
  #define MC0_PARITY_ERR_INJ_DATA_ERR_EN_P0_MAX                        (255) // 0x000000FF
  #define MC0_PARITY_ERR_INJ_DATA_ERR_EN_P0_DEF                        (0x00000000)
  #define MC0_PARITY_ERR_INJ_DATA_ERR_EN_P0_HSH                        (0x0800D9A8)

  #define MC0_PARITY_ERR_INJ_ADDR_ERR_EN_P0_OFF                        ( 8)
  #define MC0_PARITY_ERR_INJ_ADDR_ERR_EN_P0_WID                        ( 1)
  #define MC0_PARITY_ERR_INJ_ADDR_ERR_EN_P0_MSK                        (0x00000100)
  #define MC0_PARITY_ERR_INJ_ADDR_ERR_EN_P0_MIN                        (0)
  #define MC0_PARITY_ERR_INJ_ADDR_ERR_EN_P0_MAX                        (1) // 0x00000001
  #define MC0_PARITY_ERR_INJ_ADDR_ERR_EN_P0_DEF                        (0x00000000)
  #define MC0_PARITY_ERR_INJ_ADDR_ERR_EN_P0_HSH                        (0x0110D9A8)

  #define MC0_PARITY_ERR_INJ_BE_ERR_EN_P0_OFF                          ( 9)
  #define MC0_PARITY_ERR_INJ_BE_ERR_EN_P0_WID                          ( 2)
  #define MC0_PARITY_ERR_INJ_BE_ERR_EN_P0_MSK                          (0x00000600)
  #define MC0_PARITY_ERR_INJ_BE_ERR_EN_P0_MIN                          (0)
  #define MC0_PARITY_ERR_INJ_BE_ERR_EN_P0_MAX                          (3) // 0x00000003
  #define MC0_PARITY_ERR_INJ_BE_ERR_EN_P0_DEF                          (0x00000000)
  #define MC0_PARITY_ERR_INJ_BE_ERR_EN_P0_HSH                          (0x0212D9A8)

  #define MC0_PARITY_ERR_INJ_RSVD_P0_OFF                               (11)
  #define MC0_PARITY_ERR_INJ_RSVD_P0_WID                               ( 5)
  #define MC0_PARITY_ERR_INJ_RSVD_P0_MSK                               (0x0000F800)
  #define MC0_PARITY_ERR_INJ_RSVD_P0_MIN                               (0)
  #define MC0_PARITY_ERR_INJ_RSVD_P0_MAX                               (31) // 0x0000001F
  #define MC0_PARITY_ERR_INJ_RSVD_P0_DEF                               (0x00000000)
  #define MC0_PARITY_ERR_INJ_RSVD_P0_HSH                               (0x0516D9A8)

  #define MC0_PARITY_ERR_INJ_ERR_INJ_MASK_P0_OFF                       (16)
  #define MC0_PARITY_ERR_INJ_ERR_INJ_MASK_P0_WID                       ( 5)
  #define MC0_PARITY_ERR_INJ_ERR_INJ_MASK_P0_MSK                       (0x001F0000)
  #define MC0_PARITY_ERR_INJ_ERR_INJ_MASK_P0_MIN                       (0)
  #define MC0_PARITY_ERR_INJ_ERR_INJ_MASK_P0_MAX                       (31) // 0x0000001F
  #define MC0_PARITY_ERR_INJ_ERR_INJ_MASK_P0_DEF                       (0x00000000)
  #define MC0_PARITY_ERR_INJ_ERR_INJ_MASK_P0_HSH                       (0x0520D9A8)

  #define MC0_PARITY_ERR_INJ_RSVD2_P0_OFF                              (21)
  #define MC0_PARITY_ERR_INJ_RSVD2_P0_WID                              (10)
  #define MC0_PARITY_ERR_INJ_RSVD2_P0_MSK                              (0x7FE00000)
  #define MC0_PARITY_ERR_INJ_RSVD2_P0_MIN                              (0)
  #define MC0_PARITY_ERR_INJ_RSVD2_P0_MAX                              (1023) // 0x000003FF
  #define MC0_PARITY_ERR_INJ_RSVD2_P0_DEF                              (0x00000000)
  #define MC0_PARITY_ERR_INJ_RSVD2_P0_HSH                              (0x0A2AD9A8)

  #define MC0_PARITY_ERR_INJ_DATA_ERR_INJ_SRC_P0_OFF                   (31)
  #define MC0_PARITY_ERR_INJ_DATA_ERR_INJ_SRC_P0_WID                   ( 1)
  #define MC0_PARITY_ERR_INJ_DATA_ERR_INJ_SRC_P0_MSK                   (0x80000000)
  #define MC0_PARITY_ERR_INJ_DATA_ERR_INJ_SRC_P0_MIN                   (0)
  #define MC0_PARITY_ERR_INJ_DATA_ERR_INJ_SRC_P0_MAX                   (1) // 0x00000001
  #define MC0_PARITY_ERR_INJ_DATA_ERR_INJ_SRC_P0_DEF                   (0x00000000)
  #define MC0_PARITY_ERR_INJ_DATA_ERR_INJ_SRC_P0_HSH                   (0x013ED9A8)

#define MC0_PARITY_CONTROL_P0_REG                                      (0x0000D9B4)

  #define MC0_PARITY_CONTROL_ADDR_PARITY_EN_P0_OFF                     ( 0)
  #define MC0_PARITY_CONTROL_ADDR_PARITY_EN_P0_WID                     ( 1)
  #define MC0_PARITY_CONTROL_ADDR_PARITY_EN_P0_MSK                     (0x00000001)
  #define MC0_PARITY_CONTROL_ADDR_PARITY_EN_P0_MIN                     (0)
  #define MC0_PARITY_CONTROL_ADDR_PARITY_EN_P0_MAX                     (1) // 0x00000001
  #define MC0_PARITY_CONTROL_ADDR_PARITY_EN_P0_DEF                     (0x00000001)
  #define MC0_PARITY_CONTROL_ADDR_PARITY_EN_P0_HSH                     (0x0100D9B4)

  #define MC0_PARITY_CONTROL_WBE_PARITY_EN_P0_OFF                      ( 1)
  #define MC0_PARITY_CONTROL_WBE_PARITY_EN_P0_WID                      ( 1)
  #define MC0_PARITY_CONTROL_WBE_PARITY_EN_P0_MSK                      (0x00000002)
  #define MC0_PARITY_CONTROL_WBE_PARITY_EN_P0_MIN                      (0)
  #define MC0_PARITY_CONTROL_WBE_PARITY_EN_P0_MAX                      (1) // 0x00000001
  #define MC0_PARITY_CONTROL_WBE_PARITY_EN_P0_DEF                      (0x00000001)
  #define MC0_PARITY_CONTROL_WBE_PARITY_EN_P0_HSH                      (0x0102D9B4)

  #define MC0_PARITY_CONTROL_WDATA_PARITY_EN_P0_OFF                    ( 2)
  #define MC0_PARITY_CONTROL_WDATA_PARITY_EN_P0_WID                    ( 2)
  #define MC0_PARITY_CONTROL_WDATA_PARITY_EN_P0_MSK                    (0x0000000C)
  #define MC0_PARITY_CONTROL_WDATA_PARITY_EN_P0_MIN                    (0)
  #define MC0_PARITY_CONTROL_WDATA_PARITY_EN_P0_MAX                    (3) // 0x00000003
  #define MC0_PARITY_CONTROL_WDATA_PARITY_EN_P0_DEF                    (0x00000003)
  #define MC0_PARITY_CONTROL_WDATA_PARITY_EN_P0_HSH                    (0x0204D9B4)

  #define MC0_PARITY_CONTROL_RDATA_PARITY_EN_P0_OFF                    ( 4)
  #define MC0_PARITY_CONTROL_RDATA_PARITY_EN_P0_WID                    ( 1)
  #define MC0_PARITY_CONTROL_RDATA_PARITY_EN_P0_MSK                    (0x00000010)
  #define MC0_PARITY_CONTROL_RDATA_PARITY_EN_P0_MIN                    (0)
  #define MC0_PARITY_CONTROL_RDATA_PARITY_EN_P0_MAX                    (1) // 0x00000001
  #define MC0_PARITY_CONTROL_RDATA_PARITY_EN_P0_DEF                    (0x00000001)
  #define MC0_PARITY_CONTROL_RDATA_PARITY_EN_P0_HSH                    (0x0108D9B4)

  #define MC0_PARITY_CONTROL_RSVD_0_P0_OFF                             ( 5)
  #define MC0_PARITY_CONTROL_RSVD_0_P0_WID                             ( 3)
  #define MC0_PARITY_CONTROL_RSVD_0_P0_MSK                             (0x000000E0)
  #define MC0_PARITY_CONTROL_RSVD_0_P0_MIN                             (0)
  #define MC0_PARITY_CONTROL_RSVD_0_P0_MAX                             (7) // 0x00000007
  #define MC0_PARITY_CONTROL_RSVD_0_P0_DEF                             (0x00000000)
  #define MC0_PARITY_CONTROL_RSVD_0_P0_HSH                             (0x030AD9B4)

  #define MC0_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_P0_OFF               ( 8)
  #define MC0_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_P0_WID               ( 1)
  #define MC0_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_P0_MSK               (0x00000100)
  #define MC0_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_P0_MIN               (0)
  #define MC0_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_P0_MAX               (1) // 0x00000001
  #define MC0_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_P0_DEF               (0x00000000)
  #define MC0_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_P0_HSH               (0x0110D9B4)

  #define MC0_PARITY_CONTROL_DIS_PARITY_LOG_P0_OFF                     ( 9)
  #define MC0_PARITY_CONTROL_DIS_PARITY_LOG_P0_WID                     ( 1)
  #define MC0_PARITY_CONTROL_DIS_PARITY_LOG_P0_MSK                     (0x00000200)
  #define MC0_PARITY_CONTROL_DIS_PARITY_LOG_P0_MIN                     (0)
  #define MC0_PARITY_CONTROL_DIS_PARITY_LOG_P0_MAX                     (1) // 0x00000001
  #define MC0_PARITY_CONTROL_DIS_PARITY_LOG_P0_DEF                     (0x00000000)
  #define MC0_PARITY_CONTROL_DIS_PARITY_LOG_P0_HSH                     (0x0112D9B4)

  #define MC0_PARITY_CONTROL_RSVD_1_P0_OFF                             (10)
  #define MC0_PARITY_CONTROL_RSVD_1_P0_WID                             (21)
  #define MC0_PARITY_CONTROL_RSVD_1_P0_MSK                             (0x7FFFFC00)
  #define MC0_PARITY_CONTROL_RSVD_1_P0_MIN                             (0)
  #define MC0_PARITY_CONTROL_RSVD_1_P0_MAX                             (2097151) // 0x001FFFFF
  #define MC0_PARITY_CONTROL_RSVD_1_P0_DEF                             (0x00000000)
  #define MC0_PARITY_CONTROL_RSVD_1_P0_HSH                             (0x1514D9B4)

  #define MC0_PARITY_CONTROL_PARITY_EN_P0_OFF                          (31)
  #define MC0_PARITY_CONTROL_PARITY_EN_P0_WID                          ( 1)
  #define MC0_PARITY_CONTROL_PARITY_EN_P0_MSK                          (0x80000000)
  #define MC0_PARITY_CONTROL_PARITY_EN_P0_MIN                          (0)
  #define MC0_PARITY_CONTROL_PARITY_EN_P0_MAX                          (1) // 0x00000001
  #define MC0_PARITY_CONTROL_PARITY_EN_P0_DEF                          (0x00000000)
  #define MC0_PARITY_CONTROL_PARITY_EN_P0_HSH                          (0x013ED9B4)

#define MC0_MC_JEDEC_INIT_TIMING_P0_REG                                (0x0000D9B8)

  #define MC0_MC_JEDEC_INIT_TIMING_reset_low_timer_P0_OFF              ( 0)
  #define MC0_MC_JEDEC_INIT_TIMING_reset_low_timer_P0_WID              (13)
  #define MC0_MC_JEDEC_INIT_TIMING_reset_low_timer_P0_MSK              (0x00001FFF)
  #define MC0_MC_JEDEC_INIT_TIMING_reset_low_timer_P0_MIN              (0)
  #define MC0_MC_JEDEC_INIT_TIMING_reset_low_timer_P0_MAX              (8191) // 0x00001FFF
  #define MC0_MC_JEDEC_INIT_TIMING_reset_low_timer_P0_DEF              (0x000000C8)
  #define MC0_MC_JEDEC_INIT_TIMING_reset_low_timer_P0_HSH              (0x0D00D9B8)

  #define MC0_MC_JEDEC_INIT_TIMING_cke_low_timer_P0_OFF                (13)
  #define MC0_MC_JEDEC_INIT_TIMING_cke_low_timer_P0_WID                (13)
  #define MC0_MC_JEDEC_INIT_TIMING_cke_low_timer_P0_MSK                (0x03FFE000)
  #define MC0_MC_JEDEC_INIT_TIMING_cke_low_timer_P0_MIN                (0)
  #define MC0_MC_JEDEC_INIT_TIMING_cke_low_timer_P0_MAX                (8191) // 0x00001FFF
  #define MC0_MC_JEDEC_INIT_TIMING_cke_low_timer_P0_DEF                (0x000007D0)
  #define MC0_MC_JEDEC_INIT_TIMING_cke_low_timer_P0_HSH                (0x0D1AD9B8)

  #define MC0_MC_JEDEC_INIT_TIMING_pre_cmd_timer_P0_OFF                (26)
  #define MC0_MC_JEDEC_INIT_TIMING_pre_cmd_timer_P0_WID                ( 6)
  #define MC0_MC_JEDEC_INIT_TIMING_pre_cmd_timer_P0_MSK                (0xFC000000)
  #define MC0_MC_JEDEC_INIT_TIMING_pre_cmd_timer_P0_MIN                (0)
  #define MC0_MC_JEDEC_INIT_TIMING_pre_cmd_timer_P0_MAX                (63) // 0x0000003F
  #define MC0_MC_JEDEC_INIT_TIMING_pre_cmd_timer_P0_DEF                (0x00000002)
  #define MC0_MC_JEDEC_INIT_TIMING_pre_cmd_timer_P0_HSH                (0x0634D9B8)

#define MC0_DDRPL_CFG_DTF_P0_REG                                       (0x0000DF00)

  #define MC0_DDRPL_CFG_DTF_MCHTrace_P0_OFF                            ( 4)
  #define MC0_DDRPL_CFG_DTF_MCHTrace_P0_WID                            ( 1)
  #define MC0_DDRPL_CFG_DTF_MCHTrace_P0_MSK                            (0x00000010)
  #define MC0_DDRPL_CFG_DTF_MCHTrace_P0_MIN                            (0)
  #define MC0_DDRPL_CFG_DTF_MCHTrace_P0_MAX                            (1) // 0x00000001
  #define MC0_DDRPL_CFG_DTF_MCHTrace_P0_DEF                            (0x00000000)
  #define MC0_DDRPL_CFG_DTF_MCHTrace_P0_HSH                            (0x0108DF00)

  #define MC0_DDRPL_CFG_DTF_SCHTrace_P0_OFF                            ( 5)
  #define MC0_DDRPL_CFG_DTF_SCHTrace_P0_WID                            ( 1)
  #define MC0_DDRPL_CFG_DTF_SCHTrace_P0_MSK                            (0x00000020)
  #define MC0_DDRPL_CFG_DTF_SCHTrace_P0_MIN                            (0)
  #define MC0_DDRPL_CFG_DTF_SCHTrace_P0_MAX                            (1) // 0x00000001
  #define MC0_DDRPL_CFG_DTF_SCHTrace_P0_DEF                            (0x00000000)
  #define MC0_DDRPL_CFG_DTF_SCHTrace_P0_HSH                            (0x010ADF00)

  #define MC0_DDRPL_CFG_DTF_ECC_EN_P0_OFF                              ( 6)
  #define MC0_DDRPL_CFG_DTF_ECC_EN_P0_WID                              ( 1)
  #define MC0_DDRPL_CFG_DTF_ECC_EN_P0_MSK                              (0x00000040)
  #define MC0_DDRPL_CFG_DTF_ECC_EN_P0_MIN                              (0)
  #define MC0_DDRPL_CFG_DTF_ECC_EN_P0_MAX                              (1) // 0x00000001
  #define MC0_DDRPL_CFG_DTF_ECC_EN_P0_DEF                              (0x00000000)
  #define MC0_DDRPL_CFG_DTF_ECC_EN_P0_HSH                              (0x010CDF00)

  #define MC0_DDRPL_CFG_DTF_ECC_BYTE_replace_P0_OFF                    ( 7)
  #define MC0_DDRPL_CFG_DTF_ECC_BYTE_replace_P0_WID                    ( 3)
  #define MC0_DDRPL_CFG_DTF_ECC_BYTE_replace_P0_MSK                    (0x00000380)
  #define MC0_DDRPL_CFG_DTF_ECC_BYTE_replace_P0_MIN                    (0)
  #define MC0_DDRPL_CFG_DTF_ECC_BYTE_replace_P0_MAX                    (7) // 0x00000007
  #define MC0_DDRPL_CFG_DTF_ECC_BYTE_replace_P0_DEF                    (0x00000000)
  #define MC0_DDRPL_CFG_DTF_ECC_BYTE_replace_P0_HSH                    (0x030EDF00)

  #define MC0_DDRPL_CFG_DTF_RSVD_16_10_P0_OFF                          (10)
  #define MC0_DDRPL_CFG_DTF_RSVD_16_10_P0_WID                          ( 7)
  #define MC0_DDRPL_CFG_DTF_RSVD_16_10_P0_MSK                          (0x0001FC00)
  #define MC0_DDRPL_CFG_DTF_RSVD_16_10_P0_MIN                          (0)
  #define MC0_DDRPL_CFG_DTF_RSVD_16_10_P0_MAX                          (127) // 0x0000007F
  #define MC0_DDRPL_CFG_DTF_RSVD_16_10_P0_DEF                          (0x00000000)
  #define MC0_DDRPL_CFG_DTF_RSVD_16_10_P0_HSH                          (0x0714DF00)

  #define MC0_DDRPL_CFG_DTF_Enable_ACC_Trace_P0_OFF                    (17)
  #define MC0_DDRPL_CFG_DTF_Enable_ACC_Trace_P0_WID                    ( 1)
  #define MC0_DDRPL_CFG_DTF_Enable_ACC_Trace_P0_MSK                    (0x00020000)
  #define MC0_DDRPL_CFG_DTF_Enable_ACC_Trace_P0_MIN                    (0)
  #define MC0_DDRPL_CFG_DTF_Enable_ACC_Trace_P0_MAX                    (1) // 0x00000001
  #define MC0_DDRPL_CFG_DTF_Enable_ACC_Trace_P0_DEF                    (0x00000001)
  #define MC0_DDRPL_CFG_DTF_Enable_ACC_Trace_P0_HSH                    (0x0122DF00)

  #define MC0_DDRPL_CFG_DTF_Enable_ReadData_Trace_P0_OFF               (18)
  #define MC0_DDRPL_CFG_DTF_Enable_ReadData_Trace_P0_WID               ( 1)
  #define MC0_DDRPL_CFG_DTF_Enable_ReadData_Trace_P0_MSK               (0x00040000)
  #define MC0_DDRPL_CFG_DTF_Enable_ReadData_Trace_P0_MIN               (0)
  #define MC0_DDRPL_CFG_DTF_Enable_ReadData_Trace_P0_MAX               (1) // 0x00000001
  #define MC0_DDRPL_CFG_DTF_Enable_ReadData_Trace_P0_DEF               (0x00000001)
  #define MC0_DDRPL_CFG_DTF_Enable_ReadData_Trace_P0_HSH               (0x0124DF00)

  #define MC0_DDRPL_CFG_DTF_Enable_WriteData_Trace_P0_OFF              (19)
  #define MC0_DDRPL_CFG_DTF_Enable_WriteData_Trace_P0_WID              ( 1)
  #define MC0_DDRPL_CFG_DTF_Enable_WriteData_Trace_P0_MSK              (0x00080000)
  #define MC0_DDRPL_CFG_DTF_Enable_WriteData_Trace_P0_MIN              (0)
  #define MC0_DDRPL_CFG_DTF_Enable_WriteData_Trace_P0_MAX              (1) // 0x00000001
  #define MC0_DDRPL_CFG_DTF_Enable_WriteData_Trace_P0_DEF              (0x00000001)
  #define MC0_DDRPL_CFG_DTF_Enable_WriteData_Trace_P0_HSH              (0x0126DF00)

  #define MC0_DDRPL_CFG_DTF_DDRPL_Activate_P0_OFF                      (20)
  #define MC0_DDRPL_CFG_DTF_DDRPL_Activate_P0_WID                      ( 1)
  #define MC0_DDRPL_CFG_DTF_DDRPL_Activate_P0_MSK                      (0x00100000)
  #define MC0_DDRPL_CFG_DTF_DDRPL_Activate_P0_MIN                      (0)
  #define MC0_DDRPL_CFG_DTF_DDRPL_Activate_P0_MAX                      (1) // 0x00000001
  #define MC0_DDRPL_CFG_DTF_DDRPL_Activate_P0_DEF                      (0x00000000)
  #define MC0_DDRPL_CFG_DTF_DDRPL_Activate_P0_HSH                      (0x0128DF00)

  #define MC0_DDRPL_CFG_DTF_DDRPL_GLB_DRV_GATE_DIS_P0_OFF              (21)
  #define MC0_DDRPL_CFG_DTF_DDRPL_GLB_DRV_GATE_DIS_P0_WID              ( 1)
  #define MC0_DDRPL_CFG_DTF_DDRPL_GLB_DRV_GATE_DIS_P0_MSK              (0x00200000)
  #define MC0_DDRPL_CFG_DTF_DDRPL_GLB_DRV_GATE_DIS_P0_MIN              (0)
  #define MC0_DDRPL_CFG_DTF_DDRPL_GLB_DRV_GATE_DIS_P0_MAX              (1) // 0x00000001
  #define MC0_DDRPL_CFG_DTF_DDRPL_GLB_DRV_GATE_DIS_P0_DEF              (0x00000000)
  #define MC0_DDRPL_CFG_DTF_DDRPL_GLB_DRV_GATE_DIS_P0_HSH              (0x012ADF00)

  #define MC0_DDRPL_CFG_DTF_RSVD_23_22_P0_OFF                          (22)
  #define MC0_DDRPL_CFG_DTF_RSVD_23_22_P0_WID                          ( 2)
  #define MC0_DDRPL_CFG_DTF_RSVD_23_22_P0_MSK                          (0x00C00000)
  #define MC0_DDRPL_CFG_DTF_RSVD_23_22_P0_MIN                          (0)
  #define MC0_DDRPL_CFG_DTF_RSVD_23_22_P0_MAX                          (3) // 0x00000003
  #define MC0_DDRPL_CFG_DTF_RSVD_23_22_P0_DEF                          (0x00000002)
  #define MC0_DDRPL_CFG_DTF_RSVD_23_22_P0_HSH                          (0x022CDF00)

  #define MC0_DDRPL_CFG_DTF_DTF_ENC_CB_P0_OFF                          (24)
  #define MC0_DDRPL_CFG_DTF_DTF_ENC_CB_P0_WID                          ( 1)
  #define MC0_DDRPL_CFG_DTF_DTF_ENC_CB_P0_MSK                          (0x01000000)
  #define MC0_DDRPL_CFG_DTF_DTF_ENC_CB_P0_MIN                          (0)
  #define MC0_DDRPL_CFG_DTF_DTF_ENC_CB_P0_MAX                          (1) // 0x00000001
  #define MC0_DDRPL_CFG_DTF_DTF_ENC_CB_P0_DEF                          (0x00000000)
  #define MC0_DDRPL_CFG_DTF_DTF_ENC_CB_P0_HSH                          (0x0130DF00)

  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_read_P0_OFF              (26)
  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_read_P0_WID              ( 1)
  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_read_P0_MSK              (0x04000000)
  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_read_P0_MIN              (0)
  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_read_P0_MAX              (1) // 0x00000001
  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_read_P0_DEF              (0x00000000)
  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_read_P0_HSH              (0x0134DF00)

  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_write_P0_OFF             (27)
  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_write_P0_WID             ( 1)
  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_write_P0_MSK             (0x08000000)
  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_write_P0_MIN             (0)
  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_write_P0_MAX             (1) // 0x00000001
  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_write_P0_DEF             (0x00000000)
  #define MC0_DDRPL_CFG_DTF_ddr4_bypass_trace_write_P0_HSH             (0x0136DF00)

  #define MC0_DDRPL_CFG_DTF_Trace_2LM_Tag_P0_OFF                       (28)
  #define MC0_DDRPL_CFG_DTF_Trace_2LM_Tag_P0_WID                       ( 1)
  #define MC0_DDRPL_CFG_DTF_Trace_2LM_Tag_P0_MSK                       (0x10000000)
  #define MC0_DDRPL_CFG_DTF_Trace_2LM_Tag_P0_MIN                       (0)
  #define MC0_DDRPL_CFG_DTF_Trace_2LM_Tag_P0_MAX                       (1) // 0x00000001
  #define MC0_DDRPL_CFG_DTF_Trace_2LM_Tag_P0_DEF                       (0x00000000)
  #define MC0_DDRPL_CFG_DTF_Trace_2LM_Tag_P0_HSH                       (0x0138DF00)

#define MC0_DDRPL_FILTER_DTF_P0_REG                                    (0x0000DF04)

  #define MC0_DDRPL_FILTER_DTF_Enable_ACC_Window_Filtering_P0_OFF      ( 0)
  #define MC0_DDRPL_FILTER_DTF_Enable_ACC_Window_Filtering_P0_WID      ( 1)
  #define MC0_DDRPL_FILTER_DTF_Enable_ACC_Window_Filtering_P0_MSK      (0x00000001)
  #define MC0_DDRPL_FILTER_DTF_Enable_ACC_Window_Filtering_P0_MIN      (0)
  #define MC0_DDRPL_FILTER_DTF_Enable_ACC_Window_Filtering_P0_MAX      (1) // 0x00000001
  #define MC0_DDRPL_FILTER_DTF_Enable_ACC_Window_Filtering_P0_DEF      (0x00000001)
  #define MC0_DDRPL_FILTER_DTF_Enable_ACC_Window_Filtering_P0_HSH      (0x0100DF04)

  #define MC0_DDRPL_FILTER_DTF_Filter_Window_Depth_P0_OFF              ( 1)
  #define MC0_DDRPL_FILTER_DTF_Filter_Window_Depth_P0_WID              ( 8)
  #define MC0_DDRPL_FILTER_DTF_Filter_Window_Depth_P0_MSK              (0x000001FE)
  #define MC0_DDRPL_FILTER_DTF_Filter_Window_Depth_P0_MIN              (0)
  #define MC0_DDRPL_FILTER_DTF_Filter_Window_Depth_P0_MAX              (255) // 0x000000FF
  #define MC0_DDRPL_FILTER_DTF_Filter_Window_Depth_P0_DEF              (0x000000FF)
  #define MC0_DDRPL_FILTER_DTF_Filter_Window_Depth_P0_HSH              (0x0802DF04)

#define MC0_DDRPL_DEBUG_DTF_P0_REG                                     (0x0000DF08)

  #define MC0_DDRPL_DEBUG_DTF_Read_Data_UserDefined_Bits_P0_OFF        (16)
  #define MC0_DDRPL_DEBUG_DTF_Read_Data_UserDefined_Bits_P0_WID        ( 8)
  #define MC0_DDRPL_DEBUG_DTF_Read_Data_UserDefined_Bits_P0_MSK        (0x00FF0000)
  #define MC0_DDRPL_DEBUG_DTF_Read_Data_UserDefined_Bits_P0_MIN        (0)
  #define MC0_DDRPL_DEBUG_DTF_Read_Data_UserDefined_Bits_P0_MAX        (255) // 0x000000FF
  #define MC0_DDRPL_DEBUG_DTF_Read_Data_UserDefined_Bits_P0_DEF        (0x00000000)
  #define MC0_DDRPL_DEBUG_DTF_Read_Data_UserDefined_Bits_P0_HSH        (0x0820DF08)

  #define MC0_DDRPL_DEBUG_DTF_Write_Data_UserDefined_Bits_P0_OFF       (24)
  #define MC0_DDRPL_DEBUG_DTF_Write_Data_UserDefined_Bits_P0_WID       ( 8)
  #define MC0_DDRPL_DEBUG_DTF_Write_Data_UserDefined_Bits_P0_MSK       (0xFF000000)
  #define MC0_DDRPL_DEBUG_DTF_Write_Data_UserDefined_Bits_P0_MIN       (0)
  #define MC0_DDRPL_DEBUG_DTF_Write_Data_UserDefined_Bits_P0_MAX       (255) // 0x000000FF
  #define MC0_DDRPL_DEBUG_DTF_Write_Data_UserDefined_Bits_P0_DEF       (0x00000000)
  #define MC0_DDRPL_DEBUG_DTF_Write_Data_UserDefined_Bits_P0_HSH       (0x0830DF08)

#define MC0_DDRPL_VISA_LANES_P0_REG                                    (0x0000DF0C)

  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_1_out_P0_OFF             ( 0)
  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_1_out_P0_WID             ( 8)
  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_1_out_P0_MSK             (0x000000FF)
  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_1_out_P0_MIN             (0)
  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_1_out_P0_MAX             (255) // 0x000000FF
  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_1_out_P0_DEF             (0x00000000)
  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_1_out_P0_HSH             (0x0800DF0C)

  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_0_out_P0_OFF             ( 8)
  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_0_out_P0_WID             ( 8)
  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_0_out_P0_MSK             (0x0000FF00)
  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_0_out_P0_MIN             (0)
  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_0_out_P0_MAX             (255) // 0x000000FF
  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_0_out_P0_DEF             (0x00000000)
  #define MC0_DDRPL_VISA_LANES_Visa_Qclk_Lane_0_out_P0_HSH             (0x0810DF0C)

  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_1_out_P0_OFF             (16)
  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_1_out_P0_WID             ( 8)
  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_1_out_P0_MSK             (0x00FF0000)
  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_1_out_P0_MIN             (0)
  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_1_out_P0_MAX             (255) // 0x000000FF
  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_1_out_P0_DEF             (0x00000000)
  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_1_out_P0_HSH             (0x0820DF0C)

  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_0_out_P0_OFF             (24)
  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_0_out_P0_WID             ( 8)
  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_0_out_P0_MSK             (0xFF000000)
  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_0_out_P0_MIN             (0)
  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_0_out_P0_MAX             (255) // 0x000000FF
  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_0_out_P0_DEF             (0x00000000)
  #define MC0_DDRPL_VISA_LANES_Visa_Dclk_Lane_0_out_P0_HSH             (0x0830DF0C)

#define MC0_DDRPL_VISA_CFG_DTF_P0_REG                                  (0x0000DF10)

  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Dclk_tree_P0_OFF ( 0)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Dclk_tree_P0_WID ( 2)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Dclk_tree_P0_MSK (0x00000003)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Dclk_tree_P0_MIN (0)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Dclk_tree_P0_MAX (3) // 0x00000003
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Dclk_tree_P0_DEF (0x00000000)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Dclk_tree_P0_HSH (0x0200DF10)

  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Dclk_tree_P0_OFF ( 2)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Dclk_tree_P0_WID ( 2)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Dclk_tree_P0_MSK (0x0000000C)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Dclk_tree_P0_MIN (0)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Dclk_tree_P0_MAX (3) // 0x00000003
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Dclk_tree_P0_DEF (0x00000000)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Dclk_tree_P0_HSH (0x0204DF10)

  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Qclk_tree_P0_OFF ( 4)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Qclk_tree_P0_WID ( 2)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Qclk_tree_P0_MSK (0x00000030)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Qclk_tree_P0_MIN (0)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Qclk_tree_P0_MAX (3) // 0x00000003
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Qclk_tree_P0_DEF (0x00000000)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane0_Data_Stage_Qclk_tree_P0_HSH (0x0208DF10)

  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Qclk_tree_P0_OFF ( 6)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Qclk_tree_P0_WID ( 2)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Qclk_tree_P0_MSK (0x000000C0)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Qclk_tree_P0_MIN (0)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Qclk_tree_P0_MAX (3) // 0x00000003
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Qclk_tree_P0_DEF (0x00000000)
  #define MC0_DDRPL_VISA_CFG_DTF_VisaLane1_Data_Stage_Qclk_tree_P0_HSH (0x020CDF10)
#pragma pack(pop)
#endif
