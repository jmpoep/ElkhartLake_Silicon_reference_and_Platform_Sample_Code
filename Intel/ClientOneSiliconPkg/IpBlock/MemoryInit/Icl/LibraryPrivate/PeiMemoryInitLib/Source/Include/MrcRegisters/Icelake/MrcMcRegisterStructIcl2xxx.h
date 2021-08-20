#ifndef __MrcMcRegisterStructIcl2xxx_h__
#define __MrcMcRegisterStructIcl2xxx_h__
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
    UINT32 LockThresh                              :  3;  // Bits 2:0
    UINT32 LockCtr                                 :  2;  // Bits 4:3
    UINT32 VctrlDischRate                          :  2;  // Bits 6:5
    UINT32 SelVctrlHi                              :  1;  // Bits 7:7
    UINT32 StartupCntSel                           :  1;  // Bits 8:8
    UINT32 LockSel                                 :  2;  // Bits 10:9
    UINT32 RstOvrd                                 :  1;  // Bits 11:11
    UINT32 SelRstOvrd                              :  1;  // Bits 12:12
    UINT32 TimeOutOvrd                             :  1;  // Bits 13:13
    UINT32 SelTimeOutOvrd                          :  1;  // Bits 14:14
    UINT32 ClkGateOvrd                             :  1;  // Bits 15:15
    UINT32 LockOvrd                                :  1;  // Bits 16:16
    UINT32 SelLockOvrd                             :  1;  // Bits 17:17
    UINT32 OpenLoopOvrd                            :  1;  // Bits 18:18
    UINT32 SelOpenLoopOvrd                         :  1;  // Bits 19:19
    UINT32 WkLockEnOvrd                            :  1;  // Bits 20:20
    UINT32 SelWkLockEnOvrd                         :  1;  // Bits 21:21
    UINT32 CfdlDis                                 :  1;  // Bits 22:22
    UINT32 DftEn                                   :  1;  // Bits 23:23
    UINT32 spare0                                  :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA0_CR_MASTERDLLCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllBWEn                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA0_CR_CBTUNE0_STRUCT;

