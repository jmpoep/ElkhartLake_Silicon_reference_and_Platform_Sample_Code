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
#include "MrcDdr3.h"
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
#include "MrcDdrIoApi.h"

/**
  Print the input parameters to the debug message output port.

  @param[in] MrcData - The MRC global data.

  @retval mrcSuccess
**/

//
// Functions:
//
const CallTableEntry  MrcCallTable[] = {
  ///
  /// The functions are executed in the following order, as the policy flag dictates.
  /// Mrctask, post_code, OEM command, policy_flag, iteration, debug_string
  ///
  {MrcEarlyOverrides,               MRC_EARLY_OVERRIDES,        OemEarlyOverrides,      1, MF_COLD | MF_WARM | MF_S3 | MF_FAST | MF_GV_1                              ,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("MRC Early Overrides")},
  {MrcSafeMode,                     MRC_SAFE_MODE,              OemMrcSafeMode,         1, MF_COLD | MF_WARM | MF_S3 | MF_FAST | MF_GV_1                              ,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Safe Mode Override")},
  {MrcFastBootPermitted,            MRC_FAST_BOOT_PERMITTED,    OemFastBootPermitted,   1,                             MF_FAST | MF_GV_1                              ,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Fast boot permitted")},
  {MrcRestoreNonTrainingValues,     MRC_RESTORE_NON_TRAINING,   OemRestoreNonTraining,  1,           MF_WARM | MF_S3 | MF_FAST | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Restore non-training values")},
#ifdef MRC_DEBUG_PRINT
  {MrcPrintInputParameters,         MRC_PRINT_INPUT_PARAMS,     OemPrintInputParameters,1, MF_COLD | MF_WARM         | MF_FAST | MF_GV_1                              ,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Print input parameters")},
#endif // MRC_DEBUG_PRINT
  {MrcSpdProcessing,                MRC_SPD_PROCESSING,         OemSpdProcessingRun,    1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("SPD PROCESSING")},
  {MrcSetOverrides,                 MRC_SET_OVERRIDES,          OemSetOverride,         1, MF_COLD | MF_WARM | MF_S3 | MF_FAST | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("MRC Auto Updates and Overrides")},
  {MrcMcCapability,                 MRC_MC_CAPABILITY,          OemMcCapability,        1, MF_COLD | MF_WARM | MF_S3 | MF_FAST | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("MC Capabilities")},
  {MrcFrequencyLock,                MRC_FREQ_LOCK,              OemFrequencySet,        1, MF_COLD | MF_WARM | MF_S3 | MF_FAST | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("MC Frequency Lock")},
  {MrcMemorySsInit,                 MRC_MEMORY_SS_INIT,         OemMemorySsInit,        1, MF_COLD | MF_WARM | MF_S3 | MF_FAST | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Memory SubSystem Config")},
  {MrcDdrIoPreInit,                 MRC_DDRIO_PREINIT,          OemDdrPhyInit,          1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("DDRIO Config - Pre DCC")},
  {MrcMcConfiguration,              MRC_MC_CONFIG,              OemMcInitRun,           1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("MC Config")},
  {MrcDdrIoInit,                    MRC_DDRIO_INIT,             OemDdrPhyInit,          1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("DDRIO Config - Post DCC")},
  {MrcFllInit,                      MRC_FLL_INIT,               OemFllTraining,         1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("FLL Init")},
  {MrcDdrCompCalPre,                MRC_DDRCOMP_CAL_PRE,        OemDdrCompCalPre,       1, MF_COLD                   | MF_FAST | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("DDR COMP Calc - PreTraining")},
  {MrcDdrScomp,                     MRC_DDRSCOMP_INIT,          OemDdrScompInit,        1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("DDR SCOMP Config")},
  {MrcSetMemoryMap,                 MRC_MC_MEMORY_MAP,          OemMcMemoryMap,         1, MF_COLD | MF_WARM | MF_S3 | MF_FAST                               | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("MC MEMORY MAP")},

  {MrcResetSequence,                MRC_RESET_SEQUENCE,         OemMcResetRun,          1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("JEDEC RESET")},
  {MrcPreTraining,                  MRC_PRE_TRAINING,           OemPreTraining,         1, MF_COLD                   | MF_FAST | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Pre-Training")},
  {MrcSenseAmpOffsetTraining,       MRC_SENSE_AMP_OFFSET,       OemSenseAmpTraining,    1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("SenseAmp Offset Training")},
  {MrcEarlyCommandTraining,         MRC_EARLY_COMMAND,          OemEarlyCommandTraining,1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Early command training")},
  {MrcOffsetCorrectionPre,          MRC_OFFSET_CORRECTION_PRE,  OemOffsetCorrectionPre, 1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("DDR Offset Correction - PreTraining")},
//  {MrcDccInitialization,            MRC_DCC_INIT,               OemDccInit,             1, MF_COLD | MF_GV_LOW | MF_GV_MID | MF_GV_HIGH,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("DCC Initialization")},
  {MrcJedecWCKTraining,             MRC_WCK_LEVELING,           OemWckLeveling,         1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Jedec WCK training")},
  //{MrcEarlyReadMprTimingCentering2D,MRC_EARLY_RDMPR_TIMING_2D,  OemEarlyRmpr2DPostEct,  1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Early ReadMPR Timing Centering 2D High Freq")},
  {MrcReadLevelingTraining,         MRC_RECEIVE_ENABLE,         OemReceiveEnable,       1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Read Leveling training")},
  {MrcReadMprTraining,              MRC_READ_MPR,               OemReadMprTraining,     1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("CPGC-Based Read MPR training")},
  {MrcJedecWriteLevelingTraining,   MRC_JEDEC_WRITE_LEVELING,   OemJedecWriteLeveling,  1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Jedec Write Leveling training")},
  {MrcWriteLevelingFlyByTraining,   MRC_WRITE_LEVELING_FLYBY,   OemWriteLevelingFlyby,  1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Write Leveling FlyBy training")},
  {MrcEarlyWriteTimingCentering2D,  MRC_EARLY_WRITE_TIMING_2D,  OemEarlyWriteDqDqs2D,   1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Early Write Timing Centering 2D")},
  {MrcWriteTimingCentering,         MRC_WRITE_TIMING_1D,        OemWriteDqDqs,          1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Write Timing Centering")},
//{MrcDdr4DeviceMap,                MRC_DDR4_MAPPING,           OemDdr4Map,             1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("DDR4 PDA Mapping")},
  {MrcWriteVoltageCentering,        MRC_WRITE_VOLTAGE_1D,       OemWriteVoltage,        1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Write Voltage Centering")},
  {MrcReadVoltageCentering,         MRC_READ_VOLTAGE_1D,        OemReadVoltage,         1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Read Voltage Centering")},
  {MrcEarlyReadTimingCentering2D,   MRC_EARLY_READ_TIMING_2D,   OemEarlyReadDqDqs2D,    1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Early Read Timing Centering 2D")},
//  {MrcPowerSavingMeter,             MRC_PWR_MTR,                OemPowerSavingMeter,    1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("PowerSavingMeter Base Line Update")},
  {MrcTxDqTcoCompTraining,          MRC_TXDQTCO_COMP_TRAINING,  OemTxDqTcoCompTraining, 1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("TxDqTCO Comp Training")},
  {MrcTxDqsTcoCompTraining,         MRC_TXDQSTCO_COMP_TRAINING, OemTxDqsTcoCompTraining,1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("TxDqsTCO Comp Training")},
  {MrcReadTimingCentering,          MRC_READ_TIMING_1D,         OemReadDqDqs,           1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Read Timing Centering")},
  {MrcCmdVoltageCentering,          MRC_CMD_VREF,               OemCmdVoltCentering,    1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Command Voltage Centering")},
// This is used for debug
//  {CommandPlot2D,                 MRC_CMD_PLOT_2D,            OemReadDqDqs,           1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("2D command plot")},
  {MrcPostTraining,                 MRC_POST_TRAINING,          OemPostTraining,        1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Post-training")},

  {MrcVccDLLBypassTraining,         MRC_VCCDLL_BYPASS,          OemVccDllBypassTraining,1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("VccDLL bypass to VccIOG training")},
  {MrcLateCommandTraining,          MRC_LATE_COMMAND,           OemLateCommandTraining, 1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Late command training")},
//#ifndef LOCAL_STUB_FLAG
//  {MrcClkTcoCompTraining,           MRC_CLKTCO_COMP_TRAINING,   OemClkTcoCompTraining,  1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("ClkTCO Comp Training")},
//#endif // LOCAL_STUB_FLAG
  {MrcCmdVoltageCentering,          MRC_CMD_VREF,               OemCmdVoltCentering,    1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Command Voltage Centering")},
  {MrcCmdEqDsTraining,              MRC_CMD_EQ,                 OemCmdDriveStrengthEq,  1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT("CMD/CTL Drive Strength and Equalization 2D")},
  {MrcCmdSlewRate,                  MRC_CMD_SR,                 OemCmdSlewRate,         1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT("CMD CTL CLK Slew Rate") },
  {MrcCmdDsUpDnTraining,            MRC_CMD_DS,                 OemCmdDriveUpDn,        1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT,          MRC_ITERATION_MAX, MRC_DEBUG_TEXT("CMD/CTL Drive Strength Up/Dn 2D")},
  {MrcDimmOdtCaTraining,            MRC_DIMM_ODT_CA,            OemDimmOdtCaTraining,   1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("DIMM CA ODT Training")},
  {MrcDimmRonTraining,              MRC_DIMM_RON,               OemDimmRonTraining,     1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("DIMM Ron Training")},
  {MrcDimmODTTraining,              MRC_DIMM_ODT,               OemDimmODTTraining,     1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("DIMM ODT Training")},
  {MrcWriteEqDsTraining,            MRC_WRITE_EQ,               OemWriteDriveStrengthEq,1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Write Drive Strength and Equalization 2D")},
  {MrcWriteDsUpDnTraining,          MRC_WRITE_DS,               OemWriteDriveUpDn,      1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Write Drive Strength Up/Dn 2D")},
  {MrcReadODTTraining,              MRC_READ_ODT,               OemReadODTTraining,     1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Read ODT Training")},
  {MrcWriteSlewRate,                MRC_WRITE_SR,               OemWriteSlewRate,       1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Write Slew Rate")},
  {MrcPanicVttDnLpTraining,         MRC_PANIC_VTT_DN_LP,        OemPanicVttDnLpTraining,1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("PanicVttDnLp Training") },
  {MrcRxVrefDecapTraining,          MRC_READ_VREF_DECAP,        OemReadVrefDecapTraining,1, MF_COLD                            | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Read Vref Decap Training")},
  {MrcVddqTraining,                 MRC_VDDQ,                   OemVddqTraining,        1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Vddq Training") },
  {MrcReadEQTraining,               MRC_READ_EQ,                OemReadEQTraining,      1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Read Equalization Training")},
  {MrcReadAmplifierPower,           MRC_READ_AMP_POWER,         OemReadAmplifierPower,  1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Read Amplifier Power")},
//  {MrcOptimizeComp,                 MRC_CMP_OPT,                OemOptimizeComp,        1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Comp Optimization Training")},
//  {MrcForceOltm,                    MRC_FORCE_OLTM,             OemForceOltm,           1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Force OLTM")},

//  {MrcPerBitDeskewCalibration,      MRC_PBD_DESKEW_CAL,         OemPerBitDeskewCal,     1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Read Per Bit Deskew Calibration")},
  {MrcWriteVoltageCentering2D,      MRC_WRITE_VREF_2D,          OemWriteVoltCentering2D,1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Write Voltage Centering 2D")},
  {MrcReadVoltageCentering2D,       MRC_READ_VREF_2D,           OemReadVoltCentering2D, 1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Read Voltage Centering 2D")},
  {MrcWriteTimingCentering2D,       MRC_WRITE_TIMING_2D,        OemWriteDqDqs2D,        1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Write Timing Centering 2D")},
  {MrcReadTimingCentering2D,        MRC_READ_TIMING_2D,         OemReadDqDqs2D,         1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Read Timing Centering 2D")},
  {MrcReceiveEnTimingCentering,     MRC_RCVEN_TIMING_1D,        OemRcvEnCentering1D,    1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Receive Enable Timing Centering")},

//  {MrcRoundTripLatency,             MRC_ROUND_TRIP_LAT,         OemRoundTripLatency,    1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Round Trip Latency Training")},

//  {MrcVccDllFFTiming,               MRC_VCCDLL_FFTIMING,        OemVccDllFFTiming            ,1, MF_COLD                       | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("VccDll FF Timing")},
//  {MrcVccDllFFOffsetCorrection,     MRC_VCCDLL_FFOFFSETCORRECTION,OemVccDllFFOffsetCorrection,1, MF_COLD                       | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("VccDll FF Offset Correction")},
//  {MrcKickBackNoiseCorrection,      MRC_VCCDLL_KBNCORRECTION,   OemVccDllKBNCorrection       ,1, MF_COLD                       | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("VccDll KickBack Noise Correction")},
//  {MrcVsxHiFFTuning,                MRC_VSXHI_FFTUNING,         OemVsxhiFFTuning             ,1, MF_COLD                       | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("VccDllVsxHi Feed Forward tuning")},

  {MrcTurnAroundTiming,             MRC_TURN_AROUND,            OemTurnAroundTimes,     1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4 | MF_RMT | MF_TST, MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Turn Around Trip Training")},

  {MrcRetrainMarginCheck,           MRC_RETRAIN_CHECK,          OemRetrainMarginCheck,  1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   1,                 MRC_DEBUG_TEXT("Check Margin for Retrain")},
  {MrcRankMarginTool,               MRC_RMT_TOOL,               OemRmt,                 1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Rank Margin Tool")},
  {MrcRankMarginToolBit,            MRC_RMT_TOOL_BIT,           OemRmtPerBit,           1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Rank Margin Tool Bit")},
//  {MrcPowerSavingMeter,             MRC_PWR_MTR,                OemPowerSavingMeter,    1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("PowerSavingMeter update")},
  {MrcWriteDqDqsReTraining,         MRC_WRITE_DQ_DQS_RETRAINING,OemWriteDqDqsReTraining,1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Write DQ/DQS Retraining")},
  {MrcSaGvFinal,                    MRC_MR_FILL,                OemNumOfCommands,       1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("SAGV Finalization")},
  //@todo {MrcDccReplica,                   MRC_DCC_REPLICA,            OemDccReplica,          1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("DCC Replica")},
  //@todo {MrcDccFinalization,              MRC_DCC_FINAL,              OemDccFinal,            1, MF_COLD                                                     | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("DCC Finalization for Cold fow")},
  {MrcMcActivate,                   MRC_MC_ACTIVATE,            OemMrcActivate,         1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("MRC activate")},
  {MrcNormalMode,                   MRC_NORMAL_MODE,            OemNormalMode,          1, MF_COLD                                                           | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Normal Operation")},
  {MrcSaveMCValues,                 MRC_SAVE_MC_VALUES,         OemSaveMCValues,        1, MF_COLD                             | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Save MC Values")},
  {MrcRestoreTrainingValues,        MRC_RESTORE_TRAINING,       OemRestoreTraining,     1,           MF_WARM | MF_S3 | MF_FAST | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Restore Training Values")},
  //@todo {MrcDccFinalization,              MRC_DCC_FINAL,              OemDccFinal,            1,           MF_WARM | MF_S3 | MF_FAST                         | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("DCC Finalization for non-Cold flows")},

  {MrcResetSequence,                MRC_RESET_SEQUENCE,         OemMcResetRun,          1,                             MF_FAST | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("JEDEC RESET on Fast flow")},
//{MrcRankMarginTool,               MRC_RMT_TOOL,               OemRmt,                 1,                             MF_FAST | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Rank Margin Tool on Fast flow")},
  {MrcNormalMode,                   MRC_NORMAL_MODE,            OemNormalMode,          1,                             MF_FAST                               | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT ("Normal Operation For Fast flow") },
  {MrcSelfRefreshExit,              MRC_SELF_REFRESH_EXIT,      OemSelfRefreshExit,     1,           MF_WARM | MF_S3                                         | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Perform Self Refresh Exit")},
  {MrcNormalMode,                   MRC_NORMAL_MODE,            OemNormalMode,          1,           MF_WARM | MF_S3                                         | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Normal Operation For Warm / S3 flow")},
  {MrcThermalConfig,                MRC_THERMAL_CONFIG,         OemThermalConfig,       1, MF_COLD | MF_WARM | MF_S3 | MF_FAST                               | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("Configure Thermal values")},
/// @attention: MrcAliasCheck must run before any test modifying the WDB entries to zero for memory scrubbing.
  {MrcAliasCheck,                   MRC_ALIAS_CHECK,            OemAliasCheck,          1, MF_COLD                                                           | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("MRC Memory alias check")},
  {MrcEccClean,                     MRC_ECC_CLEAN_START,        OemHwMemInit,           1, MF_COLD                   | MF_FAST                               | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("MRC Memory Scrubbing")},
  {MrcEnergyPerfGain,               MRC_ENG_PERF_GAIN,          OemEngPerfGain,         1, MF_COLD | MF_WARM | MF_S3 | MF_FAST                               | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("MRC Energy Performance Gain")},
  {MrcSaGvSwitch,                   MRC_SA_GV_SWITCH,           OemSaGvSwitch,          1, MF_COLD | MF_WARM | MF_S3 | MF_FAST | MF_GV_1 | MF_GV_2 | MF_GV_3 | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("MRC SA GV Switch")},
  {MrcTxtAliasCheck,                MRC_TXT_ALIAS_CHECK,        OemTxtAliasCheck,       1, MF_COLD | MF_WARM         | MF_FAST                               | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("TXT Memory alias check")},
  {MrcDone,                         MRC_DONE,                   OemMrcDone,             1, MF_COLD | MF_WARM | MF_S3 | MF_FAST                               | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("MRC done")},
#ifdef BDAT_SUPPORT
  {MrcFillRmtStructure,             MRC_FILL_RMT_STRUCTURE,     OemMrcFillRmt,          1, MF_COLD                                                           | MF_GV_4,                   MRC_ITERATION_MAX, MRC_DEBUG_TEXT("MRC Fill RMT Structure")},
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
  BOOLEAN            Lpddr5;
  BOOLEAN            Lpddr;
  BOOLEAN            DtHalo;

  Status      = mrcSuccess;
  Inputs      = &MrcData->Inputs;
  MrcCall     = Inputs->Call.Func;
  Outputs     = &MrcData->Outputs;
  DdrType     = Outputs->DdrType;
  TrainingEnables   = &Inputs->TrainingEnables;
  TrainingEnables2  = &Inputs->TrainingEnables2;

  Lpddr4 = (DdrType == MRC_DDR_TYPE_LPDDR4);
  Lpddr5 = (DdrType == MRC_DDR_TYPE_LPDDR5);
  Ddr4   = (DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr  = (Lpddr4 || Lpddr5);
  DtHalo = (Inputs->DtHalo);

  switch (OemStatusCommand) {
    case OemMrcSafeMode:
      if (!Inputs->MrcSafeConfig || Inputs->SimicsFlag == 1) {
        Status = mrcFail; // Skip this step
      }
      break;

    case OemSpdProcessingRun:
      break;

    case OemMcTrainingRun:
      break;

    case OemDdrCompCalPre:
      if (Inputs->SimicsFlag == 0) {
        Status = mrcFail; // Don't run on Silicon yet
      }
      break;

    case OemOffsetCorrectionPre:
      Status = mrcFail; // Don't run on Silicon nor Simics yet
      break;


    case OemFllTraining:
      if (Lpddr5) {
        MRC_DEBUG_MSG (&Outputs->Debug, MSG_LEVEL_NOTE, "Disabled due to DDR Type\n");
        Status = mrcFail;
        break;
      }
    case OemMcResetRun:
    case OemPreTraining:
    case OemOptimizeComp:
    case OemPowerSavingMeter:
    case OemDccInit:
      if (Inputs->SimicsFlag == 1) {
        Status = mrcFail; // Don't run on SIMICS.
      }
      break;

    case OemTxDqTcoCompTraining:
      if (Inputs->SimicsFlag == 1) {
        Status = mrcFail; // Don't run on SIMICS.
      } else if (!TrainingEnables2->TXTCO) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemTxDqsTcoCompTraining:
      if (Inputs->SimicsFlag == 1) {
        Status = mrcFail; // Don't run on SIMICS.
      }
      else if (!TrainingEnables2->TXTCO) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemClkTcoCompTraining:
      if (Inputs->SimicsFlag == 1) {
        Status = mrcFail; // Don't run on SIMICS.
      } else if (!TrainingEnables2->CLKTCO) {
        Status = mrcFail; // Skip this step
      }
      break;

    case OemEarlyCommandTraining:
      if (Inputs->SimicsFlag == 0) {
        if ((!TrainingEnables->ECT) || Ddr4) { // Cannot run ECT on DDR4 due to PDA not stable before basic training
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemSenseAmpTraining:
      if (Inputs->SimicsFlag == 0) {
        if (!TrainingEnables->SOT) {
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReadMprTraining:
      if (Inputs->SimicsFlag == 0) {
        if (!TrainingEnables->RDMPRT) {
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReceiveEnable:
      if (Inputs->SimicsFlag == 0) {
        if (!TrainingEnables->RCVET) {
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemWckLeveling:
      if (Inputs->SimicsFlag == 0) {
        if (!TrainingEnables->JWRL) {
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemJedecWriteLeveling:
    case OemWriteLevelingFlyby:
      if ((Inputs->SimicsFlag == 0) && !Lpddr5) {
        if (!TrainingEnables->JWRL) {
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemWriteDqDqs:
      if (Inputs->SimicsFlag == 0) {
        if (!TrainingEnables->WRTC1D) {
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemWriteDqDqsReTraining:
      if (Inputs->SimicsFlag == 0) {
        if (!Lpddr || !Inputs->LpDqsOscEn) { // This is for LPDDR only
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReadVoltage:
      if (Inputs->SimicsFlag == 0) {
        if (!TrainingEnables2->RDVC1D) {
          Status = mrcFail; // Skip this training step
        }
      }  else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemWriteVoltage:
      if (Inputs->SimicsFlag == 0) {
        if (!TrainingEnables->WRVC1D) {
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemEarlyWriteDqDqs2D:
      if (Inputs->SimicsFlag == 0) {
        if (!TrainingEnables->EWRTC2D || !Ddr4) { // This is for DDR4 only
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemEarlyReadDqDqs2D:
      if (Inputs->SimicsFlag == 0) {
        if (!TrainingEnables->ERDTC2D || !Ddr4) { // This is for DDR4 only
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemEarlyRmpr2DPostEct:
      if (!Lpddr) {
        Status = mrcFail;
        break;
      }
      /* FALLTHROUGH*/
      // Fall through if we are LPDDR4 to check input parameters.
    case OemEarlyReadMprDqDqs2D:
      if (Inputs->SimicsFlag == 0) {
        if (!TrainingEnables->ERDMPRTC2D) {
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReadDqDqs:
      if (Inputs->SimicsFlag == 0) {
        if (!TrainingEnables->RDTC1D) {
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemPerBitDeskewCal:
      if (Inputs->SimicsFlag == 0) {
        if (Inputs->RdTPbdDis && Inputs->WrTPbdDis) {
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemDdr4Map:
      if ((!Inputs->DDR4MAP) || !Ddr4) { // This is for DDR4 only
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemDimmODTTraining:
      if (Inputs->SimicsFlag == 0) {
        if ((!TrainingEnables->DIMMODTT) || DtHalo || Lpddr4) {  // @todo: Not ready for DT/HALO and LP4
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemDimmOdtCaTraining:
      if (Inputs->SimicsFlag == 0) {
        if ((!TrainingEnables2->DIMMODTCA) || !Lpddr4) {  // This is for Lpddr4 only
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemDimmRonTraining:
      if (Inputs->SimicsFlag == 0) {
        if ((!TrainingEnables->DIMMRONT) || DtHalo || Lpddr4) {  // @todo: Not ready for DT/HALO and LP4
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemWriteSlewRate:
      if (Inputs->SimicsFlag == 0) {
        if (!TrainingEnables->WRSRT) {
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemWriteDriveUpDn:
      if (Inputs->SimicsFlag == 0) {
        if (!TrainingEnables->WRDSUDT || !Ddr4 || DtHalo) {
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemWriteDriveStrengthEq:
      if (Inputs->SimicsFlag == 0) {
        if (!TrainingEnables->WRDSEQT) {
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReadODTTraining:
      if (Inputs->SimicsFlag == 0) {
        if (!TrainingEnables->RDODTT) {
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReadEQTraining:
      if (Inputs->SimicsFlag == 0) {
        if (!TrainingEnables->RDEQT) {
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemPostTraining:
      if (Inputs->SimicsFlag == 0) {
        if ((!Ddr4) || !TrainingEnables->LCT) { // Cannot switch to 1N/2N without running LCT
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReadAmplifierPower:
      if (Inputs->SimicsFlag == 0) {
        if (!TrainingEnables->RDAPT) {
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemForceOltm:
      if (Inputs->SimicsFlag == 0) {
        if (!Ddr4) {        // This is for DDR4 only
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemWriteDqDqs2D:
      if (Inputs->SimicsFlag == 0) {
        if (!TrainingEnables->WRTC2D) {
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReadDqDqs2D:
      if (Inputs->SimicsFlag == 0) {
        if (!TrainingEnables->RDTC2D) {
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemCmdVoltCentering:
      if (Inputs->SimicsFlag == 0) {
        if (!TrainingEnables->CMDVC) {
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemCmdSlewRate:
      if (Inputs->SimicsFlag == 1) {
        Status = mrcFail; // Don't run on SIMICS.
      }
      else if (!TrainingEnables2->CMDSR) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemCmdDriveStrengthEq:
      if (Inputs->SimicsFlag == 1) {
        Status = mrcFail; // Don't run on SIMICS.
      }
      else if (!TrainingEnables2->CMDDSEQ) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemWriteVoltCentering2D:
      if (Inputs->SimicsFlag == 0) {
        if (!TrainingEnables->WRVC2D) {
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReadVoltCentering2D:
      if (Inputs->SimicsFlag == 0) {
        if (!TrainingEnables->RDVC2D) {
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemLateCommandTraining:
      if (Inputs->SimicsFlag == 0) {
        if (!TrainingEnables->LCT) {
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemRoundTripLatency:
      if (Inputs->SimicsFlag == 0) {
        if ((!TrainingEnables->RTL) || Lpddr4 || Ddr4) {
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemTurnAroundTimes:
      if (Inputs->SimicsFlag == 0) {
        if ((!TrainingEnables->TAT) || Lpddr4) {
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemRcvEnCentering1D:
      if (Inputs->SimicsFlag == 0) {
        if ((!TrainingEnables->RCVENC1D) || Ddr4) {
          Status = mrcFail;  // Skip this step for non-LPDDR
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemRetrainMarginCheck:
      if (Inputs->SimicsFlag == 0) {
        if ((!TrainingEnables->RMC) || (Inputs->PowerTrainingMode != MrcTmPower)) {
          Status = mrcFail; // Skip if disabled or not in Power Training mode
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;


    case OemRmt:
      if (Inputs->SimicsFlag == 0) {
        if (!TrainingEnables->RMT) {
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemRmtPerBit:
      if (Inputs->SimicsFlag == 0) {
        if (!TrainingEnables2->RMTBIT) {
          Status = mrcFail; // Skip this training step
        }
      } else {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemMemTest:
      if ((!TrainingEnables->MEMTST) || (Inputs->SimicsFlag == 1)) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemAliasCheck:
      if ((!TrainingEnables->ALIASCHK) || (Inputs->SimicsFlag == 1)) {
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
      if ((Inputs->SaGv != MrcSaGvEnabled) && (!Lpddr4)) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemDccReplica:
    case OemDccFinal:
      if (Inputs->SimicsFlag == 1) {
        Status = mrcFail; // Don't run on SIMICS.
      } else if (!TrainingEnables2->DCC) {
        Status = mrcFail; // Skip this step
      }
      break;

    case OemVccDllBypassTraining:
      if (Inputs->SimicsFlag == 1) {
        Status = mrcFail; // Don't run on SIMICS.
      }
      else if (!TrainingEnables2->VCCDLLBP) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemCmdDriveUpDn:
      if (Inputs->SimicsFlag == 1) {
        Status = mrcFail; // Don't run on SIMICS.
      }
      else if (!TrainingEnables2->CMDDRUD) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemPanicVttDnLpTraining:
      if (Inputs->SimicsFlag == 1) {
        Status = mrcFail; // Don't run on SIMICS.
      }
      else if (!TrainingEnables2->PVTTDNLP) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemReadVrefDecapTraining:
      if (Inputs->SimicsFlag == 1) {
        Status = mrcFail; // Don't run on SIMICS.
      }
      else if (!TrainingEnables2->RDVREFDC) {
        Status = mrcFail; // Skip this training step
      }
      break;

    case OemVddqTraining:
      if (Inputs->SimicsFlag == 1) {
        Status = mrcFail; // Don't run on SIMICS.
      }
      else if (!TrainingEnables2->VDDQT) {
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
  Initializes the memory controller and DIMMs.

  @param[in, out] MrcData - Include all MRC global data.
  @param[in]      Select  - The post code of the call table entry to execute.

  @retval mrcSuccess if the initialization succeeded, otherwise an error status indicating the failure.
**/
MrcStatus
MrcStartMemoryConfiguration (
  IN OUT MrcParameters *const MrcData,
  IN     MrcPostCode          Select
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
  UINT16                  PrevRdDataValid;
  UINT8                   Run;
  BOOLEAN                 PrevGear2Ever;

  Inputs  = &MrcData->Inputs;
  MrcCall = Inputs->Call.Func;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  SaGv    = Inputs->SaGv;

  BootMode  = Inputs->BootMode;
  DebugLevel = Inputs->DebugLevel;
#ifndef MRC_MINIBIOS_BUILD
  MRC_DEBUG_MSG_OPEN (MrcData, Inputs->DebugLevel, Inputs->DebugStream, Inputs->SerialBuffer.DataN, Inputs->SerialBufferSize);
#endif
  if (Select == 0) {
    MrcVersionGet (MrcData, &Outputs->Version);
    MrcVersionPrint (MrcData, &Outputs->Version);
  }
  MrcStatus = mrcFail;
  post_code = MRC_INITIALIZATION_START;
  Run       = 1;
  TotalTime = 0;
  LowestStackAddr = Debug->LowestStackAddr.DataN;

  if (SaGv == MrcSaGvEnabled) {
    SaGvStart = MrcSaGvPoint1;
    SaGvEnd = MrcSaGvPoint4;
  } else {
    switch (SaGv) {
      case MrcSaGvFixed1:
        SaGvStart = MrcSaGvPoint1;
        break;

      case MrcSaGvFixed2:
        SaGvStart = MrcSaGvPoint2;
        break;

      case MrcSaGvFixed3:
        SaGvStart = MrcSaGvPoint3;
        break;

      case MrcSaGvDisabled:
      case MrcSaGvFixed4:
      default:
        SaGvStart = MrcSaGvPoint4;
        break;
    }
    SaGvEnd = SaGvStart;
  }

  for (SaGvPoint = SaGvStart; SaGvPoint <= SaGvEnd; SaGvPoint++) {
    MrcIntData->SaGvPoint = SaGvPoint;
    Inputs->Iteration = 0;
    PointTime = 0;

    // Reset UPM/PWR limits to initial values; previous SAGV point might have done retrain.
    MrcCall->MrcCopyMem (
      (UINT8 *) RetrainLimits,
      (UINT8 *) InitialLimits,
      sizeof (MrcUpmPwrRetrainLimits) * MRC_NUMBER_UPM_PWR_RETRAIN_MARGINS
      );

    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "SAGV: %sabled, running at point %u\n",
      (SaGv == MrcSaGvEnabled) ? "En" : "Dis",
      SaGvPoint
      );

    for (RetrainLoop = 0; RetrainLoop <= 1; RetrainLoop++) {
      MrcVersionGet (MrcData, &Outputs->Version);
      MrcIntData->UpmPwrRetrainLimits.Pointer = RetrainLimits;
      for (index = 0; Run && (index < ARRAY_COUNT (MrcCallTable)); index++, post_code++) {
        Task = &MrcCallTable[index];
        // Decide if we need to execute the selected MRC task.
        if ((NULL == Task->mrc_task) || (Inputs->Iteration >= Task->iteration)) {
          continue;
        }
        if   (((BootMode == bmS3)   && (Task->policy_flag & MF_S3))
          ||  ((BootMode == bmFast) && (Task->policy_flag & MF_FAST))
          ||  ((BootMode == bmWarm) && (Task->policy_flag & MF_WARM))
          ||  ((BootMode == bmCold) && (Task->policy_flag & MF_COLD))
          ||  ((Select != 0))) {
          if  ((Select == 0) || (Select == Task->post_code_ovr)) {
            if (((MrcIntData->SaGvPoint == MrcSaGvPoint1)  && (Task->policy_flag & MF_GV_1)) ||
                ((MrcIntData->SaGvPoint == MrcSaGvPoint2)  && (Task->policy_flag & MF_GV_2)) ||
                ((MrcIntData->SaGvPoint == MrcSaGvPoint3)  && (Task->policy_flag & MF_GV_3)) ||
                ((MrcIntData->SaGvPoint == MrcSaGvPoint4)  && (Task->policy_flag & MF_GV_4)) ||
                (SaGv != MrcSaGvEnabled)) {
              if (Task->oem_cmd < OemNumOfCommands) {
                CpStatus = MrcInternalCheckPoint (MrcData, Task->oem_cmd, NULL);
                if (mrcSuccess != CpStatus) {
                  continue;
                }
              }
              // Output post code to post code I/O port.
              PostCodeOut = (Task->post_code_ovr == POST_CODE_NO_OVR) ? post_code : Task->post_code_ovr;
              if ((Select == 0) || ((Select > 0) && (Select == PostCodeOut))) {
                MrcCall->MrcDebugHook (MrcData, PostCodeOut);
              }
              // Output debug string to serial output and execute the MRC task.
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nMRC task -- %s -- Started.\n", Task->String);
              if (!Task->DebugPrint) {
                DebugLevel = Debug->Level;
                Debug->Level = MSG_LEVEL_NEVER;
              }
              start_time  = MrcCall->MrcGetCpuTime ();
              MrcStatus   = Task->mrc_task (MrcData);
              finish_time = MrcCall->MrcGetCpuTime ();
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
              if (mrcSuccess != MrcStatus) {
                Run = 0;  // Stop task execution on failure.
              }

              ElapsedTime = (UINT32) (finish_time - start_time);
              TotalTime += ElapsedTime;
              PointTime += ElapsedTime;
              // <MrcTimer Task="Print input parameters" msec="2"/>
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_TIME, "<MrcTimer Task=\"%s\" msec=\"%u\"/>\n", Task->String, ElapsedTime);

              if (Inputs->RmtPerTask && (Task->policy_flag & MF_RMT)) {  // Run RMT after this task
                MrcRankMarginTool (MrcData);
              }
              if (Inputs->TrainTrace && (Task->policy_flag & MF_TST)) {
                // <MrcTrainedStateTrace> ... <MrcTrainedStateTrace/>
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "<MrcTrainedStateTrace>\n");
                MrcTrainedStateTrace (MrcData);
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "<MrcTrainedStateTrace/>\n");
              }
            }
          } // Select match
        } // if boot mode match
      } // for index
      // Check if MRC failed due to RetrainMarginCheck
      if (MrcStatus == mrcRetrain) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\nRerunning training with higher UPM/PWR limits!\n");
        PrevRdDataValid = MrcIntData->MaxRdDataValid;
        PrevGear2Ever = Outputs->Gear2Ever;
        MrcCall->MrcSetMem ((UINT8 *) Outputs, sizeof (MrcOutput), 0);
        MrcCall->MrcSetMem ((UINT8 *) MrcIntData, sizeof (MrcIntOutput), 0);
        Outputs->Size              = sizeof (MrcOutput);
        MrcIntData->Size           = sizeof (MrcIntOutput);
        MrcIntData->SaGvPoint      = SaGvPoint;
        Outputs->UpmPwrRetrainFlag = TRUE;
        MrcIntData->MaxRdDataValid = PrevRdDataValid;
        Outputs->Gear2Ever         = PrevGear2Ever;
        MRC_DEBUG_MSG_OPEN (MrcData, Inputs->DebugLevel, Inputs->DebugStream, Inputs->SerialBuffer.DataN, Inputs->SerialBufferSize);
        Inputs->Iteration++;
        Run = 1;
      } else {
        break;    // No need to retrain
      }
    } // Retrain loop

    if ((SaGv == MrcSaGvEnabled) && (SaGvPoint != MrcSaGvPoint4)) {
      // Prepare for the next MRC iteration
      PrevRdDataValid = MrcIntData->MaxRdDataValid;
      PrevGear2Ever = Outputs->Gear2Ever;
      MrcCall->MrcSetMem ((UINT8 *) Outputs, sizeof (MrcOutput), 0);
      MrcCall->MrcSetMem ((UINT8 *) MrcIntData, sizeof (MrcIntOutput), 0);
      MrcIntData->Size = sizeof (MrcOutput);
      Outputs->Size = sizeof (MrcOutput);
      MRC_DEBUG_MSG_OPEN (MrcData, Inputs->DebugLevel, Inputs->DebugStream, Inputs->SerialBuffer.DataN, Inputs->SerialBufferSize);
      MrcIntData->MaxRdDataValid = PrevRdDataValid;
      Outputs->Gear2Ever = PrevGear2Ever;
    }

    if (SaGv == MrcSaGvEnabled) {
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_TIME,
        "MRC timer: Total time for SAGV point %u = %u msec.\n",
        SaGvPoint,
        PointTime
        );
    }
  } // for GvPoint

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_TIME, "MRC timer: Total time to execute tasks = %u msec.\n", TotalTime);

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
