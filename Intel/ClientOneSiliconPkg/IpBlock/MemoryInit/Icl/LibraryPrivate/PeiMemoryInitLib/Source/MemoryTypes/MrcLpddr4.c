/** @file
  Implementation of LPDDR4 Specific functions, and constants.

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
  JEDEC
**/
#include "MrcInterface.h"
#include "MrcCommon.h"
#include "MrcDdrCommon.h"
#include "MrcMaintenance.h"
#include "MrcLpddr4.h"
#include "MrcLpddr4Registers.h"
#include "MrcMcOffsets.h"
#include "MrcMcConfiguration.h"
#include "MrcMemoryApi.h"

///
/// Defines
///
#define MRC_LPDDR4_INIT_NUM_MR (9)

#define TFR_MIN (0)
#define TFR_MAX (1)
#define TFR_NUM_ENTRIES   (Lp4x16WrMax)
#define ODTL_NUM_ENTRIES  (7)

#define LP4_RZQ_NUM_VALUES (7)

///
/// Local Constants
///
// This table is based off of the LPDDR4 JEDEC Table, "4.12 Read and Write Latencies".
// For Read and Write Latency, each range is subdivided into [Non]DBI and Set [A/B] for a total
// of eight entries.  The frequency for the entry being programmed must be greater than the minimum
// and less than or equal to the maximum.
static const MrcFrequency TimingFreqRange[TFR_NUM_ENTRIES][2] = {
  {fNoInit, f533},
  {f533,    f1067},
  {f1067,   f1600},
  {f1600,   f2133},
  {f2133,   f2667},
  {f2667,   f3200},
  {f3200,   f3733},
  {f3733,   f4267}};

// Valid Config Table for PU-Cal versus Soc ODT
static const BOOLEAN  PuCalSocOdtValidLp4[Lp4PuCalMax][Lp4OdtMax] = {
// Disable,  240,  120,   80,    60,    48,    40  (Ohms)
  {FALSE,   TRUE, TRUE, TRUE, FALSE,  FALSE, FALSE}, //  Vddq/2.5 mV
  {FALSE,   TRUE, TRUE, TRUE,  TRUE,  TRUE,  TRUE}  //  Vddq/3 mV
};

static const BOOLEAN  PuCalSocOdtValidLp4x[Lp4PuCalMax][Lp4OdtMax] = {
// Disable,  240,   120,    80,    60,    48,    40  (Ohms)
  {FALSE,  FALSE,  TRUE, FALSE,  TRUE,  FALSE, FALSE}, //  Vddq * 0.6 mV (360mV)
  {FALSE,   TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE}  //  Vddq * 0.5 mV (300mV)
};

// This table is based off of Table 74 - ODTLon and ODTLoff Latency Values from LPDDR4 JEDEC Spec.
// This table provides ODTL timing parameters for LPDDR4.  Both the time till ODT turns on,
// and the time till ODT turns off.  This is based on three parameters: Frequency, WL Set, and ODT ON/OFF.
// The enumeration LPDDR4_WR_LATENCY_SET is used to select which timing value to return.
// The table is structured such that the frequency listed is the upper limit of the frequency
// that the timing supports.  If the timing value is 0, then that timing is not supported/valid
// for the frequency range.
static const LP4_ODTL_TIMING_TYPE Lp4OdtlTiming[ODTL_NUM_ENTRIES] = {
//         ODTLon   ODTLoff
// WL Set  A  B     A   B
// Freq
  {f1067, {0,  0}, { 0,  0}},
  {f1600, {0,  6}, { 0, 22}},
  {f2133, {4, 12}, {20, 28}},
  {f2667, {4, 14}, {22, 32}},
  {f3200, {6, 18}, {24, 36}},
  {f3733, {6, 20}, {26, 40}},
  {f4267, {8, 24}, {28, 44}}
};

// This table is the list of possible terminations the DRAM can achieve using ZQ Resistor.
const UINT16 Lp4RzqValues[LP4_RZQ_NUM_VALUES] = { 0xFFFF, 240, 120, 80, 60, 48, 40 };

// LPDDR4 ODT Values
// ODT values are in this order: { RttWr, RttCa }
const TOdtValueLpddr4 Lpddr4OdtTable[MAX_DIMMS_IN_CHANNEL][2] = {
/// 1DPC 1R,  1DPC 2R
  {{40, 80},  {40, 80}},
};

///
/// Functions
///
/**
  This function is used to get the timing parameter tDQS2DQ Min or Max.

  @param[in]  IsMin - TRUE returns the minimum value, FALSE returns the maximum value.

  @retval UINT32 - The requested parameter in Femptoseconds.
**/
UINT32
Lpddr4GetTdqs2dq (
  IN  BOOLEAN IsMin
  )
{
  return ((IsMin) ? MRC_LP4_tDQS2DQ_MIN_FS : MRC_LP4_tDQS2DQ_MAX_FS);
}

/**
  This functions checks to see if the requested latency is within the frequency range
  required by JEDEC.

  @param[in]  MrcData - Pointer to MRC global data.
  @param[in]  Latency - Encoded latency entry.  Supports Read Latency, Write Latency, tWR, and tRTP.

  @retval MrcStatus - mrcSuccess if Latency is valid and the frequency is in the range.  Else mrcWrongInputParameter.
**/
MrcStatus
Lpddr4LatencyFreqCheck (
  IN  MrcParameters *MrcData,
  IN  INT8          Latency
  )
{
  MrcDebug      *Debug;
  MrcStatus     Status;
  MrcFrequency  CurFreq;
  MrcFrequency  MaxFreq;
  MrcFrequency  MinFreq;

  Debug = &MrcData->Outputs.Debug;

  // Check to see if the time requested matches JEDEC Frequency table
  if ((Latency >= 0) && (Latency < TFR_NUM_ENTRIES)) {
    CurFreq = MrcData->Outputs.HighFrequency;
    MaxFreq = TimingFreqRange[(UINT8) Latency][TFR_MAX];
    MinFreq = TimingFreqRange[(UINT8) Latency][TFR_MIN];

    if ((CurFreq <= MinFreq) || (CurFreq > MaxFreq)) {
      Status = mrcWrongInputParameter;
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_ERROR,
        "%s Current frequency(%d) is not within supported range[%d:%d] for latency=%d",
        gErrString,
        CurFreq,
        MinFreq,
        MaxFreq,
        Latency
        );
    } else {
      Status = mrcSuccess;
    }
  } else {
    Status = mrcWrongInputParameter;
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_ERROR,
      "%s Latency(%d) entry out of range for TimingFreqRange Table(%d)",
      gErrString,
      Latency,
      TFR_NUM_ENTRIES
      );
  }

  return Status;
}

/**
  This function converts from Ohms to LPDDR4 MR ODT encoding.
  //@ todo: <CNL> Reverse ODT lookup from Encoding to Ohms.

  @param[in]  OdtValue  - ODT Value in Ohms.

  @retval INT8 - LPDDR4 encoding if valid ODT value.  Else, -1.
**/
INT8
Lpddr4OdtEncode (
  IN  UINT16  OdtValue
  )
{
  INT8      EncodeVal;

  switch (OdtValue) {
    case 0xFFFF:
      EncodeVal = Lp4OdtOff;
      break;

    case 240:
      EncodeVal = Lp4Odt240;
      break;

    case 120:
      EncodeVal = Lp4Odt120;
      break;

    case 80:
      EncodeVal = Lp4Odt80;
      break;

    case 60:
      EncodeVal = Lp4Odt60;
      break;

    case 48:
      EncodeVal = Lp4Odt48;
      break;

    case 40:
      EncodeVal = Lp4Odt40;
      break;

    default:
      EncodeVal = -1;
      break;
  }

  return EncodeVal;
}

