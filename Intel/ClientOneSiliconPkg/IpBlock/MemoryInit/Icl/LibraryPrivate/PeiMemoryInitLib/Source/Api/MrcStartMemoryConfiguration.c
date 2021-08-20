/** @file
  Starting point for the core memory reference code.

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

//
// Include files
//

#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcCommandTraining.h"
#include "MrcCommon.h"
#include "MrcCrosser.h"
#include "MrcDebugHook.h"
#include "MrcDebugPrint.h"
#include "MrcGeneral.h"
#include "MrcGlobal.h"
#include "MrcBdat.h"
#include "MrcMcConfiguration.h"
#include "MrcMemoryMap.h"
#include "MrcMemoryScrub.h"
#include "MrcReadDqDqs.h"
#include "MrcReadReceiveEnable.h"
#include "MrcRegisterCache.h"
#include "MrcReset.h"
#include "MrcSaveRestore.h"
#include "MrcSpdProcessing.h"
#include "MrcMaintenance.h"
#include "MrcStartMemoryConfiguration.h"
#include "MrcWriteDqDqs.h"
#include "MrcWriteLeveling.h"
#include "MrcGears.h"

/**
  Print the input parameters to the debug message output port.

  @param[in] MrcData - The MRC global data.

  @retval mrcSuccess
**/

