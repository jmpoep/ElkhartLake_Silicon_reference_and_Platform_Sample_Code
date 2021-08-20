/** @file
  This file include all the common tolls for the mrc algo

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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
// Include files
#include "MrcCommon.h"
#include "MrcDdrCommon.h"
#include "MrcReadDqDqs.h"
#include "MrcMaintenance.h"
#include "MrcCpgcApi.h"
#include "Cpgc20.h"
#include "Cpgc20Patterns.h"
#include "Cpgc20TestCtl.h"
#include "MrcMemoryApi.h"
#include "MrcCpgcOffsets.h"
#include "MrcLpddr4.h"
#include "MrcDdr4.h"
#include "MrcGears.h"
#include "MrcMcConfiguration.h"


/// Local Defines
#define MRC_CHNG_MAR_GRP_NUM  (2)
#define MRC_1D_ERROR_LEN      ((192 * 2) + 1)


#define MRC_EXIT_VALUE (0xFF)

#ifdef MRC_DEBUG_PRINT
const char  CcdString[] = "Controller, Channel, Dimm";
const char  RcvEnDelayString[] = "RcvEnDelay";
const char  WrVDelayString[] = "WriteVoltage";
const char  RdVDelayString[] = "ReadVoltage";
const char  DqsDelayString[] = "DqsDelay";
const char  CmdVDelayString[] = "CmdVoltage";
#endif
///
/// Global Constant
///

/// Bank Array Function parameter is a constant, but due to compiler type mismatch
/// with GetSet function, cannot define as constant.
/// Set the bank mapping so that bank groups are toggled before banks (we will use logical banks 0 and 1 only).
/// Only update the first two Banks in the mapping.
/// Logical Bank:         0  1  2 ... 15
///                       --------------
/// Physical Bank Group:  0  1  X      X
/// Physical Bank:        0  0  X      X
MRC_BG_BANK_PAIR Ddr4RdMprBankL2p[2] = {{0, 0}, {1, 0}};

/// Set the bank mapping so that bank groups are toggled before banks (can use logical banks 0 to 7).
/// 8 banks case (x8 or x16):
/// Logical Bank:         0  1  2  3  4  5  6  7
///                       ----------------------
/// Physical Bank:        0  0  1  1  2  2  3  3
/// Physical Bank Group:  0  1  0  1  0  1  0  1
MRC_BG_BANK_PAIR Ddr4x16BankMapB2B[MAX_DDR4_x16_BANKS] = {
  {0,0}, {1,0}, {0,1}, {1,1}, {0,2}, {1,2}, {0,3}, {1,3}
};

/// Set the bank mapping so that bank groups are toggled before banks (can use logical banks 0 to 15).
/// 16 banks case (x8):
/// Logical Bank:         0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
///                       -----------------------------------------------
/// Physical Bank:        0  0  0  0  1  1  1  1  2  2  2  2  3  3  3  3
/// Physical Bank Group:  0  1  2  3  0  1  2  3  0  1  2  3  0  1  2  3
MRC_BG_BANK_PAIR Ddr4x8BankMapB2B[MAX_DDR4_x8_BANKS] = {
  {0,0}, {1,0}, {2,0}, {3,0}, {0,1}, {1,1}, {2,1}, {3,1},
  {0,2}, {1,2}, {2,2}, {3,2}, {0,3}, {1,3}, {2,3}, {3,3}
};

/**
  Verify that the indicated socket is present and enabled.

  @param[in] MrcData    - Pointer to the MRC global data area.
  @param[in] Socket     - Zero based CPU socket number.

  @retval Success if present and enabled, otherwise SocketNotSupported.
**/
MrcStatus
IsSocketPresent (
  const MrcParameters * const MrcData,
  const UINT32                Socket
  )
{
  return ((Socket < MAX_CPU_SOCKETS) ? mrcSuccess : mrcSocketNotSupported);
}

/**
  Verify that the indicated controller is present and enabled.

  @param[in] MrcData    - Pointer to the MRC global data area.
  @param[in] Socket     - Zero based CPU socket number.
  @param[in] Controller - Zero based memory controller number.

  @retval Success if present and enabled, otherwise ControllerNotSupported.
**/
MrcStatus
IsControllerPresent (
  const MrcParameters * const MrcData,
  const UINT32                Socket,
  const UINT32                Controller
  )
{
  MrcStatus Status;

  Status = IsSocketPresent (MrcData, Socket);
  if (Status == mrcSuccess) {
    return (((Controller < MAX_CONTROLLERS) &&
    (MrcData->Outputs.Controller[Controller].Status == CONTROLLER_PRESENT)) ?
            mrcSuccess : mrcControllerNotSupported);
  }
  return (Status);
}

/**
  Verify that the indicated channel is present and enabled.

  @param[in] MrcData    - Pointer to the MRC global data area.
  @param[in] Socket     - Zero based CPU socket number.
  @param[in] Controller - Zero based memory controller number.
  @param[in] Channel    - Zero based memory channel number.

  @retval Success if present and enabled, otherwise ChannelNotSupported.
**/
MrcStatus
IsChannelPresent (
  const MrcParameters * const MrcData,
  const UINT32                Socket,
  const UINT32                Controller,
  const UINT32                Channel
  )
{
  MrcStatus Status;

  Status = IsControllerPresent (MrcData, Socket, Controller);
  if (Status == mrcSuccess) {
    return (((Channel < MAX_CHANNEL) &&
    (MrcData->Outputs.Controller[Controller].Channel[Channel].Status == CHANNEL_PRESENT)) ?
            mrcSuccess : mrcChannelNotSupport);
  }
  return (Status);
}

/**
  Verify that the indicated DIMM is present and enabled.

  @param[in] MrcData    - Pointer to the MRC global data area.
  @param[in] Socket     - Zero based CPU socket number.
  @param[in] Controller - Zero based memory controller number.
  @param[in] Channel    - Zero based memory channel number.
  @param[in] Dimm       - Zero based memory DIMM number.

  @retval Success if present and enabled, otherwise DimmNotSupported.
**/
MrcStatus
IsDimmPresent (
  const MrcParameters * const MrcData,
  const UINT32                Socket,
  const UINT32                Controller,
  const UINT32                Channel,
  const UINT32                Dimm
  )
{
  MrcStatus Status;

  Status = IsChannelPresent (MrcData, Socket, Controller, Channel);
  if (Status == mrcSuccess) {
    return (((Dimm < MAX_DIMMS_IN_CHANNEL) &&
    (MrcData->Outputs.Controller[Controller].Channel[Channel].Dimm[Dimm].Status == DIMM_PRESENT)) ?
            mrcSuccess : mrcDimmNotSupport);
  }
  return (Status);
}

/**
  Verify that the indicated rank is present and enabled.

  @param[in] MrcData    - Pointer to the MRC global data area.
  @param[in] Socket     - Zero based CPU socket number.
  @param[in] Controller - Zero based memory controller number.
  @param[in] Channel    - Zero based memory channel number.
  @param[in] Dimm       - Zero based memory DIMM number.
  @param[in] Rank       - Zero based memory rank number in the DIMM.

  @retval Success if present and enabled, otherwise RankNotSupported.
**/
MrcStatus
IsRankPresent (
  const MrcParameters * const MrcData,
  const UINT32                Socket,
  const UINT32                Controller,
  const UINT32                Channel,
  const UINT32                Dimm,
  const UINT32                Rank
  )
{
  MrcStatus Status;

  Status = IsDimmPresent (MrcData, Socket, Controller, Channel, Dimm);
  if (Status == mrcSuccess) {
    return (((Rank < MAX_RANK_IN_DIMM) &&
             (((UINT32) MrcData->Outputs.Controller[Controller].Channel[Channel].Dimm[Dimm].RankInDimm - 1) >= Rank)) ?
             mrcSuccess : mrcRankNotSupported);
  }
  return (Status);
}

/**
  Return the rank mask in channel if rank exist exist.

  @param[in] MrcData - Pointer to MRC global data.
  @param[in] Rank    - Rank to check.
  @param[in] Channel - Channel to work on.

  @retval Bit mask of Rank requested if the Rank exists in the system.
**/
UINT8
MrcRankInChannelExist (
  IN MrcParameters *const MrcData,
  IN const UINT32         Rank,
  IN const UINT32         Channel
  )
{
  return (((Rank < MAX_RANK_IN_CHANNEL) && (Channel < MAX_CHANNEL)) ? ((MRC_BIT0 << Rank) & MrcData->Outputs.Controller[0].Channel[Channel].ValidRankBitMask) : 0);
}

/**
  Checks if a given sub-channel is populated in a given channel

  @param[in] MrcData    - Pointer to MRC global data.
  @param[in] Channel    - Channel to work on.
  @param[in] SubChannel - Sub-Channel to work on.

  @retval TRUE if exists, FALSE otherwise.
**/
BOOLEAN
MrcSubChannelExist (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel,
  IN const UINT32         SubChannel
  )
{
  MrcOutput     *Outputs;
  MrcChannelOut *ChannelOut;

  Outputs     = &MrcData->Outputs;
  ChannelOut  = &Outputs->Controller[0].Channel[Channel];

  if ((SubChannel == 0) || !Outputs->EnhancedChannelMode) {
    // If channel is present, then subch 0 is always present
    // In x64 channel mode both subch are present
    return (ChannelOut->Status == CHANNEL_PRESENT);
  } else {
    return (Outputs->EnhancedChannelMode && ((1 << SubChannel) & ChannelOut->ValidSubChBitMask));
  }
}

/**
  This function checks if the requested byte in the channel exists.

  @param[in]  MrcData - Pointer to MRC global data.
  @param[in]  Channel - Channel to check.
  @param[in]  Byte    - Byte to check.

  @retval BOOLEAN - TRUE if exists, FALSE otherwise.
**/
BOOLEAN
MrcByteInChannelExist (
  IN  MrcParameters *const  MrcData,
  IN  const UINT32          Channel,
  IN  const UINT32          Byte
  )
{
  MrcOutput     *Outputs;
  MrcChannelOut *ChannelOut;

  if (Channel < MAX_CHANNEL) {
    Outputs     = &MrcData->Outputs;
    ChannelOut  = &Outputs->Controller[0].Channel[Channel];
    if ( ((1 << Byte) & ChannelOut->ValidByteMask) != 0 ) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
  Return the number of ranks in specific dimm.

  @param[in] MrcData - Pointer to MRC global data.
  @param[in] Channel - Channel to work on.
  @param[in] Dimm    - Dimm in channel to return.

  @retval The number of ranks in the dimm.
**/
UINT8
MrcGetRankInDimm (
  IN MrcParameters *const MrcData,
  IN const UINT8          Dimm,
  IN const UINT8          Channel
  )
{
  return MrcData->Outputs.Controller[0].Channel[Channel].Dimm[Dimm].RankInDimm;
}

/**
  Returns whether Channel is or is not present.

  @param[in] Outputs - Pointer to MRC global Output data.
  @param[in] Channel - Channel to test.

  @retval TRUE  - if there is at least one enabled DIMM in the channel.
  @retval FALSE - if there are no enabled DIMMs in the channel.
**/
BOOLEAN
MrcChannelExist (
  IN const MrcOutput *const Outputs,
  IN const UINT32           Channel
  )
{
  if (Channel < MAX_CHANNEL) {
    if (Outputs->Controller[0].Channel[Channel].Status == CHANNEL_PRESENT) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
  This function disable channel parameters.
  After this function the MRC don't use with the channel.

  @param[in] MrcData           - Include all MRC global data.
  @param[in] ChannelToDisable  - Channel to disable.
  @param[in] SkipDimmCapacity  - Switch to skip setting the DimmCapacity to 0 for the dimms in the channel disabled.

  @retval Nothing
**/
void
MrcChannelDisable (
  IN MrcParameters *const MrcData,
  IN const UINT8          ChannelToDisable,
  IN const UINT8          SkipDimmCapacity
  )
{
  MrcChannelOut *ChannelOut;
  MrcDimmOut    *DimmOut;
  UINT32        Dimm;

  ChannelOut = &MrcData->Outputs.Controller[0].Channel[ChannelToDisable];
  if (ChannelOut->Status == CHANNEL_PRESENT) {
    ChannelOut->Status            = CHANNEL_DISABLED;
    ChannelOut->ValidRankBitMask  = 0;
    for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
      DimmOut = &ChannelOut->Dimm[Dimm];
      if (DimmOut->Status == DIMM_PRESENT) {
        DimmOut->Status     = DIMM_DISABLED;
        DimmOut->RankInDimm = 0;
        if (!SkipDimmCapacity) {
          DimmOut->DimmCapacity = 0;
        }
      }
    }
  }
}

/**
  This function implements the flow to properly switch MC PLL during run time.

  @params[in] MrcData     - Pointer to MRC global data.
  @params[in] NewFreq     - The new frequency to lock MC PLL.
  @params[in] DebugPrint  - Boolean parameter to enable/disable debug messages for the callee.

  @retval MrcStatus - mrcSuccess if frequency is updated properly, otherwise an error status.
**/
MrcStatus
MrcFrequencySwitch (
  IN  MrcParameters *const  MrcData,
  IN  MrcFrequency          NewFreq,
  IN  BOOLEAN               DebugPrint
  )
{
  MrcStatus Status;

  MrcData->Outputs.Frequency = NewFreq;
  Status = McFrequencySet (MrcData, DebugPrint);
  ForceRcomp (MrcData);

  return Status;
}

/**
  Convert the given frequency and reference clock to a clock ratio.

  @param[in] MrcData   - Pointer to MRC global data.
  @param[in] Frequency - The memory frequency.
  @param[in] RefClk    - The memory reference clock.
  @param[in] BClk      - The base system reference clock.

  @retval Returns the memory clock ratio.
**/
MrcClockRatio
MrcFrequencyToRatio (
  IN MrcParameters *const  MrcData,
  IN const MrcFrequency    Frequency,
  IN const MrcRefClkSelect RefClk,
  IN const MrcBClkRef      BClk
  )
{
  const MRC_FUNCTION *MrcCall;
  UINT64 Value;
  UINT64 FreqValue;
  UINT32 RefClkValue;
  UINT32 BClkValue;

  MrcCall     = MrcData->Inputs.Call.Func;
  BClkValue   = (BClk == 0) ? (BCLK_DEFAULT / 100000) : (BClk / 100000);
  RefClkValue = (RefClk == MRC_REF_CLOCK_100) ? 100000 : 133333;
  FreqValue   = MrcCall->MrcMultU64x32 (Frequency, 1000000000ULL);
  Value       = MrcCall->MrcDivU64x64 (FreqValue, (RefClkValue * BClkValue), NULL);
  Value       = ((UINT32) Value + 500) / 1000;
  return ((MrcClockRatio) Value);
}

/**
  Convert the given ratio and reference clocks to a memory frequency.

  @param[in] MrcData - Pointer to MRC global data.
  @param[in] Ratio   - The memory ratio.
  @param[in] RefClk  - The memory reference clock.
  @param[in] BClk    - The base system reference clock.

  @retval Returns the memory frequency.
**/
MrcFrequency
MrcRatioToFrequency (
  IN MrcParameters *const  MrcData,
  IN const MrcClockRatio   Ratio,
  IN const MrcRefClkSelect RefClk,
  IN const MrcBClkRef      BClk
  )
{
  const MrcInput     *Inputs;
  const MRC_FUNCTION *MrcCall;
  MrcClockRatio      LocalRatio;
  UINT64 Value;
  UINT32 BClkValue;
  UINT32 RefClkValue;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;

  LocalRatio  = Ratio;
  BClkValue   = (BClk == 0) ? BCLK_DEFAULT : BClk;
  RefClkValue = (RefClk == MRC_REF_CLOCK_100) ? 100000000 : 133333333;
  Value = BClkValue;
  Value = MrcCall->MrcMultU64x32 (Value, LocalRatio);
  Value = MrcCall->MrcMultU64x32 (Value, RefClkValue);
  Value += 50000000000000ULL;
  Value = MrcCall->MrcDivU64x64 (Value, 100000000000000ULL, NULL);
  return ((MrcFrequency) Value);
}

/**
  Convert the given ratio and reference clocks to a memory clock.

  @param[in] Ratio  - The memory ratio.
  @param[in] RefClk - The memory reference clock.
  @param[in] BClk   - The base system reference clock.

  @retval Returns the memory clock in femtoseconds.
**/
UINT32
MrcRatioToClock (
  IN MrcParameters *const  MrcData,
  IN const MrcClockRatio   Ratio,
  IN const MrcRefClkSelect RefClk,
  IN const MrcBClkRef      BClk
  )
{
  const MrcInput     *Inputs;
  const MRC_FUNCTION *MrcCall;
  UINT32 BClkValue;
  UINT32 RefClkValue;
  UINT32 Factor;
  UINT64 Value;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;

  BClkValue   = (BClk == 0) ? 100000000UL : BClk;
  Factor      = BClkValue / 100000UL;
  RefClkValue = (RefClk == MRC_REF_CLOCK_100) ? 500000000UL : 666666667UL;
  Value       = MrcCall->MrcMultU64x32 (Factor, RefClkValue);
  Value       = MrcCall->MrcMultU64x32 (Value, Ratio);
  return ((Value == 0) ? 0 : (UINT32) MrcCall->MrcDivU64x64 (10000000000000000000ULL, Value, NULL));
}

/**
  This function determines the number of PI ticks required to cover the delay requested.
  This function will ceiling the result such that the PI tick delay may be greater
  than the requested time.

  @param[in]  MrcData - Pointer to MRC global data.
  @param[in]  TimeFs  - The delay in Femtoseconds to convert to PI ticks.

  @retval UINT32 - The number of PI ticks to reach the delay requested.
**/
UINT32
MrcPicoSec2PiTick (
  IN  MrcParameters *const  MrcData,
  IN  const UINT32          TimeFs
  )
{
  UINT32  DataRateFs;
  UINT32  PiTickFs;
  UINT32  PiCount;

  DataRateFs = MrcData->Outputs.MemoryClock / 2;

  // Pi Tick is 1/64th a Data Rate UI.
  PiTickFs  = UDIVIDEROUND (DataRateFs, 64);
  PiCount   = DIVIDECEIL (TimeFs, PiTickFs);

  return PiCount;
}

/**
  This function return the DIMM number according to the rank number.

  @param[in] Rank - The requested rank.

  @retval The DIMM number.
**/
UINT8
MrcGetDimmFromRank (
  IN const UINT8 Rank
  )
{
  UINT8 Dimm;

  if (Rank == rRank0 || Rank == rRank1) {
    Dimm = dDIMM0;
  } else {
    Dimm = dDIMM1;
  }

  return Dimm;
}

#ifdef MRC_DEBUG_PRINT
/**
  Decode the reason for MC PLL lock failure using PCODE Mailbox.

  @param[in] MrcData    - Include all MRC global data.
**/
void
MrcDecodeFrequencyError (
  IN MrcParameters *const MrcData
  )
{
  const MRC_FUNCTION  *MrcCall;
  MrcDebug            *Debug;
  UINT32              MailBoxData;
  UINT32              MailboxStatus;
  char                *Str;

  MrcCall = MrcData->Inputs.Call.Func;
  Debug   = &MrcData->Outputs.Debug;

  // Read the error PCode command READ_BIOS_MC_REQ_ERROR for DDR checks where the ratio is not locked.
  MailBoxData   = 0;
  MailboxStatus = 0;
  MrcCall->MrcCpuMailboxRead (
    MAILBOX_TYPE_PCODE,
    MAILBOX_BIOS_CMD_READ_BIOS_MC_REQ_ERROR,
    &MailBoxData,
    &MailboxStatus
  );
  if (MailboxStatus == PCODE_MAILBOX_CC_SUCCESS) {  // Command returns allways success
    if (MailBoxData == MC_REQ_ERROR_DDR_CHECKS_DDR_CHECKS_PASSED) {
      Str = "DDR Checks Passed";
    } else if (MailBoxData == MC_REQ_ERROR_DDR_CHECKS_ILLEGAL_BASE_FREQ) {
      Str = "Illegal Base Frequency - Request type in MCHBAR_PCU_REQ_TYPE Is Undefined";
    } else if (MailBoxData == MC_REQ_ERROR_DDR_CHECKS_FAILED_LT_CONDITIONS) {
      Str = "LT Conditions Not Met";
    } else if (MailBoxData == MC_REQ_ERROR_DDR_CHECKS_DDR_FREQ_BELOW_MIN) {
      Str = "Frequency Below Minimum";
    } else if (MailBoxData == MC_REQ_ERROR_DDR_CHECKS_DDR_FREQ_ABOVE_OC_LIMIT) {
      Str = "Frequency Above OC Limit";
    } else if (MailBoxData == MC_REQ_ERROR_DDR_CHECKS_DDR_FREQ_ABOVE_DMFC_LIMIT) {
      Str = "Frequency above DMFC limit";
    } else if (MailBoxData == MC_REQ_ERROR_DDR_CHECKS_DDR_FREQ_100_REF_IS_DISABLED) {
      Str = "Refclk 100Mhz is Disabled";
    } else {
      Str = "Undefined PCode Error Status";
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s %s\n", gErrString, Str);
  }
}
#endif // MRC_DEBUG_PRINT

/**
  This function sets the memory frequency.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] DebugPrint - Enable/disable debug printing

  @retval mrcSuccess on success, mrcFrequencyError on error.
**/
MrcStatus
McFrequencySet (
  IN MrcParameters *const MrcData,
  IN BOOLEAN              DebugPrint
  )
{
  const MRC_FUNCTION  *MrcCall;
  MrcDebug            *Debug;
  MrcDebugMsgLevel    DebugLevel;
  const MrcInput      *Inputs;
  MrcOutput           *Outputs;
  MrcClockRatio       Ratio;
  MrcRefClkSelect     RefClk;
  MrcStatus           Status;
  UINT32              MemoryClock;
  BOOLEAN             Gear2;
  UINT64              Timeout;
  MC_BIOS_REQ_PCU_STRUCT    McBiosReq;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  DebugLevel  = DebugPrint ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;
  Status      = mrcSuccess;
  Gear2 = Outputs->Gear2;

  if ((Inputs->MemoryProfile == USER_PROFILE) && (Inputs->Ratio > 0) && (Inputs->BootMode == bmCold)) {
    Outputs->Ratio = Inputs->Ratio;
  } else {
    Outputs->Ratio = MrcFrequencyToRatio (MrcData, Outputs->Frequency, Outputs->RefClk, Inputs->BClkFrequency);
  }

  if ((Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) && Outputs->Frequency == f1067) {
    // Use Gear1 when switching to 1067 for LP4 JEDEC reset and ECT, even if current point is Gear2
    Gear2 = FALSE;
    Outputs->Ratio = 8; // In case USER_PROFILE is used with a custom ratio
  }

  McBiosReq.Data           = 0;
  McBiosReq.Bits.REQ_DATA = Gear2 ? (Outputs->Ratio / 2) : Outputs->Ratio;
  McBiosReq.Bits.REQ_TYPE  = (Outputs->RefClk == MRC_REF_CLOCK_133) ? 0 : 1;
  McBiosReq.Bits.GEAR_TYPE = Gear2; // 0: Gear1, 1: Gear2
  McBiosReq.Bits.RUN_BUSY  = 1;
  MrcWriteCR (MrcData, MC_BIOS_REQ_PCU_REG, McBiosReq.Data);
  MRC_DEBUG_MSG (Debug, DebugLevel, "Attempting value = 0x%x - Pll busy wait ", McBiosReq.Data);

  Timeout = MrcCall->MrcGetCpuTime (MrcData) + 10000;  // 10 sec timeout
  while (McBiosReq.Bits.RUN_BUSY && (MrcCall->MrcGetCpuTime (MrcData) < Timeout)) {
    McBiosReq.Data = MrcReadCR (MrcData, MC_BIOS_REQ_PCU_REG);
  }

  if (McBiosReq.Bits.RUN_BUSY) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "- TIMEOUT. DDR frequency Update FAILED!\n");
#ifdef MRC_DEBUG_PRINT
    MrcDecodeFrequencyError (MrcData);
#endif
    return mrcFrequencyError;
  } else {
    MRC_DEBUG_MSG (Debug, DebugLevel, "- done\n");
  }

  Outputs->Frequency = MrcGetCurrentMemoryFrequency (MrcData, &MemoryClock, &Ratio, &RefClk);
  MRC_DEBUG_MSG (
    Debug,
    DebugLevel,
    "Requested/actual ratio %u/%u, Frequency=%u, Gear%u",
    Outputs->Ratio,
    Ratio,
    Outputs->Frequency,
    Gear2 ? 2 : 1
    );

  MRC_DEBUG_MSG (
    Debug,
    DebugLevel,
    ", BClk=%uHz RefClk=%uMHz, tCK=%ufs\n",
    Inputs->BClkFrequency,
    (RefClk == MRC_REF_CLOCK_133) ? 133 : 100,
    MemoryClock
    );

  if (Ratio != Outputs->Ratio) {
    if (Ratio == 0) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ERROR: MC PLL did not lock.\n");
#ifdef MRC_DEBUG_PRINT
      MrcDecodeFrequencyError (MrcData);
#endif
    }
    return mrcFrequencyError;
  }

  // We use the gear of the high frequency here, even if we are locking at 1067 for LP4
  Outputs->tCKps  = (UINT16) (Outputs->MemoryClock / 1000);     // Memory clock period in pS (external bus clock)
  Outputs->UIps   = Outputs->tCKps / 2;                         // Data Unit Interval period in pS (half of external bus clock)
  Outputs->Qclkps = Outputs->tCKps / (Outputs->Gear2 ? 1 : 2);  // QCLK period in pS, this is internal MC/DDRIO clock which is impacted by Gear1/2
  Outputs->Dclkps = Outputs->tCKps * (Outputs->Gear2 ? 2 : 1);  // DCLK period in pS, this is internal MC/DDRIO clock which is impacted by Gear1/2

  MRC_DEBUG_MSG (
    Debug,
    DebugLevel,
    "tCKps=%u, UIps=%u, Dclkps=%u, Qclkps=%u\n",
    Outputs->tCKps, Outputs->UIps, Outputs->Dclkps, Outputs->Qclkps
    );

  if (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) {
    // Update Gear2 mode in MC/DDRIO, in LP4 we switch to Gear1 when going down to 1067.
    MrcSetGear2 (MrcData, Gear2);
  }

  return Status;
}

/**
  Returns the extrapolated margin to a fixed # of errors (logT)
  vrefpass is 10x the first passing margin (with no errors) (10x used for int math)
  Errors at vrefpass/10+1 = log1
  Errors at vrefpass/10+2 = logT

  @param[in]      vrefpass      - 10x the first pass margin (w/no errors) (10x used for int match)
  @param[in]      errLog_1      - Errors at vrefpass/10+1
  @param[in]      errLog_2      - Errors at vrefpass/10+2
  @param[in]      errLog_Target - Error target determines extrapolation vs interpolation
  @param[in, out] *berStats     - Used to track interpolation vs extrapolation or if the slope is non-monotonic.
                                  NOTE: target would be Interpolation only

  @retval Interpolated/Extrapolated vref with the scale increased by 10.
**/
UINT32
interpolateVref (
  IN     UINT32  vrefpass,
  IN     UINT32  errLog_1,
  IN     UINT32  errLog_2,
  IN     UINT32  errLog_Target,
  IN OUT UINT32  *berStats
  )
{
  UINT32 vref;
  UINT32 slope;
  UINT32 ErrLogDiff;

  ErrLogDiff = errLog_2 - errLog_1;
  if (errLog_2 <= errLog_1) {
    berStats[3] += 1;                 // non-monotonic case
    return (vrefpass * 10 + 10);
  } else if (errLog_2 < errLog_Target) {
    berStats[2] += 1;                 // error target above errLog_2 -> extrapolation
  } else if (errLog_1 <= errLog_Target) {
    berStats[1] += 1;                 // error target between errLog_1 and errLog_2 -> interpolation
  } else {
    berStats[0] += 1;                 // error target below errLog_1 -> extrapolation
  }

  //extrapolate above errLog_2, max extrapolation is 1 tick (10)
  if (errLog_2 < errLog_Target) {
    vref =  vrefpass * 10 + 20 + MIN (10, (10 * (errLog_Target - errLog_2)) / (ErrLogDiff));
  } else if ( (errLog_1 <= errLog_Target) && (errLog_Target <= errLog_2) && (ErrLogDiff != 0)) {
    vref =  vrefpass * 10 + 10 + (10 * (errLog_Target - errLog_1)) / (ErrLogDiff);  //interpolate
  } else {
    //extrapolate below errLog_1
    slope = (ErrLogDiff) > errLog_1 ? (ErrLogDiff) : errLog_1;
    if (slope != 0) {
      vref = vrefpass * 10 + (10 * errLog_Target) / slope;
    } else {
      vref = 0;
    }
  }

  return vref;  //returns a (vref * 10) interpolation/extrapolation
};

/**
  This function swaps a subfield, within a 32 bit integer value with the specified value.

  @param[in] CurrentValue - 32 bit input value.
  @param[in] NewValue     - 32 bit New value.
  @param[in] Start        - Subfield start bit.
  @param[in] Length       - Subfield length in bits/

  @retval The updated 32 bit value.
**/
UINT32
MrcBitSwap (
  IN UINT32       CurrentValue,
  IN const UINT32 NewValue,
  IN const UINT8  Start,
  IN const UINT8  Length
  )
{
  UINT32 mask;

  // Do bitwise replacement:
  mask = (MRC_BIT0 << Length) - 1;
  CurrentValue &= ~(mask << Start);
  CurrentValue |= ((NewValue & mask) << Start);

  return CurrentValue;
}

/**
  This function returns the maximum Rx margin for a given Channel, Rank(s), and byte.

  @param[in] MrcData   - Pointer to MRC global data.
  @param[in] Param     - Test parameter.
  @param[in] Channel   - Channel to calculate max Rx margin.
  @param[in] RankRx    - Rank index.  0xFF causes all ranks to be considered.
  @param[in] Byte      - Byte to check.
  @param[in] Sign      - Sign of the margins (0 - negative/min, 1 - positive/max).
  @param[in] MaxMargin - Current max margin value.

  @retval The max Rx margin, either MaxMargin or value from stored margins.
**/
UINT8
MrcCalcMaxRxMargin (
  IN MrcParameters  *const MrcData,
  IN UINT8                 Param,
  IN const UINT8           Channel,
  IN const UINT8           RankRx,
  IN const UINT8           Byte,
  IN const UINT8           Sign,
  IN UINT16                MaxMargin
  )
{
  const MRC_FUNCTION *MrcCall;
  INT64         GetSetVal;
  INT64         GetSetMin;
  INT64         GetSetMax;
  UINT16        ParamList[2];
  UINT8         ParamLen;
  UINT8         Idx;
  UINT8         Start;
  UINT8         Stop;
  UINT8         Rank;
  UINT16        MinRange;
  UINT16        MaxRange;

  MrcCall = MrcData->Inputs.Call.Func;
  MrcCall->MrcSetMem ((UINT8 *) ParamList, sizeof (ParamList), 0);

  // Check for saturation on Rx Timing
  if (RankRx == 0xFF) {
    // If desired for all ranks
    Start = 0;              // Start in rank 0
    Stop = 4;               // Up to 4 ranks
  } else {
    Start = GetRankToStoreResults(MrcData, RankRx);
    Stop  = Start + 1;
  }

  ParamLen  = 1;
  MinRange  = 0;
  MaxRange  = 0;
  GetSetMin = 0;
  GetSetMax = 0;
  for (Rank = Start; Rank < Stop; Rank++) {
    if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
      if (Param == RdT) {
        MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RxDqsPDelay, ReadFromCache, &GetSetVal);
        ParamList[0] = (UINT16) GetSetVal;
        MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RxDqsNDelay, ReadFromCache, &GetSetVal);
        ParamList[1] = (UINT16) GetSetVal;
        // Assumption here is that P and N have the same limits.
        MrcGetSetLimits (MrcData, RxDqsNDelay, &GetSetMin, &GetSetMax, NULL);
        ParamLen = 2;
      } else if (Param == RdV) {
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, RxVref, ReadFromCache, &GetSetVal);
        ParamList[0] = (UINT16) GetSetVal;
        MrcGetSetLimits (MrcData, RxVref, &GetSetMin, &GetSetMax, NULL);
        // For RdV ChangeMargin(), offset step is 1/2 RxVref.
        MaxMargin /= 2;
      } else if (Param == RcvEnaX) {
        MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RecEnDelay, ReadFromCache, &GetSetVal);
        ParamList[0] = (UINT16) GetSetVal;
        MrcGetSetLimits (MrcData, RecEnDelay, &GetSetMin, &GetSetMax, NULL);
        MaxMargin *= 4;
      }
      MinRange = (UINT16) GetSetMin;
      MaxRange = (UINT16) GetSetMax;

      for (Idx = 0; Idx < ParamLen; Idx++) {
        if (Sign == 0) {
          if (MaxMargin > ParamList[Idx] - MinRange) {
            MaxMargin = ParamList[Idx] - MinRange;
          }
        } else {
          if (MaxMargin > MaxRange - ParamList[Idx]) {
            MaxMargin = MaxRange - ParamList[Idx];
          }
        }
      }
      if (Param == RdV) {
        // Scale back
        MaxMargin *= 2;
        break;
      } else if (Param == RcvEnaX) {
        MaxMargin /= 4;
      }
    }
  }
  return (UINT8) MaxMargin;
}

/**
  This function returns the maximim (Tx or Cmd) Vref margin for a given Channel.

  @param[in] MrcData   - Pointer to MRC global data.
  @param[in] Channel   - Channel to calculate max margin.
  @param[in] RankMask  - Rank Mask for DDR4 and Lpddr4.
  @param[in] Byte      - Zero based byte number.
  @param[in] Param     - Parameter of Vref to use
  @param[in] Sign      - Sign of the margins (0 - negative/min, 1 - positive/max).
  @param[in] MaxMargin - Current max margin value.
  @param[in] Pda       - Use PDA or not.

  @retval The max Vref margin, either MaxMargin or value from stored margins.
**/
UINT8
MrcCalcMaxVrefMargin (
  IN MrcParameters  *const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           RankMask,
  IN const UINT8           Byte,
  IN const UINT8           Param,
  IN const UINT8           Sign,
  IN       UINT8           MaxMargin,
  IN       BOOLEAN         Pda
  )
{

  MrcDebug                                          *Debug;
  MrcInput                                          *Inputs;
  MrcOutput                                         *Outputs;
  MrcChannelOut                                     *ChannelOut;
  MrcRankOut                                        *RankOut;
  INT32                                             CurrentVrefOff;
  INT32                                             MaxRange;
  INT32                                             MaxVrefOff;
  INT32                                             MinVrefOff;
  INT32                                             MaxVref;
  INT32                                             MinVref;
  INT32                                             CurrentVref;
  UINT8                                             GetSetCh;
  UINT8                                             Rank;
  UINT8                                             MrIndex;
  BOOLEAN                                           Ddr4;
  BOOLEAN                                           Lpddr4;
  GSM_GT                                            Group;
  INT64                                             GetSetMin;
  INT64                                             GetSetMax;
  INT64                                             GetSetVal;

  Inputs           = &MrcData->Inputs;
  Outputs          = &MrcData->Outputs;
  Debug            = &Outputs->Debug;
  Ddr4             = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr4           = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  CurrentVrefOff   = 0;

  if ((Lpddr4) || (Ddr4 && (Param == WrV))) {
    // Get maximal offset by comparing MaxRange with the distance of the current offset from the min/max offset.
    // Algorithm:
    // 1. Get MinVrefOffset, MaxVrefOffset, CurrentVref.
    // 2. Initialize MaxRange = MaxMargin.
    // 3. For all channels, ranks:
    //      a. MaxRange = MIN (MaxRange, (CurrentVrefOff - MinVrefOff)) (for negative sign)
    //      b. MaxRange = MIN (MaxRange, (MaxVrefOff - CurrentVrefOff)) (for negative sign)
    ChannelOut = &MrcData->Outputs.Controller[0].Channel[Channel];
    MaxRange = MaxMargin;
    MaxVrefOff = GetMaxPossibleVrefOffset(MrcData, Param);
    MinVrefOff = -1 * MaxVrefOff;
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel) & RankMask) {
        RankOut = &ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank)].Rank[Rank % 2];
        if (Ddr4) {
          if (Pda) {
            CurrentVrefOff = MrcVrefDqToOffsetDdr4 (RankOut->Ddr4PdaMr6[Byte] & 0x7F);
          } else {
            CurrentVrefOff = MrcVrefDqToOffsetDdr4 ((UINT8)(RankOut->MR[mrMR6] & 0x7F));
          }
          // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,  "Ddr4  Channel %u Rank %u RankOut->MR[mrMR6]= 0x%X\n",Channel, Rank, RankOut->MR[mrMR6]);
        } else { // Lpddr4
          MrIndex = (Param == CmdV) ? mrIndexMR12 : mrIndexMR14;
          MrcVrefEncToOffsetLpddr4 (
            MrcData,
            RankOut->MR[MrIndex] & 0x3F,
            (RankOut->MR[MrIndex] >> 6) & 1,
            &CurrentVrefOff
            );
          // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,  "Lpddr4  Channel %u Rank %u RankOut->MR[mrIndexMR%d]= 0x%X\n",Channel, Rank, (Param == CmdV) ? 12 : 14, RankOut->MR[MrIndex]);
        }
        if (Sign == 0) {
          MaxRange = MIN (MaxRange, (CurrentVrefOff - MinVrefOff));
        } else {  // Sign == 1
          MaxRange = MIN (MaxRange, (MaxVrefOff - CurrentVrefOff));
        }
      }
    } // for Rank
  } else {
    // In this case we compare MaxRange with the distance of the current Margin Parameter absolute value
    // (not offset) with the min/max margin parameter allowed value.  Algorithm:
    // 1. Read Param MinVref, MaxVref and CurrentVref.
    // 2. Calculate MaxRange:
    //      a. MaxRange = MIN (CurrentVref - MinVref, MaxMargin) (for negative sign)
    //      b. MaxRange = MIN (MaxVref - CurrentVref, MaxMargin) (for positive sign)
    GetSetCh = Channel;
    if (Param == CmdV) {
      if (Inputs->IclA0) {
        switch (Inputs->CaVrefConfig) {
        case 0:
        default:
          Group = CmdVref;
          break;
        case 1:
          Group = (Channel == 0) ? CmdVref : TxVref;
          GetSetCh = 0;
          break;
        case 2:
          Group = (Channel == 0) ? CmdVref : TxVref;
          break;
        }
      } else {
        Group = CmdVref;
      }
    } else {
      Group = TxVref;
    }
    MaxRange = MaxMargin;
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel) & RankMask) {
        MrcGetSetDdrIoGroupChannelRank (MrcData, GetSetCh, Rank, Group, ReadFromCache, &GetSetVal);
        MrcGetSetLimits (MrcData, Group, &GetSetMin, &GetSetMax, NULL);
        CurrentVref = (INT32) GetSetVal;
        MinVref = (INT32) GetSetMin;
        MaxVref = (INT32) GetSetMax;

        //  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%dparam %x, MaxMargin %d, CurrentVref %d, TotalVref %d\n", Channel, param, MaxMargin, CurrentVrefOff, TotalVref);
        if (Sign == 0) {
        // Saturation point of Vref
          MaxRange = MIN (CurrentVref - MinVref, MaxRange);
          //  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Saturation possible C%d, New MaxMargin %d\n", Channel, MaxRange);
        } else {
          // Sign == 1
          // Saturation point of Vref
          MaxRange = MIN (MaxVref - CurrentVref, MaxRange);
          //  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Saturation possible C%d, New MaxMargin %d\n", Channel, MaxRange);
        }
      }
    } // for Rank
  } // LP4 or DDR4 WrV

  if (MaxRange < 0) {
    MRC_DEBUG_MSG(Debug, MSG_LEVEL_ERROR, "Error Param %d Got MaxRange %d < 0\n", Param, MaxRange);
    MaxRange = 0;
  }

  return (UINT8) MaxRange;
}

/**
  This function determines if a bit lane[0-7] has seen a pass and a fail in each byte for all channels populated.

  @param[in] MrcData   - Pointer to MRC global data.
  @param[in] chBitmask - Bit mask of channels to consider.
  @param[in] OnePass   - Array of Bit masks marking DQ lanes has had a passing value.
  @param[in] OneFail   - Array of Bit masks marking DQ lanes has had a failing value.

  @retval The AND result of each Channel/byte for OnePass and OneFail.
**/
UINT8
MrcAndBytes (
  IN MrcParameters *const MrcData,
  IN const UINT8          chBitmask,
  IN UINT8                OnePass[MAX_CHANNEL][MAX_SDRAM_IN_DIMM],
  IN UINT8                OneFail[MAX_CHANNEL][MAX_SDRAM_IN_DIMM]
  )
{
  UINT8 Res;
  UINT8 Channel;
  UINT8 byte;

  Res = 0xFF;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (((MRC_BIT0 << Channel) & chBitmask) == 0) {
      continue;
    }

    for (byte = 0; byte < MrcData->Outputs.SdramCount; byte++) {
      Res &= OnePass[Channel][byte];
      Res &= OneFail[Channel][byte];
    }
  }

  return Res;
}

/**
  This function Finds the margin for all channels/all bits. The margin sweep is a parameterized
  Assume REUT test has already been fully setup to run
  This will unscale the results such that future tests start at the correct point
  Uses ChangeMargin function to handle a variety cases (Timing, Voltage, Fan, etc.)

  @param[in]     MrcData    - Include all MRC global data.
  @param[in]     chBitMask  - Channel BIT mask for Channel(s) to work on
  @param[in]     Rank       - Rank to work on
  @param[in,out] marginbit  - used as the return data ( real margin measurement, no 10x)
                              marginbit[ch,byte,bit,sign] = abs(Margin)
                              Note: If param == RdTBit/RdVBit/WrVBit, marginbit is also the starting point
  @param[in,out] marginbyte - provides the starting point on a per byte basis (still 10x)
  @param[in]     param      - defines the margin type
  @param[in]     mode       - allows for different types of modes for margining
                              {Bit0: PhLock (keep all bytes within in ch in phase),
                               Bit1: Ch2Ch Data out of phase (LFSR seed)
                               Bits 15:2: Reserved}
  @param[in]     MaxMargin  - Default Maximum margin
  @param[in]     MsgPrint   - Show debug prints

  @retval mrcSuccess if successful, otherwise it returns an error status.
**/
MrcStatus
MrcGetMarginBit (
  IN     MrcParameters *const MrcData,
  IN     UINT8                chBitMask,
  IN     UINT8                Rank,
  IN OUT UINT32               marginbit[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS][MAX_EDGES],
  IN OUT UINT32               marginbyte[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     UINT8                param,
  IN     UINT16               mode,
  IN     UINT8                MaxMargin,
  IN     BOOLEAN              MsgPrint
  )
{
  MrcDebug        *Debug;
  MrcInput        *Inputs;
  MrcOutput       *Outputs;
  MrcStatus       Status;
  MrcChannelOut   *ChannelOut;
  MrcDebugMsgLevel DebugLevel;
  const MRC_FUNCTION *MrcCall;
  UINT8           Channel;
  UINT8           SubCh;
  UINT8           ByteStart;
  UINT8           ByteEnd;
  UINT8           Byte;
  UINT8           bit;
  UINT8           sign;
  INT8            realSign;
  UINT8           pbyte;
  BOOLEAN         PerCh;
  UINT8           PerBit;
  UINT8           Points2D;
  UINT8           DoneMask;
  UINT8           ByteMax;
  UINT8           SkipWait;
  UINT8           chPass;
  UINT8           chFail;
  UINT8           AllFail;
  // Set to 1 after ch/byte/bit has a passing point
  UINT8           OnePass[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  // Set to 1 after ch/byte/bit has a failing point
  UINT8           OneFail[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT8           ErrByte;
  UINT8           ErrStatus[MAX_SDRAM_IN_DIMM];
  UINT8           MinMargin;
  UINT32          value0;
  UINT32          value1;
  UINT32          v0;
  UINT32          CMargin[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS];    // Current Margin Point Testing
  UINT32          ABMargin[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];             // Average Byte Margin
  UINT32          MinTested[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS];  // Min Margin Point Tested
  UINT8           PrintPetByte;
  INT8            RdTAdjust;
  UINT32          BitTimePerBit;
  UINT8           BitMask;
  UINT8           RankMask;
  //REUT_GLOBAL_CTL_STRUCT ReutGlobalCtl; // @todo <ICL> Update with CPGC 2.0 implementation
  INT64           GetSetVal;
  GSM_GT          GroupType;
  INT64           PerBitDelayMax;
  INT64           PerBitDelayMid;

  Status    = mrcSuccess;
  SkipWait  = 0;
  Inputs    = &MrcData->Inputs;
  Outputs   = &MrcData->Outputs;
  Debug     = &Outputs->Debug;
  MrcCall   = Inputs->Call.Func;
  ByteMax   = MaxMargin;
  RankMask  = 1 << Rank;
  GroupType = GsmGtMax;
  value0    = 0;
  DebugLevel = MsgPrint ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;
  MrcCall->MrcSetMem ((UINT8 *) ABMargin, sizeof (ABMargin), 0);
  // How many points to test
  Points2D = 1 + (param / 16);
  // Define PerByte param for PerBit cases
  if (param == RdTBit) {
    pbyte   = RdT;
    PerBit  = 1;
    GroupType = RxDqBitDelay;
  } else if (param == WrTBit) {
    pbyte   = WrT;
    PerBit  = 1;
    GroupType = TxDqBitDelay;
  } else if (param == RdVBit) {
    pbyte   = RdV;
    PerBit  = 1;
    GroupType = RxVoc;
  } else {
    pbyte   = 0;
    PerBit  = 0;
  }
  PerBitDelayMax = 0;
  PerBitDelayMid = 0;
  // Get Max and Middle value for PerBit Cases
  if (PerBit == 1) {
    MrcGetSetLimits (MrcData, GroupType, NULL, &PerBitDelayMax, NULL);
    PerBitDelayMid = (((UINT8) PerBitDelayMax) + 1) / 2;
  }

  // Print results PerBit or PerByte
  PrintPetByte = (param == RdT || param == WrT || param == RdV);
  // Created for debug purpose
  // Are we using DIMM Vref?  If so, need to use the same Vref across all bytes
  PerCh = ((param == WrFan2) || (param == WrFan3) || (param == WrV) || (mode & 0x1)) && (PerBit == 0);
  // Get Average Byte back to real margin numbers
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (chBitMask & (MRC_BIT0 << Channel)) {
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        if (!MrcByteInChannelExist(MrcData, Channel, Byte)) {
          continue;
        }
        ABMargin[Channel][Byte] = (marginbyte[Channel][Byte][0] + marginbyte[Channel][Byte][1]) / 20;
      }
    }
  }
  // Find Left and Right Edges
  for (sign = 0; sign < 2; sign++) {
    realSign = (INT8) ((2 * sign) - 1);
    MRC_DEBUG_MSG (Debug, DebugLevel, "\n+--MrcGetMarginBit, rsign = %d\n", realSign);
    MRC_DEBUG_MSG (Debug, DebugLevel, (PrintPetByte) ? "\nMargin\tBits\n" : "");
    // Initialize variables
    DoneMask = 0xFF;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(chBitMask & (MRC_BIT0 << Channel))) {
        continue; // This channel is not populated
      }
      ChannelOut = &Outputs->Controller[0].Channel[Channel];
      MinMargin = 0x7F; // Start with a huge unsigned number
      for (SubCh = 0; SubCh < MAX_SUB_CHANNEL; SubCh++) {
        ByteStart = ChannelOut->ByteStart[SubCh];
        ByteEnd   = ChannelOut->ByteEnd[SubCh];
        if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
          for (Byte = ByteStart; Byte <= ByteEnd; Byte++) {
            OnePass[Channel][Byte] = OneFail[Channel][Byte] = DoneMask;
          }
          continue;
        }
        for (Byte = ByteStart; Byte <= ByteEnd; Byte++) {
          // Init arrays to 0
          OnePass[Channel][Byte] = OneFail[Channel][Byte] = 0;
          // Find MaxMargin for this byte
          ByteMax = MaxMargin;
          if ((param == RdT) || (param == RdV)) {
            ByteMax = MrcCalcMaxRxMargin (MrcData, param, Channel, RankMask, Byte, sign, MaxMargin);
          } else if (param == WrV) {
            ByteMax = MrcCalcMaxVrefMargin (MrcData, Channel, RankMask, Byte, param, sign, MaxMargin, FALSE);
          }
          CMargin[Channel][Byte][0] = ABMargin[Channel][Byte]; // Start on the passing edge
          if ((param == RdTBit) || (param == WrTBit)) {
            // Special case for PerBit Timing
            v0 = realSign * (CMargin[Channel][Byte][0]);
            Status = ChangeMargin (MrcData, pbyte, v0, 0, 0, Channel, RankMask, Byte, 0, 0, 0);
          } else if (param == RdVBit) {
            // Special case for PerBit Voltage
            // Guardband into the failing region
            if (CMargin[Channel][Byte][0] >= 2) {
              CMargin[Channel][Byte][0] -= 2;
            } else {
              CMargin[Channel][Byte][0] = 0;
            }
            v0 = realSign * (CMargin[Channel][Byte][0]);
            Status = ChangeMargin (MrcData, pbyte, v0, 0, 0, Channel, RankMask, Byte, 0, 0, 0);
          }
          // Update the variables for PerBit tracking
          if (PerBit) {
            for (bit = 0; bit < MAX_BITS; bit++) {
              CMargin[Channel][Byte][bit] = marginbit[Channel][Byte][bit][sign];
              // Double check saturation limits as we cannot move PBD more than we can move the Byte PI.
              if (CMargin[Channel][Byte][bit] > MaxMargin) {
                CMargin[Channel][Byte][bit] = MaxMargin;
              }
            }
          } else {
            if (CMargin[Channel][Byte][0] > ByteMax) {
              CMargin[Channel][Byte][0] = ByteMax;
            }
          }
          // Find MinMargin to start and set marginbyte for the PerCh case

          if (PerCh) {
            if (CMargin[Channel][Byte][0] < MinMargin) {
              MinMargin = (UINT8) CMargin[Channel][Byte][0];
            }
            CMargin[Channel][Byte][0] = MinMargin;
          }
          for (bit = 0; bit < MAX_BITS; bit++) {
            MinTested[Channel][Byte][bit]       = CMargin[Channel][Byte][bit * PerBit];
            marginbit[Channel][Byte][bit][sign] = CMargin[Channel][Byte][bit * PerBit];
          }
        } // for Byte
      } // for SubCh
    } // for Channel
    // Initialize error status to 0.
    MrcCall->MrcSetMem ((UINT8 *) ErrStatus, sizeof (ErrStatus), 0);
    // Search algorithm:
    // Walk up until everybody fails.  Then Walk down until everybody passes.
    while (MrcAndBytes (MrcData, chBitMask, OnePass, OneFail) != DoneMask) {
      // Walk through all 2D points
/** @todo <ICL> Update with CPGC 2.0 implementation
      ReutGlobalCtl.Data = 0;
      ReutGlobalCtl.Bits.Global_Clear_Errors = 1;
      MrcWriteCR (MrcData, REUT_GLOBAL_CTL_REG, (UINT8) ReutGlobalCtl.Data); // Clear errors
**/
      for (value1 = 0; value1 < Points2D; value1++) {
        // Set Margin level
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!(chBitMask & (MRC_BIT0 << Channel))) {
            continue;
          }
          SkipWait = (chBitMask >> (Channel + 1)); // Skip if there are more channels
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
              continue;
            }
            if (PerBit) {
              for (bit = 0; bit < MAX_BITS; bit++) {
                // Per Bit Deskew.  Note: When (sign==1), then CMargin is off by 1.
                // Suppose RdTBit and Right/Left Edge Last Pass @ CMargin = 12, 9
                //    Real Right Edge = (15-12)=3,  Right Edge Moved By (8-3)=5
                //    Real Left Edge = 9,           Left Edge Moved By (9-8) =1
                // Center Movement = (5-1)/2 = +2
                // To get correct answer, need to add +1 to CMargin for Right Edge
                //   ie: Center Movement = (12+1-9)/2 = +2
                // This error will be corrected at the edge of the function
                // For RdTBit we shift data not strobe.  Since we shift the opposite signal, sign is inverted
                if ((param == RdTBit && sign) || ((param != RdTBit) && (sign == 0))) {
                  v0 = (MaxMargin - CMargin[Channel][Byte][bit]);
                } else {
                  v0 = CMargin[Channel][Byte][bit];
                }
                if (v0 > MaxMargin) {
                  v0 = MaxMargin;
                }
                GetSetVal = (UINT8) v0;
                MrcGetSetDdrIoGroupSocket0 (MrcData, Channel, Rank, Byte, bit, GroupType, WriteToCache, &GetSetVal);
              } // bit loop
            } else {
              value0 = realSign * CMargin[Channel][Byte][0];
              // EnMultiCast=0, ch,rank,byte,0, UpdateHost=0, SkipWait
              Status = ChangeMargin (
                        MrcData,
                        param,
                        value0,
                        value1,
                        0,
                        Channel,
                        RankMask,
                        Byte,
                        0,
                        0,
                        SkipWait
                        );
              if ((PerCh) && ((mode & 1) == 0)) {
                break;
              }
            } // !perBit
          } // Byte
        } // Channel
        MrcFlushRegisterCachedData (MrcData);

        // Run Test
        RunIOTest (MrcData, chBitMask, Outputs->DQPat, (value1 == 0), 0);
        // Check if we have already failed and can stop running
        if (value1 < (UINT32) (Points2D - 1)) {
          AllFail = 1;
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            if (!(chBitMask & (MRC_BIT0 << Channel))) {
              continue;
            }
            ChannelOut = &Outputs->Controller[0].Channel[Channel];
            MrcCall->MrcSetMem ((UINT8 *) ErrStatus, sizeof (ErrStatus), 0);
            for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
              MrcGetBitGroupErrStatus (MrcData, Channel, SubCh, ErrStatus);
              for (Byte = ChannelOut->ByteStart[SubCh]; Byte <= ChannelOut->ByteEnd[SubCh]; Byte++) {
                AllFail &= (ErrStatus[Byte] == 0xFF);
              }
            } // for SubCh
          } // for Channel
          if (AllFail) {
            break;  // break if any error
          }
        }
      } // for Points2D
      // Initialize error status to 0.
      MrcCall->MrcSetMem ((UINT8 *) ErrStatus, sizeof (ErrStatus), 0);
      // Collect results and Update variables for next point to test
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(chBitMask & (MRC_BIT0 << Channel))) {
          continue;
        }
        for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
          MrcGetBitGroupErrStatus (MrcData, Channel, SubCh, ErrStatus);
        } // for SubCh
        chPass = 0xFF;
        chFail = 0xFF;
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
            continue;
          }
          // Extract Errors
          ErrByte = ErrStatus[Byte];
          ErrByte &= DoneMask;
#ifdef MRC_DEBUG_PRINT
          if (PerBit == 1) {
            MRC_DEBUG_MSG (Debug, DebugLevel, "0x");
            for (bit = 0; bit < MAX_BITS; bit++) {
              MrcGetSetDdrIoGroupSocket0 (MrcData, Channel, Rank, Byte, bit, GroupType, ReadFromCache, &GetSetVal);
              MRC_DEBUG_MSG (Debug, DebugLevel, "%02X", (UINT8) GetSetVal);
            }
          } else if (param == WrT || param == RdT || param == RdV || param == WrV) {
            MRC_DEBUG_MSG (Debug, DebugLevel, "% 2d", CMargin[Channel][Byte][0]);
          }
#endif // MRC_DEBUG_PRINT
          for (bit = 0; bit < MAX_BITS; bit++) {
            BitMask       = MRC_BIT0 << bit;
            BitTimePerBit = bit * PerBit;
            // Skip if this Bit Group is done
            if (OnePass[Channel][Byte] & OneFail[Channel][Byte] & (BitMask)) {
              MRC_DEBUG_MSG (Debug, DebugLevel, "   $");
              continue;
            }
            // Update variables for fail
            if (ErrByte & (BitMask)) {
              OneFail[Channel][Byte] |= (BitMask);
              MRC_DEBUG_MSG (Debug, DebugLevel, "   #");
              // Handle Speckles
              if (marginbit[Channel][Byte][bit][sign] >= CMargin[Channel][Byte][BitTimePerBit]) {
                marginbit[Channel][Byte][bit][sign] = CMargin[Channel][Byte][BitTimePerBit] - 1;
                OnePass[Channel][Byte] &= ~(BitMask);
              }
              // Update variables for pass
            } else {
              OnePass[Channel][Byte] |= (BitMask);
              MRC_DEBUG_MSG (Debug, DebugLevel, "   .");
              if (marginbit[Channel][Byte][bit][sign] < CMargin[Channel][Byte][BitTimePerBit]) {
                marginbit[Channel][Byte][bit][sign] = CMargin[Channel][Byte][BitTimePerBit];
              }
            }
          }
          // FIND MAX Saturation limit
          ByteMax = MaxMargin;
          if ((param == RdT) || (param == RdV)) {
            ByteMax = MrcCalcMaxRxMargin (MrcData, param, Channel, RankMask, Byte, sign, MaxMargin);
          } else if (param == WrV) {
            ByteMax = MrcCalcMaxVrefMargin (MrcData, Channel, RankMask, Byte, param, sign, MaxMargin, FALSE);
          }
          // HANDLE Saturation
          if (PerBit) {
            for (bit = 0; bit < MAX_BITS; bit++) {
              BitMask = MRC_BIT0 << bit;
              if (CMargin[Channel][Byte][bit] >= ByteMax) {
                OneFail[Channel][Byte] |= (BitMask);
              }
              if (CMargin[Channel][Byte][bit] == 0) {
                OnePass[Channel][Byte] |= (BitMask);
              }
            }
          } else {
            if (CMargin[Channel][Byte][0] >= ByteMax) {
              OneFail[Channel][Byte] = DoneMask;
            }
            if (CMargin[Channel][Byte][0] == 0) {
              OnePass[Channel][Byte] = DoneMask;
            }
          }
          // DECIDE WHAT TO TEST NEXT
          // If PerByte, Do this within the for byte loop
          chPass &= OnePass[Channel][Byte];
          chFail &= OneFail[Channel][Byte];
          if (PerCh == FALSE) {
            if (PerBit) {
              for (bit = 0; bit < MAX_BITS; bit++) {
                BitMask = MRC_BIT0 << bit;
                // Skip if this Bit Group is done
                if (OnePass[Channel][Byte] & OneFail[Channel][Byte] & (BitMask)) {
                  continue;
                }
                if ((OneFail[Channel][Byte] & BitMask) == 0) {
                  CMargin[Channel][Byte][bit] += 1;
                } else if ((OnePass[Channel][Byte] & BitMask) == 0) {
                  MinTested[Channel][Byte][bit] -= 1;
                  CMargin[Channel][Byte][bit] = MinTested[Channel][Byte][bit];
                } else {
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "WARNING! Can't have both: OnePass and OneFail Not Done\n");
                }
              }
            } else {
              // PerCh
              // Skip if this Byte Group is done
              if ((OnePass[Channel][Byte] & OneFail[Channel][Byte]) == DoneMask) {
                MRC_DEBUG_MSG (Debug, DebugLevel, " ");
                continue;
              }
              if (OneFail[Channel][Byte] != DoneMask) {
                CMargin[Channel][Byte][0] += 1;
              } else if (OnePass[Channel][Byte] != DoneMask) {
                MinTested[Channel][Byte][0] -= 1;
                CMargin[Channel][Byte][0] = MinTested[Channel][Byte][0];
              }
            }
          }
          MRC_DEBUG_MSG (Debug, DebugLevel, " ");
        }
        // END OF BYTE LOOP
        // DECIDE WHAT TO TEST NEXT
        // If PerCh, Do this within the for ch loop
        if (PerCh == TRUE) {
          if ((chPass & chFail) == DoneMask) {
            continue;
          }
          if (chFail != DoneMask) {
            CMargin[Channel][0][0] += 1;
          } else {
            MinTested[Channel][0][0] -= 1;
            CMargin[Channel][0][0] = MinTested[Channel][0][0];
          }
          // All bytes must use the same margin point
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            CMargin[Channel][Byte][0] = CMargin[Channel][0][0];
          }
        }
      } // for Channel
      MRC_DEBUG_MSG (Debug, DebugLevel, "\n");
    } // while
    // Update MarginByte to have the correct result
    if (PerBit == 0) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (chBitMask & (MRC_BIT0 << Channel)) {
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
              continue;
            }
            MinMargin = 0x7F; // Start with a huge unsigned number
            for (bit = 0; bit < MAX_BITS; bit++) {
              if (MinMargin > marginbit[Channel][Byte][bit][sign]) {
                MinMargin = (UINT8) marginbit[Channel][Byte][bit][sign];
              }
            }
            marginbyte[Channel][Byte][sign] = MinMargin * 10;
            // MRC_DEBUG_MSG (Debug, DebugLevel,"+--marginbyte = MinMargin*10 = %d\n", MinMargin*10);
          } // for Byte
        }
      } // for Channel
    } else {
      // Bit Margins
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(chBitMask & (1 << Channel))) {
          continue;
        }
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
            continue;
          }
          for (bit = 0; bit < MAX_BITS; bit++) {
            if ((param == RdTBit && sign) || ((param != RdTBit) && (sign == 0))) {
              marginbit[Channel][Byte][bit][sign] = MaxMargin - marginbit[Channel][Byte][bit][sign];
            }
          }
        } // for Byte
      } // for Channel
      // Cleanup after test
      Status = ChangeMargin (MrcData, pbyte, 0, 0, 1, 0, Rank, 0, 0, 0, 0);
    }
  }
  // END OF SIGN LOOP
  // Clean up after step
  if (PerBit == 1) {
    MrcGetSetDdrIoGroupSocket0 (MrcData, MAX_CHANNEL, Rank, MAX_SDRAM_IN_DIMM, MAX_BITS, GroupType, WriteToCache, &PerBitDelayMid);
    MrcFlushRegisterCachedData (MrcData);
  } else {
    Status = ChangeMargin (MrcData, param, 0, 0, 1, 0, (param == WrV)?0:Rank, 0, 0, 0, 0);
  }
  // Correct for 1 tick error in Per Bit Deskew right edge
  RdTAdjust = 1;
#ifdef MRC_DEBUG_PRINT
  if (PerBit == 1) {
    if (param == RdTBit) {
      RdTAdjust = -1;
    }
    MRC_DEBUG_MSG (Debug, DebugLevel, "\nGains     ");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (chBitMask & (MRC_BIT0 << Channel)) {
        MRC_DEBUG_MSG (Debug, DebugLevel, "\nChannel %d", Channel);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          MRC_DEBUG_MSG (Debug, DebugLevel, "\nByte %d\t", Byte);
          for (bit = 0; bit < MAX_BITS; bit++) {
            MRC_DEBUG_MSG (
              Debug,
              DebugLevel,
              "[%3d %3d]",
              ((RdTAdjust) * ((UINT8) PerBitDelayMid - marginbit[Channel][Byte][bit][0])),
              ((RdTAdjust) * (marginbit[Channel][Byte][bit][1] - (UINT8) PerBitDelayMid))
              );
          } // for bit
        } // for Byte
      }
    } // for Channel
  } else {
    MRC_DEBUG_MSG (Debug, DebugLevel, "\nCt");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if ((chBitMask & (MRC_BIT0 << Channel))) {
        MRC_DEBUG_MSG (Debug, DebugLevel, "\nChannel %d", Channel);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          MRC_DEBUG_MSG (Debug, DebugLevel, "\nByte %d\t", Byte);
          for (bit = 0; bit < MAX_BITS; bit++) {
            MRC_DEBUG_MSG (
              Debug,
              DebugLevel,
              "%8d ",
              (INT8) (marginbit[Channel][Byte][bit][1] - marginbit[Channel][Byte][bit][0]) / 2
              );
          }
          MRC_DEBUG_MSG (Debug, DebugLevel, "   ");
        } // for Byte
      }
    } // for Channel
  }
  MRC_DEBUG_MSG (Debug, DebugLevel, "\n");
#endif // MRC_DEBUG_PRINT
  return Status;
}

/**
  Assume REUT test has already been fully setup to run
  Finds the margin for all channels/all bytes
  The margin sweep is parameterized
  Uses ChangeMargin function to handle a variety of cases (Timing, Voltage, Fan, etc.)
  mode allows for different types of modes for margining:
    mode is {Bit0: PhLock (keep all bytes within in ch in phase),
             Bit1: Ch2Ch Data out of phase (LFSR seed), Bit 15:2: Reserved}
  marginByte is used as the starting point for the search (10x the actual margin)
  marginch returns the results (10x the actual margin)
  Interior: Search inside marginch limits, enabling multiple calls with different setups
  To reduce repeatibility noise, the returned margins is actually a BER extrapolation

  @param[in]     MrcData    - The global MrcData
  @param[in,out] marginByte - Data structure with the latest margin results
  @param[in]     chBitmask  - Bit mask of present channels
  @param[in]     RankIn     - Rank to change margins for
  @param[in]     RankRx     - Ranks for Rx margin
  @param[in]     param      - parameter to get margins for
  @param[in]     mode       - allows for different types of modes for margining:
  @param[in]     BMap       - Byte mapping to configure error counter control register
  @param[in]     EnBER      - Enable BER extrapolation calculations
  @param[in]     MaxMargin  - Max Margin allowed for the parameter
  @param[in]     Interior   - Search inside marginch limits, enabling multiple calls with different setups
  @param[in,out] BERStats   - Bit Error Rate Statistics.

  @retval mrcSuccess if successful, otherwise returns an error status.
**/
MrcStatus
MrcGetBERMarginByte (
  IN     MrcParameters * const MrcData,
  IN OUT UINT32          marginByte[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     UINT8           chBitmask,
  IN     UINT8           RankIn,
  IN     UINT8           RankRx,
  IN     UINT8           param,
  IN     UINT16          mode,
  IN     UINT8           *BMap,
  IN     UINT8           EnBER,
  IN     UINT8           MaxMargin,
  IN     UINT8           Interior,
  IN OUT UINT32          *BERStats
  )
{
  const MrcInput  *Inputs;
  MrcDebug        *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput        *Outputs;
  MrcIntOutput     *MrcIntData;
  MrcControllerOut *ControllerOut;
  MrcChannelOut    *ChannelOut;
  UINT32           *MarginByteTemp;
  MrcStatus        Status;
  UINT8            ResultType;
  UINT8            sign;
  INT8             rSign;
  UINT8            Points2D;
  UINT8            Channel;
  UINT8            SubCh;
  UINT8            byte;
  UINT8            ByteStart;
  UINT8            ByteEnd;
  UINT8            chByte;
  UINT8            SkipWait;
  UINT8            byteMax;
  UINT8            Margin;
  BOOLEAN          MinEyeFlag;
  UINT8            Byte;
  UINT8            Edge;
  UINT16           DoneMask;
  UINT16           SubchDoneMask;
  // Set to 1 after ch has 2 passing points
  UINT16           TwoPass[MAX_CHANNEL];
  // Set to 1 after ch has 2 failing points
  UINT16           TwoFail[MAX_CHANNEL];
  UINT16           res;
  INT64            GetSetVal;
  UINT64           ErrStatus;
  UINT16           BitMask;
  INT8             Delta;
  BOOLEAN          Done;
  BOOLEAN          allFail;
  BOOLEAN          PerCh;
  UINT32           value0;
  UINT32           value1;
  UINT32           tmp;
  UINT32           ErrCount;
  UINT8            LastPassVref[MAX_CHANNEL][MAX_SDRAM_IN_DIMM]; // Last passing Vref
  UINT32           InitValue[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];    // Initial value from margin byte
  UINT8            MaxTested[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];    // Highest Vref Point Tested
  UINT8            MinTested[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];    // Lowest Vref Point Tested
  // Log8(Error count) at different Vref Points. 32 bit number that is broken in 4 bytes
  // [LastPass+2, LastPass+1, LastPass, LastPass-1]
  UINT32           Errors[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  BOOLEAN          Ddr4;
  UINT8            Rank;
  // UINT8            RankLoop;
  BOOLEAN          DimmVrefParam;
  BOOLEAN          Overflow;
  CH0_SC0_CR_CPGC_SEQ_CTL_STRUCT  CpgcSeqCtl;

  Status        = mrcSuccess;
  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  MrcIntData    = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  ControllerOut = &Outputs->Controller[0];
  Debug         = &Outputs->Debug;
  chByte        = 0;
  Points2D      = (param / RdFan2) + 1;
  ResultType    = GetMarginResultType (param);
  Ddr4          = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  // Are we using DIMM Vref? (and not DDR4)
  DimmVrefParam = (param == WrFan2 || param == WrFan3 || param == WrV );   // WrFan not defined
  PerCh = (param == WrFan2 || param == WrFan3 || (param == WrV) || ((mode & 1) == 1));   // WrFan not defined
  Rank = GetRankToStoreResults (MrcData, RankIn);
//  if (param == WrV)
//  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"+--->MrcGetBERMarginByte, Points2D: %d, PerCh: %d --\n", Points2D,PerCh);
  DoneMask = (MRC_BIT0 << Outputs->SdramCount) - 1; // 0x1FF or 0xFF

  if (param == RcvEnaX) {
    // Make sure RecEnDelay values exist in CR cache for this algorithm to work, because we will use WriteOffsetUncached
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RecEnDelay, ReadCached, &GetSetVal);
          }
        }
      }
    }
  }

  // Run through margin test
  for (sign = 0; sign < 2; sign++) {
    rSign = (INT8) ((2 * sign) - 1);
//    if (param == WrV)
//    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"+--MrcGetBERMarginByte, rsign = %d\n", rSign);
    MrcCall->MrcSetMem ((UINT8 *) TwoPass, sizeof (TwoPass), 0);
    MrcCall->MrcSetMem ((UINT8 *) TwoFail, sizeof (TwoFail), 0);
    // Initialize variables
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!((MRC_BIT0 << Channel) & chBitmask)) {
        TwoPass[Channel] = DoneMask;
        TwoFail[Channel] = DoneMask;
        continue;
      }
      MinTested[Channel][0] = 0x7F;
      for (byte = 0; byte < Outputs->SdramCount; byte++) {
        LastPassVref[Channel][byte] = 0x7F; // Start with a huge unsigned number 127
        Errors[Channel][byte] = 0;
        // Find MaxMargin for this byte
        byteMax = MaxMargin;
        if ((param == RdT) || (param == RdV) || (param == RcvEnaX)) {
          byteMax = MrcCalcMaxRxMargin (MrcData, param, Channel, RankRx, byte, sign, MaxMargin);
        } else if ((param == CmdV) || DimmVrefParam) {
          byteMax = MrcCalcMaxVrefMargin (MrcData, Channel, RankRx, byte, param, sign, MaxMargin, FALSE);
//          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,  "\nChannel %u rank %u byte=%u sign=%d byteMax= %d\n",Channel, Rank, byte, sign, byteMax);
        }
        // Scale MarginResult back to real margin numbers.  Set Max/MinTested
        MarginByteTemp  = &marginByte[ResultType][Rank][Channel][byte][sign];
        *MarginByteTemp = *MarginByteTemp / 10;
        if (*MarginByteTemp > byteMax) {
          *MarginByteTemp = byteMax;
        }
        InitValue[Channel][byte] = *MarginByteTemp;
        // if Per Ch, find MinMargin to start.  Else set margin for that Byte
        if (PerCh == TRUE) {
          if (*MarginByteTemp < MinTested[Channel][0]) {
            MaxTested[Channel][0] = (UINT8) *MarginByteTemp;
            MinTested[Channel][0] = (UINT8) *MarginByteTemp;
          }
        } else {
          MaxTested[Channel][byte] = (UINT8) *MarginByteTemp;
          MinTested[Channel][byte] = (UINT8) *MarginByteTemp;
        }
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
        if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
          // Mark unpopulated subchannel as Done
          SubchDoneMask = 0x0F << (SubCh * 4);
          TwoPass[Channel] = SubchDoneMask;
          TwoFail[Channel] = SubchDoneMask;
          continue;
        }
        ByteStart = ChannelOut->ByteStart[SubCh];
        ByteEnd   = ChannelOut->ByteEnd[SubCh];
        for (byte = ByteStart; byte <= ByteEnd; byte++) {
          // Setup CPGC Error Counters to count errors per byte lane.
          MrcSetupErrCounterCtl (MrcData, Channel, SubCh, byte, ErrCounterCtlPerByte);
        }
      } // for Subch

      // Set MarginResult for the PerCh case
      if (PerCh == TRUE) {
        for (byte = 0; byte < Outputs->SdramCount; byte++) {
          marginByte[ResultType][Rank][Channel][byte][sign] = MinTested[Channel][0];
        }
      }
    } // for Channel
    // Search algorithm:
    // If start with a passing point, walk to hit 2 failing points
    //    Return as needed to hit a second passing point
    // If start with a failing point, walk to hit 2 passing points
    //    Return as needed to hit a second failing point
    // Keep testing until all ch/bytes find 2 passes and 2 fails
    Done = FALSE;
    do {
      // Walk through all 2D points
      CpgcSeqCtl.Data = 0;
      CpgcSeqCtl.Bits.CLEAR_ERRORS = 1;
      Cpgc20ControlRegWrite (MrcData, CpgcSeqCtl);
      for (value1 = 0; value1 < Points2D; value1++) {
        // Set Vref level
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!((MRC_BIT0 << Channel) & chBitmask)) {
            continue;
          }
          SkipWait = (chBitmask >> (Channel + 1)); // Skip if there are more channels
          for (byte = 0; byte < Outputs->SdramCount; byte++) {
            value0 = rSign * marginByte[ResultType][Rank][Channel][byte][sign];
//            if (param == WrV)
//            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"+----->Value0 is %d, Value1 is %d\n", (INT32)value0, value1);
            Status = ChangeMargin (
                      MrcData,
                      param,
                      value0,
                      value1,
                      0,
                      Channel,
                      RankIn,
                      byte,
                      0,
                      0,
                      SkipWait
                      );
            if ((PerCh) && ((mode & 1) == 0)) {
              // Only Byte 7 on Channel 1 is needed to update Wr DIMM Vref - Taken care of inside ChangeMargin routine
              // for Ddr4 WrV is define per ch so we break after byte 0
              break;
            }
          }
        }
        // Run Test
        RunIOTest (MrcData, chBitmask, Outputs->DQPat, (value1 == 0), 0);
        if (param == CmdV) {
          MrcResetSequence (MrcData);
        }
        // What is the idea behind this? What if all byte groups failed?
        if (EnBER == 0 && value1 < (UINT32) (Points2D - 1)) {
          allFail = TRUE;
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            if (!((MRC_BIT0 << Channel) & chBitmask)) {
              continue;
            }
            // Read out per byte error results
            res = 0;
            for (SubCh = 0; SubCh < MrcIntData->SubChEngCount; SubCh++) {
              if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
                MrcGetMiscErrStatus (MrcData, Channel, SubCh, ByteGroupErrStatus, &ErrStatus);
                res |= MrcCall->MrcLeftShift64 (ErrStatus, (SubCh == 0) ? 0 : 4);
                if ((res & DoneMask) != DoneMask) {
                  allFail = FALSE;
                }
              }
            } // for SubCh
          } // for Channel
          if (allFail == TRUE) {
            break;
          }
        }
      }
      // Collect results and Update variables for next point to test
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!((MRC_BIT0 << Channel) & chBitmask)) {
          continue;
        }
        ChannelOut = &ControllerOut->Channel[Channel];
        for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
          if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
            continue;
          }
          ByteStart = ChannelOut->ByteStart[SubCh];
          ByteEnd   = ChannelOut->ByteEnd[SubCh];
          for (byte = ByteStart; byte <= ByteEnd; byte++) {
            BitMask = MRC_BIT0 << byte;
            // Skip if this Byte Group is done
            if ((TwoPass[Channel] & TwoFail[Channel] & (BitMask)) != 0) {
              continue;
            }
            // Handle PerCh vs. PerByte variable differences
            chByte = (PerCh == TRUE ? 0 : byte);
            // Read CPGC Error Count
            MrcGetErrCounterStatus (MrcData, Channel, SubCh, byte, ErrCounterCtlPerByte, &ErrCount, &Overflow);
            Margin = (UINT8)marginByte[ResultType][Rank][Channel][byte][sign];
            Delta = (Margin - LastPassVref[Channel][byte]);
            //          if (param == WrV) {
            //          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"+----->channel: %d, Error count:%x.\n", Channel, ErrCount);
            //          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"+----->Margin:%d, LastPassVref:%d, delta:%d. sign:%d\n", Margin, LastPassVref[Channel][byte], (INT8) Delta, sign);
            //          }
            // Update Pass/Fail Variables:
            if (ErrCount == 0 && Margin == MaxTested[Channel][chByte]) {
              // Passing while walking up
              if (Delta < 0) {
                // First passing point
                MRC_DEBUG_ASSERT(
                  MinTested[Channel][chByte] == MaxTested[Channel][chByte],
                  Debug,
                  "Error: MaxTested < LastPass after first point"
                  );
                LastPassVref[Channel][byte] = Margin;
              } else if (Delta == 1) {
                // Normal, walk to fail
                Errors[Channel][byte] = MrcBitShift(Errors[Channel][byte], -8 * Delta) & BER_ERROR_MASK;
                LastPassVref[Channel][byte] = Margin;
                TwoPass[Channel] |= (BitMask);
              } else if (Delta == 2) {
                // Speckling in response, Consider point as error
                Errors[Channel][byte] = MrcBitSwap(Errors[Channel][byte], MrcLog8(ErrCount), 24, 8);
                TwoFail[Channel] |= (BitMask);
              } else {
                MRC_DEBUG_ASSERT(
                  FALSE,
                  Debug,
                  "Error: Tested point twice or Tested >2 above LastPass (Passing while walking up)"
                  );
              }
            } else if (ErrCount == 0 && Margin == MinTested[Channel][chByte]) {
              // Skip if this byte is already done
              if ((TwoPass[Channel] & (BitMask)) != 0) {
                continue;
              }
              if (Delta == -1) {
                // Finding 2nd pass
                Errors[Channel][byte] = MrcBitSwap(Errors[Channel][byte], 0, 0, 8);
                TwoPass[Channel] |= (BitMask);
              } else {
                // 1st passing point
                // Don't shift Errors.  Fail points already assumed correct LastPass
                LastPassVref[Channel][byte] = Margin;
                TwoPass[Channel] &= ~(BitMask);
              }
            } else if (ErrCount > 0 && Margin == MaxTested[Channel][chByte]) {
              // Failing while walking up
              MRC_DEBUG_ASSERT(Delta <= 2, Debug, "Error: Tested >2 above LastPass (Failing while walking up)");
              if (Delta < 2) {
                // first failing point
                Errors[Channel][byte] = MrcBitSwap(Errors[Channel][byte], MrcLog8(ErrCount), 16, 8);
                TwoFail[Channel] &= ~(BitMask);
              } else if (Delta == 2) {
                // 2nd failing point
                Errors[Channel][byte] = MrcBitSwap(Errors[Channel][byte], MrcLog8(ErrCount), 24, 8);
                TwoFail[Channel] |= (BitMask);
              }
            } else if (ErrCount > 0 && Margin == MinTested[Channel][chByte]) {
              // Failing while walking down
              if (LastPassVref[Channel][byte] < 0xFF && Delta <= 0) {
                // Adjust LastPassVref and Error count to be below this failure point.
                Errors[Channel][byte] = MrcBitSwap(Errors[Channel][byte], MrcLog8(ErrCount), 8 * (Delta + 1), 8);
                Errors[Channel][byte] = MrcBitShift(Errors[Channel][byte], 8 * (1 - Delta));
                LastPassVref[Channel][byte] = Margin - 1;
              } else {
                tmp = ((Errors[Channel][byte] & 0xFF0000) << 8) + MrcLog8(ErrCount);
                Errors[Channel][byte] = MrcBitSwap(Errors[Channel][byte], tmp, 16, 16);
                //              if (param == WrV)
                //              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"Unexpected case for channel: %d, delta: %d.\n", Channel, Delta);
              }
              if (MinTested[Channel][chByte] < MaxTested[Channel][chByte]) {
                TwoFail[Channel] |= (BitMask);
              }
              if (Delta <= 0) {
                TwoPass[Channel] &= ~(BitMask);
              }
            } else {
              MRC_DEBUG_ASSERT(FALSE, Debug, "Error: Testing points other than Max/MinTested");
            }
            // FIND MAX Saturation limit
            byteMax = MaxMargin;
            if ((param == RdT) || (param == RdV) || (param == RcvEnaX)) {
              byteMax = MrcCalcMaxRxMargin(MrcData, param, Channel, RankRx, byte, sign, MaxMargin);
            } else if ((param == CmdV) || DimmVrefParam) {
              byteMax = MrcCalcMaxVrefMargin(MrcData, Channel, RankRx, byte, param, sign, MaxMargin, FALSE);
            }
            if (Interior && InitValue[Channel][byte] == Margin) {
              byteMax = Margin;
            }
            // HANDLE MAX Saturation
            if (Margin == byteMax) {
              TwoFail[Channel] |= (BitMask);
            }
            if (ErrCount == 0 && byteMax == LastPassVref[Channel][byte] && (TwoPass[Channel] & (BitMask)) != 0) {
              Errors[Channel][byte] = MrcBitSwap(Errors[Channel][byte], 0xFFFE, 16, 16);
            }
            // HANDLE MIN Saturation
            if (Margin == 0) {
              TwoPass[Channel] |= (BitMask);
              if (ErrCount > 0) {
                TwoFail[Channel] |= (BitMask);
                LastPassVref[Channel][byte] = 0;
                Errors[Channel][byte] = MrcBitSwap(
                  Errors[Channel][byte],
                  (BER_LOG_TARGET << 8) + BER_LOG_TARGET,
                  16,
                  16
                  );
              }
            }
            // DECIDE WHAT TO TEST NEXT
            // If In PerByte, Do this within the for byte loop
            if (PerCh == FALSE) {
              // Skip if this Byte Group is done
              if ((TwoPass[Channel] & TwoFail[Channel] & (BitMask)) != 0) {
                continue;
              }
              if (ErrCount == 0) {
                if ((TwoFail[Channel] & (BitMask)) == 0) {
                  // Count up to find 2 fails
                  marginByte[ResultType][Rank][Channel][byte][sign] = ++MaxTested[Channel][chByte];
                } else {
                  // Count down to find 2 passes
                  marginByte[ResultType][Rank][Channel][byte][sign] = --MinTested[Channel][chByte];
                }
              } else {
                if ((TwoPass[Channel] & (BitMask)) == 0) {
                  marginByte[ResultType][Rank][Channel][byte][sign] = --MinTested[Channel][chByte];
                } else {
                  marginByte[ResultType][Rank][Channel][byte][sign] = ++MaxTested[Channel][chByte];
                }
              }
            }
          } // for byte
        } // for SubCh
        // DECIDE WHAT TO TEST NEXT
        // If In PerCh, Do this within the for ch loop
        if (PerCh == TRUE) {
          if ((TwoPass[Channel] & TwoFail[Channel]) == DoneMask) {
            continue;
          }
          if (TwoPass[Channel] != DoneMask) {
            marginByte[ResultType][Rank][Channel][0][sign] = --MinTested[Channel][chByte];
          } else {
            marginByte[ResultType][Rank][Channel][0][sign] = ++MaxTested[Channel][chByte];
          }
          // All bytes must use the same margin point
          for (byte = 0; byte < Outputs->SdramCount; byte++) {
            marginByte[ResultType][Rank][Channel][byte][sign] = marginByte[ResultType][Rank][Channel][0][sign];
          }
        }
      }
      // check if we are done
      Done = TRUE;
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if ((TwoPass[Channel] & DoneMask) != DoneMask || (TwoFail[Channel] & DoneMask) != DoneMask) {
          Done = FALSE;
          break;
        }
      }
    } while (Done == FALSE);
    // Calculate the effective margin
    // Update MarginResult with extrapolated BER Margin
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (((MRC_BIT0 << Channel) & chBitmask) == 0) {
        continue;
      }
      for (byte = 0; byte < Outputs->SdramCount; byte++) {
//        if (param == WrV)
//        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"+----->marginByte[Ch %d, Byte%d, Sign %d] is: %d\n", Channel, byte, sign,  marginByte[ResultType][Rank][Channel][byte][sign]);
        if (EnBER) {
          marginByte[ResultType][Rank][Channel][byte][sign] = interpolateVref (
                                                                LastPassVref[Channel][byte],
                                                                (Errors[Channel][byte] >> 16) & 0xFF,
                                                                (Errors[Channel][byte] >> 24) & 0xFF,
                                                                BER_LOG_TARGET,
                                                                BERStats
                                                                );
//          if (param == WrV)
//          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"+----->BERmarginByte[Ch %d, Byte%d, Sign %d] is: %d\n", Channel, byte, sign,  marginByte[ResultType][Rank][Channel][byte][sign]);
        } else {
          marginByte[ResultType][Rank][Channel][byte][sign] = 10 * LastPassVref[Channel][byte];
//          if (param == WrV)
//          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"+----->marginByte(%s)[Ch%d, Rank%d, Byte%d, Sign%d] is: %d\n", gResTypeStr[GetMarginResultType (param)], Channel, Rank, byte, sign,  marginByte[ResultType][Rank][Channel][byte][sign]);
        }
      }
    }
  }
  // Clean up after step
  Status = ChangeMargin (MrcData, param, 0, 0, 1, 0, 0, 0, 0, 0, 0);
  if (Ddr4 && (param == WrV)) {
    // If eye < 4 dont program PDA and leave it
    // Calc min eye
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!((0x1 << Channel) & chBitmask)) {
        continue;
      }
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MinEyeFlag = TRUE;
        for (Edge = 0; Edge < MAX_EDGES; Edge++) {
          // Rank here is result/first rank
          if (marginByte[ResultType][Rank][Channel][Byte][Edge] < 40) {
            MinEyeFlag = FALSE;
            break;
          }
        }
        if (MinEyeFlag) {
          // Program PDA only in case of healthy eye per Byte.
          Status = ChangeMargin (MrcData, param, 0, 0, 0, Channel, RankIn, 1 << Byte, 0, 0, 0);
        }
      }
    }
    // need to reference the margins to their real center per byte
    GetPdaMargins (MrcData, Outputs->MarginResult, param, RankIn & Outputs->ValidRankMask);
  }

  return Status;
}

/**
  Assume REUT test has already been fully setup to run
  Finds the margin for all channels/all bytes
  The margin sweep is parameterized
  Uses ChangeMargin function to handle a variety of cases (Timing, Voltage, Fan, etc.)
  mode allows for different types of modes for margining:
  mode is {Bit0: PhLock (keep all bytes within in ch in phase),
  Bit1: Ch2Ch Data out of phase (LFSR seed), Bit 15:2: Reserved}
  marginCh is used as the starting point for the search (10x the actual margin)
  marginch returns the results (10x the actual margin)
  Interior: Search inside marginch limits, enabling multiple calls with different setups
  To reduce repeatibility noise, the returned margins is actually a BER extrapolation

  @param[in]     MrcData   - The global MrcData
  @param[in,out] marginCh  - Data structure with the latest margin results
  @param[in]     chBitmask - Bit mask of present channels
  @param[in]     RankRx    - Ranks for Rx margin and Tx Vref (Ddr4)
  @param[in]     RankIn    - Rank to change margins for
  @param[in]     param     - parameter to get margins for
  @param[in]     mode      - allows for different types of modes for margining:
  @param[in]     EnBER     - Enable BER extrapolation calculations
  @param[in]     MaxMargin - Max Margin allowed for the parameter
  @param[in]     Interior  - Search inside marginch limits, enabling multiple calls with different setups
  @param[in,out] BERStats  - Bit Error Rate Statistics.

  @retval mrcSuccess if successful, otherwise returns an error status.
**/
MrcStatus
MrcGetBERMarginCh (
  IN     MrcParameters   *MrcData,
  IN     UINT32          marginCh[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN OUT UINT8           chBitmask,
  IN     UINT8           RankRx,
  IN     UINT8           RankIn,
  IN     UINT8           param,
  IN     UINT16          mode,
  IN     UINT8           EnBER,
  IN     UINT8           MaxMargin,
  IN     UINT8           Interior,
  IN OUT UINT32          *BERStats
  )
{
  const MrcInput  *Inputs;
  MrcDebug        *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput       *Outputs;
  MrcIntOutput    *MrcIntData;
  MrcStatus       Status;
  UINT8           ResultType;
  UINT8           sign;
  INT8            rSign;
  UINT8           Points2D;
  UINT8           Channel;
  UINT8           SubCh;
  UINT8           byte;
  UINT8           ByteCount;
  UINT8           SkipWait;
  UINT8           byteMax[MAX_CHANNEL];
  UINT8           Margin;
  // Set to 1 after ch has 2 passing points
  UINT16          TwoPass[MAX_CHANNEL];
  // Set to 1 after ch has 2 failing points
  UINT8           TwoFail[MAX_CHANNEL];
  INT8            Delta;
  BOOLEAN         Done;
  BOOLEAN         DimmVrefParam;
  UINT32          value0;
  UINT32          value1;
  UINT32          tmp;
  UINT8           chError;
  UINT32          ErrCount;
  UINT32          ErrCountLocal;
  UINT8           LastPassVref[MAX_CHANNEL];  // Last passing Vref
  UINT8           MaxTested[MAX_CHANNEL];     // Highest Vref Point Tested
  UINT8           MinTested[MAX_CHANNEL];     // Lowest Vref Point Tested
  // Log8(Error count) at different Vref Points. 32 bit number that is broken in 4 bytes
  // [LastPass+2, LastPass+1, LastPass, LastPass-1]
  UINT32          Errors[MAX_CHANNEL];
  BOOLEAN         PerMc;
  UINT8           McChannel;
  UINT8           Rank;
  BOOLEAN         Lpddr4;
  BOOLEAN         Ddr4;
  BOOLEAN         Overflow;
  UINT16          ByteMask;
  //REUT_GLOBAL_CTL_STRUCT  ReutGlobalCtl; //@todo <ICL> Update to CPGC 2.0 implementation

  Inputs     = &MrcData->Inputs;
  MrcCall    = Inputs->Call.Func;
  Outputs    = &MrcData->Outputs;
  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Debug      = &Outputs->Debug;
  Status     = mrcSuccess;
  ResultType = GetMarginResultType(param);
  Points2D   = (param / 16) + 1;        // 2 for Fan2 and 3 for Fan3
  McChannel  = 0;
  Lpddr4     = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  Ddr4       = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Rank = GetRankToStoreResults(MrcData, RankIn);
  // Make sure we cover all DIMM Vref cases
  DimmVrefParam = ((param == WrFan2) || (param == WrFan3) || (param == WrV));   // WrFan not defined
  PerMc         = (param == CmdV) && (MrcCountBitsEqOne (chBitmask) >= 2) && (!Ddr4) && (!Lpddr4);
  ByteCount     = (param == CmdV) ? 1 : Outputs->SdramCount;
  // Run through margin test
  for (sign = 0; sign < 2; sign++) {
    rSign = (INT8) ((2 * sign) - 1);
//    if (DimmVrefParam)
//    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"+----->rsign: %d \n", rSign);
    MrcCall->MrcSetMem ((UINT8 *) TwoPass, sizeof (TwoPass), 0);
    MrcCall->MrcSetMem ((UINT8 *) TwoFail, sizeof (TwoFail), 0);
    // Initialize variables
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      // Set default of all variables
      byteMax[Channel]      = MaxMargin;
      LastPassVref[Channel] = 0x7F;  // Start with a huge unsigned numer - 128
      Errors[Channel]       = 0;
      MinTested[Channel]    = 0;
      MaxTested[Channel]    = 0;
      if (((MRC_BIT0 << Channel) & chBitmask) == 0) {
        TwoPass[Channel] = 1;
        TwoFail[Channel] = 1;
        continue;
      }
      // Find MaxMargin for this channel
      if (param == RdT || (param == RdV)) {
        for (byte = 0; byte < Outputs->SdramCount; byte++) {
          byteMax[Channel] = MrcCalcMaxRxMargin (MrcData, param, Channel, RankRx, byte, sign, byteMax[Channel]);
        }
      } else if ((param == CmdV) || DimmVrefParam) {
        byteMax[Channel] = MrcCalcMaxVrefMargin (MrcData, Channel, RankIn, 0, param, sign, byteMax[Channel], FALSE);
      }
      // Scale back variables to normal margins and check saturation
      marginCh[ResultType][Rank][Channel][0][sign] = marginCh[ResultType][Rank][Channel][0][sign] / 10;
      if (marginCh[ResultType][Rank][Channel][0][sign] > byteMax[Channel]) {
        marginCh[ResultType][Rank][Channel][0][sign] = byteMax[Channel];
      }
      // If PerMC, all channels should start with the lowest margin across all the channel
      if (PerMc) {
        if (marginCh[ResultType][Rank][McChannel][0][sign] > marginCh[ResultType][Rank][Channel][0][sign]) {
          marginCh[ResultType][Rank][McChannel][0][sign] = marginCh[ResultType][Rank][Channel][0][sign];
        }
      }
      MinTested[Channel]  = (UINT8) marginCh[ResultType][Rank][Channel][0][sign];
      MaxTested[Channel]  = MinTested[Channel];
      for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
        // Setup REUT Error Counters to count errors per channel
        MrcSetupErrCounterCtl (MrcData, Channel, SubCh, 0, ErrCounterCtlAllLanes);
      } // for SubCh
    } // for Channel
    // If PerMC, set all channels to use margin associated with mcChannel = 0
    if (PerMc) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (((MRC_BIT0 << Channel) & chBitmask) == 0) {
          continue;
        }
        marginCh[ResultType][Rank][Channel][0][sign] = marginCh[ResultType][Rank][McChannel][0][sign];
        MinTested[Channel] = (UINT8) marginCh[ResultType][Rank][McChannel][0][sign];
        MaxTested[Channel] = MinTested[Channel];
      }
    }
    // Search algorithm:
    // If start with a passing point, walk to hit 2 failing points
    //    Return as needed to hit a second passing point
    // If start with a failing point, walk to hit 2 passing points
    //    Return as needed to hit a second failing point
    // Keep testing until all ch/bytes find 2 passes and 2 fails
    Done = FALSE;
    do {
      // Walk through all 2D points
/** @todo <ICL>: Implement CPGC 2.0 to clear errors
      ReutGlobalCtl.Data = 0;
      ReutGlobalCtl.Bits.Global_Clear_Errors = 1;
      MrcWriteCR (MrcData, REUT_GLOBAL_CTL_REG, ReutGlobalCtl.Data);  // Clear errors
**/
      chError = 0;
      for (value1 = 0; value1 < Points2D; value1++) {
        // Set Vref level
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (((MRC_BIT0 << Channel) & chBitmask) == 0) {
            continue;
          }
          SkipWait = (chBitmask >> (Channel + 1)); // Skip if there are more channels
          value0 = rSign * marginCh[ResultType][Rank][Channel][0][sign];
//          if (DimmVrefParam) {
//            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "+----->Value0 is %d, Value1 is %d\n", (INT32) value0, value1);
//            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "+----->marginCh is %d\n", marginCh[ResultType][Rank][Channel][0][sign]);
//          }
          for (byte = 0; byte < ByteCount; byte++) {
            Status = ChangeMargin (
                      MrcData,
                      param,
                      value0,
                      value1,
                      0,
                      Channel,
                      RankIn,
                      byte,
                      0,
                      0,
                      SkipWait
                      );
          }
          if (PerMc) {
            break; // Just update once
          }
        }
        // Run Test
        chError |= RunIOTest (MrcData, chBitmask, Outputs->DQPat, (value1 == 0), 0);
        if (param == CmdV) {
          MrcResetSequence (MrcData);
        }
        // check if we have already failed and can stop running
        if (EnBER == 0 && value1 < (UINT32) (Points2D - 1) && chError == chBitmask) {
          break;
        }
        // Collect results and Update variables for next point to test
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if ((TwoPass[Channel] == 1 && TwoFail[Channel] == 1) || ((MRC_BIT0 << Channel) & chBitmask) == 0) {
            continue;
          }
          McChannel = (PerMc) ? 0 : Channel;
          // Read Error Count
          ErrCount = 0;
          for (SubCh = 0; SubCh < MrcIntData->SubChEngCount; SubCh++) {
            if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
              MrcGetErrCounterStatus (MrcData, Channel, SubCh, 0, ErrCounterCtlAllLanes, &ErrCountLocal, &Overflow);
              // Add up errors from both subch in LP4
              // In DDR4 we read errors from subch0 only
              ErrCount += ErrCountLocal;
            }
          }
          Margin                      = (UINT8) marginCh[ResultType][Rank][Channel][0][sign];
          Delta                       = (Margin - LastPassVref[Channel]);
          // Update Pass/Fail Variables:
          if (ErrCount == 0 && Margin == MaxTested[McChannel]) {
            // Passing while walking up
            if (Delta < 0) {
              // First passing point
              MRC_DEBUG_ASSERT (
                MinTested[McChannel] == MaxTested[McChannel],
                Debug,
                "Error: MaxTested < LastPass after first point"
                );
              LastPassVref[Channel] = Margin;
            } else if (Delta == 1) {
              // Normal, walk to fail
              Errors[Channel]       = MrcBitShift (Errors[Channel], -8 * Delta) & BER_ERROR_MASK;
              LastPassVref[Channel] = Margin;
              TwoPass[Channel]      = 1;
            } else if (Delta == 2) {
              // Speckling in response, Consider point as error
              Errors[Channel]   = MrcBitSwap (Errors[Channel], MrcLog8 (ErrCount), 24, 8);
              TwoFail[Channel]  = 1;
            } else {
              MRC_DEBUG_ASSERT (FALSE, Debug, "Error: Tested point twice or Tested >2 above LastPass");
            }
          } else if (ErrCount == 0 && Margin == MinTested[McChannel]) {
            if (TwoPass[Channel] == 1) {
              continue; // Skip if this channel is already done
            }
            // Passing while walking down
            if (Delta == -1) {
              Errors[Channel]  = MrcBitSwap (Errors[Channel], 0, 0, 8);
              TwoPass[Channel] = 1;     // found second pass
            } else {
              // 1st passing point
              // Don't shift errors.  Fail points already assumed correct
              LastPassVref[Channel] = Margin;
              TwoPass[Channel]      = 0;
            }
          } else if (ErrCount > 0 && Margin == MaxTested[McChannel]) {
            // Failing while walking up
            MRC_DEBUG_ASSERT (Delta <= 2, Debug, "Error: Tested >2 above LastPass");
            if (Delta < 2) {
              // first failing point
              Errors[Channel]   = MrcBitSwap (Errors[Channel], MrcLog8 (ErrCount), 16, 8);
              TwoFail[Channel]  = 0;
            } else if (Delta == 2) {
              // 2nd failing point
              Errors[Channel]   = MrcBitSwap (Errors[Channel], MrcLog8 (ErrCount), 24, 8);
              TwoFail[Channel]  = 1;
            }
          } else if (ErrCount > 0 && Margin == MinTested[McChannel]) {
            // Failing while walking down
            if (LastPassVref[Channel] < 0xFF && Delta <= 0) {
              // Adjust LastPassVref and Error count to be below this failure point
              Errors[Channel]       = MrcBitSwap (Errors[Channel], MrcLog8 (ErrCount), 8 * (Delta + 1), 8);
              Errors[Channel]       = MrcBitShift (Errors[Channel], 8 * (1 - Delta));
              LastPassVref[Channel] = Margin - 1;
            } else {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Unexpected case for channel: %d, delta: %d.\n", Channel, Delta);
              tmp             = ((Errors[Channel] & 0xFF0000) >> 8) + MrcLog8 (ErrCount);
              Errors[Channel] = MrcBitSwap (Errors[Channel], tmp, 16, 16);
            }
            if (MinTested[McChannel] < MaxTested[McChannel]) {
              TwoFail[Channel] = 1;
            }
            if (Delta <= 0) {
              TwoPass[Channel] = 0;
            }
          } else {
            MRC_DEBUG_ASSERT (FALSE, Debug, "Error: Testing points other than Max/MinTested");
          }
          // Find Max Saturation limit
          if (Interior && MaxTested[Channel] == Margin) {
            byteMax[Channel] = Margin;
          }
          // Handle Max Saturation
          if (Margin == byteMax[Channel]) {
            TwoFail[Channel] = 1;
          }
          if (ErrCount == 0 && byteMax[Channel] == LastPassVref[Channel] && TwoPass[Channel] == 1) {
            Errors[Channel] = MrcBitSwap (Errors[Channel], 0xFFFE, 16, 16);
          }
          // Handle Min Saturation
          if (Margin == 0) {
            TwoPass[Channel] = 1;
            if (ErrCount > 0) {
              TwoFail[Channel]      = 1;
              LastPassVref[Channel] = 0;
              Errors[Channel]       = MrcBitSwap (Errors[Channel], (BER_LOG_TARGET << 8) + BER_LOG_TARGET, 16, 16);
            }
          }
          // Decide what to test next for PerMC == FALSE
          if (!PerMc) {
            if (TwoPass[Channel] == 1) {
              if (TwoFail[Channel] == 1) {
                continue;
              }
              //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"++---->MaxTested[Ch] before ++:%d\n", MaxTested[Channel]);////////
              marginCh[ResultType][Rank][Channel][0][sign] = ++MaxTested[Channel];
            } else {
              //            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"++---->MinTested[Ch] before --:%d\n", MinTested[Channel]);////////
              marginCh[ResultType][Rank][Channel][0][sign] = --MinTested[Channel];
            }
          }
        }
        // Decide what to test next for PerMC == TRUE
        if (PerMc) {
          if ((TwoPass[0] == 1) && (TwoPass[1] == 1)) {
            // All Channels have 2 passes
            if ((TwoFail[0] == 1) && (TwoFail[1] == 1)) {
              // All Channels have 2 fails
              continue;
            }
            //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"++---->MaxTested[Ch] before ++:%d\n", MaxTested[Channel]);////////
            marginCh[ResultType][Rank][McChannel][0][sign] = ++MaxTested[McChannel];
          } else {
            //            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"++---->MinTested[Ch] before --:%d\n", MinTested[Channel]);////////
            marginCh[ResultType][Rank][McChannel][0][sign] = --MinTested[McChannel];
          }
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            if (((MRC_BIT0 << Channel) & chBitmask) == 0) {
              continue;
            }
            marginCh[ResultType][Rank][Channel][0][sign] = marginCh[ResultType][Rank][McChannel][0][sign];
            MinTested[Channel] = MinTested[McChannel];
            MaxTested[Channel] = MaxTested[McChannel];
          }
        }
      }
      // check if we are done
      Done = TRUE;
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (TwoPass[Channel] == 0 || TwoFail[Channel] == 0) {
          Done = FALSE;
          break;
        }
      }
    } while (Done == FALSE);
    // Calculate the effective margin
    // Update marginch with extroploated BER Margin
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (((MRC_BIT0 << Channel) & chBitmask) == 0) {
        continue;
      }
      //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE,"+----->marginCh[%d,%d] is: %d\n", Channel, sign,  marginCh[ResultType][Rank][Channel][0][sign]);
      if (EnBER) {
        marginCh[ResultType][Rank][Channel][0][sign] = interpolateVref (
                                                        LastPassVref[Channel],
                                                        (Errors[Channel] >> 16) & 0xFF,
                                                        (Errors[Channel] >> 24) & 0xFF,
                                                        BER_LOG_TARGET,
                                                        BERStats
                                                        );
        // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "+----->BERmarginCh[%d,%d] is: %d, Errors = 0x%x\n", Channel, sign,  marginCh[ResultType][Rank][Channel][0][sign], Errors[Channel]);
      } else {
        marginCh[ResultType][Rank][Channel][0][sign] = 10 * LastPassVref[Channel];
        //MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "+----->marginCh[%d,%d] is: %d\n", Channel, sign,  marginCh[ResultType][Rank][Channel][0][sign]);
      }
    }
  }
  // Clean up after step
  ByteMask = ((param == WrV) && Ddr4) ? 0x1FF: 0;
  Status = ChangeMargin (MrcData, param, 0, 0, 1, 0, 0, ByteMask, 0, 0, 0);
  return Status;
}

/**
  Check whether there is errors at Point RdT/RdV or WrT/WrV

  @param[in]      MrcData     - Include all MRC global data.
  @param[in]      chBitmask   - Bit mask of present channels
  @param[in]      RankMask    - Bit mask of Ranks to change margins for
  @param[in]      MarginPoint - Margin Point to test

  @retval MrcStatus - mrcSuccess if point successful pass, otherwise returns an error status.
**/
MrcStatus
MrcDataPointTest (
  IN     MrcParameters     *MrcData,
  IN     UINT8             chBitMask,
  IN     UINT8             RankMask,
  IN     MarginCheckPoint  *MarginPoint
  )
{
  MrcOutput           *Outputs;
  MrcDebug            *Debug;
  MrcStatus           Status;
  UINT8               Channel;
  UINT8               byte;
  UINT8               ChError;
  UINT16              ByteMask;
  BOOLEAN             Ddr4;
  UINT8               SkipWait;
  UINT8               Max;
  INT32               Min;
  INT64               GetSetVal;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Ddr4    = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

  // Check to make sure type is RdT/RdV or WrT/WrV
  if ( !(((MarginPoint->VoltageType == RdV) && (MarginPoint->TimingType == RdT)) ||
         ((MarginPoint->VoltageType == WrV) && (MarginPoint->TimingType == WrT)))) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Function MrcDataPointTest, Invalid combination TimingType: %d VoltageType:%d\n",
                     MarginPoint->TimingType, MarginPoint->VoltageType);
    return mrcWrongInputParameter;
  }

  // Change margin before the test
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (((MRC_BIT0 << Channel) & chBitMask) == 0) {
      continue;
    }
    SkipWait = (chBitMask >> (Channel + 1)); // Skip if there are more channels

    for (byte = 0; byte < Outputs->SdramCount; byte++) {
      // Change voltage margin
      ChangeMargin (MrcData, MarginPoint->VoltageType, MarginPoint->VoltageMargin, 0, 0, Channel, RankMask, byte, 0, 0, 0);

      // For changing RdT margin, Do not use ChangeMargin.
      // ChangeMargin reads cache then writes to register. RdT and RdV share the same register
      // you will overwrite the RdV. Instead, we read the register then write to the register.
      if (MarginPoint->TimingType == RdT) {
        Max = GetMaxPossibleTimingOffset (MrcData, RdT);
        Min = (-1) - Max;
        GetSetVal = RANGE (MarginPoint->TimingMargin, Min, Max);
        MrcGetSetDdrIoGroupStrobe (MrcData, Channel, MRC_IGNORE_ARG, byte, RxDqsOffset, ReadForceWriteNoCache, &GetSetVal);
      } else {
        ChangeMargin (MrcData, MarginPoint->TimingType, MarginPoint->TimingMargin, 0, 0, Channel, RankMask, byte, 0, 0, SkipWait);
      }
    }
  }

  // Run Test
  ChError = RunIOTest (MrcData, chBitMask, Outputs->DQPat, 1, 0);

  // Set whether it passed/failed
  Status = (ChError > 0) ? mrcFail : mrcSuccess;

  // Clean up timing
  ChangeMargin (MrcData, MarginPoint->TimingType, 0, 0, 1, 0, 0, 0, 0, 0, 0);

  // Clean up voltage
  ByteMask = ((MarginPoint->VoltageType == WrV) && Ddr4) ? 0x1FF: 0;
  ChangeMargin (MrcData, MarginPoint->VoltageType, 0, 0, 1, 0, 0, ByteMask, 0, 0, 0);

  return Status;
}

/**
  Check whether there is errors at Point CmdT/CmdV

  @param[in]      MrcData     - Include all MRC global data.
  @param[in]      chBitmask   - Bit mask of present channels
  @param[in]      RankMask    - Bit mask of Ranks to change margins for
  @param[in]      GroupMask   - Which groups to work on for CLK/CMD/CTL. Up to 4 CMD for LPDDR4.  Up to 5 CMD for DDR4.
  @param[in]      MarginPoint - CMD Margin Point to test

  @retval MrcStatus - mrcSuccess if point successful pass, otherwise returns an error status.
**/
MrcStatus
MrcCmdPointTest (
  IN     MrcParameters    *MrcData,
  IN     UINT8            chBitMask,
  IN     UINT8            RankMask,
  IN     UINT8            GroupMask,
  IN     MarginCheckPoint *MarginPoint
  )
{
  MrcOutput           *Outputs;
  MrcDebug            *Debug;
  MrcStatus           Status;
  UINT8               Channel;
  UINT8               ChError;
  UINT8               SkipWait;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  // Check to make sure type is CmdT/CmdV
  if((MarginPoint->VoltageType != CmdV) || (MarginPoint->TimingType != CmdT)) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Function MrcCmdPointTest, Invalid combination TimingType: %d VoltageType:%d\n",
                     MarginPoint->TimingType, MarginPoint->VoltageType);

    return mrcWrongInputParameter;
  }

  // Change CmdV before the test
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (((MRC_BIT0 << Channel) & chBitMask) == 0) {
      continue;
    }
    SkipWait = (chBitMask >> (Channel + 1)); // Skip if there are more channels

    // Change CmdV Margin
    ChangeMargin (MrcData, MarginPoint->VoltageType, MarginPoint->VoltageMargin, 0, 0, Channel, RankMask, 0, 0, 0, SkipWait);

    // Change CmdT before the test
    ShiftPIforCmdTraining (MrcData, Channel, MrcIterationClock, RankMask, GroupMask, MarginPoint->TimingMargin, 0);
  }

  // Reset DDR after changing the CLK PI
  MrcResetSequence (MrcData);

  // Run CPGC test on both channels
  ChError = RunIOTest (MrcData, chBitMask, Outputs->DQPat, 1, 0);

  // Set whether it passed/failed
  Status = (ChError > 0) ? mrcFail : mrcSuccess;

  // Restore centered value for CmdT
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if ((1 << Channel) & chBitMask) {
      ShiftPIforCmdTraining (MrcData, Channel, MrcIterationClock, RankMask, GroupMask, 0, 1);
    }
  }

  // Clean up CmdV
  ChangeMargin (MrcData, MarginPoint->VoltageType, 0, 0, 1, 0, 0, 0, 0, 0, 0);

  MrcResetSequence (MrcData);

  return Status;
}

/**
  This function shifts a 32 bit int either positive or negative

  @param[in] Value       - Input value to be shifted
  @param[in] ShiftAmount - Number of bits places to be shifted.

  @retval 0 if ShiftAmount exceeds +/- 31.  Otherwise the updated 32 bit value.
**/
UINT32
MrcBitShift (
  IN const UINT32 Value,
  IN const INT8  ShiftAmount
  )
{
  if ((ShiftAmount > 31) || (ShiftAmount < -31)) {
    return 0;
  }

  if (ShiftAmount > 0) {
    return Value << ShiftAmount;
  } else {
    return Value >> (-1 * ShiftAmount);
  }
}

/**
  This function Sign extends OldMSB to NewMSB Bits (Eg: Bit 6 to Bit 7)

  @param[in] CurrentValue - Input value to be shifted
  @param[in] OldMSB       - The original most significant Bit
  @param[in] NewMSB       - The new most significant bit.

  @retval The updated 8 bit value.
**/
UINT8
MrcSE (
  IN UINT8     CurrentValue,
  IN const UINT8 OldMSB,
  IN const UINT8 NewMSB
  )
{
  UINT8 Scratch;

  Scratch = ((MRC_BIT0 << (NewMSB - OldMSB)) - 1) << OldMSB;
  if (CurrentValue >> (OldMSB - 1)) {
    CurrentValue |= Scratch;
  } else {
    CurrentValue &= (~Scratch);
  }

  return CurrentValue;
}

/**
  This function calculates the Log base 2 of the value to a maximum of Bits

  @param[in] Value - Input value

  @retval Returns the log base 2 of input value + 1.
**/
UINT8
MrcLog2 (
  IN const UINT32 Value
  )
{
  UINT8 Log;
  UINT8 Bit;

  // Return 0 if value is negative
  Log = 0;
  if ((Value + 1) != 0) {
    for (Bit = 0; Bit < 32; Bit++) {
      if (Value & (0x1 << Bit)) {
        Log = (Bit + 1);
      }
    }
  }

  return Log;
}

/**
  This function calculates the power of integer numbers.

  @param[in] Value - Input value.
  @param[in] Power - the power to raise the Value to

  @retval Returns (Value ^ Power) * 100
**/
UINT32
MrcPercentPower (
  IN const UINT32 Value,
  IN UINT32    Power
  )
{
  UINT32  Result;

  Result = 100;
  while (Power--) {
    Result *= Value;
    if (Result != Value) { // normalize to percent
      Result /= 100;
    }
  }

  return Result;
}

/**
  This function search for item in a list and return index + 1 or 0 in not found

  @param[in] Param - Param to search for
  @param[in] ParamList - list of Params
  @param[in] ParamLen - Params length
  @param[in] Offset - list of the corresponded Offsets to work on
  @param[out] Override - override indicator
  @param[out] LocalOffset - localoffset
  @retval Returns result
**/
UINT8
MrcSearchList(
  IN           UINT8           Param,
  IN     const UINT8           *ParamList,
  IN     const UINT8           ParamLen,
  IN     const INT8            *Offset,
  OUT          BOOLEAN         *Override,
  OUT          INT8            *LocalOffset
)
{
  UINT8 Result = 0;
  UINT8 Idx;

  for (Idx = 0; Idx < ParamLen; Idx ++) {
    if (ParamList[Idx] == Param) {
      Result = Idx + 1;
      break;
    }
  }
  if (Result == 0) {
    *Override = FALSE;
    *LocalOffset = 0;
  } else {
    *Override = TRUE;
    *LocalOffset = Offset[ Result - 1 ];
  }
  return Result;
}

/**
  ***** Has Buffer Overflow for 68-71, 544-575, 4352-4607, ... ****
  This function calculates the Log base 8 of the Input parameter using integers

  @param[in] Value - Input value

  @retval Returns 10x the log base 8 of input Value
**/
UINT32
MrcLog8 (
  IN UINT32 Value
  )
{
  static const UINT8 Loglook[18] = { 0, 0, 1, 2, 3, 4, 5, 6, 7, 7, 8, 8, 9, 9, 9, 10, 10, 10 };
  UINT32    Loga;
  UINT32    Rema;

  Loga  = 0;
  Rema  = 2 * Value;
  while (Value > 8) {
    Rema  = Value >> 2;
    Value = Value >> 3;
    Loga += 10;
  };

  return (Loga + Loglook[Rema]); //returns an integer approximation of "log8(a) * 10"
}

/**
  This function Sorts Arr from largest to smallest

  @param[in,out] Arr     - Array to be sorted
  @param[in]     Channel - Channel to sort.
  @param[in]     lenArr  - Length of the array

  @retval Nothing
**/
void
MrcBsortPerChannel (
  IN OUT UINT32   Arr[MAX_CHANNEL][4],
  IN     const UINT8 Channel,
  IN     const UINT8 lenArr
  )
{
  UINT8 i;
  UINT8 j;
  UINT32 temp;

  for (i = 0; i < lenArr - 1; i++) {
    for (j = 0; j < lenArr - (1 + i); j++) {
      if (Arr[Channel][j] < Arr[Channel][j + 1]) {
        temp                = Arr[Channel][j];
        Arr[Channel][j]     = Arr[Channel][j + 1];
        Arr[Channel][j + 1] = temp;
      }
    }
  }

  return;
}

/**
  This function Sorts Arr from largest to smallest

  @param[in,out] Arr    - Array to be sort
  @param[in]     lenArr - Lenght of the array

  @retval Nothing
**/
void
MrcBsort (
  IN OUT UINT32 *const Arr,
  IN     const UINT8 lenArr
  )
{
  UINT8 i;
  UINT8 j;
  UINT32 temp;

  for (i = 0; i < lenArr - 1; i++) {
    for (j = 0; j < lenArr - (1 + i); j++) {
      if (Arr[j] < Arr[j + 1]) {
        temp        = Arr[j];
        Arr[j]      = Arr[j + 1];
        Arr[j + 1]  = temp;
      }
    }
  }

  return;
}

/**
  This function calculates the Natural Log of the Input parameter using integers

  @param[in] Input - 100 times a number to get the Natural log from.
                      Max Input Number is 40,000 (without 100x)

  @retval 100 times the actual result. Accurate within +/- 2
**/
UINT32
MrcNaturalLog (
  UINT32 Input
  )
{
  UINT32 Output;

  Output = 0;
  while (Input > 271) {
    Input = (Input * 1000) / 2718;
    Output += 100;
  }

  Output += ((-16 * Input * Input + 11578 * Input - 978860) / 10000);

  return Output;
}

/**
  This function calculates the number of bits set to 1 in a 32-bit value.

  @param[in] Input - The value to work on.

  @retval The number of bits set to 1 in Input.
**/
UINT8
MrcCountBitsEqOne (
  IN UINT32 Input
  )
{
  UINT8 NumOnes;

  NumOnes = 0;
  while (Input > 0) {
    NumOnes++;
    Input &= (Input - 1);
  }

  return NumOnes;
}

/**
  This function calculates e to the power of the Input parameter using integers.

  @param[in] Input - 100 times a number to elevate e to.

  @retval 100 times the actual result. Accurate within +/- 2.
**/
UINT32
Mrceexp (
  IN UINT32 Input
  )
{
  UINT32 Extra100;
  UINT32 Output;

  Extra100  = 0;
  Output    = 1;
  while (Input > 100) {
    Input -= 100;
    Output = (Output * 2718) / 10;
    if (Extra100) {
      Output /= 100;
    }

    Extra100 = 1;
  }

  Output = ((Output * (8 * Input * Input + 900 * Input + 101000)) / 1000);

  if (Extra100) {
    Output /= 100;
  }

  return Output;
}

/**
  This function writes a 32 bit register.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Offset  - Offset of register from MchBar Base Address.
  @param[in] Value   - Value to write.

  @retval The register value.
**/
UINT32
MrcWriteCrMulticast (
  IN MrcParameters *const MrcData,
  IN const UINT32         Offset,
  IN const UINT32         Value
  )
{
  const MRC_FUNCTION *MrcCall;
  const MrcInput     *Inputs;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  MrcData->Outputs.MchBarWriteCount++;
  MrcCall->MrcMmioWrite32 (Inputs->MchBarBaseAddress + Offset, Value);
  MRC_DEBUG_ASSERT ((Offset % 4) == 0, &MrcData->Outputs.Debug, "Invalid Offset alignment: 0x%x\n", Offset);
#ifdef MRC_DEBUG_PRINT
  if (MrcData->Outputs.Debug.PostCode[MRC_POST_CODE_WRITE] == MrcData->Outputs.Debug.PostCode[MRC_POST_CODE]) {
    MRC_DEBUG_MSG (
      &MrcData->Outputs.Debug,
      MSG_LEVEL_NOTE,
      "<mc>%04X M %08X</mc>\n",
      Offset,
      Value
      );
  }
#endif // MRC_DEBUG_PRINT
  return (Value);
}

/**
  This function writes a 64 bit register.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Offset  - Offset of register from MchBar Base Address.
  @param[in] Value   - Value to write.

  @retval The register value.
**/
UINT64
MrcWriteCR64 (
  IN MrcParameters *const MrcData,
  IN const UINT32         Offset,
  IN const UINT64         Value
  )
{
  const MRC_FUNCTION *MrcCall;
  const MrcInput     *Inputs;
  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  MrcData->Outputs.MchBarWriteCount++;
  MrcCall->MrcMmioWrite64 (Inputs->MchBarBaseAddress + Offset, Value);
  MRC_DEBUG_ASSERT ((Offset % 8) == 0, &MrcData->Outputs.Debug, "Invalid Offset alignment: 0x%x\n", Offset);
#ifdef MRC_DEBUG_PRINT
  if (MrcData->Outputs.Debug.PostCode[MRC_POST_CODE_WRITE] == MrcData->Outputs.Debug.PostCode[MRC_POST_CODE]) {
    MRC_DEBUG_MSG (
      &MrcData->Outputs.Debug,
      MSG_LEVEL_NOTE,
      "<mc>%04X W %ll_X</mc>\n",
      Offset,
      Value
      );
  }
#endif // MRC_DEBUG_PRINT
  return (Value);
}

/**
  This function writes a 32 bit register.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Offset  - Offset of register from MchBar Base Address.
  @param[in] Value   - Value to write.

  @retval The register value.
**/
UINT32
MrcWriteCR (
  IN MrcParameters *const MrcData,
  IN const UINT32  Offset,
  IN const UINT32  Value
  )
{
  const MRC_FUNCTION *MrcCall;
  const MrcInput     *Inputs;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  MrcData->Outputs.MchBarWriteCount++;
  MrcCall->MrcMmioWrite32 (Inputs->MchBarBaseAddress + Offset, Value);
  MRC_DEBUG_ASSERT ((Offset % 4) == 0, &MrcData->Outputs.Debug, "Invalid Offset alignment: 0x%x\n", Offset);
#ifdef MRC_DEBUG_PRINT
  if (MrcData->Outputs.Debug.PostCode[MRC_POST_CODE_WRITE] == MrcData->Outputs.Debug.PostCode[MRC_POST_CODE]) {
    MRC_DEBUG_MSG (
      &MrcData->Outputs.Debug,
      MSG_LEVEL_NOTE,
      "<mc>%04X W %08X</mc>\n",
      Offset,
      Value
      );
  }
#endif // MRC_DEBUG_PRINT
  return (Value);
}

/**
  This function writes a 8 bit register.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Offset  - Offset of register from MchBar Base Address.
  @param[in] Value   - The value to write.

  @retval The register value.
**/
UINT8
MrcWriteCR8 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Offset,
  IN const UINT8   Value
  )
{
  const MRC_FUNCTION *MrcCall;
  const MrcInput     *Inputs;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  MrcData->Outputs.MchBarWriteCount++;
  MrcCall->MrcMmioWrite8 (MrcData->Inputs.MchBarBaseAddress + Offset, Value);
#ifdef MRC_DEBUG_PRINT
  if (MrcData->Outputs.Debug.PostCode[MRC_POST_CODE_WRITE] == MrcData->Outputs.Debug.PostCode[MRC_POST_CODE]) {
    MRC_DEBUG_MSG (
      &MrcData->Outputs.Debug,
      MSG_LEVEL_NOTE,
      "<mc>%04X W %02X</mc>\n",
      Offset,
      Value
      );
  }
#endif // MRC_DEBUG_PRINT
  return (Value);
}

/**
  This function reads a 64 bit register.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Offset  - Offset of register from MchBar Base Address.

  @retval Value read from the register.
**/
UINT64
MrcReadCR64 (
  IN MrcParameters *const MrcData,
  IN const UINT32  Offset
  )
{
  const MRC_FUNCTION *MrcCall;
  const MrcInput     *Inputs;
  UINT64             Value;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  MrcData->Outputs.MchBarReadCount++;
  Value = (MrcCall->MrcMmioRead64 (Inputs->MchBarBaseAddress + Offset));
  MRC_DEBUG_ASSERT ((Offset % 8) == 0, &MrcData->Outputs.Debug, "Invalid Offset alignment: 0x%x\n", Offset);
#ifdef MRC_DEBUG_PRINT
  if (MrcData->Outputs.Debug.PostCode[MRC_POST_CODE_READ] == MrcData->Outputs.Debug.PostCode[MRC_POST_CODE]) {
    MRC_DEBUG_MSG (
      &MrcData->Outputs.Debug,
      MSG_LEVEL_NOTE,
      "<mc>%04X R %ll_X</mc>\n",
      Offset,
      Value
      );
  }
#endif // MRC_DEBUG_PRINT
  return (Value);
}

/**
  This function reads a 32 bit register.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Offset  - Offset of register from MchBar Base Address.

  @retval Value read from the register
**/
UINT32
MrcReadCR (
  IN MrcParameters *const MrcData,
  IN const UINT32  Offset
  )
{
  const MRC_FUNCTION *MrcCall;
  const MrcInput     *Inputs;
  UINT32             Value;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  MrcData->Outputs.MchBarReadCount++;
  Value = MrcCall->MrcMmioRead32 (Inputs->MchBarBaseAddress + Offset);
  MRC_DEBUG_ASSERT ((Offset % 4) == 0, &MrcData->Outputs.Debug, "Invalid Offset alignment: 0x%x\n", Offset);
#ifdef MRC_DEBUG_PRINT
  if (MrcData->Outputs.Debug.PostCode[MRC_POST_CODE_READ] == MrcData->Outputs.Debug.PostCode[MRC_POST_CODE]) {
    MRC_DEBUG_MSG (
      &MrcData->Outputs.Debug,
      MSG_LEVEL_NOTE,
      "<mc>%04X R %08X</mc>\n",
      Offset,
      Value
      );
  }
#endif // MRC_DEBUG_PRINT
  return (Value);
}

/**
  Wait for at least the given number of nanoseconds.

  @param[in] MrcData   - Include all MRC global data.
  @param[in] DelayNs   - time to wait in [ns], up to 2^32 [ns] = 4.29 seconds

  @retval Nothing
**/
void
MrcWait (
  IN MrcParameters *const MrcData,
  IN UINT32               DelayNs
  )
{
  const MRC_FUNCTION *MrcCall;

  MrcCall = MrcData->Inputs.Call.Func;
  MrcCall->MrcDelayNs (MrcData, DelayNs);
}

/**
  This function forces an RCOMP.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess if successful, otherwise returns an error status.
**/
MrcStatus
ForceRcomp (
  IN MrcParameters *const MrcData
  )
{

  const MRC_FUNCTION        *MrcCall;
  M_COMP_PCU_STRUCT         PcuCrMComp;
  UINT64                    Timeout;
  BOOLEAN                   Flag;
  MrcInput                  *Inputs;
  MrcDebug                  *Debug;
  MrcOutput                 *Outputs;

  Outputs         = &MrcData->Outputs;
  Debug           = &Outputs->Debug;
  MrcCall         = MrcData->Inputs.Call.Func;
  PcuCrMComp.Data = MrcReadCR (MrcData, M_COMP_PCU_REG);
  PcuCrMComp.Bits.COMP_FORCE = 1;
  MrcWriteCR (MrcData, M_COMP_PCU_REG, PcuCrMComp.Data);
  Inputs          = &MrcData->Inputs;

  if (Inputs->SimicsFlag == 0) {
    Timeout = MrcCall->MrcGetCpuTime (MrcData) + 10000; // 10 seconds timeout
    do {
      PcuCrMComp.Data = MrcReadCR (MrcData, M_COMP_PCU_REG);
      Flag = (PcuCrMComp.Bits.COMP_FORCE == 1);
    } while (Flag && (MrcCall->MrcGetCpuTime (MrcData) < Timeout));

    if (Flag) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s ForceRcomp Timed Out\n", gErrString);
      return mrcFail;
    }
  }

  MrcWait (MrcData, 10 * MRC_TIMER_1US); // Wait 10 - 20 us for Comp to Complete

  return mrcSuccess;
}

/**
  This function control's entering and exiting self refresh.

  @param[in]  MrcData - Pointer to MRC global data.
  @param[in]  SelfRef - Boolean selector to enter (1/TRUE) or exit (0/FALSE) Self Refresh.

  @retval MrcStatus - mrcSuccess if we are able to transition to the requested Self Refresh State
                    - mrcFail if we timeout before MC reports we reached the requested Self Refresh state.
**/
MrcStatus
MrcSelfRefreshState (
  IN  MrcParameters *const  MrcData,
  IN  BOOLEAN               SelfRef
  )
{
  MrcDebug  *Debug;
  MrcOutput *Outputs;
  MrcStatus Status;
  INT64     GetSetVal;
  UINT64    Timeout;
  BOOLEAN   Flag;
  const MRC_FUNCTION      *MrcCall;
  STALL_DRAIN_STRUCT  StallDrain;


  MrcCall = MrcData->Inputs.Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Status  = mrcSuccess;

  GetSetVal = SelfRef;
  MrcGetSetDdrIoGroupController0 (MrcData, GsmMccEnableSr, WriteNoCache, &GetSetVal);

  Timeout = MrcCall->MrcGetCpuTime (MrcData) + 10000; // 10 seconds timeout
  do {
    StallDrain.Data = MrcReadCR (MrcData, STALL_DRAIN_REG);
    Flag = (StallDrain.Bits.sr_state != SelfRef);
  } while (Flag && (MrcCall->MrcGetCpuTime (MrcData)  < Timeout));

  if (Flag) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MC failed to %s Self-Refresh\n", (SelfRef == MRC_SR_ENTER) ? "enter" : "exit");
    Status = mrcFail;
  }

  return Status;
}

/**
  This function defines the Command pattern spread per DRAM technology.

  @param[in]  MrcData - Pointer to MRC global data

  @retval UINT8 - Number of bits in the set of the Victim Aggressor pattern.
**/
UINT8
MrcCommandSpread (
  IN  MrcParameters *const  MrcData
  )
{
  UINT8 Spread;

  switch (MrcData->Outputs.DdrType) {
    case MRC_DDR_TYPE_LPDDR4:
      Spread = 6;
      break;

    case MRC_DDR_TYPE_DDR4:
    default:
      Spread = 6;
      break;
  }

  return Spread;
}

/**
  Fill WDB with the given fixed pattern.
  In Enhanced Channel Mode only entry [0] of each chunk will be used (low 32 bit).

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Pattern  - Array of chunks (64 bit), broken into two 32-bit entries (second dimension).
                        Length (first dimension) can be up to NUM_DPAT_EXTBUF
  @retval Nothing
**/
void
WriteFixedPattern (
  IN MrcParameters *const  MrcData,
  IN UINT32                Pattern[][2]
  )
{
  UINT32         *ExtBufPtr;
  MrcIntOutput   *MrcIntData;
  UINT8          ChanSubChanMask;
  UINT8          Channel;
  UINT8          SubChannel;
  UINT8          Index;
  UINT32         Offset;

  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  ChanSubChanMask = MrcIntData->ChSubChMaskEnable;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (SubChannel = 0; SubChannel < MrcIntData->SubChEngCount; SubChannel++) {
      if (SUB_CH_MASK_CHECK (ChanSubChanMask, Channel, SubChannel) == 0) {
        continue;
      }
      // Program ExtBuf
      Offset = OFFSET_CALC_CH_SUBCH (
                CH0_SC0_CR_CPGC_DPAT_EXTBUF_0_REG,
                CH1_SC0_CR_CPGC_DPAT_EXTBUF_0_REG, Channel,
                CH0_SC1_CR_CPGC_DPAT_EXTBUF_0_REG, SubChannel);
      for (Index = 0; Index < CPGC_20_NUM_DPAT_EXTBUF; Index++) {
        ExtBufPtr = &Pattern[Index / 2][Index % 2];
        MrcWriteCR (MrcData, Offset, *ExtBufPtr);
        //Adjust Offset for next EXTBUF
        Offset += (CH0_SC0_CR_CPGC_DPAT_EXTBUF_1_REG - CH0_SC0_CR_CPGC_DPAT_EXTBUF_0_REG);
      }
    }
  }
  return;
}

/**
  This routine performs the following steps:
    Step 0: Iterate through all VicRots
    Step 1: Create a compressed vector for a given 32 byte cacheline
            Each byte has a value of LFSR0=AA/LFSR1=CC/LFSR2=F0
    Step 2: Expand compressed vector into chunks and 32 bit segments
    Step 3: Program the pattern into the Pattern Generator
  Note: This function requires that MrcSelectEngines() has been called.

  @param[in] MrcData - Include all MRC global data.
  @param[in] vmask   - 32 bit victim mask.  1 indicates this bit should use LFSR0
  @param[in] amask   - 32 bit aggressor mask. 0/1 indicates this bit should use LFSR1/2
  @param[in] VicRot  - Number of times to circular rotate vmask/amask
  @param[in] Start   - Starting entry in the WDB

  @retval Nothing
**/
void
WriteVAPattern (
  IN MrcParameters *const MrcData,
  IN UINT32               amask,
  IN UINT32               vmask,
  IN const UINT8          VicRot,
  IN const UINT16         Start
  )
{
  UINT8           Index;
  static const UINT32 LFSR0ExtBuf = 0xAAAAAAAA;
  static const UINT32 LFSR1ExtBuf = 0x33333333;
  const UINT32                                  *ExtBufPtr;
  MrcIntOutput                                  *MrcIntData;
  UINT8                                         Channel;
  UINT8                                         SubChannel;
  UINT8                                         ChanSubChanMask;
  UINT32                                        Offset;

  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));


  ChanSubChanMask = MrcIntData->ChSubChMaskEnable;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (SubChannel = 0; SubChannel < MrcIntData->SubChEngCount; SubChannel++) {
      if (SUB_CH_MASK_CHECK (ChanSubChanMask, Channel, SubChannel) == 0) {
        continue;
      }
      // Program ExtBuf
      Offset = OFFSET_CALC_CH_SUBCH (
        CH0_SC0_CR_CPGC_DPAT_EXTBUF_0_REG,
        CH1_SC0_CR_CPGC_DPAT_EXTBUF_0_REG, Channel,
        CH0_SC1_CR_CPGC_DPAT_EXTBUF_0_REG, SubChannel);
      for (Index = 0; Index < CPGC_20_NUM_DPAT_EXTBUF; Index++) {
        ExtBufPtr = ((Index == 0) || (Index == 8)) ? &LFSR0ExtBuf : &LFSR1ExtBuf;
        MrcWriteCR (MrcData, Offset, *ExtBufPtr);
        //Adjust Offset for next EXTBUF
        Offset += (CH0_SC0_CR_CPGC_DPAT_EXTBUF_1_REG - CH0_SC0_CR_CPGC_DPAT_EXTBUF_0_REG);
      }
    }
  }

  return;
}

/**
  Write VA pattern in CADB buffer.

  Note1: CKE, ODT and CS are not used in functional mode and are ignored.
  Note2: This function requires that MrcSelectEngines() has been called.

  @param[in] MrcData      - Include all MRC global data.
  @param[in] VictimSpread - Separation of the Victim Bit.
  @param[in] VictimBit    - The Bit to be the Victim.

  @retval mrcSuccess if successful, otherwise returns an error status.
**/
MrcStatus
SetupCadbVaPat (
  IN MrcParameters *const MrcData,
  IN const UINT8          VictimSpread,
  IN const UINT8          VictimBit
  )
{
  const MRC_FUNCTION  *MrcCall;
  UINT8               Row;
  UINT8               bit;
  UINT8               CadbBits;
  UINT8               lfsr0;
  UINT8               lfsr1;
  UINT8               Lfsr;
  UINT8               Fine;
  UINT8               Cke[2];
  UINT8               Cs[2];
  UINT8               Odt;
  MRC_CA_MAP_TYPE     CadbPat;
  UINT64_STRUCT       CadbPatEncoded[CADB_20_MAX_CHUNKS];
  UINT32              CaPattern[CADB_20_MAX_CHUNKS];
  BOOLEAN             Ddr4;
  BOOLEAN             IsVictim;
/**
  we need to excercise all bits as victims on each CMD group, only one must be selected at a time per group
 for DDR4 CCC groups are mapped as follows:

                                               CmdGroup4(CKECMD/PI2)
  -----------------------------------------------------------------------
  VB    MA[5]   MA[6]   MA[9]   MA[11]  MA[12]   MA[3]                  | CmdGroup0 (CMDA/PI0)
  -----------------------------------------------------------------------
        MA[7]   MA[8]   BG[1]   ACT_N   BG[0]    MA[4]                  | CmdGroup1 (CMDA/PI1)
  -----------------------------------------------------------------------
        MA[10]  MA[13]  BA[1]   CAS_N   WE_N                            | CmdGroup2 (CMDB/PI0)
  -----------------------------------------------------------------------
        MA[0]   MA[1]   MA[2]   BA[0]   RAS_N                           | CmdGroup3 (CMDB/PI1)
  -----------------------------------------------------------------------
  0     V       a       a       a       a        a
  1     a       V       a       a       a        a
  2     a       a       V       a       a        a
  3     a       a       a       V       a        a
  4     a       a       a       a       V        a
  5     a       a       a       a       a        V

  VB = Victim Bit Offset
  V  = Victim
  a  = agressor

  the CA mapping to CADB buffer bits must look like this for each of the Victim Bits
  VB
      actn   bg1   bg0   ba1   ba0    ma16   ma15   ma14   ma13   ma12   ma11   ma10   ma9   ma8   ma7   ma6   ma5   ma4   ma3   ma2   ma1   ma0
                                      ras_n  cas_n  we_n
  0    a      a     a     a     a      a      a      a      a      a      a      V     a     a     V     a     V     a     a     a     a     V   [0x000004A1]
  1    a      a     a     a     a      a      a      a      V      a      a      a     a     V     a     V     a     a     a     a     V     a   [0x00002142]
  2    a      V     a     V     a      a      a      a      a      a      a      a     V     a     a     a     a     a     a     V     a     a   [0x00140204]
  3    V      a     a     a     V      a      V      a      a      a      V      a     a     a     a     a     a     a     a     a     a     a   [0x00228800]
  4    a      a     V     a     a      V      a      V      a      V      a      a     a     a     a     a     a     a     a     a     a     a   [0x00095000]
  5    a      a     a     a     a      a      a      a      a      a      a      a     a     a     a     a     a     V     V     a     a     a   [0x00000018]
   CA[22]   [21]  ,[20]  [19]  [18]   [16] , [15]   [14]   [13]   [12] , [11]   [10]  [9]   [8],  [7]   [6]   [5]   [4]  ,[3]   [2]   [1]   [0]
**/
  UINT8   Ddr4CccVictimBitMapMax;
  STATIC CONST UINT32  Ddr4CccVictimBitMap [] =  {
                                     0x000004A1, // Victim Bit 0
                                     0x00002142, // Victim Bit 1
                                     0x00140204, // Victim Bit 2
                                     0x00228800, // Victim Bit 3
                                     0x00095000, // Victim Bit 4
                                     0x00000018  // Victim Bit 5
                                    };

  Ddr4CccVictimBitMapMax = sizeof(Ddr4CccVictimBitMap) / sizeof(Ddr4CccVictimBitMap[0]);
  MrcCall     = MrcData->Inputs.Call.Func;
  Ddr4        = (MrcData->Outputs.DdrType == MRC_DDR_TYPE_DDR4);
  Odt         = 0;
  MrcCall->MrcSetMem ((UINT8 *) Cke, sizeof (Cke), 0);
  MrcCall->MrcSetMem ((UINT8 *) Cs, sizeof (Cs), 0);
  MrcCall->MrcSetMem ((UINT8 *) CaPattern, sizeof (CaPattern), 0);
  MrcCall->MrcSetMem ((UINT8 *) CadbPatEncoded, sizeof (CadbPatEncoded), 0);

  if (Ddr4) {
    CadbBits = 23;  // CA[22:0]
  } else {
    // LPDDR4
    CadbBits = 6;  // CA[5:0]
  }

  for (Row = 0; Row < CADB_20_MAX_CHUNKS; Row++) {
    lfsr0 = (Row & 0x1);         // 0, 1, 0, 1, 0, 1, 0, 1 for r = 0,1, ..., 7
    lfsr1 = ((Row >> 1) & 0x1);  // 0, 0, 1, 1, 0, 0, 1, 1 for r = 0,1, ..., 7
    //
    // Assign Victim/Aggressor Bits
    //
    for (bit = 0; bit < CadbBits; bit++) {

      // For DDR4 use victim bit map
      if ((Ddr4) && (VictimBit < Ddr4CccVictimBitMapMax)) {
        IsVictim = 1 & (Ddr4CccVictimBitMap[VictimBit] >> bit);
      } else {
        Fine = bit % VictimSpread;
        IsVictim = (Fine == VictimBit);
      }

      if (IsVictim) {
        Lfsr = lfsr0;
      } else {
        Lfsr = lfsr1;
      }
      CaPattern[Row] |= Lfsr << bit;
    }
  }

  for (Row = 0; Row < CADB_20_MAX_CHUNKS; Row++) {
    CadbPat.Data32 = CaPattern[Row];
    // Translate generic pattern to CADB definition
    // SA:RestrictenContent - @todo: We are calling the 2.0 package directly here.
    CpgcConvertDdrToCadb (MrcData, &CadbPat, Cke, Cs, Odt, &CadbPatEncoded[Row]);
  }

  // Write the CADB Patterns
  MrcSetCadbPgPattern (MrcData, CadbPatEncoded, CADB_20_MAX_CHUNKS, 0);

  return mrcSuccess;
}

/**
  Programs all the key registers to define a CPCG test

  @param[in] MrcData     - Include all MRC global data.
  @param[in] ChbitMask   - Channel Bit mak for which test should be setup for.
  @param[in] CmdPat      -  0: PatWrRd (Standard Write/Read Loopback),
                            1: PatWr (Write Only),
                            2: PatRd (Read Only),
                            3: PatRdWrTA (ReadWrite Turnarounds),
                            4: PatWrRdTA (WriteRead Turnarounds),
                            5: PatODTTA (ODT Turnaround)
                            9: PatRdEndless (for IO-based ReadMPR)
                            10: PatWrScrub (for zeroing whole memory)
  @param[in] NumCL       - Number of Cache lines
  @param[in] LC          - Loop Count exponent
  @param[in] CPGCAddress - Structure that stores address related settings
  @param[in] SOE         - [0: Never Stop, 1: Stop on Any Lane, 2: Stop on All Byte, 3: Stop on All Lane]
  @param[in] PatCtlPtr   - Structure that stores start, Stop, IncRate and Dqpat for pattern.
  @param[in] EnCADB      - Enable test to write random deselect packages on bus to create xtalk/isi
  @param[in] EnCKE       - Enable CKE power down by adding 64
  @param[in] SubSeqWait  - # of Dclks to stall at the end of a sub-sequence

  @retval Nothing
**/
void
SetupIOTest (
  IN MrcParameters *const         MrcData,
  IN const UINT8                  ChbitMask,
  IN const UINT8                  CmdPat,
  IN const UINT32                 NumCL,
  IN const UINT8                  LC,
  IN const Cpgc20Address *const   CPGCAddress,
  IN const MRC_TEST_STOP_TYPE     SOE,
  IN MRC_PATTERN_CTL *const       PatCtlPtr,
  IN const UINT8                  EnCADB,
  IN const UINT8                  EnCKE,
  IN UINT16                       SubSeqWait
  )
{
  static const UINT32 CadbLfsrSeeds[MRC_NUM_MUX_SEEDS]  = {0x096EA1, 0xCABEEF, 0x53DEAD};
  static const UINT32 DataLfsrSeeds[MRC_NUM_MUX_SEEDS]  = {0xA10CA1, 0xEF0D08, 0xAD0A1E};
  static const UINT32 DataStaticSeeds[MRC_NUM_MUX_SEEDS] = {0xAAAAAAAA, 0xCCCCCCCC, 0xF0F0F0F0};
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcDebug          *Debug;
  MrcIntOutput      *IntOutputs;
  MrcZqType         ZqType;
  UINT32            ChunkMask;
  UINT16            Wait;
  UINT8             ShiftLeftBy;
  UINT32            LoopCount;
  UINT32            Burst;
  UINT8             Index;
  UINT8             Channel;
  UINT8             CurChMask;
  UINT8             LaneRotateRate;
  UINT8             ValidMask;
  BOOLEAN           Ddr4;
  CH0_SC0_CR_CADB_CFG_STRUCT      CadbConfig;
  CH0_CR_PM_PDWN_CONFIG_STRUCT    PmPdwnConfig;
  CH0_SC0_CR_CPGC2_COMMAND_INSTRUCTION_0_STRUCT  Cpgc2CmdInstruction[6]; // 6 instructions defined in this function
  CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_STRUCT Cpgc2AlgoInstructionWr;
  CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_STRUCT Cpgc2AlgoInstructionRd;
  CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_STRUCT Cpgc2AlgoInstructionRdWr;
  CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_STRUCT Cpgc2AlgoInstructionWrRd;
  CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_0_STRUCT AlgoInstruct[CPGC20_MAX_ALGORITHM_INSTRUCTION];
  CH0_SC0_CR_CPGC2_ALGORITHM_INSTRUCTION_CTRL_0_STRUCT AlgoInstructControl;
  CH0_SC0_CR_CPGC2_ALGORITHM_WAIT_EVENT_CONTROL_STRUCT AlgoWaitEventControl;
  CH0_SC0_CR_CPGC2_DATA_INSTRUCTION_0_STRUCT      DataInstruct[CPGC20_MAX_DATA_INSTRUCTION];

  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[CONTROLLER_0];
  IntOutputs    = (MrcIntOutput *) MrcData->IntOutputs.Internal;
  Ddr4          = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Burst         = MAX (NumCL, 1);
  if (MrcData->Inputs.LoopBackTest) {
    Burst = 1;        // Cannot do more than a single cacheline per test in Loopback mode
  }
  ShiftLeftBy   = MIN (LC, 31);

  if (EnCADB) {
    // We have 7 subtests in CMD stress due to CA victim bit rotation (spread = 6) and one subtest without DESELECTs
    // Divide loopcount by 8 to get the intended overall loopcount in RunIOTest.
    if (ShiftLeftBy >= 3) {
      ShiftLeftBy -= 3;
    }
  } else if (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) {
    // Divide the Loopcount by 2 for Data stress, because LPDDR4 has twice longer burst length comparing to DDR4.
    if (ShiftLeftBy >= 1) {
      ShiftLeftBy -= 1;
    }
  }

  // LC defines the number of Cacheline Transactions for the test: 2^LC.
  LoopCount = (1 << ShiftLeftBy);

  // Check for the cases where this MUST be 1: When we manually walk through SUBSEQ ODT and TAWR
  if ((CmdPat == PatWrRdTA) || (CmdPat == PatODTTA)) {
    //CPGC2.1 change needed? to increase Loopcount for PatWrRdTA
    LoopCount = 1;
  }

  if (EnCKE) {
    // @todo: Need to check that PDWN is programmed already.
    PmPdwnConfig.Data = MrcReadCR (MrcData, BC_CR_PM_PDWN_CONFIG_REG);
    Wait = (UINT16) (PmPdwnConfig.Bits.PDWN_idle_counter + 16); // Adding extra DCKs, 16,  to make sure we make it to power down.
    if (Wait > SubSeqWait) {
      SubSeqWait = Wait;
    }
  }

  // Per channel settings
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    CurChMask = (1 << Channel) & Outputs->ValidChBitMask;
    if ((CurChMask & ChbitMask) == 0) {
      continue;
    }
    ChannelOut = &ControllerOut->Channel[Channel];

    //###########################################################
    // Program CADB Pattern Controls.  PGs are selected for CADB.
    //###########################################################
    MrcSelectEngines (MrcData, 0, CurChMask, ChannelOut->ValidSubChBitMask);

    // Pattern is programmed in RunIoTest
    CadbConfig.Data = 0;
    CadbConfig.Bits.CADB_MODE = EnCADB ? Cadb20ModeTriggerDeselect : 0;
    CadbConfig.Bits.LANE_DESELECT_EN = 6;                                 // Drive CADB deselects on CA/Parity, but not on CS
    CadbConfig.Bits.CMD_DESELECT_START = 0xF;                             // Start driving deselects on RD/WR/ACT/PRE; keep CMD_DESELECT_STOP = 0
    CadbConfig.Bits.INITIAL_DSEL_EN = 1;
    CadbConfig.Bits.INITIAL_DSEL_SSEQ_EN = 1;
    if (Ddr4) {
      if ((ChannelOut->Timing[MrcData->Inputs.MemoryProfile].NMode == 2) || Outputs->Gear2) {
        CadbConfig.Bits.CADB_DSEL_THROTTLE_MODE = 2;
        CadbConfig.Bits.CADB_SEL_THROTTLE_MODE  = 2;
      }
    }
    CadbConfig.Bits.CADB_TO_CPGC_BIND = EnCADB ? 1 : 0;
    Cadb20ConfigRegWrite (MrcData, CadbConfig);

    if (EnCADB) {
      // Setup CADB in terms of LFSR selects, LFSR seeds, LMN constants and overall control
      Cadb20UniseqCfg (MrcData, MrcPgMuxLfsr, MrcLfsr8);

      // Write the LFSR seeds
      MrcInitCadbPgMux (MrcData, CadbLfsrSeeds, 0, MRC_NUM_MUX_SEEDS);

      Cpgc20AddressSetupCmdStress (MrcData);
    }

    //###########################################################
    // Program Data Pattern Controls.  PGs are selected for Data
    //###########################################################
    MrcSelectEngines (MrcData, CurChMask, 0, Outputs->ValidSubChMask);

    Cpgc20BasicMemTest (MrcData, Burst, LoopCount, 1);
    // @todo: Add enable call for ECC PG source, and ECC PG enable.

    // Write the LFSR seeds
    if (PatCtlPtr->DQPat == StaticPattern) {
      MrcInitCpgcPgMux (MrcData, DataStaticSeeds, 0, MRC_NUM_MUX_SEEDS);
      LaneRotateRate = 0;
    } else {
      MrcInitCpgcPgMux (MrcData, DataLfsrSeeds, 0, MRC_NUM_MUX_SEEDS);
      LaneRotateRate = 2;
    }

    // Setup CPGC in terms of LFSR selects, LFSR seeds, LMN constants and overall control
    Cpgc20DPatCfg (MrcData, CmdPat, PatCtlPtr);
    //@todo should LSFR Poly match previous code or documentation?
    Cpgc20LfsrCfg (MrcData, MrcLfsr16, LaneRotateRate);

    //###########################################################
    // Program Command Instuctions @todo set this up in GetSet cached and then flushed
    //###########################################################
    // Write CMD [0]
    Cpgc2CmdInstruction[0].Data          = 0;
    Cpgc2CmdInstruction[0].Bits.WriteCmd = 1;
    Cpgc2CmdInstruction[0].Bits.Address_Decode_or_PRBS_En = EnCADB;
    Cpgc2CmdInstruction[0].Bits.Last     = 1;

    // Read CMD [1]
    Cpgc2CmdInstruction[1].Data          = 0;
    Cpgc2CmdInstruction[1].Bits.Address_Decode_or_PRBS_En = EnCADB;
    Cpgc2CmdInstruction[1].Bits.Last     = 1;

    // Read-Write CMD [2-3]
    Cpgc2CmdInstruction[2].Data          = 0;
    Cpgc2CmdInstruction[3].Data          = Cpgc2CmdInstruction[0].Data;

    // Write-Read CMD [4-5]
    Cpgc2CmdInstruction[4].Data          = 0;
    Cpgc2CmdInstruction[4].Bits.WriteCmd = 1;
    Cpgc2CmdInstruction[5].Data          = Cpgc2CmdInstruction[1].Data;

    Cpgc20CmdInstructWrite (MrcData, &Cpgc2CmdInstruction[0], ARRAY_COUNT (Cpgc2CmdInstruction));

    //###########################################################
    // Program Algorithm Instructions (pointing to the Command Instructions above)
    //###########################################################
    // Write Algo
    Cpgc2AlgoInstructionWr.Data = 0;
    Cpgc2AlgoInstructionWr.Bits.Command_Start_Pointer = 0;

    // Read Algo
    Cpgc2AlgoInstructionRd.Data = 0;
    Cpgc2AlgoInstructionRd.Bits.Command_Start_Pointer = 1;

    // Read-Write Algo
    Cpgc2AlgoInstructionRdWr.Data = 0;
    Cpgc2AlgoInstructionRdWr.Bits.Command_Start_Pointer = 2;

    // Write-Read Algo
    Cpgc2AlgoInstructionWrRd.Data = 0;
    Cpgc2AlgoInstructionWrRd.Bits.Command_Start_Pointer = 4;

    //###########################################################
    // Program Sequence of Algorithm Instructions based on CmdPat
    //###########################################################
    switch (CmdPat) {
      case PatWrRdTA:
        AlgoInstruct[0].Data = Cpgc2AlgoInstructionWr.Data;        // Write CMD All data
        for (Index = 1; Index <= 6; Index++) {
          AlgoInstruct[Index].Data = Cpgc2AlgoInstructionRdWr.Data;// Read-Write CMD
        }
        AlgoInstruct[7].Data = Cpgc2AlgoInstructionRd.Data;        // Read CMD
        AlgoInstruct[7].Bits.Last = 1;

        ValidMask = 0xFF;
        break;

      case PatRdWrTA:
        AlgoInstruct[0].Data = Cpgc2AlgoInstructionWrRd.Data;      // Write-Read CMD
        AlgoInstruct[0].Bits.Last = 1;

        ValidMask = 0x01;
        break;

      case PatODTTA:
        AlgoInstruct[0].Data = Cpgc2AlgoInstructionWr.Data;        // Write CMD

        AlgoInstruct[1].Data = Cpgc2AlgoInstructionRdWr.Data;      // Read-Write CMD

        AlgoInstruct[2].Data = Cpgc2AlgoInstructionRd.Data;        // Read CMD

        AlgoInstruct[3].Data = Cpgc2AlgoInstructionWrRd.Data;      // Write-Read CMD
        AlgoInstruct[3].Bits.Last = 1;

        ValidMask = 0x0F;
        break;

      case PatWrRd:
        AlgoInstruct[0].Data = Cpgc2AlgoInstructionWr.Data;        // Write CMD

        AlgoInstruct[1].Data = Cpgc2AlgoInstructionRd.Data;        // Read CMD
        AlgoInstruct[1].Bits.Last = 1;

        ValidMask = 0x03;
        break;

      case PatWr:
      case PatWrScrub:
        AlgoInstruct[0].Data = Cpgc2AlgoInstructionWr.Data;        // Write CMD
        AlgoInstruct[0].Bits.Last = 1;

        ValidMask = 0x01;
        break;

      case PatRd:
        AlgoInstruct[0].Data = Cpgc2AlgoInstructionRd.Data;        // Read CMD
        AlgoInstruct[0].Bits.Last = 1;

        ValidMask = 0x01;
        break;

      case PatRdEndless:
        // Used in endless tests like in HW-based ReadMPR
        for (Index = 0; Index < CPGC20_MAX_ALGORITHM_INSTRUCTION; Index++) {
          AlgoInstruct[Index].Data = Cpgc2AlgoInstructionRd.Data;  // Read CMD, and no Last = endless test, no data rotation
        }
        ValidMask = 0xFF;
        break;

      default:
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "SetupIOTest: Unknown value for Pattern\n");
        ValidMask = 0x00;
        break;
    }

    // Program Write Data Buffer Related Entries.
    // Assumes the PG has already been selected above for Data PG's.
    MrcProgramDataPatternRotation (MrcData, PatCtlPtr, Channel);

    AlgoInstructControl.Data = 0;
    AlgoInstructControl.Bits.Deselect_On = EnCADB;

    AlgoWaitEventControl.Data = 0;
    if (SubSeqWait != 0) {
      AlgoInstructControl.Bits.Wait_Count_Start = 1;
      AlgoInstructControl.Bits.Wait_Count_Clear = 1;
      AlgoWaitEventControl.Bits.Wait_Clock_Frequency = CPGC20_NATIVE_DUNIT_FREQ;
      AlgoWaitEventControl.Bits.Wait_Time = SubSeqWait;
    }
    Cpgc20AlgoInstructWrite (MrcData, &AlgoInstruct[0], AlgoInstructControl, AlgoWaitEventControl, ValidMask);

    DataInstruct[0].Data = 0;
    DataInstruct[0].Bits.Last = 1;
    DataInstruct[1].Data = DataInstruct[0].Data;
    DataInstruct[2].Data = DataInstruct[0].Data;
    DataInstruct[3].Data = DataInstruct[0].Data;

    Cpgc20DataInstructWrite (MrcData, &DataInstruct[0], 0x1);

    //###########################################################
    // Program Cpgc Address
    //###########################################################
    Cpgc20AddressSetup (
      MrcData,
      CPGCAddress->AddrIncOrder,
      CPGCAddress->AddrDirection,
      CPGCAddress->LastValidAddr,
      CPGCAddress->RowStart,
      CPGCAddress->ColStart,
      CPGCAddress->RowSizeBits,
      CPGCAddress->ColSizeBits,
      CPGCAddress->BankSize,
      EnCADB
      );

    //###########################################################
    // Program Error Checking
    //###########################################################

    // Enable selective_error_enable_chunk and selective_error_enable_cacheline, mask later
    // the bits we don't want to check.
    // If we are in Enhanced Channel Mode, then we have a burst length of 16 instead of 8.
    ChunkMask = (Outputs->EnhancedChannelMode) ? 0xFFFF : 0xFF;
    MrcSetupTestErrCtl (MrcData, Channel, /*SOE*/ NSOE, 0);
    MrcSetChunkAndClErrMsk (MrcData, Channel, 0xFF, ChunkMask);
    // Store the test mode in the internal cache for other functions.
    IntOutputs->TestStopMode = SOE;

    // Setup Data and ECC Errors
    MrcSetDataAndEccErrMsk (MrcData, Channel, 0xFFFFFFFFFFFFFFFFULL, 0xFF);
  } // for Channel

  MrcSelectEngines (MrcData, ChbitMask, 0, Outputs->ValidSubChMask);  // Select all participating CPGC engines

  // Always do a ZQ Short before the beginning of a test
  if (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) {
    ZqType  = MRC_ZQ_CAL;
  } else if (Outputs->DdrType == MRC_DDR_TYPE_DDR4) {
    ZqType  = MRC_ZQ_LONG;
  } else {
    ZqType  = MRC_ZQ_SHORT;
  }

  if (!IntOutputs->SkipZq) {
    MrcIssueZQ (MrcData, ChbitMask, ZqType);
  }

  return;
}

/**
  This function sets up a test with CADB for the given channel mask.

  @param[in,out] MrcData   - Pointer to MRC global data.
  @param[in]     ChbitMask - Bit masks of channels to enable for the test.
  @param[in]     LC        - Exponential umber of loops to run the test.
  @param[in]     SOE       - Error handling switch for test.
  @param[in]     EnCADB    - Switch to enable CADB
  @param[in]     EnCKE     - Switch to enable CKE.

  @retval Nothing
**/
void
SetupIOTestCADB (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          ChbitMask,
  IN     const UINT8          LC,
  IN     const UINT8          SOE,
  IN     const UINT8          EnCADB,
  IN     const UINT8          EnCKE
  )
{
  // Note: Row and Col bit size below must match the values set in Cpgc20AddressSetupCmdStress()
  static const Cpgc20Address CPGCAddress_Ddr4 = {
    CPGC20_ROW_COL_2_BANK_2_RANK,
    CPGC20_FAST_Y,
    0,    // Single Address Instruction
    0,
    0,
    14,   // RowSizeBits
    7,    // ColSizeBits
    8
  };
  static const Cpgc20Address CPGCAddress_Lpddr4 = {
    CPGC20_ROW_COL_2_BANK_2_RANK,
    CPGC20_FAST_Y,
    0,    // Single Address Instruction
    0,
    0,
    14,   // RowSizeBits
    6,    // ColSizeBits
    8
  };
  const Cpgc20Address *CpgcAddress;
  MRC_PATTERN_CTL  PatCtl;
  MrcOutput       *Outputs;
  UINT16          NumCL;

  Outputs           = &MrcData->Outputs;
  PatCtl.IncRate    = 4;
  PatCtl.Start      = 0;
  PatCtl.Stop       = 9;
  PatCtl.DQPat      = CADB;
  PatCtl.PatSource  = MrcPatSrcDynamic;
  PatCtl.EnableXor  = FALSE;

  if (Outputs->DdrType == MRC_DDR_TYPE_DDR4) {
    CpgcAddress = &CPGCAddress_Ddr4;
  } else {
    CpgcAddress = &CPGCAddress_Lpddr4;
  }

  // Column limit is 2^10
  // BL=8:  column increment is 2^3 per CL --> 10 - 3 = 7, 2^7 = 128
  // BL=16: column increment is 2^4 per CL --> 10 - 4 = 6, 2^6 = 64
  NumCL = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) ? 64 : 128;

  SetupIOTest (MrcData, ChbitMask, PatWrRd, NumCL, LC, CpgcAddress, SOE, &PatCtl, EnCADB, EnCKE, 0);

  Outputs->DQPatLC = LC - 2 - 3 + 1;
  if (Outputs->DQPatLC < 1) {
    Outputs->DQPatLC = 1;
  }

  Outputs->DQPat = CADB;
  return;
}

/**
  This function sets up a basic victim-aggressor test for the given channel mask.

  @param[in,out] MrcData   - Pointer to MRC global data.
  @param[in]     ChbitMask - Bit masks of channels to enable for the test.
  @param[in]     LC        - Exponential umber of loops to run the test.
  @param[in]     SOE       - Error handling switch for test.
  @param[in]     EnCADB    - Switch to enable CADB
  @param[in]     EnCKE     - Switch to enable CKE.
  @param[in]     Spread    - Stopping point of the pattern.

  @retval Nothing
**/
void
SetupIOTestBasicVA (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          ChbitMask,
  IN     const UINT8          LC,
  IN     const UINT8          SOE,
  IN     const UINT8          EnCADB,
  IN     const UINT8          EnCKE,
  IN     const UINT8          Spread
  )
{
  static const Cpgc20Address CPGCAddress_ddr4 = {
    CPGC20_BANK_2_ROW_COL_2_RANK,
    CPGC20_FAST_Y,
    0x0,    // Single Address Instruction
    0,
    0,
    0,
    7,
    2
  };

  static const Cpgc20Address CPGCAddress_lpdd4 = {
    CPGC20_BANK_2_ROW_COL_2_RANK,
    CPGC20_FAST_Y,
    0x0,    // Single Address Instruction
    0,
    0,
    0,
    6,
    1
  };

  MRC_PATTERN_CTL        PatCtl;
  MrcOutput             *Outputs;
  UINT16                NumCL;
  const Cpgc20Address   *CPGCAddress;

  Outputs           = &MrcData->Outputs;
  PatCtl.Start      = 0;
  PatCtl.Stop       = Spread - 1;
  PatCtl.DQPat      = BasicVA;
  PatCtl.PatSource  = MrcPatSrcDynamic;
  PatCtl.EnableXor  = FALSE;

  // Column limit is 2^10
  // BL=8:  column increment is 2^3 per CL --> 10 - 3 = 7, 2^7 = 128
  // BL=16: column increment is 2^4 per CL --> 10 - 4 = 6, 2^6 = 64
  NumCL = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) ? 64 : 128;
  PatCtl.IncRate = 4;


  if (Outputs->DdrType == MRC_DDR_TYPE_DDR4) {
    CPGCAddress = &CPGCAddress_ddr4;
  } else { // LPDDR4
    CPGCAddress = &CPGCAddress_lpdd4;
  }
  SetupIOTest (MrcData, ChbitMask, PatWrRd, NumCL, LC, CPGCAddress, SOE, &PatCtl, EnCADB, EnCKE, 0);

  Outputs->DQPatLC = LC - 8 + 1;
  if (Outputs->DQPatLC < 1) {
    Outputs->DQPatLC = 1;
  }

  Outputs->DQPat = BasicVA;
  return;
}

/**
  This function sets up a MPR test for the given channel mask.

  @param[in,out] MrcData   - Pointer to MRC global data.
  @param[in]     ChbitMask - Bit masks of channels to enable for the test.
  @param[in]     LC        - Exponential umber of loops to run the test.
  @param[in]     SOE       - Error handling switch for test.
  @param[in]     EnCADB    - Switch to enable CADB
  @param[in]     EnCKE     - Switch to enable CKE.

  @retval Nothing
**/
void
SetupIOTestMPR (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          ChbitMask,
  IN     const UINT8          LC,
  IN     const UINT8          SOE,
  IN     const UINT8          EnCADB,
  IN     const UINT8          EnCKE
  )
{
  static const Cpgc20Address CPGCAddressDdr4 = {
    CPGC20_BANK_2_ROW_COL_2_RANK,
    CPGC20_FAST_Y,
    0xFF,               // LastValidAddr: 0xFF means endless test
    0,
    0,
    0,
    4,
    2
  };
  static const Cpgc20Address CPGCAddressLpddr4 = {
    CPGC20_BANK_2_ROW_COL_2_RANK,
    CPGC20_FAST_Y,
    0xFF,               // LastValidAddr: 0xFF means endless test
    0,
    0,
    0,
    5,
    1
  };
  const Cpgc20Address   *CpgcAddress;
  MRC_PATTERN_CTL        PatCtl;
  MrcOutput             *Outputs;
  MrcDdrType            DdrType;
  UINT16                NumCL;
  UINT8                 Channel;

  Outputs = &MrcData->Outputs;
  DdrType = Outputs->DdrType;

  PatCtl.IncRate    = 0;
  PatCtl.Start      = 0;
  PatCtl.Stop       = 1;  // Dont't Care as MPR doesn't use WDB  Either IO or PG.
  PatCtl.DQPat      = StaticPattern; // Don't want RunIOTest changing the PG.
  PatCtl.PatSource  = MrcPatSrcDynamic; // PG should be used instead of WDB
  PatCtl.EnableXor  = FALSE; // Disable the Xor of WDB.

  NumCL = 128;

  CpgcAddress = (DdrType == MRC_DDR_TYPE_DDR4) ? &CPGCAddressDdr4 : &CPGCAddressLpddr4;

  SetupIOTest (MrcData, ChbitMask, PatRdEndless, NumCL, LC, CpgcAddress, SOE, &PatCtl, EnCADB, EnCKE, 0);

  WriteVAPattern (MrcData, 0, BASIC_VA_PATTERN_SPRED_8, 1, 0);
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    MrcSetupTestErrCtl (MrcData, Channel, NSOE, 0);
    Cpgc20BaseRepeats (MrcData, 0x80000000, 1);
  }

  Outputs->DQPatLC = 1;
  Outputs->DQPat   = StaticPattern;
  return;
}

/**
This function sets up a Read test for the given channel mask.

@param[in,out] MrcData   - Pointer to MRC global data.
@param[in]     ChbitMask - Bit masks of channels to enable for the test.
@param[in]     LC        - Exponential umber of loops to run the test.
@param[in]     SOE       - Error handling switch for test.
@param[in]     RdDataPtn - Read Data Pattern in 32bit  (i.e. MPR - LP4:0x0xa5a5a5a5     DDR4:0xAAAAAAAA)

@retval Nothing
**/
void
SetupIOTestCpgcRead (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          ChbitMask,
  IN     const UINT8          LC,
  IN     const UINT8          SOE,
  IN     const UINT32         RdDataPtn
  )
{
  const MRC_FUNCTION    *MrcCall;
  MRC_PATTERN_CTL       PatCtl;
  MrcOutput             *Outputs;
  MrcDdrType            DdrType;
  UINT16                NumCL;
  UINT16                IncScale;
  UINT8                 Channel;
  static const Cpgc20Address CPGCAddress = {
    CPGC20_BANK_2_ROW_COL_2_RANK,
    CPGC20_FAST_Y,
    0, //Run only on first Address Instruction
    0,
    0,
    0,
    4,
    2
  };
  UINT32 Pattern[8][2];

  MrcCall = MrcData->Inputs.Call.Func;
  Outputs = &MrcData->Outputs;
  DdrType = Outputs->DdrType;

  MrcCall->MrcSetMemDword ((UINT32 *) Pattern, sizeof (Pattern) / sizeof (UINT32), RdDataPtn);
  IncScale = (DdrType == MRC_DDR_TYPE_LPDDR4) ? 1 : 0;         // 0 - Linear
  PatCtl.IncRate = 0;
  PatCtl.Start = 0;
  PatCtl.Stop = 1;  // Dont't Care as MPR doesn't use WDB  Either IO or PG.
  PatCtl.DQPat = StaticPattern;       // Use Pattern Buffer mode
  PatCtl.PatSource = MrcPatSrcStatic;

  NumCL = 32;

  SetupIOTest (MrcData, ChbitMask, PatRd, NumCL, LC, &CPGCAddress, SOE, &PatCtl, 0, 0, 0);
  Cpgc20SetDpatBufCtl (MrcData, IncScale, PatCtl.IncRate, PatCtl.Start, PatCtl.Stop);
  WriteFixedPattern (MrcData, Pattern);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    MrcSetupTestErrCtl (MrcData, Channel, NSOE, 0);
  }

  Outputs->DQPatLC = 1;
  Outputs->DQPat   = StaticPattern;
  return;
}

/**
  This function sets up a Clock Pattern test for the given channel mask.

  @param[in,out] MrcData   - Pointer to MRC global data.
  @param[in]     ChbitMask - Bit masks of channels to enable for the test.
  @param[in]     LC        - Exponential umber of loops to run the test.
  @param[in]     SOE       - Error handling switch for test.
  @param[in]     EnCADB    - Switch to enable CADB
  @param[in]     EnCKE     - Switch to enable CKE.

  @retval Nothing
**/
void
SetupIOTestClock (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          ChbitMask,
  IN     const UINT8          LC,
  IN     const UINT8          SOE,
  IN     const UINT8          EnCADB,
  IN     const UINT8          EnCKE
  )
{
  static const Cpgc20Address CPGCAddress = {
    CPGC20_ROW_COL_2_BANK_2_RANK,
    CPGC20_FAST_Y,
    0xFF,
    0,
    0,
    0,
    4,
    2
  };
  const Cpgc20Address   *CpgcAddress;
  MRC_PATTERN_CTL        PatCtl;
  MrcOutput             *Outputs;
  UINT16                NumCL;

  Outputs = &MrcData->Outputs;

  PatCtl.IncRate    = 1;
  PatCtl.Start      = 0;
  PatCtl.Stop       = 1;  // Don't Care as Clock Test doesn't use WDB:  Either IO or PG.
  PatCtl.DQPat      = StaticPattern; // Don't want RunIOTest changing the PG.
  PatCtl.PatSource  = MrcPatSrcDynamic; // PG should be used instead of WDB
  PatCtl.EnableXor  = FALSE; // Disable the Xor of WDB.

  NumCL = 128;

  CpgcAddress = &CPGCAddress;

  SetupIOTest (MrcData, ChbitMask, PatWrRd, NumCL, LC, CpgcAddress, SOE, &PatCtl, EnCADB, EnCKE, 0);

  Outputs->DQPatLC = 1;
  Outputs->DQPat   = StaticPattern;
  return;
}

/**
  This function sets up a basic static WR/RD test for the given channel mask.

  @param[in,out] MrcData   - Pointer to MRC global data.
  @param[in]     ChbitMask - Bit masks of channels to enable for the test.
  @param[in]     LC        - Exponential number of loops to run the test.
  @param[in]     SOE       - Error handling switch for test.
  @param[in]     EnCADB    - Switch to enable CADB
  @param[in]     EnCKE     - Switch to enable CKE.
  @param[in]     NumIters  - Desired number of iterations on each cacheline.
  @param[in]     Pattern   - Array of chunks (64 bit), broken into two 32-bit entries (second dimension).
                             Length (first dimension) can be up to NUM_DPAT_EXTBUF

  @retval Nothing
**/
void
SetupIOTestStatic (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          ChbitMask,
  IN     const UINT8          LC,
  IN     const UINT8          SOE,
  IN     const UINT8          EnCADB,
  IN     const UINT8          EnCKE,
  IN     const UINT16         NumIters,
  IN           UINT32         Pattern[][2]
  )
{
  static const Cpgc20Address CPGCAddressDdr4 = {
    CPGC20_BANK_2_ROW_COL_2_RANK,
    CPGC20_FAST_Y,
    0, //Run only on first Address Instruction
    0,
    0,
    0,
    4,
    2
  };
  static const Cpgc20Address CPGCAddressLpddr4 = {
    CPGC20_BANK_2_ROW_COL_2_RANK,
    CPGC20_FAST_Y,
    0, //Run only on first Address Instruction
    0,
    0,
    0,
    5,
    2
  };
  const Cpgc20Address   *CpgcAddress;
  MRC_PATTERN_CTL       PatCtl;
  MrcOutput             *Outputs;
  MrcDdrType            DdrType;
  UINT16                IncScale;
  UINT8                 Channel;
  UINT8                 NumCL;

  Outputs           = &MrcData->Outputs;
  DdrType           = Outputs->DdrType;
  NumCL             = 4;
  IncScale          = (NumIters > 64) ? 0 : 1; // 0 <Exponential> : 1 <Linear>
  PatCtl.IncRate    = (IncScale == 0) ? (MrcLog2 (NumIters)) : (NumIters - 1);
  PatCtl.Start      = 0;
  PatCtl.Stop       = 3; //Run on all 4 cachelines
  PatCtl.DQPat      = StaticPattern;
  PatCtl.PatSource  = MrcPatSrcStatic;
  PatCtl.EnableXor  = TRUE;
  CpgcAddress       = (DdrType == MRC_DDR_TYPE_DDR4) ? &CPGCAddressDdr4 : &CPGCAddressLpddr4;

  SetupIOTest (MrcData, ChbitMask, PatWrRd, NumCL, LC, CpgcAddress, NSOE, &PatCtl, 0, 0, 0);
  MrcSelectEngines (MrcData, ChbitMask, 0, 0);
  Cpgc20SetDpatBufCtl (MrcData, IncScale, PatCtl.IncRate, PatCtl.Start, PatCtl.Stop);
  WriteFixedPattern (MrcData, Pattern);
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    MrcSetupTestErrCtl (MrcData, Channel, NSOE, 0);
  }

  Outputs->DQPatLC = 1;
  Outputs->DQPat   = StaticPattern;
  return;
}

/**
  This function sets up a WR-only test for the given channel mask, with all-zero data.
  This is used for ECC scrubbing or memory clear.

  @param[in,out] MrcData   - Pointer to MRC global data.
  @param[in]     ChbitMask - Bit masks of channels to enable for the test.

**/
void
SetupIOTestScrub (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          ChbitMask
  )
{
  // Row/Col/Bank sizes may be different per DIMM, hence set them later using Cpgc20AddressSetupScrub()
  static const Cpgc20Address CpgcAddress = {
    CPGC20_BANK_2_ROW_COL_2_RANK,
    CPGC20_FAST_Y,
    0, // Run only on first Address Instruction
    0, // RowStart
    0, // ColStart
    0, // RowSizeBits
    0, // ColSizeBits
    0  // BankSize
  };
  MRC_PATTERN_CTL       PatCtl;
  UINT8                 NumCL;
  UINT8                 LC;

  NumCL             = 0;
  LC                = 0;
  PatCtl.IncRate    = 0;
  PatCtl.Start      = 0;
  PatCtl.Stop       = 0;
  PatCtl.DQPat      = StaticPattern;
  PatCtl.PatSource  = MrcPatSrcAllZeroes;  // DC zero
  PatCtl.EnableXor  = FALSE;

  SetupIOTest (MrcData, ChbitMask, PatWrScrub, NumCL, LC, &CpgcAddress, NSOE, &PatCtl, 0, 0, 0);

  MrcData->Outputs.DQPat   = PatCtl.DQPat;
  return;
}

/**
  Runs one or more REUT tests (based on TestType).

  @param[in] MrcData      - Include all MRC global data.
  @param[in] ChBitMask    - Channel Bit mask for which test should be setup for.
  @param[in] DQPat        - The Pattern type for the test.  See MrcDqPat.
  @param[in] ClearErrors  - Decision to clear or not errors.
  @param[in] ResetMode    - Parameter that specifies what training step we are running the reset in.

  @retval Returns ch errors
**/
UINT8
RunIOTest (
  IN MrcParameters *const MrcData,
  IN const UINT8          ChBitMask,
  IN const UINT8          DQPat,
  IN const UINT8          ClearErrors,
  IN const UINT16         ResetMode
  )
{
  const MrcInput      *Inputs;
  const MRC_FUNCTION  *MrcCall;
  MrcOutput           *Outputs;
  MrcIntOutput        *MrcIntData;
  INT64               GetSetVal;
  INT64               CmdTriStateDisSave[MAX_CHANNEL];
  UINT32              Offset;
  UINT32              Channel;
  UINT32              SubCh;
  UINT32              TestIdx;
  UINT8               ErrorStatus;
  UINT8               NumTests;
  UINT8               TestDoneStatus;
  UINT8               tRDRD_dr_Min[MAX_CHANNEL];
  UINT8               tRDRD_sg_Min[MAX_CHANNEL];
  UINT8               tRDRD_dg_Min[MAX_CHANNEL];
  UINT8               TurnAroundOffset;
  UINT8               CommandSpread;
//  REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_STRUCT ReutChSeqBaseAddrIncCtl;
  CH0_SC0_CR_CPGC_SEQ_CTL_STRUCT            CpgcSeqCtl;
  CH0_SC0_CR_CPGC_SEQ_STATUS_STRUCT         CpgcSeqStatus;
  CH0_SC0_CR_CPGC_ERR_TEST_ERR_STAT_STRUCT  CpgcErrTestStatus;
  CH0_SC0_CR_CADB_CTL_STRUCT                CadbControl;

  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  MrcIntData    = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  MrcCall->MrcSetMem (tRDRD_dr_Min, sizeof (tRDRD_dr_Min), 0);
  MrcCall->MrcSetMem (tRDRD_sg_Min, sizeof (tRDRD_sg_Min), 0);
  MrcCall->MrcSetMem (tRDRD_dg_Min, sizeof (tRDRD_dg_Min), 0);
  ErrorStatus            = 0;
  NumTests               = 1;
  CpgcSeqStatus.Data     = 0;
  CpgcErrTestStatus.Data = 0;
  CommandSpread          = MrcCommandSpread (MrcData); //Number of bits in the set of the Victim Aggressor pattern.

  // To setup MrcIntData->ChSubChMaskEnable in order to start the correct set of engines as Setup of engines may have been done on per channel basis and can be out of date
  MrcSelectEngines (MrcData, ChBitMask, ChBitMask, Outputs->ValidSubChMask);

  if (DQPat == CADB) {
    // With Pattern Generators, we don't need to break the test into multiple loops.
    // This is because the CADB PG has a shift feature, which is programmed in SetupIoTest.
    // If this goes away and we manually rotate the CADB pattern, the NumTests should equal
    // to the number of times we want to rotate the bus.  See MrcCommandSpread()
    NumTests = CommandSpread;
    // add one extra cycle to run with DESELECTS disabled
    NumTests += 1;

    // Enable command tri-state, in order to get CADB on Deselects
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (((1 << Channel) & ChBitMask) != 0) {
        MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccCmdTriStateDis, ReadFromCache,  &CmdTriStateDisSave[Channel]);
        GetSetVal = 0;
        MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccCmdTriStateDis, WriteCached, &GetSetVal);
      }
    }

    // Enable CADB on MC
    McCadbEnable (MrcData, TRUE);
  } else if (DQPat == TurnAroundWR) {
    NumTests = 1;  //AlgoInstructs already setup via SetupIOTest
  } else if (DQPat == TurnAroundODT) {
    NumTests = 4;
  } else if (DQPat == RdRdTA) {
    NumTests = 2;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!((MRC_BIT0 << Channel) & ChBitMask)) {
        continue;
      }

      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDsg, ReadFromCache, &GetSetVal);
      tRDRD_sg_Min[Channel] = (UINT8) GetSetVal; // save the min value allowed
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdg, ReadFromCache, &GetSetVal);
      tRDRD_dg_Min[Channel] = (UINT8) GetSetVal; // save the min value allowed
    }
  } else if (DQPat == RdRdTA_All) {
    NumTests = 8;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (((1 << Channel) & ChBitMask) == 0) {
        continue;
      }

      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDsg, ReadFromCache, &GetSetVal);
      tRDRD_sg_Min[Channel] = (UINT8) GetSetVal; // save the min value allowed
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdg, ReadFromCache, &GetSetVal);
      tRDRD_dg_Min[Channel] = (UINT8) GetSetVal; // save the min value allowed
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdr, ReadFromCache, &GetSetVal);
      tRDRD_dr_Min[Channel] = (UINT8) GetSetVal; // save the min value allowed
    }
  }

    // Setup the Pattern Generator for the test.
    // If we are CADB, we setup DQ bus to do VA so we get failures if the address of the command is incorrect.
    // CADB setup moved below to rotate Victim Bit based on the NumTests
    // Thus, we separate the cases from if-else.  StaticPattern and CADB cannot be set at the same time.
    if (DQPat == StaticPattern) {
      // Do nothing, static pattern should be prepared by the caller
    } else {
      MrcSelectEngines (MrcData, ChBitMask, 0, 0);
      WriteVAPattern (MrcData, 0, BASIC_VA_PATTERN_SPRED_8, 1, 0);
    }

  for (TestIdx = 0; TestIdx < NumTests; TestIdx++) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!((MRC_BIT0 << Channel) & ChBitMask)) {
          continue;
        }

        if ((DQPat == TurnAroundWR) || (DQPat == TurnAroundODT)) {
          // Program which subsequence to run
          // @todo <ICL> convert to CPGC 2.0
//        Offset = OFFSET_CALC_CH (REUT_CH_SEQ_CFG_0_REG, REUT_CH_SEQ_CFG_1_REG, Channel);
//        ReutChSeqCfg.Data = MrcReadCR64 (MrcData, Offset);
//        ReutChSeqCfg.Bits.Subsequence_Start_Pointer = TestIdx;
//        ReutChSeqCfg.Bits.Subsequence_End_Pointer   = TestIdx;
//        MrcWriteCR64 (MrcData, Offset, ReutChSeqCfg.Data);

          // Program RankInc Rate
//          IncRate =
//            (
//              ((DQPat == TurnAroundWR) && ((TestIdx == 0) || (TestIdx == 7))) ||
//              ((DQPat == TurnAroundODT) && ((TestIdx == 0) || (TestIdx == 2)))
//            ) ? 0 : 1;
//            IncScale = 1;
          /**
          Offset = OFFSET_CALC_CH (REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_REG, REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_REG, Channel);
          ReutChSeqBaseAddrIncCtl.Data = MrcReadCR64 (MrcData, Offset);
          ReutChSeqBaseAddrIncCtl.Bits.Rank_Base_Address_Update_Scale = IncScale;
          ReutChSeqBaseAddrIncCtl.Bits.Rank_Base_Address_Update_Rate = IncRate;
          ReutChSeqBaseAddrIncCtl.Bits.Column_Base_Address_Update_Scale = 1;
          ReutChSeqBaseAddrIncCtl.Bits.Column_Base_Address_Update_Rate = IncRate;
          MrcWriteCR64 (MrcData, Offset, ReutChSeqBaseAddrIncCtl.Data);
          **/
        } else if (DQPat == RdRdTA) {
          // Program tRDRD parameter
          GetSetVal = tRDRD_sg_Min[Channel] + TestIdx;
          MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDsg, WriteCached, &GetSetVal);
          GetSetVal = tRDRD_dg_Min[Channel] + TestIdx;
          MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdg, WriteCached, &GetSetVal);
        } else if (DQPat == RdRdTA_All) {
          // Program tRDRD for SR and DR
          //  Run 8 tests, Covering tRDRD_sr = 4,5,6,7 and tRDRD_dr = Min,+1,+2,+3
          TurnAroundOffset = (TestIdx % 4);
          GetSetVal = tRDRD_sg_Min[Channel] + TurnAroundOffset;
          MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDsg, WriteCached, &GetSetVal);
          GetSetVal = tRDRD_dg_Min[Channel] + TurnAroundOffset;
          MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdg, WriteCached, &GetSetVal);
          GetSetVal = tRDRD_dr_Min[Channel] + TurnAroundOffset;
          MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdr, WriteCached, &GetSetVal);
          // Program RankInc Rate
//          IncRate = (TestIdx > 3)? 0 : 31; // this field + 1
          /**
          Offset = OFFSET_CALC_CH (REUT_CH_SEQ_BASE_ADDR_INC_CTL_0_REG, REUT_CH_SEQ_BASE_ADDR_INC_CTL_1_REG, Channel);
          ReutChSeqBaseAddrIncCtl.Data = MrcReadCR64 (MrcData, Offset);
          ReutChSeqBaseAddrIncCtl.Bits.Rank_Base_Address_Update_Scale = 1;
          ReutChSeqBaseAddrIncCtl.Bits.Rank_Base_Address_Update_Rate = IncRate;
          MrcWriteCR64 (MrcData, Offset, ReutChSeqBaseAddrIncCtl.Data);
          **/
        }
        if ((DQPat == RdRdTA) || (DQPat == RdRdTA_All)) {
          // Must update the XARB bubble injector when TAT values change
          SetTcBubbleInjector (MrcData, Channel);
        }
      }

    // If we are CADB, we setup DQ bus to do VA so we get failures if the address of the command is incorrect.
    if (DQPat == CADB) {
      if (TestIdx < CommandSpread) {
        SetupCadbVaPat(MrcData, CommandSpread, (UINT8)TestIdx);
      } else {
        // Disable CADB on MC
        McCadbEnable(MrcData, FALSE);
      }
    }
      //###########################################################
      // Start Test and Poll on completion
      //###########################################################

      // IO Reset needed before starting test.
      IoReset (MrcData);

      if (DQPat == CADB) {
        // Start CADB, Do not start for the last cycle (Deselects)
        if (TestIdx < CommandSpread) {
          MrcSelectEngines (MrcData, 0, ChBitMask, Outputs->ValidSubChMask);
          CadbControl.Data = 0;
          CadbControl.Bits.START_TEST = 1;
          Cadb20ControlRegWrite (MrcData, CadbControl);
        }
      }

      CpgcSeqCtl.Data = 0;
      CpgcSeqCtl.Bits.START_TEST = 1;
      if (ClearErrors && (TestIdx == 0)) {
        CpgcSeqCtl.Bits.CLEAR_ERRORS = 1;
      }
      Cpgc20ControlRegWrite (MrcData, CpgcSeqCtl);

      // Wait until Channel test done status matches ChBitMask
      do {
        TestDoneStatus = 0;
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if ((ChBitMask & (1 << Channel)) != 0) {
            CpgcSeqStatus.Data = MrcReadCR (MrcData, (Channel == 0) ? CH0_SC0_CR_CPGC_SEQ_STATUS_REG : CH1_SC0_CR_CPGC_SEQ_STATUS_REG);
            TestDoneStatus |= (CpgcSeqStatus.Bits.TEST_DONE) << Channel;
          }
        }
      } while ((TestDoneStatus & ChBitMask) != ChBitMask);
      // Get test results
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if ((ChBitMask & (1 << Channel)) != 0) {
          for (SubCh = 0; SubCh < MrcIntData->SubChEngCount; SubCh++) {
            if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
              Offset = MrcGetTestErrStatOffset (MrcData, Channel, SubCh);
              CpgcErrTestStatus.Data = MrcReadCR (MrcData, Offset);
              ErrorStatus |= (CpgcErrTestStatus.Bits.ERROR_STATUS) << Channel;  // Combine results from both subchannels into a big channel status
            }
          } // for Subch
        }
      } // for Channel

      if (DQPat == CADB) {
        // Stop CADB, no need on the last test cycle (deselects)
        if (TestIdx < CommandSpread) {
          MrcSelectEngines (MrcData, 0, ChBitMask, Outputs->ValidSubChMask);
          CadbControl.Data = 0;
          CadbControl.Bits.STOP_TEST = 1;
          Cadb20ControlRegWrite (MrcData, CadbControl);
        }
      }

      // For x64 Channels, we can break out as soon as either SubChannel has an error for the channels populated.
      // Same as Error Status mask.
      // Current assumption is SubChannels are run sequentially.  Traffic is only sent on tested sub channel.  If a failure occurs, report it as an error for that Channel.
      // If a Sch is not populated, its Error status is Don't Care.
      // Not Valid (NV)
      // Sc1,Sc0   | 0,0 | 0,1 | 1,1 | 1,0 |
      // Sc1E,Sc0E |-----------------------|
      //    0,0    | NV  |  0  |  0  |  0  |
      //    0,1    | NV  |  1  |  1  |  0  |
      //    1,1    | NV  |  1  |  1  |  1  |
      //    1,0    | NV  |  0  |  1  |  1  |
      //           |-----------------------|
      // SA:RestricteContent - @todo: <CNL> Modify when enabling 2 SCH parallel execution
      //} // NumDqRot
  } // NumTests

  if ((DQPat == RdRdTA) || (DQPat == RdRdTA_All)) {
    // Restore original tRDRD value
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!((MRC_BIT0 << Channel) & ChBitMask)) {
        continue;
      }
      GetSetVal = tRDRD_sg_Min[Channel];
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDsg, WriteCached, &GetSetVal);
      GetSetVal = tRDRD_dg_Min[Channel];
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdg, WriteCached, &GetSetVal);
      if (DQPat == RdRdTA_All){
        GetSetVal = tRDRD_dr_Min[Channel];
        MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdr, WriteCached, &GetSetVal);
      }
      // Must update the XARB bubble injector when TAT values change
      SetTcBubbleInjector (MrcData, Channel);
    }
  }
  if (DQPat == CADB) {
    // Disable CADB on MC
    McCadbEnable (MrcData, FALSE);
    // Restore original command tri-state value
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (((1 << Channel) & ChBitMask) != 0) {
        MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccCmdTriStateDis, WriteCached, &CmdTriStateDisSave[Channel]);
      }
    }
  }

  return (ErrorStatus & ChBitMask);
}

/**
  Programs REUT to run on the selected physical ranks.

  @param[in] MrcData           - Pointer to MRC global data.
  @param[in] ch                - Channel to enable.
  @param[in] RankBitMask       - Bit mask of ranks to enable.
  @param[in] SkipRankL2P       - Boolean control over skipping Logical 2 Physical programming for Rank.
  @param[in] RankFeatureEnable - RankFeatureEnable is a bit mask that can enable CKE, Refresh or ZQ
                                 RankFeatureEnable[0] enables Refresh on all non-selected ranks
                                 RankFeatureEnable[1] enables Refresh on all ranks
                                 RankFeatureEnable[2] enables ZQ on all non-selected ranks
                                 RankFeatureEnable[3] enables ZQ on all ranks
                                 RankFeatureEnable[4] enables CKE on all non-selected ranks
                                 RankFeatureEnable[5] enables CKE on all ranks

  @retval Bit mask of channel enabled if rank in the channel exists.
**/
UINT8
SelectReutRanks (
  IN MrcParameters *const MrcData,
  IN const UINT8          ch,
  IN UINT8                RankBitMask,
  IN BOOLEAN              SkipRankL2P,
  IN const UINT8          RankFeatureEnable
  )
{
  MrcIntOutput  *MrcIntData;
  UINT32  Offset;
  UINT8   SubCh;
  UINT8   En;
  UINT8   rank;
  UINT8   RankCount;
  UINT8   RankCountMinusOne;
  INT64   GetSetVal;
  INT64   GetSetVal2;
  UINT8   OrigRankCount;
  CH0_CR_REUT_CH_MISC_REFRESH_CTRL_STRUCT       ReutChMiscRefreshCtrl;
  CH0_CR_REUT_CH_MISC_ZQ_CTRL_STRUCT            ReutChMiscZqCtrl;
  CH0_SC0_CR_CPGC2_ADDRESS_SIZE_STRUCT          Cpgc2AddrSize;
  CH0_SC0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_STRUCT CpgcSeqRankL2PMappingA;

  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));

  // Make sure valid rank bit mask for this channel
  RankBitMask &= MrcData->Outputs.Controller[0].Channel[ch].ValidRankBitMask;

//   MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_ERROR, "SelectReutRanks: ch%d, RankBitMask: %d  MrcIntData->ChSubChMaskEnable = 0x%08X\n", ch, RankBitMask, MrcIntData->ChSubChMaskEnable);

  // Check if nothing is selected
  if ((RankBitMask & 0xF) == 0) {
    // Disable CPGC / CADB engine on this channel
    MrcIntData->ChSubChMaskEnable &= ~(CPGC20_BITMASK_SUBCH_PER_CHANNEL << ch * CPGC20_NUM_SUBCH_PER_CHANNEL);
    return 0;
  } else {
    // Normal case
    // Setup REUT Test to iteration through appropriate ranks during test
    CpgcSeqRankL2PMappingA.Data = 0;
    RankCount                   = 0;

    // Prepare Rank Mapping and Max Rank
    if (!SkipRankL2P) {
      for (rank = 0; rank < MAX_RANK_IN_CHANNEL; rank++) {
        if ((MRC_BIT0 << rank) & RankBitMask) {
          CpgcSeqRankL2PMappingA.Data |= (rank << (CH0_SC0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_L2P_RANK0_MAPPING_WID * RankCount));
          RankCount += 1;
        }
      }
      // Write New Rank Mapping and Max Rank
      for (SubCh = 0; SubCh < MAX_SUB_CHANNEL; SubCh++) {
        if (!MrcSubChannelExist (MrcData, ch, SubCh)) {
          continue;
        }
        Offset = OFFSET_CALC_CH_SUBCH (
                  CH0_SC0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_REG,
                  CH1_SC0_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_REG, ch,
                  CH0_SC1_CR_CPGC_SEQ_RANK_L2P_MAPPING_A_REG, SubCh);
        MrcWriteCR (MrcData, Offset, CpgcSeqRankL2PMappingA.Data);
      }
    }

    RankCountMinusOne = RankCount - 1;
    for (SubCh = 0; SubCh < MrcIntData->SubChEngCount; SubCh++) {
      if (SUB_CH_MASK_CHECK (MrcIntData->ChSubChMaskEnable, ch, SubCh) == 0) {
        continue;
      }
      Offset = OFFSET_CALC_CH_SUBCH (
                CH0_SC0_CR_CPGC2_ADDRESS_SIZE_REG,
                CH1_SC0_CR_CPGC2_ADDRESS_SIZE_REG, ch,
                CH0_SC1_CR_CPGC2_ADDRESS_SIZE_REG, SubCh);
      Cpgc2AddrSize.Data = MrcReadCR (MrcData, Offset);
      OrigRankCount = (UINT8) (Cpgc2AddrSize.Bits.Block_Size_Num_Ranks + 1);
      if (OrigRankCount != RankCount) {
        Cpgc2AddrSize.Bits.Block_Size_Num_Ranks = RankCountMinusOne;
        MrcWriteCR (MrcData, Offset, Cpgc2AddrSize.Data);
        Cpgc20AdjustNumOfRanks (MrcData, ch, SubCh, OrigRankCount, RankCount);
      }
    }
  }

  if (RankFeatureEnable != 0) {
    // Enable Refresh and ZQ - 0's to the the desired ranks
    En = RankFeatureEnable & 0x3; // Refresh
    ReutChMiscRefreshCtrl.Data                    = 0;
    ReutChMiscRefreshCtrl.Bits.Refresh_Rank_Mask  = CH0_CR_REUT_CH_MISC_REFRESH_CTRL_Refresh_Rank_Mask_MAX;
    ReutChMiscRefreshCtrl.Bits.Panic_Refresh_Only = 1;

    if (En == 1) {
      ReutChMiscRefreshCtrl.Bits.Refresh_Rank_Mask = ~RankBitMask; // Enable all non-selected ranks
    } else if (En > 1) {
      ReutChMiscRefreshCtrl.Bits.Refresh_Rank_Mask = 0;           // Enable all ranks
    }
    if (En != 0) {
      Offset = OFFSET_CALC_CH (CH0_CR_REUT_CH_MISC_REFRESH_CTRL_REG, CH1_CR_REUT_CH_MISC_REFRESH_CTRL_REG, ch);
      MrcWriteCR (MrcData, Offset, ReutChMiscRefreshCtrl.Data);
    }

    En = (RankFeatureEnable >> 2) & 0x3; // ZQ
    ReutChMiscZqCtrl.Data              = 0;
    ReutChMiscZqCtrl.Bits.ZQ_Rank_Mask = CH0_CR_REUT_CH_MISC_ZQ_CTRL_ZQ_Rank_Mask_MAX;
    ReutChMiscZqCtrl.Bits.Always_Do_ZQ = 1;
    if (En == 1) {
      ReutChMiscZqCtrl.Bits.ZQ_Rank_Mask = ~RankBitMask;
    } else if (En > 1) {
      ReutChMiscZqCtrl.Bits.ZQ_Rank_Mask = 0; // Enable all ranks
    }
    if (En != 0) {
      Offset =  OFFSET_CALC_CH (CH0_CR_REUT_CH_MISC_ZQ_CTRL_REG, CH1_CR_REUT_CH_MISC_ZQ_CTRL_REG, ch);
      MrcWriteCR (MrcData, Offset, ReutChMiscZqCtrl.Data);
    }

    // Enable CKE ranks - 1's to enable desired ranks
    En = (RankFeatureEnable >> 4) & 0x3;
    GetSetVal = 0;
    GetSetVal2 = MRC_INT64_MAX;
    if (En == 1) {
      GetSetVal = ~RankBitMask; // Enable all non-selected ranks
      GetSetVal2 = ~RankBitMask;
    } else if (En > 1) {
      GetSetVal = MRC_INT64_MAX; // Enable all ranks.
      GetSetVal2 = MRC_INT64_MAX;
    }
    if (En != 0) {
      MrcGetSetDdrIoGroupChannel (MrcData, ch, GsmIocCkeOverride, WriteNoCache, &GetSetVal);
      MrcGetSetDdrIoGroupChannel (MrcData, ch, GsmIocCkeOn,       WriteNoCache, &GetSetVal2);
    }
  }

  return (UINT8) (MRC_BIT0 << ch);
}

/**
  Returns the index into the array MarginResult in the MrcOutput structure.

  @param[in] ParamV - Margin parameter

  @retval One of the following values: LastRxV(0), LastRxT (1), LastTxV(2), LastTxT (3), LastRcvEna (4),
                                       LastWrLevel (5), LastCmdT (6), LastCmdV (7)
**/
UINT8
GetMarginResultType (
  IN const UINT8 ParamV
  )
{
  switch (ParamV) {
    case WrV:
    case WrFan2:
    case WrFan3:
      return LastTxV;

    case WrT:
    case WrTLp4:
      return LastTxT;

    case RdV:
    case RdFan2:
    case RdFan3:
      return LastRxV;

    case RdT:
      return LastRxT;

    case RcvEna:
    case RcvEnaX:
      return LastRcvEna;

    case WrLevel:
      return LastWrLevel;

    case CmdT:
      return LastCmdT;

    case CmdV:
      return LastCmdV;

    default:
      //MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "GetMarginByte: Unknown Margin Parameter\n");
      break;
  }

  return 0; // Return LastRxV to point to the beginning of the array
}

/*
1D Margin Types:
RcvEn:   Shifts just RcvEn.  Only side effect is it may eat into read dq-dqs for first bit of burst
RdT:     Shifts read DQS timing, changing where DQ is sampled
WrT:     Shifts write DQ timing, margining DQ-DQS timing
WrDqsT:  Shifts write DQS timing, margining both DQ-DQS and DQS-CLK timing
RdV:     Shifts read Vref voltage for DQ only
WrV:     Shifts write Vref voltage for DQ only
WrLevel: Shifts write DQ and DQS timing, margining only DQS-CLK timing
WrTBit:  Shifts write DQ per bit timing.
RdTBit:  Shifts read DQ per bit timing.
RdVBit:  Shifts read DQ per bit voltage.

2D Margin Types (Voltage, Time)
RdFan2:  Margins both RdV and RdT at { (off, -2/3*off),  (off, 2/3*off) }
WrFan2:  Margins both WrV and WrT at { (off, -2/3*off),  (off, 2/3*off) }
RdFan3:  Margins both RdV and RdT at { (off, -2/3*off),  (5/4*off, 0),  (off, 2/3*off)  }
WrFan3:  Margins both WrV and WrT at { (off, -2/3*off),  (5/4*off, 0),  (off, 2/3*off)  }
*/
/**
  This function Reads MrcData structure and finds the minimum last recorded margin for param.
  Searches across all bytes and ranks in RankMask.  Bytes search depend on channel length.
  For Enhanced Channel Mode, Channel margin is stored in the first byte for that channel:
        LPDDR4: SysCh   Ch  Byte
                  0     0   0
                  1     0   4
                  2     1   0
                  3     1   4

  @param[in]     MrcData         - Include all MRC global data.
  @param[in,out] MarginResult    - Data structure with the latest margin results.
  @param[in]     Param           - Defines the margin type
  @param[in]     RankMask        - Condenses down the results from multiple ranks
  @param[in]     ResultRank      - This rank will keep the results from multiple ranks
  @param[in]     EnhancedChMode  - This parameter controls the margin search and location if we support x32 or x64 channels.

  @retval mrcWrongInputParameter if a bad Param is passed in, otherwise mrcSuccess.
**/
MrcStatus
GetMarginCh (
  IN     MrcParameters *const MrcData,
  IN OUT UINT32               MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     const UINT8          Param,
  IN     const UINT8          RankMask,
  IN     const UINT8          ResultRank,
  IN     const BOOLEAN        EnhancedChMode
  )
{
  MrcOutput     *Outputs;
  MrcChannelOut *ChannelOut;
  UINT32        *Margin1;
  UINT32        *Margin2;
  UINT32        SubCh;
  UINT8         ResultType;
  UINT8         Channel;
  UINT8         Rank;
  UINT8         Byte;
  UINT8         ByteStart;
  UINT8         ByteEnd;
  UINT8         Edge;
  UINT8         Scale;
  BOOLEAN       SubChMax;

  Outputs = &MrcData->Outputs;
  switch (Param) {
    case CmdV:
    case WrV:
    case WrT:
    case WrTLp4:
    case WrLevel:
    case RdV:
    case RdT:
    case RcvEna:
    case RcvEnaX:
      Scale = 10;
      break;

    case WrFan2:
    case WrFan3:
    case RdFan2:
    case RdFan3:
      Scale = 21 / 3;
      break;

    default:
      MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_ERROR, "GetMarginCh: Unknown Margin Parameter\n");
      return mrcWrongInputParameter;
  }

  SubChMax = (EnhancedChMode) ? MAX_SUB_CHANNEL : 1;
  ResultType = GetMarginResultType (Param);
  ResultType = MIN (MAX_RESULT_TYPE - 1, ResultType);
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut = &Outputs->Controller[CONTROLLER_0].Channel[Channel];
      for (SubCh = 0; SubCh < SubChMax; SubCh++) {
        if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
          continue;
        }
        ByteStart = (EnhancedChMode) ? ChannelOut->ByteStart[SubCh] : 0;
        ByteEnd   = (EnhancedChMode) ? ChannelOut->ByteEnd[SubCh] : Outputs->SdramCount - 1;
        Margin2 = &MarginResult[ResultType][ResultRank][Channel][ByteStart][0];
        for (Byte = ByteStart; Byte <= ByteEnd; Byte++) {
          for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
            if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
              continue;
            }
            if ((1 << Rank) & RankMask) {
              Margin1 = &MarginResult[ResultType][Rank][Channel][Byte][0];
              for (Edge = 0; Edge < MAX_EDGES; Edge++) {
                if (Margin2[Edge] > Margin1[Edge]) {
                  Margin2[Edge] = Margin1[Edge];
                }
              } // Edge
            }
          } // Rank
        } // Byte
        // Scale results as needed
        for (Edge = 0; Edge < MAX_EDGES; Edge++) {
          Margin2[Edge] = (Margin2[Edge] * Scale) / 10;
        } // Edge
      } // SubCh
    }
  } // Channel

  return mrcSuccess;
}


/**
  This function Reads MrcData structure and finds the minimum last recorded margin for param
  Searches across all bytes and ranks in RankMask

  @param[in]     MrcData         - Include all MRC global data.
  @param[in,out] MarginResult    - Data structure with the latest margin results.
  @param[in]     Param           - Defines the margin type
  @param[in]     Ranks           - Condenses down the results from multiple ranks

  @retval mrcWrongInputParameter if a bad Param is passed in, otherwise mrcSuccess.
**/
MrcStatus
GetPdaMargins (
  IN     MrcParameters *const MrcData,
  IN OUT UINT32               MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     const UINT8          Param,
  IN     const UINT8          Ranks
  )
{
  MrcOutput     *Outputs;
  MrcChannelOut *ChannelOut;
  MrcRankOut    *RankOut;
  UINT32        *Margin1;
  UINT8         ResultType;
  UINT8         Channel;
  UINT8         Rank;
  UINT8         Byte;
  UINT8         Edge;
  INT32         CurrentOff;
  INT32         GlobalCenter;
  INT32         MarginOffset;

  Outputs = &MrcData->Outputs;

  ResultType = GetMarginResultType (Param);
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    ChannelOut = &Outputs->Controller[0].Channel[Channel];
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if ((MrcRankInChannelExist (MrcData, Rank, Channel) & Ranks) == 0) {
        continue;
      }
      RankOut = &ChannelOut->Dimm[Rank / 2].Rank[Rank % 2];
      GlobalCenter = MrcVrefDqToOffsetDdr4 ((UINT8)(RankOut->MR[mrMR6] & 0x7F));
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        CurrentOff = MrcVrefDqToOffsetDdr4 (RankOut->Ddr4PdaMr6[Byte] & 0x7F);
        MarginOffset = 10 * (CurrentOff - GlobalCenter);
        Margin1 = &MarginResult[ResultType][Rank][Channel][Byte][0];
        for (Edge = 0; Edge < MAX_EDGES; Edge++) {
          if (Edge == 0) {
            Margin1[Edge] += MarginOffset;
          } else {
            Margin1[Edge] -= MarginOffset;
          }
          if ((INT16) Margin1[Edge] < 0) {
            Margin1[Edge] = 0;
          }
        } // for Edge
      } // for Byte
    } // for Rank
  } // for Channel

  return mrcSuccess;
}


/**
  Use this function to retrieve the last margin results from MrcData

  @param[in]     MrcData         - Include all MRC global data.
  @param[in,out] MarginResult    - Data structure with the latest margin results.
  @param[in]     Param           - Defines the margin type
  @param[in]     RankIn          - Which rank of the host structure you want the result returned on
  @param[in]     Ranks           - Condenses down the results from multiple ranks

  @retval MarginResult structure has been updated if MrcStatus returns mrcSuccess.
  @retval Otherwise, mrcWrongInputParameter is returned if an incorrect Param is passed in.
**/
MrcStatus
GetMarginByte (
  IN     MrcParameters *const MrcData,
  IN OUT UINT32               MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     const UINT8          Param,
  IN     const UINT8          RankIn,
  IN     const UINT8          Ranks
  )
{
  MrcOutput *Outputs;
  UINT32    *Margin1;
  UINT32    *Margin2;
  UINT8     ResultType;
  UINT8     Channel;
  UINT8     Rank;
  UINT8     Byte;
  UINT8     Edge;
  UINT8     Scale;

  Outputs = &MrcData->Outputs;
  switch (Param) {
    case WrV:
    case WrT:
    case WrTLp4:
    case WrLevel:
    case RdV:
    case RdT:
    case RcvEna:
    case RcvEnaX:
    case CmdT:
    case CmdV:
      Scale = 10;
      break;

    case WrFan2:
    case WrFan3:
    case RdFan2:
    case RdFan3:
      Scale = 21 / 3;
      break;

    default:
      MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_ERROR, "GetMarginByte: Unknown Margin Parameter\n");
      return mrcWrongInputParameter;
  }

  ResultType = GetMarginResultType (Param);
  ResultType = MIN (ResultType, MAX_RESULT_TYPE - 1);
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if (MrcRankInChannelExist (MrcData, Rank, Channel) & Ranks) {
            Margin1 = &MarginResult[ResultType][RankIn][Channel][Byte][0];
            Margin2 = &MarginResult[ResultType][Rank][Channel][Byte][0];
            for (Edge = 0; Edge < MAX_EDGES; Edge++) {
              if (Margin1[Edge] > Margin2[Edge]) {
                Margin1[Edge] = Margin2[Edge];
              }
            }
          }
        }
        // Scale results as needed
        Margin1 = &MarginResult[ResultType][RankIn][Channel][Byte][0];
        for (Edge = 0; Edge < MAX_EDGES; Edge++) {
          Margin1[Edge] = (Margin1[Edge] * Scale) / 10;
        }
      }
    }
  }

  return mrcSuccess;
}

/**
  This function is use to "unscale" the MrcData last margin point
  GetMarginByte will scale the results for FAN margin
  This will unscale the results such that future tests start at the correct point

  @param[in]     MrcData      - Include all MRC global data.
  @param[in,out] MarginResult - Input array to be unscaled.
  @param[in]     Param        - Defines the margin type for proper scale selection.
  @param[in]     Rank         - Which rank of the host structure to work on

  @retval mrcSuccess
**/
MrcStatus
ScaleMarginByte (
  IN     MrcParameters *const MrcData,
  IN OUT UINT32               MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     const UINT8          Param,
  IN     const UINT8          Rank
  )
{
  MrcOutput *Outputs;
  UINT32    *Margin;
  UINT8     ResultType;
  UINT8     Channel;
  UINT8     Byte;
  UINT8     Edge;

  // Calculate scale parameter based on param
  // Leave room for expansion in case other params needed to be scaled
  Outputs = &MrcData->Outputs;
  if ((Param == RdFan2) || (Param == RdFan3) || (Param == WrFan2) || (Param == WrFan3)) {
    ResultType = GetMarginResultType (Param);
    ResultType = MIN (MAX_RESULT_TYPE - 1, ResultType);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (Outputs, Channel)) {
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          Margin = &MarginResult[ResultType][Rank][Channel][Byte][0];
          for (Edge = 0; Edge < MAX_EDGES; Edge++) {
            Margin[Edge] = (Margin[Edge] * 15) / 10;
          }
        }
      }
    }
  }

  return mrcSuccess;
}

/**
  This function will return the rank used to store the results based on the Rank Mask passed in.
  Results will be stored in the first Rank existing in the RankMask.

  @param[in]  MrcData  - Include all MRC global data.
  @param[in]  RankMask - Bit mask of Ranks being margined.

  @retval mrcSuccess
**/
UINT8
GetRankToStoreResults (
  IN      MrcParameters *const MrcData,
  IN      UINT16               RankMask
  )
{
  UINT8              Rank;
  UINT8              RankLoop;
  MrcOutput         *Outputs;

  Outputs = &MrcData->Outputs;

  Rank = 0;
  if (RankMask == 0xFF) {
    return Rank;
  }
  // We return results on first available rank which is in RankMask.
  for (RankLoop = 0; RankLoop < MAX_RANK_IN_CHANNEL; RankLoop++) {
    if ((1 << RankLoop) & RankMask & Outputs->ValidRankMask) {
      Rank = RankLoop;
      break;
    }
  }
  return Rank;
}

/**
  This function checks to see if the margin parameter is a rank based parameter.  These tend to be
  things which are controlled on the DRAM Mode Register side.

  @param[in]  MrcData - Pointer to MRC global data.
  @param[in]  Param   - The parameter to check.  Must be from MRC_MarginTypes.

  @retval BOOLEAN - TRUE if it is a rank based margin parameter.  Otherwise FALSE.
**/
BOOLEAN
IsPerRankMarginParam (
  IN MrcParameters *const MrcData,
  IN UINT8                Param
  )
{
  MrcOutput *Outputs;
  BOOLEAN   Ddr4;
  BOOLEAN   Lpddr4;
  BOOLEAN   PerRankMp;

  Outputs = &MrcData->Outputs;
  Ddr4    = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr4  = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);

  switch (Param) {
    case WrV:
    case WrFan2:
    case WrFan3:
    case CmdV:
      // WrV is via MR in both DDR4 and LP4
      // CmdV is via MR in LP4, and it is per DIMM in DDR4 (from ICL B0), so treat is as per-rank as well
      PerRankMp = (Ddr4 || Lpddr4);
      break;
    case WrTBit:
    case RdTBit:
    case RdVBit:
      PerRankMp = TRUE;
      break;

    default:
      PerRankMp = FALSE;
      break;
  }

  return PerRankMp;
}

/**
  This function is a helper function for ChangeMargin.
  It is used to resolve inconsistent interface of ChaneMargin which interprets rankIn as a rank number (0, 1, 2, 3,...)
  and in other cases as a rank mask.
  This function will receive rankIn and additional parameters which are required in order to determine if rankIn should
  be interpreted as a rank mask or as a rank number, and return the rank mask or 0 if not a rank mask.

  @param[in,out] MrcData      - Include all MRC global data.
  @param[in]     Param        - Includes parameter(s) to change including two dimensional.
  @param[in]     RankIn       - rankIn from ChangeMargin
  @param[in]     EnMultiCast  - To enable Multicast (broadcast) or single register mode

  @retval RankMask - the RankMask or 0 if not a RankMask
**/
UINT8
CalcRankMask (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Param,
  IN     const UINT8          RankIn,
  IN     const UINT8          EnMultiCast
  )
{
  BOOLEAN PerRankControl;
  UINT8   RankMask;

  PerRankControl = IsPerRankMarginParam (MrcData, Param);
  if (PerRankControl) {
    if ((EnMultiCast == 1) && (RankIn == 0)) {
      // If EnMultiCast used and RankMask is 0 assume Rank Multicast
      RankMask = 0xF;
    } else {
      // If RankMask is not 0 do not override it
      RankMask = RankIn;
    }
  } else {
    // For non controllable per rank parameter don't use RankMask
    RankMask = 0;
  }

  return RankMask;
}

/**
  This function is a helper function for ChangeMargin.
  This function forms the correct Channel Mask based on the Margin Parameter, Channel, and Multicast settings.

  @param[in,out] MrcData      - Include all MRC global data.
  @param[in]     Param        - Includes parameter(s) to change including two dimensional.
  @param[in]     Channel      - 0-based Channel Index.
  @param[in]     EnMultiCast  - To enable Multicast (broadcast) or single register mode

  @retval UINT16 - Channel Bit Mask.
**/
UINT16
CalcChannelMask (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Param,
  IN     const UINT8          Channel,
  IN     const UINT8          EnMultiCast
  )
{
  MrcInput          *Inputs;
  MrcOutput         *Outputs;
  BOOLEAN            Ddr4;
  UINT16             ChannelMask;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Ddr4    = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

  ChannelMask = 0;

  if (Param == CmdV) {
    if (Ddr4 && (Inputs->CaVrefConfig == 0)) {
      // CaVrefConfig == 0: CAVrefIntCtl  is common to both channels, defined as CH0 CaVef
      ChannelMask = 0x1;
    } else {
      ChannelMask = (EnMultiCast) ? 0x3 : (1 << Channel);
    }
  } else if (Param == WrV) {
    ChannelMask = (EnMultiCast) ? 0x3 : (1 << Channel);
  }

  return ChannelMask;
}

/**
  This function is used by most margin search functions to change the underlying margin parameter.
  This function allows single search function to be used for different types of margins with minimal impact.
  It provides multiple different parameters, including 2D parameters like Read or Write FAN.
  It can work in either MultiCast or single register mode.

  @param[in,out] MrcData       - Include all MRC global data.
  @param[in]     param         - Includes parameter(s) to change including two dimensional.
  @param[in]     value0        - Selected value to program margin param to
  @param[in]     value1        - Selected value to program margin param to in 2D mode (FAN mode)
  @param[in]     EnMultiCast   - To enable Multicast (broadcast) or single register mode
  @param[in]     channel       - Desired Channel
  @param[in]     rankIn        - Desired Rank - used for the RxTBit, TxTBit, and RdVBit settings, and to propagate RdVref. For LP4 / Ddr4 WrV and LP4 CmdV we need to pass rank bit mask.
  @param[in]     byte          - Desired byte offset register. For DDR4 PDA byte is interpreted as byte mask
  @param[in]     bitIn         - Desired bit offset
  @param[in]     UpdateMrcData - Used to decide if MRC host must be updated
  @param[in]     SkipWait      - Used to skip wait until all channel are done

  @retval MrcStatus -  if succeeded, return mrcSuccess
**/
MrcStatus
ChangeMargin (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          param,
  IN     const INT32          value0,
  IN     const INT32          value1,
  IN     const UINT8          EnMultiCast,
  IN     const UINT8          channel,
  IN     const UINT8          rankIn,
  IN     const UINT16         byte,
  IN     const UINT8          bitIn,
  IN     const UINT8          UpdateMrcData,
  IN     const UINT8          SkipWait
  )
{
  // Programs margin param to the selected value0
  // If param is a 2D margin parameter (ex: FAN), then it uses both value0 and value1
  //    For an N point 2D parameter, value1 can be an integer from 0 to (N-1)
  //    For per bit timing parameter, value1 is the sign of the shift
  // param = {0:RcvEna, 1:RdT, 2:WrT, 3: WrDqsT, 4:RdV, 5:WrV, 6:WrLevel,
  //               7:WrTBox, 8:WrTBit, 9:RdTBit, 10:RdVBit, 13:CmdV,
  //              16:RdFan2, 17:WrFan2, 32:RdFan3, 33:WrFan3}
  // Note: For Write Vref, the trained value and margin register are the same
  // Note: rank is only used for the RxTBit, TxTBit, and RdVBit settings, and to propagate RdVref
  // Note: PerBit Settings (WrTBit, RdTBit, RdVBit) provide all 8 offsets in value0

  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *CurrentChannelOut;
  MrcStatus         Status;
  GSM_GT            Group[MRC_CHNG_MAR_GRP_NUM];
  INT64             GetSetVal[MRC_CHNG_MAR_GRP_NUM];
  UINT32            GsmMode;
  UINT32            ChannelStart;
  UINT32            ChannelEnd;
  UINT32            ChannelMask;
  UINT32            ByteStart;
  UINT32            ByteEnd;
  UINT32            CurrentCh;
  UINT32            CurrentByte;
  UINT32            GrpIdx;
  UINT32            PiCenter;
  UINT8             BitValue;
  UINT8             Max0;
  UINT8             MaxT;
  UINT8             Rank;
  UINT8             bit;
  INT32             sign;
  INT32             v0;
  INT32             v0Input;
  INT32             v1;
  INT32             Min;
  BOOLEAN           UpdateGrp[MRC_CHNG_MAR_GRP_NUM];
  BOOLEAN           PdaMode;
  BOOLEAN           Ddr4;
  UINT8             RankMask;
  UINT16            DeviceMask;

  Status            = mrcSuccess;
  Outputs           = &MrcData->Outputs;
  Debug             = &Outputs->Debug;
  ControllerOut     = &Outputs->Controller[0];
  Ddr4              = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  RankMask          = CalcRankMask (MrcData, param, rankIn, EnMultiCast);
  ChannelMask       = CalcChannelMask (MrcData, param, channel, EnMultiCast);
  PdaMode           = FALSE;
  DeviceMask        = 1;
  GsmMode           = (UpdateMrcData) ? ForceWriteCached : ForceWriteUncached;

  for (v0 = 0; v0 < MRC_CHNG_MAR_GRP_NUM; v0++) {
    UpdateGrp[v0] = FALSE;
    Group[v0]     = GsmGtMax;
    GetSetVal[v0] = 0;
  }

  Rank = 0;
  if (param == WrLevel) {
    // DQS DCC Update is per-rank, so get the rank number from the rank mask.
    // This is only called from RMT, so always per rank - rankIn should only have one rank selected.
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (((1 << Rank) & rankIn) != 0) {
        break;
      }
    }
  }

  // Pre-Process the margin numbers
  // Maximum value for Time
  MaxT = GetMaxPossibleTimingOffset (MrcData, param);
  Max0 = 0;
  if ((param < RdV) || (param == WrLevel) || (param == RcvEnaX)) {
    // RcvEna, RdT, WrT, WrDqsT, WrLevel
    Max0 = MaxT;
  } else if ((param == WrTBit) || (param == RdTBit) || (param == RdVBit) || (param == WrTLp4)) {
    Max0 = 0xFF;
  } else if ((param == RdV) || (param == RdFan2) || (param == RdFan3)) {
    Max0 = GetMaxPossibleVrefOffset (MrcData, param); // Vref for RdV and RdFan modes
  }
  // Pre-Process the margin numbers.  Calculate 2D points based on FAN slopes
  v0    = value0;
  sign  = (2 * value1 - 1);

  // For Fan3, optimize point orders to minimize Vref changes and # of tests required
  if (param >= RdFan3) {
    //   RdFan3, WrFan3
    sign = ((3 * value1 - 5) * value1) / 2;   // Translates to {0:0, 1:-1, 2:+1}
    if (value1 == 0) {
      v0 = (5 * value0) / 4;
    }
  }

  v1 = (sign * value0) / 3;

  // Value parameter checking is handled within MrcUpdateVref for WrV and CmdV
  if ((param != WrV) && (param != WrFan2) && (param != WrFan3) && (param != CmdV)) {
    Min = (-1) - Max0;
    v0 = RANGE (v0, Min, Max0);
  }

  Min = (-1) - MaxT;
  v1 = RANGE (v1, Min, MaxT);

  switch (param) {
    case RcvEna:
      UpdateGrp[0]  = TRUE;
      GetSetVal[0]  = v0;
      Group[0]      = RecEnOffset;
      break;

    case RdT:
      UpdateGrp[0]  = TRUE;
      GetSetVal[0]  = v0;
      Group[0]      = RxDqsOffset;
      break;

    case WrT:
      UpdateGrp[0]  = TRUE;
      GetSetVal[0]  = v0;
      Group[0]      = TxDqOffset;
      break;

    case WrDqsT:
      UpdateGrp[0]  = TRUE;
      GetSetVal[0]  = v0;
      Group[0]      = TxDqsOffset;
      break;

    case RdV:
      UpdateGrp[0]  = TRUE;
      GetSetVal[0]  = v0;
      Group[0]      = RxVrefOffset;
      break;

    case RcvEnaX:
      v0Input = v0; // save the input offset (after min/max truncate)
      for (CurrentCh = 0; CurrentCh < MAX_CHANNEL; CurrentCh++) {
        if ((MrcChannelExist (Outputs, CurrentCh)) && (EnMultiCast || (CurrentCh == channel))) {
          v0 = v0 * 4;
          for (CurrentByte = 0; (CurrentByte < Outputs->SdramCount); CurrentByte++) {
            if ((CurrentByte == byte) || (EnMultiCast)) {
              for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
                if (MrcRankInChannelExist (MrcData, Rank, CurrentCh)) {
                  // the assumption is that we are @ 1 Qclk before edge
                  GetSetVal[0] = v0;
                  MrcGetSetDdrIoGroupStrobe (
                    MrcData,
                    CurrentCh,
                    Rank,
                    CurrentByte,
                    RecEnDelay,
                    GsmMode | WriteOffsetUncached,
                    &GetSetVal[0]
                    );
                }
              }
            }
          }
        } // if channel exists
        v0 = v0Input; // restore v0 for next channel
      } // for CurrentCh
      break;

    case WrTLp4:
      // Determine the number of PI ticks to get 500ps.  TxDqs + 500ps + (32 for Gear1, 96 for Gear2) Pi ticks is the center point: v0 = 0;
      MrcGetTdqs2dqCenter (MrcData, &PiCenter);
      PiCenter = MrcPicoSec2PiTick (MrcData, PiCenter);
      for (CurrentCh = 0; CurrentCh < MAX_CHANNEL; CurrentCh++) {
        if ((MrcChannelExist (Outputs, CurrentCh)) && (EnMultiCast || (CurrentCh == channel))) {
          for (CurrentByte = 0; (CurrentByte < Outputs->SdramCount); CurrentByte++) {
            if ((CurrentByte == byte) || (EnMultiCast)) {
              // WrTLp4 is offset from TxDqsDelay
              MrcGetSetDdrIoGroupStrobe (
                MrcData,
                CurrentCh,
                rankIn,
                CurrentByte,
                TxDqsDelay,
                ReadFromCache,
                &GetSetVal[0]
                );
              GetSetVal[0] = GetSetVal[0] + PiCenter + v0 + (Outputs->Gear2 ? 96 : 32);
              MrcGetSetDdrIoGroupStrobe (
                MrcData,
                CurrentCh,
                rankIn,
                CurrentByte,
                TxDqDelay,
                GsmMode,
                &GetSetVal[0]
                );
            }
          }
        } // if channel exists
      } // for CurrentCh
      break;

    case CmdV:
      MrcUpdateVref(MrcData, ChannelMask, RankMask, byte, param, v0, UpdateMrcData, FALSE, SkipWait, TRUE);
      break;

    case WrV:
    case WrFan2:
    case WrFan3:
      PdaMode     = (Ddr4) && (byte != 0);
      DeviceMask  = PdaMode ? byte  : 1;

      MrcUpdateVref (MrcData, ChannelMask, RankMask, DeviceMask, param, v0, UpdateMrcData, PdaMode, SkipWait, TRUE);

      if ((param == WrFan2) || (param == WrFan3)) {
        // Update TxDqOffset
        GetSetVal[1]  = v1;
        Group[1]      = TxDqOffset;
        UpdateGrp[1]  = TRUE;
      }
      break;

    // Read margin in FAN modes. Update RxDqsOffset and ReadVrefOffset
    case RdFan2:
    case RdFan3:
      GetSetVal[0]  = v0;
      Group[0]      = RxVrefOffset;
      GetSetVal[1]  = v1;
      Group[1]      = RxDqsOffset;
      UpdateGrp[0]  = TRUE;
      UpdateGrp[1]  = TRUE;
      GsmMode       = ForceWriteCached;
      break;

    case WrLevel: // Write DQ and DQS timing, margining only DQS-CLK timing
      GetSetVal[0]  = v0;
      Group[0]      = TxDqOffset;
      GetSetVal[1]  = v0;
      Group[1]      = TxDqsOffset;
      UpdateGrp[0]  = TRUE;
      UpdateGrp[1]  = TRUE;
      GsmMode       = ForceWriteCached;
      break;

    case WrTBit:  // Write DQ per BIT timing
      if (EnMultiCast == 0) {
        ChannelStart  = channel;
        ChannelEnd    = channel + 1;
        ByteStart     = (UINT8) byte;
        ByteEnd       = (UINT8) byte + 1;
      } else {
        ChannelStart  = 0;
        ChannelEnd    = MAX_CHANNEL;
        ByteStart     = 0;
        ByteEnd       = Outputs->SdramCount;
      }

      for (CurrentCh = ChannelStart; CurrentCh < ChannelEnd; CurrentCh++) {
        CurrentChannelOut = &ControllerOut->Channel[CurrentCh];
        for (CurrentByte = ByteStart; CurrentByte < ByteEnd; CurrentByte++) {
          for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
            if ((MrcRankInChannelExist (MrcData, Rank, CurrentCh)) && ((1 << Rank) & RankMask))  {
              for (bit = 0; bit < MAX_BITS; bit++) {
                BitValue     = (((UINT32) value0) >> (4 * bit)) & 0xF;
                GetSetVal[0] = BitValue;
                // For Per Bits, they may exist in the same register.  So we always update the register cache.
                // Otherwise, the value gets corrupted.
                MrcGetSetDdrIoGroupSocket0 (MrcData, CurrentCh, Rank, CurrentByte, bit, TxDqBitDelay, WriteToCache, &GetSetVal[0]);
                if (UpdateMrcData) {
                  CurrentChannelOut->TxDqPb[Rank][CurrentByte][bit].Center = BitValue;
                }
              } // bit
            }
          }
        } // CurrentByte
      } // CurrentCh
      MrcFlushRegisterCachedData (MrcData);
      break;

    case RdTBit:  // Read DQ per BIT timing
      if (EnMultiCast == 0) {
        ChannelStart  = channel;
        ChannelEnd    = channel + 1;
        ByteStart     = (UINT8) byte;
        ByteEnd       = (UINT8) byte + 1;
      } else {
        ChannelStart  = 0;
        ChannelEnd    = MAX_CHANNEL;
        ByteStart     = 0;
        ByteEnd       = Outputs->SdramCount;
      }

      for (CurrentCh = ChannelStart; CurrentCh < ChannelEnd; CurrentCh++) {
        CurrentChannelOut = &ControllerOut->Channel[CurrentCh];
        for (CurrentByte = ByteStart; CurrentByte < ByteEnd; CurrentByte++) {
          for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
            if ((MrcRankInChannelExist (MrcData, Rank, CurrentCh)) && ((1 << Rank) & RankMask)) {
              for (bit = 0; bit < MAX_BITS; bit++) {
                BitValue     = (((UINT32) value0) >> (4 * bit)) & 0x0F;
                GetSetVal[0] = BitValue;
                // For Per Bits, they may exist in the same register.  So we always update the register cache.
                // Otherwise, the value gets corrupted.
                MrcGetSetDdrIoGroupSocket0 (MrcData, CurrentCh, Rank, CurrentByte, bit, RxDqBitDelay, WriteToCache, &GetSetVal[0]);
                if (UpdateMrcData) {
                  CurrentChannelOut->RxDqPb[Rank][CurrentByte][bit].Center = BitValue;
                }
              } // bit
            }
          }
        } // CurrentByte
      } // CurrentCh
      MrcFlushRegisterCachedData (MrcData);
      break;

    case RdVBit:  // Read DQ per BIT Voltage
      MRC_DEBUG_ASSERT (FALSE, Debug, "ChangeMargin: RdVBit is not supported !\n");
      if (EnMultiCast == 0) {
        ChannelStart  = channel;
        ChannelEnd    = channel + 1;
        ByteStart     = (UINT8) byte;
        ByteEnd       = (UINT8) byte + 1;
      } else {
        ChannelStart  = 0;
        ChannelEnd    = MAX_CHANNEL;
        ByteStart     = 0;
        ByteEnd       = Outputs->SdramCount;
      }

      for (CurrentCh = ChannelStart; CurrentCh < ChannelEnd; CurrentCh++){
        CurrentChannelOut = &ControllerOut->Channel[CurrentCh];
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if ((MrcRankInChannelExist (MrcData, Rank, CurrentCh)) && ((1 << Rank) & RankMask)) {
            for (CurrentByte = ByteStart; CurrentByte < ByteEnd; CurrentByte++) {
              for (bit = 0; bit < MAX_BITS; bit++) {
                BitValue     = (((UINT32) value0) >> (4 * bit)) & 0xF;
                GetSetVal[0] = BitValue;
                // For Per Bits, they may exist in the same register.  So we always update the register cache.
                // Otherwise, the value gets corrupted.
                MrcGetSetDdrIoGroupSocket0 (MrcData, CurrentCh, Rank, CurrentByte, bit, RxVoc, WriteToCache, &GetSetVal[0]);
                if (UpdateMrcData) {
                  CurrentChannelOut->RxDqVrefPb[Rank][CurrentByte][bit].Center = BitValue;
                }
              } // bit
            } // CurrentByte
          } // Rank exists and is in RankMask
        } // CurrentRank
      } // CurrentCh
      MrcFlushRegisterCachedData (MrcData);
      break;

    default:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "ChangeMargin: Invalid parameter %d\n", param);
      return mrcWrongInputParameter;
  } // end switch (param)

  for (GrpIdx = 0; GrpIdx < MRC_CHNG_MAR_GRP_NUM; GrpIdx++) {
    if (UpdateGrp[GrpIdx] == FALSE) {
      continue;
    }
    // Write CR
    if (EnMultiCast == 0) {
      ChannelStart  = channel;
      ChannelEnd    = channel + 1;
      ByteStart     = (UINT8) byte;
      ByteEnd       = (UINT8) byte + 1;
    } else {
      ChannelStart  = 0;
      ChannelEnd    = MAX_CHANNEL;
      ByteStart     = 0;
      ByteEnd       = Outputs->SdramCount;
    }
    for (CurrentCh = ChannelStart; CurrentCh < ChannelEnd; CurrentCh++) {
      if (!MrcChannelExist (Outputs, CurrentCh)) {
        continue;
      }
      for (CurrentByte = ByteStart; CurrentByte < ByteEnd; CurrentByte++) {
        MrcGetSetDdrIoGroupStrobe (
          MrcData,
          CurrentCh,
          (param == WrLevel) ? Rank : MRC_IGNORE_ARG,   // We need Rank in WrLevel case for DQS DCC Update
          CurrentByte,
          Group[GrpIdx],
          GsmMode,
          &GetSetVal[GrpIdx]
          );
      } // CurrentByte
    } // CurrentCh
  } // GrpIdx

  return Status;
}

/**
  This procedure returns the minimal required eye height for a given training step.
  This information is subsequently used differently for making decisions, e.g., MRCFailure, PDA writing, etc.

  @param[in,out] MrcData        - Include all MRC global data.
  @param[in]     EarlyCentering - Is Step an Early Training step.

  return MinWidth UINT8
**/
UINT8
GetMinRequiredEyeWidth (
  IN MrcParameters *const MrcData,
  IN BOOLEAN              EarlyCentering
)
{
  const MrcInput    *Inputs;
  const MrcOutput   *Outputs;
  UINT8             MinWidth;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;

  if ((Outputs->DdrType == MRC_DDR_TYPE_DDR4) && (Outputs->Frequency >= f2400)) {
    MinWidth = 4;
  } else if ((Inputs->MemoryProfile != STD_PROFILE) && (EarlyCentering)) {
    MinWidth = 1;
  } else {
    MinWidth = 8;
  }

  return MinWidth;
}

/**
  This procedure is meant to handle basic timing centering, places strobe in the middle of the data eye,
  for both read and write DQ/DQS using a very robust, linear search algorthim.

  @param[in,out] MrcData        - Include all MRC global data.
  @param[in]     chBitMaskIn    - Channel bit mask.
  @param[in]     param          - {0:RcvEn, 1:RdT, 2:WrT, 3: WrDqsT, 4:RdV, 5:WrV, 6:WrLevel,
                                   8:WrTBit, 9:RdTBit, 10:RdVBit,
                                   16:RdFan2, 17:WrFan2, 32:RdFan3, 32:WrFan3}
                                   ONLY RdT and WrT are allowed in this function
  @param[in]     ResetPerBit    - Option to Reset PerBit Deskew to middle value before byte training
  @param[in]     loopcount      - loop count
  @param[in]     MsgPrint       - Show debug prints
  @param[in]     EarlyCentering - Execute as early centering routine

  @retval MrcStatus -  If succeeded, return mrcSuccess
**/
MrcStatus
DQTimeCentering1D (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          chBitMaskIn,
  IN     const UINT8          param,
  IN     const UINT8          ResetPerBit,
  IN     const UINT8          loopcount,
  IN     BOOLEAN              MsgPrint,
  IN     BOOLEAN              EarlyCentering
  )
{
  const MrcInput    *Inputs;
  const MRC_FUNCTION *MrcCall;
  MrcDebug          *Debug;
  MrcDebugMsgLevel   DebugLevel;
  MrcOutput         *Outputs;
  MrcIntOutput      *IntOutputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcStatus         Status;
  GSM_GT            GsParam;
  UINT64            ErrStatus;
  INT64             GetSetVal;
  INT64             GsMinValue;
  INT64             GsMaxValue;
  INT32             *CurrentPS;
  INT32             *CurrentPE;
  INT32             *LargestPS;
  INT32             *LargestPE;
  INT32             ByteCenter[MAX_SDRAM_IN_DIMM];
  INT32             LargestPSCh[MAX_CHANNEL];
  INT32             LargestPECh[MAX_CHANNEL];
  INT32             CurrentPassingStart[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             CurrentPassingEnd[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             LargestPassingStart[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             LargestPassingEnd[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             cWidth;
  INT32             lWidth;
  INT32             Center;
  INT32             RankCenter;
  INT32             DqsDelay;
  INT32             DqsStart;
  INT32             DqsStop;
  INT32             Vref;
  UINT32            UiMask;
  UINT32            *Margin;
  UINT32            Start;
  UINT32            End;
  UINT32            Tdqs2dqCenterFs;
  UINT16            Result;
  UINT8             Channel;
  UINT8             SubCh;
  UINT8             Rank;
  UINT8             RankMask;
  UINT8             RankRx;
  UINT8             Byte;
  UINT8             Step;
  UINT8             MinWidth;
  UINT8             chBitMask;
  UINT32            Index;
  BOOLEAN           Pass;
  BOOLEAN           Ddr4;
  BOOLEAN           Lpddr4;
  BOOLEAN           EccSupport;
  BOOLEAN           EyeTooSmall[MAX_CHANNEL][MAX_RANK_IN_CHANNEL];
  BOOLEAN           Gear2;
  BOOLEAN           GetSetParam;
  GSM_GT            GroupType;
#ifdef MRC_DEBUG_PRINT
  UINT64            BitLaneFailures[MAX_CHANNEL][MRC_1D_ERROR_LEN];
  UINT8             EccBitLaneFailures[MAX_CHANNEL][MRC_1D_ERROR_LEN];
  UINT8             BitErrStatus[MAX_SDRAM_IN_DIMM];
  UINT8             BitCountTensMax;
  UINT8             BitCountMax;
  UINT32            ErrorCount;
  UINT8             BitCount;
  const char        *DelayString;
  BOOLEAN           Overflow;
  UINT64            ChunkStatus;
  UINT16            ChunkResult[MAX_CHANNEL][MAX_SUB_CHANNEL];
#endif
  MrcIntControllerOut   *IntControllerOut;
  MrcIntClkAlignedParam *ClkAlignParam;

  IntOutputs = (MrcIntOutput *)(MrcData->IntOutputs.Internal);
  IntControllerOut = &IntOutputs->Controller[0];

  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  chBitMask     = chBitMaskIn;
  Status        = mrcSuccess;
  Center        = 0;
  RankCenter    = 0;
  Step          = 1;
  Ddr4          = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr4        = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  EccSupport    = Outputs->EccSupport;
  DebugLevel    = MsgPrint ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;
  MinWidth      = GetMinRequiredEyeWidth (MrcData, EarlyCentering);
  DebugLevel    = MsgPrint ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;
  MrcCall->MrcSetMem ((UINT8 *) EyeTooSmall, sizeof (EyeTooSmall), FALSE);
  MrcCall->MrcSetMem ((UINT8 *) ByteCenter, sizeof(ByteCenter), 0);
  MrcCall->MrcSetMem ((UINT8 *) LargestPSCh, sizeof (LargestPSCh), 0);
  MrcCall->MrcSetMem ((UINT8 *) LargestPECh, sizeof (LargestPECh), 0);

  if ((param != RcvEna) && (param != RdT) && (param != WrT) && (param != RcvEnaX)  && (param != WrV) && (param != RdV) && (param != CmdV) && (param != WrTLp4) && (param != RdTN) && (param !=RdTP)) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "DataTimeCentering1D: Unknown Margin Parameter\n");
    return mrcWrongInputParameter;
  }
  GetSetParam = ((param == RdTN) || (param == RdTP));
  if (param == RdTN) {
    GsParam = RxDqsNDelay;
  } else if (param == RdTP) {
    GsParam = RxDqsPDelay;
  } else {
    GsParam = GsmGtMax;
  }

  Gear2 = Outputs->Gear2;
  if (Lpddr4 && (Outputs->Frequency == f1067)) {
    Gear2 = FALSE;
  }

  if ((param == WrV) && Lpddr4 && EarlyCentering) {
    Step = 2;
  }

  if ((param == CmdV) && (Inputs->MemoryProfile == STD_PROFILE)) {
    Step = 2;
  }

  if ((param == WrV) || (param == CmdV) || (param == RdV)) {
    DqsStop = GetMaxPossibleVrefOffset (MrcData, param);
    DqsStart = -1 * DqsStop;
  } else if (param == WrTLp4) {
    MrcGetTdqs2dqCenter (MrcData, &Tdqs2dqCenterFs);
    DqsStart = -1 * MrcPicoSec2PiTick (MrcData, Tdqs2dqCenterFs);
    DqsStop = MrcPicoSec2PiTick (MrcData, Tdqs2dqCenterFs);
  } else if (GetSetParam) {
    MrcGetSetLimits (MrcData, GsParam, &GsMinValue, &GsMaxValue, NULL);
    DqsStart = (INT32) GsMinValue;
    DqsStop  = (INT32) GsMaxValue;
  } else {
    DqsStop  = GetMaxPossibleTimingOffset (MrcData, param);
    DqsStart = -1 * DqsStop;
  }
  if (!Outputs->UseExistingStress) {
    if (param == RcvEnaX) {
      SetupIOTestBasicVA (MrcData, chBitMask, loopcount - 3, NSOE, 0, 0, 8);
      Outputs->DQPat = RdRdTA_All;
    } else if (param == CmdV) {
      SetupIOTestCADB (MrcData, chBitMask, loopcount, NSOE, 1, 0);
    } else {
      SetupIOTestBasicVA (MrcData, chBitMask, loopcount, NSOE, 0, 0, 8);
    }
  }
  // Program chunk mask for RxDqsP/N.
  // This is set to all chunks in SetupIOTest, so needs to be done after calling SetupIOTest.
  if (GetSetParam) {
    // For RxDqsP check only even chunks
    UiMask = 0x5555;
    if (GsParam == RxDqsNDelay) {
      // For RxDqsN check only odd chunks
      UiMask = UiMask << 1;
    }
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (chBitMask & (1 << Channel)) {
        MrcSetChunkAndClErrMsk (MrcData, Channel, 0xFF, UiMask);
      }
    }
  }

#ifdef MRC_DEBUG_PRINT
  switch (param) {
    case RcvEnaX :
    case RcvEna:
      DelayString = RcvEnDelayString;
      break;
    case WrV :
      DelayString = WrVDelayString;
      break;
    case RdV :
      DelayString = RdVDelayString;
      break;
    case CmdV:
      DelayString = CmdVDelayString;
      break;
    default :
      DelayString = DqsDelayString;
  }
#endif
  // Reset PerBit Deskew to middle value before byte training
  // Write timing offset for bit[x] of the DQ byte. Linear from 0-MAX, each step size is tQCLK/64
  // Read timing offset for bit[x] of the DQ byte. Linear from 0-MAX, each step size is tQCLK/64
  if (ResetPerBit == 1) {
    GroupType = (param == RdT) ? RxDqBitDelay : TxDqBitDelay;
    MrcGetSetLimits (MrcData, GroupType, NULL, &GetSetVal, NULL);
    GetSetVal = (((UINT8) GetSetVal) + 1) / 2;
    MrcGetSetDdrIoGroupSocket0 (MrcData, MAX_CHANNEL, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, MAX_BITS, GroupType, WriteToCache, &GetSetVal);
    MrcFlushRegisterCachedData (MrcData);
  }

  // Center all Ranks

  if ((param == WrV) && Ddr4) {
    Outputs->Ddr4PdaEnable = TRUE;
  }

  if (param == RcvEnaX) {
    // Make sure RecEnDelay values exist in CR cache for this algorithm to work, because we will use WriteOffsetUncached
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RecEnDelay, ReadCached, &GetSetVal);
          }
        }
      }
    }
  }

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
#ifdef MRC_DEBUG_PRINT
    if (Outputs->ValidRankMask & (MRC_BIT0 << Rank)) {
      MRC_DEBUG_MSG (Debug, DebugLevel, "Rank = %d\nChannel 0                1\nByte\t", Rank);
      MRC_DEBUG_MSG (
        Debug,
        DebugLevel, (
        EccSupport
        ) ? "0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8 Error Count" : "0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 Error Count"
        );
    }
#endif  // MRC_DEBUG_PRINT
    chBitMask = 0;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut = &ControllerOut->Channel[Channel];
      if (param == RcvEnaX) {
        if ((ChannelOut->ValidRankBitMask & (1 << Rank)) != 0) { // If rank under test exists, then select all ranks
          RankMask = 0xFF; // run on all available ranks for TAT stress
        } else {
          RankMask = 0;
        }
      } else if (param == RdV) {
        RankMask = 0xFF; // run on all available ranks for RdV param - we dont use different vref per rank
      } else {
        RankMask = (1 << Rank);
      }
      chBitMask |= SelectReutRanks (MrcData, Channel, RankMask, FALSE, 0);

      if ((1 << Channel) & chBitMask) {
        // Clear out anything left over in DataOffsetTrain
        // Update rank timing to middle value
        for (Byte = 0; (Byte < Outputs->SdramCount) && (param != RcvEnaX) && (param != WrV); Byte++) {
          if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
            continue;
          }
          if (param == RdT) {
            // Read Dq/Dqs
            GetSetVal = Gear2 ? 64 : 32;
            MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RxDqsPDelay, WriteCached, &GetSetVal);
            MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RxDqsNDelay, WriteCached, &GetSetVal);
          } else if (param == WrT) {
            // Write Dq/Dqs
            // We want to preserve the relation of tDQS2DQ for LPDDR4, so adjust TxDQ here for matched architectured DRAM types.
            if (!Lpddr4) {
              MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqsDelay, ReadFromCache, &GetSetVal);
              GetSetVal += (Outputs->Gear2 ? 96 : 32);
              MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqDelay, WriteCached, &GetSetVal);
            }
          } else if (param == RdV) {
            // Update Vref
            MrcGetSetLimits (MrcData, RxVref, &GsMinValue, &GsMaxValue, NULL);
            GetSetVal = ((INT32) GsMinValue + (INT32) GsMaxValue) / 2;
            if (Lpddr4) {
              GetSetVal = (INT32) GetSetVal / 2;
            }
            if (!Inputs->LoopBackTest) {
              MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, RxVref, WriteCached, &GetSetVal);
            }
          }
        } // Byte
        if ((param == WrV) || (param == CmdV)) {
          // Write Vref - program to middle (zero offset) range before sweep
          if (Ddr4 && (param == CmdV)) {
            Vref = MID_INT_VREF;
          } else {
            //  Lpddr4 CmdV, WrV ; Ddr4 WrV
            Vref = 0;
          }
          MrcUpdateVref (MrcData, 1 << Channel, 1 << Rank, 0, param, Vref, TRUE, FALSE, FALSE, FALSE);
        }
        // Setup REUT Error Counters to count errors on all lanes
        for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
          if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
            MrcSetupErrCounterCtl (MrcData, Channel, SubCh, 0, ErrCounterCtlAllLanes);
          }
        } // for SubCh
      } // ((1 << Channel) & chBitMask)
    } // for Channel
    // Continue if not valid rank on any channel
    if (chBitMask == 0) {
      continue; // This rank does not exist on any of the channels
    }
    // Sweep through values
    MRC_DEBUG_MSG (Debug, DebugLevel, "\n%s", DelayString);
    if (((param == WrV) && (Ddr4 || Lpddr4)) ||
        ((param == CmdV) && Lpddr4)) {
      RankMask = 1 << Rank;
    } else {
      RankMask = Rank;
    }
    for (DqsDelay = DqsStart, Index = 0; DqsDelay <= DqsStop; DqsDelay += Step, Index++) {
      // Program DQS Delays
      if (GetSetParam) {
        GetSetVal = DqsDelay;
        MrcGetSetDdrIoGroupStrobe (MrcData, MAX_CHANNEL, Rank, MAX_SDRAM_IN_DIMM, GsParam, WriteCached, &GetSetVal);
      } else {
        ChangeMargin (MrcData, param, DqsDelay, 0, 1, 0, RankMask, 0, 0, 0, 0);
      }
      // Clear Errors and Run Test
      if ((param == CmdV) && EarlyCentering) {
        ReadMprTraining (MrcData, 1 << Rank, 8, MRC_PRINTS_OFF); // HW-based, steps of 8
      } else {
        RunIOTest (MrcData, chBitMask, Outputs->DQPat, 1, 0);
      }
      if (param == CmdV) {
        MrcResetSequence (MrcData);
      }
      IoReset (MrcData);
      MRC_DEBUG_MSG (Debug, DebugLevel, "\n% 5d  \t", DqsDelay);
      // Update results for all Channel/bytes
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(chBitMask & (MRC_BIT0 << Channel))) {
          MRC_DEBUG_MSG (
            Debug,
            DebugLevel,
            (Channel != 0) ? "" : (EccSupport ? "                  " : "                ")
            );
          continue;
        }
        ChannelOut = &ControllerOut->Channel[Channel];
        Result = 0;
#ifdef MRC_DEBUG_PRINT
        MRC_DEBUG_ASSERT (Index < MRC_1D_ERROR_LEN, Debug, "Index exceeds debug array %u > %u\n", Index, MRC_1D_ERROR_LEN);
        BitLaneFailures[Channel][Index] = 0;
#endif
        for (SubCh = 0; SubCh < IntOutputs->SubChEngCount; SubCh++) {
          if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
            // Read out per byte and per bit error results
            MrcGetMiscErrStatus (MrcData, Channel, SubCh, ByteGroupErrStatus, &ErrStatus);
            Result |= MrcCall->MrcLeftShift64 (ErrStatus, (SubCh == 0) ? 0 : 4);
#ifdef MRC_DEBUG_PRINT
            MrcGetBitGroupErrStatus (MrcData, Channel, SubCh, BitErrStatus);
            // Read per chunk error status
            MrcGetMiscErrStatus (MrcData, Channel, SubCh, ChunkErrStatus, &ChunkStatus);
            ChunkResult[Channel][SubCh] = (UINT16) ChunkStatus;
#endif
          } // MrcSubChannelExist
        } // for SubCh
#ifdef MRC_DEBUG_PRINT
        if (MsgPrint) {
          for (Byte = 0; Byte < MAX_SDRAM_IN_DIMM - 1; Byte++) {
            BitLaneFailures[Channel][Index] |= MrcCall->MrcLeftShift64 ((UINT64) BitErrStatus[Byte], 8 * Byte);
          }
          if (EccSupport) {
            EccBitLaneFailures[Channel][Index] = BitErrStatus[8];
          }
        }
#endif

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
            MRC_DEBUG_MSG (Debug, DebugLevel, "  ");
            continue;
          }
          // Check for Byte group error status
          Pass = ((Result & (MRC_BIT0 << Byte)) == 0);
          if ((param == CmdV) && EarlyCentering) {
            // Get ReadMpr eye size for this byte
            Pass = ((Outputs->MarginResult[LastRxT][Rank][Channel][Byte][0] + Outputs->MarginResult[LastRxT][Rank][Channel][Byte][1]) > 20);
          }
          MRC_DEBUG_MSG (Debug, DebugLevel, Pass ? ". " : "# ");
          CurrentPS = &CurrentPassingStart[Channel][Byte];
          CurrentPE = &CurrentPassingEnd[Channel][Byte];
          LargestPS = &LargestPassingStart[Channel][Byte];
          LargestPE = &LargestPassingEnd[Channel][Byte];
          if (DqsDelay == DqsStart) {
            if (Pass) {
              // No error on this Byte group
              *CurrentPS = *CurrentPE = *LargestPS = *LargestPE = DqsDelay;
            } else {
              // Selected Byte group has accumulated an error during loop back pattern
              *CurrentPS = *CurrentPE = *LargestPS = *LargestPE = DqsStart - 2;
            }
          } else {
            if (Pass) {
              // No error on this Byte group
              if (*CurrentPE != (DqsDelay - Step)) {
                *CurrentPS = DqsDelay;
              }
              *CurrentPE = DqsDelay;
              // Update Largest variables
              cWidth = *CurrentPE - *CurrentPS;
              lWidth = *LargestPE - *LargestPS;
              if (cWidth > lWidth) {
                *LargestPS = *CurrentPS;
                *LargestPE = *CurrentPE;
              }
            }
          }
          if (Byte == 0) {
            LargestPSCh[Channel] = *LargestPS;
            LargestPECh[Channel] = *LargestPE;
          } else {
            LargestPSCh[Channel] = MAX (LargestPSCh[Channel], *LargestPS);
            LargestPECh[Channel] = MIN (LargestPECh[Channel], *LargestPE);
          }
        } // for Byte
      } // for Channel
#ifdef MRC_DEBUG_PRINT
      if ((param != CmdV) || !EarlyCentering) {  // Skip Error Count prints for Early CmdV
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (chBitMask & (MRC_BIT0 << Channel)) {
            for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
              if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
                MrcGetErrCounterStatus (MrcData, Channel, SubCh, 0, ErrCounterCtlAllLanes, &ErrorCount, &Overflow);
                MRC_DEBUG_MSG (Debug, DebugLevel, " 0x%x  0x%x\t", ErrorCount, ChunkResult[Channel][SubCh]);
              } else {
                MRC_DEBUG_MSG (Debug, DebugLevel, "\t");
              }
            } // for SubCh
            // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "0x%016llX ", BitLaneFailures[Channel][Index]);
          }
        } // for Channel
      }
#endif  // MRC_DEBUG_PRINT
/*    {
        char Buf[10];
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nPause..\n");
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CH0_SC0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT: 0x%X\n", MrcReadCR (MrcData, CH0_SC0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_REG));
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CH0_SC1_CR_CPGC_ERR_BYTE_NTH_PAR_STAT: 0x%X\n", MrcReadCR (MrcData, CH0_SC1_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_REG));
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CH1_SC0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT: 0x%X\n", MrcReadCR (MrcData, CH1_SC0_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_REG));
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CH1_SC1_CR_CPGC_ERR_BYTE_NTH_PAR_STAT: 0x%X\n", MrcReadCR (MrcData, CH1_SC1_CR_CPGC_ERR_BYTE_NTH_PAR_STAT_REG));

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CH0_SC0_CR_CPGC_ERR_STAT03_REG: 0x%X\n", MrcReadCR (MrcData, CH0_SC0_CR_CPGC_ERR_STAT03_REG));
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CH0_SC1_CR_CPGC_ERR_STAT03_REG: 0x%X\n", MrcReadCR (MrcData, CH0_SC1_CR_CPGC_ERR_STAT03_REG));
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CH0_SC0_CR_CPGC_ERR_STAT47_REG: 0x%X\n", MrcReadCR (MrcData, CH0_SC0_CR_CPGC_ERR_STAT47_REG));
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CH0_SC1_CR_CPGC_ERR_STAT47_REG: 0x%X\n", MrcReadCR (MrcData, CH0_SC1_CR_CPGC_ERR_STAT47_REG));

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CH1_SC0_CR_CPGC_ERR_STAT03_REG: 0x%X\n", MrcReadCR (MrcData, CH1_SC0_CR_CPGC_ERR_STAT03_REG));
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CH1_SC1_CR_CPGC_ERR_STAT03_REG: 0x%X\n", MrcReadCR (MrcData, CH1_SC1_CR_CPGC_ERR_STAT03_REG));
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CH1_SC0_CR_CPGC_ERR_STAT47_REG: 0x%X\n", MrcReadCR (MrcData, CH1_SC0_CR_CPGC_ERR_STAT47_REG));
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CH1_SC1_CR_CPGC_ERR_STAT47_REG: 0x%X\n", MrcReadCR (MrcData, CH1_SC1_CR_CPGC_ERR_STAT47_REG));
        MrcGets ((char *) Buf, sizeof (Buf));
      } */
    } // for DqsDelay
    MRC_DEBUG_MSG (Debug, DebugLevel, "\n");  // End last line of Byte table.
#ifdef MRC_DEBUG_PRINT
    // Print out the bit lane failure information
    if (param != CmdV) {
      if (EccSupport) {
        BitCountMax = 72;
        BitCountTensMax = 8;
      } else {
        BitCountMax = 64;
        BitCountTensMax = 7;
      }
      MRC_DEBUG_MSG (Debug, DebugLevel, "Bit Lane Information\n");
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (chBitMask & (1 << Channel)) {
          MRC_DEBUG_MSG (Debug, DebugLevel, "Channel %d\nBitLane ", Channel);
          for (BitCount = 0; BitCount < BitCountTensMax; BitCount++) {
            MRC_DEBUG_MSG (Debug, DebugLevel, "%u         ", BitCount);
          }
          MRC_DEBUG_MSG (Debug, DebugLevel, "\n        ");  // End tens number and align ones number
          for (BitCount = 0; BitCount < BitCountMax; BitCount++) {
            MRC_DEBUG_MSG (Debug, DebugLevel, "%u", BitCount % 10);
          }
          MRC_DEBUG_MSG (Debug, DebugLevel, "\n%s", DelayString);
          for (DqsDelay = DqsStart, Index = 0; DqsDelay <= DqsStop; DqsDelay += Step, Index++) {
            MRC_DEBUG_MSG (Debug, DebugLevel, "\n% 5d\t", DqsDelay); // Begin with a new line and print the DqsDelay value
            for (BitCount = 0; BitCount < 64; BitCount++) {
              if (MrcByteInChannelExist (MrcData, Channel, BitCount / 8)) {
                MRC_DEBUG_MSG (
                  Debug,
                  DebugLevel,
                  (BitLaneFailures[Channel][Index] & MrcCall->MrcLeftShift64 (1, BitCount)) ? "#" : "."
                  );
              } else {
                MRC_DEBUG_MSG (Debug, DebugLevel, " ");
              }
            } // BitCount
            if (EccSupport) {
              for (BitCount = 0; BitCount < MAX_BITS; BitCount++) {
                MRC_DEBUG_MSG (
                  Debug,
                  DebugLevel,
                  (EccBitLaneFailures[Channel][Index] & (1 << BitCount)) ? "#" : "."
                  );
              }
            } //EccSupport
          } // DqsDelay
          MRC_DEBUG_MSG (Debug, DebugLevel, "\n"); // Gap after Channel
        } // (chBitMask & (1 << Channel))
      } // Channel
    } // (param != CmdV)
#endif
    // Clean Up for next Rank
    if (!GetSetParam) {
      ChangeMargin (MrcData, param, 0, 0, 1, 0, RankMask, 0, 0, 0, 0);
    }
    if (param == CmdV) {
      MrcResetSequence (MrcData);
    }
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        ByteCenter[Byte] = 0;
      }
      if (chBitMask & (MRC_BIT0 << Channel)) {
        ChannelOut = &ControllerOut->Channel[Channel];
        MRC_DEBUG_MSG (Debug, DebugLevel, "C%d.R%d:  Left\tRight\tWidth\tCenter\n", Channel, Rank);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
            continue;
          }
          LargestPS = &LargestPassingStart[Channel][Byte];
          LargestPE = &LargestPassingEnd[Channel][Byte];
          if (*LargestPS == *LargestPE) {
            // we like to see 0 margins when the eye closed ;)
            *LargestPS = *LargestPE = 0;
            LargestPSCh[Channel] = LargestPECh[Channel] = 0;
          }
          lWidth = *LargestPE - *LargestPS;
          Center = *LargestPS + (lWidth / 2);
          if (lWidth < MinWidth) {
            EyeTooSmall[Channel][Rank] = TRUE;
            MRC_DEBUG_MSG (
              Debug,
              DebugLevel,
              "ERROR!! DataTimeCentering1D Eye Too Small Channel: %u, Rank: %u, Byte: %u\n",
              Channel,
              Rank,
              Byte
              );
            if (Inputs->ExitOnFailure) {
              Status = mrcDataTimeCentering1DErr;
            }
          }
          MRC_DEBUG_MSG (
            Debug,
            DebugLevel,
            "  B%d:   %d\t%d\t%d\t%d\n",
            Byte,
            *LargestPS,
            *LargestPE,
            lWidth,
            Center
            );
          // Store the new margins relative to the center into MarginResult
          Start = ABS ((*LargestPS - Center) * 10);
          End   = ABS ((*LargestPE - Center) * 10);
          if (param == RdT) {
            // read Dq./Dqs
            Margin    = &Outputs->MarginResult[LastRxT][Rank][Channel][Byte][0];
            *Margin   = Start;
            Margin[1] = End;
            GetSetVal = Center;
            MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RxDqsPDelay, WriteOffsetCached, &GetSetVal);
            MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RxDqsNDelay, WriteOffsetCached, &GetSetVal);
          } else if (GetSetParam) { // RdTN / RdTP
            Margin = &Outputs->MarginResult[LastRxT][Rank][Channel][Byte][0];
            Margin[0] = Start;
            Margin[1] = End;
            GetSetVal = Center;
            MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, GsParam, WriteCached, &GetSetVal);
          } else if (param == WrT) {
            // Write Dq/Dqs
            Margin    = &Outputs->MarginResult[LastTxT][Rank][Channel][Byte][0];
            *Margin   = Start;
            Margin[1] = End;
            GetSetVal = Center;
            MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqDelay, WriteOffsetCached, &GetSetVal);
            ClkAlignParam = &IntControllerOut->IntClkAlignedMargins[Channel][Rank][Byte];
            MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqDelay, ReadFromCache, &GetSetVal);
            ClkAlignParam->TxDq = (UINT16) (GetSetVal);
          } else if (param == RcvEnaX) {
            // Receive Enable X
            for (RankRx = 0; RankRx < MAX_RANK_IN_CHANNEL; RankRx++) {
              if (ChannelOut->ValidRankBitMask & (MRC_BIT0 << RankRx)) {
                Margin    = &Outputs->MarginResult[LastRcvEna][RankRx][Channel][Byte][0];
                *Margin   = Start;
                Margin[1] = End;
                GetSetVal = 4 * Center;
                MrcGetSetDdrIoGroupStrobe (MrcData, Channel, RankRx, Byte, RecEnDelay, WriteOffsetCached, &GetSetVal);
                ClkAlignParam = &IntControllerOut->IntClkAlignedMargins[Channel][Rank][Byte];
                MrcGetSetDdrIoGroupStrobe(MrcData, Channel, Rank, Byte, RecEnDelay, ReadFromCache, &GetSetVal);
                ClkAlignParam->RcvEn = (UINT16)(GetSetVal);
              }
            }
          } else if (param == RcvEna) {
            // Receive Enable
            Margin    = &Outputs->MarginResult[LastRcvEna][Rank][Channel][Byte][0];
            *Margin   = Start;
            Margin[1] = End;
            GetSetVal = Center;
            MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RecEnDelay, WriteOffsetCached, &GetSetVal);
            ClkAlignParam = &IntControllerOut->IntClkAlignedMargins[Channel][Rank][Byte];
            MrcGetSetDdrIoGroupStrobe(MrcData, Channel, Rank, Byte, RecEnDelay, ReadFromCache, &GetSetVal);
            ClkAlignParam->RcvEn = (UINT16)(GetSetVal);
          } else if (param == WrTLp4) {
            // Write Dq/Dqs with tDQS2DQ
            Margin     = &Outputs->MarginResult[LastTxT][Rank][Channel][Byte][0];
            *Margin    = Start;
            Margin[1]  = End;
            ChangeMargin (MrcData, param, Center, 0, 0, Channel, Rank, Byte, 0, 1, 0);
            ClkAlignParam = &IntControllerOut->IntClkAlignedMargins[Channel][Rank][Byte];
            MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqDelay, ReadFromCache, &GetSetVal);
            ClkAlignParam->TxDq = (UINT16)(GetSetVal);
          } else if (param == WrV) {
            // Write Vref
            Margin    = &Outputs->MarginResult[LastTxV][Rank][Channel][Byte][0];
            *Margin   = Start;
            Margin[1] = End;
            ByteCenter[Byte] = Center;
          } else if (param == RdV) {
            // Read Vref
            GetSetVal = Center / 2;
            for (RankRx = 0; RankRx < MAX_RANK_IN_CHANNEL; RankRx++) {
              Margin    = &Outputs->MarginResult[LastRxV][RankRx][Channel][Byte][0];
              *Margin   = Start;
              Margin[1] = End;
            }
            MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, RxVref, WriteOffsetCached, &GetSetVal);
          } else if (param == CmdV) {
            // Command Vref
            Margin      = &Outputs->MarginResult[LastCmdV][Rank][Channel][Byte][0];
            Margin[0]   = ABS ((*LargestPS) * 10);
            Margin[1]   = ABS ((*LargestPE) * 10);
          }
        } // for Byte
      }

      if ((param == WrV) && Ddr4) {
        /// Calculate Non-PDA TxV Offset - average Per byte offsets
        RankCenter = 0;
        for (Byte = 0; Byte < Outputs->SdramCount ; Byte++) {
          RankCenter += ByteCenter[Byte];
        }
        RankCenter /= Outputs->SdramCount;
        // Write using PDA only when we have a passing window.
        if (EyeTooSmall[Channel][Rank]) {
          Outputs->Ddr4PdaEnable = FALSE;
          // If no passing window - Program only Non-PDA value and Update PDA/Non-PDA cached value
          ChangeMargin (MrcData, WrV, RankCenter, 0, 0, Channel, RankMask, 0, 0, 1, 1);
        } else {
          // If passing window:
          // 1. Program Non-PDA value (without updating cached value of PDA/Non-PDA)
          ChangeMargin (MrcData, WrV, RankCenter, 0, 0, Channel, RankMask, 0, 0, 0, 1);
          // 2. Program PDA value and PDA cached value
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            ChangeMargin (MrcData, WrV, ByteCenter[Byte], 0, 0, Channel, RankMask, 1 << Byte, 0, 1, 1);
          }
          // 3. Update Non-PDA cached value
          UpdatePdaCenter (MrcData, Channel, RankMask);
        }
      }
      if ((param == WrV) && Lpddr4) {
        Center = (LargestPSCh[Channel] + LargestPECh[Channel]) / 2;
        MRC_DEBUG_MSG(
          Debug,
          DebugLevel,
          "  Channel %u Summary : \n   %d\t%d\t%d\t%d\n",
          Channel,
          LargestPSCh[Channel],
          LargestPECh[Channel],
          LargestPECh[Channel] - LargestPSCh[Channel],
          Center
          );
        ChangeMargin(MrcData, param, Center, 0, 0, Channel, 1 << Rank, 0, 0, 1, 0);
      }
    } // for Channel
    if ((param == RdV) || (param == RcvEnaX)) {
      break; // We don't use different Rx vref per rank and RcvEnX already stress on all rank.
    }
  }

  IoReset (MrcData);
  return Status;
}

/**
  Adjust sense amplifier offset per bit.
  The Algorithm:
  1.Get Rx Vref range for margining.
  2.Perform full Rx Vref range sweep and collect Error Bit mask for each Vref.
  3.Find a biggest Pass region for each bit.
  4.Calculate the Vref center for each bit and average Vref per byte.
  5.Calculate offset that will be added to original senseamp value in order to bring a Vref center of each bit as close as possible to average Vref of whole byte.
  6.Set new Senseamp offset value.

  @param[in,out] MrcData     - Include all MRC global data.

  @retval MrcStatus -  If succeeded, return mrcSuccess
**/
MrcStatus
MrcSenseAmpOffsetCorrection(
  IN OUT MrcParameters *const MrcData
)
{
  const MrcInput    *Inputs;
  const MRC_FUNCTION *MrcCall;
  MrcOutput         *Outputs;
  MrcDebug          *Debug;
  MrcIntOutput      *IntOutputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  INT16             CenterBit[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS];
  INT16             CurrentPassStart[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS];
  INT16             CurrentPassEnd[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS];
  INT16             BiggestPassStart[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS];
  INT16             BiggestPassEnd[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS];
  INT16             Cwidth;
  INT16             Bwidth;
  INT16             CenterByte[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT16             SenseOffsetBit[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS];
  INT16             RxVrefVal;
  INT16             ParamStart;
  INT16             ParamEnd;
  INT64             GetSetVal;
  UINT64            BitLaneFailures[MAX_CHANNEL][MRC_1D_ERROR_LEN];
  UINT16            Index;
  UINT8             Channel;
  UINT8             Byte;
  UINT8             bit;
  UINT8             Step;
  UINT8             SubCh;
  UINT8             chBitMask;
  UINT8             RankMask;
  UINT8             Rank;
  UINT8             ByteStart;
  UINT8             ByteEnd;
  UINT8             BitErrStatus[MAX_SDRAM_IN_DIMM];
  BOOLEAN           Lpddr4;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  MrcCall       = Inputs->Call.Func;
  ControllerOut = &Outputs->Controller[0];
  IntOutputs    = (MrcIntOutput *)(MrcData->IntOutputs.Internal);
  Lpddr4        = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  Step          = 1;
  ParamEnd      = GetMaxPossibleVrefOffset (MrcData, RdV);
  ParamStart    = -1 * ParamEnd;

  // Init arrays
  MrcCall->MrcSetMem((UINT8 *)CenterBit, sizeof(CenterBit), 0);
  MrcCall->MrcSetMem((UINT8 *)CenterByte, sizeof(CenterByte), 0);
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (bit = 0; bit < MAX_BITS; bit++) {
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        CurrentPassStart[Channel][Byte][bit] = ParamStart;
        CurrentPassEnd[Channel][Byte][bit]   = ParamStart;
        BiggestPassStart[Channel][Byte][bit] = ParamStart;
        BiggestPassEnd[Channel][Byte][bit]   = ParamStart;
      }
    }
  }
  // Get margin errors per bit
  SetupIOTestBasicVA (MrcData, Outputs->ValidChBitMask, 10, NSOE, 0, 0, 8);

  RankMask = 0xFF; // run on all available ranks for RdV param - we dont use different vref per rank
  chBitMask = Outputs->ValidChBitMask;

  for (RxVrefVal = ParamStart, Index = 0; RxVrefVal <= ParamEnd; RxVrefVal += Step, Index++) {
    // Program RdVref
    ChangeMargin (MrcData, RdV, RxVrefVal, 0, 1, 0, RankMask, 0, 0, 0, 0);
    // Clear Errors and Run Test
    RunIOTest (MrcData, chBitMask, Outputs->DQPat, 1, 0);
    IoReset (MrcData);
    // Update results for all Channel/bytes
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      BitLaneFailures[Channel][Index] = 0;
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      for (SubCh = 0; SubCh < IntOutputs->SubChEngCount; SubCh++) {
        if (MrcSubChannelExist(MrcData, Channel, SubCh)) {
          if (Outputs->EnhancedChannelMode) {
            ByteStart = ChannelOut->ByteStart[SubCh];
            ByteEnd = ChannelOut->ByteEnd[SubCh];
          } else {
            ByteStart = 0;
            ByteEnd = Outputs->SdramCount - 1;
          }
          // Read out per bit error results
          MrcGetBitGroupErrStatus(MrcData, Channel, SubCh, BitErrStatus);
          for (Byte = ByteStart; Byte <= ByteEnd; Byte++) {
            BitLaneFailures[Channel][Index] |= MrcCall->MrcLeftShift64((UINT64)BitErrStatus[Byte], 8 * Byte);
          } // byte
        } // MrcSubChannelExist
      } // for SubCh
    } // for Channel
  } // For RxVrefVal

  // Calculate RdVref to senseamp offset ratio - ~ 2/3 (senseamp offset to tick of RxV) @todo measure real ratio

  // Get margin HS, LS per bit
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist(Outputs, Channel)) {
      continue;
    }
    for (RxVrefVal = ParamStart, Index = 0; RxVrefVal <= ParamEnd; RxVrefVal += Step, Index++) {
      for (Byte = 0; Byte < MrcData->Outputs.SdramCount; Byte++) {
        for (bit = 0; bit < MAX_BITS; bit++) {
          if (MrcByteInChannelExist(MrcData, Channel, Byte)) {
            if (BitLaneFailures[Channel][Index] & MrcCall->MrcLeftShift64(1, Byte * MAX_BITS + bit)) {
              CurrentPassStart[Channel][Byte][bit] = CurrentPassEnd[Channel][Byte][bit] = RxVrefVal;
            } else {
              CurrentPassEnd[Channel][Byte][bit] = RxVrefVal;
              Cwidth = CurrentPassEnd[Channel][Byte][bit] - CurrentPassStart[Channel][Byte][bit];
              Bwidth = BiggestPassEnd[Channel][Byte][bit] - BiggestPassStart[Channel][Byte][bit];
              if (Cwidth > Bwidth) {
                BiggestPassStart[Channel][Byte][bit] = CurrentPassStart[Channel][Byte][bit];
                BiggestPassEnd[Channel][Byte][bit] = CurrentPassEnd[Channel][Byte][bit];
              }
            }
          }
        } // bit
      } // Byte
    } // RxVrefVal
  } // Channel

  // Calculate center per bit, per byte
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist(Outputs, Channel)) {
      continue;
    }
    for (Byte = 0; Byte < MrcData->Outputs.SdramCount; Byte++) {
      for (bit = 0; bit < MAX_BITS; bit++) {
        CenterBit[Channel][Byte][bit] = (BiggestPassEnd[Channel][Byte][bit] + BiggestPassStart[Channel][Byte][bit]) / 2;
        CenterByte[Channel][Byte] += CenterBit[Channel][Byte][bit];
      } // bit
      CenterByte[Channel][Byte] /= MAX_BITS; // Calculate average per byte
    } // Byte
  } // channel

  // Calculate senseamp offset to original offset
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SenseAmp offsets per bit:\n");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist(Outputs, Channel)) {
      continue;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch %d\n", Channel);
    ChannelOut = &ControllerOut->Channel[Channel];
    for (Byte = 0; Byte < MrcData->Outputs.SdramCount; Byte++) {
      for (bit = 0; bit < MAX_BITS; bit++) {
        SenseOffsetBit[Channel][Byte][bit] = (CenterBit[Channel][Byte][bit] - CenterByte[Channel][Byte]) * 2 / 3;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d ", SenseOffsetBit[Channel][Byte][bit]);
        MrcGetSetDdrIoGroupSocket0 (MrcData, Channel, 0, Byte, bit, RxVoc, ReadCached, &GetSetVal); // get original offset
        GetSetVal += SenseOffsetBit[Channel][Byte][bit]; // adjust original value
        if (Lpddr4 && (GetSetVal > 31)) {
          GetSetVal = 31;
        } else if (!Lpddr4 && (GetSetVal > 15)) { // for DDR4
          GetSetVal = 15;
        }
        if (GetSetVal < 0) {
          GetSetVal = 0;
        }
        MrcGetSetDdrIoGroupSocket0(MrcData, Channel, MAX_RANK_IN_CHANNEL, Byte, bit, RxVoc, WriteToCache, &GetSetVal); // set new offset (for all ranks)
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          ChannelOut->RxDqVrefPb[Rank][Byte][bit].Center = (UINT8)GetSetVal;
        }
      } // bit
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, ", ");
    } // Byte
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  } // channel
  MrcFlushRegisterCachedData(MrcData);

  // Clean up RxVrefOffset
  ChangeMargin (MrcData, RdV, 0, 0, 1, 0, RankMask, 0, 0, 0, 0);

  return mrcSuccess;
}

/**
  This procedure is meant to handle much more complex centering that will use a 2D algorithm to optimize asymetical
  eyes for both timing and voltage margin.

  @param[in,out] MrcData         - Include all MRC global data.
  @param[in,out] MarginResult    - Margin data from centering
  @param[in]     ChBitMaskIn     - Channel bit mask.
  @param[in]     param           - {0:RcvEn, 1:RdT, 2:WrT, 3: WrDqsT, 4:RdV, 5:WrV, 6:WrLevel,
                                    8:WrTBit, 9:RdTBit, 10:RdVBit,
                                    16:RdFan2, 17:WrFan2, 32:RdFan3, 32:WrFan3}
                                    ONLY RdT and WrT are allowed in this function
  @param[in]     EnPerBit        - Option to enable per bit margining
  @param[in]     EnRxDutyCycleIn - Phase to center.
  @param[in]     ResetPerBit     - Option to Reset PerBit Deskew to middle value before byte training
  @param[in]     LoopCount       - loop count
  @param[in]     En2D            - Option to only run center at nominal Vref point
  @param[in]     Prints          - Disable/Enable debug prints

  @retval MrcStatus -  If succeeded, return mrcSuccess
**/
MrcStatus
DataTimeCentering2D (
  IN OUT MrcParameters *const MrcData,
  IN OUT UINT32               MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     const UINT8          ChBitMaskIn,
  IN     const UINT8          Param,
  IN     const UINT8          EnPerBit,
  IN     const UINT8          EnRxDutyCycleIn,
  IN     const UINT8          ResetPerBit,
  IN     const UINT8          LoopCount,
  IN     const UINT8          En2D,
  IN     BOOLEAN              Prints
  )
{
  static const UINT32      EHWeights[]       = {6, 2, 1, 0, 2, 1, 0};
  static const UINT32      EWWeights[]       = {0, 1, 2, 3, 1, 2, 3};
  static const INT32       VrefPointsConst[] = {0, -6, -12, -18, 6, 12, 18};
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  UINT8             *RxDqPbCenter;
  UINT8             *TxDqPbCenter;
  UINT16            centerTiming;
  UINT32            *Margin;
  UINT32            *Eye;
  INT32             *CenterBit;
  INT32             *CSum;
  MrcStatus         Status;
  UINT8             ResultType;
  UINT8             Channel;
  UINT8             Rank;
  UINT8             RankMask;
  UINT16            Byte;
  UINT8             Bit;
  UINT8             ParamV;
  UINT8             ParamB;
  UINT8             MaxMargin;
  UINT8             MaxVScale;
  UINT8             EnPerBitEH;
  UINT8             Strobe;
  UINT8             Strobes;
  UINT8             Vref;
  UINT8             SaveLC;
  UINT8             LCloop;
  UINT8             i;
  UINT8             SkipWait;
  UINT8             ChBitMask;
  UINT8             EnRxDutyCycle;
  UINT8             Edge;
  UINT8             BMap[9];
  UINT8             LoopEnd;
  UINT16            Mode;
  UINT32            MarginBit[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS][MAX_EDGES];
  INT32             Center;
  UINT32            Weight;
  INT32             VrefPoints[sizeof (VrefPointsConst) / sizeof (VrefPointsConst[0])];
  UINT32            SumEH;
  UINT32            SumEW;
  UINT32            BERStats[4];
  UINT32            VrefScale[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32            EH[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32            EW[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  BOOLEAN           ByteSaturated;
  UINT32            EyeShape[7][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES]; // Store all eye edges for Per Bit
  INT32             CenterSum[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             PStrobeOffset[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32             DivBy;
  INT8              DivBySign;
  INT32             Value0;
  INT32             CenterSumBit[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS];
  INT32             Calc;
  INT64             GetSetVal;
  INT64             DqBitDelayMax;
  INT64             DqBitDelayMid;
  BOOLEAN           Ddr4;
  BOOLEAN           PdaMode;
  UINT32            PerBitRank;
  GSM_GT            PerBitGt;
  UINT8             UpdateHost;
#ifdef MRC_DEBUG_PRINT
  GSM_GT            GroupType;
  INT64             GetSetVal2;
#endif // MRC_DEBUG_PRINT
  MrcIntOutput          *IntOutputs;
  MrcIntControllerOut   *IntControllerOut;
  MrcIntClkAlignedParam *ClkAlignParam;
#ifdef BDAT_SUPPORT
  UINT32            EyeType;
  UINT32            MarginValue;
  UINT8             SystemChannel;
  UINT8             SubCh;
  UINT8             SubChMax;
  UINT8             ByteStart;
  UINT8             ByteEnd;
  BOOLEAN           EnhancedChannelMode;
#endif
  MrcDebugMsgLevel    DebugLevel;

  IntOutputs = (MrcIntOutput *)(MrcData->IntOutputs.Internal);
  IntControllerOut = &IntOutputs->Controller[0];

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  DebugLevel    = Prints ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;
  MrcCall = Inputs->Call.Func;
  // 2D Margin Types (Voltage, Time)
  // RdFan2:  Margins both RdV and RdT at { (off, -2/3*off),  (off, 2/3*off) }
  // WrFan2:  Margins both WrV and WrT at { (off, -2/3*off),  (off, 2/3*off) }
  // RdFan3:  Margins both RdV and RdT at { (off, -2/3*off),  (5/4*off, 0),  (off, 2/3*off)  }
  // WrFan3:  Margins both WrV and WrT at { (off, -2/3*off),  (5/4*off, 0),  (off, 2/3*off)  }
  if ((Param != RdT) && (Param != WrT)) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "DataTimeCentering2D: Incorrect Margin Parameter %d\n", Param);
    return mrcWrongInputParameter;
  }

  MRC_DEBUG_MSG (Debug, DebugLevel, "Parameter = %d (%sT)\n", Param, (Param == RdT) ? "Rd" : "Wr");
  ControllerOut = &Outputs->Controller[0];
  ChBitMask     = ChBitMaskIn;
  EnRxDutyCycle = EnRxDutyCycleIn;
  Status        = mrcSuccess;
  MaxVScale     = 24;
  Strobes       = 2;
  Center        = 0;
  Value0        = 0;
  Ddr4          = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  ByteSaturated = 0;
  for (i = 0; i < (sizeof (BMap) / sizeof (BMap[0])); i++) {
    BMap[i] = i;
  }
  MaxMargin = GetMaxPossibleTimingOffset (MrcData, Param);
  ResultType = GetMarginResultType (Param);

  EnPerBitEH = 1; // Repeat EH Measurement after byte training, before bit training

  // SOE = 10b ( Stop on All Byte Groups Error )
  SetupIOTestBasicVA (MrcData, ChBitMask, LoopCount - 1, NSOE, 0, 0, 8);
  Outputs->DQPat = RdRdTA;

  // Duty cycle should be ONLY for Rx
  if (Param != RdT) {
    EnRxDutyCycle = 0;
  }

  Strobes = 1 + EnRxDutyCycle;

  // Option to only run center at nominal Vref point
  if (En2D == 0) {
    MrcCall->MrcSetMem ((UINT8 *) &VrefPoints[0], sizeof (VrefPoints), 0);
  } else {
    MrcCall->MrcCopyMem ((UINT8 *) &VrefPoints[0], (UINT8 *) &VrefPointsConst[0], sizeof (VrefPoints));
  }

  // Calculate SumEH / SumEW for use in weighting equations
  SumEH = SumEW = 0;
  for (Vref = 0; Vref < sizeof (VrefPoints) / sizeof (VrefPoints[0]); Vref++) {
    SumEH += EHWeights[Vref];
    SumEW += EWWeights[Vref];

    // Loop once at nominal Vref point
    if (En2D == 0) {
      break;
    }
  }

  if (Param == RdT) {
    ParamV = RdV;
    ParamB = RdTBit;
    PerBitGt = RxDqBitDelay;
  } else {
    ParamV = WrV;
    ParamB = WrTBit;
    PerBitGt = TxDqBitDelay;
  }

  // Get Max and Middle value for TxDqBitDelay and RxDqBitDelay
  MrcGetSetLimits (MrcData, PerBitGt, NULL, &DqBitDelayMax, NULL);
  DqBitDelayMid = (((UINT8) DqBitDelayMax) + 1) / 2;
  PdaMode = Ddr4 && (ParamV == WrV);
  UpdateHost = (ParamV == RdV) ? 1 : 0;

  // Optimize timing per rank
  MRC_DEBUG_MSG (Debug, DebugLevel, "Optimization is per rank\n");
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    ChBitMask = 0;
    RankMask  = 1 << Rank;

    // Select rank for REUT test
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if ((MRC_BIT0 << Channel) & ChBitMaskIn) {
        ChBitMask |= SelectReutRanks (MrcData, Channel, (MRC_BIT0 << Rank), FALSE, 0);
      }
      // Reset PerBit Deskew to middle value before byte training
      // Write timing offset for bit[x] of the DQ byte. Linear from 0-MAX, each step size is tQCLK/64
      // Read timing offset for bit[x] of the DQ byte. Linear from 0-MAX, each step size is tQCLK/64
      if (ResetPerBit == 1) {
        MrcGetSetDdrIoGroupSocket0 (MrcData, Channel, Rank, MAX_SDRAM_IN_DIMM, MAX_BITS, PerBitGt, WriteToCache | GSM_UPDATE_HOST, &DqBitDelayMid);
      }
    }
    MrcFlushRegisterCachedData (MrcData);
    // Continue if this rank does not exist on any of the channels
    if (ChBitMask == 0) {
      continue;
    }

    //####################################################
    //######   Get EH to scale vref sample point by  #####
    //####################################################
    // Pass the host last edges by reference
    // Get EH/VrefScale for the use in timing centering
    if (En2D > 0) {
      Status = DQTimeCenterEH (
                MrcData,
                ChBitMask,
                Rank,
                ParamV,
                MaxVScale,
                BMap,
                EH,
                VrefScale,
                BERStats
                );
      if (Status != mrcSuccess) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "\nDQTimeCenterEH FAILED - Using VrefScale = %d\n", MaxVScale);
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          MrcCall->MrcSetMemDword (&VrefScale[Channel][0], Outputs->SdramCount, MaxVScale);
        }
      }
    } else {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        MrcCall->MrcSetMemDword (&EH[Channel][0], Outputs->SdramCount, 1);
        MrcCall->MrcSetMemDword (&VrefScale[Channel][0], Outputs->SdramCount, 1);
      }
    }

    Status = GetMarginByte (MrcData, MarginResult, Param, Rank, (MRC_BIT0 << Rank));

#if 0
#ifdef MRC_DEBUG_PRINT
    // Read the margins
    MRC_DEBUG_MSG (Debug, DebugLevel, "\nLstSavd Margins ");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!((1 << Channel) & ChBitMask)) {
        continue;
      }

      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MRC_DEBUG_MSG (
          Debug,
          DebugLevel,
          "%4d %4d ",
          MarginResult[ResultType][Rank][Channel][Byte][0],
          MarginResult[ResultType][Rank][Channel][Byte][1]
          );
      }
    }
#endif // MRC_DEBUG_PRINT
#endif

    MRC_DEBUG_MSG (Debug, DebugLevel, "Rank: %d", Rank);
    for (Strobe = 0; Strobe < Strobes; Strobe++) {
      MRC_DEBUG_MSG (Debug, DebugLevel, "\n\nStrobe: %d\n\nChannel\t\t0\t\t\t\t\t\t\t\t\t1\nByte\t\t", Strobe);
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          MRC_DEBUG_MSG (Debug, DebugLevel, "%d\t", Byte);
        }
      }
      //####################################################
      //######   Measure Eye Width at all Vref Points  #####
      //####################################################
      // Program Selective error checking for RX. if strobe = 0 then Check even else Check odd
      if (EnRxDutyCycle) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (ChBitMask & (MRC_BIT0 << Channel)) {
            MrcSetChunkAndClErrMsk (MrcData, Channel, 0xFF, (0x5555 << Strobe));
          }
        }
      }

      // Loop through all the Vref Points to Test
      for (Vref = 0; Vref < sizeof (VrefPoints) / sizeof (VrefPoints[0]); Vref++) {
        // Setup Vref Voltage for this point
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (ChBitMask & (MRC_BIT0 << Channel)) {
            SkipWait = (ChBitMask >> (Channel + 1)); // Skip if there are more channels

            LoopEnd = (UINT8) (((ParamV == RdV) || PdaMode) ? Outputs->SdramCount : 1);
            for (Byte = 0; Byte < LoopEnd; Byte++) {
              Value0 = (INT32) (VrefPoints[Vref] * VrefScale[Channel][Byte]) / MaxVScale;
              Status = ChangeMargin (
                        MrcData,
                        ParamV,
                        Value0,
                        0,
                        0,
                        Channel,
                        RankMask,
                        PdaMode ? (1 << Byte) : Byte,
                        0,
                        UpdateHost,
                        SkipWait
                        );
            }
          }
        }

        MRC_DEBUG_MSG (Debug, DebugLevel, "\nVref = %d:\t", Value0);

        // Run Margin Test
        Mode = 0;
        Status = MrcGetBERMarginByte (
                  MrcData,
                  MarginResult,
                  ChBitMask,
                  RankMask,
                  RankMask,
                  Param,
                  Mode,
                  BMap,
                  1,
                  MaxMargin,
                  0,
                  BERStats
                  );

        // Store Results; Setup Vref Voltage for this point
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if ((ChBitMask & (MRC_BIT0 << Channel))) {

            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              Margin = &MarginResult[ResultType][Rank][Channel][Byte][0];
              MRC_DEBUG_MSG (
                Debug,
                DebugLevel,
                "%3d %3d ",
                Margin[0],
                Margin[1]
                );

              Center = (INT32) (Margin[1] -*Margin);
              if (Vref == 0) {
                EW[Channel][Byte]         = (Margin[1] +*Margin) / 10;
                CenterSum[Channel][Byte]  = 0;
              }

              // Calculate weight for this point
              Weight = EHWeights[Vref] * EH[Channel][Byte] + EWWeights[Vref] * EW[Channel][Byte];
              CenterSum[Channel][Byte] += Weight * Center;

              // Store Edges for Per Bit deskew
              Eye = &EyeShape[Vref][Channel][Byte][0];
              for (Edge = 0; Edge < MAX_EDGES; Edge++) {
                Eye[Edge] = Margin[Edge];
              }

              // RunTime Improvement.  Set margin back to Vref = 0 point when the sign  of the VrefPoint changes
              if ((VrefPoints[Vref] < 0) &&
                  (Vref < (sizeof (VrefPoints) / sizeof (VrefPoints[0]) - 1)) &&
                  (VrefPoints[Vref + 1] > 0)
                  ) {
                Eye = &EyeShape[0][Channel][Byte][0];
                for (Edge = 0; Edge < MAX_EDGES; Edge++) {
                  Margin[Edge] = Eye[Edge];
                }
              }
            }
          }
        }

        // Loop once at nominal Vref point
        if (En2D == 0) {
          Vref = sizeof (VrefPoints) / sizeof (VrefPoints[0]);
        }
      }

      //####################################################
      //############    Center Results per Byte  ###########
      //####################################################
      MRC_DEBUG_MSG (Debug, DebugLevel, "\n\nWeighted Center\t");

      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (ChBitMask & (MRC_BIT0 << Channel)) {
          ChannelOut = &ControllerOut->Channel[Channel];

          // Calculate and apply CenterPoint.  Round to Nearest Int
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            DivBy = (SumEH * EH[Channel][Byte] + SumEW * EW[Channel][Byte]);
            if (DivBy == 0) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "DataTimeCentering2D: Divide by zero\n");
              return mrcFail;
            }

            CSum      = &CenterSum[Channel][Byte];
            DivBySign = (*CSum < 0) ? (-1) : 1;

            *CSum     = (*CSum + 10 * (DivBySign * DivBy)) / (20 * DivBy);
            MRC_DEBUG_MSG (Debug, DebugLevel, "%d\t", *CSum);

            // Apply new centerpoint
            GetSetVal = *CSum;
            if (Param == RdT) {
              if (Strobe == 0) {
                PStrobeOffset[Channel][Byte] = *CSum;
              }
              // If EnRxDutyCycle is 0, we will store the data in the array above and go into this if-case.
              if ((!EnRxDutyCycle) || (Strobe == 1)) {
                MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RxDqsNDelay, WriteOffsetToCache, &GetSetVal);
                GetSetVal = PStrobeOffset[Channel][Byte];
                MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RxDqsPDelay, WriteOffsetToCache, &GetSetVal);
                MrcFlushRegisterCachedData(MrcData);
              }
            } else {
              MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqDelay, WriteOffsetCached, &GetSetVal);
              ClkAlignParam = &IntControllerOut->IntClkAlignedMargins[Channel][Rank][Byte];
              MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqDelay, ReadFromCache, &GetSetVal);
              ClkAlignParam->TxDq = (UINT16)(GetSetVal);
            }

            // Update the Eye Edges
            for (Vref = 0; Vref < sizeof (VrefPoints) / sizeof (VrefPoints[0]); Vref++) {
              Calc  = 10 **CSum;
              Eye   = &EyeShape[Vref][Channel][Byte][0];
              *Eye += Calc;
              Eye[1] -= Calc;

              // Loop once at nominal Vref point
              if (En2D == 0) {
                Vref = sizeof (VrefPoints) / sizeof (VrefPoints[0]);
              }
            }

            // Update MrcData for future tests (MarginResult points back to MrcData)
            // EyeShape for Vref 0 is assumed to have the best shape for future tests.
            for (Edge = 0; Edge < MAX_EDGES; Edge++) {
              MarginResult[ResultType][Rank][Channel][Byte][Edge] = EyeShape[0][Channel][Byte][Edge];
            }
          } // Byte
        }
      } // Channel

      centerTiming = 0;
#ifdef MRC_DEBUG_PRINT
      MRC_DEBUG_MSG (Debug, DebugLevel, "\nFinal Center\t");
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (ChBitMask & (MRC_BIT0 << Channel)) {
          ChannelOut = &ControllerOut->Channel[Channel];

          // Calculate final center point relative to "zero" as in the 1D case
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            if (Param == RdT) {
              if ((!EnRxDutyCycle) || (Strobe == 1)) {
                GroupType = RxDqsNDelay;
              } else {
                GroupType = RxDqsPDelay;
              }
              MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, GroupType, ReadFromCache, &GetSetVal);
              centerTiming = (UINT8) (GetSetVal - 32);
            } else {
              MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqDelay, ReadFromCache, &GetSetVal);
              MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqsDelay, ReadFromCache, &GetSetVal2);
              centerTiming = (UINT16) (GetSetVal - (GetSetVal2 + 32));
            }

            MRC_DEBUG_MSG (Debug, DebugLevel, "%d\t", (INT8) centerTiming);
          }
        }
      }
#endif // MRC_DEBUG_PRINT
    } // End of Byte Centering

    //######################################################
    //############     Measure Eye Width Per BIT  ##########
    //######################################################

    if (EnPerBit) {
#if 0
#ifdef MRC_DEBUG_PRINT
      MRC_DEBUG_MSG (Debug, DebugLevel, "\n\nEdges we pass on to GetMarginBit are\n");
      for (Vref = 0; Vref < sizeof (VrefPoints) / sizeof (VrefPoints[0]); Vref++) {
        MRC_DEBUG_MSG (Debug, DebugLevel, "\t\t");

        // Setup Vref Voltage for this point
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (ChBitMask & (MRC_BIT0 << Channel)) {
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              for (Edge = 0; Edge < MAX_EDGES; Edge++) {
                MRC_DEBUG_MSG (Debug, DebugLevel, "%d ", EyeShape[Vref][Channel][Byte][Edge]);
              }
            }
          }
        }

        MRC_DEBUG_MSG (Debug, DebugLevel, "\n");
        if (En2D == 0) {
          Vref = sizeof (VrefPoints) / sizeof (VrefPoints[0]);
        }
      }
#endif // MRC_DEBUG_PRINT
#endif

      MRC_DEBUG_MSG (Debug, DebugLevel, "\n\n### Measure Eye Width Per BIT\n");

      // Recalculate the EH after the Byte Centering
      if (EnPerBitEH && (En2D > 0)) {
        Status = DQTimeCenterEH (
                  MrcData,
                  ChBitMask,
                  Rank,
                  ParamV,
                  MaxVScale,
                  BMap,
                  EH,
                  VrefScale,
                  BERStats
                  );
        if (Status != mrcSuccess) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "\nDQTimeCenterEH FAILED - Using VrefScale = %d\n", MaxVScale);
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            MrcCall->MrcSetMemDword (&VrefScale[Channel][0], Outputs->SdramCount, MaxVScale);
          }
        }
      }

      // No stop on error or selective error checking
      // Stop on all lane fail
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (ChBitMask & (MRC_BIT0 << Channel)) {
#ifdef MRC_DEBUG_PRINT
          MRC_DEBUG_MSG (Debug, DebugLevel, "Channel      %d", Channel);
          if (Channel == 0) {
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              MRC_DEBUG_MSG (Debug, DebugLevel, "\t\t\t\t\t\t");
            }
          }
#endif // MRC_DEBUG_PRINT
          MrcSetChunkAndClErrMsk (MrcData, Channel, 0xFF, 0xFFFF);
          MrcSetupTestErrCtl (MrcData, Channel, ALSOE, 1);
        }
      }

#ifdef MRC_DEBUG_PRINT
      MRC_DEBUG_MSG (Debug, DebugLevel, "\n");
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (ChBitMask & (MRC_BIT0 << Channel)) {
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            MRC_DEBUG_MSG (Debug, DebugLevel, "             Byte % 24d ", Byte);
          }
        }
      }

      MRC_DEBUG_MSG (Debug, DebugLevel, "\n");
#endif // MRC_DEBUG_PRINT

      // Loop through all the Vref Points to Test
      SaveLC = Outputs->DQPatLC;
      for (Vref = 0; Vref < sizeof (VrefPoints) / sizeof (VrefPoints[0]); Vref++) {
        // Setup Vref Voltage for this point
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if ((ChBitMask & (MRC_BIT0 << Channel))) {

            SkipWait = (ChBitMask >> (Channel + 1)); // Skip if there are more channels

            // Change Vref margin
            LoopEnd = (UINT8) (((ParamV == RdV) || PdaMode) ? Outputs->SdramCount : 1);
            for (Byte = 0; Byte < LoopEnd; Byte++) {
              Value0 = (INT32) (VrefPoints[Vref] * VrefScale[Channel][Byte]) / MaxVScale;
              Status = ChangeMargin (
                        MrcData,
                        ParamV,
                        Value0,
                        0,
                        0,
                        Channel,
                        RankMask,
                        PdaMode ? (1 << Byte) : Byte,
                        0,
                        UpdateHost,
                        SkipWait
                        );
            }
          }

          MRC_DEBUG_MSG (Debug, DebugLevel, "Channel %d Vref = %d\t", Channel, Value0);
          MrcCall->MrcSetMemDword (&MarginBit[Channel][0][0][0], MAX_SDRAM_IN_DIMM * MAX_BITS * MAX_EDGES, (UINT8) DqBitDelayMid);
        }

        // Run Margin Test; Loop through 2 times. Once at low loop count and Once at high loopcount. Improves runtime
        // @todo: Need loop count of 2 when not using BASICVA
        for (LCloop = 0; LCloop < 1; LCloop++) {
          Outputs->DQPatLC  = (LCloop == 0) ? 1 : SaveLC;

          Mode = 0;
          Status = MrcGetMarginBit (MrcData, ChBitMask, Rank, MarginBit, EyeShape[Vref], ParamB, Mode, (UINT8) DqBitDelayMax, MRC_PRINTS_ON);
        }

        // MRC_DEBUG_MSG (Debug, DebugLevel, "\nCSum      ");
        // Store Results
        // Setup Vref Voltage for this point
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (ChBitMask & (MRC_BIT0 << Channel)) {

            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              // Calculate weight for this point
              Weight = EHWeights[Vref] * EH[Channel][Byte] + EWWeights[Vref] * EW[Channel][Byte];
              ByteSaturated = 1;
              for (Bit = 0; Bit < MAX_BITS; Bit++) {
                Margin  = &MarginBit[Channel][Byte][Bit][0];
                CSum    = &CenterSumBit[Channel][Byte][Bit];

                Center = ((Margin[1] - (INT32) DqBitDelayMid) - ((INT32) DqBitDelayMid - *Margin));
                if (Vref == 0) {
                  *CSum = 0;
                }

                *CSum += Weight * Center;
                ByteSaturated &= ((*Margin == 0x10) || (Margin[1] == 0x10) || (*Margin == 0) || (Margin[1] == 0));
                //MRC_DEBUG_MSG (Debug, DebugLevel, "Byte %u Saturated %u Bit %u Margin %u %u  \n", Byte, ByteSaturated, Bit, *Margin, Margin[1]);
              }
              if (Param == RdT) {
                IntControllerOut->MrcRxPbdSaturated[Channel][Rank][Byte] = ByteSaturated;
                //MRC_DEBUG_MSG (Debug, DebugLevel, "RdT ByteSaturated %u  \n", ByteSaturated);
              } else { // WrT
                IntControllerOut->MrcTxPbdSaturated[Channel][Rank][Byte] = ByteSaturated;
                //MRC_DEBUG_MSG (Debug, DebugLevel, "WrT ByteSaturated %u  \n", ByteSaturated);
              }

            }
          }
        }

        // Loop once at nominal Vref point
        if (En2D == 0) {
          Vref = sizeof (VrefPoints) / sizeof (VrefPoints[0]);
        }
      }

      //######################################################
      //#############     Center Result Per BIT  #############
      //######################################################
      MRC_DEBUG_MSG (Debug, DebugLevel, "\nWtd Ctr");
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (ChBitMask & (MRC_BIT0 << Channel)) {
          MRC_DEBUG_MSG (Debug, DebugLevel, "\nChannel %d", Channel);
          ChannelOut = &ControllerOut->Channel[Channel];

          // Cleanup after test.  Go back to the per byte setup: NSOE and all comparisons on Chunk and Cacheline
          MrcSetChunkAndClErrMsk (MrcData, Channel, 0xFF, 0xFFFF);
          MrcSetupTestErrCtl (MrcData, Channel, NSOE, 1);

          // Calculate and apply CenterPoint.  Round to Nearest Int
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            MRC_DEBUG_MSG (Debug, DebugLevel, "\nByte %d\t", Byte);
            DivBy = (SumEH * EH[Channel][Byte] + SumEW * EW[Channel][Byte]);

            // Make sure DivBy is never 0
            if (DivBy == 0) {
              DivBy = 1;
            }

            PerBitRank = 0;
            for (Bit = 0; Bit < MAX_BITS; Bit++) {
              CenterBit    = &CenterSumBit[Channel][Byte][Bit];
              RxDqPbCenter = &ChannelOut->RxDqPb[Rank][Byte][Bit].Center;
              TxDqPbCenter = &ChannelOut->TxDqPb[Rank][Byte][Bit].Center;

              DivBySign  = (*CenterBit < 0) ? (-1) : 1;
              *CenterBit = (*CenterBit + (DivBySign * DivBy)) / (2 * DivBy);

              // Centerpoint needs to be added to starting DqPb value
              *CenterBit += (Param == RdT) ? (INT32) *RxDqPbCenter : (INT32) *TxDqPbCenter;

              // Check for saturation
              if (*CenterBit > DDRDATA0CH0_CR_RXCONTROL1RANK0_Lane0PerBitDeskew_MAX) {
                *CenterBit = DDRDATA0CH0_CR_RXCONTROL1RANK0_Lane0PerBitDeskew_MAX;
              } else if (*CenterBit < 0) {
                *CenterBit = 0;
              }

              MRC_DEBUG_MSG (Debug, DebugLevel, "%8X ", *CenterBit);

              PerBitRank = *CenterBit;
              // Apply new centerpoint
              // ParamB already has the proper per bit parameter based on Param
              GetSetVal = (UINT32) PerBitRank;
              MrcGetSetDdrIoGroupSocket0 (MrcData, Channel, Rank, Byte, Bit, PerBitGt, WriteToCache | GSM_UPDATE_HOST, &GetSetVal);
            } // bit
          } // Byte
        } // Valid Channel
      } // Channel
      MrcFlushRegisterCachedData (MrcData);
      // Stop on all lane fail
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (ChBitMask & (MRC_BIT0 << Channel)) {
          MrcSetChunkAndClErrMsk (MrcData, Channel, 0xFF, 0xFFFF);
          MrcSetupTestErrCtl (MrcData, Channel, ALSOE, 1);
        }
      }

#if 0  // This code is for debug purposes ONLY if we want to know the perbyte margins after calling the perbit centering
#ifdef MRC_DEBUG_PRINT

      MRC_DEBUG_MSG (Debug, DebugLevel, "\n\nEdges\t");
      for (Vref = 0; Vref < (sizeof (VrefPoints) / sizeof (VrefPoints[0])); Vref++) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (ChBitMask & (MRC_BIT0 << Channel)) {
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              for (Edge = 0; Edge < MAX_EDGES; Edge++) {
                MRC_DEBUG_MSG (Debug, DebugLevel, "%d ", EyeShape[Vref][Channel][Byte][Edge]);
              }
            }
          }
        }

        MRC_DEBUG_MSG (Debug, DebugLevel, "\n");
        if (En2D == 0) {
          Vref = sizeof (VrefPoints) / sizeof (VrefPoints[0]);
        }
      }

      MRC_DEBUG_MSG (Debug, DebugLevel, "\nCalling GetMarginBit with per Byte Timing\nByte\n");
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (ChBitMask & (1 << Channel)) {
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            MRC_DEBUG_MSG (Debug, DebugLevel, "%d\t\t\t\t\t", Byte);
          }
        }
      }

      for (Vref = 0; Vref < (sizeof (VrefPoints) / sizeof (VrefPoints[0])); Vref++) {
        Mode    = 0;
        Status  = MrcGetMarginBit (MrcData, ChBitMask, Rank, MarginBit, EyeShape[Vref], Param, Mode, (UINT8) DqBitDelayMax, MRC_PRINTS_ON );

        // Loop once at nominal Vref point
        if (En2D == 0) {
          Vref = sizeof (VrefPoints) / sizeof (VrefPoints[0]);
        }
      }

      MRC_DEBUG_MSG (Debug, DebugLevel, "\nPerByte Margins after Bit Centering\nLeft\tRight\tCenter\n");
      for (Vref = 0; Vref < (sizeof (VrefPoints) / sizeof (VrefPoints[0])); Vref++) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (ChBitMask & (MRC_BIT0 << Channel)) {
            MRC_DEBUG_MSG (Debug, DebugLevel, "Channel %d\n", Channel);
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              MRC_DEBUG_MSG (
                Debug,
                DebugLevel,
                "%d\t%d\t%d\n",
                EyeShape[Vref][Channel][Byte][0],
                EyeShape[Vref][Channel][Byte][1],
                (((INT32) EyeShape[Vref][Channel][Byte][1] - (INT32) EyeShape[Vref][Channel][Byte][0]) / (2 * 10))
                );
            }
          }
        }

        MRC_DEBUG_MSG (Debug, DebugLevel, "\n");
        if (En2D == 0) {
          Vref = sizeof (VrefPoints) / sizeof (VrefPoints[0]);
        }
      }
#endif // MRC_DEBUG_PRINT
#endif

      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (ChBitMask & (MRC_BIT0 << Channel)) {
          // Cleanup after test
          MrcSetChunkAndClErrMsk (MrcData, Channel, 0xFF, 0xFFFF);
          MrcSetupTestErrCtl (MrcData, Channel, NSOE, 1);
        }
      }
    } // if (EnPerBit)

#ifdef BDAT_SUPPORT
    if (Inputs->BdatEnable && (Inputs->BdatTestType == Margin2DType)) {
      if ((Param == RdT) || (Param == WrT)) {
        Outputs->NumCL = 128;
        EyeType = (Param == RdT) ? 0 : 1;
        EnhancedChannelMode = Outputs->EnhancedChannelMode;
        SubChMax = (EnhancedChannelMode) ? MAX_SUB_CHANNEL : 1;
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!(ChBitMask & (MRC_BIT0 << Channel))) {
            continue;
          }
          ChannelOut = &ControllerOut->Channel[Channel];
          for (SubCh = 0; SubCh < SubChMax; SubCh++) {
            SystemChannel = (Outputs->EnhancedChannelMode) ? (MAX_CHANNEL * Channel) + SubCh : Channel;
            ByteStart = EnhancedChannelMode ? ChannelOut->ByteStart[SubCh] : 0;
            ByteEnd = EnhancedChannelMode ? ChannelOut->ByteEnd[SubCh] : Outputs->SdramCount - 1;
            for (Vref = 0; Vref < sizeof (VrefPoints) / sizeof (VrefPoints[0]); Vref++) {
              for (Edge = 0; Edge < MAX_EDGES; Edge++) {
                MarginValue = MRC_UINT32_MAX;
                for (Byte = ByteStart; Byte <= ByteEnd; Byte++) {
                  MarginValue = MIN (MarginValue, (UINT8) EyeShape[Vref][Channel][Byte][Edge]);
                }
                Outputs->Margin2DResult[EyeType][Rank][SystemChannel][Vref][Edge] = (UINT8) (MarginValue / 10);
              }
            }
          }
        }
      }
    }
#endif

    MRC_DEBUG_MSG (Debug, DebugLevel, "\n");
  } //End of Rank

  // Clean Up after test
  Byte = PdaMode ? 0x1FF : 0;
  Status            = ChangeMargin (MrcData, ParamV, 0, 0, 1, 0, 0, Byte, 0, UpdateHost, 0);
  return Status;
}

/**
  This procedure is meant to find the calibrated step size for Per Bit DeSkew
  @param[in,out] MrcData         - Include all MRC global data.
  @param[in,out] MarginResult    - Margin data from centering
  @param[in]     ChBitMaskIn     - Channel bit mask.
  @param[in]     param           - {0:RcvEn, 1:RdT, 2:WrT, 3: WrDqsT, 4:RdV, 5:WrV, 6:WrLevel,
                                    8:WrTBit, 9:RdTBit, 10:RdVBit,
                                    16:RdFan2, 17:WrFan2, 32:RdFan3, 32:WrFan3}
                                    ONLY RdT is allowed in this function
  @param[in]     LoopCount       - loop count

  @retval MrcStatus -  If succeeded, return mrcSuccess
**/
MrcStatus
GetPerBitDeSkewStep (
  IN OUT MrcParameters *const MrcData,
  IN OUT UINT32               MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     const UINT8          ChBitMaskIn,
  IN     const UINT8          Param,
  IN     const UINT8          LoopCount
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput         *Outputs;
  MrcStatus         Status;
  UINT8             ResultType;
  UINT8             Channel;
  UINT8             i;
  UINT8             ChBitMask;
  UINT8             Rank;
  UINT8             RankMask;
  UINT8             BMap[9];
  UINT16            Byte;
  UINT8             MarginResMed[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT8             MarginDiff[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT8             RxDeskewCal[MAX_CHANNEL];
  UINT32            AverPiDiff[MAX_CHANNEL];
  UINT8             LeftMargin;
  UINT8             RightMargin;
  UINT32            BERStats[4];
  INT64             CalStep;
  UINT8             ScaleCalculated[MAX_CHANNEL];
  BOOLEAN           CalDone;
  UINT8             MarginLoop;
  UINT32            PiTickPs;
  UINT32            PerPartConstant;
  UINT8             DeskewChBitDone;
  INT64             GetSetVal;
  UINT8             RxDeskewCalMax;
  UINT8             MidValPBD;
  UINT8             MaxValPBD;
  UINT8             MaxMargin;
  BOOLEAN           ForceAllSteps;

  Inputs = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug = &Outputs->Debug;
  MrcCall = Inputs->Call.Func;
  ResultType = GetMarginResultType(Param);
  ChBitMask = ChBitMaskIn;
  Status = mrcSuccess;
  MrcCall->MrcSetMem((UINT8 *)BERStats, sizeof(BERStats), 0);
  for (i = 0; i < (sizeof(BMap) / sizeof(BMap[0])); i++) {
    BMap[i] = i;
  }
  for (i = 0; i < MAX_CHANNEL; i++) {
    RxDeskewCal[i] = 0xFF;
  }
  ForceAllSteps = FALSE;

  if (Param != RdT) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "GetPerBitDeSkewStep: Incorrect Margin Parameter %d\n", Param);
    return mrcWrongInputParameter;
  }
  MaxMargin = GetMaxPossibleTimingOffset (MrcData, Param);

  // PerPartConstant = Round ((MaxValPBD /(MaxValPBD - MidRangePBD)) *PiTick_PSEC)
  MrcGetSetLimits (MrcData, RxDqBitDelay, NULL, &GetSetVal, NULL);
  MaxValPBD = (UINT8) GetSetVal;
  MidValPBD = (MaxValPBD + 1) / 2;
  PiTickPs = UDIVIDEROUND (Outputs->UIps, 64);
  PerPartConstant = UDIVIDEROUND ((MaxValPBD * PiTickPs), (MaxValPBD - MidValPBD));
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "PiTickPs = %d\n\n", PiTickPs);

  SetupIOTestBasicVA (MrcData, ChBitMask, LoopCount, NSOE, 0, 0, 8);

  // Max Step size for Per Bit Deskew calibration.
  MrcGetSetLimits (MrcData, GsmIocRxDeskewCal, NULL, &GetSetVal, NULL);
  RxDeskewCalMax = (UINT8) GetSetVal;
  DeskewChBitDone = 0;

  //Find rx-deskew-cal value per part for the 1st populated rank
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    ChBitMask = 0;
    RankMask  = 1 << Rank;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      // If we have "cal" value for this channel then skip
      if ((ForceAllSteps == FALSE) && (RxDeskewCal[Channel] != 0xFF)) {
        continue;
      }
      if ((MRC_BIT0 << Channel) & ChBitMaskIn) {
        ChBitMask |= SelectReutRanks (MrcData, Channel, (MRC_BIT0 << Rank), FALSE, 0);
      }
    }
    // Continue if this rank does not exist on any of the channels
    if (ChBitMask == 0) {
      continue;
    }

    CalStep = 0;
    CalDone = FALSE;
    // Find rxdeskew cal value for this rank
    while ((CalDone == FALSE) && (CalStep <= RxDeskewCalMax)) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!((1 << Channel) & ChBitMask)) {
          continue;
        }
        // Set RX/TX Deskew cal for this channel
        // If we have "cal" value for this channel then skip
        if ((ForceAllSteps == FALSE) && (RxDeskewCal[Channel] != 0xFF)) {
          continue;
        }
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, MAX_SDRAM_IN_DIMM, GsmIocRxDeskewCal, WriteToCache, &CalStep);
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, MAX_SDRAM_IN_DIMM, GsmIocTxDeskewCal, WriteToCache, &CalStep);
      } // Channel

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Calibration Point %d\nRank %d\n", CalStep, Rank);
      // Run MrcGetBERMarginByte for MidRangePBD and MaxValPBD
      for (MarginLoop = 0; MarginLoop < 2; MarginLoop++) {
        // MarginLoop == 0 indicates MidValPBD (32) and MarginLoop == 1 indicates MaxValPBD (63) in the following code.
        GetSetVal = (MarginLoop == 0) ? MidValPBD : MaxValPBD;
        MrcGetSetDdrIoGroupSocket0 (MrcData, MAX_CHANNEL, Rank, MAX_SDRAM_IN_DIMM, MAX_BITS, RxDqBitDelay,  WriteToCache, &GetSetVal);
        MrcFlushRegisterCachedData (MrcData);

        // Run Margin Test
        Status = MrcGetBERMarginByte (
          MrcData,
          MarginResult,
          ChBitMask,
          RankMask,
          RankMask,
          Param,
          0,
          BMap,
          1,
          MaxMargin,
          0,
          BERStats
          );

        // Read the margins and store per byte Left edge results for both ResMid and ResMax
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n%s = 0x%X\n", (MarginLoop == 0) ? "MidRangePBD" : "MaxValPBD ", (UINT32) GetSetVal);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tByte\t0\t1\t2\t3\t4\t5\t6\t7\t8\n");
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!((1 << Channel) & ChBitMask)) {
            continue;
          }
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d:\t", Channel);
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            LeftMargin = (UINT8) (MarginResult[ResultType][Rank][Channel][Byte][0] / 10);
            RightMargin = (UINT8) (MarginResult[ResultType][Rank][Channel][Byte][1] / 10);
            if (MarginLoop == 0) {
              // save Left Margins for both MidPBD and MaxPBD
              MarginResMed[Channel][Byte] = LeftMargin;
            } else {
              // Store Margin calculated between left edges from Mid and Max margins
              MarginDiff[Channel][Byte] = ABS ((MarginResMed[Channel][Byte]) - LeftMargin);
            }
            MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "%2d-%2d\t", LeftMargin, RightMargin);
          } // byte loop
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
        } // /Channel
      } // Margin Loop
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

      // Calculate the target PI diff for the applied PBD range.
      // The goal is to reach at least 100psec full PBD range w / minimal scale factor to retain small enough step size.
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Margin Difference: MarginResMed[Left]-MarginResMax[Left])\n");
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tByte\t 0  1  2  3  4  5  6  7  8\n");
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        AverPiDiff[Channel] = 0;
        if (!((1 << Channel) & ChBitMask)) {
          continue;
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d:\t", Channel);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%2d ", MarginDiff[Channel][Byte]);
          AverPiDiff[Channel] += MarginDiff[Channel][Byte];
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n", Channel);
        // Average of Margin difference
        AverPiDiff[Channel] = UDIVIDEROUND (AverPiDiff[Channel], (Outputs->SdramCount));

        // FullRangePsec = AverPiDiff * PerPartConstant. Scale = Floor(100/FullRangeSpec)
        if (AverPiDiff[Channel] != 0) {
          ScaleCalculated[Channel] = (UINT8) DIVIDEFLOOR (100, (PerPartConstant * AverPiDiff[Channel]));
        } else {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nERROR: Channel %d:Average Pi Difference cannot be zero\n", Channel);
          ScaleCalculated[Channel] = 1;
        }

        // Check if we reached the 100psec target
        if ((ScaleCalculated[Channel] == 0) || (CalStep == RxDeskewCalMax)) {
          if (RxDeskewCal[Channel] == 0xFF) {
            RxDeskewCal[Channel] = (UINT8) CalStep;
            DeskewChBitDone |= 1 << Channel;
          }
        }
      } // Channel loop
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
      CalStep++;

#ifdef MRC_DEBUG_PRINT
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!((1 << Channel) & ChBitMask)) {
          continue;
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d\nAveragePiDiff in ticks = %d\nFullRangeSpecPsec = %d\nScale for 100ps => %d\n\n",
                       Channel,
                       AverPiDiff[Channel],
                       PerPartConstant * AverPiDiff[Channel],
                       ScaleCalculated[Channel]
                       );
      }
#endif // MRC_DEBUG_PRINT

      if (DeskewChBitDone == ChBitMask) {
        if (ForceAllSteps == FALSE) {
          // Got 100psec target.
          CalDone = TRUE;
        }
      }
    } // while
  } //rank loop

  // Program the final RxDeskewCal and TxDeskewCal value
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    GetSetVal = RxDeskewCal[Channel];
    if (GetSetVal <= RxDeskewCalMax) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %d Final RX/TX deskew cal = %d\n", Channel, GetSetVal);
      MrcGetSetDdrIoGroupSocket0 (MrcData, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, MAX_BITS, GsmIocRxDeskewCal, WriteToCache, &GetSetVal);
      MrcGetSetDdrIoGroupSocket0 (MrcData, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, MAX_BITS, GsmIocTxDeskewCal, WriteToCache, &GetSetVal);
    }
  }

  // Set PBD back to MidRangePBD
  GetSetVal = MidValPBD;
  MrcGetSetDdrIoGroupSocket0 (MrcData, MAX_CHANNEL, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, MAX_BITS, RxDqBitDelay, WriteToCache, &GetSetVal);
  MrcFlushRegisterCachedData (MrcData);

  return Status;
}

/**
  Subfunction of 2D Timing Centering
  Measures paramV margin across ch/bytes and updates the EH/VrefScale variables

  @param[in]     MrcData   - Include all MRC global data.
  @param[in]     ChBitMask - Channel Bit mak for which test should be setup for.
  @param[in]     rank      - Defines rank to used for MrcData
  @param[in]     ParamV    - Margin parameter
  @param[in]     MaxVScale - Maximum Voltage Scale to use
  @param[in]     BMap      - Byte mapping to configure error counter control register
  @param[in,out] EH        - Structure that stores start, stop and increment details for address
  @param[in,out] VrefScale - Parameter to be updated
  @param[in,out] BERStats  - Bit Error Rate Statistics.

  @retval mrcSuccess if successful, otherwise the function returns an error status.
**/
MrcStatus
DQTimeCenterEH (
  IN     MrcParameters * const MrcData,
  IN     const UINT8           ChBitMask,
  IN     const UINT8           rank,
  IN     const UINT8           ParamV,
  IN     const UINT8           MaxVScale,
  IN     UINT8 * const         BMap,
  IN OUT UINT32                EH[MAX_CHANNEL][MAX_SDRAM_IN_DIMM],
  IN OUT UINT32                VrefScale[MAX_CHANNEL][MAX_SDRAM_IN_DIMM],
  IN OUT UINT32 * const        BERStats
  )
{
  const MRC_FUNCTION *MrcCall;
  const MrcInput  *Inputs;
  MrcOutput       *Outputs;
  UINT32          *MarginResult;
  UINT32          *VrefS;
  MrcStatus       Status;
  UINT8           ResultType;
  UINT8           Channel;
  UINT8           RankMask;
  UINT8           Byte;
  UINT32          MinVrefScale;
  UINT16          Mode;
  UINT8           MaxVref;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Outputs = &MrcData->Outputs;
  MaxVref = GetMaxPossibleVrefOffset (MrcData, ParamV);
  RankMask = 1 << rank;

  Mode    = 0;
  Status  = GetMarginByte (MrcData, Outputs->MarginResult, ParamV, rank, (MRC_BIT0 << rank));
  if (mrcSuccess == Status) {
    Status = MrcGetBERMarginByte (
              MrcData,
              Outputs->MarginResult,
              ChBitMask,
              RankMask,
              RankMask,
              ParamV,
              Mode,
              BMap,
              1,
              MaxVref,
              0,
              BERStats
              );
    if (mrcSuccess == Status) {
      Status = ScaleMarginByte (MrcData, Outputs->MarginResult, ParamV, rank);
      if (mrcSuccess == Status) {
        ResultType = GetMarginResultType (ParamV);

        // Update VrefScale with results
        for (Channel = 0; (Channel < MAX_CHANNEL) && (mrcSuccess == Status); Channel++) {
          if (ChBitMask & (MRC_BIT0 << Channel)) {
            // Calculate EH and VrefScale
            MinVrefScale = MaxVScale;
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              MarginResult      = &Outputs->MarginResult[ResultType][rank][Channel][Byte][0];
              VrefS             = &VrefScale[Channel][Byte];
              EH[Channel][Byte] = (*MarginResult + *(MarginResult + 1)) / 10;
              *VrefS            = EH[Channel][Byte] / 2;

              if (*VrefS > MaxVScale) {
                *VrefS = MaxVScale;
              }

              if (MinVrefScale > *VrefS) {
                MinVrefScale = *VrefS;
              }
              // Scale host back to correct values
              Status = ScaleMarginByte (MrcData, Outputs->MarginResult, ParamV, rank);
              if (mrcSuccess != Status) {
                break;
              }
              // For Tx, use the same Vref limit for all bytes. Store result in byte0
              if (ParamV == WrV) {
                MrcCall->MrcSetMemDword (&VrefScale[Channel][0], Outputs->SdramCount, MinVrefScale);
              }
            }
          }
        }
      }
    }
  }
  // Updates EH and VrefScale
  return Status;
}

/**
  This step prints out the key training parameters that are margined by Rank Margin Tool.
  This will allow tracking of current training settings across multiple steps

  @retval Nothing
**/
void
MrcTrainedStateTrace (
  IN  MrcParameters *const  MrcData
  )
{
  const GSM_GT  ByteBasedParams[]    = {RecEnDelay, RxDqsPDelay, RxDqsNDelay, TxDqsDelay, TxDqDelay};
  const GSM_GT  CmdParams[]          = { CmdGrpPi,        CtlGrpPi,            ClkGrpPi            };
  const UINT8   CmdParamGrpMaxDt[]   = { MRC_CMD_GRP_MAX, MRC_CTL_GRP_MAX,     MRC_CLK_GRP_MAX     };
  const UINT8   CmdParamGrpMaxMobl[] = { MRC_CMD_GRP_MAX, MRC_U_Y_CCC_GRP_MAX, MRC_U_Y_CCC_GRP_MAX };
  UINT8 const *CmdParamGrpMax;
  MrcOutput *Outputs;
  INT64     GetSetDummy;
  UINT32    ParamIdx;
  UINT32    Index;
  UINT32    Channel;
  UINT32    Rank;
  UINT32    Byte;

  CmdParamGrpMax = (MrcData->Inputs.CpuidModel == cmICL_DT_HALO_R) ? CmdParamGrpMaxDt : CmdParamGrpMaxMobl;
  GetSetDummy = 0;
  Outputs = &MrcData->Outputs;

  for (ParamIdx = 0; ParamIdx < (sizeof (ByteBasedParams) / sizeof (ByteBasedParams[1])); ParamIdx++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          continue;
        }
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
            continue;
          }
          MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, ByteBasedParams[ParamIdx], ReadFromCache | PrintValue, &GetSetDummy);
        }
      }
    }
  }

  for (ParamIdx = 0; ParamIdx < (sizeof (CmdParams) / sizeof (CmdParams[1])); ParamIdx++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      for (Index = 0; Index < CmdParamGrpMax[ParamIdx]; Index++) {
        MrcGetSetDdrIoCmdGroup (MrcData, Channel, Index, CmdParams[ParamIdx], ReadFromCache | PrintValue, &GetSetDummy);
      }
    }
  }

  //@todo: Add Command Vref, DIMM Mode Register Parameters
}

/**
  Update the CA/DQ Vref value

  @param[in,out] MrcData             - Include all MRC global data.
  @param[in]     ChannelMask         - Select the Channels to update Vref for.
  @param[in]     RankMask            - Selecting which Rank to talk to (DDR4: WrV and CmdV, LPDDR4: WrV and CmdV)
  @param[in]     DeviceMask          - Selecting which Devices to talk to (only valid for DDR4 and adjusting VrefDQ)
  @param[in]     VrefType            - Determines the Vref to change: WrV or CmdV only.
  @param[in]     Offset              - Vref offset value.
  @param[in]     UpdateMrcData       - Used to decide if Mrc host must be updated.
  @param[in]     PDAmode             - Selecting to use MRH or old method for MRS (only valid for DDR4 and adjusting VrefDQ)
  @param[in]     SkipWait            - Determines if we will wait for vref to settle after writing to register
  @param[in]     IsCachedOffsetParam - Determines if the parameter is an offset (relative to cache) or absolute value.

  @retval Nothing
**/
void
MrcUpdateVref (
  IN OUT MrcParameters *const MrcData,
  IN     UINT32               ChannelMask,
  IN     UINT8                RankMask,
  IN     UINT16               DeviceMask,
  IN     UINT8                VrefType,
  IN     INT32                Offset,
  IN     BOOLEAN              UpdateMrcData,
  IN     BOOLEAN              PDAmode,
  IN     BOOLEAN              SkipWait,
  IN     BOOLEAN              IsCachedOffsetParam
  )
{
  MrcDebug            *Debug;
  MrcInput            *Inputs;
  MrcOutput           *Outputs;
  MrcIntOutput        *IntOutputs;
  MrcIntControllerOut *IntControllerOut;
  const MRC_FUNCTION  *MrcCall;
  GSM_GT              Group;
  GSM_GT              PollGroup;
  INT64               GetSetVal;
  INT64               GetSetValChannels[MAX_CHANNEL];
  INT64               VrefConverged;
  INT64               CkeOn;
  UINT32              Rank;
  UINT16              *Vref;
  UINT16              NominalVref;
  UINT8               Count;
  UINT8               GetSetCh;
  UINT8               Channel;
  BOOLEAN             Ddr4;
  BOOLEAN             Lpddr4;


  IntOutputs       = (MrcIntOutput *)(MrcData->IntOutputs.Internal);
  IntControllerOut = &IntOutputs->Controller[0];
  Inputs           = &MrcData->Inputs;
  Outputs          = &MrcData->Outputs;
  Debug            = &Outputs->Debug;
  Lpddr4           = Outputs->DdrType == MRC_DDR_TYPE_LPDDR4;
  Ddr4             = Outputs->DdrType == MRC_DDR_TYPE_DDR4;
  MrcCall          = Inputs->Call.Func;


  if ((VrefType != WrV) && (VrefType != CmdV)) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s MrcUpdateVref - Invalid parameter %d\n", gErrString, VrefType);
    return;
  }
  MrcCall->MrcSetMem ((UINT8 *) GetSetValChannels, sizeof (GetSetValChannels), 0);
  if (Lpddr4 || (Ddr4 && (VrefType == WrV))) {
    if (Lpddr4 && (VrefType == CmdV)) {
      // We will program MR14 for FSP[1] while staying at low speed in FSP[0]
      Lpddr4SetFsp (MrcData, (UINT8) ChannelMask, ALL_SUB_CH_MASK, RankMask, MRC_IGNORE_ARG_8, Lp4FspWePoint1, Lp4FspOpPoint0);
      // Set Low frequency (1067), unless we're already there
      // This will also update Gear2 mode in MC/DDRIO, in LP4 we switch to Gear1 when going down to 1067.
      if ((Outputs->Frequency != f1067) && MrcData->Inputs.LpFreqSwitch) {
        // Lower CKE - change CLK frequency while DRAM is in Power Down
        CkeOn = 0;
        MrcGetSetDdrIoGroupChannel (MrcData, MAX_CHANNEL, GsmIocCkeOn, WriteNoCache, &CkeOn);
        MrcFrequencySwitch (MrcData, f1067, !Outputs->RestoreMRs);
        // Restore CKE
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (MrcChannelExist (Outputs, Channel)) {
            CkeOn = Outputs->Controller[CONTROLLER_0].Channel[Channel].ValidCkeBitMask;
            MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmIocCkeOn, WriteNoCache, &CkeOn);
          }
        } // Channel
      }
    } // LP4 and CmdV
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if ((!MrcChannelExist(Outputs, Channel)) || (((MRC_BIT0 << Channel) & ChannelMask) == 0)) {
        continue;
      }
//    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "MrcSetDramVref: Ch%d RankMask: 0x%02X\n", Channel, RankMask);
      MrcSetDramVref (
        MrcData,
        Channel,
        RankMask,
        DeviceMask,
        VrefType,
        Offset,
        UpdateMrcData,
        PDAmode,
        IsCachedOffsetParam
        );
    } // For Channel
    if (Lpddr4 && (VrefType == CmdV) && Outputs->LpddrEctDone) {
      // Set FSP-OP = 1, set High frequency
      MrcLpddr4SwitchToHigh (MrcData, !Outputs->RestoreMRs);
    }
    return;
  } // end if (Lpddr4 || (Ddr4 && (VrefType == WrV)))

  // CmdV DDR4:
  // 1. Read the Cached offset values.
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    GetChGroupTxVCmdV (MrcData, Channel, VrefType, &Group, &GetSetCh);
    MrcGetSetDdrIoGroupStrobe (MrcData, GetSetCh, 0, 0, Group, ReadFromCache, &GetSetValChannels[Channel]);
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if ((!MrcChannelExist(Outputs, Channel)) || (((MRC_BIT0 << Channel) & ChannelMask) == 0)) {
      continue;
    }
    // Get the corresponding groups and channels (register fields) to write to
    GetChGroupTxVCmdV (MrcData, Channel, VrefType, &Group, &GetSetCh);
    PollGroup = (Group == TxVref) ? GsmIocTxVrefConverge : GsmIocCmdVrefConverge;
    GetSetVal = Offset;

    if (IsCachedOffsetParam) {
      NominalVref = IntControllerOut->CaVref[Channel];
      GetSetVal += NominalVref;
    }
    // 2. Write Vref value - updated cached value.
    // TxVref and or CmdVref are fields of a single register we must ensure cache is updated,
    // Thus ForceWriteOffsetCached is required. Later we restore the cache according to UpdateMrcData.
    if (Inputs->IclA0) {
      MrcGetSetDdrIoGroupChannel (MrcData, GetSetCh, Group, ForceWriteCached, &GetSetVal);
    } else {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if ((1 << Rank) & RankMask) {
          MrcGetSetDdrIoGroupChannelRank (MrcData, GetSetCh, Rank, Group, ForceWriteCached, &GetSetVal);
        }
      }
    }

    // 3. Wait for Vref to settle.  Note VrefCA needs longer to settle.
    if (!SkipWait) {
      Count = 0;
      while (Count < 50) {
        // Don't wait more than 50uS
        if (Inputs->IclA0) {
          MrcGetSetDdrIoGroupChannel (MrcData, GetSetCh, PollGroup, ReadUncached, &VrefConverged);
        } else {
          VrefConverged = 1;
          for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
            if ((1 << Rank) & RankMask) {
              MrcGetSetDdrIoGroupChannelRank (MrcData, GetSetCh, Rank, GsmIocCmdVrefConverge, ReadUncached, &GetSetVal);
              VrefConverged &= GetSetVal;
            }
          }
        }
        if (VrefConverged == 1) {
          break;
        }
        MrcWait (MrcData, 1 * MRC_TIMER_1US);
        Count += 1;
      }
      if (Count >= 50) {
        MRC_DEBUG_MSG(Debug, MSG_LEVEL_WARNING, "CAVref circuit failed to converge: Channel %d\n", Channel);
      }
      MrcWait(MrcData, 5 * MRC_TIMER_1US); // Add 5us to make sure everything is done
    }
  }
  // 4. Update nominal CaVref point
  if (UpdateMrcData) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if ((!MrcChannelExist(Outputs, Channel)) || (((MRC_BIT0 << Channel) & ChannelMask) == 0)) {
        continue;
      }
      Vref = &IntControllerOut->CaVref[Channel];
      if (IsCachedOffsetParam) {
        *Vref += (UINT16)(Offset);
      } else {
        *Vref = (UINT16)(Offset);
      }
    }
  }
}

/**
  This function is used to move CMD/CTL/CLK/CKE PIs during training

  @param[in,out] MrcData    - Include all MRC global data.
  @param[in]     Channel    - Channel to shift PI for
  @param[in]     Iteration  - Determines which PI to shift:
                              MrcIterationClock = 0
                              MrcIterationCmd   = 1
                              MrcIterationCtl   = 2
  @param[in]     RankMask   - Ranks to work on
  @param[in]     GroupMask  - Which groups to work on for CLK/CMD/CTL. Up to 4 CMD for LPDDR4.  Up to 5 CMD for DDR4.
  @param[in]     NewValue   - value to shift in case of CLK Iteration, New value for all other cases
  @param[in]     UpdateHost - Determines if MrcData structure is updated

  @retval Nothing
**/
void
ShiftPIforCmdTraining (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Channel,
  IN     const UINT8          Iteration,
  IN     const UINT8          RankMask,
  IN     const UINT8          GroupMask,
  IN     INT32                NewValue,
  IN     const UINT8          UpdateHost
  )
{
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  const MrcChannelIn  *ChannelIn;
  MrcOutput           *Outputs;
  MrcIntOutput        *IntOutputs;
  MrcIntCmdTimingOut  *IntCmdTiming;
  GSM_GT              GsmMode;
  INT64               GetSetVal;
  UINT32              ByteMask;
  UINT32              PiGroup;
  UINT8               Rank;
  UINT8               LocalRankMask;
  UINT8               Group;
  UINT8               CmdGroupMax;
  INT8                Shift;
  BOOLEAN             Lpddr;
  BOOLEAN             Lpddr4;
  BOOLEAN             Ddr4;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ChannelIn     = &Inputs->Controller[0].Channel[Channel];
  IntOutputs    = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  IntCmdTiming  = &IntOutputs->Controller[0].CmdTiming[Channel];
  Lpddr4        = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  Ddr4          = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr         = Lpddr4;
  GsmMode       = ForceWriteCached;
  CmdGroupMax   = (Lpddr) ? MAX_COMMAND_GROUPS - 1 : MAX_COMMAND_GROUPS;

  if (Iteration != MrcIterationClock) {
    if (NewValue < 0) {
      NewValue = 0;
    } else if (NewValue > 127) {
      NewValue = 127;
    }
  }
  // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nShiftPIforCmdTraining: Iteration: %d, Channel: %d, RankMask: %d, GroupMask: %d, NewValue = %d\n", Iteration, Channel, RankMask, GroupMask, NewValue);

  switch (Iteration) {
    case MrcIterationClock: // SHIFT CLOCK
      ByteMask  = 0x1FF;    // Shift DQ PI on all 9 bytes by default
      LocalRankMask = RankMask;
      if (Inputs-> Ddr4DdpSharedClock) { // CLK 0 is shared between Rank0 and Rank1
        if (RankMask & (1 << 1)) {       // If Rank1 is selected
          LocalRankMask |= (1 << 0);     // then select Rank0 as well, for CLK PI shift
        }
      }
      if (Lpddr) {
        // In LPDDR clocks not per rank
        // LPDDR4 clocks are per channel
        for (Group = 0; Group < 2; Group++) {
          if (GroupMask & (1 << Group)) {
            Shift = (IntCmdTiming->ClkPiCode[Group] + NewValue) % 128;
            if (Shift < 0) {
              Shift = (128 - ABS (Shift));
            }

            GetSetVal = Shift;
            MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Group, ClkGrpPi, GsmMode, &GetSetVal);
            if (UpdateHost) {
              IntCmdTiming->ClkPiCode[Group] = (UINT8) GetSetVal;
            }

            // Each clock spans all ranks, so need to shift DQ PIs on all ranks, for bytes in this group only
            ByteMask = ChannelIn->DQByteMap[MrcIterationClock][Group];
            for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
              if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
                ShiftDQPIs (MrcData, Channel, Rank, ByteMask, (INT8) NewValue, UpdateHost);
              }
            }
          }
        } // for Group
      } else {
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if (LocalRankMask & (1 << Rank)) {
            Shift = ((INT8) (IntCmdTiming->ClkPiCode[Rank]) + NewValue) % 128;
            if (Shift < 0) {
              Shift = (128 - ABS (Shift));
            }

            GetSetVal = Shift;
            if (RankMask & (1 << Rank)) {
              MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Rank, ClkGrpPi, GsmMode, &GetSetVal);
              if (UpdateHost) {
                IntCmdTiming->ClkPiCode[Rank] = (UINT8) GetSetVal;
              }
              ShiftDQPIs (MrcData, Channel, Rank, ByteMask, (INT8) NewValue, UpdateHost);
            }
          }
        }
      }
      break;

    case MrcIterationCmd: // Shift Command
      GetSetVal = NewValue;
      for (Group = 0; Group < CmdGroupMax; Group++) {
        if ((1 << Group) & GroupMask) {
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Group, CmdGrpPi, GsmMode, &GetSetVal);
          if (UpdateHost) {
            IntCmdTiming->CmdPiCode[Group] = (UINT8) GetSetVal;
          }
        }
      }
      break;

    case MrcIterationCtl: // Shift CS/ODT and CKE.Control
      GetSetVal = NewValue;
      if (Ddr4) {
        // Shift CS/ODT/CKE
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if (RankMask & (1 << Rank)) {
            // X0 uses same PI Group for Ranks 0/1
            PiGroup = Rank;
            MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Rank, CtlGrpPi, GsmMode, &GetSetVal);
            MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, PiGroup, CkeGrpPi, GsmMode, &GetSetVal);
            if (UpdateHost) {
              IntCmdTiming->CtlPiCode[Rank] = (UINT8) GetSetVal;
              IntCmdTiming->CkePiCode[Rank] = (UINT8) GetSetVal;
            }
          }
        }
      } else {
        // Lpddr4 Enhanced Channel Mode.  Each CS is per Sub Channel
        // Use GroupMask to select the Sub Channel to shift.
        for (Group = 0; Group < MAX_SUB_CHANNEL; Group++) {
          if (GroupMask & (1 << Group)) {
            MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Group, CtlGrpPi, GsmMode, &GetSetVal);
            MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Group, CkeGrpPi, GsmMode, &GetSetVal);
            if (UpdateHost) {
              IntCmdTiming->CtlPiCode[Group] = (UINT8) GetSetVal;
              IntCmdTiming->CkePiCode[Group] = (UINT8) GetSetVal;
            }
          }
        }
      }
      break;

    default:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "%sUnknown parameter to shift\n", gWarnString);
      break;
  }

  return;
}

/**
  Shifts RcvEn, WriteLevel and WriteDQS timing for all bytes
  Usually used when moving the clocks on a channel

  @param[in,out] MrcData    - Include all MRC global data.
  @param[in]     Channel    - Channel to update
  @param[in]     Rank       - Rank to update
  @param[in]     ByteMask   - Bytes to update
  @param[in]     Offset     - value to shift
  @param[in]     UpdateHost - Determines if MrcData structure is updated
                              = 1 set the local valid flag to FALSE
                              = 0 set valid flag is TRUE. uses locally saved DQ/DQS/RecEn delays.

  @retval Nothing
**/
void
ShiftDQPIs (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          Channel,
  IN     const UINT8          Rank,
  IN     const UINT32         ByteMask,
  IN     const INT8           Offset,
  IN     const UINT8          UpdateHost
  )
{
  MrcOutput             *Outputs;
  MrcIntOutput          *IntOutputs;
  MrcIntControllerOut   *IntControllerOut;
  MrcIntClkAlignedParam *ClkAlignParam;
  MrcInput              *Inputs;
  MRC_FUNCTION          *MrcCall;
  UINT8                 Byte;
  UINT8                 GsmMode;
  INT64                 RecEnDelayValue[MAX_SDRAM_IN_DIMM];
  INT64                 TxDqDelayValue[MAX_SDRAM_IN_DIMM];
  INT64                 TxDqsDelayValue[MAX_SDRAM_IN_DIMM];

  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  MrcCall     = Inputs->Call.Func;
  GsmMode     = ForceWriteCached;
  IntOutputs  = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  IntControllerOut = &IntOutputs->Controller[0];
  MrcCall->MrcSetMem ((UINT8 *) RecEnDelayValue, sizeof (RecEnDelayValue), 0);
  MrcCall->MrcSetMem ((UINT8 *) TxDqDelayValue, sizeof (TxDqDelayValue), 0);
  MrcCall->MrcSetMem ((UINT8 *) TxDqsDelayValue, sizeof (TxDqsDelayValue), 0);

  for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
    if (((1 << Byte) & ByteMask) == 0) {
      continue;
    }
    ClkAlignParam = &IntControllerOut->IntClkAlignedMargins[Channel][Rank][Byte];
    // Initialize local variables which the offset is applied to.
    // If the host structure isn't valid, we start with the register state.
    // Otherwise, we will pull the results from the internal host structure.
    if (!ClkAlignParam->Valid) {
      MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RecEnDelay, ReadFromCache, &RecEnDelayValue[Byte]);
      MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqDelay,  ReadFromCache, &TxDqDelayValue[Byte]);
      MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqsDelay, ReadFromCache, &TxDqsDelayValue[Byte]);
      if (!UpdateHost) {
        // If the host structure is not valid and we're not updating the host,
        // we will save the register value to the host structure. Then set the valid bit.
        ClkAlignParam->RcvEn = (UINT16) RecEnDelayValue[Byte];
        ClkAlignParam->TxDq  = (UINT16) TxDqDelayValue[Byte];
        ClkAlignParam->TxDqs = (UINT16) TxDqsDelayValue[Byte];
        ClkAlignParam->Valid = TRUE;
      }
    } else {
      RecEnDelayValue[Byte] = ClkAlignParam->RcvEn;
      TxDqDelayValue[Byte]  = ClkAlignParam->TxDq;
      TxDqsDelayValue[Byte] = ClkAlignParam->TxDqs;
    }

    if (UpdateHost) {
      // If UpdateHost is set, we need to clear the valid bit from the host structure.
      ClkAlignParam->Valid = FALSE;
    }
  }
  for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
    if (((1 << Byte) & ByteMask) == 0) {
      continue;
    }
    RecEnDelayValue[Byte] = RecEnDelayValue[Byte] + Offset;
    TxDqDelayValue[Byte]  = TxDqDelayValue[Byte]  + Offset;
    TxDqsDelayValue[Byte] = TxDqsDelayValue[Byte] + Offset;
    MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RecEnDelay, GsmMode, &RecEnDelayValue[Byte]);
    MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqDelay,  GsmMode, &TxDqDelayValue[Byte]);
    MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqsDelay, GsmMode, &TxDqsDelayValue[Byte]);
  }

  return;
}

/**
  Retrieve the current memory frequency and clock from the memory controller.

  @param[in]      MrcData      - Include all MRC global data.
  @param[in, out] MemoryClock  - The current memory clock.
  @param[in, out] Ratio        - The current memory ratio setting.
  @param[in, out] RefClk       - The current memory reference clock.

  @retval: The current memory frequency.
**/
MrcFrequency
MrcGetCurrentMemoryFrequency (
  MrcParameters * const   MrcData,
  UINT32 * const          MemoryClock,
  MrcClockRatio * const   Ratio,
  MrcRefClkSelect * const RefClk
  )
{
  const MrcInput                 *Inputs;
  MC_BIOS_REQ_PCU_STRUCT     McBiosReqPcu;
  MC_BIOS_DATA_PCU_STRUCT    McBiosData;

  Inputs  = &MrcData->Inputs;
  McBiosReqPcu.Data = MrcReadCR (MrcData, MC_BIOS_REQ_PCU_REG);
  McBiosData.Data   = MrcReadCR (MrcData, MC_BIOS_DATA_PCU_REG);

  if (McBiosData.Bits.GEAR_TYPE == 1) {
    McBiosData.Bits.MC_FREQ *= 2; // In gear2 the actual ratio is twice the ratio in the register
  }
  if (MemoryClock != NULL) {
    *MemoryClock = MrcRatioToClock (MrcData, (MrcClockRatio) McBiosData.Bits.MC_FREQ, McBiosReqPcu.Bits.REQ_TYPE, Inputs->BClkFrequency);
  }
  if (Ratio != NULL) {
    *Ratio = (MrcClockRatio) McBiosData.Bits.MC_FREQ;
  }
  if (RefClk != NULL) {
    *RefClk = (MrcRefClkSelect) McBiosReqPcu.Bits.REQ_TYPE;
  }
  return MrcRatioToFrequency (
          MrcData,
          (MrcClockRatio) McBiosData.Bits.MC_FREQ,
          McBiosReqPcu.Bits.REQ_TYPE,
          Inputs->BClkFrequency
          );
}

/**
  Returns the Offset for DataTrainFeedback register

  @param[in]   MrcData - The MRC global data.
  @param[in]   Channel - Channel in question, 0xFF if Overall Broadcast (Byte is Dont Care if Overall Broadcast)
  @param[in]   Byte    - Byte in question, 0xFF if Channel Broadcast

  @retval Offset - MCHBAR offset
**/
UINT32
MrcGetOffsetDataTrainFeedback (
  IN MrcParameters * const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           Byte
  )
{
  UINT32  Offset;

  if (Channel >= MAX_CHANNEL) {
    // Overall Broadcast
    Offset = DDRDATA_CR_DATATRAINFEEDBACK_REG;
  } else if (Byte >= MAX_SDRAM_IN_DIMM) {
    // Channel Broadcast
    Offset = DDRDATACH0_CR_DATATRAINFEEDBACK_REG;
    Offset += ((DDRDATACH1_CR_DATATRAINFEEDBACK_REG - DDRDATACH0_CR_DATATRAINFEEDBACK_REG) * Channel);
  } else {
    // Specific Channel and Byte
    Offset = DDRDATA0CH0_CR_DATATRAINFEEDBACK_REG +
      ((DDRDATA0CH1_CR_DATATRAINFEEDBACK_REG - DDRDATA0CH0_CR_DATATRAINFEEDBACK_REG) * Channel) +
      ((DDRDATA1CH0_CR_DATATRAINFEEDBACK_REG - DDRDATA0CH0_CR_DATATRAINFEEDBACK_REG) * Byte);
  }

  return Offset;

}

/**
  Returns the Offset for DataOffsetComp register

  @param[in]   MrcData - The MRC global data.
  @param[in]   Channel - Channel in question, 0xFF if Overall Broadcast (Byte is Dont Care if Overall Broadcast)
  @param[in]   Byte    - Byte in question, 0xFF if Channel Broadcast

  @retval Offset - MCHBAR offset
**/
UINT32
MrcGetOffsetDataOffsetComp (
  IN MrcParameters * const MrcData,
  IN const UINT8           Channel,
  IN const UINT8           Byte
  )
{
  UINT32  Offset;

  if (Channel >= MAX_CHANNEL) {
    // Overall Broadcast
    Offset = DDRDATA_CR_DDRCRDATAOFFSETCOMP_REG;
  } else if (Byte >= MAX_SDRAM_IN_DIMM) {
    // Channel Broadcast
    Offset = DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_REG +
      ((DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_REG - DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_REG) * Channel);
  } else {
    // Specific Channel and Byte
    Offset = DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_REG +
      ((DDRDATA0CH1_CR_DDRCRDATAOFFSETCOMP_REG - DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_REG) * Channel) +
      ((DDRDATA1CH0_CR_DDRCRDATAOFFSETCOMP_REG - DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_REG) * Byte);
  }

  return Offset;

}

/**
  Determines if Per-Bit Deskew is needed.  If not, it will disable Per-Bit Deskew.

  @param[in]   MrcData      - The MRC global data.
  @param[in]   MarginResult - Data structure with the latest margin results.
  @param[in]   Param        - Only RdT(1) and WrT(2) are valid.
**/
void
MrcPerBitDeskew (
  IN MrcParameters * const MrcData,
  IN UINT32                MarginResult[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN const UINT8           Param
  )
{
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  UINT32            MinEyeWidth;
  UINT32            EyeWidth;
  UINT8             ResultType;
  UINT8             Channel;
  UINT8             Rank;
  UINT8             Byte;
  BOOLEAN           Update;
  BOOLEAN           ByteSaturation;
  UINT16            PwrLimit;
  UINT16            UPMLimit;
  INT64             GetSetEn;
  GSM_GT            Group;
  MrcIntOutput          *IntOutputs;
  MrcIntControllerOut   *IntControllerOut;

  IntOutputs = (MrcIntOutput *)(MrcData->IntOutputs.Internal);
  IntControllerOut = &IntOutputs->Controller[0];
  Outputs    = &MrcData->Outputs;
  Debug      = &Outputs->Debug;

  GetSetEn   = 1;
  Update    = FALSE;
  if ((Param != RdT) && (Param != WrT)) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "MrcPerBitDeskew: Incorrect Margin Parameter %d\n", Param);
    return;
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Parameter = %d (%sT)\n", Param, (Param == RdT) ? "Rd" : "Wr");
  ResultType       = GetMarginResultType (Param);

  Group = (Param == RdT) ? GsmIocRxDeskewDis : GsmIocTxDeskewDis;

  PwrLimit = MrcGetUpmPwrLimit (MrcData, Param, PowerLimit);
  UPMLimit = MrcGetUpmPwrLimit (MrcData, Param, UpmLimit);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "MrcPerBitDeskew: PwrLimit %u UPMLimit %u ((PwrLimit + UPMLimit) / 2) %u\n", PwrLimit, UPMLimit, (PwrLimit + UPMLimit) / 2);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MinEyeWidth = 0xFFFFFFFF;
        ByteSaturation = FALSE;
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
            ByteSaturation |= (Param == RdT) ? IntControllerOut->MrcRxPbdSaturated[Channel][Rank][Byte] : IntControllerOut->MrcTxPbdSaturated[Channel][Rank][Byte];
            EyeWidth = MarginResult[ResultType][Rank][Channel][Byte][0] + MarginResult[ResultType][Rank][Channel][Byte][1];
            MinEyeWidth = MIN (MinEyeWidth, EyeWidth);
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "  Channel %u Byte %u Rank %u LM %u RM %u Width %u MinWidth %u\n", Channel, Byte, Rank,
              MarginResult[ResultType][Rank][Channel][Byte][0], MarginResult[ResultType][Rank][Channel][Byte][1], EyeWidth, MinEyeWidth);
          } // if Rank Exist
        } // for Rank
        if (MinEyeWidth > (UINT32)((PwrLimit + UPMLimit) / 2)) {
          Update = TRUE;
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, Group, WriteToCache | PrintValue, &GetSetEn);
        } else if (ByteSaturation) {
          Update = TRUE;
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "  Channel %u Byte %u PBD Saturated\n", Channel, Byte, ByteSaturation);
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, Group, WriteToCache | PrintValue, &GetSetEn);
        }// if MinEyeWidth
      }// for Byte
    }// if Channel Exist
  }// for Channel

  if (Update) {
    MrcFlushRegisterCachedData (MrcData);
  }
}

/**
  Enable / Disable CADB and Deselects on MC (on all populated channels)

  @param[in] MrcData  - The MRC global data.
  @param[in] Enable   - TRUE to enable, FALSE to disable.

  @retval Nothing
**/
void
McCadbEnable (
  IN MrcParameters *const  MrcData,
  IN BOOLEAN               Enable
  )
{
  INT64   Control;
  INT64   GetSetEn;
  INT64   GetSetDis;

  Control   = Enable ? 1 : 0;
  GetSetEn  = 1;
  GetSetDis = 0;
  MrcGetSetDdrIoGroupChannel (MrcData, MAX_CHANNEL, GsmMccBlockXarb,            WriteNoCache, &GetSetEn);  // Block XARB when changing cadb_enable
  MrcGetSetDdrIoGroupChannel (MrcData, MAX_CHANNEL, GsmMccCadbEnable,           WriteNoCache, &Control);
  MrcGetSetDdrIoGroupChannel (MrcData, MAX_CHANNEL, GsmMccDeselectEnable,       WriteNoCache, &Control);
  MrcGetSetDdrIoGroupChannel (MrcData, MAX_CHANNEL, GsmMccCmdTriStateDisTrain,  WriteNoCache, &Control);
  MrcGetSetDdrIoGroupChannel (MrcData, MAX_CHANNEL, GsmMccBlockXarb,            WriteNoCache, &GetSetDis); // Unblock XARB
}

/**
  Run a short CADB sequence on selected channels

  @param[in] MrcData   - The MRC global data.
  @param[in] ChBitMask - channels to work on.

  @retval Nothing
**/
void
ShortRunCADB (
  IN MrcParameters *const  MrcData,
  IN UINT8                 ChBitMask
  )
{
  const MRC_FUNCTION  *MrcCall;
  MrcOutput   *Outputs;
  INT64       CmdTriStateDisSave[MAX_CHANNEL];
  INT64       CmdTriStateDis;
  UINT32      Channel;
  UINT32      TestDone;
  UINT64      Timeout;
  CH0_SC0_CR_CADB_CFG_STRUCT        CadbConfig;
  CH0_SC0_CR_CADB_CTL_STRUCT        CadbControl;
  CH0_SC0_CR_CADB_AO_MRSCFG_STRUCT  MrsConfig;

  MrcCall   = MrcData->Inputs.Call.Func;
  Outputs   = &MrcData->Outputs;

  // Enable CADB
  McCadbEnable (MrcData, TRUE);

  // Select CADB engines (Previous setup may have setup SEEDS on a per channel basis and thus MrcIntData->ChSubChMaskEnable may be incorrect)
  MrcSelectEngines (MrcData, 0, ChBitMask, Outputs->ValidSubChMask);

  // Disable command tri-state in order to get CADB traffic
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (((1 << Channel) & ChBitMask) != 0) {
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccCmdTriStateDis, ReadFromCache, &CmdTriStateDisSave[Channel]);
      CmdTriStateDis = 1;
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccCmdTriStateDis, WriteCached, &CmdTriStateDis);
    }
  }

  // Enable CADB Always On mode
  CadbConfig.Data = 0;
  CadbConfig.Bits.CADB_MODE = Cadb20ModeAlwaysOn;
  CadbConfig.Bits.LANE_DESELECT_EN      = 5;        // Drive deselects on CS and CA pins; @todo - not sure this is needed in AlwaysOn mode ?
  CadbConfig.Bits.INITIAL_DSEL_EN       = 1;
  CadbConfig.Bits.INITIAL_DSEL_SSEQ_EN  = 1;
  Cadb20ConfigRegWrite (MrcData, CadbConfig);

  MrsConfig.Data = 0;
  MrsConfig.Bits.MRS_AO_REPEATS = 8;                // Issue a single loop over pattern buffer (8*4=32). Zero means endless test, until STOP_TEST is set.
  // Keep MRS_GAP = 0 - No gap
  // Keep MRS_GAP_SCALE = 0 - Linear
  Cadb20MrsConfigRegWrite (MrcData, MrsConfig);

  // Start CADB
  CadbControl.Data = 0;
  CadbControl.Bits.START_TEST = 1;
  Cadb20ControlRegWrite (MrcData, CadbControl);

  // Poll till test done on all participating channels / subch
  Timeout = MrcCall->MrcGetCpuTime (MrcData) + 10000;   // 10 seconds timeout
  do {
    TestDone = Cadb20TestDoneStatus (MrcData);
  } while ((TestDone == 0) && (MrcCall->MrcGetCpuTime (MrcData) < Timeout));

  // Disable CADB Always On mode
  CadbConfig.Bits.CADB_MODE = Cadb20ModeOff;
  Cadb20ConfigRegWrite (MrcData, CadbConfig);

  // Restore original command tri-state value
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (((1 << Channel) & ChBitMask) != 0) {
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccCmdTriStateDis, WriteCached, &CmdTriStateDisSave[Channel]);
    }
  }

  // Disable CADB
  McCadbEnable (MrcData, FALSE);
}

/**
  Get the Rx Bias values

  @param[in, out] MrcData    - Include all MRC global data.
  @param[in, out] RxFselect  - Location to save RxFselect.

  @retval Nothing
**/
void
GetRxFselect (
  IN MrcParameters *const MrcData,
  IN OUT INT8             *RxFselect
  )
{
  MrcOutput                    *Outputs;

  Outputs          = &MrcData->Outputs;
  *RxFselect       = (Outputs->Ratio - ((Outputs->RefClk == MRC_REF_CLOCK_133) ? RXF_SELECT_RC_133 : RXF_SELECT_RC_100));

  // Limit ratios for 1067, 1333, 1600, 1867 & 2133 MHz
  *RxFselect = MIN (*RxFselect, RXF_SELECT_MAX);  // Maximum 2133 MHz
  *RxFselect = MAX (*RxFselect, RXF_SELECT_MIN);  // Minimum 1067 MHz
  return;
}

/**
  Read 32-bit value from the specified bus/device/function/offset.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Bus      - PCI bus number.
  @param[in] Device   - PCI device number.
  @param[in] Function - PCI function number.
  @param[in] Offset   - PCI address offset.

  @retval 32-bit PCI value.
**/
UINT32
MrcPciRead32 (
  IN const MrcParameters * const MrcData,
  IN const UINT8 Bus,
  IN const UINT8 Device,
  IN const UINT8 Function,
  IN const UINT8 Offset
  )
{
  const MrcInput     *Inputs;
  const MRC_FUNCTION *MrcCall;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  MrcCall->MrcIoWrite32 (Inputs->PciIndex, MrcCall->MrcGetPciDeviceAddress (Bus, Device, Function, Offset));
  return (MrcCall->MrcIoRead32 (Inputs->PciData));
}

/**
  This function changes the DIMM Voltage to the closest desired voltage without
  going higher. Default wait time is the minimum value of 200us, if more time
  is needed before deassertion of DIMM Reset#, then change the parameter.

  @param[in, out] MrcData            - The MRC "global data" area.
  @param[in]      VddVoltage         - Selects the DDR voltage to use, in mV.
  @param[in, out] VddSettleWaitTime  - Time needed for Vdd to settle after the update

  @retval TRUE if a voltage change occurred, otherwise FALSE.
**/
BOOLEAN
MrcVDDVoltageCheckAndSwitch (
  IN OUT MrcParameters      *MrcData,
  IN     const MrcVddSelect VddVoltage,
  IN OUT UINT32 * const     VddSettleWaitTime
  )
{
  MRC_FUNCTION *MrcCall;
  MrcInput     *Inputs;
  MrcOutput    *Outputs;
  MrcDebug     *Debug;
  MrcVddSelect Current;
  MrcVddSelect DefaultVdd;
  MrcVddSelect NewVdd;
  BOOLEAN      Status;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Status  = FALSE;

  // DDR4 use 1.2v by default; LPDDR4 is 1.1v; LPDDR4x is 0.6v
  if (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) {
    DefaultVdd = (Outputs->Lp4x) ? VDD_0_60 : VDD_1_10;
  } else {
    DefaultVdd = VDD_1_20;
  }

  Current = (MrcVddSelect) MrcCall->MrcGetMemoryVdd (MrcData, DefaultVdd);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Current VddVoltage is %u mV\n", Current);
  if (VddVoltage != Current) {
    NewVdd = MrcCall->MrcSetMemoryVdd (MrcData, DefaultVdd, VddVoltage);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*** VddVoltage updated to %u mV\n", NewVdd);
    Status = TRUE;
  }

  // Increase the VddSettleWaitTime by the amount requested in the Input structure
  *VddSettleWaitTime += Inputs->VddSettleWaitTime;

  // Either update was already done or change is not necessary every time this is called
  Outputs->VddVoltageDone = TRUE;

  return Status;
}
#ifdef MRC_DEBUG_PRINT
/**
  Debug output of MarginResults for specific ResultType

  @param[in] MrcData - Pointer to MRC global data.
  @param[in] ResultType - Margin Result Type.  MAX_RESULT_TYPE prints all parameters.

**/
void
MrcDisplayMarginResultArray (
  IN MrcParameters *MrcData,
  IN UINT8         ResultType
  )
{
  MrcDebug    *Debug;
  MrcOutput   *Outputs;
  UINT32      ResTypeStart;
  UINT32      ResTypeEnd;
  UINT32      ResTypeIdx;
  UINT32      Channel;
  UINT32      Rank;
  UINT32      Byte;
  UINT32      Edge;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  if (ResultType >= MAX_RESULT_TYPE) {
    ResTypeStart = 0;
    ResTypeEnd = MAX_RESULT_TYPE;
  } else {
    ResTypeStart = ResultType;
    ResTypeEnd = ResultType + 1;
  }

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "***********************Margin Results**********************\n"
    );
  for (ResTypeIdx = ResTypeStart; ResTypeIdx < ResTypeEnd; ResTypeIdx++) {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "%s\tB0E0\tB0E1\tB1E0\tB1E1\tB2E0\tB2E1\tB3E0\tB3E1\tB4E0\tB4E1\tB5E0\tB5E1\tB6E0\tB6E1\tB7E0\tB7E1\tB8E0\tB8E1\n",
      gResTypeStr[ResTypeIdx]
      );
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (Outputs, Channel)) {
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%dR%d\t", Channel, Rank);
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              for (Edge = 0; Edge < MAX_EDGES; Edge++) {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%u\t", (UINT16) Outputs->MarginResult[ResTypeIdx][Rank][Channel][Byte][Edge]);
              } //Edge
            } //Byte
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
          }//RankExist
        } //Rank
      } //ChannelExist
    } //Channel
  } // ResTypeIdx

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "***********************************************************\n");
}
#endif //MRC_DEBUG_PRINT

/**
  This function sets up the REUT registers for Alias Check and DDR4 PDA mapping

  Setup for Memory Check like Alias Checking and DDR4 PDA mapping

  @param[in, out] MrcData           - Pointer to MRC global data.
  @param[in, out] ReutAddress       - Pointer to ReutAddress that will be programmed to REUT engine
  @param[in] Rank                   - Rank to setup
  @param[in] NumOfCachelines        - # of Cachelines to write and read to.  0 is a special value that will write the number
                                      of Cachelines that is required to determine Row/Column Aliasing.
  @param[in, out] ReutUninitialized - Pointer of whether ReutAddress Pointer needs initializing or not.

  @retval Nothing
**/
void
MrcMemoryCheckSetup (
  IN OUT MrcParameters *const MrcData,
  IN OUT MRC_REUTAddress      *ReutAddress,
  IN UINT8                    Rank,
  IN UINT8                    NumOfCachelines,
  IN OUT BOOLEAN              *ReutUninitialized
  )
{

//  static const UINT8 WrapCarryEn[MrcReutFieldMax]   = {0, 0, 0, 0};
//  static const UINT8 WrapTriggerEn[MrcReutFieldMax] = {0, 0, 0, 0};  // Trigger Stop on Bank Wrap
//  static const UINT8 AddrInvertEn[MrcReutFieldMax]  = {0, 0, 0, 0};
//  MrcDimmOut         *DimmOut;
//  UINT32             CrOffset;
//  UINT32             WritesPerPage;
//  UINT16             ColumnIncValUnaligned;
//  UINT8              RankToDimm;
//  UINT8              Channel;
//  UINT8              GlobalControl;
// @ todo <ICL> Update with CPGC 2.0 implementation
//  REUT_CH_SEQ_CFG_0_STRUCT              ReutChSeqCfg;
//  MCHBAR_CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_STRUCT    ReutChPatWdbCl;
//  REUT_PG_PAT_CL_MUX_CFG_STRUCT ReutChPatWdbClMuxCfg;
//  REUT_CH0_SUBSEQ_CTL_0_STRUCT          ReutSubSeqCtl;

  //@todo: Use host burst length
//  BurstLength = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) ?  16 : 8;

  if (*ReutUninitialized == TRUE) {
/**
    // Test Initialization
    // Start with IncRate = 3 so we have 4 column writes per page.  This will change with Column Size.
    // Must have 4 (reg + 1) writes to move to the next LFSR code for unique values.
    ReutAddress->IncRate[MrcReutFieldRow]  = 3;
    // IncVal[Col] is chosen to be 1/4 of the minimum column supported to get 4 writes per page.
    // Each write is 1 cache line (8 or 16 column addresses worth of data).
    // IncVal is on a cache line basis when programmed.  Account for this here by dividing by the burst length.
    ColumnIncValUnaligned                 = MRC_BIT10 / 4;
    ReutAddress->IncVal[MrcReutFieldCol]  = ColumnIncValUnaligned / BurstLength; // cache line shift

    // Smallest Row address size is 2^12, but Row_Base_Address_Increment is a 12-bit signed field [0-11].
    // Thus we have to increment by 2^10.
    ReutAddress->IncVal[MrcReutFieldRow]  = MRC_BIT10;
    ReutAddress->Stop[MrcReutFieldCol]    = 1024; // 4 ([0-3] << 3) column writes before wrapping
    ReutAddress->Start[MrcReutFieldBank]  = 1;
    ReutAddress->Stop[MrcReutFieldBank]   = 1;

    // Setup Reut all present channels.
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
// @ todo <ICL> Update with CPGC 2.0 implementation; MrcProgramSequenceAddress deprecated
      // Write initial Reut Address Values.
      MrcProgramSequenceAddress (
        MrcData,
        Channel,
        ReutAddress->Start,
        NULL,              // Stop
        ReutAddress->Order,
        ReutAddress->IncRate,
        ReutAddress->IncVal,
        WrapTriggerEn,
        WrapCarryEn,
        AddrInvertEn,
        0,
        FALSE
        );

      // Set Reut to Write
      CrOffset = OFFSET_CALC_CH (REUT_CH_SEQ_CFG_0_REG, REUT_CH_SEQ_CFG_1_REG, Channel);
      ReutChSeqCfg.Data                         = MrcReadCR (MrcData, CrOffset);
      GlobalControl                             = (UINT8) ReutChSeqCfg.Bits.Global_Control;
      ReutChSeqCfg.Data                         = 0;
      ReutChSeqCfg.Bits.Initialization_Mode     = REUT_Testing_Mode;
      ReutChSeqCfg.Bits.Start_Test_Delay        = 2;
      ReutChSeqCfg.Bits.Subsequence_End_Pointer = 1;
      ReutChSeqCfg.Bits.Global_Control          = GlobalControl;

      MrcWriteCR64 (
        MrcData,
        CrOffset,
        ReutChSeqCfg.Data
        );

      MrcSetLoopcount (MrcData, Channel, 1);

      // Program Write Data Buffer Control.
      // @todo: Update for new ICL design.
      MrcSelectPatternGen (MrcData, 1 << Channel, 0, 0);
      // Setup CADB in terms of LFSR selects, LFSR seeds, LMN constants and overall control
      CrOffset = REUT_PG_PAT_CL_MUX_CFG_REG;
      ReutPgPatMuxCfg.Data               = 0;
      ReutPgPatMuxCfg.Bits.Mux0_Control  = MrcPgMuxLfsr;
      ReutPgPatMuxCfg.Bits.Mux1_Control  = MrcPgMuxLfsr;
      ReutPgPatMuxCfg.Bits.Mux2_Control  = MrcPgMuxLfsr;
      ReutPgPatMuxCfg.Bits.LFSR_Type_0   = MrcLfsr16;
      ReutPgPatMuxCfg.Bits.LFSR_Type_1   = MrcLfsr16;
      ReutPgPatMuxCfg.Bits.LFSR_Type_2   = MrcLfsr16;
      MrcWriteCR64 (MrcData, CrOffset, ReutPgPatMuxCfg.Data);
      //@todo: Enable ECC to be Checked.
    }// Channel
    *ReutUninitialized = FALSE;
  }// ReutUninitialized

  if ((MRC_BIT0 << Rank) & Outputs->ValidRankMask) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      // Update Rank stop address based on DIMM SPD if Active.
      RankToDimm  = RANK_TO_DIMM_NUMBER (Rank);
      DimmOut     = &ControllerOut->Channel[Channel].Dimm[RankToDimm];
      // Since we're counting cache lines and won't wrap the row address,
      // program Row Stop to RowSize - 1 to avoid resetting the current address.
      // Column must wrap.  The wrap occurs on the increment which is after writing,
      // to that address.  Thus, we set wrap to be the last accessed column.
      ColumnIncValUnaligned                 = ReutAddress->IncVal[MrcReutFieldCol] * BurstLength; // cache line shift
      WritesPerPage                         = DimmOut->ColumnSize / ColumnIncValUnaligned;
      ReutAddress->Stop[MrcReutFieldRow]    = (UINT16) DimmOut->RowSize - 1;
      ReutAddress->Stop[MrcReutFieldCol]    = DimmOut->ColumnSize - ColumnIncValUnaligned;
      ReutAddress->IncRate[MrcReutFieldRow] = WritesPerPage - 1; // IncRate is +1 the programmed value
// @todo <ICL> Update with CPGC 2.0 implementation; MrcProgramSequenceAddress deprecated
      MrcProgramSequenceAddress (
        MrcData,
        Channel,
        NULL,
        ReutAddress->Stop,
        NULL,
        ReutAddress->IncRate,
        NULL,
        NULL,
        NULL,
        NULL,
        0,
        FALSE
        );
      // Determine if we are doing an alias check, or a specific number of cachelines.
      WritesPerPage = (NumOfCachelines > 0) ? NumOfCachelines : ((DimmOut->RowSize / MRC_BIT10) * WritesPerPage);

      // Set up the Subsequence control.
      CrOffset = OFFSET_CALC_CH (REUT_CH0_SUBSEQ_CTL_0_REG, REUT_CH1_SUBSEQ_CTL_0_REG, Channel);
      ReutSubSeqCtl.Data = 0;
      ReutSubSeqCtl.Bits.Subsequence_Type     = BWr;
      ReutSubSeqCtl.Bits.Number_of_Cachelines = MrcLog2 (WritesPerPage - 1);
      MrcWriteCR (MrcData, CrOffset, ReutSubSeqCtl.Data);

      CrOffset += REUT_CH0_SUBSEQ_CTL_1_REG - REUT_CH0_SUBSEQ_CTL_0_REG;
      ReutSubSeqCtl.Bits.Reset_Current_Base_Address_To_Start = 1;
      ReutSubSeqCtl.Bits.Subsequence_Type = BRd;
      MrcWriteCR (MrcData, CrOffset, ReutSubSeqCtl.Data);
    }
    **/
  }
}

/**
  Hook before normal mode is enabled.

  @param[in, out] MrcData  - The MRC "global data" area.

  @retval Nothing.
**/
void
MrcBeforeNormalModeTestMenu (
  IN OUT MrcParameters *const MrcData
  )
{
  return;
}

/**
  This function is used to calculate Vref or VSwing of a generic voltage divider.
  ReceiverOdt must be non-Zero, or exceptions occurs.
  VSS, the voltage level the PullDown is attached to, is assumed to be 0.

  @param[in]  MrcData         - Pointer to global data structure.
  @param[in]  DriverPullUp    - Used to calculate Vhigh.  Value in Ohms.
  @param[in]  DriverPullDown  - Used to calculate Vlow.  Value in Ohms.
  @param[in]  ReceiverOdt     - Value in Ohms.
  @param[in]  Vdd             - Voltage level PullUp is tied to.  Must be the same unit size as Vtermination.
  @param[in]  Vtermination    - Voltage level ReceiverOdt is tied to.  Must be the same unit size as Vdd.
  @param[in]  IsVref          - Boolean to select Vref or Vswing calculation.

  @retval - Vref in units of Vdd/Vterm
**/
UINT32
MrcCalcGenericVrefOrSwing (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                DriverPullUp,
  IN  UINT32                DriverPullDown,
  IN  UINT32                ReceiverOdt,
  IN  UINT32                Vdd,
  IN  UINT32                Vtermination,
  IN  BOOLEAN               IsVref
  )
{
  MrcDebug  *Debug;
  UINT32  Vhigh;
  UINT32  Vlow;
  UINT32  Result;
  UINT32  Numerator;
  UINT32  Denominator;

  Debug = &MrcData->Outputs.Debug;

  Numerator   = ReceiverOdt;
  Denominator = DriverPullUp + ReceiverOdt;
  MRC_DEBUG_ASSERT (Denominator != 0, Debug, "Divide by 0!\n");
  //Vhigh = Vtermination + ((Vdd - Vtermination) * (ReceiverOdt / (DriverPullUp + ReceiverOdt)));
  Vhigh = (Vdd - Vtermination) * Numerator;
  Vhigh = UDIVIDEROUND (Vhigh, Denominator) + Vtermination;
  Numerator   = DriverPullDown;
  Denominator = ReceiverOdt + DriverPullDown;
  MRC_DEBUG_ASSERT (Denominator != 0, Debug, "Divide by 0!\n");
  //Vlow  = Vtermination * (DriverPullDown / (DriverPullDown + ReceoverOdt))
  Vlow = Vtermination * Numerator;
  Vlow = UDIVIDEROUND (Vlow, Denominator);

  if (IsVref) {
    Result = (Vhigh + Vlow);
    if ((MrcData->Outputs.DdrType == MRC_DDR_TYPE_LPDDR4) && MrcData->Inputs.Lp4Npath) {
      Result = UDIVIDEROUND (Result * 7, 10);
    } else {
      Result = UDIVIDEROUND (Result, 2);
    }
  } else {
    Result = Vhigh - Vlow;
  }

  return Result;
}

/**
  This function is used to gather current system parameters to pass to the function,
  which calculates the ideal Read/Write/Command Vref.  It will return the result to the caller.

  @param[in]  MrcData         - Pointer to global data structure.
  @param[in]  DriverPullUp    - Used to calculate Vhigh.  Value in Ohms.
  @param[in]  DriverPullDown  - Used to calculate Vlow.  Value in Ohms.
  @param[in]  ReceiverOdt     - Value in Ohms.
  @param[in]  VrefType        - MRC_MarginTypes: WrV, CmdV, RdV.
  @param[in]  Print           - Boolean switch to print the results and parameters.

  @retval - Vref in units of mV
**/
UINT32
MrcCalcIdealVref (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                DriverPullUp,
  IN  UINT32                DriverPullDown,
  IN  UINT32                ReceiverOdt,
  IN  MRC_MarginTypes       VrefType,
  IN  BOOLEAN               Print
  )
{
  MrcInput    *Inputs;
  MrcOutput   *Outputs;
  MrcDebug    *Debug;
  MrcDdrType  DdrType;
  MRC_ODT_MODE_TYPE OdtMode;
  UINT32      Vref;
  UINT32      Vdd;
  UINT32      Vss;
  UINT32      Vterm;
  BOOLEAN     Lpddr4;
  BOOLEAN     VddDiv2;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  DdrType = Outputs->DdrType;
  OdtMode = Outputs->OdtMode;
  Lpddr4  = (DdrType == MRC_DDR_TYPE_LPDDR4);
  VddDiv2 = ((VrefType == RdV) && ((OdtMode == MrcOdtModeVtt) || (OdtMode == MrcOdtModeCtt)));

  if (VrefType != WrV && VrefType != CmdV && VrefType != RdV) {
    MRC_DEBUG_ASSERT (1==0, Debug, "%s MrcCalcIdealRxVref - Invalid VrefType: %d\n", gErrString, VrefType);
    return 0;
  }

  Vdd   = Outputs->VddVoltage[Inputs->MemoryProfile];
  Vss   = 0;
  Vterm = MRC_UINT32_MAX;
  Vref  = MRC_UINT32_MAX;

  if (VddDiv2) {
    // True for DDR3, DDR4, LPDDR3, and LPDDR4
    Vref = Vdd / 2;
  } else {
    if (VrefType == WrV) {
      if (Lpddr4) {
        Vdd = VDD_1_10;
        if (Inputs->LowSupplyEnData) {
          Vdd = Inputs->VccIomV;
        }
      }
    } else if (VrefType == CmdV) {
      // Command Vref
      if (Lpddr4) {
        Vdd = VDD_1_10;
        if (Inputs->LowSupplyEnCcc) {
          Vdd = Inputs->VccIomV;
        }
      }
    }

    // Setup PullUp, PullDown, Vterm,
    switch (DdrType) {
      case MRC_DDR_TYPE_DDR4:
        Vterm = Vdd;
        break;

      case MRC_DDR_TYPE_LPDDR4:
        Vterm = Vss;
        break;

      default:
        MRC_DEBUG_ASSERT (FALSE, Debug, "Unsupported DRAM Type and Odt Mode: %d, %s\n", DdrType, gIoOdtModeStr[OdtMode]);
        return Vref;
    }

    Vref = MrcCalcGenericVrefOrSwing (MrcData, DriverPullUp, DriverPullDown, ReceiverOdt, Vdd, Vterm, TRUE);
  }

  if (Print) {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "DriverPullUp = %u, DriverPullDown = %u, ReceiverOdt = %u, ",
      DriverPullUp,
      DriverPullDown,
      ReceiverOdt
      );
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "Vdd = %u, Vterm = %u VrefType = %s, Vref = %u mV\n",
      Vdd,
      Vterm,
      gMarginTypesStr[VrefType],
      Vref
      );
  }

  return Vref;
}

/**
  This function will program the ideal Rx Vref to all the bytes in the Channel.
  Channel here denotes a 64-bit bus.  It will not program Bytes that aren't present,
  in the case of Sub-Channels.

  It has two phases:
    Calculate Vref based on parameters passed to the function.
    Encode the Vref calculated into the CPU register format and program the register.

  Two parameters are determined inside the function stack:
    Vdd,
    Vtermination

  @param[in]  MrcData   - Pointer to MRC global data.
  @param[in]  Channel   - Channel to program.
  @param[in]  PrintMsg  - Boolean switch to enable debug printing.

  @retval none
**/
VOID
MrcSetIdealRxVref (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                Channel,
  IN  UINT32                DriverPullUp,
  IN  UINT32                DriverPullDown,
  IN  UINT32                ReceiverOdt,
  IN BOOLEAN                PrintMsg
  )
{
  INT64   GetSetVref;
  UINT32  Vref;
  UINT32  Mode;

  Mode = WriteCached;
#ifdef MRC_DEBUG_PRINT
  if (PrintMsg) {
    Mode |= PrintValue;
  }
#endif // MRC_DEBUG_PRINT

  Vref = MrcCalcIdealVref (MrcData, DriverPullUp, DriverPullDown, ReceiverOdt, RdV, PrintMsg);

  MrcEncodeRxVref (MrcData, Vref, &GetSetVref);

  MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, MAX_SDRAM_IN_DIMM, RxVref, Mode, &GetSetVref);
}

/**
  Set ideal CPU Read Vref for DDR4.

  @param[in, out] MrcData - Include all MRC global data.
  @param[in]      DimmRon - DIMM Ron value in Ohm
  @param[in]      CpuOdt - CPU Read ODT value in Ohm
  @param[in]      PrintMsg - enable debug prints

  @retval none
**/
void
MrcSetIdealRxVrefDdr4 (
  IN OUT MrcParameters *const MrcData,
  IN UINT8                    Channel,
  IN UINT32                   DimmRon,
  IN UINT32                   CpuOdt,
  IN BOOLEAN                  PrintMsg
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcVddSelect      Vdd;
  INT64             GetSetVal;
  INT64             RxVrefMinValue;
  INT64             RxVrefMaxValue;
  INT32             RxVrefVal;
  INT64             RxVrefCode;
  UINT32            GsMode;
  MRC_ODT_MODE_TYPE OdtMode;

  Inputs            = &MrcData->Inputs;
  Outputs           = &MrcData->Outputs;
  Debug             = &Outputs->Debug;

  OdtMode = Outputs->OdtMode;
  Vdd     = Outputs->VddVoltage[Inputs->MemoryProfile];
  GsMode  = WriteCached;
  if (PrintMsg) {
    GsMode |= PrintValue;
  }

  if ((OdtMode == MrcOdtModeVtt) || (OdtMode == MrcOdtModeCtt)) {
    // in Ctt/Vtt Odt modes the ideal Vref is Vdd/2.
    RxVrefVal = Vdd / 2;
    MrcGetSetLimits (MrcData, RxVref, &RxVrefMinValue, &RxVrefMaxValue, NULL);
    RxVrefCode = RxVrefMinValue + RxVrefMaxValue;
    RxVrefCode = UDIVIDEROUND ((INT32) RxVrefCode, 2);
  } else if (OdtMode == MrcOdtModeVddq) {
    // (Vdd * (2 * DimmRon + DqOdt) / (DimmRon + DqOdt) / 2 - 0.75 * Vdd) * 192 / Vdd
    RxVrefVal = (Vdd * (2 * DimmRon + CpuOdt)) / (DimmRon + CpuOdt) / 2;
    RxVrefCode = UDIVIDEROUND (RxVrefVal * 192, Vdd);
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s: unsupported ODT type for DDR4: %u\n", gErrString, OdtMode);
    return;
  }
  GetSetVal  = RxVrefCode;
  if (PrintMsg) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CPU Odt = %d DimmRon = %d CPU Read Vref = %dmV\n", CpuOdt, DimmRon, RxVrefVal);
  }

  // Set all the bytes with the ideal value.
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, MAX_SDRAM_IN_DIMM, RxVref, GsMode, &GetSetVal);
}

/**
  Set default CPU Read Vref for DDR4 assuming CPU uses Vddq termination.
  Use default CPU ODT and DIMM Ron values.

  @param[in, out] MrcData      - Include all MRC global data.
  @param[in]      GetFromTable - Get the DIMM ODT parameters from the initial table.
  @param[in]      PrintMsg     - Enable debug prints

  @retval none
**/
void
MrcSetDefaultRxVrefDdr4 (
  IN OUT MrcParameters *const MrcData,
  IN     BOOLEAN         GetFromTable,
  IN     BOOLEAN         PrintMsg
  )
{
  const MrcInput    *Inputs;
  MrcOutput         *Outputs;
  MrcChannelOut     *ChannelOut;
  UINT32            EquOdt;
  UINT32            OdtTarget;
  UINT32            EffODT;
  UINT8             NumRanks;
  UINT8             Channel;
  UINT8             Rank;
  UINT8             Dimm;
  UINT8             SerialR;
  BOOLEAN           is2R;
  UINT8             RankInDimm;

  Inputs            = &MrcData->Inputs;
  Outputs           = &MrcData->Outputs;
  SerialR           = 15; // Ohm

  OdtTarget = Inputs->RcompTarget[RdOdt];
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(MrcChannelExist(Outputs, Channel))) {
      continue;
    }
    ChannelOut        = &Outputs->Controller[0].Channel[Channel];
    EffODT            = 0;
    NumRanks          = 0;
    is2R              = FALSE; // when 2R is detected
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        Dimm = RANK_TO_DIMM_NUMBER (Rank);
        RankInDimm = ChannelOut->Dimm[Dimm].RankInDimm;
        if ((!is2R) && (Dimm == 1) && (RankInDimm == 2)) {
          // If first DIMM is 1R and second DIMM is 2R, take into account only the 2R DIMM
          EffODT = 0;
          NumRanks = 0;
        }
        if ((RankInDimm == 1) && is2R) {
          // take into account only the 2R
          break;
        }
        EffODT += MrcGetEffDimmWriteOdt (MrcData, Channel, Rank, 1, GetFromTable);
        NumRanks++;
        if (RankInDimm == 2) {
          is2R = TRUE;
        }
      }
    }
    if (NumRanks > 0 ) {
      EffODT /= NumRanks;
    }

    EquOdt = OdtTarget *  EffODT / (OdtTarget + EffODT);

    MrcSetIdealRxVrefDdr4 (MrcData, Channel, INIT_DIMM_RON_34 + SerialR, EquOdt, PrintMsg); // DIMM Ron = RZQ/7 = 34
  } // channel loop
}

/**
  Set ideal Dimm Write Vref for DDR4 assuming CPU Ron and Dimm termination.

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in]      Channel     - Channel to setup
  @param[in]      RankBitMask - Rank bit mask to setup
  @param[in]      Byte        - Byte to setup (for PDA mode only)
  @param[in]      CpuRon      - CPU Ron value in Ohm
  @param[in]      OdtWr       - Write DIMM Odt value in Ohm
  @param[in]      DimmOdt     - Equ. DIMM Odt value in Ohm

  @retval none
**/
void
MrcSetIdealTxVrefDdr4 (
  IN OUT MrcParameters *const MrcData,
  UINT8                       Channel,
  UINT8                       RankBitMask,
  UINT8                       Byte,
  UINT32                      CpuRon,
  UINT32                      OdtWr,
  UINT32                      DimmOdt
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  UINT8             Rank;
  INT32             TxVrefMid;
  INT32             TxVref;
  INT32             TxVrefCode;
  MrcVddSelect      Vdd;
  UINT8             SerialR;

  Inputs            = &MrcData->Inputs;
  Outputs           = &MrcData->Outputs;
  Debug             = &Outputs->Debug;
  SerialR           = 15; // Ohm

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CpuRon = %d, OdtWr = %d, DimmOdt = %d\n", CpuRon, OdtWr, DimmOdt);
  Vdd = Outputs->VddVoltage[Inputs->MemoryProfile];
  TxVrefMid = (Vdd * (2 * CpuRon + DimmOdt)) / (CpuRon + DimmOdt) / 2;
  TxVref = (Vdd * SerialR + TxVrefMid * OdtWr) / (SerialR + OdtWr);
  TxVref *= 1000; // convert to uV
  TxVrefCode = DIVIDEROUND (TxVref - 1000 * DDR4_VREF_MIDDLE_RANGE, DDR4_VREF_STEP_SIZE);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Dimm Write Vref = %dmV, TxVref Code = %d\n", TxVref / 1000, TxVrefCode);

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (!(MrcRankInChannelExist (MrcData, Rank, Channel) & RankBitMask)) {
      continue;
    }
    MrcSetTxVrefDdr4 (MrcData, Channel, Rank, 0, TxVrefCode, TRUE, FALSE);
  } // for Rank
}

/**
  Set default Tx Dimm Vref for DDR4.
  Use default CPU Ron and DIMM Write Odt values.

  @param[in, out] MrcData - Include all MRC global data.

  @retval none
**/
void
MrcSetDefaultTxVrefDdr4 (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcOutput         *Outputs;
  UINT8             Channel;
  UINT8             Rank;
  UINT32            EffODT;
  UINT32            OdtWr;

  Outputs           = &MrcData->Outputs;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(MrcChannelExist (Outputs, Channel))) {
      continue;
    }
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (MrcRankInChannelExist (MrcData, Rank , Channel)) {
        EffODT = MrcGetEffDimmWriteOdt(MrcData, Channel, Rank, 0, FALSE); // GetFromTable = FALSE because we already programmed the MR's
        OdtWr = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmOdtWr, FALSE, 0, FALSE);
        OdtWr = (OdtWr == 0) ? 0xFFFF : OdtWr;
        MrcSetIdealTxVrefDdr4 (MrcData, Channel, 0x1 << Rank, 0, MrcData->Inputs.RcompTarget[WrDS], OdtWr, EffODT);
      }
    }
  } // channel loop
}


/**
  Returns the effective Dimm Write ODT.
  Consider the DRAM tech, Rtt configuration (Wr, Nom, Park) and Normal Odt logic.
  Note: We still have the assumption of same Rtt's for all ranks in the same DIMM.

  @param[in, out] MrcData - Include all MRC global data.
  @param[in] Channel      - Channel to setup
  @param[in] Rank         - Rank to setup
  @param[in] OdtType      - 0:write 1:read
  @param[in] GetFromTable - Get the Values from Odt tables

  @retval value in ohms
**/
UINT16
MrcGetEffDimmWriteOdt (
  IN OUT MrcParameters *const MrcData,
  UINT8                       Channel,
  UINT8                       Rank,
  UINT8                       OdtType,
  BOOLEAN                     GetFromTable
  )
{
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  UINT32            OdtWr;
  UINT32            OdtNom;
  UINT32            OdtNom1;
  UINT32            OdtPark;
  UINT32            OdtPark1;
  BOOLEAN           Ddr4;
  BOOLEAN           Is2DPC;
  UINT32            RttT;
  UINT32            RttNT;
  UINT32            EffOdt;
  UINT8             Dimm;
  UINT8             OtherDimm;
  UINT8             SerialR;

  Outputs           = &MrcData->Outputs;
  ControllerOut     = &Outputs->Controller[0];
  ChannelOut        = &ControllerOut->Channel[Channel];
  // @todo: <CNL> This doesn't exist in Memory Down.
  SerialR           = 15; // Ohm resistor on the dimm card

  Is2DPC = (ChannelOut->DimmCount == 2);
  Ddr4 = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Dimm = RANK_TO_DIMM_NUMBER (Rank);
  OtherDimm = (Dimm ^ 1) & 1;
  OdtPark = OdtPark1 = 0xFFFF;
  OdtNom  = OdtNom1  = 0xFFFF;

  OdtWr  = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmOdtWr, FALSE, 0, GetFromTable);

  if (Ddr4) {
    OdtNom = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmOdtNom, FALSE, 0, GetFromTable);
    OdtPark = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmOdtPark, FALSE, 0, GetFromTable);
    if (Is2DPC) {
      OdtNom1 = CalcDimmImpedance (MrcData, Channel, 2 * OtherDimm, OptDimmOdtNom, FALSE, 0, GetFromTable);
      OdtPark1 = CalcDimmImpedance (MrcData, Channel, 2 * OtherDimm, OptDimmOdtPark, FALSE, 0, GetFromTable);
    }
  }
  // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel = %d OdtWr = %d, OdtNom = %d OdtPark = %d\n", Channel, OdtWr, OdtNom, OdtPark);
  // Add the serial resistor and protect clip at 16k to not overflow when mul
  OdtWr     = (OdtWr == 0) ? 0 : OdtWr + SerialR;
  OdtNom    = MIN((OdtNom + SerialR), 0xFFFF);
  OdtNom1   = MIN((OdtNom1 + SerialR), 0xFFFF);
  OdtPark   = MIN((OdtPark + SerialR), 0xFFFF);
  OdtPark1  = MIN((OdtPark1 + SerialR), 0xFFFF);
  // Check that in DDR4 the mc toggles odt pin for the target rank for write.
  if (Ddr4) {
    RttT = (OdtWr == 0) ? 0xFFFF : OdtWr;
  } else {
    RttT = (OdtWr == 0) ? OdtNom : OdtWr;
  }

  // calc the effective park value
  if (Ddr4) {
    if (ChannelOut->Dimm[Dimm].RankInDimm == 1) {
      OdtPark = 0xFFFF;
    }
    if (Is2DPC) {
      // in 1R we will have only Rtt nom
      if (ChannelOut->Dimm[OtherDimm].RankInDimm == 2) {
        OdtPark = DIVIDEROUND (OdtPark * OdtPark1, OdtPark + OdtPark1);
      }
    }
  }

  // calc the effective NT value
  if (Is2DPC) {
    RttNT =  (Ddr4) ? DIVIDEROUND (OdtPark * OdtNom1, OdtPark + OdtNom1) : OdtNom1;
  } else {
    RttNT = (Ddr4) ? OdtPark : 0xFFFF;
  }

  if (OdtType == 0) { // Write - Target Equivalent Rtt
    EffOdt = DIVIDEROUND (RttT * RttNT, RttT + RttNT);
  } else { // Read - NonTarget Equivalent Rtt
    EffOdt = RttNT;
  }
  return (UINT16) EffOdt;
}

/**
  Generic routine to perform Linear Centering in different 2D points.
  Re-uses DQTimeCentering1D routine as the linear centering routine.
  Optimize Per channel in the 2D param space.
  Run-Time - about 20nsec for 6 vref points and loopcout of 10

  @param[in,out] MrcData        - Include all MRC global data.
  @param[in]     ChBitMask      - Channels to test.
  @param[in]     RankBitMask    - Ranks to test.
  @param[in]     Param          - Param to center with linear search - use DQTimeCentering1D (RdT,WrT,WrV,RdV,RcvX)
  @param[in]     Param2D        - The 2D Param to Offset - Use change margin routine
  @param[in]     Points2DMin    - Minimum value of second dimension points to sweep.
  @param[in]     Points2DMax    - Maxmimum value of second dimension points to sweep.
  @param[in]     ParamStepSize  - Step size of second dimension points to sweep.
  @param[in]     LoopCount      - Loop count
  @param[in]     TestType       - 0: normal reads, 1: Read MPR
  @param[in]     Prints         - Debug prints enable/disable

  @retval MrcStatus - mrcSuccess if passed, otherwise an error status.
**/
MrcStatus
EarlyLinearCentering2D (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                ChBitMask,
  IN     UINT8                RankBitMask,
  IN     UINT8                Param,
  IN     UINT8                Param2D,
  IN     INT16                Points2DMin,
  IN     INT16                Points2DMax,
  IN     UINT8                ParamStepSize,
  IN     UINT8                LoopCount,
  IN     UINT8                TestType,
  IN     BOOLEAN              Prints
  )
{
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  const MRC_FUNCTION  *MrcCall;
  MrcOutput           *Outputs;
  MrcControllerOut    *ControllerOut;
  MrcChannelOut       *ChannelOut;
  MrcStatus           Status;
  UINT32              (*MarginByte)[MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  INT64               GetSetVal;
  INT16               Idx;
  INT16               Best2DPointPerCh[MAX_CHANNEL];
  UINT16              Best1DEyePerCh[MAX_CHANNEL];
  UINT16              MinEyePerCh[MAX_CHANNEL];
  INT16               Best2DPoint[MAX_SDRAM_IN_DIMM][MAX_PHY_CHANNEL];
  UINT16              Best1DEye[MAX_SDRAM_IN_DIMM][MAX_PHY_CHANNEL];
  UINT16              MinEye[MAX_SDRAM_IN_DIMM][MAX_PHY_CHANNEL];
  UINT16              EyeSize;
  UINT8               ResultType;
  UINT8               Channel;
  UINT8               Rank;
  UINT8               Byte;
  UINT8               ByteStart;
  UINT8               ByteEnd;
  UINT8               SubCh;
  UINT8               SubChStop;
  UINT8               ChRankMask;
  UINT8               PhyChIndex;
  UINT8               MinRank[MAX_SDRAM_IN_DIMM][MAX_PHY_CHANNEL];
  UINT8               BestRank[MAX_SDRAM_IN_DIMM][MAX_PHY_CHANNEL];
  INT16               PassVrefTotal[MAX_SDRAM_IN_DIMM][MAX_PHY_CHANNEL];
  INT16               PassVrefCount[MAX_SDRAM_IN_DIMM][MAX_PHY_CHANNEL];
  UINT16              PassWidth;
  INT8                RdMprDqsStepInc;
  UINT8               Vref;
  BOOLEAN             Ddr4;
  BOOLEAN             EnhancedChannelMode;

  Inputs              = &MrcData->Inputs;
  MrcCall             = Inputs->Call.Func;
  Outputs             = &MrcData->Outputs;
  Debug               = Prints ? &Outputs->Debug : NULL;
  Status              = mrcSuccess;
  Ddr4                = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  ControllerOut       = &Outputs->Controller[0];
  MarginByte          = Outputs->MarginResult;
  EnhancedChannelMode = Outputs->EnhancedChannelMode;
  SubChStop           = ((EnhancedChannelMode) && Outputs->ValidSubChMask == 0x3) ? 2 : 1;
  RdMprDqsStepInc = 2;
  MrcCall->MrcSetMemWord ((UINT16 *) Best1DEye, sizeof (Best1DEye) / sizeof (Best1DEye[0][0]), 0);
  MrcCall->MrcSetMemWord ((UINT16 *) Best2DPoint, sizeof (Best2DPoint)  / sizeof (Best2DPoint[0][0]), Points2DMin);
  MrcCall->MrcSetMemWord ((UINT16 *) Best1DEyePerCh, ARRAY_COUNT (Best1DEyePerCh), 0);
  MrcCall->MrcSetMemWord ((UINT16 *) Best2DPointPerCh, ARRAY_COUNT (Best2DPointPerCh), Points2DMin);
  MrcCall->MrcSetMemWord ((UINT16 *) PassVrefTotal, sizeof (PassVrefTotal) / sizeof (PassVrefTotal[0][0]), 0);
  MrcCall->MrcSetMemWord ((UINT16 *) PassVrefCount, sizeof (PassVrefCount) / sizeof (PassVrefCount[0][0]), 0);
  MrcCall->MrcSetMem((UINT8 *) BestRank, sizeof(BestRank), 0);
  PassWidth = 560;    // This is a minimum margin to be cosidered as PASS for RdV center calculation (28 ticks each side)

  MRC_DEBUG_ASSERT (Points2DMin < Points2DMax, Debug, "%s: Invalid Parameters, Points2DMin(%d) and Points2DMax(%d)\n", gErrString, Points2DMin, Points2DMax);
  MRC_DEBUG_ASSERT (((TestType == ERTC2D_NORMAL) || (TestType == ERTC2D_MPR)), Debug,"%s invalid TestType requested: %d\n", gErrString, TestType);

  // ####################################################
  // ################  Initialize EW/EH variables  ######
  // ####################################################

#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n### Measure Eye Width, per BYTE, at ALL (2D) Timing Points - RankBitMask = 0x%X\n", RankBitMask);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Vref Sweep Range [%d:%d] and Step Size of %d\n", Points2DMin, Points2DMax, ParamStepSize);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tChannel %d", Channel);
    for (Byte = 0; Byte < Outputs->SdramCount - 2; Byte++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nByte\t");
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", Byte);
    }
  }
#endif // MRC_DEBUG_PRINT

  Status      = GetMarginByte (MrcData, Outputs->MarginResult, Param, 0, RankBitMask);
  ResultType  = GetMarginResultType (Param);

  if ((Param2D == WrV) || (Param2D == CmdV)) {
    // Write Vref - program to middle (zero offset) range before sweep
    if (Ddr4 && (Param2D == CmdV)) {
      Vref = MID_INT_VREF;
    } else {
      //  Lpddr4 CmdV, WrV ; Ddr4 WrV
      Vref = 0;
    }
    MrcUpdateVref (MrcData, ChBitMask, RankBitMask, 0, Param2D, Vref, TRUE, FALSE, FALSE, FALSE);
  }

  // ####################################################
  // ######   Measure Eye Width at all Vref Points  #####
  // ####################################################
  // Loop through all the 2D Points to Test
  for (Idx = Points2DMin; Idx <= Points2DMax; Idx+=ParamStepSize) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\nVref: %d\t", Idx);

    // Setup 2D Offset for this point
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(ChBitMask & (MRC_BIT0 << Channel))) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      ChRankMask = RankBitMask & ChannelOut->ValidRankBitMask;
      if (ChRankMask == 0) {
        continue;
      }
      if (Param2D == RdV) {
        for (SubCh = 0; SubCh < SubChStop; SubCh++) {
          if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
            continue;
          }
          if (EnhancedChannelMode) {
            ByteStart = ChannelOut->ByteStart[SubCh];
            ByteEnd   = ChannelOut->ByteEnd[SubCh];
          } else {
            ByteStart = 0;
            ByteEnd = Outputs->SdramCount - 1;
          }

          for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
            if (!((1 << Rank) & ChRankMask)) {
              continue;
            }
            GetSetVal = Idx;
            for (Byte = ByteStart; Byte <= ByteEnd; Byte++) {
              MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RxVref, WriteCached, &GetSetVal);
            }
          }
        }
      } else {
        Status = ChangeMargin (MrcData, Param2D, Idx, 0, 0, Channel, (Ddr4 && (Param2D == WrV))? ChRankMask : 0xFF, 0, 0, 0, 0);
      }
    }

    // Run Param Margin Test
    if (TestType == ERTC2D_NORMAL) {
      Status = DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, Param, 0, LoopCount, FALSE, TRUE);
    } else if (TestType == ERTC2D_MPR) {
      if (Outputs->LpddrEctDone && Inputs->TrainingEnables.ECT) {
        Status = MrcReadMprTrainingNormal (MrcData, RdMprDqsStepInc, FALSE); // Call CPGC-based ReadMPR
      } else {
        Status = ReadMprTraining (MrcData, RankBitMask, RdMprDqsStepInc, FALSE); // Call HW-based ReadMPR as this is before Read Leveling
      }
    }

#ifdef MRC_DEBUG_PRINT
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if ((0x1 << Rank) & Outputs->ValidRankMask & RankBitMask) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nR%d L-R\t",Rank);
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t", Byte);
            }
          } else {
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                (MrcByteInChannelExist (MrcData, Channel, Byte)) ? "%d-%d\t" : "\t",
                MarginByte[ResultType][Rank][Channel][Byte][0] / 10,
                MarginByte[ResultType][Rank][Channel][Byte][1] / 10
                );
            }
          }
        }
      }
    }
#endif // MRC_DEBUG_PRINT

    // Store Results
    MrcCall->MrcSetMem ((UINT8 *) MinEye, sizeof (MinEye), 0xFF);
    MrcCall->MrcSetMem ((UINT8 *) MinEyePerCh, sizeof (MinEyePerCh), 0xFF);
    MrcCall->MrcSetMem ((UINT8 *) MinRank, sizeof (MinRank), 0xFF);
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if ((1 << Rank) & Outputs->ValidRankMask & RankBitMask) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
            continue;
          }
          ChannelOut = &ControllerOut->Channel[Channel];
          for (SubCh = 0; SubCh < SubChStop; SubCh++) {
            if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
              continue;
            }
            if (EnhancedChannelMode) {
              ByteStart = ChannelOut->ByteStart[SubCh];
              ByteEnd   = ChannelOut->ByteEnd[SubCh];
            } else {
              ByteStart = 0;
              ByteEnd = Outputs->SdramCount - 1;
            }
            PhyChIndex = (EnhancedChannelMode) ? (MAX_CHANNEL * Channel + SubCh) : Channel;

            for (Byte = ByteStart; Byte <= ByteEnd; Byte++) {
              EyeSize = (UINT16) (MarginByte[ResultType][Rank][Channel][Byte][1] + MarginByte[ResultType][Rank][Channel][Byte][0]);
              // Track minimum eye width per subch/byte
              if (MinEye[Byte][PhyChIndex] > EyeSize) {
                MinEye[Byte][PhyChIndex] = EyeSize;
                MinRank[Byte][PhyChIndex] = Rank;
              }
              // Track minimum eye width per channel
              if (MinEyePerCh[Channel] > EyeSize) {
                MinEyePerCh[Channel] = EyeSize;
              }
              if (EyeSize >= PassWidth) {
                PassVrefTotal[Byte][PhyChIndex] += Idx;
                PassVrefCount[Byte][PhyChIndex] += 1;
                // MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%d Phych%d B%d VrefTot:%d, VrefCount:%d\n", Channel, PhyChIndex, Byte, PassVrefTotal[Byte][PhyChIndex], PassVrefCount[Byte][PhyChIndex]);
              }
            } // for Byte
          } // for SubCh
        } // for Channel
      } // if Rank exists
    } // for Rank

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs,Channel)) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      for (SubCh = 0; SubCh < SubChStop; SubCh++) {
        if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
          continue;
        }
        if (EnhancedChannelMode) {
          ByteStart = ChannelOut->ByteStart[SubCh];
          ByteEnd = ChannelOut->ByteEnd[SubCh];
        } else {
          ByteStart = 0;
          ByteEnd = Outputs->SdramCount - 1;
        }
        PhyChIndex = (EnhancedChannelMode) ? (MAX_CHANNEL * Channel + SubCh) : Channel;

        for (Byte = ByteStart; Byte <= ByteEnd; Byte++) {
        // Track best eye in the 2D space
          if (Best1DEye[Byte][PhyChIndex] < MinEye[Byte][PhyChIndex]) {
            Best1DEye[Byte][PhyChIndex] = MinEye[Byte][PhyChIndex];
            BestRank[Byte][PhyChIndex] = MinRank[Byte][PhyChIndex];
            Best2DPoint[Byte][PhyChIndex] = Idx;
          }
        }
        // Track best eye in the 2D space per channel
        if (Best1DEyePerCh[Channel] < MinEyePerCh[Channel]) {
          Best2DPointPerCh[Channel] = Idx;
          Best1DEyePerCh[Channel] = MinEyePerCh[Channel];
        }
      } //for SubCh
    } // for Channel
  } // 2D Points
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  // ####################################################
  // ###########   Center Results per Byte   ############
  // ####################################################
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(ChBitMask & (MRC_BIT0 << Channel))) {
      continue;
    }
    ChannelOut = &ControllerOut->Channel[Channel];
    ChRankMask = RankBitMask & ChannelOut->ValidRankBitMask;
    if (ChRankMask == 0) {
      continue;
    }
    for (SubCh = 0; SubCh < SubChStop; SubCh++) {
      if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
        continue;
      }
      if ((SubCh > 0) && (Param2D != RdV)) {
        // LP4 WrV - same value is sent to both subch
        continue;
      }
      PhyChIndex = (EnhancedChannelMode) ? (MAX_CHANNEL * Channel + SubCh) : Channel;
      // Note: the Change margin will work only on non TrainOffset params like WrV, RcvEnX (if other needed use GetSet)
      if (Outputs->EnhancedChannelMode) {
        ByteStart = ChannelOut->ByteStart[SubCh];
        ByteEnd   = ChannelOut->ByteEnd[SubCh];
      } else {
        ByteStart = 0;
        ByteEnd = Outputs->SdramCount - 1;
      }

      if ((Param2D == WrV) && !Ddr4) { // LP4 WrV is per rank, we use the worst case value for both ranks
        ChangeMargin (MrcData, Param2D, Best2DPointPerCh[Channel], 0, 0, Channel, 0xFF, 0, 0, 1, 1);
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "\nChannel %d: Selected Vref <%d> Smallest eye width <%d>",
          Channel,
          Best2DPointPerCh[Channel],
          Best1DEyePerCh[Channel]
          );
      } else {
        for (Byte = ByteStart; Byte <= ByteEnd; Byte++) {
          GetSetVal = Best2DPoint[Byte][PhyChIndex];
          if (Param2D == RdV) {
            if (PassVrefCount[Byte][PhyChIndex] != 0) {
              // Calculate the middle of the passing RdV range
              GetSetVal = DIVIDEROUND (PassVrefTotal[Byte][PhyChIndex], PassVrefCount[Byte][PhyChIndex]);
            }
            MrcGetSetDdrIoGroupStrobe(MrcData, Channel, MRC_IGNORE_ARG, Byte, RxVref, WriteToCache, &GetSetVal);
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nChannel %d: Byte %d: Selected Vref <%d>", PhyChIndex, Byte, (INT32) GetSetVal);
          } else { // WrV
            ChangeMargin (MrcData, Param2D, Best2DPoint[Byte][PhyChIndex], 0, 0, Channel, (Ddr4 && (Param2D == WrV)) ? ChRankMask : 0xFF, (Ddr4 && (Param2D == WrV)) ? 1 << Byte : Byte, 0, 1, 1);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "\nChannel %d: Byte %d: Selected Vref <%d>  Smallest eye width <%d> found at Rank %d",
              PhyChIndex,
              Byte,
              Best2DPoint[Byte][PhyChIndex],
              Best1DEye[Byte][PhyChIndex],
              BestRank[Byte][PhyChIndex]
              );
          }
        } // for Byte
      } // not LP4 WrV
    } // for SubCh
  } // for Channel
  MrcFlushRegisterCachedData (MrcData);  // Flush updated results to the registers.

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  // final centering at best offset
  if (TestType == ERTC2D_NORMAL) {
    Status = DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, Param, 0, LoopCount, FALSE, TRUE);
  } else if (TestType == ERTC2D_MPR) {
    if (Outputs->LpddrEctDone && Inputs->TrainingEnables.ECT) {
      Status = MrcReadMprTrainingNormal (MrcData, RdMprDqsStepInc, TRUE); // CPGC-based
    } else {
      Status = ReadMprTraining (MrcData, RankBitMask, RdMprDqsStepInc, TRUE); // HW-based
    }
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Final centering at best vref %s\n", (Status == mrcSuccess) ? "Passed" : "Failed");

  return Status;
}

/**
  Set ODT Logic behavior for DDR4.

  @param[in, out] MrcData - Include all MRC global data.
  @param[in]      Profile - Behavior type. Currently Profile 1 is supported (DDR3-like)

  @retval none
**/
void
MrcSetOdtMatrix (
  IN OUT MrcParameters *const MrcData,
  IN UINT8                    Profile
  )
{
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  INT64             EnableOdtMatrix;
  UINT32            Offset;
  UINT8             Channel;
  UINT8             Dimm;
  CH0_CR_SC_ODT_MATRIX_STRUCT  OdtMatrix;

  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];
  Debug         = &Outputs->Debug;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    ChannelOut = &ControllerOut->Channel[Channel];
    OdtMatrix.Data = 0;
    switch (Profile) {
      case 1:
        // DDR3 like behavior: put OdtNom on rank 0 of the other DIMM
        // DDR4 difference is that ODT pin is not asserted on the target rank
        if (ChannelOut->DimmCount == 2) {
          OdtMatrix.Bits.Write_Rank_0 = 0x4;
          OdtMatrix.Bits.Write_Rank_1 = 0x4;
          OdtMatrix.Bits.Write_Rank_2 = 0x1;
          OdtMatrix.Bits.Write_Rank_3 = 0x1;
          OdtMatrix.Bits.Read_Rank_0  = 0x4;
          OdtMatrix.Bits.Read_Rank_1  = 0x4;
          OdtMatrix.Bits.Read_Rank_2  = 0x1;
          OdtMatrix.Bits.Read_Rank_3  = 0x1;
        } else {
          for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
            if (ChannelOut->Dimm[Dimm].RankInDimm > 1) {
              if (Dimm == 0) {
                OdtMatrix.Bits.Write_Rank_0 = 0x1;
                OdtMatrix.Bits.Write_Rank_1 = 0x2;
              } else {
                OdtMatrix.Bits.Write_Rank_2 = 0x4;
                OdtMatrix.Bits.Write_Rank_3 = 0x8;
              }
            }
          }
        }
        break;
      case 0:
        // set odt pins to zero.
        break;
      default:
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "MrcSetOdtMatrix : Unknown Odt Matrix Profile\n");
        break;
    } // switch Profile
    Offset = OFFSET_CALC_CH (CH0_CR_SC_ODT_MATRIX_REG, CH1_CR_SC_ODT_MATRIX_REG, Channel);
    MrcWriteCR (MrcData, Offset, OdtMatrix.Data);

    EnableOdtMatrix = 1;
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccEnableOdtMatrix, WriteCached, &EnableOdtMatrix);
  } // for Channel
}

/**
  Get the Other Dimm in Channel.

  @param[in, out] MrcData  - Include all MRC global data.
  @param[in]      Channel  - Channel to search in.
  @param[in]      RankMask - Rank mask for the current DIMM.

  @retval The other Dimm outside the RankMask.  If no such DIMM, then return current DIMM.
**/
UINT8
MrcGetOtherDimm (
  IN MrcParameters *const MrcData,
  IN UINT8                Channel,
  IN UINT8                RankMask
  )
{
  UINT8 Dimm;
  UINT8 CurrentDimm;
  UINT8 OtherDimm;
  UINT8 ChannelRankMask;

  ChannelRankMask = MrcData->Outputs.Controller[0].Channel[Channel].ValidRankBitMask;
  CurrentDimm    = (RankMask & 0x3) ? 0 : 1;

  OtherDimm = CurrentDimm;
  for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
    if (Dimm == CurrentDimm) {
      continue;
    } else {
      if (DIMM_TO_RANK_MASK (Dimm) & ChannelRankMask) {
        OtherDimm = Dimm;
        break;
      }
    }
  }

  return OtherDimm;
}

/**
  Get the maximal possible offset for a given Timing Param (e.g., WrT, RdT) and DDR technology.

  @param[in]      MrcData  - Include all MRC global data.
  @param[in]      Param    - Parameter to get the max possible offset for.

  @retval The maximal possible offset
**/
UINT8
GetMaxPossibleTimingOffset (
  IN MrcParameters *const MrcData,
  IN UINT8                Param
  )
{
  MrcOutput   *Outputs;
  UINT8       MaxMargin;

  Outputs = &MrcData->Outputs;

  if (((Param == RdT) || (Param == RdTN) || (Param == RdTP)) && Outputs->Gear2) {
    MaxMargin = MAX_POSSIBLE_TIME_G2;
  } else {
    MaxMargin = MAX_POSSIBLE_TIME;
  }

  return MaxMargin;
}

/**
  Get the maximal possible offset for a given Param (e.g., WrV, RdV) and DDR technology.

  @param[in]      MrcData  - Include all MRC global data.
  @param[in]      Param    - Parameter to get the max possible offset for.

  @retval the maximal possible offset.
**/
UINT8
GetMaxPossibleVrefOffset (
  IN MrcParameters *const MrcData,
  IN UINT8                param
  )
{
  MrcOutput        *Outputs;
  MrcDebug         *Debug;
  BOOLEAN          Ddr4;
  BOOLEAN          Lpddr4;
  UINT8            MaxMargin;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Ddr4    = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr4  = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);

  switch (param) {
    case RdV:
    case RdFan2:
    case RdFan3:
      // RdV suplied by CPU, identical for all technologies
      MaxMargin = MAX_RX_VREF_OFFSET;
      break;

    case WrV:
    case WrFan2:
    case WrFan3:
      // WrV technology dependent
      if (Ddr4) {
        MaxMargin = MAX_POSSIBLE_DDR4_WRITE_VREF;
      } else { // LPDDR4
        MaxMargin = MRC_LP4_VREF_OFFSET_MAX;
      }
      break;

    case CmdV:
      // CmdV technology dependent
      if (Lpddr4) {
        MaxMargin = MRC_LP4_VREF_OFFSET_MAX;
      } else { // DDR4
        MaxMargin = MAX_DDR4_CMD_VREF_OFFSET;
      }
      break;

    default:
      // Unknown input param
      MaxMargin = 0;
      MRC_DEBUG_MSG(Debug, MSG_LEVEL_WARNING, "Warning unexpected param %d in GetMaxPossibleVrefOffset\n", MaxMargin);
      break;
  }

  return MaxMargin;
}

/**
  Relax RDRD same rank turnarounds on all channels.
  Used during early write training steps to avoid stressing reads.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Relax   - TRUE: relax the TAT values, FALSE: restore original values.
**/
void
MrcRelaxReadToReadSameRank (
  IN  MrcParameters *const MrcData,
  IN BOOLEAN               Relax
  )
{
  UINT32  Channel;
  UINT32  Mode;
  INT64   GetSetVal;

  if (Relax) {
    // Read from HW register, then write to HW register without updating the cache (assumes there is an original value already in the cache)
    GetSetVal = 32;
    Mode = ReadForceWriteNoCache | PrintValue;
  } else {
    // Add zero offset to the cached value - basically restore the cached value to the HW
    GetSetVal = 0;
    Mode = ForceWriteOffsetUncached | PrintValue;
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (&MrcData->Outputs, Channel)) {
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDsg, Mode, &GetSetVal);
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdg, Mode, &GetSetVal);
      // Must update the XARB bubble injector when TAT values change
      SetTcBubbleInjector (MrcData, Channel);
    }
  }
}

/**
  Relax WRWR same rank turnarounds on all channels.
  Used during early Read training steps to avoid stressing Writes.

  @param[in] MrcData - Include all MRC global data.
  @param[in] Relax   - TRUE: relax the TAT values, FALSE: restore original values.
**/
void
MrcRelaxWriteToWriteSameRank (
  IN  MrcParameters *const MrcData,
  IN BOOLEAN               Relax
  )
{
  UINT32  Channel;
  UINT32  Mode;
  INT64   GetSetVal;

  if (Relax) {
    // Read from HW register, then write to HW register without updating the cache (assumes there is an original value already in the cache)
    GetSetVal = 32;
    Mode = ReadForceWriteNoCache | PrintValue;
  } else {
    // Add zero offset to the cached value - basically restore the cached value to the HW
    GetSetVal = 0;
    Mode = ForceWriteOffsetUncached | PrintValue;
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (&MrcData->Outputs, Channel)) {
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRWRsg, Mode, &GetSetVal);
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRWRdg, Mode, &GetSetVal);
      // Must update the XARB bubble injector when TAT values change
      SetTcBubbleInjector (MrcData, Channel);
    }
  }
}
