#ifndef __MrcMcRegisterStructTglDxxx_h__
#define __MrcMcRegisterStructTglDxxx_h__
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

typedef MC0_CR_CPGC2_ACCESS_CONTROL_POLICY_STRUCT MC0_CH0_CR_CADB_ACCESS_CONTROL_POLICY_STRUCT;

typedef MC0_CR_CPGC2_ACCESS_READ_POLICY_STRUCT MC0_CH0_CR_CADB_ACCESS_READ_POLICY_STRUCT;

typedef MC0_CR_CPGC2_ACCESS_WRITE_POLICY_STRUCT MC0_CH0_CR_CADB_ACCESS_WRITE_POLICY_STRUCT;
typedef union {
  struct {
    UINT32 START_TEST                              :  1;  // Bits 0:0
    UINT32 STOP_TEST                               :  1;  // Bits 1:1
    UINT32                                         :  30;  // Bits 31:2
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_CH0_CR_CADB_CTL_STRUCT;
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
} MC0_CH0_CR_CADB_CFG_STRUCT;
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
} MC0_CH0_CR_CADB_DLY_STRUCT;
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
} MC0_CH0_CR_CADB_STATUS_STRUCT;
typedef union {
  struct {
    UINT8  UNISEQ_MODE                             :  2;  // Bits 1:0
    UINT8                                          :  1;  // Bits 2:2
    UINT8  UNISEQ_LFSR_POLYNOMIAL_SIZE             :  3;  // Bits 5:3
    UINT8                                          :  2;  // Bits 7:6
  } Bits;
  UINT8  Data;
} MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_STRUCT;

typedef MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_STRUCT MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_1_STRUCT;

typedef MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_STRUCT MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_2_STRUCT;
typedef union {
  struct {
    UINT32 CMD                                     :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_STRUCT;

typedef MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_STRUCT MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_1_STRUCT;

typedef MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_STRUCT MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_2_STRUCT;
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
} MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_STRUCT;
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
  struct {
    UINT32 CS                                      :  4;  // Bits 3:0
    UINT32 CID                                     :  3;  // Bits 6:4
    UINT32 ODT                                     :  4;  // Bits 10:7
    UINT32 CKE                                     :  4;  // Bits 14:11
    UINT32 USE_HALF_CA                             :  1;  // Bits 15:15
    UINT32 VAL                                     :  1;  // Bits 16:16
    UINT32 PAR                                     :  1;  // Bits 17:17
    UINT32 CALow                                   :  14;  // Bits 31:18
    UINT32 CAHigh                                  :  14;  // Bits 45:32
  } P0Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MC0_CH0_CR_CADB_BUF_0_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH0_CR_CADB_BUF_1_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH0_CR_CADB_BUF_2_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH0_CR_CADB_BUF_3_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH0_CR_CADB_BUF_4_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH0_CR_CADB_BUF_5_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH0_CR_CADB_BUF_6_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH0_CR_CADB_BUF_7_STRUCT;
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
} MC0_CH0_CR_CADB_AO_MRSCFG_STRUCT;
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
} MC0_CH0_CR_CADB_SELCFG_STRUCT;
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
  struct {
    UINT32 CS_CLOCKS                               :  3;  // Bits 2:0
    UINT32 DSEL_CLOCKS                             :  4;  // Bits 6:3
    UINT32 SETUP_CLOCKS                            :  4;  // Bits 10:7
    UINT32 CS_ACTIVE_POLARITY                      :  1;  // Bits 11:11
    UINT32 MRS_START_PTR                           :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 MRS_END_PTR                             :  3;  // Bits 18:16
    UINT32 MRS_GOTO_PTR                            :  3;  // Bits 21:19
    UINT32 MRS_CS_MODE                             :  2;  // Bits 23:22
    UINT32 MRS_DELAY_CNTLow                        :  8;  // Bits 31:24
    UINT32 MRS_DELAY_CNTHigh                       :  8;  // Bits 39:32
  } P0Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MC0_CH0_CR_CADB_MRSCFG_STRUCT;

typedef MC0_CR_CPGC2_ACCESS_CONTROL_POLICY_STRUCT MC0_CH1_CR_CADB_ACCESS_CONTROL_POLICY_STRUCT;

typedef MC0_CR_CPGC2_ACCESS_READ_POLICY_STRUCT MC0_CH1_CR_CADB_ACCESS_READ_POLICY_STRUCT;

typedef MC0_CR_CPGC2_ACCESS_WRITE_POLICY_STRUCT MC0_CH1_CR_CADB_ACCESS_WRITE_POLICY_STRUCT;

typedef MC0_CH0_CR_CADB_CTL_STRUCT MC0_CH1_CR_CADB_CTL_STRUCT;

typedef MC0_CH0_CR_CADB_CFG_STRUCT MC0_CH1_CR_CADB_CFG_STRUCT;

