/** @file
  This file include all the MRC Gears related algorithms.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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
#include "MrcTypes.h"
#include "McAddress.h"
#include "MrcCommon.h"
#include "MrcGears.h"
#include "MrcWriteDqDqs.h"
#include "MrcDdrIoApi.h"
#include "MrcDdrIoApiInt.h"

#define DCC_PRINT  (1)

/**
  This function finalizes the DCC FSM control registers for normal operation.

  @param[in]  MrcData - Pointer to global MRC data.
**/
VOID
MrcDccFsmFinalize (
  IN  MrcParameters * const MrcData
  )
{
  UINT32 Channel;
  UINT32 Data;
  UINT32 Offset;
  UINT32 FllPs;
  UINT32 DataNumSamples;
  UINT32 CccNumSamples;
  DATA0CH0_CR_DCCLANESTATUS3_STRUCT DataDccLaneStatus3;
  DATA0CH0_CR_DCCFSMCONTROL_STRUCT  DataDccFsmCtrl;
  CCC_CR_DCCFSMCONTROL_STRUCT       CccDccFsmCtrl;

  // FLL Target ratio is 3133 for 133 RefClk and 3100 for 100 RefClk
  FllPs = 1000000 / ((MrcData->Inputs.RefClk == MRC_REF_CLOCK_133) ? 3133 : 3100);

  // RANGE (RoundUpTo2^NandReturnN ((1000nS / tFLL / 2)*(tQCLK / .3125nS)) - 12), 0, 4);
  // Scale to ps on the constants and optimize down to a single divide
  // Lowest QclkPs is 938.  We stay under 1 billion.  No overflow on UINT32.
  DataNumSamples = (1000000 * MrcData->Outputs.Qclkps) / (FllPs * 2 * 313);
  DataNumSamples = MrcLog2 (DataNumSamples);
  DataNumSamples = MAX (DataNumSamples, 12);
  DataNumSamples -= 12;

  // RANGE  (RoundUpTo2^NandReturnN ((2000nS / tFLL / 2)*(tQCLK / .3125nS) )-12), 0, 4);
  // Scale to ps on the constants and optimize down to a single divide
  // Lowest QclkPs is 938.  We stay under 1 billion.  No overflow on UINT32.
  CccNumSamples = (2000000 * MrcData->Outputs.Qclkps) / (FllPs * 2 * 313);
  CccNumSamples = MrcLog2 (CccNumSamples);
  CccNumSamples = MAX (CccNumSamples, 12);
  CccNumSamples -= 12;

  // Finalize DCC configuration
  MrcWriteCrMulticast (MrcData, CCC_CR_DCCFSMSTATUS_REG, 0);
  MrcWriteCrMulticast (MrcData, DATA_CR_DCCFSMSTATUS_REG, 0);

  for (Channel = 0; Channel < MRC_NUM_CCC_INSTANCES; Channel++) {
    Offset = OFFSET_CALC_CH (CH0CCC_CR_DCCFSMCONTROL_REG, CH1CCC_CR_DCCFSMCONTROL_REG, Channel);
    CccDccFsmCtrl.Data = MrcReadCR (MrcData, Offset);
    CccDccFsmCtrl.Bits.UpdateTcoComp = 1;
    CccDccFsmCtrl.Bits.DccSamples = CccNumSamples;
    MrcWriteCR (MrcData, Offset, CccDccFsmCtrl.Data);

    // DDRDATA partition only has 2 groups of 8 instances.
    if (Channel < 2) {
      for (Data = 0; Data < 8; Data++) {
       Offset = OFFSET_CALC_MC_CH (DATA0CH0_CR_DCCLANESTATUS3_REG, DATA0CH1_CR_DCCLANESTATUS3_REG, Channel, DATA1CH0_CR_DCCLANESTATUS3_REG, Data);
       DataDccLaneStatus3.Data = MrcReadCR (MrcData, Offset);
       DataDccLaneStatus3.Bits.ExtremeCount = 0;
       DataDccLaneStatus3.Bits.ExtremeOffset = 0;
       MrcWriteCR (MrcData, Offset, DataDccLaneStatus3.Data);

       Offset = OFFSET_CALC_MC_CH (DATA0CH0_CR_DCCFSMCONTROL_REG, DATA0CH1_CR_DCCFSMCONTROL_REG, Channel, DATA1CH0_CR_DCCFSMCONTROL_REG, Data);
       DataDccFsmCtrl.Data = MrcReadCR (MrcData, Offset);
       DataDccFsmCtrl.Bits.DccSamples = DataNumSamples;
       MrcWriteCR (MrcData, Offset, DataDccFsmCtrl.Data);
      }
    }
  }
}

#if 0
/**
  This function will setup the fields in MCMISCS_DCCMAINFSMCONTROL0.  Currently adjusting fields:
  ActiveClks, ActiveBytes, dcocompen

  @params[in] MrcData   - Pointer to MRC global data.
  @params[in] IsClock   - Whether this is setup for Clk DCC vs (DQ DCC or DQS DCC).
  @params[in] DcoCompEn - Whether DcoCompEn is set (only is set if both Clock and DcoCompEn are TRUE).

  @retval Nothing
**/
void
MrcDccMainFsmControl0 (
  IN  MrcParameters * const MrcData,
  IN  BOOLEAN         IsClock,
  IN  BOOLEAN         DcoCompEn
  )
{
  MrcOutput     *Outputs;
  MrcInput      *Inputs;
  MrcIntOutput  *MrcIntData;
  UINT32        Channel;
  UINT32        ActiveBytesMask;
  UINT32        PrintMode;
  UINT8         ActiveBytesShift;
  INT64         ActiveClks;
  INT64         ActiveBytes;
  INT64         GetSetValue;

  Outputs     = &MrcData->Outputs;
  Inputs      = &MrcData->Inputs;
  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  PrintMode   = (DCC_PRINT) ? PrintValue : 0;

  if (MrcIntData->LastDccRun != IsClock) {
    // Drain is needed when switching between CLK and DATA (or vice versa)
    GetSetValue = 1;
    MrcGetSetDdrIoGroupController0 (MrcData, GsmIocDccDrain, WriteCached | PrintMode, &GetSetValue);
    MrcIntData->LastDccRun = IsClock;
  }

  // Initialize variables
  GetSetValue = (IsClock && DcoCompEn) ? 1 : 0;
  ActiveBytes = (IsClock) ? 0 : MCMISCS_DCCMAINFSMCONTROL0_ActiveBytes_MAX;
  ActiveClks  = (IsClock) ? MCMISCS_DCCMAINFSMCONTROL0_ActiveClks_MAX : 0;

  if (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) {
    ActiveBytesMask = 0;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (Outputs, Channel)) {
        if (!MrcSubChannelExist (MrcData, Channel, 1)) {
          ActiveBytesMask = 0xF0F0;
        }
        //Want to skip Channels that exists
        continue;
      }
      ActiveClks  &= ~((INT64) (1 << Channel));
      ActiveBytes &= ~((INT64) (0xFF << (Channel * 8)));
    }
    ActiveBytes &= ~((INT64) ActiveBytesMask);
  } else {
    if (Inputs->DqPinsInterleaved) {
      ActiveBytesShift = 2;
      ActiveBytesMask  = 0x5555;
    } else {
      ActiveBytesShift = 8;
      ActiveBytesMask  = 0xFF;
      //@todo Any change here for ECC?
    }
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (Outputs, Channel)) {
        // Want to skip Channels that exists
        continue;
      }
      ActiveClks  &= ~((INT64) (1 << Channel));
      ActiveBytes &= ~((INT64) (ActiveBytesMask << (Channel * ActiveBytesShift)));
    }
  }
  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocDccActiveClks,  WriteToCache | PrintMode, &ActiveClks);
  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocDccActiveBytes, WriteToCache | PrintMode, &ActiveBytes);
  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocDccDcoCompEn,   WriteToCache | PrintMode, &GetSetValue);

  MrcFlushRegisterCachedData (MrcData);
}

/**
  This function will find the first populated channel and read various DCC[CLK/DATA]CONTROL registers for
  that channel (Byte 0 if DATA).

  @params[in]  MrcData       - Pointer to MRC global data.
  @params[in]  Clock         - Whether this is to read from CLK registers or DATA registers
  @params[out] DccControl0   - Pointer to DCC[CLK/DATA]CONTROL0.
  @params[out] DccControl1   - Pointer to DCC[CLK/DATA]CONTROL1.
  @params[out] DccControl3   - Pointer to DCC[CLK/DATA]CONTROL3.
  @params[out] DccControl4   - Pointer to DCC[CLK/DATA]CONTROL4.

  @retval Nothing.
**/
void
MrcDccControlRegsRead (
  IN  MrcParameters * const MrcData,
  IN  BOOLEAN               Clock,
  OUT UINT32                *DccControl0,
  OUT UINT32                *DccControl1,
  OUT UINT32                *DccControl3,
  OUT UINT32                *DccControl4
  )
{
  MrcOutput  *Outputs;
  UINT32     Channel;
  UINT32     Offset;

  Outputs = &MrcData->Outputs;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      if (DccControl0 != NULL) {
        if (Clock) {
          Offset = OFFSET_CALC_CH (DDRCLKCH0_CR_DCCCLKCONTROL0_REG, DDRCLKCH1_CR_DCCCLKCONTROL0_REG, Channel);
        } else {
          Offset = OFFSET_CALC_CH (DATA0CH0_CR_DCCDATACONTROL0_REG, DATA0CH1_CR_DCCDATACONTROL0_REG, Channel);
        }
        *DccControl0 = MrcReadCR (MrcData, Offset);
      }

      if (DccControl1 != NULL) {
        if (Clock) {
          Offset = OFFSET_CALC_CH (DDRCLKCH0_CR_DCCCLKCONTROL1_REG, DDRCLKCH1_CR_DCCCLKCONTROL1_REG, Channel);
        } else {
          Offset = OFFSET_CALC_CH (DATA0CH0_CR_DCCDATACONTROL1_REG, DATA0CH1_CR_DCCDATACONTROL1_REG, Channel);
        }
        *DccControl1 = MrcReadCR (MrcData, Offset);
      }

      if (DccControl3 != NULL) {
        if (Clock) {
          Offset = OFFSET_CALC_CH (DDRCLKCH0_CR_DCCCLKCONTROL3_REG, DDRCLKCH1_CR_DCCCLKCONTROL3_REG, Channel);
        } else {
          Offset = OFFSET_CALC_CH (DATA0CH0_CR_DCCDATACONTROL3_REG, DATA0CH1_CR_DCCDATACONTROL3_REG, Channel);
        }
        *DccControl3 = MrcReadCR (MrcData, Offset);
      }

      if (DccControl4 != NULL) {
        if (Clock) {
          Offset = OFFSET_CALC_CH (DDRCLKCH0_CR_DCCCLKCONTROL4_REG, DDRCLKCH1_CR_DCCCLKCONTROL4_REG, Channel);
        } else {
          Offset = OFFSET_CALC_CH (DATA0CH0_CR_DCCDATACONTROL4_REG, DATA0CH1_CR_DCCDATACONTROL4_REG, Channel);
        }
        *DccControl4 = MrcReadCR (MrcData, Offset);
      }
      break;
    }
  }
}

