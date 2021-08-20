/** @file
  Implementation of LPDDR5 Specific functions, and constants.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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
#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcInterface.h"
#include "MrcHalRegisterAccess.h"
#include "MrcLpddr5Registers.h"
#include "MrcCommon.h"
#include "MrcMaintenance.h"
#include "MrcChipApi.h"
#include "MrcMemoryApi.h"
#include "MrcLpddr4.h"
#include "MrcLpddr5.h"
#include "MrcDdrIoOffsets.h"

///
/// Defines
///
#define LP5_INIT_NUM_MR         (20)

///
/// Timing Frequency Range defines
///
#define LP5_TFR_MIN (0)
#define LP5_TFR_MAX (1)
#define LP5_TFR_NUM_ENTRIES   (Lp5Wl4t1BMax)
#define LP5_ODTL_NUM_ENTRIES  (Lp5Wl4t1BMax)
#define LP5_TFR_UPPER_LIMIT (1)
#define LP5_TFR_LOWER_LIMIT (0)

typedef struct {
  UINT32  Frequency;
  INT8    WrOdtlOn;
  INT8    WrOdtlOff;
  INT8    RdOdtlOn[3];
  INT8    RdOdtlOff[3];
} LP5_ODTL_TIMING_TYPE;

///
/// Local Constants
///
// This table is based on the the following timing tables from LPDDR5 JEDEC spec:
//  Table 22 - Read Latencies and Read with AP to Activate
//  Table 23 - Write Latency
//  Table 24 - Write Recovery time
// The frequency for the entry being programmed must be greater than the minimum and
// less than or equal to the maximum.
static const MrcFrequency TimingFreqRangeLp5[LP5_TFR_NUM_ENTRIES][2] = {
  {fNoInit, f533},
  {f533,    f1067},
  {f1067,   f1600},
  {f1600,   f2133},
  {f2133,   f2750},
  {f2750,   f3200},
  {f3200,   f3733},
  {f3733,   f4267},
  {f4267,   f4800},
  {f4800,   f5500},
  {f5500,   f6000},
  {f6000,   fInvalid}};

// LPDDR4 ODT Values
// ODT values are in this order: { RttWr, RttCa }
const TOdtValueLpddr Lpddr5OdtTable[MAX_DIMMS_IN_CHANNEL][2] = {
/// 1DPC 1R,  1DPC 2R
  {{40, 60},  {40, 60}},
};

/**
  This function checks that the Vref requested is within the spec defined range for LPDDR5.

  @param[in]  MrcData   - Pointer to global MRC data.
  @param[in]  Vref      - Requested Vref in mV
  @param[in]  VrefType  - CmdV or WrV

  @param  UINT16 - The requested Vref or a clamped Vref value.
**/
UINT16
CheckVrefLimitsLpddr5 (
  IN  MrcParameters   *MrcData,
  IN  UINT16          Vref,
  IN  MRC_MarginTypes VrefType
  )
{
  UINT16  RetVref;
  UINT16  MinVref;
  UINT16  MaxVref;
#ifdef MRC_DEBUG_PRINT
  UINT32  ErrorLimit;
#endif

  MinVref = LP5_VREF_MIN_MV;
  if (VrefType == CmdV) {
    MaxVref = LP5_CA_VREF_MAX;
  } else {
    // WrV
    MaxVref = (MrcData->Outputs.HighFrequency <= f1600) ? LP5_DQ_VREF_LOW_F_MAX : LP5_DQ_VREF_HIGH_F_MAX;
  }

#ifdef MRC_DEBUG_PRINT
  ErrorLimit = 0;
  if (Vref < MinVref) {
    ErrorLimit = MinVref;
  } else if (Vref > MaxVref) {
    ErrorLimit = MaxVref;
  }
  if (ErrorLimit != 0) {
    MRC_DEBUG_MSG (
      &MrcData->Outputs.Debug,
      MSG_LEVEL_WARNING,
      "%s %s %u violates spec limit: %u\n",
      gWarnString,
      gMarginTypesStr[VrefType],
      Vref,
      ErrorLimit
      );
  }
#endif
  RetVref = RANGE (Vref, MinVref, MaxVref);

  return RetVref;
}

/**
  This function selects the initial optimal DQ ODT value based on target frequency.

  @param[in] Freq - Target Frequency.

  @retval UINT16 - ODT Value
**/
UINT16
DqOdtByFreqLpddr5 (
  IN  MrcFrequency  Freq
  )
{
  UINT16 DqOdt;

  if (Freq <= f2400) {
    DqOdt = 240;
  } else if (Freq <= f3200) {
    DqOdt = 120;
  } else if (Freq <= f4200) {
    DqOdt = 60;
  } else {
    DqOdt = 40;
  }

  return DqOdt;
}
/**
  This functions checks to see if the requested latency is within the frequency range
  required by JEDEC.

  @param[in]  MrcData - Pointer to MRC global data.
  @param[in]  Latency - Encoded latency entry.  Supports Read Latency, Write Latency, tWR, and tRTP.

  @retval MrcStatus - mrcSuccess if Latency is valid and the frequency is in the range.  Else mrcWrongInputParameter.
**/
MrcStatus
LatencyFreqCheckLpddr5 (
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
  if ((Latency >= 0) && (Latency < LP5_TFR_NUM_ENTRIES)) {
    CurFreq = MrcData->Outputs.HighFrequency;
    MaxFreq = TimingFreqRangeLp5[(UINT8) Latency][LP5_TFR_MAX];
    MinFreq = TimingFreqRangeLp5[(UINT8) Latency][LP5_TFR_MIN];

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
      LP5_TFR_NUM_ENTRIES
      );
  }

  return Status;
}

/**
  This function selects the ODT table according to the board type.

  @param[in] MrcData  - Include all the MRC general data.
  @param[in] Dimm     - selected DIMM.
  @param[in] OdtIndex - selected ODT index.

  @retval TOdtValueLpddr * - Pointer to the relevant table or NULL if the table was not found.
**/
TOdtValueLpddr *
SelectTable_LPDDR5 (
  IN MrcParameters *const MrcData,
  IN const UINT32         Dimm,
  IN const TOdtIndex      OdtIndex
  )
{
  MrcDebug        *Debug;
  MrcOutput       *Outputs;
  TOdtValueLpddr  *OdtTable;

  Outputs  = &MrcData->Outputs;
  Debug    = &Outputs->Debug;
  OdtTable = NULL;

  if ((OdtIndex >= 2) || (Dimm > 0)) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Error: Lpddr4OdtTable array out of bounds! OdtIndex: %u, Dimm: %u\n", OdtIndex, Dimm);
    return NULL;
  }
  //@todo: Bytemode.
  OdtTable = (TOdtValueLpddr *) &Lpddr5OdtTable[Dimm][OdtIndex];

  return OdtTable;
}

/**
  This function converts from DRAM Vref encoding to MRC training offset:
  Vref [10:127] - Offset [-58:58] :: LP5 (15% - 73.5%) * 500mV.

  @param[in]  MrcData - Pointer to global MRC data.
  @param[in]  Vref    - Vref MR encoding.
  @param[out] Offset  - Pointer to return training index.

  @retval mrcSuccess              Input parameters are valid (LPDDR5 Spec).
  @retval mrcWrongInputParameter  Input parameters are invalid (LPDDR5 Spec).
**/
MrcStatus
MrcVrefEncToOffsetLpddr5 (
  IN  MrcParameters *const  MrcData,
  IN  UINT8                 Vref,
  OUT INT32                 *Offset
)
{
  MrcStatus Status;
  UINT32    TrainOffset;

  Status = mrcSuccess;
  TrainOffset = 0;

  if (Vref < 10) {
    Status = mrcWrongInputParameter;
  } else {
    TrainOffset = Vref - (LP5_VREF_OFFSET_MAX + 10);

    MRC_DEBUG_ASSERT (Offset != NULL, &MrcData->Outputs.Debug, "Null pointer\n");
    *Offset = TrainOffset;
  }

  return Status;
}