typedef MC0_CH0_CR_CADB_DLY_STRUCT MC0_CH1_CR_CADB_DLY_STRUCT;

typedef MC0_CH0_CR_CADB_STATUS_STRUCT MC0_CH1_CR_CADB_STATUS_STRUCT;

typedef MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_STRUCT MC0_CH1_CR_CADB_DSEL_UNISEQ_CFG_0_STRUCT;

typedef MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_STRUCT MC0_CH1_CR_CADB_DSEL_UNISEQ_CFG_1_STRUCT;

typedef MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_STRUCT MC0_CH1_CR_CADB_DSEL_UNISEQ_CFG_2_STRUCT;

typedef MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_STRUCT MC0_CH1_CR_CADB_DSEL_UNISEQ_PBUF_0_STRUCT;

typedef MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_STRUCT MC0_CH1_CR_CADB_DSEL_UNISEQ_PBUF_1_STRUCT;

typedef MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_STRUCT MC0_CH1_CR_CADB_DSEL_UNISEQ_PBUF_2_STRUCT;

typedef MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_STRUCT MC0_CH1_CR_CADB_DSEL_UNISEQ_LMN_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH1_CR_CADB_BUF_0_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH1_CR_CADB_BUF_1_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH1_CR_CADB_BUF_2_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH1_CR_CADB_BUF_3_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH1_CR_CADB_BUF_4_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH1_CR_CADB_BUF_5_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH1_CR_CADB_BUF_6_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH1_CR_CADB_BUF_7_STRUCT;

typedef MC0_CH0_CR_CADB_AO_MRSCFG_STRUCT MC0_CH1_CR_CADB_AO_MRSCFG_STRUCT;

typedef MC0_CH0_CR_CADB_SELCFG_STRUCT MC0_CH1_CR_CADB_SELCFG_STRUCT;

typedef MC0_CH0_CR_CADB_MRSCFG_STRUCT MC0_CH1_CR_CADB_MRSCFG_STRUCT;

typedef MC0_CR_CPGC2_ACCESS_CONTROL_POLICY_STRUCT MC0_CH2_CR_CADB_ACCESS_CONTROL_POLICY_STRUCT;

typedef MC0_CR_CPGC2_ACCESS_READ_POLICY_STRUCT MC0_CH2_CR_CADB_ACCESS_READ_POLICY_STRUCT;

typedef MC0_CR_CPGC2_ACCESS_WRITE_POLICY_STRUCT MC0_CH2_CR_CADB_ACCESS_WRITE_POLICY_STRUCT;

typedef MC0_CH0_CR_CADB_CTL_STRUCT MC0_CH2_CR_CADB_CTL_STRUCT;

typedef MC0_CH0_CR_CADB_CFG_STRUCT MC0_CH2_CR_CADB_CFG_STRUCT;

typedef MC0_CH0_CR_CADB_DLY_STRUCT MC0_CH2_CR_CADB_DLY_STRUCT;

typedef MC0_CH0_CR_CADB_STATUS_STRUCT MC0_CH2_CR_CADB_STATUS_STRUCT;

typedef MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_STRUCT MC0_CH2_CR_CADB_DSEL_UNISEQ_CFG_0_STRUCT;

typedef MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_STRUCT MC0_CH2_CR_CADB_DSEL_UNISEQ_CFG_1_STRUCT;

typedef MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_STRUCT MC0_CH2_CR_CADB_DSEL_UNISEQ_CFG_2_STRUCT;

typedef MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_STRUCT MC0_CH2_CR_CADB_DSEL_UNISEQ_PBUF_0_STRUCT;

typedef MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_STRUCT MC0_CH2_CR_CADB_DSEL_UNISEQ_PBUF_1_STRUCT;

typedef MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_STRUCT MC0_CH2_CR_CADB_DSEL_UNISEQ_PBUF_2_STRUCT;

typedef MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_STRUCT MC0_CH2_CR_CADB_DSEL_UNISEQ_LMN_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH2_CR_CADB_BUF_0_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH2_CR_CADB_BUF_1_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH2_CR_CADB_BUF_2_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH2_CR_CADB_BUF_3_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH2_CR_CADB_BUF_4_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH2_CR_CADB_BUF_5_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH2_CR_CADB_BUF_6_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH2_CR_CADB_BUF_7_STRUCT;

typedef MC0_CH0_CR_CADB_AO_MRSCFG_STRUCT MC0_CH2_CR_CADB_AO_MRSCFG_STRUCT;

typedef MC0_CH0_CR_CADB_SELCFG_STRUCT MC0_CH2_CR_CADB_SELCFG_STRUCT;

typedef MC0_CH0_CR_CADB_MRSCFG_STRUCT MC0_CH2_CR_CADB_MRSCFG_STRUCT;

