#ifndef __MrcMcRegisterStructIcl3xxx_h__
#define __MrcMcRegisterStructIcl3xxx_h__
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

typedef union {
  struct {
    UINT32 ScramEn                                 :  1;  // Bits 0:0
    UINT32 ScramKey                                :  16;  // Bits 16:1
    UINT32 ClockGateAB                             :  2;  // Bits 18:17
    UINT32 ClockGateC                              :  2;  // Bits 20:19
    UINT32 EnableDbiAB                             :  1;  // Bits 21:21
    UINT32 en_dilution_mode                        :  1;  // Bits 22:22
    UINT32 ca_mirrored                             :  4;  // Bits 26:23
    UINT32 dis_cmdanalogen                         :  1;  // Bits 27:27
    UINT32 dis_CmdAnaLogEn_at_IDLE                 :  1;  // Bits 28:28
    UINT32 VsshiCompActive                         :  1;  // Bits 29:29
    UINT32 EN_VsshiCompActive_on_lp4retrain        :  1;  // Bits 30:30
    UINT32 forcecompdist                           :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRSCRAM_CR_DDRSCRAMBLECH0_STRUCT;

typedef union {
  struct {
    UINT32 ScramEn                                 :  1;  // Bits 0:0
    UINT32 ScramKey                                :  16;  // Bits 16:1
    UINT32 ClockGateAB                             :  2;  // Bits 18:17
    UINT32 ClockGateC                              :  2;  // Bits 20:19
    UINT32 EnableDbiAB                             :  1;  // Bits 21:21
    UINT32 en_dilution_mode                        :  1;  // Bits 22:22
    UINT32 ca_mirrored                             :  4;  // Bits 26:23
    UINT32 DfxLp4OBSDeltaDQSDistAck                :  1;  // Bits 27:27
    UINT32 DfxLp4OBSDeltaDQSDistReq                :  1;  // Bits 28:28
    UINT32 EarlyRankRdValidSwitch                  :  1;  // Bits 29:29
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRSCRAM_CR_DDRSCRAMBLECH1_STRUCT;

typedef union {
  struct {
    UINT32 WL_WakeCycles                           :  2;  // Bits 1:0
    UINT32 WL_SleepCycles                          :  3;  // Bits 4:2
    UINT32 CompAndDeltaDqsUpdateClkGateDisable     :  1;  // Bits 5:5
    UINT32 WeakLock_Latency                        :  4;  // Bits 9:6
    UINT32 DdrNoChInterleave                       :  1;  // Bits 10:10
    UINT32 LPDDR_Mode                              :  1;  // Bits 11:11
    UINT32 lp4_rcven_ctrl                          :  2;  // Bits 13:12
    UINT32 ddr_centric                             :  1;  // Bits 14:14
    UINT32 ECCPresent                              :  1;  // Bits 15:15
    UINT32 RcvEn_Extension                         :  4;  // Bits 19:16
    UINT32 Ddr4_Mode                               :  1;  // Bits 20:20
    UINT32 ClkGateDisable                          :  1;  // Bits 21:21
    UINT32 DllDataWeakLckEn                        :  1;  // Bits 22:22
    UINT32 DataClkGateDisAtIdle                    :  1;  // Bits 23:23
    UINT32 FourChCfg                               :  1;  // Bits 24:24
    UINT32 LpDdr4Mode                              :  1;  // Bits 25:25
    UINT32 Channel_Not_Populated                   :  4;  // Bits 29:26
    UINT32 dis_iosf_sb_clk_gate                    :  1;  // Bits 30:30
    UINT32 Gear1                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRSCRAM_CR_DDRMISCCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 tCWL4TxDqFifoWrEn                       :  6;  // Bits 5:0
    UINT32 tCWL4TxDqFifoRdEn                       :  6;  // Bits 11:6
    UINT32 Spare                                   :  7;  // Bits 18:12
    UINT32 RptChDqTxClkOn                          :  1;  // Bits 19:19
    UINT32 RptChDqRxClkOn                          :  1;  // Bits 20:20
    UINT32 RptChRepClkOn                           :  1;  // Bits 21:21
    UINT32 CmdAnlgEnGraceCnt                       :  3;  // Bits 24:22
    UINT32 TxAnlgEnGraceCnt                        :  6;  // Bits 30:25
    UINT32 TxDqFifoRdEnPerRankDelDis               :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_WRITECFGCH0_STRUCT;

typedef union {
  struct {
    UINT32 tCWL4TxDqFifoWrEn                       :  6;  // Bits 5:0
    UINT32 tCWL4TxDqFifoRdEn                       :  6;  // Bits 11:6
    UINT32 Spare                                   :  7;  // Bits 18:12
    UINT32 RptChDqTxClkOn                          :  1;  // Bits 19:19
    UINT32 RptChDqRxClkOn                          :  1;  // Bits 20:20
    UINT32 RptChRepClkOn                           :  1;  // Bits 21:21
    UINT32 CmdAnlgEnGraceCnt                       :  3;  // Bits 24:22
    UINT32 TxAnlgEnGraceCnt                        :  6;  // Bits 30:25
    UINT32 TxDqFifoRdEnPerRankDelDis               :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_WRITECFGCH1_STRUCT;

typedef union {
  struct {
    UINT32 tCWL4TxDqFifoWrEn                       :  6;  // Bits 5:0
    UINT32 tCWL4TxDqFifoRdEn                       :  6;  // Bits 11:6
    UINT32 Spare                                   :  7;  // Bits 18:12
    UINT32 RptChDqTxClkOn                          :  1;  // Bits 19:19
    UINT32 RptChDqRxClkOn                          :  1;  // Bits 20:20
    UINT32 RptChRepClkOn                           :  1;  // Bits 21:21
    UINT32 CmdAnlgEnGraceCnt                       :  3;  // Bits 24:22
    UINT32 TxAnlgEnGraceCnt                        :  6;  // Bits 30:25
    UINT32 TxDqFifoRdEnPerRankDelDis               :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_WRITECFGCH2_STRUCT;

typedef union {
  struct {
    UINT32 tCWL4TxDqFifoWrEn                       :  6;  // Bits 5:0
    UINT32 tCWL4TxDqFifoRdEn                       :  6;  // Bits 11:6
    UINT32 Spare                                   :  7;  // Bits 18:12
    UINT32 RptChDqTxClkOn                          :  1;  // Bits 19:19
    UINT32 RptChDqRxClkOn                          :  1;  // Bits 20:20
    UINT32 RptChRepClkOn                           :  1;  // Bits 21:21
    UINT32 CmdAnlgEnGraceCnt                       :  3;  // Bits 24:22
    UINT32 TxAnlgEnGraceCnt                        :  6;  // Bits 30:25
    UINT32 TxDqFifoRdEnPerRankDelDis               :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_WRITECFGCH3_STRUCT;

typedef union {
  struct {
    UINT32 Spare                                   :  15;  // Bits 14:0
    UINT32 tCL4RcvEn                               :  6;  // Bits 20:15
    UINT32 tCL4RxDqFifoRdEn                        :  6;  // Bits 26:21
    UINT32 RxDqDataValidDclkDel                    :  4;  // Bits 30:27
    UINT32 RxDqDataValidQclkDel                    :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_READCFGCH0_STRUCT;

typedef union {
  struct {
    UINT32 Spare                                   :  15;  // Bits 14:0
    UINT32 tCL4RcvEn                               :  6;  // Bits 20:15
    UINT32 tCL4RxDqFifoRdEn                        :  6;  // Bits 26:21
    UINT32 RxDqDataValidDclkDel                    :  4;  // Bits 30:27
    UINT32 RxDqDataValidQclkDel                    :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_READCFGCH1_STRUCT;

typedef union {
  struct {
    UINT32 Spare                                   :  15;  // Bits 14:0
    UINT32 tCL4RcvEn                               :  6;  // Bits 20:15
    UINT32 tCL4RxDqFifoRdEn                        :  6;  // Bits 26:21
    UINT32 RxDqDataValidDclkDel                    :  4;  // Bits 30:27
    UINT32 RxDqDataValidQclkDel                    :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_READCFGCH2_STRUCT;

typedef union {
  struct {
    UINT32 Spare                                   :  15;  // Bits 14:0
    UINT32 tCL4RcvEn                               :  6;  // Bits 20:15
    UINT32 tCL4RxDqFifoRdEn                        :  6;  // Bits 26:21
    UINT32 RxDqDataValidDclkDel                    :  4;  // Bits 30:27
    UINT32 RxDqDataValidQclkDel                    :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_READCFGCH3_STRUCT;

typedef union {
  struct {
    UINT32 ScramEn                                 :  1;  // Bits 0:0
    UINT32 ScramKey                                :  16;  // Bits 16:1
    UINT32 ClockGateAB                             :  2;  // Bits 18:17
    UINT32 ClockGateC                              :  2;  // Bits 20:19
    UINT32 EnableDbiAB                             :  1;  // Bits 21:21
    UINT32 en_dilution_mode                        :  1;  // Bits 22:22
    UINT32 ca_mirrored                             :  4;  // Bits 26:23
    UINT32 Spare                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRSCRAM_CR_DDRSCRAMBLECH2_STRUCT;

typedef union {
  struct {
    UINT32 ScramEn                                 :  1;  // Bits 0:0
    UINT32 ScramKey                                :  16;  // Bits 16:1
    UINT32 ClockGateAB                             :  2;  // Bits 18:17
    UINT32 ClockGateC                              :  2;  // Bits 20:19
    UINT32 EnableDbiAB                             :  1;  // Bits 21:21
    UINT32 en_dilution_mode                        :  1;  // Bits 22:22
    UINT32 ca_mirrored                             :  4;  // Bits 26:23
    UINT32 Spare                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRSCRAM_CR_DDRSCRAMBLECH3_STRUCT;

typedef union {
  struct {
    UINT32 CsOdtMapping_cs0                        :  4;  // Bits 3:0
    UINT32 CsOdtMapping_cs1                        :  4;  // Bits 7:4
    UINT32 CsOdtMapping_cs2                        :  4;  // Bits 11:8
    UINT32 CsOdtMapping_cs3                        :  4;  // Bits 15:12
    UINT32 CsOdtMapping_odt0                       :  4;  // Bits 19:16
    UINT32 CsOdtMapping_odt1                       :  4;  // Bits 23:20
    UINT32 io_train_rst                            :  1;  // Bits 24:24
    UINT32 io_train_rst_quiet_time                 :  1;  // Bits 25:25
    UINT32 io_train_rst_duration                   :  4;  // Bits 29:26
    UINT32 ForceCompUpdate                         :  1;  // Bits 30:30
    UINT32 ForceDeltaDQSUpdate                     :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRSCRAM_CR_DDRMISCCONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 CsOdtMapping_cs0                        :  4;  // Bits 3:0
    UINT32 CsOdtMapping_cs1                        :  4;  // Bits 7:4
    UINT32 CsOdtMapping_cs2                        :  4;  // Bits 11:8
    UINT32 CsOdtMapping_cs3                        :  4;  // Bits 15:12
    UINT32 CsOdtMapping_odt0                       :  4;  // Bits 19:16
    UINT32 CsOdtMapping_odt1                       :  4;  // Bits 23:20
    UINT32 lp4_cmd_mirror                          :  1;  // Bits 24:24
    UINT32 rx_analogen_grace_cnt                   :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRSCRAM_CR_DDRMISCCONTROL2_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_STRUCT;

typedef union {
  struct {
    UINT32 ROCountTrainChannel0Rank0Dev0           :  9;  // Bits 8:0
    UINT32 ROCountTrainChannel0Rank1Dev0           :  9;  // Bits 17:9
    UINT32 ROCountTrainChannel0Rank2Dev0           :  9;  // Bits 26:18
    UINT32 Spare                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_STRUCT;

typedef union {
  struct {
    UINT32 ROCountTrainChannel0Rank0Dev1           :  9;  // Bits 8:0
    UINT32 ROCountTrainChannel0Rank1Dev1           :  9;  // Bits 17:9
    UINT32 ROCountTrainChannel0Rank2Dev1           :  9;  // Bits 26:18
    UINT32 Spare                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_STRUCT;

typedef union {
  struct {
    UINT32 ROCountTrainChannel1Rank0Dev0           :  9;  // Bits 8:0
    UINT32 ROCountTrainChannel1Rank1Dev0           :  9;  // Bits 17:9
    UINT32 ROCountTrainChannel1Rank2Dev0           :  9;  // Bits 26:18
    UINT32 Spare                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_STRUCT;

typedef union {
  struct {
    UINT32 ROCountTrainChannel1Rank0Dev1           :  9;  // Bits 8:0
    UINT32 ROCountTrainChannel1Rank1Dev1           :  9;  // Bits 17:9
    UINT32 ROCountTrainChannel1Rank2Dev1           :  9;  // Bits 26:18
    UINT32 Spare                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_STRUCT;

typedef union {
  struct {
    UINT32 ROCountTrainChannel2Rank0Dev0           :  9;  // Bits 8:0
    UINT32 ROCountTrainChannel2Rank1Dev0           :  9;  // Bits 17:9
    UINT32 ROCountTrainChannel2Rank2Dev0           :  9;  // Bits 26:18
    UINT32 Spare                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_STRUCT;

typedef union {
  struct {
    UINT32 ROCountTrainChannel2Rank0Dev1           :  9;  // Bits 8:0
    UINT32 ROCountTrainChannel2Rank1Dev1           :  9;  // Bits 17:9
    UINT32 ROCountTrainChannel2Rank2Dev1           :  9;  // Bits 26:18
    UINT32 Spare                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_STRUCT;

typedef union {
  struct {
    UINT32 ROCountTrainChannel3Rank0Dev0           :  9;  // Bits 8:0
    UINT32 ROCountTrainChannel3Rank1Dev0           :  9;  // Bits 17:9
    UINT32 ROCountTrainChannel3Rank2Dev0           :  9;  // Bits 26:18
    UINT32 Spare                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_STRUCT;

typedef union {
  struct {
    UINT32 ROCountTrainChannel3Rank0Dev1           :  9;  // Bits 8:0
    UINT32 ROCountTrainChannel3Rank1Dev1           :  9;  // Bits 17:9
    UINT32 ROCountTrainChannel3Rank2Dev1           :  9;  // Bits 26:18
    UINT32 Spare                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_STRUCT;

typedef union {
  struct {
    UINT32 ROCountTrainChannel0Rank3Dev0           :  9;  // Bits 8:0
    UINT32 ROCountTrainChannel1Rank3Dev0           :  9;  // Bits 17:9
    UINT32 ROCountTrainChannel2Rank3Dev0           :  9;  // Bits 26:18
    UINT32 Spare                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_STRUCT;

typedef union {
  struct {
    UINT32 ROCountTrainChannel0Rank3Dev1           :  9;  // Bits 8:0
    UINT32 ROCountTrainChannel1Rank3Dev1           :  9;  // Bits 17:9
    UINT32 ROCountTrainChannel2Rank3Dev1           :  9;  // Bits 26:18
    UINT32 Spare                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_STRUCT;

typedef union {
  struct {
    UINT32 ROCountTrainChannel3Rank3Dev0           :  9;  // Bits 8:0
    UINT32 ROCountTrainChannel3Rank3Dev1           :  9;  // Bits 17:9
    UINT32 Spare                                   :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_ROCOUNTTRAINCH3RANK3DEV01_STRUCT;

typedef union {
  struct {
    UINT32 DevUseMapRank0                          :  4;  // Bits 3:0
    UINT32 DevUseMapRank1                          :  4;  // Bits 7:4
    UINT32 DevUseMapRank2                          :  4;  // Bits 11:8
    UINT32 DevUseMapRank3                          :  4;  // Bits 15:12
    UINT32 Spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_STRUCT_A0;

typedef union {
  struct {
    UINT32 DevUseMapRank0                          :  8;  // Bits 7:0
    UINT32 DevUseMapRank1                          :  8;  // Bits 15:8
    UINT32 DevUseMapRank2                          :  8;  // Bits 23:16
    UINT32 DevUseMapRank3                          :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_STRUCT;

typedef union {
  struct {
    UINT32 DevUseMapRank0                          :  4;  // Bits 3:0
    UINT32 DevUseMapRank1                          :  4;  // Bits 7:4
    UINT32 DevUseMapRank2                          :  4;  // Bits 11:8
    UINT32 DevUseMapRank3                          :  4;  // Bits 15:12
    UINT32 Spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_STRUCT_A0;

typedef union {
  struct {
    UINT32 DevUseMapRank0                          :  8;  // Bits 7:0
    UINT32 DevUseMapRank1                          :  8;  // Bits 15:8
    UINT32 DevUseMapRank2                          :  8;  // Bits 23:16
    UINT32 DevUseMapRank3                          :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_STRUCT;

typedef union {
  struct {
    UINT32 DevUseMapRank0                          :  4;  // Bits 3:0
    UINT32 DevUseMapRank1                          :  4;  // Bits 7:4
    UINT32 DevUseMapRank2                          :  4;  // Bits 11:8
    UINT32 DevUseMapRank3                          :  4;  // Bits 15:12
    UINT32 Spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_STRUCT_A0;

typedef union {
  struct {
    UINT32 DevUseMapRank0                          :  8;  // Bits 7:0
    UINT32 DevUseMapRank1                          :  8;  // Bits 15:8
    UINT32 DevUseMapRank2                          :  8;  // Bits 23:16
    UINT32 DevUseMapRank3                          :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_STRUCT;

typedef union {
  struct {
    UINT32 DevUseMapRank0                          :  4;  // Bits 3:0
    UINT32 DevUseMapRank1                          :  4;  // Bits 7:4
    UINT32 DevUseMapRank2                          :  4;  // Bits 11:8
    UINT32 DevUseMapRank3                          :  4;  // Bits 15:12
    UINT32 Spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_STRUCT_A0;

typedef union {
  struct {
    UINT32 DevUseMapRank0                          :  8;  // Bits 7:0
    UINT32 DevUseMapRank1                          :  8;  // Bits 15:8
    UINT32 DevUseMapRank2                          :  8;  // Bits 23:16
    UINT32 DevUseMapRank3                          :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_STRUCT;

typedef union {
  struct {
    UINT32 Lp4ReTrainDuration                      :  18;  // Bits 17:0
    UINT32 Lp4DeltaDQSTrainMode                    :  1;  // Bits 18:18
    UINT32 Lp4DeltaDQSCalcUnitOvrd                 :  1;  // Bits 19:19
    UINT32 Lp4DeltaDQSCalcUnitOvrdEn               :  1;  // Bits 20:20
    UINT32 Lp4DeltaDQSUpdateReqOvrd                :  1;  // Bits 21:21
    UINT32 Lp4DeltaDQSUpdateReqOvrdEn              :  1;  // Bits 22:22
    UINT32 Lp4DeltaDQSUpdateReqChRankSelectOrvd    :  4;  // Bits 26:23
    UINT32 Lp4RankPairSwap                         :  1;  // Bits 27:27
    UINT32 Lp4MR19ExeQueWriteEnableOvrd            :  1;  // Bits 28:28
    UINT32 Lp4MR19ExeQueWriteEnableOvrdEn          :  1;  // Bits 29:29
    UINT32 Lp4DeltaDQSROCountForceZero             :  1;  // Bits 30:30
    UINT32 InternalClocksOn                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DELTADQSCOMMON0_STRUCT_A0;

typedef union {
  struct {
    UINT32 Lp4ReTrainDuration                      :  18;  // Bits 17:0
    UINT32 Lp4DeltaDQSTrainMode                    :  1;  // Bits 18:18
    UINT32 Lp4DeltaDQSUpdateReqOvrd                :  1;  // Bits 19:19
    UINT32 Lp4DeltaDQSUpdateReqOvrdEn              :  1;  // Bits 20:20
    UINT32 Lp4DeltaDQSUpdateReqChRankSelectOrvd    :  4;  // Bits 24:21
    UINT32 InternalClocksOn                        :  1;  // Bits 25:25
    UINT32 clock_on_with_rxanalogen                :  1;  // Bits 26:26
    UINT32 retrain_cmd_type_swap_b                 :  1;  // Bits 27:27
    UINT32 spare                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DELTADQSCOMMON0_STRUCT;

typedef union {
  struct {
    UINT32 DeltaDQSAPBDistAddrOvrd                 :  16;  // Bits 15:0
    UINT32 DeltaDQSAPBDistAddrOvrdEn               :  1;  // Bits 16:16
    UINT32 DeltaDQSAPBRequestOvrd                  :  1;  // Bits 17:17
    UINT32 DeltaDQSAPBRequestOvrdEn                :  1;  // Bits 18:18
    UINT32 DeltaDQSMcQuietCycleReqChOvrd           :  4;  // Bits 22:19
    UINT32 DeltaDQSMcQuietCycleReqChOvrdEn         :  4;  // Bits 26:23
    UINT32 DfxLp4ObsROCountChRankSel               :  4;  // Bits 30:27
    UINT32 DfxLp4ObsSel                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DELTADQSCOMMON1_STRUCT;

typedef union {
  struct {
    UINT32 DfxLp4OBSData                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DELTADQSCOMMON2_STRUCT;

typedef union {
  struct {
    UINT32 CKEbuf0_Mapping                         :  3;  // Bits 2:0
    UINT32 CKEbuf1_Mapping                         :  3;  // Bits 5:3
    UINT32 CKEbuf2_Mapping                         :  3;  // Bits 8:6
    UINT32 CKEbuf3_Mapping                         :  3;  // Bits 11:9
    UINT32 CKEbuf4_Mapping                         :  3;  // Bits 14:12
    UINT32 CKEbuf5_Mapping                         :  3;  // Bits 17:15
    UINT32 CKEbuf6_Mapping                         :  3;  // Bits 20:18
    UINT32 CKEbuf7_Mapping                         :  3;  // Bits 23:21
    UINT32 use_grace_count_for_rxclk               :  1;  // Bits 24:24
    UINT32 glbdrv_clkgate_enable                   :  1;  // Bits 25:25
    UINT32 Spare2                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRSCRAM_CR_DDRMISCCONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 CKEbuf0_Mapping                         :  3;  // Bits 2:0
    UINT32 CKEbuf1_Mapping                         :  3;  // Bits 5:3
    UINT32 CKEbuf2_Mapping                         :  3;  // Bits 8:6
    UINT32 CKEbuf3_Mapping                         :  3;  // Bits 11:9
    UINT32 CKEbuf4_Mapping                         :  3;  // Bits 14:12
    UINT32 CKEbuf5_Mapping                         :  3;  // Bits 17:15
    UINT32 CKEbuf6_Mapping                         :  3;  // Bits 20:18
    UINT32 CKEbuf7_Mapping                         :  3;  // Bits 23:21
    UINT32 use_grace_count_for_rxclk               :  1;  // Bits 24:24
    UINT32 glbdrv_clkgate_enable                   :  1;  // Bits 25:25
    UINT32 Spare2                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRSCRAM_CR_DDRMISCCONTROL4_STRUCT;

typedef union {
  struct {
    UINT32 TxDqFifoRdEnRank0ChADel                 :  3;  // Bits 2:0
    UINT32 TxDqFifoRdEnRank1ChADel                 :  3;  // Bits 5:3
    UINT32 TxDqFifoRdEnRank2ChADel                 :  3;  // Bits 8:6
    UINT32 TxDqFifoRdEnRank3ChADel                 :  3;  // Bits 11:9
    UINT32 TxDqFifoRdEnRank0ChBDel                 :  3;  // Bits 14:12
    UINT32 TxDqFifoRdEnRank1ChBDel                 :  3;  // Bits 17:15
    UINT32 TxDqFifoRdEnRank2ChBDel                 :  3;  // Bits 20:18
    UINT32 TxDqFifoRdEnRank3ChBDel                 :  3;  // Bits 23:21
    UINT32 tx_analog_clk_gate_dis                  :  1;  // Bits 24:24
    UINT32 Spare                                   :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_WRITECFGCHACHB0_STRUCT;

typedef union {
  struct {
    UINT32 TxDqFifoRdEnRank0ChADel                 :  3;  // Bits 2:0
    UINT32 TxDqFifoRdEnRank1ChADel                 :  3;  // Bits 5:3
    UINT32 TxDqFifoRdEnRank2ChADel                 :  3;  // Bits 8:6
    UINT32 TxDqFifoRdEnRank3ChADel                 :  3;  // Bits 11:9
    UINT32 TxDqFifoRdEnRank0ChBDel                 :  3;  // Bits 14:12
    UINT32 TxDqFifoRdEnRank1ChBDel                 :  3;  // Bits 17:15
    UINT32 TxDqFifoRdEnRank2ChBDel                 :  3;  // Bits 20:18
    UINT32 TxDqFifoRdEnRank3ChBDel                 :  3;  // Bits 23:21
    UINT32 tx_analog_clk_gate_dis                  :  1;  // Bits 24:24
    UINT32 Spare                                   :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_WRITECFGCHACHB1_STRUCT;

typedef union {
  struct {
    UINT32 RcvEnRank0ChADel                        :  3;  // Bits 2:0
    UINT32 RcvEnRank1ChADel                        :  3;  // Bits 5:3
    UINT32 RcvEnRank2ChADel                        :  3;  // Bits 8:6
    UINT32 RcvEnRank3ChADel                        :  3;  // Bits 11:9
    UINT32 RcvEnRank0ChBDel                        :  3;  // Bits 14:12
    UINT32 RcvEnRank1ChBDel                        :  3;  // Bits 17:15
    UINT32 RcvEnRank2ChBDel                        :  3;  // Bits 20:18
    UINT32 RcvEnRank3ChBDel                        :  3;  // Bits 23:21
    UINT32 rx_analog_clk_gate_dis                  :  1;  // Bits 24:24
    UINT32 Spare                                   :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_READCFGCHACHB0_STRUCT;

typedef union {
  struct {
    UINT32 RcvEnRank0ChADel                        :  3;  // Bits 2:0
    UINT32 RcvEnRank1ChADel                        :  3;  // Bits 5:3
    UINT32 RcvEnRank2ChADel                        :  3;  // Bits 8:6
    UINT32 RcvEnRank3ChADel                        :  3;  // Bits 11:9
    UINT32 RcvEnRank0ChBDel                        :  3;  // Bits 14:12
    UINT32 RcvEnRank1ChBDel                        :  3;  // Bits 17:15
    UINT32 RcvEnRank2ChBDel                        :  3;  // Bits 20:18
    UINT32 RcvEnRank3ChBDel                        :  3;  // Bits 23:21
    UINT32 rx_analog_clk_gate_dis                  :  1;  // Bits 24:24
    UINT32 Spare                                   :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_READCFGCHACHB1_STRUCT;

typedef union {
  struct {
    UINT32 CsOdtMapping_odt2                       :  4;  // Bits 3:0
    UINT32 CsOdtMapping_odt3                       :  4;  // Bits 7:4
    UINT32 CsOdtMapping_cs4                        :  4;  // Bits 11:8
    UINT32 CsOdtMapping_cs5                        :  4;  // Bits 15:12
    UINT32 spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRSCRAM_CR_DDRMISCCONTROL5_STRUCT;

typedef union {
  struct {
    UINT32 CsOdtMapping_odt2                       :  4;  // Bits 3:0
    UINT32 CsOdtMapping_odt3                       :  4;  // Bits 7:4
    UINT32 CsOdtMapping_cs4                        :  4;  // Bits 11:8
    UINT32 CsOdtMapping_cs5                        :  4;  // Bits 15:12
    UINT32 spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRSCRAM_CR_DDRMISCCONTROL6_STRUCT;

typedef union {
  struct {
    UINT32 ForceAutoTrdy                           :  1;  // Bits 0:0
    UINT32 Spare                                   :  31;  // Bits 31:1
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_SYNAUTOTRDYSTART_STRUCT;

typedef union {
  struct {
    UINT32 DisableAutoTrdy                         :  1;  // Bits 0:0
    UINT32 Spare                                   :  31;  // Bits 31:1
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_SYNAUTOTRDYEND_STRUCT;

typedef union {
  struct {
    UINT32 RxDqFifoRdEnRank0ChADel                 :  4;  // Bits 3:0
    UINT32 RxDqFifoRdEnRank1ChADel                 :  4;  // Bits 7:4
    UINT32 RxDqFifoRdEnRank2ChADel                 :  4;  // Bits 11:8
    UINT32 RxDqFifoRdEnRank3ChADel                 :  4;  // Bits 15:12
    UINT32 RxDqFifoRdEnRank0ChBDel                 :  4;  // Bits 19:16
    UINT32 RxDqFifoRdEnRank1ChBDel                 :  4;  // Bits 23:20
    UINT32 RxDqFifoRdEnRank2ChBDel                 :  4;  // Bits 27:24
    UINT32 RxDqFifoRdEnRank3ChBDel                 :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_RXDQFIFORDENCHACHB0_STRUCT;

typedef union {
  struct {
    UINT32 RxDqFifoRdEnRank0ChADel                 :  4;  // Bits 3:0
    UINT32 RxDqFifoRdEnRank1ChADel                 :  4;  // Bits 7:4
    UINT32 RxDqFifoRdEnRank2ChADel                 :  4;  // Bits 11:8
    UINT32 RxDqFifoRdEnRank3ChADel                 :  4;  // Bits 15:12
    UINT32 RxDqFifoRdEnRank0ChBDel                 :  4;  // Bits 19:16
    UINT32 RxDqFifoRdEnRank1ChBDel                 :  4;  // Bits 23:20
    UINT32 RxDqFifoRdEnRank2ChBDel                 :  4;  // Bits 27:24
    UINT32 RxDqFifoRdEnRank3ChBDel                 :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_RXDQFIFORDENCHACHB1_STRUCT;

typedef union {
  struct {
    UINT32 Drain                                   :  1;  // Bits 0:0
    UINT32 Abort                                   :  1;  // Bits 1:1
    UINT32 TrainingMode                            :  1;  // Bits 2:2
    UINT32 OverrideMode                            :  1;  // Bits 3:3
    UINT32 GVPointG1                               :  1;  // Bits 4:4
    UINT32 DllLockCntPeriod                        :  13;  // Bits 17:5
    UINT32 Spare1                                  :  3;  // Bits 20:18
    UINT32 DccBubbleVal                            :  7;  // Bits 27:21
    UINT32 ClkGateDisable                          :  1;  // Bits 28:28
    UINT32 DisDrainEveryPllLock                    :  1;  // Bits 29:29
    UINT32 DcoLfsrDis                              :  1;  // Bits 30:30
    UINT32 TrainingDone                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DCCCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 PriodicDis                              :  1;  // Bits 0:0
    UINT32 PriodicForce                            :  1;  // Bits 1:1
    UINT32 PriodicSrc                              :  1;  // Bits 2:2
    UINT32 DcoCompEn                               :  1;  // Bits 3:3
    UINT32 ActiveBytes                             :  16;  // Bits 19:4
    UINT32 ActiveClks                              :  2;  // Bits 21:20
    UINT32 PriodicCntStartPortion                  :  10;  // Bits 31:22
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DCCMAINFSMCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 PriodicCntPeriod                        :  29;  // Bits 28:0
    UINT32 PriodicCntEn                            :  1;  // Bits 29:29
    UINT32 PriodicCntRst                           :  1;  // Bits 30:30
    UINT32 PriodicCntIndOrd                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DCCMAINFSMCONTROL1_STRUCT;

typedef union {
  struct {
    UINT32 ActiveEccBytes                          :  2;  // Bits 1:0
    UINT32 ActiveDtClks                            :  2;  // Bits 3:2
    UINT32 Spare                                   :  28;  // Bits 31:4
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DCCMAINFSMCONTROL2_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_STRUCT;

typedef union {
  struct {
    UINT32 DeSwizzleLane0                          :  3;  // Bits 2:0
    UINT32 DeSwizzleLane1                          :  3;  // Bits 5:3
    UINT32 DeSwizzleLane2                          :  3;  // Bits 8:6
    UINT32 DeSwizzleLane3                          :  3;  // Bits 11:9
    UINT32 DeSwizzleLane4                          :  3;  // Bits 14:12
    UINT32 DeSwizzleLane5                          :  3;  // Bits 17:15
    UINT32 DeSwizzleLane6                          :  3;  // Bits 20:18
    UINT32 DeSwizzleLane7                          :  3;  // Bits 23:21
    UINT32 DeSwizzleByte                           :  2;  // Bits 25:24
    UINT32 Spare                                   :  4;  // Bits 29:26
    UINT32 LP4_calc_in_progres_Override_Val        :  1;  // Bits 30:30
    UINT32 LP4_calc_in_progres_Override_En         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_STRUCT;

typedef union {
  struct {
    UINT32 ROCountTrainChannel0Rank0Dev0           :  9;  // Bits 8:0
    UINT32 ROCountTrainChannel0Rank1Dev0           :  9;  // Bits 17:9
    UINT32 ROCountTrainChannel0Rank2Dev0           :  9;  // Bits 26:18
    UINT32 Spare                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_STRUCT;

typedef union {
  struct {
    UINT32 ROCountTrainChannel0Rank0Dev1           :  9;  // Bits 8:0
    UINT32 ROCountTrainChannel0Rank1Dev1           :  9;  // Bits 17:9
    UINT32 ROCountTrainChannel0Rank2Dev1           :  9;  // Bits 26:18
    UINT32 Spare                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_STRUCT;

typedef union {
  struct {
    UINT32 ROCountTrainChannel1Rank0Dev0           :  9;  // Bits 8:0
    UINT32 ROCountTrainChannel1Rank1Dev0           :  9;  // Bits 17:9
    UINT32 ROCountTrainChannel1Rank2Dev0           :  9;  // Bits 26:18
    UINT32 Spare                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_STRUCT;

typedef union {
  struct {
    UINT32 ROCountTrainChannel1Rank0Dev1           :  9;  // Bits 8:0
    UINT32 ROCountTrainChannel1Rank1Dev1           :  9;  // Bits 17:9
    UINT32 ROCountTrainChannel1Rank2Dev1           :  9;  // Bits 26:18
    UINT32 Spare                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_STRUCT;

typedef union {
  struct {
    UINT32 ROCountTrainChannel2Rank0Dev0           :  9;  // Bits 8:0
    UINT32 ROCountTrainChannel2Rank1Dev0           :  9;  // Bits 17:9
    UINT32 ROCountTrainChannel2Rank2Dev0           :  9;  // Bits 26:18
    UINT32 Spare                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_STRUCT;

typedef union {
  struct {
    UINT32 ROCountTrainChannel2Rank0Dev1           :  9;  // Bits 8:0
    UINT32 ROCountTrainChannel2Rank1Dev1           :  9;  // Bits 17:9
    UINT32 ROCountTrainChannel2Rank2Dev1           :  9;  // Bits 26:18
    UINT32 Spare                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_STRUCT;

typedef union {
  struct {
    UINT32 ROCountTrainChannel3Rank0Dev0           :  9;  // Bits 8:0
    UINT32 ROCountTrainChannel3Rank1Dev0           :  9;  // Bits 17:9
    UINT32 ROCountTrainChannel3Rank2Dev0           :  9;  // Bits 26:18
    UINT32 Spare                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_STRUCT;

typedef union {
  struct {
    UINT32 ROCountTrainChannel3Rank0Dev1           :  9;  // Bits 8:0
    UINT32 ROCountTrainChannel3Rank1Dev1           :  9;  // Bits 17:9
    UINT32 ROCountTrainChannel3Rank2Dev1           :  9;  // Bits 26:18
    UINT32 Spare                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_STRUCT;

typedef union {
  struct {
    UINT32 ROCountTrainChannel0Rank3Dev0           :  9;  // Bits 8:0
    UINT32 ROCountTrainChannel1Rank3Dev0           :  9;  // Bits 17:9
    UINT32 ROCountTrainChannel2Rank3Dev0           :  9;  // Bits 26:18
    UINT32 Spare                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_STRUCT;

typedef union {
  struct {
    UINT32 ROCountTrainChannel0Rank3Dev1           :  9;  // Bits 8:0
    UINT32 ROCountTrainChannel1Rank3Dev1           :  9;  // Bits 17:9
    UINT32 ROCountTrainChannel2Rank3Dev1           :  9;  // Bits 26:18
    UINT32 Spare                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_STRUCT;

typedef union {
  struct {
    UINT32 ROCountTrainChannel3Rank3Dev0           :  9;  // Bits 8:0
    UINT32 ROCountTrainChannel3Rank3Dev1           :  9;  // Bits 17:9
    UINT32 Spare                                   :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_ROCOUNTTRAINCH3RANK3DEV23_STRUCT;

typedef union {
  struct {
    UINT32 AllDccDone                              :  1;  // Bits 0:0
    UINT32 DccByteDone                             :  16;  // Bits 16:1
    UINT32 DccEccByteDone                          :  2;  // Bits 18:17
    UINT32 DcoCompDone                             :  1;  // Bits 19:19
    UINT32 CurrState                               :  5;  // Bits 24:20
    UINT32 DccClkDone                              :  2;  // Bits 26:25
    UINT32 DccDtClkDone                            :  2;  // Bits 28:27
    UINT32 Spare                                   :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DCCMAINFSMSTATUS0_STRUCT;

typedef union {
  struct {
    UINT32 DfxLp4OBSData                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DELTADQSCOMMON2DEV23_STRUCT;

typedef union {
  struct {
    UINT32 Lp4DeltaDQSCalcUnitOvrd                 :  2;  // Bits 1:0
    UINT32 Lp4DeltaDQSCalcUnitOvrdEn               :  2;  // Bits 3:2
    UINT32 Lp4RankPairSwap                         :  2;  // Bits 5:4
    UINT32 Lp4MR19ExeQueWriteEnableOvrd            :  2;  // Bits 7:6
    UINT32 Lp4MR19ExeQueWriteEnableOvrdEn          :  2;  // Bits 9:8
    UINT32 Lp4DeltaDQSROCountForceZero             :  2;  // Bits 11:10
    UINT32 spare                                   :  20;  // Bits 31:12
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMISCS_DELTADQSCOMMON3_STRUCT;

#pragma pack(pop)
#endif
