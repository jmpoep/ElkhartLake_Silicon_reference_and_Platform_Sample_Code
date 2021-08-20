/** @file
  Implementation of the memory controller hardware abstraction layer.

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
//
// Include files
//
#include "McAddress.h"
#include "MrcInterface.h"
#include "MrcCommon.h"
#include "MrcReadReceiveEnable.h"
#include "MrcDdrIoOffsets.h"
#include "MrcMcOffsets.h"
#include "MrcGears.h"
///
/// Defines
///
#define MAX_CHUNK_SIZE (8)

// MrcCheckComplexOrSideEffect() defines
#define MRC_IS_COMPLEX (TRUE)
#define MRC_IS_SIDE_EFFECT (FALSE)

/// Hash arrays
#define ICL_ROUNDTRIP_DELAY_MAX (8)

#ifdef MRC_DEBUG_PRINT
///
/// DDR IO Debug Strings
///
const CHAR8* GsmGtDebugStrings[GsmGtMax + 4] = {
  "RecEnDelay",
  "RxDqsDelay",
  "RxDqDelay",
  "RxDqsPDelay",
  "RxDqsNDelay",
  "RxVref",
  "RxEq",
  "RxDqBitDelay",
  "RxVoc",
  "RxOdt",
  "RxOdtUp",
  "RxOdtDn",
  "DramDrvStr",
  "McOdtDelay",
  "McOdtDuration",
  "SenseAmpDelay",
  "SenseAmpDuration",
  "RoundTripDelay",
  "RxDqsBitDelay",
  "RxDqDqsDelay",
  "WrLvlDelay",
  "TxDqsDelay",
  "TxDqDelay",
  "TxVref",
  "TxEq",
  "TxDqBitDelay",
  "TxRon",
  "TxRonUp",
  "TxRonDn",
  "TxSlewRate",
  "TxImode",
  "WrOdt",
  "NomOdt",
  "ParkOdt",
  "TxTco",
  "TxXtalk",
  "RxCtleR",
  "RxCtleC",
  "RxDqsPBitDelay",
  "RxDqsNBitDelay",
  "CmdAll",
  "CmdGrp0",
  "CmdGrp1",
  "CmdGrp2",
  "CtlAll",
  "CtlGrp0",
  "CtlGrp1",
  "CtlGrp2",
  "CtlGrp3",
  "CtlGrp4",
  "CtlGrp5",
  "CmdCtlAll",
  "CkAll",
  "CmdVref",
  "AlertVref",
  "CmdRon",
  "CmdGrpPi",
  "CtlGrpPi",
  "ClkGrpPi",
  "TxCycleDelay",
  "EridDelay",
  "EridVref",
  "ErrorVref",
  "ReqVref",
  "RecEnOffset",
  "RxDqsOffset",
  "RxVrefOffset",
  "TxDqsOffset",
  "TxDqOffset",
  "CkeGrpPi",
  "RxBiasIComp",
  "RxBiasRComp",
  "RxBiasRCompMsb",
  "RxBiasRCompLsb",
  "RxDqsAmpOffset",
  "SdllPiCb",
  "D0PiCb",
  "SdllBwCtrl",
  "D0BwCtrl",
  "RxDqAmpOffset",
  "RxCben",
  "CompRxCben",
  "CBEnAmp1",
  "TxRankMuxDelay",
  "TxDqsRankMuxDelay",
  "RxRankMuxDelay",
  "RxFlybyDelay",
  "RxIoTclDelay",
  "RoundTripIoComp",
  "RxFifoRdEnFlybyDelay",
  "RxFifoRdEnTclDelay",
  "RxDqDataValidDclkDelay",
  "RxDqDataValidQclkDelay",
  "TxDqFifoWrEnTcwlDelay",
  "TxDqFifoRdEnTcwlDelay",
  "TxDqFifoRdEnFlybyDelay",
  "CmdRCompDrvDownOffset",
  "CmdRCompDrvUpOffset",
  "CmdSCompOffset",
  "ClkRCompDrvDownOffset",
  "ClkRCompDrvUpOffset",
  "ClkSCompOffset",
  "CtlRCompDrvDownOffset",
  "CtlRCompDrvUpOffset",
  "CtlSCompOffset",
  "CkeRCompDrvDownOffset",
  "CkeRCompDrvUpOffset",
  "CkeSCompOffset",
  "ClkCompOnTheFlyUpdtEn",
  "CompOffsetAll",
  "CmdSlewRate",
  "ClkSlewRate",
  "ClkRon",
  "CtlSlewRate",
  "CtlRon",
  "DqScompPC",
  "CmdScompPC",
  "CtlScompPC",
  "ClkScompPC",
  "DqRcompStatLegs",
  "SCompCodeDq",
  "SCompCodeCmd",
  "SCompCodeCtl",
  "SCompCodeClk",
  "WrDSCodeUpCmd",
  "WrDSCodeUpCtl",
  "WrDSCodeUpClk",
  "WrDSCodeDnCmd",
  "WrDSCodeDnCtl",
  "WrDSCodeDnClk",
  "TcoCompCodeCmd",
  "TcoCompCodeCtl",
  "TcoCompCodeClk",
  "TxTcoDqsN",
  "TxTcoDqsP",
  "TxTcoByPass",
  "DqOdtVref",
  "DqDrvVref",
  "CmdDrvVref",
  "CmdTxEq",
  "CtlDrvVref",
  "ClkDrvVref",
  "CompRcompOdtUp",
  "CompRcompOdtDn",
  "McDqsOdtDelay",
  "McDqsOdtDuration",
  "DqDfeEnable",
  "DqDfeDelayMode",
  "DqDfeCoeff",
  "DqDfeDelay",
  "EndOfPhyMarker",
  "GsmIocIoReset",
  "GsmIocWlWakeCyc",
  "GsmIocWlSleepCyc",
  "GsmIocForceCmpUpdt",
  "GsmIocWlLatency",
  "GsmIocLpRcvenCtrl",
  "GsmIocNoDqInterleave",
  "GsmIocScramLpMode",
  "GsmIocScramDdr4Mode",
  "GsmIocDdrCentric",
  "GsmIocScramGear1",
  "GsmIocDisClkGate",
  "GsmIocDllWlEn",
  "GsmIocDisDataIdlClkGate",
  "GsmIoc4ChMode",
  "GsmIocScramLp4Mode",
  "GsmIocChNotPop",
  "GsmIocDisIosfSbClkGate",
  "GsmIocEccEn",
  "GsmIocDataOdtStaticDis",
  "GsmIocCompOdtStaticDis",
  "GsmIocOdtSampExtEn",
  "GsmIocDqsOdtSampExtEn",
  "GsmIocLpEarlyRLeak",
  "GsmIocDllMask",
  "GsmIocStrongWeakLeaker",
  "GsmIocStrongWeakLeakerMsb",
  "GsmIocRcvenFourCycleFill",
  "GsmIocEnRcvenPreZeroFill",
  "GsmIocLpLongOdtEn",
  "GsmIocDataVddqOdtEn",
  "GsmIocDataVttOdtEn",
  "GsmIocCompVddqOdtEn",
  "GsmIocCompVttOdtEn",
  "GsmIocCmdDrvVref200ohm",
  "GsmIocVttPanicCompUpMult",
  "GsmIocVttPanicCompDnMult",
  "GsmIocRxDeskewDis",
  "GsmIocTxDeskewDis",
  "GsmIocVrefPwrDnEn",
  "GsmIocRxVrefMFC",
  "GsmIocRxStaggerCtl",
  "GsmIocRxDeskewCal",
  "GsmIocTxDeskewCal",
  "GsmIocVssOdtEn",
  "GsmIocGlobalClkEn",
  "GsmIocRxTypeSelect",
  "GsmIocLeakerComp",
  "GsmIocLeakerWithTxAnalogEn",
  "GsmIocStrong2WeakOnDqsOdt",
  "GsmIocForceDqsOnQuickOdtOff",
  "GsmIocLongWrPreambleLp4",
  "GsmIocRxBiasSel",
  "GsmIocForceRxAmpOn",
  "GsmIocForceBiasOn",
  "GsmIocTxOn",
  "GsmIocSenseAmpMode",
  "GsmIocReadLevelMode",
  "GsmIocXoverMinDelayCtl",
  "GsmIocWriteLevelMode",
  "GsmIocReadDqDqsMode",
  "GsmIocDataCtlLpMode",
  "GsmIocDataCtlLp4Mode",
  "GsmIocDataCtlDdr4Mode",
  "GsmIocRxClkStg",
  "GsmIocRxClkStgNumMsb",
  "GsmIocForceOdtOn",
  "GsmIocRxPiPwrDnDis",
  "GsmIocTxPiPwrDnDis",
  "GsmIocTxDisable",
  "GsmIocTxVrefConverge",
  "GsmIocCmdVrefConverge",
  "GsmIocCompClkOn",
  "GsmIocConstZTxEqEn",
  "GsmIocCompVccddqLo",
  "GsmIocDisableQuickComp",
  "GsmIocSinStep",
  "GsmIocSinStepAdv",
  "GsmIocSdllSegmentDisable",
  "GsmIocDllWeakLock",
  "GsmIocTxEqDis",
  "GsmIocDqSlewDlyByPass",
  "GsmIocWlLongDelEn",
  "GsmIocDqOdtUpDnOff",
  "GsmIocFixOdtD",
  "GsmIocPanicDrvUpVref",
  "GsmIocOdtOverride",
  "GsmIocOdtOn",
  "GsmIocMprTrainDdrOn",
  "GsmIocCkeOverride",
  "GsmIocCkeOn",
  "GsmIocRptChRepClkOn",
  "GsmIocCmdAnlgEnGraceCnt",
  "GsmIocTxAnlgEnGraceCnt",
  "GsmIocTxDqFifoRdEnPerRankDelDis",
  "GsmIocLowSupEnDqDqs",
  "GsmIocInternalClocksOn",
  "GsmIocLp4DqsMaskPulseCnt",
  "GsmIocLp4ForceDqsPOn",
  "GsmIocLp4ForceDqsNOn",
  "GsmIocLp4ForceDqsPOnWithLeaker",
  "GsmIocLp4ForceDqsNOnWithLeaker",
  "GsmIocLp4DqsPulseCnt",
  "GsmIocLp4DqsPulseEn",
  "GsmIocLp4DqOverrideData",
  "GsmIocLp4DqOverrideEn",
  "GsmIocRankOverrideEn",
  "GsmIocRankOverrideVal",
  "GsmIocDataCtlGear1",
  "GsmIocDccTrainingMode",
  "GsmIocDccTrainingDone",
  "GsmIocDccDrain",
  "GsmIocDccActiveClks",
  "GsmIocDccActiveBytes",
  "GsmIocDccDcoCompEn",
  "GsmIocDccPeriodicDis",
  "GsmIocDccDcoLfsrDis",
  "GsmIocDccClkTrainVal",
  "GsmIocDccDataTrainDqsVal",
  "GsmIocDccDqsReplica",
  "GsmIocDccAipCb",
  "GsmIocDccAipCbDqs",
  "EndOfIocMarker",
  "GsmMctRP",
  "GsmMctRPabExt",
  "GsmMctRAS",
  "GsmMctRDPRE",
  "GsmMctPPD",
  "GsmMctWRPRE",
  "GsmMctFAW",
  "GsmMctRRDsg",
  "GsmMctRRDdg",
  "GsmMctLpDeratingExt",
  "GsmMctRDRDsg",
  "GsmMctRDRDdg",
  "GsmMctRDRDdr",
  "GsmMctRDRDdd",
  "GsmMctRDWRsg",
  "GsmMctRDWRdg",
  "GsmMctRDWRdr",
  "GsmMctRDWRdd",
  "GsmMctWRRDsg",
  "GsmMctWRRDdg",
  "GsmMctWRRDdr",
  "GsmMctWRRDdd",
  "GsmMctWRWRsg",
  "GsmMctWRWRdg",
  "GsmMctWRWRdr",
  "GsmMctWRWRdd",
  "GsmMctCKE",
  "GsmMctXP",
  "GsmMctXPDLL",
  "GsmMctPRPDEN",
  "GsmMctRDPDEN",
  "GsmMctWRPDEN",
  "GsmMctOdtRdDuration",
  "GsmMctOdtRdDelay",
  "GsmMctOdtWrDuration",
  "GsmMctOdtWrDelay",
  "GsmMctWrEarlyOdt",
  "GsmMctCL",
  "GsmMctCWL",
  "GsmMctAONPD",
  "GsmMctCWLAdd",
  "GsmMctCWLDec",
  "GsmMctXSDLL",
  "GsmMctXSR",
  "GsmMctZQOPER",
  "GsmMctMOD",
  "GsmMctSrIdle",
  "GsmMctREFI",
  "GsmMctRFC",
  "GsmMctOrefRi",
  "GsmMctRefreshHpWm",
  "GsmMctRefreshPanicWm",
  "GsmMctREFIx9",
  "GsmMctZQCSPeriod",
  "GsmMctZQCS",
  "GsmMctZQCAL",
  "GsmMctCPDED",
  "GsmMctCAL",
  "GsmMctCKCKEH",
  "GsmMctCSCKEH",
  "GsmMctRCDwr",
  "GsmMctRFCpb",
  "EndOfMctMarker",
  "GsmMccDramType",
  "GsmMccCmdStretch",
  "GsmMccCmdGapRatio",
  "GsmMccAddrMirror",
  "GsmMccCmdTriStateDis",
  "GsmMccCmdTriStateDisTrain",
  "GsmMccFreqPoint",
  "GsmMccEnableOdtMatrix",
  "GsmMccX8Device",
  "GsmMccGear2",
  "GsmMccDdr4OneDpc",
  "GsmMccLDimmMap",
  "GsmMccRankInterleave",
  "GsmMccEnhancedInterleave",
  "GsmMccEccMode",
  "GsmMccAddrDecodeDdrType",
  "GsmMccEnhChannelMode",
  "GsmMccStackedMode",
  "GsmMccStackChMap",
  "GsmMccLChannelMap",
  "GsmMccSChannelSize",
  "GsmMccStackedChHash",
  "GsmMccLDimmSize",
  "GsmMccLDimmDramWidth",
  "GsmMccLDimmRankCnt",
  "GsmMccLDimm8Gb",
  "GsmMccSDimmSize",
  "GsmMccSDimmDramWidth",
  "GsmMccSDimmRankCnt",
  "GsmMccSDimm8Gb",
  "GsmMccPuMrcDone",
  "GsmMccDdrReset",
  "GsmMccEnableRefresh",
  "GsmMccEnableSr",
  "GsmMccMcInitDoneAck",
  "GsmMccMrcDone",
  "GsmMccSafeSr",
  "GsmMccSaveFreqPoint",
  "GsmMccEnableDclk",
  "GsmMccPureSrx",
  "GsmMccLp4FifoRdWr",
  "GsmMccIgnoreCke",
  "GsmMccMaskCs",
  "GsmMccCpgcInOrder",
  "GsmMccCadbEnable",
  "GsmMccDeselectEnable",
  "GsmMccBusRetainOnBubble",
  "GsmMccLpddr2nCsMrw",
  "GsmMccBlockXarb",
  "GsmMccResetOnCmd",
  "GsmMccResetDelay",
  "GsmMccRankOccupancy",
  "GsmMccMcSrx",
  "GsmMccRefInterval",
  "GsmMccRefStaggerEn",
  "GsmMccRefStaggerMode",
  "GsmMccDisableStolenRefresh",
  "GsmMccEnRefTypeDisplay",
  "GsmMccHashMask",
  "GsmMccLsbMaskBit",
  "GsmMccHashMode",
  "GsmMccMr2Shadow",
  "GsmMccSrtAvail",
  "GsmMccDisableCkTristate",
  "GsmMccPbrDis",
  "EndOfMccMarker",
  "GsmComplexRcvEn",
  "GsmComplexRxBias",
  "GsmGtMax",
  "x",        // Add 3 dummy strings after GsmGtMax so the protection code doesn't compare against NULL/garbage pointer when a comma is missing above
  "y",        // This supports up to 3 missing commas
  "z"
};
#endif // MCR_DEBUG_PRINT

/**
  This function sets the specified register bit field.

  @param[in] HashIn        - The bit field hash value.
  @param[in] BitFieldValue - The bit field value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetBitField32 (
  IN const UINT32 HashIn,
  IN const UINT32 BitfieldValue,
  IN const UINT32 RegisterValue
  )
{
  UINT32 Mask;
  UINT32 BfOffset;
  UINT32 BfWidth;
  MRC_REGISTER_HASH_STRUCT Hash;

  Hash.Data = HashIn;
  BfOffset  = Hash.Bits.BfOffset;
  BfWidth   = Hash.Bits.BfWidth;
  Mask      = ((BfWidth >= 32) ? (0xFFFFFFFFUL) : ((1UL << BfWidth) - 1)) << BfOffset;
  return ((RegisterValue & ~Mask) | ((BitfieldValue << BfOffset) & Mask));
}

/**
  This function sets the specified register bit field.

  @param[in] HashIn        - The bit field hash value.
  @param[in] BitFieldValue - The bit field value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalSetBitFieldS32 (
  IN const UINT32 HashIn,
  IN const INT32  BitfieldValue,
  IN const UINT32 RegisterValue
  )
{
  return (MrcHalSetBitField32 (HashIn, BitfieldValue, RegisterValue));
}

/**
  This function will determine if the group access is signed or unsigned and take care of sign extension.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] HashIn        - The bit field hash value.
  @param[in] RegisterValue - The register value to modify.

  @retval The register bit field value.
**/
INT64
MrcHalGsmGetBitField (
  IN MrcParameters *const MrcData,
  IN const MRC_REGISTER_HASH_STRUCT HashIn,
  IN const UINT64 RegisterValue
  )
{
  UINT64_STRUCT Value;

  Value.Data = RegisterValue;
  if (HashIn.Bits.RegSize == 0) {
    if (HashIn.Bits.BfSign == 0) {
      return (MrcHalGetBitField32 (HashIn.Data, Value.Data32.Low));
    } else {
      return (MrcHalGetBitFieldS32 (HashIn.Data, Value.Data32.Low));
    }
  } else {
    if (HashIn.Bits.BfSign == 0) {
      return (MrcHalGetBitField64 (MrcData, HashIn.Data, Value.Data));
    } else {
      return (MrcHalGetBitFieldS64 (MrcData, HashIn.Data, Value.Data));
    }
  }
}

/**
  This function will determine if the group access is signed or unsigned and take care of sign extension.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] HashIn        - The bit field hash value.
  @param[in] BitFieldValue - The bit field value to modify.
  @param[in] RegisterValue - The register value to modify.

  @retval The updated register.
**/
UINT64
MrcHalGsmSetBitField (
  IN MrcParameters *const MrcData,
  IN const MRC_REGISTER_HASH_STRUCT HashIn,
  IN const INT64  BitFieldValue,
  IN const UINT64 RegisterValue
  )
{
  IN INT64_STRUCT BfValue;
  IN UINT64_STRUCT Value;

  BfValue.Data = BitFieldValue;
  Value.Data = RegisterValue;
  if (HashIn.Bits.RegSize == 0) {
    if (HashIn.Bits.BfSign == 0) {
      return (MrcHalSetBitField32 (HashIn.Data, BfValue.Data32.Low, Value.Data32.Low));
    } else {
      return (MrcHalSetBitFieldS32 (HashIn.Data, BfValue.Data32.Low, Value.Data32.Low));
    }
  } else {
    if (HashIn.Bits.BfSign == 0) {
      return (MrcHalSetBitField64 (MrcData, HashIn.Data, BfValue.Data, Value.Data));
    } else {
      return (MrcHalSetBitFieldS64 (MrcData, HashIn.Data, BfValue.Data, Value.Data));
    }
  }
}

/**
  This function gets the specified register bit field.

  @param[in] HashIn        - The bit field hash value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalGetBitField32 (
  IN const UINT32 HashIn,
  IN const UINT32 RegisterValue
  )
{
  UINT32 BfWidth;
  MRC_REGISTER_HASH_STRUCT Hash;

  Hash.Data = HashIn;
  BfWidth   = Hash.Bits.BfWidth;
  return ((RegisterValue >> Hash.Bits.BfOffset) & ((BfWidth >= 32) ? (0xFFFFFFFFUL) : ((1UL << BfWidth) - 1)));
}

/**
  This function gets the specified register bit field.

  @param[in] HashIn        - The bit field hash value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
INT32
MrcHalGetBitFieldS32 (
  IN const UINT32 HashIn,
  IN const UINT32 RegisterValue
  )
{
  UINT32 Value;
  UINT32 BfWidth;
  MRC_REGISTER_HASH_STRUCT Hash;

  Hash.Data = HashIn;
  Value     = MrcHalGetBitField32 (HashIn, RegisterValue);
  BfWidth   = Hash.Bits.BfWidth;
  if (BfWidth < 32) {
    if (Value & (1 << (BfWidth - 1))) {
      Value |= ~((1 << BfWidth) - 1);
    }
  }
  return (Value);
}

/**
  This function sets the specified register bit field.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] HashIn        - The bit field hash value.
  @param[in] BitFieldValue - The bit field value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT64
MrcHalSetBitField64 (
  IN MrcParameters *const MrcData,
  IN const UINT32  HashIn,
  IN const UINT64  BitfieldValue,
  IN const UINT64  RegisterValue
  )
{
  MRC_FUNCTION *Func;
  UINT64 Mask;
  UINT32 BfOffset;
  UINT32 BfWidth;
  MRC_REGISTER_HASH_STRUCT Hash;

  Hash.Data = HashIn;
  BfWidth   = Hash.Bits.BfWidth;
  if (BfWidth >= 64) {
    return (BitfieldValue);
  }
  BfOffset = Hash.Bits.BfOffset;
  Func     = MrcData->Inputs.Call.Func;
  Mask     = Func->MrcLeftShift64 ((Func->MrcLeftShift64 (1ULL, BfWidth) - 1), BfOffset);
  return ((RegisterValue & ~Mask) | (Func->MrcLeftShift64 (BitfieldValue, BfOffset) & Mask));
}

/**
  This function sets the specified register bit field.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] HashIn        - The bit field hash value.
  @param[in] BitFieldValue - The bit field value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT64
MrcHalSetBitFieldS64 (
  IN MrcParameters *const MrcData,
  IN const UINT32  HashIn,
  IN const INT64   BitfieldValue,
  IN const UINT64  RegisterValue
  )
{
  return (MrcHalSetBitField64 (MrcData, HashIn, BitfieldValue, RegisterValue));
}

/**
  This function gets the specified register bit field.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] HashIn        - The bit field hash value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT64
MrcHalGetBitField64 (
  IN MrcParameters *const MrcData,
  IN const UINT32  HashIn,
  IN const UINT64  RegisterValue
  )
{
  MRC_FUNCTION *Func;
  UINT32 BfWidth;
  MRC_REGISTER_HASH_STRUCT Hash;

  Hash.Data = HashIn;
  BfWidth   = Hash.Bits.BfWidth;
  if (BfWidth >= 64) {
    return (RegisterValue);
  }
  Func = MrcData->Inputs.Call.Func;
  return ((Func->MrcRightShift64 (RegisterValue, Hash.Bits.BfOffset)) & (Func->MrcLeftShift64 (1ULL, BfWidth) - 1));
}

/**
  This function gets the specified register bit field.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] HashIn        - The bit field hash value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
INT64
MrcHalGetBitFieldS64 (
  IN MrcParameters *const MrcData,
  IN const UINT32  HashIn,
  IN const UINT64  RegisterValue
  )
{
  MRC_FUNCTION *Func;
  UINT64 Value;
  UINT64 Sign;
  UINT32 BfWidth;
  MRC_REGISTER_HASH_STRUCT Hash;

  Value     = MrcHalGetBitField64 (MrcData, HashIn, RegisterValue);
  Hash.Data = HashIn;
  BfWidth   = Hash.Bits.BfWidth;
  if (BfWidth < 64) {
    Func = MrcData->Inputs.Call.Func;
    Sign = Func->MrcLeftShift64 (1ULL, BfWidth - 1);
    if (Value & Sign) {
      Value |= ~(Func->MrcLeftShift64 (1ULL, BfWidth) - 1);
    }
  }
  return (Value);
}

/**
  CPU specific function when encodes Vref (mV) for the GSM_GT RxVref.

  @param[in]  MrcData       - Pointer to global data.
  @param[in]  Vref          - Vref value to encode, in mV.
  @param[out] VrefEncoding  - Register value of the Vref to program.
**/
VOID
MrcEncodeRxVref (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                Vref,
  OUT INT64                 *VrefEncoded
  )
{
  MrcOutput *Outputs;
  UINT32    Encoding;
  UINT32    Vdd;

  Outputs = &MrcData->Outputs;

  Vdd = Outputs->VddVoltage[MrcData->Inputs.MemoryProfile];
  if ((Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) && (Outputs->Lp4x)) {
    Vdd = VDD_1_10;
  }
  // Register moves in steps of VDD/191.  The encoding would be:
  //   Step = Vdd / 191
  //   Encoding = Vref / Step
  //   Encoding = Vref / Vdd / 191
  // To avoid loss of precision, multiply Vref by the step size, then DIVIDEROUND with VDD
  Encoding = Vref * 191;
  Encoding = UDIVIDEROUND (Encoding, Vdd);

  MRC_DEBUG_ASSERT (VrefEncoded != 0, &MrcData->Outputs.Debug, "%s", gNullPtrErrStr);
  *VrefEncoded = Encoding;
}