typedef MC0_CR_CPGC2_ACCESS_CONTROL_POLICY_STRUCT MC0_CH3_CR_CADB_ACCESS_CONTROL_POLICY_STRUCT;

typedef MC0_CR_CPGC2_ACCESS_READ_POLICY_STRUCT MC0_CH3_CR_CADB_ACCESS_READ_POLICY_STRUCT;

typedef MC0_CR_CPGC2_ACCESS_WRITE_POLICY_STRUCT MC0_CH3_CR_CADB_ACCESS_WRITE_POLICY_STRUCT;

typedef MC0_CH0_CR_CADB_CTL_STRUCT MC0_CH3_CR_CADB_CTL_STRUCT;

typedef MC0_CH0_CR_CADB_CFG_STRUCT MC0_CH3_CR_CADB_CFG_STRUCT;

typedef MC0_CH0_CR_CADB_DLY_STRUCT MC0_CH3_CR_CADB_DLY_STRUCT;

typedef MC0_CH0_CR_CADB_STATUS_STRUCT MC0_CH3_CR_CADB_STATUS_STRUCT;

typedef MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_STRUCT MC0_CH3_CR_CADB_DSEL_UNISEQ_CFG_0_STRUCT;

typedef MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_STRUCT MC0_CH3_CR_CADB_DSEL_UNISEQ_CFG_1_STRUCT;

typedef MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_STRUCT MC0_CH3_CR_CADB_DSEL_UNISEQ_CFG_2_STRUCT;

typedef MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_STRUCT MC0_CH3_CR_CADB_DSEL_UNISEQ_PBUF_0_STRUCT;

typedef MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_STRUCT MC0_CH3_CR_CADB_DSEL_UNISEQ_PBUF_1_STRUCT;

typedef MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_STRUCT MC0_CH3_CR_CADB_DSEL_UNISEQ_PBUF_2_STRUCT;

typedef MC0_CH0_CR_CADB_DSEL_UNISEQ_LMN_STRUCT MC0_CH3_CR_CADB_DSEL_UNISEQ_LMN_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH3_CR_CADB_BUF_0_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH3_CR_CADB_BUF_1_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH3_CR_CADB_BUF_2_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH3_CR_CADB_BUF_3_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH3_CR_CADB_BUF_4_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH3_CR_CADB_BUF_5_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH3_CR_CADB_BUF_6_STRUCT;

typedef MC0_CH0_CR_CADB_BUF_0_STRUCT MC0_CH3_CR_CADB_BUF_7_STRUCT;

typedef MC0_CH0_CR_CADB_AO_MRSCFG_STRUCT MC0_CH3_CR_CADB_AO_MRSCFG_STRUCT;

typedef MC0_CH0_CR_CADB_SELCFG_STRUCT MC0_CH3_CR_CADB_SELCFG_STRUCT;