/**
  This function configures the terminating ranks to FSP-OP 1 to enable their CA ODT
  termination for the non-terminating ranks if enabled.  Otherwise, they are set
  to FSP-OP 0, which is the reset default configuration (off).
  This is done across all LPDDR4 channels.

  @param[in]  MrcData - Pointer to the MRC global data.
  @param[in]  Enable  - Boolean parameter to enable(TRUE) or disable(FALSE) CA termination.

  @retval MrcStatus - mrcSuccess, otherwise an error status.
**/
MrcStatus
MrcLpddr4SetCbtCaOdtEn (
  IN  MrcParameters *const  MrcData,
  IN  BOOLEAN               Enable
  )
{
  MrcStatus           Status;
  MrcStatus           CurStatus;
  MrcIntOutput        *IntOutputs;
  MrcIntCmdTimingOut  *IntCmdTiming;
  UINT8               Channel;
  UINT8               Rank;
  UINT8               RankMask;
  UINT8               CmdRanksTermMask;
  LPDDR4_FSP_OP_MODE  FspOpPoint;

  IntOutputs = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  Status = mrcSuccess;
  CmdRanksTermMask = MrcData->Inputs.CmdRanksTerminated;

  FspOpPoint = (Enable) ? Lp4FspOpPoint1 : Lp4FspOpPoint0;

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    RankMask = 1 << Rank;
    if ((RankMask & MrcData->Outputs.ValidRankMask) == 0) {
      continue;
    }

    if ((CmdRanksTermMask & RankMask) != 0) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        // Use safe CS/CA PI settings, otherwise this MRW may get sampled as invalid command (or SRE etc.)
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl, 0, 0x03, MRC_INITIAL_CTL_PI, 0);
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmd, 0, 0x1F, MRC_INITIAL_CMD_PI, 0);
      }

      CurStatus = Lpddr4SetFsp (MrcData, ALL_CHANNEL_MASK, ALL_SUB_CH_MASK, RankMask, MRC_IGNORE_ARG_8, MRC_IGNORE_ARG_8, FspOpPoint);
      if (Status == mrcSuccess) {
        Status = CurStatus;
      }
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        // Restore CS/CA PI settings from the host struct
        IntCmdTiming  = &IntOutputs->Controller[0].CmdTiming[Channel];
        // CS is per subch
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl, 0, (1 << 0), IntCmdTiming->CtlPiCode[0], 0);
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCtl, 0, (1 << 1), IntCmdTiming->CtlPiCode[1], 0);
        ShiftPIforCmdTraining (MrcData, Channel, MrcIterationCmd, 0,     0x1F, IntCmdTiming->CmdPiCode[0], 0);
      }
    }
  } // Rank

  return Status;
}
/**
  This function will set up the pointer passed in based on LPDDR4 Mode Register definition.
  If MRC_IGNORE_ARGx is passed in, that parameter is ignored.
  Only WriteRecovery does error checking against spec valid values.

  @param[in]      MrcData         - Pointer to MRC global data.
  @param[in]      SdramWidth      - LPDDR4 device width (8 or 16)
  @param[in]      BurstLength     - Number of DRAM bursts (UI) per command.
  @param[in]      WrPreambleLen   - Write Preamble length in tCK.
  @param[in]      RdPreambleType  - Switch to select between a static or toggling read Preamble.
  @param[in]      WriteRecovery   - Write Recovery time for auto pre-charge commands.
  @param[in,out]  MrData          - Pointer to MR data to update.

  @retval MrcStatus - mrcWrongInputParameter or mrcSuccess.
**/
MrcStatus
MrcLpddr4SetMr1 (
  IN      MrcParameters *const  MrcData,
  IN      UINT8                 SdramWidth,
  IN      UINT8                 BurstLength,
  IN      UINT8                 WrPreambleLen,
  IN      UINT8                 RdPreambleType,
  IN      UINT8                 WriteRecovery,
  IN      UINT8                 RdPostambleLen,
  IN OUT  UINT16                *MrData
  )
{
  MrcDebug      *Debug;
  MrcStatus     Status;
  INT8          WrEncode;
  LPDDR4_MODE_REGISTER_1_TYPE *Mr1;

  Debug   = &MrcData->Outputs.Debug;
  Status  = mrcSuccess;
  Mr1     = (LPDDR4_MODE_REGISTER_1_TYPE *) MrData;

  if (BurstLength != MRC_IGNORE_ARG_8) {
    Mr1->Bits.BurstLength = BurstLength;
  }

  if (WrPreambleLen != MRC_IGNORE_ARG_8) {
    Mr1->Bits.WritePreambleLen  = WrPreambleLen;
  }

  if (RdPreambleType != MRC_IGNORE_ARG_8) {
    Mr1->Bits.RdPreambleType  = RdPreambleType;
  }

  if (RdPostambleLen != MRC_IGNORE_ARG_8) {
    Mr1->Bits.RdPostAmbleLen  = RdPostambleLen;
  }

  if (WriteRecovery != MRC_IGNORE_ARG_8) {
    WrEncode = -1;
    if (SdramWidth == 16) {
      switch (WriteRecovery) {
        case 6:
          WrEncode = Lp4x16Wr6;
          break;

        case 10:
          WrEncode = Lp4x16Wr10;
          break;

        case 16:
          WrEncode = Lp4x16Wr16;
          break;

        case 20:
          WrEncode = Lp4x16Wr20;
          break;

        case 24:
          WrEncode = Lp4x16Wr24;
          break;

        case 30:
          WrEncode = Lp4x16Wr30;
          break;

        case 34:
          WrEncode = Lp4x16Wr34;
          break;

        case 40:
          WrEncode = Lp4x16Wr40;
          break;

        default:
          WrEncode = -1;
          break;
      }
    }

    if (SdramWidth == 8) {
      switch (WriteRecovery) {
        case 6:
          WrEncode = Lp4x8Wr6;
          break;

        case 12:
          WrEncode = Lp4x8Wr12;
          break;

        case 16:
          WrEncode = Lp4x8Wr16;
          break;

        case 22:
          WrEncode = Lp4x8Wr22;
          break;

        case 28:
          WrEncode = Lp4x8Wr28;
          break;

        case 32:
          WrEncode = Lp4x8Wr32;
          break;

        case 38:
          WrEncode = Lp4x8Wr38;
          break;

        case 44:
          WrEncode = Lp4x8Wr44;
          break;

        default:
          WrEncode = -1;
          break;
      }
    }

    // Check to see if the time requested matches JEDEC Frequency table
    Status = Lpddr4LatencyFreqCheck (MrcData, WrEncode);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, (Status != mrcSuccess) ? " (WR)\n" : "");

    if (WrEncode != -1) {
      Mr1->Bits.WrRecovery  = WrEncode;
    } else {
      Status = mrcWrongInputParameter;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Unsupported Write Recovery value\n", gErrString);
    }
  }

  return Status;
}

/*
  This function will set up the pointer passed in based on LPDDR4 Mode Register definition.
  If MRC_IGNORE_ARGx is passed in, that parameter is ignored.
  Only RdLatency and WrLatency does error checking against spec valid values.

  @param[in]      MrcData         - Pointer to MRC global data.
  @param[in]      SdramWidth      - LPDDR4 device width (8 or 16)
  @param[in]      RdLatency       - Read Latency Value.  Function will convert to encoding.
  @param[in]      Wrlatency       - Write Latency Value.  Function will convert to encoding.
  @param[in]      WrLatencySet    - Switch to select between Set A and Set B of Write Latency delays.
  @param[in]      WrLevelingMode  - Switch to enable JEDEC Write Leveling mode.
  @param[in,out]  MrData          - Pointer to MR data to update.

  @retval MrcStatus - mrcWrongInputParameter or mrcSuccess.
**/
MrcStatus
MrcLpddr4SetMr2 (
  IN      MrcParameters *const  MrcData,
  IN      UINT8                 SdramWidth,
  IN      UINT16                RdLatency,
  IN      UINT16                WrLatency,
  IN      UINT8                 WrLatencySet,
  IN      UINT8                 WrLevelingMode,
  IN OUT  UINT16                *MrData
  )
{
  MrcDebug  *Debug;
  MrcStatus Status;
  UINT8     LatencySet;
  INT8      RdLatEncode;
  INT8      WrLatEncode;
  LPDDR4_MODE_REGISTER_2_TYPE *Mr2;

  Status = mrcSuccess;
  Debug = &MrcData->Outputs.Debug;
  Mr2   = (LPDDR4_MODE_REGISTER_2_TYPE *) MrData;

  // Do Write Latency Set first so we can proper encode the Write latency value.
  if (WrLatencySet != MRC_IGNORE_ARG_8) {
    Mr2->Bits.WrLatencySet = WrLatencySet;
    LatencySet = WrLatencySet;
  } else {
    // Get the set value.
    LatencySet = Mr2->Bits.WrLatencySet;
  }

  if (RdLatency != MRC_IGNORE_ARG_8) {
    RdLatEncode = -1;
    if (SdramWidth == 16) {
      switch (RdLatency) {
      case 6:
        RdLatEncode = Lp4x16Rl6;
        break;

      case 10:
        RdLatEncode = Lp4x16Rl10;
        break;

      case 14:
        RdLatEncode = Lp4x16Rl14;
        break;

      case 20:
        RdLatEncode = Lp4x16Rl20;
        break;

      case 24:
        RdLatEncode = Lp4x16Rl24;
        break;

      case 28:
        RdLatEncode = Lp4x16Rl28;
        break;

       case 32:
        RdLatEncode = Lp4x16Rl32;
        break;

      case 36:
        RdLatEncode = Lp4x16Rl36;
        break;

      default:
        RdLatEncode = -1;
        break;
      }
    }

    if (SdramWidth == 8) {
      switch (RdLatency) {
      case 6:
        RdLatEncode = Lp4x8Rl6;
        break;

      case 10:
        RdLatEncode = Lp4x8Rl10;
        break;

      case 16:
        RdLatEncode = Lp4x8Rl16;
        break;

      case 22:
        RdLatEncode = Lp4x8Rl22;
        break;

      case 26:
        RdLatEncode = Lp4x8Rl26;
        break;

      case 32:
        RdLatEncode = Lp4x8Rl32;
        break;

      case 36:
        RdLatEncode = Lp4x8Rl36;
        break;

      case 40:
        RdLatEncode = Lp4x8Rl40;
        break;

      default:
        RdLatEncode = -1;
        break;
      }
    }
    Status = Lpddr4LatencyFreqCheck (MrcData, RdLatEncode);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, (Status != mrcSuccess) ? " (RL)\n" : "");

    if (RdLatEncode == -1) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Invalid %s Latency Value: %d\n", gErrString, gRdString, RdLatency);
      Status = mrcWrongInputParameter;
    } else {
      Mr2->Bits.RdLatency = RdLatEncode;
    }
  }

  if (WrLatency != MRC_IGNORE_ARG_8) {
    if (LatencySet == Lp4WlSetA) {
      WrLatEncode   = (UINT8) WrLatency / 2;
      WrLatEncode  -= 2;
      // Only even delays between 4:18 are valid for WL "A"
      if (((WrLatency % 2) != 0) || (WrLatEncode < 0) || (WrLatEncode > Lp4WlAMax)) {
        // We will check against -1 outside the LatencySet if-statements.
        WrLatEncode = -1;
      }
    } else if (LatencySet == Lp4WlSetB) {
      switch (WrLatency) {
        case 4:
          WrLatEncode = Lp4WlB4;
          break;

        case 8:
          WrLatEncode = Lp4WlB8;
          break;

        case 12:
          WrLatEncode = Lp4WlB12;
          break;

        case 18:
          WrLatEncode = Lp4WlB18;
          break;

        case 22:
          WrLatEncode = Lp4WlB22;
          break;

        case 26:
          WrLatEncode = Lp4WlB26;
          break;

        case 30:
          WrLatEncode = Lp4WlB30;
          break;

        case 34:
          WrLatEncode = Lp4WlB34;
          break;

        default:
          // We will check against -1 outside the LatencySet if-statements.
          WrLatEncode = -1;
          break;
      }
    } else {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Improper Write Latency Set for Write Latency encoding\n", gErrString);
      Status = mrcWrongInputParameter;
      // This is a don't care at this point, but we don't want to confuse people
      // with a invalid xLatency Value message.
      WrLatEncode = 0;
    }

    Status = Lpddr4LatencyFreqCheck (MrcData, WrLatEncode);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, (Status != mrcSuccess) ? " (WL)\n" : "");

    // Check for error status in encoding conversion.
    if (WrLatEncode == -1) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Invalid %s Latency Value: %d\n", gErrString, gWrString, WrLatency);
      Status = mrcWrongInputParameter;
    } else {
      Mr2->Bits.WrLatency = WrLatEncode;
    }
  }

  if (WrLevelingMode != MRC_IGNORE_ARG_8) {
    Mr2->Bits.WrLevelingMode = WrLevelingMode;
  }

  return Status;
}

/**
  This function will set up the pointer passed in based on LPDDR4 Mode Register definition.
  If MRC_IGNORE_ARGx is passed in, that parameter is ignored.
  PdDrvStr does error checking against spec valid values.
  LPDDR4 and LPDDR4X have different enumerations for PuCalPoint; but they match the following binary switch:
    0 - Higher VOH
    1 - Lower VOH
  No type checking for Lp4x is needed here because of this.

  @param[in]      MrcData     - Pointer to global MRC data.
  @param[in]      PuCalPoint  - Pull Up Calibration Point.
  @param[in]      PdDrvStr    - Pull Down Drive Strength value to set (in Ohms).  Does not support infinity (0xFFFF) as RFU.
  @param[in,out]  MrData      - Pointer to MR data to update.

  @retval MrcStatus - mrcSuccess if a supported ODT value, else mrcWrongInputParameter.
**/
MrcStatus
MrcLpddr4SetMr3 (
  IN  MrcParameters *const  MrcData,
  IN  UINT8                 PuCalPoint,
  IN  UINT16                PdDrvStr,
  IN OUT  UINT16    *const  MrData
  )
{
  MrcDebug  *Debug;
  MrcStatus Status;
  INT8      Encoding;
  LPDDR4_MODE_REGISTER_3_TYPE  *Mr3;

  Status  = mrcSuccess;
  Mr3    = (LPDDR4_MODE_REGISTER_3_TYPE *) MrData;
  Debug   = &MrcData->Outputs.Debug;

  // Static Values
  Mr3->Bits.WrPostAmbleLen  = Lp4WrPst0_5;
  Mr3->Bits.PprProtection   = Lp4PprProtectDis;
  Mr3->Bits.DbiRdEn         = Lp4RdDbiDis;
  Mr3->Bits.DbiWrEn         = Lp4WrDbiDis;

  if (PuCalPoint != MRC_IGNORE_ARG_8) {
    Mr3->Bits.PullUpCal = PuCalPoint;
  }

  if (PdDrvStr != MRC_IGNORE_ARG_8) {
    Encoding = Lpddr4OdtEncode (PdDrvStr);

    if (Encoding == -1) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Invalid %s Value: %u\n", gErrString, gDrvStr, PdDrvStr);
      Status  = mrcWrongInputParameter;
    } else {
      Mr3->Bits.PdDriveStrength  = Encoding;
    }
  }

  return Status;
}