/**
  This function will setup MCMISCS_DCCCONTROL0 register to kick off Correction FSM and poll on trainingdone field for test completion.

  @params[in] MrcData   - Pointer to MRC global data.

  @retval mrcSuccess if FSM finished test within Timeout, otherwise mrcFail.
**/
MrcStatus
MrcDccRunTest (
  IN  MrcParameters * const MrcData
  )
{
  const MRC_FUNCTION  *MrcCall;
  MrcInput            *Inputs;
  UINT32              FsmStatusOffset;
  INT64               GetSetVal;
  UINT64              Timeout;
  BOOLEAN             TrainingDone;
  BOOLEAN             DccFsmIdle;
  MCMISCS_DCCMAINFSMSTATUS0_STRUCT  MiscDccMainFsmStatus0;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;

  FsmStatusOffset = Inputs->IclA0 ? MCMISCS_DCCMAINFSMSTATUS0_REG_A0 : MCMISCS_DCCMAINFSMSTATUS0_REG;

  Timeout = MrcCall->MrcGetCpuTime () + 10000; // 10 seconds timeout
  // Make sure DCC FSM is idle
  do {
    MiscDccMainFsmStatus0.Data = MrcReadCR (MrcData, FsmStatusOffset);
    DccFsmIdle = (MiscDccMainFsmStatus0.Bits.CurrState == 0);
  } while (!DccFsmIdle && (MrcCall->MrcGetCpuTime () < Timeout));

  if (DccFsmIdle) {
    GetSetVal = 0;
    MrcGetSetDdrIoGroupController0 (MrcData, GsmIocDccTrainingDone, WriteToCache, &GetSetVal);
    MrcGetSetDdrIoGroupController0 (MrcData, GsmIocDccDrain, WriteCached, &GetSetVal);

    // Start the FSM and wait for it to finish
    GetSetVal = 1;
    MrcGetSetDdrIoGroupController0 (MrcData, GsmIocDccTrainingMode, WriteToCache, &GetSetVal);
    MrcFlushRegisterCachedData (MrcData);
    Timeout = MrcCall->MrcGetCpuTime () + 10000; // 10 seconds timeout

    do {
      MrcGetSetDdrIoGroupController0 (MrcData, GsmIocDccTrainingDone, ReadCached, &GetSetVal);
      TrainingDone = (GetSetVal == 1);
    } while (!TrainingDone && (MrcCall->MrcGetCpuTime () < Timeout));
  } else {
    TrainingDone = FALSE;
  }

  return (TrainingDone) ? mrcSuccess : mrcFail;
}
#endif // ifdef 0

#if 0
/**
  This function will setup do the initial sweeps of the various DCC training steps to populate the Look Up Tables (LUT)

  @params[in] MrcData   - Pointer to MRC global data.

  @retval mrcSuccess if each DCC training steps was successful, otherwise mrcFail.
**/
MrcStatus
MrcDccInitialization (
  IN  MrcParameters * const MrcData
  )
{
  MrcOutput *Outputs;
  MrcInput  *Inputs;
  INT64     GetSetVal;
  INT64     CmdTriStateSave[MAX_CONTROLLER][MAX_CHANNEL];
  UINT32    PrintMode;
  UINT32    Channel;
  UINT32    Controller;
  UINT32    IpChannel;
  MrcStatus Status;
  MrcStatus CurStatus;
  BOOLEAN   Lpddr;

  Outputs = &MrcData->Outputs;
  Inputs = &MrcData->Inputs;
  Lpddr = Outputs->Lpddr;

  Status = mrcSuccess;
  PrintMode = (DCC_PRINT) ? PrintValue : 0;

  // Switch to High frequency for DCC initialization
  if (Lpddr) {
    if ((Outputs->Frequency != Outputs->HighFrequency) && (Inputs->LpFreqSwitch == TRUE)) {
      MrcFrequencySwitch (MrcData, Outputs->HighFrequency, TRUE);
    }
  }

  GetSetVal = 0;
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Controller, Channel) || (IS_MC_SUB_CH(Lpddr, Channel))) {
        continue;
      }
      IpChannel = LP_IP_CH (Lpddr, IpChannel);
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccCmdTriStateDis, ReadFromCache | PrintMode, &CmdTriStateSave[Controller][Channel]);
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccCmdTriStateDis, WriteCached   | PrintMode, &GetSetVal);
    }
  }


  // CLK DCC - done for both Gear1 and Gear2
  CurStatus = MrcDccClkInitSweep (MrcData);
  if (Status == mrcSuccess) {
    Status = CurStatus;
  }

  if (Outputs->Gear2) {
    // DQS PI DCC
    CurStatus = MrcDccDqsInitSweep (MrcData);
    if (Status == mrcSuccess) {
      Status = CurStatus;
    }

    // DQ PI (per byte) DCC
    CurStatus = MrcDccDqByteInitSweep (MrcData);
    if (Status == mrcSuccess) {
      Status = CurStatus;
    }

    // DQ Per Bit DCC
    CurStatus = MrcDccDqBitInitSweep (MrcData);
    if (Status == mrcSuccess) {
      Status = CurStatus;
    }
  }

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Controller, Channel) || (IS_MC_SUB_CH (Lpddr, Channel))) {
        continue;
      }
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccCmdTriStateDis, WriteCached | PrintMode, &CmdTriStateSave[Controller][Channel]);
    }
  }

  // Go back to 1067; this is before ECT yet
  if (Lpddr) {
    if ((Outputs->Frequency != f1067) && (Inputs->LpFreqSwitch == TRUE)) {
      MrcFrequencySwitch (MrcData, f1067, TRUE);
    }
  }
  return Status;
}
#endif

#if 0
/**
  This function will do the final setup of the various DCC settings prior to end of SAGV.

  @params[in] MrcData   - Pointer to MRC global data.

  @retval mrcSuccess if each DCC final steps was successful, otherwise mrcFail.
**/
MrcStatus
MrcDccReplica (
  IN  MrcParameters * const MrcData
  )
{
  MrcOutput    *Outputs;
  MrcStatus    Status;
  MrcStatus    CurStatus;
  INT64        GetSetVal;

  Outputs = &MrcData->Outputs;

  Status = mrcSuccess;

  GetSetVal = 0;
  MrcGetSetDdrIoGroupController0 (MrcData, GsmMccEnableDclk, WriteNoCache | PrintValue, &GetSetVal);

  // CLK DCC - for both Gear1 and Gear2
  CurStatus = MrcDccClkFinalization (MrcData);
  if (Status == mrcSuccess) {
    Status = CurStatus;
  }

  // DQS PI DCC - for both Gear1 and Gear2
  CurStatus = MrcDccDqsFinalization (MrcData);
  if (Status == mrcSuccess) {
    Status = CurStatus;
  }

  if (Outputs->Gear2) {
    CurStatus = MrcDccReInit (MrcData);
    if (Status == mrcSuccess) {
      Status = CurStatus;
    }
  }

  GetSetVal = 1;
  MrcGetSetDdrIoGroupController0 (MrcData, GsmMccEnableDclk, WriteNoCache | PrintValue, &GetSetVal);
  MrcResetSequence (MrcData);

  return Status;
}

/**
  This function will do the final setup of the various DCC settings after all SAGV.

  @params[in] MrcData   - Pointer to MRC global data.

  @retval mrcSuccess.
**/
MrcStatus
MrcDccFinalization (
  IN  MrcParameters * const MrcData
  )
{
  MrcOutput   *Outputs;
  MrcDebug    *Debug;
  UINT32      Channel;
  UINT32      Offset;
  DDRDATA0CH0_CR_DCCDATACONTROL3_STRUCT   DccDataControl3;
  DDRCLKCH0_CR_DCCCLKCONTROL3_STRUCT      DccClkControl3;
  DDRPHY_COMP_CR_DDRCRDMVREFCOMP_STRUCT   DdrCrdmVrefComp;
  DDRPHY_COMP_CR_DCCDCOSTATUS1_STRUCT     DccDcoStatus1;
  MCMISCS_DCCMAINFSMCONTROL1_STRUCT       MiscDccMainFsmControl1;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  if (Outputs->Gear2Ever) {
    MrcDccMainFsmControl0 (MrcData, FALSE, FALSE);
    //@todo H/S sku code

    MrcDccControlRegsRead (MrcData, FALSE, NULL, NULL, &DccDataControl3.Data, NULL);
    DccDataControl3.Bits.ActiveDccRank0 = 0x200; // Just the replica
    MrcWriteCrMulticast (MrcData, DDRDATA_CR_DCCDATACONTROL3_REG, DccDataControl3.Data);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DCCDATACONTROL3 = 0x%08X\n", DccDataControl3.Data);

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (Outputs, Channel)) {
        // Find first populated channel
        break;
      }
    }
    Offset = OFFSET_CALC_CH (DDRCLKCH0_CR_DCCCLKCONTROL3_REG, DDRCLKCH1_CR_DCCCLKCONTROL3_REG, Channel);
    DccClkControl3.Data = MrcReadCR (MrcData, Offset);
    DccClkControl3.Bits.ActiveDccRank0 = 0x4;    // Just the replica
    MrcWriteCrMulticast (MrcData, DDRCLKCH0CH1_CR_DCCCLKCONTROL3_REG, DccClkControl3.Data);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DCCCLKCONTROL3 = 0x%08X\n", DccClkControl3.Data);

    DdrCrdmVrefComp.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRDMVREFCOMP_REG);
    DdrCrdmVrefComp.Bits.NxtVTCompValidForDcc = 1;
    MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRDMVREFCOMP_REG, DdrCrdmVrefComp.Data);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDRPHY_COMP_CR_DDRCRDMVREFCOMP = 0x%08X\n", DdrCrdmVrefComp.Data);

    DccDcoStatus1.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DCCDCOSTATUS1_REG);
    DccDcoStatus1.Bits.VTCompOffsetDone = 1;
    MrcWriteCR (MrcData, DDRPHY_COMP_CR_DCCDCOSTATUS1_REG, DccDcoStatus1.Data);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDRPHY_COMP_CR_DCCDCOSTATUS1 = 0x%08X\n", DccDcoStatus1.Data);

    MiscDccMainFsmControl1.Data = MrcReadCR (MrcData, MCMISCS_DCCMAINFSMCONTROL1_REG);
    // MiscDccMainFsmControl1.Bits.PriodicCntEn = 1;
    MrcWriteCR (MrcData, MCMISCS_DCCMAINFSMCONTROL1_REG, MiscDccMainFsmControl1.Data);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DCCMAINFSMCONTROL1 = 0x%08X\n", MiscDccMainFsmControl1.Data);
  }
  return mrcSuccess;
}

