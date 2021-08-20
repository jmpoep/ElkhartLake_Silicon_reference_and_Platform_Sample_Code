/** @file
  Include all the DDR4 register definitions.

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
#ifndef _MrcDdr4Registers_h_
#define _MrcDdr4Registers_h_

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
    UINT16 WriteRecoveryAndRTP         : 3;    ///< Bits 9:11
    UINT16                             : 4;    ///< Bits 12:15
  } Bits;
  UINT16 Data;
  UINT8  Data8[2];
} DDR4_MODE_REGISTER_0_STRUCT;

typedef union {
  struct {
    UINT16 DllEnable                   : 1;    ///< Bits 0:0
    UINT16 ODImpedance                 : 2;    ///< Bits 1:2
    UINT16 AdditiveLatency             : 2;    ///< Bits 3:4
    UINT16                             : 2;    ///< Bits 5:6
    UINT16 WriteLeveling               : 1;    ///< Bits 7:7
    UINT16 OdtRttValue                 : 3;    ///< Bits 8:10
    UINT16 Tdqs                        : 1;    ///< Bits 11:11
    UINT16 Qoff                        : 1;    ///< Bits 12:12
    UINT16                             : 3;    ///< Bits 13:15
  } Bits;
  UINT16 Data;
  UINT8  Data8[2];
} DDR4_MODE_REGISTER_1_STRUCT;

typedef union {
  struct {
    UINT16                             : 3;    ///< Bits 0:2
    UINT16 CasWriteLatency             : 3;    ///< Bits 3:5
    UINT16 LowPowerArraySelfRefresh    : 2;    ///< Bits 7:6
    UINT16                             : 1;    ///< Bits 8:8
    UINT16 DynamicOdt                  : 3;    ///< Bits 9:11
    UINT16 WriteCrc                    : 1;    ///< Bits 12:12
    UINT16                             : 3;    ///< Bits 13:15
  } Bits;
  UINT16 Data;
  UINT8  Data8[2];
} DDR4_MODE_REGISTER_2_STRUCT;

typedef union {
  struct {
    UINT16 MprPageSelection            : 2;    ///< Bits 0:1
    UINT16 MprOperation                : 1;    ///< Bits 2:2
    UINT16 GeardownMode                : 1;    ///< Bits 3:3
    UINT16 PerDramAddressability       : 1;    ///< Bits 4:4
    UINT16 TempSensorReadout           : 1;    ///< Bits 5:5
    UINT16 RefreshRateMode             : 3;    ///< Bits 6:8
    UINT16 WriteCmdLatency             : 2;    ///< Bits 9:10
    UINT16 MprReadFormat               : 2;    ///< Bits 11:12
    UINT16                             : 3;    ///< Bits 13:15
  } Bits;
  UINT16 Data;
  UINT8  Data8[2];
} DDR4_MODE_REGISTER_3_STRUCT;

typedef union {
  struct {
    UINT16                             : 1;    ///< Bits 0:0
    UINT16 MaxPowerDownMode            : 1;    ///< Bits 1:1
    UINT16 TempRefreshRange            : 1;    ///< Bits 2:2
    UINT16 TempRefreshMode             : 1;    ///< Bits 3:3
    UINT16 InternalVrefMonitor         : 1;    ///< Bits 4:4
    UINT16                             : 1;    ///< Bits 5:5
    UINT16 CstoCmd_AddrLatencyMode     : 3;    ///< Bits 6:8
    UINT16 SelfRefreshAbort            : 1;    ///< Bits 9:9
    UINT16 ReadPreambleTrainingMode    : 1;    ///< Bits 10:10
    UINT16 ReadPreamble                : 1;    ///< Bits 11:11
    UINT16 WritePreamble               : 1;    ///< Bits 12:12
    UINT16                             : 3;    ///< Bits 13:15
  } Bits;
  UINT16 Data;
  UINT8  Data8[2];
} DDR4_MODE_REGISTER_4_STRUCT;

typedef union {
  struct {
    UINT16 C_AParityLatencyMode        : 3;    ///< Bits 2:0
    UINT16 CrcErrorClear               : 1;    ///< Bits 3:3
    UINT16 C_AParityErrorStatus        : 1;    ///< Bits 4:4
    UINT16 OdtInputBufferforPowerDown  : 1;    ///< Bits 5:5
    UINT16 RttPark                     : 3;    ///< Bits 6:8
    UINT16 C_AParityPersistentError    : 1;    ///< Bits 9:9
    UINT16 DataMask                    : 1;    ///< Bits 10:10
    UINT16 WriteDbi                    : 1;    ///< Bits 11:11
    UINT16 ReadDbi                     : 1;    ///< Bits 12:12
    UINT16                             : 3;    ///< Bits 13:15
  } Bits;
  UINT16 Data;
  UINT8  Data8[2];
} DDR4_MODE_REGISTER_5_STRUCT;

typedef union {
  struct {
    UINT16 VrefDqTrainingValue         : 6;    ///< Bits 5:0
    UINT16 VrefDqTrainingRange         : 1;    ///< Bits 6:6
    UINT16 VrefDqTrainingEnable        : 1;    ///< Bits 7:7
    UINT16                             : 2;    ///< Bits 8:9
    UINT16 Tccd_l                      : 3;    ///< Bits 10:12
    UINT16                             : 3;    ///< Bits 13:15
  } Bits;
  UINT16 Data;
  UINT8  Data8[2];
} DDR4_MODE_REGISTER_6_STRUCT;

///
/// MR0 register
///
#define DDR4_MODE_REGISTER_0_BL_OFF     (0)
#define DDR4_MODE_REGISTER_0_BL_WID     (2)
#define DDR4_MODE_REGISTER_0_BL_MAX     (3)

#define DDR4_MODE_REGISTER_0_CL_A2_OFF  (2)
#define DDR4_MODE_REGISTER_0_CL_A2_WID  (1)
#define DDR4_MODE_REGISTER_0_CL_A2_MAX  (1)

#define DDR4_MODE_REGISTER_0_RBT_OFF    (3)
#define DDR4_MODE_REGISTER_0_RBT_WID    (1)
#define DDR4_MODE_REGISTER_0_RBT_MAX    (1)

#define DDR4_MODE_REGISTER_0_CL_OFF     (4)
#define DDR4_MODE_REGISTER_0_CL_WID     (3)
#define DDR4_MODE_REGISTER_0_CL_MAX     (7)

#define DDR4_MODE_REGISTER_0_TM_OFF     (7)
#define DDR4_MODE_REGISTER_0_TM_WID     (1)
#define DDR4_MODE_REGISTER_0_TM_MAX     (1)

#define DDR4_MODE_REGISTER_0_DLL_OFF    (8)
#define DDR4_MODE_REGISTER_0_DLL_WID    (1)
#define DDR4_MODE_REGISTER_0_DLL_MAX    (1)

#define DDR4_MODE_REGISTER_0_WR_RTP_OFF (9)
#define DDR4_MODE_REGISTER_0_WR_RTP_WID (3)
#define DDR4_MODE_REGISTER_0_WR_RTP_MAX (7)

///
/// MR1 register
///
#define DDR4_MODE_REGISTER_1_DLL_OFF        (0)
#define DDR4_MODE_REGISTER_1_DLL_WID        (1)
#define DDR4_MODE_REGISTER_1_DLL_MAX        (1)

#define DDR4_MODE_REGISTER_1_D_I_C_OFF      (1)
#define DDR4_MODE_REGISTER_1_D_I_C_WID      (2)
#define DDR4_MODE_REGISTER_1_D_I_C_MAX      (1)

#define DDR4_MODE_REGISTER_1_AL_OFF         (3)
#define DDR4_MODE_REGISTER_1_AL_WID         (2)
#define DDR4_MODE_REGISTER_1_AL_MAX         (3)

#define DDR4_MODE_REGISTER_1_LEVEL_OFF      (7)
#define DDR4_MODE_REGISTER_1_LEVEL_WID      (1)
#define DDR4_MODE_REGISTER_1_LEVEL_MAX      (1)

#define DDR4_MODE_REGISTER_1_Rtt_Nom_OFF    (8)
#define DDR4_MODE_REGISTER_1_Rtt_Nom_WID    (3)
#define DDR4_MODE_REGISTER_1_Rtt_Nom_MAX    (7)

#define DDR4_MODE_REGISTER_1_TDQS_OFF       (11)
#define DDR4_MODE_REGISTER_1_TDQS_WID       (1)
#define DDR4_MODE_REGISTER_1_TDQS_MAX       (1)

#define DDR4_MODE_REGISTER_1_Qoff_OFF       (12)
#define DDR4_MODE_REGISTER_1_Qoff_WID       (1)
#define DDR4_MODE_REGISTER_1_Qoff_MAX       (1)

///
/// MR2 register
///
#define DDR4_MODE_REGISTER_2_CWL_OFF    (3)
#define DDR4_MODE_REGISTER_2_CWL_WID    (3)
#define DDR4_MODE_REGISTER_2_CWL_MAX    (7)

#define DDR4_MODE_REGISTER_2_LPASR_OFF  (6)
#define DDR4_MODE_REGISTER_2_LPASR_WID  (2)
#define DDR4_MODE_REGISTER_2_LPASR_MAX  (3)

#define DDR4_MODE_REGISTER_2_Rtt_WR_OFF (9)
#define DDR4_MODE_REGISTER_2_Rtt_WR_WID (3)
#define DDR4_MODE_REGISTER_2_Rtt_WR_MAX (4)

#define DDR4_MODE_REGISTER_2_W_CRC_OFF  (12)
#define DDR4_MODE_REGISTER_2_W_CRC_WID  (1)
#define DDR4_MODE_REGISTER_2_W_CRC_MAX  (1)

///
/// MR3 register
///
#define DDR4_MODE_REGISTER_3_MPR_PAGE_OFF (0)
#define DDR4_MODE_REGISTER_3_MPR_PAGE_WID (2)
#define DDR4_MODE_REGISTER_3_MPR_PAGE_MAX (3)

#define DDR4_MODE_REGISTER_3_MPR_OFF      (2)
#define DDR4_MODE_REGISTER_3_MPR_WID      (1)
#define DDR4_MODE_REGISTER_3_MPR_MAX      (1)

#define DDR4_MODE_REGISTER_3_GM_OFF       (3)
#define DDR4_MODE_REGISTER_3_GM_WID       (1)
#define DDR4_MODE_REGISTER_3_GM_MAX       (1)

#define DDR4_MODE_REGISTER_3_PDA_OFF      (4)
#define DDR4_MODE_REGISTER_3_PDA_WID      (1)
#define DDR4_MODE_REGISTER_3_PDA_MAX      (1)

#define DDR4_MODE_REGISTER_3_TSR_OFF      (5)
#define DDR4_MODE_REGISTER_3_TSR_WID      (1)
#define DDR4_MODE_REGISTER_3_TSR_MAX      (1)

#define DDR4_MODE_REGISTER_3_FGRM_OFF     (6)
#define DDR4_MODE_REGISTER_3_FGRM_WID     (3)
#define DDR4_MODE_REGISTER_3_FGRM_MAX     (7)

#define DDR4_MODE_REGISTER_3_WCMDL_OFF    (9)
#define DDR4_MODE_REGISTER_3_WCMDL_WID    (2)
#define DDR4_MODE_REGISTER_3_WCMDL_MAX    (3)

#define DDR4_MODE_REGISTER_3_MPR_READ_OFF (11)
#define DDR4_MODE_REGISTER_3_MPR_READ_WID (2)
#define DDR4_MODE_REGISTER_3_MPR_READ_MAX (3)

///
/// MR4 register
///
#define DDR4_MODE_REGISTER_4_MAX_PD_OFF   (1)
#define DDR4_MODE_REGISTER_4_MAX_PD_WID   (1)
#define DDR4_MODE_REGISTER_4_MAX_PD_MAX   (1)

#define DDR4_MODE_REGISTER_4_TCRR_OFF     (2)
#define DDR4_MODE_REGISTER_4_TCRR_WID     (1)
#define DDR4_MODE_REGISTER_4_TCRR_MAX     (1)

#define DDR4_MODE_REGISTER_4_TCRM_OFF     (3)
#define DDR4_MODE_REGISTER_4_TCRM_WID     (1)
#define DDR4_MODE_REGISTER_4_TCRM_MAX     (1)

#define DDR4_MODE_REGISTER_4_IVM_OFF      (4)
#define DDR4_MODE_REGISTER_4_IVM_WID      (1)
#define DDR4_MODE_REGISTER_4_IVM_MAX      (1)

#define DDR4_MODE_REGISTER_4_C_CA_LAT_OFF (6)
#define DDR4_MODE_REGISTER_4_C_CA_LAT_WID (3)
#define DDR4_MODE_REGISTER_4_C_CA_LAT_MAX (7)

#define DDR4_MODE_REGISTER_4_SRA_OFF      (9)
#define DDR4_MODE_REGISTER_4_SRA_WID      (1)
#define DDR4_MODE_REGISTER_4_SRA_MAX      (1)

#define DDR4_MODE_REGISTER_4_R_PRE_TM_OFF (10)
#define DDR4_MODE_REGISTER_4_R_PRE_TM_WID (1)
#define DDR4_MODE_REGISTER_4_R_PRE_TM_MAX (1)

#define DDR4_MODE_REGISTER_4_R_PRE_OFF    (11)
#define DDR4_MODE_REGISTER_4_R_PRE_WID    (1)
#define DDR4_MODE_REGISTER_4_R_PRE_MAX    (1)

#define DDR4_MODE_REGISTER_4_W_PRE_OFF    (12)
#define DDR4_MODE_REGISTER_4_W_PRE_WID    (1)
#define DDR4_MODE_REGISTER_4_W_PRE_MAX    (1)

///
/// MR5 register
///
#define DDR4_MODE_REGISTER_5_CA_PLM_OFF   (0)
#define DDR4_MODE_REGISTER_5_CA_PLM_WID   (3)
#define DDR4_MODE_REGISTER_5_CA_PLM_MAX   (7)

#define DDR4_MODE_REGISTER_5_CRC_EC_OFF   (3)
#define DDR4_MODE_REGISTER_5_CRC_EC_WID   (1)
#define DDR4_MODE_REGISTER_5_CRC_EC_MAX   (1)

#define DDR4_MODE_REGISTER_5_CA_PES_OFF   (4)
#define DDR4_MODE_REGISTER_5_CA_PES_WID   (1)
#define DDR4_MODE_REGISTER_5_CA_PES_MAX   (1)

#define DDR4_MODE_REGISTER_5_ODT_IB_OFF   (5)
#define DDR4_MODE_REGISTER_5_ODT_IB_WID   (1)
#define DDR4_MODE_REGISTER_5_ODT_IB_MAX   (1)

#define DDR4_MODE_REGISTER_5_Rtt_PARK_OFF (6)
#define DDR4_MODE_REGISTER_5_Rtt_PARK_WID (3)
#define DDR4_MODE_REGISTER_5_Rtt_PARK_MAX (7)

#define DDR4_MODE_REGISTER_5_CA_PPE_OFF   (9)
#define DDR4_MODE_REGISTER_5_CA_PPE_WID   (1)
#define DDR4_MODE_REGISTER_5_CA_PPE_MAX   (1)

#define DDR4_MODE_REGISTER_5_DATAMASK_OFF (10)
#define DDR4_MODE_REGISTER_5_DATAMASK_WID (1)
#define DDR4_MODE_REGISTER_5_DATAMASK_MAX (1)

#define DDR4_MODE_REGISTER_5_WRITEDBI_OFF (11)
#define DDR4_MODE_REGISTER_5_WRITEDBI_WID (1)
#define DDR4_MODE_REGISTER_5_WRITEDBI_MAX (1)

#define DDR4_MODE_REGISTER_5_READ_DBI_OFF (12)
#define DDR4_MODE_REGISTER_5_READ_DBI_WID (1)
#define DDR4_MODE_REGISTER_5_READ_DBI_MAX (1)

///
/// MR6 register
///
#define DDR4_MODE_REGISTER_6_VrefDQ_V_OFF (0)
#define DDR4_MODE_REGISTER_6_VrefDQ_V_WID (6)
#define DDR4_MODE_REGISTER_6_VrefDQ_V_MAX (0x3F)

#define DDR4_MODE_REGISTER_6_VrefDQ_R_OFF (6)
#define DDR4_MODE_REGISTER_6_VrefDQ_R_WID (1)
#define DDR4_MODE_REGISTER_6_VrefDQ_R_MAX (1)

#define DDR4_MODE_REGISTER_6_VrefDQ_E_OFF (7)
#define DDR4_MODE_REGISTER_6_VrefDQ_E_WID (1)
#define DDR4_MODE_REGISTER_6_VrefDQ_E_MAX (1)

#define DDR4_MODE_REGISTER_6_tCCD_L_OFF   (10)
#define DDR4_MODE_REGISTER_6_tCCD_L_WID   (2)
#define DDR4_MODE_REGISTER_6_tCCD_L_MAX   (4)

#pragma pack (pop)
#endif