#ifdef MRC_DEBUG_PRINT
/**
  This debug only function checks to ensure the group is supported by GetSet.

  @param[in]  MrcData - Global MRC Data.
  @param[in]  Group   - The group to be accessed.

  @retval mrcSuccess if supported, otherwise mrcWrongInputParameter
**/
static
MrcStatus
MrcCheckGroupSupported (
  IN  MrcParameters *const  MrcData,
  IN  GSM_GT        const   Group
  )
{
  if (MrcData->Inputs.IclA0) {
    if ((Group == TxVref) || (Group == GsmIocTxVrefConverge)) {
      // For B0 and up the code will continue below and return "not supported"
      return mrcSuccess;
    }
  }
  switch (Group) {
    case RecEnDelay:
    case RxDqsPDelay:
    case RxDqsNDelay:
    case RxVref:
    case RxVoc:
    case RxEq:
    case RxDqBitDelay:
    case RxRankMuxDelay:
    case TxDqsDelay:
    case TxDqDelay:
    case TxEq:
    case TxRankMuxDelay:
    case TxDqsRankMuxDelay:
    case TxDqBitDelay:
    case RecEnOffset:
    case RxDqsOffset:
    case RxVrefOffset:
    case TxDqsOffset:
    case TxDqOffset:
    case RoundTripDelay:
    case RxFlybyDelay:
    case RxIoTclDelay:
    case RxFifoRdEnFlybyDelay:
    case RxFifoRdEnTclDelay:
    case RxDqDataValidDclkDelay:
    case RxDqDataValidQclkDelay:
    case TxDqFifoWrEnTcwlDelay:
    case TxDqFifoRdEnTcwlDelay:
    case TxDqFifoRdEnFlybyDelay:
    case SenseAmpDelay:
    case SenseAmpDuration:
    case McOdtDelay:
    case McOdtDuration:
    case McDqsOdtDelay:
    case McDqsOdtDuration:
    case DqDfeEnable:
    case DqDfeDelayMode:
    case DqDfeCoeff:
    case DqDfeDelay:
    case GsmComplexRxBias:
    case RxBiasIComp:
    case RxBiasRComp:
    case RxBiasRCompMsb:
    case RxBiasRCompLsb:
    case RxDqsAmpOffset:
    case SdllPiCb:
    case D0PiCb:
    case SdllBwCtrl:
    case D0BwCtrl:
    case RxCben:
    case CBEnAmp1:
    case CmdVref:
    case CmdGrpPi:
    case CtlGrpPi:
    case ClkGrpPi:
    case CkeGrpPi:
    case TxSlewRate:
    case DqScompPC:
    case CmdSlewRate:
    case CmdScompPC:
    case CtlSlewRate:
    case CtlScompPC:
    case ClkSlewRate:
    case ClkScompPC:
    case DqRcompStatLegs:
    case SCompCodeDq:
    case SCompCodeCmd:
    case SCompCodeCtl:
    case SCompCodeClk:
    case TxRonUp:
    case WrDSCodeUpCmd:
    case WrDSCodeUpCtl:
    case WrDSCodeUpClk:
    case TxRonDn:
    case WrDSCodeDnCmd:
    case WrDSCodeDnCtl:
    case WrDSCodeDnClk:
    case TxTco:
    case TxTcoDqsN:
    case TxTcoDqsP:
    case TxTcoByPass:
    case TcoCompCodeCmd:
    case TcoCompCodeCtl:
    case TcoCompCodeClk:
    case CompRcompOdtUp:
    case CompRcompOdtDn:
    case ClkRCompDrvDownOffset:
    case ClkRCompDrvUpOffset:
    case ClkCompOnTheFlyUpdtEn:
    case ClkSCompOffset:
    case CtlSCompOffset:
    case CtlRCompDrvUpOffset:
    case CtlRCompDrvDownOffset:
    case CkeRCompDrvDownOffset:
    case CkeRCompDrvUpOffset:
    case CkeSCompOffset:
    case CmdSCompOffset:
    case CmdRCompDrvUpOffset:
    case CmdRCompDrvDownOffset:
    case GsmIocDataOdtStaticDis:
    case GsmIocCompOdtStaticDis:
    case GsmIocDataCtlLpMode:
    case GsmIocLowSupEnDqDqs:
    case GsmIocPanicDrvUpVref:
    case GsmIocLp4DqsMaskPulseCnt:
    case GsmIocLp4ForceDqsPOn:
    case GsmIocLp4ForceDqsNOn:
    case GsmIocLp4ForceDqsPOnWithLeaker:
    case GsmIocLp4ForceDqsNOnWithLeaker:
    case GsmIocLp4DqsPulseCnt:
    case GsmIocLp4DqsPulseEn:
    case GsmIocLp4DqOverrideData:
    case GsmIocLp4DqOverrideEn:
    case GsmIocRankOverrideEn:
    case GsmIocRankOverrideVal:
    case GsmIocDataCtlGear1:
    case GsmIocDccTrainingMode:
    case GsmIocDccTrainingDone:
    case GsmIocDccDrain:
    case GsmIocDccActiveClks:
    case GsmIocDccActiveBytes:
    case GsmIocDccDcoCompEn:
    case GsmIocDccPeriodicDis:
    case GsmIocDccDcoLfsrDis:
    case GsmIocDccClkTrainVal:
    case GsmIocDccDataTrainDqsVal:
    case GsmIocDccDqsReplica:
    case GsmIocDccAipCb:
    case GsmIocDccAipCbDqs:
    case GsmIocLpEarlyRLeak:
    case GsmIocOdtSampExtEn:
    case GsmIocDqsOdtSampExtEn:
    case GsmIocStrongWeakLeaker:
    case GsmIocStrongWeakLeakerMsb:
    case GsmIocRcvenFourCycleFill:
    case GsmIocEnRcvenPreZeroFill:
    case GsmIocSdllSegmentDisable:
    case GsmIocDllWeakLock:
    case GsmIocLpLongOdtEn:
    case GsmIocRxClkStg:
    case GsmIocRxClkStgNumMsb:
    case GsmIocLeakerComp:
    case GsmIocLeakerWithTxAnalogEn:
    case GsmIocStrong2WeakOnDqsOdt:
    case GsmIocForceDqsOnQuickOdtOff:
    case GsmIocLongWrPreambleLp4:
    case GsmIocRxBiasSel:
    case GsmIocDataCtlLp4Mode:
    case GsmIocForceBiasOn:
    case GsmIocForceRxAmpOn:
    case GsmIocDataVddqOdtEn:
    case GsmIocDataVttOdtEn:
    case GsmIocVssOdtEn:
    case GsmIocGlobalClkEn:
    case GsmIocRxTypeSelect:
    case GsmIocCompVddqOdtEn:
    case GsmIocCompVttOdtEn:
    case GsmIocCmdDrvVref200ohm:
    case GsmIocVttPanicCompUpMult:
    case GsmIocVttPanicCompDnMult:
    case GsmIocRxVrefMFC:
    case GsmIocVrefPwrDnEn:
    case GsmIocDataCtlDdr4Mode:
    case GsmIocRxDeskewDis:
    case GsmIocTxDeskewDis:
    case GsmIocDqSlewDlyByPass:
    case GsmIocWlLongDelEn:
    case GsmIocTxEqDis:
    case GsmIocRxStaggerCtl:
    case GsmIocRxDeskewCal:
    case GsmIocTxDeskewCal:
    case GsmIocTxOn:
    case GsmIocSenseAmpMode:
    case GsmIocReadLevelMode:
    case GsmIocXoverMinDelayCtl:
    case GsmIocWriteLevelMode:
    case GsmIocReadDqDqsMode:
    case GsmIocForceOdtOn:
    case GsmIocRxPiPwrDnDis:
    case GsmIocTxPiPwrDnDis:
    case GsmIocInternalClocksOn:
    case GsmIocTxDisable:
    case GsmIocIoReset:
    case GsmIocCmdVrefConverge:
    case GsmIocNoDqInterleave:
    case GsmIocScramLpMode:
    case GsmIocScramDdr4Mode:
    case GsmIocDdrCentric:
    case GsmIocScramGear1:
    case GsmIoc4ChMode:
    case GsmIocScramLp4Mode:
    case GsmIocChNotPop:
    case GsmIocDisIosfSbClkGate:
    case GsmIocEccEn:
    case GsmIocWlWakeCyc:
    case GsmIocWlSleepCyc:
    case GsmIocDisDataIdlClkGate:
    case GsmIocDllMask:
    case GsmIocWlLatency:
    case GsmIocLpRcvenCtrl:
    case GsmIocDllWlEn:
    case GsmIocConstZTxEqEn:
    case GsmIocCompClkOn:
    case GsmIocCompVccddqLo:
    case GsmIocDisableQuickComp:
    case GsmIocSinStep:
    case GsmIocSinStepAdv:
    case GsmIocDqOdtUpDnOff:
    case GsmIocFixOdtD:
    case GsmIocForceCmpUpdt:
    case GsmIocOdtOverride:
    case GsmIocOdtOn:
    case GsmIocMprTrainDdrOn:
    case GsmIocCkeOverride:
    case GsmIocCkeOn:
    case GsmIocRptChRepClkOn:
    case GsmIocCmdAnlgEnGraceCnt:
    case GsmIocTxAnlgEnGraceCnt:
    case GsmIocTxDqFifoRdEnPerRankDelDis:
    case DqOdtVref:
    case DqDrvVref:
    case CmdDrvVref:
    case CmdTxEq:
    case CtlDrvVref:
    case ClkDrvVref:
    case GsmMctRP:
    case GsmMctRPabExt:
    case GsmMctRAS:
    case GsmMctRDPRE:
    case GsmMctPPD:
    case GsmMctWRPRE:
    case GsmMctFAW:
    case GsmMctRRDsg:
    case GsmMctRRDdg:
    case GsmMctLpDeratingExt:
    case GsmMctRDRDsg:
    case GsmMctRDRDdg:
    case GsmMctRDRDdr:
    case GsmMctRDRDdd:
    case GsmMctRDWRsg:
    case GsmMctRDWRdg:
    case GsmMctRDWRdr:
    case GsmMctRDWRdd:
    case GsmMctWRRDsg:
    case GsmMctWRRDdg:
    case GsmMctWRRDdr:
    case GsmMctWRRDdd:
    case GsmMctWRWRsg:
    case GsmMctWRWRdg:
    case GsmMctWRWRdr:
    case GsmMctWRWRdd:
    case GsmMctCKE:
    case GsmMctXP:
    case GsmMctXPDLL:
    case GsmMctPRPDEN:
    case GsmMctRDPDEN:
    case GsmMctWRPDEN:
    case GsmMctXSDLL:
    case GsmMctXSR:
    case GsmMctZQOPER:
    case GsmMctMOD:
    case GsmMctZQCAL:
    case GsmMctZQCS:
    case GsmMctZQCSPeriod:
    case GsmMctSrIdle:
    case GsmMctREFI:
    case GsmMctRFC:
    case GsmMctOrefRi:
    case GsmMctRefreshHpWm:
    case GsmMctRefreshPanicWm:
    case GsmMctREFIx9:
    case GsmMccLDimmMap:
    case GsmMccRankInterleave:
    case GsmMccEnhancedInterleave:
    case GsmMccEccMode:
    case GsmMccAddrDecodeDdrType:
    case GsmMccEnhChannelMode:
    case GsmMccStackedMode:
    case GsmMccStackChMap:
    case GsmMccLChannelMap:
    case GsmMccSChannelSize:
    case GsmMccStackedChHash:
    case GsmMccLDimmSize:
    case GsmMccLDimmDramWidth:
    case GsmMccLDimmRankCnt:
    case GsmMccLDimm8Gb:
    case GsmMccSDimmSize:
    case GsmMccSDimmDramWidth:
    case GsmMccSDimmRankCnt:
    case GsmMccSDimm8Gb:
    case GsmMccPuMrcDone:
    case GsmMccSaveFreqPoint:
    case GsmMccEnableRefresh:
    case GsmMccEnableSr:
    case GsmMccMcInitDoneAck:
    case GsmMccMrcDone:
    case GsmMccEnableDclk:
    case GsmMccPureSrx:
    case GsmMccLp4FifoRdWr:
    case GsmMccIgnoreCke:
    case GsmMccMaskCs:
    case GsmMccCpgcInOrder:
    case GsmMccCadbEnable:
    case GsmMccDeselectEnable:
    case GsmMccBusRetainOnBubble:
    case GsmMccLpddr2nCsMrw:
    case GsmMccBlockXarb:
    case GsmMccResetOnCmd:
    case GsmMccResetDelay:
    case GsmMccDramType:
    case GsmMccCmdStretch:
    case GsmMccCmdGapRatio:
    case GsmMccAddrMirror:
    case GsmMccCmdTriStateDis:
    case GsmMccCmdTriStateDisTrain:
    case GsmMccFreqPoint: // This aliases with ddr_probless_low_frequency on SKL.
    case GsmMccEnableOdtMatrix:
    case GsmMccX8Device:
    case GsmMccGear2:
    case GsmMccDdr4OneDpc:
    case GsmMctOdtRdDuration:
    case GsmMctOdtRdDelay:
    case GsmMctWrEarlyOdt:
    case GsmMctOdtWrDuration:
    case GsmMctOdtWrDelay:
    case GsmMctCL:
    case GsmMctCWL:
    case GsmMctAONPD:
    case GsmMctCKCKEH:
    case GsmMctCSCKEH:
    case GsmMccRankOccupancy:
    case GsmMccMcSrx:
    case GsmMccRefInterval:
    case GsmMccRefStaggerEn:
    case GsmMccRefStaggerMode:
    case GsmMccDisableStolenRefresh:
    case GsmMccEnRefTypeDisplay:
    case GsmMccHashMask:
    case GsmMccLsbMaskBit:
    case GsmMccHashMode:
    case GsmMccMr2Shadow:
    case GsmMccSrtAvail:
    case GsmMctCPDED:
    case GsmMctRCDwr:
    case GsmMctRFCpb:
    case GsmMccDisableCkTristate:
    case GsmMccPbrDis:
      break;

    // These are unused.  Need to finish HAL if these fields are accessed.
    default:
      MRC_DEBUG_MSG (
        &MrcData->Outputs.Debug,
        MSG_LEVEL_ERROR,
        "%s GetSet Group %s(%d) is not supported!\n",
        gErrString,
        GsmGtDebugStrings[Group],
        Group
        );
      return mrcWrongInputParameter;
      break;
  }
  return mrcSuccess;
}
#endif

/**
  This function is used to determine if the GSM_GT passed in is a complex parameter or has a side effect.

  @param[in]  MrcData - Pointer to global data structure.
  @param[in]  Group   - GetSet group to check.
  @param[in]  IsComplex - The requested check is to see if the parameter is complex.  Otherwise is there a side effect.

  @retval TRUE if complex or side effect, otherwise FALSE.
**/
BOOLEAN
MrcCheckComplexOrSideEffect (
  IN  MrcParameters *const  MrcData,
  IN  GSM_GT        const   Group,
  IN  BOOLEAN       const   IsComplex
  )
{
  BOOLEAN RetVal;

  RetVal = FALSE;

  if (IsComplex) {
    switch (Group) {
      case RxBiasRComp:
      case GsmComplexRxBias:
        RetVal = TRUE;
        break;

      // Not a complex parameter
      default:
        break;
    }
  } else {
    // Side Effect
    switch (Group) {
      case RecEnDelay:
      case RecEnOffset:
      case TxDqsDelay:
      case TxDqsOffset:
      case TxDqDelay:
      case TxDqOffset:
      case ClkGrpPi:
        RetVal = TRUE;
        break;

      // No Side Effect.
      default:
        break;
    }
  }

  /*MRC_HAL_DEBUG_MSG (
    &MrcData->Outputs.Debug,
    MSG_LEVEL_HAL,
    "GetSet Group %s(%d) is %s a %s param.\n",
    GsmGtDebugStrings[Group],
    Group,
    (RetVal) ? "" : "not",
    (IsComplex) ? "complex" :  "side effect"
    );*/

  return RetVal;
}

/**
  This function perform any side effect action required from the Group that was just set.
  It will inherit the same Mode parameter so it passed it on to the actions executed.

  @param[in]      MrcData     - Pointer to global data structure.
  @param[in]      Socket      - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]      Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]      SubChannel  - DDR SubChannel number within a Channel (0-Based).
  @param[in]      Rank        - Rank number within a channel (0-based).
  @param[in]      Strobe      - If Group is a CMD/CTL/CLK Index type, this is the index for that signal.  Otherwise, Dqs data group within the rank (0-based).
  @param[in]      Bit         - Bit index within the data group (0-based).
  @param[in]      FreqIndex   - Index supporting multiple operating frequencies.
  @param[in]      Group       - DDRIO group to access.
  @param[in]      Mode        - Bit-field flags controlling Get/Set.
  @param[in,out]  Value       - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval Nothing.
**/
void
MrcGetSetSideEffect (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Socket,
  IN      UINT32        const   Channel,
  IN      UINT32        const   SubChannel,
  IN      UINT32        const   Rank,
  IN      UINT32        const   Strobe,
  IN      UINT32        const   Bit,
  IN      UINT32        const   FreqIndex,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN      INT64         *const  Value
  )
{
  MrcIntOutput  *MrcIntData;
  BOOLEAN   Flush;
  BOOLEAN   Gear2;
  INT64     TxDqsValue;
  INT64     TotalPiValue;
  GSM_GT    WriteGroup;
  GSM_GT    SecondGroup;
  INT64     GetSetVal;
  UINT32    LocalRank;
  UINT32    LocalModeWrite;
  UINT32    LocalModeRead;
  UINT32    SearchVal;
  UINT32    Divisor;
  BOOLEAN   Lpddr4;

  Gear2 = MrcData->Outputs.Gear2;
  Lpddr4 = (MrcData->Outputs.DdrType == MRC_DDR_TYPE_LPDDR4);

  // Read from cache or register based on the write Mode to the group
  LocalModeRead = GSM_READ_ONLY;
  if (Mode & GSM_READ_CSR) {
    LocalModeRead |= GSM_READ_CSR;
  }
  // Write based on original mode. Clear offset write flag
  LocalModeWrite = Mode;
  LocalModeWrite &= ~GSM_WRITE_OFFSET;

  if ((Mode & GSM_UPDATE_CACHE) == 0) {
    // If original mode is not using the cache, the side effect write should not use it as well
    LocalModeWrite |= GSM_READ_CSR;
  }

  // For RankMuxDelay we need to consider a total PI = Delay + Offset
  switch (Group) {
    case RecEnDelay:
      SecondGroup = RecEnOffset;
      WriteGroup  = RxRankMuxDelay;
      break;

    case RecEnOffset:
      SecondGroup = RecEnDelay;
      WriteGroup  = RxRankMuxDelay;
      break;

    case TxDqDelay:
      SecondGroup = TxDqOffset;
      WriteGroup  = TxRankMuxDelay;
      break;

    case TxDqOffset:
      SecondGroup = TxDqDelay;
      WriteGroup  = TxRankMuxDelay;
      break;

    case TxDqsDelay:
      SecondGroup = TxDqsOffset;
      WriteGroup  = TxDqsRankMuxDelay;
      break;

    case TxDqsOffset:
      SecondGroup = TxDqsDelay;
      WriteGroup  = TxDqsRankMuxDelay;
      break;

    default:
      SecondGroup = GsmGtMax;
      WriteGroup  = GsmGtMax;
      break;
  }
  if (WriteGroup != GsmGtMax) {
    // Find the smallest RecEn/TxDqs/TxDq PI in the Byte/Channel and update the new [Rx,Tx]RankMuxDelay
    SearchVal = MRC_UINT32_MAX;
    for (LocalRank = 0; LocalRank < MAX_RANK_IN_CHANNEL; LocalRank++) {
      if (MrcRankInChannelExist (MrcData, LocalRank, Channel)) {
        // Determine the total PI value from Delay and Offset
        MrcGetSetDdrIoGroupStrobe (MrcData, Channel, LocalRank, Strobe, Group,       LocalModeRead, &GetSetVal);
        MrcGetSetDdrIoGroupStrobe (MrcData, Channel, LocalRank, Strobe, SecondGroup, LocalModeRead, &TotalPiValue);
        TotalPiValue += GetSetVal;
        SearchVal = MIN (SearchVal, (UINT32) TotalPiValue);
      }
    }

    // Align to a QCLK (Gear1) or DCLK (Gear2)
    Divisor = Gear2 ? 128 : 64;
    GetSetVal = DIVIDEFLOOR (SearchVal, Divisor);

    if (WriteGroup == RxRankMuxDelay) {
      // RxRankMuxDelay = Floor(min_rank{RxRcvEnPi[n]}/(64 * Gear))
      // If Gear2: RxRankMuxDelay += (Lp4 ? 1 : 2)
      if (Gear2) {
        GetSetVal = (Lpddr4 ? 1 : 2) + GetSetVal;
      }
    }
    MrcGetSetDdrIoGroupStrobe (MrcData, Channel, 0, Strobe, WriteGroup, LocalModeWrite, &GetSetVal);
  }

  // Side Effect for DCC
  if (((Mode & GSM_READ_ONLY) == 0) && ((Group == ClkGrpPi) || (Group == TxDqsDelay) || (Group == TxDqsOffset))) {
    // Only when writing to registers related to ClkGrpPi and TxDqsDelay
    MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));

    // Flush only when GSM_CACHE_ONLY is not set
    Flush = ((Mode & GSM_CACHE_ONLY) == 0);

    if (MrcIntData->ClkDccInit && (Group == ClkGrpPi)) {
      // Update using CLK DCC LUT
      GetSetVal = (UINT32) *Value % MAX_DCC_CLOCK_PI;
      MrcDccUpdate (MrcData, Channel, Rank, Strobe, GsmIocDccClkTrainVal, &GetSetVal, Flush);
    }

    if (MrcIntData->DqsDccInit && ((Group == TxDqsDelay) || (Group == TxDqsOffset))) {
      // Determine the total TxDqs value w/ TxDqsDelay and TxDqsOffset (Read the other set, unless the write is w/ GSM_WRITE_OFFSET)
      MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Strobe, (Group == TxDqsDelay) ? TxDqsOffset : TxDqsDelay, LocalModeRead, &TxDqsValue);
      if (Mode & GSM_WRITE_OFFSET) {
        MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Strobe, Group, LocalModeRead, &GetSetVal);
        TxDqsValue += GetSetVal;
      } else {
        TxDqsValue += *Value;
      }
      // Update using DQS DCC LUT
      TxDqsValue = (UINT32) TxDqsValue % MAX_DCC_TX_DQS_DQ_PI;
      MrcDccUpdate (MrcData, Channel, Rank, Strobe, GsmIocDccDataTrainDqsVal, &TxDqsValue, Flush);
    }
  }
}

/**
  This function handles accessing and updating complex parameter values.
  This function will adjust the signal for that scope.  It will Not adjust other relative signals.
    Any shared parameter will need to be accounted for outside this function.
  The way each complex parameter is composed is project specific.
  The units of each parameter is specified in the parameter declaration in GSM_GT.

  @param[in]      MrcData     - Pointer to global data structure.
  @param[in]      Socket      - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]      Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]      SubChannel  - DDR SubChannel number within a Channel (0-Based).
  @param[in]      Rank        - Rank number within a channel (0-based).
  @param[in]      Strobe      - If Group is a CMD/CTL/CLK Index type, this is the index for that signal.  Otherwise, Dqs data group within the rank (0-based).
  @param[in]      Bit         - Bit index within the data group (0-based).
  @param[in]      FreqIndex   - Index supporting multiple operating frequencies.
  @param[in]      Group       - DDRIO group to access.
  @param[in]      Mode        - Bit-field flags controlling Get/Set.
  @param[in,out]  Value       - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus: mrcComplexParamDone - no more programming is needed, otherwise continue with GetSet flow.
**/
MrcStatus
MrcGetSetComplexParam (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Socket,
  IN      UINT32        const   Channel,
  IN      UINT32        const   SubChannel,
  IN      UINT32        const   Rank,
  IN      UINT32        const   Strobe,
  IN      UINT32        const   Bit,
  IN      UINT32        const   FreqIndex,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  )
{
  MrcStatus Status;
  INT64     Lsb;
  INT64     Msb;
  INT64     BiasRcomp;
  INT64     BiasIcomp;
  UINT64    Data64;
  UINT8     Val8;

  Status = mrcComplexParamDone;

  switch (Group) {
      // DataControl6 Bit 1 is used as the MSB to DataControl4.biasrcomp
      // The field is unsigned, and in total 4-bits wide.
    case RxBiasRComp:
      Val8 = (UINT8) *Value;
      Msb = (*Value >= 0) ? ((Val8 >> 3) & 0x1) : -1; // Cause clamping warning for negative numbers
      Lsb = Val8 & 0x7;
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Strobe, RxBiasRCompLsb, Mode, &Lsb);
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Strobe, RxBiasRCompMsb, Mode, &Msb);
      Data64 = Lsb;
      Data64 |= (UINT64)(((UINT8) Msb) << 3);
      *Value = Data64;
      break;

    case GsmComplexRxBias:
      Val8 = (UINT8) *Value;
      BiasRcomp = (Val8 / 16) + 8;
      BiasIcomp = Val8 % 16;
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Strobe, RxBiasRComp, Mode, &BiasRcomp);
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Strobe, RxBiasIComp, Mode, &BiasIcomp);
      break;

    default:
      break;
  }

  return Status;
}