/**
  This function will re-initialize DCC...

  @params[in] MrcData   - Pointer to MRC global data.

  @retval mrcSuccess.
**/
MrcStatus
MrcDccReInit (
  IN  MrcParameters * const MrcData
  )
{
  MrcOutput         *Outputs;
  MrcDebug          *Debug;
  MrcDebugMsgLevel  DebugLevel;
  INT64             GetSetVal;
  UINT32            Channel;
  UINT32            Offset;
  UINT32            PrintMode;
  DDRDATA0CH0_CR_DCCDATACONTROL0_STRUCT   DccDataControl0;
  DDRCLKCH0_CR_DCCCLKCONTROL0_STRUCT      DccClkControl0;
  MCMISCS_DCCMAINFSMCONTROL1_STRUCT       MiscDccMainFsmControl1;

  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  PrintMode   = (DCC_PRINT) ? PrintValue : 0;
  DebugLevel  = (DCC_PRINT) ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nDCC ReInit Start\n");

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      // Find first populated channel
      break;
    }
  }
  GetSetVal = 1;
  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocDccTrainingDone, WriteCached | PrintMode, &GetSetVal);

  GetSetVal = 0;
  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocDccDcoCompEn, WriteCached | PrintMode, &GetSetVal);

  MrcDccControlRegsRead (MrcData, FALSE, &DccDataControl0.Data, NULL, NULL, NULL);
  DccDataControl0.Bits.ReplicaOffsetUse = 1;
  DccDataControl0.Bits.VTCompOffsetUse = 1;
  DccDataControl0.Bits.ActiveRanks = 1;  // Only Rank0 takes care of periodic for now
  MrcWriteCrMulticast (MrcData, DDRDATA_CR_DCCDATACONTROL0_REG, DccDataControl0.Data);
  MRC_DEBUG_MSG (Debug, DebugLevel, "DDRDATA_CR_DCCDATACONTROL0_REG (0x%x) = 0x%x\n", DDRDATA_CR_DCCDATACONTROL0_REG, DccDataControl0.Data);

  Offset = OFFSET_CALC_CH (DDRCLKCH0_CR_DCCCLKCONTROL0_REG, DDRCLKCH1_CR_DCCCLKCONTROL0_REG, Channel);
  DccClkControl0.Data = MrcReadCR (MrcData, Offset);
  DccClkControl0.Bits.ReplicaOffsetUse = 1;
  DccClkControl0.Bits.VTCompOffsetUse = 1;
  DccClkControl0.Bits.ActiveRanks = 1;  // Only Rank0 takes care of periodic for now
  MrcWriteCrMulticast (MrcData, DDRCLKCH0CH1_CR_DCCCLKCONTROL0_REG, DccClkControl0.Data);
  MRC_DEBUG_MSG (Debug, DebugLevel, "DDRCLKCH0CH1_CR_DCCCLKCONTROL0_REG (0x%x) = 0x%x\n", DDRCLKCH0CH1_CR_DCCCLKCONTROL0_REG, DccClkControl0.Data);

  MiscDccMainFsmControl1.Data = MrcReadCR (MrcData, MCMISCS_DCCMAINFSMCONTROL1_REG);
  MiscDccMainFsmControl1.Bits.PriodicCntPeriod = 0x61A80;  // 3ms x 133MHz
  MiscDccMainFsmControl1.Bits.PriodicCntEn = 0;
  MrcWriteCR (MrcData, MCMISCS_DCCMAINFSMCONTROL1_REG, MiscDccMainFsmControl1.Data);
  MRC_DEBUG_MSG (Debug, DebugLevel, "MCMISCS_DCCMAINFSMCONTROL1_REG (0x%x) = 0x%x\n", MCMISCS_DCCMAINFSMCONTROL1_REG, MiscDccMainFsmControl1.Data);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DCC ReInit End\n\n");
  return mrcSuccess;
}

/**
  This function will do the initial sweep of DCC CLK to populate the Look Up Table (LUT)

  @params[in] MrcData   - Pointer to MRC global data.

  @retval mrcSuccess if all tested points was able to finish testing, otherwise mrcFail.
**/
MrcStatus
MrcDccClkInitSweep (
  IN  MrcParameters * const MrcData
  )
{
  const MrcInput      *Inputs;
  const MRC_FUNCTION  *MrcCall;
  MrcOutput           *Outputs;
  MrcDebug            *Debug;
  MrcIntOutput        *MrcIntData;
  MrcStatus           Status;
  MrcDebugMsgLevel    DebugLevel;
  UINT8               StartPi;
  UINT8               EndPi;
  UINT8               IndexPi;
  UINT8               StepSize;
  UINT8               i;
  UINT8               DccResult;
  UINT16              ActiveDccRank0[MAX_CHANNEL];
  UINT32              Channel;
  UINT32              Offset;
  UINT32              PrintMode;
  UINT32              MaxClkGroup;
  INT64               ClkPi;
  INT64               GetSetVal;
  INT64               DccAipCb;
  BOOLEAN             UlxUlt;
  BOOLEAN             Gear2;
  BOOLEAN             Rerun[MAX_CHANNEL][MAX_RANK_IN_CHANNEL];
  BOOLEAN             RerunNeeded;
  DDRCLKCH0_CR_DCCCLKCONTROL0_STRUCT   DccClkControl0;
  DDRCLKCH0_CR_DCCCLKCONTROL1_STRUCT   DccClkControl1;
  DDRCLKCH0_CR_DCCCLKCONTROL3_STRUCT   DccClkControl3;
  DDRCLKCH0_CR_DCCCLKTRAINVAL1_STRUCT  DccClkTrainVal1;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  PrintMode   = (DCC_PRINT) ? PrintValue : 0;
  DebugLevel  = (DCC_PRINT) ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;

  MrcCall->MrcSetMem ((UINT8 *) &MrcIntData->ClkDcc, MAX_CHANNEL * MAX_RANK_IN_CHANNEL * MAX_DCC_CLOCK_PI, 0);
  MrcCall->MrcSetMem ((UINT8 *) &MrcIntData->ClkDccAipCb, sizeof (MrcIntData->ClkDccAipCb), 1);  // Initial DccAipCb value is 1

  UlxUlt  = (Inputs->CpuModel == cmICL_ULX_ULT);
  Gear2   = Outputs->Gear2;
  MaxClkGroup = (UlxUlt) ? MRC_U_Y_CCC_GRP_MAX : MRC_H_S_CCC_GRP_MAX;
  Status = mrcSuccess;

  //@todo H/S sku code

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nDCC CLK Init Sweep training start\n");

  //Initialize variables
  StepSize = 1;
  MrcDccControlRegsRead (MrcData, TRUE, &DccClkControl0.Data, &DccClkControl1.Data, &DccClkControl3.Data, NULL);

  MrcDccMainFsmControl0 (MrcData, DCC_CLK, DCC_DCO_COMP_ON);

  DccAipCb = 1;
  if (Inputs->IclA0) {
    DccClkControl1.Bits.Rank0DccAipCb = (UINT32) DccAipCb;   // In A0 same field is called DccAipCb
  }
  DccClkControl1.Bits.DcdWindow = 0x800;
  DccClkControl0.Bits.ActiveRanks = 1;

  DccClkControl0.Bits.GVPointG2 = MrcIntData->SaGvPoint;
  MrcWriteCrMulticast (MrcData, DDRCLKCH0CH1_CR_DCCCLKCONTROL0_REG, DccClkControl0.Data);
  MRC_DEBUG_MSG (Debug, DebugLevel, "DDRCLKCH0CH1_DCCCLKCONTROL0: 0x%08X\n", DccClkControl0.Data);

  StartPi = DDRCMDBCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MIN;
  EndPi   = DDRCMDBCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MAX;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ActiveDccRank0[Channel] = Outputs->Controller[0].Channel[Channel].ValidRankBitMask;
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }

    Offset = OFFSET_CALC_CH (DDRCLKCH0_CR_DCCCLKTRAINVAL1_REG, DDRCLKCH1_CR_DCCCLKTRAINVAL1_REG, Channel);
    DccClkTrainVal1.Data = MrcReadCR (MrcData, Offset);
    DccClkTrainVal1.Bits.savecntsatchosenbinstep = 0;
    MrcWriteCR (MrcData, Offset, DccClkTrainVal1.Data);

    Offset = OFFSET_CALC_CH (DDRCLKCH0_CR_DCCCLKCONTROL3_REG, DDRCLKCH1_CR_DCCCLKCONTROL3_REG, Channel);
    DccClkControl3.Bits.ActiveDccRank0 = ActiveDccRank0[Channel];
    MrcWriteCR (MrcData, Offset, DccClkControl3.Data);
    MRC_DEBUG_MSG (Debug, DebugLevel, "DDRCLKCH%d_DCCCLKCONTROL3: 0x%08X\n", Channel, DccClkControl3.Data);

    Offset = OFFSET_CALC_CH (DDRCLKCH0_CR_DCCCLKCONTROL1_REG, DDRCLKCH1_CR_DCCCLKCONTROL1_REG, Channel);
    MrcWriteCR (MrcData, Offset, DccClkControl1.Data);
    MRC_DEBUG_MSG (Debug, DebugLevel, "DDRCLKCH%d_DCCCLKCONTROL1: 0x%08X\n", Channel, DccClkControl1.Data);
  }

  // Run once for DCO Comp
  Status = MrcDccRunTest (MrcData);

  MRC_DEBUG_MSG (Debug, DebugLevel, "DDRCOMP_DCCDCOCONTROL0: 0x%x\n", MrcReadCR (MrcData, DDRPHY_COMP_CR_DCCDCOCONTROL0_REG));
  MRC_DEBUG_MSG (Debug, DebugLevel, "DDRCOMP_DCCDCOCONTROL1: 0x%x\n", MrcReadCR (MrcData, DDRPHY_COMP_CR_DCCDCOCONTROL1_REG));
  MRC_DEBUG_MSG (Debug, DebugLevel, "DDRCOMP_DCCDCOSTATUS0:  0x%x\n", MrcReadCR (MrcData, DDRPHY_COMP_CR_DCCDCOSTATUS0_REG));
  MRC_DEBUG_MSG (Debug, DebugLevel, "DDRCOMP_DCCDCOSTATUS1:  0x%x\n", MrcReadCR (MrcData, DDRPHY_COMP_CR_DCCDCOSTATUS1_REG));

  // Disable DCO Comp
  MrcDccMainFsmControl0 (MrcData, DCC_CLK, DCC_DCO_COMP_OFF);
  if (Status != mrcSuccess) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s DCC CLK training did not complete for initial CLK PI\n", gErrString);
    return Status;
  }

  if (!Gear2) {
    // For Gear1 we only run the DCO step, no need to build the LUT
    return mrcSuccess;
  }

  for (IndexPi = StartPi; IndexPi <= EndPi; IndexPi += StepSize) {
    ClkPi = IndexPi;

    DccAipCb = 1;
    for (i = 0; i < MaxClkGroup; i++) {
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, i, ClkGrpPi, WriteToCache | PrintMode, &ClkPi);
      if (!Inputs->IclA0) {
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, i, GsmIocDccAipCb, WriteNoCache | PrintMode, &DccAipCb);
      }
    }
    MrcFlushRegisterCachedData (MrcData);

    // Run DCC FSM
    Status = MrcDccRunTest (MrcData);
    if (Status != mrcSuccess) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s DCC CLK training did not complete for CLK PI %d\n", gErrString, IndexPi);
      return Status;
    }

    // Capture FSM results
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      for (i = 0; i < MaxClkGroup; i++) {
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, i, GsmIocDccClkTrainVal, ReadUncached, &GetSetVal);
        MrcIntData->ClkDcc[Channel][i][IndexPi] = (UINT8) GetSetVal;
      }
    } // for Channel

    if (!Inputs->IclA0) {
      // Check if we got any saturated DCC values, and retrain with a different DccAipCb if saturated
      MrcCall->MrcSetMem ((UINT8 *) &Rerun, sizeof (Rerun), 0);
      RerunNeeded = FALSE;
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcChannelExist (Outputs, Channel)) {
          continue;
        }
        for (i = 0; i < MaxClkGroup; i++) {
          DccAipCb = 1;
          DccResult = MrcIntData->ClkDcc[Channel][i][IndexPi];
          if (DccResult < DCC_PASS_MIN) {
            DccAipCb = 0;
            Rerun[Channel][i] = TRUE;
          } else if (DccResult > DCC_PASS_MAX) {
            DccAipCb = 3;
            Rerun[Channel][i] = TRUE;
          }
          if (Rerun[Channel][i]) {
            RerunNeeded = TRUE;
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Saturated: C%d R%d Pi: %d Value: %d\n", Channel, i, IndexPi, DccResult);
            MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, i, GsmIocDccAipCb, WriteNoCache | PrintMode, &DccAipCb);
            MrcIntData->ClkDccAipCb[Channel][i][IndexPi] = (UINT8) DccAipCb;
          }
        }
      } // for Channel

      if (RerunNeeded) {
        // Run DCC FSM again
        Status = MrcDccRunTest (MrcData);
        if (Status != mrcSuccess) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s DCC CLK training did not complete for CLK PI %d\n", gErrString, IndexPi);
          return Status;
        }

        // Capture FSM results
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!MrcChannelExist (Outputs, Channel)) {
            continue;
          }
          for (i = 0; i < MaxClkGroup; i++) {
            if (Rerun[Channel][i]) {
              MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, i, GsmIocDccClkTrainVal, ReadUncached, &GetSetVal);
              MrcIntData->ClkDcc[Channel][i][IndexPi] = (UINT8) GetSetVal;
              if ((GetSetVal < DCC_PASS_MIN) || (GetSetVal > DCC_PASS_MAX)) {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "--> Still saturated: C%d R%d Pi: %d Value: %d\n", Channel, i, IndexPi, (UINT8) GetSetVal);
              }
            }
          }
        } // for Channel
      } // if Rerun
    } // if not A0
  } // for IndexPi

  MrcWait (MrcData, DIVIDECEIL (100, MRC_TIMER_1NS));
  MrcIntData->ClkDccInit = TRUE;