/**
  This function converts the Vref number in millivolts to the MRC training offset.
  LPDDR5 has one flat range from 15% of VDDq to 75% of VDDq.

  @param[in]  MrcData - Pointer to MRC global data.
  @param[in]  VrefMv  - Request Vref in millivolts.
  @param[out] Offset  - Pointer to return training index.

  @retval mrcSuccess              Input parameters are valid.
  @retval mrcWrongInputParameter  Input parameters are invalid.
**/
MrcStatus
VrefToOffsetLpddr5 (
  IN  MrcParameters *const  MrcData,
  IN  UINT16                VrefMv,
  OUT INT32                 *Offset
  )
{
  MrcStatus Status;
  INT32     TrainOffset;
  UINT32    StepSizeUv;
  UINT32    VrefUv;
  UINT32    MinVrefUv;
  UINT32    MaxVrefUv;
  UINT32    OffsetVrefUv;

  Status  = mrcSuccess;

  MinVrefUv   = LP5_VREF_MIN_UV;
  MaxVrefUv   = LP5_VREF_MAX;
  StepSizeUv  = LP5_VREF_STEP_SIZE;
  VrefUv = VrefMv * 1000;

  if (Offset == NULL) {
    MRC_DEBUG_ASSERT (1 == 0, &MrcData->Outputs.Debug, "Null pointer\n");
    Status = mrcWrongInputParameter;
  } else {
    if (VrefUv <= MinVrefUv) {
      TrainOffset = LP5_VREF_OFFSET_MIN;
    } else if (VrefUv >= MaxVrefUv) {
      TrainOffset = LP5_VREF_OFFSET_MAX;
    } else {
      // Subtract the minimum range, then do a divide round by the step size.
      OffsetVrefUv = VrefUv - MinVrefUv;
      TrainOffset = LP5_VREF_OFFSET_MIN + DIVIDEROUND (OffsetVrefUv, StepSizeUv);
    }

    *Offset = TrainOffset;
  }

  return Status;
}

/**
  This function converts from the integer defined Write Latency to the Mode Register
  encoding of the timing in LPDDR5.

  @param[in]  MrcData - Pointer to global MRC data.
  @param[in]  Value   - Requested Write Latency value.
  @param[out] EncVal  - Encoded Mode Register value.

  @retval MrcStatus - mrcSuccess if the latency is supported.  Else mrcWrongInputParameter.
**/
MrcStatus
EncodeWriteLatencyLpddr5 (
  IN  MrcParameters *MrcData,
  IN  UINT16        Value,
  OUT UINT8         *EncVal
  )
{
  MrcDebug  *Debug;
  MrcStatus Status;
  UINT8     MrValue;

  Debug = &MrcData->Outputs.Debug;
  Status = mrcSuccess;

  switch (Value) {
    case 2:
      MrValue = Lp5Wl4t1B2;
      break;

    case 3:
      MrValue = Lp5Wl4t1B3;
      break;

    case 4:
      MrValue = Lp5Wl4t1B4;
      break;

    case 5:
      MrValue = Lp5Wl4t1B5;
      break;

    case 7:
      MrValue = Lp5Wl4t1B7;
      break;

    case 8:
      MrValue = Lp5Wl4t1B8;
      break;

    case 9:
      MrValue = Lp5Wl4t1B9;
      break;

    case 11:
      MrValue = Lp5Wl4t1B11;
      break;

    case 12:
      MrValue = Lp5Wl4t1B12;
      break;

    case 14:
      MrValue = Lp5Wl4t1B14;
      break;

    case 15:
      MrValue = Lp5Wl4t1B15;
      break;

    case 16:
      MrValue = Lp5Wl4t1B16;
      break;

    default:
      MrValue = 0xFF;
      Status = mrcWrongInputParameter;
      break;
  }

  if (MrValue != 0xFF) {
    // Check to see if the time requested matches JEDEC Frequency table
    Status = LatencyFreqCheckLpddr5 (MrcData, MrValue);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, (Status != mrcSuccess) ? " (WL)\n" : "");
    if (EncVal != NULL) {
      *EncVal = MrValue;
    } else {
      Status = mrcWrongInputParameter;
    }
  } else {
    Status = mrcWrongInputParameter;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Invalid %s Latency Value: %d\n", gErrString, gWrString, Value);
  }

  return Status;
}

/**
  This function converts from the integer defined Write Recovery to the Mode Register
  encoding of the timing in LPDDR5.

  @param[in]  MrcData - Pointer to global MRC data.
  @param[in]  Value   - Requested Write Recovery value.
  @param[out] EncVal  - Encoded Mode Register value.

  @retval MrcStatus - mrcSuccess if the latency is supported.  Else mrcWrongInputParameter.
**/
MrcStatus
EncodeWriteRecoveryLpddr5 (
  IN  MrcParameters *MrcData,
  IN  UINT16        Value,
  OUT UINT8         *EncVal
  )
{
  MrcDebug  *Debug;
  MrcStatus Status;
  UINT8     MrValue;

  Debug = &MrcData->Outputs.Debug;
  Status = mrcSuccess;

  if (MrcData->Outputs.LpByteMode) {
    switch (Value) {
      case 3:
        MrValue = Lp5Wr4t1X8_3;
        break;

      case 5:
        MrValue = Lp5Wr4t1X8_5;
        break;

      case 8:
        MrValue = Lp5Wr4t1X8_8;
        break;

      case 10:
        MrValue = Lp5Wr4t1X8_10;
        break;

      case 13:
        MrValue = Lp5Wr4t1X8_13;
        break;

      case 15:
        MrValue = Lp5Wr4t1X8_15;
        break;

      case 17:
        MrValue = Lp5Wr4t1X8_17;
        break;

      case 20:
        MrValue = Lp5Wr4t1X8_20;
        break;

      case 22:
        MrValue = Lp5Wr4t1X8_22;
        break;

      case 25:
        MrValue = Lp5Wr4t1X8_25;
        break;

      case 28:
        MrValue = Lp5Wr4t1X8_28;
        break;

      case 29:
        MrValue = Lp5Wr4t1X8_29;
        break;

      default:
        MrValue = 0xFF;
        Status = mrcWrongInputParameter;
        break;
    }
  } else {
    switch (Value) {
      case 3:
        MrValue = Lp5Wr4t1X16_3;
        break;

      case 5:
        MrValue = Lp5Wr4t1X16_5;
        break;

      case 7:
        MrValue = Lp5Wr4t1X16_7;
        break;

      case 10:
        MrValue = Lp5Wr4t1X16_10;
        break;

      case 12:
        MrValue = Lp5Wr4t1X16_12;
        break;

      case 14:
        MrValue = Lp5Wr4t1X16_14;
        break;

      case 16:
        MrValue = Lp5Wr4t1X16_16;
        break;

      case 19:
        MrValue = Lp5Wr4t1X16_19;
        break;

      case 21:
        MrValue = Lp5Wr4t1X16_21;
        break;

      case 24:
        MrValue = Lp5Wr4t1X16_24;
        break;

      case 26:
        MrValue = Lp5Wr4t1X16_26;
        break;

      case 28:
        MrValue = Lp5Wr4t1X16_28;
        break;

      default:
        MrValue = 0xFF;
        Status = mrcWrongInputParameter;
        break;
    }
  }

  if (MrValue != 0xFF) {
    // Check to see if the time requested matches JEDEC Frequency table
    // @todo: Spec has conflict with itself
    //Status = LatencyFreqCheckLpddr5 (MrcData, MrValue);
    //MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, (Status != mrcSuccess) ? " (WR)\n" : "");
    if (EncVal != NULL) {
      *EncVal = MrValue;
    } else {
      Status = mrcWrongInputParameter;
    }
  } else {
    Status = mrcWrongInputParameter;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Unsupported Write Recovery value\n", gErrString);
  }

  return Status;
}

/**
  This function converts from the integer defined Read Latency to the Mode Register
  encoding of the timing in LPDDR5.

  @param[in]  MrcData - Pointer to global MRC data.
  @param[in]  Value   - Requested Read Latency value.
  @param[out] EncVal  - Encoded Mode Register value.

  @retval MrcStatus - mrcSuccess if the latency is supported.  Else mrcWrongInputParameter.
**/
MrcStatus
EncodeReadLatencyLpddr5 (
  IN  MrcParameters *MrcData,
  IN  UINT16        Value,
  OUT UINT8         *EncVal
  )
{
  MrcDebug  *Debug;
  MrcStatus Status;
  UINT8     MrValue;

  Debug = &MrcData->Outputs.Debug;
  Status = mrcSuccess;

  if (MrcData->Outputs.LpByteMode) {
    switch (Value) {
      case 3:
        MrValue = Lp5RlRbtp4t1X8_3;
        break;

      case 4:
        MrValue = Lp5RlRbtp4t1X8_4;
        break;

      case 5:
        MrValue = Lp5RlRbtp4t1X8_5;
        break;

      case 7:
        MrValue = Lp5RlRbtp4t1X8_7;
        break;

      case 8:
        MrValue = Lp5RlRbtp4t1X8_8;
        break;

      case 10:
        MrValue = Lp5RlRbtp4t1X8_10;
        break;

      case 11:
        MrValue = Lp5RlRbtp4t1X8_11;
        break;

      case 13:
        MrValue = Lp5RlRbtp4t1X8_13;
        break;

      case 14:
        MrValue = Lp5RlRbtp4t1X8_14;
        break;

      case 16:
        MrValue = Lp5RlRbtp4t1X8_16;
        break;

      case 17:
        MrValue = Lp5RlRbtp4t1X8_17;
        break;

      case 18:
        MrValue = Lp5RlRbtp4t1X8_18;
        break;

      default:
        MrValue = 0xFF;
        Status = mrcWrongInputParameter;
        break;
    }
  } else {
    switch (Value) {
      case 3:
        MrValue = Lp5RlRbtp4t1X16_3;
        break;

      case 4:
        MrValue = Lp5RlRbtp4t1X16_4;
        break;

      case 5:
        MrValue = Lp5RlRbtp4t1X16_5;
        break;

      case 6:
        MrValue = Lp5RlRbtp4t1X16_6;
        break;

      case 8:
        MrValue = Lp5RlRbtp4t1X16_8;
        break;

      case 9:
        MrValue = Lp5RlRbtp4t1X16_9;
        break;

      case 10:
        MrValue = Lp5RlRbtp4t1X16_10;
        break;

      case 12:
        MrValue = Lp5RlRbtp4t1X16_12;
        break;

      case 13:
        MrValue = Lp5RlRbtp4t1X16_13;
        break;

      case 15:
        MrValue = Lp5RlRbtp4t1X16_15;
        break;

      case 16:
        MrValue = Lp5RlRbtp4t1X16_16;
        break;

      case 17:
        MrValue = Lp5RlRbtp4t1X16_17;
        break;

      default:
        MrValue = 0xFF;
        Status = mrcWrongInputParameter;
        break;
    }
  }

  if (MrValue != 0xFF) {
    // Check to see if the time requested matches JEDEC Frequency table
    Status = LatencyFreqCheckLpddr5 (MrcData, MrValue);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, (Status != mrcSuccess) ? " (RL)\n" : "");
    if (EncVal != NULL) {
      *EncVal = MrValue;
    } else {
      Status = mrcWrongInputParameter;
    }
  } else {
    Status = mrcWrongInputParameter;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Invalid %s Latency Value: %d\n", gErrString, gRdString, Value);
  }

  return Status;
}