/**
  This function will set up the pointer passed in based on LPDDR4 Mode Register definition.
  If MRC_IGNORE_ARG8 is passed in, that parameter is ignored.
  DqOdt and CaOdt does error checking against spec valid values.

  @param[in]      MrcData - Pointer to global MRC data.
  @param[in]      DqOdt   - Data ODT value to set (in Ohms).
  @param[in]      CaOdt   - Command/Address ODT value to set (in Ohms).
  @param[in,out]  MrData  - Pointer to MR data to update.

  @retval MrcStatus - mrcSuccess if a supported ODT value, else mrcWrongInputParameter.
**/
MrcStatus
MrcLpddr4SetMr11 (
  IN      MrcParameters *const  MrcData,
  IN      UINT16                DqOdt,
  IN      UINT16                CaOdt,
  IN OUT  UINT16        *const  MrData
  )
{
  MrcDebug  *Debug;
  MrcStatus Status;
  INT8      Encoding;
  LPDDR4_MODE_REGISTER_11_TYPE  *Mr11;

  Status  = mrcSuccess;
  Mr11    = (LPDDR4_MODE_REGISTER_11_TYPE *) MrData;
  Debug   = &MrcData->Outputs.Debug;

  if (DqOdt != MRC_IGNORE_ARG_8) {
    Encoding = Lpddr4OdtEncode (DqOdt);

    if (Encoding == -1) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Invalid %s ODT Value %u\n", gErrString, gDataString, DqOdt);
      Status  = mrcWrongInputParameter;
    } else {
      Mr11->Bits.DqOdt  = Encoding;
    }
  }

  if (CaOdt != MRC_IGNORE_ARG_8) {
    Encoding = Lpddr4OdtEncode (CaOdt);

    if (Encoding == -1) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Invalid %s ODT Value %u\n", gErrString, gCmdString, CaOdt);
      Status  = mrcWrongInputParameter;
    } else {
      Mr11->Bits.CaOdt  = Encoding;
    }
  }

  return Status;
}

/**
  This function will set up the pointer passed in based on LPDDR4 Mode Register definition.
  If MRC_IGNORE_ARG8 is passed in, that parameter is ignored.
  Only CaVref does error checking against spec valid values.

  @param[in]      MrcData     - Pointer to global MRC data.
  @param[in]      CaVref      - Command/Address Vref to set (JEDEC Encoding).
  @param[in]      CaVrefRange - Command/Address Vref range selector.
  @param[in]      CaCbtMode   - Command/Address CBT training mode.
  @param[in,out]  MrData      - Pointer to MR data to update.

  @retval MrcStatus - mrcWrongInputParameter if CaVref is invalid, else mrcSuccess.
**/
MrcStatus
MrcLpddr4SetMr12 (
  IN      MrcParameters *const  MrcData,
  IN      UINT8                 CaVref,
  IN      UINT8                 CaVrefRange,
  IN      UINT8                 CaCbtMode,
  IN OUT  UINT16        *const  MrData
  )
{
  MrcDebug  *Debug;
  MrcStatus Status;
  LPDDR4_MODE_REGISTER_12_TYPE  *Mr12;

  Debug   = &MrcData->Outputs.Debug;
  Status  = mrcSuccess;
  Mr12    = (LPDDR4_MODE_REGISTER_12_TYPE *) MrData;

  if (CaVref != MRC_IGNORE_ARG_8) {
    if (CaVref < LPDDR4_VREF_FIELD_MAX) {
      Mr12->Bits.CaVref = CaVref;
    } else {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s Invalid %s Vref Setting: %d\n", gErrString, gCmdString, CaVref);
      Status = mrcWrongInputParameter;
    }
  }

  if (CaVrefRange != MRC_IGNORE_ARG_8) {
    Mr12->Bits.CaVrefRange  = CaVrefRange;
  }

  if (CaCbtMode != MRC_IGNORE_ARG_8) {
    Mr12->Bits.CaCbtMode = CaCbtMode;
  }

  return Status;
}

/**
  This function will set up the pointer passed in based on LPDDR4 Mode Register definition.
  If MRC_IGNORE_ARG8 is passed in, that parameter is ignored.

  @param[in]      MrcData         - Pointer to global MRC data.
  @param[in]      CbtMode         - Command Bus Training mode switch.
  @param[in]      RptMode         - Read Preamble Training mode switch.
  @param[in]      VrcgMode        - VREF Current Generator mode switch.
  @param[in]      DataMaskDisable - Data Mask Operation switch.
  @param[in]      FspWrite        - Frequency Set Point write enable switch.
  @param[in]      FspOpMode       - Frequency Set Point Operation Mode switch.
  @param[in,out]  MrData          - Pointer to MR data to update.

  @retval MrcStatus - mrcSuccess if a supported ODT value, else mrcWrongInputParameter.
**/
MrcStatus
MrcLpddr4SetMr13 (
  IN      MrcParameters *const  MrcData,
  IN      UINT8                 CbtMode,
  IN      UINT8                 RptMode,
  IN      UINT8                 VrcgMode,
  IN      UINT8                 DataMaskDisable,
  IN      UINT8                 FspWrite,
  IN      UINT8                 FspOpMode,
  IN OUT  UINT16        *const  MrData
  )
{
  MrcStatus Status;
  LPDDR4_MODE_REGISTER_13_TYPE  *Mr13;

  Status  = mrcSuccess;
  Mr13    = (LPDDR4_MODE_REGISTER_13_TYPE *) MrData;

  // Set Static Values.
  Mr13->Bits.RroMode  = Lp4RroAllCodes;
  Mr13->Bits.VroMode  = Lp4VroDis;

  if (CbtMode != MRC_IGNORE_ARG_8) {
    Mr13->Bits.CbtMode  = CbtMode;
  }

  if (RptMode != MRC_IGNORE_ARG_8) {
    Mr13->Bits.RptMode  = RptMode;
  }

  if (VrcgMode != MRC_IGNORE_ARG_8) {
    Mr13->Bits.VrcgMode = VrcgMode;
  }

  if (DataMaskDisable != MRC_IGNORE_ARG_8) {
    Mr13->Bits.DmDisable =  DataMaskDisable;
  }

  if (FspWrite != MRC_IGNORE_ARG_8) {
    Mr13->Bits.FspWe  = FspWrite;
  }

  if (FspOpMode != MRC_IGNORE_ARG_8) {
    Mr13->Bits.FspOpMode  = FspOpMode;
  }

  return Status;
}

/**
  This function will set up the pointer passed in based on LPDDR4 Mode Register definition.
  If MRC_IGNORE_ARG8 is passed in, that parameter is ignored.
  Only DqVref does error checking against spec valid values.

  @param[in]      MrcData     - Pointer to global MRC data.
  @param[in]      DqVref      - Data Vref to set (JEDEC Encoding).
  @param[in]      DqVrefRange - Data Vref range selector.
  @param[in,out]  MrData      - Pointer to MR data to update.

  @retval MrcStatus - mrcSuccess if a supported ODT value, else mrcWrongInputParameter.
**/
MrcStatus
MrcLpddr4SetMr14 (
  IN      MrcParameters *const  MrcData,
  IN      UINT8                 DqVref,
  IN      UINT8                 DqVrefRange,
  IN OUT  UINT16        *const  MrData
  )
{
  MrcDebug  *Debug;
  MrcStatus Status;
  LPDDR4_MODE_REGISTER_14_TYPE  *Mr14;

  Debug   = &MrcData->Outputs.Debug;
  Status  = mrcSuccess;
  Mr14    = (LPDDR4_MODE_REGISTER_14_TYPE *) MrData;

  if (DqVref != MRC_IGNORE_ARG_8) {
    if (DqVref < LPDDR4_VREF_FIELD_MAX) {
      Mr14->Bits.DqVref = DqVref;
    } else {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s Invalid %s Vref Setting\n", gErrString, gDataString, DqVref);
      Status = mrcWrongInputParameter;
    }
  }

  if (DqVrefRange != MRC_IGNORE_ARG_8) {
    Mr14->Bits.DqVrefRange  = DqVrefRange;
  }

  return Status;
}

/*
  This function will set up the pointer passed in based on LPDDR4 Mode Register definition.
  If MRC_IGNORE_ARG8 is passed in, that parameter is ignored.
  Only SocOdt does error checking against spec valid values.

  @param[in]      MrcData - Pointer to global MRC data.
  @param[in]      SocOdt  - SOC ODT value to set (in Ohms).
  @param[in]      CkOdtEn - Clock ODT enabled for non-terminating rank.
  @param[in]      CsOdtEn - Chip Select ODT enable for non-terminating rank.
  @param[in]      CaOdtEn - Command/Address ODT termination disable.
  @param[in,out]  MrData  - Pointer to MR data to update.

  @retval MrcStatus - mrcSuccess if a supported ODT value, else mrcWrongInputParameter.
**/
MrcStatus
MrcLpddr4SetMr22 (
  IN      MrcParameters *const  MrcData,
  IN      UINT16                SocOdt,
  IN      UINT8                 CkOdtEn,
  IN      UINT8                 CsOdtEn,
  IN      UINT8                 CaOdtEn,
  IN OUT  UINT16        *const  MrData
  )
{
  MrcDebug  *Debug;
  MrcStatus Status;
  INT8      Encoding;
  LPDDR4_MODE_REGISTER_22_TYPE  *Mr22;

  Status  = mrcSuccess;
  Mr22    = (LPDDR4_MODE_REGISTER_22_TYPE *) MrData;
  Debug   = &MrcData->Outputs.Debug;

  // Static Values.
  Mr22->Bits.x8OdtDis7to0  = (MrcData->Outputs.Lp4x8) ? 1 : 0;
  Mr22->Bits.x8OdtDis15to8 = 0;

  if (SocOdt != MRC_IGNORE_ARG_8) {
    Encoding = Lpddr4OdtEncode (SocOdt);

    if (Encoding == -1) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Invalid %s ODT Value\n", gErrString, gSocString, SocOdt);
      Status  = mrcWrongInputParameter;
    } else {
      Mr22->Bits.SocOdt  = Encoding;
    }
  }

  if (CkOdtEn != MRC_IGNORE_ARG_8) {
    Mr22->Bits.CkOdtEn  = CkOdtEn;
  }

  if (CsOdtEn != MRC_IGNORE_ARG_8) {
    Mr22->Bits.CsOdtEn  = CsOdtEn;
  }

  if (CaOdtEn != MRC_IGNORE_ARG_8) {
    Mr22->Bits.CaOdtEn  = CaOdtEn;
  }

  return Status;
}