#ifdef MRC_DEBUG_PRINT
  MrcDccResultsDebugPrint (MrcData, TRUE, FALSE);
#endif
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DCC CLK Init Sweep training end\n\n");
  return Status;
}

/**
  This function will do the initial sweep of DCC DQS to populate the Look Up Table (LUT)

  @params[in] MrcData   - Pointer to MRC global data.

  @retval mrcSuccess if all tested points was able to finish testing, otherwise mrcFail.
**/
MrcStatus
MrcDccDqsInitSweep (
  IN  MrcParameters * const MrcData
  )
{
  const MrcInput      *Inputs;
  const MRC_FUNCTION  *MrcCall;
  MrcOutput           *Outputs;
  MrcDebug            *Debug;
  MrcIntOutput        *MrcIntData;
  MrcStatus           Status;
  MrcStatus           CurStatus;
  MrcDebugMsgLevel    DebugLevel;
  UINT8               IndexPi;
  UINT8               StepSize;
  UINT8               SdramCount;
  UINT8               DccResult;
  UINT32              Channel;
  UINT32              Byte;
  UINT32              PrintMode;
  UINT32              Offset;
  INT64               TxDqsPi;
  INT64               GetSetVal;
  INT64               DccAipCb;
  BOOLEAN             Rerun[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  BOOLEAN             RerunNeeded;
  DDRDATA0CH0_CR_DCCDATACONTROL0_STRUCT       DccDataControl0;
  DDRDATA0CH0_CR_DCCDATACONTROL1_STRUCT       DccDataControl1;
  DDRDATA0CH0_CR_DCCDATACONTROL3_STRUCT       DccDataControl3;
  DDRDATA0CH0_CR_DCCDATATRAINVAL1RANK1_STRUCT DccDataTrainVal1Rank1;

  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  Inputs      = &MrcData->Inputs;
  MrcCall     = Inputs->Call.Func;
  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  PrintMode   = (DCC_PRINT) ? PrintValue : 0;
  DebugLevel  = (DCC_PRINT) ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;

  MrcCall->MrcSetMem ((UINT8 *) &MrcIntData->DqsDcc, MAX_CHANNEL * MAX_SDRAM_IN_DIMM * MAX_DCC_TX_DQS_DQ_PI, 0);
  MrcCall->MrcSetMem ((UINT8 *) &MrcIntData->DqsDccAipCb, sizeof (MrcIntData->DqsDccAipCb), 1);  // Initial DqsDccAipCb value is 1
  Status = mrcSuccess;
  SdramCount = Outputs->SdramCount;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nDCC DQS Init Sweep training start\n");

  //@todo H/S sku code

  StepSize = 1;
  MrcDccControlRegsRead (MrcData, FALSE, &DccDataControl0.Data, &DccDataControl1.Data, &DccDataControl3.Data, NULL);
  MrcDccMainFsmControl0 (MrcData, DCC_DATA, DCC_DCO_COMP_OFF);

  DccAipCb = 1;
  DccDataControl0.Bits.GVPointG2 = MrcIntData->SaGvPoint;
  //@todo Does this ActiveRank change w/ DT and no Rank 0 populated
  DccDataControl0.Bits.ActiveRanks = 0x1;
  if (Inputs->IclA0) {
    DccDataControl1.Bits.RepDccAipCb = (UINT32) DccAipCb;  // In A0 same field is called DccAipCb
  }
  DccDataControl1.Bits.DcdWindow = 0x800;
  DccDataControl3.Bits.ActiveDccRank0 = 0x100;

  MrcWriteCrMulticast (MrcData, DDRDATA_CR_DCCDATACONTROL0_REG, DccDataControl0.Data);
  MrcWriteCrMulticast (MrcData, DDRDATA_CR_DCCDATACONTROL1_REG, DccDataControl1.Data);
  MrcWriteCrMulticast (MrcData, DDRDATA_CR_DCCDATACONTROL3_REG, DccDataControl3.Data);
  MRC_DEBUG_MSG (Debug, DebugLevel, "DDRDATA_DCCDATACONTROL0: 0x%08x\n", DccDataControl0.Data);
  MRC_DEBUG_MSG (Debug, DebugLevel, "DDRDATA_DCCDATACONTROL1: 0x%08x\n", DccDataControl1.Data);
  MRC_DEBUG_MSG (Debug, DebugLevel, "DDRDATA_DCCDATACONTROL3: 0x%08x\n", DccDataControl3.Data);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(MrcChannelExist (Outputs, Channel))) {
      continue;
    }
    for (Byte = 0; Byte < SdramCount; Byte++) {
      if (!Inputs->IclA0) {
        Offset = DDRDATA0CH0_CR_DCCDATATRAINVAL1RANK1_REG +
                (DDRDATA0CH1_CR_DCCDATATRAINVAL1RANK0_REG - DDRDATA0CH0_CR_DCCDATATRAINVAL1RANK0_REG) * Channel +
                (DDRDATA1CH0_CR_DCCDATATRAINVAL1RANK0_REG - DDRDATA0CH0_CR_DCCDATATRAINVAL1RANK0_REG) * Byte;
        DccDataTrainVal1Rank1.Data = MrcReadCR (MrcData, Offset);
        DccDataTrainVal1Rank1.Bits.savecntsatchosenbinstep = 0;
        MrcWriteCR (MrcData, Offset, DccDataTrainVal1Rank1.Data);
      }
    }
  }

  for (IndexPi = 0; IndexPi < MAX_DCC_TX_DQS_DQ_PI; IndexPi += StepSize) {
    TxDqsPi = IndexPi;
    //@todo DT change for Rank checked
    MrcGetSetDdrIoGroupStrobe (MrcData, MAX_CHANNEL, 0, MAX_SDRAM_IN_DIMM, TxDqsDelay, WriteToCache | PrintMode, &TxDqsPi);
    MrcFlushRegisterCachedData (MrcData);

    if (!Inputs->IclA0) {
      MrcGetSetDdrIoGroupStrobe (MrcData, MAX_CHANNEL, 0, MAX_SDRAM_IN_DIMM, GsmIocDccAipCbDqs, WriteNoCache, &DccAipCb);
    }

    // Run DCC FSM
    CurStatus = MrcDccRunTest (MrcData);
    if (CurStatus != mrcSuccess) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s DCC DQS training did not complete for TX DQS PI %d\n", gErrString, IndexPi);
      return CurStatus;
    }

    // Capture FSM results
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      for (Byte = 0; Byte < SdramCount; Byte++) {
        MrcGetSetDdrIoGroupStrobe (MrcData, Channel, 0, Byte, GsmIocDccDataTrainDqsVal, ReadNoCache, &GetSetVal);
        MrcIntData->DqsDcc[Channel][Byte][IndexPi] = (UINT8) GetSetVal;
      }
    } // for Channel

    if (!Inputs->IclA0) {
      // Check if we got any saturated DCC values, and retrain with a different DccAipCb if saturated
      MrcCall->MrcSetMem ((UINT8 *) &Rerun, sizeof (Rerun), 0);
      RerunNeeded = FALSE;
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcChannelExist (Outputs, Channel)) {
          continue;
        }
        for (Byte = 0; Byte < SdramCount; Byte++) {
          DccAipCb = 1;
          DccResult = MrcIntData->DqsDcc[Channel][Byte][IndexPi];
          if (DccResult < DCC_PASS_MIN) {
            DccAipCb = 0;
            Rerun[Channel][Byte] = TRUE;
          } else if (DccResult > DCC_PASS_MAX) {
            DccAipCb = 3;
            Rerun[Channel][Byte] = TRUE;
          }
          if (Rerun[Channel][Byte]) {
            RerunNeeded = TRUE;
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Saturated: C%d B%d Pi: %d Value: %d\n", Channel, Byte, IndexPi, DccResult);
            MrcGetSetDdrIoGroupStrobe (MrcData, Channel, 0, Byte, GsmIocDccAipCbDqs, WriteNoCache | PrintMode, &DccAipCb);
            MrcIntData->DqsDccAipCb[Channel][Byte][IndexPi] = (UINT8) DccAipCb;
          }
        }
      } // for Channel

      if (RerunNeeded) {
        // Run DCC FSM again
        Status = MrcDccRunTest (MrcData);
        if (Status != mrcSuccess) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s DCC DQS training did not complete for TX DQS PI %d\n", gErrString, IndexPi);
          return Status;
        }

        // Capture FSM results
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!MrcChannelExist (Outputs, Channel)) {
            continue;
          }
          for (Byte = 0; Byte < SdramCount; Byte++) {
            if (Rerun[Channel][Byte]) {
              MrcGetSetDdrIoGroupStrobe (MrcData, Channel, 0, Byte, GsmIocDccDataTrainDqsVal, ReadNoCache, &GetSetVal);
              MrcIntData->DqsDcc[Channel][Byte][IndexPi] = (UINT8) GetSetVal;
              if ((GetSetVal < DCC_PASS_MIN) || (GetSetVal > DCC_PASS_MAX)) {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "--> Still saturated: C%d B%d Pi: %d Value: %d\n", Channel, Byte, IndexPi, (UINT8) GetSetVal);
              }
            }
          }
        } // for Channel
      } // if Rerun
    } // if not A0
  } // for IndexPi

  MrcIntData->DqsDccInit = TRUE;

#ifdef MRC_DEBUG_PRINT
  MrcDccResultsDebugPrint (MrcData, FALSE, TRUE);
#endif
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DCC DQS Init Sweep training end\n\n");
  return Status;
}