/**
  Top level function used to interact with DDRIO parameters.
  This function ignores unused parameters in Core MRC to reduce code space.
    Socket Index, DIMM index, FreqIndex, and Level.
  Only one setting for the whole controller, so Channel, Rank, Strobe, and Bit index is dropped.

  @param[in]      MrcData   - Pointer to global data structure.
  @param[in]      Group     - DDRIO group to access.
  @param[in]      Mode      - Bit-field flags controlling Get/Set.
  @param[in,out]  Value     - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetDdrIoGroupController0 (
  IN      MrcParameters *const  MrcData,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  )
{
  return MrcGetSetDdrIoGroupChannel (MrcData, MRC_IGNORE_ARG, Group, Mode, Value);
}

/**
  Top level function used to interact with DDRIO parameters.
  This function ignores unused parameters in Core MRC to reduce code space.
    Socket Index, DIMM index, FreqIndex, and Level.
  This function is used to access indexed Command/Control/Clock groups.

  @param[in]      MrcData   - Pointer to global data structure.
  @param[in]      Channel   - DDR Channel Number within the processor socket (0-based)
  @param[in]      Index     - Group index to Get/Set.
  @param[in]      Group     - DDRIO group to access.
  @param[in]      Mode      - Bit-field flags controlling Get/Set.
  @param[in,out]  Value     - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetDdrIoCmdGroup (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Channel,
  IN      UINT32        const   Index,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  )
{
  return MrcGetSetDdrIoGroupSocket0Sch (MrcData, Channel, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Index, MRC_IGNORE_ARG, Group, Mode, Value);
}

/**
  Top level function used to interact with DDRIO parameters.
  This function ignores unused parameters in Core MRC to reduce code space.
    Socket Index, DIMM index, FreqIndex, and Level.
  The lowest scope of access is Channel, so Rank, Strobe, and Bit index is dropped.

  @param[in]      MrcData   - Pointer to global data structure.
  @param[in]      Channel   - DDR Channel Number within the processor socket (0-based)
  @param[in]      Group     - DDRIO group to access.
  @param[in]      Mode      - Bit-field flags controlling Get/Set.
  @param[in,out]  Value     - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetDdrIoGroupChannel (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Channel,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  )
{
  return MrcGetSetDdrIoGroupStrobe (MrcData, Channel, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Group, Mode, Value);
}
/**
  Top level function used to interact with DDRIO parameters.
  This function ignores unused parameters in Core MRC to reduce code space.
    Socket Index, DIMM index, FreqIndex, and Level.
  This function is for those registers that are only per Channel per Rank granularity.
  The lowest scope of access is Rank, so Strobe, and Bit index is dropped.

  @param[in]      MrcData   - Pointer to global data structure.
  @param[in]      Channel   - DDR Channel Number within the processor socket (0-based)
  @param[in]      Rank      - Rank within the DDR Channel (0-based).
  @param[in]      Group     - DDRIO group to access.
  @param[in]      Mode      - Bit-field flags controlling Get/Set.
  @param[in,out]  Value     - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetDdrIoGroupChannelRank (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Channel,
  IN      UINT32        const   Rank,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  )
{
  return MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, MRC_IGNORE_ARG, Group, Mode, Value);
}

/**
  Top level function used to interact with DDRIO parameters.
  This function ignores unused parameters in Core MRC to reduce code space.
    Socket Index, DIMM index, FreqIndex, and Level.
  This function is for those registers that are only per Strobe per Channel granularity.
  The lowest scope of access is Strobe, so the Bit index is dropped.

  @param[in]      MrcData   - Pointer to global data structure.
  @param[in]      Channel   - DDR Channel Number within the processor socket (0-based)
  @param[in]      Strobe    - Dqs data group within the rank (0-based).
  @param[in]      Group     - DDRIO group to access.
  @param[in]      Mode      - Bit-field flags controlling Get/Set.
  @param[in,out]  Value     - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetDdrIoGroupChannelStrobe (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Channel,
  IN      UINT32        const   Strobe,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  )
{
  return MrcGetSetDdrIoGroupStrobe (MrcData, Channel, MRC_IGNORE_ARG, Strobe, Group, Mode, Value);
}

/**
  Top level function used to interact with DDRIO parameters.
  This function ignores unused parameters in Core MRC to reduce code space.
    Socket Index, DIMM index, FreqIndex, and Level.
  The lowest scope of access is Strobe, so the Bit index is dropped.

  @param[in]      MrcData   - Pointer to global data structure.
  @param[in]      Channel   - DDR Channel Number within the processor socket (0-based)
  @param[in]      Rank      - Rank number within a channel (0-based).
  @param[in]      Strobe    - Dqs data group within the rank (0-based).
  @param[in]      Group     - DDRIO group to access.
  @param[in]      Mode      - Bit-field flags controlling Get/Set.
  @param[in,out]  Value     - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetDdrIoGroupStrobe (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Channel,
  IN      UINT32        const   Rank,
  IN      UINT32        const   Strobe,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  )
{
  return MrcGetSetDdrIoGroupSocket0 (MrcData, Channel, Rank, Strobe, MRC_IGNORE_ARG, Group, Mode, Value);
}

/**
  Top level function used to interact with DDRIO parameters.
  This function ignores unused parameters in Core MRC to reduce code space.
    Socket Index, DIMM index, FreqIndex, and Level.

  @param[in]      MrcData   - Pointer to global data structure.
  @param[in]      Channel   - DDR Channel Number within the processor socket (0-based)
  @param[in]      Rank      - Rank number within a channel (0-based).
  @param[in]      Strobe    - Dqs data group within the rank (0-based).
  @param[in]      Bit       - Bit index within the data group (0-based).
  @param[in]      Group     - DDRIO group to access.
  @param[in]      Mode      - Bit-field flags controlling Get/Set.
  @param[in,out]  Value     - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetDdrIoGroupSocket0 (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Channel,
  IN      UINT32        const   Rank,
  IN      UINT32        const   Strobe,
  IN      UINT32        const   Bit,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  )
{
  return MrcGetSetDdrIoGroup (MrcData, 0, Channel, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Rank, Strobe, Bit, 0, DdrLevel, Group, Mode, Value);
}

/**
  Top level function used to interact with DDRIO parameters.
  This function ignores unused parameters in Core MRC to reduce code space.
    Socket, Channel, DIMM, Rank, Strobe, Bit, and Level.

  @param[in]      MrcData   - Pointer to global data structure.
  @param[in]      FreqIndex - Index supporting multiple operating frequencies.
  @param[in]      Group     - DDRIO group to access.
  @param[in]      Mode      - Bit-field flags controlling Get/Set.
  @param[in,out]  Value     - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetDdrIoGroupFreqIndex (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   FreqIndex,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  )
{
  return MrcGetSetDdrIoGroup (MrcData, 0, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, FreqIndex, DdrLevel, Group, Mode, Value);
}

/**
  Top level function used to interact with DDRIO parameters.
    Socket Index, DIMM index, FreqIndex, and Level.

  @param[in]      MrcData   - Pointer to global data structure.
  @param[in]      Channel   - DDR Channel Number within the processor socket (0-based)
  @param[in]      SubChannel  - DDR SubChannel number within a Channel (0-Based).
  @param[in]      Rank      - Rank number within a channel (0-based).
  @param[in]      Strobe    - Dqs data group within the rank (0-based).
  @param[in]      Bit       - Bit index within the data group (0-based).
  @param[in]      Group     - DDRIO group to access.
  @param[in]      Mode      - Bit-field flags controlling Get/Set.
  @param[in,out]  Value     - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetDdrIoGroupSocket0Sch (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Channel,
  IN      UINT32        const   SubChannel,
  IN      UINT32        const   Rank,
  IN      UINT32        const   Strobe,
  IN      UINT32        const   Bit,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  )
{
  return MrcGetSetDdrIoGroup (MrcData, 0, Channel, SubChannel, MRC_IGNORE_ARG, Rank, Strobe, Bit, 0, DdrLevel, Group, Mode, Value);
}

/**
  Top level function used to interact with DDRIO parameters.
  This function ignores unused parameters in Core MRC to reduce code space.
    Socket Index, DIMM index, FreqIndex, and Level.

  @param[in]      MrcData     - Pointer to global data structure.
  @param[in]      Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]      SubChannel  - DDR SubChannel number within a Channel (0-Based).
  @param[in]      Rank        - Rank number within a channel (0-based).
  @param[in]      Group       - DDRIO group to access.
  @param[in]      Mode        - Bit-field flags controlling Get/Set.
  @param[in,out]  Value       - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetDdrIoGroupChSchRnk (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Channel,
  IN      UINT32        const   SubChannel,
  IN      UINT32        const   Rank,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  )
{
  return MrcGetSetDdrIoGroup (MrcData, 0, Channel, SubChannel, MRC_IGNORE_ARG, Rank, MRC_IGNORE_ARG, MRC_IGNORE_ARG, 0, DdrLevel, Group, Mode, Value);
}

/**
  Top level function used to interact with DDRIO parameters.
  This function ignores unused parameters in Core MRC to reduce code space.
    Socket Index, DIMM index, FreqIndex, and Level.

  @param[in]      MrcData     - Pointer to global data structure.
  @param[in]      Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]      SubChannel  - DDR SubChannel number within a Channel (0-Based).
  @param[in]      Group       - DDRIO group to access.
  @param[in]      Mode        - Bit-field flags controlling Get/Set.
  @param[in,out]  Value       - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetDdrIoGroupChSch (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Channel,
  IN      UINT32        const   SubChannel,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  )
{
  return MrcGetSetDdrIoGroup (MrcData, 0, Channel, SubChannel, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, 0, DdrLevel, Group, Mode, Value);
}

/**
  Top level function used to interact with DDRIO parameters.
  The flow is as follows:
    Get the GSM_GT bit shift instruction, CR offset, and Multicasting offsets.

  @param[in]      MrcData     - Pointer to global data structure.
  @param[in]      Socket      - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]      Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]      SubChannel  - DDR SubChannel number within a Channel (0-Based).
  @param[in]      Dimm        - DIMM Number within the DDR Channel (0-based). Ignored as Rank is rank number in the channel.
  @param[in]      Rank        - Rank number within a channel (0-based).
  @param[in]      Strobe      - If Group is a CMD/CTL/CLK Index type, this is the index for that signal.  Otherwise, Dqs data group within the rank (0-based).
  @param[in]      Bit         - Bit index within the data group (0-based).
  @param[in]      FreqIndex   - Index supporting multiple operating frequencies.
  @param[in]      Level       - DDRIO level to access.
  @param[in]      Group       - DDRIO group to access.
  @param[in]      Mode        - Bit-field flags controlling Get/Set.
  @param[in,out]  Value       - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetDdrIoGroup (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Socket,
  IN      UINT32        const   Channel,
  IN      UINT32        const   SubChannel,
  IN      UINT32        const   Dimm,
  IN      UINT32        const   Rank,
  IN      UINT32        const   Strobe,
  IN      UINT32        const   Bit,
  IN      UINT32        const   FreqIndex,
  IN      GSM_LT        const   Level,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  )
{
  MrcStatus         Status;
  MrcStatus         CurrentStatus;
  MrcStatus         CacheStatus;
  INT64             CurrentVal;
  INT64             Min;
  INT64             Max;
  UINT64            RegVal;
  UINT64            NewRegVal;
  UINT32            Offset;
  UINT32            Delay;
  UINT32            SocketLoop;
  UINT32            SocketStart;
  UINT32            SocketEnd;
  UINT32            ChannelLoop;
  UINT32            ChannelStart;
  UINT32            ChannelEnd;
  UINT32            SubChLoop;
  UINT32            SubChStart;
  UINT32            SubChEnd;
  UINT32            RankLoop;
  UINT32            RankStart;
  UINT32            RankEnd;
  UINT32            StrobeLoop;
  UINT32            StrobeStart;
  UINT32            StrobeEnd;
  UINT32            BitLoop;
  UINT32            BitStart;
  UINT32            BitEnd;
  BOOLEAN           RegSize;
  BOOLEAN           ReadOnly;
  BOOLEAN           MulticastAccess;
  MRC_REGISTER_HASH_STRUCT  HashVal;
#ifdef MRC_DEBUG_PRINT
  MrcDebug      *Debug;
  INT64_STRUCT  PrintVal;
  CHAR8         Str[120];
  CHAR8         *p;
  UINT64        *Ptr;

  Debug      = &MrcData->Outputs.Debug;
#ifdef MRC_DISABLE_CACHING
  Mode &= ~GSM_CACHE_ONLY;
  Mode |= GSM_READ_CSR;
#endif
  //
  // Check that the level is supported
  //
  switch (Level) {
    case DdrLevel:
      break;

    default:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "GetSet, Level %d is not supported!\n", Level);
      return mrcWrongInputParameter;
      break;
  }

  // Check that GsmGtDebugStrings[] array is consistent with the GSM_GT enums
  Ptr = (UINT64 *) GsmGtDebugStrings[GsmGtMax];
  if ((Ptr == NULL) || (*Ptr != 0x78614d74476d7347)) { // "GsmGtMax"
    MRC_DEBUG_ASSERT (FALSE, Debug, "%s GsmGtDebugStrings[] array is not aligned with GSM_GT enums", gErrString);
  }

  //
  // Check that the Group is supported
  //
  Status = MrcCheckGroupSupported (MrcData, Group);
  if (Status != mrcSuccess) {
    return Status;
  }
#endif // MRC_DEBUG_PRINT

  ReadOnly  = (Mode & GSM_READ_ONLY) == GSM_READ_ONLY;
  Status = mrcSuccess;

  // Detect and convert all Multicast accesses into unicast.
  MulticastAccess = FALSE;
  if ((Socket != MRC_IGNORE_ARG) && (Socket >= MAX_CONTROLLERS)) {
    MulticastAccess = TRUE;
    SocketStart = 0;
    SocketEnd = MAX_CONTROLLERS - 1;
  } else {
    SocketStart = Socket;
    SocketEnd   = Socket;
  }
  if ((Channel != MRC_IGNORE_ARG) && (Channel >= MAX_CHANNEL)) {
    MulticastAccess = TRUE;
    ChannelStart  = 0;
    ChannelEnd    = MAX_CHANNEL - 1;
  } else {
    ChannelStart  = Channel;
    ChannelEnd    = Channel;
  }
  if ((SubChannel != MRC_IGNORE_ARG) && (SubChannel >= MAX_SUB_CHANNEL)) {
    MulticastAccess = TRUE;
    SubChStart  = 0;
    SubChEnd    = MrcData->Outputs.SubChCount - 1;
  } else {
    SubChStart  = SubChannel;
    SubChEnd    = SubChannel;
  }
  if ((Rank != MRC_IGNORE_ARG) && (Rank >= MAX_RANK_IN_CHANNEL)) {
    MulticastAccess = TRUE;
    RankStart = 0;
    RankEnd   = MAX_RANK_IN_CHANNEL - 1;
  } else {
    RankStart = Rank;
    RankEnd   = Rank;
  }
  if ((Strobe != MRC_IGNORE_ARG) && (Strobe >= MAX_SDRAM_IN_DIMM)) {
    MulticastAccess = TRUE;
    StrobeStart = 0;
    StrobeEnd    = MrcData->Outputs.SdramCount - 1;
  } else {
    StrobeStart = Strobe;
    StrobeEnd   = Strobe;
  }
  if ((Bit != MRC_IGNORE_ARG) && (Bit >= MAX_BITS)) {
    MulticastAccess = TRUE;
    BitStart  = 0;
    BitEnd    = MAX_BITS - 1;
  } else {
    BitStart  = Bit;
    BitEnd    = Bit;
  }

  // Break Multicast requests into multiple unicasts if it is not GSM_READ_ONLY.
  if (MulticastAccess) {
    if (ReadOnly) {
      // Ensure no one is trying to read with multicast parameters.
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Attempted to read from a Multicast. Group: %s(%d) Channel: %u, SubCh: %u, Rank: %u, Byte: %u\n",
        GsmGtDebugStrings[Group], Group, Channel, SubChannel, Rank, Strobe);
      return mrcWrongInputParameter;
    }
    MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "SocketStart: %d\tSocketEnd: %d\n", SocketStart, SocketEnd);
    MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "ChannelStart: %d\tChannelEnd: %d\n", ChannelStart, ChannelEnd);
    MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "SubChStart: %d\tSubChEnd: %d\n", SubChStart, SubChEnd);
    MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "RankStart: %d\tRankEnd: %d\n", RankStart, RankEnd);
    MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "StrobeStart: %d\tStrobeEnd: %d\n", StrobeStart, StrobeEnd);
    MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "BitStart: %d\tBitEnd: %d\n", BitStart, BitEnd);
    for (SocketLoop = SocketStart; SocketLoop <= SocketEnd; SocketLoop++) {
      for (ChannelLoop = ChannelStart; ChannelLoop <= ChannelEnd; ChannelLoop++) {
        if ((!MrcChannelExist (&MrcData->Outputs, ChannelLoop)) && (Channel != MRC_IGNORE_ARG)) {
          MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "Group %s skipped as %s %d does not exist\n", GsmGtDebugStrings[Group], gChannelStr, ChannelLoop);
          continue;
        }
        for (SubChLoop = SubChStart; SubChLoop <= SubChEnd; SubChLoop++) {
          for (RankLoop = RankStart; RankLoop <= RankEnd; RankLoop++) {
            if ((!MrcRankInChannelExist(MrcData, RankLoop, ChannelLoop)) && (Rank != MRC_IGNORE_ARG) && (Channel != MRC_IGNORE_ARG)) {
              MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "Group %s skipped as %s %d does not exist\n", GsmGtDebugStrings[Group], gRankStr, RankLoop);
              continue;
            }
            for (StrobeLoop = StrobeStart; StrobeLoop <= StrobeEnd; StrobeLoop++) {
              if ((!MrcByteInChannelExist (MrcData, ChannelLoop, StrobeLoop)) && (Strobe != MRC_IGNORE_ARG)) {
                MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "Group %s skipped as %s %d does not exist\n", GsmGtDebugStrings[Group], gByteStr, StrobeLoop);
                continue;
              }
              for (BitLoop = BitStart; BitLoop <= BitEnd; BitLoop++) {
                CurrentStatus = MrcGetSetDdrIoGroup (
                                  MrcData,
                                  SocketLoop,
                                  ChannelLoop,
                                  SubChLoop,
                                  Dimm,
                                  RankLoop,
                                  StrobeLoop,
                                  BitLoop,
                                  FreqIndex,
                                  Level,
                                  Group,
                                  Mode,
                                  Value
                                  );
                if (Status == mrcSuccess) {
                  Status = CurrentStatus;
                }
              } // BitLoop
            } // StrobeLoop
          } // RankLoop
        } // SubChLoop
      } // ChannelLoop
    } // SocketLoop
    // We stop here when breaking up multicasts.
    return Status;
  }

  if (MrcCheckComplexOrSideEffect (MrcData, Group, MRC_IS_COMPLEX)) {
    // Complex parameters will stop here.
    Status = MrcGetSetComplexParam (MrcData, Socket, Channel, SubChannel, Rank, Strobe, Bit, FreqIndex, Group, Mode, Value);
    if (Status == mrcComplexParamDone) {
      return mrcSuccess;
    }
  }

  // Get CR offset and field hash value
  if (Group < EndOfPhyMarker) {
    Status = MrcGetDdrIoHash (MrcData, Group, Socket, Channel, SubChannel, Rank, Strobe, Bit, FreqIndex, &HashVal.Data);
  } else if (Group < EndOfIocMarker) {
    Status = MrcGetDdrIoCfgHash (MrcData, Group, Socket, Channel, SubChannel, Rank, Strobe, Bit, FreqIndex, &HashVal.Data);
  } else if (Group < EndOfMctMarker) {
    Status = MrcGetMcTimingHash (MrcData, Group, Socket, Channel, FreqIndex, &HashVal.Data);
  } else {
    Status = MrcGetMcConfigHash (MrcData, Group, Socket, Channel, FreqIndex, &HashVal.Data);
  }
  if (Status != mrcSuccess) {
    return Status;
  }

  Offset = HashVal.Bits.Offset;
  RegSize = (HashVal.Bits.RegSize != 0);
#ifdef MRC_DEBUG_PRINT
  if (Offset == 0xFFFF) {
    p = Str;
    p += MrcSPrintf (MrcData, p, sizeof (Str) - (p - Str), "No Offset found for Group %s(%d)", GsmGtDebugStrings[Group], Group) - 1;
    if (Socket != MRC_IGNORE_ARG) {
      p += MrcSPrintf (MrcData, p, sizeof (Str) - (p - Str), " Socket %u,", Socket) - 1;
    }
    if (Channel != MRC_IGNORE_ARG) {
      p += MrcSPrintf (MrcData, p, sizeof (Str) - (p - Str), " Channel %u,", Channel) - 1;
    }
    if (SubChannel != MRC_IGNORE_ARG) {
      p += MrcSPrintf (MrcData, p, sizeof (Str) - (p - Str), " SubCh %u,", SubChannel) - 1;
    }
    if (Rank != MRC_IGNORE_ARG) {
      p += MrcSPrintf (MrcData, p, sizeof (Str) - (p - Str), " Rank %u,", Rank) - 1;
    }
    if (Strobe != MRC_IGNORE_ARG) {
      p += MrcSPrintf (MrcData, p, sizeof (Str) - (p - Str), " Strobe %u,", Strobe) - 1;
    }
    if (Bit != MRC_IGNORE_ARG) {
      p += MrcSPrintf (MrcData, p, sizeof (Str) - (p - Str), " Bit %u,", Bit) - 1;
    }
    if (FreqIndex != MRC_IGNORE_ARG) {
      p += MrcSPrintf (MrcData, p, sizeof (Str) - (p - Str), " FreqIndex %u", FreqIndex) - 1;
    }
    MRC_DEBUG_ASSERT (Offset != 0xFFFF, Debug, "%s\n", Str);
  }
#endif // MRC_DEBUG_PRINT
  //
  // Init data.
  //

  // Used for debug to see which GetSet groups use CR cache
  // if ((Mode & GSM_READ_CSR) == 0) {
  //   MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s - CR Cache read\n", GsmGtDebugStrings[Group]);
  // }
  // if ((Mode & GSM_UPDATE_CACHE) != 0) {
  //   MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s - CR Cache write\n", GsmGtDebugStrings[Group]);
  // }

  RegVal = MrcCrCacheRead (MrcData, Offset, RegSize, Mode, Group, Socket, Channel, Rank, Strobe, Bit);
  //
  // Get the group value
  //
  CurrentVal = MrcHalGsmGetBitField (MrcData, HashVal, RegVal);

  if (ReadOnly) {
    *Value = CurrentVal;
  } else {
    CurrentVal = ((Mode & GSM_WRITE_OFFSET) == GSM_WRITE_OFFSET) ? CurrentVal + *Value : *Value;

    //
    // Check value limits.
    //
    MrcGetSetLimits (MrcData, Group, &Min, &Max, &Delay);

    if ((CurrentVal < Min) || (CurrentVal > Max)) {
#ifdef MRC_DEBUG_PRINT
      p = Str;
      p += MrcSPrintf (MrcData, p, sizeof (Str) - (p - Str), "%s", gWarnString) - 1;
      if (Channel != MRC_IGNORE_ARG) {
        p += MrcSPrintf (MrcData, p, sizeof (Str) - (p - Str), "C%u", Channel) - 1;
      }
      if (SubChannel != MRC_IGNORE_ARG) {
        p += MrcSPrintf (MrcData, p, sizeof (Str) - (p - Str), ".Sch%u", SubChannel) - 1;
      }
      if (Rank != MRC_IGNORE_ARG) {
        p += MrcSPrintf (MrcData, p, sizeof (Str) - (p - Str), ".R%u", Rank) - 1;
      }
      if (Strobe != MRC_IGNORE_ARG) {
        p += MrcSPrintf (MrcData, p, sizeof (Str) - (p - Str), ".S%u", Strobe) - 1;
      }
      if (Bit != MRC_IGNORE_ARG) {
        p += MrcSPrintf (MrcData, p, sizeof (Str) - (p - Str), ".B%u,", Bit) - 1;
      }
      p += MrcSPrintf (MrcData, p, sizeof (Str) - (p - Str), " %s value %lld is out of range [%lld:%lld]. Clamping\n",
                       GsmGtDebugStrings[Group], CurrentVal, Min, Max) - 1;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\n", Str);
#endif // MRC_DEBUG_PRINT
      Status = mrcParamSaturation;
    }
#ifdef MRC_DEBUG_PRINT
    if (Delay != 0) {
      MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "Delay for %uus\n", Delay);
    }
#endif
    CurrentVal = RANGE (CurrentVal, Min, Max);
    //
    // Update CR with new value
    //
    NewRegVal = MrcHalGsmSetBitField (MrcData, HashVal, CurrentVal, RegVal);
    if (((Mode & GSM_FORCE_WRITE) == GSM_FORCE_WRITE) || (RegVal != NewRegVal)) {
      CacheStatus = MrcCrCacheWrite (MrcData, Offset, RegSize, Mode, Group, Socket, Channel, Rank, Strobe, Bit, Delay, NewRegVal);
      if (CacheStatus != mrcSuccess) {
        // The only reason for failure is cache full.
        // Write to the HW register in this case.
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "%s %s - CR Cache is full !\n", gWarnString, GsmGtDebugStrings[Group]);
        MrcCrCacheWrite (MrcData, Offset, RegSize, Mode | GSM_FORCE_WRITE, Group, Socket, Channel, Rank, Strobe, Bit, Delay, NewRegVal);
      }
    }
    //Update MRC Host
    if ((Mode & GSM_UPDATE_HOST) == GSM_UPDATE_HOST) {
      MrcGetSetUpdateHost (MrcData, Channel, Rank, Strobe, Bit, Group, CurrentVal);
    }
    // Check if the field written to has some side effect and resolve it.
    if (MrcCheckComplexOrSideEffect (MrcData, Group, MRC_IS_SIDE_EFFECT)) {
      MrcGetSetSideEffect (MrcData, Socket, Channel, SubChannel, Rank, Strobe, Bit, FreqIndex, Group, Mode, &CurrentVal);
    }
  }

#ifdef MRC_DEBUG_PRINT
  if (Mode & GSM_PRINT_VAL) {
    p = Str;
    PrintVal.Data = CurrentVal;
    *p++ = (ReadOnly) ? 'R' : 'W';
    *p++ = ' ';
    if (Channel != MRC_IGNORE_ARG) {
      p += MrcSPrintf (MrcData, p, sizeof (Str) - (p - Str), "C%u", Channel) - 1;
    }
    if (SubChannel != MRC_IGNORE_ARG) {
      p += MrcSPrintf (MrcData, p, sizeof (Str) - (p - Str), ".Sch%u", SubChannel) - 1;
    }
    if (Rank != MRC_IGNORE_ARG) {
      p += MrcSPrintf (MrcData, p, sizeof (Str) - (p - Str), ".R%u", Rank) - 1;
    }
    if (Strobe != MRC_IGNORE_ARG) {
      p += MrcSPrintf (MrcData, p, sizeof (Str) - (p - Str), ".S%u", Strobe) - 1;
    }
    if (Bit != MRC_IGNORE_ARG) {
      p += MrcSPrintf (MrcData, p, sizeof (Str) - (p - Str), ".B%u", Bit) - 1;
    }
    p += MrcSPrintf (MrcData, p, sizeof (Str) - (p - Str), " %s: ", GsmGtDebugStrings[Group]) - 1;
    if (HashVal.Bits.BfWidth > 32) {
      p += MrcSPrintf (MrcData, p, sizeof (Str) - (p - Str), "0x%llx", CurrentVal) - 1;
    } else {
      p += MrcSPrintf (MrcData, p, sizeof (Str) - (p - Str), "%d", PrintVal.Data32.Low) - 1;
      if ((HashVal.Bits.BfSign == 0) && (PrintVal.Data32.Low > 9)) {
        p += MrcSPrintf (MrcData, p, sizeof (Str) - (p - Str), " (0x%x)", PrintVal.Data32.Low) - 1;
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\n", Str);
  }
#endif // MRC_DEBUG_PRINT

  return Status;
}

/**
  This function returns the register limits.

  @param[in]  MrcData   - Pointer to global data.
  @param[in]  Group     - DDRIO group to access.
  @param[out] MinVal    - Return pointer for Minimum Value supported.
  @param[out] MaxVal    - Return pointer for Maximum Value supported.
  @param[out] WaitTime  - Return pointer for settle time required in microseconds.

  @retval MrcStatus - mrcSuccess if the parameter is found, otherwise mrcFail.
**/
MrcStatus
MrcGetDdrIoGroupLimits (
  IN  MrcParameters *const MrcData,
  IN  GSM_GT  const   Group,
  OUT INT64   *const  MinVal,
  OUT INT64   *const  MaxVal,
  OUT UINT32  *const  WaitTime
  )
{
  MrcStatus Status;
  MrcOutput *Outputs;
#if (defined (MRC_HAL_DEBUG) && (MRC_HAL_DEBUG == SUPPORT))
  MrcDebug  *Debug;
#endif
  INT64     Min;
  INT64     Max;
  UINT32    Wait;
  BOOLEAN   Ddr4;
  BOOLEAN   Gear2;

#if (defined (MRC_HAL_DEBUG) && (MRC_HAL_DEBUG == SUPPORT))
  Debug   = &MrcData->Outputs.Debug;
#endif
  Outputs = &MrcData->Outputs;
  Status  = mrcSuccess;
  Wait    = 0;
  Min     = MRC_INT64_MIN;
  Max     = MRC_INT64_MAX;
  Ddr4    = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

  Gear2 = Outputs->Gear2;
  if ((Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) && Outputs->Frequency == f1067) {
    Gear2 = FALSE;
  }

  switch (Group) {
    case RecEnDelay:
      Min = DDRDATA0CH0_CR_RXCONTROL0RANK0_RxRcvEnPi_MIN;
      Max = DDRDATA0CH0_CR_RXCONTROL0RANK0_RxRcvEnPi_MAX;
      break;

    case RxDqsNDelay:
      Min = DDRDATA0CH0_CR_RXCONTROL0RANK0_RxDqsPPi_MIN;
      Max = (Gear2) ? DDRDATA0CH0_CR_RXCONTROL0RANK0_RxDqsPPi_MAX : (DDRDATA0CH0_CR_RXCONTROL0RANK0_RxDqsPPi_MAX - 1) / 2;
      break;

    case RxDqsPDelay:
      Min = DDRDATA0CH0_CR_RXCONTROL0RANK0_RxDqsNPi_MIN;
      Max = (Gear2) ? DDRDATA0CH0_CR_RXCONTROL0RANK0_RxDqsNPi_MAX : (DDRDATA0CH0_CR_RXCONTROL0RANK0_RxDqsNPi_MAX - 1) / 2;
      break;

    case RxVref:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL5_RxVref_MIN;
      Max = 191; // DDRDATA0CH0_CR_DDRCRDATACONTROL5_RxVref_MAX is 255, but max valid value is 191
      break;

    case RxVoc:
      // DDR4 uses N-path, so the range is [0..15]
      // LP4 (P-Path) range is [0..31]
      Min = DDRDATA0CH0_CR_RXCONTROL2RANK0_Lane0RxOffsetVDq_MIN;
      Max = (Ddr4) ? 15 : DDRDATA0CH0_CR_RXCONTROL2RANK0_Lane0RxOffsetVDq_MAX;
      break;

    case RxEq:
      Min = DDRDATA0CH0_CR_RXCONTROL0RANK0_RxEq_MIN;
      Max = DDRDATA0CH0_CR_RXCONTROL0RANK0_RxEq_MAX;
      break;

    case RxDqBitDelay:
      Min = DDRDATA0CH0_CR_RXCONTROL1RANK0_Lane0PerBitDeskew_MIN;
      Max = DDRDATA0CH0_CR_RXCONTROL1RANK0_Lane0PerBitDeskew_MAX;
      break;

    case RxRankMuxDelay:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL2_RxRankMuxDelay_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL2_RxRankMuxDelay_MAX;
      break;

    case TxDqsDelay:
      Min = DDRDATA0CH0_CR_TXTRAINRANK0_TxDqsDelay_MIN;
      Max = DDRDATA0CH0_CR_TXTRAINRANK0_TxDqsDelay_MAX;
      break;

    case TxDqDelay:
      Min = DDRDATA0CH0_CR_TXTRAINRANK0_TxDqDelay_MIN;
      Max = DDRDATA0CH0_CR_TXTRAINRANK0_TxDqDelay_MAX;
      break;

    case TxEq:
      Min = DDRDATA0CH0_CR_TXTRAINRANK0_TxEqualization_MIN;
      Max = DDRDATA0CH0_CR_TXTRAINRANK0_TxEqualization_MAX;
      break;

    case TxRankMuxDelay:
      Min = DDRDATA0CH0_CR_TXTRAINRANK0_TxRankMuxDelay_MIN;
      Max = DDRDATA0CH0_CR_TXTRAINRANK0_TxRankMuxDelay_MAX;
      break;

    case TxDqsRankMuxDelay:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL3_TxDqsRankMuxDelay_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL3_TxDqsRankMuxDelay_MAX;
      break;

    case TxDqBitDelay:
      Min = DDRDATA0CH0_CR_TXPERBITLOWRANK0_Lane0_MIN;
      Max = DDRDATA0CH0_CR_TXPERBITLOWRANK0_Lane0_MAX;
      break;

    case RecEnOffset:
      Min = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_MAX;
      break;

    case RxDqsOffset:
      Min = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_MIN;
      Max = (Gear2) ? DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_MAX : (DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_MAX - 1) / 2;
      break;

    case RxVrefOffset:
      Min = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_MAX;
      break;

    case TxDqsOffset:
      Min = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_MAX;
      break;

    case TxDqOffset:
      Min = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_MAX;
      break;

    case RoundTripDelay:
      Min = CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_0_latency_MIN;
      Max = CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_0_latency_MAX;
      break;

    case RxFlybyDelay:
      Min = MCMISCS_READCFGCHACHB0_RcvEnRank0ChADel_MIN;
      Max = MCMISCS_READCFGCHACHB0_RcvEnRank0ChADel_MAX;
      break;

    case RxIoTclDelay:
      Min = MCMISCS_READCFGCH0_tCL4RcvEn_MIN;
      Max = MCMISCS_READCFGCH0_tCL4RcvEn_MAX;
      break;

    case RxFifoRdEnFlybyDelay:
      Min = MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank0ChADel_MIN;
      Max = (Gear2) ? (MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank0ChADel_MAX - 1) / 2 : MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank0ChADel_MAX;
      break;

    case RxFifoRdEnTclDelay:
      Min = MCMISCS_READCFGCH0_tCL4RxDqFifoRdEn_MIN;
      Max = MCMISCS_READCFGCH0_tCL4RxDqFifoRdEn_MAX;
      break;

    case RxDqDataValidDclkDelay:
      Min = MCMISCS_READCFGCH0_RxDqDataValidDclkDel_MIN;
      Max = MCMISCS_READCFGCH0_RxDqDataValidDclkDel_MAX;
      break;

    // @todo: BOOLEAN case.  If more 1-bit field are added: consolidate.
    case RxDqDataValidQclkDelay:
      Min = MCMISCS_READCFGCH0_RxDqDataValidQclkDel_MIN;
      Max = MCMISCS_READCFGCH0_RxDqDataValidQclkDel_MAX;
      break;

    case TxDqFifoWrEnTcwlDelay:
      Min = MCMISCS_WRITECFGCH0_tCWL4TxDqFifoWrEn_MIN;
      Max = MCMISCS_WRITECFGCH0_tCWL4TxDqFifoWrEn_MAX;
      break;

    case TxDqFifoRdEnTcwlDelay:
      Min = MCMISCS_WRITECFGCH0_tCWL4TxDqFifoRdEn_MIN;
      Max = MCMISCS_WRITECFGCH0_tCWL4TxDqFifoRdEn_MAX;
      break;

    case TxDqFifoRdEnFlybyDelay:
      Min = MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank0ChADel_MIN;
      Max = MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank0ChADel_MAX;
      break;

    case CmdVref:
    case TxVref:        // @todo Can remove when ICL A0 support is dropped
      Min = DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm0CaVrefIntCtl_MIN;
      Max = 383;  // DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm0CaVrefIntCtl_MAX is 511, but max valid value is 383
      break;

    case SenseAmpDelay:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_MAX;
      break;

    case SenseAmpDuration:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_MAX;
      break;

    case McOdtDelay:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL1_OdtDelay_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL1_OdtDelay_MAX;
      break;

    case McOdtDuration:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL1_OdtDuration_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL1_OdtDuration_MAX;
      break;

    case McDqsOdtDelay:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL3_DqsOdtDelay_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL3_DqsOdtDelay_MAX;
      break;

    case McDqsOdtDuration:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL3_DqsOdtDuration_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL3_DqsOdtDuration_MAX;
      break;

    case DqDfeDelayMode:
      Min = DDRDATA0CH0_CR_DDRCRDATADFECONTROL1RANK01_DfeDlyModeRank0_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATADFECONTROL1RANK01_DfeDlyModeRank0_MAX;
      break;

    case DqDfeCoeff:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL8_DqDfeCoeffRank0_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL8_DqDfeCoeffRank0_MAX;
      break;

    case DqDfeDelay:
      Min = DDRDATA0CH0_CR_RXCONTROL1RANK0_DqDfeDlyBit0_MIN;
      Max = DDRDATA0CH0_CR_RXCONTROL1RANK0_DqDfeDlyBit0_MAX;
      break;


    case RxBiasIComp:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL1_RxBiasCtl_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL1_RxBiasCtl_MAX;
      break;

    case RxBiasRComp: // Combination of DataControl4.biasrcomp[2:0] and DataControl6.RxBiasCtl.Bit1[3]
      Min = 0;
      Max = 15;
      break;

    case RxBiasRCompLsb:     ///< LSB of GsmIocRxBiasRcomp [2:0]
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL4_biasrcomp_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL4_biasrcomp_MAX;
      break;

    case RxDqsAmpOffset:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL6_RxDqsAmpOffset_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL6_RxDqsAmpOffset_MAX;
      break;

    case SdllPiCb:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL6_sdll_picb_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL6_sdll_picb_MAX;
      break;

    case D0PiCb:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL6_d0_picb_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL6_d0_picb_MAX;
      break;

    case SdllBwCtrl:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL7_sdll_bw_ctrl_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL7_sdll_bw_ctrl_MAX;
      break;

    case D0BwCtrl:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL7_d0_bw_ctrl_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL7_d0_bw_ctrl_MAX;
      break;

    case RxCben:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL2_Cben_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL2_Cben_MAX;
      break;

    case CBEnAmp1:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL3_CBEnAmp1_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL3_CBEnAmp1_MAX;
      break;

    case CtlGrpPi:
    case ClkGrpPi:
    case CmdGrpPi:
    case CkeGrpPi:
      Min = DDRCMDBCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MIN;
      Max = DDRCMDBCH0_CR_DDRCRCMDPICODING_CmdPi0Code_MAX;
      break;

    case TxSlewRate:
    case CmdSlewRate:
    case CtlSlewRate:
    case ClkSlewRate:
      Min = DDRPHY_COMP_CR_DDRCRCOMPCTL1_DqScompCells_MIN;
      Max = DDRPHY_COMP_CR_DDRCRCOMPCTL1_DqScompCells_MAX;
      break;

    case DqRcompStatLegs:
      Min = DDRPHY_COMP_CR_DDRCRCOMPCTL1_DqRcompStatLegs_MIN;
      Max = DDRPHY_COMP_CR_DDRCRCOMPCTL1_DqRcompStatLegs_MAX;
      break;

    case SCompCodeDq:
    case SCompCodeClk:
      Min = DDRDATA0CH0_CR_RCOMPDATA0_SlewRateComp_MIN;
      Max = DDRDATA0CH0_CR_RCOMPDATA0_SlewRateComp_MAX;
      break;

    case SCompCodeCmd:
    case SCompCodeCtl:
    case TxRonUp:
    case WrDSCodeUpCmd:
    case WrDSCodeUpCtl:
    case WrDSCodeUpClk:
    case TxRonDn:
    case WrDSCodeDnCmd:
    case WrDSCodeDnCtl:
    case WrDSCodeDnClk:
      Min = DDRDATA0CH0_CR_RCOMPDATA0_RcompDrvUp_MIN;
      Max = DDRDATA0CH0_CR_RCOMPDATA0_RcompDrvUp_MAX;
      break;

    case TxTco:
    case TcoCompCodeCmd:
    case TcoCompCodeCtl:
    case TcoCompCodeClk:
      Min = DDRDATA0CH0_CR_DDRCRDATATCOCONTROL0_DqsNTcoComp_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATATCOCONTROL0_DqsNTcoComp_MAX;
      break;

    case TxTcoDqsN:
    case TxTcoDqsP:
      Min = DDRDATA0CH0_CR_DDRCRDATATCOCONTROL1_DqsPTcoComp_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATATCOCONTROL1_DqsPTcoComp_MAX;
      break;

    case DqOdtVref:
      Min = DDRPHY_COMP_CR_DDRCRCOMPCTL0_DqOdtVref_MIN;
      Max = DDRPHY_COMP_CR_DDRCRCOMPCTL0_DqOdtVref_MAX;
      break;

    case DqDrvVref:
      Min = DDRPHY_COMP_CR_DDRCRCOMPCTL0_DqDrvVref_MIN;
      Max = DDRPHY_COMP_CR_DDRCRCOMPCTL0_DqDrvVref_MAX;
      break;

    case CmdDrvVref:
      Min = DDRPHY_COMP_CR_DDRCRCOMPCTL3_CmdDrvVref_MIN;
      Max = DDRPHY_COMP_CR_DDRCRCOMPCTL3_CmdDrvVref_MAX;
      break;

    case CmdTxEq:
      Min = DDRCMDACH0_CR_DDRCRCMDCONTROLS_CmdTxEq_MIN;
      Max = DDRCMDACH0_CR_DDRCRCMDCONTROLS_CmdTxEq_MAX;
      break;

    case CtlDrvVref:
      Min = DDRPHY_COMP_CR_DDRCRCOMPCTL3_CtlDrvVref_MIN;
      Max = DDRPHY_COMP_CR_DDRCRCOMPCTL3_CtlDrvVref_MAX;
      break;

    case ClkDrvVref:
      Min = DDRPHY_COMP_CR_DDRCRCOMPCTL3_ClkDrvVref_MIN;
      Max = DDRPHY_COMP_CR_DDRCRCOMPCTL3_ClkDrvVref_MAX;
      break;

    case CompRcompOdtUp:
    case CompRcompOdtDn:
      Min = DDRDATA0CH0_CR_RCOMPDATA1_RcompOdtUp_MIN;
      Max = DDRDATA0CH0_CR_RCOMPDATA1_RcompOdtUp_MAX;
      break;

    case CtlSCompOffset:
    case CmdSCompOffset:
    case CkeSCompOffset:
      Min = DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MIN;
      Max = DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_MAX;
      break;

    case CtlRCompDrvUpOffset:
    case CtlRCompDrvDownOffset:
    case CmdRCompDrvUpOffset:
    case CmdRCompDrvDownOffset:
    case CkeRCompDrvDownOffset:
    case CkeRCompDrvUpOffset:
      Min = DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MIN;
      Max = DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_MAX;
      break;

    case ClkCompOnTheFlyUpdtEn:
      Min = DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_ClkCompOnTheFlyUpdtEn_MIN;
      Max = DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_ClkCompOnTheFlyUpdtEn_MAX;
      break;

    case ClkRCompDrvDownOffset:
      Min = DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_RcompDrvDownOffset_MIN;
      Max = DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_RcompDrvDownOffset_MAX;
      break;

    case ClkRCompDrvUpOffset:
      Min = DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_RcompDrvUpOffset_MIN;
      Max = DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_RcompDrvUpOffset_MAX;
      break;

    case ClkSCompOffset:
      Min = DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_ScompOffset_MIN;
      Max = DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_ScompOffset_MAX;
      break;

    // Binary Max/Min
    case TxTcoByPass:
    case DqScompPC:
    case CmdScompPC:
    case CtlScompPC:
    case ClkScompPC:
    case DqDfeEnable:
    case RxBiasRCompMsb:     ///< MSB of GsmIocRxBiasRcomp [3]
      Min = 0;
      Max = 1;
      break;

    default:
      MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "Group %s(%d) has no limits defined\n", GsmGtDebugStrings[Group], Group);
      Status = mrcWrongInputParameter;
      break;
  }

  // Null guard the pointers
  if (MinVal != NULL) {
    *MinVal = Min;
  }
  if (MaxVal != NULL) {
    *MaxVal = Max;
  }
  if (WaitTime != NULL) {
    *WaitTime = Wait;
  }

  return Status;
}