/**
  This function will set up the pointer passed in based on LPDDR4 Mode Register definition.
  If MRC_IGNORE_ARG8 is passed in, that parameter is ignored.

  @param[in]      MrcData       - Pointer to global MRC data.
  @param[in]      DqioDuration  - DQS interval timer run time.
  @param[in,out]  MrData        - Pointer to MR data to update.

  @retval MrcStatus - mrcSuccess if the value is supported, else mrcWrongInputParameter.
**/
MrcStatus
MrcLpddr4SetMr23 (
  IN      MrcParameters *const  MrcData,
  IN      UINT8                 DqioDuration,
  IN OUT  UINT16        *const  MrData
  )
{
  MrcStatus Status;

  Status = mrcSuccess;

  *MrData = DqioDuration;

  return Status;
}

/**
  Program LPDDR4 FSP-OP and FSP-WR values.

  @param[in]  MrcData     - Pointer to MRC global data.
  @param[in]  ChMask      - Bit mask of Channel's to configure.
  @param[in]  SubChMask   - Bit mask of Sub Channel's to configure.
  @param[in]  RankMask    - Bit mask of Rank's to configure.
  @param[in]  VrcgMode    - VREF Current Generator mode switch.
  @param[in]  FspWePoint  - FSP-WR value in MR13[6]
  @param[in]  FspOpPoint  - FSP-OP value in MR13[7]

  @retval MrcStatus - mrcSuccess if successful, else an error status.
**/
MrcStatus
Lpddr4SetFsp (
  IN  MrcParameters *const  MrcData,
  IN  UINT8                 ChMask,
  IN  UINT8                 SubChMask,
  IN  UINT8                 RankMask,
  IN  UINT8                 VrcgMode,
  IN  UINT8                 FspWePoint,
  IN  UINT8                 FspOpPoint
  )
{
  MrcStatus         Status;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  UINT8             Channel;
  UINT8             Rank;
  UINT16            *MrPtr;
  UINT32            Address;
  UINT32            SubCh;
  UINT32            Delay;

  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];

  Address = mrMR13;
  Status  = mrcSuccess;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if ((!MrcChannelExist (Outputs, Channel)) || ((ChMask & (1 << Channel)) == 0)) {
      continue;
    }
    ChannelOut = &ControllerOut->Channel[Channel];
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank ++) {
      if ((!MrcRankInChannelExist (MrcData, Rank, Channel)) || ((RankMask & (1 << Rank)) == 0)) {
        continue;
      }
      MrPtr = ChannelOut->Dimm[0].Rank[Rank].MR;
      MrcLpddr4SetMr13 (MrcData, MRC_IGNORE_ARG_8, MRC_IGNORE_ARG_8, VrcgMode, MRC_IGNORE_ARG_8, FspWePoint, FspOpPoint, &MrPtr[mrIndexMR13]);
      for (SubCh = 0; SubCh < MAX_SUB_CHANNEL; SubCh++) {
        if (MrcSubChannelExist (MrcData, Channel, SubCh) && ((SubChMask & (1 << SubCh)) != 0)) {
          Status = MrcIssueMrw (MrcData, Channel, SubCh, Rank, Address, MrPtr[mrIndexMR13], FALSE, FALSE, TRUE);
          if (Status != mrcSuccess) {
            return Status;
          }
        }
      } // for SubCh
    } // for Rank
  } // for Channel

  if (FspOpPoint != MRC_IGNORE_ARG_8) {
    // When FSP-OP is changed, wait tFC_Long = 250ns
    // This covers for tVRCG_ENABLE/tVRCG_DISABLE as well if needed
    MrcWait (MrcData, MRC_LP4_tFC_LONG_NS * MRC_TIMER_1NS);
  } else if (VrcgMode != MRC_IGNORE_ARG_8) {
    // When VRCG mode is changed, wait tVRCG_ENABLE = 200ns or tVRCG_DISABLE = 100ns
    Delay = (VrcgMode == Lp4VrcgNormal) ? MRC_LP4_tVRCG_DISABLE_NS : MRC_LP4_tVRCG_ENABLE_NS;
    MrcWait (MrcData, Delay * MRC_TIMER_1NS);
  }

  return Status;
}

/**
  This function will setup the default MR values for LPDDR4 based on
  DRAM Timings and Frequency in MRC global data.
  Only populated Channels and Ranks are initialized.

  @param[in]  MrcData -  Pointer to MRC global data.

  @retval MrcStatus - mrcSuccess if successful, else an error status.
**/
MrcStatus
Lpddr4InitMrw (
  IN  MrcParameters *const MrcData
  )
{
  static const UINT8  ClkOdtCtlLp4[MAX_RANK_IN_CHANNEL]  = { Lp4CkOdtDis, Lp4CkOdtDis,  Lp4CkOdtDis,  Lp4CkOdtDis  };
  static const UINT8  ClkOdtCtlLp4x[MAX_RANK_IN_CHANNEL] = { Lp4xCkOdtEn, Lp4xCkOdtDis, Lp4xCkOdtDis, Lp4xCkOdtDis };
  static const UINT8  CaOdtCtl[MAX_RANK_IN_CHANNEL]      = { Lp4CaOdtEn,  Lp4CaOdtDis,  Lp4CaOdtDis,  Lp4CaOdtDis  };
  MrcDebug          *Debug;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcOutput         *Outputs;
  MrcInput          *Inputs;
  MrcTiming         *TimingPtr;
  UINT16            *MrPtr;
  const BOOLEAN     *PuCalSocOdtValid;
  const UINT8       *ClkOdtCtl;
  UINT8             SdramWidth;
  MrcStatus         Status;
  INT32             Offset;
  UINT32            Channel;
  UINT32            Rank;
  UINT32            Profile;
  UINT16            DqOdt;
  UINT16            CaOdt;
  UINT16            PdDrvStr;
  UINT16            RlVal;
  UINT16            WrVal;
  UINT16            SocOdt;
  UINT16            DqDrvStrength;
  UINT16            DqVrefMv;
  UINT16            CaVrefMv;
  UINT8             CaVrefEnc;
  UINT8             CaVrefRange;
  UINT8             DqVrefEnc;
  UINT8             DqVrefRange;
  UINT8             DqioDuration;
  UINT8             CsOdtCtl;
  UINT8             PuCal;
  TOdtValueLpddr4   *Lpddr4OdtTableIndex;
  LPDDR4_MODE_REGISTER_22_TYPE  *Mr22Ptr;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[CONTROLLER_0];
  Status        = mrcSuccess;
  Profile       = Inputs->MemoryProfile;
  Lpddr4OdtTableIndex = NULL;
  CaOdt = 0;
  DqOdt = 0;
  SdramWidth = (Outputs->Lp4x8) ? 8 : 16;

  // Extract ODT tables from the first populated channel
  for (Channel = 0; (Channel < MAX_CHANNEL) && (Status == mrcSuccess); Channel++) {
    if (MrcChannelExist(&MrcData->Outputs, Channel)) {
      Lpddr4OdtTableIndex = (TOdtValueLpddr4 *)GetOdtTableIndex(MrcData, (UINT8) Channel, dDIMM0);
      if (Lpddr4OdtTableIndex == NULL) {
        MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "%s: OdtTableIndex is NULL!\n", gErrString);
        return mrcFail;
      }
      DqOdt = (Outputs->DramDqOdtEn) ? Lpddr4OdtTableIndex->RttWr : 0xFFFF;
      CaOdt = Lpddr4OdtTableIndex->RttCa;
      break;
    }
  }
  // No populated channels.
  if (Lpddr4OdtTableIndex == NULL) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s: OdtTableIndex is NULL!\n", gErrString);
    return mrcFail;
  }

  SocOdt         = Inputs->RcompTarget[RdOdt];
  DqDrvStrength  = Inputs->RcompTarget[WrDS];

  DqVrefMv = (UINT16) MrcCalcIdealVref (MrcData, DqDrvStrength, 0, DqOdt, WrV, TRUE);
  // Our platform design terminates both CA (SubCh 0 & 1), and creates a parallel effective resistance.
  // Input parameter is the ODT sent to the MR of the DRAM but the effective ODT seen by the CPU is 1/2
  // CaVrefMv = (UINT16) MrcCalcIdealVref (MrcData, CaDrvStrength, 0, (CaOdt / 2), CmdV, TRUE);
  if (Outputs->Lp4x) {
    CaVrefMv = VDD_0_60 * 455 / 1000; // Default value for Lp4x
  } else {
    CaVrefMv = VDD_1_10 * 272 / 1000; // Default value for Lp4
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CmdV: %d mV\n", CaVrefMv);

  MrcVrefToOffsetLpddr4 (MrcData, DqVrefMv, &Offset);
  // Reserve 10 ticks on either edge
  if (Offset > (MRC_LP4_VREF_OFFSET_MAX - 10)) {
    Offset = MRC_LP4_VREF_OFFSET_MAX - 10;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Adjusting %s value to %d to allow for margining\n", gMarginTypesStr[WrV], Offset);
  } else if (Offset < (MRC_LP4_VREF_OFFSET_MIN + 10)) {
    Offset = MRC_LP4_VREF_OFFSET_MIN + 10;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Adjusting %s value to %d to allow for margining\n", gMarginTypesStr[WrV], Offset);
  }
  MrcOffsetToVrefLpddr4 (MrcData, Offset, &DqVrefRange, &DqVrefEnc);

  MrcVrefToOffsetLpddr4 (MrcData, CaVrefMv, &Offset);
  // Reserve 10 ticks on either edge
  if (Offset > (MRC_LP4_VREF_OFFSET_MAX - 10)) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Adjusting %s value to %d to allow for margining\n", gMarginTypesStr[CmdV], Offset);
    Offset = MRC_LP4_VREF_OFFSET_MAX - 10;
  } else if (Offset < (MRC_LP4_VREF_OFFSET_MIN + 10)) {
    Offset = MRC_LP4_VREF_OFFSET_MIN + 10;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Adjusting %s value to %d to allow for margining\n", gMarginTypesStr[CmdV], Offset);
  }
  MrcOffsetToVrefLpddr4 (MrcData, Offset, &CaVrefRange, &CaVrefEnc);

  DqioDuration  = 4;    // Stop after 64 clocks
  PdDrvStr      = 40;   // Default = RZQ/6
  if (Outputs->Lp4x) {
    PuCal             = Lp4xPuCal0_6;
    PuCalSocOdtValid  = &PuCalSocOdtValidLp4x[PuCal][0];
    ClkOdtCtl         = &ClkOdtCtlLp4x[0];
    CsOdtCtl          = Lp4xCsOdtEn;
  } else {
    PuCal             = Lp4PuCal2_5;
    PuCalSocOdtValid  = &PuCalSocOdtValidLp4[PuCal][0];
    ClkOdtCtl         = &ClkOdtCtlLp4[0];
    CsOdtCtl          = Lp4CsOdtEn;
  }

  // Initialize MR's in host structure.
  for (Channel = 0; (Channel < MAX_CHANNEL) && (Status == mrcSuccess); Channel++) {
    if (!MrcChannelExist (&MrcData->Outputs, Channel)) {
      continue;
    }

    ChannelOut  = &ControllerOut->Channel[Channel];
    TimingPtr   = &ChannelOut->Timing[Profile];
    for (Rank = 0; (Rank < MAX_RANK_IN_CHANNEL) && (Status == mrcSuccess); Rank++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)){
        continue;
      }

      MrPtr = ChannelOut->Dimm[Rank / MAX_RANK_IN_DIMM].Rank[Rank % MAX_RANK_IN_DIMM].MR;

      Status = MrcLpddr4SetMr1 (MrcData, SdramWidth, Lp4Bl16, Lp4WrPre2Tck, Lp4RdPreStatic, (UINT8) TimingPtr->tWR, Lp4RdPst0_5Tck, &MrPtr[mrIndexMR1]);
      if (Status == mrcSuccess) {
        RlVal = TimingPtr->tCL;
        // Subtract 1 here to take into account tDQSS.
        WrVal = TimingPtr->tCWL - 1;
        Status = MrcLpddr4SetMr2 (MrcData, SdramWidth, RlVal, WrVal, Lp4WlSetB, Lp4WlModeDis, &MrPtr[mrIndexMR2]);
        if (Status == mrcSuccess) {
          Status = MrcLpddr4SetMr11 (MrcData, DqOdt, CaOdt, &MrPtr[mrIndexMR11]);
          if (Status == mrcSuccess) {
            Status = MrcLpddr4SetMr12 (MrcData, CaVrefEnc, CaVrefRange, 0, &MrPtr[mrIndexMR12]);
            if (Status == mrcSuccess) {
              Status = MrcLpddr4SetMr13 (MrcData, Lp4CbtDis, Lp4RptDis, Lp4VrcgHighCurrent, Lp4DmDis, Lp4FspWePoint1, Lp4FspOpPoint0, &MrPtr[mrIndexMR13]);
              if (Status == mrcSuccess) {
                Status = MrcLpddr4SetMr14 (MrcData, DqVrefEnc, DqVrefRange, &MrPtr[mrIndexMR14]);
                if (Status == mrcSuccess) {
                  Status = MrcLpddr4SetMr22 (MrcData, SocOdt, ClkOdtCtl[Rank], CsOdtCtl, CaOdtCtl[Rank], &MrPtr[mrIndexMR22]);
                  Mr22Ptr = (LPDDR4_MODE_REGISTER_22_TYPE *) &MrPtr[mrIndexMR22];
                  if (Status == mrcSuccess) {
                    Status = MrcLpddr4SetMr3 (MrcData, PuCal, PdDrvStr, &MrPtr[mrIndexMR3]);
                    // Check if we programmed a valid combination of PuCal and SocOdt
                    if (PuCalSocOdtValid[Mr22Ptr->Bits.SocOdt] != TRUE) {
                      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s invalid combination of SocOdt(%d) and PuCal(%d).\n",
                        gErrString, Mr22Ptr->Bits.SocOdt, PuCal);
                      Status = mrcWrongInputParameter;
                    }
                    if (Status == mrcSuccess) {
                      Status = MrcLpddr4SetMr23 (MrcData, DqioDuration, &MrPtr[mrIndexMR23]);
                    } // Mr23 Success
                  } // Mr3 Success
                } // Mr22 Success
              } // Mr14 Success
            } // Mr13 Success
          } // Mr12 Success
        } // Mr11 Success
      } // Mr2 Success
    } // Mr1 Success
  } // for Channel

  return Status;
}