/**
  This function searches through the Frequency Range table to find out what Bin index
  the current Frequency is in for Timing parameters that are Bin based.

  @param[in]  Frequency - Data Rate

  @param[in]  UINT8 - Frequency Bin Index
**/

UINT8
GetFreqBinIndex (
  IN  MrcFrequency Frequency
  )
{
  UINT8 Bin;
  UINT32 Lower;
  UINT32 Upper;

  for (Bin = 0; Bin < LP5_TFR_NUM_ENTRIES; Bin++) {
    Lower = TimingFreqRangeLp5[Bin][LP5_TFR_LOWER_LIMIT];
    Upper = TimingFreqRangeLp5[Bin][LP5_TFR_UPPER_LIMIT];
    if ((Lower < Frequency) &&
        (Upper >= Frequency)) {
      break;
    }
  }

  return Bin;
}

/**
  This function converts from MRC training index to DRAM Vref encoding:
    Vref [10:127] - Offset [-58:58] :: LP5 (15% - 73.5%) * 500mV.

  @param[in]  MrcData - Pointer to MRC global data.
  @param[in]  Offset  - Training index to convert.
  @param[out] Vref    - Pointer to return the Vref MR encoding.

  @retval mrcSuccess              Input parameters are valid (LPDDR5 Spec).
  @retval mrcWrongInputParameter  Input parameters are invalid (LPDDR5 Spec).
**/
MrcStatus
MrcOffsetToVrefLpddr5 (
  IN  MrcParameters *const  MrcData,
  IN  INT32                 Offset,
  OUT UINT8                 *Vref
  )
{
  MrcDebug  *Debug;
  MrcStatus Status;
  UINT8     MrVref;

  MrVref  = 0;
  Debug   = &MrcData->Outputs.Debug;
  Status  = mrcSuccess;

  if ((Offset > LP5_VREF_OFFSET_MAX) || (Offset < LP5_VREF_OFFSET_MIN)) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Invalid Vref Setting %d is out of range [%d:%d]. Clamping\n",
      gErrString, Offset, LP5_VREF_OFFSET_MIN, LP5_VREF_OFFSET_MAX);
    Status = mrcParamSaturation;
    if (Offset > LP5_VREF_OFFSET_MAX) {
      Offset  = LP5_VREF_OFFSET_MAX;
    } else {
      Offset  = LP5_VREF_OFFSET_MIN;
    }
  }

  // MIN Offset is -58 -> 10  Vref MR Encoding
  // MAX Offset is +58 -> 126 Vref MR Encondig
  MrVref = (UINT8) Offset + 68;

  MRC_DEBUG_ASSERT (((Vref != NULL)), &MrcData->Outputs.Debug, "Null pointer\n");

  *Vref   = MrVref;

  return Status;
}