//
// Functions:
//
GLOBAL_REMOVE_IF_UNREFERENCED const CallTableEntry  MrcCallTable[] = {
  ///
  /// The functions are executed in the following order, as the policy flag dictates.
  /// Mrctask, post_code, OEM command, policy_flag, iteration, debug_string
  ///
  {MrcEarlyOverrides,               MRC_EARLY_OVERRIDES,        OemEarlyOverrides,        1, MF_COLD | MF_WARM | MF_S3 | MF_FAST | MF_GV_LOW                         ,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("MRC Early Overrides")},
  {MrcSafeMode,                     MRC_SAFE_MODE,              OemMrcSafeMode,           1, MF_COLD | MF_WARM | MF_S3 | MF_FAST | MF_GV_LOW                         ,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Safe Mode Override")},
  {MrcFastBootPermitted,            MRC_FAST_BOOT_PERMITTED,    OemFastBootPermitted,     1,                             MF_FAST | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Fast boot permitted")},
  {MrcRestoreNonTrainingValues,     MRC_RESTORE_NON_TRAINING,   OemRestoreNonTraining,    1,           MF_WARM | MF_S3 | MF_FAST | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Restore non-training values")},
#ifdef MRC_DEBUG_PRINT
  {MrcPrintInputParameters,         MRC_PRINT_INPUT_PARAMS,     OemPrintInputParameters,  1, MF_COLD | MF_WARM         | MF_FAST | MF_GV_LOW                         ,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Print input parameters")},
#endif // MRC_DEBUG_PRINT
  {MrcSpdProcessing,                MRC_SPD_PROCESSING,         OemSpdProcessingRun,      1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("SPD PROCESSING")},
  {MrcSetOverrides,                 MRC_SET_OVERRIDES,          OemSetOverride,           1, MF_COLD | MF_WARM | MF_S3 | MF_FAST | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("MRC Auto Updates and Overrides")},
  {MrcMcCapability,                 MRC_MC_CAPABILITY,          OemMcCapability,          1, MF_COLD | MF_WARM | MF_S3 | MF_FAST | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("MC Capabilities")},
  {MrcFrequencyLock,                MRC_FREQ_LOCK,              OemFrequencySet,          1, MF_COLD | MF_WARM | MF_S3 | MF_FAST | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("MC Frequency Lock")},
  {MrcMemorySsInit,                 MRC_MEMORY_SS_INIT,         OemMemorySsInit,          1, MF_COLD | MF_WARM | MF_S3 | MF_FAST | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Memory SubSystem Config")},
  {MrcDdrIoPreInit,                 MRC_DDRIO_PREINIT,          OemDdrPhyInit,            1, MF_COLD | MF_WARM | MF_S3 | MF_FAST | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("DDRIO Config - Pre DCC")},
  {MrcDccInitialization,            MRC_DCC_INIT,               OemDccInit,               1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("DCC Initialization")},
  {MrcDdrIoInit,                    MRC_DDRIO_INIT,             OemDdrPhyInit,            1, MF_COLD | MF_WARM | MF_S3 | MF_FAST | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("DDRIO Config - Post DCC")},
  {MrcMcConfiguration,              MRC_MC_CONFIG,              OemMcInitRun,             1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("MC Config")},
  {MrcDdrScompInit,                 MRC_DDRSCOMP_INIT,          OemDdrScompInit,          1, MF_COLD                   | MF_FAST | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("DDR SCOMP Config")},
  {MrcSetMemoryMap,                 MRC_MC_MEMORY_MAP,          OemMcMemoryMap,           1, MF_COLD | MF_WARM | MF_S3 | MF_FAST                         | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("MC MEMORY MAP")},

  {MrcResetSequence,                MRC_RESET_SEQUENCE,         OemMcResetRun,            1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("JEDEC RESET")},
  {MrcPreTraining,                  MRC_PRE_TRAINING,           OemPreTraining,           1, MF_COLD | MF_WARM         | MF_FAST | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Pre-Training")},
  {MrcSenseAmpOffsetTraining,       MRC_SENSE_AMP_OFFSET,       OemSenseAmpTraining,      1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("SenseAmp Offset Training")},
  {MrcEarlyReadMprTimingCentering2D,MRC_EARLY_RDMPR_TIMING_2D,  OemEarlyReadMprDqDqs2D,   1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Early ReadMPR Timing Centering 2D")},
  {MrcEarlyCommandTraining,         MRC_EARLY_COMMAND,          OemEarlyCommandTraining,  1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Early Command Training")},
  {MrcEarlyCmdVoltageCentering,     MRC_EARLY_CMDVC,            OemEarlyCmdVoltCentering, 1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Early Command Voltage Centering") },
  {MrcReadLevelingTraining,         MRC_RECEIVE_ENABLE,         OemReceiveEnable,         1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Read Leveling training")},
  {MrcReadMprTraining,              MRC_READ_MPR,               OemReadMprTraining,       1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Read MPR training")},
  {MrcEarlyReadMprTimingCentering2D,MRC_EARLY_RDMPR_TIMING_2D,  OemEarlyRmpr2DPostEct,    1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Early ReadMPR Timing Centering 2D High Freq") },

  {MrcJedecWriteLevelingTraining,   MRC_JEDEC_WRITE_LEVELING,   OemJedecWriteLeveling,    1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Jedec Write Leveling training")},
  {MrcWriteLevelingFlyByTraining,   MRC_WRITE_LEVELING_FLYBY,   OemWriteLevelingFlyby,    1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH          | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Write Leveling FlyBy training")},
  {MrcEarlyWriteTimingCentering2D,  MRC_EARLY_WRITE_TIMING_2D,  OemEarlyWriteDqDqs2D,     1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Early Write Timing Centering 2D")},
  {MrcWriteTimingCentering,         MRC_WRITE_TIMING_1D,        OemWriteDqDqs,            1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Write Timing Centering")},
//{MrcDdr4DeviceMap,                MRC_DDR4_MAPPING,           OemDdr4Map,               1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("DDR4 PDA Mapping")},
  {MrcWriteVoltageCentering,        MRC_WRITE_VOLTAGE_1D,       OemWriteVoltage,          1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Write Voltage Centering")},
//{MrcSenseAmpOffsetCorrection,     MRC_SENSAMP_OFFSET_CORR,    OemSenseAmpCorrection,    1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH ,                  MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Sense amplifier offset correction")},
  {MrcEarlyReadTimingCentering2D,   MRC_EARLY_READ_TIMING_2D,   OemEarlyReadDqDqs2D,      1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH          | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Early Read Timing Centering 2D")},
  {MrcReadVoltageCentering,         MRC_READ_VOLTAGE_1D,        OemReadVoltage,           1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Read Voltage Centering")},
//{MrcTxTcoCompTraining,            MRC_TXTCO_COMP_TRAINING,    OemTxTcoCompTraining,     1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Write TCO Comp Training")},
//{MrcTxTcoDqsCompTraining,         MRC_TXTCO_DQS_TRAINING,     OemTxTcoDqsCompTraining,  1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Write TCO DqsP/N/Bypass Training")},
  {MrcReadTimingCentering,          MRC_READ_TIMING_1D,         OemReadDqDqs,             1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Read Timing Centering")},

// This is used for debug
//  {CommandPlot2D,                 MRC_CMD_PLOT_2D,            OemReadDqDqs,             1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("2D command plot")},

  {MrcPostTraining,                 MRC_POST_TRAINING,          OemPostTraining,          1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Post-training")},

  {MrcLateCommandTraining,          MRC_LATE_COMMAND,           OemLateCommandTraining,   1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Late command training")},

//{MrcClkTcoCompTraining,           MRC_CLKTCO_COMP_TRAINING,   OemClkTcoCompTraining,    1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("ClkTCO Comp Training")},
  {MrcCmdVoltageCentering,          MRC_CMD_VREF,               OemCmdVoltCentering,      1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Command Voltage Centering")},
  {MrcCmdDsTxEq,                    MRC_CMD_DS,                 OemCmdDriveStrengthEq,    1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Command Drive Strength and Equalization 2D") },
  {MrcCmdSlewRate,                  MRC_CMD_SR,                 OemCmdSlewRate,           1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Command Slew Rate Training")},

  {MrcPowerSavingMeter,             MRC_PWR_MTR,                OemPowerSavingMeter,      1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("PowerSavingMeter Base Line Update")},
  {MrcDimmOdtCaTraining,            MRC_DIMM_ODT_CA,            OemDimmOdtCaTraining,     1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("DIMM CA ODT Training")},
  {MrcDimmRonTraining,              MRC_DIMM_RON,               OemDimmRonTraining,       1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("DIMM Ron Training")},
  {MrcDimmODTTraining,              MRC_DIMM_ODT,               OemDimmODTTraining,       1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("DIMM ODT Training")},
  {MrcWriteEqDsTraining,            MRC_WRITE_DS,               OemWriteDriveStrengthEq,  1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Write Drive Strength and Equalization 2D")},
//{MrcWriteDsUpDnTraining,          MRC_WRITE_DS,               OemWriteDriveUpDn,        1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Write Drive Strength Up/Dn 2D")},
  {MrcWriteSlewRate,                MRC_WRITE_SR,               OemWriteSlewRate,         1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Write Slew Rate")},
  {MrcReadAmplifierPower,           MRC_READ_AMP_POWER,         OemReadAmplifierPower,    1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Read Amplifier Power") },
  {MrcReadEQTraining,               MRC_READ_EQ,                OemReadEQTraining,        1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Read Equalization Training")},
//{MrcDqDfeTraining,                MRC_DQ_DFE_TRAINING,        OemDqDfeTraining,         1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("DQ DFE Training")},
  {MrcSenseAmpOffsetTraining,       MRC_SENSE_AMP_OFFSET,       OemSenseAmpRetraining,    1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("SenseAmp Offset Retraining")},
  {MrcReadODTTraining,              MRC_READ_ODT,               OemReadODTTraining,       1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Read ODT Training") },
  {MrcOptimizeComp,                 MRC_CMP_OPT,                OemOptimizeComp,          1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Comp Optimization Training")},

//{MrcPerBitDeskewCalibration,      MRC_PBD_DESKEW_CAL,         OemPerBitDeskewCal,       1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Read Per Bit Deskew Calibration")},
  {MrcWriteVoltageCentering2D,      MRC_WRITE_VREF_2D,          OemWriteVoltCentering2D,  1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Write Voltage Centering 2D")},
  {MrcReadVoltageCentering2D,       MRC_READ_VREF_2D,           OemReadVoltCentering2D,   1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Read Voltage Centering 2D")},
  {MrcWriteTimingCentering2D,       MRC_WRITE_TIMING_2D,        OemWriteDqDqs2D,          1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Write Timing Centering 2D")},
  {MrcReadTimingCentering2D,        MRC_READ_TIMING_2D,         OemReadDqDqs2D,           1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Read Timing Centering 2D")},
  {MrcReceiveEnTimingCentering,     MRC_RCVEN_TIMING_1D,        OemRcvEnCentering1D,      1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Receive Enable Timing Centering")},
//{MrcTxTcoDqsCompTraining,         MRC_TXTCO_DQS_TRAINING,     OemTxTcoDqsCompTraining,  1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Write TCO DqsP/N/Bypass Training")},
  {MrcRoundTripLatency,             MRC_ROUND_TRIP_LAT,         OemRoundTripLatency,      1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Round Trip Latency Training")},
//{MrcTurnAroundTiming,             MRC_TURN_AROUND,            OemTurnAroundTimes,       1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Turn Around Trip Training")},
  {MrcRetrainMarginCheck,           MRC_RETRAIN_CHECK,          OemRetrainMarginCheck,    1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   1,                 MRC_DEBUG_TEXT("Check Margin for Retrain")},
  {MrcRankMarginTool,               MRC_RMT_TOOL,               OemRmt,                   1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Rank Margin Tool")},
  {MrcRankMarginToolBit,            MRC_RMT_TOOL_BIT,           OemRmtPerBit,             1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Rank Margin Tool Bit")},
  {MrcPowerSavingMeter,             MRC_PWR_MTR,                OemPowerSavingMeter,      1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("PowerSavingMeter update")},


  {MrcWriteDqDqsReTraining,         MRC_WRITE_DQ_DQS_RETRAINING,OemWriteDqDqsReTraining,  1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Write DQ/DQS Retraining")},

  {MrcFillMrScratchRegs,            MRC_MR_FILL,                OemNumOfCommands,         1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Save MRs to Scratch Registers") },
//{MrcDccReplica,                   MRC_DCC_REPLICA,            OemDccReplica,            1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("DCC Replica")},

  {MrcMcActivate,                   MRC_MC_ACTIVATE,            OemMrcActivate,           1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("MRC activate")},
  {MrcNormalMode,                   MRC_NORMAL_MODE,            OemNormalMode,            1, MF_COLD                                                     | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Normal Operation")},
  {MrcSaveMCValues,                 MRC_SAVE_MC_VALUES,         OemSaveMCValues,          1, MF_COLD                             | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Save MC Values")},
  {MrcUpdateSavedMCValues,          MRC_UPDATE_SAVE_MC_VALUES,  OemUpdateSaveMCValues,    1,                             MF_FAST |                         MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Update MC Values in Fast flow")},
  {MrcRestoreTrainingValues,        MRC_RESTORE_TRAINING,       OemRestoreTraining,       1,           MF_WARM | MF_S3 | MF_FAST | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Restore Training Values")},
  {MrcResetSequence,                MRC_RESET_SEQUENCE,         OemMcResetRun,            1,           MF_WARM         | MF_FAST | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("JEDEC RESET on Fast flow")},
//{MrcRankMarginTool,               MRC_RMT_TOOL,               OemRmt,                   1,                             MF_FAST | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Rank Margin Tool on Fast flow")},
  {MrcMarginLimitCheck,             MRC_MARGIN_LIMIT_CHECK,     OemMarginLimitCheck,      1,                             MF_FAST | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Margin limit Check on Fast Flow")},

  {MrcNormalMode,                   MRC_NORMAL_MODE,            OemNormalMode,            1,                             MF_FAST                         | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Normal Operation For Fast flow") },
  {MrcSelfRefreshExit,              MRC_SELF_REFRESH_EXIT,      OemSelfRefreshExit,       1,           MF_WARM | MF_S3                                   | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Perform Self Refresh Exit")},
  {MrcNormalMode,                   MRC_NORMAL_MODE,            OemNormalMode,            1,           MF_WARM | MF_S3                                   | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Normal Operation For Warm / S3 flow")},
  {MrcThermalConfig,                MRC_THERMAL_CONFIG,         OemThermalConfig,         1, MF_COLD | MF_WARM | MF_S3 | MF_FAST                         | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Configure Thermal values")},
  {MrcIbecc,                        MRC_IBECC,                  OemIbecc,                 1, MF_COLD | MF_WARM | MF_S3 | MF_FAST | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("MRC In-band ECC") },
  {MrcAliasCheck,                   MRC_ALIAS_CHECK,            OemAliasCheck,            1, MF_COLD                                                     | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("MRC Memory alias check")},
  {MrcEccClean,                     MRC_ECC_CLEAN_START,        OemHwMemInit,             1, MF_COLD | MF_WARM         | MF_FAST                         | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("MRC Memory Scrubbing")},
  {MrcSaGvSwitch,                   MRC_SA_GV_SWITCH,           OemSaGvSwitch,            1, MF_COLD | MF_WARM | MF_S3 | MF_FAST | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("MRC SA GV Switch")},
  {MrcDccFinalization,              MRC_DCC_FINAL,              OemDccFinal,              1, MF_COLD | MF_WARM | MF_S3 | MF_FAST                         | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("DCC Finalization")},
  {MrcTxtAliasCheck,                MRC_TXT_ALIAS_CHECK,        OemTxtAliasCheck,         1, MF_COLD | MF_WARM         | MF_FAST                         | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("TXT Memory alias check")},

  {MrcDone,                         MRC_DONE,                   OemMrcDone,               1, MF_COLD | MF_WARM | MF_S3 | MF_FAST                         | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("MRC done")},
#ifdef BDAT_SUPPORT
  {MrcFillBdatStructure,            MRC_FILL_BDAT_STRUCTURE,    OemMrcFillBdat,           1, MF_COLD                                                     | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("MRC Fill BDAT Structure")},
#endif // BDAT_SUPPORT
};

/**
  this function use by the OEM to do dedicated task during the MRC.

  @param[in] MrcData           - include all the MRC data
  @param[in] OemStatusCommand  - A command that indicates the task to perform.
  @param[in] ptr               - general ptr for general use.

  @retval The status of the task.
**/
MrcStatus
MrcInternalCheckPoint (
  IN MrcParameters        *MrcData,
  IN MrcOemStatusCommand  OemStatusCommand,
  IN void                 *ptr
  )
{
  MrcInput           *Inputs;
  MRC_FUNCTION       *MrcCall;
  MrcOutput          *Outputs;
  MrcStatus          Status;
  MrcDdrType         DdrType;
  TrainingStepsEn    *TrainingEnables;
  TrainingStepsEn2   *TrainingEnables2;
  BOOLEAN            Ddr4;
  BOOLEAN            Lpddr4;
  BOOLEAN            DtHalo;
  BOOLEAN            IclB0;
  UINT32             Offset;


  Status      = mrcSuccess;
  Inputs      = &MrcData->Inputs;
  MrcCall     = Inputs->Call.Func;
  Outputs     = &MrcData->Outputs;
  DdrType     = Outputs->DdrType;
  TrainingEnables   = &Inputs->TrainingEnables;
  TrainingEnables2  = &Inputs->TrainingEnables2;

  Lpddr4 = (DdrType == MRC_DDR_TYPE_LPDDR4);
  Ddr4   = (DdrType == MRC_DDR_TYPE_DDR4);
  DtHalo = (Inputs->CpuModel == cmICL_DT_HALO_R);
  IclB0  = FALSE;

  if ((Inputs->CpuModel == cmICL_ULX_ULT) && (Inputs->CpuStepping == csIclB0)) {
    // SKPD (PCI 0:0:0:DC ) Register bit 0 : 0 for B0 1 for B1 substep
    Offset = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, SKPD_0_0_0_PCI_REG);
    IclB0  = (((MrcCall->MrcMmioRead32 (Offset)) & MRC_BIT0) == 0);
  }


  switch (OemStatusCommand) {
    case OemMrcSafeMode:
      if (!Inputs->MrcSafeConfig) {
        Status = mrcFail; // Skip this step
      }
      break;

    case OemSpdProcessingRun:
      break;

    case OemPreTraining:
      break;

    case OemMcResetRun:
      if (Inputs->SimicsFlag == 1) {
        Status = mrcFail; // Don't run on SIMICS.
      }
      if (!(IclB0 && Ddr4) && (Inputs->BootMode == bmWarm)) {
        Status = mrcFail;
      }
      break;

    case OemSelfRefreshExit:
      if (IclB0 && (Inputs->BootMode == bmWarm) && Ddr4) {
        Status = mrcFail;
      }
      break;

    case OemTxTcoCompTraining:
      if (!TrainingEnables2->TXTCO) {
        Status = mrcFail; // Skip this step
      }
      break;

    case OemTxTcoDqsCompTraining:
      if (!TrainingEnables2->TXTCODQS) {
        Status = mrcFail; // Skip this step
      }
      break;

    case OemClkTcoCompTraining:
      if (!TrainingEnables2->CLKTCO) {
        Status = mrcFail; // Skip this step
      }
      break;

    case OemEarlyCommandTraining:
      if ((!TrainingEnables->ECT) || Ddr4) { // ECT is for LPDDR4 only
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemEarlyCmdVoltCentering:
      if ((!TrainingEnables->CMDVC) || Ddr4 || (Outputs->Frequency <= f2400)) { // Only needed on LP4 at high speed
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemSenseAmpTraining:
      if (!TrainingEnables->SOT) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReadMprTraining:
      if (!TrainingEnables->RDMPRT) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReceiveEnable:
      if (!TrainingEnables->RCVET) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemJedecWriteLeveling:
    case OemWriteLevelingFlyby:
      if (!TrainingEnables->JWRL) {
        Status = mrcFail; // Skip this training step
      }
      if ((OemStatusCommand == OemJedecWriteLeveling) && Inputs->LoopBackTest) {
        Status = mrcFail;
      }
      break;

    case OemWriteDqDqs:
      if (!TrainingEnables->WRTC1D) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemWriteDqDqsReTraining:
      if (!Lpddr4 || !Inputs->Lp4DqsOscEn) { // This is for LPDDR4 only
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemSenseAmpCorrection:
      if (!TrainingEnables2->SOTC) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReadVoltage:
      if (!TrainingEnables2->RDVC1D) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemWriteVoltage:
      if (!TrainingEnables->WRVC1D) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemEarlyWriteDqDqs2D:
      if ((!TrainingEnables->EWRTC2D) || ((Outputs->Frequency == f1067) && Lpddr4)) { // Disable For LPDDR4 1067
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemEarlyReadDqDqs2D:
      if (!TrainingEnables->ERDTC2D) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemEarlyRmpr2DPostEct:
      if ((!Lpddr4) || (Outputs->Frequency == f1067)) {
        Status = mrcFail;
        break;
      }
      // Fall through if we are LPDDR4 to check input parameters
    case OemEarlyReadMprDqDqs2D:
      if (!TrainingEnables->ERDMPRTC2D) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReadDqDqs:
      if (!TrainingEnables->RDTC1D) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemPerBitDeskewCal:
      if (Inputs->RdTPbdDis && Inputs->WrTPbdDis) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemDdr4Map:
      if ((!Inputs->DDR4MAP) || !Ddr4) { // This is for DDR4 only
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemDimmODTTraining:
      if ((!TrainingEnables->DIMMODTT) || DtHalo) {  // @todo: Not ready for DT/HALO
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemDimmOdtCaTraining:
      if ((!TrainingEnables2->DIMMODTCA) || !Lpddr4) {  // This is for Lpddr4 only
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemDimmRonTraining:
      if ((!TrainingEnables->DIMMRONT) || DtHalo || Lpddr4) {  // @todo: Not ready for DT/HALO and LP4
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemWriteSlewRate:
      if (!TrainingEnables->WRSRT || Lpddr4) {  // Leave it in ByPass mode for Lp4/x
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemWriteDriveUpDn:
      if (!TrainingEnables->WRDSUDT || !Ddr4 || DtHalo) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemWriteDriveStrengthEq:
      if (!TrainingEnables->WRDSEQT) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReadODTTraining:
      if (!TrainingEnables->RDODTT) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReadEQTraining:
      if (!TrainingEnables->RDEQT || !Ddr4) { // Enable on DDR4 only
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemPostTraining:
      if (Lpddr4 || !TrainingEnables->LCT) { // Cannot switch to 1N/2N without running LCT
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReadAmplifierPower:
      if (!TrainingEnables->RDAPT || (Inputs->PowerTrainingMode == MrcTmMargin)) {  // Disable in Margin training mode
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemOptimizeComp:
      if ((Inputs->SimicsFlag == 1) || ((Outputs->Frequency == f1067) && Lpddr4)) { // Disable For LPDDR4 1067 due to inablity to recenter TxV
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemWriteDqDqs2D:
      if (!TrainingEnables->WRTC2D) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReadDqDqs2D:
      if (!TrainingEnables->RDTC2D) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemCmdVoltCentering:
      if (!TrainingEnables->CMDVC) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemCmdSlewRate:
      if (!TrainingEnables2->CMDSR ) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemCmdDriveStrengthEq:
      if (!TrainingEnables2->CMDDSEQ ) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemWriteVoltCentering2D:
      if (!TrainingEnables->WRVC2D) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReadVoltCentering2D:
      if (!TrainingEnables->RDVC2D) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemLateCommandTraining:
      if (!TrainingEnables->LCT) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemRoundTripLatency:
      if (!TrainingEnables->RTL) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemTurnAroundTimes:
      if ((!TrainingEnables->TAT) || Lpddr4) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemRcvEnCentering1D:
      if ((!TrainingEnables->RCVENC1D) || Ddr4) {
        Status = mrcFail;  // Skip this step for non-LPDDR
      }
      break;

    case OemRetrainMarginCheck:
      if ((!TrainingEnables->RMC) || (Inputs->PowerTrainingMode != MrcTmPower)) {
        Status = mrcFail; // Skip if disabled or not in Power Training mode
      }
      break;
    case OemRmt:
      if (!TrainingEnables->RMT) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemRmtPerBit:
      if (!TrainingEnables2->RMTBIT) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemSaveMCValues:
      break;

    case OemUpdateSaveMCValues:
      break;

    case OemAliasCheck:
      if (!TrainingEnables->ALIASCHK) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemBeforeNormalMode:
      break;

    case OemAfterNormalMode:
      break;

    case OemThermalConfig:
      break;

    case OemFrequencySetDone:
      break;

    case OemSaGvSwitch:
      if ((Inputs->SaGv != MrcSaGvEnabled)
           && (!Lpddr4)
         ) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemPowerSavingMeter:
      if (Inputs->SimicsFlag == 1) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemDccInit:
    case OemDccFinal:
      if (!TrainingEnables2->DCC) {
        Status = mrcFail; // Skip this step
      }
      break;

    case OemDccReplica:
      if (!TrainingEnables2->PERIODICDCC) {
        Status = mrcFail; // Skip this step
      }
      break;

    case OemDqDfeTraining:
      if (!TrainingEnables2->DQDFE || (Outputs->Frequency < f3200)) {
        Status = mrcFail; // Skip this step
      }
      break;

    case OemMarginLimitCheck:
      if (Inputs->MarginLimitCheck == MARGIN_CHECK_DISABLE) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemSenseAmpRetraining:
      if (!Outputs->SenseAmpRetrain) {
        Status = mrcFail; // Skip this training step
      }
      break;

    default:
      break;
  }
  //
  // Allow Overriding the internal checkpoint decision.
  //
  MrcCall->MrcCheckpoint (MrcData, OemStatusCommand, &Status);
  return Status;
}

/**
  Prepare MRC structures for next MRC Iteraion (SAGV or margin retrain).

  @param[in, out] MrcData - Include all MRC global data.
  @param[in]      Retrain - Turn on/off UpmPwrRetrainFlag.

**/
void
MrcPrepareNextMrcIteration (
  IN OUT MrcParameters *const MrcData,
  IN BOOLEAN                  Retrain
  )
{
  UINT16                  PrevRdDataValid;
  BOOLEAN                 PrevGear2Ever;
  const MRC_FUNCTION      *MrcCall;
  MrcIntOutput            *MrcIntData;
  MrcOutput               *Outputs;
  MrcInput                *Inputs;
#ifdef BDAT_SUPPORT
  UINT16                    Index;
  MRC_BDAT_SCHEMA_LIST_HOB  *SaveBdatSchemasHob;
  BDAT_MEMORY_DATA_HOB      *SaveBdatMemoryHob[MAX_SCHEMA_LIST_LENGTH];
#endif

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  MrcIntData = ((MrcIntOutput *)(MrcData->IntOutputs.Internal));
  MrcCall = MrcData->Inputs.Call.Func;

  PrevRdDataValid = MrcIntData->MaxRdDataValid;
  PrevGear2Ever = Outputs->Gear2Ever;
#ifdef BDAT_SUPPORT
  SaveBdatSchemasHob = Outputs->BdatSchemasHob.Pointer;
  for (Index = 0; Index < MAX_SCHEMA_LIST_LENGTH; Index++) {
    SaveBdatMemoryHob[Index] = Outputs->BdatMemoryHob[Index].Pointer;
  }
#endif // BDAT_SUPPORT
  MrcCall->MrcSetMem ((UINT8 *) Outputs, sizeof (MrcOutput), 0);
  MrcCall->MrcSetMem ((UINT8 *) MrcIntData, sizeof (MrcIntOutput), 0);
  MrcIntData->Size = sizeof (MrcOutput);
  Outputs->Size = sizeof (MrcOutput);
  MrcIntData->MaxRdDataValid = PrevRdDataValid;
  Outputs->Gear2Ever = PrevGear2Ever;
  Outputs->UpmPwrRetrainFlag = Retrain;
#ifdef BDAT_SUPPORT
  Outputs->BdatSchemasHob.Pointer = SaveBdatSchemasHob;
  for (Index = 0; Index < MAX_SCHEMA_LIST_LENGTH; Index++) {
    Outputs->BdatMemoryHob[Index].Pointer = SaveBdatMemoryHob[Index];
  }
#endif // BDAT_SUPPORT
  MRC_DEBUG_MSG_OPEN (MrcData, Inputs->DebugLevel, Inputs->DebugStream, Inputs->SerialBuffer.DataN, Inputs->SerialBufferSize);
}

/**
  Initializes the memory controller and DIMMs.

  @param[in, out] MrcData                - Include all MRC global data.
  @param[in]      Select                 - The post code of the call table entry to execute.
  @param[in, out] CurrentSaGvPoint       - The SAGV point that we want to execute the Select post code entry or to continue from (relevant if SAGV enabled).
  @param[in]      ExecuteFromSelectPoint - Execute Memory configuration from (Select,CurrentSaGvPoint) to the end

  @retval mrcSuccess if the initialization succeeded, otherwise an error status indicating the failure.
**/
MrcStatus
MrcStartMemoryConfiguration (
  IN OUT MrcParameters *const MrcData,
  IN     MrcPostCode          Select,
  IN OUT MrcSaGvPoint  *const CurrentSaGvPoint,
  IN BOOLEAN                  ExecuteFromSelectPoint
  )
{
  const MRC_FUNCTION      *MrcCall;
  const CallTableEntry    *Task;
  MrcDebug                *Debug;
  MrcInput                *Inputs;
  MrcOutput               *Outputs;
  MrcIntOutput            *MrcIntData;
  MrcSaGvPoint            SaGvPoint;
  MrcSaGvPoint            SaGvStart;
  MrcSaGvPoint            SaGvEnd;
  MrcSaGv                 SaGv;
  MrcPostCode             post_code;
  MrcPostCode             PostCodeOut;
  MrcStatus               CpStatus;
  MrcStatus               MrcStatus;
  MRC_BOOT_MODE           BootMode;
  MrcUpmPwrRetrainLimits  RetrainLimits[MRC_NUMBER_UPM_PWR_RETRAIN_MARGINS];
  UINT64                  start_time;
  UINT64                  finish_time;
  UINTN                   LowestStackAddr;
  INT32                   DebugLevel;
  UINT32                  ElapsedTime;
  UINT32                  TotalTime;
  UINT32                  PointTime;
  UINT32                  RetrainLoop;
  UINT16                  index;
  UINT8                   Run;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  SaGv    = Inputs->SaGv;

  BootMode  = Inputs->BootMode;
  DebugLevel = Inputs->DebugLevel;
  if (Select == 0) {
    MrcVersionGet (MrcData, &Outputs->Version);
    MrcVersionPrint (MrcData, &Outputs->Version);
  }
  MrcStatus = (Select == 0) ? mrcFail : mrcSuccess;
  post_code = MRC_INITIALIZATION_START;
  Run       = 1;
  TotalTime = 0;
  LowestStackAddr = Debug->LowestStackAddr.DataN;

  if (SaGv == MrcSaGvEnabled) {
    // check if we are forced to specific SAGV in selected step
    if ((CurrentSaGvPoint != NULL) && (Select != 0)) {
      // restore current SAGV points
      if (*CurrentSaGvPoint != MrcSaGvPointMax) {
        SaGvStart = *CurrentSaGvPoint;
        SaGvEnd = (ExecuteFromSelectPoint) ? MrcSaGvPointHigh : *CurrentSaGvPoint;
      } else {
        SaGvStart = MrcSaGvPointLow;
        SaGvEnd = MrcSaGvPointLow;
      }
    } else {
      SaGvStart = MrcSaGvPointLow;
      SaGvEnd = MrcSaGvPointHigh;
    }


  } else {
    if ((SaGv == MrcSaGvDisabled) || (SaGv == MrcSaGvFixedHigh)) {
      SaGvStart = MrcSaGvPointHigh;
    } else if (SaGv == MrcSaGvFixedMid) {
      SaGvStart = MrcSaGvPointMid;
    } else {
      // SaGv == MrcSaGvFixedLow
      SaGvStart = MrcSaGvPointLow;
    }
    SaGvEnd = SaGvStart;
  }

  for (SaGvPoint = SaGvStart; Run && (SaGvPoint <= SaGvEnd); SaGvPoint++) {
    // First iteration  = LOW point
    // Second iteration = MID point
    // Third iteration = HIGH point

    MrcIntData->SaGvPoint = SaGvPoint;
    // Update  *CurrentSaGvPoint for future calling
    if (CurrentSaGvPoint != NULL) {
      *CurrentSaGvPoint = SaGvPoint;
    }
    Inputs->Iteration = 0;
    PointTime = 0;

    //
    // Reset UPM/PWR limits to initial values; previous SAGV point might have done retrain.
    //
    MrcCall->MrcCopyMem (
      (UINT8 *) RetrainLimits,
      (UINT8 *) InitialLimits,
      sizeof (MrcUpmPwrRetrainLimits) * MRC_NUMBER_UPM_PWR_RETRAIN_MARGINS
      );

    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "SAGV: %sabled, running at %s point\n",
      (SaGv == MrcSaGvEnabled) ? "En" : "Dis",
      gFreqPointStr[SaGvPoint]
      );

    for (RetrainLoop = 0; RetrainLoop <= 1; RetrainLoop++) {
      MrcVersionGet (MrcData, &Outputs->Version);
      MrcIntData->UpmPwrRetrainLimits.Pointer = RetrainLimits;
      for (index = 0; Run && (index < ARRAY_COUNT (MrcCallTable)); index++, post_code++) {
        Task = &MrcCallTable[index];
        //
        // Decide if we need to execute the selected MRC task.
        //
        // If MRC task selected and ExecuteFromSelectPoint == TRUE, it means that we need to execute all MRC tasks from Selected point.
        // By clearing the Select variable we force to continue the execution of all remaining Tasks
        if ((Select != 0) && (ExecuteFromSelectPoint) && (Select == Task->post_code_ovr) ) {
          Select = 0;
        }

        if ((NULL == Task->mrc_task) || (Inputs->Iteration >= Task->iteration)) {
          continue;
        }
        if   (((BootMode == bmS3)   && (Task->policy_flag & MF_S3))
          ||  ((BootMode == bmFast) && (Task->policy_flag & MF_FAST))
          ||  ((BootMode == bmWarm) && (Task->policy_flag & MF_WARM))
          ||  ((BootMode == bmCold) && (Task->policy_flag & MF_COLD))
          ||  ((Select != 0))) {
          if  ((Select == 0) || (Select == Task->post_code_ovr)) {
            if (((MrcIntData->SaGvPoint == MrcSaGvPointLow)  && (Task->policy_flag & MF_GV_LOW))  ||
                ((MrcIntData->SaGvPoint == MrcSaGvPointMid)  && (Task->policy_flag & MF_GV_MID))  ||
                ((MrcIntData->SaGvPoint == MrcSaGvPointHigh) && (Task->policy_flag & MF_GV_HIGH)) ||
                (SaGv != MrcSaGvEnabled)) {
              if (Task->oem_cmd < OemNumOfCommands) {
                CpStatus = MrcInternalCheckPoint (MrcData, Task->oem_cmd, NULL);
                if ((mrcSuccess != CpStatus) && !Inputs->IgnoreCheckPoint) {
                  continue;
                }
              }
              //
              // Output post code to post code I/O port.
              //
              PostCodeOut = (Task->post_code_ovr == POST_CODE_NO_OVR) ? post_code : Task->post_code_ovr;
              if ((Select == 0) || ((Select > 0) && (Select == PostCodeOut))) {
                MrcCall->MrcDebugHook (MrcData, PostCodeOut);
              }
              //
              // Output debug string to serial output and execute the MRC task.
              //
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nMRC task -- %s -- Started.\n", Task->String);
              if (!Task->DebugPrint) {
                DebugLevel = Debug->Level;
                Debug->Level = MSG_LEVEL_NEVER;
              }
              start_time  = MrcCall->MrcGetCpuTime (MrcData);
              MrcStatus   = Task->mrc_task (MrcData);
              finish_time = MrcCall->MrcGetCpuTime (MrcData);
              if (!Task->DebugPrint) {
                Debug->Level = DebugLevel;
              }
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_ERROR,
                "MRC task %s -- %s, Status = %Xh.",
                Task->String,
                (mrcSuccess == MrcStatus) ? "SUCCEEDED" : "FAILED",
                MrcStatus
                );
              if (Debug->LowestStackAddr.DataN < LowestStackAddr) {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, " Stack Depth: %d\n", Debug->TopStackAddr.DataN - Debug->LowestStackAddr.DataN);
                LowestStackAddr = Debug->LowestStackAddr.DataN;
              } else {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n");
              }
              if ((mrcSuccess != MrcStatus) || (Select != 0)) {
                Run = 0;  // Stop task execution on failure or running one Task.
              }

              if (Select == 0) {
                ElapsedTime = (UINT32)(finish_time - start_time);
                TotalTime += ElapsedTime;
                PointTime += ElapsedTime;
                // <MrcTimer Task="Print input parameters" msec="2"/>
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_TIME, "<MrcTimer Task=\"%s\" msec=\"%u\"/>\n", Task->String, ElapsedTime);
              }

              if (Inputs->TrainTrace && (Task->policy_flag & MF_TST)) {
                // <MrcTrainedStateTrace> ... <MrcTrainedStateTrace/>
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "<MrcTrainedStateTrace>\n");
                MrcTrainedStateTrace (MrcData);
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "<MrcTrainedStateTrace/>\n");
              }
              if (Inputs->RmtPerTask && (Task->policy_flag & MF_RMT)) {  // Run RMT after this task
                MrcRankMarginTool (MrcData);
              }
            }
          } // Select match
        } // if boot mode match
      } // for index
      //
      // Check if MRC failed due to RetrainMarginCheck
      //
      if ((MrcStatus == mrcRetrain) && (Select == 0)) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nRerunning training with higher UPM/PWR limits!\n");
        MrcPrepareNextMrcIteration (MrcData, TRUE);
        MrcIntData->SaGvPoint      = SaGvPoint;
        Inputs->Iteration++;
        Run = 1;
      } else {
        break;    // No need to retrain
      }
    } // Retrain loop

    if ((SaGv == MrcSaGvEnabled) && (SaGvPoint != MrcSaGvPointHigh) && (Select == 0)) {
      // Prepare for the next MRC iteration
      MrcPrepareNextMrcIteration (MrcData, FALSE);
    }

    if ((SaGv == MrcSaGvEnabled) && (Select == 0)) {
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_TIME,
        "MRC timer: Total time for SAGV %s point = %u msec.\n",
        gFreqPointStr[SaGvPoint],
        PointTime
        );
    }
  } // for GvPoint

  if (Select == 0) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_TIME, "MRC timer: Total time to execute tasks = %u msec.\n", TotalTime);
  }

  return MrcStatus;
}

/**

@brief

  Get the number of call table entries.

  @param[in, out] MrcData - Include all MRC global data.

  @retval The number of call table entries.

**/
UINT16
MrcGetCallTableCount (
  IN OUT MrcParameters *const MrcData
  )
{
  return ARRAY_COUNT (MrcCallTable);
}
