/** @file
  Implements functions that are used to interact with various
  DDR technologies.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2018 Intel Corporation.

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
#include "MrcInterface.h"
#include "McAddress.h"
#include "MrcCommon.h"
#include "MrcMaintenance.h"

/**
  This function executes the MRH (Mode Register Handler).

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Channel    - the channel to work on
  @param[in] SubChannel - the sub-channel to work on
  @param[in] Rank       - the rank to work on
  @param[in] Address    - MRW address
  @param[in] Data       - MRW Data
  @param[in] MrhCmd     - MRH command, see MRC_MRH_CMD_xxx defines

  @retval mrcSuccess    - MRW was sent successfully
  @retval mrcDeviceBusy - timed out waiting for MRH
**/
MrcStatus
MrcRunMrh (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                Channel,
  IN  UINT32                SubChannel,
  IN  UINT32                Rank,
  IN  UINT32                Address,
  IN  UINT32                Data,
  IN  UINT8                 MrhCmd
  )
{
  const MRC_FUNCTION  *MrcCall;
  MrcDebug            *Debug;
  MrcOutput           *Outputs;
  INT64               Ddr4OneDpc;
  UINT32              OffsetMrCommand;
  BOOLEAN             Lpddr4;
  BOOLEAN             Busy;
  BOOLEAN             MRR;
  CH0_CR_DDR_MR_COMMAND_STRUCT MrCommand;
  UINT64              Timeout;

  MrcCall = MrcData->Inputs.Call.Func;
  Timeout = MrcCall->MrcGetCpuTime (MrcData) + 10000;   // 10 seconds timeout
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Lpddr4  = Outputs->DdrType == MRC_DDR_TYPE_LPDDR4;

  OffsetMrCommand = CH0_CR_DDR_MR_COMMAND_REG +
    ((CH1_CR_DDR_MR_COMMAND_REG - CH0_CR_DDR_MR_COMMAND_REG) * Channel);

  MRR = (MrhCmd == MRC_MRH_CMD_MRR);

  // Remap target rank if ddr4_1dpc is enabled on this channel
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccDdr4OneDpc, ReadFromCache, &Ddr4OneDpc);
  if (Ddr4OneDpc == 1) { // ddr4_1dpc enabled on DIMM0
    if (Rank == 1) {
      Rank = 3;
    }
  } else if (Ddr4OneDpc == 2) { // ddr4_1dpc enabled on DIMM1
    if (Rank == 2) {
      Rank = 0;
    }
  }

  // Make sure MRH is not busy
  do {
    MrCommand.Data = MrcReadCR (MrcData, OffsetMrCommand);
    Busy           = (MrCommand.Bits.Busy == 1);
  } while (Busy && (MrcCall->MrcGetCpuTime (MrcData) < Timeout));

  if (Busy) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Timed out waiting for previous MRH command to finish!\n");
    return mrcDeviceBusy;
  }

  //
  // Send the command
  //
  /**
    Common
      DDR4 MRS              : Address [2:0] holds MR#, Address [7:3] holds MA[12:8]
      DDR4 MPR reads/writes : Address [1:0] holds MPR page (programmed into MR3 MA[1:0])
                              Address [3:2] holds MPR# (sent as BA[1:0] on read/write command)
      LPDDR4 MRR/MRW        : Address [5:0] holds MR#, Address [7] is used MSB of rank inside the sub channel (to allow 3 and 4 ranks)
      LPDDR4 MPC            : Address [6:0] holds OP[6:0] of the MPC command, Address [7] is used MSB of rank inside the sub channel (to allow 3 and 4 ranks)
  **/
  MrCommand.Bits.Address  = Address;
  if (Lpddr4) {
    MrCommand.Bits.Address |= ((Rank & 0x2) << 6);
  }
  /**
    Common
      DDR4 MRS       : Data[7:0] holds MA[7:0] for MRS
      DDR4 MPR write : Data[7:0] holds the pattern
      LPDDR4 MRR/MRW : Data[7:0] holds MR data for MRW commands
  **/
  // Put non-zero data for MRR.
  MrCommand.Bits.Data     = (MRR) ? 1 :Data;
  /**
    Common
      DDR4:    00 - MPR read 01 - MRS 10 - Per DRAM addressability mode (PDA) MRS            11 - MPR write
      LPDDR4:  00 - MRR      01 - MRW 10 - MPC (not supporting DQ Calibraion and FIFO RD/WR) 11 - Illegal
      WIO2:    00 - MRR      01 - MRW 10 - Illegal                                           11 - Illegal
  **/
  MrCommand.Bits.Command      = MrhCmd;
  if (Lpddr4) {
    MrCommand.Bits.Rank       = (SubChannel << 1) | (Rank & 0x1);
  } else {
    MrCommand.Bits.Rank       = Rank;
  }
  MrCommand.Bits.Busy         = 1;
  MrCommand.Bits.Assume_idle  = (Outputs->DdrType == MRC_DDR_TYPE_DDR4) ? !Outputs->JedecInitDone : 0;

  if (MrCommand.Bits.Assume_idle == 1) {
    // Wait 64 DCLKs after Busy is low, before sending another MRH command
    MrcWait (MrcData, (Outputs->Dclkps * 64 * MRC_TIMER_1NS) / 1000);
  }
  MrcWriteCR (MrcData, OffsetMrCommand, MrCommand.Data);

  // Wait till MRH is done sending the command
  Timeout = MrcCall->MrcGetCpuTime (MrcData) + 10000;   // 10 seconds timeout
  do {
    MrCommand.Data = MrcReadCR (MrcData, OffsetMrCommand);
    Busy           = (MrCommand.Bits.Busy == 1);
  } while (Busy && (MrcCall->MrcGetCpuTime (MrcData) < Timeout));

  if (Busy) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Timed out sending MRH command!\n");
    return mrcDeviceBusy;
  } else if (MrCommand.Bits.Assume_idle == 1) {
    // Wait 64 DCLKs after Busy is low, before sending another MRH command
    MrcWait (MrcData, (Outputs->Dclkps * 64 * MRC_TIMER_1NS) / 1000);
  }

  return mrcSuccess;
}