/**
  This function will setup the default MR values for LPDDR5 based on
  DRAM Timings and Frequency in MRC global data.
  Only populated Channels and Ranks are initialized.

  @param[in]  MrcData -  Pointer to MRC global data.

  @retval MrcStatus - mrcSuccess if successful, else an error status.
**/
MrcStatus
InitMrwLpddr5 (
  IN  MrcParameters *const MrcData
  )
{
  MrcDebug      *Debug;
  MrcInput      *Inputs;
  MrcOutput     *Outputs;
  MrcChannelOut *ChannelOut;
  UINT16        *MrPtr;
  MrcTiming     *TimingPtr;
  MrcStatus     Status;
  UINT32        Channel;
  UINT32        Controller;
  UINT32        FirstCh;
  UINT32        FirstMc;
  UINT32        Profile;
  UINT32        Rank;
  UINT16        CaDrvStrength;
  UINT16        CaOdt;
  UINT16        CaVrefMv;
  UINT16        DqOdt;
  UINT16        DqVrefMv;
  UINT16        DqDrvStrength;
  UINT16        PdDrvStr;
  UINT16        SocOdt;
  INT32         Offset;
  INT8          CaOdtEnc;
  INT8          DqOdtEnc;
  INT8          PdDsEnc;
  INT8          SocOdtEnc;
  INT8          WckOdtEnc;
  UINT8         CaVrefEnc;
  UINT8         DqVrefEnc;
  UINT8         NtOdtEnc;
  UINT8         RlEnc;
  UINT8         WlEnc;
  UINT8         WrEnc;
  BOOLEAN       Unmatched;
  TOdtValueLpddr *LpddrOdtTableIndex;
  LPDDR5_MODE_REGISTER_1_TYPE   Mr1;
  LPDDR5_MODE_REGISTER_2_TYPE   Mr2;
  LPDDR5_MODE_REGISTER_3_TYPE   Mr3;
  LPDDR5_MODE_REGISTER_10_TYPE  Mr10;
  LPDDR5_MODE_REGISTER_11_TYPE  Mr11;
  LPDDR5_MODE_REGISTER_12_TYPE  Mr12;
  LPDDR5_MODE_REGISTER_13_TYPE  Mr13;
  LPDDR5_MODE_REGISTER_14_TYPE  Mr14;
  LPDDR5_MODE_REGISTER_15_TYPE  Mr15;
  LPDDR5_MODE_REGISTER_16_TYPE  Mr16;
  LPDDR5_MODE_REGISTER_17_TYPE  Mr17;
  LPDDR5_MODE_REGISTER_18_TYPE  Mr18;
  LPDDR5_MODE_REGISTER_20_TYPE  Mr20;
  LPDDR5_MODE_REGISTER_37_TYPE  Mr37;
  LPDDR5_MODE_REGISTER_40_TYPE  Mr40;
  LPDDR5_MODE_REGISTER_41_TYPE  Mr41;

  Inputs = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug = &Outputs->Debug;
  Profile = Inputs->MemoryProfile;
  Status = mrcSuccess;
  SocOdt = Inputs->RcompTarget[RdOdt];
  DqDrvStrength = Inputs->RcompTarget[WrDS];
  CaDrvStrength = Inputs->RcompTarget[WrDSCmd];
//  DqOdt = (Outputs->DramDqOdtEn) ? DqOdtByFreqLpddr5 (Outputs->HighFrequency) : 0xFFFF;
  Unmatched = ((Outputs->RxMode == MrcRxModeUnmatchedRxWRload) || (Outputs->RxMode == MrcRxModeUnmatchedRxWPpath));
  PdDrvStr = 40; // Ohms
  WckOdtEnc = LpddrOdtEncode (60); // Ohms
  NtOdtEnc = 0;
  // Extract ODT table for first populated channel
  FirstMc = (MrcControllerExist (MrcData, cCONTROLLER0) ? cCONTROLLER0 : cCONTROLLER1);
  FirstCh = Outputs->Controller[FirstMc].FirstPopCh;
  LpddrOdtTableIndex = (TOdtValueLpddr *) GetOdtTableIndex (MrcData, FirstMc, FirstCh, dDIMM0);
  CaOdt = LpddrOdtTableIndex->RttCa;
  DqOdt = (Outputs->DramDqOdtEn) ? LpddrOdtTableIndex->RttWr : 0xFFFF;
  CaOdtEnc = LpddrOdtEncode (CaOdt);
  DqOdtEnc = LpddrOdtEncode (DqOdt);

  if (DqOdtEnc == -1) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Invalid %s ODT Value %u\n", gErrString, gDataString, DqOdtEnc);
    Status  = mrcWrongInputParameter;
  }
  if (CaOdtEnc == -1) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Invalid %s ODT Value %u\n", gErrString, gCmdString, CaOdtEnc);
    Status  = mrcWrongInputParameter;
  }

  DqVrefMv = (UINT16) MrcCalcIdealVref (MrcData, DqDrvStrength, 0, DqOdt, WrV, TRUE);
  DqVrefMv = CheckVrefLimitsLpddr5 (MrcData, DqVrefMv, WrV);
  CaVrefMv = (UINT16) MrcCalcIdealVref (MrcData, CaDrvStrength, 0, CaOdt, CmdV, TRUE);
  CaVrefMv = CheckVrefLimitsLpddr5 (MrcData, CaVrefMv, CmdV);
  VrefToOffsetLpddr5 (MrcData, DqVrefMv, &Offset);
  MrcOffsetToVrefLpddr5 (MrcData, Offset, &DqVrefEnc);
  VrefToOffsetLpddr5 (MrcData, CaVrefMv, &Offset);
  MrcOffsetToVrefLpddr5 (MrcData, Offset, &CaVrefEnc);

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
          continue;
        }
        ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
        MrPtr = ChannelOut->Dimm[dDIMM0].Rank[Rank % MAX_RANK_IN_DIMM].MR;
        TimingPtr = &ChannelOut->Timing[Profile];

        //MR16 - FSP-OP = 0, CBT = 0, CBT-PH = 0
        Mr16.Data8 = 0;
        Mr16.Bits.FspWr = 1;
        Mr16.Bits.Vrcg  = 1;
        MrPtr[mrIndexMR16] = Mr16.Data8;

        //MR13 - 0 by default from Host Structure Init.
        Mr13.Data8 = 0;
        Mr13.Bits.DmDisable = 1;
        Mr13.Bits.DualVdd2 = 1;
        MrPtr[mrIndexMR13] = Mr13.Data8;

        //MR20 - WCK Mode is 0 (Differential)
        Mr20.Data8 = 0;
        Mr20.Bits.RdqsMode = 0x2;
        MrPtr[mrIndexMR20] = Mr20.Data8;

        //MR17 -Rank 0 CK/CA ODT = 0 (Enabled), x8 ODT Lower/Upper = (Enabled)
        Mr17.Data8 = 0;
        SocOdtEnc = LpddrOdtEncode (SocOdt);
        if (SocOdtEnc == -1) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Invalid %s ODT Value\n", gErrString, gSocString, SocOdt);
          Status = mrcWrongInputParameter;
        }
        Mr17.Bits.SocOdt = SocOdtEnc;
        if (Rank > 0) {
          Mr17.Bits.CaOdtEn = 1;
          Mr17.Bits.CkOdtEn = 1;
        }
        MrPtr[mrIndexMR17] = Mr17.Data8;

        //MR25 - Partial Array Self Refresh = 0 (Disabled), CaInput/CkPair ODT = 0
        //MR10 - RDQS Post Amble Mode = 1 (Static), RDQS PST = 0 (0.5tWCK), WCK PST = 0 (2.5tWCK)
        Mr10.Data8 = 0;
        Mr10.Bits.RdqsPstMode = 1;
        Mr10.Bits.RdqsPreLen  = Unmatched ? 1 : 0;
        MrPtr[mrIndexMR10]    = Mr10.Data8;

        //MR11
        Mr11.Data8 = 0;
        Mr11.Bits.DqOdt = DqOdtEnc;
        Mr11.Bits.CaOdt = CaOdtEnc;
        Mr11.Bits.NtOdtEn = Inputs->NonTargetOdtEn;
        MrPtr[mrIndexMR11] = Mr11.Data8;

        //MR12 - CA VREF (Byte Mode Lower or whole x16)
        Mr12.Data8 = 0;
        Mr12.Bits.CaVref = CaVrefEnc;
        MrPtr[mrIndexMR12] = Mr12.Data8;

        Mr12.Data8 = 0;
        Mr12.Bits.CaVref = CaVrefEnc;
        Mr12.Bits.VrefByteSel = 1;
        MrPtr[mrIndexMR12Upper] = Mr12.Data8;

        //MR14 - VDLC = 0 (DQ[15:8]
        Mr14.Data8 = 0;
        Mr14.Bits.DqVref = DqVrefEnc;
        MrPtr[mrIndexMR14] = Mr14.Data8;

        //MR15
        Mr15.Data8 = 0;
        Mr15.Bits.DqVref = DqVrefEnc;
        MrPtr[mrIndexMR15] = Mr15.Data8;

        //MR18 - CKR = 0 (Write to CK ratio is 4:1), WCK Sync Preamble = 0 (Half Rate for 4:1 mode)
        Mr18.Data8 = 0;
        Mr18.Bits.WckOdt = WckOdtEnc;
        // If we are in safe mode, MC is configured to have WCK always on outside of PD/SR.
        // If we have more than 1 rank, we do not use dynamic, so we set Always on = 1.
        // Needs to align with WCK_CONFIG.WCK_MODE
        Mr18.Bits.WckAlwaysOn = ((MrcData->Inputs.SafeMode) || (ChannelOut->ValidRankBitMask >  1)) ? 1 : 0;
        MrPtr[mrIndexMR18] = Mr18.Data8;

        //MR3 - DBI-RD/WR = 0 (Disabled)
        Mr3.Data8 = 0;
        PdDsEnc = LpddrOdtEncode (PdDrvStr);
        if (PdDsEnc == -1) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Invalid %s Value: %u\n", gErrString, gDrvStr, PdDrvStr);
          Status = mrcWrongInputParameter;
        }
        Mr3.Bits.PullDnDrvStr = PdDsEnc;
        Mr3.Bits.WriteLatencySet = 1; // Write Latency Set B
        Mr3.Bits.BankBgOrg = 1; // 8-Bank mode
        MrPtr[mrIndexMR3] = Mr3.Data8;

        //MR1 - Clock Mode = 0 (Differential)
        Mr1.Data8 = 0;
        // Subtract 1 here to take into account tDQSS
        if (EncodeWriteLatencyLpddr5 (MrcData, TimingPtr->tCWL, &WlEnc) != mrcSuccess) {
          Status = mrcWrongInputParameter;
        }
        Mr1.Bits.WriteLatency = WlEnc;
        MrPtr[mrIndexMR1] = Mr1.Data8;

        //MR2
        Mr2.Data8 = 0;
        if (EncodeWriteRecoveryLpddr5 (MrcData, TimingPtr->tWR, &WrEnc) != mrcSuccess) {
          Status = mrcWrongInputParameter;
        }
        if (EncodeReadLatencyLpddr5 (MrcData, TimingPtr->tCL, &RlEnc) != mrcSuccess) {
          Status = mrcWrongInputParameter;
        }
        Mr2.Bits.RlAndRbtp = RlEnc;
        Mr2.Bits.WriteRecovery = WrEnc;
        MrPtr[mrIndexMR2] = Mr2.Data8;

        //MR21 - Default is 0's: All write functions disabled.
        //MR28 - Default is 0's: Normal Reset Operation, Normal Stop Operation, 32ms interval, and Background Calibration Mode.
        //MR30 - Default is 0's: No DCA adjustment

        //MR37
        Mr37.Data8 = 0;
        Mr37.Bits.Wck2DqiInterval = 4; // Stop after 64 clocks
        MrPtr[mrIndexMR37] = Mr37.Data8;

        //MR40
        Mr40.Data8 = 0;
        Mr40.Bits.Wck2DqoInterval = 4; // Stop after 64 clocks
        MrPtr[mrIndexMR40] = Mr40.Data8;

        //MR41 - PPRE = 0 (Disabled)
        Mr41.Data8 = 0;
        Mr41.Bits.NtDqOdt = NtOdtEnc;
        MrPtr[mrIndexMR41] = Mr41.Data8;

        if (Status != mrcSuccess) {
          break;
        }
      }
    }
  }
  return Status;
}

/**
  This function returns the impact to Write Latency for the requested LPDDR_ODTL_PARAM.
  Only supports BL32 8-Bank mode.

  @param[in]  Frequency - Data Rate.
  @param[in]  OdtlParam - Select between On or Off timing.

  @retval INT8 - Timing impact in nCK.
**/
INT8
MrcGetWrOdtlLpddr5 (
  IN  MrcFrequency      Frequency,
  IN  LPDDR_ODTL_PARAM  OdtlParam
  )
{
  INT8  RetVal;

  if (OdtlParam == LpOdtlOn) {
    if (Frequency >= f4267) {
      RetVal = -3;
    } else if (Frequency >= f2133) {
      RetVal = -2;
    } else {
      RetVal = -1;
    }
  } else {
    RetVal = 5;
  }

  return RetVal;
}