/**
  This function will do the initial sweep of DCC DQ per Byte

  @params[in] MrcData   - Pointer to MRC global data.

  @retval mrcSuccess if all tested points was able to finish testing, otherwise mrcFail.
**/
MrcStatus
MrcDccDqByteInitSweep (
  IN  MrcParameters * const MrcData
  )
{
  const MrcInput      *Inputs;
  const MRC_FUNCTION  *MrcCall;
  MrcOutput           *Outputs;
  MrcDebug            *Debug;
  MrcIntOutput        *MrcIntData;
  MrcStatus           Status;
  MrcStatus           CurStatus;
  MrcDebugMsgLevel    DebugLevel;
  UINT8               IndexPi;
  UINT8               StepSize;
  UINT8               SdramCount;
  UINT32              Channel;
  UINT32              Byte;
  UINT32              PrintMode;
  UINT32              Offset;
  UINT32              DccAipCb;
  UINT32              DccResult;
  INT64               TxDqPi;
  BOOLEAN             RerunNeeded;
  BOOLEAN             Rerun[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  DDRDATA0CH0_CR_DCCDATACONTROL0_STRUCT   DccDataControl0;
  DDRDATA0CH0_CR_DCCDATACONTROL3_STRUCT   DccDataControl3;
  DDRDATA0CH0_CR_DCCDATADCCPILUT5_STRUCT  DccDataDccPiLut5;
  DDRDATA0CH0_CR_DCCDATATRAINVAL0RANK0_STRUCT DccDataTrainVal0Rank0;

  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  Inputs      = &MrcData->Inputs;
  MrcCall     = Inputs->Call.Func;
  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  PrintMode   = (DCC_PRINT) ? PrintValue : 0;
  DebugLevel  = (DCC_PRINT) ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;

  Status = mrcSuccess;
  SdramCount = Outputs->SdramCount;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nDCC DQ Byte Init Sweep training start\n");

  StepSize = 4;

  MrcDccControlRegsRead (MrcData, FALSE, &DccDataControl0.Data, NULL, &DccDataControl3.Data, NULL);
  MrcDccMainFsmControl0 (MrcData, DCC_DATA, DCC_DCO_COMP_OFF);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      Offset = OFFSET_CALC_CH (DDRDATA0CH0_CR_DCCDATADCCPILUT5_REG, DDRDATA0CH1_CR_DCCDATADCCPILUT5_REG, Channel);
      DccDataDccPiLut5.Data = MrcReadCR (MrcData, Offset);

      Offset = OFFSET_CALC_CH (DDRDATA0CH0_CR_DCCDATATRAINVAL0RANK0_REG, DDRDATA0CH1_CR_DCCDATATRAINVAL0RANK0_REG, Channel);
      DccDataTrainVal0Rank0.Data = MrcReadCR (MrcData, Offset);
      break;
    }
  }
  DccDataDccPiLut5.Bits.DccPiAipCb = 1;

  DccDataControl0.Bits.GVPointG2      = MrcIntData->SaGvPoint;
  DccDataControl0.Bits.ActiveRanks    = 0x1;
  DccDataControl3.Bits.ActiveDccRank0 = 0x1;
  DccDataTrainVal0Rank0.Bits.DqDccAipCb = 1;

  MrcWriteCrMulticast (MrcData, DDRDATA_CR_DCCDATACONTROL0_REG, DccDataControl0.Data);
  MrcWriteCrMulticast (MrcData, DDRDATA_CR_DCCDATACONTROL3_REG, DccDataControl3.Data);
  MrcWriteCrMulticast (MrcData, DDRDATA_CR_DCCDATADCCPILUT5_REG, DccDataDccPiLut5.Data);
  MrcWriteCrMulticast (MrcData, DDRDATA_CR_DCCDATATRAINVAL0RANK0_REG, DccDataTrainVal0Rank0.Data);
  MRC_DEBUG_MSG (Debug, DebugLevel, "DDRDATA_DCCDATACONTROL0: 0x%x\n", DccDataControl0.Data);
  MRC_DEBUG_MSG (Debug, DebugLevel, "DDRDATA_DCCDATACONTROL3: 0x%x\n", DccDataControl3.Data);
  MRC_DEBUG_MSG (Debug, DebugLevel, "DDRDATA_DCCDATADCCPILUT5: 0x%x\n", DccDataDccPiLut5.Data);
  MRC_DEBUG_MSG (Debug, DebugLevel, "DDRDATA_DCCDATATRAINVAL0RANK0: 0x%x\n", DccDataTrainVal0Rank0.Data);

  // Set TxDqPi to 12 in all bytes on Rank 0
  TxDqPi = 12;
  MrcGetSetDdrIoGroupStrobe (MrcData, MAX_CHANNEL, 0, MAX_SDRAM_IN_DIMM, TxDqDelay, WriteToCache | PrintMode, &TxDqPi);
  MrcFlushRegisterCachedData (MrcData);

  // Run DCC FSM
  CurStatus = MrcDccRunTest (MrcData);
  if (CurStatus != mrcSuccess) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s DCC DQ Byte training did not complete for initial PI = 12\n", gErrString);
    return CurStatus;
  }
  if (!Inputs->IclA0) {
    // Check if we got any saturated DCC values, and retrain with a different DccAipCb if saturated
    MrcCall->MrcSetMem ((UINT8 *) &Rerun, sizeof (Rerun), 0);
    RerunNeeded = FALSE;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      for (Byte = 0; Byte < SdramCount; Byte++) {
        DccAipCb = 1;
        Offset = DDRDATA0CH0_CR_DCCDATATRAINVAL0RANK0_REG +
               ((DDRDATA0CH1_CR_DCCDATATRAINVAL0RANK0_REG - DDRDATA0CH0_CR_DCCDATATRAINVAL0RANK0_REG) * Channel) +
               ((DDRDATA1CH0_CR_DCCDATATRAINVAL0RANK0_REG - DDRDATA0CH0_CR_DCCDATATRAINVAL0RANK0_REG) * Byte);
        DccDataTrainVal0Rank0.Data = MrcReadCR (MrcData, Offset);
        DccResult = DccDataTrainVal0Rank0.Bits.Dq0DccVal;
        if (DccResult < DCC_PASS_MIN) {
          DccAipCb = 0;
          Rerun[Channel][Byte] = TRUE;
        } else if (DccResult > DCC_PASS_MAX) {
          DccAipCb = 3;
          Rerun[Channel][Byte] = TRUE;
        }
        if (Rerun[Channel][Byte]) {
          RerunNeeded = TRUE;
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Saturated: C%d B%d Value: %d\n", Channel, Byte, DccResult);
          DccDataTrainVal0Rank0.Bits.DqDccAipCb = DccAipCb;
          MrcWriteCR (MrcData, Offset, DccDataTrainVal0Rank0.Data);
        }
      }
    } // for Channel

    if (RerunNeeded) {
      // Run DCC FSM again
      Status = MrcDccRunTest (MrcData);
      if (Status != mrcSuccess) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s DCC DQ Byte training did not complete for initial PI = 12\n", gErrString);
        return Status;
      }

      // Capture FSM results
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcChannelExist (Outputs, Channel)) {
          continue;
        }
        for (Byte = 0; Byte < SdramCount; Byte++) {
          if (Rerun[Channel][Byte]) {
            Offset = DDRDATA0CH0_CR_DCCDATATRAINVAL0RANK0_REG +
               ((DDRDATA0CH1_CR_DCCDATATRAINVAL0RANK0_REG - DDRDATA0CH0_CR_DCCDATATRAINVAL0RANK0_REG) * Channel) +
               ((DDRDATA1CH0_CR_DCCDATATRAINVAL0RANK0_REG - DDRDATA0CH0_CR_DCCDATATRAINVAL0RANK0_REG) * Byte);
            DccDataTrainVal0Rank0.Data = MrcReadCR (MrcData, Offset);
            DccResult = DccDataTrainVal0Rank0.Bits.Dq0DccVal;
            if ((DccResult < DCC_PASS_MIN) || (DccResult > DCC_PASS_MAX)) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "--> Still saturated: C%d B%d Value: %d\n", Channel, Byte, DccResult);
            }
          }
        }
      } // for Channel
    } // if Rerun
  } // if not A0

  DccDataControl3.Bits.ActiveDccRank0 = 0x400;
  MrcWriteCrMulticast (MrcData, DDRDATA_CR_DCCDATACONTROL3_REG, DccDataControl3.Data);
  MRC_DEBUG_MSG (Debug, DebugLevel, "DDRDATA_CR_DCCDATACONTROL3: 0x%x\n", DccDataControl3.Data);

  for (IndexPi = 0; IndexPi < MAX_DCC_TX_DQS_DQ_PI; IndexPi += StepSize) {
    TxDqPi = IndexPi;
    MrcGetSetDdrIoGroupStrobe (MrcData, MAX_CHANNEL, 0, MAX_SDRAM_IN_DIMM, TxDqDelay, WriteToCache | PrintMode, &TxDqPi);
    MrcFlushRegisterCachedData (MrcData);

    // Run DCC FSM
    CurStatus = MrcDccRunTest (MrcData);
    if (CurStatus != mrcSuccess) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s DCC DQ Byte training did not complete for TX DQ PI 0x%x\n", gErrString, IndexPi);
      return CurStatus;
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DCC DQ Byte Init Sweep training end\n\n");
  return Status;
}

