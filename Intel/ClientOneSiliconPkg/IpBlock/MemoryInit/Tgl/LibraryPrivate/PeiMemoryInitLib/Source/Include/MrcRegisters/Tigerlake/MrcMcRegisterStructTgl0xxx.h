#ifndef __MrcMcRegisterStructTgl0xxx_h__
#define __MrcMcRegisterStructTgl0xxx_h__
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
    INT32  TxDqDCCOffset                           :  6;  // Bits 5:0
    UINT32 RxDQPerBitDeskewOffset                  :  4;  // Bits 9:6
    UINT32 RxDQPerBitDeskew                        :  6;  // Bits 15:10
    UINT32 RxDQVrefOffset1                         :  5;  // Bits 20:16
    UINT32 RxDQVrefOffset0                         :  5;  // Bits 25:21
    UINT32 TxDQPerBitDeskew                        :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK0LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK0LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK0LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK0LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK0LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK0LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK0LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK0LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK1LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK1LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK1LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK1LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK1LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK1LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK1LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK1LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK1LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK2LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK2LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK2LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK2LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK2LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK2LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK2LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK2LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK2LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK3LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK3LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK3LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK3LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK3LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK3LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK3LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK3LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH0_CR_DDRDATADQRANK3LANE8_STRUCT;
typedef union {
  struct {
    INT32  TxDQSDCCOffset                          :  7;  // Bits 6:0
    UINT32 RxDQSVrefOffset                         :  5;  // Bits 11:7
    UINT32 TxDQSPerBitDeskew                       :  5;  // Bits 16:12
    UINT32 RxDqsUnMatVrefOffset                    :  5;  // Bits 21:17
    UINT32 DqsPrNfTcoDelay                         :  5;  // Bits 26:22
    UINT32 DqsPfNrTcoDelay                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DDRDATADQSRANK0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA0CH0_CR_DDRDATADQSRANK1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA0CH0_CR_DDRDATADQSRANK2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA0CH0_CR_DDRDATADQSRANK3_STRUCT;
typedef union {
  struct {
    UINT32 RxRcvEnPi                               :  11;  // Bits 10:0
    UINT32 RxDqsPDelayPi                           :  8;  // Bits 18:11
    UINT32 RxDqsNDelayPi                           :  8;  // Bits 26:19
    UINT32 Spare                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_RXCONTROL0RANK0_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA0CH0_CR_RXCONTROL0RANK1_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA0CH0_CR_RXCONTROL0RANK2_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA0CH0_CR_RXCONTROL0RANK3_STRUCT;
typedef union {
  struct {
    UINT32 TxDqDelay                               :  11;  // Bits 10:0
    UINT32 TxDqsDelay                              :  11;  // Bits 21:11
    UINT32 TxEqualization                          :  4;  // Bits 25:22
    UINT32 Spare                                   :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_TXCONTROL0RANK0_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA0CH0_CR_TXCONTROL0RANK1_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA0CH0_CR_TXCONTROL0RANK2_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA0CH0_CR_TXCONTROL0RANK3_STRUCT;
typedef union {
  struct {
    UINT32 RcompDrvUp                              :  6;  // Bits 5:0
    UINT32 RcompDrvDown                            :  6;  // Bits 11:6
    UINT32 VssHiFF                                 :  6;  // Bits 17:12
    UINT32 SlewRateComp                            :  5;  // Bits 22:18
    UINT32 DqsNTargetNUI                           :  2;  // Bits 24:23
    UINT32 DqsNOffsetNUI                           :  2;  // Bits 26:25
    UINT32 RParkOdtDown                            :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_RCOMPDATA0_STRUCT;
typedef union {
  struct {
    UINT32 RcompOdtUp                              :  6;  // Bits 5:0
    UINT32 RcompOdtDown                            :  6;  // Bits 11:6
    UINT32 RxDqsDelayN                             :  8;  // Bits 19:12
    UINT32 RxDqsDelayP                             :  8;  // Bits 27:20
    UINT32 DqsPTargetNUI                           :  2;  // Bits 29:28
    UINT32 DqsPOffsetNUI                           :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_RCOMPDATA1_STRUCT;
typedef union {
  struct {
    UINT32 PanicVttDn0                             :  8;  // Bits 7:0
    UINT32 PanicVttDn1                             :  8;  // Bits 15:8
    UINT32 PanicVttUp0                             :  8;  // Bits 23:16
    UINT32 PanicVttUp1                             :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DATACOMPVTT_STRUCT;
typedef union {
  struct {
    UINT32 RankOvrd                                :  1;  // Bits 0:0
    UINT32 RankValue                               :  2;  // Bits 2:1
    UINT32 RxAmpOffsetEn                           :  2;  // Bits 4:3
    UINT32 RxTrainingMode                          :  1;  // Bits 5:5
    UINT32 WLTrainingMode                          :  2;  // Bits 7:6
    UINT32 RLTrainingMode                          :  1;  // Bits 8:8
    UINT32 SenseampTrainingMode                    :  1;  // Bits 9:9
    UINT32 CATrainingMode                          :  1;  // Bits 10:10
    UINT32 DqsRFTrainingMode                       :  1;  // Bits 11:11
    UINT32 DataTrainFeedback                       :  10;  // Bits 21:12
    UINT32 CAParityTrain                           :  1;  // Bits 22:22
    UINT32 CAParityOdd                             :  1;  // Bits 23:23
    UINT32 LPDDR5                                  :  1;  // Bits 24:24
    UINT32 Spare                                   :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DATATRAINFEEDBACK_STRUCT;
typedef union {
  struct {
    INT32  DqDrvUpCompOffset                       :  6;  // Bits 5:0
    INT32  DqDrvDownCompOffset                     :  6;  // Bits 11:6
    INT32  DqOdtCompOffset                         :  5;  // Bits 16:12
    INT32  VssHiFFCompOffset                       :  5;  // Bits 21:17
    INT32  DqSlewRateCompOffset                    :  5;  // Bits 26:22
    INT32  RloadOffset                             :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT;
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
} DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_STRUCT;
typedef union {
  struct {
    UINT32 tx_clock_on_with_txanalogen             :  1;  // Bits 0:0
    UINT32 local_gate_d0tx                         :  1;  // Bits 1:1
    UINT32 DqsOdtVss                               :  1;  // Bits 2:2
    UINT32 InternalClocksOn                        :  1;  // Bits 3:3
    UINT32 RepeaterClocksOn                        :  1;  // Bits 4:4
    UINT32 WlLongDelEn                             :  1;  // Bits 5:5
    UINT32 TxDeskewForceOn                         :  1;  // Bits 6:6
    UINT32 TxPiOn                                  :  1;  // Bits 7:7
    UINT32 TxOn                                    :  1;  // Bits 8:8
    UINT32 TxDisable                               :  1;  // Bits 9:9
    UINT32 EnDqOdtParkMode                         :  1;  // Bits 10:10
    UINT32 EnDqsOdtParkMode                        :  2;  // Bits 12:11
    UINT32 BiasPMCtrl                              :  2;  // Bits 14:13
    UINT32 VrefPMCtrl                              :  2;  // Bits 16:15
    UINT32 RxDisable                               :  1;  // Bits 17:17
    UINT32 ForceRxOn                               :  1;  // Bits 18:18
    UINT32 RxMode                                  :  2;  // Bits 20:19
    UINT32 DqsNParkLowVoh                          :  1;  // Bits 21:21
    UINT32 OdtForceQDrvEn                          :  1;  // Bits 22:22
    UINT32 OdtSampOff                              :  1;  // Bits 23:23
    UINT32 DisableOdtStatic                        :  1;  // Bits 24:24
    UINT32 DdrCRForceODTOn                         :  1;  // Bits 25:25
    UINT32 OdtMode                                 :  2;  // Bits 27:26
    UINT32 TxRankMuxDelay                          :  4;  // Bits 31:28
  } Bits;
  struct {
    UINT32 tx_clock_on_with_txanalogen             :  1;  // Bits 0:0
    UINT32 local_gate_d0tx                         :  1;  // Bits 1:1
    UINT32 Spare                                   :  1;  // Bits 2:2
    UINT32 InternalClocksOn                        :  1;  // Bits 3:3
    UINT32 RepeaterClocksOn                        :  1;  // Bits 4:4
    UINT32 WlLongDelEn                             :  1;  // Bits 5:5
    UINT32 TxDeskewForceOn                         :  1;  // Bits 6:6
    UINT32 TxPiOn                                  :  1;  // Bits 7:7
    UINT32 TxOn                                    :  1;  // Bits 8:8
    UINT32 TxDisable                               :  1;  // Bits 9:9
    UINT32 EnDqOdtParkMode                         :  1;  // Bits 10:10
    UINT32 EnDqsOdtParkMode                        :  2;  // Bits 12:11
    UINT32 BiasPMCtrl                              :  2;  // Bits 14:13
    UINT32 VrefPMCtrl                              :  2;  // Bits 16:15
    UINT32 RxDisable                               :  1;  // Bits 17:17
    UINT32 ForceRxOn                               :  1;  // Bits 18:18
    UINT32 RxMode                                  :  2;  // Bits 20:19
    UINT32 DqsNParkLowVoh                          :  1;  // Bits 21:21
    UINT32 OdtForceQDrvEn                          :  1;  // Bits 22:22
    UINT32 OdtSampOff                              :  1;  // Bits 23:23
    UINT32 DisableOdtStatic                        :  1;  // Bits 24:24
    UINT32 DdrCRForceODTOn                         :  1;  // Bits 25:25
    UINT32 OdtMode                                 :  2;  // Bits 27:26
    UINT32 TxRankMuxDelay                          :  4;  // Bits 31:28
  } A0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DDRCRDATACONTROL0_STRUCT;
typedef union {
  struct {
    UINT32 RXDeskewForceOn                         :  1;  // Bits 0:0
    UINT32 SdllSegmentDisable                      :  4;  // Bits 4:1
    UINT32 DqsOdtDelay                             :  6;  // Bits 10:5
    UINT32 DqsOdtDuration                          :  3;  // Bits 13:11
    UINT32 DqOdtDelay                              :  5;  // Bits 18:14
    UINT32 DqOdtDuration                           :  4;  // Bits 22:19
    UINT32 SenseAmpDelay                           :  5;  // Bits 27:23
    UINT32 SenseAmpDuration                        :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DDRCRDATACONTROL1_STRUCT;
typedef union {
  struct {
    UINT32 RxVrefVddqProgMFC                       :  3;  // Bits 2:0
    UINT32 RxVrefVttProgMFC                        :  3;  // Bits 5:3
    UINT32 RxBurstLen                              :  3;  // Bits 8:6
    UINT32 DqSlewDlyByPass                         :  1;  // Bits 9:9
    UINT32 EnDqsNRcvEn                             :  1;  // Bits 10:10
    UINT32 xover_adjustment_rsvd                   :  4;  // Bits 14:11
    UINT32 xover_mindelay_ctl                      :  2;  // Bits 16:15
    UINT32 DisableDqsOdtStatic                     :  1;  // Bits 17:17
    UINT32 TxPBDCalibration                        :  2;  // Bits 19:18
    UINT32 EnConstZEqTx                            :  1;  // Bits 20:20
    UINT32 TxEqDis                                 :  1;  // Bits 21:21
    UINT32 RxClkStgNum                             :  6;  // Bits 27:22
    UINT32 RxRankMuxDelay                          :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DDRCRDATACONTROL2_STRUCT;
typedef union {
  struct {
    UINT32 Gear1                                   :  1;  // Bits 0:0
    UINT32 VrefBypassVssHi                         :  1;  // Bits 1:1
    UINT32 RxPwrMuxSelVdd2                         :  1;  // Bits 2:2
    UINT32 VrefPwrMuxSelVdd2                       :  1;  // Bits 3:3
    UINT32 RxSALTailCtrl                           :  2;  // Bits 5:4
    UINT32 wrpreamble                              :  3;  // Bits 8:6
    UINT32 RxSALDFEOvrdSel                         :  1;  // Bits 9:9
    UINT32 DbiEnable                               :  1;  // Bits 10:10
    UINT32 DbiMode                                 :  1;  // Bits 11:11
    UINT32 QualifySdlWithRcvEn                     :  1;  // Bits 12:12
    UINT32 rxfoldcs                                :  2;  // Bits 14:13
    UINT32 dqspadmuxselvdd2                        :  1;  // Bits 15:15
    UINT32 TxEq_RankMuxDelay_offset                :  2;  // Bits 17:16
    UINT32 TxPerbit_RankMuxDelay_offset            :  2;  // Bits 19:18
    UINT32 BlockSdlWithRcvEn                       :  1;  // Bits 20:20
    UINT32 RcvEnExtFF                              :  2;  // Bits 22:21
    UINT32 DisableTxDqs                            :  1;  // Bits 23:23
    UINT32 RxRankMuxDelay_2ndStg                   :  2;  // Bits 25:24
    UINT32 RxPBDCalibration                        :  2;  // Bits 27:26
    UINT32 TxDqsRankMuxDelay                       :  4;  // Bits 31:28
  } Bits;
  struct {
    UINT32 Gear1                                   :  1;  // Bits 0:0
    UINT32 VrefBypassVssHi                         :  1;  // Bits 1:1
    UINT32 RxPwrMuxSelVdd2                         :  1;  // Bits 2:2
    UINT32 VrefPwrMuxSelVdd2                       :  1;  // Bits 3:3
    UINT32 RxSALTailCtrl                           :  2;  // Bits 5:4
    UINT32 wrpreamble                              :  3;  // Bits 8:6
    UINT32 RxSALDFEOvrdSel                         :  1;  // Bits 9:9
    UINT32 DbiEnable                               :  1;  // Bits 10:10
    UINT32 DbiMode                                 :  1;  // Bits 11:11
    UINT32 QualifySdlWithRcvEn                     :  1;  // Bits 12:12
    UINT32 rxfoldcs                                :  2;  // Bits 14:13
    UINT32 dqspadmuxselvdd2                        :  1;  // Bits 15:15
    UINT32 TxEq_RankMuxDelay_offset                :  2;  // Bits 17:16
    UINT32 TxPerbit_RankMuxDelay_offset            :  2;  // Bits 19:18
    UINT32 Spare1                                  :  3;  // Bits 22:20
    UINT32 DisableTxDqs                            :  1;  // Bits 23:23
    UINT32 Spare2                                  :  2;  // Bits 25:24
    UINT32 RxPBDCalibration                        :  2;  // Bits 27:26
    UINT32 TxDqsRankMuxDelay                       :  4;  // Bits 31:28
  } A0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DDRCRDATACONTROL3_STRUCT;
typedef union {
  struct {
    UINT32 RxEqRank0                               :  8;  // Bits 7:0
    UINT32 RxEqRank1                               :  8;  // Bits 15:8
    UINT32 RxEqRank2                               :  8;  // Bits 23:16
    UINT32 RxEqRank3                               :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DDRCRDATACONTROL4_STRUCT;
typedef union {
  struct {
    UINT32 TxDqPUpPreDrvVccddq                     :  1;  // Bits 0:0
    UINT32 TxBypassVssHi                           :  1;  // Bits 1:1
    UINT32 DataInvertNibble                        :  2;  // Bits 3:2
    UINT32 RxPiOn                                  :  1;  // Bits 4:4
    UINT32 TxDqPDnPreDrvVccddq                     :  1;  // Bits 5:5
    UINT32 BiasBypassVsxHi                         :  1;  // Bits 6:6
    UINT32 BiasRloadVref                           :  3;  // Bits 9:7
    UINT32 BiasIrefAdj                             :  4;  // Bits 13:10
    UINT32 BiasPwrMuxSelVdd2                       :  1;  // Bits 14:14
    UINT32 BiasCasAdj                              :  2;  // Bits 16:15
    UINT32 ODTSingleSegEn                          :  1;  // Bits 17:17
    UINT32 DqsOdtCompOffset                        :  5;  // Bits 22:18
    UINT32 RxVref                                  :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DDRCRDATACONTROL5_STRUCT;
typedef union {
  struct {
    UINT32 sdllbwctrl                              :  4;  // Bits 3:0
    UINT32 sdll_picb                               :  4;  // Bits 7:4
    UINT32 rxd0picb                                :  4;  // Bits 11:8
    UINT32 rxd0bwctrl                              :  4;  // Bits 15:12
    UINT32 UseDefaultRdPtrCalc                     :  1;  // Bits 16:16
    UINT32 RstNumPre                               :  3;  // Bits 19:17
    UINT32 PassRcvenOnDqsFall                      :  1;  // Bits 20:20
    UINT32 RXTogglePreAmble                        :  2;  // Bits 22:21
    UINT32 RxSALDFEOvrdSel                         :  1;  // Bits 23:23
    UINT32 RcvEnWaveShape                          :  3;  // Bits 26:24
    UINT32 RxReadPointer                           :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DDRCRDATACONTROL6_STRUCT;
typedef union {
  struct {
    UINT32 DdrDqOvrdModeEn                         :  11;  // Bits 10:0
    UINT32 DdrDqOvrdData                           :  11;  // Bits 21:11
    UINT32 DDRCrDqsMaskValue                       :  1;  // Bits 22:22
    UINT32 DdrCRNumOfPulses                        :  2;  // Bits 24:23
    UINT32 DdrCRMaskCntPulseNumStart               :  4;  // Bits 28:25
    UINT32 spare                                   :  3;  // Bits 31:29
  } Bits;
  struct {
    UINT32 DdrDqOvrdModeEn                         :  11;  // Bits 10:0
    UINT32 DdrDqOvrdData                           :  11;  // Bits 21:11
    UINT32 DDRCrDqsMaskValue                       :  1;  // Bits 22:22
    UINT32 DdrCRNumOfPulses                        :  2;  // Bits 24:23
    UINT32 DdrCRMaskCntPulseNumStart               :  4;  // Bits 28:25
    UINT32 DdrCRWrPostamble                        :  1;  // Bits 29:29
    UINT32 spare                                   :  2;  // Bits 31:30
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DDRCRCMDBUSTRAIN_STRUCT;
typedef union {
  struct {
    UINT32 RankEn                                  :  2;  // Bits 1:0
    UINT32 LaneEn                                  :  10;  // Bits 11:2
    UINT32 RankMap                                 :  2;  // Bits 13:12
    UINT32 DccSamples                              :  5;  // Bits 18:14
    UINT32 SaveFullDcc                             :  1;  // Bits 19:19
    UINT32 RORank                                  :  3;  // Bits 22:20
    UINT32 EnRankOvrd                              :  1;  // Bits 23:23
    UINT32 MeasPoint                               :  2;  // Bits 25:24
    UINT32 SkipCRWrite                             :  1;  // Bits 26:26
    UINT32 SkipUpdate                              :  1;  // Bits 27:27
    UINT32 WaitForUpdate                           :  1;  // Bits 28:28
    UINT32 rsvd                                    :  3;  // Bits 31:29
  } Bits;
  struct {
    UINT32 RankEn                                  :  2;  // Bits 1:0
    UINT32 LaneEn                                  :  10;  // Bits 11:2
    UINT32 RankMap                                 :  2;  // Bits 13:12
    UINT32 DccSamples                              :  5;  // Bits 18:14
    UINT32 SaveFullDcc                             :  1;  // Bits 19:19
    UINT32 RORank                                  :  3;  // Bits 22:20
    UINT32 EnRankOvrd                              :  1;  // Bits 23:23
    UINT32 MeasPoint                               :  2;  // Bits 25:24
    UINT32 SkipCRWrite                             :  1;  // Bits 26:26
    UINT32 SkipUpdate                              :  1;  // Bits 27:27
    UINT32 WaitForUpdate                           :  1;  // Bits 28:28
    UINT32 Restore4Ranks                           :  1;  // Bits 29:29
    UINT32 rsvd                                    :  2;  // Bits 31:30
  } P0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DCCFSMCONTROL_STRUCT;
typedef union {
  struct {
    UINT32 DccStepSize                             :  5;  // Bits 4:0
    INT32  DqTargetR0                              :  4;  // Bits 8:5
    INT32  DqTargetR1                              :  4;  // Bits 12:9
    INT32  DqsTargetR0                             :  4;  // Bits 16:13
    INT32  DqsTargetR1                             :  4;  // Bits 20:17
    UINT32 TrackExtremeLane                        :  4;  // Bits 24:21
    UINT32 TrackExtremeMax                         :  1;  // Bits 25:25
    UINT32 TrackExtremeRank                        :  1;  // Bits 26:26
    UINT32 LargeChange                             :  2;  // Bits 28:27
    UINT32 WrLUTDq0                                :  1;  // Bits 29:29
    UINT32 Dcc2xStep                               :  1;  // Bits 30:30
    UINT32 rsvd                                    :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DCCCALCCONTROL_STRUCT;
typedef union {
  struct {
    UINT32 LaneDone                                :  10;  // Bits 9:0
    UINT32 RankDone                                :  2;  // Bits 11:10
    UINT32 CalcState                               :  3;  // Bits 14:12
    UINT32 CalcRank                                :  2;  // Bits 16:15
    UINT32 CalcLane                                :  4;  // Bits 20:17
    UINT32 UpdateState                             :  3;  // Bits 23:21
    UINT32 UpdateRank                              :  2;  // Bits 25:24
    UINT32 LargeChange                             :  1;  // Bits 26:26
    UINT32 rsvd                                    :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DCCFSMSTATUS_STRUCT;
typedef union {
  struct {
    UINT32 Lane0Result                             :  9;  // Bits 8:0
    UINT32 Lane1Result                             :  9;  // Bits 17:9
    UINT32 Lane2Result                             :  9;  // Bits 26:18
    UINT32 rsvd                                    :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DCCLANESTATUS0_STRUCT;
typedef union {
  struct {
    UINT32 Lane3Result                             :  9;  // Bits 8:0
    UINT32 Lane4Result                             :  9;  // Bits 17:9
    UINT32 Lane5Result                             :  9;  // Bits 26:18
    UINT32 rsvd                                    :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DCCLANESTATUS1_STRUCT;
typedef union {
  struct {
    UINT32 Lane6Result                             :  9;  // Bits 8:0
    UINT32 Lane7Result                             :  9;  // Bits 17:9
    UINT32 Lane8Result                             :  9;  // Bits 26:18
    UINT32 rsvd                                    :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DCCLANESTATUS2_STRUCT;
typedef union {
  struct {
    UINT32 Lane9Result                             :  9;  // Bits 8:0
    UINT32 ExtremeOffset                           :  7;  // Bits 15:9
    UINT32 ExtremeCount                            :  9;  // Bits 24:16
    UINT32 rsvd                                    :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DCCLANESTATUS3_STRUCT;
typedef union {
  struct {
    INT32  Fine0                                   :  6;  // Bits 5:0
    INT32  Fine1                                   :  6;  // Bits 11:6
    INT32  Fine2                                   :  6;  // Bits 17:12
    INT32  Fine3                                   :  6;  // Bits 23:18
    INT32  Fine4                                   :  6;  // Bits 29:24
    UINT32 rsvd                                    :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DCCPILUT0_STRUCT;
typedef union {
  struct {
    INT32  Fine5                                   :  6;  // Bits 5:0
    INT32  Fine6                                   :  6;  // Bits 11:6
    INT32  Fine7                                   :  6;  // Bits 17:12
    UINT32 rsvd                                    :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DCCPILUT1_STRUCT;
typedef union {
  struct {
    INT32  Coarse0                                 :  6;  // Bits 5:0
    INT32  Coarse1                                 :  6;  // Bits 11:6
    INT32  Coarse2                                 :  6;  // Bits 17:12
    INT32  Coarse3                                 :  6;  // Bits 23:18
    INT32  Coarse4                                 :  6;  // Bits 29:24
    UINT32 rsvd                                    :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DCCPILUT2_STRUCT;
typedef union {
  struct {
    INT32  Coarse5                                 :  6;  // Bits 5:0
    INT32  Coarse6                                 :  6;  // Bits 11:6
    INT32  Coarse7                                 :  6;  // Bits 17:12
    INT32  Coarse8                                 :  6;  // Bits 23:18
    INT32  Coarse9                                 :  6;  // Bits 29:24
    UINT32 rsvd                                    :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DCCPILUT3_STRUCT;
typedef union {
  struct {
    UINT32 DqTcoCompBit0                           :  6;  // Bits 5:0
    UINT32 DqTcoCompBit1                           :  6;  // Bits 11:6
    UINT32 DqTcoCompBit2                           :  6;  // Bits 17:12
    UINT32 DqTcoCompBit3                           :  6;  // Bits 23:18
    UINT32 DqTcoCompBit4                           :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DDRCRDATATCOCONTROL0_STRUCT;
typedef union {
  struct {
    UINT32 DqTcoCompBit5                           :  6;  // Bits 5:0
    UINT32 DqTcoCompBit6                           :  6;  // Bits 11:6
    UINT32 DqTcoCompBit7                           :  6;  // Bits 17:12
    UINT32 DMITcoComp                              :  6;  // Bits 23:18
    UINT32 TxVsxHiLeakerComp                       :  6;  // Bits 29:24
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  struct {
    UINT32 DqTcoCompBit5                           :  6;  // Bits 5:0
    UINT32 DqTcoCompBit6                           :  6;  // Bits 11:6
    UINT32 DqTcoCompBit7                           :  6;  // Bits 17:12
    UINT32 DMITcoComp                              :  6;  // Bits 23:18
    UINT32 Spare                                   :  8;  // Bits 31:24
  } A0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DDRCRDATATCOCONTROL1_STRUCT;
typedef union {
  struct {
    INT32  Coarse10                                :  6;  // Bits 5:0
    INT32  Coarse11                                :  6;  // Bits 11:6
    INT32  Coarse12                                :  6;  // Bits 17:12
    INT32  Coarse13                                :  6;  // Bits 23:18
    INT32  Coarse14                                :  6;  // Bits 29:24
    UINT32 rsvd                                    :  1;  // Bits 30:30
    UINT32 LUTHalfStep                             :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DCCPILUT4_STRUCT;
typedef union {
  struct {
    INT32  TargetBit0                              :  4;  // Bits 3:0
    INT32  TargetBit1                              :  4;  // Bits 7:4
    INT32  TargetBit2                              :  4;  // Bits 11:8
    INT32  TargetBit3                              :  4;  // Bits 15:12
    INT32  TargetBit4                              :  4;  // Bits 19:16
    INT32  TargetBit5                              :  4;  // Bits 23:20
    INT32  TargetBit6                              :  4;  // Bits 27:24
    INT32  TargetBit7                              :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DCCLANETARGET_STRUCT;
typedef union {
  struct {
    UINT32 DataRetrain_DQ0                         :  3;  // Bits 2:0
    UINT32 DataRetrain_DQ1                         :  3;  // Bits 5:3
    UINT32 DataRetrain_DQ2                         :  3;  // Bits 8:6
    UINT32 DataRetrain_DQ3                         :  3;  // Bits 11:9
    UINT32 DataRetrain_DQ4                         :  3;  // Bits 14:12
    UINT32 DataRetrain_DQ5                         :  3;  // Bits 17:15
    UINT32 DataRetrain_DQ6                         :  3;  // Bits 20:18
    UINT32 DataRetrain_DQ7                         :  3;  // Bits 23:21
    UINT32 DataRetrain_ByteSel                     :  1;  // Bits 24:24
    UINT32 DataRetrainEn                           :  1;  // Bits 25:25
    UINT32 SerialMRROrder                          :  1;  // Bits 26:26
    UINT32 DataInvertNibble                        :  2;  // Bits 28:27
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  struct {
    UINT32 DataRetrain_DQ0                         :  3;  // Bits 2:0
    UINT32 DataRetrain_DQ1                         :  3;  // Bits 5:3
    UINT32 DataRetrain_DQ2                         :  3;  // Bits 8:6
    UINT32 DataRetrain_DQ3                         :  3;  // Bits 11:9
    UINT32 DataRetrain_DQ4                         :  3;  // Bits 14:12
    UINT32 DataRetrain_DQ5                         :  3;  // Bits 17:15
    UINT32 DataRetrain_DQ6                         :  3;  // Bits 20:18
    UINT32 DataRetrain_DQ7                         :  3;  // Bits 23:21
    UINT32 DataRetrain_ByteSel                     :  1;  // Bits 24:24
    UINT32 DataRetrainEn                           :  1;  // Bits 25:25
    UINT32 Spare                                   :  6;  // Bits 31:26
  } A0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_STRUCT;
typedef union {
  struct {
    UINT32 InitPiCode                              :  10;  // Bits 9:0
    INT32  DeltaPiCode                             :  7;  // Bits 16:10
    UINT32 ROCount                                 :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA0CH0_CR_DDRCRWRRETRAINRANK2_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA0CH0_CR_DDRCRWRRETRAINRANK1_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA0CH0_CR_DDRCRWRRETRAINRANK0_STRUCT;
typedef union {
  struct {
    UINT32 InitTrain                               :  1;  // Bits 0:0
    UINT32 Duration                                :  10;  // Bits 10:1
    UINT32 ResetStatus                             :  1;  // Bits 11:11
    UINT32 LargeChangeDelta                        :  3;  // Bits 14:12
    UINT32 UpdOnLargeChage                         :  1;  // Bits 15:15
    UINT32 StopOnLargeChange                       :  1;  // Bits 16:16
    UINT32 R0Status                                :  2;  // Bits 18:17
    UINT32 R1Status                                :  2;  // Bits 20:19
    UINT32 R2Status                                :  2;  // Bits 22:21
    UINT32 R3Status                                :  2;  // Bits 24:23
    UINT32 FSMStatus                               :  4;  // Bits 28:25
    UINT32 FSMRank                                 :  2;  // Bits 30:29
    UINT32 LargeChangeTrig                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_STRUCT;
typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Param                                   :  3;  // Bits 3:1
    UINT32 MinVal                                  :  7;  // Bits 10:4
    UINT32 MaxVal                                  :  7;  // Bits 17:11
    UINT32 MinWidth                                :  6;  // Bits 23:18
    UINT32 CalcCenter                              :  1;  // Bits 24:24
    UINT32 IOLBCycles                              :  4;  // Bits 28:25
    UINT32 BurstIdleBurst                          :  1;  // Bits 29:29
    UINT32 LaneResult                              :  1;  // Bits 30:30
    UINT32 ForceOnRcvEn                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DDRCRMARGINMODECONTROL0_STRUCT;
typedef union {
  struct {
    UINT32 result                                  :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_STRUCT;

typedef DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_STRUCT DATA0CH0_CR_DDRCRMARGINMODEDEBUGLSB0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK0LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK0LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK0LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK0LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK0LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK0LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK0LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK0LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK0LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK1LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK1LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK1LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK1LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK1LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK1LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK1LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK1LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK1LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK2LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK2LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK2LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK2LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK2LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK2LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK2LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK2LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK2LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK3LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK3LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK3LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK3LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK3LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK3LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK3LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK3LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA0CH1_CR_DDRDATADQRANK3LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA0CH1_CR_DDRDATADQSRANK0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA0CH1_CR_DDRDATADQSRANK1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA0CH1_CR_DDRDATADQSRANK2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA0CH1_CR_DDRDATADQSRANK3_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA0CH1_CR_RXCONTROL0RANK0_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA0CH1_CR_RXCONTROL0RANK1_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA0CH1_CR_RXCONTROL0RANK2_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA0CH1_CR_RXCONTROL0RANK3_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA0CH1_CR_TXCONTROL0RANK0_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA0CH1_CR_TXCONTROL0RANK1_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA0CH1_CR_TXCONTROL0RANK2_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA0CH1_CR_TXCONTROL0RANK3_STRUCT;

typedef DATA0CH0_CR_RCOMPDATA0_STRUCT DATA0CH1_CR_RCOMPDATA0_STRUCT;

typedef DATA0CH0_CR_RCOMPDATA1_STRUCT DATA0CH1_CR_RCOMPDATA1_STRUCT;

typedef DATA0CH0_CR_DATACOMPVTT_STRUCT DATA0CH1_CR_DATACOMPVTT_STRUCT;

typedef DATA0CH0_CR_DATATRAINFEEDBACK_STRUCT DATA0CH1_CR_DATATRAINFEEDBACK_STRUCT;

typedef DATA0CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT DATA0CH1_CR_DDRCRDATAOFFSETCOMP_STRUCT;

typedef DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_STRUCT DATA0CH1_CR_DDRCRDATAOFFSETTRAIN_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL0_STRUCT DATA0CH1_CR_DDRCRDATACONTROL0_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL1_STRUCT DATA0CH1_CR_DDRCRDATACONTROL1_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL2_STRUCT DATA0CH1_CR_DDRCRDATACONTROL2_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL3_STRUCT DATA0CH1_CR_DDRCRDATACONTROL3_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL4_STRUCT DATA0CH1_CR_DDRCRDATACONTROL4_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL5_STRUCT DATA0CH1_CR_DDRCRDATACONTROL5_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL6_STRUCT DATA0CH1_CR_DDRCRDATACONTROL6_STRUCT;

typedef DATA0CH0_CR_DDRCRCMDBUSTRAIN_STRUCT DATA0CH1_CR_DDRCRCMDBUSTRAIN_STRUCT;

typedef DATA0CH0_CR_DCCFSMCONTROL_STRUCT DATA0CH1_CR_DCCFSMCONTROL_STRUCT;

typedef DATA0CH0_CR_DCCCALCCONTROL_STRUCT DATA0CH1_CR_DCCCALCCONTROL_STRUCT;

typedef DATA0CH0_CR_DCCFSMSTATUS_STRUCT DATA0CH1_CR_DCCFSMSTATUS_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS0_STRUCT DATA0CH1_CR_DCCLANESTATUS0_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS1_STRUCT DATA0CH1_CR_DCCLANESTATUS1_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS2_STRUCT DATA0CH1_CR_DCCLANESTATUS2_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS3_STRUCT DATA0CH1_CR_DCCLANESTATUS3_STRUCT;

typedef DATA0CH0_CR_DCCPILUT0_STRUCT DATA0CH1_CR_DCCPILUT0_STRUCT;

typedef DATA0CH0_CR_DCCPILUT1_STRUCT DATA0CH1_CR_DCCPILUT1_STRUCT;

typedef DATA0CH0_CR_DCCPILUT2_STRUCT DATA0CH1_CR_DCCPILUT2_STRUCT;

typedef DATA0CH0_CR_DCCPILUT3_STRUCT DATA0CH1_CR_DCCPILUT3_STRUCT;

typedef DATA0CH0_CR_DDRCRDATATCOCONTROL0_STRUCT DATA0CH1_CR_DDRCRDATATCOCONTROL0_STRUCT;

typedef DATA0CH0_CR_DDRCRDATATCOCONTROL1_STRUCT DATA0CH1_CR_DDRCRDATATCOCONTROL1_STRUCT;

typedef DATA0CH0_CR_DCCPILUT4_STRUCT DATA0CH1_CR_DCCPILUT4_STRUCT;

typedef DATA0CH0_CR_DCCLANETARGET_STRUCT DATA0CH1_CR_DCCLANETARGET_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_STRUCT DATA0CH1_CR_DDRCRWRRETRAINSWIZZLECONTROL_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA0CH1_CR_DDRCRWRRETRAINRANK3_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA0CH1_CR_DDRCRWRRETRAINRANK2_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA0CH1_CR_DDRCRWRRETRAINRANK1_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA0CH1_CR_DDRCRWRRETRAINRANK0_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_STRUCT DATA0CH1_CR_DDRCRWRRETRAINCONTROLSTATUS_STRUCT;

typedef DATA0CH0_CR_DDRCRMARGINMODECONTROL0_STRUCT DATA0CH1_CR_DDRCRMARGINMODECONTROL0_STRUCT;

typedef DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_STRUCT DATA0CH1_CR_DDRCRMARGINMODEDEBUGMSB0_STRUCT;

typedef DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_STRUCT DATA0CH1_CR_DDRCRMARGINMODEDEBUGLSB0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK0LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK0LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK0LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK0LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK0LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK0LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK0LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK0LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK0LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK1LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK1LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK1LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK1LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK1LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK1LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK1LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK1LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK1LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK2LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK2LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK2LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK2LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK2LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK2LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK2LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK2LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK2LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK3LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK3LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK3LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK3LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK3LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK3LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK3LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK3LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH0_CR_DDRDATADQRANK3LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA1CH0_CR_DDRDATADQSRANK0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA1CH0_CR_DDRDATADQSRANK1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA1CH0_CR_DDRDATADQSRANK2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA1CH0_CR_DDRDATADQSRANK3_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA1CH0_CR_RXCONTROL0RANK0_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA1CH0_CR_RXCONTROL0RANK1_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA1CH0_CR_RXCONTROL0RANK2_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA1CH0_CR_RXCONTROL0RANK3_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA1CH0_CR_TXCONTROL0RANK0_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA1CH0_CR_TXCONTROL0RANK1_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA1CH0_CR_TXCONTROL0RANK2_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA1CH0_CR_TXCONTROL0RANK3_STRUCT;

typedef DATA0CH0_CR_RCOMPDATA0_STRUCT DATA1CH0_CR_RCOMPDATA0_STRUCT;

typedef DATA0CH0_CR_RCOMPDATA1_STRUCT DATA1CH0_CR_RCOMPDATA1_STRUCT;

typedef DATA0CH0_CR_DATACOMPVTT_STRUCT DATA1CH0_CR_DATACOMPVTT_STRUCT;

typedef DATA0CH0_CR_DATATRAINFEEDBACK_STRUCT DATA1CH0_CR_DATATRAINFEEDBACK_STRUCT;

typedef DATA0CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT DATA1CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT;

typedef DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_STRUCT DATA1CH0_CR_DDRCRDATAOFFSETTRAIN_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL0_STRUCT DATA1CH0_CR_DDRCRDATACONTROL0_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL1_STRUCT DATA1CH0_CR_DDRCRDATACONTROL1_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL2_STRUCT DATA1CH0_CR_DDRCRDATACONTROL2_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL3_STRUCT DATA1CH0_CR_DDRCRDATACONTROL3_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL4_STRUCT DATA1CH0_CR_DDRCRDATACONTROL4_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL5_STRUCT DATA1CH0_CR_DDRCRDATACONTROL5_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL6_STRUCT DATA1CH0_CR_DDRCRDATACONTROL6_STRUCT;

typedef DATA0CH0_CR_DDRCRCMDBUSTRAIN_STRUCT DATA1CH0_CR_DDRCRCMDBUSTRAIN_STRUCT;

typedef DATA0CH0_CR_DCCFSMCONTROL_STRUCT DATA1CH0_CR_DCCFSMCONTROL_STRUCT;

typedef DATA0CH0_CR_DCCCALCCONTROL_STRUCT DATA1CH0_CR_DCCCALCCONTROL_STRUCT;

typedef DATA0CH0_CR_DCCFSMSTATUS_STRUCT DATA1CH0_CR_DCCFSMSTATUS_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS0_STRUCT DATA1CH0_CR_DCCLANESTATUS0_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS1_STRUCT DATA1CH0_CR_DCCLANESTATUS1_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS2_STRUCT DATA1CH0_CR_DCCLANESTATUS2_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS3_STRUCT DATA1CH0_CR_DCCLANESTATUS3_STRUCT;

typedef DATA0CH0_CR_DCCPILUT0_STRUCT DATA1CH0_CR_DCCPILUT0_STRUCT;

typedef DATA0CH0_CR_DCCPILUT1_STRUCT DATA1CH0_CR_DCCPILUT1_STRUCT;

typedef DATA0CH0_CR_DCCPILUT2_STRUCT DATA1CH0_CR_DCCPILUT2_STRUCT;

typedef DATA0CH0_CR_DCCPILUT3_STRUCT DATA1CH0_CR_DCCPILUT3_STRUCT;

typedef DATA0CH0_CR_DDRCRDATATCOCONTROL0_STRUCT DATA1CH0_CR_DDRCRDATATCOCONTROL0_STRUCT;

typedef DATA0CH0_CR_DDRCRDATATCOCONTROL1_STRUCT DATA1CH0_CR_DDRCRDATATCOCONTROL1_STRUCT;

typedef DATA0CH0_CR_DCCPILUT4_STRUCT DATA1CH0_CR_DCCPILUT4_STRUCT;

typedef DATA0CH0_CR_DCCLANETARGET_STRUCT DATA1CH0_CR_DCCLANETARGET_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_STRUCT DATA1CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA1CH0_CR_DDRCRWRRETRAINRANK3_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA1CH0_CR_DDRCRWRRETRAINRANK2_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA1CH0_CR_DDRCRWRRETRAINRANK1_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA1CH0_CR_DDRCRWRRETRAINRANK0_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_STRUCT DATA1CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_STRUCT;

typedef DATA0CH0_CR_DDRCRMARGINMODECONTROL0_STRUCT DATA1CH0_CR_DDRCRMARGINMODECONTROL0_STRUCT;

typedef DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_STRUCT DATA1CH0_CR_DDRCRMARGINMODEDEBUGMSB0_STRUCT;

typedef DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_STRUCT DATA1CH0_CR_DDRCRMARGINMODEDEBUGLSB0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK0LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK0LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK0LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK0LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK0LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK0LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK0LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK0LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK0LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK1LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK1LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK1LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK1LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK1LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK1LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK1LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK1LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK1LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK2LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK2LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK2LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK2LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK2LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK2LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK2LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK2LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK2LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK3LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK3LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK3LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK3LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK3LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK3LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK3LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK3LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA1CH1_CR_DDRDATADQRANK3LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA1CH1_CR_DDRDATADQSRANK0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA1CH1_CR_DDRDATADQSRANK1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA1CH1_CR_DDRDATADQSRANK2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA1CH1_CR_DDRDATADQSRANK3_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA1CH1_CR_RXCONTROL0RANK0_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA1CH1_CR_RXCONTROL0RANK1_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA1CH1_CR_RXCONTROL0RANK2_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA1CH1_CR_RXCONTROL0RANK3_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA1CH1_CR_TXCONTROL0RANK0_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA1CH1_CR_TXCONTROL0RANK1_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA1CH1_CR_TXCONTROL0RANK2_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA1CH1_CR_TXCONTROL0RANK3_STRUCT;

typedef DATA0CH0_CR_RCOMPDATA0_STRUCT DATA1CH1_CR_RCOMPDATA0_STRUCT;

typedef DATA0CH0_CR_RCOMPDATA1_STRUCT DATA1CH1_CR_RCOMPDATA1_STRUCT;

typedef DATA0CH0_CR_DATACOMPVTT_STRUCT DATA1CH1_CR_DATACOMPVTT_STRUCT;

typedef DATA0CH0_CR_DATATRAINFEEDBACK_STRUCT DATA1CH1_CR_DATATRAINFEEDBACK_STRUCT;

typedef DATA0CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT DATA1CH1_CR_DDRCRDATAOFFSETCOMP_STRUCT;

typedef DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_STRUCT DATA1CH1_CR_DDRCRDATAOFFSETTRAIN_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL0_STRUCT DATA1CH1_CR_DDRCRDATACONTROL0_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL1_STRUCT DATA1CH1_CR_DDRCRDATACONTROL1_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL2_STRUCT DATA1CH1_CR_DDRCRDATACONTROL2_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL3_STRUCT DATA1CH1_CR_DDRCRDATACONTROL3_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL4_STRUCT DATA1CH1_CR_DDRCRDATACONTROL4_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL5_STRUCT DATA1CH1_CR_DDRCRDATACONTROL5_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL6_STRUCT DATA1CH1_CR_DDRCRDATACONTROL6_STRUCT;

typedef DATA0CH0_CR_DDRCRCMDBUSTRAIN_STRUCT DATA1CH1_CR_DDRCRCMDBUSTRAIN_STRUCT;

typedef DATA0CH0_CR_DCCFSMCONTROL_STRUCT DATA1CH1_CR_DCCFSMCONTROL_STRUCT;

typedef DATA0CH0_CR_DCCCALCCONTROL_STRUCT DATA1CH1_CR_DCCCALCCONTROL_STRUCT;

typedef DATA0CH0_CR_DCCFSMSTATUS_STRUCT DATA1CH1_CR_DCCFSMSTATUS_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS0_STRUCT DATA1CH1_CR_DCCLANESTATUS0_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS1_STRUCT DATA1CH1_CR_DCCLANESTATUS1_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS2_STRUCT DATA1CH1_CR_DCCLANESTATUS2_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS3_STRUCT DATA1CH1_CR_DCCLANESTATUS3_STRUCT;

typedef DATA0CH0_CR_DCCPILUT0_STRUCT DATA1CH1_CR_DCCPILUT0_STRUCT;

typedef DATA0CH0_CR_DCCPILUT1_STRUCT DATA1CH1_CR_DCCPILUT1_STRUCT;

typedef DATA0CH0_CR_DCCPILUT2_STRUCT DATA1CH1_CR_DCCPILUT2_STRUCT;

typedef DATA0CH0_CR_DCCPILUT3_STRUCT DATA1CH1_CR_DCCPILUT3_STRUCT;

typedef DATA0CH0_CR_DDRCRDATATCOCONTROL0_STRUCT DATA1CH1_CR_DDRCRDATATCOCONTROL0_STRUCT;

typedef DATA0CH0_CR_DDRCRDATATCOCONTROL1_STRUCT DATA1CH1_CR_DDRCRDATATCOCONTROL1_STRUCT;

typedef DATA0CH0_CR_DCCPILUT4_STRUCT DATA1CH1_CR_DCCPILUT4_STRUCT;

typedef DATA0CH0_CR_DCCLANETARGET_STRUCT DATA1CH1_CR_DCCLANETARGET_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_STRUCT DATA1CH1_CR_DDRCRWRRETRAINSWIZZLECONTROL_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA1CH1_CR_DDRCRWRRETRAINRANK3_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA1CH1_CR_DDRCRWRRETRAINRANK2_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA1CH1_CR_DDRCRWRRETRAINRANK1_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA1CH1_CR_DDRCRWRRETRAINRANK0_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_STRUCT DATA1CH1_CR_DDRCRWRRETRAINCONTROLSTATUS_STRUCT;

typedef DATA0CH0_CR_DDRCRMARGINMODECONTROL0_STRUCT DATA1CH1_CR_DDRCRMARGINMODECONTROL0_STRUCT;

typedef DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_STRUCT DATA1CH1_CR_DDRCRMARGINMODEDEBUGMSB0_STRUCT;

typedef DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_STRUCT DATA1CH1_CR_DDRCRMARGINMODEDEBUGLSB0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK0LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK0LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK0LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK0LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK0LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK0LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK0LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK0LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK0LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK1LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK1LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK1LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK1LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK1LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK1LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK1LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK1LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK1LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK2LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK2LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK2LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK2LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK2LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK2LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK2LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK2LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK2LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK3LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK3LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK3LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK3LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK3LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK3LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK3LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK3LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH0_CR_DDRDATADQRANK3LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA2CH0_CR_DDRDATADQSRANK0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA2CH0_CR_DDRDATADQSRANK1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA2CH0_CR_DDRDATADQSRANK2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA2CH0_CR_DDRDATADQSRANK3_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA2CH0_CR_RXCONTROL0RANK0_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA2CH0_CR_RXCONTROL0RANK1_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA2CH0_CR_RXCONTROL0RANK2_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA2CH0_CR_RXCONTROL0RANK3_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA2CH0_CR_TXCONTROL0RANK0_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA2CH0_CR_TXCONTROL0RANK1_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA2CH0_CR_TXCONTROL0RANK2_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA2CH0_CR_TXCONTROL0RANK3_STRUCT;

typedef DATA0CH0_CR_RCOMPDATA0_STRUCT DATA2CH0_CR_RCOMPDATA0_STRUCT;

typedef DATA0CH0_CR_RCOMPDATA1_STRUCT DATA2CH0_CR_RCOMPDATA1_STRUCT;

typedef DATA0CH0_CR_DATACOMPVTT_STRUCT DATA2CH0_CR_DATACOMPVTT_STRUCT;

typedef DATA0CH0_CR_DATATRAINFEEDBACK_STRUCT DATA2CH0_CR_DATATRAINFEEDBACK_STRUCT;

typedef DATA0CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT DATA2CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT;

typedef DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_STRUCT DATA2CH0_CR_DDRCRDATAOFFSETTRAIN_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL0_STRUCT DATA2CH0_CR_DDRCRDATACONTROL0_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL1_STRUCT DATA2CH0_CR_DDRCRDATACONTROL1_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL2_STRUCT DATA2CH0_CR_DDRCRDATACONTROL2_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL3_STRUCT DATA2CH0_CR_DDRCRDATACONTROL3_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL4_STRUCT DATA2CH0_CR_DDRCRDATACONTROL4_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL5_STRUCT DATA2CH0_CR_DDRCRDATACONTROL5_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL6_STRUCT DATA2CH0_CR_DDRCRDATACONTROL6_STRUCT;

typedef DATA0CH0_CR_DDRCRCMDBUSTRAIN_STRUCT DATA2CH0_CR_DDRCRCMDBUSTRAIN_STRUCT;

typedef DATA0CH0_CR_DCCFSMCONTROL_STRUCT DATA2CH0_CR_DCCFSMCONTROL_STRUCT;

typedef DATA0CH0_CR_DCCCALCCONTROL_STRUCT DATA2CH0_CR_DCCCALCCONTROL_STRUCT;

typedef DATA0CH0_CR_DCCFSMSTATUS_STRUCT DATA2CH0_CR_DCCFSMSTATUS_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS0_STRUCT DATA2CH0_CR_DCCLANESTATUS0_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS1_STRUCT DATA2CH0_CR_DCCLANESTATUS1_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS2_STRUCT DATA2CH0_CR_DCCLANESTATUS2_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS3_STRUCT DATA2CH0_CR_DCCLANESTATUS3_STRUCT;

typedef DATA0CH0_CR_DCCPILUT0_STRUCT DATA2CH0_CR_DCCPILUT0_STRUCT;

typedef DATA0CH0_CR_DCCPILUT1_STRUCT DATA2CH0_CR_DCCPILUT1_STRUCT;

typedef DATA0CH0_CR_DCCPILUT2_STRUCT DATA2CH0_CR_DCCPILUT2_STRUCT;

typedef DATA0CH0_CR_DCCPILUT3_STRUCT DATA2CH0_CR_DCCPILUT3_STRUCT;

typedef DATA0CH0_CR_DDRCRDATATCOCONTROL0_STRUCT DATA2CH0_CR_DDRCRDATATCOCONTROL0_STRUCT;

typedef DATA0CH0_CR_DDRCRDATATCOCONTROL1_STRUCT DATA2CH0_CR_DDRCRDATATCOCONTROL1_STRUCT;

typedef DATA0CH0_CR_DCCPILUT4_STRUCT DATA2CH0_CR_DCCPILUT4_STRUCT;

typedef DATA0CH0_CR_DCCLANETARGET_STRUCT DATA2CH0_CR_DCCLANETARGET_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_STRUCT DATA2CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA2CH0_CR_DDRCRWRRETRAINRANK3_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA2CH0_CR_DDRCRWRRETRAINRANK2_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA2CH0_CR_DDRCRWRRETRAINRANK1_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA2CH0_CR_DDRCRWRRETRAINRANK0_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_STRUCT DATA2CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_STRUCT;

typedef DATA0CH0_CR_DDRCRMARGINMODECONTROL0_STRUCT DATA2CH0_CR_DDRCRMARGINMODECONTROL0_STRUCT;

typedef DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_STRUCT DATA2CH0_CR_DDRCRMARGINMODEDEBUGMSB0_STRUCT;

typedef DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_STRUCT DATA2CH0_CR_DDRCRMARGINMODEDEBUGLSB0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK0LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK0LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK0LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK0LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK0LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK0LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK0LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK0LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK0LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK1LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK1LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK1LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK1LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK1LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK1LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK1LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK1LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK1LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK2LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK2LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK2LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK2LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK2LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK2LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK2LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK2LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK2LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK3LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK3LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK3LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK3LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK3LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK3LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK3LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK3LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA2CH1_CR_DDRDATADQRANK3LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA2CH1_CR_DDRDATADQSRANK0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA2CH1_CR_DDRDATADQSRANK1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA2CH1_CR_DDRDATADQSRANK2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA2CH1_CR_DDRDATADQSRANK3_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA2CH1_CR_RXCONTROL0RANK0_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA2CH1_CR_RXCONTROL0RANK1_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA2CH1_CR_RXCONTROL0RANK2_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA2CH1_CR_RXCONTROL0RANK3_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA2CH1_CR_TXCONTROL0RANK0_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA2CH1_CR_TXCONTROL0RANK1_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA2CH1_CR_TXCONTROL0RANK2_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA2CH1_CR_TXCONTROL0RANK3_STRUCT;

typedef DATA0CH0_CR_RCOMPDATA0_STRUCT DATA2CH1_CR_RCOMPDATA0_STRUCT;

typedef DATA0CH0_CR_RCOMPDATA1_STRUCT DATA2CH1_CR_RCOMPDATA1_STRUCT;

typedef DATA0CH0_CR_DATACOMPVTT_STRUCT DATA2CH1_CR_DATACOMPVTT_STRUCT;

typedef DATA0CH0_CR_DATATRAINFEEDBACK_STRUCT DATA2CH1_CR_DATATRAINFEEDBACK_STRUCT;

typedef DATA0CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT DATA2CH1_CR_DDRCRDATAOFFSETCOMP_STRUCT;

typedef DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_STRUCT DATA2CH1_CR_DDRCRDATAOFFSETTRAIN_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL0_STRUCT DATA2CH1_CR_DDRCRDATACONTROL0_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL1_STRUCT DATA2CH1_CR_DDRCRDATACONTROL1_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL2_STRUCT DATA2CH1_CR_DDRCRDATACONTROL2_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL3_STRUCT DATA2CH1_CR_DDRCRDATACONTROL3_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL4_STRUCT DATA2CH1_CR_DDRCRDATACONTROL4_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL5_STRUCT DATA2CH1_CR_DDRCRDATACONTROL5_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL6_STRUCT DATA2CH1_CR_DDRCRDATACONTROL6_STRUCT;

typedef DATA0CH0_CR_DDRCRCMDBUSTRAIN_STRUCT DATA2CH1_CR_DDRCRCMDBUSTRAIN_STRUCT;

typedef DATA0CH0_CR_DCCFSMCONTROL_STRUCT DATA2CH1_CR_DCCFSMCONTROL_STRUCT;

typedef DATA0CH0_CR_DCCCALCCONTROL_STRUCT DATA2CH1_CR_DCCCALCCONTROL_STRUCT;

typedef DATA0CH0_CR_DCCFSMSTATUS_STRUCT DATA2CH1_CR_DCCFSMSTATUS_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS0_STRUCT DATA2CH1_CR_DCCLANESTATUS0_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS1_STRUCT DATA2CH1_CR_DCCLANESTATUS1_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS2_STRUCT DATA2CH1_CR_DCCLANESTATUS2_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS3_STRUCT DATA2CH1_CR_DCCLANESTATUS3_STRUCT;

typedef DATA0CH0_CR_DCCPILUT0_STRUCT DATA2CH1_CR_DCCPILUT0_STRUCT;

typedef DATA0CH0_CR_DCCPILUT1_STRUCT DATA2CH1_CR_DCCPILUT1_STRUCT;

typedef DATA0CH0_CR_DCCPILUT2_STRUCT DATA2CH1_CR_DCCPILUT2_STRUCT;

typedef DATA0CH0_CR_DCCPILUT3_STRUCT DATA2CH1_CR_DCCPILUT3_STRUCT;

typedef DATA0CH0_CR_DDRCRDATATCOCONTROL0_STRUCT DATA2CH1_CR_DDRCRDATATCOCONTROL0_STRUCT;

typedef DATA0CH0_CR_DDRCRDATATCOCONTROL1_STRUCT DATA2CH1_CR_DDRCRDATATCOCONTROL1_STRUCT;

typedef DATA0CH0_CR_DCCPILUT4_STRUCT DATA2CH1_CR_DCCPILUT4_STRUCT;

typedef DATA0CH0_CR_DCCLANETARGET_STRUCT DATA2CH1_CR_DCCLANETARGET_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_STRUCT DATA2CH1_CR_DDRCRWRRETRAINSWIZZLECONTROL_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA2CH1_CR_DDRCRWRRETRAINRANK3_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA2CH1_CR_DDRCRWRRETRAINRANK2_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA2CH1_CR_DDRCRWRRETRAINRANK1_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA2CH1_CR_DDRCRWRRETRAINRANK0_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_STRUCT DATA2CH1_CR_DDRCRWRRETRAINCONTROLSTATUS_STRUCT;

typedef DATA0CH0_CR_DDRCRMARGINMODECONTROL0_STRUCT DATA2CH1_CR_DDRCRMARGINMODECONTROL0_STRUCT;

typedef DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_STRUCT DATA2CH1_CR_DDRCRMARGINMODEDEBUGMSB0_STRUCT;

typedef DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_STRUCT DATA2CH1_CR_DDRCRMARGINMODEDEBUGLSB0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK0LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK0LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK0LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK0LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK0LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK0LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK0LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK0LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK0LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK1LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK1LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK1LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK1LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK1LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK1LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK1LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK1LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK1LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK2LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK2LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK2LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK2LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK2LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK2LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK2LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK2LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK2LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK3LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK3LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK3LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK3LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK3LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK3LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK3LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK3LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH0_CR_DDRDATADQRANK3LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA3CH0_CR_DDRDATADQSRANK0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA3CH0_CR_DDRDATADQSRANK1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA3CH0_CR_DDRDATADQSRANK2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA3CH0_CR_DDRDATADQSRANK3_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA3CH0_CR_RXCONTROL0RANK0_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA3CH0_CR_RXCONTROL0RANK1_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA3CH0_CR_RXCONTROL0RANK2_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA3CH0_CR_RXCONTROL0RANK3_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA3CH0_CR_TXCONTROL0RANK0_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA3CH0_CR_TXCONTROL0RANK1_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA3CH0_CR_TXCONTROL0RANK2_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA3CH0_CR_TXCONTROL0RANK3_STRUCT;

typedef DATA0CH0_CR_RCOMPDATA0_STRUCT DATA3CH0_CR_RCOMPDATA0_STRUCT;

typedef DATA0CH0_CR_RCOMPDATA1_STRUCT DATA3CH0_CR_RCOMPDATA1_STRUCT;

typedef DATA0CH0_CR_DATACOMPVTT_STRUCT DATA3CH0_CR_DATACOMPVTT_STRUCT;

typedef DATA0CH0_CR_DATATRAINFEEDBACK_STRUCT DATA3CH0_CR_DATATRAINFEEDBACK_STRUCT;

typedef DATA0CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT DATA3CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT;

typedef DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_STRUCT DATA3CH0_CR_DDRCRDATAOFFSETTRAIN_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL0_STRUCT DATA3CH0_CR_DDRCRDATACONTROL0_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL1_STRUCT DATA3CH0_CR_DDRCRDATACONTROL1_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL2_STRUCT DATA3CH0_CR_DDRCRDATACONTROL2_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL3_STRUCT DATA3CH0_CR_DDRCRDATACONTROL3_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL4_STRUCT DATA3CH0_CR_DDRCRDATACONTROL4_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL5_STRUCT DATA3CH0_CR_DDRCRDATACONTROL5_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL6_STRUCT DATA3CH0_CR_DDRCRDATACONTROL6_STRUCT;

typedef DATA0CH0_CR_DDRCRCMDBUSTRAIN_STRUCT DATA3CH0_CR_DDRCRCMDBUSTRAIN_STRUCT;

typedef DATA0CH0_CR_DCCFSMCONTROL_STRUCT DATA3CH0_CR_DCCFSMCONTROL_STRUCT;

typedef DATA0CH0_CR_DCCCALCCONTROL_STRUCT DATA3CH0_CR_DCCCALCCONTROL_STRUCT;

typedef DATA0CH0_CR_DCCFSMSTATUS_STRUCT DATA3CH0_CR_DCCFSMSTATUS_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS0_STRUCT DATA3CH0_CR_DCCLANESTATUS0_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS1_STRUCT DATA3CH0_CR_DCCLANESTATUS1_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS2_STRUCT DATA3CH0_CR_DCCLANESTATUS2_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS3_STRUCT DATA3CH0_CR_DCCLANESTATUS3_STRUCT;

typedef DATA0CH0_CR_DCCPILUT0_STRUCT DATA3CH0_CR_DCCPILUT0_STRUCT;

typedef DATA0CH0_CR_DCCPILUT1_STRUCT DATA3CH0_CR_DCCPILUT1_STRUCT;

typedef DATA0CH0_CR_DCCPILUT2_STRUCT DATA3CH0_CR_DCCPILUT2_STRUCT;

typedef DATA0CH0_CR_DCCPILUT3_STRUCT DATA3CH0_CR_DCCPILUT3_STRUCT;

typedef DATA0CH0_CR_DDRCRDATATCOCONTROL0_STRUCT DATA3CH0_CR_DDRCRDATATCOCONTROL0_STRUCT;

typedef DATA0CH0_CR_DDRCRDATATCOCONTROL1_STRUCT DATA3CH0_CR_DDRCRDATATCOCONTROL1_STRUCT;

typedef DATA0CH0_CR_DCCPILUT4_STRUCT DATA3CH0_CR_DCCPILUT4_STRUCT;

typedef DATA0CH0_CR_DCCLANETARGET_STRUCT DATA3CH0_CR_DCCLANETARGET_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_STRUCT DATA3CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA3CH0_CR_DDRCRWRRETRAINRANK3_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA3CH0_CR_DDRCRWRRETRAINRANK2_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA3CH0_CR_DDRCRWRRETRAINRANK1_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA3CH0_CR_DDRCRWRRETRAINRANK0_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_STRUCT DATA3CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_STRUCT;

typedef DATA0CH0_CR_DDRCRMARGINMODECONTROL0_STRUCT DATA3CH0_CR_DDRCRMARGINMODECONTROL0_STRUCT;

typedef DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_STRUCT DATA3CH0_CR_DDRCRMARGINMODEDEBUGMSB0_STRUCT;

typedef DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_STRUCT DATA3CH0_CR_DDRCRMARGINMODEDEBUGLSB0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK0LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK0LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK0LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK0LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK0LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK0LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK0LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK0LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK0LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK1LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK1LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK1LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK1LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK1LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK1LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK1LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK1LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK1LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK2LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK2LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK2LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK2LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK2LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK2LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK2LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK2LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK2LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK3LANE0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK3LANE1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK3LANE2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK3LANE3_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK3LANE4_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK3LANE5_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK3LANE6_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK3LANE7_STRUCT;

typedef DATA0CH0_CR_DDRDATADQRANK0LANE0_STRUCT DATA3CH1_CR_DDRDATADQRANK3LANE8_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA3CH1_CR_DDRDATADQSRANK0_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA3CH1_CR_DDRDATADQSRANK1_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA3CH1_CR_DDRDATADQSRANK2_STRUCT;

typedef DATA0CH0_CR_DDRDATADQSRANK0_STRUCT DATA3CH1_CR_DDRDATADQSRANK3_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA3CH1_CR_RXCONTROL0RANK0_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA3CH1_CR_RXCONTROL0RANK1_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA3CH1_CR_RXCONTROL0RANK2_STRUCT;

typedef DATA0CH0_CR_RXCONTROL0RANK0_STRUCT DATA3CH1_CR_RXCONTROL0RANK3_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA3CH1_CR_TXCONTROL0RANK0_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA3CH1_CR_TXCONTROL0RANK1_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA3CH1_CR_TXCONTROL0RANK2_STRUCT;

typedef DATA0CH0_CR_TXCONTROL0RANK0_STRUCT DATA3CH1_CR_TXCONTROL0RANK3_STRUCT;

typedef DATA0CH0_CR_RCOMPDATA0_STRUCT DATA3CH1_CR_RCOMPDATA0_STRUCT;

typedef DATA0CH0_CR_RCOMPDATA1_STRUCT DATA3CH1_CR_RCOMPDATA1_STRUCT;

typedef DATA0CH0_CR_DATACOMPVTT_STRUCT DATA3CH1_CR_DATACOMPVTT_STRUCT;

typedef DATA0CH0_CR_DATATRAINFEEDBACK_STRUCT DATA3CH1_CR_DATATRAINFEEDBACK_STRUCT;

typedef DATA0CH0_CR_DDRCRDATAOFFSETCOMP_STRUCT DATA3CH1_CR_DDRCRDATAOFFSETCOMP_STRUCT;

typedef DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_STRUCT DATA3CH1_CR_DDRCRDATAOFFSETTRAIN_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL0_STRUCT DATA3CH1_CR_DDRCRDATACONTROL0_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL1_STRUCT DATA3CH1_CR_DDRCRDATACONTROL1_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL2_STRUCT DATA3CH1_CR_DDRCRDATACONTROL2_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL3_STRUCT DATA3CH1_CR_DDRCRDATACONTROL3_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL4_STRUCT DATA3CH1_CR_DDRCRDATACONTROL4_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL5_STRUCT DATA3CH1_CR_DDRCRDATACONTROL5_STRUCT;

typedef DATA0CH0_CR_DDRCRDATACONTROL6_STRUCT DATA3CH1_CR_DDRCRDATACONTROL6_STRUCT;

typedef DATA0CH0_CR_DDRCRCMDBUSTRAIN_STRUCT DATA3CH1_CR_DDRCRCMDBUSTRAIN_STRUCT;

typedef DATA0CH0_CR_DCCFSMCONTROL_STRUCT DATA3CH1_CR_DCCFSMCONTROL_STRUCT;

typedef DATA0CH0_CR_DCCCALCCONTROL_STRUCT DATA3CH1_CR_DCCCALCCONTROL_STRUCT;

typedef DATA0CH0_CR_DCCFSMSTATUS_STRUCT DATA3CH1_CR_DCCFSMSTATUS_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS0_STRUCT DATA3CH1_CR_DCCLANESTATUS0_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS1_STRUCT DATA3CH1_CR_DCCLANESTATUS1_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS2_STRUCT DATA3CH1_CR_DCCLANESTATUS2_STRUCT;

typedef DATA0CH0_CR_DCCLANESTATUS3_STRUCT DATA3CH1_CR_DCCLANESTATUS3_STRUCT;

typedef DATA0CH0_CR_DCCPILUT0_STRUCT DATA3CH1_CR_DCCPILUT0_STRUCT;

typedef DATA0CH0_CR_DCCPILUT1_STRUCT DATA3CH1_CR_DCCPILUT1_STRUCT;

typedef DATA0CH0_CR_DCCPILUT2_STRUCT DATA3CH1_CR_DCCPILUT2_STRUCT;

typedef DATA0CH0_CR_DCCPILUT3_STRUCT DATA3CH1_CR_DCCPILUT3_STRUCT;

typedef DATA0CH0_CR_DDRCRDATATCOCONTROL0_STRUCT DATA3CH1_CR_DDRCRDATATCOCONTROL0_STRUCT;

typedef DATA0CH0_CR_DDRCRDATATCOCONTROL1_STRUCT DATA3CH1_CR_DDRCRDATATCOCONTROL1_STRUCT;

typedef DATA0CH0_CR_DCCPILUT4_STRUCT DATA3CH1_CR_DCCPILUT4_STRUCT;

typedef DATA0CH0_CR_DCCLANETARGET_STRUCT DATA3CH1_CR_DCCLANETARGET_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINSWIZZLECONTROL_STRUCT DATA3CH1_CR_DDRCRWRRETRAINSWIZZLECONTROL_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA3CH1_CR_DDRCRWRRETRAINRANK3_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA3CH1_CR_DDRCRWRRETRAINRANK2_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA3CH1_CR_DDRCRWRRETRAINRANK1_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINRANK3_STRUCT DATA3CH1_CR_DDRCRWRRETRAINRANK0_STRUCT;

typedef DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_STRUCT DATA3CH1_CR_DDRCRWRRETRAINCONTROLSTATUS_STRUCT;

typedef DATA0CH0_CR_DDRCRMARGINMODECONTROL0_STRUCT DATA3CH1_CR_DDRCRMARGINMODECONTROL0_STRUCT;

typedef DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_STRUCT DATA3CH1_CR_DDRCRMARGINMODEDEBUGMSB0_STRUCT;

typedef DATA0CH0_CR_DDRCRMARGINMODEDEBUGMSB0_STRUCT DATA3CH1_CR_DDRCRMARGINMODEDEBUGLSB0_STRUCT;

#pragma pack(pop)
#endif