/**
  This function returns the impact to Read Latency for Non-target ODT of the requested LPDDR_ODTL_PARAM.
  Only supports BL32 8-Bank mode.

  @param[in]  Frequency - Data Rate.
  @param[in]  OdtlParam - Select between On or Off timing.

  @retval INT8 - Timing impact.
**/
INT8
MrcGetNtRdOdtlLpddr5 (
  IN  MrcFrequency      Frequency,
  IN  LPDDR_ODTL_PARAM  OdtlParam
  )
{
  INT8  RetVal;

  if (OdtlParam == LpOdtlOn) {
    if (Frequency >= f4267) {
      RetVal = -5;
    } else if (Frequency >= f2133) {
      RetVal = -4;
    } else {
      RetVal = -3;
    }
    // if RDQS is disabled, add 2.
    // If RDQS is enabled and MR10[4:5] != 3 add 1
  } else {
    RetVal = 6;
    // if RDQS is disabled, add 1.
  }

  return RetVal;
}

/**
  This function returns tWCKPRE_Static for both Writes and Reads in 4:1 mode.
  The implementation is based off of Table 26/27 WCK2CK Sync AC Parameters for Write/Read Operation

  @param[in]  Frequency - Data Rate.

  @retval INT8 - Timing in tCK
**/
INT8
MrcGetWckPreStaticLpddr5 (
  IN  MrcFrequency  Frequency
  )
{
  INT8  RetVal;

  if (Frequency > f4800) {
    RetVal = 4;
  } else if (Frequency > f3200) {
    RetVal = 3;
  } else if (Frequency > f1600) {
    RetVal = 2;
  } else {
    RetVal = 1;
  }

  //Cycle align on WCK
  RetVal--;

  return RetVal;
}

/**
  This function returns tWCKENL_FS in 4:1 mode.
  The implementation si based off of Table 28 WCK2CK Sync AC Paramters for CAS(WS_FAST)

  @param[in]  Frequency - Data Rate.

  @retval UINT8 - Timing in tCK
**/
UINT8
MrcGetWckEnlFsLpddr5 (
  IN  MrcFrequency  Frequency
  )
{
  INT8  RetVal;

  if (Frequency > f4267) {
    RetVal = 2;
  } else if (Frequency > f1067) {
    RetVal = 1;
  } else {
    RetVal = 0;
  }

  return RetVal;
}

/**
  This function returns tWCKPRE_total_WR.
  The implementation is based off of Table 26 WCK2CK Sync AC Parameters for Write Operation

  @param[in]  Frequency - Data rate.

  @retval UINT8 - Timing in tCK.
**/
UINT8
MrcGetWckPreWrTotalLpddr5 (
  IN  MrcFrequency  Frequency
  )
{
  UINT8 RetVal;

  if (Frequency <= f1600) {
    RetVal = 3;
  } else if (Frequency <= f3200) {
    RetVal = 4;
  } else if (Frequency <= f4800) {
    RetVal = 5;
  } else {
    RetVal = 6;
  }

  return RetVal;
}

/**
  This function returns tWCKPRE_total_RD for SetA or SetB.
  This function assumes DVFSC is disabled and DBI is off.
  The implementation is based off of Table 27 WCK2CK Sync AC Parameters for Read Operation.

  @param[in]  Frequency - Data rate.

  @retval UINT8 - Timing in tCK.
**/
INT8
MrcGetWckPreRdTotalLpddr5 (
  IN  MrcFrequency  Frequency
  )
{
  static const UINT8 tWckPreTotalRd[LP5_TFR_NUM_ENTRIES] =  {4, 5, 5, 6, 7, 7, 8, 9, 9, 10, 11, 11};
  INT8  RetVal;
  UINT8 FreqBin;

  FreqBin = GetFreqBinIndex (Frequency);
  RetVal = tWckPreTotalRd[FreqBin];

  return RetVal;
}


/**
  This function will issue the JEDEC init MR sequence for LPDDR5.
  If RestoreMRs is set, the sequence will use the MR values saved in
  the MRC global data.  Otherwise, an initial value is used.
  Flow:
   1. Set Low frequency (1100)
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
MrcJedecInitLpddr5 (
  IN  MrcParameters *const  MrcData
  )
{
  const MRC_FUNCTION  *MrcCall;
  MrcStatus     Status;
  //MrcStatus     CurStatus;
  MrcChannelOut *ChannelOut;
  MrcOutput     *Outputs;
  MrcDebug      *Debug;
  UINT32        Channel;
  UINT32        Controller;
  UINT32        Rank;
  UINT32        VrcgFspDelayNck;
  UINT32        MrdDelayNck;
  UINT32        MrwDelayNck;
  UINT32        CurDelay;
  UINT32        tCK;
  UINT8         CurMrAddr;
  UINT8         Data;
  UINT8         MrIndex;
  UINT8         Index;
  MRC_GEN_MRS_FSM_MR_TYPE *GenMrsFsmMr;
  MRC_GEN_MRS_FSM_MR_TYPE MrData[MAX_CONTROLLER][MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_MR_GEN_FSM];
  // This sequence assumes FSP 0 is the reset FSP and the caller will switch to FSP-1.
  // This aligns with the LP4 code sequence.
  static const UINT8  MrAddress[LP5_INIT_NUM_MR] = {
    mrMR16, mrMR13, mrMR20, mrMR17, mrMR25, mrMR10, mrMR11, mrMR12, mrMR12b, mrMR14,
    mrMR15, mrMR18, mrMR3,  mrMR1,  mrMR2,  mrMR21, mrMR28, mrMR30,  mrMR37, mrMR41
    };

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  MrcCall = MrcData->Inputs.Call.Func;
  Status  = mrcSuccess;

  if (!Outputs->RestoreMRs) {
    // Setup Init MR's to a default value, and update MrcData.
    Status = InitMrwLpddr5 (MrcData);
    if (Status != mrcSuccess) {
      return Status;
    }
  }

  // Clear out our array
  MrcCall->MrcSetMem ((UINT8 *) MrData, sizeof (MrData), 0);

  // Send FSP-OP[0] MR2 to program RL of the high frequency
  // This is needed for DQ mapping step of ECT
  // Default RL/WL is for 533 MT/s
  if (Outputs->LpddrEctDone) {
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank ++) {
          if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
            continue;
          }
          Data = (UINT8) ChannelOut->Dimm[dDIMM0].Rank[Rank % MAX_RANK_IN_DIMM].MR[mrIndexMR2];
          Status = MrcIssueMrw (MrcData, Controller, Channel, Rank, mrMR2, Data, !Outputs->RestoreMRs);
          if (Status != mrcSuccess) {
            return Status;
          }
        } // for Rank
      } // for Channel
    } // for Controller
  }

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
      tCK = Outputs->tCKps;
      VrcgFspDelayNck = UDIVIDEROUND (250000, tCK);
      MrwDelayNck = DIVIDECEIL (10000, tCK);
      MrwDelayNck = MAX (MrwDelayNck, 5);
      MrdDelayNck = DIVIDECEIL (14000, tCK);
      MrdDelayNck = MAX (MrdDelayNck, 5);
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (MrcRankExist (MrcData, Controller, Channel, Rank) == 0) {
          continue;
        }
        // Build array based on MR value in host structure.
        // @todo - Support to switching over to FSM for frequency switch?
        for (Index = 0; Index < LP5_INIT_NUM_MR; Index++) {
          CurMrAddr = MrAddress[Index];
          if (((CurMrAddr == mrMR12b) && (!Outputs->LpByteMode)) || (Index >= (LP5_INIT_NUM_MR - 2))) {
            continue;
          }
          MrIndex = MrcMrAddrToIndex (MrcData, &CurMrAddr);
          if (MrIndex < MAX_MR_IN_DIMM) {
            if (CurMrAddr == mrMR16) {
              CurDelay = VrcgFspDelayNck;
            } else if (Index == (LP5_INIT_NUM_MR - 1)) {
              CurDelay = MrdDelayNck;
            } else {
              CurDelay = MrwDelayNck;
            }
            GenMrsFsmMr = &MrData[Controller][Channel][Rank][Index];
            Data = (UINT8) ChannelOut->Dimm[dDIMM0].Rank[Rank % MAX_RANK_IN_DIMM].MR[MrIndex];
            GenMrsFsmMr->MrData = Data;
            GenMrsFsmMr->MrAddr = CurMrAddr;
            GenMrsFsmMr->Valid  = TRUE;
            GenMrsFsmMr->Delay  = (UINT16) CurDelay;
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (!Outputs->JedecInitDone) ? "MC%d.C%d.R%d MR%d: 0x%X Delay: %u\n" : "", Controller, Channel, Rank, CurMrAddr, Data, CurDelay);
          } else {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "MR index(%d) exceeded MR array length(%d)\n", MrIndex, MAX_MR_IN_DIMM);
            Status = mrcWrongInputParameter;
            break;
          }
        } // Index
        if (Status != mrcSuccess) {
          break;
        }
      } // Rank
      if (Status != mrcSuccess) {
        break;
      }
    } // Channel
  } // Controller

  // Program Generic MRS FSM Per Controller/Channel
  Status = MrcGenMrsFsmConfig (MrcData, MrData);

  // Run Generic FSM
  // Since we use the MRS FSM, we've configured it to send ZQ at the end if the sequence.
  Status = MrcGenMrsFsmRun (MrcData);

  // Issue ZQ Cal Start and ZQ Cal Latch on all channels / ranks
  //CurStatus = MrcIssueZQ (MrcData, MRC_ZQ_CAL);
  //if (Status == mrcSuccess) {
  //  Status = CurStatus;
  //}

  return Status;
}

/**
  This function will set up the pointer passed in based on LPDDR5 Mode Register definition.
  If MRC_IGNORE_ARG8 is passed in, that parameter is ignored.

  @param[in]      MrcData         - Pointer to global MRC data.
  @param[in]      CbtMode         - Command Bus Training mode switch.
  @param[in,out]  MrData          - Pointer to MR data to update.

**/
MrcStatus
MrcLpddr5SetMr13 (
  IN      MrcParameters *const  MrcData,
  IN      UINT8                 CbtMode,
  IN OUT  UINT16        *const  MrData
  )
{
  MrcStatus                     Status;
  LPDDR5_MODE_REGISTER_13_TYPE  *Mr13;

  Mr13    = (LPDDR5_MODE_REGISTER_13_TYPE *) MrData;
  Status  = mrcSuccess;

  if (CbtMode != MRC_IGNORE_ARG_8) {
    Mr13->Bits.CbtMode  = CbtMode;
  }
  return Status;
}

