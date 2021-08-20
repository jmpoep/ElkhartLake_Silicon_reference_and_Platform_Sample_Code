/** @file
  Command training definitions.

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

///
/// Include files
///
#ifndef _MrcCommandTraining_h_
#define _MrcCommandTraining_h_

#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcCommon.h"
#include "MrcGlobal.h"
#include "MrcIoControl.h"
#include "MrcReadReceiveEnable.h"
#include "MrcReset.h"
#include "MrcTimingConfiguration.h"
#include "MrcMcConfiguration.h"

#define ECT_CLK_START (0)
#define ECT_CLK_STOP  (128)

#define ECT_CLK_STEP  (2)

#define ECT_CLK_LOOPS (ECT_CLK_STOP / ECT_CLK_STEP)

#define ECT_DQS_START (-32)
#define ECT_DQS_STOP  (32)
#define ECT_DQS_STEP  (8)
#define ECT_MIN_WIDTH (16)

/**
  This function performs early command training.
  Center CTL-CLK timing to allow subsequent steps to work

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus -  mrcSuccess if it succeeded
**/
extern
MrcStatus
MrcEarlyCommandTraining (
  IN MrcParameters *const MrcData
  );

/**
  This function performs Late command training.
  Center CMD/CTL-CLK timing using complex patterns.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - If it's a success return mrcSuccess
**/
extern
MrcStatus
MrcLateCommandTraining (
  IN MrcParameters *const MrcData
  );

/**
  Perform Early Command Voltage Centering.

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  if it succeeded returns mrcSuccess
**/
extern
MrcStatus
MrcEarlyCmdVoltageCentering (
  IN OUT MrcParameters *const MrcData
  );

/**
  Perform Command Voltage Centering.

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus - if it succeded returns mrcSuccess
**/
extern
MrcStatus
MrcCmdVoltageCentering (
  IN OUT MrcParameters *const MrcData
  );

/**
  Centers Command Timing around a MidPoint

  @param[in] MrcData         - Include all MRC global data.
  @param[in] Iteration       - Determines which PI to shift
  @param[in] Ranks           - Valid Rank bit mask
  @param[in] GroupMask       - which LPDDR groups to work on for CMD/CLK/CKE; not used for DDR4
  @param[in] MidPoint        - The MidPoint to center around (per channel)

  @retval Nothing
**/
extern
MrcStatus
CmdTimingCentering (
  IN MrcParameters *const MrcData,
  IN UINT8                Iteration,
  IN UINT8                Ranks,
  IN UINT8                GroupMask,
  IN UINT8                MidPoint[MAX_CHANNEL]
  );

/**
  Training the Cmd slew rate for best margins.
  Steps:
  1. Get Min/Max Stage Number from DDR Scomp config step (Start).
  2. Train Cmd Slew rate stages in the region [Start, Stop].
  3. Re-center Cmd Timing.
  4. Re-center Cmd Voltage.

  @param[in] MrcData  - Include all MRC global data.

  @retval MrcStatus
**/
extern
MrcStatus
MrcCmdSlewRate(
  IN MrcParameters *const MrcData
  );

/**
  Training the Cmd slew rate offset for best margins.
  Steps:
  1. Find the minimal number of stages for which Comp is not saturated (Start).
  2. Find the maximal number of stages for which Comp is not saturated (Stop).
  3. Train Cmd Slew rate stages in the region [Start, Stop].
  4. Re-center Cmd Timing.
  5. Re-center Cmd Voltage.

  @param[in] MrcData  - Include all MRC global data.

  @retval MrcStatus
**/
extern
MrcStatus
MrcCmdSlewRateOffset(
  IN MrcParameters *const MrcData
  );

/**
  Training the Command TxEq and Ron for best margins.
  Steps:
  1. Find the minimal Vref (Ron) for which Comp is no saturated (Start).
  2. Find the maximal Vref (Ron) for which Comp is no saturated (Stop).
  3. Train Cmd Ron (Vref) & TxEq in the region [Start, Stop].
  4. Center Cmd Timing.
  5. Center Cmd Voltage.

  @param[in] MrcData  - Include all MRC global data.

  @retval MrcStatus
**/
extern
MrcStatus
MrcCmdDsTxEq(
  IN MrcParameters *const MrcData
  );

/**
  Center CMD with respect to CLK & CTL.

  @param[in,out] MrcData        - Include all MRC global data.
  @param[in]     ChannelMask    - Channels to train
  @param[in]     LoopCount      - Loop count for CMD stress.
  @param[in]     SetupCadb      - Indicates if SetupCadb should be called and disabled at the end.
  @param[in]     DebugPrint     - Enable / disable debug printing
  @param[in]     UpdateHost     - Determines if MrcData structure is updated

  @retval MrcStatus
**/
extern
MrcStatus
MrcCmdTimingCentering(
  IN MrcParameters *const MrcData,
  IN UINT8                ChannelMask,
  IN UINT8                LoopCount,
  IN BOOLEAN              SetupCadb,
  IN BOOLEAN              DebugPrint,
  IN const UINT8          UpdateHost
  );