typedef MC0_CH0_CR_CADB_MRSCFG_STRUCT MC0_CH3_CR_CADB_MRSCFG_STRUCT;
typedef union {
  struct {
    UINT32 DDR_TYPE                                :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 CH_L_MAP                                :  1;  // Bits 4:4
    UINT32                                         :  7;  // Bits 11:5
    UINT32 CH_S_SIZE                               :  8;  // Bits 19:12
    UINT32                                         :  7;  // Bits 26:20
    UINT32 CH_WIDTH                                :  2;  // Bits 28:27
    UINT32                                         :  2;  // Bits 30:29
    UINT32 HalfCacheLineMode                       :  1;  // Bits 31:31
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_MAD_INTER_CHANNEL_P0_STRUCT;
typedef union {
  struct {
    UINT32 DIMM_L_MAP                              :  1;  // Bits 0:0
    UINT32                                         :  7;  // Bits 7:1
    UINT32 EIM                                     :  1;  // Bits 8:8
    UINT32                                         :  3;  // Bits 11:9
    UINT32 ECC                                     :  2;  // Bits 13:12
    UINT32 CRC                                     :  1;  // Bits 14:14
    UINT32                                         :  17;  // Bits 31:15
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_MAD_INTRA_CH0_P0_STRUCT;

typedef MC0_MAD_INTRA_CH0_P0_STRUCT MC0_MAD_INTRA_CH1_P0_STRUCT;
typedef union {
  struct {
    UINT32 DIMM_L_SIZE                             :  7;  // Bits 6:0
    UINT32 DLW                                     :  2;  // Bits 8:7
    UINT32 DLNOR                                   :  2;  // Bits 10:9
    UINT32                                         :  5;  // Bits 15:11
    UINT32 DIMM_S_SIZE                             :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 DSW                                     :  2;  // Bits 25:24
    UINT32 DSNOR                                   :  2;  // Bits 27:26
    UINT32                                         :  1;  // Bits 28:28
    UINT32 DLS_BG0_on_bit_11                       :  1;  // Bits 29:29
    UINT32 ddr5_device_8Gb                         :  1;  // Bits 30:30
    UINT32                                         :  1;  // Bits 31:31
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_MAD_DIMM_CH0_P0_STRUCT;

typedef MC0_MAD_DIMM_CH0_P0_STRUCT MC0_MAD_DIMM_CH1_P0_STRUCT;
typedef union {
  struct {
    UINT32 Spare_RW                                :  12;  // Bits 11:0
    UINT32 VISAByteSel                             :  4;  // Bits 15:12
    UINT32 spare_RW_V                              :  16;  // Bits 31:16
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_MCDECS_MISC_P0_STRUCT;
typedef union {
  struct {
    UINT32 increase_rcomp                          :  1;  // Bits 0:0
    UINT32 rank2_to_rank1                          :  1;  // Bits 1:1
    UINT32 ovrd_pcu_sr_exit                        :  1;  // Bits 2:2
    UINT32 psmi_freeze_pwm_counters                :  1;  // Bits 3:3
    UINT32 dis_single_ch_sr                        :  1;  // Bits 4:4
    UINT32 dis_other_ch_stolen_ref                 :  1;  // Bits 5:5
    UINT32 ForceSREntry_dft                        :  1;  // Bits 6:6
    UINT32 reserved                                :  2;  // Bits 8:7
    UINT32 ForceSREntry_dft_is_sticky              :  1;  // Bits 9:9
    UINT32                                         :  1;  // Bits 10:10
    UINT32 iosfsb_keep_ISM_active                  :  1;  // Bits 11:11
    UINT32 ignoreRefBetweenSRX2SRE                 :  1;  // Bits 12:12
    UINT32                                         :  1;  // Bits 13:13
    UINT32 dis_cmi_spec_req_early_valid            :  1;  // Bits 14:14
    UINT32 Dis_EFLOW_fwd_data_hack                 :  1;  // Bits 15:15
    UINT32 freeze_visa_values                      :  1;  // Bits 16:16
    UINT32 freeze_visa_values_on_RTB               :  1;  // Bits 17:17
    UINT32 dis_cmi_ep_power_flows                  :  1;  // Bits 18:18
    UINT32 dis_iosf_sb_error_opcodes               :  1;  // Bits 19:19
    UINT32 dis_iosf_sb_error_bar                   :  1;  // Bits 20:20
    UINT32 dis_iosf_sb_error_range                 :  1;  // Bits 21:21
    UINT32 dis_iosf_sb_error_sai                   :  1;  // Bits 22:22
    UINT32 delay_normal_mode_when_temp_read        :  1;  // Bits 23:23
    UINT32 dis_cmi_spec_rsp_cpl_early_valid        :  1;  // Bits 24:24
    UINT32 force_sb_ep_clk_req                     :  1;  // Bits 25:25
    UINT32 dis_cmi_wr_rsp                          :  1;  // Bits 26:26
    UINT32 dis_iosf_sb_clk_gate                    :  1;  // Bits 27:27
    UINT32 dis_glbdrv_clk_gate                     :  1;  // Bits 28:28
    UINT32 dis_reg_clk_gate                        :  1;  // Bits 29:29
    UINT32                                         :  1;  // Bits 30:30
    UINT32 dis_clk_gate                            :  1;  // Bits 31:31
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_MCDECS_CBIT_P0_STRUCT;
typedef union {
  struct {
    UINT32                                         :  6;  // Bits 5:0
    UINT32 HASH_MASK                               :  14;  // Bits 19:6
    UINT32                                         :  4;  // Bits 23:20
    UINT32 HASH_LSB_MASK_BIT                       :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 HASH_MODE                               :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_CHANNEL_HASH_P0_STRUCT;
typedef union {
  struct {
    UINT32                                         :  6;  // Bits 5:0
    UINT32 EHASH_MASK                              :  14;  // Bits 19:6
    UINT32                                         :  4;  // Bits 23:20
    UINT32 EHASH_LSB_MASK_BIT                      :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 EHASH_MODE                              :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_CHANNEL_EHASH_P0_STRUCT;
typedef union {
  struct {
    UINT32                                         :  1;  // Bits 0:0
    UINT32 ddr_reset                               :  1;  // Bits 1:1
    UINT32                                         :  1;  // Bits 2:2
    UINT32 refresh_enable                          :  1;  // Bits 3:3
    UINT32                                         :  1;  // Bits 4:4
    UINT32 mc_init_done_ack                        :  1;  // Bits 5:5
    UINT32                                         :  1;  // Bits 6:6
    UINT32 mrc_done                                :  1;  // Bits 7:7
    UINT32                                         :  1;  // Bits 8:8
    UINT32 pure_srx                                :  1;  // Bits 9:9
    UINT32                                         :  1;  // Bits 10:10
    UINT32 mrc_save_gv_point_0                     :  1;  // Bits 11:11
    UINT32 mrc_save_gv_point_1                     :  1;  // Bits 12:12
    UINT32 mrc_save_gv_point_2                     :  1;  // Bits 13:13
    UINT32 mrc_save_gv_point_3                     :  1;  // Bits 14:14
    UINT32                                         :  7;  // Bits 21:15
    UINT32 dclk_enable                             :  1;  // Bits 22:22
    UINT32                                         :  1;  // Bits 23:23
    UINT32 override_sr_enable                      :  1;  // Bits 24:24
    UINT32 override_sr_enable_value                :  1;  // Bits 25:25
    UINT32                                         :  6;  // Bits 31:26
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_MC_INIT_STATE_G_P0_STRUCT;
typedef union {
  struct {
    UINT32 REVISION                                :  32;  // Bits 31:0
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_MRC_REVISION_P0_STRUCT;
typedef union {
  struct {
    UINT32 CMI_Source_ID0                          :  5;  // Bits 4:0
    UINT32 CMI_Source_ID1                          :  5;  // Bits 9:5
    UINT32 CMI_Source_ID2                          :  5;  // Bits 14:10
    UINT32 CMI_Source_ID3                          :  5;  // Bits 19:15
    UINT32                                         :  12;  // Bits 31:20
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_P0_STRUCT;
typedef union {
  struct {
    UINT32 countLow                                :  32;  // Bits 31:0
    UINT32 countHigh                               :  32;  // Bits 63:32
  } P0Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MC0_PWM_TOTAL_REQCOUNT_P0_STRUCT;

typedef MC0_PWM_TOTAL_REQCOUNT_P0_STRUCT MC0_PWM_PROGRAMMABLE_REQCOUNT_0_P0_STRUCT;
typedef MC0_PWM_TOTAL_REQCOUNT_P0_STRUCT MC0_PWM_PROGRAMMABLE_REQCOUNT_1_P0_STRUCT;
typedef MC0_PWM_TOTAL_REQCOUNT_P0_STRUCT MC0_PWM_RDCAS_COUNT_P0_STRUCT;
typedef union {
  struct {
    UINT32 Idle_timer                              :  16;  // Bits 15:0
    UINT32 SR_Enable                               :  1;  // Bits 16:16
    UINT32 delay_qsync                             :  2;  // Bits 18:17
    UINT32                                         :  13;  // Bits 31:19
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_PM_SREF_CONFIG_P0_STRUCT;
typedef union {
  struct {
    UINT32 VC1_WR_CNFLT                            :  1;  // Bits 0:0
    UINT32 VC1_RD_CNFLT                            :  1;  // Bits 1:1
    UINT32                                         :  30;  // Bits 31:2
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_ATMC_STS_P0_STRUCT;

typedef MC0_PWM_TOTAL_REQCOUNT_P0_STRUCT MC0_READ_OCCUPANCY_COUNT_P0_STRUCT;
typedef union {
  struct {
    UINT32 stall_until_drain                       :  1;  // Bits 0:0
    UINT32 stall_input                             :  1;  // Bits 1:1
    UINT32                                         :  2;  // Bits 3:2
    UINT32 mc_drained                              :  1;  // Bits 4:4
    UINT32                                         :  3;  // Bits 7:5
    UINT32 sr_state                                :  1;  // Bits 8:8
    UINT32                                         :  3;  // Bits 11:9
    UINT32 stall_state                             :  1;  // Bits 12:12
    UINT32                                         :  19;  // Bits 31:13
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_STALL_DRAIN_P0_STRUCT;
typedef union {
  struct {
    UINT32 NonVC1Threshold                         :  4;  // Bits 3:0
    UINT32 VC1RdThreshold                          :  4;  // Bits 7:4
    UINT32 FixedRateEn                             :  1;  // Bits 8:8
    UINT32 HIGH_PRIO_LIM                           :  3;  // Bits 11:9
    UINT32 LOW_PRIO_LIM                            :  3;  // Bits 14:12
    UINT32 spare                                   :  8;  // Bits 22:15
    UINT32                                         :  9;  // Bits 31:23
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_IPC_MC_ARB_P0_STRUCT;

typedef MC0_IPC_MC_ARB_P0_STRUCT MC0_IPC_MC_DEC_ARB_P0_STRUCT;
typedef union {
  struct {
    UINT32 RPQ_count                               :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 WPQ_count                               :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 IPQ_count                               :  5;  // Bits 20:16
    UINT32 WPQ_MinSlotsToReq                       :  4;  // Bits 24:21
    UINT32 IPQ_MinSlotsToReq                       :  3;  // Bits 27:25
    UINT32 RPQ_MinSlotsToReq                       :  4;  // Bits 31:28
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_QUEUE_CREDIT_C_P0_STRUCT;
typedef union {
  struct {
    UINT32 AddressLow                              :  32;  // Bits 31:0
    UINT32 AddressHigh                             :  1;  // Bits 32:32
  } P0Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MC0_ECC_INJ_ADDR_COMPARE_P0_STRUCT;
typedef union {
  struct {
    UINT32                                         :  20;  // Bits 19:0
    UINT32 REMAPBASELow                            :  12;  // Bits 31:20
    UINT32 REMAPBASEHigh                           :  7;  // Bits 38:32
  } P0Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MC0_REMAPBASE_P0_STRUCT;
typedef union {
  struct {
    UINT32                                         :  20;  // Bits 19:0
    UINT32 REMAPLMTLow                             :  12;  // Bits 31:20
    UINT32 REMAPLMTHigh                            :  7;  // Bits 38:32
  } P0Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MC0_REMAPLIMIT_P0_STRUCT;

typedef MC0_PWM_TOTAL_REQCOUNT_P0_STRUCT MC0_PWM_WRCAS_COUNT_P0_STRUCT;
typedef MC0_PWM_TOTAL_REQCOUNT_P0_STRUCT MC0_PWM_COMMAND_COUNT_P0_STRUCT;
typedef MC0_PWM_TOTAL_REQCOUNT_P0_STRUCT MC0_PWM_NON_SR_COUNT_P0_STRUCT;
typedef union {
  struct {
    UINT32                                         :  20;  // Bits 19:0
    UINT32 TOLUD                                   :  12;  // Bits 31:20
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_TOLUD_P0_STRUCT;
typedef union {
  struct {
    UINT32 sys_addrLow                             :  32;  // Bits 31:0
    UINT32 sys_addrHigh                            :  1;  // Bits 32:32
  } P0Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_P0_STRUCT;

typedef MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_P0_STRUCT MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_1_P0_STRUCT;
typedef MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_P0_STRUCT MC0_GDXC_DDR_SYS_ADD_FILTER_MATCH_0_P0_STRUCT;
typedef MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_P0_STRUCT MC0_GDXC_DDR_SYS_ADD_FILTER_MATCH_1_P0_STRUCT;
typedef MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_P0_STRUCT MC0_GDXC_DDR_SYS_ADD_TRIGGER_MASK_P0_STRUCT;
typedef MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_P0_STRUCT MC0_GDXC_DDR_SYS_ADD_TRIGGER_MATCH_P0_STRUCT;
typedef union {
  struct {
    UINT32 Isoch_time_window                       :  17;  // Bits 16:0
    UINT32 Write_starvation_window                 :  11;  // Bits 27:17
    UINT32 VC1_Read_starvation_en                  :  1;  // Bits 28:28
    UINT32 Write_starvation_in_Isoc_en             :  1;  // Bits 29:29
    UINT32 Read_starvation_in_Isoch_en             :  1;  // Bits 30:30
    UINT32 VC0_counter_disable                     :  1;  // Bits 31:31
    UINT32 Read_starvation_window                  :  11;  // Bits 42:32
    UINT32 VC0_read_count                          :  9;  // Bits 51:43
    UINT32 Force_MCVC1Demote                       :  1;  // Bits 52:52
    UINT32 Disable_MCVC1Demote                     :  1;  // Bits 53:53
    UINT32 MC_Ignore_VC1Demote                     :  1;  // Bits 54:54
    UINT32 Ignore_RGBSync                          :  1;  // Bits 55:55
    UINT32 Force_MC_WPriority                      :  1;  // Bits 56:56
    UINT32 Disable_MC_WPriority                    :  1;  // Bits 57:57
    UINT32 allow_cross_vc_blocking                 :  1;  // Bits 58:58
    UINT32 VC1_block_VC0                           :  1;  // Bits 59:59
    UINT32 VC0_block_VC1                           :  1;  // Bits 60:60
    UINT32 Delay_VC1_on_read_starvation            :  1;  // Bits 61:61
  } P0Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MC0_SC_QOS_P0_STRUCT;
typedef union {
  struct {
    UINT32 GLB_GRACE_CNT                           :  8;  // Bits 7:0
    UINT32 GLB_DRV_GATE_DIS                        :  1;  // Bits 8:8
    UINT32                                         :  23;  // Bits 31:9
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_MCMAINS_GLOBAL_DRIVER_GATE_CFG_P0_STRUCT;
typedef union {
  struct {
    UINT32 CountLow                                :  32;  // Bits 31:0
    UINT32 CountHigh                               :  32;  // Bits 63:32
  } P0Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MC0_PWM_COUNTERS_DURATION_P0_STRUCT;
typedef union {
  struct {
    UINT32 cmi_req_stall_enable                    :  1;  // Bits 0:0
    UINT32 cmi_req_stall_phase                     :  1;  // Bits 1:1
    UINT32 block_scheduler                         :  4;  // Bits 5:2
    UINT32 pwm_clock_enable                        :  1;  // Bits 6:6
    UINT32 Mock_InSR                               :  1;  // Bits 7:7
    UINT32 dis_other_mc_stolen_ref                 :  1;  // Bits 8:8
    UINT32 allow_blockack_on_pending_srx           :  1;  // Bits 9:9
    UINT32 two_cyc_early_ca_valid_dis              :  1;  // Bits 10:10
    UINT32 two_cyc_early_ckstop_dis                :  1;  // Bits 11:11
    UINT32 dis_spid_cmd_clk_gate                   :  1;  // Bits 12:12
    UINT32                                         :  3;  // Bits 15:13
    UINT32 init_complete_override                  :  4;  // Bits 19:16
    UINT32                                         :  12;  // Bits 31:20
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_MCDECS_SECOND_CBIT_P0_STRUCT;
typedef union {
  struct {
    UINT32 AddressLow                              :  32;  // Bits 31:0
    UINT32 AddressHigh                             :  1;  // Bits 32:32
  } P0Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MC0_ECC_INJ_ADDR_MASK_P0_STRUCT;
typedef union {
  struct {
    UINT32 RW_Isoch_time_window                    :  17;  // Bits 16:0
    UINT32 RW_Write_starvation_window              :  11;  // Bits 27:17
    UINT32                                         :  4;  // Bits 31:28
    UINT32 RW_Read_starvation_window               :  11;  // Bits 42:32
    UINT32 Isoc_during_demote_period_x8            :  8;  // Bits 50:43
    UINT32 Isoc_during_demote_window               :  8;  // Bits 58:51
  } P0Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MC0_SC_QOS2_P0_STRUCT;
typedef union {
  struct {
    UINT32 Yellow_Decay_x128                       :  9;  // Bits 8:0
    UINT32 Yellow_Threshold                        :  10;  // Bits 18:9
    UINT32                                         :  13;  // Bits 31:19
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_SC_QOS3_P0_STRUCT;
typedef union {
  struct {
    UINT32 normalmode                              :  1;  // Bits 0:0
    UINT32                                         :  31;  // Bits 31:1
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_NORMALMODE_CFG_P0_STRUCT;
typedef union {
  struct {
    UINT32                                         :  24;  // Bits 23:0
    UINT32 CPGC_ACTIVE                             :  1;  // Bits 24:24
    UINT32                                         :  3;  // Bits 27:25
    UINT32 CPGC_ECC_BYTE                           :  3;  // Bits 30:28
    UINT32 Stall_CPGC_CMI_Req                      :  1;  // Bits 31:31
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_MC_CPGC_CMI_P0_STRUCT;
typedef union {
  struct {
    UINT32 Concat_Row2Col                          :  1;  // Bits 0:0
    UINT32 Col_align                               :  3;  // Bits 3:1
    UINT32 Concat_Bank2Row                         :  1;  // Bits 4:4
    UINT32 Concat_Col2Row                          :  1;  // Bits 5:5
    UINT32 Row_align                               :  3;  // Bits 8:6
    UINT32 Concat_BG2Bank                          :  1;  // Bits 9:9
    UINT32 dis_BankGroup                           :  1;  // Bits 10:10
    UINT32 Rank_as_it                              :  1;  // Bits 11:11
    UINT32 channel_is_CID_Zero                     :  1;  // Bits 12:12
    UINT32 Inverse_channel                         :  1;  // Bits 13:13
    UINT32 Delay_cpl_info                          :  1;  // Bits 14:14
    UINT32 Delay_cpl_data                          :  1;  // Bits 15:15
    UINT32 Reset_CPGC                              :  1;  // Bits 16:16
    UINT32 Lock_On_Active_CPGC_CMI_ISM             :  1;  // Bits 17:17
    UINT32 BG1_mask                                :  1;  // Bits 18:18
    UINT32 Rank1_as_ERM_BG1                        :  1;  // Bits 19:19
    UINT32                                         :  12;  // Bits 31:20
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_MC_CPGC_MISC_DFT_P0_STRUCT;

typedef MC0_PWM_TOTAL_REQCOUNT_P0_STRUCT MC0_PWM_GLB_DRV_OFF_COUNT_P0_STRUCT;
typedef union {
  struct {
    UINT32 ERR_ADDRESSLow                          :  32;  // Bits 31:0
    UINT32 ERR_ADDRESSHigh                         :  7;  // Bits 38:32
    UINT32 RESERVED                                :  21;  // Bits 59:39
    UINT32 ERR_SRC                                 :  1;  // Bits 60:60
    UINT32 ERR_TYPE                                :  2;  // Bits 62:61
    UINT32 ERR_STS                                 :  1;  // Bits 63:63
  } P0Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MC0_PARITYERRLOG_P0_STRUCT;
typedef union {
  struct {
    UINT32 DATA_ERR_EN                             :  8;  // Bits 7:0
    UINT32 ADDR_ERR_EN                             :  1;  // Bits 8:8
    UINT32 BE_ERR_EN                               :  2;  // Bits 10:9
    UINT32 RSVD                                    :  5;  // Bits 15:11
    UINT32 ERR_INJ_MASK                            :  5;  // Bits 20:16
    UINT32 RSVD2                                   :  10;  // Bits 30:21
    UINT32 DATA_ERR_INJ_SRC                        :  1;  // Bits 31:31
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_PARITY_ERR_INJ_P0_STRUCT;
typedef union {
  struct {
    UINT32 ADDR_PARITY_EN                          :  1;  // Bits 0:0
    UINT32 WBE_PARITY_EN                           :  1;  // Bits 1:1
    UINT32 WDATA_PARITY_EN                         :  2;  // Bits 3:2
    UINT32 RDATA_PARITY_EN                         :  1;  // Bits 4:4
    UINT32 RSVD_0                                  :  3;  // Bits 7:5
    UINT32 DIS_PARITY_PCH_EVENT                    :  1;  // Bits 8:8
    UINT32 DIS_PARITY_LOG                          :  1;  // Bits 9:9
    UINT32 RSVD_1                                  :  21;  // Bits 30:10
    UINT32 PARITY_EN                               :  1;  // Bits 31:31
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_PARITY_CONTROL_P0_STRUCT;
typedef union {
  struct {
    UINT32 reset_low_timer                         :  13;  // Bits 12:0
    UINT32 cke_low_timer                           :  13;  // Bits 25:13
    UINT32 pre_cmd_timer                           :  6;  // Bits 31:26
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_MC_JEDEC_INIT_TIMING_P0_STRUCT;
typedef union {
  struct {
    UINT32                                         :  4;  // Bits 3:0
    UINT32 MCHTrace                                :  1;  // Bits 4:4
    UINT32 SCHTrace                                :  1;  // Bits 5:5
    UINT32 ECC_EN                                  :  1;  // Bits 6:6
    UINT32 ECC_BYTE_replace                        :  3;  // Bits 9:7
    UINT32 RSVD_16_10                              :  7;  // Bits 16:10
    UINT32 Enable_ACC_Trace                        :  1;  // Bits 17:17
    UINT32 Enable_ReadData_Trace                   :  1;  // Bits 18:18
    UINT32 Enable_WriteData_Trace                  :  1;  // Bits 19:19
    UINT32 DDRPL_Activate                          :  1;  // Bits 20:20
    UINT32 DDRPL_GLB_DRV_GATE_DIS                  :  1;  // Bits 21:21
    UINT32 RSVD_23_22                              :  2;  // Bits 23:22
    UINT32 DTF_ENC_CB                              :  1;  // Bits 24:24
    UINT32                                         :  1;  // Bits 25:25
    UINT32 ddr4_bypass_trace_read                  :  1;  // Bits 26:26
    UINT32 ddr4_bypass_trace_write                 :  1;  // Bits 27:27
    UINT32 Trace_2LM_Tag                           :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_DDRPL_CFG_DTF_P0_STRUCT;
typedef union {
  struct {
    UINT32 Enable_ACC_Window_Filtering             :  1;  // Bits 0:0
    UINT32 Filter_Window_Depth                     :  8;  // Bits 8:1
    UINT32                                         :  23;  // Bits 31:9
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_DDRPL_FILTER_DTF_P0_STRUCT;
typedef union {
  struct {
    UINT32                                         :  16;  // Bits 15:0
    UINT32 Read_Data_UserDefined_Bits              :  8;  // Bits 23:16
    UINT32 Write_Data_UserDefined_Bits             :  8;  // Bits 31:24
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_DDRPL_DEBUG_DTF_P0_STRUCT;
typedef union {
  struct {
    UINT32 Visa_Qclk_Lane_1_out                    :  8;  // Bits 7:0
    UINT32 Visa_Qclk_Lane_0_out                    :  8;  // Bits 15:8
    UINT32 Visa_Dclk_Lane_1_out                    :  8;  // Bits 23:16
    UINT32 Visa_Dclk_Lane_0_out                    :  8;  // Bits 31:24
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_DDRPL_VISA_LANES_P0_STRUCT;
typedef union {
  struct {
    UINT32 VisaLane0_Data_Stage_Dclk_tree          :  2;  // Bits 1:0
    UINT32 VisaLane1_Data_Stage_Dclk_tree          :  2;  // Bits 3:2
    UINT32 VisaLane0_Data_Stage_Qclk_tree          :  2;  // Bits 5:4
    UINT32 VisaLane1_Data_Stage_Qclk_tree          :  2;  // Bits 7:6
    UINT32                                         :  24;  // Bits 31:8
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_DDRPL_VISA_CFG_DTF_P0_STRUCT;

#pragma pack(pop)
#endif