/**
  This function will set up the pointer passed in based on LPDDR5 Mode Register definition.
  If MRC_IGNORE_ARG8 is passed in, that parameter is ignored.

  @param[in]      MrcData   - Pointer to global MRC data.
  @param[in]      FspWrite  - Frequency Set Point write enable switch.
  @param[in]      FspOpMode - Frequency Set Point Operation Mode switch.
  @param[in]      CbtMode   - Command Bus Training mode switch.
  @param[in]      VrcgMode  - VREF Current Generator mode switch.
  @param[in]      CbtPhase  - Controls which phase of the clock the CA pattern is latched.
  @param[in,out]  MrData    - Pointer to MR data to update.
**/
MrcStatus
MrcLpddr5SetMr16 (
  IN      MrcParameters *const  MrcData,
  IN      UINT8                 FspWrite,
  IN      UINT8                 FspOpMode,
  IN      UINT8                 CbtMode,
  IN      UINT8                 VrcgMode,
  IN      UINT8                 CbtPhase,
  IN OUT  UINT16        *const  MrData
  )
{
  MrcStatus Status;
  LPDDR5_MODE_REGISTER_16_TYPE  *Mr16;

  Status  = mrcSuccess;
  Mr16 = (LPDDR5_MODE_REGISTER_16_TYPE *) MrData;

  if (FspWrite != MRC_IGNORE_ARG_8) {
    Mr16->Bits.FspWr = FspWrite;
  }

  if (FspOpMode != MRC_IGNORE_ARG_8) {
    Mr16->Bits.FspOp = FspOpMode;
  }

  if (CbtMode != MRC_IGNORE_ARG_8) {
    Mr16->Bits.CbtEn = CbtMode;
  }

  if (VrcgMode != MRC_IGNORE_ARG_8) {
    Mr16->Bits.Vrcg = VrcgMode;
  }

  if (CbtPhase != MRC_IGNORE_ARG_8) {
    Mr16->Bits.CbtPhase = CbtPhase;
  }

  return Status;
}

/**
  This function will drive DQ7 for LP5 ECT so that DRAM can switch from FSP0 to FSP1.

  @param[in]          MrcData          Pointer to global MRC data.
  @param[in]          DQ7Value         Value of DQ7 pin
  @param[in,out]      WckControlSave   Save the phyinit value for WckControl register
  @param[in,out]      MiscControl7Save Save the phyinit value for MiscControl7 register
  **/
VOID
MrcDriveDq7 (
  IN     MrcParameters *const  MrcData,
  IN     UINT8                  Dq7Value,
  IN OUT UINT32      *const     WckControlSave,
  IN OUT UINT32      *const     MiscControl7Save
  )
{
  MrcInput      *Inputs;
  MrcOutput     *Outputs;
  MrcChannelIn  *ChannelIn;
  INT64         GetSetVal;
  INT64         GetSetEn;
  INT64         GetSetDis;
  UINT32        Controller;
  UINT32        Channel;
  UINT32        DramBit;
  UINT32        CpuByte;
  UINT32        CpuBit;
  UINT32        WckPulseWait;
  UINT32        Wck2Dq7SuHdPs;
  UINT8         MaxChannel;
  UINT16        Qclkps;
  UINT16        WckPs;
  UINT8         CpuValue;
  UINT8         DramValue;
  DDRSCRAM_CR_DDRMISCCONTROL7_STRUCT  MiscControl7;
  MCMISCS_DDRWCKCONTROL_STRUCT  WckControl;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  Qclkps        = Outputs->Qclkps;
  WckPs         = Outputs->Wckps;
  MaxChannel    = Outputs->MaxChannels;
  DramValue     = Dq7Value;
  GetSetEn      = 1;
  GetSetDis     = 0;
  WckPulseWait  = (5 * Qclkps);

  // tWCK2DQ7H MAX (5ns, 12Wck)
  Wck2Dq7SuHdPs = WckPs * 12;
  Wck2Dq7SuHdPs = MAX (Wck2Dq7SuHdPs, MRC_LP5_tWCK2DQ7H_PS);
  WckPulseWait += Wck2Dq7SuHdPs;
  WckPulseWait = DIVIDECEIL (WckPulseWait, 1000);

  if (Dq7Value) {
    MiscControl7.Data = MrcReadCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL7_REG);
    *MiscControl7Save = MiscControl7.Data;
    MiscControl7.Bits.TrainWCkEn = 1;
    MrcWriteCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL7_REG, MiscControl7.Data);

    // Cause Clock Stop edge
    MrcGetSetMc (MrcData, MAX_CONTROLLER, GsmMccEnableDclk, WriteNoCache, &GetSetDis);
    MrcWait (MrcData, 10 * MRC_TIMER_1NS);
    MrcGetSetMc (MrcData, MAX_CONTROLLER, GsmMccEnableDclk, WriteNoCache, &GetSetEn);

    //Set WCK Control for BL/Mask and DiffLowInIdle
    WckControl.Data = MrcReadCR (MrcData, MCMISCS_DDRWCKCONTROL_REG);
    *WckControlSave = WckControl.Data;
    WckControl.Bits.TrainWCkBL = 0;
    WckControl.Bits.TrainWCkMask = 7;
    WckControl.Bits.WCkDiffLowInIdle = 1;
    MrcWriteCR (MrcData, MCMISCS_DDRWCKCONTROL_REG, WckControl.Data);

    // TrainWckPulse needs to be set after all of the above are set
    WckControl.Bits.TrainWCkPulse = 1;
    MrcWriteCR (MrcData, MCMISCS_DDRWCKCONTROL_REG, WckControl.Data);

    MrcWait (MrcData, WckPulseWait);
  }

  // Drive DQ7
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }
      ChannelIn = &Inputs->Controller[Controller].Channel[Channel];
      for (CpuByte = 0; CpuByte < Outputs->SdramCount; CpuByte++) {
        // Find which DRAM byte is mapped to this CPU byte
        CpuValue = 0;
        for (CpuBit = 0; CpuBit < MAX_BITS; CpuBit++) {
          // Find DRAM DQ pin that is connected to the current CPU DQ pin
          DramBit = ChannelIn->DqMapCpu2Dram[CpuByte][CpuBit];
          if (DramBit == 7) {
            CpuValue |= DramValue << CpuBit;  // Should go on this CPU DQ pin
          }
        }
        GetSetVal = CpuValue;
        MrcGetSetChStrb (MrcData, Controller, Channel, CpuByte, GsmIocDqOverrideData, WriteToCache, &GetSetVal);
        GetSetVal = 0x80;   // Override DQ7
        MrcGetSetChStrb (MrcData, Controller, Channel, CpuByte, GsmIocDqOverrideEn, WriteToCache, &GetSetVal);
      }
    } // for Channel
  } // for Controller
  MrcFlushRegisterCachedData (MrcData);

  // When we exit CBT, we first drive DQ7 low, wait for (MRC_LP5_tDQ7LWCK + MRC_LP5_tVREFCA_LONG) then we restore WckControl
  if (Dq7Value == 0) {
    WckControl.Data = *WckControlSave;
    MrcWriteCR (MrcData, MCMISCS_DDRWCKCONTROL_REG, WckControl.Data);
    MiscControl7.Data = *MiscControl7Save;
    MrcWriteCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL7_REG, MiscControl7.Data);
  }

  if (Dq7Value) {
    // tDQ7HWCK is the same as tWCK2DQ7H.  Reuse variable from above.
    MrcWait (MrcData, DIVIDECEIL (Wck2Dq7SuHdPs, 1000));
  } else {
    MrcWait (MrcData, DIVIDECEIL ((MRC_LP5_tDQ7LWCK_PS + MRC_LP5_tVREFCA_LONG_PS), 1000));
  }
}