/**
  This function will do the initial sweep of DCC DQ per Bit

  @params[in] MrcData   - Pointer to MRC global data.

  @retval mrcSuccess if all tested points was able to finish testing, otherwise mrcFail.
**/
MrcStatus
MrcDccDqBitInitSweep (
  IN  MrcParameters * const MrcData
  )
{
  const MrcInput      *Inputs;
  const MRC_FUNCTION  *MrcCall;
  MrcOutput           *Outputs;
  MrcDebug            *Debug;
  MrcIntOutput        *MrcIntData;
  MrcStatus           Status;
  MrcDebugMsgLevel    DebugLevel;
  UINT32              Channel;
  UINT32              Rank;
  UINT32              Byte;
  UINT32              Bit;
  UINT32              Offset;
  UINT32              Offset0;
  UINT32              Offset1;
  UINT32              PrintMode;
  UINT32              DccAipCb;
  UINT32              DccResult;
  INT64               GetSetVal;
  BOOLEAN             BitSaturated;
  BOOLEAN             BitOpposite;
  BOOLEAN             RerunNeeded;
  BOOLEAN             Rerun[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  DDRDATA0CH0_CR_DCCDATACONTROL0_STRUCT   DccDataControl0;
  DDRDATA0CH0_CR_DCCDATACONTROL3_STRUCT   DccDataControl3;
  DDRDATA0CH0_CR_DCCDATACONTROL4_STRUCT   DccDataControl4;
  DDRDATA0CH0_CR_DCCDATACONTROL3_STRUCT   DccDataControl3Orig;
  DDRDATA0CH0_CR_DCCDATACONTROL4_STRUCT   DccDataControl4Orig;
  DDRDATA0CH0_CR_DCCDATATRAINVAL0RANK0_STRUCT DccDataTrainVal0;
  DDRDATA0CH0_CR_DCCDATATRAINVAL1RANK0_STRUCT DccDataTrainVal1;

  Inputs      = &MrcData->Inputs;
  MrcCall     = Inputs->Call.Func;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  PrintMode   = (DCC_PRINT) ? PrintValue : 0;
  DebugLevel  = (DCC_PRINT) ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nDCC DQ Bit Init Sweep training start\n");

  MrcDccControlRegsRead (MrcData, FALSE, &DccDataControl0.Data, NULL, &DccDataControl3Orig.Data, &DccDataControl4Orig.Data);
  MrcDccMainFsmControl0 (MrcData, DCC_DATA, DCC_DCO_COMP_OFF);

  DccDataControl0.Bits.GVPointG2 = MrcIntData->SaGvPoint;
  DccDataControl0.Bits.ActiveRanks = 0;
  DccDataControl3Orig.Bits.ActiveDccRank0 = 0;
  DccDataControl3Orig.Bits.ActiveDccRank1 = 0;
  DccDataControl3Orig.Bits.ActiveDccRank2 = 0;
  DccDataControl4Orig.Bits.ActiveDccRank3 = 0;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(MrcChannelExist (Outputs, Channel))) {
      continue;
    }
    DccDataControl3.Data = DccDataControl3Orig.Data;
    DccDataControl4.Data = DccDataControl4Orig.Data;

    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
        continue;
      }
      DccDataControl0.Bits.ActiveRanks |= (1 << Rank);
      switch (Rank) {
        case 0:
          DccDataControl3.Bits.ActiveDccRank0 = 0xFF;
          break;

        case 1:
          DccDataControl3.Bits.ActiveDccRank1 = 0xFF;
          break;

        case 2:
          DccDataControl3.Bits.ActiveDccRank2 = 0xFF;
          break;

        case 3:
          DccDataControl4.Bits.ActiveDccRank3 = 0xFF;
          break;
      }
    }

    Offset = OFFSET_CALC_CH (DDRDATACH0_CR_DCCDATACONTROL0_REG, DDRDATACH1_CR_DCCDATACONTROL0_REG, Channel);
    MrcWriteCrMulticast (MrcData, Offset, DccDataControl0.Data);
    MRC_DEBUG_MSG (Debug, DebugLevel, "DDRDATACH%d_DCCDATACONTROL0: 0x%x\n", Channel, DccDataControl0.Data);

    Offset = OFFSET_CALC_CH (DDRDATACH0_CR_DCCDATACONTROL3_REG, DDRDATACH1_CR_DCCDATACONTROL3_REG, Channel);
    MrcWriteCrMulticast (MrcData, Offset, DccDataControl3.Data);
    MRC_DEBUG_MSG (Debug, DebugLevel, "DDRDATACH%d_DCCDATACONTROL3: 0x%x\n", Channel, DccDataControl3.Data);

    Offset = OFFSET_CALC_CH (DDRDATACH0_CR_DCCDATACONTROL4_REG, DDRDATACH1_CR_DCCDATACONTROL4_REG, Channel);
    MrcWriteCrMulticast (MrcData, Offset, DccDataControl4.Data);
    MRC_DEBUG_MSG (Debug, DebugLevel, "DDRDATACH%d_DCCDATACONTROL4: 0x%x\n", Channel, DccDataControl4.Data);

    GetSetVal = 12;
    MrcGetSetDdrIoGroupStrobe (MrcData, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, TxDqDelay, WriteToCache | PrintMode, &GetSetVal);
  }
  MrcFlushRegisterCachedData (MrcData);

  // Run DCC FSM
  Status = MrcDccRunTest (MrcData);
  if (Status != mrcSuccess) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s DCC DQ Bit training did not complete\n", gErrString);
    return Status;
  }

  if (!Inputs->IclA0) {
    // Check if we got any saturated DCC values, and retrain with a different DccAipCb if saturated
    MrcCall->MrcSetMem ((UINT8 *) &Rerun, sizeof (Rerun), 0);
    RerunNeeded = FALSE;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      for (Rank  = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
          continue;
        }
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          Offset = ((DDRDATA0CH1_CR_DCCDATATRAINVAL0RANK0_REG - DDRDATA0CH0_CR_DCCDATATRAINVAL0RANK0_REG) * Channel) +
                   ((DDRDATA0CH0_CR_DCCDATATRAINVAL0RANK1_REG - DDRDATA0CH0_CR_DCCDATATRAINVAL0RANK0_REG) * Rank) +
                   ((DDRDATA1CH0_CR_DCCDATATRAINVAL0RANK0_REG - DDRDATA0CH0_CR_DCCDATATRAINVAL0RANK0_REG) * Byte);
          Offset0 = Offset + DDRDATA0CH0_CR_DCCDATATRAINVAL0RANK0_REG;
          Offset1 = Offset + DDRDATA0CH0_CR_DCCDATATRAINVAL1RANK0_REG;
          DccDataTrainVal0.Data = MrcReadCR (MrcData, Offset0);
          DccDataTrainVal1.Data = MrcReadCR (MrcData, Offset1);
          DccAipCb = 1;
          for (Bit = 0; Bit < MAX_BITS; Bit++) {
            BitSaturated = FALSE;
            BitOpposite  = FALSE;
            if (Bit <= 4) {
              DccResult = (DccDataTrainVal0.Data >> (Bit * DDRDATA_CR_DCCDATATRAINVAL0RANK0_Dq0DccVal_WID)) & DDRDATA_CR_DCCDATATRAINVAL0RANK0_Dq0DccVal_MSK;
            } else { // This is DccDataTrainVal1RankX
              DccResult = (DccDataTrainVal1.Data >> ((Bit - 5) * DDRDATA_CR_DCCDATATRAINVAL1RANK0_Dq5DccVal_WID)) & DDRDATA_CR_DCCDATATRAINVAL1RANK0_Dq5DccVal_MSK;
            }
            if (DccResult < DCC_PASS_MIN) {
              if (DccAipCb == 3) {  // Bits in the same byte pull in opposite direction
                BitOpposite = TRUE;
              }
              DccAipCb = 0;
              Rerun[Channel][Rank][Byte] = TRUE;
              BitSaturated = TRUE;
            } else if (DccResult > DCC_PASS_MAX) {
              if (DccAipCb == 0) {  // Bits in the same byte pull in opposite direction
                BitOpposite = TRUE;
              }
              DccAipCb = 3;
              Rerun[Channel][Rank][Byte] = TRUE;
              BitSaturated = TRUE;
            }
            if (BitSaturated) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Saturated: C%d R%d B%d Dq%d Value: %d %s\n", Channel, Rank, Byte, Bit, DccResult, (BitOpposite ? "Opposite!" : ""));
            }
          } // for Bit
          if (Rerun[Channel][Rank][Byte]) {
            RerunNeeded = TRUE;
            DccDataTrainVal0.Bits.DqDccAipCb = DccAipCb;
            MrcWriteCR (MrcData, Offset0, DccDataTrainVal0.Data);
          }
        } // for Byte
      } // for Rank
    } // for Channel

    if (RerunNeeded) {
      // Run DCC FSM again
      Status = MrcDccRunTest (MrcData);
      if (Status != mrcSuccess) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s DCC DQ Byte training did not complete for initial PI = 12\n", gErrString);
        return Status;
      }

      // Capture FSM results
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        for (Rank  = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
            continue;
          }
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            Offset = ((DDRDATA0CH1_CR_DCCDATATRAINVAL0RANK0_REG - DDRDATA0CH0_CR_DCCDATATRAINVAL0RANK0_REG) * Channel) +
                     ((DDRDATA0CH0_CR_DCCDATATRAINVAL0RANK1_REG - DDRDATA0CH0_CR_DCCDATATRAINVAL0RANK0_REG) * Rank) +
                     ((DDRDATA1CH0_CR_DCCDATATRAINVAL0RANK0_REG - DDRDATA0CH0_CR_DCCDATATRAINVAL0RANK0_REG) * Byte);
            Offset0 = Offset + DDRDATA0CH0_CR_DCCDATATRAINVAL0RANK0_REG;
            Offset1 = Offset + DDRDATA0CH0_CR_DCCDATATRAINVAL1RANK0_REG;
            DccDataTrainVal0.Data = MrcReadCR (MrcData, Offset0);
            DccDataTrainVal1.Data = MrcReadCR (MrcData, Offset1);
            for (Bit = 0; Bit < MAX_BITS; Bit++) {
              if (Bit <= 4) {
                DccResult = (DccDataTrainVal0.Data >> (Bit * DDRDATA_CR_DCCDATATRAINVAL0RANK0_Dq0DccVal_WID)) & DDRDATA_CR_DCCDATATRAINVAL0RANK0_Dq0DccVal_MSK;
              } else { // This is DccDataTrainVal1RankX
                DccResult = (DccDataTrainVal1.Data >> ((Bit - 5) * DDRDATA_CR_DCCDATATRAINVAL1RANK0_Dq5DccVal_WID)) & DDRDATA_CR_DCCDATATRAINVAL1RANK0_Dq5DccVal_MSK;
              }
              if ((DccResult < DCC_PASS_MIN) || (DccResult > DCC_PASS_MAX)) {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "--> Still saturated: C%d R%d B%d Dq%d Value: %d\n", Channel, Rank, Byte, Bit, DccResult);
              }
            } // for Bit
          } // for Byte
        } // for Rank
      } // for Channel
    } // if Rerun
  } // if not A0
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DCC DQ Bit Init Sweep training end\n\n");
  return Status;
}

/**
  This function will update the corresponding stored register values (from LUT) for DCC CLK / DQS PI setting

  @params[in] MrcData - Pointer to MRC global data.
  @params[in] Channel - The Channel being adjusted for.
  @params[in] Rank    - The Rank in the Channel being adjusted for.
  @params[in] Strobe  - The Byte in the Rank being adjusted for.
  @params[in] Group   - GetSet group to update: GsmIocDccClkTrainVal or GsmIocDccDataTrainDqsVal
  @params[in] Value   - The PI setting being adjusted for.
  @params[in] Flush   - TRUE to flush the register cache at end of function or FALSE and let caller take care of this.

  @retval Nothing
**/
void
MrcDccUpdate (
  IN  MrcParameters * const MrcData,
  IN  UINT32                Channel,
  IN  UINT32                Rank,
  IN  UINT32                Strobe,
  IN  GSM_GT        const   Group,
  IN  INT64         *const  Value,
  IN  BOOLEAN               Flush
  )
{
  MrcIntOutput        *MrcIntData;
  MrcOutput           *Outputs;
  INT64               GetSetVal;
  INT64               DccAipCb;
  UINT32              Pi;
  UINT32              Index;
  UINT32              PrintMode;

  Outputs = &MrcData->Outputs;
  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  PrintMode = (DCC_PRINT) ? PrintValue : 0;

  if ((Outputs->Gear2 == 0) || !((Group == GsmIocDccClkTrainVal) || (Group == GsmIocDccDataTrainDqsVal))) {
    // Nothing to update for Gear 1 or when not adjusting the correct DCC Value
    return;
  }

  Pi = (UINT32) *Value;
  Index = (Group == GsmIocDccClkTrainVal) ? MAX_RANK_IN_CHANNEL : MAX_SDRAM_IN_DIMM;
  Index--;
  Index = MIN (Strobe, Index);
  GetSetVal = (Group == GsmIocDccClkTrainVal) ? MrcIntData->ClkDcc[Channel][Index][Pi] : MrcIntData->DqsDcc[Channel][Index][Pi];

  MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Strobe, Group, WriteNoCache | PrintMode, &GetSetVal);

  if (Group == GsmIocDccClkTrainVal) {
    DccAipCb = MrcIntData->ClkDccAipCb[Channel][Index][Pi];
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Strobe, GsmIocDccAipCb, WriteNoCache | PrintMode, &DccAipCb);
  }

  if (Group == GsmIocDccDataTrainDqsVal) {
    DccAipCb = MrcIntData->DqsDccAipCb[Channel][Index][Pi];
    MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Strobe, GsmIocDccAipCbDqs, WriteNoCache | PrintMode, &DccAipCb);
  }
}