/**
  This function returns complex group limits.

  @param[in]  MrcData   - Pointer to global data.
  @param[in]  Group     - Complex group to access.
  @param[out] MinVal    - Return pointer for Minimum Value supported.
  @param[out] MaxVal    - Return pointer for Maximum Value supported.
  @param[out] WaitTime  - Return pointer for settle time required in microseconds.

  @retval MrcStatus - mrcSuccess if the parameter is found, otherwise mrcFail.
**/
MrcStatus
MrcGetComplexGroupLimits (
  IN  MrcParameters *const  MrcData,
  IN  UINT32        const   Group,
  OUT INT64         *const  MinVal,
  OUT INT64         *const  MaxVal,
  OUT UINT32        *const  WaitTime
  )
{
  MrcStatus Status;
#if (defined (MRC_HAL_DEBUG) && (MRC_HAL_DEBUG == SUPPORT))
  MrcDebug  *Debug;
#endif
  INT64     Min;
  INT64     Max;
  UINT32    Wait;

#if (defined (MRC_HAL_DEBUG) && (MRC_HAL_DEBUG == SUPPORT))
  Debug   = &MrcData->Outputs.Debug;
#endif
  Status  = mrcSuccess;
  Wait    = 0;
  Min     = MRC_INT64_MIN;
  Max     = MRC_INT64_MAX;

  switch (Group) {
    case GsmComplexRxBias:
      Min = 0;
      Max = DDRDATA_CR_DDRCRDATACONTROL1_RxBiasCtl_MAX;
    break;

    default:
      MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "Group %s(%d) has no limits defined\n", GsmGtDebugStrings[Group], Group);
      Status = mrcWrongInputParameter;
      break;
  }

  // Null guard the pointers
  if (MinVal != NULL) {
    *MinVal = Min;
  }
  if (MaxVal != NULL) {
    *MaxVal = Max;
  }
  if (WaitTime != NULL) {
    *WaitTime = Wait;
  }

  return Status;
}

/**
  This function returns DDRIO Configuration group limits.

  @param[in]  MrcData   - Pointer to global data.
  @param[in]  Group     - DDRIO group to access.
  @param[out] MinVal    - Return pointer for Minimum Value supported.
  @param[out] MaxVal    - Return pointer for Maximum Value supported.
  @param[out] WaitTime  - Return pointer for settle time required in microseconds.

  @retval MrcStatus - mrcSuccess if the parameter is found, otherwise mrcFail.
**/
MrcStatus
MrcGetDdrIoCfgGroupLimits (
  IN  MrcParameters *const  MrcData,
  IN  UINT32        const   Group,
  OUT INT64         *const  MinVal,
  OUT INT64         *const  MaxVal,
  OUT UINT32        *const  WaitTime
  )
{
  MrcStatus Status;
#if (defined (MRC_HAL_DEBUG) && (MRC_HAL_DEBUG == SUPPORT))
  MrcDebug  *Debug;
#endif
  INT64     Min;
  INT64     Max;
  UINT32    Wait;

#if (defined (MRC_HAL_DEBUG) && (MRC_HAL_DEBUG == SUPPORT))
  Debug   = &MrcData->Outputs.Debug;
#endif
  Status  = mrcSuccess;
  Wait    = 0;
  Min     = MRC_INT64_MIN;
  Max     = MRC_INT64_MAX;

  switch (Group) {
    case GsmIocWlWakeCyc:
      Min = DDRSCRAM_CR_DDRMISCCONTROL0_WL_WakeCycles_MIN;
      Max = DDRSCRAM_CR_DDRMISCCONTROL0_WL_WakeCycles_MAX;
      break;

    case GsmIocWlSleepCyc:
      Min = DDRSCRAM_CR_DDRMISCCONTROL0_WL_SleepCycles_MIN;
      Max = DDRSCRAM_CR_DDRMISCCONTROL0_WL_SleepCycles_MAX;
      break;

    case GsmIocWlLatency:
      Min = DDRSCRAM_CR_DDRMISCCONTROL0_WeakLock_Latency_MIN;
      Max = DDRSCRAM_CR_DDRMISCCONTROL0_WeakLock_Latency_MAX;
      break;

    case GsmIocLpRcvenCtrl:
      Min = DDRSCRAM_CR_DDRMISCCONTROL0_lp4_rcven_ctrl_MIN;
      Max = DDRSCRAM_CR_DDRMISCCONTROL0_lp4_rcven_ctrl_MAX;
      break;

    case GsmIocChNotPop:
      Min = DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_MIN;
      Max = DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_MAX;
      break;

    case GsmIocStrongWeakLeaker:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL3_StrongWkLeaker_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL3_StrongWkLeaker_MAX;
      break;

    case GsmIocStrongWeakLeakerMsb:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL6_strongwkleakermsb_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL6_strongwkleakermsb_MAX;
      break;

    case GsmIocRxClkStg:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL2_RxClkStgNum_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL2_RxClkStgNum_MAX;
      break;

    case GsmIocLeakerComp:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL3_LeakerComp_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL3_LeakerComp_MAX;
      break;

    case GsmIocRxStaggerCtl:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL2_RxStaggerCtl_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL2_RxStaggerCtl_MAX;
      break;

    case GsmIocDllMask:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL1_DllMask_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL1_DllMask_MAX;
      break;

    case GsmIocSdllSegmentDisable:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_MAX;
      break;

    case GsmIocDqOdtUpDnOff:
      Min = DDRPHY_COMP_CR_DDRCRCOMPCTL0_DqOdtUpDnOff_MIN;
      Max = DDRPHY_COMP_CR_DDRCRCOMPCTL0_DqOdtUpDnOff_MAX;
      break;

    case GsmIocPanicDrvUpVref:
      Min = DDRPHY_COMP_CR_DDRCRCOMPCTL2_PanicDrvUpVref_MIN;
      Max = DDRPHY_COMP_CR_DDRCRCOMPCTL2_PanicDrvUpVref_MAX;
      break;

    case GsmIocCmdDrvVref200ohm:
      Min = DDRDATA0CH0_CR_RCOMPDATA2_RcompCmdDn200ohm_MIN;
      Max = DDRDATA0CH0_CR_RCOMPDATA2_RcompCmdDn200ohm_MAX;
      break;

    case GsmIocVttPanicCompUpMult:
      Min = DDRPHY_COMP_CR_DDRCRCOMPCTL2_VttPanicCompUpMult_MIN;
      Max = DDRPHY_COMP_CR_DDRCRCOMPCTL2_VttPanicCompUpMult_MAX;
      break;

    case GsmIocVttPanicCompDnMult:
      Min = DDRPHY_COMP_CR_DDRCRCOMPCTL2_VttPanicCompDnMult_MIN;
      Max = DDRPHY_COMP_CR_DDRCRCOMPCTL2_VttPanicCompDnMult_MAX;
      break;

    case GsmIocOdtOverride:
    case GsmIocOdtOn:
      Min = CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_Override_MIN;
      Max = CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_Override_MAX;
      break;

    case GsmIocCkeOverride:
    case GsmIocCkeOn:
      Min = CH0_CR_REUT_CH_MISC_CKE_CTRL_CKE_Override_MIN;
      Max = CH0_CR_REUT_CH_MISC_CKE_CTRL_CKE_Override_MAX;
      break;

    case GsmIocCmdAnlgEnGraceCnt:
      Min = MCMISCS_WRITECFGCH0_CmdAnlgEnGraceCnt_MIN;
      Max = MCMISCS_WRITECFGCH0_CmdAnlgEnGraceCnt_MAX;
      break;

    case GsmIocTxAnlgEnGraceCnt:
      Min = MCMISCS_WRITECFGCH0_TxAnlgEnGraceCnt_MIN;
      Max = MCMISCS_WRITECFGCH0_TxAnlgEnGraceCnt_MAX;
      break;

    case GsmIocLp4DqsMaskPulseCnt:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL5_ddrcrmaskcntpulsenumstart_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL5_ddrcrmaskcntpulsenumstart_MAX;
      break;

    case GsmIocLp4DqsPulseCnt:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL5_ddrcrnumofpulses_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL5_ddrcrnumofpulses_MAX;
      break;

    case GsmIocLp4DqOverrideData:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL5_DdrDqOvrdData_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL5_DdrDqOvrdData_MAX;
      break;

    case GsmIocLp4DqOverrideEn:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL5_DdrDqOvrdModeEn_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL5_DdrDqOvrdModeEn_MAX;
      break;

    case GsmIocRankOverrideVal:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL6_RankValue_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL6_RankValue_MAX;
      break;

    case GsmIocRxDeskewCal:
    case GsmIocTxDeskewCal:
      Min = DDRDATACH0_CR_DDRCRDATACONTROL4_rxdeskewcal_MIN;
      Max = DDRDATACH0_CR_DDRCRDATACONTROL4_rxdeskewcal_MAX;
      break;

    case GsmIocDccActiveClks:
      Min = MCMISCS_DCCMAINFSMCONTROL0_ActiveClks_MIN;
      Max = MCMISCS_DCCMAINFSMCONTROL0_ActiveClks_MAX;
      break;

    case GsmIocDccActiveBytes:
      Min = MCMISCS_DCCMAINFSMCONTROL0_ActiveBytes_MIN;
      Max = MCMISCS_DCCMAINFSMCONTROL0_ActiveBytes_MAX;
      break;

    case GsmIocDccClkTrainVal:
      Min = DDRCLKCH0_CR_DCCCLKTRAINVAL0_Clk0DccVal_MIN;
      Max = DDRCLKCH0_CR_DCCCLKTRAINVAL0_Clk0DccVal_MAX;
      break;

    case GsmIocDccDataTrainDqsVal:
      Min = DDRDATA0CH0_CR_DCCDATATRAINVAL1RANK0_DqsDccVal_MIN;
      Max = DDRDATA0CH0_CR_DCCDATATRAINVAL1RANK0_DqsDccVal_MAX;
      break;

    case GsmIocDccDqsReplica:
      Min = DDRDATA0CH0_CR_DCCDATATRAINVAL1RANK0_ReplicaShadowDccVal_MIN;
      Max = DDRDATA0CH0_CR_DCCDATATRAINVAL1RANK0_ReplicaShadowDccVal_MAX;
      break;

    case GsmIocDccAipCb:
      Min = DDRCLKCH0_CR_DCCCLKTRAINVAL0_Rank1DccAipCb_MIN;
      Max = DDRCLKCH0_CR_DCCCLKTRAINVAL0_Rank1DccAipCb_MAX;
      break;

    case GsmIocDccAipCbDqs:
      Min = DDRDATA0CH0_CR_DCCDATATRAINVAL1RANK0_DqsDccAipCb_MIN;
      Max = DDRDATA0CH0_CR_DCCDATATRAINVAL1RANK0_DqsDccAipCb_MAX;
      break;

    case GsmIocXoverMinDelayCtl:
      Min = DDRDATA0CH0_CR_DDRCRDATACONTROL0_xover_mindelay_ctl_MIN;
      Max = DDRDATA0CH0_CR_DDRCRDATACONTROL0_xover_mindelay_ctl_MAX;
      break;

    // Binary Max/Min
    case GsmIocIoReset:
    case GsmIocForceCmpUpdt:
    case GsmIocScramLp4Mode:
    case GsmIocScramDdr4Mode:
    case GsmIocDdrCentric:
    case GsmIocScramGear1:
    case GsmIoc4ChMode:
    case GsmIocDisDataIdlClkGate:
    case GsmIocDllWlEn:
    case GsmIocDisClkGate:
    case GsmIocDisIosfSbClkGate:
    case GsmIocEccEn:
    case GsmIocScramLpMode:
    case GsmIocNoDqInterleave:
    case GsmIocVrefPwrDnEn:
    case GsmIocDataCtlDdr4Mode:
    case GsmIocRxDeskewDis:
    case GsmIocTxDeskewDis:
    case GsmIocDataVddqOdtEn:
    case GsmIocDataVttOdtEn:
    case GsmIocCompVddqOdtEn:
    case GsmIocCompVttOdtEn:
    case GsmIocLpLongOdtEn:
    case GsmIocRxVrefMFC:
    case GsmIocReadDqDqsMode:
    case GsmIocSenseAmpMode:
    case GsmIocReadLevelMode:
    case GsmIocWriteLevelMode:
    case GsmIocForceOdtOn:
    case GsmIocTxOn:
    case GsmIocOdtSampExtEn:
    case GsmIocDqsOdtSampExtEn:
    case GsmIocRxPiPwrDnDis:
    case GsmIocTxPiPwrDnDis:
    case GsmIocInternalClocksOn:
    case GsmIocTxDisable:
    case GsmIocDataOdtStaticDis:
    case GsmIocCompOdtStaticDis:
    case GsmIocVssOdtEn:
    case GsmIocGlobalClkEn:
    case GsmIocRxTypeSelect:
    case GsmIocDataCtlLp4Mode:
    case GsmIocDataCtlLpMode:
    case GsmIocLowSupEnDqDqs:
    case GsmIocLp4DqsPulseEn:
    case GsmIocLongWrPreambleLp4:
    case GsmIocRxBiasSel:
    case GsmIocTxVrefConverge:  // @todo Can remove when ICL A0 support is dropped
    case GsmIocCmdVrefConverge:
    case GsmIocLpEarlyRLeak:
    case GsmIocConstZTxEqEn:
    case GsmIocCompClkOn:
    case GsmIocCompVccddqLo:
    case GsmIocDisableQuickComp:
    case GsmIocSinStep:
    case GsmIocSinStepAdv:
    case GsmIocDllWeakLock:
    case GsmIocTxEqDis:
    case GsmIocForceBiasOn:
    case GsmIocForceRxAmpOn:
    case GsmIocLp4ForceDqsPOn:
    case GsmIocLp4ForceDqsNOn:
    case GsmIocLp4ForceDqsPOnWithLeaker:
    case GsmIocLp4ForceDqsNOnWithLeaker:
    case GsmIocLeakerWithTxAnalogEn:
    case GsmIocStrong2WeakOnDqsOdt:
    case GsmIocForceDqsOnQuickOdtOff:
    case GsmIocDqSlewDlyByPass:
    case GsmIocWlLongDelEn:
    case GsmIocFixOdtD:
    case GsmIocMprTrainDdrOn:
    case GsmIocTxDqFifoRdEnPerRankDelDis:
    case GsmIocRptChRepClkOn:
    case GsmIocRankOverrideEn:
    case GsmIocDataCtlGear1:
    case GsmIocDccDcoCompEn:
    case GsmIocDccPeriodicDis:
    case GsmIocDccDcoLfsrDis:
    case GsmIocDccTrainingMode:
    case GsmIocDccTrainingDone:
    case GsmIocDccDrain:
    case GsmIocRcvenFourCycleFill:
    case GsmIocEnRcvenPreZeroFill:
    case GsmIocRxClkStgNumMsb:
      Min = 0;
      Max = 1;
      break;

    default:
    MRC_HAL_DEBUG_MSG (Debug, MSG_LEVEL_HAL, "Group %s(%d) has no limits defined\n", GsmGtDebugStrings[Group], Group);
      Status = mrcWrongInputParameter;
      break;
  }

  // Null guard the pointers
  if (MinVal != NULL) {
    *MinVal = Min;
  }
  if (MaxVal != NULL) {
    *MaxVal = Max;
  }
  if (WaitTime != NULL) {
    *WaitTime = Wait;
  }

  return Status;
}