/**
  This function will set Rcomp for DQ to look like they are in RX mode.

  @param[in]      MrcData           Pointer to global MRC data.
  @param[in]      Set               To set Rcomp values for RX mode
  @param[in,out]  DataRcompDataSave Save the phyinit value for RcompData register
  **/
VOID
MrcSetRcompData (
  IN      MrcParameters *const MrcData,
  IN      BOOLEAN              Set,
  IN OUT  UINT32               DataRcompDataSave [MAX_CONTROLLER][MAX_SDRAM_IN_DIMM]
  )
{
  MrcInput                             *Inputs;
  MrcOutput                            *Outputs;
  DATA0CH0_CR_DDRCRDATACONTROL0_STRUCT DataControl0;
  DATA0CH0_CR_DDRCRDATACONTROL5_STRUCT DataControl5;
  DATA0CH0_CR_RCOMPDATA0_STRUCT        DataRcompData0;
  DATA0CH0_CR_RCOMPDATA1_STRUCT        DataRcompData1;
  INT64                                TxOn;
  UINT32                               RlegPerSeg; //Rleg per segment, multiply by the number of segments in ODT to get RlegPerSeg
  UINT32                               Controller;
  UINT32                               Channel;
  UINT32                               Offset;
  UINT32                               TempVar1;
  UINT32                               ByteIndex;
  UINT8                                byte;

  Outputs    = &MrcData->Outputs;
  Inputs     = &MrcData->Inputs;
  TxOn = Set ? 1 : 0;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; (Channel < Outputs->MaxChannels); Channel++) {
      if (MrcChannelExist (MrcData, Controller, Channel)) {
        for (byte = 0; (byte < Outputs->SdramCount); byte++) {
          ByteIndex = (MAX_BYTE_IN_LP_CHANNEL * Channel) + byte; //@todo : For DDR5 MAX_BYTE_IN_CHANNEL != 2 so add that
          if (Set) {
            Offset = DataControl0Offset (Controller, ByteIndex);
            DataControl0.Data = MrcReadCR (MrcData, Offset);

            Offset = DataControl5Offset (Controller, ByteIndex);
            DataControl5.Data = MrcReadCR (MrcData, Offset);

            Offset = DATA0CH0_CR_RCOMPDATA1_REG +
              (DATA0CH1_CR_RCOMPDATA1_REG - DATA0CH0_CR_RCOMPDATA1_REG) * Controller +
              (DATA1CH0_CR_RCOMPDATA1_REG - DATA0CH0_CR_RCOMPDATA1_REG) * ByteIndex;
            DataRcompData1.Data = MrcReadCR (MrcData, Offset);

            Offset = DATA0CH0_CR_RCOMPDATA0_REG +
              (DATA0CH1_CR_RCOMPDATA0_REG - DATA0CH0_CR_RCOMPDATA0_REG) * Controller +
              (DATA1CH0_CR_RCOMPDATA0_REG - DATA0CH0_CR_RCOMPDATA0_REG) * ByteIndex;
            DataRcompData0.Data = MrcReadCR (MrcData, Offset);

            DataRcompDataSave[Controller][ByteIndex] = DataRcompData0.Data;

            RlegPerSeg = ((UINT32) (Inputs->RcompTarget[RdOdt])) * (23 * ((DataControl0.Bits.DisableOdtStatic == 0) ? 1 : 0) + DataRcompData1.Bits.RcompOdtDown) * (2 - DataControl5.Bits.ODTSingleSegEn);
            TempVar1 = RlegPerSeg / ((UINT32) (2 * Inputs->RcompTarget[WrDS])) - 23;
            DataRcompData0.Bits.RcompDrvDown = TempVar1;
            MrcWriteCR (MrcData, Offset, DataRcompData0.Data);
          } else { // restore RcompData
            DataRcompData0.Data = DataRcompDataSave[Controller][ByteIndex];
            Offset = DATA0CH0_CR_RCOMPDATA0_REG +
              (DATA0CH1_CR_RCOMPDATA0_REG - DATA0CH0_CR_RCOMPDATA0_REG) * Controller +
              (DATA1CH0_CR_RCOMPDATA0_REG - DATA0CH0_CR_RCOMPDATA0_REG) * ByteIndex;
            MrcWriteCR (MrcData, Offset, DataRcompData0.Data);
          }
        } // Byte
      } // ChannelExist
    } // Channel
  } // Controller
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocTxOn, WriteCached, &TxOn);
}

/**
  This function will set up the pointer passed in based on LPDDR5 Mode Register definition.
  If MRC_IGNORE_ARG8 is passed in, that parameter is ignored.
  Only CaVref does error checking against spec valid values.

  @param[in]      MrcData     - Pointer to global MRC data.
  @param[in]      CaVref      - Command/Address Vref to set (JEDEC Encoding).
  @param[in]      VrefByteSel - 0B: x16 device and byte mode DQ[7:0]
                                    device is selected. (default)
                                1B: Byte mode DQ[15:8] device is selected.
  @param[in,out]  MrData      - Pointer to MR data to update.

  @retval MrcStatus - mrcWrongInputParameter if CaVref is invalid, else mrcSuccess.
**/
MrcStatus
MrcLpddr5SetMr12 (
  IN      MrcParameters *const  MrcData,
  IN      UINT8                 CaVref,
  IN      UINT8                 VrefByteSel,
  IN OUT  UINT16        *const  MrData
  )
{
  MrcDebug  *Debug;
  MrcStatus Status;
  LPDDR5_MODE_REGISTER_12_TYPE  *Mr12;

  Debug   = &MrcData->Outputs.Debug;
  Status  = mrcSuccess;
  Mr12    = (LPDDR5_MODE_REGISTER_12_TYPE *) MrData;

  if (CaVref != MRC_IGNORE_ARG_8) {
    if (CaVref < LPDDR5_VREF_FIELD_MAX) {
      Mr12->Bits.CaVref = CaVref;
    } else {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s Invalid %s Vref Setting: %d\n", gErrString, gCmdString, CaVref);
      Status = mrcWrongInputParameter;
    }
  }

  if (VrefByteSel != MRC_IGNORE_ARG_8) {
    Mr12->Bits.VrefByteSel  = VrefByteSel;
  }

  return Status;
}

/**
  This function will set up the pointer passed in based on LPDDR5 Mode Register definition.
  If MRC_IGNORE_ARG8 is passed in, that parameter is ignored.
  Only DqVref does error checking against spec valid values.

  @param[in]      MrcData     - Pointer to global MRC data.
  @param[in]      DqVref      - Data Vref to set (JEDEC Encoding).
  @param[in,out]  MrData      - Pointer to MR data to update.

  @retval MrcStatus - mrcSuccess if a supported value, else mrcWrongInputParameter.
**/
MrcStatus
MrcLpddr5SetMr15 (
  IN      MrcParameters *const  MrcData,
  IN      UINT8                 DqVref,
  IN OUT  UINT16        *const  MrData
  )
{
  MrcDebug  *Debug;
  MrcStatus Status;
  LPDDR5_MODE_REGISTER_15_TYPE  *Mr15;

  Debug   = &MrcData->Outputs.Debug;
  Status  = mrcSuccess;
  Mr15    = (LPDDR5_MODE_REGISTER_15_TYPE *) MrData;

  if (DqVref != MRC_IGNORE_ARG_8) {
    if (DqVref < LPDDR5_VREF_FIELD_MAX) {
      Mr15->Bits.DqVref = DqVref;
    } else {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s Invalid %s Vref Setting\n", gErrString, gDataString, DqVref);
      Status = mrcWrongInputParameter;
    }
  }

  return Status;
}

