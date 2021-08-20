#ifndef __MrcMcRegisterStructIclDxxx_h__
#define __MrcMcRegisterStructIclDxxx_h__
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

typedef union {
  struct {
    UINT32 Control_PolicyLow                       :  32;  // Bits 31:0
    UINT32 Control_PolicyHigh                      :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC0_CR_CADB_ACCESS_CONTROL_POLICY_STRUCT;

typedef union {
  struct {
    UINT32 Read_PolicyLow                          :  32;  // Bits 31:0
    UINT32 Read_PolicyHigh                         :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC0_CR_CADB_ACCESS_READ_POLICY_STRUCT;

typedef union {
  struct {
    UINT32 Write_PolicyLow                         :  32;  // Bits 31:0
    UINT32 Write_PolicyHigh                        :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC0_CR_CADB_ACCESS_WRITE_POLICY_STRUCT;

typedef union {
  struct {
    UINT32 START_TEST                              :  1;  // Bits 0:0
    UINT32 STOP_TEST                               :  1;  // Bits 1:1
    UINT32                                         :  30;  // Bits 31:2
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CADB_CTL_STRUCT;

typedef union {
  struct {
    UINT32 CMD_DESELECT_START                      :  4;  // Bits 3:0
    UINT32 CMD_DESELECT_STOP                       :  4;  // Bits 7:4
    UINT32 LANE_DESELECT_EN                        :  3;  // Bits 10:8
    UINT32 INITIAL_DSEL_EN                         :  1;  // Bits 11:11
    UINT32 INITIAL_DSEL_SSEQ_EN                    :  1;  // Bits 12:12
    UINT32 CADB_DSEL_THROTTLE_MODE                 :  3;  // Bits 15:13
    UINT32 CADB_SEL_THROTTLE_MODE                  :  3;  // Bits 18:16
    UINT32                                         :  5;  // Bits 23:19
    UINT32 CADB_TO_CPGC_BIND                       :  1;  // Bits 24:24
    UINT32 GLOBAL_START_BIND                       :  1;  // Bits 25:25
    UINT32 GLOBAL_STOP_BIND                        :  1;  // Bits 26:26
    UINT32                                         :  2;  // Bits 28:27
    UINT32 CADB_MODE                               :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CADB_CFG_STRUCT;

typedef union {
  struct {
    UINT32 START_DELAY                             :  10;  // Bits 9:0
    UINT32                                         :  6;  // Bits 15:10
    UINT32 STOP_DELAY                              :  10;  // Bits 25:16
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CADB_DLY_STRUCT;

typedef union {
  struct {
    UINT32                                         :  21;  // Bits 20:0
    UINT32 MRS_CURR_PTR                            :  3;  // Bits 23:21
    UINT32 TEST_ABORTED                            :  1;  // Bits 24:24
    UINT32                                         :  3;  // Bits 27:25
    UINT32 ALGO_DONE                               :  1;  // Bits 28:28
    UINT32 START_TEST_DELAY_BUSY                   :  1;  // Bits 29:29
    UINT32 TEST_BUSY                               :  1;  // Bits 30:30
    UINT32 TEST_DONE                               :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CADB_STATUS_STRUCT;

typedef union {
  struct {
    UINT8  UNISEQ_MODE                             :  2;  // Bits 1:0
    UINT8                                          :  1;  // Bits 2:2
    UINT8  UNISEQ_LFSR_POLYNOMIAL_SIZE             :  3;  // Bits 5:3
    UINT8                                          :  2;  // Bits 7:6
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_STRUCT;

typedef union {
  struct {
    UINT8  UNISEQ_MODE                             :  2;  // Bits 1:0
    UINT8                                          :  1;  // Bits 2:2
    UINT8  UNISEQ_LFSR_POLYNOMIAL_SIZE             :  3;  // Bits 5:3
    UINT8                                          :  2;  // Bits 7:6
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_STRUCT;

typedef union {
  struct {
    UINT8  UNISEQ_MODE                             :  2;  // Bits 1:0
    UINT8                                          :  1;  // Bits 2:2
    UINT8  UNISEQ_LFSR_POLYNOMIAL_SIZE             :  3;  // Bits 5:3
    UINT8                                          :  2;  // Bits 7:6
  } Bits;
  UINT8  Data;
} CH0_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_STRUCT;

typedef union {
  struct {
    UINT32 CMD                                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_0_STRUCT;

typedef union {
  struct {
    UINT32 CMD                                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_1_STRUCT;

typedef union {
  struct {
    UINT32 CMD                                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CADB_DSEL_UNISEQ_PBUF_2_STRUCT;

typedef union {
  struct {
    UINT32 L_SEL                                   :  1;  // Bits 0:0
    UINT32                                         :  3;  // Bits 3:1
    UINT32 L_COUNTER_HI                            :  4;  // Bits 7:4
    UINT32 L_CNT                                   :  8;  // Bits 15:8
    UINT32 N_CNT                                   :  8;  // Bits 23:16
    UINT32 M_CNT                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CADB_DSEL_UNISEQ_LMN_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC0_CR_CADB_BUF_0_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC0_CR_CADB_BUF_1_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC0_CR_CADB_BUF_2_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC0_CR_CADB_BUF_3_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC0_CR_CADB_BUF_4_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC0_CR_CADB_BUF_5_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC0_CR_CADB_BUF_6_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC0_CR_CADB_BUF_7_STRUCT;

typedef union {
  struct {
    UINT32 MRS_GAP_SCALE                           :  1;  // Bits 0:0
    UINT32 MRS_GAP                                 :  4;  // Bits 4:1
    UINT32                                         :  3;  // Bits 7:5
    UINT32 MRS_AO_REPEATS                          :  16;  // Bits 23:8
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CADB_AO_MRSCFG_STRUCT;

typedef union {
  struct {
    UINT32 WR_SELECT_ENABLE                        :  3;  // Bits 2:0
    UINT32                                         :  5;  // Bits 7:3
    UINT32 RD_SELECT_ENABLE                        :  3;  // Bits 10:8
    UINT32                                         :  5;  // Bits 15:11
    UINT32 ACT_SELECT_ENABLE                       :  3;  // Bits 18:16
    UINT32                                         :  5;  // Bits 23:19
    UINT32 PRE_SELECT_ENABLE                       :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 INITIAL_SEL_SSEQ_EN                     :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC0_CR_CADB_SELCFG_STRUCT;

typedef union {
  struct {
    UINT32 CS_CLOCKS                               :  3;  // Bits 2:0
    UINT32 DSEL_CLOCKS                             :  4;  // Bits 6:3
    UINT32                                         :  1;  // Bits 7:7
    UINT32 SETUP_CLOCKS                            :  3;  // Bits 10:8
    UINT32 CS_ACTIVE_POLARITY                      :  1;  // Bits 11:11
    UINT32 MRS_START_PTR                           :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 MRS_END_PTR                             :  3;  // Bits 18:16
    UINT32 MRS_GOTO_PTR                            :  3;  // Bits 21:19
    UINT32 MRS_CS_MODE                             :  2;  // Bits 23:22
    UINT32 MRS_DELAY_CNTLow                        :  8;  // Bits 31:24
    UINT32 MRS_DELAY_CNTHigh                       :  8;  // Bits 39:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC0_CR_CADB_MRSCFG_STRUCT;

typedef union {
  struct {
    UINT32 Control_PolicyLow                       :  32;  // Bits 31:0
    UINT32 Control_PolicyHigh                      :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC1_CR_CADB_ACCESS_CONTROL_POLICY_STRUCT;

typedef union {
  struct {
    UINT32 Read_PolicyLow                          :  32;  // Bits 31:0
    UINT32 Read_PolicyHigh                         :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC1_CR_CADB_ACCESS_READ_POLICY_STRUCT;

typedef union {
  struct {
    UINT32 Write_PolicyLow                         :  32;  // Bits 31:0
    UINT32 Write_PolicyHigh                        :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC1_CR_CADB_ACCESS_WRITE_POLICY_STRUCT;

typedef union {
  struct {
    UINT32 START_TEST                              :  1;  // Bits 0:0
    UINT32 STOP_TEST                               :  1;  // Bits 1:1
    UINT32                                         :  30;  // Bits 31:2
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CADB_CTL_STRUCT;

typedef union {
  struct {
    UINT32 CMD_DESELECT_START                      :  4;  // Bits 3:0
    UINT32 CMD_DESELECT_STOP                       :  4;  // Bits 7:4
    UINT32 LANE_DESELECT_EN                        :  3;  // Bits 10:8
    UINT32 INITIAL_DSEL_EN                         :  1;  // Bits 11:11
    UINT32 INITIAL_DSEL_SSEQ_EN                    :  1;  // Bits 12:12
    UINT32 CADB_DSEL_THROTTLE_MODE                 :  3;  // Bits 15:13
    UINT32 CADB_SEL_THROTTLE_MODE                  :  3;  // Bits 18:16
    UINT32                                         :  5;  // Bits 23:19
    UINT32 CADB_TO_CPGC_BIND                       :  1;  // Bits 24:24
    UINT32 GLOBAL_START_BIND                       :  1;  // Bits 25:25
    UINT32 GLOBAL_STOP_BIND                        :  1;  // Bits 26:26
    UINT32                                         :  2;  // Bits 28:27
    UINT32 CADB_MODE                               :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CADB_CFG_STRUCT;

typedef union {
  struct {
    UINT32 START_DELAY                             :  10;  // Bits 9:0
    UINT32                                         :  6;  // Bits 15:10
    UINT32 STOP_DELAY                              :  10;  // Bits 25:16
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CADB_DLY_STRUCT;

typedef union {
  struct {
    UINT32                                         :  21;  // Bits 20:0
    UINT32 MRS_CURR_PTR                            :  3;  // Bits 23:21
    UINT32 TEST_ABORTED                            :  1;  // Bits 24:24
    UINT32                                         :  3;  // Bits 27:25
    UINT32 ALGO_DONE                               :  1;  // Bits 28:28
    UINT32 START_TEST_DELAY_BUSY                   :  1;  // Bits 29:29
    UINT32 TEST_BUSY                               :  1;  // Bits 30:30
    UINT32 TEST_DONE                               :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CADB_STATUS_STRUCT;

typedef union {
  struct {
    UINT8  UNISEQ_MODE                             :  2;  // Bits 1:0
    UINT8                                          :  1;  // Bits 2:2
    UINT8  UNISEQ_LFSR_POLYNOMIAL_SIZE             :  3;  // Bits 5:3
    UINT8                                          :  2;  // Bits 7:6
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_STRUCT;

typedef union {
  struct {
    UINT8  UNISEQ_MODE                             :  2;  // Bits 1:0
    UINT8                                          :  1;  // Bits 2:2
    UINT8  UNISEQ_LFSR_POLYNOMIAL_SIZE             :  3;  // Bits 5:3
    UINT8                                          :  2;  // Bits 7:6
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_STRUCT;

typedef union {
  struct {
    UINT8  UNISEQ_MODE                             :  2;  // Bits 1:0
    UINT8                                          :  1;  // Bits 2:2
    UINT8  UNISEQ_LFSR_POLYNOMIAL_SIZE             :  3;  // Bits 5:3
    UINT8                                          :  2;  // Bits 7:6
  } Bits;
  UINT8  Data;
} CH0_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_STRUCT;

typedef union {
  struct {
    UINT32 CMD                                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_0_STRUCT;

typedef union {
  struct {
    UINT32 CMD                                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_1_STRUCT;

typedef union {
  struct {
    UINT32 CMD                                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CADB_DSEL_UNISEQ_PBUF_2_STRUCT;

typedef union {
  struct {
    UINT32 L_SEL                                   :  1;  // Bits 0:0
    UINT32                                         :  3;  // Bits 3:1
    UINT32 L_COUNTER_HI                            :  4;  // Bits 7:4
    UINT32 L_CNT                                   :  8;  // Bits 15:8
    UINT32 N_CNT                                   :  8;  // Bits 23:16
    UINT32 M_CNT                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CADB_DSEL_UNISEQ_LMN_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC1_CR_CADB_BUF_0_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC1_CR_CADB_BUF_1_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC1_CR_CADB_BUF_2_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC1_CR_CADB_BUF_3_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC1_CR_CADB_BUF_4_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC1_CR_CADB_BUF_5_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC1_CR_CADB_BUF_6_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC1_CR_CADB_BUF_7_STRUCT;

typedef union {
  struct {
    UINT32 MRS_GAP_SCALE                           :  1;  // Bits 0:0
    UINT32 MRS_GAP                                 :  4;  // Bits 4:1
    UINT32                                         :  3;  // Bits 7:5
    UINT32 MRS_AO_REPEATS                          :  16;  // Bits 23:8
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CADB_AO_MRSCFG_STRUCT;

typedef union {
  struct {
    UINT32 WR_SELECT_ENABLE                        :  3;  // Bits 2:0
    UINT32                                         :  5;  // Bits 7:3
    UINT32 RD_SELECT_ENABLE                        :  3;  // Bits 10:8
    UINT32                                         :  5;  // Bits 15:11
    UINT32 ACT_SELECT_ENABLE                       :  3;  // Bits 18:16
    UINT32                                         :  5;  // Bits 23:19
    UINT32 PRE_SELECT_ENABLE                       :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 INITIAL_SEL_SSEQ_EN                     :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_SC1_CR_CADB_SELCFG_STRUCT;

typedef union {
  struct {
    UINT32 CS_CLOCKS                               :  3;  // Bits 2:0
    UINT32 DSEL_CLOCKS                             :  4;  // Bits 6:3
    UINT32                                         :  1;  // Bits 7:7
    UINT32 SETUP_CLOCKS                            :  3;  // Bits 10:8
    UINT32 CS_ACTIVE_POLARITY                      :  1;  // Bits 11:11
    UINT32 MRS_START_PTR                           :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 MRS_END_PTR                             :  3;  // Bits 18:16
    UINT32 MRS_GOTO_PTR                            :  3;  // Bits 21:19
    UINT32 MRS_CS_MODE                             :  2;  // Bits 23:22
    UINT32 MRS_DELAY_CNTLow                        :  8;  // Bits 31:24
    UINT32 MRS_DELAY_CNTHigh                       :  8;  // Bits 39:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_SC1_CR_CADB_MRSCFG_STRUCT;

typedef union {
  struct {
    UINT32 Control_PolicyLow                       :  32;  // Bits 31:0
    UINT32 Control_PolicyHigh                      :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC0_CR_CADB_ACCESS_CONTROL_POLICY_STRUCT;

typedef union {
  struct {
    UINT32 Read_PolicyLow                          :  32;  // Bits 31:0
    UINT32 Read_PolicyHigh                         :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC0_CR_CADB_ACCESS_READ_POLICY_STRUCT;

typedef union {
  struct {
    UINT32 Write_PolicyLow                         :  32;  // Bits 31:0
    UINT32 Write_PolicyHigh                        :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC0_CR_CADB_ACCESS_WRITE_POLICY_STRUCT;

typedef union {
  struct {
    UINT32 START_TEST                              :  1;  // Bits 0:0
    UINT32 STOP_TEST                               :  1;  // Bits 1:1
    UINT32                                         :  30;  // Bits 31:2
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CADB_CTL_STRUCT;

typedef union {
  struct {
    UINT32 CMD_DESELECT_START                      :  4;  // Bits 3:0
    UINT32 CMD_DESELECT_STOP                       :  4;  // Bits 7:4
    UINT32 LANE_DESELECT_EN                        :  3;  // Bits 10:8
    UINT32 INITIAL_DSEL_EN                         :  1;  // Bits 11:11
    UINT32 INITIAL_DSEL_SSEQ_EN                    :  1;  // Bits 12:12
    UINT32 CADB_DSEL_THROTTLE_MODE                 :  3;  // Bits 15:13
    UINT32 CADB_SEL_THROTTLE_MODE                  :  3;  // Bits 18:16
    UINT32                                         :  5;  // Bits 23:19
    UINT32 CADB_TO_CPGC_BIND                       :  1;  // Bits 24:24
    UINT32 GLOBAL_START_BIND                       :  1;  // Bits 25:25
    UINT32 GLOBAL_STOP_BIND                        :  1;  // Bits 26:26
    UINT32                                         :  2;  // Bits 28:27
    UINT32 CADB_MODE                               :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CADB_CFG_STRUCT;

typedef union {
  struct {
    UINT32 START_DELAY                             :  10;  // Bits 9:0
    UINT32                                         :  6;  // Bits 15:10
    UINT32 STOP_DELAY                              :  10;  // Bits 25:16
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CADB_DLY_STRUCT;

typedef union {
  struct {
    UINT32                                         :  21;  // Bits 20:0
    UINT32 MRS_CURR_PTR                            :  3;  // Bits 23:21
    UINT32 TEST_ABORTED                            :  1;  // Bits 24:24
    UINT32                                         :  3;  // Bits 27:25
    UINT32 ALGO_DONE                               :  1;  // Bits 28:28
    UINT32 START_TEST_DELAY_BUSY                   :  1;  // Bits 29:29
    UINT32 TEST_BUSY                               :  1;  // Bits 30:30
    UINT32 TEST_DONE                               :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CADB_STATUS_STRUCT;

typedef union {
  struct {
    UINT8  UNISEQ_MODE                             :  2;  // Bits 1:0
    UINT8                                          :  1;  // Bits 2:2
    UINT8  UNISEQ_LFSR_POLYNOMIAL_SIZE             :  3;  // Bits 5:3
    UINT8                                          :  2;  // Bits 7:6
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_0_STRUCT;

typedef union {
  struct {
    UINT8  UNISEQ_MODE                             :  2;  // Bits 1:0
    UINT8                                          :  1;  // Bits 2:2
    UINT8  UNISEQ_LFSR_POLYNOMIAL_SIZE             :  3;  // Bits 5:3
    UINT8                                          :  2;  // Bits 7:6
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_1_STRUCT;

typedef union {
  struct {
    UINT8  UNISEQ_MODE                             :  2;  // Bits 1:0
    UINT8                                          :  1;  // Bits 2:2
    UINT8  UNISEQ_LFSR_POLYNOMIAL_SIZE             :  3;  // Bits 5:3
    UINT8                                          :  2;  // Bits 7:6
  } Bits;
  UINT8  Data;
} CH1_SC0_CR_CADB_DSEL_UNISEQ_CFG_2_STRUCT;

typedef union {
  struct {
    UINT32 CMD                                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_0_STRUCT;

typedef union {
  struct {
    UINT32 CMD                                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_1_STRUCT;

typedef union {
  struct {
    UINT32 CMD                                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CADB_DSEL_UNISEQ_PBUF_2_STRUCT;

typedef union {
  struct {
    UINT32 L_SEL                                   :  1;  // Bits 0:0
    UINT32                                         :  3;  // Bits 3:1
    UINT32 L_COUNTER_HI                            :  4;  // Bits 7:4
    UINT32 L_CNT                                   :  8;  // Bits 15:8
    UINT32 N_CNT                                   :  8;  // Bits 23:16
    UINT32 M_CNT                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CADB_DSEL_UNISEQ_LMN_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC0_CR_CADB_BUF_0_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC0_CR_CADB_BUF_1_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC0_CR_CADB_BUF_2_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC0_CR_CADB_BUF_3_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC0_CR_CADB_BUF_4_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC0_CR_CADB_BUF_5_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC0_CR_CADB_BUF_6_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC0_CR_CADB_BUF_7_STRUCT;

typedef union {
  struct {
    UINT32 MRS_GAP_SCALE                           :  1;  // Bits 0:0
    UINT32 MRS_GAP                                 :  4;  // Bits 4:1
    UINT32                                         :  3;  // Bits 7:5
    UINT32 MRS_AO_REPEATS                          :  16;  // Bits 23:8
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CADB_AO_MRSCFG_STRUCT;

typedef union {
  struct {
    UINT32 WR_SELECT_ENABLE                        :  3;  // Bits 2:0
    UINT32                                         :  5;  // Bits 7:3
    UINT32 RD_SELECT_ENABLE                        :  3;  // Bits 10:8
    UINT32                                         :  5;  // Bits 15:11
    UINT32 ACT_SELECT_ENABLE                       :  3;  // Bits 18:16
    UINT32                                         :  5;  // Bits 23:19
    UINT32 PRE_SELECT_ENABLE                       :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 INITIAL_SEL_SSEQ_EN                     :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC0_CR_CADB_SELCFG_STRUCT;

typedef union {
  struct {
    UINT32 CS_CLOCKS                               :  3;  // Bits 2:0
    UINT32 DSEL_CLOCKS                             :  4;  // Bits 6:3
    UINT32                                         :  1;  // Bits 7:7
    UINT32 SETUP_CLOCKS                            :  3;  // Bits 10:8
    UINT32 CS_ACTIVE_POLARITY                      :  1;  // Bits 11:11
    UINT32 MRS_START_PTR                           :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 MRS_END_PTR                             :  3;  // Bits 18:16
    UINT32 MRS_GOTO_PTR                            :  3;  // Bits 21:19
    UINT32 MRS_CS_MODE                             :  2;  // Bits 23:22
    UINT32 MRS_DELAY_CNTLow                        :  8;  // Bits 31:24
    UINT32 MRS_DELAY_CNTHigh                       :  8;  // Bits 39:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC0_CR_CADB_MRSCFG_STRUCT;

typedef union {
  struct {
    UINT32 Control_PolicyLow                       :  32;  // Bits 31:0
    UINT32 Control_PolicyHigh                      :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC1_CR_CADB_ACCESS_CONTROL_POLICY_STRUCT;

typedef union {
  struct {
    UINT32 Read_PolicyLow                          :  32;  // Bits 31:0
    UINT32 Read_PolicyHigh                         :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC1_CR_CADB_ACCESS_READ_POLICY_STRUCT;

typedef union {
  struct {
    UINT32 Write_PolicyLow                         :  32;  // Bits 31:0
    UINT32 Write_PolicyHigh                        :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC1_CR_CADB_ACCESS_WRITE_POLICY_STRUCT;

typedef union {
  struct {
    UINT32 START_TEST                              :  1;  // Bits 0:0
    UINT32 STOP_TEST                               :  1;  // Bits 1:1
    UINT32                                         :  30;  // Bits 31:2
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CADB_CTL_STRUCT;

typedef union {
  struct {
    UINT32 CMD_DESELECT_START                      :  4;  // Bits 3:0
    UINT32 CMD_DESELECT_STOP                       :  4;  // Bits 7:4
    UINT32 LANE_DESELECT_EN                        :  3;  // Bits 10:8
    UINT32 INITIAL_DSEL_EN                         :  1;  // Bits 11:11
    UINT32 INITIAL_DSEL_SSEQ_EN                    :  1;  // Bits 12:12
    UINT32 CADB_DSEL_THROTTLE_MODE                 :  3;  // Bits 15:13
    UINT32 CADB_SEL_THROTTLE_MODE                  :  3;  // Bits 18:16
    UINT32                                         :  5;  // Bits 23:19
    UINT32 CADB_TO_CPGC_BIND                       :  1;  // Bits 24:24
    UINT32 GLOBAL_START_BIND                       :  1;  // Bits 25:25
    UINT32 GLOBAL_STOP_BIND                        :  1;  // Bits 26:26
    UINT32                                         :  2;  // Bits 28:27
    UINT32 CADB_MODE                               :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CADB_CFG_STRUCT;

typedef union {
  struct {
    UINT32 START_DELAY                             :  10;  // Bits 9:0
    UINT32                                         :  6;  // Bits 15:10
    UINT32 STOP_DELAY                              :  10;  // Bits 25:16
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CADB_DLY_STRUCT;

typedef union {
  struct {
    UINT32                                         :  21;  // Bits 20:0
    UINT32 MRS_CURR_PTR                            :  3;  // Bits 23:21
    UINT32 TEST_ABORTED                            :  1;  // Bits 24:24
    UINT32                                         :  3;  // Bits 27:25
    UINT32 ALGO_DONE                               :  1;  // Bits 28:28
    UINT32 START_TEST_DELAY_BUSY                   :  1;  // Bits 29:29
    UINT32 TEST_BUSY                               :  1;  // Bits 30:30
    UINT32 TEST_DONE                               :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CADB_STATUS_STRUCT;

typedef union {
  struct {
    UINT8  UNISEQ_MODE                             :  2;  // Bits 1:0
    UINT8                                          :  1;  // Bits 2:2
    UINT8  UNISEQ_LFSR_POLYNOMIAL_SIZE             :  3;  // Bits 5:3
    UINT8                                          :  2;  // Bits 7:6
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_0_STRUCT;

typedef union {
  struct {
    UINT8  UNISEQ_MODE                             :  2;  // Bits 1:0
    UINT8                                          :  1;  // Bits 2:2
    UINT8  UNISEQ_LFSR_POLYNOMIAL_SIZE             :  3;  // Bits 5:3
    UINT8                                          :  2;  // Bits 7:6
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_1_STRUCT;

typedef union {
  struct {
    UINT8  UNISEQ_MODE                             :  2;  // Bits 1:0
    UINT8                                          :  1;  // Bits 2:2
    UINT8  UNISEQ_LFSR_POLYNOMIAL_SIZE             :  3;  // Bits 5:3
    UINT8                                          :  2;  // Bits 7:6
  } Bits;
  UINT8  Data;
} CH1_SC1_CR_CADB_DSEL_UNISEQ_CFG_2_STRUCT;

typedef union {
  struct {
    UINT32 CMD                                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_0_STRUCT;

typedef union {
  struct {
    UINT32 CMD                                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_1_STRUCT;

typedef union {
  struct {
    UINT32 CMD                                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CADB_DSEL_UNISEQ_PBUF_2_STRUCT;

typedef union {
  struct {
    UINT32 L_SEL                                   :  1;  // Bits 0:0
    UINT32                                         :  3;  // Bits 3:1
    UINT32 L_COUNTER_HI                            :  4;  // Bits 7:4
    UINT32 L_CNT                                   :  8;  // Bits 15:8
    UINT32 N_CNT                                   :  8;  // Bits 23:16
    UINT32 M_CNT                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CADB_DSEL_UNISEQ_LMN_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC1_CR_CADB_BUF_0_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC1_CR_CADB_BUF_1_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC1_CR_CADB_BUF_2_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC1_CR_CADB_BUF_3_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC1_CR_CADB_BUF_4_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC1_CR_CADB_BUF_5_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC1_CR_CADB_BUF_6_STRUCT;

typedef union {
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  10;  // Bits 41:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC1_CR_CADB_BUF_7_STRUCT;

typedef union {
  struct {
    UINT32 MRS_GAP_SCALE                           :  1;  // Bits 0:0
    UINT32 MRS_GAP                                 :  4;  // Bits 4:1
    UINT32                                         :  3;  // Bits 7:5
    UINT32 MRS_AO_REPEATS                          :  16;  // Bits 23:8
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CADB_AO_MRSCFG_STRUCT;

typedef union {
  struct {
    UINT32 WR_SELECT_ENABLE                        :  3;  // Bits 2:0
    UINT32                                         :  5;  // Bits 7:3
    UINT32 RD_SELECT_ENABLE                        :  3;  // Bits 10:8
    UINT32                                         :  5;  // Bits 15:11
    UINT32 ACT_SELECT_ENABLE                       :  3;  // Bits 18:16
    UINT32                                         :  5;  // Bits 23:19
    UINT32 PRE_SELECT_ENABLE                       :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 INITIAL_SEL_SSEQ_EN                     :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_SC1_CR_CADB_SELCFG_STRUCT;

typedef union {
  struct {
    UINT32 CS_CLOCKS                               :  3;  // Bits 2:0
    UINT32 DSEL_CLOCKS                             :  4;  // Bits 6:3
    UINT32                                         :  1;  // Bits 7:7
    UINT32 SETUP_CLOCKS                            :  3;  // Bits 10:8
    UINT32 CS_ACTIVE_POLARITY                      :  1;  // Bits 11:11
    UINT32 MRS_START_PTR                           :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 MRS_END_PTR                             :  3;  // Bits 18:16
    UINT32 MRS_GOTO_PTR                            :  3;  // Bits 21:19
    UINT32 MRS_CS_MODE                             :  2;  // Bits 23:22
    UINT32 MRS_DELAY_CNTLow                        :  8;  // Bits 31:24
    UINT32 MRS_DELAY_CNTHigh                       :  8;  // Bits 39:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_SC1_CR_CADB_MRSCFG_STRUCT;

typedef union {
  struct {
    UINT32 IBECC_EN                                :  1;  // Bits 0:0
    UINT32 RSVD                                    :  31;  // Bits 31:1
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_ACTIVATE_STRUCT;

typedef union {
  struct {
    UINT32 IBECC_REQUESTOR_ISM_STATE               :  3;  // Bits 2:0
    UINT32 MC_RESPONDER_ISM_STATE                  :  3;  // Bits 5:3
    UINT32 RPQ_FULL                                :  1;  // Bits 6:6
    UINT32 RPQ_EMPTY                               :  1;  // Bits 7:7
    UINT32 IPQ_FULL                                :  1;  // Bits 8:8
    UINT32 IPQ_EMPTY                               :  1;  // Bits 9:9
    UINT32 WPQ_FULL                                :  1;  // Bits 10:10
    UINT32 WPQ_EMPTY                               :  1;  // Bits 11:11
    UINT32 ECC_READ_TRACKER_FULL                   :  1;  // Bits 12:12
    UINT32 ECC_READ_TRACKER_EMPTY                  :  1;  // Bits 13:13
    UINT32 PROTECTED_WRITE_EXISTS                  :  1;  // Bits 14:14
    UINT32 VC0_PROTECTED_READ_EXISTS               :  1;  // Bits 15:15
    UINT32 VC1_PROTECTED_READ_EXISTS               :  1;  // Bits 16:16
    UINT32 WAR_HAZARD_EXISTS                       :  1;  // Bits 17:17
    UINT32 RAW_HAZARD_EXISTS                       :  1;  // Bits 18:18
    UINT32 WAW_HAZARD_EXISTS                       :  1;  // Bits 19:19
    UINT32 CMI_REQUESTOR_ISM_STATE                 :  3;  // Bits 22:20
    UINT32 IBECC_RESPONDER_ISM_STATE               :  3;  // Bits 25:23
    UINT32 RSVD                                    :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_STATUS_STRUCT;

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
} IBECC_IOSF_SB_EP_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 BASE                                    :  14;  // Bits 13:0
    UINT32                                         :  1;  // Bits 14:14
    UINT32 RSVD1                                   :  1;  // Bits 15:15
    UINT32 MASK                                    :  14;  // Bits 29:16
    UINT32 RSVD2                                   :  1;  // Bits 30:30
    UINT32 RANGE_EN                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_PROTECT_ADDR_RANGE_0_STRUCT;

typedef union {
  struct {
    UINT32 BASE                                    :  14;  // Bits 13:0
    UINT32                                         :  1;  // Bits 14:14
    UINT32 RSVD1                                   :  1;  // Bits 15:15
    UINT32 MASK                                    :  14;  // Bits 29:16
    UINT32 RSVD2                                   :  1;  // Bits 30:30
    UINT32 RANGE_EN                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_PROTECT_ADDR_RANGE_1_STRUCT;

typedef union {
  struct {
    UINT32 BASE                                    :  14;  // Bits 13:0
    UINT32                                         :  1;  // Bits 14:14
    UINT32 RSVD1                                   :  1;  // Bits 15:15
    UINT32 MASK                                    :  14;  // Bits 29:16
    UINT32 RSVD2                                   :  1;  // Bits 30:30
    UINT32 RANGE_EN                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_PROTECT_ADDR_RANGE_2_STRUCT;

typedef union {
  struct {
    UINT32 BASE                                    :  14;  // Bits 13:0
    UINT32                                         :  1;  // Bits 14:14
    UINT32 RSVD1                                   :  1;  // Bits 15:15
    UINT32 MASK                                    :  14;  // Bits 29:16
    UINT32 RSVD2                                   :  1;  // Bits 30:30
    UINT32 RANGE_EN                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_PROTECT_ADDR_RANGE_3_STRUCT;

typedef union {
  struct {
    UINT32 BASE                                    :  14;  // Bits 13:0
    UINT32                                         :  1;  // Bits 14:14
    UINT32 RSVD1                                   :  1;  // Bits 15:15
    UINT32 MASK                                    :  14;  // Bits 29:16
    UINT32 RSVD2                                   :  1;  // Bits 30:30
    UINT32 RANGE_EN                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_PROTECT_ADDR_RANGE_4_STRUCT;

typedef union {
  struct {
    UINT32 BASE                                    :  14;  // Bits 13:0
    UINT32                                         :  1;  // Bits 14:14
    UINT32 RSVD1                                   :  1;  // Bits 15:15
    UINT32 MASK                                    :  14;  // Bits 29:16
    UINT32 RSVD2                                   :  1;  // Bits 30:30
    UINT32 RANGE_EN                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_PROTECT_ADDR_RANGE_5_STRUCT;

typedef union {
  struct {
    UINT32 BASE                                    :  14;  // Bits 13:0
    UINT32                                         :  1;  // Bits 14:14
    UINT32 RSVD1                                   :  1;  // Bits 15:15
    UINT32 MASK                                    :  14;  // Bits 29:16
    UINT32 RSVD2                                   :  1;  // Bits 30:30
    UINT32 RANGE_EN                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_PROTECT_ADDR_RANGE_6_STRUCT;

typedef union {
  struct {
    UINT32 BASE                                    :  14;  // Bits 13:0
    UINT32                                         :  1;  // Bits 14:14
    UINT32 RSVD1                                   :  1;  // Bits 15:15
    UINT32 MASK                                    :  14;  // Bits 29:16
    UINT32 RSVD2                                   :  1;  // Bits 30:30
    UINT32 RANGE_EN                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_PROTECT_ADDR_RANGE_7_STRUCT;

typedef union {
  struct {
    UINT32 ADDRESS                                 :  15;  // Bits 14:0
    UINT32 RSVD                                    :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_ECC_STORAGE_ADDR_STRUCT;

typedef union {
  struct {
    UINT32 SAI_MASKLow                             :  32;  // Bits 31:0
    UINT32 SAI_MASKHigh                            :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IBECC_DEFAULT_PG_CP_STRUCT;

typedef union {
  struct {
    UINT32 SAI_MASKLow                             :  32;  // Bits 31:0
    UINT32 SAI_MASKHigh                            :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IBECC_DEFAULT_PG_RAC_STRUCT;

typedef union {
  struct {
    UINT32 SAI_MASKLow                             :  32;  // Bits 31:0
    UINT32 SAI_MASKHigh                            :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IBECC_DEFAULT_PG_WAC_STRUCT;

typedef union {
  struct {
    UINT32 SAI_MASKLow                             :  32;  // Bits 31:0
    UINT32 SAI_MASKHigh                            :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IBECC_DEBUG_PG_CP_STRUCT;

typedef union {
  struct {
    UINT32 SAI_MASKLow                             :  32;  // Bits 31:0
    UINT32 SAI_MASKHigh                            :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IBECC_DEBUG_PG_RAC_STRUCT;

typedef union {
  struct {
    UINT32 SAI_MASKLow                             :  32;  // Bits 31:0
    UINT32 SAI_MASKHigh                            :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IBECC_DEBUG_PG_WAC_STRUCT;

typedef union {
  struct {
    UINT32 SAI_MASKLow                             :  32;  // Bits 31:0
    UINT32 SAI_MASKHigh                            :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IBECC_OS_PG_CP_STRUCT;

typedef union {
  struct {
    UINT32 SAI_MASKLow                             :  32;  // Bits 31:0
    UINT32 SAI_MASKHigh                            :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IBECC_OS_PG_RAC_STRUCT;

typedef union {
  struct {
    UINT32 SAI_MASKLow                             :  32;  // Bits 31:0
    UINT32 SAI_MASKHigh                            :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IBECC_OS_PG_WAC_STRUCT;

typedef union {
  struct {
    UINT32 LOW_PRIORITY_LIM                        :  16;  // Bits 15:0
    UINT32 HIGH_PRIORITY_LIM                       :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_PRIO_LIM_STRUCT;

typedef union {
  struct {
    UINT32 CLK_GATE_EN                             :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_CLK_GATE_EN_0_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED0                               :  16;  // Bits 15:0
    UINT32 REQ_WR_MAX_CREDIT                       :  8;  // Bits 23:16
    UINT32 REQ_RD_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_REQ_CREDIT_CONFIG_CHANNEL_0_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED0                               :  16;  // Bits 15:0
    UINT32 REQ_WR_MAX_CREDIT                       :  8;  // Bits 23:16
    UINT32 REQ_RD_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_REQ_CREDIT_CONFIG_CHANNEL_1_STRUCT;

typedef union {
  struct {
    UINT32 REQ_WR_QUEUEDEPTH                       :  8;  // Bits 7:0
    UINT32 REQ_RD_QUEUEDEPTH                       :  8;  // Bits 15:8
    UINT32 RESERVED1                               :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_REQ_TOTAL_CREDIT_CONFIG_STRUCT;

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
} IBECC_REQUEST_PORT_STALL_STRUCT;

typedef union {
  struct {
    UINT32 PASS                                    :  1;  // Bits 0:0
    UINT32 COMPLETE                                :  1;  // Bits 1:1
    UINT32 RSVD1                                   :  6;  // Bits 7:2
    UINT32 MBIST_FAIL_INJECT                       :  1;  // Bits 8:8
    UINT32 RSVD2                                   :  22;  // Bits 30:9
    UINT32 RUN_BUSY                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_MBIST_POST_CTRL_WDB_STRUCT;

typedef union {
  struct {
    UINT32 PASS                                    :  1;  // Bits 0:0
    UINT32 COMPLETE                                :  1;  // Bits 1:1
    UINT32 RSVD1                                   :  6;  // Bits 7:2
    UINT32 MBIST_FAIL_INJECT                       :  1;  // Bits 8:8
    UINT32 RSVD2                                   :  22;  // Bits 30:9
    UINT32 RUN_BUSY                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_MBIST_POST_CTRL_RDB_STRUCT;

typedef union {
  struct {
    UINT32 RDATA_PARITY_CHK_EN                     :  1;  // Bits 0:0
    UINT32 WBE_PARITY_CHK_EN                       :  1;  // Bits 1:1
    UINT32 WDATA_PARITY_CHK_EN                     :  1;  // Bits 2:2
    UINT32 WBE_PARITY_GEN_EN                       :  1;  // Bits 3:3
    UINT32 WDATA_PARITY_GEN_EN                     :  1;  // Bits 4:4
    UINT32 ADDR_PARITY_GEN_EN                      :  1;  // Bits 5:5
    UINT32 RSVD0                                   :  2;  // Bits 7:6
    UINT32 DIS_PARITY_PCH_EVENT                    :  1;  // Bits 8:8
    UINT32 DIS_PARITY_LOG                          :  1;  // Bits 9:9
    UINT32 RSVD1                                   :  21;  // Bits 30:10
    UINT32 PARITY_EN                               :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_PARITY_CONTROL_STRUCT;

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
} IBECC_RESPOND_PORT_STALL_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED0                               :  16;  // Bits 15:0
    UINT32 RSP_MAX_CREDIT                          :  8;  // Bits 23:16
    UINT32 RD_CPL_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_0_STRUCT;

typedef union {
  struct {
    UINT32 RESERVED0                               :  16;  // Bits 15:0
    UINT32 RSP_MAX_CREDIT                          :  8;  // Bits 23:16
    UINT32 RD_CPL_MAX_CREDIT                       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_WR_RSP_RD_CPL_CREDIT_CONFIG_CHANNEL_1_STRUCT;

typedef union {
  struct {
    UINT32 RD_CPL_QUEUEDEPTH                       :  8;  // Bits 7:0
    UINT32 RSP_QUEUEDEPTH                          :  8;  // Bits 15:8
    UINT32 RESERVED1                               :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_RSP_RD_CPL_TOTAL_CREDIT_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 GRACE_CNTR_MAX                          :  8;  // Bits 7:0
    UINT32 CLKGATE_DISABLE                         :  1;  // Bits 8:8
    UINT32 RSVD                                    :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_QCLK_GLB_DRV_CLKGATE_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 REQ_CMD_SUM                             :  16;  // Bits 15:0
    UINT32 REQ_DATA_SUM                            :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_RESPOND_PORT_ACCUM_REQ_OUT_STRUCT;

typedef union {
  struct {
    UINT32 RD_CPL_CMD_SUM                          :  16;  // Bits 15:0
    UINT32 RD_CPL_DATA_SUM                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_RESPOND_PORT_ACCUM_RD_CPL_IN_STRUCT;

typedef union {
  struct {
    UINT32 RSP_CMD_SUM                             :  16;  // Bits 15:0
    UINT32 RSVD                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_RESPOND_PORT_ACCUM_RSP_IN_STRUCT;

typedef union {
  struct {
    UINT32 RSP_CMD_SUM                             :  16;  // Bits 15:0
    UINT32 RSVD                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_REQUEST_PORT_ACCUM_RSP_OUT_STRUCT;

typedef union {
  struct {
    UINT32 COUNTLow                                :  32;  // Bits 31:0
    UINT32 COUNTHigh                               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IBECC_ECC_VC0_RD_REQCOUNT_STRUCT;

typedef union {
  struct {
    UINT32 COUNTLow                                :  32;  // Bits 31:0
    UINT32 COUNTHigh                               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IBECC_ECC_VC1_RD_REQCOUNT_STRUCT;

typedef union {
  struct {
    UINT32 COUNTLow                                :  32;  // Bits 31:0
    UINT32 COUNTHigh                               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IBECC_ECC_VC0_WR_REQCOUNT_STRUCT;

typedef union {
  struct {
    UINT32 COUNTLow                                :  32;  // Bits 31:0
    UINT32 COUNTHigh                               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IBECC_ECC_VC1_WR_REQCOUNT_STRUCT;

typedef union {
  struct {
    UINT32 COUNTLow                                :  32;  // Bits 31:0
    UINT32 COUNTHigh                               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IBECC_NOECC_VC0_RD_REQCOUNT_STRUCT;

typedef union {
  struct {
    UINT32 COUNTLow                                :  32;  // Bits 31:0
    UINT32 COUNTHigh                               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IBECC_NOECC_VC1_RD_REQCOUNT_STRUCT;

typedef union {
  struct {
    UINT32 COUNTLow                                :  32;  // Bits 31:0
    UINT32 COUNTHigh                               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IBECC_NOECC_VC0_WR_REQCOUNT_STRUCT;

typedef union {
  struct {
    UINT32 COUNTLow                                :  32;  // Bits 31:0
    UINT32 COUNTHigh                               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IBECC_NOECC_VC1_WR_REQCOUNT_STRUCT;

typedef union {
  struct {
    UINT32 NON_VC1_PRIO_THRESHOLD                  :  16;  // Bits 15:0
    UINT32 VC1_RD_PRIO_THRESHOLD                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_PRIO_THRESHOLD_STRUCT;

typedef union {
  struct {
    UINT32 VC0_RD_PARK_SIZE                        :  4;  // Bits 3:0
    UINT32 VC1_RD_PARK_SIZE                        :  4;  // Bits 7:4
    UINT32 VC0_WR_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 VC1_WR_PARK_SIZE                        :  4;  // Bits 15:12
    UINT32 RSVD                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_REQUEST_ARB_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 VC0_RD_PARK_SIZE                        :  4;  // Bits 3:0
    UINT32 VC1_RD_PARK_SIZE                        :  4;  // Bits 7:4
    UINT32 VC0_WR_PARK_SIZE                        :  4;  // Bits 11:8
    UINT32 VC1_WR_PARK_SIZE                        :  4;  // Bits 15:12
    UINT32 RSVD                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_RESPONSE_ARB_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 RSVD0                                   :  5;  // Bits 4:0
    UINT32 ERRADDLow                               :  27;  // Bits 31:5
    UINT32 ERRADDHigh                              :  7;  // Bits 38:32
    UINT32 RSVD1                                   :  7;  // Bits 45:39
    UINT32 ERRSYND                                 :  16;  // Bits 61:46
    UINT32 CERRSTS                                 :  1;  // Bits 62:62
    UINT32 MERRSTS                                 :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IBECC_ECC_ERROR_LOG_STRUCT;

typedef union {
  struct {
    UINT32 RSVD1                                   :  5;  // Bits 4:0
    UINT32 ERR_ADDRESSLow                          :  27;  // Bits 31:5
    UINT32 ERR_ADDRESSHigh                         :  7;  // Bits 38:32
    UINT32 RSVD2                                   :  21;  // Bits 59:39
    UINT32 TRANS_TYPE                              :  1;  // Bits 60:60
    UINT32 ERR_TYPE                                :  2;  // Bits 62:61
    UINT32 ERR_STS                                 :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IBECC_PARITY_ERR_LOG_STRUCT;

typedef union {
  struct {
    UINT32 RSVD1                                   :  6;  // Bits 5:0
    UINT32 ADDRESSLow                              :  26;  // Bits 31:6
    UINT32 ADDRESSHigh                             :  7;  // Bits 38:32
    UINT32 RSVD2                                   :  25;  // Bits 63:39
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IBECC_ECC_INJ_ADDR_MASK_STRUCT;

typedef union {
  struct {
    UINT32 RSVD1                                   :  6;  // Bits 5:0
    UINT32 ADDRESSLow                              :  26;  // Bits 31:6
    UINT32 ADDRESSHigh                             :  7;  // Bits 38:32
    UINT32 RSVD2                                   :  25;  // Bits 63:39
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IBECC_ECC_INJ_ADDR_BASE_STRUCT;

typedef union {
  struct {
    UINT32 DATA_ERR_EN                             :  8;  // Bits 7:0
    UINT32 RSVD1                                   :  1;  // Bits 8:8
    UINT32 BE_ERR_EN                               :  2;  // Bits 10:9
    UINT32 RSVD2                                   :  5;  // Bits 15:11
    UINT32 ERR_INJ_MASK                            :  2;  // Bits 17:16
    UINT32 RSVD3                                   :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_PARITY_ERR_INJ_STRUCT;

typedef union {
  struct {
    UINT32 OPERATION_MODE                          :  2;  // Bits 1:0
    UINT32 EC_DIS                                  :  1;  // Bits 2:2
    UINT32 DIS_PCH_EVENT                           :  1;  // Bits 3:3
    UINT32 DIS_MCA_LOG                             :  1;  // Bits 4:4
    UINT32 CLKGT_DIS                               :  1;  // Bits 5:5
    UINT32 FORCE_ISM_ACTIVE                        :  1;  // Bits 6:6
    UINT32 FIXED_WINDOW                            :  1;  // Bits 7:7
    UINT32 RSVD8                                   :  1;  // Bits 8:8
    UINT32 DIS_RAW_HAZARD                          :  1;  // Bits 9:9
    UINT32 DIS_WAW_HAZARD                          :  1;  // Bits 10:10
    UINT32 DIS_WAR_HAZARD                          :  1;  // Bits 11:11
    UINT32 DIS_NOECC_WR_RSP                        :  1;  // Bits 12:12
    UINT32 DIS_ECC_PSTD_WR                         :  1;  // Bits 13:13
    UINT32 DIS_PERF_COUNTERS                       :  1;  // Bits 14:14
    UINT32 DISABLE_MULTIPLE_PCH_MSG                :  1;  // Bits 15:15
    UINT32 ISM_IDLE_TIME                           :  8;  // Bits 23:16
    UINT32 AGENT_WR_RSP                            :  1;  // Bits 24:24
    UINT32 RSB_ENABLE                              :  1;  // Bits 25:25
    UINT32 DIS_CMI_EARLY_VALID_GEN                 :  1;  // Bits 26:26
    UINT32 RSVD                                    :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 ECC_INJECT                              :  3;  // Bits 2:0
    UINT32 RSVD1                                   :  5;  // Bits 7:3
    UINT32 COUNT                                   :  8;  // Bits 15:8
    UINT32 RSVD2                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_ECC_INJ_CONTROL_STRUCT;

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
} IBECC_ACCUM_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 RD_CPL_CMD_SUM                          :  16;  // Bits 15:0
    UINT32 RD_CPL_DATA_SUM                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_REQUEST_PORT_ACCUM_RD_CPL_OUT_STRUCT;

typedef union {
  struct {
    UINT32 REQ_CMD_SUM                             :  16;  // Bits 15:0
    UINT32 REQ_DATA_SUM                            :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_REQUEST_PORT_ACCUM_REQ_IN_STRUCT;

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
} IBECC_REQ_L3_ARB_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 PASS                                    :  1;  // Bits 0:0
    UINT32 COMPLETE                                :  1;  // Bits 1:1
    UINT32 RSVD1                                   :  6;  // Bits 7:2
    UINT32 MBIST_FAIL_INJECT                       :  1;  // Bits 8:8
    UINT32 RSVD2                                   :  22;  // Bits 30:9
    UINT32 RUN_BUSY                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} IBECC_MBIST_POST_CTRL_RSB_STRUCT;

typedef union {
  struct {
    UINT32 COUNTLow                                :  32;  // Bits 31:0
    UINT32 COUNTHigh                               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IBECC_ECC_VC0_SYND_RD_REQCOUNT_STRUCT;

typedef union {
  struct {
    UINT32 COUNTLow                                :  32;  // Bits 31:0
    UINT32 COUNTHigh                               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IBECC_ECC_VC1_SYND_RD_REQCOUNT_STRUCT;

typedef union {
  struct {
    UINT32 COUNTLow                                :  32;  // Bits 31:0
    UINT32 COUNTHigh                               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IBECC_ECC_VC0_SYND_WR_REQCOUNT_STRUCT;

typedef union {
  struct {
    UINT32 COUNTLow                                :  32;  // Bits 31:0
    UINT32 COUNTHigh                               :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} IBECC_ECC_VC1_SYND_WR_REQCOUNT_STRUCT;

#pragma pack(pop)
#endif