/**
  Use a linear search to find the edges between Low and High
  if WrapAround = 0: Look for largest passing region between low and high
  if WrapAround = 1: Look for largest passing region, including wrapping from high to low

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in]      Iteration   - Determines which PI to shift
  @param[in]      chBitMask   - Valid Channel bit mask
  @param[in]      Ranks       - Valid Rank bit mask
  @param[in]      GroupMask   - which LPDDR groups to work on for CMD/CLK/CKE; not used for DDR4
  @param[in]      Low         - Low limit
  @param[in]      High        - High limit
  @param[in]      Step        - Step size
  @param[in]      WrapAllowed - Determines the search region
  @param[in]      VrefOffsets - Array of Vref offsets
  @param[in]      SkipPrint   - Switch to enable or disable debug printing
  @param[in]      SkipVref    - Skip changing CMD Vref offsets, only run test once at the current Vref.

  @retval MrcStatus -  If it succeeds return mrcSuccess
**/
extern
MrcStatus
CmdLinearFindEdges (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Iteration,
  IN     UINT8                chBitMask,
  IN     UINT8                Ranks,
  IN     UINT8                GroupMask,
  IN     INT8                 Low,
  IN     UINT8                High,
  IN     UINT8                Step,
  IN     UINT8                WrapAllowed,
  IN     INT8                 *VrefOffsets,
  IN     BOOLEAN              SkipPrint,
  IN     BOOLEAN              SkipVref
  );

/**
  Use a binary search to find the edge between Low and High
  High and Low track passing points
  if CountUp: Low is a passing point and need to count up to find a failing point
  if CountDn: High is a passing point and need to count dn to find a failing point

  @param[in]      MrcData     - Include all MRC global data.
  @param[in]      Iteration   - Determines which PI to shift
  @param[in]      ChBitMask   - Valid Channel bit mask
  @param[in]      Ranks       - Valid Rank bit mask
  @param[in]      GroupMask   - which LPDDR groups to work on for CMD/CLK/CKE; not used for DDR4
  @param[in, out] Low         - Low limit
  @param[in, out] High        - High limit
  @param[in]      CountUp     - The direction to search
  @param[in]      VrefOffsets - Array of Vref offsets

  @retval Nothing
**/
extern
void
CmdBinaryFindEdge (
  IN     MrcParameters *const MrcData,
  IN     UINT8                Iteration,
  IN     UINT8                ChBitMask,
  IN     UINT8                Ranks,
  IN     UINT8                GroupMask,
  IN OUT UINT8                *Low,
  IN OUT UINT8                *High,
  IN     UINT8                CountUp,
  IN     INT8                 *VrefOffsets
  );

/**
  Shift the CLK/CTL Timing
  Shift the CMD Timing

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Channel    - Channel to shift
  @param[in] Offset     - Offset to shift by

  @retval Nothing
**/
extern
void
ShiftChannelTiming (
  IN MrcParameters *const MrcData,
  IN UINT8                Channel,
  IN INT32                Offset
  );

/**
  This function updtes Command Mode register, tXP and Round trip latency

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in]      Channel     - Channel to perform update to
  @param[in]      OldN        - Old N Mode value
  @param[in]      NewN        - New N mode value

  @retval Nothing
**/
extern
void
UpdateCmdNTiming (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Channel,
  IN     UINT8                OldN,
  IN     UINT8                NewN
  );


typedef struct _CADB_LINE {
  UINT32 CaHigh;
  UINT32 CaLow;
  UINT8  ChipSelect;
} CADB_LINE;

typedef enum {
  CaTrainingMode41,     ///< Enter CA training mode using MRW41
  CaTrainingMode48,     ///< Enter CA training mode using MRW48
  CaTrainingMode42      ///< Exit CA training mode using MRW42
} MrcCaTrainingMode;

/**
  Early CA / CS training for LPDDR4.
  Main flow:
  1. Run CPU-to-DRAM DQ Mapping (map DQ pins according to the board swizzling).
  2. Run Early 2D CS/CMD training
  3. Run CS vs. CLK training.
  4. Run CA vs. CLK training.
  5. Program DESWIZZLE_HIGH/LOW registers.

  @param[in] MrcData - The MRC global data.

  @retval mrcSuccess if succeeded
**/
extern
MrcStatus
EarlyCommandTrainingLpddr4 (
  IN MrcParameters *const MrcData
  );

/**
  Early CS / CLK training for LPDDR4.
  Main flow:

  @param[in] MrcData - The MRC global data.

  @retval mrcSuccess if succeeded
**/
MrcStatus
EarlyChipSelectTrainingLp4 (
  IN MrcParameters * const MrcData
  );

/**
  Sweep right and left from the current point to find the margins.

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in]      Iteration   - Determines which PI to shift
  @param[in]      ChannelMask - Valid Channel bit mask
  @param[in]      RankMask    - Valid Rank bit mask
  @param[in]      GroupMask   - Valid Group bit mask
  @param[in]      DebugPrint  - Print debug messages or not

  @retval MrcStatus -  If it succeeds return mrcSuccess
**/
void
CmdLinearFindEdgesLpddr (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Iteration,
  IN     UINT8                ChannelMask,
  IN     UINT8                RankMask,
  IN     UINT8                GroupMask,
  IN     BOOLEAN              DebugPrint
  );

