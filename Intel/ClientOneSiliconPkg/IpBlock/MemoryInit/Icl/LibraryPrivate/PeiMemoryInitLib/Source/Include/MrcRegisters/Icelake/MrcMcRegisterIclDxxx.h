#ifndef __MrcMcRegisterIclDxxx_h__
#define __MrcMcRegisterIclDxxx_h__
/** @file
  This file was automatically generated. Modify at your own risk.
  Note that no error checking is done in these functions so ensure that the correct values are passed.

@copyright
  Copyright (c) 2010 - 2017 Intel Corporation. All rights reserved
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


#define CH0_SC0_CR_CADB_ACCESS_CONTROL_POLICY_REG                      (0x0000D000)

  #define CH0_SC0_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_OFF     ( 0)
  #define CH0_SC0_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_WID     (64)
  #define CH0_SC0_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_MSK     (0xFFFFFFFFFFFFFFFFULL)
  #define CH0_SC0_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_MIN     (0)
  #define CH0_SC0_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_MAX     (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define CH0_SC0_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_DEF     (0x40001000208)
  #define CH0_SC0_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_HSH     (0x4000D000)

#define CH0_SC0_CR_CADB_ACCESS_READ_POLICY_REG                         (0x0000D008)

  #define CH0_SC0_CR_CADB_ACCESS_READ_POLICY_Read_Policy_OFF           ( 0)
  #define CH0_SC0_CR_CADB_ACCESS_READ_POLICY_Read_Policy_WID           (64)
  #define CH0_SC0_CR_CADB_ACCESS_READ_POLICY_Read_Policy_MSK           (0xFFFFFFFFFFFFFFFFULL)
  #define CH0_SC0_CR_CADB_ACCESS_READ_POLICY_Read_Policy_MIN           (0)
  #define CH0_SC0_CR_CADB_ACCESS_READ_POLICY_Read_Policy_MAX           (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define CH0_SC0_CR_CADB_ACCESS_READ_POLICY_Read_Policy_DEF           (0xFFFFFFFFFFFFFFFF)
  #define CH0_SC0_CR_CADB_ACCESS_READ_POLICY_Read_Policy_HSH           (0x4000D008)

#define CH0_SC0_CR_CADB_ACCESS_WRITE_POLICY_REG                        (0x0000D010)

  #define CH0_SC0_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_OFF         ( 0)
  #define CH0_SC0_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_WID         (64)
  #define CH0_SC0_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_MSK         (0xFFFFFFFFFFFFFFFFULL)
  #define CH0_SC0_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_MIN         (0)
  #define CH0_SC0_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_MAX         (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define CH0_SC0_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_DEF         (0x4000100021A)
  #define CH0_SC0_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_HSH         (0x4000D010)

#define CH0_SC0_CR_CADB_CTL_REG                                        (0x0000D020)

  #define CH0_SC0_CR_CADB_CTL_START_TEST_OFF                           ( 0)
  #define CH0_SC0_CR_CADB_CTL_START_TEST_WID                           ( 1)
  #define CH0_SC0_CR_CADB_CTL_START_TEST_MSK                           (0x00000001)
  #define CH0_SC0_CR_CADB_CTL_START_TEST_MIN                           (0)
  #define CH0_SC0_CR_CADB_CTL_START_TEST_MAX                           (1) // 0x00000001
  #define CH0_SC0_CR_CADB_CTL_START_TEST_DEF                           (0x00000000)
  #define CH0_SC0_CR_CADB_CTL_START_TEST_HSH                           (0x0100D020)

  #define CH0_SC0_CR_CADB_CTL_STOP_TEST_OFF                            ( 1)
  #define CH0_SC0_CR_CADB_CTL_STOP_TEST_WID                            ( 1)
  #define CH0_SC0_CR_CADB_CTL_STOP_TEST_MSK                            (0x00000002)
  #define CH0_SC0_CR_CADB_CTL_STOP_TEST_MIN                            (0)
  #define CH0_SC0_CR_CADB_CTL_STOP_TEST_MAX                            (1) // 0x00000001
  #define CH0_SC0_CR_CADB_CTL_STOP_TEST_DEF                            (0x00000000)
  #define CH0_SC0_CR_CADB_CTL_STOP_TEST_HSH                            (0x0101D020)

#define CH0_SC0_CR_CADB_CFG_REG                                        (0x0000D024)

  #define CH0_SC0_CR_CADB_CFG_CMD_DESELECT_START_OFF                   ( 0)
  #define CH0_SC0_CR_CADB_CFG_CMD_DESELECT_START_WID                   ( 4)
  #define CH0_SC0_CR_CADB_CFG_CMD_DESELECT_START_MSK                   (0x0000000F)
  #define CH0_SC0_CR_CADB_CFG_CMD_DESELECT_START_MIN                   (0)
  #define CH0_SC0_CR_CADB_CFG_CMD_DESELECT_START_MAX                   (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_CFG_CMD_DESELECT_START_DEF                   (0x00000000)
  #define CH0_SC0_CR_CADB_CFG_CMD_DESELECT_START_HSH                   (0x0400D024)

  #define CH0_SC0_CR_CADB_CFG_CMD_DESELECT_STOP_OFF                    ( 4)
  #define CH0_SC0_CR_CADB_CFG_CMD_DESELECT_STOP_WID                    ( 4)
  #define CH0_SC0_CR_CADB_CFG_CMD_DESELECT_STOP_MSK                    (0x000000F0)
  #define CH0_SC0_CR_CADB_CFG_CMD_DESELECT_STOP_MIN                    (0)
  #define CH0_SC0_CR_CADB_CFG_CMD_DESELECT_STOP_MAX                    (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_CFG_CMD_DESELECT_STOP_DEF                    (0x00000000)
  #define CH0_SC0_CR_CADB_CFG_CMD_DESELECT_STOP_HSH                    (0x0404D024)

  #define CH0_SC0_CR_CADB_CFG_LANE_DESELECT_EN_OFF                     ( 8)
  #define CH0_SC0_CR_CADB_CFG_LANE_DESELECT_EN_WID                     ( 3)
  #define CH0_SC0_CR_CADB_CFG_LANE_DESELECT_EN_MSK                     (0x00000700)
  #define CH0_SC0_CR_CADB_CFG_LANE_DESELECT_EN_MIN                     (0)
  #define CH0_SC0_CR_CADB_CFG_LANE_DESELECT_EN_MAX                     (7) // 0x00000007
  #define CH0_SC0_CR_CADB_CFG_LANE_DESELECT_EN_DEF                     (0x00000000)
  #define CH0_SC0_CR_CADB_CFG_LANE_DESELECT_EN_HSH                     (0x0308D024)

  #define CH0_SC0_CR_CADB_CFG_INITIAL_DSEL_EN_OFF                      (11)
  #define CH0_SC0_CR_CADB_CFG_INITIAL_DSEL_EN_WID                      ( 1)
  #define CH0_SC0_CR_CADB_CFG_INITIAL_DSEL_EN_MSK                      (0x00000800)
  #define CH0_SC0_CR_CADB_CFG_INITIAL_DSEL_EN_MIN                      (0)
  #define CH0_SC0_CR_CADB_CFG_INITIAL_DSEL_EN_MAX                      (1) // 0x00000001
  #define CH0_SC0_CR_CADB_CFG_INITIAL_DSEL_EN_DEF                      (0x00000001)
  #define CH0_SC0_CR_CADB_CFG_INITIAL_DSEL_EN_HSH                      (0x010BD024)

  #define CH0_SC0_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_OFF                 (12)
  #define CH0_SC0_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_WID                 ( 1)
  #define CH0_SC0_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_MSK                 (0x00001000)
  #define CH0_SC0_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_MIN                 (0)
  #define CH0_SC0_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_MAX                 (1) // 0x00000001
  #define CH0_SC0_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_DEF                 (0x00000001)
  #define CH0_SC0_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_HSH                 (0x010CD024)

  #define CH0_SC0_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_OFF              (13)
  #define CH0_SC0_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_WID              ( 3)
  #define CH0_SC0_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_MSK              (0x0000E000)
  #define CH0_SC0_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_MIN              (0)
  #define CH0_SC0_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_MAX              (7) // 0x00000007
  #define CH0_SC0_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_DEF              (0x00000000)
  #define CH0_SC0_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_HSH              (0x030DD024)

  #define CH0_SC0_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_OFF               (16)
  #define CH0_SC0_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_WID               ( 3)
  #define CH0_SC0_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_MSK               (0x00070000)
  #define CH0_SC0_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_MIN               (0)
  #define CH0_SC0_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_MAX               (7) // 0x00000007
  #define CH0_SC0_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_DEF               (0x00000000)
  #define CH0_SC0_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_HSH               (0x0310D024)

  #define CH0_SC0_CR_CADB_CFG_CADB_TO_CPGC_BIND_OFF                    (24)
  #define CH0_SC0_CR_CADB_CFG_CADB_TO_CPGC_BIND_WID                    ( 1)
  #define CH0_SC0_CR_CADB_CFG_CADB_TO_CPGC_BIND_MSK                    (0x01000000)
  #define CH0_SC0_CR_CADB_CFG_CADB_TO_CPGC_BIND_MIN                    (0)
  #define CH0_SC0_CR_CADB_CFG_CADB_TO_CPGC_BIND_MAX                    (1) // 0x00000001
  #define CH0_SC0_CR_CADB_CFG_CADB_TO_CPGC_BIND_DEF                    (0x00000000)
  #define CH0_SC0_CR_CADB_CFG_CADB_TO_CPGC_BIND_HSH                    (0x0118D024)

  #define CH0_SC0_CR_CADB_CFG_GLOBAL_START_BIND_OFF                    (25)
  #define CH0_SC0_CR_CADB_CFG_GLOBAL_START_BIND_WID                    ( 1)
  #define CH0_SC0_CR_CADB_CFG_GLOBAL_START_BIND_MSK                    (0x02000000)
  #define CH0_SC0_CR_CADB_CFG_GLOBAL_START_BIND_MIN                    (0)
  #define CH0_SC0_CR_CADB_CFG_GLOBAL_START_BIND_MAX                    (1) // 0x00000001
  #define CH0_SC0_CR_CADB_CFG_GLOBAL_START_BIND_DEF                    (0x00000000)
  #define CH0_SC0_CR_CADB_CFG_GLOBAL_START_BIND_HSH                    (0x0119D024)

  #define CH0_SC0_CR_CADB_CFG_GLOBAL_STOP_BIND_OFF                     (26)
  #define CH0_SC0_CR_CADB_CFG_GLOBAL_STOP_BIND_WID                     ( 1)
  #define CH0_SC0_CR_CADB_CFG_GLOBAL_STOP_BIND_MSK                     (0x04000000)
  #define CH0_SC0_CR_CADB_CFG_GLOBAL_STOP_BIND_MIN                     (0)
  #define CH0_SC0_CR_CADB_CFG_GLOBAL_STOP_BIND_MAX                     (1) // 0x00000001
  #define CH0_SC0_CR_CADB_CFG_GLOBAL_STOP_BIND_DEF                     (0x00000000)
  #define CH0_SC0_CR_CADB_CFG_GLOBAL_STOP_BIND_HSH                     (0x011AD024)

  #define CH0_SC0_CR_CADB_CFG_CADB_MODE_OFF                            (29)
  #define CH0_SC0_CR_CADB_CFG_CADB_MODE_WID                            ( 3)
  #define CH0_SC0_CR_CADB_CFG_CADB_MODE_MSK                            (0xE0000000)
  #define CH0_SC0_CR_CADB_CFG_CADB_MODE_MIN                            (0)
  #define CH0_SC0_CR_CADB_CFG_CADB_MODE_MAX                            (7) // 0x00000007
  #define CH0_SC0_CR_CADB_CFG_CADB_MODE_DEF                            (0x00000000)
  #define CH0_SC0_CR_CADB_CFG_CADB_MODE_HSH                            (0x031DD024)

#define CH0_SC0_CR_CADB_DLY_REG                                        (0x0000D028)

  #define CH0_SC0_CR_CADB_DLY_START_DELAY_OFF                          ( 0)
  #define CH0_SC0_CR_CADB_DLY_START_DELAY_WID                          (10)
  #define CH0_SC0_CR_CADB_DLY_START_DELAY_MSK                          (0x000003FF)
  #define CH0_SC0_CR_CADB_DLY_START_DELAY_MIN                          (0)
  #define CH0_SC0_CR_CADB_DLY_START_DELAY_MAX                          (1023) // 0x000003FF
  #define CH0_SC0_CR_CADB_DLY_START_DELAY_DEF                          (0x00000000)
  #define CH0_SC0_CR_CADB_DLY_START_DELAY_HSH                          (0x0A00D028)

  #define CH0_SC0_CR_CADB_DLY_STOP_DELAY_OFF                           (16)
  #define CH0_SC0_CR_CADB_DLY_STOP_DELAY_WID                           (10)
  #define CH0_SC0_CR_CADB_DLY_STOP_DELAY_MSK                           (0x03FF0000)
  #define CH0_SC0_CR_CADB_DLY_STOP_DELAY_MIN                           (0)
  #define CH0_SC0_CR_CADB_DLY_STOP_DELAY_MAX                           (1023) // 0x000003FF
  #define CH0_SC0_CR_CADB_DLY_STOP_DELAY_DEF                           (0x00000000)
  #define CH0_SC0_CR_CADB_DLY_STOP_DELAY_HSH                           (0x0A10D028)

#define CH0_SC0_CR_CADB_STATUS_REG                                     (0x0000D02C)

  #define CH0_SC0_CR_CADB_STATUS_MRS_CURR_PTR_OFF                      (21)
  #define CH0_SC0_CR_CADB_STATUS_MRS_CURR_PTR_WID                      ( 3)
  #define CH0_SC0_CR_CADB_STATUS_MRS_CURR_PTR_MSK                      (0x00E00000)
  #define CH0_SC0_CR_CADB_STATUS_MRS_CURR_PTR_MIN                      (0)
  #define CH0_SC0_CR_CADB_STATUS_MRS_CURR_PTR_MAX                      (7) // 0x00000007
  #define CH0_SC0_CR_CADB_STATUS_MRS_CURR_PTR_DEF                      (0x00000000)
  #define CH0_SC0_CR_CADB_STATUS_MRS_CURR_PTR_HSH                      (0x0315D02C)

  #define CH0_SC0_CR_CADB_STATUS_TEST_ABORTED_OFF                      (24)
  #define CH0_SC0_CR_CADB_STATUS_TEST_ABORTED_WID                      ( 1)
  #define CH0_SC0_CR_CADB_STATUS_TEST_ABORTED_MSK                      (0x01000000)
  #define CH0_SC0_CR_CADB_STATUS_TEST_ABORTED_MIN                      (0)
  #define CH0_SC0_CR_CADB_STATUS_TEST_ABORTED_MAX                      (1) // 0x00000001
  #define CH0_SC0_CR_CADB_STATUS_TEST_ABORTED_DEF                      (0x00000000)
  #define CH0_SC0_CR_CADB_STATUS_TEST_ABORTED_HSH                      (0x0118D02C)

  #define CH0_SC0_CR_CADB_STATUS_ALGO_DONE_OFF                         (28)
  #define CH0_SC0_CR_CADB_STATUS_ALGO_DONE_WID                         ( 1)
  #define CH0_SC0_CR_CADB_STATUS_ALGO_DONE_MSK                         (0x10000000)
  #define CH0_SC0_CR_CADB_STATUS_ALGO_DONE_MIN                         (0)
  #define CH0_SC0_CR_CADB_STATUS_ALGO_DONE_MAX                         (1) // 0x00000001
  #define CH0_SC0_CR_CADB_STATUS_ALGO_DONE_DEF                         (0x00000000)
  #define CH0_SC0_CR_CADB_STATUS_ALGO_DONE_HSH                         (0x011CD02C)

  #define CH0_SC0_CR_CADB_STATUS_START_TEST_DELAY_BUSY_OFF             (29)
  #define CH0_SC0_CR_CADB_STATUS_START_TEST_DELAY_BUSY_WID             ( 1)
  #define CH0_SC0_CR_CADB_STATUS_START_TEST_DELAY_BUSY_MSK             (0x20000000)
  #define CH0_SC0_CR_CADB_STATUS_START_TEST_DELAY_BUSY_MIN             (0)
  #define CH0_SC0_CR_CADB_STATUS_START_TEST_DELAY_BUSY_MAX             (1) // 0x00000001
  #define CH0_SC0_CR_CADB_STATUS_START_TEST_DELAY_BUSY_DEF             (0x00000000)
  #define CH0_SC0_CR_CADB_STATUS_START_TEST_DELAY_BUSY_HSH             (0x011DD02C)

  #define CH0_SC0_CR_CADB_STATUS_TEST_BUSY_OFF                         (30)
  #define CH0_SC0_CR_CADB_STATUS_TEST_BUSY_WID                         ( 1)
  #define CH0_SC0_CR_CADB_STATUS_TEST_BUSY_MSK                         (0x40000000)
  #define CH0_SC0_CR_CADB_STATUS_TEST_BUSY_MIN                         (0)
  #define CH0_SC0_CR_CADB_STATUS_TEST_BUSY_MAX                         (1) // 0x00000001
  #define CH0_SC0_CR_CADB_STATUS_TEST_BUSY_DEF                         (0x00000000)
  #define CH0_SC0_CR_CADB_STATUS_TEST_BUSY_HSH                         (0x011ED02C)

  #define CH0_SC0_CR_CADB_STATUS_TEST_DONE_OFF                         (31)
  #define CH0_SC0_CR_CADB_STATUS_TEST_DONE_WID                         ( 1)
  #define CH0_SC0_CR_CADB_STATUS_TEST_DONE_MSK                         (0x80000000)
  #define CH0_SC0_CR_CADB_STATUS_TEST_DONE_MIN                         (0)
  #define CH0_SC0_CR_CADB_STATUS_TEST_DONE_MAX                         (1) // 0x00000001
  #define CH0_SC0_CR_CADB_STATUS_TEST_DONE_DEF                         (0x00000000)
  #define CH0_SC0_CR_CADB_STATUS_TEST_DONE_HSH                         (0x011FD02C)

#define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_REG                          (0x0000D030)

  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_OFF            ( 0)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_WID            ( 2)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_MSK            (0x00000003)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_MIN            (0)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_MAX            (3) // 0x00000003
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_DEF            (0x00000001)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_HSH            (0x0200D030)

  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_OFF ( 3)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_WID ( 3)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_MSK (0x00000038)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_MIN (0)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_MAX (7) // 0x00000007
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_DEF (0x00000000)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_HSH (0x0303D030)

#define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_REG                          (0x0000D031)

  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_OFF            ( 0)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_WID            ( 2)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_MSK            (0x00000003)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_MIN            (0)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_MAX            (3) // 0x00000003
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_DEF            (0x00000001)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_HSH            (0x0200D031)

  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_OFF ( 3)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_WID ( 3)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_MSK (0x00000038)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_MIN (0)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_MAX (7) // 0x00000007
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_DEF (0x00000000)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_HSH (0x0303D031)

#define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_REG                          (0x0000D032)

  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_OFF            ( 0)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_WID            ( 2)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_MSK            (0x00000003)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_MIN            (0)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_MAX            (3) // 0x00000003
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_DEF            (0x00000001)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_HSH            (0x0200D032)

  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_OFF ( 3)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_WID ( 3)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_MSK (0x00000038)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_MIN (0)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_MAX (7) // 0x00000007
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_DEF (0x00000000)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_HSH (0x0303D032)

#define CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_0_REG                         (0x0000D034)

  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_OFF                   ( 0)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_WID                   (32)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_MSK                   (0xFFFFFFFF)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_MIN                   (0)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_MAX                   (4294967295) // 0xFFFFFFFF
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_DEF                   (0x0000AA55)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_HSH                   (0x2000D034)

#define CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_1_REG                         (0x0000D038)

  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_OFF                   ( 0)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_WID                   (32)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_MSK                   (0xFFFFFFFF)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_MIN                   (0)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_MAX                   (4294967295) // 0xFFFFFFFF
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_DEF                   (0x0000AA55)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_HSH                   (0x2000D038)

#define CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_2_REG                         (0x0000D03C)

  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_OFF                   ( 0)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_WID                   (32)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_MSK                   (0xFFFFFFFF)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_MIN                   (0)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_MAX                   (4294967295) // 0xFFFFFFFF
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_DEF                   (0x0000AA55)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_HSH                   (0x2000D03C)

#define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_REG                            (0x0000D040)

  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_OFF                    ( 0)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_WID                    ( 1)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_MSK                    (0x00000001)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_MIN                    (0)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_MAX                    (1) // 0x00000001
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_DEF                    (0x00000000)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_HSH                    (0x0100D040)

  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_OFF             ( 4)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_WID             ( 4)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_MSK             (0x000000F0)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_MIN             (0)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_MAX             (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_DEF             (0x00000000)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_HSH             (0x0404D040)

  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_OFF                    ( 8)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_WID                    ( 8)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_MSK                    (0x0000FF00)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_MIN                    (0)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_MAX                    (255) // 0x000000FF
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_DEF                    (0x00000000)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_HSH                    (0x0808D040)

  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_OFF                    (16)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_WID                    ( 8)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_MSK                    (0x00FF0000)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_MIN                    (0)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_MAX                    (255) // 0x000000FF
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_DEF                    (0x00000000)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_HSH                    (0x0810D040)

  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_OFF                    (24)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_WID                    ( 8)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_MSK                    (0xFF000000)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_MIN                    (0)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_MAX                    (255) // 0x000000FF
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_DEF                    (0x00000000)
  #define CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_HSH                    (0x0818D040)

#define CH0_SC0_CR_CADB_BUF_0_REG                                      (0x0000D048)

  #define CH0_SC0_CR_CADB_BUF_0_CS_OFF                                 ( 0)
  #define CH0_SC0_CR_CADB_BUF_0_CS_WID                                 ( 4)
  #define CH0_SC0_CR_CADB_BUF_0_CS_MSK                                 (0x0000000F)
  #define CH0_SC0_CR_CADB_BUF_0_CS_MIN                                 (0)
  #define CH0_SC0_CR_CADB_BUF_0_CS_MAX                                 (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_BUF_0_CS_DEF                                 (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_0_CS_HSH                                 (0x4400D048)

  #define CH0_SC0_CR_CADB_BUF_0_CID_OFF                                ( 4)
  #define CH0_SC0_CR_CADB_BUF_0_CID_WID                                ( 3)
  #define CH0_SC0_CR_CADB_BUF_0_CID_MSK                                (0x00000070)
  #define CH0_SC0_CR_CADB_BUF_0_CID_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_0_CID_MAX                                (7) // 0x00000007
  #define CH0_SC0_CR_CADB_BUF_0_CID_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_0_CID_HSH                                (0x4304D048)

  #define CH0_SC0_CR_CADB_BUF_0_ODT_OFF                                ( 7)
  #define CH0_SC0_CR_CADB_BUF_0_ODT_WID                                ( 4)
  #define CH0_SC0_CR_CADB_BUF_0_ODT_MSK                                (0x00000780)
  #define CH0_SC0_CR_CADB_BUF_0_ODT_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_0_ODT_MAX                                (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_BUF_0_ODT_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_0_ODT_HSH                                (0x4407D048)

  #define CH0_SC0_CR_CADB_BUF_0_CKE_OFF                                (11)
  #define CH0_SC0_CR_CADB_BUF_0_CKE_WID                                ( 4)
  #define CH0_SC0_CR_CADB_BUF_0_CKE_MSK                                (0x00007800)
  #define CH0_SC0_CR_CADB_BUF_0_CKE_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_0_CKE_MAX                                (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_BUF_0_CKE_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_0_CKE_HSH                                (0x440BD048)

  #define CH0_SC0_CR_CADB_BUF_0_USE_HALF_CA_OFF                        (15)
  #define CH0_SC0_CR_CADB_BUF_0_USE_HALF_CA_WID                        ( 1)
  #define CH0_SC0_CR_CADB_BUF_0_USE_HALF_CA_MSK                        (0x00008000)
  #define CH0_SC0_CR_CADB_BUF_0_USE_HALF_CA_MIN                        (0)
  #define CH0_SC0_CR_CADB_BUF_0_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH0_SC0_CR_CADB_BUF_0_USE_HALF_CA_DEF                        (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_0_USE_HALF_CA_HSH                        (0x410FD048)

  #define CH0_SC0_CR_CADB_BUF_0_VAL_OFF                                (16)
  #define CH0_SC0_CR_CADB_BUF_0_VAL_WID                                ( 1)
  #define CH0_SC0_CR_CADB_BUF_0_VAL_MSK                                (0x00010000)
  #define CH0_SC0_CR_CADB_BUF_0_VAL_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_0_VAL_MAX                                (1) // 0x00000001
  #define CH0_SC0_CR_CADB_BUF_0_VAL_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_0_VAL_HSH                                (0x4110D048)

  #define CH0_SC0_CR_CADB_BUF_0_PAR_OFF                                (17)
  #define CH0_SC0_CR_CADB_BUF_0_PAR_WID                                ( 1)
  #define CH0_SC0_CR_CADB_BUF_0_PAR_MSK                                (0x00020000)
  #define CH0_SC0_CR_CADB_BUF_0_PAR_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_0_PAR_MAX                                (1) // 0x00000001
  #define CH0_SC0_CR_CADB_BUF_0_PAR_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_0_PAR_HSH                                (0x4111D048)

  #define CH0_SC0_CR_CADB_BUF_0_CA_OFF                                 (18)
  #define CH0_SC0_CR_CADB_BUF_0_CA_WID                                 (24)
  #define CH0_SC0_CR_CADB_BUF_0_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH0_SC0_CR_CADB_BUF_0_CA_MIN                                 (0)
  #define CH0_SC0_CR_CADB_BUF_0_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH0_SC0_CR_CADB_BUF_0_CA_DEF                                 (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_0_CA_HSH                                 (0x5812D048)

#define CH0_SC0_CR_CADB_BUF_1_REG                                      (0x0000D050)

  #define CH0_SC0_CR_CADB_BUF_1_CS_OFF                                 ( 0)
  #define CH0_SC0_CR_CADB_BUF_1_CS_WID                                 ( 4)
  #define CH0_SC0_CR_CADB_BUF_1_CS_MSK                                 (0x0000000F)
  #define CH0_SC0_CR_CADB_BUF_1_CS_MIN                                 (0)
  #define CH0_SC0_CR_CADB_BUF_1_CS_MAX                                 (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_BUF_1_CS_DEF                                 (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_1_CS_HSH                                 (0x4400D050)

  #define CH0_SC0_CR_CADB_BUF_1_CID_OFF                                ( 4)
  #define CH0_SC0_CR_CADB_BUF_1_CID_WID                                ( 3)
  #define CH0_SC0_CR_CADB_BUF_1_CID_MSK                                (0x00000070)
  #define CH0_SC0_CR_CADB_BUF_1_CID_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_1_CID_MAX                                (7) // 0x00000007
  #define CH0_SC0_CR_CADB_BUF_1_CID_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_1_CID_HSH                                (0x4304D050)

  #define CH0_SC0_CR_CADB_BUF_1_ODT_OFF                                ( 7)
  #define CH0_SC0_CR_CADB_BUF_1_ODT_WID                                ( 4)
  #define CH0_SC0_CR_CADB_BUF_1_ODT_MSK                                (0x00000780)
  #define CH0_SC0_CR_CADB_BUF_1_ODT_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_1_ODT_MAX                                (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_BUF_1_ODT_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_1_ODT_HSH                                (0x4407D050)

  #define CH0_SC0_CR_CADB_BUF_1_CKE_OFF                                (11)
  #define CH0_SC0_CR_CADB_BUF_1_CKE_WID                                ( 4)
  #define CH0_SC0_CR_CADB_BUF_1_CKE_MSK                                (0x00007800)
  #define CH0_SC0_CR_CADB_BUF_1_CKE_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_1_CKE_MAX                                (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_BUF_1_CKE_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_1_CKE_HSH                                (0x440BD050)

  #define CH0_SC0_CR_CADB_BUF_1_USE_HALF_CA_OFF                        (15)
  #define CH0_SC0_CR_CADB_BUF_1_USE_HALF_CA_WID                        ( 1)
  #define CH0_SC0_CR_CADB_BUF_1_USE_HALF_CA_MSK                        (0x00008000)
  #define CH0_SC0_CR_CADB_BUF_1_USE_HALF_CA_MIN                        (0)
  #define CH0_SC0_CR_CADB_BUF_1_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH0_SC0_CR_CADB_BUF_1_USE_HALF_CA_DEF                        (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_1_USE_HALF_CA_HSH                        (0x410FD050)

  #define CH0_SC0_CR_CADB_BUF_1_VAL_OFF                                (16)
  #define CH0_SC0_CR_CADB_BUF_1_VAL_WID                                ( 1)
  #define CH0_SC0_CR_CADB_BUF_1_VAL_MSK                                (0x00010000)
  #define CH0_SC0_CR_CADB_BUF_1_VAL_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_1_VAL_MAX                                (1) // 0x00000001
  #define CH0_SC0_CR_CADB_BUF_1_VAL_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_1_VAL_HSH                                (0x4110D050)

  #define CH0_SC0_CR_CADB_BUF_1_PAR_OFF                                (17)
  #define CH0_SC0_CR_CADB_BUF_1_PAR_WID                                ( 1)
  #define CH0_SC0_CR_CADB_BUF_1_PAR_MSK                                (0x00020000)
  #define CH0_SC0_CR_CADB_BUF_1_PAR_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_1_PAR_MAX                                (1) // 0x00000001
  #define CH0_SC0_CR_CADB_BUF_1_PAR_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_1_PAR_HSH                                (0x4111D050)

  #define CH0_SC0_CR_CADB_BUF_1_CA_OFF                                 (18)
  #define CH0_SC0_CR_CADB_BUF_1_CA_WID                                 (24)
  #define CH0_SC0_CR_CADB_BUF_1_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH0_SC0_CR_CADB_BUF_1_CA_MIN                                 (0)
  #define CH0_SC0_CR_CADB_BUF_1_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH0_SC0_CR_CADB_BUF_1_CA_DEF                                 (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_1_CA_HSH                                 (0x5812D050)

#define CH0_SC0_CR_CADB_BUF_2_REG                                      (0x0000D058)

  #define CH0_SC0_CR_CADB_BUF_2_CS_OFF                                 ( 0)
  #define CH0_SC0_CR_CADB_BUF_2_CS_WID                                 ( 4)
  #define CH0_SC0_CR_CADB_BUF_2_CS_MSK                                 (0x0000000F)
  #define CH0_SC0_CR_CADB_BUF_2_CS_MIN                                 (0)
  #define CH0_SC0_CR_CADB_BUF_2_CS_MAX                                 (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_BUF_2_CS_DEF                                 (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_2_CS_HSH                                 (0x4400D058)

  #define CH0_SC0_CR_CADB_BUF_2_CID_OFF                                ( 4)
  #define CH0_SC0_CR_CADB_BUF_2_CID_WID                                ( 3)
  #define CH0_SC0_CR_CADB_BUF_2_CID_MSK                                (0x00000070)
  #define CH0_SC0_CR_CADB_BUF_2_CID_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_2_CID_MAX                                (7) // 0x00000007
  #define CH0_SC0_CR_CADB_BUF_2_CID_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_2_CID_HSH                                (0x4304D058)

  #define CH0_SC0_CR_CADB_BUF_2_ODT_OFF                                ( 7)
  #define CH0_SC0_CR_CADB_BUF_2_ODT_WID                                ( 4)
  #define CH0_SC0_CR_CADB_BUF_2_ODT_MSK                                (0x00000780)
  #define CH0_SC0_CR_CADB_BUF_2_ODT_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_2_ODT_MAX                                (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_BUF_2_ODT_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_2_ODT_HSH                                (0x4407D058)

  #define CH0_SC0_CR_CADB_BUF_2_CKE_OFF                                (11)
  #define CH0_SC0_CR_CADB_BUF_2_CKE_WID                                ( 4)
  #define CH0_SC0_CR_CADB_BUF_2_CKE_MSK                                (0x00007800)
  #define CH0_SC0_CR_CADB_BUF_2_CKE_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_2_CKE_MAX                                (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_BUF_2_CKE_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_2_CKE_HSH                                (0x440BD058)

  #define CH0_SC0_CR_CADB_BUF_2_USE_HALF_CA_OFF                        (15)
  #define CH0_SC0_CR_CADB_BUF_2_USE_HALF_CA_WID                        ( 1)
  #define CH0_SC0_CR_CADB_BUF_2_USE_HALF_CA_MSK                        (0x00008000)
  #define CH0_SC0_CR_CADB_BUF_2_USE_HALF_CA_MIN                        (0)
  #define CH0_SC0_CR_CADB_BUF_2_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH0_SC0_CR_CADB_BUF_2_USE_HALF_CA_DEF                        (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_2_USE_HALF_CA_HSH                        (0x410FD058)

  #define CH0_SC0_CR_CADB_BUF_2_VAL_OFF                                (16)
  #define CH0_SC0_CR_CADB_BUF_2_VAL_WID                                ( 1)
  #define CH0_SC0_CR_CADB_BUF_2_VAL_MSK                                (0x00010000)
  #define CH0_SC0_CR_CADB_BUF_2_VAL_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_2_VAL_MAX                                (1) // 0x00000001
  #define CH0_SC0_CR_CADB_BUF_2_VAL_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_2_VAL_HSH                                (0x4110D058)

  #define CH0_SC0_CR_CADB_BUF_2_PAR_OFF                                (17)
  #define CH0_SC0_CR_CADB_BUF_2_PAR_WID                                ( 1)
  #define CH0_SC0_CR_CADB_BUF_2_PAR_MSK                                (0x00020000)
  #define CH0_SC0_CR_CADB_BUF_2_PAR_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_2_PAR_MAX                                (1) // 0x00000001
  #define CH0_SC0_CR_CADB_BUF_2_PAR_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_2_PAR_HSH                                (0x4111D058)

  #define CH0_SC0_CR_CADB_BUF_2_CA_OFF                                 (18)
  #define CH0_SC0_CR_CADB_BUF_2_CA_WID                                 (24)
  #define CH0_SC0_CR_CADB_BUF_2_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH0_SC0_CR_CADB_BUF_2_CA_MIN                                 (0)
  #define CH0_SC0_CR_CADB_BUF_2_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH0_SC0_CR_CADB_BUF_2_CA_DEF                                 (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_2_CA_HSH                                 (0x5812D058)

#define CH0_SC0_CR_CADB_BUF_3_REG                                      (0x0000D060)

  #define CH0_SC0_CR_CADB_BUF_3_CS_OFF                                 ( 0)
  #define CH0_SC0_CR_CADB_BUF_3_CS_WID                                 ( 4)
  #define CH0_SC0_CR_CADB_BUF_3_CS_MSK                                 (0x0000000F)
  #define CH0_SC0_CR_CADB_BUF_3_CS_MIN                                 (0)
  #define CH0_SC0_CR_CADB_BUF_3_CS_MAX                                 (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_BUF_3_CS_DEF                                 (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_3_CS_HSH                                 (0x4400D060)

  #define CH0_SC0_CR_CADB_BUF_3_CID_OFF                                ( 4)
  #define CH0_SC0_CR_CADB_BUF_3_CID_WID                                ( 3)
  #define CH0_SC0_CR_CADB_BUF_3_CID_MSK                                (0x00000070)
  #define CH0_SC0_CR_CADB_BUF_3_CID_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_3_CID_MAX                                (7) // 0x00000007
  #define CH0_SC0_CR_CADB_BUF_3_CID_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_3_CID_HSH                                (0x4304D060)

  #define CH0_SC0_CR_CADB_BUF_3_ODT_OFF                                ( 7)
  #define CH0_SC0_CR_CADB_BUF_3_ODT_WID                                ( 4)
  #define CH0_SC0_CR_CADB_BUF_3_ODT_MSK                                (0x00000780)
  #define CH0_SC0_CR_CADB_BUF_3_ODT_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_3_ODT_MAX                                (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_BUF_3_ODT_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_3_ODT_HSH                                (0x4407D060)

  #define CH0_SC0_CR_CADB_BUF_3_CKE_OFF                                (11)
  #define CH0_SC0_CR_CADB_BUF_3_CKE_WID                                ( 4)
  #define CH0_SC0_CR_CADB_BUF_3_CKE_MSK                                (0x00007800)
  #define CH0_SC0_CR_CADB_BUF_3_CKE_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_3_CKE_MAX                                (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_BUF_3_CKE_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_3_CKE_HSH                                (0x440BD060)

  #define CH0_SC0_CR_CADB_BUF_3_USE_HALF_CA_OFF                        (15)
  #define CH0_SC0_CR_CADB_BUF_3_USE_HALF_CA_WID                        ( 1)
  #define CH0_SC0_CR_CADB_BUF_3_USE_HALF_CA_MSK                        (0x00008000)
  #define CH0_SC0_CR_CADB_BUF_3_USE_HALF_CA_MIN                        (0)
  #define CH0_SC0_CR_CADB_BUF_3_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH0_SC0_CR_CADB_BUF_3_USE_HALF_CA_DEF                        (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_3_USE_HALF_CA_HSH                        (0x410FD060)

  #define CH0_SC0_CR_CADB_BUF_3_VAL_OFF                                (16)
  #define CH0_SC0_CR_CADB_BUF_3_VAL_WID                                ( 1)
  #define CH0_SC0_CR_CADB_BUF_3_VAL_MSK                                (0x00010000)
  #define CH0_SC0_CR_CADB_BUF_3_VAL_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_3_VAL_MAX                                (1) // 0x00000001
  #define CH0_SC0_CR_CADB_BUF_3_VAL_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_3_VAL_HSH                                (0x4110D060)

  #define CH0_SC0_CR_CADB_BUF_3_PAR_OFF                                (17)
  #define CH0_SC0_CR_CADB_BUF_3_PAR_WID                                ( 1)
  #define CH0_SC0_CR_CADB_BUF_3_PAR_MSK                                (0x00020000)
  #define CH0_SC0_CR_CADB_BUF_3_PAR_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_3_PAR_MAX                                (1) // 0x00000001
  #define CH0_SC0_CR_CADB_BUF_3_PAR_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_3_PAR_HSH                                (0x4111D060)

  #define CH0_SC0_CR_CADB_BUF_3_CA_OFF                                 (18)
  #define CH0_SC0_CR_CADB_BUF_3_CA_WID                                 (24)
  #define CH0_SC0_CR_CADB_BUF_3_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH0_SC0_CR_CADB_BUF_3_CA_MIN                                 (0)
  #define CH0_SC0_CR_CADB_BUF_3_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH0_SC0_CR_CADB_BUF_3_CA_DEF                                 (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_3_CA_HSH                                 (0x5812D060)

#define CH0_SC0_CR_CADB_BUF_4_REG                                      (0x0000D068)

  #define CH0_SC0_CR_CADB_BUF_4_CS_OFF                                 ( 0)
  #define CH0_SC0_CR_CADB_BUF_4_CS_WID                                 ( 4)
  #define CH0_SC0_CR_CADB_BUF_4_CS_MSK                                 (0x0000000F)
  #define CH0_SC0_CR_CADB_BUF_4_CS_MIN                                 (0)
  #define CH0_SC0_CR_CADB_BUF_4_CS_MAX                                 (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_BUF_4_CS_DEF                                 (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_4_CS_HSH                                 (0x4400D068)

  #define CH0_SC0_CR_CADB_BUF_4_CID_OFF                                ( 4)
  #define CH0_SC0_CR_CADB_BUF_4_CID_WID                                ( 3)
  #define CH0_SC0_CR_CADB_BUF_4_CID_MSK                                (0x00000070)
  #define CH0_SC0_CR_CADB_BUF_4_CID_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_4_CID_MAX                                (7) // 0x00000007
  #define CH0_SC0_CR_CADB_BUF_4_CID_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_4_CID_HSH                                (0x4304D068)

  #define CH0_SC0_CR_CADB_BUF_4_ODT_OFF                                ( 7)
  #define CH0_SC0_CR_CADB_BUF_4_ODT_WID                                ( 4)
  #define CH0_SC0_CR_CADB_BUF_4_ODT_MSK                                (0x00000780)
  #define CH0_SC0_CR_CADB_BUF_4_ODT_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_4_ODT_MAX                                (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_BUF_4_ODT_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_4_ODT_HSH                                (0x4407D068)

  #define CH0_SC0_CR_CADB_BUF_4_CKE_OFF                                (11)
  #define CH0_SC0_CR_CADB_BUF_4_CKE_WID                                ( 4)
  #define CH0_SC0_CR_CADB_BUF_4_CKE_MSK                                (0x00007800)
  #define CH0_SC0_CR_CADB_BUF_4_CKE_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_4_CKE_MAX                                (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_BUF_4_CKE_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_4_CKE_HSH                                (0x440BD068)

  #define CH0_SC0_CR_CADB_BUF_4_USE_HALF_CA_OFF                        (15)
  #define CH0_SC0_CR_CADB_BUF_4_USE_HALF_CA_WID                        ( 1)
  #define CH0_SC0_CR_CADB_BUF_4_USE_HALF_CA_MSK                        (0x00008000)
  #define CH0_SC0_CR_CADB_BUF_4_USE_HALF_CA_MIN                        (0)
  #define CH0_SC0_CR_CADB_BUF_4_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH0_SC0_CR_CADB_BUF_4_USE_HALF_CA_DEF                        (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_4_USE_HALF_CA_HSH                        (0x410FD068)

  #define CH0_SC0_CR_CADB_BUF_4_VAL_OFF                                (16)
  #define CH0_SC0_CR_CADB_BUF_4_VAL_WID                                ( 1)
  #define CH0_SC0_CR_CADB_BUF_4_VAL_MSK                                (0x00010000)
  #define CH0_SC0_CR_CADB_BUF_4_VAL_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_4_VAL_MAX                                (1) // 0x00000001
  #define CH0_SC0_CR_CADB_BUF_4_VAL_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_4_VAL_HSH                                (0x4110D068)

  #define CH0_SC0_CR_CADB_BUF_4_PAR_OFF                                (17)
  #define CH0_SC0_CR_CADB_BUF_4_PAR_WID                                ( 1)
  #define CH0_SC0_CR_CADB_BUF_4_PAR_MSK                                (0x00020000)
  #define CH0_SC0_CR_CADB_BUF_4_PAR_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_4_PAR_MAX                                (1) // 0x00000001
  #define CH0_SC0_CR_CADB_BUF_4_PAR_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_4_PAR_HSH                                (0x4111D068)

  #define CH0_SC0_CR_CADB_BUF_4_CA_OFF                                 (18)
  #define CH0_SC0_CR_CADB_BUF_4_CA_WID                                 (24)
  #define CH0_SC0_CR_CADB_BUF_4_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH0_SC0_CR_CADB_BUF_4_CA_MIN                                 (0)
  #define CH0_SC0_CR_CADB_BUF_4_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH0_SC0_CR_CADB_BUF_4_CA_DEF                                 (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_4_CA_HSH                                 (0x5812D068)

#define CH0_SC0_CR_CADB_BUF_5_REG                                      (0x0000D070)

  #define CH0_SC0_CR_CADB_BUF_5_CS_OFF                                 ( 0)
  #define CH0_SC0_CR_CADB_BUF_5_CS_WID                                 ( 4)
  #define CH0_SC0_CR_CADB_BUF_5_CS_MSK                                 (0x0000000F)
  #define CH0_SC0_CR_CADB_BUF_5_CS_MIN                                 (0)
  #define CH0_SC0_CR_CADB_BUF_5_CS_MAX                                 (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_BUF_5_CS_DEF                                 (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_5_CS_HSH                                 (0x4400D070)

  #define CH0_SC0_CR_CADB_BUF_5_CID_OFF                                ( 4)
  #define CH0_SC0_CR_CADB_BUF_5_CID_WID                                ( 3)
  #define CH0_SC0_CR_CADB_BUF_5_CID_MSK                                (0x00000070)
  #define CH0_SC0_CR_CADB_BUF_5_CID_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_5_CID_MAX                                (7) // 0x00000007
  #define CH0_SC0_CR_CADB_BUF_5_CID_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_5_CID_HSH                                (0x4304D070)

  #define CH0_SC0_CR_CADB_BUF_5_ODT_OFF                                ( 7)
  #define CH0_SC0_CR_CADB_BUF_5_ODT_WID                                ( 4)
  #define CH0_SC0_CR_CADB_BUF_5_ODT_MSK                                (0x00000780)
  #define CH0_SC0_CR_CADB_BUF_5_ODT_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_5_ODT_MAX                                (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_BUF_5_ODT_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_5_ODT_HSH                                (0x4407D070)

  #define CH0_SC0_CR_CADB_BUF_5_CKE_OFF                                (11)
  #define CH0_SC0_CR_CADB_BUF_5_CKE_WID                                ( 4)
  #define CH0_SC0_CR_CADB_BUF_5_CKE_MSK                                (0x00007800)
  #define CH0_SC0_CR_CADB_BUF_5_CKE_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_5_CKE_MAX                                (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_BUF_5_CKE_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_5_CKE_HSH                                (0x440BD070)

  #define CH0_SC0_CR_CADB_BUF_5_USE_HALF_CA_OFF                        (15)
  #define CH0_SC0_CR_CADB_BUF_5_USE_HALF_CA_WID                        ( 1)
  #define CH0_SC0_CR_CADB_BUF_5_USE_HALF_CA_MSK                        (0x00008000)
  #define CH0_SC0_CR_CADB_BUF_5_USE_HALF_CA_MIN                        (0)
  #define CH0_SC0_CR_CADB_BUF_5_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH0_SC0_CR_CADB_BUF_5_USE_HALF_CA_DEF                        (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_5_USE_HALF_CA_HSH                        (0x410FD070)

  #define CH0_SC0_CR_CADB_BUF_5_VAL_OFF                                (16)
  #define CH0_SC0_CR_CADB_BUF_5_VAL_WID                                ( 1)
  #define CH0_SC0_CR_CADB_BUF_5_VAL_MSK                                (0x00010000)
  #define CH0_SC0_CR_CADB_BUF_5_VAL_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_5_VAL_MAX                                (1) // 0x00000001
  #define CH0_SC0_CR_CADB_BUF_5_VAL_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_5_VAL_HSH                                (0x4110D070)

  #define CH0_SC0_CR_CADB_BUF_5_PAR_OFF                                (17)
  #define CH0_SC0_CR_CADB_BUF_5_PAR_WID                                ( 1)
  #define CH0_SC0_CR_CADB_BUF_5_PAR_MSK                                (0x00020000)
  #define CH0_SC0_CR_CADB_BUF_5_PAR_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_5_PAR_MAX                                (1) // 0x00000001
  #define CH0_SC0_CR_CADB_BUF_5_PAR_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_5_PAR_HSH                                (0x4111D070)

  #define CH0_SC0_CR_CADB_BUF_5_CA_OFF                                 (18)
  #define CH0_SC0_CR_CADB_BUF_5_CA_WID                                 (24)
  #define CH0_SC0_CR_CADB_BUF_5_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH0_SC0_CR_CADB_BUF_5_CA_MIN                                 (0)
  #define CH0_SC0_CR_CADB_BUF_5_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH0_SC0_CR_CADB_BUF_5_CA_DEF                                 (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_5_CA_HSH                                 (0x5812D070)

#define CH0_SC0_CR_CADB_BUF_6_REG                                      (0x0000D078)

  #define CH0_SC0_CR_CADB_BUF_6_CS_OFF                                 ( 0)
  #define CH0_SC0_CR_CADB_BUF_6_CS_WID                                 ( 4)
  #define CH0_SC0_CR_CADB_BUF_6_CS_MSK                                 (0x0000000F)
  #define CH0_SC0_CR_CADB_BUF_6_CS_MIN                                 (0)
  #define CH0_SC0_CR_CADB_BUF_6_CS_MAX                                 (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_BUF_6_CS_DEF                                 (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_6_CS_HSH                                 (0x4400D078)

  #define CH0_SC0_CR_CADB_BUF_6_CID_OFF                                ( 4)
  #define CH0_SC0_CR_CADB_BUF_6_CID_WID                                ( 3)
  #define CH0_SC0_CR_CADB_BUF_6_CID_MSK                                (0x00000070)
  #define CH0_SC0_CR_CADB_BUF_6_CID_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_6_CID_MAX                                (7) // 0x00000007
  #define CH0_SC0_CR_CADB_BUF_6_CID_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_6_CID_HSH                                (0x4304D078)

  #define CH0_SC0_CR_CADB_BUF_6_ODT_OFF                                ( 7)
  #define CH0_SC0_CR_CADB_BUF_6_ODT_WID                                ( 4)
  #define CH0_SC0_CR_CADB_BUF_6_ODT_MSK                                (0x00000780)
  #define CH0_SC0_CR_CADB_BUF_6_ODT_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_6_ODT_MAX                                (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_BUF_6_ODT_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_6_ODT_HSH                                (0x4407D078)

  #define CH0_SC0_CR_CADB_BUF_6_CKE_OFF                                (11)
  #define CH0_SC0_CR_CADB_BUF_6_CKE_WID                                ( 4)
  #define CH0_SC0_CR_CADB_BUF_6_CKE_MSK                                (0x00007800)
  #define CH0_SC0_CR_CADB_BUF_6_CKE_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_6_CKE_MAX                                (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_BUF_6_CKE_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_6_CKE_HSH                                (0x440BD078)

  #define CH0_SC0_CR_CADB_BUF_6_USE_HALF_CA_OFF                        (15)
  #define CH0_SC0_CR_CADB_BUF_6_USE_HALF_CA_WID                        ( 1)
  #define CH0_SC0_CR_CADB_BUF_6_USE_HALF_CA_MSK                        (0x00008000)
  #define CH0_SC0_CR_CADB_BUF_6_USE_HALF_CA_MIN                        (0)
  #define CH0_SC0_CR_CADB_BUF_6_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH0_SC0_CR_CADB_BUF_6_USE_HALF_CA_DEF                        (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_6_USE_HALF_CA_HSH                        (0x410FD078)

  #define CH0_SC0_CR_CADB_BUF_6_VAL_OFF                                (16)
  #define CH0_SC0_CR_CADB_BUF_6_VAL_WID                                ( 1)
  #define CH0_SC0_CR_CADB_BUF_6_VAL_MSK                                (0x00010000)
  #define CH0_SC0_CR_CADB_BUF_6_VAL_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_6_VAL_MAX                                (1) // 0x00000001
  #define CH0_SC0_CR_CADB_BUF_6_VAL_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_6_VAL_HSH                                (0x4110D078)

  #define CH0_SC0_CR_CADB_BUF_6_PAR_OFF                                (17)
  #define CH0_SC0_CR_CADB_BUF_6_PAR_WID                                ( 1)
  #define CH0_SC0_CR_CADB_BUF_6_PAR_MSK                                (0x00020000)
  #define CH0_SC0_CR_CADB_BUF_6_PAR_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_6_PAR_MAX                                (1) // 0x00000001
  #define CH0_SC0_CR_CADB_BUF_6_PAR_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_6_PAR_HSH                                (0x4111D078)

  #define CH0_SC0_CR_CADB_BUF_6_CA_OFF                                 (18)
  #define CH0_SC0_CR_CADB_BUF_6_CA_WID                                 (24)
  #define CH0_SC0_CR_CADB_BUF_6_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH0_SC0_CR_CADB_BUF_6_CA_MIN                                 (0)
  #define CH0_SC0_CR_CADB_BUF_6_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH0_SC0_CR_CADB_BUF_6_CA_DEF                                 (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_6_CA_HSH                                 (0x5812D078)

#define CH0_SC0_CR_CADB_BUF_7_REG                                      (0x0000D080)

  #define CH0_SC0_CR_CADB_BUF_7_CS_OFF                                 ( 0)
  #define CH0_SC0_CR_CADB_BUF_7_CS_WID                                 ( 4)
  #define CH0_SC0_CR_CADB_BUF_7_CS_MSK                                 (0x0000000F)
  #define CH0_SC0_CR_CADB_BUF_7_CS_MIN                                 (0)
  #define CH0_SC0_CR_CADB_BUF_7_CS_MAX                                 (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_BUF_7_CS_DEF                                 (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_7_CS_HSH                                 (0x4400D080)

  #define CH0_SC0_CR_CADB_BUF_7_CID_OFF                                ( 4)
  #define CH0_SC0_CR_CADB_BUF_7_CID_WID                                ( 3)
  #define CH0_SC0_CR_CADB_BUF_7_CID_MSK                                (0x00000070)
  #define CH0_SC0_CR_CADB_BUF_7_CID_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_7_CID_MAX                                (7) // 0x00000007
  #define CH0_SC0_CR_CADB_BUF_7_CID_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_7_CID_HSH                                (0x4304D080)

  #define CH0_SC0_CR_CADB_BUF_7_ODT_OFF                                ( 7)
  #define CH0_SC0_CR_CADB_BUF_7_ODT_WID                                ( 4)
  #define CH0_SC0_CR_CADB_BUF_7_ODT_MSK                                (0x00000780)
  #define CH0_SC0_CR_CADB_BUF_7_ODT_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_7_ODT_MAX                                (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_BUF_7_ODT_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_7_ODT_HSH                                (0x4407D080)

  #define CH0_SC0_CR_CADB_BUF_7_CKE_OFF                                (11)
  #define CH0_SC0_CR_CADB_BUF_7_CKE_WID                                ( 4)
  #define CH0_SC0_CR_CADB_BUF_7_CKE_MSK                                (0x00007800)
  #define CH0_SC0_CR_CADB_BUF_7_CKE_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_7_CKE_MAX                                (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_BUF_7_CKE_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_7_CKE_HSH                                (0x440BD080)

  #define CH0_SC0_CR_CADB_BUF_7_USE_HALF_CA_OFF                        (15)
  #define CH0_SC0_CR_CADB_BUF_7_USE_HALF_CA_WID                        ( 1)
  #define CH0_SC0_CR_CADB_BUF_7_USE_HALF_CA_MSK                        (0x00008000)
  #define CH0_SC0_CR_CADB_BUF_7_USE_HALF_CA_MIN                        (0)
  #define CH0_SC0_CR_CADB_BUF_7_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH0_SC0_CR_CADB_BUF_7_USE_HALF_CA_DEF                        (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_7_USE_HALF_CA_HSH                        (0x410FD080)

  #define CH0_SC0_CR_CADB_BUF_7_VAL_OFF                                (16)
  #define CH0_SC0_CR_CADB_BUF_7_VAL_WID                                ( 1)
  #define CH0_SC0_CR_CADB_BUF_7_VAL_MSK                                (0x00010000)
  #define CH0_SC0_CR_CADB_BUF_7_VAL_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_7_VAL_MAX                                (1) // 0x00000001
  #define CH0_SC0_CR_CADB_BUF_7_VAL_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_7_VAL_HSH                                (0x4110D080)

  #define CH0_SC0_CR_CADB_BUF_7_PAR_OFF                                (17)
  #define CH0_SC0_CR_CADB_BUF_7_PAR_WID                                ( 1)
  #define CH0_SC0_CR_CADB_BUF_7_PAR_MSK                                (0x00020000)
  #define CH0_SC0_CR_CADB_BUF_7_PAR_MIN                                (0)
  #define CH0_SC0_CR_CADB_BUF_7_PAR_MAX                                (1) // 0x00000001
  #define CH0_SC0_CR_CADB_BUF_7_PAR_DEF                                (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_7_PAR_HSH                                (0x4111D080)

  #define CH0_SC0_CR_CADB_BUF_7_CA_OFF                                 (18)
  #define CH0_SC0_CR_CADB_BUF_7_CA_WID                                 (24)
  #define CH0_SC0_CR_CADB_BUF_7_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH0_SC0_CR_CADB_BUF_7_CA_MIN                                 (0)
  #define CH0_SC0_CR_CADB_BUF_7_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH0_SC0_CR_CADB_BUF_7_CA_DEF                                 (0x00000000)
  #define CH0_SC0_CR_CADB_BUF_7_CA_HSH                                 (0x5812D080)

#define CH0_SC0_CR_CADB_AO_MRSCFG_REG                                  (0x0000D088)

  #define CH0_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_OFF                  ( 0)
  #define CH0_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_WID                  ( 1)
  #define CH0_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_MSK                  (0x00000001)
  #define CH0_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_MIN                  (0)
  #define CH0_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_MAX                  (1) // 0x00000001
  #define CH0_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_DEF                  (0x00000000)
  #define CH0_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_HSH                  (0x0100D088)

  #define CH0_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_OFF                        ( 1)
  #define CH0_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_WID                        ( 4)
  #define CH0_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_MSK                        (0x0000001E)
  #define CH0_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_MIN                        (0)
  #define CH0_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_MAX                        (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_DEF                        (0x00000000)
  #define CH0_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_HSH                        (0x0401D088)

  #define CH0_SC0_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_OFF                 ( 8)
  #define CH0_SC0_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_WID                 (16)
  #define CH0_SC0_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_MSK                 (0x00FFFF00)
  #define CH0_SC0_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_MIN                 (0)
  #define CH0_SC0_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_MAX                 (65535) // 0x0000FFFF
  #define CH0_SC0_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_DEF                 (0x00000000)
  #define CH0_SC0_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_HSH                 (0x1008D088)

#define CH0_SC0_CR_CADB_SELCFG_REG                                     (0x0000D090)

  #define CH0_SC0_CR_CADB_SELCFG_WR_SELECT_ENABLE_OFF                  ( 0)
  #define CH0_SC0_CR_CADB_SELCFG_WR_SELECT_ENABLE_WID                  ( 3)
  #define CH0_SC0_CR_CADB_SELCFG_WR_SELECT_ENABLE_MSK                  (0x00000007)
  #define CH0_SC0_CR_CADB_SELCFG_WR_SELECT_ENABLE_MIN                  (0)
  #define CH0_SC0_CR_CADB_SELCFG_WR_SELECT_ENABLE_MAX                  (7) // 0x00000007
  #define CH0_SC0_CR_CADB_SELCFG_WR_SELECT_ENABLE_DEF                  (0x00000000)
  #define CH0_SC0_CR_CADB_SELCFG_WR_SELECT_ENABLE_HSH                  (0x0300D090)

  #define CH0_SC0_CR_CADB_SELCFG_RD_SELECT_ENABLE_OFF                  ( 8)
  #define CH0_SC0_CR_CADB_SELCFG_RD_SELECT_ENABLE_WID                  ( 3)
  #define CH0_SC0_CR_CADB_SELCFG_RD_SELECT_ENABLE_MSK                  (0x00000700)
  #define CH0_SC0_CR_CADB_SELCFG_RD_SELECT_ENABLE_MIN                  (0)
  #define CH0_SC0_CR_CADB_SELCFG_RD_SELECT_ENABLE_MAX                  (7) // 0x00000007
  #define CH0_SC0_CR_CADB_SELCFG_RD_SELECT_ENABLE_DEF                  (0x00000000)
  #define CH0_SC0_CR_CADB_SELCFG_RD_SELECT_ENABLE_HSH                  (0x0308D090)

  #define CH0_SC0_CR_CADB_SELCFG_ACT_SELECT_ENABLE_OFF                 (16)
  #define CH0_SC0_CR_CADB_SELCFG_ACT_SELECT_ENABLE_WID                 ( 3)
  #define CH0_SC0_CR_CADB_SELCFG_ACT_SELECT_ENABLE_MSK                 (0x00070000)
  #define CH0_SC0_CR_CADB_SELCFG_ACT_SELECT_ENABLE_MIN                 (0)
  #define CH0_SC0_CR_CADB_SELCFG_ACT_SELECT_ENABLE_MAX                 (7) // 0x00000007
  #define CH0_SC0_CR_CADB_SELCFG_ACT_SELECT_ENABLE_DEF                 (0x00000000)
  #define CH0_SC0_CR_CADB_SELCFG_ACT_SELECT_ENABLE_HSH                 (0x0310D090)

  #define CH0_SC0_CR_CADB_SELCFG_PRE_SELECT_ENABLE_OFF                 (24)
  #define CH0_SC0_CR_CADB_SELCFG_PRE_SELECT_ENABLE_WID                 ( 3)
  #define CH0_SC0_CR_CADB_SELCFG_PRE_SELECT_ENABLE_MSK                 (0x07000000)
  #define CH0_SC0_CR_CADB_SELCFG_PRE_SELECT_ENABLE_MIN                 (0)
  #define CH0_SC0_CR_CADB_SELCFG_PRE_SELECT_ENABLE_MAX                 (7) // 0x00000007
  #define CH0_SC0_CR_CADB_SELCFG_PRE_SELECT_ENABLE_DEF                 (0x00000000)
  #define CH0_SC0_CR_CADB_SELCFG_PRE_SELECT_ENABLE_HSH                 (0x0318D090)

  #define CH0_SC0_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_OFF               (28)
  #define CH0_SC0_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_WID               ( 1)
  #define CH0_SC0_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_MSK               (0x10000000)
  #define CH0_SC0_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_MIN               (0)
  #define CH0_SC0_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_MAX               (1) // 0x00000001
  #define CH0_SC0_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_DEF               (0x00000001)
  #define CH0_SC0_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_HSH               (0x011CD090)

#define CH0_SC0_CR_CADB_MRSCFG_REG                                     (0x0000D098)

  #define CH0_SC0_CR_CADB_MRSCFG_CS_CLOCKS_OFF                         ( 0)
  #define CH0_SC0_CR_CADB_MRSCFG_CS_CLOCKS_WID                         ( 3)
  #define CH0_SC0_CR_CADB_MRSCFG_CS_CLOCKS_MSK                         (0x00000007)
  #define CH0_SC0_CR_CADB_MRSCFG_CS_CLOCKS_MIN                         (0)
  #define CH0_SC0_CR_CADB_MRSCFG_CS_CLOCKS_MAX                         (7) // 0x00000007
  #define CH0_SC0_CR_CADB_MRSCFG_CS_CLOCKS_DEF                         (0x00000000)
  #define CH0_SC0_CR_CADB_MRSCFG_CS_CLOCKS_HSH                         (0x4300D098)

  #define CH0_SC0_CR_CADB_MRSCFG_DSEL_CLOCKS_OFF                       ( 3)
  #define CH0_SC0_CR_CADB_MRSCFG_DSEL_CLOCKS_WID                       ( 4)
  #define CH0_SC0_CR_CADB_MRSCFG_DSEL_CLOCKS_MSK                       (0x00000078)
  #define CH0_SC0_CR_CADB_MRSCFG_DSEL_CLOCKS_MIN                       (0)
  #define CH0_SC0_CR_CADB_MRSCFG_DSEL_CLOCKS_MAX                       (15) // 0x0000000F
  #define CH0_SC0_CR_CADB_MRSCFG_DSEL_CLOCKS_DEF                       (0x00000000)
  #define CH0_SC0_CR_CADB_MRSCFG_DSEL_CLOCKS_HSH                       (0x4403D098)

  #define CH0_SC0_CR_CADB_MRSCFG_SETUP_CLOCKS_OFF                      ( 8)
  #define CH0_SC0_CR_CADB_MRSCFG_SETUP_CLOCKS_WID                      ( 3)
  #define CH0_SC0_CR_CADB_MRSCFG_SETUP_CLOCKS_MSK                      (0x00000700)
  #define CH0_SC0_CR_CADB_MRSCFG_SETUP_CLOCKS_MIN                      (0)
  #define CH0_SC0_CR_CADB_MRSCFG_SETUP_CLOCKS_MAX                      (7) // 0x00000007
  #define CH0_SC0_CR_CADB_MRSCFG_SETUP_CLOCKS_DEF                      (0x00000000)
  #define CH0_SC0_CR_CADB_MRSCFG_SETUP_CLOCKS_HSH                      (0x4308D098)

  #define CH0_SC0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_OFF                (11)
  #define CH0_SC0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_WID                ( 1)
  #define CH0_SC0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_MSK                (0x00000800)
  #define CH0_SC0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_MIN                (0)
  #define CH0_SC0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_MAX                (1) // 0x00000001
  #define CH0_SC0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_DEF                (0x00000000)
  #define CH0_SC0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_HSH                (0x410BD098)

  #define CH0_SC0_CR_CADB_MRSCFG_MRS_START_PTR_OFF                     (12)
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_START_PTR_WID                     ( 3)
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_START_PTR_MSK                     (0x00007000)
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_START_PTR_MIN                     (0)
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_START_PTR_MAX                     (7) // 0x00000007
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_START_PTR_DEF                     (0x00000000)
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_START_PTR_HSH                     (0x430CD098)

  #define CH0_SC0_CR_CADB_MRSCFG_MRS_END_PTR_OFF                       (16)
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_END_PTR_WID                       ( 3)
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_END_PTR_MSK                       (0x00070000)
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_END_PTR_MIN                       (0)
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_END_PTR_MAX                       (7) // 0x00000007
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_END_PTR_DEF                       (0x00000000)
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_END_PTR_HSH                       (0x4310D098)

  #define CH0_SC0_CR_CADB_MRSCFG_MRS_GOTO_PTR_OFF                      (19)
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_GOTO_PTR_WID                      ( 3)
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_GOTO_PTR_MSK                      (0x00380000)
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_GOTO_PTR_MIN                      (0)
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_GOTO_PTR_MAX                      (7) // 0x00000007
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_GOTO_PTR_DEF                      (0x00000000)
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_GOTO_PTR_HSH                      (0x4313D098)

  #define CH0_SC0_CR_CADB_MRSCFG_MRS_CS_MODE_OFF                       (22)
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_CS_MODE_WID                       ( 2)
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_CS_MODE_MSK                       (0x00C00000)
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_CS_MODE_MIN                       (0)
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_CS_MODE_MAX                       (3) // 0x00000003
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_CS_MODE_DEF                       (0x00000000)
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_CS_MODE_HSH                       (0x4216D098)

  #define CH0_SC0_CR_CADB_MRSCFG_MRS_DELAY_CNT_OFF                     (24)
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_DELAY_CNT_WID                     (16)
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_DELAY_CNT_MSK                     (0x000000FFFF000000ULL)
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_DELAY_CNT_MIN                     (0)
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_DELAY_CNT_MAX                     (65535) // 0x0000FFFF
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_DELAY_CNT_DEF                     (0x00000000)
  #define CH0_SC0_CR_CADB_MRSCFG_MRS_DELAY_CNT_HSH                     (0x5018D098)

#define CH0_SC1_CR_CADB_ACCESS_CONTROL_POLICY_REG                      (0x0000D100)

  #define CH0_SC1_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_OFF     ( 0)
  #define CH0_SC1_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_WID     (64)
  #define CH0_SC1_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_MSK     (0xFFFFFFFFFFFFFFFFULL)
  #define CH0_SC1_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_MIN     (0)
  #define CH0_SC1_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_MAX     (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define CH0_SC1_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_DEF     (0x40001000208)
  #define CH0_SC1_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_HSH     (0x4000D100)

#define CH0_SC1_CR_CADB_ACCESS_READ_POLICY_REG                         (0x0000D108)

  #define CH0_SC1_CR_CADB_ACCESS_READ_POLICY_Read_Policy_OFF           ( 0)
  #define CH0_SC1_CR_CADB_ACCESS_READ_POLICY_Read_Policy_WID           (64)
  #define CH0_SC1_CR_CADB_ACCESS_READ_POLICY_Read_Policy_MSK           (0xFFFFFFFFFFFFFFFFULL)
  #define CH0_SC1_CR_CADB_ACCESS_READ_POLICY_Read_Policy_MIN           (0)
  #define CH0_SC1_CR_CADB_ACCESS_READ_POLICY_Read_Policy_MAX           (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define CH0_SC1_CR_CADB_ACCESS_READ_POLICY_Read_Policy_DEF           (0xFFFFFFFFFFFFFFFF)
  #define CH0_SC1_CR_CADB_ACCESS_READ_POLICY_Read_Policy_HSH           (0x4000D108)

#define CH0_SC1_CR_CADB_ACCESS_WRITE_POLICY_REG                        (0x0000D110)

  #define CH0_SC1_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_OFF         ( 0)
  #define CH0_SC1_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_WID         (64)
  #define CH0_SC1_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_MSK         (0xFFFFFFFFFFFFFFFFULL)
  #define CH0_SC1_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_MIN         (0)
  #define CH0_SC1_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_MAX         (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define CH0_SC1_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_DEF         (0x4000100021A)
  #define CH0_SC1_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_HSH         (0x4000D110)

#define CH0_SC1_CR_CADB_CTL_REG                                        (0x0000D120)

  #define CH0_SC1_CR_CADB_CTL_START_TEST_OFF                           ( 0)
  #define CH0_SC1_CR_CADB_CTL_START_TEST_WID                           ( 1)
  #define CH0_SC1_CR_CADB_CTL_START_TEST_MSK                           (0x00000001)
  #define CH0_SC1_CR_CADB_CTL_START_TEST_MIN                           (0)
  #define CH0_SC1_CR_CADB_CTL_START_TEST_MAX                           (1) // 0x00000001
  #define CH0_SC1_CR_CADB_CTL_START_TEST_DEF                           (0x00000000)
  #define CH0_SC1_CR_CADB_CTL_START_TEST_HSH                           (0x0100D120)

  #define CH0_SC1_CR_CADB_CTL_STOP_TEST_OFF                            ( 1)
  #define CH0_SC1_CR_CADB_CTL_STOP_TEST_WID                            ( 1)
  #define CH0_SC1_CR_CADB_CTL_STOP_TEST_MSK                            (0x00000002)
  #define CH0_SC1_CR_CADB_CTL_STOP_TEST_MIN                            (0)
  #define CH0_SC1_CR_CADB_CTL_STOP_TEST_MAX                            (1) // 0x00000001
  #define CH0_SC1_CR_CADB_CTL_STOP_TEST_DEF                            (0x00000000)
  #define CH0_SC1_CR_CADB_CTL_STOP_TEST_HSH                            (0x0101D120)

#define CH0_SC1_CR_CADB_CFG_REG                                        (0x0000D124)

  #define CH0_SC1_CR_CADB_CFG_CMD_DESELECT_START_OFF                   ( 0)
  #define CH0_SC1_CR_CADB_CFG_CMD_DESELECT_START_WID                   ( 4)
  #define CH0_SC1_CR_CADB_CFG_CMD_DESELECT_START_MSK                   (0x0000000F)
  #define CH0_SC1_CR_CADB_CFG_CMD_DESELECT_START_MIN                   (0)
  #define CH0_SC1_CR_CADB_CFG_CMD_DESELECT_START_MAX                   (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_CFG_CMD_DESELECT_START_DEF                   (0x00000000)
  #define CH0_SC1_CR_CADB_CFG_CMD_DESELECT_START_HSH                   (0x0400D124)

  #define CH0_SC1_CR_CADB_CFG_CMD_DESELECT_STOP_OFF                    ( 4)
  #define CH0_SC1_CR_CADB_CFG_CMD_DESELECT_STOP_WID                    ( 4)
  #define CH0_SC1_CR_CADB_CFG_CMD_DESELECT_STOP_MSK                    (0x000000F0)
  #define CH0_SC1_CR_CADB_CFG_CMD_DESELECT_STOP_MIN                    (0)
  #define CH0_SC1_CR_CADB_CFG_CMD_DESELECT_STOP_MAX                    (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_CFG_CMD_DESELECT_STOP_DEF                    (0x00000000)
  #define CH0_SC1_CR_CADB_CFG_CMD_DESELECT_STOP_HSH                    (0x0404D124)

  #define CH0_SC1_CR_CADB_CFG_LANE_DESELECT_EN_OFF                     ( 8)
  #define CH0_SC1_CR_CADB_CFG_LANE_DESELECT_EN_WID                     ( 3)
  #define CH0_SC1_CR_CADB_CFG_LANE_DESELECT_EN_MSK                     (0x00000700)
  #define CH0_SC1_CR_CADB_CFG_LANE_DESELECT_EN_MIN                     (0)
  #define CH0_SC1_CR_CADB_CFG_LANE_DESELECT_EN_MAX                     (7) // 0x00000007
  #define CH0_SC1_CR_CADB_CFG_LANE_DESELECT_EN_DEF                     (0x00000000)
  #define CH0_SC1_CR_CADB_CFG_LANE_DESELECT_EN_HSH                     (0x0308D124)

  #define CH0_SC1_CR_CADB_CFG_INITIAL_DSEL_EN_OFF                      (11)
  #define CH0_SC1_CR_CADB_CFG_INITIAL_DSEL_EN_WID                      ( 1)
  #define CH0_SC1_CR_CADB_CFG_INITIAL_DSEL_EN_MSK                      (0x00000800)
  #define CH0_SC1_CR_CADB_CFG_INITIAL_DSEL_EN_MIN                      (0)
  #define CH0_SC1_CR_CADB_CFG_INITIAL_DSEL_EN_MAX                      (1) // 0x00000001
  #define CH0_SC1_CR_CADB_CFG_INITIAL_DSEL_EN_DEF                      (0x00000001)
  #define CH0_SC1_CR_CADB_CFG_INITIAL_DSEL_EN_HSH                      (0x010BD124)

  #define CH0_SC1_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_OFF                 (12)
  #define CH0_SC1_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_WID                 ( 1)
  #define CH0_SC1_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_MSK                 (0x00001000)
  #define CH0_SC1_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_MIN                 (0)
  #define CH0_SC1_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_MAX                 (1) // 0x00000001
  #define CH0_SC1_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_DEF                 (0x00000001)
  #define CH0_SC1_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_HSH                 (0x010CD124)

  #define CH0_SC1_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_OFF              (13)
  #define CH0_SC1_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_WID              ( 3)
  #define CH0_SC1_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_MSK              (0x0000E000)
  #define CH0_SC1_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_MIN              (0)
  #define CH0_SC1_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_MAX              (7) // 0x00000007
  #define CH0_SC1_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_DEF              (0x00000000)
  #define CH0_SC1_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_HSH              (0x030DD124)

  #define CH0_SC1_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_OFF               (16)
  #define CH0_SC1_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_WID               ( 3)
  #define CH0_SC1_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_MSK               (0x00070000)
  #define CH0_SC1_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_MIN               (0)
  #define CH0_SC1_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_MAX               (7) // 0x00000007
  #define CH0_SC1_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_DEF               (0x00000000)
  #define CH0_SC1_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_HSH               (0x0310D124)

  #define CH0_SC1_CR_CADB_CFG_CADB_TO_CPGC_BIND_OFF                    (24)
  #define CH0_SC1_CR_CADB_CFG_CADB_TO_CPGC_BIND_WID                    ( 1)
  #define CH0_SC1_CR_CADB_CFG_CADB_TO_CPGC_BIND_MSK                    (0x01000000)
  #define CH0_SC1_CR_CADB_CFG_CADB_TO_CPGC_BIND_MIN                    (0)
  #define CH0_SC1_CR_CADB_CFG_CADB_TO_CPGC_BIND_MAX                    (1) // 0x00000001
  #define CH0_SC1_CR_CADB_CFG_CADB_TO_CPGC_BIND_DEF                    (0x00000000)
  #define CH0_SC1_CR_CADB_CFG_CADB_TO_CPGC_BIND_HSH                    (0x0118D124)

  #define CH0_SC1_CR_CADB_CFG_GLOBAL_START_BIND_OFF                    (25)
  #define CH0_SC1_CR_CADB_CFG_GLOBAL_START_BIND_WID                    ( 1)
  #define CH0_SC1_CR_CADB_CFG_GLOBAL_START_BIND_MSK                    (0x02000000)
  #define CH0_SC1_CR_CADB_CFG_GLOBAL_START_BIND_MIN                    (0)
  #define CH0_SC1_CR_CADB_CFG_GLOBAL_START_BIND_MAX                    (1) // 0x00000001
  #define CH0_SC1_CR_CADB_CFG_GLOBAL_START_BIND_DEF                    (0x00000000)
  #define CH0_SC1_CR_CADB_CFG_GLOBAL_START_BIND_HSH                    (0x0119D124)

  #define CH0_SC1_CR_CADB_CFG_GLOBAL_STOP_BIND_OFF                     (26)
  #define CH0_SC1_CR_CADB_CFG_GLOBAL_STOP_BIND_WID                     ( 1)
  #define CH0_SC1_CR_CADB_CFG_GLOBAL_STOP_BIND_MSK                     (0x04000000)
  #define CH0_SC1_CR_CADB_CFG_GLOBAL_STOP_BIND_MIN                     (0)
  #define CH0_SC1_CR_CADB_CFG_GLOBAL_STOP_BIND_MAX                     (1) // 0x00000001
  #define CH0_SC1_CR_CADB_CFG_GLOBAL_STOP_BIND_DEF                     (0x00000000)
  #define CH0_SC1_CR_CADB_CFG_GLOBAL_STOP_BIND_HSH                     (0x011AD124)

  #define CH0_SC1_CR_CADB_CFG_CADB_MODE_OFF                            (29)
  #define CH0_SC1_CR_CADB_CFG_CADB_MODE_WID                            ( 3)
  #define CH0_SC1_CR_CADB_CFG_CADB_MODE_MSK                            (0xE0000000)
  #define CH0_SC1_CR_CADB_CFG_CADB_MODE_MIN                            (0)
  #define CH0_SC1_CR_CADB_CFG_CADB_MODE_MAX                            (7) // 0x00000007
  #define CH0_SC1_CR_CADB_CFG_CADB_MODE_DEF                            (0x00000000)
  #define CH0_SC1_CR_CADB_CFG_CADB_MODE_HSH                            (0x031DD124)

#define CH0_SC1_CR_CADB_DLY_REG                                        (0x0000D128)

  #define CH0_SC1_CR_CADB_DLY_START_DELAY_OFF                          ( 0)
  #define CH0_SC1_CR_CADB_DLY_START_DELAY_WID                          (10)
  #define CH0_SC1_CR_CADB_DLY_START_DELAY_MSK                          (0x000003FF)
  #define CH0_SC1_CR_CADB_DLY_START_DELAY_MIN                          (0)
  #define CH0_SC1_CR_CADB_DLY_START_DELAY_MAX                          (1023) // 0x000003FF
  #define CH0_SC1_CR_CADB_DLY_START_DELAY_DEF                          (0x00000000)
  #define CH0_SC1_CR_CADB_DLY_START_DELAY_HSH                          (0x0A00D128)

  #define CH0_SC1_CR_CADB_DLY_STOP_DELAY_OFF                           (16)
  #define CH0_SC1_CR_CADB_DLY_STOP_DELAY_WID                           (10)
  #define CH0_SC1_CR_CADB_DLY_STOP_DELAY_MSK                           (0x03FF0000)
  #define CH0_SC1_CR_CADB_DLY_STOP_DELAY_MIN                           (0)
  #define CH0_SC1_CR_CADB_DLY_STOP_DELAY_MAX                           (1023) // 0x000003FF
  #define CH0_SC1_CR_CADB_DLY_STOP_DELAY_DEF                           (0x00000000)
  #define CH0_SC1_CR_CADB_DLY_STOP_DELAY_HSH                           (0x0A10D128)

#define CH0_SC1_CR_CADB_STATUS_REG                                     (0x0000D12C)

  #define CH0_SC1_CR_CADB_STATUS_MRS_CURR_PTR_OFF                      (21)
  #define CH0_SC1_CR_CADB_STATUS_MRS_CURR_PTR_WID                      ( 3)
  #define CH0_SC1_CR_CADB_STATUS_MRS_CURR_PTR_MSK                      (0x00E00000)
  #define CH0_SC1_CR_CADB_STATUS_MRS_CURR_PTR_MIN                      (0)
  #define CH0_SC1_CR_CADB_STATUS_MRS_CURR_PTR_MAX                      (7) // 0x00000007
  #define CH0_SC1_CR_CADB_STATUS_MRS_CURR_PTR_DEF                      (0x00000000)
  #define CH0_SC1_CR_CADB_STATUS_MRS_CURR_PTR_HSH                      (0x0315D12C)

  #define CH0_SC1_CR_CADB_STATUS_TEST_ABORTED_OFF                      (24)
  #define CH0_SC1_CR_CADB_STATUS_TEST_ABORTED_WID                      ( 1)
  #define CH0_SC1_CR_CADB_STATUS_TEST_ABORTED_MSK                      (0x01000000)
  #define CH0_SC1_CR_CADB_STATUS_TEST_ABORTED_MIN                      (0)
  #define CH0_SC1_CR_CADB_STATUS_TEST_ABORTED_MAX                      (1) // 0x00000001
  #define CH0_SC1_CR_CADB_STATUS_TEST_ABORTED_DEF                      (0x00000000)
  #define CH0_SC1_CR_CADB_STATUS_TEST_ABORTED_HSH                      (0x0118D12C)

  #define CH0_SC1_CR_CADB_STATUS_ALGO_DONE_OFF                         (28)
  #define CH0_SC1_CR_CADB_STATUS_ALGO_DONE_WID                         ( 1)
  #define CH0_SC1_CR_CADB_STATUS_ALGO_DONE_MSK                         (0x10000000)
  #define CH0_SC1_CR_CADB_STATUS_ALGO_DONE_MIN                         (0)
  #define CH0_SC1_CR_CADB_STATUS_ALGO_DONE_MAX                         (1) // 0x00000001
  #define CH0_SC1_CR_CADB_STATUS_ALGO_DONE_DEF                         (0x00000000)
  #define CH0_SC1_CR_CADB_STATUS_ALGO_DONE_HSH                         (0x011CD12C)

  #define CH0_SC1_CR_CADB_STATUS_START_TEST_DELAY_BUSY_OFF             (29)
  #define CH0_SC1_CR_CADB_STATUS_START_TEST_DELAY_BUSY_WID             ( 1)
  #define CH0_SC1_CR_CADB_STATUS_START_TEST_DELAY_BUSY_MSK             (0x20000000)
  #define CH0_SC1_CR_CADB_STATUS_START_TEST_DELAY_BUSY_MIN             (0)
  #define CH0_SC1_CR_CADB_STATUS_START_TEST_DELAY_BUSY_MAX             (1) // 0x00000001
  #define CH0_SC1_CR_CADB_STATUS_START_TEST_DELAY_BUSY_DEF             (0x00000000)
  #define CH0_SC1_CR_CADB_STATUS_START_TEST_DELAY_BUSY_HSH             (0x011DD12C)

  #define CH0_SC1_CR_CADB_STATUS_TEST_BUSY_OFF                         (30)
  #define CH0_SC1_CR_CADB_STATUS_TEST_BUSY_WID                         ( 1)
  #define CH0_SC1_CR_CADB_STATUS_TEST_BUSY_MSK                         (0x40000000)
  #define CH0_SC1_CR_CADB_STATUS_TEST_BUSY_MIN                         (0)
  #define CH0_SC1_CR_CADB_STATUS_TEST_BUSY_MAX                         (1) // 0x00000001
  #define CH0_SC1_CR_CADB_STATUS_TEST_BUSY_DEF                         (0x00000000)
  #define CH0_SC1_CR_CADB_STATUS_TEST_BUSY_HSH                         (0x011ED12C)

  #define CH0_SC1_CR_CADB_STATUS_TEST_DONE_OFF                         (31)
  #define CH0_SC1_CR_CADB_STATUS_TEST_DONE_WID                         ( 1)
  #define CH0_SC1_CR_CADB_STATUS_TEST_DONE_MSK                         (0x80000000)
  #define CH0_SC1_CR_CADB_STATUS_TEST_DONE_MIN                         (0)
  #define CH0_SC1_CR_CADB_STATUS_TEST_DONE_MAX                         (1) // 0x00000001
  #define CH0_SC1_CR_CADB_STATUS_TEST_DONE_DEF                         (0x00000000)
  #define CH0_SC1_CR_CADB_STATUS_TEST_DONE_HSH                         (0x011FD12C)

#define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_REG                          (0x0000D130)

  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_OFF            ( 0)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_WID            ( 2)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_MSK            (0x00000003)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_MIN            (0)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_MAX            (3) // 0x00000003
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_DEF            (0x00000001)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_HSH            (0x0200D130)

  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_OFF ( 3)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_WID ( 3)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_MSK (0x00000038)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_MIN (0)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_MAX (7) // 0x00000007
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_DEF (0x00000000)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_HSH (0x0303D130)

#define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_REG                          (0x0000D131)

  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_OFF            ( 0)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_WID            ( 2)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_MSK            (0x00000003)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_MIN            (0)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_MAX            (3) // 0x00000003
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_DEF            (0x00000001)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_HSH            (0x0200D131)

  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_OFF ( 3)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_WID ( 3)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_MSK (0x00000038)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_MIN (0)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_MAX (7) // 0x00000007
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_DEF (0x00000000)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_HSH (0x0303D131)

#define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_REG                          (0x0000D132)

  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_OFF            ( 0)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_WID            ( 2)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_MSK            (0x00000003)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_MIN            (0)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_MAX            (3) // 0x00000003
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_DEF            (0x00000001)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_HSH            (0x0200D132)

  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_OFF ( 3)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_WID ( 3)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_MSK (0x00000038)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_MIN (0)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_MAX (7) // 0x00000007
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_DEF (0x00000000)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_HSH (0x0303D132)

#define CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_0_REG                         (0x0000D134)

  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_OFF                   ( 0)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_WID                   (32)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_MSK                   (0xFFFFFFFF)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_MIN                   (0)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_MAX                   (4294967295) // 0xFFFFFFFF
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_DEF                   (0x0000AA55)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_HSH                   (0x2000D134)

#define CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_1_REG                         (0x0000D138)

  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_OFF                   ( 0)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_WID                   (32)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_MSK                   (0xFFFFFFFF)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_MIN                   (0)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_MAX                   (4294967295) // 0xFFFFFFFF
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_DEF                   (0x0000AA55)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_HSH                   (0x2000D138)

#define CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_2_REG                         (0x0000D13C)

  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_OFF                   ( 0)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_WID                   (32)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_MSK                   (0xFFFFFFFF)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_MIN                   (0)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_MAX                   (4294967295) // 0xFFFFFFFF
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_DEF                   (0x0000AA55)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_HSH                   (0x2000D13C)

#define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_REG                            (0x0000D140)

  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_OFF                    ( 0)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_WID                    ( 1)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_MSK                    (0x00000001)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_MIN                    (0)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_MAX                    (1) // 0x00000001
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_DEF                    (0x00000000)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_HSH                    (0x0100D140)

  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_OFF             ( 4)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_WID             ( 4)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_MSK             (0x000000F0)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_MIN             (0)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_MAX             (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_DEF             (0x00000000)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_HSH             (0x0404D140)

  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_OFF                    ( 8)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_WID                    ( 8)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_MSK                    (0x0000FF00)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_MIN                    (0)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_MAX                    (255) // 0x000000FF
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_DEF                    (0x00000000)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_HSH                    (0x0808D140)

  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_OFF                    (16)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_WID                    ( 8)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_MSK                    (0x00FF0000)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_MIN                    (0)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_MAX                    (255) // 0x000000FF
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_DEF                    (0x00000000)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_HSH                    (0x0810D140)

  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_OFF                    (24)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_WID                    ( 8)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_MSK                    (0xFF000000)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_MIN                    (0)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_MAX                    (255) // 0x000000FF
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_DEF                    (0x00000000)
  #define CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_HSH                    (0x0818D140)

#define CH0_SC1_CR_CADB_BUF_0_REG                                      (0x0000D148)

  #define CH0_SC1_CR_CADB_BUF_0_CS_OFF                                 ( 0)
  #define CH0_SC1_CR_CADB_BUF_0_CS_WID                                 ( 4)
  #define CH0_SC1_CR_CADB_BUF_0_CS_MSK                                 (0x0000000F)
  #define CH0_SC1_CR_CADB_BUF_0_CS_MIN                                 (0)
  #define CH0_SC1_CR_CADB_BUF_0_CS_MAX                                 (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_BUF_0_CS_DEF                                 (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_0_CS_HSH                                 (0x4400D148)

  #define CH0_SC1_CR_CADB_BUF_0_CID_OFF                                ( 4)
  #define CH0_SC1_CR_CADB_BUF_0_CID_WID                                ( 3)
  #define CH0_SC1_CR_CADB_BUF_0_CID_MSK                                (0x00000070)
  #define CH0_SC1_CR_CADB_BUF_0_CID_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_0_CID_MAX                                (7) // 0x00000007
  #define CH0_SC1_CR_CADB_BUF_0_CID_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_0_CID_HSH                                (0x4304D148)

  #define CH0_SC1_CR_CADB_BUF_0_ODT_OFF                                ( 7)
  #define CH0_SC1_CR_CADB_BUF_0_ODT_WID                                ( 4)
  #define CH0_SC1_CR_CADB_BUF_0_ODT_MSK                                (0x00000780)
  #define CH0_SC1_CR_CADB_BUF_0_ODT_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_0_ODT_MAX                                (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_BUF_0_ODT_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_0_ODT_HSH                                (0x4407D148)

  #define CH0_SC1_CR_CADB_BUF_0_CKE_OFF                                (11)
  #define CH0_SC1_CR_CADB_BUF_0_CKE_WID                                ( 4)
  #define CH0_SC1_CR_CADB_BUF_0_CKE_MSK                                (0x00007800)
  #define CH0_SC1_CR_CADB_BUF_0_CKE_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_0_CKE_MAX                                (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_BUF_0_CKE_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_0_CKE_HSH                                (0x440BD148)

  #define CH0_SC1_CR_CADB_BUF_0_USE_HALF_CA_OFF                        (15)
  #define CH0_SC1_CR_CADB_BUF_0_USE_HALF_CA_WID                        ( 1)
  #define CH0_SC1_CR_CADB_BUF_0_USE_HALF_CA_MSK                        (0x00008000)
  #define CH0_SC1_CR_CADB_BUF_0_USE_HALF_CA_MIN                        (0)
  #define CH0_SC1_CR_CADB_BUF_0_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH0_SC1_CR_CADB_BUF_0_USE_HALF_CA_DEF                        (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_0_USE_HALF_CA_HSH                        (0x410FD148)

  #define CH0_SC1_CR_CADB_BUF_0_VAL_OFF                                (16)
  #define CH0_SC1_CR_CADB_BUF_0_VAL_WID                                ( 1)
  #define CH0_SC1_CR_CADB_BUF_0_VAL_MSK                                (0x00010000)
  #define CH0_SC1_CR_CADB_BUF_0_VAL_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_0_VAL_MAX                                (1) // 0x00000001
  #define CH0_SC1_CR_CADB_BUF_0_VAL_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_0_VAL_HSH                                (0x4110D148)

  #define CH0_SC1_CR_CADB_BUF_0_PAR_OFF                                (17)
  #define CH0_SC1_CR_CADB_BUF_0_PAR_WID                                ( 1)
  #define CH0_SC1_CR_CADB_BUF_0_PAR_MSK                                (0x00020000)
  #define CH0_SC1_CR_CADB_BUF_0_PAR_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_0_PAR_MAX                                (1) // 0x00000001
  #define CH0_SC1_CR_CADB_BUF_0_PAR_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_0_PAR_HSH                                (0x4111D148)

  #define CH0_SC1_CR_CADB_BUF_0_CA_OFF                                 (18)
  #define CH0_SC1_CR_CADB_BUF_0_CA_WID                                 (24)
  #define CH0_SC1_CR_CADB_BUF_0_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH0_SC1_CR_CADB_BUF_0_CA_MIN                                 (0)
  #define CH0_SC1_CR_CADB_BUF_0_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH0_SC1_CR_CADB_BUF_0_CA_DEF                                 (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_0_CA_HSH                                 (0x5812D148)

#define CH0_SC1_CR_CADB_BUF_1_REG                                      (0x0000D150)

  #define CH0_SC1_CR_CADB_BUF_1_CS_OFF                                 ( 0)
  #define CH0_SC1_CR_CADB_BUF_1_CS_WID                                 ( 4)
  #define CH0_SC1_CR_CADB_BUF_1_CS_MSK                                 (0x0000000F)
  #define CH0_SC1_CR_CADB_BUF_1_CS_MIN                                 (0)
  #define CH0_SC1_CR_CADB_BUF_1_CS_MAX                                 (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_BUF_1_CS_DEF                                 (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_1_CS_HSH                                 (0x4400D150)

  #define CH0_SC1_CR_CADB_BUF_1_CID_OFF                                ( 4)
  #define CH0_SC1_CR_CADB_BUF_1_CID_WID                                ( 3)
  #define CH0_SC1_CR_CADB_BUF_1_CID_MSK                                (0x00000070)
  #define CH0_SC1_CR_CADB_BUF_1_CID_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_1_CID_MAX                                (7) // 0x00000007
  #define CH0_SC1_CR_CADB_BUF_1_CID_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_1_CID_HSH                                (0x4304D150)

  #define CH0_SC1_CR_CADB_BUF_1_ODT_OFF                                ( 7)
  #define CH0_SC1_CR_CADB_BUF_1_ODT_WID                                ( 4)
  #define CH0_SC1_CR_CADB_BUF_1_ODT_MSK                                (0x00000780)
  #define CH0_SC1_CR_CADB_BUF_1_ODT_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_1_ODT_MAX                                (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_BUF_1_ODT_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_1_ODT_HSH                                (0x4407D150)

  #define CH0_SC1_CR_CADB_BUF_1_CKE_OFF                                (11)
  #define CH0_SC1_CR_CADB_BUF_1_CKE_WID                                ( 4)
  #define CH0_SC1_CR_CADB_BUF_1_CKE_MSK                                (0x00007800)
  #define CH0_SC1_CR_CADB_BUF_1_CKE_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_1_CKE_MAX                                (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_BUF_1_CKE_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_1_CKE_HSH                                (0x440BD150)

  #define CH0_SC1_CR_CADB_BUF_1_USE_HALF_CA_OFF                        (15)
  #define CH0_SC1_CR_CADB_BUF_1_USE_HALF_CA_WID                        ( 1)
  #define CH0_SC1_CR_CADB_BUF_1_USE_HALF_CA_MSK                        (0x00008000)
  #define CH0_SC1_CR_CADB_BUF_1_USE_HALF_CA_MIN                        (0)
  #define CH0_SC1_CR_CADB_BUF_1_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH0_SC1_CR_CADB_BUF_1_USE_HALF_CA_DEF                        (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_1_USE_HALF_CA_HSH                        (0x410FD150)

  #define CH0_SC1_CR_CADB_BUF_1_VAL_OFF                                (16)
  #define CH0_SC1_CR_CADB_BUF_1_VAL_WID                                ( 1)
  #define CH0_SC1_CR_CADB_BUF_1_VAL_MSK                                (0x00010000)
  #define CH0_SC1_CR_CADB_BUF_1_VAL_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_1_VAL_MAX                                (1) // 0x00000001
  #define CH0_SC1_CR_CADB_BUF_1_VAL_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_1_VAL_HSH                                (0x4110D150)

  #define CH0_SC1_CR_CADB_BUF_1_PAR_OFF                                (17)
  #define CH0_SC1_CR_CADB_BUF_1_PAR_WID                                ( 1)
  #define CH0_SC1_CR_CADB_BUF_1_PAR_MSK                                (0x00020000)
  #define CH0_SC1_CR_CADB_BUF_1_PAR_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_1_PAR_MAX                                (1) // 0x00000001
  #define CH0_SC1_CR_CADB_BUF_1_PAR_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_1_PAR_HSH                                (0x4111D150)

  #define CH0_SC1_CR_CADB_BUF_1_CA_OFF                                 (18)
  #define CH0_SC1_CR_CADB_BUF_1_CA_WID                                 (24)
  #define CH0_SC1_CR_CADB_BUF_1_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH0_SC1_CR_CADB_BUF_1_CA_MIN                                 (0)
  #define CH0_SC1_CR_CADB_BUF_1_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH0_SC1_CR_CADB_BUF_1_CA_DEF                                 (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_1_CA_HSH                                 (0x5812D150)

#define CH0_SC1_CR_CADB_BUF_2_REG                                      (0x0000D158)

  #define CH0_SC1_CR_CADB_BUF_2_CS_OFF                                 ( 0)
  #define CH0_SC1_CR_CADB_BUF_2_CS_WID                                 ( 4)
  #define CH0_SC1_CR_CADB_BUF_2_CS_MSK                                 (0x0000000F)
  #define CH0_SC1_CR_CADB_BUF_2_CS_MIN                                 (0)
  #define CH0_SC1_CR_CADB_BUF_2_CS_MAX                                 (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_BUF_2_CS_DEF                                 (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_2_CS_HSH                                 (0x4400D158)

  #define CH0_SC1_CR_CADB_BUF_2_CID_OFF                                ( 4)
  #define CH0_SC1_CR_CADB_BUF_2_CID_WID                                ( 3)
  #define CH0_SC1_CR_CADB_BUF_2_CID_MSK                                (0x00000070)
  #define CH0_SC1_CR_CADB_BUF_2_CID_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_2_CID_MAX                                (7) // 0x00000007
  #define CH0_SC1_CR_CADB_BUF_2_CID_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_2_CID_HSH                                (0x4304D158)

  #define CH0_SC1_CR_CADB_BUF_2_ODT_OFF                                ( 7)
  #define CH0_SC1_CR_CADB_BUF_2_ODT_WID                                ( 4)
  #define CH0_SC1_CR_CADB_BUF_2_ODT_MSK                                (0x00000780)
  #define CH0_SC1_CR_CADB_BUF_2_ODT_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_2_ODT_MAX                                (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_BUF_2_ODT_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_2_ODT_HSH                                (0x4407D158)

  #define CH0_SC1_CR_CADB_BUF_2_CKE_OFF                                (11)
  #define CH0_SC1_CR_CADB_BUF_2_CKE_WID                                ( 4)
  #define CH0_SC1_CR_CADB_BUF_2_CKE_MSK                                (0x00007800)
  #define CH0_SC1_CR_CADB_BUF_2_CKE_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_2_CKE_MAX                                (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_BUF_2_CKE_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_2_CKE_HSH                                (0x440BD158)

  #define CH0_SC1_CR_CADB_BUF_2_USE_HALF_CA_OFF                        (15)
  #define CH0_SC1_CR_CADB_BUF_2_USE_HALF_CA_WID                        ( 1)
  #define CH0_SC1_CR_CADB_BUF_2_USE_HALF_CA_MSK                        (0x00008000)
  #define CH0_SC1_CR_CADB_BUF_2_USE_HALF_CA_MIN                        (0)
  #define CH0_SC1_CR_CADB_BUF_2_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH0_SC1_CR_CADB_BUF_2_USE_HALF_CA_DEF                        (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_2_USE_HALF_CA_HSH                        (0x410FD158)

  #define CH0_SC1_CR_CADB_BUF_2_VAL_OFF                                (16)
  #define CH0_SC1_CR_CADB_BUF_2_VAL_WID                                ( 1)
  #define CH0_SC1_CR_CADB_BUF_2_VAL_MSK                                (0x00010000)
  #define CH0_SC1_CR_CADB_BUF_2_VAL_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_2_VAL_MAX                                (1) // 0x00000001
  #define CH0_SC1_CR_CADB_BUF_2_VAL_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_2_VAL_HSH                                (0x4110D158)

  #define CH0_SC1_CR_CADB_BUF_2_PAR_OFF                                (17)
  #define CH0_SC1_CR_CADB_BUF_2_PAR_WID                                ( 1)
  #define CH0_SC1_CR_CADB_BUF_2_PAR_MSK                                (0x00020000)
  #define CH0_SC1_CR_CADB_BUF_2_PAR_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_2_PAR_MAX                                (1) // 0x00000001
  #define CH0_SC1_CR_CADB_BUF_2_PAR_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_2_PAR_HSH                                (0x4111D158)

  #define CH0_SC1_CR_CADB_BUF_2_CA_OFF                                 (18)
  #define CH0_SC1_CR_CADB_BUF_2_CA_WID                                 (24)
  #define CH0_SC1_CR_CADB_BUF_2_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH0_SC1_CR_CADB_BUF_2_CA_MIN                                 (0)
  #define CH0_SC1_CR_CADB_BUF_2_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH0_SC1_CR_CADB_BUF_2_CA_DEF                                 (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_2_CA_HSH                                 (0x5812D158)

#define CH0_SC1_CR_CADB_BUF_3_REG                                      (0x0000D160)

  #define CH0_SC1_CR_CADB_BUF_3_CS_OFF                                 ( 0)
  #define CH0_SC1_CR_CADB_BUF_3_CS_WID                                 ( 4)
  #define CH0_SC1_CR_CADB_BUF_3_CS_MSK                                 (0x0000000F)
  #define CH0_SC1_CR_CADB_BUF_3_CS_MIN                                 (0)
  #define CH0_SC1_CR_CADB_BUF_3_CS_MAX                                 (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_BUF_3_CS_DEF                                 (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_3_CS_HSH                                 (0x4400D160)

  #define CH0_SC1_CR_CADB_BUF_3_CID_OFF                                ( 4)
  #define CH0_SC1_CR_CADB_BUF_3_CID_WID                                ( 3)
  #define CH0_SC1_CR_CADB_BUF_3_CID_MSK                                (0x00000070)
  #define CH0_SC1_CR_CADB_BUF_3_CID_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_3_CID_MAX                                (7) // 0x00000007
  #define CH0_SC1_CR_CADB_BUF_3_CID_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_3_CID_HSH                                (0x4304D160)

  #define CH0_SC1_CR_CADB_BUF_3_ODT_OFF                                ( 7)
  #define CH0_SC1_CR_CADB_BUF_3_ODT_WID                                ( 4)
  #define CH0_SC1_CR_CADB_BUF_3_ODT_MSK                                (0x00000780)
  #define CH0_SC1_CR_CADB_BUF_3_ODT_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_3_ODT_MAX                                (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_BUF_3_ODT_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_3_ODT_HSH                                (0x4407D160)

  #define CH0_SC1_CR_CADB_BUF_3_CKE_OFF                                (11)
  #define CH0_SC1_CR_CADB_BUF_3_CKE_WID                                ( 4)
  #define CH0_SC1_CR_CADB_BUF_3_CKE_MSK                                (0x00007800)
  #define CH0_SC1_CR_CADB_BUF_3_CKE_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_3_CKE_MAX                                (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_BUF_3_CKE_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_3_CKE_HSH                                (0x440BD160)

  #define CH0_SC1_CR_CADB_BUF_3_USE_HALF_CA_OFF                        (15)
  #define CH0_SC1_CR_CADB_BUF_3_USE_HALF_CA_WID                        ( 1)
  #define CH0_SC1_CR_CADB_BUF_3_USE_HALF_CA_MSK                        (0x00008000)
  #define CH0_SC1_CR_CADB_BUF_3_USE_HALF_CA_MIN                        (0)
  #define CH0_SC1_CR_CADB_BUF_3_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH0_SC1_CR_CADB_BUF_3_USE_HALF_CA_DEF                        (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_3_USE_HALF_CA_HSH                        (0x410FD160)

  #define CH0_SC1_CR_CADB_BUF_3_VAL_OFF                                (16)
  #define CH0_SC1_CR_CADB_BUF_3_VAL_WID                                ( 1)
  #define CH0_SC1_CR_CADB_BUF_3_VAL_MSK                                (0x00010000)
  #define CH0_SC1_CR_CADB_BUF_3_VAL_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_3_VAL_MAX                                (1) // 0x00000001
  #define CH0_SC1_CR_CADB_BUF_3_VAL_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_3_VAL_HSH                                (0x4110D160)

  #define CH0_SC1_CR_CADB_BUF_3_PAR_OFF                                (17)
  #define CH0_SC1_CR_CADB_BUF_3_PAR_WID                                ( 1)
  #define CH0_SC1_CR_CADB_BUF_3_PAR_MSK                                (0x00020000)
  #define CH0_SC1_CR_CADB_BUF_3_PAR_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_3_PAR_MAX                                (1) // 0x00000001
  #define CH0_SC1_CR_CADB_BUF_3_PAR_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_3_PAR_HSH                                (0x4111D160)

  #define CH0_SC1_CR_CADB_BUF_3_CA_OFF                                 (18)
  #define CH0_SC1_CR_CADB_BUF_3_CA_WID                                 (24)
  #define CH0_SC1_CR_CADB_BUF_3_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH0_SC1_CR_CADB_BUF_3_CA_MIN                                 (0)
  #define CH0_SC1_CR_CADB_BUF_3_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH0_SC1_CR_CADB_BUF_3_CA_DEF                                 (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_3_CA_HSH                                 (0x5812D160)

#define CH0_SC1_CR_CADB_BUF_4_REG                                      (0x0000D168)

  #define CH0_SC1_CR_CADB_BUF_4_CS_OFF                                 ( 0)
  #define CH0_SC1_CR_CADB_BUF_4_CS_WID                                 ( 4)
  #define CH0_SC1_CR_CADB_BUF_4_CS_MSK                                 (0x0000000F)
  #define CH0_SC1_CR_CADB_BUF_4_CS_MIN                                 (0)
  #define CH0_SC1_CR_CADB_BUF_4_CS_MAX                                 (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_BUF_4_CS_DEF                                 (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_4_CS_HSH                                 (0x4400D168)

  #define CH0_SC1_CR_CADB_BUF_4_CID_OFF                                ( 4)
  #define CH0_SC1_CR_CADB_BUF_4_CID_WID                                ( 3)
  #define CH0_SC1_CR_CADB_BUF_4_CID_MSK                                (0x00000070)
  #define CH0_SC1_CR_CADB_BUF_4_CID_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_4_CID_MAX                                (7) // 0x00000007
  #define CH0_SC1_CR_CADB_BUF_4_CID_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_4_CID_HSH                                (0x4304D168)

  #define CH0_SC1_CR_CADB_BUF_4_ODT_OFF                                ( 7)
  #define CH0_SC1_CR_CADB_BUF_4_ODT_WID                                ( 4)
  #define CH0_SC1_CR_CADB_BUF_4_ODT_MSK                                (0x00000780)
  #define CH0_SC1_CR_CADB_BUF_4_ODT_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_4_ODT_MAX                                (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_BUF_4_ODT_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_4_ODT_HSH                                (0x4407D168)

  #define CH0_SC1_CR_CADB_BUF_4_CKE_OFF                                (11)
  #define CH0_SC1_CR_CADB_BUF_4_CKE_WID                                ( 4)
  #define CH0_SC1_CR_CADB_BUF_4_CKE_MSK                                (0x00007800)
  #define CH0_SC1_CR_CADB_BUF_4_CKE_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_4_CKE_MAX                                (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_BUF_4_CKE_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_4_CKE_HSH                                (0x440BD168)

  #define CH0_SC1_CR_CADB_BUF_4_USE_HALF_CA_OFF                        (15)
  #define CH0_SC1_CR_CADB_BUF_4_USE_HALF_CA_WID                        ( 1)
  #define CH0_SC1_CR_CADB_BUF_4_USE_HALF_CA_MSK                        (0x00008000)
  #define CH0_SC1_CR_CADB_BUF_4_USE_HALF_CA_MIN                        (0)
  #define CH0_SC1_CR_CADB_BUF_4_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH0_SC1_CR_CADB_BUF_4_USE_HALF_CA_DEF                        (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_4_USE_HALF_CA_HSH                        (0x410FD168)

  #define CH0_SC1_CR_CADB_BUF_4_VAL_OFF                                (16)
  #define CH0_SC1_CR_CADB_BUF_4_VAL_WID                                ( 1)
  #define CH0_SC1_CR_CADB_BUF_4_VAL_MSK                                (0x00010000)
  #define CH0_SC1_CR_CADB_BUF_4_VAL_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_4_VAL_MAX                                (1) // 0x00000001
  #define CH0_SC1_CR_CADB_BUF_4_VAL_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_4_VAL_HSH                                (0x4110D168)

  #define CH0_SC1_CR_CADB_BUF_4_PAR_OFF                                (17)
  #define CH0_SC1_CR_CADB_BUF_4_PAR_WID                                ( 1)
  #define CH0_SC1_CR_CADB_BUF_4_PAR_MSK                                (0x00020000)
  #define CH0_SC1_CR_CADB_BUF_4_PAR_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_4_PAR_MAX                                (1) // 0x00000001
  #define CH0_SC1_CR_CADB_BUF_4_PAR_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_4_PAR_HSH                                (0x4111D168)

  #define CH0_SC1_CR_CADB_BUF_4_CA_OFF                                 (18)
  #define CH0_SC1_CR_CADB_BUF_4_CA_WID                                 (24)
  #define CH0_SC1_CR_CADB_BUF_4_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH0_SC1_CR_CADB_BUF_4_CA_MIN                                 (0)
  #define CH0_SC1_CR_CADB_BUF_4_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH0_SC1_CR_CADB_BUF_4_CA_DEF                                 (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_4_CA_HSH                                 (0x5812D168)

#define CH0_SC1_CR_CADB_BUF_5_REG                                      (0x0000D170)

  #define CH0_SC1_CR_CADB_BUF_5_CS_OFF                                 ( 0)
  #define CH0_SC1_CR_CADB_BUF_5_CS_WID                                 ( 4)
  #define CH0_SC1_CR_CADB_BUF_5_CS_MSK                                 (0x0000000F)
  #define CH0_SC1_CR_CADB_BUF_5_CS_MIN                                 (0)
  #define CH0_SC1_CR_CADB_BUF_5_CS_MAX                                 (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_BUF_5_CS_DEF                                 (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_5_CS_HSH                                 (0x4400D170)

  #define CH0_SC1_CR_CADB_BUF_5_CID_OFF                                ( 4)
  #define CH0_SC1_CR_CADB_BUF_5_CID_WID                                ( 3)
  #define CH0_SC1_CR_CADB_BUF_5_CID_MSK                                (0x00000070)
  #define CH0_SC1_CR_CADB_BUF_5_CID_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_5_CID_MAX                                (7) // 0x00000007
  #define CH0_SC1_CR_CADB_BUF_5_CID_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_5_CID_HSH                                (0x4304D170)

  #define CH0_SC1_CR_CADB_BUF_5_ODT_OFF                                ( 7)
  #define CH0_SC1_CR_CADB_BUF_5_ODT_WID                                ( 4)
  #define CH0_SC1_CR_CADB_BUF_5_ODT_MSK                                (0x00000780)
  #define CH0_SC1_CR_CADB_BUF_5_ODT_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_5_ODT_MAX                                (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_BUF_5_ODT_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_5_ODT_HSH                                (0x4407D170)

  #define CH0_SC1_CR_CADB_BUF_5_CKE_OFF                                (11)
  #define CH0_SC1_CR_CADB_BUF_5_CKE_WID                                ( 4)
  #define CH0_SC1_CR_CADB_BUF_5_CKE_MSK                                (0x00007800)
  #define CH0_SC1_CR_CADB_BUF_5_CKE_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_5_CKE_MAX                                (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_BUF_5_CKE_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_5_CKE_HSH                                (0x440BD170)

  #define CH0_SC1_CR_CADB_BUF_5_USE_HALF_CA_OFF                        (15)
  #define CH0_SC1_CR_CADB_BUF_5_USE_HALF_CA_WID                        ( 1)
  #define CH0_SC1_CR_CADB_BUF_5_USE_HALF_CA_MSK                        (0x00008000)
  #define CH0_SC1_CR_CADB_BUF_5_USE_HALF_CA_MIN                        (0)
  #define CH0_SC1_CR_CADB_BUF_5_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH0_SC1_CR_CADB_BUF_5_USE_HALF_CA_DEF                        (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_5_USE_HALF_CA_HSH                        (0x410FD170)

  #define CH0_SC1_CR_CADB_BUF_5_VAL_OFF                                (16)
  #define CH0_SC1_CR_CADB_BUF_5_VAL_WID                                ( 1)
  #define CH0_SC1_CR_CADB_BUF_5_VAL_MSK                                (0x00010000)
  #define CH0_SC1_CR_CADB_BUF_5_VAL_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_5_VAL_MAX                                (1) // 0x00000001
  #define CH0_SC1_CR_CADB_BUF_5_VAL_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_5_VAL_HSH                                (0x4110D170)

  #define CH0_SC1_CR_CADB_BUF_5_PAR_OFF                                (17)
  #define CH0_SC1_CR_CADB_BUF_5_PAR_WID                                ( 1)
  #define CH0_SC1_CR_CADB_BUF_5_PAR_MSK                                (0x00020000)
  #define CH0_SC1_CR_CADB_BUF_5_PAR_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_5_PAR_MAX                                (1) // 0x00000001
  #define CH0_SC1_CR_CADB_BUF_5_PAR_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_5_PAR_HSH                                (0x4111D170)

  #define CH0_SC1_CR_CADB_BUF_5_CA_OFF                                 (18)
  #define CH0_SC1_CR_CADB_BUF_5_CA_WID                                 (24)
  #define CH0_SC1_CR_CADB_BUF_5_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH0_SC1_CR_CADB_BUF_5_CA_MIN                                 (0)
  #define CH0_SC1_CR_CADB_BUF_5_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH0_SC1_CR_CADB_BUF_5_CA_DEF                                 (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_5_CA_HSH                                 (0x5812D170)

#define CH0_SC1_CR_CADB_BUF_6_REG                                      (0x0000D178)

  #define CH0_SC1_CR_CADB_BUF_6_CS_OFF                                 ( 0)
  #define CH0_SC1_CR_CADB_BUF_6_CS_WID                                 ( 4)
  #define CH0_SC1_CR_CADB_BUF_6_CS_MSK                                 (0x0000000F)
  #define CH0_SC1_CR_CADB_BUF_6_CS_MIN                                 (0)
  #define CH0_SC1_CR_CADB_BUF_6_CS_MAX                                 (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_BUF_6_CS_DEF                                 (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_6_CS_HSH                                 (0x4400D178)

  #define CH0_SC1_CR_CADB_BUF_6_CID_OFF                                ( 4)
  #define CH0_SC1_CR_CADB_BUF_6_CID_WID                                ( 3)
  #define CH0_SC1_CR_CADB_BUF_6_CID_MSK                                (0x00000070)
  #define CH0_SC1_CR_CADB_BUF_6_CID_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_6_CID_MAX                                (7) // 0x00000007
  #define CH0_SC1_CR_CADB_BUF_6_CID_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_6_CID_HSH                                (0x4304D178)

  #define CH0_SC1_CR_CADB_BUF_6_ODT_OFF                                ( 7)
  #define CH0_SC1_CR_CADB_BUF_6_ODT_WID                                ( 4)
  #define CH0_SC1_CR_CADB_BUF_6_ODT_MSK                                (0x00000780)
  #define CH0_SC1_CR_CADB_BUF_6_ODT_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_6_ODT_MAX                                (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_BUF_6_ODT_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_6_ODT_HSH                                (0x4407D178)

  #define CH0_SC1_CR_CADB_BUF_6_CKE_OFF                                (11)
  #define CH0_SC1_CR_CADB_BUF_6_CKE_WID                                ( 4)
  #define CH0_SC1_CR_CADB_BUF_6_CKE_MSK                                (0x00007800)
  #define CH0_SC1_CR_CADB_BUF_6_CKE_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_6_CKE_MAX                                (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_BUF_6_CKE_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_6_CKE_HSH                                (0x440BD178)

  #define CH0_SC1_CR_CADB_BUF_6_USE_HALF_CA_OFF                        (15)
  #define CH0_SC1_CR_CADB_BUF_6_USE_HALF_CA_WID                        ( 1)
  #define CH0_SC1_CR_CADB_BUF_6_USE_HALF_CA_MSK                        (0x00008000)
  #define CH0_SC1_CR_CADB_BUF_6_USE_HALF_CA_MIN                        (0)
  #define CH0_SC1_CR_CADB_BUF_6_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH0_SC1_CR_CADB_BUF_6_USE_HALF_CA_DEF                        (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_6_USE_HALF_CA_HSH                        (0x410FD178)

  #define CH0_SC1_CR_CADB_BUF_6_VAL_OFF                                (16)
  #define CH0_SC1_CR_CADB_BUF_6_VAL_WID                                ( 1)
  #define CH0_SC1_CR_CADB_BUF_6_VAL_MSK                                (0x00010000)
  #define CH0_SC1_CR_CADB_BUF_6_VAL_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_6_VAL_MAX                                (1) // 0x00000001
  #define CH0_SC1_CR_CADB_BUF_6_VAL_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_6_VAL_HSH                                (0x4110D178)

  #define CH0_SC1_CR_CADB_BUF_6_PAR_OFF                                (17)
  #define CH0_SC1_CR_CADB_BUF_6_PAR_WID                                ( 1)
  #define CH0_SC1_CR_CADB_BUF_6_PAR_MSK                                (0x00020000)
  #define CH0_SC1_CR_CADB_BUF_6_PAR_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_6_PAR_MAX                                (1) // 0x00000001
  #define CH0_SC1_CR_CADB_BUF_6_PAR_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_6_PAR_HSH                                (0x4111D178)

  #define CH0_SC1_CR_CADB_BUF_6_CA_OFF                                 (18)
  #define CH0_SC1_CR_CADB_BUF_6_CA_WID                                 (24)
  #define CH0_SC1_CR_CADB_BUF_6_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH0_SC1_CR_CADB_BUF_6_CA_MIN                                 (0)
  #define CH0_SC1_CR_CADB_BUF_6_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH0_SC1_CR_CADB_BUF_6_CA_DEF                                 (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_6_CA_HSH                                 (0x5812D178)

#define CH0_SC1_CR_CADB_BUF_7_REG                                      (0x0000D180)

  #define CH0_SC1_CR_CADB_BUF_7_CS_OFF                                 ( 0)
  #define CH0_SC1_CR_CADB_BUF_7_CS_WID                                 ( 4)
  #define CH0_SC1_CR_CADB_BUF_7_CS_MSK                                 (0x0000000F)
  #define CH0_SC1_CR_CADB_BUF_7_CS_MIN                                 (0)
  #define CH0_SC1_CR_CADB_BUF_7_CS_MAX                                 (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_BUF_7_CS_DEF                                 (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_7_CS_HSH                                 (0x4400D180)

  #define CH0_SC1_CR_CADB_BUF_7_CID_OFF                                ( 4)
  #define CH0_SC1_CR_CADB_BUF_7_CID_WID                                ( 3)
  #define CH0_SC1_CR_CADB_BUF_7_CID_MSK                                (0x00000070)
  #define CH0_SC1_CR_CADB_BUF_7_CID_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_7_CID_MAX                                (7) // 0x00000007
  #define CH0_SC1_CR_CADB_BUF_7_CID_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_7_CID_HSH                                (0x4304D180)

  #define CH0_SC1_CR_CADB_BUF_7_ODT_OFF                                ( 7)
  #define CH0_SC1_CR_CADB_BUF_7_ODT_WID                                ( 4)
  #define CH0_SC1_CR_CADB_BUF_7_ODT_MSK                                (0x00000780)
  #define CH0_SC1_CR_CADB_BUF_7_ODT_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_7_ODT_MAX                                (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_BUF_7_ODT_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_7_ODT_HSH                                (0x4407D180)

  #define CH0_SC1_CR_CADB_BUF_7_CKE_OFF                                (11)
  #define CH0_SC1_CR_CADB_BUF_7_CKE_WID                                ( 4)
  #define CH0_SC1_CR_CADB_BUF_7_CKE_MSK                                (0x00007800)
  #define CH0_SC1_CR_CADB_BUF_7_CKE_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_7_CKE_MAX                                (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_BUF_7_CKE_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_7_CKE_HSH                                (0x440BD180)

  #define CH0_SC1_CR_CADB_BUF_7_USE_HALF_CA_OFF                        (15)
  #define CH0_SC1_CR_CADB_BUF_7_USE_HALF_CA_WID                        ( 1)
  #define CH0_SC1_CR_CADB_BUF_7_USE_HALF_CA_MSK                        (0x00008000)
  #define CH0_SC1_CR_CADB_BUF_7_USE_HALF_CA_MIN                        (0)
  #define CH0_SC1_CR_CADB_BUF_7_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH0_SC1_CR_CADB_BUF_7_USE_HALF_CA_DEF                        (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_7_USE_HALF_CA_HSH                        (0x410FD180)

  #define CH0_SC1_CR_CADB_BUF_7_VAL_OFF                                (16)
  #define CH0_SC1_CR_CADB_BUF_7_VAL_WID                                ( 1)
  #define CH0_SC1_CR_CADB_BUF_7_VAL_MSK                                (0x00010000)
  #define CH0_SC1_CR_CADB_BUF_7_VAL_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_7_VAL_MAX                                (1) // 0x00000001
  #define CH0_SC1_CR_CADB_BUF_7_VAL_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_7_VAL_HSH                                (0x4110D180)

  #define CH0_SC1_CR_CADB_BUF_7_PAR_OFF                                (17)
  #define CH0_SC1_CR_CADB_BUF_7_PAR_WID                                ( 1)
  #define CH0_SC1_CR_CADB_BUF_7_PAR_MSK                                (0x00020000)
  #define CH0_SC1_CR_CADB_BUF_7_PAR_MIN                                (0)
  #define CH0_SC1_CR_CADB_BUF_7_PAR_MAX                                (1) // 0x00000001
  #define CH0_SC1_CR_CADB_BUF_7_PAR_DEF                                (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_7_PAR_HSH                                (0x4111D180)

  #define CH0_SC1_CR_CADB_BUF_7_CA_OFF                                 (18)
  #define CH0_SC1_CR_CADB_BUF_7_CA_WID                                 (24)
  #define CH0_SC1_CR_CADB_BUF_7_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH0_SC1_CR_CADB_BUF_7_CA_MIN                                 (0)
  #define CH0_SC1_CR_CADB_BUF_7_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH0_SC1_CR_CADB_BUF_7_CA_DEF                                 (0x00000000)
  #define CH0_SC1_CR_CADB_BUF_7_CA_HSH                                 (0x5812D180)

#define CH0_SC1_CR_CADB_AO_MRSCFG_REG                                  (0x0000D188)

  #define CH0_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_OFF                  ( 0)
  #define CH0_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_WID                  ( 1)
  #define CH0_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_MSK                  (0x00000001)
  #define CH0_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_MIN                  (0)
  #define CH0_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_MAX                  (1) // 0x00000001
  #define CH0_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_DEF                  (0x00000000)
  #define CH0_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_HSH                  (0x0100D188)

  #define CH0_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_OFF                        ( 1)
  #define CH0_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_WID                        ( 4)
  #define CH0_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_MSK                        (0x0000001E)
  #define CH0_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_MIN                        (0)
  #define CH0_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_MAX                        (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_DEF                        (0x00000000)
  #define CH0_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_HSH                        (0x0401D188)

  #define CH0_SC1_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_OFF                 ( 8)
  #define CH0_SC1_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_WID                 (16)
  #define CH0_SC1_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_MSK                 (0x00FFFF00)
  #define CH0_SC1_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_MIN                 (0)
  #define CH0_SC1_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_MAX                 (65535) // 0x0000FFFF
  #define CH0_SC1_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_DEF                 (0x00000000)
  #define CH0_SC1_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_HSH                 (0x1008D188)

#define CH0_SC1_CR_CADB_SELCFG_REG                                     (0x0000D190)

  #define CH0_SC1_CR_CADB_SELCFG_WR_SELECT_ENABLE_OFF                  ( 0)
  #define CH0_SC1_CR_CADB_SELCFG_WR_SELECT_ENABLE_WID                  ( 3)
  #define CH0_SC1_CR_CADB_SELCFG_WR_SELECT_ENABLE_MSK                  (0x00000007)
  #define CH0_SC1_CR_CADB_SELCFG_WR_SELECT_ENABLE_MIN                  (0)
  #define CH0_SC1_CR_CADB_SELCFG_WR_SELECT_ENABLE_MAX                  (7) // 0x00000007
  #define CH0_SC1_CR_CADB_SELCFG_WR_SELECT_ENABLE_DEF                  (0x00000000)
  #define CH0_SC1_CR_CADB_SELCFG_WR_SELECT_ENABLE_HSH                  (0x0300D190)

  #define CH0_SC1_CR_CADB_SELCFG_RD_SELECT_ENABLE_OFF                  ( 8)
  #define CH0_SC1_CR_CADB_SELCFG_RD_SELECT_ENABLE_WID                  ( 3)
  #define CH0_SC1_CR_CADB_SELCFG_RD_SELECT_ENABLE_MSK                  (0x00000700)
  #define CH0_SC1_CR_CADB_SELCFG_RD_SELECT_ENABLE_MIN                  (0)
  #define CH0_SC1_CR_CADB_SELCFG_RD_SELECT_ENABLE_MAX                  (7) // 0x00000007
  #define CH0_SC1_CR_CADB_SELCFG_RD_SELECT_ENABLE_DEF                  (0x00000000)
  #define CH0_SC1_CR_CADB_SELCFG_RD_SELECT_ENABLE_HSH                  (0x0308D190)

  #define CH0_SC1_CR_CADB_SELCFG_ACT_SELECT_ENABLE_OFF                 (16)
  #define CH0_SC1_CR_CADB_SELCFG_ACT_SELECT_ENABLE_WID                 ( 3)
  #define CH0_SC1_CR_CADB_SELCFG_ACT_SELECT_ENABLE_MSK                 (0x00070000)
  #define CH0_SC1_CR_CADB_SELCFG_ACT_SELECT_ENABLE_MIN                 (0)
  #define CH0_SC1_CR_CADB_SELCFG_ACT_SELECT_ENABLE_MAX                 (7) // 0x00000007
  #define CH0_SC1_CR_CADB_SELCFG_ACT_SELECT_ENABLE_DEF                 (0x00000000)
  #define CH0_SC1_CR_CADB_SELCFG_ACT_SELECT_ENABLE_HSH                 (0x0310D190)

  #define CH0_SC1_CR_CADB_SELCFG_PRE_SELECT_ENABLE_OFF                 (24)
  #define CH0_SC1_CR_CADB_SELCFG_PRE_SELECT_ENABLE_WID                 ( 3)
  #define CH0_SC1_CR_CADB_SELCFG_PRE_SELECT_ENABLE_MSK                 (0x07000000)
  #define CH0_SC1_CR_CADB_SELCFG_PRE_SELECT_ENABLE_MIN                 (0)
  #define CH0_SC1_CR_CADB_SELCFG_PRE_SELECT_ENABLE_MAX                 (7) // 0x00000007
  #define CH0_SC1_CR_CADB_SELCFG_PRE_SELECT_ENABLE_DEF                 (0x00000000)
  #define CH0_SC1_CR_CADB_SELCFG_PRE_SELECT_ENABLE_HSH                 (0x0318D190)

  #define CH0_SC1_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_OFF               (28)
  #define CH0_SC1_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_WID               ( 1)
  #define CH0_SC1_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_MSK               (0x10000000)
  #define CH0_SC1_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_MIN               (0)
  #define CH0_SC1_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_MAX               (1) // 0x00000001
  #define CH0_SC1_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_DEF               (0x00000001)
  #define CH0_SC1_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_HSH               (0x011CD190)

#define CH0_SC1_CR_CADB_MRSCFG_REG                                     (0x0000D198)

  #define CH0_SC1_CR_CADB_MRSCFG_CS_CLOCKS_OFF                         ( 0)
  #define CH0_SC1_CR_CADB_MRSCFG_CS_CLOCKS_WID                         ( 3)
  #define CH0_SC1_CR_CADB_MRSCFG_CS_CLOCKS_MSK                         (0x00000007)
  #define CH0_SC1_CR_CADB_MRSCFG_CS_CLOCKS_MIN                         (0)
  #define CH0_SC1_CR_CADB_MRSCFG_CS_CLOCKS_MAX                         (7) // 0x00000007
  #define CH0_SC1_CR_CADB_MRSCFG_CS_CLOCKS_DEF                         (0x00000000)
  #define CH0_SC1_CR_CADB_MRSCFG_CS_CLOCKS_HSH                         (0x4300D198)

  #define CH0_SC1_CR_CADB_MRSCFG_DSEL_CLOCKS_OFF                       ( 3)
  #define CH0_SC1_CR_CADB_MRSCFG_DSEL_CLOCKS_WID                       ( 4)
  #define CH0_SC1_CR_CADB_MRSCFG_DSEL_CLOCKS_MSK                       (0x00000078)
  #define CH0_SC1_CR_CADB_MRSCFG_DSEL_CLOCKS_MIN                       (0)
  #define CH0_SC1_CR_CADB_MRSCFG_DSEL_CLOCKS_MAX                       (15) // 0x0000000F
  #define CH0_SC1_CR_CADB_MRSCFG_DSEL_CLOCKS_DEF                       (0x00000000)
  #define CH0_SC1_CR_CADB_MRSCFG_DSEL_CLOCKS_HSH                       (0x4403D198)

  #define CH0_SC1_CR_CADB_MRSCFG_SETUP_CLOCKS_OFF                      ( 8)
  #define CH0_SC1_CR_CADB_MRSCFG_SETUP_CLOCKS_WID                      ( 3)
  #define CH0_SC1_CR_CADB_MRSCFG_SETUP_CLOCKS_MSK                      (0x00000700)
  #define CH0_SC1_CR_CADB_MRSCFG_SETUP_CLOCKS_MIN                      (0)
  #define CH0_SC1_CR_CADB_MRSCFG_SETUP_CLOCKS_MAX                      (7) // 0x00000007
  #define CH0_SC1_CR_CADB_MRSCFG_SETUP_CLOCKS_DEF                      (0x00000000)
  #define CH0_SC1_CR_CADB_MRSCFG_SETUP_CLOCKS_HSH                      (0x4308D198)

  #define CH0_SC1_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_OFF                (11)
  #define CH0_SC1_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_WID                ( 1)
  #define CH0_SC1_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_MSK                (0x00000800)
  #define CH0_SC1_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_MIN                (0)
  #define CH0_SC1_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_MAX                (1) // 0x00000001
  #define CH0_SC1_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_DEF                (0x00000000)
  #define CH0_SC1_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_HSH                (0x410BD198)

  #define CH0_SC1_CR_CADB_MRSCFG_MRS_START_PTR_OFF                     (12)
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_START_PTR_WID                     ( 3)
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_START_PTR_MSK                     (0x00007000)
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_START_PTR_MIN                     (0)
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_START_PTR_MAX                     (7) // 0x00000007
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_START_PTR_DEF                     (0x00000000)
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_START_PTR_HSH                     (0x430CD198)

  #define CH0_SC1_CR_CADB_MRSCFG_MRS_END_PTR_OFF                       (16)
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_END_PTR_WID                       ( 3)
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_END_PTR_MSK                       (0x00070000)
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_END_PTR_MIN                       (0)
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_END_PTR_MAX                       (7) // 0x00000007
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_END_PTR_DEF                       (0x00000000)
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_END_PTR_HSH                       (0x4310D198)

  #define CH0_SC1_CR_CADB_MRSCFG_MRS_GOTO_PTR_OFF                      (19)
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_GOTO_PTR_WID                      ( 3)
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_GOTO_PTR_MSK                      (0x00380000)
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_GOTO_PTR_MIN                      (0)
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_GOTO_PTR_MAX                      (7) // 0x00000007
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_GOTO_PTR_DEF                      (0x00000000)
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_GOTO_PTR_HSH                      (0x4313D198)

  #define CH0_SC1_CR_CADB_MRSCFG_MRS_CS_MODE_OFF                       (22)
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_CS_MODE_WID                       ( 2)
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_CS_MODE_MSK                       (0x00C00000)
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_CS_MODE_MIN                       (0)
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_CS_MODE_MAX                       (3) // 0x00000003
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_CS_MODE_DEF                       (0x00000000)
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_CS_MODE_HSH                       (0x4216D198)

  #define CH0_SC1_CR_CADB_MRSCFG_MRS_DELAY_CNT_OFF                     (24)
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_DELAY_CNT_WID                     (16)
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_DELAY_CNT_MSK                     (0x000000FFFF000000ULL)
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_DELAY_CNT_MIN                     (0)
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_DELAY_CNT_MAX                     (65535) // 0x0000FFFF
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_DELAY_CNT_DEF                     (0x00000000)
  #define CH0_SC1_CR_CADB_MRSCFG_MRS_DELAY_CNT_HSH                     (0x5018D198)

#define CH1_SC0_CR_CADB_ACCESS_CONTROL_POLICY_REG                      (0x0000D200)

  #define CH1_SC0_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_OFF     ( 0)
  #define CH1_SC0_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_WID     (64)
  #define CH1_SC0_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_MSK     (0xFFFFFFFFFFFFFFFFULL)
  #define CH1_SC0_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_MIN     (0)
  #define CH1_SC0_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_MAX     (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define CH1_SC0_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_DEF     (0x40001000208)
  #define CH1_SC0_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_HSH     (0x4000D200)

#define CH1_SC0_CR_CADB_ACCESS_READ_POLICY_REG                         (0x0000D208)

  #define CH1_SC0_CR_CADB_ACCESS_READ_POLICY_Read_Policy_OFF           ( 0)
  #define CH1_SC0_CR_CADB_ACCESS_READ_POLICY_Read_Policy_WID           (64)
  #define CH1_SC0_CR_CADB_ACCESS_READ_POLICY_Read_Policy_MSK           (0xFFFFFFFFFFFFFFFFULL)
  #define CH1_SC0_CR_CADB_ACCESS_READ_POLICY_Read_Policy_MIN           (0)
  #define CH1_SC0_CR_CADB_ACCESS_READ_POLICY_Read_Policy_MAX           (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define CH1_SC0_CR_CADB_ACCESS_READ_POLICY_Read_Policy_DEF           (0xFFFFFFFFFFFFFFFF)
  #define CH1_SC0_CR_CADB_ACCESS_READ_POLICY_Read_Policy_HSH           (0x4000D208)

#define CH1_SC0_CR_CADB_ACCESS_WRITE_POLICY_REG                        (0x0000D210)

  #define CH1_SC0_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_OFF         ( 0)
  #define CH1_SC0_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_WID         (64)
  #define CH1_SC0_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_MSK         (0xFFFFFFFFFFFFFFFFULL)
  #define CH1_SC0_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_MIN         (0)
  #define CH1_SC0_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_MAX         (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define CH1_SC0_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_DEF         (0x4000100021A)
  #define CH1_SC0_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_HSH         (0x4000D210)

#define CH1_SC0_CR_CADB_CTL_REG                                        (0x0000D220)

  #define CH1_SC0_CR_CADB_CTL_START_TEST_OFF                           ( 0)
  #define CH1_SC0_CR_CADB_CTL_START_TEST_WID                           ( 1)
  #define CH1_SC0_CR_CADB_CTL_START_TEST_MSK                           (0x00000001)
  #define CH1_SC0_CR_CADB_CTL_START_TEST_MIN                           (0)
  #define CH1_SC0_CR_CADB_CTL_START_TEST_MAX                           (1) // 0x00000001
  #define CH1_SC0_CR_CADB_CTL_START_TEST_DEF                           (0x00000000)
  #define CH1_SC0_CR_CADB_CTL_START_TEST_HSH                           (0x0100D220)

  #define CH1_SC0_CR_CADB_CTL_STOP_TEST_OFF                            ( 1)
  #define CH1_SC0_CR_CADB_CTL_STOP_TEST_WID                            ( 1)
  #define CH1_SC0_CR_CADB_CTL_STOP_TEST_MSK                            (0x00000002)
  #define CH1_SC0_CR_CADB_CTL_STOP_TEST_MIN                            (0)
  #define CH1_SC0_CR_CADB_CTL_STOP_TEST_MAX                            (1) // 0x00000001
  #define CH1_SC0_CR_CADB_CTL_STOP_TEST_DEF                            (0x00000000)
  #define CH1_SC0_CR_CADB_CTL_STOP_TEST_HSH                            (0x0101D220)

#define CH1_SC0_CR_CADB_CFG_REG                                        (0x0000D224)

  #define CH1_SC0_CR_CADB_CFG_CMD_DESELECT_START_OFF                   ( 0)
  #define CH1_SC0_CR_CADB_CFG_CMD_DESELECT_START_WID                   ( 4)
  #define CH1_SC0_CR_CADB_CFG_CMD_DESELECT_START_MSK                   (0x0000000F)
  #define CH1_SC0_CR_CADB_CFG_CMD_DESELECT_START_MIN                   (0)
  #define CH1_SC0_CR_CADB_CFG_CMD_DESELECT_START_MAX                   (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_CFG_CMD_DESELECT_START_DEF                   (0x00000000)
  #define CH1_SC0_CR_CADB_CFG_CMD_DESELECT_START_HSH                   (0x0400D224)

  #define CH1_SC0_CR_CADB_CFG_CMD_DESELECT_STOP_OFF                    ( 4)
  #define CH1_SC0_CR_CADB_CFG_CMD_DESELECT_STOP_WID                    ( 4)
  #define CH1_SC0_CR_CADB_CFG_CMD_DESELECT_STOP_MSK                    (0x000000F0)
  #define CH1_SC0_CR_CADB_CFG_CMD_DESELECT_STOP_MIN                    (0)
  #define CH1_SC0_CR_CADB_CFG_CMD_DESELECT_STOP_MAX                    (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_CFG_CMD_DESELECT_STOP_DEF                    (0x00000000)
  #define CH1_SC0_CR_CADB_CFG_CMD_DESELECT_STOP_HSH                    (0x0404D224)

  #define CH1_SC0_CR_CADB_CFG_LANE_DESELECT_EN_OFF                     ( 8)
  #define CH1_SC0_CR_CADB_CFG_LANE_DESELECT_EN_WID                     ( 3)
  #define CH1_SC0_CR_CADB_CFG_LANE_DESELECT_EN_MSK                     (0x00000700)
  #define CH1_SC0_CR_CADB_CFG_LANE_DESELECT_EN_MIN                     (0)
  #define CH1_SC0_CR_CADB_CFG_LANE_DESELECT_EN_MAX                     (7) // 0x00000007
  #define CH1_SC0_CR_CADB_CFG_LANE_DESELECT_EN_DEF                     (0x00000000)
  #define CH1_SC0_CR_CADB_CFG_LANE_DESELECT_EN_HSH                     (0x0308D224)

  #define CH1_SC0_CR_CADB_CFG_INITIAL_DSEL_EN_OFF                      (11)
  #define CH1_SC0_CR_CADB_CFG_INITIAL_DSEL_EN_WID                      ( 1)
  #define CH1_SC0_CR_CADB_CFG_INITIAL_DSEL_EN_MSK                      (0x00000800)
  #define CH1_SC0_CR_CADB_CFG_INITIAL_DSEL_EN_MIN                      (0)
  #define CH1_SC0_CR_CADB_CFG_INITIAL_DSEL_EN_MAX                      (1) // 0x00000001
  #define CH1_SC0_CR_CADB_CFG_INITIAL_DSEL_EN_DEF                      (0x00000001)
  #define CH1_SC0_CR_CADB_CFG_INITIAL_DSEL_EN_HSH                      (0x010BD224)

  #define CH1_SC0_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_OFF                 (12)
  #define CH1_SC0_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_WID                 ( 1)
  #define CH1_SC0_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_MSK                 (0x00001000)
  #define CH1_SC0_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_MIN                 (0)
  #define CH1_SC0_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_MAX                 (1) // 0x00000001
  #define CH1_SC0_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_DEF                 (0x00000001)
  #define CH1_SC0_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_HSH                 (0x010CD224)

  #define CH1_SC0_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_OFF              (13)
  #define CH1_SC0_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_WID              ( 3)
  #define CH1_SC0_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_MSK              (0x0000E000)
  #define CH1_SC0_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_MIN              (0)
  #define CH1_SC0_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_MAX              (7) // 0x00000007
  #define CH1_SC0_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_DEF              (0x00000000)
  #define CH1_SC0_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_HSH              (0x030DD224)

  #define CH1_SC0_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_OFF               (16)
  #define CH1_SC0_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_WID               ( 3)
  #define CH1_SC0_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_MSK               (0x00070000)
  #define CH1_SC0_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_MIN               (0)
  #define CH1_SC0_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_MAX               (7) // 0x00000007
  #define CH1_SC0_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_DEF               (0x00000000)
  #define CH1_SC0_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_HSH               (0x0310D224)

  #define CH1_SC0_CR_CADB_CFG_CADB_TO_CPGC_BIND_OFF                    (24)
  #define CH1_SC0_CR_CADB_CFG_CADB_TO_CPGC_BIND_WID                    ( 1)
  #define CH1_SC0_CR_CADB_CFG_CADB_TO_CPGC_BIND_MSK                    (0x01000000)
  #define CH1_SC0_CR_CADB_CFG_CADB_TO_CPGC_BIND_MIN                    (0)
  #define CH1_SC0_CR_CADB_CFG_CADB_TO_CPGC_BIND_MAX                    (1) // 0x00000001
  #define CH1_SC0_CR_CADB_CFG_CADB_TO_CPGC_BIND_DEF                    (0x00000000)
  #define CH1_SC0_CR_CADB_CFG_CADB_TO_CPGC_BIND_HSH                    (0x0118D224)

  #define CH1_SC0_CR_CADB_CFG_GLOBAL_START_BIND_OFF                    (25)
  #define CH1_SC0_CR_CADB_CFG_GLOBAL_START_BIND_WID                    ( 1)
  #define CH1_SC0_CR_CADB_CFG_GLOBAL_START_BIND_MSK                    (0x02000000)
  #define CH1_SC0_CR_CADB_CFG_GLOBAL_START_BIND_MIN                    (0)
  #define CH1_SC0_CR_CADB_CFG_GLOBAL_START_BIND_MAX                    (1) // 0x00000001
  #define CH1_SC0_CR_CADB_CFG_GLOBAL_START_BIND_DEF                    (0x00000000)
  #define CH1_SC0_CR_CADB_CFG_GLOBAL_START_BIND_HSH                    (0x0119D224)

  #define CH1_SC0_CR_CADB_CFG_GLOBAL_STOP_BIND_OFF                     (26)
  #define CH1_SC0_CR_CADB_CFG_GLOBAL_STOP_BIND_WID                     ( 1)
  #define CH1_SC0_CR_CADB_CFG_GLOBAL_STOP_BIND_MSK                     (0x04000000)
  #define CH1_SC0_CR_CADB_CFG_GLOBAL_STOP_BIND_MIN                     (0)
  #define CH1_SC0_CR_CADB_CFG_GLOBAL_STOP_BIND_MAX                     (1) // 0x00000001
  #define CH1_SC0_CR_CADB_CFG_GLOBAL_STOP_BIND_DEF                     (0x00000000)
  #define CH1_SC0_CR_CADB_CFG_GLOBAL_STOP_BIND_HSH                     (0x011AD224)

  #define CH1_SC0_CR_CADB_CFG_CADB_MODE_OFF                            (29)
  #define CH1_SC0_CR_CADB_CFG_CADB_MODE_WID                            ( 3)
  #define CH1_SC0_CR_CADB_CFG_CADB_MODE_MSK                            (0xE0000000)
  #define CH1_SC0_CR_CADB_CFG_CADB_MODE_MIN                            (0)
  #define CH1_SC0_CR_CADB_CFG_CADB_MODE_MAX                            (7) // 0x00000007
  #define CH1_SC0_CR_CADB_CFG_CADB_MODE_DEF                            (0x00000000)
  #define CH1_SC0_CR_CADB_CFG_CADB_MODE_HSH                            (0x031DD224)

#define CH1_SC0_CR_CADB_DLY_REG                                        (0x0000D228)

  #define CH1_SC0_CR_CADB_DLY_START_DELAY_OFF                          ( 0)
  #define CH1_SC0_CR_CADB_DLY_START_DELAY_WID                          (10)
  #define CH1_SC0_CR_CADB_DLY_START_DELAY_MSK                          (0x000003FF)
  #define CH1_SC0_CR_CADB_DLY_START_DELAY_MIN                          (0)
  #define CH1_SC0_CR_CADB_DLY_START_DELAY_MAX                          (1023) // 0x000003FF
  #define CH1_SC0_CR_CADB_DLY_START_DELAY_DEF                          (0x00000000)
  #define CH1_SC0_CR_CADB_DLY_START_DELAY_HSH                          (0x0A00D228)

  #define CH1_SC0_CR_CADB_DLY_STOP_DELAY_OFF                           (16)
  #define CH1_SC0_CR_CADB_DLY_STOP_DELAY_WID                           (10)
  #define CH1_SC0_CR_CADB_DLY_STOP_DELAY_MSK                           (0x03FF0000)
  #define CH1_SC0_CR_CADB_DLY_STOP_DELAY_MIN                           (0)
  #define CH1_SC0_CR_CADB_DLY_STOP_DELAY_MAX                           (1023) // 0x000003FF
  #define CH1_SC0_CR_CADB_DLY_STOP_DELAY_DEF                           (0x00000000)
  #define CH1_SC0_CR_CADB_DLY_STOP_DELAY_HSH                           (0x0A10D228)

#define CH1_SC0_CR_CADB_STATUS_REG                                     (0x0000D22C)

  #define CH1_SC0_CR_CADB_STATUS_MRS_CURR_PTR_OFF                      (21)
  #define CH1_SC0_CR_CADB_STATUS_MRS_CURR_PTR_WID                      ( 3)
  #define CH1_SC0_CR_CADB_STATUS_MRS_CURR_PTR_MSK                      (0x00E00000)
  #define CH1_SC0_CR_CADB_STATUS_MRS_CURR_PTR_MIN                      (0)
  #define CH1_SC0_CR_CADB_STATUS_MRS_CURR_PTR_MAX                      (7) // 0x00000007
  #define CH1_SC0_CR_CADB_STATUS_MRS_CURR_PTR_DEF                      (0x00000000)
  #define CH1_SC0_CR_CADB_STATUS_MRS_CURR_PTR_HSH                      (0x0315D22C)

  #define CH1_SC0_CR_CADB_STATUS_TEST_ABORTED_OFF                      (24)
  #define CH1_SC0_CR_CADB_STATUS_TEST_ABORTED_WID                      ( 1)
  #define CH1_SC0_CR_CADB_STATUS_TEST_ABORTED_MSK                      (0x01000000)
  #define CH1_SC0_CR_CADB_STATUS_TEST_ABORTED_MIN                      (0)
  #define CH1_SC0_CR_CADB_STATUS_TEST_ABORTED_MAX                      (1) // 0x00000001
  #define CH1_SC0_CR_CADB_STATUS_TEST_ABORTED_DEF                      (0x00000000)
  #define CH1_SC0_CR_CADB_STATUS_TEST_ABORTED_HSH                      (0x0118D22C)

  #define CH1_SC0_CR_CADB_STATUS_ALGO_DONE_OFF                         (28)
  #define CH1_SC0_CR_CADB_STATUS_ALGO_DONE_WID                         ( 1)
  #define CH1_SC0_CR_CADB_STATUS_ALGO_DONE_MSK                         (0x10000000)
  #define CH1_SC0_CR_CADB_STATUS_ALGO_DONE_MIN                         (0)
  #define CH1_SC0_CR_CADB_STATUS_ALGO_DONE_MAX                         (1) // 0x00000001
  #define CH1_SC0_CR_CADB_STATUS_ALGO_DONE_DEF                         (0x00000000)
  #define CH1_SC0_CR_CADB_STATUS_ALGO_DONE_HSH                         (0x011CD22C)

  #define CH1_SC0_CR_CADB_STATUS_START_TEST_DELAY_BUSY_OFF             (29)
  #define CH1_SC0_CR_CADB_STATUS_START_TEST_DELAY_BUSY_WID             ( 1)
  #define CH1_SC0_CR_CADB_STATUS_START_TEST_DELAY_BUSY_MSK             (0x20000000)
  #define CH1_SC0_CR_CADB_STATUS_START_TEST_DELAY_BUSY_MIN             (0)
  #define CH1_SC0_CR_CADB_STATUS_START_TEST_DELAY_BUSY_MAX             (1) // 0x00000001
  #define CH1_SC0_CR_CADB_STATUS_START_TEST_DELAY_BUSY_DEF             (0x00000000)
  #define CH1_SC0_CR_CADB_STATUS_START_TEST_DELAY_BUSY_HSH             (0x011DD22C)

  #define CH1_SC0_CR_CADB_STATUS_TEST_BUSY_OFF                         (30)
  #define CH1_SC0_CR_CADB_STATUS_TEST_BUSY_WID                         ( 1)
  #define CH1_SC0_CR_CADB_STATUS_TEST_BUSY_MSK                         (0x40000000)
  #define CH1_SC0_CR_CADB_STATUS_TEST_BUSY_MIN                         (0)
  #define CH1_SC0_CR_CADB_STATUS_TEST_BUSY_MAX                         (1) // 0x00000001
  #define CH1_SC0_CR_CADB_STATUS_TEST_BUSY_DEF                         (0x00000000)
  #define CH1_SC0_CR_CADB_STATUS_TEST_BUSY_HSH                         (0x011ED22C)

  #define CH1_SC0_CR_CADB_STATUS_TEST_DONE_OFF                         (31)
  #define CH1_SC0_CR_CADB_STATUS_TEST_DONE_WID                         ( 1)
  #define CH1_SC0_CR_CADB_STATUS_TEST_DONE_MSK                         (0x80000000)
  #define CH1_SC0_CR_CADB_STATUS_TEST_DONE_MIN                         (0)
  #define CH1_SC0_CR_CADB_STATUS_TEST_DONE_MAX                         (1) // 0x00000001
  #define CH1_SC0_CR_CADB_STATUS_TEST_DONE_DEF                         (0x00000000)
  #define CH1_SC0_CR_CADB_STATUS_TEST_DONE_HSH                         (0x011FD22C)

#define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_REG                          (0x0000D230)

  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_OFF            ( 0)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_WID            ( 2)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_MSK            (0x00000003)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_MIN            (0)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_MAX            (3) // 0x00000003
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_DEF            (0x00000001)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_HSH            (0x0200D230)

  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_OFF ( 3)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_WID ( 3)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_MSK (0x00000038)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_MIN (0)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_MAX (7) // 0x00000007
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_DEF (0x00000000)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_HSH (0x0303D230)

#define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_REG                          (0x0000D231)

  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_OFF            ( 0)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_WID            ( 2)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_MSK            (0x00000003)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_MIN            (0)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_MAX            (3) // 0x00000003
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_DEF            (0x00000001)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_HSH            (0x0200D231)

  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_OFF ( 3)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_WID ( 3)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_MSK (0x00000038)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_MIN (0)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_MAX (7) // 0x00000007
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_DEF (0x00000000)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_HSH (0x0303D231)

#define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_REG                          (0x0000D232)

  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_OFF            ( 0)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_WID            ( 2)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_MSK            (0x00000003)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_MIN            (0)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_MAX            (3) // 0x00000003
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_DEF            (0x00000001)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_HSH            (0x0200D232)

  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_OFF ( 3)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_WID ( 3)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_MSK (0x00000038)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_MIN (0)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_MAX (7) // 0x00000007
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_DEF (0x00000000)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_HSH (0x0303D232)

#define CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_0_REG                         (0x0000D234)

  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_OFF                   ( 0)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_WID                   (32)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_MSK                   (0xFFFFFFFF)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_MIN                   (0)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_MAX                   (4294967295) // 0xFFFFFFFF
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_DEF                   (0x0000AA55)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_HSH                   (0x2000D234)

#define CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_1_REG                         (0x0000D238)

  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_OFF                   ( 0)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_WID                   (32)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_MSK                   (0xFFFFFFFF)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_MIN                   (0)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_MAX                   (4294967295) // 0xFFFFFFFF
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_DEF                   (0x0000AA55)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_HSH                   (0x2000D238)

#define CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_2_REG                         (0x0000D23C)

  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_OFF                   ( 0)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_WID                   (32)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_MSK                   (0xFFFFFFFF)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_MIN                   (0)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_MAX                   (4294967295) // 0xFFFFFFFF
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_DEF                   (0x0000AA55)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_HSH                   (0x2000D23C)

#define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_REG                            (0x0000D240)

  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_OFF                    ( 0)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_WID                    ( 1)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_MSK                    (0x00000001)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_MIN                    (0)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_MAX                    (1) // 0x00000001
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_DEF                    (0x00000000)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_HSH                    (0x0100D240)

  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_OFF             ( 4)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_WID             ( 4)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_MSK             (0x000000F0)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_MIN             (0)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_MAX             (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_DEF             (0x00000000)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_HSH             (0x0404D240)

  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_OFF                    ( 8)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_WID                    ( 8)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_MSK                    (0x0000FF00)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_MIN                    (0)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_MAX                    (255) // 0x000000FF
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_DEF                    (0x00000000)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_HSH                    (0x0808D240)

  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_OFF                    (16)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_WID                    ( 8)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_MSK                    (0x00FF0000)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_MIN                    (0)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_MAX                    (255) // 0x000000FF
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_DEF                    (0x00000000)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_HSH                    (0x0810D240)

  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_OFF                    (24)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_WID                    ( 8)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_MSK                    (0xFF000000)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_MIN                    (0)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_MAX                    (255) // 0x000000FF
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_DEF                    (0x00000000)
  #define CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_HSH                    (0x0818D240)

#define CH1_SC0_CR_CADB_BUF_0_REG                                      (0x0000D248)

  #define CH1_SC0_CR_CADB_BUF_0_CS_OFF                                 ( 0)
  #define CH1_SC0_CR_CADB_BUF_0_CS_WID                                 ( 4)
  #define CH1_SC0_CR_CADB_BUF_0_CS_MSK                                 (0x0000000F)
  #define CH1_SC0_CR_CADB_BUF_0_CS_MIN                                 (0)
  #define CH1_SC0_CR_CADB_BUF_0_CS_MAX                                 (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_BUF_0_CS_DEF                                 (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_0_CS_HSH                                 (0x4400D248)

  #define CH1_SC0_CR_CADB_BUF_0_CID_OFF                                ( 4)
  #define CH1_SC0_CR_CADB_BUF_0_CID_WID                                ( 3)
  #define CH1_SC0_CR_CADB_BUF_0_CID_MSK                                (0x00000070)
  #define CH1_SC0_CR_CADB_BUF_0_CID_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_0_CID_MAX                                (7) // 0x00000007
  #define CH1_SC0_CR_CADB_BUF_0_CID_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_0_CID_HSH                                (0x4304D248)

  #define CH1_SC0_CR_CADB_BUF_0_ODT_OFF                                ( 7)
  #define CH1_SC0_CR_CADB_BUF_0_ODT_WID                                ( 4)
  #define CH1_SC0_CR_CADB_BUF_0_ODT_MSK                                (0x00000780)
  #define CH1_SC0_CR_CADB_BUF_0_ODT_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_0_ODT_MAX                                (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_BUF_0_ODT_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_0_ODT_HSH                                (0x4407D248)

  #define CH1_SC0_CR_CADB_BUF_0_CKE_OFF                                (11)
  #define CH1_SC0_CR_CADB_BUF_0_CKE_WID                                ( 4)
  #define CH1_SC0_CR_CADB_BUF_0_CKE_MSK                                (0x00007800)
  #define CH1_SC0_CR_CADB_BUF_0_CKE_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_0_CKE_MAX                                (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_BUF_0_CKE_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_0_CKE_HSH                                (0x440BD248)

  #define CH1_SC0_CR_CADB_BUF_0_USE_HALF_CA_OFF                        (15)
  #define CH1_SC0_CR_CADB_BUF_0_USE_HALF_CA_WID                        ( 1)
  #define CH1_SC0_CR_CADB_BUF_0_USE_HALF_CA_MSK                        (0x00008000)
  #define CH1_SC0_CR_CADB_BUF_0_USE_HALF_CA_MIN                        (0)
  #define CH1_SC0_CR_CADB_BUF_0_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH1_SC0_CR_CADB_BUF_0_USE_HALF_CA_DEF                        (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_0_USE_HALF_CA_HSH                        (0x410FD248)

  #define CH1_SC0_CR_CADB_BUF_0_VAL_OFF                                (16)
  #define CH1_SC0_CR_CADB_BUF_0_VAL_WID                                ( 1)
  #define CH1_SC0_CR_CADB_BUF_0_VAL_MSK                                (0x00010000)
  #define CH1_SC0_CR_CADB_BUF_0_VAL_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_0_VAL_MAX                                (1) // 0x00000001
  #define CH1_SC0_CR_CADB_BUF_0_VAL_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_0_VAL_HSH                                (0x4110D248)

  #define CH1_SC0_CR_CADB_BUF_0_PAR_OFF                                (17)
  #define CH1_SC0_CR_CADB_BUF_0_PAR_WID                                ( 1)
  #define CH1_SC0_CR_CADB_BUF_0_PAR_MSK                                (0x00020000)
  #define CH1_SC0_CR_CADB_BUF_0_PAR_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_0_PAR_MAX                                (1) // 0x00000001
  #define CH1_SC0_CR_CADB_BUF_0_PAR_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_0_PAR_HSH                                (0x4111D248)

  #define CH1_SC0_CR_CADB_BUF_0_CA_OFF                                 (18)
  #define CH1_SC0_CR_CADB_BUF_0_CA_WID                                 (24)
  #define CH1_SC0_CR_CADB_BUF_0_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH1_SC0_CR_CADB_BUF_0_CA_MIN                                 (0)
  #define CH1_SC0_CR_CADB_BUF_0_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH1_SC0_CR_CADB_BUF_0_CA_DEF                                 (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_0_CA_HSH                                 (0x5812D248)

#define CH1_SC0_CR_CADB_BUF_1_REG                                      (0x0000D250)

  #define CH1_SC0_CR_CADB_BUF_1_CS_OFF                                 ( 0)
  #define CH1_SC0_CR_CADB_BUF_1_CS_WID                                 ( 4)
  #define CH1_SC0_CR_CADB_BUF_1_CS_MSK                                 (0x0000000F)
  #define CH1_SC0_CR_CADB_BUF_1_CS_MIN                                 (0)
  #define CH1_SC0_CR_CADB_BUF_1_CS_MAX                                 (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_BUF_1_CS_DEF                                 (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_1_CS_HSH                                 (0x4400D250)

  #define CH1_SC0_CR_CADB_BUF_1_CID_OFF                                ( 4)
  #define CH1_SC0_CR_CADB_BUF_1_CID_WID                                ( 3)
  #define CH1_SC0_CR_CADB_BUF_1_CID_MSK                                (0x00000070)
  #define CH1_SC0_CR_CADB_BUF_1_CID_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_1_CID_MAX                                (7) // 0x00000007
  #define CH1_SC0_CR_CADB_BUF_1_CID_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_1_CID_HSH                                (0x4304D250)

  #define CH1_SC0_CR_CADB_BUF_1_ODT_OFF                                ( 7)
  #define CH1_SC0_CR_CADB_BUF_1_ODT_WID                                ( 4)
  #define CH1_SC0_CR_CADB_BUF_1_ODT_MSK                                (0x00000780)
  #define CH1_SC0_CR_CADB_BUF_1_ODT_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_1_ODT_MAX                                (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_BUF_1_ODT_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_1_ODT_HSH                                (0x4407D250)

  #define CH1_SC0_CR_CADB_BUF_1_CKE_OFF                                (11)
  #define CH1_SC0_CR_CADB_BUF_1_CKE_WID                                ( 4)
  #define CH1_SC0_CR_CADB_BUF_1_CKE_MSK                                (0x00007800)
  #define CH1_SC0_CR_CADB_BUF_1_CKE_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_1_CKE_MAX                                (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_BUF_1_CKE_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_1_CKE_HSH                                (0x440BD250)

  #define CH1_SC0_CR_CADB_BUF_1_USE_HALF_CA_OFF                        (15)
  #define CH1_SC0_CR_CADB_BUF_1_USE_HALF_CA_WID                        ( 1)
  #define CH1_SC0_CR_CADB_BUF_1_USE_HALF_CA_MSK                        (0x00008000)
  #define CH1_SC0_CR_CADB_BUF_1_USE_HALF_CA_MIN                        (0)
  #define CH1_SC0_CR_CADB_BUF_1_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH1_SC0_CR_CADB_BUF_1_USE_HALF_CA_DEF                        (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_1_USE_HALF_CA_HSH                        (0x410FD250)

  #define CH1_SC0_CR_CADB_BUF_1_VAL_OFF                                (16)
  #define CH1_SC0_CR_CADB_BUF_1_VAL_WID                                ( 1)
  #define CH1_SC0_CR_CADB_BUF_1_VAL_MSK                                (0x00010000)
  #define CH1_SC0_CR_CADB_BUF_1_VAL_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_1_VAL_MAX                                (1) // 0x00000001
  #define CH1_SC0_CR_CADB_BUF_1_VAL_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_1_VAL_HSH                                (0x4110D250)

  #define CH1_SC0_CR_CADB_BUF_1_PAR_OFF                                (17)
  #define CH1_SC0_CR_CADB_BUF_1_PAR_WID                                ( 1)
  #define CH1_SC0_CR_CADB_BUF_1_PAR_MSK                                (0x00020000)
  #define CH1_SC0_CR_CADB_BUF_1_PAR_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_1_PAR_MAX                                (1) // 0x00000001
  #define CH1_SC0_CR_CADB_BUF_1_PAR_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_1_PAR_HSH                                (0x4111D250)

  #define CH1_SC0_CR_CADB_BUF_1_CA_OFF                                 (18)
  #define CH1_SC0_CR_CADB_BUF_1_CA_WID                                 (24)
  #define CH1_SC0_CR_CADB_BUF_1_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH1_SC0_CR_CADB_BUF_1_CA_MIN                                 (0)
  #define CH1_SC0_CR_CADB_BUF_1_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH1_SC0_CR_CADB_BUF_1_CA_DEF                                 (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_1_CA_HSH                                 (0x5812D250)

#define CH1_SC0_CR_CADB_BUF_2_REG                                      (0x0000D258)

  #define CH1_SC0_CR_CADB_BUF_2_CS_OFF                                 ( 0)
  #define CH1_SC0_CR_CADB_BUF_2_CS_WID                                 ( 4)
  #define CH1_SC0_CR_CADB_BUF_2_CS_MSK                                 (0x0000000F)
  #define CH1_SC0_CR_CADB_BUF_2_CS_MIN                                 (0)
  #define CH1_SC0_CR_CADB_BUF_2_CS_MAX                                 (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_BUF_2_CS_DEF                                 (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_2_CS_HSH                                 (0x4400D258)

  #define CH1_SC0_CR_CADB_BUF_2_CID_OFF                                ( 4)
  #define CH1_SC0_CR_CADB_BUF_2_CID_WID                                ( 3)
  #define CH1_SC0_CR_CADB_BUF_2_CID_MSK                                (0x00000070)
  #define CH1_SC0_CR_CADB_BUF_2_CID_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_2_CID_MAX                                (7) // 0x00000007
  #define CH1_SC0_CR_CADB_BUF_2_CID_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_2_CID_HSH                                (0x4304D258)

  #define CH1_SC0_CR_CADB_BUF_2_ODT_OFF                                ( 7)
  #define CH1_SC0_CR_CADB_BUF_2_ODT_WID                                ( 4)
  #define CH1_SC0_CR_CADB_BUF_2_ODT_MSK                                (0x00000780)
  #define CH1_SC0_CR_CADB_BUF_2_ODT_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_2_ODT_MAX                                (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_BUF_2_ODT_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_2_ODT_HSH                                (0x4407D258)

  #define CH1_SC0_CR_CADB_BUF_2_CKE_OFF                                (11)
  #define CH1_SC0_CR_CADB_BUF_2_CKE_WID                                ( 4)
  #define CH1_SC0_CR_CADB_BUF_2_CKE_MSK                                (0x00007800)
  #define CH1_SC0_CR_CADB_BUF_2_CKE_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_2_CKE_MAX                                (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_BUF_2_CKE_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_2_CKE_HSH                                (0x440BD258)

  #define CH1_SC0_CR_CADB_BUF_2_USE_HALF_CA_OFF                        (15)
  #define CH1_SC0_CR_CADB_BUF_2_USE_HALF_CA_WID                        ( 1)
  #define CH1_SC0_CR_CADB_BUF_2_USE_HALF_CA_MSK                        (0x00008000)
  #define CH1_SC0_CR_CADB_BUF_2_USE_HALF_CA_MIN                        (0)
  #define CH1_SC0_CR_CADB_BUF_2_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH1_SC0_CR_CADB_BUF_2_USE_HALF_CA_DEF                        (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_2_USE_HALF_CA_HSH                        (0x410FD258)

  #define CH1_SC0_CR_CADB_BUF_2_VAL_OFF                                (16)
  #define CH1_SC0_CR_CADB_BUF_2_VAL_WID                                ( 1)
  #define CH1_SC0_CR_CADB_BUF_2_VAL_MSK                                (0x00010000)
  #define CH1_SC0_CR_CADB_BUF_2_VAL_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_2_VAL_MAX                                (1) // 0x00000001
  #define CH1_SC0_CR_CADB_BUF_2_VAL_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_2_VAL_HSH                                (0x4110D258)

  #define CH1_SC0_CR_CADB_BUF_2_PAR_OFF                                (17)
  #define CH1_SC0_CR_CADB_BUF_2_PAR_WID                                ( 1)
  #define CH1_SC0_CR_CADB_BUF_2_PAR_MSK                                (0x00020000)
  #define CH1_SC0_CR_CADB_BUF_2_PAR_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_2_PAR_MAX                                (1) // 0x00000001
  #define CH1_SC0_CR_CADB_BUF_2_PAR_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_2_PAR_HSH                                (0x4111D258)

  #define CH1_SC0_CR_CADB_BUF_2_CA_OFF                                 (18)
  #define CH1_SC0_CR_CADB_BUF_2_CA_WID                                 (24)
  #define CH1_SC0_CR_CADB_BUF_2_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH1_SC0_CR_CADB_BUF_2_CA_MIN                                 (0)
  #define CH1_SC0_CR_CADB_BUF_2_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH1_SC0_CR_CADB_BUF_2_CA_DEF                                 (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_2_CA_HSH                                 (0x5812D258)

#define CH1_SC0_CR_CADB_BUF_3_REG                                      (0x0000D260)

  #define CH1_SC0_CR_CADB_BUF_3_CS_OFF                                 ( 0)
  #define CH1_SC0_CR_CADB_BUF_3_CS_WID                                 ( 4)
  #define CH1_SC0_CR_CADB_BUF_3_CS_MSK                                 (0x0000000F)
  #define CH1_SC0_CR_CADB_BUF_3_CS_MIN                                 (0)
  #define CH1_SC0_CR_CADB_BUF_3_CS_MAX                                 (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_BUF_3_CS_DEF                                 (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_3_CS_HSH                                 (0x4400D260)

  #define CH1_SC0_CR_CADB_BUF_3_CID_OFF                                ( 4)
  #define CH1_SC0_CR_CADB_BUF_3_CID_WID                                ( 3)
  #define CH1_SC0_CR_CADB_BUF_3_CID_MSK                                (0x00000070)
  #define CH1_SC0_CR_CADB_BUF_3_CID_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_3_CID_MAX                                (7) // 0x00000007
  #define CH1_SC0_CR_CADB_BUF_3_CID_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_3_CID_HSH                                (0x4304D260)

  #define CH1_SC0_CR_CADB_BUF_3_ODT_OFF                                ( 7)
  #define CH1_SC0_CR_CADB_BUF_3_ODT_WID                                ( 4)
  #define CH1_SC0_CR_CADB_BUF_3_ODT_MSK                                (0x00000780)
  #define CH1_SC0_CR_CADB_BUF_3_ODT_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_3_ODT_MAX                                (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_BUF_3_ODT_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_3_ODT_HSH                                (0x4407D260)

  #define CH1_SC0_CR_CADB_BUF_3_CKE_OFF                                (11)
  #define CH1_SC0_CR_CADB_BUF_3_CKE_WID                                ( 4)
  #define CH1_SC0_CR_CADB_BUF_3_CKE_MSK                                (0x00007800)
  #define CH1_SC0_CR_CADB_BUF_3_CKE_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_3_CKE_MAX                                (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_BUF_3_CKE_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_3_CKE_HSH                                (0x440BD260)

  #define CH1_SC0_CR_CADB_BUF_3_USE_HALF_CA_OFF                        (15)
  #define CH1_SC0_CR_CADB_BUF_3_USE_HALF_CA_WID                        ( 1)
  #define CH1_SC0_CR_CADB_BUF_3_USE_HALF_CA_MSK                        (0x00008000)
  #define CH1_SC0_CR_CADB_BUF_3_USE_HALF_CA_MIN                        (0)
  #define CH1_SC0_CR_CADB_BUF_3_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH1_SC0_CR_CADB_BUF_3_USE_HALF_CA_DEF                        (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_3_USE_HALF_CA_HSH                        (0x410FD260)

  #define CH1_SC0_CR_CADB_BUF_3_VAL_OFF                                (16)
  #define CH1_SC0_CR_CADB_BUF_3_VAL_WID                                ( 1)
  #define CH1_SC0_CR_CADB_BUF_3_VAL_MSK                                (0x00010000)
  #define CH1_SC0_CR_CADB_BUF_3_VAL_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_3_VAL_MAX                                (1) // 0x00000001
  #define CH1_SC0_CR_CADB_BUF_3_VAL_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_3_VAL_HSH                                (0x4110D260)

  #define CH1_SC0_CR_CADB_BUF_3_PAR_OFF                                (17)
  #define CH1_SC0_CR_CADB_BUF_3_PAR_WID                                ( 1)
  #define CH1_SC0_CR_CADB_BUF_3_PAR_MSK                                (0x00020000)
  #define CH1_SC0_CR_CADB_BUF_3_PAR_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_3_PAR_MAX                                (1) // 0x00000001
  #define CH1_SC0_CR_CADB_BUF_3_PAR_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_3_PAR_HSH                                (0x4111D260)

  #define CH1_SC0_CR_CADB_BUF_3_CA_OFF                                 (18)
  #define CH1_SC0_CR_CADB_BUF_3_CA_WID                                 (24)
  #define CH1_SC0_CR_CADB_BUF_3_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH1_SC0_CR_CADB_BUF_3_CA_MIN                                 (0)
  #define CH1_SC0_CR_CADB_BUF_3_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH1_SC0_CR_CADB_BUF_3_CA_DEF                                 (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_3_CA_HSH                                 (0x5812D260)

#define CH1_SC0_CR_CADB_BUF_4_REG                                      (0x0000D268)

  #define CH1_SC0_CR_CADB_BUF_4_CS_OFF                                 ( 0)
  #define CH1_SC0_CR_CADB_BUF_4_CS_WID                                 ( 4)
  #define CH1_SC0_CR_CADB_BUF_4_CS_MSK                                 (0x0000000F)
  #define CH1_SC0_CR_CADB_BUF_4_CS_MIN                                 (0)
  #define CH1_SC0_CR_CADB_BUF_4_CS_MAX                                 (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_BUF_4_CS_DEF                                 (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_4_CS_HSH                                 (0x4400D268)

  #define CH1_SC0_CR_CADB_BUF_4_CID_OFF                                ( 4)
  #define CH1_SC0_CR_CADB_BUF_4_CID_WID                                ( 3)
  #define CH1_SC0_CR_CADB_BUF_4_CID_MSK                                (0x00000070)
  #define CH1_SC0_CR_CADB_BUF_4_CID_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_4_CID_MAX                                (7) // 0x00000007
  #define CH1_SC0_CR_CADB_BUF_4_CID_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_4_CID_HSH                                (0x4304D268)

  #define CH1_SC0_CR_CADB_BUF_4_ODT_OFF                                ( 7)
  #define CH1_SC0_CR_CADB_BUF_4_ODT_WID                                ( 4)
  #define CH1_SC0_CR_CADB_BUF_4_ODT_MSK                                (0x00000780)
  #define CH1_SC0_CR_CADB_BUF_4_ODT_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_4_ODT_MAX                                (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_BUF_4_ODT_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_4_ODT_HSH                                (0x4407D268)

  #define CH1_SC0_CR_CADB_BUF_4_CKE_OFF                                (11)
  #define CH1_SC0_CR_CADB_BUF_4_CKE_WID                                ( 4)
  #define CH1_SC0_CR_CADB_BUF_4_CKE_MSK                                (0x00007800)
  #define CH1_SC0_CR_CADB_BUF_4_CKE_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_4_CKE_MAX                                (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_BUF_4_CKE_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_4_CKE_HSH                                (0x440BD268)

  #define CH1_SC0_CR_CADB_BUF_4_USE_HALF_CA_OFF                        (15)
  #define CH1_SC0_CR_CADB_BUF_4_USE_HALF_CA_WID                        ( 1)
  #define CH1_SC0_CR_CADB_BUF_4_USE_HALF_CA_MSK                        (0x00008000)
  #define CH1_SC0_CR_CADB_BUF_4_USE_HALF_CA_MIN                        (0)
  #define CH1_SC0_CR_CADB_BUF_4_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH1_SC0_CR_CADB_BUF_4_USE_HALF_CA_DEF                        (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_4_USE_HALF_CA_HSH                        (0x410FD268)

  #define CH1_SC0_CR_CADB_BUF_4_VAL_OFF                                (16)
  #define CH1_SC0_CR_CADB_BUF_4_VAL_WID                                ( 1)
  #define CH1_SC0_CR_CADB_BUF_4_VAL_MSK                                (0x00010000)
  #define CH1_SC0_CR_CADB_BUF_4_VAL_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_4_VAL_MAX                                (1) // 0x00000001
  #define CH1_SC0_CR_CADB_BUF_4_VAL_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_4_VAL_HSH                                (0x4110D268)

  #define CH1_SC0_CR_CADB_BUF_4_PAR_OFF                                (17)
  #define CH1_SC0_CR_CADB_BUF_4_PAR_WID                                ( 1)
  #define CH1_SC0_CR_CADB_BUF_4_PAR_MSK                                (0x00020000)
  #define CH1_SC0_CR_CADB_BUF_4_PAR_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_4_PAR_MAX                                (1) // 0x00000001
  #define CH1_SC0_CR_CADB_BUF_4_PAR_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_4_PAR_HSH                                (0x4111D268)

  #define CH1_SC0_CR_CADB_BUF_4_CA_OFF                                 (18)
  #define CH1_SC0_CR_CADB_BUF_4_CA_WID                                 (24)
  #define CH1_SC0_CR_CADB_BUF_4_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH1_SC0_CR_CADB_BUF_4_CA_MIN                                 (0)
  #define CH1_SC0_CR_CADB_BUF_4_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH1_SC0_CR_CADB_BUF_4_CA_DEF                                 (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_4_CA_HSH                                 (0x5812D268)

#define CH1_SC0_CR_CADB_BUF_5_REG                                      (0x0000D270)

  #define CH1_SC0_CR_CADB_BUF_5_CS_OFF                                 ( 0)
  #define CH1_SC0_CR_CADB_BUF_5_CS_WID                                 ( 4)
  #define CH1_SC0_CR_CADB_BUF_5_CS_MSK                                 (0x0000000F)
  #define CH1_SC0_CR_CADB_BUF_5_CS_MIN                                 (0)
  #define CH1_SC0_CR_CADB_BUF_5_CS_MAX                                 (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_BUF_5_CS_DEF                                 (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_5_CS_HSH                                 (0x4400D270)

  #define CH1_SC0_CR_CADB_BUF_5_CID_OFF                                ( 4)
  #define CH1_SC0_CR_CADB_BUF_5_CID_WID                                ( 3)
  #define CH1_SC0_CR_CADB_BUF_5_CID_MSK                                (0x00000070)
  #define CH1_SC0_CR_CADB_BUF_5_CID_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_5_CID_MAX                                (7) // 0x00000007
  #define CH1_SC0_CR_CADB_BUF_5_CID_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_5_CID_HSH                                (0x4304D270)

  #define CH1_SC0_CR_CADB_BUF_5_ODT_OFF                                ( 7)
  #define CH1_SC0_CR_CADB_BUF_5_ODT_WID                                ( 4)
  #define CH1_SC0_CR_CADB_BUF_5_ODT_MSK                                (0x00000780)
  #define CH1_SC0_CR_CADB_BUF_5_ODT_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_5_ODT_MAX                                (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_BUF_5_ODT_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_5_ODT_HSH                                (0x4407D270)

  #define CH1_SC0_CR_CADB_BUF_5_CKE_OFF                                (11)
  #define CH1_SC0_CR_CADB_BUF_5_CKE_WID                                ( 4)
  #define CH1_SC0_CR_CADB_BUF_5_CKE_MSK                                (0x00007800)
  #define CH1_SC0_CR_CADB_BUF_5_CKE_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_5_CKE_MAX                                (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_BUF_5_CKE_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_5_CKE_HSH                                (0x440BD270)

  #define CH1_SC0_CR_CADB_BUF_5_USE_HALF_CA_OFF                        (15)
  #define CH1_SC0_CR_CADB_BUF_5_USE_HALF_CA_WID                        ( 1)
  #define CH1_SC0_CR_CADB_BUF_5_USE_HALF_CA_MSK                        (0x00008000)
  #define CH1_SC0_CR_CADB_BUF_5_USE_HALF_CA_MIN                        (0)
  #define CH1_SC0_CR_CADB_BUF_5_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH1_SC0_CR_CADB_BUF_5_USE_HALF_CA_DEF                        (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_5_USE_HALF_CA_HSH                        (0x410FD270)

  #define CH1_SC0_CR_CADB_BUF_5_VAL_OFF                                (16)
  #define CH1_SC0_CR_CADB_BUF_5_VAL_WID                                ( 1)
  #define CH1_SC0_CR_CADB_BUF_5_VAL_MSK                                (0x00010000)
  #define CH1_SC0_CR_CADB_BUF_5_VAL_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_5_VAL_MAX                                (1) // 0x00000001
  #define CH1_SC0_CR_CADB_BUF_5_VAL_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_5_VAL_HSH                                (0x4110D270)

  #define CH1_SC0_CR_CADB_BUF_5_PAR_OFF                                (17)
  #define CH1_SC0_CR_CADB_BUF_5_PAR_WID                                ( 1)
  #define CH1_SC0_CR_CADB_BUF_5_PAR_MSK                                (0x00020000)
  #define CH1_SC0_CR_CADB_BUF_5_PAR_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_5_PAR_MAX                                (1) // 0x00000001
  #define CH1_SC0_CR_CADB_BUF_5_PAR_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_5_PAR_HSH                                (0x4111D270)

  #define CH1_SC0_CR_CADB_BUF_5_CA_OFF                                 (18)
  #define CH1_SC0_CR_CADB_BUF_5_CA_WID                                 (24)
  #define CH1_SC0_CR_CADB_BUF_5_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH1_SC0_CR_CADB_BUF_5_CA_MIN                                 (0)
  #define CH1_SC0_CR_CADB_BUF_5_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH1_SC0_CR_CADB_BUF_5_CA_DEF                                 (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_5_CA_HSH                                 (0x5812D270)

#define CH1_SC0_CR_CADB_BUF_6_REG                                      (0x0000D278)

  #define CH1_SC0_CR_CADB_BUF_6_CS_OFF                                 ( 0)
  #define CH1_SC0_CR_CADB_BUF_6_CS_WID                                 ( 4)
  #define CH1_SC0_CR_CADB_BUF_6_CS_MSK                                 (0x0000000F)
  #define CH1_SC0_CR_CADB_BUF_6_CS_MIN                                 (0)
  #define CH1_SC0_CR_CADB_BUF_6_CS_MAX                                 (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_BUF_6_CS_DEF                                 (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_6_CS_HSH                                 (0x4400D278)

  #define CH1_SC0_CR_CADB_BUF_6_CID_OFF                                ( 4)
  #define CH1_SC0_CR_CADB_BUF_6_CID_WID                                ( 3)
  #define CH1_SC0_CR_CADB_BUF_6_CID_MSK                                (0x00000070)
  #define CH1_SC0_CR_CADB_BUF_6_CID_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_6_CID_MAX                                (7) // 0x00000007
  #define CH1_SC0_CR_CADB_BUF_6_CID_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_6_CID_HSH                                (0x4304D278)

  #define CH1_SC0_CR_CADB_BUF_6_ODT_OFF                                ( 7)
  #define CH1_SC0_CR_CADB_BUF_6_ODT_WID                                ( 4)
  #define CH1_SC0_CR_CADB_BUF_6_ODT_MSK                                (0x00000780)
  #define CH1_SC0_CR_CADB_BUF_6_ODT_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_6_ODT_MAX                                (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_BUF_6_ODT_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_6_ODT_HSH                                (0x4407D278)

  #define CH1_SC0_CR_CADB_BUF_6_CKE_OFF                                (11)
  #define CH1_SC0_CR_CADB_BUF_6_CKE_WID                                ( 4)
  #define CH1_SC0_CR_CADB_BUF_6_CKE_MSK                                (0x00007800)
  #define CH1_SC0_CR_CADB_BUF_6_CKE_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_6_CKE_MAX                                (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_BUF_6_CKE_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_6_CKE_HSH                                (0x440BD278)

  #define CH1_SC0_CR_CADB_BUF_6_USE_HALF_CA_OFF                        (15)
  #define CH1_SC0_CR_CADB_BUF_6_USE_HALF_CA_WID                        ( 1)
  #define CH1_SC0_CR_CADB_BUF_6_USE_HALF_CA_MSK                        (0x00008000)
  #define CH1_SC0_CR_CADB_BUF_6_USE_HALF_CA_MIN                        (0)
  #define CH1_SC0_CR_CADB_BUF_6_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH1_SC0_CR_CADB_BUF_6_USE_HALF_CA_DEF                        (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_6_USE_HALF_CA_HSH                        (0x410FD278)

  #define CH1_SC0_CR_CADB_BUF_6_VAL_OFF                                (16)
  #define CH1_SC0_CR_CADB_BUF_6_VAL_WID                                ( 1)
  #define CH1_SC0_CR_CADB_BUF_6_VAL_MSK                                (0x00010000)
  #define CH1_SC0_CR_CADB_BUF_6_VAL_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_6_VAL_MAX                                (1) // 0x00000001
  #define CH1_SC0_CR_CADB_BUF_6_VAL_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_6_VAL_HSH                                (0x4110D278)

  #define CH1_SC0_CR_CADB_BUF_6_PAR_OFF                                (17)
  #define CH1_SC0_CR_CADB_BUF_6_PAR_WID                                ( 1)
  #define CH1_SC0_CR_CADB_BUF_6_PAR_MSK                                (0x00020000)
  #define CH1_SC0_CR_CADB_BUF_6_PAR_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_6_PAR_MAX                                (1) // 0x00000001
  #define CH1_SC0_CR_CADB_BUF_6_PAR_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_6_PAR_HSH                                (0x4111D278)

  #define CH1_SC0_CR_CADB_BUF_6_CA_OFF                                 (18)
  #define CH1_SC0_CR_CADB_BUF_6_CA_WID                                 (24)
  #define CH1_SC0_CR_CADB_BUF_6_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH1_SC0_CR_CADB_BUF_6_CA_MIN                                 (0)
  #define CH1_SC0_CR_CADB_BUF_6_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH1_SC0_CR_CADB_BUF_6_CA_DEF                                 (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_6_CA_HSH                                 (0x5812D278)

#define CH1_SC0_CR_CADB_BUF_7_REG                                      (0x0000D280)

  #define CH1_SC0_CR_CADB_BUF_7_CS_OFF                                 ( 0)
  #define CH1_SC0_CR_CADB_BUF_7_CS_WID                                 ( 4)
  #define CH1_SC0_CR_CADB_BUF_7_CS_MSK                                 (0x0000000F)
  #define CH1_SC0_CR_CADB_BUF_7_CS_MIN                                 (0)
  #define CH1_SC0_CR_CADB_BUF_7_CS_MAX                                 (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_BUF_7_CS_DEF                                 (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_7_CS_HSH                                 (0x4400D280)

  #define CH1_SC0_CR_CADB_BUF_7_CID_OFF                                ( 4)
  #define CH1_SC0_CR_CADB_BUF_7_CID_WID                                ( 3)
  #define CH1_SC0_CR_CADB_BUF_7_CID_MSK                                (0x00000070)
  #define CH1_SC0_CR_CADB_BUF_7_CID_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_7_CID_MAX                                (7) // 0x00000007
  #define CH1_SC0_CR_CADB_BUF_7_CID_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_7_CID_HSH                                (0x4304D280)

  #define CH1_SC0_CR_CADB_BUF_7_ODT_OFF                                ( 7)
  #define CH1_SC0_CR_CADB_BUF_7_ODT_WID                                ( 4)
  #define CH1_SC0_CR_CADB_BUF_7_ODT_MSK                                (0x00000780)
  #define CH1_SC0_CR_CADB_BUF_7_ODT_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_7_ODT_MAX                                (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_BUF_7_ODT_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_7_ODT_HSH                                (0x4407D280)

  #define CH1_SC0_CR_CADB_BUF_7_CKE_OFF                                (11)
  #define CH1_SC0_CR_CADB_BUF_7_CKE_WID                                ( 4)
  #define CH1_SC0_CR_CADB_BUF_7_CKE_MSK                                (0x00007800)
  #define CH1_SC0_CR_CADB_BUF_7_CKE_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_7_CKE_MAX                                (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_BUF_7_CKE_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_7_CKE_HSH                                (0x440BD280)

  #define CH1_SC0_CR_CADB_BUF_7_USE_HALF_CA_OFF                        (15)
  #define CH1_SC0_CR_CADB_BUF_7_USE_HALF_CA_WID                        ( 1)
  #define CH1_SC0_CR_CADB_BUF_7_USE_HALF_CA_MSK                        (0x00008000)
  #define CH1_SC0_CR_CADB_BUF_7_USE_HALF_CA_MIN                        (0)
  #define CH1_SC0_CR_CADB_BUF_7_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH1_SC0_CR_CADB_BUF_7_USE_HALF_CA_DEF                        (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_7_USE_HALF_CA_HSH                        (0x410FD280)

  #define CH1_SC0_CR_CADB_BUF_7_VAL_OFF                                (16)
  #define CH1_SC0_CR_CADB_BUF_7_VAL_WID                                ( 1)
  #define CH1_SC0_CR_CADB_BUF_7_VAL_MSK                                (0x00010000)
  #define CH1_SC0_CR_CADB_BUF_7_VAL_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_7_VAL_MAX                                (1) // 0x00000001
  #define CH1_SC0_CR_CADB_BUF_7_VAL_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_7_VAL_HSH                                (0x4110D280)

  #define CH1_SC0_CR_CADB_BUF_7_PAR_OFF                                (17)
  #define CH1_SC0_CR_CADB_BUF_7_PAR_WID                                ( 1)
  #define CH1_SC0_CR_CADB_BUF_7_PAR_MSK                                (0x00020000)
  #define CH1_SC0_CR_CADB_BUF_7_PAR_MIN                                (0)
  #define CH1_SC0_CR_CADB_BUF_7_PAR_MAX                                (1) // 0x00000001
  #define CH1_SC0_CR_CADB_BUF_7_PAR_DEF                                (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_7_PAR_HSH                                (0x4111D280)

  #define CH1_SC0_CR_CADB_BUF_7_CA_OFF                                 (18)
  #define CH1_SC0_CR_CADB_BUF_7_CA_WID                                 (24)
  #define CH1_SC0_CR_CADB_BUF_7_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH1_SC0_CR_CADB_BUF_7_CA_MIN                                 (0)
  #define CH1_SC0_CR_CADB_BUF_7_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH1_SC0_CR_CADB_BUF_7_CA_DEF                                 (0x00000000)
  #define CH1_SC0_CR_CADB_BUF_7_CA_HSH                                 (0x5812D280)

#define CH1_SC0_CR_CADB_AO_MRSCFG_REG                                  (0x0000D288)

  #define CH1_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_OFF                  ( 0)
  #define CH1_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_WID                  ( 1)
  #define CH1_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_MSK                  (0x00000001)
  #define CH1_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_MIN                  (0)
  #define CH1_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_MAX                  (1) // 0x00000001
  #define CH1_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_DEF                  (0x00000000)
  #define CH1_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_HSH                  (0x0100D288)

  #define CH1_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_OFF                        ( 1)
  #define CH1_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_WID                        ( 4)
  #define CH1_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_MSK                        (0x0000001E)
  #define CH1_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_MIN                        (0)
  #define CH1_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_MAX                        (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_DEF                        (0x00000000)
  #define CH1_SC0_CR_CADB_AO_MRSCFG_MRS_GAP_HSH                        (0x0401D288)

  #define CH1_SC0_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_OFF                 ( 8)
  #define CH1_SC0_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_WID                 (16)
  #define CH1_SC0_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_MSK                 (0x00FFFF00)
  #define CH1_SC0_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_MIN                 (0)
  #define CH1_SC0_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_MAX                 (65535) // 0x0000FFFF
  #define CH1_SC0_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_DEF                 (0x00000000)
  #define CH1_SC0_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_HSH                 (0x1008D288)

#define CH1_SC0_CR_CADB_SELCFG_REG                                     (0x0000D290)

  #define CH1_SC0_CR_CADB_SELCFG_WR_SELECT_ENABLE_OFF                  ( 0)
  #define CH1_SC0_CR_CADB_SELCFG_WR_SELECT_ENABLE_WID                  ( 3)
  #define CH1_SC0_CR_CADB_SELCFG_WR_SELECT_ENABLE_MSK                  (0x00000007)
  #define CH1_SC0_CR_CADB_SELCFG_WR_SELECT_ENABLE_MIN                  (0)
  #define CH1_SC0_CR_CADB_SELCFG_WR_SELECT_ENABLE_MAX                  (7) // 0x00000007
  #define CH1_SC0_CR_CADB_SELCFG_WR_SELECT_ENABLE_DEF                  (0x00000000)
  #define CH1_SC0_CR_CADB_SELCFG_WR_SELECT_ENABLE_HSH                  (0x0300D290)

  #define CH1_SC0_CR_CADB_SELCFG_RD_SELECT_ENABLE_OFF                  ( 8)
  #define CH1_SC0_CR_CADB_SELCFG_RD_SELECT_ENABLE_WID                  ( 3)
  #define CH1_SC0_CR_CADB_SELCFG_RD_SELECT_ENABLE_MSK                  (0x00000700)
  #define CH1_SC0_CR_CADB_SELCFG_RD_SELECT_ENABLE_MIN                  (0)
  #define CH1_SC0_CR_CADB_SELCFG_RD_SELECT_ENABLE_MAX                  (7) // 0x00000007
  #define CH1_SC0_CR_CADB_SELCFG_RD_SELECT_ENABLE_DEF                  (0x00000000)
  #define CH1_SC0_CR_CADB_SELCFG_RD_SELECT_ENABLE_HSH                  (0x0308D290)

  #define CH1_SC0_CR_CADB_SELCFG_ACT_SELECT_ENABLE_OFF                 (16)
  #define CH1_SC0_CR_CADB_SELCFG_ACT_SELECT_ENABLE_WID                 ( 3)
  #define CH1_SC0_CR_CADB_SELCFG_ACT_SELECT_ENABLE_MSK                 (0x00070000)
  #define CH1_SC0_CR_CADB_SELCFG_ACT_SELECT_ENABLE_MIN                 (0)
  #define CH1_SC0_CR_CADB_SELCFG_ACT_SELECT_ENABLE_MAX                 (7) // 0x00000007
  #define CH1_SC0_CR_CADB_SELCFG_ACT_SELECT_ENABLE_DEF                 (0x00000000)
  #define CH1_SC0_CR_CADB_SELCFG_ACT_SELECT_ENABLE_HSH                 (0x0310D290)

  #define CH1_SC0_CR_CADB_SELCFG_PRE_SELECT_ENABLE_OFF                 (24)
  #define CH1_SC0_CR_CADB_SELCFG_PRE_SELECT_ENABLE_WID                 ( 3)
  #define CH1_SC0_CR_CADB_SELCFG_PRE_SELECT_ENABLE_MSK                 (0x07000000)
  #define CH1_SC0_CR_CADB_SELCFG_PRE_SELECT_ENABLE_MIN                 (0)
  #define CH1_SC0_CR_CADB_SELCFG_PRE_SELECT_ENABLE_MAX                 (7) // 0x00000007
  #define CH1_SC0_CR_CADB_SELCFG_PRE_SELECT_ENABLE_DEF                 (0x00000000)
  #define CH1_SC0_CR_CADB_SELCFG_PRE_SELECT_ENABLE_HSH                 (0x0318D290)

  #define CH1_SC0_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_OFF               (28)
  #define CH1_SC0_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_WID               ( 1)
  #define CH1_SC0_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_MSK               (0x10000000)
  #define CH1_SC0_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_MIN               (0)
  #define CH1_SC0_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_MAX               (1) // 0x00000001
  #define CH1_SC0_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_DEF               (0x00000001)
  #define CH1_SC0_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_HSH               (0x011CD290)

#define CH1_SC0_CR_CADB_MRSCFG_REG                                     (0x0000D298)

  #define CH1_SC0_CR_CADB_MRSCFG_CS_CLOCKS_OFF                         ( 0)
  #define CH1_SC0_CR_CADB_MRSCFG_CS_CLOCKS_WID                         ( 3)
  #define CH1_SC0_CR_CADB_MRSCFG_CS_CLOCKS_MSK                         (0x00000007)
  #define CH1_SC0_CR_CADB_MRSCFG_CS_CLOCKS_MIN                         (0)
  #define CH1_SC0_CR_CADB_MRSCFG_CS_CLOCKS_MAX                         (7) // 0x00000007
  #define CH1_SC0_CR_CADB_MRSCFG_CS_CLOCKS_DEF                         (0x00000000)
  #define CH1_SC0_CR_CADB_MRSCFG_CS_CLOCKS_HSH                         (0x4300D298)

  #define CH1_SC0_CR_CADB_MRSCFG_DSEL_CLOCKS_OFF                       ( 3)
  #define CH1_SC0_CR_CADB_MRSCFG_DSEL_CLOCKS_WID                       ( 4)
  #define CH1_SC0_CR_CADB_MRSCFG_DSEL_CLOCKS_MSK                       (0x00000078)
  #define CH1_SC0_CR_CADB_MRSCFG_DSEL_CLOCKS_MIN                       (0)
  #define CH1_SC0_CR_CADB_MRSCFG_DSEL_CLOCKS_MAX                       (15) // 0x0000000F
  #define CH1_SC0_CR_CADB_MRSCFG_DSEL_CLOCKS_DEF                       (0x00000000)
  #define CH1_SC0_CR_CADB_MRSCFG_DSEL_CLOCKS_HSH                       (0x4403D298)

  #define CH1_SC0_CR_CADB_MRSCFG_SETUP_CLOCKS_OFF                      ( 8)
  #define CH1_SC0_CR_CADB_MRSCFG_SETUP_CLOCKS_WID                      ( 3)
  #define CH1_SC0_CR_CADB_MRSCFG_SETUP_CLOCKS_MSK                      (0x00000700)
  #define CH1_SC0_CR_CADB_MRSCFG_SETUP_CLOCKS_MIN                      (0)
  #define CH1_SC0_CR_CADB_MRSCFG_SETUP_CLOCKS_MAX                      (7) // 0x00000007
  #define CH1_SC0_CR_CADB_MRSCFG_SETUP_CLOCKS_DEF                      (0x00000000)
  #define CH1_SC0_CR_CADB_MRSCFG_SETUP_CLOCKS_HSH                      (0x4308D298)

  #define CH1_SC0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_OFF                (11)
  #define CH1_SC0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_WID                ( 1)
  #define CH1_SC0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_MSK                (0x00000800)
  #define CH1_SC0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_MIN                (0)
  #define CH1_SC0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_MAX                (1) // 0x00000001
  #define CH1_SC0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_DEF                (0x00000000)
  #define CH1_SC0_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_HSH                (0x410BD298)

  #define CH1_SC0_CR_CADB_MRSCFG_MRS_START_PTR_OFF                     (12)
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_START_PTR_WID                     ( 3)
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_START_PTR_MSK                     (0x00007000)
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_START_PTR_MIN                     (0)
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_START_PTR_MAX                     (7) // 0x00000007
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_START_PTR_DEF                     (0x00000000)
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_START_PTR_HSH                     (0x430CD298)

  #define CH1_SC0_CR_CADB_MRSCFG_MRS_END_PTR_OFF                       (16)
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_END_PTR_WID                       ( 3)
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_END_PTR_MSK                       (0x00070000)
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_END_PTR_MIN                       (0)
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_END_PTR_MAX                       (7) // 0x00000007
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_END_PTR_DEF                       (0x00000000)
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_END_PTR_HSH                       (0x4310D298)

  #define CH1_SC0_CR_CADB_MRSCFG_MRS_GOTO_PTR_OFF                      (19)
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_GOTO_PTR_WID                      ( 3)
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_GOTO_PTR_MSK                      (0x00380000)
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_GOTO_PTR_MIN                      (0)
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_GOTO_PTR_MAX                      (7) // 0x00000007
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_GOTO_PTR_DEF                      (0x00000000)
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_GOTO_PTR_HSH                      (0x4313D298)

  #define CH1_SC0_CR_CADB_MRSCFG_MRS_CS_MODE_OFF                       (22)
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_CS_MODE_WID                       ( 2)
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_CS_MODE_MSK                       (0x00C00000)
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_CS_MODE_MIN                       (0)
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_CS_MODE_MAX                       (3) // 0x00000003
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_CS_MODE_DEF                       (0x00000000)
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_CS_MODE_HSH                       (0x4216D298)

  #define CH1_SC0_CR_CADB_MRSCFG_MRS_DELAY_CNT_OFF                     (24)
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_DELAY_CNT_WID                     (16)
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_DELAY_CNT_MSK                     (0x000000FFFF000000ULL)
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_DELAY_CNT_MIN                     (0)
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_DELAY_CNT_MAX                     (65535) // 0x0000FFFF
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_DELAY_CNT_DEF                     (0x00000000)
  #define CH1_SC0_CR_CADB_MRSCFG_MRS_DELAY_CNT_HSH                     (0x5018D298)

#define CH1_SC1_CR_CADB_ACCESS_CONTROL_POLICY_REG                      (0x0000D300)

  #define CH1_SC1_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_OFF     ( 0)
  #define CH1_SC1_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_WID     (64)
  #define CH1_SC1_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_MSK     (0xFFFFFFFFFFFFFFFFULL)
  #define CH1_SC1_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_MIN     (0)
  #define CH1_SC1_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_MAX     (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define CH1_SC1_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_DEF     (0x40001000208)
  #define CH1_SC1_CR_CADB_ACCESS_CONTROL_POLICY_Control_Policy_HSH     (0x4000D300)

#define CH1_SC1_CR_CADB_ACCESS_READ_POLICY_REG                         (0x0000D308)

  #define CH1_SC1_CR_CADB_ACCESS_READ_POLICY_Read_Policy_OFF           ( 0)
  #define CH1_SC1_CR_CADB_ACCESS_READ_POLICY_Read_Policy_WID           (64)
  #define CH1_SC1_CR_CADB_ACCESS_READ_POLICY_Read_Policy_MSK           (0xFFFFFFFFFFFFFFFFULL)
  #define CH1_SC1_CR_CADB_ACCESS_READ_POLICY_Read_Policy_MIN           (0)
  #define CH1_SC1_CR_CADB_ACCESS_READ_POLICY_Read_Policy_MAX           (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define CH1_SC1_CR_CADB_ACCESS_READ_POLICY_Read_Policy_DEF           (0xFFFFFFFFFFFFFFFF)
  #define CH1_SC1_CR_CADB_ACCESS_READ_POLICY_Read_Policy_HSH           (0x4000D308)

#define CH1_SC1_CR_CADB_ACCESS_WRITE_POLICY_REG                        (0x0000D310)

  #define CH1_SC1_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_OFF         ( 0)
  #define CH1_SC1_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_WID         (64)
  #define CH1_SC1_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_MSK         (0xFFFFFFFFFFFFFFFFULL)
  #define CH1_SC1_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_MIN         (0)
  #define CH1_SC1_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_MAX         (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define CH1_SC1_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_DEF         (0x4000100021A)
  #define CH1_SC1_CR_CADB_ACCESS_WRITE_POLICY_Write_Policy_HSH         (0x4000D310)

#define CH1_SC1_CR_CADB_CTL_REG                                        (0x0000D320)

  #define CH1_SC1_CR_CADB_CTL_START_TEST_OFF                           ( 0)
  #define CH1_SC1_CR_CADB_CTL_START_TEST_WID                           ( 1)
  #define CH1_SC1_CR_CADB_CTL_START_TEST_MSK                           (0x00000001)
  #define CH1_SC1_CR_CADB_CTL_START_TEST_MIN                           (0)
  #define CH1_SC1_CR_CADB_CTL_START_TEST_MAX                           (1) // 0x00000001
  #define CH1_SC1_CR_CADB_CTL_START_TEST_DEF                           (0x00000000)
  #define CH1_SC1_CR_CADB_CTL_START_TEST_HSH                           (0x0100D320)

  #define CH1_SC1_CR_CADB_CTL_STOP_TEST_OFF                            ( 1)
  #define CH1_SC1_CR_CADB_CTL_STOP_TEST_WID                            ( 1)
  #define CH1_SC1_CR_CADB_CTL_STOP_TEST_MSK                            (0x00000002)
  #define CH1_SC1_CR_CADB_CTL_STOP_TEST_MIN                            (0)
  #define CH1_SC1_CR_CADB_CTL_STOP_TEST_MAX                            (1) // 0x00000001
  #define CH1_SC1_CR_CADB_CTL_STOP_TEST_DEF                            (0x00000000)
  #define CH1_SC1_CR_CADB_CTL_STOP_TEST_HSH                            (0x0101D320)

#define CH1_SC1_CR_CADB_CFG_REG                                        (0x0000D324)

  #define CH1_SC1_CR_CADB_CFG_CMD_DESELECT_START_OFF                   ( 0)
  #define CH1_SC1_CR_CADB_CFG_CMD_DESELECT_START_WID                   ( 4)
  #define CH1_SC1_CR_CADB_CFG_CMD_DESELECT_START_MSK                   (0x0000000F)
  #define CH1_SC1_CR_CADB_CFG_CMD_DESELECT_START_MIN                   (0)
  #define CH1_SC1_CR_CADB_CFG_CMD_DESELECT_START_MAX                   (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_CFG_CMD_DESELECT_START_DEF                   (0x00000000)
  #define CH1_SC1_CR_CADB_CFG_CMD_DESELECT_START_HSH                   (0x0400D324)

  #define CH1_SC1_CR_CADB_CFG_CMD_DESELECT_STOP_OFF                    ( 4)
  #define CH1_SC1_CR_CADB_CFG_CMD_DESELECT_STOP_WID                    ( 4)
  #define CH1_SC1_CR_CADB_CFG_CMD_DESELECT_STOP_MSK                    (0x000000F0)
  #define CH1_SC1_CR_CADB_CFG_CMD_DESELECT_STOP_MIN                    (0)
  #define CH1_SC1_CR_CADB_CFG_CMD_DESELECT_STOP_MAX                    (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_CFG_CMD_DESELECT_STOP_DEF                    (0x00000000)
  #define CH1_SC1_CR_CADB_CFG_CMD_DESELECT_STOP_HSH                    (0x0404D324)

  #define CH1_SC1_CR_CADB_CFG_LANE_DESELECT_EN_OFF                     ( 8)
  #define CH1_SC1_CR_CADB_CFG_LANE_DESELECT_EN_WID                     ( 3)
  #define CH1_SC1_CR_CADB_CFG_LANE_DESELECT_EN_MSK                     (0x00000700)
  #define CH1_SC1_CR_CADB_CFG_LANE_DESELECT_EN_MIN                     (0)
  #define CH1_SC1_CR_CADB_CFG_LANE_DESELECT_EN_MAX                     (7) // 0x00000007
  #define CH1_SC1_CR_CADB_CFG_LANE_DESELECT_EN_DEF                     (0x00000000)
  #define CH1_SC1_CR_CADB_CFG_LANE_DESELECT_EN_HSH                     (0x0308D324)

  #define CH1_SC1_CR_CADB_CFG_INITIAL_DSEL_EN_OFF                      (11)
  #define CH1_SC1_CR_CADB_CFG_INITIAL_DSEL_EN_WID                      ( 1)
  #define CH1_SC1_CR_CADB_CFG_INITIAL_DSEL_EN_MSK                      (0x00000800)
  #define CH1_SC1_CR_CADB_CFG_INITIAL_DSEL_EN_MIN                      (0)
  #define CH1_SC1_CR_CADB_CFG_INITIAL_DSEL_EN_MAX                      (1) // 0x00000001
  #define CH1_SC1_CR_CADB_CFG_INITIAL_DSEL_EN_DEF                      (0x00000001)
  #define CH1_SC1_CR_CADB_CFG_INITIAL_DSEL_EN_HSH                      (0x010BD324)

  #define CH1_SC1_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_OFF                 (12)
  #define CH1_SC1_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_WID                 ( 1)
  #define CH1_SC1_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_MSK                 (0x00001000)
  #define CH1_SC1_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_MIN                 (0)
  #define CH1_SC1_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_MAX                 (1) // 0x00000001
  #define CH1_SC1_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_DEF                 (0x00000001)
  #define CH1_SC1_CR_CADB_CFG_INITIAL_DSEL_SSEQ_EN_HSH                 (0x010CD324)

  #define CH1_SC1_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_OFF              (13)
  #define CH1_SC1_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_WID              ( 3)
  #define CH1_SC1_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_MSK              (0x0000E000)
  #define CH1_SC1_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_MIN              (0)
  #define CH1_SC1_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_MAX              (7) // 0x00000007
  #define CH1_SC1_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_DEF              (0x00000000)
  #define CH1_SC1_CR_CADB_CFG_CADB_DSEL_THROTTLE_MODE_HSH              (0x030DD324)

  #define CH1_SC1_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_OFF               (16)
  #define CH1_SC1_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_WID               ( 3)
  #define CH1_SC1_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_MSK               (0x00070000)
  #define CH1_SC1_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_MIN               (0)
  #define CH1_SC1_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_MAX               (7) // 0x00000007
  #define CH1_SC1_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_DEF               (0x00000000)
  #define CH1_SC1_CR_CADB_CFG_CADB_SEL_THROTTLE_MODE_HSH               (0x0310D324)

  #define CH1_SC1_CR_CADB_CFG_CADB_TO_CPGC_BIND_OFF                    (24)
  #define CH1_SC1_CR_CADB_CFG_CADB_TO_CPGC_BIND_WID                    ( 1)
  #define CH1_SC1_CR_CADB_CFG_CADB_TO_CPGC_BIND_MSK                    (0x01000000)
  #define CH1_SC1_CR_CADB_CFG_CADB_TO_CPGC_BIND_MIN                    (0)
  #define CH1_SC1_CR_CADB_CFG_CADB_TO_CPGC_BIND_MAX                    (1) // 0x00000001
  #define CH1_SC1_CR_CADB_CFG_CADB_TO_CPGC_BIND_DEF                    (0x00000000)
  #define CH1_SC1_CR_CADB_CFG_CADB_TO_CPGC_BIND_HSH                    (0x0118D324)

  #define CH1_SC1_CR_CADB_CFG_GLOBAL_START_BIND_OFF                    (25)
  #define CH1_SC1_CR_CADB_CFG_GLOBAL_START_BIND_WID                    ( 1)
  #define CH1_SC1_CR_CADB_CFG_GLOBAL_START_BIND_MSK                    (0x02000000)
  #define CH1_SC1_CR_CADB_CFG_GLOBAL_START_BIND_MIN                    (0)
  #define CH1_SC1_CR_CADB_CFG_GLOBAL_START_BIND_MAX                    (1) // 0x00000001
  #define CH1_SC1_CR_CADB_CFG_GLOBAL_START_BIND_DEF                    (0x00000000)
  #define CH1_SC1_CR_CADB_CFG_GLOBAL_START_BIND_HSH                    (0x0119D324)

  #define CH1_SC1_CR_CADB_CFG_GLOBAL_STOP_BIND_OFF                     (26)
  #define CH1_SC1_CR_CADB_CFG_GLOBAL_STOP_BIND_WID                     ( 1)
  #define CH1_SC1_CR_CADB_CFG_GLOBAL_STOP_BIND_MSK                     (0x04000000)
  #define CH1_SC1_CR_CADB_CFG_GLOBAL_STOP_BIND_MIN                     (0)
  #define CH1_SC1_CR_CADB_CFG_GLOBAL_STOP_BIND_MAX                     (1) // 0x00000001
  #define CH1_SC1_CR_CADB_CFG_GLOBAL_STOP_BIND_DEF                     (0x00000000)
  #define CH1_SC1_CR_CADB_CFG_GLOBAL_STOP_BIND_HSH                     (0x011AD324)

  #define CH1_SC1_CR_CADB_CFG_CADB_MODE_OFF                            (29)
  #define CH1_SC1_CR_CADB_CFG_CADB_MODE_WID                            ( 3)
  #define CH1_SC1_CR_CADB_CFG_CADB_MODE_MSK                            (0xE0000000)
  #define CH1_SC1_CR_CADB_CFG_CADB_MODE_MIN                            (0)
  #define CH1_SC1_CR_CADB_CFG_CADB_MODE_MAX                            (7) // 0x00000007
  #define CH1_SC1_CR_CADB_CFG_CADB_MODE_DEF                            (0x00000000)
  #define CH1_SC1_CR_CADB_CFG_CADB_MODE_HSH                            (0x031DD324)

#define CH1_SC1_CR_CADB_DLY_REG                                        (0x0000D328)

  #define CH1_SC1_CR_CADB_DLY_START_DELAY_OFF                          ( 0)
  #define CH1_SC1_CR_CADB_DLY_START_DELAY_WID                          (10)
  #define CH1_SC1_CR_CADB_DLY_START_DELAY_MSK                          (0x000003FF)
  #define CH1_SC1_CR_CADB_DLY_START_DELAY_MIN                          (0)
  #define CH1_SC1_CR_CADB_DLY_START_DELAY_MAX                          (1023) // 0x000003FF
  #define CH1_SC1_CR_CADB_DLY_START_DELAY_DEF                          (0x00000000)
  #define CH1_SC1_CR_CADB_DLY_START_DELAY_HSH                          (0x0A00D328)

  #define CH1_SC1_CR_CADB_DLY_STOP_DELAY_OFF                           (16)
  #define CH1_SC1_CR_CADB_DLY_STOP_DELAY_WID                           (10)
  #define CH1_SC1_CR_CADB_DLY_STOP_DELAY_MSK                           (0x03FF0000)
  #define CH1_SC1_CR_CADB_DLY_STOP_DELAY_MIN                           (0)
  #define CH1_SC1_CR_CADB_DLY_STOP_DELAY_MAX                           (1023) // 0x000003FF
  #define CH1_SC1_CR_CADB_DLY_STOP_DELAY_DEF                           (0x00000000)
  #define CH1_SC1_CR_CADB_DLY_STOP_DELAY_HSH                           (0x0A10D328)

#define CH1_SC1_CR_CADB_STATUS_REG                                     (0x0000D32C)

  #define CH1_SC1_CR_CADB_STATUS_MRS_CURR_PTR_OFF                      (21)
  #define CH1_SC1_CR_CADB_STATUS_MRS_CURR_PTR_WID                      ( 3)
  #define CH1_SC1_CR_CADB_STATUS_MRS_CURR_PTR_MSK                      (0x00E00000)
  #define CH1_SC1_CR_CADB_STATUS_MRS_CURR_PTR_MIN                      (0)
  #define CH1_SC1_CR_CADB_STATUS_MRS_CURR_PTR_MAX                      (7) // 0x00000007
  #define CH1_SC1_CR_CADB_STATUS_MRS_CURR_PTR_DEF                      (0x00000000)
  #define CH1_SC1_CR_CADB_STATUS_MRS_CURR_PTR_HSH                      (0x0315D32C)

  #define CH1_SC1_CR_CADB_STATUS_TEST_ABORTED_OFF                      (24)
  #define CH1_SC1_CR_CADB_STATUS_TEST_ABORTED_WID                      ( 1)
  #define CH1_SC1_CR_CADB_STATUS_TEST_ABORTED_MSK                      (0x01000000)
  #define CH1_SC1_CR_CADB_STATUS_TEST_ABORTED_MIN                      (0)
  #define CH1_SC1_CR_CADB_STATUS_TEST_ABORTED_MAX                      (1) // 0x00000001
  #define CH1_SC1_CR_CADB_STATUS_TEST_ABORTED_DEF                      (0x00000000)
  #define CH1_SC1_CR_CADB_STATUS_TEST_ABORTED_HSH                      (0x0118D32C)

  #define CH1_SC1_CR_CADB_STATUS_ALGO_DONE_OFF                         (28)
  #define CH1_SC1_CR_CADB_STATUS_ALGO_DONE_WID                         ( 1)
  #define CH1_SC1_CR_CADB_STATUS_ALGO_DONE_MSK                         (0x10000000)
  #define CH1_SC1_CR_CADB_STATUS_ALGO_DONE_MIN                         (0)
  #define CH1_SC1_CR_CADB_STATUS_ALGO_DONE_MAX                         (1) // 0x00000001
  #define CH1_SC1_CR_CADB_STATUS_ALGO_DONE_DEF                         (0x00000000)
  #define CH1_SC1_CR_CADB_STATUS_ALGO_DONE_HSH                         (0x011CD32C)

  #define CH1_SC1_CR_CADB_STATUS_START_TEST_DELAY_BUSY_OFF             (29)
  #define CH1_SC1_CR_CADB_STATUS_START_TEST_DELAY_BUSY_WID             ( 1)
  #define CH1_SC1_CR_CADB_STATUS_START_TEST_DELAY_BUSY_MSK             (0x20000000)
  #define CH1_SC1_CR_CADB_STATUS_START_TEST_DELAY_BUSY_MIN             (0)
  #define CH1_SC1_CR_CADB_STATUS_START_TEST_DELAY_BUSY_MAX             (1) // 0x00000001
  #define CH1_SC1_CR_CADB_STATUS_START_TEST_DELAY_BUSY_DEF             (0x00000000)
  #define CH1_SC1_CR_CADB_STATUS_START_TEST_DELAY_BUSY_HSH             (0x011DD32C)

  #define CH1_SC1_CR_CADB_STATUS_TEST_BUSY_OFF                         (30)
  #define CH1_SC1_CR_CADB_STATUS_TEST_BUSY_WID                         ( 1)
  #define CH1_SC1_CR_CADB_STATUS_TEST_BUSY_MSK                         (0x40000000)
  #define CH1_SC1_CR_CADB_STATUS_TEST_BUSY_MIN                         (0)
  #define CH1_SC1_CR_CADB_STATUS_TEST_BUSY_MAX                         (1) // 0x00000001
  #define CH1_SC1_CR_CADB_STATUS_TEST_BUSY_DEF                         (0x00000000)
  #define CH1_SC1_CR_CADB_STATUS_TEST_BUSY_HSH                         (0x011ED32C)

  #define CH1_SC1_CR_CADB_STATUS_TEST_DONE_OFF                         (31)
  #define CH1_SC1_CR_CADB_STATUS_TEST_DONE_WID                         ( 1)
  #define CH1_SC1_CR_CADB_STATUS_TEST_DONE_MSK                         (0x80000000)
  #define CH1_SC1_CR_CADB_STATUS_TEST_DONE_MIN                         (0)
  #define CH1_SC1_CR_CADB_STATUS_TEST_DONE_MAX                         (1) // 0x00000001
  #define CH1_SC1_CR_CADB_STATUS_TEST_DONE_DEF                         (0x00000000)
  #define CH1_SC1_CR_CADB_STATUS_TEST_DONE_HSH                         (0x011FD32C)

#define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_REG                          (0x0000D330)

  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_OFF            ( 0)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_WID            ( 2)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_MSK            (0x00000003)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_MIN            (0)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_MAX            (3) // 0x00000003
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_DEF            (0x00000001)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_MODE_HSH            (0x0200D330)

  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_OFF ( 3)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_WID ( 3)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_MSK (0x00000038)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_MIN (0)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_MAX (7) // 0x00000007
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_DEF (0x00000000)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_UNISEQ_LFSR_POLYNOMIAL_SIZE_HSH (0x0303D330)

#define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_REG                          (0x0000D331)

  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_OFF            ( 0)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_WID            ( 2)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_MSK            (0x00000003)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_MIN            (0)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_MAX            (3) // 0x00000003
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_DEF            (0x00000001)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_MODE_HSH            (0x0200D331)

  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_OFF ( 3)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_WID ( 3)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_MSK (0x00000038)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_MIN (0)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_MAX (7) // 0x00000007
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_DEF (0x00000000)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_UNISEQ_LFSR_POLYNOMIAL_SIZE_HSH (0x0303D331)

#define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_REG                          (0x0000D332)

  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_OFF            ( 0)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_WID            ( 2)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_MSK            (0x00000003)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_MIN            (0)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_MAX            (3) // 0x00000003
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_DEF            (0x00000001)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_MODE_HSH            (0x0200D332)

  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_OFF ( 3)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_WID ( 3)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_MSK (0x00000038)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_MIN (0)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_MAX (7) // 0x00000007
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_DEF (0x00000000)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_UNISEQ_LFSR_POLYNOMIAL_SIZE_HSH (0x0303D332)

#define CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_0_REG                         (0x0000D334)

  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_OFF                   ( 0)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_WID                   (32)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_MSK                   (0xFFFFFFFF)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_MIN                   (0)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_MAX                   (4294967295) // 0xFFFFFFFF
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_DEF                   (0x0000AA55)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_0_CMD_HSH                   (0x2000D334)

#define CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_1_REG                         (0x0000D338)

  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_OFF                   ( 0)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_WID                   (32)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_MSK                   (0xFFFFFFFF)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_MIN                   (0)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_MAX                   (4294967295) // 0xFFFFFFFF
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_DEF                   (0x0000AA55)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_1_CMD_HSH                   (0x2000D338)

#define CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_2_REG                         (0x0000D33C)

  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_OFF                   ( 0)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_WID                   (32)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_MSK                   (0xFFFFFFFF)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_MIN                   (0)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_MAX                   (4294967295) // 0xFFFFFFFF
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_DEF                   (0x0000AA55)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_2_CMD_HSH                   (0x2000D33C)

#define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_REG                            (0x0000D340)

  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_OFF                    ( 0)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_WID                    ( 1)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_MSK                    (0x00000001)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_MIN                    (0)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_MAX                    (1) // 0x00000001
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_DEF                    (0x00000000)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_SEL_HSH                    (0x0100D340)

  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_OFF             ( 4)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_WID             ( 4)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_MSK             (0x000000F0)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_MIN             (0)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_MAX             (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_DEF             (0x00000000)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_COUNTER_HI_HSH             (0x0404D340)

  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_OFF                    ( 8)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_WID                    ( 8)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_MSK                    (0x0000FF00)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_MIN                    (0)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_MAX                    (255) // 0x000000FF
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_DEF                    (0x00000000)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_L_CNT_HSH                    (0x0808D340)

  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_OFF                    (16)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_WID                    ( 8)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_MSK                    (0x00FF0000)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_MIN                    (0)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_MAX                    (255) // 0x000000FF
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_DEF                    (0x00000000)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_N_CNT_HSH                    (0x0810D340)

  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_OFF                    (24)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_WID                    ( 8)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_MSK                    (0xFF000000)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_MIN                    (0)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_MAX                    (255) // 0x000000FF
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_DEF                    (0x00000000)
  #define CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_M_CNT_HSH                    (0x0818D340)

#define CH1_SC1_CR_CADB_BUF_0_REG                                      (0x0000D348)

  #define CH1_SC1_CR_CADB_BUF_0_CS_OFF                                 ( 0)
  #define CH1_SC1_CR_CADB_BUF_0_CS_WID                                 ( 4)
  #define CH1_SC1_CR_CADB_BUF_0_CS_MSK                                 (0x0000000F)
  #define CH1_SC1_CR_CADB_BUF_0_CS_MIN                                 (0)
  #define CH1_SC1_CR_CADB_BUF_0_CS_MAX                                 (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_BUF_0_CS_DEF                                 (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_0_CS_HSH                                 (0x4400D348)

  #define CH1_SC1_CR_CADB_BUF_0_CID_OFF                                ( 4)
  #define CH1_SC1_CR_CADB_BUF_0_CID_WID                                ( 3)
  #define CH1_SC1_CR_CADB_BUF_0_CID_MSK                                (0x00000070)
  #define CH1_SC1_CR_CADB_BUF_0_CID_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_0_CID_MAX                                (7) // 0x00000007
  #define CH1_SC1_CR_CADB_BUF_0_CID_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_0_CID_HSH                                (0x4304D348)

  #define CH1_SC1_CR_CADB_BUF_0_ODT_OFF                                ( 7)
  #define CH1_SC1_CR_CADB_BUF_0_ODT_WID                                ( 4)
  #define CH1_SC1_CR_CADB_BUF_0_ODT_MSK                                (0x00000780)
  #define CH1_SC1_CR_CADB_BUF_0_ODT_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_0_ODT_MAX                                (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_BUF_0_ODT_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_0_ODT_HSH                                (0x4407D348)

  #define CH1_SC1_CR_CADB_BUF_0_CKE_OFF                                (11)
  #define CH1_SC1_CR_CADB_BUF_0_CKE_WID                                ( 4)
  #define CH1_SC1_CR_CADB_BUF_0_CKE_MSK                                (0x00007800)
  #define CH1_SC1_CR_CADB_BUF_0_CKE_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_0_CKE_MAX                                (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_BUF_0_CKE_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_0_CKE_HSH                                (0x440BD348)

  #define CH1_SC1_CR_CADB_BUF_0_USE_HALF_CA_OFF                        (15)
  #define CH1_SC1_CR_CADB_BUF_0_USE_HALF_CA_WID                        ( 1)
  #define CH1_SC1_CR_CADB_BUF_0_USE_HALF_CA_MSK                        (0x00008000)
  #define CH1_SC1_CR_CADB_BUF_0_USE_HALF_CA_MIN                        (0)
  #define CH1_SC1_CR_CADB_BUF_0_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH1_SC1_CR_CADB_BUF_0_USE_HALF_CA_DEF                        (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_0_USE_HALF_CA_HSH                        (0x410FD348)

  #define CH1_SC1_CR_CADB_BUF_0_VAL_OFF                                (16)
  #define CH1_SC1_CR_CADB_BUF_0_VAL_WID                                ( 1)
  #define CH1_SC1_CR_CADB_BUF_0_VAL_MSK                                (0x00010000)
  #define CH1_SC1_CR_CADB_BUF_0_VAL_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_0_VAL_MAX                                (1) // 0x00000001
  #define CH1_SC1_CR_CADB_BUF_0_VAL_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_0_VAL_HSH                                (0x4110D348)

  #define CH1_SC1_CR_CADB_BUF_0_PAR_OFF                                (17)
  #define CH1_SC1_CR_CADB_BUF_0_PAR_WID                                ( 1)
  #define CH1_SC1_CR_CADB_BUF_0_PAR_MSK                                (0x00020000)
  #define CH1_SC1_CR_CADB_BUF_0_PAR_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_0_PAR_MAX                                (1) // 0x00000001
  #define CH1_SC1_CR_CADB_BUF_0_PAR_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_0_PAR_HSH                                (0x4111D348)

  #define CH1_SC1_CR_CADB_BUF_0_CA_OFF                                 (18)
  #define CH1_SC1_CR_CADB_BUF_0_CA_WID                                 (24)
  #define CH1_SC1_CR_CADB_BUF_0_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH1_SC1_CR_CADB_BUF_0_CA_MIN                                 (0)
  #define CH1_SC1_CR_CADB_BUF_0_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH1_SC1_CR_CADB_BUF_0_CA_DEF                                 (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_0_CA_HSH                                 (0x5812D348)

#define CH1_SC1_CR_CADB_BUF_1_REG                                      (0x0000D350)

  #define CH1_SC1_CR_CADB_BUF_1_CS_OFF                                 ( 0)
  #define CH1_SC1_CR_CADB_BUF_1_CS_WID                                 ( 4)
  #define CH1_SC1_CR_CADB_BUF_1_CS_MSK                                 (0x0000000F)
  #define CH1_SC1_CR_CADB_BUF_1_CS_MIN                                 (0)
  #define CH1_SC1_CR_CADB_BUF_1_CS_MAX                                 (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_BUF_1_CS_DEF                                 (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_1_CS_HSH                                 (0x4400D350)

  #define CH1_SC1_CR_CADB_BUF_1_CID_OFF                                ( 4)
  #define CH1_SC1_CR_CADB_BUF_1_CID_WID                                ( 3)
  #define CH1_SC1_CR_CADB_BUF_1_CID_MSK                                (0x00000070)
  #define CH1_SC1_CR_CADB_BUF_1_CID_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_1_CID_MAX                                (7) // 0x00000007
  #define CH1_SC1_CR_CADB_BUF_1_CID_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_1_CID_HSH                                (0x4304D350)

  #define CH1_SC1_CR_CADB_BUF_1_ODT_OFF                                ( 7)
  #define CH1_SC1_CR_CADB_BUF_1_ODT_WID                                ( 4)
  #define CH1_SC1_CR_CADB_BUF_1_ODT_MSK                                (0x00000780)
  #define CH1_SC1_CR_CADB_BUF_1_ODT_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_1_ODT_MAX                                (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_BUF_1_ODT_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_1_ODT_HSH                                (0x4407D350)

  #define CH1_SC1_CR_CADB_BUF_1_CKE_OFF                                (11)
  #define CH1_SC1_CR_CADB_BUF_1_CKE_WID                                ( 4)
  #define CH1_SC1_CR_CADB_BUF_1_CKE_MSK                                (0x00007800)
  #define CH1_SC1_CR_CADB_BUF_1_CKE_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_1_CKE_MAX                                (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_BUF_1_CKE_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_1_CKE_HSH                                (0x440BD350)

  #define CH1_SC1_CR_CADB_BUF_1_USE_HALF_CA_OFF                        (15)
  #define CH1_SC1_CR_CADB_BUF_1_USE_HALF_CA_WID                        ( 1)
  #define CH1_SC1_CR_CADB_BUF_1_USE_HALF_CA_MSK                        (0x00008000)
  #define CH1_SC1_CR_CADB_BUF_1_USE_HALF_CA_MIN                        (0)
  #define CH1_SC1_CR_CADB_BUF_1_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH1_SC1_CR_CADB_BUF_1_USE_HALF_CA_DEF                        (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_1_USE_HALF_CA_HSH                        (0x410FD350)

  #define CH1_SC1_CR_CADB_BUF_1_VAL_OFF                                (16)
  #define CH1_SC1_CR_CADB_BUF_1_VAL_WID                                ( 1)
  #define CH1_SC1_CR_CADB_BUF_1_VAL_MSK                                (0x00010000)
  #define CH1_SC1_CR_CADB_BUF_1_VAL_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_1_VAL_MAX                                (1) // 0x00000001
  #define CH1_SC1_CR_CADB_BUF_1_VAL_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_1_VAL_HSH                                (0x4110D350)

  #define CH1_SC1_CR_CADB_BUF_1_PAR_OFF                                (17)
  #define CH1_SC1_CR_CADB_BUF_1_PAR_WID                                ( 1)
  #define CH1_SC1_CR_CADB_BUF_1_PAR_MSK                                (0x00020000)
  #define CH1_SC1_CR_CADB_BUF_1_PAR_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_1_PAR_MAX                                (1) // 0x00000001
  #define CH1_SC1_CR_CADB_BUF_1_PAR_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_1_PAR_HSH                                (0x4111D350)

  #define CH1_SC1_CR_CADB_BUF_1_CA_OFF                                 (18)
  #define CH1_SC1_CR_CADB_BUF_1_CA_WID                                 (24)
  #define CH1_SC1_CR_CADB_BUF_1_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH1_SC1_CR_CADB_BUF_1_CA_MIN                                 (0)
  #define CH1_SC1_CR_CADB_BUF_1_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH1_SC1_CR_CADB_BUF_1_CA_DEF                                 (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_1_CA_HSH                                 (0x5812D350)

#define CH1_SC1_CR_CADB_BUF_2_REG                                      (0x0000D358)

  #define CH1_SC1_CR_CADB_BUF_2_CS_OFF                                 ( 0)
  #define CH1_SC1_CR_CADB_BUF_2_CS_WID                                 ( 4)
  #define CH1_SC1_CR_CADB_BUF_2_CS_MSK                                 (0x0000000F)
  #define CH1_SC1_CR_CADB_BUF_2_CS_MIN                                 (0)
  #define CH1_SC1_CR_CADB_BUF_2_CS_MAX                                 (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_BUF_2_CS_DEF                                 (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_2_CS_HSH                                 (0x4400D358)

  #define CH1_SC1_CR_CADB_BUF_2_CID_OFF                                ( 4)
  #define CH1_SC1_CR_CADB_BUF_2_CID_WID                                ( 3)
  #define CH1_SC1_CR_CADB_BUF_2_CID_MSK                                (0x00000070)
  #define CH1_SC1_CR_CADB_BUF_2_CID_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_2_CID_MAX                                (7) // 0x00000007
  #define CH1_SC1_CR_CADB_BUF_2_CID_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_2_CID_HSH                                (0x4304D358)

  #define CH1_SC1_CR_CADB_BUF_2_ODT_OFF                                ( 7)
  #define CH1_SC1_CR_CADB_BUF_2_ODT_WID                                ( 4)
  #define CH1_SC1_CR_CADB_BUF_2_ODT_MSK                                (0x00000780)
  #define CH1_SC1_CR_CADB_BUF_2_ODT_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_2_ODT_MAX                                (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_BUF_2_ODT_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_2_ODT_HSH                                (0x4407D358)

  #define CH1_SC1_CR_CADB_BUF_2_CKE_OFF                                (11)
  #define CH1_SC1_CR_CADB_BUF_2_CKE_WID                                ( 4)
  #define CH1_SC1_CR_CADB_BUF_2_CKE_MSK                                (0x00007800)
  #define CH1_SC1_CR_CADB_BUF_2_CKE_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_2_CKE_MAX                                (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_BUF_2_CKE_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_2_CKE_HSH                                (0x440BD358)

  #define CH1_SC1_CR_CADB_BUF_2_USE_HALF_CA_OFF                        (15)
  #define CH1_SC1_CR_CADB_BUF_2_USE_HALF_CA_WID                        ( 1)
  #define CH1_SC1_CR_CADB_BUF_2_USE_HALF_CA_MSK                        (0x00008000)
  #define CH1_SC1_CR_CADB_BUF_2_USE_HALF_CA_MIN                        (0)
  #define CH1_SC1_CR_CADB_BUF_2_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH1_SC1_CR_CADB_BUF_2_USE_HALF_CA_DEF                        (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_2_USE_HALF_CA_HSH                        (0x410FD358)

  #define CH1_SC1_CR_CADB_BUF_2_VAL_OFF                                (16)
  #define CH1_SC1_CR_CADB_BUF_2_VAL_WID                                ( 1)
  #define CH1_SC1_CR_CADB_BUF_2_VAL_MSK                                (0x00010000)
  #define CH1_SC1_CR_CADB_BUF_2_VAL_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_2_VAL_MAX                                (1) // 0x00000001
  #define CH1_SC1_CR_CADB_BUF_2_VAL_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_2_VAL_HSH                                (0x4110D358)

  #define CH1_SC1_CR_CADB_BUF_2_PAR_OFF                                (17)
  #define CH1_SC1_CR_CADB_BUF_2_PAR_WID                                ( 1)
  #define CH1_SC1_CR_CADB_BUF_2_PAR_MSK                                (0x00020000)
  #define CH1_SC1_CR_CADB_BUF_2_PAR_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_2_PAR_MAX                                (1) // 0x00000001
  #define CH1_SC1_CR_CADB_BUF_2_PAR_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_2_PAR_HSH                                (0x4111D358)

  #define CH1_SC1_CR_CADB_BUF_2_CA_OFF                                 (18)
  #define CH1_SC1_CR_CADB_BUF_2_CA_WID                                 (24)
  #define CH1_SC1_CR_CADB_BUF_2_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH1_SC1_CR_CADB_BUF_2_CA_MIN                                 (0)
  #define CH1_SC1_CR_CADB_BUF_2_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH1_SC1_CR_CADB_BUF_2_CA_DEF                                 (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_2_CA_HSH                                 (0x5812D358)

#define CH1_SC1_CR_CADB_BUF_3_REG                                      (0x0000D360)

  #define CH1_SC1_CR_CADB_BUF_3_CS_OFF                                 ( 0)
  #define CH1_SC1_CR_CADB_BUF_3_CS_WID                                 ( 4)
  #define CH1_SC1_CR_CADB_BUF_3_CS_MSK                                 (0x0000000F)
  #define CH1_SC1_CR_CADB_BUF_3_CS_MIN                                 (0)
  #define CH1_SC1_CR_CADB_BUF_3_CS_MAX                                 (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_BUF_3_CS_DEF                                 (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_3_CS_HSH                                 (0x4400D360)

  #define CH1_SC1_CR_CADB_BUF_3_CID_OFF                                ( 4)
  #define CH1_SC1_CR_CADB_BUF_3_CID_WID                                ( 3)
  #define CH1_SC1_CR_CADB_BUF_3_CID_MSK                                (0x00000070)
  #define CH1_SC1_CR_CADB_BUF_3_CID_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_3_CID_MAX                                (7) // 0x00000007
  #define CH1_SC1_CR_CADB_BUF_3_CID_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_3_CID_HSH                                (0x4304D360)

  #define CH1_SC1_CR_CADB_BUF_3_ODT_OFF                                ( 7)
  #define CH1_SC1_CR_CADB_BUF_3_ODT_WID                                ( 4)
  #define CH1_SC1_CR_CADB_BUF_3_ODT_MSK                                (0x00000780)
  #define CH1_SC1_CR_CADB_BUF_3_ODT_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_3_ODT_MAX                                (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_BUF_3_ODT_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_3_ODT_HSH                                (0x4407D360)

  #define CH1_SC1_CR_CADB_BUF_3_CKE_OFF                                (11)
  #define CH1_SC1_CR_CADB_BUF_3_CKE_WID                                ( 4)
  #define CH1_SC1_CR_CADB_BUF_3_CKE_MSK                                (0x00007800)
  #define CH1_SC1_CR_CADB_BUF_3_CKE_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_3_CKE_MAX                                (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_BUF_3_CKE_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_3_CKE_HSH                                (0x440BD360)

  #define CH1_SC1_CR_CADB_BUF_3_USE_HALF_CA_OFF                        (15)
  #define CH1_SC1_CR_CADB_BUF_3_USE_HALF_CA_WID                        ( 1)
  #define CH1_SC1_CR_CADB_BUF_3_USE_HALF_CA_MSK                        (0x00008000)
  #define CH1_SC1_CR_CADB_BUF_3_USE_HALF_CA_MIN                        (0)
  #define CH1_SC1_CR_CADB_BUF_3_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH1_SC1_CR_CADB_BUF_3_USE_HALF_CA_DEF                        (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_3_USE_HALF_CA_HSH                        (0x410FD360)

  #define CH1_SC1_CR_CADB_BUF_3_VAL_OFF                                (16)
  #define CH1_SC1_CR_CADB_BUF_3_VAL_WID                                ( 1)
  #define CH1_SC1_CR_CADB_BUF_3_VAL_MSK                                (0x00010000)
  #define CH1_SC1_CR_CADB_BUF_3_VAL_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_3_VAL_MAX                                (1) // 0x00000001
  #define CH1_SC1_CR_CADB_BUF_3_VAL_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_3_VAL_HSH                                (0x4110D360)

  #define CH1_SC1_CR_CADB_BUF_3_PAR_OFF                                (17)
  #define CH1_SC1_CR_CADB_BUF_3_PAR_WID                                ( 1)
  #define CH1_SC1_CR_CADB_BUF_3_PAR_MSK                                (0x00020000)
  #define CH1_SC1_CR_CADB_BUF_3_PAR_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_3_PAR_MAX                                (1) // 0x00000001
  #define CH1_SC1_CR_CADB_BUF_3_PAR_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_3_PAR_HSH                                (0x4111D360)

  #define CH1_SC1_CR_CADB_BUF_3_CA_OFF                                 (18)
  #define CH1_SC1_CR_CADB_BUF_3_CA_WID                                 (24)
  #define CH1_SC1_CR_CADB_BUF_3_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH1_SC1_CR_CADB_BUF_3_CA_MIN                                 (0)
  #define CH1_SC1_CR_CADB_BUF_3_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH1_SC1_CR_CADB_BUF_3_CA_DEF                                 (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_3_CA_HSH                                 (0x5812D360)

#define CH1_SC1_CR_CADB_BUF_4_REG                                      (0x0000D368)

  #define CH1_SC1_CR_CADB_BUF_4_CS_OFF                                 ( 0)
  #define CH1_SC1_CR_CADB_BUF_4_CS_WID                                 ( 4)
  #define CH1_SC1_CR_CADB_BUF_4_CS_MSK                                 (0x0000000F)
  #define CH1_SC1_CR_CADB_BUF_4_CS_MIN                                 (0)
  #define CH1_SC1_CR_CADB_BUF_4_CS_MAX                                 (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_BUF_4_CS_DEF                                 (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_4_CS_HSH                                 (0x4400D368)

  #define CH1_SC1_CR_CADB_BUF_4_CID_OFF                                ( 4)
  #define CH1_SC1_CR_CADB_BUF_4_CID_WID                                ( 3)
  #define CH1_SC1_CR_CADB_BUF_4_CID_MSK                                (0x00000070)
  #define CH1_SC1_CR_CADB_BUF_4_CID_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_4_CID_MAX                                (7) // 0x00000007
  #define CH1_SC1_CR_CADB_BUF_4_CID_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_4_CID_HSH                                (0x4304D368)

  #define CH1_SC1_CR_CADB_BUF_4_ODT_OFF                                ( 7)
  #define CH1_SC1_CR_CADB_BUF_4_ODT_WID                                ( 4)
  #define CH1_SC1_CR_CADB_BUF_4_ODT_MSK                                (0x00000780)
  #define CH1_SC1_CR_CADB_BUF_4_ODT_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_4_ODT_MAX                                (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_BUF_4_ODT_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_4_ODT_HSH                                (0x4407D368)

  #define CH1_SC1_CR_CADB_BUF_4_CKE_OFF                                (11)
  #define CH1_SC1_CR_CADB_BUF_4_CKE_WID                                ( 4)
  #define CH1_SC1_CR_CADB_BUF_4_CKE_MSK                                (0x00007800)
  #define CH1_SC1_CR_CADB_BUF_4_CKE_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_4_CKE_MAX                                (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_BUF_4_CKE_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_4_CKE_HSH                                (0x440BD368)

  #define CH1_SC1_CR_CADB_BUF_4_USE_HALF_CA_OFF                        (15)
  #define CH1_SC1_CR_CADB_BUF_4_USE_HALF_CA_WID                        ( 1)
  #define CH1_SC1_CR_CADB_BUF_4_USE_HALF_CA_MSK                        (0x00008000)
  #define CH1_SC1_CR_CADB_BUF_4_USE_HALF_CA_MIN                        (0)
  #define CH1_SC1_CR_CADB_BUF_4_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH1_SC1_CR_CADB_BUF_4_USE_HALF_CA_DEF                        (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_4_USE_HALF_CA_HSH                        (0x410FD368)

  #define CH1_SC1_CR_CADB_BUF_4_VAL_OFF                                (16)
  #define CH1_SC1_CR_CADB_BUF_4_VAL_WID                                ( 1)
  #define CH1_SC1_CR_CADB_BUF_4_VAL_MSK                                (0x00010000)
  #define CH1_SC1_CR_CADB_BUF_4_VAL_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_4_VAL_MAX                                (1) // 0x00000001
  #define CH1_SC1_CR_CADB_BUF_4_VAL_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_4_VAL_HSH                                (0x4110D368)

  #define CH1_SC1_CR_CADB_BUF_4_PAR_OFF                                (17)
  #define CH1_SC1_CR_CADB_BUF_4_PAR_WID                                ( 1)
  #define CH1_SC1_CR_CADB_BUF_4_PAR_MSK                                (0x00020000)
  #define CH1_SC1_CR_CADB_BUF_4_PAR_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_4_PAR_MAX                                (1) // 0x00000001
  #define CH1_SC1_CR_CADB_BUF_4_PAR_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_4_PAR_HSH                                (0x4111D368)

  #define CH1_SC1_CR_CADB_BUF_4_CA_OFF                                 (18)
  #define CH1_SC1_CR_CADB_BUF_4_CA_WID                                 (24)
  #define CH1_SC1_CR_CADB_BUF_4_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH1_SC1_CR_CADB_BUF_4_CA_MIN                                 (0)
  #define CH1_SC1_CR_CADB_BUF_4_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH1_SC1_CR_CADB_BUF_4_CA_DEF                                 (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_4_CA_HSH                                 (0x5812D368)

#define CH1_SC1_CR_CADB_BUF_5_REG                                      (0x0000D370)

  #define CH1_SC1_CR_CADB_BUF_5_CS_OFF                                 ( 0)
  #define CH1_SC1_CR_CADB_BUF_5_CS_WID                                 ( 4)
  #define CH1_SC1_CR_CADB_BUF_5_CS_MSK                                 (0x0000000F)
  #define CH1_SC1_CR_CADB_BUF_5_CS_MIN                                 (0)
  #define CH1_SC1_CR_CADB_BUF_5_CS_MAX                                 (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_BUF_5_CS_DEF                                 (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_5_CS_HSH                                 (0x4400D370)

  #define CH1_SC1_CR_CADB_BUF_5_CID_OFF                                ( 4)
  #define CH1_SC1_CR_CADB_BUF_5_CID_WID                                ( 3)
  #define CH1_SC1_CR_CADB_BUF_5_CID_MSK                                (0x00000070)
  #define CH1_SC1_CR_CADB_BUF_5_CID_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_5_CID_MAX                                (7) // 0x00000007
  #define CH1_SC1_CR_CADB_BUF_5_CID_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_5_CID_HSH                                (0x4304D370)

  #define CH1_SC1_CR_CADB_BUF_5_ODT_OFF                                ( 7)
  #define CH1_SC1_CR_CADB_BUF_5_ODT_WID                                ( 4)
  #define CH1_SC1_CR_CADB_BUF_5_ODT_MSK                                (0x00000780)
  #define CH1_SC1_CR_CADB_BUF_5_ODT_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_5_ODT_MAX                                (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_BUF_5_ODT_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_5_ODT_HSH                                (0x4407D370)

  #define CH1_SC1_CR_CADB_BUF_5_CKE_OFF                                (11)
  #define CH1_SC1_CR_CADB_BUF_5_CKE_WID                                ( 4)
  #define CH1_SC1_CR_CADB_BUF_5_CKE_MSK                                (0x00007800)
  #define CH1_SC1_CR_CADB_BUF_5_CKE_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_5_CKE_MAX                                (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_BUF_5_CKE_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_5_CKE_HSH                                (0x440BD370)

  #define CH1_SC1_CR_CADB_BUF_5_USE_HALF_CA_OFF                        (15)
  #define CH1_SC1_CR_CADB_BUF_5_USE_HALF_CA_WID                        ( 1)
  #define CH1_SC1_CR_CADB_BUF_5_USE_HALF_CA_MSK                        (0x00008000)
  #define CH1_SC1_CR_CADB_BUF_5_USE_HALF_CA_MIN                        (0)
  #define CH1_SC1_CR_CADB_BUF_5_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH1_SC1_CR_CADB_BUF_5_USE_HALF_CA_DEF                        (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_5_USE_HALF_CA_HSH                        (0x410FD370)

  #define CH1_SC1_CR_CADB_BUF_5_VAL_OFF                                (16)
  #define CH1_SC1_CR_CADB_BUF_5_VAL_WID                                ( 1)
  #define CH1_SC1_CR_CADB_BUF_5_VAL_MSK                                (0x00010000)
  #define CH1_SC1_CR_CADB_BUF_5_VAL_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_5_VAL_MAX                                (1) // 0x00000001
  #define CH1_SC1_CR_CADB_BUF_5_VAL_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_5_VAL_HSH                                (0x4110D370)

  #define CH1_SC1_CR_CADB_BUF_5_PAR_OFF                                (17)
  #define CH1_SC1_CR_CADB_BUF_5_PAR_WID                                ( 1)
  #define CH1_SC1_CR_CADB_BUF_5_PAR_MSK                                (0x00020000)
  #define CH1_SC1_CR_CADB_BUF_5_PAR_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_5_PAR_MAX                                (1) // 0x00000001
  #define CH1_SC1_CR_CADB_BUF_5_PAR_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_5_PAR_HSH                                (0x4111D370)

  #define CH1_SC1_CR_CADB_BUF_5_CA_OFF                                 (18)
  #define CH1_SC1_CR_CADB_BUF_5_CA_WID                                 (24)
  #define CH1_SC1_CR_CADB_BUF_5_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH1_SC1_CR_CADB_BUF_5_CA_MIN                                 (0)
  #define CH1_SC1_CR_CADB_BUF_5_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH1_SC1_CR_CADB_BUF_5_CA_DEF                                 (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_5_CA_HSH                                 (0x5812D370)

#define CH1_SC1_CR_CADB_BUF_6_REG                                      (0x0000D378)

  #define CH1_SC1_CR_CADB_BUF_6_CS_OFF                                 ( 0)
  #define CH1_SC1_CR_CADB_BUF_6_CS_WID                                 ( 4)
  #define CH1_SC1_CR_CADB_BUF_6_CS_MSK                                 (0x0000000F)
  #define CH1_SC1_CR_CADB_BUF_6_CS_MIN                                 (0)
  #define CH1_SC1_CR_CADB_BUF_6_CS_MAX                                 (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_BUF_6_CS_DEF                                 (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_6_CS_HSH                                 (0x4400D378)

  #define CH1_SC1_CR_CADB_BUF_6_CID_OFF                                ( 4)
  #define CH1_SC1_CR_CADB_BUF_6_CID_WID                                ( 3)
  #define CH1_SC1_CR_CADB_BUF_6_CID_MSK                                (0x00000070)
  #define CH1_SC1_CR_CADB_BUF_6_CID_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_6_CID_MAX                                (7) // 0x00000007
  #define CH1_SC1_CR_CADB_BUF_6_CID_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_6_CID_HSH                                (0x4304D378)

  #define CH1_SC1_CR_CADB_BUF_6_ODT_OFF                                ( 7)
  #define CH1_SC1_CR_CADB_BUF_6_ODT_WID                                ( 4)
  #define CH1_SC1_CR_CADB_BUF_6_ODT_MSK                                (0x00000780)
  #define CH1_SC1_CR_CADB_BUF_6_ODT_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_6_ODT_MAX                                (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_BUF_6_ODT_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_6_ODT_HSH                                (0x4407D378)

  #define CH1_SC1_CR_CADB_BUF_6_CKE_OFF                                (11)
  #define CH1_SC1_CR_CADB_BUF_6_CKE_WID                                ( 4)
  #define CH1_SC1_CR_CADB_BUF_6_CKE_MSK                                (0x00007800)
  #define CH1_SC1_CR_CADB_BUF_6_CKE_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_6_CKE_MAX                                (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_BUF_6_CKE_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_6_CKE_HSH                                (0x440BD378)

  #define CH1_SC1_CR_CADB_BUF_6_USE_HALF_CA_OFF                        (15)
  #define CH1_SC1_CR_CADB_BUF_6_USE_HALF_CA_WID                        ( 1)
  #define CH1_SC1_CR_CADB_BUF_6_USE_HALF_CA_MSK                        (0x00008000)
  #define CH1_SC1_CR_CADB_BUF_6_USE_HALF_CA_MIN                        (0)
  #define CH1_SC1_CR_CADB_BUF_6_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH1_SC1_CR_CADB_BUF_6_USE_HALF_CA_DEF                        (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_6_USE_HALF_CA_HSH                        (0x410FD378)

  #define CH1_SC1_CR_CADB_BUF_6_VAL_OFF                                (16)
  #define CH1_SC1_CR_CADB_BUF_6_VAL_WID                                ( 1)
  #define CH1_SC1_CR_CADB_BUF_6_VAL_MSK                                (0x00010000)
  #define CH1_SC1_CR_CADB_BUF_6_VAL_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_6_VAL_MAX                                (1) // 0x00000001
  #define CH1_SC1_CR_CADB_BUF_6_VAL_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_6_VAL_HSH                                (0x4110D378)

  #define CH1_SC1_CR_CADB_BUF_6_PAR_OFF                                (17)
  #define CH1_SC1_CR_CADB_BUF_6_PAR_WID                                ( 1)
  #define CH1_SC1_CR_CADB_BUF_6_PAR_MSK                                (0x00020000)
  #define CH1_SC1_CR_CADB_BUF_6_PAR_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_6_PAR_MAX                                (1) // 0x00000001
  #define CH1_SC1_CR_CADB_BUF_6_PAR_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_6_PAR_HSH                                (0x4111D378)

  #define CH1_SC1_CR_CADB_BUF_6_CA_OFF                                 (18)
  #define CH1_SC1_CR_CADB_BUF_6_CA_WID                                 (24)
  #define CH1_SC1_CR_CADB_BUF_6_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH1_SC1_CR_CADB_BUF_6_CA_MIN                                 (0)
  #define CH1_SC1_CR_CADB_BUF_6_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH1_SC1_CR_CADB_BUF_6_CA_DEF                                 (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_6_CA_HSH                                 (0x5812D378)

#define CH1_SC1_CR_CADB_BUF_7_REG                                      (0x0000D380)

  #define CH1_SC1_CR_CADB_BUF_7_CS_OFF                                 ( 0)
  #define CH1_SC1_CR_CADB_BUF_7_CS_WID                                 ( 4)
  #define CH1_SC1_CR_CADB_BUF_7_CS_MSK                                 (0x0000000F)
  #define CH1_SC1_CR_CADB_BUF_7_CS_MIN                                 (0)
  #define CH1_SC1_CR_CADB_BUF_7_CS_MAX                                 (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_BUF_7_CS_DEF                                 (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_7_CS_HSH                                 (0x4400D380)

  #define CH1_SC1_CR_CADB_BUF_7_CID_OFF                                ( 4)
  #define CH1_SC1_CR_CADB_BUF_7_CID_WID                                ( 3)
  #define CH1_SC1_CR_CADB_BUF_7_CID_MSK                                (0x00000070)
  #define CH1_SC1_CR_CADB_BUF_7_CID_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_7_CID_MAX                                (7) // 0x00000007
  #define CH1_SC1_CR_CADB_BUF_7_CID_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_7_CID_HSH                                (0x4304D380)

  #define CH1_SC1_CR_CADB_BUF_7_ODT_OFF                                ( 7)
  #define CH1_SC1_CR_CADB_BUF_7_ODT_WID                                ( 4)
  #define CH1_SC1_CR_CADB_BUF_7_ODT_MSK                                (0x00000780)
  #define CH1_SC1_CR_CADB_BUF_7_ODT_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_7_ODT_MAX                                (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_BUF_7_ODT_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_7_ODT_HSH                                (0x4407D380)

  #define CH1_SC1_CR_CADB_BUF_7_CKE_OFF                                (11)
  #define CH1_SC1_CR_CADB_BUF_7_CKE_WID                                ( 4)
  #define CH1_SC1_CR_CADB_BUF_7_CKE_MSK                                (0x00007800)
  #define CH1_SC1_CR_CADB_BUF_7_CKE_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_7_CKE_MAX                                (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_BUF_7_CKE_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_7_CKE_HSH                                (0x440BD380)

  #define CH1_SC1_CR_CADB_BUF_7_USE_HALF_CA_OFF                        (15)
  #define CH1_SC1_CR_CADB_BUF_7_USE_HALF_CA_WID                        ( 1)
  #define CH1_SC1_CR_CADB_BUF_7_USE_HALF_CA_MSK                        (0x00008000)
  #define CH1_SC1_CR_CADB_BUF_7_USE_HALF_CA_MIN                        (0)
  #define CH1_SC1_CR_CADB_BUF_7_USE_HALF_CA_MAX                        (1) // 0x00000001
  #define CH1_SC1_CR_CADB_BUF_7_USE_HALF_CA_DEF                        (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_7_USE_HALF_CA_HSH                        (0x410FD380)

  #define CH1_SC1_CR_CADB_BUF_7_VAL_OFF                                (16)
  #define CH1_SC1_CR_CADB_BUF_7_VAL_WID                                ( 1)
  #define CH1_SC1_CR_CADB_BUF_7_VAL_MSK                                (0x00010000)
  #define CH1_SC1_CR_CADB_BUF_7_VAL_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_7_VAL_MAX                                (1) // 0x00000001
  #define CH1_SC1_CR_CADB_BUF_7_VAL_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_7_VAL_HSH                                (0x4110D380)

  #define CH1_SC1_CR_CADB_BUF_7_PAR_OFF                                (17)
  #define CH1_SC1_CR_CADB_BUF_7_PAR_WID                                ( 1)
  #define CH1_SC1_CR_CADB_BUF_7_PAR_MSK                                (0x00020000)
  #define CH1_SC1_CR_CADB_BUF_7_PAR_MIN                                (0)
  #define CH1_SC1_CR_CADB_BUF_7_PAR_MAX                                (1) // 0x00000001
  #define CH1_SC1_CR_CADB_BUF_7_PAR_DEF                                (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_7_PAR_HSH                                (0x4111D380)

  #define CH1_SC1_CR_CADB_BUF_7_CA_OFF                                 (18)
  #define CH1_SC1_CR_CADB_BUF_7_CA_WID                                 (24)
  #define CH1_SC1_CR_CADB_BUF_7_CA_MSK                                 (0x000003FFFFFC0000ULL)
  #define CH1_SC1_CR_CADB_BUF_7_CA_MIN                                 (0)
  #define CH1_SC1_CR_CADB_BUF_7_CA_MAX                                 (16777215) // 0x00FFFFFF
  #define CH1_SC1_CR_CADB_BUF_7_CA_DEF                                 (0x00000000)
  #define CH1_SC1_CR_CADB_BUF_7_CA_HSH                                 (0x5812D380)

#define CH1_SC1_CR_CADB_AO_MRSCFG_REG                                  (0x0000D388)

  #define CH1_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_OFF                  ( 0)
  #define CH1_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_WID                  ( 1)
  #define CH1_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_MSK                  (0x00000001)
  #define CH1_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_MIN                  (0)
  #define CH1_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_MAX                  (1) // 0x00000001
  #define CH1_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_DEF                  (0x00000000)
  #define CH1_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_SCALE_HSH                  (0x0100D388)

  #define CH1_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_OFF                        ( 1)
  #define CH1_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_WID                        ( 4)
  #define CH1_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_MSK                        (0x0000001E)
  #define CH1_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_MIN                        (0)
  #define CH1_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_MAX                        (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_DEF                        (0x00000000)
  #define CH1_SC1_CR_CADB_AO_MRSCFG_MRS_GAP_HSH                        (0x0401D388)

  #define CH1_SC1_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_OFF                 ( 8)
  #define CH1_SC1_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_WID                 (16)
  #define CH1_SC1_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_MSK                 (0x00FFFF00)
  #define CH1_SC1_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_MIN                 (0)
  #define CH1_SC1_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_MAX                 (65535) // 0x0000FFFF
  #define CH1_SC1_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_DEF                 (0x00000000)
  #define CH1_SC1_CR_CADB_AO_MRSCFG_MRS_AO_REPEATS_HSH                 (0x1008D388)

#define CH1_SC1_CR_CADB_SELCFG_REG                                     (0x0000D390)

  #define CH1_SC1_CR_CADB_SELCFG_WR_SELECT_ENABLE_OFF                  ( 0)
  #define CH1_SC1_CR_CADB_SELCFG_WR_SELECT_ENABLE_WID                  ( 3)
  #define CH1_SC1_CR_CADB_SELCFG_WR_SELECT_ENABLE_MSK                  (0x00000007)
  #define CH1_SC1_CR_CADB_SELCFG_WR_SELECT_ENABLE_MIN                  (0)
  #define CH1_SC1_CR_CADB_SELCFG_WR_SELECT_ENABLE_MAX                  (7) // 0x00000007
  #define CH1_SC1_CR_CADB_SELCFG_WR_SELECT_ENABLE_DEF                  (0x00000000)
  #define CH1_SC1_CR_CADB_SELCFG_WR_SELECT_ENABLE_HSH                  (0x0300D390)

  #define CH1_SC1_CR_CADB_SELCFG_RD_SELECT_ENABLE_OFF                  ( 8)
  #define CH1_SC1_CR_CADB_SELCFG_RD_SELECT_ENABLE_WID                  ( 3)
  #define CH1_SC1_CR_CADB_SELCFG_RD_SELECT_ENABLE_MSK                  (0x00000700)
  #define CH1_SC1_CR_CADB_SELCFG_RD_SELECT_ENABLE_MIN                  (0)
  #define CH1_SC1_CR_CADB_SELCFG_RD_SELECT_ENABLE_MAX                  (7) // 0x00000007
  #define CH1_SC1_CR_CADB_SELCFG_RD_SELECT_ENABLE_DEF                  (0x00000000)
  #define CH1_SC1_CR_CADB_SELCFG_RD_SELECT_ENABLE_HSH                  (0x0308D390)

  #define CH1_SC1_CR_CADB_SELCFG_ACT_SELECT_ENABLE_OFF                 (16)
  #define CH1_SC1_CR_CADB_SELCFG_ACT_SELECT_ENABLE_WID                 ( 3)
  #define CH1_SC1_CR_CADB_SELCFG_ACT_SELECT_ENABLE_MSK                 (0x00070000)
  #define CH1_SC1_CR_CADB_SELCFG_ACT_SELECT_ENABLE_MIN                 (0)
  #define CH1_SC1_CR_CADB_SELCFG_ACT_SELECT_ENABLE_MAX                 (7) // 0x00000007
  #define CH1_SC1_CR_CADB_SELCFG_ACT_SELECT_ENABLE_DEF                 (0x00000000)
  #define CH1_SC1_CR_CADB_SELCFG_ACT_SELECT_ENABLE_HSH                 (0x0310D390)

  #define CH1_SC1_CR_CADB_SELCFG_PRE_SELECT_ENABLE_OFF                 (24)
  #define CH1_SC1_CR_CADB_SELCFG_PRE_SELECT_ENABLE_WID                 ( 3)
  #define CH1_SC1_CR_CADB_SELCFG_PRE_SELECT_ENABLE_MSK                 (0x07000000)
  #define CH1_SC1_CR_CADB_SELCFG_PRE_SELECT_ENABLE_MIN                 (0)
  #define CH1_SC1_CR_CADB_SELCFG_PRE_SELECT_ENABLE_MAX                 (7) // 0x00000007
  #define CH1_SC1_CR_CADB_SELCFG_PRE_SELECT_ENABLE_DEF                 (0x00000000)
  #define CH1_SC1_CR_CADB_SELCFG_PRE_SELECT_ENABLE_HSH                 (0x0318D390)

  #define CH1_SC1_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_OFF               (28)
  #define CH1_SC1_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_WID               ( 1)
  #define CH1_SC1_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_MSK               (0x10000000)
  #define CH1_SC1_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_MIN               (0)
  #define CH1_SC1_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_MAX               (1) // 0x00000001
  #define CH1_SC1_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_DEF               (0x00000001)
  #define CH1_SC1_CR_CADB_SELCFG_INITIAL_SEL_SSEQ_EN_HSH               (0x011CD390)

#define CH1_SC1_CR_CADB_MRSCFG_REG                                     (0x0000D398)

  #define CH1_SC1_CR_CADB_MRSCFG_CS_CLOCKS_OFF                         ( 0)
  #define CH1_SC1_CR_CADB_MRSCFG_CS_CLOCKS_WID                         ( 3)
  #define CH1_SC1_CR_CADB_MRSCFG_CS_CLOCKS_MSK                         (0x00000007)
  #define CH1_SC1_CR_CADB_MRSCFG_CS_CLOCKS_MIN                         (0)
  #define CH1_SC1_CR_CADB_MRSCFG_CS_CLOCKS_MAX                         (7) // 0x00000007
  #define CH1_SC1_CR_CADB_MRSCFG_CS_CLOCKS_DEF                         (0x00000000)
  #define CH1_SC1_CR_CADB_MRSCFG_CS_CLOCKS_HSH                         (0x4300D398)

  #define CH1_SC1_CR_CADB_MRSCFG_DSEL_CLOCKS_OFF                       ( 3)
  #define CH1_SC1_CR_CADB_MRSCFG_DSEL_CLOCKS_WID                       ( 4)
  #define CH1_SC1_CR_CADB_MRSCFG_DSEL_CLOCKS_MSK                       (0x00000078)
  #define CH1_SC1_CR_CADB_MRSCFG_DSEL_CLOCKS_MIN                       (0)
  #define CH1_SC1_CR_CADB_MRSCFG_DSEL_CLOCKS_MAX                       (15) // 0x0000000F
  #define CH1_SC1_CR_CADB_MRSCFG_DSEL_CLOCKS_DEF                       (0x00000000)
  #define CH1_SC1_CR_CADB_MRSCFG_DSEL_CLOCKS_HSH                       (0x4403D398)

  #define CH1_SC1_CR_CADB_MRSCFG_SETUP_CLOCKS_OFF                      ( 8)
  #define CH1_SC1_CR_CADB_MRSCFG_SETUP_CLOCKS_WID                      ( 3)
  #define CH1_SC1_CR_CADB_MRSCFG_SETUP_CLOCKS_MSK                      (0x00000700)
  #define CH1_SC1_CR_CADB_MRSCFG_SETUP_CLOCKS_MIN                      (0)
  #define CH1_SC1_CR_CADB_MRSCFG_SETUP_CLOCKS_MAX                      (7) // 0x00000007
  #define CH1_SC1_CR_CADB_MRSCFG_SETUP_CLOCKS_DEF                      (0x00000000)
  #define CH1_SC1_CR_CADB_MRSCFG_SETUP_CLOCKS_HSH                      (0x4308D398)

  #define CH1_SC1_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_OFF                (11)
  #define CH1_SC1_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_WID                ( 1)
  #define CH1_SC1_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_MSK                (0x00000800)
  #define CH1_SC1_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_MIN                (0)
  #define CH1_SC1_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_MAX                (1) // 0x00000001
  #define CH1_SC1_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_DEF                (0x00000000)
  #define CH1_SC1_CR_CADB_MRSCFG_CS_ACTIVE_POLARITY_HSH                (0x410BD398)

  #define CH1_SC1_CR_CADB_MRSCFG_MRS_START_PTR_OFF                     (12)
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_START_PTR_WID                     ( 3)
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_START_PTR_MSK                     (0x00007000)
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_START_PTR_MIN                     (0)
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_START_PTR_MAX                     (7) // 0x00000007
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_START_PTR_DEF                     (0x00000000)
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_START_PTR_HSH                     (0x430CD398)

  #define CH1_SC1_CR_CADB_MRSCFG_MRS_END_PTR_OFF                       (16)
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_END_PTR_WID                       ( 3)
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_END_PTR_MSK                       (0x00070000)
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_END_PTR_MIN                       (0)
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_END_PTR_MAX                       (7) // 0x00000007
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_END_PTR_DEF                       (0x00000000)
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_END_PTR_HSH                       (0x4310D398)

  #define CH1_SC1_CR_CADB_MRSCFG_MRS_GOTO_PTR_OFF                      (19)
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_GOTO_PTR_WID                      ( 3)
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_GOTO_PTR_MSK                      (0x00380000)
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_GOTO_PTR_MIN                      (0)
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_GOTO_PTR_MAX                      (7) // 0x00000007
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_GOTO_PTR_DEF                      (0x00000000)
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_GOTO_PTR_HSH                      (0x4313D398)

  #define CH1_SC1_CR_CADB_MRSCFG_MRS_CS_MODE_OFF                       (22)
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_CS_MODE_WID                       ( 2)
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_CS_MODE_MSK                       (0x00C00000)
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_CS_MODE_MIN                       (0)
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_CS_MODE_MAX                       (3) // 0x00000003
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_CS_MODE_DEF                       (0x00000000)
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_CS_MODE_HSH                       (0x4216D398)

  #define CH1_SC1_CR_CADB_MRSCFG_MRS_DELAY_CNT_OFF                     (24)
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_DELAY_CNT_WID                     (16)
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_DELAY_CNT_MSK                     (0x000000FFFF000000ULL)
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_DELAY_CNT_MIN                     (0)
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_DELAY_CNT_MAX                     (65535) // 0x0000FFFF
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_DELAY_CNT_DEF                     (0x00000000)
  #define CH1_SC1_CR_CADB_MRSCFG_MRS_DELAY_CNT_HSH                     (0x5018D398)

#define IBECC_ACTIVATE_REG                                             (0x0000DC00)

  #define IBECC_ACTIVATE_IBECC_EN_OFF                                  ( 0)
  #define IBECC_ACTIVATE_IBECC_EN_WID                                  ( 1)
  #define IBECC_ACTIVATE_IBECC_EN_MSK                                  (0x00000001)
  #define IBECC_ACTIVATE_IBECC_EN_MIN                                  (0)
  #define IBECC_ACTIVATE_IBECC_EN_MAX                                  (1) // 0x00000001
  #define IBECC_ACTIVATE_IBECC_EN_DEF                                  (0x00000000)
  #define IBECC_ACTIVATE_IBECC_EN_HSH                                  (0x0100DC00)

  #define IBECC_ACTIVATE_RSVD_OFF                                      ( 1)
  #define IBECC_ACTIVATE_RSVD_WID                                      (31)
  #define IBECC_ACTIVATE_RSVD_MSK                                      (0xFFFFFFFE)
  #define IBECC_ACTIVATE_RSVD_MIN                                      (0)
  #define IBECC_ACTIVATE_RSVD_MAX                                      (2147483647) // 0x7FFFFFFF
  #define IBECC_ACTIVATE_RSVD_DEF                                      (0x00000000)
  #define IBECC_ACTIVATE_RSVD_HSH                                      (0x1F01DC00)

#define IBECC_STATUS_REG                                               (0x0000DC04)

  #define IBECC_STATUS_IBECC_REQUESTOR_ISM_STATE_OFF                   ( 0)
  #define IBECC_STATUS_IBECC_REQUESTOR_ISM_STATE_WID                   ( 3)
  #define IBECC_STATUS_IBECC_REQUESTOR_ISM_STATE_MSK                   (0x00000007)
  #define IBECC_STATUS_IBECC_REQUESTOR_ISM_STATE_MIN                   (0)
  #define IBECC_STATUS_IBECC_REQUESTOR_ISM_STATE_MAX                   (7) // 0x00000007
  #define IBECC_STATUS_IBECC_REQUESTOR_ISM_STATE_DEF                   (0x00000000)
  #define IBECC_STATUS_IBECC_REQUESTOR_ISM_STATE_HSH                   (0x0300DC04)

  #define IBECC_STATUS_MC_RESPONDER_ISM_STATE_OFF                      ( 3)
  #define IBECC_STATUS_MC_RESPONDER_ISM_STATE_WID                      ( 3)
  #define IBECC_STATUS_MC_RESPONDER_ISM_STATE_MSK                      (0x00000038)
  #define IBECC_STATUS_MC_RESPONDER_ISM_STATE_MIN                      (0)
  #define IBECC_STATUS_MC_RESPONDER_ISM_STATE_MAX                      (7) // 0x00000007
  #define IBECC_STATUS_MC_RESPONDER_ISM_STATE_DEF                      (0x00000000)
  #define IBECC_STATUS_MC_RESPONDER_ISM_STATE_HSH                      (0x0303DC04)

  #define IBECC_STATUS_RPQ_FULL_OFF                                    ( 6)
  #define IBECC_STATUS_RPQ_FULL_WID                                    ( 1)
  #define IBECC_STATUS_RPQ_FULL_MSK                                    (0x00000040)
  #define IBECC_STATUS_RPQ_FULL_MIN                                    (0)
  #define IBECC_STATUS_RPQ_FULL_MAX                                    (1) // 0x00000001
  #define IBECC_STATUS_RPQ_FULL_DEF                                    (0x00000000)
  #define IBECC_STATUS_RPQ_FULL_HSH                                    (0x0106DC04)

  #define IBECC_STATUS_RPQ_EMPTY_OFF                                   ( 7)
  #define IBECC_STATUS_RPQ_EMPTY_WID                                   ( 1)
  #define IBECC_STATUS_RPQ_EMPTY_MSK                                   (0x00000080)
  #define IBECC_STATUS_RPQ_EMPTY_MIN                                   (0)
  #define IBECC_STATUS_RPQ_EMPTY_MAX                                   (1) // 0x00000001
  #define IBECC_STATUS_RPQ_EMPTY_DEF                                   (0x00000000)
  #define IBECC_STATUS_RPQ_EMPTY_HSH                                   (0x0107DC04)

  #define IBECC_STATUS_IPQ_FULL_OFF                                    ( 8)
  #define IBECC_STATUS_IPQ_FULL_WID                                    ( 1)
  #define IBECC_STATUS_IPQ_FULL_MSK                                    (0x00000100)
  #define IBECC_STATUS_IPQ_FULL_MIN                                    (0)
  #define IBECC_STATUS_IPQ_FULL_MAX                                    (1) // 0x00000001
  #define IBECC_STATUS_IPQ_FULL_DEF                                    (0x00000000)
  #define IBECC_STATUS_IPQ_FULL_HSH                                    (0x0108DC04)

  #define IBECC_STATUS_IPQ_EMPTY_OFF                                   ( 9)
  #define IBECC_STATUS_IPQ_EMPTY_WID                                   ( 1)
  #define IBECC_STATUS_IPQ_EMPTY_MSK                                   (0x00000200)
  #define IBECC_STATUS_IPQ_EMPTY_MIN                                   (0)
  #define IBECC_STATUS_IPQ_EMPTY_MAX                                   (1) // 0x00000001
  #define IBECC_STATUS_IPQ_EMPTY_DEF                                   (0x00000000)
  #define IBECC_STATUS_IPQ_EMPTY_HSH                                   (0x0109DC04)

  #define IBECC_STATUS_WPQ_FULL_OFF                                    (10)
  #define IBECC_STATUS_WPQ_FULL_WID                                    ( 1)
  #define IBECC_STATUS_WPQ_FULL_MSK                                    (0x00000400)
  #define IBECC_STATUS_WPQ_FULL_MIN                                    (0)
  #define IBECC_STATUS_WPQ_FULL_MAX                                    (1) // 0x00000001
  #define IBECC_STATUS_WPQ_FULL_DEF                                    (0x00000000)
  #define IBECC_STATUS_WPQ_FULL_HSH                                    (0x010ADC04)

  #define IBECC_STATUS_WPQ_EMPTY_OFF                                   (11)
  #define IBECC_STATUS_WPQ_EMPTY_WID                                   ( 1)
  #define IBECC_STATUS_WPQ_EMPTY_MSK                                   (0x00000800)
  #define IBECC_STATUS_WPQ_EMPTY_MIN                                   (0)
  #define IBECC_STATUS_WPQ_EMPTY_MAX                                   (1) // 0x00000001
  #define IBECC_STATUS_WPQ_EMPTY_DEF                                   (0x00000000)
  #define IBECC_STATUS_WPQ_EMPTY_HSH                                   (0x010BDC04)

  #define IBECC_STATUS_ECC_READ_TRACKER_FULL_OFF                       (12)
  #define IBECC_STATUS_ECC_READ_TRACKER_FULL_WID                       ( 1)
  #define IBECC_STATUS_ECC_READ_TRACKER_FULL_MSK                       (0x00001000)
  #define IBECC_STATUS_ECC_READ_TRACKER_FULL_MIN                       (0)
  #define IBECC_STATUS_ECC_READ_TRACKER_FULL_MAX                       (1) // 0x00000001
  #define IBECC_STATUS_ECC_READ_TRACKER_FULL_DEF                       (0x00000000)
  #define IBECC_STATUS_ECC_READ_TRACKER_FULL_HSH                       (0x010CDC04)

  #define IBECC_STATUS_ECC_READ_TRACKER_EMPTY_OFF                      (13)
  #define IBECC_STATUS_ECC_READ_TRACKER_EMPTY_WID                      ( 1)
  #define IBECC_STATUS_ECC_READ_TRACKER_EMPTY_MSK                      (0x00002000)
  #define IBECC_STATUS_ECC_READ_TRACKER_EMPTY_MIN                      (0)
  #define IBECC_STATUS_ECC_READ_TRACKER_EMPTY_MAX                      (1) // 0x00000001
  #define IBECC_STATUS_ECC_READ_TRACKER_EMPTY_DEF                      (0x00000000)
  #define IBECC_STATUS_ECC_READ_TRACKER_EMPTY_HSH                      (0x010DDC04)

  #define IBECC_STATUS_PROTECTED_WRITE_EXISTS_OFF                      (14)
  #define IBECC_STATUS_PROTECTED_WRITE_EXISTS_WID                      ( 1)
  #define IBECC_STATUS_PROTECTED_WRITE_EXISTS_MSK                      (0x00004000)
  #define IBECC_STATUS_PROTECTED_WRITE_EXISTS_MIN                      (0)
  #define IBECC_STATUS_PROTECTED_WRITE_EXISTS_MAX                      (1) // 0x00000001
  #define IBECC_STATUS_PROTECTED_WRITE_EXISTS_DEF                      (0x00000000)
  #define IBECC_STATUS_PROTECTED_WRITE_EXISTS_HSH                      (0x010EDC04)

  #define IBECC_STATUS_VC0_PROTECTED_READ_EXISTS_OFF                   (15)
  #define IBECC_STATUS_VC0_PROTECTED_READ_EXISTS_WID                   ( 1)
  #define IBECC_STATUS_VC0_PROTECTED_READ_EXISTS_MSK                   (0x00008000)
  #define IBECC_STATUS_VC0_PROTECTED_READ_EXISTS_MIN                   (0)
  #define IBECC_STATUS_VC0_PROTECTED_READ_EXISTS_MAX                   (1) // 0x00000001
  #define IBECC_STATUS_VC0_PROTECTED_READ_EXISTS_DEF                   (0x00000000)
  #define IBECC_STATUS_VC0_PROTECTED_READ_EXISTS_HSH                   (0x010FDC04)

  #define IBECC_STATUS_VC1_PROTECTED_READ_EXISTS_OFF                   (16)
  #define IBECC_STATUS_VC1_PROTECTED_READ_EXISTS_WID                   ( 1)
  #define IBECC_STATUS_VC1_PROTECTED_READ_EXISTS_MSK                   (0x00010000)
  #define IBECC_STATUS_VC1_PROTECTED_READ_EXISTS_MIN                   (0)
  #define IBECC_STATUS_VC1_PROTECTED_READ_EXISTS_MAX                   (1) // 0x00000001
  #define IBECC_STATUS_VC1_PROTECTED_READ_EXISTS_DEF                   (0x00000000)
  #define IBECC_STATUS_VC1_PROTECTED_READ_EXISTS_HSH                   (0x0110DC04)

  #define IBECC_STATUS_WAR_HAZARD_EXISTS_OFF                           (17)
  #define IBECC_STATUS_WAR_HAZARD_EXISTS_WID                           ( 1)
  #define IBECC_STATUS_WAR_HAZARD_EXISTS_MSK                           (0x00020000)
  #define IBECC_STATUS_WAR_HAZARD_EXISTS_MIN                           (0)
  #define IBECC_STATUS_WAR_HAZARD_EXISTS_MAX                           (1) // 0x00000001
  #define IBECC_STATUS_WAR_HAZARD_EXISTS_DEF                           (0x00000000)
  #define IBECC_STATUS_WAR_HAZARD_EXISTS_HSH                           (0x0111DC04)

  #define IBECC_STATUS_RAW_HAZARD_EXISTS_OFF                           (18)
  #define IBECC_STATUS_RAW_HAZARD_EXISTS_WID                           ( 1)
  #define IBECC_STATUS_RAW_HAZARD_EXISTS_MSK                           (0x00040000)
  #define IBECC_STATUS_RAW_HAZARD_EXISTS_MIN                           (0)
  #define IBECC_STATUS_RAW_HAZARD_EXISTS_MAX                           (1) // 0x00000001
  #define IBECC_STATUS_RAW_HAZARD_EXISTS_DEF                           (0x00000000)
  #define IBECC_STATUS_RAW_HAZARD_EXISTS_HSH                           (0x0112DC04)

  #define IBECC_STATUS_WAW_HAZARD_EXISTS_OFF                           (19)
  #define IBECC_STATUS_WAW_HAZARD_EXISTS_WID                           ( 1)
  #define IBECC_STATUS_WAW_HAZARD_EXISTS_MSK                           (0x00080000)
  #define IBECC_STATUS_WAW_HAZARD_EXISTS_MIN                           (0)
  #define IBECC_STATUS_WAW_HAZARD_EXISTS_MAX                           (1) // 0x00000001
  #define IBECC_STATUS_WAW_HAZARD_EXISTS_DEF                           (0x00000000)
  #define IBECC_STATUS_WAW_HAZARD_EXISTS_HSH                           (0x0113DC04)

  #define IBECC_STATUS_CMI_REQUESTOR_ISM_STATE_OFF                     (20)
  #define IBECC_STATUS_CMI_REQUESTOR_ISM_STATE_WID                     ( 3)
  #define IBECC_STATUS_CMI_REQUESTOR_ISM_STATE_MSK                     (0x00700000)
  #define IBECC_STATUS_CMI_REQUESTOR_ISM_STATE_MIN                     (0)
  #define IBECC_STATUS_CMI_REQUESTOR_ISM_STATE_MAX                     (7) // 0x00000007
  #define IBECC_STATUS_CMI_REQUESTOR_ISM_STATE_DEF                     (0x00000000)
  #define IBECC_STATUS_CMI_REQUESTOR_ISM_STATE_HSH                     (0x0314DC04)

  #define IBECC_STATUS_IBECC_RESPONDER_ISM_STATE_OFF                   (23)
  #define IBECC_STATUS_IBECC_RESPONDER_ISM_STATE_WID                   ( 3)
  #define IBECC_STATUS_IBECC_RESPONDER_ISM_STATE_MSK                   (0x03800000)
  #define IBECC_STATUS_IBECC_RESPONDER_ISM_STATE_MIN                   (0)
  #define IBECC_STATUS_IBECC_RESPONDER_ISM_STATE_MAX                   (7) // 0x00000007
  #define IBECC_STATUS_IBECC_RESPONDER_ISM_STATE_DEF                   (0x00000000)
  #define IBECC_STATUS_IBECC_RESPONDER_ISM_STATE_HSH                   (0x0317DC04)

  #define IBECC_STATUS_RSVD_OFF                                        (26)
  #define IBECC_STATUS_RSVD_WID                                        ( 6)
  #define IBECC_STATUS_RSVD_MSK                                        (0xFC000000)
  #define IBECC_STATUS_RSVD_MIN                                        (0)
  #define IBECC_STATUS_RSVD_MAX                                        (63) // 0x0000003F
  #define IBECC_STATUS_RSVD_DEF                                        (0x00000000)
  #define IBECC_STATUS_RSVD_HSH                                        (0x061ADC04)

#define IBECC_IOSF_SB_EP_CTRL_REG                                      (0x0000DC08)

  #define IBECC_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEDEF_OFF                  ( 0)
  #define IBECC_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEDEF_WID                  ( 1)
  #define IBECC_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEDEF_MSK                  (0x00000001)
  #define IBECC_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEDEF_MIN                  (0)
  #define IBECC_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEDEF_MAX                  (1) // 0x00000001
  #define IBECC_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEDEF_DEF                  (0x00000000)
  #define IBECC_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEDEF_HSH                  (0x0100DC08)

  #define IBECC_IOSF_SB_EP_CTRL_RSVD0_OFF                              ( 1)
  #define IBECC_IOSF_SB_EP_CTRL_RSVD0_WID                              ( 7)
  #define IBECC_IOSF_SB_EP_CTRL_RSVD0_MSK                              (0x000000FE)
  #define IBECC_IOSF_SB_EP_CTRL_RSVD0_MIN                              (0)
  #define IBECC_IOSF_SB_EP_CTRL_RSVD0_MAX                              (127) // 0x0000007F
  #define IBECC_IOSF_SB_EP_CTRL_RSVD0_DEF                              (0x00000000)
  #define IBECC_IOSF_SB_EP_CTRL_RSVD0_HSH                              (0x0701DC08)

  #define IBECC_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEN_OFF                    ( 8)
  #define IBECC_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEN_WID                    ( 1)
  #define IBECC_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEN_MSK                    (0x00000100)
  #define IBECC_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEN_MIN                    (0)
  #define IBECC_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEN_MAX                    (1) // 0x00000001
  #define IBECC_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEN_DEF                    (0x00000001)
  #define IBECC_IOSF_SB_EP_CTRL_CGCTRL_CLKGATEN_HSH                    (0x0108DC08)

  #define IBECC_IOSF_SB_EP_CTRL_RSVD1_OFF                              ( 9)
  #define IBECC_IOSF_SB_EP_CTRL_RSVD1_WID                              ( 7)
  #define IBECC_IOSF_SB_EP_CTRL_RSVD1_MSK                              (0x0000FE00)
  #define IBECC_IOSF_SB_EP_CTRL_RSVD1_MIN                              (0)
  #define IBECC_IOSF_SB_EP_CTRL_RSVD1_MAX                              (127) // 0x0000007F
  #define IBECC_IOSF_SB_EP_CTRL_RSVD1_DEF                              (0x00000000)
  #define IBECC_IOSF_SB_EP_CTRL_RSVD1_HSH                              (0x0709DC08)

  #define IBECC_IOSF_SB_EP_CTRL_CGCTRL_IDLECNT_OFF                     (16)
  #define IBECC_IOSF_SB_EP_CTRL_CGCTRL_IDLECNT_WID                     ( 8)
  #define IBECC_IOSF_SB_EP_CTRL_CGCTRL_IDLECNT_MSK                     (0x00FF0000)
  #define IBECC_IOSF_SB_EP_CTRL_CGCTRL_IDLECNT_MIN                     (0)
  #define IBECC_IOSF_SB_EP_CTRL_CGCTRL_IDLECNT_MAX                     (255) // 0x000000FF
  #define IBECC_IOSF_SB_EP_CTRL_CGCTRL_IDLECNT_DEF                     (0x00000010)
  #define IBECC_IOSF_SB_EP_CTRL_CGCTRL_IDLECNT_HSH                     (0x0810DC08)

  #define IBECC_IOSF_SB_EP_CTRL_RSVD2_OFF                              (24)
  #define IBECC_IOSF_SB_EP_CTRL_RSVD2_WID                              ( 8)
  #define IBECC_IOSF_SB_EP_CTRL_RSVD2_MSK                              (0xFF000000)
  #define IBECC_IOSF_SB_EP_CTRL_RSVD2_MIN                              (0)
  #define IBECC_IOSF_SB_EP_CTRL_RSVD2_MAX                              (255) // 0x000000FF
  #define IBECC_IOSF_SB_EP_CTRL_RSVD2_DEF                              (0x00000000)
  #define IBECC_IOSF_SB_EP_CTRL_RSVD2_HSH                              (0x0818DC08)

#define IBECC_PROTECT_ADDR_RANGE_0_REG                                 (0x0000DC0C)

  #define IBECC_PROTECT_ADDR_RANGE_0_BASE_OFF                          ( 0)
  #define IBECC_PROTECT_ADDR_RANGE_0_BASE_WID                          (14)
  #define IBECC_PROTECT_ADDR_RANGE_0_BASE_MSK                          (0x00003FFF)
  #define IBECC_PROTECT_ADDR_RANGE_0_BASE_MIN                          (0)
  #define IBECC_PROTECT_ADDR_RANGE_0_BASE_MAX                          (16383) // 0x00003FFF
  #define IBECC_PROTECT_ADDR_RANGE_0_BASE_DEF                          (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_0_BASE_HSH                          (0x0E00DC0C)

  #define IBECC_PROTECT_ADDR_RANGE_0_RSVD1_OFF                         (15)
  #define IBECC_PROTECT_ADDR_RANGE_0_RSVD1_WID                         ( 1)
  #define IBECC_PROTECT_ADDR_RANGE_0_RSVD1_MSK                         (0x00008000)
  #define IBECC_PROTECT_ADDR_RANGE_0_RSVD1_MIN                         (0)
  #define IBECC_PROTECT_ADDR_RANGE_0_RSVD1_MAX                         (1) // 0x00000001
  #define IBECC_PROTECT_ADDR_RANGE_0_RSVD1_DEF                         (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_0_RSVD1_HSH                         (0x010FDC0C)

  #define IBECC_PROTECT_ADDR_RANGE_0_MASK_OFF                          (16)
  #define IBECC_PROTECT_ADDR_RANGE_0_MASK_WID                          (14)
  #define IBECC_PROTECT_ADDR_RANGE_0_MASK_MSK                          (0x3FFF0000)
  #define IBECC_PROTECT_ADDR_RANGE_0_MASK_MIN                          (0)
  #define IBECC_PROTECT_ADDR_RANGE_0_MASK_MAX                          (16383) // 0x00003FFF
  #define IBECC_PROTECT_ADDR_RANGE_0_MASK_DEF                          (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_0_MASK_HSH                          (0x0E10DC0C)

  #define IBECC_PROTECT_ADDR_RANGE_0_RSVD2_OFF                         (30)
  #define IBECC_PROTECT_ADDR_RANGE_0_RSVD2_WID                         ( 1)
  #define IBECC_PROTECT_ADDR_RANGE_0_RSVD2_MSK                         (0x40000000)
  #define IBECC_PROTECT_ADDR_RANGE_0_RSVD2_MIN                         (0)
  #define IBECC_PROTECT_ADDR_RANGE_0_RSVD2_MAX                         (1) // 0x00000001
  #define IBECC_PROTECT_ADDR_RANGE_0_RSVD2_DEF                         (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_0_RSVD2_HSH                         (0x011EDC0C)

  #define IBECC_PROTECT_ADDR_RANGE_0_RANGE_EN_OFF                      (31)
  #define IBECC_PROTECT_ADDR_RANGE_0_RANGE_EN_WID                      ( 1)
  #define IBECC_PROTECT_ADDR_RANGE_0_RANGE_EN_MSK                      (0x80000000)
  #define IBECC_PROTECT_ADDR_RANGE_0_RANGE_EN_MIN                      (0)
  #define IBECC_PROTECT_ADDR_RANGE_0_RANGE_EN_MAX                      (1) // 0x00000001
  #define IBECC_PROTECT_ADDR_RANGE_0_RANGE_EN_DEF                      (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_0_RANGE_EN_HSH                      (0x011FDC0C)

#define IBECC_PROTECT_ADDR_RANGE_1_REG                                 (0x0000DC10)

  #define IBECC_PROTECT_ADDR_RANGE_1_BASE_OFF                          ( 0)
  #define IBECC_PROTECT_ADDR_RANGE_1_BASE_WID                          (14)
  #define IBECC_PROTECT_ADDR_RANGE_1_BASE_MSK                          (0x00003FFF)
  #define IBECC_PROTECT_ADDR_RANGE_1_BASE_MIN                          (0)
  #define IBECC_PROTECT_ADDR_RANGE_1_BASE_MAX                          (16383) // 0x00003FFF
  #define IBECC_PROTECT_ADDR_RANGE_1_BASE_DEF                          (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_1_BASE_HSH                          (0x0E00DC10)

  #define IBECC_PROTECT_ADDR_RANGE_1_RSVD1_OFF                         (15)
  #define IBECC_PROTECT_ADDR_RANGE_1_RSVD1_WID                         ( 1)
  #define IBECC_PROTECT_ADDR_RANGE_1_RSVD1_MSK                         (0x00008000)
  #define IBECC_PROTECT_ADDR_RANGE_1_RSVD1_MIN                         (0)
  #define IBECC_PROTECT_ADDR_RANGE_1_RSVD1_MAX                         (1) // 0x00000001
  #define IBECC_PROTECT_ADDR_RANGE_1_RSVD1_DEF                         (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_1_RSVD1_HSH                         (0x010FDC10)

  #define IBECC_PROTECT_ADDR_RANGE_1_MASK_OFF                          (16)
  #define IBECC_PROTECT_ADDR_RANGE_1_MASK_WID                          (14)
  #define IBECC_PROTECT_ADDR_RANGE_1_MASK_MSK                          (0x3FFF0000)
  #define IBECC_PROTECT_ADDR_RANGE_1_MASK_MIN                          (0)
  #define IBECC_PROTECT_ADDR_RANGE_1_MASK_MAX                          (16383) // 0x00003FFF
  #define IBECC_PROTECT_ADDR_RANGE_1_MASK_DEF                          (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_1_MASK_HSH                          (0x0E10DC10)

  #define IBECC_PROTECT_ADDR_RANGE_1_RSVD2_OFF                         (30)
  #define IBECC_PROTECT_ADDR_RANGE_1_RSVD2_WID                         ( 1)
  #define IBECC_PROTECT_ADDR_RANGE_1_RSVD2_MSK                         (0x40000000)
  #define IBECC_PROTECT_ADDR_RANGE_1_RSVD2_MIN                         (0)
  #define IBECC_PROTECT_ADDR_RANGE_1_RSVD2_MAX                         (1) // 0x00000001
  #define IBECC_PROTECT_ADDR_RANGE_1_RSVD2_DEF                         (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_1_RSVD2_HSH                         (0x011EDC10)

  #define IBECC_PROTECT_ADDR_RANGE_1_RANGE_EN_OFF                      (31)
  #define IBECC_PROTECT_ADDR_RANGE_1_RANGE_EN_WID                      ( 1)
  #define IBECC_PROTECT_ADDR_RANGE_1_RANGE_EN_MSK                      (0x80000000)
  #define IBECC_PROTECT_ADDR_RANGE_1_RANGE_EN_MIN                      (0)
  #define IBECC_PROTECT_ADDR_RANGE_1_RANGE_EN_MAX                      (1) // 0x00000001
  #define IBECC_PROTECT_ADDR_RANGE_1_RANGE_EN_DEF                      (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_1_RANGE_EN_HSH                      (0x011FDC10)

#define IBECC_PROTECT_ADDR_RANGE_2_REG                                 (0x0000DC14)

  #define IBECC_PROTECT_ADDR_RANGE_2_BASE_OFF                          ( 0)
  #define IBECC_PROTECT_ADDR_RANGE_2_BASE_WID                          (14)
  #define IBECC_PROTECT_ADDR_RANGE_2_BASE_MSK                          (0x00003FFF)
  #define IBECC_PROTECT_ADDR_RANGE_2_BASE_MIN                          (0)
  #define IBECC_PROTECT_ADDR_RANGE_2_BASE_MAX                          (16383) // 0x00003FFF
  #define IBECC_PROTECT_ADDR_RANGE_2_BASE_DEF                          (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_2_BASE_HSH                          (0x0E00DC14)

  #define IBECC_PROTECT_ADDR_RANGE_2_RSVD1_OFF                         (15)
  #define IBECC_PROTECT_ADDR_RANGE_2_RSVD1_WID                         ( 1)
  #define IBECC_PROTECT_ADDR_RANGE_2_RSVD1_MSK                         (0x00008000)
  #define IBECC_PROTECT_ADDR_RANGE_2_RSVD1_MIN                         (0)
  #define IBECC_PROTECT_ADDR_RANGE_2_RSVD1_MAX                         (1) // 0x00000001
  #define IBECC_PROTECT_ADDR_RANGE_2_RSVD1_DEF                         (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_2_RSVD1_HSH                         (0x010FDC14)

  #define IBECC_PROTECT_ADDR_RANGE_2_MASK_OFF                          (16)
  #define IBECC_PROTECT_ADDR_RANGE_2_MASK_WID                          (14)
  #define IBECC_PROTECT_ADDR_RANGE_2_MASK_MSK                          (0x3FFF0000)
  #define IBECC_PROTECT_ADDR_RANGE_2_MASK_MIN                          (0)
  #define IBECC_PROTECT_ADDR_RANGE_2_MASK_MAX                          (16383) // 0x00003FFF
  #define IBECC_PROTECT_ADDR_RANGE_2_MASK_DEF                          (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_2_MASK_HSH                          (0x0E10DC14)

  #define IBECC_PROTECT_ADDR_RANGE_2_RSVD2_OFF                         (30)
  #define IBECC_PROTECT_ADDR_RANGE_2_RSVD2_WID                         ( 1)
  #define IBECC_PROTECT_ADDR_RANGE_2_RSVD2_MSK                         (0x40000000)
  #define IBECC_PROTECT_ADDR_RANGE_2_RSVD2_MIN                         (0)
  #define IBECC_PROTECT_ADDR_RANGE_2_RSVD2_MAX                         (1) // 0x00000001
  #define IBECC_PROTECT_ADDR_RANGE_2_RSVD2_DEF                         (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_2_RSVD2_HSH                         (0x011EDC14)

  #define IBECC_PROTECT_ADDR_RANGE_2_RANGE_EN_OFF                      (31)
  #define IBECC_PROTECT_ADDR_RANGE_2_RANGE_EN_WID                      ( 1)
  #define IBECC_PROTECT_ADDR_RANGE_2_RANGE_EN_MSK                      (0x80000000)
  #define IBECC_PROTECT_ADDR_RANGE_2_RANGE_EN_MIN                      (0)
  #define IBECC_PROTECT_ADDR_RANGE_2_RANGE_EN_MAX                      (1) // 0x00000001
  #define IBECC_PROTECT_ADDR_RANGE_2_RANGE_EN_DEF                      (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_2_RANGE_EN_HSH                      (0x011FDC14)

#define IBECC_PROTECT_ADDR_RANGE_3_REG                                 (0x0000DC18)

  #define IBECC_PROTECT_ADDR_RANGE_3_BASE_OFF                          ( 0)
  #define IBECC_PROTECT_ADDR_RANGE_3_BASE_WID                          (14)
  #define IBECC_PROTECT_ADDR_RANGE_3_BASE_MSK                          (0x00003FFF)
  #define IBECC_PROTECT_ADDR_RANGE_3_BASE_MIN                          (0)
  #define IBECC_PROTECT_ADDR_RANGE_3_BASE_MAX                          (16383) // 0x00003FFF
  #define IBECC_PROTECT_ADDR_RANGE_3_BASE_DEF                          (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_3_BASE_HSH                          (0x0E00DC18)

  #define IBECC_PROTECT_ADDR_RANGE_3_RSVD1_OFF                         (15)
  #define IBECC_PROTECT_ADDR_RANGE_3_RSVD1_WID                         ( 1)
  #define IBECC_PROTECT_ADDR_RANGE_3_RSVD1_MSK                         (0x00008000)
  #define IBECC_PROTECT_ADDR_RANGE_3_RSVD1_MIN                         (0)
  #define IBECC_PROTECT_ADDR_RANGE_3_RSVD1_MAX                         (1) // 0x00000001
  #define IBECC_PROTECT_ADDR_RANGE_3_RSVD1_DEF                         (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_3_RSVD1_HSH                         (0x010FDC18)

  #define IBECC_PROTECT_ADDR_RANGE_3_MASK_OFF                          (16)
  #define IBECC_PROTECT_ADDR_RANGE_3_MASK_WID                          (14)
  #define IBECC_PROTECT_ADDR_RANGE_3_MASK_MSK                          (0x3FFF0000)
  #define IBECC_PROTECT_ADDR_RANGE_3_MASK_MIN                          (0)
  #define IBECC_PROTECT_ADDR_RANGE_3_MASK_MAX                          (16383) // 0x00003FFF
  #define IBECC_PROTECT_ADDR_RANGE_3_MASK_DEF                          (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_3_MASK_HSH                          (0x0E10DC18)

  #define IBECC_PROTECT_ADDR_RANGE_3_RSVD2_OFF                         (30)
  #define IBECC_PROTECT_ADDR_RANGE_3_RSVD2_WID                         ( 1)
  #define IBECC_PROTECT_ADDR_RANGE_3_RSVD2_MSK                         (0x40000000)
  #define IBECC_PROTECT_ADDR_RANGE_3_RSVD2_MIN                         (0)
  #define IBECC_PROTECT_ADDR_RANGE_3_RSVD2_MAX                         (1) // 0x00000001
  #define IBECC_PROTECT_ADDR_RANGE_3_RSVD2_DEF                         (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_3_RSVD2_HSH                         (0x011EDC18)

  #define IBECC_PROTECT_ADDR_RANGE_3_RANGE_EN_OFF                      (31)
  #define IBECC_PROTECT_ADDR_RANGE_3_RANGE_EN_WID                      ( 1)
  #define IBECC_PROTECT_ADDR_RANGE_3_RANGE_EN_MSK                      (0x80000000)
  #define IBECC_PROTECT_ADDR_RANGE_3_RANGE_EN_MIN                      (0)
  #define IBECC_PROTECT_ADDR_RANGE_3_RANGE_EN_MAX                      (1) // 0x00000001
  #define IBECC_PROTECT_ADDR_RANGE_3_RANGE_EN_DEF                      (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_3_RANGE_EN_HSH                      (0x011FDC18)

#define IBECC_PROTECT_ADDR_RANGE_4_REG                                 (0x0000DC1C)

  #define IBECC_PROTECT_ADDR_RANGE_4_BASE_OFF                          ( 0)
  #define IBECC_PROTECT_ADDR_RANGE_4_BASE_WID                          (14)
  #define IBECC_PROTECT_ADDR_RANGE_4_BASE_MSK                          (0x00003FFF)
  #define IBECC_PROTECT_ADDR_RANGE_4_BASE_MIN                          (0)
  #define IBECC_PROTECT_ADDR_RANGE_4_BASE_MAX                          (16383) // 0x00003FFF
  #define IBECC_PROTECT_ADDR_RANGE_4_BASE_DEF                          (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_4_BASE_HSH                          (0x0E00DC1C)

  #define IBECC_PROTECT_ADDR_RANGE_4_RSVD1_OFF                         (15)
  #define IBECC_PROTECT_ADDR_RANGE_4_RSVD1_WID                         ( 1)
  #define IBECC_PROTECT_ADDR_RANGE_4_RSVD1_MSK                         (0x00008000)
  #define IBECC_PROTECT_ADDR_RANGE_4_RSVD1_MIN                         (0)
  #define IBECC_PROTECT_ADDR_RANGE_4_RSVD1_MAX                         (1) // 0x00000001
  #define IBECC_PROTECT_ADDR_RANGE_4_RSVD1_DEF                         (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_4_RSVD1_HSH                         (0x010FDC1C)

  #define IBECC_PROTECT_ADDR_RANGE_4_MASK_OFF                          (16)
  #define IBECC_PROTECT_ADDR_RANGE_4_MASK_WID                          (14)
  #define IBECC_PROTECT_ADDR_RANGE_4_MASK_MSK                          (0x3FFF0000)
  #define IBECC_PROTECT_ADDR_RANGE_4_MASK_MIN                          (0)
  #define IBECC_PROTECT_ADDR_RANGE_4_MASK_MAX                          (16383) // 0x00003FFF
  #define IBECC_PROTECT_ADDR_RANGE_4_MASK_DEF                          (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_4_MASK_HSH                          (0x0E10DC1C)

  #define IBECC_PROTECT_ADDR_RANGE_4_RSVD2_OFF                         (30)
  #define IBECC_PROTECT_ADDR_RANGE_4_RSVD2_WID                         ( 1)
  #define IBECC_PROTECT_ADDR_RANGE_4_RSVD2_MSK                         (0x40000000)
  #define IBECC_PROTECT_ADDR_RANGE_4_RSVD2_MIN                         (0)
  #define IBECC_PROTECT_ADDR_RANGE_4_RSVD2_MAX                         (1) // 0x00000001
  #define IBECC_PROTECT_ADDR_RANGE_4_RSVD2_DEF                         (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_4_RSVD2_HSH                         (0x011EDC1C)

  #define IBECC_PROTECT_ADDR_RANGE_4_RANGE_EN_OFF                      (31)
  #define IBECC_PROTECT_ADDR_RANGE_4_RANGE_EN_WID                      ( 1)
  #define IBECC_PROTECT_ADDR_RANGE_4_RANGE_EN_MSK                      (0x80000000)
  #define IBECC_PROTECT_ADDR_RANGE_4_RANGE_EN_MIN                      (0)
  #define IBECC_PROTECT_ADDR_RANGE_4_RANGE_EN_MAX                      (1) // 0x00000001
  #define IBECC_PROTECT_ADDR_RANGE_4_RANGE_EN_DEF                      (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_4_RANGE_EN_HSH                      (0x011FDC1C)

#define IBECC_PROTECT_ADDR_RANGE_5_REG                                 (0x0000DC20)

  #define IBECC_PROTECT_ADDR_RANGE_5_BASE_OFF                          ( 0)
  #define IBECC_PROTECT_ADDR_RANGE_5_BASE_WID                          (14)
  #define IBECC_PROTECT_ADDR_RANGE_5_BASE_MSK                          (0x00003FFF)
  #define IBECC_PROTECT_ADDR_RANGE_5_BASE_MIN                          (0)
  #define IBECC_PROTECT_ADDR_RANGE_5_BASE_MAX                          (16383) // 0x00003FFF
  #define IBECC_PROTECT_ADDR_RANGE_5_BASE_DEF                          (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_5_BASE_HSH                          (0x0E00DC20)

  #define IBECC_PROTECT_ADDR_RANGE_5_RSVD1_OFF                         (15)
  #define IBECC_PROTECT_ADDR_RANGE_5_RSVD1_WID                         ( 1)
  #define IBECC_PROTECT_ADDR_RANGE_5_RSVD1_MSK                         (0x00008000)
  #define IBECC_PROTECT_ADDR_RANGE_5_RSVD1_MIN                         (0)
  #define IBECC_PROTECT_ADDR_RANGE_5_RSVD1_MAX                         (1) // 0x00000001
  #define IBECC_PROTECT_ADDR_RANGE_5_RSVD1_DEF                         (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_5_RSVD1_HSH                         (0x010FDC20)

  #define IBECC_PROTECT_ADDR_RANGE_5_MASK_OFF                          (16)
  #define IBECC_PROTECT_ADDR_RANGE_5_MASK_WID                          (14)
  #define IBECC_PROTECT_ADDR_RANGE_5_MASK_MSK                          (0x3FFF0000)
  #define IBECC_PROTECT_ADDR_RANGE_5_MASK_MIN                          (0)
  #define IBECC_PROTECT_ADDR_RANGE_5_MASK_MAX                          (16383) // 0x00003FFF
  #define IBECC_PROTECT_ADDR_RANGE_5_MASK_DEF                          (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_5_MASK_HSH                          (0x0E10DC20)

  #define IBECC_PROTECT_ADDR_RANGE_5_RSVD2_OFF                         (30)
  #define IBECC_PROTECT_ADDR_RANGE_5_RSVD2_WID                         ( 1)
  #define IBECC_PROTECT_ADDR_RANGE_5_RSVD2_MSK                         (0x40000000)
  #define IBECC_PROTECT_ADDR_RANGE_5_RSVD2_MIN                         (0)
  #define IBECC_PROTECT_ADDR_RANGE_5_RSVD2_MAX                         (1) // 0x00000001
  #define IBECC_PROTECT_ADDR_RANGE_5_RSVD2_DEF                         (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_5_RSVD2_HSH                         (0x011EDC20)

  #define IBECC_PROTECT_ADDR_RANGE_5_RANGE_EN_OFF                      (31)
  #define IBECC_PROTECT_ADDR_RANGE_5_RANGE_EN_WID                      ( 1)
  #define IBECC_PROTECT_ADDR_RANGE_5_RANGE_EN_MSK                      (0x80000000)
  #define IBECC_PROTECT_ADDR_RANGE_5_RANGE_EN_MIN                      (0)
  #define IBECC_PROTECT_ADDR_RANGE_5_RANGE_EN_MAX                      (1) // 0x00000001
  #define IBECC_PROTECT_ADDR_RANGE_5_RANGE_EN_DEF                      (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_5_RANGE_EN_HSH                      (0x011FDC20)

#define IBECC_PROTECT_ADDR_RANGE_6_REG                                 (0x0000DC24)

  #define IBECC_PROTECT_ADDR_RANGE_6_BASE_OFF                          ( 0)
  #define IBECC_PROTECT_ADDR_RANGE_6_BASE_WID                          (14)
  #define IBECC_PROTECT_ADDR_RANGE_6_BASE_MSK                          (0x00003FFF)
  #define IBECC_PROTECT_ADDR_RANGE_6_BASE_MIN                          (0)
  #define IBECC_PROTECT_ADDR_RANGE_6_BASE_MAX                          (16383) // 0x00003FFF
  #define IBECC_PROTECT_ADDR_RANGE_6_BASE_DEF                          (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_6_BASE_HSH                          (0x0E00DC24)

  #define IBECC_PROTECT_ADDR_RANGE_6_RSVD1_OFF                         (15)
  #define IBECC_PROTECT_ADDR_RANGE_6_RSVD1_WID                         ( 1)
  #define IBECC_PROTECT_ADDR_RANGE_6_RSVD1_MSK                         (0x00008000)
  #define IBECC_PROTECT_ADDR_RANGE_6_RSVD1_MIN                         (0)
  #define IBECC_PROTECT_ADDR_RANGE_6_RSVD1_MAX                         (1) // 0x00000001
  #define IBECC_PROTECT_ADDR_RANGE_6_RSVD1_DEF                         (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_6_RSVD1_HSH                         (0x010FDC24)

  #define IBECC_PROTECT_ADDR_RANGE_6_MASK_OFF                          (16)
  #define IBECC_PROTECT_ADDR_RANGE_6_MASK_WID                          (14)
  #define IBECC_PROTECT_ADDR_RANGE_6_MASK_MSK                          (0x3FFF0000)
  #define IBECC_PROTECT_ADDR_RANGE_6_MASK_MIN                          (0)
  #define IBECC_PROTECT_ADDR_RANGE_6_MASK_MAX                          (16383) // 0x00003FFF
  #define IBECC_PROTECT_ADDR_RANGE_6_MASK_DEF                          (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_6_MASK_HSH                          (0x0E10DC24)

  #define IBECC_PROTECT_ADDR_RANGE_6_RSVD2_OFF                         (30)
  #define IBECC_PROTECT_ADDR_RANGE_6_RSVD2_WID                         ( 1)
  #define IBECC_PROTECT_ADDR_RANGE_6_RSVD2_MSK                         (0x40000000)
  #define IBECC_PROTECT_ADDR_RANGE_6_RSVD2_MIN                         (0)
  #define IBECC_PROTECT_ADDR_RANGE_6_RSVD2_MAX                         (1) // 0x00000001
  #define IBECC_PROTECT_ADDR_RANGE_6_RSVD2_DEF                         (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_6_RSVD2_HSH                         (0x011EDC24)

  #define IBECC_PROTECT_ADDR_RANGE_6_RANGE_EN_OFF                      (31)
  #define IBECC_PROTECT_ADDR_RANGE_6_RANGE_EN_WID                      ( 1)
  #define IBECC_PROTECT_ADDR_RANGE_6_RANGE_EN_MSK                      (0x80000000)
  #define IBECC_PROTECT_ADDR_RANGE_6_RANGE_EN_MIN                      (0)
  #define IBECC_PROTECT_ADDR_RANGE_6_RANGE_EN_MAX                      (1) // 0x00000001
  #define IBECC_PROTECT_ADDR_RANGE_6_RANGE_EN_DEF                      (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_6_RANGE_EN_HSH                      (0x011FDC24)

#define IBECC_PROTECT_ADDR_RANGE_7_REG                                 (0x0000DC28)

  #define IBECC_PROTECT_ADDR_RANGE_7_BASE_OFF                          ( 0)
  #define IBECC_PROTECT_ADDR_RANGE_7_BASE_WID                          (14)
  #define IBECC_PROTECT_ADDR_RANGE_7_BASE_MSK                          (0x00003FFF)
  #define IBECC_PROTECT_ADDR_RANGE_7_BASE_MIN                          (0)
  #define IBECC_PROTECT_ADDR_RANGE_7_BASE_MAX                          (16383) // 0x00003FFF
  #define IBECC_PROTECT_ADDR_RANGE_7_BASE_DEF                          (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_7_BASE_HSH                          (0x0E00DC28)

  #define IBECC_PROTECT_ADDR_RANGE_7_RSVD1_OFF                         (15)
  #define IBECC_PROTECT_ADDR_RANGE_7_RSVD1_WID                         ( 1)
  #define IBECC_PROTECT_ADDR_RANGE_7_RSVD1_MSK                         (0x00008000)
  #define IBECC_PROTECT_ADDR_RANGE_7_RSVD1_MIN                         (0)
  #define IBECC_PROTECT_ADDR_RANGE_7_RSVD1_MAX                         (1) // 0x00000001
  #define IBECC_PROTECT_ADDR_RANGE_7_RSVD1_DEF                         (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_7_RSVD1_HSH                         (0x010FDC28)

  #define IBECC_PROTECT_ADDR_RANGE_7_MASK_OFF                          (16)
  #define IBECC_PROTECT_ADDR_RANGE_7_MASK_WID                          (14)
  #define IBECC_PROTECT_ADDR_RANGE_7_MASK_MSK                          (0x3FFF0000)
  #define IBECC_PROTECT_ADDR_RANGE_7_MASK_MIN                          (0)
  #define IBECC_PROTECT_ADDR_RANGE_7_MASK_MAX                          (16383) // 0x00003FFF
  #define IBECC_PROTECT_ADDR_RANGE_7_MASK_DEF                          (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_7_MASK_HSH                          (0x0E10DC28)

  #define IBECC_PROTECT_ADDR_RANGE_7_RSVD2_OFF                         (30)
  #define IBECC_PROTECT_ADDR_RANGE_7_RSVD2_WID                         ( 1)
  #define IBECC_PROTECT_ADDR_RANGE_7_RSVD2_MSK                         (0x40000000)
  #define IBECC_PROTECT_ADDR_RANGE_7_RSVD2_MIN                         (0)
  #define IBECC_PROTECT_ADDR_RANGE_7_RSVD2_MAX                         (1) // 0x00000001
  #define IBECC_PROTECT_ADDR_RANGE_7_RSVD2_DEF                         (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_7_RSVD2_HSH                         (0x011EDC28)

  #define IBECC_PROTECT_ADDR_RANGE_7_RANGE_EN_OFF                      (31)
  #define IBECC_PROTECT_ADDR_RANGE_7_RANGE_EN_WID                      ( 1)
  #define IBECC_PROTECT_ADDR_RANGE_7_RANGE_EN_MSK                      (0x80000000)
  #define IBECC_PROTECT_ADDR_RANGE_7_RANGE_EN_MIN                      (0)
  #define IBECC_PROTECT_ADDR_RANGE_7_RANGE_EN_MAX                      (1) // 0x00000001
  #define IBECC_PROTECT_ADDR_RANGE_7_RANGE_EN_DEF                      (0x00000000)
  #define IBECC_PROTECT_ADDR_RANGE_7_RANGE_EN_HSH                      (0x011FDC28)

#define IBECC_ECC_STORAGE_ADDR_REG                                     (0x0000DC2C)

  #define IBECC_ECC_STORAGE_ADDR_ADDRESS_OFF                           ( 0)
  #define IBECC_ECC_STORAGE_ADDR_ADDRESS_WID                           (15)
  #define IBECC_ECC_STORAGE_ADDR_ADDRESS_MSK                           (0x00007FFF)
  #define IBECC_ECC_STORAGE_ADDR_ADDRESS_MIN                           (0)
  #define IBECC_ECC_STORAGE_ADDR_ADDRESS_MAX                           (32767) // 0x00007FFF
  #define IBECC_ECC_STORAGE_ADDR_ADDRESS_DEF                           (0x00000000)
  #define IBECC_ECC_STORAGE_ADDR_ADDRESS_HSH                           (0x0F00DC2C)

  #define IBECC_ECC_STORAGE_ADDR_RSVD_OFF                              (15)
  #define IBECC_ECC_STORAGE_ADDR_RSVD_WID                              (17)
  #define IBECC_ECC_STORAGE_ADDR_RSVD_MSK                              (0xFFFF8000)
  #define IBECC_ECC_STORAGE_ADDR_RSVD_MIN                              (0)
  #define IBECC_ECC_STORAGE_ADDR_RSVD_MAX                              (131071) // 0x0001FFFF
  #define IBECC_ECC_STORAGE_ADDR_RSVD_DEF                              (0x00000000)
  #define IBECC_ECC_STORAGE_ADDR_RSVD_HSH                              (0x110FDC2C)

#define IBECC_DEFAULT_PG_CP_REG                                        (0x0000DC30)

  #define IBECC_DEFAULT_PG_CP_SAI_MASK_OFF                             ( 0)
  #define IBECC_DEFAULT_PG_CP_SAI_MASK_WID                             (64)
  #define IBECC_DEFAULT_PG_CP_SAI_MASK_MSK                             (0xFFFFFFFFFFFFFFFFULL)
  #define IBECC_DEFAULT_PG_CP_SAI_MASK_MIN                             (0)
  #define IBECC_DEFAULT_PG_CP_SAI_MASK_MAX                             (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define IBECC_DEFAULT_PG_CP_SAI_MASK_DEF                             (0x40001000208)
  #define IBECC_DEFAULT_PG_CP_SAI_MASK_HSH                             (0x4000DC30)

#define IBECC_DEFAULT_PG_RAC_REG                                       (0x0000DC38)

  #define IBECC_DEFAULT_PG_RAC_SAI_MASK_OFF                            ( 0)
  #define IBECC_DEFAULT_PG_RAC_SAI_MASK_WID                            (64)
  #define IBECC_DEFAULT_PG_RAC_SAI_MASK_MSK                            (0xFFFFFFFFFFFFFFFFULL)
  #define IBECC_DEFAULT_PG_RAC_SAI_MASK_MIN                            (0)
  #define IBECC_DEFAULT_PG_RAC_SAI_MASK_MAX                            (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define IBECC_DEFAULT_PG_RAC_SAI_MASK_DEF                            (0xFFFFFFFFFFFFFFFF)
  #define IBECC_DEFAULT_PG_RAC_SAI_MASK_HSH                            (0x4000DC38)

#define IBECC_DEFAULT_PG_WAC_REG                                       (0x0000DC40)

  #define IBECC_DEFAULT_PG_WAC_SAI_MASK_OFF                            ( 0)
  #define IBECC_DEFAULT_PG_WAC_SAI_MASK_WID                            (64)
  #define IBECC_DEFAULT_PG_WAC_SAI_MASK_MSK                            (0xFFFFFFFFFFFFFFFFULL)
  #define IBECC_DEFAULT_PG_WAC_SAI_MASK_MIN                            (0)
  #define IBECC_DEFAULT_PG_WAC_SAI_MASK_MAX                            (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define IBECC_DEFAULT_PG_WAC_SAI_MASK_DEF                            (0x4000100061A)
  #define IBECC_DEFAULT_PG_WAC_SAI_MASK_HSH                            (0x4000DC40)

#define IBECC_DEBUG_PG_CP_REG                                          (0x0000DC48)

  #define IBECC_DEBUG_PG_CP_SAI_MASK_OFF                               ( 0)
  #define IBECC_DEBUG_PG_CP_SAI_MASK_WID                               (64)
  #define IBECC_DEBUG_PG_CP_SAI_MASK_MSK                               (0xFFFFFFFFFFFFFFFFULL)
  #define IBECC_DEBUG_PG_CP_SAI_MASK_MIN                               (0)
  #define IBECC_DEBUG_PG_CP_SAI_MASK_MAX                               (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define IBECC_DEBUG_PG_CP_SAI_MASK_DEF                               (0x40001000208)
  #define IBECC_DEBUG_PG_CP_SAI_MASK_HSH                               (0x4000DC48)

#define IBECC_DEBUG_PG_RAC_REG                                         (0x0000DC50)

  #define IBECC_DEBUG_PG_RAC_SAI_MASK_OFF                              ( 0)
  #define IBECC_DEBUG_PG_RAC_SAI_MASK_WID                              (64)
  #define IBECC_DEBUG_PG_RAC_SAI_MASK_MSK                              (0xFFFFFFFFFFFFFFFFULL)
  #define IBECC_DEBUG_PG_RAC_SAI_MASK_MIN                              (0)
  #define IBECC_DEBUG_PG_RAC_SAI_MASK_MAX                              (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define IBECC_DEBUG_PG_RAC_SAI_MASK_DEF                              (0xFFFFFFFFFFFFFFFF)
  #define IBECC_DEBUG_PG_RAC_SAI_MASK_HSH                              (0x4000DC50)

#define IBECC_DEBUG_PG_WAC_REG                                         (0x0000DC58)

  #define IBECC_DEBUG_PG_WAC_SAI_MASK_OFF                              ( 0)
  #define IBECC_DEBUG_PG_WAC_SAI_MASK_WID                              (64)
  #define IBECC_DEBUG_PG_WAC_SAI_MASK_MSK                              (0xFFFFFFFFFFFFFFFFULL)
  #define IBECC_DEBUG_PG_WAC_SAI_MASK_MIN                              (0)
  #define IBECC_DEBUG_PG_WAC_SAI_MASK_MAX                              (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define IBECC_DEBUG_PG_WAC_SAI_MASK_DEF                              (0x4000300061A)
  #define IBECC_DEBUG_PG_WAC_SAI_MASK_HSH                              (0x4000DC58)

#define IBECC_OS_PG_CP_REG                                             (0x0000DC60)

  #define IBECC_OS_PG_CP_SAI_MASK_OFF                                  ( 0)
  #define IBECC_OS_PG_CP_SAI_MASK_WID                                  (64)
  #define IBECC_OS_PG_CP_SAI_MASK_MSK                                  (0xFFFFFFFFFFFFFFFFULL)
  #define IBECC_OS_PG_CP_SAI_MASK_MIN                                  (0)
  #define IBECC_OS_PG_CP_SAI_MASK_MAX                                  (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define IBECC_OS_PG_CP_SAI_MASK_DEF                                  (0x40001000208)
  #define IBECC_OS_PG_CP_SAI_MASK_HSH                                  (0x4000DC60)

#define IBECC_OS_PG_RAC_REG                                            (0x0000DC68)

  #define IBECC_OS_PG_RAC_SAI_MASK_OFF                                 ( 0)
  #define IBECC_OS_PG_RAC_SAI_MASK_WID                                 (64)
  #define IBECC_OS_PG_RAC_SAI_MASK_MSK                                 (0xFFFFFFFFFFFFFFFFULL)
  #define IBECC_OS_PG_RAC_SAI_MASK_MIN                                 (0)
  #define IBECC_OS_PG_RAC_SAI_MASK_MAX                                 (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define IBECC_OS_PG_RAC_SAI_MASK_DEF                                 (0xFFFFFFFFFFFFFFFF)
  #define IBECC_OS_PG_RAC_SAI_MASK_HSH                                 (0x4000DC68)

#define IBECC_OS_PG_WAC_REG                                            (0x0000DC70)

  #define IBECC_OS_PG_WAC_SAI_MASK_OFF                                 ( 0)
  #define IBECC_OS_PG_WAC_SAI_MASK_WID                                 (64)
  #define IBECC_OS_PG_WAC_SAI_MASK_MSK                                 (0xFFFFFFFFFFFFFFFFULL)
  #define IBECC_OS_PG_WAC_SAI_MASK_MIN                                 (0)
  #define IBECC_OS_PG_WAC_SAI_MASK_MAX                                 (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define IBECC_OS_PG_WAC_SAI_MASK_DEF                                 (0x4000100061B)
  #define IBECC_OS_PG_WAC_SAI_MASK_HSH                                 (0x4000DC70)

#define IBECC_PRIO_LIM_REG                                             (0x0000DC78)

  #define IBECC_PRIO_LIM_LOW_PRIORITY_LIM_OFF                          ( 0)
  #define IBECC_PRIO_LIM_LOW_PRIORITY_LIM_WID                          (16)
  #define IBECC_PRIO_LIM_LOW_PRIORITY_LIM_MSK                          (0x0000FFFF)
  #define IBECC_PRIO_LIM_LOW_PRIORITY_LIM_MIN                          (0)
  #define IBECC_PRIO_LIM_LOW_PRIORITY_LIM_MAX                          (65535) // 0x0000FFFF
  #define IBECC_PRIO_LIM_LOW_PRIORITY_LIM_DEF                          (0x00000001)
  #define IBECC_PRIO_LIM_LOW_PRIORITY_LIM_HSH                          (0x1000DC78)

  #define IBECC_PRIO_LIM_HIGH_PRIORITY_LIM_OFF                         (16)
  #define IBECC_PRIO_LIM_HIGH_PRIORITY_LIM_WID                         (16)
  #define IBECC_PRIO_LIM_HIGH_PRIORITY_LIM_MSK                         (0xFFFF0000)
  #define IBECC_PRIO_LIM_HIGH_PRIORITY_LIM_MIN                         (0)
  #define IBECC_PRIO_LIM_HIGH_PRIORITY_LIM_MAX                         (65535) // 0x0000FFFF
  #define IBECC_PRIO_LIM_HIGH_PRIORITY_LIM_DEF                         (0x00000004)
  #define IBECC_PRIO_LIM_HIGH_PRIORITY_LIM_HSH                         (0x1010DC78)

#define IBECC_CLK_GATE_EN_0_REG                                        (0x0000DC7C)

  #define IBECC_CLK_GATE_EN_0_CLK_GATE_EN_OFF                          ( 0)
  #define IBECC_CLK_GATE_EN_0_CLK_GATE_EN_WID                          (32)
  #define IBECC_CLK_GATE_EN_0_CLK_GATE_EN_MSK                          (0xFFFFFFFF)
  #define IBECC_CLK_GATE_EN_0_CLK_GATE_EN_MIN                          (0)
  #define IBECC_CLK_GATE_EN_0_CLK_GATE_EN_MAX                          (4294967295) // 0xFFFFFFFF
  #define IBECC_CLK_GATE_EN_0_CLK_GATE_EN_DEF                          (0xFFFFFFFF)
  #define IBECC_CLK_GATE_EN_0_CLK_GATE_EN_HSH                          (0x2000DC7C)

#define IBECC_REQ_CREDIT_CONFIG_CHANNEL_0_REG                          (0x0000DC80)

  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_0_RESERVED0_OFF              ( 0)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_0_RESERVED0_WID              (16)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_0_RESERVED0_MSK              (0x0000FFFF)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_0_RESERVED0_MIN              (0)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_0_RESERVED0_MAX              (65535) // 0x0000FFFF
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_0_RESERVED0_DEF              (0x00000000)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_0_RESERVED0_HSH              (0x1000DC80)

  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_0_REQ_WR_MAX_CREDIT_OFF      (16)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_0_REQ_WR_MAX_CREDIT_WID      ( 8)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_0_REQ_WR_MAX_CREDIT_MSK      (0x00FF0000)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_0_REQ_WR_MAX_CREDIT_MIN      (0)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_0_REQ_WR_MAX_CREDIT_MAX      (255) // 0x000000FF
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_0_REQ_WR_MAX_CREDIT_DEF      (0x00000024)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_0_REQ_WR_MAX_CREDIT_HSH      (0x0810DC80)

  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_0_REQ_RD_MAX_CREDIT_OFF      (24)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_0_REQ_RD_MAX_CREDIT_WID      ( 8)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_0_REQ_RD_MAX_CREDIT_MSK      (0xFF000000)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_0_REQ_RD_MAX_CREDIT_MIN      (0)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_0_REQ_RD_MAX_CREDIT_MAX      (255) // 0x000000FF
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_0_REQ_RD_MAX_CREDIT_DEF      (0x00000020)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_0_REQ_RD_MAX_CREDIT_HSH      (0x0818DC80)

#define IBECC_REQ_CREDIT_CONFIG_CHANNEL_1_REG                          (0x0000DC84)

  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_1_RESERVED0_OFF              ( 0)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_1_RESERVED0_WID              (16)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_1_RESERVED0_MSK              (0x0000FFFF)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_1_RESERVED0_MIN              (0)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_1_RESERVED0_MAX              (65535) // 0x0000FFFF
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_1_RESERVED0_DEF              (0x00000000)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_1_RESERVED0_HSH              (0x1000DC84)

  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_1_REQ_WR_MAX_CREDIT_OFF      (16)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_1_REQ_WR_MAX_CREDIT_WID      ( 8)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_1_REQ_WR_MAX_CREDIT_MSK      (0x00FF0000)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_1_REQ_WR_MAX_CREDIT_MIN      (0)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_1_REQ_WR_MAX_CREDIT_MAX      (255) // 0x000000FF
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_1_REQ_WR_MAX_CREDIT_DEF      (0x00000020)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_1_REQ_WR_MAX_CREDIT_HSH      (0x0810DC84)

  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_1_REQ_RD_MAX_CREDIT_OFF      (24)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_1_REQ_RD_MAX_CREDIT_WID      ( 8)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_1_REQ_RD_MAX_CREDIT_MSK      (0xFF000000)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_1_REQ_RD_MAX_CREDIT_MIN      (0)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_1_REQ_RD_MAX_CREDIT_MAX      (255) // 0x000000FF
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_1_REQ_RD_MAX_CREDIT_DEF      (0x00000010)
  #define IBECC_REQ_CREDIT_CONFIG_CHANNEL_1_REQ_RD_MAX_CREDIT_HSH      (0x0818DC84)

#define IBECC_REQ_TOTAL_CREDIT_CONFIG_REG                              (0x0000DC88)

  #define IBECC_REQ_TOTAL_CREDIT_CONFIG_REQ_WR_QUEUEDEPTH_OFF          ( 0)
  #define IBECC_REQ_TOTAL_CREDIT_CONFIG_REQ_WR_QUEUEDEPTH_WID          ( 8)
  #define IBECC_REQ_TOTAL_CREDIT_CONFIG_REQ_WR_QUEUEDEPTH_MSK          (0x000000FF)
  #define IBECC_REQ_TOTAL_CREDIT_CONFIG_REQ_WR_QUEUEDEPTH_MIN          (0)
  #define IBECC_REQ_TOTAL_CREDIT_CONFIG_REQ_WR_QUEUEDEPTH_MAX          (255) // 0x000000FF
  #define IBECC_REQ_TOTAL_CREDIT_CONFIG_REQ_WR_QUEUEDEPTH_DEF          (0x00000028)
  #define IBECC_REQ_TOTAL_CREDIT_CONFIG_REQ_WR_QUEUEDEPTH_HSH          (0x0800DC88)

  #define IBECC_REQ_TOTAL_CREDIT_CONFIG_REQ_RD_QUEUEDEPTH_OFF          ( 8)
  #define IBECC_REQ_TOTAL_CREDIT_CONFIG_REQ_RD_QUEUEDEPTH_WID          ( 8)
  #define IBECC_REQ_TOTAL_CREDIT_CONFIG_REQ_RD_QUEUEDEPTH_MSK          (0x0000FF00)
  #define IBECC_REQ_TOTAL_CREDIT_CONFIG_REQ_RD_QUEUEDEPTH_MIN          (0)
  #define IBECC_REQ_TOTAL_CREDIT_CONFIG_REQ_RD_QUEUEDEPTH_MAX          (255) // 0x000000FF
  #define IBECC_REQ_TOTAL_CREDIT_CONFIG_REQ_RD_QUEUEDEPTH_DEF          (0x00000030)
  #define IBECC_REQ_TOTAL_CREDIT_CONFIG_REQ_RD_QUEUEDEPTH_HSH          (0x0808DC88)

  #define IBECC_REQ_TOTAL_CREDIT_CONFIG_RESERVED1_OFF                  (16)
  #define IBECC_REQ_TOTAL_CREDIT_CONFIG_RESERVED1_WID                  (16)
  #define IBECC_REQ_TOTAL_CREDIT_CONFIG_RESERVED1_MSK                  (0xFFFF0000)
  #define IBECC_REQ_TOTAL_CREDIT_CONFIG_RESERVED1_MIN                  (0)
  #define IBECC_REQ_TOTAL_CREDIT_CONFIG_RESERVED1_MAX                  (65535) // 0x0000FFFF
  #define IBECC_REQ_TOTAL_CREDIT_CONFIG_RESERVED1_DEF                  (0x00000000)
  #define IBECC_REQ_TOTAL_CREDIT_CONFIG_RESERVED1_HSH                  (0x1010DC88)

#define IBECC_REQUEST_PORT_STALL_REG                                   (0x0000DC8C)

  #define IBECC_REQUEST_PORT_STALL_REQ_STALL_OFF                       ( 0)
  #define IBECC_REQUEST_PORT_STALL_REQ_STALL_WID                       ( 1)
  #define IBECC_REQUEST_PORT_STALL_REQ_STALL_MSK                       (0x00000001)
  #define IBECC_REQUEST_PORT_STALL_REQ_STALL_MIN                       (0)
  #define IBECC_REQUEST_PORT_STALL_REQ_STALL_MAX                       (1) // 0x00000001
  #define IBECC_REQUEST_PORT_STALL_REQ_STALL_DEF                       (0x00000000)
  #define IBECC_REQUEST_PORT_STALL_REQ_STALL_HSH                       (0x0100DC8C)

  #define IBECC_REQUEST_PORT_STALL_RSVD0_OFF                           ( 1)
  #define IBECC_REQUEST_PORT_STALL_RSVD0_WID                           ( 4)
  #define IBECC_REQUEST_PORT_STALL_RSVD0_MSK                           (0x0000001E)
  #define IBECC_REQUEST_PORT_STALL_RSVD0_MIN                           (0)
  #define IBECC_REQUEST_PORT_STALL_RSVD0_MAX                           (15) // 0x0000000F
  #define IBECC_REQUEST_PORT_STALL_RSVD0_DEF                           (0x00000000)
  #define IBECC_REQUEST_PORT_STALL_RSVD0_HSH                           (0x0401DC8C)

  #define IBECC_REQUEST_PORT_STALL_RSVD1_OFF                           ( 5)
  #define IBECC_REQUEST_PORT_STALL_RSVD1_WID                           ( 3)
  #define IBECC_REQUEST_PORT_STALL_RSVD1_MSK                           (0x000000E0)
  #define IBECC_REQUEST_PORT_STALL_RSVD1_MIN                           (0)
  #define IBECC_REQUEST_PORT_STALL_RSVD1_MAX                           (7) // 0x00000007
  #define IBECC_REQUEST_PORT_STALL_RSVD1_DEF                           (0x00000000)
  #define IBECC_REQUEST_PORT_STALL_RSVD1_HSH                           (0x0305DC8C)

  #define IBECC_REQUEST_PORT_STALL_UNSTALL_COUNTER_VALUE_OFF           ( 8)
  #define IBECC_REQUEST_PORT_STALL_UNSTALL_COUNTER_VALUE_WID           (16)
  #define IBECC_REQUEST_PORT_STALL_UNSTALL_COUNTER_VALUE_MSK           (0x00FFFF00)
  #define IBECC_REQUEST_PORT_STALL_UNSTALL_COUNTER_VALUE_MIN           (0)
  #define IBECC_REQUEST_PORT_STALL_UNSTALL_COUNTER_VALUE_MAX           (65535) // 0x0000FFFF
  #define IBECC_REQUEST_PORT_STALL_UNSTALL_COUNTER_VALUE_DEF           (0x00000000)
  #define IBECC_REQUEST_PORT_STALL_UNSTALL_COUNTER_VALUE_HSH           (0x1008DC8C)

#define IBECC_MBIST_POST_CTRL_WDB_REG                                  (0x0000DC90)

  #define IBECC_MBIST_POST_CTRL_WDB_PASS_OFF                           ( 0)
  #define IBECC_MBIST_POST_CTRL_WDB_PASS_WID                           ( 1)
  #define IBECC_MBIST_POST_CTRL_WDB_PASS_MSK                           (0x00000001)
  #define IBECC_MBIST_POST_CTRL_WDB_PASS_MIN                           (0)
  #define IBECC_MBIST_POST_CTRL_WDB_PASS_MAX                           (1) // 0x00000001
  #define IBECC_MBIST_POST_CTRL_WDB_PASS_DEF                           (0x00000000)
  #define IBECC_MBIST_POST_CTRL_WDB_PASS_HSH                           (0x0100DC90)

  #define IBECC_MBIST_POST_CTRL_WDB_COMPLETE_OFF                       ( 1)
  #define IBECC_MBIST_POST_CTRL_WDB_COMPLETE_WID                       ( 1)
  #define IBECC_MBIST_POST_CTRL_WDB_COMPLETE_MSK                       (0x00000002)
  #define IBECC_MBIST_POST_CTRL_WDB_COMPLETE_MIN                       (0)
  #define IBECC_MBIST_POST_CTRL_WDB_COMPLETE_MAX                       (1) // 0x00000001
  #define IBECC_MBIST_POST_CTRL_WDB_COMPLETE_DEF                       (0x00000000)
  #define IBECC_MBIST_POST_CTRL_WDB_COMPLETE_HSH                       (0x0101DC90)

  #define IBECC_MBIST_POST_CTRL_WDB_RSVD1_OFF                          ( 2)
  #define IBECC_MBIST_POST_CTRL_WDB_RSVD1_WID                          ( 6)
  #define IBECC_MBIST_POST_CTRL_WDB_RSVD1_MSK                          (0x000000FC)
  #define IBECC_MBIST_POST_CTRL_WDB_RSVD1_MIN                          (0)
  #define IBECC_MBIST_POST_CTRL_WDB_RSVD1_MAX                          (63) // 0x0000003F
  #define IBECC_MBIST_POST_CTRL_WDB_RSVD1_DEF                          (0x00000000)
  #define IBECC_MBIST_POST_CTRL_WDB_RSVD1_HSH                          (0x0602DC90)

  #define IBECC_MBIST_POST_CTRL_WDB_MBIST_FAIL_INJECT_OFF              ( 8)
  #define IBECC_MBIST_POST_CTRL_WDB_MBIST_FAIL_INJECT_WID              ( 1)
  #define IBECC_MBIST_POST_CTRL_WDB_MBIST_FAIL_INJECT_MSK              (0x00000100)
  #define IBECC_MBIST_POST_CTRL_WDB_MBIST_FAIL_INJECT_MIN              (0)
  #define IBECC_MBIST_POST_CTRL_WDB_MBIST_FAIL_INJECT_MAX              (1) // 0x00000001
  #define IBECC_MBIST_POST_CTRL_WDB_MBIST_FAIL_INJECT_DEF              (0x00000000)
  #define IBECC_MBIST_POST_CTRL_WDB_MBIST_FAIL_INJECT_HSH              (0x0108DC90)

  #define IBECC_MBIST_POST_CTRL_WDB_RSVD2_OFF                          ( 9)
  #define IBECC_MBIST_POST_CTRL_WDB_RSVD2_WID                          (22)
  #define IBECC_MBIST_POST_CTRL_WDB_RSVD2_MSK                          (0x7FFFFE00)
  #define IBECC_MBIST_POST_CTRL_WDB_RSVD2_MIN                          (0)
  #define IBECC_MBIST_POST_CTRL_WDB_RSVD2_MAX                          (4194303) // 0x003FFFFF
  #define IBECC_MBIST_POST_CTRL_WDB_RSVD2_DEF                          (0x00000000)
  #define IBECC_MBIST_POST_CTRL_WDB_RSVD2_HSH                          (0x1609DC90)

  #define IBECC_MBIST_POST_CTRL_WDB_RUN_BUSY_OFF                       (31)
  #define IBECC_MBIST_POST_CTRL_WDB_RUN_BUSY_WID                       ( 1)
  #define IBECC_MBIST_POST_CTRL_WDB_RUN_BUSY_MSK                       (0x80000000)
  #define IBECC_MBIST_POST_CTRL_WDB_RUN_BUSY_MIN                       (0)
  #define IBECC_MBIST_POST_CTRL_WDB_RUN_BUSY_MAX                       (1) // 0x00000001
  #define IBECC_MBIST_POST_CTRL_WDB_RUN_BUSY_DEF                       (0x00000000)
  #define IBECC_MBIST_POST_CTRL_WDB_RUN_BUSY_HSH                       (0x011FDC90)

#define IBECC_MBIST_POST_CTRL_RDB_REG                                  (0x0000DC94)

  #define IBECC_MBIST_POST_CTRL_RDB_PASS_OFF                           ( 0)
  #define IBECC_MBIST_POST_CTRL_RDB_PASS_WID                           ( 1)
  #define IBECC_MBIST_POST_CTRL_RDB_PASS_MSK                           (0x00000001)
  #define IBECC_MBIST_POST_CTRL_RDB_PASS_MIN                           (0)
  #define IBECC_MBIST_POST_CTRL_RDB_PASS_MAX                           (1) // 0x00000001
  #define IBECC_MBIST_POST_CTRL_RDB_PASS_DEF                           (0x00000000)
  #define IBECC_MBIST_POST_CTRL_RDB_PASS_HSH                           (0x0100DC94)

  #define IBECC_MBIST_POST_CTRL_RDB_COMPLETE_OFF                       ( 1)
  #define IBECC_MBIST_POST_CTRL_RDB_COMPLETE_WID                       ( 1)
  #define IBECC_MBIST_POST_CTRL_RDB_COMPLETE_MSK                       (0x00000002)
  #define IBECC_MBIST_POST_CTRL_RDB_COMPLETE_MIN                       (0)
  #define IBECC_MBIST_POST_CTRL_RDB_COMPLETE_MAX                       (1) // 0x00000001
  #define IBECC_MBIST_POST_CTRL_RDB_COMPLETE_DEF                       (0x00000000)
  #define IBECC_MBIST_POST_CTRL_RDB_COMPLETE_HSH                       (0x0101DC94)

  #define IBECC_MBIST_POST_CTRL_RDB_RSVD1_OFF                          ( 2)
  #define IBECC_MBIST_POST_CTRL_RDB_RSVD1_WID                          ( 6)
  #define IBECC_MBIST_POST_CTRL_RDB_RSVD1_MSK                          (0x000000FC)
  #define IBECC_MBIST_POST_CTRL_RDB_RSVD1_MIN                          (0)
  #define IBECC_MBIST_POST_CTRL_RDB_RSVD1_MAX                          (63) // 0x0000003F
  #define IBECC_MBIST_POST_CTRL_RDB_RSVD1_DEF                          (0x00000000)
  #define IBECC_MBIST_POST_CTRL_RDB_RSVD1_HSH                          (0x0602DC94)

  #define IBECC_MBIST_POST_CTRL_RDB_MBIST_FAIL_INJECT_OFF              ( 8)
  #define IBECC_MBIST_POST_CTRL_RDB_MBIST_FAIL_INJECT_WID              ( 1)
  #define IBECC_MBIST_POST_CTRL_RDB_MBIST_FAIL_INJECT_MSK              (0x00000100)
  #define IBECC_MBIST_POST_CTRL_RDB_MBIST_FAIL_INJECT_MIN              (0)
  #define IBECC_MBIST_POST_CTRL_RDB_MBIST_FAIL_INJECT_MAX              (1) // 0x00000001
  #define IBECC_MBIST_POST_CTRL_RDB_MBIST_FAIL_INJECT_DEF              (0x00000000)
  #define IBECC_MBIST_POST_CTRL_RDB_MBIST_FAIL_INJECT_HSH              (0x0108DC94)

  #define IBECC_MBIST_POST_CTRL_RDB_RSVD2_OFF                          ( 9)
  #define IBECC_MBIST_POST_CTRL_RDB_RSVD2_WID                          (22)
  #define IBECC_MBIST_POST_CTRL_RDB_RSVD2_MSK                          (0x7FFFFE00)
  #define IBECC_MBIST_POST_CTRL_RDB_RSVD2_MIN                          (0)
  #define IBECC_MBIST_POST_CTRL_RDB_RSVD2_MAX                          (4194303) // 0x003FFFFF
  #define IBECC_MBIST_POST_CTRL_RDB_RSVD2_DEF                          (0x00000000)
  #define IBECC_MBIST_POST_CTRL_RDB_RSVD2_HSH                          (0x1609DC94)

  #define IBECC_MBIST_POST_CTRL_RDB_RUN_BUSY_OFF                       (31)
  #define IBECC_MBIST_POST_CTRL_RDB_RUN_BUSY_WID                       ( 1)
  #define IBECC_MBIST_POST_CTRL_RDB_RUN_BUSY_MSK                       (0x80000000)
  #define IBECC_MBIST_POST_CTRL_RDB_RUN_BUSY_MIN                       (0)
  #define IBECC_MBIST_POST_CTRL_RDB_RUN_BUSY_MAX                       (1) // 0x00000001
  #define IBECC_MBIST_POST_CTRL_RDB_RUN_BUSY_DEF                       (0x00000000)
  #define IBECC_MBIST_POST_CTRL_RDB_RUN_BUSY_HSH                       (0x011FDC94)

#define IBECC_PARITY_CONTROL_REG                                       (0x0000DC98)

  #define IBECC_PARITY_CONTROL_RDATA_PARITY_CHK_EN_OFF                 ( 0)
  #define IBECC_PARITY_CONTROL_RDATA_PARITY_CHK_EN_WID                 ( 1)
  #define IBECC_PARITY_CONTROL_RDATA_PARITY_CHK_EN_MSK                 (0x00000001)
  #define IBECC_PARITY_CONTROL_RDATA_PARITY_CHK_EN_MIN                 (0)
  #define IBECC_PARITY_CONTROL_RDATA_PARITY_CHK_EN_MAX                 (1) // 0x00000001
  #define IBECC_PARITY_CONTROL_RDATA_PARITY_CHK_EN_DEF                 (0x00000001)
  #define IBECC_PARITY_CONTROL_RDATA_PARITY_CHK_EN_HSH                 (0x0100DC98)

  #define IBECC_PARITY_CONTROL_WBE_PARITY_CHK_EN_OFF                   ( 1)
  #define IBECC_PARITY_CONTROL_WBE_PARITY_CHK_EN_WID                   ( 1)
  #define IBECC_PARITY_CONTROL_WBE_PARITY_CHK_EN_MSK                   (0x00000002)
  #define IBECC_PARITY_CONTROL_WBE_PARITY_CHK_EN_MIN                   (0)
  #define IBECC_PARITY_CONTROL_WBE_PARITY_CHK_EN_MAX                   (1) // 0x00000001
  #define IBECC_PARITY_CONTROL_WBE_PARITY_CHK_EN_DEF                   (0x00000001)
  #define IBECC_PARITY_CONTROL_WBE_PARITY_CHK_EN_HSH                   (0x0101DC98)

  #define IBECC_PARITY_CONTROL_WDATA_PARITY_CHK_EN_OFF                 ( 2)
  #define IBECC_PARITY_CONTROL_WDATA_PARITY_CHK_EN_WID                 ( 1)
  #define IBECC_PARITY_CONTROL_WDATA_PARITY_CHK_EN_MSK                 (0x00000004)
  #define IBECC_PARITY_CONTROL_WDATA_PARITY_CHK_EN_MIN                 (0)
  #define IBECC_PARITY_CONTROL_WDATA_PARITY_CHK_EN_MAX                 (1) // 0x00000001
  #define IBECC_PARITY_CONTROL_WDATA_PARITY_CHK_EN_DEF                 (0x00000001)
  #define IBECC_PARITY_CONTROL_WDATA_PARITY_CHK_EN_HSH                 (0x0102DC98)

  #define IBECC_PARITY_CONTROL_WBE_PARITY_GEN_EN_OFF                   ( 3)
  #define IBECC_PARITY_CONTROL_WBE_PARITY_GEN_EN_WID                   ( 1)
  #define IBECC_PARITY_CONTROL_WBE_PARITY_GEN_EN_MSK                   (0x00000008)
  #define IBECC_PARITY_CONTROL_WBE_PARITY_GEN_EN_MIN                   (0)
  #define IBECC_PARITY_CONTROL_WBE_PARITY_GEN_EN_MAX                   (1) // 0x00000001
  #define IBECC_PARITY_CONTROL_WBE_PARITY_GEN_EN_DEF                   (0x00000001)
  #define IBECC_PARITY_CONTROL_WBE_PARITY_GEN_EN_HSH                   (0x0103DC98)

  #define IBECC_PARITY_CONTROL_WDATA_PARITY_GEN_EN_OFF                 ( 4)
  #define IBECC_PARITY_CONTROL_WDATA_PARITY_GEN_EN_WID                 ( 1)
  #define IBECC_PARITY_CONTROL_WDATA_PARITY_GEN_EN_MSK                 (0x00000010)
  #define IBECC_PARITY_CONTROL_WDATA_PARITY_GEN_EN_MIN                 (0)
  #define IBECC_PARITY_CONTROL_WDATA_PARITY_GEN_EN_MAX                 (1) // 0x00000001
  #define IBECC_PARITY_CONTROL_WDATA_PARITY_GEN_EN_DEF                 (0x00000001)
  #define IBECC_PARITY_CONTROL_WDATA_PARITY_GEN_EN_HSH                 (0x0104DC98)

  #define IBECC_PARITY_CONTROL_ADDR_PARITY_GEN_EN_OFF                  ( 5)
  #define IBECC_PARITY_CONTROL_ADDR_PARITY_GEN_EN_WID                  ( 1)
  #define IBECC_PARITY_CONTROL_ADDR_PARITY_GEN_EN_MSK                  (0x00000020)
  #define IBECC_PARITY_CONTROL_ADDR_PARITY_GEN_EN_MIN                  (0)
  #define IBECC_PARITY_CONTROL_ADDR_PARITY_GEN_EN_MAX                  (1) // 0x00000001
  #define IBECC_PARITY_CONTROL_ADDR_PARITY_GEN_EN_DEF                  (0x00000001)
  #define IBECC_PARITY_CONTROL_ADDR_PARITY_GEN_EN_HSH                  (0x0105DC98)

  #define IBECC_PARITY_CONTROL_RSVD0_OFF                               ( 6)
  #define IBECC_PARITY_CONTROL_RSVD0_WID                               ( 2)
  #define IBECC_PARITY_CONTROL_RSVD0_MSK                               (0x000000C0)
  #define IBECC_PARITY_CONTROL_RSVD0_MIN                               (0)
  #define IBECC_PARITY_CONTROL_RSVD0_MAX                               (3) // 0x00000003
  #define IBECC_PARITY_CONTROL_RSVD0_DEF                               (0x00000000)
  #define IBECC_PARITY_CONTROL_RSVD0_HSH                               (0x0206DC98)

  #define IBECC_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_OFF                ( 8)
  #define IBECC_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_WID                ( 1)
  #define IBECC_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_MSK                (0x00000100)
  #define IBECC_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_MIN                (0)
  #define IBECC_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_MAX                (1) // 0x00000001
  #define IBECC_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_DEF                (0x00000000)
  #define IBECC_PARITY_CONTROL_DIS_PARITY_PCH_EVENT_HSH                (0x0108DC98)

  #define IBECC_PARITY_CONTROL_DIS_PARITY_LOG_OFF                      ( 9)
  #define IBECC_PARITY_CONTROL_DIS_PARITY_LOG_WID                      ( 1)
  #define IBECC_PARITY_CONTROL_DIS_PARITY_LOG_MSK                      (0x00000200)
  #define IBECC_PARITY_CONTROL_DIS_PARITY_LOG_MIN                      (0)
  #define IBECC_PARITY_CONTROL_DIS_PARITY_LOG_MAX                      (1) // 0x00000001
  #define IBECC_PARITY_CONTROL_DIS_PARITY_LOG_DEF                      (0x00000000)
  #define IBECC_PARITY_CONTROL_DIS_PARITY_LOG_HSH                      (0x0109DC98)

  #define IBECC_PARITY_CONTROL_RSVD1_OFF                               (10)
  #define IBECC_PARITY_CONTROL_RSVD1_WID                               (21)
  #define IBECC_PARITY_CONTROL_RSVD1_MSK                               (0x7FFFFC00)
  #define IBECC_PARITY_CONTROL_RSVD1_MIN                               (0)
  #define IBECC_PARITY_CONTROL_RSVD1_MAX                               (2097151) // 0x001FFFFF
  #define IBECC_PARITY_CONTROL_RSVD1_DEF                               (0x00000000)
  #define IBECC_PARITY_CONTROL_RSVD1_HSH                               (0x150ADC98)

  #define IBECC_PARITY_CONTROL_PARITY_EN_OFF                           (31)
  #define IBECC_PARITY_CONTROL_PARITY_EN_WID                           ( 1)
  #define IBECC_PARITY_CONTROL_PARITY_EN_MSK                           (0x80000000)
  #define IBECC_PARITY_CONTROL_PARITY_EN_MIN                           (0)
  #define IBECC_PARITY_CONTROL_PARITY_EN_MAX                           (1) // 0x00000001
  #define IBECC_PARITY_CONTROL_PARITY_EN_DEF                           (0x00000000)
  #define IBECC_PARITY_CONTROL_PARITY_EN_HSH                           (0x011FDC98)

#define IBECC_RESPOND_PORT_STALL_REG                                   (0x0000DC9C)

  #define IBECC_RESPOND_PORT_STALL_RSVD0_OFF                           ( 0)
  #define IBECC_RESPOND_PORT_STALL_RSVD0_WID                           ( 4)
  #define IBECC_RESPOND_PORT_STALL_RSVD0_MSK                           (0x0000000F)
  #define IBECC_RESPOND_PORT_STALL_RSVD0_MIN                           (0)
  #define IBECC_RESPOND_PORT_STALL_RSVD0_MAX                           (15) // 0x0000000F
  #define IBECC_RESPOND_PORT_STALL_RSVD0_DEF                           (0x00000000)
  #define IBECC_RESPOND_PORT_STALL_RSVD0_HSH                           (0x0400DC9C)

  #define IBECC_RESPOND_PORT_STALL_RSP_RD_CPL_STALL_OFF                ( 4)
  #define IBECC_RESPOND_PORT_STALL_RSP_RD_CPL_STALL_WID                ( 1)
  #define IBECC_RESPOND_PORT_STALL_RSP_RD_CPL_STALL_MSK                (0x00000010)
  #define IBECC_RESPOND_PORT_STALL_RSP_RD_CPL_STALL_MIN                (0)
  #define IBECC_RESPOND_PORT_STALL_RSP_RD_CPL_STALL_MAX                (1) // 0x00000001
  #define IBECC_RESPOND_PORT_STALL_RSP_RD_CPL_STALL_DEF                (0x00000000)
  #define IBECC_RESPOND_PORT_STALL_RSP_RD_CPL_STALL_HSH                (0x0104DC9C)

  #define IBECC_RESPOND_PORT_STALL_RSVD1_OFF                           ( 5)
  #define IBECC_RESPOND_PORT_STALL_RSVD1_WID                           ( 3)
  #define IBECC_RESPOND_PORT_STALL_RSVD1_MSK                           (0x000000E0)
  #define IBECC_RESPOND_PORT_STALL_RSVD1_MIN                           (0)
  #define IBECC_RESPOND_PORT_STALL_RSVD1_MAX                           (7) // 0x00000007
  #define IBECC_RESPOND_PORT_STALL_RSVD1_DEF                           (0x00000000)
  #define IBECC_RESPOND_PORT_STALL_RSVD1_HSH                           (0x0305DC9C)

  #define IBECC_RESPOND_PORT_STALL_UNSTALL_COUNTER_VALUE_OFF           ( 8)
  #define IBECC_RESPOND_PORT_STALL_UNSTALL_COUNTER_VALUE_WID           (16)
  #define IBECC_RESPOND_PORT_STALL_UNSTALL_COUNTER_VALUE_MSK           (0x00FFFF00)
  #define IBECC_RESPOND_PORT_STALL_UNSTALL_COUNTER_VALUE_MIN           (0)
  #define IBECC_RESPOND_PORT_STALL_UNSTALL_COUNTER_VALUE_MAX           (65535) // 0x0000FFFF
  #define IBECC_RESPOND_PORT_STALL_UNSTALL_COUNTER_VALUE_DEF           (0x00000000)
  #define IBECC_RESPOND_PORT_STALL_UNSTALL_COUNTER_VALUE_HSH           (0x1008DC9C)

#define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_0_REG                (0x0000DD00)

  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_0_RESERVED0_OFF    ( 0)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_0_RESERVED0_WID    (16)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_0_RESERVED0_MSK    (0x0000FFFF)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_0_RESERVED0_MIN    (0)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_0_RESERVED0_MAX    (65535) // 0x0000FFFF
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_0_RESERVED0_DEF    (0x00000000)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_0_RESERVED0_HSH    (0x1000DD00)

  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_0_RSP_MAX_CREDIT_OFF (16)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_0_RSP_MAX_CREDIT_WID ( 8)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_0_RSP_MAX_CREDIT_MSK (0x00FF0000)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_0_RSP_MAX_CREDIT_MIN (0)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_0_RSP_MAX_CREDIT_MAX (255) // 0x000000FF
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_0_RSP_MAX_CREDIT_DEF (0x00000010)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_0_RSP_MAX_CREDIT_HSH (0x0810DD00)

  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_0_RD_CPL_MAX_CREDIT_OFF (24)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_0_RD_CPL_MAX_CREDIT_WID ( 8)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_0_RD_CPL_MAX_CREDIT_MSK (0xFF000000)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_0_RD_CPL_MAX_CREDIT_MIN (0)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_0_RD_CPL_MAX_CREDIT_MAX (255) // 0x000000FF
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_0_RD_CPL_MAX_CREDIT_DEF (0x00000010)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_0_RD_CPL_MAX_CREDIT_HSH (0x0818DD00)

#define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_1_REG                (0x0000DD04)

  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_1_RESERVED0_OFF    ( 0)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_1_RESERVED0_WID    (16)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_1_RESERVED0_MSK    (0x0000FFFF)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_1_RESERVED0_MIN    (0)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_1_RESERVED0_MAX    (65535) // 0x0000FFFF
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_1_RESERVED0_DEF    (0x00000000)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_1_RESERVED0_HSH    (0x1000DD04)

  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_1_RSP_MAX_CREDIT_OFF (16)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_1_RSP_MAX_CREDIT_WID ( 8)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_1_RSP_MAX_CREDIT_MSK (0x00FF0000)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_1_RSP_MAX_CREDIT_MIN (0)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_1_RSP_MAX_CREDIT_MAX (255) // 0x000000FF
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_1_RSP_MAX_CREDIT_DEF (0x00000010)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_1_RSP_MAX_CREDIT_HSH (0x0810DD04)

  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_1_RD_CPL_MAX_CREDIT_OFF (24)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_1_RD_CPL_MAX_CREDIT_WID ( 8)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_1_RD_CPL_MAX_CREDIT_MSK (0xFF000000)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_1_RD_CPL_MAX_CREDIT_MIN (0)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_1_RD_CPL_MAX_CREDIT_MAX (255) // 0x000000FF
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_1_RD_CPL_MAX_CREDIT_DEF (0x00000010)
  #define IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_1_RD_CPL_MAX_CREDIT_HSH (0x0818DD04)

#define IBECC_RSP_RD_CPL_TOTAL_CREDIT_CONFIG_REG                       (0x0000DD08)

  #define IBECC_RSP_RD_CPL_TOTAL_CREDIT_CONFIG_RD_CPL_QUEUEDEPTH_OFF   ( 0)
  #define IBECC_RSP_RD_CPL_TOTAL_CREDIT_CONFIG_RD_CPL_QUEUEDEPTH_WID   ( 8)
  #define IBECC_RSP_RD_CPL_TOTAL_CREDIT_CONFIG_RD_CPL_QUEUEDEPTH_MSK   (0x000000FF)
  #define IBECC_RSP_RD_CPL_TOTAL_CREDIT_CONFIG_RD_CPL_QUEUEDEPTH_MIN   (0)
  #define IBECC_RSP_RD_CPL_TOTAL_CREDIT_CONFIG_RD_CPL_QUEUEDEPTH_MAX   (255) // 0x000000FF
  #define IBECC_RSP_RD_CPL_TOTAL_CREDIT_CONFIG_RD_CPL_QUEUEDEPTH_DEF   (0x00000020)
  #define IBECC_RSP_RD_CPL_TOTAL_CREDIT_CONFIG_RD_CPL_QUEUEDEPTH_HSH   (0x0800DD08)

  #define IBECC_RSP_RD_CPL_TOTAL_CREDIT_CONFIG_RSP_QUEUEDEPTH_OFF      ( 8)
  #define IBECC_RSP_RD_CPL_TOTAL_CREDIT_CONFIG_RSP_QUEUEDEPTH_WID      ( 8)
  #define IBECC_RSP_RD_CPL_TOTAL_CREDIT_CONFIG_RSP_QUEUEDEPTH_MSK      (0x0000FF00)
  #define IBECC_RSP_RD_CPL_TOTAL_CREDIT_CONFIG_RSP_QUEUEDEPTH_MIN      (0)
  #define IBECC_RSP_RD_CPL_TOTAL_CREDIT_CONFIG_RSP_QUEUEDEPTH_MAX      (255) // 0x000000FF
  #define IBECC_RSP_RD_CPL_TOTAL_CREDIT_CONFIG_RSP_QUEUEDEPTH_DEF      (0x00000020)
  #define IBECC_RSP_RD_CPL_TOTAL_CREDIT_CONFIG_RSP_QUEUEDEPTH_HSH      (0x0808DD08)

  #define IBECC_RSP_RD_CPL_TOTAL_CREDIT_CONFIG_RESERVED1_OFF           (16)
  #define IBECC_RSP_RD_CPL_TOTAL_CREDIT_CONFIG_RESERVED1_WID           (16)
  #define IBECC_RSP_RD_CPL_TOTAL_CREDIT_CONFIG_RESERVED1_MSK           (0xFFFF0000)
  #define IBECC_RSP_RD_CPL_TOTAL_CREDIT_CONFIG_RESERVED1_MIN           (0)
  #define IBECC_RSP_RD_CPL_TOTAL_CREDIT_CONFIG_RESERVED1_MAX           (65535) // 0x0000FFFF
  #define IBECC_RSP_RD_CPL_TOTAL_CREDIT_CONFIG_RESERVED1_DEF           (0x00000000)
  #define IBECC_RSP_RD_CPL_TOTAL_CREDIT_CONFIG_RESERVED1_HSH           (0x1010DD08)

#define IBECC_QCLK_GLB_DRV_CLKGATE_CONTROL_REG                         (0x0000DD0C)

  #define IBECC_QCLK_GLB_DRV_CLKGATE_CONTROL_GRACE_CNTR_MAX_OFF        ( 0)
  #define IBECC_QCLK_GLB_DRV_CLKGATE_CONTROL_GRACE_CNTR_MAX_WID        ( 8)
  #define IBECC_QCLK_GLB_DRV_CLKGATE_CONTROL_GRACE_CNTR_MAX_MSK        (0x000000FF)
  #define IBECC_QCLK_GLB_DRV_CLKGATE_CONTROL_GRACE_CNTR_MAX_MIN        (0)
  #define IBECC_QCLK_GLB_DRV_CLKGATE_CONTROL_GRACE_CNTR_MAX_MAX        (255) // 0x000000FF
  #define IBECC_QCLK_GLB_DRV_CLKGATE_CONTROL_GRACE_CNTR_MAX_DEF        (0x0000000C)
  #define IBECC_QCLK_GLB_DRV_CLKGATE_CONTROL_GRACE_CNTR_MAX_HSH        (0x0800DD0C)

  #define IBECC_QCLK_GLB_DRV_CLKGATE_CONTROL_CLKGATE_DISABLE_OFF       ( 8)
  #define IBECC_QCLK_GLB_DRV_CLKGATE_CONTROL_CLKGATE_DISABLE_WID       ( 1)
  #define IBECC_QCLK_GLB_DRV_CLKGATE_CONTROL_CLKGATE_DISABLE_MSK       (0x00000100)
  #define IBECC_QCLK_GLB_DRV_CLKGATE_CONTROL_CLKGATE_DISABLE_MIN       (0)
  #define IBECC_QCLK_GLB_DRV_CLKGATE_CONTROL_CLKGATE_DISABLE_MAX       (1) // 0x00000001
  #define IBECC_QCLK_GLB_DRV_CLKGATE_CONTROL_CLKGATE_DISABLE_DEF       (0x00000000)
  #define IBECC_QCLK_GLB_DRV_CLKGATE_CONTROL_CLKGATE_DISABLE_HSH       (0x0108DD0C)

  #define IBECC_QCLK_GLB_DRV_CLKGATE_CONTROL_RSVD_OFF                  ( 9)
  #define IBECC_QCLK_GLB_DRV_CLKGATE_CONTROL_RSVD_WID                  (23)
  #define IBECC_QCLK_GLB_DRV_CLKGATE_CONTROL_RSVD_MSK                  (0xFFFFFE00)
  #define IBECC_QCLK_GLB_DRV_CLKGATE_CONTROL_RSVD_MIN                  (0)
  #define IBECC_QCLK_GLB_DRV_CLKGATE_CONTROL_RSVD_MAX                  (8388607) // 0x007FFFFF
  #define IBECC_QCLK_GLB_DRV_CLKGATE_CONTROL_RSVD_DEF                  (0x00000000)
  #define IBECC_QCLK_GLB_DRV_CLKGATE_CONTROL_RSVD_HSH                  (0x1709DD0C)

#define IBECC_RESPOND_PORT_ACCUM_REQ_OUT_REG                           (0x0000DD10)

  #define IBECC_RESPOND_PORT_ACCUM_REQ_OUT_REQ_CMD_SUM_OFF             ( 0)
  #define IBECC_RESPOND_PORT_ACCUM_REQ_OUT_REQ_CMD_SUM_WID             (16)
  #define IBECC_RESPOND_PORT_ACCUM_REQ_OUT_REQ_CMD_SUM_MSK             (0x0000FFFF)
  #define IBECC_RESPOND_PORT_ACCUM_REQ_OUT_REQ_CMD_SUM_MIN             (0)
  #define IBECC_RESPOND_PORT_ACCUM_REQ_OUT_REQ_CMD_SUM_MAX             (65535) // 0x0000FFFF
  #define IBECC_RESPOND_PORT_ACCUM_REQ_OUT_REQ_CMD_SUM_DEF             (0x00000000)
  #define IBECC_RESPOND_PORT_ACCUM_REQ_OUT_REQ_CMD_SUM_HSH             (0x1000DD10)

  #define IBECC_RESPOND_PORT_ACCUM_REQ_OUT_REQ_DATA_SUM_OFF            (16)
  #define IBECC_RESPOND_PORT_ACCUM_REQ_OUT_REQ_DATA_SUM_WID            (16)
  #define IBECC_RESPOND_PORT_ACCUM_REQ_OUT_REQ_DATA_SUM_MSK            (0xFFFF0000)
  #define IBECC_RESPOND_PORT_ACCUM_REQ_OUT_REQ_DATA_SUM_MIN            (0)
  #define IBECC_RESPOND_PORT_ACCUM_REQ_OUT_REQ_DATA_SUM_MAX            (65535) // 0x0000FFFF
  #define IBECC_RESPOND_PORT_ACCUM_REQ_OUT_REQ_DATA_SUM_DEF            (0x00000000)
  #define IBECC_RESPOND_PORT_ACCUM_REQ_OUT_REQ_DATA_SUM_HSH            (0x1010DD10)

#define IBECC_RESPOND_PORT_ACCUM_RD_CPL_IN_REG                         (0x0000DD14)

  #define IBECC_RESPOND_PORT_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_OFF        ( 0)
  #define IBECC_RESPOND_PORT_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_WID        (16)
  #define IBECC_RESPOND_PORT_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_MSK        (0x0000FFFF)
  #define IBECC_RESPOND_PORT_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_MIN        (0)
  #define IBECC_RESPOND_PORT_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_MAX        (65535) // 0x0000FFFF
  #define IBECC_RESPOND_PORT_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_DEF        (0x00000000)
  #define IBECC_RESPOND_PORT_ACCUM_RD_CPL_IN_RD_CPL_CMD_SUM_HSH        (0x1000DD14)

  #define IBECC_RESPOND_PORT_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_OFF       (16)
  #define IBECC_RESPOND_PORT_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_WID       (16)
  #define IBECC_RESPOND_PORT_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_MSK       (0xFFFF0000)
  #define IBECC_RESPOND_PORT_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_MIN       (0)
  #define IBECC_RESPOND_PORT_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_MAX       (65535) // 0x0000FFFF
  #define IBECC_RESPOND_PORT_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_DEF       (0x00000000)
  #define IBECC_RESPOND_PORT_ACCUM_RD_CPL_IN_RD_CPL_DATA_SUM_HSH       (0x1010DD14)

#define IBECC_RESPOND_PORT_ACCUM_RSP_IN_REG                            (0x0000DD18)

  #define IBECC_RESPOND_PORT_ACCUM_RSP_IN_RSP_CMD_SUM_OFF              ( 0)
  #define IBECC_RESPOND_PORT_ACCUM_RSP_IN_RSP_CMD_SUM_WID              (16)
  #define IBECC_RESPOND_PORT_ACCUM_RSP_IN_RSP_CMD_SUM_MSK              (0x0000FFFF)
  #define IBECC_RESPOND_PORT_ACCUM_RSP_IN_RSP_CMD_SUM_MIN              (0)
  #define IBECC_RESPOND_PORT_ACCUM_RSP_IN_RSP_CMD_SUM_MAX              (65535) // 0x0000FFFF
  #define IBECC_RESPOND_PORT_ACCUM_RSP_IN_RSP_CMD_SUM_DEF              (0x00000000)
  #define IBECC_RESPOND_PORT_ACCUM_RSP_IN_RSP_CMD_SUM_HSH              (0x1000DD18)

  #define IBECC_RESPOND_PORT_ACCUM_RSP_IN_RSVD_OFF                     (16)
  #define IBECC_RESPOND_PORT_ACCUM_RSP_IN_RSVD_WID                     (16)
  #define IBECC_RESPOND_PORT_ACCUM_RSP_IN_RSVD_MSK                     (0xFFFF0000)
  #define IBECC_RESPOND_PORT_ACCUM_RSP_IN_RSVD_MIN                     (0)
  #define IBECC_RESPOND_PORT_ACCUM_RSP_IN_RSVD_MAX                     (65535) // 0x0000FFFF
  #define IBECC_RESPOND_PORT_ACCUM_RSP_IN_RSVD_DEF                     (0x00000000)
  #define IBECC_RESPOND_PORT_ACCUM_RSP_IN_RSVD_HSH                     (0x1010DD18)

#define IBECC_REQUEST_PORT_ACCUM_RSP_OUT_REG                           (0x0000DD1C)

  #define IBECC_REQUEST_PORT_ACCUM_RSP_OUT_RSP_CMD_SUM_OFF             ( 0)
  #define IBECC_REQUEST_PORT_ACCUM_RSP_OUT_RSP_CMD_SUM_WID             (16)
  #define IBECC_REQUEST_PORT_ACCUM_RSP_OUT_RSP_CMD_SUM_MSK             (0x0000FFFF)
  #define IBECC_REQUEST_PORT_ACCUM_RSP_OUT_RSP_CMD_SUM_MIN             (0)
  #define IBECC_REQUEST_PORT_ACCUM_RSP_OUT_RSP_CMD_SUM_MAX             (65535) // 0x0000FFFF
  #define IBECC_REQUEST_PORT_ACCUM_RSP_OUT_RSP_CMD_SUM_DEF             (0x00000000)
  #define IBECC_REQUEST_PORT_ACCUM_RSP_OUT_RSP_CMD_SUM_HSH             (0x1000DD1C)

  #define IBECC_REQUEST_PORT_ACCUM_RSP_OUT_RSVD_OFF                    (16)
  #define IBECC_REQUEST_PORT_ACCUM_RSP_OUT_RSVD_WID                    (16)
  #define IBECC_REQUEST_PORT_ACCUM_RSP_OUT_RSVD_MSK                    (0xFFFF0000)
  #define IBECC_REQUEST_PORT_ACCUM_RSP_OUT_RSVD_MIN                    (0)
  #define IBECC_REQUEST_PORT_ACCUM_RSP_OUT_RSVD_MAX                    (65535) // 0x0000FFFF
  #define IBECC_REQUEST_PORT_ACCUM_RSP_OUT_RSVD_DEF                    (0x00000000)
  #define IBECC_REQUEST_PORT_ACCUM_RSP_OUT_RSVD_HSH                    (0x1010DD1C)

#define IBECC_ECC_VC0_RD_REQCOUNT_REG                                  (0x0000DD20)

  #define IBECC_ECC_VC0_RD_REQCOUNT_COUNT_OFF                          ( 0)
  #define IBECC_ECC_VC0_RD_REQCOUNT_COUNT_WID                          (64)
  #define IBECC_ECC_VC0_RD_REQCOUNT_COUNT_MSK                          (0xFFFFFFFFFFFFFFFFULL)
  #define IBECC_ECC_VC0_RD_REQCOUNT_COUNT_MIN                          (0)
  #define IBECC_ECC_VC0_RD_REQCOUNT_COUNT_MAX                          (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define IBECC_ECC_VC0_RD_REQCOUNT_COUNT_DEF                          (0x00000000)
  #define IBECC_ECC_VC0_RD_REQCOUNT_COUNT_HSH                          (0x4000DD20)

#define IBECC_ECC_VC1_RD_REQCOUNT_REG                                  (0x0000DD28)

  #define IBECC_ECC_VC1_RD_REQCOUNT_COUNT_OFF                          ( 0)
  #define IBECC_ECC_VC1_RD_REQCOUNT_COUNT_WID                          (64)
  #define IBECC_ECC_VC1_RD_REQCOUNT_COUNT_MSK                          (0xFFFFFFFFFFFFFFFFULL)
  #define IBECC_ECC_VC1_RD_REQCOUNT_COUNT_MIN                          (0)
  #define IBECC_ECC_VC1_RD_REQCOUNT_COUNT_MAX                          (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define IBECC_ECC_VC1_RD_REQCOUNT_COUNT_DEF                          (0x00000000)
  #define IBECC_ECC_VC1_RD_REQCOUNT_COUNT_HSH                          (0x4000DD28)

#define IBECC_ECC_VC0_WR_REQCOUNT_REG                                  (0x0000DD30)

  #define IBECC_ECC_VC0_WR_REQCOUNT_COUNT_OFF                          ( 0)
  #define IBECC_ECC_VC0_WR_REQCOUNT_COUNT_WID                          (64)
  #define IBECC_ECC_VC0_WR_REQCOUNT_COUNT_MSK                          (0xFFFFFFFFFFFFFFFFULL)
  #define IBECC_ECC_VC0_WR_REQCOUNT_COUNT_MIN                          (0)
  #define IBECC_ECC_VC0_WR_REQCOUNT_COUNT_MAX                          (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define IBECC_ECC_VC0_WR_REQCOUNT_COUNT_DEF                          (0x00000000)
  #define IBECC_ECC_VC0_WR_REQCOUNT_COUNT_HSH                          (0x4000DD30)

#define IBECC_ECC_VC1_WR_REQCOUNT_REG                                  (0x0000DD38)

  #define IBECC_ECC_VC1_WR_REQCOUNT_COUNT_OFF                          ( 0)
  #define IBECC_ECC_VC1_WR_REQCOUNT_COUNT_WID                          (64)
  #define IBECC_ECC_VC1_WR_REQCOUNT_COUNT_MSK                          (0xFFFFFFFFFFFFFFFFULL)
  #define IBECC_ECC_VC1_WR_REQCOUNT_COUNT_MIN                          (0)
  #define IBECC_ECC_VC1_WR_REQCOUNT_COUNT_MAX                          (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define IBECC_ECC_VC1_WR_REQCOUNT_COUNT_DEF                          (0x00000000)
  #define IBECC_ECC_VC1_WR_REQCOUNT_COUNT_HSH                          (0x4000DD38)

#define IBECC_NOECC_VC0_RD_REQCOUNT_REG                                (0x0000DD40)

  #define IBECC_NOECC_VC0_RD_REQCOUNT_COUNT_OFF                        ( 0)
  #define IBECC_NOECC_VC0_RD_REQCOUNT_COUNT_WID                        (64)
  #define IBECC_NOECC_VC0_RD_REQCOUNT_COUNT_MSK                        (0xFFFFFFFFFFFFFFFFULL)
  #define IBECC_NOECC_VC0_RD_REQCOUNT_COUNT_MIN                        (0)
  #define IBECC_NOECC_VC0_RD_REQCOUNT_COUNT_MAX                        (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define IBECC_NOECC_VC0_RD_REQCOUNT_COUNT_DEF                        (0x00000000)
  #define IBECC_NOECC_VC0_RD_REQCOUNT_COUNT_HSH                        (0x4000DD40)

#define IBECC_NOECC_VC1_RD_REQCOUNT_REG                                (0x0000DD48)

  #define IBECC_NOECC_VC1_RD_REQCOUNT_COUNT_OFF                        ( 0)
  #define IBECC_NOECC_VC1_RD_REQCOUNT_COUNT_WID                        (64)
  #define IBECC_NOECC_VC1_RD_REQCOUNT_COUNT_MSK                        (0xFFFFFFFFFFFFFFFFULL)
  #define IBECC_NOECC_VC1_RD_REQCOUNT_COUNT_MIN                        (0)
  #define IBECC_NOECC_VC1_RD_REQCOUNT_COUNT_MAX                        (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define IBECC_NOECC_VC1_RD_REQCOUNT_COUNT_DEF                        (0x00000000)
  #define IBECC_NOECC_VC1_RD_REQCOUNT_COUNT_HSH                        (0x4000DD48)

#define IBECC_NOECC_VC0_WR_REQCOUNT_REG                                (0x0000DD50)

  #define IBECC_NOECC_VC0_WR_REQCOUNT_COUNT_OFF                        ( 0)
  #define IBECC_NOECC_VC0_WR_REQCOUNT_COUNT_WID                        (64)
  #define IBECC_NOECC_VC0_WR_REQCOUNT_COUNT_MSK                        (0xFFFFFFFFFFFFFFFFULL)
  #define IBECC_NOECC_VC0_WR_REQCOUNT_COUNT_MIN                        (0)
  #define IBECC_NOECC_VC0_WR_REQCOUNT_COUNT_MAX                        (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define IBECC_NOECC_VC0_WR_REQCOUNT_COUNT_DEF                        (0x00000000)
  #define IBECC_NOECC_VC0_WR_REQCOUNT_COUNT_HSH                        (0x4000DD50)

#define IBECC_NOECC_VC1_WR_REQCOUNT_REG                                (0x0000DD58)

  #define IBECC_NOECC_VC1_WR_REQCOUNT_COUNT_OFF                        ( 0)
  #define IBECC_NOECC_VC1_WR_REQCOUNT_COUNT_WID                        (64)
  #define IBECC_NOECC_VC1_WR_REQCOUNT_COUNT_MSK                        (0xFFFFFFFFFFFFFFFFULL)
  #define IBECC_NOECC_VC1_WR_REQCOUNT_COUNT_MIN                        (0)
  #define IBECC_NOECC_VC1_WR_REQCOUNT_COUNT_MAX                        (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define IBECC_NOECC_VC1_WR_REQCOUNT_COUNT_DEF                        (0x00000000)
  #define IBECC_NOECC_VC1_WR_REQCOUNT_COUNT_HSH                        (0x4000DD58)

#define IBECC_PRIO_THRESHOLD_REG                                       (0x0000DD60)

  #define IBECC_PRIO_THRESHOLD_NON_VC1_PRIO_THRESHOLD_OFF              ( 0)
  #define IBECC_PRIO_THRESHOLD_NON_VC1_PRIO_THRESHOLD_WID              (16)
  #define IBECC_PRIO_THRESHOLD_NON_VC1_PRIO_THRESHOLD_MSK              (0x0000FFFF)
  #define IBECC_PRIO_THRESHOLD_NON_VC1_PRIO_THRESHOLD_MIN              (0)
  #define IBECC_PRIO_THRESHOLD_NON_VC1_PRIO_THRESHOLD_MAX              (65535) // 0x0000FFFF
  #define IBECC_PRIO_THRESHOLD_NON_VC1_PRIO_THRESHOLD_DEF              (0x00000008)
  #define IBECC_PRIO_THRESHOLD_NON_VC1_PRIO_THRESHOLD_HSH              (0x1000DD60)

  #define IBECC_PRIO_THRESHOLD_VC1_RD_PRIO_THRESHOLD_OFF               (16)
  #define IBECC_PRIO_THRESHOLD_VC1_RD_PRIO_THRESHOLD_WID               (16)
  #define IBECC_PRIO_THRESHOLD_VC1_RD_PRIO_THRESHOLD_MSK               (0xFFFF0000)
  #define IBECC_PRIO_THRESHOLD_VC1_RD_PRIO_THRESHOLD_MIN               (0)
  #define IBECC_PRIO_THRESHOLD_VC1_RD_PRIO_THRESHOLD_MAX               (65535) // 0x0000FFFF
  #define IBECC_PRIO_THRESHOLD_VC1_RD_PRIO_THRESHOLD_DEF               (0x00000008)
  #define IBECC_PRIO_THRESHOLD_VC1_RD_PRIO_THRESHOLD_HSH               (0x1010DD60)

#define IBECC_REQUEST_ARB_CONFIG_REG                                   (0x0000DD64)

  #define IBECC_REQUEST_ARB_CONFIG_VC0_RD_PARK_SIZE_OFF                ( 0)
  #define IBECC_REQUEST_ARB_CONFIG_VC0_RD_PARK_SIZE_WID                ( 4)
  #define IBECC_REQUEST_ARB_CONFIG_VC0_RD_PARK_SIZE_MSK                (0x0000000F)
  #define IBECC_REQUEST_ARB_CONFIG_VC0_RD_PARK_SIZE_MIN                (0)
  #define IBECC_REQUEST_ARB_CONFIG_VC0_RD_PARK_SIZE_MAX                (15) // 0x0000000F
  #define IBECC_REQUEST_ARB_CONFIG_VC0_RD_PARK_SIZE_DEF                (0x00000003)
  #define IBECC_REQUEST_ARB_CONFIG_VC0_RD_PARK_SIZE_HSH                (0x0400DD64)

  #define IBECC_REQUEST_ARB_CONFIG_VC1_RD_PARK_SIZE_OFF                ( 4)
  #define IBECC_REQUEST_ARB_CONFIG_VC1_RD_PARK_SIZE_WID                ( 4)
  #define IBECC_REQUEST_ARB_CONFIG_VC1_RD_PARK_SIZE_MSK                (0x000000F0)
  #define IBECC_REQUEST_ARB_CONFIG_VC1_RD_PARK_SIZE_MIN                (0)
  #define IBECC_REQUEST_ARB_CONFIG_VC1_RD_PARK_SIZE_MAX                (15) // 0x0000000F
  #define IBECC_REQUEST_ARB_CONFIG_VC1_RD_PARK_SIZE_DEF                (0x00000003)
  #define IBECC_REQUEST_ARB_CONFIG_VC1_RD_PARK_SIZE_HSH                (0x0404DD64)

  #define IBECC_REQUEST_ARB_CONFIG_VC0_WR_PARK_SIZE_OFF                ( 8)
  #define IBECC_REQUEST_ARB_CONFIG_VC0_WR_PARK_SIZE_WID                ( 4)
  #define IBECC_REQUEST_ARB_CONFIG_VC0_WR_PARK_SIZE_MSK                (0x00000F00)
  #define IBECC_REQUEST_ARB_CONFIG_VC0_WR_PARK_SIZE_MIN                (0)
  #define IBECC_REQUEST_ARB_CONFIG_VC0_WR_PARK_SIZE_MAX                (15) // 0x0000000F
  #define IBECC_REQUEST_ARB_CONFIG_VC0_WR_PARK_SIZE_DEF                (0x00000003)
  #define IBECC_REQUEST_ARB_CONFIG_VC0_WR_PARK_SIZE_HSH                (0x0408DD64)

  #define IBECC_REQUEST_ARB_CONFIG_VC1_WR_PARK_SIZE_OFF                (12)
  #define IBECC_REQUEST_ARB_CONFIG_VC1_WR_PARK_SIZE_WID                ( 4)
  #define IBECC_REQUEST_ARB_CONFIG_VC1_WR_PARK_SIZE_MSK                (0x0000F000)
  #define IBECC_REQUEST_ARB_CONFIG_VC1_WR_PARK_SIZE_MIN                (0)
  #define IBECC_REQUEST_ARB_CONFIG_VC1_WR_PARK_SIZE_MAX                (15) // 0x0000000F
  #define IBECC_REQUEST_ARB_CONFIG_VC1_WR_PARK_SIZE_DEF                (0x00000003)
  #define IBECC_REQUEST_ARB_CONFIG_VC1_WR_PARK_SIZE_HSH                (0x040CDD64)

  #define IBECC_REQUEST_ARB_CONFIG_RSVD_OFF                            (16)
  #define IBECC_REQUEST_ARB_CONFIG_RSVD_WID                            (16)
  #define IBECC_REQUEST_ARB_CONFIG_RSVD_MSK                            (0xFFFF0000)
  #define IBECC_REQUEST_ARB_CONFIG_RSVD_MIN                            (0)
  #define IBECC_REQUEST_ARB_CONFIG_RSVD_MAX                            (65535) // 0x0000FFFF
  #define IBECC_REQUEST_ARB_CONFIG_RSVD_DEF                            (0x00000000)
  #define IBECC_REQUEST_ARB_CONFIG_RSVD_HSH                            (0x1010DD64)

#define IBECC_RESPONSE_ARB_CONFIG_REG                                  (0x0000DD68)

  #define IBECC_RESPONSE_ARB_CONFIG_VC0_RD_PARK_SIZE_OFF               ( 0)
  #define IBECC_RESPONSE_ARB_CONFIG_VC0_RD_PARK_SIZE_WID               ( 4)
  #define IBECC_RESPONSE_ARB_CONFIG_VC0_RD_PARK_SIZE_MSK               (0x0000000F)
  #define IBECC_RESPONSE_ARB_CONFIG_VC0_RD_PARK_SIZE_MIN               (0)
  #define IBECC_RESPONSE_ARB_CONFIG_VC0_RD_PARK_SIZE_MAX               (15) // 0x0000000F
  #define IBECC_RESPONSE_ARB_CONFIG_VC0_RD_PARK_SIZE_DEF               (0x00000003)
  #define IBECC_RESPONSE_ARB_CONFIG_VC0_RD_PARK_SIZE_HSH               (0x0400DD68)

  #define IBECC_RESPONSE_ARB_CONFIG_VC1_RD_PARK_SIZE_OFF               ( 4)
  #define IBECC_RESPONSE_ARB_CONFIG_VC1_RD_PARK_SIZE_WID               ( 4)
  #define IBECC_RESPONSE_ARB_CONFIG_VC1_RD_PARK_SIZE_MSK               (0x000000F0)
  #define IBECC_RESPONSE_ARB_CONFIG_VC1_RD_PARK_SIZE_MIN               (0)
  #define IBECC_RESPONSE_ARB_CONFIG_VC1_RD_PARK_SIZE_MAX               (15) // 0x0000000F
  #define IBECC_RESPONSE_ARB_CONFIG_VC1_RD_PARK_SIZE_DEF               (0x00000003)
  #define IBECC_RESPONSE_ARB_CONFIG_VC1_RD_PARK_SIZE_HSH               (0x0404DD68)

  #define IBECC_RESPONSE_ARB_CONFIG_VC0_WR_PARK_SIZE_OFF               ( 8)
  #define IBECC_RESPONSE_ARB_CONFIG_VC0_WR_PARK_SIZE_WID               ( 4)
  #define IBECC_RESPONSE_ARB_CONFIG_VC0_WR_PARK_SIZE_MSK               (0x00000F00)
  #define IBECC_RESPONSE_ARB_CONFIG_VC0_WR_PARK_SIZE_MIN               (0)
  #define IBECC_RESPONSE_ARB_CONFIG_VC0_WR_PARK_SIZE_MAX               (15) // 0x0000000F
  #define IBECC_RESPONSE_ARB_CONFIG_VC0_WR_PARK_SIZE_DEF               (0x00000003)
  #define IBECC_RESPONSE_ARB_CONFIG_VC0_WR_PARK_SIZE_HSH               (0x0408DD68)

  #define IBECC_RESPONSE_ARB_CONFIG_VC1_WR_PARK_SIZE_OFF               (12)
  #define IBECC_RESPONSE_ARB_CONFIG_VC1_WR_PARK_SIZE_WID               ( 4)
  #define IBECC_RESPONSE_ARB_CONFIG_VC1_WR_PARK_SIZE_MSK               (0x0000F000)
  #define IBECC_RESPONSE_ARB_CONFIG_VC1_WR_PARK_SIZE_MIN               (0)
  #define IBECC_RESPONSE_ARB_CONFIG_VC1_WR_PARK_SIZE_MAX               (15) // 0x0000000F
  #define IBECC_RESPONSE_ARB_CONFIG_VC1_WR_PARK_SIZE_DEF               (0x00000003)
  #define IBECC_RESPONSE_ARB_CONFIG_VC1_WR_PARK_SIZE_HSH               (0x040CDD68)

  #define IBECC_RESPONSE_ARB_CONFIG_RSVD_OFF                           (16)
  #define IBECC_RESPONSE_ARB_CONFIG_RSVD_WID                           (16)
  #define IBECC_RESPONSE_ARB_CONFIG_RSVD_MSK                           (0xFFFF0000)
  #define IBECC_RESPONSE_ARB_CONFIG_RSVD_MIN                           (0)
  #define IBECC_RESPONSE_ARB_CONFIG_RSVD_MAX                           (65535) // 0x0000FFFF
  #define IBECC_RESPONSE_ARB_CONFIG_RSVD_DEF                           (0x00000000)
  #define IBECC_RESPONSE_ARB_CONFIG_RSVD_HSH                           (0x1010DD68)

#define IBECC_ECC_ERROR_LOG_REG                                        (0x0000DD70)

  #define IBECC_ECC_ERROR_LOG_RSVD0_OFF                                ( 0)
  #define IBECC_ECC_ERROR_LOG_RSVD0_WID                                ( 5)
  #define IBECC_ECC_ERROR_LOG_RSVD0_MSK                                (0x0000001F)
  #define IBECC_ECC_ERROR_LOG_RSVD0_MIN                                (0)
  #define IBECC_ECC_ERROR_LOG_RSVD0_MAX                                (31) // 0x0000001F
  #define IBECC_ECC_ERROR_LOG_RSVD0_DEF                                (0x00000000)
  #define IBECC_ECC_ERROR_LOG_RSVD0_HSH                                (0x4500DD70)

  #define IBECC_ECC_ERROR_LOG_ERRADD_OFF                               ( 5)
  #define IBECC_ECC_ERROR_LOG_ERRADD_WID                               (34)
  #define IBECC_ECC_ERROR_LOG_ERRADD_MSK                               (0x0000007FFFFFFFE0ULL)
  #define IBECC_ECC_ERROR_LOG_ERRADD_MIN                               (0)
  #define IBECC_ECC_ERROR_LOG_ERRADD_MAX                               (17179869183ULL) // 0x3FFFFFFFF
  #define IBECC_ECC_ERROR_LOG_ERRADD_DEF                               (0x00000000)
  #define IBECC_ECC_ERROR_LOG_ERRADD_HSH                               (0x6205DD70)

  #define IBECC_ECC_ERROR_LOG_RSVD1_OFF                                (39)
  #define IBECC_ECC_ERROR_LOG_RSVD1_WID                                ( 7)
  #define IBECC_ECC_ERROR_LOG_RSVD1_MSK                                (0x00003F8000000000ULL)
  #define IBECC_ECC_ERROR_LOG_RSVD1_MIN                                (0)
  #define IBECC_ECC_ERROR_LOG_RSVD1_MAX                                (127) // 0x0000007F
  #define IBECC_ECC_ERROR_LOG_RSVD1_DEF                                (0x00000000)
  #define IBECC_ECC_ERROR_LOG_RSVD1_HSH                                (0x4727DD70)

  #define IBECC_ECC_ERROR_LOG_ERRSYND_OFF                              (46)
  #define IBECC_ECC_ERROR_LOG_ERRSYND_WID                              (16)
  #define IBECC_ECC_ERROR_LOG_ERRSYND_MSK                              (0x3FFFC00000000000ULL)
  #define IBECC_ECC_ERROR_LOG_ERRSYND_MIN                              (0)
  #define IBECC_ECC_ERROR_LOG_ERRSYND_MAX                              (65535) // 0x0000FFFF
  #define IBECC_ECC_ERROR_LOG_ERRSYND_DEF                              (0x00000000)
  #define IBECC_ECC_ERROR_LOG_ERRSYND_HSH                              (0x502EDD70)

  #define IBECC_ECC_ERROR_LOG_CERRSTS_OFF                              (62)
  #define IBECC_ECC_ERROR_LOG_CERRSTS_WID                              ( 1)
  #define IBECC_ECC_ERROR_LOG_CERRSTS_MSK                              (0x4000000000000000ULL)
  #define IBECC_ECC_ERROR_LOG_CERRSTS_MIN                              (0)
  #define IBECC_ECC_ERROR_LOG_CERRSTS_MAX                              (1) // 0x00000001
  #define IBECC_ECC_ERROR_LOG_CERRSTS_DEF                              (0x00000000)
  #define IBECC_ECC_ERROR_LOG_CERRSTS_HSH                              (0x413EDD70)

  #define IBECC_ECC_ERROR_LOG_MERRSTS_OFF                              (63)
  #define IBECC_ECC_ERROR_LOG_MERRSTS_WID                              ( 1)
  #define IBECC_ECC_ERROR_LOG_MERRSTS_MSK                              (0x8000000000000000ULL)
  #define IBECC_ECC_ERROR_LOG_MERRSTS_MIN                              (0)
  #define IBECC_ECC_ERROR_LOG_MERRSTS_MAX                              (1) // 0x00000001
  #define IBECC_ECC_ERROR_LOG_MERRSTS_DEF                              (0x00000000)
  #define IBECC_ECC_ERROR_LOG_MERRSTS_HSH                              (0x413FDD70)

#define IBECC_PARITY_ERR_LOG_REG                                       (0x0000DD78)

  #define IBECC_PARITY_ERR_LOG_RSVD1_OFF                               ( 0)
  #define IBECC_PARITY_ERR_LOG_RSVD1_WID                               ( 5)
  #define IBECC_PARITY_ERR_LOG_RSVD1_MSK                               (0x0000001F)
  #define IBECC_PARITY_ERR_LOG_RSVD1_MIN                               (0)
  #define IBECC_PARITY_ERR_LOG_RSVD1_MAX                               (31) // 0x0000001F
  #define IBECC_PARITY_ERR_LOG_RSVD1_DEF                               (0x00000000)
  #define IBECC_PARITY_ERR_LOG_RSVD1_HSH                               (0x4500DD78)

  #define IBECC_PARITY_ERR_LOG_ERR_ADDRESS_OFF                         ( 5)
  #define IBECC_PARITY_ERR_LOG_ERR_ADDRESS_WID                         (34)
  #define IBECC_PARITY_ERR_LOG_ERR_ADDRESS_MSK                         (0x0000007FFFFFFFE0ULL)
  #define IBECC_PARITY_ERR_LOG_ERR_ADDRESS_MIN                         (0)
  #define IBECC_PARITY_ERR_LOG_ERR_ADDRESS_MAX                         (17179869183ULL) // 0x3FFFFFFFF
  #define IBECC_PARITY_ERR_LOG_ERR_ADDRESS_DEF                         (0x00000000)
  #define IBECC_PARITY_ERR_LOG_ERR_ADDRESS_HSH                         (0x6205DD78)

  #define IBECC_PARITY_ERR_LOG_RSVD2_OFF                               (39)
  #define IBECC_PARITY_ERR_LOG_RSVD2_WID                               (21)
  #define IBECC_PARITY_ERR_LOG_RSVD2_MSK                               (0x0FFFFF8000000000ULL)
  #define IBECC_PARITY_ERR_LOG_RSVD2_MIN                               (0)
  #define IBECC_PARITY_ERR_LOG_RSVD2_MAX                               (2097151) // 0x001FFFFF
  #define IBECC_PARITY_ERR_LOG_RSVD2_DEF                               (0x00000000)
  #define IBECC_PARITY_ERR_LOG_RSVD2_HSH                               (0x5527DD78)

  #define IBECC_PARITY_ERR_LOG_TRANS_TYPE_OFF                          (60)
  #define IBECC_PARITY_ERR_LOG_TRANS_TYPE_WID                          ( 1)
  #define IBECC_PARITY_ERR_LOG_TRANS_TYPE_MSK                          (0x1000000000000000ULL)
  #define IBECC_PARITY_ERR_LOG_TRANS_TYPE_MIN                          (0)
  #define IBECC_PARITY_ERR_LOG_TRANS_TYPE_MAX                          (1) // 0x00000001
  #define IBECC_PARITY_ERR_LOG_TRANS_TYPE_DEF                          (0x00000000)
  #define IBECC_PARITY_ERR_LOG_TRANS_TYPE_HSH                          (0x413CDD78)

  #define IBECC_PARITY_ERR_LOG_ERR_TYPE_OFF                            (61)
  #define IBECC_PARITY_ERR_LOG_ERR_TYPE_WID                            ( 2)
  #define IBECC_PARITY_ERR_LOG_ERR_TYPE_MSK                            (0x6000000000000000ULL)
  #define IBECC_PARITY_ERR_LOG_ERR_TYPE_MIN                            (0)
  #define IBECC_PARITY_ERR_LOG_ERR_TYPE_MAX                            (3) // 0x00000003
  #define IBECC_PARITY_ERR_LOG_ERR_TYPE_DEF                            (0x00000000)
  #define IBECC_PARITY_ERR_LOG_ERR_TYPE_HSH                            (0x423DDD78)

  #define IBECC_PARITY_ERR_LOG_ERR_STS_OFF                             (63)
  #define IBECC_PARITY_ERR_LOG_ERR_STS_WID                             ( 1)
  #define IBECC_PARITY_ERR_LOG_ERR_STS_MSK                             (0x8000000000000000ULL)
  #define IBECC_PARITY_ERR_LOG_ERR_STS_MIN                             (0)
  #define IBECC_PARITY_ERR_LOG_ERR_STS_MAX                             (1) // 0x00000001
  #define IBECC_PARITY_ERR_LOG_ERR_STS_DEF                             (0x00000000)
  #define IBECC_PARITY_ERR_LOG_ERR_STS_HSH                             (0x413FDD78)

#define IBECC_ECC_INJ_ADDR_MASK_REG                                    (0x0000DD80)

  #define IBECC_ECC_INJ_ADDR_MASK_RSVD1_OFF                            ( 0)
  #define IBECC_ECC_INJ_ADDR_MASK_RSVD1_WID                            ( 6)
  #define IBECC_ECC_INJ_ADDR_MASK_RSVD1_MSK                            (0x0000003F)
  #define IBECC_ECC_INJ_ADDR_MASK_RSVD1_MIN                            (0)
  #define IBECC_ECC_INJ_ADDR_MASK_RSVD1_MAX                            (63) // 0x0000003F
  #define IBECC_ECC_INJ_ADDR_MASK_RSVD1_DEF                            (0x00000000)
  #define IBECC_ECC_INJ_ADDR_MASK_RSVD1_HSH                            (0x4600DD80)

  #define IBECC_ECC_INJ_ADDR_MASK_ADDRESS_OFF                          ( 6)
  #define IBECC_ECC_INJ_ADDR_MASK_ADDRESS_WID                          (33)
  #define IBECC_ECC_INJ_ADDR_MASK_ADDRESS_MSK                          (0x0000007FFFFFFFC0ULL)
  #define IBECC_ECC_INJ_ADDR_MASK_ADDRESS_MIN                          (0)
  #define IBECC_ECC_INJ_ADDR_MASK_ADDRESS_MAX                          (8589934591ULL) // 0x1FFFFFFFF
  #define IBECC_ECC_INJ_ADDR_MASK_ADDRESS_DEF                          (0x00000000)
  #define IBECC_ECC_INJ_ADDR_MASK_ADDRESS_HSH                          (0x6106DD80)

  #define IBECC_ECC_INJ_ADDR_MASK_RSVD2_OFF                            (39)
  #define IBECC_ECC_INJ_ADDR_MASK_RSVD2_WID                            (25)
  #define IBECC_ECC_INJ_ADDR_MASK_RSVD2_MSK                            (0xFFFFFF8000000000ULL)
  #define IBECC_ECC_INJ_ADDR_MASK_RSVD2_MIN                            (0)
  #define IBECC_ECC_INJ_ADDR_MASK_RSVD2_MAX                            (33554431) // 0x01FFFFFF
  #define IBECC_ECC_INJ_ADDR_MASK_RSVD2_DEF                            (0x00000000)
  #define IBECC_ECC_INJ_ADDR_MASK_RSVD2_HSH                            (0x5927DD80)

#define IBECC_ECC_INJ_ADDR_BASE_REG                                    (0x0000DD88)

  #define IBECC_ECC_INJ_ADDR_BASE_RSVD1_OFF                            ( 0)
  #define IBECC_ECC_INJ_ADDR_BASE_RSVD1_WID                            ( 6)
  #define IBECC_ECC_INJ_ADDR_BASE_RSVD1_MSK                            (0x0000003F)
  #define IBECC_ECC_INJ_ADDR_BASE_RSVD1_MIN                            (0)
  #define IBECC_ECC_INJ_ADDR_BASE_RSVD1_MAX                            (63) // 0x0000003F
  #define IBECC_ECC_INJ_ADDR_BASE_RSVD1_DEF                            (0x00000000)
  #define IBECC_ECC_INJ_ADDR_BASE_RSVD1_HSH                            (0x4600DD88)

  #define IBECC_ECC_INJ_ADDR_BASE_ADDRESS_OFF                          ( 6)
  #define IBECC_ECC_INJ_ADDR_BASE_ADDRESS_WID                          (33)
  #define IBECC_ECC_INJ_ADDR_BASE_ADDRESS_MSK                          (0x0000007FFFFFFFC0ULL)
  #define IBECC_ECC_INJ_ADDR_BASE_ADDRESS_MIN                          (0)
  #define IBECC_ECC_INJ_ADDR_BASE_ADDRESS_MAX                          (8589934591ULL) // 0x1FFFFFFFF
  #define IBECC_ECC_INJ_ADDR_BASE_ADDRESS_DEF                          (0x00000000)
  #define IBECC_ECC_INJ_ADDR_BASE_ADDRESS_HSH                          (0x6106DD88)

  #define IBECC_ECC_INJ_ADDR_BASE_RSVD2_OFF                            (39)
  #define IBECC_ECC_INJ_ADDR_BASE_RSVD2_WID                            (25)
  #define IBECC_ECC_INJ_ADDR_BASE_RSVD2_MSK                            (0xFFFFFF8000000000ULL)
  #define IBECC_ECC_INJ_ADDR_BASE_RSVD2_MIN                            (0)
  #define IBECC_ECC_INJ_ADDR_BASE_RSVD2_MAX                            (33554431) // 0x01FFFFFF
  #define IBECC_ECC_INJ_ADDR_BASE_RSVD2_DEF                            (0x00000000)
  #define IBECC_ECC_INJ_ADDR_BASE_RSVD2_HSH                            (0x5927DD88)

#define IBECC_PARITY_ERR_INJ_REG                                       (0x0000DD90)

  #define IBECC_PARITY_ERR_INJ_DATA_ERR_EN_OFF                         ( 0)
  #define IBECC_PARITY_ERR_INJ_DATA_ERR_EN_WID                         ( 8)
  #define IBECC_PARITY_ERR_INJ_DATA_ERR_EN_MSK                         (0x000000FF)
  #define IBECC_PARITY_ERR_INJ_DATA_ERR_EN_MIN                         (0)
  #define IBECC_PARITY_ERR_INJ_DATA_ERR_EN_MAX                         (255) // 0x000000FF
  #define IBECC_PARITY_ERR_INJ_DATA_ERR_EN_DEF                         (0x00000000)
  #define IBECC_PARITY_ERR_INJ_DATA_ERR_EN_HSH                         (0x0800DD90)

  #define IBECC_PARITY_ERR_INJ_RSVD1_OFF                               ( 8)
  #define IBECC_PARITY_ERR_INJ_RSVD1_WID                               ( 1)
  #define IBECC_PARITY_ERR_INJ_RSVD1_MSK                               (0x00000100)
  #define IBECC_PARITY_ERR_INJ_RSVD1_MIN                               (0)
  #define IBECC_PARITY_ERR_INJ_RSVD1_MAX                               (1) // 0x00000001
  #define IBECC_PARITY_ERR_INJ_RSVD1_DEF                               (0x00000000)
  #define IBECC_PARITY_ERR_INJ_RSVD1_HSH                               (0x0108DD90)

  #define IBECC_PARITY_ERR_INJ_BE_ERR_EN_OFF                           ( 9)
  #define IBECC_PARITY_ERR_INJ_BE_ERR_EN_WID                           ( 2)
  #define IBECC_PARITY_ERR_INJ_BE_ERR_EN_MSK                           (0x00000600)
  #define IBECC_PARITY_ERR_INJ_BE_ERR_EN_MIN                           (0)
  #define IBECC_PARITY_ERR_INJ_BE_ERR_EN_MAX                           (3) // 0x00000003
  #define IBECC_PARITY_ERR_INJ_BE_ERR_EN_DEF                           (0x00000000)
  #define IBECC_PARITY_ERR_INJ_BE_ERR_EN_HSH                           (0x0209DD90)

  #define IBECC_PARITY_ERR_INJ_RSVD2_OFF                               (11)
  #define IBECC_PARITY_ERR_INJ_RSVD2_WID                               ( 5)
  #define IBECC_PARITY_ERR_INJ_RSVD2_MSK                               (0x0000F800)
  #define IBECC_PARITY_ERR_INJ_RSVD2_MIN                               (0)
  #define IBECC_PARITY_ERR_INJ_RSVD2_MAX                               (31) // 0x0000001F
  #define IBECC_PARITY_ERR_INJ_RSVD2_DEF                               (0x00000000)
  #define IBECC_PARITY_ERR_INJ_RSVD2_HSH                               (0x050BDD90)

  #define IBECC_PARITY_ERR_INJ_ERR_INJ_MASK_OFF                        (16)
  #define IBECC_PARITY_ERR_INJ_ERR_INJ_MASK_WID                        ( 2)
  #define IBECC_PARITY_ERR_INJ_ERR_INJ_MASK_MSK                        (0x00030000)
  #define IBECC_PARITY_ERR_INJ_ERR_INJ_MASK_MIN                        (0)
  #define IBECC_PARITY_ERR_INJ_ERR_INJ_MASK_MAX                        (3) // 0x00000003
  #define IBECC_PARITY_ERR_INJ_ERR_INJ_MASK_DEF                        (0x00000000)
  #define IBECC_PARITY_ERR_INJ_ERR_INJ_MASK_HSH                        (0x0210DD90)

  #define IBECC_PARITY_ERR_INJ_RSVD3_OFF                               (18)
  #define IBECC_PARITY_ERR_INJ_RSVD3_WID                               (14)
  #define IBECC_PARITY_ERR_INJ_RSVD3_MSK                               (0xFFFC0000)
  #define IBECC_PARITY_ERR_INJ_RSVD3_MIN                               (0)
  #define IBECC_PARITY_ERR_INJ_RSVD3_MAX                               (16383) // 0x00003FFF
  #define IBECC_PARITY_ERR_INJ_RSVD3_DEF                               (0x00000000)
  #define IBECC_PARITY_ERR_INJ_RSVD3_HSH                               (0x0E12DD90)

#define IBECC_CONTROL_REG                                              (0x0000DD94)

  #define IBECC_CONTROL_OPERATION_MODE_OFF                             ( 0)
  #define IBECC_CONTROL_OPERATION_MODE_WID                             ( 2)
  #define IBECC_CONTROL_OPERATION_MODE_MSK                             (0x00000003)
  #define IBECC_CONTROL_OPERATION_MODE_MIN                             (0)
  #define IBECC_CONTROL_OPERATION_MODE_MAX                             (3) // 0x00000003
  #define IBECC_CONTROL_OPERATION_MODE_DEF                             (0x00000000)
  #define IBECC_CONTROL_OPERATION_MODE_HSH                             (0x0200DD94)

  #define IBECC_CONTROL_EC_DIS_OFF                                     ( 2)
  #define IBECC_CONTROL_EC_DIS_WID                                     ( 1)
  #define IBECC_CONTROL_EC_DIS_MSK                                     (0x00000004)
  #define IBECC_CONTROL_EC_DIS_MIN                                     (0)
  #define IBECC_CONTROL_EC_DIS_MAX                                     (1) // 0x00000001
  #define IBECC_CONTROL_EC_DIS_DEF                                     (0x00000000)
  #define IBECC_CONTROL_EC_DIS_HSH                                     (0x0102DD94)

  #define IBECC_CONTROL_DIS_PCH_EVENT_OFF                              ( 3)
  #define IBECC_CONTROL_DIS_PCH_EVENT_WID                              ( 1)
  #define IBECC_CONTROL_DIS_PCH_EVENT_MSK                              (0x00000008)
  #define IBECC_CONTROL_DIS_PCH_EVENT_MIN                              (0)
  #define IBECC_CONTROL_DIS_PCH_EVENT_MAX                              (1) // 0x00000001
  #define IBECC_CONTROL_DIS_PCH_EVENT_DEF                              (0x00000000)
  #define IBECC_CONTROL_DIS_PCH_EVENT_HSH                              (0x0103DD94)

  #define IBECC_CONTROL_DIS_MCA_LOG_OFF                                ( 4)
  #define IBECC_CONTROL_DIS_MCA_LOG_WID                                ( 1)
  #define IBECC_CONTROL_DIS_MCA_LOG_MSK                                (0x00000010)
  #define IBECC_CONTROL_DIS_MCA_LOG_MIN                                (0)
  #define IBECC_CONTROL_DIS_MCA_LOG_MAX                                (1) // 0x00000001
  #define IBECC_CONTROL_DIS_MCA_LOG_DEF                                (0x00000000)
  #define IBECC_CONTROL_DIS_MCA_LOG_HSH                                (0x0104DD94)

  #define IBECC_CONTROL_CLKGT_DIS_OFF                                  ( 5)
  #define IBECC_CONTROL_CLKGT_DIS_WID                                  ( 1)
  #define IBECC_CONTROL_CLKGT_DIS_MSK                                  (0x00000020)
  #define IBECC_CONTROL_CLKGT_DIS_MIN                                  (0)
  #define IBECC_CONTROL_CLKGT_DIS_MAX                                  (1) // 0x00000001
  #define IBECC_CONTROL_CLKGT_DIS_DEF                                  (0x00000000)
  #define IBECC_CONTROL_CLKGT_DIS_HSH                                  (0x0105DD94)

  #define IBECC_CONTROL_FORCE_ISM_ACTIVE_OFF                           ( 6)
  #define IBECC_CONTROL_FORCE_ISM_ACTIVE_WID                           ( 1)
  #define IBECC_CONTROL_FORCE_ISM_ACTIVE_MSK                           (0x00000040)
  #define IBECC_CONTROL_FORCE_ISM_ACTIVE_MIN                           (0)
  #define IBECC_CONTROL_FORCE_ISM_ACTIVE_MAX                           (1) // 0x00000001
  #define IBECC_CONTROL_FORCE_ISM_ACTIVE_DEF                           (0x00000000)
  #define IBECC_CONTROL_FORCE_ISM_ACTIVE_HSH                           (0x0106DD94)

  #define IBECC_CONTROL_FIXED_WINDOW_OFF                               ( 7)
  #define IBECC_CONTROL_FIXED_WINDOW_WID                               ( 1)
  #define IBECC_CONTROL_FIXED_WINDOW_MSK                               (0x00000080)
  #define IBECC_CONTROL_FIXED_WINDOW_MIN                               (0)
  #define IBECC_CONTROL_FIXED_WINDOW_MAX                               (1) // 0x00000001
  #define IBECC_CONTROL_FIXED_WINDOW_DEF                               (0x00000000)
  #define IBECC_CONTROL_FIXED_WINDOW_HSH                               (0x0107DD94)

  #define IBECC_CONTROL_RSVD8_OFF                                      ( 8)
  #define IBECC_CONTROL_RSVD8_WID                                      ( 1)
  #define IBECC_CONTROL_RSVD8_MSK                                      (0x00000100)
  #define IBECC_CONTROL_RSVD8_MIN                                      (0)
  #define IBECC_CONTROL_RSVD8_MAX                                      (1) // 0x00000001
  #define IBECC_CONTROL_RSVD8_DEF                                      (0x00000000)
  #define IBECC_CONTROL_RSVD8_HSH                                      (0x0108DD94)

  #define IBECC_CONTROL_DIS_RAW_HAZARD_OFF                             ( 9)
  #define IBECC_CONTROL_DIS_RAW_HAZARD_WID                             ( 1)
  #define IBECC_CONTROL_DIS_RAW_HAZARD_MSK                             (0x00000200)
  #define IBECC_CONTROL_DIS_RAW_HAZARD_MIN                             (0)
  #define IBECC_CONTROL_DIS_RAW_HAZARD_MAX                             (1) // 0x00000001
  #define IBECC_CONTROL_DIS_RAW_HAZARD_DEF                             (0x00000000)
  #define IBECC_CONTROL_DIS_RAW_HAZARD_HSH                             (0x0109DD94)

  #define IBECC_CONTROL_DIS_WAW_HAZARD_OFF                             (10)
  #define IBECC_CONTROL_DIS_WAW_HAZARD_WID                             ( 1)
  #define IBECC_CONTROL_DIS_WAW_HAZARD_MSK                             (0x00000400)
  #define IBECC_CONTROL_DIS_WAW_HAZARD_MIN                             (0)
  #define IBECC_CONTROL_DIS_WAW_HAZARD_MAX                             (1) // 0x00000001
  #define IBECC_CONTROL_DIS_WAW_HAZARD_DEF                             (0x00000000)
  #define IBECC_CONTROL_DIS_WAW_HAZARD_HSH                             (0x010ADD94)

  #define IBECC_CONTROL_DIS_WAR_HAZARD_OFF                             (11)
  #define IBECC_CONTROL_DIS_WAR_HAZARD_WID                             ( 1)
  #define IBECC_CONTROL_DIS_WAR_HAZARD_MSK                             (0x00000800)
  #define IBECC_CONTROL_DIS_WAR_HAZARD_MIN                             (0)
  #define IBECC_CONTROL_DIS_WAR_HAZARD_MAX                             (1) // 0x00000001
  #define IBECC_CONTROL_DIS_WAR_HAZARD_DEF                             (0x00000000)
  #define IBECC_CONTROL_DIS_WAR_HAZARD_HSH                             (0x010BDD94)

  #define IBECC_CONTROL_DIS_NOECC_WR_RSP_OFF                           (12)
  #define IBECC_CONTROL_DIS_NOECC_WR_RSP_WID                           ( 1)
  #define IBECC_CONTROL_DIS_NOECC_WR_RSP_MSK                           (0x00001000)
  #define IBECC_CONTROL_DIS_NOECC_WR_RSP_MIN                           (0)
  #define IBECC_CONTROL_DIS_NOECC_WR_RSP_MAX                           (1) // 0x00000001
  #define IBECC_CONTROL_DIS_NOECC_WR_RSP_DEF                           (0x00000000)
  #define IBECC_CONTROL_DIS_NOECC_WR_RSP_HSH                           (0x010CDD94)

  #define IBECC_CONTROL_DIS_ECC_PSTD_WR_OFF                            (13)
  #define IBECC_CONTROL_DIS_ECC_PSTD_WR_WID                            ( 1)
  #define IBECC_CONTROL_DIS_ECC_PSTD_WR_MSK                            (0x00002000)
  #define IBECC_CONTROL_DIS_ECC_PSTD_WR_MIN                            (0)
  #define IBECC_CONTROL_DIS_ECC_PSTD_WR_MAX                            (1) // 0x00000001
  #define IBECC_CONTROL_DIS_ECC_PSTD_WR_DEF                            (0x00000000)
  #define IBECC_CONTROL_DIS_ECC_PSTD_WR_HSH                            (0x010DDD94)

  #define IBECC_CONTROL_DIS_PERF_COUNTERS_OFF                          (14)
  #define IBECC_CONTROL_DIS_PERF_COUNTERS_WID                          ( 1)
  #define IBECC_CONTROL_DIS_PERF_COUNTERS_MSK                          (0x00004000)
  #define IBECC_CONTROL_DIS_PERF_COUNTERS_MIN                          (0)
  #define IBECC_CONTROL_DIS_PERF_COUNTERS_MAX                          (1) // 0x00000001
  #define IBECC_CONTROL_DIS_PERF_COUNTERS_DEF                          (0x00000000)
  #define IBECC_CONTROL_DIS_PERF_COUNTERS_HSH                          (0x010EDD94)

  #define IBECC_CONTROL_DISABLE_MULTIPLE_PCH_MSG_OFF                   (15)
  #define IBECC_CONTROL_DISABLE_MULTIPLE_PCH_MSG_WID                   ( 1)
  #define IBECC_CONTROL_DISABLE_MULTIPLE_PCH_MSG_MSK                   (0x00008000)
  #define IBECC_CONTROL_DISABLE_MULTIPLE_PCH_MSG_MIN                   (0)
  #define IBECC_CONTROL_DISABLE_MULTIPLE_PCH_MSG_MAX                   (1) // 0x00000001
  #define IBECC_CONTROL_DISABLE_MULTIPLE_PCH_MSG_DEF                   (0x00000000)
  #define IBECC_CONTROL_DISABLE_MULTIPLE_PCH_MSG_HSH                   (0x010FDD94)

  #define IBECC_CONTROL_ISM_IDLE_TIME_OFF                              (16)
  #define IBECC_CONTROL_ISM_IDLE_TIME_WID                              ( 8)
  #define IBECC_CONTROL_ISM_IDLE_TIME_MSK                              (0x00FF0000)
  #define IBECC_CONTROL_ISM_IDLE_TIME_MIN                              (0)
  #define IBECC_CONTROL_ISM_IDLE_TIME_MAX                              (255) // 0x000000FF
  #define IBECC_CONTROL_ISM_IDLE_TIME_DEF                              (0x00000010)
  #define IBECC_CONTROL_ISM_IDLE_TIME_HSH                              (0x0810DD94)

  #define IBECC_CONTROL_AGENT_WR_RSP_OFF                               (24)
  #define IBECC_CONTROL_AGENT_WR_RSP_WID                               ( 1)
  #define IBECC_CONTROL_AGENT_WR_RSP_MSK                               (0x01000000)
  #define IBECC_CONTROL_AGENT_WR_RSP_MIN                               (0)
  #define IBECC_CONTROL_AGENT_WR_RSP_MAX                               (1) // 0x00000001
  #define IBECC_CONTROL_AGENT_WR_RSP_DEF                               (0x00000000)
  #define IBECC_CONTROL_AGENT_WR_RSP_HSH                               (0x0118DD94)

  #define IBECC_CONTROL_RSB_ENABLE_OFF                                 (25)
  #define IBECC_CONTROL_RSB_ENABLE_WID                                 ( 1)
  #define IBECC_CONTROL_RSB_ENABLE_MSK                                 (0x02000000)
  #define IBECC_CONTROL_RSB_ENABLE_MIN                                 (0)
  #define IBECC_CONTROL_RSB_ENABLE_MAX                                 (1) // 0x00000001
  #define IBECC_CONTROL_RSB_ENABLE_DEF                                 (0x00000000)
  #define IBECC_CONTROL_RSB_ENABLE_HSH                                 (0x0119DD94)

  #define IBECC_CONTROL_DIS_CMI_EARLY_VALID_GEN_OFF                    (26)
  #define IBECC_CONTROL_DIS_CMI_EARLY_VALID_GEN_WID                    ( 1)
  #define IBECC_CONTROL_DIS_CMI_EARLY_VALID_GEN_MSK                    (0x04000000)
  #define IBECC_CONTROL_DIS_CMI_EARLY_VALID_GEN_MIN                    (0)
  #define IBECC_CONTROL_DIS_CMI_EARLY_VALID_GEN_MAX                    (1) // 0x00000001
  #define IBECC_CONTROL_DIS_CMI_EARLY_VALID_GEN_DEF                    (0x00000000)
  #define IBECC_CONTROL_DIS_CMI_EARLY_VALID_GEN_HSH                    (0x011ADD94)

  #define IBECC_CONTROL_RSVD_OFF                                       (27)
  #define IBECC_CONTROL_RSVD_WID                                       ( 5)
  #define IBECC_CONTROL_RSVD_MSK                                       (0xF8000000)
  #define IBECC_CONTROL_RSVD_MIN                                       (0)
  #define IBECC_CONTROL_RSVD_MAX                                       (31) // 0x0000001F
  #define IBECC_CONTROL_RSVD_DEF                                       (0x00000000)
  #define IBECC_CONTROL_RSVD_HSH                                       (0x051BDD94)

#define IBECC_ECC_INJ_CONTROL_REG                                      (0x0000DD98)

  #define IBECC_ECC_INJ_CONTROL_ECC_INJECT_OFF                         ( 0)
  #define IBECC_ECC_INJ_CONTROL_ECC_INJECT_WID                         ( 3)
  #define IBECC_ECC_INJ_CONTROL_ECC_INJECT_MSK                         (0x00000007)
  #define IBECC_ECC_INJ_CONTROL_ECC_INJECT_MIN                         (0)
  #define IBECC_ECC_INJ_CONTROL_ECC_INJECT_MAX                         (7) // 0x00000007
  #define IBECC_ECC_INJ_CONTROL_ECC_INJECT_DEF                         (0x00000000)
  #define IBECC_ECC_INJ_CONTROL_ECC_INJECT_HSH                         (0x0300DD98)

  #define IBECC_ECC_INJ_CONTROL_RSVD1_OFF                              ( 3)
  #define IBECC_ECC_INJ_CONTROL_RSVD1_WID                              ( 5)
  #define IBECC_ECC_INJ_CONTROL_RSVD1_MSK                              (0x000000F8)
  #define IBECC_ECC_INJ_CONTROL_RSVD1_MIN                              (0)
  #define IBECC_ECC_INJ_CONTROL_RSVD1_MAX                              (31) // 0x0000001F
  #define IBECC_ECC_INJ_CONTROL_RSVD1_DEF                              (0x00000000)
  #define IBECC_ECC_INJ_CONTROL_RSVD1_HSH                              (0x0503DD98)

  #define IBECC_ECC_INJ_CONTROL_COUNT_OFF                              ( 8)
  #define IBECC_ECC_INJ_CONTROL_COUNT_WID                              ( 8)
  #define IBECC_ECC_INJ_CONTROL_COUNT_MSK                              (0x0000FF00)
  #define IBECC_ECC_INJ_CONTROL_COUNT_MIN                              (0)
  #define IBECC_ECC_INJ_CONTROL_COUNT_MAX                              (255) // 0x000000FF
  #define IBECC_ECC_INJ_CONTROL_COUNT_DEF                              (0x00000000)
  #define IBECC_ECC_INJ_CONTROL_COUNT_HSH                              (0x0808DD98)

  #define IBECC_ECC_INJ_CONTROL_RSVD2_OFF                              (16)
  #define IBECC_ECC_INJ_CONTROL_RSVD2_WID                              (16)
  #define IBECC_ECC_INJ_CONTROL_RSVD2_MSK                              (0xFFFF0000)
  #define IBECC_ECC_INJ_CONTROL_RSVD2_MIN                              (0)
  #define IBECC_ECC_INJ_CONTROL_RSVD2_MAX                              (65535) // 0x0000FFFF
  #define IBECC_ECC_INJ_CONTROL_RSVD2_DEF                              (0x00000000)
  #define IBECC_ECC_INJ_CONTROL_RSVD2_HSH                              (0x1010DD98)

#define IBECC_ACCUM_CTRL_REG                                           (0x0000DDA0)

  #define IBECC_ACCUM_CTRL_CMD_CLEAR_OFF                               ( 0)
  #define IBECC_ACCUM_CTRL_CMD_CLEAR_WID                               ( 1)
  #define IBECC_ACCUM_CTRL_CMD_CLEAR_MSK                               (0x00000001)
  #define IBECC_ACCUM_CTRL_CMD_CLEAR_MIN                               (0)
  #define IBECC_ACCUM_CTRL_CMD_CLEAR_MAX                               (1) // 0x00000001
  #define IBECC_ACCUM_CTRL_CMD_CLEAR_DEF                               (0x00000000)
  #define IBECC_ACCUM_CTRL_CMD_CLEAR_HSH                               (0x0100DDA0)

  #define IBECC_ACCUM_CTRL_CMD_ENABLE_OFF                              ( 1)
  #define IBECC_ACCUM_CTRL_CMD_ENABLE_WID                              ( 1)
  #define IBECC_ACCUM_CTRL_CMD_ENABLE_MSK                              (0x00000002)
  #define IBECC_ACCUM_CTRL_CMD_ENABLE_MIN                              (0)
  #define IBECC_ACCUM_CTRL_CMD_ENABLE_MAX                              (1) // 0x00000001
  #define IBECC_ACCUM_CTRL_CMD_ENABLE_DEF                              (0x00000000)
  #define IBECC_ACCUM_CTRL_CMD_ENABLE_HSH                              (0x0101DDA0)

  #define IBECC_ACCUM_CTRL_CMD_FUNC_OV_OFF                             ( 2)
  #define IBECC_ACCUM_CTRL_CMD_FUNC_OV_WID                             ( 1)
  #define IBECC_ACCUM_CTRL_CMD_FUNC_OV_MSK                             (0x00000004)
  #define IBECC_ACCUM_CTRL_CMD_FUNC_OV_MIN                             (0)
  #define IBECC_ACCUM_CTRL_CMD_FUNC_OV_MAX                             (1) // 0x00000001
  #define IBECC_ACCUM_CTRL_CMD_FUNC_OV_DEF                             (0x00000000)
  #define IBECC_ACCUM_CTRL_CMD_FUNC_OV_HSH                             (0x0102DDA0)

  #define IBECC_ACCUM_CTRL_RESERVED_OFF                                ( 3)
  #define IBECC_ACCUM_CTRL_RESERVED_WID                                (29)
  #define IBECC_ACCUM_CTRL_RESERVED_MSK                                (0xFFFFFFF8)
  #define IBECC_ACCUM_CTRL_RESERVED_MIN                                (0)
  #define IBECC_ACCUM_CTRL_RESERVED_MAX                                (536870911) // 0x1FFFFFFF
  #define IBECC_ACCUM_CTRL_RESERVED_DEF                                (0x00000000)
  #define IBECC_ACCUM_CTRL_RESERVED_HSH                                (0x1D03DDA0)

#define IBECC_REQUEST_PORT_ACCUM_RD_CPL_OUT_REG                        (0x0000DDA4)

  #define IBECC_REQUEST_PORT_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_OFF       ( 0)
  #define IBECC_REQUEST_PORT_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_WID       (16)
  #define IBECC_REQUEST_PORT_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_MSK       (0x0000FFFF)
  #define IBECC_REQUEST_PORT_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_MIN       (0)
  #define IBECC_REQUEST_PORT_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_MAX       (65535) // 0x0000FFFF
  #define IBECC_REQUEST_PORT_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_DEF       (0x00000000)
  #define IBECC_REQUEST_PORT_ACCUM_RD_CPL_OUT_RD_CPL_CMD_SUM_HSH       (0x1000DDA4)

  #define IBECC_REQUEST_PORT_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_OFF      (16)
  #define IBECC_REQUEST_PORT_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_WID      (16)
  #define IBECC_REQUEST_PORT_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_MSK      (0xFFFF0000)
  #define IBECC_REQUEST_PORT_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_MIN      (0)
  #define IBECC_REQUEST_PORT_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_MAX      (65535) // 0x0000FFFF
  #define IBECC_REQUEST_PORT_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_DEF      (0x00000000)
  #define IBECC_REQUEST_PORT_ACCUM_RD_CPL_OUT_RD_CPL_DATA_SUM_HSH      (0x1010DDA4)

#define IBECC_REQUEST_PORT_ACCUM_REQ_IN_REG                            (0x0000DDA8)

  #define IBECC_REQUEST_PORT_ACCUM_REQ_IN_REQ_CMD_SUM_OFF              ( 0)
  #define IBECC_REQUEST_PORT_ACCUM_REQ_IN_REQ_CMD_SUM_WID              (16)
  #define IBECC_REQUEST_PORT_ACCUM_REQ_IN_REQ_CMD_SUM_MSK              (0x0000FFFF)
  #define IBECC_REQUEST_PORT_ACCUM_REQ_IN_REQ_CMD_SUM_MIN              (0)
  #define IBECC_REQUEST_PORT_ACCUM_REQ_IN_REQ_CMD_SUM_MAX              (65535) // 0x0000FFFF
  #define IBECC_REQUEST_PORT_ACCUM_REQ_IN_REQ_CMD_SUM_DEF              (0x00000000)
  #define IBECC_REQUEST_PORT_ACCUM_REQ_IN_REQ_CMD_SUM_HSH              (0x1000DDA8)

  #define IBECC_REQUEST_PORT_ACCUM_REQ_IN_REQ_DATA_SUM_OFF             (16)
  #define IBECC_REQUEST_PORT_ACCUM_REQ_IN_REQ_DATA_SUM_WID             (16)
  #define IBECC_REQUEST_PORT_ACCUM_REQ_IN_REQ_DATA_SUM_MSK             (0xFFFF0000)
  #define IBECC_REQUEST_PORT_ACCUM_REQ_IN_REQ_DATA_SUM_MIN             (0)
  #define IBECC_REQUEST_PORT_ACCUM_REQ_IN_REQ_DATA_SUM_MAX             (65535) // 0x0000FFFF
  #define IBECC_REQUEST_PORT_ACCUM_REQ_IN_REQ_DATA_SUM_DEF             (0x00000000)
  #define IBECC_REQUEST_PORT_ACCUM_REQ_IN_REQ_DATA_SUM_HSH             (0x1010DDA8)

#define IBECC_REQ_L3_ARB_CONFIG_REG                                    (0x0000DDB0)

  #define IBECC_REQ_L3_ARB_CONFIG_NonVC1Wr_HiPri_Park_Size_OFF         ( 0)
  #define IBECC_REQ_L3_ARB_CONFIG_NonVC1Wr_HiPri_Park_Size_WID         ( 4)
  #define IBECC_REQ_L3_ARB_CONFIG_NonVC1Wr_HiPri_Park_Size_MSK         (0x0000000F)
  #define IBECC_REQ_L3_ARB_CONFIG_NonVC1Wr_HiPri_Park_Size_MIN         (0)
  #define IBECC_REQ_L3_ARB_CONFIG_NonVC1Wr_HiPri_Park_Size_MAX         (15) // 0x0000000F
  #define IBECC_REQ_L3_ARB_CONFIG_NonVC1Wr_HiPri_Park_Size_DEF         (0x00000008)
  #define IBECC_REQ_L3_ARB_CONFIG_NonVC1Wr_HiPri_Park_Size_HSH         (0x0400DDB0)

  #define IBECC_REQ_L3_ARB_CONFIG_NonVC1Wr_LoPri_Park_Size_OFF         ( 4)
  #define IBECC_REQ_L3_ARB_CONFIG_NonVC1Wr_LoPri_Park_Size_WID         ( 4)
  #define IBECC_REQ_L3_ARB_CONFIG_NonVC1Wr_LoPri_Park_Size_MSK         (0x000000F0)
  #define IBECC_REQ_L3_ARB_CONFIG_NonVC1Wr_LoPri_Park_Size_MIN         (0)
  #define IBECC_REQ_L3_ARB_CONFIG_NonVC1Wr_LoPri_Park_Size_MAX         (15) // 0x0000000F
  #define IBECC_REQ_L3_ARB_CONFIG_NonVC1Wr_LoPri_Park_Size_DEF         (0x00000002)
  #define IBECC_REQ_L3_ARB_CONFIG_NonVC1Wr_LoPri_Park_Size_HSH         (0x0404DDB0)

  #define IBECC_REQ_L3_ARB_CONFIG_VC1Wr_HiPri_Park_Size_OFF            ( 8)
  #define IBECC_REQ_L3_ARB_CONFIG_VC1Wr_HiPri_Park_Size_WID            ( 4)
  #define IBECC_REQ_L3_ARB_CONFIG_VC1Wr_HiPri_Park_Size_MSK            (0x00000F00)
  #define IBECC_REQ_L3_ARB_CONFIG_VC1Wr_HiPri_Park_Size_MIN            (0)
  #define IBECC_REQ_L3_ARB_CONFIG_VC1Wr_HiPri_Park_Size_MAX            (15) // 0x0000000F
  #define IBECC_REQ_L3_ARB_CONFIG_VC1Wr_HiPri_Park_Size_DEF            (0x00000008)
  #define IBECC_REQ_L3_ARB_CONFIG_VC1Wr_HiPri_Park_Size_HSH            (0x0408DDB0)

  #define IBECC_REQ_L3_ARB_CONFIG_VC1Wr_LoPri_Park_Size_OFF            (12)
  #define IBECC_REQ_L3_ARB_CONFIG_VC1Wr_LoPri_Park_Size_WID            ( 4)
  #define IBECC_REQ_L3_ARB_CONFIG_VC1Wr_LoPri_Park_Size_MSK            (0x0000F000)
  #define IBECC_REQ_L3_ARB_CONFIG_VC1Wr_LoPri_Park_Size_MIN            (0)
  #define IBECC_REQ_L3_ARB_CONFIG_VC1Wr_LoPri_Park_Size_MAX            (15) // 0x0000000F
  #define IBECC_REQ_L3_ARB_CONFIG_VC1Wr_LoPri_Park_Size_DEF            (0x00000002)
  #define IBECC_REQ_L3_ARB_CONFIG_VC1Wr_LoPri_Park_Size_HSH            (0x040CDDB0)

  #define IBECC_REQ_L3_ARB_CONFIG_Reserved_OFF                         (16)
  #define IBECC_REQ_L3_ARB_CONFIG_Reserved_WID                         (16)
  #define IBECC_REQ_L3_ARB_CONFIG_Reserved_MSK                         (0xFFFF0000)
  #define IBECC_REQ_L3_ARB_CONFIG_Reserved_MIN                         (0)
  #define IBECC_REQ_L3_ARB_CONFIG_Reserved_MAX                         (65535) // 0x0000FFFF
  #define IBECC_REQ_L3_ARB_CONFIG_Reserved_DEF                         (0x00000000)
  #define IBECC_REQ_L3_ARB_CONFIG_Reserved_HSH                         (0x1010DDB0)

#define IBECC_MBIST_POST_CTRL_RSB_REG                                  (0x0000DDB8)

  #define IBECC_MBIST_POST_CTRL_RSB_PASS_OFF                           ( 0)
  #define IBECC_MBIST_POST_CTRL_RSB_PASS_WID                           ( 1)
  #define IBECC_MBIST_POST_CTRL_RSB_PASS_MSK                           (0x00000001)
  #define IBECC_MBIST_POST_CTRL_RSB_PASS_MIN                           (0)
  #define IBECC_MBIST_POST_CTRL_RSB_PASS_MAX                           (1) // 0x00000001
  #define IBECC_MBIST_POST_CTRL_RSB_PASS_DEF                           (0x00000000)
  #define IBECC_MBIST_POST_CTRL_RSB_PASS_HSH                           (0x0100DDB8)

  #define IBECC_MBIST_POST_CTRL_RSB_COMPLETE_OFF                       ( 1)
  #define IBECC_MBIST_POST_CTRL_RSB_COMPLETE_WID                       ( 1)
  #define IBECC_MBIST_POST_CTRL_RSB_COMPLETE_MSK                       (0x00000002)
  #define IBECC_MBIST_POST_CTRL_RSB_COMPLETE_MIN                       (0)
  #define IBECC_MBIST_POST_CTRL_RSB_COMPLETE_MAX                       (1) // 0x00000001
  #define IBECC_MBIST_POST_CTRL_RSB_COMPLETE_DEF                       (0x00000000)
  #define IBECC_MBIST_POST_CTRL_RSB_COMPLETE_HSH                       (0x0101DDB8)

  #define IBECC_MBIST_POST_CTRL_RSB_RSVD1_OFF                          ( 2)
  #define IBECC_MBIST_POST_CTRL_RSB_RSVD1_WID                          ( 6)
  #define IBECC_MBIST_POST_CTRL_RSB_RSVD1_MSK                          (0x000000FC)
  #define IBECC_MBIST_POST_CTRL_RSB_RSVD1_MIN                          (0)
  #define IBECC_MBIST_POST_CTRL_RSB_RSVD1_MAX                          (63) // 0x0000003F
  #define IBECC_MBIST_POST_CTRL_RSB_RSVD1_DEF                          (0x00000000)
  #define IBECC_MBIST_POST_CTRL_RSB_RSVD1_HSH                          (0x0602DDB8)

  #define IBECC_MBIST_POST_CTRL_RSB_MBIST_FAIL_INJECT_OFF              ( 8)
  #define IBECC_MBIST_POST_CTRL_RSB_MBIST_FAIL_INJECT_WID              ( 1)
  #define IBECC_MBIST_POST_CTRL_RSB_MBIST_FAIL_INJECT_MSK              (0x00000100)
  #define IBECC_MBIST_POST_CTRL_RSB_MBIST_FAIL_INJECT_MIN              (0)
  #define IBECC_MBIST_POST_CTRL_RSB_MBIST_FAIL_INJECT_MAX              (1) // 0x00000001
  #define IBECC_MBIST_POST_CTRL_RSB_MBIST_FAIL_INJECT_DEF              (0x00000000)
  #define IBECC_MBIST_POST_CTRL_RSB_MBIST_FAIL_INJECT_HSH              (0x0108DDB8)

  #define IBECC_MBIST_POST_CTRL_RSB_RSVD2_OFF                          ( 9)
  #define IBECC_MBIST_POST_CTRL_RSB_RSVD2_WID                          (22)
  #define IBECC_MBIST_POST_CTRL_RSB_RSVD2_MSK                          (0x7FFFFE00)
  #define IBECC_MBIST_POST_CTRL_RSB_RSVD2_MIN                          (0)
  #define IBECC_MBIST_POST_CTRL_RSB_RSVD2_MAX                          (4194303) // 0x003FFFFF
  #define IBECC_MBIST_POST_CTRL_RSB_RSVD2_DEF                          (0x00000000)
  #define IBECC_MBIST_POST_CTRL_RSB_RSVD2_HSH                          (0x1609DDB8)

  #define IBECC_MBIST_POST_CTRL_RSB_RUN_BUSY_OFF                       (31)
  #define IBECC_MBIST_POST_CTRL_RSB_RUN_BUSY_WID                       ( 1)
  #define IBECC_MBIST_POST_CTRL_RSB_RUN_BUSY_MSK                       (0x80000000)
  #define IBECC_MBIST_POST_CTRL_RSB_RUN_BUSY_MIN                       (0)
  #define IBECC_MBIST_POST_CTRL_RSB_RUN_BUSY_MAX                       (1) // 0x00000001
  #define IBECC_MBIST_POST_CTRL_RSB_RUN_BUSY_DEF                       (0x00000000)
  #define IBECC_MBIST_POST_CTRL_RSB_RUN_BUSY_HSH                       (0x011FDDB8)

#define IBECC_ECC_VC0_SYND_RD_REQCOUNT_REG                             (0x0000DDC0)

  #define IBECC_ECC_VC0_SYND_RD_REQCOUNT_COUNT_OFF                     ( 0)
  #define IBECC_ECC_VC0_SYND_RD_REQCOUNT_COUNT_WID                     (64)
  #define IBECC_ECC_VC0_SYND_RD_REQCOUNT_COUNT_MSK                     (0xFFFFFFFFFFFFFFFFULL)
  #define IBECC_ECC_VC0_SYND_RD_REQCOUNT_COUNT_MIN                     (0)
  #define IBECC_ECC_VC0_SYND_RD_REQCOUNT_COUNT_MAX                     (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define IBECC_ECC_VC0_SYND_RD_REQCOUNT_COUNT_DEF                     (0x00000000)
  #define IBECC_ECC_VC0_SYND_RD_REQCOUNT_COUNT_HSH                     (0x4000DDC0)

#define IBECC_ECC_VC1_SYND_RD_REQCOUNT_REG                             (0x0000DDC8)

  #define IBECC_ECC_VC1_SYND_RD_REQCOUNT_COUNT_OFF                     ( 0)
  #define IBECC_ECC_VC1_SYND_RD_REQCOUNT_COUNT_WID                     (64)
  #define IBECC_ECC_VC1_SYND_RD_REQCOUNT_COUNT_MSK                     (0xFFFFFFFFFFFFFFFFULL)
  #define IBECC_ECC_VC1_SYND_RD_REQCOUNT_COUNT_MIN                     (0)
  #define IBECC_ECC_VC1_SYND_RD_REQCOUNT_COUNT_MAX                     (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define IBECC_ECC_VC1_SYND_RD_REQCOUNT_COUNT_DEF                     (0x00000000)
  #define IBECC_ECC_VC1_SYND_RD_REQCOUNT_COUNT_HSH                     (0x4000DDC8)

#define IBECC_ECC_VC0_SYND_WR_REQCOUNT_REG                             (0x0000DDD0)

  #define IBECC_ECC_VC0_SYND_WR_REQCOUNT_COUNT_OFF                     ( 0)
  #define IBECC_ECC_VC0_SYND_WR_REQCOUNT_COUNT_WID                     (64)
  #define IBECC_ECC_VC0_SYND_WR_REQCOUNT_COUNT_MSK                     (0xFFFFFFFFFFFFFFFFULL)
  #define IBECC_ECC_VC0_SYND_WR_REQCOUNT_COUNT_MIN                     (0)
  #define IBECC_ECC_VC0_SYND_WR_REQCOUNT_COUNT_MAX                     (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define IBECC_ECC_VC0_SYND_WR_REQCOUNT_COUNT_DEF                     (0x00000000)
  #define IBECC_ECC_VC0_SYND_WR_REQCOUNT_COUNT_HSH                     (0x4000DDD0)

#define IBECC_ECC_VC1_SYND_WR_REQCOUNT_REG                             (0x0000DDD8)

  #define IBECC_ECC_VC1_SYND_WR_REQCOUNT_COUNT_OFF                     ( 0)
  #define IBECC_ECC_VC1_SYND_WR_REQCOUNT_COUNT_WID                     (64)
  #define IBECC_ECC_VC1_SYND_WR_REQCOUNT_COUNT_MSK                     (0xFFFFFFFFFFFFFFFFULL)
  #define IBECC_ECC_VC1_SYND_WR_REQCOUNT_COUNT_MIN                     (0)
  #define IBECC_ECC_VC1_SYND_WR_REQCOUNT_COUNT_MAX                     (18446744073709551615ULL) // 0xFFFFFFFFFFFFFFFF
  #define IBECC_ECC_VC1_SYND_WR_REQCOUNT_COUNT_DEF                     (0x00000000)
  #define IBECC_ECC_VC1_SYND_WR_REQCOUNT_COUNT_HSH                     (0x4000DDD8)
#pragma pack(pop)
#endif