/**
  This function will set up the pointer passed in based on LPDDR5 Mode Register definition.
  If MRC_IGNORE_ARG8 is passed in, that parameter is ignored.
  Only DqVref does error checking against spec valid values.

  @param[in]      MrcData     - Pointer to global MRC data.
  @param[in]      DqVref      - Data Vref to set (JEDEC Encoding).
  @param[in]      Vdlc        - Vref DQ Lower Byte Control
  @param[in,out]  MrData      - Pointer to MR data to update.

  @retval MrcStatus - mrcSuccess if a supported ODT value, else mrcWrongInputParameter.
**/
MrcStatus
MrcLpddr5SetMr14 (
  IN      MrcParameters *const  MrcData,
  IN      UINT8                 DqVref,
  IN      UINT8                 Vdlc,
  IN OUT  UINT16        *const  MrData
  )
{
  MrcDebug  *Debug;
  MrcStatus Status;
  LPDDR5_MODE_REGISTER_14_TYPE  *Mr14;

  Debug   = &MrcData->Outputs.Debug;
  Status  = mrcSuccess;
  Mr14    = (LPDDR5_MODE_REGISTER_14_TYPE *) MrData;

  if (DqVref != MRC_IGNORE_ARG_8) {
    if (DqVref < LPDDR5_VREF_FIELD_MAX) {
      Mr14->Bits.DqVref = DqVref;
    } else {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s Invalid %s Vref Setting\n", gErrString, gDataString, DqVref);
      Status = mrcWrongInputParameter;
    }
  }

  if (Vdlc != MRC_IGNORE_ARG_8) {
    Mr14->Bits.Vdlc  = Vdlc;
  }

  return Status;
}

/**
  Set Tx and CA DIMM Vref absolute Value for LPDDR5.

  @param[in]      MrcData       - Include all MRC global data.
  @param[in]      VrefType      - The type of Vref to set
  @param[in]      Controller    - Selecting which Controller to talk to.
  @param[in]      Channel       - Channel to program.
  @param[in]      Rank          - Selecting which Rank to talk to.
  @param[in]      Offset        - Vref Offset to program.
  @param[in]      UpdateMrcData - Update MRC host struct.

  @retval mrcSuccess              - Within programmable range.
  @retval mrcWrongInputParameter  - Not in programmable range.
  @retval mrcDeviceBusy           - MRH could not complete MR write.
**/
MrcStatus
MrcSetVrefLpddr5 (
  IN  MrcParameters *const  MrcData,
  IN  UINT8                 VrefType,
  IN  UINT8                 Controller,
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
  MrcStatus   Status;
  UINT8       RankMask;
  UINT8       VrefCode;
  UINT16      *MrPtr;
  UINT8       MrAddress;
  UINT8       MrIndex;
  UINT8       ByteSel;
  LPDDR5_MODE_REGISTER_12_TYPE  Lpddr5Mr12;
  LPDDR5_MODE_REGISTER_14_TYPE  Lpddr5Mr14;

  Status     = mrcSuccess;
  Outputs    = &MrcData->Outputs;
#if (defined (MRC_MEMORY_API_DEBUG) && (MRC_MEMORY_API_DEBUG == SUPPORT))
  Debug      = &Outputs->Debug;
#endif
  ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
  RankMask   = ChannelOut->ValidRankBitMask;
  Lpddr5Mr12.Data8 = 0;
  Lpddr5Mr14.Data8 = 0;

  if (RankMask &  (1 << Rank)) {
    MrPtr = ChannelOut->Dimm[dDIMM0].Rank[Rank % MAX_RANK_IN_DIMM].MR;

    Status = MrcOffsetToVrefLpddr5 (MrcData, Offset, &VrefCode);
    MRC_API_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " Mc%u.Ch%u.Rank%d, Requested Offset %d, VrefCode 0x%X\n", Controller, Channel, Rank, Offset, VrefCode);

    if (VrefType == CmdV) {
      MrAddress = mrMR12;
      // run twice for Byte mode
      for (ByteSel = 0; ByteSel < (Outputs->LpByteMode ? 2 : 1); ByteSel++) {
        MrIndex = mrIndexMR12 + ByteSel; // mrIndexMR12 + 1 = mrIndexMR12Upper
        Lpddr5Mr12.Bits.CaVref = VrefCode;
        Lpddr5Mr12.Bits.VrefByteSel = ByteSel;
        Status = MrcIssueMrw (
                  MrcData,
                  Controller,
                  Channel,
                  Rank,
                  MrAddress,
                  Lpddr5Mr12.Data8,
                  FALSE   // DebugPrint
                  );
        if (Status != mrcSuccess) {
          return Status;
        }
        if (UpdateMrcData) {
          MrPtr[MrIndex] = Lpddr5Mr12.Data8;
        }
        MrcWait (MrcData, DIVIDECEIL (MRC_LP4_tVREFCA_LONG_NS, MRC_TIMER_1NS));
      }
    } else { // WrV
      Lpddr5Mr14.Bits.DqVref = VrefCode;
      for (ByteSel = 0; ByteSel < 2; ByteSel++) {
        if ((Outputs->LpByteMode) && (ByteSel == 1)) {
          // Byte mode device doesn't support VDLC function (VREF DQ Lower byte copy).
          // SOC need to set MR14 and MR15 to individual devices.
          // Byte Mode device ignores OP[7] (VDLC)
          MrAddress = mrMR15;
          MrIndex   = mrIndexMR15;
        } else {
          Lpddr5Mr14.Bits.Vdlc = ByteSel;
          MrAddress = mrMR14;
          MrIndex   = mrIndexMR14;
        }
        Status = MrcIssueMrw (
                  MrcData,
                  Controller,
                  Channel,
                  Rank,
                  MrAddress,
                  Lpddr5Mr14.Data8,
                  FALSE   // DebugPrint
                  );
        if (Status != mrcSuccess) {
          return Status;
        }
        if (UpdateMrcData) {
          MrPtr[MrIndex] = Lpddr5Mr14.Data8;
        }
        MrcWait (MrcData, DIVIDECEIL (MRC_LP4_tVREFCA_LONG_NS, MRC_TIMER_1NS));
      } // ByteSel loop
    } // else WrV
  } // if RankMask &  (1 << Rank)
  return Status;
}

/**
  Used to update TxVref and CaVref for LPDDR5.
  Uses input offset value to increment/decrement current setting.

  @param[in,out] MrcData        - Include all MRC global data.
  @param[in,out] Controller     - Selecting which Controller to talk to.
  @param[in]     Channel        - Selecting which Channel to talk to.
  @param[in]     RankMask       - Selecting which Ranks to talk to.
  @param[in]     VrefType       - Determines the Vref type to change, only CmdV and TxVref are valid.
  @param[in]     Offset         - Vref offset value.
  @param[in]     UpdateMrcData  - Used to decide if Mrc host must be updated.
  @param[in]     IsCachedOffsetParam - Determines if the paramter is an offset (relative to cache) or absolute value.

  @retval MrcStatus - mrcWrongInputParameter if unsupported OptParam,  mrcSuccess otherwise
**/
MrcStatus
Lpddr5SetDramVref (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Controller,
  IN     UINT8                Channel,
  IN     UINT8                RankMask,
  IN     UINT8                VrefType,
  IN     INT32                Offset,
  IN     BOOLEAN              UpdateMrcData,
  IN     BOOLEAN              IsCachedOffsetParam
  )
{
  MrcDebug      *Debug;
  MrcOutput     *Outputs;
  MrcChannelOut *ChannelOut;
  UINT16        *MrPtr;
  UINT8         Rank;
  UINT8         MrIndex;
  INT32         CurrentOffset;
  MrcStatus     Status;
  LPDDR5_MODE_REGISTER_14_TYPE Lpddr5VrefMr; // Register struct is common to CaVref and TxVref

  Outputs            = &MrcData->Outputs;
  Debug              = &Outputs->Debug;
  ChannelOut         = &Outputs->Controller[Controller].Channel[Channel];
  Status             = mrcSuccess;
  MrIndex            = 0;
  CurrentOffset      = 0;
  Lpddr5VrefMr.Data8 = 0;

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
    if ((MrcRankExist (MrcData, Controller, Channel, Rank)) && (RankMask & (1 << Rank))) {
      MrPtr = ChannelOut->Dimm[dDIMM0].Rank[Rank % MAX_RANK_IN_DIMM].MR;

      if (IsCachedOffsetParam) {
        // Offset value.  Calculate the new Vref.
        Lpddr5VrefMr.Data8 = (UINT8) MrPtr[MrIndex];
        MrcVrefEncToOffsetLpddr5 (MrcData, Lpddr5VrefMr.Bits.DqVref, &CurrentOffset);
        CurrentOffset += Offset;
      } else {
        // For Non-Cached OffsetParam set value as-is
        CurrentOffset = Offset;
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NEVER, "Lpddr5SetDramVref - Mc%u.Ch%u.R%u RankMask = 0x%x  IsCachedOffsetParam:%d, MR14: 0x%02X, CurrentOffset: %d, Offset: %d\n",
                     Controller, Channel, Rank, RankMask, IsCachedOffsetParam, Lpddr5VrefMr.Data8, CurrentOffset, Offset);
      MrcSetVrefLpddr5 (MrcData, VrefType, Controller, Channel, Rank, CurrentOffset, UpdateMrcData);
    }

  }
  return Status;
}