/**
  This function will do the final setup of DCC CLK prior to end of SAGV.

  @params[in] MrcData   - Pointer to MRC global data.

  @retval mrcSuccess if no Timeout occurred, otherwise mrcFail.
**/
MrcStatus
MrcDccClkFinalization (
  IN  MrcParameters * const MrcData
  )
{
  const MRC_FUNCTION  *MrcCall;
  MrcIntOutput      *MrcIntData;
  MrcInput          *Inputs;
  MrcOutput         *Outputs;
  MrcDebug          *Debug;
  MrcDebugMsgLevel  DebugLevel;
  UINT32            ReplicaValue;
  UINT32            Offset;
  UINT32            Channel;
  UINT32            Replica[MAX_CHANNEL];
  UINT32            DccAipCb;
  MrcStatus         Status;
  BOOLEAN           Rerun[MAX_CHANNEL];
  BOOLEAN           RerunNeeded;
  BOOLEAN           Saturated;
  DDRCLKCH0_CR_DCCCLKCONTROL1_STRUCT        DccClkControl1;
  DDRCLKCH0_CR_DCCCLKCONTROL3_STRUCT        DccClkControl3;
  DDRCLKCH0_CR_DCCCLKTRAINVAL1_STRUCT       DccClkTrainVal1;
  DDRCLKCH0_CR_DCCCLKTRAINREPLICA0_STRUCT   DccClkTrainReplica0;
  DDRCLKCH0_CR_DCCCLKTRAINSTATUS2_STRUCT    DccClkTrainStatus2;

  MrcIntData  = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Inputs      = &MrcData->Inputs;
  MrcCall     = Inputs->Call.Func;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  DebugLevel  = (DCC_PRINT) ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;

  MrcCall->MrcSetMem ((UINT8 *) &Replica, sizeof (Replica), 0);
  MrcCall->MrcSetMem ((UINT8 *) &Rerun, sizeof (Rerun), 0);
  RerunNeeded = FALSE;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nDCC CLK Replica Start\n");
  MrcDccMainFsmControl0 (MrcData, DCC_CLK, DCC_DCO_COMP_OFF);

  MrcDccControlRegsRead (MrcData, TRUE, NULL, &DccClkControl1.Data, &DccClkControl3.Data, NULL);

  DccClkControl3.Bits.ActiveDccRank0 = 0x4;
  DccAipCb = 1;
  if (Inputs->IclA0) {
    DccClkControl1.Bits.Rank0DccAipCb = (UINT32) DccAipCb;   // In A0 this field is called DccAipCb
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(MrcChannelExist (Outputs, Channel))) {
      continue;
    }
    Offset = OFFSET_CALC_CH (DDRCLKCH0_CR_DCCCLKCONTROL3_REG, DDRCLKCH1_CR_DCCCLKCONTROL3_REG, Channel);
    MrcWriteCR (MrcData, Offset, DccClkControl3.Data);
    MRC_DEBUG_MSG (Debug, DebugLevel, "DDRCLKCH%d_DCCCLKCONTROL3: 0x%08X\n", Channel, DccClkControl3.Data);

    Offset = OFFSET_CALC_CH (DDRCLKCH0_CR_DCCCLKCONTROL1_REG, DDRCLKCH1_CR_DCCCLKCONTROL1_REG, Channel);
    MrcWriteCR (MrcData, Offset, DccClkControl1.Data);
    MRC_DEBUG_MSG (Debug, DebugLevel, "DDRCLKCH%d_DCCCLKCONTROL1: 0x%08X\n", Channel, DccClkControl1.Data);

    if (!Inputs->IclA0) {
      Offset = OFFSET_CALC_CH (DDRCLKCH0_CR_DCCCLKTRAINVAL1_REG, DDRCLKCH1_CR_DCCCLKTRAINVAL1_REG, Channel);
      DccClkTrainVal1.Data = MrcReadCR (MrcData, Offset);
      DccClkTrainVal1.Bits.RepDccAipCb = DccAipCb;
      MrcWriteCR (MrcData, Offset, DccClkTrainVal1.Data);
    }
  }

  // Run DCC FSM
  Status = MrcDccRunTest (MrcData);

  if (Status != mrcSuccess) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s DCC CLK Finalization did not complete for Replica\n", gErrString);
    return Status;
  }

  // Capture FSM results
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(MrcChannelExist (Outputs, Channel))) {
      continue;
    }
    Offset = OFFSET_CALC_CH (DDRCLKCH0_CR_DCCCLKTRAINVAL1_REG, DDRCLKCH1_CR_DCCCLKTRAINVAL1_REG, Channel);
    DccClkTrainVal1.Data = MrcReadCR (MrcData, Offset);
    Replica[Channel] = DccClkTrainVal1.Bits.ReplicaShadowDccVal;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%d: Replica = %d\n", Channel, Replica[Channel]);
  } // for Channel

  if (!Inputs->IclA0) {
    // Check if we got any saturated DCC values, and retrain with a different DccAipCb if saturated
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      DccAipCb = 1;
      ReplicaValue = Replica[Channel];
      if (ReplicaValue < DCC_PASS_MIN) {
        DccAipCb = 0;
        Rerun[Channel] = TRUE;
      } else if (ReplicaValue > DCC_PASS_MAX) {
        DccAipCb = 3;
        Rerun[Channel] = TRUE;
      }
      if (Rerun[Channel]) {
        RerunNeeded = TRUE;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Saturated: C%d Replica: %d\n", Channel, ReplicaValue);
        Offset = OFFSET_CALC_CH (DDRCLKCH0_CR_DCCCLKTRAINVAL1_REG, DDRCLKCH1_CR_DCCCLKTRAINVAL1_REG, Channel);
        DccClkTrainVal1.Data = MrcReadCR (MrcData, Offset);
        DccClkTrainVal1.Bits.RepDccAipCb = DccAipCb;
        MrcWriteCR (MrcData, Offset, DccClkTrainVal1.Data);
      }
    } // for Channel
    if (RerunNeeded) {
      // Run DCC FSM again
      Status = MrcDccRunTest (MrcData);
      if (Status != mrcSuccess) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s DCC CLK Finalization did not complete for Replica\n", gErrString);
        return Status;
      }
      // Capture FSM results
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcChannelExist (Outputs, Channel)) {
          continue;
        }
        if (Rerun[Channel]) {
          Offset = OFFSET_CALC_CH (DDRCLKCH0_CR_DCCCLKTRAINVAL1_REG, DDRCLKCH1_CR_DCCCLKTRAINVAL1_REG, Channel);
          DccClkTrainVal1.Data = MrcReadCR (MrcData, Offset);
          ReplicaValue = DccClkTrainVal1.Bits.ReplicaShadowDccVal;
          Replica[Channel] = ReplicaValue;
          Saturated = (ReplicaValue < DCC_PASS_MIN) || (ReplicaValue > DCC_PASS_MAX);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%d Replica: %d %s\n", Channel, ReplicaValue, Saturated ? "- still saturated" : "");
        }
      } // for Channel
    } // if Rerun
  } // if not A0

  // Program the final replica results - only for A0. This happens automatically on B0 and on.
  if (Inputs->IclA0) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcChannelExist (Outputs, Channel))) {
        continue;
      }
      ReplicaValue = Replica[Channel];
      Offset = OFFSET_CALC_CH (DDRCLKCH0_CR_DCCCLKTRAINREPLICA0_REG, DDRCLKCH1_CR_DCCCLKTRAINREPLICA0_REG, Channel);
      DccClkTrainReplica0.Data = MrcReadCR (MrcData, Offset);

      switch (MrcIntData->SaGvPoint) {
        case MrcSaGvPointLow:
          DccClkTrainReplica0.Bits.ReplicaTrain_GVp0 = ReplicaValue;
          break;

        case MrcSaGvPointMid:
          DccClkTrainReplica0.Bits.ReplicaTrain_GVp1 = ReplicaValue;
          break;

        default:
        case MrcSaGvPointHigh:
          DccClkTrainReplica0.Bits.ReplicaTrain_GVp2 = ReplicaValue;
          break;
      }
      MrcWriteCR (MrcData, Offset, DccClkTrainReplica0.Data);

      DccClkTrainReplica0.Bits.ReplicaOffsetPrev = 0;
      MrcWriteCR (MrcData, Offset, DccClkTrainReplica0.Data);
      MRC_DEBUG_MSG (Debug, DebugLevel, "DDRCLKCH%d_DCCCLKTRAINREPLICA0: 0x%x\n", Channel, DccClkTrainReplica0.Data);

      Offset = OFFSET_CALC_CH (DDRCLKCH0_CR_DCCCLKTRAINSTATUS2_REG, DDRCLKCH1_CR_DCCCLKTRAINSTATUS2_REG, Channel);
      DccClkTrainStatus2.Data = MrcReadCR (MrcData, Offset);
      DccClkTrainStatus2.Bits.ReplicaOffset = 0;
      MrcWriteCR (MrcData, Offset, DccClkTrainStatus2.Data);
    } // for Channel
  } // if A0

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DCC CLK Replica End\n\n");
  return Status;
}