/**
  This function searches the list of valid ODT encodings for LPDDR4 to find the closest matching
  ODT.  The SOC ODT and the SOC_ODT programming to the LPDDR4 MR must match or unexpected behavior
  may occur.  It will return this value to the caller.

  @param[in]  MrcData - Pointer to the global MRC data
  @param[in]  SocOdt  - The ODT requested by the system

  @retval - Closest matching ODT value.
**/
UINT16
MrcCheckSocOdtLpddr4 (
  IN  MrcParameters *const  MrcData,
  IN  UINT16                SocOdt
  )
{
  UINT32  Index;
  UINT16  Distance1;
  UINT16  Distance2;
  UINT16  SocOdtRet;
  UINT16  LastValidValue;
  UINT8   PuCal;
  MrcOutput         *Outputs;
  const BOOLEAN     *PuCalSocOdtValid;

  Outputs = &MrcData->Outputs;


  if (Outputs->Lp4x) {
    PuCal = Lp4xPuCal0_6;
    PuCalSocOdtValid = &PuCalSocOdtValidLp4x[PuCal][0];
  } else {
    PuCal = Lp4PuCal2_5;
    PuCalSocOdtValid = &PuCalSocOdtValidLp4[PuCal][0];
  }

  SocOdtRet = 0;
  LastValidValue = 0xFFFF;

  // Determine the SOC ODT Encoding that matches closest to the real RxOdt value.
  // This is programmed in MR 22.
  for (Index = 0; Index < LP4_RZQ_NUM_VALUES; Index++) {
    if (PuCalSocOdtValid[Index] == FALSE) {
      continue;
    }
    if (SocOdt == Lp4RzqValues[Index]) {
      SocOdtRet = SocOdt;
      break;
    }
    // No exact match, find the closest match.
    // Array is ordered from Largest to smallest.
    // If we're Index == 0, only check if the requested value is greater
    if (Index == 0) {
      if (SocOdt > Lp4RzqValues[Index]) {
        SocOdtRet = Lp4RzqValues[Index];
        break;
      }
    } else if (Index == (LP4_RZQ_NUM_VALUES - 1)) {
      // End of the list, return the last element.
      SocOdtRet = Lp4RzqValues[Index];
      break;
    } else {
      // See if it falls between this index and the previous.
      if ((SocOdt < LastValidValue) && (SocOdt > Lp4RzqValues[Index])) {
        // Determine which termination is closest to the SOC and select that for MR22
        Distance1 = LastValidValue - SocOdt;
        Distance2 = SocOdt - Lp4RzqValues[Index];
        // Select the one with the smallest distance
        SocOdtRet = (Distance1 < Distance2) ? LastValidValue : Lp4RzqValues[Index];
        break;
      }
    }
    LastValidValue = Lp4RzqValues[Index];
  }
  if (SocOdtRet == 0) {
    SocOdtRet = LastValidValue;
  }

  return SocOdtRet;
}

/**
  This function will return the requested ODTL timing value (On/OFF).

  @param[in]  Frequency - Integer based number representing the frequency.
  @param[in]  WlSet     - The current Write Latency set used.
  @param[in]  OdtlParam - Specifies which value of ODTL to return: On or Off (LPDDR4_ODTL_PARAM).

  @retval UINT8 The timing value in DCLK's.  0 If it is unsupported/undefined.
**/
UINT8
MrcGetOdtlTimingLpddr4 (
  IN  UINT32                Frequency,
  IN  LPDDR4_WR_LATENCY_SET WlSet,
  IN  LPDDR4_ODTL_PARAM     OdtlParam
  )
{
  LP4_ODTL_TIMING_TYPE const  *TableEntry;
  UINT8 const                 *OdtlArray;
  UINT8                       RetVal;
  UINT8                       Index;

  RetVal      = 0;
  TableEntry  = NULL;

  // Search for the table entry matching the requested frequency.
  // The search will look for the entry which is <= to the requested frequency.
  for (Index = 0; Index < ODTL_NUM_ENTRIES; Index++) {
    TableEntry = &Lp4OdtlTiming[Index];

    if (Frequency <= TableEntry->Frequency) {
      break;
    }
  }

  // If we do not find a matching table entry, return 0
  if ((Index < ODTL_NUM_ENTRIES) && (TableEntry != NULL)) {
    if (OdtlParam == Lp4OdtlOn) {
      OdtlArray = TableEntry->OdtlOn;
    } else {
      // Lp4OdtOff
      OdtlArray = TableEntry->OdtlOff;
    }

    RetVal = OdtlArray[WlSet];
  }

  return RetVal;
}

/**
  Issue LPDDR4 MPC command using MRH (Mode Register Handler).

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Channel    - The channel to work on
  @param[in] SubChannel - The sub-channel to work on
  @param[in] Rank       - The rank to work on
  @param[in] Address    - MPC address
  @param[in] Data       - MPC Data
  @param[in] DebugPrint - When TRUE, will print debugging information

  @retval mrcSuccess    - MPC was sent successfully
  @retval mrcDeviceBusy - Timed out waiting for MRH
**/
MrcStatus
MrcIssueMpc (
  IN MrcParameters *const MrcData,
  IN UINT32               Channel,
  IN UINT32               SubChannel,
  IN UINT32               Rank,
  IN UINT32               Address,
  IN UINT32               Data,
  IN BOOLEAN              DebugPrint
  )
{
  MrcStatus Status;
  MrcDebug  *Debug;
  MrcOutput *Outputs;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  // Send the MPC
  Status = MrcRunMrh (MrcData, Channel, SubChannel, Rank, Address, Data, MRC_MRH_CMD_LP4_MPC);

  if (DebugPrint) {
    MRC_DEBUG_MSG (
      Debug, MSG_LEVEL_NOTE,
      "MrcIssueMpc on Ch %d SubCh %d Rank %d: Address 0x%X, Data=0x%08X\n",
      Channel, SubChannel, Rank, Address, Data
      );
  }

  return Status;
}