/**
  This function returns MC Timing group limits.

  @param[in]  MrcData   - Pointer to global data.
  @param[in]  Group     - DDRIO group to access.
  @param[out] MinVal    - Return pointer for Minimum Value supported.
  @param[out] MaxVal    - Return pointer for Maximum Value supported.
  @param[out] WaitTime  - Return pointer for settle time required in microseconds.

  @retval MrcStatus - mrcSuccess if the parameter is found, otherwise mrcFail.
**/
MrcStatus
MrcGetMcTimingGroupLimits (
  IN  MrcParameters *const MrcData,
  IN  GSM_GT  const   Group,
  OUT INT64   *const  MinVal,
  OUT INT64   *const  MaxVal,
  OUT UINT32  *const  WaitTime
  )
{
  MrcStatus Status;
  MrcDebug  *Debug;
  INT64     Max;
  INT64     Min;
  UINT32    Wait;

  Debug   = &MrcData->Outputs.Debug;
  Status  = mrcSuccess;
  Wait    = 0;
  Min     = MRC_INT64_MIN;
  Max     = MRC_INT64_MAX;

  switch (Group) {
    case GsmMctRP:
      Min = CH0_CR_TC_PRE_tRP_MIN;
      Max = CH0_CR_TC_PRE_tRP_MAX;
      break;

    case GsmMctRCDwr:
      Min = CH0_CR_TC_ACT_tRCD_wr_MIN;
      Max = CH0_CR_TC_ACT_tRCD_wr_MAX;
      break;

    case GsmMctRFCpb:
      Min = CH0_CR_SC_PBR_tRFCpb_MIN;
      Max = CH0_CR_SC_PBR_tRFCpb_MAX;
      break;

    case GsmMctRPabExt:
      Min = CH0_CR_TC_PRE_tRPab_ext_MIN;
      Max = 6;
      break;

    case GsmMctRAS:
      Min = CH0_CR_TC_PRE_tRAS_MIN;
      Max = CH0_CR_TC_PRE_tRAS_MAX;
      break;

    case GsmMctRDPRE:
      Min = CH0_CR_TC_PRE_tRDPRE_MIN;
      Max = CH0_CR_TC_PRE_tRDPRE_MAX;
      break;

    case GsmMctPPD:
      Min = CH0_CR_TC_PRE_tPPD_MIN;
      Max = CH0_CR_TC_PRE_tPPD_MAX;
      break;

    case GsmMctWRPRE:
      Min = CH0_CR_TC_PRE_tWRPRE_MIN;
      Max = CH0_CR_TC_PRE_tWRPRE_MAX;
      break;

    case GsmMctFAW:
      Min = CH0_CR_TC_ACT_tFAW_MIN;
      Max = CH0_CR_TC_ACT_tFAW_MAX;
      break;

    case GsmMctRRDsg:
      Min = CH0_CR_TC_ACT_tRRD_sg_MIN;
      Max = CH0_CR_TC_ACT_tRRD_sg_MAX;
      break;

    case GsmMctRRDdg:
      Min = CH0_CR_TC_ACT_tRRD_dg_MIN;
      Max = CH0_CR_TC_ACT_tRRD_dg_MAX;
      break;

    case GsmMctLpDeratingExt:
      Min = CH0_CR_TC_ACT_derating_ext_MIN;
      Max = CH0_CR_TC_ACT_derating_ext_MAX;
      break;

    case GsmMctRDRDsg:
      Min = CH0_CR_TC_RDRD_tRDRD_sg_MIN;
      Max = CH0_CR_TC_RDRD_tRDRD_sg_MAX;
      break;

    case GsmMctRDRDdg:
      Min = CH0_CR_TC_RDRD_tRDRD_dg_MIN;
      Max = CH0_CR_TC_RDRD_tRDRD_dg_MAX;
      break;

    case GsmMctRDRDdr:
      Min = CH0_CR_TC_RDRD_tRDRD_dr_MIN;
      Max = CH0_CR_TC_RDRD_tRDRD_dr_MAX;
      break;

    case GsmMctRDRDdd:
      Min = CH0_CR_TC_RDRD_tRDRD_dd_MIN;
      Max = CH0_CR_TC_RDRD_tRDRD_dd_MAX;
      break;

    case GsmMctRDWRsg:
      Min = CH0_CR_TC_RDWR_tRDWR_sg_MIN;
      Max = CH0_CR_TC_RDWR_tRDWR_sg_MAX;
      break;

    case GsmMctRDWRdg:
      Min = CH0_CR_TC_RDWR_tRDWR_dg_MIN;
      Max = CH0_CR_TC_RDWR_tRDWR_dg_MAX;
      break;

    case GsmMctRDWRdr:
      Min = CH0_CR_TC_RDWR_tRDWR_dr_MIN;
      Max = CH0_CR_TC_RDWR_tRDWR_dr_MAX;
      break;

    case GsmMctRDWRdd:
      Min = CH0_CR_TC_RDWR_tRDWR_dd_MIN;
      Max = CH0_CR_TC_RDWR_tRDWR_dd_MAX;
      break;

    case GsmMctWRRDsg:
      Min = CH0_CR_TC_WRRD_tWRRD_sg_MIN;
      Max = CH0_CR_TC_WRRD_tWRRD_sg_MAX;
      break;

    case GsmMctWRRDdg:
      Min = CH0_CR_TC_WRRD_tWRRD_dg_MIN;
      Max = CH0_CR_TC_WRRD_tWRRD_dg_MAX;
      break;

    case GsmMctWRRDdr:
      Min = CH0_CR_TC_WRRD_tWRRD_dr_MIN;
      Max = CH0_CR_TC_WRRD_tWRRD_dr_MAX;
      break;

    case GsmMctWRRDdd:
      Min = CH0_CR_TC_WRRD_tWRRD_dd_MIN;
      Max = CH0_CR_TC_WRRD_tWRRD_dd_MAX;
      break;

    case GsmMctWRWRsg:
      Min = CH0_CR_TC_WRWR_tWRWR_sg_MIN;
      Max = CH0_CR_TC_WRWR_tWRWR_sg_MAX;
      break;

    case GsmMctWRWRdg:
      Min = CH0_CR_TC_WRWR_tWRWR_dg_MIN;
      Max = CH0_CR_TC_WRWR_tWRWR_dg_MAX;
      break;

    case GsmMctWRWRdr:
      Min = CH0_CR_TC_WRWR_tWRWR_dr_MIN;
      Max = CH0_CR_TC_WRWR_tWRWR_dr_MAX;
      break;

    case GsmMctWRWRdd:
      Min = CH0_CR_TC_WRWR_tWRWR_dd_MIN;
      Max = CH0_CR_TC_WRWR_tWRWR_dd_MAX;
      break;

    case GsmMctOdtRdDuration:
      Min = CH0_CR_TC_ODT_ODT_read_duration_MIN;
      Max = CH0_CR_TC_ODT_ODT_read_duration_MAX;
      break;

    case GsmMctOdtRdDelay:
      Min = CH0_CR_TC_ODT_ODT_Read_Delay_MIN;
      Max = CH0_CR_TC_ODT_ODT_Read_Delay_MAX;
      break;

    case GsmMctOdtWrDuration:
      Min = CH0_CR_TC_ODT_ODT_write_duration_MIN;
      Max = CH0_CR_TC_ODT_ODT_write_duration_MAX;
      break;

    case GsmMctOdtWrDelay:
      Min = CH0_CR_TC_ODT_ODT_Write_Delay_MIN;
      Max = CH0_CR_TC_ODT_ODT_Write_Delay_MAX;
      break;

    case GsmMctCL:
      Min = CH0_CR_TC_ODT_tCL_MIN;
      Max = CH0_CR_TC_ODT_tCL_MAX;
      break;

    case GsmMctCWL:
      Min = CH0_CR_TC_ODT_tCWL_MIN;
      Max = CH0_CR_TC_ODT_tCWL_MAX;
      break;

    case GsmMctAONPD:
      Min = CH0_CR_TC_ODT_tAONPD_MIN;
      Max = CH0_CR_TC_ODT_tAONPD_MAX;
      break;

    case GsmMctCKE:
      Min = CH0_CR_TC_PWRDN_tCKE_MIN;
      Max = CH0_CR_TC_PWRDN_tCKE_MAX;
      break;

    case GsmMctXP:
      Min = CH0_CR_TC_PWRDN_tXP_MIN;
      Max = CH0_CR_TC_PWRDN_tXP_MAX;
      break;

    case GsmMctXPDLL:
      Min = CH0_CR_TC_PWRDN_tXPDLL_MIN;
      Max = CH0_CR_TC_PWRDN_tXPDLL_MAX;
      break;

    case GsmMctPRPDEN:
      Min = CH0_CR_TC_PWRDN_tPRPDEN_MIN;
      Max = CH0_CR_TC_PWRDN_tPRPDEN_MAX;
      break;

    case GsmMctRDPDEN:
      Min = CH0_CR_TC_PWRDN_tRDPDEN_MIN;
      Max = CH0_CR_TC_PWRDN_tRDPDEN_MAX;
      break;

    case GsmMctWRPDEN:
      Min = CH0_CR_TC_PWRDN_tWRPDEN_MIN;
      Max = CH0_CR_TC_PWRDN_tWRPDEN_MAX;
      break;

    case GsmMctXSDLL:
      Min = CH0_CR_TC_SRFTP_tXSDLL_MIN;
      Max = CH0_CR_TC_SRFTP_tXSDLL_MAX;
      break;

    case GsmMctXSR:
      Min = CH0_CR_TC_SREXITTP_tXSR_MIN;
      Max = CH0_CR_TC_SREXITTP_tXSR_MAX;
      break;

    case GsmMctZQOPER:
      Min = CH0_CR_TC_SRFTP_tZQOPER_MIN;
      Max = CH0_CR_TC_SRFTP_tZQOPER_MAX;
      break;

    case GsmMctMOD:
      Min = CH0_CR_TC_SRFTP_tMOD_MIN;
      Max = CH0_CR_TC_SRFTP_tMOD_MAX;
      break;

    case GsmMctZQCAL:
      Min = CH0_CR_TC_ZQCAL_tZQCAL_MIN;
      Max = CH0_CR_TC_ZQCAL_tZQCAL_MAX;
      break;

    case GsmMctZQCS:
      Min = CH0_CR_TC_ZQCAL_tZQCS_MIN;
      Max = CH0_CR_TC_ZQCAL_tZQCS_MAX;
      break;

    case GsmMctZQCSPeriod:
      Min = CH0_CR_TC_ZQCAL_ZQCS_period_MIN;
      Max = CH0_CR_TC_ZQCAL_ZQCS_period_MAX;
      break;

    case GsmMctCPDED:
      Min = CH0_CR_SC_GS_CFG_tCPDED_MIN;
      Max = CH0_CR_SC_GS_CFG_tCPDED_MAX;
      break;

    case GsmMctCAL:
      Min = CH0_CR_SC_GS_CFG_tCAL_MIN;
      Max = CH0_CR_SC_GS_CFG_tCAL_MAX;
      break;

    case GsmMctCKCKEH:
      Min = CH0_CR_SC_GS_CFG_ck_to_cke_MIN;
      Max = CH0_CR_SC_GS_CFG_ck_to_cke_MAX;
      break;

    case GsmMctCSCKEH:
      Min = CH0_CR_SC_GS_CFG_cs_to_cke_MIN;
      Max = CH0_CR_SC_GS_CFG_cs_to_cke_MAX;
      break;

    case GsmMctSrIdle:
      Min = PM_SREF_CONFIG_Idle_timer_MIN;
      Max = PM_SREF_CONFIG_Idle_timer_MAX;
      break;

    case GsmMctREFI:
      Min = CH0_CR_TC_RFTP_tREFI_MIN;
      Max = CH0_CR_TC_RFTP_tREFI_MAX;
      break;

    case GsmMctRFC:
      Min = CH0_CR_TC_RFTP_tRFC_MIN;
      Max = CH0_CR_TC_RFTP_tRFC_MAX;
      break;

    case GsmMctOrefRi:
      Min = CH0_CR_TC_RFP_OREF_RI_MIN;
      Max = CH0_CR_TC_RFP_OREF_RI_MAX;
      break;

    case GsmMctRefreshHpWm:
      Min = CH0_CR_TC_RFP_Refresh_HP_WM_MIN;
      Max = CH0_CR_TC_RFP_Refresh_HP_WM_MAX;
      break;

    case GsmMctRefreshPanicWm:
      Min = CH0_CR_TC_RFP_Refresh_panic_wm_MIN;
      Max = CH0_CR_TC_RFP_Refresh_panic_wm_MAX;
      break;

    case GsmMctREFIx9:
      Min = CH0_CR_TC_RFP_tREFIx9_MIN;
      Max = CH0_CR_TC_RFP_tREFIx9_MAX;
      break;

      // Group all the Boolean Variables here
    case GsmMctWrEarlyOdt:
      Min = 0;
      Max = 1;
      break;

    default:
      Status = mrcWrongInputParameter;
      break;
  }

  if (Status != mrcSuccess) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Group %s(%d) has no limits defined\n", GsmGtDebugStrings[Group], Group);
  }

  // Null guard the pointers
  if (MinVal != NULL) {
    *MinVal = Min;
  }
  if (MaxVal != NULL) {
    *MaxVal = Max;
  }
  if (WaitTime != NULL) {
    *WaitTime = Wait;
  }


  return Status;
}

/**
  This function returns MC Config register limits.

  @param[in]  MrcData   - Pointer to global data.
  @param[in]  Group     - DDRIO group to access.
  @param[out] MinVal    - Return pointer for Minimum Value supported.
  @param[out] MaxVal    - Return pointer for Maximum Value supported.
  @param[out] WaitTime  - Return pointer for settle time required in microseconds.

  @retval MrcStatus - mrcSuccess if the parameter is found, otherwise mrcFail.
**/
MrcStatus
MrcGetMcConfigGroupLimits (
  IN  MrcParameters *const MrcData,
  IN  GSM_GT  const   Group,
  OUT INT64   *const  MinVal,
  OUT INT64   *const  MaxVal,
  OUT UINT32  *const  WaitTime
  )
{
  MrcStatus Status;
  MrcDebug  *Debug;
  INT64     Max;
  INT64     Min;
  UINT32    Wait;

  Debug   = &MrcData->Outputs.Debug;
  Status  = mrcSuccess;
  Wait    = 0;
  Min     = MRC_INT64_MIN;
  Max     = MRC_INT64_MAX;

  switch (Group) {
    case GsmMccDramType:
      Min = CH0_CR_SC_GS_CFG_DRAM_technology_MIN;
      Max = CH0_CR_SC_GS_CFG_DRAM_technology_MAX;
      break;

    case GsmMccCmdStretch:
      Min = CH0_CR_SC_GS_CFG_CMD_stretch_MIN;
      Max = CH0_CR_SC_GS_CFG_CMD_stretch_MAX;
      break;

    case GsmMccCmdGapRatio:
      Min = CH0_CR_SC_GS_CFG_N_to_1_ratio_MIN;
      Max = CH0_CR_SC_GS_CFG_N_to_1_ratio_MAX;
      break;

    case GsmMccAddrMirror:
      Min = CH0_CR_SC_GS_CFG_Address_mirror_MIN;
      Max = CH0_CR_SC_GS_CFG_Address_mirror_MAX;
      break;

    case GsmMccFreqPoint:
      Min = CH0_CR_SC_GS_CFG_frequency_point_MIN;
      Max = CH0_CR_SC_GS_CFG_frequency_point_MAX;
      break;

    case GsmMccLDimmMap:
      Min = MAD_INTRA_CH0_DIMM_L_MAP_MIN;
      Max = MAD_INTRA_CH0_DIMM_L_MAP_MAX;
      break;

    case GsmMccEccMode:
      Min = MAD_INTRA_CH0_ECC_MIN;
      Max = MAD_INTRA_CH0_ECC_MAX;
      // Wait 4 usec after enabling the ECC IO, needed by HW
      Wait = 4;
      break;

    case GsmMccAddrDecodeDdrType:
      Min = MAD_INTER_CHANNEL_DDR_TYPE_MIN;
      Max = MAD_INTER_CHANNEL_DDR_TYPE_MAX;
      break;

    case GsmMccSChannelSize:
      Min = MAD_INTER_CHANNEL_CH_S_SIZE_MIN;
      Max = MAD_INTER_CHANNEL_CH_S_SIZE_MAX;
      break;

    case GsmMccStackedChHash:
      Min = MAD_INTER_CHANNEL_STKD_MODE_CH_BITS_MIN;
      Max = MAD_INTER_CHANNEL_STKD_MODE_CH_BITS_MAX;
      break;

    case GsmMccLDimmSize:
      Min = MAD_DIMM_CH0_DIMM_L_SIZE_MIN;
      Max = MAD_DIMM_CH0_DIMM_L_SIZE_MAX;
      break;

    case GsmMccLDimmDramWidth:
      Min = MAD_DIMM_CH0_DLW_MIN;
      Max = MAD_DIMM_CH0_DLW_MAX;
      break;

    case GsmMccLDimmRankCnt:
      Min = MAD_DIMM_CH0_DLNOR_MIN;
      Max = MAD_DIMM_CH0_DLNOR_MAX;
      break;

    case GsmMccSDimmSize:
      Min = MAD_DIMM_CH0_DIMM_S_SIZE_MIN;
      Max = MAD_DIMM_CH0_DIMM_S_SIZE_MAX;
      break;

    case GsmMccSDimmDramWidth:
      Min = MAD_DIMM_CH0_DSW_MIN;
      Max = MAD_DIMM_CH0_DSW_MAX;
      break;

    case GsmMccSDimmRankCnt:
      Min = MAD_DIMM_CH0_DSNOR_MIN;
      Max = MAD_DIMM_CH0_DSNOR_MAX;
      break;

    case GsmMccResetOnCmd:
      Min = CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_MIN;
      Max = CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_MAX;
      break;

    case GsmMccResetDelay:
      Min = CH0_CR_SC_GS_CFG_TRAINING_reset_delay_MIN;
      Max = CH0_CR_SC_GS_CFG_TRAINING_reset_delay_MAX;
      break;

    case GsmMccRankOccupancy:
      Min = CH0_CR_MC_INIT_STATE_Rank_occupancy_MIN;
      Max = CH0_CR_MC_INIT_STATE_Rank_occupancy_MAX;
      break;

    case GsmMccRefInterval:
      Min = CH0_CR_MC_REFRESH_STAGGER_Ref_Interval_MIN;
      Max = CH0_CR_MC_REFRESH_STAGGER_Ref_Interval_MAX;
      break;

    case GsmMccHashMask:
      Min = CHANNEL_HASH_HASH_MASK_MIN;
      Max = CHANNEL_HASH_HASH_MASK_MAX;
      break;

    case GsmMccLsbMaskBit:
      Min = CHANNEL_HASH_HASH_LSB_MASK_BIT_MIN;
      Max = CHANNEL_HASH_HASH_LSB_MASK_BIT_MAX;
      break;

    case GsmMccX8Device:
      Min = CH0_CR_SC_GS_CFG_x8_device_MIN;
      Max = CH0_CR_SC_GS_CFG_x8_device_MAX;
      break;

    case GsmMccMr2Shadow:
      Min = CH0_CR_TC_MR2_SHADDOW_MR2_shaddow_MIN;
      Max = CH0_CR_TC_MR2_SHADDOW_MR2_shaddow_MAX;
      break;

    case GsmMccSrtAvail:
      Min = CH0_CR_TC_MR2_SHADDOW_SRT_avail_MIN;
      Max = CH0_CR_TC_MR2_SHADDOW_SRT_avail_MAX;
      break;

    case GsmMccDdr4OneDpc:
      Min = CH0_CR_SC_GS_CFG_ddr4_1dpc_MIN;
      Max = CH0_CR_SC_GS_CFG_ddr4_1dpc_MAX;
      break;

    //
    // For boolean parameters, we will group them here as their Min/Max is always 0/1
    //
    case GsmMccGear2:
    case GsmMccCpgcInOrder:
    case GsmMccCadbEnable:
    case GsmMccDeselectEnable:
    case GsmMccBusRetainOnBubble:
    case GsmMccLp4FifoRdWr:
    case GsmMccIgnoreCke:
    case GsmMccMaskCs:
    case GsmMccLpddr2nCsMrw:
    case GsmMccBlockXarb:
    case GsmMccEnableOdtMatrix:
    case GsmMccCmdTriStateDis:
    case GsmMccCmdTriStateDisTrain:
    case GsmMccRankInterleave:
    case GsmMccEnhancedInterleave:
    case GsmMccEnhChannelMode:
    case GsmMccStackedMode:
    case GsmMccStackChMap:
    case GsmMccLChannelMap:
    case GsmMccLDimm8Gb:
    case GsmMccSDimm8Gb:
    case GsmMccPuMrcDone:
    case GsmMccSaveFreqPoint:
    case GsmMccEnableRefresh:
    case GsmMccEnableSr:
    case GsmMccMcInitDoneAck:
    case GsmMccMrcDone:
    case GsmMccEnableDclk:
    case GsmMccPureSrx:
    case GsmMccMcSrx:
    case GsmMccHashMode:
    case GsmMccRefStaggerEn:
    case GsmMccRefStaggerMode:
    case GsmMccDisableStolenRefresh:
    case GsmMccEnRefTypeDisplay:
    case GsmMccDisableCkTristate:
    case GsmMccPbrDis:
      Min = 0;
      Max = 1;
      break;

    // These are unused.  Need to finish HAL if these fields are accessed.
    case GsmMccDdrReset:
    case GsmMccSafeSr:

    default:
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Group %s(%d) has no limits defined\n", GsmGtDebugStrings[Group], Group);
      Status = mrcWrongInputParameter;
      break;
  }

  // Null guard the pointers
  if (MinVal != NULL) {
    *MinVal = Min;
  }
  if (MaxVal != NULL) {
    *MaxVal = Max;
  }
  if (WaitTime != NULL) {
    *WaitTime = Wait;
  }

  return Status;
}

