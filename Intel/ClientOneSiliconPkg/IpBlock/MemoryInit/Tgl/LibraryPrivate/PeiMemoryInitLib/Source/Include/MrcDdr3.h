/** @file
  This file includes all the DDR3 specific characteristic definitions.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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
#ifndef _MrcDdr3_h_
#define _MrcDdr3_h_

#include "MrcTypes.h"
#include "MrcApi.h"
#include "McAddress.h"
#include "MrcCommon.h"
#include "MrcDdrCommon.h"
#include "MrcDdr3Registers.h"
#include "MrcDdr4Registers.h"
#include "MrcIoControl.h"
#include "MrcPowerModes.h"
#include "MrcRefreshConfiguration.h"
#include "MrcMemoryScrub.h"
#include "MrcReset.h"
#include "MrcReadReceiveEnable.h"

#pragma pack (push, 1)
///
/// Mode Register Handler Commands
///
#define MRC_MRH_CMD_MRR             (0)
#define MRC_MRH_CMD_DDR4_MPR_RD     (0)
#define MRC_MRH_CMD_MRW             (1)
#define MRC_MRH_CMD_MRS             (1)
#define MRC_MRH_CMD_LP4_MPC         (2)
#define MRC_MRH_CMD_DDR4_PDA_MRS    (2)
#define MRC_MRH_CMD_DDR4_MPR_WR     (3)

#ifndef tZQinit
#define tZQinit                     (512)   ///< define the tZQinit as define in jedec spec
#endif

#ifndef tWLMRD
#define tWLMRD                      (40)    ///< First DQS/DQS# rising edge after write leveling mode is programmed.
#endif

#ifndef tWLOE
#define tWLOE                       (40)    ///< Write leveling output error the time is 2ns ~ 2 nCK
#endif

#ifndef tZQCS_TIME
#define tZQCS_TIME                  (64)    ///< jedec timing
#endif

#define tVREFDQ_MIN                 (3 * HPET_MIN) ///< DDR4: tVREFDQ is 150 ns

#define MRC_DDR4_SDRAM_TYPE_NUMBER  (0x0C)  ///< use to know the DDR type that data came from Jedec SPD byte 2
#define MRC_UDIMM_TYPE_NUMBER       (0x02)  ///< use to know if the DIMM type is UDIMM define in Jedec SPD byte 3
#define MRC_SOIMM_TYPE_NUMBER       (0x03)  ///< use to know if the DIMM type is SO-DIMM define in Jedec SPD byte 3
#define MRC_SDRAM_DEVICE_WIDTH_8    (0x1)   ///< use to know if the DDRAM is 8 bits width
#define MRC_SDRAM_DEVICE_WIDTH_16   (0x2)   ///< use to know if the DDRAM is 16 bits width
#define MRC_PRIMARY_BUS_WIDTH_64    (0x3)   ///< use to know if the DIMM primary bus width is not 64
#define MRC_CL_MAX_OFFSET           (0xF)   ///< in the spd data include cl from bit 0 to bit 15 each bit represent different support CL
#define MRC_CL_IN_NANO_SEC          (20)    ///< define the nax CL value in nano second

#define INIT_DIMM_RON_34            (34)    ///< Initial DIMM RON Setting

#define tCCD_L_1333_AND_LOWER       (4)
#define tCCD_L_1600_FS              (6250000)  // 6.250 ns
#define tCCD_L_1867_2133_FS         (5355000)  // 5.355 ns
#define tCCD_L_2400_FS              (5000000)  // 5 ns

/**
  This function sends the proper MRS command for specific ranks as indicated by RankMask

  @param[in] MrcData         - include all the MRC data
  @param[in] Controller      - Controller to send command to
  @param[in] Channel         - Channel to send command to
  @param[in] RankMask        - Rank mask for which command will be sent to
  @param[in] MR              - MRS command to be sent
  @param[in] DimmValue       - Dimm Values to be sent

  @retval MrcStatus
**/
extern
MrcStatus
MrcWriteMRSAll (
  IN MrcParameters *const MrcData,
  IN const UINT32         Controller,
  IN const UINT32         Channel,
  IN       UINT8          RankMask,
  IN const UINT8          MR,
  IN const UINT16 *const  DimmValue
  );

/**
  This function sends the proper MRS command for specific ranks as indicated by RankMask

  @param[in] MrcData    - Include all the MRC data
  @param[in] Controller - Controller to send MRS
  @param[in] Channel    - Channel to send command to
  @param[in] RankMask   - Rank mask for which command will be sent to
  @param[in] MR         - MRS command to be sent
  @param[in] Value      - Value to be sent

  @retval MrcStatus
**/
extern
MrcStatus
MrcWriteMRS (
  IN MrcParameters *const MrcData,
  IN       UINT32         Controller,
  IN const UINT8          Channel,
  IN UINT8                RankMask,
  IN const UINT8          MR,
  IN const UINT16         Value
  );

/**
  Issue LPDDR MRW (Mode Register Write) command using MRH (Mode Register Handler).

  @param[in] MrcData      - Include all MRC global data.
  @param[in] Controller   - Controller to send MRW.
  @param[in] Channel      - the channel to work on
  @param[in] Rank         - the rank to work on
  @param[in] Address      - MRW address
  @param[in] Data         - MRW Data
  @param[in] DebugPrint   - when TRUE, will print debugging information

  @retval mrcSuccess    - MRW was sent successfully
  @retval mrcDeviceBusy - timed out waiting for MRH
**/
MrcStatus
MrcIssueMrw (
  IN MrcParameters *const MrcData,
  IN UINT32               Controller,
  IN UINT32               Channel,
  IN UINT32               Rank,
  IN UINT32               Address,
  IN UINT32               Data,
  IN BOOLEAN              DebugPrint
  );

/**
  Issue LPDDR MRR (Mode Register Read) command using MRH (Mode Register Handler).
  Use DQ mapping array to deswizzle the MR data.

  @param[in]  MrcData     - Include all MRC global data.
  @param[in]  Controller  - Controller to issue MRR.
  @param[in]  Channel     - the channel to work on
  @param[in]  Rank        - the rank to work on
  @param[in]  Address     - MRR address
  @param[out] Data        - MRR Data array per SDRAM device

  @retval mrcSuccess    - MRR was executed successfully
  @retval mrcDeviceBusy - timed out waiting for MRH
**/
extern
MrcStatus
MrcIssueMrr (
  IN MrcParameters *const MrcData,
  IN UINT32               Controller,
  IN UINT32               Channel,
  IN UINT32               Rank,
  IN UINT32               Address,
  OUT UINT8               Data[4]
  );

/**
  Use MRS Burst FSM to program all relevant MR registers in one quick operation.
  Can only be used on ULT/ULX (up to 2 ranks, no ECC).
  Runs on all populated controllers, channels, and ranks.

  @param[in]  MrcData - Include all MRC global data.

  @retval mrcSuccess    - MRS FSM was executed successfully
  @retval mrcDeviceBusy - timed out waiting for MRH or MRS FSM
**/
MrcStatus
MrcProgramMrsFsm (
  IN MrcParameters *const MrcData
  );

#pragma pack (pop)
#endif // _MrcDdr3_h_