/**
  Plot CmdT (linear CLK shift) vs CmdV, used for debug of DDR4.

  @param[in] MrcData         - Include all MRC global data.

  @retval MrcStatus
**/
MrcStatus
CommandPlot2D (
  IN     MrcParameters *const MrcData
  );


/**
Plot Rd/Wr Eye

@param[in] MrcData - Include all MRC global data.

@retval MrcStatus
**/
MrcStatus
DataPlot2D(
  IN     MrcParameters *const MrcData,
  IN     UINT8                Param
);

/**
  Enter / exit LPDDR4 CA training mode:
  If ENABLE:
    - Send MRW to MR13 OP[0] = 1, Wait tMRD
    - Force CKE low
    - Switch PLL to High frequency
  Else // DISABLE
    - Switch PLL to Low frequency
    - Force CKE high, Wait tFC
    - Send MRW to MR13 OP[0] = 0.

  @param[in] MrcData      - The MRC global data.
  @param[in] ChBitMask    - Channels to work on.
  @param[in] RankBitMask  - Ranks to work on.
  @param[in] Enable       - Enable or disable CBT.

  @retval mrcSuccess if succeeded
**/
MrcStatus
Lpddr4CommandTrainingMode (
  IN MrcParameters *const  MrcData,
  IN UINT8                 ChBitMask,
  IN UINT8                 RankBitMask,
  IN BOOLEAN               Enable
  );

/**
  This routine is used throughout LPDDR4 ECT code to initialize DDR IO for CA training.
  On "Odd" DRAM bytes: enable the following bits because we will use DATATRAINFEEDBACK to read back CA values on DQ[13:8] pins:
    DataControl2.ForceRxOn and ForceBiasOn (must be set first)
    DataControl0.SenseampTrainingMode, ForceOdtOn and TxDisable

  On "Even" DRAM bytes we will send VrefCA values on DQ[6:0] pins:
    DataControl5.DdrCRMaskCntPulseNumStart[16:13] = 6 (number of masked DQS pulses)
    DataControl5.DdrCRNumOfPulses[12:11] = 2 (number of DQS pulses sent)
    DataControl5.Ddrcrdqsmaskcnten[10] = 1 (enables the special CBT VrefCA programming mode)
    DataControl0.TxOn (must be after DataControl5)

  @param[in] MrcData - The MRC global data.

  @retval none
**/
VOID
Lpddr4CaTrainingInitIo (
  IN MrcParameters *const MrcData
  );

/**
  This routine is used throughout LPDDR4 ECT code to initialize DDR IO for CA training.
  On all DRAM bytes we will send VrefCA values on DQ[6:0] pins:
    DataControl5.DdrCRMaskCntPulseNumStart[16:13] = 6 (number of masked DQS pulses)
    DataControl5.DdrCRNumOfPulses[12:11] = 2 (number of DQS pulses sent)
    DataControl5.Ddrcrdqsmaskcnten[10] = 1 (enables the special CBT VrefCA programming mode)
    DataControl0.TxOn (must be after DataControl5)

  @param[in] MrcData - The MRC global data.

  @retval none
**/
VOID
Lpddr4CaTrainingInitIoTx (
  IN MrcParameters *const MrcData
  );

/**
  This routine is used throughout LPDDR4 ECT code to restore DDR IO from CA training.
  On all DRAM bytes: disable the following bits:
    DataControl0.TxOn (must be cleared first)
    DataControl5.Ddrcrdqsmaskcnten[10] = 0 (disable the special CBT VrefCA programming mode)

  The order of HW writes is opposite from Lpddr4CaTrainingInitIoTx.

  @param[in] MrcData - The MRC global data.

  @retval none
**/
VOID
Lpddr4CaTrainingRestoreIoTx (
  IN MrcParameters *const MrcData
  );

/**
  This routine is used throughout LPDDR4 ECT code to restore DDR IO from CA training.
  On "Odd" DRAM bytes: disable the following bits:
    DataControl2.ForceRxOn and ForceBiasOn (must be cleared last)
    DataControl0.SenseampTrainingMode, ForceOdtOn and TxDisable

  On "Even" DRAM bytes: disable the following bits:
    DataControl0.TxOn (must be cleared first)
    DataControl5.Ddrcrdqsmaskcnten[10] = 0 (disable the special CBT VrefCA programming mode)

  The order of HW writes is opposite from Lpddr4CaTrainingInitIo.

  @param[in] MrcData - The MRC global data.

  @retval none
**/
VOID
Lpddr4CaTrainingRestoreIo (
  IN MrcParameters *const  MrcData
  );

/**
  Send VrefCA on DQ[6:0] during LPDDR4 CBT.

  @param[in] MrcData  - The MRC global data.
  @param[in] Rank     - The rank to work on.

  @retval none
**/
VOID
MrcSendCaVrefOnDq (
  IN MrcParameters *const   MrcData,
  IN UINT32                 Rank
  );

#endif // _MrcCommandTraining_h_