/**
  This function generates the hash used to execute the Get/Set function.
  The hash consists of: Register Offset, BitField start bit, BitField length.

  @param[in]  MrcData     - Pointer to global data.
  @param[in]  Group       - DDRIO group to access.
  @param[in]  Socket      - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]  SubChannel  - DDR SubChannel within the channel Number(0-based).
  @param[in]  Rank        - Rank number within a channel (0-based).
  @param[in]  Strobe      - Dqs data group within the rank (0-based).
  @param[in]  Bit         - Bit index within the data group (0-based).
  @param[in]  FreqIndex   - Index supporting multiple operating frequencies. (Not used in Client CPU's)
  @param[out] HashVal     - Pointer to return the MMIO access instruction.

  @retval MrcStatus
**/
MrcStatus
MrcGetDdrIoHash (
  IN  MrcParameters *const  MrcData,
  IN  GSM_GT  const   Group,
  IN  UINT32  const   Socket,
  IN  UINT32  const   Channel,
  IN  UINT32  const   SubChannel,
  IN  UINT32  const   Rank,
  IN  UINT32  const   Strobe,
  IN  UINT32  const   Bit,
  IN  UINT32  const   FreqIndex,
  OUT UINT32  *const  HashVal
  )
{
  MrcOutput *Outputs;
  MrcStatus Status;
  MrcDebug  *Debug;
  UINT32    CrOffset;
  UINT32    MaxIndex;
  UINT32    CmdGrpMax;
  UINT32    LogicalIndex;
  BOOLEAN   Lpddr4;
  BOOLEAN   Gear2;
  MRC_REGISTER_HASH_STRUCT *HashPtr;

  static const UINT32 RoundtripDelayHsh[ICL_ROUNDTRIP_DELAY_MAX] = {
    CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_0_latency_HSH, CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_1_latency_HSH,
    CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_2_latency_HSH, CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_3_latency_HSH,
    CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_4_latency_HSH, CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_5_latency_HSH,
    CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_6_latency_HSH, CH0_CR_SC_ROUNDTRIP_LATENCY_Rank_7_latency_HSH
  };
  static const UINT32 RxFlybyDelayCnlHsh[MAX_SUB_CHANNEL][MAX_RANK_IN_CHANNEL] = {
    {MCMISCS_READCFGCHACHB0_RcvEnRank0ChADel_HSH, MCMISCS_READCFGCHACHB0_RcvEnRank1ChADel_HSH,
     MCMISCS_READCFGCHACHB0_RcvEnRank2ChADel_HSH, MCMISCS_READCFGCHACHB0_RcvEnRank3ChADel_HSH}, // SubChannel 0
    {MCMISCS_READCFGCHACHB0_RcvEnRank0ChBDel_HSH, MCMISCS_READCFGCHACHB0_RcvEnRank1ChBDel_HSH,
     MCMISCS_READCFGCHACHB0_RcvEnRank2ChBDel_HSH, MCMISCS_READCFGCHACHB0_RcvEnRank3ChBDel_HSH}  // SubChannel 1
  };
  static const UINT32 RxFifoRdyDelay[MAX_SUB_CHANNEL][MAX_RANK_IN_CHANNEL] = {
    {MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank0ChADel_HSH, MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank1ChADel_HSH,
     MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank2ChADel_HSH, MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank3ChADel_HSH}, // SubChannel 0
    {MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank0ChBDel_HSH, MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank1ChBDel_HSH,
     MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank2ChBDel_HSH, MCMISCS_RXDQFIFORDENCHACHB0_RxDqFifoRdEnRank3ChBDel_HSH}  // SubChannel 1
  };
  static const UINT32 TxDqFifoRdEnFlybyCnl[MAX_SUB_CHANNEL][MAX_RANK_IN_CHANNEL] = {
    {MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank0ChADel_HSH, MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank1ChADel_HSH,
     MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank2ChADel_HSH, MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank3ChADel_HSH}, // SubChannel 0
    {MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank0ChBDel_HSH, MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank1ChBDel_HSH,
     MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank2ChBDel_HSH, MCMISCS_WRITECFGCHACHB0_TxDqFifoRdEnRank3ChBDel_HSH}  // SubChannel 1
  };
  static const UINT32 RxVocHash[MAX_BITS] =  {
    DDRDATA0CH0_CR_RXCONTROL2RANK0_Lane0RxOffsetVDq_HSH, DDRDATA0CH0_CR_RXCONTROL2RANK0_Lane1RxOffsetVDq_HSH,
    DDRDATA0CH0_CR_RXCONTROL2RANK0_Lane2RxOffsetVDq_HSH, DDRDATA0CH0_CR_RXCONTROL2RANK0_Lane3RxOffsetVDq_HSH,
    DDRDATA0CH0_CR_RXCONTROL3RANK0_Lane4RxOffsetVDq_HSH, DDRDATA0CH0_CR_RXCONTROL3RANK0_Lane5RxOffsetVDq_HSH,
    DDRDATA0CH0_CR_RXCONTROL3RANK0_Lane6RxOffsetVDq_HSH, DDRDATA0CH0_CR_RXCONTROL3RANK0_Lane7RxOffsetVDq_HSH
  };
  static const UINT32 CnlClkHsh[MRC_CLK_GRP_MAX] = {
    DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode0_HSH, DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode1_HSH,
    DDRCTLCLKCKE0_CR_DDRCRCTLPICODING_CtlPiCode0_HSH, DDRCTLCLKCKE0_CR_DDRCRCTLPICODING_CtlPiCode1_HSH
  };
  static const UINT32 CnlCtlHsh[MRC_CTL_GRP_MAX] = {
    DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode2_HSH, DDRCTLCH0_CR_DDRCRCTLPICODING_CtlPiCode3_HSH,
    DDRCTLCLKCKE0_CR_DDRCRCTLPICODING_CtlPiCode2_HSH, DDRCTLCLKCKE0_CR_DDRCRCTLPICODING_CtlPiCode3_HSH
  };
  static const UINT32 CnlCkeHsh[MRC_CKE_GRP_MAX] =  {
    DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode0_HSH, DDRCKECH0_CR_DDRCRCTLPICODING_CtlPiCode1_HSH,
    DDRCTLCLKCKE0_CR_DDRCRCTLPICODING_CtlPiCode2_HSH, DDRCTLCLKCKE0_CR_DDRCRCTLPICODING_CtlPiCode3_HSH
  };
  static const UINT32 CaVrefHsh[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL] = {  // CaVref is per DIMM starting from ICL B0
    {
      DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm0CaVrefIntCtl_HSH,
      DDRVREF_CR_DDRCRVREFADJUST1_Ch0Dimm1CaVrefIntCtl_HSH
    },
    {
      DDRVREF_CR_DDRCRVREFADJUST1_Ch1Dimm0CaVrefIntCtl_HSH,
      DDRVREF_CR_DDRCRVREFADJUST3_Ch1Dimm1CaVrefIntCtl_HSH
    }
  };
  static const UINT32 DqDfeDelayModeHsh[MAX_RANK_IN_CHANNEL] =  {
    DDRDATA0CH0_CR_DDRCRDATADFECONTROL1RANK01_DfeDlyModeRank0_HSH, DDRDATA0CH0_CR_DDRCRDATADFECONTROL1RANK01_DfeDlyModeRank1_HSH,
    DDRDATA0CH0_CR_DDRCRDATADFECONTROL1RANK01_DfeDlyModeRank2_HSH, DDRDATA0CH0_CR_DDRCRDATADFECONTROL1RANK01_DfeDlyModeRank3_HSH
  };
  static const UINT32 DqDfeCoeffHsh[MAX_RANK_IN_CHANNEL] =  {
    DDRDATA0CH0_CR_DDRCRDATACONTROL8_DqDfeCoeffRank0_HSH, DDRDATA0CH0_CR_DDRCRDATACONTROL8_DqDfeCoeffRank1_HSH,
    DDRDATA0CH0_CR_DDRCRDATACONTROL8_DqDfeCoeffRank2_HSH, DDRDATA0CH0_CR_DDRCRDATACONTROL8_DqDfeCoeffRank3_HSH
  };

  Outputs   = &MrcData->Outputs;
  Debug     = &Outputs->Debug;
  Status    = mrcSuccess;
  HashPtr   = (MRC_REGISTER_HASH_STRUCT *) HashVal;
  CrOffset  = MRC_UINT32_MAX;
  CmdGrpMax = MRC_CMD_GRP_MAX;
  Lpddr4    = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);

  Gear2 = Outputs->Gear2;
  if (Lpddr4 && Outputs->Frequency == f1067) {
    Gear2 = FALSE;
  }

  switch (Group) {
    case RecEnDelay:
      HashPtr->Data = DDRDATA0CH0_CR_RXCONTROL0RANK0_RxRcvEnPi_HSH;
      break;

    case RxDqsPDelay:
      HashPtr->Data = DDRDATA0CH0_CR_RXCONTROL0RANK0_RxDqsNPi_HSH;
      break;

    case RxDqsNDelay:
      HashPtr->Data = DDRDATA0CH0_CR_RXCONTROL0RANK0_RxDqsPPi_HSH;
      break;

    case RxVref:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL5_RxVref_HSH;
      break;

    case RxVoc:
      if (Bit < MAX_BITS) {
        HashPtr->Data = RxVocHash[Bit];
        break;
      } else {
        Status = mrcWrongInputParameter;
      }
      break;

    case RxEq:
      HashPtr->Data = DDRDATA0CH0_CR_RXCONTROL0RANK0_RxEq_HSH;
      break;

    case RxRankMuxDelay:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL2_RxRankMuxDelay_HSH;
      break;

    case RxDqBitDelay:
      switch (Bit) {
        default:
          Status = mrcWrongInputParameter;
          // no break;
        case 0:
          HashPtr->Data = DDRDATA0CH0_CR_RXCONTROL1RANK0_Lane0PerBitDeskew_HSH;
          break;

        case 1:
          HashPtr->Data = DDRDATA0CH0_CR_RXCONTROL1RANK0_Lane1PerBitDeskew_HSH;
          break;

        case 2:
          HashPtr->Data = DDRDATA0CH0_CR_RXCONTROL1RANK0_Lane2PerBitDeskew_HSH;
          break;

        case 3:
          HashPtr->Data = DDRDATA0CH0_CR_RXCONTROL1RANK0_Lane3PerBitDeskew_HSH;
          break;

        case 4:
          HashPtr->Data = DDRDATA0CH0_CR_RXCONTROL2RANK0_Lane4PerBitDeskew_HSH;
          break;

        case 5:
          HashPtr->Data = DDRDATA0CH0_CR_RXCONTROL2RANK0_Lane5PerBitDeskew_HSH;
          break;

        case 6:
          HashPtr->Data = DDRDATA0CH0_CR_RXCONTROL3RANK0_Lane6PerBitDeskew_HSH;
          break;

        case 7:
          HashPtr->Data = DDRDATA0CH0_CR_RXCONTROL3RANK0_Lane7PerBitDeskew_HSH;
          break;
      }
      break;

    case TxDqsDelay:
      HashPtr->Data = DDRDATA0CH0_CR_TXTRAINRANK0_TxDqsDelay_HSH;
      break;

    case TxDqDelay:
      HashPtr->Data = DDRDATA0CH0_CR_TXTRAINRANK0_TxDqDelay_HSH;
      break;

    case TxEq:
      HashPtr->Data = DDRDATA0CH0_CR_TXTRAINRANK0_TxEqualization_HSH;
      break;

    case TxRankMuxDelay:
      HashPtr->Data = DDRDATA0CH0_CR_TXTRAINRANK0_TxRankMuxDelay_HSH;
      break;

    case TxDqsRankMuxDelay:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL3_TxDqsRankMuxDelay_HSH;
      break;

    case TxDqBitDelay:
      switch (Bit) {
        default:
          Status = mrcWrongInputParameter;
          // no break;
        case 0:
          HashPtr->Data = DDRDATA0CH0_CR_TXPERBITLOWRANK0_Lane0_HSH;
          break;

        case 1:
          HashPtr->Data = DDRDATA0CH0_CR_TXPERBITLOWRANK0_Lane1_HSH;
          break;

        case 2:
          HashPtr->Data = DDRDATA0CH0_CR_TXPERBITLOWRANK0_Lane2_HSH;
          break;

        case 3:
          HashPtr->Data = DDRDATA0CH0_CR_TXPERBITLOWRANK0_Lane3_HSH;
          break;

        case 4:
          HashPtr->Data = DDRDATA0CH0_CR_TXPERBITHIRANK0_Lane4_HSH;
          break;

        case 5:
          HashPtr->Data = DDRDATA0CH0_CR_TXPERBITHIRANK0_Lane5_HSH;
          break;

        case 6:
          HashPtr->Data = DDRDATA0CH0_CR_TXPERBITHIRANK0_Lane6_HSH;
          break;

        case 7:
          HashPtr->Data = DDRDATA0CH0_CR_TXPERBITHIRANK0_Lane7_HSH;
          break;
      }
      break;

    case RecEnOffset:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RcvEnOffset_HSH;
      break;

    case RxDqsOffset:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_RxDqsOffset_HSH;
      break;

    case RxVrefOffset:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_VrefOffset_HSH;
      break;

    case TxDqsOffset:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqsOffset_HSH;
      break;

    case TxDqOffset:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_TxDqOffset_HSH;
      break;

    case RoundTripDelay:
      MaxIndex = ICL_ROUNDTRIP_DELAY_MAX;
      if (Lpddr4) {
        LogicalIndex = (2 * (SubChannel % 2)) + (4 * (Rank / 2)) + (Rank % 2);
      } else {
        LogicalIndex = Rank % 4;
      }
      if (LogicalIndex < MaxIndex) {
        HashPtr->Data = RoundtripDelayHsh[LogicalIndex];
        HashPtr->Bits.RegSize = 1;
      } else {
        Status = mrcWrongInputParameter;
      }
      break;

    case RxFlybyDelay:
      if ((Rank >= MAX_RANK_IN_CHANNEL) || (SubChannel >= MAX_SUB_CHANNEL)) {
        Status = mrcWrongInputParameter;
      } else {
        HashPtr->Data = RxFlybyDelayCnlHsh[SubChannel][Rank];
      }
      break;

    case RxIoTclDelay:
      HashPtr->Data = MCMISCS_READCFGCH0_tCL4RcvEn_HSH;
      break;

    case RxFifoRdEnFlybyDelay:
      if ((Rank >= MAX_RANK_IN_CHANNEL) || (SubChannel >= MAX_SUB_CHANNEL)) {
        Status = mrcWrongInputParameter;
      } else {
        HashPtr->Data = RxFifoRdyDelay[SubChannel][Rank];
        if (Gear2) {
          // In Gear2 the value in tCK is in bits [3:1], and bit [0] should be 0
          // In Gear1 we program the value as is, it has UI resolution
          HashPtr->Bits.BfOffset += 1;
          HashPtr->Bits.BfWidth  -= 1;
        }
      }
      break;

    case RxFifoRdEnTclDelay:
      HashPtr->Data = MCMISCS_READCFGCH0_tCL4RxDqFifoRdEn_HSH;
      break;

    case RxDqDataValidDclkDelay:
      HashPtr->Data = MCMISCS_READCFGCH0_RxDqDataValidDclkDel_HSH;
      break;

    case RxDqDataValidQclkDelay:
      HashPtr->Data = MCMISCS_READCFGCH0_RxDqDataValidQclkDel_HSH;
      break;

    case TxDqFifoWrEnTcwlDelay:
      HashPtr->Data = MCMISCS_WRITECFGCH0_tCWL4TxDqFifoWrEn_HSH;
      break;

    case TxDqFifoRdEnTcwlDelay:
      HashPtr->Data = MCMISCS_WRITECFGCH0_tCWL4TxDqFifoRdEn_HSH;
      break;

    case TxDqFifoRdEnFlybyDelay:
      if ((Rank >= MAX_RANK_IN_CHANNEL) || (SubChannel >= MAX_SUB_CHANNEL)) {
        Status = mrcWrongInputParameter;
      } else {
        HashPtr->Data = TxDqFifoRdEnFlybyCnl[SubChannel][Rank];
      }
      break;

    case SenseAmpDelay:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL1_SenseAmpDelay_HSH;
      break;

    case SenseAmpDuration:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL1_SenseAmpDuration_HSH;
      break;

    case McOdtDelay:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL1_OdtDelay_HSH;
      break;

    case McOdtDuration:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL1_OdtDuration_HSH;
      break;

    case McDqsOdtDelay:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL3_DqsOdtDelay_HSH;
      break;

    case McDqsOdtDuration:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL3_DqsOdtDuration_HSH;
      break;

    case DqDfeEnable:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATADFECONTROL0RANK0_DqDfeEn_HSH;
      break;

    case DqDfeDelayMode:
      if (Rank >= MAX_RANK_IN_CHANNEL) {
        Status = mrcWrongInputParameter;
      } else {
        HashPtr->Data = DqDfeDelayModeHsh[Rank];
      }
      break;

    case DqDfeCoeff:
      if (Rank >= MAX_RANK_IN_CHANNEL) {
        Status = mrcWrongInputParameter;
      } else {
        HashPtr->Data = DqDfeCoeffHsh[Rank];
      }
      break;

    case DqDfeDelay:
      if (Bit == 0) {  //Bit 0
        HashPtr->Data = DDRDATA0CH0_CR_RXCONTROL1RANK0_DqDfeDlyBit0_HSH;
      } else if (Bit == 1) {  //Bit 1
        HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATADFECONTROL0RANK0_DqDfeDlyBit1_HSH;
      } else if (Bit == 2) {  //Bit 2
        HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATADFECONTROL0RANK0_DqDfeDlyBit2_HSH;
      } else if (Bit == 3) {  //Bit 3
        HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATADFECONTROL0RANK0_DqDfeDlyBit3_HSH;
      } else if (Bit == 4) {  //Bit 4
        HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATADFECONTROL0RANK0_DqDfeDlyBit4_HSH;
      } else if (Bit == 5) {  //Bit 5
        HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATADFECONTROL0RANK0_DqDfeDlyBit5_HSH;
      } else if (Bit == 6) {  //Bit 6
        switch (Rank) {
          case 0:
          case 2:
            HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATADFECONTROL1RANK01_DqDfeDlyBit6Rank0_HSH;
            break;
          case 1:
          case 3:
            HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATADFECONTROL1RANK01_DqDfeDlyBit6Rank1_HSH;
            break;
          default:
            Status = mrcWrongInputParameter;
            break;
        }
      } else if (Bit == 7) {  //Bit 7
        switch (Rank) {
          case 0:
          case 2:
            HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATADFECONTROL1RANK01_DqDfeDlyBit7Rank0_HSH;
            break;
          case 1:
          case 3:
            HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATADFECONTROL1RANK01_DqDfeDlyBit7Rank1_HSH;
            break;
          default:
            Status = mrcWrongInputParameter;
            break;
        }
      } else {
        Status = mrcWrongInputParameter;
      }
      break;


    case RxBiasIComp:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL1_RxBiasCtl_HSH;
      break;

    case RxBiasRCompMsb:     ///< MSB of GsmIocRxBiasRcomp [3]
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL6_BiasRcompMsb_HSH;
      break;

    case RxBiasRCompLsb:     ///< LSB of GsmIocRxBiasRcomp [2:0]
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL4_biasrcomp_HSH;
      break;

    case RxDqsAmpOffset:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL6_RxDqsAmpOffset_HSH;
      break;

    case SdllPiCb:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL6_sdll_picb_HSH;
      break;

    case D0PiCb:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL6_d0_picb_HSH;
      break;

    case SdllBwCtrl:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL7_sdll_bw_ctrl_HSH;
      break;

    case D0BwCtrl:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL7_d0_bw_ctrl_HSH;
      break;

    case RxCben:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL2_Cben_HSH;
      break;

    case CBEnAmp1:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL3_CBEnAmp1_HSH;
      break;

    case TxVref:        // @todo Can remove when ICL A0 support is dropped
      if (Channel == 0) {
        HashPtr->Data = DDRVREF_CR_DDRCRVREFADJUST1_Ch0VrefIntCtl_HSH_A0;
      } else {
        HashPtr->Data = DDRVREF_CR_DDRCRVREFADJUST1_Ch1VrefIntCtl_HSH_A0;
      }
      break;

    case CmdVref:
      if (MrcData->Inputs.IclA0) {
        HashPtr->Data = DDRVREF_CR_DDRCRVREFADJUST1_CAVrefIntCtl_HSH_A0;
      } else if (Rank < MAX_RANK_IN_CHANNEL) {
        HashPtr->Data = CaVrefHsh[Channel][RANK_TO_DIMM_NUMBER (Rank)];
      } else {
        Status = mrcWrongInputParameter;
      }
      break;

    case CmdGrpPi:
      if (Strobe < CmdGrpMax) {
        if (Strobe == 4) {
          HashPtr->Data = DDRCTLCLKCKE0_CR_DDRCRCTLPICODING_CtlPiCode2_HSH;
        } else {
          // All CMD N/S, CKE-CMD, and CNL CMD B/A use the same Register Layout.
          HashPtr->Data = ((Strobe % 2) == 0) ? DDRCMDBCH0_CR_DDRCRCMDPICODING_CmdPi0Code_HSH : DDRCMDBCH0_CR_DDRCRCMDPICODING_CmdPi1Code_HSH;
        }
      } else {
        Status = mrcWrongInputParameter;
      }
      break;

    case ClkGrpPi:
      if (Strobe < MRC_CLK_GRP_MAX) {
        HashPtr->Data = CnlClkHsh[Strobe];
      } else {
        Status = mrcWrongInputParameter;
      }
      break;

    case CtlGrpPi:
      if (Strobe < MRC_CTL_GRP_MAX) {
        HashPtr->Data = CnlCtlHsh[Strobe];
      } else {
        Status = mrcWrongInputParameter;
      }
      break;

    case CkeGrpPi:
      if (Strobe < MRC_CKE_GRP_MAX) {
        HashPtr->Data = CnlCkeHsh[Strobe];
      } else {
        Status = mrcWrongInputParameter;
      }
      break;

    case TxSlewRate:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL1_DqScompCells_HSH;
      break;

    case DqScompPC:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL1_DqScompPC_HSH;
      break;

    case CmdSlewRate:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL1_CmdScompCells_HSH;
      break;

    case CmdScompPC:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL1_CmdScompPC_HSH;
      break;

    case CtlSlewRate:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL1_CtlScompCells_HSH;
      break;

    case CtlScompPC:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL1_CtlScompPC_HSH;
      break;

    case ClkSlewRate:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL1_ClkScompCells_HSH;
      break;

    case ClkScompPC:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL1_ClkScompPC_HSH;
      break;

    case DqRcompStatLegs:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL1_DqRcompStatLegs_HSH;
      break;

    case SCompCodeDq:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRDATACOMP0_SlewRateComp_HSH;
      break;

    case SCompCodeCmd:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCMDCOMP_Scomp_HSH;
      break;

    case SCompCodeCtl:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCTLCOMP_Scomp_HSH;
      break;

    case SCompCodeClk:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCLKCOMP_Scomp_HSH;
      break;

    case TxRonUp:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRDATACOMP0_RcompDrvUp_HSH;
      break;

    case WrDSCodeUpCmd:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCMDCOMP_RcompDrvUp_HSH;
      break;

    case WrDSCodeUpCtl:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCTLCOMP_RcompDrvUp_HSH;
      break;

    case WrDSCodeUpClk:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCLKCOMP_RcompDrvUp_HSH;
      break;

    case TxRonDn:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRDATACOMP0_RcompDrvDown_HSH;
      break;

    case WrDSCodeDnCmd:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCMDCOMP_RcompDrvDown_HSH;
      break;

    case WrDSCodeDnCtl:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCTLCOMP_RcompDrvDown_HSH;
      break;

    case WrDSCodeDnClk:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCLKCOMP_RcompDrvDown_HSH;
      break;

    case TxTco:
      switch (Bit) {
      default:
        Status = mrcWrongInputParameter;
        // no break to set default to case 0;
      case 0:
        HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit0_HSH;
        break;

      case 1:
        HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit1_HSH;
        break;

      case 2:
        HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit2_HSH;
        break;

      case 3:
        HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATATCOCONTROL0_DqTcoCompBit3_HSH;
        break;

      case 4:
        HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit4_HSH;
        break;

      case 5:
        HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit5_HSH;
        break;

      case 6:
        HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit6_HSH;
        break;

      case 7:
        HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATATCOCONTROL1_DqTcoCompBit7_HSH;
        break;
      }
      break;

    case TxTcoDqsN:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATATCOCONTROL0_DqsNTcoComp_HSH;
      break;

    case TxTcoDqsP:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATATCOCONTROL1_DqsPTcoComp_HSH;
      break;

    case TxTcoByPass:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL0_DqTcoBypass_HSH;
      break;

    case TcoCompCodeCmd:
      HashPtr->Data = DDRCMDACH0_CR_DDRCRCMDTCOCONTROL0_CmdTcoComp_HSH;
      break;

    case TcoCompCodeCtl:
      HashPtr->Data = DDRCTLCH0_CR_DDRCRCTLTCOCONTROL0_CtlTcoComp_HSH;
      break;

    case TcoCompCodeClk:
      HashPtr->Data = DDRCLKCH0_CR_DDRCRCLKTCOCONTROL0_ClkTcoComp_HSH;
      break;

    case DqOdtVref:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL0_DqOdtVref_HSH;
      break;

    case DqDrvVref:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL0_DqDrvVref_HSH;
      break;

    case CmdDrvVref:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL3_CmdDrvVref_HSH;
      break;

    case CmdTxEq:
      HashPtr->Data = DDRCMDACH0_CR_DDRCRCMDCONTROLS_CmdTxEq_HSH;
      break;

    case CtlDrvVref:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL3_CtlDrvVref_HSH;
      break;

    case ClkDrvVref:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL3_ClkDrvVref_HSH;
      break;

    case CompRcompOdtUp:
      HashPtr->Data = DDRDATA0CH0_CR_RCOMPDATA1_RcompOdtUp_HSH;
      break;

    case CompRcompOdtDn:
      HashPtr->Data = DDRDATA0CH0_CR_RCOMPDATA1_RcompOdtDown_HSH;
      break;

    case CtlSCompOffset:
      HashPtr->Data = DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_HSH;
      break;

    case CtlRCompDrvUpOffset:
      HashPtr->Data = DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_HSH;
      break;

    case CtlRCompDrvDownOffset:
      HashPtr->Data = DDRCKECTLCH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_HSH;
      break;

    case CmdSCompOffset:
      HashPtr->Data = DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_ScompOffset_HSH;
      break;

    case CkeSCompOffset:
      HashPtr->Data = DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_ScompOffset_HSH;
      break;

    case CmdRCompDrvUpOffset:
      HashPtr->Data = DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvUpOffset_HSH;
      break;

    case CmdRCompDrvDownOffset:
      HashPtr->Data = DDRCMDCH0_CR_DDRCRCMDCOMPOFFSET_RcompDrvDownOffset_HSH;
      break;

    case ClkCompOnTheFlyUpdtEn:
      HashPtr->Data = DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_ClkCompOnTheFlyUpdtEn_HSH;
      break;

    case ClkRCompDrvDownOffset:
      HashPtr->Data = DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_RcompDrvDownOffset_HSH;
      break;

    case ClkRCompDrvUpOffset:
      HashPtr->Data = DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_RcompDrvUpOffset_HSH;
      break;

    case ClkSCompOffset:
      HashPtr->Data = DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_ScompOffset_HSH;
      break;

    case CkeRCompDrvDownOffset:
      HashPtr->Data = DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvDownOffset_HSH;
      break;

    case CkeRCompDrvUpOffset:
      HashPtr->Data = DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_RcompDrvUpOffset_HSH;
      break;

    // These are unused.  Need to finish HAL if these fields are accessed.
    case TxRon:
    case CmdRon:
    case ClkRon:
    case CtlRon:

    default:
      Status = mrcWrongInputParameter;
      break;
  }

  if (Status == mrcSuccess) {
    CrOffset = MrcGetDdrIoRegOffset (MrcData, Group, Socket, Channel, SubChannel, Rank, Strobe, Bit, FreqIndex);
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Hash is undefined: Group %s(%d) Channel %u Rank %u Strobe %u\n", gErrString, GsmGtDebugStrings[Group], Group, Channel, Rank, Strobe);
  }
  if (CrOffset > 0xFFFF) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Bad Offset = 0x%08X Group %s(%d) Channel %u Rank %u Strobe %u\n", gErrString, CrOffset, GsmGtDebugStrings[Group], Group, Channel, Rank, Strobe);
    CrOffset = MRC_UINT32_MAX;
  }

  HashPtr->Bits.Offset = CrOffset;

  return Status;
}

