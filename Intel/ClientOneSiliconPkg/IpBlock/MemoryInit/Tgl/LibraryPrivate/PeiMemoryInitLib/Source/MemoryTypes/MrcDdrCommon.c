/** @file
  Implements functions that are common various LP/DDR technologies.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2019 Intel Corporation.

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

///
/// Initialization Timing Parameters
///
#define MRC_LP_tINIT0_US   20000   ///< Max voltage-ramp time
#define MRC_LP_tINIT1_US   200     ///< Min RESET_n low time after Voltage Ramp
#define MRC_LP_tINIT3_US   2000    ///< Min CKE low time after RESET_n high
#define MRC_LP_tINIT4_TCK  5       ///< Min stable clock before first CKE high
#define MRC_LP_tINIT5_US   2       ///< Min idle time before first MR[W,R]

#define LP_RZQ_NUM_VALUES (7)     ///< Number of ODT encodings in LPDDR MR's

///
/// Constants
///
// This table is the list of possible terminations the DRAM can achieve using ZQ Resistor.
static const UINT16 LpRzqValues[LP_RZQ_NUM_VALUES] = {0xFFFF, 240, 120, 80, 60, 48, 40};

/**
  This function converts from Ohms to LPDDR4/5 MR ODT encoding.

  @param[in]  OdtValue  - ODT Value in Ohms.

  @retval INT8 - Encoding if valid ODT value.  Else, -1.
**/
INT8
LpddrOdtEncode (
  IN  UINT16  OdtValue
  )
{
  INT8      EncodeVal;

  switch (OdtValue) {
    case 0xFFFF:
      EncodeVal = LpOdtOff;
      break;

    case 240:
      EncodeVal = LpOdt240;
      break;

    case 120:
      EncodeVal = LpOdt120;
      break;

    case 80:
      EncodeVal = LpOdt80;
      break;

    case 60:
      EncodeVal = LpOdt60;
      break;

    case 48:
      EncodeVal = LpOdt48;
      break;

    case 40:
      EncodeVal = LpOdt40;
      break;

    default:
      EncodeVal = -1;
      break;
  }

  return EncodeVal;
}

/**
  This function searches the list of valid ODT encodings for LPDDR4/5 to find the closest matching
  ODT.  The SOC ODT and the SOC_ODT programming to the LPDDR4/5 MR must match or unexpected behavior
  may occur.  It will return this value to the caller.

  @param[in]  MrcData - Pointer to the global MRC data
  @param[in]  SocOdt  - The ODT requested by the system

  @retval - Closest matching ODT value.
**/
UINT16
MrcCheckSocOdtLpddr (
  IN  MrcParameters *const  MrcData,
  IN  UINT16                SocOdt
  )
{
  UINT32  Index;
  UINT16  Distance1;
  UINT16  Distance2;
  UINT16  SocOdtRet;

  SocOdtRet = 0;

  // Determine the SOC ODT Encoding that matches closest to the real RxOdt value.
  // This is programmed in MR 22.
  for (Index = 0; Index < LP_RZQ_NUM_VALUES; Index++) {
    if (SocOdt == LpRzqValues[Index]) {
      SocOdtRet = SocOdt;
      break;
    }
    // No exact match, find the closest match.
    // Array is ordered from Largest to smallest.
    // If we're Index == 0, only check if the requested value is greater
    if (Index == 0) {
      if (SocOdt > LpRzqValues[Index]) {
        SocOdtRet = LpRzqValues[Index];
        break;
      }
    } else if (Index == (LP_RZQ_NUM_VALUES - 1)) {
      // End of the list, return the last element.
      SocOdtRet = LpRzqValues[Index];
      break;
    } else {
      // See if it falls between this index and the previous.
      if ((SocOdt < LpRzqValues[Index - 1]) && (SocOdt > LpRzqValues[Index])) {
        // Determine which termination is closest to the SOC and select that for MR22
        Distance1 = LpRzqValues[Index - 1] - SocOdt;
        Distance2 = SocOdt - LpRzqValues[Index];
        // Select the one with the smallest distance
        SocOdtRet = (Distance1 < Distance2) ? LpRzqValues[Index - 1] : LpRzqValues[Index];
        break;
      }
    }
  }

  return SocOdtRet;
}

