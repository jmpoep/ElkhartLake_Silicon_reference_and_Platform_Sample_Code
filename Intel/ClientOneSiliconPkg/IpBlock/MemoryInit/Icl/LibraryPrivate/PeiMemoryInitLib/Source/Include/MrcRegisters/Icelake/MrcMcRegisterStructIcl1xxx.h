#ifndef __MrcMcRegisterStructIcl1xxx_h__
#define __MrcMcRegisterStructIcl1xxx_h__
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
    UINT32 ReplicaTrain_GVp0                       :  6;  // Bits 5:0
    UINT32 ReplicaTrain_GVp1                       :  6;  // Bits 11:6
    UINT32 ReplicaTrain_GVp2                       :  6;  // Bits 17:12
    UINT32 ReplicaTrain_GVp3                       :  6;  // Bits 23:18
    UINT32 ReplicaOffsetPrev                       :  7;  // Bits 30:24
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH0_CR_DCCDATATRAINREPLICA0_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH0_CR_DCCDATATRAINVAL0RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH0_CR_DCCDATATRAINVAL0RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH0_CR_DCCDATATRAINVAL0RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH0_CR_DCCDATATRAINVAL0RANK3_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 ReplicaShadowDccVal                     :  6;  // Bits 29:24
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH0_CR_DCCDATATRAINVAL1RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 spare2                                  :  2;  // Bits 25:24
    UINT32 binfsmsteptosavecnts                    :  3;  // Bits 28:26
    UINT32 savecntsatchosenbinstep                 :  1;  // Bits 29:29
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH0_CR_DCCDATATRAINVAL1RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 Spare                                   :  6;  // Bits 29:24
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH0_CR_DCCDATATRAINVAL1RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 Spare                                   :  6;  // Bits 29:24
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH0_CR_DCCDATATRAINVAL1RANK3_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_0                        :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_4                        :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_8                        :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_12                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_16                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH0_CR_DCCDATADCCPILUT0_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_20                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_24                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_28                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_32                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_36                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH0_CR_DCCDATADCCPILUT1_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_40                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_44                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_48                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_52                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_56                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH0_CR_DCCDATADCCPILUT2_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_60                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_64                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_68                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_72                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_76                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH0_CR_DCCDATADCCPILUT3_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_80                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_84                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_88                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_92                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_96                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH0_CR_DCCDATADCCPILUT4_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_100                      :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_104                      :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_108                      :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_112                      :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_116                      :  6;  // Bits 29:24
    UINT32 DccPiAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH0_CR_DCCDATADCCPILUT5_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_120                      :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_124                      :  6;  // Bits 11:6
    UINT32 DccPiStaticCode                         :  6;  // Bits 17:12
    UINT32 DccPiStaticCodeGear1                    :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH0_CR_DCCDATADCCPILUT6_STRUCT;