/**
  This function will issue the JEDEC init MR sequence for LPDDR4.
  If RestoreMRs is set, the sequence will use the MR values saved in
  the MRC global data.  Otherwise, an initial value is used.
  MR order: MR1, MR2, MR3, MR11, MR12, MR13, MR14, MR22, MR23, ZQ Start, ZQ Latch.
  Flow:
   1. Set Low frequency (1067)
   2. Send FSP-OP[0] MR2 to program RL of the high frequency
     - This is needed for DQ mapping step of ECT
   3. Set FSP-WR = 1, FSP-OP = 0
   4. Send all MRs
   5. If ECT_Done
     a. Set High frequency
     b. Set FSP-OP = 1

  @param[in]  MrcData - Pointer to MRC global data.

  @retval MrcStatus - mrcSuccess if successful, else an error status.
**/
MrcStatus
MrcJedecInitLpddr4 (
  IN  MrcParameters *const  MrcData
  )
{
  MrcStatus           Status;
  MrcStatus           CurStatus;
  MrcControllerOut    *ControllerOut;
  MrcChannelOut       *ChannelOut;
  MrcOutput           *Outputs;
  MrcDebug            *Debug;
  UINT32              Channel;
  UINT32              SubCh;
  UINT32              Rank;
  UINT16              Data;
  UINT8               MrData[MRC_LPDDR4_INIT_NUM_MR];
  UINT8               Index;
  static const UINT8  MrAddress[MRC_LPDDR4_INIT_NUM_MR] = { mrMR1,      mrMR2,      mrMR22,       mrMR11,       mrMR12,       mrMR13,       mrMR14,       mrMR3,      mrMR23 };
  static const UINT8  MrIndex[MRC_LPDDR4_INIT_NUM_MR]   = { mrIndexMR1, mrIndexMR2, mrIndexMR22,  mrIndexMR11,  mrIndexMR12,  mrIndexMR13,  mrIndexMR14,  mrIndexMR3, mrIndexMR23};

  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[CONTROLLER_0];
  Status        = mrcSuccess;

  if (!Outputs->RestoreMRs) {
    // Setup Init MR's to a default value, and update MrcData.
    Status = Lpddr4InitMrw (MrcData);
    if (Status != mrcSuccess) {
      return Status;
    }
  }

  // Send FSP-OP[0] MR2 to program RL of the high frequency
  // This is needed for DQ mapping step of ECT
  // Default RL/WL is for 533 MT/s
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    ChannelOut = &ControllerOut->Channel[Channel];
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank ++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
      Data = ChannelOut->Dimm[Rank / MAX_RANK_IN_DIMM].Rank[Rank % MAX_RANK_IN_DIMM].MR[mrIndexMR2];
      for (SubCh = 0; SubCh < MAX_SUB_CHANNEL; SubCh++) {
        if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
          Status = MrcIssueMrw (MrcData, Channel, SubCh, Rank, mrMR2, Data, FALSE, FALSE, !Outputs->RestoreMRs);
          if (Status != mrcSuccess) {
            return Status;
          }
        }
      } // for SubCh
    } // for Rank
  } // for Channel

  // Set FSP-WR = 1, FSP-OP = 0 - we will program MR's for FSP[1] while staying at FSP[0]
  Status = Lpddr4SetFsp (MrcData, ALL_CHANNEL_MASK, ALL_SUB_CH_MASK, ALL_RANK_MASK, MRC_IGNORE_ARG_8, Lp4FspWePoint1, Lp4FspOpPoint0);
  if (Status != mrcSuccess) {
    return Status;
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    ChannelOut  = &ControllerOut->Channel[Channel];
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel) == 0) {
        continue;
      }
      // Build array based on MR value in host structure.
      for (Index = 0; Index < MRC_LPDDR4_INIT_NUM_MR; Index++) {
        if (MrIndex[Index] < MAX_MR_IN_DIMM) {
          MrData[Index] = (UINT8) ChannelOut->Dimm[Rank / 2].Rank[Rank % 2].MR[MrIndex[Index]];
        } else {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "MR index(%d) exceeded MR array length(%d)\n", MrIndex[Index], MAX_MR_IN_DIMM);
          Status = mrcWrongInputParameter;
          break;
        }
      } // Index
      if (Status != mrcSuccess) {
        break;
      }

      // Send out MR's to DRAM.
      for (Index = 0; Index < MRC_LPDDR4_INIT_NUM_MR; Index++) {
        for (SubCh = 0; SubCh < MAX_SUB_CHANNEL; SubCh++) {
          if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
            continue;
          }
          CurStatus = MrcIssueMrw (
                       MrcData,
                       Channel,
                       SubCh,
                       Rank,
                       MrAddress[Index],
                       MrData[Index],
                       FALSE,  // InitMrw
                       FALSE,  // ChipSelect2N
                       !Outputs->RestoreMRs    // DebugPrint
                       );
          if (Status == mrcSuccess) {
            Status = CurStatus;
          }
        }
      } // Index
    } // Rank
    if (Status != mrcSuccess) {
      break;
    }
  } // Channel

  // Issue ZQ Cal Start and ZQ Cal Latch on all channels / ranks
  CurStatus = MrcIssueZQ (MrcData, Outputs->ValidChBitMask, MRC_ZQ_CAL);
  if (Status == mrcSuccess) {
    Status = CurStatus;
  }

  return Status;
}

/**
  Switch LPDDR4 to high operating frequency:
   - Set FSP_OP = 1
   - Lock MC PLL at high frequency

  @param[in] MrcData    - Pointer to MRC global data.
  @param[in] DebugPrint - Enable/disable debug printing

  @retval MrcStatus - mrcSuccess if successful, else an error status.
**/
MrcStatus
MrcLpddr4SwitchToHigh (
  IN  MrcParameters *const  MrcData,
  IN BOOLEAN                DebugPrint
  )
{
  MrcOutput     *Outputs;
  MrcStatus     Status;
  INT64         CkeOn;
  UINT32        Channel;

  Outputs = &MrcData->Outputs;

  // Set FSP-OP = 1
  Status = Lpddr4SetFsp (MrcData, ALL_CHANNEL_MASK, ALL_SUB_CH_MASK, ALL_RANK_MASK, MRC_IGNORE_ARG_8, MRC_IGNORE_ARG_8, Lp4FspOpPoint1);
  if (Status != mrcSuccess) {
    return Status;
  }

  // Set High frequency
  if ((Outputs->Frequency != Outputs->HighFrequency) && (MrcData->Inputs.LpFreqSwitch == TRUE)) {
    // Lower CKE - change CLK frequency while DRAM is in Power Down
    CkeOn = 0;
    MrcGetSetDdrIoGroupChannel (MrcData, MAX_CHANNEL, GsmIocCkeOn, WriteNoCache, &CkeOn);
    Status = MrcFrequencySwitch (MrcData, Outputs->HighFrequency, DebugPrint);
    // Restore CKE
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (Outputs, Channel)) {
        CkeOn = Outputs->Controller[CONTROLLER_0].Channel[Channel].ValidCkeBitMask;
        MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmIocCkeOn, WriteNoCache, &CkeOn);
      }
    }
  }

  return Status;
}

/**
  This function performs the reset sequence required by JEDEC spec for LPDDR4.

  @param[in]  MrcData - Pointer to MRC global data.

  @retval MrcStatus - mrcSuccess if successful, else an error status.
**/
MrcStatus
MrcJedecResetLpddr4 (
  IN  MrcParameters *const  MrcData
  )
{
  MrcInput      *Inputs;
  MrcOutput     *Outputs;
  MRC_FUNCTION  *MrcCall;
  MrcStatus     Status;
  MrcVddSelect  VddVoltage;
  INT64         GetSetVal;
  UINT32        PciEBar;
  UINT32        tInit1;
  UINT32        tInit3;
  UINT32        tInit5;
  UINT32        Channel;
  UINT32        VddSettleWaitTime;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  MrcCall = Inputs->Call.Func;
  PciEBar = Inputs->PciEBaseAddress;
  Status  = mrcSuccess;
  tInit1  = MRC_LP4_tINIT1_US * MRC_TIMER_1US;
  tInit3  = MRC_LP4_tINIT3_US * MRC_TIMER_1US;
  tInit5  = MRC_LP4_tINIT5_US * MRC_TIMER_1US;

  // Wait till voltages are stable
  VddVoltage = Outputs->VddVoltage[Inputs->MemoryProfile];
  if ((VddVoltage != VDD_INVALID) && (Outputs->VddVoltageDone == FALSE)) {
    VddSettleWaitTime = 0;
    MrcVDDVoltageCheckAndSwitch (MrcData, VddVoltage, &VddSettleWaitTime);
  }

  // Assert DRAM RESET# signal after Voltage Ramp (Step 2)
  MrcCall->MrcDramReset (PciEBar, 0);

  // Force CKE low
  GetSetVal = 0;
  MrcGetSetDdrIoGroupChannel (MrcData, MAX_CHANNEL, GsmIocCkeOn, WriteNoCache, &GetSetVal);

  // Ensure tINIT1 (200us) before de-asserting DRAM reset. This will cover tINIT2 (10ns) as well.
  MrcWait (MrcData, tInit1);

  // De-Assert DRAM RESET# signal.
  MrcCall->MrcDramReset (PciEBar, 1);

  // Enable Dclk
  GetSetVal = 1;
  MrcGetSetDdrIoGroupController0 (MrcData, GsmMccEnableDclk, WriteNoCache, &GetSetVal);

  // Wait tINIT3 (2ms) - covers Min CKE low after RESET# high and tINIT4 (5tCK) - Min Stable CLK before CKE high
  MrcWait (MrcData, tInit3);

  // Set the valid CKE's
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      GetSetVal = Outputs->Controller[CONTROLLER_0].Channel[Channel].ValidCkeBitMask;
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmIocCkeOn, WriteNoCache, &GetSetVal);
    }
  }

  // Wait tINIT5: Min idle time before first MR[R,W] command.
  MrcWait (MrcData, tInit5);

  return Status;
}

/**
  This function converts from MRC training index to DRAM Vref encoding:
    Offset [-40:-11]  - Range 0 Vref 0 - 29 :: LP4 (10% - 21.6%) * 1100mV, LP4x (15%   - 32.3%) * 600mV.
    Offset [-10:40]   - Range 1 Vref 0 - 50 :: LP4 (22% - 42%)   * 1100mV, LP4x (32.9% - 62.9%) * 600mV.

  @param[in]  MrcData - Pointer to MRC global data.
  @param[in]  Offset  - Training index to convert.
  @param[out] Vref    - Pointer to return the Vref MR encoding.
  @param[out] Range   - Pointer to return the Vref range.

  @retval mrcSuccess              Input parameters are valid (LPDDR4 Spec).
  @retval mrcWrongInputParameter  Input parameters are invalid (LPDDR4 Spec).
**/
MrcStatus
MrcOffsetToVrefLpddr4 (
  IN  MrcParameters *const  MrcData,
  IN  INT32                 Offset,
  OUT UINT8                 *Range,
  OUT UINT8                 *Vref
  )
{
  MrcDebug  *Debug;
  MrcStatus Status;
  UINT8     MrRange;
  UINT8     MrVref;

  MrRange = 0;
  MrVref  = 0;
  Debug   = &MrcData->Outputs.Debug;
  Status  = mrcSuccess;

  if ((Offset > MRC_LP4_VREF_OFFSET_MAX) || (Offset < (-1 * MRC_LP4_VREF_OFFSET_MAX))) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Invalid Vref Setting %d is out of range [%d:%d]. Clamping\n",
      gErrString, Offset, (-1 * MRC_LP4_VREF_OFFSET_MAX), MRC_LP4_VREF_OFFSET_MAX);
    Status = mrcParamSaturation;
    if (Offset > MRC_LP4_VREF_OFFSET_MAX) {
      MrRange = 1;
      MrVref  = MRC_LP4_VREF_CODE_MAX;
    } else {
      MrRange = 0;
      MrVref  = 0;
    }
  } else if (Offset < -10) {
    MrRange = 0;
    MrVref  = (UINT8)(Offset + 40);
  } else {
    MrRange = 1;
    MrVref  = (UINT8)(Offset + 10);
  }

  MRC_DEBUG_ASSERT (((Range != NULL) && (Vref != NULL)), &MrcData->Outputs.Debug, "Null pointer\n");

  *Range  = MrRange;
  *Vref   = MrVref;

  return Status;
}