/**
  This function performs the reset sequence required by JEDEC spec for LPDDR4/5.

  @param[in]  MrcData - Pointer to MRC global data.

  @retval MrcStatus - mrcSuccess if successful, else an error status.
**/
MrcStatus
MrcJedecResetLpddr (
  IN  MrcParameters *const  MrcData
  )
{
  MrcInput      *Inputs;
  MrcOutput     *Outputs;
  MRC_FUNCTION  *MrcCall;
  MrcStatus     Status;
  INT64         GetSetVal;
  INT32         Channel;
  UINT32        PciEBar;
  UINT32        tInit1;
  UINT32        tInit3;
  UINT32        tInit5;
  UINT32        Controller;
  UINT32        ValidRankMask;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  MrcCall = Inputs->Call.Func;
  PciEBar = Inputs->PciEBaseAddress;
  Status  = mrcSuccess;
  tInit1  = MRC_LP_tINIT1_US * MRC_TIMER_1US;
  tInit3  = MRC_LP_tINIT3_US * MRC_TIMER_1US;
  tInit5  = MRC_LP_tINIT5_US * MRC_TIMER_1US;

  // Assert DRAM RESET# signal after Voltage Ramp (Step 2)
  MrcCall->MrcDramReset (PciEBar, 0);

  // Force CKE low
  GetSetVal = 0;
  MrcGetSetMcCh (MrcData, MAX_CONTROLLER, MAX_CHANNEL, GsmMccCkeOn, WriteNoCache, &GetSetVal);

  // Ensure tINIT1 (200us) before de-asserting DRAM reset. This will cover tINIT2 (10ns) as well.
  MrcWait (MrcData, tInit1);

  // De-Assert DRAM RESET# signal.
  MrcCall->MrcDramReset (PciEBar, 1);

  // Wait tINIT3 (2ms) - covers Min CKE low after RESET# high and tINIT4 (5tCK) - Min Stable CLK before CKE high
  MrcWait (MrcData, tInit3);

  // Set the valid CKE's
  // Walk the array backwards as 3/1 are sub channels of 0/2 for MC.
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = (MAX_CHANNEL - 1); Channel >= 0; Channel--) {
      if (MrcChannelExist (MrcData, Controller, Channel)) {
        ValidRankMask = Outputs->Controller[Controller].Channel[Channel].ValidRankBitMask;
        if (Channel % 2) {
          //Channel 3/1 are bits 3:2 for Rank Mask.
          GetSetVal = ValidRankMask << 2;
        } else {
          GetSetVal |= ValidRankMask;
          MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccCkeOn, WriteNoCache, &GetSetVal);
          // Clear the variable for the next set of channels.
          GetSetVal = 0;
        }
      }
    }
  }

  // Wait tINIT5: Min idle time before first MR[R,W] command.
  MrcWait (MrcData, tInit5);

  return Status;
}

