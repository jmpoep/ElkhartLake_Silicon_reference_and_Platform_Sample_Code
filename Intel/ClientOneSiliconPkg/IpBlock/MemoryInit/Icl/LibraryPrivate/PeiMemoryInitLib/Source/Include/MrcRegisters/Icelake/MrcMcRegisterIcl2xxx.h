#ifndef __MrcMcRegisterIcl2xxx_h__
#define __MrcMcRegisterIcl2xxx_h__
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


#define DDRDATA0_CR_MASTERDLLCFG_REG                                   (0x00002000)

  #define DDRDATA0_CR_MASTERDLLCFG_LockThresh_OFF                      ( 0)
  #define DDRDATA0_CR_MASTERDLLCFG_LockThresh_WID                      ( 3)
  #define DDRDATA0_CR_MASTERDLLCFG_LockThresh_MSK                      (0x00000007)
  #define DDRDATA0_CR_MASTERDLLCFG_LockThresh_MIN                      (0)
  #define DDRDATA0_CR_MASTERDLLCFG_LockThresh_MAX                      (7) // 0x00000007
  #define DDRDATA0_CR_MASTERDLLCFG_LockThresh_DEF                      (0x00000004)
  #define DDRDATA0_CR_MASTERDLLCFG_LockThresh_HSH                      (0x03002000)

  #define DDRDATA0_CR_MASTERDLLCFG_LockCtr_OFF                         ( 3)
  #define DDRDATA0_CR_MASTERDLLCFG_LockCtr_WID                         ( 2)
  #define DDRDATA0_CR_MASTERDLLCFG_LockCtr_MSK                         (0x00000018)
  #define DDRDATA0_CR_MASTERDLLCFG_LockCtr_MIN                         (0)
  #define DDRDATA0_CR_MASTERDLLCFG_LockCtr_MAX                         (3) // 0x00000003
  #define DDRDATA0_CR_MASTERDLLCFG_LockCtr_DEF                         (0x00000000)
  #define DDRDATA0_CR_MASTERDLLCFG_LockCtr_HSH                         (0x02032000)

  #define DDRDATA0_CR_MASTERDLLCFG_VctrlDischRate_OFF                  ( 5)
  #define DDRDATA0_CR_MASTERDLLCFG_VctrlDischRate_WID                  ( 2)
  #define DDRDATA0_CR_MASTERDLLCFG_VctrlDischRate_MSK                  (0x00000060)
  #define DDRDATA0_CR_MASTERDLLCFG_VctrlDischRate_MIN                  (0)
  #define DDRDATA0_CR_MASTERDLLCFG_VctrlDischRate_MAX                  (3) // 0x00000003
  #define DDRDATA0_CR_MASTERDLLCFG_VctrlDischRate_DEF                  (0x00000000)
  #define DDRDATA0_CR_MASTERDLLCFG_VctrlDischRate_HSH                  (0x02052000)

  #define DDRDATA0_CR_MASTERDLLCFG_SelVctrlHi_OFF                      ( 7)
  #define DDRDATA0_CR_MASTERDLLCFG_SelVctrlHi_WID                      ( 1)
  #define DDRDATA0_CR_MASTERDLLCFG_SelVctrlHi_MSK                      (0x00000080)
  #define DDRDATA0_CR_MASTERDLLCFG_SelVctrlHi_MIN                      (0)
  #define DDRDATA0_CR_MASTERDLLCFG_SelVctrlHi_MAX                      (1) // 0x00000001
  #define DDRDATA0_CR_MASTERDLLCFG_SelVctrlHi_DEF                      (0x00000000)
  #define DDRDATA0_CR_MASTERDLLCFG_SelVctrlHi_HSH                      (0x01072000)

  #define DDRDATA0_CR_MASTERDLLCFG_StartupCntSel_OFF                   ( 8)
  #define DDRDATA0_CR_MASTERDLLCFG_StartupCntSel_WID                   ( 1)
  #define DDRDATA0_CR_MASTERDLLCFG_StartupCntSel_MSK                   (0x00000100)
  #define DDRDATA0_CR_MASTERDLLCFG_StartupCntSel_MIN                   (0)
  #define DDRDATA0_CR_MASTERDLLCFG_StartupCntSel_MAX                   (1) // 0x00000001
  #define DDRDATA0_CR_MASTERDLLCFG_StartupCntSel_DEF                   (0x00000000)
  #define DDRDATA0_CR_MASTERDLLCFG_StartupCntSel_HSH                   (0x01082000)

  #define DDRDATA0_CR_MASTERDLLCFG_LockSel_OFF                         ( 9)
  #define DDRDATA0_CR_MASTERDLLCFG_LockSel_WID                         ( 2)
  #define DDRDATA0_CR_MASTERDLLCFG_LockSel_MSK                         (0x00000600)
  #define DDRDATA0_CR_MASTERDLLCFG_LockSel_MIN                         (0)
  #define DDRDATA0_CR_MASTERDLLCFG_LockSel_MAX                         (3) // 0x00000003
  #define DDRDATA0_CR_MASTERDLLCFG_LockSel_DEF                         (0x00000000)
  #define DDRDATA0_CR_MASTERDLLCFG_LockSel_HSH                         (0x02092000)

  #define DDRDATA0_CR_MASTERDLLCFG_RstOvrd_OFF                         (11)
  #define DDRDATA0_CR_MASTERDLLCFG_RstOvrd_WID                         ( 1)
  #define DDRDATA0_CR_MASTERDLLCFG_RstOvrd_MSK                         (0x00000800)
  #define DDRDATA0_CR_MASTERDLLCFG_RstOvrd_MIN                         (0)
  #define DDRDATA0_CR_MASTERDLLCFG_RstOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA0_CR_MASTERDLLCFG_RstOvrd_DEF                         (0x00000000)
  #define DDRDATA0_CR_MASTERDLLCFG_RstOvrd_HSH                         (0x010B2000)

  #define DDRDATA0_CR_MASTERDLLCFG_SelRstOvrd_OFF                      (12)
  #define DDRDATA0_CR_MASTERDLLCFG_SelRstOvrd_WID                      ( 1)
  #define DDRDATA0_CR_MASTERDLLCFG_SelRstOvrd_MSK                      (0x00001000)
  #define DDRDATA0_CR_MASTERDLLCFG_SelRstOvrd_MIN                      (0)
  #define DDRDATA0_CR_MASTERDLLCFG_SelRstOvrd_MAX                      (1) // 0x00000001
  #define DDRDATA0_CR_MASTERDLLCFG_SelRstOvrd_DEF                      (0x00000000)
  #define DDRDATA0_CR_MASTERDLLCFG_SelRstOvrd_HSH                      (0x010C2000)

  #define DDRDATA0_CR_MASTERDLLCFG_TimeOutOvrd_OFF                     (13)
  #define DDRDATA0_CR_MASTERDLLCFG_TimeOutOvrd_WID                     ( 1)
  #define DDRDATA0_CR_MASTERDLLCFG_TimeOutOvrd_MSK                     (0x00002000)
  #define DDRDATA0_CR_MASTERDLLCFG_TimeOutOvrd_MIN                     (0)
  #define DDRDATA0_CR_MASTERDLLCFG_TimeOutOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA0_CR_MASTERDLLCFG_TimeOutOvrd_DEF                     (0x00000000)
  #define DDRDATA0_CR_MASTERDLLCFG_TimeOutOvrd_HSH                     (0x010D2000)

  #define DDRDATA0_CR_MASTERDLLCFG_SelTimeOutOvrd_OFF                  (14)
  #define DDRDATA0_CR_MASTERDLLCFG_SelTimeOutOvrd_WID                  ( 1)
  #define DDRDATA0_CR_MASTERDLLCFG_SelTimeOutOvrd_MSK                  (0x00004000)
  #define DDRDATA0_CR_MASTERDLLCFG_SelTimeOutOvrd_MIN                  (0)
  #define DDRDATA0_CR_MASTERDLLCFG_SelTimeOutOvrd_MAX                  (1) // 0x00000001
  #define DDRDATA0_CR_MASTERDLLCFG_SelTimeOutOvrd_DEF                  (0x00000000)
  #define DDRDATA0_CR_MASTERDLLCFG_SelTimeOutOvrd_HSH                  (0x010E2000)

  #define DDRDATA0_CR_MASTERDLLCFG_ClkGateOvrd_OFF                     (15)
  #define DDRDATA0_CR_MASTERDLLCFG_ClkGateOvrd_WID                     ( 1)
  #define DDRDATA0_CR_MASTERDLLCFG_ClkGateOvrd_MSK                     (0x00008000)
  #define DDRDATA0_CR_MASTERDLLCFG_ClkGateOvrd_MIN                     (0)
  #define DDRDATA0_CR_MASTERDLLCFG_ClkGateOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA0_CR_MASTERDLLCFG_ClkGateOvrd_DEF                     (0x00000000)
  #define DDRDATA0_CR_MASTERDLLCFG_ClkGateOvrd_HSH                     (0x010F2000)

  #define DDRDATA0_CR_MASTERDLLCFG_LockOvrd_OFF                        (16)
  #define DDRDATA0_CR_MASTERDLLCFG_LockOvrd_WID                        ( 1)
  #define DDRDATA0_CR_MASTERDLLCFG_LockOvrd_MSK                        (0x00010000)
  #define DDRDATA0_CR_MASTERDLLCFG_LockOvrd_MIN                        (0)
  #define DDRDATA0_CR_MASTERDLLCFG_LockOvrd_MAX                        (1) // 0x00000001
  #define DDRDATA0_CR_MASTERDLLCFG_LockOvrd_DEF                        (0x00000000)
  #define DDRDATA0_CR_MASTERDLLCFG_LockOvrd_HSH                        (0x01102000)

  #define DDRDATA0_CR_MASTERDLLCFG_SelLockOvrd_OFF                     (17)
  #define DDRDATA0_CR_MASTERDLLCFG_SelLockOvrd_WID                     ( 1)
  #define DDRDATA0_CR_MASTERDLLCFG_SelLockOvrd_MSK                     (0x00020000)
  #define DDRDATA0_CR_MASTERDLLCFG_SelLockOvrd_MIN                     (0)
  #define DDRDATA0_CR_MASTERDLLCFG_SelLockOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA0_CR_MASTERDLLCFG_SelLockOvrd_DEF                     (0x00000000)
  #define DDRDATA0_CR_MASTERDLLCFG_SelLockOvrd_HSH                     (0x01112000)

  #define DDRDATA0_CR_MASTERDLLCFG_OpenLoopOvrd_OFF                    (18)
  #define DDRDATA0_CR_MASTERDLLCFG_OpenLoopOvrd_WID                    ( 1)
  #define DDRDATA0_CR_MASTERDLLCFG_OpenLoopOvrd_MSK                    (0x00040000)
  #define DDRDATA0_CR_MASTERDLLCFG_OpenLoopOvrd_MIN                    (0)
  #define DDRDATA0_CR_MASTERDLLCFG_OpenLoopOvrd_MAX                    (1) // 0x00000001
  #define DDRDATA0_CR_MASTERDLLCFG_OpenLoopOvrd_DEF                    (0x00000000)
  #define DDRDATA0_CR_MASTERDLLCFG_OpenLoopOvrd_HSH                    (0x01122000)

  #define DDRDATA0_CR_MASTERDLLCFG_SelOpenLoopOvrd_OFF                 (19)
  #define DDRDATA0_CR_MASTERDLLCFG_SelOpenLoopOvrd_WID                 ( 1)
  #define DDRDATA0_CR_MASTERDLLCFG_SelOpenLoopOvrd_MSK                 (0x00080000)
  #define DDRDATA0_CR_MASTERDLLCFG_SelOpenLoopOvrd_MIN                 (0)
  #define DDRDATA0_CR_MASTERDLLCFG_SelOpenLoopOvrd_MAX                 (1) // 0x00000001
  #define DDRDATA0_CR_MASTERDLLCFG_SelOpenLoopOvrd_DEF                 (0x00000000)
  #define DDRDATA0_CR_MASTERDLLCFG_SelOpenLoopOvrd_HSH                 (0x01132000)

  #define DDRDATA0_CR_MASTERDLLCFG_WkLockEnOvrd_OFF                    (20)
  #define DDRDATA0_CR_MASTERDLLCFG_WkLockEnOvrd_WID                    ( 1)
  #define DDRDATA0_CR_MASTERDLLCFG_WkLockEnOvrd_MSK                    (0x00100000)
  #define DDRDATA0_CR_MASTERDLLCFG_WkLockEnOvrd_MIN                    (0)
  #define DDRDATA0_CR_MASTERDLLCFG_WkLockEnOvrd_MAX                    (1) // 0x00000001
  #define DDRDATA0_CR_MASTERDLLCFG_WkLockEnOvrd_DEF                    (0x00000000)
  #define DDRDATA0_CR_MASTERDLLCFG_WkLockEnOvrd_HSH                    (0x01142000)

  #define DDRDATA0_CR_MASTERDLLCFG_SelWkLockEnOvrd_OFF                 (21)
  #define DDRDATA0_CR_MASTERDLLCFG_SelWkLockEnOvrd_WID                 ( 1)
  #define DDRDATA0_CR_MASTERDLLCFG_SelWkLockEnOvrd_MSK                 (0x00200000)
  #define DDRDATA0_CR_MASTERDLLCFG_SelWkLockEnOvrd_MIN                 (0)
  #define DDRDATA0_CR_MASTERDLLCFG_SelWkLockEnOvrd_MAX                 (1) // 0x00000001
  #define DDRDATA0_CR_MASTERDLLCFG_SelWkLockEnOvrd_DEF                 (0x00000000)
  #define DDRDATA0_CR_MASTERDLLCFG_SelWkLockEnOvrd_HSH                 (0x01152000)

  #define DDRDATA0_CR_MASTERDLLCFG_CfdlDis_OFF                         (22)
  #define DDRDATA0_CR_MASTERDLLCFG_CfdlDis_WID                         ( 1)
  #define DDRDATA0_CR_MASTERDLLCFG_CfdlDis_MSK                         (0x00400000)
  #define DDRDATA0_CR_MASTERDLLCFG_CfdlDis_MIN                         (0)
  #define DDRDATA0_CR_MASTERDLLCFG_CfdlDis_MAX                         (1) // 0x00000001
  #define DDRDATA0_CR_MASTERDLLCFG_CfdlDis_DEF                         (0x00000000)
  #define DDRDATA0_CR_MASTERDLLCFG_CfdlDis_HSH                         (0x01162000)

  #define DDRDATA0_CR_MASTERDLLCFG_DftEn_OFF                           (23)
  #define DDRDATA0_CR_MASTERDLLCFG_DftEn_WID                           ( 1)
  #define DDRDATA0_CR_MASTERDLLCFG_DftEn_MSK                           (0x00800000)
  #define DDRDATA0_CR_MASTERDLLCFG_DftEn_MIN                           (0)
  #define DDRDATA0_CR_MASTERDLLCFG_DftEn_MAX                           (1) // 0x00000001
  #define DDRDATA0_CR_MASTERDLLCFG_DftEn_DEF                           (0x00000000)
  #define DDRDATA0_CR_MASTERDLLCFG_DftEn_HSH                           (0x01172000)

  #define DDRDATA0_CR_MASTERDLLCFG_spare0_OFF                          (24)
  #define DDRDATA0_CR_MASTERDLLCFG_spare0_WID                          ( 8)
  #define DDRDATA0_CR_MASTERDLLCFG_spare0_MSK                          (0xFF000000)
  #define DDRDATA0_CR_MASTERDLLCFG_spare0_MIN                          (0)
  #define DDRDATA0_CR_MASTERDLLCFG_spare0_MAX                          (255) // 0x000000FF
  #define DDRDATA0_CR_MASTERDLLCFG_spare0_DEF                          (0x00000000)
  #define DDRDATA0_CR_MASTERDLLCFG_spare0_HSH                          (0x08182000)

#define DDRDATA0_CR_CBTUNE0_REG                                        (0x00002004)

  #define DDRDATA0_CR_CBTUNE0_DllBWEn_OFF                              ( 0)
  #define DDRDATA0_CR_CBTUNE0_DllBWEn_WID                              (32)
  #define DDRDATA0_CR_CBTUNE0_DllBWEn_MSK                              (0xFFFFFFFF)
  #define DDRDATA0_CR_CBTUNE0_DllBWEn_MIN                              (0)
  #define DDRDATA0_CR_CBTUNE0_DllBWEn_MAX                              (4294967295) // 0xFFFFFFFF
  #define DDRDATA0_CR_CBTUNE0_DllBWEn_DEF                              (0xFDB86521)
  #define DDRDATA0_CR_CBTUNE0_DllBWEn_HSH                              (0x20002004)

#define DDRDATA0_CR_CBTUNE1_REG                                        (0x00002008)

  #define DDRDATA0_CR_CBTUNE1_PiCbEn_OFF                               ( 0)
  #define DDRDATA0_CR_CBTUNE1_PiCbEn_WID                               (24)
  #define DDRDATA0_CR_CBTUNE1_PiCbEn_MSK                               (0x00FFFFFF)
  #define DDRDATA0_CR_CBTUNE1_PiCbEn_MIN                               (0)
  #define DDRDATA0_CR_CBTUNE1_PiCbEn_MAX                               (16777215) // 0x00FFFFFF
  #define DDRDATA0_CR_CBTUNE1_PiCbEn_DEF                               (0x00249492)
  #define DDRDATA0_CR_CBTUNE1_PiCbEn_HSH                               (0x18002008)

  #define DDRDATA0_CR_CBTUNE1_CbEnRsvd_OFF                             (24)
  #define DDRDATA0_CR_CBTUNE1_CbEnRsvd_WID                             ( 3)
  #define DDRDATA0_CR_CBTUNE1_CbEnRsvd_MSK                             (0x07000000)
  #define DDRDATA0_CR_CBTUNE1_CbEnRsvd_MIN                             (0)
  #define DDRDATA0_CR_CBTUNE1_CbEnRsvd_MAX                             (7) // 0x00000007
  #define DDRDATA0_CR_CBTUNE1_CbEnRsvd_DEF                             (0x00000000)
  #define DDRDATA0_CR_CBTUNE1_CbEnRsvd_HSH                             (0x03182008)

  #define DDRDATA0_CR_CBTUNE1_CbEnDllFuse_OFF                          (27)
  #define DDRDATA0_CR_CBTUNE1_CbEnDllFuse_WID                          ( 3)
  #define DDRDATA0_CR_CBTUNE1_CbEnDllFuse_MSK                          (0x38000000)
  #define DDRDATA0_CR_CBTUNE1_CbEnDllFuse_MIN                          (0)
  #define DDRDATA0_CR_CBTUNE1_CbEnDllFuse_MAX                          (7) // 0x00000007
  #define DDRDATA0_CR_CBTUNE1_CbEnDllFuse_DEF                          (0x00000002)
  #define DDRDATA0_CR_CBTUNE1_CbEnDllFuse_HSH                          (0x031B2008)

  #define DDRDATA0_CR_CBTUNE1_Spare_OFF                                (30)
  #define DDRDATA0_CR_CBTUNE1_Spare_WID                                ( 2)
  #define DDRDATA0_CR_CBTUNE1_Spare_MSK                                (0xC0000000)
  #define DDRDATA0_CR_CBTUNE1_Spare_MIN                                (0)
  #define DDRDATA0_CR_CBTUNE1_Spare_MAX                                (3) // 0x00000003
  #define DDRDATA0_CR_CBTUNE1_Spare_DEF                                (0x00000000)
  #define DDRDATA0_CR_CBTUNE1_Spare_HSH                                (0x021E2008)

#define DDRDATA0_CR_ADCCFG_REG                                         (0x0000200C)

  #define DDRDATA0_CR_ADCCFG_ADC_frz_OFF                               ( 0)
  #define DDRDATA0_CR_ADCCFG_ADC_frz_WID                               ( 1)
  #define DDRDATA0_CR_ADCCFG_ADC_frz_MSK                               (0x00000001)
  #define DDRDATA0_CR_ADCCFG_ADC_frz_MIN                               (0)
  #define DDRDATA0_CR_ADCCFG_ADC_frz_MAX                               (1) // 0x00000001
  #define DDRDATA0_CR_ADCCFG_ADC_frz_DEF                               (0x00000000)
  #define DDRDATA0_CR_ADCCFG_ADC_frz_HSH                               (0x0100200C)

  #define DDRDATA0_CR_ADCCFG_ADC_en_OFF                                ( 1)
  #define DDRDATA0_CR_ADCCFG_ADC_en_WID                                ( 1)
  #define DDRDATA0_CR_ADCCFG_ADC_en_MSK                                (0x00000002)
  #define DDRDATA0_CR_ADCCFG_ADC_en_MIN                                (0)
  #define DDRDATA0_CR_ADCCFG_ADC_en_MAX                                (1) // 0x00000001
  #define DDRDATA0_CR_ADCCFG_ADC_en_DEF                                (0x00000000)
  #define DDRDATA0_CR_ADCCFG_ADC_en_HSH                                (0x0101200C)

  #define DDRDATA0_CR_ADCCFG_ADCclkdiv_OFF                             ( 2)
  #define DDRDATA0_CR_ADCCFG_ADCclkdiv_WID                             ( 2)
  #define DDRDATA0_CR_ADCCFG_ADCclkdiv_MSK                             (0x0000000C)
  #define DDRDATA0_CR_ADCCFG_ADCclkdiv_MIN                             (0)
  #define DDRDATA0_CR_ADCCFG_ADCclkdiv_MAX                             (3) // 0x00000003
  #define DDRDATA0_CR_ADCCFG_ADCclkdiv_DEF                             (0x00000000)
  #define DDRDATA0_CR_ADCCFG_ADCclkdiv_HSH                             (0x0202200C)

  #define DDRDATA0_CR_ADCCFG_ADCstartcount_OFF                         ( 4)
  #define DDRDATA0_CR_ADCCFG_ADCstartcount_WID                         ( 2)
  #define DDRDATA0_CR_ADCCFG_ADCstartcount_MSK                         (0x00000030)
  #define DDRDATA0_CR_ADCCFG_ADCstartcount_MIN                         (0)
  #define DDRDATA0_CR_ADCCFG_ADCstartcount_MAX                         (3) // 0x00000003
  #define DDRDATA0_CR_ADCCFG_ADCstartcount_DEF                         (0x00000000)
  #define DDRDATA0_CR_ADCCFG_ADCstartcount_HSH                         (0x0204200C)

  #define DDRDATA0_CR_ADCCFG_ADCChopEn_OFF                             ( 6)
  #define DDRDATA0_CR_ADCCFG_ADCChopEn_WID                             ( 1)
  #define DDRDATA0_CR_ADCCFG_ADCChopEn_MSK                             (0x00000040)
  #define DDRDATA0_CR_ADCCFG_ADCChopEn_MIN                             (0)
  #define DDRDATA0_CR_ADCCFG_ADCChopEn_MAX                             (1) // 0x00000001
  #define DDRDATA0_CR_ADCCFG_ADCChopEn_DEF                             (0x00000000)
  #define DDRDATA0_CR_ADCCFG_ADCChopEn_HSH                             (0x0106200C)

  #define DDRDATA0_CR_ADCCFG_Spare_OFF                                 ( 7)
  #define DDRDATA0_CR_ADCCFG_Spare_WID                                 (25)
  #define DDRDATA0_CR_ADCCFG_Spare_MSK                                 (0xFFFFFF80)
  #define DDRDATA0_CR_ADCCFG_Spare_MIN                                 (0)
  #define DDRDATA0_CR_ADCCFG_Spare_MAX                                 (33554431) // 0x01FFFFFF
  #define DDRDATA0_CR_ADCCFG_Spare_DEF                                 (0x00000000)
  #define DDRDATA0_CR_ADCCFG_Spare_HSH                                 (0x1907200C)

#define DDRDATA0_CR_CBTUNE2_REG                                        (0x00002010)

  #define DDRDATA0_CR_CBTUNE2_DllCbEn_OFF                              ( 0)
  #define DDRDATA0_CR_CBTUNE2_DllCbEn_WID                              (16)
  #define DDRDATA0_CR_CBTUNE2_DllCbEn_MSK                              (0x0000FFFF)
  #define DDRDATA0_CR_CBTUNE2_DllCbEn_MIN                              (0)
  #define DDRDATA0_CR_CBTUNE2_DllCbEn_MAX                              (65535) // 0x0000FFFF
  #define DDRDATA0_CR_CBTUNE2_DllCbEn_DEF                              (0x00000000)
  #define DDRDATA0_CR_CBTUNE2_DllCbEn_HSH                              (0x10002010)

  #define DDRDATA0_CR_CBTUNE2_Spare_OFF                                (16)
  #define DDRDATA0_CR_CBTUNE2_Spare_WID                                (16)
  #define DDRDATA0_CR_CBTUNE2_Spare_MSK                                (0xFFFF0000)
  #define DDRDATA0_CR_CBTUNE2_Spare_MIN                                (0)
  #define DDRDATA0_CR_CBTUNE2_Spare_MAX                                (65535) // 0x0000FFFF
  #define DDRDATA0_CR_CBTUNE2_Spare_DEF                                (0x00000000)
  #define DDRDATA0_CR_CBTUNE2_Spare_HSH                                (0x10102010)

#define DDRDATA0_CR_PIDFTDLY_REG                                       (0x00002018)

  #define DDRDATA0_CR_PIDFTDLY_PiDftDelay_OFF                          ( 0)
  #define DDRDATA0_CR_PIDFTDLY_PiDftDelay_WID                          ( 7)
  #define DDRDATA0_CR_PIDFTDLY_PiDftDelay_MSK                          (0x0000007F)
  #define DDRDATA0_CR_PIDFTDLY_PiDftDelay_MIN                          (0)
  #define DDRDATA0_CR_PIDFTDLY_PiDftDelay_MAX                          (127) // 0x0000007F
  #define DDRDATA0_CR_PIDFTDLY_PiDftDelay_DEF                          (0x00000000)
  #define DDRDATA0_CR_PIDFTDLY_PiDftDelay_HSH                          (0x07002018)

  #define DDRDATA0_CR_PIDFTDLY_Ch0PiEnOvrd_OFF                         ( 7)
  #define DDRDATA0_CR_PIDFTDLY_Ch0PiEnOvrd_WID                         ( 1)
  #define DDRDATA0_CR_PIDFTDLY_Ch0PiEnOvrd_MSK                         (0x00000080)
  #define DDRDATA0_CR_PIDFTDLY_Ch0PiEnOvrd_MIN                         (0)
  #define DDRDATA0_CR_PIDFTDLY_Ch0PiEnOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA0_CR_PIDFTDLY_Ch0PiEnOvrd_DEF                         (0x00000000)
  #define DDRDATA0_CR_PIDFTDLY_Ch0PiEnOvrd_HSH                         (0x01072018)

  #define DDRDATA0_CR_PIDFTDLY_Ch1PiEnOvrd_OFF                         ( 8)
  #define DDRDATA0_CR_PIDFTDLY_Ch1PiEnOvrd_WID                         ( 1)
  #define DDRDATA0_CR_PIDFTDLY_Ch1PiEnOvrd_MSK                         (0x00000100)
  #define DDRDATA0_CR_PIDFTDLY_Ch1PiEnOvrd_MIN                         (0)
  #define DDRDATA0_CR_PIDFTDLY_Ch1PiEnOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA0_CR_PIDFTDLY_Ch1PiEnOvrd_DEF                         (0x00000000)
  #define DDRDATA0_CR_PIDFTDLY_Ch1PiEnOvrd_HSH                         (0x01082018)

  #define DDRDATA0_CR_PIDFTDLY_Ch0PiDFTEn_OFF                          ( 9)
  #define DDRDATA0_CR_PIDFTDLY_Ch0PiDFTEn_WID                          ( 1)
  #define DDRDATA0_CR_PIDFTDLY_Ch0PiDFTEn_MSK                          (0x00000200)
  #define DDRDATA0_CR_PIDFTDLY_Ch0PiDFTEn_MIN                          (0)
  #define DDRDATA0_CR_PIDFTDLY_Ch0PiDFTEn_MAX                          (1) // 0x00000001
  #define DDRDATA0_CR_PIDFTDLY_Ch0PiDFTEn_DEF                          (0x00000000)
  #define DDRDATA0_CR_PIDFTDLY_Ch0PiDFTEn_HSH                          (0x01092018)

  #define DDRDATA0_CR_PIDFTDLY_Ch1PiDFTEn_OFF                          (10)
  #define DDRDATA0_CR_PIDFTDLY_Ch1PiDFTEn_WID                          ( 1)
  #define DDRDATA0_CR_PIDFTDLY_Ch1PiDFTEn_MSK                          (0x00000400)
  #define DDRDATA0_CR_PIDFTDLY_Ch1PiDFTEn_MIN                          (0)
  #define DDRDATA0_CR_PIDFTDLY_Ch1PiDFTEn_MAX                          (1) // 0x00000001
  #define DDRDATA0_CR_PIDFTDLY_Ch1PiDFTEn_DEF                          (0x00000000)
  #define DDRDATA0_CR_PIDFTDLY_Ch1PiDFTEn_HSH                          (0x010A2018)

  #define DDRDATA0_CR_PIDFTDLY_Spare_OFF                               (11)
  #define DDRDATA0_CR_PIDFTDLY_Spare_WID                               ( 4)
  #define DDRDATA0_CR_PIDFTDLY_Spare_MSK                               (0x00007800)
  #define DDRDATA0_CR_PIDFTDLY_Spare_MIN                               (0)
  #define DDRDATA0_CR_PIDFTDLY_Spare_MAX                               (15) // 0x0000000F
  #define DDRDATA0_CR_PIDFTDLY_Spare_DEF                               (0x00000000)
  #define DDRDATA0_CR_PIDFTDLY_Spare_HSH                               (0x040B2018)

  #define DDRDATA0_CR_PIDFTDLY_RefPiOvrd_OFF                           (15)
  #define DDRDATA0_CR_PIDFTDLY_RefPiOvrd_WID                           ( 1)
  #define DDRDATA0_CR_PIDFTDLY_RefPiOvrd_MSK                           (0x00008000)
  #define DDRDATA0_CR_PIDFTDLY_RefPiOvrd_MIN                           (0)
  #define DDRDATA0_CR_PIDFTDLY_RefPiOvrd_MAX                           (1) // 0x00000001
  #define DDRDATA0_CR_PIDFTDLY_RefPiOvrd_DEF                           (0x00000000)
  #define DDRDATA0_CR_PIDFTDLY_RefPiOvrd_HSH                           (0x010F2018)

  #define DDRDATA0_CR_PIDFTDLY_Rsvd_OFF                                (16)
  #define DDRDATA0_CR_PIDFTDLY_Rsvd_WID                                (16)
  #define DDRDATA0_CR_PIDFTDLY_Rsvd_MSK                                (0xFFFF0000)
  #define DDRDATA0_CR_PIDFTDLY_Rsvd_MIN                                (0)
  #define DDRDATA0_CR_PIDFTDLY_Rsvd_MAX                                (65535) // 0x0000FFFF
  #define DDRDATA0_CR_PIDFTDLY_Rsvd_DEF                                (0x00000000)
  #define DDRDATA0_CR_PIDFTDLY_Rsvd_HSH                                (0x10102018)

#define DDRDATA0_CR_DLLPITESTANDADC_REG                                (0x0000201C)

  #define DDRDATA0_CR_DLLPITESTANDADC_RunTest_OFF                      ( 0)
  #define DDRDATA0_CR_DLLPITESTANDADC_RunTest_WID                      ( 1)
  #define DDRDATA0_CR_DLLPITESTANDADC_RunTest_MSK                      (0x00000001)
  #define DDRDATA0_CR_DLLPITESTANDADC_RunTest_MIN                      (0)
  #define DDRDATA0_CR_DLLPITESTANDADC_RunTest_MAX                      (1) // 0x00000001
  #define DDRDATA0_CR_DLLPITESTANDADC_RunTest_DEF                      (0x00000000)
  #define DDRDATA0_CR_DLLPITESTANDADC_RunTest_HSH                      (0x0100201C)

  #define DDRDATA0_CR_DLLPITESTANDADC_Load_OFF                         ( 1)
  #define DDRDATA0_CR_DLLPITESTANDADC_Load_WID                         ( 1)
  #define DDRDATA0_CR_DLLPITESTANDADC_Load_MSK                         (0x00000002)
  #define DDRDATA0_CR_DLLPITESTANDADC_Load_MIN                         (0)
  #define DDRDATA0_CR_DLLPITESTANDADC_Load_MAX                         (1) // 0x00000001
  #define DDRDATA0_CR_DLLPITESTANDADC_Load_DEF                         (0x00000000)
  #define DDRDATA0_CR_DLLPITESTANDADC_Load_HSH                         (0x0101201C)

  #define DDRDATA0_CR_DLLPITESTANDADC_ModeHVM_OFF                      ( 2)
  #define DDRDATA0_CR_DLLPITESTANDADC_ModeHVM_WID                      ( 1)
  #define DDRDATA0_CR_DLLPITESTANDADC_ModeHVM_MSK                      (0x00000004)
  #define DDRDATA0_CR_DLLPITESTANDADC_ModeHVM_MIN                      (0)
  #define DDRDATA0_CR_DLLPITESTANDADC_ModeHVM_MAX                      (1) // 0x00000001
  #define DDRDATA0_CR_DLLPITESTANDADC_ModeHVM_DEF                      (0x00000000)
  #define DDRDATA0_CR_DLLPITESTANDADC_ModeHVM_HSH                      (0x0102201C)

  #define DDRDATA0_CR_DLLPITESTANDADC_ModeDV_OFF                       ( 3)
  #define DDRDATA0_CR_DLLPITESTANDADC_ModeDV_WID                       ( 1)
  #define DDRDATA0_CR_DLLPITESTANDADC_ModeDV_MSK                       (0x00000008)
  #define DDRDATA0_CR_DLLPITESTANDADC_ModeDV_MIN                       (0)
  #define DDRDATA0_CR_DLLPITESTANDADC_ModeDV_MAX                       (1) // 0x00000001
  #define DDRDATA0_CR_DLLPITESTANDADC_ModeDV_DEF                       (0x00000000)
  #define DDRDATA0_CR_DLLPITESTANDADC_ModeDV_HSH                       (0x0103201C)

  #define DDRDATA0_CR_DLLPITESTANDADC_CalCfdl_OFF                      ( 4)
  #define DDRDATA0_CR_DLLPITESTANDADC_CalCfdl_WID                      ( 1)
  #define DDRDATA0_CR_DLLPITESTANDADC_CalCfdl_MSK                      (0x00000010)
  #define DDRDATA0_CR_DLLPITESTANDADC_CalCfdl_MIN                      (0)
  #define DDRDATA0_CR_DLLPITESTANDADC_CalCfdl_MAX                      (1) // 0x00000001
  #define DDRDATA0_CR_DLLPITESTANDADC_CalCfdl_DEF                      (0x00000000)
  #define DDRDATA0_CR_DLLPITESTANDADC_CalCfdl_HSH                      (0x0104201C)

  #define DDRDATA0_CR_DLLPITESTANDADC_LoadCount_OFF                    ( 5)
  #define DDRDATA0_CR_DLLPITESTANDADC_LoadCount_WID                    (10)
  #define DDRDATA0_CR_DLLPITESTANDADC_LoadCount_MSK                    (0x00007FE0)
  #define DDRDATA0_CR_DLLPITESTANDADC_LoadCount_MIN                    (0)
  #define DDRDATA0_CR_DLLPITESTANDADC_LoadCount_MAX                    (1023) // 0x000003FF
  #define DDRDATA0_CR_DLLPITESTANDADC_LoadCount_DEF                    (0x00000000)
  #define DDRDATA0_CR_DLLPITESTANDADC_LoadCount_HSH                    (0x0A05201C)

  #define DDRDATA0_CR_DLLPITESTANDADC_CountStatus_OFF                  (15)
  #define DDRDATA0_CR_DLLPITESTANDADC_CountStatus_WID                  (10)
  #define DDRDATA0_CR_DLLPITESTANDADC_CountStatus_MSK                  (0x01FF8000)
  #define DDRDATA0_CR_DLLPITESTANDADC_CountStatus_MIN                  (0)
  #define DDRDATA0_CR_DLLPITESTANDADC_CountStatus_MAX                  (1023) // 0x000003FF
  #define DDRDATA0_CR_DLLPITESTANDADC_CountStatus_DEF                  (0x00000000)
  #define DDRDATA0_CR_DLLPITESTANDADC_CountStatus_HSH                  (0x0A0F201C)

  #define DDRDATA0_CR_DLLPITESTANDADC_ModeADC_OFF                      (25)
  #define DDRDATA0_CR_DLLPITESTANDADC_ModeADC_WID                      ( 1)
  #define DDRDATA0_CR_DLLPITESTANDADC_ModeADC_MSK                      (0x02000000)
  #define DDRDATA0_CR_DLLPITESTANDADC_ModeADC_MIN                      (0)
  #define DDRDATA0_CR_DLLPITESTANDADC_ModeADC_MAX                      (1) // 0x00000001
  #define DDRDATA0_CR_DLLPITESTANDADC_ModeADC_DEF                      (0x00000000)
  #define DDRDATA0_CR_DLLPITESTANDADC_ModeADC_HSH                      (0x0119201C)

  #define DDRDATA0_CR_DLLPITESTANDADC_ADCClkDiv_OFF                    (26)
  #define DDRDATA0_CR_DLLPITESTANDADC_ADCClkDiv_WID                    ( 2)
  #define DDRDATA0_CR_DLLPITESTANDADC_ADCClkDiv_MSK                    (0x0C000000)
  #define DDRDATA0_CR_DLLPITESTANDADC_ADCClkDiv_MIN                    (0)
  #define DDRDATA0_CR_DLLPITESTANDADC_ADCClkDiv_MAX                    (3) // 0x00000003
  #define DDRDATA0_CR_DLLPITESTANDADC_ADCClkDiv_DEF                    (0x00000000)
  #define DDRDATA0_CR_DLLPITESTANDADC_ADCClkDiv_HSH                    (0x021A201C)

  #define DDRDATA0_CR_DLLPITESTANDADC_ADCDdrChanSel_OFF                (28)
  #define DDRDATA0_CR_DLLPITESTANDADC_ADCDdrChanSel_WID                ( 1)
  #define DDRDATA0_CR_DLLPITESTANDADC_ADCDdrChanSel_MSK                (0x10000000)
  #define DDRDATA0_CR_DLLPITESTANDADC_ADCDdrChanSel_MIN                (0)
  #define DDRDATA0_CR_DLLPITESTANDADC_ADCDdrChanSel_MAX                (1) // 0x00000001
  #define DDRDATA0_CR_DLLPITESTANDADC_ADCDdrChanSel_DEF                (0x00000000)
  #define DDRDATA0_CR_DLLPITESTANDADC_ADCDdrChanSel_HSH                (0x011C201C)

  #define DDRDATA0_CR_DLLPITESTANDADC_ADCChopEn_OFF                    (29)
  #define DDRDATA0_CR_DLLPITESTANDADC_ADCChopEn_WID                    ( 1)
  #define DDRDATA0_CR_DLLPITESTANDADC_ADCChopEn_MSK                    (0x20000000)
  #define DDRDATA0_CR_DLLPITESTANDADC_ADCChopEn_MIN                    (0)
  #define DDRDATA0_CR_DLLPITESTANDADC_ADCChopEn_MAX                    (1) // 0x00000001
  #define DDRDATA0_CR_DLLPITESTANDADC_ADCChopEn_DEF                    (0x00000000)
  #define DDRDATA0_CR_DLLPITESTANDADC_ADCChopEn_HSH                    (0x011D201C)

  #define DDRDATA0_CR_DLLPITESTANDADC_ADCDone_OFF                      (30)
  #define DDRDATA0_CR_DLLPITESTANDADC_ADCDone_WID                      ( 1)
  #define DDRDATA0_CR_DLLPITESTANDADC_ADCDone_MSK                      (0x40000000)
  #define DDRDATA0_CR_DLLPITESTANDADC_ADCDone_MIN                      (0)
  #define DDRDATA0_CR_DLLPITESTANDADC_ADCDone_MAX                      (1) // 0x00000001
  #define DDRDATA0_CR_DLLPITESTANDADC_ADCDone_DEF                      (0x00000000)
  #define DDRDATA0_CR_DLLPITESTANDADC_ADCDone_HSH                      (0x011E201C)

  #define DDRDATA0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF             (31)
  #define DDRDATA0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID             ( 1)
  #define DDRDATA0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK             (0x80000000)
  #define DDRDATA0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN             (0)
  #define DDRDATA0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX             (1) // 0x00000001
  #define DDRDATA0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF             (0x00000000)
  #define DDRDATA0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH             (0x011F201C)

#define DDRDATA0_CR_DLLSTATUS_REG                                      (0x00002020)

  #define DDRDATA0_CR_DLLSTATUS_DetrmLockStat_OFF                      ( 0)
  #define DDRDATA0_CR_DLLSTATUS_DetrmLockStat_WID                      ( 1)
  #define DDRDATA0_CR_DLLSTATUS_DetrmLockStat_MSK                      (0x00000001)
  #define DDRDATA0_CR_DLLSTATUS_DetrmLockStat_MIN                      (0)
  #define DDRDATA0_CR_DLLSTATUS_DetrmLockStat_MAX                      (1) // 0x00000001
  #define DDRDATA0_CR_DLLSTATUS_DetrmLockStat_DEF                      (0x00000000)
  #define DDRDATA0_CR_DLLSTATUS_DetrmLockStat_HSH                      (0x01002020)

  #define DDRDATA0_CR_DLLSTATUS_FuncLockStat_OFF                       ( 1)
  #define DDRDATA0_CR_DLLSTATUS_FuncLockStat_WID                       ( 1)
  #define DDRDATA0_CR_DLLSTATUS_FuncLockStat_MSK                       (0x00000002)
  #define DDRDATA0_CR_DLLSTATUS_FuncLockStat_MIN                       (0)
  #define DDRDATA0_CR_DLLSTATUS_FuncLockStat_MAX                       (1) // 0x00000001
  #define DDRDATA0_CR_DLLSTATUS_FuncLockStat_DEF                       (0x00000000)
  #define DDRDATA0_CR_DLLSTATUS_FuncLockStat_HSH                       (0x01012020)

  #define DDRDATA0_CR_DLLSTATUS_Lock_OFF                               ( 2)
  #define DDRDATA0_CR_DLLSTATUS_Lock_WID                               ( 1)
  #define DDRDATA0_CR_DLLSTATUS_Lock_MSK                               (0x00000004)
  #define DDRDATA0_CR_DLLSTATUS_Lock_MIN                               (0)
  #define DDRDATA0_CR_DLLSTATUS_Lock_MAX                               (1) // 0x00000001
  #define DDRDATA0_CR_DLLSTATUS_Lock_DEF                               (0x00000000)
  #define DDRDATA0_CR_DLLSTATUS_Lock_HSH                               (0x01022020)

  #define DDRDATA0_CR_DLLSTATUS_Timeout_OFF                            ( 3)
  #define DDRDATA0_CR_DLLSTATUS_Timeout_WID                            ( 1)
  #define DDRDATA0_CR_DLLSTATUS_Timeout_MSK                            (0x00000008)
  #define DDRDATA0_CR_DLLSTATUS_Timeout_MIN                            (0)
  #define DDRDATA0_CR_DLLSTATUS_Timeout_MAX                            (1) // 0x00000001
  #define DDRDATA0_CR_DLLSTATUS_Timeout_DEF                            (0x00000000)
  #define DDRDATA0_CR_DLLSTATUS_Timeout_HSH                            (0x01032020)

  #define DDRDATA0_CR_DLLSTATUS_DllReset_OFF                           ( 4)
  #define DDRDATA0_CR_DLLSTATUS_DllReset_WID                           ( 1)
  #define DDRDATA0_CR_DLLSTATUS_DllReset_MSK                           (0x00000010)
  #define DDRDATA0_CR_DLLSTATUS_DllReset_MIN                           (0)
  #define DDRDATA0_CR_DLLSTATUS_DllReset_MAX                           (1) // 0x00000001
  #define DDRDATA0_CR_DLLSTATUS_DllReset_DEF                           (0x00000000)
  #define DDRDATA0_CR_DLLSTATUS_DllReset_HSH                           (0x01042020)

  #define DDRDATA0_CR_DLLSTATUS_LongLockStat_OFF                       ( 5)
  #define DDRDATA0_CR_DLLSTATUS_LongLockStat_WID                       ( 1)
  #define DDRDATA0_CR_DLLSTATUS_LongLockStat_MSK                       (0x00000020)
  #define DDRDATA0_CR_DLLSTATUS_LongLockStat_MIN                       (0)
  #define DDRDATA0_CR_DLLSTATUS_LongLockStat_MAX                       (1) // 0x00000001
  #define DDRDATA0_CR_DLLSTATUS_LongLockStat_DEF                       (0x00000000)
  #define DDRDATA0_CR_DLLSTATUS_LongLockStat_HSH                       (0x01052020)

  #define DDRDATA0_CR_DLLSTATUS_EarlyLockStat_OFF                      ( 6)
  #define DDRDATA0_CR_DLLSTATUS_EarlyLockStat_WID                      ( 1)
  #define DDRDATA0_CR_DLLSTATUS_EarlyLockStat_MSK                      (0x00000040)
  #define DDRDATA0_CR_DLLSTATUS_EarlyLockStat_MIN                      (0)
  #define DDRDATA0_CR_DLLSTATUS_EarlyLockStat_MAX                      (1) // 0x00000001
  #define DDRDATA0_CR_DLLSTATUS_EarlyLockStat_DEF                      (0x00000000)
  #define DDRDATA0_CR_DLLSTATUS_EarlyLockStat_HSH                      (0x01062020)

  #define DDRDATA0_CR_DLLSTATUS_NormalMode_NotWkLock_OFF               ( 7)
  #define DDRDATA0_CR_DLLSTATUS_NormalMode_NotWkLock_WID               ( 1)
  #define DDRDATA0_CR_DLLSTATUS_NormalMode_NotWkLock_MSK               (0x00000080)
  #define DDRDATA0_CR_DLLSTATUS_NormalMode_NotWkLock_MIN               (0)
  #define DDRDATA0_CR_DLLSTATUS_NormalMode_NotWkLock_MAX               (1) // 0x00000001
  #define DDRDATA0_CR_DLLSTATUS_NormalMode_NotWkLock_DEF               (0x00000000)
  #define DDRDATA0_CR_DLLSTATUS_NormalMode_NotWkLock_HSH               (0x01072020)

  #define DDRDATA0_CR_DLLSTATUS_ADCout_OFF                             ( 8)
  #define DDRDATA0_CR_DLLSTATUS_ADCout_WID                             (10)
  #define DDRDATA0_CR_DLLSTATUS_ADCout_MSK                             (0x0003FF00)
  #define DDRDATA0_CR_DLLSTATUS_ADCout_MIN                             (0)
  #define DDRDATA0_CR_DLLSTATUS_ADCout_MAX                             (1023) // 0x000003FF
  #define DDRDATA0_CR_DLLSTATUS_ADCout_DEF                             (0x00000000)
  #define DDRDATA0_CR_DLLSTATUS_ADCout_HSH                             (0x0A082020)

  #define DDRDATA0_CR_DLLSTATUS_ADCStatus_OFF                          (18)
  #define DDRDATA0_CR_DLLSTATUS_ADCStatus_WID                          ( 1)
  #define DDRDATA0_CR_DLLSTATUS_ADCStatus_MSK                          (0x00040000)
  #define DDRDATA0_CR_DLLSTATUS_ADCStatus_MIN                          (0)
  #define DDRDATA0_CR_DLLSTATUS_ADCStatus_MAX                          (1) // 0x00000001
  #define DDRDATA0_CR_DLLSTATUS_ADCStatus_DEF                          (0x00000000)
  #define DDRDATA0_CR_DLLSTATUS_ADCStatus_HSH                          (0x01122020)

  #define DDRDATA0_CR_DLLSTATUS_pilags_OFF                             (19)
  #define DDRDATA0_CR_DLLSTATUS_pilags_WID                             ( 1)
  #define DDRDATA0_CR_DLLSTATUS_pilags_MSK                             (0x00080000)
  #define DDRDATA0_CR_DLLSTATUS_pilags_MIN                             (0)
  #define DDRDATA0_CR_DLLSTATUS_pilags_MAX                             (1) // 0x00000001
  #define DDRDATA0_CR_DLLSTATUS_pilags_DEF                             (0x00000000)
  #define DDRDATA0_CR_DLLSTATUS_pilags_HSH                             (0x01132020)

  #define DDRDATA0_CR_DLLSTATUS_spare_OFF                              (20)
  #define DDRDATA0_CR_DLLSTATUS_spare_WID                              (12)
  #define DDRDATA0_CR_DLLSTATUS_spare_MSK                              (0xFFF00000)
  #define DDRDATA0_CR_DLLSTATUS_spare_MIN                              (0)
  #define DDRDATA0_CR_DLLSTATUS_spare_MAX                              (4095) // 0x00000FFF
  #define DDRDATA0_CR_DLLSTATUS_spare_DEF                              (0x00000000)
  #define DDRDATA0_CR_DLLSTATUS_spare_HSH                              (0x0C142020)

#define DDRDATA0_CR_DLLDCMCTL_REG                                      (0x00002024)

  #define DDRDATA0_CR_DLLDCMCTL_start_OFF                              ( 0)
  #define DDRDATA0_CR_DLLDCMCTL_start_WID                              ( 1)
  #define DDRDATA0_CR_DLLDCMCTL_start_MSK                              (0x00000001)
  #define DDRDATA0_CR_DLLDCMCTL_start_MIN                              (0)
  #define DDRDATA0_CR_DLLDCMCTL_start_MAX                              (1) // 0x00000001
  #define DDRDATA0_CR_DLLDCMCTL_start_DEF                              (0x00000000)
  #define DDRDATA0_CR_DLLDCMCTL_start_HSH                              (0x01002024)

  #define DDRDATA0_CR_DLLDCMCTL_clken_OFF                              ( 1)
  #define DDRDATA0_CR_DLLDCMCTL_clken_WID                              ( 1)
  #define DDRDATA0_CR_DLLDCMCTL_clken_MSK                              (0x00000002)
  #define DDRDATA0_CR_DLLDCMCTL_clken_MIN                              (0)
  #define DDRDATA0_CR_DLLDCMCTL_clken_MAX                              (1) // 0x00000001
  #define DDRDATA0_CR_DLLDCMCTL_clken_DEF                              (0x00000000)
  #define DDRDATA0_CR_DLLDCMCTL_clken_HSH                              (0x01012024)

  #define DDRDATA0_CR_DLLDCMCTL_dcm_dccctl_en_OFF                      ( 2)
  #define DDRDATA0_CR_DLLDCMCTL_dcm_dccctl_en_WID                      ( 1)
  #define DDRDATA0_CR_DLLDCMCTL_dcm_dccctl_en_MSK                      (0x00000004)
  #define DDRDATA0_CR_DLLDCMCTL_dcm_dccctl_en_MIN                      (0)
  #define DDRDATA0_CR_DLLDCMCTL_dcm_dccctl_en_MAX                      (1) // 0x00000001
  #define DDRDATA0_CR_DLLDCMCTL_dcm_dccctl_en_DEF                      (0x00000000)
  #define DDRDATA0_CR_DLLDCMCTL_dcm_dccctl_en_HSH                      (0x01022024)

  #define DDRDATA0_CR_DLLDCMCTL_dccctl_OFF                             ( 3)
  #define DDRDATA0_CR_DLLDCMCTL_dccctl_WID                             ( 4)
  #define DDRDATA0_CR_DLLDCMCTL_dccctl_MSK                             (0x00000078)
  #define DDRDATA0_CR_DLLDCMCTL_dccctl_MIN                             (0)
  #define DDRDATA0_CR_DLLDCMCTL_dccctl_MAX                             (15) // 0x0000000F
  #define DDRDATA0_CR_DLLDCMCTL_dccctl_DEF                             (0x00000000)
  #define DDRDATA0_CR_DLLDCMCTL_dccctl_HSH                             (0x04032024)

  #define DDRDATA0_CR_DLLDCMCTL_duration_OFF                           ( 7)
  #define DDRDATA0_CR_DLLDCMCTL_duration_WID                           ( 3)
  #define DDRDATA0_CR_DLLDCMCTL_duration_MSK                           (0x00000380)
  #define DDRDATA0_CR_DLLDCMCTL_duration_MIN                           (0)
  #define DDRDATA0_CR_DLLDCMCTL_duration_MAX                           (7) // 0x00000007
  #define DDRDATA0_CR_DLLDCMCTL_duration_DEF                           (0x00000000)
  #define DDRDATA0_CR_DLLDCMCTL_duration_HSH                           (0x03072024)

  #define DDRDATA0_CR_DLLDCMCTL_dcm_done_OFF                           (10)
  #define DDRDATA0_CR_DLLDCMCTL_dcm_done_WID                           ( 1)
  #define DDRDATA0_CR_DLLDCMCTL_dcm_done_MSK                           (0x00000400)
  #define DDRDATA0_CR_DLLDCMCTL_dcm_done_MIN                           (0)
  #define DDRDATA0_CR_DLLDCMCTL_dcm_done_MAX                           (1) // 0x00000001
  #define DDRDATA0_CR_DLLDCMCTL_dcm_done_DEF                           (0x00000000)
  #define DDRDATA0_CR_DLLDCMCTL_dcm_done_HSH                           (0x010A2024)

  #define DDRDATA0_CR_DLLDCMCTL_dcm_results_OFF                        (11)
  #define DDRDATA0_CR_DLLDCMCTL_dcm_results_WID                        (15)
  #define DDRDATA0_CR_DLLDCMCTL_dcm_results_MSK                        (0x03FFF800)
  #define DDRDATA0_CR_DLLDCMCTL_dcm_results_MIN                        (0)
  #define DDRDATA0_CR_DLLDCMCTL_dcm_results_MAX                        (32767) // 0x00007FFF
  #define DDRDATA0_CR_DLLDCMCTL_dcm_results_DEF                        (0x00000000)
  #define DDRDATA0_CR_DLLDCMCTL_dcm_results_HSH                        (0x0F0B2024)

  #define DDRDATA0_CR_DLLDCMCTL_spare0_OFF                             (26)
  #define DDRDATA0_CR_DLLDCMCTL_spare0_WID                             ( 6)
  #define DDRDATA0_CR_DLLDCMCTL_spare0_MSK                             (0xFC000000)
  #define DDRDATA0_CR_DLLDCMCTL_spare0_MIN                             (0)
  #define DDRDATA0_CR_DLLDCMCTL_spare0_MAX                             (63) // 0x0000003F
  #define DDRDATA0_CR_DLLDCMCTL_spare0_DEF                             (0x00000000)
  #define DDRDATA0_CR_DLLDCMCTL_spare0_HSH                             (0x061A2024)

#define DDRDATA1_CR_MASTERDLLCFG_REG                                   (0x00002080)

  #define DDRDATA1_CR_MASTERDLLCFG_LockThresh_OFF                      ( 0)
  #define DDRDATA1_CR_MASTERDLLCFG_LockThresh_WID                      ( 3)
  #define DDRDATA1_CR_MASTERDLLCFG_LockThresh_MSK                      (0x00000007)
  #define DDRDATA1_CR_MASTERDLLCFG_LockThresh_MIN                      (0)
  #define DDRDATA1_CR_MASTERDLLCFG_LockThresh_MAX                      (7) // 0x00000007
  #define DDRDATA1_CR_MASTERDLLCFG_LockThresh_DEF                      (0x00000004)
  #define DDRDATA1_CR_MASTERDLLCFG_LockThresh_HSH                      (0x03002080)

  #define DDRDATA1_CR_MASTERDLLCFG_LockCtr_OFF                         ( 3)
  #define DDRDATA1_CR_MASTERDLLCFG_LockCtr_WID                         ( 2)
  #define DDRDATA1_CR_MASTERDLLCFG_LockCtr_MSK                         (0x00000018)
  #define DDRDATA1_CR_MASTERDLLCFG_LockCtr_MIN                         (0)
  #define DDRDATA1_CR_MASTERDLLCFG_LockCtr_MAX                         (3) // 0x00000003
  #define DDRDATA1_CR_MASTERDLLCFG_LockCtr_DEF                         (0x00000000)
  #define DDRDATA1_CR_MASTERDLLCFG_LockCtr_HSH                         (0x02032080)

  #define DDRDATA1_CR_MASTERDLLCFG_VctrlDischRate_OFF                  ( 5)
  #define DDRDATA1_CR_MASTERDLLCFG_VctrlDischRate_WID                  ( 2)
  #define DDRDATA1_CR_MASTERDLLCFG_VctrlDischRate_MSK                  (0x00000060)
  #define DDRDATA1_CR_MASTERDLLCFG_VctrlDischRate_MIN                  (0)
  #define DDRDATA1_CR_MASTERDLLCFG_VctrlDischRate_MAX                  (3) // 0x00000003
  #define DDRDATA1_CR_MASTERDLLCFG_VctrlDischRate_DEF                  (0x00000000)
  #define DDRDATA1_CR_MASTERDLLCFG_VctrlDischRate_HSH                  (0x02052080)

  #define DDRDATA1_CR_MASTERDLLCFG_SelVctrlHi_OFF                      ( 7)
  #define DDRDATA1_CR_MASTERDLLCFG_SelVctrlHi_WID                      ( 1)
  #define DDRDATA1_CR_MASTERDLLCFG_SelVctrlHi_MSK                      (0x00000080)
  #define DDRDATA1_CR_MASTERDLLCFG_SelVctrlHi_MIN                      (0)
  #define DDRDATA1_CR_MASTERDLLCFG_SelVctrlHi_MAX                      (1) // 0x00000001
  #define DDRDATA1_CR_MASTERDLLCFG_SelVctrlHi_DEF                      (0x00000000)
  #define DDRDATA1_CR_MASTERDLLCFG_SelVctrlHi_HSH                      (0x01072080)

  #define DDRDATA1_CR_MASTERDLLCFG_StartupCntSel_OFF                   ( 8)
  #define DDRDATA1_CR_MASTERDLLCFG_StartupCntSel_WID                   ( 1)
  #define DDRDATA1_CR_MASTERDLLCFG_StartupCntSel_MSK                   (0x00000100)
  #define DDRDATA1_CR_MASTERDLLCFG_StartupCntSel_MIN                   (0)
  #define DDRDATA1_CR_MASTERDLLCFG_StartupCntSel_MAX                   (1) // 0x00000001
  #define DDRDATA1_CR_MASTERDLLCFG_StartupCntSel_DEF                   (0x00000000)
  #define DDRDATA1_CR_MASTERDLLCFG_StartupCntSel_HSH                   (0x01082080)

  #define DDRDATA1_CR_MASTERDLLCFG_LockSel_OFF                         ( 9)
  #define DDRDATA1_CR_MASTERDLLCFG_LockSel_WID                         ( 2)
  #define DDRDATA1_CR_MASTERDLLCFG_LockSel_MSK                         (0x00000600)
  #define DDRDATA1_CR_MASTERDLLCFG_LockSel_MIN                         (0)
  #define DDRDATA1_CR_MASTERDLLCFG_LockSel_MAX                         (3) // 0x00000003
  #define DDRDATA1_CR_MASTERDLLCFG_LockSel_DEF                         (0x00000000)
  #define DDRDATA1_CR_MASTERDLLCFG_LockSel_HSH                         (0x02092080)

  #define DDRDATA1_CR_MASTERDLLCFG_RstOvrd_OFF                         (11)
  #define DDRDATA1_CR_MASTERDLLCFG_RstOvrd_WID                         ( 1)
  #define DDRDATA1_CR_MASTERDLLCFG_RstOvrd_MSK                         (0x00000800)
  #define DDRDATA1_CR_MASTERDLLCFG_RstOvrd_MIN                         (0)
  #define DDRDATA1_CR_MASTERDLLCFG_RstOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA1_CR_MASTERDLLCFG_RstOvrd_DEF                         (0x00000000)
  #define DDRDATA1_CR_MASTERDLLCFG_RstOvrd_HSH                         (0x010B2080)

  #define DDRDATA1_CR_MASTERDLLCFG_SelRstOvrd_OFF                      (12)
  #define DDRDATA1_CR_MASTERDLLCFG_SelRstOvrd_WID                      ( 1)
  #define DDRDATA1_CR_MASTERDLLCFG_SelRstOvrd_MSK                      (0x00001000)
  #define DDRDATA1_CR_MASTERDLLCFG_SelRstOvrd_MIN                      (0)
  #define DDRDATA1_CR_MASTERDLLCFG_SelRstOvrd_MAX                      (1) // 0x00000001
  #define DDRDATA1_CR_MASTERDLLCFG_SelRstOvrd_DEF                      (0x00000000)
  #define DDRDATA1_CR_MASTERDLLCFG_SelRstOvrd_HSH                      (0x010C2080)

  #define DDRDATA1_CR_MASTERDLLCFG_TimeOutOvrd_OFF                     (13)
  #define DDRDATA1_CR_MASTERDLLCFG_TimeOutOvrd_WID                     ( 1)
  #define DDRDATA1_CR_MASTERDLLCFG_TimeOutOvrd_MSK                     (0x00002000)
  #define DDRDATA1_CR_MASTERDLLCFG_TimeOutOvrd_MIN                     (0)
  #define DDRDATA1_CR_MASTERDLLCFG_TimeOutOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA1_CR_MASTERDLLCFG_TimeOutOvrd_DEF                     (0x00000000)
  #define DDRDATA1_CR_MASTERDLLCFG_TimeOutOvrd_HSH                     (0x010D2080)

  #define DDRDATA1_CR_MASTERDLLCFG_SelTimeOutOvrd_OFF                  (14)
  #define DDRDATA1_CR_MASTERDLLCFG_SelTimeOutOvrd_WID                  ( 1)
  #define DDRDATA1_CR_MASTERDLLCFG_SelTimeOutOvrd_MSK                  (0x00004000)
  #define DDRDATA1_CR_MASTERDLLCFG_SelTimeOutOvrd_MIN                  (0)
  #define DDRDATA1_CR_MASTERDLLCFG_SelTimeOutOvrd_MAX                  (1) // 0x00000001
  #define DDRDATA1_CR_MASTERDLLCFG_SelTimeOutOvrd_DEF                  (0x00000000)
  #define DDRDATA1_CR_MASTERDLLCFG_SelTimeOutOvrd_HSH                  (0x010E2080)

  #define DDRDATA1_CR_MASTERDLLCFG_ClkGateOvrd_OFF                     (15)
  #define DDRDATA1_CR_MASTERDLLCFG_ClkGateOvrd_WID                     ( 1)
  #define DDRDATA1_CR_MASTERDLLCFG_ClkGateOvrd_MSK                     (0x00008000)
  #define DDRDATA1_CR_MASTERDLLCFG_ClkGateOvrd_MIN                     (0)
  #define DDRDATA1_CR_MASTERDLLCFG_ClkGateOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA1_CR_MASTERDLLCFG_ClkGateOvrd_DEF                     (0x00000000)
  #define DDRDATA1_CR_MASTERDLLCFG_ClkGateOvrd_HSH                     (0x010F2080)

  #define DDRDATA1_CR_MASTERDLLCFG_LockOvrd_OFF                        (16)
  #define DDRDATA1_CR_MASTERDLLCFG_LockOvrd_WID                        ( 1)
  #define DDRDATA1_CR_MASTERDLLCFG_LockOvrd_MSK                        (0x00010000)
  #define DDRDATA1_CR_MASTERDLLCFG_LockOvrd_MIN                        (0)
  #define DDRDATA1_CR_MASTERDLLCFG_LockOvrd_MAX                        (1) // 0x00000001
  #define DDRDATA1_CR_MASTERDLLCFG_LockOvrd_DEF                        (0x00000000)
  #define DDRDATA1_CR_MASTERDLLCFG_LockOvrd_HSH                        (0x01102080)

  #define DDRDATA1_CR_MASTERDLLCFG_SelLockOvrd_OFF                     (17)
  #define DDRDATA1_CR_MASTERDLLCFG_SelLockOvrd_WID                     ( 1)
  #define DDRDATA1_CR_MASTERDLLCFG_SelLockOvrd_MSK                     (0x00020000)
  #define DDRDATA1_CR_MASTERDLLCFG_SelLockOvrd_MIN                     (0)
  #define DDRDATA1_CR_MASTERDLLCFG_SelLockOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA1_CR_MASTERDLLCFG_SelLockOvrd_DEF                     (0x00000000)
  #define DDRDATA1_CR_MASTERDLLCFG_SelLockOvrd_HSH                     (0x01112080)

  #define DDRDATA1_CR_MASTERDLLCFG_OpenLoopOvrd_OFF                    (18)
  #define DDRDATA1_CR_MASTERDLLCFG_OpenLoopOvrd_WID                    ( 1)
  #define DDRDATA1_CR_MASTERDLLCFG_OpenLoopOvrd_MSK                    (0x00040000)
  #define DDRDATA1_CR_MASTERDLLCFG_OpenLoopOvrd_MIN                    (0)
  #define DDRDATA1_CR_MASTERDLLCFG_OpenLoopOvrd_MAX                    (1) // 0x00000001
  #define DDRDATA1_CR_MASTERDLLCFG_OpenLoopOvrd_DEF                    (0x00000000)
  #define DDRDATA1_CR_MASTERDLLCFG_OpenLoopOvrd_HSH                    (0x01122080)

  #define DDRDATA1_CR_MASTERDLLCFG_SelOpenLoopOvrd_OFF                 (19)
  #define DDRDATA1_CR_MASTERDLLCFG_SelOpenLoopOvrd_WID                 ( 1)
  #define DDRDATA1_CR_MASTERDLLCFG_SelOpenLoopOvrd_MSK                 (0x00080000)
  #define DDRDATA1_CR_MASTERDLLCFG_SelOpenLoopOvrd_MIN                 (0)
  #define DDRDATA1_CR_MASTERDLLCFG_SelOpenLoopOvrd_MAX                 (1) // 0x00000001
  #define DDRDATA1_CR_MASTERDLLCFG_SelOpenLoopOvrd_DEF                 (0x00000000)
  #define DDRDATA1_CR_MASTERDLLCFG_SelOpenLoopOvrd_HSH                 (0x01132080)

  #define DDRDATA1_CR_MASTERDLLCFG_WkLockEnOvrd_OFF                    (20)
  #define DDRDATA1_CR_MASTERDLLCFG_WkLockEnOvrd_WID                    ( 1)
  #define DDRDATA1_CR_MASTERDLLCFG_WkLockEnOvrd_MSK                    (0x00100000)
  #define DDRDATA1_CR_MASTERDLLCFG_WkLockEnOvrd_MIN                    (0)
  #define DDRDATA1_CR_MASTERDLLCFG_WkLockEnOvrd_MAX                    (1) // 0x00000001
  #define DDRDATA1_CR_MASTERDLLCFG_WkLockEnOvrd_DEF                    (0x00000000)
  #define DDRDATA1_CR_MASTERDLLCFG_WkLockEnOvrd_HSH                    (0x01142080)

  #define DDRDATA1_CR_MASTERDLLCFG_SelWkLockEnOvrd_OFF                 (21)
  #define DDRDATA1_CR_MASTERDLLCFG_SelWkLockEnOvrd_WID                 ( 1)
  #define DDRDATA1_CR_MASTERDLLCFG_SelWkLockEnOvrd_MSK                 (0x00200000)
  #define DDRDATA1_CR_MASTERDLLCFG_SelWkLockEnOvrd_MIN                 (0)
  #define DDRDATA1_CR_MASTERDLLCFG_SelWkLockEnOvrd_MAX                 (1) // 0x00000001
  #define DDRDATA1_CR_MASTERDLLCFG_SelWkLockEnOvrd_DEF                 (0x00000000)
  #define DDRDATA1_CR_MASTERDLLCFG_SelWkLockEnOvrd_HSH                 (0x01152080)

  #define DDRDATA1_CR_MASTERDLLCFG_CfdlDis_OFF                         (22)
  #define DDRDATA1_CR_MASTERDLLCFG_CfdlDis_WID                         ( 1)
  #define DDRDATA1_CR_MASTERDLLCFG_CfdlDis_MSK                         (0x00400000)
  #define DDRDATA1_CR_MASTERDLLCFG_CfdlDis_MIN                         (0)
  #define DDRDATA1_CR_MASTERDLLCFG_CfdlDis_MAX                         (1) // 0x00000001
  #define DDRDATA1_CR_MASTERDLLCFG_CfdlDis_DEF                         (0x00000000)
  #define DDRDATA1_CR_MASTERDLLCFG_CfdlDis_HSH                         (0x01162080)

  #define DDRDATA1_CR_MASTERDLLCFG_DftEn_OFF                           (23)
  #define DDRDATA1_CR_MASTERDLLCFG_DftEn_WID                           ( 1)
  #define DDRDATA1_CR_MASTERDLLCFG_DftEn_MSK                           (0x00800000)
  #define DDRDATA1_CR_MASTERDLLCFG_DftEn_MIN                           (0)
  #define DDRDATA1_CR_MASTERDLLCFG_DftEn_MAX                           (1) // 0x00000001
  #define DDRDATA1_CR_MASTERDLLCFG_DftEn_DEF                           (0x00000000)
  #define DDRDATA1_CR_MASTERDLLCFG_DftEn_HSH                           (0x01172080)

  #define DDRDATA1_CR_MASTERDLLCFG_spare0_OFF                          (24)
  #define DDRDATA1_CR_MASTERDLLCFG_spare0_WID                          ( 8)
  #define DDRDATA1_CR_MASTERDLLCFG_spare0_MSK                          (0xFF000000)
  #define DDRDATA1_CR_MASTERDLLCFG_spare0_MIN                          (0)
  #define DDRDATA1_CR_MASTERDLLCFG_spare0_MAX                          (255) // 0x000000FF
  #define DDRDATA1_CR_MASTERDLLCFG_spare0_DEF                          (0x00000000)
  #define DDRDATA1_CR_MASTERDLLCFG_spare0_HSH                          (0x08182080)

#define DDRDATA1_CR_CBTUNE0_REG                                        (0x00002084)

  #define DDRDATA1_CR_CBTUNE0_DllBWEn_OFF                              ( 0)
  #define DDRDATA1_CR_CBTUNE0_DllBWEn_WID                              (32)
  #define DDRDATA1_CR_CBTUNE0_DllBWEn_MSK                              (0xFFFFFFFF)
  #define DDRDATA1_CR_CBTUNE0_DllBWEn_MIN                              (0)
  #define DDRDATA1_CR_CBTUNE0_DllBWEn_MAX                              (4294967295) // 0xFFFFFFFF
  #define DDRDATA1_CR_CBTUNE0_DllBWEn_DEF                              (0xFDB86521)
  #define DDRDATA1_CR_CBTUNE0_DllBWEn_HSH                              (0x20002084)

#define DDRDATA1_CR_CBTUNE1_REG                                        (0x00002088)

  #define DDRDATA1_CR_CBTUNE1_PiCbEn_OFF                               ( 0)
  #define DDRDATA1_CR_CBTUNE1_PiCbEn_WID                               (24)
  #define DDRDATA1_CR_CBTUNE1_PiCbEn_MSK                               (0x00FFFFFF)
  #define DDRDATA1_CR_CBTUNE1_PiCbEn_MIN                               (0)
  #define DDRDATA1_CR_CBTUNE1_PiCbEn_MAX                               (16777215) // 0x00FFFFFF
  #define DDRDATA1_CR_CBTUNE1_PiCbEn_DEF                               (0x00249492)
  #define DDRDATA1_CR_CBTUNE1_PiCbEn_HSH                               (0x18002088)

  #define DDRDATA1_CR_CBTUNE1_CbEnRsvd_OFF                             (24)
  #define DDRDATA1_CR_CBTUNE1_CbEnRsvd_WID                             ( 3)
  #define DDRDATA1_CR_CBTUNE1_CbEnRsvd_MSK                             (0x07000000)
  #define DDRDATA1_CR_CBTUNE1_CbEnRsvd_MIN                             (0)
  #define DDRDATA1_CR_CBTUNE1_CbEnRsvd_MAX                             (7) // 0x00000007
  #define DDRDATA1_CR_CBTUNE1_CbEnRsvd_DEF                             (0x00000000)
  #define DDRDATA1_CR_CBTUNE1_CbEnRsvd_HSH                             (0x03182088)

  #define DDRDATA1_CR_CBTUNE1_CbEnDllFuse_OFF                          (27)
  #define DDRDATA1_CR_CBTUNE1_CbEnDllFuse_WID                          ( 3)
  #define DDRDATA1_CR_CBTUNE1_CbEnDllFuse_MSK                          (0x38000000)
  #define DDRDATA1_CR_CBTUNE1_CbEnDllFuse_MIN                          (0)
  #define DDRDATA1_CR_CBTUNE1_CbEnDllFuse_MAX                          (7) // 0x00000007
  #define DDRDATA1_CR_CBTUNE1_CbEnDllFuse_DEF                          (0x00000002)
  #define DDRDATA1_CR_CBTUNE1_CbEnDllFuse_HSH                          (0x031B2088)

  #define DDRDATA1_CR_CBTUNE1_Spare_OFF                                (30)
  #define DDRDATA1_CR_CBTUNE1_Spare_WID                                ( 2)
  #define DDRDATA1_CR_CBTUNE1_Spare_MSK                                (0xC0000000)
  #define DDRDATA1_CR_CBTUNE1_Spare_MIN                                (0)
  #define DDRDATA1_CR_CBTUNE1_Spare_MAX                                (3) // 0x00000003
  #define DDRDATA1_CR_CBTUNE1_Spare_DEF                                (0x00000000)
  #define DDRDATA1_CR_CBTUNE1_Spare_HSH                                (0x021E2088)

#define DDRDATA1_CR_ADCCFG_REG                                         (0x0000208C)

  #define DDRDATA1_CR_ADCCFG_ADC_frz_OFF                               ( 0)
  #define DDRDATA1_CR_ADCCFG_ADC_frz_WID                               ( 1)
  #define DDRDATA1_CR_ADCCFG_ADC_frz_MSK                               (0x00000001)
  #define DDRDATA1_CR_ADCCFG_ADC_frz_MIN                               (0)
  #define DDRDATA1_CR_ADCCFG_ADC_frz_MAX                               (1) // 0x00000001
  #define DDRDATA1_CR_ADCCFG_ADC_frz_DEF                               (0x00000000)
  #define DDRDATA1_CR_ADCCFG_ADC_frz_HSH                               (0x0100208C)

  #define DDRDATA1_CR_ADCCFG_ADC_en_OFF                                ( 1)
  #define DDRDATA1_CR_ADCCFG_ADC_en_WID                                ( 1)
  #define DDRDATA1_CR_ADCCFG_ADC_en_MSK                                (0x00000002)
  #define DDRDATA1_CR_ADCCFG_ADC_en_MIN                                (0)
  #define DDRDATA1_CR_ADCCFG_ADC_en_MAX                                (1) // 0x00000001
  #define DDRDATA1_CR_ADCCFG_ADC_en_DEF                                (0x00000000)
  #define DDRDATA1_CR_ADCCFG_ADC_en_HSH                                (0x0101208C)

  #define DDRDATA1_CR_ADCCFG_ADCclkdiv_OFF                             ( 2)
  #define DDRDATA1_CR_ADCCFG_ADCclkdiv_WID                             ( 2)
  #define DDRDATA1_CR_ADCCFG_ADCclkdiv_MSK                             (0x0000000C)
  #define DDRDATA1_CR_ADCCFG_ADCclkdiv_MIN                             (0)
  #define DDRDATA1_CR_ADCCFG_ADCclkdiv_MAX                             (3) // 0x00000003
  #define DDRDATA1_CR_ADCCFG_ADCclkdiv_DEF                             (0x00000000)
  #define DDRDATA1_CR_ADCCFG_ADCclkdiv_HSH                             (0x0202208C)

  #define DDRDATA1_CR_ADCCFG_ADCstartcount_OFF                         ( 4)
  #define DDRDATA1_CR_ADCCFG_ADCstartcount_WID                         ( 2)
  #define DDRDATA1_CR_ADCCFG_ADCstartcount_MSK                         (0x00000030)
  #define DDRDATA1_CR_ADCCFG_ADCstartcount_MIN                         (0)
  #define DDRDATA1_CR_ADCCFG_ADCstartcount_MAX                         (3) // 0x00000003
  #define DDRDATA1_CR_ADCCFG_ADCstartcount_DEF                         (0x00000000)
  #define DDRDATA1_CR_ADCCFG_ADCstartcount_HSH                         (0x0204208C)

  #define DDRDATA1_CR_ADCCFG_ADCChopEn_OFF                             ( 6)
  #define DDRDATA1_CR_ADCCFG_ADCChopEn_WID                             ( 1)
  #define DDRDATA1_CR_ADCCFG_ADCChopEn_MSK                             (0x00000040)
  #define DDRDATA1_CR_ADCCFG_ADCChopEn_MIN                             (0)
  #define DDRDATA1_CR_ADCCFG_ADCChopEn_MAX                             (1) // 0x00000001
  #define DDRDATA1_CR_ADCCFG_ADCChopEn_DEF                             (0x00000000)
  #define DDRDATA1_CR_ADCCFG_ADCChopEn_HSH                             (0x0106208C)

  #define DDRDATA1_CR_ADCCFG_Spare_OFF                                 ( 7)
  #define DDRDATA1_CR_ADCCFG_Spare_WID                                 (25)
  #define DDRDATA1_CR_ADCCFG_Spare_MSK                                 (0xFFFFFF80)
  #define DDRDATA1_CR_ADCCFG_Spare_MIN                                 (0)
  #define DDRDATA1_CR_ADCCFG_Spare_MAX                                 (33554431) // 0x01FFFFFF
  #define DDRDATA1_CR_ADCCFG_Spare_DEF                                 (0x00000000)
  #define DDRDATA1_CR_ADCCFG_Spare_HSH                                 (0x1907208C)

#define DDRDATA1_CR_CBTUNE2_REG                                        (0x00002090)

  #define DDRDATA1_CR_CBTUNE2_DllCbEn_OFF                              ( 0)
  #define DDRDATA1_CR_CBTUNE2_DllCbEn_WID                              (16)
  #define DDRDATA1_CR_CBTUNE2_DllCbEn_MSK                              (0x0000FFFF)
  #define DDRDATA1_CR_CBTUNE2_DllCbEn_MIN                              (0)
  #define DDRDATA1_CR_CBTUNE2_DllCbEn_MAX                              (65535) // 0x0000FFFF
  #define DDRDATA1_CR_CBTUNE2_DllCbEn_DEF                              (0x00000000)
  #define DDRDATA1_CR_CBTUNE2_DllCbEn_HSH                              (0x10002090)

  #define DDRDATA1_CR_CBTUNE2_Spare_OFF                                (16)
  #define DDRDATA1_CR_CBTUNE2_Spare_WID                                (16)
  #define DDRDATA1_CR_CBTUNE2_Spare_MSK                                (0xFFFF0000)
  #define DDRDATA1_CR_CBTUNE2_Spare_MIN                                (0)
  #define DDRDATA1_CR_CBTUNE2_Spare_MAX                                (65535) // 0x0000FFFF
  #define DDRDATA1_CR_CBTUNE2_Spare_DEF                                (0x00000000)
  #define DDRDATA1_CR_CBTUNE2_Spare_HSH                                (0x10102090)

#define DDRDATA1_CR_PIDFTDLY_REG                                       (0x00002098)

  #define DDRDATA1_CR_PIDFTDLY_PiDftDelay_OFF                          ( 0)
  #define DDRDATA1_CR_PIDFTDLY_PiDftDelay_WID                          ( 7)
  #define DDRDATA1_CR_PIDFTDLY_PiDftDelay_MSK                          (0x0000007F)
  #define DDRDATA1_CR_PIDFTDLY_PiDftDelay_MIN                          (0)
  #define DDRDATA1_CR_PIDFTDLY_PiDftDelay_MAX                          (127) // 0x0000007F
  #define DDRDATA1_CR_PIDFTDLY_PiDftDelay_DEF                          (0x00000000)
  #define DDRDATA1_CR_PIDFTDLY_PiDftDelay_HSH                          (0x07002098)

  #define DDRDATA1_CR_PIDFTDLY_Ch0PiEnOvrd_OFF                         ( 7)
  #define DDRDATA1_CR_PIDFTDLY_Ch0PiEnOvrd_WID                         ( 1)
  #define DDRDATA1_CR_PIDFTDLY_Ch0PiEnOvrd_MSK                         (0x00000080)
  #define DDRDATA1_CR_PIDFTDLY_Ch0PiEnOvrd_MIN                         (0)
  #define DDRDATA1_CR_PIDFTDLY_Ch0PiEnOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA1_CR_PIDFTDLY_Ch0PiEnOvrd_DEF                         (0x00000000)
  #define DDRDATA1_CR_PIDFTDLY_Ch0PiEnOvrd_HSH                         (0x01072098)

  #define DDRDATA1_CR_PIDFTDLY_Ch1PiEnOvrd_OFF                         ( 8)
  #define DDRDATA1_CR_PIDFTDLY_Ch1PiEnOvrd_WID                         ( 1)
  #define DDRDATA1_CR_PIDFTDLY_Ch1PiEnOvrd_MSK                         (0x00000100)
  #define DDRDATA1_CR_PIDFTDLY_Ch1PiEnOvrd_MIN                         (0)
  #define DDRDATA1_CR_PIDFTDLY_Ch1PiEnOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA1_CR_PIDFTDLY_Ch1PiEnOvrd_DEF                         (0x00000000)
  #define DDRDATA1_CR_PIDFTDLY_Ch1PiEnOvrd_HSH                         (0x01082098)

  #define DDRDATA1_CR_PIDFTDLY_Ch0PiDFTEn_OFF                          ( 9)
  #define DDRDATA1_CR_PIDFTDLY_Ch0PiDFTEn_WID                          ( 1)
  #define DDRDATA1_CR_PIDFTDLY_Ch0PiDFTEn_MSK                          (0x00000200)
  #define DDRDATA1_CR_PIDFTDLY_Ch0PiDFTEn_MIN                          (0)
  #define DDRDATA1_CR_PIDFTDLY_Ch0PiDFTEn_MAX                          (1) // 0x00000001
  #define DDRDATA1_CR_PIDFTDLY_Ch0PiDFTEn_DEF                          (0x00000000)
  #define DDRDATA1_CR_PIDFTDLY_Ch0PiDFTEn_HSH                          (0x01092098)

  #define DDRDATA1_CR_PIDFTDLY_Ch1PiDFTEn_OFF                          (10)
  #define DDRDATA1_CR_PIDFTDLY_Ch1PiDFTEn_WID                          ( 1)
  #define DDRDATA1_CR_PIDFTDLY_Ch1PiDFTEn_MSK                          (0x00000400)
  #define DDRDATA1_CR_PIDFTDLY_Ch1PiDFTEn_MIN                          (0)
  #define DDRDATA1_CR_PIDFTDLY_Ch1PiDFTEn_MAX                          (1) // 0x00000001
  #define DDRDATA1_CR_PIDFTDLY_Ch1PiDFTEn_DEF                          (0x00000000)
  #define DDRDATA1_CR_PIDFTDLY_Ch1PiDFTEn_HSH                          (0x010A2098)

  #define DDRDATA1_CR_PIDFTDLY_Spare_OFF                               (11)
  #define DDRDATA1_CR_PIDFTDLY_Spare_WID                               ( 4)
  #define DDRDATA1_CR_PIDFTDLY_Spare_MSK                               (0x00007800)
  #define DDRDATA1_CR_PIDFTDLY_Spare_MIN                               (0)
  #define DDRDATA1_CR_PIDFTDLY_Spare_MAX                               (15) // 0x0000000F
  #define DDRDATA1_CR_PIDFTDLY_Spare_DEF                               (0x00000000)
  #define DDRDATA1_CR_PIDFTDLY_Spare_HSH                               (0x040B2098)

  #define DDRDATA1_CR_PIDFTDLY_RefPiOvrd_OFF                           (15)
  #define DDRDATA1_CR_PIDFTDLY_RefPiOvrd_WID                           ( 1)
  #define DDRDATA1_CR_PIDFTDLY_RefPiOvrd_MSK                           (0x00008000)
  #define DDRDATA1_CR_PIDFTDLY_RefPiOvrd_MIN                           (0)
  #define DDRDATA1_CR_PIDFTDLY_RefPiOvrd_MAX                           (1) // 0x00000001
  #define DDRDATA1_CR_PIDFTDLY_RefPiOvrd_DEF                           (0x00000000)
  #define DDRDATA1_CR_PIDFTDLY_RefPiOvrd_HSH                           (0x010F2098)

  #define DDRDATA1_CR_PIDFTDLY_Rsvd_OFF                                (16)
  #define DDRDATA1_CR_PIDFTDLY_Rsvd_WID                                (16)
  #define DDRDATA1_CR_PIDFTDLY_Rsvd_MSK                                (0xFFFF0000)
  #define DDRDATA1_CR_PIDFTDLY_Rsvd_MIN                                (0)
  #define DDRDATA1_CR_PIDFTDLY_Rsvd_MAX                                (65535) // 0x0000FFFF
  #define DDRDATA1_CR_PIDFTDLY_Rsvd_DEF                                (0x00000000)
  #define DDRDATA1_CR_PIDFTDLY_Rsvd_HSH                                (0x10102098)

#define DDRDATA1_CR_DLLPITESTANDADC_REG                                (0x0000209C)

  #define DDRDATA1_CR_DLLPITESTANDADC_RunTest_OFF                      ( 0)
  #define DDRDATA1_CR_DLLPITESTANDADC_RunTest_WID                      ( 1)
  #define DDRDATA1_CR_DLLPITESTANDADC_RunTest_MSK                      (0x00000001)
  #define DDRDATA1_CR_DLLPITESTANDADC_RunTest_MIN                      (0)
  #define DDRDATA1_CR_DLLPITESTANDADC_RunTest_MAX                      (1) // 0x00000001
  #define DDRDATA1_CR_DLLPITESTANDADC_RunTest_DEF                      (0x00000000)
  #define DDRDATA1_CR_DLLPITESTANDADC_RunTest_HSH                      (0x0100209C)

  #define DDRDATA1_CR_DLLPITESTANDADC_Load_OFF                         ( 1)
  #define DDRDATA1_CR_DLLPITESTANDADC_Load_WID                         ( 1)
  #define DDRDATA1_CR_DLLPITESTANDADC_Load_MSK                         (0x00000002)
  #define DDRDATA1_CR_DLLPITESTANDADC_Load_MIN                         (0)
  #define DDRDATA1_CR_DLLPITESTANDADC_Load_MAX                         (1) // 0x00000001
  #define DDRDATA1_CR_DLLPITESTANDADC_Load_DEF                         (0x00000000)
  #define DDRDATA1_CR_DLLPITESTANDADC_Load_HSH                         (0x0101209C)

  #define DDRDATA1_CR_DLLPITESTANDADC_ModeHVM_OFF                      ( 2)
  #define DDRDATA1_CR_DLLPITESTANDADC_ModeHVM_WID                      ( 1)
  #define DDRDATA1_CR_DLLPITESTANDADC_ModeHVM_MSK                      (0x00000004)
  #define DDRDATA1_CR_DLLPITESTANDADC_ModeHVM_MIN                      (0)
  #define DDRDATA1_CR_DLLPITESTANDADC_ModeHVM_MAX                      (1) // 0x00000001
  #define DDRDATA1_CR_DLLPITESTANDADC_ModeHVM_DEF                      (0x00000000)
  #define DDRDATA1_CR_DLLPITESTANDADC_ModeHVM_HSH                      (0x0102209C)

  #define DDRDATA1_CR_DLLPITESTANDADC_ModeDV_OFF                       ( 3)
  #define DDRDATA1_CR_DLLPITESTANDADC_ModeDV_WID                       ( 1)
  #define DDRDATA1_CR_DLLPITESTANDADC_ModeDV_MSK                       (0x00000008)
  #define DDRDATA1_CR_DLLPITESTANDADC_ModeDV_MIN                       (0)
  #define DDRDATA1_CR_DLLPITESTANDADC_ModeDV_MAX                       (1) // 0x00000001
  #define DDRDATA1_CR_DLLPITESTANDADC_ModeDV_DEF                       (0x00000000)
  #define DDRDATA1_CR_DLLPITESTANDADC_ModeDV_HSH                       (0x0103209C)

  #define DDRDATA1_CR_DLLPITESTANDADC_CalCfdl_OFF                      ( 4)
  #define DDRDATA1_CR_DLLPITESTANDADC_CalCfdl_WID                      ( 1)
  #define DDRDATA1_CR_DLLPITESTANDADC_CalCfdl_MSK                      (0x00000010)
  #define DDRDATA1_CR_DLLPITESTANDADC_CalCfdl_MIN                      (0)
  #define DDRDATA1_CR_DLLPITESTANDADC_CalCfdl_MAX                      (1) // 0x00000001
  #define DDRDATA1_CR_DLLPITESTANDADC_CalCfdl_DEF                      (0x00000000)
  #define DDRDATA1_CR_DLLPITESTANDADC_CalCfdl_HSH                      (0x0104209C)

  #define DDRDATA1_CR_DLLPITESTANDADC_LoadCount_OFF                    ( 5)
  #define DDRDATA1_CR_DLLPITESTANDADC_LoadCount_WID                    (10)
  #define DDRDATA1_CR_DLLPITESTANDADC_LoadCount_MSK                    (0x00007FE0)
  #define DDRDATA1_CR_DLLPITESTANDADC_LoadCount_MIN                    (0)
  #define DDRDATA1_CR_DLLPITESTANDADC_LoadCount_MAX                    (1023) // 0x000003FF
  #define DDRDATA1_CR_DLLPITESTANDADC_LoadCount_DEF                    (0x00000000)
  #define DDRDATA1_CR_DLLPITESTANDADC_LoadCount_HSH                    (0x0A05209C)

  #define DDRDATA1_CR_DLLPITESTANDADC_CountStatus_OFF                  (15)
  #define DDRDATA1_CR_DLLPITESTANDADC_CountStatus_WID                  (10)
  #define DDRDATA1_CR_DLLPITESTANDADC_CountStatus_MSK                  (0x01FF8000)
  #define DDRDATA1_CR_DLLPITESTANDADC_CountStatus_MIN                  (0)
  #define DDRDATA1_CR_DLLPITESTANDADC_CountStatus_MAX                  (1023) // 0x000003FF
  #define DDRDATA1_CR_DLLPITESTANDADC_CountStatus_DEF                  (0x00000000)
  #define DDRDATA1_CR_DLLPITESTANDADC_CountStatus_HSH                  (0x0A0F209C)

  #define DDRDATA1_CR_DLLPITESTANDADC_ModeADC_OFF                      (25)
  #define DDRDATA1_CR_DLLPITESTANDADC_ModeADC_WID                      ( 1)
  #define DDRDATA1_CR_DLLPITESTANDADC_ModeADC_MSK                      (0x02000000)
  #define DDRDATA1_CR_DLLPITESTANDADC_ModeADC_MIN                      (0)
  #define DDRDATA1_CR_DLLPITESTANDADC_ModeADC_MAX                      (1) // 0x00000001
  #define DDRDATA1_CR_DLLPITESTANDADC_ModeADC_DEF                      (0x00000000)
  #define DDRDATA1_CR_DLLPITESTANDADC_ModeADC_HSH                      (0x0119209C)

  #define DDRDATA1_CR_DLLPITESTANDADC_ADCClkDiv_OFF                    (26)
  #define DDRDATA1_CR_DLLPITESTANDADC_ADCClkDiv_WID                    ( 2)
  #define DDRDATA1_CR_DLLPITESTANDADC_ADCClkDiv_MSK                    (0x0C000000)
  #define DDRDATA1_CR_DLLPITESTANDADC_ADCClkDiv_MIN                    (0)
  #define DDRDATA1_CR_DLLPITESTANDADC_ADCClkDiv_MAX                    (3) // 0x00000003
  #define DDRDATA1_CR_DLLPITESTANDADC_ADCClkDiv_DEF                    (0x00000000)
  #define DDRDATA1_CR_DLLPITESTANDADC_ADCClkDiv_HSH                    (0x021A209C)

  #define DDRDATA1_CR_DLLPITESTANDADC_ADCDdrChanSel_OFF                (28)
  #define DDRDATA1_CR_DLLPITESTANDADC_ADCDdrChanSel_WID                ( 1)
  #define DDRDATA1_CR_DLLPITESTANDADC_ADCDdrChanSel_MSK                (0x10000000)
  #define DDRDATA1_CR_DLLPITESTANDADC_ADCDdrChanSel_MIN                (0)
  #define DDRDATA1_CR_DLLPITESTANDADC_ADCDdrChanSel_MAX                (1) // 0x00000001
  #define DDRDATA1_CR_DLLPITESTANDADC_ADCDdrChanSel_DEF                (0x00000000)
  #define DDRDATA1_CR_DLLPITESTANDADC_ADCDdrChanSel_HSH                (0x011C209C)

  #define DDRDATA1_CR_DLLPITESTANDADC_ADCChopEn_OFF                    (29)
  #define DDRDATA1_CR_DLLPITESTANDADC_ADCChopEn_WID                    ( 1)
  #define DDRDATA1_CR_DLLPITESTANDADC_ADCChopEn_MSK                    (0x20000000)
  #define DDRDATA1_CR_DLLPITESTANDADC_ADCChopEn_MIN                    (0)
  #define DDRDATA1_CR_DLLPITESTANDADC_ADCChopEn_MAX                    (1) // 0x00000001
  #define DDRDATA1_CR_DLLPITESTANDADC_ADCChopEn_DEF                    (0x00000000)
  #define DDRDATA1_CR_DLLPITESTANDADC_ADCChopEn_HSH                    (0x011D209C)

  #define DDRDATA1_CR_DLLPITESTANDADC_ADCDone_OFF                      (30)
  #define DDRDATA1_CR_DLLPITESTANDADC_ADCDone_WID                      ( 1)
  #define DDRDATA1_CR_DLLPITESTANDADC_ADCDone_MSK                      (0x40000000)
  #define DDRDATA1_CR_DLLPITESTANDADC_ADCDone_MIN                      (0)
  #define DDRDATA1_CR_DLLPITESTANDADC_ADCDone_MAX                      (1) // 0x00000001
  #define DDRDATA1_CR_DLLPITESTANDADC_ADCDone_DEF                      (0x00000000)
  #define DDRDATA1_CR_DLLPITESTANDADC_ADCDone_HSH                      (0x011E209C)

  #define DDRDATA1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF             (31)
  #define DDRDATA1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID             ( 1)
  #define DDRDATA1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK             (0x80000000)
  #define DDRDATA1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN             (0)
  #define DDRDATA1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX             (1) // 0x00000001
  #define DDRDATA1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF             (0x00000000)
  #define DDRDATA1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH             (0x011F209C)

#define DDRDATA1_CR_DLLSTATUS_REG                                      (0x000020A0)

  #define DDRDATA1_CR_DLLSTATUS_DetrmLockStat_OFF                      ( 0)
  #define DDRDATA1_CR_DLLSTATUS_DetrmLockStat_WID                      ( 1)
  #define DDRDATA1_CR_DLLSTATUS_DetrmLockStat_MSK                      (0x00000001)
  #define DDRDATA1_CR_DLLSTATUS_DetrmLockStat_MIN                      (0)
  #define DDRDATA1_CR_DLLSTATUS_DetrmLockStat_MAX                      (1) // 0x00000001
  #define DDRDATA1_CR_DLLSTATUS_DetrmLockStat_DEF                      (0x00000000)
  #define DDRDATA1_CR_DLLSTATUS_DetrmLockStat_HSH                      (0x010020A0)

  #define DDRDATA1_CR_DLLSTATUS_FuncLockStat_OFF                       ( 1)
  #define DDRDATA1_CR_DLLSTATUS_FuncLockStat_WID                       ( 1)
  #define DDRDATA1_CR_DLLSTATUS_FuncLockStat_MSK                       (0x00000002)
  #define DDRDATA1_CR_DLLSTATUS_FuncLockStat_MIN                       (0)
  #define DDRDATA1_CR_DLLSTATUS_FuncLockStat_MAX                       (1) // 0x00000001
  #define DDRDATA1_CR_DLLSTATUS_FuncLockStat_DEF                       (0x00000000)
  #define DDRDATA1_CR_DLLSTATUS_FuncLockStat_HSH                       (0x010120A0)

  #define DDRDATA1_CR_DLLSTATUS_Lock_OFF                               ( 2)
  #define DDRDATA1_CR_DLLSTATUS_Lock_WID                               ( 1)
  #define DDRDATA1_CR_DLLSTATUS_Lock_MSK                               (0x00000004)
  #define DDRDATA1_CR_DLLSTATUS_Lock_MIN                               (0)
  #define DDRDATA1_CR_DLLSTATUS_Lock_MAX                               (1) // 0x00000001
  #define DDRDATA1_CR_DLLSTATUS_Lock_DEF                               (0x00000000)
  #define DDRDATA1_CR_DLLSTATUS_Lock_HSH                               (0x010220A0)

  #define DDRDATA1_CR_DLLSTATUS_Timeout_OFF                            ( 3)
  #define DDRDATA1_CR_DLLSTATUS_Timeout_WID                            ( 1)
  #define DDRDATA1_CR_DLLSTATUS_Timeout_MSK                            (0x00000008)
  #define DDRDATA1_CR_DLLSTATUS_Timeout_MIN                            (0)
  #define DDRDATA1_CR_DLLSTATUS_Timeout_MAX                            (1) // 0x00000001
  #define DDRDATA1_CR_DLLSTATUS_Timeout_DEF                            (0x00000000)
  #define DDRDATA1_CR_DLLSTATUS_Timeout_HSH                            (0x010320A0)

  #define DDRDATA1_CR_DLLSTATUS_DllReset_OFF                           ( 4)
  #define DDRDATA1_CR_DLLSTATUS_DllReset_WID                           ( 1)
  #define DDRDATA1_CR_DLLSTATUS_DllReset_MSK                           (0x00000010)
  #define DDRDATA1_CR_DLLSTATUS_DllReset_MIN                           (0)
  #define DDRDATA1_CR_DLLSTATUS_DllReset_MAX                           (1) // 0x00000001
  #define DDRDATA1_CR_DLLSTATUS_DllReset_DEF                           (0x00000000)
  #define DDRDATA1_CR_DLLSTATUS_DllReset_HSH                           (0x010420A0)

  #define DDRDATA1_CR_DLLSTATUS_LongLockStat_OFF                       ( 5)
  #define DDRDATA1_CR_DLLSTATUS_LongLockStat_WID                       ( 1)
  #define DDRDATA1_CR_DLLSTATUS_LongLockStat_MSK                       (0x00000020)
  #define DDRDATA1_CR_DLLSTATUS_LongLockStat_MIN                       (0)
  #define DDRDATA1_CR_DLLSTATUS_LongLockStat_MAX                       (1) // 0x00000001
  #define DDRDATA1_CR_DLLSTATUS_LongLockStat_DEF                       (0x00000000)
  #define DDRDATA1_CR_DLLSTATUS_LongLockStat_HSH                       (0x010520A0)

  #define DDRDATA1_CR_DLLSTATUS_EarlyLockStat_OFF                      ( 6)
  #define DDRDATA1_CR_DLLSTATUS_EarlyLockStat_WID                      ( 1)
  #define DDRDATA1_CR_DLLSTATUS_EarlyLockStat_MSK                      (0x00000040)
  #define DDRDATA1_CR_DLLSTATUS_EarlyLockStat_MIN                      (0)
  #define DDRDATA1_CR_DLLSTATUS_EarlyLockStat_MAX                      (1) // 0x00000001
  #define DDRDATA1_CR_DLLSTATUS_EarlyLockStat_DEF                      (0x00000000)
  #define DDRDATA1_CR_DLLSTATUS_EarlyLockStat_HSH                      (0x010620A0)

  #define DDRDATA1_CR_DLLSTATUS_NormalMode_NotWkLock_OFF               ( 7)
  #define DDRDATA1_CR_DLLSTATUS_NormalMode_NotWkLock_WID               ( 1)
  #define DDRDATA1_CR_DLLSTATUS_NormalMode_NotWkLock_MSK               (0x00000080)
  #define DDRDATA1_CR_DLLSTATUS_NormalMode_NotWkLock_MIN               (0)
  #define DDRDATA1_CR_DLLSTATUS_NormalMode_NotWkLock_MAX               (1) // 0x00000001
  #define DDRDATA1_CR_DLLSTATUS_NormalMode_NotWkLock_DEF               (0x00000000)
  #define DDRDATA1_CR_DLLSTATUS_NormalMode_NotWkLock_HSH               (0x010720A0)

  #define DDRDATA1_CR_DLLSTATUS_ADCout_OFF                             ( 8)
  #define DDRDATA1_CR_DLLSTATUS_ADCout_WID                             (10)
  #define DDRDATA1_CR_DLLSTATUS_ADCout_MSK                             (0x0003FF00)
  #define DDRDATA1_CR_DLLSTATUS_ADCout_MIN                             (0)
  #define DDRDATA1_CR_DLLSTATUS_ADCout_MAX                             (1023) // 0x000003FF
  #define DDRDATA1_CR_DLLSTATUS_ADCout_DEF                             (0x00000000)
  #define DDRDATA1_CR_DLLSTATUS_ADCout_HSH                             (0x0A0820A0)

  #define DDRDATA1_CR_DLLSTATUS_ADCStatus_OFF                          (18)
  #define DDRDATA1_CR_DLLSTATUS_ADCStatus_WID                          ( 1)
  #define DDRDATA1_CR_DLLSTATUS_ADCStatus_MSK                          (0x00040000)
  #define DDRDATA1_CR_DLLSTATUS_ADCStatus_MIN                          (0)
  #define DDRDATA1_CR_DLLSTATUS_ADCStatus_MAX                          (1) // 0x00000001
  #define DDRDATA1_CR_DLLSTATUS_ADCStatus_DEF                          (0x00000000)
  #define DDRDATA1_CR_DLLSTATUS_ADCStatus_HSH                          (0x011220A0)

  #define DDRDATA1_CR_DLLSTATUS_pilags_OFF                             (19)
  #define DDRDATA1_CR_DLLSTATUS_pilags_WID                             ( 1)
  #define DDRDATA1_CR_DLLSTATUS_pilags_MSK                             (0x00080000)
  #define DDRDATA1_CR_DLLSTATUS_pilags_MIN                             (0)
  #define DDRDATA1_CR_DLLSTATUS_pilags_MAX                             (1) // 0x00000001
  #define DDRDATA1_CR_DLLSTATUS_pilags_DEF                             (0x00000000)
  #define DDRDATA1_CR_DLLSTATUS_pilags_HSH                             (0x011320A0)

  #define DDRDATA1_CR_DLLSTATUS_spare_OFF                              (20)
  #define DDRDATA1_CR_DLLSTATUS_spare_WID                              (12)
  #define DDRDATA1_CR_DLLSTATUS_spare_MSK                              (0xFFF00000)
  #define DDRDATA1_CR_DLLSTATUS_spare_MIN                              (0)
  #define DDRDATA1_CR_DLLSTATUS_spare_MAX                              (4095) // 0x00000FFF
  #define DDRDATA1_CR_DLLSTATUS_spare_DEF                              (0x00000000)
  #define DDRDATA1_CR_DLLSTATUS_spare_HSH                              (0x0C1420A0)

#define DDRDATA1_CR_DLLDCMCTL_REG                                      (0x000020A4)

  #define DDRDATA1_CR_DLLDCMCTL_start_OFF                              ( 0)
  #define DDRDATA1_CR_DLLDCMCTL_start_WID                              ( 1)
  #define DDRDATA1_CR_DLLDCMCTL_start_MSK                              (0x00000001)
  #define DDRDATA1_CR_DLLDCMCTL_start_MIN                              (0)
  #define DDRDATA1_CR_DLLDCMCTL_start_MAX                              (1) // 0x00000001
  #define DDRDATA1_CR_DLLDCMCTL_start_DEF                              (0x00000000)
  #define DDRDATA1_CR_DLLDCMCTL_start_HSH                              (0x010020A4)

  #define DDRDATA1_CR_DLLDCMCTL_clken_OFF                              ( 1)
  #define DDRDATA1_CR_DLLDCMCTL_clken_WID                              ( 1)
  #define DDRDATA1_CR_DLLDCMCTL_clken_MSK                              (0x00000002)
  #define DDRDATA1_CR_DLLDCMCTL_clken_MIN                              (0)
  #define DDRDATA1_CR_DLLDCMCTL_clken_MAX                              (1) // 0x00000001
  #define DDRDATA1_CR_DLLDCMCTL_clken_DEF                              (0x00000000)
  #define DDRDATA1_CR_DLLDCMCTL_clken_HSH                              (0x010120A4)

  #define DDRDATA1_CR_DLLDCMCTL_dcm_dccctl_en_OFF                      ( 2)
  #define DDRDATA1_CR_DLLDCMCTL_dcm_dccctl_en_WID                      ( 1)
  #define DDRDATA1_CR_DLLDCMCTL_dcm_dccctl_en_MSK                      (0x00000004)
  #define DDRDATA1_CR_DLLDCMCTL_dcm_dccctl_en_MIN                      (0)
  #define DDRDATA1_CR_DLLDCMCTL_dcm_dccctl_en_MAX                      (1) // 0x00000001
  #define DDRDATA1_CR_DLLDCMCTL_dcm_dccctl_en_DEF                      (0x00000000)
  #define DDRDATA1_CR_DLLDCMCTL_dcm_dccctl_en_HSH                      (0x010220A4)

  #define DDRDATA1_CR_DLLDCMCTL_dccctl_OFF                             ( 3)
  #define DDRDATA1_CR_DLLDCMCTL_dccctl_WID                             ( 4)
  #define DDRDATA1_CR_DLLDCMCTL_dccctl_MSK                             (0x00000078)
  #define DDRDATA1_CR_DLLDCMCTL_dccctl_MIN                             (0)
  #define DDRDATA1_CR_DLLDCMCTL_dccctl_MAX                             (15) // 0x0000000F
  #define DDRDATA1_CR_DLLDCMCTL_dccctl_DEF                             (0x00000000)
  #define DDRDATA1_CR_DLLDCMCTL_dccctl_HSH                             (0x040320A4)

  #define DDRDATA1_CR_DLLDCMCTL_duration_OFF                           ( 7)
  #define DDRDATA1_CR_DLLDCMCTL_duration_WID                           ( 3)
  #define DDRDATA1_CR_DLLDCMCTL_duration_MSK                           (0x00000380)
  #define DDRDATA1_CR_DLLDCMCTL_duration_MIN                           (0)
  #define DDRDATA1_CR_DLLDCMCTL_duration_MAX                           (7) // 0x00000007
  #define DDRDATA1_CR_DLLDCMCTL_duration_DEF                           (0x00000000)
  #define DDRDATA1_CR_DLLDCMCTL_duration_HSH                           (0x030720A4)

  #define DDRDATA1_CR_DLLDCMCTL_dcm_done_OFF                           (10)
  #define DDRDATA1_CR_DLLDCMCTL_dcm_done_WID                           ( 1)
  #define DDRDATA1_CR_DLLDCMCTL_dcm_done_MSK                           (0x00000400)
  #define DDRDATA1_CR_DLLDCMCTL_dcm_done_MIN                           (0)
  #define DDRDATA1_CR_DLLDCMCTL_dcm_done_MAX                           (1) // 0x00000001
  #define DDRDATA1_CR_DLLDCMCTL_dcm_done_DEF                           (0x00000000)
  #define DDRDATA1_CR_DLLDCMCTL_dcm_done_HSH                           (0x010A20A4)

  #define DDRDATA1_CR_DLLDCMCTL_dcm_results_OFF                        (11)
  #define DDRDATA1_CR_DLLDCMCTL_dcm_results_WID                        (15)
  #define DDRDATA1_CR_DLLDCMCTL_dcm_results_MSK                        (0x03FFF800)
  #define DDRDATA1_CR_DLLDCMCTL_dcm_results_MIN                        (0)
  #define DDRDATA1_CR_DLLDCMCTL_dcm_results_MAX                        (32767) // 0x00007FFF
  #define DDRDATA1_CR_DLLDCMCTL_dcm_results_DEF                        (0x00000000)
  #define DDRDATA1_CR_DLLDCMCTL_dcm_results_HSH                        (0x0F0B20A4)

  #define DDRDATA1_CR_DLLDCMCTL_spare0_OFF                             (26)
  #define DDRDATA1_CR_DLLDCMCTL_spare0_WID                             ( 6)
  #define DDRDATA1_CR_DLLDCMCTL_spare0_MSK                             (0xFC000000)
  #define DDRDATA1_CR_DLLDCMCTL_spare0_MIN                             (0)
  #define DDRDATA1_CR_DLLDCMCTL_spare0_MAX                             (63) // 0x0000003F
  #define DDRDATA1_CR_DLLDCMCTL_spare0_DEF                             (0x00000000)
  #define DDRDATA1_CR_DLLDCMCTL_spare0_HSH                             (0x061A20A4)

#define DDRDATA2_CR_MASTERDLLCFG_REG                                   (0x00002100)

  #define DDRDATA2_CR_MASTERDLLCFG_LockThresh_OFF                      ( 0)
  #define DDRDATA2_CR_MASTERDLLCFG_LockThresh_WID                      ( 3)
  #define DDRDATA2_CR_MASTERDLLCFG_LockThresh_MSK                      (0x00000007)
  #define DDRDATA2_CR_MASTERDLLCFG_LockThresh_MIN                      (0)
  #define DDRDATA2_CR_MASTERDLLCFG_LockThresh_MAX                      (7) // 0x00000007
  #define DDRDATA2_CR_MASTERDLLCFG_LockThresh_DEF                      (0x00000004)
  #define DDRDATA2_CR_MASTERDLLCFG_LockThresh_HSH                      (0x03002100)

  #define DDRDATA2_CR_MASTERDLLCFG_LockCtr_OFF                         ( 3)
  #define DDRDATA2_CR_MASTERDLLCFG_LockCtr_WID                         ( 2)
  #define DDRDATA2_CR_MASTERDLLCFG_LockCtr_MSK                         (0x00000018)
  #define DDRDATA2_CR_MASTERDLLCFG_LockCtr_MIN                         (0)
  #define DDRDATA2_CR_MASTERDLLCFG_LockCtr_MAX                         (3) // 0x00000003
  #define DDRDATA2_CR_MASTERDLLCFG_LockCtr_DEF                         (0x00000000)
  #define DDRDATA2_CR_MASTERDLLCFG_LockCtr_HSH                         (0x02032100)

  #define DDRDATA2_CR_MASTERDLLCFG_VctrlDischRate_OFF                  ( 5)
  #define DDRDATA2_CR_MASTERDLLCFG_VctrlDischRate_WID                  ( 2)
  #define DDRDATA2_CR_MASTERDLLCFG_VctrlDischRate_MSK                  (0x00000060)
  #define DDRDATA2_CR_MASTERDLLCFG_VctrlDischRate_MIN                  (0)
  #define DDRDATA2_CR_MASTERDLLCFG_VctrlDischRate_MAX                  (3) // 0x00000003
  #define DDRDATA2_CR_MASTERDLLCFG_VctrlDischRate_DEF                  (0x00000000)
  #define DDRDATA2_CR_MASTERDLLCFG_VctrlDischRate_HSH                  (0x02052100)

  #define DDRDATA2_CR_MASTERDLLCFG_SelVctrlHi_OFF                      ( 7)
  #define DDRDATA2_CR_MASTERDLLCFG_SelVctrlHi_WID                      ( 1)
  #define DDRDATA2_CR_MASTERDLLCFG_SelVctrlHi_MSK                      (0x00000080)
  #define DDRDATA2_CR_MASTERDLLCFG_SelVctrlHi_MIN                      (0)
  #define DDRDATA2_CR_MASTERDLLCFG_SelVctrlHi_MAX                      (1) // 0x00000001
  #define DDRDATA2_CR_MASTERDLLCFG_SelVctrlHi_DEF                      (0x00000000)
  #define DDRDATA2_CR_MASTERDLLCFG_SelVctrlHi_HSH                      (0x01072100)

  #define DDRDATA2_CR_MASTERDLLCFG_StartupCntSel_OFF                   ( 8)
  #define DDRDATA2_CR_MASTERDLLCFG_StartupCntSel_WID                   ( 1)
  #define DDRDATA2_CR_MASTERDLLCFG_StartupCntSel_MSK                   (0x00000100)
  #define DDRDATA2_CR_MASTERDLLCFG_StartupCntSel_MIN                   (0)
  #define DDRDATA2_CR_MASTERDLLCFG_StartupCntSel_MAX                   (1) // 0x00000001
  #define DDRDATA2_CR_MASTERDLLCFG_StartupCntSel_DEF                   (0x00000000)
  #define DDRDATA2_CR_MASTERDLLCFG_StartupCntSel_HSH                   (0x01082100)

  #define DDRDATA2_CR_MASTERDLLCFG_LockSel_OFF                         ( 9)
  #define DDRDATA2_CR_MASTERDLLCFG_LockSel_WID                         ( 2)
  #define DDRDATA2_CR_MASTERDLLCFG_LockSel_MSK                         (0x00000600)
  #define DDRDATA2_CR_MASTERDLLCFG_LockSel_MIN                         (0)
  #define DDRDATA2_CR_MASTERDLLCFG_LockSel_MAX                         (3) // 0x00000003
  #define DDRDATA2_CR_MASTERDLLCFG_LockSel_DEF                         (0x00000000)
  #define DDRDATA2_CR_MASTERDLLCFG_LockSel_HSH                         (0x02092100)

  #define DDRDATA2_CR_MASTERDLLCFG_RstOvrd_OFF                         (11)
  #define DDRDATA2_CR_MASTERDLLCFG_RstOvrd_WID                         ( 1)
  #define DDRDATA2_CR_MASTERDLLCFG_RstOvrd_MSK                         (0x00000800)
  #define DDRDATA2_CR_MASTERDLLCFG_RstOvrd_MIN                         (0)
  #define DDRDATA2_CR_MASTERDLLCFG_RstOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA2_CR_MASTERDLLCFG_RstOvrd_DEF                         (0x00000000)
  #define DDRDATA2_CR_MASTERDLLCFG_RstOvrd_HSH                         (0x010B2100)

  #define DDRDATA2_CR_MASTERDLLCFG_SelRstOvrd_OFF                      (12)
  #define DDRDATA2_CR_MASTERDLLCFG_SelRstOvrd_WID                      ( 1)
  #define DDRDATA2_CR_MASTERDLLCFG_SelRstOvrd_MSK                      (0x00001000)
  #define DDRDATA2_CR_MASTERDLLCFG_SelRstOvrd_MIN                      (0)
  #define DDRDATA2_CR_MASTERDLLCFG_SelRstOvrd_MAX                      (1) // 0x00000001
  #define DDRDATA2_CR_MASTERDLLCFG_SelRstOvrd_DEF                      (0x00000000)
  #define DDRDATA2_CR_MASTERDLLCFG_SelRstOvrd_HSH                      (0x010C2100)

  #define DDRDATA2_CR_MASTERDLLCFG_TimeOutOvrd_OFF                     (13)
  #define DDRDATA2_CR_MASTERDLLCFG_TimeOutOvrd_WID                     ( 1)
  #define DDRDATA2_CR_MASTERDLLCFG_TimeOutOvrd_MSK                     (0x00002000)
  #define DDRDATA2_CR_MASTERDLLCFG_TimeOutOvrd_MIN                     (0)
  #define DDRDATA2_CR_MASTERDLLCFG_TimeOutOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA2_CR_MASTERDLLCFG_TimeOutOvrd_DEF                     (0x00000000)
  #define DDRDATA2_CR_MASTERDLLCFG_TimeOutOvrd_HSH                     (0x010D2100)

  #define DDRDATA2_CR_MASTERDLLCFG_SelTimeOutOvrd_OFF                  (14)
  #define DDRDATA2_CR_MASTERDLLCFG_SelTimeOutOvrd_WID                  ( 1)
  #define DDRDATA2_CR_MASTERDLLCFG_SelTimeOutOvrd_MSK                  (0x00004000)
  #define DDRDATA2_CR_MASTERDLLCFG_SelTimeOutOvrd_MIN                  (0)
  #define DDRDATA2_CR_MASTERDLLCFG_SelTimeOutOvrd_MAX                  (1) // 0x00000001
  #define DDRDATA2_CR_MASTERDLLCFG_SelTimeOutOvrd_DEF                  (0x00000000)
  #define DDRDATA2_CR_MASTERDLLCFG_SelTimeOutOvrd_HSH                  (0x010E2100)

  #define DDRDATA2_CR_MASTERDLLCFG_ClkGateOvrd_OFF                     (15)
  #define DDRDATA2_CR_MASTERDLLCFG_ClkGateOvrd_WID                     ( 1)
  #define DDRDATA2_CR_MASTERDLLCFG_ClkGateOvrd_MSK                     (0x00008000)
  #define DDRDATA2_CR_MASTERDLLCFG_ClkGateOvrd_MIN                     (0)
  #define DDRDATA2_CR_MASTERDLLCFG_ClkGateOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA2_CR_MASTERDLLCFG_ClkGateOvrd_DEF                     (0x00000000)
  #define DDRDATA2_CR_MASTERDLLCFG_ClkGateOvrd_HSH                     (0x010F2100)

  #define DDRDATA2_CR_MASTERDLLCFG_LockOvrd_OFF                        (16)
  #define DDRDATA2_CR_MASTERDLLCFG_LockOvrd_WID                        ( 1)
  #define DDRDATA2_CR_MASTERDLLCFG_LockOvrd_MSK                        (0x00010000)
  #define DDRDATA2_CR_MASTERDLLCFG_LockOvrd_MIN                        (0)
  #define DDRDATA2_CR_MASTERDLLCFG_LockOvrd_MAX                        (1) // 0x00000001
  #define DDRDATA2_CR_MASTERDLLCFG_LockOvrd_DEF                        (0x00000000)
  #define DDRDATA2_CR_MASTERDLLCFG_LockOvrd_HSH                        (0x01102100)

  #define DDRDATA2_CR_MASTERDLLCFG_SelLockOvrd_OFF                     (17)
  #define DDRDATA2_CR_MASTERDLLCFG_SelLockOvrd_WID                     ( 1)
  #define DDRDATA2_CR_MASTERDLLCFG_SelLockOvrd_MSK                     (0x00020000)
  #define DDRDATA2_CR_MASTERDLLCFG_SelLockOvrd_MIN                     (0)
  #define DDRDATA2_CR_MASTERDLLCFG_SelLockOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA2_CR_MASTERDLLCFG_SelLockOvrd_DEF                     (0x00000000)
  #define DDRDATA2_CR_MASTERDLLCFG_SelLockOvrd_HSH                     (0x01112100)

  #define DDRDATA2_CR_MASTERDLLCFG_OpenLoopOvrd_OFF                    (18)
  #define DDRDATA2_CR_MASTERDLLCFG_OpenLoopOvrd_WID                    ( 1)
  #define DDRDATA2_CR_MASTERDLLCFG_OpenLoopOvrd_MSK                    (0x00040000)
  #define DDRDATA2_CR_MASTERDLLCFG_OpenLoopOvrd_MIN                    (0)
  #define DDRDATA2_CR_MASTERDLLCFG_OpenLoopOvrd_MAX                    (1) // 0x00000001
  #define DDRDATA2_CR_MASTERDLLCFG_OpenLoopOvrd_DEF                    (0x00000000)
  #define DDRDATA2_CR_MASTERDLLCFG_OpenLoopOvrd_HSH                    (0x01122100)

  #define DDRDATA2_CR_MASTERDLLCFG_SelOpenLoopOvrd_OFF                 (19)
  #define DDRDATA2_CR_MASTERDLLCFG_SelOpenLoopOvrd_WID                 ( 1)
  #define DDRDATA2_CR_MASTERDLLCFG_SelOpenLoopOvrd_MSK                 (0x00080000)
  #define DDRDATA2_CR_MASTERDLLCFG_SelOpenLoopOvrd_MIN                 (0)
  #define DDRDATA2_CR_MASTERDLLCFG_SelOpenLoopOvrd_MAX                 (1) // 0x00000001
  #define DDRDATA2_CR_MASTERDLLCFG_SelOpenLoopOvrd_DEF                 (0x00000000)
  #define DDRDATA2_CR_MASTERDLLCFG_SelOpenLoopOvrd_HSH                 (0x01132100)

  #define DDRDATA2_CR_MASTERDLLCFG_WkLockEnOvrd_OFF                    (20)
  #define DDRDATA2_CR_MASTERDLLCFG_WkLockEnOvrd_WID                    ( 1)
  #define DDRDATA2_CR_MASTERDLLCFG_WkLockEnOvrd_MSK                    (0x00100000)
  #define DDRDATA2_CR_MASTERDLLCFG_WkLockEnOvrd_MIN                    (0)
  #define DDRDATA2_CR_MASTERDLLCFG_WkLockEnOvrd_MAX                    (1) // 0x00000001
  #define DDRDATA2_CR_MASTERDLLCFG_WkLockEnOvrd_DEF                    (0x00000000)
  #define DDRDATA2_CR_MASTERDLLCFG_WkLockEnOvrd_HSH                    (0x01142100)

  #define DDRDATA2_CR_MASTERDLLCFG_SelWkLockEnOvrd_OFF                 (21)
  #define DDRDATA2_CR_MASTERDLLCFG_SelWkLockEnOvrd_WID                 ( 1)
  #define DDRDATA2_CR_MASTERDLLCFG_SelWkLockEnOvrd_MSK                 (0x00200000)
  #define DDRDATA2_CR_MASTERDLLCFG_SelWkLockEnOvrd_MIN                 (0)
  #define DDRDATA2_CR_MASTERDLLCFG_SelWkLockEnOvrd_MAX                 (1) // 0x00000001
  #define DDRDATA2_CR_MASTERDLLCFG_SelWkLockEnOvrd_DEF                 (0x00000000)
  #define DDRDATA2_CR_MASTERDLLCFG_SelWkLockEnOvrd_HSH                 (0x01152100)

  #define DDRDATA2_CR_MASTERDLLCFG_CfdlDis_OFF                         (22)
  #define DDRDATA2_CR_MASTERDLLCFG_CfdlDis_WID                         ( 1)
  #define DDRDATA2_CR_MASTERDLLCFG_CfdlDis_MSK                         (0x00400000)
  #define DDRDATA2_CR_MASTERDLLCFG_CfdlDis_MIN                         (0)
  #define DDRDATA2_CR_MASTERDLLCFG_CfdlDis_MAX                         (1) // 0x00000001
  #define DDRDATA2_CR_MASTERDLLCFG_CfdlDis_DEF                         (0x00000000)
  #define DDRDATA2_CR_MASTERDLLCFG_CfdlDis_HSH                         (0x01162100)

  #define DDRDATA2_CR_MASTERDLLCFG_DftEn_OFF                           (23)
  #define DDRDATA2_CR_MASTERDLLCFG_DftEn_WID                           ( 1)
  #define DDRDATA2_CR_MASTERDLLCFG_DftEn_MSK                           (0x00800000)
  #define DDRDATA2_CR_MASTERDLLCFG_DftEn_MIN                           (0)
  #define DDRDATA2_CR_MASTERDLLCFG_DftEn_MAX                           (1) // 0x00000001
  #define DDRDATA2_CR_MASTERDLLCFG_DftEn_DEF                           (0x00000000)
  #define DDRDATA2_CR_MASTERDLLCFG_DftEn_HSH                           (0x01172100)

  #define DDRDATA2_CR_MASTERDLLCFG_spare0_OFF                          (24)
  #define DDRDATA2_CR_MASTERDLLCFG_spare0_WID                          ( 8)
  #define DDRDATA2_CR_MASTERDLLCFG_spare0_MSK                          (0xFF000000)
  #define DDRDATA2_CR_MASTERDLLCFG_spare0_MIN                          (0)
  #define DDRDATA2_CR_MASTERDLLCFG_spare0_MAX                          (255) // 0x000000FF
  #define DDRDATA2_CR_MASTERDLLCFG_spare0_DEF                          (0x00000000)
  #define DDRDATA2_CR_MASTERDLLCFG_spare0_HSH                          (0x08182100)

#define DDRDATA2_CR_CBTUNE0_REG                                        (0x00002104)

  #define DDRDATA2_CR_CBTUNE0_DllBWEn_OFF                              ( 0)
  #define DDRDATA2_CR_CBTUNE0_DllBWEn_WID                              (32)
  #define DDRDATA2_CR_CBTUNE0_DllBWEn_MSK                              (0xFFFFFFFF)
  #define DDRDATA2_CR_CBTUNE0_DllBWEn_MIN                              (0)
  #define DDRDATA2_CR_CBTUNE0_DllBWEn_MAX                              (4294967295) // 0xFFFFFFFF
  #define DDRDATA2_CR_CBTUNE0_DllBWEn_DEF                              (0xFDB86521)
  #define DDRDATA2_CR_CBTUNE0_DllBWEn_HSH                              (0x20002104)

#define DDRDATA2_CR_CBTUNE1_REG                                        (0x00002108)

  #define DDRDATA2_CR_CBTUNE1_PiCbEn_OFF                               ( 0)
  #define DDRDATA2_CR_CBTUNE1_PiCbEn_WID                               (24)
  #define DDRDATA2_CR_CBTUNE1_PiCbEn_MSK                               (0x00FFFFFF)
  #define DDRDATA2_CR_CBTUNE1_PiCbEn_MIN                               (0)
  #define DDRDATA2_CR_CBTUNE1_PiCbEn_MAX                               (16777215) // 0x00FFFFFF
  #define DDRDATA2_CR_CBTUNE1_PiCbEn_DEF                               (0x00249492)
  #define DDRDATA2_CR_CBTUNE1_PiCbEn_HSH                               (0x18002108)

  #define DDRDATA2_CR_CBTUNE1_CbEnRsvd_OFF                             (24)
  #define DDRDATA2_CR_CBTUNE1_CbEnRsvd_WID                             ( 3)
  #define DDRDATA2_CR_CBTUNE1_CbEnRsvd_MSK                             (0x07000000)
  #define DDRDATA2_CR_CBTUNE1_CbEnRsvd_MIN                             (0)
  #define DDRDATA2_CR_CBTUNE1_CbEnRsvd_MAX                             (7) // 0x00000007
  #define DDRDATA2_CR_CBTUNE1_CbEnRsvd_DEF                             (0x00000000)
  #define DDRDATA2_CR_CBTUNE1_CbEnRsvd_HSH                             (0x03182108)

  #define DDRDATA2_CR_CBTUNE1_CbEnDllFuse_OFF                          (27)
  #define DDRDATA2_CR_CBTUNE1_CbEnDllFuse_WID                          ( 3)
  #define DDRDATA2_CR_CBTUNE1_CbEnDllFuse_MSK                          (0x38000000)
  #define DDRDATA2_CR_CBTUNE1_CbEnDllFuse_MIN                          (0)
  #define DDRDATA2_CR_CBTUNE1_CbEnDllFuse_MAX                          (7) // 0x00000007
  #define DDRDATA2_CR_CBTUNE1_CbEnDllFuse_DEF                          (0x00000002)
  #define DDRDATA2_CR_CBTUNE1_CbEnDllFuse_HSH                          (0x031B2108)

  #define DDRDATA2_CR_CBTUNE1_Spare_OFF                                (30)
  #define DDRDATA2_CR_CBTUNE1_Spare_WID                                ( 2)
  #define DDRDATA2_CR_CBTUNE1_Spare_MSK                                (0xC0000000)
  #define DDRDATA2_CR_CBTUNE1_Spare_MIN                                (0)
  #define DDRDATA2_CR_CBTUNE1_Spare_MAX                                (3) // 0x00000003
  #define DDRDATA2_CR_CBTUNE1_Spare_DEF                                (0x00000000)
  #define DDRDATA2_CR_CBTUNE1_Spare_HSH                                (0x021E2108)

#define DDRDATA2_CR_ADCCFG_REG                                         (0x0000210C)

  #define DDRDATA2_CR_ADCCFG_ADC_frz_OFF                               ( 0)
  #define DDRDATA2_CR_ADCCFG_ADC_frz_WID                               ( 1)
  #define DDRDATA2_CR_ADCCFG_ADC_frz_MSK                               (0x00000001)
  #define DDRDATA2_CR_ADCCFG_ADC_frz_MIN                               (0)
  #define DDRDATA2_CR_ADCCFG_ADC_frz_MAX                               (1) // 0x00000001
  #define DDRDATA2_CR_ADCCFG_ADC_frz_DEF                               (0x00000000)
  #define DDRDATA2_CR_ADCCFG_ADC_frz_HSH                               (0x0100210C)

  #define DDRDATA2_CR_ADCCFG_ADC_en_OFF                                ( 1)
  #define DDRDATA2_CR_ADCCFG_ADC_en_WID                                ( 1)
  #define DDRDATA2_CR_ADCCFG_ADC_en_MSK                                (0x00000002)
  #define DDRDATA2_CR_ADCCFG_ADC_en_MIN                                (0)
  #define DDRDATA2_CR_ADCCFG_ADC_en_MAX                                (1) // 0x00000001
  #define DDRDATA2_CR_ADCCFG_ADC_en_DEF                                (0x00000000)
  #define DDRDATA2_CR_ADCCFG_ADC_en_HSH                                (0x0101210C)

  #define DDRDATA2_CR_ADCCFG_ADCclkdiv_OFF                             ( 2)
  #define DDRDATA2_CR_ADCCFG_ADCclkdiv_WID                             ( 2)
  #define DDRDATA2_CR_ADCCFG_ADCclkdiv_MSK                             (0x0000000C)
  #define DDRDATA2_CR_ADCCFG_ADCclkdiv_MIN                             (0)
  #define DDRDATA2_CR_ADCCFG_ADCclkdiv_MAX                             (3) // 0x00000003
  #define DDRDATA2_CR_ADCCFG_ADCclkdiv_DEF                             (0x00000000)
  #define DDRDATA2_CR_ADCCFG_ADCclkdiv_HSH                             (0x0202210C)

  #define DDRDATA2_CR_ADCCFG_ADCstartcount_OFF                         ( 4)
  #define DDRDATA2_CR_ADCCFG_ADCstartcount_WID                         ( 2)
  #define DDRDATA2_CR_ADCCFG_ADCstartcount_MSK                         (0x00000030)
  #define DDRDATA2_CR_ADCCFG_ADCstartcount_MIN                         (0)
  #define DDRDATA2_CR_ADCCFG_ADCstartcount_MAX                         (3) // 0x00000003
  #define DDRDATA2_CR_ADCCFG_ADCstartcount_DEF                         (0x00000000)
  #define DDRDATA2_CR_ADCCFG_ADCstartcount_HSH                         (0x0204210C)

  #define DDRDATA2_CR_ADCCFG_ADCChopEn_OFF                             ( 6)
  #define DDRDATA2_CR_ADCCFG_ADCChopEn_WID                             ( 1)
  #define DDRDATA2_CR_ADCCFG_ADCChopEn_MSK                             (0x00000040)
  #define DDRDATA2_CR_ADCCFG_ADCChopEn_MIN                             (0)
  #define DDRDATA2_CR_ADCCFG_ADCChopEn_MAX                             (1) // 0x00000001
  #define DDRDATA2_CR_ADCCFG_ADCChopEn_DEF                             (0x00000000)
  #define DDRDATA2_CR_ADCCFG_ADCChopEn_HSH                             (0x0106210C)

  #define DDRDATA2_CR_ADCCFG_Spare_OFF                                 ( 7)
  #define DDRDATA2_CR_ADCCFG_Spare_WID                                 (25)
  #define DDRDATA2_CR_ADCCFG_Spare_MSK                                 (0xFFFFFF80)
  #define DDRDATA2_CR_ADCCFG_Spare_MIN                                 (0)
  #define DDRDATA2_CR_ADCCFG_Spare_MAX                                 (33554431) // 0x01FFFFFF
  #define DDRDATA2_CR_ADCCFG_Spare_DEF                                 (0x00000000)
  #define DDRDATA2_CR_ADCCFG_Spare_HSH                                 (0x1907210C)

#define DDRDATA2_CR_CBTUNE2_REG                                        (0x00002110)

  #define DDRDATA2_CR_CBTUNE2_DllCbEn_OFF                              ( 0)
  #define DDRDATA2_CR_CBTUNE2_DllCbEn_WID                              (16)
  #define DDRDATA2_CR_CBTUNE2_DllCbEn_MSK                              (0x0000FFFF)
  #define DDRDATA2_CR_CBTUNE2_DllCbEn_MIN                              (0)
  #define DDRDATA2_CR_CBTUNE2_DllCbEn_MAX                              (65535) // 0x0000FFFF
  #define DDRDATA2_CR_CBTUNE2_DllCbEn_DEF                              (0x00000000)
  #define DDRDATA2_CR_CBTUNE2_DllCbEn_HSH                              (0x10002110)

  #define DDRDATA2_CR_CBTUNE2_Spare_OFF                                (16)
  #define DDRDATA2_CR_CBTUNE2_Spare_WID                                (16)
  #define DDRDATA2_CR_CBTUNE2_Spare_MSK                                (0xFFFF0000)
  #define DDRDATA2_CR_CBTUNE2_Spare_MIN                                (0)
  #define DDRDATA2_CR_CBTUNE2_Spare_MAX                                (65535) // 0x0000FFFF
  #define DDRDATA2_CR_CBTUNE2_Spare_DEF                                (0x00000000)
  #define DDRDATA2_CR_CBTUNE2_Spare_HSH                                (0x10102110)

#define DDRDATA2_CR_PIDFTDLY_REG                                       (0x00002118)

  #define DDRDATA2_CR_PIDFTDLY_PiDftDelay_OFF                          ( 0)
  #define DDRDATA2_CR_PIDFTDLY_PiDftDelay_WID                          ( 7)
  #define DDRDATA2_CR_PIDFTDLY_PiDftDelay_MSK                          (0x0000007F)
  #define DDRDATA2_CR_PIDFTDLY_PiDftDelay_MIN                          (0)
  #define DDRDATA2_CR_PIDFTDLY_PiDftDelay_MAX                          (127) // 0x0000007F
  #define DDRDATA2_CR_PIDFTDLY_PiDftDelay_DEF                          (0x00000000)
  #define DDRDATA2_CR_PIDFTDLY_PiDftDelay_HSH                          (0x07002118)

  #define DDRDATA2_CR_PIDFTDLY_Ch0PiEnOvrd_OFF                         ( 7)
  #define DDRDATA2_CR_PIDFTDLY_Ch0PiEnOvrd_WID                         ( 1)
  #define DDRDATA2_CR_PIDFTDLY_Ch0PiEnOvrd_MSK                         (0x00000080)
  #define DDRDATA2_CR_PIDFTDLY_Ch0PiEnOvrd_MIN                         (0)
  #define DDRDATA2_CR_PIDFTDLY_Ch0PiEnOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA2_CR_PIDFTDLY_Ch0PiEnOvrd_DEF                         (0x00000000)
  #define DDRDATA2_CR_PIDFTDLY_Ch0PiEnOvrd_HSH                         (0x01072118)

  #define DDRDATA2_CR_PIDFTDLY_Ch1PiEnOvrd_OFF                         ( 8)
  #define DDRDATA2_CR_PIDFTDLY_Ch1PiEnOvrd_WID                         ( 1)
  #define DDRDATA2_CR_PIDFTDLY_Ch1PiEnOvrd_MSK                         (0x00000100)
  #define DDRDATA2_CR_PIDFTDLY_Ch1PiEnOvrd_MIN                         (0)
  #define DDRDATA2_CR_PIDFTDLY_Ch1PiEnOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA2_CR_PIDFTDLY_Ch1PiEnOvrd_DEF                         (0x00000000)
  #define DDRDATA2_CR_PIDFTDLY_Ch1PiEnOvrd_HSH                         (0x01082118)

  #define DDRDATA2_CR_PIDFTDLY_Ch0PiDFTEn_OFF                          ( 9)
  #define DDRDATA2_CR_PIDFTDLY_Ch0PiDFTEn_WID                          ( 1)
  #define DDRDATA2_CR_PIDFTDLY_Ch0PiDFTEn_MSK                          (0x00000200)
  #define DDRDATA2_CR_PIDFTDLY_Ch0PiDFTEn_MIN                          (0)
  #define DDRDATA2_CR_PIDFTDLY_Ch0PiDFTEn_MAX                          (1) // 0x00000001
  #define DDRDATA2_CR_PIDFTDLY_Ch0PiDFTEn_DEF                          (0x00000000)
  #define DDRDATA2_CR_PIDFTDLY_Ch0PiDFTEn_HSH                          (0x01092118)

  #define DDRDATA2_CR_PIDFTDLY_Ch1PiDFTEn_OFF                          (10)
  #define DDRDATA2_CR_PIDFTDLY_Ch1PiDFTEn_WID                          ( 1)
  #define DDRDATA2_CR_PIDFTDLY_Ch1PiDFTEn_MSK                          (0x00000400)
  #define DDRDATA2_CR_PIDFTDLY_Ch1PiDFTEn_MIN                          (0)
  #define DDRDATA2_CR_PIDFTDLY_Ch1PiDFTEn_MAX                          (1) // 0x00000001
  #define DDRDATA2_CR_PIDFTDLY_Ch1PiDFTEn_DEF                          (0x00000000)
  #define DDRDATA2_CR_PIDFTDLY_Ch1PiDFTEn_HSH                          (0x010A2118)

  #define DDRDATA2_CR_PIDFTDLY_Spare_OFF                               (11)
  #define DDRDATA2_CR_PIDFTDLY_Spare_WID                               ( 4)
  #define DDRDATA2_CR_PIDFTDLY_Spare_MSK                               (0x00007800)
  #define DDRDATA2_CR_PIDFTDLY_Spare_MIN                               (0)
  #define DDRDATA2_CR_PIDFTDLY_Spare_MAX                               (15) // 0x0000000F
  #define DDRDATA2_CR_PIDFTDLY_Spare_DEF                               (0x00000000)
  #define DDRDATA2_CR_PIDFTDLY_Spare_HSH                               (0x040B2118)

  #define DDRDATA2_CR_PIDFTDLY_RefPiOvrd_OFF                           (15)
  #define DDRDATA2_CR_PIDFTDLY_RefPiOvrd_WID                           ( 1)
  #define DDRDATA2_CR_PIDFTDLY_RefPiOvrd_MSK                           (0x00008000)
  #define DDRDATA2_CR_PIDFTDLY_RefPiOvrd_MIN                           (0)
  #define DDRDATA2_CR_PIDFTDLY_RefPiOvrd_MAX                           (1) // 0x00000001
  #define DDRDATA2_CR_PIDFTDLY_RefPiOvrd_DEF                           (0x00000000)
  #define DDRDATA2_CR_PIDFTDLY_RefPiOvrd_HSH                           (0x010F2118)

  #define DDRDATA2_CR_PIDFTDLY_Rsvd_OFF                                (16)
  #define DDRDATA2_CR_PIDFTDLY_Rsvd_WID                                (16)
  #define DDRDATA2_CR_PIDFTDLY_Rsvd_MSK                                (0xFFFF0000)
  #define DDRDATA2_CR_PIDFTDLY_Rsvd_MIN                                (0)
  #define DDRDATA2_CR_PIDFTDLY_Rsvd_MAX                                (65535) // 0x0000FFFF
  #define DDRDATA2_CR_PIDFTDLY_Rsvd_DEF                                (0x00000000)
  #define DDRDATA2_CR_PIDFTDLY_Rsvd_HSH                                (0x10102118)

#define DDRDATA2_CR_DLLPITESTANDADC_REG                                (0x0000211C)

  #define DDRDATA2_CR_DLLPITESTANDADC_RunTest_OFF                      ( 0)
  #define DDRDATA2_CR_DLLPITESTANDADC_RunTest_WID                      ( 1)
  #define DDRDATA2_CR_DLLPITESTANDADC_RunTest_MSK                      (0x00000001)
  #define DDRDATA2_CR_DLLPITESTANDADC_RunTest_MIN                      (0)
  #define DDRDATA2_CR_DLLPITESTANDADC_RunTest_MAX                      (1) // 0x00000001
  #define DDRDATA2_CR_DLLPITESTANDADC_RunTest_DEF                      (0x00000000)
  #define DDRDATA2_CR_DLLPITESTANDADC_RunTest_HSH                      (0x0100211C)

  #define DDRDATA2_CR_DLLPITESTANDADC_Load_OFF                         ( 1)
  #define DDRDATA2_CR_DLLPITESTANDADC_Load_WID                         ( 1)
  #define DDRDATA2_CR_DLLPITESTANDADC_Load_MSK                         (0x00000002)
  #define DDRDATA2_CR_DLLPITESTANDADC_Load_MIN                         (0)
  #define DDRDATA2_CR_DLLPITESTANDADC_Load_MAX                         (1) // 0x00000001
  #define DDRDATA2_CR_DLLPITESTANDADC_Load_DEF                         (0x00000000)
  #define DDRDATA2_CR_DLLPITESTANDADC_Load_HSH                         (0x0101211C)

  #define DDRDATA2_CR_DLLPITESTANDADC_ModeHVM_OFF                      ( 2)
  #define DDRDATA2_CR_DLLPITESTANDADC_ModeHVM_WID                      ( 1)
  #define DDRDATA2_CR_DLLPITESTANDADC_ModeHVM_MSK                      (0x00000004)
  #define DDRDATA2_CR_DLLPITESTANDADC_ModeHVM_MIN                      (0)
  #define DDRDATA2_CR_DLLPITESTANDADC_ModeHVM_MAX                      (1) // 0x00000001
  #define DDRDATA2_CR_DLLPITESTANDADC_ModeHVM_DEF                      (0x00000000)
  #define DDRDATA2_CR_DLLPITESTANDADC_ModeHVM_HSH                      (0x0102211C)

  #define DDRDATA2_CR_DLLPITESTANDADC_ModeDV_OFF                       ( 3)
  #define DDRDATA2_CR_DLLPITESTANDADC_ModeDV_WID                       ( 1)
  #define DDRDATA2_CR_DLLPITESTANDADC_ModeDV_MSK                       (0x00000008)
  #define DDRDATA2_CR_DLLPITESTANDADC_ModeDV_MIN                       (0)
  #define DDRDATA2_CR_DLLPITESTANDADC_ModeDV_MAX                       (1) // 0x00000001
  #define DDRDATA2_CR_DLLPITESTANDADC_ModeDV_DEF                       (0x00000000)
  #define DDRDATA2_CR_DLLPITESTANDADC_ModeDV_HSH                       (0x0103211C)

  #define DDRDATA2_CR_DLLPITESTANDADC_CalCfdl_OFF                      ( 4)
  #define DDRDATA2_CR_DLLPITESTANDADC_CalCfdl_WID                      ( 1)
  #define DDRDATA2_CR_DLLPITESTANDADC_CalCfdl_MSK                      (0x00000010)
  #define DDRDATA2_CR_DLLPITESTANDADC_CalCfdl_MIN                      (0)
  #define DDRDATA2_CR_DLLPITESTANDADC_CalCfdl_MAX                      (1) // 0x00000001
  #define DDRDATA2_CR_DLLPITESTANDADC_CalCfdl_DEF                      (0x00000000)
  #define DDRDATA2_CR_DLLPITESTANDADC_CalCfdl_HSH                      (0x0104211C)

  #define DDRDATA2_CR_DLLPITESTANDADC_LoadCount_OFF                    ( 5)
  #define DDRDATA2_CR_DLLPITESTANDADC_LoadCount_WID                    (10)
  #define DDRDATA2_CR_DLLPITESTANDADC_LoadCount_MSK                    (0x00007FE0)
  #define DDRDATA2_CR_DLLPITESTANDADC_LoadCount_MIN                    (0)
  #define DDRDATA2_CR_DLLPITESTANDADC_LoadCount_MAX                    (1023) // 0x000003FF
  #define DDRDATA2_CR_DLLPITESTANDADC_LoadCount_DEF                    (0x00000000)
  #define DDRDATA2_CR_DLLPITESTANDADC_LoadCount_HSH                    (0x0A05211C)

  #define DDRDATA2_CR_DLLPITESTANDADC_CountStatus_OFF                  (15)
  #define DDRDATA2_CR_DLLPITESTANDADC_CountStatus_WID                  (10)
  #define DDRDATA2_CR_DLLPITESTANDADC_CountStatus_MSK                  (0x01FF8000)
  #define DDRDATA2_CR_DLLPITESTANDADC_CountStatus_MIN                  (0)
  #define DDRDATA2_CR_DLLPITESTANDADC_CountStatus_MAX                  (1023) // 0x000003FF
  #define DDRDATA2_CR_DLLPITESTANDADC_CountStatus_DEF                  (0x00000000)
  #define DDRDATA2_CR_DLLPITESTANDADC_CountStatus_HSH                  (0x0A0F211C)

  #define DDRDATA2_CR_DLLPITESTANDADC_ModeADC_OFF                      (25)
  #define DDRDATA2_CR_DLLPITESTANDADC_ModeADC_WID                      ( 1)
  #define DDRDATA2_CR_DLLPITESTANDADC_ModeADC_MSK                      (0x02000000)
  #define DDRDATA2_CR_DLLPITESTANDADC_ModeADC_MIN                      (0)
  #define DDRDATA2_CR_DLLPITESTANDADC_ModeADC_MAX                      (1) // 0x00000001
  #define DDRDATA2_CR_DLLPITESTANDADC_ModeADC_DEF                      (0x00000000)
  #define DDRDATA2_CR_DLLPITESTANDADC_ModeADC_HSH                      (0x0119211C)

  #define DDRDATA2_CR_DLLPITESTANDADC_ADCClkDiv_OFF                    (26)
  #define DDRDATA2_CR_DLLPITESTANDADC_ADCClkDiv_WID                    ( 2)
  #define DDRDATA2_CR_DLLPITESTANDADC_ADCClkDiv_MSK                    (0x0C000000)
  #define DDRDATA2_CR_DLLPITESTANDADC_ADCClkDiv_MIN                    (0)
  #define DDRDATA2_CR_DLLPITESTANDADC_ADCClkDiv_MAX                    (3) // 0x00000003
  #define DDRDATA2_CR_DLLPITESTANDADC_ADCClkDiv_DEF                    (0x00000000)
  #define DDRDATA2_CR_DLLPITESTANDADC_ADCClkDiv_HSH                    (0x021A211C)

  #define DDRDATA2_CR_DLLPITESTANDADC_ADCDdrChanSel_OFF                (28)
  #define DDRDATA2_CR_DLLPITESTANDADC_ADCDdrChanSel_WID                ( 1)
  #define DDRDATA2_CR_DLLPITESTANDADC_ADCDdrChanSel_MSK                (0x10000000)
  #define DDRDATA2_CR_DLLPITESTANDADC_ADCDdrChanSel_MIN                (0)
  #define DDRDATA2_CR_DLLPITESTANDADC_ADCDdrChanSel_MAX                (1) // 0x00000001
  #define DDRDATA2_CR_DLLPITESTANDADC_ADCDdrChanSel_DEF                (0x00000000)
  #define DDRDATA2_CR_DLLPITESTANDADC_ADCDdrChanSel_HSH                (0x011C211C)

  #define DDRDATA2_CR_DLLPITESTANDADC_ADCChopEn_OFF                    (29)
  #define DDRDATA2_CR_DLLPITESTANDADC_ADCChopEn_WID                    ( 1)
  #define DDRDATA2_CR_DLLPITESTANDADC_ADCChopEn_MSK                    (0x20000000)
  #define DDRDATA2_CR_DLLPITESTANDADC_ADCChopEn_MIN                    (0)
  #define DDRDATA2_CR_DLLPITESTANDADC_ADCChopEn_MAX                    (1) // 0x00000001
  #define DDRDATA2_CR_DLLPITESTANDADC_ADCChopEn_DEF                    (0x00000000)
  #define DDRDATA2_CR_DLLPITESTANDADC_ADCChopEn_HSH                    (0x011D211C)

  #define DDRDATA2_CR_DLLPITESTANDADC_ADCDone_OFF                      (30)
  #define DDRDATA2_CR_DLLPITESTANDADC_ADCDone_WID                      ( 1)
  #define DDRDATA2_CR_DLLPITESTANDADC_ADCDone_MSK                      (0x40000000)
  #define DDRDATA2_CR_DLLPITESTANDADC_ADCDone_MIN                      (0)
  #define DDRDATA2_CR_DLLPITESTANDADC_ADCDone_MAX                      (1) // 0x00000001
  #define DDRDATA2_CR_DLLPITESTANDADC_ADCDone_DEF                      (0x00000000)
  #define DDRDATA2_CR_DLLPITESTANDADC_ADCDone_HSH                      (0x011E211C)

  #define DDRDATA2_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF             (31)
  #define DDRDATA2_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID             ( 1)
  #define DDRDATA2_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK             (0x80000000)
  #define DDRDATA2_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN             (0)
  #define DDRDATA2_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX             (1) // 0x00000001
  #define DDRDATA2_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF             (0x00000000)
  #define DDRDATA2_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH             (0x011F211C)

#define DDRDATA2_CR_DLLSTATUS_REG                                      (0x00002120)

  #define DDRDATA2_CR_DLLSTATUS_DetrmLockStat_OFF                      ( 0)
  #define DDRDATA2_CR_DLLSTATUS_DetrmLockStat_WID                      ( 1)
  #define DDRDATA2_CR_DLLSTATUS_DetrmLockStat_MSK                      (0x00000001)
  #define DDRDATA2_CR_DLLSTATUS_DetrmLockStat_MIN                      (0)
  #define DDRDATA2_CR_DLLSTATUS_DetrmLockStat_MAX                      (1) // 0x00000001
  #define DDRDATA2_CR_DLLSTATUS_DetrmLockStat_DEF                      (0x00000000)
  #define DDRDATA2_CR_DLLSTATUS_DetrmLockStat_HSH                      (0x01002120)

  #define DDRDATA2_CR_DLLSTATUS_FuncLockStat_OFF                       ( 1)
  #define DDRDATA2_CR_DLLSTATUS_FuncLockStat_WID                       ( 1)
  #define DDRDATA2_CR_DLLSTATUS_FuncLockStat_MSK                       (0x00000002)
  #define DDRDATA2_CR_DLLSTATUS_FuncLockStat_MIN                       (0)
  #define DDRDATA2_CR_DLLSTATUS_FuncLockStat_MAX                       (1) // 0x00000001
  #define DDRDATA2_CR_DLLSTATUS_FuncLockStat_DEF                       (0x00000000)
  #define DDRDATA2_CR_DLLSTATUS_FuncLockStat_HSH                       (0x01012120)

  #define DDRDATA2_CR_DLLSTATUS_Lock_OFF                               ( 2)
  #define DDRDATA2_CR_DLLSTATUS_Lock_WID                               ( 1)
  #define DDRDATA2_CR_DLLSTATUS_Lock_MSK                               (0x00000004)
  #define DDRDATA2_CR_DLLSTATUS_Lock_MIN                               (0)
  #define DDRDATA2_CR_DLLSTATUS_Lock_MAX                               (1) // 0x00000001
  #define DDRDATA2_CR_DLLSTATUS_Lock_DEF                               (0x00000000)
  #define DDRDATA2_CR_DLLSTATUS_Lock_HSH                               (0x01022120)

  #define DDRDATA2_CR_DLLSTATUS_Timeout_OFF                            ( 3)
  #define DDRDATA2_CR_DLLSTATUS_Timeout_WID                            ( 1)
  #define DDRDATA2_CR_DLLSTATUS_Timeout_MSK                            (0x00000008)
  #define DDRDATA2_CR_DLLSTATUS_Timeout_MIN                            (0)
  #define DDRDATA2_CR_DLLSTATUS_Timeout_MAX                            (1) // 0x00000001
  #define DDRDATA2_CR_DLLSTATUS_Timeout_DEF                            (0x00000000)
  #define DDRDATA2_CR_DLLSTATUS_Timeout_HSH                            (0x01032120)

  #define DDRDATA2_CR_DLLSTATUS_DllReset_OFF                           ( 4)
  #define DDRDATA2_CR_DLLSTATUS_DllReset_WID                           ( 1)
  #define DDRDATA2_CR_DLLSTATUS_DllReset_MSK                           (0x00000010)
  #define DDRDATA2_CR_DLLSTATUS_DllReset_MIN                           (0)
  #define DDRDATA2_CR_DLLSTATUS_DllReset_MAX                           (1) // 0x00000001
  #define DDRDATA2_CR_DLLSTATUS_DllReset_DEF                           (0x00000000)
  #define DDRDATA2_CR_DLLSTATUS_DllReset_HSH                           (0x01042120)

  #define DDRDATA2_CR_DLLSTATUS_LongLockStat_OFF                       ( 5)
  #define DDRDATA2_CR_DLLSTATUS_LongLockStat_WID                       ( 1)
  #define DDRDATA2_CR_DLLSTATUS_LongLockStat_MSK                       (0x00000020)
  #define DDRDATA2_CR_DLLSTATUS_LongLockStat_MIN                       (0)
  #define DDRDATA2_CR_DLLSTATUS_LongLockStat_MAX                       (1) // 0x00000001
  #define DDRDATA2_CR_DLLSTATUS_LongLockStat_DEF                       (0x00000000)
  #define DDRDATA2_CR_DLLSTATUS_LongLockStat_HSH                       (0x01052120)

  #define DDRDATA2_CR_DLLSTATUS_EarlyLockStat_OFF                      ( 6)
  #define DDRDATA2_CR_DLLSTATUS_EarlyLockStat_WID                      ( 1)
  #define DDRDATA2_CR_DLLSTATUS_EarlyLockStat_MSK                      (0x00000040)
  #define DDRDATA2_CR_DLLSTATUS_EarlyLockStat_MIN                      (0)
  #define DDRDATA2_CR_DLLSTATUS_EarlyLockStat_MAX                      (1) // 0x00000001
  #define DDRDATA2_CR_DLLSTATUS_EarlyLockStat_DEF                      (0x00000000)
  #define DDRDATA2_CR_DLLSTATUS_EarlyLockStat_HSH                      (0x01062120)

  #define DDRDATA2_CR_DLLSTATUS_NormalMode_NotWkLock_OFF               ( 7)
  #define DDRDATA2_CR_DLLSTATUS_NormalMode_NotWkLock_WID               ( 1)
  #define DDRDATA2_CR_DLLSTATUS_NormalMode_NotWkLock_MSK               (0x00000080)
  #define DDRDATA2_CR_DLLSTATUS_NormalMode_NotWkLock_MIN               (0)
  #define DDRDATA2_CR_DLLSTATUS_NormalMode_NotWkLock_MAX               (1) // 0x00000001
  #define DDRDATA2_CR_DLLSTATUS_NormalMode_NotWkLock_DEF               (0x00000000)
  #define DDRDATA2_CR_DLLSTATUS_NormalMode_NotWkLock_HSH               (0x01072120)

  #define DDRDATA2_CR_DLLSTATUS_ADCout_OFF                             ( 8)
  #define DDRDATA2_CR_DLLSTATUS_ADCout_WID                             (10)
  #define DDRDATA2_CR_DLLSTATUS_ADCout_MSK                             (0x0003FF00)
  #define DDRDATA2_CR_DLLSTATUS_ADCout_MIN                             (0)
  #define DDRDATA2_CR_DLLSTATUS_ADCout_MAX                             (1023) // 0x000003FF
  #define DDRDATA2_CR_DLLSTATUS_ADCout_DEF                             (0x00000000)
  #define DDRDATA2_CR_DLLSTATUS_ADCout_HSH                             (0x0A082120)

  #define DDRDATA2_CR_DLLSTATUS_ADCStatus_OFF                          (18)
  #define DDRDATA2_CR_DLLSTATUS_ADCStatus_WID                          ( 1)
  #define DDRDATA2_CR_DLLSTATUS_ADCStatus_MSK                          (0x00040000)
  #define DDRDATA2_CR_DLLSTATUS_ADCStatus_MIN                          (0)
  #define DDRDATA2_CR_DLLSTATUS_ADCStatus_MAX                          (1) // 0x00000001
  #define DDRDATA2_CR_DLLSTATUS_ADCStatus_DEF                          (0x00000000)
  #define DDRDATA2_CR_DLLSTATUS_ADCStatus_HSH                          (0x01122120)

  #define DDRDATA2_CR_DLLSTATUS_pilags_OFF                             (19)
  #define DDRDATA2_CR_DLLSTATUS_pilags_WID                             ( 1)
  #define DDRDATA2_CR_DLLSTATUS_pilags_MSK                             (0x00080000)
  #define DDRDATA2_CR_DLLSTATUS_pilags_MIN                             (0)
  #define DDRDATA2_CR_DLLSTATUS_pilags_MAX                             (1) // 0x00000001
  #define DDRDATA2_CR_DLLSTATUS_pilags_DEF                             (0x00000000)
  #define DDRDATA2_CR_DLLSTATUS_pilags_HSH                             (0x01132120)

  #define DDRDATA2_CR_DLLSTATUS_spare_OFF                              (20)
  #define DDRDATA2_CR_DLLSTATUS_spare_WID                              (12)
  #define DDRDATA2_CR_DLLSTATUS_spare_MSK                              (0xFFF00000)
  #define DDRDATA2_CR_DLLSTATUS_spare_MIN                              (0)
  #define DDRDATA2_CR_DLLSTATUS_spare_MAX                              (4095) // 0x00000FFF
  #define DDRDATA2_CR_DLLSTATUS_spare_DEF                              (0x00000000)
  #define DDRDATA2_CR_DLLSTATUS_spare_HSH                              (0x0C142120)

#define DDRDATA2_CR_DLLDCMCTL_REG                                      (0x00002124)

  #define DDRDATA2_CR_DLLDCMCTL_start_OFF                              ( 0)
  #define DDRDATA2_CR_DLLDCMCTL_start_WID                              ( 1)
  #define DDRDATA2_CR_DLLDCMCTL_start_MSK                              (0x00000001)
  #define DDRDATA2_CR_DLLDCMCTL_start_MIN                              (0)
  #define DDRDATA2_CR_DLLDCMCTL_start_MAX                              (1) // 0x00000001
  #define DDRDATA2_CR_DLLDCMCTL_start_DEF                              (0x00000000)
  #define DDRDATA2_CR_DLLDCMCTL_start_HSH                              (0x01002124)

  #define DDRDATA2_CR_DLLDCMCTL_clken_OFF                              ( 1)
  #define DDRDATA2_CR_DLLDCMCTL_clken_WID                              ( 1)
  #define DDRDATA2_CR_DLLDCMCTL_clken_MSK                              (0x00000002)
  #define DDRDATA2_CR_DLLDCMCTL_clken_MIN                              (0)
  #define DDRDATA2_CR_DLLDCMCTL_clken_MAX                              (1) // 0x00000001
  #define DDRDATA2_CR_DLLDCMCTL_clken_DEF                              (0x00000000)
  #define DDRDATA2_CR_DLLDCMCTL_clken_HSH                              (0x01012124)

  #define DDRDATA2_CR_DLLDCMCTL_dcm_dccctl_en_OFF                      ( 2)
  #define DDRDATA2_CR_DLLDCMCTL_dcm_dccctl_en_WID                      ( 1)
  #define DDRDATA2_CR_DLLDCMCTL_dcm_dccctl_en_MSK                      (0x00000004)
  #define DDRDATA2_CR_DLLDCMCTL_dcm_dccctl_en_MIN                      (0)
  #define DDRDATA2_CR_DLLDCMCTL_dcm_dccctl_en_MAX                      (1) // 0x00000001
  #define DDRDATA2_CR_DLLDCMCTL_dcm_dccctl_en_DEF                      (0x00000000)
  #define DDRDATA2_CR_DLLDCMCTL_dcm_dccctl_en_HSH                      (0x01022124)

  #define DDRDATA2_CR_DLLDCMCTL_dccctl_OFF                             ( 3)
  #define DDRDATA2_CR_DLLDCMCTL_dccctl_WID                             ( 4)
  #define DDRDATA2_CR_DLLDCMCTL_dccctl_MSK                             (0x00000078)
  #define DDRDATA2_CR_DLLDCMCTL_dccctl_MIN                             (0)
  #define DDRDATA2_CR_DLLDCMCTL_dccctl_MAX                             (15) // 0x0000000F
  #define DDRDATA2_CR_DLLDCMCTL_dccctl_DEF                             (0x00000000)
  #define DDRDATA2_CR_DLLDCMCTL_dccctl_HSH                             (0x04032124)

  #define DDRDATA2_CR_DLLDCMCTL_duration_OFF                           ( 7)
  #define DDRDATA2_CR_DLLDCMCTL_duration_WID                           ( 3)
  #define DDRDATA2_CR_DLLDCMCTL_duration_MSK                           (0x00000380)
  #define DDRDATA2_CR_DLLDCMCTL_duration_MIN                           (0)
  #define DDRDATA2_CR_DLLDCMCTL_duration_MAX                           (7) // 0x00000007
  #define DDRDATA2_CR_DLLDCMCTL_duration_DEF                           (0x00000000)
  #define DDRDATA2_CR_DLLDCMCTL_duration_HSH                           (0x03072124)

  #define DDRDATA2_CR_DLLDCMCTL_dcm_done_OFF                           (10)
  #define DDRDATA2_CR_DLLDCMCTL_dcm_done_WID                           ( 1)
  #define DDRDATA2_CR_DLLDCMCTL_dcm_done_MSK                           (0x00000400)
  #define DDRDATA2_CR_DLLDCMCTL_dcm_done_MIN                           (0)
  #define DDRDATA2_CR_DLLDCMCTL_dcm_done_MAX                           (1) // 0x00000001
  #define DDRDATA2_CR_DLLDCMCTL_dcm_done_DEF                           (0x00000000)
  #define DDRDATA2_CR_DLLDCMCTL_dcm_done_HSH                           (0x010A2124)

  #define DDRDATA2_CR_DLLDCMCTL_dcm_results_OFF                        (11)
  #define DDRDATA2_CR_DLLDCMCTL_dcm_results_WID                        (15)
  #define DDRDATA2_CR_DLLDCMCTL_dcm_results_MSK                        (0x03FFF800)
  #define DDRDATA2_CR_DLLDCMCTL_dcm_results_MIN                        (0)
  #define DDRDATA2_CR_DLLDCMCTL_dcm_results_MAX                        (32767) // 0x00007FFF
  #define DDRDATA2_CR_DLLDCMCTL_dcm_results_DEF                        (0x00000000)
  #define DDRDATA2_CR_DLLDCMCTL_dcm_results_HSH                        (0x0F0B2124)

  #define DDRDATA2_CR_DLLDCMCTL_spare0_OFF                             (26)
  #define DDRDATA2_CR_DLLDCMCTL_spare0_WID                             ( 6)
  #define DDRDATA2_CR_DLLDCMCTL_spare0_MSK                             (0xFC000000)
  #define DDRDATA2_CR_DLLDCMCTL_spare0_MIN                             (0)
  #define DDRDATA2_CR_DLLDCMCTL_spare0_MAX                             (63) // 0x0000003F
  #define DDRDATA2_CR_DLLDCMCTL_spare0_DEF                             (0x00000000)
  #define DDRDATA2_CR_DLLDCMCTL_spare0_HSH                             (0x061A2124)

#define DDRDATA3_CR_MASTERDLLCFG_REG                                   (0x00002180)

  #define DDRDATA3_CR_MASTERDLLCFG_LockThresh_OFF                      ( 0)
  #define DDRDATA3_CR_MASTERDLLCFG_LockThresh_WID                      ( 3)
  #define DDRDATA3_CR_MASTERDLLCFG_LockThresh_MSK                      (0x00000007)
  #define DDRDATA3_CR_MASTERDLLCFG_LockThresh_MIN                      (0)
  #define DDRDATA3_CR_MASTERDLLCFG_LockThresh_MAX                      (7) // 0x00000007
  #define DDRDATA3_CR_MASTERDLLCFG_LockThresh_DEF                      (0x00000004)
  #define DDRDATA3_CR_MASTERDLLCFG_LockThresh_HSH                      (0x03002180)

  #define DDRDATA3_CR_MASTERDLLCFG_LockCtr_OFF                         ( 3)
  #define DDRDATA3_CR_MASTERDLLCFG_LockCtr_WID                         ( 2)
  #define DDRDATA3_CR_MASTERDLLCFG_LockCtr_MSK                         (0x00000018)
  #define DDRDATA3_CR_MASTERDLLCFG_LockCtr_MIN                         (0)
  #define DDRDATA3_CR_MASTERDLLCFG_LockCtr_MAX                         (3) // 0x00000003
  #define DDRDATA3_CR_MASTERDLLCFG_LockCtr_DEF                         (0x00000000)
  #define DDRDATA3_CR_MASTERDLLCFG_LockCtr_HSH                         (0x02032180)

  #define DDRDATA3_CR_MASTERDLLCFG_VctrlDischRate_OFF                  ( 5)
  #define DDRDATA3_CR_MASTERDLLCFG_VctrlDischRate_WID                  ( 2)
  #define DDRDATA3_CR_MASTERDLLCFG_VctrlDischRate_MSK                  (0x00000060)
  #define DDRDATA3_CR_MASTERDLLCFG_VctrlDischRate_MIN                  (0)
  #define DDRDATA3_CR_MASTERDLLCFG_VctrlDischRate_MAX                  (3) // 0x00000003
  #define DDRDATA3_CR_MASTERDLLCFG_VctrlDischRate_DEF                  (0x00000000)
  #define DDRDATA3_CR_MASTERDLLCFG_VctrlDischRate_HSH                  (0x02052180)

  #define DDRDATA3_CR_MASTERDLLCFG_SelVctrlHi_OFF                      ( 7)
  #define DDRDATA3_CR_MASTERDLLCFG_SelVctrlHi_WID                      ( 1)
  #define DDRDATA3_CR_MASTERDLLCFG_SelVctrlHi_MSK                      (0x00000080)
  #define DDRDATA3_CR_MASTERDLLCFG_SelVctrlHi_MIN                      (0)
  #define DDRDATA3_CR_MASTERDLLCFG_SelVctrlHi_MAX                      (1) // 0x00000001
  #define DDRDATA3_CR_MASTERDLLCFG_SelVctrlHi_DEF                      (0x00000000)
  #define DDRDATA3_CR_MASTERDLLCFG_SelVctrlHi_HSH                      (0x01072180)

  #define DDRDATA3_CR_MASTERDLLCFG_StartupCntSel_OFF                   ( 8)
  #define DDRDATA3_CR_MASTERDLLCFG_StartupCntSel_WID                   ( 1)
  #define DDRDATA3_CR_MASTERDLLCFG_StartupCntSel_MSK                   (0x00000100)
  #define DDRDATA3_CR_MASTERDLLCFG_StartupCntSel_MIN                   (0)
  #define DDRDATA3_CR_MASTERDLLCFG_StartupCntSel_MAX                   (1) // 0x00000001
  #define DDRDATA3_CR_MASTERDLLCFG_StartupCntSel_DEF                   (0x00000000)
  #define DDRDATA3_CR_MASTERDLLCFG_StartupCntSel_HSH                   (0x01082180)

  #define DDRDATA3_CR_MASTERDLLCFG_LockSel_OFF                         ( 9)
  #define DDRDATA3_CR_MASTERDLLCFG_LockSel_WID                         ( 2)
  #define DDRDATA3_CR_MASTERDLLCFG_LockSel_MSK                         (0x00000600)
  #define DDRDATA3_CR_MASTERDLLCFG_LockSel_MIN                         (0)
  #define DDRDATA3_CR_MASTERDLLCFG_LockSel_MAX                         (3) // 0x00000003
  #define DDRDATA3_CR_MASTERDLLCFG_LockSel_DEF                         (0x00000000)
  #define DDRDATA3_CR_MASTERDLLCFG_LockSel_HSH                         (0x02092180)

  #define DDRDATA3_CR_MASTERDLLCFG_RstOvrd_OFF                         (11)
  #define DDRDATA3_CR_MASTERDLLCFG_RstOvrd_WID                         ( 1)
  #define DDRDATA3_CR_MASTERDLLCFG_RstOvrd_MSK                         (0x00000800)
  #define DDRDATA3_CR_MASTERDLLCFG_RstOvrd_MIN                         (0)
  #define DDRDATA3_CR_MASTERDLLCFG_RstOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA3_CR_MASTERDLLCFG_RstOvrd_DEF                         (0x00000000)
  #define DDRDATA3_CR_MASTERDLLCFG_RstOvrd_HSH                         (0x010B2180)

  #define DDRDATA3_CR_MASTERDLLCFG_SelRstOvrd_OFF                      (12)
  #define DDRDATA3_CR_MASTERDLLCFG_SelRstOvrd_WID                      ( 1)
  #define DDRDATA3_CR_MASTERDLLCFG_SelRstOvrd_MSK                      (0x00001000)
  #define DDRDATA3_CR_MASTERDLLCFG_SelRstOvrd_MIN                      (0)
  #define DDRDATA3_CR_MASTERDLLCFG_SelRstOvrd_MAX                      (1) // 0x00000001
  #define DDRDATA3_CR_MASTERDLLCFG_SelRstOvrd_DEF                      (0x00000000)
  #define DDRDATA3_CR_MASTERDLLCFG_SelRstOvrd_HSH                      (0x010C2180)

  #define DDRDATA3_CR_MASTERDLLCFG_TimeOutOvrd_OFF                     (13)
  #define DDRDATA3_CR_MASTERDLLCFG_TimeOutOvrd_WID                     ( 1)
  #define DDRDATA3_CR_MASTERDLLCFG_TimeOutOvrd_MSK                     (0x00002000)
  #define DDRDATA3_CR_MASTERDLLCFG_TimeOutOvrd_MIN                     (0)
  #define DDRDATA3_CR_MASTERDLLCFG_TimeOutOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA3_CR_MASTERDLLCFG_TimeOutOvrd_DEF                     (0x00000000)
  #define DDRDATA3_CR_MASTERDLLCFG_TimeOutOvrd_HSH                     (0x010D2180)

  #define DDRDATA3_CR_MASTERDLLCFG_SelTimeOutOvrd_OFF                  (14)
  #define DDRDATA3_CR_MASTERDLLCFG_SelTimeOutOvrd_WID                  ( 1)
  #define DDRDATA3_CR_MASTERDLLCFG_SelTimeOutOvrd_MSK                  (0x00004000)
  #define DDRDATA3_CR_MASTERDLLCFG_SelTimeOutOvrd_MIN                  (0)
  #define DDRDATA3_CR_MASTERDLLCFG_SelTimeOutOvrd_MAX                  (1) // 0x00000001
  #define DDRDATA3_CR_MASTERDLLCFG_SelTimeOutOvrd_DEF                  (0x00000000)
  #define DDRDATA3_CR_MASTERDLLCFG_SelTimeOutOvrd_HSH                  (0x010E2180)

  #define DDRDATA3_CR_MASTERDLLCFG_ClkGateOvrd_OFF                     (15)
  #define DDRDATA3_CR_MASTERDLLCFG_ClkGateOvrd_WID                     ( 1)
  #define DDRDATA3_CR_MASTERDLLCFG_ClkGateOvrd_MSK                     (0x00008000)
  #define DDRDATA3_CR_MASTERDLLCFG_ClkGateOvrd_MIN                     (0)
  #define DDRDATA3_CR_MASTERDLLCFG_ClkGateOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA3_CR_MASTERDLLCFG_ClkGateOvrd_DEF                     (0x00000000)
  #define DDRDATA3_CR_MASTERDLLCFG_ClkGateOvrd_HSH                     (0x010F2180)

  #define DDRDATA3_CR_MASTERDLLCFG_LockOvrd_OFF                        (16)
  #define DDRDATA3_CR_MASTERDLLCFG_LockOvrd_WID                        ( 1)
  #define DDRDATA3_CR_MASTERDLLCFG_LockOvrd_MSK                        (0x00010000)
  #define DDRDATA3_CR_MASTERDLLCFG_LockOvrd_MIN                        (0)
  #define DDRDATA3_CR_MASTERDLLCFG_LockOvrd_MAX                        (1) // 0x00000001
  #define DDRDATA3_CR_MASTERDLLCFG_LockOvrd_DEF                        (0x00000000)
  #define DDRDATA3_CR_MASTERDLLCFG_LockOvrd_HSH                        (0x01102180)

  #define DDRDATA3_CR_MASTERDLLCFG_SelLockOvrd_OFF                     (17)
  #define DDRDATA3_CR_MASTERDLLCFG_SelLockOvrd_WID                     ( 1)
  #define DDRDATA3_CR_MASTERDLLCFG_SelLockOvrd_MSK                     (0x00020000)
  #define DDRDATA3_CR_MASTERDLLCFG_SelLockOvrd_MIN                     (0)
  #define DDRDATA3_CR_MASTERDLLCFG_SelLockOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA3_CR_MASTERDLLCFG_SelLockOvrd_DEF                     (0x00000000)
  #define DDRDATA3_CR_MASTERDLLCFG_SelLockOvrd_HSH                     (0x01112180)

  #define DDRDATA3_CR_MASTERDLLCFG_OpenLoopOvrd_OFF                    (18)
  #define DDRDATA3_CR_MASTERDLLCFG_OpenLoopOvrd_WID                    ( 1)
  #define DDRDATA3_CR_MASTERDLLCFG_OpenLoopOvrd_MSK                    (0x00040000)
  #define DDRDATA3_CR_MASTERDLLCFG_OpenLoopOvrd_MIN                    (0)
  #define DDRDATA3_CR_MASTERDLLCFG_OpenLoopOvrd_MAX                    (1) // 0x00000001
  #define DDRDATA3_CR_MASTERDLLCFG_OpenLoopOvrd_DEF                    (0x00000000)
  #define DDRDATA3_CR_MASTERDLLCFG_OpenLoopOvrd_HSH                    (0x01122180)

  #define DDRDATA3_CR_MASTERDLLCFG_SelOpenLoopOvrd_OFF                 (19)
  #define DDRDATA3_CR_MASTERDLLCFG_SelOpenLoopOvrd_WID                 ( 1)
  #define DDRDATA3_CR_MASTERDLLCFG_SelOpenLoopOvrd_MSK                 (0x00080000)
  #define DDRDATA3_CR_MASTERDLLCFG_SelOpenLoopOvrd_MIN                 (0)
  #define DDRDATA3_CR_MASTERDLLCFG_SelOpenLoopOvrd_MAX                 (1) // 0x00000001
  #define DDRDATA3_CR_MASTERDLLCFG_SelOpenLoopOvrd_DEF                 (0x00000000)
  #define DDRDATA3_CR_MASTERDLLCFG_SelOpenLoopOvrd_HSH                 (0x01132180)

  #define DDRDATA3_CR_MASTERDLLCFG_WkLockEnOvrd_OFF                    (20)
  #define DDRDATA3_CR_MASTERDLLCFG_WkLockEnOvrd_WID                    ( 1)
  #define DDRDATA3_CR_MASTERDLLCFG_WkLockEnOvrd_MSK                    (0x00100000)
  #define DDRDATA3_CR_MASTERDLLCFG_WkLockEnOvrd_MIN                    (0)
  #define DDRDATA3_CR_MASTERDLLCFG_WkLockEnOvrd_MAX                    (1) // 0x00000001
  #define DDRDATA3_CR_MASTERDLLCFG_WkLockEnOvrd_DEF                    (0x00000000)
  #define DDRDATA3_CR_MASTERDLLCFG_WkLockEnOvrd_HSH                    (0x01142180)

  #define DDRDATA3_CR_MASTERDLLCFG_SelWkLockEnOvrd_OFF                 (21)
  #define DDRDATA3_CR_MASTERDLLCFG_SelWkLockEnOvrd_WID                 ( 1)
  #define DDRDATA3_CR_MASTERDLLCFG_SelWkLockEnOvrd_MSK                 (0x00200000)
  #define DDRDATA3_CR_MASTERDLLCFG_SelWkLockEnOvrd_MIN                 (0)
  #define DDRDATA3_CR_MASTERDLLCFG_SelWkLockEnOvrd_MAX                 (1) // 0x00000001
  #define DDRDATA3_CR_MASTERDLLCFG_SelWkLockEnOvrd_DEF                 (0x00000000)
  #define DDRDATA3_CR_MASTERDLLCFG_SelWkLockEnOvrd_HSH                 (0x01152180)

  #define DDRDATA3_CR_MASTERDLLCFG_CfdlDis_OFF                         (22)
  #define DDRDATA3_CR_MASTERDLLCFG_CfdlDis_WID                         ( 1)
  #define DDRDATA3_CR_MASTERDLLCFG_CfdlDis_MSK                         (0x00400000)
  #define DDRDATA3_CR_MASTERDLLCFG_CfdlDis_MIN                         (0)
  #define DDRDATA3_CR_MASTERDLLCFG_CfdlDis_MAX                         (1) // 0x00000001
  #define DDRDATA3_CR_MASTERDLLCFG_CfdlDis_DEF                         (0x00000000)
  #define DDRDATA3_CR_MASTERDLLCFG_CfdlDis_HSH                         (0x01162180)

  #define DDRDATA3_CR_MASTERDLLCFG_DftEn_OFF                           (23)
  #define DDRDATA3_CR_MASTERDLLCFG_DftEn_WID                           ( 1)
  #define DDRDATA3_CR_MASTERDLLCFG_DftEn_MSK                           (0x00800000)
  #define DDRDATA3_CR_MASTERDLLCFG_DftEn_MIN                           (0)
  #define DDRDATA3_CR_MASTERDLLCFG_DftEn_MAX                           (1) // 0x00000001
  #define DDRDATA3_CR_MASTERDLLCFG_DftEn_DEF                           (0x00000000)
  #define DDRDATA3_CR_MASTERDLLCFG_DftEn_HSH                           (0x01172180)

  #define DDRDATA3_CR_MASTERDLLCFG_spare0_OFF                          (24)
  #define DDRDATA3_CR_MASTERDLLCFG_spare0_WID                          ( 8)
  #define DDRDATA3_CR_MASTERDLLCFG_spare0_MSK                          (0xFF000000)
  #define DDRDATA3_CR_MASTERDLLCFG_spare0_MIN                          (0)
  #define DDRDATA3_CR_MASTERDLLCFG_spare0_MAX                          (255) // 0x000000FF
  #define DDRDATA3_CR_MASTERDLLCFG_spare0_DEF                          (0x00000000)
  #define DDRDATA3_CR_MASTERDLLCFG_spare0_HSH                          (0x08182180)

#define DDRDATA3_CR_CBTUNE0_REG                                        (0x00002184)

  #define DDRDATA3_CR_CBTUNE0_DllBWEn_OFF                              ( 0)
  #define DDRDATA3_CR_CBTUNE0_DllBWEn_WID                              (32)
  #define DDRDATA3_CR_CBTUNE0_DllBWEn_MSK                              (0xFFFFFFFF)
  #define DDRDATA3_CR_CBTUNE0_DllBWEn_MIN                              (0)
  #define DDRDATA3_CR_CBTUNE0_DllBWEn_MAX                              (4294967295) // 0xFFFFFFFF
  #define DDRDATA3_CR_CBTUNE0_DllBWEn_DEF                              (0xFDB86521)
  #define DDRDATA3_CR_CBTUNE0_DllBWEn_HSH                              (0x20002184)

#define DDRDATA3_CR_CBTUNE1_REG                                        (0x00002188)

  #define DDRDATA3_CR_CBTUNE1_PiCbEn_OFF                               ( 0)
  #define DDRDATA3_CR_CBTUNE1_PiCbEn_WID                               (24)
  #define DDRDATA3_CR_CBTUNE1_PiCbEn_MSK                               (0x00FFFFFF)
  #define DDRDATA3_CR_CBTUNE1_PiCbEn_MIN                               (0)
  #define DDRDATA3_CR_CBTUNE1_PiCbEn_MAX                               (16777215) // 0x00FFFFFF
  #define DDRDATA3_CR_CBTUNE1_PiCbEn_DEF                               (0x00249492)
  #define DDRDATA3_CR_CBTUNE1_PiCbEn_HSH                               (0x18002188)

  #define DDRDATA3_CR_CBTUNE1_CbEnRsvd_OFF                             (24)
  #define DDRDATA3_CR_CBTUNE1_CbEnRsvd_WID                             ( 3)
  #define DDRDATA3_CR_CBTUNE1_CbEnRsvd_MSK                             (0x07000000)
  #define DDRDATA3_CR_CBTUNE1_CbEnRsvd_MIN                             (0)
  #define DDRDATA3_CR_CBTUNE1_CbEnRsvd_MAX                             (7) // 0x00000007
  #define DDRDATA3_CR_CBTUNE1_CbEnRsvd_DEF                             (0x00000000)
  #define DDRDATA3_CR_CBTUNE1_CbEnRsvd_HSH                             (0x03182188)

  #define DDRDATA3_CR_CBTUNE1_CbEnDllFuse_OFF                          (27)
  #define DDRDATA3_CR_CBTUNE1_CbEnDllFuse_WID                          ( 3)
  #define DDRDATA3_CR_CBTUNE1_CbEnDllFuse_MSK                          (0x38000000)
  #define DDRDATA3_CR_CBTUNE1_CbEnDllFuse_MIN                          (0)
  #define DDRDATA3_CR_CBTUNE1_CbEnDllFuse_MAX                          (7) // 0x00000007
  #define DDRDATA3_CR_CBTUNE1_CbEnDllFuse_DEF                          (0x00000002)
  #define DDRDATA3_CR_CBTUNE1_CbEnDllFuse_HSH                          (0x031B2188)

  #define DDRDATA3_CR_CBTUNE1_Spare_OFF                                (30)
  #define DDRDATA3_CR_CBTUNE1_Spare_WID                                ( 2)
  #define DDRDATA3_CR_CBTUNE1_Spare_MSK                                (0xC0000000)
  #define DDRDATA3_CR_CBTUNE1_Spare_MIN                                (0)
  #define DDRDATA3_CR_CBTUNE1_Spare_MAX                                (3) // 0x00000003
  #define DDRDATA3_CR_CBTUNE1_Spare_DEF                                (0x00000000)
  #define DDRDATA3_CR_CBTUNE1_Spare_HSH                                (0x021E2188)

#define DDRDATA3_CR_ADCCFG_REG                                         (0x0000218C)

  #define DDRDATA3_CR_ADCCFG_ADC_frz_OFF                               ( 0)
  #define DDRDATA3_CR_ADCCFG_ADC_frz_WID                               ( 1)
  #define DDRDATA3_CR_ADCCFG_ADC_frz_MSK                               (0x00000001)
  #define DDRDATA3_CR_ADCCFG_ADC_frz_MIN                               (0)
  #define DDRDATA3_CR_ADCCFG_ADC_frz_MAX                               (1) // 0x00000001
  #define DDRDATA3_CR_ADCCFG_ADC_frz_DEF                               (0x00000000)
  #define DDRDATA3_CR_ADCCFG_ADC_frz_HSH                               (0x0100218C)

  #define DDRDATA3_CR_ADCCFG_ADC_en_OFF                                ( 1)
  #define DDRDATA3_CR_ADCCFG_ADC_en_WID                                ( 1)
  #define DDRDATA3_CR_ADCCFG_ADC_en_MSK                                (0x00000002)
  #define DDRDATA3_CR_ADCCFG_ADC_en_MIN                                (0)
  #define DDRDATA3_CR_ADCCFG_ADC_en_MAX                                (1) // 0x00000001
  #define DDRDATA3_CR_ADCCFG_ADC_en_DEF                                (0x00000000)
  #define DDRDATA3_CR_ADCCFG_ADC_en_HSH                                (0x0101218C)

  #define DDRDATA3_CR_ADCCFG_ADCclkdiv_OFF                             ( 2)
  #define DDRDATA3_CR_ADCCFG_ADCclkdiv_WID                             ( 2)
  #define DDRDATA3_CR_ADCCFG_ADCclkdiv_MSK                             (0x0000000C)
  #define DDRDATA3_CR_ADCCFG_ADCclkdiv_MIN                             (0)
  #define DDRDATA3_CR_ADCCFG_ADCclkdiv_MAX                             (3) // 0x00000003
  #define DDRDATA3_CR_ADCCFG_ADCclkdiv_DEF                             (0x00000000)
  #define DDRDATA3_CR_ADCCFG_ADCclkdiv_HSH                             (0x0202218C)

  #define DDRDATA3_CR_ADCCFG_ADCstartcount_OFF                         ( 4)
  #define DDRDATA3_CR_ADCCFG_ADCstartcount_WID                         ( 2)
  #define DDRDATA3_CR_ADCCFG_ADCstartcount_MSK                         (0x00000030)
  #define DDRDATA3_CR_ADCCFG_ADCstartcount_MIN                         (0)
  #define DDRDATA3_CR_ADCCFG_ADCstartcount_MAX                         (3) // 0x00000003
  #define DDRDATA3_CR_ADCCFG_ADCstartcount_DEF                         (0x00000000)
  #define DDRDATA3_CR_ADCCFG_ADCstartcount_HSH                         (0x0204218C)

  #define DDRDATA3_CR_ADCCFG_ADCChopEn_OFF                             ( 6)
  #define DDRDATA3_CR_ADCCFG_ADCChopEn_WID                             ( 1)
  #define DDRDATA3_CR_ADCCFG_ADCChopEn_MSK                             (0x00000040)
  #define DDRDATA3_CR_ADCCFG_ADCChopEn_MIN                             (0)
  #define DDRDATA3_CR_ADCCFG_ADCChopEn_MAX                             (1) // 0x00000001
  #define DDRDATA3_CR_ADCCFG_ADCChopEn_DEF                             (0x00000000)
  #define DDRDATA3_CR_ADCCFG_ADCChopEn_HSH                             (0x0106218C)

  #define DDRDATA3_CR_ADCCFG_Spare_OFF                                 ( 7)
  #define DDRDATA3_CR_ADCCFG_Spare_WID                                 (25)
  #define DDRDATA3_CR_ADCCFG_Spare_MSK                                 (0xFFFFFF80)
  #define DDRDATA3_CR_ADCCFG_Spare_MIN                                 (0)
  #define DDRDATA3_CR_ADCCFG_Spare_MAX                                 (33554431) // 0x01FFFFFF
  #define DDRDATA3_CR_ADCCFG_Spare_DEF                                 (0x00000000)
  #define DDRDATA3_CR_ADCCFG_Spare_HSH                                 (0x1907218C)

#define DDRDATA3_CR_CBTUNE2_REG                                        (0x00002190)

  #define DDRDATA3_CR_CBTUNE2_DllCbEn_OFF                              ( 0)
  #define DDRDATA3_CR_CBTUNE2_DllCbEn_WID                              (16)
  #define DDRDATA3_CR_CBTUNE2_DllCbEn_MSK                              (0x0000FFFF)
  #define DDRDATA3_CR_CBTUNE2_DllCbEn_MIN                              (0)
  #define DDRDATA3_CR_CBTUNE2_DllCbEn_MAX                              (65535) // 0x0000FFFF
  #define DDRDATA3_CR_CBTUNE2_DllCbEn_DEF                              (0x00000000)
  #define DDRDATA3_CR_CBTUNE2_DllCbEn_HSH                              (0x10002190)

  #define DDRDATA3_CR_CBTUNE2_Spare_OFF                                (16)
  #define DDRDATA3_CR_CBTUNE2_Spare_WID                                (16)
  #define DDRDATA3_CR_CBTUNE2_Spare_MSK                                (0xFFFF0000)
  #define DDRDATA3_CR_CBTUNE2_Spare_MIN                                (0)
  #define DDRDATA3_CR_CBTUNE2_Spare_MAX                                (65535) // 0x0000FFFF
  #define DDRDATA3_CR_CBTUNE2_Spare_DEF                                (0x00000000)
  #define DDRDATA3_CR_CBTUNE2_Spare_HSH                                (0x10102190)

#define DDRDATA3_CR_PIDFTDLY_REG                                       (0x00002198)

  #define DDRDATA3_CR_PIDFTDLY_PiDftDelay_OFF                          ( 0)
  #define DDRDATA3_CR_PIDFTDLY_PiDftDelay_WID                          ( 7)
  #define DDRDATA3_CR_PIDFTDLY_PiDftDelay_MSK                          (0x0000007F)
  #define DDRDATA3_CR_PIDFTDLY_PiDftDelay_MIN                          (0)
  #define DDRDATA3_CR_PIDFTDLY_PiDftDelay_MAX                          (127) // 0x0000007F
  #define DDRDATA3_CR_PIDFTDLY_PiDftDelay_DEF                          (0x00000000)
  #define DDRDATA3_CR_PIDFTDLY_PiDftDelay_HSH                          (0x07002198)

  #define DDRDATA3_CR_PIDFTDLY_Ch0PiEnOvrd_OFF                         ( 7)
  #define DDRDATA3_CR_PIDFTDLY_Ch0PiEnOvrd_WID                         ( 1)
  #define DDRDATA3_CR_PIDFTDLY_Ch0PiEnOvrd_MSK                         (0x00000080)
  #define DDRDATA3_CR_PIDFTDLY_Ch0PiEnOvrd_MIN                         (0)
  #define DDRDATA3_CR_PIDFTDLY_Ch0PiEnOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA3_CR_PIDFTDLY_Ch0PiEnOvrd_DEF                         (0x00000000)
  #define DDRDATA3_CR_PIDFTDLY_Ch0PiEnOvrd_HSH                         (0x01072198)

  #define DDRDATA3_CR_PIDFTDLY_Ch1PiEnOvrd_OFF                         ( 8)
  #define DDRDATA3_CR_PIDFTDLY_Ch1PiEnOvrd_WID                         ( 1)
  #define DDRDATA3_CR_PIDFTDLY_Ch1PiEnOvrd_MSK                         (0x00000100)
  #define DDRDATA3_CR_PIDFTDLY_Ch1PiEnOvrd_MIN                         (0)
  #define DDRDATA3_CR_PIDFTDLY_Ch1PiEnOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA3_CR_PIDFTDLY_Ch1PiEnOvrd_DEF                         (0x00000000)
  #define DDRDATA3_CR_PIDFTDLY_Ch1PiEnOvrd_HSH                         (0x01082198)

  #define DDRDATA3_CR_PIDFTDLY_Ch0PiDFTEn_OFF                          ( 9)
  #define DDRDATA3_CR_PIDFTDLY_Ch0PiDFTEn_WID                          ( 1)
  #define DDRDATA3_CR_PIDFTDLY_Ch0PiDFTEn_MSK                          (0x00000200)
  #define DDRDATA3_CR_PIDFTDLY_Ch0PiDFTEn_MIN                          (0)
  #define DDRDATA3_CR_PIDFTDLY_Ch0PiDFTEn_MAX                          (1) // 0x00000001
  #define DDRDATA3_CR_PIDFTDLY_Ch0PiDFTEn_DEF                          (0x00000000)
  #define DDRDATA3_CR_PIDFTDLY_Ch0PiDFTEn_HSH                          (0x01092198)

  #define DDRDATA3_CR_PIDFTDLY_Ch1PiDFTEn_OFF                          (10)
  #define DDRDATA3_CR_PIDFTDLY_Ch1PiDFTEn_WID                          ( 1)
  #define DDRDATA3_CR_PIDFTDLY_Ch1PiDFTEn_MSK                          (0x00000400)
  #define DDRDATA3_CR_PIDFTDLY_Ch1PiDFTEn_MIN                          (0)
  #define DDRDATA3_CR_PIDFTDLY_Ch1PiDFTEn_MAX                          (1) // 0x00000001
  #define DDRDATA3_CR_PIDFTDLY_Ch1PiDFTEn_DEF                          (0x00000000)
  #define DDRDATA3_CR_PIDFTDLY_Ch1PiDFTEn_HSH                          (0x010A2198)

  #define DDRDATA3_CR_PIDFTDLY_Spare_OFF                               (11)
  #define DDRDATA3_CR_PIDFTDLY_Spare_WID                               ( 4)
  #define DDRDATA3_CR_PIDFTDLY_Spare_MSK                               (0x00007800)
  #define DDRDATA3_CR_PIDFTDLY_Spare_MIN                               (0)
  #define DDRDATA3_CR_PIDFTDLY_Spare_MAX                               (15) // 0x0000000F
  #define DDRDATA3_CR_PIDFTDLY_Spare_DEF                               (0x00000000)
  #define DDRDATA3_CR_PIDFTDLY_Spare_HSH                               (0x040B2198)

  #define DDRDATA3_CR_PIDFTDLY_RefPiOvrd_OFF                           (15)
  #define DDRDATA3_CR_PIDFTDLY_RefPiOvrd_WID                           ( 1)
  #define DDRDATA3_CR_PIDFTDLY_RefPiOvrd_MSK                           (0x00008000)
  #define DDRDATA3_CR_PIDFTDLY_RefPiOvrd_MIN                           (0)
  #define DDRDATA3_CR_PIDFTDLY_RefPiOvrd_MAX                           (1) // 0x00000001
  #define DDRDATA3_CR_PIDFTDLY_RefPiOvrd_DEF                           (0x00000000)
  #define DDRDATA3_CR_PIDFTDLY_RefPiOvrd_HSH                           (0x010F2198)

  #define DDRDATA3_CR_PIDFTDLY_Rsvd_OFF                                (16)
  #define DDRDATA3_CR_PIDFTDLY_Rsvd_WID                                (16)
  #define DDRDATA3_CR_PIDFTDLY_Rsvd_MSK                                (0xFFFF0000)
  #define DDRDATA3_CR_PIDFTDLY_Rsvd_MIN                                (0)
  #define DDRDATA3_CR_PIDFTDLY_Rsvd_MAX                                (65535) // 0x0000FFFF
  #define DDRDATA3_CR_PIDFTDLY_Rsvd_DEF                                (0x00000000)
  #define DDRDATA3_CR_PIDFTDLY_Rsvd_HSH                                (0x10102198)

#define DDRDATA3_CR_DLLPITESTANDADC_REG                                (0x0000219C)

  #define DDRDATA3_CR_DLLPITESTANDADC_RunTest_OFF                      ( 0)
  #define DDRDATA3_CR_DLLPITESTANDADC_RunTest_WID                      ( 1)
  #define DDRDATA3_CR_DLLPITESTANDADC_RunTest_MSK                      (0x00000001)
  #define DDRDATA3_CR_DLLPITESTANDADC_RunTest_MIN                      (0)
  #define DDRDATA3_CR_DLLPITESTANDADC_RunTest_MAX                      (1) // 0x00000001
  #define DDRDATA3_CR_DLLPITESTANDADC_RunTest_DEF                      (0x00000000)
  #define DDRDATA3_CR_DLLPITESTANDADC_RunTest_HSH                      (0x0100219C)

  #define DDRDATA3_CR_DLLPITESTANDADC_Load_OFF                         ( 1)
  #define DDRDATA3_CR_DLLPITESTANDADC_Load_WID                         ( 1)
  #define DDRDATA3_CR_DLLPITESTANDADC_Load_MSK                         (0x00000002)
  #define DDRDATA3_CR_DLLPITESTANDADC_Load_MIN                         (0)
  #define DDRDATA3_CR_DLLPITESTANDADC_Load_MAX                         (1) // 0x00000001
  #define DDRDATA3_CR_DLLPITESTANDADC_Load_DEF                         (0x00000000)
  #define DDRDATA3_CR_DLLPITESTANDADC_Load_HSH                         (0x0101219C)

  #define DDRDATA3_CR_DLLPITESTANDADC_ModeHVM_OFF                      ( 2)
  #define DDRDATA3_CR_DLLPITESTANDADC_ModeHVM_WID                      ( 1)
  #define DDRDATA3_CR_DLLPITESTANDADC_ModeHVM_MSK                      (0x00000004)
  #define DDRDATA3_CR_DLLPITESTANDADC_ModeHVM_MIN                      (0)
  #define DDRDATA3_CR_DLLPITESTANDADC_ModeHVM_MAX                      (1) // 0x00000001
  #define DDRDATA3_CR_DLLPITESTANDADC_ModeHVM_DEF                      (0x00000000)
  #define DDRDATA3_CR_DLLPITESTANDADC_ModeHVM_HSH                      (0x0102219C)

  #define DDRDATA3_CR_DLLPITESTANDADC_ModeDV_OFF                       ( 3)
  #define DDRDATA3_CR_DLLPITESTANDADC_ModeDV_WID                       ( 1)
  #define DDRDATA3_CR_DLLPITESTANDADC_ModeDV_MSK                       (0x00000008)
  #define DDRDATA3_CR_DLLPITESTANDADC_ModeDV_MIN                       (0)
  #define DDRDATA3_CR_DLLPITESTANDADC_ModeDV_MAX                       (1) // 0x00000001
  #define DDRDATA3_CR_DLLPITESTANDADC_ModeDV_DEF                       (0x00000000)
  #define DDRDATA3_CR_DLLPITESTANDADC_ModeDV_HSH                       (0x0103219C)

  #define DDRDATA3_CR_DLLPITESTANDADC_CalCfdl_OFF                      ( 4)
  #define DDRDATA3_CR_DLLPITESTANDADC_CalCfdl_WID                      ( 1)
  #define DDRDATA3_CR_DLLPITESTANDADC_CalCfdl_MSK                      (0x00000010)
  #define DDRDATA3_CR_DLLPITESTANDADC_CalCfdl_MIN                      (0)
  #define DDRDATA3_CR_DLLPITESTANDADC_CalCfdl_MAX                      (1) // 0x00000001
  #define DDRDATA3_CR_DLLPITESTANDADC_CalCfdl_DEF                      (0x00000000)
  #define DDRDATA3_CR_DLLPITESTANDADC_CalCfdl_HSH                      (0x0104219C)

  #define DDRDATA3_CR_DLLPITESTANDADC_LoadCount_OFF                    ( 5)
  #define DDRDATA3_CR_DLLPITESTANDADC_LoadCount_WID                    (10)
  #define DDRDATA3_CR_DLLPITESTANDADC_LoadCount_MSK                    (0x00007FE0)
  #define DDRDATA3_CR_DLLPITESTANDADC_LoadCount_MIN                    (0)
  #define DDRDATA3_CR_DLLPITESTANDADC_LoadCount_MAX                    (1023) // 0x000003FF
  #define DDRDATA3_CR_DLLPITESTANDADC_LoadCount_DEF                    (0x00000000)
  #define DDRDATA3_CR_DLLPITESTANDADC_LoadCount_HSH                    (0x0A05219C)

  #define DDRDATA3_CR_DLLPITESTANDADC_CountStatus_OFF                  (15)
  #define DDRDATA3_CR_DLLPITESTANDADC_CountStatus_WID                  (10)
  #define DDRDATA3_CR_DLLPITESTANDADC_CountStatus_MSK                  (0x01FF8000)
  #define DDRDATA3_CR_DLLPITESTANDADC_CountStatus_MIN                  (0)
  #define DDRDATA3_CR_DLLPITESTANDADC_CountStatus_MAX                  (1023) // 0x000003FF
  #define DDRDATA3_CR_DLLPITESTANDADC_CountStatus_DEF                  (0x00000000)
  #define DDRDATA3_CR_DLLPITESTANDADC_CountStatus_HSH                  (0x0A0F219C)

  #define DDRDATA3_CR_DLLPITESTANDADC_ModeADC_OFF                      (25)
  #define DDRDATA3_CR_DLLPITESTANDADC_ModeADC_WID                      ( 1)
  #define DDRDATA3_CR_DLLPITESTANDADC_ModeADC_MSK                      (0x02000000)
  #define DDRDATA3_CR_DLLPITESTANDADC_ModeADC_MIN                      (0)
  #define DDRDATA3_CR_DLLPITESTANDADC_ModeADC_MAX                      (1) // 0x00000001
  #define DDRDATA3_CR_DLLPITESTANDADC_ModeADC_DEF                      (0x00000000)
  #define DDRDATA3_CR_DLLPITESTANDADC_ModeADC_HSH                      (0x0119219C)

  #define DDRDATA3_CR_DLLPITESTANDADC_ADCClkDiv_OFF                    (26)
  #define DDRDATA3_CR_DLLPITESTANDADC_ADCClkDiv_WID                    ( 2)
  #define DDRDATA3_CR_DLLPITESTANDADC_ADCClkDiv_MSK                    (0x0C000000)
  #define DDRDATA3_CR_DLLPITESTANDADC_ADCClkDiv_MIN                    (0)
  #define DDRDATA3_CR_DLLPITESTANDADC_ADCClkDiv_MAX                    (3) // 0x00000003
  #define DDRDATA3_CR_DLLPITESTANDADC_ADCClkDiv_DEF                    (0x00000000)
  #define DDRDATA3_CR_DLLPITESTANDADC_ADCClkDiv_HSH                    (0x021A219C)

  #define DDRDATA3_CR_DLLPITESTANDADC_ADCDdrChanSel_OFF                (28)
  #define DDRDATA3_CR_DLLPITESTANDADC_ADCDdrChanSel_WID                ( 1)
  #define DDRDATA3_CR_DLLPITESTANDADC_ADCDdrChanSel_MSK                (0x10000000)
  #define DDRDATA3_CR_DLLPITESTANDADC_ADCDdrChanSel_MIN                (0)
  #define DDRDATA3_CR_DLLPITESTANDADC_ADCDdrChanSel_MAX                (1) // 0x00000001
  #define DDRDATA3_CR_DLLPITESTANDADC_ADCDdrChanSel_DEF                (0x00000000)
  #define DDRDATA3_CR_DLLPITESTANDADC_ADCDdrChanSel_HSH                (0x011C219C)

  #define DDRDATA3_CR_DLLPITESTANDADC_ADCChopEn_OFF                    (29)
  #define DDRDATA3_CR_DLLPITESTANDADC_ADCChopEn_WID                    ( 1)
  #define DDRDATA3_CR_DLLPITESTANDADC_ADCChopEn_MSK                    (0x20000000)
  #define DDRDATA3_CR_DLLPITESTANDADC_ADCChopEn_MIN                    (0)
  #define DDRDATA3_CR_DLLPITESTANDADC_ADCChopEn_MAX                    (1) // 0x00000001
  #define DDRDATA3_CR_DLLPITESTANDADC_ADCChopEn_DEF                    (0x00000000)
  #define DDRDATA3_CR_DLLPITESTANDADC_ADCChopEn_HSH                    (0x011D219C)

  #define DDRDATA3_CR_DLLPITESTANDADC_ADCDone_OFF                      (30)
  #define DDRDATA3_CR_DLLPITESTANDADC_ADCDone_WID                      ( 1)
  #define DDRDATA3_CR_DLLPITESTANDADC_ADCDone_MSK                      (0x40000000)
  #define DDRDATA3_CR_DLLPITESTANDADC_ADCDone_MIN                      (0)
  #define DDRDATA3_CR_DLLPITESTANDADC_ADCDone_MAX                      (1) // 0x00000001
  #define DDRDATA3_CR_DLLPITESTANDADC_ADCDone_DEF                      (0x00000000)
  #define DDRDATA3_CR_DLLPITESTANDADC_ADCDone_HSH                      (0x011E219C)

  #define DDRDATA3_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF             (31)
  #define DDRDATA3_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID             ( 1)
  #define DDRDATA3_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK             (0x80000000)
  #define DDRDATA3_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN             (0)
  #define DDRDATA3_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX             (1) // 0x00000001
  #define DDRDATA3_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF             (0x00000000)
  #define DDRDATA3_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH             (0x011F219C)

#define DDRDATA3_CR_DLLSTATUS_REG                                      (0x000021A0)

  #define DDRDATA3_CR_DLLSTATUS_DetrmLockStat_OFF                      ( 0)
  #define DDRDATA3_CR_DLLSTATUS_DetrmLockStat_WID                      ( 1)
  #define DDRDATA3_CR_DLLSTATUS_DetrmLockStat_MSK                      (0x00000001)
  #define DDRDATA3_CR_DLLSTATUS_DetrmLockStat_MIN                      (0)
  #define DDRDATA3_CR_DLLSTATUS_DetrmLockStat_MAX                      (1) // 0x00000001
  #define DDRDATA3_CR_DLLSTATUS_DetrmLockStat_DEF                      (0x00000000)
  #define DDRDATA3_CR_DLLSTATUS_DetrmLockStat_HSH                      (0x010021A0)

  #define DDRDATA3_CR_DLLSTATUS_FuncLockStat_OFF                       ( 1)
  #define DDRDATA3_CR_DLLSTATUS_FuncLockStat_WID                       ( 1)
  #define DDRDATA3_CR_DLLSTATUS_FuncLockStat_MSK                       (0x00000002)
  #define DDRDATA3_CR_DLLSTATUS_FuncLockStat_MIN                       (0)
  #define DDRDATA3_CR_DLLSTATUS_FuncLockStat_MAX                       (1) // 0x00000001
  #define DDRDATA3_CR_DLLSTATUS_FuncLockStat_DEF                       (0x00000000)
  #define DDRDATA3_CR_DLLSTATUS_FuncLockStat_HSH                       (0x010121A0)

  #define DDRDATA3_CR_DLLSTATUS_Lock_OFF                               ( 2)
  #define DDRDATA3_CR_DLLSTATUS_Lock_WID                               ( 1)
  #define DDRDATA3_CR_DLLSTATUS_Lock_MSK                               (0x00000004)
  #define DDRDATA3_CR_DLLSTATUS_Lock_MIN                               (0)
  #define DDRDATA3_CR_DLLSTATUS_Lock_MAX                               (1) // 0x00000001
  #define DDRDATA3_CR_DLLSTATUS_Lock_DEF                               (0x00000000)
  #define DDRDATA3_CR_DLLSTATUS_Lock_HSH                               (0x010221A0)

  #define DDRDATA3_CR_DLLSTATUS_Timeout_OFF                            ( 3)
  #define DDRDATA3_CR_DLLSTATUS_Timeout_WID                            ( 1)
  #define DDRDATA3_CR_DLLSTATUS_Timeout_MSK                            (0x00000008)
  #define DDRDATA3_CR_DLLSTATUS_Timeout_MIN                            (0)
  #define DDRDATA3_CR_DLLSTATUS_Timeout_MAX                            (1) // 0x00000001
  #define DDRDATA3_CR_DLLSTATUS_Timeout_DEF                            (0x00000000)
  #define DDRDATA3_CR_DLLSTATUS_Timeout_HSH                            (0x010321A0)

  #define DDRDATA3_CR_DLLSTATUS_DllReset_OFF                           ( 4)
  #define DDRDATA3_CR_DLLSTATUS_DllReset_WID                           ( 1)
  #define DDRDATA3_CR_DLLSTATUS_DllReset_MSK                           (0x00000010)
  #define DDRDATA3_CR_DLLSTATUS_DllReset_MIN                           (0)
  #define DDRDATA3_CR_DLLSTATUS_DllReset_MAX                           (1) // 0x00000001
  #define DDRDATA3_CR_DLLSTATUS_DllReset_DEF                           (0x00000000)
  #define DDRDATA3_CR_DLLSTATUS_DllReset_HSH                           (0x010421A0)

  #define DDRDATA3_CR_DLLSTATUS_LongLockStat_OFF                       ( 5)
  #define DDRDATA3_CR_DLLSTATUS_LongLockStat_WID                       ( 1)
  #define DDRDATA3_CR_DLLSTATUS_LongLockStat_MSK                       (0x00000020)
  #define DDRDATA3_CR_DLLSTATUS_LongLockStat_MIN                       (0)
  #define DDRDATA3_CR_DLLSTATUS_LongLockStat_MAX                       (1) // 0x00000001
  #define DDRDATA3_CR_DLLSTATUS_LongLockStat_DEF                       (0x00000000)
  #define DDRDATA3_CR_DLLSTATUS_LongLockStat_HSH                       (0x010521A0)

  #define DDRDATA3_CR_DLLSTATUS_EarlyLockStat_OFF                      ( 6)
  #define DDRDATA3_CR_DLLSTATUS_EarlyLockStat_WID                      ( 1)
  #define DDRDATA3_CR_DLLSTATUS_EarlyLockStat_MSK                      (0x00000040)
  #define DDRDATA3_CR_DLLSTATUS_EarlyLockStat_MIN                      (0)
  #define DDRDATA3_CR_DLLSTATUS_EarlyLockStat_MAX                      (1) // 0x00000001
  #define DDRDATA3_CR_DLLSTATUS_EarlyLockStat_DEF                      (0x00000000)
  #define DDRDATA3_CR_DLLSTATUS_EarlyLockStat_HSH                      (0x010621A0)

  #define DDRDATA3_CR_DLLSTATUS_NormalMode_NotWkLock_OFF               ( 7)
  #define DDRDATA3_CR_DLLSTATUS_NormalMode_NotWkLock_WID               ( 1)
  #define DDRDATA3_CR_DLLSTATUS_NormalMode_NotWkLock_MSK               (0x00000080)
  #define DDRDATA3_CR_DLLSTATUS_NormalMode_NotWkLock_MIN               (0)
  #define DDRDATA3_CR_DLLSTATUS_NormalMode_NotWkLock_MAX               (1) // 0x00000001
  #define DDRDATA3_CR_DLLSTATUS_NormalMode_NotWkLock_DEF               (0x00000000)
  #define DDRDATA3_CR_DLLSTATUS_NormalMode_NotWkLock_HSH               (0x010721A0)

  #define DDRDATA3_CR_DLLSTATUS_ADCout_OFF                             ( 8)
  #define DDRDATA3_CR_DLLSTATUS_ADCout_WID                             (10)
  #define DDRDATA3_CR_DLLSTATUS_ADCout_MSK                             (0x0003FF00)
  #define DDRDATA3_CR_DLLSTATUS_ADCout_MIN                             (0)
  #define DDRDATA3_CR_DLLSTATUS_ADCout_MAX                             (1023) // 0x000003FF
  #define DDRDATA3_CR_DLLSTATUS_ADCout_DEF                             (0x00000000)
  #define DDRDATA3_CR_DLLSTATUS_ADCout_HSH                             (0x0A0821A0)

  #define DDRDATA3_CR_DLLSTATUS_ADCStatus_OFF                          (18)
  #define DDRDATA3_CR_DLLSTATUS_ADCStatus_WID                          ( 1)
  #define DDRDATA3_CR_DLLSTATUS_ADCStatus_MSK                          (0x00040000)
  #define DDRDATA3_CR_DLLSTATUS_ADCStatus_MIN                          (0)
  #define DDRDATA3_CR_DLLSTATUS_ADCStatus_MAX                          (1) // 0x00000001
  #define DDRDATA3_CR_DLLSTATUS_ADCStatus_DEF                          (0x00000000)
  #define DDRDATA3_CR_DLLSTATUS_ADCStatus_HSH                          (0x011221A0)

  #define DDRDATA3_CR_DLLSTATUS_pilags_OFF                             (19)
  #define DDRDATA3_CR_DLLSTATUS_pilags_WID                             ( 1)
  #define DDRDATA3_CR_DLLSTATUS_pilags_MSK                             (0x00080000)
  #define DDRDATA3_CR_DLLSTATUS_pilags_MIN                             (0)
  #define DDRDATA3_CR_DLLSTATUS_pilags_MAX                             (1) // 0x00000001
  #define DDRDATA3_CR_DLLSTATUS_pilags_DEF                             (0x00000000)
  #define DDRDATA3_CR_DLLSTATUS_pilags_HSH                             (0x011321A0)

  #define DDRDATA3_CR_DLLSTATUS_spare_OFF                              (20)
  #define DDRDATA3_CR_DLLSTATUS_spare_WID                              (12)
  #define DDRDATA3_CR_DLLSTATUS_spare_MSK                              (0xFFF00000)
  #define DDRDATA3_CR_DLLSTATUS_spare_MIN                              (0)
  #define DDRDATA3_CR_DLLSTATUS_spare_MAX                              (4095) // 0x00000FFF
  #define DDRDATA3_CR_DLLSTATUS_spare_DEF                              (0x00000000)
  #define DDRDATA3_CR_DLLSTATUS_spare_HSH                              (0x0C1421A0)

#define DDRDATA3_CR_DLLDCMCTL_REG                                      (0x000021A4)

  #define DDRDATA3_CR_DLLDCMCTL_start_OFF                              ( 0)
  #define DDRDATA3_CR_DLLDCMCTL_start_WID                              ( 1)
  #define DDRDATA3_CR_DLLDCMCTL_start_MSK                              (0x00000001)
  #define DDRDATA3_CR_DLLDCMCTL_start_MIN                              (0)
  #define DDRDATA3_CR_DLLDCMCTL_start_MAX                              (1) // 0x00000001
  #define DDRDATA3_CR_DLLDCMCTL_start_DEF                              (0x00000000)
  #define DDRDATA3_CR_DLLDCMCTL_start_HSH                              (0x010021A4)

  #define DDRDATA3_CR_DLLDCMCTL_clken_OFF                              ( 1)
  #define DDRDATA3_CR_DLLDCMCTL_clken_WID                              ( 1)
  #define DDRDATA3_CR_DLLDCMCTL_clken_MSK                              (0x00000002)
  #define DDRDATA3_CR_DLLDCMCTL_clken_MIN                              (0)
  #define DDRDATA3_CR_DLLDCMCTL_clken_MAX                              (1) // 0x00000001
  #define DDRDATA3_CR_DLLDCMCTL_clken_DEF                              (0x00000000)
  #define DDRDATA3_CR_DLLDCMCTL_clken_HSH                              (0x010121A4)

  #define DDRDATA3_CR_DLLDCMCTL_dcm_dccctl_en_OFF                      ( 2)
  #define DDRDATA3_CR_DLLDCMCTL_dcm_dccctl_en_WID                      ( 1)
  #define DDRDATA3_CR_DLLDCMCTL_dcm_dccctl_en_MSK                      (0x00000004)
  #define DDRDATA3_CR_DLLDCMCTL_dcm_dccctl_en_MIN                      (0)
  #define DDRDATA3_CR_DLLDCMCTL_dcm_dccctl_en_MAX                      (1) // 0x00000001
  #define DDRDATA3_CR_DLLDCMCTL_dcm_dccctl_en_DEF                      (0x00000000)
  #define DDRDATA3_CR_DLLDCMCTL_dcm_dccctl_en_HSH                      (0x010221A4)

  #define DDRDATA3_CR_DLLDCMCTL_dccctl_OFF                             ( 3)
  #define DDRDATA3_CR_DLLDCMCTL_dccctl_WID                             ( 4)
  #define DDRDATA3_CR_DLLDCMCTL_dccctl_MSK                             (0x00000078)
  #define DDRDATA3_CR_DLLDCMCTL_dccctl_MIN                             (0)
  #define DDRDATA3_CR_DLLDCMCTL_dccctl_MAX                             (15) // 0x0000000F
  #define DDRDATA3_CR_DLLDCMCTL_dccctl_DEF                             (0x00000000)
  #define DDRDATA3_CR_DLLDCMCTL_dccctl_HSH                             (0x040321A4)

  #define DDRDATA3_CR_DLLDCMCTL_duration_OFF                           ( 7)
  #define DDRDATA3_CR_DLLDCMCTL_duration_WID                           ( 3)
  #define DDRDATA3_CR_DLLDCMCTL_duration_MSK                           (0x00000380)
  #define DDRDATA3_CR_DLLDCMCTL_duration_MIN                           (0)
  #define DDRDATA3_CR_DLLDCMCTL_duration_MAX                           (7) // 0x00000007
  #define DDRDATA3_CR_DLLDCMCTL_duration_DEF                           (0x00000000)
  #define DDRDATA3_CR_DLLDCMCTL_duration_HSH                           (0x030721A4)

  #define DDRDATA3_CR_DLLDCMCTL_dcm_done_OFF                           (10)
  #define DDRDATA3_CR_DLLDCMCTL_dcm_done_WID                           ( 1)
  #define DDRDATA3_CR_DLLDCMCTL_dcm_done_MSK                           (0x00000400)
  #define DDRDATA3_CR_DLLDCMCTL_dcm_done_MIN                           (0)
  #define DDRDATA3_CR_DLLDCMCTL_dcm_done_MAX                           (1) // 0x00000001
  #define DDRDATA3_CR_DLLDCMCTL_dcm_done_DEF                           (0x00000000)
  #define DDRDATA3_CR_DLLDCMCTL_dcm_done_HSH                           (0x010A21A4)

  #define DDRDATA3_CR_DLLDCMCTL_dcm_results_OFF                        (11)
  #define DDRDATA3_CR_DLLDCMCTL_dcm_results_WID                        (15)
  #define DDRDATA3_CR_DLLDCMCTL_dcm_results_MSK                        (0x03FFF800)
  #define DDRDATA3_CR_DLLDCMCTL_dcm_results_MIN                        (0)
  #define DDRDATA3_CR_DLLDCMCTL_dcm_results_MAX                        (32767) // 0x00007FFF
  #define DDRDATA3_CR_DLLDCMCTL_dcm_results_DEF                        (0x00000000)
  #define DDRDATA3_CR_DLLDCMCTL_dcm_results_HSH                        (0x0F0B21A4)

  #define DDRDATA3_CR_DLLDCMCTL_spare0_OFF                             (26)
  #define DDRDATA3_CR_DLLDCMCTL_spare0_WID                             ( 6)
  #define DDRDATA3_CR_DLLDCMCTL_spare0_MSK                             (0xFC000000)
  #define DDRDATA3_CR_DLLDCMCTL_spare0_MIN                             (0)
  #define DDRDATA3_CR_DLLDCMCTL_spare0_MAX                             (63) // 0x0000003F
  #define DDRDATA3_CR_DLLDCMCTL_spare0_DEF                             (0x00000000)
  #define DDRDATA3_CR_DLLDCMCTL_spare0_HSH                             (0x061A21A4)

#define DDRDATA4_CR_MASTERDLLCFG_REG                                   (0x00002200)

  #define DDRDATA4_CR_MASTERDLLCFG_LockThresh_OFF                      ( 0)
  #define DDRDATA4_CR_MASTERDLLCFG_LockThresh_WID                      ( 3)
  #define DDRDATA4_CR_MASTERDLLCFG_LockThresh_MSK                      (0x00000007)
  #define DDRDATA4_CR_MASTERDLLCFG_LockThresh_MIN                      (0)
  #define DDRDATA4_CR_MASTERDLLCFG_LockThresh_MAX                      (7) // 0x00000007
  #define DDRDATA4_CR_MASTERDLLCFG_LockThresh_DEF                      (0x00000004)
  #define DDRDATA4_CR_MASTERDLLCFG_LockThresh_HSH                      (0x03002200)

  #define DDRDATA4_CR_MASTERDLLCFG_LockCtr_OFF                         ( 3)
  #define DDRDATA4_CR_MASTERDLLCFG_LockCtr_WID                         ( 2)
  #define DDRDATA4_CR_MASTERDLLCFG_LockCtr_MSK                         (0x00000018)
  #define DDRDATA4_CR_MASTERDLLCFG_LockCtr_MIN                         (0)
  #define DDRDATA4_CR_MASTERDLLCFG_LockCtr_MAX                         (3) // 0x00000003
  #define DDRDATA4_CR_MASTERDLLCFG_LockCtr_DEF                         (0x00000000)
  #define DDRDATA4_CR_MASTERDLLCFG_LockCtr_HSH                         (0x02032200)

  #define DDRDATA4_CR_MASTERDLLCFG_VctrlDischRate_OFF                  ( 5)
  #define DDRDATA4_CR_MASTERDLLCFG_VctrlDischRate_WID                  ( 2)
  #define DDRDATA4_CR_MASTERDLLCFG_VctrlDischRate_MSK                  (0x00000060)
  #define DDRDATA4_CR_MASTERDLLCFG_VctrlDischRate_MIN                  (0)
  #define DDRDATA4_CR_MASTERDLLCFG_VctrlDischRate_MAX                  (3) // 0x00000003
  #define DDRDATA4_CR_MASTERDLLCFG_VctrlDischRate_DEF                  (0x00000000)
  #define DDRDATA4_CR_MASTERDLLCFG_VctrlDischRate_HSH                  (0x02052200)

  #define DDRDATA4_CR_MASTERDLLCFG_SelVctrlHi_OFF                      ( 7)
  #define DDRDATA4_CR_MASTERDLLCFG_SelVctrlHi_WID                      ( 1)
  #define DDRDATA4_CR_MASTERDLLCFG_SelVctrlHi_MSK                      (0x00000080)
  #define DDRDATA4_CR_MASTERDLLCFG_SelVctrlHi_MIN                      (0)
  #define DDRDATA4_CR_MASTERDLLCFG_SelVctrlHi_MAX                      (1) // 0x00000001
  #define DDRDATA4_CR_MASTERDLLCFG_SelVctrlHi_DEF                      (0x00000000)
  #define DDRDATA4_CR_MASTERDLLCFG_SelVctrlHi_HSH                      (0x01072200)

  #define DDRDATA4_CR_MASTERDLLCFG_StartupCntSel_OFF                   ( 8)
  #define DDRDATA4_CR_MASTERDLLCFG_StartupCntSel_WID                   ( 1)
  #define DDRDATA4_CR_MASTERDLLCFG_StartupCntSel_MSK                   (0x00000100)
  #define DDRDATA4_CR_MASTERDLLCFG_StartupCntSel_MIN                   (0)
  #define DDRDATA4_CR_MASTERDLLCFG_StartupCntSel_MAX                   (1) // 0x00000001
  #define DDRDATA4_CR_MASTERDLLCFG_StartupCntSel_DEF                   (0x00000000)
  #define DDRDATA4_CR_MASTERDLLCFG_StartupCntSel_HSH                   (0x01082200)

  #define DDRDATA4_CR_MASTERDLLCFG_LockSel_OFF                         ( 9)
  #define DDRDATA4_CR_MASTERDLLCFG_LockSel_WID                         ( 2)
  #define DDRDATA4_CR_MASTERDLLCFG_LockSel_MSK                         (0x00000600)
  #define DDRDATA4_CR_MASTERDLLCFG_LockSel_MIN                         (0)
  #define DDRDATA4_CR_MASTERDLLCFG_LockSel_MAX                         (3) // 0x00000003
  #define DDRDATA4_CR_MASTERDLLCFG_LockSel_DEF                         (0x00000000)
  #define DDRDATA4_CR_MASTERDLLCFG_LockSel_HSH                         (0x02092200)

  #define DDRDATA4_CR_MASTERDLLCFG_RstOvrd_OFF                         (11)
  #define DDRDATA4_CR_MASTERDLLCFG_RstOvrd_WID                         ( 1)
  #define DDRDATA4_CR_MASTERDLLCFG_RstOvrd_MSK                         (0x00000800)
  #define DDRDATA4_CR_MASTERDLLCFG_RstOvrd_MIN                         (0)
  #define DDRDATA4_CR_MASTERDLLCFG_RstOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA4_CR_MASTERDLLCFG_RstOvrd_DEF                         (0x00000000)
  #define DDRDATA4_CR_MASTERDLLCFG_RstOvrd_HSH                         (0x010B2200)

  #define DDRDATA4_CR_MASTERDLLCFG_SelRstOvrd_OFF                      (12)
  #define DDRDATA4_CR_MASTERDLLCFG_SelRstOvrd_WID                      ( 1)
  #define DDRDATA4_CR_MASTERDLLCFG_SelRstOvrd_MSK                      (0x00001000)
  #define DDRDATA4_CR_MASTERDLLCFG_SelRstOvrd_MIN                      (0)
  #define DDRDATA4_CR_MASTERDLLCFG_SelRstOvrd_MAX                      (1) // 0x00000001
  #define DDRDATA4_CR_MASTERDLLCFG_SelRstOvrd_DEF                      (0x00000000)
  #define DDRDATA4_CR_MASTERDLLCFG_SelRstOvrd_HSH                      (0x010C2200)

  #define DDRDATA4_CR_MASTERDLLCFG_TimeOutOvrd_OFF                     (13)
  #define DDRDATA4_CR_MASTERDLLCFG_TimeOutOvrd_WID                     ( 1)
  #define DDRDATA4_CR_MASTERDLLCFG_TimeOutOvrd_MSK                     (0x00002000)
  #define DDRDATA4_CR_MASTERDLLCFG_TimeOutOvrd_MIN                     (0)
  #define DDRDATA4_CR_MASTERDLLCFG_TimeOutOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA4_CR_MASTERDLLCFG_TimeOutOvrd_DEF                     (0x00000000)
  #define DDRDATA4_CR_MASTERDLLCFG_TimeOutOvrd_HSH                     (0x010D2200)

  #define DDRDATA4_CR_MASTERDLLCFG_SelTimeOutOvrd_OFF                  (14)
  #define DDRDATA4_CR_MASTERDLLCFG_SelTimeOutOvrd_WID                  ( 1)
  #define DDRDATA4_CR_MASTERDLLCFG_SelTimeOutOvrd_MSK                  (0x00004000)
  #define DDRDATA4_CR_MASTERDLLCFG_SelTimeOutOvrd_MIN                  (0)
  #define DDRDATA4_CR_MASTERDLLCFG_SelTimeOutOvrd_MAX                  (1) // 0x00000001
  #define DDRDATA4_CR_MASTERDLLCFG_SelTimeOutOvrd_DEF                  (0x00000000)
  #define DDRDATA4_CR_MASTERDLLCFG_SelTimeOutOvrd_HSH                  (0x010E2200)

  #define DDRDATA4_CR_MASTERDLLCFG_ClkGateOvrd_OFF                     (15)
  #define DDRDATA4_CR_MASTERDLLCFG_ClkGateOvrd_WID                     ( 1)
  #define DDRDATA4_CR_MASTERDLLCFG_ClkGateOvrd_MSK                     (0x00008000)
  #define DDRDATA4_CR_MASTERDLLCFG_ClkGateOvrd_MIN                     (0)
  #define DDRDATA4_CR_MASTERDLLCFG_ClkGateOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA4_CR_MASTERDLLCFG_ClkGateOvrd_DEF                     (0x00000000)
  #define DDRDATA4_CR_MASTERDLLCFG_ClkGateOvrd_HSH                     (0x010F2200)

  #define DDRDATA4_CR_MASTERDLLCFG_LockOvrd_OFF                        (16)
  #define DDRDATA4_CR_MASTERDLLCFG_LockOvrd_WID                        ( 1)
  #define DDRDATA4_CR_MASTERDLLCFG_LockOvrd_MSK                        (0x00010000)
  #define DDRDATA4_CR_MASTERDLLCFG_LockOvrd_MIN                        (0)
  #define DDRDATA4_CR_MASTERDLLCFG_LockOvrd_MAX                        (1) // 0x00000001
  #define DDRDATA4_CR_MASTERDLLCFG_LockOvrd_DEF                        (0x00000000)
  #define DDRDATA4_CR_MASTERDLLCFG_LockOvrd_HSH                        (0x01102200)

  #define DDRDATA4_CR_MASTERDLLCFG_SelLockOvrd_OFF                     (17)
  #define DDRDATA4_CR_MASTERDLLCFG_SelLockOvrd_WID                     ( 1)
  #define DDRDATA4_CR_MASTERDLLCFG_SelLockOvrd_MSK                     (0x00020000)
  #define DDRDATA4_CR_MASTERDLLCFG_SelLockOvrd_MIN                     (0)
  #define DDRDATA4_CR_MASTERDLLCFG_SelLockOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA4_CR_MASTERDLLCFG_SelLockOvrd_DEF                     (0x00000000)
  #define DDRDATA4_CR_MASTERDLLCFG_SelLockOvrd_HSH                     (0x01112200)

  #define DDRDATA4_CR_MASTERDLLCFG_OpenLoopOvrd_OFF                    (18)
  #define DDRDATA4_CR_MASTERDLLCFG_OpenLoopOvrd_WID                    ( 1)
  #define DDRDATA4_CR_MASTERDLLCFG_OpenLoopOvrd_MSK                    (0x00040000)
  #define DDRDATA4_CR_MASTERDLLCFG_OpenLoopOvrd_MIN                    (0)
  #define DDRDATA4_CR_MASTERDLLCFG_OpenLoopOvrd_MAX                    (1) // 0x00000001
  #define DDRDATA4_CR_MASTERDLLCFG_OpenLoopOvrd_DEF                    (0x00000000)
  #define DDRDATA4_CR_MASTERDLLCFG_OpenLoopOvrd_HSH                    (0x01122200)

  #define DDRDATA4_CR_MASTERDLLCFG_SelOpenLoopOvrd_OFF                 (19)
  #define DDRDATA4_CR_MASTERDLLCFG_SelOpenLoopOvrd_WID                 ( 1)
  #define DDRDATA4_CR_MASTERDLLCFG_SelOpenLoopOvrd_MSK                 (0x00080000)
  #define DDRDATA4_CR_MASTERDLLCFG_SelOpenLoopOvrd_MIN                 (0)
  #define DDRDATA4_CR_MASTERDLLCFG_SelOpenLoopOvrd_MAX                 (1) // 0x00000001
  #define DDRDATA4_CR_MASTERDLLCFG_SelOpenLoopOvrd_DEF                 (0x00000000)
  #define DDRDATA4_CR_MASTERDLLCFG_SelOpenLoopOvrd_HSH                 (0x01132200)

  #define DDRDATA4_CR_MASTERDLLCFG_WkLockEnOvrd_OFF                    (20)
  #define DDRDATA4_CR_MASTERDLLCFG_WkLockEnOvrd_WID                    ( 1)
  #define DDRDATA4_CR_MASTERDLLCFG_WkLockEnOvrd_MSK                    (0x00100000)
  #define DDRDATA4_CR_MASTERDLLCFG_WkLockEnOvrd_MIN                    (0)
  #define DDRDATA4_CR_MASTERDLLCFG_WkLockEnOvrd_MAX                    (1) // 0x00000001
  #define DDRDATA4_CR_MASTERDLLCFG_WkLockEnOvrd_DEF                    (0x00000000)
  #define DDRDATA4_CR_MASTERDLLCFG_WkLockEnOvrd_HSH                    (0x01142200)

  #define DDRDATA4_CR_MASTERDLLCFG_SelWkLockEnOvrd_OFF                 (21)
  #define DDRDATA4_CR_MASTERDLLCFG_SelWkLockEnOvrd_WID                 ( 1)
  #define DDRDATA4_CR_MASTERDLLCFG_SelWkLockEnOvrd_MSK                 (0x00200000)
  #define DDRDATA4_CR_MASTERDLLCFG_SelWkLockEnOvrd_MIN                 (0)
  #define DDRDATA4_CR_MASTERDLLCFG_SelWkLockEnOvrd_MAX                 (1) // 0x00000001
  #define DDRDATA4_CR_MASTERDLLCFG_SelWkLockEnOvrd_DEF                 (0x00000000)
  #define DDRDATA4_CR_MASTERDLLCFG_SelWkLockEnOvrd_HSH                 (0x01152200)

  #define DDRDATA4_CR_MASTERDLLCFG_CfdlDis_OFF                         (22)
  #define DDRDATA4_CR_MASTERDLLCFG_CfdlDis_WID                         ( 1)
  #define DDRDATA4_CR_MASTERDLLCFG_CfdlDis_MSK                         (0x00400000)
  #define DDRDATA4_CR_MASTERDLLCFG_CfdlDis_MIN                         (0)
  #define DDRDATA4_CR_MASTERDLLCFG_CfdlDis_MAX                         (1) // 0x00000001
  #define DDRDATA4_CR_MASTERDLLCFG_CfdlDis_DEF                         (0x00000000)
  #define DDRDATA4_CR_MASTERDLLCFG_CfdlDis_HSH                         (0x01162200)

  #define DDRDATA4_CR_MASTERDLLCFG_DftEn_OFF                           (23)
  #define DDRDATA4_CR_MASTERDLLCFG_DftEn_WID                           ( 1)
  #define DDRDATA4_CR_MASTERDLLCFG_DftEn_MSK                           (0x00800000)
  #define DDRDATA4_CR_MASTERDLLCFG_DftEn_MIN                           (0)
  #define DDRDATA4_CR_MASTERDLLCFG_DftEn_MAX                           (1) // 0x00000001
  #define DDRDATA4_CR_MASTERDLLCFG_DftEn_DEF                           (0x00000000)
  #define DDRDATA4_CR_MASTERDLLCFG_DftEn_HSH                           (0x01172200)

  #define DDRDATA4_CR_MASTERDLLCFG_spare0_OFF                          (24)
  #define DDRDATA4_CR_MASTERDLLCFG_spare0_WID                          ( 8)
  #define DDRDATA4_CR_MASTERDLLCFG_spare0_MSK                          (0xFF000000)
  #define DDRDATA4_CR_MASTERDLLCFG_spare0_MIN                          (0)
  #define DDRDATA4_CR_MASTERDLLCFG_spare0_MAX                          (255) // 0x000000FF
  #define DDRDATA4_CR_MASTERDLLCFG_spare0_DEF                          (0x00000000)
  #define DDRDATA4_CR_MASTERDLLCFG_spare0_HSH                          (0x08182200)

#define DDRDATA4_CR_CBTUNE0_REG                                        (0x00002204)

  #define DDRDATA4_CR_CBTUNE0_DllBWEn_OFF                              ( 0)
  #define DDRDATA4_CR_CBTUNE0_DllBWEn_WID                              (32)
  #define DDRDATA4_CR_CBTUNE0_DllBWEn_MSK                              (0xFFFFFFFF)
  #define DDRDATA4_CR_CBTUNE0_DllBWEn_MIN                              (0)
  #define DDRDATA4_CR_CBTUNE0_DllBWEn_MAX                              (4294967295) // 0xFFFFFFFF
  #define DDRDATA4_CR_CBTUNE0_DllBWEn_DEF                              (0xFDB86521)
  #define DDRDATA4_CR_CBTUNE0_DllBWEn_HSH                              (0x20002204)

#define DDRDATA4_CR_CBTUNE1_REG                                        (0x00002208)

  #define DDRDATA4_CR_CBTUNE1_PiCbEn_OFF                               ( 0)
  #define DDRDATA4_CR_CBTUNE1_PiCbEn_WID                               (24)
  #define DDRDATA4_CR_CBTUNE1_PiCbEn_MSK                               (0x00FFFFFF)
  #define DDRDATA4_CR_CBTUNE1_PiCbEn_MIN                               (0)
  #define DDRDATA4_CR_CBTUNE1_PiCbEn_MAX                               (16777215) // 0x00FFFFFF
  #define DDRDATA4_CR_CBTUNE1_PiCbEn_DEF                               (0x00249492)
  #define DDRDATA4_CR_CBTUNE1_PiCbEn_HSH                               (0x18002208)

  #define DDRDATA4_CR_CBTUNE1_CbEnRsvd_OFF                             (24)
  #define DDRDATA4_CR_CBTUNE1_CbEnRsvd_WID                             ( 3)
  #define DDRDATA4_CR_CBTUNE1_CbEnRsvd_MSK                             (0x07000000)
  #define DDRDATA4_CR_CBTUNE1_CbEnRsvd_MIN                             (0)
  #define DDRDATA4_CR_CBTUNE1_CbEnRsvd_MAX                             (7) // 0x00000007
  #define DDRDATA4_CR_CBTUNE1_CbEnRsvd_DEF                             (0x00000000)
  #define DDRDATA4_CR_CBTUNE1_CbEnRsvd_HSH                             (0x03182208)

  #define DDRDATA4_CR_CBTUNE1_CbEnDllFuse_OFF                          (27)
  #define DDRDATA4_CR_CBTUNE1_CbEnDllFuse_WID                          ( 3)
  #define DDRDATA4_CR_CBTUNE1_CbEnDllFuse_MSK                          (0x38000000)
  #define DDRDATA4_CR_CBTUNE1_CbEnDllFuse_MIN                          (0)
  #define DDRDATA4_CR_CBTUNE1_CbEnDllFuse_MAX                          (7) // 0x00000007
  #define DDRDATA4_CR_CBTUNE1_CbEnDllFuse_DEF                          (0x00000002)
  #define DDRDATA4_CR_CBTUNE1_CbEnDllFuse_HSH                          (0x031B2208)

  #define DDRDATA4_CR_CBTUNE1_Spare_OFF                                (30)
  #define DDRDATA4_CR_CBTUNE1_Spare_WID                                ( 2)
  #define DDRDATA4_CR_CBTUNE1_Spare_MSK                                (0xC0000000)
  #define DDRDATA4_CR_CBTUNE1_Spare_MIN                                (0)
  #define DDRDATA4_CR_CBTUNE1_Spare_MAX                                (3) // 0x00000003
  #define DDRDATA4_CR_CBTUNE1_Spare_DEF                                (0x00000000)
  #define DDRDATA4_CR_CBTUNE1_Spare_HSH                                (0x021E2208)

#define DDRDATA4_CR_ADCCFG_REG                                         (0x0000220C)

  #define DDRDATA4_CR_ADCCFG_ADC_frz_OFF                               ( 0)
  #define DDRDATA4_CR_ADCCFG_ADC_frz_WID                               ( 1)
  #define DDRDATA4_CR_ADCCFG_ADC_frz_MSK                               (0x00000001)
  #define DDRDATA4_CR_ADCCFG_ADC_frz_MIN                               (0)
  #define DDRDATA4_CR_ADCCFG_ADC_frz_MAX                               (1) // 0x00000001
  #define DDRDATA4_CR_ADCCFG_ADC_frz_DEF                               (0x00000000)
  #define DDRDATA4_CR_ADCCFG_ADC_frz_HSH                               (0x0100220C)

  #define DDRDATA4_CR_ADCCFG_ADC_en_OFF                                ( 1)
  #define DDRDATA4_CR_ADCCFG_ADC_en_WID                                ( 1)
  #define DDRDATA4_CR_ADCCFG_ADC_en_MSK                                (0x00000002)
  #define DDRDATA4_CR_ADCCFG_ADC_en_MIN                                (0)
  #define DDRDATA4_CR_ADCCFG_ADC_en_MAX                                (1) // 0x00000001
  #define DDRDATA4_CR_ADCCFG_ADC_en_DEF                                (0x00000000)
  #define DDRDATA4_CR_ADCCFG_ADC_en_HSH                                (0x0101220C)

  #define DDRDATA4_CR_ADCCFG_ADCclkdiv_OFF                             ( 2)
  #define DDRDATA4_CR_ADCCFG_ADCclkdiv_WID                             ( 2)
  #define DDRDATA4_CR_ADCCFG_ADCclkdiv_MSK                             (0x0000000C)
  #define DDRDATA4_CR_ADCCFG_ADCclkdiv_MIN                             (0)
  #define DDRDATA4_CR_ADCCFG_ADCclkdiv_MAX                             (3) // 0x00000003
  #define DDRDATA4_CR_ADCCFG_ADCclkdiv_DEF                             (0x00000000)
  #define DDRDATA4_CR_ADCCFG_ADCclkdiv_HSH                             (0x0202220C)

  #define DDRDATA4_CR_ADCCFG_ADCstartcount_OFF                         ( 4)
  #define DDRDATA4_CR_ADCCFG_ADCstartcount_WID                         ( 2)
  #define DDRDATA4_CR_ADCCFG_ADCstartcount_MSK                         (0x00000030)
  #define DDRDATA4_CR_ADCCFG_ADCstartcount_MIN                         (0)
  #define DDRDATA4_CR_ADCCFG_ADCstartcount_MAX                         (3) // 0x00000003
  #define DDRDATA4_CR_ADCCFG_ADCstartcount_DEF                         (0x00000000)
  #define DDRDATA4_CR_ADCCFG_ADCstartcount_HSH                         (0x0204220C)

  #define DDRDATA4_CR_ADCCFG_ADCChopEn_OFF                             ( 6)
  #define DDRDATA4_CR_ADCCFG_ADCChopEn_WID                             ( 1)
  #define DDRDATA4_CR_ADCCFG_ADCChopEn_MSK                             (0x00000040)
  #define DDRDATA4_CR_ADCCFG_ADCChopEn_MIN                             (0)
  #define DDRDATA4_CR_ADCCFG_ADCChopEn_MAX                             (1) // 0x00000001
  #define DDRDATA4_CR_ADCCFG_ADCChopEn_DEF                             (0x00000000)
  #define DDRDATA4_CR_ADCCFG_ADCChopEn_HSH                             (0x0106220C)

  #define DDRDATA4_CR_ADCCFG_Spare_OFF                                 ( 7)
  #define DDRDATA4_CR_ADCCFG_Spare_WID                                 (25)
  #define DDRDATA4_CR_ADCCFG_Spare_MSK                                 (0xFFFFFF80)
  #define DDRDATA4_CR_ADCCFG_Spare_MIN                                 (0)
  #define DDRDATA4_CR_ADCCFG_Spare_MAX                                 (33554431) // 0x01FFFFFF
  #define DDRDATA4_CR_ADCCFG_Spare_DEF                                 (0x00000000)
  #define DDRDATA4_CR_ADCCFG_Spare_HSH                                 (0x1907220C)

#define DDRDATA4_CR_CBTUNE2_REG                                        (0x00002210)

  #define DDRDATA4_CR_CBTUNE2_DllCbEn_OFF                              ( 0)
  #define DDRDATA4_CR_CBTUNE2_DllCbEn_WID                              (16)
  #define DDRDATA4_CR_CBTUNE2_DllCbEn_MSK                              (0x0000FFFF)
  #define DDRDATA4_CR_CBTUNE2_DllCbEn_MIN                              (0)
  #define DDRDATA4_CR_CBTUNE2_DllCbEn_MAX                              (65535) // 0x0000FFFF
  #define DDRDATA4_CR_CBTUNE2_DllCbEn_DEF                              (0x00000000)
  #define DDRDATA4_CR_CBTUNE2_DllCbEn_HSH                              (0x10002210)

  #define DDRDATA4_CR_CBTUNE2_Spare_OFF                                (16)
  #define DDRDATA4_CR_CBTUNE2_Spare_WID                                (16)
  #define DDRDATA4_CR_CBTUNE2_Spare_MSK                                (0xFFFF0000)
  #define DDRDATA4_CR_CBTUNE2_Spare_MIN                                (0)
  #define DDRDATA4_CR_CBTUNE2_Spare_MAX                                (65535) // 0x0000FFFF
  #define DDRDATA4_CR_CBTUNE2_Spare_DEF                                (0x00000000)
  #define DDRDATA4_CR_CBTUNE2_Spare_HSH                                (0x10102210)

#define DDRDATA4_CR_PIDFTDLY_REG                                       (0x00002218)

  #define DDRDATA4_CR_PIDFTDLY_PiDftDelay_OFF                          ( 0)
  #define DDRDATA4_CR_PIDFTDLY_PiDftDelay_WID                          ( 7)
  #define DDRDATA4_CR_PIDFTDLY_PiDftDelay_MSK                          (0x0000007F)
  #define DDRDATA4_CR_PIDFTDLY_PiDftDelay_MIN                          (0)
  #define DDRDATA4_CR_PIDFTDLY_PiDftDelay_MAX                          (127) // 0x0000007F
  #define DDRDATA4_CR_PIDFTDLY_PiDftDelay_DEF                          (0x00000000)
  #define DDRDATA4_CR_PIDFTDLY_PiDftDelay_HSH                          (0x07002218)

  #define DDRDATA4_CR_PIDFTDLY_Ch0PiEnOvrd_OFF                         ( 7)
  #define DDRDATA4_CR_PIDFTDLY_Ch0PiEnOvrd_WID                         ( 1)
  #define DDRDATA4_CR_PIDFTDLY_Ch0PiEnOvrd_MSK                         (0x00000080)
  #define DDRDATA4_CR_PIDFTDLY_Ch0PiEnOvrd_MIN                         (0)
  #define DDRDATA4_CR_PIDFTDLY_Ch0PiEnOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA4_CR_PIDFTDLY_Ch0PiEnOvrd_DEF                         (0x00000000)
  #define DDRDATA4_CR_PIDFTDLY_Ch0PiEnOvrd_HSH                         (0x01072218)

  #define DDRDATA4_CR_PIDFTDLY_Ch1PiEnOvrd_OFF                         ( 8)
  #define DDRDATA4_CR_PIDFTDLY_Ch1PiEnOvrd_WID                         ( 1)
  #define DDRDATA4_CR_PIDFTDLY_Ch1PiEnOvrd_MSK                         (0x00000100)
  #define DDRDATA4_CR_PIDFTDLY_Ch1PiEnOvrd_MIN                         (0)
  #define DDRDATA4_CR_PIDFTDLY_Ch1PiEnOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA4_CR_PIDFTDLY_Ch1PiEnOvrd_DEF                         (0x00000000)
  #define DDRDATA4_CR_PIDFTDLY_Ch1PiEnOvrd_HSH                         (0x01082218)

  #define DDRDATA4_CR_PIDFTDLY_Ch0PiDFTEn_OFF                          ( 9)
  #define DDRDATA4_CR_PIDFTDLY_Ch0PiDFTEn_WID                          ( 1)
  #define DDRDATA4_CR_PIDFTDLY_Ch0PiDFTEn_MSK                          (0x00000200)
  #define DDRDATA4_CR_PIDFTDLY_Ch0PiDFTEn_MIN                          (0)
  #define DDRDATA4_CR_PIDFTDLY_Ch0PiDFTEn_MAX                          (1) // 0x00000001
  #define DDRDATA4_CR_PIDFTDLY_Ch0PiDFTEn_DEF                          (0x00000000)
  #define DDRDATA4_CR_PIDFTDLY_Ch0PiDFTEn_HSH                          (0x01092218)

  #define DDRDATA4_CR_PIDFTDLY_Ch1PiDFTEn_OFF                          (10)
  #define DDRDATA4_CR_PIDFTDLY_Ch1PiDFTEn_WID                          ( 1)
  #define DDRDATA4_CR_PIDFTDLY_Ch1PiDFTEn_MSK                          (0x00000400)
  #define DDRDATA4_CR_PIDFTDLY_Ch1PiDFTEn_MIN                          (0)
  #define DDRDATA4_CR_PIDFTDLY_Ch1PiDFTEn_MAX                          (1) // 0x00000001
  #define DDRDATA4_CR_PIDFTDLY_Ch1PiDFTEn_DEF                          (0x00000000)
  #define DDRDATA4_CR_PIDFTDLY_Ch1PiDFTEn_HSH                          (0x010A2218)

  #define DDRDATA4_CR_PIDFTDLY_Spare_OFF                               (11)
  #define DDRDATA4_CR_PIDFTDLY_Spare_WID                               ( 4)
  #define DDRDATA4_CR_PIDFTDLY_Spare_MSK                               (0x00007800)
  #define DDRDATA4_CR_PIDFTDLY_Spare_MIN                               (0)
  #define DDRDATA4_CR_PIDFTDLY_Spare_MAX                               (15) // 0x0000000F
  #define DDRDATA4_CR_PIDFTDLY_Spare_DEF                               (0x00000000)
  #define DDRDATA4_CR_PIDFTDLY_Spare_HSH                               (0x040B2218)

  #define DDRDATA4_CR_PIDFTDLY_RefPiOvrd_OFF                           (15)
  #define DDRDATA4_CR_PIDFTDLY_RefPiOvrd_WID                           ( 1)
  #define DDRDATA4_CR_PIDFTDLY_RefPiOvrd_MSK                           (0x00008000)
  #define DDRDATA4_CR_PIDFTDLY_RefPiOvrd_MIN                           (0)
  #define DDRDATA4_CR_PIDFTDLY_RefPiOvrd_MAX                           (1) // 0x00000001
  #define DDRDATA4_CR_PIDFTDLY_RefPiOvrd_DEF                           (0x00000000)
  #define DDRDATA4_CR_PIDFTDLY_RefPiOvrd_HSH                           (0x010F2218)

  #define DDRDATA4_CR_PIDFTDLY_Rsvd_OFF                                (16)
  #define DDRDATA4_CR_PIDFTDLY_Rsvd_WID                                (16)
  #define DDRDATA4_CR_PIDFTDLY_Rsvd_MSK                                (0xFFFF0000)
  #define DDRDATA4_CR_PIDFTDLY_Rsvd_MIN                                (0)
  #define DDRDATA4_CR_PIDFTDLY_Rsvd_MAX                                (65535) // 0x0000FFFF
  #define DDRDATA4_CR_PIDFTDLY_Rsvd_DEF                                (0x00000000)
  #define DDRDATA4_CR_PIDFTDLY_Rsvd_HSH                                (0x10102218)

#define DDRDATA4_CR_DLLPITESTANDADC_REG                                (0x0000221C)

  #define DDRDATA4_CR_DLLPITESTANDADC_RunTest_OFF                      ( 0)
  #define DDRDATA4_CR_DLLPITESTANDADC_RunTest_WID                      ( 1)
  #define DDRDATA4_CR_DLLPITESTANDADC_RunTest_MSK                      (0x00000001)
  #define DDRDATA4_CR_DLLPITESTANDADC_RunTest_MIN                      (0)
  #define DDRDATA4_CR_DLLPITESTANDADC_RunTest_MAX                      (1) // 0x00000001
  #define DDRDATA4_CR_DLLPITESTANDADC_RunTest_DEF                      (0x00000000)
  #define DDRDATA4_CR_DLLPITESTANDADC_RunTest_HSH                      (0x0100221C)

  #define DDRDATA4_CR_DLLPITESTANDADC_Load_OFF                         ( 1)
  #define DDRDATA4_CR_DLLPITESTANDADC_Load_WID                         ( 1)
  #define DDRDATA4_CR_DLLPITESTANDADC_Load_MSK                         (0x00000002)
  #define DDRDATA4_CR_DLLPITESTANDADC_Load_MIN                         (0)
  #define DDRDATA4_CR_DLLPITESTANDADC_Load_MAX                         (1) // 0x00000001
  #define DDRDATA4_CR_DLLPITESTANDADC_Load_DEF                         (0x00000000)
  #define DDRDATA4_CR_DLLPITESTANDADC_Load_HSH                         (0x0101221C)

  #define DDRDATA4_CR_DLLPITESTANDADC_ModeHVM_OFF                      ( 2)
  #define DDRDATA4_CR_DLLPITESTANDADC_ModeHVM_WID                      ( 1)
  #define DDRDATA4_CR_DLLPITESTANDADC_ModeHVM_MSK                      (0x00000004)
  #define DDRDATA4_CR_DLLPITESTANDADC_ModeHVM_MIN                      (0)
  #define DDRDATA4_CR_DLLPITESTANDADC_ModeHVM_MAX                      (1) // 0x00000001
  #define DDRDATA4_CR_DLLPITESTANDADC_ModeHVM_DEF                      (0x00000000)
  #define DDRDATA4_CR_DLLPITESTANDADC_ModeHVM_HSH                      (0x0102221C)

  #define DDRDATA4_CR_DLLPITESTANDADC_ModeDV_OFF                       ( 3)
  #define DDRDATA4_CR_DLLPITESTANDADC_ModeDV_WID                       ( 1)
  #define DDRDATA4_CR_DLLPITESTANDADC_ModeDV_MSK                       (0x00000008)
  #define DDRDATA4_CR_DLLPITESTANDADC_ModeDV_MIN                       (0)
  #define DDRDATA4_CR_DLLPITESTANDADC_ModeDV_MAX                       (1) // 0x00000001
  #define DDRDATA4_CR_DLLPITESTANDADC_ModeDV_DEF                       (0x00000000)
  #define DDRDATA4_CR_DLLPITESTANDADC_ModeDV_HSH                       (0x0103221C)

  #define DDRDATA4_CR_DLLPITESTANDADC_CalCfdl_OFF                      ( 4)
  #define DDRDATA4_CR_DLLPITESTANDADC_CalCfdl_WID                      ( 1)
  #define DDRDATA4_CR_DLLPITESTANDADC_CalCfdl_MSK                      (0x00000010)
  #define DDRDATA4_CR_DLLPITESTANDADC_CalCfdl_MIN                      (0)
  #define DDRDATA4_CR_DLLPITESTANDADC_CalCfdl_MAX                      (1) // 0x00000001
  #define DDRDATA4_CR_DLLPITESTANDADC_CalCfdl_DEF                      (0x00000000)
  #define DDRDATA4_CR_DLLPITESTANDADC_CalCfdl_HSH                      (0x0104221C)

  #define DDRDATA4_CR_DLLPITESTANDADC_LoadCount_OFF                    ( 5)
  #define DDRDATA4_CR_DLLPITESTANDADC_LoadCount_WID                    (10)
  #define DDRDATA4_CR_DLLPITESTANDADC_LoadCount_MSK                    (0x00007FE0)
  #define DDRDATA4_CR_DLLPITESTANDADC_LoadCount_MIN                    (0)
  #define DDRDATA4_CR_DLLPITESTANDADC_LoadCount_MAX                    (1023) // 0x000003FF
  #define DDRDATA4_CR_DLLPITESTANDADC_LoadCount_DEF                    (0x00000000)
  #define DDRDATA4_CR_DLLPITESTANDADC_LoadCount_HSH                    (0x0A05221C)

  #define DDRDATA4_CR_DLLPITESTANDADC_CountStatus_OFF                  (15)
  #define DDRDATA4_CR_DLLPITESTANDADC_CountStatus_WID                  (10)
  #define DDRDATA4_CR_DLLPITESTANDADC_CountStatus_MSK                  (0x01FF8000)
  #define DDRDATA4_CR_DLLPITESTANDADC_CountStatus_MIN                  (0)
  #define DDRDATA4_CR_DLLPITESTANDADC_CountStatus_MAX                  (1023) // 0x000003FF
  #define DDRDATA4_CR_DLLPITESTANDADC_CountStatus_DEF                  (0x00000000)
  #define DDRDATA4_CR_DLLPITESTANDADC_CountStatus_HSH                  (0x0A0F221C)

  #define DDRDATA4_CR_DLLPITESTANDADC_ModeADC_OFF                      (25)
  #define DDRDATA4_CR_DLLPITESTANDADC_ModeADC_WID                      ( 1)
  #define DDRDATA4_CR_DLLPITESTANDADC_ModeADC_MSK                      (0x02000000)
  #define DDRDATA4_CR_DLLPITESTANDADC_ModeADC_MIN                      (0)
  #define DDRDATA4_CR_DLLPITESTANDADC_ModeADC_MAX                      (1) // 0x00000001
  #define DDRDATA4_CR_DLLPITESTANDADC_ModeADC_DEF                      (0x00000000)
  #define DDRDATA4_CR_DLLPITESTANDADC_ModeADC_HSH                      (0x0119221C)

  #define DDRDATA4_CR_DLLPITESTANDADC_ADCClkDiv_OFF                    (26)
  #define DDRDATA4_CR_DLLPITESTANDADC_ADCClkDiv_WID                    ( 2)
  #define DDRDATA4_CR_DLLPITESTANDADC_ADCClkDiv_MSK                    (0x0C000000)
  #define DDRDATA4_CR_DLLPITESTANDADC_ADCClkDiv_MIN                    (0)
  #define DDRDATA4_CR_DLLPITESTANDADC_ADCClkDiv_MAX                    (3) // 0x00000003
  #define DDRDATA4_CR_DLLPITESTANDADC_ADCClkDiv_DEF                    (0x00000000)
  #define DDRDATA4_CR_DLLPITESTANDADC_ADCClkDiv_HSH                    (0x021A221C)

  #define DDRDATA4_CR_DLLPITESTANDADC_ADCDdrChanSel_OFF                (28)
  #define DDRDATA4_CR_DLLPITESTANDADC_ADCDdrChanSel_WID                ( 1)
  #define DDRDATA4_CR_DLLPITESTANDADC_ADCDdrChanSel_MSK                (0x10000000)
  #define DDRDATA4_CR_DLLPITESTANDADC_ADCDdrChanSel_MIN                (0)
  #define DDRDATA4_CR_DLLPITESTANDADC_ADCDdrChanSel_MAX                (1) // 0x00000001
  #define DDRDATA4_CR_DLLPITESTANDADC_ADCDdrChanSel_DEF                (0x00000000)
  #define DDRDATA4_CR_DLLPITESTANDADC_ADCDdrChanSel_HSH                (0x011C221C)

  #define DDRDATA4_CR_DLLPITESTANDADC_ADCChopEn_OFF                    (29)
  #define DDRDATA4_CR_DLLPITESTANDADC_ADCChopEn_WID                    ( 1)
  #define DDRDATA4_CR_DLLPITESTANDADC_ADCChopEn_MSK                    (0x20000000)
  #define DDRDATA4_CR_DLLPITESTANDADC_ADCChopEn_MIN                    (0)
  #define DDRDATA4_CR_DLLPITESTANDADC_ADCChopEn_MAX                    (1) // 0x00000001
  #define DDRDATA4_CR_DLLPITESTANDADC_ADCChopEn_DEF                    (0x00000000)
  #define DDRDATA4_CR_DLLPITESTANDADC_ADCChopEn_HSH                    (0x011D221C)

  #define DDRDATA4_CR_DLLPITESTANDADC_ADCDone_OFF                      (30)
  #define DDRDATA4_CR_DLLPITESTANDADC_ADCDone_WID                      ( 1)
  #define DDRDATA4_CR_DLLPITESTANDADC_ADCDone_MSK                      (0x40000000)
  #define DDRDATA4_CR_DLLPITESTANDADC_ADCDone_MIN                      (0)
  #define DDRDATA4_CR_DLLPITESTANDADC_ADCDone_MAX                      (1) // 0x00000001
  #define DDRDATA4_CR_DLLPITESTANDADC_ADCDone_DEF                      (0x00000000)
  #define DDRDATA4_CR_DLLPITESTANDADC_ADCDone_HSH                      (0x011E221C)

  #define DDRDATA4_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF             (31)
  #define DDRDATA4_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID             ( 1)
  #define DDRDATA4_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK             (0x80000000)
  #define DDRDATA4_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN             (0)
  #define DDRDATA4_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX             (1) // 0x00000001
  #define DDRDATA4_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF             (0x00000000)
  #define DDRDATA4_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH             (0x011F221C)

#define DDRDATA4_CR_DLLSTATUS_REG                                      (0x00002220)

  #define DDRDATA4_CR_DLLSTATUS_DetrmLockStat_OFF                      ( 0)
  #define DDRDATA4_CR_DLLSTATUS_DetrmLockStat_WID                      ( 1)
  #define DDRDATA4_CR_DLLSTATUS_DetrmLockStat_MSK                      (0x00000001)
  #define DDRDATA4_CR_DLLSTATUS_DetrmLockStat_MIN                      (0)
  #define DDRDATA4_CR_DLLSTATUS_DetrmLockStat_MAX                      (1) // 0x00000001
  #define DDRDATA4_CR_DLLSTATUS_DetrmLockStat_DEF                      (0x00000000)
  #define DDRDATA4_CR_DLLSTATUS_DetrmLockStat_HSH                      (0x01002220)

  #define DDRDATA4_CR_DLLSTATUS_FuncLockStat_OFF                       ( 1)
  #define DDRDATA4_CR_DLLSTATUS_FuncLockStat_WID                       ( 1)
  #define DDRDATA4_CR_DLLSTATUS_FuncLockStat_MSK                       (0x00000002)
  #define DDRDATA4_CR_DLLSTATUS_FuncLockStat_MIN                       (0)
  #define DDRDATA4_CR_DLLSTATUS_FuncLockStat_MAX                       (1) // 0x00000001
  #define DDRDATA4_CR_DLLSTATUS_FuncLockStat_DEF                       (0x00000000)
  #define DDRDATA4_CR_DLLSTATUS_FuncLockStat_HSH                       (0x01012220)

  #define DDRDATA4_CR_DLLSTATUS_Lock_OFF                               ( 2)
  #define DDRDATA4_CR_DLLSTATUS_Lock_WID                               ( 1)
  #define DDRDATA4_CR_DLLSTATUS_Lock_MSK                               (0x00000004)
  #define DDRDATA4_CR_DLLSTATUS_Lock_MIN                               (0)
  #define DDRDATA4_CR_DLLSTATUS_Lock_MAX                               (1) // 0x00000001
  #define DDRDATA4_CR_DLLSTATUS_Lock_DEF                               (0x00000000)
  #define DDRDATA4_CR_DLLSTATUS_Lock_HSH                               (0x01022220)

  #define DDRDATA4_CR_DLLSTATUS_Timeout_OFF                            ( 3)
  #define DDRDATA4_CR_DLLSTATUS_Timeout_WID                            ( 1)
  #define DDRDATA4_CR_DLLSTATUS_Timeout_MSK                            (0x00000008)
  #define DDRDATA4_CR_DLLSTATUS_Timeout_MIN                            (0)
  #define DDRDATA4_CR_DLLSTATUS_Timeout_MAX                            (1) // 0x00000001
  #define DDRDATA4_CR_DLLSTATUS_Timeout_DEF                            (0x00000000)
  #define DDRDATA4_CR_DLLSTATUS_Timeout_HSH                            (0x01032220)

  #define DDRDATA4_CR_DLLSTATUS_DllReset_OFF                           ( 4)
  #define DDRDATA4_CR_DLLSTATUS_DllReset_WID                           ( 1)
  #define DDRDATA4_CR_DLLSTATUS_DllReset_MSK                           (0x00000010)
  #define DDRDATA4_CR_DLLSTATUS_DllReset_MIN                           (0)
  #define DDRDATA4_CR_DLLSTATUS_DllReset_MAX                           (1) // 0x00000001
  #define DDRDATA4_CR_DLLSTATUS_DllReset_DEF                           (0x00000000)
  #define DDRDATA4_CR_DLLSTATUS_DllReset_HSH                           (0x01042220)

  #define DDRDATA4_CR_DLLSTATUS_LongLockStat_OFF                       ( 5)
  #define DDRDATA4_CR_DLLSTATUS_LongLockStat_WID                       ( 1)
  #define DDRDATA4_CR_DLLSTATUS_LongLockStat_MSK                       (0x00000020)
  #define DDRDATA4_CR_DLLSTATUS_LongLockStat_MIN                       (0)
  #define DDRDATA4_CR_DLLSTATUS_LongLockStat_MAX                       (1) // 0x00000001
  #define DDRDATA4_CR_DLLSTATUS_LongLockStat_DEF                       (0x00000000)
  #define DDRDATA4_CR_DLLSTATUS_LongLockStat_HSH                       (0x01052220)

  #define DDRDATA4_CR_DLLSTATUS_EarlyLockStat_OFF                      ( 6)
  #define DDRDATA4_CR_DLLSTATUS_EarlyLockStat_WID                      ( 1)
  #define DDRDATA4_CR_DLLSTATUS_EarlyLockStat_MSK                      (0x00000040)
  #define DDRDATA4_CR_DLLSTATUS_EarlyLockStat_MIN                      (0)
  #define DDRDATA4_CR_DLLSTATUS_EarlyLockStat_MAX                      (1) // 0x00000001
  #define DDRDATA4_CR_DLLSTATUS_EarlyLockStat_DEF                      (0x00000000)
  #define DDRDATA4_CR_DLLSTATUS_EarlyLockStat_HSH                      (0x01062220)

  #define DDRDATA4_CR_DLLSTATUS_NormalMode_NotWkLock_OFF               ( 7)
  #define DDRDATA4_CR_DLLSTATUS_NormalMode_NotWkLock_WID               ( 1)
  #define DDRDATA4_CR_DLLSTATUS_NormalMode_NotWkLock_MSK               (0x00000080)
  #define DDRDATA4_CR_DLLSTATUS_NormalMode_NotWkLock_MIN               (0)
  #define DDRDATA4_CR_DLLSTATUS_NormalMode_NotWkLock_MAX               (1) // 0x00000001
  #define DDRDATA4_CR_DLLSTATUS_NormalMode_NotWkLock_DEF               (0x00000000)
  #define DDRDATA4_CR_DLLSTATUS_NormalMode_NotWkLock_HSH               (0x01072220)

  #define DDRDATA4_CR_DLLSTATUS_ADCout_OFF                             ( 8)
  #define DDRDATA4_CR_DLLSTATUS_ADCout_WID                             (10)
  #define DDRDATA4_CR_DLLSTATUS_ADCout_MSK                             (0x0003FF00)
  #define DDRDATA4_CR_DLLSTATUS_ADCout_MIN                             (0)
  #define DDRDATA4_CR_DLLSTATUS_ADCout_MAX                             (1023) // 0x000003FF
  #define DDRDATA4_CR_DLLSTATUS_ADCout_DEF                             (0x00000000)
  #define DDRDATA4_CR_DLLSTATUS_ADCout_HSH                             (0x0A082220)

  #define DDRDATA4_CR_DLLSTATUS_ADCStatus_OFF                          (18)
  #define DDRDATA4_CR_DLLSTATUS_ADCStatus_WID                          ( 1)
  #define DDRDATA4_CR_DLLSTATUS_ADCStatus_MSK                          (0x00040000)
  #define DDRDATA4_CR_DLLSTATUS_ADCStatus_MIN                          (0)
  #define DDRDATA4_CR_DLLSTATUS_ADCStatus_MAX                          (1) // 0x00000001
  #define DDRDATA4_CR_DLLSTATUS_ADCStatus_DEF                          (0x00000000)
  #define DDRDATA4_CR_DLLSTATUS_ADCStatus_HSH                          (0x01122220)

  #define DDRDATA4_CR_DLLSTATUS_pilags_OFF                             (19)
  #define DDRDATA4_CR_DLLSTATUS_pilags_WID                             ( 1)
  #define DDRDATA4_CR_DLLSTATUS_pilags_MSK                             (0x00080000)
  #define DDRDATA4_CR_DLLSTATUS_pilags_MIN                             (0)
  #define DDRDATA4_CR_DLLSTATUS_pilags_MAX                             (1) // 0x00000001
  #define DDRDATA4_CR_DLLSTATUS_pilags_DEF                             (0x00000000)
  #define DDRDATA4_CR_DLLSTATUS_pilags_HSH                             (0x01132220)

  #define DDRDATA4_CR_DLLSTATUS_spare_OFF                              (20)
  #define DDRDATA4_CR_DLLSTATUS_spare_WID                              (12)
  #define DDRDATA4_CR_DLLSTATUS_spare_MSK                              (0xFFF00000)
  #define DDRDATA4_CR_DLLSTATUS_spare_MIN                              (0)
  #define DDRDATA4_CR_DLLSTATUS_spare_MAX                              (4095) // 0x00000FFF
  #define DDRDATA4_CR_DLLSTATUS_spare_DEF                              (0x00000000)
  #define DDRDATA4_CR_DLLSTATUS_spare_HSH                              (0x0C142220)

#define DDRDATA4_CR_DLLDCMCTL_REG                                      (0x00002224)

  #define DDRDATA4_CR_DLLDCMCTL_start_OFF                              ( 0)
  #define DDRDATA4_CR_DLLDCMCTL_start_WID                              ( 1)
  #define DDRDATA4_CR_DLLDCMCTL_start_MSK                              (0x00000001)
  #define DDRDATA4_CR_DLLDCMCTL_start_MIN                              (0)
  #define DDRDATA4_CR_DLLDCMCTL_start_MAX                              (1) // 0x00000001
  #define DDRDATA4_CR_DLLDCMCTL_start_DEF                              (0x00000000)
  #define DDRDATA4_CR_DLLDCMCTL_start_HSH                              (0x01002224)

  #define DDRDATA4_CR_DLLDCMCTL_clken_OFF                              ( 1)
  #define DDRDATA4_CR_DLLDCMCTL_clken_WID                              ( 1)
  #define DDRDATA4_CR_DLLDCMCTL_clken_MSK                              (0x00000002)
  #define DDRDATA4_CR_DLLDCMCTL_clken_MIN                              (0)
  #define DDRDATA4_CR_DLLDCMCTL_clken_MAX                              (1) // 0x00000001
  #define DDRDATA4_CR_DLLDCMCTL_clken_DEF                              (0x00000000)
  #define DDRDATA4_CR_DLLDCMCTL_clken_HSH                              (0x01012224)

  #define DDRDATA4_CR_DLLDCMCTL_dcm_dccctl_en_OFF                      ( 2)
  #define DDRDATA4_CR_DLLDCMCTL_dcm_dccctl_en_WID                      ( 1)
  #define DDRDATA4_CR_DLLDCMCTL_dcm_dccctl_en_MSK                      (0x00000004)
  #define DDRDATA4_CR_DLLDCMCTL_dcm_dccctl_en_MIN                      (0)
  #define DDRDATA4_CR_DLLDCMCTL_dcm_dccctl_en_MAX                      (1) // 0x00000001
  #define DDRDATA4_CR_DLLDCMCTL_dcm_dccctl_en_DEF                      (0x00000000)
  #define DDRDATA4_CR_DLLDCMCTL_dcm_dccctl_en_HSH                      (0x01022224)

  #define DDRDATA4_CR_DLLDCMCTL_dccctl_OFF                             ( 3)
  #define DDRDATA4_CR_DLLDCMCTL_dccctl_WID                             ( 4)
  #define DDRDATA4_CR_DLLDCMCTL_dccctl_MSK                             (0x00000078)
  #define DDRDATA4_CR_DLLDCMCTL_dccctl_MIN                             (0)
  #define DDRDATA4_CR_DLLDCMCTL_dccctl_MAX                             (15) // 0x0000000F
  #define DDRDATA4_CR_DLLDCMCTL_dccctl_DEF                             (0x00000000)
  #define DDRDATA4_CR_DLLDCMCTL_dccctl_HSH                             (0x04032224)

  #define DDRDATA4_CR_DLLDCMCTL_duration_OFF                           ( 7)
  #define DDRDATA4_CR_DLLDCMCTL_duration_WID                           ( 3)
  #define DDRDATA4_CR_DLLDCMCTL_duration_MSK                           (0x00000380)
  #define DDRDATA4_CR_DLLDCMCTL_duration_MIN                           (0)
  #define DDRDATA4_CR_DLLDCMCTL_duration_MAX                           (7) // 0x00000007
  #define DDRDATA4_CR_DLLDCMCTL_duration_DEF                           (0x00000000)
  #define DDRDATA4_CR_DLLDCMCTL_duration_HSH                           (0x03072224)

  #define DDRDATA4_CR_DLLDCMCTL_dcm_done_OFF                           (10)
  #define DDRDATA4_CR_DLLDCMCTL_dcm_done_WID                           ( 1)
  #define DDRDATA4_CR_DLLDCMCTL_dcm_done_MSK                           (0x00000400)
  #define DDRDATA4_CR_DLLDCMCTL_dcm_done_MIN                           (0)
  #define DDRDATA4_CR_DLLDCMCTL_dcm_done_MAX                           (1) // 0x00000001
  #define DDRDATA4_CR_DLLDCMCTL_dcm_done_DEF                           (0x00000000)
  #define DDRDATA4_CR_DLLDCMCTL_dcm_done_HSH                           (0x010A2224)

  #define DDRDATA4_CR_DLLDCMCTL_dcm_results_OFF                        (11)
  #define DDRDATA4_CR_DLLDCMCTL_dcm_results_WID                        (15)
  #define DDRDATA4_CR_DLLDCMCTL_dcm_results_MSK                        (0x03FFF800)
  #define DDRDATA4_CR_DLLDCMCTL_dcm_results_MIN                        (0)
  #define DDRDATA4_CR_DLLDCMCTL_dcm_results_MAX                        (32767) // 0x00007FFF
  #define DDRDATA4_CR_DLLDCMCTL_dcm_results_DEF                        (0x00000000)
  #define DDRDATA4_CR_DLLDCMCTL_dcm_results_HSH                        (0x0F0B2224)

  #define DDRDATA4_CR_DLLDCMCTL_spare0_OFF                             (26)
  #define DDRDATA4_CR_DLLDCMCTL_spare0_WID                             ( 6)
  #define DDRDATA4_CR_DLLDCMCTL_spare0_MSK                             (0xFC000000)
  #define DDRDATA4_CR_DLLDCMCTL_spare0_MIN                             (0)
  #define DDRDATA4_CR_DLLDCMCTL_spare0_MAX                             (63) // 0x0000003F
  #define DDRDATA4_CR_DLLDCMCTL_spare0_DEF                             (0x00000000)
  #define DDRDATA4_CR_DLLDCMCTL_spare0_HSH                             (0x061A2224)

#define DDRDATA5_CR_MASTERDLLCFG_REG                                   (0x00002280)

  #define DDRDATA5_CR_MASTERDLLCFG_LockThresh_OFF                      ( 0)
  #define DDRDATA5_CR_MASTERDLLCFG_LockThresh_WID                      ( 3)
  #define DDRDATA5_CR_MASTERDLLCFG_LockThresh_MSK                      (0x00000007)
  #define DDRDATA5_CR_MASTERDLLCFG_LockThresh_MIN                      (0)
  #define DDRDATA5_CR_MASTERDLLCFG_LockThresh_MAX                      (7) // 0x00000007
  #define DDRDATA5_CR_MASTERDLLCFG_LockThresh_DEF                      (0x00000004)
  #define DDRDATA5_CR_MASTERDLLCFG_LockThresh_HSH                      (0x03002280)

  #define DDRDATA5_CR_MASTERDLLCFG_LockCtr_OFF                         ( 3)
  #define DDRDATA5_CR_MASTERDLLCFG_LockCtr_WID                         ( 2)
  #define DDRDATA5_CR_MASTERDLLCFG_LockCtr_MSK                         (0x00000018)
  #define DDRDATA5_CR_MASTERDLLCFG_LockCtr_MIN                         (0)
  #define DDRDATA5_CR_MASTERDLLCFG_LockCtr_MAX                         (3) // 0x00000003
  #define DDRDATA5_CR_MASTERDLLCFG_LockCtr_DEF                         (0x00000000)
  #define DDRDATA5_CR_MASTERDLLCFG_LockCtr_HSH                         (0x02032280)

  #define DDRDATA5_CR_MASTERDLLCFG_VctrlDischRate_OFF                  ( 5)
  #define DDRDATA5_CR_MASTERDLLCFG_VctrlDischRate_WID                  ( 2)
  #define DDRDATA5_CR_MASTERDLLCFG_VctrlDischRate_MSK                  (0x00000060)
  #define DDRDATA5_CR_MASTERDLLCFG_VctrlDischRate_MIN                  (0)
  #define DDRDATA5_CR_MASTERDLLCFG_VctrlDischRate_MAX                  (3) // 0x00000003
  #define DDRDATA5_CR_MASTERDLLCFG_VctrlDischRate_DEF                  (0x00000000)
  #define DDRDATA5_CR_MASTERDLLCFG_VctrlDischRate_HSH                  (0x02052280)

  #define DDRDATA5_CR_MASTERDLLCFG_SelVctrlHi_OFF                      ( 7)
  #define DDRDATA5_CR_MASTERDLLCFG_SelVctrlHi_WID                      ( 1)
  #define DDRDATA5_CR_MASTERDLLCFG_SelVctrlHi_MSK                      (0x00000080)
  #define DDRDATA5_CR_MASTERDLLCFG_SelVctrlHi_MIN                      (0)
  #define DDRDATA5_CR_MASTERDLLCFG_SelVctrlHi_MAX                      (1) // 0x00000001
  #define DDRDATA5_CR_MASTERDLLCFG_SelVctrlHi_DEF                      (0x00000000)
  #define DDRDATA5_CR_MASTERDLLCFG_SelVctrlHi_HSH                      (0x01072280)

  #define DDRDATA5_CR_MASTERDLLCFG_StartupCntSel_OFF                   ( 8)
  #define DDRDATA5_CR_MASTERDLLCFG_StartupCntSel_WID                   ( 1)
  #define DDRDATA5_CR_MASTERDLLCFG_StartupCntSel_MSK                   (0x00000100)
  #define DDRDATA5_CR_MASTERDLLCFG_StartupCntSel_MIN                   (0)
  #define DDRDATA5_CR_MASTERDLLCFG_StartupCntSel_MAX                   (1) // 0x00000001
  #define DDRDATA5_CR_MASTERDLLCFG_StartupCntSel_DEF                   (0x00000000)
  #define DDRDATA5_CR_MASTERDLLCFG_StartupCntSel_HSH                   (0x01082280)

  #define DDRDATA5_CR_MASTERDLLCFG_LockSel_OFF                         ( 9)
  #define DDRDATA5_CR_MASTERDLLCFG_LockSel_WID                         ( 2)
  #define DDRDATA5_CR_MASTERDLLCFG_LockSel_MSK                         (0x00000600)
  #define DDRDATA5_CR_MASTERDLLCFG_LockSel_MIN                         (0)
  #define DDRDATA5_CR_MASTERDLLCFG_LockSel_MAX                         (3) // 0x00000003
  #define DDRDATA5_CR_MASTERDLLCFG_LockSel_DEF                         (0x00000000)
  #define DDRDATA5_CR_MASTERDLLCFG_LockSel_HSH                         (0x02092280)

  #define DDRDATA5_CR_MASTERDLLCFG_RstOvrd_OFF                         (11)
  #define DDRDATA5_CR_MASTERDLLCFG_RstOvrd_WID                         ( 1)
  #define DDRDATA5_CR_MASTERDLLCFG_RstOvrd_MSK                         (0x00000800)
  #define DDRDATA5_CR_MASTERDLLCFG_RstOvrd_MIN                         (0)
  #define DDRDATA5_CR_MASTERDLLCFG_RstOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA5_CR_MASTERDLLCFG_RstOvrd_DEF                         (0x00000000)
  #define DDRDATA5_CR_MASTERDLLCFG_RstOvrd_HSH                         (0x010B2280)

  #define DDRDATA5_CR_MASTERDLLCFG_SelRstOvrd_OFF                      (12)
  #define DDRDATA5_CR_MASTERDLLCFG_SelRstOvrd_WID                      ( 1)
  #define DDRDATA5_CR_MASTERDLLCFG_SelRstOvrd_MSK                      (0x00001000)
  #define DDRDATA5_CR_MASTERDLLCFG_SelRstOvrd_MIN                      (0)
  #define DDRDATA5_CR_MASTERDLLCFG_SelRstOvrd_MAX                      (1) // 0x00000001
  #define DDRDATA5_CR_MASTERDLLCFG_SelRstOvrd_DEF                      (0x00000000)
  #define DDRDATA5_CR_MASTERDLLCFG_SelRstOvrd_HSH                      (0x010C2280)

  #define DDRDATA5_CR_MASTERDLLCFG_TimeOutOvrd_OFF                     (13)
  #define DDRDATA5_CR_MASTERDLLCFG_TimeOutOvrd_WID                     ( 1)
  #define DDRDATA5_CR_MASTERDLLCFG_TimeOutOvrd_MSK                     (0x00002000)
  #define DDRDATA5_CR_MASTERDLLCFG_TimeOutOvrd_MIN                     (0)
  #define DDRDATA5_CR_MASTERDLLCFG_TimeOutOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA5_CR_MASTERDLLCFG_TimeOutOvrd_DEF                     (0x00000000)
  #define DDRDATA5_CR_MASTERDLLCFG_TimeOutOvrd_HSH                     (0x010D2280)

  #define DDRDATA5_CR_MASTERDLLCFG_SelTimeOutOvrd_OFF                  (14)
  #define DDRDATA5_CR_MASTERDLLCFG_SelTimeOutOvrd_WID                  ( 1)
  #define DDRDATA5_CR_MASTERDLLCFG_SelTimeOutOvrd_MSK                  (0x00004000)
  #define DDRDATA5_CR_MASTERDLLCFG_SelTimeOutOvrd_MIN                  (0)
  #define DDRDATA5_CR_MASTERDLLCFG_SelTimeOutOvrd_MAX                  (1) // 0x00000001
  #define DDRDATA5_CR_MASTERDLLCFG_SelTimeOutOvrd_DEF                  (0x00000000)
  #define DDRDATA5_CR_MASTERDLLCFG_SelTimeOutOvrd_HSH                  (0x010E2280)

  #define DDRDATA5_CR_MASTERDLLCFG_ClkGateOvrd_OFF                     (15)
  #define DDRDATA5_CR_MASTERDLLCFG_ClkGateOvrd_WID                     ( 1)
  #define DDRDATA5_CR_MASTERDLLCFG_ClkGateOvrd_MSK                     (0x00008000)
  #define DDRDATA5_CR_MASTERDLLCFG_ClkGateOvrd_MIN                     (0)
  #define DDRDATA5_CR_MASTERDLLCFG_ClkGateOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA5_CR_MASTERDLLCFG_ClkGateOvrd_DEF                     (0x00000000)
  #define DDRDATA5_CR_MASTERDLLCFG_ClkGateOvrd_HSH                     (0x010F2280)

  #define DDRDATA5_CR_MASTERDLLCFG_LockOvrd_OFF                        (16)
  #define DDRDATA5_CR_MASTERDLLCFG_LockOvrd_WID                        ( 1)
  #define DDRDATA5_CR_MASTERDLLCFG_LockOvrd_MSK                        (0x00010000)
  #define DDRDATA5_CR_MASTERDLLCFG_LockOvrd_MIN                        (0)
  #define DDRDATA5_CR_MASTERDLLCFG_LockOvrd_MAX                        (1) // 0x00000001
  #define DDRDATA5_CR_MASTERDLLCFG_LockOvrd_DEF                        (0x00000000)
  #define DDRDATA5_CR_MASTERDLLCFG_LockOvrd_HSH                        (0x01102280)

  #define DDRDATA5_CR_MASTERDLLCFG_SelLockOvrd_OFF                     (17)
  #define DDRDATA5_CR_MASTERDLLCFG_SelLockOvrd_WID                     ( 1)
  #define DDRDATA5_CR_MASTERDLLCFG_SelLockOvrd_MSK                     (0x00020000)
  #define DDRDATA5_CR_MASTERDLLCFG_SelLockOvrd_MIN                     (0)
  #define DDRDATA5_CR_MASTERDLLCFG_SelLockOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA5_CR_MASTERDLLCFG_SelLockOvrd_DEF                     (0x00000000)
  #define DDRDATA5_CR_MASTERDLLCFG_SelLockOvrd_HSH                     (0x01112280)

  #define DDRDATA5_CR_MASTERDLLCFG_OpenLoopOvrd_OFF                    (18)
  #define DDRDATA5_CR_MASTERDLLCFG_OpenLoopOvrd_WID                    ( 1)
  #define DDRDATA5_CR_MASTERDLLCFG_OpenLoopOvrd_MSK                    (0x00040000)
  #define DDRDATA5_CR_MASTERDLLCFG_OpenLoopOvrd_MIN                    (0)
  #define DDRDATA5_CR_MASTERDLLCFG_OpenLoopOvrd_MAX                    (1) // 0x00000001
  #define DDRDATA5_CR_MASTERDLLCFG_OpenLoopOvrd_DEF                    (0x00000000)
  #define DDRDATA5_CR_MASTERDLLCFG_OpenLoopOvrd_HSH                    (0x01122280)

  #define DDRDATA5_CR_MASTERDLLCFG_SelOpenLoopOvrd_OFF                 (19)
  #define DDRDATA5_CR_MASTERDLLCFG_SelOpenLoopOvrd_WID                 ( 1)
  #define DDRDATA5_CR_MASTERDLLCFG_SelOpenLoopOvrd_MSK                 (0x00080000)
  #define DDRDATA5_CR_MASTERDLLCFG_SelOpenLoopOvrd_MIN                 (0)
  #define DDRDATA5_CR_MASTERDLLCFG_SelOpenLoopOvrd_MAX                 (1) // 0x00000001
  #define DDRDATA5_CR_MASTERDLLCFG_SelOpenLoopOvrd_DEF                 (0x00000000)
  #define DDRDATA5_CR_MASTERDLLCFG_SelOpenLoopOvrd_HSH                 (0x01132280)

  #define DDRDATA5_CR_MASTERDLLCFG_WkLockEnOvrd_OFF                    (20)
  #define DDRDATA5_CR_MASTERDLLCFG_WkLockEnOvrd_WID                    ( 1)
  #define DDRDATA5_CR_MASTERDLLCFG_WkLockEnOvrd_MSK                    (0x00100000)
  #define DDRDATA5_CR_MASTERDLLCFG_WkLockEnOvrd_MIN                    (0)
  #define DDRDATA5_CR_MASTERDLLCFG_WkLockEnOvrd_MAX                    (1) // 0x00000001
  #define DDRDATA5_CR_MASTERDLLCFG_WkLockEnOvrd_DEF                    (0x00000000)
  #define DDRDATA5_CR_MASTERDLLCFG_WkLockEnOvrd_HSH                    (0x01142280)

  #define DDRDATA5_CR_MASTERDLLCFG_SelWkLockEnOvrd_OFF                 (21)
  #define DDRDATA5_CR_MASTERDLLCFG_SelWkLockEnOvrd_WID                 ( 1)
  #define DDRDATA5_CR_MASTERDLLCFG_SelWkLockEnOvrd_MSK                 (0x00200000)
  #define DDRDATA5_CR_MASTERDLLCFG_SelWkLockEnOvrd_MIN                 (0)
  #define DDRDATA5_CR_MASTERDLLCFG_SelWkLockEnOvrd_MAX                 (1) // 0x00000001
  #define DDRDATA5_CR_MASTERDLLCFG_SelWkLockEnOvrd_DEF                 (0x00000000)
  #define DDRDATA5_CR_MASTERDLLCFG_SelWkLockEnOvrd_HSH                 (0x01152280)

  #define DDRDATA5_CR_MASTERDLLCFG_CfdlDis_OFF                         (22)
  #define DDRDATA5_CR_MASTERDLLCFG_CfdlDis_WID                         ( 1)
  #define DDRDATA5_CR_MASTERDLLCFG_CfdlDis_MSK                         (0x00400000)
  #define DDRDATA5_CR_MASTERDLLCFG_CfdlDis_MIN                         (0)
  #define DDRDATA5_CR_MASTERDLLCFG_CfdlDis_MAX                         (1) // 0x00000001
  #define DDRDATA5_CR_MASTERDLLCFG_CfdlDis_DEF                         (0x00000000)
  #define DDRDATA5_CR_MASTERDLLCFG_CfdlDis_HSH                         (0x01162280)

  #define DDRDATA5_CR_MASTERDLLCFG_DftEn_OFF                           (23)
  #define DDRDATA5_CR_MASTERDLLCFG_DftEn_WID                           ( 1)
  #define DDRDATA5_CR_MASTERDLLCFG_DftEn_MSK                           (0x00800000)
  #define DDRDATA5_CR_MASTERDLLCFG_DftEn_MIN                           (0)
  #define DDRDATA5_CR_MASTERDLLCFG_DftEn_MAX                           (1) // 0x00000001
  #define DDRDATA5_CR_MASTERDLLCFG_DftEn_DEF                           (0x00000000)
  #define DDRDATA5_CR_MASTERDLLCFG_DftEn_HSH                           (0x01172280)

  #define DDRDATA5_CR_MASTERDLLCFG_spare0_OFF                          (24)
  #define DDRDATA5_CR_MASTERDLLCFG_spare0_WID                          ( 8)
  #define DDRDATA5_CR_MASTERDLLCFG_spare0_MSK                          (0xFF000000)
  #define DDRDATA5_CR_MASTERDLLCFG_spare0_MIN                          (0)
  #define DDRDATA5_CR_MASTERDLLCFG_spare0_MAX                          (255) // 0x000000FF
  #define DDRDATA5_CR_MASTERDLLCFG_spare0_DEF                          (0x00000000)
  #define DDRDATA5_CR_MASTERDLLCFG_spare0_HSH                          (0x08182280)

#define DDRDATA5_CR_CBTUNE0_REG                                        (0x00002284)

  #define DDRDATA5_CR_CBTUNE0_DllBWEn_OFF                              ( 0)
  #define DDRDATA5_CR_CBTUNE0_DllBWEn_WID                              (32)
  #define DDRDATA5_CR_CBTUNE0_DllBWEn_MSK                              (0xFFFFFFFF)
  #define DDRDATA5_CR_CBTUNE0_DllBWEn_MIN                              (0)
  #define DDRDATA5_CR_CBTUNE0_DllBWEn_MAX                              (4294967295) // 0xFFFFFFFF
  #define DDRDATA5_CR_CBTUNE0_DllBWEn_DEF                              (0xFDB86521)
  #define DDRDATA5_CR_CBTUNE0_DllBWEn_HSH                              (0x20002284)

#define DDRDATA5_CR_CBTUNE1_REG                                        (0x00002288)

  #define DDRDATA5_CR_CBTUNE1_PiCbEn_OFF                               ( 0)
  #define DDRDATA5_CR_CBTUNE1_PiCbEn_WID                               (24)
  #define DDRDATA5_CR_CBTUNE1_PiCbEn_MSK                               (0x00FFFFFF)
  #define DDRDATA5_CR_CBTUNE1_PiCbEn_MIN                               (0)
  #define DDRDATA5_CR_CBTUNE1_PiCbEn_MAX                               (16777215) // 0x00FFFFFF
  #define DDRDATA5_CR_CBTUNE1_PiCbEn_DEF                               (0x00249492)
  #define DDRDATA5_CR_CBTUNE1_PiCbEn_HSH                               (0x18002288)

  #define DDRDATA5_CR_CBTUNE1_CbEnRsvd_OFF                             (24)
  #define DDRDATA5_CR_CBTUNE1_CbEnRsvd_WID                             ( 3)
  #define DDRDATA5_CR_CBTUNE1_CbEnRsvd_MSK                             (0x07000000)
  #define DDRDATA5_CR_CBTUNE1_CbEnRsvd_MIN                             (0)
  #define DDRDATA5_CR_CBTUNE1_CbEnRsvd_MAX                             (7) // 0x00000007
  #define DDRDATA5_CR_CBTUNE1_CbEnRsvd_DEF                             (0x00000000)
  #define DDRDATA5_CR_CBTUNE1_CbEnRsvd_HSH                             (0x03182288)

  #define DDRDATA5_CR_CBTUNE1_CbEnDllFuse_OFF                          (27)
  #define DDRDATA5_CR_CBTUNE1_CbEnDllFuse_WID                          ( 3)
  #define DDRDATA5_CR_CBTUNE1_CbEnDllFuse_MSK                          (0x38000000)
  #define DDRDATA5_CR_CBTUNE1_CbEnDllFuse_MIN                          (0)
  #define DDRDATA5_CR_CBTUNE1_CbEnDllFuse_MAX                          (7) // 0x00000007
  #define DDRDATA5_CR_CBTUNE1_CbEnDllFuse_DEF                          (0x00000002)
  #define DDRDATA5_CR_CBTUNE1_CbEnDllFuse_HSH                          (0x031B2288)

  #define DDRDATA5_CR_CBTUNE1_Spare_OFF                                (30)
  #define DDRDATA5_CR_CBTUNE1_Spare_WID                                ( 2)
  #define DDRDATA5_CR_CBTUNE1_Spare_MSK                                (0xC0000000)
  #define DDRDATA5_CR_CBTUNE1_Spare_MIN                                (0)
  #define DDRDATA5_CR_CBTUNE1_Spare_MAX                                (3) // 0x00000003
  #define DDRDATA5_CR_CBTUNE1_Spare_DEF                                (0x00000000)
  #define DDRDATA5_CR_CBTUNE1_Spare_HSH                                (0x021E2288)

#define DDRDATA5_CR_ADCCFG_REG                                         (0x0000228C)

  #define DDRDATA5_CR_ADCCFG_ADC_frz_OFF                               ( 0)
  #define DDRDATA5_CR_ADCCFG_ADC_frz_WID                               ( 1)
  #define DDRDATA5_CR_ADCCFG_ADC_frz_MSK                               (0x00000001)
  #define DDRDATA5_CR_ADCCFG_ADC_frz_MIN                               (0)
  #define DDRDATA5_CR_ADCCFG_ADC_frz_MAX                               (1) // 0x00000001
  #define DDRDATA5_CR_ADCCFG_ADC_frz_DEF                               (0x00000000)
  #define DDRDATA5_CR_ADCCFG_ADC_frz_HSH                               (0x0100228C)

  #define DDRDATA5_CR_ADCCFG_ADC_en_OFF                                ( 1)
  #define DDRDATA5_CR_ADCCFG_ADC_en_WID                                ( 1)
  #define DDRDATA5_CR_ADCCFG_ADC_en_MSK                                (0x00000002)
  #define DDRDATA5_CR_ADCCFG_ADC_en_MIN                                (0)
  #define DDRDATA5_CR_ADCCFG_ADC_en_MAX                                (1) // 0x00000001
  #define DDRDATA5_CR_ADCCFG_ADC_en_DEF                                (0x00000000)
  #define DDRDATA5_CR_ADCCFG_ADC_en_HSH                                (0x0101228C)

  #define DDRDATA5_CR_ADCCFG_ADCclkdiv_OFF                             ( 2)
  #define DDRDATA5_CR_ADCCFG_ADCclkdiv_WID                             ( 2)
  #define DDRDATA5_CR_ADCCFG_ADCclkdiv_MSK                             (0x0000000C)
  #define DDRDATA5_CR_ADCCFG_ADCclkdiv_MIN                             (0)
  #define DDRDATA5_CR_ADCCFG_ADCclkdiv_MAX                             (3) // 0x00000003
  #define DDRDATA5_CR_ADCCFG_ADCclkdiv_DEF                             (0x00000000)
  #define DDRDATA5_CR_ADCCFG_ADCclkdiv_HSH                             (0x0202228C)

  #define DDRDATA5_CR_ADCCFG_ADCstartcount_OFF                         ( 4)
  #define DDRDATA5_CR_ADCCFG_ADCstartcount_WID                         ( 2)
  #define DDRDATA5_CR_ADCCFG_ADCstartcount_MSK                         (0x00000030)
  #define DDRDATA5_CR_ADCCFG_ADCstartcount_MIN                         (0)
  #define DDRDATA5_CR_ADCCFG_ADCstartcount_MAX                         (3) // 0x00000003
  #define DDRDATA5_CR_ADCCFG_ADCstartcount_DEF                         (0x00000000)
  #define DDRDATA5_CR_ADCCFG_ADCstartcount_HSH                         (0x0204228C)

  #define DDRDATA5_CR_ADCCFG_ADCChopEn_OFF                             ( 6)
  #define DDRDATA5_CR_ADCCFG_ADCChopEn_WID                             ( 1)
  #define DDRDATA5_CR_ADCCFG_ADCChopEn_MSK                             (0x00000040)
  #define DDRDATA5_CR_ADCCFG_ADCChopEn_MIN                             (0)
  #define DDRDATA5_CR_ADCCFG_ADCChopEn_MAX                             (1) // 0x00000001
  #define DDRDATA5_CR_ADCCFG_ADCChopEn_DEF                             (0x00000000)
  #define DDRDATA5_CR_ADCCFG_ADCChopEn_HSH                             (0x0106228C)

  #define DDRDATA5_CR_ADCCFG_Spare_OFF                                 ( 7)
  #define DDRDATA5_CR_ADCCFG_Spare_WID                                 (25)
  #define DDRDATA5_CR_ADCCFG_Spare_MSK                                 (0xFFFFFF80)
  #define DDRDATA5_CR_ADCCFG_Spare_MIN                                 (0)
  #define DDRDATA5_CR_ADCCFG_Spare_MAX                                 (33554431) // 0x01FFFFFF
  #define DDRDATA5_CR_ADCCFG_Spare_DEF                                 (0x00000000)
  #define DDRDATA5_CR_ADCCFG_Spare_HSH                                 (0x1907228C)

#define DDRDATA5_CR_CBTUNE2_REG                                        (0x00002290)

  #define DDRDATA5_CR_CBTUNE2_DllCbEn_OFF                              ( 0)
  #define DDRDATA5_CR_CBTUNE2_DllCbEn_WID                              (16)
  #define DDRDATA5_CR_CBTUNE2_DllCbEn_MSK                              (0x0000FFFF)
  #define DDRDATA5_CR_CBTUNE2_DllCbEn_MIN                              (0)
  #define DDRDATA5_CR_CBTUNE2_DllCbEn_MAX                              (65535) // 0x0000FFFF
  #define DDRDATA5_CR_CBTUNE2_DllCbEn_DEF                              (0x00000000)
  #define DDRDATA5_CR_CBTUNE2_DllCbEn_HSH                              (0x10002290)

  #define DDRDATA5_CR_CBTUNE2_Spare_OFF                                (16)
  #define DDRDATA5_CR_CBTUNE2_Spare_WID                                (16)
  #define DDRDATA5_CR_CBTUNE2_Spare_MSK                                (0xFFFF0000)
  #define DDRDATA5_CR_CBTUNE2_Spare_MIN                                (0)
  #define DDRDATA5_CR_CBTUNE2_Spare_MAX                                (65535) // 0x0000FFFF
  #define DDRDATA5_CR_CBTUNE2_Spare_DEF                                (0x00000000)
  #define DDRDATA5_CR_CBTUNE2_Spare_HSH                                (0x10102290)

#define DDRDATA5_CR_PIDFTDLY_REG                                       (0x00002298)

  #define DDRDATA5_CR_PIDFTDLY_PiDftDelay_OFF                          ( 0)
  #define DDRDATA5_CR_PIDFTDLY_PiDftDelay_WID                          ( 7)
  #define DDRDATA5_CR_PIDFTDLY_PiDftDelay_MSK                          (0x0000007F)
  #define DDRDATA5_CR_PIDFTDLY_PiDftDelay_MIN                          (0)
  #define DDRDATA5_CR_PIDFTDLY_PiDftDelay_MAX                          (127) // 0x0000007F
  #define DDRDATA5_CR_PIDFTDLY_PiDftDelay_DEF                          (0x00000000)
  #define DDRDATA5_CR_PIDFTDLY_PiDftDelay_HSH                          (0x07002298)

  #define DDRDATA5_CR_PIDFTDLY_Ch0PiEnOvrd_OFF                         ( 7)
  #define DDRDATA5_CR_PIDFTDLY_Ch0PiEnOvrd_WID                         ( 1)
  #define DDRDATA5_CR_PIDFTDLY_Ch0PiEnOvrd_MSK                         (0x00000080)
  #define DDRDATA5_CR_PIDFTDLY_Ch0PiEnOvrd_MIN                         (0)
  #define DDRDATA5_CR_PIDFTDLY_Ch0PiEnOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA5_CR_PIDFTDLY_Ch0PiEnOvrd_DEF                         (0x00000000)
  #define DDRDATA5_CR_PIDFTDLY_Ch0PiEnOvrd_HSH                         (0x01072298)

  #define DDRDATA5_CR_PIDFTDLY_Ch1PiEnOvrd_OFF                         ( 8)
  #define DDRDATA5_CR_PIDFTDLY_Ch1PiEnOvrd_WID                         ( 1)
  #define DDRDATA5_CR_PIDFTDLY_Ch1PiEnOvrd_MSK                         (0x00000100)
  #define DDRDATA5_CR_PIDFTDLY_Ch1PiEnOvrd_MIN                         (0)
  #define DDRDATA5_CR_PIDFTDLY_Ch1PiEnOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA5_CR_PIDFTDLY_Ch1PiEnOvrd_DEF                         (0x00000000)
  #define DDRDATA5_CR_PIDFTDLY_Ch1PiEnOvrd_HSH                         (0x01082298)

  #define DDRDATA5_CR_PIDFTDLY_Ch0PiDFTEn_OFF                          ( 9)
  #define DDRDATA5_CR_PIDFTDLY_Ch0PiDFTEn_WID                          ( 1)
  #define DDRDATA5_CR_PIDFTDLY_Ch0PiDFTEn_MSK                          (0x00000200)
  #define DDRDATA5_CR_PIDFTDLY_Ch0PiDFTEn_MIN                          (0)
  #define DDRDATA5_CR_PIDFTDLY_Ch0PiDFTEn_MAX                          (1) // 0x00000001
  #define DDRDATA5_CR_PIDFTDLY_Ch0PiDFTEn_DEF                          (0x00000000)
  #define DDRDATA5_CR_PIDFTDLY_Ch0PiDFTEn_HSH                          (0x01092298)

  #define DDRDATA5_CR_PIDFTDLY_Ch1PiDFTEn_OFF                          (10)
  #define DDRDATA5_CR_PIDFTDLY_Ch1PiDFTEn_WID                          ( 1)
  #define DDRDATA5_CR_PIDFTDLY_Ch1PiDFTEn_MSK                          (0x00000400)
  #define DDRDATA5_CR_PIDFTDLY_Ch1PiDFTEn_MIN                          (0)
  #define DDRDATA5_CR_PIDFTDLY_Ch1PiDFTEn_MAX                          (1) // 0x00000001
  #define DDRDATA5_CR_PIDFTDLY_Ch1PiDFTEn_DEF                          (0x00000000)
  #define DDRDATA5_CR_PIDFTDLY_Ch1PiDFTEn_HSH                          (0x010A2298)

  #define DDRDATA5_CR_PIDFTDLY_Spare_OFF                               (11)
  #define DDRDATA5_CR_PIDFTDLY_Spare_WID                               ( 4)
  #define DDRDATA5_CR_PIDFTDLY_Spare_MSK                               (0x00007800)
  #define DDRDATA5_CR_PIDFTDLY_Spare_MIN                               (0)
  #define DDRDATA5_CR_PIDFTDLY_Spare_MAX                               (15) // 0x0000000F
  #define DDRDATA5_CR_PIDFTDLY_Spare_DEF                               (0x00000000)
  #define DDRDATA5_CR_PIDFTDLY_Spare_HSH                               (0x040B2298)

  #define DDRDATA5_CR_PIDFTDLY_RefPiOvrd_OFF                           (15)
  #define DDRDATA5_CR_PIDFTDLY_RefPiOvrd_WID                           ( 1)
  #define DDRDATA5_CR_PIDFTDLY_RefPiOvrd_MSK                           (0x00008000)
  #define DDRDATA5_CR_PIDFTDLY_RefPiOvrd_MIN                           (0)
  #define DDRDATA5_CR_PIDFTDLY_RefPiOvrd_MAX                           (1) // 0x00000001
  #define DDRDATA5_CR_PIDFTDLY_RefPiOvrd_DEF                           (0x00000000)
  #define DDRDATA5_CR_PIDFTDLY_RefPiOvrd_HSH                           (0x010F2298)

  #define DDRDATA5_CR_PIDFTDLY_Rsvd_OFF                                (16)
  #define DDRDATA5_CR_PIDFTDLY_Rsvd_WID                                (16)
  #define DDRDATA5_CR_PIDFTDLY_Rsvd_MSK                                (0xFFFF0000)
  #define DDRDATA5_CR_PIDFTDLY_Rsvd_MIN                                (0)
  #define DDRDATA5_CR_PIDFTDLY_Rsvd_MAX                                (65535) // 0x0000FFFF
  #define DDRDATA5_CR_PIDFTDLY_Rsvd_DEF                                (0x00000000)
  #define DDRDATA5_CR_PIDFTDLY_Rsvd_HSH                                (0x10102298)

#define DDRDATA5_CR_DLLPITESTANDADC_REG                                (0x0000229C)

  #define DDRDATA5_CR_DLLPITESTANDADC_RunTest_OFF                      ( 0)
  #define DDRDATA5_CR_DLLPITESTANDADC_RunTest_WID                      ( 1)
  #define DDRDATA5_CR_DLLPITESTANDADC_RunTest_MSK                      (0x00000001)
  #define DDRDATA5_CR_DLLPITESTANDADC_RunTest_MIN                      (0)
  #define DDRDATA5_CR_DLLPITESTANDADC_RunTest_MAX                      (1) // 0x00000001
  #define DDRDATA5_CR_DLLPITESTANDADC_RunTest_DEF                      (0x00000000)
  #define DDRDATA5_CR_DLLPITESTANDADC_RunTest_HSH                      (0x0100229C)

  #define DDRDATA5_CR_DLLPITESTANDADC_Load_OFF                         ( 1)
  #define DDRDATA5_CR_DLLPITESTANDADC_Load_WID                         ( 1)
  #define DDRDATA5_CR_DLLPITESTANDADC_Load_MSK                         (0x00000002)
  #define DDRDATA5_CR_DLLPITESTANDADC_Load_MIN                         (0)
  #define DDRDATA5_CR_DLLPITESTANDADC_Load_MAX                         (1) // 0x00000001
  #define DDRDATA5_CR_DLLPITESTANDADC_Load_DEF                         (0x00000000)
  #define DDRDATA5_CR_DLLPITESTANDADC_Load_HSH                         (0x0101229C)

  #define DDRDATA5_CR_DLLPITESTANDADC_ModeHVM_OFF                      ( 2)
  #define DDRDATA5_CR_DLLPITESTANDADC_ModeHVM_WID                      ( 1)
  #define DDRDATA5_CR_DLLPITESTANDADC_ModeHVM_MSK                      (0x00000004)
  #define DDRDATA5_CR_DLLPITESTANDADC_ModeHVM_MIN                      (0)
  #define DDRDATA5_CR_DLLPITESTANDADC_ModeHVM_MAX                      (1) // 0x00000001
  #define DDRDATA5_CR_DLLPITESTANDADC_ModeHVM_DEF                      (0x00000000)
  #define DDRDATA5_CR_DLLPITESTANDADC_ModeHVM_HSH                      (0x0102229C)

  #define DDRDATA5_CR_DLLPITESTANDADC_ModeDV_OFF                       ( 3)
  #define DDRDATA5_CR_DLLPITESTANDADC_ModeDV_WID                       ( 1)
  #define DDRDATA5_CR_DLLPITESTANDADC_ModeDV_MSK                       (0x00000008)
  #define DDRDATA5_CR_DLLPITESTANDADC_ModeDV_MIN                       (0)
  #define DDRDATA5_CR_DLLPITESTANDADC_ModeDV_MAX                       (1) // 0x00000001
  #define DDRDATA5_CR_DLLPITESTANDADC_ModeDV_DEF                       (0x00000000)
  #define DDRDATA5_CR_DLLPITESTANDADC_ModeDV_HSH                       (0x0103229C)

  #define DDRDATA5_CR_DLLPITESTANDADC_CalCfdl_OFF                      ( 4)
  #define DDRDATA5_CR_DLLPITESTANDADC_CalCfdl_WID                      ( 1)
  #define DDRDATA5_CR_DLLPITESTANDADC_CalCfdl_MSK                      (0x00000010)
  #define DDRDATA5_CR_DLLPITESTANDADC_CalCfdl_MIN                      (0)
  #define DDRDATA5_CR_DLLPITESTANDADC_CalCfdl_MAX                      (1) // 0x00000001
  #define DDRDATA5_CR_DLLPITESTANDADC_CalCfdl_DEF                      (0x00000000)
  #define DDRDATA5_CR_DLLPITESTANDADC_CalCfdl_HSH                      (0x0104229C)

  #define DDRDATA5_CR_DLLPITESTANDADC_LoadCount_OFF                    ( 5)
  #define DDRDATA5_CR_DLLPITESTANDADC_LoadCount_WID                    (10)
  #define DDRDATA5_CR_DLLPITESTANDADC_LoadCount_MSK                    (0x00007FE0)
  #define DDRDATA5_CR_DLLPITESTANDADC_LoadCount_MIN                    (0)
  #define DDRDATA5_CR_DLLPITESTANDADC_LoadCount_MAX                    (1023) // 0x000003FF
  #define DDRDATA5_CR_DLLPITESTANDADC_LoadCount_DEF                    (0x00000000)
  #define DDRDATA5_CR_DLLPITESTANDADC_LoadCount_HSH                    (0x0A05229C)

  #define DDRDATA5_CR_DLLPITESTANDADC_CountStatus_OFF                  (15)
  #define DDRDATA5_CR_DLLPITESTANDADC_CountStatus_WID                  (10)
  #define DDRDATA5_CR_DLLPITESTANDADC_CountStatus_MSK                  (0x01FF8000)
  #define DDRDATA5_CR_DLLPITESTANDADC_CountStatus_MIN                  (0)
  #define DDRDATA5_CR_DLLPITESTANDADC_CountStatus_MAX                  (1023) // 0x000003FF
  #define DDRDATA5_CR_DLLPITESTANDADC_CountStatus_DEF                  (0x00000000)
  #define DDRDATA5_CR_DLLPITESTANDADC_CountStatus_HSH                  (0x0A0F229C)

  #define DDRDATA5_CR_DLLPITESTANDADC_ModeADC_OFF                      (25)
  #define DDRDATA5_CR_DLLPITESTANDADC_ModeADC_WID                      ( 1)
  #define DDRDATA5_CR_DLLPITESTANDADC_ModeADC_MSK                      (0x02000000)
  #define DDRDATA5_CR_DLLPITESTANDADC_ModeADC_MIN                      (0)
  #define DDRDATA5_CR_DLLPITESTANDADC_ModeADC_MAX                      (1) // 0x00000001
  #define DDRDATA5_CR_DLLPITESTANDADC_ModeADC_DEF                      (0x00000000)
  #define DDRDATA5_CR_DLLPITESTANDADC_ModeADC_HSH                      (0x0119229C)

  #define DDRDATA5_CR_DLLPITESTANDADC_ADCClkDiv_OFF                    (26)
  #define DDRDATA5_CR_DLLPITESTANDADC_ADCClkDiv_WID                    ( 2)
  #define DDRDATA5_CR_DLLPITESTANDADC_ADCClkDiv_MSK                    (0x0C000000)
  #define DDRDATA5_CR_DLLPITESTANDADC_ADCClkDiv_MIN                    (0)
  #define DDRDATA5_CR_DLLPITESTANDADC_ADCClkDiv_MAX                    (3) // 0x00000003
  #define DDRDATA5_CR_DLLPITESTANDADC_ADCClkDiv_DEF                    (0x00000000)
  #define DDRDATA5_CR_DLLPITESTANDADC_ADCClkDiv_HSH                    (0x021A229C)

  #define DDRDATA5_CR_DLLPITESTANDADC_ADCDdrChanSel_OFF                (28)
  #define DDRDATA5_CR_DLLPITESTANDADC_ADCDdrChanSel_WID                ( 1)
  #define DDRDATA5_CR_DLLPITESTANDADC_ADCDdrChanSel_MSK                (0x10000000)
  #define DDRDATA5_CR_DLLPITESTANDADC_ADCDdrChanSel_MIN                (0)
  #define DDRDATA5_CR_DLLPITESTANDADC_ADCDdrChanSel_MAX                (1) // 0x00000001
  #define DDRDATA5_CR_DLLPITESTANDADC_ADCDdrChanSel_DEF                (0x00000000)
  #define DDRDATA5_CR_DLLPITESTANDADC_ADCDdrChanSel_HSH                (0x011C229C)

  #define DDRDATA5_CR_DLLPITESTANDADC_ADCChopEn_OFF                    (29)
  #define DDRDATA5_CR_DLLPITESTANDADC_ADCChopEn_WID                    ( 1)
  #define DDRDATA5_CR_DLLPITESTANDADC_ADCChopEn_MSK                    (0x20000000)
  #define DDRDATA5_CR_DLLPITESTANDADC_ADCChopEn_MIN                    (0)
  #define DDRDATA5_CR_DLLPITESTANDADC_ADCChopEn_MAX                    (1) // 0x00000001
  #define DDRDATA5_CR_DLLPITESTANDADC_ADCChopEn_DEF                    (0x00000000)
  #define DDRDATA5_CR_DLLPITESTANDADC_ADCChopEn_HSH                    (0x011D229C)

  #define DDRDATA5_CR_DLLPITESTANDADC_ADCDone_OFF                      (30)
  #define DDRDATA5_CR_DLLPITESTANDADC_ADCDone_WID                      ( 1)
  #define DDRDATA5_CR_DLLPITESTANDADC_ADCDone_MSK                      (0x40000000)
  #define DDRDATA5_CR_DLLPITESTANDADC_ADCDone_MIN                      (0)
  #define DDRDATA5_CR_DLLPITESTANDADC_ADCDone_MAX                      (1) // 0x00000001
  #define DDRDATA5_CR_DLLPITESTANDADC_ADCDone_DEF                      (0x00000000)
  #define DDRDATA5_CR_DLLPITESTANDADC_ADCDone_HSH                      (0x011E229C)

  #define DDRDATA5_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF             (31)
  #define DDRDATA5_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID             ( 1)
  #define DDRDATA5_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK             (0x80000000)
  #define DDRDATA5_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN             (0)
  #define DDRDATA5_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX             (1) // 0x00000001
  #define DDRDATA5_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF             (0x00000000)
  #define DDRDATA5_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH             (0x011F229C)

#define DDRDATA5_CR_DLLSTATUS_REG                                      (0x000022A0)

  #define DDRDATA5_CR_DLLSTATUS_DetrmLockStat_OFF                      ( 0)
  #define DDRDATA5_CR_DLLSTATUS_DetrmLockStat_WID                      ( 1)
  #define DDRDATA5_CR_DLLSTATUS_DetrmLockStat_MSK                      (0x00000001)
  #define DDRDATA5_CR_DLLSTATUS_DetrmLockStat_MIN                      (0)
  #define DDRDATA5_CR_DLLSTATUS_DetrmLockStat_MAX                      (1) // 0x00000001
  #define DDRDATA5_CR_DLLSTATUS_DetrmLockStat_DEF                      (0x00000000)
  #define DDRDATA5_CR_DLLSTATUS_DetrmLockStat_HSH                      (0x010022A0)

  #define DDRDATA5_CR_DLLSTATUS_FuncLockStat_OFF                       ( 1)
  #define DDRDATA5_CR_DLLSTATUS_FuncLockStat_WID                       ( 1)
  #define DDRDATA5_CR_DLLSTATUS_FuncLockStat_MSK                       (0x00000002)
  #define DDRDATA5_CR_DLLSTATUS_FuncLockStat_MIN                       (0)
  #define DDRDATA5_CR_DLLSTATUS_FuncLockStat_MAX                       (1) // 0x00000001
  #define DDRDATA5_CR_DLLSTATUS_FuncLockStat_DEF                       (0x00000000)
  #define DDRDATA5_CR_DLLSTATUS_FuncLockStat_HSH                       (0x010122A0)

  #define DDRDATA5_CR_DLLSTATUS_Lock_OFF                               ( 2)
  #define DDRDATA5_CR_DLLSTATUS_Lock_WID                               ( 1)
  #define DDRDATA5_CR_DLLSTATUS_Lock_MSK                               (0x00000004)
  #define DDRDATA5_CR_DLLSTATUS_Lock_MIN                               (0)
  #define DDRDATA5_CR_DLLSTATUS_Lock_MAX                               (1) // 0x00000001
  #define DDRDATA5_CR_DLLSTATUS_Lock_DEF                               (0x00000000)
  #define DDRDATA5_CR_DLLSTATUS_Lock_HSH                               (0x010222A0)

  #define DDRDATA5_CR_DLLSTATUS_Timeout_OFF                            ( 3)
  #define DDRDATA5_CR_DLLSTATUS_Timeout_WID                            ( 1)
  #define DDRDATA5_CR_DLLSTATUS_Timeout_MSK                            (0x00000008)
  #define DDRDATA5_CR_DLLSTATUS_Timeout_MIN                            (0)
  #define DDRDATA5_CR_DLLSTATUS_Timeout_MAX                            (1) // 0x00000001
  #define DDRDATA5_CR_DLLSTATUS_Timeout_DEF                            (0x00000000)
  #define DDRDATA5_CR_DLLSTATUS_Timeout_HSH                            (0x010322A0)

  #define DDRDATA5_CR_DLLSTATUS_DllReset_OFF                           ( 4)
  #define DDRDATA5_CR_DLLSTATUS_DllReset_WID                           ( 1)
  #define DDRDATA5_CR_DLLSTATUS_DllReset_MSK                           (0x00000010)
  #define DDRDATA5_CR_DLLSTATUS_DllReset_MIN                           (0)
  #define DDRDATA5_CR_DLLSTATUS_DllReset_MAX                           (1) // 0x00000001
  #define DDRDATA5_CR_DLLSTATUS_DllReset_DEF                           (0x00000000)
  #define DDRDATA5_CR_DLLSTATUS_DllReset_HSH                           (0x010422A0)

  #define DDRDATA5_CR_DLLSTATUS_LongLockStat_OFF                       ( 5)
  #define DDRDATA5_CR_DLLSTATUS_LongLockStat_WID                       ( 1)
  #define DDRDATA5_CR_DLLSTATUS_LongLockStat_MSK                       (0x00000020)
  #define DDRDATA5_CR_DLLSTATUS_LongLockStat_MIN                       (0)
  #define DDRDATA5_CR_DLLSTATUS_LongLockStat_MAX                       (1) // 0x00000001
  #define DDRDATA5_CR_DLLSTATUS_LongLockStat_DEF                       (0x00000000)
  #define DDRDATA5_CR_DLLSTATUS_LongLockStat_HSH                       (0x010522A0)

  #define DDRDATA5_CR_DLLSTATUS_EarlyLockStat_OFF                      ( 6)
  #define DDRDATA5_CR_DLLSTATUS_EarlyLockStat_WID                      ( 1)
  #define DDRDATA5_CR_DLLSTATUS_EarlyLockStat_MSK                      (0x00000040)
  #define DDRDATA5_CR_DLLSTATUS_EarlyLockStat_MIN                      (0)
  #define DDRDATA5_CR_DLLSTATUS_EarlyLockStat_MAX                      (1) // 0x00000001
  #define DDRDATA5_CR_DLLSTATUS_EarlyLockStat_DEF                      (0x00000000)
  #define DDRDATA5_CR_DLLSTATUS_EarlyLockStat_HSH                      (0x010622A0)

  #define DDRDATA5_CR_DLLSTATUS_NormalMode_NotWkLock_OFF               ( 7)
  #define DDRDATA5_CR_DLLSTATUS_NormalMode_NotWkLock_WID               ( 1)
  #define DDRDATA5_CR_DLLSTATUS_NormalMode_NotWkLock_MSK               (0x00000080)
  #define DDRDATA5_CR_DLLSTATUS_NormalMode_NotWkLock_MIN               (0)
  #define DDRDATA5_CR_DLLSTATUS_NormalMode_NotWkLock_MAX               (1) // 0x00000001
  #define DDRDATA5_CR_DLLSTATUS_NormalMode_NotWkLock_DEF               (0x00000000)
  #define DDRDATA5_CR_DLLSTATUS_NormalMode_NotWkLock_HSH               (0x010722A0)

  #define DDRDATA5_CR_DLLSTATUS_ADCout_OFF                             ( 8)
  #define DDRDATA5_CR_DLLSTATUS_ADCout_WID                             (10)
  #define DDRDATA5_CR_DLLSTATUS_ADCout_MSK                             (0x0003FF00)
  #define DDRDATA5_CR_DLLSTATUS_ADCout_MIN                             (0)
  #define DDRDATA5_CR_DLLSTATUS_ADCout_MAX                             (1023) // 0x000003FF
  #define DDRDATA5_CR_DLLSTATUS_ADCout_DEF                             (0x00000000)
  #define DDRDATA5_CR_DLLSTATUS_ADCout_HSH                             (0x0A0822A0)

  #define DDRDATA5_CR_DLLSTATUS_ADCStatus_OFF                          (18)
  #define DDRDATA5_CR_DLLSTATUS_ADCStatus_WID                          ( 1)
  #define DDRDATA5_CR_DLLSTATUS_ADCStatus_MSK                          (0x00040000)
  #define DDRDATA5_CR_DLLSTATUS_ADCStatus_MIN                          (0)
  #define DDRDATA5_CR_DLLSTATUS_ADCStatus_MAX                          (1) // 0x00000001
  #define DDRDATA5_CR_DLLSTATUS_ADCStatus_DEF                          (0x00000000)
  #define DDRDATA5_CR_DLLSTATUS_ADCStatus_HSH                          (0x011222A0)

  #define DDRDATA5_CR_DLLSTATUS_pilags_OFF                             (19)
  #define DDRDATA5_CR_DLLSTATUS_pilags_WID                             ( 1)
  #define DDRDATA5_CR_DLLSTATUS_pilags_MSK                             (0x00080000)
  #define DDRDATA5_CR_DLLSTATUS_pilags_MIN                             (0)
  #define DDRDATA5_CR_DLLSTATUS_pilags_MAX                             (1) // 0x00000001
  #define DDRDATA5_CR_DLLSTATUS_pilags_DEF                             (0x00000000)
  #define DDRDATA5_CR_DLLSTATUS_pilags_HSH                             (0x011322A0)

  #define DDRDATA5_CR_DLLSTATUS_spare_OFF                              (20)
  #define DDRDATA5_CR_DLLSTATUS_spare_WID                              (12)
  #define DDRDATA5_CR_DLLSTATUS_spare_MSK                              (0xFFF00000)
  #define DDRDATA5_CR_DLLSTATUS_spare_MIN                              (0)
  #define DDRDATA5_CR_DLLSTATUS_spare_MAX                              (4095) // 0x00000FFF
  #define DDRDATA5_CR_DLLSTATUS_spare_DEF                              (0x00000000)
  #define DDRDATA5_CR_DLLSTATUS_spare_HSH                              (0x0C1422A0)

#define DDRDATA5_CR_DLLDCMCTL_REG                                      (0x000022A4)

  #define DDRDATA5_CR_DLLDCMCTL_start_OFF                              ( 0)
  #define DDRDATA5_CR_DLLDCMCTL_start_WID                              ( 1)
  #define DDRDATA5_CR_DLLDCMCTL_start_MSK                              (0x00000001)
  #define DDRDATA5_CR_DLLDCMCTL_start_MIN                              (0)
  #define DDRDATA5_CR_DLLDCMCTL_start_MAX                              (1) // 0x00000001
  #define DDRDATA5_CR_DLLDCMCTL_start_DEF                              (0x00000000)
  #define DDRDATA5_CR_DLLDCMCTL_start_HSH                              (0x010022A4)

  #define DDRDATA5_CR_DLLDCMCTL_clken_OFF                              ( 1)
  #define DDRDATA5_CR_DLLDCMCTL_clken_WID                              ( 1)
  #define DDRDATA5_CR_DLLDCMCTL_clken_MSK                              (0x00000002)
  #define DDRDATA5_CR_DLLDCMCTL_clken_MIN                              (0)
  #define DDRDATA5_CR_DLLDCMCTL_clken_MAX                              (1) // 0x00000001
  #define DDRDATA5_CR_DLLDCMCTL_clken_DEF                              (0x00000000)
  #define DDRDATA5_CR_DLLDCMCTL_clken_HSH                              (0x010122A4)

  #define DDRDATA5_CR_DLLDCMCTL_dcm_dccctl_en_OFF                      ( 2)
  #define DDRDATA5_CR_DLLDCMCTL_dcm_dccctl_en_WID                      ( 1)
  #define DDRDATA5_CR_DLLDCMCTL_dcm_dccctl_en_MSK                      (0x00000004)
  #define DDRDATA5_CR_DLLDCMCTL_dcm_dccctl_en_MIN                      (0)
  #define DDRDATA5_CR_DLLDCMCTL_dcm_dccctl_en_MAX                      (1) // 0x00000001
  #define DDRDATA5_CR_DLLDCMCTL_dcm_dccctl_en_DEF                      (0x00000000)
  #define DDRDATA5_CR_DLLDCMCTL_dcm_dccctl_en_HSH                      (0x010222A4)

  #define DDRDATA5_CR_DLLDCMCTL_dccctl_OFF                             ( 3)
  #define DDRDATA5_CR_DLLDCMCTL_dccctl_WID                             ( 4)
  #define DDRDATA5_CR_DLLDCMCTL_dccctl_MSK                             (0x00000078)
  #define DDRDATA5_CR_DLLDCMCTL_dccctl_MIN                             (0)
  #define DDRDATA5_CR_DLLDCMCTL_dccctl_MAX                             (15) // 0x0000000F
  #define DDRDATA5_CR_DLLDCMCTL_dccctl_DEF                             (0x00000000)
  #define DDRDATA5_CR_DLLDCMCTL_dccctl_HSH                             (0x040322A4)

  #define DDRDATA5_CR_DLLDCMCTL_duration_OFF                           ( 7)
  #define DDRDATA5_CR_DLLDCMCTL_duration_WID                           ( 3)
  #define DDRDATA5_CR_DLLDCMCTL_duration_MSK                           (0x00000380)
  #define DDRDATA5_CR_DLLDCMCTL_duration_MIN                           (0)
  #define DDRDATA5_CR_DLLDCMCTL_duration_MAX                           (7) // 0x00000007
  #define DDRDATA5_CR_DLLDCMCTL_duration_DEF                           (0x00000000)
  #define DDRDATA5_CR_DLLDCMCTL_duration_HSH                           (0x030722A4)

  #define DDRDATA5_CR_DLLDCMCTL_dcm_done_OFF                           (10)
  #define DDRDATA5_CR_DLLDCMCTL_dcm_done_WID                           ( 1)
  #define DDRDATA5_CR_DLLDCMCTL_dcm_done_MSK                           (0x00000400)
  #define DDRDATA5_CR_DLLDCMCTL_dcm_done_MIN                           (0)
  #define DDRDATA5_CR_DLLDCMCTL_dcm_done_MAX                           (1) // 0x00000001
  #define DDRDATA5_CR_DLLDCMCTL_dcm_done_DEF                           (0x00000000)
  #define DDRDATA5_CR_DLLDCMCTL_dcm_done_HSH                           (0x010A22A4)

  #define DDRDATA5_CR_DLLDCMCTL_dcm_results_OFF                        (11)
  #define DDRDATA5_CR_DLLDCMCTL_dcm_results_WID                        (15)
  #define DDRDATA5_CR_DLLDCMCTL_dcm_results_MSK                        (0x03FFF800)
  #define DDRDATA5_CR_DLLDCMCTL_dcm_results_MIN                        (0)
  #define DDRDATA5_CR_DLLDCMCTL_dcm_results_MAX                        (32767) // 0x00007FFF
  #define DDRDATA5_CR_DLLDCMCTL_dcm_results_DEF                        (0x00000000)
  #define DDRDATA5_CR_DLLDCMCTL_dcm_results_HSH                        (0x0F0B22A4)

  #define DDRDATA5_CR_DLLDCMCTL_spare0_OFF                             (26)
  #define DDRDATA5_CR_DLLDCMCTL_spare0_WID                             ( 6)
  #define DDRDATA5_CR_DLLDCMCTL_spare0_MSK                             (0xFC000000)
  #define DDRDATA5_CR_DLLDCMCTL_spare0_MIN                             (0)
  #define DDRDATA5_CR_DLLDCMCTL_spare0_MAX                             (63) // 0x0000003F
  #define DDRDATA5_CR_DLLDCMCTL_spare0_DEF                             (0x00000000)
  #define DDRDATA5_CR_DLLDCMCTL_spare0_HSH                             (0x061A22A4)

#define DDRDATA6_CR_MASTERDLLCFG_REG                                   (0x00002300)

  #define DDRDATA6_CR_MASTERDLLCFG_LockThresh_OFF                      ( 0)
  #define DDRDATA6_CR_MASTERDLLCFG_LockThresh_WID                      ( 3)
  #define DDRDATA6_CR_MASTERDLLCFG_LockThresh_MSK                      (0x00000007)
  #define DDRDATA6_CR_MASTERDLLCFG_LockThresh_MIN                      (0)
  #define DDRDATA6_CR_MASTERDLLCFG_LockThresh_MAX                      (7) // 0x00000007
  #define DDRDATA6_CR_MASTERDLLCFG_LockThresh_DEF                      (0x00000004)
  #define DDRDATA6_CR_MASTERDLLCFG_LockThresh_HSH                      (0x03002300)

  #define DDRDATA6_CR_MASTERDLLCFG_LockCtr_OFF                         ( 3)
  #define DDRDATA6_CR_MASTERDLLCFG_LockCtr_WID                         ( 2)
  #define DDRDATA6_CR_MASTERDLLCFG_LockCtr_MSK                         (0x00000018)
  #define DDRDATA6_CR_MASTERDLLCFG_LockCtr_MIN                         (0)
  #define DDRDATA6_CR_MASTERDLLCFG_LockCtr_MAX                         (3) // 0x00000003
  #define DDRDATA6_CR_MASTERDLLCFG_LockCtr_DEF                         (0x00000000)
  #define DDRDATA6_CR_MASTERDLLCFG_LockCtr_HSH                         (0x02032300)

  #define DDRDATA6_CR_MASTERDLLCFG_VctrlDischRate_OFF                  ( 5)
  #define DDRDATA6_CR_MASTERDLLCFG_VctrlDischRate_WID                  ( 2)
  #define DDRDATA6_CR_MASTERDLLCFG_VctrlDischRate_MSK                  (0x00000060)
  #define DDRDATA6_CR_MASTERDLLCFG_VctrlDischRate_MIN                  (0)
  #define DDRDATA6_CR_MASTERDLLCFG_VctrlDischRate_MAX                  (3) // 0x00000003
  #define DDRDATA6_CR_MASTERDLLCFG_VctrlDischRate_DEF                  (0x00000000)
  #define DDRDATA6_CR_MASTERDLLCFG_VctrlDischRate_HSH                  (0x02052300)

  #define DDRDATA6_CR_MASTERDLLCFG_SelVctrlHi_OFF                      ( 7)
  #define DDRDATA6_CR_MASTERDLLCFG_SelVctrlHi_WID                      ( 1)
  #define DDRDATA6_CR_MASTERDLLCFG_SelVctrlHi_MSK                      (0x00000080)
  #define DDRDATA6_CR_MASTERDLLCFG_SelVctrlHi_MIN                      (0)
  #define DDRDATA6_CR_MASTERDLLCFG_SelVctrlHi_MAX                      (1) // 0x00000001
  #define DDRDATA6_CR_MASTERDLLCFG_SelVctrlHi_DEF                      (0x00000000)
  #define DDRDATA6_CR_MASTERDLLCFG_SelVctrlHi_HSH                      (0x01072300)

  #define DDRDATA6_CR_MASTERDLLCFG_StartupCntSel_OFF                   ( 8)
  #define DDRDATA6_CR_MASTERDLLCFG_StartupCntSel_WID                   ( 1)
  #define DDRDATA6_CR_MASTERDLLCFG_StartupCntSel_MSK                   (0x00000100)
  #define DDRDATA6_CR_MASTERDLLCFG_StartupCntSel_MIN                   (0)
  #define DDRDATA6_CR_MASTERDLLCFG_StartupCntSel_MAX                   (1) // 0x00000001
  #define DDRDATA6_CR_MASTERDLLCFG_StartupCntSel_DEF                   (0x00000000)
  #define DDRDATA6_CR_MASTERDLLCFG_StartupCntSel_HSH                   (0x01082300)

  #define DDRDATA6_CR_MASTERDLLCFG_LockSel_OFF                         ( 9)
  #define DDRDATA6_CR_MASTERDLLCFG_LockSel_WID                         ( 2)
  #define DDRDATA6_CR_MASTERDLLCFG_LockSel_MSK                         (0x00000600)
  #define DDRDATA6_CR_MASTERDLLCFG_LockSel_MIN                         (0)
  #define DDRDATA6_CR_MASTERDLLCFG_LockSel_MAX                         (3) // 0x00000003
  #define DDRDATA6_CR_MASTERDLLCFG_LockSel_DEF                         (0x00000000)
  #define DDRDATA6_CR_MASTERDLLCFG_LockSel_HSH                         (0x02092300)

  #define DDRDATA6_CR_MASTERDLLCFG_RstOvrd_OFF                         (11)
  #define DDRDATA6_CR_MASTERDLLCFG_RstOvrd_WID                         ( 1)
  #define DDRDATA6_CR_MASTERDLLCFG_RstOvrd_MSK                         (0x00000800)
  #define DDRDATA6_CR_MASTERDLLCFG_RstOvrd_MIN                         (0)
  #define DDRDATA6_CR_MASTERDLLCFG_RstOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA6_CR_MASTERDLLCFG_RstOvrd_DEF                         (0x00000000)
  #define DDRDATA6_CR_MASTERDLLCFG_RstOvrd_HSH                         (0x010B2300)

  #define DDRDATA6_CR_MASTERDLLCFG_SelRstOvrd_OFF                      (12)
  #define DDRDATA6_CR_MASTERDLLCFG_SelRstOvrd_WID                      ( 1)
  #define DDRDATA6_CR_MASTERDLLCFG_SelRstOvrd_MSK                      (0x00001000)
  #define DDRDATA6_CR_MASTERDLLCFG_SelRstOvrd_MIN                      (0)
  #define DDRDATA6_CR_MASTERDLLCFG_SelRstOvrd_MAX                      (1) // 0x00000001
  #define DDRDATA6_CR_MASTERDLLCFG_SelRstOvrd_DEF                      (0x00000000)
  #define DDRDATA6_CR_MASTERDLLCFG_SelRstOvrd_HSH                      (0x010C2300)

  #define DDRDATA6_CR_MASTERDLLCFG_TimeOutOvrd_OFF                     (13)
  #define DDRDATA6_CR_MASTERDLLCFG_TimeOutOvrd_WID                     ( 1)
  #define DDRDATA6_CR_MASTERDLLCFG_TimeOutOvrd_MSK                     (0x00002000)
  #define DDRDATA6_CR_MASTERDLLCFG_TimeOutOvrd_MIN                     (0)
  #define DDRDATA6_CR_MASTERDLLCFG_TimeOutOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA6_CR_MASTERDLLCFG_TimeOutOvrd_DEF                     (0x00000000)
  #define DDRDATA6_CR_MASTERDLLCFG_TimeOutOvrd_HSH                     (0x010D2300)

  #define DDRDATA6_CR_MASTERDLLCFG_SelTimeOutOvrd_OFF                  (14)
  #define DDRDATA6_CR_MASTERDLLCFG_SelTimeOutOvrd_WID                  ( 1)
  #define DDRDATA6_CR_MASTERDLLCFG_SelTimeOutOvrd_MSK                  (0x00004000)
  #define DDRDATA6_CR_MASTERDLLCFG_SelTimeOutOvrd_MIN                  (0)
  #define DDRDATA6_CR_MASTERDLLCFG_SelTimeOutOvrd_MAX                  (1) // 0x00000001
  #define DDRDATA6_CR_MASTERDLLCFG_SelTimeOutOvrd_DEF                  (0x00000000)
  #define DDRDATA6_CR_MASTERDLLCFG_SelTimeOutOvrd_HSH                  (0x010E2300)

  #define DDRDATA6_CR_MASTERDLLCFG_ClkGateOvrd_OFF                     (15)
  #define DDRDATA6_CR_MASTERDLLCFG_ClkGateOvrd_WID                     ( 1)
  #define DDRDATA6_CR_MASTERDLLCFG_ClkGateOvrd_MSK                     (0x00008000)
  #define DDRDATA6_CR_MASTERDLLCFG_ClkGateOvrd_MIN                     (0)
  #define DDRDATA6_CR_MASTERDLLCFG_ClkGateOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA6_CR_MASTERDLLCFG_ClkGateOvrd_DEF                     (0x00000000)
  #define DDRDATA6_CR_MASTERDLLCFG_ClkGateOvrd_HSH                     (0x010F2300)

  #define DDRDATA6_CR_MASTERDLLCFG_LockOvrd_OFF                        (16)
  #define DDRDATA6_CR_MASTERDLLCFG_LockOvrd_WID                        ( 1)
  #define DDRDATA6_CR_MASTERDLLCFG_LockOvrd_MSK                        (0x00010000)
  #define DDRDATA6_CR_MASTERDLLCFG_LockOvrd_MIN                        (0)
  #define DDRDATA6_CR_MASTERDLLCFG_LockOvrd_MAX                        (1) // 0x00000001
  #define DDRDATA6_CR_MASTERDLLCFG_LockOvrd_DEF                        (0x00000000)
  #define DDRDATA6_CR_MASTERDLLCFG_LockOvrd_HSH                        (0x01102300)

  #define DDRDATA6_CR_MASTERDLLCFG_SelLockOvrd_OFF                     (17)
  #define DDRDATA6_CR_MASTERDLLCFG_SelLockOvrd_WID                     ( 1)
  #define DDRDATA6_CR_MASTERDLLCFG_SelLockOvrd_MSK                     (0x00020000)
  #define DDRDATA6_CR_MASTERDLLCFG_SelLockOvrd_MIN                     (0)
  #define DDRDATA6_CR_MASTERDLLCFG_SelLockOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA6_CR_MASTERDLLCFG_SelLockOvrd_DEF                     (0x00000000)
  #define DDRDATA6_CR_MASTERDLLCFG_SelLockOvrd_HSH                     (0x01112300)

  #define DDRDATA6_CR_MASTERDLLCFG_OpenLoopOvrd_OFF                    (18)
  #define DDRDATA6_CR_MASTERDLLCFG_OpenLoopOvrd_WID                    ( 1)
  #define DDRDATA6_CR_MASTERDLLCFG_OpenLoopOvrd_MSK                    (0x00040000)
  #define DDRDATA6_CR_MASTERDLLCFG_OpenLoopOvrd_MIN                    (0)
  #define DDRDATA6_CR_MASTERDLLCFG_OpenLoopOvrd_MAX                    (1) // 0x00000001
  #define DDRDATA6_CR_MASTERDLLCFG_OpenLoopOvrd_DEF                    (0x00000000)
  #define DDRDATA6_CR_MASTERDLLCFG_OpenLoopOvrd_HSH                    (0x01122300)

  #define DDRDATA6_CR_MASTERDLLCFG_SelOpenLoopOvrd_OFF                 (19)
  #define DDRDATA6_CR_MASTERDLLCFG_SelOpenLoopOvrd_WID                 ( 1)
  #define DDRDATA6_CR_MASTERDLLCFG_SelOpenLoopOvrd_MSK                 (0x00080000)
  #define DDRDATA6_CR_MASTERDLLCFG_SelOpenLoopOvrd_MIN                 (0)
  #define DDRDATA6_CR_MASTERDLLCFG_SelOpenLoopOvrd_MAX                 (1) // 0x00000001
  #define DDRDATA6_CR_MASTERDLLCFG_SelOpenLoopOvrd_DEF                 (0x00000000)
  #define DDRDATA6_CR_MASTERDLLCFG_SelOpenLoopOvrd_HSH                 (0x01132300)

  #define DDRDATA6_CR_MASTERDLLCFG_WkLockEnOvrd_OFF                    (20)
  #define DDRDATA6_CR_MASTERDLLCFG_WkLockEnOvrd_WID                    ( 1)
  #define DDRDATA6_CR_MASTERDLLCFG_WkLockEnOvrd_MSK                    (0x00100000)
  #define DDRDATA6_CR_MASTERDLLCFG_WkLockEnOvrd_MIN                    (0)
  #define DDRDATA6_CR_MASTERDLLCFG_WkLockEnOvrd_MAX                    (1) // 0x00000001
  #define DDRDATA6_CR_MASTERDLLCFG_WkLockEnOvrd_DEF                    (0x00000000)
  #define DDRDATA6_CR_MASTERDLLCFG_WkLockEnOvrd_HSH                    (0x01142300)

  #define DDRDATA6_CR_MASTERDLLCFG_SelWkLockEnOvrd_OFF                 (21)
  #define DDRDATA6_CR_MASTERDLLCFG_SelWkLockEnOvrd_WID                 ( 1)
  #define DDRDATA6_CR_MASTERDLLCFG_SelWkLockEnOvrd_MSK                 (0x00200000)
  #define DDRDATA6_CR_MASTERDLLCFG_SelWkLockEnOvrd_MIN                 (0)
  #define DDRDATA6_CR_MASTERDLLCFG_SelWkLockEnOvrd_MAX                 (1) // 0x00000001
  #define DDRDATA6_CR_MASTERDLLCFG_SelWkLockEnOvrd_DEF                 (0x00000000)
  #define DDRDATA6_CR_MASTERDLLCFG_SelWkLockEnOvrd_HSH                 (0x01152300)

  #define DDRDATA6_CR_MASTERDLLCFG_CfdlDis_OFF                         (22)
  #define DDRDATA6_CR_MASTERDLLCFG_CfdlDis_WID                         ( 1)
  #define DDRDATA6_CR_MASTERDLLCFG_CfdlDis_MSK                         (0x00400000)
  #define DDRDATA6_CR_MASTERDLLCFG_CfdlDis_MIN                         (0)
  #define DDRDATA6_CR_MASTERDLLCFG_CfdlDis_MAX                         (1) // 0x00000001
  #define DDRDATA6_CR_MASTERDLLCFG_CfdlDis_DEF                         (0x00000000)
  #define DDRDATA6_CR_MASTERDLLCFG_CfdlDis_HSH                         (0x01162300)

  #define DDRDATA6_CR_MASTERDLLCFG_DftEn_OFF                           (23)
  #define DDRDATA6_CR_MASTERDLLCFG_DftEn_WID                           ( 1)
  #define DDRDATA6_CR_MASTERDLLCFG_DftEn_MSK                           (0x00800000)
  #define DDRDATA6_CR_MASTERDLLCFG_DftEn_MIN                           (0)
  #define DDRDATA6_CR_MASTERDLLCFG_DftEn_MAX                           (1) // 0x00000001
  #define DDRDATA6_CR_MASTERDLLCFG_DftEn_DEF                           (0x00000000)
  #define DDRDATA6_CR_MASTERDLLCFG_DftEn_HSH                           (0x01172300)

  #define DDRDATA6_CR_MASTERDLLCFG_spare0_OFF                          (24)
  #define DDRDATA6_CR_MASTERDLLCFG_spare0_WID                          ( 8)
  #define DDRDATA6_CR_MASTERDLLCFG_spare0_MSK                          (0xFF000000)
  #define DDRDATA6_CR_MASTERDLLCFG_spare0_MIN                          (0)
  #define DDRDATA6_CR_MASTERDLLCFG_spare0_MAX                          (255) // 0x000000FF
  #define DDRDATA6_CR_MASTERDLLCFG_spare0_DEF                          (0x00000000)
  #define DDRDATA6_CR_MASTERDLLCFG_spare0_HSH                          (0x08182300)

#define DDRDATA6_CR_CBTUNE0_REG                                        (0x00002304)

  #define DDRDATA6_CR_CBTUNE0_DllBWEn_OFF                              ( 0)
  #define DDRDATA6_CR_CBTUNE0_DllBWEn_WID                              (32)
  #define DDRDATA6_CR_CBTUNE0_DllBWEn_MSK                              (0xFFFFFFFF)
  #define DDRDATA6_CR_CBTUNE0_DllBWEn_MIN                              (0)
  #define DDRDATA6_CR_CBTUNE0_DllBWEn_MAX                              (4294967295) // 0xFFFFFFFF
  #define DDRDATA6_CR_CBTUNE0_DllBWEn_DEF                              (0xFDB86521)
  #define DDRDATA6_CR_CBTUNE0_DllBWEn_HSH                              (0x20002304)

#define DDRDATA6_CR_CBTUNE1_REG                                        (0x00002308)

  #define DDRDATA6_CR_CBTUNE1_PiCbEn_OFF                               ( 0)
  #define DDRDATA6_CR_CBTUNE1_PiCbEn_WID                               (24)
  #define DDRDATA6_CR_CBTUNE1_PiCbEn_MSK                               (0x00FFFFFF)
  #define DDRDATA6_CR_CBTUNE1_PiCbEn_MIN                               (0)
  #define DDRDATA6_CR_CBTUNE1_PiCbEn_MAX                               (16777215) // 0x00FFFFFF
  #define DDRDATA6_CR_CBTUNE1_PiCbEn_DEF                               (0x00249492)
  #define DDRDATA6_CR_CBTUNE1_PiCbEn_HSH                               (0x18002308)

  #define DDRDATA6_CR_CBTUNE1_CbEnRsvd_OFF                             (24)
  #define DDRDATA6_CR_CBTUNE1_CbEnRsvd_WID                             ( 3)
  #define DDRDATA6_CR_CBTUNE1_CbEnRsvd_MSK                             (0x07000000)
  #define DDRDATA6_CR_CBTUNE1_CbEnRsvd_MIN                             (0)
  #define DDRDATA6_CR_CBTUNE1_CbEnRsvd_MAX                             (7) // 0x00000007
  #define DDRDATA6_CR_CBTUNE1_CbEnRsvd_DEF                             (0x00000000)
  #define DDRDATA6_CR_CBTUNE1_CbEnRsvd_HSH                             (0x03182308)

  #define DDRDATA6_CR_CBTUNE1_CbEnDllFuse_OFF                          (27)
  #define DDRDATA6_CR_CBTUNE1_CbEnDllFuse_WID                          ( 3)
  #define DDRDATA6_CR_CBTUNE1_CbEnDllFuse_MSK                          (0x38000000)
  #define DDRDATA6_CR_CBTUNE1_CbEnDllFuse_MIN                          (0)
  #define DDRDATA6_CR_CBTUNE1_CbEnDllFuse_MAX                          (7) // 0x00000007
  #define DDRDATA6_CR_CBTUNE1_CbEnDllFuse_DEF                          (0x00000002)
  #define DDRDATA6_CR_CBTUNE1_CbEnDllFuse_HSH                          (0x031B2308)

  #define DDRDATA6_CR_CBTUNE1_Spare_OFF                                (30)
  #define DDRDATA6_CR_CBTUNE1_Spare_WID                                ( 2)
  #define DDRDATA6_CR_CBTUNE1_Spare_MSK                                (0xC0000000)
  #define DDRDATA6_CR_CBTUNE1_Spare_MIN                                (0)
  #define DDRDATA6_CR_CBTUNE1_Spare_MAX                                (3) // 0x00000003
  #define DDRDATA6_CR_CBTUNE1_Spare_DEF                                (0x00000000)
  #define DDRDATA6_CR_CBTUNE1_Spare_HSH                                (0x021E2308)

#define DDRDATA6_CR_ADCCFG_REG                                         (0x0000230C)

  #define DDRDATA6_CR_ADCCFG_ADC_frz_OFF                               ( 0)
  #define DDRDATA6_CR_ADCCFG_ADC_frz_WID                               ( 1)
  #define DDRDATA6_CR_ADCCFG_ADC_frz_MSK                               (0x00000001)
  #define DDRDATA6_CR_ADCCFG_ADC_frz_MIN                               (0)
  #define DDRDATA6_CR_ADCCFG_ADC_frz_MAX                               (1) // 0x00000001
  #define DDRDATA6_CR_ADCCFG_ADC_frz_DEF                               (0x00000000)
  #define DDRDATA6_CR_ADCCFG_ADC_frz_HSH                               (0x0100230C)

  #define DDRDATA6_CR_ADCCFG_ADC_en_OFF                                ( 1)
  #define DDRDATA6_CR_ADCCFG_ADC_en_WID                                ( 1)
  #define DDRDATA6_CR_ADCCFG_ADC_en_MSK                                (0x00000002)
  #define DDRDATA6_CR_ADCCFG_ADC_en_MIN                                (0)
  #define DDRDATA6_CR_ADCCFG_ADC_en_MAX                                (1) // 0x00000001
  #define DDRDATA6_CR_ADCCFG_ADC_en_DEF                                (0x00000000)
  #define DDRDATA6_CR_ADCCFG_ADC_en_HSH                                (0x0101230C)

  #define DDRDATA6_CR_ADCCFG_ADCclkdiv_OFF                             ( 2)
  #define DDRDATA6_CR_ADCCFG_ADCclkdiv_WID                             ( 2)
  #define DDRDATA6_CR_ADCCFG_ADCclkdiv_MSK                             (0x0000000C)
  #define DDRDATA6_CR_ADCCFG_ADCclkdiv_MIN                             (0)
  #define DDRDATA6_CR_ADCCFG_ADCclkdiv_MAX                             (3) // 0x00000003
  #define DDRDATA6_CR_ADCCFG_ADCclkdiv_DEF                             (0x00000000)
  #define DDRDATA6_CR_ADCCFG_ADCclkdiv_HSH                             (0x0202230C)

  #define DDRDATA6_CR_ADCCFG_ADCstartcount_OFF                         ( 4)
  #define DDRDATA6_CR_ADCCFG_ADCstartcount_WID                         ( 2)
  #define DDRDATA6_CR_ADCCFG_ADCstartcount_MSK                         (0x00000030)
  #define DDRDATA6_CR_ADCCFG_ADCstartcount_MIN                         (0)
  #define DDRDATA6_CR_ADCCFG_ADCstartcount_MAX                         (3) // 0x00000003
  #define DDRDATA6_CR_ADCCFG_ADCstartcount_DEF                         (0x00000000)
  #define DDRDATA6_CR_ADCCFG_ADCstartcount_HSH                         (0x0204230C)

  #define DDRDATA6_CR_ADCCFG_ADCChopEn_OFF                             ( 6)
  #define DDRDATA6_CR_ADCCFG_ADCChopEn_WID                             ( 1)
  #define DDRDATA6_CR_ADCCFG_ADCChopEn_MSK                             (0x00000040)
  #define DDRDATA6_CR_ADCCFG_ADCChopEn_MIN                             (0)
  #define DDRDATA6_CR_ADCCFG_ADCChopEn_MAX                             (1) // 0x00000001
  #define DDRDATA6_CR_ADCCFG_ADCChopEn_DEF                             (0x00000000)
  #define DDRDATA6_CR_ADCCFG_ADCChopEn_HSH                             (0x0106230C)

  #define DDRDATA6_CR_ADCCFG_Spare_OFF                                 ( 7)
  #define DDRDATA6_CR_ADCCFG_Spare_WID                                 (25)
  #define DDRDATA6_CR_ADCCFG_Spare_MSK                                 (0xFFFFFF80)
  #define DDRDATA6_CR_ADCCFG_Spare_MIN                                 (0)
  #define DDRDATA6_CR_ADCCFG_Spare_MAX                                 (33554431) // 0x01FFFFFF
  #define DDRDATA6_CR_ADCCFG_Spare_DEF                                 (0x00000000)
  #define DDRDATA6_CR_ADCCFG_Spare_HSH                                 (0x1907230C)

#define DDRDATA6_CR_CBTUNE2_REG                                        (0x00002310)

  #define DDRDATA6_CR_CBTUNE2_DllCbEn_OFF                              ( 0)
  #define DDRDATA6_CR_CBTUNE2_DllCbEn_WID                              (16)
  #define DDRDATA6_CR_CBTUNE2_DllCbEn_MSK                              (0x0000FFFF)
  #define DDRDATA6_CR_CBTUNE2_DllCbEn_MIN                              (0)
  #define DDRDATA6_CR_CBTUNE2_DllCbEn_MAX                              (65535) // 0x0000FFFF
  #define DDRDATA6_CR_CBTUNE2_DllCbEn_DEF                              (0x00000000)
  #define DDRDATA6_CR_CBTUNE2_DllCbEn_HSH                              (0x10002310)

  #define DDRDATA6_CR_CBTUNE2_Spare_OFF                                (16)
  #define DDRDATA6_CR_CBTUNE2_Spare_WID                                (16)
  #define DDRDATA6_CR_CBTUNE2_Spare_MSK                                (0xFFFF0000)
  #define DDRDATA6_CR_CBTUNE2_Spare_MIN                                (0)
  #define DDRDATA6_CR_CBTUNE2_Spare_MAX                                (65535) // 0x0000FFFF
  #define DDRDATA6_CR_CBTUNE2_Spare_DEF                                (0x00000000)
  #define DDRDATA6_CR_CBTUNE2_Spare_HSH                                (0x10102310)

#define DDRDATA6_CR_PIDFTDLY_REG                                       (0x00002318)

  #define DDRDATA6_CR_PIDFTDLY_PiDftDelay_OFF                          ( 0)
  #define DDRDATA6_CR_PIDFTDLY_PiDftDelay_WID                          ( 7)
  #define DDRDATA6_CR_PIDFTDLY_PiDftDelay_MSK                          (0x0000007F)
  #define DDRDATA6_CR_PIDFTDLY_PiDftDelay_MIN                          (0)
  #define DDRDATA6_CR_PIDFTDLY_PiDftDelay_MAX                          (127) // 0x0000007F
  #define DDRDATA6_CR_PIDFTDLY_PiDftDelay_DEF                          (0x00000000)
  #define DDRDATA6_CR_PIDFTDLY_PiDftDelay_HSH                          (0x07002318)

  #define DDRDATA6_CR_PIDFTDLY_Ch0PiEnOvrd_OFF                         ( 7)
  #define DDRDATA6_CR_PIDFTDLY_Ch0PiEnOvrd_WID                         ( 1)
  #define DDRDATA6_CR_PIDFTDLY_Ch0PiEnOvrd_MSK                         (0x00000080)
  #define DDRDATA6_CR_PIDFTDLY_Ch0PiEnOvrd_MIN                         (0)
  #define DDRDATA6_CR_PIDFTDLY_Ch0PiEnOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA6_CR_PIDFTDLY_Ch0PiEnOvrd_DEF                         (0x00000000)
  #define DDRDATA6_CR_PIDFTDLY_Ch0PiEnOvrd_HSH                         (0x01072318)

  #define DDRDATA6_CR_PIDFTDLY_Ch1PiEnOvrd_OFF                         ( 8)
  #define DDRDATA6_CR_PIDFTDLY_Ch1PiEnOvrd_WID                         ( 1)
  #define DDRDATA6_CR_PIDFTDLY_Ch1PiEnOvrd_MSK                         (0x00000100)
  #define DDRDATA6_CR_PIDFTDLY_Ch1PiEnOvrd_MIN                         (0)
  #define DDRDATA6_CR_PIDFTDLY_Ch1PiEnOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA6_CR_PIDFTDLY_Ch1PiEnOvrd_DEF                         (0x00000000)
  #define DDRDATA6_CR_PIDFTDLY_Ch1PiEnOvrd_HSH                         (0x01082318)

  #define DDRDATA6_CR_PIDFTDLY_Ch0PiDFTEn_OFF                          ( 9)
  #define DDRDATA6_CR_PIDFTDLY_Ch0PiDFTEn_WID                          ( 1)
  #define DDRDATA6_CR_PIDFTDLY_Ch0PiDFTEn_MSK                          (0x00000200)
  #define DDRDATA6_CR_PIDFTDLY_Ch0PiDFTEn_MIN                          (0)
  #define DDRDATA6_CR_PIDFTDLY_Ch0PiDFTEn_MAX                          (1) // 0x00000001
  #define DDRDATA6_CR_PIDFTDLY_Ch0PiDFTEn_DEF                          (0x00000000)
  #define DDRDATA6_CR_PIDFTDLY_Ch0PiDFTEn_HSH                          (0x01092318)

  #define DDRDATA6_CR_PIDFTDLY_Ch1PiDFTEn_OFF                          (10)
  #define DDRDATA6_CR_PIDFTDLY_Ch1PiDFTEn_WID                          ( 1)
  #define DDRDATA6_CR_PIDFTDLY_Ch1PiDFTEn_MSK                          (0x00000400)
  #define DDRDATA6_CR_PIDFTDLY_Ch1PiDFTEn_MIN                          (0)
  #define DDRDATA6_CR_PIDFTDLY_Ch1PiDFTEn_MAX                          (1) // 0x00000001
  #define DDRDATA6_CR_PIDFTDLY_Ch1PiDFTEn_DEF                          (0x00000000)
  #define DDRDATA6_CR_PIDFTDLY_Ch1PiDFTEn_HSH                          (0x010A2318)

  #define DDRDATA6_CR_PIDFTDLY_Spare_OFF                               (11)
  #define DDRDATA6_CR_PIDFTDLY_Spare_WID                               ( 4)
  #define DDRDATA6_CR_PIDFTDLY_Spare_MSK                               (0x00007800)
  #define DDRDATA6_CR_PIDFTDLY_Spare_MIN                               (0)
  #define DDRDATA6_CR_PIDFTDLY_Spare_MAX                               (15) // 0x0000000F
  #define DDRDATA6_CR_PIDFTDLY_Spare_DEF                               (0x00000000)
  #define DDRDATA6_CR_PIDFTDLY_Spare_HSH                               (0x040B2318)

  #define DDRDATA6_CR_PIDFTDLY_RefPiOvrd_OFF                           (15)
  #define DDRDATA6_CR_PIDFTDLY_RefPiOvrd_WID                           ( 1)
  #define DDRDATA6_CR_PIDFTDLY_RefPiOvrd_MSK                           (0x00008000)
  #define DDRDATA6_CR_PIDFTDLY_RefPiOvrd_MIN                           (0)
  #define DDRDATA6_CR_PIDFTDLY_RefPiOvrd_MAX                           (1) // 0x00000001
  #define DDRDATA6_CR_PIDFTDLY_RefPiOvrd_DEF                           (0x00000000)
  #define DDRDATA6_CR_PIDFTDLY_RefPiOvrd_HSH                           (0x010F2318)

  #define DDRDATA6_CR_PIDFTDLY_Rsvd_OFF                                (16)
  #define DDRDATA6_CR_PIDFTDLY_Rsvd_WID                                (16)
  #define DDRDATA6_CR_PIDFTDLY_Rsvd_MSK                                (0xFFFF0000)
  #define DDRDATA6_CR_PIDFTDLY_Rsvd_MIN                                (0)
  #define DDRDATA6_CR_PIDFTDLY_Rsvd_MAX                                (65535) // 0x0000FFFF
  #define DDRDATA6_CR_PIDFTDLY_Rsvd_DEF                                (0x00000000)
  #define DDRDATA6_CR_PIDFTDLY_Rsvd_HSH                                (0x10102318)

#define DDRDATA6_CR_DLLPITESTANDADC_REG                                (0x0000231C)

  #define DDRDATA6_CR_DLLPITESTANDADC_RunTest_OFF                      ( 0)
  #define DDRDATA6_CR_DLLPITESTANDADC_RunTest_WID                      ( 1)
  #define DDRDATA6_CR_DLLPITESTANDADC_RunTest_MSK                      (0x00000001)
  #define DDRDATA6_CR_DLLPITESTANDADC_RunTest_MIN                      (0)
  #define DDRDATA6_CR_DLLPITESTANDADC_RunTest_MAX                      (1) // 0x00000001
  #define DDRDATA6_CR_DLLPITESTANDADC_RunTest_DEF                      (0x00000000)
  #define DDRDATA6_CR_DLLPITESTANDADC_RunTest_HSH                      (0x0100231C)

  #define DDRDATA6_CR_DLLPITESTANDADC_Load_OFF                         ( 1)
  #define DDRDATA6_CR_DLLPITESTANDADC_Load_WID                         ( 1)
  #define DDRDATA6_CR_DLLPITESTANDADC_Load_MSK                         (0x00000002)
  #define DDRDATA6_CR_DLLPITESTANDADC_Load_MIN                         (0)
  #define DDRDATA6_CR_DLLPITESTANDADC_Load_MAX                         (1) // 0x00000001
  #define DDRDATA6_CR_DLLPITESTANDADC_Load_DEF                         (0x00000000)
  #define DDRDATA6_CR_DLLPITESTANDADC_Load_HSH                         (0x0101231C)

  #define DDRDATA6_CR_DLLPITESTANDADC_ModeHVM_OFF                      ( 2)
  #define DDRDATA6_CR_DLLPITESTANDADC_ModeHVM_WID                      ( 1)
  #define DDRDATA6_CR_DLLPITESTANDADC_ModeHVM_MSK                      (0x00000004)
  #define DDRDATA6_CR_DLLPITESTANDADC_ModeHVM_MIN                      (0)
  #define DDRDATA6_CR_DLLPITESTANDADC_ModeHVM_MAX                      (1) // 0x00000001
  #define DDRDATA6_CR_DLLPITESTANDADC_ModeHVM_DEF                      (0x00000000)
  #define DDRDATA6_CR_DLLPITESTANDADC_ModeHVM_HSH                      (0x0102231C)

  #define DDRDATA6_CR_DLLPITESTANDADC_ModeDV_OFF                       ( 3)
  #define DDRDATA6_CR_DLLPITESTANDADC_ModeDV_WID                       ( 1)
  #define DDRDATA6_CR_DLLPITESTANDADC_ModeDV_MSK                       (0x00000008)
  #define DDRDATA6_CR_DLLPITESTANDADC_ModeDV_MIN                       (0)
  #define DDRDATA6_CR_DLLPITESTANDADC_ModeDV_MAX                       (1) // 0x00000001
  #define DDRDATA6_CR_DLLPITESTANDADC_ModeDV_DEF                       (0x00000000)
  #define DDRDATA6_CR_DLLPITESTANDADC_ModeDV_HSH                       (0x0103231C)

  #define DDRDATA6_CR_DLLPITESTANDADC_CalCfdl_OFF                      ( 4)
  #define DDRDATA6_CR_DLLPITESTANDADC_CalCfdl_WID                      ( 1)
  #define DDRDATA6_CR_DLLPITESTANDADC_CalCfdl_MSK                      (0x00000010)
  #define DDRDATA6_CR_DLLPITESTANDADC_CalCfdl_MIN                      (0)
  #define DDRDATA6_CR_DLLPITESTANDADC_CalCfdl_MAX                      (1) // 0x00000001
  #define DDRDATA6_CR_DLLPITESTANDADC_CalCfdl_DEF                      (0x00000000)
  #define DDRDATA6_CR_DLLPITESTANDADC_CalCfdl_HSH                      (0x0104231C)

  #define DDRDATA6_CR_DLLPITESTANDADC_LoadCount_OFF                    ( 5)
  #define DDRDATA6_CR_DLLPITESTANDADC_LoadCount_WID                    (10)
  #define DDRDATA6_CR_DLLPITESTANDADC_LoadCount_MSK                    (0x00007FE0)
  #define DDRDATA6_CR_DLLPITESTANDADC_LoadCount_MIN                    (0)
  #define DDRDATA6_CR_DLLPITESTANDADC_LoadCount_MAX                    (1023) // 0x000003FF
  #define DDRDATA6_CR_DLLPITESTANDADC_LoadCount_DEF                    (0x00000000)
  #define DDRDATA6_CR_DLLPITESTANDADC_LoadCount_HSH                    (0x0A05231C)

  #define DDRDATA6_CR_DLLPITESTANDADC_CountStatus_OFF                  (15)
  #define DDRDATA6_CR_DLLPITESTANDADC_CountStatus_WID                  (10)
  #define DDRDATA6_CR_DLLPITESTANDADC_CountStatus_MSK                  (0x01FF8000)
  #define DDRDATA6_CR_DLLPITESTANDADC_CountStatus_MIN                  (0)
  #define DDRDATA6_CR_DLLPITESTANDADC_CountStatus_MAX                  (1023) // 0x000003FF
  #define DDRDATA6_CR_DLLPITESTANDADC_CountStatus_DEF                  (0x00000000)
  #define DDRDATA6_CR_DLLPITESTANDADC_CountStatus_HSH                  (0x0A0F231C)

  #define DDRDATA6_CR_DLLPITESTANDADC_ModeADC_OFF                      (25)
  #define DDRDATA6_CR_DLLPITESTANDADC_ModeADC_WID                      ( 1)
  #define DDRDATA6_CR_DLLPITESTANDADC_ModeADC_MSK                      (0x02000000)
  #define DDRDATA6_CR_DLLPITESTANDADC_ModeADC_MIN                      (0)
  #define DDRDATA6_CR_DLLPITESTANDADC_ModeADC_MAX                      (1) // 0x00000001
  #define DDRDATA6_CR_DLLPITESTANDADC_ModeADC_DEF                      (0x00000000)
  #define DDRDATA6_CR_DLLPITESTANDADC_ModeADC_HSH                      (0x0119231C)

  #define DDRDATA6_CR_DLLPITESTANDADC_ADCClkDiv_OFF                    (26)
  #define DDRDATA6_CR_DLLPITESTANDADC_ADCClkDiv_WID                    ( 2)
  #define DDRDATA6_CR_DLLPITESTANDADC_ADCClkDiv_MSK                    (0x0C000000)
  #define DDRDATA6_CR_DLLPITESTANDADC_ADCClkDiv_MIN                    (0)
  #define DDRDATA6_CR_DLLPITESTANDADC_ADCClkDiv_MAX                    (3) // 0x00000003
  #define DDRDATA6_CR_DLLPITESTANDADC_ADCClkDiv_DEF                    (0x00000000)
  #define DDRDATA6_CR_DLLPITESTANDADC_ADCClkDiv_HSH                    (0x021A231C)

  #define DDRDATA6_CR_DLLPITESTANDADC_ADCDdrChanSel_OFF                (28)
  #define DDRDATA6_CR_DLLPITESTANDADC_ADCDdrChanSel_WID                ( 1)
  #define DDRDATA6_CR_DLLPITESTANDADC_ADCDdrChanSel_MSK                (0x10000000)
  #define DDRDATA6_CR_DLLPITESTANDADC_ADCDdrChanSel_MIN                (0)
  #define DDRDATA6_CR_DLLPITESTANDADC_ADCDdrChanSel_MAX                (1) // 0x00000001
  #define DDRDATA6_CR_DLLPITESTANDADC_ADCDdrChanSel_DEF                (0x00000000)
  #define DDRDATA6_CR_DLLPITESTANDADC_ADCDdrChanSel_HSH                (0x011C231C)

  #define DDRDATA6_CR_DLLPITESTANDADC_ADCChopEn_OFF                    (29)
  #define DDRDATA6_CR_DLLPITESTANDADC_ADCChopEn_WID                    ( 1)
  #define DDRDATA6_CR_DLLPITESTANDADC_ADCChopEn_MSK                    (0x20000000)
  #define DDRDATA6_CR_DLLPITESTANDADC_ADCChopEn_MIN                    (0)
  #define DDRDATA6_CR_DLLPITESTANDADC_ADCChopEn_MAX                    (1) // 0x00000001
  #define DDRDATA6_CR_DLLPITESTANDADC_ADCChopEn_DEF                    (0x00000000)
  #define DDRDATA6_CR_DLLPITESTANDADC_ADCChopEn_HSH                    (0x011D231C)

  #define DDRDATA6_CR_DLLPITESTANDADC_ADCDone_OFF                      (30)
  #define DDRDATA6_CR_DLLPITESTANDADC_ADCDone_WID                      ( 1)
  #define DDRDATA6_CR_DLLPITESTANDADC_ADCDone_MSK                      (0x40000000)
  #define DDRDATA6_CR_DLLPITESTANDADC_ADCDone_MIN                      (0)
  #define DDRDATA6_CR_DLLPITESTANDADC_ADCDone_MAX                      (1) // 0x00000001
  #define DDRDATA6_CR_DLLPITESTANDADC_ADCDone_DEF                      (0x00000000)
  #define DDRDATA6_CR_DLLPITESTANDADC_ADCDone_HSH                      (0x011E231C)

  #define DDRDATA6_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF             (31)
  #define DDRDATA6_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID             ( 1)
  #define DDRDATA6_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK             (0x80000000)
  #define DDRDATA6_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN             (0)
  #define DDRDATA6_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX             (1) // 0x00000001
  #define DDRDATA6_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF             (0x00000000)
  #define DDRDATA6_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH             (0x011F231C)

#define DDRDATA6_CR_DLLSTATUS_REG                                      (0x00002320)

  #define DDRDATA6_CR_DLLSTATUS_DetrmLockStat_OFF                      ( 0)
  #define DDRDATA6_CR_DLLSTATUS_DetrmLockStat_WID                      ( 1)
  #define DDRDATA6_CR_DLLSTATUS_DetrmLockStat_MSK                      (0x00000001)
  #define DDRDATA6_CR_DLLSTATUS_DetrmLockStat_MIN                      (0)
  #define DDRDATA6_CR_DLLSTATUS_DetrmLockStat_MAX                      (1) // 0x00000001
  #define DDRDATA6_CR_DLLSTATUS_DetrmLockStat_DEF                      (0x00000000)
  #define DDRDATA6_CR_DLLSTATUS_DetrmLockStat_HSH                      (0x01002320)

  #define DDRDATA6_CR_DLLSTATUS_FuncLockStat_OFF                       ( 1)
  #define DDRDATA6_CR_DLLSTATUS_FuncLockStat_WID                       ( 1)
  #define DDRDATA6_CR_DLLSTATUS_FuncLockStat_MSK                       (0x00000002)
  #define DDRDATA6_CR_DLLSTATUS_FuncLockStat_MIN                       (0)
  #define DDRDATA6_CR_DLLSTATUS_FuncLockStat_MAX                       (1) // 0x00000001
  #define DDRDATA6_CR_DLLSTATUS_FuncLockStat_DEF                       (0x00000000)
  #define DDRDATA6_CR_DLLSTATUS_FuncLockStat_HSH                       (0x01012320)

  #define DDRDATA6_CR_DLLSTATUS_Lock_OFF                               ( 2)
  #define DDRDATA6_CR_DLLSTATUS_Lock_WID                               ( 1)
  #define DDRDATA6_CR_DLLSTATUS_Lock_MSK                               (0x00000004)
  #define DDRDATA6_CR_DLLSTATUS_Lock_MIN                               (0)
  #define DDRDATA6_CR_DLLSTATUS_Lock_MAX                               (1) // 0x00000001
  #define DDRDATA6_CR_DLLSTATUS_Lock_DEF                               (0x00000000)
  #define DDRDATA6_CR_DLLSTATUS_Lock_HSH                               (0x01022320)

  #define DDRDATA6_CR_DLLSTATUS_Timeout_OFF                            ( 3)
  #define DDRDATA6_CR_DLLSTATUS_Timeout_WID                            ( 1)
  #define DDRDATA6_CR_DLLSTATUS_Timeout_MSK                            (0x00000008)
  #define DDRDATA6_CR_DLLSTATUS_Timeout_MIN                            (0)
  #define DDRDATA6_CR_DLLSTATUS_Timeout_MAX                            (1) // 0x00000001
  #define DDRDATA6_CR_DLLSTATUS_Timeout_DEF                            (0x00000000)
  #define DDRDATA6_CR_DLLSTATUS_Timeout_HSH                            (0x01032320)

  #define DDRDATA6_CR_DLLSTATUS_DllReset_OFF                           ( 4)
  #define DDRDATA6_CR_DLLSTATUS_DllReset_WID                           ( 1)
  #define DDRDATA6_CR_DLLSTATUS_DllReset_MSK                           (0x00000010)
  #define DDRDATA6_CR_DLLSTATUS_DllReset_MIN                           (0)
  #define DDRDATA6_CR_DLLSTATUS_DllReset_MAX                           (1) // 0x00000001
  #define DDRDATA6_CR_DLLSTATUS_DllReset_DEF                           (0x00000000)
  #define DDRDATA6_CR_DLLSTATUS_DllReset_HSH                           (0x01042320)

  #define DDRDATA6_CR_DLLSTATUS_LongLockStat_OFF                       ( 5)
  #define DDRDATA6_CR_DLLSTATUS_LongLockStat_WID                       ( 1)
  #define DDRDATA6_CR_DLLSTATUS_LongLockStat_MSK                       (0x00000020)
  #define DDRDATA6_CR_DLLSTATUS_LongLockStat_MIN                       (0)
  #define DDRDATA6_CR_DLLSTATUS_LongLockStat_MAX                       (1) // 0x00000001
  #define DDRDATA6_CR_DLLSTATUS_LongLockStat_DEF                       (0x00000000)
  #define DDRDATA6_CR_DLLSTATUS_LongLockStat_HSH                       (0x01052320)

  #define DDRDATA6_CR_DLLSTATUS_EarlyLockStat_OFF                      ( 6)
  #define DDRDATA6_CR_DLLSTATUS_EarlyLockStat_WID                      ( 1)
  #define DDRDATA6_CR_DLLSTATUS_EarlyLockStat_MSK                      (0x00000040)
  #define DDRDATA6_CR_DLLSTATUS_EarlyLockStat_MIN                      (0)
  #define DDRDATA6_CR_DLLSTATUS_EarlyLockStat_MAX                      (1) // 0x00000001
  #define DDRDATA6_CR_DLLSTATUS_EarlyLockStat_DEF                      (0x00000000)
  #define DDRDATA6_CR_DLLSTATUS_EarlyLockStat_HSH                      (0x01062320)

  #define DDRDATA6_CR_DLLSTATUS_NormalMode_NotWkLock_OFF               ( 7)
  #define DDRDATA6_CR_DLLSTATUS_NormalMode_NotWkLock_WID               ( 1)
  #define DDRDATA6_CR_DLLSTATUS_NormalMode_NotWkLock_MSK               (0x00000080)
  #define DDRDATA6_CR_DLLSTATUS_NormalMode_NotWkLock_MIN               (0)
  #define DDRDATA6_CR_DLLSTATUS_NormalMode_NotWkLock_MAX               (1) // 0x00000001
  #define DDRDATA6_CR_DLLSTATUS_NormalMode_NotWkLock_DEF               (0x00000000)
  #define DDRDATA6_CR_DLLSTATUS_NormalMode_NotWkLock_HSH               (0x01072320)

  #define DDRDATA6_CR_DLLSTATUS_ADCout_OFF                             ( 8)
  #define DDRDATA6_CR_DLLSTATUS_ADCout_WID                             (10)
  #define DDRDATA6_CR_DLLSTATUS_ADCout_MSK                             (0x0003FF00)
  #define DDRDATA6_CR_DLLSTATUS_ADCout_MIN                             (0)
  #define DDRDATA6_CR_DLLSTATUS_ADCout_MAX                             (1023) // 0x000003FF
  #define DDRDATA6_CR_DLLSTATUS_ADCout_DEF                             (0x00000000)
  #define DDRDATA6_CR_DLLSTATUS_ADCout_HSH                             (0x0A082320)

  #define DDRDATA6_CR_DLLSTATUS_ADCStatus_OFF                          (18)
  #define DDRDATA6_CR_DLLSTATUS_ADCStatus_WID                          ( 1)
  #define DDRDATA6_CR_DLLSTATUS_ADCStatus_MSK                          (0x00040000)
  #define DDRDATA6_CR_DLLSTATUS_ADCStatus_MIN                          (0)
  #define DDRDATA6_CR_DLLSTATUS_ADCStatus_MAX                          (1) // 0x00000001
  #define DDRDATA6_CR_DLLSTATUS_ADCStatus_DEF                          (0x00000000)
  #define DDRDATA6_CR_DLLSTATUS_ADCStatus_HSH                          (0x01122320)

  #define DDRDATA6_CR_DLLSTATUS_pilags_OFF                             (19)
  #define DDRDATA6_CR_DLLSTATUS_pilags_WID                             ( 1)
  #define DDRDATA6_CR_DLLSTATUS_pilags_MSK                             (0x00080000)
  #define DDRDATA6_CR_DLLSTATUS_pilags_MIN                             (0)
  #define DDRDATA6_CR_DLLSTATUS_pilags_MAX                             (1) // 0x00000001
  #define DDRDATA6_CR_DLLSTATUS_pilags_DEF                             (0x00000000)
  #define DDRDATA6_CR_DLLSTATUS_pilags_HSH                             (0x01132320)

  #define DDRDATA6_CR_DLLSTATUS_spare_OFF                              (20)
  #define DDRDATA6_CR_DLLSTATUS_spare_WID                              (12)
  #define DDRDATA6_CR_DLLSTATUS_spare_MSK                              (0xFFF00000)
  #define DDRDATA6_CR_DLLSTATUS_spare_MIN                              (0)
  #define DDRDATA6_CR_DLLSTATUS_spare_MAX                              (4095) // 0x00000FFF
  #define DDRDATA6_CR_DLLSTATUS_spare_DEF                              (0x00000000)
  #define DDRDATA6_CR_DLLSTATUS_spare_HSH                              (0x0C142320)

#define DDRDATA6_CR_DLLDCMCTL_REG                                      (0x00002324)

  #define DDRDATA6_CR_DLLDCMCTL_start_OFF                              ( 0)
  #define DDRDATA6_CR_DLLDCMCTL_start_WID                              ( 1)
  #define DDRDATA6_CR_DLLDCMCTL_start_MSK                              (0x00000001)
  #define DDRDATA6_CR_DLLDCMCTL_start_MIN                              (0)
  #define DDRDATA6_CR_DLLDCMCTL_start_MAX                              (1) // 0x00000001
  #define DDRDATA6_CR_DLLDCMCTL_start_DEF                              (0x00000000)
  #define DDRDATA6_CR_DLLDCMCTL_start_HSH                              (0x01002324)

  #define DDRDATA6_CR_DLLDCMCTL_clken_OFF                              ( 1)
  #define DDRDATA6_CR_DLLDCMCTL_clken_WID                              ( 1)
  #define DDRDATA6_CR_DLLDCMCTL_clken_MSK                              (0x00000002)
  #define DDRDATA6_CR_DLLDCMCTL_clken_MIN                              (0)
  #define DDRDATA6_CR_DLLDCMCTL_clken_MAX                              (1) // 0x00000001
  #define DDRDATA6_CR_DLLDCMCTL_clken_DEF                              (0x00000000)
  #define DDRDATA6_CR_DLLDCMCTL_clken_HSH                              (0x01012324)

  #define DDRDATA6_CR_DLLDCMCTL_dcm_dccctl_en_OFF                      ( 2)
  #define DDRDATA6_CR_DLLDCMCTL_dcm_dccctl_en_WID                      ( 1)
  #define DDRDATA6_CR_DLLDCMCTL_dcm_dccctl_en_MSK                      (0x00000004)
  #define DDRDATA6_CR_DLLDCMCTL_dcm_dccctl_en_MIN                      (0)
  #define DDRDATA6_CR_DLLDCMCTL_dcm_dccctl_en_MAX                      (1) // 0x00000001
  #define DDRDATA6_CR_DLLDCMCTL_dcm_dccctl_en_DEF                      (0x00000000)
  #define DDRDATA6_CR_DLLDCMCTL_dcm_dccctl_en_HSH                      (0x01022324)

  #define DDRDATA6_CR_DLLDCMCTL_dccctl_OFF                             ( 3)
  #define DDRDATA6_CR_DLLDCMCTL_dccctl_WID                             ( 4)
  #define DDRDATA6_CR_DLLDCMCTL_dccctl_MSK                             (0x00000078)
  #define DDRDATA6_CR_DLLDCMCTL_dccctl_MIN                             (0)
  #define DDRDATA6_CR_DLLDCMCTL_dccctl_MAX                             (15) // 0x0000000F
  #define DDRDATA6_CR_DLLDCMCTL_dccctl_DEF                             (0x00000000)
  #define DDRDATA6_CR_DLLDCMCTL_dccctl_HSH                             (0x04032324)

  #define DDRDATA6_CR_DLLDCMCTL_duration_OFF                           ( 7)
  #define DDRDATA6_CR_DLLDCMCTL_duration_WID                           ( 3)
  #define DDRDATA6_CR_DLLDCMCTL_duration_MSK                           (0x00000380)
  #define DDRDATA6_CR_DLLDCMCTL_duration_MIN                           (0)
  #define DDRDATA6_CR_DLLDCMCTL_duration_MAX                           (7) // 0x00000007
  #define DDRDATA6_CR_DLLDCMCTL_duration_DEF                           (0x00000000)
  #define DDRDATA6_CR_DLLDCMCTL_duration_HSH                           (0x03072324)

  #define DDRDATA6_CR_DLLDCMCTL_dcm_done_OFF                           (10)
  #define DDRDATA6_CR_DLLDCMCTL_dcm_done_WID                           ( 1)
  #define DDRDATA6_CR_DLLDCMCTL_dcm_done_MSK                           (0x00000400)
  #define DDRDATA6_CR_DLLDCMCTL_dcm_done_MIN                           (0)
  #define DDRDATA6_CR_DLLDCMCTL_dcm_done_MAX                           (1) // 0x00000001
  #define DDRDATA6_CR_DLLDCMCTL_dcm_done_DEF                           (0x00000000)
  #define DDRDATA6_CR_DLLDCMCTL_dcm_done_HSH                           (0x010A2324)

  #define DDRDATA6_CR_DLLDCMCTL_dcm_results_OFF                        (11)
  #define DDRDATA6_CR_DLLDCMCTL_dcm_results_WID                        (15)
  #define DDRDATA6_CR_DLLDCMCTL_dcm_results_MSK                        (0x03FFF800)
  #define DDRDATA6_CR_DLLDCMCTL_dcm_results_MIN                        (0)
  #define DDRDATA6_CR_DLLDCMCTL_dcm_results_MAX                        (32767) // 0x00007FFF
  #define DDRDATA6_CR_DLLDCMCTL_dcm_results_DEF                        (0x00000000)
  #define DDRDATA6_CR_DLLDCMCTL_dcm_results_HSH                        (0x0F0B2324)

  #define DDRDATA6_CR_DLLDCMCTL_spare0_OFF                             (26)
  #define DDRDATA6_CR_DLLDCMCTL_spare0_WID                             ( 6)
  #define DDRDATA6_CR_DLLDCMCTL_spare0_MSK                             (0xFC000000)
  #define DDRDATA6_CR_DLLDCMCTL_spare0_MIN                             (0)
  #define DDRDATA6_CR_DLLDCMCTL_spare0_MAX                             (63) // 0x0000003F
  #define DDRDATA6_CR_DLLDCMCTL_spare0_DEF                             (0x00000000)
  #define DDRDATA6_CR_DLLDCMCTL_spare0_HSH                             (0x061A2324)

#define DDRDATA7_CR_MASTERDLLCFG_REG                                   (0x00002380)

  #define DDRDATA7_CR_MASTERDLLCFG_LockThresh_OFF                      ( 0)
  #define DDRDATA7_CR_MASTERDLLCFG_LockThresh_WID                      ( 3)
  #define DDRDATA7_CR_MASTERDLLCFG_LockThresh_MSK                      (0x00000007)
  #define DDRDATA7_CR_MASTERDLLCFG_LockThresh_MIN                      (0)
  #define DDRDATA7_CR_MASTERDLLCFG_LockThresh_MAX                      (7) // 0x00000007
  #define DDRDATA7_CR_MASTERDLLCFG_LockThresh_DEF                      (0x00000004)
  #define DDRDATA7_CR_MASTERDLLCFG_LockThresh_HSH                      (0x03002380)

  #define DDRDATA7_CR_MASTERDLLCFG_LockCtr_OFF                         ( 3)
  #define DDRDATA7_CR_MASTERDLLCFG_LockCtr_WID                         ( 2)
  #define DDRDATA7_CR_MASTERDLLCFG_LockCtr_MSK                         (0x00000018)
  #define DDRDATA7_CR_MASTERDLLCFG_LockCtr_MIN                         (0)
  #define DDRDATA7_CR_MASTERDLLCFG_LockCtr_MAX                         (3) // 0x00000003
  #define DDRDATA7_CR_MASTERDLLCFG_LockCtr_DEF                         (0x00000000)
  #define DDRDATA7_CR_MASTERDLLCFG_LockCtr_HSH                         (0x02032380)

  #define DDRDATA7_CR_MASTERDLLCFG_VctrlDischRate_OFF                  ( 5)
  #define DDRDATA7_CR_MASTERDLLCFG_VctrlDischRate_WID                  ( 2)
  #define DDRDATA7_CR_MASTERDLLCFG_VctrlDischRate_MSK                  (0x00000060)
  #define DDRDATA7_CR_MASTERDLLCFG_VctrlDischRate_MIN                  (0)
  #define DDRDATA7_CR_MASTERDLLCFG_VctrlDischRate_MAX                  (3) // 0x00000003
  #define DDRDATA7_CR_MASTERDLLCFG_VctrlDischRate_DEF                  (0x00000000)
  #define DDRDATA7_CR_MASTERDLLCFG_VctrlDischRate_HSH                  (0x02052380)

  #define DDRDATA7_CR_MASTERDLLCFG_SelVctrlHi_OFF                      ( 7)
  #define DDRDATA7_CR_MASTERDLLCFG_SelVctrlHi_WID                      ( 1)
  #define DDRDATA7_CR_MASTERDLLCFG_SelVctrlHi_MSK                      (0x00000080)
  #define DDRDATA7_CR_MASTERDLLCFG_SelVctrlHi_MIN                      (0)
  #define DDRDATA7_CR_MASTERDLLCFG_SelVctrlHi_MAX                      (1) // 0x00000001
  #define DDRDATA7_CR_MASTERDLLCFG_SelVctrlHi_DEF                      (0x00000000)
  #define DDRDATA7_CR_MASTERDLLCFG_SelVctrlHi_HSH                      (0x01072380)

  #define DDRDATA7_CR_MASTERDLLCFG_StartupCntSel_OFF                   ( 8)
  #define DDRDATA7_CR_MASTERDLLCFG_StartupCntSel_WID                   ( 1)
  #define DDRDATA7_CR_MASTERDLLCFG_StartupCntSel_MSK                   (0x00000100)
  #define DDRDATA7_CR_MASTERDLLCFG_StartupCntSel_MIN                   (0)
  #define DDRDATA7_CR_MASTERDLLCFG_StartupCntSel_MAX                   (1) // 0x00000001
  #define DDRDATA7_CR_MASTERDLLCFG_StartupCntSel_DEF                   (0x00000000)
  #define DDRDATA7_CR_MASTERDLLCFG_StartupCntSel_HSH                   (0x01082380)

  #define DDRDATA7_CR_MASTERDLLCFG_LockSel_OFF                         ( 9)
  #define DDRDATA7_CR_MASTERDLLCFG_LockSel_WID                         ( 2)
  #define DDRDATA7_CR_MASTERDLLCFG_LockSel_MSK                         (0x00000600)
  #define DDRDATA7_CR_MASTERDLLCFG_LockSel_MIN                         (0)
  #define DDRDATA7_CR_MASTERDLLCFG_LockSel_MAX                         (3) // 0x00000003
  #define DDRDATA7_CR_MASTERDLLCFG_LockSel_DEF                         (0x00000000)
  #define DDRDATA7_CR_MASTERDLLCFG_LockSel_HSH                         (0x02092380)

  #define DDRDATA7_CR_MASTERDLLCFG_RstOvrd_OFF                         (11)
  #define DDRDATA7_CR_MASTERDLLCFG_RstOvrd_WID                         ( 1)
  #define DDRDATA7_CR_MASTERDLLCFG_RstOvrd_MSK                         (0x00000800)
  #define DDRDATA7_CR_MASTERDLLCFG_RstOvrd_MIN                         (0)
  #define DDRDATA7_CR_MASTERDLLCFG_RstOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA7_CR_MASTERDLLCFG_RstOvrd_DEF                         (0x00000000)
  #define DDRDATA7_CR_MASTERDLLCFG_RstOvrd_HSH                         (0x010B2380)

  #define DDRDATA7_CR_MASTERDLLCFG_SelRstOvrd_OFF                      (12)
  #define DDRDATA7_CR_MASTERDLLCFG_SelRstOvrd_WID                      ( 1)
  #define DDRDATA7_CR_MASTERDLLCFG_SelRstOvrd_MSK                      (0x00001000)
  #define DDRDATA7_CR_MASTERDLLCFG_SelRstOvrd_MIN                      (0)
  #define DDRDATA7_CR_MASTERDLLCFG_SelRstOvrd_MAX                      (1) // 0x00000001
  #define DDRDATA7_CR_MASTERDLLCFG_SelRstOvrd_DEF                      (0x00000000)
  #define DDRDATA7_CR_MASTERDLLCFG_SelRstOvrd_HSH                      (0x010C2380)

  #define DDRDATA7_CR_MASTERDLLCFG_TimeOutOvrd_OFF                     (13)
  #define DDRDATA7_CR_MASTERDLLCFG_TimeOutOvrd_WID                     ( 1)
  #define DDRDATA7_CR_MASTERDLLCFG_TimeOutOvrd_MSK                     (0x00002000)
  #define DDRDATA7_CR_MASTERDLLCFG_TimeOutOvrd_MIN                     (0)
  #define DDRDATA7_CR_MASTERDLLCFG_TimeOutOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA7_CR_MASTERDLLCFG_TimeOutOvrd_DEF                     (0x00000000)
  #define DDRDATA7_CR_MASTERDLLCFG_TimeOutOvrd_HSH                     (0x010D2380)

  #define DDRDATA7_CR_MASTERDLLCFG_SelTimeOutOvrd_OFF                  (14)
  #define DDRDATA7_CR_MASTERDLLCFG_SelTimeOutOvrd_WID                  ( 1)
  #define DDRDATA7_CR_MASTERDLLCFG_SelTimeOutOvrd_MSK                  (0x00004000)
  #define DDRDATA7_CR_MASTERDLLCFG_SelTimeOutOvrd_MIN                  (0)
  #define DDRDATA7_CR_MASTERDLLCFG_SelTimeOutOvrd_MAX                  (1) // 0x00000001
  #define DDRDATA7_CR_MASTERDLLCFG_SelTimeOutOvrd_DEF                  (0x00000000)
  #define DDRDATA7_CR_MASTERDLLCFG_SelTimeOutOvrd_HSH                  (0x010E2380)

  #define DDRDATA7_CR_MASTERDLLCFG_ClkGateOvrd_OFF                     (15)
  #define DDRDATA7_CR_MASTERDLLCFG_ClkGateOvrd_WID                     ( 1)
  #define DDRDATA7_CR_MASTERDLLCFG_ClkGateOvrd_MSK                     (0x00008000)
  #define DDRDATA7_CR_MASTERDLLCFG_ClkGateOvrd_MIN                     (0)
  #define DDRDATA7_CR_MASTERDLLCFG_ClkGateOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA7_CR_MASTERDLLCFG_ClkGateOvrd_DEF                     (0x00000000)
  #define DDRDATA7_CR_MASTERDLLCFG_ClkGateOvrd_HSH                     (0x010F2380)

  #define DDRDATA7_CR_MASTERDLLCFG_LockOvrd_OFF                        (16)
  #define DDRDATA7_CR_MASTERDLLCFG_LockOvrd_WID                        ( 1)
  #define DDRDATA7_CR_MASTERDLLCFG_LockOvrd_MSK                        (0x00010000)
  #define DDRDATA7_CR_MASTERDLLCFG_LockOvrd_MIN                        (0)
  #define DDRDATA7_CR_MASTERDLLCFG_LockOvrd_MAX                        (1) // 0x00000001
  #define DDRDATA7_CR_MASTERDLLCFG_LockOvrd_DEF                        (0x00000000)
  #define DDRDATA7_CR_MASTERDLLCFG_LockOvrd_HSH                        (0x01102380)

  #define DDRDATA7_CR_MASTERDLLCFG_SelLockOvrd_OFF                     (17)
  #define DDRDATA7_CR_MASTERDLLCFG_SelLockOvrd_WID                     ( 1)
  #define DDRDATA7_CR_MASTERDLLCFG_SelLockOvrd_MSK                     (0x00020000)
  #define DDRDATA7_CR_MASTERDLLCFG_SelLockOvrd_MIN                     (0)
  #define DDRDATA7_CR_MASTERDLLCFG_SelLockOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA7_CR_MASTERDLLCFG_SelLockOvrd_DEF                     (0x00000000)
  #define DDRDATA7_CR_MASTERDLLCFG_SelLockOvrd_HSH                     (0x01112380)

  #define DDRDATA7_CR_MASTERDLLCFG_OpenLoopOvrd_OFF                    (18)
  #define DDRDATA7_CR_MASTERDLLCFG_OpenLoopOvrd_WID                    ( 1)
  #define DDRDATA7_CR_MASTERDLLCFG_OpenLoopOvrd_MSK                    (0x00040000)
  #define DDRDATA7_CR_MASTERDLLCFG_OpenLoopOvrd_MIN                    (0)
  #define DDRDATA7_CR_MASTERDLLCFG_OpenLoopOvrd_MAX                    (1) // 0x00000001
  #define DDRDATA7_CR_MASTERDLLCFG_OpenLoopOvrd_DEF                    (0x00000000)
  #define DDRDATA7_CR_MASTERDLLCFG_OpenLoopOvrd_HSH                    (0x01122380)

  #define DDRDATA7_CR_MASTERDLLCFG_SelOpenLoopOvrd_OFF                 (19)
  #define DDRDATA7_CR_MASTERDLLCFG_SelOpenLoopOvrd_WID                 ( 1)
  #define DDRDATA7_CR_MASTERDLLCFG_SelOpenLoopOvrd_MSK                 (0x00080000)
  #define DDRDATA7_CR_MASTERDLLCFG_SelOpenLoopOvrd_MIN                 (0)
  #define DDRDATA7_CR_MASTERDLLCFG_SelOpenLoopOvrd_MAX                 (1) // 0x00000001
  #define DDRDATA7_CR_MASTERDLLCFG_SelOpenLoopOvrd_DEF                 (0x00000000)
  #define DDRDATA7_CR_MASTERDLLCFG_SelOpenLoopOvrd_HSH                 (0x01132380)

  #define DDRDATA7_CR_MASTERDLLCFG_WkLockEnOvrd_OFF                    (20)
  #define DDRDATA7_CR_MASTERDLLCFG_WkLockEnOvrd_WID                    ( 1)
  #define DDRDATA7_CR_MASTERDLLCFG_WkLockEnOvrd_MSK                    (0x00100000)
  #define DDRDATA7_CR_MASTERDLLCFG_WkLockEnOvrd_MIN                    (0)
  #define DDRDATA7_CR_MASTERDLLCFG_WkLockEnOvrd_MAX                    (1) // 0x00000001
  #define DDRDATA7_CR_MASTERDLLCFG_WkLockEnOvrd_DEF                    (0x00000000)
  #define DDRDATA7_CR_MASTERDLLCFG_WkLockEnOvrd_HSH                    (0x01142380)

  #define DDRDATA7_CR_MASTERDLLCFG_SelWkLockEnOvrd_OFF                 (21)
  #define DDRDATA7_CR_MASTERDLLCFG_SelWkLockEnOvrd_WID                 ( 1)
  #define DDRDATA7_CR_MASTERDLLCFG_SelWkLockEnOvrd_MSK                 (0x00200000)
  #define DDRDATA7_CR_MASTERDLLCFG_SelWkLockEnOvrd_MIN                 (0)
  #define DDRDATA7_CR_MASTERDLLCFG_SelWkLockEnOvrd_MAX                 (1) // 0x00000001
  #define DDRDATA7_CR_MASTERDLLCFG_SelWkLockEnOvrd_DEF                 (0x00000000)
  #define DDRDATA7_CR_MASTERDLLCFG_SelWkLockEnOvrd_HSH                 (0x01152380)

  #define DDRDATA7_CR_MASTERDLLCFG_CfdlDis_OFF                         (22)
  #define DDRDATA7_CR_MASTERDLLCFG_CfdlDis_WID                         ( 1)
  #define DDRDATA7_CR_MASTERDLLCFG_CfdlDis_MSK                         (0x00400000)
  #define DDRDATA7_CR_MASTERDLLCFG_CfdlDis_MIN                         (0)
  #define DDRDATA7_CR_MASTERDLLCFG_CfdlDis_MAX                         (1) // 0x00000001
  #define DDRDATA7_CR_MASTERDLLCFG_CfdlDis_DEF                         (0x00000000)
  #define DDRDATA7_CR_MASTERDLLCFG_CfdlDis_HSH                         (0x01162380)

  #define DDRDATA7_CR_MASTERDLLCFG_DftEn_OFF                           (23)
  #define DDRDATA7_CR_MASTERDLLCFG_DftEn_WID                           ( 1)
  #define DDRDATA7_CR_MASTERDLLCFG_DftEn_MSK                           (0x00800000)
  #define DDRDATA7_CR_MASTERDLLCFG_DftEn_MIN                           (0)
  #define DDRDATA7_CR_MASTERDLLCFG_DftEn_MAX                           (1) // 0x00000001
  #define DDRDATA7_CR_MASTERDLLCFG_DftEn_DEF                           (0x00000000)
  #define DDRDATA7_CR_MASTERDLLCFG_DftEn_HSH                           (0x01172380)

  #define DDRDATA7_CR_MASTERDLLCFG_spare0_OFF                          (24)
  #define DDRDATA7_CR_MASTERDLLCFG_spare0_WID                          ( 8)
  #define DDRDATA7_CR_MASTERDLLCFG_spare0_MSK                          (0xFF000000)
  #define DDRDATA7_CR_MASTERDLLCFG_spare0_MIN                          (0)
  #define DDRDATA7_CR_MASTERDLLCFG_spare0_MAX                          (255) // 0x000000FF
  #define DDRDATA7_CR_MASTERDLLCFG_spare0_DEF                          (0x00000000)
  #define DDRDATA7_CR_MASTERDLLCFG_spare0_HSH                          (0x08182380)

#define DDRDATA7_CR_CBTUNE0_REG                                        (0x00002384)

  #define DDRDATA7_CR_CBTUNE0_DllBWEn_OFF                              ( 0)
  #define DDRDATA7_CR_CBTUNE0_DllBWEn_WID                              (32)
  #define DDRDATA7_CR_CBTUNE0_DllBWEn_MSK                              (0xFFFFFFFF)
  #define DDRDATA7_CR_CBTUNE0_DllBWEn_MIN                              (0)
  #define DDRDATA7_CR_CBTUNE0_DllBWEn_MAX                              (4294967295) // 0xFFFFFFFF
  #define DDRDATA7_CR_CBTUNE0_DllBWEn_DEF                              (0xFDB86521)
  #define DDRDATA7_CR_CBTUNE0_DllBWEn_HSH                              (0x20002384)

#define DDRDATA7_CR_CBTUNE1_REG                                        (0x00002388)

  #define DDRDATA7_CR_CBTUNE1_PiCbEn_OFF                               ( 0)
  #define DDRDATA7_CR_CBTUNE1_PiCbEn_WID                               (24)
  #define DDRDATA7_CR_CBTUNE1_PiCbEn_MSK                               (0x00FFFFFF)
  #define DDRDATA7_CR_CBTUNE1_PiCbEn_MIN                               (0)
  #define DDRDATA7_CR_CBTUNE1_PiCbEn_MAX                               (16777215) // 0x00FFFFFF
  #define DDRDATA7_CR_CBTUNE1_PiCbEn_DEF                               (0x00249492)
  #define DDRDATA7_CR_CBTUNE1_PiCbEn_HSH                               (0x18002388)

  #define DDRDATA7_CR_CBTUNE1_CbEnRsvd_OFF                             (24)
  #define DDRDATA7_CR_CBTUNE1_CbEnRsvd_WID                             ( 3)
  #define DDRDATA7_CR_CBTUNE1_CbEnRsvd_MSK                             (0x07000000)
  #define DDRDATA7_CR_CBTUNE1_CbEnRsvd_MIN                             (0)
  #define DDRDATA7_CR_CBTUNE1_CbEnRsvd_MAX                             (7) // 0x00000007
  #define DDRDATA7_CR_CBTUNE1_CbEnRsvd_DEF                             (0x00000000)
  #define DDRDATA7_CR_CBTUNE1_CbEnRsvd_HSH                             (0x03182388)

  #define DDRDATA7_CR_CBTUNE1_CbEnDllFuse_OFF                          (27)
  #define DDRDATA7_CR_CBTUNE1_CbEnDllFuse_WID                          ( 3)
  #define DDRDATA7_CR_CBTUNE1_CbEnDllFuse_MSK                          (0x38000000)
  #define DDRDATA7_CR_CBTUNE1_CbEnDllFuse_MIN                          (0)
  #define DDRDATA7_CR_CBTUNE1_CbEnDllFuse_MAX                          (7) // 0x00000007
  #define DDRDATA7_CR_CBTUNE1_CbEnDllFuse_DEF                          (0x00000002)
  #define DDRDATA7_CR_CBTUNE1_CbEnDllFuse_HSH                          (0x031B2388)

  #define DDRDATA7_CR_CBTUNE1_Spare_OFF                                (30)
  #define DDRDATA7_CR_CBTUNE1_Spare_WID                                ( 2)
  #define DDRDATA7_CR_CBTUNE1_Spare_MSK                                (0xC0000000)
  #define DDRDATA7_CR_CBTUNE1_Spare_MIN                                (0)
  #define DDRDATA7_CR_CBTUNE1_Spare_MAX                                (3) // 0x00000003
  #define DDRDATA7_CR_CBTUNE1_Spare_DEF                                (0x00000000)
  #define DDRDATA7_CR_CBTUNE1_Spare_HSH                                (0x021E2388)

#define DDRDATA7_CR_ADCCFG_REG                                         (0x0000238C)

  #define DDRDATA7_CR_ADCCFG_ADC_frz_OFF                               ( 0)
  #define DDRDATA7_CR_ADCCFG_ADC_frz_WID                               ( 1)
  #define DDRDATA7_CR_ADCCFG_ADC_frz_MSK                               (0x00000001)
  #define DDRDATA7_CR_ADCCFG_ADC_frz_MIN                               (0)
  #define DDRDATA7_CR_ADCCFG_ADC_frz_MAX                               (1) // 0x00000001
  #define DDRDATA7_CR_ADCCFG_ADC_frz_DEF                               (0x00000000)
  #define DDRDATA7_CR_ADCCFG_ADC_frz_HSH                               (0x0100238C)

  #define DDRDATA7_CR_ADCCFG_ADC_en_OFF                                ( 1)
  #define DDRDATA7_CR_ADCCFG_ADC_en_WID                                ( 1)
  #define DDRDATA7_CR_ADCCFG_ADC_en_MSK                                (0x00000002)
  #define DDRDATA7_CR_ADCCFG_ADC_en_MIN                                (0)
  #define DDRDATA7_CR_ADCCFG_ADC_en_MAX                                (1) // 0x00000001
  #define DDRDATA7_CR_ADCCFG_ADC_en_DEF                                (0x00000000)
  #define DDRDATA7_CR_ADCCFG_ADC_en_HSH                                (0x0101238C)

  #define DDRDATA7_CR_ADCCFG_ADCclkdiv_OFF                             ( 2)
  #define DDRDATA7_CR_ADCCFG_ADCclkdiv_WID                             ( 2)
  #define DDRDATA7_CR_ADCCFG_ADCclkdiv_MSK                             (0x0000000C)
  #define DDRDATA7_CR_ADCCFG_ADCclkdiv_MIN                             (0)
  #define DDRDATA7_CR_ADCCFG_ADCclkdiv_MAX                             (3) // 0x00000003
  #define DDRDATA7_CR_ADCCFG_ADCclkdiv_DEF                             (0x00000000)
  #define DDRDATA7_CR_ADCCFG_ADCclkdiv_HSH                             (0x0202238C)

  #define DDRDATA7_CR_ADCCFG_ADCstartcount_OFF                         ( 4)
  #define DDRDATA7_CR_ADCCFG_ADCstartcount_WID                         ( 2)
  #define DDRDATA7_CR_ADCCFG_ADCstartcount_MSK                         (0x00000030)
  #define DDRDATA7_CR_ADCCFG_ADCstartcount_MIN                         (0)
  #define DDRDATA7_CR_ADCCFG_ADCstartcount_MAX                         (3) // 0x00000003
  #define DDRDATA7_CR_ADCCFG_ADCstartcount_DEF                         (0x00000000)
  #define DDRDATA7_CR_ADCCFG_ADCstartcount_HSH                         (0x0204238C)

  #define DDRDATA7_CR_ADCCFG_ADCChopEn_OFF                             ( 6)
  #define DDRDATA7_CR_ADCCFG_ADCChopEn_WID                             ( 1)
  #define DDRDATA7_CR_ADCCFG_ADCChopEn_MSK                             (0x00000040)
  #define DDRDATA7_CR_ADCCFG_ADCChopEn_MIN                             (0)
  #define DDRDATA7_CR_ADCCFG_ADCChopEn_MAX                             (1) // 0x00000001
  #define DDRDATA7_CR_ADCCFG_ADCChopEn_DEF                             (0x00000000)
  #define DDRDATA7_CR_ADCCFG_ADCChopEn_HSH                             (0x0106238C)

  #define DDRDATA7_CR_ADCCFG_Spare_OFF                                 ( 7)
  #define DDRDATA7_CR_ADCCFG_Spare_WID                                 (25)
  #define DDRDATA7_CR_ADCCFG_Spare_MSK                                 (0xFFFFFF80)
  #define DDRDATA7_CR_ADCCFG_Spare_MIN                                 (0)
  #define DDRDATA7_CR_ADCCFG_Spare_MAX                                 (33554431) // 0x01FFFFFF
  #define DDRDATA7_CR_ADCCFG_Spare_DEF                                 (0x00000000)
  #define DDRDATA7_CR_ADCCFG_Spare_HSH                                 (0x1907238C)

#define DDRDATA7_CR_CBTUNE2_REG                                        (0x00002390)

  #define DDRDATA7_CR_CBTUNE2_DllCbEn_OFF                              ( 0)
  #define DDRDATA7_CR_CBTUNE2_DllCbEn_WID                              (16)
  #define DDRDATA7_CR_CBTUNE2_DllCbEn_MSK                              (0x0000FFFF)
  #define DDRDATA7_CR_CBTUNE2_DllCbEn_MIN                              (0)
  #define DDRDATA7_CR_CBTUNE2_DllCbEn_MAX                              (65535) // 0x0000FFFF
  #define DDRDATA7_CR_CBTUNE2_DllCbEn_DEF                              (0x00000000)
  #define DDRDATA7_CR_CBTUNE2_DllCbEn_HSH                              (0x10002390)

  #define DDRDATA7_CR_CBTUNE2_Spare_OFF                                (16)
  #define DDRDATA7_CR_CBTUNE2_Spare_WID                                (16)
  #define DDRDATA7_CR_CBTUNE2_Spare_MSK                                (0xFFFF0000)
  #define DDRDATA7_CR_CBTUNE2_Spare_MIN                                (0)
  #define DDRDATA7_CR_CBTUNE2_Spare_MAX                                (65535) // 0x0000FFFF
  #define DDRDATA7_CR_CBTUNE2_Spare_DEF                                (0x00000000)
  #define DDRDATA7_CR_CBTUNE2_Spare_HSH                                (0x10102390)

#define DDRDATA7_CR_PIDFTDLY_REG                                       (0x00002398)

  #define DDRDATA7_CR_PIDFTDLY_PiDftDelay_OFF                          ( 0)
  #define DDRDATA7_CR_PIDFTDLY_PiDftDelay_WID                          ( 7)
  #define DDRDATA7_CR_PIDFTDLY_PiDftDelay_MSK                          (0x0000007F)
  #define DDRDATA7_CR_PIDFTDLY_PiDftDelay_MIN                          (0)
  #define DDRDATA7_CR_PIDFTDLY_PiDftDelay_MAX                          (127) // 0x0000007F
  #define DDRDATA7_CR_PIDFTDLY_PiDftDelay_DEF                          (0x00000000)
  #define DDRDATA7_CR_PIDFTDLY_PiDftDelay_HSH                          (0x07002398)

  #define DDRDATA7_CR_PIDFTDLY_Ch0PiEnOvrd_OFF                         ( 7)
  #define DDRDATA7_CR_PIDFTDLY_Ch0PiEnOvrd_WID                         ( 1)
  #define DDRDATA7_CR_PIDFTDLY_Ch0PiEnOvrd_MSK                         (0x00000080)
  #define DDRDATA7_CR_PIDFTDLY_Ch0PiEnOvrd_MIN                         (0)
  #define DDRDATA7_CR_PIDFTDLY_Ch0PiEnOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA7_CR_PIDFTDLY_Ch0PiEnOvrd_DEF                         (0x00000000)
  #define DDRDATA7_CR_PIDFTDLY_Ch0PiEnOvrd_HSH                         (0x01072398)

  #define DDRDATA7_CR_PIDFTDLY_Ch1PiEnOvrd_OFF                         ( 8)
  #define DDRDATA7_CR_PIDFTDLY_Ch1PiEnOvrd_WID                         ( 1)
  #define DDRDATA7_CR_PIDFTDLY_Ch1PiEnOvrd_MSK                         (0x00000100)
  #define DDRDATA7_CR_PIDFTDLY_Ch1PiEnOvrd_MIN                         (0)
  #define DDRDATA7_CR_PIDFTDLY_Ch1PiEnOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA7_CR_PIDFTDLY_Ch1PiEnOvrd_DEF                         (0x00000000)
  #define DDRDATA7_CR_PIDFTDLY_Ch1PiEnOvrd_HSH                         (0x01082398)

  #define DDRDATA7_CR_PIDFTDLY_Ch0PiDFTEn_OFF                          ( 9)
  #define DDRDATA7_CR_PIDFTDLY_Ch0PiDFTEn_WID                          ( 1)
  #define DDRDATA7_CR_PIDFTDLY_Ch0PiDFTEn_MSK                          (0x00000200)
  #define DDRDATA7_CR_PIDFTDLY_Ch0PiDFTEn_MIN                          (0)
  #define DDRDATA7_CR_PIDFTDLY_Ch0PiDFTEn_MAX                          (1) // 0x00000001
  #define DDRDATA7_CR_PIDFTDLY_Ch0PiDFTEn_DEF                          (0x00000000)
  #define DDRDATA7_CR_PIDFTDLY_Ch0PiDFTEn_HSH                          (0x01092398)

  #define DDRDATA7_CR_PIDFTDLY_Ch1PiDFTEn_OFF                          (10)
  #define DDRDATA7_CR_PIDFTDLY_Ch1PiDFTEn_WID                          ( 1)
  #define DDRDATA7_CR_PIDFTDLY_Ch1PiDFTEn_MSK                          (0x00000400)
  #define DDRDATA7_CR_PIDFTDLY_Ch1PiDFTEn_MIN                          (0)
  #define DDRDATA7_CR_PIDFTDLY_Ch1PiDFTEn_MAX                          (1) // 0x00000001
  #define DDRDATA7_CR_PIDFTDLY_Ch1PiDFTEn_DEF                          (0x00000000)
  #define DDRDATA7_CR_PIDFTDLY_Ch1PiDFTEn_HSH                          (0x010A2398)

  #define DDRDATA7_CR_PIDFTDLY_Spare_OFF                               (11)
  #define DDRDATA7_CR_PIDFTDLY_Spare_WID                               ( 4)
  #define DDRDATA7_CR_PIDFTDLY_Spare_MSK                               (0x00007800)
  #define DDRDATA7_CR_PIDFTDLY_Spare_MIN                               (0)
  #define DDRDATA7_CR_PIDFTDLY_Spare_MAX                               (15) // 0x0000000F
  #define DDRDATA7_CR_PIDFTDLY_Spare_DEF                               (0x00000000)
  #define DDRDATA7_CR_PIDFTDLY_Spare_HSH                               (0x040B2398)

  #define DDRDATA7_CR_PIDFTDLY_RefPiOvrd_OFF                           (15)
  #define DDRDATA7_CR_PIDFTDLY_RefPiOvrd_WID                           ( 1)
  #define DDRDATA7_CR_PIDFTDLY_RefPiOvrd_MSK                           (0x00008000)
  #define DDRDATA7_CR_PIDFTDLY_RefPiOvrd_MIN                           (0)
  #define DDRDATA7_CR_PIDFTDLY_RefPiOvrd_MAX                           (1) // 0x00000001
  #define DDRDATA7_CR_PIDFTDLY_RefPiOvrd_DEF                           (0x00000000)
  #define DDRDATA7_CR_PIDFTDLY_RefPiOvrd_HSH                           (0x010F2398)

  #define DDRDATA7_CR_PIDFTDLY_Rsvd_OFF                                (16)
  #define DDRDATA7_CR_PIDFTDLY_Rsvd_WID                                (16)
  #define DDRDATA7_CR_PIDFTDLY_Rsvd_MSK                                (0xFFFF0000)
  #define DDRDATA7_CR_PIDFTDLY_Rsvd_MIN                                (0)
  #define DDRDATA7_CR_PIDFTDLY_Rsvd_MAX                                (65535) // 0x0000FFFF
  #define DDRDATA7_CR_PIDFTDLY_Rsvd_DEF                                (0x00000000)
  #define DDRDATA7_CR_PIDFTDLY_Rsvd_HSH                                (0x10102398)

#define DDRDATA7_CR_DLLPITESTANDADC_REG                                (0x0000239C)

  #define DDRDATA7_CR_DLLPITESTANDADC_RunTest_OFF                      ( 0)
  #define DDRDATA7_CR_DLLPITESTANDADC_RunTest_WID                      ( 1)
  #define DDRDATA7_CR_DLLPITESTANDADC_RunTest_MSK                      (0x00000001)
  #define DDRDATA7_CR_DLLPITESTANDADC_RunTest_MIN                      (0)
  #define DDRDATA7_CR_DLLPITESTANDADC_RunTest_MAX                      (1) // 0x00000001
  #define DDRDATA7_CR_DLLPITESTANDADC_RunTest_DEF                      (0x00000000)
  #define DDRDATA7_CR_DLLPITESTANDADC_RunTest_HSH                      (0x0100239C)

  #define DDRDATA7_CR_DLLPITESTANDADC_Load_OFF                         ( 1)
  #define DDRDATA7_CR_DLLPITESTANDADC_Load_WID                         ( 1)
  #define DDRDATA7_CR_DLLPITESTANDADC_Load_MSK                         (0x00000002)
  #define DDRDATA7_CR_DLLPITESTANDADC_Load_MIN                         (0)
  #define DDRDATA7_CR_DLLPITESTANDADC_Load_MAX                         (1) // 0x00000001
  #define DDRDATA7_CR_DLLPITESTANDADC_Load_DEF                         (0x00000000)
  #define DDRDATA7_CR_DLLPITESTANDADC_Load_HSH                         (0x0101239C)

  #define DDRDATA7_CR_DLLPITESTANDADC_ModeHVM_OFF                      ( 2)
  #define DDRDATA7_CR_DLLPITESTANDADC_ModeHVM_WID                      ( 1)
  #define DDRDATA7_CR_DLLPITESTANDADC_ModeHVM_MSK                      (0x00000004)
  #define DDRDATA7_CR_DLLPITESTANDADC_ModeHVM_MIN                      (0)
  #define DDRDATA7_CR_DLLPITESTANDADC_ModeHVM_MAX                      (1) // 0x00000001
  #define DDRDATA7_CR_DLLPITESTANDADC_ModeHVM_DEF                      (0x00000000)
  #define DDRDATA7_CR_DLLPITESTANDADC_ModeHVM_HSH                      (0x0102239C)

  #define DDRDATA7_CR_DLLPITESTANDADC_ModeDV_OFF                       ( 3)
  #define DDRDATA7_CR_DLLPITESTANDADC_ModeDV_WID                       ( 1)
  #define DDRDATA7_CR_DLLPITESTANDADC_ModeDV_MSK                       (0x00000008)
  #define DDRDATA7_CR_DLLPITESTANDADC_ModeDV_MIN                       (0)
  #define DDRDATA7_CR_DLLPITESTANDADC_ModeDV_MAX                       (1) // 0x00000001
  #define DDRDATA7_CR_DLLPITESTANDADC_ModeDV_DEF                       (0x00000000)
  #define DDRDATA7_CR_DLLPITESTANDADC_ModeDV_HSH                       (0x0103239C)

  #define DDRDATA7_CR_DLLPITESTANDADC_CalCfdl_OFF                      ( 4)
  #define DDRDATA7_CR_DLLPITESTANDADC_CalCfdl_WID                      ( 1)
  #define DDRDATA7_CR_DLLPITESTANDADC_CalCfdl_MSK                      (0x00000010)
  #define DDRDATA7_CR_DLLPITESTANDADC_CalCfdl_MIN                      (0)
  #define DDRDATA7_CR_DLLPITESTANDADC_CalCfdl_MAX                      (1) // 0x00000001
  #define DDRDATA7_CR_DLLPITESTANDADC_CalCfdl_DEF                      (0x00000000)
  #define DDRDATA7_CR_DLLPITESTANDADC_CalCfdl_HSH                      (0x0104239C)

  #define DDRDATA7_CR_DLLPITESTANDADC_LoadCount_OFF                    ( 5)
  #define DDRDATA7_CR_DLLPITESTANDADC_LoadCount_WID                    (10)
  #define DDRDATA7_CR_DLLPITESTANDADC_LoadCount_MSK                    (0x00007FE0)
  #define DDRDATA7_CR_DLLPITESTANDADC_LoadCount_MIN                    (0)
  #define DDRDATA7_CR_DLLPITESTANDADC_LoadCount_MAX                    (1023) // 0x000003FF
  #define DDRDATA7_CR_DLLPITESTANDADC_LoadCount_DEF                    (0x00000000)
  #define DDRDATA7_CR_DLLPITESTANDADC_LoadCount_HSH                    (0x0A05239C)

  #define DDRDATA7_CR_DLLPITESTANDADC_CountStatus_OFF                  (15)
  #define DDRDATA7_CR_DLLPITESTANDADC_CountStatus_WID                  (10)
  #define DDRDATA7_CR_DLLPITESTANDADC_CountStatus_MSK                  (0x01FF8000)
  #define DDRDATA7_CR_DLLPITESTANDADC_CountStatus_MIN                  (0)
  #define DDRDATA7_CR_DLLPITESTANDADC_CountStatus_MAX                  (1023) // 0x000003FF
  #define DDRDATA7_CR_DLLPITESTANDADC_CountStatus_DEF                  (0x00000000)
  #define DDRDATA7_CR_DLLPITESTANDADC_CountStatus_HSH                  (0x0A0F239C)

  #define DDRDATA7_CR_DLLPITESTANDADC_ModeADC_OFF                      (25)
  #define DDRDATA7_CR_DLLPITESTANDADC_ModeADC_WID                      ( 1)
  #define DDRDATA7_CR_DLLPITESTANDADC_ModeADC_MSK                      (0x02000000)
  #define DDRDATA7_CR_DLLPITESTANDADC_ModeADC_MIN                      (0)
  #define DDRDATA7_CR_DLLPITESTANDADC_ModeADC_MAX                      (1) // 0x00000001
  #define DDRDATA7_CR_DLLPITESTANDADC_ModeADC_DEF                      (0x00000000)
  #define DDRDATA7_CR_DLLPITESTANDADC_ModeADC_HSH                      (0x0119239C)

  #define DDRDATA7_CR_DLLPITESTANDADC_ADCClkDiv_OFF                    (26)
  #define DDRDATA7_CR_DLLPITESTANDADC_ADCClkDiv_WID                    ( 2)
  #define DDRDATA7_CR_DLLPITESTANDADC_ADCClkDiv_MSK                    (0x0C000000)
  #define DDRDATA7_CR_DLLPITESTANDADC_ADCClkDiv_MIN                    (0)
  #define DDRDATA7_CR_DLLPITESTANDADC_ADCClkDiv_MAX                    (3) // 0x00000003
  #define DDRDATA7_CR_DLLPITESTANDADC_ADCClkDiv_DEF                    (0x00000000)
  #define DDRDATA7_CR_DLLPITESTANDADC_ADCClkDiv_HSH                    (0x021A239C)

  #define DDRDATA7_CR_DLLPITESTANDADC_ADCDdrChanSel_OFF                (28)
  #define DDRDATA7_CR_DLLPITESTANDADC_ADCDdrChanSel_WID                ( 1)
  #define DDRDATA7_CR_DLLPITESTANDADC_ADCDdrChanSel_MSK                (0x10000000)
  #define DDRDATA7_CR_DLLPITESTANDADC_ADCDdrChanSel_MIN                (0)
  #define DDRDATA7_CR_DLLPITESTANDADC_ADCDdrChanSel_MAX                (1) // 0x00000001
  #define DDRDATA7_CR_DLLPITESTANDADC_ADCDdrChanSel_DEF                (0x00000000)
  #define DDRDATA7_CR_DLLPITESTANDADC_ADCDdrChanSel_HSH                (0x011C239C)

  #define DDRDATA7_CR_DLLPITESTANDADC_ADCChopEn_OFF                    (29)
  #define DDRDATA7_CR_DLLPITESTANDADC_ADCChopEn_WID                    ( 1)
  #define DDRDATA7_CR_DLLPITESTANDADC_ADCChopEn_MSK                    (0x20000000)
  #define DDRDATA7_CR_DLLPITESTANDADC_ADCChopEn_MIN                    (0)
  #define DDRDATA7_CR_DLLPITESTANDADC_ADCChopEn_MAX                    (1) // 0x00000001
  #define DDRDATA7_CR_DLLPITESTANDADC_ADCChopEn_DEF                    (0x00000000)
  #define DDRDATA7_CR_DLLPITESTANDADC_ADCChopEn_HSH                    (0x011D239C)

  #define DDRDATA7_CR_DLLPITESTANDADC_ADCDone_OFF                      (30)
  #define DDRDATA7_CR_DLLPITESTANDADC_ADCDone_WID                      ( 1)
  #define DDRDATA7_CR_DLLPITESTANDADC_ADCDone_MSK                      (0x40000000)
  #define DDRDATA7_CR_DLLPITESTANDADC_ADCDone_MIN                      (0)
  #define DDRDATA7_CR_DLLPITESTANDADC_ADCDone_MAX                      (1) // 0x00000001
  #define DDRDATA7_CR_DLLPITESTANDADC_ADCDone_DEF                      (0x00000000)
  #define DDRDATA7_CR_DLLPITESTANDADC_ADCDone_HSH                      (0x011E239C)

  #define DDRDATA7_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF             (31)
  #define DDRDATA7_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID             ( 1)
  #define DDRDATA7_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK             (0x80000000)
  #define DDRDATA7_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN             (0)
  #define DDRDATA7_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX             (1) // 0x00000001
  #define DDRDATA7_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF             (0x00000000)
  #define DDRDATA7_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH             (0x011F239C)

#define DDRDATA7_CR_DLLSTATUS_REG                                      (0x000023A0)

  #define DDRDATA7_CR_DLLSTATUS_DetrmLockStat_OFF                      ( 0)
  #define DDRDATA7_CR_DLLSTATUS_DetrmLockStat_WID                      ( 1)
  #define DDRDATA7_CR_DLLSTATUS_DetrmLockStat_MSK                      (0x00000001)
  #define DDRDATA7_CR_DLLSTATUS_DetrmLockStat_MIN                      (0)
  #define DDRDATA7_CR_DLLSTATUS_DetrmLockStat_MAX                      (1) // 0x00000001
  #define DDRDATA7_CR_DLLSTATUS_DetrmLockStat_DEF                      (0x00000000)
  #define DDRDATA7_CR_DLLSTATUS_DetrmLockStat_HSH                      (0x010023A0)

  #define DDRDATA7_CR_DLLSTATUS_FuncLockStat_OFF                       ( 1)
  #define DDRDATA7_CR_DLLSTATUS_FuncLockStat_WID                       ( 1)
  #define DDRDATA7_CR_DLLSTATUS_FuncLockStat_MSK                       (0x00000002)
  #define DDRDATA7_CR_DLLSTATUS_FuncLockStat_MIN                       (0)
  #define DDRDATA7_CR_DLLSTATUS_FuncLockStat_MAX                       (1) // 0x00000001
  #define DDRDATA7_CR_DLLSTATUS_FuncLockStat_DEF                       (0x00000000)
  #define DDRDATA7_CR_DLLSTATUS_FuncLockStat_HSH                       (0x010123A0)

  #define DDRDATA7_CR_DLLSTATUS_Lock_OFF                               ( 2)
  #define DDRDATA7_CR_DLLSTATUS_Lock_WID                               ( 1)
  #define DDRDATA7_CR_DLLSTATUS_Lock_MSK                               (0x00000004)
  #define DDRDATA7_CR_DLLSTATUS_Lock_MIN                               (0)
  #define DDRDATA7_CR_DLLSTATUS_Lock_MAX                               (1) // 0x00000001
  #define DDRDATA7_CR_DLLSTATUS_Lock_DEF                               (0x00000000)
  #define DDRDATA7_CR_DLLSTATUS_Lock_HSH                               (0x010223A0)

  #define DDRDATA7_CR_DLLSTATUS_Timeout_OFF                            ( 3)
  #define DDRDATA7_CR_DLLSTATUS_Timeout_WID                            ( 1)
  #define DDRDATA7_CR_DLLSTATUS_Timeout_MSK                            (0x00000008)
  #define DDRDATA7_CR_DLLSTATUS_Timeout_MIN                            (0)
  #define DDRDATA7_CR_DLLSTATUS_Timeout_MAX                            (1) // 0x00000001
  #define DDRDATA7_CR_DLLSTATUS_Timeout_DEF                            (0x00000000)
  #define DDRDATA7_CR_DLLSTATUS_Timeout_HSH                            (0x010323A0)

  #define DDRDATA7_CR_DLLSTATUS_DllReset_OFF                           ( 4)
  #define DDRDATA7_CR_DLLSTATUS_DllReset_WID                           ( 1)
  #define DDRDATA7_CR_DLLSTATUS_DllReset_MSK                           (0x00000010)
  #define DDRDATA7_CR_DLLSTATUS_DllReset_MIN                           (0)
  #define DDRDATA7_CR_DLLSTATUS_DllReset_MAX                           (1) // 0x00000001
  #define DDRDATA7_CR_DLLSTATUS_DllReset_DEF                           (0x00000000)
  #define DDRDATA7_CR_DLLSTATUS_DllReset_HSH                           (0x010423A0)

  #define DDRDATA7_CR_DLLSTATUS_LongLockStat_OFF                       ( 5)
  #define DDRDATA7_CR_DLLSTATUS_LongLockStat_WID                       ( 1)
  #define DDRDATA7_CR_DLLSTATUS_LongLockStat_MSK                       (0x00000020)
  #define DDRDATA7_CR_DLLSTATUS_LongLockStat_MIN                       (0)
  #define DDRDATA7_CR_DLLSTATUS_LongLockStat_MAX                       (1) // 0x00000001
  #define DDRDATA7_CR_DLLSTATUS_LongLockStat_DEF                       (0x00000000)
  #define DDRDATA7_CR_DLLSTATUS_LongLockStat_HSH                       (0x010523A0)

  #define DDRDATA7_CR_DLLSTATUS_EarlyLockStat_OFF                      ( 6)
  #define DDRDATA7_CR_DLLSTATUS_EarlyLockStat_WID                      ( 1)
  #define DDRDATA7_CR_DLLSTATUS_EarlyLockStat_MSK                      (0x00000040)
  #define DDRDATA7_CR_DLLSTATUS_EarlyLockStat_MIN                      (0)
  #define DDRDATA7_CR_DLLSTATUS_EarlyLockStat_MAX                      (1) // 0x00000001
  #define DDRDATA7_CR_DLLSTATUS_EarlyLockStat_DEF                      (0x00000000)
  #define DDRDATA7_CR_DLLSTATUS_EarlyLockStat_HSH                      (0x010623A0)

  #define DDRDATA7_CR_DLLSTATUS_NormalMode_NotWkLock_OFF               ( 7)
  #define DDRDATA7_CR_DLLSTATUS_NormalMode_NotWkLock_WID               ( 1)
  #define DDRDATA7_CR_DLLSTATUS_NormalMode_NotWkLock_MSK               (0x00000080)
  #define DDRDATA7_CR_DLLSTATUS_NormalMode_NotWkLock_MIN               (0)
  #define DDRDATA7_CR_DLLSTATUS_NormalMode_NotWkLock_MAX               (1) // 0x00000001
  #define DDRDATA7_CR_DLLSTATUS_NormalMode_NotWkLock_DEF               (0x00000000)
  #define DDRDATA7_CR_DLLSTATUS_NormalMode_NotWkLock_HSH               (0x010723A0)

  #define DDRDATA7_CR_DLLSTATUS_ADCout_OFF                             ( 8)
  #define DDRDATA7_CR_DLLSTATUS_ADCout_WID                             (10)
  #define DDRDATA7_CR_DLLSTATUS_ADCout_MSK                             (0x0003FF00)
  #define DDRDATA7_CR_DLLSTATUS_ADCout_MIN                             (0)
  #define DDRDATA7_CR_DLLSTATUS_ADCout_MAX                             (1023) // 0x000003FF
  #define DDRDATA7_CR_DLLSTATUS_ADCout_DEF                             (0x00000000)
  #define DDRDATA7_CR_DLLSTATUS_ADCout_HSH                             (0x0A0823A0)

  #define DDRDATA7_CR_DLLSTATUS_ADCStatus_OFF                          (18)
  #define DDRDATA7_CR_DLLSTATUS_ADCStatus_WID                          ( 1)
  #define DDRDATA7_CR_DLLSTATUS_ADCStatus_MSK                          (0x00040000)
  #define DDRDATA7_CR_DLLSTATUS_ADCStatus_MIN                          (0)
  #define DDRDATA7_CR_DLLSTATUS_ADCStatus_MAX                          (1) // 0x00000001
  #define DDRDATA7_CR_DLLSTATUS_ADCStatus_DEF                          (0x00000000)
  #define DDRDATA7_CR_DLLSTATUS_ADCStatus_HSH                          (0x011223A0)

  #define DDRDATA7_CR_DLLSTATUS_pilags_OFF                             (19)
  #define DDRDATA7_CR_DLLSTATUS_pilags_WID                             ( 1)
  #define DDRDATA7_CR_DLLSTATUS_pilags_MSK                             (0x00080000)
  #define DDRDATA7_CR_DLLSTATUS_pilags_MIN                             (0)
  #define DDRDATA7_CR_DLLSTATUS_pilags_MAX                             (1) // 0x00000001
  #define DDRDATA7_CR_DLLSTATUS_pilags_DEF                             (0x00000000)
  #define DDRDATA7_CR_DLLSTATUS_pilags_HSH                             (0x011323A0)

  #define DDRDATA7_CR_DLLSTATUS_spare_OFF                              (20)
  #define DDRDATA7_CR_DLLSTATUS_spare_WID                              (12)
  #define DDRDATA7_CR_DLLSTATUS_spare_MSK                              (0xFFF00000)
  #define DDRDATA7_CR_DLLSTATUS_spare_MIN                              (0)
  #define DDRDATA7_CR_DLLSTATUS_spare_MAX                              (4095) // 0x00000FFF
  #define DDRDATA7_CR_DLLSTATUS_spare_DEF                              (0x00000000)
  #define DDRDATA7_CR_DLLSTATUS_spare_HSH                              (0x0C1423A0)

#define DDRDATA7_CR_DLLDCMCTL_REG                                      (0x000023A4)

  #define DDRDATA7_CR_DLLDCMCTL_start_OFF                              ( 0)
  #define DDRDATA7_CR_DLLDCMCTL_start_WID                              ( 1)
  #define DDRDATA7_CR_DLLDCMCTL_start_MSK                              (0x00000001)
  #define DDRDATA7_CR_DLLDCMCTL_start_MIN                              (0)
  #define DDRDATA7_CR_DLLDCMCTL_start_MAX                              (1) // 0x00000001
  #define DDRDATA7_CR_DLLDCMCTL_start_DEF                              (0x00000000)
  #define DDRDATA7_CR_DLLDCMCTL_start_HSH                              (0x010023A4)

  #define DDRDATA7_CR_DLLDCMCTL_clken_OFF                              ( 1)
  #define DDRDATA7_CR_DLLDCMCTL_clken_WID                              ( 1)
  #define DDRDATA7_CR_DLLDCMCTL_clken_MSK                              (0x00000002)
  #define DDRDATA7_CR_DLLDCMCTL_clken_MIN                              (0)
  #define DDRDATA7_CR_DLLDCMCTL_clken_MAX                              (1) // 0x00000001
  #define DDRDATA7_CR_DLLDCMCTL_clken_DEF                              (0x00000000)
  #define DDRDATA7_CR_DLLDCMCTL_clken_HSH                              (0x010123A4)

  #define DDRDATA7_CR_DLLDCMCTL_dcm_dccctl_en_OFF                      ( 2)
  #define DDRDATA7_CR_DLLDCMCTL_dcm_dccctl_en_WID                      ( 1)
  #define DDRDATA7_CR_DLLDCMCTL_dcm_dccctl_en_MSK                      (0x00000004)
  #define DDRDATA7_CR_DLLDCMCTL_dcm_dccctl_en_MIN                      (0)
  #define DDRDATA7_CR_DLLDCMCTL_dcm_dccctl_en_MAX                      (1) // 0x00000001
  #define DDRDATA7_CR_DLLDCMCTL_dcm_dccctl_en_DEF                      (0x00000000)
  #define DDRDATA7_CR_DLLDCMCTL_dcm_dccctl_en_HSH                      (0x010223A4)

  #define DDRDATA7_CR_DLLDCMCTL_dccctl_OFF                             ( 3)
  #define DDRDATA7_CR_DLLDCMCTL_dccctl_WID                             ( 4)
  #define DDRDATA7_CR_DLLDCMCTL_dccctl_MSK                             (0x00000078)
  #define DDRDATA7_CR_DLLDCMCTL_dccctl_MIN                             (0)
  #define DDRDATA7_CR_DLLDCMCTL_dccctl_MAX                             (15) // 0x0000000F
  #define DDRDATA7_CR_DLLDCMCTL_dccctl_DEF                             (0x00000000)
  #define DDRDATA7_CR_DLLDCMCTL_dccctl_HSH                             (0x040323A4)

  #define DDRDATA7_CR_DLLDCMCTL_duration_OFF                           ( 7)
  #define DDRDATA7_CR_DLLDCMCTL_duration_WID                           ( 3)
  #define DDRDATA7_CR_DLLDCMCTL_duration_MSK                           (0x00000380)
  #define DDRDATA7_CR_DLLDCMCTL_duration_MIN                           (0)
  #define DDRDATA7_CR_DLLDCMCTL_duration_MAX                           (7) // 0x00000007
  #define DDRDATA7_CR_DLLDCMCTL_duration_DEF                           (0x00000000)
  #define DDRDATA7_CR_DLLDCMCTL_duration_HSH                           (0x030723A4)

  #define DDRDATA7_CR_DLLDCMCTL_dcm_done_OFF                           (10)
  #define DDRDATA7_CR_DLLDCMCTL_dcm_done_WID                           ( 1)
  #define DDRDATA7_CR_DLLDCMCTL_dcm_done_MSK                           (0x00000400)
  #define DDRDATA7_CR_DLLDCMCTL_dcm_done_MIN                           (0)
  #define DDRDATA7_CR_DLLDCMCTL_dcm_done_MAX                           (1) // 0x00000001
  #define DDRDATA7_CR_DLLDCMCTL_dcm_done_DEF                           (0x00000000)
  #define DDRDATA7_CR_DLLDCMCTL_dcm_done_HSH                           (0x010A23A4)

  #define DDRDATA7_CR_DLLDCMCTL_dcm_results_OFF                        (11)
  #define DDRDATA7_CR_DLLDCMCTL_dcm_results_WID                        (15)
  #define DDRDATA7_CR_DLLDCMCTL_dcm_results_MSK                        (0x03FFF800)
  #define DDRDATA7_CR_DLLDCMCTL_dcm_results_MIN                        (0)
  #define DDRDATA7_CR_DLLDCMCTL_dcm_results_MAX                        (32767) // 0x00007FFF
  #define DDRDATA7_CR_DLLDCMCTL_dcm_results_DEF                        (0x00000000)
  #define DDRDATA7_CR_DLLDCMCTL_dcm_results_HSH                        (0x0F0B23A4)

  #define DDRDATA7_CR_DLLDCMCTL_spare0_OFF                             (26)
  #define DDRDATA7_CR_DLLDCMCTL_spare0_WID                             ( 6)
  #define DDRDATA7_CR_DLLDCMCTL_spare0_MSK                             (0xFC000000)
  #define DDRDATA7_CR_DLLDCMCTL_spare0_MIN                             (0)
  #define DDRDATA7_CR_DLLDCMCTL_spare0_MAX                             (63) // 0x0000003F
  #define DDRDATA7_CR_DLLDCMCTL_spare0_DEF                             (0x00000000)
  #define DDRDATA7_CR_DLLDCMCTL_spare0_HSH                             (0x061A23A4)

#define DDRDATA8_CR_MASTERDLLCFG_REG                                   (0x00002400)

  #define DDRDATA8_CR_MASTERDLLCFG_LockThresh_OFF                      ( 0)
  #define DDRDATA8_CR_MASTERDLLCFG_LockThresh_WID                      ( 3)
  #define DDRDATA8_CR_MASTERDLLCFG_LockThresh_MSK                      (0x00000007)
  #define DDRDATA8_CR_MASTERDLLCFG_LockThresh_MIN                      (0)
  #define DDRDATA8_CR_MASTERDLLCFG_LockThresh_MAX                      (7) // 0x00000007
  #define DDRDATA8_CR_MASTERDLLCFG_LockThresh_DEF                      (0x00000004)
  #define DDRDATA8_CR_MASTERDLLCFG_LockThresh_HSH                      (0x03002400)

  #define DDRDATA8_CR_MASTERDLLCFG_LockCtr_OFF                         ( 3)
  #define DDRDATA8_CR_MASTERDLLCFG_LockCtr_WID                         ( 2)
  #define DDRDATA8_CR_MASTERDLLCFG_LockCtr_MSK                         (0x00000018)
  #define DDRDATA8_CR_MASTERDLLCFG_LockCtr_MIN                         (0)
  #define DDRDATA8_CR_MASTERDLLCFG_LockCtr_MAX                         (3) // 0x00000003
  #define DDRDATA8_CR_MASTERDLLCFG_LockCtr_DEF                         (0x00000000)
  #define DDRDATA8_CR_MASTERDLLCFG_LockCtr_HSH                         (0x02032400)

  #define DDRDATA8_CR_MASTERDLLCFG_VctrlDischRate_OFF                  ( 5)
  #define DDRDATA8_CR_MASTERDLLCFG_VctrlDischRate_WID                  ( 2)
  #define DDRDATA8_CR_MASTERDLLCFG_VctrlDischRate_MSK                  (0x00000060)
  #define DDRDATA8_CR_MASTERDLLCFG_VctrlDischRate_MIN                  (0)
  #define DDRDATA8_CR_MASTERDLLCFG_VctrlDischRate_MAX                  (3) // 0x00000003
  #define DDRDATA8_CR_MASTERDLLCFG_VctrlDischRate_DEF                  (0x00000000)
  #define DDRDATA8_CR_MASTERDLLCFG_VctrlDischRate_HSH                  (0x02052400)

  #define DDRDATA8_CR_MASTERDLLCFG_SelVctrlHi_OFF                      ( 7)
  #define DDRDATA8_CR_MASTERDLLCFG_SelVctrlHi_WID                      ( 1)
  #define DDRDATA8_CR_MASTERDLLCFG_SelVctrlHi_MSK                      (0x00000080)
  #define DDRDATA8_CR_MASTERDLLCFG_SelVctrlHi_MIN                      (0)
  #define DDRDATA8_CR_MASTERDLLCFG_SelVctrlHi_MAX                      (1) // 0x00000001
  #define DDRDATA8_CR_MASTERDLLCFG_SelVctrlHi_DEF                      (0x00000000)
  #define DDRDATA8_CR_MASTERDLLCFG_SelVctrlHi_HSH                      (0x01072400)

  #define DDRDATA8_CR_MASTERDLLCFG_StartupCntSel_OFF                   ( 8)
  #define DDRDATA8_CR_MASTERDLLCFG_StartupCntSel_WID                   ( 1)
  #define DDRDATA8_CR_MASTERDLLCFG_StartupCntSel_MSK                   (0x00000100)
  #define DDRDATA8_CR_MASTERDLLCFG_StartupCntSel_MIN                   (0)
  #define DDRDATA8_CR_MASTERDLLCFG_StartupCntSel_MAX                   (1) // 0x00000001
  #define DDRDATA8_CR_MASTERDLLCFG_StartupCntSel_DEF                   (0x00000000)
  #define DDRDATA8_CR_MASTERDLLCFG_StartupCntSel_HSH                   (0x01082400)

  #define DDRDATA8_CR_MASTERDLLCFG_LockSel_OFF                         ( 9)
  #define DDRDATA8_CR_MASTERDLLCFG_LockSel_WID                         ( 2)
  #define DDRDATA8_CR_MASTERDLLCFG_LockSel_MSK                         (0x00000600)
  #define DDRDATA8_CR_MASTERDLLCFG_LockSel_MIN                         (0)
  #define DDRDATA8_CR_MASTERDLLCFG_LockSel_MAX                         (3) // 0x00000003
  #define DDRDATA8_CR_MASTERDLLCFG_LockSel_DEF                         (0x00000000)
  #define DDRDATA8_CR_MASTERDLLCFG_LockSel_HSH                         (0x02092400)

  #define DDRDATA8_CR_MASTERDLLCFG_RstOvrd_OFF                         (11)
  #define DDRDATA8_CR_MASTERDLLCFG_RstOvrd_WID                         ( 1)
  #define DDRDATA8_CR_MASTERDLLCFG_RstOvrd_MSK                         (0x00000800)
  #define DDRDATA8_CR_MASTERDLLCFG_RstOvrd_MIN                         (0)
  #define DDRDATA8_CR_MASTERDLLCFG_RstOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA8_CR_MASTERDLLCFG_RstOvrd_DEF                         (0x00000000)
  #define DDRDATA8_CR_MASTERDLLCFG_RstOvrd_HSH                         (0x010B2400)

  #define DDRDATA8_CR_MASTERDLLCFG_SelRstOvrd_OFF                      (12)
  #define DDRDATA8_CR_MASTERDLLCFG_SelRstOvrd_WID                      ( 1)
  #define DDRDATA8_CR_MASTERDLLCFG_SelRstOvrd_MSK                      (0x00001000)
  #define DDRDATA8_CR_MASTERDLLCFG_SelRstOvrd_MIN                      (0)
  #define DDRDATA8_CR_MASTERDLLCFG_SelRstOvrd_MAX                      (1) // 0x00000001
  #define DDRDATA8_CR_MASTERDLLCFG_SelRstOvrd_DEF                      (0x00000000)
  #define DDRDATA8_CR_MASTERDLLCFG_SelRstOvrd_HSH                      (0x010C2400)

  #define DDRDATA8_CR_MASTERDLLCFG_TimeOutOvrd_OFF                     (13)
  #define DDRDATA8_CR_MASTERDLLCFG_TimeOutOvrd_WID                     ( 1)
  #define DDRDATA8_CR_MASTERDLLCFG_TimeOutOvrd_MSK                     (0x00002000)
  #define DDRDATA8_CR_MASTERDLLCFG_TimeOutOvrd_MIN                     (0)
  #define DDRDATA8_CR_MASTERDLLCFG_TimeOutOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA8_CR_MASTERDLLCFG_TimeOutOvrd_DEF                     (0x00000000)
  #define DDRDATA8_CR_MASTERDLLCFG_TimeOutOvrd_HSH                     (0x010D2400)

  #define DDRDATA8_CR_MASTERDLLCFG_SelTimeOutOvrd_OFF                  (14)
  #define DDRDATA8_CR_MASTERDLLCFG_SelTimeOutOvrd_WID                  ( 1)
  #define DDRDATA8_CR_MASTERDLLCFG_SelTimeOutOvrd_MSK                  (0x00004000)
  #define DDRDATA8_CR_MASTERDLLCFG_SelTimeOutOvrd_MIN                  (0)
  #define DDRDATA8_CR_MASTERDLLCFG_SelTimeOutOvrd_MAX                  (1) // 0x00000001
  #define DDRDATA8_CR_MASTERDLLCFG_SelTimeOutOvrd_DEF                  (0x00000000)
  #define DDRDATA8_CR_MASTERDLLCFG_SelTimeOutOvrd_HSH                  (0x010E2400)

  #define DDRDATA8_CR_MASTERDLLCFG_ClkGateOvrd_OFF                     (15)
  #define DDRDATA8_CR_MASTERDLLCFG_ClkGateOvrd_WID                     ( 1)
  #define DDRDATA8_CR_MASTERDLLCFG_ClkGateOvrd_MSK                     (0x00008000)
  #define DDRDATA8_CR_MASTERDLLCFG_ClkGateOvrd_MIN                     (0)
  #define DDRDATA8_CR_MASTERDLLCFG_ClkGateOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA8_CR_MASTERDLLCFG_ClkGateOvrd_DEF                     (0x00000000)
  #define DDRDATA8_CR_MASTERDLLCFG_ClkGateOvrd_HSH                     (0x010F2400)

  #define DDRDATA8_CR_MASTERDLLCFG_LockOvrd_OFF                        (16)
  #define DDRDATA8_CR_MASTERDLLCFG_LockOvrd_WID                        ( 1)
  #define DDRDATA8_CR_MASTERDLLCFG_LockOvrd_MSK                        (0x00010000)
  #define DDRDATA8_CR_MASTERDLLCFG_LockOvrd_MIN                        (0)
  #define DDRDATA8_CR_MASTERDLLCFG_LockOvrd_MAX                        (1) // 0x00000001
  #define DDRDATA8_CR_MASTERDLLCFG_LockOvrd_DEF                        (0x00000000)
  #define DDRDATA8_CR_MASTERDLLCFG_LockOvrd_HSH                        (0x01102400)

  #define DDRDATA8_CR_MASTERDLLCFG_SelLockOvrd_OFF                     (17)
  #define DDRDATA8_CR_MASTERDLLCFG_SelLockOvrd_WID                     ( 1)
  #define DDRDATA8_CR_MASTERDLLCFG_SelLockOvrd_MSK                     (0x00020000)
  #define DDRDATA8_CR_MASTERDLLCFG_SelLockOvrd_MIN                     (0)
  #define DDRDATA8_CR_MASTERDLLCFG_SelLockOvrd_MAX                     (1) // 0x00000001
  #define DDRDATA8_CR_MASTERDLLCFG_SelLockOvrd_DEF                     (0x00000000)
  #define DDRDATA8_CR_MASTERDLLCFG_SelLockOvrd_HSH                     (0x01112400)

  #define DDRDATA8_CR_MASTERDLLCFG_OpenLoopOvrd_OFF                    (18)
  #define DDRDATA8_CR_MASTERDLLCFG_OpenLoopOvrd_WID                    ( 1)
  #define DDRDATA8_CR_MASTERDLLCFG_OpenLoopOvrd_MSK                    (0x00040000)
  #define DDRDATA8_CR_MASTERDLLCFG_OpenLoopOvrd_MIN                    (0)
  #define DDRDATA8_CR_MASTERDLLCFG_OpenLoopOvrd_MAX                    (1) // 0x00000001
  #define DDRDATA8_CR_MASTERDLLCFG_OpenLoopOvrd_DEF                    (0x00000000)
  #define DDRDATA8_CR_MASTERDLLCFG_OpenLoopOvrd_HSH                    (0x01122400)

  #define DDRDATA8_CR_MASTERDLLCFG_SelOpenLoopOvrd_OFF                 (19)
  #define DDRDATA8_CR_MASTERDLLCFG_SelOpenLoopOvrd_WID                 ( 1)
  #define DDRDATA8_CR_MASTERDLLCFG_SelOpenLoopOvrd_MSK                 (0x00080000)
  #define DDRDATA8_CR_MASTERDLLCFG_SelOpenLoopOvrd_MIN                 (0)
  #define DDRDATA8_CR_MASTERDLLCFG_SelOpenLoopOvrd_MAX                 (1) // 0x00000001
  #define DDRDATA8_CR_MASTERDLLCFG_SelOpenLoopOvrd_DEF                 (0x00000000)
  #define DDRDATA8_CR_MASTERDLLCFG_SelOpenLoopOvrd_HSH                 (0x01132400)

  #define DDRDATA8_CR_MASTERDLLCFG_WkLockEnOvrd_OFF                    (20)
  #define DDRDATA8_CR_MASTERDLLCFG_WkLockEnOvrd_WID                    ( 1)
  #define DDRDATA8_CR_MASTERDLLCFG_WkLockEnOvrd_MSK                    (0x00100000)
  #define DDRDATA8_CR_MASTERDLLCFG_WkLockEnOvrd_MIN                    (0)
  #define DDRDATA8_CR_MASTERDLLCFG_WkLockEnOvrd_MAX                    (1) // 0x00000001
  #define DDRDATA8_CR_MASTERDLLCFG_WkLockEnOvrd_DEF                    (0x00000000)
  #define DDRDATA8_CR_MASTERDLLCFG_WkLockEnOvrd_HSH                    (0x01142400)

  #define DDRDATA8_CR_MASTERDLLCFG_SelWkLockEnOvrd_OFF                 (21)
  #define DDRDATA8_CR_MASTERDLLCFG_SelWkLockEnOvrd_WID                 ( 1)
  #define DDRDATA8_CR_MASTERDLLCFG_SelWkLockEnOvrd_MSK                 (0x00200000)
  #define DDRDATA8_CR_MASTERDLLCFG_SelWkLockEnOvrd_MIN                 (0)
  #define DDRDATA8_CR_MASTERDLLCFG_SelWkLockEnOvrd_MAX                 (1) // 0x00000001
  #define DDRDATA8_CR_MASTERDLLCFG_SelWkLockEnOvrd_DEF                 (0x00000000)
  #define DDRDATA8_CR_MASTERDLLCFG_SelWkLockEnOvrd_HSH                 (0x01152400)

  #define DDRDATA8_CR_MASTERDLLCFG_CfdlDis_OFF                         (22)
  #define DDRDATA8_CR_MASTERDLLCFG_CfdlDis_WID                         ( 1)
  #define DDRDATA8_CR_MASTERDLLCFG_CfdlDis_MSK                         (0x00400000)
  #define DDRDATA8_CR_MASTERDLLCFG_CfdlDis_MIN                         (0)
  #define DDRDATA8_CR_MASTERDLLCFG_CfdlDis_MAX                         (1) // 0x00000001
  #define DDRDATA8_CR_MASTERDLLCFG_CfdlDis_DEF                         (0x00000000)
  #define DDRDATA8_CR_MASTERDLLCFG_CfdlDis_HSH                         (0x01162400)

  #define DDRDATA8_CR_MASTERDLLCFG_DftEn_OFF                           (23)
  #define DDRDATA8_CR_MASTERDLLCFG_DftEn_WID                           ( 1)
  #define DDRDATA8_CR_MASTERDLLCFG_DftEn_MSK                           (0x00800000)
  #define DDRDATA8_CR_MASTERDLLCFG_DftEn_MIN                           (0)
  #define DDRDATA8_CR_MASTERDLLCFG_DftEn_MAX                           (1) // 0x00000001
  #define DDRDATA8_CR_MASTERDLLCFG_DftEn_DEF                           (0x00000000)
  #define DDRDATA8_CR_MASTERDLLCFG_DftEn_HSH                           (0x01172400)

  #define DDRDATA8_CR_MASTERDLLCFG_spare0_OFF                          (24)
  #define DDRDATA8_CR_MASTERDLLCFG_spare0_WID                          ( 8)
  #define DDRDATA8_CR_MASTERDLLCFG_spare0_MSK                          (0xFF000000)
  #define DDRDATA8_CR_MASTERDLLCFG_spare0_MIN                          (0)
  #define DDRDATA8_CR_MASTERDLLCFG_spare0_MAX                          (255) // 0x000000FF
  #define DDRDATA8_CR_MASTERDLLCFG_spare0_DEF                          (0x00000000)
  #define DDRDATA8_CR_MASTERDLLCFG_spare0_HSH                          (0x08182400)

#define DDRDATA8_CR_CBTUNE0_REG                                        (0x00002404)

  #define DDRDATA8_CR_CBTUNE0_DllBWEn_OFF                              ( 0)
  #define DDRDATA8_CR_CBTUNE0_DllBWEn_WID                              (32)
  #define DDRDATA8_CR_CBTUNE0_DllBWEn_MSK                              (0xFFFFFFFF)
  #define DDRDATA8_CR_CBTUNE0_DllBWEn_MIN                              (0)
  #define DDRDATA8_CR_CBTUNE0_DllBWEn_MAX                              (4294967295) // 0xFFFFFFFF
  #define DDRDATA8_CR_CBTUNE0_DllBWEn_DEF                              (0xFDB86521)
  #define DDRDATA8_CR_CBTUNE0_DllBWEn_HSH                              (0x20002404)

#define DDRDATA8_CR_CBTUNE1_REG                                        (0x00002408)

  #define DDRDATA8_CR_CBTUNE1_PiCbEn_OFF                               ( 0)
  #define DDRDATA8_CR_CBTUNE1_PiCbEn_WID                               (24)
  #define DDRDATA8_CR_CBTUNE1_PiCbEn_MSK                               (0x00FFFFFF)
  #define DDRDATA8_CR_CBTUNE1_PiCbEn_MIN                               (0)
  #define DDRDATA8_CR_CBTUNE1_PiCbEn_MAX                               (16777215) // 0x00FFFFFF
  #define DDRDATA8_CR_CBTUNE1_PiCbEn_DEF                               (0x00249492)
  #define DDRDATA8_CR_CBTUNE1_PiCbEn_HSH                               (0x18002408)

  #define DDRDATA8_CR_CBTUNE1_CbEnRsvd_OFF                             (24)
  #define DDRDATA8_CR_CBTUNE1_CbEnRsvd_WID                             ( 3)
  #define DDRDATA8_CR_CBTUNE1_CbEnRsvd_MSK                             (0x07000000)
  #define DDRDATA8_CR_CBTUNE1_CbEnRsvd_MIN                             (0)
  #define DDRDATA8_CR_CBTUNE1_CbEnRsvd_MAX                             (7) // 0x00000007
  #define DDRDATA8_CR_CBTUNE1_CbEnRsvd_DEF                             (0x00000000)
  #define DDRDATA8_CR_CBTUNE1_CbEnRsvd_HSH                             (0x03182408)

  #define DDRDATA8_CR_CBTUNE1_CbEnDllFuse_OFF                          (27)
  #define DDRDATA8_CR_CBTUNE1_CbEnDllFuse_WID                          ( 3)
  #define DDRDATA8_CR_CBTUNE1_CbEnDllFuse_MSK                          (0x38000000)
  #define DDRDATA8_CR_CBTUNE1_CbEnDllFuse_MIN                          (0)
  #define DDRDATA8_CR_CBTUNE1_CbEnDllFuse_MAX                          (7) // 0x00000007
  #define DDRDATA8_CR_CBTUNE1_CbEnDllFuse_DEF                          (0x00000002)
  #define DDRDATA8_CR_CBTUNE1_CbEnDllFuse_HSH                          (0x031B2408)

  #define DDRDATA8_CR_CBTUNE1_Spare_OFF                                (30)
  #define DDRDATA8_CR_CBTUNE1_Spare_WID                                ( 2)
  #define DDRDATA8_CR_CBTUNE1_Spare_MSK                                (0xC0000000)
  #define DDRDATA8_CR_CBTUNE1_Spare_MIN                                (0)
  #define DDRDATA8_CR_CBTUNE1_Spare_MAX                                (3) // 0x00000003
  #define DDRDATA8_CR_CBTUNE1_Spare_DEF                                (0x00000000)
  #define DDRDATA8_CR_CBTUNE1_Spare_HSH                                (0x021E2408)

#define DDRDATA8_CR_ADCCFG_REG                                         (0x0000240C)

  #define DDRDATA8_CR_ADCCFG_ADC_frz_OFF                               ( 0)
  #define DDRDATA8_CR_ADCCFG_ADC_frz_WID                               ( 1)
  #define DDRDATA8_CR_ADCCFG_ADC_frz_MSK                               (0x00000001)
  #define DDRDATA8_CR_ADCCFG_ADC_frz_MIN                               (0)
  #define DDRDATA8_CR_ADCCFG_ADC_frz_MAX                               (1) // 0x00000001
  #define DDRDATA8_CR_ADCCFG_ADC_frz_DEF                               (0x00000000)
  #define DDRDATA8_CR_ADCCFG_ADC_frz_HSH                               (0x0100240C)

  #define DDRDATA8_CR_ADCCFG_ADC_en_OFF                                ( 1)
  #define DDRDATA8_CR_ADCCFG_ADC_en_WID                                ( 1)
  #define DDRDATA8_CR_ADCCFG_ADC_en_MSK                                (0x00000002)
  #define DDRDATA8_CR_ADCCFG_ADC_en_MIN                                (0)
  #define DDRDATA8_CR_ADCCFG_ADC_en_MAX                                (1) // 0x00000001
  #define DDRDATA8_CR_ADCCFG_ADC_en_DEF                                (0x00000000)
  #define DDRDATA8_CR_ADCCFG_ADC_en_HSH                                (0x0101240C)

  #define DDRDATA8_CR_ADCCFG_ADCclkdiv_OFF                             ( 2)
  #define DDRDATA8_CR_ADCCFG_ADCclkdiv_WID                             ( 2)
  #define DDRDATA8_CR_ADCCFG_ADCclkdiv_MSK                             (0x0000000C)
  #define DDRDATA8_CR_ADCCFG_ADCclkdiv_MIN                             (0)
  #define DDRDATA8_CR_ADCCFG_ADCclkdiv_MAX                             (3) // 0x00000003
  #define DDRDATA8_CR_ADCCFG_ADCclkdiv_DEF                             (0x00000000)
  #define DDRDATA8_CR_ADCCFG_ADCclkdiv_HSH                             (0x0202240C)

  #define DDRDATA8_CR_ADCCFG_ADCstartcount_OFF                         ( 4)
  #define DDRDATA8_CR_ADCCFG_ADCstartcount_WID                         ( 2)
  #define DDRDATA8_CR_ADCCFG_ADCstartcount_MSK                         (0x00000030)
  #define DDRDATA8_CR_ADCCFG_ADCstartcount_MIN                         (0)
  #define DDRDATA8_CR_ADCCFG_ADCstartcount_MAX                         (3) // 0x00000003
  #define DDRDATA8_CR_ADCCFG_ADCstartcount_DEF                         (0x00000000)
  #define DDRDATA8_CR_ADCCFG_ADCstartcount_HSH                         (0x0204240C)

  #define DDRDATA8_CR_ADCCFG_ADCChopEn_OFF                             ( 6)
  #define DDRDATA8_CR_ADCCFG_ADCChopEn_WID                             ( 1)
  #define DDRDATA8_CR_ADCCFG_ADCChopEn_MSK                             (0x00000040)
  #define DDRDATA8_CR_ADCCFG_ADCChopEn_MIN                             (0)
  #define DDRDATA8_CR_ADCCFG_ADCChopEn_MAX                             (1) // 0x00000001
  #define DDRDATA8_CR_ADCCFG_ADCChopEn_DEF                             (0x00000000)
  #define DDRDATA8_CR_ADCCFG_ADCChopEn_HSH                             (0x0106240C)

  #define DDRDATA8_CR_ADCCFG_Spare_OFF                                 ( 7)
  #define DDRDATA8_CR_ADCCFG_Spare_WID                                 (25)
  #define DDRDATA8_CR_ADCCFG_Spare_MSK                                 (0xFFFFFF80)
  #define DDRDATA8_CR_ADCCFG_Spare_MIN                                 (0)
  #define DDRDATA8_CR_ADCCFG_Spare_MAX                                 (33554431) // 0x01FFFFFF
  #define DDRDATA8_CR_ADCCFG_Spare_DEF                                 (0x00000000)
  #define DDRDATA8_CR_ADCCFG_Spare_HSH                                 (0x1907240C)

#define DDRDATA8_CR_CBTUNE2_REG                                        (0x00002410)

  #define DDRDATA8_CR_CBTUNE2_DllCbEn_OFF                              ( 0)
  #define DDRDATA8_CR_CBTUNE2_DllCbEn_WID                              (16)
  #define DDRDATA8_CR_CBTUNE2_DllCbEn_MSK                              (0x0000FFFF)
  #define DDRDATA8_CR_CBTUNE2_DllCbEn_MIN                              (0)
  #define DDRDATA8_CR_CBTUNE2_DllCbEn_MAX                              (65535) // 0x0000FFFF
  #define DDRDATA8_CR_CBTUNE2_DllCbEn_DEF                              (0x00000000)
  #define DDRDATA8_CR_CBTUNE2_DllCbEn_HSH                              (0x10002410)

  #define DDRDATA8_CR_CBTUNE2_Spare_OFF                                (16)
  #define DDRDATA8_CR_CBTUNE2_Spare_WID                                (16)
  #define DDRDATA8_CR_CBTUNE2_Spare_MSK                                (0xFFFF0000)
  #define DDRDATA8_CR_CBTUNE2_Spare_MIN                                (0)
  #define DDRDATA8_CR_CBTUNE2_Spare_MAX                                (65535) // 0x0000FFFF
  #define DDRDATA8_CR_CBTUNE2_Spare_DEF                                (0x00000000)
  #define DDRDATA8_CR_CBTUNE2_Spare_HSH                                (0x10102410)

#define DDRDATA8_CR_PIDFTDLY_REG                                       (0x00002418)

  #define DDRDATA8_CR_PIDFTDLY_PiDftDelay_OFF                          ( 0)
  #define DDRDATA8_CR_PIDFTDLY_PiDftDelay_WID                          ( 7)
  #define DDRDATA8_CR_PIDFTDLY_PiDftDelay_MSK                          (0x0000007F)
  #define DDRDATA8_CR_PIDFTDLY_PiDftDelay_MIN                          (0)
  #define DDRDATA8_CR_PIDFTDLY_PiDftDelay_MAX                          (127) // 0x0000007F
  #define DDRDATA8_CR_PIDFTDLY_PiDftDelay_DEF                          (0x00000000)
  #define DDRDATA8_CR_PIDFTDLY_PiDftDelay_HSH                          (0x07002418)

  #define DDRDATA8_CR_PIDFTDLY_Ch0PiEnOvrd_OFF                         ( 7)
  #define DDRDATA8_CR_PIDFTDLY_Ch0PiEnOvrd_WID                         ( 1)
  #define DDRDATA8_CR_PIDFTDLY_Ch0PiEnOvrd_MSK                         (0x00000080)
  #define DDRDATA8_CR_PIDFTDLY_Ch0PiEnOvrd_MIN                         (0)
  #define DDRDATA8_CR_PIDFTDLY_Ch0PiEnOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA8_CR_PIDFTDLY_Ch0PiEnOvrd_DEF                         (0x00000000)
  #define DDRDATA8_CR_PIDFTDLY_Ch0PiEnOvrd_HSH                         (0x01072418)

  #define DDRDATA8_CR_PIDFTDLY_Ch1PiEnOvrd_OFF                         ( 8)
  #define DDRDATA8_CR_PIDFTDLY_Ch1PiEnOvrd_WID                         ( 1)
  #define DDRDATA8_CR_PIDFTDLY_Ch1PiEnOvrd_MSK                         (0x00000100)
  #define DDRDATA8_CR_PIDFTDLY_Ch1PiEnOvrd_MIN                         (0)
  #define DDRDATA8_CR_PIDFTDLY_Ch1PiEnOvrd_MAX                         (1) // 0x00000001
  #define DDRDATA8_CR_PIDFTDLY_Ch1PiEnOvrd_DEF                         (0x00000000)
  #define DDRDATA8_CR_PIDFTDLY_Ch1PiEnOvrd_HSH                         (0x01082418)

  #define DDRDATA8_CR_PIDFTDLY_Ch0PiDFTEn_OFF                          ( 9)
  #define DDRDATA8_CR_PIDFTDLY_Ch0PiDFTEn_WID                          ( 1)
  #define DDRDATA8_CR_PIDFTDLY_Ch0PiDFTEn_MSK                          (0x00000200)
  #define DDRDATA8_CR_PIDFTDLY_Ch0PiDFTEn_MIN                          (0)
  #define DDRDATA8_CR_PIDFTDLY_Ch0PiDFTEn_MAX                          (1) // 0x00000001
  #define DDRDATA8_CR_PIDFTDLY_Ch0PiDFTEn_DEF                          (0x00000000)
  #define DDRDATA8_CR_PIDFTDLY_Ch0PiDFTEn_HSH                          (0x01092418)

  #define DDRDATA8_CR_PIDFTDLY_Ch1PiDFTEn_OFF                          (10)
  #define DDRDATA8_CR_PIDFTDLY_Ch1PiDFTEn_WID                          ( 1)
  #define DDRDATA8_CR_PIDFTDLY_Ch1PiDFTEn_MSK                          (0x00000400)
  #define DDRDATA8_CR_PIDFTDLY_Ch1PiDFTEn_MIN                          (0)
  #define DDRDATA8_CR_PIDFTDLY_Ch1PiDFTEn_MAX                          (1) // 0x00000001
  #define DDRDATA8_CR_PIDFTDLY_Ch1PiDFTEn_DEF                          (0x00000000)
  #define DDRDATA8_CR_PIDFTDLY_Ch1PiDFTEn_HSH                          (0x010A2418)

  #define DDRDATA8_CR_PIDFTDLY_Spare_OFF                               (11)
  #define DDRDATA8_CR_PIDFTDLY_Spare_WID                               ( 4)
  #define DDRDATA8_CR_PIDFTDLY_Spare_MSK                               (0x00007800)
  #define DDRDATA8_CR_PIDFTDLY_Spare_MIN                               (0)
  #define DDRDATA8_CR_PIDFTDLY_Spare_MAX                               (15) // 0x0000000F
  #define DDRDATA8_CR_PIDFTDLY_Spare_DEF                               (0x00000000)
  #define DDRDATA8_CR_PIDFTDLY_Spare_HSH                               (0x040B2418)

  #define DDRDATA8_CR_PIDFTDLY_RefPiOvrd_OFF                           (15)
  #define DDRDATA8_CR_PIDFTDLY_RefPiOvrd_WID                           ( 1)
  #define DDRDATA8_CR_PIDFTDLY_RefPiOvrd_MSK                           (0x00008000)
  #define DDRDATA8_CR_PIDFTDLY_RefPiOvrd_MIN                           (0)
  #define DDRDATA8_CR_PIDFTDLY_RefPiOvrd_MAX                           (1) // 0x00000001
  #define DDRDATA8_CR_PIDFTDLY_RefPiOvrd_DEF                           (0x00000000)
  #define DDRDATA8_CR_PIDFTDLY_RefPiOvrd_HSH                           (0x010F2418)

  #define DDRDATA8_CR_PIDFTDLY_Rsvd_OFF                                (16)
  #define DDRDATA8_CR_PIDFTDLY_Rsvd_WID                                (16)
  #define DDRDATA8_CR_PIDFTDLY_Rsvd_MSK                                (0xFFFF0000)
  #define DDRDATA8_CR_PIDFTDLY_Rsvd_MIN                                (0)
  #define DDRDATA8_CR_PIDFTDLY_Rsvd_MAX                                (65535) // 0x0000FFFF
  #define DDRDATA8_CR_PIDFTDLY_Rsvd_DEF                                (0x00000000)
  #define DDRDATA8_CR_PIDFTDLY_Rsvd_HSH                                (0x10102418)

#define DDRDATA8_CR_DLLPITESTANDADC_REG                                (0x0000241C)

  #define DDRDATA8_CR_DLLPITESTANDADC_RunTest_OFF                      ( 0)
  #define DDRDATA8_CR_DLLPITESTANDADC_RunTest_WID                      ( 1)
  #define DDRDATA8_CR_DLLPITESTANDADC_RunTest_MSK                      (0x00000001)
  #define DDRDATA8_CR_DLLPITESTANDADC_RunTest_MIN                      (0)
  #define DDRDATA8_CR_DLLPITESTANDADC_RunTest_MAX                      (1) // 0x00000001
  #define DDRDATA8_CR_DLLPITESTANDADC_RunTest_DEF                      (0x00000000)
  #define DDRDATA8_CR_DLLPITESTANDADC_RunTest_HSH                      (0x0100241C)

  #define DDRDATA8_CR_DLLPITESTANDADC_Load_OFF                         ( 1)
  #define DDRDATA8_CR_DLLPITESTANDADC_Load_WID                         ( 1)
  #define DDRDATA8_CR_DLLPITESTANDADC_Load_MSK                         (0x00000002)
  #define DDRDATA8_CR_DLLPITESTANDADC_Load_MIN                         (0)
  #define DDRDATA8_CR_DLLPITESTANDADC_Load_MAX                         (1) // 0x00000001
  #define DDRDATA8_CR_DLLPITESTANDADC_Load_DEF                         (0x00000000)
  #define DDRDATA8_CR_DLLPITESTANDADC_Load_HSH                         (0x0101241C)

  #define DDRDATA8_CR_DLLPITESTANDADC_ModeHVM_OFF                      ( 2)
  #define DDRDATA8_CR_DLLPITESTANDADC_ModeHVM_WID                      ( 1)
  #define DDRDATA8_CR_DLLPITESTANDADC_ModeHVM_MSK                      (0x00000004)
  #define DDRDATA8_CR_DLLPITESTANDADC_ModeHVM_MIN                      (0)
  #define DDRDATA8_CR_DLLPITESTANDADC_ModeHVM_MAX                      (1) // 0x00000001
  #define DDRDATA8_CR_DLLPITESTANDADC_ModeHVM_DEF                      (0x00000000)
  #define DDRDATA8_CR_DLLPITESTANDADC_ModeHVM_HSH                      (0x0102241C)

  #define DDRDATA8_CR_DLLPITESTANDADC_ModeDV_OFF                       ( 3)
  #define DDRDATA8_CR_DLLPITESTANDADC_ModeDV_WID                       ( 1)
  #define DDRDATA8_CR_DLLPITESTANDADC_ModeDV_MSK                       (0x00000008)
  #define DDRDATA8_CR_DLLPITESTANDADC_ModeDV_MIN                       (0)
  #define DDRDATA8_CR_DLLPITESTANDADC_ModeDV_MAX                       (1) // 0x00000001
  #define DDRDATA8_CR_DLLPITESTANDADC_ModeDV_DEF                       (0x00000000)
  #define DDRDATA8_CR_DLLPITESTANDADC_ModeDV_HSH                       (0x0103241C)

  #define DDRDATA8_CR_DLLPITESTANDADC_CalCfdl_OFF                      ( 4)
  #define DDRDATA8_CR_DLLPITESTANDADC_CalCfdl_WID                      ( 1)
  #define DDRDATA8_CR_DLLPITESTANDADC_CalCfdl_MSK                      (0x00000010)
  #define DDRDATA8_CR_DLLPITESTANDADC_CalCfdl_MIN                      (0)
  #define DDRDATA8_CR_DLLPITESTANDADC_CalCfdl_MAX                      (1) // 0x00000001
  #define DDRDATA8_CR_DLLPITESTANDADC_CalCfdl_DEF                      (0x00000000)
  #define DDRDATA8_CR_DLLPITESTANDADC_CalCfdl_HSH                      (0x0104241C)

  #define DDRDATA8_CR_DLLPITESTANDADC_LoadCount_OFF                    ( 5)
  #define DDRDATA8_CR_DLLPITESTANDADC_LoadCount_WID                    (10)
  #define DDRDATA8_CR_DLLPITESTANDADC_LoadCount_MSK                    (0x00007FE0)
  #define DDRDATA8_CR_DLLPITESTANDADC_LoadCount_MIN                    (0)
  #define DDRDATA8_CR_DLLPITESTANDADC_LoadCount_MAX                    (1023) // 0x000003FF
  #define DDRDATA8_CR_DLLPITESTANDADC_LoadCount_DEF                    (0x00000000)
  #define DDRDATA8_CR_DLLPITESTANDADC_LoadCount_HSH                    (0x0A05241C)

  #define DDRDATA8_CR_DLLPITESTANDADC_CountStatus_OFF                  (15)
  #define DDRDATA8_CR_DLLPITESTANDADC_CountStatus_WID                  (10)
  #define DDRDATA8_CR_DLLPITESTANDADC_CountStatus_MSK                  (0x01FF8000)
  #define DDRDATA8_CR_DLLPITESTANDADC_CountStatus_MIN                  (0)
  #define DDRDATA8_CR_DLLPITESTANDADC_CountStatus_MAX                  (1023) // 0x000003FF
  #define DDRDATA8_CR_DLLPITESTANDADC_CountStatus_DEF                  (0x00000000)
  #define DDRDATA8_CR_DLLPITESTANDADC_CountStatus_HSH                  (0x0A0F241C)

  #define DDRDATA8_CR_DLLPITESTANDADC_ModeADC_OFF                      (25)
  #define DDRDATA8_CR_DLLPITESTANDADC_ModeADC_WID                      ( 1)
  #define DDRDATA8_CR_DLLPITESTANDADC_ModeADC_MSK                      (0x02000000)
  #define DDRDATA8_CR_DLLPITESTANDADC_ModeADC_MIN                      (0)
  #define DDRDATA8_CR_DLLPITESTANDADC_ModeADC_MAX                      (1) // 0x00000001
  #define DDRDATA8_CR_DLLPITESTANDADC_ModeADC_DEF                      (0x00000000)
  #define DDRDATA8_CR_DLLPITESTANDADC_ModeADC_HSH                      (0x0119241C)

  #define DDRDATA8_CR_DLLPITESTANDADC_ADCClkDiv_OFF                    (26)
  #define DDRDATA8_CR_DLLPITESTANDADC_ADCClkDiv_WID                    ( 2)
  #define DDRDATA8_CR_DLLPITESTANDADC_ADCClkDiv_MSK                    (0x0C000000)
  #define DDRDATA8_CR_DLLPITESTANDADC_ADCClkDiv_MIN                    (0)
  #define DDRDATA8_CR_DLLPITESTANDADC_ADCClkDiv_MAX                    (3) // 0x00000003
  #define DDRDATA8_CR_DLLPITESTANDADC_ADCClkDiv_DEF                    (0x00000000)
  #define DDRDATA8_CR_DLLPITESTANDADC_ADCClkDiv_HSH                    (0x021A241C)

  #define DDRDATA8_CR_DLLPITESTANDADC_ADCDdrChanSel_OFF                (28)
  #define DDRDATA8_CR_DLLPITESTANDADC_ADCDdrChanSel_WID                ( 1)
  #define DDRDATA8_CR_DLLPITESTANDADC_ADCDdrChanSel_MSK                (0x10000000)
  #define DDRDATA8_CR_DLLPITESTANDADC_ADCDdrChanSel_MIN                (0)
  #define DDRDATA8_CR_DLLPITESTANDADC_ADCDdrChanSel_MAX                (1) // 0x00000001
  #define DDRDATA8_CR_DLLPITESTANDADC_ADCDdrChanSel_DEF                (0x00000000)
  #define DDRDATA8_CR_DLLPITESTANDADC_ADCDdrChanSel_HSH                (0x011C241C)

  #define DDRDATA8_CR_DLLPITESTANDADC_ADCChopEn_OFF                    (29)
  #define DDRDATA8_CR_DLLPITESTANDADC_ADCChopEn_WID                    ( 1)
  #define DDRDATA8_CR_DLLPITESTANDADC_ADCChopEn_MSK                    (0x20000000)
  #define DDRDATA8_CR_DLLPITESTANDADC_ADCChopEn_MIN                    (0)
  #define DDRDATA8_CR_DLLPITESTANDADC_ADCChopEn_MAX                    (1) // 0x00000001
  #define DDRDATA8_CR_DLLPITESTANDADC_ADCChopEn_DEF                    (0x00000000)
  #define DDRDATA8_CR_DLLPITESTANDADC_ADCChopEn_HSH                    (0x011D241C)

  #define DDRDATA8_CR_DLLPITESTANDADC_ADCDone_OFF                      (30)
  #define DDRDATA8_CR_DLLPITESTANDADC_ADCDone_WID                      ( 1)
  #define DDRDATA8_CR_DLLPITESTANDADC_ADCDone_MSK                      (0x40000000)
  #define DDRDATA8_CR_DLLPITESTANDADC_ADCDone_MIN                      (0)
  #define DDRDATA8_CR_DLLPITESTANDADC_ADCDone_MAX                      (1) // 0x00000001
  #define DDRDATA8_CR_DLLPITESTANDADC_ADCDone_DEF                      (0x00000000)
  #define DDRDATA8_CR_DLLPITESTANDADC_ADCDone_HSH                      (0x011E241C)

  #define DDRDATA8_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF             (31)
  #define DDRDATA8_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID             ( 1)
  #define DDRDATA8_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK             (0x80000000)
  #define DDRDATA8_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN             (0)
  #define DDRDATA8_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX             (1) // 0x00000001
  #define DDRDATA8_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF             (0x00000000)
  #define DDRDATA8_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH             (0x011F241C)

#define DDRDATA8_CR_DLLSTATUS_REG                                      (0x00002420)

  #define DDRDATA8_CR_DLLSTATUS_DetrmLockStat_OFF                      ( 0)
  #define DDRDATA8_CR_DLLSTATUS_DetrmLockStat_WID                      ( 1)
  #define DDRDATA8_CR_DLLSTATUS_DetrmLockStat_MSK                      (0x00000001)
  #define DDRDATA8_CR_DLLSTATUS_DetrmLockStat_MIN                      (0)
  #define DDRDATA8_CR_DLLSTATUS_DetrmLockStat_MAX                      (1) // 0x00000001
  #define DDRDATA8_CR_DLLSTATUS_DetrmLockStat_DEF                      (0x00000000)
  #define DDRDATA8_CR_DLLSTATUS_DetrmLockStat_HSH                      (0x01002420)

  #define DDRDATA8_CR_DLLSTATUS_FuncLockStat_OFF                       ( 1)
  #define DDRDATA8_CR_DLLSTATUS_FuncLockStat_WID                       ( 1)
  #define DDRDATA8_CR_DLLSTATUS_FuncLockStat_MSK                       (0x00000002)
  #define DDRDATA8_CR_DLLSTATUS_FuncLockStat_MIN                       (0)
  #define DDRDATA8_CR_DLLSTATUS_FuncLockStat_MAX                       (1) // 0x00000001
  #define DDRDATA8_CR_DLLSTATUS_FuncLockStat_DEF                       (0x00000000)
  #define DDRDATA8_CR_DLLSTATUS_FuncLockStat_HSH                       (0x01012420)

  #define DDRDATA8_CR_DLLSTATUS_Lock_OFF                               ( 2)
  #define DDRDATA8_CR_DLLSTATUS_Lock_WID                               ( 1)
  #define DDRDATA8_CR_DLLSTATUS_Lock_MSK                               (0x00000004)
  #define DDRDATA8_CR_DLLSTATUS_Lock_MIN                               (0)
  #define DDRDATA8_CR_DLLSTATUS_Lock_MAX                               (1) // 0x00000001
  #define DDRDATA8_CR_DLLSTATUS_Lock_DEF                               (0x00000000)
  #define DDRDATA8_CR_DLLSTATUS_Lock_HSH                               (0x01022420)

  #define DDRDATA8_CR_DLLSTATUS_Timeout_OFF                            ( 3)
  #define DDRDATA8_CR_DLLSTATUS_Timeout_WID                            ( 1)
  #define DDRDATA8_CR_DLLSTATUS_Timeout_MSK                            (0x00000008)
  #define DDRDATA8_CR_DLLSTATUS_Timeout_MIN                            (0)
  #define DDRDATA8_CR_DLLSTATUS_Timeout_MAX                            (1) // 0x00000001
  #define DDRDATA8_CR_DLLSTATUS_Timeout_DEF                            (0x00000000)
  #define DDRDATA8_CR_DLLSTATUS_Timeout_HSH                            (0x01032420)

  #define DDRDATA8_CR_DLLSTATUS_DllReset_OFF                           ( 4)
  #define DDRDATA8_CR_DLLSTATUS_DllReset_WID                           ( 1)
  #define DDRDATA8_CR_DLLSTATUS_DllReset_MSK                           (0x00000010)
  #define DDRDATA8_CR_DLLSTATUS_DllReset_MIN                           (0)
  #define DDRDATA8_CR_DLLSTATUS_DllReset_MAX                           (1) // 0x00000001
  #define DDRDATA8_CR_DLLSTATUS_DllReset_DEF                           (0x00000000)
  #define DDRDATA8_CR_DLLSTATUS_DllReset_HSH                           (0x01042420)

  #define DDRDATA8_CR_DLLSTATUS_LongLockStat_OFF                       ( 5)
  #define DDRDATA8_CR_DLLSTATUS_LongLockStat_WID                       ( 1)
  #define DDRDATA8_CR_DLLSTATUS_LongLockStat_MSK                       (0x00000020)
  #define DDRDATA8_CR_DLLSTATUS_LongLockStat_MIN                       (0)
  #define DDRDATA8_CR_DLLSTATUS_LongLockStat_MAX                       (1) // 0x00000001
  #define DDRDATA8_CR_DLLSTATUS_LongLockStat_DEF                       (0x00000000)
  #define DDRDATA8_CR_DLLSTATUS_LongLockStat_HSH                       (0x01052420)

  #define DDRDATA8_CR_DLLSTATUS_EarlyLockStat_OFF                      ( 6)
  #define DDRDATA8_CR_DLLSTATUS_EarlyLockStat_WID                      ( 1)
  #define DDRDATA8_CR_DLLSTATUS_EarlyLockStat_MSK                      (0x00000040)
  #define DDRDATA8_CR_DLLSTATUS_EarlyLockStat_MIN                      (0)
  #define DDRDATA8_CR_DLLSTATUS_EarlyLockStat_MAX                      (1) // 0x00000001
  #define DDRDATA8_CR_DLLSTATUS_EarlyLockStat_DEF                      (0x00000000)
  #define DDRDATA8_CR_DLLSTATUS_EarlyLockStat_HSH                      (0x01062420)

  #define DDRDATA8_CR_DLLSTATUS_NormalMode_NotWkLock_OFF               ( 7)
  #define DDRDATA8_CR_DLLSTATUS_NormalMode_NotWkLock_WID               ( 1)
  #define DDRDATA8_CR_DLLSTATUS_NormalMode_NotWkLock_MSK               (0x00000080)
  #define DDRDATA8_CR_DLLSTATUS_NormalMode_NotWkLock_MIN               (0)
  #define DDRDATA8_CR_DLLSTATUS_NormalMode_NotWkLock_MAX               (1) // 0x00000001
  #define DDRDATA8_CR_DLLSTATUS_NormalMode_NotWkLock_DEF               (0x00000000)
  #define DDRDATA8_CR_DLLSTATUS_NormalMode_NotWkLock_HSH               (0x01072420)

  #define DDRDATA8_CR_DLLSTATUS_ADCout_OFF                             ( 8)
  #define DDRDATA8_CR_DLLSTATUS_ADCout_WID                             (10)
  #define DDRDATA8_CR_DLLSTATUS_ADCout_MSK                             (0x0003FF00)
  #define DDRDATA8_CR_DLLSTATUS_ADCout_MIN                             (0)
  #define DDRDATA8_CR_DLLSTATUS_ADCout_MAX                             (1023) // 0x000003FF
  #define DDRDATA8_CR_DLLSTATUS_ADCout_DEF                             (0x00000000)
  #define DDRDATA8_CR_DLLSTATUS_ADCout_HSH                             (0x0A082420)

  #define DDRDATA8_CR_DLLSTATUS_ADCStatus_OFF                          (18)
  #define DDRDATA8_CR_DLLSTATUS_ADCStatus_WID                          ( 1)
  #define DDRDATA8_CR_DLLSTATUS_ADCStatus_MSK                          (0x00040000)
  #define DDRDATA8_CR_DLLSTATUS_ADCStatus_MIN                          (0)
  #define DDRDATA8_CR_DLLSTATUS_ADCStatus_MAX                          (1) // 0x00000001
  #define DDRDATA8_CR_DLLSTATUS_ADCStatus_DEF                          (0x00000000)
  #define DDRDATA8_CR_DLLSTATUS_ADCStatus_HSH                          (0x01122420)

  #define DDRDATA8_CR_DLLSTATUS_pilags_OFF                             (19)
  #define DDRDATA8_CR_DLLSTATUS_pilags_WID                             ( 1)
  #define DDRDATA8_CR_DLLSTATUS_pilags_MSK                             (0x00080000)
  #define DDRDATA8_CR_DLLSTATUS_pilags_MIN                             (0)
  #define DDRDATA8_CR_DLLSTATUS_pilags_MAX                             (1) // 0x00000001
  #define DDRDATA8_CR_DLLSTATUS_pilags_DEF                             (0x00000000)
  #define DDRDATA8_CR_DLLSTATUS_pilags_HSH                             (0x01132420)

  #define DDRDATA8_CR_DLLSTATUS_spare_OFF                              (20)
  #define DDRDATA8_CR_DLLSTATUS_spare_WID                              (12)
  #define DDRDATA8_CR_DLLSTATUS_spare_MSK                              (0xFFF00000)
  #define DDRDATA8_CR_DLLSTATUS_spare_MIN                              (0)
  #define DDRDATA8_CR_DLLSTATUS_spare_MAX                              (4095) // 0x00000FFF
  #define DDRDATA8_CR_DLLSTATUS_spare_DEF                              (0x00000000)
  #define DDRDATA8_CR_DLLSTATUS_spare_HSH                              (0x0C142420)

#define DDRDATA8_CR_DLLDCMCTL_REG                                      (0x00002424)

  #define DDRDATA8_CR_DLLDCMCTL_start_OFF                              ( 0)
  #define DDRDATA8_CR_DLLDCMCTL_start_WID                              ( 1)
  #define DDRDATA8_CR_DLLDCMCTL_start_MSK                              (0x00000001)
  #define DDRDATA8_CR_DLLDCMCTL_start_MIN                              (0)
  #define DDRDATA8_CR_DLLDCMCTL_start_MAX                              (1) // 0x00000001
  #define DDRDATA8_CR_DLLDCMCTL_start_DEF                              (0x00000000)
  #define DDRDATA8_CR_DLLDCMCTL_start_HSH                              (0x01002424)

  #define DDRDATA8_CR_DLLDCMCTL_clken_OFF                              ( 1)
  #define DDRDATA8_CR_DLLDCMCTL_clken_WID                              ( 1)
  #define DDRDATA8_CR_DLLDCMCTL_clken_MSK                              (0x00000002)
  #define DDRDATA8_CR_DLLDCMCTL_clken_MIN                              (0)
  #define DDRDATA8_CR_DLLDCMCTL_clken_MAX                              (1) // 0x00000001
  #define DDRDATA8_CR_DLLDCMCTL_clken_DEF                              (0x00000000)
  #define DDRDATA8_CR_DLLDCMCTL_clken_HSH                              (0x01012424)

  #define DDRDATA8_CR_DLLDCMCTL_dcm_dccctl_en_OFF                      ( 2)
  #define DDRDATA8_CR_DLLDCMCTL_dcm_dccctl_en_WID                      ( 1)
  #define DDRDATA8_CR_DLLDCMCTL_dcm_dccctl_en_MSK                      (0x00000004)
  #define DDRDATA8_CR_DLLDCMCTL_dcm_dccctl_en_MIN                      (0)
  #define DDRDATA8_CR_DLLDCMCTL_dcm_dccctl_en_MAX                      (1) // 0x00000001
  #define DDRDATA8_CR_DLLDCMCTL_dcm_dccctl_en_DEF                      (0x00000000)
  #define DDRDATA8_CR_DLLDCMCTL_dcm_dccctl_en_HSH                      (0x01022424)

  #define DDRDATA8_CR_DLLDCMCTL_dccctl_OFF                             ( 3)
  #define DDRDATA8_CR_DLLDCMCTL_dccctl_WID                             ( 4)
  #define DDRDATA8_CR_DLLDCMCTL_dccctl_MSK                             (0x00000078)
  #define DDRDATA8_CR_DLLDCMCTL_dccctl_MIN                             (0)
  #define DDRDATA8_CR_DLLDCMCTL_dccctl_MAX                             (15) // 0x0000000F
  #define DDRDATA8_CR_DLLDCMCTL_dccctl_DEF                             (0x00000000)
  #define DDRDATA8_CR_DLLDCMCTL_dccctl_HSH                             (0x04032424)

  #define DDRDATA8_CR_DLLDCMCTL_duration_OFF                           ( 7)
  #define DDRDATA8_CR_DLLDCMCTL_duration_WID                           ( 3)
  #define DDRDATA8_CR_DLLDCMCTL_duration_MSK                           (0x00000380)
  #define DDRDATA8_CR_DLLDCMCTL_duration_MIN                           (0)
  #define DDRDATA8_CR_DLLDCMCTL_duration_MAX                           (7) // 0x00000007
  #define DDRDATA8_CR_DLLDCMCTL_duration_DEF                           (0x00000000)
  #define DDRDATA8_CR_DLLDCMCTL_duration_HSH                           (0x03072424)

  #define DDRDATA8_CR_DLLDCMCTL_dcm_done_OFF                           (10)
  #define DDRDATA8_CR_DLLDCMCTL_dcm_done_WID                           ( 1)
  #define DDRDATA8_CR_DLLDCMCTL_dcm_done_MSK                           (0x00000400)
  #define DDRDATA8_CR_DLLDCMCTL_dcm_done_MIN                           (0)
  #define DDRDATA8_CR_DLLDCMCTL_dcm_done_MAX                           (1) // 0x00000001
  #define DDRDATA8_CR_DLLDCMCTL_dcm_done_DEF                           (0x00000000)
  #define DDRDATA8_CR_DLLDCMCTL_dcm_done_HSH                           (0x010A2424)

  #define DDRDATA8_CR_DLLDCMCTL_dcm_results_OFF                        (11)
  #define DDRDATA8_CR_DLLDCMCTL_dcm_results_WID                        (15)
  #define DDRDATA8_CR_DLLDCMCTL_dcm_results_MSK                        (0x03FFF800)
  #define DDRDATA8_CR_DLLDCMCTL_dcm_results_MIN                        (0)
  #define DDRDATA8_CR_DLLDCMCTL_dcm_results_MAX                        (32767) // 0x00007FFF
  #define DDRDATA8_CR_DLLDCMCTL_dcm_results_DEF                        (0x00000000)
  #define DDRDATA8_CR_DLLDCMCTL_dcm_results_HSH                        (0x0F0B2424)

  #define DDRDATA8_CR_DLLDCMCTL_spare0_OFF                             (26)
  #define DDRDATA8_CR_DLLDCMCTL_spare0_WID                             ( 6)
  #define DDRDATA8_CR_DLLDCMCTL_spare0_MSK                             (0xFC000000)
  #define DDRDATA8_CR_DLLDCMCTL_spare0_MIN                             (0)
  #define DDRDATA8_CR_DLLDCMCTL_spare0_MAX                             (63) // 0x0000003F
  #define DDRDATA8_CR_DLLDCMCTL_spare0_DEF                             (0x00000000)
  #define DDRDATA8_CR_DLLDCMCTL_spare0_HSH                             (0x061A2424)

#define DDRCTL1_CR_MASTERDLLCFG_REG                                    (0x00002480)

  #define DDRCTL1_CR_MASTERDLLCFG_LockThresh_OFF                       ( 0)
  #define DDRCTL1_CR_MASTERDLLCFG_LockThresh_WID                       ( 3)
  #define DDRCTL1_CR_MASTERDLLCFG_LockThresh_MSK                       (0x00000007)
  #define DDRCTL1_CR_MASTERDLLCFG_LockThresh_MIN                       (0)
  #define DDRCTL1_CR_MASTERDLLCFG_LockThresh_MAX                       (7) // 0x00000007
  #define DDRCTL1_CR_MASTERDLLCFG_LockThresh_DEF                       (0x00000004)
  #define DDRCTL1_CR_MASTERDLLCFG_LockThresh_HSH                       (0x03002480)

  #define DDRCTL1_CR_MASTERDLLCFG_LockCtr_OFF                          ( 3)
  #define DDRCTL1_CR_MASTERDLLCFG_LockCtr_WID                          ( 2)
  #define DDRCTL1_CR_MASTERDLLCFG_LockCtr_MSK                          (0x00000018)
  #define DDRCTL1_CR_MASTERDLLCFG_LockCtr_MIN                          (0)
  #define DDRCTL1_CR_MASTERDLLCFG_LockCtr_MAX                          (3) // 0x00000003
  #define DDRCTL1_CR_MASTERDLLCFG_LockCtr_DEF                          (0x00000000)
  #define DDRCTL1_CR_MASTERDLLCFG_LockCtr_HSH                          (0x02032480)

  #define DDRCTL1_CR_MASTERDLLCFG_VctrlDischRate_OFF                   ( 5)
  #define DDRCTL1_CR_MASTERDLLCFG_VctrlDischRate_WID                   ( 2)
  #define DDRCTL1_CR_MASTERDLLCFG_VctrlDischRate_MSK                   (0x00000060)
  #define DDRCTL1_CR_MASTERDLLCFG_VctrlDischRate_MIN                   (0)
  #define DDRCTL1_CR_MASTERDLLCFG_VctrlDischRate_MAX                   (3) // 0x00000003
  #define DDRCTL1_CR_MASTERDLLCFG_VctrlDischRate_DEF                   (0x00000000)
  #define DDRCTL1_CR_MASTERDLLCFG_VctrlDischRate_HSH                   (0x02052480)

  #define DDRCTL1_CR_MASTERDLLCFG_SelVctrlHi_OFF                       ( 7)
  #define DDRCTL1_CR_MASTERDLLCFG_SelVctrlHi_WID                       ( 1)
  #define DDRCTL1_CR_MASTERDLLCFG_SelVctrlHi_MSK                       (0x00000080)
  #define DDRCTL1_CR_MASTERDLLCFG_SelVctrlHi_MIN                       (0)
  #define DDRCTL1_CR_MASTERDLLCFG_SelVctrlHi_MAX                       (1) // 0x00000001
  #define DDRCTL1_CR_MASTERDLLCFG_SelVctrlHi_DEF                       (0x00000000)
  #define DDRCTL1_CR_MASTERDLLCFG_SelVctrlHi_HSH                       (0x01072480)

  #define DDRCTL1_CR_MASTERDLLCFG_StartupCntSel_OFF                    ( 8)
  #define DDRCTL1_CR_MASTERDLLCFG_StartupCntSel_WID                    ( 1)
  #define DDRCTL1_CR_MASTERDLLCFG_StartupCntSel_MSK                    (0x00000100)
  #define DDRCTL1_CR_MASTERDLLCFG_StartupCntSel_MIN                    (0)
  #define DDRCTL1_CR_MASTERDLLCFG_StartupCntSel_MAX                    (1) // 0x00000001
  #define DDRCTL1_CR_MASTERDLLCFG_StartupCntSel_DEF                    (0x00000000)
  #define DDRCTL1_CR_MASTERDLLCFG_StartupCntSel_HSH                    (0x01082480)

  #define DDRCTL1_CR_MASTERDLLCFG_LockSel_OFF                          ( 9)
  #define DDRCTL1_CR_MASTERDLLCFG_LockSel_WID                          ( 2)
  #define DDRCTL1_CR_MASTERDLLCFG_LockSel_MSK                          (0x00000600)
  #define DDRCTL1_CR_MASTERDLLCFG_LockSel_MIN                          (0)
  #define DDRCTL1_CR_MASTERDLLCFG_LockSel_MAX                          (3) // 0x00000003
  #define DDRCTL1_CR_MASTERDLLCFG_LockSel_DEF                          (0x00000000)
  #define DDRCTL1_CR_MASTERDLLCFG_LockSel_HSH                          (0x02092480)

  #define DDRCTL1_CR_MASTERDLLCFG_RstOvrd_OFF                          (11)
  #define DDRCTL1_CR_MASTERDLLCFG_RstOvrd_WID                          ( 1)
  #define DDRCTL1_CR_MASTERDLLCFG_RstOvrd_MSK                          (0x00000800)
  #define DDRCTL1_CR_MASTERDLLCFG_RstOvrd_MIN                          (0)
  #define DDRCTL1_CR_MASTERDLLCFG_RstOvrd_MAX                          (1) // 0x00000001
  #define DDRCTL1_CR_MASTERDLLCFG_RstOvrd_DEF                          (0x00000000)
  #define DDRCTL1_CR_MASTERDLLCFG_RstOvrd_HSH                          (0x010B2480)

  #define DDRCTL1_CR_MASTERDLLCFG_SelRstOvrd_OFF                       (12)
  #define DDRCTL1_CR_MASTERDLLCFG_SelRstOvrd_WID                       ( 1)
  #define DDRCTL1_CR_MASTERDLLCFG_SelRstOvrd_MSK                       (0x00001000)
  #define DDRCTL1_CR_MASTERDLLCFG_SelRstOvrd_MIN                       (0)
  #define DDRCTL1_CR_MASTERDLLCFG_SelRstOvrd_MAX                       (1) // 0x00000001
  #define DDRCTL1_CR_MASTERDLLCFG_SelRstOvrd_DEF                       (0x00000000)
  #define DDRCTL1_CR_MASTERDLLCFG_SelRstOvrd_HSH                       (0x010C2480)

  #define DDRCTL1_CR_MASTERDLLCFG_TimeOutOvrd_OFF                      (13)
  #define DDRCTL1_CR_MASTERDLLCFG_TimeOutOvrd_WID                      ( 1)
  #define DDRCTL1_CR_MASTERDLLCFG_TimeOutOvrd_MSK                      (0x00002000)
  #define DDRCTL1_CR_MASTERDLLCFG_TimeOutOvrd_MIN                      (0)
  #define DDRCTL1_CR_MASTERDLLCFG_TimeOutOvrd_MAX                      (1) // 0x00000001
  #define DDRCTL1_CR_MASTERDLLCFG_TimeOutOvrd_DEF                      (0x00000000)
  #define DDRCTL1_CR_MASTERDLLCFG_TimeOutOvrd_HSH                      (0x010D2480)

  #define DDRCTL1_CR_MASTERDLLCFG_SelTimeOutOvrd_OFF                   (14)
  #define DDRCTL1_CR_MASTERDLLCFG_SelTimeOutOvrd_WID                   ( 1)
  #define DDRCTL1_CR_MASTERDLLCFG_SelTimeOutOvrd_MSK                   (0x00004000)
  #define DDRCTL1_CR_MASTERDLLCFG_SelTimeOutOvrd_MIN                   (0)
  #define DDRCTL1_CR_MASTERDLLCFG_SelTimeOutOvrd_MAX                   (1) // 0x00000001
  #define DDRCTL1_CR_MASTERDLLCFG_SelTimeOutOvrd_DEF                   (0x00000000)
  #define DDRCTL1_CR_MASTERDLLCFG_SelTimeOutOvrd_HSH                   (0x010E2480)

  #define DDRCTL1_CR_MASTERDLLCFG_ClkGateOvrd_OFF                      (15)
  #define DDRCTL1_CR_MASTERDLLCFG_ClkGateOvrd_WID                      ( 1)
  #define DDRCTL1_CR_MASTERDLLCFG_ClkGateOvrd_MSK                      (0x00008000)
  #define DDRCTL1_CR_MASTERDLLCFG_ClkGateOvrd_MIN                      (0)
  #define DDRCTL1_CR_MASTERDLLCFG_ClkGateOvrd_MAX                      (1) // 0x00000001
  #define DDRCTL1_CR_MASTERDLLCFG_ClkGateOvrd_DEF                      (0x00000000)
  #define DDRCTL1_CR_MASTERDLLCFG_ClkGateOvrd_HSH                      (0x010F2480)

  #define DDRCTL1_CR_MASTERDLLCFG_LockOvrd_OFF                         (16)
  #define DDRCTL1_CR_MASTERDLLCFG_LockOvrd_WID                         ( 1)
  #define DDRCTL1_CR_MASTERDLLCFG_LockOvrd_MSK                         (0x00010000)
  #define DDRCTL1_CR_MASTERDLLCFG_LockOvrd_MIN                         (0)
  #define DDRCTL1_CR_MASTERDLLCFG_LockOvrd_MAX                         (1) // 0x00000001
  #define DDRCTL1_CR_MASTERDLLCFG_LockOvrd_DEF                         (0x00000000)
  #define DDRCTL1_CR_MASTERDLLCFG_LockOvrd_HSH                         (0x01102480)

  #define DDRCTL1_CR_MASTERDLLCFG_SelLockOvrd_OFF                      (17)
  #define DDRCTL1_CR_MASTERDLLCFG_SelLockOvrd_WID                      ( 1)
  #define DDRCTL1_CR_MASTERDLLCFG_SelLockOvrd_MSK                      (0x00020000)
  #define DDRCTL1_CR_MASTERDLLCFG_SelLockOvrd_MIN                      (0)
  #define DDRCTL1_CR_MASTERDLLCFG_SelLockOvrd_MAX                      (1) // 0x00000001
  #define DDRCTL1_CR_MASTERDLLCFG_SelLockOvrd_DEF                      (0x00000000)
  #define DDRCTL1_CR_MASTERDLLCFG_SelLockOvrd_HSH                      (0x01112480)

  #define DDRCTL1_CR_MASTERDLLCFG_OpenLoopOvrd_OFF                     (18)
  #define DDRCTL1_CR_MASTERDLLCFG_OpenLoopOvrd_WID                     ( 1)
  #define DDRCTL1_CR_MASTERDLLCFG_OpenLoopOvrd_MSK                     (0x00040000)
  #define DDRCTL1_CR_MASTERDLLCFG_OpenLoopOvrd_MIN                     (0)
  #define DDRCTL1_CR_MASTERDLLCFG_OpenLoopOvrd_MAX                     (1) // 0x00000001
  #define DDRCTL1_CR_MASTERDLLCFG_OpenLoopOvrd_DEF                     (0x00000000)
  #define DDRCTL1_CR_MASTERDLLCFG_OpenLoopOvrd_HSH                     (0x01122480)

  #define DDRCTL1_CR_MASTERDLLCFG_SelOpenLoopOvrd_OFF                  (19)
  #define DDRCTL1_CR_MASTERDLLCFG_SelOpenLoopOvrd_WID                  ( 1)
  #define DDRCTL1_CR_MASTERDLLCFG_SelOpenLoopOvrd_MSK                  (0x00080000)
  #define DDRCTL1_CR_MASTERDLLCFG_SelOpenLoopOvrd_MIN                  (0)
  #define DDRCTL1_CR_MASTERDLLCFG_SelOpenLoopOvrd_MAX                  (1) // 0x00000001
  #define DDRCTL1_CR_MASTERDLLCFG_SelOpenLoopOvrd_DEF                  (0x00000000)
  #define DDRCTL1_CR_MASTERDLLCFG_SelOpenLoopOvrd_HSH                  (0x01132480)

  #define DDRCTL1_CR_MASTERDLLCFG_WkLockEnOvrd_OFF                     (20)
  #define DDRCTL1_CR_MASTERDLLCFG_WkLockEnOvrd_WID                     ( 1)
  #define DDRCTL1_CR_MASTERDLLCFG_WkLockEnOvrd_MSK                     (0x00100000)
  #define DDRCTL1_CR_MASTERDLLCFG_WkLockEnOvrd_MIN                     (0)
  #define DDRCTL1_CR_MASTERDLLCFG_WkLockEnOvrd_MAX                     (1) // 0x00000001
  #define DDRCTL1_CR_MASTERDLLCFG_WkLockEnOvrd_DEF                     (0x00000000)
  #define DDRCTL1_CR_MASTERDLLCFG_WkLockEnOvrd_HSH                     (0x01142480)

  #define DDRCTL1_CR_MASTERDLLCFG_SelWkLockEnOvrd_OFF                  (21)
  #define DDRCTL1_CR_MASTERDLLCFG_SelWkLockEnOvrd_WID                  ( 1)
  #define DDRCTL1_CR_MASTERDLLCFG_SelWkLockEnOvrd_MSK                  (0x00200000)
  #define DDRCTL1_CR_MASTERDLLCFG_SelWkLockEnOvrd_MIN                  (0)
  #define DDRCTL1_CR_MASTERDLLCFG_SelWkLockEnOvrd_MAX                  (1) // 0x00000001
  #define DDRCTL1_CR_MASTERDLLCFG_SelWkLockEnOvrd_DEF                  (0x00000000)
  #define DDRCTL1_CR_MASTERDLLCFG_SelWkLockEnOvrd_HSH                  (0x01152480)

  #define DDRCTL1_CR_MASTERDLLCFG_CfdlDis_OFF                          (22)
  #define DDRCTL1_CR_MASTERDLLCFG_CfdlDis_WID                          ( 1)
  #define DDRCTL1_CR_MASTERDLLCFG_CfdlDis_MSK                          (0x00400000)
  #define DDRCTL1_CR_MASTERDLLCFG_CfdlDis_MIN                          (0)
  #define DDRCTL1_CR_MASTERDLLCFG_CfdlDis_MAX                          (1) // 0x00000001
  #define DDRCTL1_CR_MASTERDLLCFG_CfdlDis_DEF                          (0x00000000)
  #define DDRCTL1_CR_MASTERDLLCFG_CfdlDis_HSH                          (0x01162480)

  #define DDRCTL1_CR_MASTERDLLCFG_DftEn_OFF                            (23)
  #define DDRCTL1_CR_MASTERDLLCFG_DftEn_WID                            ( 1)
  #define DDRCTL1_CR_MASTERDLLCFG_DftEn_MSK                            (0x00800000)
  #define DDRCTL1_CR_MASTERDLLCFG_DftEn_MIN                            (0)
  #define DDRCTL1_CR_MASTERDLLCFG_DftEn_MAX                            (1) // 0x00000001
  #define DDRCTL1_CR_MASTERDLLCFG_DftEn_DEF                            (0x00000000)
  #define DDRCTL1_CR_MASTERDLLCFG_DftEn_HSH                            (0x01172480)

  #define DDRCTL1_CR_MASTERDLLCFG_spare0_OFF                           (24)
  #define DDRCTL1_CR_MASTERDLLCFG_spare0_WID                           ( 8)
  #define DDRCTL1_CR_MASTERDLLCFG_spare0_MSK                           (0xFF000000)
  #define DDRCTL1_CR_MASTERDLLCFG_spare0_MIN                           (0)
  #define DDRCTL1_CR_MASTERDLLCFG_spare0_MAX                           (255) // 0x000000FF
  #define DDRCTL1_CR_MASTERDLLCFG_spare0_DEF                           (0x00000000)
  #define DDRCTL1_CR_MASTERDLLCFG_spare0_HSH                           (0x08182480)

#define DDRCTL1_CR_CBTUNE0_REG                                         (0x00002484)

  #define DDRCTL1_CR_CBTUNE0_DllBWEn_OFF                               ( 0)
  #define DDRCTL1_CR_CBTUNE0_DllBWEn_WID                               (32)
  #define DDRCTL1_CR_CBTUNE0_DllBWEn_MSK                               (0xFFFFFFFF)
  #define DDRCTL1_CR_CBTUNE0_DllBWEn_MIN                               (0)
  #define DDRCTL1_CR_CBTUNE0_DllBWEn_MAX                               (4294967295) // 0xFFFFFFFF
  #define DDRCTL1_CR_CBTUNE0_DllBWEn_DEF                               (0xFDB86521)
  #define DDRCTL1_CR_CBTUNE0_DllBWEn_HSH                               (0x20002484)

#define DDRCTL1_CR_CBTUNE1_REG                                         (0x00002488)

  #define DDRCTL1_CR_CBTUNE1_PiCbEn_OFF                                ( 0)
  #define DDRCTL1_CR_CBTUNE1_PiCbEn_WID                                (24)
  #define DDRCTL1_CR_CBTUNE1_PiCbEn_MSK                                (0x00FFFFFF)
  #define DDRCTL1_CR_CBTUNE1_PiCbEn_MIN                                (0)
  #define DDRCTL1_CR_CBTUNE1_PiCbEn_MAX                                (16777215) // 0x00FFFFFF
  #define DDRCTL1_CR_CBTUNE1_PiCbEn_DEF                                (0x00249492)
  #define DDRCTL1_CR_CBTUNE1_PiCbEn_HSH                                (0x18002488)

  #define DDRCTL1_CR_CBTUNE1_CbEnRsvd_OFF                              (24)
  #define DDRCTL1_CR_CBTUNE1_CbEnRsvd_WID                              ( 3)
  #define DDRCTL1_CR_CBTUNE1_CbEnRsvd_MSK                              (0x07000000)
  #define DDRCTL1_CR_CBTUNE1_CbEnRsvd_MIN                              (0)
  #define DDRCTL1_CR_CBTUNE1_CbEnRsvd_MAX                              (7) // 0x00000007
  #define DDRCTL1_CR_CBTUNE1_CbEnRsvd_DEF                              (0x00000000)
  #define DDRCTL1_CR_CBTUNE1_CbEnRsvd_HSH                              (0x03182488)

  #define DDRCTL1_CR_CBTUNE1_CbEnDllFuse_OFF                           (27)
  #define DDRCTL1_CR_CBTUNE1_CbEnDllFuse_WID                           ( 3)
  #define DDRCTL1_CR_CBTUNE1_CbEnDllFuse_MSK                           (0x38000000)
  #define DDRCTL1_CR_CBTUNE1_CbEnDllFuse_MIN                           (0)
  #define DDRCTL1_CR_CBTUNE1_CbEnDllFuse_MAX                           (7) // 0x00000007
  #define DDRCTL1_CR_CBTUNE1_CbEnDllFuse_DEF                           (0x00000002)
  #define DDRCTL1_CR_CBTUNE1_CbEnDllFuse_HSH                           (0x031B2488)

  #define DDRCTL1_CR_CBTUNE1_Spare_OFF                                 (30)
  #define DDRCTL1_CR_CBTUNE1_Spare_WID                                 ( 2)
  #define DDRCTL1_CR_CBTUNE1_Spare_MSK                                 (0xC0000000)
  #define DDRCTL1_CR_CBTUNE1_Spare_MIN                                 (0)
  #define DDRCTL1_CR_CBTUNE1_Spare_MAX                                 (3) // 0x00000003
  #define DDRCTL1_CR_CBTUNE1_Spare_DEF                                 (0x00000000)
  #define DDRCTL1_CR_CBTUNE1_Spare_HSH                                 (0x021E2488)

#define DDRCTL1_CR_ADCCFG_REG                                          (0x0000248C)

  #define DDRCTL1_CR_ADCCFG_ADC_frz_OFF                                ( 0)
  #define DDRCTL1_CR_ADCCFG_ADC_frz_WID                                ( 1)
  #define DDRCTL1_CR_ADCCFG_ADC_frz_MSK                                (0x00000001)
  #define DDRCTL1_CR_ADCCFG_ADC_frz_MIN                                (0)
  #define DDRCTL1_CR_ADCCFG_ADC_frz_MAX                                (1) // 0x00000001
  #define DDRCTL1_CR_ADCCFG_ADC_frz_DEF                                (0x00000000)
  #define DDRCTL1_CR_ADCCFG_ADC_frz_HSH                                (0x0100248C)

  #define DDRCTL1_CR_ADCCFG_ADC_en_OFF                                 ( 1)
  #define DDRCTL1_CR_ADCCFG_ADC_en_WID                                 ( 1)
  #define DDRCTL1_CR_ADCCFG_ADC_en_MSK                                 (0x00000002)
  #define DDRCTL1_CR_ADCCFG_ADC_en_MIN                                 (0)
  #define DDRCTL1_CR_ADCCFG_ADC_en_MAX                                 (1) // 0x00000001
  #define DDRCTL1_CR_ADCCFG_ADC_en_DEF                                 (0x00000000)
  #define DDRCTL1_CR_ADCCFG_ADC_en_HSH                                 (0x0101248C)

  #define DDRCTL1_CR_ADCCFG_ADCclkdiv_OFF                              ( 2)
  #define DDRCTL1_CR_ADCCFG_ADCclkdiv_WID                              ( 2)
  #define DDRCTL1_CR_ADCCFG_ADCclkdiv_MSK                              (0x0000000C)
  #define DDRCTL1_CR_ADCCFG_ADCclkdiv_MIN                              (0)
  #define DDRCTL1_CR_ADCCFG_ADCclkdiv_MAX                              (3) // 0x00000003
  #define DDRCTL1_CR_ADCCFG_ADCclkdiv_DEF                              (0x00000000)
  #define DDRCTL1_CR_ADCCFG_ADCclkdiv_HSH                              (0x0202248C)

  #define DDRCTL1_CR_ADCCFG_ADCstartcount_OFF                          ( 4)
  #define DDRCTL1_CR_ADCCFG_ADCstartcount_WID                          ( 2)
  #define DDRCTL1_CR_ADCCFG_ADCstartcount_MSK                          (0x00000030)
  #define DDRCTL1_CR_ADCCFG_ADCstartcount_MIN                          (0)
  #define DDRCTL1_CR_ADCCFG_ADCstartcount_MAX                          (3) // 0x00000003
  #define DDRCTL1_CR_ADCCFG_ADCstartcount_DEF                          (0x00000000)
  #define DDRCTL1_CR_ADCCFG_ADCstartcount_HSH                          (0x0204248C)

  #define DDRCTL1_CR_ADCCFG_ADCChopEn_OFF                              ( 6)
  #define DDRCTL1_CR_ADCCFG_ADCChopEn_WID                              ( 1)
  #define DDRCTL1_CR_ADCCFG_ADCChopEn_MSK                              (0x00000040)
  #define DDRCTL1_CR_ADCCFG_ADCChopEn_MIN                              (0)
  #define DDRCTL1_CR_ADCCFG_ADCChopEn_MAX                              (1) // 0x00000001
  #define DDRCTL1_CR_ADCCFG_ADCChopEn_DEF                              (0x00000000)
  #define DDRCTL1_CR_ADCCFG_ADCChopEn_HSH                              (0x0106248C)

  #define DDRCTL1_CR_ADCCFG_Spare_OFF                                  ( 7)
  #define DDRCTL1_CR_ADCCFG_Spare_WID                                  (25)
  #define DDRCTL1_CR_ADCCFG_Spare_MSK                                  (0xFFFFFF80)
  #define DDRCTL1_CR_ADCCFG_Spare_MIN                                  (0)
  #define DDRCTL1_CR_ADCCFG_Spare_MAX                                  (33554431) // 0x01FFFFFF
  #define DDRCTL1_CR_ADCCFG_Spare_DEF                                  (0x00000000)
  #define DDRCTL1_CR_ADCCFG_Spare_HSH                                  (0x1907248C)

#define DDRCTL1_CR_CBTUNE2_REG                                         (0x00002490)

  #define DDRCTL1_CR_CBTUNE2_DllCbEn_OFF                               ( 0)
  #define DDRCTL1_CR_CBTUNE2_DllCbEn_WID                               (16)
  #define DDRCTL1_CR_CBTUNE2_DllCbEn_MSK                               (0x0000FFFF)
  #define DDRCTL1_CR_CBTUNE2_DllCbEn_MIN                               (0)
  #define DDRCTL1_CR_CBTUNE2_DllCbEn_MAX                               (65535) // 0x0000FFFF
  #define DDRCTL1_CR_CBTUNE2_DllCbEn_DEF                               (0x00000000)
  #define DDRCTL1_CR_CBTUNE2_DllCbEn_HSH                               (0x10002490)

  #define DDRCTL1_CR_CBTUNE2_Spare_OFF                                 (16)
  #define DDRCTL1_CR_CBTUNE2_Spare_WID                                 (16)
  #define DDRCTL1_CR_CBTUNE2_Spare_MSK                                 (0xFFFF0000)
  #define DDRCTL1_CR_CBTUNE2_Spare_MIN                                 (0)
  #define DDRCTL1_CR_CBTUNE2_Spare_MAX                                 (65535) // 0x0000FFFF
  #define DDRCTL1_CR_CBTUNE2_Spare_DEF                                 (0x00000000)
  #define DDRCTL1_CR_CBTUNE2_Spare_HSH                                 (0x10102490)

#define DDRCTL1_CR_PIDFTDLY_REG                                        (0x00002498)

  #define DDRCTL1_CR_PIDFTDLY_PiDftDelay_OFF                           ( 0)
  #define DDRCTL1_CR_PIDFTDLY_PiDftDelay_WID                           ( 7)
  #define DDRCTL1_CR_PIDFTDLY_PiDftDelay_MSK                           (0x0000007F)
  #define DDRCTL1_CR_PIDFTDLY_PiDftDelay_MIN                           (0)
  #define DDRCTL1_CR_PIDFTDLY_PiDftDelay_MAX                           (127) // 0x0000007F
  #define DDRCTL1_CR_PIDFTDLY_PiDftDelay_DEF                           (0x00000000)
  #define DDRCTL1_CR_PIDFTDLY_PiDftDelay_HSH                           (0x07002498)

  #define DDRCTL1_CR_PIDFTDLY_Ch0PiEnOvrd_OFF                          ( 7)
  #define DDRCTL1_CR_PIDFTDLY_Ch0PiEnOvrd_WID                          ( 1)
  #define DDRCTL1_CR_PIDFTDLY_Ch0PiEnOvrd_MSK                          (0x00000080)
  #define DDRCTL1_CR_PIDFTDLY_Ch0PiEnOvrd_MIN                          (0)
  #define DDRCTL1_CR_PIDFTDLY_Ch0PiEnOvrd_MAX                          (1) // 0x00000001
  #define DDRCTL1_CR_PIDFTDLY_Ch0PiEnOvrd_DEF                          (0x00000000)
  #define DDRCTL1_CR_PIDFTDLY_Ch0PiEnOvrd_HSH                          (0x01072498)

  #define DDRCTL1_CR_PIDFTDLY_Ch1PiEnOvrd_OFF                          ( 8)
  #define DDRCTL1_CR_PIDFTDLY_Ch1PiEnOvrd_WID                          ( 1)
  #define DDRCTL1_CR_PIDFTDLY_Ch1PiEnOvrd_MSK                          (0x00000100)
  #define DDRCTL1_CR_PIDFTDLY_Ch1PiEnOvrd_MIN                          (0)
  #define DDRCTL1_CR_PIDFTDLY_Ch1PiEnOvrd_MAX                          (1) // 0x00000001
  #define DDRCTL1_CR_PIDFTDLY_Ch1PiEnOvrd_DEF                          (0x00000000)
  #define DDRCTL1_CR_PIDFTDLY_Ch1PiEnOvrd_HSH                          (0x01082498)

  #define DDRCTL1_CR_PIDFTDLY_Ch0PiDFTEn_OFF                           ( 9)
  #define DDRCTL1_CR_PIDFTDLY_Ch0PiDFTEn_WID                           ( 1)
  #define DDRCTL1_CR_PIDFTDLY_Ch0PiDFTEn_MSK                           (0x00000200)
  #define DDRCTL1_CR_PIDFTDLY_Ch0PiDFTEn_MIN                           (0)
  #define DDRCTL1_CR_PIDFTDLY_Ch0PiDFTEn_MAX                           (1) // 0x00000001
  #define DDRCTL1_CR_PIDFTDLY_Ch0PiDFTEn_DEF                           (0x00000000)
  #define DDRCTL1_CR_PIDFTDLY_Ch0PiDFTEn_HSH                           (0x01092498)

  #define DDRCTL1_CR_PIDFTDLY_Ch1PiDFTEn_OFF                           (10)
  #define DDRCTL1_CR_PIDFTDLY_Ch1PiDFTEn_WID                           ( 1)
  #define DDRCTL1_CR_PIDFTDLY_Ch1PiDFTEn_MSK                           (0x00000400)
  #define DDRCTL1_CR_PIDFTDLY_Ch1PiDFTEn_MIN                           (0)
  #define DDRCTL1_CR_PIDFTDLY_Ch1PiDFTEn_MAX                           (1) // 0x00000001
  #define DDRCTL1_CR_PIDFTDLY_Ch1PiDFTEn_DEF                           (0x00000000)
  #define DDRCTL1_CR_PIDFTDLY_Ch1PiDFTEn_HSH                           (0x010A2498)

  #define DDRCTL1_CR_PIDFTDLY_Spare_OFF                                (11)
  #define DDRCTL1_CR_PIDFTDLY_Spare_WID                                ( 4)
  #define DDRCTL1_CR_PIDFTDLY_Spare_MSK                                (0x00007800)
  #define DDRCTL1_CR_PIDFTDLY_Spare_MIN                                (0)
  #define DDRCTL1_CR_PIDFTDLY_Spare_MAX                                (15) // 0x0000000F
  #define DDRCTL1_CR_PIDFTDLY_Spare_DEF                                (0x00000000)
  #define DDRCTL1_CR_PIDFTDLY_Spare_HSH                                (0x040B2498)

  #define DDRCTL1_CR_PIDFTDLY_RefPiOvrd_OFF                            (15)
  #define DDRCTL1_CR_PIDFTDLY_RefPiOvrd_WID                            ( 1)
  #define DDRCTL1_CR_PIDFTDLY_RefPiOvrd_MSK                            (0x00008000)
  #define DDRCTL1_CR_PIDFTDLY_RefPiOvrd_MIN                            (0)
  #define DDRCTL1_CR_PIDFTDLY_RefPiOvrd_MAX                            (1) // 0x00000001
  #define DDRCTL1_CR_PIDFTDLY_RefPiOvrd_DEF                            (0x00000000)
  #define DDRCTL1_CR_PIDFTDLY_RefPiOvrd_HSH                            (0x010F2498)

  #define DDRCTL1_CR_PIDFTDLY_Rsvd_OFF                                 (16)
  #define DDRCTL1_CR_PIDFTDLY_Rsvd_WID                                 (16)
  #define DDRCTL1_CR_PIDFTDLY_Rsvd_MSK                                 (0xFFFF0000)
  #define DDRCTL1_CR_PIDFTDLY_Rsvd_MIN                                 (0)
  #define DDRCTL1_CR_PIDFTDLY_Rsvd_MAX                                 (65535) // 0x0000FFFF
  #define DDRCTL1_CR_PIDFTDLY_Rsvd_DEF                                 (0x00000000)
  #define DDRCTL1_CR_PIDFTDLY_Rsvd_HSH                                 (0x10102498)

#define DDRCTL1_CR_DLLPITESTANDADC_REG                                 (0x0000249C)

  #define DDRCTL1_CR_DLLPITESTANDADC_RunTest_OFF                       ( 0)
  #define DDRCTL1_CR_DLLPITESTANDADC_RunTest_WID                       ( 1)
  #define DDRCTL1_CR_DLLPITESTANDADC_RunTest_MSK                       (0x00000001)
  #define DDRCTL1_CR_DLLPITESTANDADC_RunTest_MIN                       (0)
  #define DDRCTL1_CR_DLLPITESTANDADC_RunTest_MAX                       (1) // 0x00000001
  #define DDRCTL1_CR_DLLPITESTANDADC_RunTest_DEF                       (0x00000000)
  #define DDRCTL1_CR_DLLPITESTANDADC_RunTest_HSH                       (0x0100249C)

  #define DDRCTL1_CR_DLLPITESTANDADC_Load_OFF                          ( 1)
  #define DDRCTL1_CR_DLLPITESTANDADC_Load_WID                          ( 1)
  #define DDRCTL1_CR_DLLPITESTANDADC_Load_MSK                          (0x00000002)
  #define DDRCTL1_CR_DLLPITESTANDADC_Load_MIN                          (0)
  #define DDRCTL1_CR_DLLPITESTANDADC_Load_MAX                          (1) // 0x00000001
  #define DDRCTL1_CR_DLLPITESTANDADC_Load_DEF                          (0x00000000)
  #define DDRCTL1_CR_DLLPITESTANDADC_Load_HSH                          (0x0101249C)

  #define DDRCTL1_CR_DLLPITESTANDADC_ModeHVM_OFF                       ( 2)
  #define DDRCTL1_CR_DLLPITESTANDADC_ModeHVM_WID                       ( 1)
  #define DDRCTL1_CR_DLLPITESTANDADC_ModeHVM_MSK                       (0x00000004)
  #define DDRCTL1_CR_DLLPITESTANDADC_ModeHVM_MIN                       (0)
  #define DDRCTL1_CR_DLLPITESTANDADC_ModeHVM_MAX                       (1) // 0x00000001
  #define DDRCTL1_CR_DLLPITESTANDADC_ModeHVM_DEF                       (0x00000000)
  #define DDRCTL1_CR_DLLPITESTANDADC_ModeHVM_HSH                       (0x0102249C)

  #define DDRCTL1_CR_DLLPITESTANDADC_ModeDV_OFF                        ( 3)
  #define DDRCTL1_CR_DLLPITESTANDADC_ModeDV_WID                        ( 1)
  #define DDRCTL1_CR_DLLPITESTANDADC_ModeDV_MSK                        (0x00000008)
  #define DDRCTL1_CR_DLLPITESTANDADC_ModeDV_MIN                        (0)
  #define DDRCTL1_CR_DLLPITESTANDADC_ModeDV_MAX                        (1) // 0x00000001
  #define DDRCTL1_CR_DLLPITESTANDADC_ModeDV_DEF                        (0x00000000)
  #define DDRCTL1_CR_DLLPITESTANDADC_ModeDV_HSH                        (0x0103249C)

  #define DDRCTL1_CR_DLLPITESTANDADC_CalCfdl_OFF                       ( 4)
  #define DDRCTL1_CR_DLLPITESTANDADC_CalCfdl_WID                       ( 1)
  #define DDRCTL1_CR_DLLPITESTANDADC_CalCfdl_MSK                       (0x00000010)
  #define DDRCTL1_CR_DLLPITESTANDADC_CalCfdl_MIN                       (0)
  #define DDRCTL1_CR_DLLPITESTANDADC_CalCfdl_MAX                       (1) // 0x00000001
  #define DDRCTL1_CR_DLLPITESTANDADC_CalCfdl_DEF                       (0x00000000)
  #define DDRCTL1_CR_DLLPITESTANDADC_CalCfdl_HSH                       (0x0104249C)

  #define DDRCTL1_CR_DLLPITESTANDADC_LoadCount_OFF                     ( 5)
  #define DDRCTL1_CR_DLLPITESTANDADC_LoadCount_WID                     (10)
  #define DDRCTL1_CR_DLLPITESTANDADC_LoadCount_MSK                     (0x00007FE0)
  #define DDRCTL1_CR_DLLPITESTANDADC_LoadCount_MIN                     (0)
  #define DDRCTL1_CR_DLLPITESTANDADC_LoadCount_MAX                     (1023) // 0x000003FF
  #define DDRCTL1_CR_DLLPITESTANDADC_LoadCount_DEF                     (0x00000000)
  #define DDRCTL1_CR_DLLPITESTANDADC_LoadCount_HSH                     (0x0A05249C)

  #define DDRCTL1_CR_DLLPITESTANDADC_CountStatus_OFF                   (15)
  #define DDRCTL1_CR_DLLPITESTANDADC_CountStatus_WID                   (10)
  #define DDRCTL1_CR_DLLPITESTANDADC_CountStatus_MSK                   (0x01FF8000)
  #define DDRCTL1_CR_DLLPITESTANDADC_CountStatus_MIN                   (0)
  #define DDRCTL1_CR_DLLPITESTANDADC_CountStatus_MAX                   (1023) // 0x000003FF
  #define DDRCTL1_CR_DLLPITESTANDADC_CountStatus_DEF                   (0x00000000)
  #define DDRCTL1_CR_DLLPITESTANDADC_CountStatus_HSH                   (0x0A0F249C)

  #define DDRCTL1_CR_DLLPITESTANDADC_ModeADC_OFF                       (25)
  #define DDRCTL1_CR_DLLPITESTANDADC_ModeADC_WID                       ( 1)
  #define DDRCTL1_CR_DLLPITESTANDADC_ModeADC_MSK                       (0x02000000)
  #define DDRCTL1_CR_DLLPITESTANDADC_ModeADC_MIN                       (0)
  #define DDRCTL1_CR_DLLPITESTANDADC_ModeADC_MAX                       (1) // 0x00000001
  #define DDRCTL1_CR_DLLPITESTANDADC_ModeADC_DEF                       (0x00000000)
  #define DDRCTL1_CR_DLLPITESTANDADC_ModeADC_HSH                       (0x0119249C)

  #define DDRCTL1_CR_DLLPITESTANDADC_ADCClkDiv_OFF                     (26)
  #define DDRCTL1_CR_DLLPITESTANDADC_ADCClkDiv_WID                     ( 2)
  #define DDRCTL1_CR_DLLPITESTANDADC_ADCClkDiv_MSK                     (0x0C000000)
  #define DDRCTL1_CR_DLLPITESTANDADC_ADCClkDiv_MIN                     (0)
  #define DDRCTL1_CR_DLLPITESTANDADC_ADCClkDiv_MAX                     (3) // 0x00000003
  #define DDRCTL1_CR_DLLPITESTANDADC_ADCClkDiv_DEF                     (0x00000000)
  #define DDRCTL1_CR_DLLPITESTANDADC_ADCClkDiv_HSH                     (0x021A249C)

  #define DDRCTL1_CR_DLLPITESTANDADC_ADCDdrChanSel_OFF                 (28)
  #define DDRCTL1_CR_DLLPITESTANDADC_ADCDdrChanSel_WID                 ( 1)
  #define DDRCTL1_CR_DLLPITESTANDADC_ADCDdrChanSel_MSK                 (0x10000000)
  #define DDRCTL1_CR_DLLPITESTANDADC_ADCDdrChanSel_MIN                 (0)
  #define DDRCTL1_CR_DLLPITESTANDADC_ADCDdrChanSel_MAX                 (1) // 0x00000001
  #define DDRCTL1_CR_DLLPITESTANDADC_ADCDdrChanSel_DEF                 (0x00000000)
  #define DDRCTL1_CR_DLLPITESTANDADC_ADCDdrChanSel_HSH                 (0x011C249C)

  #define DDRCTL1_CR_DLLPITESTANDADC_ADCChopEn_OFF                     (29)
  #define DDRCTL1_CR_DLLPITESTANDADC_ADCChopEn_WID                     ( 1)
  #define DDRCTL1_CR_DLLPITESTANDADC_ADCChopEn_MSK                     (0x20000000)
  #define DDRCTL1_CR_DLLPITESTANDADC_ADCChopEn_MIN                     (0)
  #define DDRCTL1_CR_DLLPITESTANDADC_ADCChopEn_MAX                     (1) // 0x00000001
  #define DDRCTL1_CR_DLLPITESTANDADC_ADCChopEn_DEF                     (0x00000000)
  #define DDRCTL1_CR_DLLPITESTANDADC_ADCChopEn_HSH                     (0x011D249C)

  #define DDRCTL1_CR_DLLPITESTANDADC_ADCDone_OFF                       (30)
  #define DDRCTL1_CR_DLLPITESTANDADC_ADCDone_WID                       ( 1)
  #define DDRCTL1_CR_DLLPITESTANDADC_ADCDone_MSK                       (0x40000000)
  #define DDRCTL1_CR_DLLPITESTANDADC_ADCDone_MIN                       (0)
  #define DDRCTL1_CR_DLLPITESTANDADC_ADCDone_MAX                       (1) // 0x00000001
  #define DDRCTL1_CR_DLLPITESTANDADC_ADCDone_DEF                       (0x00000000)
  #define DDRCTL1_CR_DLLPITESTANDADC_ADCDone_HSH                       (0x011E249C)

  #define DDRCTL1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF              (31)
  #define DDRCTL1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID              ( 1)
  #define DDRCTL1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK              (0x80000000)
  #define DDRCTL1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN              (0)
  #define DDRCTL1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX              (1) // 0x00000001
  #define DDRCTL1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF              (0x00000000)
  #define DDRCTL1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH              (0x011F249C)

#define DDRCTL1_CR_DLLSTATUS_REG                                       (0x000024A0)

  #define DDRCTL1_CR_DLLSTATUS_DetrmLockStat_OFF                       ( 0)
  #define DDRCTL1_CR_DLLSTATUS_DetrmLockStat_WID                       ( 1)
  #define DDRCTL1_CR_DLLSTATUS_DetrmLockStat_MSK                       (0x00000001)
  #define DDRCTL1_CR_DLLSTATUS_DetrmLockStat_MIN                       (0)
  #define DDRCTL1_CR_DLLSTATUS_DetrmLockStat_MAX                       (1) // 0x00000001
  #define DDRCTL1_CR_DLLSTATUS_DetrmLockStat_DEF                       (0x00000000)
  #define DDRCTL1_CR_DLLSTATUS_DetrmLockStat_HSH                       (0x010024A0)

  #define DDRCTL1_CR_DLLSTATUS_FuncLockStat_OFF                        ( 1)
  #define DDRCTL1_CR_DLLSTATUS_FuncLockStat_WID                        ( 1)
  #define DDRCTL1_CR_DLLSTATUS_FuncLockStat_MSK                        (0x00000002)
  #define DDRCTL1_CR_DLLSTATUS_FuncLockStat_MIN                        (0)
  #define DDRCTL1_CR_DLLSTATUS_FuncLockStat_MAX                        (1) // 0x00000001
  #define DDRCTL1_CR_DLLSTATUS_FuncLockStat_DEF                        (0x00000000)
  #define DDRCTL1_CR_DLLSTATUS_FuncLockStat_HSH                        (0x010124A0)

  #define DDRCTL1_CR_DLLSTATUS_Lock_OFF                                ( 2)
  #define DDRCTL1_CR_DLLSTATUS_Lock_WID                                ( 1)
  #define DDRCTL1_CR_DLLSTATUS_Lock_MSK                                (0x00000004)
  #define DDRCTL1_CR_DLLSTATUS_Lock_MIN                                (0)
  #define DDRCTL1_CR_DLLSTATUS_Lock_MAX                                (1) // 0x00000001
  #define DDRCTL1_CR_DLLSTATUS_Lock_DEF                                (0x00000000)
  #define DDRCTL1_CR_DLLSTATUS_Lock_HSH                                (0x010224A0)

  #define DDRCTL1_CR_DLLSTATUS_Timeout_OFF                             ( 3)
  #define DDRCTL1_CR_DLLSTATUS_Timeout_WID                             ( 1)
  #define DDRCTL1_CR_DLLSTATUS_Timeout_MSK                             (0x00000008)
  #define DDRCTL1_CR_DLLSTATUS_Timeout_MIN                             (0)
  #define DDRCTL1_CR_DLLSTATUS_Timeout_MAX                             (1) // 0x00000001
  #define DDRCTL1_CR_DLLSTATUS_Timeout_DEF                             (0x00000000)
  #define DDRCTL1_CR_DLLSTATUS_Timeout_HSH                             (0x010324A0)

  #define DDRCTL1_CR_DLLSTATUS_DllReset_OFF                            ( 4)
  #define DDRCTL1_CR_DLLSTATUS_DllReset_WID                            ( 1)
  #define DDRCTL1_CR_DLLSTATUS_DllReset_MSK                            (0x00000010)
  #define DDRCTL1_CR_DLLSTATUS_DllReset_MIN                            (0)
  #define DDRCTL1_CR_DLLSTATUS_DllReset_MAX                            (1) // 0x00000001
  #define DDRCTL1_CR_DLLSTATUS_DllReset_DEF                            (0x00000000)
  #define DDRCTL1_CR_DLLSTATUS_DllReset_HSH                            (0x010424A0)

  #define DDRCTL1_CR_DLLSTATUS_LongLockStat_OFF                        ( 5)
  #define DDRCTL1_CR_DLLSTATUS_LongLockStat_WID                        ( 1)
  #define DDRCTL1_CR_DLLSTATUS_LongLockStat_MSK                        (0x00000020)
  #define DDRCTL1_CR_DLLSTATUS_LongLockStat_MIN                        (0)
  #define DDRCTL1_CR_DLLSTATUS_LongLockStat_MAX                        (1) // 0x00000001
  #define DDRCTL1_CR_DLLSTATUS_LongLockStat_DEF                        (0x00000000)
  #define DDRCTL1_CR_DLLSTATUS_LongLockStat_HSH                        (0x010524A0)

  #define DDRCTL1_CR_DLLSTATUS_EarlyLockStat_OFF                       ( 6)
  #define DDRCTL1_CR_DLLSTATUS_EarlyLockStat_WID                       ( 1)
  #define DDRCTL1_CR_DLLSTATUS_EarlyLockStat_MSK                       (0x00000040)
  #define DDRCTL1_CR_DLLSTATUS_EarlyLockStat_MIN                       (0)
  #define DDRCTL1_CR_DLLSTATUS_EarlyLockStat_MAX                       (1) // 0x00000001
  #define DDRCTL1_CR_DLLSTATUS_EarlyLockStat_DEF                       (0x00000000)
  #define DDRCTL1_CR_DLLSTATUS_EarlyLockStat_HSH                       (0x010624A0)

  #define DDRCTL1_CR_DLLSTATUS_NormalMode_NotWkLock_OFF                ( 7)
  #define DDRCTL1_CR_DLLSTATUS_NormalMode_NotWkLock_WID                ( 1)
  #define DDRCTL1_CR_DLLSTATUS_NormalMode_NotWkLock_MSK                (0x00000080)
  #define DDRCTL1_CR_DLLSTATUS_NormalMode_NotWkLock_MIN                (0)
  #define DDRCTL1_CR_DLLSTATUS_NormalMode_NotWkLock_MAX                (1) // 0x00000001
  #define DDRCTL1_CR_DLLSTATUS_NormalMode_NotWkLock_DEF                (0x00000000)
  #define DDRCTL1_CR_DLLSTATUS_NormalMode_NotWkLock_HSH                (0x010724A0)

  #define DDRCTL1_CR_DLLSTATUS_ADCout_OFF                              ( 8)
  #define DDRCTL1_CR_DLLSTATUS_ADCout_WID                              (10)
  #define DDRCTL1_CR_DLLSTATUS_ADCout_MSK                              (0x0003FF00)
  #define DDRCTL1_CR_DLLSTATUS_ADCout_MIN                              (0)
  #define DDRCTL1_CR_DLLSTATUS_ADCout_MAX                              (1023) // 0x000003FF
  #define DDRCTL1_CR_DLLSTATUS_ADCout_DEF                              (0x00000000)
  #define DDRCTL1_CR_DLLSTATUS_ADCout_HSH                              (0x0A0824A0)

  #define DDRCTL1_CR_DLLSTATUS_ADCStatus_OFF                           (18)
  #define DDRCTL1_CR_DLLSTATUS_ADCStatus_WID                           ( 1)
  #define DDRCTL1_CR_DLLSTATUS_ADCStatus_MSK                           (0x00040000)
  #define DDRCTL1_CR_DLLSTATUS_ADCStatus_MIN                           (0)
  #define DDRCTL1_CR_DLLSTATUS_ADCStatus_MAX                           (1) // 0x00000001
  #define DDRCTL1_CR_DLLSTATUS_ADCStatus_DEF                           (0x00000000)
  #define DDRCTL1_CR_DLLSTATUS_ADCStatus_HSH                           (0x011224A0)

  #define DDRCTL1_CR_DLLSTATUS_pilags_OFF                              (19)
  #define DDRCTL1_CR_DLLSTATUS_pilags_WID                              ( 1)
  #define DDRCTL1_CR_DLLSTATUS_pilags_MSK                              (0x00080000)
  #define DDRCTL1_CR_DLLSTATUS_pilags_MIN                              (0)
  #define DDRCTL1_CR_DLLSTATUS_pilags_MAX                              (1) // 0x00000001
  #define DDRCTL1_CR_DLLSTATUS_pilags_DEF                              (0x00000000)
  #define DDRCTL1_CR_DLLSTATUS_pilags_HSH                              (0x011324A0)

  #define DDRCTL1_CR_DLLSTATUS_spare_OFF                               (20)
  #define DDRCTL1_CR_DLLSTATUS_spare_WID                               (12)
  #define DDRCTL1_CR_DLLSTATUS_spare_MSK                               (0xFFF00000)
  #define DDRCTL1_CR_DLLSTATUS_spare_MIN                               (0)
  #define DDRCTL1_CR_DLLSTATUS_spare_MAX                               (4095) // 0x00000FFF
  #define DDRCTL1_CR_DLLSTATUS_spare_DEF                               (0x00000000)
  #define DDRCTL1_CR_DLLSTATUS_spare_HSH                               (0x0C1424A0)

#define DDRCTL1_CR_DLLDCMCTL_REG                                       (0x000024A4)

  #define DDRCTL1_CR_DLLDCMCTL_start_OFF                               ( 0)
  #define DDRCTL1_CR_DLLDCMCTL_start_WID                               ( 1)
  #define DDRCTL1_CR_DLLDCMCTL_start_MSK                               (0x00000001)
  #define DDRCTL1_CR_DLLDCMCTL_start_MIN                               (0)
  #define DDRCTL1_CR_DLLDCMCTL_start_MAX                               (1) // 0x00000001
  #define DDRCTL1_CR_DLLDCMCTL_start_DEF                               (0x00000000)
  #define DDRCTL1_CR_DLLDCMCTL_start_HSH                               (0x010024A4)

  #define DDRCTL1_CR_DLLDCMCTL_clken_OFF                               ( 1)
  #define DDRCTL1_CR_DLLDCMCTL_clken_WID                               ( 1)
  #define DDRCTL1_CR_DLLDCMCTL_clken_MSK                               (0x00000002)
  #define DDRCTL1_CR_DLLDCMCTL_clken_MIN                               (0)
  #define DDRCTL1_CR_DLLDCMCTL_clken_MAX                               (1) // 0x00000001
  #define DDRCTL1_CR_DLLDCMCTL_clken_DEF                               (0x00000000)
  #define DDRCTL1_CR_DLLDCMCTL_clken_HSH                               (0x010124A4)

  #define DDRCTL1_CR_DLLDCMCTL_dcm_dccctl_en_OFF                       ( 2)
  #define DDRCTL1_CR_DLLDCMCTL_dcm_dccctl_en_WID                       ( 1)
  #define DDRCTL1_CR_DLLDCMCTL_dcm_dccctl_en_MSK                       (0x00000004)
  #define DDRCTL1_CR_DLLDCMCTL_dcm_dccctl_en_MIN                       (0)
  #define DDRCTL1_CR_DLLDCMCTL_dcm_dccctl_en_MAX                       (1) // 0x00000001
  #define DDRCTL1_CR_DLLDCMCTL_dcm_dccctl_en_DEF                       (0x00000000)
  #define DDRCTL1_CR_DLLDCMCTL_dcm_dccctl_en_HSH                       (0x010224A4)

  #define DDRCTL1_CR_DLLDCMCTL_dccctl_OFF                              ( 3)
  #define DDRCTL1_CR_DLLDCMCTL_dccctl_WID                              ( 4)
  #define DDRCTL1_CR_DLLDCMCTL_dccctl_MSK                              (0x00000078)
  #define DDRCTL1_CR_DLLDCMCTL_dccctl_MIN                              (0)
  #define DDRCTL1_CR_DLLDCMCTL_dccctl_MAX                              (15) // 0x0000000F
  #define DDRCTL1_CR_DLLDCMCTL_dccctl_DEF                              (0x00000000)
  #define DDRCTL1_CR_DLLDCMCTL_dccctl_HSH                              (0x040324A4)

  #define DDRCTL1_CR_DLLDCMCTL_duration_OFF                            ( 7)
  #define DDRCTL1_CR_DLLDCMCTL_duration_WID                            ( 3)
  #define DDRCTL1_CR_DLLDCMCTL_duration_MSK                            (0x00000380)
  #define DDRCTL1_CR_DLLDCMCTL_duration_MIN                            (0)
  #define DDRCTL1_CR_DLLDCMCTL_duration_MAX                            (7) // 0x00000007
  #define DDRCTL1_CR_DLLDCMCTL_duration_DEF                            (0x00000000)
  #define DDRCTL1_CR_DLLDCMCTL_duration_HSH                            (0x030724A4)

  #define DDRCTL1_CR_DLLDCMCTL_dcm_done_OFF                            (10)
  #define DDRCTL1_CR_DLLDCMCTL_dcm_done_WID                            ( 1)
  #define DDRCTL1_CR_DLLDCMCTL_dcm_done_MSK                            (0x00000400)
  #define DDRCTL1_CR_DLLDCMCTL_dcm_done_MIN                            (0)
  #define DDRCTL1_CR_DLLDCMCTL_dcm_done_MAX                            (1) // 0x00000001
  #define DDRCTL1_CR_DLLDCMCTL_dcm_done_DEF                            (0x00000000)
  #define DDRCTL1_CR_DLLDCMCTL_dcm_done_HSH                            (0x010A24A4)

  #define DDRCTL1_CR_DLLDCMCTL_dcm_results_OFF                         (11)
  #define DDRCTL1_CR_DLLDCMCTL_dcm_results_WID                         (15)
  #define DDRCTL1_CR_DLLDCMCTL_dcm_results_MSK                         (0x03FFF800)
  #define DDRCTL1_CR_DLLDCMCTL_dcm_results_MIN                         (0)
  #define DDRCTL1_CR_DLLDCMCTL_dcm_results_MAX                         (32767) // 0x00007FFF
  #define DDRCTL1_CR_DLLDCMCTL_dcm_results_DEF                         (0x00000000)
  #define DDRCTL1_CR_DLLDCMCTL_dcm_results_HSH                         (0x0F0B24A4)

  #define DDRCTL1_CR_DLLDCMCTL_spare0_OFF                              (26)
  #define DDRCTL1_CR_DLLDCMCTL_spare0_WID                              ( 6)
  #define DDRCTL1_CR_DLLDCMCTL_spare0_MSK                              (0xFC000000)
  #define DDRCTL1_CR_DLLDCMCTL_spare0_MIN                              (0)
  #define DDRCTL1_CR_DLLDCMCTL_spare0_MAX                              (63) // 0x0000003F
  #define DDRCTL1_CR_DLLDCMCTL_spare0_DEF                              (0x00000000)
  #define DDRCTL1_CR_DLLDCMCTL_spare0_HSH                              (0x061A24A4)

#define DDRCMD0_CR_MASTERDLLCFG_REG                                    (0x00002500)

  #define DDRCMD0_CR_MASTERDLLCFG_LockThresh_OFF                       ( 0)
  #define DDRCMD0_CR_MASTERDLLCFG_LockThresh_WID                       ( 3)
  #define DDRCMD0_CR_MASTERDLLCFG_LockThresh_MSK                       (0x00000007)
  #define DDRCMD0_CR_MASTERDLLCFG_LockThresh_MIN                       (0)
  #define DDRCMD0_CR_MASTERDLLCFG_LockThresh_MAX                       (7) // 0x00000007
  #define DDRCMD0_CR_MASTERDLLCFG_LockThresh_DEF                       (0x00000004)
  #define DDRCMD0_CR_MASTERDLLCFG_LockThresh_HSH                       (0x03002500)

  #define DDRCMD0_CR_MASTERDLLCFG_LockCtr_OFF                          ( 3)
  #define DDRCMD0_CR_MASTERDLLCFG_LockCtr_WID                          ( 2)
  #define DDRCMD0_CR_MASTERDLLCFG_LockCtr_MSK                          (0x00000018)
  #define DDRCMD0_CR_MASTERDLLCFG_LockCtr_MIN                          (0)
  #define DDRCMD0_CR_MASTERDLLCFG_LockCtr_MAX                          (3) // 0x00000003
  #define DDRCMD0_CR_MASTERDLLCFG_LockCtr_DEF                          (0x00000000)
  #define DDRCMD0_CR_MASTERDLLCFG_LockCtr_HSH                          (0x02032500)

  #define DDRCMD0_CR_MASTERDLLCFG_VctrlDischRate_OFF                   ( 5)
  #define DDRCMD0_CR_MASTERDLLCFG_VctrlDischRate_WID                   ( 2)
  #define DDRCMD0_CR_MASTERDLLCFG_VctrlDischRate_MSK                   (0x00000060)
  #define DDRCMD0_CR_MASTERDLLCFG_VctrlDischRate_MIN                   (0)
  #define DDRCMD0_CR_MASTERDLLCFG_VctrlDischRate_MAX                   (3) // 0x00000003
  #define DDRCMD0_CR_MASTERDLLCFG_VctrlDischRate_DEF                   (0x00000000)
  #define DDRCMD0_CR_MASTERDLLCFG_VctrlDischRate_HSH                   (0x02052500)

  #define DDRCMD0_CR_MASTERDLLCFG_SelVctrlHi_OFF                       ( 7)
  #define DDRCMD0_CR_MASTERDLLCFG_SelVctrlHi_WID                       ( 1)
  #define DDRCMD0_CR_MASTERDLLCFG_SelVctrlHi_MSK                       (0x00000080)
  #define DDRCMD0_CR_MASTERDLLCFG_SelVctrlHi_MIN                       (0)
  #define DDRCMD0_CR_MASTERDLLCFG_SelVctrlHi_MAX                       (1) // 0x00000001
  #define DDRCMD0_CR_MASTERDLLCFG_SelVctrlHi_DEF                       (0x00000000)
  #define DDRCMD0_CR_MASTERDLLCFG_SelVctrlHi_HSH                       (0x01072500)

  #define DDRCMD0_CR_MASTERDLLCFG_StartupCntSel_OFF                    ( 8)
  #define DDRCMD0_CR_MASTERDLLCFG_StartupCntSel_WID                    ( 1)
  #define DDRCMD0_CR_MASTERDLLCFG_StartupCntSel_MSK                    (0x00000100)
  #define DDRCMD0_CR_MASTERDLLCFG_StartupCntSel_MIN                    (0)
  #define DDRCMD0_CR_MASTERDLLCFG_StartupCntSel_MAX                    (1) // 0x00000001
  #define DDRCMD0_CR_MASTERDLLCFG_StartupCntSel_DEF                    (0x00000000)
  #define DDRCMD0_CR_MASTERDLLCFG_StartupCntSel_HSH                    (0x01082500)

  #define DDRCMD0_CR_MASTERDLLCFG_LockSel_OFF                          ( 9)
  #define DDRCMD0_CR_MASTERDLLCFG_LockSel_WID                          ( 2)
  #define DDRCMD0_CR_MASTERDLLCFG_LockSel_MSK                          (0x00000600)
  #define DDRCMD0_CR_MASTERDLLCFG_LockSel_MIN                          (0)
  #define DDRCMD0_CR_MASTERDLLCFG_LockSel_MAX                          (3) // 0x00000003
  #define DDRCMD0_CR_MASTERDLLCFG_LockSel_DEF                          (0x00000000)
  #define DDRCMD0_CR_MASTERDLLCFG_LockSel_HSH                          (0x02092500)

  #define DDRCMD0_CR_MASTERDLLCFG_RstOvrd_OFF                          (11)
  #define DDRCMD0_CR_MASTERDLLCFG_RstOvrd_WID                          ( 1)
  #define DDRCMD0_CR_MASTERDLLCFG_RstOvrd_MSK                          (0x00000800)
  #define DDRCMD0_CR_MASTERDLLCFG_RstOvrd_MIN                          (0)
  #define DDRCMD0_CR_MASTERDLLCFG_RstOvrd_MAX                          (1) // 0x00000001
  #define DDRCMD0_CR_MASTERDLLCFG_RstOvrd_DEF                          (0x00000000)
  #define DDRCMD0_CR_MASTERDLLCFG_RstOvrd_HSH                          (0x010B2500)

  #define DDRCMD0_CR_MASTERDLLCFG_SelRstOvrd_OFF                       (12)
  #define DDRCMD0_CR_MASTERDLLCFG_SelRstOvrd_WID                       ( 1)
  #define DDRCMD0_CR_MASTERDLLCFG_SelRstOvrd_MSK                       (0x00001000)
  #define DDRCMD0_CR_MASTERDLLCFG_SelRstOvrd_MIN                       (0)
  #define DDRCMD0_CR_MASTERDLLCFG_SelRstOvrd_MAX                       (1) // 0x00000001
  #define DDRCMD0_CR_MASTERDLLCFG_SelRstOvrd_DEF                       (0x00000000)
  #define DDRCMD0_CR_MASTERDLLCFG_SelRstOvrd_HSH                       (0x010C2500)

  #define DDRCMD0_CR_MASTERDLLCFG_TimeOutOvrd_OFF                      (13)
  #define DDRCMD0_CR_MASTERDLLCFG_TimeOutOvrd_WID                      ( 1)
  #define DDRCMD0_CR_MASTERDLLCFG_TimeOutOvrd_MSK                      (0x00002000)
  #define DDRCMD0_CR_MASTERDLLCFG_TimeOutOvrd_MIN                      (0)
  #define DDRCMD0_CR_MASTERDLLCFG_TimeOutOvrd_MAX                      (1) // 0x00000001
  #define DDRCMD0_CR_MASTERDLLCFG_TimeOutOvrd_DEF                      (0x00000000)
  #define DDRCMD0_CR_MASTERDLLCFG_TimeOutOvrd_HSH                      (0x010D2500)

  #define DDRCMD0_CR_MASTERDLLCFG_SelTimeOutOvrd_OFF                   (14)
  #define DDRCMD0_CR_MASTERDLLCFG_SelTimeOutOvrd_WID                   ( 1)
  #define DDRCMD0_CR_MASTERDLLCFG_SelTimeOutOvrd_MSK                   (0x00004000)
  #define DDRCMD0_CR_MASTERDLLCFG_SelTimeOutOvrd_MIN                   (0)
  #define DDRCMD0_CR_MASTERDLLCFG_SelTimeOutOvrd_MAX                   (1) // 0x00000001
  #define DDRCMD0_CR_MASTERDLLCFG_SelTimeOutOvrd_DEF                   (0x00000000)
  #define DDRCMD0_CR_MASTERDLLCFG_SelTimeOutOvrd_HSH                   (0x010E2500)

  #define DDRCMD0_CR_MASTERDLLCFG_ClkGateOvrd_OFF                      (15)
  #define DDRCMD0_CR_MASTERDLLCFG_ClkGateOvrd_WID                      ( 1)
  #define DDRCMD0_CR_MASTERDLLCFG_ClkGateOvrd_MSK                      (0x00008000)
  #define DDRCMD0_CR_MASTERDLLCFG_ClkGateOvrd_MIN                      (0)
  #define DDRCMD0_CR_MASTERDLLCFG_ClkGateOvrd_MAX                      (1) // 0x00000001
  #define DDRCMD0_CR_MASTERDLLCFG_ClkGateOvrd_DEF                      (0x00000000)
  #define DDRCMD0_CR_MASTERDLLCFG_ClkGateOvrd_HSH                      (0x010F2500)

  #define DDRCMD0_CR_MASTERDLLCFG_LockOvrd_OFF                         (16)
  #define DDRCMD0_CR_MASTERDLLCFG_LockOvrd_WID                         ( 1)
  #define DDRCMD0_CR_MASTERDLLCFG_LockOvrd_MSK                         (0x00010000)
  #define DDRCMD0_CR_MASTERDLLCFG_LockOvrd_MIN                         (0)
  #define DDRCMD0_CR_MASTERDLLCFG_LockOvrd_MAX                         (1) // 0x00000001
  #define DDRCMD0_CR_MASTERDLLCFG_LockOvrd_DEF                         (0x00000000)
  #define DDRCMD0_CR_MASTERDLLCFG_LockOvrd_HSH                         (0x01102500)

  #define DDRCMD0_CR_MASTERDLLCFG_SelLockOvrd_OFF                      (17)
  #define DDRCMD0_CR_MASTERDLLCFG_SelLockOvrd_WID                      ( 1)
  #define DDRCMD0_CR_MASTERDLLCFG_SelLockOvrd_MSK                      (0x00020000)
  #define DDRCMD0_CR_MASTERDLLCFG_SelLockOvrd_MIN                      (0)
  #define DDRCMD0_CR_MASTERDLLCFG_SelLockOvrd_MAX                      (1) // 0x00000001
  #define DDRCMD0_CR_MASTERDLLCFG_SelLockOvrd_DEF                      (0x00000000)
  #define DDRCMD0_CR_MASTERDLLCFG_SelLockOvrd_HSH                      (0x01112500)

  #define DDRCMD0_CR_MASTERDLLCFG_OpenLoopOvrd_OFF                     (18)
  #define DDRCMD0_CR_MASTERDLLCFG_OpenLoopOvrd_WID                     ( 1)
  #define DDRCMD0_CR_MASTERDLLCFG_OpenLoopOvrd_MSK                     (0x00040000)
  #define DDRCMD0_CR_MASTERDLLCFG_OpenLoopOvrd_MIN                     (0)
  #define DDRCMD0_CR_MASTERDLLCFG_OpenLoopOvrd_MAX                     (1) // 0x00000001
  #define DDRCMD0_CR_MASTERDLLCFG_OpenLoopOvrd_DEF                     (0x00000000)
  #define DDRCMD0_CR_MASTERDLLCFG_OpenLoopOvrd_HSH                     (0x01122500)

  #define DDRCMD0_CR_MASTERDLLCFG_SelOpenLoopOvrd_OFF                  (19)
  #define DDRCMD0_CR_MASTERDLLCFG_SelOpenLoopOvrd_WID                  ( 1)
  #define DDRCMD0_CR_MASTERDLLCFG_SelOpenLoopOvrd_MSK                  (0x00080000)
  #define DDRCMD0_CR_MASTERDLLCFG_SelOpenLoopOvrd_MIN                  (0)
  #define DDRCMD0_CR_MASTERDLLCFG_SelOpenLoopOvrd_MAX                  (1) // 0x00000001
  #define DDRCMD0_CR_MASTERDLLCFG_SelOpenLoopOvrd_DEF                  (0x00000000)
  #define DDRCMD0_CR_MASTERDLLCFG_SelOpenLoopOvrd_HSH                  (0x01132500)

  #define DDRCMD0_CR_MASTERDLLCFG_WkLockEnOvrd_OFF                     (20)
  #define DDRCMD0_CR_MASTERDLLCFG_WkLockEnOvrd_WID                     ( 1)
  #define DDRCMD0_CR_MASTERDLLCFG_WkLockEnOvrd_MSK                     (0x00100000)
  #define DDRCMD0_CR_MASTERDLLCFG_WkLockEnOvrd_MIN                     (0)
  #define DDRCMD0_CR_MASTERDLLCFG_WkLockEnOvrd_MAX                     (1) // 0x00000001
  #define DDRCMD0_CR_MASTERDLLCFG_WkLockEnOvrd_DEF                     (0x00000000)
  #define DDRCMD0_CR_MASTERDLLCFG_WkLockEnOvrd_HSH                     (0x01142500)

  #define DDRCMD0_CR_MASTERDLLCFG_SelWkLockEnOvrd_OFF                  (21)
  #define DDRCMD0_CR_MASTERDLLCFG_SelWkLockEnOvrd_WID                  ( 1)
  #define DDRCMD0_CR_MASTERDLLCFG_SelWkLockEnOvrd_MSK                  (0x00200000)
  #define DDRCMD0_CR_MASTERDLLCFG_SelWkLockEnOvrd_MIN                  (0)
  #define DDRCMD0_CR_MASTERDLLCFG_SelWkLockEnOvrd_MAX                  (1) // 0x00000001
  #define DDRCMD0_CR_MASTERDLLCFG_SelWkLockEnOvrd_DEF                  (0x00000000)
  #define DDRCMD0_CR_MASTERDLLCFG_SelWkLockEnOvrd_HSH                  (0x01152500)

  #define DDRCMD0_CR_MASTERDLLCFG_CfdlDis_OFF                          (22)
  #define DDRCMD0_CR_MASTERDLLCFG_CfdlDis_WID                          ( 1)
  #define DDRCMD0_CR_MASTERDLLCFG_CfdlDis_MSK                          (0x00400000)
  #define DDRCMD0_CR_MASTERDLLCFG_CfdlDis_MIN                          (0)
  #define DDRCMD0_CR_MASTERDLLCFG_CfdlDis_MAX                          (1) // 0x00000001
  #define DDRCMD0_CR_MASTERDLLCFG_CfdlDis_DEF                          (0x00000000)
  #define DDRCMD0_CR_MASTERDLLCFG_CfdlDis_HSH                          (0x01162500)

  #define DDRCMD0_CR_MASTERDLLCFG_DftEn_OFF                            (23)
  #define DDRCMD0_CR_MASTERDLLCFG_DftEn_WID                            ( 1)
  #define DDRCMD0_CR_MASTERDLLCFG_DftEn_MSK                            (0x00800000)
  #define DDRCMD0_CR_MASTERDLLCFG_DftEn_MIN                            (0)
  #define DDRCMD0_CR_MASTERDLLCFG_DftEn_MAX                            (1) // 0x00000001
  #define DDRCMD0_CR_MASTERDLLCFG_DftEn_DEF                            (0x00000000)
  #define DDRCMD0_CR_MASTERDLLCFG_DftEn_HSH                            (0x01172500)

  #define DDRCMD0_CR_MASTERDLLCFG_spare0_OFF                           (24)
  #define DDRCMD0_CR_MASTERDLLCFG_spare0_WID                           ( 8)
  #define DDRCMD0_CR_MASTERDLLCFG_spare0_MSK                           (0xFF000000)
  #define DDRCMD0_CR_MASTERDLLCFG_spare0_MIN                           (0)
  #define DDRCMD0_CR_MASTERDLLCFG_spare0_MAX                           (255) // 0x000000FF
  #define DDRCMD0_CR_MASTERDLLCFG_spare0_DEF                           (0x00000000)
  #define DDRCMD0_CR_MASTERDLLCFG_spare0_HSH                           (0x08182500)

#define DDRCMD0_CR_CBTUNE0_REG                                         (0x00002504)

  #define DDRCMD0_CR_CBTUNE0_DllBWEn_OFF                               ( 0)
  #define DDRCMD0_CR_CBTUNE0_DllBWEn_WID                               (32)
  #define DDRCMD0_CR_CBTUNE0_DllBWEn_MSK                               (0xFFFFFFFF)
  #define DDRCMD0_CR_CBTUNE0_DllBWEn_MIN                               (0)
  #define DDRCMD0_CR_CBTUNE0_DllBWEn_MAX                               (4294967295) // 0xFFFFFFFF
  #define DDRCMD0_CR_CBTUNE0_DllBWEn_DEF                               (0xFDB86521)
  #define DDRCMD0_CR_CBTUNE0_DllBWEn_HSH                               (0x20002504)

#define DDRCMD0_CR_CBTUNE1_REG                                         (0x00002508)

  #define DDRCMD0_CR_CBTUNE1_PiCbEn_OFF                                ( 0)
  #define DDRCMD0_CR_CBTUNE1_PiCbEn_WID                                (24)
  #define DDRCMD0_CR_CBTUNE1_PiCbEn_MSK                                (0x00FFFFFF)
  #define DDRCMD0_CR_CBTUNE1_PiCbEn_MIN                                (0)
  #define DDRCMD0_CR_CBTUNE1_PiCbEn_MAX                                (16777215) // 0x00FFFFFF
  #define DDRCMD0_CR_CBTUNE1_PiCbEn_DEF                                (0x00249492)
  #define DDRCMD0_CR_CBTUNE1_PiCbEn_HSH                                (0x18002508)

  #define DDRCMD0_CR_CBTUNE1_CbEnRsvd_OFF                              (24)
  #define DDRCMD0_CR_CBTUNE1_CbEnRsvd_WID                              ( 3)
  #define DDRCMD0_CR_CBTUNE1_CbEnRsvd_MSK                              (0x07000000)
  #define DDRCMD0_CR_CBTUNE1_CbEnRsvd_MIN                              (0)
  #define DDRCMD0_CR_CBTUNE1_CbEnRsvd_MAX                              (7) // 0x00000007
  #define DDRCMD0_CR_CBTUNE1_CbEnRsvd_DEF                              (0x00000000)
  #define DDRCMD0_CR_CBTUNE1_CbEnRsvd_HSH                              (0x03182508)

  #define DDRCMD0_CR_CBTUNE1_CbEnDllFuse_OFF                           (27)
  #define DDRCMD0_CR_CBTUNE1_CbEnDllFuse_WID                           ( 3)
  #define DDRCMD0_CR_CBTUNE1_CbEnDllFuse_MSK                           (0x38000000)
  #define DDRCMD0_CR_CBTUNE1_CbEnDllFuse_MIN                           (0)
  #define DDRCMD0_CR_CBTUNE1_CbEnDllFuse_MAX                           (7) // 0x00000007
  #define DDRCMD0_CR_CBTUNE1_CbEnDllFuse_DEF                           (0x00000002)
  #define DDRCMD0_CR_CBTUNE1_CbEnDllFuse_HSH                           (0x031B2508)

  #define DDRCMD0_CR_CBTUNE1_Spare_OFF                                 (30)
  #define DDRCMD0_CR_CBTUNE1_Spare_WID                                 ( 2)
  #define DDRCMD0_CR_CBTUNE1_Spare_MSK                                 (0xC0000000)
  #define DDRCMD0_CR_CBTUNE1_Spare_MIN                                 (0)
  #define DDRCMD0_CR_CBTUNE1_Spare_MAX                                 (3) // 0x00000003
  #define DDRCMD0_CR_CBTUNE1_Spare_DEF                                 (0x00000000)
  #define DDRCMD0_CR_CBTUNE1_Spare_HSH                                 (0x021E2508)

#define DDRCMD0_CR_ADCCFG_REG                                          (0x0000250C)

  #define DDRCMD0_CR_ADCCFG_ADC_frz_OFF                                ( 0)
  #define DDRCMD0_CR_ADCCFG_ADC_frz_WID                                ( 1)
  #define DDRCMD0_CR_ADCCFG_ADC_frz_MSK                                (0x00000001)
  #define DDRCMD0_CR_ADCCFG_ADC_frz_MIN                                (0)
  #define DDRCMD0_CR_ADCCFG_ADC_frz_MAX                                (1) // 0x00000001
  #define DDRCMD0_CR_ADCCFG_ADC_frz_DEF                                (0x00000000)
  #define DDRCMD0_CR_ADCCFG_ADC_frz_HSH                                (0x0100250C)

  #define DDRCMD0_CR_ADCCFG_ADC_en_OFF                                 ( 1)
  #define DDRCMD0_CR_ADCCFG_ADC_en_WID                                 ( 1)
  #define DDRCMD0_CR_ADCCFG_ADC_en_MSK                                 (0x00000002)
  #define DDRCMD0_CR_ADCCFG_ADC_en_MIN                                 (0)
  #define DDRCMD0_CR_ADCCFG_ADC_en_MAX                                 (1) // 0x00000001
  #define DDRCMD0_CR_ADCCFG_ADC_en_DEF                                 (0x00000000)
  #define DDRCMD0_CR_ADCCFG_ADC_en_HSH                                 (0x0101250C)

  #define DDRCMD0_CR_ADCCFG_ADCclkdiv_OFF                              ( 2)
  #define DDRCMD0_CR_ADCCFG_ADCclkdiv_WID                              ( 2)
  #define DDRCMD0_CR_ADCCFG_ADCclkdiv_MSK                              (0x0000000C)
  #define DDRCMD0_CR_ADCCFG_ADCclkdiv_MIN                              (0)
  #define DDRCMD0_CR_ADCCFG_ADCclkdiv_MAX                              (3) // 0x00000003
  #define DDRCMD0_CR_ADCCFG_ADCclkdiv_DEF                              (0x00000000)
  #define DDRCMD0_CR_ADCCFG_ADCclkdiv_HSH                              (0x0202250C)

  #define DDRCMD0_CR_ADCCFG_ADCstartcount_OFF                          ( 4)
  #define DDRCMD0_CR_ADCCFG_ADCstartcount_WID                          ( 2)
  #define DDRCMD0_CR_ADCCFG_ADCstartcount_MSK                          (0x00000030)
  #define DDRCMD0_CR_ADCCFG_ADCstartcount_MIN                          (0)
  #define DDRCMD0_CR_ADCCFG_ADCstartcount_MAX                          (3) // 0x00000003
  #define DDRCMD0_CR_ADCCFG_ADCstartcount_DEF                          (0x00000000)
  #define DDRCMD0_CR_ADCCFG_ADCstartcount_HSH                          (0x0204250C)

  #define DDRCMD0_CR_ADCCFG_ADCChopEn_OFF                              ( 6)
  #define DDRCMD0_CR_ADCCFG_ADCChopEn_WID                              ( 1)
  #define DDRCMD0_CR_ADCCFG_ADCChopEn_MSK                              (0x00000040)
  #define DDRCMD0_CR_ADCCFG_ADCChopEn_MIN                              (0)
  #define DDRCMD0_CR_ADCCFG_ADCChopEn_MAX                              (1) // 0x00000001
  #define DDRCMD0_CR_ADCCFG_ADCChopEn_DEF                              (0x00000000)
  #define DDRCMD0_CR_ADCCFG_ADCChopEn_HSH                              (0x0106250C)

  #define DDRCMD0_CR_ADCCFG_Spare_OFF                                  ( 7)
  #define DDRCMD0_CR_ADCCFG_Spare_WID                                  (25)
  #define DDRCMD0_CR_ADCCFG_Spare_MSK                                  (0xFFFFFF80)
  #define DDRCMD0_CR_ADCCFG_Spare_MIN                                  (0)
  #define DDRCMD0_CR_ADCCFG_Spare_MAX                                  (33554431) // 0x01FFFFFF
  #define DDRCMD0_CR_ADCCFG_Spare_DEF                                  (0x00000000)
  #define DDRCMD0_CR_ADCCFG_Spare_HSH                                  (0x1907250C)

#define DDRCMD0_CR_CBTUNE2_REG                                         (0x00002510)

  #define DDRCMD0_CR_CBTUNE2_DllCbEn_OFF                               ( 0)
  #define DDRCMD0_CR_CBTUNE2_DllCbEn_WID                               (16)
  #define DDRCMD0_CR_CBTUNE2_DllCbEn_MSK                               (0x0000FFFF)
  #define DDRCMD0_CR_CBTUNE2_DllCbEn_MIN                               (0)
  #define DDRCMD0_CR_CBTUNE2_DllCbEn_MAX                               (65535) // 0x0000FFFF
  #define DDRCMD0_CR_CBTUNE2_DllCbEn_DEF                               (0x00000000)
  #define DDRCMD0_CR_CBTUNE2_DllCbEn_HSH                               (0x10002510)

  #define DDRCMD0_CR_CBTUNE2_Spare_OFF                                 (16)
  #define DDRCMD0_CR_CBTUNE2_Spare_WID                                 (16)
  #define DDRCMD0_CR_CBTUNE2_Spare_MSK                                 (0xFFFF0000)
  #define DDRCMD0_CR_CBTUNE2_Spare_MIN                                 (0)
  #define DDRCMD0_CR_CBTUNE2_Spare_MAX                                 (65535) // 0x0000FFFF
  #define DDRCMD0_CR_CBTUNE2_Spare_DEF                                 (0x00000000)
  #define DDRCMD0_CR_CBTUNE2_Spare_HSH                                 (0x10102510)

#define DDRCMD0_CR_PIDFTDLY_REG                                        (0x00002518)

  #define DDRCMD0_CR_PIDFTDLY_PiDftDelay_OFF                           ( 0)
  #define DDRCMD0_CR_PIDFTDLY_PiDftDelay_WID                           ( 7)
  #define DDRCMD0_CR_PIDFTDLY_PiDftDelay_MSK                           (0x0000007F)
  #define DDRCMD0_CR_PIDFTDLY_PiDftDelay_MIN                           (0)
  #define DDRCMD0_CR_PIDFTDLY_PiDftDelay_MAX                           (127) // 0x0000007F
  #define DDRCMD0_CR_PIDFTDLY_PiDftDelay_DEF                           (0x00000000)
  #define DDRCMD0_CR_PIDFTDLY_PiDftDelay_HSH                           (0x07002518)

  #define DDRCMD0_CR_PIDFTDLY_Ch0PiEnOvrd_OFF                          ( 7)
  #define DDRCMD0_CR_PIDFTDLY_Ch0PiEnOvrd_WID                          ( 1)
  #define DDRCMD0_CR_PIDFTDLY_Ch0PiEnOvrd_MSK                          (0x00000080)
  #define DDRCMD0_CR_PIDFTDLY_Ch0PiEnOvrd_MIN                          (0)
  #define DDRCMD0_CR_PIDFTDLY_Ch0PiEnOvrd_MAX                          (1) // 0x00000001
  #define DDRCMD0_CR_PIDFTDLY_Ch0PiEnOvrd_DEF                          (0x00000000)
  #define DDRCMD0_CR_PIDFTDLY_Ch0PiEnOvrd_HSH                          (0x01072518)

  #define DDRCMD0_CR_PIDFTDLY_Ch1PiEnOvrd_OFF                          ( 8)
  #define DDRCMD0_CR_PIDFTDLY_Ch1PiEnOvrd_WID                          ( 1)
  #define DDRCMD0_CR_PIDFTDLY_Ch1PiEnOvrd_MSK                          (0x00000100)
  #define DDRCMD0_CR_PIDFTDLY_Ch1PiEnOvrd_MIN                          (0)
  #define DDRCMD0_CR_PIDFTDLY_Ch1PiEnOvrd_MAX                          (1) // 0x00000001
  #define DDRCMD0_CR_PIDFTDLY_Ch1PiEnOvrd_DEF                          (0x00000000)
  #define DDRCMD0_CR_PIDFTDLY_Ch1PiEnOvrd_HSH                          (0x01082518)

  #define DDRCMD0_CR_PIDFTDLY_Ch0PiDFTEn_OFF                           ( 9)
  #define DDRCMD0_CR_PIDFTDLY_Ch0PiDFTEn_WID                           ( 1)
  #define DDRCMD0_CR_PIDFTDLY_Ch0PiDFTEn_MSK                           (0x00000200)
  #define DDRCMD0_CR_PIDFTDLY_Ch0PiDFTEn_MIN                           (0)
  #define DDRCMD0_CR_PIDFTDLY_Ch0PiDFTEn_MAX                           (1) // 0x00000001
  #define DDRCMD0_CR_PIDFTDLY_Ch0PiDFTEn_DEF                           (0x00000000)
  #define DDRCMD0_CR_PIDFTDLY_Ch0PiDFTEn_HSH                           (0x01092518)

  #define DDRCMD0_CR_PIDFTDLY_Ch1PiDFTEn_OFF                           (10)
  #define DDRCMD0_CR_PIDFTDLY_Ch1PiDFTEn_WID                           ( 1)
  #define DDRCMD0_CR_PIDFTDLY_Ch1PiDFTEn_MSK                           (0x00000400)
  #define DDRCMD0_CR_PIDFTDLY_Ch1PiDFTEn_MIN                           (0)
  #define DDRCMD0_CR_PIDFTDLY_Ch1PiDFTEn_MAX                           (1) // 0x00000001
  #define DDRCMD0_CR_PIDFTDLY_Ch1PiDFTEn_DEF                           (0x00000000)
  #define DDRCMD0_CR_PIDFTDLY_Ch1PiDFTEn_HSH                           (0x010A2518)

  #define DDRCMD0_CR_PIDFTDLY_Spare_OFF                                (11)
  #define DDRCMD0_CR_PIDFTDLY_Spare_WID                                ( 4)
  #define DDRCMD0_CR_PIDFTDLY_Spare_MSK                                (0x00007800)
  #define DDRCMD0_CR_PIDFTDLY_Spare_MIN                                (0)
  #define DDRCMD0_CR_PIDFTDLY_Spare_MAX                                (15) // 0x0000000F
  #define DDRCMD0_CR_PIDFTDLY_Spare_DEF                                (0x00000000)
  #define DDRCMD0_CR_PIDFTDLY_Spare_HSH                                (0x040B2518)

  #define DDRCMD0_CR_PIDFTDLY_RefPiOvrd_OFF                            (15)
  #define DDRCMD0_CR_PIDFTDLY_RefPiOvrd_WID                            ( 1)
  #define DDRCMD0_CR_PIDFTDLY_RefPiOvrd_MSK                            (0x00008000)
  #define DDRCMD0_CR_PIDFTDLY_RefPiOvrd_MIN                            (0)
  #define DDRCMD0_CR_PIDFTDLY_RefPiOvrd_MAX                            (1) // 0x00000001
  #define DDRCMD0_CR_PIDFTDLY_RefPiOvrd_DEF                            (0x00000000)
  #define DDRCMD0_CR_PIDFTDLY_RefPiOvrd_HSH                            (0x010F2518)

  #define DDRCMD0_CR_PIDFTDLY_Rsvd_OFF                                 (16)
  #define DDRCMD0_CR_PIDFTDLY_Rsvd_WID                                 (16)
  #define DDRCMD0_CR_PIDFTDLY_Rsvd_MSK                                 (0xFFFF0000)
  #define DDRCMD0_CR_PIDFTDLY_Rsvd_MIN                                 (0)
  #define DDRCMD0_CR_PIDFTDLY_Rsvd_MAX                                 (65535) // 0x0000FFFF
  #define DDRCMD0_CR_PIDFTDLY_Rsvd_DEF                                 (0x00000000)
  #define DDRCMD0_CR_PIDFTDLY_Rsvd_HSH                                 (0x10102518)

#define DDRCMD0_CR_DLLPITESTANDADC_REG                                 (0x0000251C)

  #define DDRCMD0_CR_DLLPITESTANDADC_RunTest_OFF                       ( 0)
  #define DDRCMD0_CR_DLLPITESTANDADC_RunTest_WID                       ( 1)
  #define DDRCMD0_CR_DLLPITESTANDADC_RunTest_MSK                       (0x00000001)
  #define DDRCMD0_CR_DLLPITESTANDADC_RunTest_MIN                       (0)
  #define DDRCMD0_CR_DLLPITESTANDADC_RunTest_MAX                       (1) // 0x00000001
  #define DDRCMD0_CR_DLLPITESTANDADC_RunTest_DEF                       (0x00000000)
  #define DDRCMD0_CR_DLLPITESTANDADC_RunTest_HSH                       (0x0100251C)

  #define DDRCMD0_CR_DLLPITESTANDADC_Load_OFF                          ( 1)
  #define DDRCMD0_CR_DLLPITESTANDADC_Load_WID                          ( 1)
  #define DDRCMD0_CR_DLLPITESTANDADC_Load_MSK                          (0x00000002)
  #define DDRCMD0_CR_DLLPITESTANDADC_Load_MIN                          (0)
  #define DDRCMD0_CR_DLLPITESTANDADC_Load_MAX                          (1) // 0x00000001
  #define DDRCMD0_CR_DLLPITESTANDADC_Load_DEF                          (0x00000000)
  #define DDRCMD0_CR_DLLPITESTANDADC_Load_HSH                          (0x0101251C)

  #define DDRCMD0_CR_DLLPITESTANDADC_ModeHVM_OFF                       ( 2)
  #define DDRCMD0_CR_DLLPITESTANDADC_ModeHVM_WID                       ( 1)
  #define DDRCMD0_CR_DLLPITESTANDADC_ModeHVM_MSK                       (0x00000004)
  #define DDRCMD0_CR_DLLPITESTANDADC_ModeHVM_MIN                       (0)
  #define DDRCMD0_CR_DLLPITESTANDADC_ModeHVM_MAX                       (1) // 0x00000001
  #define DDRCMD0_CR_DLLPITESTANDADC_ModeHVM_DEF                       (0x00000000)
  #define DDRCMD0_CR_DLLPITESTANDADC_ModeHVM_HSH                       (0x0102251C)

  #define DDRCMD0_CR_DLLPITESTANDADC_ModeDV_OFF                        ( 3)
  #define DDRCMD0_CR_DLLPITESTANDADC_ModeDV_WID                        ( 1)
  #define DDRCMD0_CR_DLLPITESTANDADC_ModeDV_MSK                        (0x00000008)
  #define DDRCMD0_CR_DLLPITESTANDADC_ModeDV_MIN                        (0)
  #define DDRCMD0_CR_DLLPITESTANDADC_ModeDV_MAX                        (1) // 0x00000001
  #define DDRCMD0_CR_DLLPITESTANDADC_ModeDV_DEF                        (0x00000000)
  #define DDRCMD0_CR_DLLPITESTANDADC_ModeDV_HSH                        (0x0103251C)

  #define DDRCMD0_CR_DLLPITESTANDADC_CalCfdl_OFF                       ( 4)
  #define DDRCMD0_CR_DLLPITESTANDADC_CalCfdl_WID                       ( 1)
  #define DDRCMD0_CR_DLLPITESTANDADC_CalCfdl_MSK                       (0x00000010)
  #define DDRCMD0_CR_DLLPITESTANDADC_CalCfdl_MIN                       (0)
  #define DDRCMD0_CR_DLLPITESTANDADC_CalCfdl_MAX                       (1) // 0x00000001
  #define DDRCMD0_CR_DLLPITESTANDADC_CalCfdl_DEF                       (0x00000000)
  #define DDRCMD0_CR_DLLPITESTANDADC_CalCfdl_HSH                       (0x0104251C)

  #define DDRCMD0_CR_DLLPITESTANDADC_LoadCount_OFF                     ( 5)
  #define DDRCMD0_CR_DLLPITESTANDADC_LoadCount_WID                     (10)
  #define DDRCMD0_CR_DLLPITESTANDADC_LoadCount_MSK                     (0x00007FE0)
  #define DDRCMD0_CR_DLLPITESTANDADC_LoadCount_MIN                     (0)
  #define DDRCMD0_CR_DLLPITESTANDADC_LoadCount_MAX                     (1023) // 0x000003FF
  #define DDRCMD0_CR_DLLPITESTANDADC_LoadCount_DEF                     (0x00000000)
  #define DDRCMD0_CR_DLLPITESTANDADC_LoadCount_HSH                     (0x0A05251C)

  #define DDRCMD0_CR_DLLPITESTANDADC_CountStatus_OFF                   (15)
  #define DDRCMD0_CR_DLLPITESTANDADC_CountStatus_WID                   (10)
  #define DDRCMD0_CR_DLLPITESTANDADC_CountStatus_MSK                   (0x01FF8000)
  #define DDRCMD0_CR_DLLPITESTANDADC_CountStatus_MIN                   (0)
  #define DDRCMD0_CR_DLLPITESTANDADC_CountStatus_MAX                   (1023) // 0x000003FF
  #define DDRCMD0_CR_DLLPITESTANDADC_CountStatus_DEF                   (0x00000000)
  #define DDRCMD0_CR_DLLPITESTANDADC_CountStatus_HSH                   (0x0A0F251C)

  #define DDRCMD0_CR_DLLPITESTANDADC_ModeADC_OFF                       (25)
  #define DDRCMD0_CR_DLLPITESTANDADC_ModeADC_WID                       ( 1)
  #define DDRCMD0_CR_DLLPITESTANDADC_ModeADC_MSK                       (0x02000000)
  #define DDRCMD0_CR_DLLPITESTANDADC_ModeADC_MIN                       (0)
  #define DDRCMD0_CR_DLLPITESTANDADC_ModeADC_MAX                       (1) // 0x00000001
  #define DDRCMD0_CR_DLLPITESTANDADC_ModeADC_DEF                       (0x00000000)
  #define DDRCMD0_CR_DLLPITESTANDADC_ModeADC_HSH                       (0x0119251C)

  #define DDRCMD0_CR_DLLPITESTANDADC_ADCClkDiv_OFF                     (26)
  #define DDRCMD0_CR_DLLPITESTANDADC_ADCClkDiv_WID                     ( 2)
  #define DDRCMD0_CR_DLLPITESTANDADC_ADCClkDiv_MSK                     (0x0C000000)
  #define DDRCMD0_CR_DLLPITESTANDADC_ADCClkDiv_MIN                     (0)
  #define DDRCMD0_CR_DLLPITESTANDADC_ADCClkDiv_MAX                     (3) // 0x00000003
  #define DDRCMD0_CR_DLLPITESTANDADC_ADCClkDiv_DEF                     (0x00000000)
  #define DDRCMD0_CR_DLLPITESTANDADC_ADCClkDiv_HSH                     (0x021A251C)

  #define DDRCMD0_CR_DLLPITESTANDADC_ADCDdrChanSel_OFF                 (28)
  #define DDRCMD0_CR_DLLPITESTANDADC_ADCDdrChanSel_WID                 ( 1)
  #define DDRCMD0_CR_DLLPITESTANDADC_ADCDdrChanSel_MSK                 (0x10000000)
  #define DDRCMD0_CR_DLLPITESTANDADC_ADCDdrChanSel_MIN                 (0)
  #define DDRCMD0_CR_DLLPITESTANDADC_ADCDdrChanSel_MAX                 (1) // 0x00000001
  #define DDRCMD0_CR_DLLPITESTANDADC_ADCDdrChanSel_DEF                 (0x00000000)
  #define DDRCMD0_CR_DLLPITESTANDADC_ADCDdrChanSel_HSH                 (0x011C251C)

  #define DDRCMD0_CR_DLLPITESTANDADC_ADCChopEn_OFF                     (29)
  #define DDRCMD0_CR_DLLPITESTANDADC_ADCChopEn_WID                     ( 1)
  #define DDRCMD0_CR_DLLPITESTANDADC_ADCChopEn_MSK                     (0x20000000)
  #define DDRCMD0_CR_DLLPITESTANDADC_ADCChopEn_MIN                     (0)
  #define DDRCMD0_CR_DLLPITESTANDADC_ADCChopEn_MAX                     (1) // 0x00000001
  #define DDRCMD0_CR_DLLPITESTANDADC_ADCChopEn_DEF                     (0x00000000)
  #define DDRCMD0_CR_DLLPITESTANDADC_ADCChopEn_HSH                     (0x011D251C)

  #define DDRCMD0_CR_DLLPITESTANDADC_ADCDone_OFF                       (30)
  #define DDRCMD0_CR_DLLPITESTANDADC_ADCDone_WID                       ( 1)
  #define DDRCMD0_CR_DLLPITESTANDADC_ADCDone_MSK                       (0x40000000)
  #define DDRCMD0_CR_DLLPITESTANDADC_ADCDone_MIN                       (0)
  #define DDRCMD0_CR_DLLPITESTANDADC_ADCDone_MAX                       (1) // 0x00000001
  #define DDRCMD0_CR_DLLPITESTANDADC_ADCDone_DEF                       (0x00000000)
  #define DDRCMD0_CR_DLLPITESTANDADC_ADCDone_HSH                       (0x011E251C)

  #define DDRCMD0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF              (31)
  #define DDRCMD0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID              ( 1)
  #define DDRCMD0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK              (0x80000000)
  #define DDRCMD0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN              (0)
  #define DDRCMD0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX              (1) // 0x00000001
  #define DDRCMD0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF              (0x00000000)
  #define DDRCMD0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH              (0x011F251C)

#define DDRCMD0_CR_DLLSTATUS_REG                                       (0x00002520)

  #define DDRCMD0_CR_DLLSTATUS_DetrmLockStat_OFF                       ( 0)
  #define DDRCMD0_CR_DLLSTATUS_DetrmLockStat_WID                       ( 1)
  #define DDRCMD0_CR_DLLSTATUS_DetrmLockStat_MSK                       (0x00000001)
  #define DDRCMD0_CR_DLLSTATUS_DetrmLockStat_MIN                       (0)
  #define DDRCMD0_CR_DLLSTATUS_DetrmLockStat_MAX                       (1) // 0x00000001
  #define DDRCMD0_CR_DLLSTATUS_DetrmLockStat_DEF                       (0x00000000)
  #define DDRCMD0_CR_DLLSTATUS_DetrmLockStat_HSH                       (0x01002520)

  #define DDRCMD0_CR_DLLSTATUS_FuncLockStat_OFF                        ( 1)
  #define DDRCMD0_CR_DLLSTATUS_FuncLockStat_WID                        ( 1)
  #define DDRCMD0_CR_DLLSTATUS_FuncLockStat_MSK                        (0x00000002)
  #define DDRCMD0_CR_DLLSTATUS_FuncLockStat_MIN                        (0)
  #define DDRCMD0_CR_DLLSTATUS_FuncLockStat_MAX                        (1) // 0x00000001
  #define DDRCMD0_CR_DLLSTATUS_FuncLockStat_DEF                        (0x00000000)
  #define DDRCMD0_CR_DLLSTATUS_FuncLockStat_HSH                        (0x01012520)

  #define DDRCMD0_CR_DLLSTATUS_Lock_OFF                                ( 2)
  #define DDRCMD0_CR_DLLSTATUS_Lock_WID                                ( 1)
  #define DDRCMD0_CR_DLLSTATUS_Lock_MSK                                (0x00000004)
  #define DDRCMD0_CR_DLLSTATUS_Lock_MIN                                (0)
  #define DDRCMD0_CR_DLLSTATUS_Lock_MAX                                (1) // 0x00000001
  #define DDRCMD0_CR_DLLSTATUS_Lock_DEF                                (0x00000000)
  #define DDRCMD0_CR_DLLSTATUS_Lock_HSH                                (0x01022520)

  #define DDRCMD0_CR_DLLSTATUS_Timeout_OFF                             ( 3)
  #define DDRCMD0_CR_DLLSTATUS_Timeout_WID                             ( 1)
  #define DDRCMD0_CR_DLLSTATUS_Timeout_MSK                             (0x00000008)
  #define DDRCMD0_CR_DLLSTATUS_Timeout_MIN                             (0)
  #define DDRCMD0_CR_DLLSTATUS_Timeout_MAX                             (1) // 0x00000001
  #define DDRCMD0_CR_DLLSTATUS_Timeout_DEF                             (0x00000000)
  #define DDRCMD0_CR_DLLSTATUS_Timeout_HSH                             (0x01032520)

  #define DDRCMD0_CR_DLLSTATUS_DllReset_OFF                            ( 4)
  #define DDRCMD0_CR_DLLSTATUS_DllReset_WID                            ( 1)
  #define DDRCMD0_CR_DLLSTATUS_DllReset_MSK                            (0x00000010)
  #define DDRCMD0_CR_DLLSTATUS_DllReset_MIN                            (0)
  #define DDRCMD0_CR_DLLSTATUS_DllReset_MAX                            (1) // 0x00000001
  #define DDRCMD0_CR_DLLSTATUS_DllReset_DEF                            (0x00000000)
  #define DDRCMD0_CR_DLLSTATUS_DllReset_HSH                            (0x01042520)

  #define DDRCMD0_CR_DLLSTATUS_LongLockStat_OFF                        ( 5)
  #define DDRCMD0_CR_DLLSTATUS_LongLockStat_WID                        ( 1)
  #define DDRCMD0_CR_DLLSTATUS_LongLockStat_MSK                        (0x00000020)
  #define DDRCMD0_CR_DLLSTATUS_LongLockStat_MIN                        (0)
  #define DDRCMD0_CR_DLLSTATUS_LongLockStat_MAX                        (1) // 0x00000001
  #define DDRCMD0_CR_DLLSTATUS_LongLockStat_DEF                        (0x00000000)
  #define DDRCMD0_CR_DLLSTATUS_LongLockStat_HSH                        (0x01052520)

  #define DDRCMD0_CR_DLLSTATUS_EarlyLockStat_OFF                       ( 6)
  #define DDRCMD0_CR_DLLSTATUS_EarlyLockStat_WID                       ( 1)
  #define DDRCMD0_CR_DLLSTATUS_EarlyLockStat_MSK                       (0x00000040)
  #define DDRCMD0_CR_DLLSTATUS_EarlyLockStat_MIN                       (0)
  #define DDRCMD0_CR_DLLSTATUS_EarlyLockStat_MAX                       (1) // 0x00000001
  #define DDRCMD0_CR_DLLSTATUS_EarlyLockStat_DEF                       (0x00000000)
  #define DDRCMD0_CR_DLLSTATUS_EarlyLockStat_HSH                       (0x01062520)

  #define DDRCMD0_CR_DLLSTATUS_NormalMode_NotWkLock_OFF                ( 7)
  #define DDRCMD0_CR_DLLSTATUS_NormalMode_NotWkLock_WID                ( 1)
  #define DDRCMD0_CR_DLLSTATUS_NormalMode_NotWkLock_MSK                (0x00000080)
  #define DDRCMD0_CR_DLLSTATUS_NormalMode_NotWkLock_MIN                (0)
  #define DDRCMD0_CR_DLLSTATUS_NormalMode_NotWkLock_MAX                (1) // 0x00000001
  #define DDRCMD0_CR_DLLSTATUS_NormalMode_NotWkLock_DEF                (0x00000000)
  #define DDRCMD0_CR_DLLSTATUS_NormalMode_NotWkLock_HSH                (0x01072520)

  #define DDRCMD0_CR_DLLSTATUS_ADCout_OFF                              ( 8)
  #define DDRCMD0_CR_DLLSTATUS_ADCout_WID                              (10)
  #define DDRCMD0_CR_DLLSTATUS_ADCout_MSK                              (0x0003FF00)
  #define DDRCMD0_CR_DLLSTATUS_ADCout_MIN                              (0)
  #define DDRCMD0_CR_DLLSTATUS_ADCout_MAX                              (1023) // 0x000003FF
  #define DDRCMD0_CR_DLLSTATUS_ADCout_DEF                              (0x00000000)
  #define DDRCMD0_CR_DLLSTATUS_ADCout_HSH                              (0x0A082520)

  #define DDRCMD0_CR_DLLSTATUS_ADCStatus_OFF                           (18)
  #define DDRCMD0_CR_DLLSTATUS_ADCStatus_WID                           ( 1)
  #define DDRCMD0_CR_DLLSTATUS_ADCStatus_MSK                           (0x00040000)
  #define DDRCMD0_CR_DLLSTATUS_ADCStatus_MIN                           (0)
  #define DDRCMD0_CR_DLLSTATUS_ADCStatus_MAX                           (1) // 0x00000001
  #define DDRCMD0_CR_DLLSTATUS_ADCStatus_DEF                           (0x00000000)
  #define DDRCMD0_CR_DLLSTATUS_ADCStatus_HSH                           (0x01122520)

  #define DDRCMD0_CR_DLLSTATUS_pilags_OFF                              (19)
  #define DDRCMD0_CR_DLLSTATUS_pilags_WID                              ( 1)
  #define DDRCMD0_CR_DLLSTATUS_pilags_MSK                              (0x00080000)
  #define DDRCMD0_CR_DLLSTATUS_pilags_MIN                              (0)
  #define DDRCMD0_CR_DLLSTATUS_pilags_MAX                              (1) // 0x00000001
  #define DDRCMD0_CR_DLLSTATUS_pilags_DEF                              (0x00000000)
  #define DDRCMD0_CR_DLLSTATUS_pilags_HSH                              (0x01132520)

  #define DDRCMD0_CR_DLLSTATUS_spare_OFF                               (20)
  #define DDRCMD0_CR_DLLSTATUS_spare_WID                               (12)
  #define DDRCMD0_CR_DLLSTATUS_spare_MSK                               (0xFFF00000)
  #define DDRCMD0_CR_DLLSTATUS_spare_MIN                               (0)
  #define DDRCMD0_CR_DLLSTATUS_spare_MAX                               (4095) // 0x00000FFF
  #define DDRCMD0_CR_DLLSTATUS_spare_DEF                               (0x00000000)
  #define DDRCMD0_CR_DLLSTATUS_spare_HSH                               (0x0C142520)

#define DDRCMD0_CR_DLLDCMCTL_REG                                       (0x00002524)

  #define DDRCMD0_CR_DLLDCMCTL_start_OFF                               ( 0)
  #define DDRCMD0_CR_DLLDCMCTL_start_WID                               ( 1)
  #define DDRCMD0_CR_DLLDCMCTL_start_MSK                               (0x00000001)
  #define DDRCMD0_CR_DLLDCMCTL_start_MIN                               (0)
  #define DDRCMD0_CR_DLLDCMCTL_start_MAX                               (1) // 0x00000001
  #define DDRCMD0_CR_DLLDCMCTL_start_DEF                               (0x00000000)
  #define DDRCMD0_CR_DLLDCMCTL_start_HSH                               (0x01002524)

  #define DDRCMD0_CR_DLLDCMCTL_clken_OFF                               ( 1)
  #define DDRCMD0_CR_DLLDCMCTL_clken_WID                               ( 1)
  #define DDRCMD0_CR_DLLDCMCTL_clken_MSK                               (0x00000002)
  #define DDRCMD0_CR_DLLDCMCTL_clken_MIN                               (0)
  #define DDRCMD0_CR_DLLDCMCTL_clken_MAX                               (1) // 0x00000001
  #define DDRCMD0_CR_DLLDCMCTL_clken_DEF                               (0x00000000)
  #define DDRCMD0_CR_DLLDCMCTL_clken_HSH                               (0x01012524)

  #define DDRCMD0_CR_DLLDCMCTL_dcm_dccctl_en_OFF                       ( 2)
  #define DDRCMD0_CR_DLLDCMCTL_dcm_dccctl_en_WID                       ( 1)
  #define DDRCMD0_CR_DLLDCMCTL_dcm_dccctl_en_MSK                       (0x00000004)
  #define DDRCMD0_CR_DLLDCMCTL_dcm_dccctl_en_MIN                       (0)
  #define DDRCMD0_CR_DLLDCMCTL_dcm_dccctl_en_MAX                       (1) // 0x00000001
  #define DDRCMD0_CR_DLLDCMCTL_dcm_dccctl_en_DEF                       (0x00000000)
  #define DDRCMD0_CR_DLLDCMCTL_dcm_dccctl_en_HSH                       (0x01022524)

  #define DDRCMD0_CR_DLLDCMCTL_dccctl_OFF                              ( 3)
  #define DDRCMD0_CR_DLLDCMCTL_dccctl_WID                              ( 4)
  #define DDRCMD0_CR_DLLDCMCTL_dccctl_MSK                              (0x00000078)
  #define DDRCMD0_CR_DLLDCMCTL_dccctl_MIN                              (0)
  #define DDRCMD0_CR_DLLDCMCTL_dccctl_MAX                              (15) // 0x0000000F
  #define DDRCMD0_CR_DLLDCMCTL_dccctl_DEF                              (0x00000000)
  #define DDRCMD0_CR_DLLDCMCTL_dccctl_HSH                              (0x04032524)

  #define DDRCMD0_CR_DLLDCMCTL_duration_OFF                            ( 7)
  #define DDRCMD0_CR_DLLDCMCTL_duration_WID                            ( 3)
  #define DDRCMD0_CR_DLLDCMCTL_duration_MSK                            (0x00000380)
  #define DDRCMD0_CR_DLLDCMCTL_duration_MIN                            (0)
  #define DDRCMD0_CR_DLLDCMCTL_duration_MAX                            (7) // 0x00000007
  #define DDRCMD0_CR_DLLDCMCTL_duration_DEF                            (0x00000000)
  #define DDRCMD0_CR_DLLDCMCTL_duration_HSH                            (0x03072524)

  #define DDRCMD0_CR_DLLDCMCTL_dcm_done_OFF                            (10)
  #define DDRCMD0_CR_DLLDCMCTL_dcm_done_WID                            ( 1)
  #define DDRCMD0_CR_DLLDCMCTL_dcm_done_MSK                            (0x00000400)
  #define DDRCMD0_CR_DLLDCMCTL_dcm_done_MIN                            (0)
  #define DDRCMD0_CR_DLLDCMCTL_dcm_done_MAX                            (1) // 0x00000001
  #define DDRCMD0_CR_DLLDCMCTL_dcm_done_DEF                            (0x00000000)
  #define DDRCMD0_CR_DLLDCMCTL_dcm_done_HSH                            (0x010A2524)

  #define DDRCMD0_CR_DLLDCMCTL_dcm_results_OFF                         (11)
  #define DDRCMD0_CR_DLLDCMCTL_dcm_results_WID                         (15)
  #define DDRCMD0_CR_DLLDCMCTL_dcm_results_MSK                         (0x03FFF800)
  #define DDRCMD0_CR_DLLDCMCTL_dcm_results_MIN                         (0)
  #define DDRCMD0_CR_DLLDCMCTL_dcm_results_MAX                         (32767) // 0x00007FFF
  #define DDRCMD0_CR_DLLDCMCTL_dcm_results_DEF                         (0x00000000)
  #define DDRCMD0_CR_DLLDCMCTL_dcm_results_HSH                         (0x0F0B2524)

  #define DDRCMD0_CR_DLLDCMCTL_spare0_OFF                              (26)
  #define DDRCMD0_CR_DLLDCMCTL_spare0_WID                              ( 6)
  #define DDRCMD0_CR_DLLDCMCTL_spare0_MSK                              (0xFC000000)
  #define DDRCMD0_CR_DLLDCMCTL_spare0_MIN                              (0)
  #define DDRCMD0_CR_DLLDCMCTL_spare0_MAX                              (63) // 0x0000003F
  #define DDRCMD0_CR_DLLDCMCTL_spare0_DEF                              (0x00000000)
  #define DDRCMD0_CR_DLLDCMCTL_spare0_HSH                              (0x061A2524)

#define DDRCMD1_CR_MASTERDLLCFG_REG                                    (0x00002580)

  #define DDRCMD1_CR_MASTERDLLCFG_LockThresh_OFF                       ( 0)
  #define DDRCMD1_CR_MASTERDLLCFG_LockThresh_WID                       ( 3)
  #define DDRCMD1_CR_MASTERDLLCFG_LockThresh_MSK                       (0x00000007)
  #define DDRCMD1_CR_MASTERDLLCFG_LockThresh_MIN                       (0)
  #define DDRCMD1_CR_MASTERDLLCFG_LockThresh_MAX                       (7) // 0x00000007
  #define DDRCMD1_CR_MASTERDLLCFG_LockThresh_DEF                       (0x00000004)
  #define DDRCMD1_CR_MASTERDLLCFG_LockThresh_HSH                       (0x03002580)

  #define DDRCMD1_CR_MASTERDLLCFG_LockCtr_OFF                          ( 3)
  #define DDRCMD1_CR_MASTERDLLCFG_LockCtr_WID                          ( 2)
  #define DDRCMD1_CR_MASTERDLLCFG_LockCtr_MSK                          (0x00000018)
  #define DDRCMD1_CR_MASTERDLLCFG_LockCtr_MIN                          (0)
  #define DDRCMD1_CR_MASTERDLLCFG_LockCtr_MAX                          (3) // 0x00000003
  #define DDRCMD1_CR_MASTERDLLCFG_LockCtr_DEF                          (0x00000000)
  #define DDRCMD1_CR_MASTERDLLCFG_LockCtr_HSH                          (0x02032580)

  #define DDRCMD1_CR_MASTERDLLCFG_VctrlDischRate_OFF                   ( 5)
  #define DDRCMD1_CR_MASTERDLLCFG_VctrlDischRate_WID                   ( 2)
  #define DDRCMD1_CR_MASTERDLLCFG_VctrlDischRate_MSK                   (0x00000060)
  #define DDRCMD1_CR_MASTERDLLCFG_VctrlDischRate_MIN                   (0)
  #define DDRCMD1_CR_MASTERDLLCFG_VctrlDischRate_MAX                   (3) // 0x00000003
  #define DDRCMD1_CR_MASTERDLLCFG_VctrlDischRate_DEF                   (0x00000000)
  #define DDRCMD1_CR_MASTERDLLCFG_VctrlDischRate_HSH                   (0x02052580)

  #define DDRCMD1_CR_MASTERDLLCFG_SelVctrlHi_OFF                       ( 7)
  #define DDRCMD1_CR_MASTERDLLCFG_SelVctrlHi_WID                       ( 1)
  #define DDRCMD1_CR_MASTERDLLCFG_SelVctrlHi_MSK                       (0x00000080)
  #define DDRCMD1_CR_MASTERDLLCFG_SelVctrlHi_MIN                       (0)
  #define DDRCMD1_CR_MASTERDLLCFG_SelVctrlHi_MAX                       (1) // 0x00000001
  #define DDRCMD1_CR_MASTERDLLCFG_SelVctrlHi_DEF                       (0x00000000)
  #define DDRCMD1_CR_MASTERDLLCFG_SelVctrlHi_HSH                       (0x01072580)

  #define DDRCMD1_CR_MASTERDLLCFG_StartupCntSel_OFF                    ( 8)
  #define DDRCMD1_CR_MASTERDLLCFG_StartupCntSel_WID                    ( 1)
  #define DDRCMD1_CR_MASTERDLLCFG_StartupCntSel_MSK                    (0x00000100)
  #define DDRCMD1_CR_MASTERDLLCFG_StartupCntSel_MIN                    (0)
  #define DDRCMD1_CR_MASTERDLLCFG_StartupCntSel_MAX                    (1) // 0x00000001
  #define DDRCMD1_CR_MASTERDLLCFG_StartupCntSel_DEF                    (0x00000000)
  #define DDRCMD1_CR_MASTERDLLCFG_StartupCntSel_HSH                    (0x01082580)

  #define DDRCMD1_CR_MASTERDLLCFG_LockSel_OFF                          ( 9)
  #define DDRCMD1_CR_MASTERDLLCFG_LockSel_WID                          ( 2)
  #define DDRCMD1_CR_MASTERDLLCFG_LockSel_MSK                          (0x00000600)
  #define DDRCMD1_CR_MASTERDLLCFG_LockSel_MIN                          (0)
  #define DDRCMD1_CR_MASTERDLLCFG_LockSel_MAX                          (3) // 0x00000003
  #define DDRCMD1_CR_MASTERDLLCFG_LockSel_DEF                          (0x00000000)
  #define DDRCMD1_CR_MASTERDLLCFG_LockSel_HSH                          (0x02092580)

  #define DDRCMD1_CR_MASTERDLLCFG_RstOvrd_OFF                          (11)
  #define DDRCMD1_CR_MASTERDLLCFG_RstOvrd_WID                          ( 1)
  #define DDRCMD1_CR_MASTERDLLCFG_RstOvrd_MSK                          (0x00000800)
  #define DDRCMD1_CR_MASTERDLLCFG_RstOvrd_MIN                          (0)
  #define DDRCMD1_CR_MASTERDLLCFG_RstOvrd_MAX                          (1) // 0x00000001
  #define DDRCMD1_CR_MASTERDLLCFG_RstOvrd_DEF                          (0x00000000)
  #define DDRCMD1_CR_MASTERDLLCFG_RstOvrd_HSH                          (0x010B2580)

  #define DDRCMD1_CR_MASTERDLLCFG_SelRstOvrd_OFF                       (12)
  #define DDRCMD1_CR_MASTERDLLCFG_SelRstOvrd_WID                       ( 1)
  #define DDRCMD1_CR_MASTERDLLCFG_SelRstOvrd_MSK                       (0x00001000)
  #define DDRCMD1_CR_MASTERDLLCFG_SelRstOvrd_MIN                       (0)
  #define DDRCMD1_CR_MASTERDLLCFG_SelRstOvrd_MAX                       (1) // 0x00000001
  #define DDRCMD1_CR_MASTERDLLCFG_SelRstOvrd_DEF                       (0x00000000)
  #define DDRCMD1_CR_MASTERDLLCFG_SelRstOvrd_HSH                       (0x010C2580)

  #define DDRCMD1_CR_MASTERDLLCFG_TimeOutOvrd_OFF                      (13)
  #define DDRCMD1_CR_MASTERDLLCFG_TimeOutOvrd_WID                      ( 1)
  #define DDRCMD1_CR_MASTERDLLCFG_TimeOutOvrd_MSK                      (0x00002000)
  #define DDRCMD1_CR_MASTERDLLCFG_TimeOutOvrd_MIN                      (0)
  #define DDRCMD1_CR_MASTERDLLCFG_TimeOutOvrd_MAX                      (1) // 0x00000001
  #define DDRCMD1_CR_MASTERDLLCFG_TimeOutOvrd_DEF                      (0x00000000)
  #define DDRCMD1_CR_MASTERDLLCFG_TimeOutOvrd_HSH                      (0x010D2580)

  #define DDRCMD1_CR_MASTERDLLCFG_SelTimeOutOvrd_OFF                   (14)
  #define DDRCMD1_CR_MASTERDLLCFG_SelTimeOutOvrd_WID                   ( 1)
  #define DDRCMD1_CR_MASTERDLLCFG_SelTimeOutOvrd_MSK                   (0x00004000)
  #define DDRCMD1_CR_MASTERDLLCFG_SelTimeOutOvrd_MIN                   (0)
  #define DDRCMD1_CR_MASTERDLLCFG_SelTimeOutOvrd_MAX                   (1) // 0x00000001
  #define DDRCMD1_CR_MASTERDLLCFG_SelTimeOutOvrd_DEF                   (0x00000000)
  #define DDRCMD1_CR_MASTERDLLCFG_SelTimeOutOvrd_HSH                   (0x010E2580)

  #define DDRCMD1_CR_MASTERDLLCFG_ClkGateOvrd_OFF                      (15)
  #define DDRCMD1_CR_MASTERDLLCFG_ClkGateOvrd_WID                      ( 1)
  #define DDRCMD1_CR_MASTERDLLCFG_ClkGateOvrd_MSK                      (0x00008000)
  #define DDRCMD1_CR_MASTERDLLCFG_ClkGateOvrd_MIN                      (0)
  #define DDRCMD1_CR_MASTERDLLCFG_ClkGateOvrd_MAX                      (1) // 0x00000001
  #define DDRCMD1_CR_MASTERDLLCFG_ClkGateOvrd_DEF                      (0x00000000)
  #define DDRCMD1_CR_MASTERDLLCFG_ClkGateOvrd_HSH                      (0x010F2580)

  #define DDRCMD1_CR_MASTERDLLCFG_LockOvrd_OFF                         (16)
  #define DDRCMD1_CR_MASTERDLLCFG_LockOvrd_WID                         ( 1)
  #define DDRCMD1_CR_MASTERDLLCFG_LockOvrd_MSK                         (0x00010000)
  #define DDRCMD1_CR_MASTERDLLCFG_LockOvrd_MIN                         (0)
  #define DDRCMD1_CR_MASTERDLLCFG_LockOvrd_MAX                         (1) // 0x00000001
  #define DDRCMD1_CR_MASTERDLLCFG_LockOvrd_DEF                         (0x00000000)
  #define DDRCMD1_CR_MASTERDLLCFG_LockOvrd_HSH                         (0x01102580)

  #define DDRCMD1_CR_MASTERDLLCFG_SelLockOvrd_OFF                      (17)
  #define DDRCMD1_CR_MASTERDLLCFG_SelLockOvrd_WID                      ( 1)
  #define DDRCMD1_CR_MASTERDLLCFG_SelLockOvrd_MSK                      (0x00020000)
  #define DDRCMD1_CR_MASTERDLLCFG_SelLockOvrd_MIN                      (0)
  #define DDRCMD1_CR_MASTERDLLCFG_SelLockOvrd_MAX                      (1) // 0x00000001
  #define DDRCMD1_CR_MASTERDLLCFG_SelLockOvrd_DEF                      (0x00000000)
  #define DDRCMD1_CR_MASTERDLLCFG_SelLockOvrd_HSH                      (0x01112580)

  #define DDRCMD1_CR_MASTERDLLCFG_OpenLoopOvrd_OFF                     (18)
  #define DDRCMD1_CR_MASTERDLLCFG_OpenLoopOvrd_WID                     ( 1)
  #define DDRCMD1_CR_MASTERDLLCFG_OpenLoopOvrd_MSK                     (0x00040000)
  #define DDRCMD1_CR_MASTERDLLCFG_OpenLoopOvrd_MIN                     (0)
  #define DDRCMD1_CR_MASTERDLLCFG_OpenLoopOvrd_MAX                     (1) // 0x00000001
  #define DDRCMD1_CR_MASTERDLLCFG_OpenLoopOvrd_DEF                     (0x00000000)
  #define DDRCMD1_CR_MASTERDLLCFG_OpenLoopOvrd_HSH                     (0x01122580)

  #define DDRCMD1_CR_MASTERDLLCFG_SelOpenLoopOvrd_OFF                  (19)
  #define DDRCMD1_CR_MASTERDLLCFG_SelOpenLoopOvrd_WID                  ( 1)
  #define DDRCMD1_CR_MASTERDLLCFG_SelOpenLoopOvrd_MSK                  (0x00080000)
  #define DDRCMD1_CR_MASTERDLLCFG_SelOpenLoopOvrd_MIN                  (0)
  #define DDRCMD1_CR_MASTERDLLCFG_SelOpenLoopOvrd_MAX                  (1) // 0x00000001
  #define DDRCMD1_CR_MASTERDLLCFG_SelOpenLoopOvrd_DEF                  (0x00000000)
  #define DDRCMD1_CR_MASTERDLLCFG_SelOpenLoopOvrd_HSH                  (0x01132580)

  #define DDRCMD1_CR_MASTERDLLCFG_WkLockEnOvrd_OFF                     (20)
  #define DDRCMD1_CR_MASTERDLLCFG_WkLockEnOvrd_WID                     ( 1)
  #define DDRCMD1_CR_MASTERDLLCFG_WkLockEnOvrd_MSK                     (0x00100000)
  #define DDRCMD1_CR_MASTERDLLCFG_WkLockEnOvrd_MIN                     (0)
  #define DDRCMD1_CR_MASTERDLLCFG_WkLockEnOvrd_MAX                     (1) // 0x00000001
  #define DDRCMD1_CR_MASTERDLLCFG_WkLockEnOvrd_DEF                     (0x00000000)
  #define DDRCMD1_CR_MASTERDLLCFG_WkLockEnOvrd_HSH                     (0x01142580)

  #define DDRCMD1_CR_MASTERDLLCFG_SelWkLockEnOvrd_OFF                  (21)
  #define DDRCMD1_CR_MASTERDLLCFG_SelWkLockEnOvrd_WID                  ( 1)
  #define DDRCMD1_CR_MASTERDLLCFG_SelWkLockEnOvrd_MSK                  (0x00200000)
  #define DDRCMD1_CR_MASTERDLLCFG_SelWkLockEnOvrd_MIN                  (0)
  #define DDRCMD1_CR_MASTERDLLCFG_SelWkLockEnOvrd_MAX                  (1) // 0x00000001
  #define DDRCMD1_CR_MASTERDLLCFG_SelWkLockEnOvrd_DEF                  (0x00000000)
  #define DDRCMD1_CR_MASTERDLLCFG_SelWkLockEnOvrd_HSH                  (0x01152580)

  #define DDRCMD1_CR_MASTERDLLCFG_CfdlDis_OFF                          (22)
  #define DDRCMD1_CR_MASTERDLLCFG_CfdlDis_WID                          ( 1)
  #define DDRCMD1_CR_MASTERDLLCFG_CfdlDis_MSK                          (0x00400000)
  #define DDRCMD1_CR_MASTERDLLCFG_CfdlDis_MIN                          (0)
  #define DDRCMD1_CR_MASTERDLLCFG_CfdlDis_MAX                          (1) // 0x00000001
  #define DDRCMD1_CR_MASTERDLLCFG_CfdlDis_DEF                          (0x00000000)
  #define DDRCMD1_CR_MASTERDLLCFG_CfdlDis_HSH                          (0x01162580)

  #define DDRCMD1_CR_MASTERDLLCFG_DftEn_OFF                            (23)
  #define DDRCMD1_CR_MASTERDLLCFG_DftEn_WID                            ( 1)
  #define DDRCMD1_CR_MASTERDLLCFG_DftEn_MSK                            (0x00800000)
  #define DDRCMD1_CR_MASTERDLLCFG_DftEn_MIN                            (0)
  #define DDRCMD1_CR_MASTERDLLCFG_DftEn_MAX                            (1) // 0x00000001
  #define DDRCMD1_CR_MASTERDLLCFG_DftEn_DEF                            (0x00000000)
  #define DDRCMD1_CR_MASTERDLLCFG_DftEn_HSH                            (0x01172580)

  #define DDRCMD1_CR_MASTERDLLCFG_spare0_OFF                           (24)
  #define DDRCMD1_CR_MASTERDLLCFG_spare0_WID                           ( 8)
  #define DDRCMD1_CR_MASTERDLLCFG_spare0_MSK                           (0xFF000000)
  #define DDRCMD1_CR_MASTERDLLCFG_spare0_MIN                           (0)
  #define DDRCMD1_CR_MASTERDLLCFG_spare0_MAX                           (255) // 0x000000FF
  #define DDRCMD1_CR_MASTERDLLCFG_spare0_DEF                           (0x00000000)
  #define DDRCMD1_CR_MASTERDLLCFG_spare0_HSH                           (0x08182580)

#define DDRCMD1_CR_CBTUNE0_REG                                         (0x00002584)

  #define DDRCMD1_CR_CBTUNE0_DllBWEn_OFF                               ( 0)
  #define DDRCMD1_CR_CBTUNE0_DllBWEn_WID                               (32)
  #define DDRCMD1_CR_CBTUNE0_DllBWEn_MSK                               (0xFFFFFFFF)
  #define DDRCMD1_CR_CBTUNE0_DllBWEn_MIN                               (0)
  #define DDRCMD1_CR_CBTUNE0_DllBWEn_MAX                               (4294967295) // 0xFFFFFFFF
  #define DDRCMD1_CR_CBTUNE0_DllBWEn_DEF                               (0xFDB86521)
  #define DDRCMD1_CR_CBTUNE0_DllBWEn_HSH                               (0x20002584)

#define DDRCMD1_CR_CBTUNE1_REG                                         (0x00002588)

  #define DDRCMD1_CR_CBTUNE1_PiCbEn_OFF                                ( 0)
  #define DDRCMD1_CR_CBTUNE1_PiCbEn_WID                                (24)
  #define DDRCMD1_CR_CBTUNE1_PiCbEn_MSK                                (0x00FFFFFF)
  #define DDRCMD1_CR_CBTUNE1_PiCbEn_MIN                                (0)
  #define DDRCMD1_CR_CBTUNE1_PiCbEn_MAX                                (16777215) // 0x00FFFFFF
  #define DDRCMD1_CR_CBTUNE1_PiCbEn_DEF                                (0x00249492)
  #define DDRCMD1_CR_CBTUNE1_PiCbEn_HSH                                (0x18002588)

  #define DDRCMD1_CR_CBTUNE1_CbEnRsvd_OFF                              (24)
  #define DDRCMD1_CR_CBTUNE1_CbEnRsvd_WID                              ( 3)
  #define DDRCMD1_CR_CBTUNE1_CbEnRsvd_MSK                              (0x07000000)
  #define DDRCMD1_CR_CBTUNE1_CbEnRsvd_MIN                              (0)
  #define DDRCMD1_CR_CBTUNE1_CbEnRsvd_MAX                              (7) // 0x00000007
  #define DDRCMD1_CR_CBTUNE1_CbEnRsvd_DEF                              (0x00000000)
  #define DDRCMD1_CR_CBTUNE1_CbEnRsvd_HSH                              (0x03182588)

  #define DDRCMD1_CR_CBTUNE1_CbEnDllFuse_OFF                           (27)
  #define DDRCMD1_CR_CBTUNE1_CbEnDllFuse_WID                           ( 3)
  #define DDRCMD1_CR_CBTUNE1_CbEnDllFuse_MSK                           (0x38000000)
  #define DDRCMD1_CR_CBTUNE1_CbEnDllFuse_MIN                           (0)
  #define DDRCMD1_CR_CBTUNE1_CbEnDllFuse_MAX                           (7) // 0x00000007
  #define DDRCMD1_CR_CBTUNE1_CbEnDllFuse_DEF                           (0x00000002)
  #define DDRCMD1_CR_CBTUNE1_CbEnDllFuse_HSH                           (0x031B2588)

  #define DDRCMD1_CR_CBTUNE1_Spare_OFF                                 (30)
  #define DDRCMD1_CR_CBTUNE1_Spare_WID                                 ( 2)
  #define DDRCMD1_CR_CBTUNE1_Spare_MSK                                 (0xC0000000)
  #define DDRCMD1_CR_CBTUNE1_Spare_MIN                                 (0)
  #define DDRCMD1_CR_CBTUNE1_Spare_MAX                                 (3) // 0x00000003
  #define DDRCMD1_CR_CBTUNE1_Spare_DEF                                 (0x00000000)
  #define DDRCMD1_CR_CBTUNE1_Spare_HSH                                 (0x021E2588)

#define DDRCMD1_CR_ADCCFG_REG                                          (0x0000258C)

  #define DDRCMD1_CR_ADCCFG_ADC_frz_OFF                                ( 0)
  #define DDRCMD1_CR_ADCCFG_ADC_frz_WID                                ( 1)
  #define DDRCMD1_CR_ADCCFG_ADC_frz_MSK                                (0x00000001)
  #define DDRCMD1_CR_ADCCFG_ADC_frz_MIN                                (0)
  #define DDRCMD1_CR_ADCCFG_ADC_frz_MAX                                (1) // 0x00000001
  #define DDRCMD1_CR_ADCCFG_ADC_frz_DEF                                (0x00000000)
  #define DDRCMD1_CR_ADCCFG_ADC_frz_HSH                                (0x0100258C)

  #define DDRCMD1_CR_ADCCFG_ADC_en_OFF                                 ( 1)
  #define DDRCMD1_CR_ADCCFG_ADC_en_WID                                 ( 1)
  #define DDRCMD1_CR_ADCCFG_ADC_en_MSK                                 (0x00000002)
  #define DDRCMD1_CR_ADCCFG_ADC_en_MIN                                 (0)
  #define DDRCMD1_CR_ADCCFG_ADC_en_MAX                                 (1) // 0x00000001
  #define DDRCMD1_CR_ADCCFG_ADC_en_DEF                                 (0x00000000)
  #define DDRCMD1_CR_ADCCFG_ADC_en_HSH                                 (0x0101258C)

  #define DDRCMD1_CR_ADCCFG_ADCclkdiv_OFF                              ( 2)
  #define DDRCMD1_CR_ADCCFG_ADCclkdiv_WID                              ( 2)
  #define DDRCMD1_CR_ADCCFG_ADCclkdiv_MSK                              (0x0000000C)
  #define DDRCMD1_CR_ADCCFG_ADCclkdiv_MIN                              (0)
  #define DDRCMD1_CR_ADCCFG_ADCclkdiv_MAX                              (3) // 0x00000003
  #define DDRCMD1_CR_ADCCFG_ADCclkdiv_DEF                              (0x00000000)
  #define DDRCMD1_CR_ADCCFG_ADCclkdiv_HSH                              (0x0202258C)

  #define DDRCMD1_CR_ADCCFG_ADCstartcount_OFF                          ( 4)
  #define DDRCMD1_CR_ADCCFG_ADCstartcount_WID                          ( 2)
  #define DDRCMD1_CR_ADCCFG_ADCstartcount_MSK                          (0x00000030)
  #define DDRCMD1_CR_ADCCFG_ADCstartcount_MIN                          (0)
  #define DDRCMD1_CR_ADCCFG_ADCstartcount_MAX                          (3) // 0x00000003
  #define DDRCMD1_CR_ADCCFG_ADCstartcount_DEF                          (0x00000000)
  #define DDRCMD1_CR_ADCCFG_ADCstartcount_HSH                          (0x0204258C)

  #define DDRCMD1_CR_ADCCFG_ADCChopEn_OFF                              ( 6)
  #define DDRCMD1_CR_ADCCFG_ADCChopEn_WID                              ( 1)
  #define DDRCMD1_CR_ADCCFG_ADCChopEn_MSK                              (0x00000040)
  #define DDRCMD1_CR_ADCCFG_ADCChopEn_MIN                              (0)
  #define DDRCMD1_CR_ADCCFG_ADCChopEn_MAX                              (1) // 0x00000001
  #define DDRCMD1_CR_ADCCFG_ADCChopEn_DEF                              (0x00000000)
  #define DDRCMD1_CR_ADCCFG_ADCChopEn_HSH                              (0x0106258C)

  #define DDRCMD1_CR_ADCCFG_Spare_OFF                                  ( 7)
  #define DDRCMD1_CR_ADCCFG_Spare_WID                                  (25)
  #define DDRCMD1_CR_ADCCFG_Spare_MSK                                  (0xFFFFFF80)
  #define DDRCMD1_CR_ADCCFG_Spare_MIN                                  (0)
  #define DDRCMD1_CR_ADCCFG_Spare_MAX                                  (33554431) // 0x01FFFFFF
  #define DDRCMD1_CR_ADCCFG_Spare_DEF                                  (0x00000000)
  #define DDRCMD1_CR_ADCCFG_Spare_HSH                                  (0x1907258C)

#define DDRCMD1_CR_CBTUNE2_REG                                         (0x00002590)

  #define DDRCMD1_CR_CBTUNE2_DllCbEn_OFF                               ( 0)
  #define DDRCMD1_CR_CBTUNE2_DllCbEn_WID                               (16)
  #define DDRCMD1_CR_CBTUNE2_DllCbEn_MSK                               (0x0000FFFF)
  #define DDRCMD1_CR_CBTUNE2_DllCbEn_MIN                               (0)
  #define DDRCMD1_CR_CBTUNE2_DllCbEn_MAX                               (65535) // 0x0000FFFF
  #define DDRCMD1_CR_CBTUNE2_DllCbEn_DEF                               (0x00000000)
  #define DDRCMD1_CR_CBTUNE2_DllCbEn_HSH                               (0x10002590)

  #define DDRCMD1_CR_CBTUNE2_Spare_OFF                                 (16)
  #define DDRCMD1_CR_CBTUNE2_Spare_WID                                 (16)
  #define DDRCMD1_CR_CBTUNE2_Spare_MSK                                 (0xFFFF0000)
  #define DDRCMD1_CR_CBTUNE2_Spare_MIN                                 (0)
  #define DDRCMD1_CR_CBTUNE2_Spare_MAX                                 (65535) // 0x0000FFFF
  #define DDRCMD1_CR_CBTUNE2_Spare_DEF                                 (0x00000000)
  #define DDRCMD1_CR_CBTUNE2_Spare_HSH                                 (0x10102590)

#define DDRCMD1_CR_PIDFTDLY_REG                                        (0x00002598)

  #define DDRCMD1_CR_PIDFTDLY_PiDftDelay_OFF                           ( 0)
  #define DDRCMD1_CR_PIDFTDLY_PiDftDelay_WID                           ( 7)
  #define DDRCMD1_CR_PIDFTDLY_PiDftDelay_MSK                           (0x0000007F)
  #define DDRCMD1_CR_PIDFTDLY_PiDftDelay_MIN                           (0)
  #define DDRCMD1_CR_PIDFTDLY_PiDftDelay_MAX                           (127) // 0x0000007F
  #define DDRCMD1_CR_PIDFTDLY_PiDftDelay_DEF                           (0x00000000)
  #define DDRCMD1_CR_PIDFTDLY_PiDftDelay_HSH                           (0x07002598)

  #define DDRCMD1_CR_PIDFTDLY_Ch0PiEnOvrd_OFF                          ( 7)
  #define DDRCMD1_CR_PIDFTDLY_Ch0PiEnOvrd_WID                          ( 1)
  #define DDRCMD1_CR_PIDFTDLY_Ch0PiEnOvrd_MSK                          (0x00000080)
  #define DDRCMD1_CR_PIDFTDLY_Ch0PiEnOvrd_MIN                          (0)
  #define DDRCMD1_CR_PIDFTDLY_Ch0PiEnOvrd_MAX                          (1) // 0x00000001
  #define DDRCMD1_CR_PIDFTDLY_Ch0PiEnOvrd_DEF                          (0x00000000)
  #define DDRCMD1_CR_PIDFTDLY_Ch0PiEnOvrd_HSH                          (0x01072598)

  #define DDRCMD1_CR_PIDFTDLY_Ch1PiEnOvrd_OFF                          ( 8)
  #define DDRCMD1_CR_PIDFTDLY_Ch1PiEnOvrd_WID                          ( 1)
  #define DDRCMD1_CR_PIDFTDLY_Ch1PiEnOvrd_MSK                          (0x00000100)
  #define DDRCMD1_CR_PIDFTDLY_Ch1PiEnOvrd_MIN                          (0)
  #define DDRCMD1_CR_PIDFTDLY_Ch1PiEnOvrd_MAX                          (1) // 0x00000001
  #define DDRCMD1_CR_PIDFTDLY_Ch1PiEnOvrd_DEF                          (0x00000000)
  #define DDRCMD1_CR_PIDFTDLY_Ch1PiEnOvrd_HSH                          (0x01082598)

  #define DDRCMD1_CR_PIDFTDLY_Ch0PiDFTEn_OFF                           ( 9)
  #define DDRCMD1_CR_PIDFTDLY_Ch0PiDFTEn_WID                           ( 1)
  #define DDRCMD1_CR_PIDFTDLY_Ch0PiDFTEn_MSK                           (0x00000200)
  #define DDRCMD1_CR_PIDFTDLY_Ch0PiDFTEn_MIN                           (0)
  #define DDRCMD1_CR_PIDFTDLY_Ch0PiDFTEn_MAX                           (1) // 0x00000001
  #define DDRCMD1_CR_PIDFTDLY_Ch0PiDFTEn_DEF                           (0x00000000)
  #define DDRCMD1_CR_PIDFTDLY_Ch0PiDFTEn_HSH                           (0x01092598)

  #define DDRCMD1_CR_PIDFTDLY_Ch1PiDFTEn_OFF                           (10)
  #define DDRCMD1_CR_PIDFTDLY_Ch1PiDFTEn_WID                           ( 1)
  #define DDRCMD1_CR_PIDFTDLY_Ch1PiDFTEn_MSK                           (0x00000400)
  #define DDRCMD1_CR_PIDFTDLY_Ch1PiDFTEn_MIN                           (0)
  #define DDRCMD1_CR_PIDFTDLY_Ch1PiDFTEn_MAX                           (1) // 0x00000001
  #define DDRCMD1_CR_PIDFTDLY_Ch1PiDFTEn_DEF                           (0x00000000)
  #define DDRCMD1_CR_PIDFTDLY_Ch1PiDFTEn_HSH                           (0x010A2598)

  #define DDRCMD1_CR_PIDFTDLY_Spare_OFF                                (11)
  #define DDRCMD1_CR_PIDFTDLY_Spare_WID                                ( 4)
  #define DDRCMD1_CR_PIDFTDLY_Spare_MSK                                (0x00007800)
  #define DDRCMD1_CR_PIDFTDLY_Spare_MIN                                (0)
  #define DDRCMD1_CR_PIDFTDLY_Spare_MAX                                (15) // 0x0000000F
  #define DDRCMD1_CR_PIDFTDLY_Spare_DEF                                (0x00000000)
  #define DDRCMD1_CR_PIDFTDLY_Spare_HSH                                (0x040B2598)

  #define DDRCMD1_CR_PIDFTDLY_RefPiOvrd_OFF                            (15)
  #define DDRCMD1_CR_PIDFTDLY_RefPiOvrd_WID                            ( 1)
  #define DDRCMD1_CR_PIDFTDLY_RefPiOvrd_MSK                            (0x00008000)
  #define DDRCMD1_CR_PIDFTDLY_RefPiOvrd_MIN                            (0)
  #define DDRCMD1_CR_PIDFTDLY_RefPiOvrd_MAX                            (1) // 0x00000001
  #define DDRCMD1_CR_PIDFTDLY_RefPiOvrd_DEF                            (0x00000000)
  #define DDRCMD1_CR_PIDFTDLY_RefPiOvrd_HSH                            (0x010F2598)

  #define DDRCMD1_CR_PIDFTDLY_Rsvd_OFF                                 (16)
  #define DDRCMD1_CR_PIDFTDLY_Rsvd_WID                                 (16)
  #define DDRCMD1_CR_PIDFTDLY_Rsvd_MSK                                 (0xFFFF0000)
  #define DDRCMD1_CR_PIDFTDLY_Rsvd_MIN                                 (0)
  #define DDRCMD1_CR_PIDFTDLY_Rsvd_MAX                                 (65535) // 0x0000FFFF
  #define DDRCMD1_CR_PIDFTDLY_Rsvd_DEF                                 (0x00000000)
  #define DDRCMD1_CR_PIDFTDLY_Rsvd_HSH                                 (0x10102598)

#define DDRCMD1_CR_DLLPITESTANDADC_REG                                 (0x0000259C)

  #define DDRCMD1_CR_DLLPITESTANDADC_RunTest_OFF                       ( 0)
  #define DDRCMD1_CR_DLLPITESTANDADC_RunTest_WID                       ( 1)
  #define DDRCMD1_CR_DLLPITESTANDADC_RunTest_MSK                       (0x00000001)
  #define DDRCMD1_CR_DLLPITESTANDADC_RunTest_MIN                       (0)
  #define DDRCMD1_CR_DLLPITESTANDADC_RunTest_MAX                       (1) // 0x00000001
  #define DDRCMD1_CR_DLLPITESTANDADC_RunTest_DEF                       (0x00000000)
  #define DDRCMD1_CR_DLLPITESTANDADC_RunTest_HSH                       (0x0100259C)

  #define DDRCMD1_CR_DLLPITESTANDADC_Load_OFF                          ( 1)
  #define DDRCMD1_CR_DLLPITESTANDADC_Load_WID                          ( 1)
  #define DDRCMD1_CR_DLLPITESTANDADC_Load_MSK                          (0x00000002)
  #define DDRCMD1_CR_DLLPITESTANDADC_Load_MIN                          (0)
  #define DDRCMD1_CR_DLLPITESTANDADC_Load_MAX                          (1) // 0x00000001
  #define DDRCMD1_CR_DLLPITESTANDADC_Load_DEF                          (0x00000000)
  #define DDRCMD1_CR_DLLPITESTANDADC_Load_HSH                          (0x0101259C)

  #define DDRCMD1_CR_DLLPITESTANDADC_ModeHVM_OFF                       ( 2)
  #define DDRCMD1_CR_DLLPITESTANDADC_ModeHVM_WID                       ( 1)
  #define DDRCMD1_CR_DLLPITESTANDADC_ModeHVM_MSK                       (0x00000004)
  #define DDRCMD1_CR_DLLPITESTANDADC_ModeHVM_MIN                       (0)
  #define DDRCMD1_CR_DLLPITESTANDADC_ModeHVM_MAX                       (1) // 0x00000001
  #define DDRCMD1_CR_DLLPITESTANDADC_ModeHVM_DEF                       (0x00000000)
  #define DDRCMD1_CR_DLLPITESTANDADC_ModeHVM_HSH                       (0x0102259C)

  #define DDRCMD1_CR_DLLPITESTANDADC_ModeDV_OFF                        ( 3)
  #define DDRCMD1_CR_DLLPITESTANDADC_ModeDV_WID                        ( 1)
  #define DDRCMD1_CR_DLLPITESTANDADC_ModeDV_MSK                        (0x00000008)
  #define DDRCMD1_CR_DLLPITESTANDADC_ModeDV_MIN                        (0)
  #define DDRCMD1_CR_DLLPITESTANDADC_ModeDV_MAX                        (1) // 0x00000001
  #define DDRCMD1_CR_DLLPITESTANDADC_ModeDV_DEF                        (0x00000000)
  #define DDRCMD1_CR_DLLPITESTANDADC_ModeDV_HSH                        (0x0103259C)

  #define DDRCMD1_CR_DLLPITESTANDADC_CalCfdl_OFF                       ( 4)
  #define DDRCMD1_CR_DLLPITESTANDADC_CalCfdl_WID                       ( 1)
  #define DDRCMD1_CR_DLLPITESTANDADC_CalCfdl_MSK                       (0x00000010)
  #define DDRCMD1_CR_DLLPITESTANDADC_CalCfdl_MIN                       (0)
  #define DDRCMD1_CR_DLLPITESTANDADC_CalCfdl_MAX                       (1) // 0x00000001
  #define DDRCMD1_CR_DLLPITESTANDADC_CalCfdl_DEF                       (0x00000000)
  #define DDRCMD1_CR_DLLPITESTANDADC_CalCfdl_HSH                       (0x0104259C)

  #define DDRCMD1_CR_DLLPITESTANDADC_LoadCount_OFF                     ( 5)
  #define DDRCMD1_CR_DLLPITESTANDADC_LoadCount_WID                     (10)
  #define DDRCMD1_CR_DLLPITESTANDADC_LoadCount_MSK                     (0x00007FE0)
  #define DDRCMD1_CR_DLLPITESTANDADC_LoadCount_MIN                     (0)
  #define DDRCMD1_CR_DLLPITESTANDADC_LoadCount_MAX                     (1023) // 0x000003FF
  #define DDRCMD1_CR_DLLPITESTANDADC_LoadCount_DEF                     (0x00000000)
  #define DDRCMD1_CR_DLLPITESTANDADC_LoadCount_HSH                     (0x0A05259C)

  #define DDRCMD1_CR_DLLPITESTANDADC_CountStatus_OFF                   (15)
  #define DDRCMD1_CR_DLLPITESTANDADC_CountStatus_WID                   (10)
  #define DDRCMD1_CR_DLLPITESTANDADC_CountStatus_MSK                   (0x01FF8000)
  #define DDRCMD1_CR_DLLPITESTANDADC_CountStatus_MIN                   (0)
  #define DDRCMD1_CR_DLLPITESTANDADC_CountStatus_MAX                   (1023) // 0x000003FF
  #define DDRCMD1_CR_DLLPITESTANDADC_CountStatus_DEF                   (0x00000000)
  #define DDRCMD1_CR_DLLPITESTANDADC_CountStatus_HSH                   (0x0A0F259C)

  #define DDRCMD1_CR_DLLPITESTANDADC_ModeADC_OFF                       (25)
  #define DDRCMD1_CR_DLLPITESTANDADC_ModeADC_WID                       ( 1)
  #define DDRCMD1_CR_DLLPITESTANDADC_ModeADC_MSK                       (0x02000000)
  #define DDRCMD1_CR_DLLPITESTANDADC_ModeADC_MIN                       (0)
  #define DDRCMD1_CR_DLLPITESTANDADC_ModeADC_MAX                       (1) // 0x00000001
  #define DDRCMD1_CR_DLLPITESTANDADC_ModeADC_DEF                       (0x00000000)
  #define DDRCMD1_CR_DLLPITESTANDADC_ModeADC_HSH                       (0x0119259C)

  #define DDRCMD1_CR_DLLPITESTANDADC_ADCClkDiv_OFF                     (26)
  #define DDRCMD1_CR_DLLPITESTANDADC_ADCClkDiv_WID                     ( 2)
  #define DDRCMD1_CR_DLLPITESTANDADC_ADCClkDiv_MSK                     (0x0C000000)
  #define DDRCMD1_CR_DLLPITESTANDADC_ADCClkDiv_MIN                     (0)
  #define DDRCMD1_CR_DLLPITESTANDADC_ADCClkDiv_MAX                     (3) // 0x00000003
  #define DDRCMD1_CR_DLLPITESTANDADC_ADCClkDiv_DEF                     (0x00000000)
  #define DDRCMD1_CR_DLLPITESTANDADC_ADCClkDiv_HSH                     (0x021A259C)

  #define DDRCMD1_CR_DLLPITESTANDADC_ADCDdrChanSel_OFF                 (28)
  #define DDRCMD1_CR_DLLPITESTANDADC_ADCDdrChanSel_WID                 ( 1)
  #define DDRCMD1_CR_DLLPITESTANDADC_ADCDdrChanSel_MSK                 (0x10000000)
  #define DDRCMD1_CR_DLLPITESTANDADC_ADCDdrChanSel_MIN                 (0)
  #define DDRCMD1_CR_DLLPITESTANDADC_ADCDdrChanSel_MAX                 (1) // 0x00000001
  #define DDRCMD1_CR_DLLPITESTANDADC_ADCDdrChanSel_DEF                 (0x00000000)
  #define DDRCMD1_CR_DLLPITESTANDADC_ADCDdrChanSel_HSH                 (0x011C259C)

  #define DDRCMD1_CR_DLLPITESTANDADC_ADCChopEn_OFF                     (29)
  #define DDRCMD1_CR_DLLPITESTANDADC_ADCChopEn_WID                     ( 1)
  #define DDRCMD1_CR_DLLPITESTANDADC_ADCChopEn_MSK                     (0x20000000)
  #define DDRCMD1_CR_DLLPITESTANDADC_ADCChopEn_MIN                     (0)
  #define DDRCMD1_CR_DLLPITESTANDADC_ADCChopEn_MAX                     (1) // 0x00000001
  #define DDRCMD1_CR_DLLPITESTANDADC_ADCChopEn_DEF                     (0x00000000)
  #define DDRCMD1_CR_DLLPITESTANDADC_ADCChopEn_HSH                     (0x011D259C)

  #define DDRCMD1_CR_DLLPITESTANDADC_ADCDone_OFF                       (30)
  #define DDRCMD1_CR_DLLPITESTANDADC_ADCDone_WID                       ( 1)
  #define DDRCMD1_CR_DLLPITESTANDADC_ADCDone_MSK                       (0x40000000)
  #define DDRCMD1_CR_DLLPITESTANDADC_ADCDone_MIN                       (0)
  #define DDRCMD1_CR_DLLPITESTANDADC_ADCDone_MAX                       (1) // 0x00000001
  #define DDRCMD1_CR_DLLPITESTANDADC_ADCDone_DEF                       (0x00000000)
  #define DDRCMD1_CR_DLLPITESTANDADC_ADCDone_HSH                       (0x011E259C)

  #define DDRCMD1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF              (31)
  #define DDRCMD1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID              ( 1)
  #define DDRCMD1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK              (0x80000000)
  #define DDRCMD1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN              (0)
  #define DDRCMD1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX              (1) // 0x00000001
  #define DDRCMD1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF              (0x00000000)
  #define DDRCMD1_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH              (0x011F259C)

#define DDRCMD1_CR_DLLSTATUS_REG                                       (0x000025A0)

  #define DDRCMD1_CR_DLLSTATUS_DetrmLockStat_OFF                       ( 0)
  #define DDRCMD1_CR_DLLSTATUS_DetrmLockStat_WID                       ( 1)
  #define DDRCMD1_CR_DLLSTATUS_DetrmLockStat_MSK                       (0x00000001)
  #define DDRCMD1_CR_DLLSTATUS_DetrmLockStat_MIN                       (0)
  #define DDRCMD1_CR_DLLSTATUS_DetrmLockStat_MAX                       (1) // 0x00000001
  #define DDRCMD1_CR_DLLSTATUS_DetrmLockStat_DEF                       (0x00000000)
  #define DDRCMD1_CR_DLLSTATUS_DetrmLockStat_HSH                       (0x010025A0)

  #define DDRCMD1_CR_DLLSTATUS_FuncLockStat_OFF                        ( 1)
  #define DDRCMD1_CR_DLLSTATUS_FuncLockStat_WID                        ( 1)
  #define DDRCMD1_CR_DLLSTATUS_FuncLockStat_MSK                        (0x00000002)
  #define DDRCMD1_CR_DLLSTATUS_FuncLockStat_MIN                        (0)
  #define DDRCMD1_CR_DLLSTATUS_FuncLockStat_MAX                        (1) // 0x00000001
  #define DDRCMD1_CR_DLLSTATUS_FuncLockStat_DEF                        (0x00000000)
  #define DDRCMD1_CR_DLLSTATUS_FuncLockStat_HSH                        (0x010125A0)

  #define DDRCMD1_CR_DLLSTATUS_Lock_OFF                                ( 2)
  #define DDRCMD1_CR_DLLSTATUS_Lock_WID                                ( 1)
  #define DDRCMD1_CR_DLLSTATUS_Lock_MSK                                (0x00000004)
  #define DDRCMD1_CR_DLLSTATUS_Lock_MIN                                (0)
  #define DDRCMD1_CR_DLLSTATUS_Lock_MAX                                (1) // 0x00000001
  #define DDRCMD1_CR_DLLSTATUS_Lock_DEF                                (0x00000000)
  #define DDRCMD1_CR_DLLSTATUS_Lock_HSH                                (0x010225A0)

  #define DDRCMD1_CR_DLLSTATUS_Timeout_OFF                             ( 3)
  #define DDRCMD1_CR_DLLSTATUS_Timeout_WID                             ( 1)
  #define DDRCMD1_CR_DLLSTATUS_Timeout_MSK                             (0x00000008)
  #define DDRCMD1_CR_DLLSTATUS_Timeout_MIN                             (0)
  #define DDRCMD1_CR_DLLSTATUS_Timeout_MAX                             (1) // 0x00000001
  #define DDRCMD1_CR_DLLSTATUS_Timeout_DEF                             (0x00000000)
  #define DDRCMD1_CR_DLLSTATUS_Timeout_HSH                             (0x010325A0)

  #define DDRCMD1_CR_DLLSTATUS_DllReset_OFF                            ( 4)
  #define DDRCMD1_CR_DLLSTATUS_DllReset_WID                            ( 1)
  #define DDRCMD1_CR_DLLSTATUS_DllReset_MSK                            (0x00000010)
  #define DDRCMD1_CR_DLLSTATUS_DllReset_MIN                            (0)
  #define DDRCMD1_CR_DLLSTATUS_DllReset_MAX                            (1) // 0x00000001
  #define DDRCMD1_CR_DLLSTATUS_DllReset_DEF                            (0x00000000)
  #define DDRCMD1_CR_DLLSTATUS_DllReset_HSH                            (0x010425A0)

  #define DDRCMD1_CR_DLLSTATUS_LongLockStat_OFF                        ( 5)
  #define DDRCMD1_CR_DLLSTATUS_LongLockStat_WID                        ( 1)
  #define DDRCMD1_CR_DLLSTATUS_LongLockStat_MSK                        (0x00000020)
  #define DDRCMD1_CR_DLLSTATUS_LongLockStat_MIN                        (0)
  #define DDRCMD1_CR_DLLSTATUS_LongLockStat_MAX                        (1) // 0x00000001
  #define DDRCMD1_CR_DLLSTATUS_LongLockStat_DEF                        (0x00000000)
  #define DDRCMD1_CR_DLLSTATUS_LongLockStat_HSH                        (0x010525A0)

  #define DDRCMD1_CR_DLLSTATUS_EarlyLockStat_OFF                       ( 6)
  #define DDRCMD1_CR_DLLSTATUS_EarlyLockStat_WID                       ( 1)
  #define DDRCMD1_CR_DLLSTATUS_EarlyLockStat_MSK                       (0x00000040)
  #define DDRCMD1_CR_DLLSTATUS_EarlyLockStat_MIN                       (0)
  #define DDRCMD1_CR_DLLSTATUS_EarlyLockStat_MAX                       (1) // 0x00000001
  #define DDRCMD1_CR_DLLSTATUS_EarlyLockStat_DEF                       (0x00000000)
  #define DDRCMD1_CR_DLLSTATUS_EarlyLockStat_HSH                       (0x010625A0)

  #define DDRCMD1_CR_DLLSTATUS_NormalMode_NotWkLock_OFF                ( 7)
  #define DDRCMD1_CR_DLLSTATUS_NormalMode_NotWkLock_WID                ( 1)
  #define DDRCMD1_CR_DLLSTATUS_NormalMode_NotWkLock_MSK                (0x00000080)
  #define DDRCMD1_CR_DLLSTATUS_NormalMode_NotWkLock_MIN                (0)
  #define DDRCMD1_CR_DLLSTATUS_NormalMode_NotWkLock_MAX                (1) // 0x00000001
  #define DDRCMD1_CR_DLLSTATUS_NormalMode_NotWkLock_DEF                (0x00000000)
  #define DDRCMD1_CR_DLLSTATUS_NormalMode_NotWkLock_HSH                (0x010725A0)

  #define DDRCMD1_CR_DLLSTATUS_ADCout_OFF                              ( 8)
  #define DDRCMD1_CR_DLLSTATUS_ADCout_WID                              (10)
  #define DDRCMD1_CR_DLLSTATUS_ADCout_MSK                              (0x0003FF00)
  #define DDRCMD1_CR_DLLSTATUS_ADCout_MIN                              (0)
  #define DDRCMD1_CR_DLLSTATUS_ADCout_MAX                              (1023) // 0x000003FF
  #define DDRCMD1_CR_DLLSTATUS_ADCout_DEF                              (0x00000000)
  #define DDRCMD1_CR_DLLSTATUS_ADCout_HSH                              (0x0A0825A0)

  #define DDRCMD1_CR_DLLSTATUS_ADCStatus_OFF                           (18)
  #define DDRCMD1_CR_DLLSTATUS_ADCStatus_WID                           ( 1)
  #define DDRCMD1_CR_DLLSTATUS_ADCStatus_MSK                           (0x00040000)
  #define DDRCMD1_CR_DLLSTATUS_ADCStatus_MIN                           (0)
  #define DDRCMD1_CR_DLLSTATUS_ADCStatus_MAX                           (1) // 0x00000001
  #define DDRCMD1_CR_DLLSTATUS_ADCStatus_DEF                           (0x00000000)
  #define DDRCMD1_CR_DLLSTATUS_ADCStatus_HSH                           (0x011225A0)

  #define DDRCMD1_CR_DLLSTATUS_pilags_OFF                              (19)
  #define DDRCMD1_CR_DLLSTATUS_pilags_WID                              ( 1)
  #define DDRCMD1_CR_DLLSTATUS_pilags_MSK                              (0x00080000)
  #define DDRCMD1_CR_DLLSTATUS_pilags_MIN                              (0)
  #define DDRCMD1_CR_DLLSTATUS_pilags_MAX                              (1) // 0x00000001
  #define DDRCMD1_CR_DLLSTATUS_pilags_DEF                              (0x00000000)
  #define DDRCMD1_CR_DLLSTATUS_pilags_HSH                              (0x011325A0)

  #define DDRCMD1_CR_DLLSTATUS_spare_OFF                               (20)
  #define DDRCMD1_CR_DLLSTATUS_spare_WID                               (12)
  #define DDRCMD1_CR_DLLSTATUS_spare_MSK                               (0xFFF00000)
  #define DDRCMD1_CR_DLLSTATUS_spare_MIN                               (0)
  #define DDRCMD1_CR_DLLSTATUS_spare_MAX                               (4095) // 0x00000FFF
  #define DDRCMD1_CR_DLLSTATUS_spare_DEF                               (0x00000000)
  #define DDRCMD1_CR_DLLSTATUS_spare_HSH                               (0x0C1425A0)

#define DDRCMD1_CR_DLLDCMCTL_REG                                       (0x000025A4)

  #define DDRCMD1_CR_DLLDCMCTL_start_OFF                               ( 0)
  #define DDRCMD1_CR_DLLDCMCTL_start_WID                               ( 1)
  #define DDRCMD1_CR_DLLDCMCTL_start_MSK                               (0x00000001)
  #define DDRCMD1_CR_DLLDCMCTL_start_MIN                               (0)
  #define DDRCMD1_CR_DLLDCMCTL_start_MAX                               (1) // 0x00000001
  #define DDRCMD1_CR_DLLDCMCTL_start_DEF                               (0x00000000)
  #define DDRCMD1_CR_DLLDCMCTL_start_HSH                               (0x010025A4)

  #define DDRCMD1_CR_DLLDCMCTL_clken_OFF                               ( 1)
  #define DDRCMD1_CR_DLLDCMCTL_clken_WID                               ( 1)
  #define DDRCMD1_CR_DLLDCMCTL_clken_MSK                               (0x00000002)
  #define DDRCMD1_CR_DLLDCMCTL_clken_MIN                               (0)
  #define DDRCMD1_CR_DLLDCMCTL_clken_MAX                               (1) // 0x00000001
  #define DDRCMD1_CR_DLLDCMCTL_clken_DEF                               (0x00000000)
  #define DDRCMD1_CR_DLLDCMCTL_clken_HSH                               (0x010125A4)

  #define DDRCMD1_CR_DLLDCMCTL_dcm_dccctl_en_OFF                       ( 2)
  #define DDRCMD1_CR_DLLDCMCTL_dcm_dccctl_en_WID                       ( 1)
  #define DDRCMD1_CR_DLLDCMCTL_dcm_dccctl_en_MSK                       (0x00000004)
  #define DDRCMD1_CR_DLLDCMCTL_dcm_dccctl_en_MIN                       (0)
  #define DDRCMD1_CR_DLLDCMCTL_dcm_dccctl_en_MAX                       (1) // 0x00000001
  #define DDRCMD1_CR_DLLDCMCTL_dcm_dccctl_en_DEF                       (0x00000000)
  #define DDRCMD1_CR_DLLDCMCTL_dcm_dccctl_en_HSH                       (0x010225A4)

  #define DDRCMD1_CR_DLLDCMCTL_dccctl_OFF                              ( 3)
  #define DDRCMD1_CR_DLLDCMCTL_dccctl_WID                              ( 4)
  #define DDRCMD1_CR_DLLDCMCTL_dccctl_MSK                              (0x00000078)
  #define DDRCMD1_CR_DLLDCMCTL_dccctl_MIN                              (0)
  #define DDRCMD1_CR_DLLDCMCTL_dccctl_MAX                              (15) // 0x0000000F
  #define DDRCMD1_CR_DLLDCMCTL_dccctl_DEF                              (0x00000000)
  #define DDRCMD1_CR_DLLDCMCTL_dccctl_HSH                              (0x040325A4)

  #define DDRCMD1_CR_DLLDCMCTL_duration_OFF                            ( 7)
  #define DDRCMD1_CR_DLLDCMCTL_duration_WID                            ( 3)
  #define DDRCMD1_CR_DLLDCMCTL_duration_MSK                            (0x00000380)
  #define DDRCMD1_CR_DLLDCMCTL_duration_MIN                            (0)
  #define DDRCMD1_CR_DLLDCMCTL_duration_MAX                            (7) // 0x00000007
  #define DDRCMD1_CR_DLLDCMCTL_duration_DEF                            (0x00000000)
  #define DDRCMD1_CR_DLLDCMCTL_duration_HSH                            (0x030725A4)

  #define DDRCMD1_CR_DLLDCMCTL_dcm_done_OFF                            (10)
  #define DDRCMD1_CR_DLLDCMCTL_dcm_done_WID                            ( 1)
  #define DDRCMD1_CR_DLLDCMCTL_dcm_done_MSK                            (0x00000400)
  #define DDRCMD1_CR_DLLDCMCTL_dcm_done_MIN                            (0)
  #define DDRCMD1_CR_DLLDCMCTL_dcm_done_MAX                            (1) // 0x00000001
  #define DDRCMD1_CR_DLLDCMCTL_dcm_done_DEF                            (0x00000000)
  #define DDRCMD1_CR_DLLDCMCTL_dcm_done_HSH                            (0x010A25A4)

  #define DDRCMD1_CR_DLLDCMCTL_dcm_results_OFF                         (11)
  #define DDRCMD1_CR_DLLDCMCTL_dcm_results_WID                         (15)
  #define DDRCMD1_CR_DLLDCMCTL_dcm_results_MSK                         (0x03FFF800)
  #define DDRCMD1_CR_DLLDCMCTL_dcm_results_MIN                         (0)
  #define DDRCMD1_CR_DLLDCMCTL_dcm_results_MAX                         (32767) // 0x00007FFF
  #define DDRCMD1_CR_DLLDCMCTL_dcm_results_DEF                         (0x00000000)
  #define DDRCMD1_CR_DLLDCMCTL_dcm_results_HSH                         (0x0F0B25A4)

  #define DDRCMD1_CR_DLLDCMCTL_spare0_OFF                              (26)
  #define DDRCMD1_CR_DLLDCMCTL_spare0_WID                              ( 6)
  #define DDRCMD1_CR_DLLDCMCTL_spare0_MSK                              (0xFC000000)
  #define DDRCMD1_CR_DLLDCMCTL_spare0_MIN                              (0)
  #define DDRCMD1_CR_DLLDCMCTL_spare0_MAX                              (63) // 0x0000003F
  #define DDRCMD1_CR_DLLDCMCTL_spare0_DEF                              (0x00000000)
  #define DDRCMD1_CR_DLLDCMCTL_spare0_HSH                              (0x061A25A4)

#define DDRCTL0_CR_MASTERDLLCFG_REG                                    (0x00002600)

  #define DDRCTL0_CR_MASTERDLLCFG_LockThresh_OFF                       ( 0)
  #define DDRCTL0_CR_MASTERDLLCFG_LockThresh_WID                       ( 3)
  #define DDRCTL0_CR_MASTERDLLCFG_LockThresh_MSK                       (0x00000007)
  #define DDRCTL0_CR_MASTERDLLCFG_LockThresh_MIN                       (0)
  #define DDRCTL0_CR_MASTERDLLCFG_LockThresh_MAX                       (7) // 0x00000007
  #define DDRCTL0_CR_MASTERDLLCFG_LockThresh_DEF                       (0x00000004)
  #define DDRCTL0_CR_MASTERDLLCFG_LockThresh_HSH                       (0x03002600)

  #define DDRCTL0_CR_MASTERDLLCFG_LockCtr_OFF                          ( 3)
  #define DDRCTL0_CR_MASTERDLLCFG_LockCtr_WID                          ( 2)
  #define DDRCTL0_CR_MASTERDLLCFG_LockCtr_MSK                          (0x00000018)
  #define DDRCTL0_CR_MASTERDLLCFG_LockCtr_MIN                          (0)
  #define DDRCTL0_CR_MASTERDLLCFG_LockCtr_MAX                          (3) // 0x00000003
  #define DDRCTL0_CR_MASTERDLLCFG_LockCtr_DEF                          (0x00000000)
  #define DDRCTL0_CR_MASTERDLLCFG_LockCtr_HSH                          (0x02032600)

  #define DDRCTL0_CR_MASTERDLLCFG_VctrlDischRate_OFF                   ( 5)
  #define DDRCTL0_CR_MASTERDLLCFG_VctrlDischRate_WID                   ( 2)
  #define DDRCTL0_CR_MASTERDLLCFG_VctrlDischRate_MSK                   (0x00000060)
  #define DDRCTL0_CR_MASTERDLLCFG_VctrlDischRate_MIN                   (0)
  #define DDRCTL0_CR_MASTERDLLCFG_VctrlDischRate_MAX                   (3) // 0x00000003
  #define DDRCTL0_CR_MASTERDLLCFG_VctrlDischRate_DEF                   (0x00000000)
  #define DDRCTL0_CR_MASTERDLLCFG_VctrlDischRate_HSH                   (0x02052600)

  #define DDRCTL0_CR_MASTERDLLCFG_SelVctrlHi_OFF                       ( 7)
  #define DDRCTL0_CR_MASTERDLLCFG_SelVctrlHi_WID                       ( 1)
  #define DDRCTL0_CR_MASTERDLLCFG_SelVctrlHi_MSK                       (0x00000080)
  #define DDRCTL0_CR_MASTERDLLCFG_SelVctrlHi_MIN                       (0)
  #define DDRCTL0_CR_MASTERDLLCFG_SelVctrlHi_MAX                       (1) // 0x00000001
  #define DDRCTL0_CR_MASTERDLLCFG_SelVctrlHi_DEF                       (0x00000000)
  #define DDRCTL0_CR_MASTERDLLCFG_SelVctrlHi_HSH                       (0x01072600)

  #define DDRCTL0_CR_MASTERDLLCFG_StartupCntSel_OFF                    ( 8)
  #define DDRCTL0_CR_MASTERDLLCFG_StartupCntSel_WID                    ( 1)
  #define DDRCTL0_CR_MASTERDLLCFG_StartupCntSel_MSK                    (0x00000100)
  #define DDRCTL0_CR_MASTERDLLCFG_StartupCntSel_MIN                    (0)
  #define DDRCTL0_CR_MASTERDLLCFG_StartupCntSel_MAX                    (1) // 0x00000001
  #define DDRCTL0_CR_MASTERDLLCFG_StartupCntSel_DEF                    (0x00000000)
  #define DDRCTL0_CR_MASTERDLLCFG_StartupCntSel_HSH                    (0x01082600)

  #define DDRCTL0_CR_MASTERDLLCFG_LockSel_OFF                          ( 9)
  #define DDRCTL0_CR_MASTERDLLCFG_LockSel_WID                          ( 2)
  #define DDRCTL0_CR_MASTERDLLCFG_LockSel_MSK                          (0x00000600)
  #define DDRCTL0_CR_MASTERDLLCFG_LockSel_MIN                          (0)
  #define DDRCTL0_CR_MASTERDLLCFG_LockSel_MAX                          (3) // 0x00000003
  #define DDRCTL0_CR_MASTERDLLCFG_LockSel_DEF                          (0x00000000)
  #define DDRCTL0_CR_MASTERDLLCFG_LockSel_HSH                          (0x02092600)

  #define DDRCTL0_CR_MASTERDLLCFG_RstOvrd_OFF                          (11)
  #define DDRCTL0_CR_MASTERDLLCFG_RstOvrd_WID                          ( 1)
  #define DDRCTL0_CR_MASTERDLLCFG_RstOvrd_MSK                          (0x00000800)
  #define DDRCTL0_CR_MASTERDLLCFG_RstOvrd_MIN                          (0)
  #define DDRCTL0_CR_MASTERDLLCFG_RstOvrd_MAX                          (1) // 0x00000001
  #define DDRCTL0_CR_MASTERDLLCFG_RstOvrd_DEF                          (0x00000000)
  #define DDRCTL0_CR_MASTERDLLCFG_RstOvrd_HSH                          (0x010B2600)

  #define DDRCTL0_CR_MASTERDLLCFG_SelRstOvrd_OFF                       (12)
  #define DDRCTL0_CR_MASTERDLLCFG_SelRstOvrd_WID                       ( 1)
  #define DDRCTL0_CR_MASTERDLLCFG_SelRstOvrd_MSK                       (0x00001000)
  #define DDRCTL0_CR_MASTERDLLCFG_SelRstOvrd_MIN                       (0)
  #define DDRCTL0_CR_MASTERDLLCFG_SelRstOvrd_MAX                       (1) // 0x00000001
  #define DDRCTL0_CR_MASTERDLLCFG_SelRstOvrd_DEF                       (0x00000000)
  #define DDRCTL0_CR_MASTERDLLCFG_SelRstOvrd_HSH                       (0x010C2600)

  #define DDRCTL0_CR_MASTERDLLCFG_TimeOutOvrd_OFF                      (13)
  #define DDRCTL0_CR_MASTERDLLCFG_TimeOutOvrd_WID                      ( 1)
  #define DDRCTL0_CR_MASTERDLLCFG_TimeOutOvrd_MSK                      (0x00002000)
  #define DDRCTL0_CR_MASTERDLLCFG_TimeOutOvrd_MIN                      (0)
  #define DDRCTL0_CR_MASTERDLLCFG_TimeOutOvrd_MAX                      (1) // 0x00000001
  #define DDRCTL0_CR_MASTERDLLCFG_TimeOutOvrd_DEF                      (0x00000000)
  #define DDRCTL0_CR_MASTERDLLCFG_TimeOutOvrd_HSH                      (0x010D2600)

  #define DDRCTL0_CR_MASTERDLLCFG_SelTimeOutOvrd_OFF                   (14)
  #define DDRCTL0_CR_MASTERDLLCFG_SelTimeOutOvrd_WID                   ( 1)
  #define DDRCTL0_CR_MASTERDLLCFG_SelTimeOutOvrd_MSK                   (0x00004000)
  #define DDRCTL0_CR_MASTERDLLCFG_SelTimeOutOvrd_MIN                   (0)
  #define DDRCTL0_CR_MASTERDLLCFG_SelTimeOutOvrd_MAX                   (1) // 0x00000001
  #define DDRCTL0_CR_MASTERDLLCFG_SelTimeOutOvrd_DEF                   (0x00000000)
  #define DDRCTL0_CR_MASTERDLLCFG_SelTimeOutOvrd_HSH                   (0x010E2600)

  #define DDRCTL0_CR_MASTERDLLCFG_ClkGateOvrd_OFF                      (15)
  #define DDRCTL0_CR_MASTERDLLCFG_ClkGateOvrd_WID                      ( 1)
  #define DDRCTL0_CR_MASTERDLLCFG_ClkGateOvrd_MSK                      (0x00008000)
  #define DDRCTL0_CR_MASTERDLLCFG_ClkGateOvrd_MIN                      (0)
  #define DDRCTL0_CR_MASTERDLLCFG_ClkGateOvrd_MAX                      (1) // 0x00000001
  #define DDRCTL0_CR_MASTERDLLCFG_ClkGateOvrd_DEF                      (0x00000000)
  #define DDRCTL0_CR_MASTERDLLCFG_ClkGateOvrd_HSH                      (0x010F2600)

  #define DDRCTL0_CR_MASTERDLLCFG_LockOvrd_OFF                         (16)
  #define DDRCTL0_CR_MASTERDLLCFG_LockOvrd_WID                         ( 1)
  #define DDRCTL0_CR_MASTERDLLCFG_LockOvrd_MSK                         (0x00010000)
  #define DDRCTL0_CR_MASTERDLLCFG_LockOvrd_MIN                         (0)
  #define DDRCTL0_CR_MASTERDLLCFG_LockOvrd_MAX                         (1) // 0x00000001
  #define DDRCTL0_CR_MASTERDLLCFG_LockOvrd_DEF                         (0x00000000)
  #define DDRCTL0_CR_MASTERDLLCFG_LockOvrd_HSH                         (0x01102600)

  #define DDRCTL0_CR_MASTERDLLCFG_SelLockOvrd_OFF                      (17)
  #define DDRCTL0_CR_MASTERDLLCFG_SelLockOvrd_WID                      ( 1)
  #define DDRCTL0_CR_MASTERDLLCFG_SelLockOvrd_MSK                      (0x00020000)
  #define DDRCTL0_CR_MASTERDLLCFG_SelLockOvrd_MIN                      (0)
  #define DDRCTL0_CR_MASTERDLLCFG_SelLockOvrd_MAX                      (1) // 0x00000001
  #define DDRCTL0_CR_MASTERDLLCFG_SelLockOvrd_DEF                      (0x00000000)
  #define DDRCTL0_CR_MASTERDLLCFG_SelLockOvrd_HSH                      (0x01112600)

  #define DDRCTL0_CR_MASTERDLLCFG_OpenLoopOvrd_OFF                     (18)
  #define DDRCTL0_CR_MASTERDLLCFG_OpenLoopOvrd_WID                     ( 1)
  #define DDRCTL0_CR_MASTERDLLCFG_OpenLoopOvrd_MSK                     (0x00040000)
  #define DDRCTL0_CR_MASTERDLLCFG_OpenLoopOvrd_MIN                     (0)
  #define DDRCTL0_CR_MASTERDLLCFG_OpenLoopOvrd_MAX                     (1) // 0x00000001
  #define DDRCTL0_CR_MASTERDLLCFG_OpenLoopOvrd_DEF                     (0x00000000)
  #define DDRCTL0_CR_MASTERDLLCFG_OpenLoopOvrd_HSH                     (0x01122600)

  #define DDRCTL0_CR_MASTERDLLCFG_SelOpenLoopOvrd_OFF                  (19)
  #define DDRCTL0_CR_MASTERDLLCFG_SelOpenLoopOvrd_WID                  ( 1)
  #define DDRCTL0_CR_MASTERDLLCFG_SelOpenLoopOvrd_MSK                  (0x00080000)
  #define DDRCTL0_CR_MASTERDLLCFG_SelOpenLoopOvrd_MIN                  (0)
  #define DDRCTL0_CR_MASTERDLLCFG_SelOpenLoopOvrd_MAX                  (1) // 0x00000001
  #define DDRCTL0_CR_MASTERDLLCFG_SelOpenLoopOvrd_DEF                  (0x00000000)
  #define DDRCTL0_CR_MASTERDLLCFG_SelOpenLoopOvrd_HSH                  (0x01132600)

  #define DDRCTL0_CR_MASTERDLLCFG_WkLockEnOvrd_OFF                     (20)
  #define DDRCTL0_CR_MASTERDLLCFG_WkLockEnOvrd_WID                     ( 1)
  #define DDRCTL0_CR_MASTERDLLCFG_WkLockEnOvrd_MSK                     (0x00100000)
  #define DDRCTL0_CR_MASTERDLLCFG_WkLockEnOvrd_MIN                     (0)
  #define DDRCTL0_CR_MASTERDLLCFG_WkLockEnOvrd_MAX                     (1) // 0x00000001
  #define DDRCTL0_CR_MASTERDLLCFG_WkLockEnOvrd_DEF                     (0x00000000)
  #define DDRCTL0_CR_MASTERDLLCFG_WkLockEnOvrd_HSH                     (0x01142600)

  #define DDRCTL0_CR_MASTERDLLCFG_SelWkLockEnOvrd_OFF                  (21)
  #define DDRCTL0_CR_MASTERDLLCFG_SelWkLockEnOvrd_WID                  ( 1)
  #define DDRCTL0_CR_MASTERDLLCFG_SelWkLockEnOvrd_MSK                  (0x00200000)
  #define DDRCTL0_CR_MASTERDLLCFG_SelWkLockEnOvrd_MIN                  (0)
  #define DDRCTL0_CR_MASTERDLLCFG_SelWkLockEnOvrd_MAX                  (1) // 0x00000001
  #define DDRCTL0_CR_MASTERDLLCFG_SelWkLockEnOvrd_DEF                  (0x00000000)
  #define DDRCTL0_CR_MASTERDLLCFG_SelWkLockEnOvrd_HSH                  (0x01152600)

  #define DDRCTL0_CR_MASTERDLLCFG_CfdlDis_OFF                          (22)
  #define DDRCTL0_CR_MASTERDLLCFG_CfdlDis_WID                          ( 1)
  #define DDRCTL0_CR_MASTERDLLCFG_CfdlDis_MSK                          (0x00400000)
  #define DDRCTL0_CR_MASTERDLLCFG_CfdlDis_MIN                          (0)
  #define DDRCTL0_CR_MASTERDLLCFG_CfdlDis_MAX                          (1) // 0x00000001
  #define DDRCTL0_CR_MASTERDLLCFG_CfdlDis_DEF                          (0x00000000)
  #define DDRCTL0_CR_MASTERDLLCFG_CfdlDis_HSH                          (0x01162600)

  #define DDRCTL0_CR_MASTERDLLCFG_DftEn_OFF                            (23)
  #define DDRCTL0_CR_MASTERDLLCFG_DftEn_WID                            ( 1)
  #define DDRCTL0_CR_MASTERDLLCFG_DftEn_MSK                            (0x00800000)
  #define DDRCTL0_CR_MASTERDLLCFG_DftEn_MIN                            (0)
  #define DDRCTL0_CR_MASTERDLLCFG_DftEn_MAX                            (1) // 0x00000001
  #define DDRCTL0_CR_MASTERDLLCFG_DftEn_DEF                            (0x00000000)
  #define DDRCTL0_CR_MASTERDLLCFG_DftEn_HSH                            (0x01172600)

  #define DDRCTL0_CR_MASTERDLLCFG_spare0_OFF                           (24)
  #define DDRCTL0_CR_MASTERDLLCFG_spare0_WID                           ( 8)
  #define DDRCTL0_CR_MASTERDLLCFG_spare0_MSK                           (0xFF000000)
  #define DDRCTL0_CR_MASTERDLLCFG_spare0_MIN                           (0)
  #define DDRCTL0_CR_MASTERDLLCFG_spare0_MAX                           (255) // 0x000000FF
  #define DDRCTL0_CR_MASTERDLLCFG_spare0_DEF                           (0x00000000)
  #define DDRCTL0_CR_MASTERDLLCFG_spare0_HSH                           (0x08182600)

#define DDRCTL0_CR_CBTUNE0_REG                                         (0x00002604)

  #define DDRCTL0_CR_CBTUNE0_DllBWEn_OFF                               ( 0)
  #define DDRCTL0_CR_CBTUNE0_DllBWEn_WID                               (32)
  #define DDRCTL0_CR_CBTUNE0_DllBWEn_MSK                               (0xFFFFFFFF)
  #define DDRCTL0_CR_CBTUNE0_DllBWEn_MIN                               (0)
  #define DDRCTL0_CR_CBTUNE0_DllBWEn_MAX                               (4294967295) // 0xFFFFFFFF
  #define DDRCTL0_CR_CBTUNE0_DllBWEn_DEF                               (0xFDB86521)
  #define DDRCTL0_CR_CBTUNE0_DllBWEn_HSH                               (0x20002604)

#define DDRCTL0_CR_CBTUNE1_REG                                         (0x00002608)

  #define DDRCTL0_CR_CBTUNE1_PiCbEn_OFF                                ( 0)
  #define DDRCTL0_CR_CBTUNE1_PiCbEn_WID                                (24)
  #define DDRCTL0_CR_CBTUNE1_PiCbEn_MSK                                (0x00FFFFFF)
  #define DDRCTL0_CR_CBTUNE1_PiCbEn_MIN                                (0)
  #define DDRCTL0_CR_CBTUNE1_PiCbEn_MAX                                (16777215) // 0x00FFFFFF
  #define DDRCTL0_CR_CBTUNE1_PiCbEn_DEF                                (0x00249492)
  #define DDRCTL0_CR_CBTUNE1_PiCbEn_HSH                                (0x18002608)

  #define DDRCTL0_CR_CBTUNE1_CbEnRsvd_OFF                              (24)
  #define DDRCTL0_CR_CBTUNE1_CbEnRsvd_WID                              ( 3)
  #define DDRCTL0_CR_CBTUNE1_CbEnRsvd_MSK                              (0x07000000)
  #define DDRCTL0_CR_CBTUNE1_CbEnRsvd_MIN                              (0)
  #define DDRCTL0_CR_CBTUNE1_CbEnRsvd_MAX                              (7) // 0x00000007
  #define DDRCTL0_CR_CBTUNE1_CbEnRsvd_DEF                              (0x00000000)
  #define DDRCTL0_CR_CBTUNE1_CbEnRsvd_HSH                              (0x03182608)

  #define DDRCTL0_CR_CBTUNE1_CbEnDllFuse_OFF                           (27)
  #define DDRCTL0_CR_CBTUNE1_CbEnDllFuse_WID                           ( 3)
  #define DDRCTL0_CR_CBTUNE1_CbEnDllFuse_MSK                           (0x38000000)
  #define DDRCTL0_CR_CBTUNE1_CbEnDllFuse_MIN                           (0)
  #define DDRCTL0_CR_CBTUNE1_CbEnDllFuse_MAX                           (7) // 0x00000007
  #define DDRCTL0_CR_CBTUNE1_CbEnDllFuse_DEF                           (0x00000002)
  #define DDRCTL0_CR_CBTUNE1_CbEnDllFuse_HSH                           (0x031B2608)

  #define DDRCTL0_CR_CBTUNE1_Spare_OFF                                 (30)
  #define DDRCTL0_CR_CBTUNE1_Spare_WID                                 ( 2)
  #define DDRCTL0_CR_CBTUNE1_Spare_MSK                                 (0xC0000000)
  #define DDRCTL0_CR_CBTUNE1_Spare_MIN                                 (0)
  #define DDRCTL0_CR_CBTUNE1_Spare_MAX                                 (3) // 0x00000003
  #define DDRCTL0_CR_CBTUNE1_Spare_DEF                                 (0x00000000)
  #define DDRCTL0_CR_CBTUNE1_Spare_HSH                                 (0x021E2608)

#define DDRCTL0_CR_ADCCFG_REG                                          (0x0000260C)

  #define DDRCTL0_CR_ADCCFG_ADC_frz_OFF                                ( 0)
  #define DDRCTL0_CR_ADCCFG_ADC_frz_WID                                ( 1)
  #define DDRCTL0_CR_ADCCFG_ADC_frz_MSK                                (0x00000001)
  #define DDRCTL0_CR_ADCCFG_ADC_frz_MIN                                (0)
  #define DDRCTL0_CR_ADCCFG_ADC_frz_MAX                                (1) // 0x00000001
  #define DDRCTL0_CR_ADCCFG_ADC_frz_DEF                                (0x00000000)
  #define DDRCTL0_CR_ADCCFG_ADC_frz_HSH                                (0x0100260C)

  #define DDRCTL0_CR_ADCCFG_ADC_en_OFF                                 ( 1)
  #define DDRCTL0_CR_ADCCFG_ADC_en_WID                                 ( 1)
  #define DDRCTL0_CR_ADCCFG_ADC_en_MSK                                 (0x00000002)
  #define DDRCTL0_CR_ADCCFG_ADC_en_MIN                                 (0)
  #define DDRCTL0_CR_ADCCFG_ADC_en_MAX                                 (1) // 0x00000001
  #define DDRCTL0_CR_ADCCFG_ADC_en_DEF                                 (0x00000000)
  #define DDRCTL0_CR_ADCCFG_ADC_en_HSH                                 (0x0101260C)

  #define DDRCTL0_CR_ADCCFG_ADCclkdiv_OFF                              ( 2)
  #define DDRCTL0_CR_ADCCFG_ADCclkdiv_WID                              ( 2)
  #define DDRCTL0_CR_ADCCFG_ADCclkdiv_MSK                              (0x0000000C)
  #define DDRCTL0_CR_ADCCFG_ADCclkdiv_MIN                              (0)
  #define DDRCTL0_CR_ADCCFG_ADCclkdiv_MAX                              (3) // 0x00000003
  #define DDRCTL0_CR_ADCCFG_ADCclkdiv_DEF                              (0x00000000)
  #define DDRCTL0_CR_ADCCFG_ADCclkdiv_HSH                              (0x0202260C)

  #define DDRCTL0_CR_ADCCFG_ADCstartcount_OFF                          ( 4)
  #define DDRCTL0_CR_ADCCFG_ADCstartcount_WID                          ( 2)
  #define DDRCTL0_CR_ADCCFG_ADCstartcount_MSK                          (0x00000030)
  #define DDRCTL0_CR_ADCCFG_ADCstartcount_MIN                          (0)
  #define DDRCTL0_CR_ADCCFG_ADCstartcount_MAX                          (3) // 0x00000003
  #define DDRCTL0_CR_ADCCFG_ADCstartcount_DEF                          (0x00000000)
  #define DDRCTL0_CR_ADCCFG_ADCstartcount_HSH                          (0x0204260C)

  #define DDRCTL0_CR_ADCCFG_ADCChopEn_OFF                              ( 6)
  #define DDRCTL0_CR_ADCCFG_ADCChopEn_WID                              ( 1)
  #define DDRCTL0_CR_ADCCFG_ADCChopEn_MSK                              (0x00000040)
  #define DDRCTL0_CR_ADCCFG_ADCChopEn_MIN                              (0)
  #define DDRCTL0_CR_ADCCFG_ADCChopEn_MAX                              (1) // 0x00000001
  #define DDRCTL0_CR_ADCCFG_ADCChopEn_DEF                              (0x00000000)
  #define DDRCTL0_CR_ADCCFG_ADCChopEn_HSH                              (0x0106260C)

  #define DDRCTL0_CR_ADCCFG_Spare_OFF                                  ( 7)
  #define DDRCTL0_CR_ADCCFG_Spare_WID                                  (25)
  #define DDRCTL0_CR_ADCCFG_Spare_MSK                                  (0xFFFFFF80)
  #define DDRCTL0_CR_ADCCFG_Spare_MIN                                  (0)
  #define DDRCTL0_CR_ADCCFG_Spare_MAX                                  (33554431) // 0x01FFFFFF
  #define DDRCTL0_CR_ADCCFG_Spare_DEF                                  (0x00000000)
  #define DDRCTL0_CR_ADCCFG_Spare_HSH                                  (0x1907260C)

#define DDRCTL0_CR_CBTUNE2_REG                                         (0x00002610)

  #define DDRCTL0_CR_CBTUNE2_DllCbEn_OFF                               ( 0)
  #define DDRCTL0_CR_CBTUNE2_DllCbEn_WID                               (16)
  #define DDRCTL0_CR_CBTUNE2_DllCbEn_MSK                               (0x0000FFFF)
  #define DDRCTL0_CR_CBTUNE2_DllCbEn_MIN                               (0)
  #define DDRCTL0_CR_CBTUNE2_DllCbEn_MAX                               (65535) // 0x0000FFFF
  #define DDRCTL0_CR_CBTUNE2_DllCbEn_DEF                               (0x00000000)
  #define DDRCTL0_CR_CBTUNE2_DllCbEn_HSH                               (0x10002610)

  #define DDRCTL0_CR_CBTUNE2_Spare_OFF                                 (16)
  #define DDRCTL0_CR_CBTUNE2_Spare_WID                                 (16)
  #define DDRCTL0_CR_CBTUNE2_Spare_MSK                                 (0xFFFF0000)
  #define DDRCTL0_CR_CBTUNE2_Spare_MIN                                 (0)
  #define DDRCTL0_CR_CBTUNE2_Spare_MAX                                 (65535) // 0x0000FFFF
  #define DDRCTL0_CR_CBTUNE2_Spare_DEF                                 (0x00000000)
  #define DDRCTL0_CR_CBTUNE2_Spare_HSH                                 (0x10102610)

#define DDRCTL0_CR_PIDFTDLY_REG                                        (0x00002618)

  #define DDRCTL0_CR_PIDFTDLY_PiDftDelay_OFF                           ( 0)
  #define DDRCTL0_CR_PIDFTDLY_PiDftDelay_WID                           ( 7)
  #define DDRCTL0_CR_PIDFTDLY_PiDftDelay_MSK                           (0x0000007F)
  #define DDRCTL0_CR_PIDFTDLY_PiDftDelay_MIN                           (0)
  #define DDRCTL0_CR_PIDFTDLY_PiDftDelay_MAX                           (127) // 0x0000007F
  #define DDRCTL0_CR_PIDFTDLY_PiDftDelay_DEF                           (0x00000000)
  #define DDRCTL0_CR_PIDFTDLY_PiDftDelay_HSH                           (0x07002618)

  #define DDRCTL0_CR_PIDFTDLY_Ch0PiEnOvrd_OFF                          ( 7)
  #define DDRCTL0_CR_PIDFTDLY_Ch0PiEnOvrd_WID                          ( 1)
  #define DDRCTL0_CR_PIDFTDLY_Ch0PiEnOvrd_MSK                          (0x00000080)
  #define DDRCTL0_CR_PIDFTDLY_Ch0PiEnOvrd_MIN                          (0)
  #define DDRCTL0_CR_PIDFTDLY_Ch0PiEnOvrd_MAX                          (1) // 0x00000001
  #define DDRCTL0_CR_PIDFTDLY_Ch0PiEnOvrd_DEF                          (0x00000000)
  #define DDRCTL0_CR_PIDFTDLY_Ch0PiEnOvrd_HSH                          (0x01072618)

  #define DDRCTL0_CR_PIDFTDLY_Ch1PiEnOvrd_OFF                          ( 8)
  #define DDRCTL0_CR_PIDFTDLY_Ch1PiEnOvrd_WID                          ( 1)
  #define DDRCTL0_CR_PIDFTDLY_Ch1PiEnOvrd_MSK                          (0x00000100)
  #define DDRCTL0_CR_PIDFTDLY_Ch1PiEnOvrd_MIN                          (0)
  #define DDRCTL0_CR_PIDFTDLY_Ch1PiEnOvrd_MAX                          (1) // 0x00000001
  #define DDRCTL0_CR_PIDFTDLY_Ch1PiEnOvrd_DEF                          (0x00000000)
  #define DDRCTL0_CR_PIDFTDLY_Ch1PiEnOvrd_HSH                          (0x01082618)

  #define DDRCTL0_CR_PIDFTDLY_Ch0PiDFTEn_OFF                           ( 9)
  #define DDRCTL0_CR_PIDFTDLY_Ch0PiDFTEn_WID                           ( 1)
  #define DDRCTL0_CR_PIDFTDLY_Ch0PiDFTEn_MSK                           (0x00000200)
  #define DDRCTL0_CR_PIDFTDLY_Ch0PiDFTEn_MIN                           (0)
  #define DDRCTL0_CR_PIDFTDLY_Ch0PiDFTEn_MAX                           (1) // 0x00000001
  #define DDRCTL0_CR_PIDFTDLY_Ch0PiDFTEn_DEF                           (0x00000000)
  #define DDRCTL0_CR_PIDFTDLY_Ch0PiDFTEn_HSH                           (0x01092618)

  #define DDRCTL0_CR_PIDFTDLY_Ch1PiDFTEn_OFF                           (10)
  #define DDRCTL0_CR_PIDFTDLY_Ch1PiDFTEn_WID                           ( 1)
  #define DDRCTL0_CR_PIDFTDLY_Ch1PiDFTEn_MSK                           (0x00000400)
  #define DDRCTL0_CR_PIDFTDLY_Ch1PiDFTEn_MIN                           (0)
  #define DDRCTL0_CR_PIDFTDLY_Ch1PiDFTEn_MAX                           (1) // 0x00000001
  #define DDRCTL0_CR_PIDFTDLY_Ch1PiDFTEn_DEF                           (0x00000000)
  #define DDRCTL0_CR_PIDFTDLY_Ch1PiDFTEn_HSH                           (0x010A2618)

  #define DDRCTL0_CR_PIDFTDLY_Spare_OFF                                (11)
  #define DDRCTL0_CR_PIDFTDLY_Spare_WID                                ( 4)
  #define DDRCTL0_CR_PIDFTDLY_Spare_MSK                                (0x00007800)
  #define DDRCTL0_CR_PIDFTDLY_Spare_MIN                                (0)
  #define DDRCTL0_CR_PIDFTDLY_Spare_MAX                                (15) // 0x0000000F
  #define DDRCTL0_CR_PIDFTDLY_Spare_DEF                                (0x00000000)
  #define DDRCTL0_CR_PIDFTDLY_Spare_HSH                                (0x040B2618)

  #define DDRCTL0_CR_PIDFTDLY_RefPiOvrd_OFF                            (15)
  #define DDRCTL0_CR_PIDFTDLY_RefPiOvrd_WID                            ( 1)
  #define DDRCTL0_CR_PIDFTDLY_RefPiOvrd_MSK                            (0x00008000)
  #define DDRCTL0_CR_PIDFTDLY_RefPiOvrd_MIN                            (0)
  #define DDRCTL0_CR_PIDFTDLY_RefPiOvrd_MAX                            (1) // 0x00000001
  #define DDRCTL0_CR_PIDFTDLY_RefPiOvrd_DEF                            (0x00000000)
  #define DDRCTL0_CR_PIDFTDLY_RefPiOvrd_HSH                            (0x010F2618)

  #define DDRCTL0_CR_PIDFTDLY_Rsvd_OFF                                 (16)
  #define DDRCTL0_CR_PIDFTDLY_Rsvd_WID                                 (16)
  #define DDRCTL0_CR_PIDFTDLY_Rsvd_MSK                                 (0xFFFF0000)
  #define DDRCTL0_CR_PIDFTDLY_Rsvd_MIN                                 (0)
  #define DDRCTL0_CR_PIDFTDLY_Rsvd_MAX                                 (65535) // 0x0000FFFF
  #define DDRCTL0_CR_PIDFTDLY_Rsvd_DEF                                 (0x00000000)
  #define DDRCTL0_CR_PIDFTDLY_Rsvd_HSH                                 (0x10102618)

#define DDRCTL0_CR_DLLPITESTANDADC_REG                                 (0x0000261C)

  #define DDRCTL0_CR_DLLPITESTANDADC_RunTest_OFF                       ( 0)
  #define DDRCTL0_CR_DLLPITESTANDADC_RunTest_WID                       ( 1)
  #define DDRCTL0_CR_DLLPITESTANDADC_RunTest_MSK                       (0x00000001)
  #define DDRCTL0_CR_DLLPITESTANDADC_RunTest_MIN                       (0)
  #define DDRCTL0_CR_DLLPITESTANDADC_RunTest_MAX                       (1) // 0x00000001
  #define DDRCTL0_CR_DLLPITESTANDADC_RunTest_DEF                       (0x00000000)
  #define DDRCTL0_CR_DLLPITESTANDADC_RunTest_HSH                       (0x0100261C)

  #define DDRCTL0_CR_DLLPITESTANDADC_Load_OFF                          ( 1)
  #define DDRCTL0_CR_DLLPITESTANDADC_Load_WID                          ( 1)
  #define DDRCTL0_CR_DLLPITESTANDADC_Load_MSK                          (0x00000002)
  #define DDRCTL0_CR_DLLPITESTANDADC_Load_MIN                          (0)
  #define DDRCTL0_CR_DLLPITESTANDADC_Load_MAX                          (1) // 0x00000001
  #define DDRCTL0_CR_DLLPITESTANDADC_Load_DEF                          (0x00000000)
  #define DDRCTL0_CR_DLLPITESTANDADC_Load_HSH                          (0x0101261C)

  #define DDRCTL0_CR_DLLPITESTANDADC_ModeHVM_OFF                       ( 2)
  #define DDRCTL0_CR_DLLPITESTANDADC_ModeHVM_WID                       ( 1)
  #define DDRCTL0_CR_DLLPITESTANDADC_ModeHVM_MSK                       (0x00000004)
  #define DDRCTL0_CR_DLLPITESTANDADC_ModeHVM_MIN                       (0)
  #define DDRCTL0_CR_DLLPITESTANDADC_ModeHVM_MAX                       (1) // 0x00000001
  #define DDRCTL0_CR_DLLPITESTANDADC_ModeHVM_DEF                       (0x00000000)
  #define DDRCTL0_CR_DLLPITESTANDADC_ModeHVM_HSH                       (0x0102261C)

  #define DDRCTL0_CR_DLLPITESTANDADC_ModeDV_OFF                        ( 3)
  #define DDRCTL0_CR_DLLPITESTANDADC_ModeDV_WID                        ( 1)
  #define DDRCTL0_CR_DLLPITESTANDADC_ModeDV_MSK                        (0x00000008)
  #define DDRCTL0_CR_DLLPITESTANDADC_ModeDV_MIN                        (0)
  #define DDRCTL0_CR_DLLPITESTANDADC_ModeDV_MAX                        (1) // 0x00000001
  #define DDRCTL0_CR_DLLPITESTANDADC_ModeDV_DEF                        (0x00000000)
  #define DDRCTL0_CR_DLLPITESTANDADC_ModeDV_HSH                        (0x0103261C)

  #define DDRCTL0_CR_DLLPITESTANDADC_CalCfdl_OFF                       ( 4)
  #define DDRCTL0_CR_DLLPITESTANDADC_CalCfdl_WID                       ( 1)
  #define DDRCTL0_CR_DLLPITESTANDADC_CalCfdl_MSK                       (0x00000010)
  #define DDRCTL0_CR_DLLPITESTANDADC_CalCfdl_MIN                       (0)
  #define DDRCTL0_CR_DLLPITESTANDADC_CalCfdl_MAX                       (1) // 0x00000001
  #define DDRCTL0_CR_DLLPITESTANDADC_CalCfdl_DEF                       (0x00000000)
  #define DDRCTL0_CR_DLLPITESTANDADC_CalCfdl_HSH                       (0x0104261C)

  #define DDRCTL0_CR_DLLPITESTANDADC_LoadCount_OFF                     ( 5)
  #define DDRCTL0_CR_DLLPITESTANDADC_LoadCount_WID                     (10)
  #define DDRCTL0_CR_DLLPITESTANDADC_LoadCount_MSK                     (0x00007FE0)
  #define DDRCTL0_CR_DLLPITESTANDADC_LoadCount_MIN                     (0)
  #define DDRCTL0_CR_DLLPITESTANDADC_LoadCount_MAX                     (1023) // 0x000003FF
  #define DDRCTL0_CR_DLLPITESTANDADC_LoadCount_DEF                     (0x00000000)
  #define DDRCTL0_CR_DLLPITESTANDADC_LoadCount_HSH                     (0x0A05261C)

  #define DDRCTL0_CR_DLLPITESTANDADC_CountStatus_OFF                   (15)
  #define DDRCTL0_CR_DLLPITESTANDADC_CountStatus_WID                   (10)
  #define DDRCTL0_CR_DLLPITESTANDADC_CountStatus_MSK                   (0x01FF8000)
  #define DDRCTL0_CR_DLLPITESTANDADC_CountStatus_MIN                   (0)
  #define DDRCTL0_CR_DLLPITESTANDADC_CountStatus_MAX                   (1023) // 0x000003FF
  #define DDRCTL0_CR_DLLPITESTANDADC_CountStatus_DEF                   (0x00000000)
  #define DDRCTL0_CR_DLLPITESTANDADC_CountStatus_HSH                   (0x0A0F261C)

  #define DDRCTL0_CR_DLLPITESTANDADC_ModeADC_OFF                       (25)
  #define DDRCTL0_CR_DLLPITESTANDADC_ModeADC_WID                       ( 1)
  #define DDRCTL0_CR_DLLPITESTANDADC_ModeADC_MSK                       (0x02000000)
  #define DDRCTL0_CR_DLLPITESTANDADC_ModeADC_MIN                       (0)
  #define DDRCTL0_CR_DLLPITESTANDADC_ModeADC_MAX                       (1) // 0x00000001
  #define DDRCTL0_CR_DLLPITESTANDADC_ModeADC_DEF                       (0x00000000)
  #define DDRCTL0_CR_DLLPITESTANDADC_ModeADC_HSH                       (0x0119261C)

  #define DDRCTL0_CR_DLLPITESTANDADC_ADCClkDiv_OFF                     (26)
  #define DDRCTL0_CR_DLLPITESTANDADC_ADCClkDiv_WID                     ( 2)
  #define DDRCTL0_CR_DLLPITESTANDADC_ADCClkDiv_MSK                     (0x0C000000)
  #define DDRCTL0_CR_DLLPITESTANDADC_ADCClkDiv_MIN                     (0)
  #define DDRCTL0_CR_DLLPITESTANDADC_ADCClkDiv_MAX                     (3) // 0x00000003
  #define DDRCTL0_CR_DLLPITESTANDADC_ADCClkDiv_DEF                     (0x00000000)
  #define DDRCTL0_CR_DLLPITESTANDADC_ADCClkDiv_HSH                     (0x021A261C)

  #define DDRCTL0_CR_DLLPITESTANDADC_ADCDdrChanSel_OFF                 (28)
  #define DDRCTL0_CR_DLLPITESTANDADC_ADCDdrChanSel_WID                 ( 1)
  #define DDRCTL0_CR_DLLPITESTANDADC_ADCDdrChanSel_MSK                 (0x10000000)
  #define DDRCTL0_CR_DLLPITESTANDADC_ADCDdrChanSel_MIN                 (0)
  #define DDRCTL0_CR_DLLPITESTANDADC_ADCDdrChanSel_MAX                 (1) // 0x00000001
  #define DDRCTL0_CR_DLLPITESTANDADC_ADCDdrChanSel_DEF                 (0x00000000)
  #define DDRCTL0_CR_DLLPITESTANDADC_ADCDdrChanSel_HSH                 (0x011C261C)

  #define DDRCTL0_CR_DLLPITESTANDADC_ADCChopEn_OFF                     (29)
  #define DDRCTL0_CR_DLLPITESTANDADC_ADCChopEn_WID                     ( 1)
  #define DDRCTL0_CR_DLLPITESTANDADC_ADCChopEn_MSK                     (0x20000000)
  #define DDRCTL0_CR_DLLPITESTANDADC_ADCChopEn_MIN                     (0)
  #define DDRCTL0_CR_DLLPITESTANDADC_ADCChopEn_MAX                     (1) // 0x00000001
  #define DDRCTL0_CR_DLLPITESTANDADC_ADCChopEn_DEF                     (0x00000000)
  #define DDRCTL0_CR_DLLPITESTANDADC_ADCChopEn_HSH                     (0x011D261C)

  #define DDRCTL0_CR_DLLPITESTANDADC_ADCDone_OFF                       (30)
  #define DDRCTL0_CR_DLLPITESTANDADC_ADCDone_WID                       ( 1)
  #define DDRCTL0_CR_DLLPITESTANDADC_ADCDone_MSK                       (0x40000000)
  #define DDRCTL0_CR_DLLPITESTANDADC_ADCDone_MIN                       (0)
  #define DDRCTL0_CR_DLLPITESTANDADC_ADCDone_MAX                       (1) // 0x00000001
  #define DDRCTL0_CR_DLLPITESTANDADC_ADCDone_DEF                       (0x00000000)
  #define DDRCTL0_CR_DLLPITESTANDADC_ADCDone_HSH                       (0x011E261C)

  #define DDRCTL0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF              (31)
  #define DDRCTL0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID              ( 1)
  #define DDRCTL0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK              (0x80000000)
  #define DDRCTL0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN              (0)
  #define DDRCTL0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX              (1) // 0x00000001
  #define DDRCTL0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF              (0x00000000)
  #define DDRCTL0_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH              (0x011F261C)

#define DDRCTL0_CR_DLLSTATUS_REG                                       (0x00002620)

  #define DDRCTL0_CR_DLLSTATUS_DetrmLockStat_OFF                       ( 0)
  #define DDRCTL0_CR_DLLSTATUS_DetrmLockStat_WID                       ( 1)
  #define DDRCTL0_CR_DLLSTATUS_DetrmLockStat_MSK                       (0x00000001)
  #define DDRCTL0_CR_DLLSTATUS_DetrmLockStat_MIN                       (0)
  #define DDRCTL0_CR_DLLSTATUS_DetrmLockStat_MAX                       (1) // 0x00000001
  #define DDRCTL0_CR_DLLSTATUS_DetrmLockStat_DEF                       (0x00000000)
  #define DDRCTL0_CR_DLLSTATUS_DetrmLockStat_HSH                       (0x01002620)

  #define DDRCTL0_CR_DLLSTATUS_FuncLockStat_OFF                        ( 1)
  #define DDRCTL0_CR_DLLSTATUS_FuncLockStat_WID                        ( 1)
  #define DDRCTL0_CR_DLLSTATUS_FuncLockStat_MSK                        (0x00000002)
  #define DDRCTL0_CR_DLLSTATUS_FuncLockStat_MIN                        (0)
  #define DDRCTL0_CR_DLLSTATUS_FuncLockStat_MAX                        (1) // 0x00000001
  #define DDRCTL0_CR_DLLSTATUS_FuncLockStat_DEF                        (0x00000000)
  #define DDRCTL0_CR_DLLSTATUS_FuncLockStat_HSH                        (0x01012620)

  #define DDRCTL0_CR_DLLSTATUS_Lock_OFF                                ( 2)
  #define DDRCTL0_CR_DLLSTATUS_Lock_WID                                ( 1)
  #define DDRCTL0_CR_DLLSTATUS_Lock_MSK                                (0x00000004)
  #define DDRCTL0_CR_DLLSTATUS_Lock_MIN                                (0)
  #define DDRCTL0_CR_DLLSTATUS_Lock_MAX                                (1) // 0x00000001
  #define DDRCTL0_CR_DLLSTATUS_Lock_DEF                                (0x00000000)
  #define DDRCTL0_CR_DLLSTATUS_Lock_HSH                                (0x01022620)

  #define DDRCTL0_CR_DLLSTATUS_Timeout_OFF                             ( 3)
  #define DDRCTL0_CR_DLLSTATUS_Timeout_WID                             ( 1)
  #define DDRCTL0_CR_DLLSTATUS_Timeout_MSK                             (0x00000008)
  #define DDRCTL0_CR_DLLSTATUS_Timeout_MIN                             (0)
  #define DDRCTL0_CR_DLLSTATUS_Timeout_MAX                             (1) // 0x00000001
  #define DDRCTL0_CR_DLLSTATUS_Timeout_DEF                             (0x00000000)
  #define DDRCTL0_CR_DLLSTATUS_Timeout_HSH                             (0x01032620)

  #define DDRCTL0_CR_DLLSTATUS_DllReset_OFF                            ( 4)
  #define DDRCTL0_CR_DLLSTATUS_DllReset_WID                            ( 1)
  #define DDRCTL0_CR_DLLSTATUS_DllReset_MSK                            (0x00000010)
  #define DDRCTL0_CR_DLLSTATUS_DllReset_MIN                            (0)
  #define DDRCTL0_CR_DLLSTATUS_DllReset_MAX                            (1) // 0x00000001
  #define DDRCTL0_CR_DLLSTATUS_DllReset_DEF                            (0x00000000)
  #define DDRCTL0_CR_DLLSTATUS_DllReset_HSH                            (0x01042620)

  #define DDRCTL0_CR_DLLSTATUS_LongLockStat_OFF                        ( 5)
  #define DDRCTL0_CR_DLLSTATUS_LongLockStat_WID                        ( 1)
  #define DDRCTL0_CR_DLLSTATUS_LongLockStat_MSK                        (0x00000020)
  #define DDRCTL0_CR_DLLSTATUS_LongLockStat_MIN                        (0)
  #define DDRCTL0_CR_DLLSTATUS_LongLockStat_MAX                        (1) // 0x00000001
  #define DDRCTL0_CR_DLLSTATUS_LongLockStat_DEF                        (0x00000000)
  #define DDRCTL0_CR_DLLSTATUS_LongLockStat_HSH                        (0x01052620)

  #define DDRCTL0_CR_DLLSTATUS_EarlyLockStat_OFF                       ( 6)
  #define DDRCTL0_CR_DLLSTATUS_EarlyLockStat_WID                       ( 1)
  #define DDRCTL0_CR_DLLSTATUS_EarlyLockStat_MSK                       (0x00000040)
  #define DDRCTL0_CR_DLLSTATUS_EarlyLockStat_MIN                       (0)
  #define DDRCTL0_CR_DLLSTATUS_EarlyLockStat_MAX                       (1) // 0x00000001
  #define DDRCTL0_CR_DLLSTATUS_EarlyLockStat_DEF                       (0x00000000)
  #define DDRCTL0_CR_DLLSTATUS_EarlyLockStat_HSH                       (0x01062620)

  #define DDRCTL0_CR_DLLSTATUS_NormalMode_NotWkLock_OFF                ( 7)
  #define DDRCTL0_CR_DLLSTATUS_NormalMode_NotWkLock_WID                ( 1)
  #define DDRCTL0_CR_DLLSTATUS_NormalMode_NotWkLock_MSK                (0x00000080)
  #define DDRCTL0_CR_DLLSTATUS_NormalMode_NotWkLock_MIN                (0)
  #define DDRCTL0_CR_DLLSTATUS_NormalMode_NotWkLock_MAX                (1) // 0x00000001
  #define DDRCTL0_CR_DLLSTATUS_NormalMode_NotWkLock_DEF                (0x00000000)
  #define DDRCTL0_CR_DLLSTATUS_NormalMode_NotWkLock_HSH                (0x01072620)

  #define DDRCTL0_CR_DLLSTATUS_ADCout_OFF                              ( 8)
  #define DDRCTL0_CR_DLLSTATUS_ADCout_WID                              (10)
  #define DDRCTL0_CR_DLLSTATUS_ADCout_MSK                              (0x0003FF00)
  #define DDRCTL0_CR_DLLSTATUS_ADCout_MIN                              (0)
  #define DDRCTL0_CR_DLLSTATUS_ADCout_MAX                              (1023) // 0x000003FF
  #define DDRCTL0_CR_DLLSTATUS_ADCout_DEF                              (0x00000000)
  #define DDRCTL0_CR_DLLSTATUS_ADCout_HSH                              (0x0A082620)

  #define DDRCTL0_CR_DLLSTATUS_ADCStatus_OFF                           (18)
  #define DDRCTL0_CR_DLLSTATUS_ADCStatus_WID                           ( 1)
  #define DDRCTL0_CR_DLLSTATUS_ADCStatus_MSK                           (0x00040000)
  #define DDRCTL0_CR_DLLSTATUS_ADCStatus_MIN                           (0)
  #define DDRCTL0_CR_DLLSTATUS_ADCStatus_MAX                           (1) // 0x00000001
  #define DDRCTL0_CR_DLLSTATUS_ADCStatus_DEF                           (0x00000000)
  #define DDRCTL0_CR_DLLSTATUS_ADCStatus_HSH                           (0x01122620)

  #define DDRCTL0_CR_DLLSTATUS_pilags_OFF                              (19)
  #define DDRCTL0_CR_DLLSTATUS_pilags_WID                              ( 1)
  #define DDRCTL0_CR_DLLSTATUS_pilags_MSK                              (0x00080000)
  #define DDRCTL0_CR_DLLSTATUS_pilags_MIN                              (0)
  #define DDRCTL0_CR_DLLSTATUS_pilags_MAX                              (1) // 0x00000001
  #define DDRCTL0_CR_DLLSTATUS_pilags_DEF                              (0x00000000)
  #define DDRCTL0_CR_DLLSTATUS_pilags_HSH                              (0x01132620)

  #define DDRCTL0_CR_DLLSTATUS_spare_OFF                               (20)
  #define DDRCTL0_CR_DLLSTATUS_spare_WID                               (12)
  #define DDRCTL0_CR_DLLSTATUS_spare_MSK                               (0xFFF00000)
  #define DDRCTL0_CR_DLLSTATUS_spare_MIN                               (0)
  #define DDRCTL0_CR_DLLSTATUS_spare_MAX                               (4095) // 0x00000FFF
  #define DDRCTL0_CR_DLLSTATUS_spare_DEF                               (0x00000000)
  #define DDRCTL0_CR_DLLSTATUS_spare_HSH                               (0x0C142620)

#define DDRCTL0_CR_DLLDCMCTL_REG                                       (0x00002624)

  #define DDRCTL0_CR_DLLDCMCTL_start_OFF                               ( 0)
  #define DDRCTL0_CR_DLLDCMCTL_start_WID                               ( 1)
  #define DDRCTL0_CR_DLLDCMCTL_start_MSK                               (0x00000001)
  #define DDRCTL0_CR_DLLDCMCTL_start_MIN                               (0)
  #define DDRCTL0_CR_DLLDCMCTL_start_MAX                               (1) // 0x00000001
  #define DDRCTL0_CR_DLLDCMCTL_start_DEF                               (0x00000000)
  #define DDRCTL0_CR_DLLDCMCTL_start_HSH                               (0x01002624)

  #define DDRCTL0_CR_DLLDCMCTL_clken_OFF                               ( 1)
  #define DDRCTL0_CR_DLLDCMCTL_clken_WID                               ( 1)
  #define DDRCTL0_CR_DLLDCMCTL_clken_MSK                               (0x00000002)
  #define DDRCTL0_CR_DLLDCMCTL_clken_MIN                               (0)
  #define DDRCTL0_CR_DLLDCMCTL_clken_MAX                               (1) // 0x00000001
  #define DDRCTL0_CR_DLLDCMCTL_clken_DEF                               (0x00000000)
  #define DDRCTL0_CR_DLLDCMCTL_clken_HSH                               (0x01012624)

  #define DDRCTL0_CR_DLLDCMCTL_dcm_dccctl_en_OFF                       ( 2)
  #define DDRCTL0_CR_DLLDCMCTL_dcm_dccctl_en_WID                       ( 1)
  #define DDRCTL0_CR_DLLDCMCTL_dcm_dccctl_en_MSK                       (0x00000004)
  #define DDRCTL0_CR_DLLDCMCTL_dcm_dccctl_en_MIN                       (0)
  #define DDRCTL0_CR_DLLDCMCTL_dcm_dccctl_en_MAX                       (1) // 0x00000001
  #define DDRCTL0_CR_DLLDCMCTL_dcm_dccctl_en_DEF                       (0x00000000)
  #define DDRCTL0_CR_DLLDCMCTL_dcm_dccctl_en_HSH                       (0x01022624)

  #define DDRCTL0_CR_DLLDCMCTL_dccctl_OFF                              ( 3)
  #define DDRCTL0_CR_DLLDCMCTL_dccctl_WID                              ( 4)
  #define DDRCTL0_CR_DLLDCMCTL_dccctl_MSK                              (0x00000078)
  #define DDRCTL0_CR_DLLDCMCTL_dccctl_MIN                              (0)
  #define DDRCTL0_CR_DLLDCMCTL_dccctl_MAX                              (15) // 0x0000000F
  #define DDRCTL0_CR_DLLDCMCTL_dccctl_DEF                              (0x00000000)
  #define DDRCTL0_CR_DLLDCMCTL_dccctl_HSH                              (0x04032624)

  #define DDRCTL0_CR_DLLDCMCTL_duration_OFF                            ( 7)
  #define DDRCTL0_CR_DLLDCMCTL_duration_WID                            ( 3)
  #define DDRCTL0_CR_DLLDCMCTL_duration_MSK                            (0x00000380)
  #define DDRCTL0_CR_DLLDCMCTL_duration_MIN                            (0)
  #define DDRCTL0_CR_DLLDCMCTL_duration_MAX                            (7) // 0x00000007
  #define DDRCTL0_CR_DLLDCMCTL_duration_DEF                            (0x00000000)
  #define DDRCTL0_CR_DLLDCMCTL_duration_HSH                            (0x03072624)

  #define DDRCTL0_CR_DLLDCMCTL_dcm_done_OFF                            (10)
  #define DDRCTL0_CR_DLLDCMCTL_dcm_done_WID                            ( 1)
  #define DDRCTL0_CR_DLLDCMCTL_dcm_done_MSK                            (0x00000400)
  #define DDRCTL0_CR_DLLDCMCTL_dcm_done_MIN                            (0)
  #define DDRCTL0_CR_DLLDCMCTL_dcm_done_MAX                            (1) // 0x00000001
  #define DDRCTL0_CR_DLLDCMCTL_dcm_done_DEF                            (0x00000000)
  #define DDRCTL0_CR_DLLDCMCTL_dcm_done_HSH                            (0x010A2624)

  #define DDRCTL0_CR_DLLDCMCTL_dcm_results_OFF                         (11)
  #define DDRCTL0_CR_DLLDCMCTL_dcm_results_WID                         (15)
  #define DDRCTL0_CR_DLLDCMCTL_dcm_results_MSK                         (0x03FFF800)
  #define DDRCTL0_CR_DLLDCMCTL_dcm_results_MIN                         (0)
  #define DDRCTL0_CR_DLLDCMCTL_dcm_results_MAX                         (32767) // 0x00007FFF
  #define DDRCTL0_CR_DLLDCMCTL_dcm_results_DEF                         (0x00000000)
  #define DDRCTL0_CR_DLLDCMCTL_dcm_results_HSH                         (0x0F0B2624)

  #define DDRCTL0_CR_DLLDCMCTL_spare0_OFF                              (26)
  #define DDRCTL0_CR_DLLDCMCTL_spare0_WID                              ( 6)
  #define DDRCTL0_CR_DLLDCMCTL_spare0_MSK                              (0xFC000000)
  #define DDRCTL0_CR_DLLDCMCTL_spare0_MIN                              (0)
  #define DDRCTL0_CR_DLLDCMCTL_spare0_MAX                              (63) // 0x0000003F
  #define DDRCTL0_CR_DLLDCMCTL_spare0_DEF                              (0x00000000)
  #define DDRCTL0_CR_DLLDCMCTL_spare0_HSH                              (0x061A2624)

#define DDRCKECH0_CR_DDRCRCMDCOMP_REG                                  (0x00002680)

  #define DDRCKECH0_CR_DDRCRCMDCOMP_Scomp_OFF                          ( 0)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_Scomp_WID                          ( 6)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_Scomp_MSK                          (0x0000003F)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_Scomp_MIN                          (0)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_Scomp_MAX                          (63) // 0x0000003F
  #define DDRCKECH0_CR_DDRCRCMDCOMP_Scomp_DEF                          (0x00000000)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_Scomp_HSH                          (0x06002680)

  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvUp_OFF                     ( 6)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvUp_WID                     ( 6)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvUp_MSK                     (0x00000FC0)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvUp_MIN                     (0)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvUp_MAX                     (63) // 0x0000003F
  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvUp_DEF                     (0x00000000)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvUp_HSH                     (0x06062680)

  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvDown_OFF                   (12)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvDown_WID                   ( 6)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvDown_MSK                   (0x0003F000)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvDown_MIN                   (0)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvDown_MAX                   (63) // 0x0000003F
  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvDown_DEF                   (0x00000000)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_RcompDrvDown_HSH                   (0x060C2680)

  #define DDRCKECH0_CR_DDRCRCMDCOMP_Spare_OFF                          (18)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_Spare_WID                          (14)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_Spare_MSK                          (0xFFFC0000)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_Spare_MIN                          (0)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_Spare_MAX                          (16383) // 0x00003FFF
  #define DDRCKECH0_CR_DDRCRCMDCOMP_Spare_DEF                          (0x00000000)
  #define DDRCKECH0_CR_DDRCRCMDCOMP_Spare_HSH                          (0x0E122680)

#define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_REG                            (0x00002684)

  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_OFF              ( 0)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_WID              ( 5)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MSK              (0x0000001F)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MIN              (-16)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MAX              (15) // 0x0000000F
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_DEF              (0x00000000)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_HSH              (0x85002684)

  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_OFF         ( 5)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_WID         ( 4)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MSK         (0x000001E0)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MIN         (-8)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MAX         (7) // 0x00000007
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_DEF         (0x00000000)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_HSH         (0x84052684)

  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_OFF       ( 9)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_WID       ( 4)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MSK       (0x00001E00)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MIN       (-8)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MAX       (7) // 0x00000007
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_DEF       (0x00000000)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_HSH       (0x84092684)

  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_Spare_OFF                    (13)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_Spare_WID                    (19)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_Spare_MSK                    (0xFFFFE000)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_Spare_MIN                    (0)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_Spare_MAX                    (524287) // 0x0007FFFF
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_Spare_DEF                    (0x00000000)
  #define DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_Spare_HSH                    (0x130D2684)

#define DDRCKECH0_CR_DDRCRCKERANKSUSED_REG                             (0x00002688)

  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_CtlCkTxEn_OFF                 ( 0)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_CtlCkTxEn_WID                 ( 8)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_CtlCkTxEn_MSK                 (0x000000FF)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_CtlCkTxEn_MIN                 (0)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_CtlCkTxEn_MAX                 (255) // 0x000000FF
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_CtlCkTxEn_DEF                 (0x000000FF)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_CtlCkTxEn_HSH                 (0x08002688)

  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_PiClkEn_OFF                   ( 8)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_PiClkEn_WID                   ( 4)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_PiClkEn_MSK                   (0x00000F00)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_PiClkEn_MIN                   (0)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_PiClkEn_MAX                   (15) // 0x0000000F
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_PiClkEn_DEF                   (0x0000000F)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_PiClkEn_HSH                   (0x04082688)

  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_DdrCkeCmdSlwDlyByp_OFF        (12)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_DdrCkeCmdSlwDlyByp_WID        ( 1)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_DdrCkeCmdSlwDlyByp_MSK        (0x00001000)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_DdrCkeCmdSlwDlyByp_MIN        (0)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_DdrCkeCmdSlwDlyByp_MAX        (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_DdrCkeCmdSlwDlyByp_DEF        (0x00000000)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_DdrCkeCmdSlwDlyByp_HSH        (0x010C2688)

  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_DdrCtlCkeSlwDlyByp_OFF        (13)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_DdrCtlCkeSlwDlyByp_WID        ( 1)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_DdrCtlCkeSlwDlyByp_MSK        (0x00002000)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_DdrCtlCkeSlwDlyByp_MIN        (0)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_DdrCtlCkeSlwDlyByp_MAX        (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_DdrCtlCkeSlwDlyByp_DEF        (0x00000000)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_DdrCtlCkeSlwDlyByp_HSH        (0x010D2688)

  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_PrtEn_OFF                     (14)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_PrtEn_WID                     ( 1)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_PrtEn_MSK                     (0x00004000)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_PrtEn_MIN                     (0)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_PrtEn_MAX                     (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_PrtEn_DEF                     (0x00000000)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_PrtEn_HSH                     (0x010E2688)

  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_AlrtEn_OFF                    (15)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_AlrtEn_WID                    ( 1)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_AlrtEn_MSK                    (0x00008000)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_AlrtEn_MIN                    (0)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_AlrtEn_MAX                    (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_AlrtEn_DEF                    (0x00000000)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_AlrtEn_HSH                    (0x010F2688)

  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cke_pi_gate_sr_only_OFF       (16)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cke_pi_gate_sr_only_WID       ( 1)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cke_pi_gate_sr_only_MSK       (0x00010000)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cke_pi_gate_sr_only_MIN       (0)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cke_pi_gate_sr_only_MAX       (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cke_pi_gate_sr_only_DEF       (0x00000000)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cke_pi_gate_sr_only_HSH       (0x01102688)

  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_Gear1_OFF                     (17)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_Gear1_WID                     ( 1)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_Gear1_MSK                     (0x00020000)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_Gear1_MIN                     (0)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_Gear1_MAX                     (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_Gear1_DEF                     (0x00000001)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_Gear1_HSH                     (0x01112688)

  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_lp4xvoltageselect_OFF         (18)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_lp4xvoltageselect_WID         ( 1)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_lp4xvoltageselect_MSK         (0x00040000)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_lp4xvoltageselect_MIN         (0)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_lp4xvoltageselect_MAX         (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_lp4xvoltageselect_DEF         (0x00000000)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_lp4xvoltageselect_HSH         (0x01122688)

  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_xover_mindelay_ctl_OFF        (19)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_xover_mindelay_ctl_WID        ( 2)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_xover_mindelay_ctl_MSK        (0x00180000)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_xover_mindelay_ctl_MIN        (0)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_xover_mindelay_ctl_MAX        (3) // 0x00000003
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_xover_mindelay_ctl_DEF        (0x00000000)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_xover_mindelay_ctl_HSH        (0x02132688)

  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cmd_eq_strengh_OFF            (21)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cmd_eq_strengh_WID            ( 4)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cmd_eq_strengh_MSK            (0x01E00000)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cmd_eq_strengh_MIN            (0)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cmd_eq_strengh_MAX            (15) // 0x0000000F
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cmd_eq_strengh_DEF            (0x0000000F)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cmd_eq_strengh_HSH            (0x04152688)

  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cmd_eq_en_OFF                 (25)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cmd_eq_en_WID                 ( 1)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cmd_eq_en_MSK                 (0x02000000)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cmd_eq_en_MIN                 (0)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cmd_eq_en_MAX                 (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cmd_eq_en_DEF                 (0x00000000)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cmd_eq_en_HSH                 (0x01192688)

  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cmd_eq_constz_OFF             (26)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cmd_eq_constz_WID             ( 1)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cmd_eq_constz_MSK             (0x04000000)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cmd_eq_constz_MIN             (0)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cmd_eq_constz_MAX             (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cmd_eq_constz_DEF             (0x00000001)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_cmd_eq_constz_HSH             (0x011A2688)

  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_CkeCriClkGateEnGvBlock_OFF    (27)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_CkeCriClkGateEnGvBlock_WID    ( 1)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_CkeCriClkGateEnGvBlock_MSK    (0x08000000)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_CkeCriClkGateEnGvBlock_MIN    (0)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_CkeCriClkGateEnGvBlock_MAX    (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_CkeCriClkGateEnGvBlock_DEF    (0x00000000)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_CkeCriClkGateEnGvBlock_HSH    (0x011B2688)

  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_Spare_OFF                     (28)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_Spare_WID                     ( 4)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_Spare_MSK                     (0xF0000000)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_Spare_MIN                     (0)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_Spare_MAX                     (15) // 0x0000000F
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_Spare_DEF                     (0x00000000)
  #define DDRCKECH0_CR_DDRCRCKERANKSUSED_Spare_HSH                     (0x041C2688)

#define DDRCKECH0_CR_DDRCRCTLCOMP_REG                                  (0x00002690)

  #define DDRCKECH0_CR_DDRCRCTLCOMP_Scomp_OFF                          ( 0)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_Scomp_WID                          ( 6)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_Scomp_MSK                          (0x0000003F)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_Scomp_MIN                          (0)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_Scomp_MAX                          (63) // 0x0000003F
  #define DDRCKECH0_CR_DDRCRCTLCOMP_Scomp_DEF                          (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_Scomp_HSH                          (0x06002690)

  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvUp_OFF                     ( 6)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvUp_WID                     ( 6)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvUp_MSK                     (0x00000FC0)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvUp_MIN                     (0)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvUp_MAX                     (63) // 0x0000003F
  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvUp_DEF                     (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvUp_HSH                     (0x06062690)

  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvDown_OFF                   (12)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvDown_WID                   ( 6)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvDown_MSK                   (0x0003F000)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvDown_MIN                   (0)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvDown_MAX                   (63) // 0x0000003F
  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvDown_DEF                   (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_RcompDrvDown_HSH                   (0x060C2690)

  #define DDRCKECH0_CR_DDRCRCTLCOMP_Spare_OFF                          (18)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_Spare_WID                          (14)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_Spare_MSK                          (0xFFFC0000)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_Spare_MIN                          (0)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_Spare_MAX                          (16383) // 0x00003FFF
  #define DDRCKECH0_CR_DDRCRCTLCOMP_Spare_DEF                          (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCOMP_Spare_HSH                          (0x0E122690)

#define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_REG                            (0x00002694)

  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_OFF              ( 0)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_WID              ( 5)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MSK              (0x0000001F)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MIN              (-16)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MAX              (15) // 0x0000000F
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_DEF              (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_HSH              (0x85002694)

  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_OFF         ( 5)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_WID         ( 4)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MSK         (0x000001E0)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MIN         (-8)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MAX         (7) // 0x00000007
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_DEF         (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_HSH         (0x84052694)

  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_OFF       ( 9)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_WID       ( 4)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MSK       (0x00001E00)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MIN       (-8)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MAX       (7) // 0x00000007
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_DEF       (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_HSH       (0x84092694)

  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_Spare_OFF                    (13)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_Spare_WID                    (19)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_Spare_MSK                    (0xFFFFE000)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_Spare_MIN                    (0)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_Spare_MAX                    (524287) // 0x0007FFFF
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_Spare_DEF                    (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_Spare_HSH                    (0x130D2694)

#define DDRCKECH0_CR_DDRCRCTLPICODING_REG                              (0x00002698)

  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode0_OFF                 ( 0)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode0_WID                 ( 7)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode0_MSK                 (0x0000007F)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode0_MIN                 (0)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode0_MAX                 (127) // 0x0000007F
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode0_DEF                 (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode0_HSH                 (0x07002698)

  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode1_OFF                 ( 7)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode1_WID                 ( 7)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode1_MSK                 (0x00003F80)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode1_MIN                 (0)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode1_MAX                 (127) // 0x0000007F
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode1_DEF                 (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode1_HSH                 (0x07072698)

  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode2_OFF                 (14)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode2_WID                 ( 7)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode2_MSK                 (0x001FC000)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode2_MIN                 (0)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode2_MAX                 (127) // 0x0000007F
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode2_DEF                 (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode2_HSH                 (0x070E2698)

  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode3_OFF                 (21)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode3_WID                 ( 7)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode3_MSK                 (0x0FE00000)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode3_MIN                 (0)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode3_MAX                 (127) // 0x0000007F
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode3_DEF                 (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode3_HSH                 (0x07152698)

  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlXoverEnable_OFF             (28)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlXoverEnable_WID             ( 1)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlXoverEnable_MSK             (0x10000000)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlXoverEnable_MIN             (0)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlXoverEnable_MAX             (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlXoverEnable_DEF             (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_CtlXoverEnable_HSH             (0x011C2698)

  #define DDRCKECH0_CR_DDRCRCTLPICODING_Spare_OFF                      (29)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_Spare_WID                      ( 3)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_Spare_MSK                      (0xE0000000)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_Spare_MIN                      (0)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_Spare_MAX                      (7) // 0x00000007
  #define DDRCKECH0_CR_DDRCRCTLPICODING_Spare_DEF                      (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLPICODING_Spare_HSH                      (0x031D2698)

#define DDRCKECH0_CR_DDRCRCTLCONTROLS_REG                              (0x0000269C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RefPi_OFF                      ( 0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RefPi_WID                      ( 4)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RefPi_MSK                      (0x0000000F)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RefPi_MIN                      (-8)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RefPi_MAX                      (7) // 0x00000007
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RefPi_DEF                      (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RefPi_HSH                      (0x8400269C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllMask_OFF                    ( 4)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllMask_WID                    ( 2)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllMask_MSK                    (0x00000030)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllMask_MIN                    (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllMask_MAX                    (3) // 0x00000003
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllMask_DEF                    (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllMask_HSH                    (0x0204269C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_OFF             ( 6)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_WID             ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_MSK             (0x00000040)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_MIN             (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_MAX             (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_DEF             (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_ClkGateDisable_HSH             (0x0106269C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_TxOn_OFF                       ( 7)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_TxOn_WID                       ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_TxOn_MSK                       (0x00000080)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_TxOn_MIN                       (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_TxOn_MAX                       (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_TxOn_DEF                       (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_TxOn_HSH                       (0x0107269C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IntClkOn_OFF                   ( 8)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IntClkOn_WID                   ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IntClkOn_MSK                   (0x00000100)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IntClkOn_MIN                   (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IntClkOn_MAX                   (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IntClkOn_DEF                   (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IntClkOn_HSH                   (0x0108269C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RepClkOn_OFF                   ( 9)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RepClkOn_WID                   ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RepClkOn_MSK                   (0x00000200)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RepClkOn_MIN                   (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RepClkOn_MAX                   (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RepClkOn_DEF                   (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RepClkOn_HSH                   (0x0109269C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_OFF                 (10)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_WID                 ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_MSK                 (0x00000400)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_MIN                 (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_MAX                 (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_DEF                 (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IolbOrMisr_HSH                 (0x010A269C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IOLBHold_OFF                   (11)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IOLBHold_WID                   ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IOLBHold_MSK                   (0x00000800)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IOLBHold_MIN                   (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IOLBHold_MAX                   (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IOLBHold_DEF                   (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_IOLBHold_HSH                   (0x010B269C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_OdtMode_OFF                    (12)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_OdtMode_WID                    ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_OdtMode_MSK                    (0x00001000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_OdtMode_MIN                    (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_OdtMode_MAX                    (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_OdtMode_DEF                    (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_OdtMode_HSH                    (0x010C269C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CmdTxEq_OFF                    (13)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CmdTxEq_WID                    ( 2)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CmdTxEq_MSK                    (0x00006000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CmdTxEq_MIN                    (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CmdTxEq_MAX                    (3) // 0x00000003
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CmdTxEq_DEF                    (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CmdTxEq_HSH                    (0x020D269C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_OFF             (15)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_WID             ( 2)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MSK             (0x00018000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MIN             (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MAX             (3) // 0x00000003
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_DEF             (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_HSH             (0x020F269C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlTxEq_OFF                    (17)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlTxEq_WID                    ( 2)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlTxEq_MSK                    (0x00060000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlTxEq_MIN                    (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlTxEq_MAX                    (3) // 0x00000003
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlTxEq_DEF                    (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlTxEq_HSH                    (0x0211269C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_OFF                   (19)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_WID                   ( 2)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_MSK                   (0x00180000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_MIN                   (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_MAX                   (3) // 0x00000003
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_DEF                   (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CtlSRDrv_HSH                   (0x0213269C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RxVref_OFF                     (21)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RxVref_WID                     ( 6)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RxVref_MSK                     (0x07E00000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RxVref_MIN                     (-32)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RxVref_MAX                     (31) // 0x0000001F
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RxVref_DEF                     (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_RxVref_HSH                     (0x8615269C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_VccddqHi_OFF                   (27)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_VccddqHi_WID                   ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_VccddqHi_MSK                   (0x08000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_VccddqHi_MIN                   (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_VccddqHi_MAX                   (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_VccddqHi_DEF                   (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_VccddqHi_HSH                   (0x011B269C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllWeakLock_OFF                (28)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllWeakLock_WID                ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllWeakLock_MSK                (0x10000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllWeakLock_MIN                (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllWeakLock_MAX                (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllWeakLock_DEF                (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_DllWeakLock_HSH                (0x011C269C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CMD_Rate_OFF                   (29)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CMD_Rate_WID                   ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CMD_Rate_MSK                   (0x20000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CMD_Rate_MIN                   (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CMD_Rate_MAX                   (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CMD_Rate_DEF                   (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_CMD_Rate_HSH                   (0x011D269C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_OFF                (30)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_WID                ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MSK                (0x40000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MIN                (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MAX                (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_DEF                (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_HSH                (0x011E269C)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_ma3_ma4_par_dis_OFF            (31)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_ma3_ma4_par_dis_WID            ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_ma3_ma4_par_dis_MSK            (0x80000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_ma3_ma4_par_dis_MIN            (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_ma3_ma4_par_dis_MAX            (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_ma3_ma4_par_dis_DEF            (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS_ma3_ma4_par_dis_HSH            (0x011F269C)

#define DDRCKECH0_CR_DDRCRCTLCONTROLS1_REG                             (0x000026A0)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_RxVref_OFF                    ( 0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_RxVref_WID                    ( 8)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_RxVref_MSK                    (0x000000FF)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_RxVref_MIN                    (-128)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_RxVref_MAX                    (127) // 0x0000007F
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_RxVref_DEF                    (0x00000060)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_RxVref_HSH                    (0x880026A0)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_MapCkeForScOdt_OFF            ( 8)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_MapCkeForScOdt_WID            (18)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_MapCkeForScOdt_MSK            (0x03FFFF00)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_MapCkeForScOdt_MIN            (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_MapCkeForScOdt_MAX            (262143) // 0x0003FFFF
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_MapCkeForScOdt_DEF            (0x00010458)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_MapCkeForScOdt_HSH            (0x120826A0)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CMDLowsupEn_OFF               (26)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CMDLowsupEn_WID               ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CMDLowsupEn_MSK               (0x04000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CMDLowsupEn_MIN               (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CMDLowsupEn_MAX               (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CMDLowsupEn_DEF               (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CMDLowsupEn_HSH               (0x011A26A0)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CKELowsupEn_OFF               (27)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CKELowsupEn_WID               ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CKELowsupEn_MSK               (0x08000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CKELowsupEn_MIN               (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CKELowsupEn_MAX               (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CKELowsupEn_DEF               (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CKELowsupEn_HSH               (0x011B26A0)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CTLLowsupEn_OFF               (28)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CTLLowsupEn_WID               ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CTLLowsupEn_MSK               (0x10000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CTLLowsupEn_MIN               (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CTLLowsupEn_MAX               (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CTLLowsupEn_DEF               (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CTLLowsupEn_HSH               (0x011C26A0)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CLKLowsupEn_OFF               (29)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CLKLowsupEn_WID               ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CLKLowsupEn_MSK               (0x20000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CLKLowsupEn_MIN               (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CLKLowsupEn_MAX               (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CLKLowsupEn_DEF               (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_CLKLowsupEn_HSH               (0x011D26A0)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_en_sr_mode_to_cke_OFF         (30)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_en_sr_mode_to_cke_WID         ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_en_sr_mode_to_cke_MSK         (0x40000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_en_sr_mode_to_cke_MIN         (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_en_sr_mode_to_cke_MAX         (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_en_sr_mode_to_cke_DEF         (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_en_sr_mode_to_cke_HSH         (0x011E26A0)

  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_c3segsel_b_for_cke_OFF        (31)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_c3segsel_b_for_cke_WID        ( 1)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_c3segsel_b_for_cke_MSK        (0x80000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_c3segsel_b_for_cke_MIN        (0)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_c3segsel_b_for_cke_MAX        (1) // 0x00000001
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_c3segsel_b_for_cke_DEF        (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLCONTROLS1_c3segsel_b_for_cke_HSH        (0x011F26A0)

#define DDRCKECH0_CR_DDRCRLOOPBACKFEEDBACK_REG                         (0x000026A4)

  #define DDRCKECH0_CR_DDRCRLOOPBACKFEEDBACK_datatrainfeedback_OFF     ( 0)
  #define DDRCKECH0_CR_DDRCRLOOPBACKFEEDBACK_datatrainfeedback_WID     (10)
  #define DDRCKECH0_CR_DDRCRLOOPBACKFEEDBACK_datatrainfeedback_MSK     (0x000003FF)
  #define DDRCKECH0_CR_DDRCRLOOPBACKFEEDBACK_datatrainfeedback_MIN     (0)
  #define DDRCKECH0_CR_DDRCRLOOPBACKFEEDBACK_datatrainfeedback_MAX     (1023) // 0x000003FF
  #define DDRCKECH0_CR_DDRCRLOOPBACKFEEDBACK_datatrainfeedback_DEF     (0x00000000)
  #define DDRCKECH0_CR_DDRCRLOOPBACKFEEDBACK_datatrainfeedback_HSH     (0x0A0026A4)

  #define DDRCKECH0_CR_DDRCRLOOPBACKFEEDBACK_Spare_OFF                 (10)
  #define DDRCKECH0_CR_DDRCRLOOPBACKFEEDBACK_Spare_WID                 (22)
  #define DDRCKECH0_CR_DDRCRLOOPBACKFEEDBACK_Spare_MSK                 (0xFFFFFC00)
  #define DDRCKECH0_CR_DDRCRLOOPBACKFEEDBACK_Spare_MIN                 (0)
  #define DDRCKECH0_CR_DDRCRLOOPBACKFEEDBACK_Spare_MAX                 (4194303) // 0x003FFFFF
  #define DDRCKECH0_CR_DDRCRLOOPBACKFEEDBACK_Spare_DEF                 (0x00000000)
  #define DDRCKECH0_CR_DDRCRLOOPBACKFEEDBACK_Spare_HSH                 (0x160A26A4)

#define DDRCKECH0_CR_DDRCRCTLTCOCONTROL0_REG                           (0x000026A8)

  #define DDRCKECH0_CR_DDRCRCTLTCOCONTROL0_CtlTcoComp_OFF              ( 0)
  #define DDRCKECH0_CR_DDRCRCTLTCOCONTROL0_CtlTcoComp_WID              ( 6)
  #define DDRCKECH0_CR_DDRCRCTLTCOCONTROL0_CtlTcoComp_MSK              (0x0000003F)
  #define DDRCKECH0_CR_DDRCRCTLTCOCONTROL0_CtlTcoComp_MIN              (0)
  #define DDRCKECH0_CR_DDRCRCTLTCOCONTROL0_CtlTcoComp_MAX              (63) // 0x0000003F
  #define DDRCKECH0_CR_DDRCRCTLTCOCONTROL0_CtlTcoComp_DEF              (0x00000020)
  #define DDRCKECH0_CR_DDRCRCTLTCOCONTROL0_CtlTcoComp_HSH              (0x060026A8)

  #define DDRCKECH0_CR_DDRCRCTLTCOCONTROL0_Spare_OFF                   ( 6)
  #define DDRCKECH0_CR_DDRCRCTLTCOCONTROL0_Spare_WID                   (26)
  #define DDRCKECH0_CR_DDRCRCTLTCOCONTROL0_Spare_MSK                   (0xFFFFFFC0)
  #define DDRCKECH0_CR_DDRCRCTLTCOCONTROL0_Spare_MIN                   (0)
  #define DDRCKECH0_CR_DDRCRCTLTCOCONTROL0_Spare_MAX                   (67108863) // 0x03FFFFFF
  #define DDRCKECH0_CR_DDRCRCTLTCOCONTROL0_Spare_DEF                   (0x00000000)
  #define DDRCKECH0_CR_DDRCRCTLTCOCONTROL0_Spare_HSH                   (0x1A0626A8)

#define DDRCKECH0_CR_DDRCRCMDTCOCONTROL0_REG                           (0x000026AC)

  #define DDRCKECH0_CR_DDRCRCMDTCOCONTROL0_CmdTcoComp_OFF              ( 0)
  #define DDRCKECH0_CR_DDRCRCMDTCOCONTROL0_CmdTcoComp_WID              ( 6)
  #define DDRCKECH0_CR_DDRCRCMDTCOCONTROL0_CmdTcoComp_MSK              (0x0000003F)
  #define DDRCKECH0_CR_DDRCRCMDTCOCONTROL0_CmdTcoComp_MIN              (0)
  #define DDRCKECH0_CR_DDRCRCMDTCOCONTROL0_CmdTcoComp_MAX              (63) // 0x0000003F
  #define DDRCKECH0_CR_DDRCRCMDTCOCONTROL0_CmdTcoComp_DEF              (0x00000020)
  #define DDRCKECH0_CR_DDRCRCMDTCOCONTROL0_CmdTcoComp_HSH              (0x060026AC)

  #define DDRCKECH0_CR_DDRCRCMDTCOCONTROL0_Spare_OFF                   ( 6)
  #define DDRCKECH0_CR_DDRCRCMDTCOCONTROL0_Spare_WID                   (26)
  #define DDRCKECH0_CR_DDRCRCMDTCOCONTROL0_Spare_MSK                   (0xFFFFFFC0)
  #define DDRCKECH0_CR_DDRCRCMDTCOCONTROL0_Spare_MIN                   (0)
  #define DDRCKECH0_CR_DDRCRCMDTCOCONTROL0_Spare_MAX                   (67108863) // 0x03FFFFFF
  #define DDRCKECH0_CR_DDRCRCMDTCOCONTROL0_Spare_DEF                   (0x00000000)
  #define DDRCKECH0_CR_DDRCRCMDTCOCONTROL0_Spare_HSH                   (0x1A0626AC)

#define DDRCKECH1_CR_DDRCRCMDCOMP_REG                                  (0x00002700)

  #define DDRCKECH1_CR_DDRCRCMDCOMP_Scomp_OFF                          ( 0)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_Scomp_WID                          ( 6)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_Scomp_MSK                          (0x0000003F)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_Scomp_MIN                          (0)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_Scomp_MAX                          (63) // 0x0000003F
  #define DDRCKECH1_CR_DDRCRCMDCOMP_Scomp_DEF                          (0x00000000)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_Scomp_HSH                          (0x06002700)

  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvUp_OFF                     ( 6)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvUp_WID                     ( 6)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvUp_MSK                     (0x00000FC0)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvUp_MIN                     (0)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvUp_MAX                     (63) // 0x0000003F
  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvUp_DEF                     (0x00000000)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvUp_HSH                     (0x06062700)

  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvDown_OFF                   (12)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvDown_WID                   ( 6)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvDown_MSK                   (0x0003F000)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvDown_MIN                   (0)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvDown_MAX                   (63) // 0x0000003F
  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvDown_DEF                   (0x00000000)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_RcompDrvDown_HSH                   (0x060C2700)

  #define DDRCKECH1_CR_DDRCRCMDCOMP_Spare_OFF                          (18)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_Spare_WID                          (14)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_Spare_MSK                          (0xFFFC0000)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_Spare_MIN                          (0)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_Spare_MAX                          (16383) // 0x00003FFF
  #define DDRCKECH1_CR_DDRCRCMDCOMP_Spare_DEF                          (0x00000000)
  #define DDRCKECH1_CR_DDRCRCMDCOMP_Spare_HSH                          (0x0E122700)

#define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_REG                            (0x00002704)

  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_OFF              ( 0)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_WID              ( 5)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MSK              (0x0000001F)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MIN              (-16)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MAX              (15) // 0x0000000F
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_DEF              (0x00000000)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_ScompOffset_HSH              (0x85002704)

  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_OFF         ( 5)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_WID         ( 4)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MSK         (0x000001E0)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MIN         (-8)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MAX         (7) // 0x00000007
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_DEF         (0x00000000)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_HSH         (0x84052704)

  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_OFF       ( 9)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_WID       ( 4)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MSK       (0x00001E00)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MIN       (-8)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_MAX       (7) // 0x00000007
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_DEF       (0x00000000)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_HSH       (0x84092704)

  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_Spare_OFF                    (13)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_Spare_WID                    (19)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_Spare_MSK                    (0xFFFFE000)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_Spare_MIN                    (0)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_Spare_MAX                    (524287) // 0x0007FFFF
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_Spare_DEF                    (0x00000000)
  #define DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_Spare_HSH                    (0x130D2704)

#define DDRCKECH1_CR_DDRCRCKERANKSUSED_REG                             (0x00002708)

  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_CtlCkTxEn_OFF                 ( 0)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_CtlCkTxEn_WID                 ( 8)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_CtlCkTxEn_MSK                 (0x000000FF)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_CtlCkTxEn_MIN                 (0)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_CtlCkTxEn_MAX                 (255) // 0x000000FF
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_CtlCkTxEn_DEF                 (0x000000FF)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_CtlCkTxEn_HSH                 (0x08002708)

  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_PiClkEn_OFF                   ( 8)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_PiClkEn_WID                   ( 4)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_PiClkEn_MSK                   (0x00000F00)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_PiClkEn_MIN                   (0)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_PiClkEn_MAX                   (15) // 0x0000000F
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_PiClkEn_DEF                   (0x0000000F)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_PiClkEn_HSH                   (0x04082708)

  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_DdrCkeCmdSlwDlyByp_OFF        (12)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_DdrCkeCmdSlwDlyByp_WID        ( 1)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_DdrCkeCmdSlwDlyByp_MSK        (0x00001000)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_DdrCkeCmdSlwDlyByp_MIN        (0)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_DdrCkeCmdSlwDlyByp_MAX        (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_DdrCkeCmdSlwDlyByp_DEF        (0x00000000)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_DdrCkeCmdSlwDlyByp_HSH        (0x010C2708)

  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_DdrCtlCkeSlwDlyByp_OFF        (13)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_DdrCtlCkeSlwDlyByp_WID        ( 1)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_DdrCtlCkeSlwDlyByp_MSK        (0x00002000)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_DdrCtlCkeSlwDlyByp_MIN        (0)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_DdrCtlCkeSlwDlyByp_MAX        (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_DdrCtlCkeSlwDlyByp_DEF        (0x00000000)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_DdrCtlCkeSlwDlyByp_HSH        (0x010D2708)

  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_PrtEn_OFF                     (14)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_PrtEn_WID                     ( 1)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_PrtEn_MSK                     (0x00004000)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_PrtEn_MIN                     (0)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_PrtEn_MAX                     (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_PrtEn_DEF                     (0x00000000)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_PrtEn_HSH                     (0x010E2708)

  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_AlrtEn_OFF                    (15)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_AlrtEn_WID                    ( 1)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_AlrtEn_MSK                    (0x00008000)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_AlrtEn_MIN                    (0)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_AlrtEn_MAX                    (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_AlrtEn_DEF                    (0x00000000)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_AlrtEn_HSH                    (0x010F2708)

  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cke_pi_gate_sr_only_OFF       (16)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cke_pi_gate_sr_only_WID       ( 1)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cke_pi_gate_sr_only_MSK       (0x00010000)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cke_pi_gate_sr_only_MIN       (0)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cke_pi_gate_sr_only_MAX       (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cke_pi_gate_sr_only_DEF       (0x00000000)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cke_pi_gate_sr_only_HSH       (0x01102708)

  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_Gear1_OFF                     (17)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_Gear1_WID                     ( 1)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_Gear1_MSK                     (0x00020000)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_Gear1_MIN                     (0)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_Gear1_MAX                     (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_Gear1_DEF                     (0x00000001)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_Gear1_HSH                     (0x01112708)

  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_lp4xvoltageselect_OFF         (18)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_lp4xvoltageselect_WID         ( 1)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_lp4xvoltageselect_MSK         (0x00040000)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_lp4xvoltageselect_MIN         (0)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_lp4xvoltageselect_MAX         (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_lp4xvoltageselect_DEF         (0x00000000)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_lp4xvoltageselect_HSH         (0x01122708)

  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_xover_mindelay_ctl_OFF        (19)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_xover_mindelay_ctl_WID        ( 2)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_xover_mindelay_ctl_MSK        (0x00180000)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_xover_mindelay_ctl_MIN        (0)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_xover_mindelay_ctl_MAX        (3) // 0x00000003
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_xover_mindelay_ctl_DEF        (0x00000000)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_xover_mindelay_ctl_HSH        (0x02132708)

  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cmd_eq_strengh_OFF            (21)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cmd_eq_strengh_WID            ( 4)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cmd_eq_strengh_MSK            (0x01E00000)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cmd_eq_strengh_MIN            (0)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cmd_eq_strengh_MAX            (15) // 0x0000000F
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cmd_eq_strengh_DEF            (0x0000000F)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cmd_eq_strengh_HSH            (0x04152708)

  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cmd_eq_en_OFF                 (25)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cmd_eq_en_WID                 ( 1)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cmd_eq_en_MSK                 (0x02000000)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cmd_eq_en_MIN                 (0)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cmd_eq_en_MAX                 (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cmd_eq_en_DEF                 (0x00000000)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cmd_eq_en_HSH                 (0x01192708)

  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cmd_eq_constz_OFF             (26)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cmd_eq_constz_WID             ( 1)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cmd_eq_constz_MSK             (0x04000000)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cmd_eq_constz_MIN             (0)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cmd_eq_constz_MAX             (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cmd_eq_constz_DEF             (0x00000001)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_cmd_eq_constz_HSH             (0x011A2708)

  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_CkeCriClkGateEnGvBlock_OFF    (27)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_CkeCriClkGateEnGvBlock_WID    ( 1)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_CkeCriClkGateEnGvBlock_MSK    (0x08000000)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_CkeCriClkGateEnGvBlock_MIN    (0)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_CkeCriClkGateEnGvBlock_MAX    (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_CkeCriClkGateEnGvBlock_DEF    (0x00000000)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_CkeCriClkGateEnGvBlock_HSH    (0x011B2708)

  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_Spare_OFF                     (28)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_Spare_WID                     ( 4)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_Spare_MSK                     (0xF0000000)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_Spare_MIN                     (0)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_Spare_MAX                     (15) // 0x0000000F
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_Spare_DEF                     (0x00000000)
  #define DDRCKECH1_CR_DDRCRCKERANKSUSED_Spare_HSH                     (0x041C2708)

#define DDRCKECH1_CR_DDRCRCTLCOMP_REG                                  (0x00002710)

  #define DDRCKECH1_CR_DDRCRCTLCOMP_Scomp_OFF                          ( 0)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_Scomp_WID                          ( 6)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_Scomp_MSK                          (0x0000003F)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_Scomp_MIN                          (0)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_Scomp_MAX                          (63) // 0x0000003F
  #define DDRCKECH1_CR_DDRCRCTLCOMP_Scomp_DEF                          (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_Scomp_HSH                          (0x06002710)

  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvUp_OFF                     ( 6)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvUp_WID                     ( 6)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvUp_MSK                     (0x00000FC0)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvUp_MIN                     (0)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvUp_MAX                     (63) // 0x0000003F
  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvUp_DEF                     (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvUp_HSH                     (0x06062710)

  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvDown_OFF                   (12)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvDown_WID                   ( 6)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvDown_MSK                   (0x0003F000)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvDown_MIN                   (0)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvDown_MAX                   (63) // 0x0000003F
  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvDown_DEF                   (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_RcompDrvDown_HSH                   (0x060C2710)

  #define DDRCKECH1_CR_DDRCRCTLCOMP_Spare_OFF                          (18)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_Spare_WID                          (14)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_Spare_MSK                          (0xFFFC0000)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_Spare_MIN                          (0)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_Spare_MAX                          (16383) // 0x00003FFF
  #define DDRCKECH1_CR_DDRCRCTLCOMP_Spare_DEF                          (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCOMP_Spare_HSH                          (0x0E122710)

#define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_REG                            (0x00002714)

  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_OFF              ( 0)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_WID              ( 5)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MSK              (0x0000001F)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MIN              (-16)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_MAX              (15) // 0x0000000F
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_DEF              (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_ScompOffset_HSH              (0x85002714)

  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_OFF         ( 5)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_WID         ( 4)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MSK         (0x000001E0)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MIN         (-8)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_MAX         (7) // 0x00000007
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_DEF         (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_HSH         (0x84052714)

  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_OFF       ( 9)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_WID       ( 4)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MSK       (0x00001E00)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MIN       (-8)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_MAX       (7) // 0x00000007
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_DEF       (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_HSH       (0x84092714)

  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_Spare_OFF                    (13)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_Spare_WID                    (19)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_Spare_MSK                    (0xFFFFE000)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_Spare_MIN                    (0)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_Spare_MAX                    (524287) // 0x0007FFFF
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_Spare_DEF                    (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_Spare_HSH                    (0x130D2714)

#define DDRCKECH1_CR_DDRCRCTLPICODING_REG                              (0x00002718)

  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode0_OFF                 ( 0)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode0_WID                 ( 7)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode0_MSK                 (0x0000007F)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode0_MIN                 (0)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode0_MAX                 (127) // 0x0000007F
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode0_DEF                 (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode0_HSH                 (0x07002718)

  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode1_OFF                 ( 7)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode1_WID                 ( 7)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode1_MSK                 (0x00003F80)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode1_MIN                 (0)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode1_MAX                 (127) // 0x0000007F
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode1_DEF                 (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode1_HSH                 (0x07072718)

  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode2_OFF                 (14)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode2_WID                 ( 7)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode2_MSK                 (0x001FC000)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode2_MIN                 (0)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode2_MAX                 (127) // 0x0000007F
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode2_DEF                 (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode2_HSH                 (0x070E2718)

  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode3_OFF                 (21)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode3_WID                 ( 7)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode3_MSK                 (0x0FE00000)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode3_MIN                 (0)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode3_MAX                 (127) // 0x0000007F
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode3_DEF                 (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlPiCode3_HSH                 (0x07152718)

  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlXoverEnable_OFF             (28)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlXoverEnable_WID             ( 1)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlXoverEnable_MSK             (0x10000000)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlXoverEnable_MIN             (0)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlXoverEnable_MAX             (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlXoverEnable_DEF             (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_CtlXoverEnable_HSH             (0x011C2718)

  #define DDRCKECH1_CR_DDRCRCTLPICODING_Spare_OFF                      (29)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_Spare_WID                      ( 3)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_Spare_MSK                      (0xE0000000)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_Spare_MIN                      (0)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_Spare_MAX                      (7) // 0x00000007
  #define DDRCKECH1_CR_DDRCRCTLPICODING_Spare_DEF                      (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLPICODING_Spare_HSH                      (0x031D2718)

#define DDRCKECH1_CR_DDRCRCTLCONTROLS_REG                              (0x0000271C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RefPi_OFF                      ( 0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RefPi_WID                      ( 4)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RefPi_MSK                      (0x0000000F)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RefPi_MIN                      (-8)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RefPi_MAX                      (7) // 0x00000007
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RefPi_DEF                      (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RefPi_HSH                      (0x8400271C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllMask_OFF                    ( 4)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllMask_WID                    ( 2)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllMask_MSK                    (0x00000030)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllMask_MIN                    (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllMask_MAX                    (3) // 0x00000003
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllMask_DEF                    (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllMask_HSH                    (0x0204271C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_OFF             ( 6)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_WID             ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_MSK             (0x00000040)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_MIN             (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_MAX             (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_DEF             (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_ClkGateDisable_HSH             (0x0106271C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_TxOn_OFF                       ( 7)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_TxOn_WID                       ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_TxOn_MSK                       (0x00000080)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_TxOn_MIN                       (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_TxOn_MAX                       (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_TxOn_DEF                       (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_TxOn_HSH                       (0x0107271C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IntClkOn_OFF                   ( 8)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IntClkOn_WID                   ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IntClkOn_MSK                   (0x00000100)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IntClkOn_MIN                   (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IntClkOn_MAX                   (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IntClkOn_DEF                   (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IntClkOn_HSH                   (0x0108271C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RepClkOn_OFF                   ( 9)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RepClkOn_WID                   ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RepClkOn_MSK                   (0x00000200)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RepClkOn_MIN                   (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RepClkOn_MAX                   (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RepClkOn_DEF                   (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RepClkOn_HSH                   (0x0109271C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_OFF                 (10)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_WID                 ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_MSK                 (0x00000400)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_MIN                 (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_MAX                 (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_DEF                 (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IolbOrMisr_HSH                 (0x010A271C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IOLBHold_OFF                   (11)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IOLBHold_WID                   ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IOLBHold_MSK                   (0x00000800)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IOLBHold_MIN                   (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IOLBHold_MAX                   (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IOLBHold_DEF                   (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_IOLBHold_HSH                   (0x010B271C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_OdtMode_OFF                    (12)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_OdtMode_WID                    ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_OdtMode_MSK                    (0x00001000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_OdtMode_MIN                    (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_OdtMode_MAX                    (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_OdtMode_DEF                    (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_OdtMode_HSH                    (0x010C271C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CmdTxEq_OFF                    (13)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CmdTxEq_WID                    ( 2)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CmdTxEq_MSK                    (0x00006000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CmdTxEq_MIN                    (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CmdTxEq_MAX                    (3) // 0x00000003
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CmdTxEq_DEF                    (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CmdTxEq_HSH                    (0x020D271C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_OFF             (15)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_WID             ( 2)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MSK             (0x00018000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MIN             (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_MAX             (3) // 0x00000003
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_DEF             (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_EarlyWeakDrive_HSH             (0x020F271C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlTxEq_OFF                    (17)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlTxEq_WID                    ( 2)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlTxEq_MSK                    (0x00060000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlTxEq_MIN                    (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlTxEq_MAX                    (3) // 0x00000003
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlTxEq_DEF                    (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlTxEq_HSH                    (0x0211271C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_OFF                   (19)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_WID                   ( 2)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_MSK                   (0x00180000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_MIN                   (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_MAX                   (3) // 0x00000003
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_DEF                   (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CtlSRDrv_HSH                   (0x0213271C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RxVref_OFF                     (21)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RxVref_WID                     ( 6)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RxVref_MSK                     (0x07E00000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RxVref_MIN                     (-32)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RxVref_MAX                     (31) // 0x0000001F
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RxVref_DEF                     (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_RxVref_HSH                     (0x8615271C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_VccddqHi_OFF                   (27)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_VccddqHi_WID                   ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_VccddqHi_MSK                   (0x08000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_VccddqHi_MIN                   (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_VccddqHi_MAX                   (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_VccddqHi_DEF                   (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_VccddqHi_HSH                   (0x011B271C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllWeakLock_OFF                (28)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllWeakLock_WID                ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllWeakLock_MSK                (0x10000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllWeakLock_MIN                (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllWeakLock_MAX                (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllWeakLock_DEF                (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_DllWeakLock_HSH                (0x011C271C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CMD_Rate_OFF                   (29)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CMD_Rate_WID                   ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CMD_Rate_MSK                   (0x20000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CMD_Rate_MIN                   (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CMD_Rate_MAX                   (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CMD_Rate_DEF                   (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_CMD_Rate_HSH                   (0x011D271C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_OFF                (30)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_WID                ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MSK                (0x40000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MIN                (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_MAX                (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_DEF                (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_LaDrvEnOvrd_HSH                (0x011E271C)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_ma3_ma4_par_dis_OFF            (31)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_ma3_ma4_par_dis_WID            ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_ma3_ma4_par_dis_MSK            (0x80000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_ma3_ma4_par_dis_MIN            (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_ma3_ma4_par_dis_MAX            (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_ma3_ma4_par_dis_DEF            (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS_ma3_ma4_par_dis_HSH            (0x011F271C)

#define DDRCKECH1_CR_DDRCRCTLCONTROLS1_REG                             (0x00002720)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_RxVref_OFF                    ( 0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_RxVref_WID                    ( 8)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_RxVref_MSK                    (0x000000FF)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_RxVref_MIN                    (-128)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_RxVref_MAX                    (127) // 0x0000007F
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_RxVref_DEF                    (0x00000060)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_RxVref_HSH                    (0x88002720)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_MapCkeForScOdt_OFF            ( 8)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_MapCkeForScOdt_WID            (18)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_MapCkeForScOdt_MSK            (0x03FFFF00)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_MapCkeForScOdt_MIN            (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_MapCkeForScOdt_MAX            (262143) // 0x0003FFFF
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_MapCkeForScOdt_DEF            (0x00010458)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_MapCkeForScOdt_HSH            (0x12082720)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CMDLowsupEn_OFF               (26)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CMDLowsupEn_WID               ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CMDLowsupEn_MSK               (0x04000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CMDLowsupEn_MIN               (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CMDLowsupEn_MAX               (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CMDLowsupEn_DEF               (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CMDLowsupEn_HSH               (0x011A2720)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CKELowsupEn_OFF               (27)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CKELowsupEn_WID               ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CKELowsupEn_MSK               (0x08000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CKELowsupEn_MIN               (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CKELowsupEn_MAX               (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CKELowsupEn_DEF               (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CKELowsupEn_HSH               (0x011B2720)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CTLLowsupEn_OFF               (28)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CTLLowsupEn_WID               ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CTLLowsupEn_MSK               (0x10000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CTLLowsupEn_MIN               (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CTLLowsupEn_MAX               (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CTLLowsupEn_DEF               (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CTLLowsupEn_HSH               (0x011C2720)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CLKLowsupEn_OFF               (29)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CLKLowsupEn_WID               ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CLKLowsupEn_MSK               (0x20000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CLKLowsupEn_MIN               (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CLKLowsupEn_MAX               (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CLKLowsupEn_DEF               (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_CLKLowsupEn_HSH               (0x011D2720)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_en_sr_mode_to_cke_OFF         (30)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_en_sr_mode_to_cke_WID         ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_en_sr_mode_to_cke_MSK         (0x40000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_en_sr_mode_to_cke_MIN         (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_en_sr_mode_to_cke_MAX         (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_en_sr_mode_to_cke_DEF         (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_en_sr_mode_to_cke_HSH         (0x011E2720)

  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_c3segsel_b_for_cke_OFF        (31)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_c3segsel_b_for_cke_WID        ( 1)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_c3segsel_b_for_cke_MSK        (0x80000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_c3segsel_b_for_cke_MIN        (0)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_c3segsel_b_for_cke_MAX        (1) // 0x00000001
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_c3segsel_b_for_cke_DEF        (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLCONTROLS1_c3segsel_b_for_cke_HSH        (0x011F2720)

#define DDRCKECH1_CR_DDRCRLOOPBACKFEEDBACK_REG                         (0x00002724)

  #define DDRCKECH1_CR_DDRCRLOOPBACKFEEDBACK_datatrainfeedback_OFF     ( 0)
  #define DDRCKECH1_CR_DDRCRLOOPBACKFEEDBACK_datatrainfeedback_WID     (10)
  #define DDRCKECH1_CR_DDRCRLOOPBACKFEEDBACK_datatrainfeedback_MSK     (0x000003FF)
  #define DDRCKECH1_CR_DDRCRLOOPBACKFEEDBACK_datatrainfeedback_MIN     (0)
  #define DDRCKECH1_CR_DDRCRLOOPBACKFEEDBACK_datatrainfeedback_MAX     (1023) // 0x000003FF
  #define DDRCKECH1_CR_DDRCRLOOPBACKFEEDBACK_datatrainfeedback_DEF     (0x00000000)
  #define DDRCKECH1_CR_DDRCRLOOPBACKFEEDBACK_datatrainfeedback_HSH     (0x0A002724)

  #define DDRCKECH1_CR_DDRCRLOOPBACKFEEDBACK_Spare_OFF                 (10)
  #define DDRCKECH1_CR_DDRCRLOOPBACKFEEDBACK_Spare_WID                 (22)
  #define DDRCKECH1_CR_DDRCRLOOPBACKFEEDBACK_Spare_MSK                 (0xFFFFFC00)
  #define DDRCKECH1_CR_DDRCRLOOPBACKFEEDBACK_Spare_MIN                 (0)
  #define DDRCKECH1_CR_DDRCRLOOPBACKFEEDBACK_Spare_MAX                 (4194303) // 0x003FFFFF
  #define DDRCKECH1_CR_DDRCRLOOPBACKFEEDBACK_Spare_DEF                 (0x00000000)
  #define DDRCKECH1_CR_DDRCRLOOPBACKFEEDBACK_Spare_HSH                 (0x160A2724)

#define DDRCKECH1_CR_DDRCRCTLTCOCONTROL0_REG                           (0x00002728)

  #define DDRCKECH1_CR_DDRCRCTLTCOCONTROL0_CtlTcoComp_OFF              ( 0)
  #define DDRCKECH1_CR_DDRCRCTLTCOCONTROL0_CtlTcoComp_WID              ( 6)
  #define DDRCKECH1_CR_DDRCRCTLTCOCONTROL0_CtlTcoComp_MSK              (0x0000003F)
  #define DDRCKECH1_CR_DDRCRCTLTCOCONTROL0_CtlTcoComp_MIN              (0)
  #define DDRCKECH1_CR_DDRCRCTLTCOCONTROL0_CtlTcoComp_MAX              (63) // 0x0000003F
  #define DDRCKECH1_CR_DDRCRCTLTCOCONTROL0_CtlTcoComp_DEF              (0x00000020)
  #define DDRCKECH1_CR_DDRCRCTLTCOCONTROL0_CtlTcoComp_HSH              (0x06002728)

  #define DDRCKECH1_CR_DDRCRCTLTCOCONTROL0_Spare_OFF                   ( 6)
  #define DDRCKECH1_CR_DDRCRCTLTCOCONTROL0_Spare_WID                   (26)
  #define DDRCKECH1_CR_DDRCRCTLTCOCONTROL0_Spare_MSK                   (0xFFFFFFC0)
  #define DDRCKECH1_CR_DDRCRCTLTCOCONTROL0_Spare_MIN                   (0)
  #define DDRCKECH1_CR_DDRCRCTLTCOCONTROL0_Spare_MAX                   (67108863) // 0x03FFFFFF
  #define DDRCKECH1_CR_DDRCRCTLTCOCONTROL0_Spare_DEF                   (0x00000000)
  #define DDRCKECH1_CR_DDRCRCTLTCOCONTROL0_Spare_HSH                   (0x1A062728)

#define DDRCKECH1_CR_DDRCRCMDTCOCONTROL0_REG                           (0x0000272C)

  #define DDRCKECH1_CR_DDRCRCMDTCOCONTROL0_CmdTcoComp_OFF              ( 0)
  #define DDRCKECH1_CR_DDRCRCMDTCOCONTROL0_CmdTcoComp_WID              ( 6)
  #define DDRCKECH1_CR_DDRCRCMDTCOCONTROL0_CmdTcoComp_MSK              (0x0000003F)
  #define DDRCKECH1_CR_DDRCRCMDTCOCONTROL0_CmdTcoComp_MIN              (0)
  #define DDRCKECH1_CR_DDRCRCMDTCOCONTROL0_CmdTcoComp_MAX              (63) // 0x0000003F
  #define DDRCKECH1_CR_DDRCRCMDTCOCONTROL0_CmdTcoComp_DEF              (0x00000020)
  #define DDRCKECH1_CR_DDRCRCMDTCOCONTROL0_CmdTcoComp_HSH              (0x0600272C)

  #define DDRCKECH1_CR_DDRCRCMDTCOCONTROL0_Spare_OFF                   ( 6)
  #define DDRCKECH1_CR_DDRCRCMDTCOCONTROL0_Spare_WID                   (26)
  #define DDRCKECH1_CR_DDRCRCMDTCOCONTROL0_Spare_MSK                   (0xFFFFFFC0)
  #define DDRCKECH1_CR_DDRCRCMDTCOCONTROL0_Spare_MIN                   (0)
  #define DDRCKECH1_CR_DDRCRCMDTCOCONTROL0_Spare_MAX                   (67108863) // 0x03FFFFFF
  #define DDRCKECH1_CR_DDRCRCMDTCOCONTROL0_Spare_DEF                   (0x00000000)
  #define DDRCKECH1_CR_DDRCRCMDTCOCONTROL0_Spare_HSH                   (0x1A06272C)

#define DDRVREF_CR_DDRRCOMPDATA_REG                                    (0x00002800)

  #define DDRVREF_CR_DDRRCOMPDATA_VTComp_OFF                           ( 0)
  #define DDRVREF_CR_DDRRCOMPDATA_VTComp_WID                           ( 6)
  #define DDRVREF_CR_DDRRCOMPDATA_VTComp_MSK                           (0x0000003F)
  #define DDRVREF_CR_DDRRCOMPDATA_VTComp_MIN                           (0)
  #define DDRVREF_CR_DDRRCOMPDATA_VTComp_MAX                           (63) // 0x0000003F
  #define DDRVREF_CR_DDRRCOMPDATA_VTComp_DEF                           (0x00000000)
  #define DDRVREF_CR_DDRRCOMPDATA_VTComp_HSH                           (0x06002800)

  #define DDRVREF_CR_DDRRCOMPDATA_NxtVTCompValidForDcc_OFF             ( 6)
  #define DDRVREF_CR_DDRRCOMPDATA_NxtVTCompValidForDcc_WID             ( 1)
  #define DDRVREF_CR_DDRRCOMPDATA_NxtVTCompValidForDcc_MSK             (0x00000040)
  #define DDRVREF_CR_DDRRCOMPDATA_NxtVTCompValidForDcc_MIN             (0)
  #define DDRVREF_CR_DDRRCOMPDATA_NxtVTCompValidForDcc_MAX             (1) // 0x00000001
  #define DDRVREF_CR_DDRRCOMPDATA_NxtVTCompValidForDcc_DEF             (0x00000000)
  #define DDRVREF_CR_DDRRCOMPDATA_NxtVTCompValidForDcc_HSH             (0x01062800)

  #define DDRVREF_CR_DDRRCOMPDATA_CompLoopsNumForDcc_OFF               ( 7)
  #define DDRVREF_CR_DDRRCOMPDATA_CompLoopsNumForDcc_WID               ( 5)
  #define DDRVREF_CR_DDRRCOMPDATA_CompLoopsNumForDcc_MSK               (0x00000F80)
  #define DDRVREF_CR_DDRRCOMPDATA_CompLoopsNumForDcc_MIN               (0)
  #define DDRVREF_CR_DDRRCOMPDATA_CompLoopsNumForDcc_MAX               (31) // 0x0000001F
  #define DDRVREF_CR_DDRRCOMPDATA_CompLoopsNumForDcc_DEF               (0x00000001)
  #define DDRVREF_CR_DDRRCOMPDATA_CompLoopsNumForDcc_HSH               (0x05072800)

  #define DDRVREF_CR_DDRRCOMPDATA_ActivateCompLoopsCntForDcc_OFF       (12)
  #define DDRVREF_CR_DDRRCOMPDATA_ActivateCompLoopsCntForDcc_WID       ( 1)
  #define DDRVREF_CR_DDRRCOMPDATA_ActivateCompLoopsCntForDcc_MSK       (0x00001000)
  #define DDRVREF_CR_DDRRCOMPDATA_ActivateCompLoopsCntForDcc_MIN       (0)
  #define DDRVREF_CR_DDRRCOMPDATA_ActivateCompLoopsCntForDcc_MAX       (1) // 0x00000001
  #define DDRVREF_CR_DDRRCOMPDATA_ActivateCompLoopsCntForDcc_DEF       (0x00000000)
  #define DDRVREF_CR_DDRRCOMPDATA_ActivateCompLoopsCntForDcc_HSH       (0x010C2800)

  #define DDRVREF_CR_DDRRCOMPDATA_KfactorForDccVtCompOffsetCalc_OFF    (13)
  #define DDRVREF_CR_DDRRCOMPDATA_KfactorForDccVtCompOffsetCalc_WID    ( 2)
  #define DDRVREF_CR_DDRRCOMPDATA_KfactorForDccVtCompOffsetCalc_MSK    (0x00006000)
  #define DDRVREF_CR_DDRRCOMPDATA_KfactorForDccVtCompOffsetCalc_MIN    (0)
  #define DDRVREF_CR_DDRRCOMPDATA_KfactorForDccVtCompOffsetCalc_MAX    (3) // 0x00000003
  #define DDRVREF_CR_DDRRCOMPDATA_KfactorForDccVtCompOffsetCalc_DEF    (0x00000000)
  #define DDRVREF_CR_DDRRCOMPDATA_KfactorForDccVtCompOffsetCalc_HSH    (0x020D2800)

  #define DDRVREF_CR_DDRRCOMPDATA_Spare_OFF                            (15)
  #define DDRVREF_CR_DDRRCOMPDATA_Spare_WID                            (17)
  #define DDRVREF_CR_DDRRCOMPDATA_Spare_MSK                            (0xFFFF8000)
  #define DDRVREF_CR_DDRRCOMPDATA_Spare_MIN                            (0)
  #define DDRVREF_CR_DDRRCOMPDATA_Spare_MAX                            (131071) // 0x0001FFFF
  #define DDRVREF_CR_DDRRCOMPDATA_Spare_DEF                            (0x00000000)
  #define DDRVREF_CR_DDRRCOMPDATA_Spare_HSH                            (0x110F2800)

#define DDRVREF_CR_DDRCRVREFCONTROL_REG                                (0x00002804)

  #define DDRVREF_CR_DDRCRVREFCONTROL_HiBWDivider_OFF                  ( 0)
  #define DDRVREF_CR_DDRCRVREFCONTROL_HiBWDivider_WID                  ( 2)
  #define DDRVREF_CR_DDRCRVREFCONTROL_HiBWDivider_MSK                  (0x00000003)
  #define DDRVREF_CR_DDRCRVREFCONTROL_HiBWDivider_MIN                  (0)
  #define DDRVREF_CR_DDRCRVREFCONTROL_HiBWDivider_MAX                  (3) // 0x00000003
  #define DDRVREF_CR_DDRCRVREFCONTROL_HiBWDivider_DEF                  (0x00000002)
  #define DDRVREF_CR_DDRCRVREFCONTROL_HiBWDivider_HSH                  (0x02002804)

  #define DDRVREF_CR_DDRCRVREFCONTROL_LoBWDivider_OFF                  ( 2)
  #define DDRVREF_CR_DDRCRVREFCONTROL_LoBWDivider_WID                  ( 2)
  #define DDRVREF_CR_DDRCRVREFCONTROL_LoBWDivider_MSK                  (0x0000000C)
  #define DDRVREF_CR_DDRCRVREFCONTROL_LoBWDivider_MIN                  (0)
  #define DDRVREF_CR_DDRCRVREFCONTROL_LoBWDivider_MAX                  (3) // 0x00000003
  #define DDRVREF_CR_DDRCRVREFCONTROL_LoBWDivider_DEF                  (0x00000002)
  #define DDRVREF_CR_DDRCRVREFCONTROL_LoBWDivider_HSH                  (0x02022804)

  #define DDRVREF_CR_DDRCRVREFCONTROL_SampleDivider_OFF                ( 4)
  #define DDRVREF_CR_DDRCRVREFCONTROL_SampleDivider_WID                ( 3)
  #define DDRVREF_CR_DDRCRVREFCONTROL_SampleDivider_MSK                (0x00000070)
  #define DDRVREF_CR_DDRCRVREFCONTROL_SampleDivider_MIN                (0)
  #define DDRVREF_CR_DDRCRVREFCONTROL_SampleDivider_MAX                (7) // 0x00000007
  #define DDRVREF_CR_DDRCRVREFCONTROL_SampleDivider_DEF                (0x00000003)
  #define DDRVREF_CR_DDRCRVREFCONTROL_SampleDivider_HSH                (0x03042804)

  #define DDRVREF_CR_DDRCRVREFCONTROL_OpenLoop_OFF                     ( 7)
  #define DDRVREF_CR_DDRCRVREFCONTROL_OpenLoop_WID                     ( 1)
  #define DDRVREF_CR_DDRCRVREFCONTROL_OpenLoop_MSK                     (0x00000080)
  #define DDRVREF_CR_DDRCRVREFCONTROL_OpenLoop_MIN                     (0)
  #define DDRVREF_CR_DDRCRVREFCONTROL_OpenLoop_MAX                     (1) // 0x00000001
  #define DDRVREF_CR_DDRCRVREFCONTROL_OpenLoop_DEF                     (0x00000000)
  #define DDRVREF_CR_DDRCRVREFCONTROL_OpenLoop_HSH                     (0x01072804)

  #define DDRVREF_CR_DDRCRVREFCONTROL_SlowBWError_OFF                  ( 8)
  #define DDRVREF_CR_DDRCRVREFCONTROL_SlowBWError_WID                  ( 2)
  #define DDRVREF_CR_DDRCRVREFCONTROL_SlowBWError_MSK                  (0x00000300)
  #define DDRVREF_CR_DDRCRVREFCONTROL_SlowBWError_MIN                  (0)
  #define DDRVREF_CR_DDRCRVREFCONTROL_SlowBWError_MAX                  (3) // 0x00000003
  #define DDRVREF_CR_DDRCRVREFCONTROL_SlowBWError_DEF                  (0x00000001)
  #define DDRVREF_CR_DDRCRVREFCONTROL_SlowBWError_HSH                  (0x02082804)

  #define DDRVREF_CR_DDRCRVREFCONTROL_HiBWEnable_OFF                   (10)
  #define DDRVREF_CR_DDRCRVREFCONTROL_HiBWEnable_WID                   ( 1)
  #define DDRVREF_CR_DDRCRVREFCONTROL_HiBWEnable_MSK                   (0x00000400)
  #define DDRVREF_CR_DDRCRVREFCONTROL_HiBWEnable_MIN                   (0)
  #define DDRVREF_CR_DDRCRVREFCONTROL_HiBWEnable_MAX                   (1) // 0x00000001
  #define DDRVREF_CR_DDRCRVREFCONTROL_HiBWEnable_DEF                   (0x00000001)
  #define DDRVREF_CR_DDRCRVREFCONTROL_HiBWEnable_HSH                   (0x010A2804)

  #define DDRVREF_CR_DDRCRVREFCONTROL_VtSlopeB_OFF                     (11)
  #define DDRVREF_CR_DDRCRVREFCONTROL_VtSlopeB_WID                     ( 3)
  #define DDRVREF_CR_DDRCRVREFCONTROL_VtSlopeB_MSK                     (0x00003800)
  #define DDRVREF_CR_DDRCRVREFCONTROL_VtSlopeB_MIN                     (0)
  #define DDRVREF_CR_DDRCRVREFCONTROL_VtSlopeB_MAX                     (7) // 0x00000007
  #define DDRVREF_CR_DDRCRVREFCONTROL_VtSlopeB_DEF                     (0x00000004)
  #define DDRVREF_CR_DDRCRVREFCONTROL_VtSlopeB_HSH                     (0x030B2804)

  #define DDRVREF_CR_DDRCRVREFCONTROL_VtSlopeA_OFF                     (14)
  #define DDRVREF_CR_DDRCRVREFCONTROL_VtSlopeA_WID                     ( 3)
  #define DDRVREF_CR_DDRCRVREFCONTROL_VtSlopeA_MSK                     (0x0001C000)
  #define DDRVREF_CR_DDRCRVREFCONTROL_VtSlopeA_MIN                     (0)
  #define DDRVREF_CR_DDRCRVREFCONTROL_VtSlopeA_MAX                     (7) // 0x00000007
  #define DDRVREF_CR_DDRCRVREFCONTROL_VtSlopeA_DEF                     (0x00000004)
  #define DDRVREF_CR_DDRCRVREFCONTROL_VtSlopeA_HSH                     (0x030E2804)

  #define DDRVREF_CR_DDRCRVREFCONTROL_VtOffset_OFF                     (17)
  #define DDRVREF_CR_DDRCRVREFCONTROL_VtOffset_WID                     ( 4)
  #define DDRVREF_CR_DDRCRVREFCONTROL_VtOffset_MSK                     (0x001E0000)
  #define DDRVREF_CR_DDRCRVREFCONTROL_VtOffset_MIN                     (0)
  #define DDRVREF_CR_DDRCRVREFCONTROL_VtOffset_MAX                     (15) // 0x0000000F
  #define DDRVREF_CR_DDRCRVREFCONTROL_VtOffset_DEF                     (0x00000003)
  #define DDRVREF_CR_DDRCRVREFCONTROL_VtOffset_HSH                     (0x04112804)

  #define DDRVREF_CR_DDRCRVREFCONTROL_SelCode_OFF                      (21)
  #define DDRVREF_CR_DDRCRVREFCONTROL_SelCode_WID                      ( 3)
  #define DDRVREF_CR_DDRCRVREFCONTROL_SelCode_MSK                      (0x00E00000)
  #define DDRVREF_CR_DDRCRVREFCONTROL_SelCode_MIN                      (0)
  #define DDRVREF_CR_DDRCRVREFCONTROL_SelCode_MAX                      (7) // 0x00000007
  #define DDRVREF_CR_DDRCRVREFCONTROL_SelCode_DEF                      (0x00000000)
  #define DDRVREF_CR_DDRCRVREFCONTROL_SelCode_HSH                      (0x03152804)

  #define DDRVREF_CR_DDRCRVREFCONTROL_OutputCode_OFF                   (24)
  #define DDRVREF_CR_DDRCRVREFCONTROL_OutputCode_WID                   ( 8)
  #define DDRVREF_CR_DDRCRVREFCONTROL_OutputCode_MSK                   (0xFF000000)
  #define DDRVREF_CR_DDRCRVREFCONTROL_OutputCode_MIN                   (0)
  #define DDRVREF_CR_DDRCRVREFCONTROL_OutputCode_MAX                   (255) // 0x000000FF
  #define DDRVREF_CR_DDRCRVREFCONTROL_OutputCode_DEF                   (0x00000000)
  #define DDRVREF_CR_DDRCRVREFCONTROL_OutputCode_HSH                   (0x08182804)

#define DDRVREF_CR_DDRCRVREFADJUST1_REG                                (0x00002808)

  #define DDRVREF_CR_DDRCRVREFADJUST1_CAVrefIntCtl_OFF_A0                 ( 0)
  #define DDRVREF_CR_DDRCRVREFADJUST1_CAVrefIntCtl_WID_A0                 ( 9)
  #define DDRVREF_CR_DDRCRVREFADJUST1_CAVrefIntCtl_MSK_A0                 (0x000001FF)
  #define DDRVREF_CR_DDRCRVREFADJUST1_CAVrefIntCtl_MIN_A0                 (0)
  #define DDRVREF_CR_DDRCRVREFADJUST1_CAVrefIntCtl_MAX_A0                 (511) // 0x000001FF
  #define DDRVREF_CR_DDRCRVREFADJUST1_CAVrefIntCtl_DEF_A0                 (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST1_CAVrefIntCtl_HSH_A0                 (0x09002808)

  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch1VrefIntCtl_OFF_A0                ( 9)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch1VrefIntCtl_WID_A0                ( 9)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch1VrefIntCtl_MSK_A0                (0x0003FE00)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch1VrefIntCtl_MIN_A0                (0)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch1VrefIntCtl_MAX_A0                (511) // 0x000001FF
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch1VrefIntCtl_DEF_A0                (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch1VrefIntCtl_HSH_A0                (0x09092808)

  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0VrefIntCtl_OFF_A0                (18)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0VrefIntCtl_WID_A0                ( 9)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0VrefIntCtl_MSK_A0                (0x07FC0000)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0VrefIntCtl_MIN_A0                (0)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0VrefIntCtl_MAX_A0                (511) // 0x000001FF
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0VrefIntCtl_DEF_A0                (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0VrefIntCtl_HSH_A0                (0x09122808)

  #define DDRVREF_CR_DDRCRVREFADJUST1_EnDimmVrefCA_OFF_A0                 (27)
  #define DDRVREF_CR_DDRCRVREFADJUST1_EnDimmVrefCA_WID_A0                 ( 1)
  #define DDRVREF_CR_DDRCRVREFADJUST1_EnDimmVrefCA_MSK_A0                 (0x08000000)
  #define DDRVREF_CR_DDRCRVREFADJUST1_EnDimmVrefCA_MIN_A0                 (0)
  #define DDRVREF_CR_DDRCRVREFADJUST1_EnDimmVrefCA_MAX_A0                 (1) // 0x00000001
  #define DDRVREF_CR_DDRCRVREFADJUST1_EnDimmVrefCA_DEF_A0                 (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST1_EnDimmVrefCA_HSH_A0                 (0x011B2808)

  #define DDRVREF_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_OFF_A0                (28)
  #define DDRVREF_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_WID_A0                ( 1)
  #define DDRVREF_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_MSK_A0                (0x10000000)
  #define DDRVREF_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_MIN_A0                (0)
  #define DDRVREF_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_MAX_A0                (1) // 0x00000001
  #define DDRVREF_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_DEF_A0                (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST1_EnDimmVrefCh1_HSH_A0                (0x011C2808)

  #define DDRVREF_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_OFF_A0                (29)
  #define DDRVREF_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_WID_A0                ( 1)
  #define DDRVREF_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_MSK_A0                (0x20000000)
  #define DDRVREF_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_MIN_A0                (0)
  #define DDRVREF_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_MAX_A0                (1) // 0x00000001
  #define DDRVREF_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_DEF_A0                (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST1_EnDimmVrefCh0_HSH_A0                (0x011D2808)

  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm0CaVrefIntCtl_OFF         ( 0)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm0CaVrefIntCtl_WID         ( 9)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm0CaVrefIntCtl_MSK         (0x000001FF)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm0CaVrefIntCtl_MIN         (0)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm0CaVrefIntCtl_MAX         (511) // 0x000001FF
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm0CaVrefIntCtl_DEF         (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm0CaVrefIntCtl_HSH         (0x09002808)

  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch1Dimm0CaVrefIntCtl_OFF         ( 9)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch1Dimm0CaVrefIntCtl_WID         ( 9)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch1Dimm0CaVrefIntCtl_MSK         (0x0003FE00)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch1Dimm0CaVrefIntCtl_MIN         (0)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch1Dimm0CaVrefIntCtl_MAX         (511) // 0x000001FF
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch1Dimm0CaVrefIntCtl_DEF         (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch1Dimm0CaVrefIntCtl_HSH         (0x09092808)

  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm1CaVrefIntCtl_OFF         (18)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm1CaVrefIntCtl_WID         ( 9)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm1CaVrefIntCtl_MSK         (0x07FC0000)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm1CaVrefIntCtl_MIN         (0)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm1CaVrefIntCtl_MAX         (511) // 0x000001FF
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm1CaVrefIntCtl_DEF         (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm1CaVrefIntCtl_HSH         (0x09122808)

  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm0CaVrefEn_OFF             (27)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm0CaVrefEn_WID             ( 1)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm0CaVrefEn_MSK             (0x08000000)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm0CaVrefEn_MIN             (0)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm0CaVrefEn_MAX             (1) // 0x00000001
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm0CaVrefEn_DEF             (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm0CaVrefEn_HSH             (0x011B2808)

  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch1Dimm0CaVrefEn_OFF             (28)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch1Dimm0CaVrefEn_WID             ( 1)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch1Dimm0CaVrefEn_MSK             (0x10000000)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch1Dimm0CaVrefEn_MIN             (0)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch1Dimm0CaVrefEn_MAX             (1) // 0x00000001
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch1Dimm0CaVrefEn_DEF             (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch1Dimm0CaVrefEn_HSH             (0x011C2808)

  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm1CaVrefEn_OFF             (29)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm1CaVrefEn_WID             ( 1)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm1CaVrefEn_MSK             (0x20000000)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm1CaVrefEn_MIN             (0)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm1CaVrefEn_MAX             (1) // 0x00000001
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm1CaVrefEn_DEF             (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm1CaVrefEn_HSH             (0x011D2808)

  #define DDRVREF_CR_DDRCRVREFADJUST1_VrefDimmSagvSlowBWTargetCodeChange_OFF (30)
  #define DDRVREF_CR_DDRCRVREFADJUST1_VrefDimmSagvSlowBWTargetCodeChange_WID ( 1)
  #define DDRVREF_CR_DDRCRVREFADJUST1_VrefDimmSagvSlowBWTargetCodeChange_MSK (0x40000000)
  #define DDRVREF_CR_DDRCRVREFADJUST1_VrefDimmSagvSlowBWTargetCodeChange_MIN (0)
  #define DDRVREF_CR_DDRCRVREFADJUST1_VrefDimmSagvSlowBWTargetCodeChange_MAX (1) // 0x00000001
  #define DDRVREF_CR_DDRCRVREFADJUST1_VrefDimmSagvSlowBWTargetCodeChange_DEF (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST1_VrefDimmSagvSlowBWTargetCodeChange_HSH (0x011E2808)

  #define DDRVREF_CR_DDRCRVREFADJUST1_VrefDimmSagvAnalogEn_OFF         (31)
  #define DDRVREF_CR_DDRCRVREFADJUST1_VrefDimmSagvAnalogEn_WID         ( 1)
  #define DDRVREF_CR_DDRCRVREFADJUST1_VrefDimmSagvAnalogEn_MSK         (0x80000000)
  #define DDRVREF_CR_DDRCRVREFADJUST1_VrefDimmSagvAnalogEn_MIN         (0)
  #define DDRVREF_CR_DDRCRVREFADJUST1_VrefDimmSagvAnalogEn_MAX         (1) // 0x00000001
  #define DDRVREF_CR_DDRCRVREFADJUST1_VrefDimmSagvAnalogEn_DEF         (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST1_VrefDimmSagvAnalogEn_HSH         (0x011F2808)

#define DDRVREF_CR_DDRCRVREFADJUST2_REG                                (0x0000280C)

  #define DDRVREF_CR_DDRCRVREFADJUST2_HiZTimerCtrl_OFF                 ( 0)
  #define DDRVREF_CR_DDRCRVREFADJUST2_HiZTimerCtrl_WID                 ( 2)
  #define DDRVREF_CR_DDRCRVREFADJUST2_HiZTimerCtrl_MSK                 (0x00000003)
  #define DDRVREF_CR_DDRCRVREFADJUST2_HiZTimerCtrl_MIN                 (0)
  #define DDRVREF_CR_DDRCRVREFADJUST2_HiZTimerCtrl_MAX                 (3) // 0x00000003
  #define DDRVREF_CR_DDRCRVREFADJUST2_HiZTimerCtrl_DEF                 (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST2_HiZTimerCtrl_HSH                 (0x0200280C)

  #define DDRVREF_CR_DDRCRVREFADJUST2_caSlowBW_OFF_A0                     ( 2)
  #define DDRVREF_CR_DDRCRVREFADJUST2_caSlowBW_WID_A0                     ( 1)
  #define DDRVREF_CR_DDRCRVREFADJUST2_caSlowBW_MSK_A0                     (0x00000004)
  #define DDRVREF_CR_DDRCRVREFADJUST2_caSlowBW_MIN_A0                     (0)
  #define DDRVREF_CR_DDRCRVREFADJUST2_caSlowBW_MAX_A0                     (1) // 0x00000001
  #define DDRVREF_CR_DDRCRVREFADJUST2_caSlowBW_DEF_A0                     (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST2_caSlowBW_HSH_A0                     (0x0102280C)

  #define DDRVREF_CR_DDRCRVREFADJUST2_ch0SlowBW_OFF_A0                    ( 3)
  #define DDRVREF_CR_DDRCRVREFADJUST2_ch0SlowBW_WID_A0                    ( 1)
  #define DDRVREF_CR_DDRCRVREFADJUST2_ch0SlowBW_MSK_A0                    (0x00000008)
  #define DDRVREF_CR_DDRCRVREFADJUST2_ch0SlowBW_MIN_A0                    (0)
  #define DDRVREF_CR_DDRCRVREFADJUST2_ch0SlowBW_MAX_A0                    (1) // 0x00000001
  #define DDRVREF_CR_DDRCRVREFADJUST2_ch0SlowBW_DEF_A0                    (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST2_ch0SlowBW_HSH_A0                    (0x0103280C)

  #define DDRVREF_CR_DDRCRVREFADJUST2_ch1SlowBW_OFF_A0                    ( 4)
  #define DDRVREF_CR_DDRCRVREFADJUST2_ch1SlowBW_WID_A0                    ( 1)
  #define DDRVREF_CR_DDRCRVREFADJUST2_ch1SlowBW_MSK_A0                    (0x00000010)
  #define DDRVREF_CR_DDRCRVREFADJUST2_ch1SlowBW_MIN_A0                    (0)
  #define DDRVREF_CR_DDRCRVREFADJUST2_ch1SlowBW_MAX_A0                    (1) // 0x00000001
  #define DDRVREF_CR_DDRCRVREFADJUST2_ch1SlowBW_DEF_A0                    (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST2_ch1SlowBW_HSH_A0                    (0x0104280C)

  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh0Dimm0SlowBW_OFF             ( 2)
  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh0Dimm0SlowBW_WID             ( 1)
  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh0Dimm0SlowBW_MSK             (0x00000004)
  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh0Dimm0SlowBW_MIN             (0)
  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh0Dimm0SlowBW_MAX             (1) // 0x00000001
  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh0Dimm0SlowBW_DEF             (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh0Dimm0SlowBW_HSH             (0x0102280C)

  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh0Dimm1SlowBW_OFF             ( 3)
  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh0Dimm1SlowBW_WID             ( 1)
  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh0Dimm1SlowBW_MSK             (0x00000008)
  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh0Dimm1SlowBW_MIN             (0)
  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh0Dimm1SlowBW_MAX             (1) // 0x00000001
  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh0Dimm1SlowBW_DEF             (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh0Dimm1SlowBW_HSH             (0x0103280C)

  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh1Dimm0SlowBW_OFF             ( 4)
  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh1Dimm0SlowBW_WID             ( 1)
  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh1Dimm0SlowBW_MSK             (0x00000010)
  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh1Dimm0SlowBW_MIN             (0)
  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh1Dimm0SlowBW_MAX             (1) // 0x00000001
  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh1Dimm0SlowBW_DEF             (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh1Dimm0SlowBW_HSH             (0x0104280C)

  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh1Dimm1SlowBW_OFF             ( 5)
  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh1Dimm1SlowBW_WID             ( 1)
  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh1Dimm1SlowBW_MSK             (0x00000020)
  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh1Dimm1SlowBW_MIN             (0)
  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh1Dimm1SlowBW_MAX             (1) // 0x00000001
  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh1Dimm1SlowBW_DEF             (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST2_CaCh1Dimm1SlowBW_HSH             (0x0105280C)

  #define DDRVREF_CR_DDRCRVREFADJUST2_Rsvd_OFF                         ( 6)
  #define DDRVREF_CR_DDRCRVREFADJUST2_Rsvd_WID                         ( 7)
  #define DDRVREF_CR_DDRCRVREFADJUST2_Rsvd_MSK                         (0x00001FC0)
  #define DDRVREF_CR_DDRCRVREFADJUST2_Rsvd_MIN                         (0)
  #define DDRVREF_CR_DDRCRVREFADJUST2_Rsvd_MAX                         (127) // 0x0000007F
  #define DDRVREF_CR_DDRCRVREFADJUST2_Rsvd_DEF                         (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST2_Rsvd_HSH                         (0x0706280C)

  #define DDRVREF_CR_DDRCRVREFADJUST2_VtSlopeBOnSAGV_OFF               (13)
  #define DDRVREF_CR_DDRCRVREFADJUST2_VtSlopeBOnSAGV_WID               ( 3)
  #define DDRVREF_CR_DDRCRVREFADJUST2_VtSlopeBOnSAGV_MSK               (0x0000E000)
  #define DDRVREF_CR_DDRCRVREFADJUST2_VtSlopeBOnSAGV_MIN               (0)
  #define DDRVREF_CR_DDRCRVREFADJUST2_VtSlopeBOnSAGV_MAX               (7) // 0x00000007
  #define DDRVREF_CR_DDRCRVREFADJUST2_VtSlopeBOnSAGV_DEF               (0x00000004)
  #define DDRVREF_CR_DDRCRVREFADJUST2_VtSlopeBOnSAGV_HSH               (0x030D280C)

  #define DDRVREF_CR_DDRCRVREFADJUST2_VtSlopeAOnSAGV_OFF               (16)
  #define DDRVREF_CR_DDRCRVREFADJUST2_VtSlopeAOnSAGV_WID               ( 3)
  #define DDRVREF_CR_DDRCRVREFADJUST2_VtSlopeAOnSAGV_MSK               (0x00070000)
  #define DDRVREF_CR_DDRCRVREFADJUST2_VtSlopeAOnSAGV_MIN               (0)
  #define DDRVREF_CR_DDRCRVREFADJUST2_VtSlopeAOnSAGV_MAX               (7) // 0x00000007
  #define DDRVREF_CR_DDRCRVREFADJUST2_VtSlopeAOnSAGV_DEF               (0x00000004)
  #define DDRVREF_CR_DDRCRVREFADJUST2_VtSlopeAOnSAGV_HSH               (0x0310280C)

  #define DDRVREF_CR_DDRCRVREFADJUST2_VtOffsetOnSAGV_OFF               (19)
  #define DDRVREF_CR_DDRCRVREFADJUST2_VtOffsetOnSAGV_WID               ( 4)
  #define DDRVREF_CR_DDRCRVREFADJUST2_VtOffsetOnSAGV_MSK               (0x00780000)
  #define DDRVREF_CR_DDRCRVREFADJUST2_VtOffsetOnSAGV_MIN               (0)
  #define DDRVREF_CR_DDRCRVREFADJUST2_VtOffsetOnSAGV_MAX               (15) // 0x0000000F
  #define DDRVREF_CR_DDRCRVREFADJUST2_VtOffsetOnSAGV_DEF               (0x00000003)
  #define DDRVREF_CR_DDRCRVREFADJUST2_VtOffsetOnSAGV_HSH               (0x0413280C)

  #define DDRVREF_CR_DDRCRVREFADJUST2_vtcompovrden_OFF                 (23)
  #define DDRVREF_CR_DDRCRVREFADJUST2_vtcompovrden_WID                 ( 1)
  #define DDRVREF_CR_DDRCRVREFADJUST2_vtcompovrden_MSK                 (0x00800000)
  #define DDRVREF_CR_DDRCRVREFADJUST2_vtcompovrden_MIN                 (0)
  #define DDRVREF_CR_DDRCRVREFADJUST2_vtcompovrden_MAX                 (1) // 0x00000001
  #define DDRVREF_CR_DDRCRVREFADJUST2_vtcompovrden_DEF                 (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST2_vtcompovrden_HSH                 (0x0117280C)

  #define DDRVREF_CR_DDRCRVREFADJUST2_vtcompovrd_OFF                   (24)
  #define DDRVREF_CR_DDRCRVREFADJUST2_vtcompovrd_WID                   ( 8)
  #define DDRVREF_CR_DDRCRVREFADJUST2_vtcompovrd_MSK                   (0xFF000000)
  #define DDRVREF_CR_DDRCRVREFADJUST2_vtcompovrd_MIN                   (0)
  #define DDRVREF_CR_DDRCRVREFADJUST2_vtcompovrd_MAX                   (255) // 0x000000FF
  #define DDRVREF_CR_DDRCRVREFADJUST2_vtcompovrd_DEF                   (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST2_vtcompovrd_HSH                   (0x0818280C)

#define DDRVREF_CR_DDRCRVREFADJUST3_REG                                (0x00002810)

  #define DDRVREF_CR_DDRCRVREFADJUST3_Ch1Dimm1CaVrefIntCtl_OFF         ( 0)
  #define DDRVREF_CR_DDRCRVREFADJUST3_Ch1Dimm1CaVrefIntCtl_WID         ( 9)
  #define DDRVREF_CR_DDRCRVREFADJUST3_Ch1Dimm1CaVrefIntCtl_MSK         (0x000001FF)
  #define DDRVREF_CR_DDRCRVREFADJUST3_Ch1Dimm1CaVrefIntCtl_MIN         (0)
  #define DDRVREF_CR_DDRCRVREFADJUST3_Ch1Dimm1CaVrefIntCtl_MAX         (511) // 0x000001FF
  #define DDRVREF_CR_DDRCRVREFADJUST3_Ch1Dimm1CaVrefIntCtl_DEF         (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST3_Ch1Dimm1CaVrefIntCtl_HSH         (0x09002810)

  #define DDRVREF_CR_DDRCRVREFADJUST3_Ch1Dimm1CaVrefEn_OFF             ( 9)
  #define DDRVREF_CR_DDRCRVREFADJUST3_Ch1Dimm1CaVrefEn_WID             ( 1)
  #define DDRVREF_CR_DDRCRVREFADJUST3_Ch1Dimm1CaVrefEn_MSK             (0x00000200)
  #define DDRVREF_CR_DDRCRVREFADJUST3_Ch1Dimm1CaVrefEn_MIN             (0)
  #define DDRVREF_CR_DDRCRVREFADJUST3_Ch1Dimm1CaVrefEn_MAX             (1) // 0x00000001
  #define DDRVREF_CR_DDRCRVREFADJUST3_Ch1Dimm1CaVrefEn_DEF             (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST3_Ch1Dimm1CaVrefEn_HSH             (0x01092810)

  #define DDRVREF_CR_DDRCRVREFADJUST3_VrefDimmSagvSlowBWTargetCodeChangeRep_OFF (10)
  #define DDRVREF_CR_DDRCRVREFADJUST3_VrefDimmSagvSlowBWTargetCodeChangeRep_WID ( 1)
  #define DDRVREF_CR_DDRCRVREFADJUST3_VrefDimmSagvSlowBWTargetCodeChangeRep_MSK (0x00000400)
  #define DDRVREF_CR_DDRCRVREFADJUST3_VrefDimmSagvSlowBWTargetCodeChangeRep_MIN (0)
  #define DDRVREF_CR_DDRCRVREFADJUST3_VrefDimmSagvSlowBWTargetCodeChangeRep_MAX (1) // 0x00000001
  #define DDRVREF_CR_DDRCRVREFADJUST3_VrefDimmSagvSlowBWTargetCodeChangeRep_DEF (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST3_VrefDimmSagvSlowBWTargetCodeChangeRep_HSH (0x010A2810)

  #define DDRVREF_CR_DDRCRVREFADJUST3_spare_OFF                        (11)
  #define DDRVREF_CR_DDRCRVREFADJUST3_spare_WID                        (21)
  #define DDRVREF_CR_DDRCRVREFADJUST3_spare_MSK                        (0xFFFFF800)
  #define DDRVREF_CR_DDRCRVREFADJUST3_spare_MIN                        (0)
  #define DDRVREF_CR_DDRCRVREFADJUST3_spare_MAX                        (2097151) // 0x001FFFFF
  #define DDRVREF_CR_DDRCRVREFADJUST3_spare_DEF                        (0x00000000)
  #define DDRVREF_CR_DDRCRVREFADJUST3_spare_HSH                        (0x150B2810)

#define DDRVSSHIBOTA_CR_DDRRCOMPDATA_REG                               (0x00002880)

  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_PanicDrvDn_OFF                  ( 0)
  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_PanicDrvDn_WID                  (10)
  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_PanicDrvDn_MSK                  (0x000003FF)
  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_PanicDrvDn_MIN                  (0)
  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_PanicDrvDn_MAX                  (1023) // 0x000003FF
  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_PanicDrvDn_DEF                  (0x00000094)
  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_PanicDrvDn_HSH                  (0x0A002880)

  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_PanicDrvUp_OFF                  (10)
  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_PanicDrvUp_WID                  (10)
  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_PanicDrvUp_MSK                  (0x000FFC00)
  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_PanicDrvUp_MIN                  (0)
  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_PanicDrvUp_MAX                  (1023) // 0x000003FF
  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_PanicDrvUp_DEF                  (0x00000094)
  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_PanicDrvUp_HSH                  (0x0A0A2880)

  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_VTComp_OFF                      (20)
  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_VTComp_WID                      ( 5)
  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_VTComp_MSK                      (0x01F00000)
  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_VTComp_MIN                      (0)
  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_VTComp_MAX                      (31) // 0x0000001F
  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_VTComp_DEF                      (0x00000005)
  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_VTComp_HSH                      (0x05142880)

  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_spare_OFF                       (25)
  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_spare_WID                       ( 7)
  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_spare_MSK                       (0xFE000000)
  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_spare_MIN                       (0)
  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_spare_MAX                       (127) // 0x0000007F
  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_spare_DEF                       (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRRCOMPDATA_spare_HSH                       (0x07192880)

#define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_REG                          (0x00002884)

  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_Target_OFF                 ( 0)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_Target_WID                 ( 6)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_Target_MSK                 (0x0000003F)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_Target_MIN                 (0)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_Target_MAX                 (63) // 0x0000003F
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_Target_DEF                 (0x0000001C)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_Target_HSH                 (0x06002884)

  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_HiBWDivider_OFF            ( 6)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_HiBWDivider_WID            ( 2)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_HiBWDivider_MSK            (0x000000C0)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_HiBWDivider_MIN            (0)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_HiBWDivider_MAX            (3) // 0x00000003
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_HiBWDivider_DEF            (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_HiBWDivider_HSH            (0x02062884)

  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_LoBWDivider_OFF            ( 8)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_LoBWDivider_WID            ( 2)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_LoBWDivider_MSK            (0x00000300)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_LoBWDivider_MIN            (0)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_LoBWDivider_MAX            (3) // 0x00000003
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_LoBWDivider_DEF            (0x00000002)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_LoBWDivider_HSH            (0x02082884)

  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_SampleDivider_OFF          (10)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_SampleDivider_WID          ( 2)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_SampleDivider_MSK          (0x00000C00)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_SampleDivider_MIN          (0)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_SampleDivider_MAX          (3) // 0x00000003
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_SampleDivider_DEF          (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_SampleDivider_HSH          (0x020A2884)

  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_EnIdleActiveSwap_OFF       (12)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_EnIdleActiveSwap_WID       ( 1)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_EnIdleActiveSwap_MSK       (0x00001000)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_EnIdleActiveSwap_MIN       (0)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_EnIdleActiveSwap_MAX       (1) // 0x00000001
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_EnIdleActiveSwap_DEF       (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_EnIdleActiveSwap_HSH       (0x010C2884)

  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_OpenLoop_OFF               (13)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_OpenLoop_WID               ( 1)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_OpenLoop_MSK               (0x00002000)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_OpenLoop_MIN               (0)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_OpenLoop_MAX               (1) // 0x00000001
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_OpenLoop_DEF               (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_OpenLoop_HSH               (0x010D2884)

  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_BWError_OFF                (14)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_BWError_WID                ( 2)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_BWError_MSK                (0x0000C000)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_BWError_MIN                (0)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_BWError_MAX                (3) // 0x00000003
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_BWError_DEF                (0x00000002)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_BWError_HSH                (0x020E2884)

  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_PanicEn_OFF                (16)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_PanicEn_WID                ( 1)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_PanicEn_MSK                (0x00010000)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_PanicEn_MIN                (0)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_PanicEn_MAX                (1) // 0x00000001
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_PanicEn_DEF                (0x00000001)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_PanicEn_HSH                (0x01102884)

  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_EnCkePanic_OFF             (17)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_EnCkePanic_WID             ( 1)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_EnCkePanic_MSK             (0x00020000)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_EnCkePanic_MIN             (0)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_EnCkePanic_MAX             (1) // 0x00000001
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_EnCkePanic_DEF             (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_EnCkePanic_HSH             (0x01112884)

  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_Spare1_OFF                 (18)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_Spare1_WID                 ( 4)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_Spare1_MSK                 (0x003C0000)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_Spare1_MIN                 (0)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_Spare1_MAX                 (15) // 0x0000000F
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_Spare1_DEF                 (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_Spare1_HSH                 (0x04122884)

  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_GainBoost_OFF              (22)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_GainBoost_WID              ( 1)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_GainBoost_MSK              (0x00400000)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_GainBoost_MIN              (0)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_GainBoost_MAX              (1) // 0x00000001
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_GainBoost_DEF              (0x00000001)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_GainBoost_HSH              (0x01162884)

  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_SelCode_OFF                (23)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_SelCode_WID                ( 1)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_SelCode_MSK                (0x00800000)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_SelCode_MIN                (0)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_SelCode_MAX                (1) // 0x00000001
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_SelCode_DEF                (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_SelCode_HSH                (0x01172884)

  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_DisableOverFlowDrv_OFF     (24)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_DisableOverFlowDrv_WID     ( 1)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_DisableOverFlowDrv_MSK     (0x01000000)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_DisableOverFlowDrv_MIN     (0)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_DisableOverFlowDrv_MAX     (1) // 0x00000001
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_DisableOverFlowDrv_DEF     (0x00000001)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_DisableOverFlowDrv_HSH     (0x01182884)

  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_OutputCode_OFF             (25)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_OutputCode_WID             ( 7)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_OutputCode_MSK             (0xFE000000)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_OutputCode_MIN             (0)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_OutputCode_MAX             (127) // 0x0000007F
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_OutputCode_DEF             (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_OutputCode_HSH             (0x07192884)

#define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_REG                  (0x00002888)

  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare1_OFF         ( 0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare1_WID         ( 4)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare1_MSK         (0x0000000F)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare1_MIN         (0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare1_MAX         (15) // 0x0000000F
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare1_DEF         (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare1_HSH         (0x04002888)

  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_Panic_OFF          ( 4)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_Panic_WID          ( 5)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_Panic_MSK          (0x000001F0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_Panic_MIN          (0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_Panic_MAX          (31) // 0x0000001F
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_Panic_DEF          (0x00000004)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_Panic_HSH          (0x05042888)

  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare2_OFF         ( 9)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare2_WID         ( 2)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare2_MSK         (0x00000600)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare2_MIN         (0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare2_MAX         (3) // 0x00000003
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare2_DEF         (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare2_HSH         (0x02092888)

  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_DisSensorPwrDn_OFF (11)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_DisSensorPwrDn_WID ( 1)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_DisSensorPwrDn_MSK (0x00000800)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_DisSensorPwrDn_MIN (0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_DisSensorPwrDn_MAX (1) // 0x00000001
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_DisSensorPwrDn_DEF (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_DisSensorPwrDn_HSH (0x010B2888)

  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrdEn_OFF     (12)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrdEn_WID     ( 1)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrdEn_MSK     (0x00001000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrdEn_MIN     (0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrdEn_MAX     (1) // 0x00000001
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrdEn_DEF     (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrdEn_HSH     (0x010C2888)

  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_ViewOfstsel_OFF    (13)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_ViewOfstsel_WID    ( 3)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_ViewOfstsel_MSK    (0x0000E000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_ViewOfstsel_MIN    (0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_ViewOfstsel_MAX    (7) // 0x00000007
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_ViewOfstsel_DEF    (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_ViewOfstsel_HSH    (0x030D2888)

  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_envttcompforvsshi_OFF (16)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_envttcompforvsshi_WID ( 1)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_envttcompforvsshi_MSK (0x00010000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_envttcompforvsshi_MIN (0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_envttcompforvsshi_MAX (1) // 0x00000001
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_envttcompforvsshi_DEF (0x00000001)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_envttcompforvsshi_HSH (0x01102888)

  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_DdrCRForceODTOn_OFF (17)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_DdrCRForceODTOn_WID ( 1)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_DdrCRForceODTOn_MSK (0x00020000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_DdrCRForceODTOn_MIN (0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_DdrCRForceODTOn_MAX (1) // 0x00000001
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_DdrCRForceODTOn_DEF (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_DdrCRForceODTOn_HSH (0x01112888)

  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqHi_OFF       (18)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqHi_WID       ( 1)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqHi_MSK       (0x00040000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqHi_MIN       (0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqHi_MAX       (1) // 0x00000001
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqHi_DEF       (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqHi_HSH       (0x01122888)

  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqLo_OFF       (19)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqLo_WID       ( 1)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqLo_MSK       (0x00080000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqLo_MIN       (0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqLo_MAX       (1) // 0x00000001
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqLo_DEF       (0x00000001)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqLo_HSH       (0x01132888)

  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_EnVttOdt_OFF       (20)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_EnVttOdt_WID       ( 1)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_EnVttOdt_MSK       (0x00100000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_EnVttOdt_MIN       (0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_EnVttOdt_MAX       (1) // 0x00000001
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_EnVttOdt_DEF       (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_EnVttOdt_HSH       (0x01142888)

  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_SalCompLegacyCbit_OFF (21)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_SalCompLegacyCbit_WID ( 1)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_SalCompLegacyCbit_MSK (0x00200000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_SalCompLegacyCbit_MIN (0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_SalCompLegacyCbit_MAX (1) // 0x00000001
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_SalCompLegacyCbit_DEF (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_SalCompLegacyCbit_HSH (0x01152888)

  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare3_OFF         (22)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare3_WID         ( 2)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare3_MSK         (0x00C00000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare3_MIN         (0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare3_MAX         (3) // 0x00000003
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare3_DEF         (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare3_HSH         (0x02162888)

  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_VssHiGndSel_OFF    (24)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_VssHiGndSel_WID    ( 1)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_VssHiGndSel_MSK    (0x01000000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_VssHiGndSel_MIN    (0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_VssHiGndSel_MAX    (1) // 0x00000001
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_VssHiGndSel_DEF    (0x00000001)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_VssHiGndSel_HSH    (0x01182888)

  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_Disable2Vt_OFF     (25)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_Disable2Vt_WID     ( 1)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_Disable2Vt_MSK     (0x02000000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_Disable2Vt_MIN     (0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_Disable2Vt_MAX     (1) // 0x00000001
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_Disable2Vt_DEF     (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_Disable2Vt_HSH     (0x01192888)

  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrd_OFF       (26)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrd_WID       ( 6)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrd_MSK       (0xFC000000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrd_MIN       (0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrd_MAX       (63) // 0x0000003F
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrd_DEF       (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrd_HSH       (0x061A2888)

#define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_REG                 (0x0000288C)

  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicSpareCompOfst_OFF ( 0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicSpareCompOfst_WID ( 6)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicSpareCompOfst_MSK (0x0000003F)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicSpareCompOfst_MIN (0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicSpareCompOfst_MAX (63) // 0x0000003F
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicSpareCompOfst_DEF (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicSpareCompOfst_HSH (0x0600288C)

  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicTargetCompOfst_OFF ( 6)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicTargetCompOfst_WID ( 6)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicTargetCompOfst_MSK (0x00000FC0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicTargetCompOfst_MIN (0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicTargetCompOfst_MAX (63) // 0x0000003F
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicTargetCompOfst_DEF (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicTargetCompOfst_HSH (0x0606288C)

  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicLoCompOfst_OFF (12)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicLoCompOfst_WID ( 6)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicLoCompOfst_MSK (0x0003F000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicLoCompOfst_MIN (0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicLoCompOfst_MAX (63) // 0x0000003F
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicLoCompOfst_DEF (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicLoCompOfst_HSH (0x060C288C)

  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicHiCompOfst_OFF (18)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicHiCompOfst_WID ( 6)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicHiCompOfst_MSK (0x00FC0000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicHiCompOfst_MIN (0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicHiCompOfst_MAX (63) // 0x0000003F
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicHiCompOfst_DEF (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicHiCompOfst_HSH (0x0612288C)

  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_spare_OFF         (24)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_spare_WID         ( 8)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_spare_MSK         (0xFF000000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_spare_MIN         (0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_spare_MAX         (255) // 0x000000FF
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_spare_DEF         (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_spare_HSH         (0x0818288C)

#define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL1_REG                 (0x00002890)

  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL1_View_OFF          ( 0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL1_View_WID          ( 6)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL1_View_MSK          (0x0000003F)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL1_View_MIN          (0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL1_View_MAX          (63) // 0x0000003F
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL1_View_DEF          (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL1_View_HSH          (0x06002890)

  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL1_Spare_OFF         ( 6)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL1_Spare_WID         (26)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL1_Spare_MSK         (0xFFFFFFC0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL1_Spare_MIN         (0)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL1_Spare_MAX         (67108863) // 0x03FFFFFF
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL1_Spare_DEF         (0x00000000)
  #define DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL1_Spare_HSH         (0x1A062890)

#define DDRVSSHITOPA_CR_DDRRCOMPDATA_REG                               (0x00002900)

  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_PanicDrvDn_OFF                  ( 0)
  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_PanicDrvDn_WID                  (10)
  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_PanicDrvDn_MSK                  (0x000003FF)
  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_PanicDrvDn_MIN                  (0)
  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_PanicDrvDn_MAX                  (1023) // 0x000003FF
  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_PanicDrvDn_DEF                  (0x00000094)
  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_PanicDrvDn_HSH                  (0x0A002900)

  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_PanicDrvUp_OFF                  (10)
  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_PanicDrvUp_WID                  (10)
  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_PanicDrvUp_MSK                  (0x000FFC00)
  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_PanicDrvUp_MIN                  (0)
  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_PanicDrvUp_MAX                  (1023) // 0x000003FF
  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_PanicDrvUp_DEF                  (0x00000094)
  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_PanicDrvUp_HSH                  (0x0A0A2900)

  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_VTComp_OFF                      (20)
  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_VTComp_WID                      ( 5)
  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_VTComp_MSK                      (0x01F00000)
  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_VTComp_MIN                      (0)
  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_VTComp_MAX                      (31) // 0x0000001F
  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_VTComp_DEF                      (0x00000005)
  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_VTComp_HSH                      (0x05142900)

  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_spare_OFF                       (25)
  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_spare_WID                       ( 7)
  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_spare_MSK                       (0xFE000000)
  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_spare_MIN                       (0)
  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_spare_MAX                       (127) // 0x0000007F
  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_spare_DEF                       (0x00000000)
  #define DDRVSSHITOPA_CR_DDRRCOMPDATA_spare_HSH                       (0x07192900)

#define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_REG                          (0x00002904)

  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_Target_OFF                 ( 0)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_Target_WID                 ( 6)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_Target_MSK                 (0x0000003F)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_Target_MIN                 (0)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_Target_MAX                 (63) // 0x0000003F
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_Target_DEF                 (0x0000001C)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_Target_HSH                 (0x06002904)

  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_HiBWDivider_OFF            ( 6)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_HiBWDivider_WID            ( 2)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_HiBWDivider_MSK            (0x000000C0)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_HiBWDivider_MIN            (0)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_HiBWDivider_MAX            (3) // 0x00000003
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_HiBWDivider_DEF            (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_HiBWDivider_HSH            (0x02062904)

  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_LoBWDivider_OFF            ( 8)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_LoBWDivider_WID            ( 2)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_LoBWDivider_MSK            (0x00000300)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_LoBWDivider_MIN            (0)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_LoBWDivider_MAX            (3) // 0x00000003
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_LoBWDivider_DEF            (0x00000002)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_LoBWDivider_HSH            (0x02082904)

  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_SampleDivider_OFF          (10)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_SampleDivider_WID          ( 2)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_SampleDivider_MSK          (0x00000C00)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_SampleDivider_MIN          (0)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_SampleDivider_MAX          (3) // 0x00000003
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_SampleDivider_DEF          (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_SampleDivider_HSH          (0x020A2904)

  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_EnIdleActiveSwap_OFF       (12)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_EnIdleActiveSwap_WID       ( 1)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_EnIdleActiveSwap_MSK       (0x00001000)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_EnIdleActiveSwap_MIN       (0)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_EnIdleActiveSwap_MAX       (1) // 0x00000001
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_EnIdleActiveSwap_DEF       (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_EnIdleActiveSwap_HSH       (0x010C2904)

  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_OpenLoop_OFF               (13)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_OpenLoop_WID               ( 1)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_OpenLoop_MSK               (0x00002000)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_OpenLoop_MIN               (0)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_OpenLoop_MAX               (1) // 0x00000001
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_OpenLoop_DEF               (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_OpenLoop_HSH               (0x010D2904)

  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_BWError_OFF                (14)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_BWError_WID                ( 2)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_BWError_MSK                (0x0000C000)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_BWError_MIN                (0)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_BWError_MAX                (3) // 0x00000003
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_BWError_DEF                (0x00000002)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_BWError_HSH                (0x020E2904)

  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_PanicEn_OFF                (16)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_PanicEn_WID                ( 1)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_PanicEn_MSK                (0x00010000)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_PanicEn_MIN                (0)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_PanicEn_MAX                (1) // 0x00000001
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_PanicEn_DEF                (0x00000001)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_PanicEn_HSH                (0x01102904)

  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_EnCkePanic_OFF             (17)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_EnCkePanic_WID             ( 1)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_EnCkePanic_MSK             (0x00020000)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_EnCkePanic_MIN             (0)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_EnCkePanic_MAX             (1) // 0x00000001
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_EnCkePanic_DEF             (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_EnCkePanic_HSH             (0x01112904)

  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_Spare1_OFF                 (18)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_Spare1_WID                 ( 4)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_Spare1_MSK                 (0x003C0000)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_Spare1_MIN                 (0)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_Spare1_MAX                 (15) // 0x0000000F
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_Spare1_DEF                 (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_Spare1_HSH                 (0x04122904)

  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_GainBoost_OFF              (22)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_GainBoost_WID              ( 1)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_GainBoost_MSK              (0x00400000)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_GainBoost_MIN              (0)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_GainBoost_MAX              (1) // 0x00000001
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_GainBoost_DEF              (0x00000001)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_GainBoost_HSH              (0x01162904)

  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_SelCode_OFF                (23)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_SelCode_WID                ( 1)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_SelCode_MSK                (0x00800000)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_SelCode_MIN                (0)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_SelCode_MAX                (1) // 0x00000001
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_SelCode_DEF                (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_SelCode_HSH                (0x01172904)

  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_DisableOverFlowDrv_OFF     (24)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_DisableOverFlowDrv_WID     ( 1)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_DisableOverFlowDrv_MSK     (0x01000000)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_DisableOverFlowDrv_MIN     (0)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_DisableOverFlowDrv_MAX     (1) // 0x00000001
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_DisableOverFlowDrv_DEF     (0x00000001)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_DisableOverFlowDrv_HSH     (0x01182904)

  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_OutputCode_OFF             (25)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_OutputCode_WID             ( 7)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_OutputCode_MSK             (0xFE000000)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_OutputCode_MIN             (0)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_OutputCode_MAX             (127) // 0x0000007F
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_OutputCode_DEF             (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_OutputCode_HSH             (0x07192904)

#define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_REG                  (0x00002908)

  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_spare1_OFF         ( 0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_spare1_WID         ( 4)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_spare1_MSK         (0x0000000F)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_spare1_MIN         (0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_spare1_MAX         (15) // 0x0000000F
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_spare1_DEF         (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_spare1_HSH         (0x04002908)

  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_Panic_OFF          ( 4)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_Panic_WID          ( 5)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_Panic_MSK          (0x000001F0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_Panic_MIN          (0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_Panic_MAX          (31) // 0x0000001F
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_Panic_DEF          (0x00000004)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_Panic_HSH          (0x05042908)

  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_spare2_OFF         ( 9)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_spare2_WID         ( 2)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_spare2_MSK         (0x00000600)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_spare2_MIN         (0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_spare2_MAX         (3) // 0x00000003
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_spare2_DEF         (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_spare2_HSH         (0x02092908)

  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_DisSensorPwrDn_OFF (11)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_DisSensorPwrDn_WID ( 1)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_DisSensorPwrDn_MSK (0x00000800)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_DisSensorPwrDn_MIN (0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_DisSensorPwrDn_MAX (1) // 0x00000001
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_DisSensorPwrDn_DEF (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_DisSensorPwrDn_HSH (0x010B2908)

  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrdEn_OFF     (12)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrdEn_WID     ( 1)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrdEn_MSK     (0x00001000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrdEn_MIN     (0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrdEn_MAX     (1) // 0x00000001
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrdEn_DEF     (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrdEn_HSH     (0x010C2908)

  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_ViewOfstsel_OFF    (13)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_ViewOfstsel_WID    ( 3)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_ViewOfstsel_MSK    (0x0000E000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_ViewOfstsel_MIN    (0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_ViewOfstsel_MAX    (7) // 0x00000007
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_ViewOfstsel_DEF    (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_ViewOfstsel_HSH    (0x030D2908)

  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_envttcompforvsshi_OFF (16)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_envttcompforvsshi_WID ( 1)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_envttcompforvsshi_MSK (0x00010000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_envttcompforvsshi_MIN (0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_envttcompforvsshi_MAX (1) // 0x00000001
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_envttcompforvsshi_DEF (0x00000001)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_envttcompforvsshi_HSH (0x01102908)

  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_DdrCRForceODTOn_OFF (17)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_DdrCRForceODTOn_WID ( 1)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_DdrCRForceODTOn_MSK (0x00020000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_DdrCRForceODTOn_MIN (0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_DdrCRForceODTOn_MAX (1) // 0x00000001
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_DdrCRForceODTOn_DEF (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_DdrCRForceODTOn_HSH (0x01112908)

  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqHi_OFF       (18)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqHi_WID       ( 1)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqHi_MSK       (0x00040000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqHi_MIN       (0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqHi_MAX       (1) // 0x00000001
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqHi_DEF       (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqHi_HSH       (0x01122908)

  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqLo_OFF       (19)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqLo_WID       ( 1)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqLo_MSK       (0x00080000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqLo_MIN       (0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqLo_MAX       (1) // 0x00000001
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqLo_DEF       (0x00000001)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqLo_HSH       (0x01132908)

  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_EnVttOdt_OFF       (20)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_EnVttOdt_WID       ( 1)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_EnVttOdt_MSK       (0x00100000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_EnVttOdt_MIN       (0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_EnVttOdt_MAX       (1) // 0x00000001
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_EnVttOdt_DEF       (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_EnVttOdt_HSH       (0x01142908)

  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_SalCompLegacyCbit_OFF (21)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_SalCompLegacyCbit_WID ( 1)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_SalCompLegacyCbit_MSK (0x00200000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_SalCompLegacyCbit_MIN (0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_SalCompLegacyCbit_MAX (1) // 0x00000001
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_SalCompLegacyCbit_DEF (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_SalCompLegacyCbit_HSH (0x01152908)

  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_spare3_OFF         (22)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_spare3_WID         ( 2)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_spare3_MSK         (0x00C00000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_spare3_MIN         (0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_spare3_MAX         (3) // 0x00000003
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_spare3_DEF         (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_spare3_HSH         (0x02162908)

  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_VssHiGndSel_OFF    (24)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_VssHiGndSel_WID    ( 1)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_VssHiGndSel_MSK    (0x01000000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_VssHiGndSel_MIN    (0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_VssHiGndSel_MAX    (1) // 0x00000001
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_VssHiGndSel_DEF    (0x00000001)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_VssHiGndSel_HSH    (0x01182908)

  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_Disable2Vt_OFF     (25)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_Disable2Vt_WID     ( 1)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_Disable2Vt_MSK     (0x02000000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_Disable2Vt_MIN     (0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_Disable2Vt_MAX     (1) // 0x00000001
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_Disable2Vt_DEF     (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_Disable2Vt_HSH     (0x01192908)

  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrd_OFF       (26)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrd_WID       ( 6)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrd_MSK       (0xFC000000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrd_MIN       (0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrd_MAX       (63) // 0x0000003F
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrd_DEF       (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrd_HSH       (0x061A2908)

#define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_REG                 (0x0000290C)

  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicSpareCompOfst_OFF ( 0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicSpareCompOfst_WID ( 6)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicSpareCompOfst_MSK (0x0000003F)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicSpareCompOfst_MIN (0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicSpareCompOfst_MAX (63) // 0x0000003F
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicSpareCompOfst_DEF (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicSpareCompOfst_HSH (0x0600290C)

  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicTargetCompOfst_OFF ( 6)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicTargetCompOfst_WID ( 6)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicTargetCompOfst_MSK (0x00000FC0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicTargetCompOfst_MIN (0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicTargetCompOfst_MAX (63) // 0x0000003F
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicTargetCompOfst_DEF (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicTargetCompOfst_HSH (0x0606290C)

  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicLoCompOfst_OFF (12)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicLoCompOfst_WID ( 6)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicLoCompOfst_MSK (0x0003F000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicLoCompOfst_MIN (0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicLoCompOfst_MAX (63) // 0x0000003F
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicLoCompOfst_DEF (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicLoCompOfst_HSH (0x060C290C)

  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicHiCompOfst_OFF (18)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicHiCompOfst_WID ( 6)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicHiCompOfst_MSK (0x00FC0000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicHiCompOfst_MIN (0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicHiCompOfst_MAX (63) // 0x0000003F
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicHiCompOfst_DEF (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicHiCompOfst_HSH (0x0612290C)

  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_spare_OFF         (24)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_spare_WID         ( 8)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_spare_MSK         (0xFF000000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_spare_MIN         (0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_spare_MAX         (255) // 0x000000FF
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_spare_DEF         (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_spare_HSH         (0x0818290C)

#define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL1_REG                 (0x00002910)

  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL1_View_OFF          ( 0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL1_View_WID          ( 6)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL1_View_MSK          (0x0000003F)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL1_View_MIN          (0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL1_View_MAX          (63) // 0x0000003F
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL1_View_DEF          (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL1_View_HSH          (0x06002910)

  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL1_Spare_OFF         ( 6)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL1_Spare_WID         (26)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL1_Spare_MSK         (0xFFFFFFC0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL1_Spare_MIN         (0)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL1_Spare_MAX         (67108863) // 0x03FFFFFF
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL1_Spare_DEF         (0x00000000)
  #define DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL1_Spare_HSH         (0x1A062910)

#define DDRVSSHICENTA_CR_DDRRCOMPDATA_REG                              (0x00002980)

  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_PanicDrvDn_OFF                 ( 0)
  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_PanicDrvDn_WID                 (10)
  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_PanicDrvDn_MSK                 (0x000003FF)
  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_PanicDrvDn_MIN                 (0)
  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_PanicDrvDn_MAX                 (1023) // 0x000003FF
  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_PanicDrvDn_DEF                 (0x00000094)
  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_PanicDrvDn_HSH                 (0x0A002980)

  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_PanicDrvUp_OFF                 (10)
  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_PanicDrvUp_WID                 (10)
  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_PanicDrvUp_MSK                 (0x000FFC00)
  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_PanicDrvUp_MIN                 (0)
  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_PanicDrvUp_MAX                 (1023) // 0x000003FF
  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_PanicDrvUp_DEF                 (0x00000094)
  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_PanicDrvUp_HSH                 (0x0A0A2980)

  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_VTComp_OFF                     (20)
  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_VTComp_WID                     ( 5)
  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_VTComp_MSK                     (0x01F00000)
  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_VTComp_MIN                     (0)
  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_VTComp_MAX                     (31) // 0x0000001F
  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_VTComp_DEF                     (0x00000005)
  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_VTComp_HSH                     (0x05142980)

  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_spare_OFF                      (25)
  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_spare_WID                      ( 7)
  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_spare_MSK                      (0xFE000000)
  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_spare_MIN                      (0)
  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_spare_MAX                      (127) // 0x0000007F
  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_spare_DEF                      (0x00000000)
  #define DDRVSSHICENTA_CR_DDRRCOMPDATA_spare_HSH                      (0x07192980)

#define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_REG                         (0x00002984)

  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_Target_OFF                ( 0)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_Target_WID                ( 6)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_Target_MSK                (0x0000003F)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_Target_MIN                (0)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_Target_MAX                (63) // 0x0000003F
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_Target_DEF                (0x0000001C)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_Target_HSH                (0x06002984)

  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_HiBWDivider_OFF           ( 6)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_HiBWDivider_WID           ( 2)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_HiBWDivider_MSK           (0x000000C0)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_HiBWDivider_MIN           (0)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_HiBWDivider_MAX           (3) // 0x00000003
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_HiBWDivider_DEF           (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_HiBWDivider_HSH           (0x02062984)

  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_LoBWDivider_OFF           ( 8)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_LoBWDivider_WID           ( 2)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_LoBWDivider_MSK           (0x00000300)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_LoBWDivider_MIN           (0)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_LoBWDivider_MAX           (3) // 0x00000003
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_LoBWDivider_DEF           (0x00000002)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_LoBWDivider_HSH           (0x02082984)

  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_SampleDivider_OFF         (10)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_SampleDivider_WID         ( 2)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_SampleDivider_MSK         (0x00000C00)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_SampleDivider_MIN         (0)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_SampleDivider_MAX         (3) // 0x00000003
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_SampleDivider_DEF         (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_SampleDivider_HSH         (0x020A2984)

  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_EnIdleActiveSwap_OFF      (12)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_EnIdleActiveSwap_WID      ( 1)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_EnIdleActiveSwap_MSK      (0x00001000)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_EnIdleActiveSwap_MIN      (0)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_EnIdleActiveSwap_MAX      (1) // 0x00000001
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_EnIdleActiveSwap_DEF      (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_EnIdleActiveSwap_HSH      (0x010C2984)

  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_OpenLoop_OFF              (13)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_OpenLoop_WID              ( 1)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_OpenLoop_MSK              (0x00002000)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_OpenLoop_MIN              (0)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_OpenLoop_MAX              (1) // 0x00000001
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_OpenLoop_DEF              (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_OpenLoop_HSH              (0x010D2984)

  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_BWError_OFF               (14)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_BWError_WID               ( 2)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_BWError_MSK               (0x0000C000)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_BWError_MIN               (0)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_BWError_MAX               (3) // 0x00000003
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_BWError_DEF               (0x00000002)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_BWError_HSH               (0x020E2984)

  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_PanicEn_OFF               (16)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_PanicEn_WID               ( 1)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_PanicEn_MSK               (0x00010000)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_PanicEn_MIN               (0)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_PanicEn_MAX               (1) // 0x00000001
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_PanicEn_DEF               (0x00000001)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_PanicEn_HSH               (0x01102984)

  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_EnCkePanic_OFF            (17)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_EnCkePanic_WID            ( 1)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_EnCkePanic_MSK            (0x00020000)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_EnCkePanic_MIN            (0)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_EnCkePanic_MAX            (1) // 0x00000001
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_EnCkePanic_DEF            (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_EnCkePanic_HSH            (0x01112984)

  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_Spare1_OFF                (18)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_Spare1_WID                ( 4)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_Spare1_MSK                (0x003C0000)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_Spare1_MIN                (0)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_Spare1_MAX                (15) // 0x0000000F
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_Spare1_DEF                (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_Spare1_HSH                (0x04122984)

  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_GainBoost_OFF             (22)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_GainBoost_WID             ( 1)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_GainBoost_MSK             (0x00400000)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_GainBoost_MIN             (0)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_GainBoost_MAX             (1) // 0x00000001
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_GainBoost_DEF             (0x00000001)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_GainBoost_HSH             (0x01162984)

  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_SelCode_OFF               (23)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_SelCode_WID               ( 1)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_SelCode_MSK               (0x00800000)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_SelCode_MIN               (0)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_SelCode_MAX               (1) // 0x00000001
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_SelCode_DEF               (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_SelCode_HSH               (0x01172984)

  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_DisableOverFlowDrv_OFF    (24)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_DisableOverFlowDrv_WID    ( 1)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_DisableOverFlowDrv_MSK    (0x01000000)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_DisableOverFlowDrv_MIN    (0)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_DisableOverFlowDrv_MAX    (1) // 0x00000001
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_DisableOverFlowDrv_DEF    (0x00000001)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_DisableOverFlowDrv_HSH    (0x01182984)

  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_OutputCode_OFF            (25)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_OutputCode_WID            ( 7)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_OutputCode_MSK            (0xFE000000)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_OutputCode_MIN            (0)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_OutputCode_MAX            (127) // 0x0000007F
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_OutputCode_DEF            (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_OutputCode_HSH            (0x07192984)

#define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_REG                 (0x00002988)

  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare1_OFF        ( 0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare1_WID        ( 4)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare1_MSK        (0x0000000F)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare1_MIN        (0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare1_MAX        (15) // 0x0000000F
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare1_DEF        (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare1_HSH        (0x04002988)

  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_Panic_OFF         ( 4)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_Panic_WID         ( 5)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_Panic_MSK         (0x000001F0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_Panic_MIN         (0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_Panic_MAX         (31) // 0x0000001F
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_Panic_DEF         (0x00000004)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_Panic_HSH         (0x05042988)

  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare2_OFF        ( 9)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare2_WID        ( 2)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare2_MSK        (0x00000600)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare2_MIN        (0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare2_MAX        (3) // 0x00000003
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare2_DEF        (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare2_HSH        (0x02092988)

  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_DisSensorPwrDn_OFF (11)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_DisSensorPwrDn_WID ( 1)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_DisSensorPwrDn_MSK (0x00000800)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_DisSensorPwrDn_MIN (0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_DisSensorPwrDn_MAX (1) // 0x00000001
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_DisSensorPwrDn_DEF (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_DisSensorPwrDn_HSH (0x010B2988)

  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrdEn_OFF    (12)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrdEn_WID    ( 1)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrdEn_MSK    (0x00001000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrdEn_MIN    (0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrdEn_MAX    (1) // 0x00000001
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrdEn_DEF    (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrdEn_HSH    (0x010C2988)

  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_ViewOfstsel_OFF   (13)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_ViewOfstsel_WID   ( 3)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_ViewOfstsel_MSK   (0x0000E000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_ViewOfstsel_MIN   (0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_ViewOfstsel_MAX   (7) // 0x00000007
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_ViewOfstsel_DEF   (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_ViewOfstsel_HSH   (0x030D2988)

  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_envttcompforvsshi_OFF (16)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_envttcompforvsshi_WID ( 1)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_envttcompforvsshi_MSK (0x00010000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_envttcompforvsshi_MIN (0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_envttcompforvsshi_MAX (1) // 0x00000001
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_envttcompforvsshi_DEF (0x00000001)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_envttcompforvsshi_HSH (0x01102988)

  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_DdrCRForceODTOn_OFF (17)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_DdrCRForceODTOn_WID ( 1)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_DdrCRForceODTOn_MSK (0x00020000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_DdrCRForceODTOn_MIN (0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_DdrCRForceODTOn_MAX (1) // 0x00000001
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_DdrCRForceODTOn_DEF (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_DdrCRForceODTOn_HSH (0x01112988)

  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqHi_OFF      (18)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqHi_WID      ( 1)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqHi_MSK      (0x00040000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqHi_MIN      (0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqHi_MAX      (1) // 0x00000001
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqHi_DEF      (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqHi_HSH      (0x01122988)

  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqLo_OFF      (19)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqLo_WID      ( 1)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqLo_MSK      (0x00080000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqLo_MIN      (0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqLo_MAX      (1) // 0x00000001
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqLo_DEF      (0x00000001)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_VccddqLo_HSH      (0x01132988)

  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_EnVttOdt_OFF      (20)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_EnVttOdt_WID      ( 1)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_EnVttOdt_MSK      (0x00100000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_EnVttOdt_MIN      (0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_EnVttOdt_MAX      (1) // 0x00000001
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_EnVttOdt_DEF      (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_EnVttOdt_HSH      (0x01142988)

  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_SalCompLegacyCbit_OFF (21)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_SalCompLegacyCbit_WID ( 1)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_SalCompLegacyCbit_MSK (0x00200000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_SalCompLegacyCbit_MIN (0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_SalCompLegacyCbit_MAX (1) // 0x00000001
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_SalCompLegacyCbit_DEF (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_SalCompLegacyCbit_HSH (0x01152988)

  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare3_OFF        (22)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare3_WID        ( 2)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare3_MSK        (0x00C00000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare3_MIN        (0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare3_MAX        (3) // 0x00000003
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare3_DEF        (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_spare3_HSH        (0x02162988)

  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_VssHiGndSel_OFF   (24)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_VssHiGndSel_WID   ( 1)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_VssHiGndSel_MSK   (0x01000000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_VssHiGndSel_MIN   (0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_VssHiGndSel_MAX   (1) // 0x00000001
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_VssHiGndSel_DEF   (0x00000001)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_VssHiGndSel_HSH   (0x01182988)

  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_Disable2Vt_OFF    (25)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_Disable2Vt_WID    ( 1)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_Disable2Vt_MSK    (0x02000000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_Disable2Vt_MIN    (0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_Disable2Vt_MAX    (1) // 0x00000001
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_Disable2Vt_DEF    (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_Disable2Vt_HSH    (0x01192988)

  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrd_OFF      (26)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrd_WID      ( 6)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrd_MSK      (0xFC000000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrd_MIN      (0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrd_MAX      (63) // 0x0000003F
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrd_DEF      (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_OfstOvrd_HSH      (0x061A2988)

#define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_REG                (0x0000298C)

  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicSpareCompOfst_OFF ( 0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicSpareCompOfst_WID ( 6)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicSpareCompOfst_MSK (0x0000003F)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicSpareCompOfst_MIN (0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicSpareCompOfst_MAX (63) // 0x0000003F
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicSpareCompOfst_DEF (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicSpareCompOfst_HSH (0x0600298C)

  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicTargetCompOfst_OFF ( 6)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicTargetCompOfst_WID ( 6)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicTargetCompOfst_MSK (0x00000FC0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicTargetCompOfst_MIN (0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicTargetCompOfst_MAX (63) // 0x0000003F
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicTargetCompOfst_DEF (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicTargetCompOfst_HSH (0x0606298C)

  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicLoCompOfst_OFF (12)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicLoCompOfst_WID ( 6)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicLoCompOfst_MSK (0x0003F000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicLoCompOfst_MIN (0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicLoCompOfst_MAX (63) // 0x0000003F
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicLoCompOfst_DEF (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicLoCompOfst_HSH (0x060C298C)

  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicHiCompOfst_OFF (18)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicHiCompOfst_WID ( 6)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicHiCompOfst_MSK (0x00FC0000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicHiCompOfst_MIN (0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicHiCompOfst_MAX (63) // 0x0000003F
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicHiCompOfst_DEF (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_PanicHiCompOfst_HSH (0x0612298C)

  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_spare_OFF        (24)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_spare_WID        ( 8)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_spare_MSK        (0xFF000000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_spare_MIN        (0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_spare_MAX        (255) // 0x000000FF
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_spare_DEF        (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_spare_HSH        (0x0818298C)

#define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL1_REG                (0x00002990)

  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL1_View_OFF         ( 0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL1_View_WID         ( 6)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL1_View_MSK         (0x0000003F)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL1_View_MIN         (0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL1_View_MAX         (63) // 0x0000003F
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL1_View_DEF         (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL1_View_HSH         (0x06002990)

  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL1_Spare_OFF        ( 6)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL1_Spare_WID        (26)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL1_Spare_MSK        (0xFFFFFFC0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL1_Spare_MIN        (0)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL1_Spare_MAX        (67108863) // 0x03FFFFFF
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL1_Spare_DEF        (0x00000000)
  #define DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL1_Spare_HSH        (0x1A062990)

#define DDRCTLCLKCKE_CR_MASTERDLLCFG_REG                               (0x00002A00)

  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockThresh_OFF                  ( 0)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockThresh_WID                  ( 3)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockThresh_MSK                  (0x00000007)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockThresh_MIN                  (0)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockThresh_MAX                  (7) // 0x00000007
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockThresh_DEF                  (0x00000004)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockThresh_HSH                  (0x03002A00)

  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockCtr_OFF                     ( 3)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockCtr_WID                     ( 2)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockCtr_MSK                     (0x00000018)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockCtr_MIN                     (0)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockCtr_MAX                     (3) // 0x00000003
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockCtr_DEF                     (0x00000000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockCtr_HSH                     (0x02032A00)

  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_VctrlDischRate_OFF              ( 5)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_VctrlDischRate_WID              ( 2)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_VctrlDischRate_MSK              (0x00000060)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_VctrlDischRate_MIN              (0)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_VctrlDischRate_MAX              (3) // 0x00000003
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_VctrlDischRate_DEF              (0x00000000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_VctrlDischRate_HSH              (0x02052A00)

  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelVctrlHi_OFF                  ( 7)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelVctrlHi_WID                  ( 1)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelVctrlHi_MSK                  (0x00000080)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelVctrlHi_MIN                  (0)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelVctrlHi_MAX                  (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelVctrlHi_DEF                  (0x00000000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelVctrlHi_HSH                  (0x01072A00)

  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_StartupCntSel_OFF               ( 8)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_StartupCntSel_WID               ( 1)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_StartupCntSel_MSK               (0x00000100)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_StartupCntSel_MIN               (0)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_StartupCntSel_MAX               (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_StartupCntSel_DEF               (0x00000000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_StartupCntSel_HSH               (0x01082A00)

  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockSel_OFF                     ( 9)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockSel_WID                     ( 2)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockSel_MSK                     (0x00000600)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockSel_MIN                     (0)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockSel_MAX                     (3) // 0x00000003
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockSel_DEF                     (0x00000000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockSel_HSH                     (0x02092A00)

  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_RstOvrd_OFF                     (11)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_RstOvrd_WID                     ( 1)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_RstOvrd_MSK                     (0x00000800)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_RstOvrd_MIN                     (0)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_RstOvrd_MAX                     (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_RstOvrd_DEF                     (0x00000000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_RstOvrd_HSH                     (0x010B2A00)

  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelRstOvrd_OFF                  (12)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelRstOvrd_WID                  ( 1)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelRstOvrd_MSK                  (0x00001000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelRstOvrd_MIN                  (0)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelRstOvrd_MAX                  (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelRstOvrd_DEF                  (0x00000000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelRstOvrd_HSH                  (0x010C2A00)

  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_TimeOutOvrd_OFF                 (13)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_TimeOutOvrd_WID                 ( 1)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_TimeOutOvrd_MSK                 (0x00002000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_TimeOutOvrd_MIN                 (0)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_TimeOutOvrd_MAX                 (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_TimeOutOvrd_DEF                 (0x00000000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_TimeOutOvrd_HSH                 (0x010D2A00)

  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelTimeOutOvrd_OFF              (14)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelTimeOutOvrd_WID              ( 1)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelTimeOutOvrd_MSK              (0x00004000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelTimeOutOvrd_MIN              (0)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelTimeOutOvrd_MAX              (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelTimeOutOvrd_DEF              (0x00000000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelTimeOutOvrd_HSH              (0x010E2A00)

  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_ClkGateOvrd_OFF                 (15)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_ClkGateOvrd_WID                 ( 1)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_ClkGateOvrd_MSK                 (0x00008000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_ClkGateOvrd_MIN                 (0)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_ClkGateOvrd_MAX                 (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_ClkGateOvrd_DEF                 (0x00000000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_ClkGateOvrd_HSH                 (0x010F2A00)

  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockOvrd_OFF                    (16)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockOvrd_WID                    ( 1)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockOvrd_MSK                    (0x00010000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockOvrd_MIN                    (0)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockOvrd_MAX                    (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockOvrd_DEF                    (0x00000000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_LockOvrd_HSH                    (0x01102A00)

  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelLockOvrd_OFF                 (17)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelLockOvrd_WID                 ( 1)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelLockOvrd_MSK                 (0x00020000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelLockOvrd_MIN                 (0)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelLockOvrd_MAX                 (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelLockOvrd_DEF                 (0x00000000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelLockOvrd_HSH                 (0x01112A00)

  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_OpenLoopOvrd_OFF                (18)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_OpenLoopOvrd_WID                ( 1)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_OpenLoopOvrd_MSK                (0x00040000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_OpenLoopOvrd_MIN                (0)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_OpenLoopOvrd_MAX                (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_OpenLoopOvrd_DEF                (0x00000000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_OpenLoopOvrd_HSH                (0x01122A00)

  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelOpenLoopOvrd_OFF             (19)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelOpenLoopOvrd_WID             ( 1)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelOpenLoopOvrd_MSK             (0x00080000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelOpenLoopOvrd_MIN             (0)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelOpenLoopOvrd_MAX             (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelOpenLoopOvrd_DEF             (0x00000000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelOpenLoopOvrd_HSH             (0x01132A00)

  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_WkLockEnOvrd_OFF                (20)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_WkLockEnOvrd_WID                ( 1)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_WkLockEnOvrd_MSK                (0x00100000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_WkLockEnOvrd_MIN                (0)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_WkLockEnOvrd_MAX                (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_WkLockEnOvrd_DEF                (0x00000000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_WkLockEnOvrd_HSH                (0x01142A00)

  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelWkLockEnOvrd_OFF             (21)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelWkLockEnOvrd_WID             ( 1)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelWkLockEnOvrd_MSK             (0x00200000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelWkLockEnOvrd_MIN             (0)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelWkLockEnOvrd_MAX             (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelWkLockEnOvrd_DEF             (0x00000000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_SelWkLockEnOvrd_HSH             (0x01152A00)

  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_CfdlDis_OFF                     (22)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_CfdlDis_WID                     ( 1)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_CfdlDis_MSK                     (0x00400000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_CfdlDis_MIN                     (0)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_CfdlDis_MAX                     (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_CfdlDis_DEF                     (0x00000000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_CfdlDis_HSH                     (0x01162A00)

  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_DftEn_OFF                       (23)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_DftEn_WID                       ( 1)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_DftEn_MSK                       (0x00800000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_DftEn_MIN                       (0)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_DftEn_MAX                       (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_DftEn_DEF                       (0x00000000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_DftEn_HSH                       (0x01172A00)

  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_spare0_OFF                      (24)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_spare0_WID                      ( 8)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_spare0_MSK                      (0xFF000000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_spare0_MIN                      (0)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_spare0_MAX                      (255) // 0x000000FF
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_spare0_DEF                      (0x00000000)
  #define DDRCTLCLKCKE_CR_MASTERDLLCFG_spare0_HSH                      (0x08182A00)

#define DDRCTLCLKCKE_CR_CBTUNE0_REG                                    (0x00002A04)

  #define DDRCTLCLKCKE_CR_CBTUNE0_DllBWEn_OFF                          ( 0)
  #define DDRCTLCLKCKE_CR_CBTUNE0_DllBWEn_WID                          (32)
  #define DDRCTLCLKCKE_CR_CBTUNE0_DllBWEn_MSK                          (0xFFFFFFFF)
  #define DDRCTLCLKCKE_CR_CBTUNE0_DllBWEn_MIN                          (0)
  #define DDRCTLCLKCKE_CR_CBTUNE0_DllBWEn_MAX                          (4294967295) // 0xFFFFFFFF
  #define DDRCTLCLKCKE_CR_CBTUNE0_DllBWEn_DEF                          (0xFDB86521)
  #define DDRCTLCLKCKE_CR_CBTUNE0_DllBWEn_HSH                          (0x20002A04)

#define DDRCTLCLKCKE_CR_CBTUNE1_REG                                    (0x00002A08)

  #define DDRCTLCLKCKE_CR_CBTUNE1_PiCbEn_OFF                           ( 0)
  #define DDRCTLCLKCKE_CR_CBTUNE1_PiCbEn_WID                           (24)
  #define DDRCTLCLKCKE_CR_CBTUNE1_PiCbEn_MSK                           (0x00FFFFFF)
  #define DDRCTLCLKCKE_CR_CBTUNE1_PiCbEn_MIN                           (0)
  #define DDRCTLCLKCKE_CR_CBTUNE1_PiCbEn_MAX                           (16777215) // 0x00FFFFFF
  #define DDRCTLCLKCKE_CR_CBTUNE1_PiCbEn_DEF                           (0x00249492)
  #define DDRCTLCLKCKE_CR_CBTUNE1_PiCbEn_HSH                           (0x18002A08)

  #define DDRCTLCLKCKE_CR_CBTUNE1_CbEnRsvd_OFF                         (24)
  #define DDRCTLCLKCKE_CR_CBTUNE1_CbEnRsvd_WID                         ( 3)
  #define DDRCTLCLKCKE_CR_CBTUNE1_CbEnRsvd_MSK                         (0x07000000)
  #define DDRCTLCLKCKE_CR_CBTUNE1_CbEnRsvd_MIN                         (0)
  #define DDRCTLCLKCKE_CR_CBTUNE1_CbEnRsvd_MAX                         (7) // 0x00000007
  #define DDRCTLCLKCKE_CR_CBTUNE1_CbEnRsvd_DEF                         (0x00000000)
  #define DDRCTLCLKCKE_CR_CBTUNE1_CbEnRsvd_HSH                         (0x03182A08)

  #define DDRCTLCLKCKE_CR_CBTUNE1_CbEnDllFuse_OFF                      (27)
  #define DDRCTLCLKCKE_CR_CBTUNE1_CbEnDllFuse_WID                      ( 3)
  #define DDRCTLCLKCKE_CR_CBTUNE1_CbEnDllFuse_MSK                      (0x38000000)
  #define DDRCTLCLKCKE_CR_CBTUNE1_CbEnDllFuse_MIN                      (0)
  #define DDRCTLCLKCKE_CR_CBTUNE1_CbEnDllFuse_MAX                      (7) // 0x00000007
  #define DDRCTLCLKCKE_CR_CBTUNE1_CbEnDllFuse_DEF                      (0x00000002)
  #define DDRCTLCLKCKE_CR_CBTUNE1_CbEnDllFuse_HSH                      (0x031B2A08)

  #define DDRCTLCLKCKE_CR_CBTUNE1_Spare_OFF                            (30)
  #define DDRCTLCLKCKE_CR_CBTUNE1_Spare_WID                            ( 2)
  #define DDRCTLCLKCKE_CR_CBTUNE1_Spare_MSK                            (0xC0000000)
  #define DDRCTLCLKCKE_CR_CBTUNE1_Spare_MIN                            (0)
  #define DDRCTLCLKCKE_CR_CBTUNE1_Spare_MAX                            (3) // 0x00000003
  #define DDRCTLCLKCKE_CR_CBTUNE1_Spare_DEF                            (0x00000000)
  #define DDRCTLCLKCKE_CR_CBTUNE1_Spare_HSH                            (0x021E2A08)

#define DDRCTLCLKCKE_CR_ADCCFG_REG                                     (0x00002A0C)

  #define DDRCTLCLKCKE_CR_ADCCFG_ADC_frz_OFF                           ( 0)
  #define DDRCTLCLKCKE_CR_ADCCFG_ADC_frz_WID                           ( 1)
  #define DDRCTLCLKCKE_CR_ADCCFG_ADC_frz_MSK                           (0x00000001)
  #define DDRCTLCLKCKE_CR_ADCCFG_ADC_frz_MIN                           (0)
  #define DDRCTLCLKCKE_CR_ADCCFG_ADC_frz_MAX                           (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_ADCCFG_ADC_frz_DEF                           (0x00000000)
  #define DDRCTLCLKCKE_CR_ADCCFG_ADC_frz_HSH                           (0x01002A0C)

  #define DDRCTLCLKCKE_CR_ADCCFG_ADC_en_OFF                            ( 1)
  #define DDRCTLCLKCKE_CR_ADCCFG_ADC_en_WID                            ( 1)
  #define DDRCTLCLKCKE_CR_ADCCFG_ADC_en_MSK                            (0x00000002)
  #define DDRCTLCLKCKE_CR_ADCCFG_ADC_en_MIN                            (0)
  #define DDRCTLCLKCKE_CR_ADCCFG_ADC_en_MAX                            (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_ADCCFG_ADC_en_DEF                            (0x00000000)
  #define DDRCTLCLKCKE_CR_ADCCFG_ADC_en_HSH                            (0x01012A0C)

  #define DDRCTLCLKCKE_CR_ADCCFG_ADCclkdiv_OFF                         ( 2)
  #define DDRCTLCLKCKE_CR_ADCCFG_ADCclkdiv_WID                         ( 2)
  #define DDRCTLCLKCKE_CR_ADCCFG_ADCclkdiv_MSK                         (0x0000000C)
  #define DDRCTLCLKCKE_CR_ADCCFG_ADCclkdiv_MIN                         (0)
  #define DDRCTLCLKCKE_CR_ADCCFG_ADCclkdiv_MAX                         (3) // 0x00000003
  #define DDRCTLCLKCKE_CR_ADCCFG_ADCclkdiv_DEF                         (0x00000000)
  #define DDRCTLCLKCKE_CR_ADCCFG_ADCclkdiv_HSH                         (0x02022A0C)

  #define DDRCTLCLKCKE_CR_ADCCFG_ADCstartcount_OFF                     ( 4)
  #define DDRCTLCLKCKE_CR_ADCCFG_ADCstartcount_WID                     ( 2)
  #define DDRCTLCLKCKE_CR_ADCCFG_ADCstartcount_MSK                     (0x00000030)
  #define DDRCTLCLKCKE_CR_ADCCFG_ADCstartcount_MIN                     (0)
  #define DDRCTLCLKCKE_CR_ADCCFG_ADCstartcount_MAX                     (3) // 0x00000003
  #define DDRCTLCLKCKE_CR_ADCCFG_ADCstartcount_DEF                     (0x00000000)
  #define DDRCTLCLKCKE_CR_ADCCFG_ADCstartcount_HSH                     (0x02042A0C)

  #define DDRCTLCLKCKE_CR_ADCCFG_ADCChopEn_OFF                         ( 6)
  #define DDRCTLCLKCKE_CR_ADCCFG_ADCChopEn_WID                         ( 1)
  #define DDRCTLCLKCKE_CR_ADCCFG_ADCChopEn_MSK                         (0x00000040)
  #define DDRCTLCLKCKE_CR_ADCCFG_ADCChopEn_MIN                         (0)
  #define DDRCTLCLKCKE_CR_ADCCFG_ADCChopEn_MAX                         (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_ADCCFG_ADCChopEn_DEF                         (0x00000000)
  #define DDRCTLCLKCKE_CR_ADCCFG_ADCChopEn_HSH                         (0x01062A0C)

  #define DDRCTLCLKCKE_CR_ADCCFG_Spare_OFF                             ( 7)
  #define DDRCTLCLKCKE_CR_ADCCFG_Spare_WID                             (25)
  #define DDRCTLCLKCKE_CR_ADCCFG_Spare_MSK                             (0xFFFFFF80)
  #define DDRCTLCLKCKE_CR_ADCCFG_Spare_MIN                             (0)
  #define DDRCTLCLKCKE_CR_ADCCFG_Spare_MAX                             (33554431) // 0x01FFFFFF
  #define DDRCTLCLKCKE_CR_ADCCFG_Spare_DEF                             (0x00000000)
  #define DDRCTLCLKCKE_CR_ADCCFG_Spare_HSH                             (0x19072A0C)

#define DDRCTLCLKCKE_CR_CBTUNE2_REG                                    (0x00002A10)

  #define DDRCTLCLKCKE_CR_CBTUNE2_DllCbEn_OFF                          ( 0)
  #define DDRCTLCLKCKE_CR_CBTUNE2_DllCbEn_WID                          (16)
  #define DDRCTLCLKCKE_CR_CBTUNE2_DllCbEn_MSK                          (0x0000FFFF)
  #define DDRCTLCLKCKE_CR_CBTUNE2_DllCbEn_MIN                          (0)
  #define DDRCTLCLKCKE_CR_CBTUNE2_DllCbEn_MAX                          (65535) // 0x0000FFFF
  #define DDRCTLCLKCKE_CR_CBTUNE2_DllCbEn_DEF                          (0x00000000)
  #define DDRCTLCLKCKE_CR_CBTUNE2_DllCbEn_HSH                          (0x10002A10)

  #define DDRCTLCLKCKE_CR_CBTUNE2_Spare_OFF                            (16)
  #define DDRCTLCLKCKE_CR_CBTUNE2_Spare_WID                            (16)
  #define DDRCTLCLKCKE_CR_CBTUNE2_Spare_MSK                            (0xFFFF0000)
  #define DDRCTLCLKCKE_CR_CBTUNE2_Spare_MIN                            (0)
  #define DDRCTLCLKCKE_CR_CBTUNE2_Spare_MAX                            (65535) // 0x0000FFFF
  #define DDRCTLCLKCKE_CR_CBTUNE2_Spare_DEF                            (0x00000000)
  #define DDRCTLCLKCKE_CR_CBTUNE2_Spare_HSH                            (0x10102A10)

#define DDRCTLCLKCKE_CR_PIDFTDLY_REG                                   (0x00002A18)

  #define DDRCTLCLKCKE_CR_PIDFTDLY_PiDftDelay_OFF                      ( 0)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_PiDftDelay_WID                      ( 7)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_PiDftDelay_MSK                      (0x0000007F)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_PiDftDelay_MIN                      (0)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_PiDftDelay_MAX                      (127) // 0x0000007F
  #define DDRCTLCLKCKE_CR_PIDFTDLY_PiDftDelay_DEF                      (0x00000000)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_PiDftDelay_HSH                      (0x07002A18)

  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch0PiEnOvrd_OFF                     ( 7)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch0PiEnOvrd_WID                     ( 1)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch0PiEnOvrd_MSK                     (0x00000080)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch0PiEnOvrd_MIN                     (0)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch0PiEnOvrd_MAX                     (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch0PiEnOvrd_DEF                     (0x00000000)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch0PiEnOvrd_HSH                     (0x01072A18)

  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch1PiEnOvrd_OFF                     ( 8)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch1PiEnOvrd_WID                     ( 1)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch1PiEnOvrd_MSK                     (0x00000100)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch1PiEnOvrd_MIN                     (0)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch1PiEnOvrd_MAX                     (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch1PiEnOvrd_DEF                     (0x00000000)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch1PiEnOvrd_HSH                     (0x01082A18)

  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch0PiDFTEn_OFF                      ( 9)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch0PiDFTEn_WID                      ( 1)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch0PiDFTEn_MSK                      (0x00000200)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch0PiDFTEn_MIN                      (0)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch0PiDFTEn_MAX                      (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch0PiDFTEn_DEF                      (0x00000000)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch0PiDFTEn_HSH                      (0x01092A18)

  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch1PiDFTEn_OFF                      (10)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch1PiDFTEn_WID                      ( 1)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch1PiDFTEn_MSK                      (0x00000400)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch1PiDFTEn_MIN                      (0)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch1PiDFTEn_MAX                      (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch1PiDFTEn_DEF                      (0x00000000)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Ch1PiDFTEn_HSH                      (0x010A2A18)

  #define DDRCTLCLKCKE_CR_PIDFTDLY_Spare_OFF                           (11)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Spare_WID                           ( 4)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Spare_MSK                           (0x00007800)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Spare_MIN                           (0)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Spare_MAX                           (15) // 0x0000000F
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Spare_DEF                           (0x00000000)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Spare_HSH                           (0x040B2A18)

  #define DDRCTLCLKCKE_CR_PIDFTDLY_RefPiOvrd_OFF                       (15)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_RefPiOvrd_WID                       ( 1)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_RefPiOvrd_MSK                       (0x00008000)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_RefPiOvrd_MIN                       (0)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_RefPiOvrd_MAX                       (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_PIDFTDLY_RefPiOvrd_DEF                       (0x00000000)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_RefPiOvrd_HSH                       (0x010F2A18)

  #define DDRCTLCLKCKE_CR_PIDFTDLY_Rsvd_OFF                            (16)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Rsvd_WID                            (16)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Rsvd_MSK                            (0xFFFF0000)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Rsvd_MIN                            (0)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Rsvd_MAX                            (65535) // 0x0000FFFF
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Rsvd_DEF                            (0x00000000)
  #define DDRCTLCLKCKE_CR_PIDFTDLY_Rsvd_HSH                            (0x10102A18)

#define DDRCTLCLKCKE_CR_DLLPITESTANDADC_REG                            (0x00002A1C)

  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_RunTest_OFF                  ( 0)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_RunTest_WID                  ( 1)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_RunTest_MSK                  (0x00000001)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_RunTest_MIN                  (0)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_RunTest_MAX                  (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_RunTest_DEF                  (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_RunTest_HSH                  (0x01002A1C)

  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_Load_OFF                     ( 1)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_Load_WID                     ( 1)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_Load_MSK                     (0x00000002)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_Load_MIN                     (0)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_Load_MAX                     (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_Load_DEF                     (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_Load_HSH                     (0x01012A1C)

  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ModeHVM_OFF                  ( 2)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ModeHVM_WID                  ( 1)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ModeHVM_MSK                  (0x00000004)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ModeHVM_MIN                  (0)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ModeHVM_MAX                  (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ModeHVM_DEF                  (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ModeHVM_HSH                  (0x01022A1C)

  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ModeDV_OFF                   ( 3)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ModeDV_WID                   ( 1)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ModeDV_MSK                   (0x00000008)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ModeDV_MIN                   (0)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ModeDV_MAX                   (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ModeDV_DEF                   (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ModeDV_HSH                   (0x01032A1C)

  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_CalCfdl_OFF                  ( 4)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_CalCfdl_WID                  ( 1)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_CalCfdl_MSK                  (0x00000010)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_CalCfdl_MIN                  (0)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_CalCfdl_MAX                  (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_CalCfdl_DEF                  (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_CalCfdl_HSH                  (0x01042A1C)

  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_LoadCount_OFF                ( 5)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_LoadCount_WID                (10)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_LoadCount_MSK                (0x00007FE0)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_LoadCount_MIN                (0)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_LoadCount_MAX                (1023) // 0x000003FF
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_LoadCount_DEF                (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_LoadCount_HSH                (0x0A052A1C)

  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_CountStatus_OFF              (15)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_CountStatus_WID              (10)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_CountStatus_MSK              (0x01FF8000)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_CountStatus_MIN              (0)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_CountStatus_MAX              (1023) // 0x000003FF
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_CountStatus_DEF              (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_CountStatus_HSH              (0x0A0F2A1C)

  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ModeADC_OFF                  (25)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ModeADC_WID                  ( 1)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ModeADC_MSK                  (0x02000000)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ModeADC_MIN                  (0)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ModeADC_MAX                  (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ModeADC_DEF                  (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ModeADC_HSH                  (0x01192A1C)

  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCClkDiv_OFF                (26)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCClkDiv_WID                ( 2)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCClkDiv_MSK                (0x0C000000)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCClkDiv_MIN                (0)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCClkDiv_MAX                (3) // 0x00000003
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCClkDiv_DEF                (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCClkDiv_HSH                (0x021A2A1C)

  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCDdrChanSel_OFF            (28)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCDdrChanSel_WID            ( 1)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCDdrChanSel_MSK            (0x10000000)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCDdrChanSel_MIN            (0)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCDdrChanSel_MAX            (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCDdrChanSel_DEF            (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCDdrChanSel_HSH            (0x011C2A1C)

  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCChopEn_OFF                (29)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCChopEn_WID                ( 1)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCChopEn_MSK                (0x20000000)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCChopEn_MIN                (0)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCChopEn_MAX                (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCChopEn_DEF                (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCChopEn_HSH                (0x011D2A1C)

  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCDone_OFF                  (30)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCDone_WID                  ( 1)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCDone_MSK                  (0x40000000)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCDone_MIN                  (0)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCDone_MAX                  (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCDone_DEF                  (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_ADCDone_HSH                  (0x011E2A1C)

  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_OFF         (31)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_WID         ( 1)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MSK         (0x80000000)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MIN         (0)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_MAX         (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_DEF         (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLPITESTANDADC_PhaseDrvPwrSavOn_HSH         (0x011F2A1C)

#define DDRCTLCLKCKE_CR_DLLSTATUS_REG                                  (0x00002A20)

  #define DDRCTLCLKCKE_CR_DLLSTATUS_DetrmLockStat_OFF                  ( 0)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_DetrmLockStat_WID                  ( 1)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_DetrmLockStat_MSK                  (0x00000001)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_DetrmLockStat_MIN                  (0)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_DetrmLockStat_MAX                  (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_DLLSTATUS_DetrmLockStat_DEF                  (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_DetrmLockStat_HSH                  (0x01002A20)

  #define DDRCTLCLKCKE_CR_DLLSTATUS_FuncLockStat_OFF                   ( 1)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_FuncLockStat_WID                   ( 1)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_FuncLockStat_MSK                   (0x00000002)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_FuncLockStat_MIN                   (0)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_FuncLockStat_MAX                   (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_DLLSTATUS_FuncLockStat_DEF                   (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_FuncLockStat_HSH                   (0x01012A20)

  #define DDRCTLCLKCKE_CR_DLLSTATUS_Lock_OFF                           ( 2)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_Lock_WID                           ( 1)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_Lock_MSK                           (0x00000004)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_Lock_MIN                           (0)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_Lock_MAX                           (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_DLLSTATUS_Lock_DEF                           (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_Lock_HSH                           (0x01022A20)

  #define DDRCTLCLKCKE_CR_DLLSTATUS_Timeout_OFF                        ( 3)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_Timeout_WID                        ( 1)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_Timeout_MSK                        (0x00000008)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_Timeout_MIN                        (0)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_Timeout_MAX                        (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_DLLSTATUS_Timeout_DEF                        (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_Timeout_HSH                        (0x01032A20)

  #define DDRCTLCLKCKE_CR_DLLSTATUS_DllReset_OFF                       ( 4)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_DllReset_WID                       ( 1)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_DllReset_MSK                       (0x00000010)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_DllReset_MIN                       (0)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_DllReset_MAX                       (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_DLLSTATUS_DllReset_DEF                       (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_DllReset_HSH                       (0x01042A20)

  #define DDRCTLCLKCKE_CR_DLLSTATUS_LongLockStat_OFF                   ( 5)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_LongLockStat_WID                   ( 1)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_LongLockStat_MSK                   (0x00000020)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_LongLockStat_MIN                   (0)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_LongLockStat_MAX                   (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_DLLSTATUS_LongLockStat_DEF                   (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_LongLockStat_HSH                   (0x01052A20)

  #define DDRCTLCLKCKE_CR_DLLSTATUS_EarlyLockStat_OFF                  ( 6)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_EarlyLockStat_WID                  ( 1)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_EarlyLockStat_MSK                  (0x00000040)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_EarlyLockStat_MIN                  (0)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_EarlyLockStat_MAX                  (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_DLLSTATUS_EarlyLockStat_DEF                  (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_EarlyLockStat_HSH                  (0x01062A20)

  #define DDRCTLCLKCKE_CR_DLLSTATUS_NormalMode_NotWkLock_OFF           ( 7)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_NormalMode_NotWkLock_WID           ( 1)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_NormalMode_NotWkLock_MSK           (0x00000080)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_NormalMode_NotWkLock_MIN           (0)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_NormalMode_NotWkLock_MAX           (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_DLLSTATUS_NormalMode_NotWkLock_DEF           (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_NormalMode_NotWkLock_HSH           (0x01072A20)

  #define DDRCTLCLKCKE_CR_DLLSTATUS_ADCout_OFF                         ( 8)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_ADCout_WID                         (10)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_ADCout_MSK                         (0x0003FF00)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_ADCout_MIN                         (0)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_ADCout_MAX                         (1023) // 0x000003FF
  #define DDRCTLCLKCKE_CR_DLLSTATUS_ADCout_DEF                         (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_ADCout_HSH                         (0x0A082A20)

  #define DDRCTLCLKCKE_CR_DLLSTATUS_ADCStatus_OFF                      (18)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_ADCStatus_WID                      ( 1)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_ADCStatus_MSK                      (0x00040000)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_ADCStatus_MIN                      (0)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_ADCStatus_MAX                      (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_DLLSTATUS_ADCStatus_DEF                      (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_ADCStatus_HSH                      (0x01122A20)

  #define DDRCTLCLKCKE_CR_DLLSTATUS_pilags_OFF                         (19)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_pilags_WID                         ( 1)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_pilags_MSK                         (0x00080000)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_pilags_MIN                         (0)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_pilags_MAX                         (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_DLLSTATUS_pilags_DEF                         (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_pilags_HSH                         (0x01132A20)

  #define DDRCTLCLKCKE_CR_DLLSTATUS_spare_OFF                          (20)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_spare_WID                          (12)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_spare_MSK                          (0xFFF00000)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_spare_MIN                          (0)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_spare_MAX                          (4095) // 0x00000FFF
  #define DDRCTLCLKCKE_CR_DLLSTATUS_spare_DEF                          (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLSTATUS_spare_HSH                          (0x0C142A20)

#define DDRCTLCLKCKE_CR_DLLDCMCTL_REG                                  (0x00002A24)

  #define DDRCTLCLKCKE_CR_DLLDCMCTL_start_OFF                          ( 0)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_start_WID                          ( 1)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_start_MSK                          (0x00000001)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_start_MIN                          (0)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_start_MAX                          (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_start_DEF                          (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_start_HSH                          (0x01002A24)

  #define DDRCTLCLKCKE_CR_DLLDCMCTL_clken_OFF                          ( 1)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_clken_WID                          ( 1)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_clken_MSK                          (0x00000002)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_clken_MIN                          (0)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_clken_MAX                          (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_clken_DEF                          (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_clken_HSH                          (0x01012A24)

  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dcm_dccctl_en_OFF                  ( 2)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dcm_dccctl_en_WID                  ( 1)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dcm_dccctl_en_MSK                  (0x00000004)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dcm_dccctl_en_MIN                  (0)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dcm_dccctl_en_MAX                  (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dcm_dccctl_en_DEF                  (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dcm_dccctl_en_HSH                  (0x01022A24)

  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dccctl_OFF                         ( 3)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dccctl_WID                         ( 4)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dccctl_MSK                         (0x00000078)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dccctl_MIN                         (0)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dccctl_MAX                         (15) // 0x0000000F
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dccctl_DEF                         (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dccctl_HSH                         (0x04032A24)

  #define DDRCTLCLKCKE_CR_DLLDCMCTL_duration_OFF                       ( 7)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_duration_WID                       ( 3)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_duration_MSK                       (0x00000380)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_duration_MIN                       (0)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_duration_MAX                       (7) // 0x00000007
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_duration_DEF                       (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_duration_HSH                       (0x03072A24)

  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dcm_done_OFF                       (10)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dcm_done_WID                       ( 1)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dcm_done_MSK                       (0x00000400)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dcm_done_MIN                       (0)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dcm_done_MAX                       (1) // 0x00000001
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dcm_done_DEF                       (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dcm_done_HSH                       (0x010A2A24)

  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dcm_results_OFF                    (11)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dcm_results_WID                    (15)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dcm_results_MSK                    (0x03FFF800)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dcm_results_MIN                    (0)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dcm_results_MAX                    (32767) // 0x00007FFF
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dcm_results_DEF                    (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_dcm_results_HSH                    (0x0F0B2A24)

  #define DDRCTLCLKCKE_CR_DLLDCMCTL_spare0_OFF                         (26)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_spare0_WID                         ( 6)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_spare0_MSK                         (0xFC000000)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_spare0_MIN                         (0)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_spare0_MAX                         (63) // 0x0000003F
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_spare0_DEF                         (0x00000000)
  #define DDRCTLCLKCKE_CR_DLLDCMCTL_spare0_HSH                         (0x061A2A24)

#define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_REG                           (0x00002B00)

  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Target_OFF                  ( 0)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Target_WID                  ( 7)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Target_MSK                  (0x0000007F)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Target_MIN                  (0)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Target_MAX                  (127) // 0x0000007F
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Target_DEF                  (0x0000004C)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Target_HSH                  (0x07002B00)

  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Panic_OFF                   ( 7)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Panic_WID                   ( 5)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Panic_MSK                   (0x00000F80)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Panic_MIN                   (0)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Panic_MAX                   (31) // 0x0000001F
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Panic_DEF                   (0x00000010)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Panic_HSH                   (0x05072B00)

  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_OFF          (12)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_WID          ( 1)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MSK          (0x00001000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MIN          (0)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MAX          (1) // 0x00000001
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_DEF          (0x00000000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_HSH          (0x010C2B00)

  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_OFF              (13)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_WID              ( 1)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MSK              (0x00002000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MIN              (0)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MAX              (1) // 0x00000001
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_DEF              (0x00000000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_HSH              (0x010D2B00)

  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_OFF             (14)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_WID             ( 3)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MSK             (0x0001C000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MIN             (0)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MAX             (7) // 0x00000007
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_DEF             (0x00000000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_HSH             (0x030E2B00)

  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_OFF         (17)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_WID         ( 1)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_MSK         (0x00020000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_MIN         (0)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_MAX         (1) // 0x00000001
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_DEF         (0x00000000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_HSH         (0x01112B00)

  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_OFF       (18)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_WID       ( 1)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_MSK       (0x00040000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_MIN       (0)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_MAX       (1) // 0x00000001
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_DEF       (0x00000000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_HSH       (0x01122B00)

  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Spare_OFF                   (19)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Spare_WID                   ( 1)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Spare_MSK                   (0x00080000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Spare_MIN                   (0)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Spare_MAX                   (1) // 0x00000001
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Spare_DEF                   (0x00000000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Spare_HSH                   (0x01132B00)

  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_EnVttOdt_OFF                (20)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_EnVttOdt_WID                ( 1)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_EnVttOdt_MSK                (0x00100000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_EnVttOdt_MIN                (0)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_EnVttOdt_MAX                (1) // 0x00000001
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_EnVttOdt_DEF                (0x00000000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_EnVttOdt_HSH                (0x01142B00)

  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_OFF (21)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_WID ( 1)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_MSK (0x00200000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_MIN (0)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_MAX (1) // 0x00000001
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_DEF (0x00000001)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_HSH (0x01152B00)

  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_OFF       (22)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_WID       ( 1)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_MSK       (0x00400000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_MIN       (0)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_MAX       (1) // 0x00000001
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_DEF       (0x00000000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_HSH       (0x01162B00)

  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_OFF           (23)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_WID           ( 1)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_MSK           (0x00800000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_MIN           (0)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_MAX           (1) // 0x00000001
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_DEF           (0x00000001)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_HSH           (0x01172B00)

  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_OFF           (24)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_WID           ( 1)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_MSK           (0x01000000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_MIN           (0)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_MAX           (1) // 0x00000001
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_DEF           (0x00000001)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_HSH           (0x01182B00)

  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Disable2Vt_OFF              (25)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Disable2Vt_WID              ( 1)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Disable2Vt_MSK              (0x02000000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Disable2Vt_MIN              (0)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Disable2Vt_MAX              (1) // 0x00000001
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Disable2Vt_DEF              (0x00000000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_Disable2Vt_HSH              (0x01192B00)

  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_OfstOvrd_OFF                (26)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_OfstOvrd_WID                ( 6)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_OfstOvrd_MSK                (0xFC000000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_OfstOvrd_MIN                (0)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_OfstOvrd_MAX                (63) // 0x0000003F
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_OfstOvrd_DEF                (0x00000000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_OfstOvrd_HSH                (0x061A2B00)

#define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_REG                          (0x00002B04)

  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_OFF    ( 0)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_WID    ( 1)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_MSK    (0x00000001)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_MIN    (0)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_MAX    (1) // 0x00000001
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_DEF    (0x00000000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_HSH    (0x01002B04)

  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_OFF ( 1)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_WID ( 7)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_MSK (0x000000FE)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_MIN (0)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_MAX (127) // 0x0000007F
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_DEF (0x00000034)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_HSH (0x07012B04)

  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_OFF     ( 8)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_WID     ( 1)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_MSK     (0x00000100)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_MIN     (0)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_MAX     (1) // 0x00000001
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_DEF     (0x00000000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_HSH     (0x01082B04)

  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_Spare_OFF                  ( 9)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_Spare_WID                  (23)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_Spare_MSK                  (0xFFFFFE00)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_Spare_MIN                  (0)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_Spare_MAX                  (8388607) // 0x007FFFFF
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_Spare_DEF                  (0x00000000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_Spare_HSH                  (0x17092B04)

#define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL3_REG                          (0x00002B08)

  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL3_View_OFF                   ( 0)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL3_View_WID                   ( 6)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL3_View_MSK                   (0x0000003F)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL3_View_MIN                   (0)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL3_View_MAX                   (63) // 0x0000003F
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL3_View_DEF                   (0x00000000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL3_View_HSH                   (0x06002B08)

  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL3_Spare_OFF                  ( 6)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL3_Spare_WID                  (26)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL3_Spare_MSK                  (0xFFFFFFC0)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL3_Spare_MIN                  (0)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL3_Spare_MAX                  (67108863) // 0x03FFFFFF
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL3_Spare_DEF                  (0x00000000)
  #define DDRVTTTOP0_CR_DDRCRVTTGENCONTROL3_Spare_HSH                  (0x1A062B08)

#define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_REG                       (0x00002B80)

  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Target_OFF              ( 0)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Target_WID              ( 7)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Target_MSK              (0x0000007F)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Target_MIN              (0)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Target_MAX              (127) // 0x0000007F
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Target_DEF              (0x0000004C)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Target_HSH              (0x07002B80)

  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Panic_OFF               ( 7)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Panic_WID               ( 5)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Panic_MSK               (0x00000F80)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Panic_MIN               (0)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Panic_MAX               (31) // 0x0000001F
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Panic_DEF               (0x00000010)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Panic_HSH               (0x05072B80)

  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_OFF      (12)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_WID      ( 1)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MSK      (0x00001000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MIN      (0)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MAX      (1) // 0x00000001
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_DEF      (0x00000000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_HSH      (0x010C2B80)

  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_OFF          (13)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_WID          ( 1)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MSK          (0x00002000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MIN          (0)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MAX          (1) // 0x00000001
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_DEF          (0x00000000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_HSH          (0x010D2B80)

  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_OFF         (14)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_WID         ( 3)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MSK         (0x0001C000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MIN         (0)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MAX         (7) // 0x00000007
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_DEF         (0x00000000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_HSH         (0x030E2B80)

  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_OFF     (17)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_WID     ( 1)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_MSK     (0x00020000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_MIN     (0)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_MAX     (1) // 0x00000001
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_DEF     (0x00000000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_HSH     (0x01112B80)

  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_OFF   (18)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_WID   ( 1)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_MSK   (0x00040000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_MIN   (0)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_MAX   (1) // 0x00000001
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_DEF   (0x00000000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_HSH   (0x01122B80)

  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Spare_OFF               (19)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Spare_WID               ( 1)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Spare_MSK               (0x00080000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Spare_MIN               (0)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Spare_MAX               (1) // 0x00000001
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Spare_DEF               (0x00000000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Spare_HSH               (0x01132B80)

  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_EnVttOdt_OFF            (20)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_EnVttOdt_WID            ( 1)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_EnVttOdt_MSK            (0x00100000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_EnVttOdt_MIN            (0)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_EnVttOdt_MAX            (1) // 0x00000001
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_EnVttOdt_DEF            (0x00000000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_EnVttOdt_HSH            (0x01142B80)

  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_OFF (21)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_WID ( 1)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_MSK (0x00200000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_MIN (0)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_MAX (1) // 0x00000001
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_DEF (0x00000001)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_HSH (0x01152B80)

  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_OFF   (22)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_WID   ( 1)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_MSK   (0x00400000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_MIN   (0)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_MAX   (1) // 0x00000001
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_DEF   (0x00000000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_HSH   (0x01162B80)

  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_OFF       (23)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_WID       ( 1)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_MSK       (0x00800000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_MIN       (0)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_MAX       (1) // 0x00000001
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_DEF       (0x00000001)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_HSH       (0x01172B80)

  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_OFF       (24)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_WID       ( 1)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_MSK       (0x01000000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_MIN       (0)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_MAX       (1) // 0x00000001
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_DEF       (0x00000001)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_HSH       (0x01182B80)

  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Disable2Vt_OFF          (25)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Disable2Vt_WID          ( 1)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Disable2Vt_MSK          (0x02000000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Disable2Vt_MIN          (0)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Disable2Vt_MAX          (1) // 0x00000001
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Disable2Vt_DEF          (0x00000000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_Disable2Vt_HSH          (0x01192B80)

  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_OfstOvrd_OFF            (26)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_OfstOvrd_WID            ( 6)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_OfstOvrd_MSK            (0xFC000000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_OfstOvrd_MIN            (0)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_OfstOvrd_MAX            (63) // 0x0000003F
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_OfstOvrd_DEF            (0x00000000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_OfstOvrd_HSH            (0x061A2B80)

#define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_REG                      (0x00002B84)

  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_OFF ( 0)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_WID ( 1)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_MSK (0x00000001)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_MIN (0)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_MAX (1) // 0x00000001
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_DEF (0x00000000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_HSH (0x01002B84)

  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_OFF ( 1)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_WID ( 7)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_MSK (0x000000FE)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_MIN (0)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_MAX (127) // 0x0000007F
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_DEF (0x00000034)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_HSH (0x07012B84)

  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_OFF ( 8)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_WID ( 1)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_MSK (0x00000100)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_MIN (0)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_MAX (1) // 0x00000001
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_DEF (0x00000000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_HSH (0x01082B84)

  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_Spare_OFF              ( 9)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_Spare_WID              (23)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_Spare_MSK              (0xFFFFFE00)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_Spare_MIN              (0)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_Spare_MAX              (8388607) // 0x007FFFFF
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_Spare_DEF              (0x00000000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_Spare_HSH              (0x17092B84)

#define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL3_REG                      (0x00002B88)

  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL3_View_OFF               ( 0)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL3_View_WID               ( 6)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL3_View_MSK               (0x0000003F)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL3_View_MIN               (0)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL3_View_MAX               (63) // 0x0000003F
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL3_View_DEF               (0x00000000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL3_View_HSH               (0x06002B88)

  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL3_Spare_OFF              ( 6)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL3_Spare_WID              (26)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL3_Spare_MSK              (0xFFFFFFC0)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL3_Spare_MIN              (0)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL3_Spare_MAX              (67108863) // 0x03FFFFFF
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL3_Spare_DEF              (0x00000000)
  #define DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL3_Spare_HSH              (0x1A062B88)

#define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_REG                        (0x00002C00)

  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Target_OFF               ( 0)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Target_WID               ( 7)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Target_MSK               (0x0000007F)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Target_MIN               (0)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Target_MAX               (127) // 0x0000007F
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Target_DEF               (0x0000004C)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Target_HSH               (0x07002C00)

  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Panic_OFF                ( 7)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Panic_WID                ( 5)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Panic_MSK                (0x00000F80)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Panic_MIN                (0)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Panic_MAX                (31) // 0x0000001F
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Panic_DEF                (0x00000010)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Panic_HSH                (0x05072C00)

  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_OFF       (12)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_WID       ( 1)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MSK       (0x00001000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MIN       (0)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MAX       (1) // 0x00000001
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_DEF       (0x00000000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_HSH       (0x010C2C00)

  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_OFF           (13)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_WID           ( 1)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MSK           (0x00002000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MIN           (0)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MAX           (1) // 0x00000001
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_DEF           (0x00000000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_HSH           (0x010D2C00)

  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_OFF          (14)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_WID          ( 3)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MSK          (0x0001C000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MIN          (0)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MAX          (7) // 0x00000007
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_DEF          (0x00000000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_HSH          (0x030E2C00)

  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_OFF      (17)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_WID      ( 1)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_MSK      (0x00020000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_MIN      (0)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_MAX      (1) // 0x00000001
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_DEF      (0x00000000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_HSH      (0x01112C00)

  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_OFF    (18)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_WID    ( 1)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_MSK    (0x00040000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_MIN    (0)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_MAX    (1) // 0x00000001
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_DEF    (0x00000000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_HSH    (0x01122C00)

  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Spare_OFF                (19)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Spare_WID                ( 1)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Spare_MSK                (0x00080000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Spare_MIN                (0)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Spare_MAX                (1) // 0x00000001
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Spare_DEF                (0x00000000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Spare_HSH                (0x01132C00)

  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_EnVttOdt_OFF             (20)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_EnVttOdt_WID             ( 1)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_EnVttOdt_MSK             (0x00100000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_EnVttOdt_MIN             (0)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_EnVttOdt_MAX             (1) // 0x00000001
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_EnVttOdt_DEF             (0x00000000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_EnVttOdt_HSH             (0x01142C00)

  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_OFF (21)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_WID ( 1)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_MSK (0x00200000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_MIN (0)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_MAX (1) // 0x00000001
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_DEF (0x00000001)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_HSH (0x01152C00)

  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_OFF    (22)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_WID    ( 1)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_MSK    (0x00400000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_MIN    (0)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_MAX    (1) // 0x00000001
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_DEF    (0x00000000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_HSH    (0x01162C00)

  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_OFF        (23)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_WID        ( 1)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_MSK        (0x00800000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_MIN        (0)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_MAX        (1) // 0x00000001
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_DEF        (0x00000001)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_HSH        (0x01172C00)

  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_OFF        (24)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_WID        ( 1)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_MSK        (0x01000000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_MIN        (0)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_MAX        (1) // 0x00000001
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_DEF        (0x00000001)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_HSH        (0x01182C00)

  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Disable2Vt_OFF           (25)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Disable2Vt_WID           ( 1)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Disable2Vt_MSK           (0x02000000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Disable2Vt_MIN           (0)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Disable2Vt_MAX           (1) // 0x00000001
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Disable2Vt_DEF           (0x00000000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_Disable2Vt_HSH           (0x01192C00)

  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_OfstOvrd_OFF             (26)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_OfstOvrd_WID             ( 6)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_OfstOvrd_MSK             (0xFC000000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_OfstOvrd_MIN             (0)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_OfstOvrd_MAX             (63) // 0x0000003F
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_OfstOvrd_DEF             (0x00000000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_OfstOvrd_HSH             (0x061A2C00)

#define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_REG                       (0x00002C04)

  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_OFF ( 0)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_WID ( 1)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_MSK (0x00000001)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_MIN (0)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_MAX (1) // 0x00000001
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_DEF (0x00000000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_HSH (0x01002C04)

  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_OFF ( 1)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_WID ( 7)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_MSK (0x000000FE)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_MIN (0)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_MAX (127) // 0x0000007F
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_DEF (0x00000034)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_HSH (0x07012C04)

  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_OFF  ( 8)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_WID  ( 1)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_MSK  (0x00000100)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_MIN  (0)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_MAX  (1) // 0x00000001
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_DEF  (0x00000000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_HSH  (0x01082C04)

  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_Spare_OFF               ( 9)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_Spare_WID               (23)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_Spare_MSK               (0xFFFFFE00)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_Spare_MIN               (0)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_Spare_MAX               (8388607) // 0x007FFFFF
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_Spare_DEF               (0x00000000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_Spare_HSH               (0x17092C04)

#define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL3_REG                       (0x00002C08)

  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL3_View_OFF                ( 0)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL3_View_WID                ( 6)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL3_View_MSK                (0x0000003F)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL3_View_MIN                (0)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL3_View_MAX                (63) // 0x0000003F
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL3_View_DEF                (0x00000000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL3_View_HSH                (0x06002C08)

  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL3_Spare_OFF               ( 6)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL3_Spare_WID               (26)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL3_Spare_MSK               (0xFFFFFFC0)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL3_Spare_MIN               (0)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL3_Spare_MAX               (67108863) // 0x03FFFFFF
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL3_Spare_DEF               (0x00000000)
  #define DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL3_Spare_HSH               (0x1A062C08)

#define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_REG                           (0x00002C80)

  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Target_OFF                  ( 0)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Target_WID                  ( 7)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Target_MSK                  (0x0000007F)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Target_MIN                  (0)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Target_MAX                  (127) // 0x0000007F
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Target_DEF                  (0x0000004C)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Target_HSH                  (0x07002C80)

  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Panic_OFF                   ( 7)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Panic_WID                   ( 5)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Panic_MSK                   (0x00000F80)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Panic_MIN                   (0)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Panic_MAX                   (31) // 0x0000001F
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Panic_DEF                   (0x00000010)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Panic_HSH                   (0x05072C80)

  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_OFF          (12)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_WID          ( 1)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MSK          (0x00001000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MIN          (0)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MAX          (1) // 0x00000001
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_DEF          (0x00000000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_HSH          (0x010C2C80)

  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_OFF              (13)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_WID              ( 1)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MSK              (0x00002000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MIN              (0)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MAX              (1) // 0x00000001
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_DEF              (0x00000000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_HSH              (0x010D2C80)

  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_OFF             (14)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_WID             ( 3)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MSK             (0x0001C000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MIN             (0)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MAX             (7) // 0x00000007
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_DEF             (0x00000000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_ViewOfstsel_HSH             (0x030E2C80)

  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_OFF         (17)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_WID         ( 1)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_MSK         (0x00020000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_MIN         (0)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_MAX         (1) // 0x00000001
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_DEF         (0x00000000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_HSH         (0x01112C80)

  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_OFF       (18)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_WID       ( 1)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_MSK       (0x00040000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_MIN       (0)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_MAX       (1) // 0x00000001
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_DEF       (0x00000000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_HSH       (0x01122C80)

  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Spare_OFF                   (19)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Spare_WID                   ( 1)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Spare_MSK                   (0x00080000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Spare_MIN                   (0)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Spare_MAX                   (1) // 0x00000001
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Spare_DEF                   (0x00000000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Spare_HSH                   (0x01132C80)

  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_EnVttOdt_OFF                (20)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_EnVttOdt_WID                ( 1)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_EnVttOdt_MSK                (0x00100000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_EnVttOdt_MIN                (0)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_EnVttOdt_MAX                (1) // 0x00000001
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_EnVttOdt_DEF                (0x00000000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_EnVttOdt_HSH                (0x01142C80)

  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_OFF (21)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_WID ( 1)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_MSK (0x00200000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_MIN (0)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_MAX (1) // 0x00000001
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_DEF (0x00000001)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_HSH (0x01152C80)

  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_OFF       (22)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_WID       ( 1)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_MSK       (0x00400000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_MIN       (0)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_MAX       (1) // 0x00000001
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_DEF       (0x00000000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_HSH       (0x01162C80)

  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_OFF           (23)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_WID           ( 1)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_MSK           (0x00800000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_MIN           (0)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_MAX           (1) // 0x00000001
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_DEF           (0x00000001)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_HSH           (0x01172C80)

  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_OFF           (24)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_WID           ( 1)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_MSK           (0x01000000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_MIN           (0)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_MAX           (1) // 0x00000001
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_DEF           (0x00000001)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_HSH           (0x01182C80)

  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Disable2Vt_OFF              (25)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Disable2Vt_WID              ( 1)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Disable2Vt_MSK              (0x02000000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Disable2Vt_MIN              (0)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Disable2Vt_MAX              (1) // 0x00000001
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Disable2Vt_DEF              (0x00000000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_Disable2Vt_HSH              (0x01192C80)

  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_OfstOvrd_OFF                (26)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_OfstOvrd_WID                ( 6)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_OfstOvrd_MSK                (0xFC000000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_OfstOvrd_MIN                (0)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_OfstOvrd_MAX                (63) // 0x0000003F
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_OfstOvrd_DEF                (0x00000000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_OfstOvrd_HSH                (0x061A2C80)

#define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_REG                          (0x00002C84)

  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_OFF    ( 0)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_WID    ( 1)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_MSK    (0x00000001)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_MIN    (0)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_MAX    (1) // 0x00000001
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_DEF    (0x00000000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_HSH    (0x01002C84)

  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_OFF ( 1)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_WID ( 7)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_MSK (0x000000FE)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_MIN (0)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_MAX (127) // 0x0000007F
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_DEF (0x00000034)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_HSH (0x07012C84)

  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_OFF     ( 8)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_WID     ( 1)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_MSK     (0x00000100)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_MIN     (0)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_MAX     (1) // 0x00000001
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_DEF     (0x00000000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_HSH     (0x01082C84)

  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_Spare_OFF                  ( 9)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_Spare_WID                  (23)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_Spare_MSK                  (0xFFFFFE00)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_Spare_MIN                  (0)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_Spare_MAX                  (8388607) // 0x007FFFFF
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_Spare_DEF                  (0x00000000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_Spare_HSH                  (0x17092C84)

#define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL3_REG                          (0x00002C88)

  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL3_View_OFF                   ( 0)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL3_View_WID                   ( 6)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL3_View_MSK                   (0x0000003F)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL3_View_MIN                   (0)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL3_View_MAX                   (63) // 0x0000003F
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL3_View_DEF                   (0x00000000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL3_View_HSH                   (0x06002C88)

  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL3_Spare_OFF                  ( 6)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL3_Spare_WID                  (26)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL3_Spare_MSK                  (0xFFFFFFC0)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL3_Spare_MIN                  (0)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL3_Spare_MAX                  (67108863) // 0x03FFFFFF
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL3_Spare_DEF                  (0x00000000)
  #define DDRVTTBOT0_CR_DDRCRVTTGENCONTROL3_Spare_HSH                  (0x1A062C88)

#define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_REG                           (0x00002D00)

  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Target_OFF                  ( 0)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Target_WID                  ( 7)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Target_MSK                  (0x0000007F)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Target_MIN                  (0)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Target_MAX                  (127) // 0x0000007F
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Target_DEF                  (0x0000004C)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Target_HSH                  (0x07002D00)

  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Panic_OFF                   ( 7)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Panic_WID                   ( 5)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Panic_MSK                   (0x00000F80)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Panic_MIN                   (0)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Panic_MAX                   (31) // 0x0000001F
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Panic_DEF                   (0x00000010)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Panic_HSH                   (0x05072D00)

  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_OFF          (12)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_WID          ( 1)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MSK          (0x00001000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MIN          (0)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MAX          (1) // 0x00000001
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_DEF          (0x00000000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_HSH          (0x010C2D00)

  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_OFF              (13)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_WID              ( 1)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MSK              (0x00002000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MIN              (0)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MAX              (1) // 0x00000001
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_DEF              (0x00000000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_HSH              (0x010D2D00)

  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_OFF             (14)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_WID             ( 3)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MSK             (0x0001C000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MIN             (0)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MAX             (7) // 0x00000007
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_DEF             (0x00000000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_HSH             (0x030E2D00)

  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_OFF         (17)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_WID         ( 1)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_MSK         (0x00020000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_MIN         (0)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_MAX         (1) // 0x00000001
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_DEF         (0x00000000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_HSH         (0x01112D00)

  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_OFF       (18)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_WID       ( 1)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_MSK       (0x00040000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_MIN       (0)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_MAX       (1) // 0x00000001
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_DEF       (0x00000000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_HSH       (0x01122D00)

  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Spare_OFF                   (19)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Spare_WID                   ( 1)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Spare_MSK                   (0x00080000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Spare_MIN                   (0)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Spare_MAX                   (1) // 0x00000001
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Spare_DEF                   (0x00000000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Spare_HSH                   (0x01132D00)

  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_EnVttOdt_OFF                (20)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_EnVttOdt_WID                ( 1)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_EnVttOdt_MSK                (0x00100000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_EnVttOdt_MIN                (0)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_EnVttOdt_MAX                (1) // 0x00000001
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_EnVttOdt_DEF                (0x00000000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_EnVttOdt_HSH                (0x01142D00)

  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_OFF (21)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_WID ( 1)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_MSK (0x00200000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_MIN (0)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_MAX (1) // 0x00000001
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_DEF (0x00000001)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_HSH (0x01152D00)

  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_OFF       (22)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_WID       ( 1)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_MSK       (0x00400000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_MIN       (0)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_MAX       (1) // 0x00000001
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_DEF       (0x00000000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_HSH       (0x01162D00)

  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_OFF           (23)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_WID           ( 1)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_MSK           (0x00800000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_MIN           (0)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_MAX           (1) // 0x00000001
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_DEF           (0x00000001)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_HSH           (0x01172D00)

  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_OFF           (24)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_WID           ( 1)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_MSK           (0x01000000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_MIN           (0)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_MAX           (1) // 0x00000001
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_DEF           (0x00000001)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_HSH           (0x01182D00)

  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Disable2Vt_OFF              (25)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Disable2Vt_WID              ( 1)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Disable2Vt_MSK              (0x02000000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Disable2Vt_MIN              (0)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Disable2Vt_MAX              (1) // 0x00000001
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Disable2Vt_DEF              (0x00000000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_Disable2Vt_HSH              (0x01192D00)

  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_OfstOvrd_OFF                (26)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_OfstOvrd_WID                ( 6)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_OfstOvrd_MSK                (0xFC000000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_OfstOvrd_MIN                (0)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_OfstOvrd_MAX                (63) // 0x0000003F
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_OfstOvrd_DEF                (0x00000000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_OfstOvrd_HSH                (0x061A2D00)

#define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_REG                          (0x00002D04)

  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_OFF    ( 0)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_WID    ( 1)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_MSK    (0x00000001)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_MIN    (0)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_MAX    (1) // 0x00000001
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_DEF    (0x00000000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_HSH    (0x01002D04)

  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_OFF ( 1)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_WID ( 7)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_MSK (0x000000FE)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_MIN (0)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_MAX (127) // 0x0000007F
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_DEF (0x00000034)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_HSH (0x07012D04)

  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_OFF     ( 8)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_WID     ( 1)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_MSK     (0x00000100)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_MIN     (0)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_MAX     (1) // 0x00000001
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_DEF     (0x00000000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_HSH     (0x01082D04)

  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_Spare_OFF                  ( 9)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_Spare_WID                  (23)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_Spare_MSK                  (0xFFFFFE00)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_Spare_MIN                  (0)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_Spare_MAX                  (8388607) // 0x007FFFFF
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_Spare_DEF                  (0x00000000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_Spare_HSH                  (0x17092D04)

#define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL3_REG                          (0x00002D08)

  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL3_View_OFF                   ( 0)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL3_View_WID                   ( 6)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL3_View_MSK                   (0x0000003F)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL3_View_MIN                   (0)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL3_View_MAX                   (63) // 0x0000003F
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL3_View_DEF                   (0x00000000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL3_View_HSH                   (0x06002D08)

  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL3_Spare_OFF                  ( 6)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL3_Spare_WID                  (26)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL3_Spare_MSK                  (0xFFFFFFC0)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL3_Spare_MIN                  (0)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL3_Spare_MAX                  (67108863) // 0x03FFFFFF
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL3_Spare_DEF                  (0x00000000)
  #define DDRVTTTOP1_CR_DDRCRVTTGENCONTROL3_Spare_HSH                  (0x1A062D08)

#define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_REG                       (0x00002D80)

  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Target_OFF              ( 0)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Target_WID              ( 7)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Target_MSK              (0x0000007F)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Target_MIN              (0)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Target_MAX              (127) // 0x0000007F
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Target_DEF              (0x0000004C)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Target_HSH              (0x07002D80)

  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Panic_OFF               ( 7)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Panic_WID               ( 5)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Panic_MSK               (0x00000F80)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Panic_MIN               (0)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Panic_MAX               (31) // 0x0000001F
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Panic_DEF               (0x00000010)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Panic_HSH               (0x05072D80)

  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_OFF      (12)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_WID      ( 1)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MSK      (0x00001000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MIN      (0)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MAX      (1) // 0x00000001
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_DEF      (0x00000000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_HSH      (0x010C2D80)

  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_OFF          (13)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_WID          ( 1)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MSK          (0x00002000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MIN          (0)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MAX          (1) // 0x00000001
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_DEF          (0x00000000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_HSH          (0x010D2D80)

  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_OFF         (14)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_WID         ( 3)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MSK         (0x0001C000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MIN         (0)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MAX         (7) // 0x00000007
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_DEF         (0x00000000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_HSH         (0x030E2D80)

  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_OFF     (17)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_WID     ( 1)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_MSK     (0x00020000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_MIN     (0)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_MAX     (1) // 0x00000001
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_DEF     (0x00000000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_HSH     (0x01112D80)

  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_OFF   (18)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_WID   ( 1)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_MSK   (0x00040000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_MIN   (0)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_MAX   (1) // 0x00000001
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_DEF   (0x00000000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_HSH   (0x01122D80)

  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Spare_OFF               (19)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Spare_WID               ( 1)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Spare_MSK               (0x00080000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Spare_MIN               (0)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Spare_MAX               (1) // 0x00000001
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Spare_DEF               (0x00000000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Spare_HSH               (0x01132D80)

  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_EnVttOdt_OFF            (20)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_EnVttOdt_WID            ( 1)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_EnVttOdt_MSK            (0x00100000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_EnVttOdt_MIN            (0)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_EnVttOdt_MAX            (1) // 0x00000001
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_EnVttOdt_DEF            (0x00000000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_EnVttOdt_HSH            (0x01142D80)

  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_OFF (21)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_WID ( 1)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_MSK (0x00200000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_MIN (0)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_MAX (1) // 0x00000001
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_DEF (0x00000001)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_HSH (0x01152D80)

  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_OFF   (22)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_WID   ( 1)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_MSK   (0x00400000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_MIN   (0)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_MAX   (1) // 0x00000001
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_DEF   (0x00000000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_HSH   (0x01162D80)

  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_OFF       (23)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_WID       ( 1)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_MSK       (0x00800000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_MIN       (0)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_MAX       (1) // 0x00000001
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_DEF       (0x00000001)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_HSH       (0x01172D80)

  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_OFF       (24)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_WID       ( 1)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_MSK       (0x01000000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_MIN       (0)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_MAX       (1) // 0x00000001
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_DEF       (0x00000001)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_HSH       (0x01182D80)

  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Disable2Vt_OFF          (25)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Disable2Vt_WID          ( 1)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Disable2Vt_MSK          (0x02000000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Disable2Vt_MIN          (0)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Disable2Vt_MAX          (1) // 0x00000001
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Disable2Vt_DEF          (0x00000000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_Disable2Vt_HSH          (0x01192D80)

  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_OfstOvrd_OFF            (26)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_OfstOvrd_WID            ( 6)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_OfstOvrd_MSK            (0xFC000000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_OfstOvrd_MIN            (0)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_OfstOvrd_MAX            (63) // 0x0000003F
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_OfstOvrd_DEF            (0x00000000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_OfstOvrd_HSH            (0x061A2D80)

#define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_REG                      (0x00002D84)

  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_OFF ( 0)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_WID ( 1)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_MSK (0x00000001)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_MIN (0)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_MAX (1) // 0x00000001
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_DEF (0x00000000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_HSH (0x01002D84)

  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_OFF ( 1)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_WID ( 7)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_MSK (0x000000FE)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_MIN (0)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_MAX (127) // 0x0000007F
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_DEF (0x00000034)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_HSH (0x07012D84)

  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_OFF ( 8)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_WID ( 1)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_MSK (0x00000100)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_MIN (0)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_MAX (1) // 0x00000001
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_DEF (0x00000000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_HSH (0x01082D84)

  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_Spare_OFF              ( 9)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_Spare_WID              (23)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_Spare_MSK              (0xFFFFFE00)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_Spare_MIN              (0)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_Spare_MAX              (8388607) // 0x007FFFFF
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_Spare_DEF              (0x00000000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_Spare_HSH              (0x17092D84)

#define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL3_REG                      (0x00002D88)

  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL3_View_OFF               ( 0)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL3_View_WID               ( 6)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL3_View_MSK               (0x0000003F)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL3_View_MIN               (0)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL3_View_MAX               (63) // 0x0000003F
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL3_View_DEF               (0x00000000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL3_View_HSH               (0x06002D88)

  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL3_Spare_OFF              ( 6)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL3_Spare_WID              (26)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL3_Spare_MSK              (0xFFFFFFC0)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL3_Spare_MIN              (0)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL3_Spare_MAX              (67108863) // 0x03FFFFFF
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL3_Spare_DEF              (0x00000000)
  #define DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL3_Spare_HSH              (0x1A062D88)

#define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_REG                        (0x00002E00)

  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Target_OFF               ( 0)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Target_WID               ( 7)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Target_MSK               (0x0000007F)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Target_MIN               (0)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Target_MAX               (127) // 0x0000007F
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Target_DEF               (0x0000004C)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Target_HSH               (0x07002E00)

  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Panic_OFF                ( 7)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Panic_WID                ( 5)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Panic_MSK                (0x00000F80)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Panic_MIN                (0)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Panic_MAX                (31) // 0x0000001F
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Panic_DEF                (0x00000010)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Panic_HSH                (0x05072E00)

  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_OFF       (12)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_WID       ( 1)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MSK       (0x00001000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MIN       (0)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MAX       (1) // 0x00000001
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_DEF       (0x00000000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_HSH       (0x010C2E00)

  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_OFF           (13)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_WID           ( 1)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MSK           (0x00002000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MIN           (0)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MAX           (1) // 0x00000001
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_DEF           (0x00000000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_HSH           (0x010D2E00)

  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_OFF          (14)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_WID          ( 3)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MSK          (0x0001C000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MIN          (0)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MAX          (7) // 0x00000007
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_DEF          (0x00000000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_HSH          (0x030E2E00)

  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_OFF      (17)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_WID      ( 1)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_MSK      (0x00020000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_MIN      (0)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_MAX      (1) // 0x00000001
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_DEF      (0x00000000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_HSH      (0x01112E00)

  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_OFF    (18)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_WID    ( 1)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_MSK    (0x00040000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_MIN    (0)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_MAX    (1) // 0x00000001
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_DEF    (0x00000000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_HSH    (0x01122E00)

  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Spare_OFF                (19)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Spare_WID                ( 1)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Spare_MSK                (0x00080000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Spare_MIN                (0)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Spare_MAX                (1) // 0x00000001
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Spare_DEF                (0x00000000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Spare_HSH                (0x01132E00)

  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_EnVttOdt_OFF             (20)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_EnVttOdt_WID             ( 1)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_EnVttOdt_MSK             (0x00100000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_EnVttOdt_MIN             (0)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_EnVttOdt_MAX             (1) // 0x00000001
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_EnVttOdt_DEF             (0x00000000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_EnVttOdt_HSH             (0x01142E00)

  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_OFF (21)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_WID ( 1)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_MSK (0x00200000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_MIN (0)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_MAX (1) // 0x00000001
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_DEF (0x00000001)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_HSH (0x01152E00)

  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_OFF    (22)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_WID    ( 1)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_MSK    (0x00400000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_MIN    (0)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_MAX    (1) // 0x00000001
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_DEF    (0x00000000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_HSH    (0x01162E00)

  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_OFF        (23)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_WID        ( 1)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_MSK        (0x00800000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_MIN        (0)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_MAX        (1) // 0x00000001
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_DEF        (0x00000001)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_HSH        (0x01172E00)

  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_OFF        (24)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_WID        ( 1)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_MSK        (0x01000000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_MIN        (0)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_MAX        (1) // 0x00000001
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_DEF        (0x00000001)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_HSH        (0x01182E00)

  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Disable2Vt_OFF           (25)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Disable2Vt_WID           ( 1)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Disable2Vt_MSK           (0x02000000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Disable2Vt_MIN           (0)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Disable2Vt_MAX           (1) // 0x00000001
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Disable2Vt_DEF           (0x00000000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_Disable2Vt_HSH           (0x01192E00)

  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_OfstOvrd_OFF             (26)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_OfstOvrd_WID             ( 6)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_OfstOvrd_MSK             (0xFC000000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_OfstOvrd_MIN             (0)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_OfstOvrd_MAX             (63) // 0x0000003F
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_OfstOvrd_DEF             (0x00000000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_OfstOvrd_HSH             (0x061A2E00)

#define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_REG                       (0x00002E04)

  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_OFF ( 0)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_WID ( 1)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_MSK (0x00000001)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_MIN (0)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_MAX (1) // 0x00000001
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_DEF (0x00000000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_HSH (0x01002E04)

  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_OFF ( 1)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_WID ( 7)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_MSK (0x000000FE)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_MIN (0)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_MAX (127) // 0x0000007F
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_DEF (0x00000034)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_HSH (0x07012E04)

  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_OFF  ( 8)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_WID  ( 1)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_MSK  (0x00000100)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_MIN  (0)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_MAX  (1) // 0x00000001
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_DEF  (0x00000000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_HSH  (0x01082E04)

  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_Spare_OFF               ( 9)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_Spare_WID               (23)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_Spare_MSK               (0xFFFFFE00)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_Spare_MIN               (0)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_Spare_MAX               (8388607) // 0x007FFFFF
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_Spare_DEF               (0x00000000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_Spare_HSH               (0x17092E04)

#define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL3_REG                       (0x00002E08)

  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL3_View_OFF                ( 0)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL3_View_WID                ( 6)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL3_View_MSK                (0x0000003F)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL3_View_MIN                (0)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL3_View_MAX                (63) // 0x0000003F
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL3_View_DEF                (0x00000000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL3_View_HSH                (0x06002E08)

  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL3_Spare_OFF               ( 6)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL3_Spare_WID               (26)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL3_Spare_MSK               (0xFFFFFFC0)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL3_Spare_MIN               (0)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL3_Spare_MAX               (67108863) // 0x03FFFFFF
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL3_Spare_DEF               (0x00000000)
  #define DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL3_Spare_HSH               (0x1A062E08)

#define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_REG                           (0x00002E80)

  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Target_OFF                  ( 0)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Target_WID                  ( 7)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Target_MSK                  (0x0000007F)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Target_MIN                  (0)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Target_MAX                  (127) // 0x0000007F
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Target_DEF                  (0x0000004C)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Target_HSH                  (0x07002E80)

  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Panic_OFF                   ( 7)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Panic_WID                   ( 5)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Panic_MSK                   (0x00000F80)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Panic_MIN                   (0)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Panic_MAX                   (31) // 0x0000001F
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Panic_DEF                   (0x00000010)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Panic_HSH                   (0x05072E80)

  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_OFF          (12)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_WID          ( 1)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MSK          (0x00001000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MIN          (0)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_MAX          (1) // 0x00000001
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_DEF          (0x00000000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_DisSensorPwrDn_HSH          (0x010C2E80)

  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_OFF              (13)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_WID              ( 1)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MSK              (0x00002000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MIN              (0)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_MAX              (1) // 0x00000001
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_DEF              (0x00000000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_OfstOvrdEn_HSH              (0x010D2E80)

  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_OFF             (14)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_WID             ( 3)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MSK             (0x0001C000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MIN             (0)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_MAX             (7) // 0x00000007
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_DEF             (0x00000000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_ViewOfstsel_HSH             (0x030E2E80)

  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_OFF         (17)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_WID         ( 1)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_MSK         (0x00020000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_MIN         (0)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_MAX         (1) // 0x00000001
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_DEF         (0x00000000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_DdrCRForceODTOn_HSH         (0x01112E80)

  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_OFF       (18)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_WID       ( 1)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_MSK       (0x00040000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_MIN       (0)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_MAX       (1) // 0x00000001
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_DEF       (0x00000000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_SalCompLegacyCbit_HSH       (0x01122E80)

  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Spare_OFF                   (19)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Spare_WID                   ( 1)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Spare_MSK                   (0x00080000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Spare_MIN                   (0)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Spare_MAX                   (1) // 0x00000001
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Spare_DEF                   (0x00000000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Spare_HSH                   (0x01132E80)

  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_EnVttOdt_OFF                (20)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_EnVttOdt_WID                ( 1)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_EnVttOdt_MSK                (0x00100000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_EnVttOdt_MIN                (0)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_EnVttOdt_MAX                (1) // 0x00000001
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_EnVttOdt_DEF                (0x00000000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_EnVttOdt_HSH                (0x01142E80)

  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_OFF (21)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_WID ( 1)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_MSK (0x00200000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_MIN (0)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_MAX (1) // 0x00000001
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_DEF (0x00000001)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_PmosOrNmosComperatorTypeSel_HSH (0x01152E80)

  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_OFF       (22)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_WID       ( 1)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_MSK       (0x00400000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_MIN       (0)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_MAX       (1) // 0x00000001
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_DEF       (0x00000000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_UsePmosOffsetComp_HSH       (0x01162E80)

  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_OFF           (23)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_WID           ( 1)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_MSK           (0x00800000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_MIN           (0)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_MAX           (1) // 0x00000001
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_DEF           (0x00000001)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Enable2VtPmos_HSH           (0x01172E80)

  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_OFF           (24)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_WID           ( 1)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_MSK           (0x01000000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_MIN           (0)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_MAX           (1) // 0x00000001
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_DEF           (0x00000001)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Enable2VtNmos_HSH           (0x01182E80)

  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Disable2Vt_OFF              (25)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Disable2Vt_WID              ( 1)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Disable2Vt_MSK              (0x02000000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Disable2Vt_MIN              (0)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Disable2Vt_MAX              (1) // 0x00000001
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Disable2Vt_DEF              (0x00000000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_Disable2Vt_HSH              (0x01192E80)

  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_OfstOvrd_OFF                (26)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_OfstOvrd_WID                ( 6)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_OfstOvrd_MSK                (0xFC000000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_OfstOvrd_MIN                (0)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_OfstOvrd_MAX                (63) // 0x0000003F
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_OfstOvrd_DEF                (0x00000000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_OfstOvrd_HSH                (0x061A2E80)

#define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_REG                          (0x00002E84)

  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_OFF    ( 0)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_WID    ( 1)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_MSK    (0x00000001)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_MIN    (0)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_MAX    (1) // 0x00000001
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_DEF    (0x00000000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_DdrVttMainFsmLegacy_HSH    (0x01002E84)

  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_OFF ( 1)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_WID ( 7)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_MSK (0x000000FE)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_MIN (0)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_MAX (127) // 0x0000007F
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_DEF (0x00000034)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_VttUsePmosCompCRThreshold_HSH (0x07012E84)

  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_OFF     ( 8)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_WID     ( 1)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_MSK     (0x00000100)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_MIN     (0)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_MAX     (1) // 0x00000001
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_DEF     (0x00000000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_LowVoltageParkMode_HSH     (0x01082E84)

  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_Spare_OFF                  ( 9)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_Spare_WID                  (23)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_Spare_MSK                  (0xFFFFFE00)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_Spare_MIN                  (0)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_Spare_MAX                  (8388607) // 0x007FFFFF
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_Spare_DEF                  (0x00000000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_Spare_HSH                  (0x17092E84)

#define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL3_REG                          (0x00002E88)

  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL3_View_OFF                   ( 0)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL3_View_WID                   ( 6)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL3_View_MSK                   (0x0000003F)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL3_View_MIN                   (0)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL3_View_MAX                   (63) // 0x0000003F
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL3_View_DEF                   (0x00000000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL3_View_HSH                   (0x06002E88)

  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL3_Spare_OFF                  ( 6)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL3_Spare_WID                  (26)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL3_Spare_MSK                  (0xFFFFFFC0)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL3_Spare_MIN                  (0)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL3_Spare_MAX                  (67108863) // 0x03FFFFFF
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL3_Spare_DEF                  (0x00000000)
  #define DDRVTTBOT1_CR_DDRCRVTTGENCONTROL3_Spare_HSH                  (0x1A062E88)
#pragma pack(pop)
#endif
