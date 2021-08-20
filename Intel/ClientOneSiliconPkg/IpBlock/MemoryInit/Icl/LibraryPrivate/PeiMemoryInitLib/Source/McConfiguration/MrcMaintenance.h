/** @file
  This module contains functions to configure and use Memory Controller
  maintenance features.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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
#ifndef _MrcMaintenance_h_
#define _MrcMaintenance_h_

#include "MrcDdrCommon.h"
#include "MrcDdr4Registers.h"
#include "MrcRefreshConfiguration.h"

///
/// Mode Register Handler Commands
///
#define MRC_MRH_CMD_MRR             (0)
#define MRC_MRH_CMD_MRW             (1)
#define MRC_MRH_CMD_MRS             (1)
#define MRC_MRH_CMD_LP4_MPC         (2)
#define MRC_MRH_CMD_LP3_INIT_MRW    (3)

#define INIT_DIMM_RON_34            (34)            ///< Initial DIMM RON Setting

#define tCCD_L_1333_AND_LOWER       (4)
#define tCCD_L_1600_FS              (6250000)  // 6.250 ns
#define tCCD_L_1867_2133_FS         (5355000)  // 5.355 ns
#define tCCD_L_2400_FS              (5000000)  // 5 ns

/**
  This function will disable the DQS Oscillator maintenance feature in the Memory Controller.

  @params[in] MrcData - Pointer to MRC global data.
**/
VOID
MrcDisableDqsOscillatorMc (
  IN  MrcParameters * const MrcData
  );

/**
  This function executes the requested ZQ command for DDR4 / LPDDR4 DRAMS.
  This function will wait the appropriate wait time as specified in the JEDEC spec.

  @param[in]  MrcData   - Pointer to MRC global data.
  @param[in]  ChBitMask - Bit mask of channels to run.

  @retval MrcStatus - mrcSuccess if successful, else an error status.
**/
MrcStatus
MrcSendZq (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                ChBitMask
  );

/**
  Issue ZQ calibration command on all ranks.
  When done, wait appropriate delay depending on the ZQ type.

  @param[in] MrcData         - include all the MRC data
  @param[in] chBitMask       - Channel bit mask to be sent to.
  @param[in] ZqType          - Type of ZQ Calibration: see MrcZqType enum

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status
**/
MrcStatus
MrcIssueZQ (
  IN MrcParameters *const MrcData,
  IN const UINT8          chBitMask,
  IN const MrcZqType      ZqType
  );

/**
  Issue DDR4 MRS command (PDA Mode)

  @param[in] MrcData         - Include all the MRC general data.
  @param[in] Channel         - Channel to send command to
  @param[in] Rank            - Rank to send command to
  @param[in] Address         - MRS data
  @param[in] MR              - MR # to change
  @param[in] DeviceMask      - Devices/Bytes to send MRS data to

  @retval mrcSuccess    - PDA command was sent successfully
  @retval mrcDeviceBusy - Timed out waiting for MRH
**/
MrcStatus
MrcDdr4PdaCmd (
  IN MrcParameters *const MrcData,
  IN UINT32               Channel,
  IN UINT32               Rank,
  IN UINT16               Address,
  IN UINT8                MR,
  IN UINT16               DeviceMask
  );

/**
  This function provides the initial configuration of the Memory Controller's
  maintenance services.  Some items are disabled during MRC training, and will need
  to be configured at the end of MRC.

  @params[in] MrcData - Pointer to MRC global data.
**/
VOID
MrcMaintenanceConfig (
  IN  MrcParameters * const MrcData
  );

/**
  Issue LPDDR MRR (Mode Register Read) command using MRH (Mode Register Handler).
  Use DQ mapping array to deswizzle the MR data.

  @param[in]  MrcData     - Include all MRC global data.
  @param[in]  Channel     - the channel to work on
  @param[in]  SubChannel  - the sub-channel to work on
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
  IN UINT32               Channel,
  IN UINT32               SubChannel,
  IN UINT32               Rank,
  IN UINT32               Address,
  OUT UINT8               Data[4]
);

/**
  Issue LPDDR MRW (Mode Register Write) command using MRH (Mode Register Handler).

  @param[in] MrcData      - Include all MRC global data.
  @param[in] Channel      - the channel to work on
  @param[in] SubChannel   - the sub-channel to work on
  @param[in] Rank         - the rank to work on
  @param[in] Address      - MRW address
  @param[in] Data         - MRW Data
  @param[in] InitMrw      - when TRUE, command is stretched (used before CA training is done)
  @param[in] ChipSelect2N - when TRUE, use 2N stretch mode for CS (used before CA training is done)
  @param[in] DebugPrint   - when TRUE, will print debugging information

  @retval mrcSuccess    - MRW was sent successfully
  @retval mrcDeviceBusy - timed out waiting for MRH
**/
MrcStatus
MrcIssueMrw (
  IN MrcParameters *const MrcData,
  IN UINT32               Channel,
  IN UINT32               SubChannel,
  IN UINT32               Rank,
  IN UINT32               Address,
  IN UINT32               Data,
  IN BOOLEAN              InitMrw,
  IN BOOLEAN              ChipSelect2N,
  IN BOOLEAN              DebugPrint
);

/**
This function sends the proper MRS command for specific ranks as indicated by RankMask

@param[in] MrcData         - include all the MRC data
@param[in] Channel         - Channel to send command to
@param[in] RankMask        - Rank mask for which command will be sent to
@param[in] MR              - MRS command to be sent
@param[in] DimmValue       - Dimm Values to be sent

@retval MrcStatus
**/
extern
MrcStatus
MrcWriteMRSAll(
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN       UINT8          RankMask,
  IN const UINT8          MR,
  IN const UINT16 *const  DimmValue
);

/**
This function sends the proper MRS command for specific ranks as indicated by RankMask

@param[in] MrcData         - Include all the MRC data
@param[in] Channel         - Channel to send command to
@param[in] RankMask        - Rank mask for which command will be sent to
@param[in] MR              - MRS command to be sent
@param[in] Value           - Value to be sent

@retval MrcStatus
**/
extern
MrcStatus
MrcWriteMRS(
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN UINT8                RankMask,
  IN const UINT8          MR,
  IN const UINT16         Value
);

/**
Use MRS Burst FSM to program all relevant MR registers in one quick operation.
Can only be used on ULT/ULX (up to 2 ranks, no ECC)

@param[in]  MrcData     - Include all MRC global data.
@param[in]  ChannelMask - bit mask of channels to run.

@retval mrcSuccess    - MRS FSM was executed successfully
@retval mrcDeviceBusy - timed out waiting for MRH or MRS FSM
**/
MrcStatus
MrcProgramMrsFsm(
  IN MrcParameters *const MrcData,
  IN UINT32               ChannelMask
);


#endif // _MrcMaintenance_h_