/**
  This function generates the hash used to execute the Get/Set function.
  The hash consists of: Register Offset, BitField start bit, BitField length.

  @param[in]  MrcData     - Pointer to global data.
  @param[in]  Group       - DDRIO group to access.
  @param[in]  Socket      - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]  SubChannel  - DDR SubChannel within the channel Number(0-based).
  @param[in]  Rank        - Rank number within a channel (0-based).
  @param[in]  Strobe      - Dqs data group within the rank (0-based).
  @param[in]  Bit         - Bit index within the data group (0-based).
  @param[in]  FreqIndex   - Index supporting multiple operating frequencies. (Not used in Client CPU's)
  @param[out] HashVal     - Pointer to return the MMIO access instruction.

  @retval MrcStatus
**/
MrcStatus
MrcGetDdrIoCfgHash (
  IN  MrcParameters   *const  MrcData,
  IN  GSM_GT          const   Group,
  IN  UINT32          const   Socket,
  IN  UINT32          const   Channel,
  IN  UINT32          const   SubChannel,
  IN  UINT32          const   Rank,
  IN  UINT32          const   Strobe,
  IN  UINT32          const   Bit,
  IN  UINT32          const   FreqIndex,
  OUT UINT32          *const  HashVal
  )
{
  MrcStatus Status;
  MrcDebug  *Debug;
  UINT32    CrOffset;
  MRC_REGISTER_HASH_STRUCT *HashPtr;

  static const UINT32 CaVrefConvergeHsh[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL] = { // CaVref is per DIMM starting from ICL B0
    {
      DDRVREF_CR_DDRCRVREFADJUST2_CaCh0Dimm0SlowBW_HSH,
      DDRVREF_CR_DDRCRVREFADJUST2_CaCh0Dimm1SlowBW_HSH
    },
    {
      DDRVREF_CR_DDRCRVREFADJUST2_CaCh1Dimm0SlowBW_HSH,
      DDRVREF_CR_DDRCRVREFADJUST2_CaCh1Dimm1SlowBW_HSH
    }
  };

  Debug     = &MrcData->Outputs.Debug;
  Status    = mrcSuccess;
  HashPtr   = (MRC_REGISTER_HASH_STRUCT *) HashVal;
  CrOffset  = MRC_UINT32_MAX;

  switch (Group) {
    case GsmIocWlWakeCyc:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_WL_WakeCycles_HSH;
      break;

    case GsmIocWlSleepCyc:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_WL_SleepCycles_HSH;
      break;

    case GsmIocForceCmpUpdt:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL1_ForceCompUpdate_HSH;
      break;

    case GsmIocWlLatency:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_WeakLock_Latency_HSH;
      break;

    case GsmIocLpRcvenCtrl:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_lp4_rcven_ctrl_HSH;
      break;

    case GsmIocNoDqInterleave:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_DdrNoChInterleave_HSH;
      break;

    case GsmIocScramLpMode:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_LPDDR_Mode_HSH;
      break;

    case GsmIocScramDdr4Mode:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_Ddr4_Mode_HSH;
      break;

    case GsmIocDdrCentric:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_ddr_centric_HSH;
      break;

    case GsmIocScramGear1:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_Gear1_HSH;
      break;

    case GsmIocDisClkGate:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_ClkGateDisable_HSH;
      break;

    case GsmIocDllWlEn:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_DllDataWeakLckEn_HSH;
      break;

    case GsmIocDisDataIdlClkGate:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_DataClkGateDisAtIdle_HSH;
      break;

    case GsmIoc4ChMode:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_FourChCfg_HSH;
      break;

    case GsmIocScramLp4Mode:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_LpDdr4Mode_HSH;
      break;

    case GsmIocChNotPop:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_Channel_Not_Populated_HSH;
      break;

    case GsmIocDisIosfSbClkGate:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_dis_iosf_sb_clk_gate_HSH;
      break;

    case GsmIocEccEn:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL0_ECCPresent_HSH;
      break;

    case GsmIocDataOdtStaticDis:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL0_DisableOdtStatic_HSH;
      break;

    case GsmIocDataCtlLpMode:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL0_LPDDR_Mode_HSH;
      break;

    case GsmIocLowSupEnDqDqs:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL0_DQDQSLowsupEn_HSH;
      break;

    case GsmIocLp4DqsMaskPulseCnt:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL5_ddrcrmaskcntpulsenumstart_HSH;
      break;

    case GsmIocLp4ForceDqsPOn:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL6_ForceDqsPon_HSH;
      break;

    case GsmIocLp4ForceDqsNOn:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL6_ForceDqsNon_HSH;
      break;

    case GsmIocLp4ForceDqsPOnWithLeaker:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL6_forcedqsponwithleaker_HSH;
      break;

    case GsmIocLp4ForceDqsNOnWithLeaker:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL6_forcedqsnonwithleaker_HSH;
      break;

    case GsmIocLp4DqsPulseCnt:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL5_ddrcrnumofpulses_HSH;
      break;

    case GsmIocLp4DqsPulseEn:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL5_ddrcrdqsmaskcnten_HSH;
      break;

    case GsmIocLp4DqOverrideData:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL5_DdrDqOvrdData_HSH;
      break;

    case GsmIocLp4DqOverrideEn:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL5_DdrDqOvrdModeEn_HSH;
      break;

    case GsmIocRankOverrideEn:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL6_RankOvrd_HSH;
      break;

    case GsmIocRankOverrideVal:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL6_RankValue_HSH;
      break;

    case GsmIocDataCtlGear1:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL6_Gear1_HSH;
      break;

    case GsmIocLpEarlyRLeak:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL0_EarlyRleakEn_HSH;
      break;

    case GsmIocOdtSampExtEn:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL0_OdtSampExtendEn_HSH;
      break;

    case GsmIocDqsOdtSampExtEn:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL3_DqsOdtSampExtendEn_HSH;
      break;

    case GsmIocTxOn:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL0_TxOn_HSH;
      break;

    case GsmIocSenseAmpMode:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL0_SenseampTrainingMode_HSH;
      break;

    case GsmIocReadLevelMode:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL0_RLTrainingMode_HSH;
      break;

    case GsmIocXoverMinDelayCtl:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL0_xover_mindelay_ctl_HSH;
      break;


    case GsmIocWriteLevelMode:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL0_WLTrainingMode_HSH;
      break;

    case GsmIocReadDqDqsMode:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL0_RxTrainingMode_HSH;
      break;

    case GsmIocForceOdtOn:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL0_ForceOdtOn_HSH;
      break;

    case GsmIocRxPiPwrDnDis:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL0_RxPiOn_HSH;
      break;

    case GsmIocTxPiPwrDnDis:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL0_TxPiOn_HSH;
      break;

    case GsmIocInternalClocksOn:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL0_InternalClocksOn_HSH;
      break;

    case GsmIocTxDisable:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL0_TxDisable_HSH;
      break;

    case GsmIocDllMask:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL1_DllMask_HSH;
      break;

    case GsmIocStrongWeakLeaker:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL3_StrongWkLeaker_HSH;
      break;

    case GsmIocStrongWeakLeakerMsb:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL6_strongwkleakermsb_HSH;
      break;

    case GsmIocRcvenFourCycleFill:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL3_rcven_four_cycle_fill_HSH;
      break;

    case GsmIocEnRcvenPreZeroFill:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL8_en_rcvenpre_zero_fill_HSH;
      break;

    case GsmIocSdllSegmentDisable:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL1_SdllSegmentDisable_HSH;
      break;

    case GsmIocDllWeakLock:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL1_DllWeakLock_HSH;
      break;

    case GsmIocLpLongOdtEn:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL2_LpDdrLongOdtEn_HSH;
      break;

    case GsmIocRxClkStg:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL2_RxClkStgNum_HSH;
      break;

    case GsmIocRxClkStgNumMsb:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL3_rxclkstgnummsb_HSH;
      break;

    case GsmIocLeakerComp:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL3_LeakerComp_HSH;
      break;

    case GsmIocLeakerWithTxAnalogEn:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL4_leakerwithtxanalogen_HSH;
      break;

    case GsmIocStrong2WeakOnDqsOdt:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL3_Strong2WeakOnDqsOdt_HSH;
      break;

    case GsmIocForceDqsOnQuickOdtOff:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL3_ForceDqsOnQuickOdtOff_HSH;
      break;

    case GsmIocLongWrPreambleLp4:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL4_lpddr4wrlongpreambleen_HSH;
      break;

    case GsmIocRxBiasSel:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL4_dllnbiassel_HSH;
        break;

    case GsmIocDataVddqOdtEn:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL2_EnVddqOdt_HSH;
      break;

    case GsmIocDataVttOdtEn:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL2_EnVttOdt_HSH;
      break;

    case GsmIocRxVrefMFC:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL2_RxVrefProgMFC_HSH;
      break;

    case GsmIocVrefPwrDnEn:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL2_EnableVrefPwrDn_HSH;
      break;

    case GsmIocDataCtlDdr4Mode:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL2_Ddr4Mode_HSH;
      break;

    case GsmIocConstZTxEqEn:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL2_EnConstZEqTx_HSH;
      break;

    case GsmIocRxDeskewDis:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL2_RxDeskewDisable_HSH;
      break;

    case GsmIocTxDeskewDis:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL2_TxDeskewDisable_HSH;
      break;

    case GsmIocForceRxAmpOn:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL2_ForceRxOn_HSH;
      break;

    case GsmIocForceBiasOn:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL2_ForceBiasOn_HSH;
      break;

    case GsmIocDqSlewDlyByPass:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL2_DqSlewDlyByPass_HSH;
      break;

    case GsmIocWlLongDelEn:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL2_WlLongDelEn_HSH;
      break;

    case GsmIocTxEqDis:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL2_TxEqDis_HSH;
      break;

    case GsmIocRxStaggerCtl:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL2_RxStaggerCtl_HSH;
      break;

    case GsmIocRxDeskewCal:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL4_rxdeskewcal_HSH;
      break;

    case GsmIocTxDeskewCal:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL4_txdeskewcal_HSH;
      break;

    case GsmIocVssOdtEn:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL4_VssODTEn_HSH;
      break;

    case GsmIocGlobalClkEn:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL4_glbdrv_clkgate_enable_HSH;
      break;

    case GsmIocRxTypeSelect:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL4_rxsel_HSH;
      break;

    case GsmIocDataCtlLp4Mode:
      HashPtr->Data = DDRDATA0CH0_CR_DDRCRDATACONTROL4_LpDdr4Mode_HSH;
      break;

    case GsmIocIoReset:
      HashPtr->Data = DDRSCRAM_CR_DDRMISCCONTROL1_io_train_rst_HSH;
      break;

    case GsmIocTxVrefConverge:          // @todo Can remove when ICL A0 support is dropped
      if (Channel == 0) {
        HashPtr->Data = DDRVREF_CR_DDRCRVREFADJUST2_ch0SlowBW_HSH_A0;
      } else {
        HashPtr->Data = DDRVREF_CR_DDRCRVREFADJUST2_ch1SlowBW_HSH_A0;
      }
      break;

    case GsmIocCmdVrefConverge:
      if (MrcData->Inputs.IclA0) {
        HashPtr->Data = DDRVREF_CR_DDRCRVREFADJUST2_caSlowBW_HSH_A0;
      } else if (Rank < MAX_RANK_IN_CHANNEL) {
        HashPtr->Data = CaVrefConvergeHsh[Channel][RANK_TO_DIMM_NUMBER (Rank)];
      } else {
        Status = mrcWrongInputParameter;
      }
      break;

    case GsmIocCompClkOn:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL1_CompClkOn_HSH;
      break;

    case GsmIocCompVccddqLo:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL1_VccddqLo_HSH;
      break;

    case GsmIocDisableQuickComp:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL1_DisableQuickComp_HSH;
      break;

    case GsmIocSinStep:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL1_SinStep_HSH;
      break;

    case GsmIocSinStepAdv:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL1_SinStepAdv_HSH;
      break;

    case GsmIocCompOdtStaticDis:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL0_DisableOdtStatic_HSH;
      break;

    case GsmIocFixOdtD:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL0_FixOdtD_HSH;
      break;

    case GsmIocOdtOverride:
      HashPtr->Data = CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_Override_HSH;
      break;

    case GsmIocOdtOn:
      HashPtr->Data = CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_On_HSH;
      break;

    case GsmIocMprTrainDdrOn:
      HashPtr->Data = CH0_CR_REUT_CH_MISC_ODT_CTRL_MPR_Train_DDR_On_HSH;
      break;

    case GsmIocCkeOverride:
      HashPtr->Data = CH0_CR_REUT_CH_MISC_CKE_CTRL_CKE_Override_HSH;
      break;

    case GsmIocCkeOn:
      HashPtr->Data = CH0_CR_REUT_CH_MISC_CKE_CTRL_CKE_On_HSH;
      break;

    case GsmIocDqOdtUpDnOff:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL0_DqOdtUpDnOff_HSH;
      break;

    case GsmIocPanicDrvUpVref:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL2_PanicDrvUpVref_HSH;
      break;

    case GsmIocCompVddqOdtEn:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL2_EnVddqOdt_HSH;
      break;

    case GsmIocCompVttOdtEn:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL2_EnVttOdt_HSH;
      break;

    case GsmIocVttPanicCompUpMult:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL2_VttPanicCompUpMult_HSH;
      break;

    case GsmIocVttPanicCompDnMult:
      HashPtr->Data = DDRPHY_COMP_CR_DDRCRCOMPCTL2_VttPanicCompDnMult_HSH;
      break;

    case GsmIocRptChRepClkOn:
      HashPtr->Data = MCMISCS_WRITECFGCH0_RptChRepClkOn_HSH;
      break;

    case GsmIocCmdAnlgEnGraceCnt:
      HashPtr->Data = MCMISCS_WRITECFGCH0_CmdAnlgEnGraceCnt_HSH;
      break;

    case GsmIocTxAnlgEnGraceCnt:
      HashPtr->Data = MCMISCS_WRITECFGCH0_TxAnlgEnGraceCnt_HSH;
      break;

    case GsmIocTxDqFifoRdEnPerRankDelDis:
      HashPtr->Data = MCMISCS_WRITECFGCH0_TxDqFifoRdEnPerRankDelDis_HSH;
      break;

    case GsmIocDccTrainingMode:
      HashPtr->Data = MCMISCS_DCCCONTROL0_TrainingMode_HSH;
      break;

    case GsmIocDccTrainingDone:
      HashPtr->Data = MCMISCS_DCCCONTROL0_TrainingDone_HSH;
      break;

    case GsmIocDccDrain:
      HashPtr->Data = MCMISCS_DCCCONTROL0_Drain_HSH;
      break;

    case GsmIocDccActiveClks:
      HashPtr->Data = MCMISCS_DCCMAINFSMCONTROL0_ActiveClks_HSH;
      break;

    case GsmIocDccActiveBytes:
      HashPtr->Data = MCMISCS_DCCMAINFSMCONTROL0_ActiveBytes_HSH;
      break;

    case GsmIocDccDcoCompEn:
      HashPtr->Data = MCMISCS_DCCMAINFSMCONTROL0_DcoCompEn_HSH;
      break;

    case GsmIocDccPeriodicDis:
      HashPtr->Data = MCMISCS_DCCMAINFSMCONTROL0_PriodicDis_HSH;
      break;

    case GsmIocDccDcoLfsrDis:
      HashPtr->Data = MCMISCS_DCCCONTROL0_DcoLfsrDis_HSH;
      break;

    case GsmIocDccClkTrainVal:
      // Rank is MRC_IGNORE_ARG, Strobe is the one that is valid
      if (Strobe == 0) {
        HashPtr->Data = DDRCLKCH0_CR_DCCCLKTRAINVAL0_Clk0DccVal_HSH;
      } else if (Strobe == 1) {
        HashPtr->Data = DDRCLKCH0_CR_DCCCLKTRAINVAL0_Clk1DccVal_HSH;
      } else if (Strobe == 2) {
        //@todo H/S sku code
        Status = mrcWrongInputParameter;
      } else {
        //@todo H/S sku code
        Status = mrcWrongInputParameter;
      }
      break;

    case GsmIocDccDataTrainDqsVal:
      HashPtr->Data = DDRDATA0CH0_CR_DCCDATATRAINVAL1RANK0_DqsDccVal_HSH;
      break;

    case GsmIocDccDqsReplica:
      HashPtr->Data = DDRDATA0CH0_CR_DCCDATATRAINVAL1RANK0_ReplicaShadowDccVal_HSH;
      break;

    case GsmIocDccAipCb:
      if (Strobe == 0) {
        HashPtr->Data = DDRCLKCH0_CR_DCCCLKCONTROL1_Rank0DccAipCb_HSH;
      } else if (Strobe == 1) {
        HashPtr->Data = DDRCLKCH0_CR_DCCCLKTRAINVAL0_Rank1DccAipCb_HSH;
      } else if (Strobe == 2) {
        HashPtr->Data = DDRCTLCLKCKE0_CR_DCCCLKCONTROL1_Rank0DccAipCb_HSH;
      } else if (Strobe == 3) {
        HashPtr->Data = DDRCTLCLKCKE0_CR_DCCCLKTRAINVAL0_Rank1DccAipCb_HSH;
      } else {
        Status = mrcWrongInputParameter;
      }
      break;

    case GsmIocDccAipCbDqs:
      HashPtr->Data = DDRDATA0CH0_CR_DCCDATATRAINVAL1RANK0_DqsDccAipCb_HSH;
      break;

    // These are unused.  Need to finish HAL if these fields are accessed.
    default:
      Status = mrcWrongInputParameter;
      break;
  }

  if (Status == mrcSuccess) {
    CrOffset = MrcGetDdrIoConfigOffsets (MrcData, Group, Socket, Channel, SubChannel, Rank, Strobe, Bit, FreqIndex);
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Hash is undefined: Group %s(%d) Channel %u Rank %u Strobe %u\n", gErrString, GsmGtDebugStrings[Group], Group, Channel, Rank, Strobe);
  }
  if (CrOffset > 0xFFFF) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Bad Offset = 0x%08X Group %s(%d) Channel %u Rank %u Strobe %u\n", gErrString, CrOffset, GsmGtDebugStrings[Group], Group, Channel, Rank, Strobe);
    CrOffset = MRC_UINT32_MAX;
  }

  HashPtr->Bits.Offset  = CrOffset;

  return Status;
}