typedef union {
  struct {
    UINT32 DqTcoCompBit0                           :  6;  // Bits 5:0
    UINT32 DqTcoCompBit1                           :  6;  // Bits 11:6
    UINT32 DqTcoCompBit2                           :  6;  // Bits 17:12
    UINT32 DqTcoCompBit3                           :  6;  // Bits 23:18
    UINT32 DqsNTcoComp                             :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH0_CR_DDRCRDATATCOCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 DqTcoCompBit4                           :  6;  // Bits 5:0
    UINT32 DqTcoCompBit5                           :  6;  // Bits 11:6
    UINT32 DqTcoCompBit6                           :  6;  // Bits 17:12
    UINT32 DqTcoCompBit7                           :  6;  // Bits 23:18
    UINT32 DqsPTcoComp                             :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH0_CR_DDRCRDATATCOCONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit6Rank0                       :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit6Rank1                       :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit7Rank0                       :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit7Rank1                       :  6;  // Bits 23:18
    UINT32 DfeDlyModeRank0                         :  2;  // Bits 25:24
    UINT32 DfeDlyModeRank1                         :  2;  // Bits 27:26
    UINT32 DfeDlyModeRank2                         :  2;  // Bits 29:28
    UINT32 DfeDlyModeRank3                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH0_CR_DDRCRDATADFECONTROL1RANK01_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit6Rank2                       :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit6Rank3                       :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit7Rank2                       :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit7Rank3                       :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH0_CR_DDRCRDATADFECONTROL1RANK23_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH0_CR_DDRCRDATADFECONTROL0RANK0_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH0_CR_DDRCRDATADFECONTROL0RANK1_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH0_CR_DDRCRDATADFECONTROL0RANK2_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH0_CR_DDRCRDATADFECONTROL0RANK3_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_RXCONTROL0RANK0_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_RXCONTROL0RANK1_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_RXCONTROL0RANK2_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_RXCONTROL0RANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_RXCONTROL1RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_RXCONTROL1RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_RXCONTROL1RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_RXCONTROL1RANK3_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 TxRankMuxDelay                          :  4;  // Bits 29:26
    UINT32 Spare1                                  :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_TXTRAINRANK0_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 TxRankMuxDelay_2nd_stage_offset         :  2;  // Bits 27:26
    UINT32 Spare1                                  :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_TXTRAINRANK1_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 Spare1                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_TXTRAINRANK2_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 Spare1                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_TXTRAINRANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_TXPERBITLOWRANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_TXPERBITLOWRANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_TXPERBITLOWRANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_TXPERBITLOWRANK3_STRUCT;

typedef union {
  struct {
    UINT32 RcompDrvUp                              :  6;  // Bits 5:0
    UINT32 Rsvd                                    :  8;  // Bits 13:6
    UINT32 RcompDrvDown                            :  6;  // Bits 19:14
    UINT32 SlewRateComp                            :  5;  // Bits 24:20
    UINT32 Spare                                   :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_RCOMPDATA0_STRUCT;

typedef union {
  struct {
    UINT32 RcompOdtUp                              :  6;  // Bits 5:0
    UINT32 spare                                   :  20;  // Bits 25:6
    UINT32 RcompOdtDown                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_RCOMPDATA1_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeCoeffRank0                         :  2;  // Bits 1:0
    UINT32 DqDfeCoeffRank1                         :  2;  // Bits 3:2
    UINT32 DqDfeCoeffRank2                         :  2;  // Bits 5:4
    UINT32 DqDfeCoeffRank3                         :  2;  // Bits 7:6
    UINT32 en_rcvenpre_zero_fill                   :  1;  // Bits 8:8
    UINT32 spare                                   :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DDRCRDATACONTROL8_STRUCT;

typedef union {
  struct {
    UINT32 PanicVttUp                              :  8;  // Bits 7:0
    UINT32 PanicVttDn                              :  8;  // Bits 15:8
    UINT32 RcompCmdDn200ohm                        :  6;  // Bits 21:16
    UINT32 Spare                                   :  10;  // Bits 31:22
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_RCOMPDATA2_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_RXCONTROL2RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_RXCONTROL2RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_RXCONTROL2RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_RXCONTROL2RANK3_STRUCT;

typedef union {
  struct {
    UINT32 DataTrainFeedback                       :  9;  // Bits 8:0
    UINT32 Spare                                   :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DATATRAINFEEDBACK_STRUCT;

typedef union {
  struct {
    INT32  DqDrvUpCompOffset                       :  6;  // Bits 5:0
    INT32  DqDrvDownCompOffset                     :  6;  // Bits 11:6
    INT32  DqOdtUpCompOffset                       :  5;  // Bits 16:12
    INT32  DqOdtDownCompOffset                     :  5;  // Bits 21:17
    UINT32 Spare                                   :  5;  // Bits 26:22
    INT32  DqSlewRateCompOffset                    :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DDRCRDATAOFFSETCOMP_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 DllWeakLock                             :  1;  // Bits 6:6
    UINT32 SdllSegmentDisable                      :  3;  // Bits 9:7
    UINT32 RxBiasCtl                               :  4;  // Bits 13:10
    INT32  OdtDelay                                :  5;  // Bits 18:14
    UINT32 OdtDuration                             :  3;  // Bits 21:19
    INT32  SenseAmpDelay                           :  5;  // Bits 26:22
    UINT32 SenseAmpDuration                        :  3;  // Bits 29:27
    UINT32 CBEnAmp2                                :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DDRCRDATACONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 RxStaggerCtl                            :  5;  // Bits 4:0
    UINT32 ForceBiasOn                             :  1;  // Bits 5:5
    UINT32 ForceRxOn                               :  1;  // Bits 6:6
    UINT32 DisableDqsOdtStatic                     :  1;  // Bits 7:7
    UINT32 LpDdrLongOdtEn                          :  1;  // Bits 8:8
    UINT32 RxRankMuxDelay                          :  4;  // Bits 12:9
    UINT32 RxClkStgNum                             :  5;  // Bits 17:13
    UINT32 WlLongDelEn                             :  1;  // Bits 18:18
    UINT32 EnableVrefPwrDn                         :  1;  // Bits 19:19
    UINT32 Ddr4Mode                                :  1;  // Bits 20:20
    UINT32 EnVddqOdt                               :  1;  // Bits 21:21
    UINT32 EnVttOdt                                :  1;  // Bits 22:22
    UINT32 EnConstZEqTx                            :  1;  // Bits 23:23
    UINT32 TxEqDis                                 :  1;  // Bits 24:24
    UINT32 RxVrefProgMFC                           :  1;  // Bits 25:25
    UINT32 Cben                                    :  3;  // Bits 28:26
    UINT32 TxDeskewDisable                         :  1;  // Bits 29:29
    UINT32 RxDeskewDisable                         :  1;  // Bits 30:30
    UINT32 DqSlewDlyByPass                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DDRCRDATACONTROL2_STRUCT;

typedef union {
  struct {
    INT32  RcvEnOffset                             :  6;  // Bits 5:0
    INT32  RxDqsOffset                             :  7;  // Bits 12:6
    INT32  TxDqOffset                              :  6;  // Bits 18:13
    INT32  TxDqsOffset                             :  6;  // Bits 24:19
    INT32  VrefOffset                              :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DDRCRDATAOFFSETTRAIN_STRUCT;

typedef union {
  struct {
    UINT32 RxTrainingMode                          :  1;  // Bits 0:0
    UINT32 WLTrainingMode                          :  1;  // Bits 1:1
    UINT32 RLTrainingMode                          :  1;  // Bits 2:2
    UINT32 SenseampTrainingMode                    :  1;  // Bits 3:3
    UINT32 TxOn                                    :  1;  // Bits 4:4
    UINT32 LPDDR_Mode                              :  1;  // Bits 5:5
    UINT32 RxPiOn                                  :  1;  // Bits 6:6
    UINT32 TxPiOn                                  :  1;  // Bits 7:7
    UINT32 InternalClocksOn                        :  1;  // Bits 8:8
    UINT32 RepeaterClocksOn                        :  1;  // Bits 9:9
    UINT32 TxDisable                               :  1;  // Bits 10:10
    UINT32 RxDisable                               :  1;  // Bits 11:11
    UINT32 Spare2                                  :  1;  // Bits 12:12
    UINT32 RxDqsCtle                               :  2;  // Bits 14:13
    UINT32 RxReadPointer                           :  4;  // Bits 18:15
    UINT32 xover_mindelay_ctl                      :  2;  // Bits 20:19
    UINT32 DQDQSLowsupEn                           :  1;  // Bits 21:21
    UINT32 DqTcoBypass                             :  1;  // Bits 22:22
    UINT32 viewQclkDis                             :  1;  // Bits 23:23
    UINT32 ForceOdtOn                              :  1;  // Bits 24:24
    UINT32 OdtSampOff                              :  1;  // Bits 25:25
    UINT32 DisableOdtStatic                        :  1;  // Bits 26:26
    UINT32 DdrCRForceODTOn                         :  1;  // Bits 27:27
    UINT32 spare                                   :  1;  // Bits 28:28
    UINT32 LongOdtR2W                              :  1;  // Bits 29:29
    UINT32 OdtSampExtendEn                         :  1;  // Bits 30:30
    UINT32 EarlyRleakEn                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DDRCRDATACONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 TxDqsRankMuxDelay                       :  4;  // Bits 3:0
    UINT32 TxDqsRankMuxDelay_2nd_stage_offset      :  2;  // Bits 5:4
    UINT32 ForceDqsOnQuickOdtOff                   :  1;  // Bits 6:6
    UINT32 Strong2WeakOnDqsOdt                     :  1;  // Bits 7:7
    INT32  DqsOdtDelay                             :  6;  // Bits 13:8
    UINT32 vrefinten_atckepwrdown                  :  1;  // Bits 14:14
    UINT32 DqsOdtSampExtendEn                      :  1;  // Bits 15:15
    UINT32 DqsOdtDuration                          :  3;  // Bits 18:16
    UINT32 AllowOvrdOdtOnAsyncDrv                  :  1;  // Bits 19:19
    UINT32 LeakerComp                              :  3;  // Bits 22:20
    UINT32 rxclkstgnummsb                          :  1;  // Bits 23:23
    UINT32 NomPgDis                                :  1;  // Bits 24:24
    UINT32 rcven_four_cycle_fill                   :  1;  // Bits 25:25
    UINT32 StrongWkLeaker                          :  4;  // Bits 29:26
    UINT32 CBEnAmp1                                :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DDRCRDATACONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 leakerwithtxanalogen                    :  1;  // Bits 0:0
    UINT32 glbdrv_clkgate_enable                   :  1;  // Bits 1:1
    UINT32 biasrcomp                               :  3;  // Bits 4:2
    UINT32 txdeskewcal                             :  1;  // Bits 5:5
    UINT32 txdeskewdqscodesel                      :  1;  // Bits 6:6
    UINT32 rxdeskewcal                             :  1;  // Bits 7:7
    UINT32 rxdeskewdqscodesel                      :  1;  // Bits 8:8
    UINT32 DisPanicDrv                             :  2;  // Bits 10:9
    UINT32 dllnbiassel                             :  1;  // Bits 11:11
    UINT32 rxsel                                   :  1;  // Bits 12:12
    UINT32 ampoffseten                             :  1;  // Bits 13:13
    UINT32 LpDdr4Mode                              :  1;  // Bits 14:14
    UINT32 lpddr4wrlongpreambleen                  :  1;  // Bits 15:15
    UINT32 ddr4wrlongpreambleen                    :  1;  // Bits 16:16
    UINT32 VssODTSingleSegEn                       :  1;  // Bits 17:17
    UINT32 VssODTEn                                :  1;  // Bits 18:18
    UINT32 dqsodtdowncompoffset                    :  5;  // Bits 23:19
    UINT32 dqsodtupcompoffset                      :  5;  // Bits 28:24
    UINT32 spare2                                  :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DDRCRDATACONTROL4_STRUCT;

typedef union {
  struct {
    UINT32 RxVref                                  :  8;  // Bits 7:0
    UINT32 ddrcrdqsmaskcnten                       :  1;  // Bits 8:8
    UINT32 ddrcrnumofpulses                        :  2;  // Bits 10:9
    UINT32 ddrcrmaskcntpulsenumstart               :  4;  // Bits 14:11
    UINT32 Lp4xVoltageSelect                       :  1;  // Bits 15:15
    UINT32 DdrDqOvrdModeEn                         :  8;  // Bits 23:16
    UINT32 DdrDqOvrdData                           :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DDRCRDATACONTROL5_STRUCT;

typedef union {
  struct {
    UINT32 RankOvrd                                :  1;  // Bits 0:0
    UINT32 RankValue                               :  2;  // Bits 2:1
    UINT32 Gear1                                   :  1;  // Bits 3:3
    UINT32 RxDqsAmpOffset                          :  5;  // Bits 8:4
    UINT32 fast_dqsoutputenable                    :  1;  // Bits 9:9
    UINT32 tx_clock_on_with_txanalogen             :  1;  // Bits 10:10
    UINT32 local_gate_d0tx                         :  1;  // Bits 11:11
    UINT32 strongwkleakermsb                       :  2;  // Bits 13:12
    UINT32 forcedqsponwithleaker                   :  1;  // Bits 14:14
    UINT32 forcedqsnonwithleaker                   :  1;  // Bits 15:15
    UINT32 RxBiasCtl1                              :  8;  // Bits 23:16
    UINT32 ForceDqsPon                             :  1;  // Bits 24:24
    UINT32 ForceDqsNon                             :  1;  // Bits 25:25
    UINT32 sdll_picb                               :  3;  // Bits 28:26
    UINT32 d0_picb                                 :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DDRCRDATACONTROL6_STRUCT;

typedef union {
  struct {
    UINT32 DqsDfeDlyRank0                          :  6;  // Bits 5:0
    UINT32 DqsDfeDlyRank1                          :  6;  // Bits 11:6
    UINT32 DqsDfeDlyRank2                          :  6;  // Bits 17:12
    UINT32 DqsDfeDlyRank3                          :  6;  // Bits 23:18
    UINT32 sdll_bw_ctrl                            :  4;  // Bits 27:24
    UINT32 d0_bw_ctrl                              :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DDRCRDATACONTROL7_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DELTADQSRANK0_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DELTADQSRANK1_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DELTADQSRANK2_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DELTADQSRANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_RXCONTROL3RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_RXCONTROL3RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_RXCONTROL3RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_RXCONTROL3RANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_TXPERBITHIRANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_TXPERBITHIRANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_TXPERBITHIRANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_TXPERBITHIRANK3_STRUCT;

typedef union {
  struct {
    UINT32 GVPointG1                               :  1;  // Bits 0:0
    UINT32 GVPointG2                               :  2;  // Bits 2:1
    UINT32 ReplicaOffsetUse                        :  1;  // Bits 3:3
    UINT32 VTCompOffsetUse                         :  2;  // Bits 5:4
    UINT32 ExtOffset                               :  7;  // Bits 12:6
    UINT32 BiasOffset                              :  15;  // Bits 27:13
    UINT32 ActiveRanks                             :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATACONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 DccCodeOvrd                             :  6;  // Bits 5:0
    UINT32 RepDccAipCb                             :  2;  // Bits 7:6
    UINT32 DccPtrOvrd                              :  4;  // Bits 11:8
    UINT32 RnkPtrOvrd                              :  2;  // Bits 13:12
    UINT32 DcdDigEnOvrd                            :  1;  // Bits 14:14
    UINT32 DcdAnaEnOvrd                            :  1;  // Bits 15:15
    UINT32 DcdWindow                               :  15;  // Bits 30:16
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATACONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 StartBinCode                            :  6;  // Bits 5:0
    UINT32 CodePtrStartBit                         :  3;  // Bits 8:6
    UINT32 DccTrshOld                              :  13;  // Bits 21:9
    UINT32 DcdCntsStartDiff                        :  5;  // Bits 26:22
    UINT32 ClkGateDisable                          :  1;  // Bits 27:27
    UINT32 DccDataViewSelect0                      :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATACONTROL2_STRUCT;

typedef union {
  struct {
    UINT32 ActiveDccRank0                          :  11;  // Bits 10:0
    UINT32 ActiveDccRank1                          :  9;  // Bits 19:11
    UINT32 ActiveDccRank2                          :  9;  // Bits 28:20
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATACONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 ActiveDccRank3                          :  9;  // Bits 8:0
    UINT32 Spare                                   :  1;  // Bits 9:9
    UINT32 ReplicaPrev_GVp0                        :  6;  // Bits 15:10
    UINT32 ReplicaPrev_GVp1                        :  6;  // Bits 21:16
    UINT32 ReplicaPrev_GVp2                        :  6;  // Bits 27:22
    UINT32 DccDataViewSelect1                      :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATACONTROL4_STRUCT;

typedef union {
  struct {
    UINT32 Spare                                   :  2;  // Bits 1:0
    UINT32 vtcompoffsetmsgwren                     :  1;  // Bits 2:2
    UINT32 ReplicaPrev_GVp3                        :  6;  // Bits 8:3
    UINT32 BubbleCntVal                            :  5;  // Bits 13:9
    UINT32 DeterministicSyncVal                    :  6;  // Bits 19:14
    UINT32 DeterministicCntVal                     :  11;  // Bits 30:20
    UINT32 DeterministicMode                       :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATACONTROL5_STRUCT;

typedef union {
  struct {
    UINT32 Rank0DccDone                            :  11;  // Bits 10:0
    UINT32 Rank1DccDone                            :  9;  // Bits 19:11
    UINT32 Rank2DccDone                            :  9;  // Bits 28:20
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATATRAINSTATUS0_STRUCT;

typedef union {
  struct {
    UINT32 Rank3DccDone                            :  9;  // Bits 8:0
    UINT32 Spare0                                  :  1;  // Bits 9:9
    UINT32 CntDone                                 :  1;  // Bits 10:10
    UINT32 Dcd_O_Cnt                               :  15;  // Bits 25:11
    UINT32 Spare1                                  :  1;  // Bits 26:26
    UINT32 BinFsmCurrState                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATATRAINSTATUS1_STRUCT;

typedef union {
  struct {
    UINT32 AuxCnt                                  :  16;  // Bits 15:0
    UINT32 ReplicaOffset                           :  7;  // Bits 22:16
    UINT32 VTCompOffset                            :  7;  // Bits 29:23
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATATRAINSTATUS2_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  11;  // Bits 10:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 27:11
    UINT32 Spare                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATATRAINERRSTATUSRANK0_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  9;  // Bits 8:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 25:9
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATATRAINERRSTATUSRANK1_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  9;  // Bits 8:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 25:9
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATATRAINERRSTATUSRANK2_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  9;  // Bits 8:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 25:9
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATATRAINERRSTATUSRANK3_STRUCT;

typedef union {
  struct {
    UINT32 ReplicaTrain_GVp0                       :  6;  // Bits 5:0
    UINT32 ReplicaTrain_GVp1                       :  6;  // Bits 11:6
    UINT32 ReplicaTrain_GVp2                       :  6;  // Bits 17:12
    UINT32 ReplicaTrain_GVp3                       :  6;  // Bits 23:18
    UINT32 ReplicaOffsetPrev                       :  7;  // Bits 30:24
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATATRAINREPLICA0_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATATRAINVAL0RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATATRAINVAL0RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATATRAINVAL0RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATATRAINVAL0RANK3_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 ReplicaShadowDccVal                     :  6;  // Bits 29:24
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATATRAINVAL1RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 spare2                                  :  2;  // Bits 25:24
    UINT32 binfsmsteptosavecnts                    :  3;  // Bits 28:26
    UINT32 savecntsatchosenbinstep                 :  1;  // Bits 29:29
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATATRAINVAL1RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 Spare                                   :  6;  // Bits 29:24
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATATRAINVAL1RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 Spare                                   :  6;  // Bits 29:24
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATATRAINVAL1RANK3_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_0                        :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_4                        :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_8                        :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_12                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_16                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATADCCPILUT0_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_20                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_24                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_28                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_32                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_36                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATADCCPILUT1_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_40                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_44                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_48                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_52                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_56                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATADCCPILUT2_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_60                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_64                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_68                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_72                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_76                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATADCCPILUT3_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_80                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_84                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_88                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_92                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_96                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATADCCPILUT4_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_100                      :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_104                      :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_108                      :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_112                      :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_116                      :  6;  // Bits 29:24
    UINT32 DccPiAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATADCCPILUT5_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_120                      :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_124                      :  6;  // Bits 11:6
    UINT32 DccPiStaticCode                         :  6;  // Bits 17:12
    UINT32 DccPiStaticCodeGear1                    :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DCCDATADCCPILUT6_STRUCT;

typedef union {
  struct {
    UINT32 DqTcoCompBit0                           :  6;  // Bits 5:0
    UINT32 DqTcoCompBit1                           :  6;  // Bits 11:6
    UINT32 DqTcoCompBit2                           :  6;  // Bits 17:12
    UINT32 DqTcoCompBit3                           :  6;  // Bits 23:18
    UINT32 DqsNTcoComp                             :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DDRCRDATATCOCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 DqTcoCompBit4                           :  6;  // Bits 5:0
    UINT32 DqTcoCompBit5                           :  6;  // Bits 11:6
    UINT32 DqTcoCompBit6                           :  6;  // Bits 17:12
    UINT32 DqTcoCompBit7                           :  6;  // Bits 23:18
    UINT32 DqsPTcoComp                             :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DDRCRDATATCOCONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit6Rank0                       :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit6Rank1                       :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit7Rank0                       :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit7Rank1                       :  6;  // Bits 23:18
    UINT32 DfeDlyModeRank0                         :  2;  // Bits 25:24
    UINT32 DfeDlyModeRank1                         :  2;  // Bits 27:26
    UINT32 DfeDlyModeRank2                         :  2;  // Bits 29:28
    UINT32 DfeDlyModeRank3                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DDRCRDATADFECONTROL1RANK01_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit6Rank2                       :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit6Rank3                       :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit7Rank2                       :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit7Rank3                       :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DDRCRDATADFECONTROL1RANK23_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DDRCRDATADFECONTROL0RANK0_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DDRCRDATADFECONTROL0RANK1_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DDRCRDATADFECONTROL0RANK2_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5CH1_CR_DDRCRDATADFECONTROL0RANK3_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_RXCONTROL0RANK0_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_RXCONTROL0RANK1_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_RXCONTROL0RANK2_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_RXCONTROL0RANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_RXCONTROL1RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_RXCONTROL1RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_RXCONTROL1RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_RXCONTROL1RANK3_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 TxRankMuxDelay                          :  4;  // Bits 29:26
    UINT32 Spare1                                  :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_TXTRAINRANK0_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 TxRankMuxDelay_2nd_stage_offset         :  2;  // Bits 27:26
    UINT32 Spare1                                  :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_TXTRAINRANK1_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 Spare1                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_TXTRAINRANK2_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 Spare1                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_TXTRAINRANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_TXPERBITLOWRANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_TXPERBITLOWRANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_TXPERBITLOWRANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_TXPERBITLOWRANK3_STRUCT;

typedef union {
  struct {
    UINT32 RcompDrvUp                              :  6;  // Bits 5:0
    UINT32 Rsvd                                    :  8;  // Bits 13:6
    UINT32 RcompDrvDown                            :  6;  // Bits 19:14
    UINT32 SlewRateComp                            :  5;  // Bits 24:20
    UINT32 Spare                                   :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_RCOMPDATA0_STRUCT;

typedef union {
  struct {
    UINT32 RcompOdtUp                              :  6;  // Bits 5:0
    UINT32 spare                                   :  20;  // Bits 25:6
    UINT32 RcompOdtDown                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_RCOMPDATA1_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeCoeffRank0                         :  2;  // Bits 1:0
    UINT32 DqDfeCoeffRank1                         :  2;  // Bits 3:2
    UINT32 DqDfeCoeffRank2                         :  2;  // Bits 5:4
    UINT32 DqDfeCoeffRank3                         :  2;  // Bits 7:6
    UINT32 en_rcvenpre_zero_fill                   :  1;  // Bits 8:8
    UINT32 spare                                   :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DDRCRDATACONTROL8_STRUCT;

typedef union {
  struct {
    UINT32 PanicVttUp                              :  8;  // Bits 7:0
    UINT32 PanicVttDn                              :  8;  // Bits 15:8
    UINT32 RcompCmdDn200ohm                        :  6;  // Bits 21:16
    UINT32 Spare                                   :  10;  // Bits 31:22
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_RCOMPDATA2_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_RXCONTROL2RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_RXCONTROL2RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_RXCONTROL2RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_RXCONTROL2RANK3_STRUCT;

typedef union {
  struct {
    UINT32 DataTrainFeedback                       :  9;  // Bits 8:0
    UINT32 Spare                                   :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DATATRAINFEEDBACK_STRUCT;

typedef union {
  struct {
    INT32  DqDrvUpCompOffset                       :  6;  // Bits 5:0
    INT32  DqDrvDownCompOffset                     :  6;  // Bits 11:6
    INT32  DqOdtUpCompOffset                       :  5;  // Bits 16:12
    INT32  DqOdtDownCompOffset                     :  5;  // Bits 21:17
    UINT32 Spare                                   :  5;  // Bits 26:22
    INT32  DqSlewRateCompOffset                    :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 DllWeakLock                             :  1;  // Bits 6:6
    UINT32 SdllSegmentDisable                      :  3;  // Bits 9:7
    UINT32 RxBiasCtl                               :  4;  // Bits 13:10
    INT32  OdtDelay                                :  5;  // Bits 18:14
    UINT32 OdtDuration                             :  3;  // Bits 21:19
    INT32  SenseAmpDelay                           :  5;  // Bits 26:22
    UINT32 SenseAmpDuration                        :  3;  // Bits 29:27
    UINT32 CBEnAmp2                                :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DDRCRDATACONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 RxStaggerCtl                            :  5;  // Bits 4:0
    UINT32 ForceBiasOn                             :  1;  // Bits 5:5
    UINT32 ForceRxOn                               :  1;  // Bits 6:6
    UINT32 DisableDqsOdtStatic                     :  1;  // Bits 7:7
    UINT32 LpDdrLongOdtEn                          :  1;  // Bits 8:8
    UINT32 RxRankMuxDelay                          :  4;  // Bits 12:9
    UINT32 RxClkStgNum                             :  5;  // Bits 17:13
    UINT32 WlLongDelEn                             :  1;  // Bits 18:18
    UINT32 EnableVrefPwrDn                         :  1;  // Bits 19:19
    UINT32 Ddr4Mode                                :  1;  // Bits 20:20
    UINT32 EnVddqOdt                               :  1;  // Bits 21:21
    UINT32 EnVttOdt                                :  1;  // Bits 22:22
    UINT32 EnConstZEqTx                            :  1;  // Bits 23:23
    UINT32 TxEqDis                                 :  1;  // Bits 24:24
    UINT32 RxVrefProgMFC                           :  1;  // Bits 25:25
    UINT32 Cben                                    :  3;  // Bits 28:26
    UINT32 TxDeskewDisable                         :  1;  // Bits 29:29
    UINT32 RxDeskewDisable                         :  1;  // Bits 30:30
    UINT32 DqSlewDlyByPass                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DDRCRDATACONTROL2_STRUCT;

typedef union {
  struct {
    INT32  RcvEnOffset                             :  6;  // Bits 5:0
    INT32  RxDqsOffset                             :  7;  // Bits 12:6
    INT32  TxDqOffset                              :  6;  // Bits 18:13
    INT32  TxDqsOffset                             :  6;  // Bits 24:19
    INT32  VrefOffset                              :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DDRCRDATAOFFSETTRAIN_STRUCT;

typedef union {
  struct {
    UINT32 RxTrainingMode                          :  1;  // Bits 0:0
    UINT32 WLTrainingMode                          :  1;  // Bits 1:1
    UINT32 RLTrainingMode                          :  1;  // Bits 2:2
    UINT32 SenseampTrainingMode                    :  1;  // Bits 3:3
    UINT32 TxOn                                    :  1;  // Bits 4:4
    UINT32 LPDDR_Mode                              :  1;  // Bits 5:5
    UINT32 RxPiOn                                  :  1;  // Bits 6:6
    UINT32 TxPiOn                                  :  1;  // Bits 7:7
    UINT32 InternalClocksOn                        :  1;  // Bits 8:8
    UINT32 RepeaterClocksOn                        :  1;  // Bits 9:9
    UINT32 TxDisable                               :  1;  // Bits 10:10
    UINT32 RxDisable                               :  1;  // Bits 11:11
    UINT32 Spare2                                  :  1;  // Bits 12:12
    UINT32 RxDqsCtle                               :  2;  // Bits 14:13
    UINT32 RxReadPointer                           :  4;  // Bits 18:15
    UINT32 xover_mindelay_ctl                      :  2;  // Bits 20:19
    UINT32 DQDQSLowsupEn                           :  1;  // Bits 21:21
    UINT32 DqTcoBypass                             :  1;  // Bits 22:22
    UINT32 viewQclkDis                             :  1;  // Bits 23:23
    UINT32 ForceOdtOn                              :  1;  // Bits 24:24
    UINT32 OdtSampOff                              :  1;  // Bits 25:25
    UINT32 DisableOdtStatic                        :  1;  // Bits 26:26
    UINT32 DdrCRForceODTOn                         :  1;  // Bits 27:27
    UINT32 spare                                   :  1;  // Bits 28:28
    UINT32 LongOdtR2W                              :  1;  // Bits 29:29
    UINT32 OdtSampExtendEn                         :  1;  // Bits 30:30
    UINT32 EarlyRleakEn                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DDRCRDATACONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 TxDqsRankMuxDelay                       :  4;  // Bits 3:0
    UINT32 TxDqsRankMuxDelay_2nd_stage_offset      :  2;  // Bits 5:4
    UINT32 ForceDqsOnQuickOdtOff                   :  1;  // Bits 6:6
    UINT32 Strong2WeakOnDqsOdt                     :  1;  // Bits 7:7
    INT32  DqsOdtDelay                             :  6;  // Bits 13:8
    UINT32 vrefinten_atckepwrdown                  :  1;  // Bits 14:14
    UINT32 DqsOdtSampExtendEn                      :  1;  // Bits 15:15
    UINT32 DqsOdtDuration                          :  3;  // Bits 18:16
    UINT32 AllowOvrdOdtOnAsyncDrv                  :  1;  // Bits 19:19
    UINT32 LeakerComp                              :  3;  // Bits 22:20
    UINT32 rxclkstgnummsb                          :  1;  // Bits 23:23
    UINT32 NomPgDis                                :  1;  // Bits 24:24
    UINT32 rcven_four_cycle_fill                   :  1;  // Bits 25:25
    UINT32 StrongWkLeaker                          :  4;  // Bits 29:26
    UINT32 CBEnAmp1                                :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DDRCRDATACONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 leakerwithtxanalogen                    :  1;  // Bits 0:0
    UINT32 glbdrv_clkgate_enable                   :  1;  // Bits 1:1
    UINT32 biasrcomp                               :  3;  // Bits 4:2
    UINT32 txdeskewcal                             :  1;  // Bits 5:5
    UINT32 txdeskewdqscodesel                      :  1;  // Bits 6:6
    UINT32 rxdeskewcal                             :  1;  // Bits 7:7
    UINT32 rxdeskewdqscodesel                      :  1;  // Bits 8:8
    UINT32 DisPanicDrv                             :  2;  // Bits 10:9
    UINT32 dllnbiassel                             :  1;  // Bits 11:11
    UINT32 rxsel                                   :  1;  // Bits 12:12
    UINT32 ampoffseten                             :  1;  // Bits 13:13
    UINT32 LpDdr4Mode                              :  1;  // Bits 14:14
    UINT32 lpddr4wrlongpreambleen                  :  1;  // Bits 15:15
    UINT32 ddr4wrlongpreambleen                    :  1;  // Bits 16:16
    UINT32 VssODTSingleSegEn                       :  1;  // Bits 17:17
    UINT32 VssODTEn                                :  1;  // Bits 18:18
    UINT32 dqsodtdowncompoffset                    :  5;  // Bits 23:19
    UINT32 dqsodtupcompoffset                      :  5;  // Bits 28:24
    UINT32 spare2                                  :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DDRCRDATACONTROL4_STRUCT;

typedef union {
  struct {
    UINT32 RxVref                                  :  8;  // Bits 7:0
    UINT32 ddrcrdqsmaskcnten                       :  1;  // Bits 8:8
    UINT32 ddrcrnumofpulses                        :  2;  // Bits 10:9
    UINT32 ddrcrmaskcntpulsenumstart               :  4;  // Bits 14:11
    UINT32 Lp4xVoltageSelect                       :  1;  // Bits 15:15
    UINT32 DdrDqOvrdModeEn                         :  8;  // Bits 23:16
    UINT32 DdrDqOvrdData                           :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DDRCRDATACONTROL5_STRUCT;

typedef union {
  struct {
    UINT32 RankOvrd                                :  1;  // Bits 0:0
    UINT32 RankValue                               :  2;  // Bits 2:1
    UINT32 Gear1                                   :  1;  // Bits 3:3
    UINT32 RxDqsAmpOffset                          :  5;  // Bits 8:4
    UINT32 fast_dqsoutputenable                    :  1;  // Bits 9:9
    UINT32 tx_clock_on_with_txanalogen             :  1;  // Bits 10:10
    UINT32 local_gate_d0tx                         :  1;  // Bits 11:11
    UINT32 strongwkleakermsb                       :  2;  // Bits 13:12
    UINT32 forcedqsponwithleaker                   :  1;  // Bits 14:14
    UINT32 forcedqsnonwithleaker                   :  1;  // Bits 15:15
    UINT32 RxBiasCtl1                              :  8;  // Bits 23:16
    UINT32 ForceDqsPon                             :  1;  // Bits 24:24
    UINT32 ForceDqsNon                             :  1;  // Bits 25:25
    UINT32 sdll_picb                               :  3;  // Bits 28:26
    UINT32 d0_picb                                 :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DDRCRDATACONTROL6_STRUCT;

typedef union {
  struct {
    UINT32 DqsDfeDlyRank0                          :  6;  // Bits 5:0
    UINT32 DqsDfeDlyRank1                          :  6;  // Bits 11:6
    UINT32 DqsDfeDlyRank2                          :  6;  // Bits 17:12
    UINT32 DqsDfeDlyRank3                          :  6;  // Bits 23:18
    UINT32 sdll_bw_ctrl                            :  4;  // Bits 27:24
    UINT32 d0_bw_ctrl                              :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DDRCRDATACONTROL7_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DELTADQSRANK0_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DELTADQSRANK1_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DELTADQSRANK2_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DELTADQSRANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_RXCONTROL3RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_RXCONTROL3RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_RXCONTROL3RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_RXCONTROL3RANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_TXPERBITHIRANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_TXPERBITHIRANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_TXPERBITHIRANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_TXPERBITHIRANK3_STRUCT;

typedef union {
  struct {
    UINT32 GVPointG1                               :  1;  // Bits 0:0
    UINT32 GVPointG2                               :  2;  // Bits 2:1
    UINT32 ReplicaOffsetUse                        :  1;  // Bits 3:3
    UINT32 VTCompOffsetUse                         :  2;  // Bits 5:4
    UINT32 ExtOffset                               :  7;  // Bits 12:6
    UINT32 BiasOffset                              :  15;  // Bits 27:13
    UINT32 ActiveRanks                             :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATACONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 DccCodeOvrd                             :  6;  // Bits 5:0
    UINT32 RepDccAipCb                             :  2;  // Bits 7:6
    UINT32 DccPtrOvrd                              :  4;  // Bits 11:8
    UINT32 RnkPtrOvrd                              :  2;  // Bits 13:12
    UINT32 DcdDigEnOvrd                            :  1;  // Bits 14:14
    UINT32 DcdAnaEnOvrd                            :  1;  // Bits 15:15
    UINT32 DcdWindow                               :  15;  // Bits 30:16
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATACONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 StartBinCode                            :  6;  // Bits 5:0
    UINT32 CodePtrStartBit                         :  3;  // Bits 8:6
    UINT32 DccTrshOld                              :  13;  // Bits 21:9
    UINT32 DcdCntsStartDiff                        :  5;  // Bits 26:22
    UINT32 ClkGateDisable                          :  1;  // Bits 27:27
    UINT32 DccDataViewSelect0                      :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATACONTROL2_STRUCT;

typedef union {
  struct {
    UINT32 ActiveDccRank0                          :  11;  // Bits 10:0
    UINT32 ActiveDccRank1                          :  9;  // Bits 19:11
    UINT32 ActiveDccRank2                          :  9;  // Bits 28:20
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATACONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 ActiveDccRank3                          :  9;  // Bits 8:0
    UINT32 Spare                                   :  1;  // Bits 9:9
    UINT32 ReplicaPrev_GVp0                        :  6;  // Bits 15:10
    UINT32 ReplicaPrev_GVp1                        :  6;  // Bits 21:16
    UINT32 ReplicaPrev_GVp2                        :  6;  // Bits 27:22
    UINT32 DccDataViewSelect1                      :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATACONTROL4_STRUCT;

typedef union {
  struct {
    UINT32 Spare                                   :  2;  // Bits 1:0
    UINT32 vtcompoffsetmsgwren                     :  1;  // Bits 2:2
    UINT32 ReplicaPrev_GVp3                        :  6;  // Bits 8:3
    UINT32 BubbleCntVal                            :  5;  // Bits 13:9
    UINT32 DeterministicSyncVal                    :  6;  // Bits 19:14
    UINT32 DeterministicCntVal                     :  11;  // Bits 30:20
    UINT32 DeterministicMode                       :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATACONTROL5_STRUCT;

typedef union {
  struct {
    UINT32 Rank0DccDone                            :  11;  // Bits 10:0
    UINT32 Rank1DccDone                            :  9;  // Bits 19:11
    UINT32 Rank2DccDone                            :  9;  // Bits 28:20
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATATRAINSTATUS0_STRUCT;

typedef union {
  struct {
    UINT32 Rank3DccDone                            :  9;  // Bits 8:0
    UINT32 Spare0                                  :  1;  // Bits 9:9
    UINT32 CntDone                                 :  1;  // Bits 10:10
    UINT32 Dcd_O_Cnt                               :  15;  // Bits 25:11
    UINT32 Spare1                                  :  1;  // Bits 26:26
    UINT32 BinFsmCurrState                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATATRAINSTATUS1_STRUCT;

typedef union {
  struct {
    UINT32 AuxCnt                                  :  16;  // Bits 15:0
    UINT32 ReplicaOffset                           :  7;  // Bits 22:16
    UINT32 VTCompOffset                            :  7;  // Bits 29:23
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATATRAINSTATUS2_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  11;  // Bits 10:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 27:11
    UINT32 Spare                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATATRAINERRSTATUSRANK0_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  9;  // Bits 8:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 25:9
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATATRAINERRSTATUSRANK1_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  9;  // Bits 8:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 25:9
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATATRAINERRSTATUSRANK2_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  9;  // Bits 8:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 25:9
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATATRAINERRSTATUSRANK3_STRUCT;

typedef union {
  struct {
    UINT32 ReplicaTrain_GVp0                       :  6;  // Bits 5:0
    UINT32 ReplicaTrain_GVp1                       :  6;  // Bits 11:6
    UINT32 ReplicaTrain_GVp2                       :  6;  // Bits 17:12
    UINT32 ReplicaTrain_GVp3                       :  6;  // Bits 23:18
    UINT32 ReplicaOffsetPrev                       :  7;  // Bits 30:24
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATATRAINREPLICA0_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATATRAINVAL0RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATATRAINVAL0RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATATRAINVAL0RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATATRAINVAL0RANK3_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 ReplicaShadowDccVal                     :  6;  // Bits 29:24
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATATRAINVAL1RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 spare2                                  :  2;  // Bits 25:24
    UINT32 binfsmsteptosavecnts                    :  3;  // Bits 28:26
    UINT32 savecntsatchosenbinstep                 :  1;  // Bits 29:29
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATATRAINVAL1RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 Spare                                   :  6;  // Bits 29:24
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATATRAINVAL1RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 Spare                                   :  6;  // Bits 29:24
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATATRAINVAL1RANK3_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_0                        :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_4                        :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_8                        :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_12                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_16                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATADCCPILUT0_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_20                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_24                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_28                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_32                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_36                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATADCCPILUT1_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_40                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_44                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_48                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_52                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_56                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATADCCPILUT2_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_60                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_64                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_68                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_72                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_76                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATADCCPILUT3_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_80                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_84                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_88                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_92                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_96                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATADCCPILUT4_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_100                      :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_104                      :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_108                      :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_112                      :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_116                      :  6;  // Bits 29:24
    UINT32 DccPiAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATADCCPILUT5_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_120                      :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_124                      :  6;  // Bits 11:6
    UINT32 DccPiStaticCode                         :  6;  // Bits 17:12
    UINT32 DccPiStaticCodeGear1                    :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DCCDATADCCPILUT6_STRUCT;

typedef union {
  struct {
    UINT32 DqTcoCompBit0                           :  6;  // Bits 5:0
    UINT32 DqTcoCompBit1                           :  6;  // Bits 11:6
    UINT32 DqTcoCompBit2                           :  6;  // Bits 17:12
    UINT32 DqTcoCompBit3                           :  6;  // Bits 23:18
    UINT32 DqsNTcoComp                             :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DDRCRDATATCOCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 DqTcoCompBit4                           :  6;  // Bits 5:0
    UINT32 DqTcoCompBit5                           :  6;  // Bits 11:6
    UINT32 DqTcoCompBit6                           :  6;  // Bits 17:12
    UINT32 DqTcoCompBit7                           :  6;  // Bits 23:18
    UINT32 DqsPTcoComp                             :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DDRCRDATATCOCONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit6Rank0                       :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit6Rank1                       :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit7Rank0                       :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit7Rank1                       :  6;  // Bits 23:18
    UINT32 DfeDlyModeRank0                         :  2;  // Bits 25:24
    UINT32 DfeDlyModeRank1                         :  2;  // Bits 27:26
    UINT32 DfeDlyModeRank2                         :  2;  // Bits 29:28
    UINT32 DfeDlyModeRank3                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DDRCRDATADFECONTROL1RANK01_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit6Rank2                       :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit6Rank3                       :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit7Rank2                       :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit7Rank3                       :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DDRCRDATADFECONTROL1RANK23_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DDRCRDATADFECONTROL0RANK0_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DDRCRDATADFECONTROL0RANK1_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DDRCRDATADFECONTROL0RANK2_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH0_CR_DDRCRDATADFECONTROL0RANK3_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_RXCONTROL0RANK0_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_RXCONTROL0RANK1_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_RXCONTROL0RANK2_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_RXCONTROL0RANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_RXCONTROL1RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_RXCONTROL1RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_RXCONTROL1RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_RXCONTROL1RANK3_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 TxRankMuxDelay                          :  4;  // Bits 29:26
    UINT32 Spare1                                  :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_TXTRAINRANK0_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 TxRankMuxDelay_2nd_stage_offset         :  2;  // Bits 27:26
    UINT32 Spare1                                  :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_TXTRAINRANK1_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 Spare1                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_TXTRAINRANK2_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 Spare1                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_TXTRAINRANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_TXPERBITLOWRANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_TXPERBITLOWRANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_TXPERBITLOWRANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_TXPERBITLOWRANK3_STRUCT;

typedef union {
  struct {
    UINT32 RcompDrvUp                              :  6;  // Bits 5:0
    UINT32 Rsvd                                    :  8;  // Bits 13:6
    UINT32 RcompDrvDown                            :  6;  // Bits 19:14
    UINT32 SlewRateComp                            :  5;  // Bits 24:20
    UINT32 Spare                                   :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_RCOMPDATA0_STRUCT;

typedef union {
  struct {
    UINT32 RcompOdtUp                              :  6;  // Bits 5:0
    UINT32 spare                                   :  20;  // Bits 25:6
    UINT32 RcompOdtDown                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_RCOMPDATA1_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeCoeffRank0                         :  2;  // Bits 1:0
    UINT32 DqDfeCoeffRank1                         :  2;  // Bits 3:2
    UINT32 DqDfeCoeffRank2                         :  2;  // Bits 5:4
    UINT32 DqDfeCoeffRank3                         :  2;  // Bits 7:6
    UINT32 en_rcvenpre_zero_fill                   :  1;  // Bits 8:8
    UINT32 spare                                   :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DDRCRDATACONTROL8_STRUCT;

typedef union {
  struct {
    UINT32 PanicVttUp                              :  8;  // Bits 7:0
    UINT32 PanicVttDn                              :  8;  // Bits 15:8
    UINT32 RcompCmdDn200ohm                        :  6;  // Bits 21:16
    UINT32 Spare                                   :  10;  // Bits 31:22
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_RCOMPDATA2_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_RXCONTROL2RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_RXCONTROL2RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_RXCONTROL2RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_RXCONTROL2RANK3_STRUCT;

typedef union {
  struct {
    UINT32 DataTrainFeedback                       :  9;  // Bits 8:0
    UINT32 Spare                                   :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DATATRAINFEEDBACK_STRUCT;

typedef union {
  struct {
    INT32  DqDrvUpCompOffset                       :  6;  // Bits 5:0
    INT32  DqDrvDownCompOffset                     :  6;  // Bits 11:6
    INT32  DqOdtUpCompOffset                       :  5;  // Bits 16:12
    INT32  DqOdtDownCompOffset                     :  5;  // Bits 21:17
    UINT32 Spare                                   :  5;  // Bits 26:22
    INT32  DqSlewRateCompOffset                    :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DDRCRDATAOFFSETCOMP_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 DllWeakLock                             :  1;  // Bits 6:6
    UINT32 SdllSegmentDisable                      :  3;  // Bits 9:7
    UINT32 RxBiasCtl                               :  4;  // Bits 13:10
    INT32  OdtDelay                                :  5;  // Bits 18:14
    UINT32 OdtDuration                             :  3;  // Bits 21:19
    INT32  SenseAmpDelay                           :  5;  // Bits 26:22
    UINT32 SenseAmpDuration                        :  3;  // Bits 29:27
    UINT32 CBEnAmp2                                :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DDRCRDATACONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 RxStaggerCtl                            :  5;  // Bits 4:0
    UINT32 ForceBiasOn                             :  1;  // Bits 5:5
    UINT32 ForceRxOn                               :  1;  // Bits 6:6
    UINT32 DisableDqsOdtStatic                     :  1;  // Bits 7:7
    UINT32 LpDdrLongOdtEn                          :  1;  // Bits 8:8
    UINT32 RxRankMuxDelay                          :  4;  // Bits 12:9
    UINT32 RxClkStgNum                             :  5;  // Bits 17:13
    UINT32 WlLongDelEn                             :  1;  // Bits 18:18
    UINT32 EnableVrefPwrDn                         :  1;  // Bits 19:19
    UINT32 Ddr4Mode                                :  1;  // Bits 20:20
    UINT32 EnVddqOdt                               :  1;  // Bits 21:21
    UINT32 EnVttOdt                                :  1;  // Bits 22:22
    UINT32 EnConstZEqTx                            :  1;  // Bits 23:23
    UINT32 TxEqDis                                 :  1;  // Bits 24:24
    UINT32 RxVrefProgMFC                           :  1;  // Bits 25:25
    UINT32 Cben                                    :  3;  // Bits 28:26
    UINT32 TxDeskewDisable                         :  1;  // Bits 29:29
    UINT32 RxDeskewDisable                         :  1;  // Bits 30:30
    UINT32 DqSlewDlyByPass                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DDRCRDATACONTROL2_STRUCT;

typedef union {
  struct {
    INT32  RcvEnOffset                             :  6;  // Bits 5:0
    INT32  RxDqsOffset                             :  7;  // Bits 12:6
    INT32  TxDqOffset                              :  6;  // Bits 18:13
    INT32  TxDqsOffset                             :  6;  // Bits 24:19
    INT32  VrefOffset                              :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DDRCRDATAOFFSETTRAIN_STRUCT;

typedef union {
  struct {
    UINT32 RxTrainingMode                          :  1;  // Bits 0:0
    UINT32 WLTrainingMode                          :  1;  // Bits 1:1
    UINT32 RLTrainingMode                          :  1;  // Bits 2:2
    UINT32 SenseampTrainingMode                    :  1;  // Bits 3:3
    UINT32 TxOn                                    :  1;  // Bits 4:4
    UINT32 LPDDR_Mode                              :  1;  // Bits 5:5
    UINT32 RxPiOn                                  :  1;  // Bits 6:6
    UINT32 TxPiOn                                  :  1;  // Bits 7:7
    UINT32 InternalClocksOn                        :  1;  // Bits 8:8
    UINT32 RepeaterClocksOn                        :  1;  // Bits 9:9
    UINT32 TxDisable                               :  1;  // Bits 10:10
    UINT32 RxDisable                               :  1;  // Bits 11:11
    UINT32 Spare2                                  :  1;  // Bits 12:12
    UINT32 RxDqsCtle                               :  2;  // Bits 14:13
    UINT32 RxReadPointer                           :  4;  // Bits 18:15
    UINT32 xover_mindelay_ctl                      :  2;  // Bits 20:19
    UINT32 DQDQSLowsupEn                           :  1;  // Bits 21:21
    UINT32 DqTcoBypass                             :  1;  // Bits 22:22
    UINT32 viewQclkDis                             :  1;  // Bits 23:23
    UINT32 ForceOdtOn                              :  1;  // Bits 24:24
    UINT32 OdtSampOff                              :  1;  // Bits 25:25
    UINT32 DisableOdtStatic                        :  1;  // Bits 26:26
    UINT32 DdrCRForceODTOn                         :  1;  // Bits 27:27
    UINT32 spare                                   :  1;  // Bits 28:28
    UINT32 LongOdtR2W                              :  1;  // Bits 29:29
    UINT32 OdtSampExtendEn                         :  1;  // Bits 30:30
    UINT32 EarlyRleakEn                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DDRCRDATACONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 TxDqsRankMuxDelay                       :  4;  // Bits 3:0
    UINT32 TxDqsRankMuxDelay_2nd_stage_offset      :  2;  // Bits 5:4
    UINT32 ForceDqsOnQuickOdtOff                   :  1;  // Bits 6:6
    UINT32 Strong2WeakOnDqsOdt                     :  1;  // Bits 7:7
    INT32  DqsOdtDelay                             :  6;  // Bits 13:8
    UINT32 vrefinten_atckepwrdown                  :  1;  // Bits 14:14
    UINT32 DqsOdtSampExtendEn                      :  1;  // Bits 15:15
    UINT32 DqsOdtDuration                          :  3;  // Bits 18:16
    UINT32 AllowOvrdOdtOnAsyncDrv                  :  1;  // Bits 19:19
    UINT32 LeakerComp                              :  3;  // Bits 22:20
    UINT32 rxclkstgnummsb                          :  1;  // Bits 23:23
    UINT32 NomPgDis                                :  1;  // Bits 24:24
    UINT32 rcven_four_cycle_fill                   :  1;  // Bits 25:25
    UINT32 StrongWkLeaker                          :  4;  // Bits 29:26
    UINT32 CBEnAmp1                                :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DDRCRDATACONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 leakerwithtxanalogen                    :  1;  // Bits 0:0
    UINT32 glbdrv_clkgate_enable                   :  1;  // Bits 1:1
    UINT32 biasrcomp                               :  3;  // Bits 4:2
    UINT32 txdeskewcal                             :  1;  // Bits 5:5
    UINT32 txdeskewdqscodesel                      :  1;  // Bits 6:6
    UINT32 rxdeskewcal                             :  1;  // Bits 7:7
    UINT32 rxdeskewdqscodesel                      :  1;  // Bits 8:8
    UINT32 DisPanicDrv                             :  2;  // Bits 10:9
    UINT32 dllnbiassel                             :  1;  // Bits 11:11
    UINT32 rxsel                                   :  1;  // Bits 12:12
    UINT32 ampoffseten                             :  1;  // Bits 13:13
    UINT32 LpDdr4Mode                              :  1;  // Bits 14:14
    UINT32 lpddr4wrlongpreambleen                  :  1;  // Bits 15:15
    UINT32 ddr4wrlongpreambleen                    :  1;  // Bits 16:16
    UINT32 VssODTSingleSegEn                       :  1;  // Bits 17:17
    UINT32 VssODTEn                                :  1;  // Bits 18:18
    UINT32 dqsodtdowncompoffset                    :  5;  // Bits 23:19
    UINT32 dqsodtupcompoffset                      :  5;  // Bits 28:24
    UINT32 spare2                                  :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DDRCRDATACONTROL4_STRUCT;

typedef union {
  struct {
    UINT32 RxVref                                  :  8;  // Bits 7:0
    UINT32 ddrcrdqsmaskcnten                       :  1;  // Bits 8:8
    UINT32 ddrcrnumofpulses                        :  2;  // Bits 10:9
    UINT32 ddrcrmaskcntpulsenumstart               :  4;  // Bits 14:11
    UINT32 Lp4xVoltageSelect                       :  1;  // Bits 15:15
    UINT32 DdrDqOvrdModeEn                         :  8;  // Bits 23:16
    UINT32 DdrDqOvrdData                           :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DDRCRDATACONTROL5_STRUCT;

typedef union {
  struct {
    UINT32 RankOvrd                                :  1;  // Bits 0:0
    UINT32 RankValue                               :  2;  // Bits 2:1
    UINT32 Gear1                                   :  1;  // Bits 3:3
    UINT32 RxDqsAmpOffset                          :  5;  // Bits 8:4
    UINT32 fast_dqsoutputenable                    :  1;  // Bits 9:9
    UINT32 tx_clock_on_with_txanalogen             :  1;  // Bits 10:10
    UINT32 local_gate_d0tx                         :  1;  // Bits 11:11
    UINT32 strongwkleakermsb                       :  2;  // Bits 13:12
    UINT32 forcedqsponwithleaker                   :  1;  // Bits 14:14
    UINT32 forcedqsnonwithleaker                   :  1;  // Bits 15:15
    UINT32 RxBiasCtl1                              :  8;  // Bits 23:16
    UINT32 ForceDqsPon                             :  1;  // Bits 24:24
    UINT32 ForceDqsNon                             :  1;  // Bits 25:25
    UINT32 sdll_picb                               :  3;  // Bits 28:26
    UINT32 d0_picb                                 :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DDRCRDATACONTROL6_STRUCT;

typedef union {
  struct {
    UINT32 DqsDfeDlyRank0                          :  6;  // Bits 5:0
    UINT32 DqsDfeDlyRank1                          :  6;  // Bits 11:6
    UINT32 DqsDfeDlyRank2                          :  6;  // Bits 17:12
    UINT32 DqsDfeDlyRank3                          :  6;  // Bits 23:18
    UINT32 sdll_bw_ctrl                            :  4;  // Bits 27:24
    UINT32 d0_bw_ctrl                              :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DDRCRDATACONTROL7_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DELTADQSRANK0_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DELTADQSRANK1_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DELTADQSRANK2_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DELTADQSRANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_RXCONTROL3RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_RXCONTROL3RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_RXCONTROL3RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_RXCONTROL3RANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_TXPERBITHIRANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_TXPERBITHIRANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_TXPERBITHIRANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_TXPERBITHIRANK3_STRUCT;

typedef union {
  struct {
    UINT32 GVPointG1                               :  1;  // Bits 0:0
    UINT32 GVPointG2                               :  2;  // Bits 2:1
    UINT32 ReplicaOffsetUse                        :  1;  // Bits 3:3
    UINT32 VTCompOffsetUse                         :  2;  // Bits 5:4
    UINT32 ExtOffset                               :  7;  // Bits 12:6
    UINT32 BiasOffset                              :  15;  // Bits 27:13
    UINT32 ActiveRanks                             :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATACONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 DccCodeOvrd                             :  6;  // Bits 5:0
    UINT32 RepDccAipCb                             :  2;  // Bits 7:6
    UINT32 DccPtrOvrd                              :  4;  // Bits 11:8
    UINT32 RnkPtrOvrd                              :  2;  // Bits 13:12
    UINT32 DcdDigEnOvrd                            :  1;  // Bits 14:14
    UINT32 DcdAnaEnOvrd                            :  1;  // Bits 15:15
    UINT32 DcdWindow                               :  15;  // Bits 30:16
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATACONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 StartBinCode                            :  6;  // Bits 5:0
    UINT32 CodePtrStartBit                         :  3;  // Bits 8:6
    UINT32 DccTrshOld                              :  13;  // Bits 21:9
    UINT32 DcdCntsStartDiff                        :  5;  // Bits 26:22
    UINT32 ClkGateDisable                          :  1;  // Bits 27:27
    UINT32 DccDataViewSelect0                      :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATACONTROL2_STRUCT;

typedef union {
  struct {
    UINT32 ActiveDccRank0                          :  11;  // Bits 10:0
    UINT32 ActiveDccRank1                          :  9;  // Bits 19:11
    UINT32 ActiveDccRank2                          :  9;  // Bits 28:20
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATACONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 ActiveDccRank3                          :  9;  // Bits 8:0
    UINT32 Spare                                   :  1;  // Bits 9:9
    UINT32 ReplicaPrev_GVp0                        :  6;  // Bits 15:10
    UINT32 ReplicaPrev_GVp1                        :  6;  // Bits 21:16
    UINT32 ReplicaPrev_GVp2                        :  6;  // Bits 27:22
    UINT32 DccDataViewSelect1                      :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATACONTROL4_STRUCT;

typedef union {
  struct {
    UINT32 Spare                                   :  2;  // Bits 1:0
    UINT32 vtcompoffsetmsgwren                     :  1;  // Bits 2:2
    UINT32 ReplicaPrev_GVp3                        :  6;  // Bits 8:3
    UINT32 BubbleCntVal                            :  5;  // Bits 13:9
    UINT32 DeterministicSyncVal                    :  6;  // Bits 19:14
    UINT32 DeterministicCntVal                     :  11;  // Bits 30:20
    UINT32 DeterministicMode                       :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATACONTROL5_STRUCT;

typedef union {
  struct {
    UINT32 Rank0DccDone                            :  11;  // Bits 10:0
    UINT32 Rank1DccDone                            :  9;  // Bits 19:11
    UINT32 Rank2DccDone                            :  9;  // Bits 28:20
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATATRAINSTATUS0_STRUCT;

typedef union {
  struct {
    UINT32 Rank3DccDone                            :  9;  // Bits 8:0
    UINT32 Spare0                                  :  1;  // Bits 9:9
    UINT32 CntDone                                 :  1;  // Bits 10:10
    UINT32 Dcd_O_Cnt                               :  15;  // Bits 25:11
    UINT32 Spare1                                  :  1;  // Bits 26:26
    UINT32 BinFsmCurrState                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATATRAINSTATUS1_STRUCT;

typedef union {
  struct {
    UINT32 AuxCnt                                  :  16;  // Bits 15:0
    UINT32 ReplicaOffset                           :  7;  // Bits 22:16
    UINT32 VTCompOffset                            :  7;  // Bits 29:23
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATATRAINSTATUS2_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  11;  // Bits 10:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 27:11
    UINT32 Spare                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATATRAINERRSTATUSRANK0_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  9;  // Bits 8:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 25:9
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATATRAINERRSTATUSRANK1_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  9;  // Bits 8:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 25:9
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATATRAINERRSTATUSRANK2_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  9;  // Bits 8:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 25:9
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATATRAINERRSTATUSRANK3_STRUCT;

typedef union {
  struct {
    UINT32 ReplicaTrain_GVp0                       :  6;  // Bits 5:0
    UINT32 ReplicaTrain_GVp1                       :  6;  // Bits 11:6
    UINT32 ReplicaTrain_GVp2                       :  6;  // Bits 17:12
    UINT32 ReplicaTrain_GVp3                       :  6;  // Bits 23:18
    UINT32 ReplicaOffsetPrev                       :  7;  // Bits 30:24
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATATRAINREPLICA0_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATATRAINVAL0RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATATRAINVAL0RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATATRAINVAL0RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATATRAINVAL0RANK3_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 ReplicaShadowDccVal                     :  6;  // Bits 29:24
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATATRAINVAL1RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 spare2                                  :  2;  // Bits 25:24
    UINT32 binfsmsteptosavecnts                    :  3;  // Bits 28:26
    UINT32 savecntsatchosenbinstep                 :  1;  // Bits 29:29
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATATRAINVAL1RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 Spare                                   :  6;  // Bits 29:24
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATATRAINVAL1RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 Spare                                   :  6;  // Bits 29:24
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATATRAINVAL1RANK3_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_0                        :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_4                        :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_8                        :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_12                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_16                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATADCCPILUT0_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_20                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_24                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_28                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_32                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_36                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATADCCPILUT1_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_40                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_44                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_48                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_52                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_56                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATADCCPILUT2_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_60                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_64                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_68                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_72                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_76                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATADCCPILUT3_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_80                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_84                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_88                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_92                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_96                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATADCCPILUT4_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_100                      :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_104                      :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_108                      :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_112                      :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_116                      :  6;  // Bits 29:24
    UINT32 DccPiAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATADCCPILUT5_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_120                      :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_124                      :  6;  // Bits 11:6
    UINT32 DccPiStaticCode                         :  6;  // Bits 17:12
    UINT32 DccPiStaticCodeGear1                    :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DCCDATADCCPILUT6_STRUCT;

typedef union {
  struct {
    UINT32 DqTcoCompBit0                           :  6;  // Bits 5:0
    UINT32 DqTcoCompBit1                           :  6;  // Bits 11:6
    UINT32 DqTcoCompBit2                           :  6;  // Bits 17:12
    UINT32 DqTcoCompBit3                           :  6;  // Bits 23:18
    UINT32 DqsNTcoComp                             :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DDRCRDATATCOCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 DqTcoCompBit4                           :  6;  // Bits 5:0
    UINT32 DqTcoCompBit5                           :  6;  // Bits 11:6
    UINT32 DqTcoCompBit6                           :  6;  // Bits 17:12
    UINT32 DqTcoCompBit7                           :  6;  // Bits 23:18
    UINT32 DqsPTcoComp                             :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DDRCRDATATCOCONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit6Rank0                       :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit6Rank1                       :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit7Rank0                       :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit7Rank1                       :  6;  // Bits 23:18
    UINT32 DfeDlyModeRank0                         :  2;  // Bits 25:24
    UINT32 DfeDlyModeRank1                         :  2;  // Bits 27:26
    UINT32 DfeDlyModeRank2                         :  2;  // Bits 29:28
    UINT32 DfeDlyModeRank3                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DDRCRDATADFECONTROL1RANK01_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit6Rank2                       :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit6Rank3                       :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit7Rank2                       :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit7Rank3                       :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DDRCRDATADFECONTROL1RANK23_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DDRCRDATADFECONTROL0RANK0_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DDRCRDATADFECONTROL0RANK1_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DDRCRDATADFECONTROL0RANK2_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6CH1_CR_DDRCRDATADFECONTROL0RANK3_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_RXCONTROL0RANK0_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_RXCONTROL0RANK1_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_RXCONTROL0RANK2_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_RXCONTROL0RANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_RXCONTROL1RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_RXCONTROL1RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_RXCONTROL1RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_RXCONTROL1RANK3_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 TxRankMuxDelay                          :  4;  // Bits 29:26
    UINT32 Spare1                                  :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_TXTRAINRANK0_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 TxRankMuxDelay_2nd_stage_offset         :  2;  // Bits 27:26
    UINT32 Spare1                                  :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_TXTRAINRANK1_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 Spare1                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_TXTRAINRANK2_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 Spare1                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_TXTRAINRANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_TXPERBITLOWRANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_TXPERBITLOWRANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_TXPERBITLOWRANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_TXPERBITLOWRANK3_STRUCT;

typedef union {
  struct {
    UINT32 RcompDrvUp                              :  6;  // Bits 5:0
    UINT32 Rsvd                                    :  8;  // Bits 13:6
    UINT32 RcompDrvDown                            :  6;  // Bits 19:14
    UINT32 SlewRateComp                            :  5;  // Bits 24:20
    UINT32 Spare                                   :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_RCOMPDATA0_STRUCT;

typedef union {
  struct {
    UINT32 RcompOdtUp                              :  6;  // Bits 5:0
    UINT32 spare                                   :  20;  // Bits 25:6
    UINT32 RcompOdtDown                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_RCOMPDATA1_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeCoeffRank0                         :  2;  // Bits 1:0
    UINT32 DqDfeCoeffRank1                         :  2;  // Bits 3:2
    UINT32 DqDfeCoeffRank2                         :  2;  // Bits 5:4
    UINT32 DqDfeCoeffRank3                         :  2;  // Bits 7:6
    UINT32 en_rcvenpre_zero_fill                   :  1;  // Bits 8:8
    UINT32 spare                                   :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DDRCRDATACONTROL8_STRUCT;

typedef union {
  struct {
    UINT32 PanicVttUp                              :  8;  // Bits 7:0
    UINT32 PanicVttDn                              :  8;  // Bits 15:8
    UINT32 RcompCmdDn200ohm                        :  6;  // Bits 21:16
    UINT32 Spare                                   :  10;  // Bits 31:22
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_RCOMPDATA2_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_RXCONTROL2RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_RXCONTROL2RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_RXCONTROL2RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_RXCONTROL2RANK3_STRUCT;

typedef union {
  struct {
    UINT32 DataTrainFeedback                       :  9;  // Bits 8:0
    UINT32 Spare                                   :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DATATRAINFEEDBACK_STRUCT;

typedef union {
  struct {
    INT32  DqDrvUpCompOffset                       :  6;  // Bits 5:0
    INT32  DqDrvDownCompOffset                     :  6;  // Bits 11:6
    INT32  DqOdtUpCompOffset                       :  5;  // Bits 16:12
    INT32  DqOdtDownCompOffset                     :  5;  // Bits 21:17
    UINT32 Spare                                   :  5;  // Bits 26:22
    INT32  DqSlewRateCompOffset                    :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 DllWeakLock                             :  1;  // Bits 6:6
    UINT32 SdllSegmentDisable                      :  3;  // Bits 9:7
    UINT32 RxBiasCtl                               :  4;  // Bits 13:10
    INT32  OdtDelay                                :  5;  // Bits 18:14
    UINT32 OdtDuration                             :  3;  // Bits 21:19
    INT32  SenseAmpDelay                           :  5;  // Bits 26:22
    UINT32 SenseAmpDuration                        :  3;  // Bits 29:27
    UINT32 CBEnAmp2                                :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DDRCRDATACONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 RxStaggerCtl                            :  5;  // Bits 4:0
    UINT32 ForceBiasOn                             :  1;  // Bits 5:5
    UINT32 ForceRxOn                               :  1;  // Bits 6:6
    UINT32 DisableDqsOdtStatic                     :  1;  // Bits 7:7
    UINT32 LpDdrLongOdtEn                          :  1;  // Bits 8:8
    UINT32 RxRankMuxDelay                          :  4;  // Bits 12:9
    UINT32 RxClkStgNum                             :  5;  // Bits 17:13
    UINT32 WlLongDelEn                             :  1;  // Bits 18:18
    UINT32 EnableVrefPwrDn                         :  1;  // Bits 19:19
    UINT32 Ddr4Mode                                :  1;  // Bits 20:20
    UINT32 EnVddqOdt                               :  1;  // Bits 21:21
    UINT32 EnVttOdt                                :  1;  // Bits 22:22
    UINT32 EnConstZEqTx                            :  1;  // Bits 23:23
    UINT32 TxEqDis                                 :  1;  // Bits 24:24
    UINT32 RxVrefProgMFC                           :  1;  // Bits 25:25
    UINT32 Cben                                    :  3;  // Bits 28:26
    UINT32 TxDeskewDisable                         :  1;  // Bits 29:29
    UINT32 RxDeskewDisable                         :  1;  // Bits 30:30
    UINT32 DqSlewDlyByPass                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DDRCRDATACONTROL2_STRUCT;

typedef union {
  struct {
    INT32  RcvEnOffset                             :  6;  // Bits 5:0
    INT32  RxDqsOffset                             :  7;  // Bits 12:6
    INT32  TxDqOffset                              :  6;  // Bits 18:13
    INT32  TxDqsOffset                             :  6;  // Bits 24:19
    INT32  VrefOffset                              :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DDRCRDATAOFFSETTRAIN_STRUCT;

typedef union {
  struct {
    UINT32 RxTrainingMode                          :  1;  // Bits 0:0
    UINT32 WLTrainingMode                          :  1;  // Bits 1:1
    UINT32 RLTrainingMode                          :  1;  // Bits 2:2
    UINT32 SenseampTrainingMode                    :  1;  // Bits 3:3
    UINT32 TxOn                                    :  1;  // Bits 4:4
    UINT32 LPDDR_Mode                              :  1;  // Bits 5:5
    UINT32 RxPiOn                                  :  1;  // Bits 6:6
    UINT32 TxPiOn                                  :  1;  // Bits 7:7
    UINT32 InternalClocksOn                        :  1;  // Bits 8:8
    UINT32 RepeaterClocksOn                        :  1;  // Bits 9:9
    UINT32 TxDisable                               :  1;  // Bits 10:10
    UINT32 RxDisable                               :  1;  // Bits 11:11
    UINT32 Spare2                                  :  1;  // Bits 12:12
    UINT32 RxDqsCtle                               :  2;  // Bits 14:13
    UINT32 RxReadPointer                           :  4;  // Bits 18:15
    UINT32 xover_mindelay_ctl                      :  2;  // Bits 20:19
    UINT32 DQDQSLowsupEn                           :  1;  // Bits 21:21
    UINT32 DqTcoBypass                             :  1;  // Bits 22:22
    UINT32 viewQclkDis                             :  1;  // Bits 23:23
    UINT32 ForceOdtOn                              :  1;  // Bits 24:24
    UINT32 OdtSampOff                              :  1;  // Bits 25:25
    UINT32 DisableOdtStatic                        :  1;  // Bits 26:26
    UINT32 DdrCRForceODTOn                         :  1;  // Bits 27:27
    UINT32 spare                                   :  1;  // Bits 28:28
    UINT32 LongOdtR2W                              :  1;  // Bits 29:29
    UINT32 OdtSampExtendEn                         :  1;  // Bits 30:30
    UINT32 EarlyRleakEn                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DDRCRDATACONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 TxDqsRankMuxDelay                       :  4;  // Bits 3:0
    UINT32 TxDqsRankMuxDelay_2nd_stage_offset      :  2;  // Bits 5:4
    UINT32 ForceDqsOnQuickOdtOff                   :  1;  // Bits 6:6
    UINT32 Strong2WeakOnDqsOdt                     :  1;  // Bits 7:7
    INT32  DqsOdtDelay                             :  6;  // Bits 13:8
    UINT32 vrefinten_atckepwrdown                  :  1;  // Bits 14:14
    UINT32 DqsOdtSampExtendEn                      :  1;  // Bits 15:15
    UINT32 DqsOdtDuration                          :  3;  // Bits 18:16
    UINT32 AllowOvrdOdtOnAsyncDrv                  :  1;  // Bits 19:19
    UINT32 LeakerComp                              :  3;  // Bits 22:20
    UINT32 rxclkstgnummsb                          :  1;  // Bits 23:23
    UINT32 NomPgDis                                :  1;  // Bits 24:24
    UINT32 rcven_four_cycle_fill                   :  1;  // Bits 25:25
    UINT32 StrongWkLeaker                          :  4;  // Bits 29:26
    UINT32 CBEnAmp1                                :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DDRCRDATACONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 leakerwithtxanalogen                    :  1;  // Bits 0:0
    UINT32 glbdrv_clkgate_enable                   :  1;  // Bits 1:1
    UINT32 biasrcomp                               :  3;  // Bits 4:2
    UINT32 txdeskewcal                             :  1;  // Bits 5:5
    UINT32 txdeskewdqscodesel                      :  1;  // Bits 6:6
    UINT32 rxdeskewcal                             :  1;  // Bits 7:7
    UINT32 rxdeskewdqscodesel                      :  1;  // Bits 8:8
    UINT32 DisPanicDrv                             :  2;  // Bits 10:9
    UINT32 dllnbiassel                             :  1;  // Bits 11:11
    UINT32 rxsel                                   :  1;  // Bits 12:12
    UINT32 ampoffseten                             :  1;  // Bits 13:13
    UINT32 LpDdr4Mode                              :  1;  // Bits 14:14
    UINT32 lpddr4wrlongpreambleen                  :  1;  // Bits 15:15
    UINT32 ddr4wrlongpreambleen                    :  1;  // Bits 16:16
    UINT32 VssODTSingleSegEn                       :  1;  // Bits 17:17
    UINT32 VssODTEn                                :  1;  // Bits 18:18
    UINT32 dqsodtdowncompoffset                    :  5;  // Bits 23:19
    UINT32 dqsodtupcompoffset                      :  5;  // Bits 28:24
    UINT32 spare2                                  :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DDRCRDATACONTROL4_STRUCT;

typedef union {
  struct {
    UINT32 RxVref                                  :  8;  // Bits 7:0
    UINT32 ddrcrdqsmaskcnten                       :  1;  // Bits 8:8
    UINT32 ddrcrnumofpulses                        :  2;  // Bits 10:9
    UINT32 ddrcrmaskcntpulsenumstart               :  4;  // Bits 14:11
    UINT32 Lp4xVoltageSelect                       :  1;  // Bits 15:15
    UINT32 DdrDqOvrdModeEn                         :  8;  // Bits 23:16
    UINT32 DdrDqOvrdData                           :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DDRCRDATACONTROL5_STRUCT;

typedef union {
  struct {
    UINT32 RankOvrd                                :  1;  // Bits 0:0
    UINT32 RankValue                               :  2;  // Bits 2:1
    UINT32 Gear1                                   :  1;  // Bits 3:3
    UINT32 RxDqsAmpOffset                          :  5;  // Bits 8:4
    UINT32 fast_dqsoutputenable                    :  1;  // Bits 9:9
    UINT32 tx_clock_on_with_txanalogen             :  1;  // Bits 10:10
    UINT32 local_gate_d0tx                         :  1;  // Bits 11:11
    UINT32 strongwkleakermsb                       :  2;  // Bits 13:12
    UINT32 forcedqsponwithleaker                   :  1;  // Bits 14:14
    UINT32 forcedqsnonwithleaker                   :  1;  // Bits 15:15
    UINT32 RxBiasCtl1                              :  8;  // Bits 23:16
    UINT32 ForceDqsPon                             :  1;  // Bits 24:24
    UINT32 ForceDqsNon                             :  1;  // Bits 25:25
    UINT32 sdll_picb                               :  3;  // Bits 28:26
    UINT32 d0_picb                                 :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DDRCRDATACONTROL6_STRUCT;

typedef union {
  struct {
    UINT32 DqsDfeDlyRank0                          :  6;  // Bits 5:0
    UINT32 DqsDfeDlyRank1                          :  6;  // Bits 11:6
    UINT32 DqsDfeDlyRank2                          :  6;  // Bits 17:12
    UINT32 DqsDfeDlyRank3                          :  6;  // Bits 23:18
    UINT32 sdll_bw_ctrl                            :  4;  // Bits 27:24
    UINT32 d0_bw_ctrl                              :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DDRCRDATACONTROL7_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DELTADQSRANK0_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DELTADQSRANK1_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DELTADQSRANK2_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DELTADQSRANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_RXCONTROL3RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_RXCONTROL3RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_RXCONTROL3RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_RXCONTROL3RANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_TXPERBITHIRANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_TXPERBITHIRANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_TXPERBITHIRANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_TXPERBITHIRANK3_STRUCT;

typedef union {
  struct {
    UINT32 GVPointG1                               :  1;  // Bits 0:0
    UINT32 GVPointG2                               :  2;  // Bits 2:1
    UINT32 ReplicaOffsetUse                        :  1;  // Bits 3:3
    UINT32 VTCompOffsetUse                         :  2;  // Bits 5:4
    UINT32 ExtOffset                               :  7;  // Bits 12:6
    UINT32 BiasOffset                              :  15;  // Bits 27:13
    UINT32 ActiveRanks                             :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATACONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 DccCodeOvrd                             :  6;  // Bits 5:0
    UINT32 RepDccAipCb                             :  2;  // Bits 7:6
    UINT32 DccPtrOvrd                              :  4;  // Bits 11:8
    UINT32 RnkPtrOvrd                              :  2;  // Bits 13:12
    UINT32 DcdDigEnOvrd                            :  1;  // Bits 14:14
    UINT32 DcdAnaEnOvrd                            :  1;  // Bits 15:15
    UINT32 DcdWindow                               :  15;  // Bits 30:16
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATACONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 StartBinCode                            :  6;  // Bits 5:0
    UINT32 CodePtrStartBit                         :  3;  // Bits 8:6
    UINT32 DccTrshOld                              :  13;  // Bits 21:9
    UINT32 DcdCntsStartDiff                        :  5;  // Bits 26:22
    UINT32 ClkGateDisable                          :  1;  // Bits 27:27
    UINT32 DccDataViewSelect0                      :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATACONTROL2_STRUCT;

typedef union {
  struct {
    UINT32 ActiveDccRank0                          :  11;  // Bits 10:0
    UINT32 ActiveDccRank1                          :  9;  // Bits 19:11
    UINT32 ActiveDccRank2                          :  9;  // Bits 28:20
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATACONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 ActiveDccRank3                          :  9;  // Bits 8:0
    UINT32 Spare                                   :  1;  // Bits 9:9
    UINT32 ReplicaPrev_GVp0                        :  6;  // Bits 15:10
    UINT32 ReplicaPrev_GVp1                        :  6;  // Bits 21:16
    UINT32 ReplicaPrev_GVp2                        :  6;  // Bits 27:22
    UINT32 DccDataViewSelect1                      :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATACONTROL4_STRUCT;

typedef union {
  struct {
    UINT32 Spare                                   :  2;  // Bits 1:0
    UINT32 vtcompoffsetmsgwren                     :  1;  // Bits 2:2
    UINT32 ReplicaPrev_GVp3                        :  6;  // Bits 8:3
    UINT32 BubbleCntVal                            :  5;  // Bits 13:9
    UINT32 DeterministicSyncVal                    :  6;  // Bits 19:14
    UINT32 DeterministicCntVal                     :  11;  // Bits 30:20
    UINT32 DeterministicMode                       :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATACONTROL5_STRUCT;

typedef union {
  struct {
    UINT32 Rank0DccDone                            :  11;  // Bits 10:0
    UINT32 Rank1DccDone                            :  9;  // Bits 19:11
    UINT32 Rank2DccDone                            :  9;  // Bits 28:20
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATATRAINSTATUS0_STRUCT;

typedef union {
  struct {
    UINT32 Rank3DccDone                            :  9;  // Bits 8:0
    UINT32 Spare0                                  :  1;  // Bits 9:9
    UINT32 CntDone                                 :  1;  // Bits 10:10
    UINT32 Dcd_O_Cnt                               :  15;  // Bits 25:11
    UINT32 Spare1                                  :  1;  // Bits 26:26
    UINT32 BinFsmCurrState                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATATRAINSTATUS1_STRUCT;

typedef union {
  struct {
    UINT32 AuxCnt                                  :  16;  // Bits 15:0
    UINT32 ReplicaOffset                           :  7;  // Bits 22:16
    UINT32 VTCompOffset                            :  7;  // Bits 29:23
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATATRAINSTATUS2_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  11;  // Bits 10:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 27:11
    UINT32 Spare                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATATRAINERRSTATUSRANK0_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  9;  // Bits 8:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 25:9
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATATRAINERRSTATUSRANK1_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  9;  // Bits 8:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 25:9
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATATRAINERRSTATUSRANK2_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  9;  // Bits 8:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 25:9
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATATRAINERRSTATUSRANK3_STRUCT;

typedef union {
  struct {
    UINT32 ReplicaTrain_GVp0                       :  6;  // Bits 5:0
    UINT32 ReplicaTrain_GVp1                       :  6;  // Bits 11:6
    UINT32 ReplicaTrain_GVp2                       :  6;  // Bits 17:12
    UINT32 ReplicaTrain_GVp3                       :  6;  // Bits 23:18
    UINT32 ReplicaOffsetPrev                       :  7;  // Bits 30:24
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATATRAINREPLICA0_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATATRAINVAL0RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATATRAINVAL0RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATATRAINVAL0RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATATRAINVAL0RANK3_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 ReplicaShadowDccVal                     :  6;  // Bits 29:24
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATATRAINVAL1RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 spare2                                  :  2;  // Bits 25:24
    UINT32 binfsmsteptosavecnts                    :  3;  // Bits 28:26
    UINT32 savecntsatchosenbinstep                 :  1;  // Bits 29:29
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATATRAINVAL1RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 Spare                                   :  6;  // Bits 29:24
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATATRAINVAL1RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 Spare                                   :  6;  // Bits 29:24
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATATRAINVAL1RANK3_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_0                        :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_4                        :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_8                        :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_12                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_16                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATADCCPILUT0_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_20                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_24                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_28                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_32                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_36                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATADCCPILUT1_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_40                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_44                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_48                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_52                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_56                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATADCCPILUT2_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_60                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_64                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_68                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_72                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_76                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATADCCPILUT3_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_80                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_84                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_88                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_92                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_96                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATADCCPILUT4_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_100                      :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_104                      :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_108                      :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_112                      :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_116                      :  6;  // Bits 29:24
    UINT32 DccPiAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATADCCPILUT5_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_120                      :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_124                      :  6;  // Bits 11:6
    UINT32 DccPiStaticCode                         :  6;  // Bits 17:12
    UINT32 DccPiStaticCodeGear1                    :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DCCDATADCCPILUT6_STRUCT;

typedef union {
  struct {
    UINT32 DqTcoCompBit0                           :  6;  // Bits 5:0
    UINT32 DqTcoCompBit1                           :  6;  // Bits 11:6
    UINT32 DqTcoCompBit2                           :  6;  // Bits 17:12
    UINT32 DqTcoCompBit3                           :  6;  // Bits 23:18
    UINT32 DqsNTcoComp                             :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DDRCRDATATCOCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 DqTcoCompBit4                           :  6;  // Bits 5:0
    UINT32 DqTcoCompBit5                           :  6;  // Bits 11:6
    UINT32 DqTcoCompBit6                           :  6;  // Bits 17:12
    UINT32 DqTcoCompBit7                           :  6;  // Bits 23:18
    UINT32 DqsPTcoComp                             :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DDRCRDATATCOCONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit6Rank0                       :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit6Rank1                       :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit7Rank0                       :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit7Rank1                       :  6;  // Bits 23:18
    UINT32 DfeDlyModeRank0                         :  2;  // Bits 25:24
    UINT32 DfeDlyModeRank1                         :  2;  // Bits 27:26
    UINT32 DfeDlyModeRank2                         :  2;  // Bits 29:28
    UINT32 DfeDlyModeRank3                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DDRCRDATADFECONTROL1RANK01_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit6Rank2                       :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit6Rank3                       :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit7Rank2                       :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit7Rank3                       :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DDRCRDATADFECONTROL1RANK23_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DDRCRDATADFECONTROL0RANK0_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DDRCRDATADFECONTROL0RANK1_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DDRCRDATADFECONTROL0RANK2_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH0_CR_DDRCRDATADFECONTROL0RANK3_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_RXCONTROL0RANK0_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_RXCONTROL0RANK1_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_RXCONTROL0RANK2_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_RXCONTROL0RANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_RXCONTROL1RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_RXCONTROL1RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_RXCONTROL1RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_RXCONTROL1RANK3_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 TxRankMuxDelay                          :  4;  // Bits 29:26
    UINT32 Spare1                                  :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_TXTRAINRANK0_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 TxRankMuxDelay_2nd_stage_offset         :  2;  // Bits 27:26
    UINT32 Spare1                                  :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_TXTRAINRANK1_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 Spare1                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_TXTRAINRANK2_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 Spare1                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_TXTRAINRANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_TXPERBITLOWRANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_TXPERBITLOWRANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_TXPERBITLOWRANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_TXPERBITLOWRANK3_STRUCT;

typedef union {
  struct {
    UINT32 RcompDrvUp                              :  6;  // Bits 5:0
    UINT32 Rsvd                                    :  8;  // Bits 13:6
    UINT32 RcompDrvDown                            :  6;  // Bits 19:14
    UINT32 SlewRateComp                            :  5;  // Bits 24:20
    UINT32 Spare                                   :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_RCOMPDATA0_STRUCT;

typedef union {
  struct {
    UINT32 RcompOdtUp                              :  6;  // Bits 5:0
    UINT32 spare                                   :  20;  // Bits 25:6
    UINT32 RcompOdtDown                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_RCOMPDATA1_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeCoeffRank0                         :  2;  // Bits 1:0
    UINT32 DqDfeCoeffRank1                         :  2;  // Bits 3:2
    UINT32 DqDfeCoeffRank2                         :  2;  // Bits 5:4
    UINT32 DqDfeCoeffRank3                         :  2;  // Bits 7:6
    UINT32 en_rcvenpre_zero_fill                   :  1;  // Bits 8:8
    UINT32 spare                                   :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DDRCRDATACONTROL8_STRUCT;

typedef union {
  struct {
    UINT32 PanicVttUp                              :  8;  // Bits 7:0
    UINT32 PanicVttDn                              :  8;  // Bits 15:8
    UINT32 RcompCmdDn200ohm                        :  6;  // Bits 21:16
    UINT32 Spare                                   :  10;  // Bits 31:22
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_RCOMPDATA2_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_RXCONTROL2RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_RXCONTROL2RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_RXCONTROL2RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_RXCONTROL2RANK3_STRUCT;

typedef union {
  struct {
    UINT32 DataTrainFeedback                       :  9;  // Bits 8:0
    UINT32 Spare                                   :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DATATRAINFEEDBACK_STRUCT;

typedef union {
  struct {
    INT32  DqDrvUpCompOffset                       :  6;  // Bits 5:0
    INT32  DqDrvDownCompOffset                     :  6;  // Bits 11:6
    INT32  DqOdtUpCompOffset                       :  5;  // Bits 16:12
    INT32  DqOdtDownCompOffset                     :  5;  // Bits 21:17
    UINT32 Spare                                   :  5;  // Bits 26:22
    INT32  DqSlewRateCompOffset                    :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DDRCRDATAOFFSETCOMP_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 DllWeakLock                             :  1;  // Bits 6:6
    UINT32 SdllSegmentDisable                      :  3;  // Bits 9:7
    UINT32 RxBiasCtl                               :  4;  // Bits 13:10
    INT32  OdtDelay                                :  5;  // Bits 18:14
    UINT32 OdtDuration                             :  3;  // Bits 21:19
    INT32  SenseAmpDelay                           :  5;  // Bits 26:22
    UINT32 SenseAmpDuration                        :  3;  // Bits 29:27
    UINT32 CBEnAmp2                                :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DDRCRDATACONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 RxStaggerCtl                            :  5;  // Bits 4:0
    UINT32 ForceBiasOn                             :  1;  // Bits 5:5
    UINT32 ForceRxOn                               :  1;  // Bits 6:6
    UINT32 DisableDqsOdtStatic                     :  1;  // Bits 7:7
    UINT32 LpDdrLongOdtEn                          :  1;  // Bits 8:8
    UINT32 RxRankMuxDelay                          :  4;  // Bits 12:9
    UINT32 RxClkStgNum                             :  5;  // Bits 17:13
    UINT32 WlLongDelEn                             :  1;  // Bits 18:18
    UINT32 EnableVrefPwrDn                         :  1;  // Bits 19:19
    UINT32 Ddr4Mode                                :  1;  // Bits 20:20
    UINT32 EnVddqOdt                               :  1;  // Bits 21:21
    UINT32 EnVttOdt                                :  1;  // Bits 22:22
    UINT32 EnConstZEqTx                            :  1;  // Bits 23:23
    UINT32 TxEqDis                                 :  1;  // Bits 24:24
    UINT32 RxVrefProgMFC                           :  1;  // Bits 25:25
    UINT32 Cben                                    :  3;  // Bits 28:26
    UINT32 TxDeskewDisable                         :  1;  // Bits 29:29
    UINT32 RxDeskewDisable                         :  1;  // Bits 30:30
    UINT32 DqSlewDlyByPass                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DDRCRDATACONTROL2_STRUCT;

typedef union {
  struct {
    INT32  RcvEnOffset                             :  6;  // Bits 5:0
    INT32  RxDqsOffset                             :  7;  // Bits 12:6
    INT32  TxDqOffset                              :  6;  // Bits 18:13
    INT32  TxDqsOffset                             :  6;  // Bits 24:19
    INT32  VrefOffset                              :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DDRCRDATAOFFSETTRAIN_STRUCT;

typedef union {
  struct {
    UINT32 RxTrainingMode                          :  1;  // Bits 0:0
    UINT32 WLTrainingMode                          :  1;  // Bits 1:1
    UINT32 RLTrainingMode                          :  1;  // Bits 2:2
    UINT32 SenseampTrainingMode                    :  1;  // Bits 3:3
    UINT32 TxOn                                    :  1;  // Bits 4:4
    UINT32 LPDDR_Mode                              :  1;  // Bits 5:5
    UINT32 RxPiOn                                  :  1;  // Bits 6:6
    UINT32 TxPiOn                                  :  1;  // Bits 7:7
    UINT32 InternalClocksOn                        :  1;  // Bits 8:8
    UINT32 RepeaterClocksOn                        :  1;  // Bits 9:9
    UINT32 TxDisable                               :  1;  // Bits 10:10
    UINT32 RxDisable                               :  1;  // Bits 11:11
    UINT32 Spare2                                  :  1;  // Bits 12:12
    UINT32 RxDqsCtle                               :  2;  // Bits 14:13
    UINT32 RxReadPointer                           :  4;  // Bits 18:15
    UINT32 xover_mindelay_ctl                      :  2;  // Bits 20:19
    UINT32 DQDQSLowsupEn                           :  1;  // Bits 21:21
    UINT32 DqTcoBypass                             :  1;  // Bits 22:22
    UINT32 viewQclkDis                             :  1;  // Bits 23:23
    UINT32 ForceOdtOn                              :  1;  // Bits 24:24
    UINT32 OdtSampOff                              :  1;  // Bits 25:25
    UINT32 DisableOdtStatic                        :  1;  // Bits 26:26
    UINT32 DdrCRForceODTOn                         :  1;  // Bits 27:27
    UINT32 spare                                   :  1;  // Bits 28:28
    UINT32 LongOdtR2W                              :  1;  // Bits 29:29
    UINT32 OdtSampExtendEn                         :  1;  // Bits 30:30
    UINT32 EarlyRleakEn                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DDRCRDATACONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 TxDqsRankMuxDelay                       :  4;  // Bits 3:0
    UINT32 TxDqsRankMuxDelay_2nd_stage_offset      :  2;  // Bits 5:4
    UINT32 ForceDqsOnQuickOdtOff                   :  1;  // Bits 6:6
    UINT32 Strong2WeakOnDqsOdt                     :  1;  // Bits 7:7
    INT32  DqsOdtDelay                             :  6;  // Bits 13:8
    UINT32 vrefinten_atckepwrdown                  :  1;  // Bits 14:14
    UINT32 DqsOdtSampExtendEn                      :  1;  // Bits 15:15
    UINT32 DqsOdtDuration                          :  3;  // Bits 18:16
    UINT32 AllowOvrdOdtOnAsyncDrv                  :  1;  // Bits 19:19
    UINT32 LeakerComp                              :  3;  // Bits 22:20
    UINT32 rxclkstgnummsb                          :  1;  // Bits 23:23
    UINT32 NomPgDis                                :  1;  // Bits 24:24
    UINT32 rcven_four_cycle_fill                   :  1;  // Bits 25:25
    UINT32 StrongWkLeaker                          :  4;  // Bits 29:26
    UINT32 CBEnAmp1                                :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DDRCRDATACONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 leakerwithtxanalogen                    :  1;  // Bits 0:0
    UINT32 glbdrv_clkgate_enable                   :  1;  // Bits 1:1
    UINT32 biasrcomp                               :  3;  // Bits 4:2
    UINT32 txdeskewcal                             :  1;  // Bits 5:5
    UINT32 txdeskewdqscodesel                      :  1;  // Bits 6:6
    UINT32 rxdeskewcal                             :  1;  // Bits 7:7
    UINT32 rxdeskewdqscodesel                      :  1;  // Bits 8:8
    UINT32 DisPanicDrv                             :  2;  // Bits 10:9
    UINT32 dllnbiassel                             :  1;  // Bits 11:11
    UINT32 rxsel                                   :  1;  // Bits 12:12
    UINT32 ampoffseten                             :  1;  // Bits 13:13
    UINT32 LpDdr4Mode                              :  1;  // Bits 14:14
    UINT32 lpddr4wrlongpreambleen                  :  1;  // Bits 15:15
    UINT32 ddr4wrlongpreambleen                    :  1;  // Bits 16:16
    UINT32 VssODTSingleSegEn                       :  1;  // Bits 17:17
    UINT32 VssODTEn                                :  1;  // Bits 18:18
    UINT32 dqsodtdowncompoffset                    :  5;  // Bits 23:19
    UINT32 dqsodtupcompoffset                      :  5;  // Bits 28:24
    UINT32 spare2                                  :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DDRCRDATACONTROL4_STRUCT;

typedef union {
  struct {
    UINT32 RxVref                                  :  8;  // Bits 7:0
    UINT32 ddrcrdqsmaskcnten                       :  1;  // Bits 8:8
    UINT32 ddrcrnumofpulses                        :  2;  // Bits 10:9
    UINT32 ddrcrmaskcntpulsenumstart               :  4;  // Bits 14:11
    UINT32 Lp4xVoltageSelect                       :  1;  // Bits 15:15
    UINT32 DdrDqOvrdModeEn                         :  8;  // Bits 23:16
    UINT32 DdrDqOvrdData                           :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DDRCRDATACONTROL5_STRUCT;

typedef union {
  struct {
    UINT32 RankOvrd                                :  1;  // Bits 0:0
    UINT32 RankValue                               :  2;  // Bits 2:1
    UINT32 Gear1                                   :  1;  // Bits 3:3
    UINT32 RxDqsAmpOffset                          :  5;  // Bits 8:4
    UINT32 fast_dqsoutputenable                    :  1;  // Bits 9:9
    UINT32 tx_clock_on_with_txanalogen             :  1;  // Bits 10:10
    UINT32 local_gate_d0tx                         :  1;  // Bits 11:11
    UINT32 strongwkleakermsb                       :  2;  // Bits 13:12
    UINT32 forcedqsponwithleaker                   :  1;  // Bits 14:14
    UINT32 forcedqsnonwithleaker                   :  1;  // Bits 15:15
    UINT32 RxBiasCtl1                              :  8;  // Bits 23:16
    UINT32 ForceDqsPon                             :  1;  // Bits 24:24
    UINT32 ForceDqsNon                             :  1;  // Bits 25:25
    UINT32 sdll_picb                               :  3;  // Bits 28:26
    UINT32 d0_picb                                 :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DDRCRDATACONTROL6_STRUCT;

typedef union {
  struct {
    UINT32 DqsDfeDlyRank0                          :  6;  // Bits 5:0
    UINT32 DqsDfeDlyRank1                          :  6;  // Bits 11:6
    UINT32 DqsDfeDlyRank2                          :  6;  // Bits 17:12
    UINT32 DqsDfeDlyRank3                          :  6;  // Bits 23:18
    UINT32 sdll_bw_ctrl                            :  4;  // Bits 27:24
    UINT32 d0_bw_ctrl                              :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DDRCRDATACONTROL7_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DELTADQSRANK0_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DELTADQSRANK1_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DELTADQSRANK2_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DELTADQSRANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_RXCONTROL3RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_RXCONTROL3RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_RXCONTROL3RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_RXCONTROL3RANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_TXPERBITHIRANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_TXPERBITHIRANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_TXPERBITHIRANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_TXPERBITHIRANK3_STRUCT;

typedef union {
  struct {
    UINT32 GVPointG1                               :  1;  // Bits 0:0
    UINT32 GVPointG2                               :  2;  // Bits 2:1
    UINT32 ReplicaOffsetUse                        :  1;  // Bits 3:3
    UINT32 VTCompOffsetUse                         :  2;  // Bits 5:4
    UINT32 ExtOffset                               :  7;  // Bits 12:6
    UINT32 BiasOffset                              :  15;  // Bits 27:13
    UINT32 ActiveRanks                             :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATACONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 DccCodeOvrd                             :  6;  // Bits 5:0
    UINT32 RepDccAipCb                             :  2;  // Bits 7:6
    UINT32 DccPtrOvrd                              :  4;  // Bits 11:8
    UINT32 RnkPtrOvrd                              :  2;  // Bits 13:12
    UINT32 DcdDigEnOvrd                            :  1;  // Bits 14:14
    UINT32 DcdAnaEnOvrd                            :  1;  // Bits 15:15
    UINT32 DcdWindow                               :  15;  // Bits 30:16
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATACONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 StartBinCode                            :  6;  // Bits 5:0
    UINT32 CodePtrStartBit                         :  3;  // Bits 8:6
    UINT32 DccTrshOld                              :  13;  // Bits 21:9
    UINT32 DcdCntsStartDiff                        :  5;  // Bits 26:22
    UINT32 ClkGateDisable                          :  1;  // Bits 27:27
    UINT32 DccDataViewSelect0                      :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATACONTROL2_STRUCT;

typedef union {
  struct {
    UINT32 ActiveDccRank0                          :  11;  // Bits 10:0
    UINT32 ActiveDccRank1                          :  9;  // Bits 19:11
    UINT32 ActiveDccRank2                          :  9;  // Bits 28:20
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATACONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 ActiveDccRank3                          :  9;  // Bits 8:0
    UINT32 Spare                                   :  1;  // Bits 9:9
    UINT32 ReplicaPrev_GVp0                        :  6;  // Bits 15:10
    UINT32 ReplicaPrev_GVp1                        :  6;  // Bits 21:16
    UINT32 ReplicaPrev_GVp2                        :  6;  // Bits 27:22
    UINT32 DccDataViewSelect1                      :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATACONTROL4_STRUCT;

typedef union {
  struct {
    UINT32 Spare                                   :  2;  // Bits 1:0
    UINT32 vtcompoffsetmsgwren                     :  1;  // Bits 2:2
    UINT32 ReplicaPrev_GVp3                        :  6;  // Bits 8:3
    UINT32 BubbleCntVal                            :  5;  // Bits 13:9
    UINT32 DeterministicSyncVal                    :  6;  // Bits 19:14
    UINT32 DeterministicCntVal                     :  11;  // Bits 30:20
    UINT32 DeterministicMode                       :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATACONTROL5_STRUCT;

typedef union {
  struct {
    UINT32 Rank0DccDone                            :  11;  // Bits 10:0
    UINT32 Rank1DccDone                            :  9;  // Bits 19:11
    UINT32 Rank2DccDone                            :  9;  // Bits 28:20
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATATRAINSTATUS0_STRUCT;

typedef union {
  struct {
    UINT32 Rank3DccDone                            :  9;  // Bits 8:0
    UINT32 Spare0                                  :  1;  // Bits 9:9
    UINT32 CntDone                                 :  1;  // Bits 10:10
    UINT32 Dcd_O_Cnt                               :  15;  // Bits 25:11
    UINT32 Spare1                                  :  1;  // Bits 26:26
    UINT32 BinFsmCurrState                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATATRAINSTATUS1_STRUCT;

typedef union {
  struct {
    UINT32 AuxCnt                                  :  16;  // Bits 15:0
    UINT32 ReplicaOffset                           :  7;  // Bits 22:16
    UINT32 VTCompOffset                            :  7;  // Bits 29:23
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATATRAINSTATUS2_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  11;  // Bits 10:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 27:11
    UINT32 Spare                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATATRAINERRSTATUSRANK0_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  9;  // Bits 8:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 25:9
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATATRAINERRSTATUSRANK1_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  9;  // Bits 8:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 25:9
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATATRAINERRSTATUSRANK2_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  9;  // Bits 8:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 25:9
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATATRAINERRSTATUSRANK3_STRUCT;

typedef union {
  struct {
    UINT32 ReplicaTrain_GVp0                       :  6;  // Bits 5:0
    UINT32 ReplicaTrain_GVp1                       :  6;  // Bits 11:6
    UINT32 ReplicaTrain_GVp2                       :  6;  // Bits 17:12
    UINT32 ReplicaTrain_GVp3                       :  6;  // Bits 23:18
    UINT32 ReplicaOffsetPrev                       :  7;  // Bits 30:24
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATATRAINREPLICA0_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATATRAINVAL0RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATATRAINVAL0RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATATRAINVAL0RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATATRAINVAL0RANK3_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 ReplicaShadowDccVal                     :  6;  // Bits 29:24
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATATRAINVAL1RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 spare2                                  :  2;  // Bits 25:24
    UINT32 binfsmsteptosavecnts                    :  3;  // Bits 28:26
    UINT32 savecntsatchosenbinstep                 :  1;  // Bits 29:29
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATATRAINVAL1RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 Spare                                   :  6;  // Bits 29:24
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATATRAINVAL1RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 Spare                                   :  6;  // Bits 29:24
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATATRAINVAL1RANK3_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_0                        :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_4                        :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_8                        :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_12                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_16                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATADCCPILUT0_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_20                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_24                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_28                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_32                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_36                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATADCCPILUT1_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_40                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_44                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_48                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_52                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_56                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATADCCPILUT2_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_60                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_64                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_68                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_72                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_76                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATADCCPILUT3_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_80                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_84                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_88                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_92                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_96                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATADCCPILUT4_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_100                      :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_104                      :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_108                      :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_112                      :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_116                      :  6;  // Bits 29:24
    UINT32 DccPiAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATADCCPILUT5_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_120                      :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_124                      :  6;  // Bits 11:6
    UINT32 DccPiStaticCode                         :  6;  // Bits 17:12
    UINT32 DccPiStaticCodeGear1                    :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DCCDATADCCPILUT6_STRUCT;

typedef union {
  struct {
    UINT32 DqTcoCompBit0                           :  6;  // Bits 5:0
    UINT32 DqTcoCompBit1                           :  6;  // Bits 11:6
    UINT32 DqTcoCompBit2                           :  6;  // Bits 17:12
    UINT32 DqTcoCompBit3                           :  6;  // Bits 23:18
    UINT32 DqsNTcoComp                             :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DDRCRDATATCOCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 DqTcoCompBit4                           :  6;  // Bits 5:0
    UINT32 DqTcoCompBit5                           :  6;  // Bits 11:6
    UINT32 DqTcoCompBit6                           :  6;  // Bits 17:12
    UINT32 DqTcoCompBit7                           :  6;  // Bits 23:18
    UINT32 DqsPTcoComp                             :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DDRCRDATATCOCONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit6Rank0                       :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit6Rank1                       :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit7Rank0                       :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit7Rank1                       :  6;  // Bits 23:18
    UINT32 DfeDlyModeRank0                         :  2;  // Bits 25:24
    UINT32 DfeDlyModeRank1                         :  2;  // Bits 27:26
    UINT32 DfeDlyModeRank2                         :  2;  // Bits 29:28
    UINT32 DfeDlyModeRank3                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DDRCRDATADFECONTROL1RANK01_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit6Rank2                       :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit6Rank3                       :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit7Rank2                       :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit7Rank3                       :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DDRCRDATADFECONTROL1RANK23_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DDRCRDATADFECONTROL0RANK0_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DDRCRDATADFECONTROL0RANK1_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DDRCRDATADFECONTROL0RANK2_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7CH1_CR_DDRCRDATADFECONTROL0RANK3_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXCONTROL0RANK0_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXCONTROL0RANK1_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXCONTROL0RANK2_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXCONTROL0RANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXCONTROL1RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXCONTROL1RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXCONTROL1RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXCONTROL1RANK3_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 TxRankMuxDelay                          :  4;  // Bits 29:26
    UINT32 Spare1                                  :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_TXTRAINRANK0_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 TxRankMuxDelay_2nd_stage_offset         :  2;  // Bits 27:26
    UINT32 Spare1                                  :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_TXTRAINRANK1_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 Spare1                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_TXTRAINRANK2_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 Spare1                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_TXTRAINRANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_TXPERBITLOWRANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_TXPERBITLOWRANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_TXPERBITLOWRANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_TXPERBITLOWRANK3_STRUCT;

typedef union {
  struct {
    UINT32 RcompDrvUp                              :  6;  // Bits 5:0
    UINT32 Rsvd                                    :  8;  // Bits 13:6
    UINT32 RcompDrvDown                            :  6;  // Bits 19:14
    UINT32 SlewRateComp                            :  5;  // Bits 24:20
    UINT32 Spare                                   :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RCOMPDATA0_STRUCT;

typedef union {
  struct {
    UINT32 RcompOdtUp                              :  6;  // Bits 5:0
    UINT32 spare                                   :  20;  // Bits 25:6
    UINT32 RcompOdtDown                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RCOMPDATA1_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeCoeffRank0                         :  2;  // Bits 1:0
    UINT32 DqDfeCoeffRank1                         :  2;  // Bits 3:2
    UINT32 DqDfeCoeffRank2                         :  2;  // Bits 5:4
    UINT32 DqDfeCoeffRank3                         :  2;  // Bits 7:6
    UINT32 en_rcvenpre_zero_fill                   :  1;  // Bits 8:8
    UINT32 spare                                   :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRDATACONTROL8_STRUCT;

typedef union {
  struct {
    UINT32 PanicVttUp                              :  8;  // Bits 7:0
    UINT32 PanicVttDn                              :  8;  // Bits 15:8
    UINT32 RcompCmdDn200ohm                        :  6;  // Bits 21:16
    UINT32 Spare                                   :  10;  // Bits 31:22
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RCOMPDATA2_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXCONTROL2RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXCONTROL2RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXCONTROL2RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXCONTROL2RANK3_STRUCT;

typedef union {
  struct {
    UINT32 DataTrainFeedback                       :  9;  // Bits 8:0
    UINT32 Spare                                   :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DATATRAINFEEDBACK_STRUCT;

typedef union {
  struct {
    INT32  DqDrvUpCompOffset                       :  6;  // Bits 5:0
    INT32  DqDrvDownCompOffset                     :  6;  // Bits 11:6
    INT32  DqOdtUpCompOffset                       :  5;  // Bits 16:12
    INT32  DqOdtDownCompOffset                     :  5;  // Bits 21:17
    UINT32 Spare                                   :  5;  // Bits 26:22
    INT32  DqSlewRateCompOffset                    :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 DllWeakLock                             :  1;  // Bits 6:6
    UINT32 SdllSegmentDisable                      :  3;  // Bits 9:7
    UINT32 RxBiasCtl                               :  4;  // Bits 13:10
    INT32  OdtDelay                                :  5;  // Bits 18:14
    UINT32 OdtDuration                             :  3;  // Bits 21:19
    INT32  SenseAmpDelay                           :  5;  // Bits 26:22
    UINT32 SenseAmpDuration                        :  3;  // Bits 29:27
    UINT32 CBEnAmp2                                :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRDATACONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 RxStaggerCtl                            :  5;  // Bits 4:0
    UINT32 ForceBiasOn                             :  1;  // Bits 5:5
    UINT32 ForceRxOn                               :  1;  // Bits 6:6
    UINT32 DisableDqsOdtStatic                     :  1;  // Bits 7:7
    UINT32 LpDdrLongOdtEn                          :  1;  // Bits 8:8
    UINT32 RxRankMuxDelay                          :  4;  // Bits 12:9
    UINT32 RxClkStgNum                             :  5;  // Bits 17:13
    UINT32 WlLongDelEn                             :  1;  // Bits 18:18
    UINT32 EnableVrefPwrDn                         :  1;  // Bits 19:19
    UINT32 Ddr4Mode                                :  1;  // Bits 20:20
    UINT32 EnVddqOdt                               :  1;  // Bits 21:21
    UINT32 EnVttOdt                                :  1;  // Bits 22:22
    UINT32 EnConstZEqTx                            :  1;  // Bits 23:23
    UINT32 TxEqDis                                 :  1;  // Bits 24:24
    UINT32 RxVrefProgMFC                           :  1;  // Bits 25:25
    UINT32 Cben                                    :  3;  // Bits 28:26
    UINT32 TxDeskewDisable                         :  1;  // Bits 29:29
    UINT32 RxDeskewDisable                         :  1;  // Bits 30:30
    UINT32 DqSlewDlyByPass                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRDATACONTROL2_STRUCT;

typedef union {
  struct {
    INT32  RcvEnOffset                             :  6;  // Bits 5:0
    INT32  RxDqsOffset                             :  7;  // Bits 12:6
    INT32  TxDqOffset                              :  6;  // Bits 18:13
    INT32  TxDqsOffset                             :  6;  // Bits 24:19
    INT32  VrefOffset                              :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRDATAOFFSETTRAIN_STRUCT;

typedef union {
  struct {
    UINT32 RxTrainingMode                          :  1;  // Bits 0:0
    UINT32 WLTrainingMode                          :  1;  // Bits 1:1
    UINT32 RLTrainingMode                          :  1;  // Bits 2:2
    UINT32 SenseampTrainingMode                    :  1;  // Bits 3:3
    UINT32 TxOn                                    :  1;  // Bits 4:4
    UINT32 LPDDR_Mode                              :  1;  // Bits 5:5
    UINT32 RxPiOn                                  :  1;  // Bits 6:6
    UINT32 TxPiOn                                  :  1;  // Bits 7:7
    UINT32 InternalClocksOn                        :  1;  // Bits 8:8
    UINT32 RepeaterClocksOn                        :  1;  // Bits 9:9
    UINT32 TxDisable                               :  1;  // Bits 10:10
    UINT32 RxDisable                               :  1;  // Bits 11:11
    UINT32 Spare2                                  :  1;  // Bits 12:12
    UINT32 RxDqsCtle                               :  2;  // Bits 14:13
    UINT32 RxReadPointer                           :  4;  // Bits 18:15
    UINT32 xover_mindelay_ctl                      :  2;  // Bits 20:19
    UINT32 DQDQSLowsupEn                           :  1;  // Bits 21:21
    UINT32 DqTcoBypass                             :  1;  // Bits 22:22
    UINT32 viewQclkDis                             :  1;  // Bits 23:23
    UINT32 ForceOdtOn                              :  1;  // Bits 24:24
    UINT32 OdtSampOff                              :  1;  // Bits 25:25
    UINT32 DisableOdtStatic                        :  1;  // Bits 26:26
    UINT32 DdrCRForceODTOn                         :  1;  // Bits 27:27
    UINT32 spare                                   :  1;  // Bits 28:28
    UINT32 LongOdtR2W                              :  1;  // Bits 29:29
    UINT32 OdtSampExtendEn                         :  1;  // Bits 30:30
    UINT32 EarlyRleakEn                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRDATACONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 TxDqsRankMuxDelay                       :  4;  // Bits 3:0
    UINT32 TxDqsRankMuxDelay_2nd_stage_offset      :  2;  // Bits 5:4
    UINT32 ForceDqsOnQuickOdtOff                   :  1;  // Bits 6:6
    UINT32 Strong2WeakOnDqsOdt                     :  1;  // Bits 7:7
    INT32  DqsOdtDelay                             :  6;  // Bits 13:8
    UINT32 vrefinten_atckepwrdown                  :  1;  // Bits 14:14
    UINT32 DqsOdtSampExtendEn                      :  1;  // Bits 15:15
    UINT32 DqsOdtDuration                          :  3;  // Bits 18:16
    UINT32 AllowOvrdOdtOnAsyncDrv                  :  1;  // Bits 19:19
    UINT32 LeakerComp                              :  3;  // Bits 22:20
    UINT32 rxclkstgnummsb                          :  1;  // Bits 23:23
    UINT32 NomPgDis                                :  1;  // Bits 24:24
    UINT32 rcven_four_cycle_fill                   :  1;  // Bits 25:25
    UINT32 StrongWkLeaker                          :  4;  // Bits 29:26
    UINT32 CBEnAmp1                                :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRDATACONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 leakerwithtxanalogen                    :  1;  // Bits 0:0
    UINT32 glbdrv_clkgate_enable                   :  1;  // Bits 1:1
    UINT32 biasrcomp                               :  3;  // Bits 4:2
    UINT32 txdeskewcal                             :  1;  // Bits 5:5
    UINT32 txdeskewdqscodesel                      :  1;  // Bits 6:6
    UINT32 rxdeskewcal                             :  1;  // Bits 7:7
    UINT32 rxdeskewdqscodesel                      :  1;  // Bits 8:8
    UINT32 DisPanicDrv                             :  2;  // Bits 10:9
    UINT32 dllnbiassel                             :  1;  // Bits 11:11
    UINT32 rxsel                                   :  1;  // Bits 12:12
    UINT32 ampoffseten                             :  1;  // Bits 13:13
    UINT32 LpDdr4Mode                              :  1;  // Bits 14:14
    UINT32 lpddr4wrlongpreambleen                  :  1;  // Bits 15:15
    UINT32 ddr4wrlongpreambleen                    :  1;  // Bits 16:16
    UINT32 VssODTSingleSegEn                       :  1;  // Bits 17:17
    UINT32 VssODTEn                                :  1;  // Bits 18:18
    UINT32 dqsodtdowncompoffset                    :  5;  // Bits 23:19
    UINT32 dqsodtupcompoffset                      :  5;  // Bits 28:24
    UINT32 spare2                                  :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRDATACONTROL4_STRUCT;

typedef union {
  struct {
    UINT32 RxVref                                  :  8;  // Bits 7:0
    UINT32 ddrcrdqsmaskcnten                       :  1;  // Bits 8:8
    UINT32 ddrcrnumofpulses                        :  2;  // Bits 10:9
    UINT32 ddrcrmaskcntpulsenumstart               :  4;  // Bits 14:11
    UINT32 Lp4xVoltageSelect                       :  1;  // Bits 15:15
    UINT32 DdrDqOvrdModeEn                         :  8;  // Bits 23:16
    UINT32 DdrDqOvrdData                           :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRDATACONTROL5_STRUCT;

typedef union {
  struct {
    UINT32 RankOvrd                                :  1;  // Bits 0:0
    UINT32 RankValue                               :  2;  // Bits 2:1
    UINT32 Gear1                                   :  1;  // Bits 3:3
    UINT32 RxDqsAmpOffset                          :  5;  // Bits 8:4
    UINT32 fast_dqsoutputenable                    :  1;  // Bits 9:9
    UINT32 tx_clock_on_with_txanalogen             :  1;  // Bits 10:10
    UINT32 local_gate_d0tx                         :  1;  // Bits 11:11
    UINT32 strongwkleakermsb                       :  2;  // Bits 13:12
    UINT32 forcedqsponwithleaker                   :  1;  // Bits 14:14
    UINT32 forcedqsnonwithleaker                   :  1;  // Bits 15:15
    UINT32 RxBiasCtl1                              :  8;  // Bits 23:16
    UINT32 ForceDqsPon                             :  1;  // Bits 24:24
    UINT32 ForceDqsNon                             :  1;  // Bits 25:25
    UINT32 sdll_picb                               :  3;  // Bits 28:26
    UINT32 d0_picb                                 :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRDATACONTROL6_STRUCT;

typedef union {
  struct {
    UINT32 DqsDfeDlyRank0                          :  6;  // Bits 5:0
    UINT32 DqsDfeDlyRank1                          :  6;  // Bits 11:6
    UINT32 DqsDfeDlyRank2                          :  6;  // Bits 17:12
    UINT32 DqsDfeDlyRank3                          :  6;  // Bits 23:18
    UINT32 sdll_bw_ctrl                            :  4;  // Bits 27:24
    UINT32 d0_bw_ctrl                              :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRDATACONTROL7_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DELTADQSRANK0_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DELTADQSRANK1_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DELTADQSRANK2_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DELTADQSRANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXCONTROL3RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXCONTROL3RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXCONTROL3RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_RXCONTROL3RANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_TXPERBITHIRANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_TXPERBITHIRANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_TXPERBITHIRANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_TXPERBITHIRANK3_STRUCT;

typedef union {
  struct {
    UINT32 GVPointG1                               :  1;  // Bits 0:0
    UINT32 GVPointG2                               :  2;  // Bits 2:1
    UINT32 ReplicaOffsetUse                        :  1;  // Bits 3:3
    UINT32 VTCompOffsetUse                         :  2;  // Bits 5:4
    UINT32 ExtOffset                               :  7;  // Bits 12:6
    UINT32 BiasOffset                              :  15;  // Bits 27:13
    UINT32 ActiveRanks                             :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATACONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 DccCodeOvrd                             :  6;  // Bits 5:0
    UINT32 RepDccAipCb                             :  2;  // Bits 7:6
    UINT32 DccPtrOvrd                              :  4;  // Bits 11:8
    UINT32 RnkPtrOvrd                              :  2;  // Bits 13:12
    UINT32 DcdDigEnOvrd                            :  1;  // Bits 14:14
    UINT32 DcdAnaEnOvrd                            :  1;  // Bits 15:15
    UINT32 DcdWindow                               :  15;  // Bits 30:16
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATACONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 StartBinCode                            :  6;  // Bits 5:0
    UINT32 CodePtrStartBit                         :  3;  // Bits 8:6
    UINT32 DccTrshOld                              :  13;  // Bits 21:9
    UINT32 DcdCntsStartDiff                        :  5;  // Bits 26:22
    UINT32 ClkGateDisable                          :  1;  // Bits 27:27
    UINT32 DccDataViewSelect0                      :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATACONTROL2_STRUCT;

typedef union {
  struct {
    UINT32 ActiveDccRank0                          :  11;  // Bits 10:0
    UINT32 ActiveDccRank1                          :  9;  // Bits 19:11
    UINT32 ActiveDccRank2                          :  9;  // Bits 28:20
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATACONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 ActiveDccRank3                          :  9;  // Bits 8:0
    UINT32 Spare                                   :  1;  // Bits 9:9
    UINT32 ReplicaPrev_GVp0                        :  6;  // Bits 15:10
    UINT32 ReplicaPrev_GVp1                        :  6;  // Bits 21:16
    UINT32 ReplicaPrev_GVp2                        :  6;  // Bits 27:22
    UINT32 DccDataViewSelect1                      :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATACONTROL4_STRUCT;

typedef union {
  struct {
    UINT32 Spare                                   :  2;  // Bits 1:0
    UINT32 vtcompoffsetmsgwren                     :  1;  // Bits 2:2
    UINT32 ReplicaPrev_GVp3                        :  6;  // Bits 8:3
    UINT32 BubbleCntVal                            :  5;  // Bits 13:9
    UINT32 DeterministicSyncVal                    :  6;  // Bits 19:14
    UINT32 DeterministicCntVal                     :  11;  // Bits 30:20
    UINT32 DeterministicMode                       :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATACONTROL5_STRUCT;

typedef union {
  struct {
    UINT32 Rank0DccDone                            :  11;  // Bits 10:0
    UINT32 Rank1DccDone                            :  9;  // Bits 19:11
    UINT32 Rank2DccDone                            :  9;  // Bits 28:20
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATATRAINSTATUS0_STRUCT;

typedef union {
  struct {
    UINT32 Rank3DccDone                            :  9;  // Bits 8:0
    UINT32 Spare0                                  :  1;  // Bits 9:9
    UINT32 CntDone                                 :  1;  // Bits 10:10
    UINT32 Dcd_O_Cnt                               :  15;  // Bits 25:11
    UINT32 Spare1                                  :  1;  // Bits 26:26
    UINT32 BinFsmCurrState                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATATRAINSTATUS1_STRUCT;

typedef union {
  struct {
    UINT32 AuxCnt                                  :  16;  // Bits 15:0
    UINT32 ReplicaOffset                           :  7;  // Bits 22:16
    UINT32 VTCompOffset                            :  7;  // Bits 29:23
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATATRAINSTATUS2_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  11;  // Bits 10:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 27:11
    UINT32 Spare                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATATRAINERRSTATUSRANK0_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  9;  // Bits 8:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 25:9
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATATRAINERRSTATUSRANK1_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  9;  // Bits 8:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 25:9
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATATRAINERRSTATUSRANK2_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  9;  // Bits 8:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 25:9
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATATRAINERRSTATUSRANK3_STRUCT;

typedef union {
  struct {
    UINT32 ReplicaTrain_GVp0                       :  6;  // Bits 5:0
    UINT32 ReplicaTrain_GVp1                       :  6;  // Bits 11:6
    UINT32 ReplicaTrain_GVp2                       :  6;  // Bits 17:12
    UINT32 ReplicaTrain_GVp3                       :  6;  // Bits 23:18
    UINT32 ReplicaOffsetPrev                       :  7;  // Bits 30:24
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATATRAINREPLICA0_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATATRAINVAL0RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATATRAINVAL0RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATATRAINVAL0RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATATRAINVAL0RANK3_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 ReplicaShadowDccVal                     :  6;  // Bits 29:24
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATATRAINVAL1RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 spare2                                  :  2;  // Bits 25:24
    UINT32 binfsmsteptosavecnts                    :  3;  // Bits 28:26
    UINT32 savecntsatchosenbinstep                 :  1;  // Bits 29:29
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATATRAINVAL1RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 Spare                                   :  6;  // Bits 29:24
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATATRAINVAL1RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 Spare                                   :  6;  // Bits 29:24
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATATRAINVAL1RANK3_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_0                        :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_4                        :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_8                        :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_12                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_16                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATADCCPILUT0_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_20                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_24                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_28                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_32                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_36                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATADCCPILUT1_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_40                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_44                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_48                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_52                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_56                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATADCCPILUT2_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_60                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_64                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_68                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_72                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_76                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATADCCPILUT3_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_80                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_84                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_88                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_92                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_96                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATADCCPILUT4_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_100                      :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_104                      :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_108                      :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_112                      :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_116                      :  6;  // Bits 29:24
    UINT32 DccPiAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATADCCPILUT5_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_120                      :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_124                      :  6;  // Bits 11:6
    UINT32 DccPiStaticCode                         :  6;  // Bits 17:12
    UINT32 DccPiStaticCodeGear1                    :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DCCDATADCCPILUT6_STRUCT;

typedef union {
  struct {
    UINT32 DqTcoCompBit0                           :  6;  // Bits 5:0
    UINT32 DqTcoCompBit1                           :  6;  // Bits 11:6
    UINT32 DqTcoCompBit2                           :  6;  // Bits 17:12
    UINT32 DqTcoCompBit3                           :  6;  // Bits 23:18
    UINT32 DqsNTcoComp                             :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRDATATCOCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 DqTcoCompBit4                           :  6;  // Bits 5:0
    UINT32 DqTcoCompBit5                           :  6;  // Bits 11:6
    UINT32 DqTcoCompBit6                           :  6;  // Bits 17:12
    UINT32 DqTcoCompBit7                           :  6;  // Bits 23:18
    UINT32 DqsPTcoComp                             :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRDATATCOCONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit6Rank0                       :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit6Rank1                       :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit7Rank0                       :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit7Rank1                       :  6;  // Bits 23:18
    UINT32 DfeDlyModeRank0                         :  2;  // Bits 25:24
    UINT32 DfeDlyModeRank1                         :  2;  // Bits 27:26
    UINT32 DfeDlyModeRank2                         :  2;  // Bits 29:28
    UINT32 DfeDlyModeRank3                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRDATADFECONTROL1RANK01_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit6Rank2                       :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit6Rank3                       :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit7Rank2                       :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit7Rank3                       :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRDATADFECONTROL1RANK23_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRDATADFECONTROL0RANK0_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRDATADFECONTROL0RANK1_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRDATADFECONTROL0RANK2_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH0_CR_DDRCRDATADFECONTROL0RANK3_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXCONTROL0RANK0_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXCONTROL0RANK1_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXCONTROL0RANK2_STRUCT;

typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPPi                                :  7;  // Bits 17:11
    UINT32 RxEq                                    :  7;  // Bits 24:18
    UINT32 RxDqsNPi                                :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXCONTROL0RANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXCONTROL1RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXCONTROL1RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXCONTROL1RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane3PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane2PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane1PerBitDeskew                       :  6;  // Bits 17:12
    UINT32 Lane0PerBitDeskew                       :  6;  // Bits 23:18
    UINT32 DqsDfeCoeff                             :  2;  // Bits 25:24
    UINT32 DqDfeDlyBit0                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXCONTROL1RANK3_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 TxRankMuxDelay                          :  4;  // Bits 29:26
    UINT32 Spare1                                  :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_TXTRAINRANK0_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 TxRankMuxDelay_2nd_stage_offset         :  2;  // Bits 27:26
    UINT32 Spare1                                  :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_TXTRAINRANK1_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 Spare1                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_TXTRAINRANK2_STRUCT;

typedef union {
  struct {
    UINT32 TxDqDelay                               :  10;  // Bits 9:0
    UINT32 TxDqsDelay                              :  10;  // Bits 19:10
    UINT32 TxEqualization                          :  6;  // Bits 25:20
    UINT32 Spare1                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_TXTRAINRANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_TXPERBITLOWRANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_TXPERBITLOWRANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_TXPERBITLOWRANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane0                                   :  6;  // Bits 5:0
    UINT32 Lane1                                   :  6;  // Bits 11:6
    UINT32 Lane2                                   :  6;  // Bits 17:12
    UINT32 Lane3                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_TXPERBITLOWRANK3_STRUCT;

typedef union {
  struct {
    UINT32 RcompDrvUp                              :  6;  // Bits 5:0
    UINT32 Rsvd                                    :  8;  // Bits 13:6
    UINT32 RcompDrvDown                            :  6;  // Bits 19:14
    UINT32 SlewRateComp                            :  5;  // Bits 24:20
    UINT32 Spare                                   :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RCOMPDATA0_STRUCT;

typedef union {
  struct {
    UINT32 RcompOdtUp                              :  6;  // Bits 5:0
    UINT32 spare                                   :  20;  // Bits 25:6
    UINT32 RcompOdtDown                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RCOMPDATA1_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeCoeffRank0                         :  2;  // Bits 1:0
    UINT32 DqDfeCoeffRank1                         :  2;  // Bits 3:2
    UINT32 DqDfeCoeffRank2                         :  2;  // Bits 5:4
    UINT32 DqDfeCoeffRank3                         :  2;  // Bits 7:6
    UINT32 en_rcvenpre_zero_fill                   :  1;  // Bits 8:8
    UINT32 spare                                   :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRDATACONTROL8_STRUCT;

typedef union {
  struct {
    UINT32 PanicVttUp                              :  8;  // Bits 7:0
    UINT32 PanicVttDn                              :  8;  // Bits 15:8
    UINT32 RcompCmdDn200ohm                        :  6;  // Bits 21:16
    UINT32 Spare                                   :  10;  // Bits 31:22
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RCOMPDATA2_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXCONTROL2RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXCONTROL2RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXCONTROL2RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane4PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane5PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane0RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane1RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane2RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane3RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXCONTROL2RANK3_STRUCT;

typedef union {
  struct {
    UINT32 DataTrainFeedback                       :  9;  // Bits 8:0
    UINT32 Spare                                   :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DATATRAINFEEDBACK_STRUCT;

typedef union {
  struct {
    INT32  DqDrvUpCompOffset                       :  6;  // Bits 5:0
    INT32  DqDrvDownCompOffset                     :  6;  // Bits 11:6
    INT32  DqOdtUpCompOffset                       :  5;  // Bits 16:12
    INT32  DqOdtDownCompOffset                     :  5;  // Bits 21:17
    UINT32 Spare                                   :  5;  // Bits 26:22
    INT32  DqSlewRateCompOffset                    :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRDATAOFFSETCOMP_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 DllWeakLock                             :  1;  // Bits 6:6
    UINT32 SdllSegmentDisable                      :  3;  // Bits 9:7
    UINT32 RxBiasCtl                               :  4;  // Bits 13:10
    INT32  OdtDelay                                :  5;  // Bits 18:14
    UINT32 OdtDuration                             :  3;  // Bits 21:19
    INT32  SenseAmpDelay                           :  5;  // Bits 26:22
    UINT32 SenseAmpDuration                        :  3;  // Bits 29:27
    UINT32 CBEnAmp2                                :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRDATACONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 RxStaggerCtl                            :  5;  // Bits 4:0
    UINT32 ForceBiasOn                             :  1;  // Bits 5:5
    UINT32 ForceRxOn                               :  1;  // Bits 6:6
    UINT32 DisableDqsOdtStatic                     :  1;  // Bits 7:7
    UINT32 LpDdrLongOdtEn                          :  1;  // Bits 8:8
    UINT32 RxRankMuxDelay                          :  4;  // Bits 12:9
    UINT32 RxClkStgNum                             :  5;  // Bits 17:13
    UINT32 WlLongDelEn                             :  1;  // Bits 18:18
    UINT32 EnableVrefPwrDn                         :  1;  // Bits 19:19
    UINT32 Ddr4Mode                                :  1;  // Bits 20:20
    UINT32 EnVddqOdt                               :  1;  // Bits 21:21
    UINT32 EnVttOdt                                :  1;  // Bits 22:22
    UINT32 EnConstZEqTx                            :  1;  // Bits 23:23
    UINT32 TxEqDis                                 :  1;  // Bits 24:24
    UINT32 RxVrefProgMFC                           :  1;  // Bits 25:25
    UINT32 Cben                                    :  3;  // Bits 28:26
    UINT32 TxDeskewDisable                         :  1;  // Bits 29:29
    UINT32 RxDeskewDisable                         :  1;  // Bits 30:30
    UINT32 DqSlewDlyByPass                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRDATACONTROL2_STRUCT;

typedef union {
  struct {
    INT32  RcvEnOffset                             :  6;  // Bits 5:0
    INT32  RxDqsOffset                             :  7;  // Bits 12:6
    INT32  TxDqOffset                              :  6;  // Bits 18:13
    INT32  TxDqsOffset                             :  6;  // Bits 24:19
    INT32  VrefOffset                              :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRDATAOFFSETTRAIN_STRUCT;

typedef union {
  struct {
    UINT32 RxTrainingMode                          :  1;  // Bits 0:0
    UINT32 WLTrainingMode                          :  1;  // Bits 1:1
    UINT32 RLTrainingMode                          :  1;  // Bits 2:2
    UINT32 SenseampTrainingMode                    :  1;  // Bits 3:3
    UINT32 TxOn                                    :  1;  // Bits 4:4
    UINT32 LPDDR_Mode                              :  1;  // Bits 5:5
    UINT32 RxPiOn                                  :  1;  // Bits 6:6
    UINT32 TxPiOn                                  :  1;  // Bits 7:7
    UINT32 InternalClocksOn                        :  1;  // Bits 8:8
    UINT32 RepeaterClocksOn                        :  1;  // Bits 9:9
    UINT32 TxDisable                               :  1;  // Bits 10:10
    UINT32 RxDisable                               :  1;  // Bits 11:11
    UINT32 Spare2                                  :  1;  // Bits 12:12
    UINT32 RxDqsCtle                               :  2;  // Bits 14:13
    UINT32 RxReadPointer                           :  4;  // Bits 18:15
    UINT32 xover_mindelay_ctl                      :  2;  // Bits 20:19
    UINT32 DQDQSLowsupEn                           :  1;  // Bits 21:21
    UINT32 DqTcoBypass                             :  1;  // Bits 22:22
    UINT32 viewQclkDis                             :  1;  // Bits 23:23
    UINT32 ForceOdtOn                              :  1;  // Bits 24:24
    UINT32 OdtSampOff                              :  1;  // Bits 25:25
    UINT32 DisableOdtStatic                        :  1;  // Bits 26:26
    UINT32 DdrCRForceODTOn                         :  1;  // Bits 27:27
    UINT32 spare                                   :  1;  // Bits 28:28
    UINT32 LongOdtR2W                              :  1;  // Bits 29:29
    UINT32 OdtSampExtendEn                         :  1;  // Bits 30:30
    UINT32 EarlyRleakEn                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRDATACONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 TxDqsRankMuxDelay                       :  4;  // Bits 3:0
    UINT32 TxDqsRankMuxDelay_2nd_stage_offset      :  2;  // Bits 5:4
    UINT32 ForceDqsOnQuickOdtOff                   :  1;  // Bits 6:6
    UINT32 Strong2WeakOnDqsOdt                     :  1;  // Bits 7:7
    INT32  DqsOdtDelay                             :  6;  // Bits 13:8
    UINT32 vrefinten_atckepwrdown                  :  1;  // Bits 14:14
    UINT32 DqsOdtSampExtendEn                      :  1;  // Bits 15:15
    UINT32 DqsOdtDuration                          :  3;  // Bits 18:16
    UINT32 AllowOvrdOdtOnAsyncDrv                  :  1;  // Bits 19:19
    UINT32 LeakerComp                              :  3;  // Bits 22:20
    UINT32 rxclkstgnummsb                          :  1;  // Bits 23:23
    UINT32 NomPgDis                                :  1;  // Bits 24:24
    UINT32 rcven_four_cycle_fill                   :  1;  // Bits 25:25
    UINT32 StrongWkLeaker                          :  4;  // Bits 29:26
    UINT32 CBEnAmp1                                :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRDATACONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 leakerwithtxanalogen                    :  1;  // Bits 0:0
    UINT32 glbdrv_clkgate_enable                   :  1;  // Bits 1:1
    UINT32 biasrcomp                               :  3;  // Bits 4:2
    UINT32 txdeskewcal                             :  1;  // Bits 5:5
    UINT32 txdeskewdqscodesel                      :  1;  // Bits 6:6
    UINT32 rxdeskewcal                             :  1;  // Bits 7:7
    UINT32 rxdeskewdqscodesel                      :  1;  // Bits 8:8
    UINT32 DisPanicDrv                             :  2;  // Bits 10:9
    UINT32 dllnbiassel                             :  1;  // Bits 11:11
    UINT32 rxsel                                   :  1;  // Bits 12:12
    UINT32 ampoffseten                             :  1;  // Bits 13:13
    UINT32 LpDdr4Mode                              :  1;  // Bits 14:14
    UINT32 lpddr4wrlongpreambleen                  :  1;  // Bits 15:15
    UINT32 ddr4wrlongpreambleen                    :  1;  // Bits 16:16
    UINT32 VssODTSingleSegEn                       :  1;  // Bits 17:17
    UINT32 VssODTEn                                :  1;  // Bits 18:18
    UINT32 dqsodtdowncompoffset                    :  5;  // Bits 23:19
    UINT32 dqsodtupcompoffset                      :  5;  // Bits 28:24
    UINT32 spare2                                  :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRDATACONTROL4_STRUCT;

typedef union {
  struct {
    UINT32 RxVref                                  :  8;  // Bits 7:0
    UINT32 ddrcrdqsmaskcnten                       :  1;  // Bits 8:8
    UINT32 ddrcrnumofpulses                        :  2;  // Bits 10:9
    UINT32 ddrcrmaskcntpulsenumstart               :  4;  // Bits 14:11
    UINT32 Lp4xVoltageSelect                       :  1;  // Bits 15:15
    UINT32 DdrDqOvrdModeEn                         :  8;  // Bits 23:16
    UINT32 DdrDqOvrdData                           :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRDATACONTROL5_STRUCT;

typedef union {
  struct {
    UINT32 RankOvrd                                :  1;  // Bits 0:0
    UINT32 RankValue                               :  2;  // Bits 2:1
    UINT32 Gear1                                   :  1;  // Bits 3:3
    UINT32 RxDqsAmpOffset                          :  5;  // Bits 8:4
    UINT32 fast_dqsoutputenable                    :  1;  // Bits 9:9
    UINT32 tx_clock_on_with_txanalogen             :  1;  // Bits 10:10
    UINT32 local_gate_d0tx                         :  1;  // Bits 11:11
    UINT32 strongwkleakermsb                       :  2;  // Bits 13:12
    UINT32 forcedqsponwithleaker                   :  1;  // Bits 14:14
    UINT32 forcedqsnonwithleaker                   :  1;  // Bits 15:15
    UINT32 RxBiasCtl1                              :  8;  // Bits 23:16
    UINT32 ForceDqsPon                             :  1;  // Bits 24:24
    UINT32 ForceDqsNon                             :  1;  // Bits 25:25
    UINT32 sdll_picb                               :  3;  // Bits 28:26
    UINT32 d0_picb                                 :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRDATACONTROL6_STRUCT;

typedef union {
  struct {
    UINT32 DqsDfeDlyRank0                          :  6;  // Bits 5:0
    UINT32 DqsDfeDlyRank1                          :  6;  // Bits 11:6
    UINT32 DqsDfeDlyRank2                          :  6;  // Bits 17:12
    UINT32 DqsDfeDlyRank3                          :  6;  // Bits 23:18
    UINT32 sdll_bw_ctrl                            :  4;  // Bits 27:24
    UINT32 d0_bw_ctrl                              :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRDATACONTROL7_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DELTADQSRANK0_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DELTADQSRANK1_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DELTADQSRANK2_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQS                                :  10;  // Bits 9:0
    UINT32 Spare1                                  :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DELTADQSRANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXCONTROL3RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXCONTROL3RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXCONTROL3RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane6PerBitDeskew                       :  6;  // Bits 5:0
    UINT32 Lane7PerBitDeskew                       :  6;  // Bits 11:6
    UINT32 Lane4RxOffsetVDq                        :  5;  // Bits 16:12
    UINT32 Lane5RxOffsetVDq                        :  5;  // Bits 21:17
    UINT32 Lane6RxOffsetVDq                        :  5;  // Bits 26:22
    UINT32 Lane7RxOffsetVDq                        :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_RXCONTROL3RANK3_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_TXPERBITHIRANK0_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_TXPERBITHIRANK1_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_TXPERBITHIRANK2_STRUCT;

typedef union {
  struct {
    UINT32 Lane4                                   :  6;  // Bits 5:0
    UINT32 Lane5                                   :  6;  // Bits 11:6
    UINT32 Lane6                                   :  6;  // Bits 17:12
    UINT32 Lane7                                   :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_TXPERBITHIRANK3_STRUCT;

typedef union {
  struct {
    UINT32 GVPointG1                               :  1;  // Bits 0:0
    UINT32 GVPointG2                               :  2;  // Bits 2:1
    UINT32 ReplicaOffsetUse                        :  1;  // Bits 3:3
    UINT32 VTCompOffsetUse                         :  2;  // Bits 5:4
    UINT32 ExtOffset                               :  7;  // Bits 12:6
    UINT32 BiasOffset                              :  15;  // Bits 27:13
    UINT32 ActiveRanks                             :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATACONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 DccCodeOvrd                             :  6;  // Bits 5:0
    UINT32 RepDccAipCb                             :  2;  // Bits 7:6
    UINT32 DccPtrOvrd                              :  4;  // Bits 11:8
    UINT32 RnkPtrOvrd                              :  2;  // Bits 13:12
    UINT32 DcdDigEnOvrd                            :  1;  // Bits 14:14
    UINT32 DcdAnaEnOvrd                            :  1;  // Bits 15:15
    UINT32 DcdWindow                               :  15;  // Bits 30:16
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATACONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 StartBinCode                            :  6;  // Bits 5:0
    UINT32 CodePtrStartBit                         :  3;  // Bits 8:6
    UINT32 DccTrshOld                              :  13;  // Bits 21:9
    UINT32 DcdCntsStartDiff                        :  5;  // Bits 26:22
    UINT32 ClkGateDisable                          :  1;  // Bits 27:27
    UINT32 DccDataViewSelect0                      :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATACONTROL2_STRUCT;

typedef union {
  struct {
    UINT32 ActiveDccRank0                          :  11;  // Bits 10:0
    UINT32 ActiveDccRank1                          :  9;  // Bits 19:11
    UINT32 ActiveDccRank2                          :  9;  // Bits 28:20
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATACONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 ActiveDccRank3                          :  9;  // Bits 8:0
    UINT32 Spare                                   :  1;  // Bits 9:9
    UINT32 ReplicaPrev_GVp0                        :  6;  // Bits 15:10
    UINT32 ReplicaPrev_GVp1                        :  6;  // Bits 21:16
    UINT32 ReplicaPrev_GVp2                        :  6;  // Bits 27:22
    UINT32 DccDataViewSelect1                      :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATACONTROL4_STRUCT;

typedef union {
  struct {
    UINT32 Spare                                   :  2;  // Bits 1:0
    UINT32 vtcompoffsetmsgwren                     :  1;  // Bits 2:2
    UINT32 ReplicaPrev_GVp3                        :  6;  // Bits 8:3
    UINT32 BubbleCntVal                            :  5;  // Bits 13:9
    UINT32 DeterministicSyncVal                    :  6;  // Bits 19:14
    UINT32 DeterministicCntVal                     :  11;  // Bits 30:20
    UINT32 DeterministicMode                       :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATACONTROL5_STRUCT;

typedef union {
  struct {
    UINT32 Rank0DccDone                            :  11;  // Bits 10:0
    UINT32 Rank1DccDone                            :  9;  // Bits 19:11
    UINT32 Rank2DccDone                            :  9;  // Bits 28:20
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATATRAINSTATUS0_STRUCT;

typedef union {
  struct {
    UINT32 Rank3DccDone                            :  9;  // Bits 8:0
    UINT32 Spare0                                  :  1;  // Bits 9:9
    UINT32 CntDone                                 :  1;  // Bits 10:10
    UINT32 Dcd_O_Cnt                               :  15;  // Bits 25:11
    UINT32 Spare1                                  :  1;  // Bits 26:26
    UINT32 BinFsmCurrState                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATATRAINSTATUS1_STRUCT;

typedef union {
  struct {
    UINT32 AuxCnt                                  :  16;  // Bits 15:0
    UINT32 ReplicaOffset                           :  7;  // Bits 22:16
    UINT32 VTCompOffset                            :  7;  // Bits 29:23
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATATRAINSTATUS2_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  11;  // Bits 10:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 27:11
    UINT32 Spare                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATATRAINERRSTATUSRANK0_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  9;  // Bits 8:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 25:9
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATATRAINERRSTATUSRANK1_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  9;  // Bits 8:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 25:9
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATATRAINERRSTATUSRANK2_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  9;  // Bits 8:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 25:9
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATATRAINERRSTATUSRANK3_STRUCT;

typedef union {
  struct {
    UINT32 ReplicaTrain_GVp0                       :  6;  // Bits 5:0
    UINT32 ReplicaTrain_GVp1                       :  6;  // Bits 11:6
    UINT32 ReplicaTrain_GVp2                       :  6;  // Bits 17:12
    UINT32 ReplicaTrain_GVp3                       :  6;  // Bits 23:18
    UINT32 ReplicaOffsetPrev                       :  7;  // Bits 30:24
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATATRAINREPLICA0_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATATRAINVAL0RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATATRAINVAL0RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATATRAINVAL0RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Dq0DccVal                               :  6;  // Bits 5:0
    UINT32 Dq1DccVal                               :  6;  // Bits 11:6
    UINT32 Dq2DccVal                               :  6;  // Bits 17:12
    UINT32 Dq3DccVal                               :  6;  // Bits 23:18
    UINT32 Dq4DccVal                               :  6;  // Bits 29:24
    UINT32 DqDccAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATATRAINVAL0RANK3_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 ReplicaShadowDccVal                     :  6;  // Bits 29:24
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATATRAINVAL1RANK0_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 spare2                                  :  2;  // Bits 25:24
    UINT32 binfsmsteptosavecnts                    :  3;  // Bits 28:26
    UINT32 savecntsatchosenbinstep                 :  1;  // Bits 29:29
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATATRAINVAL1RANK1_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 Spare                                   :  6;  // Bits 29:24
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATATRAINVAL1RANK2_STRUCT;

typedef union {
  struct {
    UINT32 Dq5DccVal                               :  6;  // Bits 5:0
    UINT32 Dq6DccVal                               :  6;  // Bits 11:6
    UINT32 Dq7DccVal                               :  6;  // Bits 17:12
    UINT32 DqsDccVal                               :  6;  // Bits 23:18
    UINT32 Spare                                   :  6;  // Bits 29:24
    UINT32 DqsDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATATRAINVAL1RANK3_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_0                        :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_4                        :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_8                        :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_12                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_16                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATADCCPILUT0_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_20                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_24                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_28                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_32                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_36                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATADCCPILUT1_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_40                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_44                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_48                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_52                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_56                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATADCCPILUT2_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_60                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_64                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_68                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_72                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_76                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATADCCPILUT3_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_80                       :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_84                       :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_88                       :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_92                       :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_96                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATADCCPILUT4_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_100                      :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_104                      :  6;  // Bits 11:6
    UINT32 DccPiForPiCode_108                      :  6;  // Bits 17:12
    UINT32 DccPiForPiCode_112                      :  6;  // Bits 23:18
    UINT32 DccPiForPiCode_116                      :  6;  // Bits 29:24
    UINT32 DccPiAipCb                              :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATADCCPILUT5_STRUCT;

typedef union {
  struct {
    UINT32 DccPiForPiCode_120                      :  6;  // Bits 5:0
    UINT32 DccPiForPiCode_124                      :  6;  // Bits 11:6
    UINT32 DccPiStaticCode                         :  6;  // Bits 17:12
    UINT32 DccPiStaticCodeGear1                    :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DCCDATADCCPILUT6_STRUCT;

typedef union {
  struct {
    UINT32 DqTcoCompBit0                           :  6;  // Bits 5:0
    UINT32 DqTcoCompBit1                           :  6;  // Bits 11:6
    UINT32 DqTcoCompBit2                           :  6;  // Bits 17:12
    UINT32 DqTcoCompBit3                           :  6;  // Bits 23:18
    UINT32 DqsNTcoComp                             :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRDATATCOCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 DqTcoCompBit4                           :  6;  // Bits 5:0
    UINT32 DqTcoCompBit5                           :  6;  // Bits 11:6
    UINT32 DqTcoCompBit6                           :  6;  // Bits 17:12
    UINT32 DqTcoCompBit7                           :  6;  // Bits 23:18
    UINT32 DqsPTcoComp                             :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRDATATCOCONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit6Rank0                       :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit6Rank1                       :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit7Rank0                       :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit7Rank1                       :  6;  // Bits 23:18
    UINT32 DfeDlyModeRank0                         :  2;  // Bits 25:24
    UINT32 DfeDlyModeRank1                         :  2;  // Bits 27:26
    UINT32 DfeDlyModeRank2                         :  2;  // Bits 29:28
    UINT32 DfeDlyModeRank3                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRDATADFECONTROL1RANK01_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit6Rank2                       :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit6Rank3                       :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit7Rank2                       :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit7Rank3                       :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRDATADFECONTROL1RANK23_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRDATADFECONTROL0RANK0_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRDATADFECONTROL0RANK1_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRDATADFECONTROL0RANK2_STRUCT;

typedef union {
  struct {
    UINT32 DqDfeDlyBit1                            :  6;  // Bits 5:0
    UINT32 DqDfeDlyBit2                            :  6;  // Bits 11:6
    UINT32 DqDfeDlyBit3                            :  6;  // Bits 17:12
    UINT32 DqDfeDlyBit4                            :  6;  // Bits 23:18
    UINT32 DqDfeDlyBit5                            :  6;  // Bits 29:24
    UINT32 DqDfeEn                                 :  1;  // Bits 30:30
    UINT32 DqsDfeEn                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8CH1_CR_DDRCRDATADFECONTROL0RANK3_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  6;  // Bits 5:0
    UINT32 RcompDrvUp                              :  6;  // Bits 11:6
    UINT32 RcompDrvDown                            :  6;  // Bits 17:12
    UINT32 Spare                                   :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDBCH0_CR_DDRCRCMDCOMP_STRUCT;

typedef union {
  struct {
    INT32  ScompOffset                             :  5;  // Bits 4:0
    INT32  RcompDrvUpOffset                        :  4;  // Bits 8:5
    INT32  RcompDrvDownOffset                      :  4;  // Bits 12:9
    UINT32 Spare                                   :  19;  // Bits 31:13
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDBCH0_CR_DDRCRCMDCOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 CmdPi0Code                              :  7;  // Bits 6:0
    UINT32 CmdPi1Code                              :  7;  // Bits 13:7
    UINT32 spare0                                  :  2;  // Bits 15:14
    UINT32 CmdPi2Code                              :  7;  // Bits 22:16
    UINT32 spare1                                  :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDBCH0_CR_DDRCRCMDPICODING_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 ClkGateDisable                          :  1;  // Bits 6:6
    UINT32 TxOn                                    :  1;  // Bits 7:7
    UINT32 IntClkOn                                :  1;  // Bits 8:8
    UINT32 RepClkOn                                :  1;  // Bits 9:9
    UINT32 IolbOrMisr                              :  1;  // Bits 10:10
    UINT32 IolbHold                                :  1;  // Bits 11:11
    UINT32 OdtMode                                 :  1;  // Bits 12:12
    UINT32 CmdTxEq                                 :  2;  // Bits 14:13
    UINT32 EarlyWeakDrive                          :  2;  // Bits 16:15
    UINT32 dis_lp4_cmd_mirror                      :  1;  // Bits 17:17
    UINT32 CmdCriClkGateEnGvBlock                  :  1;  // Bits 18:18
    UINT32 LaDrvEnOvrd                             :  1;  // Bits 19:19
    UINT32 DdrCmdSlwDlyByp                         :  1;  // Bits 20:20
    INT32  Spares                                  :  6;  // Bits 26:21
    UINT32 VccddqHi                                :  1;  // Bits 27:27
    UINT32 DllWeakLock                             :  1;  // Bits 28:28
    UINT32 CMD_Rate                                :  1;  // Bits 29:29
    UINT32 LPDdrCAA_or_CAB_Dis                     :  1;  // Bits 30:30
    UINT32 Lp4xVoltageSelect                       :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDBCH0_CR_DDRCRCMDCONTROLS_STRUCT;

typedef union {
  struct {
    INT32  RxVref                                  :  8;  // Bits 7:0
    UINT32 CMDLowsupEn                             :  1;  // Bits 8:8
    UINT32 Gear1                                   :  1;  // Bits 9:9
    UINT32 xover_mindelay_ctl                      :  2;  // Bits 11:10
    UINT32 cmd_eq_strengh                          :  4;  // Bits 15:12
    UINT32 cmd_eq_en                               :  1;  // Bits 16:16
    UINT32 cmd_eq_constz                           :  1;  // Bits 17:17
    UINT32 Spare                                   :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDBCH0_CR_DDRCRCMDCONTROLS1_STRUCT;

typedef union {
  struct {
    UINT32 datatrainfeedback                       :  10;  // Bits 9:0
    UINT32 Spare                                   :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDBCH0_CR_DDRCRLOOPBACKFEEDBACK_STRUCT;

typedef union {
  struct {
    UINT32 CmdTcoComp                              :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDBCH0_CR_DDRCRCMDTCOCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  6;  // Bits 5:0
    UINT32 RcompDrvUp                              :  6;  // Bits 11:6
    UINT32 RcompDrvDown                            :  6;  // Bits 17:12
    UINT32 Spare                                   :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDBCH1_CR_DDRCRCMDCOMP_STRUCT;

typedef union {
  struct {
    INT32  ScompOffset                             :  5;  // Bits 4:0
    INT32  RcompDrvUpOffset                        :  4;  // Bits 8:5
    INT32  RcompDrvDownOffset                      :  4;  // Bits 12:9
    UINT32 Spare                                   :  19;  // Bits 31:13
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDBCH1_CR_DDRCRCMDCOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 CmdPi0Code                              :  7;  // Bits 6:0
    UINT32 CmdPi1Code                              :  7;  // Bits 13:7
    UINT32 spare0                                  :  2;  // Bits 15:14
    UINT32 CmdPi2Code                              :  7;  // Bits 22:16
    UINT32 spare1                                  :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDBCH1_CR_DDRCRCMDPICODING_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 ClkGateDisable                          :  1;  // Bits 6:6
    UINT32 TxOn                                    :  1;  // Bits 7:7
    UINT32 IntClkOn                                :  1;  // Bits 8:8
    UINT32 RepClkOn                                :  1;  // Bits 9:9
    UINT32 IolbOrMisr                              :  1;  // Bits 10:10
    UINT32 IolbHold                                :  1;  // Bits 11:11
    UINT32 OdtMode                                 :  1;  // Bits 12:12
    UINT32 CmdTxEq                                 :  2;  // Bits 14:13
    UINT32 EarlyWeakDrive                          :  2;  // Bits 16:15
    UINT32 dis_lp4_cmd_mirror                      :  1;  // Bits 17:17
    UINT32 CmdCriClkGateEnGvBlock                  :  1;  // Bits 18:18
    UINT32 LaDrvEnOvrd                             :  1;  // Bits 19:19
    UINT32 DdrCmdSlwDlyByp                         :  1;  // Bits 20:20
    INT32  Spares                                  :  6;  // Bits 26:21
    UINT32 VccddqHi                                :  1;  // Bits 27:27
    UINT32 DllWeakLock                             :  1;  // Bits 28:28
    UINT32 CMD_Rate                                :  1;  // Bits 29:29
    UINT32 LPDdrCAA_or_CAB_Dis                     :  1;  // Bits 30:30
    UINT32 Lp4xVoltageSelect                       :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDBCH1_CR_DDRCRCMDCONTROLS_STRUCT;

typedef union {
  struct {
    INT32  RxVref                                  :  8;  // Bits 7:0
    UINT32 CMDLowsupEn                             :  1;  // Bits 8:8
    UINT32 Gear1                                   :  1;  // Bits 9:9
    UINT32 xover_mindelay_ctl                      :  2;  // Bits 11:10
    UINT32 cmd_eq_strengh                          :  4;  // Bits 15:12
    UINT32 cmd_eq_en                               :  1;  // Bits 16:16
    UINT32 cmd_eq_constz                           :  1;  // Bits 17:17
    UINT32 Spare                                   :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDBCH1_CR_DDRCRCMDCONTROLS1_STRUCT;

typedef union {
  struct {
    UINT32 datatrainfeedback                       :  10;  // Bits 9:0
    UINT32 Spare                                   :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDBCH1_CR_DDRCRLOOPBACKFEEDBACK_STRUCT;

typedef union {
  struct {
    UINT32 CmdTcoComp                              :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDBCH1_CR_DDRCRCMDTCOCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 ClkTcoComp                              :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DDRCRCLKTCOCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 CtlTcoComp                              :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DDRCRCTLTCOCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 datatrainfeedback                       :  10;  // Bits 9:0
    UINT32 Spare                                   :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DDRCRLOOPBACKFEEDBACK_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  6;  // Bits 5:0
    UINT32 RcompDrvUp                              :  6;  // Bits 11:6
    UINT32 RcompDrvDown                            :  6;  // Bits 17:12
    UINT32 Spare                                   :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DDRCRCTLCOMP_STRUCT;

typedef union {
  struct {
    INT32  ScompOffset                             :  5;  // Bits 4:0
    INT32  RcompDrvUpOffset                        :  4;  // Bits 8:5
    INT32  RcompDrvDownOffset                      :  4;  // Bits 12:9
    UINT32 Spare                                   :  19;  // Bits 31:13
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DDRCRCTLCOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 CtlPiCode0                              :  7;  // Bits 6:0
    UINT32 CtlPiCode1                              :  7;  // Bits 13:7
    UINT32 CtlPiCode2                              :  7;  // Bits 20:14
    UINT32 CtlPiCode3                              :  7;  // Bits 27:21
    UINT32 CtlXoverEnable                          :  1;  // Bits 28:28
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DDRCRCTLPICODING_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 ClkGateDisable                          :  1;  // Bits 6:6
    UINT32 TxOn                                    :  1;  // Bits 7:7
    UINT32 IntClkOn                                :  1;  // Bits 8:8
    UINT32 RepClkOn                                :  1;  // Bits 9:9
    UINT32 IolbOrMisr                              :  1;  // Bits 10:10
    UINT32 IOLBHold                                :  1;  // Bits 11:11
    UINT32 OdtMode                                 :  1;  // Bits 12:12
    UINT32 CmdTxEq                                 :  2;  // Bits 14:13
    UINT32 EarlyWeakDrive                          :  2;  // Bits 16:15
    UINT32 CtlTxEq                                 :  2;  // Bits 18:17
    UINT32 CtlSRDrv                                :  2;  // Bits 20:19
    INT32  RxVref                                  :  6;  // Bits 26:21
    UINT32 VccddqHi                                :  1;  // Bits 27:27
    UINT32 DllWeakLock                             :  1;  // Bits 28:28
    UINT32 CMD_Rate                                :  1;  // Bits 29:29
    UINT32 LaDrvEnOvrd                             :  1;  // Bits 30:30
    UINT32 ma3_ma4_par_dis                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DDRCRCTLCONTROLS_STRUCT;

typedef union {
  struct {
    UINT32 CtlCkTxEn                               :  8;  // Bits 7:0
    UINT32 PiClkEn                                 :  4;  // Bits 11:8
    UINT32 DdrCtlCkeSlwDlyByp                      :  1;  // Bits 12:12
    UINT32 cs_all_clk_gate_dis                     :  1;  // Bits 13:13
    UINT32 CsClkGateDis_in_idle                    :  1;  // Bits 14:14
    UINT32 CsPiClkGateEn                           :  2;  // Bits 16:15
    UINT32 CsOdtForCS_ODT_1                        :  1;  // Bits 17:17
    UINT32 CsOdtForCS_ODT_0                        :  1;  // Bits 18:18
    UINT32 CsOdtForCS_N_3                          :  1;  // Bits 19:19
    UINT32 CsOdtForCS_N_2                          :  1;  // Bits 20:20
    UINT32 CsOdtForCS_N_1                          :  1;  // Bits 21:21
    UINT32 CsOdtForCS_N_0                          :  1;  // Bits 22:22
    UINT32 Gear1                                   :  1;  // Bits 23:23
    UINT32 lp4xvoltageselect                       :  1;  // Bits 24:24
    UINT32 xover_mindelay_ctl                      :  2;  // Bits 26:25
    UINT32 ClkSlewDlyByPass                        :  1;  // Bits 27:27
    UINT32 CtlCriClkGateEnGvBlock                  :  1;  // Bits 28:28
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DDRCRCTLRANKSUSED_STRUCT;

typedef union {
  struct {
    INT32  RxVref                                  :  8;  // Bits 7:0
    UINT32 MapCkeForScOdt                          :  18;  // Bits 25:8
    UINT32 CMDLowsupEn                             :  1;  // Bits 26:26
    UINT32 CKELowsupEn                             :  1;  // Bits 27:27
    UINT32 CTLLowsupEn                             :  1;  // Bits 28:28
    UINT32 CLKLowsupEn                             :  1;  // Bits 29:29
    UINT32 en_sr_mode_to_cke                       :  1;  // Bits 30:30
    UINT32 c3segsel_b_for_cke                      :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DDRCRCTLCONTROLS1_STRUCT;

typedef union {
  struct {
    INT32  ScompOffset                             :  4;  // Bits 3:0
    INT32  RcompDrvUpOffset                        :  4;  // Bits 7:4
    INT32  RcompDrvDownOffset                      :  4;  // Bits 11:8
    UINT32 ClkCompOnTheFlyUpdtEn                   :  1;  // Bits 12:12
    UINT32 Spare                                   :  19;  // Bits 31:13
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DDRCRCLKCOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  5;  // Bits 4:0
    UINT32 RcompDrvUp                              :  6;  // Bits 10:5
    UINT32 RcompDrvDown                            :  6;  // Bits 16:11
    UINT32 Spare                                   :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DDRCRCLKCOMP_STRUCT;

typedef union {
  struct {
    INT32  ScompOffset                             :  5;  // Bits 4:0
    INT32  RcompDrvUpOffset                        :  4;  // Bits 8:5
    INT32  RcompDrvDownOffset                      :  4;  // Bits 12:9
    UINT32 Spare                                   :  19;  // Bits 31:13
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DDRCRCCCCOMPOFFSET1_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 ClkGateDisable                          :  1;  // Bits 4:4
    UINT32 TxOn                                    :  1;  // Bits 5:5
    UINT32 IntClkOn                                :  1;  // Bits 6:6
    UINT32 RepClkOn                                :  1;  // Bits 7:7
    UINT32 IolbOrMisr                              :  1;  // Bits 8:8
    UINT32 IOLBHold                                :  1;  // Bits 9:9
    UINT32 OdtMode                                 :  1;  // Bits 10:10
    UINT32 CmdTxEq                                 :  2;  // Bits 12:11
    UINT32 EarlyWeakDrive                          :  2;  // Bits 14:13
    UINT32 CtlTxEq                                 :  2;  // Bits 16:15
    UINT32 CtlSRDrv                                :  2;  // Bits 18:17
    INT32  RxVref                                  :  6;  // Bits 24:19
    UINT32 CKELowsupEn                             :  1;  // Bits 25:25
    UINT32 spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DDRCRCCC4CKECONTROLS_STRUCT;

typedef union {
  struct {
    UINT32 ctlcktxen                               :  2;  // Bits 1:0
    UINT32 PiClkEn                                 :  4;  // Bits 5:2
    UINT32 DdrCkeCmdSlwDlyByp                      :  2;  // Bits 7:6
    UINT32 Spare                                   :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DDRCRCCC4CKERANKSUSED_STRUCT;

typedef union {
  struct {
    UINT32 CRVALID                                 :  1;  // Bits 0:0
    UINT32 GVPointG2                               :  2;  // Bits 2:1
    UINT32 ReplicaOffsetUse                        :  1;  // Bits 3:3
    UINT32 VTCompOffsetUse                         :  2;  // Bits 5:4
    UINT32 ExtOffset                               :  7;  // Bits 12:6
    UINT32 BiasOffset                              :  15;  // Bits 27:13
    UINT32 ActiveRanks                             :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DCCCLKCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 DccCodeOvrd                             :  6;  // Bits 5:0
    UINT32 Rank0DccAipCb                           :  2;  // Bits 7:6
    UINT32 DccPtrOvrd                              :  4;  // Bits 11:8
    UINT32 RnkPtrOvrd                              :  2;  // Bits 13:12
    UINT32 DcdDigEnOvrd                            :  1;  // Bits 14:14
    UINT32 DcdAnaEnOvrd                            :  1;  // Bits 15:15
    UINT32 DcdWindow                               :  15;  // Bits 30:16
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DCCCLKCONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 StartBinCode                            :  6;  // Bits 5:0
    UINT32 CodePtrStartBit                         :  3;  // Bits 8:6
    UINT32 DccTrshOld                              :  13;  // Bits 21:9
    UINT32 DcdCntsStartDiff                        :  5;  // Bits 26:22
    UINT32 ClkGateDisable                          :  1;  // Bits 27:27
    UINT32 DccClkViewSelect0                       :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DCCCLKCONTROL2_STRUCT;

typedef union {
  struct {
    UINT32 ActiveDccRank0                          :  11;  // Bits 10:0
    UINT32 ActiveDccRank1                          :  9;  // Bits 19:11
    UINT32 ActiveDccRank2                          :  9;  // Bits 28:20
    UINT32 clkdccupdateoldpath                     :  1;  // Bits 29:29
    UINT32 clkdcccfgbypass                         :  1;  // Bits 30:30
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DCCCLKCONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 ActiveDccRank3                          :  9;  // Bits 8:0
    UINT32 Spare                                   :  1;  // Bits 9:9
    UINT32 ReplicaPrev_GVp0                        :  6;  // Bits 15:10
    UINT32 ReplicaPrev_GVp1                        :  6;  // Bits 21:16
    UINT32 ReplicaPrev_GVp2                        :  6;  // Bits 27:22
    UINT32 DccClkViewSelect1                       :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DCCCLKCONTROL4_STRUCT;

typedef union {
  struct {
    UINT32 dccclkupdtstepsize                      :  2;  // Bits 1:0
    UINT32 vtcompoffsetmsgwren                     :  1;  // Bits 2:2
    UINT32 ReplicaPrev_GVp3                        :  6;  // Bits 8:3
    UINT32 BubbleCntVal                            :  5;  // Bits 13:9
    UINT32 DeterministicSyncVal                    :  6;  // Bits 19:14
    UINT32 DeterministicCntVal                     :  11;  // Bits 30:20
    UINT32 DeterministicMode                       :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DCCCLKCONTROL5_STRUCT;

typedef union {
  struct {
    UINT32 ClkDccDone                              :  3;  // Bits 2:0
    UINT32 Spare                                   :  29;  // Bits 31:3
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DCCCLKTRAINSTATUS0_STRUCT;

typedef union {
  struct {
    UINT32 Spare0                                  :  10;  // Bits 9:0
    UINT32 CntDone                                 :  1;  // Bits 10:10
    UINT32 Dcd_O_Cnt                               :  15;  // Bits 25:11
    UINT32 Spare1                                  :  1;  // Bits 26:26
    UINT32 BinFsmCurrState                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DCCCLKTRAINSTATUS1_STRUCT;

typedef union {
  struct {
    UINT32 AuxCnt                                  :  16;  // Bits 15:0
    UINT32 ReplicaOffset                           :  7;  // Bits 22:16
    UINT32 VTCompOffset                            :  7;  // Bits 29:23
    UINT32 Spare                                   :  1;  // Bits 30:30
    UINT32 CRVALID                                 :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DCCCLKTRAINSTATUS2_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  11;  // Bits 10:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 27:11
    UINT32 Spare                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DCCCLKTRAINERRSTATUS_STRUCT;

typedef union {
  struct {
    UINT32 Clk0DccVal                              :  6;  // Bits 5:0
    UINT32 Clk1DccVal                              :  6;  // Bits 11:6
    UINT32 Spare                                   :  17;  // Bits 28:12
    UINT32 CRVALID                                 :  1;  // Bits 29:29
    UINT32 Rank1DccAipCb                           :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DCCCLKTRAINVAL0_STRUCT;

typedef union {
  struct {
    UINT32 ReplicaShadowDccVal                     :  6;  // Bits 5:0
    UINT32 Spare                                   :  20;  // Bits 25:6
    UINT32 binfsmsteptosavecnts                    :  3;  // Bits 28:26
    UINT32 savecntsatchosenbinstep                 :  1;  // Bits 29:29
    UINT32 RepDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DCCCLKTRAINVAL1_STRUCT;

typedef union {
  struct {
    UINT32 ReplicaTrain_GVp0                       :  6;  // Bits 5:0
    UINT32 ReplicaTrain_GVp1                       :  6;  // Bits 11:6
    UINT32 ReplicaTrain_GVp2                       :  6;  // Bits 17:12
    UINT32 ReplicaTrain_GVp3                       :  6;  // Bits 23:18
    UINT32 ReplicaOffsetPrev                       :  7;  // Bits 30:24
    UINT32 CRVALID                                 :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE0_CR_DCCCLKTRAINREPLICA0_STRUCT;

typedef union {
  struct {
    UINT32 ClkTcoComp                              :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DDRCRCLKTCOCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 CtlTcoComp                              :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DDRCRCTLTCOCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 datatrainfeedback                       :  10;  // Bits 9:0
    UINT32 Spare                                   :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DDRCRLOOPBACKFEEDBACK_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  6;  // Bits 5:0
    UINT32 RcompDrvUp                              :  6;  // Bits 11:6
    UINT32 RcompDrvDown                            :  6;  // Bits 17:12
    UINT32 Spare                                   :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DDRCRCTLCOMP_STRUCT;

typedef union {
  struct {
    INT32  ScompOffset                             :  5;  // Bits 4:0
    INT32  RcompDrvUpOffset                        :  4;  // Bits 8:5
    INT32  RcompDrvDownOffset                      :  4;  // Bits 12:9
    UINT32 Spare                                   :  19;  // Bits 31:13
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DDRCRCTLCOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 CtlPiCode0                              :  7;  // Bits 6:0
    UINT32 CtlPiCode1                              :  7;  // Bits 13:7
    UINT32 CtlPiCode2                              :  7;  // Bits 20:14
    UINT32 CtlPiCode3                              :  7;  // Bits 27:21
    UINT32 CtlXoverEnable                          :  1;  // Bits 28:28
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DDRCRCTLPICODING_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 ClkGateDisable                          :  1;  // Bits 6:6
    UINT32 TxOn                                    :  1;  // Bits 7:7
    UINT32 IntClkOn                                :  1;  // Bits 8:8
    UINT32 RepClkOn                                :  1;  // Bits 9:9
    UINT32 IolbOrMisr                              :  1;  // Bits 10:10
    UINT32 IOLBHold                                :  1;  // Bits 11:11
    UINT32 OdtMode                                 :  1;  // Bits 12:12
    UINT32 CmdTxEq                                 :  2;  // Bits 14:13
    UINT32 EarlyWeakDrive                          :  2;  // Bits 16:15
    UINT32 CtlTxEq                                 :  2;  // Bits 18:17
    UINT32 CtlSRDrv                                :  2;  // Bits 20:19
    INT32  RxVref                                  :  6;  // Bits 26:21
    UINT32 VccddqHi                                :  1;  // Bits 27:27
    UINT32 DllWeakLock                             :  1;  // Bits 28:28
    UINT32 CMD_Rate                                :  1;  // Bits 29:29
    UINT32 LaDrvEnOvrd                             :  1;  // Bits 30:30
    UINT32 ma3_ma4_par_dis                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DDRCRCTLCONTROLS_STRUCT;

typedef union {
  struct {
    UINT32 CtlCkTxEn                               :  8;  // Bits 7:0
    UINT32 PiClkEn                                 :  4;  // Bits 11:8
    UINT32 DdrCtlCkeSlwDlyByp                      :  1;  // Bits 12:12
    UINT32 cs_all_clk_gate_dis                     :  1;  // Bits 13:13
    UINT32 CsClkGateDis_in_idle                    :  1;  // Bits 14:14
    UINT32 CsPiClkGateEn                           :  2;  // Bits 16:15
    UINT32 CsOdtForCS_ODT_1                        :  1;  // Bits 17:17
    UINT32 CsOdtForCS_ODT_0                        :  1;  // Bits 18:18
    UINT32 CsOdtForCS_N_3                          :  1;  // Bits 19:19
    UINT32 CsOdtForCS_N_2                          :  1;  // Bits 20:20
    UINT32 CsOdtForCS_N_1                          :  1;  // Bits 21:21
    UINT32 CsOdtForCS_N_0                          :  1;  // Bits 22:22
    UINT32 Gear1                                   :  1;  // Bits 23:23
    UINT32 lp4xvoltageselect                       :  1;  // Bits 24:24
    UINT32 xover_mindelay_ctl                      :  2;  // Bits 26:25
    UINT32 ClkSlewDlyByPass                        :  1;  // Bits 27:27
    UINT32 CtlCriClkGateEnGvBlock                  :  1;  // Bits 28:28
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DDRCRCTLRANKSUSED_STRUCT;

typedef union {
  struct {
    INT32  RxVref                                  :  8;  // Bits 7:0
    UINT32 MapCkeForScOdt                          :  18;  // Bits 25:8
    UINT32 CMDLowsupEn                             :  1;  // Bits 26:26
    UINT32 CKELowsupEn                             :  1;  // Bits 27:27
    UINT32 CTLLowsupEn                             :  1;  // Bits 28:28
    UINT32 CLKLowsupEn                             :  1;  // Bits 29:29
    UINT32 en_sr_mode_to_cke                       :  1;  // Bits 30:30
    UINT32 c3segsel_b_for_cke                      :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DDRCRCTLCONTROLS1_STRUCT;

typedef union {
  struct {
    INT32  ScompOffset                             :  4;  // Bits 3:0
    INT32  RcompDrvUpOffset                        :  4;  // Bits 7:4
    INT32  RcompDrvDownOffset                      :  4;  // Bits 11:8
    UINT32 ClkCompOnTheFlyUpdtEn                   :  1;  // Bits 12:12
    UINT32 Spare                                   :  19;  // Bits 31:13
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DDRCRCLKCOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  5;  // Bits 4:0
    UINT32 RcompDrvUp                              :  6;  // Bits 10:5
    UINT32 RcompDrvDown                            :  6;  // Bits 16:11
    UINT32 Spare                                   :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DDRCRCLKCOMP_STRUCT;

typedef union {
  struct {
    INT32  ScompOffset                             :  5;  // Bits 4:0
    INT32  RcompDrvUpOffset                        :  4;  // Bits 8:5
    INT32  RcompDrvDownOffset                      :  4;  // Bits 12:9
    UINT32 Spare                                   :  19;  // Bits 31:13
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DDRCRCCCCOMPOFFSET1_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 ClkGateDisable                          :  1;  // Bits 4:4
    UINT32 TxOn                                    :  1;  // Bits 5:5
    UINT32 IntClkOn                                :  1;  // Bits 6:6
    UINT32 RepClkOn                                :  1;  // Bits 7:7
    UINT32 IolbOrMisr                              :  1;  // Bits 8:8
    UINT32 IOLBHold                                :  1;  // Bits 9:9
    UINT32 OdtMode                                 :  1;  // Bits 10:10
    UINT32 CmdTxEq                                 :  2;  // Bits 12:11
    UINT32 EarlyWeakDrive                          :  2;  // Bits 14:13
    UINT32 CtlTxEq                                 :  2;  // Bits 16:15
    UINT32 CtlSRDrv                                :  2;  // Bits 18:17
    INT32  RxVref                                  :  6;  // Bits 24:19
    UINT32 CKELowsupEn                             :  1;  // Bits 25:25
    UINT32 spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DDRCRCCC4CKECONTROLS_STRUCT;

typedef union {
  struct {
    UINT32 ctlcktxen                               :  2;  // Bits 1:0
    UINT32 PiClkEn                                 :  4;  // Bits 5:2
    UINT32 DdrCkeCmdSlwDlyByp                      :  2;  // Bits 7:6
    UINT32 Spare                                   :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DDRCRCCC4CKERANKSUSED_STRUCT;

typedef union {
  struct {
    UINT32 CRVALID                                 :  1;  // Bits 0:0
    UINT32 GVPointG2                               :  2;  // Bits 2:1
    UINT32 ReplicaOffsetUse                        :  1;  // Bits 3:3
    UINT32 VTCompOffsetUse                         :  2;  // Bits 5:4
    UINT32 ExtOffset                               :  7;  // Bits 12:6
    UINT32 BiasOffset                              :  15;  // Bits 27:13
    UINT32 ActiveRanks                             :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DCCCLKCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 DccCodeOvrd                             :  6;  // Bits 5:0
    UINT32 Rank0DccAipCb                           :  2;  // Bits 7:6
    UINT32 DccPtrOvrd                              :  4;  // Bits 11:8
    UINT32 RnkPtrOvrd                              :  2;  // Bits 13:12
    UINT32 DcdDigEnOvrd                            :  1;  // Bits 14:14
    UINT32 DcdAnaEnOvrd                            :  1;  // Bits 15:15
    UINT32 DcdWindow                               :  15;  // Bits 30:16
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DCCCLKCONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 StartBinCode                            :  6;  // Bits 5:0
    UINT32 CodePtrStartBit                         :  3;  // Bits 8:6
    UINT32 DccTrshOld                              :  13;  // Bits 21:9
    UINT32 DcdCntsStartDiff                        :  5;  // Bits 26:22
    UINT32 ClkGateDisable                          :  1;  // Bits 27:27
    UINT32 DccClkViewSelect0                       :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DCCCLKCONTROL2_STRUCT;

typedef union {
  struct {
    UINT32 ActiveDccRank0                          :  11;  // Bits 10:0
    UINT32 ActiveDccRank1                          :  9;  // Bits 19:11
    UINT32 ActiveDccRank2                          :  9;  // Bits 28:20
    UINT32 clkdccupdateoldpath                     :  1;  // Bits 29:29
    UINT32 clkdcccfgbypass                         :  1;  // Bits 30:30
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DCCCLKCONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 ActiveDccRank3                          :  9;  // Bits 8:0
    UINT32 Spare                                   :  1;  // Bits 9:9
    UINT32 ReplicaPrev_GVp0                        :  6;  // Bits 15:10
    UINT32 ReplicaPrev_GVp1                        :  6;  // Bits 21:16
    UINT32 ReplicaPrev_GVp2                        :  6;  // Bits 27:22
    UINT32 DccClkViewSelect1                       :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DCCCLKCONTROL4_STRUCT;

typedef union {
  struct {
    UINT32 dccclkupdtstepsize                      :  2;  // Bits 1:0
    UINT32 vtcompoffsetmsgwren                     :  1;  // Bits 2:2
    UINT32 ReplicaPrev_GVp3                        :  6;  // Bits 8:3
    UINT32 BubbleCntVal                            :  5;  // Bits 13:9
    UINT32 DeterministicSyncVal                    :  6;  // Bits 19:14
    UINT32 DeterministicCntVal                     :  11;  // Bits 30:20
    UINT32 DeterministicMode                       :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DCCCLKCONTROL5_STRUCT;

typedef union {
  struct {
    UINT32 ClkDccDone                              :  3;  // Bits 2:0
    UINT32 Spare                                   :  29;  // Bits 31:3
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DCCCLKTRAINSTATUS0_STRUCT;

typedef union {
  struct {
    UINT32 Spare0                                  :  10;  // Bits 9:0
    UINT32 CntDone                                 :  1;  // Bits 10:10
    UINT32 Dcd_O_Cnt                               :  15;  // Bits 25:11
    UINT32 Spare1                                  :  1;  // Bits 26:26
    UINT32 BinFsmCurrState                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DCCCLKTRAINSTATUS1_STRUCT;

typedef union {
  struct {
    UINT32 AuxCnt                                  :  16;  // Bits 15:0
    UINT32 ReplicaOffset                           :  7;  // Bits 22:16
    UINT32 VTCompOffset                            :  7;  // Bits 29:23
    UINT32 Spare                                   :  1;  // Bits 30:30
    UINT32 CRVALID                                 :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DCCCLKTRAINSTATUS2_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  11;  // Bits 10:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 27:11
    UINT32 Spare                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DCCCLKTRAINERRSTATUS_STRUCT;

typedef union {
  struct {
    UINT32 Clk0DccVal                              :  6;  // Bits 5:0
    UINT32 Clk1DccVal                              :  6;  // Bits 11:6
    UINT32 Spare                                   :  17;  // Bits 28:12
    UINT32 CRVALID                                 :  1;  // Bits 29:29
    UINT32 Rank1DccAipCb                           :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DCCCLKTRAINVAL0_STRUCT;

typedef union {
  struct {
    UINT32 ReplicaShadowDccVal                     :  6;  // Bits 5:0
    UINT32 Spare                                   :  20;  // Bits 25:6
    UINT32 binfsmsteptosavecnts                    :  3;  // Bits 28:26
    UINT32 savecntsatchosenbinstep                 :  1;  // Bits 29:29
    UINT32 RepDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DCCCLKTRAINVAL1_STRUCT;

typedef union {
  struct {
    UINT32 ReplicaTrain_GVp0                       :  6;  // Bits 5:0
    UINT32 ReplicaTrain_GVp1                       :  6;  // Bits 11:6
    UINT32 ReplicaTrain_GVp2                       :  6;  // Bits 17:12
    UINT32 ReplicaTrain_GVp3                       :  6;  // Bits 23:18
    UINT32 ReplicaOffsetPrev                       :  7;  // Bits 30:24
    UINT32 CRVALID                                 :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE1_CR_DCCCLKTRAINREPLICA0_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  6;  // Bits 5:0
    UINT32 RcompDrvUp                              :  6;  // Bits 11:6
    UINT32 RcompDrvDown                            :  6;  // Bits 17:12
    UINT32 Spare                                   :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDACH0_CR_DDRCRCMDCOMP_STRUCT;

typedef union {
  struct {
    INT32  ScompOffset                             :  5;  // Bits 4:0
    INT32  RcompDrvUpOffset                        :  4;  // Bits 8:5
    INT32  RcompDrvDownOffset                      :  4;  // Bits 12:9
    UINT32 Spare                                   :  19;  // Bits 31:13
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDACH0_CR_DDRCRCMDCOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 CmdPi0Code                              :  7;  // Bits 6:0
    UINT32 CmdPi1Code                              :  7;  // Bits 13:7
    UINT32 spare0                                  :  2;  // Bits 15:14
    UINT32 CmdPi2Code                              :  7;  // Bits 22:16
    UINT32 spare1                                  :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDACH0_CR_DDRCRCMDPICODING_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 ClkGateDisable                          :  1;  // Bits 6:6
    UINT32 TxOn                                    :  1;  // Bits 7:7
    UINT32 IntClkOn                                :  1;  // Bits 8:8
    UINT32 RepClkOn                                :  1;  // Bits 9:9
    UINT32 IolbOrMisr                              :  1;  // Bits 10:10
    UINT32 IolbHold                                :  1;  // Bits 11:11
    UINT32 OdtMode                                 :  1;  // Bits 12:12
    UINT32 CmdTxEq                                 :  2;  // Bits 14:13
    UINT32 EarlyWeakDrive                          :  2;  // Bits 16:15
    UINT32 dis_lp4_cmd_mirror                      :  1;  // Bits 17:17
    UINT32 CmdCriClkGateEnGvBlock                  :  1;  // Bits 18:18
    UINT32 LaDrvEnOvrd                             :  1;  // Bits 19:19
    UINT32 DdrCmdSlwDlyByp                         :  1;  // Bits 20:20
    INT32  Spares                                  :  6;  // Bits 26:21
    UINT32 VccddqHi                                :  1;  // Bits 27:27
    UINT32 DllWeakLock                             :  1;  // Bits 28:28
    UINT32 CMD_Rate                                :  1;  // Bits 29:29
    UINT32 LPDdrCAA_or_CAB_Dis                     :  1;  // Bits 30:30
    UINT32 Lp4xVoltageSelect                       :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDACH0_CR_DDRCRCMDCONTROLS_STRUCT;

typedef union {
  struct {
    INT32  RxVref                                  :  8;  // Bits 7:0
    UINT32 CMDLowsupEn                             :  1;  // Bits 8:8
    UINT32 Gear1                                   :  1;  // Bits 9:9
    UINT32 xover_mindelay_ctl                      :  2;  // Bits 11:10
    UINT32 cmd_eq_strengh                          :  4;  // Bits 15:12
    UINT32 cmd_eq_en                               :  1;  // Bits 16:16
    UINT32 cmd_eq_constz                           :  1;  // Bits 17:17
    UINT32 Spare                                   :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDACH0_CR_DDRCRCMDCONTROLS1_STRUCT;

typedef union {
  struct {
    UINT32 datatrainfeedback                       :  10;  // Bits 9:0
    UINT32 Spare                                   :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDACH0_CR_DDRCRLOOPBACKFEEDBACK_STRUCT;

typedef union {
  struct {
    UINT32 CmdTcoComp                              :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDACH0_CR_DDRCRCMDTCOCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  6;  // Bits 5:0
    UINT32 RcompDrvUp                              :  6;  // Bits 11:6
    UINT32 RcompDrvDown                            :  6;  // Bits 17:12
    UINT32 Spare                                   :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDACH1_CR_DDRCRCMDCOMP_STRUCT;

typedef union {
  struct {
    INT32  ScompOffset                             :  5;  // Bits 4:0
    INT32  RcompDrvUpOffset                        :  4;  // Bits 8:5
    INT32  RcompDrvDownOffset                      :  4;  // Bits 12:9
    UINT32 Spare                                   :  19;  // Bits 31:13
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDACH1_CR_DDRCRCMDCOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 CmdPi0Code                              :  7;  // Bits 6:0
    UINT32 CmdPi1Code                              :  7;  // Bits 13:7
    UINT32 spare0                                  :  2;  // Bits 15:14
    UINT32 CmdPi2Code                              :  7;  // Bits 22:16
    UINT32 spare1                                  :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDACH1_CR_DDRCRCMDPICODING_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 ClkGateDisable                          :  1;  // Bits 6:6
    UINT32 TxOn                                    :  1;  // Bits 7:7
    UINT32 IntClkOn                                :  1;  // Bits 8:8
    UINT32 RepClkOn                                :  1;  // Bits 9:9
    UINT32 IolbOrMisr                              :  1;  // Bits 10:10
    UINT32 IolbHold                                :  1;  // Bits 11:11
    UINT32 OdtMode                                 :  1;  // Bits 12:12
    UINT32 CmdTxEq                                 :  2;  // Bits 14:13
    UINT32 EarlyWeakDrive                          :  2;  // Bits 16:15
    UINT32 dis_lp4_cmd_mirror                      :  1;  // Bits 17:17
    UINT32 CmdCriClkGateEnGvBlock                  :  1;  // Bits 18:18
    UINT32 LaDrvEnOvrd                             :  1;  // Bits 19:19
    UINT32 DdrCmdSlwDlyByp                         :  1;  // Bits 20:20
    INT32  Spares                                  :  6;  // Bits 26:21
    UINT32 VccddqHi                                :  1;  // Bits 27:27
    UINT32 DllWeakLock                             :  1;  // Bits 28:28
    UINT32 CMD_Rate                                :  1;  // Bits 29:29
    UINT32 LPDdrCAA_or_CAB_Dis                     :  1;  // Bits 30:30
    UINT32 Lp4xVoltageSelect                       :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDACH1_CR_DDRCRCMDCONTROLS_STRUCT;

typedef union {
  struct {
    INT32  RxVref                                  :  8;  // Bits 7:0
    UINT32 CMDLowsupEn                             :  1;  // Bits 8:8
    UINT32 Gear1                                   :  1;  // Bits 9:9
    UINT32 xover_mindelay_ctl                      :  2;  // Bits 11:10
    UINT32 cmd_eq_strengh                          :  4;  // Bits 15:12
    UINT32 cmd_eq_en                               :  1;  // Bits 16:16
    UINT32 cmd_eq_constz                           :  1;  // Bits 17:17
    UINT32 Spare                                   :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDACH1_CR_DDRCRCMDCONTROLS1_STRUCT;

typedef union {
  struct {
    UINT32 datatrainfeedback                       :  10;  // Bits 9:0
    UINT32 Spare                                   :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDACH1_CR_DDRCRLOOPBACKFEEDBACK_STRUCT;

typedef union {
  struct {
    UINT32 CmdTcoComp                              :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMDACH1_CR_DDRCRCMDTCOCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 CtlCkTxEn                               :  8;  // Bits 7:0
    UINT32 PiClkEn                                 :  4;  // Bits 11:8
    UINT32 DdrCtlCkeSlwDlyByp                      :  1;  // Bits 12:12
    UINT32 cs_all_clk_gate_dis                     :  1;  // Bits 13:13
    UINT32 CsClkGateDis_in_idle                    :  1;  // Bits 14:14
    UINT32 CsPiClkGateEn                           :  2;  // Bits 16:15
    UINT32 CsOdtForCS_ODT_1                        :  1;  // Bits 17:17
    UINT32 CsOdtForCS_ODT_0                        :  1;  // Bits 18:18
    UINT32 CsOdtForCS_N_3                          :  1;  // Bits 19:19
    UINT32 CsOdtForCS_N_2                          :  1;  // Bits 20:20
    UINT32 CsOdtForCS_N_1                          :  1;  // Bits 21:21
    UINT32 CsOdtForCS_N_0                          :  1;  // Bits 22:22
    UINT32 Gear1                                   :  1;  // Bits 23:23
    UINT32 lp4xvoltageselect                       :  1;  // Bits 24:24
    UINT32 xover_mindelay_ctl                      :  2;  // Bits 26:25
    UINT32 ClkSlewDlyByPass                        :  1;  // Bits 27:27
    UINT32 CtlCriClkGateEnGvBlock                  :  1;  // Bits 28:28
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH0_CR_DDRCRCTLRANKSUSED_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  6;  // Bits 5:0
    UINT32 RcompDrvUp                              :  6;  // Bits 11:6
    UINT32 RcompDrvDown                            :  6;  // Bits 17:12
    UINT32 Spare                                   :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH0_CR_DDRCRCTLCOMP_STRUCT;

typedef union {
  struct {
    INT32  ScompOffset                             :  5;  // Bits 4:0
    INT32  RcompDrvUpOffset                        :  4;  // Bits 8:5
    INT32  RcompDrvDownOffset                      :  4;  // Bits 12:9
    UINT32 Spare                                   :  19;  // Bits 31:13
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 CtlPiCode0                              :  7;  // Bits 6:0
    UINT32 CtlPiCode1                              :  7;  // Bits 13:7
    UINT32 CtlPiCode2                              :  7;  // Bits 20:14
    UINT32 CtlPiCode3                              :  7;  // Bits 27:21
    UINT32 CtlXoverEnable                          :  1;  // Bits 28:28
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH0_CR_DDRCRCTLPICODING_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 ClkGateDisable                          :  1;  // Bits 6:6
    UINT32 TxOn                                    :  1;  // Bits 7:7
    UINT32 IntClkOn                                :  1;  // Bits 8:8
    UINT32 RepClkOn                                :  1;  // Bits 9:9
    UINT32 IolbOrMisr                              :  1;  // Bits 10:10
    UINT32 IOLBHold                                :  1;  // Bits 11:11
    UINT32 OdtMode                                 :  1;  // Bits 12:12
    UINT32 CmdTxEq                                 :  2;  // Bits 14:13
    UINT32 EarlyWeakDrive                          :  2;  // Bits 16:15
    UINT32 CtlTxEq                                 :  2;  // Bits 18:17
    UINT32 CtlSRDrv                                :  2;  // Bits 20:19
    INT32  RxVref                                  :  6;  // Bits 26:21
    UINT32 VccddqHi                                :  1;  // Bits 27:27
    UINT32 DllWeakLock                             :  1;  // Bits 28:28
    UINT32 CMD_Rate                                :  1;  // Bits 29:29
    UINT32 LaDrvEnOvrd                             :  1;  // Bits 30:30
    UINT32 ma3_ma4_par_dis                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH0_CR_DDRCRCTLCONTROLS_STRUCT;

typedef union {
  struct {
    INT32  RxVref                                  :  8;  // Bits 7:0
    UINT32 MapCkeForScOdt                          :  18;  // Bits 25:8
    UINT32 CMDLowsupEn                             :  1;  // Bits 26:26
    UINT32 CKELowsupEn                             :  1;  // Bits 27:27
    UINT32 CTLLowsupEn                             :  1;  // Bits 28:28
    UINT32 CLKLowsupEn                             :  1;  // Bits 29:29
    UINT32 en_sr_mode_to_cke                       :  1;  // Bits 30:30
    UINT32 c3segsel_b_for_cke                      :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH0_CR_DDRCRCTLCONTROLS1_STRUCT;

typedef union {
  struct {
    UINT32 datatrainfeedback                       :  10;  // Bits 9:0
    UINT32 Spare                                   :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH0_CR_DDRCRLOOPBACKFEEDBACK_STRUCT;

typedef union {
  struct {
    UINT32 shift_16                                :  1;  // Bits 0:0
    UINT32 clken_pulse_mode                        :  1;  // Bits 1:1
    UINT32 reg_clken_mode                          :  1;  // Bits 2:2
    UINT32 reg_clken                               :  1;  // Bits 3:3
    UINT32 feedback_en                             :  1;  // Bits 4:4
    UINT32 event_mode                              :  1;  // Bits 5:5
    UINT32 lfsr_reset                              :  1;  // Bits 6:6
    UINT32 sdo_en                                  :  1;  // Bits 7:7
    UINT32 reserved0                               :  8;  // Bits 15:8
    UINT32 cr_rd_data                              :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH0_CR_DDRCMDMISR_STRUCT;

typedef union {
  struct {
    UINT32 CtlTcoComp                              :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH0_CR_DDRCRCTLTCOCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  5;  // Bits 4:0
    UINT32 RcompDrvUp                              :  6;  // Bits 10:5
    UINT32 RcompDrvDown                            :  6;  // Bits 16:11
    UINT32 Spare                                   :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH0_CR_DDRCRCLKCOMP_STRUCT;

typedef union {
  struct {
    INT32  ScompOffset                             :  4;  // Bits 3:0
    INT32  RcompDrvUpOffset                        :  4;  // Bits 7:4
    INT32  RcompDrvDownOffset                      :  4;  // Bits 11:8
    UINT32 ClkCompOnTheFlyUpdtEn                   :  1;  // Bits 12:12
    UINT32 Spare                                   :  19;  // Bits 31:13
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 Spare                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH0_CR_DDR4CRBSCANDATA_STRUCT;

typedef union {
  struct {
    UINT32 CRVALID                                 :  1;  // Bits 0:0
    UINT32 GVPointG2                               :  2;  // Bits 2:1
    UINT32 ReplicaOffsetUse                        :  1;  // Bits 3:3
    UINT32 VTCompOffsetUse                         :  2;  // Bits 5:4
    UINT32 ExtOffset                               :  7;  // Bits 12:6
    UINT32 BiasOffset                              :  15;  // Bits 27:13
    UINT32 ActiveRanks                             :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH0_CR_DCCCLKCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 DccCodeOvrd                             :  6;  // Bits 5:0
    UINT32 Rank0DccAipCb                           :  2;  // Bits 7:6
    UINT32 DccPtrOvrd                              :  4;  // Bits 11:8
    UINT32 RnkPtrOvrd                              :  2;  // Bits 13:12
    UINT32 DcdDigEnOvrd                            :  1;  // Bits 14:14
    UINT32 DcdAnaEnOvrd                            :  1;  // Bits 15:15
    UINT32 DcdWindow                               :  15;  // Bits 30:16
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH0_CR_DCCCLKCONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 StartBinCode                            :  6;  // Bits 5:0
    UINT32 CodePtrStartBit                         :  3;  // Bits 8:6
    UINT32 DccTrshOld                              :  13;  // Bits 21:9
    UINT32 DcdCntsStartDiff                        :  5;  // Bits 26:22
    UINT32 ClkGateDisable                          :  1;  // Bits 27:27
    UINT32 DccClkViewSelect0                       :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH0_CR_DCCCLKCONTROL2_STRUCT;

typedef union {
  struct {
    UINT32 ActiveDccRank0                          :  11;  // Bits 10:0
    UINT32 ActiveDccRank1                          :  9;  // Bits 19:11
    UINT32 ActiveDccRank2                          :  9;  // Bits 28:20
    UINT32 clkdccupdateoldpath                     :  1;  // Bits 29:29
    UINT32 clkdcccfgbypass                         :  1;  // Bits 30:30
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH0_CR_DCCCLKCONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 ActiveDccRank3                          :  9;  // Bits 8:0
    UINT32 Spare                                   :  1;  // Bits 9:9
    UINT32 ReplicaPrev_GVp0                        :  6;  // Bits 15:10
    UINT32 ReplicaPrev_GVp1                        :  6;  // Bits 21:16
    UINT32 ReplicaPrev_GVp2                        :  6;  // Bits 27:22
    UINT32 DccClkViewSelect1                       :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH0_CR_DCCCLKCONTROL4_STRUCT;

typedef union {
  struct {
    UINT32 dccclkupdtstepsize                      :  2;  // Bits 1:0
    UINT32 vtcompoffsetmsgwren                     :  1;  // Bits 2:2
    UINT32 ReplicaPrev_GVp3                        :  6;  // Bits 8:3
    UINT32 BubbleCntVal                            :  5;  // Bits 13:9
    UINT32 DeterministicSyncVal                    :  6;  // Bits 19:14
    UINT32 DeterministicCntVal                     :  11;  // Bits 30:20
    UINT32 DeterministicMode                       :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH0_CR_DCCCLKCONTROL5_STRUCT;

typedef union {
  struct {
    UINT32 ClkDccDone                              :  3;  // Bits 2:0
    UINT32 Spare                                   :  29;  // Bits 31:3
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH0_CR_DCCCLKTRAINSTATUS0_STRUCT;

typedef union {
  struct {
    UINT32 Spare0                                  :  10;  // Bits 9:0
    UINT32 CntDone                                 :  1;  // Bits 10:10
    UINT32 Dcd_O_Cnt                               :  15;  // Bits 25:11
    UINT32 Spare1                                  :  1;  // Bits 26:26
    UINT32 BinFsmCurrState                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH0_CR_DCCCLKTRAINSTATUS1_STRUCT;

typedef union {
  struct {
    UINT32 AuxCnt                                  :  16;  // Bits 15:0
    UINT32 ReplicaOffset                           :  7;  // Bits 22:16
    UINT32 VTCompOffset                            :  7;  // Bits 29:23
    UINT32 Spare                                   :  1;  // Bits 30:30
    UINT32 CRVALID                                 :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH0_CR_DCCCLKTRAINSTATUS2_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  11;  // Bits 10:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 27:11
    UINT32 Spare                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH0_CR_DCCCLKTRAINERRSTATUS_STRUCT;

typedef union {
  struct {
    UINT32 ReplicaTrain_GVp0                       :  6;  // Bits 5:0
    UINT32 ReplicaTrain_GVp1                       :  6;  // Bits 11:6
    UINT32 ReplicaTrain_GVp2                       :  6;  // Bits 17:12
    UINT32 ReplicaTrain_GVp3                       :  6;  // Bits 23:18
    UINT32 ReplicaOffsetPrev                       :  7;  // Bits 30:24
    UINT32 CRVALID                                 :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH0_CR_DCCCLKTRAINREPLICA0_STRUCT;

typedef union {
  struct {
    UINT32 Clk0DccVal                              :  6;  // Bits 5:0
    UINT32 Clk1DccVal                              :  6;  // Bits 11:6
    UINT32 Spare                                   :  17;  // Bits 28:12
    UINT32 CRVALID                                 :  1;  // Bits 29:29
    UINT32 Rank1DccAipCb                           :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH0_CR_DCCCLKTRAINVAL0_STRUCT;

typedef union {
  struct {
    UINT32 ReplicaShadowDccVal                     :  6;  // Bits 5:0
    UINT32 Spare                                   :  20;  // Bits 25:6
    UINT32 binfsmsteptosavecnts                    :  3;  // Bits 28:26
    UINT32 savecntsatchosenbinstep                 :  1;  // Bits 29:29
    UINT32 RepDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH0_CR_DCCCLKTRAINVAL1_STRUCT;

typedef union {
  struct {
    UINT32 ClkTcoComp                              :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH0_CR_DDRCRCLKTCOCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 CtlCkTxEn                               :  8;  // Bits 7:0
    UINT32 PiClkEn                                 :  4;  // Bits 11:8
    UINT32 DdrCtlCkeSlwDlyByp                      :  1;  // Bits 12:12
    UINT32 cs_all_clk_gate_dis                     :  1;  // Bits 13:13
    UINT32 CsClkGateDis_in_idle                    :  1;  // Bits 14:14
    UINT32 CsPiClkGateEn                           :  2;  // Bits 16:15
    UINT32 CsOdtForCS_ODT_1                        :  1;  // Bits 17:17
    UINT32 CsOdtForCS_ODT_0                        :  1;  // Bits 18:18
    UINT32 CsOdtForCS_N_3                          :  1;  // Bits 19:19
    UINT32 CsOdtForCS_N_2                          :  1;  // Bits 20:20
    UINT32 CsOdtForCS_N_1                          :  1;  // Bits 21:21
    UINT32 CsOdtForCS_N_0                          :  1;  // Bits 22:22
    UINT32 Gear1                                   :  1;  // Bits 23:23
    UINT32 lp4xvoltageselect                       :  1;  // Bits 24:24
    UINT32 xover_mindelay_ctl                      :  2;  // Bits 26:25
    UINT32 ClkSlewDlyByPass                        :  1;  // Bits 27:27
    UINT32 CtlCriClkGateEnGvBlock                  :  1;  // Bits 28:28
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH1_CR_DDRCRCTLRANKSUSED_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  6;  // Bits 5:0
    UINT32 RcompDrvUp                              :  6;  // Bits 11:6
    UINT32 RcompDrvDown                            :  6;  // Bits 17:12
    UINT32 Spare                                   :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH1_CR_DDRCRCTLCOMP_STRUCT;

typedef union {
  struct {
    INT32  ScompOffset                             :  5;  // Bits 4:0
    INT32  RcompDrvUpOffset                        :  4;  // Bits 8:5
    INT32  RcompDrvDownOffset                      :  4;  // Bits 12:9
    UINT32 Spare                                   :  19;  // Bits 31:13
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 CtlPiCode0                              :  7;  // Bits 6:0
    UINT32 CtlPiCode1                              :  7;  // Bits 13:7
    UINT32 CtlPiCode2                              :  7;  // Bits 20:14
    UINT32 CtlPiCode3                              :  7;  // Bits 27:21
    UINT32 CtlXoverEnable                          :  1;  // Bits 28:28
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH1_CR_DDRCRCTLPICODING_STRUCT;

typedef union {
  struct {
    INT32  RefPi                                   :  4;  // Bits 3:0
    UINT32 DllMask                                 :  2;  // Bits 5:4
    UINT32 ClkGateDisable                          :  1;  // Bits 6:6
    UINT32 TxOn                                    :  1;  // Bits 7:7
    UINT32 IntClkOn                                :  1;  // Bits 8:8
    UINT32 RepClkOn                                :  1;  // Bits 9:9
    UINT32 IolbOrMisr                              :  1;  // Bits 10:10
    UINT32 IOLBHold                                :  1;  // Bits 11:11
    UINT32 OdtMode                                 :  1;  // Bits 12:12
    UINT32 CmdTxEq                                 :  2;  // Bits 14:13
    UINT32 EarlyWeakDrive                          :  2;  // Bits 16:15
    UINT32 CtlTxEq                                 :  2;  // Bits 18:17
    UINT32 CtlSRDrv                                :  2;  // Bits 20:19
    INT32  RxVref                                  :  6;  // Bits 26:21
    UINT32 VccddqHi                                :  1;  // Bits 27:27
    UINT32 DllWeakLock                             :  1;  // Bits 28:28
    UINT32 CMD_Rate                                :  1;  // Bits 29:29
    UINT32 LaDrvEnOvrd                             :  1;  // Bits 30:30
    UINT32 ma3_ma4_par_dis                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH1_CR_DDRCRCTLCONTROLS_STRUCT;

typedef union {
  struct {
    INT32  RxVref                                  :  8;  // Bits 7:0
    UINT32 MapCkeForScOdt                          :  18;  // Bits 25:8
    UINT32 CMDLowsupEn                             :  1;  // Bits 26:26
    UINT32 CKELowsupEn                             :  1;  // Bits 27:27
    UINT32 CTLLowsupEn                             :  1;  // Bits 28:28
    UINT32 CLKLowsupEn                             :  1;  // Bits 29:29
    UINT32 en_sr_mode_to_cke                       :  1;  // Bits 30:30
    UINT32 c3segsel_b_for_cke                      :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH1_CR_DDRCRCTLCONTROLS1_STRUCT;

typedef union {
  struct {
    UINT32 datatrainfeedback                       :  10;  // Bits 9:0
    UINT32 Spare                                   :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH1_CR_DDRCRLOOPBACKFEEDBACK_STRUCT;

typedef union {
  struct {
    UINT32 shift_16                                :  1;  // Bits 0:0
    UINT32 clken_pulse_mode                        :  1;  // Bits 1:1
    UINT32 reg_clken_mode                          :  1;  // Bits 2:2
    UINT32 reg_clken                               :  1;  // Bits 3:3
    UINT32 feedback_en                             :  1;  // Bits 4:4
    UINT32 event_mode                              :  1;  // Bits 5:5
    UINT32 lfsr_reset                              :  1;  // Bits 6:6
    UINT32 sdo_en                                  :  1;  // Bits 7:7
    UINT32 reserved0                               :  8;  // Bits 15:8
    UINT32 cr_rd_data                              :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH1_CR_DDRCMDMISR_STRUCT;

typedef union {
  struct {
    UINT32 CtlTcoComp                              :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCH1_CR_DDRCRCTLTCOCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  5;  // Bits 4:0
    UINT32 RcompDrvUp                              :  6;  // Bits 10:5
    UINT32 RcompDrvDown                            :  6;  // Bits 16:11
    UINT32 Spare                                   :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH1_CR_DDRCRCLKCOMP_STRUCT;

typedef union {
  struct {
    INT32  ScompOffset                             :  4;  // Bits 3:0
    INT32  RcompDrvUpOffset                        :  4;  // Bits 7:4
    INT32  RcompDrvDownOffset                      :  4;  // Bits 11:8
    UINT32 ClkCompOnTheFlyUpdtEn                   :  1;  // Bits 12:12
    UINT32 Spare                                   :  19;  // Bits 31:13
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 Spare                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH1_CR_DDR4CRBSCANDATA_STRUCT;

typedef union {
  struct {
    UINT32 CRVALID                                 :  1;  // Bits 0:0
    UINT32 GVPointG2                               :  2;  // Bits 2:1
    UINT32 ReplicaOffsetUse                        :  1;  // Bits 3:3
    UINT32 VTCompOffsetUse                         :  2;  // Bits 5:4
    UINT32 ExtOffset                               :  7;  // Bits 12:6
    UINT32 BiasOffset                              :  15;  // Bits 27:13
    UINT32 ActiveRanks                             :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH1_CR_DCCCLKCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 DccCodeOvrd                             :  6;  // Bits 5:0
    UINT32 Rank0DccAipCb                           :  2;  // Bits 7:6
    UINT32 DccPtrOvrd                              :  4;  // Bits 11:8
    UINT32 RnkPtrOvrd                              :  2;  // Bits 13:12
    UINT32 DcdDigEnOvrd                            :  1;  // Bits 14:14
    UINT32 DcdAnaEnOvrd                            :  1;  // Bits 15:15
    UINT32 DcdWindow                               :  15;  // Bits 30:16
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH1_CR_DCCCLKCONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 StartBinCode                            :  6;  // Bits 5:0
    UINT32 CodePtrStartBit                         :  3;  // Bits 8:6
    UINT32 DccTrshOld                              :  13;  // Bits 21:9
    UINT32 DcdCntsStartDiff                        :  5;  // Bits 26:22
    UINT32 ClkGateDisable                          :  1;  // Bits 27:27
    UINT32 DccClkViewSelect0                       :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH1_CR_DCCCLKCONTROL2_STRUCT;

typedef union {
  struct {
    UINT32 ActiveDccRank0                          :  11;  // Bits 10:0
    UINT32 ActiveDccRank1                          :  9;  // Bits 19:11
    UINT32 ActiveDccRank2                          :  9;  // Bits 28:20
    UINT32 clkdccupdateoldpath                     :  1;  // Bits 29:29
    UINT32 clkdcccfgbypass                         :  1;  // Bits 30:30
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH1_CR_DCCCLKCONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 ActiveDccRank3                          :  9;  // Bits 8:0
    UINT32 Spare                                   :  1;  // Bits 9:9
    UINT32 ReplicaPrev_GVp0                        :  6;  // Bits 15:10
    UINT32 ReplicaPrev_GVp1                        :  6;  // Bits 21:16
    UINT32 ReplicaPrev_GVp2                        :  6;  // Bits 27:22
    UINT32 DccClkViewSelect1                       :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH1_CR_DCCCLKCONTROL4_STRUCT;

typedef union {
  struct {
    UINT32 dccclkupdtstepsize                      :  2;  // Bits 1:0
    UINT32 vtcompoffsetmsgwren                     :  1;  // Bits 2:2
    UINT32 ReplicaPrev_GVp3                        :  6;  // Bits 8:3
    UINT32 BubbleCntVal                            :  5;  // Bits 13:9
    UINT32 DeterministicSyncVal                    :  6;  // Bits 19:14
    UINT32 DeterministicCntVal                     :  11;  // Bits 30:20
    UINT32 DeterministicMode                       :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH1_CR_DCCCLKCONTROL5_STRUCT;

typedef union {
  struct {
    UINT32 ClkDccDone                              :  3;  // Bits 2:0
    UINT32 Spare                                   :  29;  // Bits 31:3
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH1_CR_DCCCLKTRAINSTATUS0_STRUCT;

typedef union {
  struct {
    UINT32 Spare0                                  :  10;  // Bits 9:0
    UINT32 CntDone                                 :  1;  // Bits 10:10
    UINT32 Dcd_O_Cnt                               :  15;  // Bits 25:11
    UINT32 Spare1                                  :  1;  // Bits 26:26
    UINT32 BinFsmCurrState                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH1_CR_DCCCLKTRAINSTATUS1_STRUCT;

typedef union {
  struct {
    UINT32 AuxCnt                                  :  16;  // Bits 15:0
    UINT32 ReplicaOffset                           :  7;  // Bits 22:16
    UINT32 VTCompOffset                            :  7;  // Bits 29:23
    UINT32 Spare                                   :  1;  // Bits 30:30
    UINT32 CRVALID                                 :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH1_CR_DCCCLKTRAINSTATUS2_STRUCT;

typedef union {
  struct {
    UINT32 DccConvergeErr                          :  11;  // Bits 10:0
    UINT32 MaxConvergeErr                          :  17;  // Bits 27:11
    UINT32 Spare                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH1_CR_DCCCLKTRAINERRSTATUS_STRUCT;

typedef union {
  struct {
    UINT32 ReplicaTrain_GVp0                       :  6;  // Bits 5:0
    UINT32 ReplicaTrain_GVp1                       :  6;  // Bits 11:6
    UINT32 ReplicaTrain_GVp2                       :  6;  // Bits 17:12
    UINT32 ReplicaTrain_GVp3                       :  6;  // Bits 23:18
    UINT32 ReplicaOffsetPrev                       :  7;  // Bits 30:24
    UINT32 CRVALID                                 :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH1_CR_DCCCLKTRAINREPLICA0_STRUCT;

typedef union {
  struct {
    UINT32 Clk0DccVal                              :  6;  // Bits 5:0
    UINT32 Clk1DccVal                              :  6;  // Bits 11:6
    UINT32 Spare                                   :  17;  // Bits 28:12
    UINT32 CRVALID                                 :  1;  // Bits 29:29
    UINT32 Rank1DccAipCb                           :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH1_CR_DCCCLKTRAINVAL0_STRUCT;

typedef union {
  struct {
    UINT32 ReplicaShadowDccVal                     :  6;  // Bits 5:0
    UINT32 Spare                                   :  20;  // Bits 25:6
    UINT32 binfsmsteptosavecnts                    :  3;  // Bits 28:26
    UINT32 savecntsatchosenbinstep                 :  1;  // Bits 29:29
    UINT32 RepDccAipCb                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH1_CR_DCCCLKTRAINVAL1_STRUCT;

typedef union {
  struct {
    UINT32 ClkTcoComp                              :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCLKCH1_CR_DDRCRCLKTCOCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 RcompDrvUp                              :  6;  // Bits 5:0
    UINT32 Rsvd                                    :  8;  // Bits 13:6
    UINT32 RcompDrvDown                            :  6;  // Bits 19:14
    UINT32 SlewRateComp                            :  5;  // Bits 24:20
    UINT32 Spare                                   :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPHY_COMP_CR_DDRCRDATACOMP0_STRUCT;

typedef union {
  struct {
    UINT32 RcompOdtUp                              :  6;  // Bits 5:0
    UINT32 spare                                   :  20;  // Bits 25:6
    UINT32 RcompOdtDown                            :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPHY_COMP_CR_DDRCRDATACOMP1_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  6;  // Bits 5:0
    UINT32 RcompDrvUp                              :  6;  // Bits 11:6
    UINT32 RcompDrvDown                            :  6;  // Bits 17:12
    UINT32 Spare                                   :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPHY_COMP_CR_DDRCRCMDCOMP_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  6;  // Bits 5:0
    UINT32 RcompDrvUp                              :  6;  // Bits 11:6
    UINT32 RcompDrvDown                            :  6;  // Bits 17:12
    UINT32 Spare                                   :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPHY_COMP_CR_DDRCRCTLCOMP_STRUCT;

typedef union {
  struct {
    UINT32 Scomp                                   :  5;  // Bits 4:0
    UINT32 RcompDrvUp                              :  6;  // Bits 10:5
    UINT32 RcompDrvDown                            :  6;  // Bits 16:11
    UINT32 Spare                                   :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPHY_COMP_CR_DDRCRCLKCOMP_STRUCT;

typedef union {
  struct {
    UINT32 En200ohmVsshiPncUp                      :  1;  // Bits 0:0
    UINT32 Spare0                                  :  1;  // Bits 1:1
    UINT32 DisableCompRotate                       :  1;  // Bits 2:2
    UINT32 DisableOdtStatic                        :  1;  // Bits 3:3
    UINT32 DqOdtUpDnOff                            :  6;  // Bits 9:4
    UINT32 FixOdtD                                 :  1;  // Bits 10:10
    UINT32 DqDrvVref                               :  8;  // Bits 18:11
    UINT32 DqOdtVref                               :  8;  // Bits 26:19
    UINT32 Spare1                                  :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPHY_COMP_CR_DDRCRCOMPCTL0_STRUCT;

typedef union {
  struct {
    UINT32 DqScompCells                            :  4;  // Bits 3:0
    UINT32 DqScompPC                               :  1;  // Bits 4:4
    UINT32 CmdScompCells                           :  4;  // Bits 8:5
    UINT32 CmdScompPC                              :  1;  // Bits 9:9
    UINT32 CtlScompCells                           :  4;  // Bits 13:10
    UINT32 CtlScompPC                              :  1;  // Bits 14:14
    UINT32 ClkScompCells                           :  4;  // Bits 18:15
    UINT32 ClkScompPC                              :  1;  // Bits 19:19
    UINT32 CompClkOn                               :  1;  // Bits 20:20
    UINT32 Spare                                   :  5;  // Bits 25:21
    UINT32 VccddqLo                                :  1;  // Bits 26:26
    UINT32 DqRcompStatLegs                         :  2;  // Bits 28:27
    UINT32 DisableQuickComp                        :  1;  // Bits 29:29
    UINT32 SinStep                                 :  1;  // Bits 30:30
    UINT32 SinStepAdv                              :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPHY_COMP_CR_DDRCRCOMPCTL1_STRUCT;

typedef union {
  struct {
    UINT32 Spare1                                  :  6;  // Bits 5:0
    UINT32 VtOffset                                :  5;  // Bits 10:6
    UINT32 VtSlopeA                                :  3;  // Bits 13:11
    UINT32 VtSlopeB                                :  3;  // Bits 16:14
    UINT32 PanicCompUpMult                         :  7;  // Bits 23:17
    UINT32 PanicCompDnMult                         :  7;  // Bits 30:24
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPHY_COMP_CR_DDRCRCOMPVSSHI_STRUCT;

typedef union {
  struct {
    UINT32 DqDrvU                                  :  1;  // Bits 0:0
    UINT32 DqDrvD                                  :  1;  // Bits 1:1
    UINT32 DqOdtU                                  :  1;  // Bits 2:2
    UINT32 DqOdtD                                  :  1;  // Bits 3:3
    UINT32 CmdDrvU                                 :  1;  // Bits 4:4
    UINT32 CmdDrvD                                 :  1;  // Bits 5:5
    UINT32 CtlDrvU                                 :  1;  // Bits 6:6
    UINT32 CtlDrvD                                 :  1;  // Bits 7:7
    UINT32 ClkDrvU                                 :  1;  // Bits 8:8
    UINT32 ClkDrvD                                 :  1;  // Bits 9:9
    UINT32 DqSR                                    :  1;  // Bits 10:10
    UINT32 CmdSR                                   :  1;  // Bits 11:11
    UINT32 CtlSR                                   :  1;  // Bits 12:12
    UINT32 ClkSR                                   :  1;  // Bits 13:13
    UINT32 Spare                                   :  6;  // Bits 19:14
    UINT32 CmdDn200                                :  1;  // Bits 20:20
    UINT32 PanicDrvUp                              :  1;  // Bits 21:21
    UINT32 PanicDrvDn                              :  1;  // Bits 22:22
    UINT32 VTComp                                  :  1;  // Bits 23:23
    UINT32 LsComp                                  :  3;  // Bits 26:24
    UINT32 PanicVttUp                              :  1;  // Bits 27:27
    UINT32 PanicVttDn                              :  1;  // Bits 28:28
    UINT32 RcompCheckEn                            :  1;  // Bits 29:29
    UINT32 RcompSwapEn                             :  1;  // Bits 30:30
    UINT32 VtDmVrefFsm                             :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPHY_COMP_CR_DDRCRCOMPOVR_STRUCT;

typedef union {
  struct {
    UINT32 EnVddqOdt                               :  1;  // Bits 0:0
    UINT32 EnVttOdt                                :  1;  // Bits 1:1
    UINT32 Spare                                   :  6;  // Bits 7:2
    UINT32 VttPanicCompUpMult                      :  4;  // Bits 11:8
    UINT32 VttPanicCompDnMult                      :  5;  // Bits 16:12
    UINT32 DisableFallingPD                        :  1;  // Bits 17:17
    UINT32 SinStepAdvBin                           :  1;  // Bits 18:18
    UINT32 SinStepBin                              :  1;  // Bits 19:19
    UINT32 CMDLowsupEn                             :  1;  // Bits 20:20
    UINT32 CTLLowsupEn                             :  1;  // Bits 21:21
    UINT32 DQDQSLowsupEn                           :  1;  // Bits 22:22
    UINT32 CLKLowsupEn                             :  1;  // Bits 23:23
    UINT32 PanicDrvUpVref                          :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPHY_COMP_CR_DDRCRCOMPCTL2_STRUCT;

typedef union {
  struct {
    UINT32 PanicVttUp                              :  8;  // Bits 7:0
    UINT32 PanicVttDn                              :  8;  // Bits 15:8
    UINT32 RcompCmdDn200ohm                        :  6;  // Bits 21:16
    UINT32 Spare                                   :  10;  // Bits 31:22
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPHY_COMP_CR_DDRCRDATACOMP2_STRUCT;

typedef union {
  struct {
    UINT32 DqRcompDrvUp_Previous                   :  6;  // Bits 5:0
    UINT32 DqRcompDrvDn_Previous                   :  6;  // Bits 11:6
    UINT32 OdtRcompDrvUp_Previous                  :  6;  // Bits 17:12
    UINT32 OdtRcompDrvDn_Previous                  :  6;  // Bits 23:18
    UINT32 ClkRcompDrvUp_Previous                  :  6;  // Bits 29:24
    UINT32 Rcomp_DriftLimit                        :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPHY_COMP_CR_DDRCRCOMPDEBUG0_STRUCT;

typedef union {
  struct {
    UINT32 ClkRcompDrvDn_Previous                  :  6;  // Bits 5:0
    UINT32 CmdRcompDrvUp_Previous                  :  6;  // Bits 11:6
    UINT32 CmdRcompDrvDn_Previous                  :  6;  // Bits 17:12
    UINT32 CtlRcompDrvUp_Previous                  :  6;  // Bits 23:18
    UINT32 CtlRcompDrvDn_Previous                  :  6;  // Bits 29:24
    UINT32 Drift_detected                          :  1;  // Bits 30:30
    UINT32 Spare                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPHY_COMP_CR_DDRCRCOMPDEBUG1_STRUCT;

typedef union {
  struct {
    UINT32 DDRIORssRcompDef                        :  6;  // Bits 5:0
    UINT32 DDRIORttRcompDef                        :  6;  // Bits 11:6
    UINT32 Spare                                   :  20;  // Bits 31:12
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPHY_COMP_CR_DDRCRDIGVIEWRCOMPCTL_STRUCT;

typedef union {
  struct {
    UINT32 CmdDrvVref                              :  8;  // Bits 7:0
    UINT32 CtlDrvVref                              :  8;  // Bits 15:8
    UINT32 ClkDrvVref                              :  8;  // Bits 23:16
    UINT32 CmdDrvVrefForVttPanicComp               :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPHY_COMP_CR_DDRCRCOMPCTL3_STRUCT;

typedef union {
  struct {
    UINT32 PanicDrvDn                              :  10;  // Bits 9:0
    UINT32 PanicDrvUp                              :  10;  // Bits 19:10
    UINT32 VTComp                                  :  5;  // Bits 24:20
    UINT32 spare                                   :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPHY_COMP_CR_DDRCRVSSICOMP_STRUCT;

typedef union {
  struct {
    UINT32 VTComp                                  :  6;  // Bits 5:0
    UINT32 NxtVTCompValidForDcc                    :  1;  // Bits 6:6
    UINT32 CompLoopsNumForDcc                      :  5;  // Bits 11:7
    UINT32 ActivateCompLoopsCntForDcc              :  1;  // Bits 12:12
    UINT32 KfactorForDccVtCompOffsetCalc           :  2;  // Bits 14:13
    UINT32 Spare                                   :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPHY_COMP_CR_DDRCRDMVREFCOMP_STRUCT;

typedef union {
  struct {
    UINT32 CmdDrvVrefDn                            :  8;  // Bits 7:0
    UINT32 CtlDrvVrefDn                            :  8;  // Bits 15:8
    UINT32 ClkDrvVrefDn                            :  8;  // Bits 23:16
    UINT32 DqDrvVrefDn                             :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPHY_COMP_CR_DDRCRCOMPCTL4_STRUCT;

typedef union {
  struct {
    UINT32 DqOdtVrefDn                             :  8;  // Bits 7:0
    UINT32 view_pins_status                        :  2;  // Bits 9:8
    UINT32 Lp4xVoltageSelect                       :  1;  // Bits 10:10
    UINT32 VttTargetCode1stLevel                   :  5;  // Bits 15:11
    UINT32 VttTargetCode2ndLevel                   :  3;  // Bits 18:16
    UINT32 Spare                                   :  13;  // Bits 31:19
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPHY_COMP_CR_DDRCRCOMPCTL5_STRUCT;

typedef union {
  struct {
    UINT32 PreLfsrDiv                              :  2;  // Bits 1:0
    UINT32 PostDivInitVal                          :  4;  // Bits 5:2
    UINT32 PreDiv                                  :  2;  // Bits 7:6
    UINT32 PostDiv                                 :  4;  // Bits 11:8
    UINT32 PostDivCntWindow                        :  11;  // Bits 22:12
    UINT32 Spare                                   :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPHY_COMP_CR_DCCDCOCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 PreDivCntWindow                         :  11;  // Bits 10:0
    UINT32 RefCntWindow                            :  12;  // Bits 22:11
    UINT32 DcoViewSelect0                          :  4;  // Bits 26:23
    UINT32 DcoViewSelect1                          :  4;  // Bits 30:27
    UINT32 ClkGateDisable                          :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPHY_COMP_CR_DCCDCOCONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 RefCntDone                              :  1;  // Bits 0:0
    UINT32 PreDivCntDone                           :  1;  // Bits 1:1
    UINT32 PostDivCntDone                          :  1;  // Bits 2:2
    UINT32 PreDivCnt                               :  11;  // Bits 13:3
    UINT32 PostDivCnt                              :  11;  // Bits 24:14
    UINT32 PreDivErr                               :  1;  // Bits 25:25
    UINT32 PostDivErr                              :  1;  // Bits 26:26
    UINT32 CurrState                               :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPHY_COMP_CR_DCCDCOSTATUS0_STRUCT;

typedef union {
  struct {
    UINT32 RefCnt                                  :  12;  // Bits 11:0
    UINT32 VTCompOffset                            :  7;  // Bits 18:12
    UINT32 VTCompOffsetDone                        :  1;  // Bits 19:19
    UINT32 VTCompXLoopsDone                        :  1;  // Bits 20:20
    UINT32 Spare                                   :  11;  // Bits 31:21
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPHY_COMP_CR_DCCDCOSTATUS1_STRUCT;

typedef union {
  struct {
    UINT32 DcoEnOvrd                               :  1;  // Bits 0:0
    UINT32 PreDivCntEnOvrd                         :  1;  // Bits 1:1
    UINT32 PostDivCntEnOvrd                        :  1;  // Bits 2:2
    UINT32 LfsrEnOvrd                              :  1;  // Bits 3:3
    UINT32 Spare                                   :  10;  // Bits 13:4
    UINT32 DeterministicSyncVal                    :  6;  // Bits 19:14
    UINT32 DeterministicCntVal                     :  11;  // Bits 30:20
    UINT32 DeterministicMode                       :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPHY_COMP_CR_DCCDCOCONTROL2_STRUCT;

#pragma pack(pop)
#endif