/**
  This function executes the MRH (Mode Register Handler).

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Controller - Controller to run MRH.
  @param[in] Channel    - the channel to work on
  @param[in] Rank       - the rank to work on
  @param[in] Address    - MRW address
  @param[in] Data       - MRW Data
  @param[in] DebugPrint - when TRUE, will print debugging information

  @retval mrcSuccess    - MRW was sent successfully
  @retval mrcDeviceBusy - timed out waiting for MRH
**/
MrcStatus
MrcRunMrh (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                Controller,
  IN  UINT32                Channel,
  IN  UINT32                Rank,
  IN  UINT32                Address,
  IN  UINT32                Data,
  IN  UINT8                 MrhCmd,
  IN  BOOLEAN               DebugPrint
  )
{
  const MRC_FUNCTION  *MrcCall;
  MrcDebug            *Debug;
  MrcOutput           *Outputs;
  MrcDdrType          DdrType;
  INT64               Ddr4OneDpc;
  UINT32              OffsetMrCommand;
  UINT32              IpChannel;
  BOOLEAN             Busy;
  BOOLEAN             MRR;
  BOOLEAN             Lpddr;
  MC0_CH0_CR_DDR_MR_COMMAND_STRUCT MrCommand;
  UINT64  Timeout;

  MrcCall = MrcData->Inputs.Call.Func;
  Timeout = MrcCall->MrcGetCpuTime () + 10000;   // 10 seconds timeout
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  DdrType = Outputs->DdrType;
  Lpddr   = Outputs->Lpddr;
  IpChannel = LP_IP_CH (Lpddr, Channel);

  OffsetMrCommand = OFFSET_CALC_MC_CH (MC0_CH0_CR_DDR_MR_COMMAND_REG, MC1_CH0_CR_DDR_MR_COMMAND_REG, Controller, MC0_CH1_CR_DDR_MR_COMMAND_REG, IpChannel);

  MRR = (MrhCmd == MRC_MRH_CMD_MRR);

  if (DdrType == MRC_DDR_TYPE_DDR4) {
    // Remap target rank if ddr4_1dpc is enabled on this channel
    MrcGetSetMcCh (MrcData, Controller, IpChannel, GsmMccDdr4OneDpc, ReadNoCache, &Ddr4OneDpc);
    if (Ddr4OneDpc == 1) { // ddr4_1dpc enabled on DIMM0
      if (Rank == 1) {
        Rank = 3;
      }
    } else if (Ddr4OneDpc == 2) { // ddr4_1dpc enabled on DIMM1
      if (Rank == 2) {
        Rank = 0;
      }
    }
  }

  //
  // Make sure MRH is not busy
  //
  do {
    MrCommand.Data = MrcReadCR (MrcData, OffsetMrCommand);
    Busy           = (MrCommand.Bits.Busy == 1);
  } while (Busy && (MrcCall->MrcGetCpuTime () < Timeout));

  if (Busy) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Timed out waiting for previous MRH command to finish!\n");
    return mrcDeviceBusy;
  }

  //
  // Send the command
  //
  /**
      DDR4 MRS              : Address [2:0] holds MR#, Address [8:3] holds MA[13:8]
      DDR4 MPR reads/writes : Address [1:0] holds MPR page (programmed into MR3 MA[1:0])
                              Address [3:2] holds MPR# (sent as BA[1:0] on read/write command)
      LPDDR4 MRR/MRW        : Address [5:0] holds MR#, Address [8] is used MSB of rank inside the sub channel (to allow 2 and 3 ranks)
      LPDDR4 MPC            : Address [6:0] holds OP[6:0] of the MPC command, Address [8] is used MSB of rank inside the sub channel (to allow 2 and 3 ranks)
                              Address [3:2] holds MPR# (sent as BA[1:0] on read/write command)
      LPDDR5 MRR/MRW        : Address [5:0] holds MR#, Address [8] is used MSB of rank inside the sub channel (to allow 2 and 3 ranks)
      LPDDR5 MPC            : Address [6:0] holds OP[7:0] of the MPC command, Address [8] is used MSB of rank inside the sub channel (to allow 2 and 3 ranks)
  **/
  MrCommand.Bits.Address  = Address;
  if (Lpddr) {
    MrCommand.Bits.Address |= ((Rank & 2) << 6);
    MrCommand.Bits.Address |= ((Channel % 2) << 8);
  }
// @todo check how to do this for ERM, currently we use ranks 2 and 3 for the second subch
//  if ((Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) && (Rank > 1)) {
//    MrCommand.Bits.Address |= 1 << 8;
//  }
  /**
      DDR4 MRS          : Data[7:0] holds MA[7:0] for MRS
      DDR4 MPR write    : Data[7:0] holds the pattern
      LPDDR4/5 MRR/MRW  : Data[7:0] holds MR data for MRW commands
  **/
  // Put non-zero data for MRR.
  MrCommand.Bits.Data     = (MRR) ? 1 : Data;
  /**
      DDR4:    00 - MPR read 01 - MRS 10 - Per DRAM addressability mode (PDA) MRS            11 - MPR write
      LPDDR4:  00 - MRR      01 - MRW 10 - MPC (not supporting DQ Calibraion and FIFO RD/WR) 11 - Illegal
  **/
  MrCommand.Bits.Command      = MrhCmd;
  MrCommand.Bits.Rank         = Rank;
  MrCommand.Bits.Busy         = 1;
  MrCommand.Bits.Assume_idle  = (DdrType == MRC_DDR_TYPE_DDR4) ? !Outputs->JedecInitDone : 0;

  if (MrCommand.Bits.Assume_idle == 1) {
    // Wait 64 DCLKs after Busy is low, before sending another MRH command
    MrcWait (MrcData, (Outputs->Dclkps * 64 * MRC_TIMER_1NS) / 1000);
  }
  MrcWriteCR (MrcData, OffsetMrCommand, MrCommand.Data);

  //
  // Wait till MRH is done sending the command
  //
  Timeout = MrcCall->MrcGetCpuTime () + 10000;   // 10 seconds timeout
  do {
    MrCommand.Data = MrcReadCR (MrcData, OffsetMrCommand);
    Busy           = (MrCommand.Bits.Busy == 1);
  } while (Busy && (MrcCall->MrcGetCpuTime () < Timeout));

  if (Busy) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Timed out sending MRH command!\n");
    return mrcDeviceBusy;
  } else if (MrCommand.Bits.Assume_idle == 1) {
    // Wait 64 DCLKs after Busy is low, before sending another MRH command
    MrcWait (MrcData, (Outputs->Dclkps * 64 * MRC_TIMER_1NS) / 1000);
  }

  return mrcSuccess;
}
