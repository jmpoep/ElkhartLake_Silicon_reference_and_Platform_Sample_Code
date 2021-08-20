/** @file
  Include all the DDR3 register definitions.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2017 Intel Corporation.

  The source code contained or described herein and all documents related to the
  source code ("Material") are owned by Intel Corporation or its suppliers or
  licensors. Title to the Material remains with Intel Corporation or its suppliers
  and licensors. The Material may contain trade secrets and proprietary and
  confidential information of Intel Corporation and its suppliers and licensors,
  and is protected by worldwide copyright and trade secret laws and treaty
  provisions. No part of the Material may be used, copied, reproduced, modified,
  published, uploaded, posted, transmitted, distributed, or disclosed in any way
  without Intel's prior express written permission.

  No license under any patent, copyright, trade secret or other intellectual
  property right is granted to or conferred upon you by disclosure or delivery
  of the Materials, either expressly, by implication, inducement, estoppel or
  otherwise. Any license under such intellectual property rights must be
  express and approved by Intel in writing.

  Unless otherwise agreed by Intel in writing, you may not remove or alter
  this notice or any other notice embedded in Materials by Intel or
  Intel's suppliers or licensors in any way.

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#ifndef _MrcDdr3Registers_h_
#define _MrcDdr3Registers_h_


#include "MrcTypes.h"

#pragma pack(push, 1)

typedef union {
  struct {
    UINT16 BurstLength                 : 2;    ///< Bits 0:1
    UINT16 CasLatencyLow               : 1;    ///< Bits 2:2
    UINT16 ReadBurstType               : 1;    ///< Bits 3:3
    UINT16 CasLatencyHigh              : 3;    ///< Bits 4:6
    UINT16 TestMode                    : 1;    ///< Bits 7:7
    UINT16 DllReset                    : 1;    ///< Bits 8:8
    UINT16 WriteRecovery               : 3;    ///< Bits 9:11
    UINT16 PrechargePdDll              : 1;    ///< Bits 12:12
    UINT16                             : 3;    ///< Bits 13:15
  } Bits;
  UINT16 Data;
  UINT8  Data8[2];
} DDR3_MODE_REGISTER_0_STRUCT;

typedef union {
  struct {
    UINT16 DllEnable                   : 1;    ///< Bits 0:0
    UINT16 ODImpedanceLow              : 1;    ///< Bits 1:1
    UINT16 OdtRttValueLow              : 1;    ///< Bits 2:2
    UINT16 AdditiveLatency             : 2;    ///< Bits 3:4
    UINT16 ODImpedanceHigh             : 1;    ///< Bits 5:5
    UINT16 OdtRttValueMid              : 1;    ///< Bits 6:6
    UINT16 WriteLeveling               : 1;    ///< Bits 7:7
    UINT16                             : 1;    ///< Bits 8:8
    UINT16 OdtRttValueHigh             : 1;    ///< Bits 9:9
    UINT16                             : 1;    ///< Bits 10:10
    UINT16 Tdqs                        : 1;    ///< Bits 11:11
    UINT16 Qoff                        : 1;    ///< Bits 12:12
    UINT16                             : 3;    ///< Bits 13:15
  } Bits;
  UINT16 Data;
  UINT8  Data8[2];
} DDR3_MODE_REGISTER_1_STRUCT;

typedef union {
  struct {
    UINT16 PartialArraySR              : 3;    ///< Bits 0:2
    UINT16 CasWriteLatency             : 3;    ///< Bits 3:5
    UINT16 AutoSelfRefresh             : 1;    ///< Bits 6:6
    UINT16 SelfRefreshTemp             : 1;    ///< Bits 7:7
    UINT16                             : 1;    ///< Bits 8:8
    UINT16 DynamicOdt                  : 2;    ///< Bits 9:10
    UINT16                             : 5;    ///< Bits 11:15
  } Bits;
  UINT16 Data;
  UINT8  Data8[2];
} DDR3_MODE_REGISTER_2_STRUCT;

typedef union {
  struct {
    UINT16 MprLocation                 : 2;    ///< Bits 0:1
    UINT16 MprOperation                : 1;    ///< Bits 2:2
    UINT16                             : 13;   ///< Bits 3:15
  } Bits;
  UINT16 Data;
  UINT8  Data8[2];
} DDR3_MODE_REGISTER_3_STRUCT;

///
/// MR0 register
///
#define DDR3_MODE_REGISTER_0_BL_OFF     (0)
#define DDR3_MODE_REGISTER_0_BL_WID     (2)
#define DDR3_MODE_REGISTER_0_BL_MAX     (3)

#define DDR3_MODE_REGISTER_0_CL_A2_OFF  (2)
#define DDR3_MODE_REGISTER_0_CL_A2_WID  (1)
#define DDR3_MODE_REGISTER_0_CL_A2_MAX  (1)

#define DDR3_MODE_REGISTER_0_RBT_OFF    (3)
#define DDR3_MODE_REGISTER_0_RBT_WID    (1)
#define DDR3_MODE_REGISTER_0_RBT_MAX    (1)

#define DDR3_MODE_REGISTER_0_CL_OFF     (4)
#define DDR3_MODE_REGISTER_0_CL_WID     (3)
#define DDR3_MODE_REGISTER_0_CL_MAX     (7)

#define DDR3_MODE_REGISTER_0_TM_OFF     (7)
#define DDR3_MODE_REGISTER_0_TM_WID     (1)
#define DDR3_MODE_REGISTER_0_TM_MAX     (1)

#define DDR3_MODE_REGISTER_0_DLL_OFF    (8)
#define DDR3_MODE_REGISTER_0_DLL_WID    (1)
#define DDR3_MODE_REGISTER_0_DLL_MAX    (1)

#define DDR3_MODE_REGISTER_0_WR_OFF     (9)
#define DDR3_MODE_REGISTER_0_WR_WID     (3)
#define DDR3_MODE_REGISTER_0_WR_MAX     (7)

#define DDR3_MODE_REGISTER_0_PPD_OFF    (12)
#define DDR3_MODE_REGISTER_0_PPD_WID    (1)
#define DDR3_MODE_REGISTER_0_PPD_MAX    (1)

///
/// MR1 register
///
#define DDR3_MODE_REGISTER_1_DLL_OFF        (0)
#define DDR3_MODE_REGISTER_1_DLL_WID        (1)
#define DDR3_MODE_REGISTER_1_DLL_MAX        (1)

#define DDR3_MODE_REGISTER_1_D_I_C_A1_OFF   (1)
#define DDR3_MODE_REGISTER_1_D_I_C_A1_WID   (1)

#define DDR3_MODE_REGISTER_1_Rtt_Nom_A2_OFF (2)
#define DDR3_MODE_REGISTER_1_Rtt_Nom_A2_WID (1)

#define DDR3_MODE_REGISTER_1_AL_OFF         (3)
#define DDR3_MODE_REGISTER_1_AL_WID         (2)
#define DDR3_MODE_REGISTER_1_AL_MAX         (3)

#define DDR3_MODE_REGISTER_1_D_I_C_A5_OFF   (5)
#define DDR3_MODE_REGISTER_1_D_I_C_A5_WID   (1)
#define DDR3_MODE_REGISTER_1_D_I_C_A5_A1_WID (2)
#define DDR3_MODE_REGISTER_1_D_I_C_A5_A1_MAX (1)

#define DDR3_MODE_REGISTER_1_Rtt_Nom_A6_OFF (6)
#define DDR3_MODE_REGISTER_1_Rtt_Nom_A6_WID (1)
#define DDR3_MODE_REGISTER_1_Rtt_Nom_A9_A6_A2_WID (3)
#define DDR3_MODE_REGISTER_1_Rtt_Nom_A9_A6_A2_MAX (5)

#define DDR3_MODE_REGISTER_1_LEVEL_OFF      (7)
#define DDR3_MODE_REGISTER_1_LEVEL_WID      (1)
#define DDR3_MODE_REGISTER_1_LEVEL_MAX      (1)

#define DDR3_MODE_REGISTER_1_Rtt_Nom_A9_OFF (9)
#define DDR3_MODE_REGISTER_1_Rtt_Nom_A9_WID (1)

#define DDR3_MODE_REGISTER_1_TDQS_OFF       (11)
#define DDR3_MODE_REGISTER_1_TDQS_WID       (1)
#define DDR3_MODE_REGISTER_1_TDQS_MAX       (1)

#define DDR3_MODE_REGISTER_1_Qoff_OFF       (12)
#define DDR3_MODE_REGISTER_1_Qoff_WID       (1)
#define DDR3_MODE_REGISTER_1_Qoff_MAX       (1)

///
/// MR2 register
///
#define DDR3_MODE_REGISTER_2_PASR_OFF   (0)
#define DDR3_MODE_REGISTER_2_PASR_WID   (3)
#define DDR3_MODE_REGISTER_2_PASR_MAX   (7)

#define DDR3_MODE_REGISTER_2_CWL_OFF    (3)
#define DDR3_MODE_REGISTER_2_CWL_WID    (3)
#define DDR3_MODE_REGISTER_2_CWL_MAX    (7)

#define DDR3_MODE_REGISTER_2_ASR_OFF    (6)
#define DDR3_MODE_REGISTER_2_ASR_WID    (1)
#define DDR3_MODE_REGISTER_2_ASR_MAX    (1)

#define DDR3_MODE_REGISTER_2_STR_OFF    (7)
#define DDR3_MODE_REGISTER_2_STR_WID    (1)
#define DDR3_MODE_REGISTER_2_STR_MAX    (1)

#define DDR3_MODE_REGISTER_2_Rtt_WR_OFF (9)
#define DDR3_MODE_REGISTER_2_Rtt_WR_WID (2)
#define DDR3_MODE_REGISTER_2_Rtt_WR_MAX (2)

///
/// MR3 register
///
#define DDR3_MODE_REGISTER_3_MPR_LOC_OFF  (0)
#define DDR3_MODE_REGISTER_3_MPR_LOC_WID  (2)
#define DDR3_MODE_REGISTER_3_MPR_LOC_MAX  (3)

#define DDR3_MODE_REGISTER_3_MPR_OFF      (2)
#define DDR3_MODE_REGISTER_3_MPR_WID      (1)
#define DDR3_MODE_REGISTER_3_MPR_MAX      (1)

#pragma pack (pop)
#endif
