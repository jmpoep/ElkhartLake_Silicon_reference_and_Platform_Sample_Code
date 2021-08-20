#ifndef __MrcMcRegisterIcl3xxx_h__
#define __MrcMcRegisterIcl3xxx_h__
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


#define DDRSCRAM_CR_DDRSCRAMBLECH0_REG                                 (0x00003000)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramEn_OFF                       ( 0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramEn_WID                       ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramEn_MSK                       (0x00000001)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramEn_MIN                       (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramEn_MAX                       (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramEn_DEF                       (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramEn_HSH                       (0x01003000)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramKey_OFF                      ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramKey_WID                      (16)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramKey_MSK                      (0x0001FFFE)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramKey_MIN                      (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramKey_MAX                      (65535) // 0x0000FFFF
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramKey_DEF                      (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ScramKey_HSH                      (0x10013000)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateAB_OFF                   (17)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateAB_WID                   ( 2)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateAB_MSK                   (0x00060000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateAB_MIN                   (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateAB_MAX                   (3) // 0x00000003
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateAB_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateAB_HSH                   (0x02113000)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateC_OFF                    (19)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateC_WID                    ( 2)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateC_MSK                    (0x00180000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateC_MIN                    (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateC_MAX                    (3) // 0x00000003
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateC_DEF                    (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ClockGateC_HSH                    (0x02133000)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EnableDbiAB_OFF                   (21)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EnableDbiAB_WID                   ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EnableDbiAB_MSK                   (0x00200000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EnableDbiAB_MIN                   (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EnableDbiAB_MAX                   (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EnableDbiAB_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EnableDbiAB_HSH                   (0x01153000)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_en_dilution_mode_OFF              (22)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_en_dilution_mode_WID              ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_en_dilution_mode_MSK              (0x00400000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_en_dilution_mode_MIN              (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_en_dilution_mode_MAX              (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_en_dilution_mode_DEF              (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_en_dilution_mode_HSH              (0x01163000)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ca_mirrored_OFF                   (23)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ca_mirrored_WID                   ( 4)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ca_mirrored_MSK                   (0x07800000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ca_mirrored_MIN                   (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ca_mirrored_MAX                   (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ca_mirrored_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_ca_mirrored_HSH                   (0x04173000)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_cmdanalogen_OFF               (27)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_cmdanalogen_WID               ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_cmdanalogen_MSK               (0x08000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_cmdanalogen_MIN               (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_cmdanalogen_MAX               (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_cmdanalogen_DEF               (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_cmdanalogen_HSH               (0x011B3000)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_CmdAnaLogEn_at_IDLE_OFF       (28)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_CmdAnaLogEn_at_IDLE_WID       ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_CmdAnaLogEn_at_IDLE_MSK       (0x10000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_CmdAnaLogEn_at_IDLE_MIN       (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_CmdAnaLogEn_at_IDLE_MAX       (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_CmdAnaLogEn_at_IDLE_DEF       (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_dis_CmdAnaLogEn_at_IDLE_HSH       (0x011C3000)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_VsshiCompActive_OFF               (29)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_VsshiCompActive_WID               ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_VsshiCompActive_MSK               (0x20000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_VsshiCompActive_MIN               (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_VsshiCompActive_MAX               (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_VsshiCompActive_DEF               (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_VsshiCompActive_HSH               (0x011D3000)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EN_VsshiCompActive_on_lp4retrain_OFF (30)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EN_VsshiCompActive_on_lp4retrain_WID ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EN_VsshiCompActive_on_lp4retrain_MSK (0x40000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EN_VsshiCompActive_on_lp4retrain_MIN (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EN_VsshiCompActive_on_lp4retrain_MAX (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EN_VsshiCompActive_on_lp4retrain_DEF (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_EN_VsshiCompActive_on_lp4retrain_HSH (0x011E3000)

  #define DDRSCRAM_CR_DDRSCRAMBLECH0_forcecompdist_OFF                 (31)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_forcecompdist_WID                 ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_forcecompdist_MSK                 (0x80000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_forcecompdist_MIN                 (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_forcecompdist_MAX                 (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_forcecompdist_DEF                 (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH0_forcecompdist_HSH                 (0x011F3000)

#define DDRSCRAM_CR_DDRSCRAMBLECH1_REG                                 (0x00003004)

  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramEn_OFF                       ( 0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramEn_WID                       ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramEn_MSK                       (0x00000001)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramEn_MIN                       (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramEn_MAX                       (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramEn_DEF                       (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramEn_HSH                       (0x01003004)

  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramKey_OFF                      ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramKey_WID                      (16)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramKey_MSK                      (0x0001FFFE)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramKey_MIN                      (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramKey_MAX                      (65535) // 0x0000FFFF
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramKey_DEF                      (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ScramKey_HSH                      (0x10013004)

  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateAB_OFF                   (17)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateAB_WID                   ( 2)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateAB_MSK                   (0x00060000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateAB_MIN                   (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateAB_MAX                   (3) // 0x00000003
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateAB_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateAB_HSH                   (0x02113004)

  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateC_OFF                    (19)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateC_WID                    ( 2)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateC_MSK                    (0x00180000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateC_MIN                    (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateC_MAX                    (3) // 0x00000003
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateC_DEF                    (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ClockGateC_HSH                    (0x02133004)

  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EnableDbiAB_OFF                   (21)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EnableDbiAB_WID                   ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EnableDbiAB_MSK                   (0x00200000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EnableDbiAB_MIN                   (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EnableDbiAB_MAX                   (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EnableDbiAB_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EnableDbiAB_HSH                   (0x01153004)

  #define DDRSCRAM_CR_DDRSCRAMBLECH1_en_dilution_mode_OFF              (22)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_en_dilution_mode_WID              ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_en_dilution_mode_MSK              (0x00400000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_en_dilution_mode_MIN              (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_en_dilution_mode_MAX              (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_en_dilution_mode_DEF              (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_en_dilution_mode_HSH              (0x01163004)

  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ca_mirrored_OFF                   (23)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ca_mirrored_WID                   ( 4)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ca_mirrored_MSK                   (0x07800000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ca_mirrored_MIN                   (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ca_mirrored_MAX                   (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ca_mirrored_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_ca_mirrored_HSH                   (0x04173004)

  #define DDRSCRAM_CR_DDRSCRAMBLECH1_DfxLp4OBSDeltaDQSDistAck_OFF      (27)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_DfxLp4OBSDeltaDQSDistAck_WID      ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_DfxLp4OBSDeltaDQSDistAck_MSK      (0x08000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_DfxLp4OBSDeltaDQSDistAck_MIN      (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_DfxLp4OBSDeltaDQSDistAck_MAX      (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_DfxLp4OBSDeltaDQSDistAck_DEF      (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_DfxLp4OBSDeltaDQSDistAck_HSH      (0x011B3004)

  #define DDRSCRAM_CR_DDRSCRAMBLECH1_DfxLp4OBSDeltaDQSDistReq_OFF      (28)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_DfxLp4OBSDeltaDQSDistReq_WID      ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_DfxLp4OBSDeltaDQSDistReq_MSK      (0x10000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_DfxLp4OBSDeltaDQSDistReq_MIN      (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_DfxLp4OBSDeltaDQSDistReq_MAX      (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_DfxLp4OBSDeltaDQSDistReq_DEF      (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_DfxLp4OBSDeltaDQSDistReq_HSH      (0x011C3004)

  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EarlyRankRdValidSwitch_OFF        (29)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EarlyRankRdValidSwitch_WID        ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EarlyRankRdValidSwitch_MSK        (0x20000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EarlyRankRdValidSwitch_MIN        (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EarlyRankRdValidSwitch_MAX        (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EarlyRankRdValidSwitch_DEF        (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_EarlyRankRdValidSwitch_HSH        (0x011D3004)

  #define DDRSCRAM_CR_DDRSCRAMBLECH1_Spare_OFF                         (30)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_Spare_WID                         ( 2)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_Spare_MSK                         (0xC0000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_Spare_MIN                         (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_Spare_MAX                         (3) // 0x00000003
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_Spare_DEF                         (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH1_Spare_HSH                         (0x021E3004)

#define DDRSCRAM_CR_DDRMISCCONTROL0_REG                                (0x00003008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_WakeCycles_OFF                ( 0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_WakeCycles_WID                ( 2)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_WakeCycles_MSK                (0x00000003)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_WakeCycles_MIN                (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_WakeCycles_MAX                (3) // 0x00000003
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_WakeCycles_DEF                (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_WakeCycles_HSH                (0x02003008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_SleepCycles_OFF               ( 2)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_SleepCycles_WID               ( 3)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_SleepCycles_MSK               (0x0000001C)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_SleepCycles_MIN               (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_SleepCycles_MAX               (7) // 0x00000007
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_SleepCycles_DEF               (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WL_SleepCycles_HSH               (0x03023008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_CompAndDeltaDqsUpdateClkGateDisable_OFF ( 5)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_CompAndDeltaDqsUpdateClkGateDisable_WID ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_CompAndDeltaDqsUpdateClkGateDisable_MSK (0x00000020)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_CompAndDeltaDqsUpdateClkGateDisable_MIN (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_CompAndDeltaDqsUpdateClkGateDisable_MAX (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_CompAndDeltaDqsUpdateClkGateDisable_DEF (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_CompAndDeltaDqsUpdateClkGateDisable_HSH (0x01053008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_WeakLock_Latency_OFF             ( 6)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WeakLock_Latency_WID             ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WeakLock_Latency_MSK             (0x000003C0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WeakLock_Latency_MIN             (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WeakLock_Latency_MAX             (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WeakLock_Latency_DEF             (0x0000000C)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_WeakLock_Latency_HSH             (0x04063008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_OFF            (10)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_WID            ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_MSK            (0x00000400)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_MIN            (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_MAX            (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_DEF            (0x00000001)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_HSH            (0x010A3008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_OFF                   (11)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_WID                   ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_MSK                   (0x00000800)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_MIN                   (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_MAX                   (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_HSH                   (0x010B3008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_lp4_rcven_ctrl_OFF               (12)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_lp4_rcven_ctrl_WID               ( 2)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_lp4_rcven_ctrl_MSK               (0x00003000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_lp4_rcven_ctrl_MIN               (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_lp4_rcven_ctrl_MAX               (3) // 0x00000003
  #define DDRSCRAM_CR_DDRMISCCONTROL0_lp4_rcven_ctrl_DEF               (0x00000002)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_lp4_rcven_ctrl_HSH               (0x020C3008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_ddr_centric_OFF                  (14)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ddr_centric_WID                  ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ddr_centric_MSK                  (0x00004000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ddr_centric_MIN                  (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ddr_centric_MAX                  (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ddr_centric_DEF                  (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ddr_centric_HSH                  (0x010E3008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_ECCPresent_OFF                   (15)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ECCPresent_WID                   ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ECCPresent_MSK                   (0x00008000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ECCPresent_MIN                   (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ECCPresent_MAX                   (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ECCPresent_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ECCPresent_HSH                   (0x010F3008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_RcvEn_Extension_OFF              (16)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_RcvEn_Extension_WID              ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_RcvEn_Extension_MSK              (0x000F0000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_RcvEn_Extension_MIN              (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_RcvEn_Extension_MAX              (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL0_RcvEn_Extension_DEF              (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_RcvEn_Extension_HSH              (0x04103008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_OFF                    (20)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_WID                    ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_MSK                    (0x00100000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_MIN                    (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_MAX                    (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_DEF                    (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_HSH                    (0x01143008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_OFF               (21)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_WID               ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_MSK               (0x00200000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_MIN               (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_MAX               (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_DEF               (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_HSH               (0x01153008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_DllDataWeakLckEn_OFF             (22)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DllDataWeakLckEn_WID             ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DllDataWeakLckEn_MSK             (0x00400000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DllDataWeakLckEn_MIN             (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DllDataWeakLckEn_MAX             (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DllDataWeakLckEn_DEF             (0x00000001)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DllDataWeakLckEn_HSH             (0x01163008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_OFF         (23)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_WID         ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_MSK         (0x00800000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_MIN         (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_MAX         (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_DEF         (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_HSH         (0x01173008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_FourChCfg_OFF                    (24)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_FourChCfg_WID                    ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_FourChCfg_MSK                    (0x01000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_FourChCfg_MIN                    (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_FourChCfg_MAX                    (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_FourChCfg_DEF                    (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_FourChCfg_HSH                    (0x01183008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_LpDdr4Mode_OFF                   (25)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LpDdr4Mode_WID                   ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LpDdr4Mode_MSK                   (0x02000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LpDdr4Mode_MIN                   (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LpDdr4Mode_MAX                   (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LpDdr4Mode_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_LpDdr4Mode_HSH                   (0x01193008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_OFF        (26)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_WID        ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_MSK        (0x3C000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_MIN        (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_MAX        (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_DEF        (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_HSH        (0x041A3008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_dis_iosf_sb_clk_gate_OFF         (30)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_dis_iosf_sb_clk_gate_WID         ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_dis_iosf_sb_clk_gate_MSK         (0x40000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_dis_iosf_sb_clk_gate_MIN         (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_dis_iosf_sb_clk_gate_MAX         (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_dis_iosf_sb_clk_gate_DEF         (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_dis_iosf_sb_clk_gate_HSH         (0x011E3008)

  #define DDRSCRAM_CR_DDRMISCCONTROL0_Gear1_OFF                        (31)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Gear1_WID                        ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Gear1_MSK                        (0x80000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Gear1_MIN                        (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Gear1_MAX                        (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Gear1_DEF                        (0x00000001)
  #define DDRSCRAM_CR_DDRMISCCONTROL0_Gear1_HSH                        (0x011F3008)

#define MCMISCS_WRITECFGCH0_REG                                        (0x0000300C)

  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoWrEn_OFF                    ( 0)
  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoWrEn_WID                    ( 6)
  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoWrEn_MSK                    (0x0000003F)
  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoWrEn_MIN                    (0)
  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoWrEn_MAX                    (63) // 0x0000003F
  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoWrEn_DEF                    (0x00000000)
  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoWrEn_HSH                    (0x0600300C)

  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoRdEn_OFF                    ( 6)
  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoRdEn_WID                    ( 6)
  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoRdEn_MSK                    (0x00000FC0)
  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoRdEn_MIN                    (0)
  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoRdEn_MAX                    (63) // 0x0000003F
  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoRdEn_DEF                    (0x00000000)
  #define MCMISCS_WRITECFGCH0_tCWL4TxDqFifoRdEn_HSH                    (0x0606300C)

  #define MCMISCS_WRITECFGCH0_Spare_OFF                                (12)
  #define MCMISCS_WRITECFGCH0_Spare_WID                                ( 7)
  #define MCMISCS_WRITECFGCH0_Spare_MSK                                (0x0007F000)
  #define MCMISCS_WRITECFGCH0_Spare_MIN                                (0)
  #define MCMISCS_WRITECFGCH0_Spare_MAX                                (127) // 0x0000007F
  #define MCMISCS_WRITECFGCH0_Spare_DEF                                (0x00000000)
  #define MCMISCS_WRITECFGCH0_Spare_HSH                                (0x070C300C)

  #define MCMISCS_WRITECFGCH0_RptChDqTxClkOn_OFF                       (19)
  #define MCMISCS_WRITECFGCH0_RptChDqTxClkOn_WID                       ( 1)
  #define MCMISCS_WRITECFGCH0_RptChDqTxClkOn_MSK                       (0x00080000)
  #define MCMISCS_WRITECFGCH0_RptChDqTxClkOn_MIN                       (0)
  #define MCMISCS_WRITECFGCH0_RptChDqTxClkOn_MAX                       (1) // 0x00000001
  #define MCMISCS_WRITECFGCH0_RptChDqTxClkOn_DEF                       (0x00000000)
  #define MCMISCS_WRITECFGCH0_RptChDqTxClkOn_HSH                       (0x0113300C)

  #define MCMISCS_WRITECFGCH0_RptChDqRxClkOn_OFF                       (20)
  #define MCMISCS_WRITECFGCH0_RptChDqRxClkOn_WID                       ( 1)
  #define MCMISCS_WRITECFGCH0_RptChDqRxClkOn_MSK                       (0x00100000)
  #define MCMISCS_WRITECFGCH0_RptChDqRxClkOn_MIN                       (0)
  #define MCMISCS_WRITECFGCH0_RptChDqRxClkOn_MAX                       (1) // 0x00000001
  #define MCMISCS_WRITECFGCH0_RptChDqRxClkOn_DEF                       (0x00000000)
  #define MCMISCS_WRITECFGCH0_RptChDqRxClkOn_HSH                       (0x0114300C)

  #define MCMISCS_WRITECFGCH0_RptChRepClkOn_OFF                        (21)
  #define MCMISCS_WRITECFGCH0_RptChRepClkOn_WID                        ( 1)
  #define MCMISCS_WRITECFGCH0_RptChRepClkOn_MSK                        (0x00200000)
  #define MCMISCS_WRITECFGCH0_RptChRepClkOn_MIN                        (0)
  #define MCMISCS_WRITECFGCH0_RptChRepClkOn_MAX                        (1) // 0x00000001
  #define MCMISCS_WRITECFGCH0_RptChRepClkOn_DEF                        (0x00000000)
  #define MCMISCS_WRITECFGCH0_RptChRepClkOn_HSH                        (0x0115300C)

  #define MCMISCS_WRITECFGCH0_CmdAnlgEnGraceCnt_OFF                    (22)
  #define MCMISCS_WRITECFGCH0_CmdAnlgEnGraceCnt_WID                    ( 3)
  #define MCMISCS_WRITECFGCH0_CmdAnlgEnGraceCnt_MSK                    (0x01C00000)
  #define MCMISCS_WRITECFGCH0_CmdAnlgEnGraceCnt_MIN                    (0)
  #define MCMISCS_WRITECFGCH0_CmdAnlgEnGraceCnt_MAX                    (7) // 0x00000007
  #define MCMISCS_WRITECFGCH0_CmdAnlgEnGraceCnt_DEF                    (0x00000007)
  #define MCMISCS_WRITECFGCH0_CmdAnlgEnGraceCnt_HSH                    (0x0316300C)

  #define MCMISCS_WRITECFGCH0_TxAnlgEnGraceCnt_OFF                     (25)
  #define MCMISCS_WRITECFGCH0_TxAnlgEnGraceCnt_WID                     ( 6)
  #define MCMISCS_WRITECFGCH0_TxAnlgEnGraceCnt_MSK                     (0x7E000000)
  #define MCMISCS_WRITECFGCH0_TxAnlgEnGraceCnt_MIN                     (0)
  #define MCMISCS_WRITECFGCH0_TxAnlgEnGraceCnt_MAX                     (63) // 0x0000003F
  #define MCMISCS_WRITECFGCH0_TxAnlgEnGraceCnt_DEF                     (0x0000003F)
  #define MCMISCS_WRITECFGCH0_TxAnlgEnGraceCnt_HSH                     (0x0619300C)

  #define MCMISCS_WRITECFGCH0_TxDqFifoRdEnPerRankDelDis_OFF            (31)
  #define MCMISCS_WRITECFGCH0_TxDqFifoRdEnPerRankDelDis_WID            ( 1)
  #define MCMISCS_WRITECFGCH0_TxDqFifoRdEnPerRankDelDis_MSK            (0x80000000)
  #define MCMISCS_WRITECFGCH0_TxDqFifoRdEnPerRankDelDis_MIN            (0)
  #define MCMISCS_WRITECFGCH0_TxDqFifoRdEnPerRankDelDis_MAX            (1) // 0x00000001
  #define MCMISCS_WRITECFGCH0_TxDqFifoRdEnPerRankDelDis_DEF            (0x00000000)
  #define MCMISCS_WRITECFGCH0_TxDqFifoRdEnPerRankDelDis_HSH            (0x011F300C)

#define MCMISCS_WRITECFGCH1_REG                                        (0x00003010)

  #define MCMISCS_WRITECFGCH1_tCWL4TxDqFifoWrEn_OFF                    ( 0)
  #define MCMISCS_WRITECFGCH1_tCWL4TxDqFifoWrEn_WID                    ( 6)
  #define MCMISCS_WRITECFGCH1_tCWL4TxDqFifoWrEn_MSK                    (0x0000003F)
  #define MCMISCS_WRITECFGCH1_tCWL4TxDqFifoWrEn_MIN                    (0)
  #define MCMISCS_WRITECFGCH1_tCWL4TxDqFifoWrEn_MAX                    (63) // 0x0000003F
  #define MCMISCS_WRITECFGCH1_tCWL4TxDqFifoWrEn_DEF                    (0x00000000)
  #define MCMISCS_WRITECFGCH1_tCWL4TxDqFifoWrEn_HSH                    (0x06003010)

  #define MCMISCS_WRITECFGCH1_tCWL4TxDqFifoRdEn_OFF                    ( 6)
  #define MCMISCS_WRITECFGCH1_tCWL4TxDqFifoRdEn_WID                    ( 6)
  #define MCMISCS_WRITECFGCH1_tCWL4TxDqFifoRdEn_MSK                    (0x00000FC0)
  #define MCMISCS_WRITECFGCH1_tCWL4TxDqFifoRdEn_MIN                    (0)
  #define MCMISCS_WRITECFGCH1_tCWL4TxDqFifoRdEn_MAX                    (63) // 0x0000003F
  #define MCMISCS_WRITECFGCH1_tCWL4TxDqFifoRdEn_DEF                    (0x00000000)
  #define MCMISCS_WRITECFGCH1_tCWL4TxDqFifoRdEn_HSH                    (0x06063010)

  #define MCMISCS_WRITECFGCH1_Spare_OFF                                (12)
  #define MCMISCS_WRITECFGCH1_Spare_WID                                ( 7)
  #define MCMISCS_WRITECFGCH1_Spare_MSK                                (0x0007F000)
  #define MCMISCS_WRITECFGCH1_Spare_MIN                                (0)
  #define MCMISCS_WRITECFGCH1_Spare_MAX                                (127) // 0x0000007F
  #define MCMISCS_WRITECFGCH1_Spare_DEF                                (0x00000000)
  #define MCMISCS_WRITECFGCH1_Spare_HSH                                (0x070C3010)

  #define MCMISCS_WRITECFGCH1_RptChDqTxClkOn_OFF                       (19)
  #define MCMISCS_WRITECFGCH1_RptChDqTxClkOn_WID                       ( 1)
  #define MCMISCS_WRITECFGCH1_RptChDqTxClkOn_MSK                       (0x00080000)
  #define MCMISCS_WRITECFGCH1_RptChDqTxClkOn_MIN                       (0)
  #define MCMISCS_WRITECFGCH1_RptChDqTxClkOn_MAX                       (1) // 0x00000001
  #define MCMISCS_WRITECFGCH1_RptChDqTxClkOn_DEF                       (0x00000000)
  #define MCMISCS_WRITECFGCH1_RptChDqTxClkOn_HSH                       (0x01133010)

  #define MCMISCS_WRITECFGCH1_RptChDqRxClkOn_OFF                       (20)
  #define MCMISCS_WRITECFGCH1_RptChDqRxClkOn_WID                       ( 1)
  #define MCMISCS_WRITECFGCH1_RptChDqRxClkOn_MSK                       (0x00100000)
  #define MCMISCS_WRITECFGCH1_RptChDqRxClkOn_MIN                       (0)
  #define MCMISCS_WRITECFGCH1_RptChDqRxClkOn_MAX                       (1) // 0x00000001
  #define MCMISCS_WRITECFGCH1_RptChDqRxClkOn_DEF                       (0x00000000)
  #define MCMISCS_WRITECFGCH1_RptChDqRxClkOn_HSH                       (0x01143010)

  #define MCMISCS_WRITECFGCH1_RptChRepClkOn_OFF                        (21)
  #define MCMISCS_WRITECFGCH1_RptChRepClkOn_WID                        ( 1)
  #define MCMISCS_WRITECFGCH1_RptChRepClkOn_MSK                        (0x00200000)
  #define MCMISCS_WRITECFGCH1_RptChRepClkOn_MIN                        (0)
  #define MCMISCS_WRITECFGCH1_RptChRepClkOn_MAX                        (1) // 0x00000001
  #define MCMISCS_WRITECFGCH1_RptChRepClkOn_DEF                        (0x00000000)
  #define MCMISCS_WRITECFGCH1_RptChRepClkOn_HSH                        (0x01153010)

  #define MCMISCS_WRITECFGCH1_CmdAnlgEnGraceCnt_OFF                    (22)
  #define MCMISCS_WRITECFGCH1_CmdAnlgEnGraceCnt_WID                    ( 3)
  #define MCMISCS_WRITECFGCH1_CmdAnlgEnGraceCnt_MSK                    (0x01C00000)
  #define MCMISCS_WRITECFGCH1_CmdAnlgEnGraceCnt_MIN                    (0)
  #define MCMISCS_WRITECFGCH1_CmdAnlgEnGraceCnt_MAX                    (7) // 0x00000007
  #define MCMISCS_WRITECFGCH1_CmdAnlgEnGraceCnt_DEF                    (0x00000007)
  #define MCMISCS_WRITECFGCH1_CmdAnlgEnGraceCnt_HSH                    (0x03163010)

  #define MCMISCS_WRITECFGCH1_TxAnlgEnGraceCnt_OFF                     (25)
  #define MCMISCS_WRITECFGCH1_TxAnlgEnGraceCnt_WID                     ( 6)
  #define MCMISCS_WRITECFGCH1_TxAnlgEnGraceCnt_MSK                     (0x7E000000)
  #define MCMISCS_WRITECFGCH1_TxAnlgEnGraceCnt_MIN                     (0)
  #define MCMISCS_WRITECFGCH1_TxAnlgEnGraceCnt_MAX                     (63) // 0x0000003F
  #define MCMISCS_WRITECFGCH1_TxAnlgEnGraceCnt_DEF                     (0x0000003F)
  #define MCMISCS_WRITECFGCH1_TxAnlgEnGraceCnt_HSH                     (0x06193010)

  #define MCMISCS_WRITECFGCH1_TxDqFifoRdEnPerRankDelDis_OFF            (31)
  #define MCMISCS_WRITECFGCH1_TxDqFifoRdEnPerRankDelDis_WID            ( 1)
  #define MCMISCS_WRITECFGCH1_TxDqFifoRdEnPerRankDelDis_MSK            (0x80000000)
  #define MCMISCS_WRITECFGCH1_TxDqFifoRdEnPerRankDelDis_MIN            (0)
  #define MCMISCS_WRITECFGCH1_TxDqFifoRdEnPerRankDelDis_MAX            (1) // 0x00000001
  #define MCMISCS_WRITECFGCH1_TxDqFifoRdEnPerRankDelDis_DEF            (0x00000000)
  #define MCMISCS_WRITECFGCH1_TxDqFifoRdEnPerRankDelDis_HSH            (0x011F3010)

#define MCMISCS_WRITECFGCH2_REG                                        (0x00003014)

  #define MCMISCS_WRITECFGCH2_tCWL4TxDqFifoWrEn_OFF                    ( 0)
  #define MCMISCS_WRITECFGCH2_tCWL4TxDqFifoWrEn_WID                    ( 6)
  #define MCMISCS_WRITECFGCH2_tCWL4TxDqFifoWrEn_MSK                    (0x0000003F)
  #define MCMISCS_WRITECFGCH2_tCWL4TxDqFifoWrEn_MIN                    (0)
  #define MCMISCS_WRITECFGCH2_tCWL4TxDqFifoWrEn_MAX                    (63) // 0x0000003F
  #define MCMISCS_WRITECFGCH2_tCWL4TxDqFifoWrEn_DEF                    (0x00000000)
  #define MCMISCS_WRITECFGCH2_tCWL4TxDqFifoWrEn_HSH                    (0x06003014)

  #define MCMISCS_WRITECFGCH2_tCWL4TxDqFifoRdEn_OFF                    ( 6)
  #define MCMISCS_WRITECFGCH2_tCWL4TxDqFifoRdEn_WID                    ( 6)
  #define MCMISCS_WRITECFGCH2_tCWL4TxDqFifoRdEn_MSK                    (0x00000FC0)
  #define MCMISCS_WRITECFGCH2_tCWL4TxDqFifoRdEn_MIN                    (0)
  #define MCMISCS_WRITECFGCH2_tCWL4TxDqFifoRdEn_MAX                    (63) // 0x0000003F
  #define MCMISCS_WRITECFGCH2_tCWL4TxDqFifoRdEn_DEF                    (0x00000000)
  #define MCMISCS_WRITECFGCH2_tCWL4TxDqFifoRdEn_HSH                    (0x06063014)

  #define MCMISCS_WRITECFGCH2_Spare_OFF                                (12)
  #define MCMISCS_WRITECFGCH2_Spare_WID                                ( 7)
  #define MCMISCS_WRITECFGCH2_Spare_MSK                                (0x0007F000)
  #define MCMISCS_WRITECFGCH2_Spare_MIN                                (0)
  #define MCMISCS_WRITECFGCH2_Spare_MAX                                (127) // 0x0000007F
  #define MCMISCS_WRITECFGCH2_Spare_DEF                                (0x00000000)
  #define MCMISCS_WRITECFGCH2_Spare_HSH                                (0x070C3014)

  #define MCMISCS_WRITECFGCH2_RptChDqTxClkOn_OFF                       (19)
  #define MCMISCS_WRITECFGCH2_RptChDqTxClkOn_WID                       ( 1)
  #define MCMISCS_WRITECFGCH2_RptChDqTxClkOn_MSK                       (0x00080000)
  #define MCMISCS_WRITECFGCH2_RptChDqTxClkOn_MIN                       (0)
  #define MCMISCS_WRITECFGCH2_RptChDqTxClkOn_MAX                       (1) // 0x00000001
  #define MCMISCS_WRITECFGCH2_RptChDqTxClkOn_DEF                       (0x00000000)
  #define MCMISCS_WRITECFGCH2_RptChDqTxClkOn_HSH                       (0x01133014)

  #define MCMISCS_WRITECFGCH2_RptChDqRxClkOn_OFF                       (20)
  #define MCMISCS_WRITECFGCH2_RptChDqRxClkOn_WID                       ( 1)
  #define MCMISCS_WRITECFGCH2_RptChDqRxClkOn_MSK                       (0x00100000)
  #define MCMISCS_WRITECFGCH2_RptChDqRxClkOn_MIN                       (0)
  #define MCMISCS_WRITECFGCH2_RptChDqRxClkOn_MAX                       (1) // 0x00000001
  #define MCMISCS_WRITECFGCH2_RptChDqRxClkOn_DEF                       (0x00000000)
  #define MCMISCS_WRITECFGCH2_RptChDqRxClkOn_HSH                       (0x01143014)

  #define MCMISCS_WRITECFGCH2_RptChRepClkOn_OFF                        (21)
  #define MCMISCS_WRITECFGCH2_RptChRepClkOn_WID                        ( 1)
  #define MCMISCS_WRITECFGCH2_RptChRepClkOn_MSK                        (0x00200000)
  #define MCMISCS_WRITECFGCH2_RptChRepClkOn_MIN                        (0)
  #define MCMISCS_WRITECFGCH2_RptChRepClkOn_MAX                        (1) // 0x00000001
  #define MCMISCS_WRITECFGCH2_RptChRepClkOn_DEF                        (0x00000000)
  #define MCMISCS_WRITECFGCH2_RptChRepClkOn_HSH                        (0x01153014)

  #define MCMISCS_WRITECFGCH2_CmdAnlgEnGraceCnt_OFF                    (22)
  #define MCMISCS_WRITECFGCH2_CmdAnlgEnGraceCnt_WID                    ( 3)
  #define MCMISCS_WRITECFGCH2_CmdAnlgEnGraceCnt_MSK                    (0x01C00000)
  #define MCMISCS_WRITECFGCH2_CmdAnlgEnGraceCnt_MIN                    (0)
  #define MCMISCS_WRITECFGCH2_CmdAnlgEnGraceCnt_MAX                    (7) // 0x00000007
  #define MCMISCS_WRITECFGCH2_CmdAnlgEnGraceCnt_DEF                    (0x00000007)
  #define MCMISCS_WRITECFGCH2_CmdAnlgEnGraceCnt_HSH                    (0x03163014)

  #define MCMISCS_WRITECFGCH2_TxAnlgEnGraceCnt_OFF                     (25)
  #define MCMISCS_WRITECFGCH2_TxAnlgEnGraceCnt_WID                     ( 6)
  #define MCMISCS_WRITECFGCH2_TxAnlgEnGraceCnt_MSK                     (0x7E000000)
  #define MCMISCS_WRITECFGCH2_TxAnlgEnGraceCnt_MIN                     (0)
  #define MCMISCS_WRITECFGCH2_TxAnlgEnGraceCnt_MAX                     (63) // 0x0000003F
  #define MCMISCS_WRITECFGCH2_TxAnlgEnGraceCnt_DEF                     (0x0000003F)
  #define MCMISCS_WRITECFGCH2_TxAnlgEnGraceCnt_HSH                     (0x06193014)

  #define MCMISCS_WRITECFGCH2_TxDqFifoRdEnPerRankDelDis_OFF            (31)
  #define MCMISCS_WRITECFGCH2_TxDqFifoRdEnPerRankDelDis_WID            ( 1)
  #define MCMISCS_WRITECFGCH2_TxDqFifoRdEnPerRankDelDis_MSK            (0x80000000)
  #define MCMISCS_WRITECFGCH2_TxDqFifoRdEnPerRankDelDis_MIN            (0)
  #define MCMISCS_WRITECFGCH2_TxDqFifoRdEnPerRankDelDis_MAX            (1) // 0x00000001
  #define MCMISCS_WRITECFGCH2_TxDqFifoRdEnPerRankDelDis_DEF            (0x00000000)
  #define MCMISCS_WRITECFGCH2_TxDqFifoRdEnPerRankDelDis_HSH            (0x011F3014)

#define MCMISCS_WRITECFGCH3_REG                                        (0x00003018)

  #define MCMISCS_WRITECFGCH3_tCWL4TxDqFifoWrEn_OFF                    ( 0)
  #define MCMISCS_WRITECFGCH3_tCWL4TxDqFifoWrEn_WID                    ( 6)
  #define MCMISCS_WRITECFGCH3_tCWL4TxDqFifoWrEn_MSK                    (0x0000003F)
  #define MCMISCS_WRITECFGCH3_tCWL4TxDqFifoWrEn_MIN                    (0)
  #define MCMISCS_WRITECFGCH3_tCWL4TxDqFifoWrEn_MAX                    (63) // 0x0000003F
  #define MCMISCS_WRITECFGCH3_tCWL4TxDqFifoWrEn_DEF                    (0x00000000)
  #define MCMISCS_WRITECFGCH3_tCWL4TxDqFifoWrEn_HSH                    (0x06003018)

  #define MCMISCS_WRITECFGCH3_tCWL4TxDqFifoRdEn_OFF                    ( 6)
  #define MCMISCS_WRITECFGCH3_tCWL4TxDqFifoRdEn_WID                    ( 6)
  #define MCMISCS_WRITECFGCH3_tCWL4TxDqFifoRdEn_MSK                    (0x00000FC0)
  #define MCMISCS_WRITECFGCH3_tCWL4TxDqFifoRdEn_MIN                    (0)
  #define MCMISCS_WRITECFGCH3_tCWL4TxDqFifoRdEn_MAX                    (63) // 0x0000003F
  #define MCMISCS_WRITECFGCH3_tCWL4TxDqFifoRdEn_DEF                    (0x00000000)
  #define MCMISCS_WRITECFGCH3_tCWL4TxDqFifoRdEn_HSH                    (0x06063018)

  #define MCMISCS_WRITECFGCH3_Spare_OFF                                (12)
  #define MCMISCS_WRITECFGCH3_Spare_WID                                ( 7)
  #define MCMISCS_WRITECFGCH3_Spare_MSK                                (0x0007F000)
  #define MCMISCS_WRITECFGCH3_Spare_MIN                                (0)
  #define MCMISCS_WRITECFGCH3_Spare_MAX                                (127) // 0x0000007F
  #define MCMISCS_WRITECFGCH3_Spare_DEF                                (0x00000000)
  #define MCMISCS_WRITECFGCH3_Spare_HSH                                (0x070C3018)

  #define MCMISCS_WRITECFGCH3_RptChDqTxClkOn_OFF                       (19)
  #define MCMISCS_WRITECFGCH3_RptChDqTxClkOn_WID                       ( 1)
  #define MCMISCS_WRITECFGCH3_RptChDqTxClkOn_MSK                       (0x00080000)
  #define MCMISCS_WRITECFGCH3_RptChDqTxClkOn_MIN                       (0)
  #define MCMISCS_WRITECFGCH3_RptChDqTxClkOn_MAX                       (1) // 0x00000001
  #define MCMISCS_WRITECFGCH3_RptChDqTxClkOn_DEF                       (0x00000000)
  #define MCMISCS_WRITECFGCH3_RptChDqTxClkOn_HSH                       (0x01133018)

  #define MCMISCS_WRITECFGCH3_RptChDqRxClkOn_OFF                       (20)
  #define MCMISCS_WRITECFGCH3_RptChDqRxClkOn_WID                       ( 1)
  #define MCMISCS_WRITECFGCH3_RptChDqRxClkOn_MSK                       (0x00100000)
  #define MCMISCS_WRITECFGCH3_RptChDqRxClkOn_MIN                       (0)
  #define MCMISCS_WRITECFGCH3_RptChDqRxClkOn_MAX                       (1) // 0x00000001
  #define MCMISCS_WRITECFGCH3_RptChDqRxClkOn_DEF                       (0x00000000)
  #define MCMISCS_WRITECFGCH3_RptChDqRxClkOn_HSH                       (0x01143018)

  #define MCMISCS_WRITECFGCH3_RptChRepClkOn_OFF                        (21)
  #define MCMISCS_WRITECFGCH3_RptChRepClkOn_WID                        ( 1)
  #define MCMISCS_WRITECFGCH3_RptChRepClkOn_MSK                        (0x00200000)
  #define MCMISCS_WRITECFGCH3_RptChRepClkOn_MIN                        (0)
  #define MCMISCS_WRITECFGCH3_RptChRepClkOn_MAX                        (1) // 0x00000001
  #define MCMISCS_WRITECFGCH3_RptChRepClkOn_DEF                        (0x00000000)
  #define MCMISCS_WRITECFGCH3_RptChRepClkOn_HSH                        (0x01153018)

  #define MCMISCS_WRITECFGCH3_CmdAnlgEnGraceCnt_OFF                    (22)
  #define MCMISCS_WRITECFGCH3_CmdAnlgEnGraceCnt_WID                    ( 3)
  #define MCMISCS_WRITECFGCH3_CmdAnlgEnGraceCnt_MSK                    (0x01C00000)
  #define MCMISCS_WRITECFGCH3_CmdAnlgEnGraceCnt_MIN                    (0)
  #define MCMISCS_WRITECFGCH3_CmdAnlgEnGraceCnt_MAX                    (7) // 0x00000007
  #define MCMISCS_WRITECFGCH3_CmdAnlgEnGraceCnt_DEF                    (0x00000007)
  #define MCMISCS_WRITECFGCH3_CmdAnlgEnGraceCnt_HSH                    (0x03163018)

  #define MCMISCS_WRITECFGCH3_TxAnlgEnGraceCnt_OFF                     (25)
  #define MCMISCS_WRITECFGCH3_TxAnlgEnGraceCnt_WID                     ( 6)
  #define MCMISCS_WRITECFGCH3_TxAnlgEnGraceCnt_MSK                     (0x7E000000)
  #define MCMISCS_WRITECFGCH3_TxAnlgEnGraceCnt_MIN                     (0)
  #define MCMISCS_WRITECFGCH3_TxAnlgEnGraceCnt_MAX                     (63) // 0x0000003F
  #define MCMISCS_WRITECFGCH3_TxAnlgEnGraceCnt_DEF                     (0x0000003F)
  #define MCMISCS_WRITECFGCH3_TxAnlgEnGraceCnt_HSH                     (0x06193018)

  #define MCMISCS_WRITECFGCH3_TxDqFifoRdEnPerRankDelDis_OFF            (31)
  #define MCMISCS_WRITECFGCH3_TxDqFifoRdEnPerRankDelDis_WID            ( 1)
  #define MCMISCS_WRITECFGCH3_TxDqFifoRdEnPerRankDelDis_MSK            (0x80000000)
  #define MCMISCS_WRITECFGCH3_TxDqFifoRdEnPerRankDelDis_MIN            (0)
  #define MCMISCS_WRITECFGCH3_TxDqFifoRdEnPerRankDelDis_MAX            (1) // 0x00000001
  #define MCMISCS_WRITECFGCH3_TxDqFifoRdEnPerRankDelDis_DEF            (0x00000000)
  #define MCMISCS_WRITECFGCH3_TxDqFifoRdEnPerRankDelDis_HSH            (0x011F3018)

#define MCMISCS_READCFGCH0_REG                                         (0x0000301C)

  #define MCMISCS_READCFGCH0_Spare_OFF                                 ( 0)
  #define MCMISCS_READCFGCH0_Spare_WID                                 (15)
  #define MCMISCS_READCFGCH0_Spare_MSK                                 (0x00007FFF)
  #define MCMISCS_READCFGCH0_Spare_MIN                                 (0)
  #define MCMISCS_READCFGCH0_Spare_MAX                                 (32767) // 0x00007FFF
  #define MCMISCS_READCFGCH0_Spare_DEF                                 (0x00000000)
  #define MCMISCS_READCFGCH0_Spare_HSH                                 (0x0F00301C)

  #define MCMISCS_READCFGCH0_tCL4RcvEn_OFF                             (15)
  #define MCMISCS_READCFGCH0_tCL4RcvEn_WID                             ( 6)
  #define MCMISCS_READCFGCH0_tCL4RcvEn_MSK                             (0x001F8000)
  #define MCMISCS_READCFGCH0_tCL4RcvEn_MIN                             (0)
  #define MCMISCS_READCFGCH0_tCL4RcvEn_MAX                             (63) // 0x0000003F
  #define MCMISCS_READCFGCH0_tCL4RcvEn_DEF                             (0x00000000)
  #define MCMISCS_READCFGCH0_tCL4RcvEn_HSH                             (0x060F301C)

  #define MCMISCS_READCFGCH0_tCL4RxDqFifoRdEn_OFF                      (21)
  #define MCMISCS_READCFGCH0_tCL4RxDqFifoRdEn_WID                      ( 6)
  #define MCMISCS_READCFGCH0_tCL4RxDqFifoRdEn_MSK                      (0x07E00000)
  #define MCMISCS_READCFGCH0_tCL4RxDqFifoRdEn_MIN                      (0)
  #define MCMISCS_READCFGCH0_tCL4RxDqFifoRdEn_MAX                      (63) // 0x0000003F
  #define MCMISCS_READCFGCH0_tCL4RxDqFifoRdEn_DEF                      (0x00000000)
  #define MCMISCS_READCFGCH0_tCL4RxDqFifoRdEn_HSH                      (0x0615301C)

  #define MCMISCS_READCFGCH0_RxDqDataValidDclkDel_OFF                  (27)
  #define MCMISCS_READCFGCH0_RxDqDataValidDclkDel_WID                  ( 4)
  #define MCMISCS_READCFGCH0_RxDqDataValidDclkDel_MSK                  (0x78000000)
  #define MCMISCS_READCFGCH0_RxDqDataValidDclkDel_MIN                  (0)
  #define MCMISCS_READCFGCH0_RxDqDataValidDclkDel_MAX                  (15) // 0x0000000F
  #define MCMISCS_READCFGCH0_RxDqDataValidDclkDel_DEF                  (0x00000001)
  #define MCMISCS_READCFGCH0_RxDqDataValidDclkDel_HSH                  (0x041B301C)

  #define MCMISCS_READCFGCH0_RxDqDataValidQclkDel_OFF                  (31)
  #define MCMISCS_READCFGCH0_RxDqDataValidQclkDel_WID                  ( 1)
  #define MCMISCS_READCFGCH0_RxDqDataValidQclkDel_MSK                  (0x80000000)
  #define MCMISCS_READCFGCH0_RxDqDataValidQclkDel_MIN                  (0)
  #define MCMISCS_READCFGCH0_RxDqDataValidQclkDel_MAX                  (1) // 0x00000001
  #define MCMISCS_READCFGCH0_RxDqDataValidQclkDel_DEF                  (0x00000000)
  #define MCMISCS_READCFGCH0_RxDqDataValidQclkDel_HSH                  (0x011F301C)

#define MCMISCS_READCFGCH1_REG                                         (0x00003020)

  #define MCMISCS_READCFGCH1_Spare_OFF                                 ( 0)
  #define MCMISCS_READCFGCH1_Spare_WID                                 (15)
  #define MCMISCS_READCFGCH1_Spare_MSK                                 (0x00007FFF)
  #define MCMISCS_READCFGCH1_Spare_MIN                                 (0)
  #define MCMISCS_READCFGCH1_Spare_MAX                                 (32767) // 0x00007FFF
  #define MCMISCS_READCFGCH1_Spare_DEF                                 (0x00000000)
  #define MCMISCS_READCFGCH1_Spare_HSH                                 (0x0F003020)

  #define MCMISCS_READCFGCH1_tCL4RcvEn_OFF                             (15)
  #define MCMISCS_READCFGCH1_tCL4RcvEn_WID                             ( 6)
  #define MCMISCS_READCFGCH1_tCL4RcvEn_MSK                             (0x001F8000)
  #define MCMISCS_READCFGCH1_tCL4RcvEn_MIN                             (0)
  #define MCMISCS_READCFGCH1_tCL4RcvEn_MAX                             (63) // 0x0000003F
  #define MCMISCS_READCFGCH1_tCL4RcvEn_DEF                             (0x00000000)
  #define MCMISCS_READCFGCH1_tCL4RcvEn_HSH                             (0x060F3020)

  #define MCMISCS_READCFGCH1_tCL4RxDqFifoRdEn_OFF                      (21)
  #define MCMISCS_READCFGCH1_tCL4RxDqFifoRdEn_WID                      ( 6)
  #define MCMISCS_READCFGCH1_tCL4RxDqFifoRdEn_MSK                      (0x07E00000)
  #define MCMISCS_READCFGCH1_tCL4RxDqFifoRdEn_MIN                      (0)
  #define MCMISCS_READCFGCH1_tCL4RxDqFifoRdEn_MAX                      (63) // 0x0000003F
  #define MCMISCS_READCFGCH1_tCL4RxDqFifoRdEn_DEF                      (0x00000000)
  #define MCMISCS_READCFGCH1_tCL4RxDqFifoRdEn_HSH                      (0x06153020)

  #define MCMISCS_READCFGCH1_RxDqDataValidDclkDel_OFF                  (27)
  #define MCMISCS_READCFGCH1_RxDqDataValidDclkDel_WID                  ( 4)
  #define MCMISCS_READCFGCH1_RxDqDataValidDclkDel_MSK                  (0x78000000)
  #define MCMISCS_READCFGCH1_RxDqDataValidDclkDel_MIN                  (0)
  #define MCMISCS_READCFGCH1_RxDqDataValidDclkDel_MAX                  (15) // 0x0000000F
  #define MCMISCS_READCFGCH1_RxDqDataValidDclkDel_DEF                  (0x00000001)
  #define MCMISCS_READCFGCH1_RxDqDataValidDclkDel_HSH                  (0x041B3020)

  #define MCMISCS_READCFGCH1_RxDqDataValidQclkDel_OFF                  (31)
  #define MCMISCS_READCFGCH1_RxDqDataValidQclkDel_WID                  ( 1)
  #define MCMISCS_READCFGCH1_RxDqDataValidQclkDel_MSK                  (0x80000000)
  #define MCMISCS_READCFGCH1_RxDqDataValidQclkDel_MIN                  (0)
  #define MCMISCS_READCFGCH1_RxDqDataValidQclkDel_MAX                  (1) // 0x00000001
  #define MCMISCS_READCFGCH1_RxDqDataValidQclkDel_DEF                  (0x00000000)
  #define MCMISCS_READCFGCH1_RxDqDataValidQclkDel_HSH                  (0x011F3020)

#define MCMISCS_READCFGCH2_REG                                         (0x00003024)

  #define MCMISCS_READCFGCH2_Spare_OFF                                 ( 0)
  #define MCMISCS_READCFGCH2_Spare_WID                                 (15)
  #define MCMISCS_READCFGCH2_Spare_MSK                                 (0x00007FFF)
  #define MCMISCS_READCFGCH2_Spare_MIN                                 (0)
  #define MCMISCS_READCFGCH2_Spare_MAX                                 (32767) // 0x00007FFF
  #define MCMISCS_READCFGCH2_Spare_DEF                                 (0x00000000)
  #define MCMISCS_READCFGCH2_Spare_HSH                                 (0x0F003024)

  #define MCMISCS_READCFGCH2_tCL4RcvEn_OFF                             (15)
  #define MCMISCS_READCFGCH2_tCL4RcvEn_WID                             ( 6)
  #define MCMISCS_READCFGCH2_tCL4RcvEn_MSK                             (0x001F8000)
  #define MCMISCS_READCFGCH2_tCL4RcvEn_MIN                             (0)
  #define MCMISCS_READCFGCH2_tCL4RcvEn_MAX                             (63) // 0x0000003F
  #define MCMISCS_READCFGCH2_tCL4RcvEn_DEF                             (0x00000000)
  #define MCMISCS_READCFGCH2_tCL4RcvEn_HSH                             (0x060F3024)

  #define MCMISCS_READCFGCH2_tCL4RxDqFifoRdEn_OFF                      (21)
  #define MCMISCS_READCFGCH2_tCL4RxDqFifoRdEn_WID                      ( 6)
  #define MCMISCS_READCFGCH2_tCL4RxDqFifoRdEn_MSK                      (0x07E00000)
  #define MCMISCS_READCFGCH2_tCL4RxDqFifoRdEn_MIN                      (0)
  #define MCMISCS_READCFGCH2_tCL4RxDqFifoRdEn_MAX                      (63) // 0x0000003F
  #define MCMISCS_READCFGCH2_tCL4RxDqFifoRdEn_DEF                      (0x00000000)
  #define MCMISCS_READCFGCH2_tCL4RxDqFifoRdEn_HSH                      (0x06153024)

  #define MCMISCS_READCFGCH2_RxDqDataValidDclkDel_OFF                  (27)
  #define MCMISCS_READCFGCH2_RxDqDataValidDclkDel_WID                  ( 4)
  #define MCMISCS_READCFGCH2_RxDqDataValidDclkDel_MSK                  (0x78000000)
  #define MCMISCS_READCFGCH2_RxDqDataValidDclkDel_MIN                  (0)
  #define MCMISCS_READCFGCH2_RxDqDataValidDclkDel_MAX                  (15) // 0x0000000F
  #define MCMISCS_READCFGCH2_RxDqDataValidDclkDel_DEF                  (0x00000001)
  #define MCMISCS_READCFGCH2_RxDqDataValidDclkDel_HSH                  (0x041B3024)

  #define MCMISCS_READCFGCH2_RxDqDataValidQclkDel_OFF                  (31)
  #define MCMISCS_READCFGCH2_RxDqDataValidQclkDel_WID                  ( 1)
  #define MCMISCS_READCFGCH2_RxDqDataValidQclkDel_MSK                  (0x80000000)
  #define MCMISCS_READCFGCH2_RxDqDataValidQclkDel_MIN                  (0)
  #define MCMISCS_READCFGCH2_RxDqDataValidQclkDel_MAX                  (1) // 0x00000001
  #define MCMISCS_READCFGCH2_RxDqDataValidQclkDel_DEF                  (0x00000000)
  #define MCMISCS_READCFGCH2_RxDqDataValidQclkDel_HSH                  (0x011F3024)

#define MCMISCS_READCFGCH3_REG                                         (0x00003028)

  #define MCMISCS_READCFGCH3_Spare_OFF                                 ( 0)
  #define MCMISCS_READCFGCH3_Spare_WID                                 (15)
  #define MCMISCS_READCFGCH3_Spare_MSK                                 (0x00007FFF)
  #define MCMISCS_READCFGCH3_Spare_MIN                                 (0)
  #define MCMISCS_READCFGCH3_Spare_MAX                                 (32767) // 0x00007FFF
  #define MCMISCS_READCFGCH3_Spare_DEF                                 (0x00000000)
  #define MCMISCS_READCFGCH3_Spare_HSH                                 (0x0F003028)

  #define MCMISCS_READCFGCH3_tCL4RcvEn_OFF                             (15)
  #define MCMISCS_READCFGCH3_tCL4RcvEn_WID                             ( 6)
  #define MCMISCS_READCFGCH3_tCL4RcvEn_MSK                             (0x001F8000)
  #define MCMISCS_READCFGCH3_tCL4RcvEn_MIN                             (0)
  #define MCMISCS_READCFGCH3_tCL4RcvEn_MAX                             (63) // 0x0000003F
  #define MCMISCS_READCFGCH3_tCL4RcvEn_DEF                             (0x00000000)
  #define MCMISCS_READCFGCH3_tCL4RcvEn_HSH                             (0x060F3028)

  #define MCMISCS_READCFGCH3_tCL4RxDqFifoRdEn_OFF                      (21)
  #define MCMISCS_READCFGCH3_tCL4RxDqFifoRdEn_WID                      ( 6)
  #define MCMISCS_READCFGCH3_tCL4RxDqFifoRdEn_MSK                      (0x07E00000)
  #define MCMISCS_READCFGCH3_tCL4RxDqFifoRdEn_MIN                      (0)
  #define MCMISCS_READCFGCH3_tCL4RxDqFifoRdEn_MAX                      (63) // 0x0000003F
  #define MCMISCS_READCFGCH3_tCL4RxDqFifoRdEn_DEF                      (0x00000000)
  #define MCMISCS_READCFGCH3_tCL4RxDqFifoRdEn_HSH                      (0x06153028)

  #define MCMISCS_READCFGCH3_RxDqDataValidDclkDel_OFF                  (27)
  #define MCMISCS_READCFGCH3_RxDqDataValidDclkDel_WID                  ( 4)
  #define MCMISCS_READCFGCH3_RxDqDataValidDclkDel_MSK                  (0x78000000)
  #define MCMISCS_READCFGCH3_RxDqDataValidDclkDel_MIN                  (0)
  #define MCMISCS_READCFGCH3_RxDqDataValidDclkDel_MAX                  (15) // 0x0000000F
  #define MCMISCS_READCFGCH3_RxDqDataValidDclkDel_DEF                  (0x00000001)
  #define MCMISCS_READCFGCH3_RxDqDataValidDclkDel_HSH                  (0x041B3028)

  #define MCMISCS_READCFGCH3_RxDqDataValidQclkDel_OFF                  (31)
  #define MCMISCS_READCFGCH3_RxDqDataValidQclkDel_WID                  ( 1)
  #define MCMISCS_READCFGCH3_RxDqDataValidQclkDel_MSK                  (0x80000000)
  #define MCMISCS_READCFGCH3_RxDqDataValidQclkDel_MIN                  (0)
  #define MCMISCS_READCFGCH3_RxDqDataValidQclkDel_MAX                  (1) // 0x00000001
  #define MCMISCS_READCFGCH3_RxDqDataValidQclkDel_DEF                  (0x00000000)
  #define MCMISCS_READCFGCH3_RxDqDataValidQclkDel_HSH                  (0x011F3028)

#define DDRSCRAM_CR_DDRSCRAMBLECH2_REG                                 (0x0000302C)

  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ScramEn_OFF                       ( 0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ScramEn_WID                       ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ScramEn_MSK                       (0x00000001)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ScramEn_MIN                       (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ScramEn_MAX                       (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ScramEn_DEF                       (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ScramEn_HSH                       (0x0100302C)

  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ScramKey_OFF                      ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ScramKey_WID                      (16)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ScramKey_MSK                      (0x0001FFFE)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ScramKey_MIN                      (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ScramKey_MAX                      (65535) // 0x0000FFFF
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ScramKey_DEF                      (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ScramKey_HSH                      (0x1001302C)

  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ClockGateAB_OFF                   (17)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ClockGateAB_WID                   ( 2)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ClockGateAB_MSK                   (0x00060000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ClockGateAB_MIN                   (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ClockGateAB_MAX                   (3) // 0x00000003
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ClockGateAB_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ClockGateAB_HSH                   (0x0211302C)

  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ClockGateC_OFF                    (19)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ClockGateC_WID                    ( 2)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ClockGateC_MSK                    (0x00180000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ClockGateC_MIN                    (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ClockGateC_MAX                    (3) // 0x00000003
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ClockGateC_DEF                    (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ClockGateC_HSH                    (0x0213302C)

  #define DDRSCRAM_CR_DDRSCRAMBLECH2_EnableDbiAB_OFF                   (21)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_EnableDbiAB_WID                   ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_EnableDbiAB_MSK                   (0x00200000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_EnableDbiAB_MIN                   (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_EnableDbiAB_MAX                   (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_EnableDbiAB_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_EnableDbiAB_HSH                   (0x0115302C)

  #define DDRSCRAM_CR_DDRSCRAMBLECH2_en_dilution_mode_OFF              (22)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_en_dilution_mode_WID              ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_en_dilution_mode_MSK              (0x00400000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_en_dilution_mode_MIN              (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_en_dilution_mode_MAX              (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_en_dilution_mode_DEF              (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_en_dilution_mode_HSH              (0x0116302C)

  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ca_mirrored_OFF                   (23)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ca_mirrored_WID                   ( 4)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ca_mirrored_MSK                   (0x07800000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ca_mirrored_MIN                   (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ca_mirrored_MAX                   (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ca_mirrored_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_ca_mirrored_HSH                   (0x0417302C)

  #define DDRSCRAM_CR_DDRSCRAMBLECH2_Spare_OFF                         (27)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_Spare_WID                         ( 5)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_Spare_MSK                         (0xF8000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_Spare_MIN                         (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_Spare_MAX                         (31) // 0x0000001F
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_Spare_DEF                         (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH2_Spare_HSH                         (0x051B302C)

#define DDRSCRAM_CR_DDRSCRAMBLECH3_REG                                 (0x00003030)

  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ScramEn_OFF                       ( 0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ScramEn_WID                       ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ScramEn_MSK                       (0x00000001)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ScramEn_MIN                       (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ScramEn_MAX                       (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ScramEn_DEF                       (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ScramEn_HSH                       (0x01003030)

  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ScramKey_OFF                      ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ScramKey_WID                      (16)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ScramKey_MSK                      (0x0001FFFE)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ScramKey_MIN                      (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ScramKey_MAX                      (65535) // 0x0000FFFF
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ScramKey_DEF                      (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ScramKey_HSH                      (0x10013030)

  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ClockGateAB_OFF                   (17)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ClockGateAB_WID                   ( 2)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ClockGateAB_MSK                   (0x00060000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ClockGateAB_MIN                   (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ClockGateAB_MAX                   (3) // 0x00000003
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ClockGateAB_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ClockGateAB_HSH                   (0x02113030)

  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ClockGateC_OFF                    (19)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ClockGateC_WID                    ( 2)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ClockGateC_MSK                    (0x00180000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ClockGateC_MIN                    (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ClockGateC_MAX                    (3) // 0x00000003
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ClockGateC_DEF                    (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ClockGateC_HSH                    (0x02133030)

  #define DDRSCRAM_CR_DDRSCRAMBLECH3_EnableDbiAB_OFF                   (21)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_EnableDbiAB_WID                   ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_EnableDbiAB_MSK                   (0x00200000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_EnableDbiAB_MIN                   (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_EnableDbiAB_MAX                   (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_EnableDbiAB_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_EnableDbiAB_HSH                   (0x01153030)

  #define DDRSCRAM_CR_DDRSCRAMBLECH3_en_dilution_mode_OFF              (22)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_en_dilution_mode_WID              ( 1)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_en_dilution_mode_MSK              (0x00400000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_en_dilution_mode_MIN              (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_en_dilution_mode_MAX              (1) // 0x00000001
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_en_dilution_mode_DEF              (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_en_dilution_mode_HSH              (0x01163030)

  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ca_mirrored_OFF                   (23)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ca_mirrored_WID                   ( 4)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ca_mirrored_MSK                   (0x07800000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ca_mirrored_MIN                   (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ca_mirrored_MAX                   (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ca_mirrored_DEF                   (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_ca_mirrored_HSH                   (0x04173030)

  #define DDRSCRAM_CR_DDRSCRAMBLECH3_Spare_OFF                         (27)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_Spare_WID                         ( 5)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_Spare_MSK                         (0xF8000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_Spare_MIN                         (0)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_Spare_MAX                         (31) // 0x0000001F
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_Spare_DEF                         (0x00000000)
  #define DDRSCRAM_CR_DDRSCRAMBLECH3_Spare_HSH                         (0x051B3030)

#define DDRSCRAM_CR_DDRMISCCONTROL1_REG                                (0x00003034)

  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs0_OFF             ( 0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs0_WID             ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs0_MSK             (0x0000000F)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs0_MIN             (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs0_MAX             (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs0_DEF             (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs0_HSH             (0x04003034)

  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs1_OFF             ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs1_WID             ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs1_MSK             (0x000000F0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs1_MIN             (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs1_MAX             (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs1_DEF             (0x00000003)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs1_HSH             (0x04043034)

  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs2_OFF             ( 8)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs2_WID             ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs2_MSK             (0x00000F00)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs2_MIN             (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs2_MAX             (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs2_DEF             (0x00000001)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs2_HSH             (0x04083034)

  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs3_OFF             (12)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs3_WID             ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs3_MSK             (0x0000F000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs3_MIN             (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs3_MAX             (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs3_DEF             (0x00000002)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_cs3_HSH             (0x040C3034)

  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt0_OFF            (16)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt0_WID            ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt0_MSK            (0x000F0000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt0_MIN            (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt0_MAX            (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt0_DEF            (0x00000004)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt0_HSH            (0x04103034)

  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt1_OFF            (20)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt1_WID            ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt1_MSK            (0x00F00000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt1_MIN            (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt1_MAX            (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt1_DEF            (0x00000006)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_CsOdtMapping_odt1_HSH            (0x04143034)

  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_OFF                 (24)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_WID                 ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_MSK                 (0x01000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_MIN                 (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_MAX                 (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_DEF                 (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_HSH                 (0x01183034)

  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_quiet_time_OFF      (25)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_quiet_time_WID      ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_quiet_time_MSK      (0x02000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_quiet_time_MIN      (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_quiet_time_MAX      (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_quiet_time_DEF      (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_quiet_time_HSH      (0x01193034)

  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_duration_OFF        (26)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_duration_WID        ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_duration_MSK        (0x3C000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_duration_MIN        (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_duration_MAX        (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_duration_DEF        (0x0000000A)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_duration_HSH        (0x041A3034)

  #define DDRSCRAM_CR_DDRMISCCONTROL1_ForceCompUpdate_OFF              (30)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_ForceCompUpdate_WID              ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_ForceCompUpdate_MSK              (0x40000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_ForceCompUpdate_MIN              (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_ForceCompUpdate_MAX              (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL1_ForceCompUpdate_DEF              (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_ForceCompUpdate_HSH              (0x011E3034)

  #define DDRSCRAM_CR_DDRMISCCONTROL1_ForceDeltaDQSUpdate_OFF          (31)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_ForceDeltaDQSUpdate_WID          ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_ForceDeltaDQSUpdate_MSK          (0x80000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_ForceDeltaDQSUpdate_MIN          (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_ForceDeltaDQSUpdate_MAX          (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL1_ForceDeltaDQSUpdate_DEF          (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL1_ForceDeltaDQSUpdate_HSH          (0x011F3034)

#define DDRSCRAM_CR_DDRMISCCONTROL2_REG                                (0x00003038)

  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs0_OFF             ( 0)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs0_WID             ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs0_MSK             (0x0000000F)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs0_MIN             (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs0_MAX             (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs0_DEF             (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs0_HSH             (0x04003038)

  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs1_OFF             ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs1_WID             ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs1_MSK             (0x000000F0)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs1_MIN             (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs1_MAX             (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs1_DEF             (0x00000003)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs1_HSH             (0x04043038)

  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs2_OFF             ( 8)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs2_WID             ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs2_MSK             (0x00000F00)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs2_MIN             (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs2_MAX             (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs2_DEF             (0x00000001)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs2_HSH             (0x04083038)

  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs3_OFF             (12)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs3_WID             ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs3_MSK             (0x0000F000)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs3_MIN             (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs3_MAX             (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs3_DEF             (0x00000002)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_cs3_HSH             (0x040C3038)

  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt0_OFF            (16)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt0_WID            ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt0_MSK            (0x000F0000)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt0_MIN            (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt0_MAX            (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt0_DEF            (0x00000004)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt0_HSH            (0x04103038)

  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt1_OFF            (20)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt1_WID            ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt1_MSK            (0x00F00000)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt1_MIN            (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt1_MAX            (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt1_DEF            (0x00000006)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_CsOdtMapping_odt1_HSH            (0x04143038)

  #define DDRSCRAM_CR_DDRMISCCONTROL2_lp4_cmd_mirror_OFF               (24)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_lp4_cmd_mirror_WID               ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_lp4_cmd_mirror_MSK               (0x01000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_lp4_cmd_mirror_MIN               (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_lp4_cmd_mirror_MAX               (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL2_lp4_cmd_mirror_DEF               (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_lp4_cmd_mirror_HSH               (0x01183038)

  #define DDRSCRAM_CR_DDRMISCCONTROL2_rx_analogen_grace_cnt_OFF        (25)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_rx_analogen_grace_cnt_WID        ( 7)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_rx_analogen_grace_cnt_MSK        (0xFE000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_rx_analogen_grace_cnt_MIN        (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_rx_analogen_grace_cnt_MAX        (127) // 0x0000007F
  #define DDRSCRAM_CR_DDRMISCCONTROL2_rx_analogen_grace_cnt_DEF        (0x00000064)
  #define DDRSCRAM_CR_DDRMISCCONTROL2_rx_analogen_grace_cnt_HSH        (0x07193038)

#define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_REG                         (0x0000303C)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane0_HSH        (0x0300303C)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane1_HSH        (0x0303303C)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane2_HSH        (0x0306303C)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane3_HSH        (0x0309303C)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane4_HSH        (0x030C303C)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane5_HSH        (0x030F303C)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane6_HSH        (0x0312303C)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleLane7_HSH        (0x0315303C)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_DeSwizzleByte_HSH         (0x0218303C)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_Spare_HSH                 (0x041A303C)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_HSH (0x011E303C)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_HSH (0x011F303C)

#define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_REG                         (0x00003040)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane0_HSH        (0x03003040)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane1_HSH        (0x03033040)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane2_HSH        (0x03063040)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane3_HSH        (0x03093040)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane4_HSH        (0x030C3040)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane5_HSH        (0x030F3040)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane6_HSH        (0x03123040)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleLane7_HSH        (0x03153040)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_DeSwizzleByte_HSH         (0x02183040)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_Spare_HSH                 (0x041A3040)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_HSH (0x011E3040)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_HSH (0x011F3040)

#define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_REG                         (0x00003044)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane0_HSH        (0x03003044)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane1_HSH        (0x03033044)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane2_HSH        (0x03063044)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane3_HSH        (0x03093044)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane4_HSH        (0x030C3044)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane5_HSH        (0x030F3044)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane6_HSH        (0x03123044)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleLane7_HSH        (0x03153044)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_DeSwizzleByte_HSH         (0x02183044)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_Spare_HSH                 (0x041A3044)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_HSH (0x011E3044)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_HSH (0x011F3044)

#define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_REG                         (0x00003048)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane0_HSH        (0x03003048)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane1_HSH        (0x03033048)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane2_HSH        (0x03063048)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane3_HSH        (0x03093048)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane4_HSH        (0x030C3048)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane5_HSH        (0x030F3048)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane6_HSH        (0x03123048)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleLane7_HSH        (0x03153048)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_DeSwizzleByte_HSH         (0x02183048)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_Spare_HSH                 (0x041A3048)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_HSH (0x011E3048)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_HSH (0x011F3048)

#define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_REG                         (0x0000304C)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane0_HSH        (0x0300304C)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane1_HSH        (0x0303304C)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane2_HSH        (0x0306304C)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane3_HSH        (0x0309304C)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane4_HSH        (0x030C304C)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane5_HSH        (0x030F304C)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane6_HSH        (0x0312304C)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleLane7_HSH        (0x0315304C)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_DeSwizzleByte_HSH         (0x0218304C)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_Spare_HSH                 (0x041A304C)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_HSH (0x011E304C)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_HSH (0x011F304C)

#define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_REG                         (0x00003050)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane0_HSH        (0x03003050)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane1_HSH        (0x03033050)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane2_HSH        (0x03063050)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane3_HSH        (0x03093050)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane4_HSH        (0x030C3050)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane5_HSH        (0x030F3050)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane6_HSH        (0x03123050)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleLane7_HSH        (0x03153050)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_DeSwizzleByte_HSH         (0x02183050)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_Spare_HSH                 (0x041A3050)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_HSH (0x011E3050)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_HSH (0x011F3050)

#define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_REG                         (0x00003054)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane0_HSH        (0x03003054)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane1_HSH        (0x03033054)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane2_HSH        (0x03063054)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane3_HSH        (0x03093054)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane4_HSH        (0x030C3054)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane5_HSH        (0x030F3054)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane6_HSH        (0x03123054)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleLane7_HSH        (0x03153054)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_DeSwizzleByte_HSH         (0x02183054)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_Spare_HSH                 (0x041A3054)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_HSH (0x011E3054)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_HSH (0x011F3054)

#define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_REG                         (0x00003058)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane0_HSH        (0x03003058)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane1_HSH        (0x03033058)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane2_HSH        (0x03063058)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane3_HSH        (0x03093058)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane4_HSH        (0x030C3058)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane5_HSH        (0x030F3058)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane6_HSH        (0x03123058)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleLane7_HSH        (0x03153058)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_DeSwizzleByte_HSH         (0x02183058)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_Spare_HSH                 (0x041A3058)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_HSH (0x011E3058)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_HSH (0x011F3058)

#define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_REG                         (0x0000305C)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane0_HSH        (0x0300305C)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane1_HSH        (0x0303305C)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane2_HSH        (0x0306305C)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane3_HSH        (0x0309305C)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane4_HSH        (0x030C305C)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane5_HSH        (0x030F305C)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane6_HSH        (0x0312305C)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleLane7_HSH        (0x0315305C)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_DeSwizzleByte_HSH         (0x0218305C)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_Spare_HSH                 (0x041A305C)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_HSH (0x011E305C)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_HSH (0x011F305C)

#define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_REG                         (0x00003060)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane0_HSH        (0x03003060)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane1_HSH        (0x03033060)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane2_HSH        (0x03063060)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane3_HSH        (0x03093060)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane4_HSH        (0x030C3060)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane5_HSH        (0x030F3060)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane6_HSH        (0x03123060)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleLane7_HSH        (0x03153060)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_DeSwizzleByte_HSH         (0x02183060)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_Spare_HSH                 (0x041A3060)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_HSH (0x011E3060)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_HSH (0x011F3060)

#define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_REG                         (0x00003064)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane0_HSH        (0x03003064)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane1_HSH        (0x03033064)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane2_HSH        (0x03063064)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane3_HSH        (0x03093064)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane4_HSH        (0x030C3064)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane5_HSH        (0x030F3064)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane6_HSH        (0x03123064)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleLane7_HSH        (0x03153064)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_DeSwizzleByte_HSH         (0x02183064)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_Spare_HSH                 (0x041A3064)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_HSH (0x011E3064)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_HSH (0x011F3064)

#define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_REG                         (0x00003068)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane0_HSH        (0x03003068)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane1_HSH        (0x03033068)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane2_HSH        (0x03063068)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane3_HSH        (0x03093068)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane4_HSH        (0x030C3068)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane5_HSH        (0x030F3068)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane6_HSH        (0x03123068)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleLane7_HSH        (0x03153068)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_DeSwizzleByte_HSH         (0x02183068)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_Spare_HSH                 (0x041A3068)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_HSH (0x011E3068)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_HSH (0x011F3068)

#define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_REG                         (0x0000306C)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane0_HSH        (0x0300306C)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane1_HSH        (0x0303306C)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane2_HSH        (0x0306306C)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane3_HSH        (0x0309306C)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane4_HSH        (0x030C306C)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane5_HSH        (0x030F306C)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane6_HSH        (0x0312306C)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleLane7_HSH        (0x0315306C)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_DeSwizzleByte_HSH         (0x0218306C)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_Spare_HSH                 (0x041A306C)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_LP4_calc_in_progres_Override_Val_HSH (0x011E306C)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV0_LP4_calc_in_progres_Override_En_HSH (0x011F306C)

#define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_REG                         (0x00003070)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane0_HSH        (0x03003070)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane1_HSH        (0x03033070)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane2_HSH        (0x03063070)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane3_HSH        (0x03093070)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane4_HSH        (0x030C3070)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane5_HSH        (0x030F3070)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane6_HSH        (0x03123070)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleLane7_HSH        (0x03153070)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_DeSwizzleByte_HSH         (0x02183070)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_Spare_HSH                 (0x041A3070)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_LP4_calc_in_progres_Override_Val_HSH (0x011E3070)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV1_LP4_calc_in_progres_Override_En_HSH (0x011F3070)

#define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_REG                         (0x00003074)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane0_HSH        (0x03003074)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane1_HSH        (0x03033074)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane2_HSH        (0x03063074)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane3_HSH        (0x03093074)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane4_HSH        (0x030C3074)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane5_HSH        (0x030F3074)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane6_HSH        (0x03123074)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleLane7_HSH        (0x03153074)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_DeSwizzleByte_HSH         (0x02183074)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_Spare_HSH                 (0x041A3074)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_LP4_calc_in_progres_Override_Val_HSH (0x011E3074)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV0_LP4_calc_in_progres_Override_En_HSH (0x011F3074)

#define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_REG                         (0x00003078)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane0_HSH        (0x03003078)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane1_HSH        (0x03033078)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane2_HSH        (0x03063078)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane3_HSH        (0x03093078)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane4_HSH        (0x030C3078)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane5_HSH        (0x030F3078)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane6_HSH        (0x03123078)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleLane7_HSH        (0x03153078)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_DeSwizzleByte_HSH         (0x02183078)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_Spare_HSH                 (0x041A3078)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_LP4_calc_in_progres_Override_Val_HSH (0x011E3078)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV1_LP4_calc_in_progres_Override_En_HSH (0x011F3078)

#define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_REG                         (0x0000307C)

  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_ROCountTrainChannel0Rank0Dev0_OFF ( 0)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_ROCountTrainChannel0Rank0Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_ROCountTrainChannel0Rank0Dev0_MSK (0x000001FF)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_ROCountTrainChannel0Rank0Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_ROCountTrainChannel0Rank0Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_ROCountTrainChannel0Rank0Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_ROCountTrainChannel0Rank0Dev0_HSH (0x0900307C)

  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_ROCountTrainChannel0Rank1Dev0_OFF ( 9)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_ROCountTrainChannel0Rank1Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_ROCountTrainChannel0Rank1Dev0_MSK (0x0003FE00)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_ROCountTrainChannel0Rank1Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_ROCountTrainChannel0Rank1Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_ROCountTrainChannel0Rank1Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_ROCountTrainChannel0Rank1Dev0_HSH (0x0909307C)

  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_ROCountTrainChannel0Rank2Dev0_OFF (18)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_ROCountTrainChannel0Rank2Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_ROCountTrainChannel0Rank2Dev0_MSK (0x07FC0000)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_ROCountTrainChannel0Rank2Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_ROCountTrainChannel0Rank2Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_ROCountTrainChannel0Rank2Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_ROCountTrainChannel0Rank2Dev0_HSH (0x0912307C)

  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_Spare_OFF                 (27)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_Spare_WID                 ( 5)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_Spare_MSK                 (0xF8000000)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_Spare_MIN                 (0)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_Spare_MAX                 (31) // 0x0000001F
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_Spare_DEF                 (0x00000000)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV0_Spare_HSH                 (0x051B307C)

#define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_REG                         (0x00003080)

  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_ROCountTrainChannel0Rank0Dev1_OFF ( 0)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_ROCountTrainChannel0Rank0Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_ROCountTrainChannel0Rank0Dev1_MSK (0x000001FF)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_ROCountTrainChannel0Rank0Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_ROCountTrainChannel0Rank0Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_ROCountTrainChannel0Rank0Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_ROCountTrainChannel0Rank0Dev1_HSH (0x09003080)

  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_ROCountTrainChannel0Rank1Dev1_OFF ( 9)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_ROCountTrainChannel0Rank1Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_ROCountTrainChannel0Rank1Dev1_MSK (0x0003FE00)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_ROCountTrainChannel0Rank1Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_ROCountTrainChannel0Rank1Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_ROCountTrainChannel0Rank1Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_ROCountTrainChannel0Rank1Dev1_HSH (0x09093080)

  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_ROCountTrainChannel0Rank2Dev1_OFF (18)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_ROCountTrainChannel0Rank2Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_ROCountTrainChannel0Rank2Dev1_MSK (0x07FC0000)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_ROCountTrainChannel0Rank2Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_ROCountTrainChannel0Rank2Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_ROCountTrainChannel0Rank2Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_ROCountTrainChannel0Rank2Dev1_HSH (0x09123080)

  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_Spare_OFF                 (27)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_Spare_WID                 ( 5)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_Spare_MSK                 (0xF8000000)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_Spare_MIN                 (0)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_Spare_MAX                 (31) // 0x0000001F
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_Spare_DEF                 (0x00000000)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV1_Spare_HSH                 (0x051B3080)

#define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_REG                         (0x00003084)

  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_ROCountTrainChannel1Rank0Dev0_OFF ( 0)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_ROCountTrainChannel1Rank0Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_ROCountTrainChannel1Rank0Dev0_MSK (0x000001FF)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_ROCountTrainChannel1Rank0Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_ROCountTrainChannel1Rank0Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_ROCountTrainChannel1Rank0Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_ROCountTrainChannel1Rank0Dev0_HSH (0x09003084)

  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_ROCountTrainChannel1Rank1Dev0_OFF ( 9)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_ROCountTrainChannel1Rank1Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_ROCountTrainChannel1Rank1Dev0_MSK (0x0003FE00)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_ROCountTrainChannel1Rank1Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_ROCountTrainChannel1Rank1Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_ROCountTrainChannel1Rank1Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_ROCountTrainChannel1Rank1Dev0_HSH (0x09093084)

  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_ROCountTrainChannel1Rank2Dev0_OFF (18)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_ROCountTrainChannel1Rank2Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_ROCountTrainChannel1Rank2Dev0_MSK (0x07FC0000)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_ROCountTrainChannel1Rank2Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_ROCountTrainChannel1Rank2Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_ROCountTrainChannel1Rank2Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_ROCountTrainChannel1Rank2Dev0_HSH (0x09123084)

  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_Spare_OFF                 (27)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_Spare_WID                 ( 5)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_Spare_MSK                 (0xF8000000)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_Spare_MIN                 (0)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_Spare_MAX                 (31) // 0x0000001F
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_Spare_DEF                 (0x00000000)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV0_Spare_HSH                 (0x051B3084)

#define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_REG                         (0x00003088)

  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_ROCountTrainChannel1Rank0Dev1_OFF ( 0)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_ROCountTrainChannel1Rank0Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_ROCountTrainChannel1Rank0Dev1_MSK (0x000001FF)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_ROCountTrainChannel1Rank0Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_ROCountTrainChannel1Rank0Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_ROCountTrainChannel1Rank0Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_ROCountTrainChannel1Rank0Dev1_HSH (0x09003088)

  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_ROCountTrainChannel1Rank1Dev1_OFF ( 9)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_ROCountTrainChannel1Rank1Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_ROCountTrainChannel1Rank1Dev1_MSK (0x0003FE00)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_ROCountTrainChannel1Rank1Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_ROCountTrainChannel1Rank1Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_ROCountTrainChannel1Rank1Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_ROCountTrainChannel1Rank1Dev1_HSH (0x09093088)

  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_ROCountTrainChannel1Rank2Dev1_OFF (18)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_ROCountTrainChannel1Rank2Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_ROCountTrainChannel1Rank2Dev1_MSK (0x07FC0000)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_ROCountTrainChannel1Rank2Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_ROCountTrainChannel1Rank2Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_ROCountTrainChannel1Rank2Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_ROCountTrainChannel1Rank2Dev1_HSH (0x09123088)

  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_Spare_OFF                 (27)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_Spare_WID                 ( 5)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_Spare_MSK                 (0xF8000000)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_Spare_MIN                 (0)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_Spare_MAX                 (31) // 0x0000001F
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_Spare_DEF                 (0x00000000)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV1_Spare_HSH                 (0x051B3088)

#define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_REG                         (0x0000308C)

  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_ROCountTrainChannel2Rank0Dev0_OFF ( 0)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_ROCountTrainChannel2Rank0Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_ROCountTrainChannel2Rank0Dev0_MSK (0x000001FF)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_ROCountTrainChannel2Rank0Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_ROCountTrainChannel2Rank0Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_ROCountTrainChannel2Rank0Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_ROCountTrainChannel2Rank0Dev0_HSH (0x0900308C)

  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_ROCountTrainChannel2Rank1Dev0_OFF ( 9)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_ROCountTrainChannel2Rank1Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_ROCountTrainChannel2Rank1Dev0_MSK (0x0003FE00)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_ROCountTrainChannel2Rank1Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_ROCountTrainChannel2Rank1Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_ROCountTrainChannel2Rank1Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_ROCountTrainChannel2Rank1Dev0_HSH (0x0909308C)

  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_ROCountTrainChannel2Rank2Dev0_OFF (18)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_ROCountTrainChannel2Rank2Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_ROCountTrainChannel2Rank2Dev0_MSK (0x07FC0000)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_ROCountTrainChannel2Rank2Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_ROCountTrainChannel2Rank2Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_ROCountTrainChannel2Rank2Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_ROCountTrainChannel2Rank2Dev0_HSH (0x0912308C)

  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_Spare_OFF                 (27)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_Spare_WID                 ( 5)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_Spare_MSK                 (0xF8000000)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_Spare_MIN                 (0)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_Spare_MAX                 (31) // 0x0000001F
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_Spare_DEF                 (0x00000000)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV0_Spare_HSH                 (0x051B308C)

#define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_REG                         (0x00003090)

  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_ROCountTrainChannel2Rank0Dev1_OFF ( 0)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_ROCountTrainChannel2Rank0Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_ROCountTrainChannel2Rank0Dev1_MSK (0x000001FF)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_ROCountTrainChannel2Rank0Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_ROCountTrainChannel2Rank0Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_ROCountTrainChannel2Rank0Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_ROCountTrainChannel2Rank0Dev1_HSH (0x09003090)

  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_ROCountTrainChannel2Rank1Dev1_OFF ( 9)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_ROCountTrainChannel2Rank1Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_ROCountTrainChannel2Rank1Dev1_MSK (0x0003FE00)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_ROCountTrainChannel2Rank1Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_ROCountTrainChannel2Rank1Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_ROCountTrainChannel2Rank1Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_ROCountTrainChannel2Rank1Dev1_HSH (0x09093090)

  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_ROCountTrainChannel2Rank2Dev1_OFF (18)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_ROCountTrainChannel2Rank2Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_ROCountTrainChannel2Rank2Dev1_MSK (0x07FC0000)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_ROCountTrainChannel2Rank2Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_ROCountTrainChannel2Rank2Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_ROCountTrainChannel2Rank2Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_ROCountTrainChannel2Rank2Dev1_HSH (0x09123090)

  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_Spare_OFF                 (27)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_Spare_WID                 ( 5)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_Spare_MSK                 (0xF8000000)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_Spare_MIN                 (0)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_Spare_MAX                 (31) // 0x0000001F
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_Spare_DEF                 (0x00000000)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV1_Spare_HSH                 (0x051B3090)

#define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_REG                         (0x00003094)

  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_ROCountTrainChannel3Rank0Dev0_OFF ( 0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_ROCountTrainChannel3Rank0Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_ROCountTrainChannel3Rank0Dev0_MSK (0x000001FF)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_ROCountTrainChannel3Rank0Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_ROCountTrainChannel3Rank0Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_ROCountTrainChannel3Rank0Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_ROCountTrainChannel3Rank0Dev0_HSH (0x09003094)

  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_ROCountTrainChannel3Rank1Dev0_OFF ( 9)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_ROCountTrainChannel3Rank1Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_ROCountTrainChannel3Rank1Dev0_MSK (0x0003FE00)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_ROCountTrainChannel3Rank1Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_ROCountTrainChannel3Rank1Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_ROCountTrainChannel3Rank1Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_ROCountTrainChannel3Rank1Dev0_HSH (0x09093094)

  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_ROCountTrainChannel3Rank2Dev0_OFF (18)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_ROCountTrainChannel3Rank2Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_ROCountTrainChannel3Rank2Dev0_MSK (0x07FC0000)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_ROCountTrainChannel3Rank2Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_ROCountTrainChannel3Rank2Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_ROCountTrainChannel3Rank2Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_ROCountTrainChannel3Rank2Dev0_HSH (0x09123094)

  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_Spare_OFF                 (27)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_Spare_WID                 ( 5)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_Spare_MSK                 (0xF8000000)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_Spare_MIN                 (0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_Spare_MAX                 (31) // 0x0000001F
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_Spare_DEF                 (0x00000000)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV0_Spare_HSH                 (0x051B3094)

#define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_REG                         (0x00003098)

  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_ROCountTrainChannel3Rank0Dev1_OFF ( 0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_ROCountTrainChannel3Rank0Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_ROCountTrainChannel3Rank0Dev1_MSK (0x000001FF)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_ROCountTrainChannel3Rank0Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_ROCountTrainChannel3Rank0Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_ROCountTrainChannel3Rank0Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_ROCountTrainChannel3Rank0Dev1_HSH (0x09003098)

  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_ROCountTrainChannel3Rank1Dev1_OFF ( 9)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_ROCountTrainChannel3Rank1Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_ROCountTrainChannel3Rank1Dev1_MSK (0x0003FE00)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_ROCountTrainChannel3Rank1Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_ROCountTrainChannel3Rank1Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_ROCountTrainChannel3Rank1Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_ROCountTrainChannel3Rank1Dev1_HSH (0x09093098)

  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_ROCountTrainChannel3Rank2Dev1_OFF (18)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_ROCountTrainChannel3Rank2Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_ROCountTrainChannel3Rank2Dev1_MSK (0x07FC0000)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_ROCountTrainChannel3Rank2Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_ROCountTrainChannel3Rank2Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_ROCountTrainChannel3Rank2Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_ROCountTrainChannel3Rank2Dev1_HSH (0x09123098)

  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_Spare_OFF                 (27)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_Spare_WID                 ( 5)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_Spare_MSK                 (0xF8000000)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_Spare_MIN                 (0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_Spare_MAX                 (31) // 0x0000001F
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_Spare_DEF                 (0x00000000)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV1_Spare_HSH                 (0x051B3098)

#define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_REG                         (0x0000309C)

  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_ROCountTrainChannel0Rank3Dev0_OFF ( 0)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_ROCountTrainChannel0Rank3Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_ROCountTrainChannel0Rank3Dev0_MSK (0x000001FF)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_ROCountTrainChannel0Rank3Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_ROCountTrainChannel0Rank3Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_ROCountTrainChannel0Rank3Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_ROCountTrainChannel0Rank3Dev0_HSH (0x0900309C)

  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_ROCountTrainChannel1Rank3Dev0_OFF ( 9)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_ROCountTrainChannel1Rank3Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_ROCountTrainChannel1Rank3Dev0_MSK (0x0003FE00)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_ROCountTrainChannel1Rank3Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_ROCountTrainChannel1Rank3Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_ROCountTrainChannel1Rank3Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_ROCountTrainChannel1Rank3Dev0_HSH (0x0909309C)

  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_ROCountTrainChannel2Rank3Dev0_OFF (18)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_ROCountTrainChannel2Rank3Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_ROCountTrainChannel2Rank3Dev0_MSK (0x07FC0000)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_ROCountTrainChannel2Rank3Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_ROCountTrainChannel2Rank3Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_ROCountTrainChannel2Rank3Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_ROCountTrainChannel2Rank3Dev0_HSH (0x0912309C)

  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_Spare_OFF                 (27)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_Spare_WID                 ( 5)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_Spare_MSK                 (0xF8000000)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_Spare_MIN                 (0)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_Spare_MAX                 (31) // 0x0000001F
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_Spare_DEF                 (0x00000000)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV0_Spare_HSH                 (0x051B309C)

#define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_REG                         (0x000030A0)

  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_ROCountTrainChannel0Rank3Dev1_OFF ( 0)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_ROCountTrainChannel0Rank3Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_ROCountTrainChannel0Rank3Dev1_MSK (0x000001FF)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_ROCountTrainChannel0Rank3Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_ROCountTrainChannel0Rank3Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_ROCountTrainChannel0Rank3Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_ROCountTrainChannel0Rank3Dev1_HSH (0x090030A0)

  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_ROCountTrainChannel1Rank3Dev1_OFF ( 9)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_ROCountTrainChannel1Rank3Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_ROCountTrainChannel1Rank3Dev1_MSK (0x0003FE00)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_ROCountTrainChannel1Rank3Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_ROCountTrainChannel1Rank3Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_ROCountTrainChannel1Rank3Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_ROCountTrainChannel1Rank3Dev1_HSH (0x090930A0)

  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_ROCountTrainChannel2Rank3Dev1_OFF (18)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_ROCountTrainChannel2Rank3Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_ROCountTrainChannel2Rank3Dev1_MSK (0x07FC0000)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_ROCountTrainChannel2Rank3Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_ROCountTrainChannel2Rank3Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_ROCountTrainChannel2Rank3Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_ROCountTrainChannel2Rank3Dev1_HSH (0x091230A0)

  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_Spare_OFF                 (27)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_Spare_WID                 ( 5)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_Spare_MSK                 (0xF8000000)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_Spare_MIN                 (0)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_Spare_MAX                 (31) // 0x0000001F
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_Spare_DEF                 (0x00000000)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV1_Spare_HSH                 (0x051B30A0)

#define MCMISCS_ROCOUNTTRAINCH3RANK3DEV01_REG                          (0x000030A4)

  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV01_ROCountTrainChannel3Rank3Dev0_OFF ( 0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV01_ROCountTrainChannel3Rank3Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV01_ROCountTrainChannel3Rank3Dev0_MSK (0x000001FF)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV01_ROCountTrainChannel3Rank3Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV01_ROCountTrainChannel3Rank3Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV01_ROCountTrainChannel3Rank3Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV01_ROCountTrainChannel3Rank3Dev0_HSH (0x090030A4)

  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV01_ROCountTrainChannel3Rank3Dev1_OFF ( 9)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV01_ROCountTrainChannel3Rank3Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV01_ROCountTrainChannel3Rank3Dev1_MSK (0x0003FE00)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV01_ROCountTrainChannel3Rank3Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV01_ROCountTrainChannel3Rank3Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV01_ROCountTrainChannel3Rank3Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV01_ROCountTrainChannel3Rank3Dev1_HSH (0x090930A4)

  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV01_Spare_OFF                  (18)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV01_Spare_WID                  (14)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV01_Spare_MSK                  (0xFFFC0000)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV01_Spare_MIN                  (0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV01_Spare_MAX                  (16383) // 0x00003FFF
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV01_Spare_DEF                  (0x00000000)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV01_Spare_HSH                  (0x0E1230A4)

#define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_REG                          (0x000030A8)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank0_OFF_A0         ( 0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank0_WID_A0         ( 4)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank0_MSK_A0         (0x0000000F)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank0_MIN_A0         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank0_MAX_A0         (15) // 0x0000000F
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank0_DEF_A0         (0x00000001)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank0_HSH_A0         (0x040030A8)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank1_OFF_A0         ( 4)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank1_WID_A0         ( 4)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank1_MSK_A0         (0x000000F0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank1_MIN_A0         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank1_MAX_A0         (15) // 0x0000000F
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank1_DEF_A0         (0x00000002)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank1_HSH_A0         (0x040430A8)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank2_OFF_A0         ( 8)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank2_WID_A0         ( 4)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank2_MSK_A0         (0x00000F00)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank2_MIN_A0         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank2_MAX_A0         (15) // 0x0000000F
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank2_DEF_A0         (0x00000004)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank2_HSH_A0         (0x040830A8)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank3_OFF_A0         (12)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank3_WID_A0         ( 4)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank3_MSK_A0         (0x0000F000)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank3_MIN_A0         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank3_MAX_A0         (15) // 0x0000000F
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank3_DEF_A0         (0x00000008)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank3_HSH_A0         (0x040C30A8)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_Spare_OFF_A0                  (16)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_Spare_WID_A0                  (16)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_Spare_MSK_A0                  (0xFFFF0000)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_Spare_MIN_A0                  (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_Spare_MAX_A0                  (65535) // 0x0000FFFF
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_Spare_DEF_A0                  (0x00000000)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_Spare_HSH_A0                  (0x101030A8)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank0_OFF         ( 0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank0_WID         ( 8)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank0_MSK         (0x000000FF)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank0_MIN         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank0_MAX         (255) // 0x000000FF
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank0_DEF         (0x00000001)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank0_HSH         (0x080030A8)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank1_OFF         ( 8)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank1_WID         ( 8)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank1_MSK         (0x0000FF00)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank1_MIN         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank1_MAX         (255) // 0x000000FF
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank1_DEF         (0x00000002)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank1_HSH         (0x080830A8)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank2_OFF         (16)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank2_WID         ( 8)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank2_MSK         (0x00FF0000)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank2_MIN         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank2_MAX         (255) // 0x000000FF
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank2_DEF         (0x00000004)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank2_HSH         (0x081030A8)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank3_OFF         (24)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank3_WID         ( 8)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank3_MSK         (0xFF000000)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank3_MIN         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank3_MAX         (255) // 0x000000FF
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank3_DEF         (0x00000008)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL0_DevUseMapRank3_HSH         (0x081830A8)

#define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_REG                          (0x000030AC)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank0_OFF_A0         ( 0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank0_WID_A0         ( 4)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank0_MSK_A0         (0x0000000F)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank0_MIN_A0         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank0_MAX_A0         (15) // 0x0000000F
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank0_DEF_A0         (0x00000001)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank0_HSH_A0         (0x040030AC)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank1_OFF_A0         ( 4)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank1_WID_A0         ( 4)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank1_MSK_A0         (0x000000F0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank1_MIN_A0         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank1_MAX_A0         (15) // 0x0000000F
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank1_DEF_A0         (0x00000002)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank1_HSH_A0         (0x040430AC)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank2_OFF_A0         ( 8)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank2_WID_A0         ( 4)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank2_MSK_A0         (0x00000F00)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank2_MIN_A0         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank2_MAX_A0         (15) // 0x0000000F
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank2_DEF_A0         (0x00000004)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank2_HSH_A0         (0x040830AC)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank3_OFF_A0         (12)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank3_WID_A0         ( 4)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank3_MSK_A0         (0x0000F000)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank3_MIN_A0         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank3_MAX_A0         (15) // 0x0000000F
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank3_DEF_A0         (0x00000008)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank3_HSH_A0         (0x040C30AC)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_Spare_OFF_A0                  (16)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_Spare_WID_A0                  (16)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_Spare_MSK_A0                  (0xFFFF0000)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_Spare_MIN_A0                  (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_Spare_MAX_A0                  (65535) // 0x0000FFFF
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_Spare_DEF_A0                  (0x00000000)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_Spare_HSH_A0                  (0x101030AC)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank0_OFF         ( 0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank0_WID         ( 8)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank0_MSK         (0x000000FF)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank0_MIN         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank0_MAX         (255) // 0x000000FF
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank0_DEF         (0x00000001)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank0_HSH         (0x080030AC)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank1_OFF         ( 8)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank1_WID         ( 8)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank1_MSK         (0x0000FF00)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank1_MIN         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank1_MAX         (255) // 0x000000FF
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank1_DEF         (0x00000002)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank1_HSH         (0x080830AC)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank2_OFF         (16)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank2_WID         ( 8)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank2_MSK         (0x00FF0000)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank2_MIN         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank2_MAX         (255) // 0x000000FF
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank2_DEF         (0x00000004)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank2_HSH         (0x081030AC)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank3_OFF         (24)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank3_WID         ( 8)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank3_MSK         (0xFF000000)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank3_MIN         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank3_MAX         (255) // 0x000000FF
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank3_DEF         (0x00000008)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL1_DevUseMapRank3_HSH         (0x081830AC)

#define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_REG                          (0x000030B0)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank0_OFF_A0         ( 0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank0_WID_A0         ( 4)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank0_MSK_A0         (0x0000000F)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank0_MIN_A0         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank0_MAX_A0         (15) // 0x0000000F
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank0_DEF_A0         (0x00000001)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank0_HSH_A0         (0x040030B0)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank1_OFF_A0         ( 4)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank1_WID_A0         ( 4)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank1_MSK_A0         (0x000000F0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank1_MIN_A0         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank1_MAX_A0         (15) // 0x0000000F
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank1_DEF_A0         (0x00000002)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank1_HSH_A0         (0x040430B0)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank2_OFF_A0         ( 8)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank2_WID_A0         ( 4)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank2_MSK_A0         (0x00000F00)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank2_MIN_A0         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank2_MAX_A0         (15) // 0x0000000F
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank2_DEF_A0         (0x00000004)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank2_HSH_A0         (0x040830B0)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank3_OFF_A0         (12)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank3_WID_A0         ( 4)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank3_MSK_A0         (0x0000F000)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank3_MIN_A0         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank3_MAX_A0         (15) // 0x0000000F
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank3_DEF_A0         (0x00000008)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank3_HSH_A0         (0x040C30B0)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_Spare_OFF_A0                  (16)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_Spare_WID_A0                  (16)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_Spare_MSK_A0                  (0xFFFF0000)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_Spare_MIN_A0                  (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_Spare_MAX_A0                  (65535) // 0x0000FFFF
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_Spare_DEF_A0                  (0x00000000)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_Spare_HSH_A0                  (0x101030B0)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank0_OFF         ( 0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank0_WID         ( 8)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank0_MSK         (0x000000FF)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank0_MIN         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank0_MAX         (255) // 0x000000FF
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank0_DEF         (0x00000001)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank0_HSH         (0x080030B0)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank1_OFF         ( 8)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank1_WID         ( 8)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank1_MSK         (0x0000FF00)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank1_MIN         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank1_MAX         (255) // 0x000000FF
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank1_DEF         (0x00000002)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank1_HSH         (0x080830B0)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank2_OFF         (16)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank2_WID         ( 8)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank2_MSK         (0x00FF0000)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank2_MIN         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank2_MAX         (255) // 0x000000FF
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank2_DEF         (0x00000004)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank2_HSH         (0x081030B0)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank3_OFF         (24)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank3_WID         ( 8)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank3_MSK         (0xFF000000)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank3_MIN         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank3_MAX         (255) // 0x000000FF
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank3_DEF         (0x00000008)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL2_DevUseMapRank3_HSH         (0x081830B0)

#define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_REG                          (0x000030B4)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank0_OFF_A0         ( 0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank0_WID_A0         ( 4)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank0_MSK_A0         (0x0000000F)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank0_MIN_A0         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank0_MAX_A0         (15) // 0x0000000F
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank0_DEF_A0         (0x00000001)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank0_HSH_A0         (0x040030B4)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank1_OFF_A0         ( 4)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank1_WID_A0         ( 4)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank1_MSK_A0         (0x000000F0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank1_MIN_A0         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank1_MAX_A0         (15) // 0x0000000F
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank1_DEF_A0         (0x00000002)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank1_HSH_A0         (0x040430B4)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank2_OFF_A0         ( 8)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank2_WID_A0         ( 4)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank2_MSK_A0         (0x00000F00)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank2_MIN_A0         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank2_MAX_A0         (15) // 0x0000000F
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank2_DEF_A0         (0x00000004)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank2_HSH_A0         (0x040830B4)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank3_OFF_A0         (12)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank3_WID_A0         ( 4)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank3_MSK_A0         (0x0000F000)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank3_MIN_A0         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank3_MAX_A0         (15) // 0x0000000F
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank3_DEF_A0         (0x00000008)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank3_HSH_A0         (0x040C30B4)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_Spare_OFF_A0                  (16)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_Spare_WID_A0                  (16)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_Spare_MSK_A0                  (0xFFFF0000)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_Spare_MIN_A0                  (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_Spare_MAX_A0                  (65535) // 0x0000FFFF
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_Spare_DEF_A0                  (0x00000000)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_Spare_HSH_A0                  (0x101030B4)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank0_OFF         ( 0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank0_WID         ( 8)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank0_MSK         (0x000000FF)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank0_MIN         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank0_MAX         (255) // 0x000000FF
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank0_DEF         (0x00000001)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank0_HSH         (0x080030B4)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank1_OFF         ( 8)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank1_WID         ( 8)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank1_MSK         (0x0000FF00)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank1_MIN         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank1_MAX         (255) // 0x000000FF
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank1_DEF         (0x00000002)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank1_HSH         (0x080830B4)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank2_OFF         (16)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank2_WID         ( 8)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank2_MSK         (0x00FF0000)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank2_MIN         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank2_MAX         (255) // 0x000000FF
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank2_DEF         (0x00000004)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank2_HSH         (0x081030B4)

  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank3_OFF         (24)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank3_WID         ( 8)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank3_MSK         (0xFF000000)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank3_MIN         (0)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank3_MAX         (255) // 0x000000FF
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank3_DEF         (0x00000008)
  #define MCMISCS_DELTADQSDEVUSEMAPCHANNEL3_DevUseMapRank3_HSH         (0x081830B4)

#define MCMISCS_DELTADQSCOMMON0_REG                                    (0x000030B8)

  #define MCMISCS_DELTADQSCOMMON0_Lp4ReTrainDuration_OFF               ( 0)
  #define MCMISCS_DELTADQSCOMMON0_Lp4ReTrainDuration_WID               (18)
  #define MCMISCS_DELTADQSCOMMON0_Lp4ReTrainDuration_MSK               (0x0003FFFF)
  #define MCMISCS_DELTADQSCOMMON0_Lp4ReTrainDuration_MIN               (0)
  #define MCMISCS_DELTADQSCOMMON0_Lp4ReTrainDuration_MAX               (262143) // 0x0003FFFF
  #define MCMISCS_DELTADQSCOMMON0_Lp4ReTrainDuration_DEF               (0x00010000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4ReTrainDuration_HSH               (0x120030B8)

  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSTrainMode_OFF             (18)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSTrainMode_WID             ( 1)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSTrainMode_MSK             (0x00040000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSTrainMode_MIN             (0)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSTrainMode_MAX             (1) // 0x00000001
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSTrainMode_DEF             (0x00000000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSTrainMode_HSH             (0x011230B8)

  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSCalcUnitOvrd_OFF_A0          (19)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSCalcUnitOvrd_WID_A0          ( 1)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSCalcUnitOvrd_MSK_A0          (0x00080000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSCalcUnitOvrd_MIN_A0          (0)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSCalcUnitOvrd_MAX_A0          (1) // 0x00000001
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSCalcUnitOvrd_DEF_A0          (0x00000000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSCalcUnitOvrd_HSH_A0          (0x011330B8)

  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSCalcUnitOvrdEn_OFF_A0        (20)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSCalcUnitOvrdEn_WID_A0        ( 1)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSCalcUnitOvrdEn_MSK_A0        (0x00100000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSCalcUnitOvrdEn_MIN_A0        (0)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSCalcUnitOvrdEn_MAX_A0        (1) // 0x00000001
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSCalcUnitOvrdEn_DEF_A0        (0x00000000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSCalcUnitOvrdEn_HSH_A0        (0x011430B8)

  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrd_OFF_A0         (21)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrd_WID_A0         ( 1)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrd_MSK_A0         (0x00200000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrd_MIN_A0         (0)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrd_MAX_A0         (1) // 0x00000001
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrd_DEF_A0         (0x00000000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrd_HSH_A0         (0x011530B8)

  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrdEn_OFF_A0       (22)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrdEn_WID_A0       ( 1)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrdEn_MSK_A0       (0x00400000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrdEn_MIN_A0       (0)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrdEn_MAX_A0       (1) // 0x00000001
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrdEn_DEF_A0       (0x00000000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrdEn_HSH_A0       (0x011630B8)

  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqChRankSelectOrvd_OFF_A0 (23)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqChRankSelectOrvd_WID_A0 ( 4)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqChRankSelectOrvd_MSK_A0 (0x07800000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqChRankSelectOrvd_MIN_A0 (0)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqChRankSelectOrvd_MAX_A0 (15) // 0x0000000F
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqChRankSelectOrvd_DEF_A0 (0x00000000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqChRankSelectOrvd_HSH_A0 (0x041730B8)

  #define MCMISCS_DELTADQSCOMMON0_Lp4RankPairSwap_OFF_A0                  (27)
  #define MCMISCS_DELTADQSCOMMON0_Lp4RankPairSwap_WID_A0                  ( 1)
  #define MCMISCS_DELTADQSCOMMON0_Lp4RankPairSwap_MSK_A0                  (0x08000000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4RankPairSwap_MIN_A0                  (0)
  #define MCMISCS_DELTADQSCOMMON0_Lp4RankPairSwap_MAX_A0                  (1) // 0x00000001
  #define MCMISCS_DELTADQSCOMMON0_Lp4RankPairSwap_DEF_A0                  (0x00000000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4RankPairSwap_HSH_A0                  (0x011B30B8)

  #define MCMISCS_DELTADQSCOMMON0_Lp4MR19ExeQueWriteEnableOvrd_OFF_A0     (28)
  #define MCMISCS_DELTADQSCOMMON0_Lp4MR19ExeQueWriteEnableOvrd_WID_A0     ( 1)
  #define MCMISCS_DELTADQSCOMMON0_Lp4MR19ExeQueWriteEnableOvrd_MSK_A0     (0x10000000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4MR19ExeQueWriteEnableOvrd_MIN_A0     (0)
  #define MCMISCS_DELTADQSCOMMON0_Lp4MR19ExeQueWriteEnableOvrd_MAX_A0     (1) // 0x00000001
  #define MCMISCS_DELTADQSCOMMON0_Lp4MR19ExeQueWriteEnableOvrd_DEF_A0     (0x00000000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4MR19ExeQueWriteEnableOvrd_HSH_A0     (0x011C30B8)

  #define MCMISCS_DELTADQSCOMMON0_Lp4MR19ExeQueWriteEnableOvrdEn_OFF_A0   (29)
  #define MCMISCS_DELTADQSCOMMON0_Lp4MR19ExeQueWriteEnableOvrdEn_WID_A0   ( 1)
  #define MCMISCS_DELTADQSCOMMON0_Lp4MR19ExeQueWriteEnableOvrdEn_MSK_A0   (0x20000000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4MR19ExeQueWriteEnableOvrdEn_MIN_A0   (0)
  #define MCMISCS_DELTADQSCOMMON0_Lp4MR19ExeQueWriteEnableOvrdEn_MAX_A0   (1) // 0x00000001
  #define MCMISCS_DELTADQSCOMMON0_Lp4MR19ExeQueWriteEnableOvrdEn_DEF_A0   (0x00000000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4MR19ExeQueWriteEnableOvrdEn_HSH_A0   (0x011D30B8)

  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSROCountForceZero_OFF_A0      (30)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSROCountForceZero_WID_A0      ( 1)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSROCountForceZero_MSK_A0      (0x40000000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSROCountForceZero_MIN_A0      (0)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSROCountForceZero_MAX_A0      (1) // 0x00000001
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSROCountForceZero_DEF_A0      (0x00000000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSROCountForceZero_HSH_A0      (0x011E30B8)

  #define MCMISCS_DELTADQSCOMMON0_InternalClocksOn_OFF_A0                 (31)
  #define MCMISCS_DELTADQSCOMMON0_InternalClocksOn_WID_A0                 ( 1)
  #define MCMISCS_DELTADQSCOMMON0_InternalClocksOn_MSK_A0                 (0x80000000)
  #define MCMISCS_DELTADQSCOMMON0_InternalClocksOn_MIN_A0                 (0)
  #define MCMISCS_DELTADQSCOMMON0_InternalClocksOn_MAX_A0                 (1) // 0x00000001
  #define MCMISCS_DELTADQSCOMMON0_InternalClocksOn_DEF_A0                 (0x00000000)
  #define MCMISCS_DELTADQSCOMMON0_InternalClocksOn_HSH_A0                 (0x011F30B8)

  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrd_OFF         (19)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrd_WID         ( 1)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrd_MSK         (0x00080000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrd_MIN         (0)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrd_MAX         (1) // 0x00000001
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrd_DEF         (0x00000000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrd_HSH         (0x011330B8)

  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrdEn_OFF       (20)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrdEn_WID       ( 1)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrdEn_MSK       (0x00100000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrdEn_MIN       (0)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrdEn_MAX       (1) // 0x00000001
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrdEn_DEF       (0x00000000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqOvrdEn_HSH       (0x011430B8)

  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqChRankSelectOrvd_OFF (21)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqChRankSelectOrvd_WID ( 4)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqChRankSelectOrvd_MSK (0x01E00000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqChRankSelectOrvd_MIN (0)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqChRankSelectOrvd_MAX (15) // 0x0000000F
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqChRankSelectOrvd_DEF (0x00000000)
  #define MCMISCS_DELTADQSCOMMON0_Lp4DeltaDQSUpdateReqChRankSelectOrvd_HSH (0x041530B8)

  #define MCMISCS_DELTADQSCOMMON0_InternalClocksOn_OFF                 (25)
  #define MCMISCS_DELTADQSCOMMON0_InternalClocksOn_WID                 ( 1)
  #define MCMISCS_DELTADQSCOMMON0_InternalClocksOn_MSK                 (0x02000000)
  #define MCMISCS_DELTADQSCOMMON0_InternalClocksOn_MIN                 (0)
  #define MCMISCS_DELTADQSCOMMON0_InternalClocksOn_MAX                 (1) // 0x00000001
  #define MCMISCS_DELTADQSCOMMON0_InternalClocksOn_DEF                 (0x00000000)
  #define MCMISCS_DELTADQSCOMMON0_InternalClocksOn_HSH                 (0x011930B8)

  #define MCMISCS_DELTADQSCOMMON0_clock_on_with_rxanalogen_OFF         (26)
  #define MCMISCS_DELTADQSCOMMON0_clock_on_with_rxanalogen_WID         ( 1)
  #define MCMISCS_DELTADQSCOMMON0_clock_on_with_rxanalogen_MSK         (0x04000000)
  #define MCMISCS_DELTADQSCOMMON0_clock_on_with_rxanalogen_MIN         (0)
  #define MCMISCS_DELTADQSCOMMON0_clock_on_with_rxanalogen_MAX         (1) // 0x00000001
  #define MCMISCS_DELTADQSCOMMON0_clock_on_with_rxanalogen_DEF         (0x00000000)
  #define MCMISCS_DELTADQSCOMMON0_clock_on_with_rxanalogen_HSH         (0x011A30B8)

  #define MCMISCS_DELTADQSCOMMON0_retrain_cmd_type_swap_b_OFF          (27)
  #define MCMISCS_DELTADQSCOMMON0_retrain_cmd_type_swap_b_WID          ( 1)
  #define MCMISCS_DELTADQSCOMMON0_retrain_cmd_type_swap_b_MSK          (0x08000000)
  #define MCMISCS_DELTADQSCOMMON0_retrain_cmd_type_swap_b_MIN          (0)
  #define MCMISCS_DELTADQSCOMMON0_retrain_cmd_type_swap_b_MAX          (1) // 0x00000001
  #define MCMISCS_DELTADQSCOMMON0_retrain_cmd_type_swap_b_DEF          (0x00000000)
  #define MCMISCS_DELTADQSCOMMON0_retrain_cmd_type_swap_b_HSH          (0x011B30B8)

  #define MCMISCS_DELTADQSCOMMON0_spare_OFF                            (28)
  #define MCMISCS_DELTADQSCOMMON0_spare_WID                            ( 4)
  #define MCMISCS_DELTADQSCOMMON0_spare_MSK                            (0xF0000000)
  #define MCMISCS_DELTADQSCOMMON0_spare_MIN                            (0)
  #define MCMISCS_DELTADQSCOMMON0_spare_MAX                            (15) // 0x0000000F
  #define MCMISCS_DELTADQSCOMMON0_spare_DEF                            (0x00000000)
  #define MCMISCS_DELTADQSCOMMON0_spare_HSH                            (0x041C30B8)

#define MCMISCS_DELTADQSCOMMON1_REG                                    (0x000030BC)

  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBDistAddrOvrd_OFF          ( 0)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBDistAddrOvrd_WID          (16)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBDistAddrOvrd_MSK          (0x0000FFFF)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBDistAddrOvrd_MIN          (0)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBDistAddrOvrd_MAX          (65535) // 0x0000FFFF
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBDistAddrOvrd_DEF          (0x00000000)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBDistAddrOvrd_HSH          (0x100030BC)

  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBDistAddrOvrdEn_OFF        (16)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBDistAddrOvrdEn_WID        ( 1)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBDistAddrOvrdEn_MSK        (0x00010000)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBDistAddrOvrdEn_MIN        (0)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBDistAddrOvrdEn_MAX        (1) // 0x00000001
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBDistAddrOvrdEn_DEF        (0x00000000)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBDistAddrOvrdEn_HSH        (0x011030BC)

  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBRequestOvrd_OFF           (17)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBRequestOvrd_WID           ( 1)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBRequestOvrd_MSK           (0x00020000)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBRequestOvrd_MIN           (0)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBRequestOvrd_MAX           (1) // 0x00000001
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBRequestOvrd_DEF           (0x00000000)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBRequestOvrd_HSH           (0x011130BC)

  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBRequestOvrdEn_OFF         (18)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBRequestOvrdEn_WID         ( 1)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBRequestOvrdEn_MSK         (0x00040000)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBRequestOvrdEn_MIN         (0)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBRequestOvrdEn_MAX         (1) // 0x00000001
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBRequestOvrdEn_DEF         (0x00000000)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSAPBRequestOvrdEn_HSH         (0x011230BC)

  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSMcQuietCycleReqChOvrd_OFF    (19)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSMcQuietCycleReqChOvrd_WID    ( 4)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSMcQuietCycleReqChOvrd_MSK    (0x00780000)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSMcQuietCycleReqChOvrd_MIN    (0)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSMcQuietCycleReqChOvrd_MAX    (15) // 0x0000000F
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSMcQuietCycleReqChOvrd_DEF    (0x00000000)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSMcQuietCycleReqChOvrd_HSH    (0x041330BC)

  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSMcQuietCycleReqChOvrdEn_OFF  (23)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSMcQuietCycleReqChOvrdEn_WID  ( 4)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSMcQuietCycleReqChOvrdEn_MSK  (0x07800000)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSMcQuietCycleReqChOvrdEn_MIN  (0)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSMcQuietCycleReqChOvrdEn_MAX  (15) // 0x0000000F
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSMcQuietCycleReqChOvrdEn_DEF  (0x00000000)
  #define MCMISCS_DELTADQSCOMMON1_DeltaDQSMcQuietCycleReqChOvrdEn_HSH  (0x041730BC)

  #define MCMISCS_DELTADQSCOMMON1_DfxLp4ObsROCountChRankSel_OFF        (27)
  #define MCMISCS_DELTADQSCOMMON1_DfxLp4ObsROCountChRankSel_WID        ( 4)
  #define MCMISCS_DELTADQSCOMMON1_DfxLp4ObsROCountChRankSel_MSK        (0x78000000)
  #define MCMISCS_DELTADQSCOMMON1_DfxLp4ObsROCountChRankSel_MIN        (0)
  #define MCMISCS_DELTADQSCOMMON1_DfxLp4ObsROCountChRankSel_MAX        (15) // 0x0000000F
  #define MCMISCS_DELTADQSCOMMON1_DfxLp4ObsROCountChRankSel_DEF        (0x00000000)
  #define MCMISCS_DELTADQSCOMMON1_DfxLp4ObsROCountChRankSel_HSH        (0x041B30BC)

  #define MCMISCS_DELTADQSCOMMON1_DfxLp4ObsSel_OFF                     (31)
  #define MCMISCS_DELTADQSCOMMON1_DfxLp4ObsSel_WID                     ( 1)
  #define MCMISCS_DELTADQSCOMMON1_DfxLp4ObsSel_MSK                     (0x80000000)
  #define MCMISCS_DELTADQSCOMMON1_DfxLp4ObsSel_MIN                     (0)
  #define MCMISCS_DELTADQSCOMMON1_DfxLp4ObsSel_MAX                     (1) // 0x00000001
  #define MCMISCS_DELTADQSCOMMON1_DfxLp4ObsSel_DEF                     (0x00000000)
  #define MCMISCS_DELTADQSCOMMON1_DfxLp4ObsSel_HSH                     (0x011F30BC)

#define MCMISCS_DELTADQSCOMMON2_REG                                    (0x000030C0)

  #define MCMISCS_DELTADQSCOMMON2_DfxLp4OBSData_OFF                    ( 0)
  #define MCMISCS_DELTADQSCOMMON2_DfxLp4OBSData_WID                    (32)
  #define MCMISCS_DELTADQSCOMMON2_DfxLp4OBSData_MSK                    (0xFFFFFFFF)
  #define MCMISCS_DELTADQSCOMMON2_DfxLp4OBSData_MIN                    (0)
  #define MCMISCS_DELTADQSCOMMON2_DfxLp4OBSData_MAX                    (4294967295) // 0xFFFFFFFF
  #define MCMISCS_DELTADQSCOMMON2_DfxLp4OBSData_DEF                    (0x00000000)
  #define MCMISCS_DELTADQSCOMMON2_DfxLp4OBSData_HSH                    (0x200030C0)

#define DDRSCRAM_CR_DDRMISCCONTROL3_REG                                (0x000030C4)

  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf0_Mapping_OFF              ( 0)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf0_Mapping_WID              ( 3)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf0_Mapping_MSK              (0x00000007)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf0_Mapping_MIN              (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf0_Mapping_MAX              (7) // 0x00000007
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf0_Mapping_DEF              (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf0_Mapping_HSH              (0x030030C4)

  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf1_Mapping_OFF              ( 3)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf1_Mapping_WID              ( 3)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf1_Mapping_MSK              (0x00000038)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf1_Mapping_MIN              (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf1_Mapping_MAX              (7) // 0x00000007
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf1_Mapping_DEF              (0x00000001)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf1_Mapping_HSH              (0x030330C4)

  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf2_Mapping_OFF              ( 6)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf2_Mapping_WID              ( 3)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf2_Mapping_MSK              (0x000001C0)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf2_Mapping_MIN              (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf2_Mapping_MAX              (7) // 0x00000007
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf2_Mapping_DEF              (0x00000002)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf2_Mapping_HSH              (0x030630C4)

  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf3_Mapping_OFF              ( 9)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf3_Mapping_WID              ( 3)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf3_Mapping_MSK              (0x00000E00)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf3_Mapping_MIN              (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf3_Mapping_MAX              (7) // 0x00000007
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf3_Mapping_DEF              (0x00000003)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf3_Mapping_HSH              (0x030930C4)

  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf4_Mapping_OFF              (12)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf4_Mapping_WID              ( 3)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf4_Mapping_MSK              (0x00007000)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf4_Mapping_MIN              (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf4_Mapping_MAX              (7) // 0x00000007
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf4_Mapping_DEF              (0x00000004)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf4_Mapping_HSH              (0x030C30C4)

  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf5_Mapping_OFF              (15)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf5_Mapping_WID              ( 3)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf5_Mapping_MSK              (0x00038000)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf5_Mapping_MIN              (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf5_Mapping_MAX              (7) // 0x00000007
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf5_Mapping_DEF              (0x00000005)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf5_Mapping_HSH              (0x030F30C4)

  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf6_Mapping_OFF              (18)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf6_Mapping_WID              ( 3)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf6_Mapping_MSK              (0x001C0000)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf6_Mapping_MIN              (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf6_Mapping_MAX              (7) // 0x00000007
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf6_Mapping_DEF              (0x00000006)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf6_Mapping_HSH              (0x031230C4)

  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf7_Mapping_OFF              (21)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf7_Mapping_WID              ( 3)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf7_Mapping_MSK              (0x00E00000)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf7_Mapping_MIN              (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf7_Mapping_MAX              (7) // 0x00000007
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf7_Mapping_DEF              (0x00000007)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_CKEbuf7_Mapping_HSH              (0x031530C4)

  #define DDRSCRAM_CR_DDRMISCCONTROL3_use_grace_count_for_rxclk_OFF    (24)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_use_grace_count_for_rxclk_WID    ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_use_grace_count_for_rxclk_MSK    (0x01000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_use_grace_count_for_rxclk_MIN    (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_use_grace_count_for_rxclk_MAX    (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL3_use_grace_count_for_rxclk_DEF    (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_use_grace_count_for_rxclk_HSH    (0x011830C4)

  #define DDRSCRAM_CR_DDRMISCCONTROL3_glbdrv_clkgate_enable_OFF        (25)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_glbdrv_clkgate_enable_WID        ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_glbdrv_clkgate_enable_MSK        (0x02000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_glbdrv_clkgate_enable_MIN        (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_glbdrv_clkgate_enable_MAX        (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL3_glbdrv_clkgate_enable_DEF        (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_glbdrv_clkgate_enable_HSH        (0x011930C4)

  #define DDRSCRAM_CR_DDRMISCCONTROL3_Spare2_OFF                       (26)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_Spare2_WID                       ( 6)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_Spare2_MSK                       (0xFC000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_Spare2_MIN                       (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_Spare2_MAX                       (63) // 0x0000003F
  #define DDRSCRAM_CR_DDRMISCCONTROL3_Spare2_DEF                       (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL3_Spare2_HSH                       (0x061A30C4)

#define DDRSCRAM_CR_DDRMISCCONTROL4_REG                                (0x000030C8)

  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf0_Mapping_OFF              ( 0)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf0_Mapping_WID              ( 3)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf0_Mapping_MSK              (0x00000007)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf0_Mapping_MIN              (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf0_Mapping_MAX              (7) // 0x00000007
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf0_Mapping_DEF              (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf0_Mapping_HSH              (0x030030C8)

  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf1_Mapping_OFF              ( 3)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf1_Mapping_WID              ( 3)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf1_Mapping_MSK              (0x00000038)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf1_Mapping_MIN              (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf1_Mapping_MAX              (7) // 0x00000007
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf1_Mapping_DEF              (0x00000001)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf1_Mapping_HSH              (0x030330C8)

  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf2_Mapping_OFF              ( 6)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf2_Mapping_WID              ( 3)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf2_Mapping_MSK              (0x000001C0)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf2_Mapping_MIN              (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf2_Mapping_MAX              (7) // 0x00000007
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf2_Mapping_DEF              (0x00000002)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf2_Mapping_HSH              (0x030630C8)

  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf3_Mapping_OFF              ( 9)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf3_Mapping_WID              ( 3)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf3_Mapping_MSK              (0x00000E00)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf3_Mapping_MIN              (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf3_Mapping_MAX              (7) // 0x00000007
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf3_Mapping_DEF              (0x00000003)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf3_Mapping_HSH              (0x030930C8)

  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf4_Mapping_OFF              (12)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf4_Mapping_WID              ( 3)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf4_Mapping_MSK              (0x00007000)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf4_Mapping_MIN              (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf4_Mapping_MAX              (7) // 0x00000007
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf4_Mapping_DEF              (0x00000004)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf4_Mapping_HSH              (0x030C30C8)

  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf5_Mapping_OFF              (15)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf5_Mapping_WID              ( 3)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf5_Mapping_MSK              (0x00038000)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf5_Mapping_MIN              (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf5_Mapping_MAX              (7) // 0x00000007
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf5_Mapping_DEF              (0x00000005)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf5_Mapping_HSH              (0x030F30C8)

  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf6_Mapping_OFF              (18)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf6_Mapping_WID              ( 3)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf6_Mapping_MSK              (0x001C0000)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf6_Mapping_MIN              (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf6_Mapping_MAX              (7) // 0x00000007
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf6_Mapping_DEF              (0x00000006)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf6_Mapping_HSH              (0x031230C8)

  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf7_Mapping_OFF              (21)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf7_Mapping_WID              ( 3)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf7_Mapping_MSK              (0x00E00000)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf7_Mapping_MIN              (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf7_Mapping_MAX              (7) // 0x00000007
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf7_Mapping_DEF              (0x00000007)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_CKEbuf7_Mapping_HSH              (0x031530C8)

  #define DDRSCRAM_CR_DDRMISCCONTROL4_use_grace_count_for_rxclk_OFF    (24)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_use_grace_count_for_rxclk_WID    ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_use_grace_count_for_rxclk_MSK    (0x01000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_use_grace_count_for_rxclk_MIN    (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_use_grace_count_for_rxclk_MAX    (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL4_use_grace_count_for_rxclk_DEF    (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_use_grace_count_for_rxclk_HSH    (0x011830C8)

  #define DDRSCRAM_CR_DDRMISCCONTROL4_glbdrv_clkgate_enable_OFF        (25)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_glbdrv_clkgate_enable_WID        ( 1)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_glbdrv_clkgate_enable_MSK        (0x02000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_glbdrv_clkgate_enable_MIN        (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_glbdrv_clkgate_enable_MAX        (1) // 0x00000001
  #define DDRSCRAM_CR_DDRMISCCONTROL4_glbdrv_clkgate_enable_DEF        (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_glbdrv_clkgate_enable_HSH        (0x011930C8)

  #define DDRSCRAM_CR_DDRMISCCONTROL4_Spare2_OFF                       (26)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_Spare2_WID                       ( 6)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_Spare2_MSK                       (0xFC000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_Spare2_MIN                       (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_Spare2_MAX                       (63) // 0x0000003F
  #define DDRSCRAM_CR_DDRMISCCONTROL4_Spare2_DEF                       (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL4_Spare2_HSH                       (0x061A30C8)

#define MCMISCS_WRITECFGCHACHB0_REG                                    (0x000030CC)

  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank0ChADel_OFF          ( 0)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank0ChADel_WID          ( 3)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank0ChADel_MSK          (0x00000007)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank0ChADel_MIN          (0)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank0ChADel_MAX          (7) // 0x00000007
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank0ChADel_DEF          (0x00000000)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank0ChADel_HSH          (0x030030CC)

  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank1ChADel_OFF          ( 3)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank1ChADel_WID          ( 3)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank1ChADel_MSK          (0x00000038)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank1ChADel_MIN          (0)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank1ChADel_MAX          (7) // 0x00000007
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank1ChADel_DEF          (0x00000000)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank1ChADel_HSH          (0x030330CC)

  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank2ChADel_OFF          ( 6)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank2ChADel_WID          ( 3)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank2ChADel_MSK          (0x000001C0)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank2ChADel_MIN          (0)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank2ChADel_MAX          (7) // 0x00000007
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank2ChADel_DEF          (0x00000000)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank2ChADel_HSH          (0x030630CC)

  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank3ChADel_OFF          ( 9)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank3ChADel_WID          ( 3)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank3ChADel_MSK          (0x00000E00)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank3ChADel_MIN          (0)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank3ChADel_MAX          (7) // 0x00000007
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank3ChADel_DEF          (0x00000000)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank3ChADel_HSH          (0x030930CC)

  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank0ChBDel_OFF          (12)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank0ChBDel_WID          ( 3)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank0ChBDel_MSK          (0x00007000)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank0ChBDel_MIN          (0)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank0ChBDel_MAX          (7) // 0x00000007
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank0ChBDel_DEF          (0x00000000)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank0ChBDel_HSH          (0x030C30CC)

  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank1ChBDel_OFF          (15)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank1ChBDel_WID          ( 3)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank1ChBDel_MSK          (0x00038000)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank1ChBDel_MIN          (0)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank1ChBDel_MAX          (7) // 0x00000007
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank1ChBDel_DEF          (0x00000000)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank1ChBDel_HSH          (0x030F30CC)

  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank2ChBDel_OFF          (18)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank2ChBDel_WID          ( 3)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank2ChBDel_MSK          (0x001C0000)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank2ChBDel_MIN          (0)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank2ChBDel_MAX          (7) // 0x00000007
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank2ChBDel_DEF          (0x00000000)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank2ChBDel_HSH          (0x031230CC)

  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank3ChBDel_OFF          (21)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank3ChBDel_WID          ( 3)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank3ChBDel_MSK          (0x00E00000)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank3ChBDel_MIN          (0)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank3ChBDel_MAX          (7) // 0x00000007
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank3ChBDel_DEF          (0x00000000)
  #define MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank3ChBDel_HSH          (0x031530CC)

  #define MCMISCS_WRITECFGCHACHB0_tx_analog_clk_gate_dis_OFF           (24)
  #define MCMISCS_WRITECFGCHACHB0_tx_analog_clk_gate_dis_WID           ( 1)
  #define MCMISCS_WRITECFGCHACHB0_tx_analog_clk_gate_dis_MSK           (0x01000000)
  #define MCMISCS_WRITECFGCHACHB0_tx_analog_clk_gate_dis_MIN           (0)
  #define MCMISCS_WRITECFGCHACHB0_tx_analog_clk_gate_dis_MAX           (1) // 0x00000001
  #define MCMISCS_WRITECFGCHACHB0_tx_analog_clk_gate_dis_DEF           (0x00000000)
  #define MCMISCS_WRITECFGCHACHB0_tx_analog_clk_gate_dis_HSH           (0x011830CC)

  #define MCMISCS_WRITECFGCHACHB0_Spare_OFF                            (25)
  #define MCMISCS_WRITECFGCHACHB0_Spare_WID                            ( 7)
  #define MCMISCS_WRITECFGCHACHB0_Spare_MSK                            (0xFE000000)
  #define MCMISCS_WRITECFGCHACHB0_Spare_MIN                            (0)
  #define MCMISCS_WRITECFGCHACHB0_Spare_MAX                            (127) // 0x0000007F
  #define MCMISCS_WRITECFGCHACHB0_Spare_DEF                            (0x00000000)
  #define MCMISCS_WRITECFGCHACHB0_Spare_HSH                            (0x071930CC)

#define MCMISCS_WRITECFGCHACHB1_REG                                    (0x000030D0)

  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank0ChADel_OFF          ( 0)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank0ChADel_WID          ( 3)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank0ChADel_MSK          (0x00000007)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank0ChADel_MIN          (0)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank0ChADel_MAX          (7) // 0x00000007
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank0ChADel_DEF          (0x00000000)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank0ChADel_HSH          (0x030030D0)

  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank1ChADel_OFF          ( 3)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank1ChADel_WID          ( 3)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank1ChADel_MSK          (0x00000038)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank1ChADel_MIN          (0)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank1ChADel_MAX          (7) // 0x00000007
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank1ChADel_DEF          (0x00000000)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank1ChADel_HSH          (0x030330D0)

  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank2ChADel_OFF          ( 6)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank2ChADel_WID          ( 3)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank2ChADel_MSK          (0x000001C0)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank2ChADel_MIN          (0)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank2ChADel_MAX          (7) // 0x00000007
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank2ChADel_DEF          (0x00000000)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank2ChADel_HSH          (0x030630D0)

  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank3ChADel_OFF          ( 9)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank3ChADel_WID          ( 3)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank3ChADel_MSK          (0x00000E00)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank3ChADel_MIN          (0)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank3ChADel_MAX          (7) // 0x00000007
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank3ChADel_DEF          (0x00000000)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank3ChADel_HSH          (0x030930D0)

  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank0ChBDel_OFF          (12)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank0ChBDel_WID          ( 3)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank0ChBDel_MSK          (0x00007000)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank0ChBDel_MIN          (0)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank0ChBDel_MAX          (7) // 0x00000007
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank0ChBDel_DEF          (0x00000000)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank0ChBDel_HSH          (0x030C30D0)

  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank1ChBDel_OFF          (15)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank1ChBDel_WID          ( 3)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank1ChBDel_MSK          (0x00038000)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank1ChBDel_MIN          (0)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank1ChBDel_MAX          (7) // 0x00000007
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank1ChBDel_DEF          (0x00000000)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank1ChBDel_HSH          (0x030F30D0)

  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank2ChBDel_OFF          (18)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank2ChBDel_WID          ( 3)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank2ChBDel_MSK          (0x001C0000)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank2ChBDel_MIN          (0)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank2ChBDel_MAX          (7) // 0x00000007
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank2ChBDel_DEF          (0x00000000)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank2ChBDel_HSH          (0x031230D0)

  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank3ChBDel_OFF          (21)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank3ChBDel_WID          ( 3)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank3ChBDel_MSK          (0x00E00000)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank3ChBDel_MIN          (0)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank3ChBDel_MAX          (7) // 0x00000007
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank3ChBDel_DEF          (0x00000000)
  #define MCMISCS_WRITECFGCHACHB1_TxDqFifoRdEnRank3ChBDel_HSH          (0x031530D0)

  #define MCMISCS_WRITECFGCHACHB1_tx_analog_clk_gate_dis_OFF           (24)
  #define MCMISCS_WRITECFGCHACHB1_tx_analog_clk_gate_dis_WID           ( 1)
  #define MCMISCS_WRITECFGCHACHB1_tx_analog_clk_gate_dis_MSK           (0x01000000)
  #define MCMISCS_WRITECFGCHACHB1_tx_analog_clk_gate_dis_MIN           (0)
  #define MCMISCS_WRITECFGCHACHB1_tx_analog_clk_gate_dis_MAX           (1) // 0x00000001
  #define MCMISCS_WRITECFGCHACHB1_tx_analog_clk_gate_dis_DEF           (0x00000000)
  #define MCMISCS_WRITECFGCHACHB1_tx_analog_clk_gate_dis_HSH           (0x011830D0)

  #define MCMISCS_WRITECFGCHACHB1_Spare_OFF                            (25)
  #define MCMISCS_WRITECFGCHACHB1_Spare_WID                            ( 7)
  #define MCMISCS_WRITECFGCHACHB1_Spare_MSK                            (0xFE000000)
  #define MCMISCS_WRITECFGCHACHB1_Spare_MIN                            (0)
  #define MCMISCS_WRITECFGCHACHB1_Spare_MAX                            (127) // 0x0000007F
  #define MCMISCS_WRITECFGCHACHB1_Spare_DEF                            (0x00000000)
  #define MCMISCS_WRITECFGCHACHB1_Spare_HSH                            (0x071930D0)

#define MCMISCS_READCFGCHACHB0_REG                                     (0x000030D4)

  #define MCMISCS_READCFGCHACHB0_RcvEnRank0ChADel_OFF                  ( 0)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank0ChADel_WID                  ( 3)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank0ChADel_MSK                  (0x00000007)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank0ChADel_MIN                  (0)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank0ChADel_MAX                  (7) // 0x00000007
  #define MCMISCS_READCFGCHACHB0_RcvEnRank0ChADel_DEF                  (0x00000000)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank0ChADel_HSH                  (0x030030D4)

  #define MCMISCS_READCFGCHACHB0_RcvEnRank1ChADel_OFF                  ( 3)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank1ChADel_WID                  ( 3)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank1ChADel_MSK                  (0x00000038)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank1ChADel_MIN                  (0)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank1ChADel_MAX                  (7) // 0x00000007
  #define MCMISCS_READCFGCHACHB0_RcvEnRank1ChADel_DEF                  (0x00000000)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank1ChADel_HSH                  (0x030330D4)

  #define MCMISCS_READCFGCHACHB0_RcvEnRank2ChADel_OFF                  ( 6)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank2ChADel_WID                  ( 3)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank2ChADel_MSK                  (0x000001C0)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank2ChADel_MIN                  (0)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank2ChADel_MAX                  (7) // 0x00000007
  #define MCMISCS_READCFGCHACHB0_RcvEnRank2ChADel_DEF                  (0x00000000)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank2ChADel_HSH                  (0x030630D4)

  #define MCMISCS_READCFGCHACHB0_RcvEnRank3ChADel_OFF                  ( 9)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank3ChADel_WID                  ( 3)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank3ChADel_MSK                  (0x00000E00)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank3ChADel_MIN                  (0)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank3ChADel_MAX                  (7) // 0x00000007
  #define MCMISCS_READCFGCHACHB0_RcvEnRank3ChADel_DEF                  (0x00000000)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank3ChADel_HSH                  (0x030930D4)

  #define MCMISCS_READCFGCHACHB0_RcvEnRank0ChBDel_OFF                  (12)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank0ChBDel_WID                  ( 3)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank0ChBDel_MSK                  (0x00007000)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank0ChBDel_MIN                  (0)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank0ChBDel_MAX                  (7) // 0x00000007
  #define MCMISCS_READCFGCHACHB0_RcvEnRank0ChBDel_DEF                  (0x00000000)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank0ChBDel_HSH                  (0x030C30D4)

  #define MCMISCS_READCFGCHACHB0_RcvEnRank1ChBDel_OFF                  (15)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank1ChBDel_WID                  ( 3)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank1ChBDel_MSK                  (0x00038000)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank1ChBDel_MIN                  (0)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank1ChBDel_MAX                  (7) // 0x00000007
  #define MCMISCS_READCFGCHACHB0_RcvEnRank1ChBDel_DEF                  (0x00000000)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank1ChBDel_HSH                  (0x030F30D4)

  #define MCMISCS_READCFGCHACHB0_RcvEnRank2ChBDel_OFF                  (18)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank2ChBDel_WID                  ( 3)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank2ChBDel_MSK                  (0x001C0000)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank2ChBDel_MIN                  (0)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank2ChBDel_MAX                  (7) // 0x00000007
  #define MCMISCS_READCFGCHACHB0_RcvEnRank2ChBDel_DEF                  (0x00000000)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank2ChBDel_HSH                  (0x031230D4)

  #define MCMISCS_READCFGCHACHB0_RcvEnRank3ChBDel_OFF                  (21)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank3ChBDel_WID                  ( 3)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank3ChBDel_MSK                  (0x00E00000)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank3ChBDel_MIN                  (0)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank3ChBDel_MAX                  (7) // 0x00000007
  #define MCMISCS_READCFGCHACHB0_RcvEnRank3ChBDel_DEF                  (0x00000000)
  #define MCMISCS_READCFGCHACHB0_RcvEnRank3ChBDel_HSH                  (0x031530D4)

  #define MCMISCS_READCFGCHACHB0_rx_analog_clk_gate_dis_OFF            (24)
  #define MCMISCS_READCFGCHACHB0_rx_analog_clk_gate_dis_WID            ( 1)
  #define MCMISCS_READCFGCHACHB0_rx_analog_clk_gate_dis_MSK            (0x01000000)
  #define MCMISCS_READCFGCHACHB0_rx_analog_clk_gate_dis_MIN            (0)
  #define MCMISCS_READCFGCHACHB0_rx_analog_clk_gate_dis_MAX            (1) // 0x00000001
  #define MCMISCS_READCFGCHACHB0_rx_analog_clk_gate_dis_DEF            (0x00000000)
  #define MCMISCS_READCFGCHACHB0_rx_analog_clk_gate_dis_HSH            (0x011830D4)

  #define MCMISCS_READCFGCHACHB0_Spare_OFF                             (25)
  #define MCMISCS_READCFGCHACHB0_Spare_WID                             ( 7)
  #define MCMISCS_READCFGCHACHB0_Spare_MSK                             (0xFE000000)
  #define MCMISCS_READCFGCHACHB0_Spare_MIN                             (0)
  #define MCMISCS_READCFGCHACHB0_Spare_MAX                             (127) // 0x0000007F
  #define MCMISCS_READCFGCHACHB0_Spare_DEF                             (0x00000000)
  #define MCMISCS_READCFGCHACHB0_Spare_HSH                             (0x071930D4)

#define MCMISCS_READCFGCHACHB1_REG                                     (0x000030D8)

  #define MCMISCS_READCFGCHACHB1_RcvEnRank0ChADel_OFF                  ( 0)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank0ChADel_WID                  ( 3)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank0ChADel_MSK                  (0x00000007)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank0ChADel_MIN                  (0)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank0ChADel_MAX                  (7) // 0x00000007
  #define MCMISCS_READCFGCHACHB1_RcvEnRank0ChADel_DEF                  (0x00000000)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank0ChADel_HSH                  (0x030030D8)

  #define MCMISCS_READCFGCHACHB1_RcvEnRank1ChADel_OFF                  ( 3)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank1ChADel_WID                  ( 3)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank1ChADel_MSK                  (0x00000038)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank1ChADel_MIN                  (0)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank1ChADel_MAX                  (7) // 0x00000007
  #define MCMISCS_READCFGCHACHB1_RcvEnRank1ChADel_DEF                  (0x00000000)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank1ChADel_HSH                  (0x030330D8)

  #define MCMISCS_READCFGCHACHB1_RcvEnRank2ChADel_OFF                  ( 6)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank2ChADel_WID                  ( 3)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank2ChADel_MSK                  (0x000001C0)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank2ChADel_MIN                  (0)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank2ChADel_MAX                  (7) // 0x00000007
  #define MCMISCS_READCFGCHACHB1_RcvEnRank2ChADel_DEF                  (0x00000000)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank2ChADel_HSH                  (0x030630D8)

  #define MCMISCS_READCFGCHACHB1_RcvEnRank3ChADel_OFF                  ( 9)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank3ChADel_WID                  ( 3)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank3ChADel_MSK                  (0x00000E00)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank3ChADel_MIN                  (0)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank3ChADel_MAX                  (7) // 0x00000007
  #define MCMISCS_READCFGCHACHB1_RcvEnRank3ChADel_DEF                  (0x00000000)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank3ChADel_HSH                  (0x030930D8)

  #define MCMISCS_READCFGCHACHB1_RcvEnRank0ChBDel_OFF                  (12)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank0ChBDel_WID                  ( 3)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank0ChBDel_MSK                  (0x00007000)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank0ChBDel_MIN                  (0)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank0ChBDel_MAX                  (7) // 0x00000007
  #define MCMISCS_READCFGCHACHB1_RcvEnRank0ChBDel_DEF                  (0x00000000)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank0ChBDel_HSH                  (0x030C30D8)

  #define MCMISCS_READCFGCHACHB1_RcvEnRank1ChBDel_OFF                  (15)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank1ChBDel_WID                  ( 3)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank1ChBDel_MSK                  (0x00038000)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank1ChBDel_MIN                  (0)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank1ChBDel_MAX                  (7) // 0x00000007
  #define MCMISCS_READCFGCHACHB1_RcvEnRank1ChBDel_DEF                  (0x00000000)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank1ChBDel_HSH                  (0x030F30D8)

  #define MCMISCS_READCFGCHACHB1_RcvEnRank2ChBDel_OFF                  (18)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank2ChBDel_WID                  ( 3)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank2ChBDel_MSK                  (0x001C0000)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank2ChBDel_MIN                  (0)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank2ChBDel_MAX                  (7) // 0x00000007
  #define MCMISCS_READCFGCHACHB1_RcvEnRank2ChBDel_DEF                  (0x00000000)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank2ChBDel_HSH                  (0x031230D8)

  #define MCMISCS_READCFGCHACHB1_RcvEnRank3ChBDel_OFF                  (21)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank3ChBDel_WID                  ( 3)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank3ChBDel_MSK                  (0x00E00000)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank3ChBDel_MIN                  (0)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank3ChBDel_MAX                  (7) // 0x00000007
  #define MCMISCS_READCFGCHACHB1_RcvEnRank3ChBDel_DEF                  (0x00000000)
  #define MCMISCS_READCFGCHACHB1_RcvEnRank3ChBDel_HSH                  (0x031530D8)

  #define MCMISCS_READCFGCHACHB1_rx_analog_clk_gate_dis_OFF            (24)
  #define MCMISCS_READCFGCHACHB1_rx_analog_clk_gate_dis_WID            ( 1)
  #define MCMISCS_READCFGCHACHB1_rx_analog_clk_gate_dis_MSK            (0x01000000)
  #define MCMISCS_READCFGCHACHB1_rx_analog_clk_gate_dis_MIN            (0)
  #define MCMISCS_READCFGCHACHB1_rx_analog_clk_gate_dis_MAX            (1) // 0x00000001
  #define MCMISCS_READCFGCHACHB1_rx_analog_clk_gate_dis_DEF            (0x00000000)
  #define MCMISCS_READCFGCHACHB1_rx_analog_clk_gate_dis_HSH            (0x011830D8)

  #define MCMISCS_READCFGCHACHB1_Spare_OFF                             (25)
  #define MCMISCS_READCFGCHACHB1_Spare_WID                             ( 7)
  #define MCMISCS_READCFGCHACHB1_Spare_MSK                             (0xFE000000)
  #define MCMISCS_READCFGCHACHB1_Spare_MIN                             (0)
  #define MCMISCS_READCFGCHACHB1_Spare_MAX                             (127) // 0x0000007F
  #define MCMISCS_READCFGCHACHB1_Spare_DEF                             (0x00000000)
  #define MCMISCS_READCFGCHACHB1_Spare_HSH                             (0x071930D8)

#define DDRSCRAM_CR_DDRMISCCONTROL5_REG                                (0x000030DC)

  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_odt2_OFF            ( 0)
  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_odt2_WID            ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_odt2_MSK            (0x0000000F)
  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_odt2_MIN            (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_odt2_MAX            (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_odt2_DEF            (0x00000006)
  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_odt2_HSH            (0x040030DC)

  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_odt3_OFF            ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_odt3_WID            ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_odt3_MSK            (0x000000F0)
  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_odt3_MIN            (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_odt3_MAX            (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_odt3_DEF            (0x00000007)
  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_odt3_HSH            (0x040430DC)

  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_cs4_OFF             ( 8)
  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_cs4_WID             ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_cs4_MSK             (0x00000F00)
  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_cs4_MIN             (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_cs4_MAX             (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_cs4_DEF             (0x00000008)
  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_cs4_HSH             (0x040830DC)

  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_cs5_OFF             (12)
  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_cs5_WID             ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_cs5_MSK             (0x0000F000)
  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_cs5_MIN             (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_cs5_MAX             (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_cs5_DEF             (0x00000009)
  #define DDRSCRAM_CR_DDRMISCCONTROL5_CsOdtMapping_cs5_HSH             (0x040C30DC)

  #define DDRSCRAM_CR_DDRMISCCONTROL5_spare_OFF                        (16)
  #define DDRSCRAM_CR_DDRMISCCONTROL5_spare_WID                        (16)
  #define DDRSCRAM_CR_DDRMISCCONTROL5_spare_MSK                        (0xFFFF0000)
  #define DDRSCRAM_CR_DDRMISCCONTROL5_spare_MIN                        (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL5_spare_MAX                        (65535) // 0x0000FFFF
  #define DDRSCRAM_CR_DDRMISCCONTROL5_spare_DEF                        (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL5_spare_HSH                        (0x101030DC)

#define DDRSCRAM_CR_DDRMISCCONTROL6_REG                                (0x000030E0)

  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_odt2_OFF            ( 0)
  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_odt2_WID            ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_odt2_MSK            (0x0000000F)
  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_odt2_MIN            (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_odt2_MAX            (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_odt2_DEF            (0x00000006)
  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_odt2_HSH            (0x040030E0)

  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_odt3_OFF            ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_odt3_WID            ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_odt3_MSK            (0x000000F0)
  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_odt3_MIN            (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_odt3_MAX            (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_odt3_DEF            (0x00000007)
  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_odt3_HSH            (0x040430E0)

  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_cs4_OFF             ( 8)
  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_cs4_WID             ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_cs4_MSK             (0x00000F00)
  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_cs4_MIN             (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_cs4_MAX             (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_cs4_DEF             (0x00000008)
  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_cs4_HSH             (0x040830E0)

  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_cs5_OFF             (12)
  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_cs5_WID             ( 4)
  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_cs5_MSK             (0x0000F000)
  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_cs5_MIN             (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_cs5_MAX             (15) // 0x0000000F
  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_cs5_DEF             (0x00000009)
  #define DDRSCRAM_CR_DDRMISCCONTROL6_CsOdtMapping_cs5_HSH             (0x040C30E0)

  #define DDRSCRAM_CR_DDRMISCCONTROL6_spare_OFF                        (16)
  #define DDRSCRAM_CR_DDRMISCCONTROL6_spare_WID                        (16)
  #define DDRSCRAM_CR_DDRMISCCONTROL6_spare_MSK                        (0xFFFF0000)
  #define DDRSCRAM_CR_DDRMISCCONTROL6_spare_MIN                        (0)
  #define DDRSCRAM_CR_DDRMISCCONTROL6_spare_MAX                        (65535) // 0x0000FFFF
  #define DDRSCRAM_CR_DDRMISCCONTROL6_spare_DEF                        (0x00000000)
  #define DDRSCRAM_CR_DDRMISCCONTROL6_spare_HSH                        (0x101030E0)

#define MCMISCS_SYNAUTOTRDYSTART_REG                                   (0x000030E4)

  #define MCMISCS_SYNAUTOTRDYSTART_ForceAutoTrdy_OFF                   ( 0)
  #define MCMISCS_SYNAUTOTRDYSTART_ForceAutoTrdy_WID                   ( 1)
  #define MCMISCS_SYNAUTOTRDYSTART_ForceAutoTrdy_MSK                   (0x00000001)
  #define MCMISCS_SYNAUTOTRDYSTART_ForceAutoTrdy_MIN                   (0)
  #define MCMISCS_SYNAUTOTRDYSTART_ForceAutoTrdy_MAX                   (1) // 0x00000001
  #define MCMISCS_SYNAUTOTRDYSTART_ForceAutoTrdy_DEF                   (0x00000000)
  #define MCMISCS_SYNAUTOTRDYSTART_ForceAutoTrdy_HSH                   (0x010030E4)

  #define MCMISCS_SYNAUTOTRDYSTART_Spare_OFF                           ( 1)
  #define MCMISCS_SYNAUTOTRDYSTART_Spare_WID                           (31)
  #define MCMISCS_SYNAUTOTRDYSTART_Spare_MSK                           (0xFFFFFFFE)
  #define MCMISCS_SYNAUTOTRDYSTART_Spare_MIN                           (0)
  #define MCMISCS_SYNAUTOTRDYSTART_Spare_MAX                           (2147483647) // 0x7FFFFFFF
  #define MCMISCS_SYNAUTOTRDYSTART_Spare_DEF                           (0x00000000)
  #define MCMISCS_SYNAUTOTRDYSTART_Spare_HSH                           (0x1F0130E4)

#define MCMISCS_SYNAUTOTRDYEND_REG                                     (0x000030E8)

  #define MCMISCS_SYNAUTOTRDYEND_DisableAutoTrdy_OFF                   ( 0)
  #define MCMISCS_SYNAUTOTRDYEND_DisableAutoTrdy_WID                   ( 1)
  #define MCMISCS_SYNAUTOTRDYEND_DisableAutoTrdy_MSK                   (0x00000001)
  #define MCMISCS_SYNAUTOTRDYEND_DisableAutoTrdy_MIN                   (0)
  #define MCMISCS_SYNAUTOTRDYEND_DisableAutoTrdy_MAX                   (1) // 0x00000001
  #define MCMISCS_SYNAUTOTRDYEND_DisableAutoTrdy_DEF                   (0x00000000)
  #define MCMISCS_SYNAUTOTRDYEND_DisableAutoTrdy_HSH                   (0x010030E8)

  #define MCMISCS_SYNAUTOTRDYEND_Spare_OFF                             ( 1)
  #define MCMISCS_SYNAUTOTRDYEND_Spare_WID                             (31)
  #define MCMISCS_SYNAUTOTRDYEND_Spare_MSK                             (0xFFFFFFFE)
  #define MCMISCS_SYNAUTOTRDYEND_Spare_MIN                             (0)
  #define MCMISCS_SYNAUTOTRDYEND_Spare_MAX                             (2147483647) // 0x7FFFFFFF
  #define MCMISCS_SYNAUTOTRDYEND_Spare_DEF                             (0x00000000)
  #define MCMISCS_SYNAUTOTRDYEND_Spare_HSH                             (0x1F0130E8)

#define MCMISCS_RXDQFIFORDENCHACHB0_REG                                (0x000030EC)

  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank0ChADel_OFF      ( 0)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank0ChADel_WID      ( 4)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank0ChADel_MSK      (0x0000000F)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank0ChADel_MIN      (0)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank0ChADel_MAX      (15) // 0x0000000F
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank0ChADel_DEF      (0x00000000)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank0ChADel_HSH      (0x040030EC)

  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank1ChADel_OFF      ( 4)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank1ChADel_WID      ( 4)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank1ChADel_MSK      (0x000000F0)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank1ChADel_MIN      (0)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank1ChADel_MAX      (15) // 0x0000000F
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank1ChADel_DEF      (0x00000000)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank1ChADel_HSH      (0x040430EC)

  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank2ChADel_OFF      ( 8)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank2ChADel_WID      ( 4)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank2ChADel_MSK      (0x00000F00)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank2ChADel_MIN      (0)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank2ChADel_MAX      (15) // 0x0000000F
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank2ChADel_DEF      (0x00000000)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank2ChADel_HSH      (0x040830EC)

  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank3ChADel_OFF      (12)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank3ChADel_WID      ( 4)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank3ChADel_MSK      (0x0000F000)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank3ChADel_MIN      (0)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank3ChADel_MAX      (15) // 0x0000000F
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank3ChADel_DEF      (0x00000000)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank3ChADel_HSH      (0x040C30EC)

  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank0ChBDel_OFF      (16)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank0ChBDel_WID      ( 4)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank0ChBDel_MSK      (0x000F0000)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank0ChBDel_MIN      (0)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank0ChBDel_MAX      (15) // 0x0000000F
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank0ChBDel_DEF      (0x00000000)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank0ChBDel_HSH      (0x041030EC)

  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank1ChBDel_OFF      (20)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank1ChBDel_WID      ( 4)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank1ChBDel_MSK      (0x00F00000)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank1ChBDel_MIN      (0)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank1ChBDel_MAX      (15) // 0x0000000F
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank1ChBDel_DEF      (0x00000000)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank1ChBDel_HSH      (0x041430EC)

  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank2ChBDel_OFF      (24)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank2ChBDel_WID      ( 4)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank2ChBDel_MSK      (0x0F000000)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank2ChBDel_MIN      (0)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank2ChBDel_MAX      (15) // 0x0000000F
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank2ChBDel_DEF      (0x00000000)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank2ChBDel_HSH      (0x041830EC)

  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank3ChBDel_OFF      (28)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank3ChBDel_WID      ( 4)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank3ChBDel_MSK      (0xF0000000)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank3ChBDel_MIN      (0)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank3ChBDel_MAX      (15) // 0x0000000F
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank3ChBDel_DEF      (0x00000000)
  #define MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank3ChBDel_HSH      (0x041C30EC)

#define MCMISCS_RXDQFIFORDENCHACHB1_REG                                (0x000030F0)

  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank0ChADel_OFF      ( 0)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank0ChADel_WID      ( 4)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank0ChADel_MSK      (0x0000000F)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank0ChADel_MIN      (0)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank0ChADel_MAX      (15) // 0x0000000F
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank0ChADel_DEF      (0x00000000)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank0ChADel_HSH      (0x040030F0)

  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank1ChADel_OFF      ( 4)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank1ChADel_WID      ( 4)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank1ChADel_MSK      (0x000000F0)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank1ChADel_MIN      (0)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank1ChADel_MAX      (15) // 0x0000000F
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank1ChADel_DEF      (0x00000000)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank1ChADel_HSH      (0x040430F0)

  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank2ChADel_OFF      ( 8)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank2ChADel_WID      ( 4)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank2ChADel_MSK      (0x00000F00)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank2ChADel_MIN      (0)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank2ChADel_MAX      (15) // 0x0000000F
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank2ChADel_DEF      (0x00000000)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank2ChADel_HSH      (0x040830F0)

  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank3ChADel_OFF      (12)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank3ChADel_WID      ( 4)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank3ChADel_MSK      (0x0000F000)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank3ChADel_MIN      (0)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank3ChADel_MAX      (15) // 0x0000000F
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank3ChADel_DEF      (0x00000000)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank3ChADel_HSH      (0x040C30F0)

  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank0ChBDel_OFF      (16)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank0ChBDel_WID      ( 4)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank0ChBDel_MSK      (0x000F0000)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank0ChBDel_MIN      (0)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank0ChBDel_MAX      (15) // 0x0000000F
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank0ChBDel_DEF      (0x00000000)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank0ChBDel_HSH      (0x041030F0)

  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank1ChBDel_OFF      (20)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank1ChBDel_WID      ( 4)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank1ChBDel_MSK      (0x00F00000)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank1ChBDel_MIN      (0)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank1ChBDel_MAX      (15) // 0x0000000F
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank1ChBDel_DEF      (0x00000000)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank1ChBDel_HSH      (0x041430F0)

  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank2ChBDel_OFF      (24)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank2ChBDel_WID      ( 4)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank2ChBDel_MSK      (0x0F000000)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank2ChBDel_MIN      (0)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank2ChBDel_MAX      (15) // 0x0000000F
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank2ChBDel_DEF      (0x00000000)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank2ChBDel_HSH      (0x041830F0)

  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank3ChBDel_OFF      (28)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank3ChBDel_WID      ( 4)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank3ChBDel_MSK      (0xF0000000)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank3ChBDel_MIN      (0)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank3ChBDel_MAX      (15) // 0x0000000F
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank3ChBDel_DEF      (0x00000000)
  #define MCMISCS_RXDQFIFORDENCHACHB1_RxDqFifoRdEnRank3ChBDel_HSH      (0x041C30F0)

#define MCMISCS_DCCCONTROL0_REG                                        (0x000030F4)

  #define MCMISCS_DCCCONTROL0_Drain_OFF                                ( 0)
  #define MCMISCS_DCCCONTROL0_Drain_WID                                ( 1)
  #define MCMISCS_DCCCONTROL0_Drain_MSK                                (0x00000001)
  #define MCMISCS_DCCCONTROL0_Drain_MIN                                (0)
  #define MCMISCS_DCCCONTROL0_Drain_MAX                                (1) // 0x00000001
  #define MCMISCS_DCCCONTROL0_Drain_DEF                                (0x00000000)
  #define MCMISCS_DCCCONTROL0_Drain_HSH                                (0x010030F4)

  #define MCMISCS_DCCCONTROL0_Abort_OFF                                ( 1)
  #define MCMISCS_DCCCONTROL0_Abort_WID                                ( 1)
  #define MCMISCS_DCCCONTROL0_Abort_MSK                                (0x00000002)
  #define MCMISCS_DCCCONTROL0_Abort_MIN                                (0)
  #define MCMISCS_DCCCONTROL0_Abort_MAX                                (1) // 0x00000001
  #define MCMISCS_DCCCONTROL0_Abort_DEF                                (0x00000000)
  #define MCMISCS_DCCCONTROL0_Abort_HSH                                (0x010130F4)

  #define MCMISCS_DCCCONTROL0_TrainingMode_OFF                         ( 2)
  #define MCMISCS_DCCCONTROL0_TrainingMode_WID                         ( 1)
  #define MCMISCS_DCCCONTROL0_TrainingMode_MSK                         (0x00000004)
  #define MCMISCS_DCCCONTROL0_TrainingMode_MIN                         (0)
  #define MCMISCS_DCCCONTROL0_TrainingMode_MAX                         (1) // 0x00000001
  #define MCMISCS_DCCCONTROL0_TrainingMode_DEF                         (0x00000000)
  #define MCMISCS_DCCCONTROL0_TrainingMode_HSH                         (0x010230F4)

  #define MCMISCS_DCCCONTROL0_OverrideMode_OFF                         ( 3)
  #define MCMISCS_DCCCONTROL0_OverrideMode_WID                         ( 1)
  #define MCMISCS_DCCCONTROL0_OverrideMode_MSK                         (0x00000008)
  #define MCMISCS_DCCCONTROL0_OverrideMode_MIN                         (0)
  #define MCMISCS_DCCCONTROL0_OverrideMode_MAX                         (1) // 0x00000001
  #define MCMISCS_DCCCONTROL0_OverrideMode_DEF                         (0x00000000)
  #define MCMISCS_DCCCONTROL0_OverrideMode_HSH                         (0x010330F4)

  #define MCMISCS_DCCCONTROL0_GVPointG1_OFF                            ( 4)
  #define MCMISCS_DCCCONTROL0_GVPointG1_WID                            ( 1)
  #define MCMISCS_DCCCONTROL0_GVPointG1_MSK                            (0x00000010)
  #define MCMISCS_DCCCONTROL0_GVPointG1_MIN                            (0)
  #define MCMISCS_DCCCONTROL0_GVPointG1_MAX                            (1) // 0x00000001
  #define MCMISCS_DCCCONTROL0_GVPointG1_DEF                            (0x00000001)
  #define MCMISCS_DCCCONTROL0_GVPointG1_HSH                            (0x010430F4)

  #define MCMISCS_DCCCONTROL0_DllLockCntPeriod_OFF                     ( 5)
  #define MCMISCS_DCCCONTROL0_DllLockCntPeriod_WID                     (13)
  #define MCMISCS_DCCCONTROL0_DllLockCntPeriod_MSK                     (0x0003FFE0)
  #define MCMISCS_DCCCONTROL0_DllLockCntPeriod_MIN                     (0)
  #define MCMISCS_DCCCONTROL0_DllLockCntPeriod_MAX                     (8191) // 0x00001FFF
  #define MCMISCS_DCCCONTROL0_DllLockCntPeriod_DEF                     (0x0000003C)
  #define MCMISCS_DCCCONTROL0_DllLockCntPeriod_HSH                     (0x0D0530F4)

  #define MCMISCS_DCCCONTROL0_Spare1_OFF                               (18)
  #define MCMISCS_DCCCONTROL0_Spare1_WID                               ( 3)
  #define MCMISCS_DCCCONTROL0_Spare1_MSK                               (0x001C0000)
  #define MCMISCS_DCCCONTROL0_Spare1_MIN                               (0)
  #define MCMISCS_DCCCONTROL0_Spare1_MAX                               (7) // 0x00000007
  #define MCMISCS_DCCCONTROL0_Spare1_DEF                               (0x00000000)
  #define MCMISCS_DCCCONTROL0_Spare1_HSH                               (0x031230F4)

  #define MCMISCS_DCCCONTROL0_DccBubbleVal_OFF                         (21)
  #define MCMISCS_DCCCONTROL0_DccBubbleVal_WID                         ( 7)
  #define MCMISCS_DCCCONTROL0_DccBubbleVal_MSK                         (0x0FE00000)
  #define MCMISCS_DCCCONTROL0_DccBubbleVal_MIN                         (0)
  #define MCMISCS_DCCCONTROL0_DccBubbleVal_MAX                         (127) // 0x0000007F
  #define MCMISCS_DCCCONTROL0_DccBubbleVal_DEF                         (0x00000014)
  #define MCMISCS_DCCCONTROL0_DccBubbleVal_HSH                         (0x071530F4)

  #define MCMISCS_DCCCONTROL0_ClkGateDisable_OFF                       (28)
  #define MCMISCS_DCCCONTROL0_ClkGateDisable_WID                       ( 1)
  #define MCMISCS_DCCCONTROL0_ClkGateDisable_MSK                       (0x10000000)
  #define MCMISCS_DCCCONTROL0_ClkGateDisable_MIN                       (0)
  #define MCMISCS_DCCCONTROL0_ClkGateDisable_MAX                       (1) // 0x00000001
  #define MCMISCS_DCCCONTROL0_ClkGateDisable_DEF                       (0x00000000)
  #define MCMISCS_DCCCONTROL0_ClkGateDisable_HSH                       (0x011C30F4)

  #define MCMISCS_DCCCONTROL0_DisDrainEveryPllLock_OFF                 (29)
  #define MCMISCS_DCCCONTROL0_DisDrainEveryPllLock_WID                 ( 1)
  #define MCMISCS_DCCCONTROL0_DisDrainEveryPllLock_MSK                 (0x20000000)
  #define MCMISCS_DCCCONTROL0_DisDrainEveryPllLock_MIN                 (0)
  #define MCMISCS_DCCCONTROL0_DisDrainEveryPllLock_MAX                 (1) // 0x00000001
  #define MCMISCS_DCCCONTROL0_DisDrainEveryPllLock_DEF                 (0x00000000)
  #define MCMISCS_DCCCONTROL0_DisDrainEveryPllLock_HSH                 (0x011D30F4)

  #define MCMISCS_DCCCONTROL0_DcoLfsrDis_OFF                           (30)
  #define MCMISCS_DCCCONTROL0_DcoLfsrDis_WID                           ( 1)
  #define MCMISCS_DCCCONTROL0_DcoLfsrDis_MSK                           (0x40000000)
  #define MCMISCS_DCCCONTROL0_DcoLfsrDis_MIN                           (0)
  #define MCMISCS_DCCCONTROL0_DcoLfsrDis_MAX                           (1) // 0x00000001
  #define MCMISCS_DCCCONTROL0_DcoLfsrDis_DEF                           (0x00000001)
  #define MCMISCS_DCCCONTROL0_DcoLfsrDis_HSH                           (0x011E30F4)

  #define MCMISCS_DCCCONTROL0_TrainingDone_OFF                         (31)
  #define MCMISCS_DCCCONTROL0_TrainingDone_WID                         ( 1)
  #define MCMISCS_DCCCONTROL0_TrainingDone_MSK                         (0x80000000)
  #define MCMISCS_DCCCONTROL0_TrainingDone_MIN                         (0)
  #define MCMISCS_DCCCONTROL0_TrainingDone_MAX                         (1) // 0x00000001
  #define MCMISCS_DCCCONTROL0_TrainingDone_DEF                         (0x00000000)
  #define MCMISCS_DCCCONTROL0_TrainingDone_HSH                         (0x011F30F4)

#define MCMISCS_DCCMAINFSMCONTROL0_REG                                 (0x000030F8)

  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicDis_OFF                    ( 0)
  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicDis_WID                    ( 1)
  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicDis_MSK                    (0x00000001)
  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicDis_MIN                    (0)
  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicDis_MAX                    (1) // 0x00000001
  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicDis_DEF                    (0x00000000)
  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicDis_HSH                    (0x010030F8)

  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicForce_OFF                  ( 1)
  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicForce_WID                  ( 1)
  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicForce_MSK                  (0x00000002)
  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicForce_MIN                  (0)
  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicForce_MAX                  (1) // 0x00000001
  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicForce_DEF                  (0x00000000)
  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicForce_HSH                  (0x010130F8)

  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicSrc_OFF                    ( 2)
  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicSrc_WID                    ( 1)
  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicSrc_MSK                    (0x00000004)
  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicSrc_MIN                    (0)
  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicSrc_MAX                    (1) // 0x00000001
  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicSrc_DEF                    (0x00000000)
  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicSrc_HSH                    (0x010230F8)

  #define MCMISCS_DCCMAINFSMCONTROL0_DcoCompEn_OFF                     ( 3)
  #define MCMISCS_DCCMAINFSMCONTROL0_DcoCompEn_WID                     ( 1)
  #define MCMISCS_DCCMAINFSMCONTROL0_DcoCompEn_MSK                     (0x00000008)
  #define MCMISCS_DCCMAINFSMCONTROL0_DcoCompEn_MIN                     (0)
  #define MCMISCS_DCCMAINFSMCONTROL0_DcoCompEn_MAX                     (1) // 0x00000001
  #define MCMISCS_DCCMAINFSMCONTROL0_DcoCompEn_DEF                     (0x00000001)
  #define MCMISCS_DCCMAINFSMCONTROL0_DcoCompEn_HSH                     (0x010330F8)

  #define MCMISCS_DCCMAINFSMCONTROL0_ActiveBytes_OFF                   ( 4)
  #define MCMISCS_DCCMAINFSMCONTROL0_ActiveBytes_WID                   (16)
  #define MCMISCS_DCCMAINFSMCONTROL0_ActiveBytes_MSK                   (0x000FFFF0)
  #define MCMISCS_DCCMAINFSMCONTROL0_ActiveBytes_MIN                   (0)
  #define MCMISCS_DCCMAINFSMCONTROL0_ActiveBytes_MAX                   (65535) // 0x0000FFFF
  #define MCMISCS_DCCMAINFSMCONTROL0_ActiveBytes_DEF                   (0x0000FFFF)
  #define MCMISCS_DCCMAINFSMCONTROL0_ActiveBytes_HSH                   (0x100430F8)

  #define MCMISCS_DCCMAINFSMCONTROL0_ActiveClks_OFF                    (20)
  #define MCMISCS_DCCMAINFSMCONTROL0_ActiveClks_WID                    ( 2)
  #define MCMISCS_DCCMAINFSMCONTROL0_ActiveClks_MSK                    (0x00300000)
  #define MCMISCS_DCCMAINFSMCONTROL0_ActiveClks_MIN                    (0)
  #define MCMISCS_DCCMAINFSMCONTROL0_ActiveClks_MAX                    (3) // 0x00000003
  #define MCMISCS_DCCMAINFSMCONTROL0_ActiveClks_DEF                    (0x00000003)
  #define MCMISCS_DCCMAINFSMCONTROL0_ActiveClks_HSH                    (0x021430F8)

  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicCntStartPortion_OFF        (22)
  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicCntStartPortion_WID        (10)
  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicCntStartPortion_MSK        (0xFFC00000)
  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicCntStartPortion_MIN        (0)
  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicCntStartPortion_MAX        (1023) // 0x000003FF
  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicCntStartPortion_DEF        (0x00000030)
  #define MCMISCS_DCCMAINFSMCONTROL0_PriodicCntStartPortion_HSH        (0x0A1630F8)

#define MCMISCS_DCCMAINFSMCONTROL1_REG                                 (0x000030FC)

  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntPeriod_OFF              ( 0)
  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntPeriod_WID              (29)
  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntPeriod_MSK              (0x1FFFFFFF)
  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntPeriod_MIN              (0)
  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntPeriod_MAX              (536870911) // 0x1FFFFFFF
  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntPeriod_DEF              (0x00010000)
  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntPeriod_HSH              (0x1D0030FC)

  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntEn_OFF                  (29)
  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntEn_WID                  ( 1)
  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntEn_MSK                  (0x20000000)
  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntEn_MIN                  (0)
  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntEn_MAX                  (1) // 0x00000001
  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntEn_DEF                  (0x00000000)
  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntEn_HSH                  (0x011D30FC)

  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntRst_OFF                 (30)
  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntRst_WID                 ( 1)
  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntRst_MSK                 (0x40000000)
  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntRst_MIN                 (0)
  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntRst_MAX                 (1) // 0x00000001
  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntRst_DEF                 (0x00000000)
  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntRst_HSH                 (0x011E30FC)

  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntIndOrd_OFF              (31)
  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntIndOrd_WID              ( 1)
  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntIndOrd_MSK              (0x80000000)
  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntIndOrd_MIN              (0)
  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntIndOrd_MAX              (1) // 0x00000001
  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntIndOrd_DEF              (0x00000000)
  #define MCMISCS_DCCMAINFSMCONTROL1_PriodicCntIndOrd_HSH              (0x011F30FC)

#define MCMISCS_DCCMAINFSMCONTROL2_REG                                 (0x00003100)

  #define MCMISCS_DCCMAINFSMCONTROL2_ActiveEccBytes_OFF                ( 0)
  #define MCMISCS_DCCMAINFSMCONTROL2_ActiveEccBytes_WID                ( 2)
  #define MCMISCS_DCCMAINFSMCONTROL2_ActiveEccBytes_MSK                (0x00000003)
  #define MCMISCS_DCCMAINFSMCONTROL2_ActiveEccBytes_MIN                (0)
  #define MCMISCS_DCCMAINFSMCONTROL2_ActiveEccBytes_MAX                (3) // 0x00000003
  #define MCMISCS_DCCMAINFSMCONTROL2_ActiveEccBytes_DEF                (0x00000000)
  #define MCMISCS_DCCMAINFSMCONTROL2_ActiveEccBytes_HSH                (0x02003100)

  #define MCMISCS_DCCMAINFSMCONTROL2_ActiveDtClks_OFF                  ( 2)
  #define MCMISCS_DCCMAINFSMCONTROL2_ActiveDtClks_WID                  ( 2)
  #define MCMISCS_DCCMAINFSMCONTROL2_ActiveDtClks_MSK                  (0x0000000C)
  #define MCMISCS_DCCMAINFSMCONTROL2_ActiveDtClks_MIN                  (0)
  #define MCMISCS_DCCMAINFSMCONTROL2_ActiveDtClks_MAX                  (3) // 0x00000003
  #define MCMISCS_DCCMAINFSMCONTROL2_ActiveDtClks_DEF                  (0x00000000)
  #define MCMISCS_DCCMAINFSMCONTROL2_ActiveDtClks_HSH                  (0x02023100)

  #define MCMISCS_DCCMAINFSMCONTROL2_Spare_OFF                         ( 4)
  #define MCMISCS_DCCMAINFSMCONTROL2_Spare_WID                         (28)
  #define MCMISCS_DCCMAINFSMCONTROL2_Spare_MSK                         (0xFFFFFFF0)
  #define MCMISCS_DCCMAINFSMCONTROL2_Spare_MIN                         (0)
  #define MCMISCS_DCCMAINFSMCONTROL2_Spare_MAX                         (268435455) // 0x0FFFFFFF
  #define MCMISCS_DCCMAINFSMCONTROL2_Spare_DEF                         (0x00000000)
  #define MCMISCS_DCCMAINFSMCONTROL2_Spare_HSH                         (0x1C043100)

#define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_REG                         (0x00003104)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane0_HSH        (0x03003104)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane1_HSH        (0x03033104)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane2_HSH        (0x03063104)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane3_HSH        (0x03093104)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane4_HSH        (0x030C3104)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane5_HSH        (0x030F3104)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane6_HSH        (0x03123104)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleLane7_HSH        (0x03153104)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_DeSwizzleByte_HSH         (0x02183104)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_Spare_HSH                 (0x041A3104)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_HSH (0x011E3104)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_HSH (0x011F3104)

#define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_REG                         (0x00003108)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane0_HSH        (0x03003108)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane1_HSH        (0x03033108)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane2_HSH        (0x03063108)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane3_HSH        (0x03093108)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane4_HSH        (0x030C3108)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane5_HSH        (0x030F3108)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane6_HSH        (0x03123108)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleLane7_HSH        (0x03153108)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_DeSwizzleByte_HSH         (0x02183108)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_Spare_HSH                 (0x041A3108)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_HSH (0x011E3108)

  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_HSH (0x011F3108)

#define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_REG                         (0x0000310C)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane0_HSH        (0x0300310C)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane1_HSH        (0x0303310C)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane2_HSH        (0x0306310C)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane3_HSH        (0x0309310C)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane4_HSH        (0x030C310C)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane5_HSH        (0x030F310C)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane6_HSH        (0x0312310C)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleLane7_HSH        (0x0315310C)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_DeSwizzleByte_HSH         (0x0218310C)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_Spare_HSH                 (0x041A310C)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_HSH (0x011E310C)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_HSH (0x011F310C)

#define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_REG                         (0x00003110)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane0_HSH        (0x03003110)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane1_HSH        (0x03033110)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane2_HSH        (0x03063110)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane3_HSH        (0x03093110)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane4_HSH        (0x030C3110)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane5_HSH        (0x030F3110)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane6_HSH        (0x03123110)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleLane7_HSH        (0x03153110)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_DeSwizzleByte_HSH         (0x02183110)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_Spare_HSH                 (0x041A3110)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_HSH (0x011E3110)

  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH0RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_HSH (0x011F3110)

#define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_REG                         (0x00003114)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane0_HSH        (0x03003114)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane1_HSH        (0x03033114)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane2_HSH        (0x03063114)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane3_HSH        (0x03093114)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane4_HSH        (0x030C3114)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane5_HSH        (0x030F3114)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane6_HSH        (0x03123114)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleLane7_HSH        (0x03153114)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_DeSwizzleByte_HSH         (0x02183114)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_Spare_HSH                 (0x041A3114)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_HSH (0x011E3114)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_HSH (0x011F3114)

#define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_REG                         (0x00003118)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane0_HSH        (0x03003118)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane1_HSH        (0x03033118)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane2_HSH        (0x03063118)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane3_HSH        (0x03093118)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane4_HSH        (0x030C3118)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane5_HSH        (0x030F3118)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane6_HSH        (0x03123118)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleLane7_HSH        (0x03153118)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_DeSwizzleByte_HSH         (0x02183118)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_Spare_HSH                 (0x041A3118)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_HSH (0x011E3118)

  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_HSH (0x011F3118)

#define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_REG                         (0x0000311C)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane0_HSH        (0x0300311C)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane1_HSH        (0x0303311C)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane2_HSH        (0x0306311C)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane3_HSH        (0x0309311C)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane4_HSH        (0x030C311C)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane5_HSH        (0x030F311C)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane6_HSH        (0x0312311C)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleLane7_HSH        (0x0315311C)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_DeSwizzleByte_HSH         (0x0218311C)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_Spare_HSH                 (0x041A311C)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_HSH (0x011E311C)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_HSH (0x011F311C)

#define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_REG                         (0x00003120)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane0_HSH        (0x03003120)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane1_HSH        (0x03033120)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane2_HSH        (0x03063120)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane3_HSH        (0x03093120)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane4_HSH        (0x030C3120)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane5_HSH        (0x030F3120)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane6_HSH        (0x03123120)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleLane7_HSH        (0x03153120)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_DeSwizzleByte_HSH         (0x02183120)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_Spare_HSH                 (0x041A3120)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_HSH (0x011E3120)

  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH1RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_HSH (0x011F3120)

#define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_REG                         (0x00003124)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane0_HSH        (0x03003124)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane1_HSH        (0x03033124)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane2_HSH        (0x03063124)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane3_HSH        (0x03093124)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane4_HSH        (0x030C3124)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane5_HSH        (0x030F3124)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane6_HSH        (0x03123124)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleLane7_HSH        (0x03153124)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_DeSwizzleByte_HSH         (0x02183124)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_Spare_HSH                 (0x041A3124)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_HSH (0x011E3124)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_HSH (0x011F3124)

#define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_REG                         (0x00003128)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane0_HSH        (0x03003128)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane1_HSH        (0x03033128)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane2_HSH        (0x03063128)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane3_HSH        (0x03093128)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane4_HSH        (0x030C3128)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane5_HSH        (0x030F3128)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane6_HSH        (0x03123128)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleLane7_HSH        (0x03153128)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_DeSwizzleByte_HSH         (0x02183128)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_Spare_HSH                 (0x041A3128)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_HSH (0x011E3128)

  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_HSH (0x011F3128)

#define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_REG                         (0x0000312C)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane0_HSH        (0x0300312C)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane1_HSH        (0x0303312C)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane2_HSH        (0x0306312C)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane3_HSH        (0x0309312C)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane4_HSH        (0x030C312C)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane5_HSH        (0x030F312C)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane6_HSH        (0x0312312C)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleLane7_HSH        (0x0315312C)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_DeSwizzleByte_HSH         (0x0218312C)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_Spare_HSH                 (0x041A312C)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_HSH (0x011E312C)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_HSH (0x011F312C)

#define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_REG                         (0x00003130)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane0_HSH        (0x03003130)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane1_HSH        (0x03033130)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane2_HSH        (0x03063130)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane3_HSH        (0x03093130)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane4_HSH        (0x030C3130)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane5_HSH        (0x030F3130)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane6_HSH        (0x03123130)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleLane7_HSH        (0x03153130)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_DeSwizzleByte_HSH         (0x02183130)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_Spare_HSH                 (0x041A3130)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_HSH (0x011E3130)

  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH2RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_HSH (0x011F3130)

#define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_REG                         (0x00003134)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane0_HSH        (0x03003134)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane1_HSH        (0x03033134)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane2_HSH        (0x03063134)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane3_HSH        (0x03093134)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane4_HSH        (0x030C3134)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane5_HSH        (0x030F3134)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane6_HSH        (0x03123134)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleLane7_HSH        (0x03153134)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_DeSwizzleByte_HSH         (0x02183134)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_Spare_HSH                 (0x041A3134)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_LP4_calc_in_progres_Override_Val_HSH (0x011E3134)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV2_LP4_calc_in_progres_Override_En_HSH (0x011F3134)

#define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_REG                         (0x00003138)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane0_HSH        (0x03003138)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane1_HSH        (0x03033138)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane2_HSH        (0x03063138)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane3_HSH        (0x03093138)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane4_HSH        (0x030C3138)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane5_HSH        (0x030F3138)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane6_HSH        (0x03123138)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleLane7_HSH        (0x03153138)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_DeSwizzleByte_HSH         (0x02183138)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_Spare_HSH                 (0x041A3138)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_LP4_calc_in_progres_Override_Val_HSH (0x011E3138)

  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR01DEV3_LP4_calc_in_progres_Override_En_HSH (0x011F3138)

#define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_REG                         (0x0000313C)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane0_HSH        (0x0300313C)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane1_HSH        (0x0303313C)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane2_HSH        (0x0306313C)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane3_HSH        (0x0309313C)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane4_HSH        (0x030C313C)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane5_HSH        (0x030F313C)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane6_HSH        (0x0312313C)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleLane7_HSH        (0x0315313C)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_DeSwizzleByte_HSH         (0x0218313C)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_Spare_HSH                 (0x041A313C)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_LP4_calc_in_progres_Override_Val_HSH (0x011E313C)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV2_LP4_calc_in_progres_Override_En_HSH (0x011F313C)

#define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_REG                         (0x00003140)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane0_OFF        ( 0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane0_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane0_MSK        (0x00000007)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane0_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane0_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane0_DEF        (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane0_HSH        (0x03003140)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane1_OFF        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane1_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane1_MSK        (0x00000038)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane1_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane1_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane1_DEF        (0x00000001)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane1_HSH        (0x03033140)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane2_OFF        ( 6)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane2_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane2_MSK        (0x000001C0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane2_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane2_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane2_DEF        (0x00000002)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane2_HSH        (0x03063140)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane3_OFF        ( 9)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane3_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane3_MSK        (0x00000E00)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane3_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane3_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane3_DEF        (0x00000003)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane3_HSH        (0x03093140)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane4_OFF        (12)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane4_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane4_MSK        (0x00007000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane4_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane4_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane4_DEF        (0x00000004)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane4_HSH        (0x030C3140)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane5_OFF        (15)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane5_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane5_MSK        (0x00038000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane5_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane5_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane5_DEF        (0x00000005)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane5_HSH        (0x030F3140)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane6_OFF        (18)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane6_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane6_MSK        (0x001C0000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane6_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane6_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane6_DEF        (0x00000006)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane6_HSH        (0x03123140)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane7_OFF        (21)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane7_WID        ( 3)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane7_MSK        (0x00E00000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane7_MIN        (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane7_MAX        (7) // 0x00000007
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane7_DEF        (0x00000007)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleLane7_HSH        (0x03153140)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleByte_OFF         (24)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleByte_WID         ( 2)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleByte_MSK         (0x03000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleByte_MIN         (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleByte_MAX         (3) // 0x00000003
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleByte_DEF         (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_DeSwizzleByte_HSH         (0x02183140)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_Spare_OFF                 (26)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_Spare_WID                 ( 4)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_Spare_MSK                 (0x3C000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_Spare_MIN                 (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_Spare_MAX                 (15) // 0x0000000F
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_Spare_DEF                 (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_Spare_HSH                 (0x041A3140)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_OFF (30)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_WID ( 1)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_MSK (0x40000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_MIN (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_LP4_calc_in_progres_Override_Val_HSH (0x011E3140)

  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_OFF (31)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_WID ( 1)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_MSK (0x80000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_MIN (0)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_MAX (1) // 0x00000001
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_DEF (0x00000000)
  #define MCMISCS_DESWIZZLECH3RANKPAIR23DEV3_LP4_calc_in_progres_Override_En_HSH (0x011F3140)

#define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_REG                         (0x00003144)

  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_ROCountTrainChannel0Rank0Dev0_OFF ( 0)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_ROCountTrainChannel0Rank0Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_ROCountTrainChannel0Rank0Dev0_MSK (0x000001FF)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_ROCountTrainChannel0Rank0Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_ROCountTrainChannel0Rank0Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_ROCountTrainChannel0Rank0Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_ROCountTrainChannel0Rank0Dev0_HSH (0x09003144)

  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_ROCountTrainChannel0Rank1Dev0_OFF ( 9)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_ROCountTrainChannel0Rank1Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_ROCountTrainChannel0Rank1Dev0_MSK (0x0003FE00)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_ROCountTrainChannel0Rank1Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_ROCountTrainChannel0Rank1Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_ROCountTrainChannel0Rank1Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_ROCountTrainChannel0Rank1Dev0_HSH (0x09093144)

  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_ROCountTrainChannel0Rank2Dev0_OFF (18)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_ROCountTrainChannel0Rank2Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_ROCountTrainChannel0Rank2Dev0_MSK (0x07FC0000)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_ROCountTrainChannel0Rank2Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_ROCountTrainChannel0Rank2Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_ROCountTrainChannel0Rank2Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_ROCountTrainChannel0Rank2Dev0_HSH (0x09123144)

  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_Spare_OFF                 (27)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_Spare_WID                 ( 5)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_Spare_MSK                 (0xF8000000)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_Spare_MIN                 (0)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_Spare_MAX                 (31) // 0x0000001F
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_Spare_DEF                 (0x00000000)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV2_Spare_HSH                 (0x051B3144)

#define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_REG                         (0x00003148)

  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_ROCountTrainChannel0Rank0Dev1_OFF ( 0)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_ROCountTrainChannel0Rank0Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_ROCountTrainChannel0Rank0Dev1_MSK (0x000001FF)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_ROCountTrainChannel0Rank0Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_ROCountTrainChannel0Rank0Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_ROCountTrainChannel0Rank0Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_ROCountTrainChannel0Rank0Dev1_HSH (0x09003148)

  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_ROCountTrainChannel0Rank1Dev1_OFF ( 9)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_ROCountTrainChannel0Rank1Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_ROCountTrainChannel0Rank1Dev1_MSK (0x0003FE00)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_ROCountTrainChannel0Rank1Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_ROCountTrainChannel0Rank1Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_ROCountTrainChannel0Rank1Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_ROCountTrainChannel0Rank1Dev1_HSH (0x09093148)

  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_ROCountTrainChannel0Rank2Dev1_OFF (18)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_ROCountTrainChannel0Rank2Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_ROCountTrainChannel0Rank2Dev1_MSK (0x07FC0000)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_ROCountTrainChannel0Rank2Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_ROCountTrainChannel0Rank2Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_ROCountTrainChannel0Rank2Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_ROCountTrainChannel0Rank2Dev1_HSH (0x09123148)

  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_Spare_OFF                 (27)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_Spare_WID                 ( 5)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_Spare_MSK                 (0xF8000000)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_Spare_MIN                 (0)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_Spare_MAX                 (31) // 0x0000001F
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_Spare_DEF                 (0x00000000)
  #define MCMISCS_ROCOUNTTRAINCH0RANK012DEV3_Spare_HSH                 (0x051B3148)

#define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_REG                         (0x0000314C)

  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_ROCountTrainChannel1Rank0Dev0_OFF ( 0)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_ROCountTrainChannel1Rank0Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_ROCountTrainChannel1Rank0Dev0_MSK (0x000001FF)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_ROCountTrainChannel1Rank0Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_ROCountTrainChannel1Rank0Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_ROCountTrainChannel1Rank0Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_ROCountTrainChannel1Rank0Dev0_HSH (0x0900314C)

  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_ROCountTrainChannel1Rank1Dev0_OFF ( 9)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_ROCountTrainChannel1Rank1Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_ROCountTrainChannel1Rank1Dev0_MSK (0x0003FE00)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_ROCountTrainChannel1Rank1Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_ROCountTrainChannel1Rank1Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_ROCountTrainChannel1Rank1Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_ROCountTrainChannel1Rank1Dev0_HSH (0x0909314C)

  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_ROCountTrainChannel1Rank2Dev0_OFF (18)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_ROCountTrainChannel1Rank2Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_ROCountTrainChannel1Rank2Dev0_MSK (0x07FC0000)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_ROCountTrainChannel1Rank2Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_ROCountTrainChannel1Rank2Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_ROCountTrainChannel1Rank2Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_ROCountTrainChannel1Rank2Dev0_HSH (0x0912314C)

  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_Spare_OFF                 (27)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_Spare_WID                 ( 5)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_Spare_MSK                 (0xF8000000)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_Spare_MIN                 (0)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_Spare_MAX                 (31) // 0x0000001F
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_Spare_DEF                 (0x00000000)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV2_Spare_HSH                 (0x051B314C)

#define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_REG                         (0x00003150)

  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_ROCountTrainChannel1Rank0Dev1_OFF ( 0)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_ROCountTrainChannel1Rank0Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_ROCountTrainChannel1Rank0Dev1_MSK (0x000001FF)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_ROCountTrainChannel1Rank0Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_ROCountTrainChannel1Rank0Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_ROCountTrainChannel1Rank0Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_ROCountTrainChannel1Rank0Dev1_HSH (0x09003150)

  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_ROCountTrainChannel1Rank1Dev1_OFF ( 9)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_ROCountTrainChannel1Rank1Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_ROCountTrainChannel1Rank1Dev1_MSK (0x0003FE00)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_ROCountTrainChannel1Rank1Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_ROCountTrainChannel1Rank1Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_ROCountTrainChannel1Rank1Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_ROCountTrainChannel1Rank1Dev1_HSH (0x09093150)

  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_ROCountTrainChannel1Rank2Dev1_OFF (18)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_ROCountTrainChannel1Rank2Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_ROCountTrainChannel1Rank2Dev1_MSK (0x07FC0000)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_ROCountTrainChannel1Rank2Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_ROCountTrainChannel1Rank2Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_ROCountTrainChannel1Rank2Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_ROCountTrainChannel1Rank2Dev1_HSH (0x09123150)

  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_Spare_OFF                 (27)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_Spare_WID                 ( 5)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_Spare_MSK                 (0xF8000000)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_Spare_MIN                 (0)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_Spare_MAX                 (31) // 0x0000001F
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_Spare_DEF                 (0x00000000)
  #define MCMISCS_ROCOUNTTRAINCH1RANK012DEV3_Spare_HSH                 (0x051B3150)

#define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_REG                         (0x00003154)

  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_ROCountTrainChannel2Rank0Dev0_OFF ( 0)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_ROCountTrainChannel2Rank0Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_ROCountTrainChannel2Rank0Dev0_MSK (0x000001FF)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_ROCountTrainChannel2Rank0Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_ROCountTrainChannel2Rank0Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_ROCountTrainChannel2Rank0Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_ROCountTrainChannel2Rank0Dev0_HSH (0x09003154)

  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_ROCountTrainChannel2Rank1Dev0_OFF ( 9)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_ROCountTrainChannel2Rank1Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_ROCountTrainChannel2Rank1Dev0_MSK (0x0003FE00)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_ROCountTrainChannel2Rank1Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_ROCountTrainChannel2Rank1Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_ROCountTrainChannel2Rank1Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_ROCountTrainChannel2Rank1Dev0_HSH (0x09093154)

  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_ROCountTrainChannel2Rank2Dev0_OFF (18)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_ROCountTrainChannel2Rank2Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_ROCountTrainChannel2Rank2Dev0_MSK (0x07FC0000)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_ROCountTrainChannel2Rank2Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_ROCountTrainChannel2Rank2Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_ROCountTrainChannel2Rank2Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_ROCountTrainChannel2Rank2Dev0_HSH (0x09123154)

  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_Spare_OFF                 (27)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_Spare_WID                 ( 5)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_Spare_MSK                 (0xF8000000)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_Spare_MIN                 (0)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_Spare_MAX                 (31) // 0x0000001F
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_Spare_DEF                 (0x00000000)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV2_Spare_HSH                 (0x051B3154)

#define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_REG                         (0x00003158)

  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_ROCountTrainChannel2Rank0Dev1_OFF ( 0)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_ROCountTrainChannel2Rank0Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_ROCountTrainChannel2Rank0Dev1_MSK (0x000001FF)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_ROCountTrainChannel2Rank0Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_ROCountTrainChannel2Rank0Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_ROCountTrainChannel2Rank0Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_ROCountTrainChannel2Rank0Dev1_HSH (0x09003158)

  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_ROCountTrainChannel2Rank1Dev1_OFF ( 9)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_ROCountTrainChannel2Rank1Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_ROCountTrainChannel2Rank1Dev1_MSK (0x0003FE00)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_ROCountTrainChannel2Rank1Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_ROCountTrainChannel2Rank1Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_ROCountTrainChannel2Rank1Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_ROCountTrainChannel2Rank1Dev1_HSH (0x09093158)

  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_ROCountTrainChannel2Rank2Dev1_OFF (18)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_ROCountTrainChannel2Rank2Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_ROCountTrainChannel2Rank2Dev1_MSK (0x07FC0000)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_ROCountTrainChannel2Rank2Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_ROCountTrainChannel2Rank2Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_ROCountTrainChannel2Rank2Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_ROCountTrainChannel2Rank2Dev1_HSH (0x09123158)

  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_Spare_OFF                 (27)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_Spare_WID                 ( 5)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_Spare_MSK                 (0xF8000000)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_Spare_MIN                 (0)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_Spare_MAX                 (31) // 0x0000001F
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_Spare_DEF                 (0x00000000)
  #define MCMISCS_ROCOUNTTRAINCH2RANK012DEV3_Spare_HSH                 (0x051B3158)

#define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_REG                         (0x0000315C)

  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_ROCountTrainChannel3Rank0Dev0_OFF ( 0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_ROCountTrainChannel3Rank0Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_ROCountTrainChannel3Rank0Dev0_MSK (0x000001FF)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_ROCountTrainChannel3Rank0Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_ROCountTrainChannel3Rank0Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_ROCountTrainChannel3Rank0Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_ROCountTrainChannel3Rank0Dev0_HSH (0x0900315C)

  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_ROCountTrainChannel3Rank1Dev0_OFF ( 9)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_ROCountTrainChannel3Rank1Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_ROCountTrainChannel3Rank1Dev0_MSK (0x0003FE00)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_ROCountTrainChannel3Rank1Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_ROCountTrainChannel3Rank1Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_ROCountTrainChannel3Rank1Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_ROCountTrainChannel3Rank1Dev0_HSH (0x0909315C)

  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_ROCountTrainChannel3Rank2Dev0_OFF (18)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_ROCountTrainChannel3Rank2Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_ROCountTrainChannel3Rank2Dev0_MSK (0x07FC0000)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_ROCountTrainChannel3Rank2Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_ROCountTrainChannel3Rank2Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_ROCountTrainChannel3Rank2Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_ROCountTrainChannel3Rank2Dev0_HSH (0x0912315C)

  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_Spare_OFF                 (27)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_Spare_WID                 ( 5)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_Spare_MSK                 (0xF8000000)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_Spare_MIN                 (0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_Spare_MAX                 (31) // 0x0000001F
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_Spare_DEF                 (0x00000000)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV2_Spare_HSH                 (0x051B315C)

#define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_REG                         (0x00003160)

  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_ROCountTrainChannel3Rank0Dev1_OFF ( 0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_ROCountTrainChannel3Rank0Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_ROCountTrainChannel3Rank0Dev1_MSK (0x000001FF)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_ROCountTrainChannel3Rank0Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_ROCountTrainChannel3Rank0Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_ROCountTrainChannel3Rank0Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_ROCountTrainChannel3Rank0Dev1_HSH (0x09003160)

  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_ROCountTrainChannel3Rank1Dev1_OFF ( 9)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_ROCountTrainChannel3Rank1Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_ROCountTrainChannel3Rank1Dev1_MSK (0x0003FE00)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_ROCountTrainChannel3Rank1Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_ROCountTrainChannel3Rank1Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_ROCountTrainChannel3Rank1Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_ROCountTrainChannel3Rank1Dev1_HSH (0x09093160)

  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_ROCountTrainChannel3Rank2Dev1_OFF (18)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_ROCountTrainChannel3Rank2Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_ROCountTrainChannel3Rank2Dev1_MSK (0x07FC0000)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_ROCountTrainChannel3Rank2Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_ROCountTrainChannel3Rank2Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_ROCountTrainChannel3Rank2Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_ROCountTrainChannel3Rank2Dev1_HSH (0x09123160)

  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_Spare_OFF                 (27)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_Spare_WID                 ( 5)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_Spare_MSK                 (0xF8000000)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_Spare_MIN                 (0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_Spare_MAX                 (31) // 0x0000001F
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_Spare_DEF                 (0x00000000)
  #define MCMISCS_ROCOUNTTRAINCH3RANK012DEV3_Spare_HSH                 (0x051B3160)

#define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_REG                         (0x00003164)

  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_ROCountTrainChannel0Rank3Dev0_OFF ( 0)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_ROCountTrainChannel0Rank3Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_ROCountTrainChannel0Rank3Dev0_MSK (0x000001FF)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_ROCountTrainChannel0Rank3Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_ROCountTrainChannel0Rank3Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_ROCountTrainChannel0Rank3Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_ROCountTrainChannel0Rank3Dev0_HSH (0x09003164)

  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_ROCountTrainChannel1Rank3Dev0_OFF ( 9)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_ROCountTrainChannel1Rank3Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_ROCountTrainChannel1Rank3Dev0_MSK (0x0003FE00)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_ROCountTrainChannel1Rank3Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_ROCountTrainChannel1Rank3Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_ROCountTrainChannel1Rank3Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_ROCountTrainChannel1Rank3Dev0_HSH (0x09093164)

  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_ROCountTrainChannel2Rank3Dev0_OFF (18)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_ROCountTrainChannel2Rank3Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_ROCountTrainChannel2Rank3Dev0_MSK (0x07FC0000)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_ROCountTrainChannel2Rank3Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_ROCountTrainChannel2Rank3Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_ROCountTrainChannel2Rank3Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_ROCountTrainChannel2Rank3Dev0_HSH (0x09123164)

  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_Spare_OFF                 (27)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_Spare_WID                 ( 5)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_Spare_MSK                 (0xF8000000)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_Spare_MIN                 (0)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_Spare_MAX                 (31) // 0x0000001F
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_Spare_DEF                 (0x00000000)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV2_Spare_HSH                 (0x051B3164)

#define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_REG                         (0x00003168)

  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_ROCountTrainChannel0Rank3Dev1_OFF ( 0)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_ROCountTrainChannel0Rank3Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_ROCountTrainChannel0Rank3Dev1_MSK (0x000001FF)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_ROCountTrainChannel0Rank3Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_ROCountTrainChannel0Rank3Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_ROCountTrainChannel0Rank3Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_ROCountTrainChannel0Rank3Dev1_HSH (0x09003168)

  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_ROCountTrainChannel1Rank3Dev1_OFF ( 9)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_ROCountTrainChannel1Rank3Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_ROCountTrainChannel1Rank3Dev1_MSK (0x0003FE00)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_ROCountTrainChannel1Rank3Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_ROCountTrainChannel1Rank3Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_ROCountTrainChannel1Rank3Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_ROCountTrainChannel1Rank3Dev1_HSH (0x09093168)

  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_ROCountTrainChannel2Rank3Dev1_OFF (18)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_ROCountTrainChannel2Rank3Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_ROCountTrainChannel2Rank3Dev1_MSK (0x07FC0000)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_ROCountTrainChannel2Rank3Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_ROCountTrainChannel2Rank3Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_ROCountTrainChannel2Rank3Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_ROCountTrainChannel2Rank3Dev1_HSH (0x09123168)

  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_Spare_OFF                 (27)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_Spare_WID                 ( 5)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_Spare_MSK                 (0xF8000000)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_Spare_MIN                 (0)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_Spare_MAX                 (31) // 0x0000001F
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_Spare_DEF                 (0x00000000)
  #define MCMISCS_ROCOUNTTRAINCH012RANK3DEV3_Spare_HSH                 (0x051B3168)

#define MCMISCS_ROCOUNTTRAINCH3RANK3DEV23_REG                          (0x0000316C)

  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV23_ROCountTrainChannel3Rank3Dev0_OFF ( 0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV23_ROCountTrainChannel3Rank3Dev0_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV23_ROCountTrainChannel3Rank3Dev0_MSK (0x000001FF)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV23_ROCountTrainChannel3Rank3Dev0_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV23_ROCountTrainChannel3Rank3Dev0_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV23_ROCountTrainChannel3Rank3Dev0_DEF (0x0000000F)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV23_ROCountTrainChannel3Rank3Dev0_HSH (0x0900316C)

  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV23_ROCountTrainChannel3Rank3Dev1_OFF ( 9)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV23_ROCountTrainChannel3Rank3Dev1_WID ( 9)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV23_ROCountTrainChannel3Rank3Dev1_MSK (0x0003FE00)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV23_ROCountTrainChannel3Rank3Dev1_MIN (0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV23_ROCountTrainChannel3Rank3Dev1_MAX (511) // 0x000001FF
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV23_ROCountTrainChannel3Rank3Dev1_DEF (0x00000010)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV23_ROCountTrainChannel3Rank3Dev1_HSH (0x0909316C)

  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV23_Spare_OFF                  (18)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV23_Spare_WID                  (14)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV23_Spare_MSK                  (0xFFFC0000)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV23_Spare_MIN                  (0)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV23_Spare_MAX                  (16383) // 0x00003FFF
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV23_Spare_DEF                  (0x00000000)
  #define MCMISCS_ROCOUNTTRAINCH3RANK3DEV23_Spare_HSH                  (0x0E12316C)

#define MCMISCS_DCCMAINFSMSTATUS0_REG_A0                               (0x00003100)

  #define MCMISCS_DCCMAINFSMSTATUS0_AllDccDone_OFF_A0                     ( 0)
  #define MCMISCS_DCCMAINFSMSTATUS0_AllDccDone_WID_A0                     ( 1)
  #define MCMISCS_DCCMAINFSMSTATUS0_AllDccDone_MSK_A0                     (0x00000001)
  #define MCMISCS_DCCMAINFSMSTATUS0_AllDccDone_MIN_A0                     (0)
  #define MCMISCS_DCCMAINFSMSTATUS0_AllDccDone_MAX_A0                     (1) // 0x00000001
  #define MCMISCS_DCCMAINFSMSTATUS0_AllDccDone_DEF_A0                     (0x00000000)
  #define MCMISCS_DCCMAINFSMSTATUS0_AllDccDone_HSH_A0                     (0x01003100)

  #define MCMISCS_DCCMAINFSMSTATUS0_DccByteDone_OFF_A0                    ( 1)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccByteDone_WID_A0                    (18)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccByteDone_MSK_A0                    (0x0007FFFE)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccByteDone_MIN_A0                    (0)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccByteDone_MAX_A0                    (262143) // 0x0003FFFF
  #define MCMISCS_DCCMAINFSMSTATUS0_DccByteDone_DEF_A0                    (0x00000000)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccByteDone_HSH_A0                    (0x12013100)

  #define MCMISCS_DCCMAINFSMSTATUS0_DcoCompDone_OFF_A0                    (19)
  #define MCMISCS_DCCMAINFSMSTATUS0_DcoCompDone_WID_A0                    ( 1)
  #define MCMISCS_DCCMAINFSMSTATUS0_DcoCompDone_MSK_A0                    (0x00080000)
  #define MCMISCS_DCCMAINFSMSTATUS0_DcoCompDone_MIN_A0                    (0)
  #define MCMISCS_DCCMAINFSMSTATUS0_DcoCompDone_MAX_A0                    (1) // 0x00000001
  #define MCMISCS_DCCMAINFSMSTATUS0_DcoCompDone_DEF_A0                    (0x00000000)
  #define MCMISCS_DCCMAINFSMSTATUS0_DcoCompDone_HSH_A0                    (0x01133100)

  #define MCMISCS_DCCMAINFSMSTATUS0_CurrState_OFF_A0                      (20)
  #define MCMISCS_DCCMAINFSMSTATUS0_CurrState_WID_A0                      ( 5)
  #define MCMISCS_DCCMAINFSMSTATUS0_CurrState_MSK_A0                      (0x01F00000)
  #define MCMISCS_DCCMAINFSMSTATUS0_CurrState_MIN_A0                      (0)
  #define MCMISCS_DCCMAINFSMSTATUS0_CurrState_MAX_A0                      (31) // 0x0000001F
  #define MCMISCS_DCCMAINFSMSTATUS0_CurrState_DEF_A0                      (0x00000000)
  #define MCMISCS_DCCMAINFSMSTATUS0_CurrState_HSH_A0                      (0x05143100)

  #define MCMISCS_DCCMAINFSMSTATUS0_DccClkDone_OFF_A0                     (25)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccClkDone_WID_A0                     ( 2)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccClkDone_MSK_A0                     (0x06000000)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccClkDone_MIN_A0                     (0)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccClkDone_MAX_A0                     (3) // 0x00000003
  #define MCMISCS_DCCMAINFSMSTATUS0_DccClkDone_DEF_A0                     (0x00000000)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccClkDone_HSH_A0                     (0x02193100)

  #define MCMISCS_DCCMAINFSMSTATUS0_Spare_OFF_A0                          (27)
  #define MCMISCS_DCCMAINFSMSTATUS0_Spare_WID_A0                          ( 5)
  #define MCMISCS_DCCMAINFSMSTATUS0_Spare_MSK_A0                          (0xF8000000)
  #define MCMISCS_DCCMAINFSMSTATUS0_Spare_MIN_A0                          (0)
  #define MCMISCS_DCCMAINFSMSTATUS0_Spare_MAX_A0                          (31) // 0x0000001F
  #define MCMISCS_DCCMAINFSMSTATUS0_Spare_DEF_A0                          (0x00000000)
  #define MCMISCS_DCCMAINFSMSTATUS0_Spare_HSH_A0                          (0x051B3100)

#define MCMISCS_DCCMAINFSMSTATUS0_REG                                  (0x00003170)

  #define MCMISCS_DCCMAINFSMSTATUS0_AllDccDone_OFF                     ( 0)
  #define MCMISCS_DCCMAINFSMSTATUS0_AllDccDone_WID                     ( 1)
  #define MCMISCS_DCCMAINFSMSTATUS0_AllDccDone_MSK                     (0x00000001)
  #define MCMISCS_DCCMAINFSMSTATUS0_AllDccDone_MIN                     (0)
  #define MCMISCS_DCCMAINFSMSTATUS0_AllDccDone_MAX                     (1) // 0x00000001
  #define MCMISCS_DCCMAINFSMSTATUS0_AllDccDone_DEF                     (0x00000000)
  #define MCMISCS_DCCMAINFSMSTATUS0_AllDccDone_HSH                     (0x01003170)

  #define MCMISCS_DCCMAINFSMSTATUS0_DccByteDone_OFF                    ( 1)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccByteDone_WID                    (16)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccByteDone_MSK                    (0x0001FFFE)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccByteDone_MIN                    (0)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccByteDone_MAX                    (65535) // 0x0000FFFF
  #define MCMISCS_DCCMAINFSMSTATUS0_DccByteDone_DEF                    (0x00000000)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccByteDone_HSH                    (0x10013170)

  #define MCMISCS_DCCMAINFSMSTATUS0_DccEccByteDone_OFF                 (17)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccEccByteDone_WID                 ( 2)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccEccByteDone_MSK                 (0x00060000)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccEccByteDone_MIN                 (0)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccEccByteDone_MAX                 (3) // 0x00000003
  #define MCMISCS_DCCMAINFSMSTATUS0_DccEccByteDone_DEF                 (0x00000000)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccEccByteDone_HSH                 (0x02113170)

  #define MCMISCS_DCCMAINFSMSTATUS0_DcoCompDone_OFF                    (19)
  #define MCMISCS_DCCMAINFSMSTATUS0_DcoCompDone_WID                    ( 1)
  #define MCMISCS_DCCMAINFSMSTATUS0_DcoCompDone_MSK                    (0x00080000)
  #define MCMISCS_DCCMAINFSMSTATUS0_DcoCompDone_MIN                    (0)
  #define MCMISCS_DCCMAINFSMSTATUS0_DcoCompDone_MAX                    (1) // 0x00000001
  #define MCMISCS_DCCMAINFSMSTATUS0_DcoCompDone_DEF                    (0x00000000)
  #define MCMISCS_DCCMAINFSMSTATUS0_DcoCompDone_HSH                    (0x01133170)

  #define MCMISCS_DCCMAINFSMSTATUS0_CurrState_OFF                      (20)
  #define MCMISCS_DCCMAINFSMSTATUS0_CurrState_WID                      ( 5)
  #define MCMISCS_DCCMAINFSMSTATUS0_CurrState_MSK                      (0x01F00000)
  #define MCMISCS_DCCMAINFSMSTATUS0_CurrState_MIN                      (0)
  #define MCMISCS_DCCMAINFSMSTATUS0_CurrState_MAX                      (31) // 0x0000001F
  #define MCMISCS_DCCMAINFSMSTATUS0_CurrState_DEF                      (0x00000000)
  #define MCMISCS_DCCMAINFSMSTATUS0_CurrState_HSH                      (0x05143170)

  #define MCMISCS_DCCMAINFSMSTATUS0_DccClkDone_OFF                     (25)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccClkDone_WID                     ( 2)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccClkDone_MSK                     (0x06000000)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccClkDone_MIN                     (0)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccClkDone_MAX                     (3) // 0x00000003
  #define MCMISCS_DCCMAINFSMSTATUS0_DccClkDone_DEF                     (0x00000000)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccClkDone_HSH                     (0x02193170)

  #define MCMISCS_DCCMAINFSMSTATUS0_DccDtClkDone_OFF                   (27)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccDtClkDone_WID                   ( 2)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccDtClkDone_MSK                   (0x18000000)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccDtClkDone_MIN                   (0)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccDtClkDone_MAX                   (3) // 0x00000003
  #define MCMISCS_DCCMAINFSMSTATUS0_DccDtClkDone_DEF                   (0x00000000)
  #define MCMISCS_DCCMAINFSMSTATUS0_DccDtClkDone_HSH                   (0x021B3170)

  #define MCMISCS_DCCMAINFSMSTATUS0_Spare_OFF                          (29)
  #define MCMISCS_DCCMAINFSMSTATUS0_Spare_WID                          ( 3)
  #define MCMISCS_DCCMAINFSMSTATUS0_Spare_MSK                          (0xE0000000)
  #define MCMISCS_DCCMAINFSMSTATUS0_Spare_MIN                          (0)
  #define MCMISCS_DCCMAINFSMSTATUS0_Spare_MAX                          (7) // 0x00000007
  #define MCMISCS_DCCMAINFSMSTATUS0_Spare_DEF                          (0x00000000)
  #define MCMISCS_DCCMAINFSMSTATUS0_Spare_HSH                          (0x031D3170)

#define MCMISCS_DELTADQSCOMMON2DEV23_REG                               (0x00003180)

  #define MCMISCS_DELTADQSCOMMON2DEV23_DfxLp4OBSData_OFF               ( 0)
  #define MCMISCS_DELTADQSCOMMON2DEV23_DfxLp4OBSData_WID               (32)
  #define MCMISCS_DELTADQSCOMMON2DEV23_DfxLp4OBSData_MSK               (0xFFFFFFFF)
  #define MCMISCS_DELTADQSCOMMON2DEV23_DfxLp4OBSData_MIN               (0)
  #define MCMISCS_DELTADQSCOMMON2DEV23_DfxLp4OBSData_MAX               (4294967295) // 0xFFFFFFFF
  #define MCMISCS_DELTADQSCOMMON2DEV23_DfxLp4OBSData_DEF               (0x00000000)
  #define MCMISCS_DELTADQSCOMMON2DEV23_DfxLp4OBSData_HSH               (0x20003180)

#define MCMISCS_DELTADQSCOMMON3_REG                                    (0x00003184)

  #define MCMISCS_DELTADQSCOMMON3_Lp4DeltaDQSCalcUnitOvrd_OFF          ( 0)
  #define MCMISCS_DELTADQSCOMMON3_Lp4DeltaDQSCalcUnitOvrd_WID          ( 2)
  #define MCMISCS_DELTADQSCOMMON3_Lp4DeltaDQSCalcUnitOvrd_MSK          (0x00000003)
  #define MCMISCS_DELTADQSCOMMON3_Lp4DeltaDQSCalcUnitOvrd_MIN          (0)
  #define MCMISCS_DELTADQSCOMMON3_Lp4DeltaDQSCalcUnitOvrd_MAX          (3) // 0x00000003
  #define MCMISCS_DELTADQSCOMMON3_Lp4DeltaDQSCalcUnitOvrd_DEF          (0x00000000)
  #define MCMISCS_DELTADQSCOMMON3_Lp4DeltaDQSCalcUnitOvrd_HSH          (0x02003184)

  #define MCMISCS_DELTADQSCOMMON3_Lp4DeltaDQSCalcUnitOvrdEn_OFF        ( 2)
  #define MCMISCS_DELTADQSCOMMON3_Lp4DeltaDQSCalcUnitOvrdEn_WID        ( 2)
  #define MCMISCS_DELTADQSCOMMON3_Lp4DeltaDQSCalcUnitOvrdEn_MSK        (0x0000000C)
  #define MCMISCS_DELTADQSCOMMON3_Lp4DeltaDQSCalcUnitOvrdEn_MIN        (0)
  #define MCMISCS_DELTADQSCOMMON3_Lp4DeltaDQSCalcUnitOvrdEn_MAX        (3) // 0x00000003
  #define MCMISCS_DELTADQSCOMMON3_Lp4DeltaDQSCalcUnitOvrdEn_DEF        (0x00000000)
  #define MCMISCS_DELTADQSCOMMON3_Lp4DeltaDQSCalcUnitOvrdEn_HSH        (0x02023184)

  #define MCMISCS_DELTADQSCOMMON3_Lp4RankPairSwap_OFF                  ( 4)
  #define MCMISCS_DELTADQSCOMMON3_Lp4RankPairSwap_WID                  ( 2)
  #define MCMISCS_DELTADQSCOMMON3_Lp4RankPairSwap_MSK                  (0x00000030)
  #define MCMISCS_DELTADQSCOMMON3_Lp4RankPairSwap_MIN                  (0)
  #define MCMISCS_DELTADQSCOMMON3_Lp4RankPairSwap_MAX                  (3) // 0x00000003
  #define MCMISCS_DELTADQSCOMMON3_Lp4RankPairSwap_DEF                  (0x00000000)
  #define MCMISCS_DELTADQSCOMMON3_Lp4RankPairSwap_HSH                  (0x02043184)

  #define MCMISCS_DELTADQSCOMMON3_Lp4MR19ExeQueWriteEnableOvrd_OFF     ( 6)
  #define MCMISCS_DELTADQSCOMMON3_Lp4MR19ExeQueWriteEnableOvrd_WID     ( 2)
  #define MCMISCS_DELTADQSCOMMON3_Lp4MR19ExeQueWriteEnableOvrd_MSK     (0x000000C0)
  #define MCMISCS_DELTADQSCOMMON3_Lp4MR19ExeQueWriteEnableOvrd_MIN     (0)
  #define MCMISCS_DELTADQSCOMMON3_Lp4MR19ExeQueWriteEnableOvrd_MAX     (3) // 0x00000003
  #define MCMISCS_DELTADQSCOMMON3_Lp4MR19ExeQueWriteEnableOvrd_DEF     (0x00000000)
  #define MCMISCS_DELTADQSCOMMON3_Lp4MR19ExeQueWriteEnableOvrd_HSH     (0x02063184)

  #define MCMISCS_DELTADQSCOMMON3_Lp4MR19ExeQueWriteEnableOvrdEn_OFF   ( 8)
  #define MCMISCS_DELTADQSCOMMON3_Lp4MR19ExeQueWriteEnableOvrdEn_WID   ( 2)
  #define MCMISCS_DELTADQSCOMMON3_Lp4MR19ExeQueWriteEnableOvrdEn_MSK   (0x00000300)
  #define MCMISCS_DELTADQSCOMMON3_Lp4MR19ExeQueWriteEnableOvrdEn_MIN   (0)
  #define MCMISCS_DELTADQSCOMMON3_Lp4MR19ExeQueWriteEnableOvrdEn_MAX   (3) // 0x00000003
  #define MCMISCS_DELTADQSCOMMON3_Lp4MR19ExeQueWriteEnableOvrdEn_DEF   (0x00000000)
  #define MCMISCS_DELTADQSCOMMON3_Lp4MR19ExeQueWriteEnableOvrdEn_HSH   (0x02083184)

  #define MCMISCS_DELTADQSCOMMON3_Lp4DeltaDQSROCountForceZero_OFF      (10)
  #define MCMISCS_DELTADQSCOMMON3_Lp4DeltaDQSROCountForceZero_WID      ( 2)
  #define MCMISCS_DELTADQSCOMMON3_Lp4DeltaDQSROCountForceZero_MSK      (0x00000C00)
  #define MCMISCS_DELTADQSCOMMON3_Lp4DeltaDQSROCountForceZero_MIN      (0)
  #define MCMISCS_DELTADQSCOMMON3_Lp4DeltaDQSROCountForceZero_MAX      (3) // 0x00000003
  #define MCMISCS_DELTADQSCOMMON3_Lp4DeltaDQSROCountForceZero_DEF      (0x00000000)
  #define MCMISCS_DELTADQSCOMMON3_Lp4DeltaDQSROCountForceZero_HSH      (0x020A3184)

  #define MCMISCS_DELTADQSCOMMON3_spare_OFF                            (12)
  #define MCMISCS_DELTADQSCOMMON3_spare_WID                            (20)
  #define MCMISCS_DELTADQSCOMMON3_spare_MSK                            (0xFFFFF000)
  #define MCMISCS_DELTADQSCOMMON3_spare_MIN                            (0)
  #define MCMISCS_DELTADQSCOMMON3_spare_MAX                            (1048575) // 0x000FFFFF
  #define MCMISCS_DELTADQSCOMMON3_spare_DEF                            (0x00000000)
  #define MCMISCS_DELTADQSCOMMON3_spare_HSH                            (0x140C3184)
#pragma pack(pop)
#endif