/**
  This function will do the final setup of DCC DQS prior to end of SAGV.

  @params[in] MrcData   - Pointer to MRC global data.

  @retval mrcSuccess if no Timeout occurred, otherwise mrcFail.
**/
MrcStatus
MrcDccDqsFinalization (
  IN  MrcParameters * const MrcData
  )
{
  const MRC_FUNCTION  *MrcCall;
  MrcInput          *Inputs;
  MrcOutput         *Outputs;
  MrcDebug          *Debug;
  MrcStatus         Status;
  MrcDebugMsgLevel  DebugLevel;
  UINT32            Offset;
  UINT32            ReplicaValue;
  UINT32            DccAipCb;
  INT64             GetSetVal;
  BOOLEAN           Rerun[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  BOOLEAN           RerunNeeded;
#ifdef MRC_DEBUG_PRINT
  BOOLEAN           Saturated;
#endif
  UINT32            Channel;
  UINT32            Byte;
  DDRDATA0CH0_CR_DCCDATACONTROL0_STRUCT   DccDataControl0;
  DDRDATA0CH0_CR_DCCDATACONTROL1_STRUCT   DccDataControl1;
  DDRDATA0CH0_CR_DCCDATACONTROL3_STRUCT   DccDataControl3;
  DDRDATA0CH0_CR_DCCDATACONTROL4_STRUCT   DccDataControl4;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Status  = mrcSuccess;
  DebugLevel  = (DCC_PRINT) ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nDCC DQS Replica Start\n");

  MrcDccMainFsmControl0 (MrcData, DCC_DATA, DCC_DCO_COMP_OFF);
  MrcDccControlRegsRead (MrcData, FALSE, &DccDataControl0.Data, &DccDataControl1.Data, &DccDataControl3.Data, &DccDataControl4.Data);

  DccDataControl0.Bits.ActiveRanks = 0x1;
  DccDataControl3.Bits.ActiveDccRank0 = 0x200;
  DccDataControl3.Bits.ActiveDccRank1 = 0;
  DccDataControl3.Bits.ActiveDccRank2 = 0;
  DccDataControl4.Bits.ActiveDccRank3 = 0;
  if (!Inputs->IclA0) {
    DccDataControl1.Bits.RepDccAipCb  = 1;
  }

  MrcWriteCrMulticast (MrcData, DDRDATA_CR_DCCDATACONTROL0_REG, DccDataControl0.Data);
  MrcWriteCrMulticast (MrcData, DDRDATA_CR_DCCDATACONTROL1_REG, DccDataControl1.Data);
  MrcWriteCrMulticast (MrcData, DDRDATA_CR_DCCDATACONTROL3_REG, DccDataControl3.Data);
  MrcWriteCrMulticast (MrcData, DDRDATA_CR_DCCDATACONTROL4_REG, DccDataControl4.Data);
  MRC_DEBUG_MSG (Debug, DebugLevel, "DDRDATA_DCCDATACONTROL0: 0x%x\n", DccDataControl0.Data);
  MRC_DEBUG_MSG (Debug, DebugLevel, "DDRDATA_DCCDATACONTROL1: 0x%x\n", DccDataControl1.Data);
  MRC_DEBUG_MSG (Debug, DebugLevel, "DDRDATA_DCCDATACONTROL3: 0x%x\n", DccDataControl3.Data);
  MRC_DEBUG_MSG (Debug, DebugLevel, "DDRDATA_DCCDATACONTROL4: 0x%x\n", DccDataControl4.Data);

  // @todo If (DT && Rank0 not populated && Rank2 populated) -->Set DdrCrTxTrainRank0.txdqsdelay = DdrCrTxTrainRank2.txdqsdelay

  // Run DCC FSM
  Status = MrcDccRunTest (MrcData);

  if (Status != mrcSuccess) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s DCC DQS Finalization did not complete for Replica\n", gErrString);
    return Status;
  }

  if (!Inputs->IclA0) {
    // Check if we got any saturated DCC values, and retrain with a different DccAipCb if saturated
    MrcCall->MrcSetMem ((UINT8 *) &Rerun, sizeof (Rerun), 0);
    RerunNeeded = FALSE;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        DccAipCb = 1;
        MrcGetSetDdrIoGroupStrobe (MrcData, Channel, 0, Byte, GsmIocDccDqsReplica, ReadNoCache, &GetSetVal);
        ReplicaValue = (UINT32) GetSetVal;
        if (ReplicaValue < DCC_PASS_MIN) {
          DccAipCb = 0;
          Rerun[Channel][Byte] = TRUE;
        } else if (ReplicaValue > DCC_PASS_MAX) {
          DccAipCb = 3;
          Rerun[Channel][Byte] = TRUE;
        }
        if (Rerun[Channel][Byte]) {
          RerunNeeded = TRUE;
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Saturated: C%d B%d Replica: %d\n", Channel, Byte, ReplicaValue);
          DccDataControl1.Bits.RepDccAipCb = DccAipCb;
          Offset = DDRDATA0CH0_CR_DCCDATACONTROL1_REG +
                  (DDRDATA0CH1_CR_DCCDATACONTROL1_REG - DDRDATA0CH0_CR_DCCDATACONTROL1_REG) * Channel +
                  (DDRDATA1CH0_CR_DCCDATACONTROL1_REG - DDRDATA0CH0_CR_DCCDATACONTROL1_REG) * Byte;
          MrcWriteCR (MrcData, Offset, DccDataControl1.Data);
        }
      } // for Byte
    } // for Channel
    if (RerunNeeded) {
      // Run DCC FSM again - replica results are captured automatically
      Status = MrcDccRunTest (MrcData);
      if (Status != mrcSuccess) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s DCC CLK Finalization did not complete for Replica\n", gErrString);
        return Status;
      }
#ifdef MRC_DEBUG_PRINT
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcChannelExist (Outputs, Channel)) {
          continue;
        }
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (Rerun[Channel][Byte]) {
            MrcGetSetDdrIoGroupStrobe (MrcData, Channel, 0, Byte, GsmIocDccDqsReplica, ReadNoCache, &GetSetVal);
            ReplicaValue = (UINT32) GetSetVal;
            Saturated = (ReplicaValue < DCC_PASS_MIN) || (ReplicaValue > DCC_PASS_MAX);
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%d B%d Replica: %d %s\n", Channel, Byte, ReplicaValue, Saturated ? "- still saturated" : "");
          }
        }
      } // for Channel
#endif // MRC_DEBUG_PRINT
    } // if Rerun
  } // if not A0


#ifdef MRC_DEBUG_PRINT
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    Offset = OFFSET_CALC_CH (DDRDATA0CH0_CR_DCCDATACONTROL4_REG, DDRDATA0CH1_CR_DCCDATACONTROL4_REG, Channel);
    MRC_DEBUG_MSG (Debug, DebugLevel, "DDRDATA_CR_DCCDATACONTROL4: 0x%x\n", MrcReadCR (MrcData, Offset));
    Offset = OFFSET_CALC_CH (DDRDATA0CH0_CR_DCCDATACONTROL5_REG, DDRDATA0CH1_CR_DCCDATACONTROL5_REG, Channel);
    MRC_DEBUG_MSG (Debug, DebugLevel, "DDRDATA_CR_DCCDATACONTROL5: 0x%x\n", MrcReadCR (MrcData, Offset));

    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      Offset = DDRDATA0CH0_CR_DCCDATATRAINREPLICA0_REG +
        ((DDRDATA0CH1_CR_DCCDATATRAINREPLICA0_REG - DDRDATA0CH0_CR_DCCDATATRAINREPLICA0_REG) * Channel) +
        ((DDRDATA1CH0_CR_DCCDATATRAINREPLICA0_REG - DDRDATA0CH0_CR_DCCDATATRAINREPLICA0_REG) * Byte);
      MRC_DEBUG_MSG (Debug, DebugLevel, "DDRDATA%uCH%u_CR_DCCDATATRAINREPLICA0: 0x%x\n", Byte, Channel, MrcReadCR (MrcData, Offset));
      Offset = DDRDATA0CH0_CR_DCCDATATRAINSTATUS0_REG +
        ((DDRDATA0CH1_CR_DCCDATATRAINSTATUS0_REG - DDRDATA0CH0_CR_DCCDATATRAINSTATUS0_REG) * Channel) +
        ((DDRDATA1CH0_CR_DCCDATATRAINSTATUS0_REG - DDRDATA0CH0_CR_DCCDATATRAINSTATUS0_REG) * Byte);
      MRC_DEBUG_MSG (Debug, DebugLevel, "DDRDATA%uCH%u_CR_DCCDATATRAINSTATUS0: 0x%x\n", Byte, Channel, MrcReadCR (MrcData, Offset));
      Offset = DDRDATA0CH0_CR_DCCDATATRAINSTATUS1_REG +
        ((DDRDATA0CH1_CR_DCCDATATRAINSTATUS1_REG - DDRDATA0CH0_CR_DCCDATATRAINSTATUS1_REG) * Channel) +
        ((DDRDATA1CH0_CR_DCCDATATRAINSTATUS1_REG - DDRDATA0CH0_CR_DCCDATATRAINSTATUS1_REG) * Byte);
      MRC_DEBUG_MSG (Debug, DebugLevel, "DDRDATA%uCH%u_CR_DCCDATATRAINSTATUS1: 0x%x\n", Byte, Channel, MrcReadCR (MrcData, Offset));
      Offset = DDRDATA0CH0_CR_DCCDATATRAINSTATUS2_REG +
        ((DDRDATA0CH1_CR_DCCDATATRAINSTATUS2_REG - DDRDATA0CH0_CR_DCCDATATRAINSTATUS2_REG) * Channel) +
        ((DDRDATA1CH0_CR_DCCDATATRAINSTATUS2_REG - DDRDATA0CH0_CR_DCCDATATRAINSTATUS2_REG) * Byte);
      MRC_DEBUG_MSG (Debug, DebugLevel, "DDRDATA%uCH%u_CR_DCCDATATRAINSTATUS2: 0x%x\n", Byte, Channel, MrcReadCR (MrcData, Offset));
      Offset = DDRDATA0CH0_CR_DCCDATATRAINERRSTATUSRANK0_REG +
        ((DDRDATA0CH1_CR_DCCDATATRAINERRSTATUSRANK0_REG - DDRDATA0CH0_CR_DCCDATATRAINERRSTATUSRANK0_REG) * Channel) +
        ((DDRDATA1CH0_CR_DCCDATATRAINERRSTATUSRANK0_REG - DDRDATA0CH0_CR_DCCDATATRAINERRSTATUSRANK0_REG) * Byte);
      MRC_DEBUG_MSG (Debug, DebugLevel, "DDRDATA%uCH%u_CR_DCCDATATRAINERRSTATUSRANK0: 0x%x\n", Byte, Channel, MrcReadCR (MrcData, Offset));
    }
  }
#endif // MRC_DEBUG_PRINT

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DCC DQS Replica End\n\n");
  return Status;
}

#ifdef MRC_DEBUG_PRINT
/**
  This function will print the Look Up Table results for CLK and/or Tx DQS

  @params[in] MrcData   - Pointer to MRC global data.
  @params[in] ClkDcc    - TRUE to print CLK DCC LUT, otherwise FALSE.
  @params[in] DqsDcc    - TRUE to print TxDqs DCC LUT, otherwise FALSE.
**/
void
MrcDccResultsDebugPrint (
  IN  MrcParameters * const MrcData,
  IN  BOOLEAN               ClkDcc,
  IN  BOOLEAN               DqsDcc
  )
{
  MrcOutput     *Outputs;
  MrcDebug      *Debug;
  MrcIntOutput  *MrcIntData;
  UINT32        Channel;
  UINT32        Byte;
  UINT32        Rank;
  UINT32        MaxByte;
  UINT32        Pi;

  Outputs = &MrcData->Outputs;
  Debug = &Outputs->Debug;
  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));

  if (ClkDcc) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CLK DCC\n");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcChannelExist (Outputs, Channel))) {
        continue;
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d\n", Channel);
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
          continue;
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " Rank %d", Rank);
        for (Pi = 0; Pi < MAX_DCC_CLOCK_PI; Pi++) {
          if ((Pi % 8) == 0) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
          }
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", MrcIntData->ClkDcc[Channel][Rank][Pi]);
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n DccAipCb:");
        for (Pi = 0; Pi < MAX_DCC_CLOCK_PI; Pi++) {
          if ((Pi % 8) == 0) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
          }
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", MrcIntData->ClkDccAipCb[Channel][Rank][Pi]);
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
      }
    }
  }
  if (DqsDcc) {
    MaxByte = Outputs->SdramCount;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DQS DCC\n");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(MrcChannelExist (Outputs, Channel))) {
        continue;
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d\n", Channel);
      for (Byte = 0; Byte < MaxByte; Byte++) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " Byte %d", Byte);
        for (Pi = 0; Pi < MAX_DCC_TX_DQS_DQ_PI; Pi++) {
          if ((Pi % 8) == 0) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
          }
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", MrcIntData->DqsDcc[Channel][Byte][Pi]);
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n DqsDccAipCb:");
        for (Pi = 0; Pi < MAX_DCC_TX_DQS_DQ_PI; Pi++) {
          if ((Pi % 8) == 0) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
          }
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", MrcIntData->DqsDccAipCb[Channel][Byte][Pi]);
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
      }
    }
  }
}
#endif // MRC_DEBUG_PRINT
#endif // if 0

