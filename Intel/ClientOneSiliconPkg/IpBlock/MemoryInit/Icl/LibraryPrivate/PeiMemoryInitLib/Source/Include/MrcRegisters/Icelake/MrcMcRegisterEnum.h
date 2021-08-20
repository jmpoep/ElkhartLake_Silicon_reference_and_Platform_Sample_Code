/** @file
  This file was automatically generated. Modify at your own risk.
  Note that no error checking is done in these functions so ensure that the correct values are passed.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2017 Intel Corporation.

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
#ifndef __MrcMcRegisterEnum_h__
#define __MrcMcRegisterEnum_h__

#pragma pack(push, 1)
#include "McAddress.h"

//
// Note that the following typedef enums are in alphabetical order.
//
typedef enum {
  MrcHalActSelectDisable,
  MrcHalActSelectDriveOnMa,
  MrcHalActSelectDriveOnBa,
  MrcHalActSelectMax,
  MrcHalActSelectIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_ACT_SELECT_CONTROL;

typedef enum {
  MrcHalAddressInvertDisable,
  MrcHalAddressInvertEnable,
  MrcHalAddressInvertMax,
  MrcHalAddressInvertIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_ADDRESS_INVERT_CONTROL;

typedef enum {
  MrcHalAddressSelectRank,
  MrcHalAddressSelectBank,
  MrcHalAddressSelectRow,
  MrcHalAddressSelectColumn,
  MrcHalAddressSelectMax,
  MrcHalAddressSelectIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_ADDRESS_SELECT;

typedef enum {
  MrcHalAddressUpdateRateModeCachelines,
  MrcHalAddressUpdateRateModeLoopcount,
  MrcHalAddressUpdateRateModeMax,
  MrcHalAddressUpdateRateModeIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_ADDRESS_UPDATE_RATE_CONTROL;

typedef enum {
  MrcHalAddressWrapCarryDisable,
  MrcHalAddressWrapCarryEnable,
  MrcHalAddressWrapCarryMax,
  MrcHalAddressWrapCarryIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_ADDRESS_WRAP_CARRY;

typedef enum {
  MrcHalAddressWrapTriggerDisable,
  MrcHalAddressWrapTriggerEnable,
  MrcHalAddressWrapTriggerMax,
  MrcHalAddressWrapTriggerIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_ADDRESS_WRAP_TRIGGER;

typedef enum {
  MrcHalBankMaskBankNone,
  MrcHalBankMaskBank0,
  MrcHalBankMaskBank1,
  MrcHalBankMaskBank2 = 4,
  MrcHalBankMaskBank3 = 8,
  MrcHalBankMaskBank4 = 0x10,
  MrcHalBankMaskBank5 = 0x20,
  MrcHalBankMaskBank6 = 0x40,
  MrcHalBankMaskBank7 = 0x80,
  MrcHalBankMaskBank8 = 0x100,
  MrcHalBankMaskBank9 = 0x200,
  MrcHalBankMaskBank10 = 0x400,
  MrcHalBankMaskBank11 = 0x800,
  MrcHalBankMaskBank12 = 0x1000,
  MrcHalBankMaskBank13 = 0x2000,
  MrcHalBankMaskBank14 = 0x4000,
  MrcHalBankMaskBank15 = 0x8000,
  MrcHalBankMaskMax,
  MrcHalBankMaskIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_BANK_MASK_CONTROL;

typedef enum {
  MrcHalCachelineCounterCommands,
  MrcHalCachelineCounterReadData,
  MrcHalCachelineCounterMax,
  MrcHalCachelineCounterIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_CACHELINE_COUNTER_CONTROL;

typedef enum {
  MrcHalCadbAlwaysOnDisable,
  MrcHalCadbAlwaysOnEnable,
  MrcHalCadbAlwaysOnMax,
  MrcHalCadbAlwaysOnIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_CADB_ALWAYS_ON_CONTROL;

typedef enum {
  MrcHalCadbOnDeselectDisable,
  MrcHalCadbOnDeselectEnable,
  MrcHalCadbOnDeselectMax,
  MrcHalCadbOnDeselectIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_CADB_ON_DESELECT_CONTROL;

typedef enum {
  MrcHalCadbUniseqIndex0,
  MrcHalCadbUniseqIndex1,
  MrcHalCadbUniseqIndex2,
  MrcHalCadbUniseqIndexMax,
  MrcHalCadbUniseqIndexIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_CADB_UNISEQ_INDEX_TYPE;

typedef enum {
  MrcHalCasSelectDisable,
  MrcHalCasSelectDriveOnMa,
  MrcHalCasSelectDriveOnBa,
  MrcHalCasSelectMax,
  MrcHalCasSelectIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_CAS_SELECT_CONTROL;

typedef enum {
  MrcHalClearErrorDisable,
  MrcHalClearErrorEnable,
  MrcHalClearErrorMax,
  MrcHalClearErrorIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_CLEAR_ERROR_CONTROL;

typedef enum {
  MrcHalClockGateAbDisable,
  MrcHalClockGateAbCycles2,
  MrcHalClockGateAbCycles3,
  MrcHalClockGateAbCycles4,
  MrcHalClockGateAbMax,
  MrcHalClockGateAbIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_CLOCK_GATE_AB_CONTROL;

typedef enum {
  MrcHalClockGateCDisable,
  MrcHalClockGateCCycles2,
  MrcHalClockGateCCycles4,
  MrcHalClockGateCCycles8,
  MrcHalClockGateCMax,
  MrcHalClockGateCIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_CLOCK_GATE_C_CONTROL;

typedef enum {
  MrcHalCmdDeselectDisable,
  MrcHalCmdDeselectAfterWrCmd,
  MrcHalCmdDeselectAfterRdCmd,
  MrcHalCmdDeselectAfterActCmd = 4,
  MrcHalCmdDeselectAfterPreCmd = 8,
  MrcHalCmdDeselectMax,
  MrcHalCmdDeselectIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_CMD_DESELECT_CONTROL;

typedef enum {
  MrcHalDbiAbControlDisable,
  MrcHalDbiAbControlEnable,
  MrcHalDbiAbControlMax,
  MrcHalDbiAbControlIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_DBI_AB_CONTROL;

typedef enum {
  MrcHalDcPolarityControlLogicLow,
  MrcHalDcPolarityControlLogicHigh,
  MrcHalDcPolarityControlMax,
  MrcHalDcPolarityControlIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_DC_POLARITY_CONTROL;

typedef enum {
  MrcHalDllWeakLockDisable,
  MrcHalDllWeakLockEnable,
  MrcHalDllWeakLockMax,
  MrcHalDllWeakLockIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_DLL_WEAK_LOCK;

typedef enum {
  MrcHalDummyReadDisable,
  MrcHalDummyReadEnable,
  MrcHalDummyReadMax,
  MrcHalDummyReadIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_DUMMY_READ_CONTROL;

typedef enum {
  MrcHalEccReplaceByteFalse,
  MrcHalEccReplaceByteTrue,
  MrcHalEccReplaceByteMax,
  MrcHalEccReplaceByteIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_ECC_REPLACE_BYTE;

typedef enum {
  MrcHalEccDataSourceSelectByteGroup0,
  MrcHalEccDataSourceSelectByteGroup7,
  MrcHalEccDataSourceSelectMax,
  MrcHalEccDataSourceSelectIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_ECC_SOURCE_SELECT;

typedef enum {
  MrcHalEnableSweepFreq0,
  MrcHalEnableSweepFreq1,
  MrcHalEnableSweepFreqMax,
  MrcHalEnableSweepFreqIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_ENABLE_SWEEP_FREQ;

typedef enum {
  MrcHalErrorCounterControlNone,
  MrcHalErrorCounterControlLane,
  MrcHalErrorCounterControlByteGroup,
  MrcHalErrorCounterControlChunk,
  MrcHalErrorCounterControlMax,
  MrcHalErrorCounterControlIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_ERROR_COUNTER_CONTROL;

typedef enum {
  MrcHalGlobalControlDisable,
  MrcHalGlobalControlEnable,
  MrcHalGlobalControlMax,
  MrcHalGlobalControlIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_GLOBAL_CONTROL;

typedef enum {
  MrcHalIncrementScaleExponential,
  MrcHalIncrementScaleLinear,
  MrcHalIncrementScaleMax,
  MrcHalIncrementScaleIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_INCRMENT_SCALE_CONTROL;

typedef enum {
  MrcHalInitializationModeIdleOnMcReset,
  MrcHalInitializationModeReutTesting,
  MrcHalInitializationModeMrs,
  MrcHalInitializationModeNormalOperation,
  MrcHalInitializationModeMax,
  MrcHalInitializationModeIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_INITIALIZATION_MODE;

typedef enum {
  MrcHalInvOrDcControlInvert,
  MrcHalInvOrDcControlUseDcPolarityControl,
  MrcHalInvOrDcControlMax,
  MrcHalInvOrDcControlMaxIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_INV_OR_DC_CONTROL;

typedef enum {
  MrcHalLDataSelectLogic0,
  MrcHalLDataSelectLogic1,
  MrcHalLDataSelectMax,
  MrcHalLDataSelectIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_L_DATA_SELECT;

typedef enum {
  MrcHalLaneDeselectDisable,
  MrcHalLaneDeselectDriveOnMa,
  MrcHalLaneDeselectDriveOnBa,
  MrcHalLaneDeselectDriveOnCmd = 4,
  MrcHalLaneDeselectDriveOnCs = 8,
  MrcHalLaneDeselectMax,
  MrcHalLaneDeselectIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_LANE_DESELECT_CONTROL;

typedef enum {
  MrcHalLfsrChainingFalse,
  MrcHalLfsrChainingTrue,
  MrcHalLfsrChainingMax,
  MrcHalLfsrChainingIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_LFSR_CHAINING_CONTROL;

typedef enum {
  MrcHalLfsrType3,
  MrcHalLfsrType4,
  MrcHalLfsrType6,
  MrcHalLfsrType8,
  MrcHalLfsrType10,
  MrcHalLfsrType12,
  MrcHalLfsrType16,
  MrcHalLfsrType24,
  MrcHalLfsrTypeMax,
  MrcHalLfsrTypeIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_LFSR_TYPE;

typedef enum {
  MrcHalMprTrainDdrDisable,
  MrcHalMprTrainDdrEnable,
  MrcHalMprTrainDdrMax,
  MrcHalMprTrainDdrIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_MPR_TRAIN_CONTROL;

typedef enum {
  MrcHalMuxControlLmnCounter,
  MrcHalMuxControl24BitBuffer,
  MrcHalMuxControlLfsr,
  MrcHalMuxControlMax,
  MrcHalMuxControlIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_MUX_CONTROL;

typedef enum {
  MrcHalOpportunisticRefreshDisable,
  MrcHalOpportunisticRefreshEnable,
  MrcHalOpportunisticRefreshMax,
  MrcHalOpportunisticRefreshIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_OPPORTUNISTIC_REFRESH_CONTROL;

typedef enum {
  MrcHalPanicRefreshOnlyDisable,
  MrcHalPanicRefreshOnlyEnable,
  MrcHalPanicRefreshOnlyMax,
  MrcHalPanicRefreshOnlyIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_PANIC_REFRESH_CONTROL;

typedef enum {
  MrcHalParityInvertDisable,
  MrcHalParityInvertEnable,
  MrcHalParityInvertMax,
  MrcHalParityInvertIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_PARITY_INVERT_CONTROL;

typedef enum {
  MrcHalSelectPatternBufferNone,
  MrcHalSelectPatternBufferRead,
  MrcHalSelectPatternBufferWrite,
  MrcHalSelectPatternBufferBoth,
  MrcHalSelectPatternBufferMax,
  MrcHalSelectPatternBufferIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_PATTERN_BUFFER_SELECT;

typedef enum {
  MrcHalPreSelectDisable,
  MrcHalPreSelectDriveOnMa,
  MrcHalPreSelectDriveOnBa,
  MrcHalPreSelectMax,
  MrcHalPreSelectIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_PRE_SELECT_CONTROL;

typedef enum {
  MrcHalRankMaskRankNone,
  MrcHalRankMaskRank0,
  MrcHalRankMaskRank1,
  MrcHalRankMaskRank2 = 0x4,
  MrcHalRankMaskRank3 = 0x8,
  MrcHalRankMaskMax,
  MrcHalRankMaskIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_RANK_MASK_CONTROL;

typedef enum {
  MrcHalReloadSeedDisable,
  MrcHalReloadSeedOnWrCmd,
  MrcHalReloadSeedOnRdCmd,
  MrcHalReloadSeedOnActCmd = 4,
  MrcHalReloadSeedOnPreCmd = 8,
  MrcHalReloadSeedOnMax,
  MrcHalReloadSeedOnIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_RELOAD_SEED_CONTROL;

typedef enum {
  MrcHalSaveSeedDisable,
  MrcHalSaveSeedOnWrCmd,
  MrcHalSaveSeedOnRdCmd,
  MrcHalSaveSeedOnActCmd = 4,
  MrcHalSaveSeedOnPreCmd = 8,
  MrcHalSaveSeedOnMax,
  MrcHalSaveSeedOnIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_SAVE_SEED_CONTROL;

typedef enum {
  MrcHalScramblerControlDisable,
  MrcHalScramblerControlEnable,
  MrcHalScramblerControlMax,
  MrcHalScramblerControlIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_SCRAMBLER_CONTROL;

typedef enum {
  MrcHalSeedRateModeExponential,
  MrcHalSeedRateModeLinear,
  MrcHalSeedRateModeMax,
  MrcHalSeedRateModeIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_SEED_RATE_MODE;

typedef enum {
  MrcHalSelectiveErrorEnableCachelineNone,
  MrcHalSelectiveErrorEnableCacheline0,
  MrcHalSelectiveErrorEnableCacheline1,
  MrcHalSelectiveErrorEnableCacheline2 = 0x04,
  MrcHalSelectiveErrorEnableCacheline3 = 0x08,
  MrcHalSelectiveErrorEnableCacheline4 = 0x10,
  MrcHalSelectiveErrorEnableCacheline5 = 0x20,
  MrcHalSelectiveErrorEnableCacheline6 = 0x40,
  MrcHalSelectiveErrorEnableCacheline7 = 0x80,
  MrcHalSelectiveErrorEnableCachelineMax,
  MrcHalSelectiveErrorEnableCachelineIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_SELECTIVE_ERROR_ENABLE_CACHELINE;

typedef enum {
  MrcHalSelectiveErrorEnableChunkNone,
  MrcHalSelectiveErrorEnableChunk0,
  MrcHalSelectiveErrorEnableChunk1,
  MrcHalSelectiveErrorEnableChunk2 = 0x04,
  MrcHalSelectiveErrorEnableChunk3 = 0x08,
  MrcHalSelectiveErrorEnableChunk4 = 0x10,
  MrcHalSelectiveErrorEnableChunk5 = 0x20,
  MrcHalSelectiveErrorEnableChunk6 = 0x40,
  MrcHalSelectiveErrorEnableChunk7 = 0x80,
  MrcHalSelectiveErrorEnableMax,
  MrcHalSelectiveErrorEnableIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_SELECTIVE_ERROR_ENABLE_CHUNK;

typedef enum {
  MrcHalSelfRefreshDisable,
  MrcHalSelfRefreshEnable,
  MrcHalSelfRefreshMax,
  MrcHalSelfRefreshIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_SELF_REFRESH_CONTROL;

typedef enum {
  MrcHalSequenceWrapDisable,
  MrcHalSequenceWrapEnable,
  MrcHalSequenceWrapMax,
  MrcHalSequenceWrapIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_SEQUENCE_WRAP_CONTROL;

typedef enum {
  MrcHalStartTestSyncDisable,
  MrcHalStartTestSyncEnable,
  MrcHalStartTestSyncMax,
  MrcHalStartTestSyncIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_START_TEST_SYNC;

typedef enum {
  MrcHalStopOnCaAlertDisable,
  MrcHalStopOnCaAlertEnable,
  MrcHalStopOnCaAlertMax,
  MrcHalStopOnCaAlertIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_STOP_ON_CA_ALERT;

typedef enum {
  MrcHalStopOnErrorDisable,
  MrcHalStopOnNthLaneError,
  MrcHalStopOnAllByteGroupsError,
  MrcHalStopOnAllLaneError,
  MrcHalStopOnErrorMax,
  MrcHalStopOnErrorIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_STOP_ON_ERROR_CONTROL;

typedef enum {
  MrcHalSubSequencePointer0,
  MrcHalSubSequencePointer1,
  MrcHalSubSequencePointer2,
  MrcHalSubSequencePointer3,
  MrcHalSubSequencePointer4,
  MrcHalSubSequencePointer5,
  MrcHalSubSequencePointer6,
  MrcHalSubSequencePointer7,
  MrcHalSubSequencePointerMax,
  MrcHalSubSequencePointerIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_SUBSEQUENCE_POINTER_VALUE;

typedef enum {
  MrcHalTestControlNull,
  MrcHalTestControlStop,
  MrcHalTestControlStart,
  MrcHalTestControlMax,
  MrcHalTestControlIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_TEST_CONTROL;

typedef enum {
  MrcHalWdbUniseqIndex0,
  MrcHalWdbUniseqIndex1,
  MrcHalWdbUniseqIndex2,
  MrcHalWdbUniseqIndexMax,
  MrcHalWdbUniseqIndexIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_WDB_UNISEQ_INDEX_TYPE;

typedef enum {
  MrcHalWritePointerDisable,
  MrcHalWritePointerEnable,
  MrcHalWritePointerMax,
  MrcHalWritePointerIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_WRITE_POINTER_CONTROL;

typedef enum {
  MrcHalAlwaysDoZqDisable,
  MrcHalAlwaysDoZqEnable,
  MrcHalAlwaysDoZqMax,
  MrcHalAlwaysDoZqIgnoreArg = MRC_IGNORE_ARG
} MRC_HAL_ENUM_ZQ_OPERATION_CONTROL;
#pragma pack(pop)
#endif