/**
  This function generates the hash used to execute the Get/Set function.
  The hash consists of: Register Offset, BitField start bit, BitField length.

  @param[in]  MrcData   - Pointer to global data.
  @param[in]  Group     - MC Timing group to access.
  @param[in]  Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel   - DDR Channel Number within the processor socket (0-based).
  @param[out] HashVal   - Pointer to return the MMIO access instruction.

  @retval MrcStatus
**/
MrcStatus
MrcGetMcTimingHash (
  IN  MrcParameters   *const  MrcData,
  IN  GSM_GT          const   Group,
  IN  UINT32          const   Socket,
  IN  UINT32          const   Channel,
  IN  UINT32          const   FreqIndex,
  OUT UINT32          *const  HashVal
  )
{
  MrcStatus Status;
  MrcDebug  *Debug;
  MRC_REGISTER_HASH_STRUCT *HashPtr;
  UINT32  CrOffset;

  Debug   = &MrcData->Outputs.Debug;
  Status  = mrcSuccess;
  HashPtr = (MRC_REGISTER_HASH_STRUCT *) HashVal;
  CrOffset = MRC_UINT32_MAX;

  switch (Group) {
    case GsmMctRP:
      HashPtr->Data = CH0_CR_TC_PRE_tRP_HSH;
      break;

    case GsmMctRCDwr:
      HashPtr->Data = CH0_CR_TC_ACT_tRCD_wr_HSH;
      break;

    case GsmMctRFCpb:
      HashPtr->Data = CH0_CR_SC_PBR_tRFCpb_HSH;
      break;

    case GsmMctRPabExt:
      HashPtr->Data = CH0_CR_TC_PRE_tRPab_ext_HSH;
      break;

    case GsmMctRAS:
      HashPtr->Data = CH0_CR_TC_PRE_tRAS_HSH;
      break;

    case GsmMctRDPRE:
      HashPtr->Data = CH0_CR_TC_PRE_tRDPRE_HSH;
      break;

    case GsmMctPPD:
      HashPtr->Data = CH0_CR_TC_PRE_tPPD_HSH;
      break;

    case GsmMctWRPRE:
      HashPtr->Data = CH0_CR_TC_PRE_tWRPRE_HSH;
      break;

    case GsmMctFAW:
      HashPtr->Data = CH0_CR_TC_ACT_tFAW_HSH;
      break;

    case GsmMctRRDsg:
      HashPtr->Data = CH0_CR_TC_ACT_tRRD_sg_HSH;
      break;

    case GsmMctRRDdg:
      HashPtr->Data = CH0_CR_TC_ACT_tRRD_dg_HSH;
      break;

    case GsmMctLpDeratingExt:
      HashPtr->Data = CH0_CR_TC_ACT_derating_ext_HSH;
      break;

    case GsmMctRDRDsg:
      HashPtr->Data = CH0_CR_TC_RDRD_tRDRD_sg_HSH;
      break;

    case GsmMctRDRDdg:
      HashPtr->Data = CH0_CR_TC_RDRD_tRDRD_dg_HSH;
      break;

    case GsmMctRDRDdr:
      HashPtr->Data = CH0_CR_TC_RDRD_tRDRD_dr_HSH;
      break;

    case GsmMctRDRDdd:
      HashPtr->Data = CH0_CR_TC_RDRD_tRDRD_dd_HSH;
      break;

    case GsmMctRDWRsg:
      HashPtr->Data = CH0_CR_TC_RDWR_tRDWR_sg_HSH;
      break;

    case GsmMctRDWRdg:
      HashPtr->Data = CH0_CR_TC_RDWR_tRDWR_dg_HSH;
      break;

    case GsmMctRDWRdr:
      HashPtr->Data = CH0_CR_TC_RDWR_tRDWR_dr_HSH;
      break;

    case GsmMctRDWRdd:
      HashPtr->Data = CH0_CR_TC_RDWR_tRDWR_dd_HSH;
      break;

    case GsmMctWRRDsg:
      HashPtr->Data = CH0_CR_TC_WRRD_tWRRD_sg_HSH;
      break;

    case GsmMctWRRDdg:
      HashPtr->Data = CH0_CR_TC_WRRD_tWRRD_dg_HSH;
      break;

    case GsmMctWRRDdr:
      HashPtr->Data = CH0_CR_TC_WRRD_tWRRD_dr_HSH;
      break;

    case GsmMctWRRDdd:
      HashPtr->Data = CH0_CR_TC_WRRD_tWRRD_dd_HSH;
      break;

    case GsmMctWRWRsg:
      HashPtr->Data = CH0_CR_TC_WRWR_tWRWR_sg_HSH;
      break;

    case GsmMctWRWRdg:
      HashPtr->Data = CH0_CR_TC_WRWR_tWRWR_dg_HSH;
      break;

    case GsmMctWRWRdr:
      HashPtr->Data = CH0_CR_TC_WRWR_tWRWR_dr_HSH;
      break;

    case GsmMctWRWRdd:
      HashPtr->Data = CH0_CR_TC_WRWR_tWRWR_dd_HSH;
      break;

    case GsmMctOdtRdDuration:
      HashPtr->Data = CH0_CR_TC_ODT_ODT_read_duration_HSH;
      break;

    case GsmMctOdtRdDelay:
      HashPtr->Data = CH0_CR_TC_ODT_ODT_Read_Delay_HSH;
      break;

    case GsmMctWrEarlyOdt:
      HashPtr->Data = CH0_CR_TC_ODT_Write_Early_ODT_HSH;
      break;

    case GsmMctOdtWrDuration:
      HashPtr->Data = CH0_CR_TC_ODT_ODT_write_duration_HSH;
      break;

    case GsmMctOdtWrDelay:
      HashPtr->Data = CH0_CR_TC_ODT_ODT_Write_Delay_HSH;
      break;

    case GsmMctCL:
      HashPtr->Data = CH0_CR_TC_ODT_tCL_HSH;
      break;

    case GsmMctCWL:
      HashPtr->Data = CH0_CR_TC_ODT_tCWL_HSH;
      break;

    case GsmMctAONPD:
      HashPtr->Data = CH0_CR_TC_ODT_tAONPD_HSH;
      break;

    case GsmMctCKE:
      HashPtr->Data = CH0_CR_TC_PWRDN_tCKE_HSH;
      break;

    case GsmMctXP:
      HashPtr->Data = CH0_CR_TC_PWRDN_tXP_HSH;
      break;

    case GsmMctXPDLL:
      HashPtr->Data = CH0_CR_TC_PWRDN_tXPDLL_HSH;
      break;

    case GsmMctPRPDEN:
      HashPtr->Data = CH0_CR_TC_PWRDN_tPRPDEN_HSH;
      break;

    case GsmMctRDPDEN:
      HashPtr->Data = CH0_CR_TC_PWRDN_tRDPDEN_HSH;
      break;

    case GsmMctWRPDEN:
      HashPtr->Data = CH0_CR_TC_PWRDN_tWRPDEN_HSH;
      break;

    case GsmMctXSDLL:
      HashPtr->Data = CH0_CR_TC_SRFTP_tXSDLL_HSH;
      break;

    case GsmMctXSR:
      HashPtr->Data = CH0_CR_TC_SREXITTP_tXSR_HSH;
      break;

    case GsmMctZQOPER:
      HashPtr->Data = CH0_CR_TC_SRFTP_tZQOPER_HSH;
      break;

    case GsmMctMOD:
      HashPtr->Data = CH0_CR_TC_SRFTP_tMOD_HSH;
      break;

    case GsmMctZQCAL:
      HashPtr->Data = CH0_CR_TC_ZQCAL_tZQCAL_HSH;
      break;

    case GsmMctZQCS:
      HashPtr->Data = CH0_CR_TC_ZQCAL_tZQCS_HSH;
      break;

    case GsmMctZQCSPeriod:
      HashPtr->Data = CH0_CR_TC_ZQCAL_ZQCS_period_HSH;
      break;

    case GsmMctCPDED:
      HashPtr->Data = CH0_CR_SC_GS_CFG_tCPDED_HSH;
      break;

    case GsmMctCAL:
      HashPtr->Data = CH0_CR_SC_GS_CFG_tCAL_HSH;
      break;

    case GsmMctCKCKEH:
      HashPtr->Data = CH0_CR_SC_GS_CFG_ck_to_cke_HSH;
      break;

    case GsmMctCSCKEH:
      HashPtr->Data = CH0_CR_SC_GS_CFG_cs_to_cke_HSH;
      break;

    case GsmMctSrIdle:
      HashPtr->Data = PM_SREF_CONFIG_Idle_timer_HSH;
      break;

    case GsmMctREFI:
      HashPtr->Data = CH0_CR_TC_RFTP_tREFI_HSH;
      break;

    case GsmMctRFC:
      HashPtr->Data = CH0_CR_TC_RFTP_tRFC_HSH;
      break;

    case GsmMctOrefRi:
      HashPtr->Data = CH0_CR_TC_RFP_OREF_RI_HSH;
      break;

    case GsmMctRefreshHpWm:
      HashPtr->Data = CH0_CR_TC_RFP_Refresh_HP_WM_HSH;
      break;

    case GsmMctRefreshPanicWm:
      HashPtr->Data = CH0_CR_TC_RFP_Refresh_panic_wm_HSH;
      break;

    case GsmMctREFIx9:
      HashPtr->Data = CH0_CR_TC_RFP_tREFIx9_HSH;
      break;

    default:
      HashPtr->Data = MRC_UINT32_MAX;
      Status = mrcWrongInputParameter;
      break;
  }

  if (Status == mrcSuccess) {
    CrOffset = MrcGetMcTimingRegOffset (MrcData, Group, Socket, Channel, FreqIndex);
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Hash is undefined: Group %s(%d) Channel %u\n", gErrString, GsmGtDebugStrings[Group], Group, Channel);
  }
  if (CrOffset > 0xFFFF) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Bad Offset = 0x%08X Group %s(%d) Channel %u\n", gErrString, CrOffset, GsmGtDebugStrings[Group], Group, Channel);
    CrOffset = MRC_UINT32_MAX;
  }

  HashPtr->Bits.Offset = CrOffset;

  return Status;
}

/**
  This function returns the hash used to execute the Get/Set function.
  The hash consists of: Register Offset, BitField start bit, BitField length.

  @param[in]  MrcData   - Pointer to global data.
  @param[in]  Group     - MC Timing group to access.
  @param[in]  Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel   - DDR Channel Number within the processor socket (0-based).
  @param[in]  FreqIndex - Index supporting multiple operating frequencies. (Not used in Client CPU's)
  @param[out] HashVal   - Pointer to return the MMIO access instruction.

  @retval MrcStatus
**/
MrcStatus
MrcGetMcConfigHash (
  IN  MrcParameters   *const  MrcData,
  IN  GSM_GT          const   Group,
  IN  UINT32          const   Socket,
  IN  UINT32          const   Channel,
  IN  UINT32          const   FreqIndex,
  OUT UINT32          *const  HashVal
  )
{
  MrcStatus Status;
  MrcDebug  *Debug;
  MRC_REGISTER_HASH_STRUCT *HashPtr;
  UINT32 CrOffset;

  Debug   = &MrcData->Outputs.Debug;
  Status  = mrcSuccess;
  HashPtr = (MRC_REGISTER_HASH_STRUCT *) HashVal;
  CrOffset = MRC_UINT32_MAX;

  switch (Group) {
    case GsmMccDramType:
      HashPtr->Data = CH0_CR_SC_GS_CFG_DRAM_technology_HSH;
      break;

    case GsmMccCmdStretch:
      HashPtr->Data = CH0_CR_SC_GS_CFG_CMD_stretch_HSH;
      break;

    case GsmMccCmdGapRatio:
      HashPtr->Data = CH0_CR_SC_GS_CFG_N_to_1_ratio_HSH;
      break;

    case GsmMccAddrMirror:
      HashPtr->Data = CH0_CR_SC_GS_CFG_Address_mirror_HSH;
      break;

    case GsmMccCmdTriStateDis:
      HashPtr->Data = CH0_CR_SC_GS_CFG_disable_tristate_HSH;
      break;

    case GsmMccCmdTriStateDisTrain:
      HashPtr->Data = CH0_CR_SC_GS_CFG_TRAINING_disable_tristate_HSH;
      break;

    case GsmMccFreqPoint:
      HashPtr->Data = CH0_CR_SC_GS_CFG_frequency_point_HSH;
      break;

    case GsmMccEnableOdtMatrix:
      HashPtr->Data = CH0_CR_SC_GS_CFG_enable_odt_matrix_HSH;
      break;

    case GsmMccX8Device:
      HashPtr->Data = CH0_CR_SC_GS_CFG_x8_device_HSH;
      break;

    case GsmMccGear2:
      HashPtr->Data = CH0_CR_SC_GS_CFG_gear2_HSH;
      break;

    case GsmMccDdr4OneDpc:
      HashPtr->Data = CH0_CR_SC_GS_CFG_ddr4_1dpc_HSH;
      break;

    case GsmMccLDimmMap:
      HashPtr->Data = MAD_INTRA_CH0_DIMM_L_MAP_HSH;
      break;

    case GsmMccRankInterleave:
      HashPtr->Data = MAD_INTRA_CH0_RI_HSH;
      break;

    case GsmMccEnhancedInterleave:
      HashPtr->Data = MAD_INTRA_CH0_EIM_HSH;
      break;

    case GsmMccEccMode:
      HashPtr->Data = MAD_INTRA_CH0_ECC_HSH;
      break;

    case GsmMccAddrDecodeDdrType:
      HashPtr->Data = MAD_INTER_CHANNEL_DDR_TYPE_HSH;
      break;

    case GsmMccEnhChannelMode:
      HashPtr->Data = MAD_INTER_CHANNEL_ECHM_HSH;
      break;

    case GsmMccStackedMode:
      HashPtr->Data = MAD_INTER_CHANNEL_STKD_MODE_HSH;
      break;

    case GsmMccStackChMap:
      HashPtr->Data = MAD_INTER_CHANNEL_STKD_MODE_CH1_HSH;
      break;

    case GsmMccLChannelMap:
      HashPtr->Data = MAD_INTER_CHANNEL_CH_L_MAP_HSH;
      break;

    case GsmMccSChannelSize:
      HashPtr->Data = MAD_INTER_CHANNEL_CH_S_SIZE_HSH;
      break;

    case GsmMccStackedChHash:
      HashPtr->Data = MAD_INTER_CHANNEL_STKD_MODE_CH_BITS_HSH;
      break;

    case GsmMccLDimmSize:
      HashPtr->Data = MAD_DIMM_CH0_DIMM_L_SIZE_HSH;
      break;

    case GsmMccLDimmDramWidth:
      HashPtr->Data = MAD_DIMM_CH0_DLW_HSH;
      break;

    case GsmMccLDimmRankCnt:
      HashPtr->Data = MAD_DIMM_CH0_DLNOR_HSH;
      break;

    case GsmMccLDimm8Gb:
      HashPtr->Data = MAD_DIMM_CH0_DL8Gb_HSH;
      break;

    case GsmMccSDimmSize:
      HashPtr->Data = MAD_DIMM_CH0_DIMM_S_SIZE_HSH;
      break;

    case GsmMccSDimmDramWidth:
      HashPtr->Data = MAD_DIMM_CH0_DSW_HSH;
      break;

    case GsmMccSDimmRankCnt:
      HashPtr->Data = MAD_DIMM_CH0_DSNOR_HSH;
      break;

    case GsmMccSDimm8Gb:
      HashPtr->Data = MAD_DIMM_CH0_DS8Gb_HSH;
      break;

    case GsmMccPuMrcDone:
      HashPtr->Data = MC_INIT_STATE_G_pu_mrc_done_HSH;
      break;

    case GsmMccSaveFreqPoint:
      switch (FreqIndex) {
        case 0:
          HashPtr->Data = MC_INIT_STATE_G_mrc_save_low_HSH;
          break;

        case 1:
          HashPtr->Data = MC_INIT_STATE_G_mrc_save_med_HSH;
          break;

        case 2:
          HashPtr->Data = MC_INIT_STATE_G_mrc_save_high_HSH;
          break;

        default:
          Status = mrcWrongInputParameter;
          break;
      }
      break;

    case GsmMccEnableSr:
      HashPtr->Data = PM_SREF_CONFIG_SR_Enable_HSH;
      break;

    case GsmMccEnableRefresh:
      HashPtr->Data = MC_INIT_STATE_G_refresh_enable_HSH;
      break;

    case GsmMccMcInitDoneAck:
      HashPtr->Data = MC_INIT_STATE_G_mc_init_done_ack_HSH;
      break;

    case GsmMccMrcDone:
      HashPtr->Data = MC_INIT_STATE_G_mrc_done_HSH;
      break;

    case GsmMccEnableDclk:
      HashPtr->Data = MC_INIT_STATE_G_dclk_enable_HSH;
      break;

    case GsmMccPureSrx:
      HashPtr->Data = MC_INIT_STATE_G_pure_srx_HSH;
      break;

    case GsmMccLp4FifoRdWr:
      HashPtr->Data = CH0_CR_SC_GS_CFG_TRAINING_lp4_fifo_rd_wr_HSH;
      break;

    case GsmMccIgnoreCke:
      HashPtr->Data = CH0_CR_SC_GS_CFG_TRAINING_ignore_cke_HSH;
      break;

    case GsmMccMaskCs:
      HashPtr->Data = CH0_CR_SC_GS_CFG_TRAINING_mask_cs_HSH;
      break;

    case GsmMccCpgcInOrder:
      HashPtr->Data = CH0_CR_SC_GS_CFG_TRAINING_cpgc_in_order_HSH;
      break;

    case GsmMccCadbEnable:
      HashPtr->Data = CH0_CR_SC_GS_CFG_TRAINING_cadb_enable_HSH;
      break;

    case GsmMccDeselectEnable:
      HashPtr->Data = CH0_CR_SC_GS_CFG_TRAINING_deselect_enable_HSH;
      break;

    case GsmMccBusRetainOnBubble:
      HashPtr->Data = CH0_CR_SC_GS_CFG_TRAINING_bus_retain_on_n_to_1_bubble_HSH;
      break;

    case GsmMccLpddr2nCsMrw:
      HashPtr->Data = CH0_CR_SC_GS_CFG_TRAINING_LPDDR_2N_CS_MRW_HSH;
      break;

    case GsmMccBlockXarb:
      HashPtr->Data = CH0_CR_SC_GS_CFG_TRAINING_Block_xarb_HSH;
      break;

    case GsmMccResetOnCmd:
      HashPtr->Data = CH0_CR_SC_GS_CFG_TRAINING_reset_on_command_HSH;
      break;

    case GsmMccResetDelay:
      HashPtr->Data = CH0_CR_SC_GS_CFG_TRAINING_reset_delay_HSH;
      break;

    case GsmMccRankOccupancy:
      HashPtr->Data = CH0_CR_MC_INIT_STATE_Rank_occupancy_HSH;
      break;

    case GsmMccRefInterval:
      HashPtr->Data = CH0_CR_MC_REFRESH_STAGGER_Ref_Interval_HSH;
      break;

    case GsmMccRefStaggerEn:
      HashPtr->Data = CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_En_HSH;
      break;

    case GsmMccRefStaggerMode:
      HashPtr->Data = CH0_CR_MC_REFRESH_STAGGER_Ref_Stagger_Mode_HSH;
      break;

    case GsmMccDisableStolenRefresh:
      HashPtr->Data = CH0_CR_MC_REFRESH_STAGGER_Disable_Stolen_Refresh_HSH;
      break;

    case GsmMccEnRefTypeDisplay:
      HashPtr->Data = CH0_CR_MC_REFRESH_STAGGER_En_Ref_Type_Display_HSH;
      break;

    case GsmMccHashMask:
      HashPtr->Data = CHANNEL_HASH_HASH_MASK_HSH;
      break;

    case GsmMccLsbMaskBit:
      HashPtr->Data = CHANNEL_HASH_HASH_LSB_MASK_BIT_HSH;
      break;

    case GsmMccHashMode:
      HashPtr->Data = CHANNEL_HASH_HASH_MODE_HSH;
      break;

    case GsmMccMr2Shadow:
      HashPtr->Data = CH0_CR_TC_MR2_SHADDOW_MR2_shaddow_HSH;
      break;

    case GsmMccSrtAvail:
      HashPtr->Data = CH0_CR_TC_MR2_SHADDOW_SRT_avail_HSH;
      break;

    case GsmMccDisableCkTristate:
      HashPtr->Data = CH0_CR_SCHED_SECOND_CBIT_dis_ck_tristate_HSH;
      break;

    case GsmMccPbrDis:
      HashPtr->Data = CH0_CR_SC_PBR_PBR_Disable_HSH;
      break;

    // These are unused.  Need to finish HAL if these fields are accessed.
    case GsmMccDdrReset:
    case GsmMccSafeSr:

    default:
      HashPtr->Data = MRC_UINT32_MAX;
      Status = mrcWrongInputParameter;
      break;
  }

  if (Status == mrcSuccess) {
    CrOffset = MrcGetMcConfigRegOffset (MrcData, Group, Socket, Channel, FreqIndex);
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Hash is undefined: Group %s(%d) Channel %u\n", gErrString, GsmGtDebugStrings[Group], Group, Channel);
  }
  if (CrOffset > 0xFFFF) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Bad Offset = 0x%08X Group %s(%d) Channel %u\n", gErrString, CrOffset, GsmGtDebugStrings[Group], Group, Channel);
    CrOffset = MRC_UINT32_MAX;
  }

  HashPtr->Bits.Offset = CrOffset;

  return Status;
}

///
/// Public Functions
///
/**
  This function is the interface for the core of the MRC to get the limits of a
  specific GSM_GT parameter.

  @param[in]  MrcData   - Pointer to global data.
  @param[in]  Group     - DDRIO group to access.
  @param[out] MinVal    - Return pointer for Minimum Value supported.
  @param[out] MaxVal    - Return pointer for Maximum Value supported.
  @param[out] WaitTime  - Return pointer for settle time required in microseconds.

  @retval MrcStatus - mrcSuccess if the parameter is found, otherwise mrcFail.
**/
MrcStatus
MrcGetSetLimits (
  IN  MrcParameters *const MrcData,
  IN  GSM_GT  const   Group,
  OUT INT64   *const  MinVal,
  OUT INT64   *const  MaxVal,
  OUT UINT32  *const  WaitTime
  )
{
  MrcStatus Status;

  Status = mrcSuccess;

  if (Group < EndOfPhyMarker) {
    MrcGetDdrIoGroupLimits (MrcData, Group, MinVal, MaxVal, WaitTime);
  } else if (Group < EndOfIocMarker) {
    MrcGetDdrIoCfgGroupLimits (MrcData, Group, MinVal, MaxVal, WaitTime);
  } else if (Group < EndOfMctMarker) {
    MrcGetMcTimingGroupLimits (MrcData, Group, MinVal, MaxVal, WaitTime);
  } else if (Group < EndOfMccMarker) {
    MrcGetMcConfigGroupLimits (MrcData, Group, MinVal, MaxVal, WaitTime);
  } else {
    MrcGetComplexGroupLimits (MrcData, Group, MinVal, MaxVal, WaitTime);
  }

  return Status;
}

/**
  Get the corresponding register group and channel (register field) for a given VrefType and Channel
  based on Inputs->CaVrefConfig parameter.
  CaVrefConfig must be configured correctly for the DRAM Type
  See MrcCheckInputParams() for details.

  @param[in, out] MrcData  - Include all MRC global data.
  @param[in]      Channel  - Channel to search in.
  @param[in]      VrefType - TxVref of CmdVref
  @param[in, out] Group     - The corresponding register group
  @param[in, out] GetSetCh  - The corresponding channel in terms of register field
**/
void
GetChGroupTxVCmdV (
  IN     MrcParameters *const MrcData,
  IN     UINT8                Channel,
  IN     UINT8                VrefType,
  IN OUT GSM_GT*              Group,
  IN OUT UINT8*               GetSetCh
)
{
  MrcInput            *Inputs;
  MrcOutput           *Outputs;
  MrcDebug            *Debug;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  switch (Inputs->CaVrefConfig) {
  case 0:
    // CAVrefIntCtl (CmdVref, Ch 0) controls CmdVref of both Ch 0 and Ch 1
    // Ch0VrefIntCtl (TxVref, Ch0) and Ch1VrefIntCtl (TxVref, Ch1) control DQ Vref of Ch0 and Ch1 respectively
    *Group    = (VrefType == WrV) ? TxVref : CmdVref;
    *GetSetCh = (*Group == TxVref) ? Channel : 0;
    break;

  case 1:
    // CAVrefIntCtl (CmdVref, Ch0) and Ch0VrefIntCtl (TxVref, Ch0) control CmdVref of Ch 0 and Ch 1 respectively
    *Group    = (Channel == 0) ? CmdVref : TxVref;
    *GetSetCh = 0;
    break;

  case 2:
    // CAVrefIntCtl (CmdVref, Ch0) and Ch1VrefIntCtl (TxVref, Ch1) control CmdVref of Ch 0 and Ch 1 respectively
    *Group    = (Channel == 0) ? CmdVref : TxVref;
    *GetSetCh = (*Group == TxVref) ? 1 : 0;
    break;

  default:
    MRC_DEBUG_ASSERT (
      (1 == 0),
      Debug,
      "Invalid Inputs->CaVrefConfig %u", Inputs->CaVrefConfig
      );
    break;
  }

  if (!Inputs->IclA0) {
    // CaVref is per channel / DIMM from ICL B0 and on
    *Group    = CmdVref;
    *GetSetCh = Channel;
  }
}


#ifdef MRC_DEBUG_PRINT
/**
  This function outputs the specified group values to the debug print device.

  @param[in] MrcData   - Pointer to global data.
  @param[in] Group     - DDRIO group to access.
  @param[in] Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in] Channel   - DDR Channel Number within the processor socket (0-based).
  @param[in] Rank      - Rank number within a channel (0-based).
  @param[in] Strobe    - Dqs data group within the rank (0-based).
  @param[in] Bit       - Bit index within the data group (0-based).
  @param[in] FreqIndex - Index supporting multiple operating frequencies. (Not used in Client CPU's)

  @retval MrcStatus
**/
MrcStatus
MrcPrintDdrIoGroup (
  IN MrcParameters *const  MrcData,
  IN UINT32  const Socket,
  IN UINT32  const Channel,
  IN UINT32  const Rank,
  IN UINT32  const Strobe,
  IN UINT32  const Bit,
  IN UINT32  const FreqIndex,
  IN GSM_GT  const Group
  )
{
  MrcDebug      *Debug;
  INT64_STRUCT  Value;
  UINT32        ChannelIndex;
  UINT32        ChannelMax;
  UINT32        ChannelStart;
  UINT32        RankIndex;
  UINT32        RankMax;
  UINT32        RankStart;
  UINT32        Byte;
  UINT32        ByteMax;
  UINT32        ByteStart;
  UINT32        BitIndex;
  UINT32        BitMax;
  UINT32        BitStart;

  Debug = &MrcData->Outputs.Debug;

  if ((Strobe >= MAX_SDRAM_IN_DIMM) && (Strobe != MRC_IGNORE_ARG)) {
    ByteMax   = MrcData->Outputs.SdramCount;
    ByteStart = 0;
  } else {
    ByteMax   = Strobe + 1;
    ByteStart = Strobe;
  }
  if ((Bit >= MAX_BITS) && (Strobe != MRC_IGNORE_ARG)) {
    BitMax    = MAX_BITS;
    BitStart  = 0;
  } else {
    BitMax    = Bit + 1;
    BitStart  = Bit;
  }
  if ((Channel >= MAX_CHANNEL) && (Channel != MRC_IGNORE_ARG)) {
    ChannelMax    = MAX_CHANNEL;
    ChannelStart  = 0;
  } else {
    ChannelMax    = Channel + 1;
    ChannelStart  = Channel;
  }
  if ((Rank >= MAX_RANK_IN_CHANNEL) && (Rank != MRC_IGNORE_ARG)) {
    RankMax   = MAX_RANK_IN_CHANNEL;
    RankStart = 0;
  } else {
    RankMax   = Rank + 1;
    RankStart = Rank;
  }

  switch (Group) {
    case RecEnDelay:
      for (ChannelIndex = ChannelStart; ChannelIndex < ChannelMax; ChannelIndex++) {
        for (RankIndex = RankStart; RankIndex < RankMax; RankIndex++) {
          if (!MrcRankInChannelExist (MrcData, RankIndex, ChannelIndex)) {
            continue;
          }
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RecEnDelay Channel %u Rank %u:\n", ChannelIndex, RankIndex);
          for (Byte = ByteStart; Byte < ByteMax; Byte++) {
            if (MrcByteInChannelExist (MrcData, ChannelIndex, Byte)) {
              MrcGetSetDdrIoGroup (
                MrcData,
                SOCKET_0,
                ChannelIndex,
                MRC_IGNORE_ARG,
                MRC_IGNORE_ARG,
                RankIndex,
                Byte,
                MRC_IGNORE_ARG,
                MRC_IGNORE_ARG,
                DdrLevel,
                RecEnDelay,
                GSM_READ_ONLY,
                &Value.Data
                );
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " B%u: %d\n", Byte, Value.Data32.Low);
            }
          }
        }
      } // Byte
    break;

    case RxDqBitDelay:
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RxDqBitDelay Channel %u Rank %u Byte %u:", Channel, Rank, Strobe);
        for (BitIndex = BitStart; BitIndex < BitMax; BitIndex++) {
          MrcGetSetDdrIoGroup (
            MrcData,
            SOCKET_0,
            Channel,
            MRC_IGNORE_ARG,
            MRC_IGNORE_ARG,
            Rank,
            Strobe,
            BitIndex,
            MRC_IGNORE_ARG,
            DdrLevel,
            RxDqBitDelay,
            GSM_READ_ONLY,
            &Value.Data
            );
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %02X", Value.Data32.Low);
        } // Bit
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
    break;

    default:
      break;
  }
  return (mrcSuccess);
}
#endif // MRC_DEBUG_PRINT



/**
  Update MRC Host Data Structure when GSM_UPDATE_HOST is set.
  Currently only used for RxDqBitDelay and TxDqBitDelay

  @param[in]      MrcData     - Pointer to global data structure.
  @param[in]      Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]      Rank        - Rank number within a channel (0-based).
  @param[in]      Strobe      - If Group is a CMD/CTL/CLK Index type, this is the index for that signal.  Otherwise, Dqs data group within the rank (0-based).
  @param[in]      Bit         - Bit index within the data group (0-based).
  @param[in]      Group       - DDRIO group to access.
  @param[in,out]  Value       - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

**/
void
MrcGetSetUpdateHost (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Channel,
  IN      UINT32        const   Rank,
  IN      UINT32        const   Strobe,
  IN      UINT32        const   Bit,
  IN      GSM_GT        const   Group,
  IN      INT64         const   Value
  )
{
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;

  Outputs           = &MrcData->Outputs;
  ControllerOut     = &Outputs->Controller[0];
  ChannelOut        = &ControllerOut->Channel[Channel];

  switch (Group) {
    case RxDqBitDelay:
      ChannelOut->RxDqPb[Rank][Strobe][Bit].Center = (UINT8) Value;
      break;

    case TxDqBitDelay:
      ChannelOut->TxDqPb[Rank][Strobe][Bit].Center = (UINT8) Value;
      break;

    default:
      break;
  }
}