/**
  This function converts from DRAM Vref encoding to MRC training offset:
    Range 0 Vref [0:29] - Offset [-40:-11] :: LP4 (10% - 21.6%) * 1100mV, LP4x (15%   - 32.3%) * 600mV.
    Range 1 Vref [0:50] - Offset [-10: 40] :: LP4 (22% - 42%)   * 1100mV, LP4x (32.9% - 62.9%) * 600mV.

  @param[in]  Vref    - Vref MR encoding.
  @param[in]  Range   - Vref range.  Only 0 and 1 are valid.
  @param[out] Offset  - Pointer to return training index.

  @retval mrcSuccess              Input parameters are valid (LPDDR4 Spec).
  @retval mrcWrongInputParameter  Input parameters are invalid (LPDDR4 Spec).
**/
MrcStatus
MrcVrefEncToOffsetLpddr4 (
  IN  MrcParameters *const  MrcData,
  IN  UINT8                 Vref,
  IN  UINT8                 Range,
  OUT INT32                 *Offset
  )
{
  MrcStatus Status;
  INT32     TrainOffset;

  Status      = mrcSuccess;
  TrainOffset = 0;

  if (Range == 0) {
    if (Vref < 30) {
      TrainOffset = MRC_LP4_VREF_OFFSET_MIN;
    } else {
      Status = mrcWrongInputParameter;
    }
  } else if (Range == 1) {
    if (Vref < 51) {
      TrainOffset = -10;
    } else {
      Status = mrcWrongInputParameter;
    }
  } else {
    Status = mrcWrongInputParameter;
  }

  // If we're successful in the range check above, add the Vref encoding into TrainOffset.
  // Then place it in the output variable.
  if (Status == mrcSuccess) {
    TrainOffset += Vref;

    MRC_DEBUG_ASSERT (Offset != NULL, &MrcData->Outputs.Debug, "Null pointer\n");
    *Offset = TrainOffset;
  }

  return Status;
}

/**
  This function converts the Vref number in millivolts to the MRC training offset.
  This function will return the closest training offset.
    Range 0 Vref [0:29] - Offset [-40:-11] :: LP4 (10% - 21.6%) * 1100mV, LP4x (15%   - 32.3%) * 600mV.
    Range 1 Vref [0:50] - Offset [-10: 40] :: LP4 (22% - 42%)   * 1100mV, LP4x (32.9% - 62.9%) * 600mV.

  @param[in]  MrcData - Pointer to MRC global data.
  @param[in]  VrefMv  - Request Vref in millivolts.
  @param[out] Offset  - Pointer to return training index.

  @retval mrcSuccess              Input parameters are valid.
  @retval mrcWrongInputParameter  Input parameters are invalid.
**/
MrcStatus
MrcVrefToOffsetLpddr4 (
  IN  MrcParameters *const  MrcData,
  IN  UINT16                VrefMv,
  OUT INT32                 *Offset
  )
{
  MrcStatus Status;
  BOOLEAN   Lp4x;
  INT32     TrainOffset;
  UINT32    StepSizeUv;
  UINT32    VrefUv;
  UINT32    MinVrefUv;
  UINT32    MaxVrefUv;
  UINT32    OffsetVrefUv;

  Status  = mrcSuccess;
  Lp4x    = MrcData->Outputs.Lp4x;

  if (Lp4x) {
    MinVrefUv   = MRC_LP4X_VREF_MIN;
    MaxVrefUv   = MRC_LP4X_VREF_MAX;
    StepSizeUv  = MRC_LP4X_VREF_STEP_SIZE;
  } else {
    MinVrefUv   = MRC_LP4_VREF_MIN;
    MaxVrefUv   = MRC_LP4_VREF_MAX;
    StepSizeUv  = MRC_LP4_VREF_STEP_SIZE;
  }
  VrefUv = VrefMv * 1000;

  if (Offset == NULL) {
    MRC_DEBUG_ASSERT (1 == 0, &MrcData->Outputs.Debug, "Null pointer\n");
    Status = mrcWrongInputParameter;
  } else {
    if (VrefUv <= MinVrefUv) {
      TrainOffset = MRC_LP4_VREF_OFFSET_MIN;
    } else if (VrefUv >= MaxVrefUv) {
      TrainOffset = MRC_LP4_VREF_OFFSET_MAX;
    } else {
      // Subtract the minimum range, then do a divide round by the step size.
      // Then adjust the TrainOffset to the MRC encoding of offset by subtracting the
      // number of steps that are in the negative range of the margin range.
      OffsetVrefUv = VrefUv - MinVrefUv;
      TrainOffset = DIVIDEROUND (OffsetVrefUv, StepSizeUv);
      // Define is negative, so we can do an add here.
      TrainOffset += MRC_LP4_VREF_OFFSET_MIN;
    }

    *Offset = TrainOffset;
  }

  return Status;
}

/**
  Set Tx and CA DIMM Vref absolute Value for LDDR4.
                              LPDDR4      LPDDR4x
  MRC range [-40:+40] -  110mV:462mV 90mV:377.4mV
  Zero offset         -        286mV      233.4mV
  Step size           -        4.4mV        3.6mV
  Swing               -        352mV      287.4mV

  51 indexes (-10:40) on Range 1.
  30 indexes (-40:-11) on Range 0.

  @param[in, out] MrcData       - Include all MRC global data.
  @param[in]      VrefType      - The type of Vref to set
  @param[in]      Channel       - Channel to program.
  @param[in]      Rank          - Selecting which Rank to talk to.
  @param[in]      Offset        - Vref Offset to program.
  @param[in]      UpdateMrcData - Update MRC host struct.

  @retval mrcSuccess              - Within programmable range.
  @retval mrcWrongInputParameter  - Not in programmable range.
  @retval mrcDeviceBusy           - MRH could not complete MR write.
**/
MrcStatus
MrcSetVrefLpddr4 (
  IN  MrcParameters *const  MrcData,
  IN  UINT8                 VrefType,
  IN  UINT8                 Channel,
  IN  UINT8                 Rank,
  IN  INT32                 Offset,
  IN  BOOLEAN               UpdateMrcData
  )
{
  MrcOutput     *Outputs;
  MrcChannelOut *ChannelOut;
#if (defined (MRC_MEMORY_API_DEBUG) && (MRC_MEMORY_API_DEBUG == SUPPORT))
  MrcDebug    *Debug;
#endif
  MrcRankOut  *RankOut;
  MrcStatus   Status;
  UINT32      SubCh;
  UINT8       RankMask;
  UINT8       RankHalf;
  UINT8       RankMod2;
  UINT8       VrefCode;
  UINT8       Range;
  UINT16      *MrPtr;
  UINT8       MrAddress;
  LPDDR4_MODE_REGISTER_14_TYPE  Lpddr4Mr14;

  Status     = mrcSuccess;
  Outputs    = &MrcData->Outputs;
#if (defined (MRC_MEMORY_API_DEBUG) && (MRC_MEMORY_API_DEBUG == SUPPORT))
  Debug      = &Outputs->Debug;
#endif
  ChannelOut = &Outputs->Controller[0].Channel[Channel];
  RankMask   = ChannelOut->ValidRankBitMask;
  MrAddress  = (VrefType == CmdV) ? mrMR12 : mrMR14;
  Lpddr4Mr14.Data8 = 0;

  if (RankMask &  (1 << Rank)) {
    RankHalf = Rank / 2;
    RankMod2 = Rank % 2;
    RankOut = &ChannelOut->Dimm[RankHalf].Rank[RankMod2];
    MrPtr = RankOut->MR;

    Status = MrcOffsetToVrefLpddr4 (MrcData, Offset, &Range, &VrefCode);
    Lpddr4Mr14.Bits.DqVref = VrefCode;
    Lpddr4Mr14.Bits.DqVrefRange = Range;
    MRC_API_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Channel%d, Rank%d, Requested Offset %d, VrefCode 0x%X, Range %d\n", Channel, Rank, Offset, VrefCode, Range);

    for (SubCh = 0; SubCh < MAX_SUB_CHANNEL; SubCh++) {
      if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
        Status = MrcIssueMrw (
                  MrcData,
                  Channel,
                  SubCh,
                  Rank,
                  MrAddress,
                  Lpddr4Mr14.Data8,
                  FALSE,  // InitMrw
                  FALSE,  // ChipSelect2N
                  FALSE   // DebugPrint
                  );
        if (Status != mrcSuccess) {
          return Status;
        }
      }
    } // for SubCh
    MrcWait (MrcData, MRC_LP4_tVREFCA_LONG_NS * MRC_TIMER_1NS);

    if (UpdateMrcData) {
      if (VrefType == CmdV) {
        Status = MrcLpddr4SetMr12 (MrcData, VrefCode, Range, MRC_IGNORE_ARG_8, &MrPtr[mrIndexMR12]);
      } else {
        Status = MrcLpddr4SetMr14 (MrcData, VrefCode, Range, &MrPtr[mrIndexMR14]);
      }
    }
  }
  return Status;
}

/**
  This function selects the ODT table according to the board type.

  @param[in] MrcData         - Include all the MRC general data.
  @param[in] Dimm            - selected DIMM.
  @param[in] OdtIndex        - selected ODT index.

  @retval TOdtValueDdr4 * - Pointer to the relevant table or NULL if the table was not found.
**/
TOdtValueLpddr4 *
SelectTable_LPDDR4 (
  IN MrcParameters *const MrcData,
  IN const UINT8          Dimm,
  IN const TOdtIndex      OdtIndex
  )
{
  MrcDebug        *Debug;
  MrcOutput       *Outputs;
  TOdtValueLpddr4 *OdtTable;

  Outputs  = &MrcData->Outputs;
  Debug    = &Outputs->Debug;
  OdtTable = NULL;

  if ((OdtIndex >= 2) || (Dimm > 0)) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Error: Lpddr4OdtTable array out of bounds! OdtIndex: %u, Dimm: %u\n", OdtIndex, Dimm);
    return NULL;
  }
  OdtTable = (TOdtValueLpddr4 *) &Lpddr4OdtTable[Dimm][OdtIndex];

  return OdtTable;
}

/**
  Lpddr4 Set DimmParamValue is responsible for performing the concrete set DIMM parameter to value,
  using Lpddr4 specific MR set functions.
  Parameters supported: OptDimmRon, OptDimmOdtWr

  @param[in,out]  MrcData         - Include all MRC global data.
  @param[in,out]  MrData          - Pointer to the MR data to update.
  @param[in]      OptParam        - The Dimm Opt Param (e.g., OptDimmRon, OptDimmOdtWr, OptDimmOdtPark, OptDimmOdtNom)
  @param[in]      ParamValue      - The actual values (Typically in Ohms)

  @retval MrcStatus - mrcWrongInputParameter if unsupported OptParam
                    - MrcStatus of the MR set functions otherwise

**/
MrcStatus
Lpddr4SetDimmParamValue (
  IN OUT MrcParameters *const MrcData,
  IN OUT UINT16        *const MrData,
  IN     UINT8                OptParam,
  IN     UINT16               ParamValue
  )
{
  MrcDebug        *Debug;
  MrcStatus       Status;

  Debug = &MrcData->Outputs.Debug;

  switch (OptParam) {

    case OptDimmRon:
      // DIMM RON
      Status = MrcLpddr4SetMr3 (MrcData, MRC_IGNORE_ARG_8, ParamValue, MrData);
      break;

    case OptDimmOdtWr:
      // DIMM RTT WR
      Status = MrcLpddr4SetMr11 (MrcData, ParamValue, MRC_IGNORE_ARG_8, MrData);
      break;

    case OptDimmOdtCA:
      // DIMM ODT CA
      Status = MrcLpddr4SetMr11 (MrcData, MRC_IGNORE_ARG_8, ParamValue, MrData);
      break;

    case OptDimmSocOdt:
      // SOC ODT
      Status = MrcLpddr4SetMr22 (MrcData, ParamValue, MRC_IGNORE_ARG_8, MRC_IGNORE_ARG_8, MRC_IGNORE_ARG_8, MrData);
      break;

    default:
      Status = mrcWrongInputParameter;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s %u ", gWrongInputParam, OptParam);
      break;
  }


  return Status;
}