typedef union {
  struct {
    UINT32 PiCbEn                                  :  24;  // Bits 23:0
    UINT32 CbEnRsvd                                :  3;  // Bits 26:24
    UINT32 CbEnDllFuse                             :  3;  // Bits 29:27
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA0_CR_CBTUNE1_STRUCT;

typedef union {
  struct {
    UINT32 ADC_frz                                 :  1;  // Bits 0:0
    UINT32 ADC_en                                  :  1;  // Bits 1:1
    UINT32 ADCclkdiv                               :  2;  // Bits 3:2
    UINT32 ADCstartcount                           :  2;  // Bits 5:4
    UINT32 ADCChopEn                               :  1;  // Bits 6:6
    UINT32 Spare                                   :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA0_CR_ADCCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllCbEn                                 :  16;  // Bits 15:0
    UINT32 Spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA0_CR_CBTUNE2_STRUCT;

typedef union {
  struct {
    UINT32 PiDftDelay                              :  7;  // Bits 6:0
    UINT32 Ch0PiEnOvrd                             :  1;  // Bits 7:7
    UINT32 Ch1PiEnOvrd                             :  1;  // Bits 8:8
    UINT32 Ch0PiDFTEn                              :  1;  // Bits 9:9
    UINT32 Ch1PiDFTEn                              :  1;  // Bits 10:10
    UINT32 Spare                                   :  4;  // Bits 14:11
    UINT32 RefPiOvrd                               :  1;  // Bits 15:15
    UINT32 Rsvd                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA0_CR_PIDFTDLY_STRUCT;

typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Load                                    :  1;  // Bits 1:1
    UINT32 ModeHVM                                 :  1;  // Bits 2:2
    UINT32 ModeDV                                  :  1;  // Bits 3:3
    UINT32 CalCfdl                                 :  1;  // Bits 4:4
    UINT32 LoadCount                               :  10;  // Bits 14:5
    UINT32 CountStatus                             :  10;  // Bits 24:15
    UINT32 ModeADC                                 :  1;  // Bits 25:25
    UINT32 ADCClkDiv                               :  2;  // Bits 27:26
    UINT32 ADCDdrChanSel                           :  1;  // Bits 28:28
    UINT32 ADCChopEn                               :  1;  // Bits 29:29
    UINT32 ADCDone                                 :  1;  // Bits 30:30
    UINT32 PhaseDrvPwrSavOn                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA0_CR_DLLPITESTANDADC_STRUCT;

typedef union {
  struct {
    UINT32 DetrmLockStat                           :  1;  // Bits 0:0
    UINT32 FuncLockStat                            :  1;  // Bits 1:1
    UINT32 Lock                                    :  1;  // Bits 2:2
    UINT32 Timeout                                 :  1;  // Bits 3:3
    UINT32 DllReset                                :  1;  // Bits 4:4
    UINT32 LongLockStat                            :  1;  // Bits 5:5
    UINT32 EarlyLockStat                           :  1;  // Bits 6:6
    UINT32 NormalMode_NotWkLock                    :  1;  // Bits 7:7
    UINT32 ADCout                                  :  10;  // Bits 17:8
    UINT32 ADCStatus                               :  1;  // Bits 18:18
    UINT32 pilags                                  :  1;  // Bits 19:19
    UINT32 spare                                   :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA0_CR_DLLSTATUS_STRUCT;

typedef union {
  struct {
    UINT32 start                                   :  1;  // Bits 0:0
    UINT32 clken                                   :  1;  // Bits 1:1
    UINT32 dcm_dccctl_en                           :  1;  // Bits 2:2
    UINT32 dccctl                                  :  4;  // Bits 6:3
    UINT32 duration                                :  3;  // Bits 9:7
    UINT32 dcm_done                                :  1;  // Bits 10:10
    UINT32 dcm_results                             :  15;  // Bits 25:11
    UINT32 spare0                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA0_CR_DLLDCMCTL_STRUCT;

typedef union {
  struct {
    UINT32 LockThresh                              :  3;  // Bits 2:0
    UINT32 LockCtr                                 :  2;  // Bits 4:3
    UINT32 VctrlDischRate                          :  2;  // Bits 6:5
    UINT32 SelVctrlHi                              :  1;  // Bits 7:7
    UINT32 StartupCntSel                           :  1;  // Bits 8:8
    UINT32 LockSel                                 :  2;  // Bits 10:9
    UINT32 RstOvrd                                 :  1;  // Bits 11:11
    UINT32 SelRstOvrd                              :  1;  // Bits 12:12
    UINT32 TimeOutOvrd                             :  1;  // Bits 13:13
    UINT32 SelTimeOutOvrd                          :  1;  // Bits 14:14
    UINT32 ClkGateOvrd                             :  1;  // Bits 15:15
    UINT32 LockOvrd                                :  1;  // Bits 16:16
    UINT32 SelLockOvrd                             :  1;  // Bits 17:17
    UINT32 OpenLoopOvrd                            :  1;  // Bits 18:18
    UINT32 SelOpenLoopOvrd                         :  1;  // Bits 19:19
    UINT32 WkLockEnOvrd                            :  1;  // Bits 20:20
    UINT32 SelWkLockEnOvrd                         :  1;  // Bits 21:21
    UINT32 CfdlDis                                 :  1;  // Bits 22:22
    UINT32 DftEn                                   :  1;  // Bits 23:23
    UINT32 spare0                                  :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA1_CR_MASTERDLLCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllBWEn                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA1_CR_CBTUNE0_STRUCT;

typedef union {
  struct {
    UINT32 PiCbEn                                  :  24;  // Bits 23:0
    UINT32 CbEnRsvd                                :  3;  // Bits 26:24
    UINT32 CbEnDllFuse                             :  3;  // Bits 29:27
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA1_CR_CBTUNE1_STRUCT;

typedef union {
  struct {
    UINT32 ADC_frz                                 :  1;  // Bits 0:0
    UINT32 ADC_en                                  :  1;  // Bits 1:1
    UINT32 ADCclkdiv                               :  2;  // Bits 3:2
    UINT32 ADCstartcount                           :  2;  // Bits 5:4
    UINT32 ADCChopEn                               :  1;  // Bits 6:6
    UINT32 Spare                                   :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA1_CR_ADCCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllCbEn                                 :  16;  // Bits 15:0
    UINT32 Spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA1_CR_CBTUNE2_STRUCT;

typedef union {
  struct {
    UINT32 PiDftDelay                              :  7;  // Bits 6:0
    UINT32 Ch0PiEnOvrd                             :  1;  // Bits 7:7
    UINT32 Ch1PiEnOvrd                             :  1;  // Bits 8:8
    UINT32 Ch0PiDFTEn                              :  1;  // Bits 9:9
    UINT32 Ch1PiDFTEn                              :  1;  // Bits 10:10
    UINT32 Spare                                   :  4;  // Bits 14:11
    UINT32 RefPiOvrd                               :  1;  // Bits 15:15
    UINT32 Rsvd                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA1_CR_PIDFTDLY_STRUCT;

typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Load                                    :  1;  // Bits 1:1
    UINT32 ModeHVM                                 :  1;  // Bits 2:2
    UINT32 ModeDV                                  :  1;  // Bits 3:3
    UINT32 CalCfdl                                 :  1;  // Bits 4:4
    UINT32 LoadCount                               :  10;  // Bits 14:5
    UINT32 CountStatus                             :  10;  // Bits 24:15
    UINT32 ModeADC                                 :  1;  // Bits 25:25
    UINT32 ADCClkDiv                               :  2;  // Bits 27:26
    UINT32 ADCDdrChanSel                           :  1;  // Bits 28:28
    UINT32 ADCChopEn                               :  1;  // Bits 29:29
    UINT32 ADCDone                                 :  1;  // Bits 30:30
    UINT32 PhaseDrvPwrSavOn                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA1_CR_DLLPITESTANDADC_STRUCT;

typedef union {
  struct {
    UINT32 DetrmLockStat                           :  1;  // Bits 0:0
    UINT32 FuncLockStat                            :  1;  // Bits 1:1
    UINT32 Lock                                    :  1;  // Bits 2:2
    UINT32 Timeout                                 :  1;  // Bits 3:3
    UINT32 DllReset                                :  1;  // Bits 4:4
    UINT32 LongLockStat                            :  1;  // Bits 5:5
    UINT32 EarlyLockStat                           :  1;  // Bits 6:6
    UINT32 NormalMode_NotWkLock                    :  1;  // Bits 7:7
    UINT32 ADCout                                  :  10;  // Bits 17:8
    UINT32 ADCStatus                               :  1;  // Bits 18:18
    UINT32 pilags                                  :  1;  // Bits 19:19
    UINT32 spare                                   :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA1_CR_DLLSTATUS_STRUCT;

typedef union {
  struct {
    UINT32 start                                   :  1;  // Bits 0:0
    UINT32 clken                                   :  1;  // Bits 1:1
    UINT32 dcm_dccctl_en                           :  1;  // Bits 2:2
    UINT32 dccctl                                  :  4;  // Bits 6:3
    UINT32 duration                                :  3;  // Bits 9:7
    UINT32 dcm_done                                :  1;  // Bits 10:10
    UINT32 dcm_results                             :  15;  // Bits 25:11
    UINT32 spare0                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA1_CR_DLLDCMCTL_STRUCT;

typedef union {
  struct {
    UINT32 LockThresh                              :  3;  // Bits 2:0
    UINT32 LockCtr                                 :  2;  // Bits 4:3
    UINT32 VctrlDischRate                          :  2;  // Bits 6:5
    UINT32 SelVctrlHi                              :  1;  // Bits 7:7
    UINT32 StartupCntSel                           :  1;  // Bits 8:8
    UINT32 LockSel                                 :  2;  // Bits 10:9
    UINT32 RstOvrd                                 :  1;  // Bits 11:11
    UINT32 SelRstOvrd                              :  1;  // Bits 12:12
    UINT32 TimeOutOvrd                             :  1;  // Bits 13:13
    UINT32 SelTimeOutOvrd                          :  1;  // Bits 14:14
    UINT32 ClkGateOvrd                             :  1;  // Bits 15:15
    UINT32 LockOvrd                                :  1;  // Bits 16:16
    UINT32 SelLockOvrd                             :  1;  // Bits 17:17
    UINT32 OpenLoopOvrd                            :  1;  // Bits 18:18
    UINT32 SelOpenLoopOvrd                         :  1;  // Bits 19:19
    UINT32 WkLockEnOvrd                            :  1;  // Bits 20:20
    UINT32 SelWkLockEnOvrd                         :  1;  // Bits 21:21
    UINT32 CfdlDis                                 :  1;  // Bits 22:22
    UINT32 DftEn                                   :  1;  // Bits 23:23
    UINT32 spare0                                  :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA2_CR_MASTERDLLCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllBWEn                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA2_CR_CBTUNE0_STRUCT;

typedef union {
  struct {
    UINT32 PiCbEn                                  :  24;  // Bits 23:0
    UINT32 CbEnRsvd                                :  3;  // Bits 26:24
    UINT32 CbEnDllFuse                             :  3;  // Bits 29:27
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA2_CR_CBTUNE1_STRUCT;

typedef union {
  struct {
    UINT32 ADC_frz                                 :  1;  // Bits 0:0
    UINT32 ADC_en                                  :  1;  // Bits 1:1
    UINT32 ADCclkdiv                               :  2;  // Bits 3:2
    UINT32 ADCstartcount                           :  2;  // Bits 5:4
    UINT32 ADCChopEn                               :  1;  // Bits 6:6
    UINT32 Spare                                   :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA2_CR_ADCCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllCbEn                                 :  16;  // Bits 15:0
    UINT32 Spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA2_CR_CBTUNE2_STRUCT;

typedef union {
  struct {
    UINT32 PiDftDelay                              :  7;  // Bits 6:0
    UINT32 Ch0PiEnOvrd                             :  1;  // Bits 7:7
    UINT32 Ch1PiEnOvrd                             :  1;  // Bits 8:8
    UINT32 Ch0PiDFTEn                              :  1;  // Bits 9:9
    UINT32 Ch1PiDFTEn                              :  1;  // Bits 10:10
    UINT32 Spare                                   :  4;  // Bits 14:11
    UINT32 RefPiOvrd                               :  1;  // Bits 15:15
    UINT32 Rsvd                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA2_CR_PIDFTDLY_STRUCT;

typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Load                                    :  1;  // Bits 1:1
    UINT32 ModeHVM                                 :  1;  // Bits 2:2
    UINT32 ModeDV                                  :  1;  // Bits 3:3
    UINT32 CalCfdl                                 :  1;  // Bits 4:4
    UINT32 LoadCount                               :  10;  // Bits 14:5
    UINT32 CountStatus                             :  10;  // Bits 24:15
    UINT32 ModeADC                                 :  1;  // Bits 25:25
    UINT32 ADCClkDiv                               :  2;  // Bits 27:26
    UINT32 ADCDdrChanSel                           :  1;  // Bits 28:28
    UINT32 ADCChopEn                               :  1;  // Bits 29:29
    UINT32 ADCDone                                 :  1;  // Bits 30:30
    UINT32 PhaseDrvPwrSavOn                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA2_CR_DLLPITESTANDADC_STRUCT;

typedef union {
  struct {
    UINT32 DetrmLockStat                           :  1;  // Bits 0:0
    UINT32 FuncLockStat                            :  1;  // Bits 1:1
    UINT32 Lock                                    :  1;  // Bits 2:2
    UINT32 Timeout                                 :  1;  // Bits 3:3
    UINT32 DllReset                                :  1;  // Bits 4:4
    UINT32 LongLockStat                            :  1;  // Bits 5:5
    UINT32 EarlyLockStat                           :  1;  // Bits 6:6
    UINT32 NormalMode_NotWkLock                    :  1;  // Bits 7:7
    UINT32 ADCout                                  :  10;  // Bits 17:8
    UINT32 ADCStatus                               :  1;  // Bits 18:18
    UINT32 pilags                                  :  1;  // Bits 19:19
    UINT32 spare                                   :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA2_CR_DLLSTATUS_STRUCT;

typedef union {
  struct {
    UINT32 start                                   :  1;  // Bits 0:0
    UINT32 clken                                   :  1;  // Bits 1:1
    UINT32 dcm_dccctl_en                           :  1;  // Bits 2:2
    UINT32 dccctl                                  :  4;  // Bits 6:3
    UINT32 duration                                :  3;  // Bits 9:7
    UINT32 dcm_done                                :  1;  // Bits 10:10
    UINT32 dcm_results                             :  15;  // Bits 25:11
    UINT32 spare0                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA2_CR_DLLDCMCTL_STRUCT;

typedef union {
  struct {
    UINT32 LockThresh                              :  3;  // Bits 2:0
    UINT32 LockCtr                                 :  2;  // Bits 4:3
    UINT32 VctrlDischRate                          :  2;  // Bits 6:5
    UINT32 SelVctrlHi                              :  1;  // Bits 7:7
    UINT32 StartupCntSel                           :  1;  // Bits 8:8
    UINT32 LockSel                                 :  2;  // Bits 10:9
    UINT32 RstOvrd                                 :  1;  // Bits 11:11
    UINT32 SelRstOvrd                              :  1;  // Bits 12:12
    UINT32 TimeOutOvrd                             :  1;  // Bits 13:13
    UINT32 SelTimeOutOvrd                          :  1;  // Bits 14:14
    UINT32 ClkGateOvrd                             :  1;  // Bits 15:15
    UINT32 LockOvrd                                :  1;  // Bits 16:16
    UINT32 SelLockOvrd                             :  1;  // Bits 17:17
    UINT32 OpenLoopOvrd                            :  1;  // Bits 18:18
    UINT32 SelOpenLoopOvrd                         :  1;  // Bits 19:19
    UINT32 WkLockEnOvrd                            :  1;  // Bits 20:20
    UINT32 SelWkLockEnOvrd                         :  1;  // Bits 21:21
    UINT32 CfdlDis                                 :  1;  // Bits 22:22
    UINT32 DftEn                                   :  1;  // Bits 23:23
    UINT32 spare0                                  :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA3_CR_MASTERDLLCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllBWEn                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA3_CR_CBTUNE0_STRUCT;

typedef union {
  struct {
    UINT32 PiCbEn                                  :  24;  // Bits 23:0
    UINT32 CbEnRsvd                                :  3;  // Bits 26:24
    UINT32 CbEnDllFuse                             :  3;  // Bits 29:27
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA3_CR_CBTUNE1_STRUCT;

typedef union {
  struct {
    UINT32 ADC_frz                                 :  1;  // Bits 0:0
    UINT32 ADC_en                                  :  1;  // Bits 1:1
    UINT32 ADCclkdiv                               :  2;  // Bits 3:2
    UINT32 ADCstartcount                           :  2;  // Bits 5:4
    UINT32 ADCChopEn                               :  1;  // Bits 6:6
    UINT32 Spare                                   :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA3_CR_ADCCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllCbEn                                 :  16;  // Bits 15:0
    UINT32 Spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA3_CR_CBTUNE2_STRUCT;

typedef union {
  struct {
    UINT32 PiDftDelay                              :  7;  // Bits 6:0
    UINT32 Ch0PiEnOvrd                             :  1;  // Bits 7:7
    UINT32 Ch1PiEnOvrd                             :  1;  // Bits 8:8
    UINT32 Ch0PiDFTEn                              :  1;  // Bits 9:9
    UINT32 Ch1PiDFTEn                              :  1;  // Bits 10:10
    UINT32 Spare                                   :  4;  // Bits 14:11
    UINT32 RefPiOvrd                               :  1;  // Bits 15:15
    UINT32 Rsvd                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA3_CR_PIDFTDLY_STRUCT;

typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Load                                    :  1;  // Bits 1:1
    UINT32 ModeHVM                                 :  1;  // Bits 2:2
    UINT32 ModeDV                                  :  1;  // Bits 3:3
    UINT32 CalCfdl                                 :  1;  // Bits 4:4
    UINT32 LoadCount                               :  10;  // Bits 14:5
    UINT32 CountStatus                             :  10;  // Bits 24:15
    UINT32 ModeADC                                 :  1;  // Bits 25:25
    UINT32 ADCClkDiv                               :  2;  // Bits 27:26
    UINT32 ADCDdrChanSel                           :  1;  // Bits 28:28
    UINT32 ADCChopEn                               :  1;  // Bits 29:29
    UINT32 ADCDone                                 :  1;  // Bits 30:30
    UINT32 PhaseDrvPwrSavOn                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA3_CR_DLLPITESTANDADC_STRUCT;

typedef union {
  struct {
    UINT32 DetrmLockStat                           :  1;  // Bits 0:0
    UINT32 FuncLockStat                            :  1;  // Bits 1:1
    UINT32 Lock                                    :  1;  // Bits 2:2
    UINT32 Timeout                                 :  1;  // Bits 3:3
    UINT32 DllReset                                :  1;  // Bits 4:4
    UINT32 LongLockStat                            :  1;  // Bits 5:5
    UINT32 EarlyLockStat                           :  1;  // Bits 6:6
    UINT32 NormalMode_NotWkLock                    :  1;  // Bits 7:7
    UINT32 ADCout                                  :  10;  // Bits 17:8
    UINT32 ADCStatus                               :  1;  // Bits 18:18
    UINT32 pilags                                  :  1;  // Bits 19:19
    UINT32 spare                                   :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA3_CR_DLLSTATUS_STRUCT;

typedef union {
  struct {
    UINT32 start                                   :  1;  // Bits 0:0
    UINT32 clken                                   :  1;  // Bits 1:1
    UINT32 dcm_dccctl_en                           :  1;  // Bits 2:2
    UINT32 dccctl                                  :  4;  // Bits 6:3
    UINT32 duration                                :  3;  // Bits 9:7
    UINT32 dcm_done                                :  1;  // Bits 10:10
    UINT32 dcm_results                             :  15;  // Bits 25:11
    UINT32 spare0                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA3_CR_DLLDCMCTL_STRUCT;

typedef union {
  struct {
    UINT32 LockThresh                              :  3;  // Bits 2:0
    UINT32 LockCtr                                 :  2;  // Bits 4:3
    UINT32 VctrlDischRate                          :  2;  // Bits 6:5
    UINT32 SelVctrlHi                              :  1;  // Bits 7:7
    UINT32 StartupCntSel                           :  1;  // Bits 8:8
    UINT32 LockSel                                 :  2;  // Bits 10:9
    UINT32 RstOvrd                                 :  1;  // Bits 11:11
    UINT32 SelRstOvrd                              :  1;  // Bits 12:12
    UINT32 TimeOutOvrd                             :  1;  // Bits 13:13
    UINT32 SelTimeOutOvrd                          :  1;  // Bits 14:14
    UINT32 ClkGateOvrd                             :  1;  // Bits 15:15
    UINT32 LockOvrd                                :  1;  // Bits 16:16
    UINT32 SelLockOvrd                             :  1;  // Bits 17:17
    UINT32 OpenLoopOvrd                            :  1;  // Bits 18:18
    UINT32 SelOpenLoopOvrd                         :  1;  // Bits 19:19
    UINT32 WkLockEnOvrd                            :  1;  // Bits 20:20
    UINT32 SelWkLockEnOvrd                         :  1;  // Bits 21:21
    UINT32 CfdlDis                                 :  1;  // Bits 22:22
    UINT32 DftEn                                   :  1;  // Bits 23:23
    UINT32 spare0                                  :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA4_CR_MASTERDLLCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllBWEn                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA4_CR_CBTUNE0_STRUCT;

typedef union {
  struct {
    UINT32 PiCbEn                                  :  24;  // Bits 23:0
    UINT32 CbEnRsvd                                :  3;  // Bits 26:24
    UINT32 CbEnDllFuse                             :  3;  // Bits 29:27
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA4_CR_CBTUNE1_STRUCT;

typedef union {
  struct {
    UINT32 ADC_frz                                 :  1;  // Bits 0:0
    UINT32 ADC_en                                  :  1;  // Bits 1:1
    UINT32 ADCclkdiv                               :  2;  // Bits 3:2
    UINT32 ADCstartcount                           :  2;  // Bits 5:4
    UINT32 ADCChopEn                               :  1;  // Bits 6:6
    UINT32 Spare                                   :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA4_CR_ADCCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllCbEn                                 :  16;  // Bits 15:0
    UINT32 Spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA4_CR_CBTUNE2_STRUCT;

typedef union {
  struct {
    UINT32 PiDftDelay                              :  7;  // Bits 6:0
    UINT32 Ch0PiEnOvrd                             :  1;  // Bits 7:7
    UINT32 Ch1PiEnOvrd                             :  1;  // Bits 8:8
    UINT32 Ch0PiDFTEn                              :  1;  // Bits 9:9
    UINT32 Ch1PiDFTEn                              :  1;  // Bits 10:10
    UINT32 Spare                                   :  4;  // Bits 14:11
    UINT32 RefPiOvrd                               :  1;  // Bits 15:15
    UINT32 Rsvd                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA4_CR_PIDFTDLY_STRUCT;

typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Load                                    :  1;  // Bits 1:1
    UINT32 ModeHVM                                 :  1;  // Bits 2:2
    UINT32 ModeDV                                  :  1;  // Bits 3:3
    UINT32 CalCfdl                                 :  1;  // Bits 4:4
    UINT32 LoadCount                               :  10;  // Bits 14:5
    UINT32 CountStatus                             :  10;  // Bits 24:15
    UINT32 ModeADC                                 :  1;  // Bits 25:25
    UINT32 ADCClkDiv                               :  2;  // Bits 27:26
    UINT32 ADCDdrChanSel                           :  1;  // Bits 28:28
    UINT32 ADCChopEn                               :  1;  // Bits 29:29
    UINT32 ADCDone                                 :  1;  // Bits 30:30
    UINT32 PhaseDrvPwrSavOn                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA4_CR_DLLPITESTANDADC_STRUCT;

typedef union {
  struct {
    UINT32 DetrmLockStat                           :  1;  // Bits 0:0
    UINT32 FuncLockStat                            :  1;  // Bits 1:1
    UINT32 Lock                                    :  1;  // Bits 2:2
    UINT32 Timeout                                 :  1;  // Bits 3:3
    UINT32 DllReset                                :  1;  // Bits 4:4
    UINT32 LongLockStat                            :  1;  // Bits 5:5
    UINT32 EarlyLockStat                           :  1;  // Bits 6:6
    UINT32 NormalMode_NotWkLock                    :  1;  // Bits 7:7
    UINT32 ADCout                                  :  10;  // Bits 17:8
    UINT32 ADCStatus                               :  1;  // Bits 18:18
    UINT32 pilags                                  :  1;  // Bits 19:19
    UINT32 spare                                   :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA4_CR_DLLSTATUS_STRUCT;

typedef union {
  struct {
    UINT32 start                                   :  1;  // Bits 0:0
    UINT32 clken                                   :  1;  // Bits 1:1
    UINT32 dcm_dccctl_en                           :  1;  // Bits 2:2
    UINT32 dccctl                                  :  4;  // Bits 6:3
    UINT32 duration                                :  3;  // Bits 9:7
    UINT32 dcm_done                                :  1;  // Bits 10:10
    UINT32 dcm_results                             :  15;  // Bits 25:11
    UINT32 spare0                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA4_CR_DLLDCMCTL_STRUCT;

typedef union {
  struct {
    UINT32 LockThresh                              :  3;  // Bits 2:0
    UINT32 LockCtr                                 :  2;  // Bits 4:3
    UINT32 VctrlDischRate                          :  2;  // Bits 6:5
    UINT32 SelVctrlHi                              :  1;  // Bits 7:7
    UINT32 StartupCntSel                           :  1;  // Bits 8:8
    UINT32 LockSel                                 :  2;  // Bits 10:9
    UINT32 RstOvrd                                 :  1;  // Bits 11:11
    UINT32 SelRstOvrd                              :  1;  // Bits 12:12
    UINT32 TimeOutOvrd                             :  1;  // Bits 13:13
    UINT32 SelTimeOutOvrd                          :  1;  // Bits 14:14
    UINT32 ClkGateOvrd                             :  1;  // Bits 15:15
    UINT32 LockOvrd                                :  1;  // Bits 16:16
    UINT32 SelLockOvrd                             :  1;  // Bits 17:17
    UINT32 OpenLoopOvrd                            :  1;  // Bits 18:18
    UINT32 SelOpenLoopOvrd                         :  1;  // Bits 19:19
    UINT32 WkLockEnOvrd                            :  1;  // Bits 20:20
    UINT32 SelWkLockEnOvrd                         :  1;  // Bits 21:21
    UINT32 CfdlDis                                 :  1;  // Bits 22:22
    UINT32 DftEn                                   :  1;  // Bits 23:23
    UINT32 spare0                                  :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5_CR_MASTERDLLCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllBWEn                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5_CR_CBTUNE0_STRUCT;

typedef union {
  struct {
    UINT32 PiCbEn                                  :  24;  // Bits 23:0
    UINT32 CbEnRsvd                                :  3;  // Bits 26:24
    UINT32 CbEnDllFuse                             :  3;  // Bits 29:27
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5_CR_CBTUNE1_STRUCT;

typedef union {
  struct {
    UINT32 ADC_frz                                 :  1;  // Bits 0:0
    UINT32 ADC_en                                  :  1;  // Bits 1:1
    UINT32 ADCclkdiv                               :  2;  // Bits 3:2
    UINT32 ADCstartcount                           :  2;  // Bits 5:4
    UINT32 ADCChopEn                               :  1;  // Bits 6:6
    UINT32 Spare                                   :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5_CR_ADCCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllCbEn                                 :  16;  // Bits 15:0
    UINT32 Spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5_CR_CBTUNE2_STRUCT;

typedef union {
  struct {
    UINT32 PiDftDelay                              :  7;  // Bits 6:0
    UINT32 Ch0PiEnOvrd                             :  1;  // Bits 7:7
    UINT32 Ch1PiEnOvrd                             :  1;  // Bits 8:8
    UINT32 Ch0PiDFTEn                              :  1;  // Bits 9:9
    UINT32 Ch1PiDFTEn                              :  1;  // Bits 10:10
    UINT32 Spare                                   :  4;  // Bits 14:11
    UINT32 RefPiOvrd                               :  1;  // Bits 15:15
    UINT32 Rsvd                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5_CR_PIDFTDLY_STRUCT;

typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Load                                    :  1;  // Bits 1:1
    UINT32 ModeHVM                                 :  1;  // Bits 2:2
    UINT32 ModeDV                                  :  1;  // Bits 3:3
    UINT32 CalCfdl                                 :  1;  // Bits 4:4
    UINT32 LoadCount                               :  10;  // Bits 14:5
    UINT32 CountStatus                             :  10;  // Bits 24:15
    UINT32 ModeADC                                 :  1;  // Bits 25:25
    UINT32 ADCClkDiv                               :  2;  // Bits 27:26
    UINT32 ADCDdrChanSel                           :  1;  // Bits 28:28
    UINT32 ADCChopEn                               :  1;  // Bits 29:29
    UINT32 ADCDone                                 :  1;  // Bits 30:30
    UINT32 PhaseDrvPwrSavOn                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5_CR_DLLPITESTANDADC_STRUCT;

typedef union {
  struct {
    UINT32 DetrmLockStat                           :  1;  // Bits 0:0
    UINT32 FuncLockStat                            :  1;  // Bits 1:1
    UINT32 Lock                                    :  1;  // Bits 2:2
    UINT32 Timeout                                 :  1;  // Bits 3:3
    UINT32 DllReset                                :  1;  // Bits 4:4
    UINT32 LongLockStat                            :  1;  // Bits 5:5
    UINT32 EarlyLockStat                           :  1;  // Bits 6:6
    UINT32 NormalMode_NotWkLock                    :  1;  // Bits 7:7
    UINT32 ADCout                                  :  10;  // Bits 17:8
    UINT32 ADCStatus                               :  1;  // Bits 18:18
    UINT32 pilags                                  :  1;  // Bits 19:19
    UINT32 spare                                   :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5_CR_DLLSTATUS_STRUCT;

typedef union {
  struct {
    UINT32 start                                   :  1;  // Bits 0:0
    UINT32 clken                                   :  1;  // Bits 1:1
    UINT32 dcm_dccctl_en                           :  1;  // Bits 2:2
    UINT32 dccctl                                  :  4;  // Bits 6:3
    UINT32 duration                                :  3;  // Bits 9:7
    UINT32 dcm_done                                :  1;  // Bits 10:10
    UINT32 dcm_results                             :  15;  // Bits 25:11
    UINT32 spare0                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA5_CR_DLLDCMCTL_STRUCT;

typedef union {
  struct {
    UINT32 LockThresh                              :  3;  // Bits 2:0
    UINT32 LockCtr                                 :  2;  // Bits 4:3
    UINT32 VctrlDischRate                          :  2;  // Bits 6:5
    UINT32 SelVctrlHi                              :  1;  // Bits 7:7
    UINT32 StartupCntSel                           :  1;  // Bits 8:8
    UINT32 LockSel                                 :  2;  // Bits 10:9
    UINT32 RstOvrd                                 :  1;  // Bits 11:11
    UINT32 SelRstOvrd                              :  1;  // Bits 12:12
    UINT32 TimeOutOvrd                             :  1;  // Bits 13:13
    UINT32 SelTimeOutOvrd                          :  1;  // Bits 14:14
    UINT32 ClkGateOvrd                             :  1;  // Bits 15:15
    UINT32 LockOvrd                                :  1;  // Bits 16:16
    UINT32 SelLockOvrd                             :  1;  // Bits 17:17
    UINT32 OpenLoopOvrd                            :  1;  // Bits 18:18
    UINT32 SelOpenLoopOvrd                         :  1;  // Bits 19:19
    UINT32 WkLockEnOvrd                            :  1;  // Bits 20:20
    UINT32 SelWkLockEnOvrd                         :  1;  // Bits 21:21
    UINT32 CfdlDis                                 :  1;  // Bits 22:22
    UINT32 DftEn                                   :  1;  // Bits 23:23
    UINT32 spare0                                  :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6_CR_MASTERDLLCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllBWEn                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6_CR_CBTUNE0_STRUCT;

typedef union {
  struct {
    UINT32 PiCbEn                                  :  24;  // Bits 23:0
    UINT32 CbEnRsvd                                :  3;  // Bits 26:24
    UINT32 CbEnDllFuse                             :  3;  // Bits 29:27
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6_CR_CBTUNE1_STRUCT;

typedef union {
  struct {
    UINT32 ADC_frz                                 :  1;  // Bits 0:0
    UINT32 ADC_en                                  :  1;  // Bits 1:1
    UINT32 ADCclkdiv                               :  2;  // Bits 3:2
    UINT32 ADCstartcount                           :  2;  // Bits 5:4
    UINT32 ADCChopEn                               :  1;  // Bits 6:6
    UINT32 Spare                                   :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6_CR_ADCCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllCbEn                                 :  16;  // Bits 15:0
    UINT32 Spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6_CR_CBTUNE2_STRUCT;

typedef union {
  struct {
    UINT32 PiDftDelay                              :  7;  // Bits 6:0
    UINT32 Ch0PiEnOvrd                             :  1;  // Bits 7:7
    UINT32 Ch1PiEnOvrd                             :  1;  // Bits 8:8
    UINT32 Ch0PiDFTEn                              :  1;  // Bits 9:9
    UINT32 Ch1PiDFTEn                              :  1;  // Bits 10:10
    UINT32 Spare                                   :  4;  // Bits 14:11
    UINT32 RefPiOvrd                               :  1;  // Bits 15:15
    UINT32 Rsvd                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6_CR_PIDFTDLY_STRUCT;

typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Load                                    :  1;  // Bits 1:1
    UINT32 ModeHVM                                 :  1;  // Bits 2:2
    UINT32 ModeDV                                  :  1;  // Bits 3:3
    UINT32 CalCfdl                                 :  1;  // Bits 4:4
    UINT32 LoadCount                               :  10;  // Bits 14:5
    UINT32 CountStatus                             :  10;  // Bits 24:15
    UINT32 ModeADC                                 :  1;  // Bits 25:25
    UINT32 ADCClkDiv                               :  2;  // Bits 27:26
    UINT32 ADCDdrChanSel                           :  1;  // Bits 28:28
    UINT32 ADCChopEn                               :  1;  // Bits 29:29
    UINT32 ADCDone                                 :  1;  // Bits 30:30
    UINT32 PhaseDrvPwrSavOn                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6_CR_DLLPITESTANDADC_STRUCT;

typedef union {
  struct {
    UINT32 DetrmLockStat                           :  1;  // Bits 0:0
    UINT32 FuncLockStat                            :  1;  // Bits 1:1
    UINT32 Lock                                    :  1;  // Bits 2:2
    UINT32 Timeout                                 :  1;  // Bits 3:3
    UINT32 DllReset                                :  1;  // Bits 4:4
    UINT32 LongLockStat                            :  1;  // Bits 5:5
    UINT32 EarlyLockStat                           :  1;  // Bits 6:6
    UINT32 NormalMode_NotWkLock                    :  1;  // Bits 7:7
    UINT32 ADCout                                  :  10;  // Bits 17:8
    UINT32 ADCStatus                               :  1;  // Bits 18:18
    UINT32 pilags                                  :  1;  // Bits 19:19
    UINT32 spare                                   :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6_CR_DLLSTATUS_STRUCT;

typedef union {
  struct {
    UINT32 start                                   :  1;  // Bits 0:0
    UINT32 clken                                   :  1;  // Bits 1:1
    UINT32 dcm_dccctl_en                           :  1;  // Bits 2:2
    UINT32 dccctl                                  :  4;  // Bits 6:3
    UINT32 duration                                :  3;  // Bits 9:7
    UINT32 dcm_done                                :  1;  // Bits 10:10
    UINT32 dcm_results                             :  15;  // Bits 25:11
    UINT32 spare0                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA6_CR_DLLDCMCTL_STRUCT;

typedef union {
  struct {
    UINT32 LockThresh                              :  3;  // Bits 2:0
    UINT32 LockCtr                                 :  2;  // Bits 4:3
    UINT32 VctrlDischRate                          :  2;  // Bits 6:5
    UINT32 SelVctrlHi                              :  1;  // Bits 7:7
    UINT32 StartupCntSel                           :  1;  // Bits 8:8
    UINT32 LockSel                                 :  2;  // Bits 10:9
    UINT32 RstOvrd                                 :  1;  // Bits 11:11
    UINT32 SelRstOvrd                              :  1;  // Bits 12:12
    UINT32 TimeOutOvrd                             :  1;  // Bits 13:13
    UINT32 SelTimeOutOvrd                          :  1;  // Bits 14:14
    UINT32 ClkGateOvrd                             :  1;  // Bits 15:15
    UINT32 LockOvrd                                :  1;  // Bits 16:16
    UINT32 SelLockOvrd                             :  1;  // Bits 17:17
    UINT32 OpenLoopOvrd                            :  1;  // Bits 18:18
    UINT32 SelOpenLoopOvrd                         :  1;  // Bits 19:19
    UINT32 WkLockEnOvrd                            :  1;  // Bits 20:20
    UINT32 SelWkLockEnOvrd                         :  1;  // Bits 21:21
    UINT32 CfdlDis                                 :  1;  // Bits 22:22
    UINT32 DftEn                                   :  1;  // Bits 23:23
    UINT32 spare0                                  :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7_CR_MASTERDLLCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllBWEn                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7_CR_CBTUNE0_STRUCT;

typedef union {
  struct {
    UINT32 PiCbEn                                  :  24;  // Bits 23:0
    UINT32 CbEnRsvd                                :  3;  // Bits 26:24
    UINT32 CbEnDllFuse                             :  3;  // Bits 29:27
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7_CR_CBTUNE1_STRUCT;

typedef union {
  struct {
    UINT32 ADC_frz                                 :  1;  // Bits 0:0
    UINT32 ADC_en                                  :  1;  // Bits 1:1
    UINT32 ADCclkdiv                               :  2;  // Bits 3:2
    UINT32 ADCstartcount                           :  2;  // Bits 5:4
    UINT32 ADCChopEn                               :  1;  // Bits 6:6
    UINT32 Spare                                   :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7_CR_ADCCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllCbEn                                 :  16;  // Bits 15:0
    UINT32 Spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7_CR_CBTUNE2_STRUCT;

typedef union {
  struct {
    UINT32 PiDftDelay                              :  7;  // Bits 6:0
    UINT32 Ch0PiEnOvrd                             :  1;  // Bits 7:7
    UINT32 Ch1PiEnOvrd                             :  1;  // Bits 8:8
    UINT32 Ch0PiDFTEn                              :  1;  // Bits 9:9
    UINT32 Ch1PiDFTEn                              :  1;  // Bits 10:10
    UINT32 Spare                                   :  4;  // Bits 14:11
    UINT32 RefPiOvrd                               :  1;  // Bits 15:15
    UINT32 Rsvd                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7_CR_PIDFTDLY_STRUCT;

typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Load                                    :  1;  // Bits 1:1
    UINT32 ModeHVM                                 :  1;  // Bits 2:2
    UINT32 ModeDV                                  :  1;  // Bits 3:3
    UINT32 CalCfdl                                 :  1;  // Bits 4:4
    UINT32 LoadCount                               :  10;  // Bits 14:5
    UINT32 CountStatus                             :  10;  // Bits 24:15
    UINT32 ModeADC                                 :  1;  // Bits 25:25
    UINT32 ADCClkDiv                               :  2;  // Bits 27:26
    UINT32 ADCDdrChanSel                           :  1;  // Bits 28:28
    UINT32 ADCChopEn                               :  1;  // Bits 29:29
    UINT32 ADCDone                                 :  1;  // Bits 30:30
    UINT32 PhaseDrvPwrSavOn                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7_CR_DLLPITESTANDADC_STRUCT;

typedef union {
  struct {
    UINT32 DetrmLockStat                           :  1;  // Bits 0:0
    UINT32 FuncLockStat                            :  1;  // Bits 1:1
    UINT32 Lock                                    :  1;  // Bits 2:2
    UINT32 Timeout                                 :  1;  // Bits 3:3
    UINT32 DllReset                                :  1;  // Bits 4:4
    UINT32 LongLockStat                            :  1;  // Bits 5:5
    UINT32 EarlyLockStat                           :  1;  // Bits 6:6
    UINT32 NormalMode_NotWkLock                    :  1;  // Bits 7:7
    UINT32 ADCout                                  :  10;  // Bits 17:8
    UINT32 ADCStatus                               :  1;  // Bits 18:18
    UINT32 pilags                                  :  1;  // Bits 19:19
    UINT32 spare                                   :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7_CR_DLLSTATUS_STRUCT;

typedef union {
  struct {
    UINT32 start                                   :  1;  // Bits 0:0
    UINT32 clken                                   :  1;  // Bits 1:1
    UINT32 dcm_dccctl_en                           :  1;  // Bits 2:2
    UINT32 dccctl                                  :  4;  // Bits 6:3
    UINT32 duration                                :  3;  // Bits 9:7
    UINT32 dcm_done                                :  1;  // Bits 10:10
    UINT32 dcm_results                             :  15;  // Bits 25:11
    UINT32 spare0                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA7_CR_DLLDCMCTL_STRUCT;

typedef union {
  struct {
    UINT32 LockThresh                              :  3;  // Bits 2:0
    UINT32 LockCtr                                 :  2;  // Bits 4:3
    UINT32 VctrlDischRate                          :  2;  // Bits 6:5
    UINT32 SelVctrlHi                              :  1;  // Bits 7:7
    UINT32 StartupCntSel                           :  1;  // Bits 8:8
    UINT32 LockSel                                 :  2;  // Bits 10:9
    UINT32 RstOvrd                                 :  1;  // Bits 11:11
    UINT32 SelRstOvrd                              :  1;  // Bits 12:12
    UINT32 TimeOutOvrd                             :  1;  // Bits 13:13
    UINT32 SelTimeOutOvrd                          :  1;  // Bits 14:14
    UINT32 ClkGateOvrd                             :  1;  // Bits 15:15
    UINT32 LockOvrd                                :  1;  // Bits 16:16
    UINT32 SelLockOvrd                             :  1;  // Bits 17:17
    UINT32 OpenLoopOvrd                            :  1;  // Bits 18:18
    UINT32 SelOpenLoopOvrd                         :  1;  // Bits 19:19
    UINT32 WkLockEnOvrd                            :  1;  // Bits 20:20
    UINT32 SelWkLockEnOvrd                         :  1;  // Bits 21:21
    UINT32 CfdlDis                                 :  1;  // Bits 22:22
    UINT32 DftEn                                   :  1;  // Bits 23:23
    UINT32 spare0                                  :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8_CR_MASTERDLLCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllBWEn                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8_CR_CBTUNE0_STRUCT;

typedef union {
  struct {
    UINT32 PiCbEn                                  :  24;  // Bits 23:0
    UINT32 CbEnRsvd                                :  3;  // Bits 26:24
    UINT32 CbEnDllFuse                             :  3;  // Bits 29:27
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8_CR_CBTUNE1_STRUCT;

typedef union {
  struct {
    UINT32 ADC_frz                                 :  1;  // Bits 0:0
    UINT32 ADC_en                                  :  1;  // Bits 1:1
    UINT32 ADCclkdiv                               :  2;  // Bits 3:2
    UINT32 ADCstartcount                           :  2;  // Bits 5:4
    UINT32 ADCChopEn                               :  1;  // Bits 6:6
    UINT32 Spare                                   :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8_CR_ADCCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllCbEn                                 :  16;  // Bits 15:0
    UINT32 Spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8_CR_CBTUNE2_STRUCT;

typedef union {
  struct {
    UINT32 PiDftDelay                              :  7;  // Bits 6:0
    UINT32 Ch0PiEnOvrd                             :  1;  // Bits 7:7
    UINT32 Ch1PiEnOvrd                             :  1;  // Bits 8:8
    UINT32 Ch0PiDFTEn                              :  1;  // Bits 9:9
    UINT32 Ch1PiDFTEn                              :  1;  // Bits 10:10
    UINT32 Spare                                   :  4;  // Bits 14:11
    UINT32 RefPiOvrd                               :  1;  // Bits 15:15
    UINT32 Rsvd                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8_CR_PIDFTDLY_STRUCT;

typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Load                                    :  1;  // Bits 1:1
    UINT32 ModeHVM                                 :  1;  // Bits 2:2
    UINT32 ModeDV                                  :  1;  // Bits 3:3
    UINT32 CalCfdl                                 :  1;  // Bits 4:4
    UINT32 LoadCount                               :  10;  // Bits 14:5
    UINT32 CountStatus                             :  10;  // Bits 24:15
    UINT32 ModeADC                                 :  1;  // Bits 25:25
    UINT32 ADCClkDiv                               :  2;  // Bits 27:26
    UINT32 ADCDdrChanSel                           :  1;  // Bits 28:28
    UINT32 ADCChopEn                               :  1;  // Bits 29:29
    UINT32 ADCDone                                 :  1;  // Bits 30:30
    UINT32 PhaseDrvPwrSavOn                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8_CR_DLLPITESTANDADC_STRUCT;

typedef union {
  struct {
    UINT32 DetrmLockStat                           :  1;  // Bits 0:0
    UINT32 FuncLockStat                            :  1;  // Bits 1:1
    UINT32 Lock                                    :  1;  // Bits 2:2
    UINT32 Timeout                                 :  1;  // Bits 3:3
    UINT32 DllReset                                :  1;  // Bits 4:4
    UINT32 LongLockStat                            :  1;  // Bits 5:5
    UINT32 EarlyLockStat                           :  1;  // Bits 6:6
    UINT32 NormalMode_NotWkLock                    :  1;  // Bits 7:7
    UINT32 ADCout                                  :  10;  // Bits 17:8
    UINT32 ADCStatus                               :  1;  // Bits 18:18
    UINT32 pilags                                  :  1;  // Bits 19:19
    UINT32 spare                                   :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8_CR_DLLSTATUS_STRUCT;

typedef union {
  struct {
    UINT32 start                                   :  1;  // Bits 0:0
    UINT32 clken                                   :  1;  // Bits 1:1
    UINT32 dcm_dccctl_en                           :  1;  // Bits 2:2
    UINT32 dccctl                                  :  4;  // Bits 6:3
    UINT32 duration                                :  3;  // Bits 9:7
    UINT32 dcm_done                                :  1;  // Bits 10:10
    UINT32 dcm_results                             :  15;  // Bits 25:11
    UINT32 spare0                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRDATA8_CR_DLLDCMCTL_STRUCT;

typedef union {
  struct {
    UINT32 LockThresh                              :  3;  // Bits 2:0
    UINT32 LockCtr                                 :  2;  // Bits 4:3
    UINT32 VctrlDischRate                          :  2;  // Bits 6:5
    UINT32 SelVctrlHi                              :  1;  // Bits 7:7
    UINT32 StartupCntSel                           :  1;  // Bits 8:8
    UINT32 LockSel                                 :  2;  // Bits 10:9
    UINT32 RstOvrd                                 :  1;  // Bits 11:11
    UINT32 SelRstOvrd                              :  1;  // Bits 12:12
    UINT32 TimeOutOvrd                             :  1;  // Bits 13:13
    UINT32 SelTimeOutOvrd                          :  1;  // Bits 14:14
    UINT32 ClkGateOvrd                             :  1;  // Bits 15:15
    UINT32 LockOvrd                                :  1;  // Bits 16:16
    UINT32 SelLockOvrd                             :  1;  // Bits 17:17
    UINT32 OpenLoopOvrd                            :  1;  // Bits 18:18
    UINT32 SelOpenLoopOvrd                         :  1;  // Bits 19:19
    UINT32 WkLockEnOvrd                            :  1;  // Bits 20:20
    UINT32 SelWkLockEnOvrd                         :  1;  // Bits 21:21
    UINT32 CfdlDis                                 :  1;  // Bits 22:22
    UINT32 DftEn                                   :  1;  // Bits 23:23
    UINT32 spare0                                  :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTL1_CR_MASTERDLLCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllBWEn                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTL1_CR_CBTUNE0_STRUCT;

typedef union {
  struct {
    UINT32 PiCbEn                                  :  24;  // Bits 23:0
    UINT32 CbEnRsvd                                :  3;  // Bits 26:24
    UINT32 CbEnDllFuse                             :  3;  // Bits 29:27
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTL1_CR_CBTUNE1_STRUCT;

typedef union {
  struct {
    UINT32 ADC_frz                                 :  1;  // Bits 0:0
    UINT32 ADC_en                                  :  1;  // Bits 1:1
    UINT32 ADCclkdiv                               :  2;  // Bits 3:2
    UINT32 ADCstartcount                           :  2;  // Bits 5:4
    UINT32 ADCChopEn                               :  1;  // Bits 6:6
    UINT32 Spare                                   :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTL1_CR_ADCCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllCbEn                                 :  16;  // Bits 15:0
    UINT32 Spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTL1_CR_CBTUNE2_STRUCT;

typedef union {
  struct {
    UINT32 PiDftDelay                              :  7;  // Bits 6:0
    UINT32 Ch0PiEnOvrd                             :  1;  // Bits 7:7
    UINT32 Ch1PiEnOvrd                             :  1;  // Bits 8:8
    UINT32 Ch0PiDFTEn                              :  1;  // Bits 9:9
    UINT32 Ch1PiDFTEn                              :  1;  // Bits 10:10
    UINT32 Spare                                   :  4;  // Bits 14:11
    UINT32 RefPiOvrd                               :  1;  // Bits 15:15
    UINT32 Rsvd                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTL1_CR_PIDFTDLY_STRUCT;

typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Load                                    :  1;  // Bits 1:1
    UINT32 ModeHVM                                 :  1;  // Bits 2:2
    UINT32 ModeDV                                  :  1;  // Bits 3:3
    UINT32 CalCfdl                                 :  1;  // Bits 4:4
    UINT32 LoadCount                               :  10;  // Bits 14:5
    UINT32 CountStatus                             :  10;  // Bits 24:15
    UINT32 ModeADC                                 :  1;  // Bits 25:25
    UINT32 ADCClkDiv                               :  2;  // Bits 27:26
    UINT32 ADCDdrChanSel                           :  1;  // Bits 28:28
    UINT32 ADCChopEn                               :  1;  // Bits 29:29
    UINT32 ADCDone                                 :  1;  // Bits 30:30
    UINT32 PhaseDrvPwrSavOn                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTL1_CR_DLLPITESTANDADC_STRUCT;

typedef union {
  struct {
    UINT32 DetrmLockStat                           :  1;  // Bits 0:0
    UINT32 FuncLockStat                            :  1;  // Bits 1:1
    UINT32 Lock                                    :  1;  // Bits 2:2
    UINT32 Timeout                                 :  1;  // Bits 3:3
    UINT32 DllReset                                :  1;  // Bits 4:4
    UINT32 LongLockStat                            :  1;  // Bits 5:5
    UINT32 EarlyLockStat                           :  1;  // Bits 6:6
    UINT32 NormalMode_NotWkLock                    :  1;  // Bits 7:7
    UINT32 ADCout                                  :  10;  // Bits 17:8
    UINT32 ADCStatus                               :  1;  // Bits 18:18
    UINT32 pilags                                  :  1;  // Bits 19:19
    UINT32 spare                                   :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTL1_CR_DLLSTATUS_STRUCT;

typedef union {
  struct {
    UINT32 start                                   :  1;  // Bits 0:0
    UINT32 clken                                   :  1;  // Bits 1:1
    UINT32 dcm_dccctl_en                           :  1;  // Bits 2:2
    UINT32 dccctl                                  :  4;  // Bits 6:3
    UINT32 duration                                :  3;  // Bits 9:7
    UINT32 dcm_done                                :  1;  // Bits 10:10
    UINT32 dcm_results                             :  15;  // Bits 25:11
    UINT32 spare0                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTL1_CR_DLLDCMCTL_STRUCT;

typedef union {
  struct {
    UINT32 LockThresh                              :  3;  // Bits 2:0
    UINT32 LockCtr                                 :  2;  // Bits 4:3
    UINT32 VctrlDischRate                          :  2;  // Bits 6:5
    UINT32 SelVctrlHi                              :  1;  // Bits 7:7
    UINT32 StartupCntSel                           :  1;  // Bits 8:8
    UINT32 LockSel                                 :  2;  // Bits 10:9
    UINT32 RstOvrd                                 :  1;  // Bits 11:11
    UINT32 SelRstOvrd                              :  1;  // Bits 12:12
    UINT32 TimeOutOvrd                             :  1;  // Bits 13:13
    UINT32 SelTimeOutOvrd                          :  1;  // Bits 14:14
    UINT32 ClkGateOvrd                             :  1;  // Bits 15:15
    UINT32 LockOvrd                                :  1;  // Bits 16:16
    UINT32 SelLockOvrd                             :  1;  // Bits 17:17
    UINT32 OpenLoopOvrd                            :  1;  // Bits 18:18
    UINT32 SelOpenLoopOvrd                         :  1;  // Bits 19:19
    UINT32 WkLockEnOvrd                            :  1;  // Bits 20:20
    UINT32 SelWkLockEnOvrd                         :  1;  // Bits 21:21
    UINT32 CfdlDis                                 :  1;  // Bits 22:22
    UINT32 DftEn                                   :  1;  // Bits 23:23
    UINT32 spare0                                  :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMD0_CR_MASTERDLLCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllBWEn                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMD0_CR_CBTUNE0_STRUCT;

typedef union {
  struct {
    UINT32 PiCbEn                                  :  24;  // Bits 23:0
    UINT32 CbEnRsvd                                :  3;  // Bits 26:24
    UINT32 CbEnDllFuse                             :  3;  // Bits 29:27
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMD0_CR_CBTUNE1_STRUCT;

typedef union {
  struct {
    UINT32 ADC_frz                                 :  1;  // Bits 0:0
    UINT32 ADC_en                                  :  1;  // Bits 1:1
    UINT32 ADCclkdiv                               :  2;  // Bits 3:2
    UINT32 ADCstartcount                           :  2;  // Bits 5:4
    UINT32 ADCChopEn                               :  1;  // Bits 6:6
    UINT32 Spare                                   :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMD0_CR_ADCCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllCbEn                                 :  16;  // Bits 15:0
    UINT32 Spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMD0_CR_CBTUNE2_STRUCT;

typedef union {
  struct {
    UINT32 PiDftDelay                              :  7;  // Bits 6:0
    UINT32 Ch0PiEnOvrd                             :  1;  // Bits 7:7
    UINT32 Ch1PiEnOvrd                             :  1;  // Bits 8:8
    UINT32 Ch0PiDFTEn                              :  1;  // Bits 9:9
    UINT32 Ch1PiDFTEn                              :  1;  // Bits 10:10
    UINT32 Spare                                   :  4;  // Bits 14:11
    UINT32 RefPiOvrd                               :  1;  // Bits 15:15
    UINT32 Rsvd                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMD0_CR_PIDFTDLY_STRUCT;

typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Load                                    :  1;  // Bits 1:1
    UINT32 ModeHVM                                 :  1;  // Bits 2:2
    UINT32 ModeDV                                  :  1;  // Bits 3:3
    UINT32 CalCfdl                                 :  1;  // Bits 4:4
    UINT32 LoadCount                               :  10;  // Bits 14:5
    UINT32 CountStatus                             :  10;  // Bits 24:15
    UINT32 ModeADC                                 :  1;  // Bits 25:25
    UINT32 ADCClkDiv                               :  2;  // Bits 27:26
    UINT32 ADCDdrChanSel                           :  1;  // Bits 28:28
    UINT32 ADCChopEn                               :  1;  // Bits 29:29
    UINT32 ADCDone                                 :  1;  // Bits 30:30
    UINT32 PhaseDrvPwrSavOn                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMD0_CR_DLLPITESTANDADC_STRUCT;

typedef union {
  struct {
    UINT32 DetrmLockStat                           :  1;  // Bits 0:0
    UINT32 FuncLockStat                            :  1;  // Bits 1:1
    UINT32 Lock                                    :  1;  // Bits 2:2
    UINT32 Timeout                                 :  1;  // Bits 3:3
    UINT32 DllReset                                :  1;  // Bits 4:4
    UINT32 LongLockStat                            :  1;  // Bits 5:5
    UINT32 EarlyLockStat                           :  1;  // Bits 6:6
    UINT32 NormalMode_NotWkLock                    :  1;  // Bits 7:7
    UINT32 ADCout                                  :  10;  // Bits 17:8
    UINT32 ADCStatus                               :  1;  // Bits 18:18
    UINT32 pilags                                  :  1;  // Bits 19:19
    UINT32 spare                                   :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMD0_CR_DLLSTATUS_STRUCT;

typedef union {
  struct {
    UINT32 start                                   :  1;  // Bits 0:0
    UINT32 clken                                   :  1;  // Bits 1:1
    UINT32 dcm_dccctl_en                           :  1;  // Bits 2:2
    UINT32 dccctl                                  :  4;  // Bits 6:3
    UINT32 duration                                :  3;  // Bits 9:7
    UINT32 dcm_done                                :  1;  // Bits 10:10
    UINT32 dcm_results                             :  15;  // Bits 25:11
    UINT32 spare0                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMD0_CR_DLLDCMCTL_STRUCT;

typedef union {
  struct {
    UINT32 LockThresh                              :  3;  // Bits 2:0
    UINT32 LockCtr                                 :  2;  // Bits 4:3
    UINT32 VctrlDischRate                          :  2;  // Bits 6:5
    UINT32 SelVctrlHi                              :  1;  // Bits 7:7
    UINT32 StartupCntSel                           :  1;  // Bits 8:8
    UINT32 LockSel                                 :  2;  // Bits 10:9
    UINT32 RstOvrd                                 :  1;  // Bits 11:11
    UINT32 SelRstOvrd                              :  1;  // Bits 12:12
    UINT32 TimeOutOvrd                             :  1;  // Bits 13:13
    UINT32 SelTimeOutOvrd                          :  1;  // Bits 14:14
    UINT32 ClkGateOvrd                             :  1;  // Bits 15:15
    UINT32 LockOvrd                                :  1;  // Bits 16:16
    UINT32 SelLockOvrd                             :  1;  // Bits 17:17
    UINT32 OpenLoopOvrd                            :  1;  // Bits 18:18
    UINT32 SelOpenLoopOvrd                         :  1;  // Bits 19:19
    UINT32 WkLockEnOvrd                            :  1;  // Bits 20:20
    UINT32 SelWkLockEnOvrd                         :  1;  // Bits 21:21
    UINT32 CfdlDis                                 :  1;  // Bits 22:22
    UINT32 DftEn                                   :  1;  // Bits 23:23
    UINT32 spare0                                  :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMD1_CR_MASTERDLLCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllBWEn                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMD1_CR_CBTUNE0_STRUCT;

typedef union {
  struct {
    UINT32 PiCbEn                                  :  24;  // Bits 23:0
    UINT32 CbEnRsvd                                :  3;  // Bits 26:24
    UINT32 CbEnDllFuse                             :  3;  // Bits 29:27
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMD1_CR_CBTUNE1_STRUCT;

typedef union {
  struct {
    UINT32 ADC_frz                                 :  1;  // Bits 0:0
    UINT32 ADC_en                                  :  1;  // Bits 1:1
    UINT32 ADCclkdiv                               :  2;  // Bits 3:2
    UINT32 ADCstartcount                           :  2;  // Bits 5:4
    UINT32 ADCChopEn                               :  1;  // Bits 6:6
    UINT32 Spare                                   :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMD1_CR_ADCCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllCbEn                                 :  16;  // Bits 15:0
    UINT32 Spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMD1_CR_CBTUNE2_STRUCT;

typedef union {
  struct {
    UINT32 PiDftDelay                              :  7;  // Bits 6:0
    UINT32 Ch0PiEnOvrd                             :  1;  // Bits 7:7
    UINT32 Ch1PiEnOvrd                             :  1;  // Bits 8:8
    UINT32 Ch0PiDFTEn                              :  1;  // Bits 9:9
    UINT32 Ch1PiDFTEn                              :  1;  // Bits 10:10
    UINT32 Spare                                   :  4;  // Bits 14:11
    UINT32 RefPiOvrd                               :  1;  // Bits 15:15
    UINT32 Rsvd                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMD1_CR_PIDFTDLY_STRUCT;

typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Load                                    :  1;  // Bits 1:1
    UINT32 ModeHVM                                 :  1;  // Bits 2:2
    UINT32 ModeDV                                  :  1;  // Bits 3:3
    UINT32 CalCfdl                                 :  1;  // Bits 4:4
    UINT32 LoadCount                               :  10;  // Bits 14:5
    UINT32 CountStatus                             :  10;  // Bits 24:15
    UINT32 ModeADC                                 :  1;  // Bits 25:25
    UINT32 ADCClkDiv                               :  2;  // Bits 27:26
    UINT32 ADCDdrChanSel                           :  1;  // Bits 28:28
    UINT32 ADCChopEn                               :  1;  // Bits 29:29
    UINT32 ADCDone                                 :  1;  // Bits 30:30
    UINT32 PhaseDrvPwrSavOn                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMD1_CR_DLLPITESTANDADC_STRUCT;

typedef union {
  struct {
    UINT32 DetrmLockStat                           :  1;  // Bits 0:0
    UINT32 FuncLockStat                            :  1;  // Bits 1:1
    UINT32 Lock                                    :  1;  // Bits 2:2
    UINT32 Timeout                                 :  1;  // Bits 3:3
    UINT32 DllReset                                :  1;  // Bits 4:4
    UINT32 LongLockStat                            :  1;  // Bits 5:5
    UINT32 EarlyLockStat                           :  1;  // Bits 6:6
    UINT32 NormalMode_NotWkLock                    :  1;  // Bits 7:7
    UINT32 ADCout                                  :  10;  // Bits 17:8
    UINT32 ADCStatus                               :  1;  // Bits 18:18
    UINT32 pilags                                  :  1;  // Bits 19:19
    UINT32 spare                                   :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMD1_CR_DLLSTATUS_STRUCT;

typedef union {
  struct {
    UINT32 start                                   :  1;  // Bits 0:0
    UINT32 clken                                   :  1;  // Bits 1:1
    UINT32 dcm_dccctl_en                           :  1;  // Bits 2:2
    UINT32 dccctl                                  :  4;  // Bits 6:3
    UINT32 duration                                :  3;  // Bits 9:7
    UINT32 dcm_done                                :  1;  // Bits 10:10
    UINT32 dcm_results                             :  15;  // Bits 25:11
    UINT32 spare0                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCMD1_CR_DLLDCMCTL_STRUCT;

typedef union {
  struct {
    UINT32 LockThresh                              :  3;  // Bits 2:0
    UINT32 LockCtr                                 :  2;  // Bits 4:3
    UINT32 VctrlDischRate                          :  2;  // Bits 6:5
    UINT32 SelVctrlHi                              :  1;  // Bits 7:7
    UINT32 StartupCntSel                           :  1;  // Bits 8:8
    UINT32 LockSel                                 :  2;  // Bits 10:9
    UINT32 RstOvrd                                 :  1;  // Bits 11:11
    UINT32 SelRstOvrd                              :  1;  // Bits 12:12
    UINT32 TimeOutOvrd                             :  1;  // Bits 13:13
    UINT32 SelTimeOutOvrd                          :  1;  // Bits 14:14
    UINT32 ClkGateOvrd                             :  1;  // Bits 15:15
    UINT32 LockOvrd                                :  1;  // Bits 16:16
    UINT32 SelLockOvrd                             :  1;  // Bits 17:17
    UINT32 OpenLoopOvrd                            :  1;  // Bits 18:18
    UINT32 SelOpenLoopOvrd                         :  1;  // Bits 19:19
    UINT32 WkLockEnOvrd                            :  1;  // Bits 20:20
    UINT32 SelWkLockEnOvrd                         :  1;  // Bits 21:21
    UINT32 CfdlDis                                 :  1;  // Bits 22:22
    UINT32 DftEn                                   :  1;  // Bits 23:23
    UINT32 spare0                                  :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTL0_CR_MASTERDLLCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllBWEn                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTL0_CR_CBTUNE0_STRUCT;

typedef union {
  struct {
    UINT32 PiCbEn                                  :  24;  // Bits 23:0
    UINT32 CbEnRsvd                                :  3;  // Bits 26:24
    UINT32 CbEnDllFuse                             :  3;  // Bits 29:27
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTL0_CR_CBTUNE1_STRUCT;

typedef union {
  struct {
    UINT32 ADC_frz                                 :  1;  // Bits 0:0
    UINT32 ADC_en                                  :  1;  // Bits 1:1
    UINT32 ADCclkdiv                               :  2;  // Bits 3:2
    UINT32 ADCstartcount                           :  2;  // Bits 5:4
    UINT32 ADCChopEn                               :  1;  // Bits 6:6
    UINT32 Spare                                   :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTL0_CR_ADCCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllCbEn                                 :  16;  // Bits 15:0
    UINT32 Spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTL0_CR_CBTUNE2_STRUCT;

typedef union {
  struct {
    UINT32 PiDftDelay                              :  7;  // Bits 6:0
    UINT32 Ch0PiEnOvrd                             :  1;  // Bits 7:7
    UINT32 Ch1PiEnOvrd                             :  1;  // Bits 8:8
    UINT32 Ch0PiDFTEn                              :  1;  // Bits 9:9
    UINT32 Ch1PiDFTEn                              :  1;  // Bits 10:10
    UINT32 Spare                                   :  4;  // Bits 14:11
    UINT32 RefPiOvrd                               :  1;  // Bits 15:15
    UINT32 Rsvd                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTL0_CR_PIDFTDLY_STRUCT;

typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Load                                    :  1;  // Bits 1:1
    UINT32 ModeHVM                                 :  1;  // Bits 2:2
    UINT32 ModeDV                                  :  1;  // Bits 3:3
    UINT32 CalCfdl                                 :  1;  // Bits 4:4
    UINT32 LoadCount                               :  10;  // Bits 14:5
    UINT32 CountStatus                             :  10;  // Bits 24:15
    UINT32 ModeADC                                 :  1;  // Bits 25:25
    UINT32 ADCClkDiv                               :  2;  // Bits 27:26
    UINT32 ADCDdrChanSel                           :  1;  // Bits 28:28
    UINT32 ADCChopEn                               :  1;  // Bits 29:29
    UINT32 ADCDone                                 :  1;  // Bits 30:30
    UINT32 PhaseDrvPwrSavOn                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTL0_CR_DLLPITESTANDADC_STRUCT;

typedef union {
  struct {
    UINT32 DetrmLockStat                           :  1;  // Bits 0:0
    UINT32 FuncLockStat                            :  1;  // Bits 1:1
    UINT32 Lock                                    :  1;  // Bits 2:2
    UINT32 Timeout                                 :  1;  // Bits 3:3
    UINT32 DllReset                                :  1;  // Bits 4:4
    UINT32 LongLockStat                            :  1;  // Bits 5:5
    UINT32 EarlyLockStat                           :  1;  // Bits 6:6
    UINT32 NormalMode_NotWkLock                    :  1;  // Bits 7:7
    UINT32 ADCout                                  :  10;  // Bits 17:8
    UINT32 ADCStatus                               :  1;  // Bits 18:18
    UINT32 pilags                                  :  1;  // Bits 19:19
    UINT32 spare                                   :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTL0_CR_DLLSTATUS_STRUCT;

typedef union {
  struct {
    UINT32 start                                   :  1;  // Bits 0:0
    UINT32 clken                                   :  1;  // Bits 1:1
    UINT32 dcm_dccctl_en                           :  1;  // Bits 2:2
    UINT32 dccctl                                  :  4;  // Bits 6:3
    UINT32 duration                                :  3;  // Bits 9:7
    UINT32 dcm_done                                :  1;  // Bits 10:10
    UINT32 dcm_results                             :  15;  // Bits 25:11
    UINT32 spare0                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTL0_CR_DLLDCMCTL_STRUCT;

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
} DDRCKECH0_CR_DDRCRCMDCOMP_STRUCT;

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
} DDRCKECH0_CR_DDRCRCMDCOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 CtlCkTxEn                               :  8;  // Bits 7:0
    UINT32 PiClkEn                                 :  4;  // Bits 11:8
    UINT32 DdrCkeCmdSlwDlyByp                      :  1;  // Bits 12:12
    UINT32 DdrCtlCkeSlwDlyByp                      :  1;  // Bits 13:13
    UINT32 PrtEn                                   :  1;  // Bits 14:14
    UINT32 AlrtEn                                  :  1;  // Bits 15:15
    UINT32 cke_pi_gate_sr_only                     :  1;  // Bits 16:16
    UINT32 Gear1                                   :  1;  // Bits 17:17
    UINT32 lp4xvoltageselect                       :  1;  // Bits 18:18
    UINT32 xover_mindelay_ctl                      :  2;  // Bits 20:19
    UINT32 cmd_eq_strengh                          :  4;  // Bits 24:21
    UINT32 cmd_eq_en                               :  1;  // Bits 25:25
    UINT32 cmd_eq_constz                           :  1;  // Bits 26:26
    UINT32 CkeCriClkGateEnGvBlock                  :  1;  // Bits 27:27
    UINT32 Spare                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCKECH0_CR_DDRCRCKERANKSUSED_STRUCT;

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
} DDRCKECH0_CR_DDRCRCTLCOMP_STRUCT;

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
} DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_STRUCT;

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
} DDRCKECH0_CR_DDRCRCTLPICODING_STRUCT;

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
} DDRCKECH0_CR_DDRCRCTLCONTROLS_STRUCT;

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
} DDRCKECH0_CR_DDRCRCTLCONTROLS1_STRUCT;

typedef union {
  struct {
    UINT32 datatrainfeedback                       :  10;  // Bits 9:0
    UINT32 Spare                                   :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCKECH0_CR_DDRCRLOOPBACKFEEDBACK_STRUCT;

typedef union {
  struct {
    UINT32 CtlTcoComp                              :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCKECH0_CR_DDRCRCTLTCOCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 CmdTcoComp                              :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCKECH0_CR_DDRCRCMDTCOCONTROL0_STRUCT;

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
} DDRCKECH1_CR_DDRCRCMDCOMP_STRUCT;

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
} DDRCKECH1_CR_DDRCRCMDCOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 CtlCkTxEn                               :  8;  // Bits 7:0
    UINT32 PiClkEn                                 :  4;  // Bits 11:8
    UINT32 DdrCkeCmdSlwDlyByp                      :  1;  // Bits 12:12
    UINT32 DdrCtlCkeSlwDlyByp                      :  1;  // Bits 13:13
    UINT32 PrtEn                                   :  1;  // Bits 14:14
    UINT32 AlrtEn                                  :  1;  // Bits 15:15
    UINT32 cke_pi_gate_sr_only                     :  1;  // Bits 16:16
    UINT32 Gear1                                   :  1;  // Bits 17:17
    UINT32 lp4xvoltageselect                       :  1;  // Bits 18:18
    UINT32 xover_mindelay_ctl                      :  2;  // Bits 20:19
    UINT32 cmd_eq_strengh                          :  4;  // Bits 24:21
    UINT32 cmd_eq_en                               :  1;  // Bits 25:25
    UINT32 cmd_eq_constz                           :  1;  // Bits 26:26
    UINT32 CkeCriClkGateEnGvBlock                  :  1;  // Bits 27:27
    UINT32 Spare                                   :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCKECH1_CR_DDRCRCKERANKSUSED_STRUCT;

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
} DDRCKECH1_CR_DDRCRCTLCOMP_STRUCT;

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
} DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_STRUCT;

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
} DDRCKECH1_CR_DDRCRCTLPICODING_STRUCT;

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
} DDRCKECH1_CR_DDRCRCTLCONTROLS_STRUCT;

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
} DDRCKECH1_CR_DDRCRCTLCONTROLS1_STRUCT;

typedef union {
  struct {
    UINT32 datatrainfeedback                       :  10;  // Bits 9:0
    UINT32 Spare                                   :  22;  // Bits 31:10
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCKECH1_CR_DDRCRLOOPBACKFEEDBACK_STRUCT;

typedef union {
  struct {
    UINT32 CtlTcoComp                              :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCKECH1_CR_DDRCRCTLTCOCONTROL0_STRUCT;

typedef union {
  struct {
    UINT32 CmdTcoComp                              :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCKECH1_CR_DDRCRCMDTCOCONTROL0_STRUCT;

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
} DDRVREF_CR_DDRRCOMPDATA_STRUCT;

typedef union {
  struct {
    UINT32 HiBWDivider                             :  2;  // Bits 1:0
    UINT32 LoBWDivider                             :  2;  // Bits 3:2
    UINT32 SampleDivider                           :  3;  // Bits 6:4
    UINT32 OpenLoop                                :  1;  // Bits 7:7
    UINT32 SlowBWError                             :  2;  // Bits 9:8
    UINT32 HiBWEnable                              :  1;  // Bits 10:10
    UINT32 VtSlopeB                                :  3;  // Bits 13:11
    UINT32 VtSlopeA                                :  3;  // Bits 16:14
    UINT32 VtOffset                                :  4;  // Bits 20:17
    UINT32 SelCode                                 :  3;  // Bits 23:21
    UINT32 OutputCode                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVREF_CR_DDRCRVREFCONTROL_STRUCT;

typedef union {
  struct {
    UINT32 CAVrefIntCtl                            :  9;  // Bits 8:0
    UINT32 Ch1VrefIntCtl                           :  9;  // Bits 17:9
    UINT32 Ch0VrefIntCtl                           :  9;  // Bits 26:18
    UINT32 EnDimmVrefCA                            :  1;  // Bits 27:27
    UINT32 EnDimmVrefCh1                           :  1;  // Bits 28:28
    UINT32 EnDimmVrefCh0                           :  1;  // Bits 29:29
    UINT32 VrefDimmSagvSlowBWTargetCodeChange      :  1;  // Bits 30:30
    UINT32 VrefDimmSagvAnalogEn                    :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVREF_CR_DDRCRVREFADJUST1_STRUCT_A0;

typedef union {
  struct {
    UINT32 Ch0Dimm0CaVrefIntCtl                    :  9;  // Bits 8:0
    UINT32 Ch1Dimm0CaVrefIntCtl                    :  9;  // Bits 17:9
    UINT32 Ch0Dimm1CaVrefIntCtl                    :  9;  // Bits 26:18
    UINT32 Ch0Dimm0CaVrefEn                        :  1;  // Bits 27:27
    UINT32 Ch1Dimm0CaVrefEn                        :  1;  // Bits 28:28
    UINT32 Ch0Dimm1CaVrefEn                        :  1;  // Bits 29:29
    UINT32 VrefDimmSagvSlowBWTargetCodeChange      :  1;  // Bits 30:30
    UINT32 VrefDimmSagvAnalogEn                    :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVREF_CR_DDRCRVREFADJUST1_STRUCT;

typedef union {
  struct {
    UINT32 HiZTimerCtrl                            :  2;  // Bits 1:0
    UINT32 caSlowBW                                :  1;  // Bits 2:2
    UINT32 ch0SlowBW                               :  1;  // Bits 3:3
    UINT32 ch1SlowBW                               :  1;  // Bits 4:4
    UINT32 Rsvd                                    :  8;  // Bits 12:5
    UINT32 VtSlopeBOnSAGV                          :  3;  // Bits 15:13
    UINT32 VtSlopeAOnSAGV                          :  3;  // Bits 18:16
    UINT32 VtOffsetOnSAGV                          :  4;  // Bits 22:19
    UINT32 vtcompovrden                            :  1;  // Bits 23:23
    UINT32 vtcompovrd                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVREF_CR_DDRCRVREFADJUST2_STRUCT_A0;

typedef union {
  struct {
    UINT32 HiZTimerCtrl                            :  2;  // Bits 1:0
    UINT32 CaCh0Dimm0SlowBW                        :  1;  // Bits 2:2
    UINT32 CaCh0Dimm1SlowBW                        :  1;  // Bits 3:3
    UINT32 CaCh1Dimm0SlowBW                        :  1;  // Bits 4:4
    UINT32 CaCh1Dimm1SlowBW                        :  1;  // Bits 5:5
    UINT32 Rsvd                                    :  7;  // Bits 12:6
    UINT32 VtSlopeBOnSAGV                          :  3;  // Bits 15:13
    UINT32 VtSlopeAOnSAGV                          :  3;  // Bits 18:16
    UINT32 VtOffsetOnSAGV                          :  4;  // Bits 22:19
    UINT32 vtcompovrden                            :  1;  // Bits 23:23
    UINT32 vtcompovrd                              :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVREF_CR_DDRCRVREFADJUST2_STRUCT;

typedef union {
  struct {
    UINT32 Ch1Dimm1CaVrefIntCtl                    :  9;  // Bits 8:0
    UINT32 Ch1Dimm1CaVrefEn                        :  1;  // Bits 9:9
    UINT32 VrefDimmSagvSlowBWTargetCodeChangeRep   :  1;  // Bits 10:10
    UINT32 spare                                   :  21;  // Bits 31:11
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVREF_CR_DDRCRVREFADJUST3_STRUCT;

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
} DDRVSSHIBOTA_CR_DDRRCOMPDATA_STRUCT;

typedef union {
  struct {
    UINT32 Target                                  :  6;  // Bits 5:0
    UINT32 HiBWDivider                             :  2;  // Bits 7:6
    UINT32 LoBWDivider                             :  2;  // Bits 9:8
    UINT32 SampleDivider                           :  2;  // Bits 11:10
    UINT32 EnIdleActiveSwap                        :  1;  // Bits 12:12
    UINT32 OpenLoop                                :  1;  // Bits 13:13
    UINT32 BWError                                 :  2;  // Bits 15:14
    UINT32 PanicEn                                 :  1;  // Bits 16:16
    UINT32 EnCkePanic                              :  1;  // Bits 17:17
    UINT32 Spare1                                  :  4;  // Bits 21:18
    UINT32 GainBoost                               :  1;  // Bits 22:22
    UINT32 SelCode                                 :  1;  // Bits 23:23
    UINT32 DisableOverFlowDrv                      :  1;  // Bits 24:24
    UINT32 OutputCode                              :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVSSHIBOTA_CR_DDRCRVSSHICONTROL_STRUCT;

typedef union {
  struct {
    UINT32 spare1                                  :  4;  // Bits 3:0
    UINT32 Panic                                   :  5;  // Bits 8:4
    UINT32 spare2                                  :  2;  // Bits 10:9
    UINT32 DisSensorPwrDn                          :  1;  // Bits 11:11
    UINT32 OfstOvrdEn                              :  1;  // Bits 12:12
    UINT32 ViewOfstsel                             :  3;  // Bits 15:13
    UINT32 envttcompforvsshi                       :  1;  // Bits 16:16
    UINT32 DdrCRForceODTOn                         :  1;  // Bits 17:17
    UINT32 VccddqHi                                :  1;  // Bits 18:18
    UINT32 VccddqLo                                :  1;  // Bits 19:19
    UINT32 EnVttOdt                                :  1;  // Bits 20:20
    UINT32 SalCompLegacyCbit                       :  1;  // Bits 21:21
    UINT32 spare3                                  :  2;  // Bits 23:22
    UINT32 VssHiGndSel                             :  1;  // Bits 24:24
    UINT32 Disable2Vt                              :  1;  // Bits 25:25
    UINT32 OfstOvrd                                :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_STRUCT;

typedef union {
  struct {
    UINT32 PanicSpareCompOfst                      :  6;  // Bits 5:0
    UINT32 PanicTargetCompOfst                     :  6;  // Bits 11:6
    UINT32 PanicLoCompOfst                         :  6;  // Bits 17:12
    UINT32 PanicHiCompOfst                         :  6;  // Bits 23:18
    UINT32 spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 View                                    :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL1_STRUCT;

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
} DDRVSSHITOPA_CR_DDRRCOMPDATA_STRUCT;

typedef union {
  struct {
    UINT32 Target                                  :  6;  // Bits 5:0
    UINT32 HiBWDivider                             :  2;  // Bits 7:6
    UINT32 LoBWDivider                             :  2;  // Bits 9:8
    UINT32 SampleDivider                           :  2;  // Bits 11:10
    UINT32 EnIdleActiveSwap                        :  1;  // Bits 12:12
    UINT32 OpenLoop                                :  1;  // Bits 13:13
    UINT32 BWError                                 :  2;  // Bits 15:14
    UINT32 PanicEn                                 :  1;  // Bits 16:16
    UINT32 EnCkePanic                              :  1;  // Bits 17:17
    UINT32 Spare1                                  :  4;  // Bits 21:18
    UINT32 GainBoost                               :  1;  // Bits 22:22
    UINT32 SelCode                                 :  1;  // Bits 23:23
    UINT32 DisableOverFlowDrv                      :  1;  // Bits 24:24
    UINT32 OutputCode                              :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVSSHITOPA_CR_DDRCRVSSHICONTROL_STRUCT;

typedef union {
  struct {
    UINT32 spare1                                  :  4;  // Bits 3:0
    UINT32 Panic                                   :  5;  // Bits 8:4
    UINT32 spare2                                  :  2;  // Bits 10:9
    UINT32 DisSensorPwrDn                          :  1;  // Bits 11:11
    UINT32 OfstOvrdEn                              :  1;  // Bits 12:12
    UINT32 ViewOfstsel                             :  3;  // Bits 15:13
    UINT32 envttcompforvsshi                       :  1;  // Bits 16:16
    UINT32 DdrCRForceODTOn                         :  1;  // Bits 17:17
    UINT32 VccddqHi                                :  1;  // Bits 18:18
    UINT32 VccddqLo                                :  1;  // Bits 19:19
    UINT32 EnVttOdt                                :  1;  // Bits 20:20
    UINT32 SalCompLegacyCbit                       :  1;  // Bits 21:21
    UINT32 spare3                                  :  2;  // Bits 23:22
    UINT32 VssHiGndSel                             :  1;  // Bits 24:24
    UINT32 Disable2Vt                              :  1;  // Bits 25:25
    UINT32 OfstOvrd                                :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL_STRUCT;

typedef union {
  struct {
    UINT32 PanicSpareCompOfst                      :  6;  // Bits 5:0
    UINT32 PanicTargetCompOfst                     :  6;  // Bits 11:6
    UINT32 PanicLoCompOfst                         :  6;  // Bits 17:12
    UINT32 PanicHiCompOfst                         :  6;  // Bits 23:18
    UINT32 spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 View                                    :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVSSHITOPA_CR_DDRCRVTTFORVSSHICORNRTROL1_STRUCT;

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
} DDRVSSHICENTA_CR_DDRRCOMPDATA_STRUCT;

typedef union {
  struct {
    UINT32 Target                                  :  6;  // Bits 5:0
    UINT32 HiBWDivider                             :  2;  // Bits 7:6
    UINT32 LoBWDivider                             :  2;  // Bits 9:8
    UINT32 SampleDivider                           :  2;  // Bits 11:10
    UINT32 EnIdleActiveSwap                        :  1;  // Bits 12:12
    UINT32 OpenLoop                                :  1;  // Bits 13:13
    UINT32 BWError                                 :  2;  // Bits 15:14
    UINT32 PanicEn                                 :  1;  // Bits 16:16
    UINT32 EnCkePanic                              :  1;  // Bits 17:17
    UINT32 Spare1                                  :  4;  // Bits 21:18
    UINT32 GainBoost                               :  1;  // Bits 22:22
    UINT32 SelCode                                 :  1;  // Bits 23:23
    UINT32 DisableOverFlowDrv                      :  1;  // Bits 24:24
    UINT32 OutputCode                              :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVSSHICENTA_CR_DDRCRVSSHICONTROL_STRUCT;

typedef union {
  struct {
    UINT32 spare1                                  :  4;  // Bits 3:0
    UINT32 Panic                                   :  5;  // Bits 8:4
    UINT32 spare2                                  :  2;  // Bits 10:9
    UINT32 DisSensorPwrDn                          :  1;  // Bits 11:11
    UINT32 OfstOvrdEn                              :  1;  // Bits 12:12
    UINT32 ViewOfstsel                             :  3;  // Bits 15:13
    UINT32 envttcompforvsshi                       :  1;  // Bits 16:16
    UINT32 DdrCRForceODTOn                         :  1;  // Bits 17:17
    UINT32 VccddqHi                                :  1;  // Bits 18:18
    UINT32 VccddqLo                                :  1;  // Bits 19:19
    UINT32 EnVttOdt                                :  1;  // Bits 20:20
    UINT32 SalCompLegacyCbit                       :  1;  // Bits 21:21
    UINT32 spare3                                  :  2;  // Bits 23:22
    UINT32 VssHiGndSel                             :  1;  // Bits 24:24
    UINT32 Disable2Vt                              :  1;  // Bits 25:25
    UINT32 OfstOvrd                                :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL_STRUCT;

typedef union {
  struct {
    UINT32 PanicSpareCompOfst                      :  6;  // Bits 5:0
    UINT32 PanicTargetCompOfst                     :  6;  // Bits 11:6
    UINT32 PanicLoCompOfst                         :  6;  // Bits 17:12
    UINT32 PanicHiCompOfst                         :  6;  // Bits 23:18
    UINT32 spare                                   :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICOMPOFFSET_STRUCT;

typedef union {
  struct {
    UINT32 View                                    :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVSSHICENTA_CR_DDRCRVTTFORVSSHICORNRTROL1_STRUCT;

typedef union {
  struct {
    UINT32 LockThresh                              :  3;  // Bits 2:0
    UINT32 LockCtr                                 :  2;  // Bits 4:3
    UINT32 VctrlDischRate                          :  2;  // Bits 6:5
    UINT32 SelVctrlHi                              :  1;  // Bits 7:7
    UINT32 StartupCntSel                           :  1;  // Bits 8:8
    UINT32 LockSel                                 :  2;  // Bits 10:9
    UINT32 RstOvrd                                 :  1;  // Bits 11:11
    UINT32 SelRstOvrd                              :  1;  // Bits 12:12
    UINT32 TimeOutOvrd                             :  1;  // Bits 13:13
    UINT32 SelTimeOutOvrd                          :  1;  // Bits 14:14
    UINT32 ClkGateOvrd                             :  1;  // Bits 15:15
    UINT32 LockOvrd                                :  1;  // Bits 16:16
    UINT32 SelLockOvrd                             :  1;  // Bits 17:17
    UINT32 OpenLoopOvrd                            :  1;  // Bits 18:18
    UINT32 SelOpenLoopOvrd                         :  1;  // Bits 19:19
    UINT32 WkLockEnOvrd                            :  1;  // Bits 20:20
    UINT32 SelWkLockEnOvrd                         :  1;  // Bits 21:21
    UINT32 CfdlDis                                 :  1;  // Bits 22:22
    UINT32 DftEn                                   :  1;  // Bits 23:23
    UINT32 spare0                                  :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE_CR_MASTERDLLCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllBWEn                                 :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE_CR_CBTUNE0_STRUCT;

typedef union {
  struct {
    UINT32 PiCbEn                                  :  24;  // Bits 23:0
    UINT32 CbEnRsvd                                :  3;  // Bits 26:24
    UINT32 CbEnDllFuse                             :  3;  // Bits 29:27
    UINT32 Spare                                   :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE_CR_CBTUNE1_STRUCT;

typedef union {
  struct {
    UINT32 ADC_frz                                 :  1;  // Bits 0:0
    UINT32 ADC_en                                  :  1;  // Bits 1:1
    UINT32 ADCclkdiv                               :  2;  // Bits 3:2
    UINT32 ADCstartcount                           :  2;  // Bits 5:4
    UINT32 ADCChopEn                               :  1;  // Bits 6:6
    UINT32 Spare                                   :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE_CR_ADCCFG_STRUCT;

typedef union {
  struct {
    UINT32 DllCbEn                                 :  16;  // Bits 15:0
    UINT32 Spare                                   :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE_CR_CBTUNE2_STRUCT;

typedef union {
  struct {
    UINT32 PiDftDelay                              :  7;  // Bits 6:0
    UINT32 Ch0PiEnOvrd                             :  1;  // Bits 7:7
    UINT32 Ch1PiEnOvrd                             :  1;  // Bits 8:8
    UINT32 Ch0PiDFTEn                              :  1;  // Bits 9:9
    UINT32 Ch1PiDFTEn                              :  1;  // Bits 10:10
    UINT32 Spare                                   :  4;  // Bits 14:11
    UINT32 RefPiOvrd                               :  1;  // Bits 15:15
    UINT32 Rsvd                                    :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE_CR_PIDFTDLY_STRUCT;

typedef union {
  struct {
    UINT32 RunTest                                 :  1;  // Bits 0:0
    UINT32 Load                                    :  1;  // Bits 1:1
    UINT32 ModeHVM                                 :  1;  // Bits 2:2
    UINT32 ModeDV                                  :  1;  // Bits 3:3
    UINT32 CalCfdl                                 :  1;  // Bits 4:4
    UINT32 LoadCount                               :  10;  // Bits 14:5
    UINT32 CountStatus                             :  10;  // Bits 24:15
    UINT32 ModeADC                                 :  1;  // Bits 25:25
    UINT32 ADCClkDiv                               :  2;  // Bits 27:26
    UINT32 ADCDdrChanSel                           :  1;  // Bits 28:28
    UINT32 ADCChopEn                               :  1;  // Bits 29:29
    UINT32 ADCDone                                 :  1;  // Bits 30:30
    UINT32 PhaseDrvPwrSavOn                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE_CR_DLLPITESTANDADC_STRUCT;

typedef union {
  struct {
    UINT32 DetrmLockStat                           :  1;  // Bits 0:0
    UINT32 FuncLockStat                            :  1;  // Bits 1:1
    UINT32 Lock                                    :  1;  // Bits 2:2
    UINT32 Timeout                                 :  1;  // Bits 3:3
    UINT32 DllReset                                :  1;  // Bits 4:4
    UINT32 LongLockStat                            :  1;  // Bits 5:5
    UINT32 EarlyLockStat                           :  1;  // Bits 6:6
    UINT32 NormalMode_NotWkLock                    :  1;  // Bits 7:7
    UINT32 ADCout                                  :  10;  // Bits 17:8
    UINT32 ADCStatus                               :  1;  // Bits 18:18
    UINT32 pilags                                  :  1;  // Bits 19:19
    UINT32 spare                                   :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE_CR_DLLSTATUS_STRUCT;

typedef union {
  struct {
    UINT32 start                                   :  1;  // Bits 0:0
    UINT32 clken                                   :  1;  // Bits 1:1
    UINT32 dcm_dccctl_en                           :  1;  // Bits 2:2
    UINT32 dccctl                                  :  4;  // Bits 6:3
    UINT32 duration                                :  3;  // Bits 9:7
    UINT32 dcm_done                                :  1;  // Bits 10:10
    UINT32 dcm_results                             :  15;  // Bits 25:11
    UINT32 spare0                                  :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRCTLCLKCKE_CR_DLLDCMCTL_STRUCT;

typedef union {
  struct {
    UINT32 Target                                  :  7;  // Bits 6:0
    UINT32 Panic                                   :  5;  // Bits 11:7
    UINT32 DisSensorPwrDn                          :  1;  // Bits 12:12
    UINT32 OfstOvrdEn                              :  1;  // Bits 13:13
    UINT32 ViewOfstsel                             :  3;  // Bits 16:14
    UINT32 DdrCRForceODTOn                         :  1;  // Bits 17:17
    UINT32 SalCompLegacyCbit                       :  1;  // Bits 18:18
    UINT32 Spare                                   :  1;  // Bits 19:19
    UINT32 EnVttOdt                                :  1;  // Bits 20:20
    UINT32 PmosOrNmosComperatorTypeSel             :  1;  // Bits 21:21
    UINT32 UsePmosOffsetComp                       :  1;  // Bits 22:22
    UINT32 Enable2VtPmos                           :  1;  // Bits 23:23
    UINT32 Enable2VtNmos                           :  1;  // Bits 24:24
    UINT32 Disable2Vt                              :  1;  // Bits 25:25
    UINT32 OfstOvrd                                :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_STRUCT;

typedef union {
  struct {
    UINT32 DdrVttMainFsmLegacy                     :  1;  // Bits 0:0
    UINT32 VttUsePmosCompCRThreshold               :  7;  // Bits 7:1
    UINT32 LowVoltageParkMode                      :  1;  // Bits 8:8
    UINT32 Spare                                   :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_STRUCT;

typedef union {
  struct {
    UINT32 View                                    :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVTTTOP0_CR_DDRCRVTTGENCONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 Target                                  :  7;  // Bits 6:0
    UINT32 Panic                                   :  5;  // Bits 11:7
    UINT32 DisSensorPwrDn                          :  1;  // Bits 12:12
    UINT32 OfstOvrdEn                              :  1;  // Bits 13:13
    UINT32 ViewOfstsel                             :  3;  // Bits 16:14
    UINT32 DdrCRForceODTOn                         :  1;  // Bits 17:17
    UINT32 SalCompLegacyCbit                       :  1;  // Bits 18:18
    UINT32 Spare                                   :  1;  // Bits 19:19
    UINT32 EnVttOdt                                :  1;  // Bits 20:20
    UINT32 PmosOrNmosComperatorTypeSel             :  1;  // Bits 21:21
    UINT32 UsePmosOffsetComp                       :  1;  // Bits 22:22
    UINT32 Enable2VtPmos                           :  1;  // Bits 23:23
    UINT32 Enable2VtNmos                           :  1;  // Bits 24:24
    UINT32 Disable2Vt                              :  1;  // Bits 25:25
    UINT32 OfstOvrd                                :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_STRUCT;

typedef union {
  struct {
    UINT32 DdrVttMainFsmLegacy                     :  1;  // Bits 0:0
    UINT32 VttUsePmosCompCRThreshold               :  7;  // Bits 7:1
    UINT32 LowVoltageParkMode                      :  1;  // Bits 8:8
    UINT32 Spare                                   :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL2_STRUCT;

typedef union {
  struct {
    UINT32 View                                    :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 Target                                  :  7;  // Bits 6:0
    UINT32 Panic                                   :  5;  // Bits 11:7
    UINT32 DisSensorPwrDn                          :  1;  // Bits 12:12
    UINT32 OfstOvrdEn                              :  1;  // Bits 13:13
    UINT32 ViewOfstsel                             :  3;  // Bits 16:14
    UINT32 DdrCRForceODTOn                         :  1;  // Bits 17:17
    UINT32 SalCompLegacyCbit                       :  1;  // Bits 18:18
    UINT32 Spare                                   :  1;  // Bits 19:19
    UINT32 EnVttOdt                                :  1;  // Bits 20:20
    UINT32 PmosOrNmosComperatorTypeSel             :  1;  // Bits 21:21
    UINT32 UsePmosOffsetComp                       :  1;  // Bits 22:22
    UINT32 Enable2VtPmos                           :  1;  // Bits 23:23
    UINT32 Enable2VtNmos                           :  1;  // Bits 24:24
    UINT32 Disable2Vt                              :  1;  // Bits 25:25
    UINT32 OfstOvrd                                :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_STRUCT;

typedef union {
  struct {
    UINT32 DdrVttMainFsmLegacy                     :  1;  // Bits 0:0
    UINT32 VttUsePmosCompCRThreshold               :  7;  // Bits 7:1
    UINT32 LowVoltageParkMode                      :  1;  // Bits 8:8
    UINT32 Spare                                   :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL2_STRUCT;

typedef union {
  struct {
    UINT32 View                                    :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 Target                                  :  7;  // Bits 6:0
    UINT32 Panic                                   :  5;  // Bits 11:7
    UINT32 DisSensorPwrDn                          :  1;  // Bits 12:12
    UINT32 OfstOvrdEn                              :  1;  // Bits 13:13
    UINT32 ViewOfstsel                             :  3;  // Bits 16:14
    UINT32 DdrCRForceODTOn                         :  1;  // Bits 17:17
    UINT32 SalCompLegacyCbit                       :  1;  // Bits 18:18
    UINT32 Spare                                   :  1;  // Bits 19:19
    UINT32 EnVttOdt                                :  1;  // Bits 20:20
    UINT32 PmosOrNmosComperatorTypeSel             :  1;  // Bits 21:21
    UINT32 UsePmosOffsetComp                       :  1;  // Bits 22:22
    UINT32 Enable2VtPmos                           :  1;  // Bits 23:23
    UINT32 Enable2VtNmos                           :  1;  // Bits 24:24
    UINT32 Disable2Vt                              :  1;  // Bits 25:25
    UINT32 OfstOvrd                                :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_STRUCT;

typedef union {
  struct {
    UINT32 DdrVttMainFsmLegacy                     :  1;  // Bits 0:0
    UINT32 VttUsePmosCompCRThreshold               :  7;  // Bits 7:1
    UINT32 LowVoltageParkMode                      :  1;  // Bits 8:8
    UINT32 Spare                                   :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVTTBOT0_CR_DDRCRVTTGENCONTROL2_STRUCT;

typedef union {
  struct {
    UINT32 View                                    :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVTTBOT0_CR_DDRCRVTTGENCONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 Target                                  :  7;  // Bits 6:0
    UINT32 Panic                                   :  5;  // Bits 11:7
    UINT32 DisSensorPwrDn                          :  1;  // Bits 12:12
    UINT32 OfstOvrdEn                              :  1;  // Bits 13:13
    UINT32 ViewOfstsel                             :  3;  // Bits 16:14
    UINT32 DdrCRForceODTOn                         :  1;  // Bits 17:17
    UINT32 SalCompLegacyCbit                       :  1;  // Bits 18:18
    UINT32 Spare                                   :  1;  // Bits 19:19
    UINT32 EnVttOdt                                :  1;  // Bits 20:20
    UINT32 PmosOrNmosComperatorTypeSel             :  1;  // Bits 21:21
    UINT32 UsePmosOffsetComp                       :  1;  // Bits 22:22
    UINT32 Enable2VtPmos                           :  1;  // Bits 23:23
    UINT32 Enable2VtNmos                           :  1;  // Bits 24:24
    UINT32 Disable2Vt                              :  1;  // Bits 25:25
    UINT32 OfstOvrd                                :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_STRUCT;

typedef union {
  struct {
    UINT32 DdrVttMainFsmLegacy                     :  1;  // Bits 0:0
    UINT32 VttUsePmosCompCRThreshold               :  7;  // Bits 7:1
    UINT32 LowVoltageParkMode                      :  1;  // Bits 8:8
    UINT32 Spare                                   :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVTTTOP1_CR_DDRCRVTTGENCONTROL2_STRUCT;

typedef union {
  struct {
    UINT32 View                                    :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVTTTOP1_CR_DDRCRVTTGENCONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 Target                                  :  7;  // Bits 6:0
    UINT32 Panic                                   :  5;  // Bits 11:7
    UINT32 DisSensorPwrDn                          :  1;  // Bits 12:12
    UINT32 OfstOvrdEn                              :  1;  // Bits 13:13
    UINT32 ViewOfstsel                             :  3;  // Bits 16:14
    UINT32 DdrCRForceODTOn                         :  1;  // Bits 17:17
    UINT32 SalCompLegacyCbit                       :  1;  // Bits 18:18
    UINT32 Spare                                   :  1;  // Bits 19:19
    UINT32 EnVttOdt                                :  1;  // Bits 20:20
    UINT32 PmosOrNmosComperatorTypeSel             :  1;  // Bits 21:21
    UINT32 UsePmosOffsetComp                       :  1;  // Bits 22:22
    UINT32 Enable2VtPmos                           :  1;  // Bits 23:23
    UINT32 Enable2VtNmos                           :  1;  // Bits 24:24
    UINT32 Disable2Vt                              :  1;  // Bits 25:25
    UINT32 OfstOvrd                                :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_STRUCT;

typedef union {
  struct {
    UINT32 DdrVttMainFsmLegacy                     :  1;  // Bits 0:0
    UINT32 VttUsePmosCompCRThreshold               :  7;  // Bits 7:1
    UINT32 LowVoltageParkMode                      :  1;  // Bits 8:8
    UINT32 Spare                                   :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL2_STRUCT;

typedef union {
  struct {
    UINT32 View                                    :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 Target                                  :  7;  // Bits 6:0
    UINT32 Panic                                   :  5;  // Bits 11:7
    UINT32 DisSensorPwrDn                          :  1;  // Bits 12:12
    UINT32 OfstOvrdEn                              :  1;  // Bits 13:13
    UINT32 ViewOfstsel                             :  3;  // Bits 16:14
    UINT32 DdrCRForceODTOn                         :  1;  // Bits 17:17
    UINT32 SalCompLegacyCbit                       :  1;  // Bits 18:18
    UINT32 Spare                                   :  1;  // Bits 19:19
    UINT32 EnVttOdt                                :  1;  // Bits 20:20
    UINT32 PmosOrNmosComperatorTypeSel             :  1;  // Bits 21:21
    UINT32 UsePmosOffsetComp                       :  1;  // Bits 22:22
    UINT32 Enable2VtPmos                           :  1;  // Bits 23:23
    UINT32 Enable2VtNmos                           :  1;  // Bits 24:24
    UINT32 Disable2Vt                              :  1;  // Bits 25:25
    UINT32 OfstOvrd                                :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_STRUCT;

typedef union {
  struct {
    UINT32 DdrVttMainFsmLegacy                     :  1;  // Bits 0:0
    UINT32 VttUsePmosCompCRThreshold               :  7;  // Bits 7:1
    UINT32 LowVoltageParkMode                      :  1;  // Bits 8:8
    UINT32 Spare                                   :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL2_STRUCT;

typedef union {
  struct {
    UINT32 View                                    :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL3_STRUCT;

typedef union {
  struct {
    UINT32 Target                                  :  7;  // Bits 6:0
    UINT32 Panic                                   :  5;  // Bits 11:7
    UINT32 DisSensorPwrDn                          :  1;  // Bits 12:12
    UINT32 OfstOvrdEn                              :  1;  // Bits 13:13
    UINT32 ViewOfstsel                             :  3;  // Bits 16:14
    UINT32 DdrCRForceODTOn                         :  1;  // Bits 17:17
    UINT32 SalCompLegacyCbit                       :  1;  // Bits 18:18
    UINT32 Spare                                   :  1;  // Bits 19:19
    UINT32 EnVttOdt                                :  1;  // Bits 20:20
    UINT32 PmosOrNmosComperatorTypeSel             :  1;  // Bits 21:21
    UINT32 UsePmosOffsetComp                       :  1;  // Bits 22:22
    UINT32 Enable2VtPmos                           :  1;  // Bits 23:23
    UINT32 Enable2VtNmos                           :  1;  // Bits 24:24
    UINT32 Disable2Vt                              :  1;  // Bits 25:25
    UINT32 OfstOvrd                                :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_STRUCT;

typedef union {
  struct {
    UINT32 DdrVttMainFsmLegacy                     :  1;  // Bits 0:0
    UINT32 VttUsePmosCompCRThreshold               :  7;  // Bits 7:1
    UINT32 LowVoltageParkMode                      :  1;  // Bits 8:8
    UINT32 Spare                                   :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVTTBOT1_CR_DDRCRVTTGENCONTROL2_STRUCT;

typedef union {
  struct {
    UINT32 View                                    :  6;  // Bits 5:0
    UINT32 Spare                                   :  26;  // Bits 31:6
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRVTTBOT1_CR_DDRCRVTTGENCONTROL3_STRUCT;

#pragma pack(pop)
#endif