/**
  Lppdr4 Get the MR value and its corresponding index for a given DIMM Opt Param.
  Value is set by reference to the corresponding pointers.

  @param[in]      MrcData     - Include all MRC global data.
  @param[in]      OptParam    - The Dimm Opt Param (e.g., OptDimmRon, OptDimmOdtWr, OptDimmOdtPark, OptDimmOdtNom)
  @param[out]     *MrIndex    - Updated Pointer to the MR index.
  @param[out]     *MrNum      - Updated Pointer to the MR number.

  @retval MrcStatus - mrcWrongInputParameter if unsupported OptParam,
                      mrcSuccess             otherwise
**/
MrcStatus
Lpddr4GetOptDimmParamMrIndex (
  IN MrcParameters *const MrcData,
  IN UINT8                OptDimmParam,
  OUT UINT8               *MrIndex,
  OUT UINT8               *MrNum
)
{
  MrcDebug          *Debug;
  MrcStatus         Status;

  Status = mrcSuccess;
  Debug = &MrcData->Outputs.Debug;

  switch (OptDimmParam) {

  case OptDimmRon:
    // DIMM RON
    *MrIndex = mrIndexMR3;
    *MrNum   = mrMR3;
    break;

  case OptDimmOdtCA:
  case OptDimmOdtWr:
    // DIMM RTT WR or DIMM ODT CA
    *MrIndex = mrIndexMR11;
    *MrNum  = mrMR11;
    break;

  case OptDimmSocOdt:
    // SOC ODT
    *MrIndex = mrIndexMR22;
    *MrNum   = mrMR22;
    break;

  default:
    *MrIndex = 0xFF;
    *MrNum  = 0xFF;
    Status = mrcWrongInputParameter;
    MRC_DEBUG_MSG(Debug, MSG_LEVEL_ERROR, "%s %u ", gWrongInputParam, OptDimmParam);
    break;

  }

  return Status;
}

/**
  This function configures MR22 on FSP 0 and FSP 1 to the same value.

  @param[in] MrcData - Pointer to global MRC data.

  @retval Nothing.
**/
MrcStatus
Lpddr4FspSetStaticMrs (
  IN MrcParameters *const MrcData
  )
{
  MrcOutput         *Outputs;
  MrcChannelOut     *ChannelOut;
  MrcControllerOut  *ControllerOut;
  MrcStatus         Status;
  MrcStatus         CurStatus;
  UINT32            Channel;
  UINT32            Rank;
  UINT32            SubCh;
  UINT16            *MrList;

  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];

  // MRC works with FSP-1 as the training point.  FSP-0 is used for reset.  So we start with FSP-WR/OP = 1
  // Set FSP-WR = 0
  Status = Lpddr4SetFsp (MrcData, ALL_CHANNEL_MASK, ALL_SUB_CH_MASK, ALL_RANK_MASK, MRC_IGNORE_ARG_8, Lp4FspWePoint0, MRC_IGNORE_ARG_8);

  // Write MR22 to FSP-0
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut  = &ControllerOut->Channel[Channel];
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel) == 0) {
        continue;
      }
      MrList = &ChannelOut->Dimm[Rank / 2].Rank[Rank % 2].MR[0];
      // Send out MR's to DRAM.
      for (SubCh = 0; SubCh < MAX_SUB_CHANNEL; SubCh++) {
        if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
          continue;
        }
        CurStatus = MrcIssueMrw (
                      MrcData,
                      Channel,
                      SubCh,
                      Rank,
                      mrMR22,
                      MrList[mrIndexMR22],
                      FALSE,  // InitMrw
                      FALSE,  // ChipSelect2N
                      TRUE// DebugPrint
                      );
        if (Status == mrcSuccess) {
          Status = CurStatus;
        }
      } // SubCh
    } // Rank
  } // Channel

  // Set FSP-WR = 1 to match the previous flow
  CurStatus = Lpddr4SetFsp (MrcData, ALL_CHANNEL_MASK, ALL_SUB_CH_MASK, ALL_RANK_MASK, MRC_IGNORE_ARG_8, Lp4FspWePoint1, MRC_IGNORE_ARG_8);
  if (Status == mrcSuccess) {
    Status = CurStatus;
  }

  return Status;
}

/**
  LPDDR4 get available values and the number of possible values of a given DimmOptParam.

  @param[in]      MrcData               - Include all MRC global data.
  @param[in]      DimmOptParam          - e.g., OptDimmOdtWr, OptDimmOdtNom, OptDimmOdtPark, OptDimmRon
  @param[out]     **DimmOptParamVals    - Reference to the pointer of values.
  @param[out]     *NumDimmOptParamVals  - Reference to the number of values.

  @retval MrcStatus - mrcWrongInputParameter if unsupported OptParam
                      mrcSuccess             otherwise
**/
MrcStatus
Lpddr4GetDimmOptParamValues (
  IN MrcParameters *const MrcData,
  IN UINT8                DimmOptParam,
  OUT UINT16              **DimmOptParamVals,
  OUT UINT8               *NumDimmOptParamVals)
{

  static const UINT16    Lpddr4DimmRonVals[]  = { 240, 120, 80, 60, 48, 40 };              // LPDDR4 Pull Down Drive Strength in Ohms
  static const UINT16    Lpdr4DimmRttWrVals[] = { 120, 80, 60, 48, 40 };          // LPDDR4 RttWr Values in Ohms, not included 0xFFFF, 240,
  MrcDebug               *Debug;
  MrcStatus              Status;

  Debug   = &MrcData->Outputs.Debug;
  Status  = mrcSuccess;

  switch (DimmOptParam) {
    case OptDimmOdtCA:
    case OptDimmOdtWr:
      // DIMM RTT_WR / DIMM CA_ODT
      *DimmOptParamVals    =    (UINT16 *) Lpdr4DimmRttWrVals;
      *NumDimmOptParamVals = ARRAY_COUNT (Lpdr4DimmRttWrVals);
      break;

    case OptDimmRon:
      // DIMM RON
      *DimmOptParamVals    =    (UINT16 *) Lpddr4DimmRonVals;
      *NumDimmOptParamVals = ARRAY_COUNT (Lpddr4DimmRonVals);
      break;

    case OptDimmOdtNom:
    case OptDimmOdtPark:
    default:
      *DimmOptParamVals    = (UINT16 *)NULL;
      *NumDimmOptParamVals = 0;
      Status = mrcWrongInputParameter;
      MRC_DEBUG_MSG(Debug, MSG_LEVEL_ERROR, "%s %u ", gWrongInputParam, DimmOptParam);
      break;
  }

  return Status;
}

/**
  Used to update TxVref and CaVref for LPDDR4.
  Uses input offset value to increment/decrement current setting.

  @param[in,out] MrcData       - Include all MRC global data.
  @param[in]     Channel       - Selecting which Channel to talk to.
  @param[in]     RankMask      - Selecting which Ranks to talk to.
  @param[in]     VrefType      - Determines the Vref type to change, only CmdV and TxVref are valid.
  @param[in]     Offset        - Vref offset value.
  @param[in]     UpdateMrcData - Used to decide if Mrc host must be updated.
  @param[in]     IsCachedOffsetParam - Determines if the paramter is an offset (relative to cache) or absolute value.

  @retval MrcStatus - mrcWrongInputParameter if unsupported OptParam,  mrcSuccess otherwise
**/
MrcStatus
Lpddr4SetDramVref (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Channel,
  IN     UINT8                RankMask,
  IN     UINT8                VrefType,
  IN     INT32                Offset,
  IN     BOOLEAN              UpdateMrcData,
  IN     BOOLEAN              IsCachedOffsetParam
  )
{
  MrcDebug                     *Debug;
  MrcOutput                    *Outputs;
  MrcChannelOut                *ChannelOut;
  MrcRankOut                   *RankOut;
  UINT16                       *MrPtr;
  UINT8                        Rank;
  UINT8                        RankHalf;
  UINT8                        RankMod2;
  UINT8                        MrIndex;
  INT32                        CurrentOffset;
  MrcStatus                    Status;
  LPDDR4_MODE_REGISTER_14_TYPE Lpddr4VrefMr; // Register struct is common to CaVref and TxVref

  Outputs            = &MrcData->Outputs;
  Debug              = &Outputs->Debug;
  ChannelOut         = &Outputs->Controller[0].Channel[Channel];
  Outputs            = &MrcData->Outputs;
  Status             = mrcSuccess;
  MrIndex            = 0;
  CurrentOffset      = 0;
  Lpddr4VrefMr.Data8 = 0;

  switch (VrefType) {
    case CmdV:
      MrIndex = mrIndexMR12;
      break;

    case WrV:
      MrIndex = mrIndexMR14;
      break;

    default:
      Status = mrcWrongInputParameter;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s %u ", gWrongInputParam, VrefType);
      break;
  }

  if (Status != mrcSuccess) {
    return Status;
  }

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if ((MrcRankInChannelExist (MrcData, Rank, Channel)) && (RankMask & (1 << Rank))) {
      RankHalf = Rank / 2;
      RankMod2 = Rank % 2;
      RankOut = &ChannelOut->Dimm[RankHalf].Rank[RankMod2];
      MrPtr = RankOut->MR;

      if (IsCachedOffsetParam) {
        // Offset value.  Calculate the new Vref.
        Lpddr4VrefMr.Data8 = (UINT8) MrPtr[MrIndex];
        MrcVrefEncToOffsetLpddr4 (MrcData, Lpddr4VrefMr.Bits.DqVref, Lpddr4VrefMr.Bits.DqVrefRange, &CurrentOffset);
//      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Lpddr4SetDramVref - IsCachedOffsetParam: Rank: %d, MR14: 0x%02X, CurentOffset: %d, Offset: %d\n", Rank, Lpddr4VrefMr.Data8, CurrentOffset, Offset);
        CurrentOffset += Offset;
      } else {
        // For Non-Cached OffsetParam set value as-is
        CurrentOffset = Offset;
      }
      MrcSetVrefLpddr4 (MrcData, VrefType, Channel, Rank, CurrentOffset, UpdateMrcData);
    }

  }
  return Status;
}

